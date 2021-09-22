#include <gtest/gtest.h>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <map>

#include "generic_ode_model.h"

using Eigen::VectorXd;

TEST(BaseModel, BasicStuff) {
  GenericOdeModel base_model;
  
  base_model.Init();
  auto x = base_model.GetStates();
  EXPECT_EQ(x["x"], VectorXd::Ones(3));
  EXPECT_EQ(x["x"], VectorXd::Ones(3));

  std::map<std::string, VectorXd> test_input;
  test_input["u"] = VectorXd::Ones(3);

  for (int i = 0; i < 10; i++) {
    base_model.UpdateStates(test_input, 0.1);
    base_model.UpdateOutput(test_input);
  }
  x = base_model.GetStates();
  EXPECT_TRUE(x["x"].isApprox(2*VectorXd::Ones(3)));

  auto y = base_model.GetOutput();
  EXPECT_TRUE(y["x_out"].isApprox(2*VectorXd::Ones(3)));
}
