// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from auto_aim_interfaces:msg/Gimbal.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__BUILDER_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__BUILDER_HPP_

#include "auto_aim_interfaces/msg/detail/gimbal__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace auto_aim_interfaces
{

namespace msg
{

namespace builder
{

class Init_Gimbal_pred_point_cam
{
public:
  explicit Init_Gimbal_pred_point_cam(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  ::auto_aim_interfaces::msg::Gimbal pred_point_cam(::auto_aim_interfaces::msg::Gimbal::_pred_point_cam_type arg)
  {
    msg_.pred_point_cam = std::move(arg);
    return std::move(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_meas_point_cam
{
public:
  explicit Init_Gimbal_meas_point_cam(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_pred_point_cam meas_point_cam(::auto_aim_interfaces::msg::Gimbal::_meas_point_cam_type arg)
  {
    msg_.meas_point_cam = std::move(arg);
    return Init_Gimbal_pred_point_cam(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_prediction
{
public:
  explicit Init_Gimbal_is_prediction(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_meas_point_cam is_prediction(::auto_aim_interfaces::msg::Gimbal::_is_prediction_type arg)
  {
    msg_.is_prediction = std::move(arg);
    return Init_Gimbal_meas_point_cam(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_shooting
{
public:
  explicit Init_Gimbal_is_shooting(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_prediction is_shooting(::auto_aim_interfaces::msg::Gimbal::_is_shooting_type arg)
  {
    msg_.is_shooting = std::move(arg);
    return Init_Gimbal_is_prediction(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_spinning_switched
{
public:
  explicit Init_Gimbal_is_spinning_switched(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_shooting is_spinning_switched(::auto_aim_interfaces::msg::Gimbal::_is_spinning_switched_type arg)
  {
    msg_.is_spinning_switched = std::move(arg);
    return Init_Gimbal_is_shooting(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_spinning
{
public:
  explicit Init_Gimbal_is_spinning(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_spinning_switched is_spinning(::auto_aim_interfaces::msg::Gimbal::_is_spinning_type arg)
  {
    msg_.is_spinning = std::move(arg);
    return Init_Gimbal_is_spinning_switched(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_target
{
public:
  explicit Init_Gimbal_is_target(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_spinning is_target(::auto_aim_interfaces::msg::Gimbal::_is_target_type arg)
  {
    msg_.is_target = std::move(arg);
    return Init_Gimbal_is_spinning(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_is_switched
{
public:
  explicit Init_Gimbal_is_switched(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_target is_switched(::auto_aim_interfaces::msg::Gimbal::_is_switched_type arg)
  {
    msg_.is_switched = std::move(arg);
    return Init_Gimbal_is_target(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_distance
{
public:
  explicit Init_Gimbal_distance(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_is_switched distance(::auto_aim_interfaces::msg::Gimbal::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_Gimbal_is_switched(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_yaw
{
public:
  explicit Init_Gimbal_yaw(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_distance yaw(::auto_aim_interfaces::msg::Gimbal::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_Gimbal_distance(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_pitch
{
public:
  explicit Init_Gimbal_pitch(::auto_aim_interfaces::msg::Gimbal & msg)
  : msg_(msg)
  {}
  Init_Gimbal_yaw pitch(::auto_aim_interfaces::msg::Gimbal::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_Gimbal_yaw(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

class Init_Gimbal_header
{
public:
  Init_Gimbal_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Gimbal_pitch header(::auto_aim_interfaces::msg::Gimbal::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Gimbal_pitch(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Gimbal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::auto_aim_interfaces::msg::Gimbal>()
{
  return auto_aim_interfaces::msg::builder::Init_Gimbal_header();
}

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__BUILDER_HPP_
