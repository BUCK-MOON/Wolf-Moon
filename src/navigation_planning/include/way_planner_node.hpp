#include <rclcpp/rclcpp.hpp>
#include <rclcpp/publisher.hpp>
#include "rclcpp_action/rclcpp_action.hpp"

#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <nav2_costmap_2d/costmap_2d_ros.hpp>
#include <nav2_costmap_2d/cost_values.hpp>
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include <grid_map_msgs/msg/grid_map.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav2_costmap_2d/costmap_layer.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_core/grid_map_core.hpp>
#include <grid_map_core/GridMapMath.hpp>
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
#include <geometry_msgs/msg/transform_stamped.hpp>
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
#include "color.hpp"

namespace navigation
{
    struct MapData
    {
        MapData();
        ~MapData();
        std::string image_file_name_;
        // MapMode mode_;
        double resolution_{0};
        double origin_x_, origin_y_;
        bool negate_;
        double free_thresh_;
        double occupied_thresh_;

        bool loadMapFromYaml(const std::string &yaml_path);
        bool loadMapFromFile();
        cv::Mat map_image_;
        nav_msgs::msg::OccupancyGrid occ_msg_;
        grid_map::GridMap global_map_;
    };

    class WayPlannerNode : public rclcpp::Node
    {
    public:
        // MapData map_param_;
        std::unique_ptr<MapData> map_param_;
        WayPlannerNode(const rclcpp::NodeOptions &options = rclcpp::NodeOptions());
        ~WayPlannerNode();
        // unsigned int goal_x, goal_y;
        // TF2
         std::mutex map_mutex_,pos_mutex_;
        // std::recursive_mutex map_mutex_,pos_mutex_; // 线程锁

        std::unique_ptr<tf2_ros::Buffer> tf_buffer_;
        std::shared_ptr<tf2_ros::TransformListener> tf_;
        grid_map::Position goal_pos_;
        std::unique_ptr<std::thread> loop_send_thread_;


    private:
        void run();

        void initParam();
        void initSubscribers();
        void initPublishers();
        // void initSerives();
        void init();

        // 占据地图发布者
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_pub_;
        void publishMap();
        // 路径发布者
        rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
        // 栅格地图接受者
        rclcpp::Subscription<grid_map_msgs::msg::GridMap>::SharedPtr grid_map_sub_;
        void gridMapCallback(const grid_map_msgs::msg::GridMap::SharedPtr msg);
        // 目标点发布者
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_pub_;

        // 目标地址接受者
        rclcpp_action::Server<nav2_msgs::action::NavigateToPose>::SharedPtr action_server_;

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