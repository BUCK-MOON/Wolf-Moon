#include "../include/armor_processor.hpp"
namespace rm_auto_aim
{
    /**
     * @brief 主要功能类的初始化
     */
    ArmorProcessor::ArmorProcessor() : logger_(rclcpp::get_logger("armor_processor"))
    {
        ballistic_processor_ = std::make_unique<BallisticProcessor>(); // 创建弹道类指针
        skf_ = std::make_unique<SphericalKalmanFilter>();
        // std::cout << "1.." <<dictionary["max_match_yaw_diff"]<< std::endl;
        initConfig(); // 初始化参数
        tracker_ = std::make_unique<Tracker>(dictionary["max_match_distance"], dictionary["max_match_yaw_diff"]);
        // std::cout << "1" << std::endl;
        tracker_->tracking_thres = dictionary["tracking_thres"];
        lost_time_thres_ = dictionary["lost_time_thres"];
        // std::cout << lost_time_thres_ << std::endl;
        initTracker();
        initMarker();
        // src_ = cv::Mat(480, 640, CV_8UC3);
    }
    bool ArmorProcessor::initTracker()
    {
        // EKF
        // xa = x_armor, xc = x_robot_center
        // state: xc, v_xc, yc, v_yc, za, v_za, yaw, v_yaw, r
        // measurement: xa, ya, za, yaw
        // f - Process function
        auto f = [this](const Eigen::VectorXd &x)
        {
            Eigen::VectorXd x_new = x;
            x_new(0) += x(1) * dt_;
            x_new(2) += x(3) * dt_;
            x_new(4) += x(5) * dt_;
            x_new(6) += x(7) * dt_;
            return x_new;
        };
        // J_f - Jacobian of process function
        auto j_f = [this](const Eigen::VectorXd &)
        {
            Eigen::MatrixXd f(9, 9);
            // clang-format off
    f <<  1,   dt_, 0,   0,   0,   0,   0,   0,   0,
          0,   1,   0,   0,   0,   0,   0,   0,   0,
          0,   0,   1,   dt_, 0,   0,   0,   0,   0, 
          0,   0,   0,   1,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   1,   dt_, 0,   0,   0,
          0,   0,   0,   0,   0,   1,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   1,   dt_, 0,
          0,   0,   0,   0,   0,   0,   0,   1,   0,
          0,   0,   0,   0,   0,   0,   0,   0,   1;
            // clang-format on
            return f;
        };
        // h - Observation function
        auto h = [](const Eigen::VectorXd &x)
        {
            Eigen::VectorXd z(4);
            double xc = x(0), yc = x(2), yaw = x(6), r = x(8);
            z(0) = xc - r * cos(yaw); // xa
            z(1) = yc - r * sin(yaw); // ya
            z(2) = x(4);              // za
            z(3) = x(6);              // yaw
            return z;
        };
        // J_h - Jacobian of observation function
        auto j_h = [](const Eigen::VectorXd &x)
        {
            Eigen::MatrixXd h(4, 9);
            double yaw = x(6), r = x(8);
            // clang-format off
    //    xc   v_xc yc   v_yc za   v_za yaw         v_yaw r
    h <<  1,   0,   0,   0,   0,   0,   r*sin(yaw), 0,   -cos(yaw),
          0,   0,   1,   0,   0,   0,   -r*cos(yaw),0,   -sin(yaw),
          0,   0,   0,   0,   1,   0,   0,          0,   0,
          0,   0,   0,   0,   0,   0,   1,          0,   0;
            // clang-format on
            return h;
        };
        // update_Q - process noise covariance matrix
        s2qxyz_ = dictionary["sigma2_q_xyz"]; // declare_parameter("ekf.sigma2_q_xyz", 20.0);
        s2qyaw_ = dictionary["sigma2_q_yaw"]; // declare_parameter("ekf.sigma2_q_yaw", 100.0);
        s2qr_ = dictionary["sigma2_q_r"];     // declare_parameter("ekf.sigma2_q_r", 800.0);
        auto u_q = [this]()
        {
            Eigen::MatrixXd q(9, 9);
            double t = dt_, x = s2qxyz_, y = s2qyaw_, r = s2qr_;
            double q_x_x = pow(t, 4) / 4 * x, q_x_vx = pow(t, 3) / 2 * x, q_vx_vx = pow(t, 2) * x;
            double q_y_y = pow(t, 4) / 4 * y, q_y_vy = pow(t, 3) / 2 * x, q_vy_vy = pow(t, 2) * y;
            double q_r = pow(t, 4) / 4 * r;
            // clang-format off
    //    xc      v_xc    yc      v_yc    za      v_za    yaw     v_yaw   r
    q <<  q_x_x,  q_x_vx, 0,      0,      0,      0,      0,      0,      0,
          q_x_vx, q_vx_vx,0,      0,      0,      0,      0,      0,      0,
          0,      0,      q_x_x,  q_x_vx, 0,      0,      0,      0,      0,
          0,      0,      q_x_vx, q_vx_vx,0,      0,      0,      0,      0,
          0,      0,      0,      0,      q_x_x,  q_x_vx, 0,      0,      0,
          0,      0,      0,      0,      q_x_vx, q_vx_vx,0,      0,      0,
          0,      0,      0,      0,      0,      0,      q_y_y,  q_y_vy, 0,
          0,      0,      0,      0,      0,      0,      q_y_vy, q_vy_vy,0,
          0,      0,      0,      0,      0,      0,      0,      0,      q_r;
            // clang-format on
            return q;
        };
        // update_R - measurement noise covariance matrix
        r_xyz_factor = dictionary["r_xyz_factor"]; // declare_parameter("ekf.r_xyz_factor", 0.05);
        r_yaw = dictionary["r_yaw"];               // declare_parameter("ekf.r_yaw", 0.02);
        auto u_r = [this](const Eigen::VectorXd &z)
        {
            Eigen::DiagonalMatrix<double, 4> r;
            double x = r_xyz_factor;
            r.diagonal() << abs(x * z[0]), abs(x * z[1]), abs(x * z[2]), r_yaw;
            return r;
        };
        // P - error estimate covariance matrix
        Eigen::DiagonalMatrix<double, 9> p0;
        p0.setIdentity();
        tracker_->ekf = ExtendedKalmanFilter{f, h, j_f, j_h, u_q, u_r, p0};
        return true;
    }
    void ArmorProcessor::initMarker()
    {
        // TODO 更多的可视化信息
        armor_marker_.header.frame_id = "imu_link";                  // 设置坐标系
        armor_marker_.header.stamp = steady_clock_.now();            // 设置时间戳
        armor_marker_.ns = "markers";                                // 设置命名空间
        armor_marker_.id = 0;                                        // 设置唯一标识符
        armor_marker_.type = visualization_msgs::msg::Marker::CUBE;  // 设置类型为立方体
        armor_marker_.action = visualization_msgs::msg::Marker::ADD; // 添加新的立方体
        geometry_msgs::msg::Vector3 scale;
        scale.x = 0.175; // 设置立方体的大小
        scale.y = 0.125;
        scale.z = 0.02;
        armor_marker_.scale = scale;
        std_msgs::msg::ColorRGBA color;
        color.r = 0.12; // 设置立方体的颜色为红色
        color.g = 0.71;
        color.b = 0.12;
        color.a = 1.0;
        armor_marker_.color = color;
        // 另一坐标系下该装甲板
        warmor_marker_ = armor_marker_;
        warmor_marker_.header.frame_id = "bace_link";
        warmor_marker_.id = 3;

        // 箭头
        center_marker_.header.frame_id = "imu_link";                  // 设置坐标系
        center_marker_.header.stamp = steady_clock_.now();            // 设置时间戳
        center_marker_.ns = "markers";                                // 设置命名空间
        center_marker_.id = 1;                                        // 设置唯一标识符
        center_marker_.type = visualization_msgs::msg::Marker::CUBE;  // 设置类型为箭头
        center_marker_.action = visualization_msgs::msg::Marker::ADD; // 添加新的箭头
        // geometry_msgs::msg::Vector3 scale;
        scale.x = 0.02; // 设置箭头的大小
        scale.y = 0.02;
        scale.z = 0.5;
        center_marker_.scale = scale;
        center_marker_.pose.orientation.x = 0.0; // 设置箭头的方向
        center_marker_.pose.orientation.y = 0.0;
        center_marker_.pose.orientation.z = 0.0;
        center_marker_.pose.orientation.w = 1.0;
        // std_msgs::msg::ColorRGBA color;
        color.r = 1.0; // 设置箭头的颜色为红色
        color.g = 0.0;
        color.b = 0.0;
        color.a = 1.0;
        center_marker_.color = color;
        wcenter_marker_ = center_marker_;
        wcenter_marker_.header.frame_id = "bace_link";
        wcenter_marker_.id = 4;
    }
    void ArmorProcessor::processMarkers(visualization_msgs::msg::MarkerArray &markers_msg)
    {
        auto armor = tracker_->tracked_armor;
        auto &state = tracker_->target_state;

        // armor.pose.position.z = 0.0;
        warmor_marker_.pose = armor.pose;
        markers_msg.markers.emplace_back(warmor_marker_);
        wcenter_marker_.pose.position.x = state[0]; // 设置箭头的位置 x 坐标
        wcenter_marker_.pose.position.y = state[2]; // 设置箭头的位置 y 坐标
        wcenter_marker_.pose.position.z = 0.0;
        markers_msg.markers.emplace_back(wcenter_marker_);

        armor.pose.position.x = armor.pose.position.x - state[0];
        armor.pose.position.y = armor.pose.position.y - state[2];
        // armor.pose.position.z = 0.0;
        armor_marker_.pose = armor.pose;
        markers_msg.markers.emplace_back(armor_marker_);
        center_marker_.pose.position.x = 0; // state[0]; // 设置箭头的位置 x 坐标
        center_marker_.pose.position.y = 0; // state[2]; // 设置箭头的位置 y 坐标
        center_marker_.pose.position.z = 0.0;
        markers_msg.markers.emplace_back(center_marker_);
    }
    bool ArmorProcessor::processArmors(Gimbal &gimbal_msg, Mission &mission, Armors &armors_msg, State &state_msg)
    {
        // src_.setTo(27);
        if (dictionary["debug"])
        {
            initConfig();
        }
        if (mission.bullet_speed >= 20 && mission.bullet_speed <= 30)
        {
            ballistic_processor_->bullet_speed = (ballistic_processor_->bullet_speed + mission.bullet_speed) / 2.0; // 射击延迟
            // predictor_->bullet_speed_ = (predictor_->bullet_speed_ + mission.bullet_speed) / 2.0;
            // std::cout << mission.bullet_speed << std::endl;
            // std::cout << mission.shoot_delay << std::endl;
        }
        mission.rmat = mission.quat.toRotationMatrix();
        // mission.mode = 0;
        std::cout << mission.mode << std::endl;
        for (auto &armor : armors_msg.armors)
        {
            transformArmor(armor, mission);
        }
        // Filter abnormal armors
        armors_msg.armors.erase(
            std::remove_if(
                armors_msg.armors.begin(), armors_msg.armors.end(),
                [this](const auto_aim_interfaces::msg::Armor &armor)
                {
                    return Eigen::Vector2d(armor.pose.position.x, armor.pose.position.y).norm() >
                           dictionary["max_armor_distance"];
                }),
            armors_msg.armors.end());
        // 筛选和过远装甲板
        // if (armors_msg.armors.size() == 0)
        // {
        //     RCLCPP_WARN_THROTTLE(logger_, steady_clock_, 647, "\033[1m\033[31m empty armors \033[0m");
        //     // Eigen::Vector2d vec(0, 0);
        //     // Eigen::Vector2d s_angle = skf_->updateSKF(vec);
        //     // gimbal_msg.pitch = s_angle(0);
        //     // gimbal_msg.yaw = s_angle(1);
        //     return false;
        // }
        // else
        // {
        rclcpp::Time time = armors_msg.header.stamp;

        gimbal_msg.header.stamp = time;
        gimbal_msg.header.frame_id = "tracker";
        // Update tracker
        if (tracker_->tracker_state == Tracker::LOST /*|| mission.change == 2*/)
        {
            // if (mission.change == 2)
            // {
            //     mission.change = 1;
            // }
            // std::cout << "init" << std::endl;
            tracker_->init(armors_msg);
            gimbal_msg.is_spinning = false;
            sloveMeasurement(gimbal_msg, mission);
        }
        else
        {
            dt_ = (time - last_time_).seconds();
            // std::cout << "aaa" << dt_ << std::endl;
            tracker_->lost_thres = static_cast<int>(lost_time_thres_ / dt_); // 0.3
            tracker_->update(armors_msg);                                    // 追踪器更新与重启
            sloveMeasurement(gimbal_msg, mission);

            if (tracker_->tracker_state == Tracker::DETECTING)
            {
                gimbal_msg.is_spinning = false;
            }
            else if (
                tracker_->tracker_state == Tracker::TRACKING ||
                tracker_->tracker_state == Tracker::TEMP_LOST)
            {
                // std::cout << tracker_->tracker_state << std::endl;
                gimbal_msg.is_spinning = true;

                sloveState(gimbal_msg, mission);
            }
        }
        getState(state_msg, mission);
        // TODO

        // if (!skf_->tracking_)
        // {
        //     Eigen::Vector2d vec(gimbal_msg.pitch, gimbal_msg.yaw);
        //     skf_->initSKF(vec);
        // }
        // else
        // {
        //     Eigen::Vector2d vec(gimbal_msg.pitch, gimbal_msg.yaw);

        //     Eigen::Vector2d s_angle = skf_->updateSKF(vec);
        //     gimbal_msg.pitch = s_angle(0);
        //     gimbal_msg.yaw = s_angle(1);
        // }
        last_time_ = time;
        return true;
    }
    // }mission
    void ArmorProcessor::getState(State &state_msg, Mission &mission)
    {
        const auto &state = tracker_->target_state;

        // Eigen::Vector3d center = Eigen::Vector3d{state(0), state(2), state(4)};
        // getXYZ(state_msg, center, mission.rmat);
        // state_msg.state.xc = state[0];  //
        // state_msg.state.xv = state[1];  //
        // state_msg.state.yc = state[2];  //
        // state_msg.state.yv = state[3];  //
        // state_msg.state.zc = state[4];  //
        // state_msg.state.zv = state[5];  //
        // state_msg.state.yaw = state[6]; //
        // state_msg.state.yav = state[7]; //
        // state_msg.state.r = state[8];   //
        state_msg.mode = mission.mode;  // 可视化消息赋值
        state_msg.angle.x = angle_(1);
        state_msg.angle.y = angle_(0);
        state_msg.predict.x = predict_(1);
        state_msg.predict.y = predict_(0);
        state_msg.calculate.x = calculate_.x; // 圈
        state_msg.calculate.y = calculate_.y;
        // src.filler = 2;
    }
    /**
     * @brief 获得车辆中心坐标系，TODO用于ROI
     */
    // void ArmorProcessor::getXYZ(State &state_msg, Eigen::Vector3d &xyz, Eigen::Matrix3d &rmat_imu)
    // {
    //     cv::Point2f center[4];
    //     Eigen::Vector3d xyz_cam = ballistic_processor_->worldToCam(xyz, rmat_imu);
    //     // std::cout<<xyz_cam<<std::endl;
    //     // ROI
    //     xyz_cam = xyz_cam + Eigen::Vector3d{0.42, 0, 0};
    //     center[1] = ballistic_processor_->reproject(xyz_cam);
    //     xyz_cam = xyz_cam - Eigen::Vector3d{0.84, 0, 0};
    //     center[0] = ballistic_processor_->reproject(xyz_cam);

