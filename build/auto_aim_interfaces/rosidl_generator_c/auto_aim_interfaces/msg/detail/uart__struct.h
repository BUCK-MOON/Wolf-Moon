// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from auto_aim_interfaces:msg/Uart.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_H_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_H_

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

// Struct defined in msg/Uart in the package auto_aim_interfaces.
typedef struct auto_aim_interfaces__msg__Uart
{
  std_msgs__msg__Header header;
  uint16_t remain_time;
  uint8_t game_stage;
  uint16_t outpost_hp;
  uint16_t sentry_hp;
  uint8_t commd_keyboard;
  uint8_t x;
  uint8_t y;
} auto_aim_interfaces__msg__Uart;

// Struct for a sequence of auto_aim_interfaces__msg__Uart.
typedef struct auto_aim_interfaces__msg__Uart__Sequence
{
  auto_aim_interfaces__msg__Uart * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} auto_aim_interfaces__msg__Uart__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_H_
