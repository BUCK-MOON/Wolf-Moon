// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from auto_aim_interfaces:msg/Point2f.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__STRUCT_H_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Point2f in the package auto_aim_interfaces.
typedef struct auto_aim_interfaces__msg__Point2f
{
  float x;
  float y;
} auto_aim_interfaces__msg__Point2f;

// Struct for a sequence of auto_aim_interfaces__msg__Point2f.
typedef struct auto_aim_interfaces__msg__Point2f__Sequence
{
  auto_aim_interfaces__msg__Point2f * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} auto_aim_interfaces__msg__Point2f__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__STRUCT_H_
