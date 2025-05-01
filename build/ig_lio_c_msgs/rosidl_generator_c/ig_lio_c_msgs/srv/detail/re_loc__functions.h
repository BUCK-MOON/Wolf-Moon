// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from ig_lio_c_msgs:srv/ReLoc.idl
// generated code does not contain a copyright notice

#ifndef IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__FUNCTIONS_H_
#define IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "ig_lio_c_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "ig_lio_c_msgs/srv/detail/re_loc__struct.h"

/// Initialize srv/ReLoc message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ig_lio_c_msgs__srv__ReLoc_Request
 * )) before or use
 * ig_lio_c_msgs__srv__ReLoc_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__init(ig_lio_c_msgs__srv__ReLoc_Request * msg);

/// Finalize srv/ReLoc message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Request__fini(ig_lio_c_msgs__srv__ReLoc_Request * msg);

/// Create srv/ReLoc message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ig_lio_c_msgs__srv__ReLoc_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
ig_lio_c_msgs__srv__ReLoc_Request *
ig_lio_c_msgs__srv__ReLoc_Request__create();

/// Destroy srv/ReLoc message.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Request__destroy(ig_lio_c_msgs__srv__ReLoc_Request * msg);

/// Check for srv/ReLoc message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__are_equal(const ig_lio_c_msgs__srv__ReLoc_Request * lhs, const ig_lio_c_msgs__srv__ReLoc_Request * rhs);

/// Copy a srv/ReLoc message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__copy(
  const ig_lio_c_msgs__srv__ReLoc_Request * input,
  ig_lio_c_msgs__srv__ReLoc_Request * output);

/// Initialize array of srv/ReLoc messages.
/**
 * It allocates the memory for the number of elements and calls
 * ig_lio_c_msgs__srv__ReLoc_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__init(ig_lio_c_msgs__srv__ReLoc_Request__Sequence * array, size_t size);

/// Finalize array of srv/ReLoc messages.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__fini(ig_lio_c_msgs__srv__ReLoc_Request__Sequence * array);

/// Create array of srv/ReLoc messages.
/**
 * It allocates the memory for the array and calls
 * ig_lio_c_msgs__srv__ReLoc_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
ig_lio_c_msgs__srv__ReLoc_Request__Sequence *
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__create(size_t size);

/// Destroy array of srv/ReLoc messages.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__destroy(ig_lio_c_msgs__srv__ReLoc_Request__Sequence * array);

/// Check for srv/ReLoc message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__are_equal(const ig_lio_c_msgs__srv__ReLoc_Request__Sequence * lhs, const ig_lio_c_msgs__srv__ReLoc_Request__Sequence * rhs);

/// Copy an array of srv/ReLoc messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Request__Sequence__copy(
  const ig_lio_c_msgs__srv__ReLoc_Request__Sequence * input,
  ig_lio_c_msgs__srv__ReLoc_Request__Sequence * output);

/// Initialize srv/ReLoc message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * ig_lio_c_msgs__srv__ReLoc_Response
 * )) before or use
 * ig_lio_c_msgs__srv__ReLoc_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__init(ig_lio_c_msgs__srv__ReLoc_Response * msg);

/// Finalize srv/ReLoc message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Response__fini(ig_lio_c_msgs__srv__ReLoc_Response * msg);

/// Create srv/ReLoc message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * ig_lio_c_msgs__srv__ReLoc_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
ig_lio_c_msgs__srv__ReLoc_Response *
ig_lio_c_msgs__srv__ReLoc_Response__create();

/// Destroy srv/ReLoc message.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Response__destroy(ig_lio_c_msgs__srv__ReLoc_Response * msg);

/// Check for srv/ReLoc message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__are_equal(const ig_lio_c_msgs__srv__ReLoc_Response * lhs, const ig_lio_c_msgs__srv__ReLoc_Response * rhs);

/// Copy a srv/ReLoc message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__copy(
  const ig_lio_c_msgs__srv__ReLoc_Response * input,
  ig_lio_c_msgs__srv__ReLoc_Response * output);

/// Initialize array of srv/ReLoc messages.
/**
 * It allocates the memory for the number of elements and calls
 * ig_lio_c_msgs__srv__ReLoc_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__init(ig_lio_c_msgs__srv__ReLoc_Response__Sequence * array, size_t size);

/// Finalize array of srv/ReLoc messages.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__fini(ig_lio_c_msgs__srv__ReLoc_Response__Sequence * array);

/// Create array of srv/ReLoc messages.
/**
 * It allocates the memory for the array and calls
 * ig_lio_c_msgs__srv__ReLoc_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
ig_lio_c_msgs__srv__ReLoc_Response__Sequence *
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__create(size_t size);

/// Destroy array of srv/ReLoc messages.
/**
 * It calls
 * ig_lio_c_msgs__srv__ReLoc_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
void
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__destroy(ig_lio_c_msgs__srv__ReLoc_Response__Sequence * array);

/// Check for srv/ReLoc message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__are_equal(const ig_lio_c_msgs__srv__ReLoc_Response__Sequence * lhs, const ig_lio_c_msgs__srv__ReLoc_Response__Sequence * rhs);

/// Copy an array of srv/ReLoc messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_ig_lio_c_msgs
bool
ig_lio_c_msgs__srv__ReLoc_Response__Sequence__copy(
  const ig_lio_c_msgs__srv__ReLoc_Response__Sequence * input,
  ig_lio_c_msgs__srv__ReLoc_Response__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // IG_LIO_C_MSGS__SRV__DETAIL__RE_LOC__FUNCTIONS_H_
