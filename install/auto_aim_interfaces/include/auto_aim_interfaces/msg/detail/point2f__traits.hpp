// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from auto_aim_interfaces:msg/Point2f.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__TRAITS_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__TRAITS_HPP_

#include "auto_aim_interfaces/msg/detail/point2f__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const auto_aim_interfaces::msg::Point2f & msg,
  std::ostream & out, size_t indentation = 0)
{
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

inline std::string to_yaml(const auto_aim_interfaces::msg::Point2f & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<auto_aim_interfaces::msg::Point2f>()
{
  return "auto_aim_interfaces::msg::Point2f";
}

template<>
inline const char * name<auto_aim_interfaces::msg::Point2f>()
{
  return "auto_aim_interfaces/msg/Point2f";
}

template<>
struct has_fixed_size<auto_aim_interfaces::msg::Point2f>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<auto_aim_interfaces::msg::Point2f>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<auto_aim_interfaces::msg::Point2f>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__POINT2F__TRAITS_HPP_
