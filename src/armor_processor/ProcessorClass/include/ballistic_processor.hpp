#ifndef ARMOR_PROCESSOR__BALLSITC_PROCESSOR_HPP_
#define ARMOR_PROCESSOR__BALLSTIC_PROCESSOR_HPP_

#include <Eigen/Core>
#include <Eigen/Dense>

#include <opencv2/core/eigen.hpp>
#include <yaml-cpp/yaml.h>
#include <rclcpp/rclcpp.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
namespace rm_auto_aim
{

    class BallisticProcessor
    {
        Eigen::Matrix4d T_ci_;
        Eigen::Matrix4d T_ic_; // 转移矩阵
        Eigen::Vector3d T_iw_; // 补偿向量
        Eigen::Matrix3d T_cc_; // 相机参数

    public:
        Eigen::Vector2d angle_offset;
        Eigen::Vector3d xyz_offset;
        int max_iter = 10;
        int R_K_iter = 50;
        float stop_error = 0.001;
        const double k = 0.01903; // 25°C,1atm,小弹丸
        // const double k = 0.00556;                //25°C,1atm,大弹丸
        // const double k = 0.00530;                //25°C,1atm,发光大弹丸
        const double g = 9.781;
        double bullet_speed = 22.0;
        BallisticProcessor();
        bool initMatrix(Eigen::MatrixXd &matrix, cv::FileNode vector);
        cv::Point2f reproject(Eigen::Vector3d &xyz);
        Eigen::Vector3d worldToCam(const Eigen::Vector3d &point_world, const Eigen::Matrix3d &rmat);
        Eigen::Vector3d camToWorld(const Eigen::Vector3d &point_camera, const Eigen::Matrix3d &rmat);
        Eigen::Matrix3d camToWorld(const Eigen::Matrix3d &martirx_camera, const Eigen::Matrix3d &rmat);
        Eigen::Vector2d getAttitude(Eigen::Vector3d &xyz, Eigen::Matrix3d &rmat);
        inline double gainBallisticPitch(Eigen::Vector3d &xyz);
        inline Eigen::Vector2d gainAngle(Eigen::Vector3d &xyz_cam);
        inline double gainYaw(Eigen::Vector3d &xyz);
        inline double gainPitch(Eigen::Vector3d &xyz);
    };
}
#endif