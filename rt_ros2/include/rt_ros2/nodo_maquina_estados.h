#ifndef RT_ROS2__NODO_MAQUINA_ESTADOS_H_
#define RT_ROS2__NODO_MAQUINA_ESTADOS_H_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/illuminance.hpp>
#include <std_msgs/msg/float32.hpp>
#include <cactus_rt/tracing.h>

namespace rt_ros2
{
enum class Estado {
    SEGUIR_LINEA,
    RECUPERAR,
    PARAR
};

class NodoMaquinaEstados : public rclcpp::Node {
private:
    rclcpp::Subscription<sensor_msgs::msg::Illuminance>::SharedPtr color;  // Suscripción a /color
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr robot_estado;      // Publicación de /robot_estado
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr error_pos;        // Publicacion de /error_pos (error en frente a la posición incial del robot)
    rclcpp::Publisher<std_msgs::msg::Header>::SharedPtr sensor_stamp_pub;  // Publicación del timestamp de lectura del sensor para End-To-End delay

    rclcpp::TimerBase::SharedPtr timer_publicacion;      // Timer de publicación periódica del estado
    Estado estado_actual;                                // Estado en el que se encuentra el robot (SEGUIR_LINEA, RECUPERAR O PARAR)
    float valor_sensor;                                  // valor leído del sensor (0.0 negro, 1.0 blanco)
    rclcpp::Time stamp_recuperar;                        // Time stamp del inicio de la recuperación
    rclcpp::Time stamp_sensor;

    // Callback que recibe el topic /color (valor de iluminancia) y actualiza el estado
    void color_callback(const sensor_msgs::msg::Illuminance::SharedPtr topic);

    // Callback del timer, publica el estado del robot constantemente
    void publicar_estado_robot();

    // Tracer para medir latencias con cactus_rt
    std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracer;

public:
    NodoMaquinaEstados(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracerME);
};

}  // namespace rt_ros2
#endif  // RT_ROS2__NODO_MAQUINA_ESTADOS_H_
