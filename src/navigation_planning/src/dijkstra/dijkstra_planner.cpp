#include "../../include/dijkstra/dijkstra_planner.hpp"
namespace navigation
{

    grid_map::Index DijkstraPlanner::findNearestUnoccupiedPoint(const grid_map::GridMap &map, const grid_map::Index &start_index)
    {
        // 获取周围邻近的点
        grid_map::Index closest_unoccupied_index = start_index;
        int search_radius = 1; // 搜索半径，可以根据需要调整
        // auto cost_layer = map["combined"];
        auto cost_layer = map["combined"];

        while (true)
        {
            for (int dy = -search_radius; dy <= search_radius; ++dy)
            {
                for (int dx = -search_radius; dx <= search_radius; ++dx)
                {
                    // 获取该点的占据状态，假设 "occupancy" 图层表示占据情况，0 表示未占据
                    if (cost_layer(start_index(0) + dx, start_index(1) + dy) < obstacle_thresh_)
                    {
                        // 找到第一个未占据的点
                        return grid_map::Index(start_index(0) + dx, start_index(1) + dy);
                    }
                }
            }
            search_radius++;
        }

        // 如果没有找到未占据的点，返回起始点
        return closest_unoccupied_index;
    }

    // 如果没有找到未占据的点，返回起始点
    DijkstraPlanner::DijkstraPlanner()
    {
        // angle_threshold_ = angle_threshold_ * M_PI / 180.0;
    }
    DijkstraPlanner::~DijkstraPlanner()
    {
    }
    bool DijkstraPlanner::pathPlanner(std::unique_ptr<MapProcessor> &map_processor, nav_msgs::msg::Path &path)
    {

        if (!map_processor->global_map_.isInside(map_processor->start_pos_) || !map_processor->global_map_.isInside(map_processor->goal_pos_))
        {
            RCLCPP_ERROR(rclcpp::get_logger("dijkstra_planner"), "Start or goal outside map!");
            return false;
        }
        auto cost_layer = map_processor->global_map_["combined"];
        grid_map::Index start_index, goal_index;
        if (map_processor->global_map_.getIndex(map_processor->start_pos_, start_index))
        {
            std::cout << start_index << std::endl;

            // RCLCPP_WARN(rclcpp::get_logger("dijkstra_planner"), "Failed to get start or goal index!");
            start_index = findNearestUnoccupiedPoint(map_processor->global_map_, start_index);
        }
        if (map_processor->global_map_.getIndex(map_processor->goal_pos_, goal_index))
        {
            // RCLCPP_ERROR(rclcpp::get_logger("dijkstra_planner"), "Failed to get start or goal index!");
            goal_index =findNearestUnoccupiedPoint(map_processor->global_map_, goal_index);
        }
        // Dijkstra算法实现
        const float INF = std::numeric_limits<float>::max();
        grid_map::Size map_size = map_processor->global_map_.getSize();

        // 初始化距离矩阵和访问矩阵
        distances_ = Eigen::MatrixXf::Constant(map_size(0), map_size(1), INF);
        visited_ = Eigen::MatrixXi::Zero(map_size(0), map_size(1));
        previous_x_ = Eigen::MatrixXi::Constant(map_size(0), map_size(1), -1);
        previous_y_ = Eigen::MatrixXi::Constant(map_size(0), map_size(1), -1);
        // 使用优先队列存储待访问节点 (距离, x, y)
        // 设置起点距离为0
        distances_(start_index(0), start_index(1)) = 0;
        PriorityQueue queue;
        queue.emplace(0, start_index(0), start_index(1));

        // 定义8个方向的邻域

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
            if (visited_(x, y) || current_dist > distances_(x, y))
                continue;

            visited_(x, y) = 1;

            // 检查所有邻域
            for (int i = 0; i < 8; ++i)
            {
                int nx = x + dx_[i];
                int ny = y + dy_[i];

                // 检查边界
                if (nx < 0 || nx >= map_size(0) || ny < 0 || ny >= map_size(1))
                    continue;

                // 检查是否可通行 (假设NaN或大于某个阈值为障碍物)
                float cost = cost_layer(nx, ny);
                if (std::isnan(cost) || cost > obstacle_thresh_) // 调整阈值根据实际情况
                    continue;

                // 计算新距离 (对角线移动距离为sqrt(2))
                float new_dist = current_dist + ((dx_[i] != 0 && dy_[i] != 0) ? sqrt2_ : 1.0f); //

                // 如果找到更短路径
                if (new_dist < distances_(nx, ny))
                {
                    distances_(nx, ny) = new_dist;
                    previous_x_(nx, ny) = x;
                    previous_y_(nx, ny) = y;
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
                int prev_x = previous_x_(x, y);
                int prev_y = previous_y_(x, y);
                x = prev_x;
                y = prev_y;
            }

            std::reverse(path_indices.begin(), path_indices.end());

            // 转换为Path消息
            for (const auto &index : path_indices)
            {
                grid_map::Position position;
                map_processor->global_map_.getPosition(index, position);

                geometry_msgs::msg::PoseStamped pose;
                pose.header = path.header;
                pose.pose.position.x = position.x();
                pose.pose.position.y = position.y();
                pose.pose.position.z = 0.0;
                pose.pose.orientation.w = 1.0;

                path.poses.push_back(pose);
            }
            smoothPath(path);
            RCLCPP_INFO(rclcpp::get_logger("dijkstra_planner"), "found path size %li", path.poses.size());

            return true;
        }
        else
        {
            RCLCPP_WARN(rclcpp::get_logger("dijkstra_planner"), "No path found from start to goal!");
            return false;
            // continue;
        }
    }

