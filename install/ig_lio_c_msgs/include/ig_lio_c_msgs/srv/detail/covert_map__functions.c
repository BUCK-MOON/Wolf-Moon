// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from ig_lio_c_msgs:srv/CovertMap.idl
// generated code does not contain a copyright notice
#include "ig_lio_c_msgs/srv/detail/covert_map__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Include directives for member types
// Member `pcd_path`
// Member `map_file_name`
// Member `image_format`
// Member `map_mode`
#include "rosidl_runtime_c/string_functions.h"

bool
ig_lio_c_msgs__srv__CovertMap_Request__init(ig_lio_c_msgs__srv__CovertMap_Request * msg)
{
  if (!msg) {
    return false;
  }
  // pcd_path
  if (!rosidl_runtime_c__String__init(&msg->pcd_path)) {
    ig_lio_c_msgs__srv__CovertMap_Request__fini(msg);
    return false;
  }
  // map_file_name
  if (!rosidl_runtime_c__String__init(&msg->map_file_name)) {
    ig_lio_c_msgs__srv__CovertMap_Request__fini(msg);
    return false;
  }
  // image_format
  if (!rosidl_runtime_c__String__init(&msg->image_format)) {
    ig_lio_c_msgs__srv__CovertMap_Request__fini(msg);
    return false;
  }
  // map_mode
  if (!rosidl_runtime_c__String__init(&msg->map_mode)) {
    ig_lio_c_msgs__srv__CovertMap_Request__fini(msg);
    return false;
  }
  // free_thresh
  // occupied_thresh
  return true;
}

void
ig_lio_c_msgs__srv__CovertMap_Request__fini(ig_lio_c_msgs__srv__CovertMap_Request * msg)
{
  if (!msg) {
    return;
  }
  // pcd_path
  rosidl_runtime_c__String__fini(&msg->pcd_path);
  // map_file_name
  rosidl_runtime_c__String__fini(&msg->map_file_name);
  // image_format
  rosidl_runtime_c__String__fini(&msg->image_format);
  // map_mode
  rosidl_runtime_c__String__fini(&msg->map_mode);
  // free_thresh
  // occupied_thresh
}

bool
ig_lio_c_msgs__srv__CovertMap_Request__are_equal(const ig_lio_c_msgs__srv__CovertMap_Request * lhs, const ig_lio_c_msgs__srv__CovertMap_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // pcd_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->pcd_path), &(rhs->pcd_path)))
  {
    return false;
  }
  // map_file_name
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_file_name), &(rhs->map_file_name)))
  {
    return false;
  }
  // image_format
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->image_format), &(rhs->image_format)))
  {
    return false;
  }
  // map_mode
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->map_mode), &(rhs->map_mode)))
  {
    return false;
  }
  // free_thresh
  if (lhs->free_thresh != rhs->free_thresh) {
    return false;
  }
  // occupied_thresh
  if (lhs->occupied_thresh != rhs->occupied_thresh) {
    return false;
  }
  return true;
}

bool
ig_lio_c_msgs__srv__CovertMap_Request__copy(
  const ig_lio_c_msgs__srv__CovertMap_Request * input,
  ig_lio_c_msgs__srv__CovertMap_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // pcd_path
  if (!rosidl_runtime_c__String__copy(
      &(input->pcd_path), &(output->pcd_path)))
  {
    return false;
  }
  // map_file_name
  if (!rosidl_runtime_c__String__copy(
      &(input->map_file_name), &(output->map_file_name)))
  {
    return false;
  }
  // image_format
  if (!rosidl_runtime_c__String__copy(
      &(input->image_format), &(output->image_format)))
  {
    return false;
  }
  // map_mode
  if (!rosidl_runtime_c__String__copy(
      &(input->map_mode), &(output->map_mode)))
  {
    return false;
  }
  // free_thresh
  output->free_thresh = input->free_thresh;
  // occupied_thresh
  output->occupied_thresh = input->occupied_thresh;
  return true;
}

