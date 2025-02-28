// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from auto_aim_interfaces:msg/Armor.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_

#include "auto_aim_interfaces/msg/detail/armor__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const auto_aim_interfaces::msg::Armor & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: number
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "number: ";
    value_to_yaml(msg.number, out);
    out << "\n";
  }

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: distance_to_image_center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_to_image_center: ";
    value_to_yaml(msg.distance_to_image_center, out);
    out << "\n";
  }

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_yaml(msg.pose, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const auto_aim_interfaces::msg::Armor & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<auto_aim_interfaces::msg::Armor>()
{
  return "auto_aim_interfaces::msg::Armor";
}

template<>
inline const char * name<auto_aim_interfaces::msg::Armor>()
{
  return "auto_aim_interfaces/msg/Armor";
}

template<>
struct has_fixed_size<auto_aim_interfaces::msg::Armor>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<auto_aim_interfaces::msg::Armor>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<auto_aim_interfaces::msg::Armor>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__ARMOR__TRAITS_HPP_
