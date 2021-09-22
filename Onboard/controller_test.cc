#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include "controller.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

TEST(ControllerTests, BasicFunctions) {
  Onboard::Controller controller;
  
  VectorXd e1(3);
  e1 << 1, 0, 0;

  std::map<std::string, VectorXd> x;
  std::map<std::string, VectorXd> u;
  u["x"] = VectorXd::Zero(3);
  u["v"] = VectorXd::Zero(3);
  u["R"] = MatrixXd::Identity(3,3).reshaped(9,1);
  u["W"] = VectorXd::Zero(3);
  u["xd"] = VectorXd::Ones(3);
  u["b1d"] = e1;

  controller.UpdateOutput(u);
}
