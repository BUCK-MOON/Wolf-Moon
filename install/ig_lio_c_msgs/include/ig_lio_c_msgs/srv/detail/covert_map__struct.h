// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ig_lio_c_msgs:srv/CovertMap.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_H_
#define IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_H_

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
// Member 'map_file_name'
// Member 'image_format'
// Member 'map_mode'
#include "rosidl_runtime_c/string.h"

// Struct defined in srv/CovertMap in the package ig_lio_c_msgs.
typedef struct ig_lio_c_msgs__srv__CovertMap_Request
{
  rosidl_runtime_c__String pcd_path;
  rosidl_runtime_c__String map_file_name;
  rosidl_runtime_c__String image_format;
  rosidl_runtime_c__String map_mode;
  float free_thresh;
  float occupied_thresh;
} ig_lio_c_msgs__srv__CovertMap_Request;

// Struct for a sequence of ig_lio_c_msgs__srv__CovertMap_Request.
typedef struct ig_lio_c_msgs__srv__CovertMap_Request__Sequence
{
  ig_lio_c_msgs__srv__CovertMap_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ig_lio_c_msgs__srv__CovertMap_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

// Struct defined in srv/CovertMap in the package ig_lio_c_msgs.
typedef struct ig_lio_c_msgs__srv__CovertMap_Response
{
  int32_t status;
  rosidl_runtime_c__String message;
} ig_lio_c_msgs__srv__CovertMap_Response;

// Struct for a sequence of ig_lio_c_msgs__srv__CovertMap_Response.
typedef struct ig_lio_c_msgs__srv__CovertMap_Response__Sequence
{
  ig_lio_c_msgs__srv__CovertMap_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ig_lio_c_msgs__srv__CovertMap_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__COVERT_MAP__STRUCT_H_
