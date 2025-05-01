// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from grid_map_msgs:srv/SetGridMap.idl
// generated code does not contain a copyright notice

#ifndef GRID_MAP_MSGS__SRV__DETAIL__SET_GRID_MAP__TRAITS_HPP_
#define GRID_MAP_MSGS__SRV__DETAIL__SET_GRID_MAP__TRAITS_HPP_

#include "grid_map_msgs/srv/detail/set_grid_map__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'map'
#include "grid_map_msgs/msg/detail/grid_map__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const grid_map_msgs::srv::SetGridMap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: map
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map:\n";
    to_yaml(msg.map, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const grid_map_msgs::srv::SetGridMap_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<grid_map_msgs::srv::SetGridMap_Request>()
{
  return "grid_map_msgs::srv::SetGridMap_Request";
}

template<>
inline const char * name<grid_map_msgs::srv::SetGridMap_Request>()
{
  return "grid_map_msgs/srv/SetGridMap_Request";
}

template<>
struct has_fixed_size<grid_map_msgs::srv::SetGridMap_Request>
  : std::integral_constant<bool, has_fixed_size<grid_map_msgs::msg::GridMap>::value> {};

template<>
struct has_bounded_size<grid_map_msgs::srv::SetGridMap_Request>
  : std::integral_constant<bool, has_bounded_size<grid_map_msgs::msg::GridMap>::value> {};

template<>
struct is_message<grid_map_msgs::srv::SetGridMap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

inline void to_yaml(
  const grid_map_msgs::srv::SetGridMap_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const grid_map_msgs::srv::SetGridMap_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<grid_map_msgs::srv::SetGridMap_Response>()
{
  return "grid_map_msgs::srv::SetGridMap_Response";
}

template<>
inline const char * name<grid_map_msgs::srv::SetGridMap_Response>()
{
  return "grid_map_msgs/srv/SetGridMap_Response";
}

template<>
struct has_fixed_size<grid_map_msgs::srv::SetGridMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<grid_map_msgs::srv::SetGridMap_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<grid_map_msgs::srv::SetGridMap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<grid_map_msgs::srv::SetGridMap>()
{
  return "grid_map_msgs::srv::SetGridMap";
}

template<>
inline const char * name<grid_map_msgs::srv::SetGridMap>()
{
  return "grid_map_msgs/srv/SetGridMap";
}

template<>
struct has_fixed_size<grid_map_msgs::srv::SetGridMap>
  : std::integral_constant<
    bool,
    has_fixed_size<grid_map_msgs::srv::SetGridMap_Request>::value &&
    has_fixed_size<grid_map_msgs::srv::SetGridMap_Response>::value
  >
{
};

template<>
struct has_bounded_size<grid_map_msgs::srv::SetGridMap>
  : std::integral_constant<
    bool,
    has_bounded_size<grid_map_msgs::srv::SetGridMap_Request>::value &&
    has_bounded_size<grid_map_msgs::srv::SetGridMap_Response>::value
  >
{
};

template<>
struct is_service<grid_map_msgs::srv::SetGridMap>
  : std::true_type
{
};

template<>
struct is_service_request<grid_map_msgs::srv::SetGridMap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<grid_map_msgs::srv::SetGridMap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // GRID_MAP_MSGS__SRV__DETAIL__SET_GRID_MAP__TRAITS_HPP_
