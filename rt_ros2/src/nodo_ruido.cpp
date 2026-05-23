// rt_ros2/src/nodo_ruido.cpp
#include <rclcpp/rclcpp.hpp>
#include <cmath>

namespace rt_ros2 {

class NodoRuido : public rclcpp::Node {
    rclcpp::TimerBase::SharedPtr timer_;
    volatile double resultado_ = 0.0;

public:
    NodoRuido() : Node("nodo_ruido") {
        // Carga CPU cada 5ms con trabajo artificial
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(5),
            [this]() {
                // Trabajo intensivo de CPU para crear contención
                for (int i = 0; i < 500000; i++) {
                    resultado_ += std::sin(i) * std::cos(i);
                }
            }
        );
        RCLCPP_INFO(this->get_logger(), "Nodo ruido iniciado");
    }
};

} // namespace rt_ros2

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    auto nodo = std::make_shared<rt_ros2::NodoRuido>();
    rclcpp::spin(nodo);
    rclcpp::shutdown();
}