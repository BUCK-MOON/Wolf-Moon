// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from ig_lio_c_msgs:srv/CovertMap.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "ig_lio_c_msgs/srv/detail/covert_map__rosidl_typesupport_introspection_c.h"
#include "ig_lio_c_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "ig_lio_c_msgs/srv/detail/covert_map__functions.h"
#include "ig_lio_c_msgs/srv/detail/covert_map__struct.h"


// Include directives for member types
// Member `pcd_path`
// Member `map_file_name`
// Member `image_format`
// Member `map_mode`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ig_lio_c_msgs__srv__CovertMap_Request__init(message_memory);
}

void CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_fini_function(void * message_memory)
{
  ig_lio_c_msgs__srv__CovertMap_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_member_array[6] = {
  {
    "pcd_path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, pcd_path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_file_name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, map_file_name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "image_format",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, image_format),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "map_mode",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, map_mode),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "free_thresh",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, free_thresh),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "occupied_thresh",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Request, occupied_thresh),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_members = {
  "ig_lio_c_msgs__srv",  // message namespace
  "CovertMap_Request",  // message name
  6,  // number of fields
  sizeof(ig_lio_c_msgs__srv__CovertMap_Request),
  CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_member_array,  // message members
  CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_type_support_handle = {
  0,
  &CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ig_lio_c_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Request)() {
  if (!CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_type_support_handle.typesupport_identifier) {
    CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &CovertMap_Request__rosidl_typesupport_introspection_c__CovertMap_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "ig_lio_c_msgs/srv/detail/covert_map__rosidl_typesupport_introspection_c.h"
// already included above
// #include "ig_lio_c_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "ig_lio_c_msgs/srv/detail/covert_map__functions.h"
// already included above
// #include "ig_lio_c_msgs/srv/detail/covert_map__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  ig_lio_c_msgs__srv__CovertMap_Response__init(message_memory);
}

void CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_fini_function(void * message_memory)
{
  ig_lio_c_msgs__srv__CovertMap_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(ig_lio_c_msgs__srv__CovertMap_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_members = {
  "ig_lio_c_msgs__srv",  // message namespace
  "CovertMap_Response",  // message name
  2,  // number of fields
  sizeof(ig_lio_c_msgs__srv__CovertMap_Response),
  CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_member_array,  // message members
  CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_type_support_handle = {
  0,
  &CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ig_lio_c_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Response)() {
  if (!CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_type_support_handle.typesupport_identifier) {
    CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &CovertMap_Response__rosidl_typesupport_introspection_c__CovertMap_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "ig_lio_c_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "ig_lio_c_msgs/srv/detail/covert_map__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_members = {
  "ig_lio_c_msgs__srv",  // service namespace
  "CovertMap",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_Request_message_type_support_handle,
  NULL  // response message
  // ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_Response_message_type_support_handle
};

static rosidl_service_type_support_t ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_type_support_handle = {
  0,
  &ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_ig_lio_c_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap)() {
  if (!ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_type_support_handle.typesupport_identifier) {
    ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, ig_lio_c_msgs, srv, CovertMap_Response)()->data;
  }

  return &ig_lio_c_msgs__srv__detail__covert_map__rosidl_typesupport_introspection_c__CovertMap_service_type_support_handle;
}
