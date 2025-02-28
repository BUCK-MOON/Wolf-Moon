// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from livox_ros_driver2:msg/CustomMsg.idl
// generated code does not contain a copyright notice

#ifndef LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_MSG__TRAITS_HPP_
#define LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_MSG__TRAITS_HPP_

#include "livox_ros_driver2/msg/detail/custom_msg__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'points'
#include "livox_ros_driver2/msg/detail/custom_point__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const livox_ros_driver2::msg::CustomMsg & msg,
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

  // member: timebase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timebase: ";
    value_to_yaml(msg.timebase, out);
    out << "\n";
  }

  // member: point_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "point_num: ";
    value_to_yaml(msg.point_num, out);
    out << "\n";
  }

  // member: lidar_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lidar_id: ";
    value_to_yaml(msg.lidar_id, out);
    out << "\n";
  }

  // member: rsvd
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.rsvd.size() == 0) {
      out << "rsvd: []\n";
    } else {
      out << "rsvd:\n";
      for (auto item : msg.rsvd) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: points
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.points.size() == 0) {
      out << "points: []\n";
    } else {
      out << "points:\n";
      for (auto item : msg.points) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const livox_ros_driver2::msg::CustomMsg & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<livox_ros_driver2::msg::CustomMsg>()
{
  return "livox_ros_driver2::msg::CustomMsg";
}

template<>
inline const char * name<livox_ros_driver2::msg::CustomMsg>()
{
  return "livox_ros_driver2/msg/CustomMsg";
}

template<>
struct has_fixed_size<livox_ros_driver2::msg::CustomMsg>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<livox_ros_driver2::msg::CustomMsg>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<livox_ros_driver2::msg::CustomMsg>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LIVOX_ROS_DRIVER2__MSG__DETAIL__CUSTOM_MSG__TRAITS_HPP_
