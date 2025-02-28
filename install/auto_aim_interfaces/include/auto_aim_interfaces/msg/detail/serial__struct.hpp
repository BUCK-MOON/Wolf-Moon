// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from auto_aim_interfaces:msg/Serial.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__STRUCT_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__STRUCT_HPP_

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
// Member 'imu'
#include "sensor_msgs/msg/detail/imu__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__auto_aim_interfaces__msg__Serial __attribute__((deprecated))
#else
# define DEPRECATED__auto_aim_interfaces__msg__Serial __declspec(deprecated)
#endif

namespace auto_aim_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Serial_
{
  using Type = Serial_<ContainerAllocator>;

  explicit Serial_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    imu(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->bullet_speed = 0.0f;
      this->shoot_delay = 0.0f;
    }
  }

  explicit Serial_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    imu(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->bullet_speed = 0.0f;
      this->shoot_delay = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _imu_type =
    sensor_msgs::msg::Imu_<ContainerAllocator>;
  _imu_type imu;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _bullet_speed_type =
    float;
  _bullet_speed_type bullet_speed;
  using _shoot_delay_type =
    float;
  _shoot_delay_type shoot_delay;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__imu(
    const sensor_msgs::msg::Imu_<ContainerAllocator> & _arg)
  {
    this->imu = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__bullet_speed(
    const float & _arg)
  {
    this->bullet_speed = _arg;
    return *this;
  }
  Type & set__shoot_delay(
    const float & _arg)
  {
    this->shoot_delay = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    auto_aim_interfaces::msg::Serial_<ContainerAllocator> *;
  using ConstRawPtr =
    const auto_aim_interfaces::msg::Serial_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Serial_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Serial_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__auto_aim_interfaces__msg__Serial
    std::shared_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__auto_aim_interfaces__msg__Serial
    std::shared_ptr<auto_aim_interfaces::msg::Serial_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Serial_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->imu != other.imu) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->bullet_speed != other.bullet_speed) {
      return false;
    }
    if (this->shoot_delay != other.shoot_delay) {
      return false;
    }
    return true;
  }
  bool operator!=(const Serial_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Serial_

// alias to use template instance with default allocator
using Serial =
  auto_aim_interfaces::msg::Serial_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__SERIAL__STRUCT_HPP_
