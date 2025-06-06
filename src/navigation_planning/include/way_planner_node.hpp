#include <rclcpp/rclcpp.hpp>
#include <rclcpp/publisher.hpp>
#include "rclcpp_action/rclcpp_action.hpp"

#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <rmw/qos_profiles.h>
#include <rclcpp/qos.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/duration.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float64.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <message_filters/subscriber.h>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_ros/transform_broadcaster.h>
#include "geometry_msgs/msg/pose_stamped.hpp"

// #include <nav2_behavior_tree/plugins/action/navigate_to_pose_action.hpp>

#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>

#include <queue>
#include <unordered_set>
#include <cmath>
#include <mutex>
#include <memory>
#include <atomic>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <termios.h> //
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/netlink.h>
#include <string>
#include "dijkstra/color.hpp"
#include "dijkstra/map_processor.hpp"
#include "dijkstra/dijkstra_planner.hpp"

namespace navigation
{

    class WayPlannerNode : public rclcpp::Node
    {
    public:
        // MapData map_param_;
        std::unique_ptr<MapProcessor> map_processor_;
        std::unique_ptr<DijkstraPlanner> dijkstra_planner_;
        WayPlannerNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
        ~WayPlannerNode();
        // unsigned int goal_x, goal_y;
        // TF2
        std::mutex map_mutex_, pos_mutex_;
        // std::recursive_mutex map_mutex_,pos_mutex_; // 线程锁

        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        std::shared_ptr<tf2_ros::TransformListener> tf_;
        grid_map::Position goal_pos_;
        std::unique_ptr<std::thread> loop_send_thread_;
        bool flag_=false;
        double goal_thresh_ = 0.3;

    private:
        void
        run();

        void initParam();
        void initSubscribers();
        void initPublishers();
        // void initSerives();
        void init();

        // 占据地图发布者
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr base_map_pub_;
        rclcpp::Publisher<grid_map_msgs::msg::GridMap>::SharedPtr global_map_pub_;
        // rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr pose_pub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_array_pub_; // rviz消息
        visualization_msgs::msg::MarkerArray markers_msg_;                                    // 可视化消息
        void publishMap();
        // 路径发布者
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
        // 栅格地图接受者
        rclcpp::Subscription<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_sub_;
        void gridMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr msg);
        // 订阅者成员变量
        rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr goal_sub_;
        void onGoalPoseReceived(const geometry_msgs::msg::PoseStamped::SharedPtr msg);
        rclcpp_action::Server<nav2_msgs::action::NavigateToPose>::SharedPtr action_server_;

        // 目标点发布者
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;

        // 目标地址接受者

        rclcpp_action::GoalResponse handleGoal(const rclcpp_action::GoalUUID &uuid,
                                               std::shared_ptr<const nav2_msgs::action::NavigateToPose::Goal> goal);
        bool isGoalValid(const geometry_msgs::msg::PoseStamped &pose);
        rclcpp_action::CancelResponse handleCancel(const std::shared_ptr<rclcpp_action::ServerGoalHandle<nav2_msgs::action::NavigateToPose>> goal_handle);
        void handleAccepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<nav2_msgs::action::NavigateToPose>> goal_handle);

        // 规划补偿发布者
        rclcpp::Publisher<nav2_msgs::action::NavigateToPose::Impl::FeedbackMessage>::SharedPtr nav_feedback_pub_;

        // 规划状态发布者
        rclcpp::Publisher<action_msgs::msg::GoalStatusArray>::SharedPtr goal_status_pub_;
    };
}