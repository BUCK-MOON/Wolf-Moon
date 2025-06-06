#!/bin/bash
export ROS_HOME="/home/sentry/Wolf-Moon"
cd /home/sentry/Wolf-Moon
# 设置需要启动和监视的ros命令
declare -a commands=(
                    "ros2 launch sentry_decision_v2 launch.py"
                    "ros2 launch livox_ros_driver2 msg_MID360_launch.py"
                    "ros2 launch ig_lio_c map_mapping_launch.py"
                    # "ros2 bag record -o bag /livox/imu /livox/lidar"
                    "ros2 run navigation_planning way_planner_node"
                    "rviz2"
                    # "ros2 run hik_camera hik_camera_node"
                    # "ros2 run armor_detector armor_detector_node"
                    # "ros2 run armor_processor armor_processor_node"
                    "ros2 run rm_serial_port rm_serial_port_node"
                    )

# 定义函数来启动ros命令
start_commands() {
  echo "7" | sudo -S  ifconfig lo multicast
  for cmd in "${commands[@]}"
  do
	gnome-terminal -- bash -c "export LD_LIBRARY_PATH=/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/lib:$LD_LIBRARY_PATH;source /home/sentry/.bashrc;source install/setup.bash;$cmd;exec bash;"
  done
}

# 定义函数来监视ros进程是否在运行
watch_commands() {
  while true
  do
    for cmd in "${commands[@]}"
    do
      process_name=$(echo $cmd | awk '{print $1}') # 提取进程名
      pgrep -f "$cmd"
      if ! pgrep -f "$cmd" > /dev/null
      then
        echo "$cmd 未在运行, 重新启动"
	gnome-terminal -- bash -c "export LD_LIBRARY_PATH=/home/sentry/Wolf-Moon/src/ThirdParty/OCTOMAP/lib:$LD_LIBRARY_PATH;source /home/sentry/.bashrc;source install/setup.bash;$cmd;exec bash;"
      fi
    done
    sleep 5 # 设置睡眠时间，以便在下一次检查之前给进程足够的时间运行
  done
}

# 启动ros命令和监视进程
start_commands
watch_commands


