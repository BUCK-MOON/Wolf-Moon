// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from ig_lio_c_msgs:srv/CovertMap.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_HPP_
#define IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Request __attribute__((deprecated))
#else
# define DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Request __declspec(deprecated)
#endif

namespace ig_lio_c_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CovertMap_Request_
{
  using Type = CovertMap_Request_<ContainerAllocator>;

  explicit CovertMap_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pcd_path = "";
      this->map_file_name = "";
      this->image_format = "";
      this->map_mode = "";
      this->free_thresh = 0.0f;
      this->occupied_thresh = 0.0f;
    }
  }

  explicit CovertMap_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pcd_path(_alloc),
    map_file_name(_alloc),
    image_format(_alloc),
    map_mode(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pcd_path = "";
      this->map_file_name = "";
      this->image_format = "";
      this->map_mode = "";
      this->free_thresh = 0.0f;
      this->occupied_thresh = 0.0f;
    }
  }

  // field types and members
  using _pcd_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _pcd_path_type pcd_path;
  using _map_file_name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_file_name_type map_file_name;
  using _image_format_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _image_format_type image_format;
  using _map_mode_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _map_mode_type map_mode;
  using _free_thresh_type =
    float;
  _free_thresh_type free_thresh;
  using _occupied_thresh_type =
    float;
  _occupied_thresh_type occupied_thresh;

  // setters for named parameter idiom
  Type & set__pcd_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->pcd_path = _arg;
    return *this;
  }
  Type & set__map_file_name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_file_name = _arg;
    return *this;
  }
  Type & set__image_format(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->image_format = _arg;
    return *this;
  }
  Type & set__map_mode(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->map_mode = _arg;
    return *this;
  }
  Type & set__free_thresh(
    const float & _arg)
  {
    this->free_thresh = _arg;
    return *this;
  }
  Type & set__occupied_thresh(
    const float & _arg)
  {
    this->occupied_thresh = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Request
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Request
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CovertMap_Request_ & other) const
  {
    if (this->pcd_path != other.pcd_path) {
      return false;
    }
    if (this->map_file_name != other.map_file_name) {
      return false;
    }
    if (this->image_format != other.image_format) {
      return false;
    }
    if (this->map_mode != other.map_mode) {
      return false;
    }
    if (this->free_thresh != other.free_thresh) {
      return false;
    }
    if (this->occupied_thresh != other.occupied_thresh) {
      return false;
    }
    return true;
  }
  bool operator!=(const CovertMap_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CovertMap_Request_

// alias to use template instance with default allocator
using CovertMap_Request =
  ig_lio_c_msgs::srv::CovertMap_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ig_lio_c_msgs


#ifndef _WIN32
# define DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Response __attribute__((deprecated))
#else
# define DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Response __declspec(deprecated)
#endif

namespace ig_lio_c_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct CovertMap_Response_
{
  using Type = CovertMap_Response_<ContainerAllocator>;

  explicit CovertMap_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0l;
      this->message = "";
    }
  }

  explicit CovertMap_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Response
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__ig_lio_c_msgs__srv__CovertMap_Response
    std::shared_ptr<ig_lio_c_msgs::srv::CovertMap_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CovertMap_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const CovertMap_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CovertMap_Response_

// alias to use template instance with default allocator
using CovertMap_Response =
  ig_lio_c_msgs::srv::CovertMap_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace ig_lio_c_msgs

namespace ig_lio_c_msgs
{

namespace srv
{

struct CovertMap
{
  using Request = ig_lio_c_msgs::srv::CovertMap_Request;
  using Response = ig_lio_c_msgs::srv::CovertMap_Response;
};

}  // namespace srv

}  // namespace ig_lio_c_msgs

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_HPP_
