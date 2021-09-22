#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include "quadcopter_model.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

TEST(QuadcopterModelTests, Dynamics) {

    Simulation::QuadcopterModel quadcopter;
    quadcopter.Init();

    std::map<std::string, VectorXd> u;
    u["f"] = VectorXd::Zero(1);
    u["M"] = VectorXd::Zero(3);
    double dt = 0.01;
    quadcopter.UpdateStates(u, dt);
}