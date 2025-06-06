#ifndef ARMOR_DETECTOR__INFERENCE_HPP_
#define ARMOR_DETECTOR__INFERENCE_HPP_

// c++
#include <iterator>
#include <memory>
#include <string>
#include <vector>
#include <iostream>

// ROS
#include <image_transport/image_transport.hpp>
#include <image_transport/publisher.hpp>
#include <image_transport/subscriber_filter.hpp>
#include <rclcpp/publisher.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/camera_info.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

// openvino
#include <openvino/openvino.hpp>

// opencv
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>

// eigen
#include <Eigen/Dense>

// #include "../armor/armor.hpp"

namespace rm_auto_aim
{
    struct Object
    {
        cv::Rect_<float> rect;
        int cls;
        int color;
        float prob;
        std::vector<cv::Point2f> pts;
    };
    struct ArmorObject : Object
    {
        int area;
        cv::Point2f apex[4];
    };
    struct GridAndStride
    {
        int grid0;
        int grid1;
        int stride;
    };
    /**
     * 图像推理类
     */
    class Detector
    {
    public:
        Detector();
        bool detect(cv::Mat &src, std::vector<ArmorObject> &objects);
        bool initModel(std::string path);

    private:
        int dw, dh;
        float rescale_ratio;
        ov::Core core;
        std::shared_ptr<ov::Model> model; // 网络
        ov::CompiledModel compiled_model; // 可执行网络
        ov::InferRequest infer_request;   // 推理请求
        ov::Tensor input_tensor;
        std::string input_name;
        std::string output_name;
        Eigen::Matrix<float, 3, 3> transfrom_matrix;
        /////////////////
        // log control //
        /////////////////
    public:
        rclcpp::Logger logger_;
        rclcpp::Clock steady_clock_{RCL_STEADY_TIME};
    };

}

#endif