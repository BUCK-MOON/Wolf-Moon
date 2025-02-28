// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/Uart.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/uart__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"

bool
auto_aim_interfaces__msg__Uart__init(auto_aim_interfaces__msg__Uart * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    auto_aim_interfaces__msg__Uart__fini(msg);
    return false;
  }
  // remain_time
  // game_stage
  // outpost_hp
  // sentry_hp
  // commd_keyboard
  // x
  // y
  return true;
}

void
auto_aim_interfaces__msg__Uart__fini(auto_aim_interfaces__msg__Uart * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // remain_time
  // game_stage
  // outpost_hp
  // sentry_hp
  // commd_keyboard
  // x
  // y
}

bool
auto_aim_interfaces__msg__Uart__are_equal(const auto_aim_interfaces__msg__Uart * lhs, const auto_aim_interfaces__msg__Uart * rhs)
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
  // remain_time
  if (lhs->remain_time != rhs->remain_time) {
    return false;
  }
  // game_stage
  if (lhs->game_stage != rhs->game_stage) {
    return false;
  }
  // outpost_hp
  if (lhs->outpost_hp != rhs->outpost_hp) {
    return false;
  }
  // sentry_hp
  if (lhs->sentry_hp != rhs->sentry_hp) {
    return false;
  }
  // commd_keyboard
  if (lhs->commd_keyboard != rhs->commd_keyboard) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  return true;
}

bool
auto_aim_interfaces__msg__Uart__copy(
  const auto_aim_interfaces__msg__Uart * input,
  auto_aim_interfaces__msg__Uart * output)
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
  // remain_time
  output->remain_time = input->remain_time;
  // game_stage
  output->game_stage = input->game_stage;
  // outpost_hp
  output->outpost_hp = input->outpost_hp;
  // sentry_hp
  output->sentry_hp = input->sentry_hp;
  // commd_keyboard
  output->commd_keyboard = input->commd_keyboard;
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

auto_aim_interfaces__msg__Uart *
auto_aim_interfaces__msg__Uart__create()
{
  auto_aim_interfaces__msg__Uart * msg = (auto_aim_interfaces__msg__Uart *)malloc(sizeof(auto_aim_interfaces__msg__Uart));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__Uart));
  bool success = auto_aim_interfaces__msg__Uart__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__Uart__destroy(auto_aim_interfaces__msg__Uart * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__Uart__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__Uart__Sequence__init(auto_aim_interfaces__msg__Uart__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__Uart * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__Uart *)calloc(size, sizeof(auto_aim_interfaces__msg__Uart));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__Uart__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__Uart__fini(&data[i - 1]);
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
auto_aim_interfaces__msg__Uart__Sequence__fini(auto_aim_interfaces__msg__Uart__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__Uart__fini(&array->data[i]);
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

auto_aim_interfaces__msg__Uart__Sequence *
auto_aim_interfaces__msg__Uart__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__Uart__Sequence * array = (auto_aim_interfaces__msg__Uart__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__Uart__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__Uart__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__Uart__Sequence__destroy(auto_aim_interfaces__msg__Uart__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__Uart__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__Uart__Sequence__are_equal(const auto_aim_interfaces__msg__Uart__Sequence * lhs, const auto_aim_interfaces__msg__Uart__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__Uart__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__Uart__Sequence__copy(
  const auto_aim_interfaces__msg__Uart__Sequence * input,
  auto_aim_interfaces__msg__Uart__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__Uart);
    auto_aim_interfaces__msg__Uart * data =
      (auto_aim_interfaces__msg__Uart *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__Uart__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__Uart__fini(&data[i]);
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
    if (!auto_aim_interfaces__msg__Uart__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
