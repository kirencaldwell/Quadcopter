#include "generic_ode_model.h"

// Initialization step, to be filled in by specific model
void GenericOdeModel::Init() {
  _states["x"] = VectorXd::Ones(3);
  _output["x_out"] = VectorXd::Ones(3);
}

void GenericOdeModel::UpdateStates(std::map<std::string, VectorXd> input, double dt) {
  // get time derivative of states
  auto state_dot = StateOde(_states, input);
  // Euler integration for all states
  for (auto const& [key, val] : _states) {
    _states[key] += dt*state_dot[key];
  }
}

std::map<std::string, VectorXd> GenericOdeModel::StateOde(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  auto state_dot = x;
  state_dot["x"] = u["u"];
  return state_dot;
}

std::map<std::string, VectorXd> GenericOdeModel::MeasurementFunction(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  auto y = _output;
  y["x_out"] = x["x"];
  return y;
}

void GenericOdeModel::UpdateOutput(std::map<std::string, VectorXd> input) {
  _output = MeasurementFunction(_states, input);
}

std::map<std::string, VectorXd> GenericOdeModel::GetOutput() {
  return _output;
}

std::map<std::string, VectorXd> GenericOdeModel::GetStates() {
  return _states;
}
  
