#include "../include/pnp_solver.hpp"
namespace rm_auto_aim
{
    PnPSolver::PnPSolver() : logger_(rclcpp::get_logger("armor_detector"))
    {
        std::cout<<"1"<<std::endl;

        auto pkg_path = ament_index_cpp::get_package_share_directory("armor_detector"); // 读取相机参数
        std::string coord_path = pkg_path + "/config/info_config.yaml";
        cv::FileStorage config(coord_path, cv::FileStorage::READ);
        std::cout<<"1"<<std::endl;

        config["Intrinsic_Matrix"] >> camera_matrix_; // 内参
        config["Distortion_Matrix"] >> dist_coeffs_;  // 畸变
        std::cout<<"1"<<std::endl;

        config.release();
        RCLCPP_INFO_THROTTLE(logger_, steady_clock_, 50,
                             "\033[1m\033[36minitialize info succeed...\033[0m");
    }
    PnPSolver::~PnPSolver()
    {
    }
    bool PnPSolver::initMatrix(Eigen::MatrixXd &matrix, cv::FileNode vector)
    {
        int cnt = 0;
        for (int row = 0; row < matrix.rows(); row++)
        {
            for (int col = 0; col < matrix.cols(); col++)
            {
                matrix(row, col) = vector[cnt];
                cnt++;
            }
        }
        return true;
    }
    bool PnPSolver::solvePnP(int target_type, std::vector<cv::Point2f> &image_armor_points, cv::Mat &rvec, cv::Mat &tvec)
    {
        auto object_points = target_type == 0 ? small_armor_points_world_ : big_armor_points_world_;
        cv::solvePnP(
            object_points, image_armor_points, camera_matrix_, dist_coeffs_, rvec, tvec, false,
            cv::SOLVEPNP_IPPE);
        return cv::solvePnP(object_points, image_armor_points, camera_matrix_, dist_coeffs_, rvec, tvec, true, cv::SOLVEPNP_ITERATIVE);
    }
    float PnPSolver::calculateDistanceToCenter(const cv::Point2f &image_point)
    {
        float cx = camera_matrix_.at<double>(0, 2);
        float cy = camera_matrix_.at<double>(1, 2);
        return cv::norm(image_point - cv::Point2f(cx, cy));
    }
}