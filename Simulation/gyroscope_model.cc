#include "gyroscope_model.h"

void Simulation::GyroscopeModel::Init() {
  // intialize constants
  _parameters["b"] = ModelParameter(VectorXd::Zero(3), 0.1*MatrixXd::Identity(3, 3), false);
  // intialize states
  
  // initialize outputs
  _output["W"] = VectorXd::Zero(3);
}

void Simulation::GyroscopeModel::UpdateStates(std::map<std::string, VectorXd> input, double dt) {
}

std::map<std::string, VectorXd> Simulation::GyroscopeModel::StateOde(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
    return x;
}

std::map<std::string, VectorXd> Simulation::GyroscopeModel::MeasurementFunction(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  auto y = _output;
  VectorXd gyro_bias = _parameters["b"].GetVector();
  y["W"] = u["W"] - gyro_bias;
  return y;
}