    void DijkstraPlanner::pointPlanner(nav_msgs::msg::Path &path, geometry_msgs::msg::Twist &twist, visualization_msgs::msg::MarkerArray &markers_msg)
    {
        Point dir = {0, 0};
        geometry_msgs::msg::PoseStamped target = getTargetPoint(path, dir);
        visualization_msgs::msg::Marker marker;
        Point path_dir = {target.pose.position.x - path.poses[0].pose.position.x,
                          target.pose.position.y - path.poses[0].pose.position.y};
        double distance = std::sqrt(path_dir.x * path_dir.x + path_dir.y * path_dir.x);
        double theta = std::atan2(path_dir.y / abs(path_dir.y) * abs(dir.y),
                                  path_dir.x / abs(path_dir.x) * abs(dir.x));
        marker.header.stamp = rclcpp::Clock().now(); // 设置时间戳
        marker.id = 0;
        marker.header.frame_id = "map";
        marker.ns = "markers";                                // 设置命名空间
        marker.type = visualization_msgs::msg::Marker::ARROW; // 或者 LINE_LIST
        marker.action = visualization_msgs::msg::Marker::ADD;
        marker.pose = path.poses[0].pose;
        marker.pose.position.x = marker.pose.position.x + ((threshold_) / 2) * std::cos(theta);
        marker.scale.x = distance; // 线段的宽度
        marker.scale.y = threshold_;
        marker.scale.z = 0.01;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 1.0f;
        marker.color.a = 0.5f;
        marker.pose.orientation.x = std::cos(theta / 2.0);
        marker.pose.orientation.y = std::sin(theta / 2.0);
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 0.0;
        markers_msg.markers.emplace_back(marker);

        theta = std::atan2(path_dir.y, path_dir.x);
        marker.id = 1;
        marker.scale.x = motion_offset_; // 线段的宽度s
        marker.scale.y = 0.01;
        marker.scale.z = 0.01;
        marker.color.r = 1.0f;
        marker.color.g = 0.0f;
        marker.color.b = 1.0f;
        marker.color.a = 1.0f;
        marker.pose.orientation.x = std::cos(theta / 2.0);
        marker.pose.orientation.y = std::sin(theta / 2.0);
        marker.pose.orientation.z = 0.0;
        marker.pose.orientation.w = 0.0;
        markers_msg.markers.emplace_back(marker);

        twist.linear.x = path.poses[0].pose.position.x + motion_offset_ * std::cos(theta);
        twist.linear.y = path.poses[0].pose.position.y + motion_offset_ * std::sin(theta);
        marker.id = 2;
        marker.type = visualization_msgs::msg::Marker::SPHERE; // 或者 LINE_LIST
        marker.pose.position.x = twist.linear.x + ((threshold_) / 2) * std::cos(theta);
        marker.pose.position.y = twist.linear.y;
        marker.scale.x = threshold_; // 线段的宽度
        marker.scale.y = threshold_;
        // marker.scale.z = 0.1;
        marker.color.r = 1.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0f;
        markers_msg.markers.emplace_back(marker);
    }

