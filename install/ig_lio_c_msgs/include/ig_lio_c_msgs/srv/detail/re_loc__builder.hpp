// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ig_lio_c_msgs:srv/ReLoc.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__BUILDER_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__BUILDER_HPP_

#include "ig_lio_c_msgs/srv/detail/re_loc__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_ReLoc_Request_yaw
{
public:
  explicit Init_ReLoc_Request_yaw(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::ReLoc_Request yaw(::ig_lio_c_msgs::srv::ReLoc_Request::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_pitch
{
public:
  explicit Init_ReLoc_Request_pitch(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  Init_ReLoc_Request_yaw pitch(::ig_lio_c_msgs::srv::ReLoc_Request::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_ReLoc_Request_yaw(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_roll
{
public:
  explicit Init_ReLoc_Request_roll(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  Init_ReLoc_Request_pitch roll(::ig_lio_c_msgs::srv::ReLoc_Request::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_ReLoc_Request_pitch(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_z
{
public:
  explicit Init_ReLoc_Request_z(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  Init_ReLoc_Request_roll z(::ig_lio_c_msgs::srv::ReLoc_Request::_z_type arg)
  {
    msg_.z = std::move(arg);
    return Init_ReLoc_Request_roll(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_y
{
public:
  explicit Init_ReLoc_Request_y(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  Init_ReLoc_Request_z y(::ig_lio_c_msgs::srv::ReLoc_Request::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_ReLoc_Request_z(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_x
{
public:
  explicit Init_ReLoc_Request_x(::ig_lio_c_msgs::srv::ReLoc_Request & msg)
  : msg_(msg)
  {}
  Init_ReLoc_Request_y x(::ig_lio_c_msgs::srv::ReLoc_Request::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_ReLoc_Request_y(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

class Init_ReLoc_Request_pcd_path
{
public:
  Init_ReLoc_Request_pcd_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReLoc_Request_x pcd_path(::ig_lio_c_msgs::srv::ReLoc_Request::_pcd_path_type arg)
  {
    msg_.pcd_path = std::move(arg);
    return Init_ReLoc_Request_x(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::ReLoc_Request>()
{
  return ig_lio_c_msgs::srv::builder::Init_ReLoc_Request_pcd_path();
}

}  // namespace ig_lio_c_msgs


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_ReLoc_Response_message
{
public:
  explicit Init_ReLoc_Response_message(::ig_lio_c_msgs::srv::ReLoc_Response & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::ReLoc_Response message(::ig_lio_c_msgs::srv::ReLoc_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Response msg_;
};

class Init_ReLoc_Response_status
{
public:
  Init_ReLoc_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ReLoc_Response_message status(::ig_lio_c_msgs::srv::ReLoc_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_ReLoc_Response_message(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::ReLoc_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::ReLoc_Response>()
{
  return ig_lio_c_msgs::srv::builder::Init_ReLoc_Response_status();
}

}  // namespace ig_lio_c_msgs

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__BUILDER_HPP_
