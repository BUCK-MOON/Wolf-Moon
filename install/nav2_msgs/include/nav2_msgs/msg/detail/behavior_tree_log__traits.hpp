// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from nav2_msgs:msg/BehaviorTreeLog.idl
// generated code does not contain a copyright notice

#ifndef NAV2_MSGS__MSG__DETAIL__BEHAVIOR_TREE_LOG__TRAITS_HPP_
#define NAV2_MSGS__MSG__DETAIL__BEHAVIOR_TREE_LOG__TRAITS_HPP_

#include "nav2_msgs/msg/detail/behavior_tree_log__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

// Include directives for member types
// Member 'timestamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"
// Member 'event_log'
#include "nav2_msgs/msg/detail/behavior_tree_status_change__traits.hpp"

namespace rosidl_generator_traits
{

inline void to_yaml(
  const nav2_msgs::msg::BehaviorTreeLog & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: timestamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timestamp:\n";
    to_yaml(msg.timestamp, out, indentation + 2);
  }

  // member: event_log
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.event_log.size() == 0) {
      out << "event_log: []\n";
    } else {
      out << "event_log:\n";
      for (auto item : msg.event_log) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const nav2_msgs::msg::BehaviorTreeLog & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<nav2_msgs::msg::BehaviorTreeLog>()
{
  return "nav2_msgs::msg::BehaviorTreeLog";
}

template<>
inline const char * name<nav2_msgs::msg::BehaviorTreeLog>()
{
  return "nav2_msgs/msg/BehaviorTreeLog";
}

template<>
struct has_fixed_size<nav2_msgs::msg::BehaviorTreeLog>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<nav2_msgs::msg::BehaviorTreeLog>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<nav2_msgs::msg::BehaviorTreeLog>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // NAV2_MSGS__MSG__DETAIL__BEHAVIOR_TREE_LOG__TRAITS_HPP_
