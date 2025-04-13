#ifndef LOCALIZATION_MAPPING__MAP_BUILDER_NODE_HPP_
#define LOCALIZATION_MAPPING__MAP_BUILDER_NODE_HPP_
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
        std::shared_ptr<SharedData> shared_data_;                                   // 结构体    指向SharedData类的共享指针，用于与主线程共享数据。
        std::shared_ptr<rclcpp::Rate> rate_;                                        // 控制回环检测线程的运行频率。
        LoopParams loop_params_;                                                    // 结构体    回环检测的参数配置，如搜索半径、时间阈值等。
        std::vector<Pose6D> temp_poses_;                                            // 临时存储的关键帧位姿列表。
        int previous_index_ = 0;                                                    // 先前索引
        int lastest_index_;                                                         // 最后一次索引
        bool loop_found_ = false;                                                   // 是否回环检测找到
        bool is_alive = true;                                                       // 是否存在
        bool terminate_flag = false;                                                // 终止符号
        gtsam::Values initialized_estimate_;                                        // 初始估计值
        gtsam::Values optimized_estimate_;                                          // 优化估计值
        std::shared_ptr<gtsam::ISAM2> isam2_;                                       // GTSAM库中的ISAM2（增量平滑与建图）对象，用于图优化。
        gtsam::NonlinearFactorGraph gtsam_graph_;                                   // 重要的类，用于表示和管理非线性因子图。
        pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree_history_poses_;                 // 用于存储历史位姿的KD树，加速最近邻搜索。
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_history_poses_;                   // 存储历史位姿的点云。
        pcl::VoxelGrid<IG_LIO::PointType>::Ptr sub_map_downsize_filter_;            // 指针类型，用于创建和管理一个点云下采样的过滤器。
        pcl::IterativeClosestPoint<IG_LIO::PointType, IG_LIO::PointType>::Ptr icp_; // 迭代最近点（ICP）算法对象，用于点云配准。

    public:
        /**
         * @brief 初始化函数
         * 设置ISAM2参数、KD树、点云滤波器、ICP算法等。
         */
        void init()
        {
            // GTSAM 初始化
            gtsam::ISAM2Params isam2_params;                       // 配置 ISAM2（增量平滑与建图）的参数。
            isam2_params.relinearizeThreshold = 0.01;              // 重新线性化的阈值。
            isam2_params.relinearizeSkip = 1;                      // 重新线性化的跳过次数。
            isam2_ = std::make_shared<gtsam::ISAM2>(isam2_params); // 创建 ISAM2 对象，用于后续的图优化。

            // 点云处理工具初始化
            kdtree_history_poses_.reset(new pcl::KdTreeFLANN<pcl::PointXYZ>);      // 初始化 KD 树，用于加速历史位姿的最近邻搜索。
            cloud_history_poses_.reset(new pcl::PointCloud<pcl::PointXYZ>);        // 初始化点云，用于存储历史位姿的位置信息。
            sub_map_downsize_filter_.reset(new pcl::VoxelGrid<IG_LIO::PointType>); // 初始化点云降采样滤波器，用于降低子地图的分辨率。
            sub_map_downsize_filter_->setLeafSize(loop_params_.submap_resolution,
                                                  loop_params_.submap_resolution,
                                                  loop_params_.submap_resolution); // 设置降采样滤波器的体素大小 (setLeafSize)。

            // ICP 初始化
            icp_.reset(new pcl::IterativeClosestPoint<IG_LIO::PointType, IG_LIO::PointType>); // 初始化 ICP（迭代最近点）算法，用于点云配准。
            icp_->setMaxCorrespondenceDistance(100);                                          // 设置 ICP 的最大对应距离、最大迭代次数、变换 epsilon 等参数。
            icp_->setMaximumIterations(50);
            icp_->setTransformationEpsilon(1e-6);
            icp_->setEuclideanFitnessEpsilon(1e-6);
            icp_->setRANSACIterations(0);
        }

        /**
         * @brief 设置 ICP 的最大对应距离、最大迭代次数、变换 epsilon 等参数。
         */
        void setShared(std::shared_ptr<SharedData> share_data)
        {
            shared_data_ = share_data;
        }

        /**
         * @brief 设置线程的运行频率，控制回环检测的执行速度。
         */
        void setRate(const double &rate)
        {
            rate_ = std::make_shared<rclcpp::Rate>(rate);
        }
        void setRate(std::shared_ptr<rclcpp::Rate> rate)
        {
            rate_ = rate;
        }

        /**
         * @brief 参数
         */
        LoopParams &mutableParams()
        {
            return loop_params_;
        }

        /**
         * 获取代价地图
         */
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

        /**
         * @brief 线程主循环
         * 重载()
         * 调用该函数  对象()
         */
        void operator()()
        {
            while (is_alive)
            {
                rate_->sleep();     // 根据设置的频率控制循环的执行速度。
                if (terminate_flag) // 检查是否收到终止信号，如果是则退出循环。
                {
                    is_alive = !terminate_flag;
                    break;
                }
                if (!loop_params_.activate) // 检查回环检测是否激活，如果没有激活则跳过本次循环。
                    continue;
                if (shared_data_->key_poses.size() < std::size_t(loop_params_.loop_pose_index_thresh)) // 检查关键帧数量是否达到回环检测的阈值。
                    continue;
                if (!shared_data_->key_pose_added) // 检查是否有新的关键帧加入。
                    continue;
                shared_data_->key_pose_added = false;
                {
                    std::lock_guard<std::mutex> lock(shared_data_->mutex); // 从共享数据中拷贝关键帧位姿到临时变量中，避免多线程冲突。
                    lastest_index_ = shared_data_->key_poses.size() - 1;   // 记录最新关键帧的索引。
                    temp_poses_.clear();
                    temp_poses_.assign(shared_data_->key_poses.begin(), shared_data_->key_poses.end());
                }
                loopCheck();
                addOdomFactor();
                addLoopFactor();
                smoothAndUpdate();
            }
        }

        /**
         * @brief 线程停止
         */
        void stop()
        {
            terminate_flag = true; // 设置终止标志，线程在下一次循环中退出。
        }

        /**
         * @brief 是回环检测的核心函数，负责检测当前帧与历史帧是否匹配。
         */
        void loopCheck()
        {
            if (temp_poses_.empty())
                return;
            int cur_index = temp_poses_.size() - 1;
            int pre_index = -1;
            // 将历史关键帧的位姿（位置信息）转换为点云格式。
            cloud_history_poses_->clear();

            for (Pose6D &p : temp_poses_)
            {
                pcl::PointXYZ point;
                point.x = p.global_pos(0);
                point.y = p.global_pos(1);
                point.z = p.global_pos(2);
                cloud_history_poses_->push_back(point);
            }

            // 使用 KD 树加速最近邻搜索。
            kdtree_history_poses_->setInputCloud(cloud_history_poses_);
            std::vector<int> ids;
            std::vector<float> sqdists;
            // 在当前帧附近搜索历史帧，找到可能匹配的候选帧。
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
            // 获取当前帧的点云。
            IG_LIO::PointCloudXYZI::Ptr cur_cloud = getSubMaps(temp_poses_, shared_data_->cloud_history, cur_index, 0);
            // 获取候选帧附近的子地图。
            IG_LIO::PointCloudXYZI::Ptr sub_maps = getSubMaps(temp_poses_, shared_data_->cloud_history, pre_index, loop_params_.submap_search_num);

            icp_->setInputSource(cur_cloud);
            icp_->setInputTarget(sub_maps);

            IG_LIO::PointCloudXYZI::Ptr aligned(new IG_LIO::PointCloudXYZI);
            // 使用 ICP 算法将当前帧与子地图进行配准。
            icp_->align(*aligned, Eigen::Matrix4f::Identity());

            // 计算变换矩阵 (T_pre_cur) 和匹配得分 (score)。
            float score = icp_->getFitnessScore();
            // 如果 ICP 匹配成功且得分低于阈值 (loop_params_.loop_icp_thresh)，则认为检测到回环。
            if (!icp_->hasConverged() || score > loop_params_.loop_icp_thresh)
                return;
            RCLCPP_INFO_STREAM(rclcpp::get_logger("map_builder_node"), CYAN << "Detected LOOP: " << MAGENTA << pre_index << " " << cur_index << " " << score << RESET);
            // 记录回环信息到 shared_data_->loop_history 和 shared_data_->loop_pairs。
            shared_data_->loop_history.emplace_back(pre_index, cur_index);
            loop_found_ = true;

            Eigen::Matrix4d T_pre_cur = icp_->getFinalTransformation().cast<double>();
            Eigen::Matrix3d R12 = temp_poses_[pre_index].global_rot.transpose() * T_pre_cur.block<3, 3>(0, 0) * temp_poses_[cur_index].global_rot;
            Eigen::Vector3d t12 = temp_poses_[pre_index].global_rot.transpose() * (T_pre_cur.block<3, 3>(0, 0) * temp_poses_[cur_index].global_pos + T_pre_cur.block<3, 1>(0, 3) - temp_poses_[pre_index].global_pos);
            shared_data_->loop_pairs.emplace_back(pre_index, cur_index, score, R12, t12);
        }

        /**
         * @brief 添加里程计因子
         */
        void addOdomFactor()
        {
            for (int i = previous_index_; i < lastest_index_; i++)
            {
                Pose6D &p1 = temp_poses_[i];
                Pose6D &p2 = temp_poses_[i + 1];
                // initialized_estimate_：初始化 GTSAM 的位姿估计。
                // 如果是第一帧，添加先验因子。
                // 对于后续帧，添加相邻帧之间的相对位姿因子。
                if (i == 0)
                {
                    initialized_estimate_.insert(i, gtsam::Pose3(gtsam::Rot3(p1.local_rot),
                                                                 gtsam::Point3(p1.local_pos)));
                    gtsam::noiseModel::Diagonal::shared_ptr noise = gtsam::noiseModel::Diagonal::Variances(gtsam::Vector6::Ones() * 1e-12);
                    gtsam_graph_.add(gtsam::PriorFactor<gtsam::Pose3>(i, gtsam::Pose3(gtsam::Rot3(p1.local_rot), gtsam::Point3(p1.local_pos)), noise)); // 添加里程计因子到 GTSAM 图中。
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

        /**
         * @brief 添加回环因子
         * 如果检测到回环，从 shared_data_->loop_pairs 中提取回环信息。
         * 将回环因子添加到 GTSAM 图中，用于校正累积误差。
         */
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

        /**
         *  图优化与更新
         */
        void smoothAndUpdate()
        {
            isam2_->update(gtsam_graph_, initialized_estimate_); // 执行图优化，更新位姿估计。
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

            optimized_estimate_ = isam2_->calculateBestEstimate();                               // 获取优化后的位姿。
            gtsam::Pose3 latest_estimate = optimized_estimate_.at<gtsam::Pose3>(lastest_index_); // 获取最新帧的优化位姿。
            temp_poses_[lastest_index_].global_rot = latest_estimate.rotation().matrix().cast<double>();
            temp_poses_[lastest_index_].global_pos = latest_estimate.translation().matrix().cast<double>();
            Eigen::Matrix3d offset_rot;
            Eigen::Vector3d offset_pos;
            temp_poses_[lastest_index_].getOffset(offset_rot, offset_pos); // 计算当前帧与优化后的位姿之间的偏移量。

            int current_size;
            {
                std::lock_guard<std::mutex> lck(shared_data_->mutex);
                current_size = shared_data_->key_poses.size(); // 将优化后的位姿更新到 shared_data_->key_poses 中。
                shared_data_->offset_rot = offset_rot;
                shared_data_->offset_pos = offset_pos;
            }
            // 将偏移量应用到后续关键帧中。
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

    /**
     * @brief 重定位
     * 在线重定位，异步于主线程，通过shared_data共享数据，由ReLoc服务触发
     */
    class LocalizerThread
    {
    private:
        bool is_alive = true;
        bool terminate_flag = false;
        std::shared_ptr<SharedData> shared_data_;             // 共享指针，用于与主线程共享数据。
        std::shared_ptr<IG_LIO::IcpLocalizer> icp_localizer_; // ICP 定位器对象，负责点云匹配和位姿计算。
        std::shared_ptr<rclcpp::Rate> rate_;                  // 控制线程的运行频率。
        pcl::PointCloud<pcl::PointXYZI>::Ptr current_cloud_;  // 存储当前帧的点云数据。
        Eigen::Matrix4d global_pose_;                         // 存储重定位后的全局位姿。
        // 存储当前帧的局部旋转和平移。
        Eigen::Matrix3d local_rot_;
        Eigen::Vector3d local_pos_;

    public:
        LocalizerThread() {}

        /**
         * @brief 设置共享数据
         */
        void setSharedDate(std::shared_ptr<SharedData> shared_data)
        {
            shared_data_ = shared_data;
        }

        /**
         * @brief 设置运行频率
         */
        void setRate(double rate)
        {
            rate_ = std::make_shared<rclcpp::Rate>(rate);
        }
        void setRate(std::shared_ptr<rclcpp::Rate> rate)
        {
            rate_ = rate;
        }

        /**
         * @brief  设置 ICP 定位器，用于点云匹配和位姿计算。
         */
        void setLocalizer(std::shared_ptr<IG_LIO::IcpLocalizer> localizer)
        {
            icp_localizer_ = localizer;
        }

        /**
         * @brief 是线程的主循环函数，负责执行重定位的核心逻辑。
         */
        void operator()()
        {
            current_cloud_.reset(new pcl::PointCloud<pcl::PointXYZI>);

            while (is_alive)
            {
                rate_->sleep();     // 根据设置的频率控制循环的执行速度。
                if (terminate_flag) // 检查是否收到终止信号，如果是则退出循环。
                {
                    is_alive = !terminate_flag;
                    break;
                }
                if (shared_data_->halt_flag)
                    continue;
                if (!shared_data_->localizer_activate)
                    continue;
                if (!shared_data_->pose_updated)
                    continue;
                global_pose_.setIdentity(); // 初始化全局位姿为单位矩阵。
                bool rectify = false;
                Eigen::Matrix4d init_guess; // 初始化初始猜测位姿。
                {
                    // 从共享数据中获取当前帧的局部旋转和平移。
                    std::lock_guard<std::mutex> lock(shared_data_->mutex);
                    shared_data_->pose_updated = false;
                    init_guess.setIdentity();
                    local_rot_ = shared_data_->local_rot;
                    local_pos_ = shared_data_->local_pos;
                    init_guess.block<3, 3>(0, 0) = shared_data_->offset_rot_loc * local_rot_;
                    init_guess.block<3, 1>(0, 3) = shared_data_->offset_rot_loc * local_pos_ + shared_data_->offset_pos;
                    pcl::copyPointCloud(*shared_data_->cloud, *current_cloud_); // 从共享数据中拷贝当前帧的点云数据。
                }

                if (shared_data_->localizer_service_called) // 检查是否通过服务调用触发重定位。
                {
                    // 如果是，则初始化 ICP 定位器，并使用初始猜测位姿进行多帧同步匹配 (multi_align_sync)。
                    // 如果匹配成功，则设置重定位成功标志 (localizer_service_success) 并激活重定位 (localizer_activate)。
                    std::lock_guard<std::mutex> lock(shared_data_->service_mutex);
                    shared_data_->localizer_service_called = false;
                    icp_localizer_->init(shared_data_->map_path, false);
                    global_pose_ = icp_localizer_->multi_align_sync(current_cloud_, shared_data_->initial_guess);
                    if (icp_localizer_->isSuccess())
                    {
                        rectify = true;
                        shared_data_->localizer_activate = true;
                        shared_data_->localizer_service_success = true;
                    }
                    else
                    {
                        rectify = false;
                        shared_data_->localizer_activate = false;
                        shared_data_->localizer_service_success = false;
                    }
                }
                else
                {
                    global_pose_ = icp_localizer_->align(current_cloud_, init_guess); // 如果不是服务触发，则使用初始猜测位姿进行单帧匹配
                    if (icp_localizer_->isSuccess())                                  // 如果匹配成功，则设置校正标志 (rectify)。
                        rectify = true;
                    else
                        rectify = false;
                }

                if (rectify)
                {
                    std::lock_guard<std::mutex> lock(shared_data_->mutex);
                    shared_data_->offset_rot_loc = global_pose_.block<3, 3>(0, 0) * local_rot_.transpose();
                    shared_data_->offset_pos_loc = -global_pose_.block<3, 3>(0, 0) * local_rot_.transpose() * local_pos_ + global_pose_.block<3, 1>(0, 3);
                }
            }
        }

        void stop()
        {
            terminate_flag = true;
        }
    };

    /**
     * @attention node ！！！
     * @brief 主节点
     * iG-LIO SLAM主要Node
     */
    class MapBuilderNode : public rclcpp::Node
    {
    public:
        MapBuilderNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
        ~MapBuilderNode();

        void run();
        void stop();

        std::function<void(void)> f;

    private:
        void param_respond();
        void initSubscribers();
        void initPublishers();
        void initSerivces();
        void init();
        void systemReset();
        void addKeyPose();
        void publishBodyCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub);
        void publishMapCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub);
        void publishLocalCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub);
        void publishSlamCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub);
        void publishOdom(const nav_msgs::msg::Odometry &odom_to_pub);
        void publishBaseLink();
        void publishLocalPath();
        void publishGlobalPath();
        void publishLoopMark();
        void imuCallbackGroup(const sensor_msgs::msg::Imu::SharedPtr msg);
        void saveMapCallBack(const ig_lio_c_msgs::srv::SaveMap::Request::SharedPtr request,
                             const ig_lio_c_msgs::srv::SaveMap::Response::SharedPtr response);
        void relocCallback(const ig_lio_c_msgs::srv::ReLoc::Request::SharedPtr request,
                           const ig_lio_c_msgs::srv::ReLoc::Response::SharedPtr response);

    private:
        std::string global_frame_;
        std::string local_frame_;
        std::string body_frame_;
        std::string dynamic_point_cloud_removal_config_;
rightJacobian
        bool localizer_reloc_on_init;

        std::shared_future<std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response>> localizer_response;
        std::string localizer_pcd_path;
        std::vector<double> localizer_xyz_rpy = {0., 0., 0., 0., 0., 0.};
        IG_LIO::State current_state_;
        ImuData imu_data_;
        LivoxData livox_data_;
        MeasureGroup measure_group_;
        IG_LIO::IGLIOParams lio_params_;
        IG_LIO::LocalizerParams localizer_params_;

        std::shared_ptr<IG_LIO::IGLIOBuilder> lio_builder_;
        std::shared_ptr<IG_LIO::IcpLocalizer> icp_localizer_;

        std::shared_ptr<SharedData> shared_data_;
        std::shared_ptr<rclcpp::Rate> local_rate_;
        std::shared_ptr<rclcpp::Rate> loop_rate_lc_;
        std::shared_ptr<rclcpp::Rate> loop_rate_l_;

        LoopClosureThread loop_closure_;
        std::shared_ptr<std::thread> loop_thread_;
        LocalizerThread localizer_loop_;
        std::shared_ptr<std::thread> localizer_thread_;
        std::shared_ptr<tf2_ros::TransformBroadcaster> br_;
        std::shared_ptr<tf2_ros::StaticTransformBroadcaster> static_br_;

        rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr odom_pub_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr local_cloud_pub_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr body_cloud_pub_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr map_cloud_pub_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr slam_cloud_pub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr loop_mark_pub_;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr local_path_pub_;
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr global_path_pub_;
        rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
        rclcpp::Subscription<livox_ros_driver2::msg::CustomMsg>::SharedPtr livox_sub_;
        rclcpp::Service<ig_lio_c_msgs::srv::SaveMap>::SharedPtr Savemap_Server;
        rclcpp::Service<ig_lio_c_msgs::srv::ReLoc>::SharedPtr Reloc_Server;
        rclcpp::Client<ig_lio_c_msgs::srv::ReLoc>::SharedPtr Reloc_Client;

        Eigen::Matrix3d offset_rot_ = Eigen::Matrix3d::Identity();

        Eigen::Vector3d offset_pos_ = Eigen::Vector3d::Zero();

        IG_LIO::PointCloudXYZI::Ptr current_cloud_body_;
    };
}

#endif