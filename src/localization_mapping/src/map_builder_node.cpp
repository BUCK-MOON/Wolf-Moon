#include "../include/map_builder_node.hpp"
namespace IG_LIO
{
    MapBuilderNode::MapBuilderNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions()) : Node("map_builder", options)
    {
        // 初始化参数
        RCLCPP_INFO_STREAM(this->get_logger(), GREEN << "Starting map_builder node ..." << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing params ..." << RESET);
        // 初始化监听者
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing subscribers ..." << RESET);
        initSubscribers();
        // 初始化发布者
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing publishers ..." << RESET);
        initPublishers();

        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing init ..." << RESET);
        init();
        RCLCPP_INFO_STREAM(this->get_logger(), GREEN << "DONE." << RESET);
    }
    MapBuilderNode::~MapBuilderNode()
    {
    }
    void MapBuilderNode::param_respond()
    {
        this->declare_parameter<std::string>("map_frame", std::string("map"));     // 地图坐标系名称
        this->declare_parameter<std::string>("local_frame", std::string("local")); // 局部坐标系名称
        this->declare_parameter<std::string>("body_frame", std::string("body"));   // 本体坐标系名称
        this->get_parameter("map_frame", global_frame_);
        this->get_parameter("local_frame", local_frame_);
        this->get_parameter("body_frame", body_frame_);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "map_frame set to " << global_frame_ << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "local_frame set to " << local_frame_ << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "body_frame set to " << body_frame_ << RESET);

        this->declare_parameter<std::string>("imu_topic", std::string("/imu/data"));
        this->declare_parameter<std::string>("livox_topic", std::string("/livox/lidar"));
        this->get_parameter("imu_topic", imu_data_.topic);
        this->get_parameter("livox_topic", livox_data_.topic);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "imu_topic set to " << imu_data_.topic << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "livox_topic set to " << livox_data_.topic << RESET);
        // 点云去除配置文件
        this->declare_parameter<std::string>("dynamic_point_cloud_removal_config", std::string("config_fg.yaml"));
        this->get_parameter("dynamic_point_cloud_removal_config", dynamic_point_cloud_removal_config_);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "dynamic_point_cloud_removal_config set to " << dynamic_point_cloud_removal_config_ << RESET);

        this->declare_parameter<bool>("publish_map_cloud", false);
        this->declare_parameter<bool>("publish_slam_cloud", false);
        this->declare_parameter<int>("max_slam_cloud_num", 100);
        this->get_parameter("publish_map_cloud", publish_map_cloud_);
        this->get_parameter("publish_slam_cloud", publish_slam_cloud_);
        this->get_parameter("max_slam_cloud_num", max_slam_cloud_num_);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "publish_map_cloud set to " << publish_map_cloud_ << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "publish_slam_cloud set to " << publish_slam_cloud_ << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "max_slam_cloud_num set to " << max_slam_cloud_num_ << RESET);

        {
            double local_rate, loop_rate_lc, loop_rate_l;
            this->declare_parameter<double>("local_rate", 20.0);
            this->declare_parameter<double>("loop_rate_lc", 1.0);
            this->declare_parameter<double>("loop_rate_l", 1.0);
            this->get_parameter("local_rate", local_rate);
            this->get_parameter("loop_rate_lc", loop_rate_lc);
            this->get_parameter("loop_rate_l", loop_rate_l);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "local_rate set to " << local_rate << RESET);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_rate_lc set to " << loop_rate_lc << RESET);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_rate_l set to " << loop_rate_l << RESET);
            local_rate_ = std::make_shared<rclcpp::Rate>(local_rate);     // 控制局部建图/定位模块的运行频率，通常设置为较高的值以满足实时性需求。
            loop_rate_lc_ = std::make_shared<rclcpp::Rate>(loop_rate_lc); // 控制回环检测模块的运行频率，通常设置为较低的值以减少计算负载。
            loop_rate_l_ = std::make_shared<rclcpp::Rate>(loop_rate_l);   // 重定位频率
        }

        this->declare_parameter<double>("blind", 0.5);
        this->declare_parameter<double>("height_offset", 0.7);
        this->get_parameter("blind", livox_data_.blind);
        livox_data_.calcBlindFieldByBlind();
        this->get_parameter("height_offset", livox_data_.height_offset);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "blind set to " << livox_data_.blind << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "height_offset set to " << livox_data_.height_offset << RESET);

        // 声明和初始化与 LiDAR-Inertial Odometry (LIO) 构建器相关的参数
        this->declare_parameter<double>("lio_builder.scan_resolution", 0.3);        // 扫描点云的分辨率。
        this->declare_parameter<double>("lio_builder.map_resolution", 0.3);         // 地图点云的分辨率。
        this->declare_parameter<double>("lio_builder.point2plane_gain", 100.0);     // 点对面约束的增益。
        this->declare_parameter<double>("lio_builder.gicp_constraint_gain", 100.0); // GICP（Generalized Iterative Closest Point）约束的增益。
        this->get_parameter("lio_builder.scan_resolution", lio_params_.scan_resolution);
        this->get_parameter("lio_builder.map_resolution", lio_params_.map_resolution);
        this->get_parameter("lio_builder.point2plane_gain", lio_params_.point2plane_gain);
        this->get_parameter("lio_builder.gicp_constraint_gain", lio_params_.gicp_constraint_gain);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.scan_resolution set to " << lio_params_.scan_resolution << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.map_resolution set to " << lio_params_.map_resolution << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.point2plane_gain set to " << lio_params_.point2plane_gain << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.gicp_constraint_gain set to " << lio_params_.gicp_constraint_gain << RESET);
        {
            int map_capacity, grid_capacity;
            this->declare_parameter<int>("lio_builder.map_capacity", 5000000);
            this->declare_parameter<int>("lio_builder.grid_capacity", 20);
            this->get_parameter("lio_builder.map_capacity", map_capacity);
            this->get_parameter("lio_builder.grid_capacity", grid_capacity);
            lio_params_.map_capacity = static_cast<size_t>(map_capacity);
            lio_params_.grid_capacity = static_cast<size_t>(grid_capacity);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.map_capacity set to " << lio_params_.map_capacity << RESET);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.grid_capacity set to " << lio_params_.grid_capacity << RESET);
        }

        this->declare_parameter<bool>("lio_builder.align_gravity", true);     // 控制是否对齐重力向量。
        this->declare_parameter<bool>("lio_builder.set_initpose", true);      // 控制是否设置初始位姿。
        this->declare_parameter<bool>("lio_builder.extrinsic_est_en", false); // 控制是否启用外参估计。如果设置为 true，系统会估计 LiDAR 和 IMU 之间的外参（即传感器之间的相对位姿）。
        this->declare_parameter<double>("lio_builder.acc_cov", 0.1);          // 定义 加速度计的噪声协方差。
        this->declare_parameter<double>("lio_builder.gyr_cov", 0.1);          // 定义 陀螺仪的噪声协方差。
        this->declare_parameter<double>("lio_builder.ba_cov", 0.00001);       // 定义 加速度计零偏的噪声协方差。
        this->declare_parameter<double>("lio_builder.bg_cov", 0.00001);       // 定义 陀螺仪零偏的噪声协方差。
        this->get_parameter("lio_builder.align_gravity", lio_params_.align_gravity);
        this->get_parameter("lio_builder.set_initpose", lio_params_.set_initpose);
        this->get_parameter("lio_builder.extrinsic_est_en", lio_params_.extrinsic_est_en);
        this->get_parameter("lio_builder.acc_cov", lio_params_.imu_acc_cov);
        this->get_parameter("lio_builder.gyr_cov", lio_params_.imu_gyro_cov);
        this->get_parameter("lio_builder.ba_cov", lio_params_.imu_acc_bias_cov);
        this->get_parameter("lio_builder.bg_cov", lio_params_.imu_gyro_bias_cov);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.align_gravity set to " << lio_params_.align_gravity << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.set_initpose set to " << lio_params_.set_initpose << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.extrinsic_est_en set to " << lio_params_.extrinsic_est_en << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.acc_cov set to " << lio_params_.imu_acc_cov << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.gyr_cov set to " << lio_params_.imu_gyro_cov << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.ba_cov set to " << lio_params_.imu_acc_bias_cov << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.bg_cov set to " << lio_params_.imu_gyro_bias_cov << RESET);

        {
            std::vector<double> pre_rot = {1, 0, 0, 0, 1, 0, 0, 0, 1}; // 定义 IMU 和中心之间的旋转矩阵。
            std::vector<double> pre_pos = {-0.011, -0.02329, 0.04412}; // 定义 IMU 和 LiDAR 之间的平移向量。
            this->declare_parameter<std::vector<double>>("lio_builder.imu_ext_rot", pre_rot);
            this->declare_parameter<std::vector<double>>("lio_builder.imu_ext_pos", pre_pos);
            this->get_parameter("lio_builder.imu_ext_rot", lio_params_.imu_ext_rot);
            this->get_parameter("lio_builder.imu_ext_pos", lio_params_.imu_ext_pos);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.imu_ext_rot set to "
                                                        << lio_params_.imu_ext_rot[0] << " "
                                                        << lio_params_.imu_ext_rot[1] << " "
                                                        << lio_params_.imu_ext_rot[2] << " "
                                                        << lio_params_.imu_ext_rot[3] << " "
                                                        << lio_params_.imu_ext_rot[4] << " "
                                                        << lio_params_.imu_ext_rot[5] << " "
                                                        << lio_params_.imu_ext_rot[6] << " "
                                                        << lio_params_.imu_ext_rot[7] << " "
                                                        << lio_params_.imu_ext_rot[8] << " "
                                                        << RESET);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.imu_ext_pos set to "
                                                        << lio_params_.imu_ext_pos[0] << " "
                                                        << lio_params_.imu_ext_pos[1] << " "
                                                        << lio_params_.imu_ext_pos[2] << " "
                                                        << RESET);
        }

        {
            int mode;
            this->declare_parameter<int>("lio_builder.near_mode", 2);
            this->get_parameter("lio_builder.near_mode", mode);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.near_mode set to " << mode << RESET);
            switch (mode) // 邻近点搜索模式的作用
            {
            case 1:
                lio_params_.mode = IG_LIO::VoxelMap::MODE::NEARBY_1;
                break;
            case 2:
                lio_params_.mode = IG_LIO::VoxelMap::MODE::NEARBY_7;
                break;
            case 3:
                lio_params_.mode = IG_LIO::VoxelMap::MODE::NEARBY_19;
                break;
            case 4:
                lio_params_.mode = IG_LIO::VoxelMap::MODE::NEARBY_26;
                break;

            default:
                lio_params_.mode = IG_LIO::VoxelMap::MODE::NEARBY_1;
                break;
            }
        }

        { // 外参
            std::vector<double> pre_ext_r = {3.14, 0., 0.};
            std::vector<double> pre_ext_t = {-0.0151, 0., 0.};
            this->declare_parameter<std::vector<double>>("lio_slam.ext_r", pre_ext_r);
            this->declare_parameter<std::vector<double>>("lio_slam.ext_t", pre_ext_t);
            this->get_parameter("lio_slam.ext_r", lio_params_.ext_r);
            this->get_parameter("lio_slam.ext_t", lio_params_.ext_t);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_slam.ext_r set to "
                                                        << lio_params_.ext_r[0] << " "
                                                        << lio_params_.ext_r[1] << " "
                                                        << lio_params_.ext_r[2] << " "
                                                        << RESET);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_builder.ext_t set to "
                                                        << lio_params_.ext_t[0] << " "
                                                        << lio_params_.ext_t[1] << " "
                                                        << lio_params_.ext_t[2] << " "
                                                        << RESET);
        }

        // 是否启用imu补偿
        this->declare_parameter<bool>("lio_slam.imu_compensation", false);
        this->get_parameter("lio_slam.imu_compensation", lio_params_.imu_compensation_);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "lio_slam.imu_compensation set to " << lio_params_.imu_compensation_ << RESET);

        // 回环检测相关参数
        this->declare_parameter<bool>("loop_closure.activate", false);                 // 控制是否启用回环检测。
        this->declare_parameter<double>("loop_closure.rad_thresh", 0.4);               // 定义 回环检测的旋转阈值。
        this->declare_parameter<double>("loop_closure.dist_thresh", 2.5);              // 定义 回环检测的距离阈值。
        this->declare_parameter<double>("loop_closure.time_thresh", 30.0);             // 定义 回环检测的时间阈值
        this->declare_parameter<double>("loop_closure.loop_pose_search_radius", 10.0); // 定义 回环检测的搜索半径。
        this->declare_parameter<int>("loop_closure.loop_pose_index_thresh", 5);        // 定义 回环检测的索引阈值。
        this->declare_parameter<double>("loop_closure.submap_resolution", 0.2);        // 定义 子地图的分辨率。
        this->declare_parameter<int>("loop_closure.submap_search_num", 20);            // 定义 子地图搜索的数量。
        this->declare_parameter<double>("loop_closure.loop_icp_thresh", 0.3);          // 定义 ICP（迭代最近点）匹配的阈值。
        this->get_parameter("loop_closure.activate", loop_closure_.mutableParams().activate);
        this->get_parameter("loop_closure.rad_thresh", loop_closure_.mutableParams().rad_thresh);
        this->get_parameter("loop_closure.dist_thresh", loop_closure_.mutableParams().dist_thresh);
        this->get_parameter("loop_closure.time_thresh", loop_closure_.mutableParams().time_thresh);
        this->get_parameter("loop_closure.loop_pose_search_radius", loop_closure_.mutableParams().loop_pose_search_radius);
        this->get_parameter("loop_closure.loop_pose_index_thresh", loop_closure_.mutableParams().loop_pose_index_thresh);
        this->get_parameter("loop_closure.submap_resolution", loop_closure_.mutableParams().submap_resolution);
        this->get_parameter("loop_closure.submap_search_num", loop_closure_.mutableParams().submap_search_num);
        this->get_parameter("loop_closure.loop_icp_thresh", loop_closure_.mutableParams().loop_icp_thresh);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.activate set to " << loop_closure_.mutableParams().activate << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.rad_thresh set to " << loop_closure_.mutableParams().rad_thresh << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.dist_thresh set to " << loop_closure_.mutableParams().dist_thresh << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.time_thresh set to " << loop_closure_.mutableParams().time_thresh << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.loop_pose_search_radius set to " << loop_closure_.mutableParams().loop_pose_search_radius << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.loop_pose_index_thresh set to " << loop_closure_.mutableParams().loop_pose_index_thresh << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.submap_resolution set to " << loop_closure_.mutableParams().submap_resolution << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.submap_search_num set to " << loop_closure_.mutableParams().submap_search_num << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop_closure.loop_icp_thresh set to " << loop_closure_.mutableParams().loop_icp_thresh << RESET);

        // 重定位相关
        this->declare_parameter<double>("localizer.refine_resolution", 0.15); // 定义 精匹配（Refine Matching）的分辨率。
        this->declare_parameter<double>("localizer.rough_resolution", 0.3);   // 定义 粗匹配（Rough Matching）的分辨率。
        this->declare_parameter<double>("localizer.refine_iter", 5.);         // 定义 精匹配的迭代次数。
        this->declare_parameter<double>("localizer.rough_iter", 10.);         // 定义 粗匹配的迭代次数。
        this->declare_parameter<double>("localizer.thresh", 0.15);            // 定义 匹配的阈值。
        this->declare_parameter<double>("localizer.xy_offset", 1.0);          // 定义 XY 平面的偏移量。
        this->declare_parameter<int>("localizer.yaw_offset", 0);              // 定义 Yaw 角的偏移量。
        this->declare_parameter<double>("localizer.yaw_resolution", 0.3);     // 定义 Yaw 角的分辨率。
        this->get_parameter("localizer.refine_resolution", localizer_params_.refine_resolution);
        this->get_parameter("localizer.rough_resolution", localizer_params_.rough_resolution);
        this->get_parameter("localizer.refine_iter", localizer_params_.refine_iter);
        this->get_parameter("localizer.rough_iter", localizer_params_.rough_iter);
        this->get_parameter("localizer.thresh", localizer_params_.thresh);
        this->get_parameter("localizer.xy_offset", localizer_params_.xy_offset);
        this->get_parameter("localizer.yaw_offset", localizer_params_.yaw_offset);
        this->get_parameter("localizer.yaw_resolution", localizer_params_.yaw_resolution);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.refine_resolution set to " << localizer_params_.refine_resolution << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.rough_resolution set to " << localizer_params_.rough_resolution << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.refine_iter set to " << localizer_params_.refine_iter << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.rough_iter set to " << localizer_params_.rough_iter << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.thresh set to " << localizer_params_.thresh << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.xy_offset set to " << localizer_params_.xy_offset << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.yaw_offset set to " << localizer_params_.yaw_offset << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.yaw_resolution set to " << localizer_params_.yaw_resolution << RESET);

        //
        this->declare_parameter<bool>("localizer.reloc_on_init", false); // 是否在初始的时候进行初始化
        this->declare_parameter<std::string>("localizer.pcd_path", "");  // 定义 点云文件（PCD 文件）的路径。
        this->get_parameter("localizer.reloc_on_init", localizer_reloc_on_init);
        this->get_parameter("localizer.pcd_path", localizer_pcd_path);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.reloc_on_init set to " << localizer_reloc_on_init << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.pcd_path set to " << localizer_pcd_path << RESET);

        { // 初始位姿
            std::vector<double> pre_xyz_rpy = {0., 0., 0., 0., 0., 0.};
            this->declare_parameter<std::vector<double>>("localizer.xyz_rpy", pre_xyz_rpy); // 定义 初始位姿的 XYZ 和 RPY 值。
            this->get_parameter("localizer.xyz_rpy", localizer_xyz_rpy);
            RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "localizer.xyz_rpy set to "
                                                        << localizer_xyz_rpy[0] << " "
                                                        << localizer_xyz_rpy[1] << " "
                                                        << localizer_xyz_rpy[2] << " "
                                                        << localizer_xyz_rpy[3] << " "
                                                        << localizer_xyz_rpy[4] << " "
                                                        << localizer_xyz_rpy[5] << " "
                                                        << RESET);
        }
    }

    void MapBuilderNode::initSubscribers()
    {
        // 获取imu数据
        imu_sub_ =
            this->create_subscription<sensor_msgs::msg::Imu>(imu_data_.topic,
                                                             rclcpp::QoS(400).reliable().keep_last(1),
                                                             std::bind(&MapBuilderNode::imuCallbackGroup, this, _1));

        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "imu data subscribe from " << imu_data_.topic << RESET);

        // 获取点云数据
        livox_sub_ =
            this->create_subscription<livox_ros_driver2::msg::CustomMsg>(livox_data_.topic,
                                                                         rclcpp::QoS(20).reliable().keep_last(1),
                                                                         std::bind(&LivoxData::callback, &livox_data_, _1));

        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "livox pointcloud data subscribe from " << livox_data_.topic << RESET);
    }

    void MapBuilderNode::imuCallbackGroup(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        imu_data_.callback(msg);
        if (lio_params_.imu_compensation_)
        {
            lio_builder_->calcIMUCompensation(imu_data_.buffer.back());
        }
    }

    void MapBuilderNode::initPublishers()
    {
        // 局部点云通常是当前帧或最近几帧的点云数据，用于实时显示机器人的局部环境。
        local_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("local_cloud", rclcpp::QoS(10).transient_local().keep_last(1));
        // 通常是机器人本体上的传感器（如 LiDAR）采集的点云数据。
        body_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("body_cloud", rclcpp::QoS(10).transient_local().keep_last(1));
        // 全局地图是 SLAM 系统构建的完整环境地图，包含所有历史帧的点云数据。
        map_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("map_cloud", rclcpp::QoS(10).transient_local().keep_last(1));
        // 通常是经过 SLAM 算法处理后的点云数据，用于显示 SLAM 系统的实时状态。
        slam_cloud_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("slam_cloud", rclcpp::QoS(10).transient_local().keep_last(1));
        // 里程计数据包含机器人的位姿（位置和方向）信息，用于导航和路径规划。
        odom_pub_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", rclcpp::QoS(200).transient_local().keep_last(1));
        // 用于可视化回环检测的结果，例如检测到的回环位置。
        loop_mark_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("loop_mark", rclcpp::QoS(10).transient_local().keep_last(1));
        // 局部路径通常是机器人在局部环境中的规划路径。
        local_path_pub_ = this->create_publisher<nav_msgs::msg::Path>("local_path", rclcpp::QoS(10).transient_local().keep_last(1));
        // 全局路径通常是机器人在全局地图中的规划路径。
        global_path_pub_ = this->create_publisher<nav_msgs::msg::Path>("global_path", rclcpp::QoS(10).transient_local().keep_last(1));

        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "local cloud publish to "
                   OccupancyGridConverterNode                                 << "local_cloud" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "body cloud data publish to "
                                                    << "body_cloud" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "map cloud data publish to "
                                                    << "map_cloud" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "slam cloud data publish to "
                                                    << "slam_cloud" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "odom data publish to "
                                                    << "odom" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "loop mark publish to "
                                                    << "loop_mark" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "local path publish to "
                                                    << "local_path" << RESET);
        RCLCPP_INFO_STREAM(this->get_logger(), CYAN << "global path publish to "
                                                    << "global_path" << RESET);
    }

    void MapBuilderNode::initSerivces()
    {
        // 保存地图请求
        Savemap_Server = this->create_service<ig_lio_c_msgs::srv::SaveMap>("SaveMap",
                                                                           std::bind(&MapBuilderNode::saveMapCallBack, this, _1, _2),
                                                                           rmw_qos_profile_services_default);
        // 重定位请求服务
        Reloc_Server = this->create_service<ig_lio_c_msgs::srv::ReLoc>("ReLoc",
                                                                       std::bind(&MapBuilderNode::relocCallback, this, _1, _2),
                                                                       rmw_qos_profile_services_default);
        // 向其他节点发送重定位请求，用于程序启动时的重定位
        Reloc_Client = this->create_client<ig_lio_c_msgs::srv::ReLoc>("ReLoc", rmw_qos_profile_services_default);
    }

    void MapBuilderNode::saveMapCallBack(const ig_lio_c_msgs::srv::SaveMap::Request::SharedPtr request,
                                         const ig_lio_c_msgs::srv::SaveMap::Response::SharedPtr response)
    {
        std::string file_path = request->save_path;
        int cnt = 1;
        octomap::MapUpdater map_updater(ament_index_cpp::get_package_share_directory("ig_lio_c") + "/config/" + dynamic_point_cloud_removal_config_);
        IG_LIO::PointCloudXYZI::Ptr cloud(new IG_LIO::PointCloudXYZI);
        {
            std::lock_guard<std::mutex> lck(shared_data_->mutex);
            for (Pose6D &p : shared_data_->key_poses)
            {
                map_updater.timing.start(" One Scan Cost  ");
                IG_LIO::PointCloudXYZI::Ptr temp_cloud(new IG_LIO::PointCloudXYZI);
                pcl::transformPointCloud(*shared_data_->cloud_history[p.index],
                                         *temp_cloud,
                                         p.global_pos,
                                         Eigen::Quaterniond(p.global_rot));
                if (cnt > 1 && !map_updater.getCfg().verbose_)
                {
                    std::ostringstream log_msg;
                    log_msg << "( Processing:" << cnt << ")"
                            << " Time Cost: "
                            << map_updater.timing.lastSeconds(" One Scan Cost  ") << "s";
                    std::string spaces(10, ' ');
                    log_msg << spaces;
                    RCLCPP_INFO_STREAM(this->get_logger(), CYAN << log_msg.str().c_str() << RESET);
                }
                pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_xyz(new pcl::PointCloud<pcl::PointXYZ>());
                pcl::copyPointCloud(*temp_cloud, *cloud_xyz);
                map_updater.run(cloud_xyz);
                map_updater.timing.stop(" One Scan Cost  ");
                cnt++;
            }
        }
        map_updater.timing.start("4. Query & Write");
        std::string output_file;
        if (map_updater.getCfg().filterGroundPlane && map_updater.getCfg().filterNoise)
            output_file = "octomapfg";
        else if (map_updater.getCfg().filterGroundPlane)
            output_file = "octomapg";
        else
            output_file = "octomap";
        auto static_cloud = map_updater.getRawMap();
        if (static_cloud->empty())
        {
            response->status = false;
            response->message = "Empty cloud!";
            RCLCPP_ERROR_STREAM(this->get_logger(), RED << "Failed to save map !" << RESET);
        }
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_SOR_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::StatisticalOutlierRemoval<pcl::PointXYZ> sor;
        sor.setInputCloud(static_cloud);
        sor.setMeanK(50);
        sor.setStddevMulThresh(1.0);
        sor.filter(*cloud_SOR_filtered);
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_VG_filtered(new pcl::PointCloud<pcl::PointXYZ>);
        pcl::VoxelGrid<pcl::PointXYZ> vg;
        vg.setInputCloud(cloud_SOR_filtered);
        vg.setLeafSize(0.02f, 0.02f, 0.02f);
        vg.filter(*cloud_VG_filtered);
        pcl::io::savePCDFileBinary(request->save_path + "/" + output_file + "_output.pcd", *cloud_VG_filtered);
        map_updater.timing.stop("4. Query & Write");
        map_updater.timing.setColor("0. Fit ground   ", ufo::Timing::boldYellowColor());
        map_updater.timing.setColor("1. Ray SetFreeOc", ufo::Timing::boldCyanColor());
        map_updater.timing.setColor("2. Update Octree", ufo::Timing::boldMagentaColor());
        map_updater.timing.setColor("3. Prune Tree   ", ufo::Timing::boldGreenColor());
        map_updater.timing.setColor("4. Query & Write", ufo::Timing::boldRedColor());
        RCLCPP_INFO(this->get_logger(), "\nOctomap Timings:\n");
        RCLCPP_INFO(this->get_logger(), "\t Component\t\tTotal\tLast\tMean\tStDev\t Min\t Max\t Steps\n");
        for (auto const &tag : map_updater.timing.tags())
        {
            RCLCPP_INFO(this->get_logger(), "\t%s%s\t%5.2f\t%5.4f\t%5.4f\t%5.4f\t%5.4f\t%5.4f\t%6lu%s\n",
                        map_updater.timing.color(tag).c_str(), tag.c_str(), map_updater.timing.totalSeconds(tag),
                        map_updater.timing.lastSeconds(tag), map_updater.timing.meanSeconds(tag), map_updater.timing.stdSeconds(tag),
                        map_updater.timing.minSeconds(tag), map_updater.timing.maxSeconds(tag), map_updater.timing.numSamples(tag),
                        ufo::Timing::resetColor());
        }
        response->status = 1;
        response->message = "Success to save map !";
        RCLCPP_INFO_STREAM(this->get_logger(), GREEN << "Success to save map !" << RESET);
    }

    void MapBuilderNode::relocCallback(const ig_lio_c_msgs::srv::ReLoc::Request::SharedPtr request,
                                       const ig_lio_c_msgs::srv::ReLoc::Response::SharedPtr response)
    {
        std::string map_path = request->pcd_path;
        float x = request->x;
        float y = request->y;
        float z = request->z;
        float roll = request->roll;
        float pitch = request->pitch;
        float yaw = request->yaw;
        Eigen::AngleAxisf rollAngle(roll, Eigen::Vector3f::UnitX());
        Eigen::AngleAxisf pitchAngle(pitch, Eigen::Vector3f::UnitY());
        Eigen::AngleAxisf yawAngle(yaw, Eigen::Vector3f::UnitZ());
        Eigen::Quaternionf q = rollAngle * pitchAngle * yawAngle;
        {
            std::lock_guard<std::mutex> lck(shared_data_->service_mutex);
            shared_data_->halt_flag = false;
            shared_data_->localizer_service_called = true;
            shared_data_->localizer_activate = true;
            shared_data_->map_path = map_path;
            shared_data_->initial_guess.block<3, 3>(0, 0) = q.toRotationMatrix().cast<double>();
            shared_data_->initial_guess.block<3, 1>(0, 3) = Eigen::Vector3d(x, y, z);
        }
        response->status = 1;
        response->message = "RELOCALIZE CALLED!";
    }

    void MapBuilderNode::init()
    {
        shared_data_ = std::make_shared<SharedData>();               // 创建 SharedData 对象，用于在多个模块之间共享数据。
        br_ = std::make_shared<tf2_ros::TransformBroadcaster>(this); // 创建 TF 广播器，用于发布机器人的位姿和坐标系变换。
        static_br_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
        lio_builder_ = std::make_shared<IG_LIO::IGLIOBuilder>(lio_params_); // 创建 IGLIOBuilder 对象，用于构建 LiDAR-Inertial Odometry (LIO) 系统。
        loop_closure_.setRate(loop_rate_lc_);
        loop_closure_.setShared(shared_data_);
        loop_closure_.init();
        loop_thread_ = std::make_shared<std::thread>(std::ref(loop_closure_)); // 配置回环检测模块的参数，并启动回环检测线程。
        // 创建 IcpLocalizer 对象，用于点云匹配和重定位。
        icp_localizer_ = std::make_shared<IG_LIO::IcpLocalizer>(localizer_params_.refine_resolution,
                                                                localizer_params_.rough_resolution,
                                                                localizer_params_.refine_iter,
                                                                localizer_params_.rough_iter,
                                                                localizer_params_.thresh);
        icp_localizer_->setSearchParams(localizer_params_.xy_offset, localizer_params_.yaw_offset, localizer_params_.yaw_resolution);
        localizer_loop_.setRate(loop_rate_l_);
        localizer_loop_.setSharedDate(shared_data_);
        localizer_loop_.setLocalizer(icp_localizer_);
        localizer_thread_ = std::make_shared<std::thread>(std::ref(localizer_loop_)); // 配置定位线程的参数，并启动定位线程。

        f = std::bind(&MapBuilderNode::run, this); // 将 run 函数绑定到 f，用于后续的主循环。

        publishBaseLink(); // 调用 publishBaseLink 函数，发布机器人的基坐标系。

        if (localizer_reloc_on_init) // 如果配置参数 localizer_reloc_on_init 为 true，则在初始化时触发重定位。
        {
            std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Request> request(new ig_lio_c_msgs::srv::ReLoc_Request);
            request->pcd_path = localizer_pcd_path;
            request->x = localizer_xyz_rpy[0];
            request->y = localizer_xyz_rpy[1];
            request->z = localizer_xyz_rpy[2];
            request->roll = localizer_xyz_rpy[3];
            request->pitch = localizer_xyz_rpy[4];
            request->yaw = localizer_xyz_rpy[5];
            localizer_response = this->Reloc_Client->async_send_request(request);
        }
    }

    void MapBuilderNode::publishBaseLink()
    {
        Eigen::Vector3d baselink2odom_t;
        Eigen::Matrix3d baselink2odom_r;
        baselink2odom_r = Eigen::AngleAxisd(lio_params_.ext_r[0], Eigen::Vector3d::UnitX()) *
                          Eigen::AngleAxisd(lio_params_.ext_r[1], Eigen::Vector3d::UnitY()) *
                          Eigen::AngleAxisd(lio_params_.ext_r[2], Eigen::Vector3d::UnitZ());
        baselink2odom_t << lio_params_.ext_t[0], lio_params_.ext_t[1], lio_params_.ext_t[2];
        Eigen::Isometry3d baselink_pose = Eigen::Isometry3d::Identity();
        baselink_pose.translation() = baselink2odom_t;
        baselink_pose.rotate(baselink2odom_r);
        geometry_msgs::msg::TransformStamped transform;
        transform.header.frame_id = body_frame_;
        transform.header.stamp = rclcpp::Clock().now();
        transform.child_frame_id = "base_link";
        transform.transform.translation.x = baselink_pose.translation().x();
        transform.transform.translation.y = baselink_pose.translation().y();
        transform.transform.translation.z = baselink_pose.translation().z();
        Eigen::Quaterniond q = Eigen::Quaterniond(baselink_pose.rotation());
        transform.transform.rotation.w = q.w();
        transform.transform.rotation.x = q.x();
        transform.transform.rotation.y = q.y();
        transform.transform.rotation.z = q.z();
        static_br_->sendTransform(std::move(transform));
    }

    /**
     * @brief 重置 SLAM 系统的状态，包括位姿偏移量、共享数据中的偏移量以及 LIO 构建器的状态
     */
    void MapBuilderNode::systemReset()
    {
        // 将 offset_rot_ 和 offset_pos_ 重置为单位矩阵和零向量。
        offset_rot_ = Eigen::Matrix3d::Identity();
        offset_pos_ = Eigen::Vector3d::Zero();
        {
            // 将共享数据中的 offset_rot、offset_pos、offset_rot_loc 和 offset_pos_loc 重置为单位矩阵和零向量。
            std::lock_guard<std::mutex> lck(shared_data_->mutex);
            shared_data_->offset_rot = Eigen::Matrix3d::Identity();
            shared_data_->offset_pos = Eigen::Vector3d::Zero();
            shared_data_->offset_rot_loc = Eigen::Matrix3d::Identity();
            shared_data_->offset_pos_loc = Eigen::Vector3d::Zero();
            // 将 shared_data_->localizer_service_success 重置为 false，表示定位服务未成功。
            shared_data_->localizer_service_success = false;
        }
        // 调用 lio_builder_->reset()，重置 LIO 构建器的状态。
        lio_builder_->reset();
    }

    void MapBuilderNode::run()
    {
        local_rate_->sleep();

        // 重定位请求处理
        if (localizer_reloc_on_init) // 如果 localizer_reloc_on_init 为 true，则等待重定位请求的响应。
        {
            std::future_status status;
            status = localizer_response.wait_for(std::chrono::nanoseconds(1)); // 等待重定位请求的响应。
            if (status == std::future_status::ready)                           // 如果请求完成，获取响应并打印消息。
            {
                std::shared_ptr<ig_lio_c_msgs::srv::ReLoc_Response> response = localizer_response.get();
                localizer_reloc_on_init = false;
                RCLCPP_INFO_STREAM(this->get_logger(), CYAN << response->message.c_str() << RESET);
            }
            else if (status == std::future_status::timeout) // 如果请求超时，打印警告信息。
            {
                RCLCPP_WARN_STREAM(this->get_logger(), YELLOW << "RELOC CALL FAILED !" << RESET);
                localizer_reloc_on_init = false;
            }
        }

        // 同步传感器数据
        if (!measure_group_.syncPackage(imu_data_, livox_data_)) // 调用 measure_group_.syncPackage 同步 IMU 和 LiDAR 数据。
        {
            if (lio_params_.imu_compensation_ &&
                lio_builder_->currentStatus() == IG_LIO::Status::MAPPING) // 如果启用 IMU 数据补偿，并且系统处于建图状态，则使用 IMU 数据校正位姿。
            {
                std::shared_ptr<IG_LIO::PiontIMU> pointIMU = lio_builder_->getPointIMU();
                if (pointIMU->checkImuPushed())
                {
                    Eigen::Matrix3d rot_with_imu = pointIMU->getRot();
                    Eigen::Vector3d pos_with_imu = pointIMU->getPos();
                    double imu_time = pointIMU->getLastIMUT();
                    br_->sendTransform(std::move(eigen2Transform(rot_with_imu,
                                                                 pos_with_imu,
                                                                 local_frame_,
                                                                 body_frame_,
                                                                 imu_time)));
                    // 发布校正后的位姿和里程计数据。
                    publishOdom(eigen2Odometry(rot_with_imu,
                                               pos_with_imu,
                                               local_frame_,
                                               body_frame_,
                                               imu_time));
                    pointIMU->confirmCost();
                }
            }
            return;
        }

        if (shared_data_->halt_flag) // 如果 shared_data_->halt_flag 为 true，则暂停等下一次状态。
            return;

        if (shared_data_->reset_flag) // 如果 shared_data_->reset_flag 为 true，则重置系统状态。
        {
            RCLCPP_WARN_STREAM(this->get_logger(), YELLOW << "SYSTEM RESET!" << RESET);
            systemReset(); // 调用 systemReset 函数，重置系统状态。
            std::lock_guard<std::mutex> lck(shared_data_->service_mutex);
            shared_data_->reset_flag = false; // 重置标志位。
        }

        lio_builder_->mapping(measure_group_); // 调用 lio_builder_->mapping 进行 SLAM 建图。
        if (lio_builder_->currentStatus() == IG_LIO::Status::INITIALIZE)
            return;
        // 状态更新
        current_time_ = measure_group_.lidar_time_end; // 更新当前时间。
        current_state_ = lio_builder_->currentState(); // 获取当前状态（位姿、速度、零偏等）。
        RCLCPP_INFO_STREAM(this->get_logger(), MAGENTA << " ba: " << current_state_.ba.transpose()
                                                       << " ba_norm: " << current_state_.ba.norm()
                                                       << " bg: " << current_state_.bg.transpose() * 180.0 / M_PI
                                                       << " bg_norm: " << current_state_.bg.norm() * 180.0 / M_PI << RESET);
        current_cloud_body_ = lio_builder_->cloudUndistortedBody(); // 更新当前时间、状态和点云数据。获取当前帧的点云数据。

        // 发布 SLAM 点云
        if (publish_slam_cloud_) // 发布位姿、点云、路径和回环检测标记。只有在该标志位启用时，才会执行后续的点云发布逻辑，允许用户按需控制发布行为。
        {
            IG_LIO::PointCloudXYZI::Ptr slam_cloud_(new IG_LIO::PointCloudXYZI); // 初始化一个空的点云对象 slam_cloud_，用于后续拼接多帧点云。
            {                                                                    // PointCloudXYZI 表示包含坐标（X/Y/Z）和强度（Intensity）的点云。
                std::lock_guard<std::mutex> lck(shared_data_->mutex);            // 通过 std::lock_guard 获取共享数据 shared_data_ 的互斥锁。
                //                           预设的最大处理帧数（避免资源过载）。          实际存储的关键帧数量。
                size_t num_poses_to_copy = std::min(max_slam_cloud_num_, int(shared_data_->key_poses.size())); // 计算需要处理的关键帧数量。

                // 遍历关键帧并转换点云
                for (size_t i = 0; i < num_poses_to_copy; ++i)
                {
                    const auto &p = shared_data_->key_poses[shared_data_->key_poses.size() - i - 1];
                    IG_LIO::PointCloudXYZI::Ptr temp_cloud(new IG_LIO::PointCloudXYZI);
                    // 通过 p.index 从 cloud_history 中提取对应帧的局部点云。
                    // 将局部点云变换到全局坐标系，p.global_pos：全局位置（平移向量），p.global_rot：全局姿态（旋转四元数）。
                    pcl::transformPointCloud(*shared_data_->cloud_history[p.index],
                                             *temp_cloud,
                                             p.global_pos,
                                             Eigen::Quaterniond(p.global_rot));

                    *slam_cloud_ += *temp_cloud; // 点云拼接：将变换后的点云 temp_cloud 合并到 slam_cloud_ 中。
                }
            }
            // 发布全局点云
            publishSlamCloud(pcl2msg(slam_cloud_,
                                     global_frame_,
                                     current_time_));
            // 格式转换：调用 pcl2msg 将PCL点云转为ROS的 sensor_msgs/PointCloud2 消息。
            // 设置元数据：指定全局坐标系（global_frame_）和当前时间戳（current_time_）。
            // 通过 publishSlamCloud 函数发布消息，供其他节点（如Rviz）订阅和可视化。
        }

        { //    将当前状态和点云数据更新到共享数据中。计算位姿偏移量。
            std::lock_guard<std::mutex> lck(shared_data_->mutex);
            shared_data_->local_rot = current_state_.rot;
            shared_data_->local_pos = current_state_.pos;
            shared_data_->cloud = current_cloud_body_;
            offset_rot_ = shared_data_->offset_rot_loc * shared_data_->offset_rot;
            offset_pos_ = shared_data_->offset_pos_loc + shared_data_->offset_rot_loc * shared_data_->offset_pos;
            shared_data_->pose_updated = true;
        }

        if (current_state_.bg.norm() * 180.0 / M_PI > 2.0) // 如果陀螺仪零偏过大，则跳过地图更新。
        {
            RCLCPP_WARN_STREAM(this->get_logger(), YELLOW << "bg_norm too large, jump map process!" << RESET);
            return;
        }

        // 使用 br_->sendTransform 发布位姿变换。
        br_->sendTransform(std::move(eigen2Transform(offset_rot_,
                                                     offset_pos_,
                                                     global_frame_,
                                                     local_frame_,
                                                     current_time_)));
        br_->sendTransform(std::move(eigen2Transform(current_state_.rot,
                                                     current_state_.pos,
                                                     local_frame_,
                                                     body_frame_,
                                                     current_time_)));
        // 使用 publishOdom 发布里程计数据。
        publishOdom(eigen2Odometry(current_state_.rot,
                                   current_state_.pos,
                                   local_frame_,
                                   body_frame_,
                                   current_time_));

        addKeyPose();
        // 发布机器人本体的点云。
        publishBodyCloud(pcl2msg(current_cloud_body_,
                                 body_frame_,
                                 current_time_));
        // 发布局部点云。
        publishLocalCloud(pcl2msg(lio_builder_->cloudWorld(),
                                  local_frame_,
                                  current_time_));
        publishLocalPath();  // 发布局部路径。
        publishGlobalPath(); // 发布全局路径。
        publishLoopMark();   // 发布回环检测标记。
        // 如果 publish_map_cloud_ 为 true，并且 ICP 定位器已初始化，则发布地图点云。
        if (publish_map_cloud_)
        {
            if (icp_localizer_->isInitialized())
            {
                publishMapCloud(pcl2msg(icp_localizer_->getRoughMap(),
                                        global_frame_,
                                        current_time_));
            }
        }
    }

    void MapBuilderNode::publishLocalPath()
    {
        if (local_path_pub_->get_subscription_count() == 0)
            return;

        if (shared_data_->key_poses.empty())
            return;

        nav_msgs::msg::Path path;
        path.header.frame_id = global_frame_;
        path.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
        for (Pose6D &p : shared_data_->key_poses)
        {
            geometry_msgs::msg::PoseStamped pose;
            pose.header.frame_id = global_frame_;
            pose.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
            pose.pose.position.x = p.local_pos(0);
            pose.pose.position.y = p.local_pos(1);
            pose.pose.position.z = p.local_pos(2);
            Eigen::Quaterniond q(p.local_rot);
            pose.pose.orientation.x = q.x();
            pose.pose.orientation.y = q.y();
            pose.pose.orientation.z = q.z();
            pose.pose.orientation.w = q.w();
            path.poses.push_back(pose);
        }
        local_path_pub_->publish(std::move(path));
    }

    void MapBuilderNode::publishGlobalPath()
    {
        if (global_path_pub_->get_subscription_count() == 0)
            return;

        if (shared_data_->key_poses.empty())
            return;
        nav_msgs::msg::Path path;
        path.header.frame_id = global_frame_;
        path.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
        for (Pose6D &p : shared_data_->key_poses)
        {
            geometry_msgs::msg::PoseStamped pose;
            pose.header.frame_id = global_frame_;
            pose.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
            pose.pose.position.x = p.global_pos(0);
            pose.pose.position.y = p.global_pos(1);
            pose.pose.position.z = p.global_pos(2);
            Eigen::Quaterniond q(p.global_rot);
            pose.pose.orientation.x = q.x();
            pose.pose.orientation.y = q.y();
            pose.pose.orientation.z = q.z();
            pose.pose.orientation.w = q.w();
            path.poses.push_back(pose);
        }
        global_path_pub_->publish(std::move(path));
    }

    void MapBuilderNode::publishLoopMark()
    {
        if (loop_mark_pub_->get_subscription_count() == 0)
            return;
        if (shared_data_->loop_history.empty())
            return;
        visualization_msgs::msg::MarkerArray marker_array;
        visualization_msgs::msg::Marker nodes_marker;
        nodes_marker.header.frame_id = global_frame_;
        nodes_marker.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
        nodes_marker.ns = "loop_nodes";
        nodes_marker.id = 0;
        nodes_marker.type = visualization_msgs::msg::Marker::SPHERE_LIST;
        nodes_marker.action = visualization_msgs::msg::Marker::ADD;
        nodes_marker.pose.orientation.w = 1.0;
        nodes_marker.scale.x = 0.05;
        nodes_marker.scale.y = 0.05;
        nodes_marker.scale.z = 0.05;
        nodes_marker.color.r = 1.0;
        nodes_marker.color.g = 0.8;
        nodes_marker.color.b = 0.0;
        nodes_marker.color.a = 1.0;

        visualization_msgs::msg::Marker edges_marker;
        edges_marker.header.frame_id = global_frame_;
        edges_marker.header.stamp = rclcpp::Time(static_cast<uint64_t>(current_time_ * 1e9));
        edges_marker.ns = "loop_edges";
        edges_marker.id = 1;
        edges_marker.type = visualization_msgs::msg::Marker::LINE_LIST;
        edges_marker.action = visualization_msgs::msg::Marker::ADD;
        edges_marker.pose.orientation.w = 1.0;
        edges_marker.scale.x = 0.05;
        edges_marker.color.r = 0.0;
        edges_marker.color.g = 0.8;
        edges_marker.color.b = 0.0;
        edges_marker.color.a = 1.0;

        for (auto &p : shared_data_->loop_history)
        {
            Pose6D &p1 = shared_data_->key_poses[p.first];
            Pose6D &p2 = shared_data_->key_poses[p.second];
            geometry_msgs::msg::Point point1;
            point1.x = p1.global_pos(0);
            point1.y = p1.global_pos(1);
            point1.z = p1.global_pos(2);
            geometry_msgs::msg::Point point2;
            point2.x = p2.global_pos(0);
            point2.y = p2.global_pos(1);
            point2.z = p2.global_pos(2);
            nodes_marker.points.push_back(point1);
            nodes_marker.points.push_back(point2);
            edges_marker.points.push_back(point1);
            edges_marker.points.push_back(point2);
        }
        marker_array.markers.push_back(nodes_marker);
        marker_array.markers.push_back(edges_marker);
        loop_mark_pub_->publish(std::move(marker_array));
    }

    void MapBuilderNode::stop()
    {
        loop_closure_.stop();
        loop_thread_->join();
        localizer_loop_.stop();
        localizer_thread_->join();
    }

    void MapBuilderNode::addKeyPose()
    {
        int idx = shared_data_->key_poses.size(); // 获取当前关键位姿的数量，用来确定即将添加的关键位姿的索引。这个索引是在 key_poses 列表中的位置。
        if (shared_data_->key_poses.empty())
        { // 如果当前没有任何关键位姿（即 key_poses 是空的），就直接添加当前的位姿。
            std::lock_guard<std::mutex> lck(shared_data_->mutex);
            // 使用 std::lock_guard 来确保线程安全，因为多个线程可能会同时访问 shared_data_ 中的数据。mutex 保证了在同一时间只有一个线程可以修改共享数据。
            shared_data_->key_poses.emplace_back(idx, current_time_, current_state_.rot, current_state_.pos);
            // 向 key_poses 列表中添加一个新的 Pose6D 对象。这个对象的构造函数使用了当前时间 (current_time_)、当前状态的旋转矩阵 (current_state_.rot) 和位置向量 (current_state_.pos) 来初始化。
            shared_data_->key_poses.back().addOffset(shared_data_->offset_rot, shared_data_->offset_pos);
            // 对刚刚添加的 Pose6D 对象应用一个偏移量，这里偏移量是 shared_data_->offset_rot 和 shared_data_->offset_pos。这些偏移量通常是为了校准或者补偿某些传感器或地图误差。
            shared_data_->key_pose_added = true;
            // 设置标志 key_pose_added 为 true，表示已经成功添加了一个新的关键位姿。
            shared_data_->cloud_history.push_back(lio_builder_->cloudUndistortedBody());
            // 将当前的点云数据（可能是未畸变的激光点云）添加到 cloud_history 列表中，用于后续的处理。
            return;
        }

        Pose6D &last_key_pose = shared_data_->key_poses.back(); // 获取 key_poses 列表中最后一个关键位姿。
        // 计算当前位姿与最后一个关键位姿之间的旋转差异。首先通过转置操作将 last_key_pose.local_rot 与当前状态的旋转矩阵 current_state_.rot 相乘。
        Eigen::Matrix3d diff_rot = last_key_pose.local_rot.transpose() * current_state_.rot;
        // 计算当前位姿与最后一个关键位姿之间的平移差异。通过旋转矩阵将当前位姿的平移向量与最后一个关键位姿的平移差异转换到一个新的参考系。
        Eigen::Vector3d diff_pose = last_key_pose.local_rot.transpose() * (current_state_.pos - last_key_pose.local_pos);
        Eigen::Vector3d rpy = rotate2rpy(diff_rot); // 将旋转差异 diff_rot 转换为欧拉角（roll, pitch, yaw）。
        // 这个条件判断是决定是否将当前位姿添加为一个新的关键位姿。如果当前位姿与最后一个关键位姿的差异（包括平移和旋转）超过预设的阈值（dist_thresh 和 rad_thresh），则添加当前位姿为新的关键位姿。
        // diff_pose.norm() 计算平移差异的模长（即两者之间的距离）。
        // rpy 中的各个角度差异判断是否超过了设定的旋转阈值。
        if (diff_pose.norm() > loop_closure_.mutableParams().dist_thresh ||
            std::abs(rpy(0)) > loop_closure_.mutableParams().rad_thresh ||
            std::abs(rpy(1)) > loop_closure_.mutableParams().rad_thresh ||
            std::abs(rpy(2)) > loop_closure_.mutableParams().rad_thresh)
        {
            std::lock_guard<std::mutex> lck(shared_data_->mutex);                                             // 与前面相同，使用 mutex 进行线程同步。
            shared_data_->key_poses.emplace_back(idx, current_time_, current_state_.rot, current_state_.pos); // 如果条件满足，则将当前位姿添加到 key_poses 中。
            shared_data_->key_poses.back().addOffset(shared_data_->offset_rot, shared_data_->offset_pos);
            shared_data_->key_pose_added = true;
            shared_data_->cloud_history.push_back(lio_builder_->cloudUndistortedBody()); // 同时将当前的点云数据添加到 cloud_history 中。
        }
    }

    void MapBuilderNode::publishBodyCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub)
    {
        if (body_cloud_pub_->get_subscription_count() == 0)
            return;
        body_cloud_pub_->publish(std::move(cloud_to_pub));
    }

    void MapBuilderNode::publishMapCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub)
    {
        if (map_cloud_pub_->get_subscription_count() == 0)
            return;
        map_cloud_pub_->publish(std::move(cloud_to_pub));
    }

    void MapBuilderNode::publishLocalCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub)
    {
        if (local_cloud_pub_->get_subscription_count() != 0)
            local_cloud_pub_->publish(std::move(cloud_to_pub));
    }

    void MapBuilderNode::publishSlamCloud(const sensor_msgs::msg::PointCloud2 &cloud_to_pub)
    {
        if (slam_cloud_pub_->get_subscription_count() != 0)
            slam_cloud_pub_->publish(std::move(cloud_to_pub));
    }

    void MapBuilderNode::publishOdom(const nav_msgs::msg::Odometry &odom_to_pub)
    {
        if (odom_pub_->get_subscription_count() == 0)
            return;
        odom_pub_->publish(std::move(odom_to_pub));
    }
} // namespace IG_LIO

bool terminate_flag = false;

void signalHandler(int signum)
{
    switch (signum)
    {
    case SIGALRM:
        break;
    case SIGINT:
        std::cout << RED << "SHUTTING DOWN MAPPING NODE!" << RESET << std::endl;
        terminate_flag = true;
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    signal(SIGINT, signalHandler);
    rclcpp::init(argc, argv);
    auto node = std::make_shared<IG_LIO::MapBuilderNode>();
    while (rclcpp::ok() && !terminate_flag)
    {
        rclcpp::spin_some(node);
        node->f();
    }
    node->stop();
    rclcpp::shutdown();
    return 0;
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(IG_LIO::MapBuilderNode)