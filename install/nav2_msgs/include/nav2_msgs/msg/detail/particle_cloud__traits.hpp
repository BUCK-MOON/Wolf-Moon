// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:msg/ParticleCloud.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__PARTICLE_CLOUD__TRAITS_HPP_
#define NAV2_MSGS__MSG__DETAIL__PARTICLE_CLOUD__TRAITS_HPP_

#include "nav2_msgs/msg/detail/particle_cloud__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'particles'
#include "nav2_msgs/msg/detail/particle__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::msg::ParticleCloud & msg,
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

  // member: particles
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.particles.size() == 0) {
      out << "particles: []\n";
    } else {
      out << "particles:\n";
      for (auto item : msg.particles) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::msg::ParticleCloud & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::msg::ParticleCloud>()
{
  return "nav2_msgs::msg::ParticleCloud";
}

template<>
inline const char * name<nav2_msgs::msg::ParticleCloud>()
{
  return "nav2_msgs/msg/ParticleCloud";
}

template<>
struct has_fixed_size<nav2_msgs::msg::ParticleCloud>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::msg::ParticleCloud>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::msg::ParticleCloud>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__MSG__DETAIL__PARTICLE_CLOUD__TRAITS_HPP_