ig_lio_c_msgs__srv__CovertMap_Request *
ig_lio_c_msgs__srv__CovertMap_Request__create()
{
  ig_lio_c_msgs__srv__CovertMap_Request * msg = (ig_lio_c_msgs__srv__CovertMap_Request *)malloc(sizeof(ig_lio_c_msgs__srv__CovertMap_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ig_lio_c_msgs__srv__CovertMap_Request));
  bool success = ig_lio_c_msgs__srv__CovertMap_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ig_lio_c_msgs__srv__CovertMap_Request__destroy(ig_lio_c_msgs__srv__CovertMap_Request * msg)
{
  if (msg) {
    ig_lio_c_msgs__srv__CovertMap_Request__fini(msg);
  }
  free(msg);
}


bool
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__init(ig_lio_c_msgs__srv__CovertMap_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ig_lio_c_msgs__srv__CovertMap_Request * data = NULL;
  if (size) {
    data = (ig_lio_c_msgs__srv__CovertMap_Request *)calloc(size, sizeof(ig_lio_c_msgs__srv__CovertMap_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ig_lio_c_msgs__srv__CovertMap_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ig_lio_c_msgs__srv__CovertMap_Request__fini(&data[i - 1]);
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
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__fini(ig_lio_c_msgs__srv__CovertMap_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ig_lio_c_msgs__srv__CovertMap_Request__fini(&array->data[i]);
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

ig_lio_c_msgs__srv__CovertMap_Request__Sequence *
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__create(size_t size)
{
  ig_lio_c_msgs__srv__CovertMap_Request__Sequence * array = (ig_lio_c_msgs__srv__CovertMap_Request__Sequence *)malloc(sizeof(ig_lio_c_msgs__srv__CovertMap_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ig_lio_c_msgs__srv__CovertMap_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__destroy(ig_lio_c_msgs__srv__CovertMap_Request__Sequence * array)
{
  if (array) {
    ig_lio_c_msgs__srv__CovertMap_Request__Sequence__fini(array);
  }
  free(array);
}

bool
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__are_equal(const ig_lio_c_msgs__srv__CovertMap_Request__Sequence * lhs, const ig_lio_c_msgs__srv__CovertMap_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ig_lio_c_msgs__srv__CovertMap_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ig_lio_c_msgs__srv__CovertMap_Request__Sequence__copy(
  const ig_lio_c_msgs__srv__CovertMap_Request__Sequence * input,
  ig_lio_c_msgs__srv__CovertMap_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ig_lio_c_msgs__srv__CovertMap_Request);
    ig_lio_c_msgs__srv__CovertMap_Request * data =
      (ig_lio_c_msgs__srv__CovertMap_Request *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ig_lio_c_msgs__srv__CovertMap_Request__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          ig_lio_c_msgs__srv__CovertMap_Request__fini(&data[i]);
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
    if (!ig_lio_c_msgs__srv__CovertMap_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
ig_lio_c_msgs__srv__CovertMap_Response__init(ig_lio_c_msgs__srv__CovertMap_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    ig_lio_c_msgs__srv__CovertMap_Response__fini(msg);
    return false;
  }
  return true;
}

void
ig_lio_c_msgs__srv__CovertMap_Response__fini(ig_lio_c_msgs__srv__CovertMap_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
ig_lio_c_msgs__srv__CovertMap_Response__are_equal(const ig_lio_c_msgs__srv__CovertMap_Response * lhs, const ig_lio_c_msgs__srv__CovertMap_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
ig_lio_c_msgs__srv__CovertMap_Response__copy(
  const ig_lio_c_msgs__srv__CovertMap_Response * input,
  ig_lio_c_msgs__srv__CovertMap_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

ig_lio_c_msgs__srv__CovertMap_Response *
ig_lio_c_msgs__srv__CovertMap_Response__create()
{
  ig_lio_c_msgs__srv__CovertMap_Response * msg = (ig_lio_c_msgs__srv__CovertMap_Response *)malloc(sizeof(ig_lio_c_msgs__srv__CovertMap_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(ig_lio_c_msgs__srv__CovertMap_Response));
  bool success = ig_lio_c_msgs__srv__CovertMap_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
ig_lio_c_msgs__srv__CovertMap_Response__destroy(ig_lio_c_msgs__srv__CovertMap_Response * msg)
{
  if (msg) {
    ig_lio_c_msgs__srv__CovertMap_Response__fini(msg);
  }
  free(msg);
}


bool
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__init(ig_lio_c_msgs__srv__CovertMap_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  ig_lio_c_msgs__srv__CovertMap_Response * data = NULL;
  if (size) {
    data = (ig_lio_c_msgs__srv__CovertMap_Response *)calloc(size, sizeof(ig_lio_c_msgs__srv__CovertMap_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = ig_lio_c_msgs__srv__CovertMap_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        ig_lio_c_msgs__srv__CovertMap_Response__fini(&data[i - 1]);
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
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__fini(ig_lio_c_msgs__srv__CovertMap_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      ig_lio_c_msgs__srv__CovertMap_Response__fini(&array->data[i]);
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

ig_lio_c_msgs__srv__CovertMap_Response__Sequence *
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__create(size_t size)
{
  ig_lio_c_msgs__srv__CovertMap_Response__Sequence * array = (ig_lio_c_msgs__srv__CovertMap_Response__Sequence *)malloc(sizeof(ig_lio_c_msgs__srv__CovertMap_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = ig_lio_c_msgs__srv__CovertMap_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__destroy(ig_lio_c_msgs__srv__CovertMap_Response__Sequence * array)
{
  if (array) {
    ig_lio_c_msgs__srv__CovertMap_Response__Sequence__fini(array);
  }
  free(array);
}

bool
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__are_equal(const ig_lio_c_msgs__srv__CovertMap_Response__Sequence * lhs, const ig_lio_c_msgs__srv__CovertMap_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!ig_lio_c_msgs__srv__CovertMap_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
ig_lio_c_msgs__srv__CovertMap_Response__Sequence__copy(
  const ig_lio_c_msgs__srv__CovertMap_Response__Sequence * input,
  ig_lio_c_msgs__srv__CovertMap_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(ig_lio_c_msgs__srv__CovertMap_Response);
    ig_lio_c_msgs__srv__CovertMap_Response * data =
      (ig_lio_c_msgs__srv__CovertMap_Response *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!ig_lio_c_msgs__srv__CovertMap_Response__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          ig_lio_c_msgs__srv__CovertMap_Response__fini(&data[i]);
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
    if (!ig_lio_c_msgs__srv__CovertMap_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
