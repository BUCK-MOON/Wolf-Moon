// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice
#include "auto_aim_interfaces/msg/detail/state__rosidl_typesupport_fastrtps_cpp.hpp"
#include "auto_aim_interfaces/msg/detail/state__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs

namespace auto_aim_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const auto_aim_interfaces::msg::Point2f &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  auto_aim_interfaces::msg::Point2f &);
size_t get_serialized_size(
  const auto_aim_interfaces::msg::Point2f &,
  size_t current_alignment);
size_t
max_serialized_size_Point2f(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace auto_aim_interfaces

namespace auto_aim_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const auto_aim_interfaces::msg::Point2f &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  auto_aim_interfaces::msg::Point2f &);
size_t get_serialized_size(
  const auto_aim_interfaces::msg::Point2f &,
  size_t current_alignment);
size_t
max_serialized_size_Point2f(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace auto_aim_interfaces

namespace auto_aim_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const auto_aim_interfaces::msg::Point2f &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  auto_aim_interfaces::msg::Point2f &);
size_t get_serialized_size(
  const auto_aim_interfaces::msg::Point2f &,
  size_t current_alignment);
size_t
max_serialized_size_Point2f(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace auto_aim_interfaces

namespace auto_aim_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const auto_aim_interfaces::msg::Point2f &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  auto_aim_interfaces::msg::Point2f &);
size_t get_serialized_size(
  const auto_aim_interfaces::msg::Point2f &,
  size_t current_alignment);
size_t
max_serialized_size_Point2f(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace auto_aim_interfaces


namespace auto_aim_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_auto_aim_interfaces
cdr_serialize(
  const auto_aim_interfaces::msg::State & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: mode
  cdr << ros_message.mode;
  // Member: center
  {
    for (size_t i = 0; i < 4; i++) {
      auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.center[i],
        cdr);
    }
  }
  // Member: predict
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.predict,
    cdr);
  // Member: calculate
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.calculate,
    cdr);
  // Member: angle
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.angle,
    cdr);
  // Member: state
  {
    cdr << ros_message.state;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_auto_aim_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  auto_aim_interfaces::msg::State & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: mode
  cdr >> ros_message.mode;

  // Member: center
  {
    for (size_t i = 0; i < 4; i++) {
      auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr,
        ros_message.center[i]);
    }
  }

  // Member: predict
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.predict);

  // Member: calculate
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.calculate);

  // Member: angle
  auto_aim_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.angle);

  // Member: state
  {
    cdr >> ros_message.state;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_auto_aim_interfaces
get_serialized_size(
  const auto_aim_interfaces::msg::State & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: mode
  {
    size_t item_size = sizeof(ros_message.mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: center
  {
    size_t array_size = 4;

    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        auto_aim_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.center[index], current_alignment);
    }
  }
  // Member: predict

  current_alignment +=
    auto_aim_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.predict, current_alignment);
  // Member: calculate

  current_alignment +=
    auto_aim_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.calculate, current_alignment);
  // Member: angle

  current_alignment +=
    auto_aim_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.angle, current_alignment);
  // Member: state
  {
    size_t array_size = 9;
    size_t item_size = sizeof(ros_message.state[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_auto_aim_interfaces
max_serialized_size_State(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        full_bounded, current_alignment);
    }
  }

  // Member: mode
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: center
  {
    size_t array_size = 4;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        auto_aim_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Point2f(
        full_bounded, current_alignment);
    }
  }

  // Member: predict
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        auto_aim_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Point2f(
        full_bounded, current_alignment);
    }
  }

  // Member: calculate
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        auto_aim_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Point2f(
        full_bounded, current_alignment);
    }
  }

  // Member: angle
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        auto_aim_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Point2f(
        full_bounded, current_alignment);
    }
  }

  // Member: state
  {
    size_t array_size = 9;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static bool _State__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const auto_aim_interfaces::msg::State *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _State__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<auto_aim_interfaces::msg::State *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _State__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const auto_aim_interfaces::msg::State *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _State__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_State(full_bounded, 0);
}

static message_type_support_callbacks_t _State__callbacks = {
  "auto_aim_interfaces::msg",
  "State",
  _State__cdr_serialize,
  _State__cdr_deserialize,
  _State__get_serialized_size,
  _State__max_serialized_size
};

static rosidl_message_type_support_t _State__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_State__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace auto_aim_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_auto_aim_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<auto_aim_interfaces::msg::State>()
{
  return &auto_aim_interfaces::msg::typesupport_fastrtps_cpp::_State__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, auto_aim_interfaces, msg, State)() {
  return &auto_aim_interfaces::msg::typesupport_fastrtps_cpp::_State__handle;
}

#ifdef __cplusplus
}
#endif
