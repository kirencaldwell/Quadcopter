#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <map>
#include <math.h>
#include "named_vector.h"

#include "generic_model.h"

using Eigen::VectorXd;

class PendulumModel : public GenericModel {
  public: 
    void Init(bool monte_carlo_flag) {
      _parameters.AddParameter("m", 2, 0.1, monte_carlo_flag);
      _parameters.AddParameter("k", 3, 0.1, monte_carlo_flag);
      _parameters.AddParameter("c", 1, 0.1, monte_carlo_flag);
      _states.Add("theta", 1);
      _states.Add("theta_dot", 0);
      _output.Add("theta", 1);

      SetModelCovariance(0.1*MatrixXd::Identity(2,2));
      SetMeasurementCovariance(0.1*MatrixXd::Identity(1,1));
    }

    NamedVector ComputeDerivative(NamedVector x, NamedVector u) override {
      auto state_dot = x;

      double theta = x.Get<double>("theta");
      double theta_dot = x.Get<double>("theta_dot");
      double theta_ddot = (1/_parameters.Get<double>("m")) * (-_parameters.Get<double>("k")*theta - _parameters.Get<double>("c")*theta_dot) + u.Get<double>("u");
      state_dot.Set("theta", theta_dot);
      state_dot.Set("theta_dot", theta_ddot);
      return state_dot;
    }

    NamedVector ComputeMeasurement(NamedVector x, NamedVector u) override {
      auto out = _output;
      out.Set("theta", x.Get<double>("theta") + u.Get<double>("u"));
      return out;
    }
};

// TEST(BaseModel, GenerateNoisySolution) {
//   PendulumModel pendulum;

//   pendulum.Init(true);
//   auto x = pendulum.GetStates();
//   EXPECT_EQ(x.Get<double>("theta"), 1);

//   std::map<std::string, VectorXd> test_input;
//   test_input["u"] = VectorXd::Zero(1);

//   for (int i = 0; i < 100000; i++) {
//     pendulum.PropagateWithNoise(test_input, 0.1);
//   }
//   x = pendulum.GetStates();
//   EXPECT_FALSE(x["theta"].isApprox(VectorXd::Zero(1)));

//   auto y = pendulum.GetOutput();
//   EXPECT_FALSE(y["theta"].isApprox(VectorXd::Zero(1)));
// }
TEST(BaseModel, GenerateNominalSolution) {
  PendulumModel pendulum;

  pendulum.Init(false);
  auto x = pendulum.GetStates();
  EXPECT_EQ(x.Get<double>("theta"), 1);

  NamedVector test_input;
  test_input.Add("u", 0);

  for (int i = 0; i < 1000; i++) {
    pendulum.Propagate(test_input, 0.1);
  }
  x = pendulum.GetStates();
  EXPECT_LT(x.Get<double>("theta"), 0.01);

  auto y = pendulum.GetOutput();
  EXPECT_LT(y.Get<double>("theta"), 0.01);
}

TEST(BaseModel, GenerateLinearModels) {
  PendulumModel pendulum;

  pendulum.Init(false);
  auto x = pendulum.GetStates();
  EXPECT_EQ(x.Get<double>("theta"), 1);

  NamedVector u;
  u.Add("u", 0);
  MatrixXd A_exp(2,2);
  A_exp << 0, 1, -1.5, -0.5;
  MatrixXd B_exp(2,1);
  B_exp << 0, 1;
  MatrixXd C_exp(1,2);
  C_exp << 1, 0;
  MatrixXd D_exp = MatrixXd::Ones(1,1);
  LinearModel linear_model = pendulum.GetLinearModel(x, u);

  EXPECT_TRUE(linear_model.A.isApprox(A_exp));
  EXPECT_TRUE(linear_model.B.isApprox(B_exp));
  EXPECT_TRUE(linear_model.C.isApprox(C_exp));
  EXPECT_TRUE(linear_model.D.isApprox(D_exp));
}



