#ifndef MATH_H
#define MATH_H

#include <eigen3/Eigen/Dense>
#include "eigen3/unsupported/Eigen/MatrixFunctions"
#include <random>

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace Utilities {
namespace Math {

struct NormalRandomVariable 
{
    NormalRandomVariable(Eigen::MatrixXd const& covar)
        : NormalRandomVariable(Eigen::VectorXd::Zero(covar.rows()), covar)
    {}

    NormalRandomVariable(Eigen::VectorXd const& mean, Eigen::MatrixXd const& covar)
        : mean(mean)
    {
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(covar);
        transform = eigenSolver.eigenvectors() * eigenSolver.eigenvalues().cwiseSqrt().asDiagonal();
    }

    Eigen::VectorXd mean;
    Eigen::MatrixXd transform;

    Eigen::VectorXd operator()() const
    {
        static std::mt19937 gen{ std::random_device{}() };
        static std::normal_distribution<> dist;

        return mean + transform * Eigen::VectorXd{ mean.size() }.unaryExpr([&](auto x) { return dist(gen); });
    }
};

inline MatrixXd Hat(VectorXd x) {
  MatrixXd A(3,3);
  A << 0, -x(2), x(1), 
      x(2), 0, -x(0),
      -x(1), x(0), 0;
  return A;
}

inline VectorXd Vee(MatrixXd A) {
  VectorXd y(3);
  y << A(2,1), A(0,2), A(1,0);
  return y;
} 

} // Math
} // Utilities

#endif
