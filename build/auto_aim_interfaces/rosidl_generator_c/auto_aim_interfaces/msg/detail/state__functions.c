// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/state__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `center`
// Member `predict`
// Member `calculate`
// Member `angle`
#include "auto_aim_interfaces/msg/detail/point2f__functions.h"

bool
auto_aim_interfaces__msg__State__init(auto_aim_interfaces__msg__State * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    auto_aim_interfaces__msg__State__fini(msg);
    return false;
  }
  // mode
  // center
  for (size_t i = 0; i < 4; ++i) {
    if (!auto_aim_interfaces__msg__Point2f__init(&msg->center[i])) {
      auto_aim_interfaces__msg__State__fini(msg);
      return false;
    }
  }
  // predict
  if (!auto_aim_interfaces__msg__Point2f__init(&msg->predict)) {
    auto_aim_interfaces__msg__State__fini(msg);
    return false;
  }
  // calculate
  if (!auto_aim_interfaces__msg__Point2f__init(&msg->calculate)) {
    auto_aim_interfaces__msg__State__fini(msg);
    return false;
  }
  // angle
  if (!auto_aim_interfaces__msg__Point2f__init(&msg->angle)) {
    auto_aim_interfaces__msg__State__fini(msg);
    return false;
  }
  // state
  return true;
}

void
auto_aim_interfaces__msg__State__fini(auto_aim_interfaces__msg__State * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // mode
  // center
  for (size_t i = 0; i < 4; ++i) {
    auto_aim_interfaces__msg__Point2f__fini(&msg->center[i]);
  }
  // predict
  auto_aim_interfaces__msg__Point2f__fini(&msg->predict);
  // calculate
  auto_aim_interfaces__msg__Point2f__fini(&msg->calculate);
  // angle
  auto_aim_interfaces__msg__Point2f__fini(&msg->angle);
  // state
}

bool
auto_aim_interfaces__msg__State__are_equal(const auto_aim_interfaces__msg__State * lhs, const auto_aim_interfaces__msg__State * rhs)
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
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // center
  for (size_t i = 0; i < 4; ++i) {
    if (!auto_aim_interfaces__msg__Point2f__are_equal(
        &(lhs->center[i]), &(rhs->center[i])))
    {
      return false;
    }
  }
  // predict
  if (!auto_aim_interfaces__msg__Point2f__are_equal(
      &(lhs->predict), &(rhs->predict)))
  {
    return false;
  }
  // calculate
  if (!auto_aim_interfaces__msg__Point2f__are_equal(
      &(lhs->calculate), &(rhs->calculate)))
  {
    return false;
  }
  // angle
  if (!auto_aim_interfaces__msg__Point2f__are_equal(
      &(lhs->angle), &(rhs->angle)))
  {
    return false;
  }
  // state
  for (size_t i = 0; i < 9; ++i) {
    if (lhs->state[i] != rhs->state[i]) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__State__copy(
  const auto_aim_interfaces__msg__State * input,
  auto_aim_interfaces__msg__State * output)
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
  // mode
  output->mode = input->mode;
  // center
  for (size_t i = 0; i < 4; ++i) {
    if (!auto_aim_interfaces__msg__Point2f__copy(
        &(input->center[i]), &(output->center[i])))
    {
      return false;
    }
  }
  // predict
  if (!auto_aim_interfaces__msg__Point2f__copy(
      &(input->predict), &(output->predict)))
  {
    return false;
  }
  // calculate
  if (!auto_aim_interfaces__msg__Point2f__copy(
      &(input->calculate), &(output->calculate)))
  {
    return false;
  }
  // angle
  if (!auto_aim_interfaces__msg__Point2f__copy(
      &(input->angle), &(output->angle)))
  {
    return false;
  }
  // state
  for (size_t i = 0; i < 9; ++i) {
    output->state[i] = input->state[i];
  }
  return true;
}

auto_aim_interfaces__msg__State *
auto_aim_interfaces__msg__State__create()
{
  auto_aim_interfaces__msg__State * msg = (auto_aim_interfaces__msg__State *)malloc(sizeof(auto_aim_interfaces__msg__State));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__State));
  bool success = auto_aim_interfaces__msg__State__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__State__destroy(auto_aim_interfaces__msg__State * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__State__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__State__Sequence__init(auto_aim_interfaces__msg__State__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__State * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__State *)calloc(size, sizeof(auto_aim_interfaces__msg__State));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__State__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__State__fini(&data[i - 1]);
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
auto_aim_interfaces__msg__State__Sequence__fini(auto_aim_interfaces__msg__State__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__State__fini(&array->data[i]);
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

auto_aim_interfaces__msg__State__Sequence *
auto_aim_interfaces__msg__State__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__State__Sequence * array = (auto_aim_interfaces__msg__State__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__State__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__State__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__State__Sequence__destroy(auto_aim_interfaces__msg__State__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__State__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__State__Sequence__are_equal(const auto_aim_interfaces__msg__State__Sequence * lhs, const auto_aim_interfaces__msg__State__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__State__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__State__Sequence__copy(
  const auto_aim_interfaces__msg__State__Sequence * input,
  auto_aim_interfaces__msg__State__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__State);
    auto_aim_interfaces__msg__State * data =
      (auto_aim_interfaces__msg__State *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__State__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__State__fini(&data[i]);
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
    if (!auto_aim_interfaces__msg__State__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