    //     Eigen::Vector3d z = xyz + Eigen::Vector3d{0, 0, 0.3}; // 中心柱
    //     z = ballistic_processor_->worldToCam(z, rmat_imu);
    //     center[2] = ballistic_processor_->reproject(z);
    //     Eigen::Vector3d o = xyz;
    //     o = ballistic_processor_->worldToCam(o, rmat_imu);
    //     center[3] = ballistic_processor_->reproject(o);
    //     for (int i = 0; i < 4; i++)
    //     {
    //         state_msg.center[i].x = static_cast<float>(center[i].x);
    //         state_msg.center[i].y = static_cast<float>(center[i].y); // 給可视化消息赋值
    //     }
    //     // src.filler = 1;
    // }
    /**
     * @brief 获得预测消息
     */
    void ArmorProcessor::sloveState(Gimbal &gimbal_msg, Mission &mission)
    {

        // 基础预测
        auto state = tracker_->target_state;
        const auto armor = tracker_->tracked_armor;
        double xyz_delay = 0;//((armor.distance / 30) + /*(mission.shoot_delay / 1e3)*/ +dictionary["xyz_time_offset"]); // 飞行时间+射击延迟+时间补常;armor.distance / 30 +armor.distance / 37 +
        double yaw_delay = ((armor.distance / 30) + /*(mission.shoot_delay / 1e3)*/ +dictionary["yaw_time_offset"]); // 飞行时间+射击延迟+时间补常;armor.distance / 30 +armor.distance / 37 +

        for (int i = 0; i < 4; i++)
        {
            if (i != 3 || i != 2)
            {
                state[2 * i] += state[(2 * i) + 1] * xyz_delay;
            }
            else if (i == 3)
            {
                state[2 * i] += state[(2 * i) + 1] * yaw_delay;
            }
        }
        RCLCPP_INFO_THROTTLE(logger_, steady_clock_, 50, "delay:%f,%f,%f", armor.distance / 30, xyz_delay, yaw_delay); // mission.shoot_delay / 1e3 +
        Eigen::Vector3d xyz = tracker_->getArmorPositionFromState(state);
        xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
        std::cout<<"speed"<<tracker_->target_state[7]<<std::endl;
        predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
        gimbal_msg.is_target = 1;
        calculate_ = ballistic_processor_->reproject(xyz); // 重投 // 预测点坐标，可识化消息
        // std::cout << "yaw"
        //           << "," << state[7] << std::endl;
        if (mission.mode == 1)
        {
            if (abs(predict_(0)) < dictionary["shoot_thres"] && abs(predict_(1)) < dictionary["shoot_thres"])
                gimbal_msg.is_shooting = true;
            RCLCPP_ERROR(logger_, "shoot");

            // gimbal_msg.pitch = predict_(1);

            gimbal_msg.pitch = angle_(1);
            gimbal_msg.yaw = predict_(0);
            // if (abs(state[7]) > 0.3)
            // {
            //     RCLCPP_INFO(logger_, "shoot type 2");

            //     // // 小陀螺状态
            //     gimbal_msg.is_spinning = true;
            //     RCLCPP_INFO(logger_, "crack spin");
            //     gimbal_msg.is_shooting = true;
            //     // state = tracker_->target_state;
            //     double yaw = atan2(state[2], state[0]);
            //     double left_yaw = yaw + dictionary["shoot_thres"];
            //     double right_yaw = yaw - dictionary["shoot_thres"];
            //     // if(state[6]<left_yaw&&state[6]>left_yaw)
            //     // {
            //     //     // }
            //     if (state[6] > left_yaw && state[7] > 0)
            //     { // 如果目标超出良好打击范围，则转到另一边，准备打击下一个
            //         auto state1 = state;
            //         state1[8] = tracker_->another_r;
            //         state1[6] = right_yaw;
            //         state1[4] += tracker_->dz;
            //         xyz = tracker_->getArmorPositionFromState(state1);
            //         xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);

            //         predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
            //         gimbal_msg.pitch = predict_(1);
            //         gimbal_msg.yaw = predict_(0);
            //         gimbal_msg.is_shooting = false;
            //         RCLCPP_INFO(logger_, "crack turn");
            //         //
            //         // auto state2 = state;
            //         // if (state2[6] - 1.5 > right_yaw)
            //         // {
            //         //     state2[8] = tracker_->another_r;
            //         //     state2[6] = state[6] - 1.57;
            //         //     state2[4] += tracker_->dz;
            //         //     xyz = tracker_->getArmorPositionFromState(state2);
            //         //     xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
            //         //     predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
            //         //     gimbal_msg.pitch = predict_(1);
            //         //     gimbal_msg.yaw = predict_(0);
            //         //     gimbal_msg.is_shooting = true;
            //         // }
            //     }
            //     if (state[6] < right_yaw && state[7] < 0)
            //     {
            //         auto state1 = state;
            //         state1[8] = tracker_->another_r;
            //         state1[6] = left_yaw;
            //         state1[4] += tracker_->dz;
            //         xyz = tracker_->getArmorPositionFromState(state1);
            //         xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);

            //         predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
            //         gimbal_msg.pitch = predict_(1);
            //         gimbal_msg.yaw = predict_(0);
            //         gimbal_msg.is_shooting = false;
            //         //
            //         RCLCPP_INFO(logger_, "crack turn");

            //         // auto state2 = state;
            //         // if (state2[6] + 1.5 < left_yaw)
            //         // {
            //         //     state2[8] = tracker_->another_r;
            //         //     state2[6] = state[6] + 1.57;
            //         //     state2[4] += tracker_->dz;
            //         //     xyz = tracker_->getArmorPositionFromState(state2);
            //         //     xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
            //         //     predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
            //         //     gimbal_msg.pitch = predict_(1);
            //         //     gimbal_msg.yaw = predict_(0);
            //         //     gimbal_msg.is_shooting = true;
            //         // }
            //     }
            // }
        }
        if (mission.mode == 2)
        {
            // RCLCPP_ERROR(logger_, "shoot type 3");
            // state = tracker_->target_state;
            gimbal_msg.is_shooting = false;
            double yaw = atan2(tracker_->target_state[2], tracker_->target_state[0]);
            double dev = abs(yaw - state[6]);

            RCLCPP_WARN(logger_, "no_shoot:%f", dev);
            int z_f = (dev / CV_PI / 2);
            if (z_f % 2 == 0)
            {
                state[6] = yaw;
                xyz = tracker_->getArmorPositionFromState(state);
                // xyz = Eigen::Vector3d{state[0], state[2], state[4]};
                xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
                predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
                calculate_ = ballistic_processor_->reproject(xyz); // 重投影
                gimbal_msg.pitch =  angle_(1);
                gimbal_msg.yaw = predict_(0);
            }
            else
            {
                state[6] = yaw;
                state[4] = state[4] + tracker_->dz;
                state[8] = tracker_->another_r;
                xyz = tracker_->getArmorPositionFromState(state);
                // xyz = Eigen::Vector3d{state[0], state[2], state[4]+ tracker_->dz};
                xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
                predict_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
                calculate_ = ballistic_processor_->reproject(xyz); // 重投影

                gimbal_msg.pitch =  angle_(1);
                gimbal_msg.yaw = predict_(0);
            }
            double crack;
            if (armor.type == "large")
            {
                crack = dictionary["crack_angle_big"];
            }
            else
            {
                crack = dictionary["crack_angle_small"];
            }
            if (tracker_->tracked_armors_num == ArmorsNum::NORMAL_4)
            {
                if (fmod(dev, CV_PI / 2) < crack)
                {
                    // if (abs(angle_(1) - predict_(1)) < dictionary["shoot_thres"])
                    gimbal_msg.is_shooting = true;
                    RCLCPP_ERROR(logger_, "shoot:%f", dev);
                }
            }
            else if (tracker_->tracked_armors_num == ArmorsNum::OUTPOST_3)
            {
                if (fmod(dev, 2 * CV_PI / 3) < crack)
                {
                    // if (abs(angle_(1) - predict_(1)) < dictionary["shoot_thres"])
                    gimbal_msg.is_shooting = true;
                    RCLCPP_ERROR(logger_, "shoot:%f", dev);
                }
            }
            else if (tracker_->tracked_armors_num == ArmorsNum::BALANCE_2)
            {
                if (fmod(dev, CV_PI) < crack)
                {
                    // if (abs(angle_(1) - predict_(1)) < dictionary["shoot_thres"])
                    gimbal_msg.is_shooting = true;
                    RCLCPP_ERROR(logger_, "shoot:%f", dev);
                }
            }
        }
    }
    /**
     * @brief 获得跟踪消息
     */
    void ArmorProcessor::sloveMeasurement(Gimbal &gimbal_msg, Mission &mission)
    {
        const auto armor = tracker_->tracked_armor;
        // auto state = tracker_->target_state;

        Eigen::Vector3d xyz = Eigen::Vector3d{armor.pose.position.x, armor.pose.position.y, armor.pose.position.z};
        // std::cout << xyz << std::endl;
        xyz = ballistic_processor_->worldToCam(xyz, mission.rmat);
        angle_ = ballistic_processor_->getAttitude(xyz, mission.rmat);
        calculate_ = ballistic_processor_->reproject(xyz); // 重投影

        // std::cout << "cout"<< std::endl;
        gimbal_msg.is_target = 2;
        gimbal_msg.pitch = angle_(1);
        gimbal_msg.yaw = angle_(0);
        // gimbal_msg.pitch = predict_(1);
        // // gimbal_msg.pitch = angle_(1);
        // gimbal_msg.yaw = predict_(0);
    }

