cmake_minimum_required(VERSION 3.8)
project(navigation_planning)
set(CMAKE_BUILD_TYPE Release)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()


find_package(ament_cmake REQUIRED COMPONENTS)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(nav2_msgs REQUIRED)
find_package(nav2_costmap_2d REQUIRED)
find_package(OpenCV REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)
find_package(grid_map_msgs REQUIRED)
find_package(grid_map_core REQUIRED)
find_package(grid_map_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)



set(dependencies
  rclcpp
  rclcpp_components
  tf2
  tf2_ros
  nav2_msgs
  nav2_costmap_2d
  OpenCV
  yaml_cpp_vendor
  grid_map_msgs
  grid_map_core
  grid_map_ros
  tf2_geometry_msgs
)

include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${EIGEN3_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


set(sources_planner_node
  src/way_planner_node.cpp
)

add_executable(way_planner_node
  ${sources_planner_node}
)
ament_target_dependencies(way_planner_node
  ${dependencies}
)

target_link_libraries(way_planner_node
  ${Eigen3_LIBRARIES}
)

install(TARGETS
way_planner_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  map
  config
  DESTINATION share/${PROJECT_NAME}
)
ament_package()