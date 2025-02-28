// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from auto_aim_interfaces:msg/Uart.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__auto_aim_interfaces__msg__Uart __attribute__((deprecated))
#else
# define DEPRECATED__auto_aim_interfaces__msg__Uart __declspec(deprecated)
#endif

namespace auto_aim_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Uart_
{
  using Type = Uart_<ContainerAllocator>;

  explicit Uart_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->remain_time = 0;
      this->game_stage = 0;
      this->outpost_hp = 0;
      this->sentry_hp = 0;
      this->commd_keyboard = 0;
      this->x = 0;
      this->y = 0;
    }
  }

  explicit Uart_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->remain_time = 0;
      this->game_stage = 0;
      this->outpost_hp = 0;
      this->sentry_hp = 0;
      this->commd_keyboard = 0;
      this->x = 0;
      this->y = 0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _remain_time_type =
    uint16_t;
  _remain_time_type remain_time;
  using _game_stage_type =
    uint8_t;
  _game_stage_type game_stage;
  using _outpost_hp_type =
    uint16_t;
  _outpost_hp_type outpost_hp;
  using _sentry_hp_type =
    uint16_t;
  _sentry_hp_type sentry_hp;
  using _commd_keyboard_type =
    uint8_t;
  _commd_keyboard_type commd_keyboard;
  using _x_type =
    uint8_t;
  _x_type x;
  using _y_type =
    uint8_t;
  _y_type y;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__remain_time(
    const uint16_t & _arg)
  {
    this->remain_time = _arg;
    return *this;
  }
  Type & set__game_stage(
    const uint8_t & _arg)
  {
    this->game_stage = _arg;
    return *this;
  }
  Type & set__outpost_hp(
    const uint16_t & _arg)
  {
    this->outpost_hp = _arg;
    return *this;
  }
  Type & set__sentry_hp(
    const uint16_t & _arg)
  {
    this->sentry_hp = _arg;
    return *this;
  }
  Type & set__commd_keyboard(
    const uint8_t & _arg)
  {
    this->commd_keyboard = _arg;
    return *this;
  }
  Type & set__x(
    const uint8_t & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const uint8_t & _arg)
  {
    this->y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    auto_aim_interfaces::msg::Uart_<ContainerAllocator> *;
  using ConstRawPtr =
    const auto_aim_interfaces::msg::Uart_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Uart_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Uart_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__auto_aim_interfaces__msg__Uart
    std::shared_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__auto_aim_interfaces__msg__Uart
    std::shared_ptr<auto_aim_interfaces::msg::Uart_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Uart_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->remain_time != other.remain_time) {
      return false;
    }
    if (this->game_stage != other.game_stage) {
      return false;
    }
    if (this->outpost_hp != other.outpost_hp) {
      return false;
    }
    if (this->sentry_hp != other.sentry_hp) {
      return false;
    }
    if (this->commd_keyboard != other.commd_keyboard) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    return true;
  }
  bool operator!=(const Uart_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Uart_

// alias to use template instance with default allocator
using Uart =
  auto_aim_interfaces::msg::Uart_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__UART__STRUCT_HPP_
