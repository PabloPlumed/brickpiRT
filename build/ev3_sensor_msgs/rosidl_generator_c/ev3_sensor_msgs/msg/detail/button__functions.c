// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ev3_sensor_msgs:msg/Button.idl
// generated code does not contain a copyright notice
#include "ev3_sensor_msgs/msg/detail/button__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
ev3_sensor_msgs__msg__Button__init(ev3_sensor_msgs__msg__Button * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    ev3_sensor_msgs__msg__Button__fini(msg);
    return false;
  }
  // state
  return true;
}

void
ev3_sensor_msgs__msg__Button__fini(ev3_sensor_msgs__msg__Button * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
}

bool
ev3_sensor_msgs__msg__Button__are_equal(const ev3_sensor_msgs__msg__Button * lhs, const ev3_sensor_msgs__msg__Button * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  return true;
}

bool
ev3_sensor_msgs__msg__Button__copy(
  const ev3_sensor_msgs__msg__Button * input,
  ev3_sensor_msgs__msg__Button * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // state
  output->state = input->state;
  return true;
}

ev3_sensor_msgs__msg__Button *
ev3_sensor_msgs__msg__Button__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ev3_sensor_msgs__msg__Button * msg = (ev3_sensor_msgs__msg__Button *)allocator.allocate(sizeof(ev3_sensor_msgs__msg__Button), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ev3_sensor_msgs__msg__Button));
  bool success = ev3_sensor_msgs__msg__Button__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
ev3_sensor_msgs__msg__Button__destroy(ev3_sensor_msgs__msg__Button * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    ev3_sensor_msgs__msg__Button__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
ev3_sensor_msgs__msg__Button__Sequence__init(ev3_sensor_msgs__msg__Button__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ev3_sensor_msgs__msg__Button * data = NULL;

  if (size) {
    data = (ev3_sensor_msgs__msg__Button *)allocator.zero_allocate(size, sizeof(ev3_sensor_msgs__msg__Button), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ev3_sensor_msgs__msg__Button__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ev3_sensor_msgs__msg__Button__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
ev3_sensor_msgs__msg__Button__Sequence__fini(ev3_sensor_msgs__msg__Button__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ev3_sensor_msgs__msg__Button__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

ev3_sensor_msgs__msg__Button__Sequence *
ev3_sensor_msgs__msg__Button__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  ev3_sensor_msgs__msg__Button__Sequence * array = (ev3_sensor_msgs__msg__Button__Sequence *)allocator.allocate(sizeof(ev3_sensor_msgs__msg__Button__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = ev3_sensor_msgs__msg__Button__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
ev3_sensor_msgs__msg__Button__Sequence__destroy(ev3_sensor_msgs__msg__Button__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    ev3_sensor_msgs__msg__Button__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
ev3_sensor_msgs__msg__Button__Sequence__are_equal(const ev3_sensor_msgs__msg__Button__Sequence * lhs, const ev3_sensor_msgs__msg__Button__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ev3_sensor_msgs__msg__Button__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ev3_sensor_msgs__msg__Button__Sequence__copy(
  const ev3_sensor_msgs__msg__Button__Sequence * input,
  ev3_sensor_msgs__msg__Button__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ev3_sensor_msgs__msg__Button);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    ev3_sensor_msgs__msg__Button * data =
      (ev3_sensor_msgs__msg__Button *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ev3_sensor_msgs__msg__Button__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          ev3_sensor_msgs__msg__Button__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!ev3_sensor_msgs__msg__Button__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
