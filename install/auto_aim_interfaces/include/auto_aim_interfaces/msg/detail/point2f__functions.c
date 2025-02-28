// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/Point2f.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/point2f__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
auto_aim_interfaces__msg__Point2f__init(auto_aim_interfaces__msg__Point2f * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  return true;
}

void
auto_aim_interfaces__msg__Point2f__fini(auto_aim_interfaces__msg__Point2f * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
}

bool
auto_aim_interfaces__msg__Point2f__are_equal(const auto_aim_interfaces__msg__Point2f * lhs, const auto_aim_interfaces__msg__Point2f * rhs)
{
  if (!lhs || !rhs) {
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
auto_aim_interfaces__msg__Point2f__copy(
  const auto_aim_interfaces__msg__Point2f * input,
  auto_aim_interfaces__msg__Point2f * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  return true;
}

auto_aim_interfaces__msg__Point2f *
auto_aim_interfaces__msg__Point2f__create()
{
  auto_aim_interfaces__msg__Point2f * msg = (auto_aim_interfaces__msg__Point2f *)malloc(sizeof(auto_aim_interfaces__msg__Point2f));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__Point2f));
  bool success = auto_aim_interfaces__msg__Point2f__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__Point2f__destroy(auto_aim_interfaces__msg__Point2f * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__Point2f__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__Point2f__Sequence__init(auto_aim_interfaces__msg__Point2f__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__Point2f * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__Point2f *)calloc(size, sizeof(auto_aim_interfaces__msg__Point2f));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__Point2f__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__Point2f__fini(&data[i - 1]);
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
auto_aim_interfaces__msg__Point2f__Sequence__fini(auto_aim_interfaces__msg__Point2f__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__Point2f__fini(&array->data[i]);
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

auto_aim_interfaces__msg__Point2f__Sequence *
auto_aim_interfaces__msg__Point2f__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__Point2f__Sequence * array = (auto_aim_interfaces__msg__Point2f__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__Point2f__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__Point2f__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__Point2f__Sequence__destroy(auto_aim_interfaces__msg__Point2f__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__Point2f__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__Point2f__Sequence__are_equal(const auto_aim_interfaces__msg__Point2f__Sequence * lhs, const auto_aim_interfaces__msg__Point2f__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__Point2f__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__Point2f__Sequence__copy(
  const auto_aim_interfaces__msg__Point2f__Sequence * input,
  auto_aim_interfaces__msg__Point2f__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__Point2f);
    auto_aim_interfaces__msg__Point2f * data =
      (auto_aim_interfaces__msg__Point2f *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__Point2f__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__Point2f__fini(&data[i]);
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
    if (!auto_aim_interfaces__msg__Point2f__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
