// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__BUILDER_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__BUILDER_HPP_

#include "auto_aim_interfaces/msg/detail/state__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace auto_aim_interfaces
{

namespace msg
{

namespace builder
{

class Init_State_state
{
public:
  explicit Init_State_state(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  ::auto_aim_interfaces::msg::State state(::auto_aim_interfaces::msg::State::_state_type arg)
  {
    msg_.state = std::move(arg);
    return std::move(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_angle
{
public:
  explicit Init_State_angle(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_state angle(::auto_aim_interfaces::msg::State::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_State_state(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_calculate
{
public:
  explicit Init_State_calculate(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_angle calculate(::auto_aim_interfaces::msg::State::_calculate_type arg)
  {
    msg_.calculate = std::move(arg);
    return Init_State_angle(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_predict
{
public:
  explicit Init_State_predict(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_calculate predict(::auto_aim_interfaces::msg::State::_predict_type arg)
  {
    msg_.predict = std::move(arg);
    return Init_State_calculate(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_center
{
public:
  explicit Init_State_center(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_predict center(::auto_aim_interfaces::msg::State::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_State_predict(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_mode
{
public:
  explicit Init_State_mode(::auto_aim_interfaces::msg::State & msg)
  : msg_(msg)
  {}
  Init_State_center mode(::auto_aim_interfaces::msg::State::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_State_center(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

class Init_State_header
{
public:
  Init_State_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_State_mode header(::auto_aim_interfaces::msg::State::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_State_mode(msg_);
  }

private:
  ::auto_aim_interfaces::msg::State msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::auto_aim_interfaces::msg::State>()
{
  return auto_aim_interfaces::msg::builder::Init_State_header();
}

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__BUILDER_HPP_
