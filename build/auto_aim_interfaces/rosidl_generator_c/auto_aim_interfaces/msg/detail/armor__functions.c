// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from auto_aim_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/armor__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `number`
// Member `type`
#include "rosidl_runtime_c/string_functions.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose__functions.h"

bool
auto_aim_interfaces__msg__Armor__init(auto_aim_interfaces__msg__Armor * msg)
{
  if (!msg) {
    return false;
  }
  // number
  if (!rosidl_runtime_c__String__init(&msg->number)) {
    auto_aim_interfaces__msg__Armor__fini(msg);
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__init(&msg->type)) {
    auto_aim_interfaces__msg__Armor__fini(msg);
    return false;
  }
  // distance_to_image_center
  // pose
  if (!geometry_msgs__msg__Pose__init(&msg->pose)) {
    auto_aim_interfaces__msg__Armor__fini(msg);
    return false;
  }
  return true;
}

void
auto_aim_interfaces__msg__Armor__fini(auto_aim_interfaces__msg__Armor * msg)
{
  if (!msg) {
    return;
  }
  // number
  rosidl_runtime_c__String__fini(&msg->number);
  // type
  rosidl_runtime_c__String__fini(&msg->type);
  // distance_to_image_center
  // pose
  geometry_msgs__msg__Pose__fini(&msg->pose);
}

bool
auto_aim_interfaces__msg__Armor__are_equal(const auto_aim_interfaces__msg__Armor * lhs, const auto_aim_interfaces__msg__Armor * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // number
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->number), &(rhs->number)))
  {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->type), &(rhs->type)))
  {
    return false;
  }
  // distance_to_image_center
  if (lhs->distance_to_image_center != rhs->distance_to_image_center) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__Pose__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  return true;
}

bool
auto_aim_interfaces__msg__Armor__copy(
  const auto_aim_interfaces__msg__Armor * input,
  auto_aim_interfaces__msg__Armor * output)
{
  if (!input || !output) {
    return false;
  }
  // number
  if (!rosidl_runtime_c__String__copy(
      &(input->number), &(output->number)))
  {
    return false;
  }
  // type
  if (!rosidl_runtime_c__String__copy(
      &(input->type), &(output->type)))
  {
    return false;
  }
  // distance_to_image_center
  output->distance_to_image_center = input->distance_to_image_center;
  // pose
  if (!geometry_msgs__msg__Pose__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  return true;
}

auto_aim_interfaces__msg__Armor *
auto_aim_interfaces__msg__Armor__create()
{
  auto_aim_interfaces__msg__Armor * msg = (auto_aim_interfaces__msg__Armor *)malloc(sizeof(auto_aim_interfaces__msg__Armor));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(auto_aim_interfaces__msg__Armor));
  bool success = auto_aim_interfaces__msg__Armor__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
auto_aim_interfaces__msg__Armor__destroy(auto_aim_interfaces__msg__Armor * msg)
{
  if (msg) {
    auto_aim_interfaces__msg__Armor__fini(msg);
  }
  free(msg);
}


bool
auto_aim_interfaces__msg__Armor__Sequence__init(auto_aim_interfaces__msg__Armor__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  auto_aim_interfaces__msg__Armor * data = NULL;
  if (size) {
    data = (auto_aim_interfaces__msg__Armor *)calloc(size, sizeof(auto_aim_interfaces__msg__Armor));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = auto_aim_interfaces__msg__Armor__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        auto_aim_interfaces__msg__Armor__fini(&data[i - 1]);
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
auto_aim_interfaces__msg__Armor__Sequence__fini(auto_aim_interfaces__msg__Armor__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      auto_aim_interfaces__msg__Armor__fini(&array->data[i]);
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

auto_aim_interfaces__msg__Armor__Sequence *
auto_aim_interfaces__msg__Armor__Sequence__create(size_t size)
{
  auto_aim_interfaces__msg__Armor__Sequence * array = (auto_aim_interfaces__msg__Armor__Sequence *)malloc(sizeof(auto_aim_interfaces__msg__Armor__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = auto_aim_interfaces__msg__Armor__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
auto_aim_interfaces__msg__Armor__Sequence__destroy(auto_aim_interfaces__msg__Armor__Sequence * array)
{
  if (array) {
    auto_aim_interfaces__msg__Armor__Sequence__fini(array);
  }
  free(array);
}

bool
auto_aim_interfaces__msg__Armor__Sequence__are_equal(const auto_aim_interfaces__msg__Armor__Sequence * lhs, const auto_aim_interfaces__msg__Armor__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!auto_aim_interfaces__msg__Armor__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
auto_aim_interfaces__msg__Armor__Sequence__copy(
  const auto_aim_interfaces__msg__Armor__Sequence * input,
  auto_aim_interfaces__msg__Armor__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(auto_aim_interfaces__msg__Armor);
    auto_aim_interfaces__msg__Armor * data =
      (auto_aim_interfaces__msg__Armor *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!auto_aim_interfaces__msg__Armor__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          auto_aim_interfaces__msg__Armor__fini(&data[i]);
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
    if (!auto_aim_interfaces__msg__Armor__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
