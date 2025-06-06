// Copyright (c) 2022 ChenJun
// Licensed under the MIT License.

// MindVision Camera SDK
#include <CameraApi.h>

// ROS
#include <camera_info_manager/camera_info_manager.hpp>
#include <image_transport/image_transport.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
// C++ system
#include <memory>
#include <string>
#include <thread>
#include <vector>

namespace mindvision_camera
{
  class MVCameraNode : public rclcpp::Node
  {
  private:
    int i_camera_counts = 1;
    int i_status = -1;
    tSdkCameraDevInfo t_camera_enum_list;
    int h_camera_;
    uint8_t *pby_buffer_;
    tSdkCameraCapbility t_capability_; // 设备描述信息
    tSdkFrameHead s_frame_info_;       // 图像帧头信息
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;
    sensor_msgs::msg::Image image_msg_;

    // image_transport::CameraPublisher camera_pub_;

  public:
    explicit MVCameraNode(const rclcpp::NodeOptions &options) : Node("mindvs_camera", options)
    {
      RCLCPP_INFO(this->get_logger(), "Starting MVCameraNode!");
      CameraSdkInit(1);                                                        // 启动sdk
      i_status = CameraEnumerateDevice(&t_camera_enum_list, &i_camera_counts); // 遍历相机
      RCLCPP_INFO(this->get_logger(), "Enumerate state = %d", i_status);
      RCLCPP_INFO(this->get_logger(), "Found camera count = %d", i_camera_counts);
      i_status = CameraInit(&t_camera_enum_list, -1, -1, &h_camera_); // 相机初始化。初始化成功后，才能调用任何其他相机相关的操作接口
      // 获得相机的特性描述结构体。该结构体中包含了相机可设置的各种参数的范围信息。决定了相关函数的参数

      CameraGetCapability(h_camera_, &t_capability_);
      // 直接使用vector的内存作为相机输出buffer
      image_msg_.data.reserve(
          t_capability_.sResolutionRange.iHeightMax * t_capability_.sResolutionRange.iWidthMax * 3);

      // 设置手动曝光
      CameraSetAeState(h_camera_, false);
      // 让SDK进入工作模式，开始接收来自相机发送的图像
      // 数据。如果当前相机是触发模式，则需要接收到
      // 触发帧以后才会更新图像。
      CameraPlay(h_camera_);

      CameraSetIspOutFormat(h_camera_, CAMERA_MEDIA_TYPE_RGB8);
      rclcpp::QoS qos(0);
      qos.keep_last(5);
      qos.reliable();
      qos.transient_local();
      qos.durability_volatile();
      img_pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_raw", qos);
      image_msg_.header.frame_id = "right";
      image_msg_.encoding = "rgb8";
      while (rclcpp::ok())
      {
        int status = CameraGetImageBuffer(h_camera_, &s_frame_info_, &pby_buffer_, 1000);
        if (status == CAMERA_STATUS_SUCCESS)
        {
          CameraImageProcess(h_camera_, pby_buffer_, image_msg_.data.data(), &s_frame_info_);
          CameraFlipFrameBuffer(image_msg_.data.data(), &s_frame_info_, 3);
          cv::Mat Src = cv::Mat(s_frame_info_.iHeight, s_frame_info_.iWidth, CV_8UC3, image_msg_.data.data());
          // std::cout << "1" << std::endl;
          cv::cvtColor(Src,Src,cv::COLOR_BGR2RGB);
          cv::resize(Src, Src, cv::Size(640, 480));
          cv::flip(Src, Src, 0);
          // memcpy(Src.data, &s_frame_info_, s_frame_info_.iWidth * s_frame_info_.iHeight * 3);
          // imshow("src", Src);
          // image_msg_.height = s_frame_info_.iHeight;
          // image_msg_.width = s_frame_info_.iWidth;
          // image_msg_.step = s_frame_info_.iWidth * 3;
          // image_msg_.data.resize(s_frame_info_.iWidth * s_frame_info_.iHeight * 3);
          image_msg_.header.stamp = this->get_clock()->now();

          image_msg_.height = 480;
          image_msg_.width = 640;
          image_msg_.step = 640 * 3;
          image_msg_.data.resize(480 * 640 * 3);
          memcpy(image_msg_.data.data(), Src.data, 640 * 480 * 3);
          // std::cout << "1" << std::endl;
          img_pub_->publish(image_msg_);
          CameraReleaseImageBuffer(h_camera_, pby_buffer_);
        }
      }
    }
  };

} // namespace mindvision_camera

#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(mindvision_camera::MVCameraNode)
