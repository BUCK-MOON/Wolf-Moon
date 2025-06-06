cmake_minimum_required(VERSION 3.10)
project(daheng_camera)

## Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)

add_definitions(-Wall -Werror -Wextra -Wpedantic -O3)
## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.

## Export compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#######################
## Find dependencies ##
#######################

find_package(ament_cmake_auto REQUIRED)
find_package(OpenCV REQUIRED)
ament_auto_find_build_dependencies()

###########
## Build ##
###########

ament_auto_add_library(${PROJECT_NAME} SHARED
  src/daheng_camera_node.cpp
)
target_include_directories(${PROJECT_NAME} PUBLIC daheng_sdk)
target_include_directories(${PROJECT_NAME} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
  target_link_directories(${PROJECT_NAME} PUBLIC daheng_sdk/lib/amd64)
# elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
#   target_link_directories(${PROJECT_NAME} PUBLIC daheng_sdk/lib/arm64)
else()
  message(FATAL_ERROR "Unsupport host system architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}!")
endif()

target_link_libraries(${PROJECT_NAME} gxiapi)

rclcpp_components_register_node(${PROJECT_NAME}
  PLUGIN daheng_camera::DaHengCameraNode
  EXECUTABLE ${PROJECT_NAME}_node
)

#############
## Testing ##
#############

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  list(APPEND AMENT_LINT_AUTO_EXCLUDE
    ament_cmake_copyright
    ament_cmake_cpplint
    ament_cmake_uncrustify
  )
  ament_lint_auto_find_test_dependencies()

  set(_linter_excludes
    daheng_sdk/include/DxImageProc.h
    daheng_sdk/include/GxIAPI.h
  )
  ament_cpplint(EXCLUDE ${_linter_excludes})
endif()

# ############
# # Install ##
# ############


ament_auto_package(
  INSTALL_TO_SHARE
  config
  # launch
)
##########
##config##
# ##########
# set(original_filename "config")  # 假设原始文件在当前CMakeLists.txt的同级目录下，并命名为"config"
# # 获取原始文件的绝对路径
# get_filename_component(
#   original_path 
#   ${CMAKE_CURRENT_SOURCE_DIR}/${original_filename} ABSOLUTE
# )
# # 安装文件到包的share文件夹中
# install(
#   CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
#   ${original_path} 
#   \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/${original_filename})"
# )
