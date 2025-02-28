// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from auto_aim_interfaces:msg/Uart.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__UART__TRAITS_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__UART__TRAITS_HPP_

#include "auto_aim_interfaces/msg/detail/uart__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const auto_aim_interfaces::msg::Uart & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_yaml(msg.header, out, indentation + 2);
  }

  // member: remain_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remain_time: ";
    value_to_yaml(msg.remain_time, out);
    out << "\n";
  }

  // member: game_stage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "game_stage: ";
    value_to_yaml(msg.game_stage, out);
    out << "\n";
  }

  // member: outpost_hp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "outpost_hp: ";
    value_to_yaml(msg.outpost_hp, out);
    out << "\n";
  }

  // member: sentry_hp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sentry_hp: ";
    value_to_yaml(msg.sentry_hp, out);
    out << "\n";
  }

  // member: commd_keyboard
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "commd_keyboard: ";
    value_to_yaml(msg.commd_keyboard, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    value_to_yaml(msg.y, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const auto_aim_interfaces::msg::Uart & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<auto_aim_interfaces::msg::Uart>()
{
  return "auto_aim_interfaces::msg::Uart";
}

template<>
inline const char * name<auto_aim_interfaces::msg::Uart>()
{
  return "auto_aim_interfaces/msg/Uart";
}

template<>
struct has_fixed_size<auto_aim_interfaces::msg::Uart>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<auto_aim_interfaces::msg::Uart>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<auto_aim_interfaces::msg::Uart>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__UART__TRAITS_HPP_
