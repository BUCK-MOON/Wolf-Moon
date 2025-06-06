#include "../include/ballistic_processor.hpp"
namespace rm_auto_aim
{
    /**
     * @brief 初始化，参数
     */
    BallisticProcessor::BallisticProcessor()
    {
        auto pkg_path = ament_index_cpp::get_package_share_directory("armor_processor"); // 读取相机参数
        std::string coord_path = pkg_path + "/config/info_config.yaml";
        cv::FileStorage config(coord_path, cv::FileStorage::READ);

        auto read_vector = config["T_ci"]; // 车向imu转
        Eigen::MatrixXd mat_ci(4, 4);
        initMatrix(mat_ci, read_vector);
        T_ci_ = mat_ci;
        read_vector = config["T_ic"]; // imu向车转
        Eigen::MatrixXd mat_ic(4, 4);
        initMatrix(mat_ic, read_vector);
        T_ic_ = mat_ic;
        read_vector = config["T_iw"]; // imu向世界偏移向量
        Eigen::MatrixXd mat_iw(1, 3);
        initMatrix(mat_iw, read_vector);
        T_iw_ = mat_iw.transpose();
        read_vector = config["T_cc"];
        Eigen::MatrixXd mat_cam(3, 3);
        initMatrix(mat_cam, read_vector);
        T_cc_ = mat_cam;
        config.release();
    }
    /**
     * @brief 初始化矩阵
     */
    bool BallisticProcessor::initMatrix(Eigen::MatrixXd &matrix, cv::FileNode vector)
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

    Eigen::Vector3d BallisticProcessor::worldToCam(const Eigen::Vector3d &point_world, const Eigen::Matrix3d &rmat)
    {
        Eigen::Vector4d point_camera_tmp;
        Eigen::Vector4d point_imu_tmp;
        Eigen::Vector3d point_imu;
        Eigen::Vector3d point_camera;

        point_imu = rmat.transpose() * point_world;
        point_imu += T_iw_;
        point_imu_tmp << point_imu[0], point_imu[1], point_imu[2], 1;
        point_camera_tmp = T_ci_ * point_imu_tmp;
        point_camera << point_camera_tmp[0], point_camera_tmp[1], point_camera_tmp[2];

        return point_camera;
    }
    /**
     * @brief 相机坐标系转到世界坐标系
     * @param T_ic imu转到车辆坐标系
     */
    Eigen::Vector3d BallisticProcessor::camToWorld(const Eigen::Vector3d &point_camera, const Eigen::Matrix3d &rmat)
    {
        Eigen::Vector4d point_camera_tmp;
        Eigen::Vector4d point_imu_tmp;
        Eigen::Vector3d point_imu;
        Eigen::Vector3d point_world;

        point_camera_tmp << point_camera[0], point_camera[1], point_camera[2], 1;
        point_imu_tmp = T_ic_ * point_camera_tmp;
        point_imu << point_imu_tmp[0], point_imu_tmp[1], point_imu_tmp[2];
        point_imu -= T_iw_;
        return rmat * point_imu;
    }

    Eigen::Matrix3d BallisticProcessor::camToWorld(const Eigen::Matrix3d &martirx_camera, const Eigen::Matrix3d &rmat)
    {
        Eigen::Matrix3d R_ic = T_ic_.block<3, 3>(0, 0);
        Eigen::Matrix3d R_im = R_ic * martirx_camera;
        return rmat * R_im;
    }

    cv::Point2f BallisticProcessor::reproject(Eigen::Vector3d &xyz)
    {
        auto result = (1.f / xyz[2]) * T_cc_ * (xyz); // 解算前进行单位转换
        return cv::Point2f(result[0], result[1]);
    }

    Eigen::Vector2d BallisticProcessor::getAttitude(Eigen::Vector3d &xyz_cam, Eigen::Matrix3d &rmat)
    {
        Eigen::Vector3d xyz = xyz_cam + xyz_offset;
        auto xyz_world = camToWorld(xyz, rmat);
        auto angle_cam = gainAngle(xyz);
        auto pitch_offset = gainBallisticPitch(xyz_world);
        angle_cam[1] = angle_cam[1] + pitch_offset;
        angle_cam += angle_offset;

        return angle_cam ;
        ;
    }

