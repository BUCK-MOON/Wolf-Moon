// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from livox_ros_driver2:msg/CustomPoint.idl
// generated code does not contain a copyright notice

#ifndef LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_POINT__TRAITS_HPP_
#define LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_POINT__TRAITS_HPP_

#include "livox_ros_driver2/msg/detail/custom_point__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const livox_ros_driver2::msg::CustomPoint & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: offset_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "offset_time: ";
    value_to_yaml(msg.offset_time, out);
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

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: reflectivity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reflectivity: ";
    value_to_yaml(msg.reflectivity, out);
    out << "\n";
  }

  // member: tag
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tag: ";
    value_to_yaml(msg.tag, out);
    out << "\n";
  }

  // member: line
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "line: ";
    value_to_yaml(msg.line, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const livox_ros_driver2::msg::CustomPoint & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<livox_ros_driver2::msg::CustomPoint>()
{
  return "livox_ros_driver2::msg::CustomPoint";
}

template<>
inline const char * name<livox_ros_driver2::msg::CustomPoint>()
{
  return "livox_ros_driver2/msg/CustomPoint";
}

template<>
struct has_fixed_size<livox_ros_driver2::msg::CustomPoint>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<livox_ros_driver2::msg::CustomPoint>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<livox_ros_driver2::msg::CustomPoint>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_POINT__TRAITS_HPP_
