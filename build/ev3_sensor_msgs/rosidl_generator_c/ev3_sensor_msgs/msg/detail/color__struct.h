// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ev3_sensor_msgs:msg/Color.idl
// generated code does not contain a copyright notice

#ifndef EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__STRUCT_H_
#define EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'color'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Color in the package ev3_sensor_msgs.
typedef struct ev3_sensor_msgs__msg__Color
{
  std_msgs__msg__Header header;
  rosidl_runtime_c__String color;
} ev3_sensor_msgs__msg__Color;

// Struct for a sequence of ev3_sensor_msgs__msg__Color.
typedef struct ev3_sensor_msgs__msg__Color__Sequence
{
  ev3_sensor_msgs__msg__Color * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ev3_sensor_msgs__msg__Color__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // EV3_SENSOR_MSGS__MSG__DETAIL__COLOR__STRUCT_H_
