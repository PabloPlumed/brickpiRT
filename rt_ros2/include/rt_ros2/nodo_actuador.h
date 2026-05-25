#ifndef RT_ROS2__NODO_ACTUADOR_H_
#define RT_ROS2__NODO_ACTUADOR_H_

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float32.hpp>
#include <geometry_msgs/msg/twist_stamped.hpp>
#include <cactus_rt/tracing.h>

namespace rt_ros2 
{
class NodoActuador : public rclcpp::Node {
private:
    // Suscripciones
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr robot_estado;     // Suscripción a /robot_estado
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr error_pos;       // y al error de posición
    rclcpp::Subscription<std_msgs::msg::Header>::SharedPtr sensor_stamp_sub;

    rclcpp::Publisher<geometry_msgs::msg::TwistStamped>::SharedPtr cmd_vel;  // Publicación de /cmd_vel
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr e2e_delay_pub;

    rclcpp::TimerBase::SharedPtr timer_publicacion;   // Timer de publicación periódica del comando de velocidad
    std::string estado_actual;                        // Estado actual recibido de la máquina de estados
    float error_actual;                               // Valor del error de posición, de -0.5 a 0.5
    rclcpp::Time ultimo_stamp_sensor{0, 0, RCL_ROS_TIME};

    // Simplemente para prints
    std::string estado_anterior;
    float error_anterior;

    // Callbacks
    void estado_callback(const std_msgs::msg::String::SharedPtr topic);
    void error_callback(const std_msgs::msg::Float32::SharedPtr topic);
    void sensor_stamp_callback(const std_msgs::msg::Header::SharedPtr topic);

    // Lógica de control
    void publicar_cmd_vel();

    // Tracer para medir latencias con cactus_rt
    std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracer;
public:
    NodoActuador(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracerA);

};

}  // namespace rt_ros2
#endif  // RT_ROS2__NODO_ACTUADOR_H_
