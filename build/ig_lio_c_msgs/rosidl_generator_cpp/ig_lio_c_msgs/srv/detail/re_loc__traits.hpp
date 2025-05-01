// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from ig_lio_c_msgs:srv/ReLoc.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__TRAITS_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__TRAITS_HPP_

#include "ig_lio_c_msgs/srv/detail/re_loc__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const ig_lio_c_msgs::srv::ReLoc_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pcd_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pcd_path: ";
    value_to_yaml(msg.pcd_path, out);
    out << "\n";
  }

  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "z: ";
    value_to_yaml(msg.z, out);
    out << "\n";
  }

  // member: roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "roll: ";
    value_to_yaml(msg.roll, out);
    out << "\n";
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ig_lio_c_msgs::srv::ReLoc_Request & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<ig_lio_c_msgs::srv::ReLoc_Request>()
{
  return "ig_lio_c_msgs::srv::ReLoc_Request";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::ReLoc_Request>()
{
  return "ig_lio_c_msgs/srv/ReLoc_Request";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::ReLoc_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::ReLoc_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ig_lio_c_msgs::srv::ReLoc_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

inline void to_yaml(
  const ig_lio_c_msgs::srv::ReLoc_Response & msg,
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

inline std::string to_yaml(const ig_lio_c_msgs::srv::ReLoc_Response & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<ig_lio_c_msgs::srv::ReLoc_Response>()
{
  return "ig_lio_c_msgs::srv::ReLoc_Response";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::ReLoc_Response>()
{
  return "ig_lio_c_msgs/srv/ReLoc_Response";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::ReLoc_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::ReLoc_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<ig_lio_c_msgs::srv::ReLoc_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<ig_lio_c_msgs::srv::ReLoc>()
{
  return "ig_lio_c_msgs::srv::ReLoc";
}

template<>
inline const char * name<ig_lio_c_msgs::srv::ReLoc>()
{
  return "ig_lio_c_msgs/srv/ReLoc";
}

template<>
struct has_fixed_size<ig_lio_c_msgs::srv::ReLoc>
  : std::integral_constant<
    bool,
    has_fixed_size<ig_lio_c_msgs::srv::ReLoc_Request>::value &&
    has_fixed_size<ig_lio_c_msgs::srv::ReLoc_Response>::value
  >
{
};

template<>
struct has_bounded_size<ig_lio_c_msgs::srv::ReLoc>
  : std::integral_constant<
    bool,
    has_bounded_size<ig_lio_c_msgs::srv::ReLoc_Request>::value &&
    has_bounded_size<ig_lio_c_msgs::srv::ReLoc_Response>::value
  >
{
};

template<>
struct is_service<ig_lio_c_msgs::srv::ReLoc>
  : std::true_type
{
};

template<>
struct is_service_request<ig_lio_c_msgs::srv::ReLoc_Request>
  : std::true_type
{
};

template<>
struct is_service_response<ig_lio_c_msgs::srv::ReLoc_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__TRAITS_HPP_
