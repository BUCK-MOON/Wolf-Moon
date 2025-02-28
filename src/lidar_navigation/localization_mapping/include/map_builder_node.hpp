#ifndef _MAP_BUILDER_NODE_HPP
#define _MAP_BUILDER_NODE_HPP
#include <map>
#include <mutex>
#include <vector>
#include <thread>
#include <csignal>
#include <rclcpp/rclcpp.hpp>
#include <chrono>
#include <boost/optional.hpp>

#include <gtsam/geometry/Rot3.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/nonlinear/ISAM2.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>

#include <pcl/io/pcd_io.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/filters/statistical_outlier_removal.h>

#include <nav_msgs/msg/path.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

#include <ig_lio_c_msgs/srv/save_map.hpp>
#include <ig_lio_c_msgs/srv/re_loc.hpp>

#include "./ig_lio_c/iglio_builder.h"
#include "./ig_lio_c/icp_localizer.h"

#include "../../OCTOMAP/octomap_mapping/include/octomapper.h"

namespace IG_LIO
{
    using namespace std::chrono;
    using std::placeholders::_1;
    using std::placeholders::_2;

    /**
     * @brief 循环对比
     */
    struct LoopPair
    {
        int pre_idx;
        int cur_idx;
        double score;
        Eigen::Matrix3d diff_rot;
        Eigen::Vector3d diff_pos;
        LoopPair(int p, int c, float s, Eigen::Matrix3d &dr, Eigen::Vector3d &dp)
            : pre_idx(p), cur_idx(c), score(s), diff_rot(dr), diff_pos(dp) {}
    };

    struct Pose6D
    {
        int index;                  // 表示位姿的索引
        double time;                // 记录对应位姿的时间戳
        Eigen::Matrix3d local_rot;  // 局部坐标系旋转矩阵
        Eigen::Vector3d local_pos;  // 局部坐标系位置向量
        Eigen::Matrix3d global_rot; // 全局坐标系旋转矩阵
        Eigen::Vector3d global_pos; // 全局坐标系位置向量

        Pose6D(int i, double t, Eigen::Matrix3d lr, Eigen::Vector3d lp)
            : index(i), time(t), local_rot(lr), local_pos(lp)
        {
        }

        /**
         * @brief 设置全局位姿。将全局旋转矩阵 gr 和全局位置 gp 设置到 global_rot 和 global_pos 中。
         */
        void setGlobalPose(const Eigen::Matrix3d &gr, const Eigen::Vector3d &gp)
        {
            global_rot = gr;
            global_pos = gp;
        }

        /**
         *@brief 根据给定的偏移量（旋转和位置），将局部位姿转换为全局位姿。
         *@brief 这个方法会将局部旋转矩阵 local_rot 和位置 local_pos 与偏移量一起计算出新的全局位姿。
         */
        void addOffset(const Eigen::Matrix3d &offset_rot, const Eigen::Vector3d &offset_pos)
        {
            global_rot = offset_rot * local_rot;
            global_pos = offset_rot * local_pos + offset_pos;
        }

        /**
         * 计算并返回从局部坐标系到全局坐标系的偏移量。
         * 这个方法通过全局旋转矩阵和局部旋转矩阵的关系来计算出旋转偏移量 offset_rot 和位置偏移量 offset_pos。
         */
        void getOffset(Eigen::Matrix3d &offset_rot, Eigen::Vector3d &offset_pos)
        {
            offset_rot = global_rot * local_rot.transpose();
            offset_pos = -global_rot * local_rot.transpose() * local_pos + global_pos;
        }
    };

    struct SharedData
    {
        bool key_pose_added = false;            // 关键位姿是否添加
        bool pose_updated = false;              // 是否更新了位姿
        bool localizer_activate = false;        // 定位器是否激活
        bool localizer_service_called = false;  // 服务是否在监听
        bool localizer_service_success = false; // 服务是否成功

        std::mutex service_mutex; // 服务互斥锁
        std::mutex mutex;         // 互斥锁

        /**
         * 不同坐标系的两种补偿
         */
        Eigen::Matrix3d offset_rot = Eigen::Matrix3d::Identity();
        Eigen::Vector3d offset_pos = Eigen::Vector3d::Zero();
        Eigen::Matrix3d offset_rot_loc = Eigen::Matrix3d::Identity();
        Eigen::Vector3d offset_pos_loc = Eigen::Vector3d::Zero();

