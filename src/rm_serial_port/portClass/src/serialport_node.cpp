#include "../include/serialport_node.hpp"
namespace rm_auto_aim
{
    SerialPortNode::SerialPortNode(const rclcpp::NodeOptions &options) : Node("serial_port", options)
    {

        RCLCPP_WARN(this->get_logger(), "Serialport node...");
        serial_port_ = std::make_unique<Serialport>();
        // rclcpp::QoS qos(0);
        // qos.keep_last(5);
        // qos.reliable();
        // qos.durability();
        // qos.deadline();
        twist_msg_ = geometry_msgs::msg::Twist::SharedPtr{};

        tf_buffer_ = std::make_unique<tf2_ros::Buffer>(this->get_clock());
        tf_ = std::make_shared<tf2_ros::TransformListener>(*tf_buffer_);
        read_rate_ = std::make_shared<rclcpp::Rate>(200);
        write_rate_ = std::make_shared<rclcpp::Rate>(200);
        auto_aim_sub_ = this->create_subscription<auto_aim_interfaces::msg::Gimbal>(
            "/gimbal_msg",
            rclcpp::SensorDataQoS(),
            std::bind(&SerialPortNode::gimbalMsgCallback, this, _1));
        sentry_twist_sub_ = this->create_subscription<geometry_msgs::msg::Twist>(
            "/cmd_vel",
            rclcpp::SensorDataQoS(),
            std::bind(&SerialPortNode::sentryNavCallback, this, _1));

        serial_msg_pub_ = this->create_publisher<auto_aim_interfaces::msg::Serial>("/serial_port/serial_msg", rclcpp::SensorDataQoS());
        uart_msg_pub_ = this->create_publisher<auto_aim_interfaces::msg::Uart>("/uart", rclcpp::SystemDefaultsQoS());
        loop_read_thread_ = std::make_unique<std::thread>(&SerialPortNode::readLoopSend, this);
        loop_write_thread_ = std::make_unique<std::thread>(&SerialPortNode::writeLoopAccept, this);
    }

    SerialPortNode::~SerialPortNode()
    {
    }

    void SerialPortNode::gimbalMsgCallback(auto_aim_interfaces::msg::Gimbal::SharedPtr gimbal_msg)
    {
        std::lock_guard<mutex> lck(serial_mutex_);
        serial_port_->sendDataA(gimbal_msg);
    }
    void SerialPortNode::readLoopSend()
    {
        while (rclcpp::ok())
        {
            read_rate_->sleep();

            serial_port_->receiveData(serial_msg_, uart_msg_);
            // rclcpp::Time now = this->get_clock()->now();
            // serial_msg.header.frame_id = "serial";
            serial_msg_.header.stamp = this->get_clock()->now();
            // serial_msg.imu.header.stamp = now;
            serial_msg_pub_->publish(std::move(serial_msg_));
            uart_msg_pub_->publish(std::move(uart_msg_));
        }
    }
    void SerialPortNode::writeLoopAccept()
    {
        while (rclcpp::ok())
        {
            write_rate_->sleep();
            geometry_msgs::msg::TransformStamped::SharedPtr transformStamped = nullptr;
            // 尝试获取base_link到map坐标系的变换
            try
            {
                transformStamped = std::make_shared<geometry_msgs::msg::TransformStamped>(this->tf_buffer_->lookupTransform("map", "base_link", tf2::TimePointZero));
            }
            catch (tf2::TransformException &ex)
            {
                // 记录变换获取失败的错误
                RCLCPP_ERROR(
                    this->get_logger(),
                    "Cannot get transform ! TransformException: %s",
                    ex.what());
                continue;
            }
            if (twist_msg_->linear.z == 1.0)
            {
                twist_msg_->linear.x = transformStamped->transform.translation.x;
                twist_msg_->linear.y = transformStamped->transform.translation.y;
            }
            twist_msg_->angular.x = transformStamped->transform.translation.x;
            twist_msg_->angular.y = transformStamped->transform.translation.y;
            std::cout << twist_msg_->angular.x << twist_msg_->angular.y << std::endl;
            tf2::Quaternion quat(

                transformStamped->transform.rotation.x,

                transformStamped->transform.rotation.y,

                transformStamped->transform.rotation.z,

                transformStamped->transform.rotation.w);

            double yaw = tf2::getYaw(quat);
            // msg->angular.z;
            twist_msg_->angular.z = yaw;
            std::lock_guard<mutex> lck(serial_mutex_);
            serial_port_->sendDataB(twist_msg_);
        }
    }

    void SerialPortNode::sentryNavCallback(geometry_msgs::msg::Twist::SharedPtr msg)
    {
        std::lock_guard<mutex> lck(serial_mutex_);
        twist_msg_ = msg;
        // serial_port_->sendDataB(msg);
    }

} // namespace rm_auto_aim
int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 4, true);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<rm_auto_aim::SerialPortNode>(options);
    executor.add_node(node);
    executor.spin();
    rclcpp::shutdown();
    return 0;
}

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(rm_auto_aim::SerialPortNode)