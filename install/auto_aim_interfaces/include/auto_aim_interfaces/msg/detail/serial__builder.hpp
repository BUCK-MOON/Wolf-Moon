// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from auto_aim_interfaces:msg/Serial.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__BUILDER_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__BUILDER_HPP_

#include "auto_aim_interfaces/msg/detail/serial__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace auto_aim_interfaces
{

namespace msg
{

namespace builder
{

class Init_Serial_shoot_delay
{
public:
  explicit Init_Serial_shoot_delay(::auto_aim_interfaces::msg::Serial & msg)
  : msg_(msg)
  {}
  ::auto_aim_interfaces::msg::Serial shoot_delay(::auto_aim_interfaces::msg::Serial::_shoot_delay_type arg)
  {
    msg_.shoot_delay = std::move(arg);
    return std::move(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Serial msg_;
};

class Init_Serial_bullet_speed
{
public:
  explicit Init_Serial_bullet_speed(::auto_aim_interfaces::msg::Serial & msg)
  : msg_(msg)
  {}
  Init_Serial_shoot_delay bullet_speed(::auto_aim_interfaces::msg::Serial::_bullet_speed_type arg)
  {
    msg_.bullet_speed = std::move(arg);
    return Init_Serial_shoot_delay(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Serial msg_;
};

class Init_Serial_mode
{
public:
  explicit Init_Serial_mode(::auto_aim_interfaces::msg::Serial & msg)
  : msg_(msg)
  {}
  Init_Serial_bullet_speed mode(::auto_aim_interfaces::msg::Serial::_mode_type arg)
  {
    msg_.mode = std::move(arg);
    return Init_Serial_bullet_speed(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Serial msg_;
};

class Init_Serial_imu
{
public:
  explicit Init_Serial_imu(::auto_aim_interfaces::msg::Serial & msg)
  : msg_(msg)
  {}
  Init_Serial_mode imu(::auto_aim_interfaces::msg::Serial::_imu_type arg)
  {
    msg_.imu = std::move(arg);
    return Init_Serial_mode(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Serial msg_;
};

class Init_Serial_header
{
public:
  Init_Serial_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Serial_imu header(::auto_aim_interfaces::msg::Serial::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Serial_imu(msg_);
  }

private:
  ::auto_aim_interfaces::msg::Serial msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::auto_aim_interfaces::msg::Serial>()
{
  return auto_aim_interfaces::msg::builder::Init_Serial_header();
}

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__BUILDER_HPP_
