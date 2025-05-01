// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from grid_map_msgs:msg/GridMap.idl
// generated code does not contain a copyright notice

#ifndef GRID_MAP_MSGS__MSG__DETAIL__GRID_MAP__TRAITS_HPP_
#define GRID_MAP_MSGS__MSG__DETAIL__GRID_MAP__TRAITS_HPP_

#include "grid_map_msgs/msg/detail/grid_map__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'info'
#include "grid_map_msgs/msg/detail/grid_map_info__traits.hpp"
// Member 'data'
#include "std_msgs/msg/detail/float32_multi_array__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const grid_map_msgs::msg::GridMap & msg,
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

  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_yaml(msg.info, out, indentation + 2);
  }

  // member: layers
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.layers.size() == 0) {
      out << "layers: []\n";
    } else {
      out << "layers:\n";
      for (auto item : msg.layers) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: basic_layers
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.basic_layers.size() == 0) {
      out << "basic_layers: []\n";
    } else {
      out << "basic_layers:\n";
      for (auto item : msg.basic_layers) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
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
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: outer_start_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "outer_start_index: ";
    value_to_yaml(msg.outer_start_index, out);
    out << "\n";
  }

  // member: inner_start_index
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "inner_start_index: ";
    value_to_yaml(msg.inner_start_index, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const grid_map_msgs::msg::GridMap & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<grid_map_msgs::msg::GridMap>()
{
  return "grid_map_msgs::msg::GridMap";
}

template<>
inline const char * name<grid_map_msgs::msg::GridMap>()
{
  return "grid_map_msgs/msg/GridMap";
}

template<>
struct has_fixed_size<grid_map_msgs::msg::GridMap>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<grid_map_msgs::msg::GridMap>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<grid_map_msgs::msg::GridMap>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // GRID_MAP_MSGS__MSG__DETAIL__GRID_MAP__TRAITS_HPP_
