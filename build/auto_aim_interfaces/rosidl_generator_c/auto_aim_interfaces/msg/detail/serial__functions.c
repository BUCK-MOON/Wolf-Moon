// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/Serial.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/serial__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `imu`
#include "sensor_msgs/msg/detail/imu__functions.h"

bool
auto_aim_interfaces__msg__Serial__init(auto_aim_interfaces__msg__Serial * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    auto_aim_interfaces__msg__Serial__fini(msg);
    return false;
  }
  // imu
  if (!sensor_msgs__msg__Imu__init(&msg->imu)) {
    auto_aim_interfaces__msg__Serial__fini(msg);
    return false;
  }
  // mode
  // bullet_speed
  // shoot_delay
  return true;
}

void
auto_aim_interfaces__msg__Serial__fini(auto_aim_interfaces__msg__Serial * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // imu
  sensor_msgs__msg__Imu__fini(&msg->imu);
  // mode
  // bullet_speed
  // shoot_delay
}

bool
auto_aim_interfaces__msg__Serial__are_equal(const auto_aim_interfaces__msg__Serial * lhs, const auto_aim_interfaces__msg__Serial * rhs)
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
  // imu
  if (!sensor_msgs__msg__Imu__are_equal(
      &(lhs->imu), &(rhs->imu)))
  {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // bullet_speed
  if (lhs->bullet_speed != rhs->bullet_speed) {
    return false;
  }
  // shoot_delay
  if (lhs->shoot_delay != rhs->shoot_delay) {
    return false;
  }
  return true;
}

bool
auto_aim_interfaces__msg__Serial__copy(
  const auto_aim_interfaces__msg__Serial * input,
  auto_aim_interfaces__msg__Serial * output)
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
  // imu
  if (!sensor_msgs__msg__Imu__copy(
      &(input->imu), &(output->imu)))
  {
    return false;
  }
  // mode
  output->mode = input->mode;
  // bullet_speed
  output->bullet_speed = input->bullet_speed;
  // shoot_delay
  output->shoot_delay = input->shoot_delay;
  return true;
}

auto_aim_interfaces__msg__Serial *
auto_aim_interfaces__msg__Serial__create()
{
  auto_aim_interfaces__msg__Serial * msg = (auto_aim_interfaces__msg__Serial *)malloc(sizeof(auto_aim_interfaces__msg__Serial));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__Serial));
  bool success = auto_aim_interfaces__msg__Serial__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__Serial__destroy(auto_aim_interfaces__msg__Serial * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__Serial__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__Serial__Sequence__init(auto_aim_interfaces__msg__Serial__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__Serial * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__Serial *)calloc(size, sizeof(auto_aim_interfaces__msg__Serial));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__Serial__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__Serial__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
auto_aim_interfaces__msg__Serial__Sequence__fini(auto_aim_interfaces__msg__Serial__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__Serial__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

auto_aim_interfaces__msg__Serial__Sequence *
auto_aim_interfaces__msg__Serial__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__Serial__Sequence * array = (auto_aim_interfaces__msg__Serial__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__Serial__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__Serial__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__Serial__Sequence__destroy(auto_aim_interfaces__msg__Serial__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__Serial__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__Serial__Sequence__are_equal(const auto_aim_interfaces__msg__Serial__Sequence * lhs, const auto_aim_interfaces__msg__Serial__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__Serial__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__Serial__Sequence__copy(
  const auto_aim_interfaces__msg__Serial__Sequence * input,
  auto_aim_interfaces__msg__Serial__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__Serial);
    auto_aim_interfaces__msg__Serial * data =
      (auto_aim_interfaces__msg__Serial *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__Serial__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__Serial__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!auto_aim_interfaces__msg__Serial__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
