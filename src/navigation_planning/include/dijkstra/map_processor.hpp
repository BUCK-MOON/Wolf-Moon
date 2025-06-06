#ifndef NAVIGATION_PLANNING__MAP_PROCESSOR_
#define NAVIGATION_PLANNING__MAP_PROCESSOR_
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
// #include <geometry_msgs/msg/Pose2D.h>
#include <geometry_msgs/msg/twist.hpp>
#include <nav2_costmap_2d/costmap_layer.hpp>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_core/grid_map_core.hpp>
#include <grid_map_core/GridMapMath.hpp>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

namespace navigation
{
    struct MapProcessor
    {
        MapProcessor();
        ~MapProcessor();
        std::string image_file_name_;
        // MapMode mode_;
        double resolution_{0};
        double origin_x_, origin_y_;
        bool negate_;
        double free_thresh_;
        double occupied_thresh_;
        grid_map::Position goal_pos_,start_pos_;


        double robot_radius_=0.3;
        double obstacle_offset_=0.2;

        bool loadMapFromYaml(const std::string &yaml_path);
        bool loadMapFromFile();
        void inflateObstacles(cv::Mat& map_image); 
        void combinedMap(const grid_map_msgs::msg::GridMap::SharedPtr local_map);
        cv::Mat map_image_;
        nav_msgs::msg::OccupancyGrid occ_msg_;
        grid_map::GridMap global_map_;
    };
}

#endif