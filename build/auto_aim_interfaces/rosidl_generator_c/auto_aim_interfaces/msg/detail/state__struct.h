// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_H_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_H_

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
// Member 'center'
// Member 'predict'
// Member 'calculate'
// Member 'angle'
#include "auto_aim_interfaces/msg/detail/point2f__struct.h"

// Struct defined in msg/State in the package auto_aim_interfaces.
typedef struct auto_aim_interfaces__msg__State
{
  std_msgs__msg__Header header;
  uint8_t mode;
  auto_aim_interfaces__msg__Point2f center[4];
  auto_aim_interfaces__msg__Point2f predict;
  auto_aim_interfaces__msg__Point2f calculate;
  auto_aim_interfaces__msg__Point2f angle;
  double state[9];
} auto_aim_interfaces__msg__State;

// Struct for a sequence of auto_aim_interfaces__msg__State.
typedef struct auto_aim_interfaces__msg__State__Sequence
{
  auto_aim_interfaces__msg__State * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} auto_aim_interfaces__msg__State__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_H_
