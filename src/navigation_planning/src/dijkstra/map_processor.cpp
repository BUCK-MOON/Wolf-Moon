#include "../../include/dijkstra/map_processor.hpp"
namespace navigation
{
    MapProcessor::MapProcessor()
    {
    }

    MapProcessor::~MapProcessor()
    {
    }
    bool MapProcessor::loadMapFromYaml(const std::string &yaml_name)
    {
        std::string package = ament_index_cpp::get_package_share_directory("navigation_planning");
        std::string path = package + "/map/" + yaml_name;
        // 解析YAML文件
        YAML::Node config = YAML::LoadFile(path);

        // 获取地图信息
        if (!config["image"])
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "YAML lack 'image' param");
            return false;
        }
        image_file_name_ = config["image"].as<std::string>();
        // 从YAML文件路径推断PGM文件的完整路径
        image_file_name_ = package + "/map/" + image_file_name_;
        resolution_ = config["resolution"].as<double>();
        if (resolution_ <= 0)
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "invalid resolution: %f", resolution_);
            return false;
        }

        if (!config["origin"] || config["origin"].size() < 2)
        {
            RCLCPP_ERROR(rclcpp::get_logger("MapData"), "invalid or lack 'origine' param");
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
                        "occupied thresh (%f)should be greater than free thresh(%f)",
                        occupied_thresh_, free_thresh_);
        }
        loadMapFromFile();
        return true;
    }
    bool MapProcessor::loadMapFromFile()
    {
        // 使用OpenCV加载PGM图像
        cv::Mat map_image = cv::imread(image_file_name_, cv::IMREAD_GRAYSCALE);
        if (map_image.empty())
        {
            return false;
        }
        inflateObstacles(map_image);
        // cv::imshow("map", map_image);
        // cv::waitKey(0);
        // 获取代价地图指针
        // 初始化OccupancyGrid消息
        occ_msg_.header.frame_id = "local";
        occ_msg_.info.resolution = resolution_;
        occ_msg_.info.width = map_image.cols;
        occ_msg_.info.height = map_image.rows;
        occ_msg_.info.origin.position.x = origin_x_;
        occ_msg_.info.origin.position.y = origin_y_;
        occ_msg_.info.origin.orientation.w = 1.0; // 默认无旋转
        occ_msg_.data.resize(occ_msg_.info.width * occ_msg_.info.height);

        global_map_.setFrameId("local");
        global_map_.setGeometry(grid_map::Length(map_image.cols, map_image.rows), resolution_);
        // global_map_.add("local_map",0.0); // 预分配局部地图图层
        global_map_.add("combined", 0.0);
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
                    occupancy_value = 0; // 0表示自由
                }
                else if (pixel >= occupied_pixel) // 障碍物
                {
                    occupancy_value = 1; // 100表示完全占据
                }
                occ_msg_.data[flipped_y * occ_msg_.info.width + x] = occupancy_value;
            }
        }
        // global_map_.add("elevation");
        grid_map::GridMapRosConverter::fromOccupancyGrid(occ_msg_, "elevation", global_map_);
        // RCLCPP_INFO_STREAM(this->get_logger(), BLUE << "load map success" << RESET);
        return true;
    }
    void MapProcessor::inflateObstacles(cv::Mat &map_image)
    {
        cv::bitwise_not(map_image, map_image);
        int dilation_size = static_cast<int>(robot_radius_ / resolution_);
        cv::Mat kernel = cv::getStructuringElement(
            cv::MORPH_ELLIPSE,
            cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1));
        cv::dilate(map_image, map_image, kernel);
    }
    void MapProcessor::combinedMap(grid_map_msgs::msg::GridMap::SharedPtr local_msg)
    {
        global_map_["combined"] = global_map_["elevation"];
        grid_map::GridMap local_map;
        grid_map::GridMapRosConverter::fromMessage(*local_msg, local_map);
        /////
        grid_map::Matrix &data = local_map["elevation"];
        grid_map::Matrix dilated_data = data;

        int rows = data.rows();
        int cols = data.cols();
        // std::cout << rows << "," << cols << std::endl;
        int dilation_radius = 6; // 单次膨胀半径（像素）
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {

                if (data(i, j)>-0.4)
                {
                    //     data(i, j) = 0.0;
                    // 如果是障碍物或已经膨胀的区域，就继续向外膨胀
                    for (int di = -dilation_radius; di <= dilation_radius; ++di)
                    {
                        for (int dj = -dilation_radius; dj <= dilation_radius; ++dj)
                        {
                            // 圆形膨胀（可选）
                            float distance = std::sqrt(di * di + dj * dj);
                            if (distance > dilation_radius)
                                continue;

                            int ni = i + di;
                            int nj = j + dj;

                            if (ni >= 0 && ni < rows && nj >= 0 && nj < cols)
                            {

                                // 更新膨胀区域
                                dilated_data(ni, nj) = std::max(data(i, j), dilated_data(ni, nj));
                            }
                        }
                    }
                }
            }
        }

        // Copy the result back to the original matrix
         data = dilated_data;
        //

        // 4. 将局部地图数据转换到全局坐标系
        for (grid_map::GridMapIterator it(local_map); !it.isPastEnd(); ++it)
        {
            // 6.1 获取局部地图单元格的值
            const float cell_value = local_map.at("elevation", *it) + 0.5+obstacle_offset_;

            // 6.2 仅处理障碍物（值超过阈值）
            // if (cell_value < 0.0)
            // {
            //     continue; // 忽略自由空间和未知区域
            // }
            // 获取局部地图单元格的位置
            grid_map::Position local_pos;
            local_map.getPosition(*it, local_pos);
            // 将数据写入全局地图（若在范围内）
            if (global_map_.isInside(local_pos))
            {

                float &global_value = global_map_.atPosition("combined", local_pos);
                // global_value*=100;
                // std::cout << global_value << cell_value << std::endl;

                global_value = std::max(global_value, cell_value);
            }
        }
    }

}