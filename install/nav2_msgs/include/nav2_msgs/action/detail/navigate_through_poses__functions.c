// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from nav2_msgs:action/NavigateThroughPoses.idl
// generated code does not contain a copyright notice
#include "nav2_msgs/action/detail/navigate_through_poses__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `poses`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"
// Member `behavior_tree`
#include "rosidl_runtime_c/string_functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_Goal__init(nav2_msgs__action__NavigateThroughPoses_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // poses
  if (!geometry_msgs__msg__PoseStamped__Sequence__init(&msg->poses, 0)) {
    nav2_msgs__action__NavigateThroughPoses_Goal__fini(msg);
    return false;
  }
  // behavior_tree
  if (!rosidl_runtime_c__String__init(&msg->behavior_tree)) {
    nav2_msgs__action__NavigateThroughPoses_Goal__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_Goal__fini(nav2_msgs__action__NavigateThroughPoses_Goal * msg)
{
  if (!msg) {
    return;
  }
  // poses
  geometry_msgs__msg__PoseStamped__Sequence__fini(&msg->poses);
  // behavior_tree
  rosidl_runtime_c__String__fini(&msg->behavior_tree);
}

bool
nav2_msgs__action__NavigateThroughPoses_Goal__are_equal(const nav2_msgs__action__NavigateThroughPoses_Goal * lhs, const nav2_msgs__action__NavigateThroughPoses_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // poses
  if (!geometry_msgs__msg__PoseStamped__Sequence__are_equal(
      &(lhs->poses), &(rhs->poses)))
  {
    return false;
  }
  // behavior_tree
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->behavior_tree), &(rhs->behavior_tree)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Goal__copy(
  const nav2_msgs__action__NavigateThroughPoses_Goal * input,
  nav2_msgs__action__NavigateThroughPoses_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // poses
  if (!geometry_msgs__msg__PoseStamped__Sequence__copy(
      &(input->poses), &(output->poses)))
  {
    return false;
  }
  // behavior_tree
  if (!rosidl_runtime_c__String__copy(
      &(input->behavior_tree), &(output->behavior_tree)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_Goal *
nav2_msgs__action__NavigateThroughPoses_Goal__create()
{
  nav2_msgs__action__NavigateThroughPoses_Goal * msg = (nav2_msgs__action__NavigateThroughPoses_Goal *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Goal));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_Goal));
  bool success = nav2_msgs__action__NavigateThroughPoses_Goal__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_Goal__destroy(nav2_msgs__action__NavigateThroughPoses_Goal * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_Goal__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__init(nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_Goal * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_Goal *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_Goal));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_Goal__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_Goal__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_Goal__Sequence *
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_Goal__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Goal__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Goal__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_Goal);
    nav2_msgs__action__NavigateThroughPoses_Goal * data =
      (nav2_msgs__action__NavigateThroughPoses_Goal *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_Goal__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_Goal__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
#include "std_msgs/msg/detail/empty__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_Result__init(nav2_msgs__action__NavigateThroughPoses_Result * msg)
{
  if (!msg) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__init(&msg->result)) {
    nav2_msgs__action__NavigateThroughPoses_Result__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_Result__fini(nav2_msgs__action__NavigateThroughPoses_Result * msg)
{
  if (!msg) {
    return;
  }
  // result
  std_msgs__msg__Empty__fini(&msg->result);
}

bool
nav2_msgs__action__NavigateThroughPoses_Result__are_equal(const nav2_msgs__action__NavigateThroughPoses_Result * lhs, const nav2_msgs__action__NavigateThroughPoses_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Result__copy(
  const nav2_msgs__action__NavigateThroughPoses_Result * input,
  nav2_msgs__action__NavigateThroughPoses_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // result
  if (!std_msgs__msg__Empty__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_Result *
nav2_msgs__action__NavigateThroughPoses_Result__create()
{
  nav2_msgs__action__NavigateThroughPoses_Result * msg = (nav2_msgs__action__NavigateThroughPoses_Result *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Result));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_Result));
  bool success = nav2_msgs__action__NavigateThroughPoses_Result__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_Result__destroy(nav2_msgs__action__NavigateThroughPoses_Result * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_Result__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__init(nav2_msgs__action__NavigateThroughPoses_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_Result * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_Result *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_Result));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_Result__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_Result__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_Result__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_Result__Sequence *
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_Result__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_Result__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Result__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_Result__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_Result__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_Result__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_Result__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Result__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_Result__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_Result);
    nav2_msgs__action__NavigateThroughPoses_Result * data =
      (nav2_msgs__action__NavigateThroughPoses_Result *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_Result__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_Result__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `current_pose`
// already included above
// #include "geometry_msgs/msg/detail/pose_stamped__functions.h"
// Member `navigation_time`
// Member `estimated_time_remaining`
#include "builtin_interfaces/msg/detail/duration__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_Feedback__init(nav2_msgs__action__NavigateThroughPoses_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // current_pose
  if (!geometry_msgs__msg__PoseStamped__init(&msg->current_pose)) {
    nav2_msgs__action__NavigateThroughPoses_Feedback__fini(msg);
    return false;
  }
  // navigation_time
  if (!builtin_interfaces__msg__Duration__init(&msg->navigation_time)) {
    nav2_msgs__action__NavigateThroughPoses_Feedback__fini(msg);
    return false;
  }
  // estimated_time_remaining
  if (!builtin_interfaces__msg__Duration__init(&msg->estimated_time_remaining)) {
    nav2_msgs__action__NavigateThroughPoses_Feedback__fini(msg);
    return false;
  }
  // number_of_recoveries
  // distance_remaining
  // number_of_poses_remaining
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_Feedback__fini(nav2_msgs__action__NavigateThroughPoses_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // current_pose
  geometry_msgs__msg__PoseStamped__fini(&msg->current_pose);
  // navigation_time
  builtin_interfaces__msg__Duration__fini(&msg->navigation_time);
  // estimated_time_remaining
  builtin_interfaces__msg__Duration__fini(&msg->estimated_time_remaining);
  // number_of_recoveries
  // distance_remaining
  // number_of_poses_remaining
}

bool
nav2_msgs__action__NavigateThroughPoses_Feedback__are_equal(const nav2_msgs__action__NavigateThroughPoses_Feedback * lhs, const nav2_msgs__action__NavigateThroughPoses_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // current_pose
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->current_pose), &(rhs->current_pose)))
  {
    return false;
  }
  // navigation_time
  if (!builtin_interfaces__msg__Duration__are_equal(
      &(lhs->navigation_time), &(rhs->navigation_time)))
  {
    return false;
  }
  // estimated_time_remaining
  if (!builtin_interfaces__msg__Duration__are_equal(
      &(lhs->estimated_time_remaining), &(rhs->estimated_time_remaining)))
  {
    return false;
  }
  // number_of_recoveries
  if (lhs->number_of_recoveries != rhs->number_of_recoveries) {
    return false;
  }
  // distance_remaining
  if (lhs->distance_remaining != rhs->distance_remaining) {
    return false;
  }
  // number_of_poses_remaining
  if (lhs->number_of_poses_remaining != rhs->number_of_poses_remaining) {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Feedback__copy(
  const nav2_msgs__action__NavigateThroughPoses_Feedback * input,
  nav2_msgs__action__NavigateThroughPoses_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // current_pose
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->current_pose), &(output->current_pose)))
  {
    return false;
  }
  // navigation_time
  if (!builtin_interfaces__msg__Duration__copy(
      &(input->navigation_time), &(output->navigation_time)))
  {
    return false;
  }
  // estimated_time_remaining
  if (!builtin_interfaces__msg__Duration__copy(
      &(input->estimated_time_remaining), &(output->estimated_time_remaining)))
  {
    return false;
  }
  // number_of_recoveries
  output->number_of_recoveries = input->number_of_recoveries;
  // distance_remaining
  output->distance_remaining = input->distance_remaining;
  // number_of_poses_remaining
  output->number_of_poses_remaining = input->number_of_poses_remaining;
  return true;
}

