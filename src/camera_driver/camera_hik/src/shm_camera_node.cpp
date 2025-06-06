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
    class ShmCameraNode : public rclcpp::Node
    {
        void *camera_handle_;
        std::shared_ptr<shm_video_trans::VideoSender> img_pub_;
        mutex mutex_;
        MV_CC_DEVICE_INFO_LIST device_list;

    public:
        ~ShmCameraNode()
        {
            MV_CC_StopGrabbing(camera_handle_);
            MV_CC_CloseDevice(camera_handle_);
            MV_CC_DestroyHandle(&camera_handle_);
        }
        explicit ShmCameraNode(const rclcpp::NodeOptions &options) : Node("shm_camera", options)
        {
            int nRet = MV_OK;
            RCLCPP_INFO(this->get_logger(), "Starting HikCameraNode!");
            img_pub_ = std::make_shared<shm_video_trans::VideoSender>("image_raw", 1280, 1024);
            // img_pub_[1] = std::make_shared<shm_video_trans::VideoSender>("image_law", 1280, 1024);

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
            MV_CC_SetFloatValue(camera_handle_, "ExposureTime", 5700);
            MV_CC_SetFloatValue(camera_handle_, "Gain", 16);
            MV_CC_StartGrabbing(camera_handle_);
            MV_FRAME_OUT out_frame;
            Mat frame = Mat::zeros(1024, 1280, CV_8UC3);
            while (rclcpp::ok())
            {
                nRet = MV_CC_GetImageBuffer(camera_handle_, &out_frame, 1000);
                while (( MV_OK!=nRet) && rclcpp::ok())
                {
                    RCLCPP_ERROR(this->get_logger(), "Try reconnecting the camera");
                    MV_CC_StopGrabbing(camera_handle_);
                    MV_CC_CloseDevice(camera_handle_);
                    MV_CC_DestroyHandle(&camera_handle_);
                    nRet = MV_CC_EnumDevices(MV_USB_DEVICE, &device_list);
                    RCLCPP_INFO(this->get_logger(), "Found camera count = %d", device_list.nDeviceNum);

                    if(device_list.nDeviceNum < 1 && rclcpp::ok())
                    {
                        RCLCPP_ERROR(this->get_logger(), "No camera found!");
                        RCLCPP_INFO(this->get_logger(), "Enum state: [%x]", nRet);
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        break;
                    }
                    MV_CC_CreateHandle(&camera_handle_, device_list.pDeviceInfo[0]);
                    MV_CC_OpenDevice(camera_handle_);
                    MV_CC_GetImageInfo(camera_handle_, &img_info_);
                    MV_CC_SetFloatValue(camera_handle_, "ExposureTime", 5700);
                    MV_CC_SetFloatValue(camera_handle_, "Gain", 16);
                    nRet = MV_CC_StartGrabbing(camera_handle_);
                    if ((nRet == MV_OK) && rclcpp::ok())
                    {
                        RCLCPP_INFO(this->get_logger(), "camera publish");
                        nRet = MV_CC_GetImageBuffer(camera_handle_, &out_frame, 1000);
                        break;
                    }
                    else
                    {
                        RCLCPP_ERROR(this->get_logger(), "Try reconnecting the camera");
                    }
                }
                if (MV_OK == nRet)
                {
                    // convert_param_.pDstBuffer = image_msg.data.data();
                    // convert_param_.nDstBufferSize = image_msg.data.size();
                    convert_param_.pDstBuffer = frame.data;
                    convert_param_.nDstBufferSize = out_frame.stFrameInfo.nHeight * out_frame.stFrameInfo.nWidth * 3;
                    convert_param_.pSrcData = out_frame.pBufAddr;
                    convert_param_.nSrcDataLen = out_frame.stFrameInfo.nFrameLen;
                    convert_param_.enSrcPixelType = out_frame.stFrameInfo.enPixelType;
                    MV_CC_ConvertPixelType(camera_handle_, &convert_param_);
                    // image_msg.header.stamp = this->get_clock()->now();
                    // image_msg.height = out_frame.stFrameInfo.nHeight;
                    // image_msg.width = out_frame.stFrameInfo.nWidth;
                    // image_msg.step = out_frame.stFrameInfo.nWidth * 3;
                    // image_msg.data.resize(image_msg.width * image_msg.height * 3);
                    if (!frame.empty())
                    {
                        cvtColor(frame, frame, cv::COLOR_RGB2BGR);
                        img_pub_->send(frame, std::chrono::high_resolution_clock::now());
                    }
                    // img_pub_[num]->publish(image_msg);
                    MV_CC_FreeImageBuffer(camera_handle_, &out_frame);
                }
            }
        }
    };
} // namespace hik_camera
#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(hik_camera::ShmCameraNode)