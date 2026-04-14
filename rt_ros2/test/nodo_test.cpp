// test/test_automatico.cpp
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/illuminance.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_msgs/msg/float32.hpp>

#define FREC_SENSOR_MS  100   // 10Hz, que es la frecuencia del sensor en el sistema real
#define TAM_COLA_ROS    10

namespace rt_ros2
{

class TestAutomatico : public rclcpp::Node
{
private:
    int tick;
        
    rclcpp::TimerBase::SharedPtr timer;
        
    rclcpp::Publisher<sensor_msgs::msg::Illuminance>::SharedPtr pub_sensor;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_estado;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_error;


    void publicar()
    {
        auto msg = sensor_msgs::msg::Illuminance();
        msg.header.stamp = this->get_clock()->now();

        // Hardcodeamos un escenario de prueba
        if      (tick < 20)  msg.illuminance = 0.7; // En línea negra, seguir línea
        else if (tick < 30)  msg.illuminance = 1.0; // Se ha salido de la línea, recuperar el trayecto
        else if (tick < 40)  msg.illuminance = 0.5; // Ha vuelto, volverla a seguir
        else if (tick < 50)  msg.illuminance = 0.8; // Sale por última vez
        else                 msg.illuminance = 0.6;  // timeout

        RCLCPP_INFO(this->get_logger(), "Tick %d → iluminancia=%.1f", tick, msg.illuminance);
        pub_sensor->publish(msg);
        tick++;
    }
    
public:
    TestAutomatico() : Node("test_automatico"), tick(0)
    {
        // Hace de nodo adquisidor y comprueba los valores que se obtienen de la adquisición
        pub_sensor = this->create_publisher<sensor_msgs::msg::Illuminance>("/light_intensity", TAM_COLA_ROS);

        // Informa del estado y el error que ha llegado del nodo actuador
        auto cb_estado = [this](const std_msgs::msg::String::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Estado: %s", msg->data.c_str());
        };
        sub_estado = this->create_subscription<std_msgs::msg::String>("/robot_estado", TAM_COLA_ROS, cb_estado);

        auto cb_error = [this](const std_msgs::msg::Float32::SharedPtr msg) {
            RCLCPP_INFO(this->get_logger(), "Error: %.3f", msg->data);
        };
        sub_error = this->create_subscription<std_msgs::msg::Float32>("/error_pos", TAM_COLA_ROS, cb_error);


        timer = this->create_wall_timer(std::chrono::milliseconds(FREC_SENSOR_MS),[this]() { publicar(); });

        RCLCPP_INFO(this->get_logger(), "Test automatico iniciado");
    }
};

}  // namespace rt_ros2

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto nodo = std::make_shared<rt_ros2::TestAutomatico>();
    rclcpp::spin(nodo);
    rclcpp::shutdown();
    return 0;
}
