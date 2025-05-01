// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ig_lio_c_msgs:srv/ReLoc.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Request __attribute__((deprecated))
#else
# define DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Request __declspec(deprecated)
#endif

namespace ig_lio_c_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReLoc_Request_
{
  using Type = ReLoc_Request_<ContainerAllocator>;

  explicit ReLoc_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pcd_path = "";
      this->x = 0.0f;
      this->y = 0.0f;
      this->z = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
    }
  }

  explicit ReLoc_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pcd_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pcd_path = "";
      this->x = 0.0f;
      this->y = 0.0f;
      this->z = 0.0f;
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
    }
  }

  // field types and members
  using _pcd_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pcd_path_type pcd_path;
  using _x_type =
    float;
  _x_type x;
  using _y_type =
    float;
  _y_type y;
  using _z_type =
    float;
  _z_type z;
  using _roll_type =
    float;
  _roll_type roll;
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _yaw_type =
    float;
  _yaw_type yaw;

  // setters for named parameter idiom
  Type & set__pcd_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pcd_path = _arg;
    return *this;
  }
  Type & set__x(
    const float & _arg)
  {
    this->x = _arg;
    return *this;
  }
  Type & set__y(
    const float & _arg)
  {
    this->y = _arg;
    return *this;
  }
  Type & set__z(
    const float & _arg)
  {
    this->z = _arg;
    return *this;
  }
  Type & set__roll(
    const float & _arg)
  {
    this->roll = _arg;
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

  // constant declarations

  // pointer types
  using RawPtr =
    ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Request
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Request
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReLoc_Request_ & other) const
  {
    if (this->pcd_path != other.pcd_path) {
      return false;
    }
    if (this->x != other.x) {
      return false;
    }
    if (this->y != other.y) {
      return false;
    }
    if (this->z != other.z) {
      return false;
    }
    if (this->roll != other.roll) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReLoc_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReLoc_Request_

// alias to use template instance with default allocator
using ReLoc_Request =
  ig_lio_c_msgs::srv::ReLoc_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ig_lio_c_msgs


#ifndef _WIN32
# define DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Response __attribute__((deprecated))
#else
# define DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Response __declspec(deprecated)
#endif

namespace ig_lio_c_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ReLoc_Response_
{
  using Type = ReLoc_Response_<ContainerAllocator>;

  explicit ReLoc_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0l;
      this->message = "";
    }
  }

  explicit ReLoc_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0l;
      this->message = "";
    }
  }

  // field types and members
  using _status_type =
    int32_t;
  _status_type status;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__status(
    const int32_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Response
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ig_lio_c_msgs__srv__ReLoc_Response
    std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ReLoc_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ReLoc_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ReLoc_Response_

// alias to use template instance with default allocator
using ReLoc_Response =
  ig_lio_c_msgs::srv::ReLoc_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ig_lio_c_msgs

namespace ig_lio_c_msgs
{

namespace srv
{

struct ReLoc
{
  using Request = ig_lio_c_msgs::srv::ReLoc_Request;
  using Response = ig_lio_c_msgs::srv::ReLoc_Response;
};

}  // namespace srv

}  // namespace ig_lio_c_msgs

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_HPP_
