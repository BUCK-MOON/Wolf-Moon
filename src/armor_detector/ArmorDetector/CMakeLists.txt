###########
## cmake ##
###########
cmake_minimum_required(VERSION 3.10)
project(armor_detector)
## Use C++14
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
## By adding -Wall and -Werror, the compiler does not ignore warnings anymore,
## enforcing cleaner code.
set(CMAKE_BUILD_TYPE Release)

# add_definitions(-Wall -Werror -Wextra -Wpedantic -O3 -march=native -Ofast)
## Export compile commands for clangd-Werror
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




#######################
## Find dependencies ##
#######################
find_package(ament_cmake_auto REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(angles REQUIRED)
find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(auto_aim_interfaces REQUIRED)

# find_package(shm_msgs REQUIRED)
# find_package(shm_class REQUIRED)

find_package(OpenVINO REQUIRED)
# find_package(yaml-cpp REQUIRED)
find_package( OpenCL REQUIRED )
# find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
# include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
ament_auto_find_build_dependencies()


include_directories( ${OPENCL_INCLUDE_DIR} )

#########
## msg ##
#########





###########
## Build ##
###########
#添加C++文件
ament_auto_add_library(
    ${PROJECT_NAME} 
    SHARED
    DIRECTORY ../DetectorClass/src
)
##添加openvino头文件
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    /opt/intel/openvino_2022/runtime/include/
)
target_include_directories(
    ${PROJECT_NAME} 
    PUBLIC 
    ${OpenCV_INCLUDE_DIRS} 
    ${OpenVINO_INCLUDE_DIRS}
)
target_link_libraries(
    ${PROJECT_NAME} 
    ${OpenCV_LIBS} 
    ${OPENCL_LIBRARIES}
    pthread rt
    openvino::runtime
)
##
##添加依赖
set(dependencies 
        rclcpp
        rclcpp_components
        rclpy
        OpenCV 
        message_filters 
        image_transport
        sensor_msgs
        OpenVINO
        angles
        Boost
        openCL
        Ceres
        shm_msgs
        auto_aim_interfaces
        Eigen3
        shm_class
        cv_bridge
)
##########
## node ##
##########
rclcpp_components_register_node(
    ${PROJECT_NAME}
    PLUGIN "rm_auto_aim::DetectorNode"
    EXECUTABLE armor_detector_node
)


# 注册 导出头文件
install(
  DIRECTORY ../DetectorClass/include/
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



#############
## Install ##
#############
ament_auto_package(
    INSTALL_TO_SHARE
    config
    model
)