        std::vector<Pose6D> key_poses;                          // 关键位姿的历史信息
        std::vector<LoopPair> loop_pairs;                       // 回环检测结果
        std::vector<std::pair<int, int>> loop_history;          // 回环历史记录
        std::vector<IG_LIO::PointCloudXYZI::Ptr> cloud_history; // 历史点云信息
        std::string map_path;                                   // 地图文件路径
        Eigen::Matrix3d local_rot;                              // 本地位姿
        Eigen::Vector3d local_pos;                              // 本地位姿
        Eigen::Matrix4d initial_guess;                          // 猜测位姿
        IG_LIO::PointCloudXYZI::Ptr cloud;                      // 当前点云数据

        bool reset_flag = false; // 重置
        bool halt_flag = false;  // 暂停
    };

    struct LoopParams
    {
        double rad_thresh = 0.4;               // 半径阈值
        double dist_thresh = 2.5;              // 距离阈值
        double time_thresh = 30.0;             // 时间阈值
        double loop_pose_search_radius = 10.0; // 回环检测的搜索半径
        int loop_pose_index_thresh = 5;        // 回环检测索引阈值
        double submap_resolution = 0.2;        // 子地图分辨率
        int submap_search_num = 20;            // 子地图搜索次数
        double loop_icp_thresh = 0.3;          // icp算法匹配质量阈值
        bool activate = false;                 // 循环检测功能是否激活
    };
    /**
     * @brief 回环检测
     * 用于处理回环检测，异步于主线程，通过shared_data共享数据
     * 通过比较当前帧与历史帧的相似性，检测是否发生了回环。
     * 使用GTSAM库进行图优化，校正机器人的位姿。
     * 通过SharedData类与主线程共享数据，确保回环检测的结果能够及时更新到主线程中。
     */
    class LoopClosureThread
    {
    private:
        std::shared_ptr<SharedData> shared_data_;//指向SharedData类的共享指针，用于与主线程共享数据。
        std::shared_ptr<rclcpp::Rate> rate_;//
        LoopParams loop_params_;//
        std::vector<Pose6D> temp_poses_;//
        int previous_index_ = 0;//
        int lastest_index_;//
        bool loop_found_ = false;//
        bool is_alive = true;//
        bool terminate_flag = false;//
        gtsam::Values initialized_estimate_;//
        gtsam::Values optimized_estimate_;//
        std::shared_ptr<gtsam::ISAM2> isam2_;//
        gtsam::NonlinearFactorGraph gtsam_graph_;//
        pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree_history_poses_;//
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_history_poses_;//
        pcl::VoxelGrid<IG_LIO::PointType>::Ptr sub_map_downsize_filter_;//
        pcl::IterativeClosestPoint<IG_LIO::PointType, IG_LIO::PointType>::Ptr icp_;//

    public:
        void init()
        {

            gtsam::ISAM2Params isam2_params;
            isam2_params.relinearizeThreshold = 0.01;
            isam2_params.relinearizeSkip = 1;
            isam2_ = std::make_shared<gtsam::ISAM2>(isam2_params);
            kdtree_history_poses_.reset(new pcl::KdTreeFLANN<pcl::PointXYZ>);
            cloud_history_poses_.reset(new pcl::PointCloud<pcl::PointXYZ>);
            sub_map_downsize_filter_.reset(new pcl::VoxelGrid<IG_LIO::PointType>);
            sub_map_downsize_filter_->setLeafSize(loop_params_.submap_resolution,
                                                  loop_params_.submap_resolution,
                                                  loop_params_.submap_resolution);

            icp_.reset(new pcl::IterativeClosestPoint<IG_LIO::PointType, IG_LIO::PointType>);
            icp_->setMaxCorrespondenceDistance(100);
            icp_->setMaximumIterations(50);
            icp_->setTransformationEpsilon(1e-6);
            icp_->setEuclideanFitnessEpsilon(1e-6);
            icp_->setRANSACIterations(0);
        }
        void setShared(std::shared_ptr<SharedData> share_data)
        {
            shared_data_ = share_data;
        }
        void setRate(const double &rate)
        {
            rate_ = std::make_shared<rclcpp::Rate>(rate);
        }
        void setRate(std::shared_ptr<rclcpp::Rate> rate)
        {
            rate_ = rate;
        }
        LoopParams &mutableParams()
        {
            return loop_params_;
        }

