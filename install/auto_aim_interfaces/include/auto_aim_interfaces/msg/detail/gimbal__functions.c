// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/Gimbal.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/gimbal__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `meas_point_cam`
// Member `pred_point_cam`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
auto_aim_interfaces__msg__Gimbal__init(auto_aim_interfaces__msg__Gimbal * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    auto_aim_interfaces__msg__Gimbal__fini(msg);
    return false;
  }
  // pitch
  // yaw
  // distance
  // is_switched
  // is_target
  // is_spinning
  // is_spinning_switched
  // is_shooting
  // is_prediction
  // meas_point_cam
  if (!geometry_msgs__msg__Point__init(&msg->meas_point_cam)) {
    auto_aim_interfaces__msg__Gimbal__fini(msg);
    return false;
  }
  // pred_point_cam
  if (!geometry_msgs__msg__Point__init(&msg->pred_point_cam)) {
    auto_aim_interfaces__msg__Gimbal__fini(msg);
    return false;
  }
  return true;
}

void
auto_aim_interfaces__msg__Gimbal__fini(auto_aim_interfaces__msg__Gimbal * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // pitch
  // yaw
  // distance
  // is_switched
  // is_target
  // is_spinning
  // is_spinning_switched
  // is_shooting
  // is_prediction
  // meas_point_cam
  geometry_msgs__msg__Point__fini(&msg->meas_point_cam);
  // pred_point_cam
  geometry_msgs__msg__Point__fini(&msg->pred_point_cam);
}

bool
auto_aim_interfaces__msg__Gimbal__are_equal(const auto_aim_interfaces__msg__Gimbal * lhs, const auto_aim_interfaces__msg__Gimbal * rhs)
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
  // pitch
  if (lhs->pitch != rhs->pitch) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // is_switched
  if (lhs->is_switched != rhs->is_switched) {
    return false;
  }
  // is_target
  if (lhs->is_target != rhs->is_target) {
    return false;
  }
  // is_spinning
  if (lhs->is_spinning != rhs->is_spinning) {
    return false;
  }
  // is_spinning_switched
  if (lhs->is_spinning_switched != rhs->is_spinning_switched) {
    return false;
  }
  // is_shooting
  if (lhs->is_shooting != rhs->is_shooting) {
    return false;
  }
  // is_prediction
  if (lhs->is_prediction != rhs->is_prediction) {
    return false;
  }
  // meas_point_cam
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->meas_point_cam), &(rhs->meas_point_cam)))
  {
    return false;
  }
  // pred_point_cam
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->pred_point_cam), &(rhs->pred_point_cam)))
  {
    return false;
  }
  return true;
}

bool
auto_aim_interfaces__msg__Gimbal__copy(
  const auto_aim_interfaces__msg__Gimbal * input,
  auto_aim_interfaces__msg__Gimbal * output)
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
  // pitch
  output->pitch = input->pitch;
  // yaw
  output->yaw = input->yaw;
  // distance
  output->distance = input->distance;
  // is_switched
  output->is_switched = input->is_switched;
  // is_target
  output->is_target = input->is_target;
  // is_spinning
  output->is_spinning = input->is_spinning;
  // is_spinning_switched
  output->is_spinning_switched = input->is_spinning_switched;
  // is_shooting
  output->is_shooting = input->is_shooting;
  // is_prediction
  output->is_prediction = input->is_prediction;
  // meas_point_cam
  if (!geometry_msgs__msg__Point__copy(
      &(input->meas_point_cam), &(output->meas_point_cam)))
  {
    return false;
  }
  // pred_point_cam
  if (!geometry_msgs__msg__Point__copy(
      &(input->pred_point_cam), &(output->pred_point_cam)))
  {
    return false;
  }
  return true;
}

auto_aim_interfaces__msg__Gimbal *
auto_aim_interfaces__msg__Gimbal__create()
{
  auto_aim_interfaces__msg__Gimbal * msg = (auto_aim_interfaces__msg__Gimbal *)malloc(sizeof(auto_aim_interfaces__msg__Gimbal));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__Gimbal));
  bool success = auto_aim_interfaces__msg__Gimbal__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__Gimbal__destroy(auto_aim_interfaces__msg__Gimbal * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__Gimbal__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__Gimbal__Sequence__init(auto_aim_interfaces__msg__Gimbal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__Gimbal * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__Gimbal *)calloc(size, sizeof(auto_aim_interfaces__msg__Gimbal));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__Gimbal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__Gimbal__fini(&data[i - 1]);
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
auto_aim_interfaces__msg__Gimbal__Sequence__fini(auto_aim_interfaces__msg__Gimbal__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__Gimbal__fini(&array->data[i]);
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

auto_aim_interfaces__msg__Gimbal__Sequence *
auto_aim_interfaces__msg__Gimbal__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__Gimbal__Sequence * array = (auto_aim_interfaces__msg__Gimbal__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__Gimbal__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__Gimbal__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__Gimbal__Sequence__destroy(auto_aim_interfaces__msg__Gimbal__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__Gimbal__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__Gimbal__Sequence__are_equal(const auto_aim_interfaces__msg__Gimbal__Sequence * lhs, const auto_aim_interfaces__msg__Gimbal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__Gimbal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__Gimbal__Sequence__copy(
  const auto_aim_interfaces__msg__Gimbal__Sequence * input,
  auto_aim_interfaces__msg__Gimbal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__Gimbal);
    auto_aim_interfaces__msg__Gimbal * data =
      (auto_aim_interfaces__msg__Gimbal *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__Gimbal__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__Gimbal__fini(&data[i]);
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
    if (!auto_aim_interfaces__msg__Gimbal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
