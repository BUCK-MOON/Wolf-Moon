// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from auto_aim_interfaces:msg/Gimbal.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_H_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_H_

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
// Member 'meas_point_cam'
// Member 'pred_point_cam'
#include "geometry_msgs/msg/detail/point__struct.h"

// Struct defined in msg/Gimbal in the package auto_aim_interfaces.
typedef struct auto_aim_interfaces__msg__Gimbal
{
  std_msgs__msg__Header header;
  float pitch;
  float yaw;
  float distance;
  bool is_switched;
  bool is_target;
  bool is_spinning;
  bool is_spinning_switched;
  bool is_shooting;
  bool is_prediction;
  geometry_msgs__msg__Point meas_point_cam;
  geometry_msgs__msg__Point pred_point_cam;
} auto_aim_interfaces__msg__Gimbal;

// Struct for a sequence of auto_aim_interfaces__msg__Gimbal.
typedef struct auto_aim_interfaces__msg__Gimbal__Sequence
{
  auto_aim_interfaces__msg__Gimbal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} auto_aim_interfaces__msg__Gimbal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_H_