        IG_LIO::PointCloudXYZI::Ptr getSubMaps(std::vector<Pose6D> &pose_list,
                                               std::vector<IG_LIO::PointCloudXYZI::Ptr> &cloud_list,
                                               int index,
                                               int search_num)
        {
            IG_LIO::PointCloudXYZI::Ptr cloud(new IG_LIO::PointCloudXYZI);
            int max_size = pose_list.size();
            int min_index = std::max(0, index - search_num);
            int max_index = std::min(max_size - 1, index + search_num);
            for (int i = min_index; i <= max_index; i++)
            {
                Pose6D &p = pose_list[i];
                Eigen::Matrix4d T = Eigen::Matrix4d::Identity();
                T.block<3, 3>(0, 0) = p.global_rot;
                T.block<3, 1>(0, 3) = p.global_pos;
                IG_LIO::PointCloudXYZI::Ptr temp_cloud(new IG_LIO::PointCloudXYZI);
                pcl::transformPointCloud(*cloud_list[p.index], *temp_cloud, T);
                *cloud += *temp_cloud;
            }
            sub_map_downsize_filter_->setInputCloud(cloud);
            sub_map_downsize_filter_->filter(*cloud);
            return cloud;
        }

        void operator()()
        {
            while (is_alive)
            {
                rate_->sleep();
                if (terminate_flag)
                {
                    is_alive = !terminate_flag;
                    break;
                }
                if (!loop_params_.activate)
                    continue;
                if (shared_data_->key_poses.size() < std::size_t(loop_params_.loop_pose_index_thresh))
                    continue;
                if (!shared_data_->key_pose_added)
                    continue;
                shared_data_->key_pose_added = false;
                {
                    std::lock_guard<std::mutex> lock(shared_data_->mutex);
                    lastest_index_ = shared_data_->key_poses.size() - 1;
                    temp_poses_.clear();
                    temp_poses_.assign(shared_data_->key_poses.begin(), shared_data_->key_poses.end());
                }
                loopCheck();
                addOdomFactor();
                addLoopFactor();
                smoothAndUpdate();
            }
        }

        void stop()
        {
            terminate_flag = true;
        }

        void loopCheck()
        {
            if (temp_poses_.empty())
                return;
            int cur_index = temp_poses_.size() - 1;
            int pre_index = -1;

            cloud_history_poses_->clear();

            for (Pose6D &p : temp_poses_)
            {
                pcl::PointXYZ point;
                point.x = p.global_pos(0);
                point.y = p.global_pos(1);
                point.z = p.global_pos(2);
                cloud_history_poses_->push_back(point);
            }
            kdtree_history_poses_->setInputCloud(cloud_history_poses_);
            std::vector<int> ids;
            std::vector<float> sqdists;
            kdtree_history_poses_->radiusSearch(cloud_history_poses_->back(), loop_params_.loop_pose_search_radius, ids, sqdists, 0);

            for (std::size_t i = 0; i < ids.size(); i++)
            {
                int id = ids[i];
                if (std::abs(temp_poses_[id].time - temp_poses_.back().time) > loop_params_.time_thresh && std::abs(cur_index - id) >= loop_params_.loop_pose_index_thresh)
                {
                    pre_index = id;
                    break;
                }
            }
            if (pre_index == -1 || pre_index == cur_index)
                return;

            IG_LIO::PointCloudXYZI::Ptr cur_cloud = getSubMaps(temp_poses_, shared_data_->cloud_history, cur_index, 0);
            IG_LIO::PointCloudXYZI::Ptr sub_maps = getSubMaps(temp_poses_, shared_data_->cloud_history, pre_index, loop_params_.submap_search_num);

            icp_->setInputSource(cur_cloud);
            icp_->setInputTarget(sub_maps);

            IG_LIO::PointCloudXYZI::Ptr aligned(new IG_LIO::PointCloudXYZI);

            icp_->align(*aligned, Eigen::Matrix4f::Identity());

            float score = icp_->getFitnessScore();

            if (!icp_->hasConverged() || score > loop_params_.loop_icp_thresh)
                return;
            RCLCPP_INFO_STREAM(rclcpp::get_logger("map_builder_node"), CYAN << "Detected LOOP: " << MAGENTA << pre_index << " " << cur_index << " " << score << RESET);
            shared_data_->loop_history.emplace_back(pre_index, cur_index);
            loop_found_ = true;

            Eigen::Matrix4d T_pre_cur = icp_->getFinalTransformation().cast<double>();
            Eigen::Matrix3d R12 = temp_poses_[pre_index].global_rot.transpose() * T_pre_cur.block<3, 3>(0, 0) * temp_poses_[cur_index].global_rot;
            Eigen::Vector3d t12 = temp_poses_[pre_index].global_rot.transpose() * (T_pre_cur.block<3, 3>(0, 0) * temp_poses_[cur_index].global_pos + T_pre_cur.block<3, 1>(0, 3) - temp_poses_[pre_index].global_pos);
            shared_data_->loop_pairs.emplace_back(pre_index, cur_index, score, R12, t12);
        }