    inline double BallisticProcessor::gainBallisticPitch(Eigen::Vector3d &xyz)
    {
        // TODO:根据陀螺仪安装位置调整距离求解方式
        // 降维，坐标系Y轴以垂直向上为正方向
        auto dist_vertical = xyz[2];
        auto vertical_tmp = dist_vertical;
        auto dist_horizonal = sqrt(xyz.squaredNorm() - dist_vertical * dist_vertical);
        // auto dist_vertical = xyz[2];
        // auto dist_horizonal = sqrt(xyz.squaredNorm() - dist_vertical * dist_vertical);
        double pitch = atan(dist_vertical / dist_horizonal) * 180 / CV_PI;
        auto pitch_new = pitch;
        // auto pitch_offset = 0.0;
        // 开始使用龙格库塔法求解弹道补偿
        for (int i = 0; i < max_iter; i++)
        {
            // R_K_iter = 50;
            // TODO:可以考虑将迭代起点改为世界坐标系下的枪口位置
            // 初始化
            auto x = 0.0;
            auto y = 0.0;
            auto p = tan(pitch_new / 180 * CV_PI);
            auto v = bullet_speed;
            auto u = v / sqrt(1 + pow(p, 2));
            auto delta_x = dist_horizonal / R_K_iter;
            for (int j = 0; j < R_K_iter; j++)
            {
                auto k1_u = -k * u * sqrt(1 + pow(p, 2));
                auto k1_p = -g / pow(u, 2);
                auto k1_u_sum = u + k1_u * (delta_x / 2);
                auto k1_p_sum = p + k1_p * (delta_x / 2);

                auto k2_u = -k * k1_u_sum * sqrt(1 + pow(k1_p_sum, 2));
                auto k2_p = -g / pow(k1_u_sum, 2);
                auto k2_u_sum = u + k2_u * (delta_x / 2);
                auto k2_p_sum = p + k2_p * (delta_x / 2);

                auto k3_u = -k * k2_u_sum * sqrt(1 + pow(k2_p_sum, 2));
                auto k3_p = -g / pow(k2_u_sum, 2);
                auto k3_u_sum = u + k3_u * (delta_x / 2);
                auto k3_p_sum = p + k3_p * (delta_x / 2);

                auto k4_u = -k * k3_u_sum * sqrt(1 + pow(k3_p_sum, 2));
                auto k4_p = -g / pow(k3_u_sum, 2);

                u += (delta_x / 6) * (k1_u + 2 * k2_u + 2 * k3_u + k4_u);
                p += (delta_x / 6) * (k1_p + 2 * k2_p + 2 * k3_p + k4_p);

                x += delta_x;
                y += p * delta_x;
            }
            // 评估迭代结果,若小于迭代精度需求则停止迭代
            auto error = dist_vertical - y;
            if (abs(error) <= stop_error)
            {
                break;
            }
            else
            {
                vertical_tmp += error;
                // xyz_tmp[1] -= error;
                pitch_new = atan(vertical_tmp / dist_horizonal) * 180 / CV_PI;
            }
        }
        return pitch_new - pitch;
    }
    inline Eigen::Vector2d BallisticProcessor::gainAngle(Eigen::Vector3d &xyz)
    {
        Eigen::Vector2d angle;
        // Yaw(逆时针)
        // Pitch(目标在上方为正)
        angle << gainYaw(xyz), gainPitch(xyz);
        return angle;
    }
    inline double BallisticProcessor::gainYaw(Eigen::Vector3d &xyz)
    {
        return atan2(xyz[0], xyz[2]) * 180 / CV_PI;
    }
    inline double BallisticProcessor::gainPitch(Eigen::Vector3d &xyz)
    {
        return -(atan2(xyz[1], sqrt(xyz[0] * xyz[0] + xyz[2] * xyz[2])) * 180 / CV_PI);
        // return (atan2(xyz[1], sqrt(xyz[0] * xyz[0] + xyz[2] * xyz[2])) * 180 / CV_PI);
    }

}