// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from auto_aim_interfaces:msg/State.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_HPP_

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
// Member 'center'
// Member 'predict'
// Member 'calculate'
// Member 'angle'
#include "auto_aim_interfaces/msg/detail/point2f__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__auto_aim_interfaces__msg__State __attribute__((deprecated))
#else
# define DEPRECATED__auto_aim_interfaces__msg__State __declspec(deprecated)
#endif

namespace auto_aim_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct State_
{
  using Type = State_<ContainerAllocator>;

  explicit State_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    predict(_init),
    calculate(_init),
    angle(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->center.fill(auto_aim_interfaces::msg::Point2f_<ContainerAllocator>{_init});
      std::fill<typename std::array<double, 9>::iterator, double>(this->state.begin(), this->state.end(), 0.0);
    }
  }

  explicit State_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    center(_alloc),
    predict(_alloc, _init),
    calculate(_alloc, _init),
    angle(_alloc, _init),
    state(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->mode = 0;
      this->center.fill(auto_aim_interfaces::msg::Point2f_<ContainerAllocator>{_alloc, _init});
      std::fill<typename std::array<double, 9>::iterator, double>(this->state.begin(), this->state.end(), 0.0);
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _mode_type =
    uint8_t;
  _mode_type mode;
  using _center_type =
    std::array<auto_aim_interfaces::msg::Point2f_<ContainerAllocator>, 4>;
  _center_type center;
  using _predict_type =
    auto_aim_interfaces::msg::Point2f_<ContainerAllocator>;
  _predict_type predict;
  using _calculate_type =
    auto_aim_interfaces::msg::Point2f_<ContainerAllocator>;
  _calculate_type calculate;
  using _angle_type =
    auto_aim_interfaces::msg::Point2f_<ContainerAllocator>;
  _angle_type angle;
  using _state_type =
    std::array<double, 9>;
  _state_type state;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__mode(
    const uint8_t & _arg)
  {
    this->mode = _arg;
    return *this;
  }
  Type & set__center(
    const std::array<auto_aim_interfaces::msg::Point2f_<ContainerAllocator>, 4> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__predict(
    const auto_aim_interfaces::msg::Point2f_<ContainerAllocator> & _arg)
  {
    this->predict = _arg;
    return *this;
  }
  Type & set__calculate(
    const auto_aim_interfaces::msg::Point2f_<ContainerAllocator> & _arg)
  {
    this->calculate = _arg;
    return *this;
  }
  Type & set__angle(
    const auto_aim_interfaces::msg::Point2f_<ContainerAllocator> & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__state(
    const std::array<double, 9> & _arg)
  {
    this->state = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    auto_aim_interfaces::msg::State_<ContainerAllocator> *;
  using ConstRawPtr =
    const auto_aim_interfaces::msg::State_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::State_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::State_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__auto_aim_interfaces__msg__State
    std::shared_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__auto_aim_interfaces__msg__State
    std::shared_ptr<auto_aim_interfaces::msg::State_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const State_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->mode != other.mode) {
      return false;
    }
    if (this->center != other.center) {
      return false;
    }
    if (this->predict != other.predict) {
      return false;
    }
    if (this->calculate != other.calculate) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    return true;
  }
  bool operator!=(const State_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct State_

// alias to use template instance with default allocator
using State =
  auto_aim_interfaces::msg::State_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__STATE__STRUCT_HPP_
