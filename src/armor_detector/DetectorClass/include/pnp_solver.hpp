#ifndef ARMOR_DETECTOR__PNP_SOLVER_HPP_
#define ARMOR_DETECTOR__PNP_SOLVER_HPP_
#include <geometry_msgs/msg/point.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <Eigen/Core>
#include <yaml-cpp/yaml.h>
#include <opencv2/core/eigen.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
// STD
#include <array>
#include <vector>
namespace rm_auto_aim
{
    class PnPSolver
    {
        cv::Mat camera_matrix_ = cv::Mat(3, 3, CV_64F);
        cv::Mat dist_coeffs_ = cv::Mat(1, 5, CV_64F);
        std::vector<cv::Point3d>
            big_armor_points_world_ = {
                {-0.1125, 0.027, 0},
                {-0.1125, -0.027, 0},
                {0.1125, -0.027, 0},
                {0.1125, 0.027, 0}};
        std::vector<cv::Point3d>
            small_armor_points_world_ = {
                {-0.066, 0.027, 0},
                {-0.066, -0.027, 0},
                {0.066, -0.027, 0},
                {0.066, 0.027, 0}};
        rclcpp::Logger logger_;
        rclcpp::Clock steady_clock_{RCL_STEADY_TIME};

    public:
        PnPSolver();
        ~PnPSolver();
        bool solvePnP(int target_type, std::vector<cv::Point2f> &image_armor_points, cv::Mat &rvec, cv::Mat &tvec);
        bool initMatrix(Eigen::MatrixXd &matrix, cv::FileNode vector);
        float calculateDistanceToCenter(const cv::Point2f &image_point);
    };
}
#endif