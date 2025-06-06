#!/bin/bash
###
 # @Description: This is a ros-based project!
 # @Author: Qi Shiyu
 # @Date: 2025-01-02 22:20:13
 # @LastEditTime: 2025-05-05 15:23:45
 # @FigtPath: /TUP-Vision-2024-Based/WatchDog.sh
### 
export ROS_HOME="/home/sentry/Wolf-Moon"
cd /home/sentry/Wolf-Moon
# 设置需要启动和监视的ros命令
# declare -a commands=("ros2 launch armor_processor autoaim_bringup_launch.py ")
declare -a commands=(
                      "ros2 run hik_camera hik_camera_node"
                      "ros2 run armor_detector armor_detector_node"
                      # "ros2 run hik_camera hik_camera_node"
                      # "ros2 run buff_processor buff_processor_node"
                      # "ros2 run daheng_camera daheng_camera_node"
                      "ros2 run armor_processor armor_processor_node"
                      # "ros2 run rm_serial_port rm_serial_port_node"
                      )

# 定义函数来启动ros命令
start_commands() {
  for cmd in "${commands[@]}"
  do
	gnome-terminal -- bash -c "source /opt/intel/openvino_2022/setupvars.sh;source /opt/ros/galactic/setup.bash;cd $(pwd);source install/setup.bash;$cmd;exec bash;"
  done
}

# 定义函数来监视ros进程是否在运行
watch_commands() {
  while true
  do
    for cmd in "${commands[@]}"
    do
      process_name=$(echo $cmd | awk '{print $1}') # 提取进程名
      if ! pgrep -f "$cmd" > /dev/null
      then
        echo "$cmd 未在运行, 重新启动"
	gnome-terminal -- bash -c "source /opt/intel/openvino_2022/setupvars.sh;source /opt/ros/galactic/setup.bash;cd $(pwd);source install/setup.bash;$cmd;exec bash;"
      fi
    done
    sleep 1 # 设置睡眠时间，以便在下一次检查之前给进程足够的时间运行
  done
}





# 启动ros命令和监视进程
start_commands

watch_commands
