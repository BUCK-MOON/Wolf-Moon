#ifndef ARMOR_DETECTOR__ARMOR_DETECTOR_HPP_
#define ARMOR_DETECTOR__ARMOR_DETECTOR_HPP_
// std
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>
// ros
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <rmw/qos_profiles.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2/convert.h>
#include <fstream>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
// msg
#include "auto_aim_interfaces/msg/armors.hpp"
#include "auto_aim_interfaces/msg/armor.h"
#include "auto_aim_interfaces/msg/state.hpp"
#include "pnp_solver.hpp"
#include "inference.hpp"
namespace rm_auto_aim
{

    struct Tally
    {
        cv::Rect_<float> rect;
        double sum = 0;
        double num = 0;
    };

    class ArmorDetector
    {

        std::vector<ArmorObject> objects_;
        std::unique_ptr<PnPSolver> pnp_solver_;
        std::unique_ptr<Detector> detector_;
        std::string netWork_ = "/model/yolox_armor3.xml";

        cv::Mat input_;
        cv::Mat rvec_, tvec_;
        cv::Point2f apex2d_[4];
        auto_aim_interfaces::msg::Armor armor_msg_;

        // 帧率计算
        std::chrono::steady_clock::time_point start_time_, now_time_;
        std::chrono::duration<double> elapsed_time_;
        double frame_rate_ = 0;
        int frame_rate_flag_ = 0;

        std::vector<int> armors_id_; // 灰色装甲板识别相关
        std::vector<Tally> armor_tally_;

        rclcpp::Logger logger_;
        rclcpp::Clock steady_clock_{RCL_STEADY_TIME};

        std::map<std::string, double> dictionary; // 调控相关

    public:
        ArmorDetector();
        ~ArmorDetector();
        void drawArmor(cv::Point2f apex2d[4], cv::Mat src, cv::Point2f center);
        bool detectArmors(cv::Mat &src, auto_aim_interfaces::msg::Armors &armors_msg_);
        void initConfig();
        std::vector<cv::Point2f> fillArmor(cv::Point2f apex2d[4]);
        bool drawState(cv::Mat &src, auto_aim_interfaces::msg::State &state_msg_);
        void showImage(cv::Mat &src);
        void drawFrameRate(cv::Mat &src);
    };
}
#endif