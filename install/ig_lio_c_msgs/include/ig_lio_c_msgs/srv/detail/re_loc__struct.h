// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ig_lio_c_msgs:srv/ReLoc.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_H_
#define IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'pcd_path'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/ReLoc in the package ig_lio_c_msgs.
typedef struct ig_lio_c_msgs__srv__ReLoc_Request
{
  rosidl_runtime_c__String pcd_path;
  float x;
  float y;
  float z;
  float roll;
  float pitch;
  float yaw;
} ig_lio_c_msgs__srv__ReLoc_Request;

// Struct for a sequence of ig_lio_c_msgs__srv__ReLoc_Request.
typedef struct ig_lio_c_msgs__srv__ReLoc_Request__Sequence
{
  ig_lio_c_msgs__srv__ReLoc_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ig_lio_c_msgs__srv__ReLoc_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/ReLoc in the package ig_lio_c_msgs.
typedef struct ig_lio_c_msgs__srv__ReLoc_Response
{
  int32_t status;
  rosidl_runtime_c__String message;
} ig_lio_c_msgs__srv__ReLoc_Response;

// Struct for a sequence of ig_lio_c_msgs__srv__ReLoc_Response.
typedef struct ig_lio_c_msgs__srv__ReLoc_Response__Sequence
{
  ig_lio_c_msgs__srv__ReLoc_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ig_lio_c_msgs__srv__ReLoc_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__STRUCT_H_
