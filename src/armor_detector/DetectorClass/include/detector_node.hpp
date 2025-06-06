#ifndef ARMOR_DETECTOR__DETECTOR_NODE_HPP_
#define ARMOR_DETECTOR__DETECTOR_NODE_HPP_
// ROS
#include <image_transport/image_transport.hpp>
#include <image_transport/publisher.hpp>
#include <image_transport/subscriber_filter.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <rclcpp/duration.hpp>
#include <rclcpp/qos.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <cv_bridge/cv_bridge.h>
#include <rmw/qos_profiles.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/convert.h>
#include <ament_index_cpp/get_package_share_directory.hpp>

// STD
#include <memory>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <opencv2/opencv.hpp>
#include <opencv2/core/eigen.hpp>
#include <algorithm>
#include <map>
//
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "auto_aim_interfaces/msg/armors.hpp"
#include "auto_aim_interfaces/msg/armor.hpp"
//
#include "armor_detector.hpp"
// #define SHM
// #define MATCH
#ifdef SHM
#include "../../../camera_drive/camera_shm/shm_sdk/shm_video_transmission.h"
#endif
namespace rm_auto_aim
{
    class DetectorNode : public rclcpp::Node
    {
    public:
        explicit DetectorNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
        ~DetectorNode();

    private:
        std::unique_ptr<ArmorDetector> armor_detector_;
        cv::Mat src_;
        auto_aim_interfaces::msg::Armors armors_msg_; // Detected armors publisher
        auto_aim_interfaces::msg::State state_msg_;
        std::recursive_mutex state_msg_mutex_; // 线程锁

#ifdef SHM
        shm_video_trans::FrameBag receivedFrame_;
        std::shared_ptr<shm_video_trans::VideoReceiver> receiver_;
        std::shared_ptr<std::thread> imageloop_;
        void imageLoop();
#endif

#ifndef SHM
        void imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr img_msg);
        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
#endif

        void stateCallback(const auto_aim_interfaces::msg::State &state_msg);
        rclcpp::Publisher<auto_aim_interfaces::msg::Armors>::SharedPtr armors_pub_;
        rclcpp::Subscription<auto_aim_interfaces::msg::State>::SharedPtr state_sub_;
    };
} // namespace rm_auto_aim
#endif // ARMOR_DETECTOR__DETECTOR_NODE_HPP_