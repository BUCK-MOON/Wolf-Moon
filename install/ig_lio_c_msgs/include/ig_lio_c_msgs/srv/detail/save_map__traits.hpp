// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ig_lio_c_msgs:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_

#include "ig_lio_c_msgs/srv/detail/save_map__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const ig_lio_c_msgs::srv::SaveMap_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: save_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "save_path: ";
    value_to_yaml(msg.save_path, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ig_lio_c_msgs::srv::SaveMap_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<ig_lio_c_msgs::srv::SaveMap_Request>()
{
  return "ig_lio_c_msgs::srv::SaveMap_Request";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::SaveMap_Request>()
{
  return "ig_lio_c_msgs/srv/SaveMap_Request";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::SaveMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::SaveMap_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ig_lio_c_msgs::srv::SaveMap_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

inline void to_yaml(
  const ig_lio_c_msgs::srv::SaveMap_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    value_to_yaml(msg.message, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ig_lio_c_msgs::srv::SaveMap_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<ig_lio_c_msgs::srv::SaveMap_Response>()
{
  return "ig_lio_c_msgs::srv::SaveMap_Response";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::SaveMap_Response>()
{
  return "ig_lio_c_msgs/srv/SaveMap_Response";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::SaveMap_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::SaveMap_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ig_lio_c_msgs::srv::SaveMap_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ig_lio_c_msgs::srv::SaveMap>()
{
  return "ig_lio_c_msgs::srv::SaveMap";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::SaveMap>()
{
  return "ig_lio_c_msgs/srv/SaveMap";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::SaveMap>
  : std::integral_constant<
    bool,
    has_fixed_size<ig_lio_c_msgs::srv::SaveMap_Request>::value &&
    has_fixed_size<ig_lio_c_msgs::srv::SaveMap_Response>::value
  >
{
};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::SaveMap>
  : std::integral_constant<
    bool,
    has_bounded_size<ig_lio_c_msgs::srv::SaveMap_Request>::value &&
    has_bounded_size<ig_lio_c_msgs::srv::SaveMap_Response>::value
  >
{
};

template<>
struct is_service<ig_lio_c_msgs::srv::SaveMap>
  : std::true_type
{
};

template<>
struct is_service_request<ig_lio_c_msgs::srv::SaveMap_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ig_lio_c_msgs::srv::SaveMap_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__TRAITS_HPP_
