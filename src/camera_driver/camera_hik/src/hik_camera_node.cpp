#include "MvCameraControl.h"
// ROS
#include <camera_info_manager/camera_info_manager.hpp>
#include <image_transport/image_transport.hpp>
#include <rclcpp/logging.hpp>
#include <rclcpp/rclcpp.hpp>
#include <mutex>
#include <rclcpp/utilities.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
// OpenCV
#include <opencv2/opencv.hpp>

// SHM
#include "../shm_sdk/shm_video_transmission.h"

using namespace std;
using namespace cv;
namespace hik_camera
{
    class HikCameraNode : public rclcpp::Node
    {
        void *camera_handle_;
        // std::shared_ptr<shm_video_trans::VideoSender> img_pub_;
        // mutex mutex_;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr img_pub_;
        sensor_msgs::msg::Image image_msg_;
        MV_CC_DEVICE_INFO_LIST device_list;

    public:
        ~HikCameraNode()
        {
            MV_CC_StopGrabbing(camera_handle_);
            MV_CC_CloseDevice(camera_handle_);
            MV_CC_DestroyHandle(&camera_handle_);
        }
        explicit HikCameraNode(const rclcpp::NodeOptions &options) : Node("shm_camera", options)
        {
            int nRet = MV_OK;
            RCLCPP_INFO(this->get_logger(), "Starting HikCameraNode!");
            // img_pub_ = std::make_shared<shm_video_trans::VideoSender>("image_raw", 1280, 1024);
            // img_pub_[1] = std::make_shared<shm_video_trans::VideoSender>("image_law", 1280, 1024);
            img_pub_ = this->create_publisher<sensor_msgs::msg::Image>("image_raw", rclcpp::SensorDataQoS());
            // 遍历像机
            nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
            RCLCPP_INFO(this->get_logger(), "Found camera count = %d", device_list.nDeviceNum);

            while (device_list.nDeviceNum < 1 && rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "No camera found!");
                RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
                std::this_thread::sleep_for(std::chrono::seconds(1));
                nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
            }
            // RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
            MV_IMAGE_BASIC_INFO img_info_;
            MV_CC_PIXEL_CONVERT_PARAM convert_param_;
            // sensor_msgs::msg::Image image_msg;
            MV_CC_CreateHandle(&camera_handle_, device_list.pDeviceInfo[0]);
            MV_CC_OpenDevice(camera_handle_);
            MV_CC_GetImageInfo(camera_handle_, &img_info_);
            // Init convert param
            convert_param_.nWidth = img_info_.nWidthValue;
            convert_param_.nHeight = img_info_.nHeightValue;
            convert_param_.enDstPixelType = PixelType_Gvsp_RGB8_Packed;
            MV_CC_SetFloatValue(camera_handle_, "ExposureTime", 4700);
            MV_CC_SetFloatValue(camera_handle_, "Gain", 16);
            MV_CC_StartGrabbing(camera_handle_);

            MV_FRAME_OUT out_frame;
            // RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
            while (rclcpp::ok())
            {
                nRet = MV_CC_GetImageBuffer(camera_handle_, &out_frame, 1000);
                if (MV_OK == nRet)
                {
                    Mat frame = Mat::zeros(1024, 1280, CV_8UC3);

                    // convert_param_.pDstBuffer = image_msg_.data.data();
                    // convert_param_.nDstBufferSize = image_msg_.data.size();
                    std::cout << "1" << std::endl;
                    convert_param_.pDstBuffer = frame.data;
                    convert_param_.nDstBufferSize = out_frame.stFrameInfo.nHeight * out_frame.stFrameInfo.nWidth * 3;
                    convert_param_.pSrcData = out_frame.pBufAddr;
                    convert_param_.nSrcDataLen = out_frame.stFrameInfo.nFrameLen;
                    convert_param_.enSrcPixelType = out_frame.stFrameInfo.enPixelType;
                    std::cout << "1" << std::endl;
                    MV_CC_ConvertPixelType(camera_handle_, &convert_param_);
                    image_msg_.header.stamp = this->get_clock()->now();
                    image_msg_.encoding = "rgb8";
                    std::cout << "1" << std::endl;
                    // image_msg_.height = out_frame.stFrameInfo.nHeight;
                    // image_msg_.width = out_frame.stFrameInfo.nWidth;
                    // image_msg_.step = out_frame.stFrameInfo.nWidth * 3;
                    // image_msg_.data.resize(image_msg_.width * image_msg_.height * 3);
                    // if (!frame.empty())
                    // {
                    // Mat frame;
                    cvtColor(frame, frame, cv::COLOR_RGB2BGR);
                    // cv::resize(frame, frame, cv::Size(640, 480));
                    image_msg_.data.assign(frame.datastart, frame.dataend);
                    image_msg_.height = frame.rows;
                    image_msg_.width = frame.cols;
                    image_msg_.step = frame.cols * 3;
                    image_msg_.data.resize(frame.rows * frame.cols * 3);
                    img_pub_->publish(std::move(image_msg_));
                    MV_CC_FreeImageBuffer(camera_handle_, &out_frame);
                }
                else
                {
                    nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
                    RCLCPP_INFO(this->get_logger(), "Found camera count = %d", device_list.nDeviceNum);
                    while (device_list.nDeviceNum < 1 && rclcpp::ok())
                    {
                        RCLCPP_ERROR(this->get_logger(), "No camera found!");
                        RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
                    }
                    // RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
                    // MV_IMAGE_BASIC_INFO img_info_;
                    // MV_CC_PIXEL_CONVERT_PARAM convert_param_;
                    // sensor_msgs::msg::Image image_msg;
                    MV_CC_CreateHandle(&camera_handle_, device_list.pDeviceInfo[0]);
                    MV_CC_OpenDevice(camera_handle_);
                    MV_CC_GetImageInfo(camera_handle_, &img_info_);
                    // Init convert param
                    convert_param_.nWidth = img_info_.nWidthValue;
                    convert_param_.nHeight = img_info_.nHeightValue;
                    convert_param_.enDstPixelType = PixelType_Gvsp_RGB8_Packed;
                    MV_CC_SetFloatValue(camera_handle_, "ExposureTime", 5600);
                    MV_CC_SetFloatValue(camera_handle_, "Gain", 32);
                    MV_CC_StartGrabbing(camera_handle_);
                }
            }
        }
    };
} // namespace hik_camera
#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(hik_camera::HikCameraNode)