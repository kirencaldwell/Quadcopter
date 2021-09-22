#ifndef MATH_H
#define MATH_H

#include <eigen3/Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace Utilities {
namespace Math {

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
