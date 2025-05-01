#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav2_costmap_2d/costmap_2d.hpp>
#include <nav2_costmap_2d/costmap_2d_ros.hpp>
#include <nav2_costmap_2d/cost_values.hpp>
#include <yaml-cpp/yaml.h>
#include <opencv2/opencv.hpp>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <memory>

class DijkstraPlanner : public rclcpp::Node
{
public:
    DijkstraPlanner() : Node("dijkstra_planner"), costmap_ros_(std::make_shared<nav2_costmap_2d::Costmap2DROS>("global_costmap"))
    {
        // 初始化代价地图
        costmap_ros_->on_configure(rclcpp_lifecycle::State());

        // 声明参数
        this->declare_parameter("map_yaml_path", "");
        this->declare_parameter("start_x", 0.0);
        this->declare_parameter("start_y", 0.0);
        this->declare_parameter("goal_x", 10.0);
        this->declare_parameter("goal_y", 10.0);

        // 获取参数
        std::string map_yaml_path = this->get_parameter("map_yaml_path").as_string();
        start_x_ = this->get_parameter("start_x").as_double();
        start_y_ = this->get_parameter("start_y").as_double();
        goal_x_ = this->get_parameter("goal_x").as_double();
        goal_y_ = this->get_parameter("goal_y").as_double();

        // 加载地图到代价地图
        if (!loadMapToCostmap(map_yaml_path))
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to load map!");
            return;
        }

        // 创建发布者
        path_pub_ = this->create_publisher<nav_msgs::msg::Path>("global_path", 10);

        // 执行路径规划
        planPath();

        // 发布路径
        publishPath();
    }

