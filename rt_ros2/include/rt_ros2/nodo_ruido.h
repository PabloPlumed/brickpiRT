#ifndef RT_ROS2__NODO_RUIDO_H_
#define RT_ROS2__NODO_RUIDO_H_

#include <rclcpp/rclcpp.hpp>
#include <cmath>
#include <cactus_rt/tracing.h>

namespace rt_ros2 {

class NodoRuido : public rclcpp::Node {
    rclcpp::TimerBase::SharedPtr timer_;
    volatile double resultado_ = 0.0;
    std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracer_;

public:
    NodoRuido(std::shared_ptr<cactus_rt::tracing::ThreadTracer> tracer);
};

} // namespace rt_ros2
#endif