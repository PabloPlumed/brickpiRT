// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ev3_sensor_msgs:msg/Button.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_HPP_
#define EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__ev3_sensor_msgs__msg__Button __attribute__((deprecated))
#else
# define DEPRECATED__ev3_sensor_msgs__msg__Button __declspec(deprecated)
#endif

namespace ev3_sensor_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Button_
{
  using Type = Button_<ContainerAllocator>;

  explicit Button_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
    }
  }

  explicit Button_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    uint8_t;
  _state_type state;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t RELEASED =
    0u;
  static constexpr uint8_t PRESSED =
    1u;

  // pointer types
  using RawPtr =
    ev3_sensor_msgs::msg::Button_<ContainerAllocator> *;
  using ConstRawPtr =
    const ev3_sensor_msgs::msg::Button_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ev3_sensor_msgs::msg::Button_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ev3_sensor_msgs::msg::Button_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ev3_sensor_msgs__msg__Button
    std::shared_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ev3_sensor_msgs__msg__Button
    std::shared_ptr<ev3_sensor_msgs::msg::Button_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Button_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const Button_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Button_

// alias to use template instance with default allocator
using Button =
  ev3_sensor_msgs::msg::Button_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Button_<ContainerAllocator>::RELEASED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t Button_<ContainerAllocator>::PRESSED;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace ev3_sensor_msgs

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_HPP_
