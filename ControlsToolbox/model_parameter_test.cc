#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <map>

#include "model_parameter.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

TEST(ModelParameters, BasicStuff) {
    ModelParameter mc_scalar(1, 2, true);
    ModelParameter scalar(1, 2, false);
    ModelParameter mc_vector(VectorXd::Ones(3), MatrixXd::Identity(3,3), true);
    ModelParameter vector(VectorXd::Ones(3), MatrixXd::Identity(3,3), false);

    EXPECT_EQ(scalar.GetScalar(), 1);
    EXPECT_EQ(vector.GetVector(), VectorXd::Ones(3));

    // expect scalar to be between +/- 4 sigma
    EXPECT_GT(mc_scalar.GetScalar(), -7);
    EXPECT_LT(mc_scalar.GetScalar(), 9);

    // TODO: kirencaldwell - create tests for true variance in distributions
}