nav2_msgs__action__NavigateThroughPoses_Feedback *
nav2_msgs__action__NavigateThroughPoses_Feedback__create()
{
  nav2_msgs__action__NavigateThroughPoses_Feedback * msg = (nav2_msgs__action__NavigateThroughPoses_Feedback *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Feedback));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_Feedback));
  bool success = nav2_msgs__action__NavigateThroughPoses_Feedback__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_Feedback__destroy(nav2_msgs__action__NavigateThroughPoses_Feedback * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_Feedback__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__init(nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_Feedback * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_Feedback *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_Feedback));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_Feedback__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_Feedback__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence *
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_Feedback);
    nav2_msgs__action__NavigateThroughPoses_Feedback * data =
      (nav2_msgs__action__NavigateThroughPoses_Feedback *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_Feedback__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_Feedback__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "nav2_msgs/action/detail/navigate_through_poses__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__init(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!nav2_msgs__action__NavigateThroughPoses_Goal__init(&msg->goal)) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  nav2_msgs__action__NavigateThroughPoses_Goal__fini(&msg->goal);
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__are_equal(const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * lhs, const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!nav2_msgs__action__NavigateThroughPoses_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__copy(
  const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * input,
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!nav2_msgs__action__NavigateThroughPoses_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_SendGoal_Request *
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__create()
{
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * msg = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Request *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request));
  bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__destroy(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__init(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Request *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence *
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Request);
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Request * data =
      (nav2_msgs__action__NavigateThroughPoses_SendGoal_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__init(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__are_equal(const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * lhs, const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__copy(
  const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * input,
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_SendGoal_Response *
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__create()
{
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * msg = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Response *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response));
  bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__destroy(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__init(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Response *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence *
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_SendGoal_Response);
    nav2_msgs__action__NavigateThroughPoses_SendGoal_Response * data =
      (nav2_msgs__action__NavigateThroughPoses_SendGoal_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__init(nav2_msgs__action__NavigateThroughPoses_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(nav2_msgs__action__NavigateThroughPoses_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__are_equal(const nav2_msgs__action__NavigateThroughPoses_GetResult_Request * lhs, const nav2_msgs__action__NavigateThroughPoses_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__copy(
  const nav2_msgs__action__NavigateThroughPoses_GetResult_Request * input,
  nav2_msgs__action__NavigateThroughPoses_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_GetResult_Request *
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__create()
{
  nav2_msgs__action__NavigateThroughPoses_GetResult_Request * msg = (nav2_msgs__action__NavigateThroughPoses_GetResult_Request *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Request));
  bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__destroy(nav2_msgs__action__NavigateThroughPoses_GetResult_Request * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__init(nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_GetResult_Request * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_GetResult_Request *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence *
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Request);
    nav2_msgs__action__NavigateThroughPoses_GetResult_Request * data =
      (nav2_msgs__action__NavigateThroughPoses_GetResult_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_GetResult_Request__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "nav2_msgs/action/detail/navigate_through_poses__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__init(nav2_msgs__action__NavigateThroughPoses_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!nav2_msgs__action__NavigateThroughPoses_Result__init(&msg->result)) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(nav2_msgs__action__NavigateThroughPoses_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  nav2_msgs__action__NavigateThroughPoses_Result__fini(&msg->result);
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__are_equal(const nav2_msgs__action__NavigateThroughPoses_GetResult_Response * lhs, const nav2_msgs__action__NavigateThroughPoses_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!nav2_msgs__action__NavigateThroughPoses_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__copy(
  const nav2_msgs__action__NavigateThroughPoses_GetResult_Response * input,
  nav2_msgs__action__NavigateThroughPoses_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!nav2_msgs__action__NavigateThroughPoses_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_GetResult_Response *
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__create()
{
  nav2_msgs__action__NavigateThroughPoses_GetResult_Response * msg = (nav2_msgs__action__NavigateThroughPoses_GetResult_Response *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Response));
  bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__destroy(nav2_msgs__action__NavigateThroughPoses_GetResult_Response * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__init(nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_GetResult_Response * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_GetResult_Response *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence *
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_GetResult_Response);
    nav2_msgs__action__NavigateThroughPoses_GetResult_Response * data =
      (nav2_msgs__action__NavigateThroughPoses_GetResult_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_GetResult_Response__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "nav2_msgs/action/detail/navigate_through_poses__functions.h"

bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__init(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!nav2_msgs__action__NavigateThroughPoses_Feedback__init(&msg->feedback)) {
    nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  nav2_msgs__action__NavigateThroughPoses_Feedback__fini(&msg->feedback);
}

bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__are_equal(const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * lhs, const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!nav2_msgs__action__NavigateThroughPoses_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__copy(
  const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * input,
  nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!nav2_msgs__action__NavigateThroughPoses_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

nav2_msgs__action__NavigateThroughPoses_FeedbackMessage *
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__create()
{
  nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * msg = (nav2_msgs__action__NavigateThroughPoses_FeedbackMessage *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage));
  bool success = nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__destroy(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * msg)
{
  if (msg) {
    nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(msg);
  }
  free(msg);
}


bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__init(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * data = NULL;
  if (size) {
    data = (nav2_msgs__action__NavigateThroughPoses_FeedbackMessage *)calloc(size, sizeof(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(&data[i - 1]);
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
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__fini(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(&array->data[i]);
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

nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence *
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__create(size_t size)
{
  nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * array = (nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence *)malloc(sizeof(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__destroy(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * array)
{
  if (array) {
    nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__fini(array);
  }
  free(array);
}

bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__are_equal(const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * lhs, const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence__copy(
  const nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * input,
  nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(nav2_msgs__action__NavigateThroughPoses_FeedbackMessage);
    nav2_msgs__action__NavigateThroughPoses_FeedbackMessage * data =
      (nav2_msgs__action__NavigateThroughPoses_FeedbackMessage *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__fini(&data[i]);
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
    if (!nav2_msgs__action__NavigateThroughPoses_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
