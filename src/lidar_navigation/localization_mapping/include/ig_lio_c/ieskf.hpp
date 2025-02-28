#ifndef IESKF_HPP_
#define IESKF_HPP_

#include <Eigen/Core>
#include <sophus/so3.hpp>

namespace IG_LIO
{
  const double GRAVITY = 9.8011;
  using Vector21d = Eigen::Matrix<double, 21, 1>;
  using Vector12d = Eigen::Matrix<double, 12, 1>;
  using Vector23d = Eigen::Matrix<double, 23, 1>;
  using Vector24d = Eigen::Matrix<double, 24, 1>;

  using Matrix21d = Eigen::Matrix<double, 21, 21>;
  using Matrix12d = Eigen::Matrix<double, 12, 12>;
  using Matrix23d = Eigen::Matrix<double, 23, 23>;

  using Matrix3x2d = Eigen::Matrix<double, 3, 2>;
  using Matrix2x3d = Eigen::Matrix<double, 2, 3>;
  using Matrix21x12d = Eigen::Matrix<double, 21, 12>;
  using Matrix23x12d = Eigen::Matrix<double, 23, 12>;

  Eigen::Matrix3d rightJacobian(const Eigen::Vector3d &inp);

  struct SharedState
  {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW // 主要用于确保对象在内存中按照适当的对齐方式进行分配
        Matrix12d H;
    Vector12d b;
    size_t iter_num = 0;
  };

  struct State // 物理运动状态
  {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Eigen::Vector3d pos = Eigen::Vector3d::Zero();           // 位置
    Eigen::Matrix3d rot = Eigen::Matrix3d::Identity();       // 旋转状态
    Eigen::Vector3d pos_ext = Eigen::Vector3d::Zero();       // ext系下位置
    Eigen::Matrix3d rot_ext = Eigen::Matrix3d::Identity();   // ext系下旋转矩阵
    Eigen::Vector3d vel = Eigen::Vector3d::Zero();           // 速度状态
    Eigen::Vector3d bg = Eigen::Vector3d::Zero();            // 加速度计偏置，纠正偏差
    Eigen::Vector3d ba = Eigen::Vector3d::Zero();            // 陀螺仪偏置
    Eigen::Vector3d g = Eigen::Vector3d(0.0, 0.0, -GRAVITY); // 重力加速度，通过 initG 方法可以重新初始化。

    /**
     * 该方法初始化重力加速度向量 g，使其符合给定的方向（gravity_dir）并乘以常数重力加速度（GRAVITY）。这对于考虑不同方向的重力影响可能很有用。
     */
    void initG(const Eigen::Vector3d &gravity_dir)
    {
      g = gravity_dir.normalized() * GRAVITY;
    }

    // 状态转换计算方法
    void operator+=(const Vector23d &delta);

    void operator+=(const Vector24d &delta);

    Vector23d operator-(const State &other);

    Matrix3x2d getBx() const;

    Matrix3x2d getMx() const;

    Matrix3x2d getMx(const Eigen::Vector2d &res) const;

    Matrix2x3d getNx() const;
  };

  struct Input // 存储加速度计，和陀螺仪数据
  {
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Eigen::Vector3d acc;  // 存储加速度数据
    Eigen::Vector3d gyro; // 陀螺仪角角度分量
    Input() = default;
    Input(Eigen::Vector3d &a, Eigen::Vector3d &g) : acc(a), gyro(g) {}
    Input(double a1, double a2, double a3, double g1, double g2, double g3) : acc(a1, a2, a3), gyro(g1, g2, g3) {}
  };

  // std::function 是 C++11 引入的一个模板类，它允许你将任何符合特定签名的可调用对象封装成一个统一的类型。
  using measure_func = std::function<void(State &, SharedState &)>;

  class IESKF // 卡尔曼滤波器
  {
  public:
    IESKF();
    IESKF(size_t max_iter) : max_iter_(max_iter) {}

    State &x() { return x_; }

    void change_x(State &x) { x_ = x; }

    Matrix23d &P() { return P_; }

    void set_share_function(measure_func func) { func_ = func; }

    void change_P(Matrix23d &P) { P_ = P; }

    void predict(const Input &inp, double dt, const Matrix12d &Q);

    void update();

  private:
    size_t max_iter_ = 8; // 最大迭代次数，可能与滤波过程中的某些优化或非线性问题的求解有关（例如牛顿法、最小二乘法等）。
    double eps_ = 0.001;  // 一个小的阈值，用来控制迭代的终止条件，通常用于判断算法是否收敛。
    State x_;             // 代表当前的 状态向量。这通常包括系统的各种估计状态（如位置、速度、姿态等）。
    Matrix23d P_;         // 代表 误差协方差矩阵，用于衡量状态估计的精度。它描述了状态变量之间的不确定性或误差。
    measure_func func_;   // 这是一个函数指针或函数对象，用于进行某种测量操作的回调（类型是 measure_func，也许它是一个自定义的类型）。这通常用于测量更新步骤，用来获取新的传感器数据。
    Matrix23d H_;         // 观测矩阵（或称 测量矩阵），它将预测的状态转换为观测空间。用于将预测的状态与实际测量值对比。
    Vector23d b_;         // 观测残差 或 校正项，它用于在更新步骤中调整状态估计。
    Matrix23d F_;         // 可能是 状态转移矩阵，描述了如何从当前状态推算到下一个状态，通常与系统的动力学模型有关。
    Matrix23x12d G_;      // 可能是 过程噪声矩阵，它将过程噪声与状态变量之间的关系进行建模。
  };
} // namespace IG_LIO
#endif // _IESKF_H