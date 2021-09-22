#include "quadcopter_model.h"

// hat map
// TODO: kirencaldwell - move this somewhere more useful

void Simulation::QuadcopterModel::Init() {
  // intialize constants
  _moment_of_inertia << 0.0820, 0, 0,
                        0, 0.0845, 0,
                        0, 0, 0.1377;
  _mass = 4.34;
  _motor_arm = 0.315;
  _c_tau = 8.004e-4;

  // intialize states
  _states["x"] = VectorXd::Zero(3);
  _states["v"] = VectorXd::Zero(3);
  _states["R"] = MatrixXd::Identity(3,3).reshaped(9,1);
  _states["W"] = VectorXd::Zero(3);
  
  // initialize outputs
  _output["x"] = VectorXd::Zero(3);
  _output["v"] = VectorXd::Zero(3);
}

void Simulation::QuadcopterModel::UpdateStates(std::map<std::string, VectorXd> input, double dt) {
  // get time derivative of states
  auto state_dot = StateOde(_states, input);
  // Euler integration for all states
  for (auto const& [key, val] : _states) {
    if (key == "R") {
      // unpack rotation matrix
      MatrixXd R(3,3);
      R = _states["R"].reshaped(3,3);
      R = R*(Utilities::Math::Hat(_states["W"]*dt)).exp();
      _states["R"] = R.reshaped(9,1);
      // _states["R"] = input["Rd"].reshaped(9,1);
    }
    else {
      _states[key] += dt*state_dot[key];
    }
  }
}

std::map<std::string, VectorXd> Simulation::QuadcopterModel::StateOde(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  auto x_dot = x;
  
  // constants
  // TODO: kirencaldwell - move these somewhere better
  VectorXd e3(3);
  e3 << 0, 0, 1;
  double g = 9.81;

  // convert to scalar?
  double f = u["f"](0);

  // unpack rotation matrix
  MatrixXd R(3,3);
  R = _states["R"].reshaped(3,3);
  
  // translational dynamics
  x_dot["x"] = x["v"];
  x_dot["v"] = (1/_mass) * (_mass*g*e3 - f*R*e3);

  // rotational dynamics
  x_dot["R"] = (R*Utilities::Math::Hat(x["W"])).reshaped(9,1);
  x_dot["W"] = _moment_of_inertia.inverse() * (u["M"] - Utilities::Math::Hat(x["W"])*_moment_of_inertia*x["W"]);

  return x_dot;
}

std::map<std::string, VectorXd> Simulation::QuadcopterModel::MeasurementFunction(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  auto y = _output;
  y["x"] = x["x"];
  y["v"] = x["v"];
  return y;
}
