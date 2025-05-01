// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:srv/GetCostmap.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__SRV__DETAIL__GET_COSTMAP__TRAITS_HPP_
#define NAV2_MSGS__SRV__DETAIL__GET_COSTMAP__TRAITS_HPP_

#include "nav2_msgs/srv/detail/get_costmap__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'specs'
#include "nav2_msgs/msg/detail/costmap_meta_data__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::srv::GetCostmap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: specs
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "specs:\n";
    to_yaml(msg.specs, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::srv::GetCostmap_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::srv::GetCostmap_Request>()
{
  return "nav2_msgs::srv::GetCostmap_Request";
}

template<>
inline const char * name<nav2_msgs::srv::GetCostmap_Request>()
{
  return "nav2_msgs/srv/GetCostmap_Request";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCostmap_Request>
  : std::integral_constant<bool, has_fixed_size<nav2_msgs::msg::CostmapMetaData>::value> {};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCostmap_Request>
  : std::integral_constant<bool, has_bounded_size<nav2_msgs::msg::CostmapMetaData>::value> {};

template<>
struct is_message<nav2_msgs::srv::GetCostmap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'map'
#include "nav2_msgs/msg/detail/costmap__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::srv::GetCostmap_Response & msg,
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

inline std::string to_yaml(const nav2_msgs::srv::GetCostmap_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::srv::GetCostmap_Response>()
{
  return "nav2_msgs::srv::GetCostmap_Response";
}

template<>
inline const char * name<nav2_msgs::srv::GetCostmap_Response>()
{
  return "nav2_msgs/srv/GetCostmap_Response";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCostmap_Response>
  : std::integral_constant<bool, has_fixed_size<nav2_msgs::msg::Costmap>::value> {};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCostmap_Response>
  : std::integral_constant<bool, has_bounded_size<nav2_msgs::msg::Costmap>::value> {};

template<>
struct is_message<nav2_msgs::srv::GetCostmap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<nav2_msgs::srv::GetCostmap>()
{
  return "nav2_msgs::srv::GetCostmap";
}

template<>
inline const char * name<nav2_msgs::srv::GetCostmap>()
{
  return "nav2_msgs/srv/GetCostmap";
}

template<>
struct has_fixed_size<nav2_msgs::srv::GetCostmap>
  : std::integral_constant<
    bool,
    has_fixed_size<nav2_msgs::srv::GetCostmap_Request>::value &&
    has_fixed_size<nav2_msgs::srv::GetCostmap_Response>::value
  >
{
};

template<>
struct has_bounded_size<nav2_msgs::srv::GetCostmap>
  : std::integral_constant<
    bool,
    has_bounded_size<nav2_msgs::srv::GetCostmap_Request>::value &&
    has_bounded_size<nav2_msgs::srv::GetCostmap_Response>::value
  >
{
};

template<>
struct is_service<nav2_msgs::srv::GetCostmap>
  : std::true_type
{
};

template<>
struct is_service_request<nav2_msgs::srv::GetCostmap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<nav2_msgs::srv::GetCostmap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__SRV__DETAIL__GET_COSTMAP__TRAITS_HPP_
