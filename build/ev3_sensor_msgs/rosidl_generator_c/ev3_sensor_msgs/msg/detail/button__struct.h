// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ev3_sensor_msgs:msg/Button.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_H_
#define EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'RELEASED'.
enum
{
  ev3_sensor_msgs__msg__Button__RELEASED = 0
};

/// Constant 'PRESSED'.
enum
{
  ev3_sensor_msgs__msg__Button__PRESSED = 1
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/Button in the package ev3_sensor_msgs.
typedef struct ev3_sensor_msgs__msg__Button
{
  std_msgs__msg__Header header;
  uint8_t state;
} ev3_sensor_msgs__msg__Button;

// Struct for a sequence of ev3_sensor_msgs__msg__Button.
typedef struct ev3_sensor_msgs__msg__Button__Sequence
{
  ev3_sensor_msgs__msg__Button * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ev3_sensor_msgs__msg__Button__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__BUTTON__STRUCT_H_
