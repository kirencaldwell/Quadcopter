#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>

#include "named_vector.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

TEST(NamedVectorTests, Algebra) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    double r = 2;
    MatrixXd A = r*MatrixXd::Identity(13,13);
    NamedVector out = r*(A*vec + vec + r*vec);
    EXPECT_EQ(out.Get(), r*(A*vec.Get() + vec.Get() + r*vec.Get()));
}
TEST(NamedVectorTests, WorkingWithMatrices) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    MatrixXd A = 2*MatrixXd::Identity(13,13);
    NamedVector out = A*vec;
    EXPECT_EQ(out.Get(), A*vec.Get());
}

TEST(NamedVectorTests, WorkingWithDoubles) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    double r = 5;
    NamedVector out = vec+r;
    EXPECT_EQ(out.Get(), vec.Get()+r*VectorXd::Ones(vec.Get().size()));
    out = r+vec;
    EXPECT_EQ(out.Get(), vec.Get()+r*VectorXd::Ones(vec.Get().size()));

    out = r*vec;
    EXPECT_EQ(out.Get(), r*vec.Get());
    out = vec*r;
    EXPECT_EQ(out.Get(), r*vec.Get());
}

TEST(NamedVectorTests, Subtraction) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    NamedVector vec2;
    vec2 = vec;

    NamedVector vec3 = vec - vec2;
    EXPECT_EQ(vec3.Get(), vec.Get()-vec2.Get());
}

TEST(NamedVectorTests, Addition) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    NamedVector vec2;
    vec2 = vec;

    NamedVector vec3 = vec + vec2;
    EXPECT_EQ(vec3.Get(), vec.Get()+vec2.Get());
}

TEST(NamedVectorTests, GetAndSet) {
    NamedVector vec;
    double x = 0.1;
    VectorXd y(3);
    y << 1,2,3;
    MatrixXd R = MatrixXd::Identity(3,3);
    vec.Add("x", x);    
    vec.Add("y", y);
    vec.Add("R", R);

    NamedVector vec2;
    vec2 = vec;

    EXPECT_EQ(vec.Get<double>("x"), x);
    EXPECT_EQ(vec.Get<VectorXd>("y"), y);
    EXPECT_EQ(vec.Get<MatrixXd>("R"), R);
    EXPECT_EQ(vec2.Get<VectorXd>("y"), y);

    VectorXd u(1+y.size()+R.size());
    u << x, y, R.reshaped(R.size(),1);
    EXPECT_EQ(vec.Get(), u);

    vec.Set("x", 2.5);
    y << 4,5,6;
    vec.Set("y", y);
    EXPECT_EQ(vec.Get<double>("x"), 2.5); 
    EXPECT_EQ(vec.Get<VectorXd>("y"), y);

    u(4) = 77;
    vec.Set(u);
    EXPECT_EQ(vec.Get(), u);
}