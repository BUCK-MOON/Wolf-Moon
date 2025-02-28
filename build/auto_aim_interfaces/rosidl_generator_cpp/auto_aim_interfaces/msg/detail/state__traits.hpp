// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__TRAITS_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__TRAITS_HPP_

#include "auto_aim_interfaces/msg/detail/state__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'center'
// Member 'predict'
// Member 'calculate'
// Member 'angle'
#include "auto_aim_interfaces/msg/detail/point2f__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const auto_aim_interfaces::msg::State & msg,
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

  // member: mode
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "mode: ";
    value_to_yaml(msg.mode, out);
    out << "\n";
  }

  // member: center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.center.size() == 0) {
      out << "center: []\n";
    } else {
      out << "center:\n";
      for (auto item : msg.center) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: predict
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "predict:\n";
    to_yaml(msg.predict, out, indentation + 2);
  }

  // member: calculate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "calculate:\n";
    to_yaml(msg.calculate, out, indentation + 2);
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle:\n";
    to_yaml(msg.angle, out, indentation + 2);
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.state.size() == 0) {
      out << "state: []\n";
    } else {
      out << "state:\n";
      for (auto item : msg.state) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const auto_aim_interfaces::msg::State & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<auto_aim_interfaces::msg::State>()
{
  return "auto_aim_interfaces::msg::State";
}

template<>
inline const char * name<auto_aim_interfaces::msg::State>()
{
  return "auto_aim_interfaces/msg/State";
}

template<>
struct has_fixed_size<auto_aim_interfaces::msg::State>
  : std::integral_constant<bool, has_fixed_size<auto_aim_interfaces::msg::Point2f>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<auto_aim_interfaces::msg::State>
  : std::integral_constant<bool, has_bounded_size<auto_aim_interfaces::msg::Point2f>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<auto_aim_interfaces::msg::State>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__TRAITS_HPP_
