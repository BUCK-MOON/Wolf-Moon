#include "../include/way_planner_node.hpp"
namespace navigation
{
    MapData::MapData()
    {
    }

    MapData::~MapData()
    {
    }
    bool MapData::loadMapFromYaml(const std::string &yaml_name)
    {
        std::string package = ament_index_cpp::get_package_share_directory("navigation_planning");
        std::string path = package + "/map/" + yaml_name;
        // 解析YAML文件
        YAML::Node config = YAML::LoadFile(path);

        // 获取地图信息
        if (!config["image"])
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "YAML中缺少'image'参数");
            return false;
        }
        image_file_name_ = config["image"].as<std::string>();
        // 从YAML文件路径推断PGM文件的完整路径
        image_file_name_ = package + "/map/" + image_file_name_;
        resolution_ = config["resolution"].as<double>();
        if (resolution_ <= 0)
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "无效的分辨率值: %f", resolution_);
            return false;
        }

        if (!config["origin"] || config["origin"].size() < 2)
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "无效或缺少'origine'参数");
            return false;
        }
        origin_x_ = config["origin"][0].as<double>();
        origin_y_ = config["origin"][1].as<double>();
        negate_ = config["negate"].as<int>();
        occupied_thresh_ = config["occupied_thresh"].as<double>();
        free_thresh_ = config["free_thresh"].as<double>();
        if (occupied_thresh_ <= free_thresh_)
        {
            RCLCPP_WARN(rclcpp::get_logger("MapData"),
                        "障碍物阈值(%f)应大于自由空间阈值(%f)",
                        occupied_thresh_, free_thresh_);
        }
        loadMapFromFile();
        return true;
    }
    bool MapData::loadMapFromFile()
    {
        // 使用OpenCV加载PGM图像
        cv::Mat map_image = cv::imread(image_file_name_, cv::IMREAD_GRAYSCALE);
        if (map_image.empty())
        {
            return false;
        }
        // cv::imshow("map", map_image);
        // cv::waitKey(0);
        // 获取代价地图指针
        // 初始化OccupancyGrid消息
        occ_msg_.header.frame_id = "map";
        occ_msg_.info.resolution = resolution_;
        occ_msg_.info.width = map_image.cols;
        occ_msg_.info.height = map_image.rows;
        occ_msg_.info.origin.position.x = origin_x_;
        occ_msg_.info.origin.position.y = origin_y_;
        occ_msg_.info.origin.orientation.w = 1.0; // 默认无旋转
        occ_msg_.data.resize(occ_msg_.info.width * occ_msg_.info.height);

        global_map_.setFrameId("map");
        global_map_.setGeometry(grid_map::Length(map_image.cols, map_image.rows), resolution_);
        global_map_.add("local_map"); // 预分配局部地图图层
        // 填充代价地图
        int occupied_pixel = 255 * occupied_thresh_;
        int free_pixel = 255 * free_thresh_;

        for (unsigned int y = 0; y < map_image.rows; ++y)
        {
            for (unsigned int x = 0; x < map_image.cols; ++x)
            {
                unsigned int flipped_y = map_image.rows - y - 1;
                int pixel = map_image.at<uchar>(y, x);
                int8_t occupancy_value = -1; // 默认未知(-1)
                if (pixel <= free_pixel)     // 自由空间
                {
                    occupancy_value = 100; // 0表示自由
                }
                else if (pixel >= occupied_pixel) // 障碍物
                {
                    occupancy_value = 0; // 100表示完全占据
                }
                occ_msg_.data[flipped_y * occ_msg_.info.width + x] = occupancy_value;
            }
        }
        grid_map::GridMapRosConverter::fromOccupancyGrid(occ_msg_, "elevation", global_map_);
        // RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "load map success" << RESET);
        return true;
    }

    WayPlannerNode::WayPlannerNode(const rclcpp::NodeOptions &options) : rclcpp::Node("way_planner_node", options)
    {
        // map_param_.global_costmap_->on_configure(rclcpp_lifecycle::State());
        map_param_ = std::make_unique<MapData>();
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        map_param_->loadMapFromYaml("rmuc_map.yaml");
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing params ..." << RESET);
        initParam();
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing subscribers ..." << RESET);
        initSubscribers();
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing publishers ..." << RESET);
        initPublishers();
        RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "processing init ..." << RESET);
        init();
    }

    WayPlannerNode::~WayPlannerNode()
    {
        cv::destroyAllWindows();
    }

    void WayPlannerNode::initParam()
    {
    }

    void WayPlannerNode::initSubscribers()
    {
        grid_map_sub_ = this->create_subscription<grid_map_msgs::msg::GridMap>(
            "/local_costmap/grid_map",
            rclcpp::SensorDataQoS(), // 必须与发布者完全匹配
            std::bind(&WayPlannerNode::gridMapCallback, this, std::placeholders::_1));
    }
    void WayPlannerNode::gridMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr msg)
    {
        // std::lock_guard<std::mutex> lock(map_mutex_);
        // // map_mutex_.lock();
        // std::string layer_name = "local_map_" + std::to_string(msg->header.stamp.sec);
        // grid_map::GridMap local_map;
        // grid_map::GridMapRosConverter::fromMessage(*msg, local_map);
        // map_param_->global_map_["local_map"] = local_map["elevation"];
        // RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "recive local_map..." << RESET);
        // map_mutex_.unlock();
    }
    void WayPlannerNode::initPublishers()
    {
        map_pub_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
            "occ_map",
            rclcpp::QoS(10).reliable());

        path_pub_ = create_publisher<nav_msgs::msg::Path>("global_path", 10);

        nav_feedback_pub_ = this->create_publisher<nav2_msgs::action::NavigateToPose::Impl::FeedbackMessage>(
            "navigate_to_pose/_action/feedback", // 自定义发布话题
            rclcpp::QoS(10).reliable());

        goal_status_pub_ = this->create_publisher<action_msgs::msg::GoalStatusArray>(
            "navigate_to_pose/_action/status",
            rclcpp::QoS(10).reliable());

        // 创建发布者，使用与订阅者相同的主题名和QoS配置
        twist_pub_ = this->create_publisher<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            rclcpp::SensorDataQoS()); // 使用传感器数据QoS
    }
    void WayPlannerNode::publishMap()
    {
    }
    void WayPlannerNode::init()
    {
        // 创建临时图层

        action_server_ = rclcpp_action::create_server<nav2_msgs::action::NavigateToPose>(
            this,
            "navigate_to_pose",
            std::bind(&WayPlannerNode::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&WayPlannerNode::handleCancel, this, std::placeholders::_1),
            std::bind(&WayPlannerNode::handleAccepted, this, std::placeholders::_1));
        rclcpp::sleep_for(std::chrono::milliseconds(50));

        loop_send_thread_ = std::make_unique<std::thread>(&WayPlannerNode::run, this);
    }
    rclcpp_action::GoalResponse WayPlannerNode::handleGoal(const rclcpp_action::GoalUUID &uuid,
                                                           std::shared_ptr<const nav2_msgs::action::NavigateToPose::Goal> goal)
    {
        RCLCPP_INFO(get_logger(), "Received goal request with target (%.2f, %.2f)",
                    goal->pose.pose.position.x,
                    goal->pose.pose.position.y);
        // 检查目标有效性
        if (isGoalValid(goal->pose))
        {
            return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
        }
        else
        {
            return rclcpp_action::GoalResponse::REJECT;
        }
    }
    bool WayPlannerNode::isGoalValid(const geometry_msgs::msg::PoseStamped &pose)
    {
        // 实现目标有效性检查
        return true;
    }
    rclcpp_action::CancelResponse WayPlannerNode::handleCancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<nav2_msgs::action::NavigateToPose>> goal_handle)
    {
        RCLCPP_INFO(get_logger(), "Received request to cancel goal");
        // 执行取消逻辑
        // cancel_navigation();
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void WayPlannerNode::handleAccepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<nav2_msgs::action::NavigateToPose>> goal_handle)
    {
        std::lock_guard<std::mutex> lock(pos_mutex_);
        // pos_mutex_.lock();
        const auto goal = goal_handle->get_goal();
        grid_map::Position goal_pos_(
            goal->pose.pose.position.x,
            goal->pose.pose.position.y);
        // pos_mutex_.unlock();
    }

    void WayPlannerNode::run()
    {
        while (rclcpp::ok())
        {
            // 控制循环频率
            rclcpp::sleep_for(std::chrono::milliseconds(10));
            map_pub_->publish(map_param_->occ_msg_);
            // Step 2: 通过TF获取机器人当前位置
            grid_map::Position start_pos;
            geometry_msgs::msg::TransformStamped::SharedPtr transformStamped = nullptr;
            // 尝试获取base_link到map坐标系的变换
            try
            {
                transformStamped = std::make_shared<geometry_msgs::msg::TransformStamped>(this->tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero));
            }
            catch (tf2::TransformException &ex)
            {
                // 记录变换获取失败的错误
                RCLCPP_ERROR(
                    this->get_logger(),
                    "Cannot get transform ! TransformException: %s",
                    ex.what());
                continue;
            }
            {
                std::lock_guard<std::mutex> lock(pos_mutex_);
                // pos_mutex_.lock();
                start_pos.x() = transformStamped->transform.translation.x;
                start_pos.y() = transformStamped->transform.translation.y;
                // pos_mutex_.unlock();
            }
            nav_msgs::msg::Path path;
            // std::cout << "111" << std::endl;
            grid_map::Position goal_pos_(
                3.0,
                3.0);
            path.header.frame_id = map_param_->global_map_.getFrameId();
            path.header.stamp = now();
            if (!map_param_->global_map_.isInside(start_pos) || !map_param_->global_map_.isInside(goal_pos_))
            {
                RCLCPP_ERROR(get_logger(), "Start or goal outside map!");
                continue;
            }

            // 获取代价图层
            std::lock_guard<std::mutex> lock(map_mutex_);
            // map_mutex_.lock();
            auto cost_layer = map_param_->global_map_["elevation"] ;//+ map_param_->global_map_["local_map"];
            auto layer=map_param_->global_map_["local_map"];
            // cost_layer=cost_layer+layer;
            // map_mutex_.unlock();
            grid_map::Index start_index, goal_index;
            if (!map_param_->global_map_.getIndex(start_pos, start_index) ||
                !map_param_->global_map_.getIndex(goal_pos_, goal_index))
            {
                RCLCPP_ERROR(get_logger(), "Failed to get start or goal index!");
                continue;
            }
            // Dijkstra算法实现
            const float INF = std::numeric_limits<float>::max();
            grid_map::Size map_size = map_param_->global_map_.getSize();

            // 初始化距离矩阵和访问矩阵
            Eigen::MatrixXf distances = Eigen::MatrixXf::Constant(map_size(0), map_size(1), INF);
            Eigen::MatrixXi visited = Eigen::MatrixXi::Zero(map_size(0), map_size(1));
            Eigen::MatrixXi previous_x = Eigen::MatrixXi::Constant(map_size(0), map_size(1), -1);
            Eigen::MatrixXi previous_y = Eigen::MatrixXi::Constant(map_size(0), map_size(1), -1);
            // 使用优先队列存储待访问节点 (距离, x, y)
            using QueueElement = std::tuple<float, int, int>;
            std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>> queue;
            // 设置起点距离为0
            distances(start_index(0), start_index(1)) = 0;
            queue.emplace(0, start_index(0), start_index(1));

            // 定义8个方向的邻域
            const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
            const int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
            const float sqrt2 = std::sqrt(2.0f);

            bool found = false;

            while (!queue.empty())
            {
                auto [current_dist, x, y] = queue.top();
                queue.pop();

                // 如果到达目标点
                if (x == goal_index(0) && y == goal_index(1))
                {
                    found = true;
                    break;
                }

                // 如果已经访问过或者当前距离大于已知距离
                if (visited(x, y) || current_dist > distances(x, y))
                    continue;

                visited(x, y) = 1;

                // 检查所有邻域
                for (int i = 0; i < 8; ++i)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    // 检查边界
                    if (nx < 0 || nx >= map_size(0) || ny < 0 || ny >= map_size(1))
                        continue;

                    // 检查是否可通行 (假设NaN或大于某个阈值为障碍物)
                    float cost = cost_layer(nx, ny);
                    if (std::isnan(cost) || cost > 0.5) // 调整阈值根据实际情况
                        continue;

                    // 计算新距离 (对角线移动距离为sqrt(2))
                    float new_dist = current_dist + ((dx[i] != 0 && dy[i] != 0) ? sqrt2 : 1.0f); //

                    // 如果找到更短路径
                    if (new_dist < distances(nx, ny))
                    {
                        distances(nx, ny) = new_dist;
                        previous_x(nx, ny) = x;
                        previous_y(nx, ny) = y;
                        queue.emplace(new_dist, nx, ny);
                    }
                }
            }

            if (found)
            {
                // 回溯路径
                std::vector<grid_map::Index> path_indices;
                int x = goal_index(0), y = goal_index(1);

                while (x != -1 && y != -1)
                {
                    path_indices.emplace_back(x, y);
                    int prev_x = previous_x(x, y);
                    int prev_y = previous_y(x, y);
                    x = prev_x;
                    y = prev_y;
                }

                std::reverse(path_indices.begin(), path_indices.end());

                // 转换为Path消息
                for (const auto &index : path_indices)
                {
                    grid_map::Position position;
                    map_param_->global_map_.getPosition(index, position);

                    geometry_msgs::msg::PoseStamped pose;
                    pose.header = path.header;
                    pose.pose.position.x = position.x();
                    pose.pose.position.y = position.y();
                    pose.pose.position.z = 0.0;
                    pose.pose.orientation.w = 1.0;

                    path.poses.push_back(pose);
                }
                std::cout << "111" << std::endl;

                // 发布路径
                path_pub_->publish(path);
            }
            else
            {
                RCLCPP_WARN(get_logger(), "No path found from start to goal!");
                continue;
            }
        }
    }

}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto my_node = std::make_shared<navigation::WayPlannerNode>(options);
    rclcpp::spin(my_node);
    rclcpp::shutdown();
    return 0;
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(navigation::WayPlannerNode)