    /**
     * @brief 转化装甲板到世界坐标系
     */
    bool ArmorProcessor::transformArmor(Armor &armor, Mission &mission)
    {
        Eigen::Vector3d xyz = {armor.pose.position.x, armor.pose.position.y, armor.pose.position.z};
        // cv::Point2f target = ballistic_processor_->reproject(xyz);
        // cv::circle(src_, target, 5, cv::Scalar{255, 255, 255}, 2, cv::LINE_AA);
        armor.distance = xyz.norm(); // 因为方便和减少detector复杂度所以在这赋值
        // std::cout << xyz.norm() << std::endl;

        xyz = ballistic_processor_->camToWorld(xyz, mission.rmat);
        Eigen::Quaterniond quat(armor.pose.orientation.w,
                                armor.pose.orientation.x,
                                armor.pose.orientation.y,
                                armor.pose.orientation.z);
        Eigen::Matrix3d rmat = quat.toRotationMatrix();
        rmat = ballistic_processor_->camToWorld(rmat, mission.rmat);
        quat = Eigen::Quaterniond(rmat);
        armor.pose.position.x = xyz.x();
        armor.pose.position.y = xyz.y();
        armor.pose.position.z = xyz.z(); // 平移向量存入
        armor.pose.orientation.w = quat.w();
        armor.pose.orientation.x = quat.x();
        armor.pose.orientation.y = quat.y();
        armor.pose.orientation.z = quat.z(); // 四元数存入
        return true;
    }

