// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:msg/CostmapMetaData.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__COSTMAP_META_DATA__TRAITS_HPP_
#define NAV2_MSGS__MSG__DETAIL__COSTMAP_META_DATA__TRAITS_HPP_

#include "nav2_msgs/msg/detail/costmap_meta_data__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'map_load_time'
// Member 'update_time'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'origin'
#include "geometry_msgs/msg/detail/pose__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::msg::CostmapMetaData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: map_load_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_load_time:\n";
    to_yaml(msg.map_load_time, out, indentation + 2);
  }

  // member: update_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "update_time:\n";
    to_yaml(msg.update_time, out, indentation + 2);
  }

  // member: layer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "layer: ";
    value_to_yaml(msg.layer, out);
    out << "\n";
  }

  // member: resolution
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "resolution: ";
    value_to_yaml(msg.resolution, out);
    out << "\n";
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

  // member: origin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "origin:\n";
    to_yaml(msg.origin, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::msg::CostmapMetaData & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::msg::CostmapMetaData>()
{
  return "nav2_msgs::msg::CostmapMetaData";
}

template<>
inline const char * name<nav2_msgs::msg::CostmapMetaData>()
{
  return "nav2_msgs/msg/CostmapMetaData";
}

template<>
struct has_fixed_size<nav2_msgs::msg::CostmapMetaData>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::msg::CostmapMetaData>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::msg::CostmapMetaData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__MSG__DETAIL__COSTMAP_META_DATA__TRAITS_HPP_
