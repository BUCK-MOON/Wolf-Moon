// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:srv/LoadMap.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__SRV__DETAIL__LOAD_MAP__TRAITS_HPP_
#define NAV2_MSGS__SRV__DETAIL__LOAD_MAP__TRAITS_HPP_

#include "nav2_msgs/srv/detail/load_map__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::srv::LoadMap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: map_url
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "map_url: ";
    value_to_yaml(msg.map_url, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::srv::LoadMap_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::srv::LoadMap_Request>()
{
  return "nav2_msgs::srv::LoadMap_Request";
}

template<>
inline const char * name<nav2_msgs::srv::LoadMap_Request>()
{
  return "nav2_msgs/srv/LoadMap_Request";
}

template<>
struct has_fixed_size<nav2_msgs::srv::LoadMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::srv::LoadMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::srv::LoadMap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'map'
#include "nav_msgs/msg/detail/occupancy_grid__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::srv::LoadMap_Response & msg,
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

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result: ";
    value_to_yaml(msg.result, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::srv::LoadMap_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::srv::LoadMap_Response>()
{
  return "nav2_msgs::srv::LoadMap_Response";
}

template<>
inline const char * name<nav2_msgs::srv::LoadMap_Response>()
{
  return "nav2_msgs/srv/LoadMap_Response";
}

template<>
struct has_fixed_size<nav2_msgs::srv::LoadMap_Response>
  : std::integral_constant<bool, has_fixed_size<nav_msgs::msg::OccupancyGrid>::value> {};

template<>
struct has_bounded_size<nav2_msgs::srv::LoadMap_Response>
  : std::integral_constant<bool, has_bounded_size<nav_msgs::msg::OccupancyGrid>::value> {};

template<>
struct is_message<nav2_msgs::srv::LoadMap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<nav2_msgs::srv::LoadMap>()
{
  return "nav2_msgs::srv::LoadMap";
}

template<>
inline const char * name<nav2_msgs::srv::LoadMap>()
{
  return "nav2_msgs/srv/LoadMap";
}

template<>
struct has_fixed_size<nav2_msgs::srv::LoadMap>
  : std::integral_constant<
    bool,
    has_fixed_size<nav2_msgs::srv::LoadMap_Request>::value &&
    has_fixed_size<nav2_msgs::srv::LoadMap_Response>::value
  >
{
};

template<>
struct has_bounded_size<nav2_msgs::srv::LoadMap>
  : std::integral_constant<
    bool,
    has_bounded_size<nav2_msgs::srv::LoadMap_Request>::value &&
    has_bounded_size<nav2_msgs::srv::LoadMap_Response>::value
  >
{
};

template<>
struct is_service<nav2_msgs::srv::LoadMap>
  : std::true_type
{
};

template<>
struct is_service_request<nav2_msgs::srv::LoadMap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<nav2_msgs::srv::LoadMap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__SRV__DETAIL__LOAD_MAP__TRAITS_HPP_
