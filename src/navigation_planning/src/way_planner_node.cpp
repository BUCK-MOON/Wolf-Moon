#include "../include/way_planner_node.hpp"
namespace navigation
{

    WayPlannerNode::WayPlannerNode(const rclcpp::NodeOptions &options) : rclcpp::Node("way_planner_node", options)
    {
        // map_param_.global_costmap_->on_configure(rclcpp_lifecycle::State());

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

    rclcpp_action::GoalResponse WayPlannerNode::handleGoal(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const nav2_msgs::action::NavigateToPose::Goal> goal)
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
        map_processor_->goal_pos_ = grid_map::Position(0, 0);
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    void WayPlannerNode::handleAccepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<nav2_msgs::action::NavigateToPose>> goal_handle)
    {
        std::lock_guard<std::mutex> lock(pos_mutex_);
        // pos_mutex_.lock();
        RCLCPP_WARN(get_logger(), "get_goal");
        const auto goal = goal_handle->get_goal();
        flag_ = true;

        map_processor_->goal_pos_ = grid_map::Position(
            goal->pose.pose.position.x,
            goal->pose.pose.position.y);
        // pos_mutex_.unlock();
    }
    void WayPlannerNode::onGoalPoseReceived(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received new goal pose:");
        RCLCPP_INFO(this->get_logger(), "  Header:");
        RCLCPP_INFO(this->get_logger(), "    Frame ID: %s", msg->header.frame_id.c_str());
        RCLCPP_INFO(this->get_logger(), "    Timestamp: %d.%d",
                    msg->header.stamp.sec, msg->header.stamp.nanosec);
        RCLCPP_INFO(this->get_logger(), "  Position: x=%.2f, y=%.2f, z=%.2f",
                    msg->pose.position.x, msg->pose.position.y, msg->pose.position.z);
        RCLCPP_INFO(this->get_logger(), "  Orientation: x=%.2f, y=%.2f, z=%.2f, w=%.2f",
                    msg->pose.orientation.x, msg->pose.orientation.y,
                    msg->pose.orientation.z, msg->pose.orientation.w);
        flag_ = true;
        map_processor_->goal_pos_ = grid_map::Position(
            msg->pose.position.x,
            msg->pose.position.y);
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
        goal_sub_ = this->create_subscription<geometry_msgs::msg::PoseStamped>(
            "goal_pose",
            rclcpp::SystemDefaultsQoS(),
            std::bind(&WayPlannerNode::onGoalPoseReceived, this, std::placeholders::_1));
        action_server_ = rclcpp_action::create_server<nav2_msgs::action::NavigateToPose>(
            this,
            "/navigate_to_pose",
            std::bind(&WayPlannerNode::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&WayPlannerNode::handleCancel, this, std::placeholders::_1),
            std::bind(&WayPlannerNode::handleAccepted, this, std::placeholders::_1));
    }
    void WayPlannerNode::gridMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(map_mutex_);
        map_processor_->combinedMap(msg);
    }

    void WayPlannerNode::initPublishers()
    {
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
        marker_array_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("/marker_msg", 1);
    }
    void WayPlannerNode::publishMap()
    {
    }
    void WayPlannerNode::init()
    {
        map_processor_ = std::make_unique<MapProcessor>();
        dijkstra_planner_ = std::make_unique<DijkstraPlanner>();
        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        map_processor_->loadMapFromYaml("5.yaml");
        // 创建临时图层
        base_map_pub_ = create_publisher<nav_msgs::msg::OccupancyGrid>(
            "occ_map",
            rclcpp::QoS(10).reliable());
        path_pub_ = create_publisher<nav_msgs::msg::Path>("global_path", 10);
        loop_send_thread_ = std::make_unique<std::thread>(&WayPlannerNode::run, this);
    }

    void WayPlannerNode::run()
    {
        while (rclcpp::ok())
        {
            geometry_msgs::msg::Twist twist;
            action_msgs::msg::GoalStatusArray status_msg;
            action_msgs::msg::GoalStatus status_entry;
            status_entry.goal_info.goal_id.uuid = {0x01, 0x02, 0x03, 0x04};
            status_entry.goal_info.stamp = this->now();

            status_entry.status = action_msgs::msg::GoalStatus::STATUS_ACCEPTED;
            // 控制循环频率
            geometry_msgs::msg::TransformStamped::SharedPtr transformStamped = nullptr;
            // 尝试获取base_link到map坐标系的变换

            try
            {
                transformStamped = std::make_shared<geometry_msgs::msg::TransformStamped>(this->tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero));
            }
            catch (tf2::TransformException &ex)
            {
                status_msg.status_list.push_back(status_entry);
                goal_status_pub_->publish(status_msg);
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
                map_processor_->start_pos_.x() = transformStamped->transform.translation.x;
                map_processor_->start_pos_.y() = transformStamped->transform.translation.y;
                // pos_mutex_.unlock();
            }
            std::lock_guard<std::mutex> lock(map_mutex_);
            nav_msgs::msg::OccupancyGrid occ_msg;
            grid_map::GridMapRosConverter::toOccupancyGrid(map_processor_->global_map_, "combined", 0, 1, occ_msg);
            nav_msgs::msg::Path path;
            base_map_pub_->publish(occ_msg);
            double dx = map_processor_->goal_pos_.x() - map_processor_->start_pos_.x();
            double dy = map_processor_->goal_pos_.y() - map_processor_->start_pos_.y();
            twist.linear.x = map_processor_->start_pos_.x();
            twist.linear.y = map_processor_->start_pos_.y();
            // std::cout << dx << dy << std::endl;
            double distance = std::sqrt(dx * dx + dy * dy);
            if (distance < goal_thresh_)
            {
                twist.linear.z = 1.0;
                if (flag_)
                {
                    status_entry.status = action_msgs::msg::GoalStatus::STATUS_SUCCEEDED;
                    flag_ = false;
                    RCLCPP_INFO(this->get_logger(), "is goal");
                    status_msg.status_list.push_back(status_entry);
                    goal_status_pub_->publish(status_msg);
                }

                // RCLCPP_INFO(get_logger(), "is goal");
                // marker_array_pub_->publish(markers_msg_);
                RCLCPP_INFO_THROTTLE(this->get_logger(), *this->get_clock(), 500, "is wait");

                marker_array_pub_->publish(markers_msg_);

                twist_pub_->publish(twist);
                continue;
            }

            path.header.frame_id = map_processor_->global_map_.getFrameId();
            // path.header.stamp = now();
            if (dijkstra_planner_->pathPlanner(map_processor_, path))
            {
                status_entry.status = action_msgs::msg::GoalStatus::STATUS_EXECUTING;
                status_msg.status_list.push_back(status_entry);
                goal_status_pub_->publish(status_msg);
                path_pub_->publish(path);
                std::cout << "111111111111" << std::endl;
                markers_msg_.markers.clear();
                dijkstra_planner_->pointPlanner(path, twist, markers_msg_);
                twist_pub_->publish(twist);
                marker_array_pub_->publish(markers_msg_);
                // pose_pub_->publish(target);
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