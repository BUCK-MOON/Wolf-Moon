#include "../include/armor_detector.hpp"
namespace rm_auto_aim
{
    /**
     * @brief 构造函数，初始化类
     */
    ArmorDetector::ArmorDetector() : logger_(rclcpp::get_logger("armor_detector"))
    {
        std::cout << "1" << std::endl;
        pnp_solver_ = std::make_unique<PnPSolver>();
        std::cout << "1" << std::endl;

        detector_ = std::make_unique<Detector>();
        initConfig();
        auto pkg_path = ament_index_cpp::get_package_share_directory("armor_detector");
        auto network_path = pkg_path + netWork_;
        detector_->initModel(network_path);
    }
    /**
     * @brief 析构函数
     */
    ArmorDetector::~ArmorDetector()
    {
    }

    /**
     * @brief 初始化参数
     */
    void ArmorDetector::initConfig()
    {
        std::cout << "1" << std::endl;
        auto pkg_path = ament_index_cpp::get_package_share_directory("armor_detector");
        std::string init_config_path = pkg_path + "/config/init_config.yaml";
        cv::FileStorage init_config(init_config_path, cv::FileStorage::READ);
        init_config["debug"] >> dictionary["debug"];
        init_config["enemy"] >> dictionary["enemy"];
        init_config["roi"] >> dictionary["roi"];
        init_config["max_armors_cnt"] >> dictionary["max_armors_cnt"];
        init_config.release();
    }
    /**
     * @brief 推理装甲板函数
     */
    bool ArmorDetector::detectArmors(cv::Mat &src, auto_aim_interfaces::msg::Armors &armors_msg_)
    {
        cv::resize(src, src, cv::Size(640, 480));
        // cv::cvtColor(src, src, cv::COLOR_BGR2RGB);

        // cv::flip(src, src, 0);
        if (dictionary["debug"] == 1)
        {
            initConfig();
        }
        // TODO ROI
        std::vector<ArmorObject> objects;
        objects_.swap(objects);
        drawFrameRate(src);
        std::vector<int> armors_id;

        if (detector_->detect(src, objects_))
        {

            sort(objects_.begin(), objects_.end(), [](ArmorObject &prev, ArmorObject &next)
                 { return prev.area > next.area; });
            if ((int)(objects_.size()) > dictionary["max_armors_cnt"])
                objects_.resize(dictionary["max_armors_cnt"]);
            // std::cout << "=======> "<< std::endl;

            std::vector<Tally> armor_tally;
            for (auto &object : objects_)
            {
                std::vector<cv::Point2f> points;
                points.push_back(object.apex[0]);
                points.push_back(object.apex[1]);
                points.push_back(object.apex[2]);
                points.push_back(object.apex[3]);
                cv::Rect rect = cv::boundingRect(points);
                cv::Rect_<float> gram(rect);

                bool is_update = false;
                for (int i = 0; i < (int)(armor_tally_.size()); i++)

                {

                    cv::Rect_<float> inter = gram & armor_tally_[i].rect;
                    float inter_area = inter.area();
                    float union_area = armor_tally_[i].rect.area() + gram.area() - inter_area;
                    if ((inter_area / union_area) > 0.9)
                    {
                        Tally tally;
                        tally.num = armor_tally_[i].num + 1;
                        tally.sum = armor_tally_[i].sum + object.cls;
                        object.cls = round(tally.sum / tally.num);
                        tally.rect = gram;
                        armor_tally.emplace_back(tally);
                        is_update = true;
                    }
                    if (!is_update)
                    {
                        Tally tally;
                        tally.num = 1;
                        tally.sum = object.cls;
                        tally.rect = gram;
                        armor_tally.emplace_back(tally);
                    }
                }
            }
            armor_tally = armor_tally;

            for (auto object : objects_) // 遍历装甲板
            {
                // std::cout << object.color << std::endl;

                // if (object.cls == 0)
                // {
                //     continue;
                // }
                // BEGIN 灰色装甲板识别逻辑
                bool object_jump = false;
                if (object.color / 2 == 3)
                {
                    object_jump = true;
                    for (int id : armors_id_)
                    {
                        if (object.cls == id)
                        {
                            object_jump = false;
                        }
                    }
                }
                if (object_jump)
                {
                    continue;
                }
                // END
                if (object.color / 2 == dictionary["enemy"] || object.color / 2 == 3)
                {
        
                    // cv::Point2f concer = center_[0];
                    for (int i = 0; i < 4; i++)
                    {
                        apex2d_[i] = object.apex[i];
                    }
                    cv::Point2f center(0, 0);
                    for (int i = 0; i < 4; i++)
                    {
                        center += apex2d_[i];
                    }
                    center /= 4;
                    drawArmor(apex2d_, src, center);
                    std::vector<cv::Point2f> points_pic(apex2d_, apex2d_ + 4);
                    if (pnp_solver_->solvePnP(object.color % 2, points_pic, rvec_, tvec_))
                    {
                        // armor_msg_.type = object.color % 2;
                        if (object.color % 2 == 0)
                        {
                            armor_msg_.type = "small";
                        }
                        else
                        {
                            armor_msg_.type = "large";
                        }

                        armor_msg_.number = std::to_string(/*object.cls*/ 4);
                        // armor_msg_.number = std::to_string(5);
                        cv::putText(
                            src, armor_msg_.number, points_pic[0], cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 100, 0}, 1);

                        // std::cout << tvec_ << std::endl;
                        armor_msg_.pose.position.x = tvec_.at<double>(0);
                        armor_msg_.pose.position.y = tvec_.at<double>(1);
                        armor_msg_.pose.position.z = tvec_.at<double>(2); // Fill pose
                        cv::Mat rotation_matrix;
                        cv::Rodrigues(rvec_, rotation_matrix);
                        tf2::Matrix3x3 tf2_rotation_matrix(
                            rotation_matrix.at<double>(0, 0), rotation_matrix.at<double>(0, 1), rotation_matrix.at<double>(0, 2),
                            rotation_matrix.at<double>(1, 0), rotation_matrix.at<double>(1, 1), rotation_matrix.at<double>(1, 2),
                            rotation_matrix.at<double>(2, 0), rotation_matrix.at<double>(2, 1), rotation_matrix.at<double>(2, 2));
                        tf2::Quaternion tf2_q;
                        tf2_rotation_matrix.getRotation(tf2_q);
                        armor_msg_.pose.orientation = tf2::toMsg(tf2_q); // Fill pose
                        armor_msg_.distance_to_image_center = pnp_solver_->calculateDistanceToCenter(center);
                        armors_msg_.armors.emplace_back(std::move(armor_msg_));
                    }
                }
                else
                {
                    continue;
                }
            }

            armors_id_ = armors_id; // 推入这一帧装甲板信息，用于下帧灰色装甲板筛选
        }
        return (armors_msg_.armors.size() != 0) ? true : false;
    }

    bool ArmorDetector::drawState(cv::Mat &src, auto_aim_interfaces::msg::State &state_msg_)
    {
        // if (frame_rate_flag_ == 3)
        // {
        // 瞄准线 //
        line(src, cv::Point(src.cols / 2, 0), cv::Point(src.cols / 2, src.rows), {0, 0, 255}, 1);
        line(src, cv::Point(0, src.rows / 2), cv::Point(src.cols, src.rows / 2), {0, 0, 255}, 1);

        // 普通pitch，yaw///
        float pitch = state_msg_.angle.x;
        float yaw = state_msg_.angle.y;
        cv::putText(src, "TCK:", cv::Point(7, 81), cv::FONT_HERSHEY_SIMPLEX, 1, {0, 0, 255}, 3);
        cv::putText(src, "pitch|" + std::to_string(pitch), cv::Point(87, 67), cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 255, 255}, 2);
        cv::putText(src, "yaw |" + std::to_string(yaw), cv::Point(89, 88), cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 255, 0}, 2);

        // 预测pitch,yaw //
        float pitch_prd = state_msg_.predict.x;
        float yaw_prd = state_msg_.predict.y;
        cv::putText(src, "PRD:", cv::Point(7, 131), cv::FONT_HERSHEY_SIMPLEX, 1, {255, 0, 0}, 3);
        cv::putText(src, "pitch|" + std::to_string(pitch_prd), cv::Point(87, 117), cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 255, 255}, 2);
        cv::putText(src, "yaw |" + std::to_string(yaw_prd), cv::Point(89, 138), cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 255, 0}, 2);

        // 预测点 //
        cv::Point2f calculate = cv::Point2f(state_msg_.calculate.x, state_msg_.calculate.y);
        cv::circle(src, calculate, 7, {247, 0, 247}, -1);
        // mode //
        int mode = state_msg_.mode;
        cv::putText(src, std::to_string(mode), cv::Point(75, 47), cv::FONT_HERSHEY_SIMPLEX, 0.7, {0, 255, 0}, 2);
        cv::putText(src, "mode[ ]", cv::Point(7, 47), cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 0, 255}, 2.3);
        // }
        return true;
    }
    void ArmorDetector::drawArmor(cv::Point2f apex2d[4], cv::Mat src, cv::Point2f center)
    {
        std::vector<cv::Point2f> point = fillArmor(apex2d);
        int distance = cv::norm(apex2d[2] - apex2d[3]);
        cv::circle(src, center, distance, {247, 247, 247}, 3, cv::LINE_AA);
        for (int i = 0; i < 4; i++)
        {
            cv::circle(src, point[i % 4], 1.5 * i, {255, 255, 255}, 2);
            line(src, apex2d[i % 4], apex2d[(i + 1) % 4], {0, 255, 0}, 1);
        }
    }
    std::vector<cv::Point2f> ArmorDetector::fillArmor(cv::Point2f apex2d[4])
    {
        cv::Point2f point[4];
        point[0] = cv::Point(apex2d[0].x + ((apex2d[0].x - apex2d[1].x) / 2), apex2d[0].y - ((apex2d[1].y - apex2d[0].y) / 2));
        point[1] = cv::Point(apex2d[1].x - ((apex2d[0].x - apex2d[1].x) / 2), apex2d[1].y + ((apex2d[1].y - apex2d[0].y) / 2));
        point[2] = cv::Point(apex2d[2].x + ((apex2d[2].x - apex2d[3].x) / 2), apex2d[2].y + ((apex2d[2].y - apex2d[3].y) / 2));
        point[3] = cv::Point(apex2d[3].x - ((apex2d[2].x - apex2d[3].x) / 2), apex2d[3].y - ((apex2d[2].y - apex2d[3].y) / 2));
        std::vector<cv::Point2f> points_pic(point, point + 4);
        return points_pic;
    }
    void ArmorDetector::showImage(cv::Mat &src)
    {
        if (frame_rate_flag_ == 4)
        {
            cv::namedWindow("armor_det", cv::WINDOW_NORMAL);
            // cv::resizeWindow("armor_det", 80, 60); // 指定窗口的宽度和高度
            cv::imshow("armor_det", src);
            cv::waitKey(1);
        }
    }
    void ArmorDetector::drawFrameRate(cv::Mat &src)
    {
        // 定义计时器
        now_time_ = std::chrono::steady_clock::now();

        // 计算帧率
        if (frame_rate_flag_ == 7)
        {
            frame_rate_flag_ = 0;

            elapsed_time_ = now_time_ - start_time_;
            double elapsed_seconds = std::chrono::duration_cast<std::chrono::duration<double>>(elapsed_time_).count();
            frame_rate_ = 1.0 / elapsed_seconds ;
        }

        char FPS[11];
        sprintf(FPS, "%.1f", frame_rate_);
        std::string fps = FPS;
        cv::putText(
            src, "fps:" + fps, cv::Point(20, 20), cv::FONT_HERSHEY_SIMPLEX, 0.7, {255, 255, 255}, 1);
        frame_rate_flag_++;
        std::cout << fps << std::endl;
        start_time_ = now_time_;

    }
}