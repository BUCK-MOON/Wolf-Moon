// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from livox_ros_driver2:msg/CustomMsg.idl
// generated code does not contain a copyright notice
#include "livox_ros_driver2/msg/detail/custom_msg__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `points`
#include "livox_ros_driver2/msg/detail/custom_point__functions.h"

bool
livox_ros_driver2__msg__CustomMsg__init(livox_ros_driver2__msg__CustomMsg * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    livox_ros_driver2__msg__CustomMsg__fini(msg);
    return false;
  }
  // timebase
  // point_num
  // lidar_id
  // rsvd
  // points
  if (!livox_ros_driver2__msg__CustomPoint__Sequence__init(&msg->points, 0)) {
    livox_ros_driver2__msg__CustomMsg__fini(msg);
    return false;
  }
  return true;
}

void
livox_ros_driver2__msg__CustomMsg__fini(livox_ros_driver2__msg__CustomMsg * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // timebase
  // point_num
  // lidar_id
  // rsvd
  // points
  livox_ros_driver2__msg__CustomPoint__Sequence__fini(&msg->points);
}

bool
livox_ros_driver2__msg__CustomMsg__are_equal(const livox_ros_driver2__msg__CustomMsg * lhs, const livox_ros_driver2__msg__CustomMsg * rhs)
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
  // timebase
  if (lhs->timebase != rhs->timebase) {
    return false;
  }
  // point_num
  if (lhs->point_num != rhs->point_num) {
    return false;
  }
  // lidar_id
  if (lhs->lidar_id != rhs->lidar_id) {
    return false;
  }
  // rsvd
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->rsvd[i] != rhs->rsvd[i]) {
      return false;
    }
  }
  // points
  if (!livox_ros_driver2__msg__CustomPoint__Sequence__are_equal(
      &(lhs->points), &(rhs->points)))
  {
    return false;
  }
  return true;
}

bool
livox_ros_driver2__msg__CustomMsg__copy(
  const livox_ros_driver2__msg__CustomMsg * input,
  livox_ros_driver2__msg__CustomMsg * output)
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
  // timebase
  output->timebase = input->timebase;
  // point_num
  output->point_num = input->point_num;
  // lidar_id
  output->lidar_id = input->lidar_id;
  // rsvd
  for (size_t i = 0; i < 3; ++i) {
    output->rsvd[i] = input->rsvd[i];
  }
  // points
  if (!livox_ros_driver2__msg__CustomPoint__Sequence__copy(
      &(input->points), &(output->points)))
  {
    return false;
  }
  return true;
}

livox_ros_driver2__msg__CustomMsg *
livox_ros_driver2__msg__CustomMsg__create()
{
  livox_ros_driver2__msg__CustomMsg * msg = (livox_ros_driver2__msg__CustomMsg *)malloc(sizeof(livox_ros_driver2__msg__CustomMsg));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(livox_ros_driver2__msg__CustomMsg));
  bool success = livox_ros_driver2__msg__CustomMsg__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
livox_ros_driver2__msg__CustomMsg__destroy(livox_ros_driver2__msg__CustomMsg * msg)
{
  if (msg) {
    livox_ros_driver2__msg__CustomMsg__fini(msg);
  }
  free(msg);
}


bool
livox_ros_driver2__msg__CustomMsg__Sequence__init(livox_ros_driver2__msg__CustomMsg__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  livox_ros_driver2__msg__CustomMsg * data = NULL;
  if (size) {
    data = (livox_ros_driver2__msg__CustomMsg *)calloc(size, sizeof(livox_ros_driver2__msg__CustomMsg));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = livox_ros_driver2__msg__CustomMsg__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        livox_ros_driver2__msg__CustomMsg__fini(&data[i - 1]);
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
livox_ros_driver2__msg__CustomMsg__Sequence__fini(livox_ros_driver2__msg__CustomMsg__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      livox_ros_driver2__msg__CustomMsg__fini(&array->data[i]);
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

livox_ros_driver2__msg__CustomMsg__Sequence *
livox_ros_driver2__msg__CustomMsg__Sequence__create(size_t size)
{
  livox_ros_driver2__msg__CustomMsg__Sequence * array = (livox_ros_driver2__msg__CustomMsg__Sequence *)malloc(sizeof(livox_ros_driver2__msg__CustomMsg__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = livox_ros_driver2__msg__CustomMsg__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
livox_ros_driver2__msg__CustomMsg__Sequence__destroy(livox_ros_driver2__msg__CustomMsg__Sequence * array)
{
  if (array) {
    livox_ros_driver2__msg__CustomMsg__Sequence__fini(array);
  }
  free(array);
}

bool
livox_ros_driver2__msg__CustomMsg__Sequence__are_equal(const livox_ros_driver2__msg__CustomMsg__Sequence * lhs, const livox_ros_driver2__msg__CustomMsg__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!livox_ros_driver2__msg__CustomMsg__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
livox_ros_driver2__msg__CustomMsg__Sequence__copy(
  const livox_ros_driver2__msg__CustomMsg__Sequence * input,
  livox_ros_driver2__msg__CustomMsg__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(livox_ros_driver2__msg__CustomMsg);
    livox_ros_driver2__msg__CustomMsg * data =
      (livox_ros_driver2__msg__CustomMsg *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!livox_ros_driver2__msg__CustomMsg__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          livox_ros_driver2__msg__CustomMsg__fini(&data[i]);
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
    if (!livox_ros_driver2__msg__CustomMsg__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
