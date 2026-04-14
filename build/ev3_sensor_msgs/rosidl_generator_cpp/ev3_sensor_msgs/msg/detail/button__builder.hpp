// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ev3_sensor_msgs:msg/Button.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__BUILDER_HPP_
#define EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "ev3_sensor_msgs/msg/detail/button__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace ev3_sensor_msgs
{

namespace msg
{

namespace builder
{

class Init_Button_state
{
public:
  explicit Init_Button_state(::ev3_sensor_msgs::msg::Button & msg)
  : msg_(msg)
  {}
  ::ev3_sensor_msgs::msg::Button state(::ev3_sensor_msgs::msg::Button::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ev3_sensor_msgs::msg::Button msg_;
};

class Init_Button_header
{
public:
  Init_Button_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Button_state header(::ev3_sensor_msgs::msg::Button::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Button_state(msg_);
  }

private:
  ::ev3_sensor_msgs::msg::Button msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::ev3_sensor_msgs::msg::Button>()
{
  return ev3_sensor_msgs::msg::builder::Init_Button_header();
}

}  // namespace ev3_sensor_msgs

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__BUILDER_HPP_
