// #define HERO
#ifndef ARMOR_PROCESSOR__ARMOR_PROCESSOR_HPP_
#define ARMOR_PROCESSOR__ARMOR_PROCESSOR_HPP_
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include "auto_aim_interfaces/msg/armors.hpp"
#include "auto_aim_interfaces/msg/armor.hpp"
#include "auto_aim_interfaces/msg/gimbal.hpp"
#include "auto_aim_interfaces/msg/state.hpp"
// #include <rclcpp/rclcpp.hpp>
// #include "matplotlibcpp.h"
#include <math.h>
#include <string>
#include <opencv2/opencv.hpp>
#include <Eigen/Core>
// Eigen
#include <Eigen/Dense>
#include <Eigen/Core>
#include "ballistic_processor.hpp"
#include "extension_tools.hpp"
#include "armor_tracker/armor_tracker.hpp"
// namespace plt = matplotlibcpp;
namespace rm_auto_aim
{
    using Gimbal = auto_aim_interfaces::msg::Gimbal;
    using Armors = auto_aim_interfaces::msg::Armors;
    using Armor = auto_aim_interfaces::msg::Armor;
    using State = auto_aim_interfaces::msg::State;
    using MarkerArrary = visualization_msgs::msg::MarkerArray;
    struct Mission
    {
        int mode;
        int change;
        Eigen::Quaterniond quat;
        Eigen::Matrix3d rmat;
        int64_t timestamp;
        double bullet_speed;
        double shoot_delay;
    };

    class ArmorProcessor // 主要功能类
    {
        std::unique_ptr<BallisticProcessor> ballistic_processor_; // 坐标系转化类
        std::unique_ptr<Tracker> tracker_;                        // 追踪类
        std::unique_ptr<SphericalKalmanFilter> skf_;              // 追踪类，用于装甲板丢失时平滑下降
        rclcpp::Logger logger_;
        rclcpp::Clock steady_clock_{RCL_STEADY_TIME};
        std::vector<double> plot_[9];
        // state_msg
        Eigen::Vector2d angle_, predict_;
        cv::Point2f calculate_;

        // tracker
        rclcpp::Time last_time_;
        double lost_time_thres_;
        double dt_;
        double s2qxyz_, s2qyaw_, s2qr_; // Armor tracker
        double r_xyz_factor, r_yaw;
        visualization_msgs::msg::Marker armor_marker_;
        visualization_msgs::msg::Marker center_marker_;
        visualization_msgs::msg::Marker warmor_marker_;
        visualization_msgs::msg::Marker wcenter_marker_;

    public:
        std::map<std::string, double> dictionary; // 调控相关

        ArmorProcessor();
        bool processArmors(Gimbal &gimbal_msg, Mission &mission, Armors &armors_msg, State &state_msg); // 主进程函数
        bool transformArmor(Armor &armor_msg, Mission &mission);
        void sloveMeasurement(Gimbal &gimbal_msg, Mission &mission);
        void sloveState(Gimbal &gimbal_msg, Mission &mission);
        bool initTracker();
        void initConfig();
        //向前端发送的可视化
        void getState(State &src, Mission &mission); // matplotlib
        void getXYZ(State &src, Eigen::Vector3d &xyz, Eigen::Matrix3d &rmat_imu);
        //向rviz发送的可视化
        void initMarker();
        void processMarkers(visualization_msgs::msg::MarkerArray &markers_msg);
    };
}
#endif