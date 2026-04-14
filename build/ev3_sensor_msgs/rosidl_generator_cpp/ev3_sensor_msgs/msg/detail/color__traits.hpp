// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ev3_sensor_msgs:msg/Color.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__TRAITS_HPP_
#define EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "ev3_sensor_msgs/msg/detail/color__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace ev3_sensor_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Color & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Color & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Color & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace ev3_sensor_msgs

namespace rosidl_generator_traits
{

[[deprecated("use ev3_sensor_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const ev3_sensor_msgs::msg::Color & msg,
  std::ostream & out, size_t indentation = 0)
{
  ev3_sensor_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use ev3_sensor_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const ev3_sensor_msgs::msg::Color & msg)
{
  return ev3_sensor_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<ev3_sensor_msgs::msg::Color>()
{
  return "ev3_sensor_msgs::msg::Color";
}

template<>
inline const char * name<ev3_sensor_msgs::msg::Color>()
{
  return "ev3_sensor_msgs/msg/Color";
}

template<>
struct has_fixed_size<ev3_sensor_msgs::msg::Color>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ev3_sensor_msgs::msg::Color>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ev3_sensor_msgs::msg::Color>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__TRAITS_HPP_
