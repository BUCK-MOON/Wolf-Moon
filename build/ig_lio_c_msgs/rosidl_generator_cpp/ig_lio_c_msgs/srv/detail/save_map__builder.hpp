// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ig_lio_c_msgs:srv/SaveMap.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_

#include "ig_lio_c_msgs/srv/detail/save_map__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Request_resolution
{
public:
  explicit Init_SaveMap_Request_resolution(::ig_lio_c_msgs::srv::SaveMap_Request & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::SaveMap_Request resolution(::ig_lio_c_msgs::srv::SaveMap_Request::_resolution_type arg)
  {
    msg_.resolution = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::SaveMap_Request msg_;
};

class Init_SaveMap_Request_save_path
{
public:
  Init_SaveMap_Request_save_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveMap_Request_resolution save_path(::ig_lio_c_msgs::srv::SaveMap_Request::_save_path_type arg)
  {
    msg_.save_path = std::move(arg);
    return Init_SaveMap_Request_resolution(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::SaveMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::SaveMap_Request>()
{
  return ig_lio_c_msgs::srv::builder::Init_SaveMap_Request_save_path();
}

}  // namespace ig_lio_c_msgs


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_SaveMap_Response_message
{
public:
  explicit Init_SaveMap_Response_message(::ig_lio_c_msgs::srv::SaveMap_Response & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::SaveMap_Response message(::ig_lio_c_msgs::srv::SaveMap_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::SaveMap_Response msg_;
};

class Init_SaveMap_Response_status
{
public:
  Init_SaveMap_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SaveMap_Response_message status(::ig_lio_c_msgs::srv::SaveMap_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_SaveMap_Response_message(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::SaveMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::SaveMap_Response>()
{
  return ig_lio_c_msgs::srv::builder::Init_SaveMap_Response_status();
}

}  // namespace ig_lio_c_msgs

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__SAVE_MAP__BUILDER_HPP_
