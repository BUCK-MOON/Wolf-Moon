#include <iostream>
#include <opencv2/opencv.hpp>
// ROS
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <camera_info_manager/camera_info_manager.hpp>
#include <image_transport/image_transport.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <rmw/qos_profiles.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <rclcpp/duration.hpp>
#include <rclcpp/qos.hpp>
// C++ system
#include <memory>
#include <string>
#include <thread>
#include <vector>
#include <chrono>
#include <variant>

// #define SHM

using namespace std;
using namespace cv;

#ifndef SHM
VideoCapture capture;
FileStorage config;

namespace USB
{
    class USBCameraNode : public rclcpp::Node
    {
    public:
        std::string camera_name_;
        std::string videoPath;
        bool useCamera;
        bool flag = false;
        int cameraID;
        int sleep_time;
        sensor_msgs::msg::Image image_msg_;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;

        USBCameraNode(const rclcpp::NodeOptions &options) : Node("usb_camera", options)
        {
            // 设置程序节点名
            camera_name_ = this->declare_parameter("camera_name", "usb_camera");
            std::string packagePath = ament_index_cpp::get_package_share_directory("usb_camera");
            std::string filePath = packagePath + "/config/config.yaml";
            RCLCPP_INFO(this->get_logger(), "-> open file %s ", filePath.c_str());

            // config["useQos"] >> use_qos;
            rclcpp::QoS qos(0);
            qos.keep_last(5);
            qos.durability();
            qos.reliable();
            // 输出日志
            img_pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_raw", qos);
            RCLCPP_INFO(this->get_logger(), "Starting USBCameraNode");
            // 声明相机配置文件地址
            // 判断文件是否存在

            image_msg_.header.frame_id = "camera_optical_frame";
            image_msg_.encoding = "rgb8";
            while (rclcpp::ok())
            {
                Mat Src;
                config.open(filePath, FileStorage::READ);
                config["useCamera"] >> useCamera;
                config["sleepTime"] >> sleep_time;
                capture >> Src;
                if (!useCamera)
                {
                    config["videoPath"] >> videoPath;
                    if (flag)
                    {
                        // capture.release();
                        RCLCPP_INFO(this->get_logger(), "-> open video-> %s ", videoPath.c_str());
                        capture.open(videoPath);
                        flag = false;
                    }

                    if (Src.empty())
                    {
                        // capture.release();
                        RCLCPP_INFO(this->get_logger(), "-> open video-> %s ", videoPath.c_str());
                        capture.open(videoPath);
                    }
                }
                else
                {
                    if (!flag)
                    {
                        //  capture.release();
                        config["cameraID"] >> cameraID;
                        RCLCPP_INFO(this->get_logger(), "-> open camera->");
                        capture.open(cameraID);
                        flag = true;
                    }
                }
                if (!Src.empty())
                {
                    std::chrono::milliseconds duration(sleep_time); // 停顿一毫秒

                    std::this_thread::sleep_for(duration);
                    cv::resize(Src, Src, cv::Size(640, 480));

                    image_msg_.header.stamp = this->get_clock()->now();
                    image_msg_.data.assign(Src.datastart, Src.dataend);
                    image_msg_.height = Src.rows;
                    image_msg_.width = Src.cols;
                    image_msg_.step = Src.cols * 3;
                    image_msg_.data.resize(Src.rows * Src.cols * 3);
                    img_pub_->publish(image_msg_);
                }
            }
        }
    };
};
#endif
#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(USB::USBCameraNode)
