#include "rt_ros2/nodo_ruido.h"

namespace rt_ros2 {

NodoRuido::NodoRuido(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracer)
    : Node("nodo_ruido"), tracer_(tracer)
{
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(5),
        [this]() {
            auto traza = tracer_->WithSpan("ruido_callback");
            for (int i = 0; i < 500000; i++) {
                resultado_ += std::sin(i) * std::cos(i);
            }
        }
    );
    RCLCPP_INFO(this->get_logger(), "Nodo ruido iniciado");
}

} // namespace rt_ros2