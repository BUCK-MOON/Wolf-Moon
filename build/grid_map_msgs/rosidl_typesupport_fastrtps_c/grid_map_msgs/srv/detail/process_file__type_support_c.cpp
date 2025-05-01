// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from grid_map_msgs:srv/ProcessFile.idl
// generated code does not contain a copyright notice
#include "grid_map_msgs/srv/detail/process_file__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "grid_map_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "grid_map_msgs/srv/detail/process_file__struct.h"
#include "grid_map_msgs/srv/detail/process_file__functions.h"
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

#include "rosidl_runtime_c/string.h"  // file_path, topic_name
#include "rosidl_runtime_c/string_functions.h"  // file_path, topic_name

// forward declare type support functions


using _ProcessFile_Request__ros_msg_type = grid_map_msgs__srv__ProcessFile_Request;

static bool _ProcessFile_Request__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ProcessFile_Request__ros_msg_type * ros_message = static_cast<const _ProcessFile_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: file_path
  {
    const rosidl_runtime_c__String * str = &ros_message->file_path;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: topic_name
  {
    const rosidl_runtime_c__String * str = &ros_message->topic_name;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  return true;
}

static bool _ProcessFile_Request__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ProcessFile_Request__ros_msg_type * ros_message = static_cast<_ProcessFile_Request__ros_msg_type *>(untyped_ros_message);
  // Field name: file_path
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->file_path.data) {
      rosidl_runtime_c__String__init(&ros_message->file_path);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->file_path,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'file_path'\n");
      return false;
    }
  }

  // Field name: topic_name
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->topic_name.data) {
      rosidl_runtime_c__String__init(&ros_message->topic_name);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->topic_name,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'topic_name'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_grid_map_msgs
size_t get_serialized_size_grid_map_msgs__srv__ProcessFile_Request(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ProcessFile_Request__ros_msg_type * ros_message = static_cast<const _ProcessFile_Request__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name file_path
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->file_path.size + 1);
  // field.name topic_name
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->topic_name.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _ProcessFile_Request__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_grid_map_msgs__srv__ProcessFile_Request(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_grid_map_msgs
size_t max_serialized_size_grid_map_msgs__srv__ProcessFile_Request(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: file_path
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: topic_name
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  return current_alignment - initial_alignment;
}

static size_t _ProcessFile_Request__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_grid_map_msgs__srv__ProcessFile_Request(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_ProcessFile_Request = {
  "grid_map_msgs::srv",
  "ProcessFile_Request",
  _ProcessFile_Request__cdr_serialize,
  _ProcessFile_Request__cdr_deserialize,
  _ProcessFile_Request__get_serialized_size,
  _ProcessFile_Request__max_serialized_size
};

static rosidl_message_type_support_t _ProcessFile_Request__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ProcessFile_Request,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, grid_map_msgs, srv, ProcessFile_Request)() {
  return &_ProcessFile_Request__type_support;
}

#if defined(__cplusplus)
}
#endif

// already included above
// #include <cassert>
// already included above
// #include <limits>
// already included above
// #include <string>
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
// already included above
// #include "grid_map_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
// already included above
// #include "grid_map_msgs/srv/detail/process_file__struct.h"
// already included above
// #include "grid_map_msgs/srv/detail/process_file__functions.h"
// already included above
// #include "fastcdr/Cdr.h"

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


// forward declare type support functions


using _ProcessFile_Response__ros_msg_type = grid_map_msgs__srv__ProcessFile_Response;

static bool _ProcessFile_Response__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _ProcessFile_Response__ros_msg_type * ros_message = static_cast<const _ProcessFile_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    cdr << (ros_message->success ? true : false);
  }

  return true;
}

static bool _ProcessFile_Response__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _ProcessFile_Response__ros_msg_type * ros_message = static_cast<_ProcessFile_Response__ros_msg_type *>(untyped_ros_message);
  // Field name: success
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->success = tmp ? true : false;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_grid_map_msgs
size_t get_serialized_size_grid_map_msgs__srv__ProcessFile_Response(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _ProcessFile_Response__ros_msg_type * ros_message = static_cast<const _ProcessFile_Response__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name success
  {
    size_t item_size = sizeof(ros_message->success);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _ProcessFile_Response__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_grid_map_msgs__srv__ProcessFile_Response(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_grid_map_msgs
size_t max_serialized_size_grid_map_msgs__srv__ProcessFile_Response(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: success
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _ProcessFile_Response__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_grid_map_msgs__srv__ProcessFile_Response(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_ProcessFile_Response = {
  "grid_map_msgs::srv",
  "ProcessFile_Response",
  _ProcessFile_Response__cdr_serialize,
  _ProcessFile_Response__cdr_deserialize,
  _ProcessFile_Response__get_serialized_size,
  _ProcessFile_Response__max_serialized_size
};

static rosidl_message_type_support_t _ProcessFile_Response__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_ProcessFile_Response,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, grid_map_msgs, srv, ProcessFile_Response)() {
  return &_ProcessFile_Response__type_support;
}

#if defined(__cplusplus)
}
#endif

#include "rosidl_typesupport_fastrtps_cpp/service_type_support.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "rosidl_typesupport_fastrtps_c/identifier.h"
// already included above
// #include "grid_map_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "grid_map_msgs/srv/process_file.h"

#if defined(__cplusplus)
extern "C"
{
#endif

static service_type_support_callbacks_t ProcessFile__callbacks = {
  "grid_map_msgs::srv",
  "ProcessFile",
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, grid_map_msgs, srv, ProcessFile_Request)(),
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, grid_map_msgs, srv, ProcessFile_Response)(),
};

static rosidl_service_type_support_t ProcessFile__handle = {
  rosidl_typesupport_fastrtps_c__identifier,
  &ProcessFile__callbacks,
  get_service_typesupport_handle_function,
};

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, grid_map_msgs, srv, ProcessFile)() {
  return &ProcessFile__handle;
}

#if defined(__cplusplus)
}
#endif