    void DijkstraPlanner::smoothPath(nav_msgs::msg::Path &path)
    {
        if (path.poses.size() < 3)
            return; // 路径太短无需平滑

        std::vector<geometry_msgs::msg::PoseStamped> new_poses = path.poses;
        double change = tolerance_;

        for (int iter = 0; iter < max_iterations_ && change >= tolerance_; ++iter)
        {
            change = 0.0;
            // 跳过第一个和最后一个点（保持起点和终点不变）
            for (size_t i = 1; i < new_poses.size() - 1; ++i)
            {
                geometry_msgs::msg::Point prev_point = new_poses[i - 1].pose.position;
                geometry_msgs::msg::Point curr_point = new_poses[i].pose.position;
                geometry_msgs::msg::Point next_point = new_poses[i + 1].pose.position;
                geometry_msgs::msg::Point original_point = path.poses[i].pose.position;

                // 计算梯度
                double delta_x = alpha_ * (original_point.x - curr_point.x) + beta_ * (prev_point.x + next_point.x - 2 * curr_point.x);
                double delta_y = alpha_ * (original_point.y - curr_point.y) + beta_ * (prev_point.y + next_point.y - 2 * curr_point.y);

                // 更新点坐标
                new_poses[i].pose.position.x += delta_x;
                new_poses[i].pose.position.y += delta_y;

                change += std::abs(delta_x) + std::abs(delta_y);
            }
        }
        path.poses = new_poses;
    }
    double DijkstraPlanner::cross(const Point &O, const Point &A, const Point &B)
    {
        return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    }

    std::vector<Point> DijkstraPlanner::computeConvexHull(std::vector<Point> points)
    {
        int n = points.size();
        if (n <= 1)
            return points;
        std::sort(points.begin(), points.end());
        std::vector<Point> hull;
        hull.reserve(n + 1);
        for (int i = 0; i < n; ++i)
        {
            while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        int lower_hull_size = hull.size();
        for (int i = n - 2; i >= 0; --i)
        {
            while (hull.size() > lower_hull_size && cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
            {
                hull.pop_back();
            }
            hull.push_back(points[i]);
        }
        if (hull.size() > 1)
        {
            hull.pop_back();
        }
        return hull;
    }

    // 计算凸包的最小宽度（即两条平行支撑线的最小间距）
    double DijkstraPlanner::computeConvexHullWidth(const std::vector<Point> &convex_hull, Point &dir)
    {
        int n = convex_hull.size();
        // 处理退化情况
        if (n <= 1)
            return 0.0;
        if (n == 2) // 两点构成线段的情况
        {
            const Point &a = convex_hull[0];
            const Point &b = convex_hull[1];
            dir = {b.x - a.x, b.y - a.y};            // 方向向量
            return std::hypot(a.x - b.x, a.y - b.y); // 直接返回线段长度
        }
        // 初始化最小宽度为最大值
        double min_width = std::numeric_limits<double>::max();
        int j = 1; // 对踵点指针（使用旋转卡壳算法）

        for (int i = 0; i < n; ++i)
        {
            // 当前边AB：A=convex_hull[i], B=convex_hull[(i+1)%n]
            const Point &a = convex_hull[i];
            const Point &b = convex_hull[(i + 1) % n];
            while (true)
            {
                const Point &c = convex_hull[j];           // 当前候选点C
                const Point &d = convex_hull[(j + 1) % n]; // 下一个候选点D
                // 通过叉积比较面积（等效比较点到直线的距离）
                double current_area = cross(a, b, c);
                double next_area = cross(a, b, d);
                if (next_area > current_area)
                {
                    j = (j + 1) % n;
                }
                else
                {
                    break;
                }
            }
            double distance = std::abs(cross(a, b, convex_hull[j])) / std::hypot(b.x - a.x, b.y - a.y);
            if (distance < min_width)
            {
                min_width = distance;
                dir = {b.x - a.x, b.y - a.y}; // 平行线1的方向向量
            }
        }

        return min_width;
    }

    geometry_msgs::msg::PoseStamped DijkstraPlanner::getTargetPoint(nav_msgs::msg::Path &path, Point &dir)
    {
        if (path.poses.empty())
        {
            throw std::runtime_error("Empty path");
        }

        std::vector<Point> current_points;
        // Point dir = {0, 0};
        for (size_t i = 0; i < path.poses.size(); ++i)
        {
            const auto &pose = path.poses[i];
            Point pt;
            pt.x = pose.pose.position.x;
            pt.y = pose.pose.position.y;
            current_points.push_back(pt);

            // 当有至少两个点时开始进行凸包宽度检测
            if (current_points.size() >= 2)
            {
                // 步骤1：计算当前点集的凸包（最小包围多边形）
                std::vector<Point> convex_hull = computeConvexHull(current_points);
                // 步骤2：使用旋转卡壳法计算凸包的最小宽度
                double width = computeConvexHullWidth(convex_hull, dir);
                if (width > threshold_)
                { // threshold_ 是类成员变量，表示阈值
                    if (i == 0)
                    {
                        // 当只有两个点且超过阈值时，返回第一个点
                        return path.poses[0];
                    }
                    else
                    {
                        // 返回前一个点
                        return path.poses[i - 1];
                    }
                }
            }
        }

        // 所有点处理完仍未超过阈值，返回最后一个点
        return path.poses.back();
    }
}
