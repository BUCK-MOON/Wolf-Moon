// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:msg/CostmapFilterInfo.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__TRAITS_HPP_
#define NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__TRAITS_HPP_

#include "nav2_msgs/msg/detail/costmap_filter_info__struct.hpp"
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
  const nav2_msgs::msg::CostmapFilterInfo & msg,
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

  // member: type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "type: ";
    value_to_yaml(msg.type, out);
    out << "\n";
  }

  // member: filter_mask_topic
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "filter_mask_topic: ";
    value_to_yaml(msg.filter_mask_topic, out);
    out << "\n";
  }

  // member: base
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "base: ";
    value_to_yaml(msg.base, out);
    out << "\n";
  }

  // member: multiplier
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "multiplier: ";
    value_to_yaml(msg.multiplier, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::msg::CostmapFilterInfo & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::msg::CostmapFilterInfo>()
{
  return "nav2_msgs::msg::CostmapFilterInfo";
}

template<>
inline const char * name<nav2_msgs::msg::CostmapFilterInfo>()
{
  return "nav2_msgs/msg/CostmapFilterInfo";
}

template<>
struct has_fixed_size<nav2_msgs::msg::CostmapFilterInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::msg::CostmapFilterInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::msg::CostmapFilterInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__MSG__DETAIL__COSTMAP_FILTER_INFO__TRAITS_HPP_
