// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from nav2_msgs:msg/CostmapFilterInfo.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__STRUCT_H_
#define NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'filter_mask_topic'
#include "rosidl_runtime_c/string.h"

// Struct defined in msg/CostmapFilterInfo in the package nav2_msgs.
typedef struct nav2_msgs__msg__CostmapFilterInfo
{
  std_msgs__msg__Header header;
  uint8_t type;
  rosidl_runtime_c__String filter_mask_topic;
  float base;
  float multiplier;
} nav2_msgs__msg__CostmapFilterInfo;

// Struct for a sequence of nav2_msgs__msg__CostmapFilterInfo.
typedef struct nav2_msgs__msg__CostmapFilterInfo__Sequence
{
  nav2_msgs__msg__CostmapFilterInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} nav2_msgs__msg__CostmapFilterInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__STRUCT_H_
