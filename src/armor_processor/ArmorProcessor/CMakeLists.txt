#########
##cmake##
#########
cmake_minimum_required(VERSION 3.8)
project(armor_processor)
set(CMAKE_BUILD_TYPE Release)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_definitions(-Wall  -O3)

endif()




#####################
##find dependencies##
#####################
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclpy REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(OpenCV REQUIRED)
find_package(message_filters REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)
find_package(matplotlib_cpp REQUIRED)
find_package(image_transport REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(auto_aim_interfaces REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(angles REQUIRED)
# find_package(Python2 COMPONENTS Development)
# include_directories(${Python2_INCLUDE_DIRS})




#########
##build##
#########
set(dependencies 
      rclcpp
      rclpy 
      rclcpp_components
      message_filters
      Eigen3
      OpenCV
      Ceres
      angles
      image_transport
      sensor_msgs
      cv_bridge
      matplotlib_cpp
      # python2
      auto_aim_interfaces
      visualization_msgs
      tf2_geometry_msgs
      tf2_ros 
)
include_directories(
  include
  ${EIGEN3_INCLUDE_DIRS}
)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  /opt/ros/<distro>/include  # ROS系统头文件路径
  /usr/include/angles  # angles库头文件路径
)
add_library(
  ${PROJECT_NAME} 
  SHARED
  ../ProcessorClass/src/armor_processor.cpp
  ../ProcessorClass/src/ballistic_processor.cpp  
  ../ProcessorClass/src/armor_tracker/armor_tracker.cpp  
  ../ProcessorClass/src/extension_tools.cpp
  ../ProcessorClass/src/armor_tracker/extended_kalman_filter.cpp  

)
ament_target_dependencies(
  ${PROJECT_NAME} 
  ${dependencies} 
)
target_link_libraries(
  ${PROJECT_NAME}
    ceres
    glog 
    matplotlib_cpp::matplotlib_cpp
)




########
##node##
########
add_executable(
  ${PROJECT_NAME}_node 
  ../ProcessorClass/src/processor_node.cpp
)
ament_target_dependencies(
  ${PROJECT_NAME}_node 
  ${dependencies} 
)

target_link_libraries(
  ${PROJECT_NAME}_node 
  ${PROJECT_NAME} 
)
rclcpp_components_register_nodes(${PROJECT_NAME} 
  PLUGIN "rm_auto_aim::ProcessorNode"
  EXECUTABLE ${PROJECT_NAME}_node 
)

# 注册 导出头文件
install(
  DIRECTORY ../ProcessorClass/include/
  DESTINATION include
)

# 注册 导出库文件
install(
  TARGETS ${PROJECT_NAME} # 告诉ros2有这么个目标（可执行文件或者库）
  EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

install(DIRECTORY
  launch
  config
  DESTINATION share/${PROJECT_NAME}
)


##########
##config##
##########
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



# ##########
# ##launch##
# ##########
# set(original_launch "launch")  # 假设原始文件在当前CMakeLists.txt的同级目录下，并命名为"config"
# # 获取原始文件的绝对路径
# get_filename_component(
#   launch_path 
#   ${CMAKE_CURRENT_SOURCE_DIR}/${original_launch} ABSOLUTE
# )
# # 安装文件到包的share文件夹中
# install(
#   CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink 
#   ${launch_path} 
#   \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/${original_launch})"
# )


###########
##install##
###########
install(TARGETS 
  ${PROJECT_NAME}
  # EXPORT ${PROJECT_NAME}
  ARCHIVE DESTINATION lib 
  LIBRARY DESTINATION lib 
  RUNTIME DESTINATION lib 
  INCLUDES DESTINATION include
)
install(TARGETS
  ${PROJECT_NAME}_node 
  DESTINATION lib/${PROJECT_NAME}
)
# ament_auto_package(
#   INSTALL_TO_SHARE
#   config
# )


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
