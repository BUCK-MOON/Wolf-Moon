// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from ig_lio_c_msgs:srv/CovertMap.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__BUILDER_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__BUILDER_HPP_

#include "ig_lio_c_msgs/srv/detail/covert_map__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_CovertMap_Request_occupied_thresh
{
public:
  explicit Init_CovertMap_Request_occupied_thresh(::ig_lio_c_msgs::srv::CovertMap_Request & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::CovertMap_Request occupied_thresh(::ig_lio_c_msgs::srv::CovertMap_Request::_occupied_thresh_type arg)
  {
    msg_.occupied_thresh = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

class Init_CovertMap_Request_free_thresh
{
public:
  explicit Init_CovertMap_Request_free_thresh(::ig_lio_c_msgs::srv::CovertMap_Request & msg)
  : msg_(msg)
  {}
  Init_CovertMap_Request_occupied_thresh free_thresh(::ig_lio_c_msgs::srv::CovertMap_Request::_free_thresh_type arg)
  {
    msg_.free_thresh = std::move(arg);
    return Init_CovertMap_Request_occupied_thresh(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

class Init_CovertMap_Request_map_mode
{
public:
  explicit Init_CovertMap_Request_map_mode(::ig_lio_c_msgs::srv::CovertMap_Request & msg)
  : msg_(msg)
  {}
  Init_CovertMap_Request_free_thresh map_mode(::ig_lio_c_msgs::srv::CovertMap_Request::_map_mode_type arg)
  {
    msg_.map_mode = std::move(arg);
    return Init_CovertMap_Request_free_thresh(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

class Init_CovertMap_Request_image_format
{
public:
  explicit Init_CovertMap_Request_image_format(::ig_lio_c_msgs::srv::CovertMap_Request & msg)
  : msg_(msg)
  {}
  Init_CovertMap_Request_map_mode image_format(::ig_lio_c_msgs::srv::CovertMap_Request::_image_format_type arg)
  {
    msg_.image_format = std::move(arg);
    return Init_CovertMap_Request_map_mode(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

class Init_CovertMap_Request_map_file_name
{
public:
  explicit Init_CovertMap_Request_map_file_name(::ig_lio_c_msgs::srv::CovertMap_Request & msg)
  : msg_(msg)
  {}
  Init_CovertMap_Request_image_format map_file_name(::ig_lio_c_msgs::srv::CovertMap_Request::_map_file_name_type arg)
  {
    msg_.map_file_name = std::move(arg);
    return Init_CovertMap_Request_image_format(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

class Init_CovertMap_Request_pcd_path
{
public:
  Init_CovertMap_Request_pcd_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CovertMap_Request_map_file_name pcd_path(::ig_lio_c_msgs::srv::CovertMap_Request::_pcd_path_type arg)
  {
    msg_.pcd_path = std::move(arg);
    return Init_CovertMap_Request_map_file_name(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::CovertMap_Request>()
{
  return ig_lio_c_msgs::srv::builder::Init_CovertMap_Request_pcd_path();
}

}  // namespace ig_lio_c_msgs


namespace ig_lio_c_msgs
{

namespace srv
{

namespace builder
{

class Init_CovertMap_Response_message
{
public:
  explicit Init_CovertMap_Response_message(::ig_lio_c_msgs::srv::CovertMap_Response & msg)
  : msg_(msg)
  {}
  ::ig_lio_c_msgs::srv::CovertMap_Response message(::ig_lio_c_msgs::srv::CovertMap_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Response msg_;
};

class Init_CovertMap_Response_status
{
public:
  Init_CovertMap_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CovertMap_Response_message status(::ig_lio_c_msgs::srv::CovertMap_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_CovertMap_Response_message(msg_);
  }

private:
  ::ig_lio_c_msgs::srv::CovertMap_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::ig_lio_c_msgs::srv::CovertMap_Response>()
{
  return ig_lio_c_msgs::srv::builder::Init_CovertMap_Response_status();
}

}  // namespace ig_lio_c_msgs

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__BUILDER_HPP_
