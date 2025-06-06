
#ifndef ARMOR_PROCESSOR__PROCESSOR_NODE_HPP_
#define ARMOR_PROCESSOR__PROCESSOR_NODE_HPP_
#include <iostream>

// ros相关
#include <rclcpp/rclcpp.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/msg/image.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <image_transport/publisher.hpp>
#include <image_transport/image_transport.hpp>
#include <image_transport/subscriber_filter.hpp>
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
// std命名空间下
#include <mutex>
#include <atomic>
#include <thread>
#include <opencv2/opencv.hpp>
// 自定义头文件
#include "auto_aim_interfaces/msg/armors.hpp"
#include "auto_aim_interfaces/msg/armor.hpp"
#include "auto_aim_interfaces/msg/serial.hpp"
#include "auto_aim_interfaces/msg/gimbal.hpp"
#include "armor_processor.hpp"
using namespace message_filters;
using namespace ament_index_cpp;
// using namespace std::placeholders;
namespace rm_auto_aim
{
    class ProcessorNode : public rclcpp::Node
    {
        rclcpp::Subscription<auto_aim_interfaces::msg::Armors>::SharedPtr armor_msg_sub_;
        rclcpp::Publisher<auto_aim_interfaces::msg::Gimbal>::SharedPtr gimbal_msg_pub_;       // 云台消息
        rclcpp::Publisher<auto_aim_interfaces::msg::State>::SharedPtr state_msg_pub_;         // 可视消息
        rclcpp::Subscription<auto_aim_interfaces::msg::Serial>::SharedPtr serial_msg_sub_;    // 串口接收者
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_array_pub_; // rviz消息
        std::recursive_mutex serial_msg_mutex_;                                               // 线程锁
        std::recursive_mutex state_msg_mutex_;                                               // 线程锁
        auto_aim_interfaces::msg::Armors armors_msg_;                                         // 接收消息
        auto_aim_interfaces::msg::Gimbal gimbal_msg_;                                         // 发布消息
        auto_aim_interfaces::msg::State state_msg_;                                           // 可视消息
        // 消息同步
        std::deque<auto_aim_interfaces::msg::Serial> serial_msg_deque_; // 收集串口陀螺仪数据
        // 消息同步
        visualization_msgs::msg::MarkerArray markers_msg_; // 可视化消息
        std::unique_ptr<ArmorProcessor> armor_processor_;  // 功能类
        Mission mission_;                                  // 结构体
    public:
        explicit ProcessorNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
        ~ProcessorNode();
        void sensorMsgCallback(const auto_aim_interfaces::msg::Serial &serial_msg);
        void targetMsgCallback(const auto_aim_interfaces::msg::Armors ::ConstSharedPtr armor_msg);
    };
}
#endif