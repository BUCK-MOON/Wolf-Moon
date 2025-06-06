#include <DxImageProc.h>
#include <GxIAPI.h>

// ROS
// #include <camera_info_manager/camera_info_manager.hpp>
#include <image_transport/image_transport.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>

// OpenCV
#include <opencv2/opencv.hpp>

// C++ system
#include <memory>
#include <string>
#include <thread>
#include <vector>
// #include <filesystem>
// namespace fs = std::filesystem;
namespace daheng_camera
{
    class DaHengCameraNode : public rclcpp::Node
    {
    private:
        GX_STATUS status;      // 用以存储错误模式
        GX_DEV_HANDLE hDevice; // 相机句柄
        PGX_FRAME_BUFFER pFrameBuffer;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;
        sensor_msgs::msg::Image image_msg_;
        std::map<std::string, double> dictionary;

    public:
        bool initConfig()
        {
            std::string pkg_path = ament_index_cpp::get_package_share_directory("daheng_camera");
            std::string init_config_path = pkg_path + "/config/init_config.yaml";
            cv::FileStorage init_config;
            init_config = cv::FileStorage(init_config_path, cv::FileStorage::READ);
            init_config["cache"] >> dictionary["cache"];
            // std::cout << dictionary["cache"] << std::endl;
            init_config["exposure"] >> dictionary["exposure"];
            // std::cout << dictionary["exposure"] << std::endl;
            init_config["gain"] >> dictionary["gain"];
            // std::cout << dictionary["gain"] << std::endl;
            cv::FileNode balance = init_config["balance"];
            // std::cout << dictionary["balance"] << std::endl;
            dictionary["blue"] = (double)balance["blue"];
            // std::cout << dictionary["blue"] << std::endl;
            dictionary["green"] = (double)balance["green"];
            // std::cout << dictionary["green"] << std::endl;
            dictionary["red"] = (double)balance["red"];
            // std::cout << dictionary["red"] << std::endl;
            init_config.release();

            return true;
        }
        ~DaHengCameraNode() override
        {
            GXCloseDevice(hDevice);
            RCLCPP_INFO(this->get_logger(), "Camera node destroyed!");
        }
        bool setParam()
        {
            status = GXSetAcqusitionBufferNumber(hDevice, dictionary["cache"]);                      // 设置缓存空间大小
            status = GXSetBool(hDevice, GX_BOOL_CHUNKMODE_ACTIVE, true);                             // 设置帧信息
            status = GXSetEnum(hDevice, GX_ENUM_CHUNK_SELECTOR, GX_CHUNK_SELECTOR_CHUNK_TIME_STAMP); // 启用时间戳
            GXStreamOn(hDevice);                                                                     // 开始读取视频流
            status = GXSetFloat(hDevice, GX_FLOAT_EXPOSURE_TIME, dictionary["exposure"]);            // 设置曝光时间
            status = GXSetEnum(hDevice, GX_ENUM_GAIN_SELECTOR, GX_GAIN_SELECTOR_ALL);                // 选择全通道增益
            status = GXSetFloat(hDevice, GX_FLOAT_GAIN, dictionary["gain"]);                         // 设置增益值为16
            status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_BLUE);
            status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, dictionary["blue"]);
            status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_GREEN);
            status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, dictionary["green"]);
            status = GXSetEnum(hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_RED);
            status = GXSetFloat(hDevice, GX_FLOAT_BALANCE_RATIO, dictionary["red"]);
            if (status == 0)
            {
                // RCLCPP_WARN(this->get_logger(), "Connected camera");
                RCLCPP_INFO(this->get_logger(), "config success");

                return true;
            }
            else
            {
                RCLCPP_INFO(this->get_logger(), "config fail");

                return false;
            }
        }
        bool initCamera()
        {

            uint32_t nDeviceNum = 0;
            GX_OPEN_PARAM stOpenParam;
            hDevice = NULL;
            status = GXInitLib();                              // 若返回0值则代表成功
            status = GXUpdateAllDeviceList(&nDeviceNum, 1000); // 枚举设备,设备数，等待时间
            stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;      // 独占模式打开相机
            stOpenParam.openMode = GX_OPEN_INDEX;              // 索引号打开模式
            stOpenParam.pszContent = "1";                      // 索引号1
            status = GXOpenDevice(&stOpenParam, &hDevice);     // 打开相机
            status = GXSetEnum(hDevice, GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_OFF);
            if (setParam())
            {
                RCLCPP_WARN(this->get_logger(), "Connected camera");

                return true;
            }
            else
            {
                return false;
            }
        }
        explicit DaHengCameraNode(const rclcpp::NodeOptions &options) : Node("daheng_camera", options) // 程序入口
        {
            RCLCPP_INFO(this->get_logger(), "Starting DaHengCameraNode!");
            img_pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_raw", rclcpp::SensorDataQoS());
            initConfig();
            initCamera();

                // initCamera();
                RCLCPP_INFO(this->get_logger(), "camera publish");
            image_msg_.header.frame_id = "left";
            image_msg_.encoding = "rgb8";

            while (rclcpp::ok())
            {
                status = GXDQBuf(hDevice, &pFrameBuffer, 1000); // 调 用 GXDQBuf 取 一 帧 图 像

                while ((status != 0) && rclcpp::ok())
                {
                    GXCloseDevice(hDevice);
                    if (initCamera())
                    {
                        RCLCPP_INFO(this->get_logger(), "camera publish");
                        status = GXDQBuf(hDevice, &pFrameBuffer, 1000); // 调 用 GXDQBuf 取 一 帧 图 像
                        break;
                    }
                    else
                    {
                        RCLCPP_ERROR(this->get_logger(), "Try reconnecting the camera");
                    }
                }
                // 开始准备
                DX_BAYER_CONVERT_TYPE cvtype = RAW2RGB_NEIGHBOUR3; // 选 择 插 值 算 法
                DX_PIXEL_COLOR_FILTER nBayerType = DX_PIXEL_COLOR_FILTER(BAYERBG);
                bool bFlip = false;
                char *pRGB24Buf = new char[pFrameBuffer->nWidth * pFrameBuffer->nHeight * 3]; // 输 出 图 像 RGB 数 据
                VxInt32 DxStatus = DxRaw8toRGB24(pFrameBuffer->pImgBuf, pRGB24Buf, pFrameBuffer->nWidth, pFrameBuffer->nHeight, cvtype, nBayerType, bFlip);
                // 前期准备
                if (DxStatus != DX_OK)
                {
                    RCLCPP_ERROR(this->get_logger(), "Raw8 to RGB24 failed!");
                    if (pRGB24Buf != NULL)
                    {
                        delete[] pRGB24Buf;
                        pRGB24Buf = NULL;
                    }
                    return;
                }
                cv::Mat Src = cv::Mat(pFrameBuffer->nHeight, pFrameBuffer->nWidth, CV_8UC3);

                memcpy(Src.data, pRGB24Buf, pFrameBuffer->nWidth * pFrameBuffer->nHeight * 3);
                // 给Mat赋值
                if (status == GX_STATUS_SUCCESS)
                {
                    cv::resize(Src, Src, cv::Size(640, 480));
                    image_msg_.header.stamp = this->get_clock()->now();
                    image_msg_.data.assign(Src.datastart, Src.dataend);
                    image_msg_.height = Src.rows;
                    image_msg_.width = Src.cols;
                    image_msg_.step = Src.cols * 3;
                    image_msg_.data.resize(Src.rows * Src.cols * 3);
                    img_pub_->publish(std::move(image_msg_));
                }
                delete[] pRGB24Buf;
                pRGB24Buf = NULL;
                // //调 用 GXQBuf 将 图 像 buf 放 回 库 中 继 续 采 图
                status = GXQBuf(hDevice, pFrameBuffer);
            }
            return;
        }
    };
} // namespace daheng_camera
#include "rclcpp_components/register_node_macro.hpp"
int main(int argc, char **argv)
{

    rclcpp::init(argc, argv);
    rclcpp::NodeOptions options;
    auto node = std::make_shared<daheng_camera::DaHengCameraNode>(options);
    while (rclcpp::ok())
    {
        rclcpp::spin_some(node);
    }

    rclcpp::shutdown();

    return 0;
}
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
RCLCPP_COMPONENTS_REGISTER_NODE(daheng_camera::DaHengCameraNode)