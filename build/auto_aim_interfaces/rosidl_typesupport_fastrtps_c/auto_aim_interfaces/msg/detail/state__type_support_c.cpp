// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/state__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "auto_aim_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "auto_aim_interfaces/msg/detail/state__struct.h"
#include "auto_aim_interfaces/msg/detail/state__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "auto_aim_interfaces/msg/detail/point2f__functions.h"  // angle, calculate, center, predict
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
size_t get_serialized_size_auto_aim_interfaces__msg__Point2f(
  const void * untyped_ros_message,
  size_t current_alignment);

size_t max_serialized_size_auto_aim_interfaces__msg__Point2f(
  bool & full_bounded,
  size_t current_alignment);

const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f)();
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_auto_aim_interfaces
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_auto_aim_interfaces
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_auto_aim_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _State__ros_msg_type = auto_aim_interfaces__msg__State;

static bool _State__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _State__ros_msg_type * ros_message = static_cast<const _State__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: mode
  {
    cdr << ros_message->mode;
  }

  // Field name: center
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    size_t size = 4;
    auto array_ptr = ros_message->center;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_serialize(
          &array_ptr[i], cdr))
      {
        return false;
      }
    }
  }

  // Field name: predict
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->predict, cdr))
    {
      return false;
    }
  }

  // Field name: calculate
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->calculate, cdr))
    {
      return false;
    }
  }

  // Field name: angle
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->angle, cdr))
    {
      return false;
    }
  }

  // Field name: state
  {
    size_t size = 9;
    auto array_ptr = ros_message->state;
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _State__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _State__ros_msg_type * ros_message = static_cast<_State__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: mode
  {
    cdr >> ros_message->mode;
  }

  // Field name: center
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    size_t size = 4;
    auto array_ptr = ros_message->center;
    for (size_t i = 0; i < size; ++i) {
      if (!callbacks->cdr_deserialize(
          cdr, &array_ptr[i]))
      {
        return false;
      }
    }
  }

  // Field name: predict
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->predict))
    {
      return false;
    }
  }

  // Field name: calculate
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->calculate))
    {
      return false;
    }
  }

  // Field name: angle
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, Point2f
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->angle))
    {
      return false;
    }
  }

  // Field name: state
  {
    size_t size = 9;
    auto array_ptr = ros_message->state;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_auto_aim_interfaces
size_t get_serialized_size_auto_aim_interfaces__msg__State(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _State__ros_msg_type * ros_message = static_cast<const _State__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name mode
  {
    size_t item_size = sizeof(ros_message->mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name center
  {
    size_t array_size = 4;
    auto array_ptr = ros_message->center;

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += get_serialized_size_auto_aim_interfaces__msg__Point2f(
        &array_ptr[index], current_alignment);
    }
  }
  // field.name predict

  current_alignment += get_serialized_size_auto_aim_interfaces__msg__Point2f(
    &(ros_message->predict), current_alignment);
  // field.name calculate

  current_alignment += get_serialized_size_auto_aim_interfaces__msg__Point2f(
    &(ros_message->calculate), current_alignment);
  // field.name angle

  current_alignment += get_serialized_size_auto_aim_interfaces__msg__Point2f(
    &(ros_message->angle), current_alignment);
  // field.name state
  {
    size_t array_size = 9;
    auto array_ptr = ros_message->state;
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _State__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_auto_aim_interfaces__msg__State(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_auto_aim_interfaces
size_t max_serialized_size_auto_aim_interfaces__msg__State(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: mode
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: center
  {
    size_t array_size = 4;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_auto_aim_interfaces__msg__Point2f(
        full_bounded, current_alignment);
    }
  }
  // member: predict
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_auto_aim_interfaces__msg__Point2f(
        full_bounded, current_alignment);
    }
  }
  // member: calculate
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_auto_aim_interfaces__msg__Point2f(
        full_bounded, current_alignment);
    }
  }
  // member: angle
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_auto_aim_interfaces__msg__Point2f(
        full_bounded, current_alignment);
    }
  }
  // member: state
  {
    size_t array_size = 9;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _State__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_auto_aim_interfaces__msg__State(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_State = {
  "auto_aim_interfaces::msg",
  "State",
  _State__cdr_serialize,
  _State__cdr_deserialize,
  _State__get_serialized_size,
  _State__max_serialized_size
};

static rosidl_message_type_support_t _State__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_State,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, auto_aim_interfaces, msg, State)() {
  return &_State__type_support;
}

#if defined(__cplusplus)
}
#endif
