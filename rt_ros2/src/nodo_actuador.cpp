#include "rt_ros2/nodo_actuador.h"

#define KP            0.5f        // Ganancia proporcional para saber cuanto girar (tenemos valores entre 0 y 0.5)
#define VEL_LINEAL    0.03f       // Velocidad lineal base cuando sigue la línea
#define VEL_REC       0.02f       // Velocidad lineal cuando tiene que recuperar la línea
#define VEL_ANGULAR   0.3f // Velocidad angular el doble de agresiva al recuperar
#define TAM_COLA_ROS  10          // Tamaño del buffer antes de descartar los mensajes más viejos
#define FREC_TOPIC_MS 50          // Frecuencia a la que se publica un topic (en ms, no en Hz)

namespace rt_ros2
{

NodoActuador::NodoActuador(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracerA): 
              Node("nodo_actuador"), estado_actual("PARAR"), error_actual(0.0f), estado_anterior(""), error_anterior(0.0f), tracer(tracerA)
{
    // Suscripciones al estado del robot y al error con respecto a la posición inicial del robot
    auto cb_estado = [this](const std_msgs::msg::String::SharedPtr msg) { estado_callback(msg); };
    robot_estado = this->create_subscription<std_msgs::msg::String>("/robot_estado", TAM_COLA_ROS, cb_estado);

    auto cb_error  = [this](const std_msgs::msg::Float32::SharedPtr msg) { error_callback(msg); };
    error_pos = this->create_subscription<std_msgs::msg::Float32>("/error_pos", TAM_COLA_ROS, cb_error);

    // Creación del topic del estado de comando de velocidad para el controlador
    cmd_vel = this->create_publisher<geometry_msgs::msg::TwistStamped>("/cmd_vel", TAM_COLA_ROS);

    // Cada 50 milis se publica /cmd_vel, aunque no lleguen mensajes necesitamos 20Hz para que diff_drive_controller no pare el robot por timeout
    auto cb_timer = [this]() { publicar_cmd_vel(); };
    timer_publicacion = this->create_wall_timer(std::chrono::milliseconds(FREC_TOPIC_MS), cb_timer);

    RCLCPP_INFO(this->get_logger(), "Nodo Actuador Iniciado");
}

void NodoActuador::estado_callback(const std_msgs::msg::String::SharedPtr topic)
{   estado_actual = topic->data;   }

void NodoActuador::error_callback(const std_msgs::msg::Float32::SharedPtr topic)
{   error_actual = topic->data;    }

void printEstado(const rclcpp::Logger& logger, const std::string& estado, const float linear, const float angular)
{
    if (estado == "SEGUIR_LINEA") 
        RCLCPP_INFO(logger, "Tengo que seguir la línea (linear=%.2f, angular=%.2f)", linear, angular);
    else if (estado == "RECUPERAR") 
        RCLCPP_INFO(logger, "Recuperando posicion (linear=%.2f, angular=%.2f)", linear, angular);
    else if (estado == "PARAR")
        RCLCPP_WARN(logger, "Toca pararse (linear=%.2f, angular=%.2f)", linear, angular);
    else
        RCLCPP_ERROR(logger, "En que estado estoy!: %s", estado.c_str());
}

void NodoActuador::publicar_cmd_vel()
{
    // Empezamos la traza para medir la latencia
    auto trazaCmdVel = tracer->WithSpan("publicar_cmd_vel");

    // Creación del mensaje de velocidad, con el timestamp actual
    auto topic_vel = geometry_msgs::msg::TwistStamped();
    topic_vel.header.stamp = this->now();

    // LÓGICA PROPORCIONAL: 
    // Siempre corregimos el ángulo basándonos en el error.
    // Si error_actual > 0 (más blanco), angular.z será positivo/negativo para girar hacia la línea.
    if (estado_actual == "SEGUIR_LINEA") {
        topic_vel.twist.linear.x  = VEL_LINEAL;
        // El signo de KP dependerá de hacia qué lado quieres que gire el robot cuando vea blanco.
        // Si el sensor está a la derecha del eje central: blanco -> girar izquierda (angular.z positivo)
        topic_vel.twist.angular.z = -KP * error_actual; 
    } 
    // Si ha perdido la línea por completo (blanco puro)
    else if (estado_actual == "RECUPERAR") {
        topic_vel.twist.linear.x  = VEL_REC;
        // Gira en la última dirección conocida o hacia donde cree que está la línea
        topic_vel.twist.angular.z = (error_actual >= 0) ? -VEL_ANGULAR : VEL_ANGULAR;
    } 
    else {
        topic_vel.twist.linear.x = topic_vel.twist.angular.z = 0.0;
    }

    if (estado_actual != estado_anterior || std::abs(error_actual - error_anterior) > 0.01f) {
        printEstado(this->get_logger(), estado_actual, topic_vel.twist.linear.x, topic_vel.twist.angular.z);
        estado_anterior = estado_actual;
        error_anterior = error_actual;
    }

    cmd_vel->publish(topic_vel);
}

}  // namespace rt_ros2