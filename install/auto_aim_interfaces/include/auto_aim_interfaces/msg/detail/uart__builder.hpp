// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from auto_aim_interfaces:msg/Uart.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__UART__BUILDER_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__UART__BUILDER_HPP_

#include "auto_aim_interfaces/msg/detail/uart__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace auto_aim_interfaces
{

namespace msg
{

namespace builder
{

class Init_Uart_y
{
public:
  explicit Init_Uart_y(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  ::auto_aim_interfaces::msg::Uart y(::auto_aim_interfaces::msg::Uart::_y_type arg)
  {
    msg_.y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_x
{
public:
  explicit Init_Uart_x(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_y x(::auto_aim_interfaces::msg::Uart::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Uart_y(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_commd_keyboard
{
public:
  explicit Init_Uart_commd_keyboard(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_x commd_keyboard(::auto_aim_interfaces::msg::Uart::_commd_keyboard_type arg)
  {
    msg_.commd_keyboard = std::move(arg);
    return Init_Uart_x(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_sentry_hp
{
public:
  explicit Init_Uart_sentry_hp(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_commd_keyboard sentry_hp(::auto_aim_interfaces::msg::Uart::_sentry_hp_type arg)
  {
    msg_.sentry_hp = std::move(arg);
    return Init_Uart_commd_keyboard(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_outpost_hp
{
public:
  explicit Init_Uart_outpost_hp(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_sentry_hp outpost_hp(::auto_aim_interfaces::msg::Uart::_outpost_hp_type arg)
  {
    msg_.outpost_hp = std::move(arg);
    return Init_Uart_sentry_hp(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_game_stage
{
public:
  explicit Init_Uart_game_stage(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_outpost_hp game_stage(::auto_aim_interfaces::msg::Uart::_game_stage_type arg)
  {
    msg_.game_stage = std::move(arg);
    return Init_Uart_outpost_hp(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_remain_time
{
public:
  explicit Init_Uart_remain_time(::auto_aim_interfaces::msg::Uart & msg)
  : msg_(msg)
  {}
  Init_Uart_game_stage remain_time(::auto_aim_interfaces::msg::Uart::_remain_time_type arg)
  {
    msg_.remain_time = std::move(arg);
    return Init_Uart_game_stage(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

class Init_Uart_header
{
public:
  Init_Uart_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Uart_remain_time header(::auto_aim_interfaces::msg::Uart::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Uart_remain_time(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Uart msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::auto_aim_interfaces::msg::Uart>()
{
  return auto_aim_interfaces::msg::builder::Init_Uart_header();
}

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__UART__BUILDER_HPP_
