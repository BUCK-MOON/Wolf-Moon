// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from auto_aim_interfaces:msg/Gimbal.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__TRAITS_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__TRAITS_HPP_

#include "auto_aim_interfaces/msg/detail/gimbal__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'meas_point_cam'
// Member 'pred_point_cam'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const auto_aim_interfaces::msg::Gimbal & msg,
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

  // member: pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch: ";
    value_to_yaml(msg.pitch, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    value_to_yaml(msg.distance, out);
    out << "\n";
  }

  // member: is_switched
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_switched: ";
    value_to_yaml(msg.is_switched, out);
    out << "\n";
  }

  // member: is_target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_target: ";
    value_to_yaml(msg.is_target, out);
    out << "\n";
  }

  // member: is_spinning
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_spinning: ";
    value_to_yaml(msg.is_spinning, out);
    out << "\n";
  }

  // member: is_spinning_switched
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_spinning_switched: ";
    value_to_yaml(msg.is_spinning_switched, out);
    out << "\n";
  }

  // member: is_shooting
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_shooting: ";
    value_to_yaml(msg.is_shooting, out);
    out << "\n";
  }

  // member: is_prediction
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_prediction: ";
    value_to_yaml(msg.is_prediction, out);
    out << "\n";
  }

  // member: meas_point_cam
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "meas_point_cam:\n";
    to_yaml(msg.meas_point_cam, out, indentation + 2);
  }

  // member: pred_point_cam
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pred_point_cam:\n";
    to_yaml(msg.pred_point_cam, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const auto_aim_interfaces::msg::Gimbal & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<auto_aim_interfaces::msg::Gimbal>()
{
  return "auto_aim_interfaces::msg::Gimbal";
}

template<>
inline const char * name<auto_aim_interfaces::msg::Gimbal>()
{
  return "auto_aim_interfaces/msg/Gimbal";
}

template<>
struct has_fixed_size<auto_aim_interfaces::msg::Gimbal>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<auto_aim_interfaces::msg::Gimbal>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<auto_aim_interfaces::msg::Gimbal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__TRAITS_HPP_
