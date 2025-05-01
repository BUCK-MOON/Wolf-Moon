// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:msg/VoxelGrid.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__VOXEL_GRID__TRAITS_HPP_
#define NAV2_MSGS__MSG__DETAIL__VOXEL_GRID__TRAITS_HPP_

#include "nav2_msgs/msg/detail/voxel_grid__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'origin'
#include "geometry_msgs/msg/detail/point32__traits.hpp"
// Member 'resolutions'
#include "geometry_msgs/msg/detail/vector3__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::msg::VoxelGrid & msg,
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

  // member: data
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.data.size() == 0) {
      out << "data: []\n";
    } else {
      out << "data:\n";
      for (auto item : msg.data) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: origin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "origin:\n";
    to_yaml(msg.origin, out, indentation + 2);
  }

  // member: resolutions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resolutions:\n";
    to_yaml(msg.resolutions, out, indentation + 2);
  }

  // member: size_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size_x: ";
    value_to_yaml(msg.size_x, out);
    out << "\n";
  }

  // member: size_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size_y: ";
    value_to_yaml(msg.size_y, out);
    out << "\n";
  }

  // member: size_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "size_z: ";
    value_to_yaml(msg.size_z, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::msg::VoxelGrid & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::msg::VoxelGrid>()
{
  return "nav2_msgs::msg::VoxelGrid";
}

template<>
inline const char * name<nav2_msgs::msg::VoxelGrid>()
{
  return "nav2_msgs/msg/VoxelGrid";
}

template<>
struct has_fixed_size<nav2_msgs::msg::VoxelGrid>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::msg::VoxelGrid>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::msg::VoxelGrid>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__MSG__DETAIL__VOXEL_GRID__TRAITS_HPP_