        void addOdomFactor()
        {
            for (int i = previous_index_; i < lastest_index_; i++)
            {
                Pose6D &p1 = temp_poses_[i];
                Pose6D &p2 = temp_poses_[i + 1];

                if (i == 0)
                {
                    initialized_estimate_.insert(i, gtsam::Pose3(gtsam::Rot3(p1.local_rot),
                                                                 gtsam::Point3(p1.local_pos)));
                    gtsam::noiseModel::Diagonal::shared_ptr noise = gtsam::noiseModel::Diagonal::Variances(gtsam::Vector6::Ones() * 1e-12);
                    gtsam_graph_.add(gtsam::PriorFactor<gtsam::Pose3>(i, gtsam::Pose3(gtsam::Rot3(p1.local_rot), gtsam::Point3(p1.local_pos)), noise));
                }
                initialized_estimate_.insert(i + 1, gtsam::Pose3(gtsam::Rot3(p2.local_rot),
                                                                 gtsam::Point3(p2.local_pos)));
                Eigen::Matrix3d R12 = p1.local_rot.transpose() * p2.local_rot;
                Eigen::Vector3d t12 = p1.local_rot.transpose() * (p2.local_pos - p1.local_pos);

                gtsam::noiseModel::Diagonal::shared_ptr noise = gtsam::noiseModel::Diagonal::Variances((gtsam::Vector(6) << 1e-6, 1e-6, 1e-6, 1e-4, 1e-4, 1e-6).finished());
                gtsam_graph_.add(gtsam::BetweenFactor<gtsam::Pose3>(i,
                                                                    i + 1,
                                                                    gtsam::Pose3(gtsam::Rot3(R12), gtsam::Point3(t12)), noise));
            }
            previous_index_ = lastest_index_;
        }

        void addLoopFactor()
        {
            if (!loop_found_)
                return;
            if (shared_data_->loop_pairs.empty())
                return;
            for (LoopPair &lp : shared_data_->loop_pairs)
            {
                gtsam::Pose3 pose_between(gtsam::Rot3(lp.diff_rot), gtsam::Point3(lp.diff_pos));
                gtsam_graph_.add(gtsam::BetweenFactor<gtsam::Pose3>(lp.pre_idx,
                                                                    lp.cur_idx,
                                                                    pose_between,
                                                                    gtsam::noiseModel::Diagonal::Variances(gtsam::Vector6::Ones() * lp.score)));
            }
            shared_data_->loop_pairs.clear();
        }

        void smoothAndUpdate()
        {
            isam2_->update(gtsam_graph_, initialized_estimate_);
            isam2_->update();
            if (loop_found_)
            {
                isam2_->update();
                isam2_->update();
                isam2_->update();
                isam2_->update();
                isam2_->update();
                loop_found_ = false;
            }
            gtsam_graph_.resize(0);
            initialized_estimate_.clear();

            optimized_estimate_ = isam2_->calculateBestEstimate();
            gtsam::Pose3 latest_estimate = optimized_estimate_.at<gtsam::Pose3>(lastest_index_);
            temp_poses_[lastest_index_].global_rot = latest_estimate.rotation().matrix().cast<double>();
            temp_poses_[lastest_index_].global_pos = latest_estimate.translation().matrix().cast<double>();
            Eigen::Matrix3d offset_rot;
            Eigen::Vector3d offset_pos;
            temp_poses_[lastest_index_].getOffset(offset_rot, offset_pos);

            int current_size;
            {
                std::lock_guard<std::mutex> lck(shared_data_->mutex);
                current_size = shared_data_->key_poses.size();
                shared_data_->offset_rot = offset_rot;
                shared_data_->offset_pos = offset_pos;
            }

            for (int i = 0; i < lastest_index_; i++)
            {
                gtsam::Pose3 temp_pose = optimized_estimate_.at<gtsam::Pose3>(i);
                shared_data_->key_poses[i].global_rot = temp_pose.rotation().matrix().cast<double>();
                shared_data_->key_poses[i].global_pos = temp_pose.translation().matrix().cast<double>();
            }

            for (int i = lastest_index_; i < current_size; i++)
            {
                shared_data_->key_poses[i].addOffset(offset_rot, offset_pos);
            }
        }
    };
}

#endif