// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from auto_aim_interfaces:msg/Gimbal.idl
// generated code does not contain a copyright notice

#ifndef AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_HPP_
#define AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_HPP_

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
// Member 'meas_point_cam'
// Member 'pred_point_cam'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__auto_aim_interfaces__msg__Gimbal __attribute__((deprecated))
#else
# define DEPRECATED__auto_aim_interfaces__msg__Gimbal __declspec(deprecated)
#endif

namespace auto_aim_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Gimbal_
{
  using Type = Gimbal_<ContainerAllocator>;

  explicit Gimbal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    meas_point_cam(_init),
    pred_point_cam(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->distance = 0.0f;
      this->is_switched = false;
      this->is_target = false;
      this->is_spinning = false;
      this->is_spinning_switched = false;
      this->is_shooting = false;
      this->is_prediction = false;
    }
  }

  explicit Gimbal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    meas_point_cam(_alloc, _init),
    pred_point_cam(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->distance = 0.0f;
      this->is_switched = false;
      this->is_target = false;
      this->is_spinning = false;
      this->is_spinning_switched = false;
      this->is_shooting = false;
      this->is_prediction = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _distance_type =
    float;
  _distance_type distance;
  using _is_switched_type =
    bool;
  _is_switched_type is_switched;
  using _is_target_type =
    bool;
  _is_target_type is_target;
  using _is_spinning_type =
    bool;
  _is_spinning_type is_spinning;
  using _is_spinning_switched_type =
    bool;
  _is_spinning_switched_type is_spinning_switched;
  using _is_shooting_type =
    bool;
  _is_shooting_type is_shooting;
  using _is_prediction_type =
    bool;
  _is_prediction_type is_prediction;
  using _meas_point_cam_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _meas_point_cam_type meas_point_cam;
  using _pred_point_cam_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _pred_point_cam_type pred_point_cam;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__pitch(
    const float & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }
  Type & set__is_switched(
    const bool & _arg)
  {
    this->is_switched = _arg;
    return *this;
  }
  Type & set__is_target(
    const bool & _arg)
  {
    this->is_target = _arg;
    return *this;
  }
  Type & set__is_spinning(
    const bool & _arg)
  {
    this->is_spinning = _arg;
    return *this;
  }
  Type & set__is_spinning_switched(
    const bool & _arg)
  {
    this->is_spinning_switched = _arg;
    return *this;
  }
  Type & set__is_shooting(
    const bool & _arg)
  {
    this->is_shooting = _arg;
    return *this;
  }
  Type & set__is_prediction(
    const bool & _arg)
  {
    this->is_prediction = _arg;
    return *this;
  }
  Type & set__meas_point_cam(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->meas_point_cam = _arg;
    return *this;
  }
  Type & set__pred_point_cam(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->pred_point_cam = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> *;
  using ConstRawPtr =
    const auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__auto_aim_interfaces__msg__Gimbal
    std::shared_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__auto_aim_interfaces__msg__Gimbal
    std::shared_ptr<auto_aim_interfaces::msg::Gimbal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Gimbal_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    if (this->is_switched != other.is_switched) {
      return false;
    }
    if (this->is_target != other.is_target) {
      return false;
    }
    if (this->is_spinning != other.is_spinning) {
      return false;
    }
    if (this->is_spinning_switched != other.is_spinning_switched) {
      return false;
    }
    if (this->is_shooting != other.is_shooting) {
      return false;
    }
    if (this->is_prediction != other.is_prediction) {
      return false;
    }
    if (this->meas_point_cam != other.meas_point_cam) {
      return false;
    }
    if (this->pred_point_cam != other.pred_point_cam) {
      return false;
    }
    return true;
  }
  bool operator!=(const Gimbal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Gimbal_

// alias to use template instance with default allocator
using Gimbal =
  auto_aim_interfaces::msg::Gimbal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace auto_aim_interfaces

#endif  // AUTO_AIM_INTERFACES__MSG__DETAIL__GIMBAL__STRUCT_HPP_
