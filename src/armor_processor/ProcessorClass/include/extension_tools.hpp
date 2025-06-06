#ifndef ARMOR_PROCESSOR__EXTENSION_TOOLS_HPP_
#define ARMOR_PROCESSOR__EXTENSION_TOOLS_HPP_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
// Eigen
#include <Eigen/Dense>
#include <Eigen/Core>
using namespace std;
using namespace cv;

namespace rm_auto_aim
{

    class SphericalKalmanFilter
    {
    public:
        bool tracking_ = false;
        KalmanFilter skf = KalmanFilter(4, 2, 0);
        Mat state = Mat(4, 1, CV_32F);              // 状态向量 [x, y, dx/dt, dy/dt]
        Mat measurement = Mat::zeros(2, 1, CV_32F); // 观测值 [pitch, yaw]
        Mat prediction = Mat::zeros(2, 1, CV_32F);  // 观测值 [pitch, yaw]
        // 观测矩阵 H
        SphericalKalmanFilter();
        void initSKF(Eigen::Vector2d &angle);
        Eigen::Vector2d updateSKF(Eigen::Vector2d &angle);
    };

}
#endif // ARMOR_PROCESSOR_EXTENSION_TOOLS_HPP_