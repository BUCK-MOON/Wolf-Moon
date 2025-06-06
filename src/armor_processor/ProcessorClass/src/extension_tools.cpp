#include "../include/extension_tools.hpp"
namespace rm_auto_aim
{

    SphericalKalmanFilter::SphericalKalmanFilter()
    {
        skf.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0,
                                0, 1, 0, 1,
                                0, 0, 1, 0,
                                0, 0, 0, 1);
        setIdentity(skf.measurementMatrix);

        // 过程噪声协方差矩阵 Q
        setIdentity(skf.processNoiseCov, Scalar::all(7));

        // 观测噪声协方差矩阵 R
        setIdentity(skf.measurementNoiseCov, Scalar::all(0.1));
    }
    void SphericalKalmanFilter::initSKF(Eigen::Vector2d &angle)
    {
        // 初始状态估计值
        skf.statePost.at<float>(0) = angle[0];
        skf.statePost.at<float>(1) = 0;
        skf.statePost.at<float>(2) = angle[1];
        skf.statePost.at<float>(3) = 0;
        tracking_ = true;
    }
    Eigen::Vector2d SphericalKalmanFilter::updateSKF(Eigen::Vector2d &angle)
    {
        cv::Mat predit = skf.predict();
        if (abs(predit.at<float>(0)) < 0.01 && abs(predit.at<float>(1)) < 0.01)
            tracking_ = false;
        measurement.at<float>(0) = angle[0];
        measurement.at<float>(1) = angle[1];
        // 更新卡尔曼滤波器的状态估计值
        prediction = skf.correct(measurement);
        return Eigen::Vector2d(predit.at<float>(0),predit.at<float>(1));
    }
}