    void ArmorProcessor::initConfig()
    {
        auto pkg_path = ament_index_cpp::get_package_share_directory("armor_processor");
        std::string init_config_path = pkg_path + "/config/init_config.yaml";
        cv::FileStorage init_config(init_config_path, cv::FileStorage::READ);
        init_config["debug"] >> dictionary["debug"];
        // init_config["useImu"] >> dictionary["useImu"];
        // 甲类
        init_config["serial_save"] >> dictionary["serial_save"];
        init_config["xyz_time_offset"] >> dictionary["xyz_time_offset"];
        init_config["yaw_time_offset"] >> dictionary["yaw_time_offset"];
        init_config["shoot_thres"] >> dictionary["shoot_thres"];
        init_config["crack_angle_small"] >> dictionary["crack_angle_small"];
        init_config["crack_angle_big"] >> dictionary["crack_angle_big"];
        // 乙类
        init_config["max_armor_distance"] >> dictionary["max_armor_distance"];

        cv::FileNode xyz_offset_node = init_config["xyz_offset"]; // 获取xyz_offset节点的子节点x、y、z的值
        ballistic_processor_->xyz_offset = Eigen::Vector3d{(double)xyz_offset_node["x"], (double)xyz_offset_node["y"], (double)xyz_offset_node["z"]};
        cv::FileNode angle_offset_node = init_config["angle_offset"]; // 获取angle_offset节点的子节点pitch、yaw的值
        ballistic_processor_->angle_offset = Eigen::Vector2d{(double)angle_offset_node["yaw"], (double)angle_offset_node["pitch"]};
        // 滤波条件类
        cv::FileNode tracker = init_config["tracker"];
        dictionary["max_match_distance"] = (double)tracker["max_match_distance"];
        dictionary["max_match_yaw_diff"] = (double)tracker["max_match_yaw_diff"];
        dictionary["tracking_thres"] = (double)tracker["tracking_thres"];
        dictionary["lost_time_thres"] = (double)tracker["lost_time_thres"];
        // 滤波参数类
        cv::FileNode ekf = init_config["ekf"];
        dictionary["sigma2_q_xyz"] = (double)ekf["sigma2_q_xyz"];
        // std::cout << dictionary["sigma2_q_xyz"] << std::endl;

        dictionary["sigma2_q_yaw"] = (double)ekf["sigma2_q_yaw"];
        // std::cout << dictionary["sigma2_q_yaw"] << std::endl;

        dictionary["sigma2_q_r"] = (double)ekf["sigma2_q_r"];
        // std::cout << dictionary["sigma2_q_r"] << std::endl;

        dictionary["r_xyz_factor"] = (double)ekf["r_xyz_factor"];
        // std::cout << dictionary["r_xyz_factor"] << std::endl;

        dictionary["r_yaw"] = (double)ekf["r_yaw"];
        // std::cout << dictionary["r_yaw"] << std::endl;
        init_config.release();
        // std::cout << dictionary["xyz_time_offset"] << std::endl;
        // std::cout << dictionary["yaw_time_offset"] << std::endl;
        // std::cout << dictionary["shoot_thres"] << std::endl;
    }
}