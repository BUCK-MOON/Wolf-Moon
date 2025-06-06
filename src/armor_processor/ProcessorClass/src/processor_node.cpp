#include "../include/processor_node.hpp"
namespace rm_auto_aim
{
    /**
     * @brief
     */
    ProcessorNode::ProcessorNode(const rclcpp::NodeOptions &options) : Node("armor_processor_node", options)
    {
        RCLCPP_INFO(this->get_logger(), "\033[1m\033[46mStarting processor node...\033[0m");
        armor_processor_ = std::make_unique<ArmorProcessor>();

        // rclcpp::QoS qos(0);
        // qos.keep_last(1);
        // qos.durability();
        // qos.reliable();
        serial_msg_sub_ = this->create_subscription<auto_aim_interfaces::msg::Serial>(
            "/serial_msg",
            rclcpp::SensorDataQoS(),
            std::bind(&ProcessorNode::sensorMsgCallback,
                      this, std::placeholders::_1));
        armor_msg_sub_ = this->create_subscription<auto_aim_interfaces::msg::Armors>(
            "/armor_detector/armors_msg",
            rclcpp::SensorDataQoS(),
            std::bind(&ProcessorNode::targetMsgCallback, this, std::placeholders::_1));
        // std::cout<<"1"<<std::endl;

        gimbal_msg_pub_ = this->create_publisher<auto_aim_interfaces::msg::Gimbal>("/gimbal_msg", rclcpp::SensorDataQoS());
        state_msg_pub_ = this->create_publisher<auto_aim_interfaces::msg::State>("/armor_processor/state_msg", rclcpp::SensorDataQoS());
        marker_array_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("armor_processor/marker_msg", 10);
        // state_msg_.filler = 0;
        // std::cout<<"1"<<std::endl;
    }

    /**
     * @brief
     */
    void ProcessorNode::sensorMsgCallback(const auto_aim_interfaces::msg::Serial &serial_msg)
    {
        // 串口补偿逻辑---前
        // std::cout<<1<<std::endl;
        state_msg_mutex_.lock();
        // state_msg_.mode = serial_msg.mode;
        // state_msg_.mode = serial_msg.mode;
        state_msg_pub_->publish(state_msg_);
        state_msg_mutex_.unlock();
        serial_msg_mutex_.lock();
        // if (mission_.change == 0 && serial_msg.change == 1)
        // {
        //     mission_.change = 2;
        // }
        // else if (mission_.change == 2)
        // {
        // }
        // else
        // {
        //     mission_.change = serial_msg.change;
        // }
        serial_msg_deque_.push_back(serial_msg);
        while (rclcpp::ok())
        {
            rclcpp::Time time1 = serial_msg_deque_[0].header.stamp;
            rclcpp::Time time2 = serial_msg.header.stamp;
            double dif = (time2 - time1).seconds();
            // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Time1: %f seconds, %d nanoseconds", time1.seconds(), time1.nanoseconds());
            // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Time2: %f seconds, %d nanoseconds", time2.seconds(), time2.nanoseconds());
            // std::cout << dif << std::endl;
            if (dif < armor_processor_->dictionary["serial_save"])
            {
                break;
            }
            serial_msg_deque_.pop_front();
            RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 500, "serial delet:%zu time %f", serial_msg_deque_.size(), dif);
            // RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 50, "serial delet:%f", dif);
        }
        serial_msg_mutex_.unlock();
    }

    /**
     * @brief
     */
    void ProcessorNode::targetMsgCallback(const auto_aim_interfaces::msg::Armors::ConstSharedPtr armors_msg)
    {
        // std::cout << "1" << std::endl;
        // 串口补偿逻辑---后
        auto_aim_interfaces::msg::Serial serial_msg;
        double differ = MAX_CANON;
        int select = 0;
        serial_msg_mutex_.lock(); // 上锁
        if (serial_msg_deque_.size() != 0)
        {
            for (unsigned int i = 0; i < serial_msg_deque_.size(); i++)
            {
                rclcpp::Time time_serial = serial_msg_deque_[i].header.stamp;
                // RCLCPP_INFO(get_logger(), "Serial Time: %f", time_serial.seconds());
                rclcpp::Time time_image = armors_msg_.header.stamp;
                // RCLCPP_INFO(get_logger(), "image Time: %f", time_image.seconds());
                double dif = abs((time_serial - time_image).seconds());
                // std::cout << dif << std::endl;

                if (dif < differ)
                {
                    differ = dif;
                    select = i;
                }
            }
            RCLCPP_WARN(this->get_logger(), "serial select:%d", select);
            serial_msg = serial_msg_deque_[select];
            std::cout << differ << std::endl;
        }
        serial_msg_mutex_.unlock(); // 开锁
        //
        // std::cout << "11" << std::endl;

        rclcpp::Time serial_stamp = serial_msg.header.stamp;
        mission_.timestamp = serial_stamp.nanoseconds();
        mission_.mode = serial_msg.mode;
        mission_.quat.w() = serial_msg.imu.orientation.w;
        mission_.quat.x() = serial_msg.imu.orientation.x;
        mission_.quat.y() = serial_msg.imu.orientation.y;
        mission_.quat.z() = serial_msg.imu.orientation.z; // 四元数
        mission_.bullet_speed = serial_msg.bullet_speed;  // 弹速
        if (serial_msg.shoot_delay >= 50 && serial_msg.shoot_delay <= 300)
        {
            mission_.shoot_delay = (serial_msg.shoot_delay + mission_.shoot_delay) / 2.0; // 射击延迟
        }
        mission_.mode = 0;
        armors_msg_ = std::move(*armors_msg);
        // 清空消息
        markers_msg_.markers.clear();

        gimbal_msg_ = auto_aim_interfaces::msg::Gimbal{};
        state_msg_ = auto_aim_interfaces::msg::State{};
        state_msg_.mode = mission_.mode;
        gimbal_msg_.header = state_msg_.header = armors_msg->header;
        gimbal_msg_.is_target = 0;
        gimbal_msg_.pitch = 0;
        gimbal_msg_.yaw = 0.0;
        state_msg_.angle.x = 0;
        state_msg_.angle.y = 0;
        state_msg_.predict.x = 0;
        state_msg_.predict.y = 0;
        state_msg_.calculate.x = 0;
        state_msg_.calculate.y = 0;
        if (armors_msg_.get_armor)
        {
            gimbal_msg_.is_shooting = true;

            state_msg_mutex_.lock();
            if (armor_processor_->processArmors(gimbal_msg_, mission_, armors_msg_, state_msg_))
            {
                gimbal_msg_.is_target = 1;
                armor_processor_->processMarkers(markers_msg_);
            }
            state_msg_mutex_.unlock();
        }
        // gimbal_msg_.pitch = -gimbal_msg_.pitch;
        // gimbal_msg_.yaw = 0.1;
        // std::cout << state_msg_.mode << std::endl;
        state_msg_pub_->publish(state_msg_);
        gimbal_msg_pub_->publish(gimbal_msg_);
        marker_array_pub_->publish(markers_msg_);
    }

    /**
     * @brief
     */
    ProcessorNode::~ProcessorNode()
    {
    }
}
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<rm_auto_aim::ProcessorNode>());
    rclcpp::shutdown();
    return 0;
}
#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rm_auto_aim::ProcessorNode)