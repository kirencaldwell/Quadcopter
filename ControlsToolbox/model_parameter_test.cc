#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <map>

#include "model_parameter.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

TEST(ModelParameters, BasicStuff) {
    ModelParameter parameters;
    parameters.AddParameter("mc_scalar", 1, 2, true);
    parameters.AddParameter("scalar", 1, 2, false);
    parameters.AddParameter("mc_vector", VectorXd::Ones(3), MatrixXd::Identity(3,3), true);
    parameters.AddParameter("vector", VectorXd::Ones(3), MatrixXd::Identity(3,3), false);

    EXPECT_EQ(parameters.Get<double>("scalar"), 1);
    EXPECT_EQ(parameters.Get<VectorXd>("vector"), VectorXd::Ones(3));

    // expect scalar to be between +/- 4 sigma
    EXPECT_GT(parameters.Get<double>("scalar"), -7);
    EXPECT_LT(parameters.Get<double>("scalar"), 9);

    // TODO: kirencaldwell - create tests for true variance in distributions
}