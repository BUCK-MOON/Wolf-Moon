
#include "../include/detector_node.hpp"
namespace rm_auto_aim
{
    /**
     * init node
     */
    DetectorNode::DetectorNode(const rclcpp::NodeOptions &options) : Node("armor_detector_node", options)
    {
        RCLCPP_INFO(this->get_logger(), "\033[47m\033[1mStarting DetectorNode!\033[0m");
        // std::cout<<"1"<<std::endl;

        armor_detector_ = std::make_unique<ArmorDetector>();
        // std::cout<<"1"<<std::endl;

#ifdef SHM

        receiver_ = std::make_shared<shm_video_trans::VideoReceiver>("image_raw");
        while (!receiver_->init())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        imageloop_ = std::make_shared<std::thread>(std::bind(&DetectorNode::imageLoop, this));
#endif
#ifndef SHM
        img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/image_raw",
            rclcpp::SensorDataQoS(),
            std::bind(&DetectorNode::imageCallback,
                      this, std::placeholders::_1));
#endif
        state_sub_ = this->create_subscription<auto_aim_interfaces::msg::State>(
            "/armor_processor/state_msg",
            rclcpp::SensorDataQoS(),
            std::bind(&DetectorNode::stateCallback,
                      this, std::placeholders::_1));
        armors_pub_ = this->create_publisher<auto_aim_interfaces::msg::Armors>("/armor_detector/armors_msg", rclcpp::SensorDataQoS());
        // std::cout << "1" << std::endl;
    }

    DetectorNode::~DetectorNode()
    {
    }

    void DetectorNode::stateCallback(const auto_aim_interfaces::msg::State &state_msg)
    {
        state_msg_mutex_.lock();
        state_msg_ = state_msg;
        state_msg_mutex_.unlock();
    }
#ifdef SHM
    void DetectorNode::imageLoop()
    {
        while (rclcpp::ok())
        {
#ifdef MATCH
            if (state_msg_.mode == 0 || state_msg_.mode == 1 || state_msg_.mode == 2)
            {
#endif
                if (receiver_->receive())
                {
                    RCLCPP_INFO(this->get_logger(), "Received...");
                    receiver_->lock();
                    receivedFrame_ = receiver_->toCvShare();
                    armors_msg_.armors.clear();
                    armors_msg_.header.frame_id = "left";
                    armors_msg_.header.stamp = rclcpp::Time(receivedFrame_.write_time.time_since_epoch().count());
                    // src_ = receivedFrame_.frame;
                    armors_msg_.get_armor = armor_detector_->detectArmors(receivedFrame_.frame, armors_msg_);
                    armors_pub_->publish(std::move(armors_msg_)); // Publishing detected armors

                    state_msg_mutex_.lock();
                    armor_detector_->drawState(receivedFrame_.frame, state_msg_);
                    state_msg_mutex_.unlock();
                    armor_detector_->showImage(receivedFrame_.frame);
                    receiver_->unlock();
                }
#ifdef MATCH
            }
            else
            {
                cv::destroyAllWindows();
            }
#endif
        }
    }

#endif

#ifndef SHM
    /**
     * image callback
     */
    void DetectorNode::imageCallback(const sensor_msgs::msg::Image::ConstSharedPtr img_msg)
    {
#ifdef MATCH
        if (state_msg_.mode == 0 || state_msg_.mode == 1 || state_msg_.mode == 2)
        {
#endif
            if (!img_msg)
            {
                RCLCPP_ERROR_THROTTLE(this->get_logger(), *this->get_clock(), 500, "\033[1m\033[41m[msg error\033[0m");
                return;
            }
            armors_msg_.header = img_msg->header;
            armors_msg_.armors.clear();
            src_ = cv_bridge::toCvShare(img_msg, "rgb8")->image; // 图像消息转为Mat矩阵
            armors_msg_.get_armor = armor_detector_->detectArmors(src_, armors_msg_);
            armors_pub_->publish(std::move(armors_msg_)); // Publishing detected armors

            state_msg_mutex_.lock();

            armor_detector_->drawState(src_, state_msg_);

            state_msg_mutex_.unlock();

            armor_detector_->showImage(src_);
#ifdef MATCH
        }
        else
        {
            cv::destroyAllWindows();
        }
#endif
    }
#endif
} // namespace rm_auto_aim
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    rclcpp::spin(std::make_shared<rm_auto_aim::DetectorNode>(options));
    rclcpp::shutdown();
    return 0;
}
#include "rclcpp_components/register_node_macro.hpp"

// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(rm_auto_aim::DetectorNode)