#include "rt_ros2/nodo_maquina_estados.h" 

#define UMBRAL_NEGRO  0.5f  // Por debajo de este valor, está dentro de la línea
#define UMBRAL_BLANCO 0.7f  // Por encima de esta valor, se ha salido de la línea
#define RECUPERAR_TO  10.0   // Timeout en segundos del estado de recuperar, si lo supera, el robot se para
#define TAM_COLA_ROS  10    // Tamaño del buffer antes de descartar los mensajes más viejos
#define FREC_TOPIC_MS 100   // Frecuencia a la que se publica un topic (en ms, no en Hz)

namespace rt_ros2
{

NodoMaquinaEstados::NodoMaquinaEstados(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracerME) 
                  : Node("nodo_maquina_estados"), estado_actual(Estado::SEGUIR_LINEA), valor_sensor(0.0f), tracer(tracerME)
{
    // Creación de suscripción 
    // bind empaqueta el callback, this le indica el objeto sobre el que se tiene que ejecutar y placeholders para el arg que llegará
    // funciones lambda en vez de bind por la resolución de direcciones de ROS2Humble
    auto cb_color = [this](const sensor_msgs::msg::Illuminance::SharedPtr msg) { color_callback(msg); }; 
    color = this->create_subscription<sensor_msgs::msg::Illuminance>("/light_intensity", TAM_COLA_ROS, cb_color);

    // Creación del topic del estado del robot y error en la posición
    robot_estado = this->create_publisher<std_msgs::msg::String>("/robot_estado", TAM_COLA_ROS);
    error_pos = this->create_publisher<std_msgs::msg::Float32>("/error_pos", TAM_COLA_ROS);

    // Cada 100 milis se publica el estado del robot, es decir, 10Hz
    auto cb_timer = [this]() { publicar_estado_robot(); };
    timer_publicacion = this->create_wall_timer( std::chrono::milliseconds(FREC_TOPIC_MS), cb_timer);

    RCLCPP_INFO(this->get_logger(), "Nodo Maquina de Estados Iniciado");
}

void NodoMaquinaEstados::color_callback(const sensor_msgs::msg::Illuminance::SharedPtr topic)
{
    // Empezamos la traza para medir la latencia
    auto trazaColor = tracer->WithSpan("color_callback");

    // Valor de iluminancia obtenido por el sensor
    valor_sensor = static_cast<float>(topic->illuminance);

    switch (estado_actual) {
        case Estado::SEGUIR_LINEA:
            // Solo entra en recuperación si ve blanco puro (muy lejos de la línea)
            if (valor_sensor > UMBRAL_BLANCO) {
                estado_actual = Estado::RECUPERAR;
                stamp_recuperar = this->now();
                RCLCPP_INFO(this->get_logger(), "¡Blanco puro! Perdiendo línea (valor = %.2f)", valor_sensor);
            }
            break;

        case Estado::RECUPERAR:
            // Si ve cualquier rastro de negro, vuelve a seguir línea
            if (valor_sensor <= UMBRAL_BLANCO) {
                estado_actual = Estado::SEGUIR_LINEA;
                RCLCPP_INFO(this->get_logger(), "Línea o borde detectado, volviendo a control proporcional (valor = %.2f)", valor_sensor);
            }
            // Si lleva un rato en blanco puro, paramos por seguridad
            else {
                double secs_recuperando = (this->now() - stamp_recuperar).seconds();
                if (secs_recuperando > RECUPERAR_TO) {
                    estado_actual = Estado::PARAR;
                    RCLCPP_WARN(this->get_logger(), "Timeout: Línea no encontrada (%.1fs)", secs_recuperando);
                }
            }
            break;

        case Estado::PARAR:
            if (valor_sensor <= UMBRAL_BLANCO) {
                estado_actual = Estado::SEGUIR_LINEA;
                RCLCPP_INFO(this->get_logger(), "Reiniciando seguimiento (valor = %.2f)", valor_sensor);
            }
            break;
    }
}

void NodoMaquinaEstados::publicar_estado_robot()
{
    // Empezamos la traza para medir la latencia
    auto trazaEstadoRobot = tracer->WithSpan("publicar_estado_robot");  

    // Publicar topic /robot_estado
    auto topic_estado = std_msgs::msg::String();
    switch (estado_actual) {
        case Estado::SEGUIR_LINEA: topic_estado.data = "SEGUIR_LINEA"; break;
        case Estado::RECUPERAR:    topic_estado.data = "RECUPERAR";    break;
        case Estado::PARAR:        topic_estado.data = "PARAR";        break;
    }
    robot_estado->publish(topic_estado);

    // Publicar topic /error_pos
    auto topic_error = std_msgs::msg::Float32();
    
    // IMPORTANTE: Definimos el "Punto de ajuste" (Set Point)
    // Si el sensor da 0.6 (más blanco que negro), el error será positivo (0.1) -> giro a un lado.
    // Si el sensor da 0.4 (más negro que blanco), el error será negativo (-0.1) -> giro al otro.
    // Si el sensor da 0.5 (mitad y mitad), el error es 0.0 -> recto.
    float set_point = 0.5f; 
    topic_error.data = valor_sensor - set_point;
    
    error_pos->publish(topic_error);
}

}  // namespace rt_ros2