private:
    struct Node
    {
        unsigned int x, y;
        double cost;
        Node* parent;

        Node(unsigned int x, unsigned int y, double cost, Node* parent = nullptr)
            : x(x), y(y), cost(cost), parent(parent) {}

        bool operator==(const Node& other) const
        {
            return x == other.x && y == other.y;
        }
    };

    struct NodeHash
    {
        size_t operator()(const Node& node) const
        {
            return std::hash<unsigned int>()(node.x) ^ std::hash<unsigned int>()(node.y);
        }
    };

    struct CompareNode
    {
        bool operator()(const Node* a, const Node* b) const
        {
            return a->cost > b->cost;
        }
    };

    bool loadMapToCostmap(const std::string& yaml_path)
    {
        try
        {
            // 解析YAML文件
            YAML::Node config = YAML::LoadFile(yaml_path);

            // 获取地图信息
            std::string image_path = config["image"].as<std::string>();
            resolution_ = config["resolution"].as<double>();
            origin_x_ = config["origin"][0].as<double>();
            origin_y_ = config["origin"][1].as<double>();

            // 从YAML文件路径推断PGM文件的完整路径
            std::string pgm_path = yaml_path.substr(0, yaml_path.find_last_of('/') + 1) + image_path;

            // 使用OpenCV加载PGM图像
            cv::Mat map_image = cv::imread(pgm_path, cv::IMREAD_GRAYSCALE);
            if (map_image.empty())
            {
                RCLCPP_ERROR(this->get_logger(), "Failed to load map image: %s", pgm_path.c_str());
                return false;
            }

            // 获取代价地图指针
            auto costmap = costmap_ros_->getCostmap();
            
            // 调整代价地图大小
            costmap->resizeMap(map_image.cols, map_image.rows, resolution_, origin_x_, origin_y_);

            // 填充代价地图
            for (unsigned int y = 0; y < costmap->getSizeInCellsY(); ++y)
            {
                for (unsigned int x = 0; x < costmap->getSizeInCellsX(); ++x)
                {
                    int pixel = map_image.at<uchar>(y, x);
                    
                    // 转换为Nav2代价值
                    unsigned char cost;
                    if (pixel == 205) // 未知区域
                    {
                        cost = nav2_costmap_2d::NO_INFORMATION;
                    }
                    else if (pixel >= 254) // 自由空间
                    {
                        cost = nav2_costmap_2d::FREE_SPACE;
                    }
                    else // 障碍物
                    {
                        cost = nav2_costmap_2d::LETHAL_OBSTACLE;
                    }
                    
                    costmap->setCost(x, y, cost);
                }
            }

            RCLCPP_INFO(this->get_logger(), "Costmap loaded successfully. Size: %dx%d", 
                       costmap->getSizeInCellsX(), costmap->getSizeInCellsY());
            return true;
        }
        catch (const YAML::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "YAML parsing error: %s", e.what());
            return false;
        }
        catch (const cv::Exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "OpenCV error: %s", e.what());
            return false;
        }
    }

    void planPath()
    {
        auto costmap = costmap_ros_->getCostmap();
        
        // 将世界坐标转换为地图坐标
        unsigned int start_x, start_y;
        unsigned int goal_x, goal_y;
        
        if (!costmap->worldToMap(start_x_, start_y_, start_x, start_y) ||
            !costmap->worldToMap(goal_x_, goal_y_, goal_x, goal_y))
        {
            RCLCPP_ERROR(this->get_logger(), "Start or goal position is outside of the map!");
            return;
        }

        // 检查起点和终点是否有效
        if (!isValid(start_x, start_y) || !isValid(goal_x, goal_y))
        {
            RCLCPP_ERROR(this->get_logger(), "Start or goal position is invalid!");
            return;
        }

        // 优先队列用于Dijkstra算法
        std::priority_queue<Node*, std::vector<Node*>, CompareNode> open_set;
        std::unordered_set<Node, NodeHash> closed_set;

        // 创建起点节点
        Node* start_node = new Node(start_x, start_y, 0.0);
        open_set.push(start_node);

        // 8个可能的移动方向
        const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        const double move_cost[] = {1.414, 1.0, 1.414, 1.0, 1.0, 1.414, 1.0, 1.414};

        bool path_found = false;
        Node* goal_node = nullptr;

        while (!open_set.empty())
        {
            Node* current = open_set.top();
            open_set.pop();

            // 检查是否到达目标
            if (current->x == goal_x && current->y == goal_y)
            {
                goal_node = current;
                path_found = true;
                break;
            }

            // 检查是否已经处理过该节点
            if (closed_set.count(*current))
            {
                delete current;
                continue;
            }

            closed_set.insert(*current);

            // 探索邻居
            for (int i = 0; i < 8; ++i)
            {
                unsigned int nx = current->x + dx[i];
                unsigned int ny = current->y + dy[i];

                // 检查边界
                if (nx >= costmap->getSizeInCellsX() || ny >= costmap->getSizeInCellsY())
                    continue;

                if (!isValid(nx, ny))
                    continue;

                // 计算新成本
                double new_cost = current->cost + move_cost[i] * getCostMultiplier(nx, ny);

                // 创建新节点
                Node* neighbor = new Node(nx, ny, new_cost, current);

                // 如果邻居已经在closed_set中，跳过
                if (closed_set.count(*neighbor))
                {
                    delete neighbor;
                    continue;
                }

                open_set.push(neighbor);
            }
        }

        if (path_found)
        {
            // 回溯路径
            Node* current = goal_node;
            while (current != nullptr)
            {
                path_.push_back({current->x, current->y});
                current = current->parent;
            }
            std::reverse(path_.begin(), path_.end());

            RCLCPP_INFO(this->get_logger(), "Path found with %zu waypoints!", path_.size());
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to find a path!");
        }

        // 清理内存
        while (!open_set.empty())
        {
            delete open_set.top();
            open_set.pop();
        }
    }

    bool isValid(unsigned int x, unsigned int y) const
    {
        auto costmap = costmap_ros_->getCostmap();
        unsigned char cost = costmap->getCost(x, y);
        
        // 在Nav2中，LETHAL_OBSTACLE(254)和NO_INFORMATION(255)是不可通行的
        return cost < nav2_costmap_2d::INSCRIBED_INFLATED_OBSTACLE;
    }

    double getCostMultiplier(unsigned int x, unsigned int y) const
    {
        auto costmap = costmap_ros_->getCostmap();
        unsigned char cost = costmap->getCost(x, y);
        
        // 根据代价调整移动成本
        if (cost == nav2_costmap_2d::FREE_SPACE) return 1.0;
        if (cost <= nav2_costmap_2d::INSCRIBED_INFLATED_OBSTACLE) return 1.0 + (cost / 10.0);
        return std::numeric_limits<double>::infinity();
    }

    void publishPath()
    {
        if (path_.empty())
            return;

        auto costmap = costmap_ros_->getCostmap();

        nav_msgs::msg::Path path_msg;
        path_msg.header.stamp = this->now();
        path_msg.header.frame_id = costmap_ros_->getGlobalFrameID();

        for (const auto& point : path_)
        {
            double wx, wy;
            costmap->mapToWorld(point.first, point.second, wx, wy);

            geometry_msgs::msg::PoseStamped pose;
            pose.header = path_msg.header;
            pose.pose.position.x = wx;
            pose.pose.position.y = wy;
            pose.pose.orientation.w = 1.0;
            path_msg.poses.push_back(pose);
        }

        path_pub_->publish(path_msg);
        RCLCPP_INFO(this->get_logger(), "Path published!");
    }

    // 成员变量
    std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros_;
    rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
    std::vector<std::pair<unsigned int, unsigned int>> path_;
    double resolution_;
    double origin_x_, origin_y_;
    double start_x_, start_y_;
    double goal_x_, goal_y_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<DijkstraPlanner>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}