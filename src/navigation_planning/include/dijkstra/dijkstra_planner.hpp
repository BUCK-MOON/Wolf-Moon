#ifndef NAVIGATION_PLANNING__DIJKSTRA_PLANNER_
#define NAVIGATION_PLANNING__DIJKSTRA_PLANNER_
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <nav2_costmap_2d/costmap_2d_ros.hpp>
#include <nav2_costmap_2d/cost_values.hpp>
#include "nav2_msgs/action/navigate_to_pose.hpp"
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <grid_map_msgs/msg/grid_map.hpp>
#include <geometry_msgs/msg/transform_stamped.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
// #include <geometry_msgs/msg/Pose2D.h>
#include <geometry_msgs/msg/twist.hpp>
#include <nav2_costmap_2d/costmap_layer.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_core/grid_map_core.hpp>
#include <grid_map_core/GridMapMath.hpp>
#include <yaml-cpp/yaml.h>
#include <rclcpp/rclcpp.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include "map_processor.hpp"
namespace navigation
{
    struct Point
    {
        double x, y;
        bool operator<(const Point &other) const
        {
            return x < other.x || (x == other.x && y < other.y);
        }
    };
    class DijkstraPlanner
    {
        // planner
        Eigen::MatrixXf distances_;  // 距离矩阵
        Eigen::MatrixXi visited_;    // 访问标记矩阵
        Eigen::MatrixXi previous_x_; // 前驱节点 X 坐标
        Eigen::MatrixXi previous_y_; // 前驱节点 Y 坐标
        using QueueElement = std::tuple<float, int, int>;
        using PriorityQueue = std::priority_queue<QueueElement, std::vector<QueueElement>, std::greater<QueueElement>>;
        const int dx_[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy_[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        const float sqrt2_ = std::sqrt(1.414f);
        double obstacle_thresh_ = 0.6;
        // smoot
        double alpha_ = 0.1;      // 权重：原始路径吸引力
        double beta_ = 0.3;       // 权重：平滑度
        int max_iterations_ = 50; // 最大迭代次数
        double tolerance_ = 0.01; // 收敛阈值
        // point
        double threshold_ = 0.1;
        double motion_offset_ = 0.5;

    public:
        DijkstraPlanner();
        ~DijkstraPlanner();

        bool pathPlanner(std::unique_ptr<MapProcessor> &processor, nav_msgs::msg::Path &path);
        grid_map::Index findNearestUnoccupiedPoint(const grid_map::GridMap &map, const grid_map::Index &start_index);
        void smoothPath(nav_msgs::msg::Path &path);
        void pointPlanner(nav_msgs::msg::Path &path, geometry_msgs::msg::Twist &twist, visualization_msgs::msg::MarkerArray &markers_msg);
        geometry_msgs::msg::PoseStamped getTargetPoint(nav_msgs::msg::Path &path, Point &dir);
        double cross(const Point &O, const Point &A, const Point &B);
        std::vector<Point> computeConvexHull(std::vector<Point> points);
        double computeConvexHullWidth(const std::vector<Point> &convex_hull, Point &dir);
    };
}

#endif