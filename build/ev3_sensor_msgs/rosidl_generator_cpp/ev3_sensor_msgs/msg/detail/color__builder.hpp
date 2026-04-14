// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ev3_sensor_msgs:msg/Color.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__BUILDER_HPP_
#define EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ev3_sensor_msgs/msg/detail/color__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ev3_sensor_msgs
{

namespace msg
{

namespace builder
{

class Init_Color_color
{
public:
  explicit Init_Color_color(::ev3_sensor_msgs::msg::Color & msg)
  : msg_(msg)
  {}
  ::ev3_sensor_msgs::msg::Color color(::ev3_sensor_msgs::msg::Color::_color_type arg)
  {
    msg_.color = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ev3_sensor_msgs::msg::Color msg_;
};

class Init_Color_header
{
public:
  Init_Color_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Color_color header(::ev3_sensor_msgs::msg::Color::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Color_color(msg_);
  }

private:
  ::ev3_sensor_msgs::msg::Color msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ev3_sensor_msgs::msg::Color>()
{
  return ev3_sensor_msgs::msg::builder::Init_Color_header();
}

}  // namespace ev3_sensor_msgs

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__BUILDER_HPP_
