#include "generic_model.h"
#include "Utilities/math.h"
#include <iostream>

// Initialization step, to be filled in by specific model
void GenericModel::Init(bool monte_carlo_flag) {
  double m = 1;
  double m_var = 0.2;
  _parameters.AddParameter("m", m, m_var, false);
  VectorXd x = VectorXd::Ones(3);
  VectorXd x_out = VectorXd::Ones(3);
  _states.Add("x", x);
  _output.Add("x_out", x_out);
}

void GenericModel::Propagate(NamedVector input, double dt) {
  IntegrateOde(input, dt);
  UpdateOutput(input);
}

void GenericModel::PropagateWithNoise(NamedVector input, double dt) {
  IntegrateOde(input, dt);
  _states = AddNoise(_states, _Q);
  UpdateOutput(input);
  _output = AddNoise(_output, _R);
}

void GenericModel::IntegrateOde(NamedVector input, double dt) {
  // get time derivative of states
  auto state_dot = ComputeDerivative(_states, input);
  // Euler integration for all states
  _states = _states + dt*state_dot;
}

NamedVector GenericModel::AddNoise(NamedVector x, MatrixXd P) {
  Utilities::Math::NormalRandomVariable q{P};
  x.Set(x.Get() + q());
  return x;
}

LinearModel GenericModel::GetLinearModel(NamedVector x, NamedVector u) {
  LinearModel out;
  auto f0 = ComputeDerivative(x, u);
  auto y0 = ComputeMeasurement(x, u);
  int n = x.size();
  int m = y0.size();
  int p = u.size();

  out.A = MatrixXd::Zero(n, n);
  out.B = MatrixXd::Zero(n, p);
  out.C = MatrixXd::Zero(m, n);
  out.D = MatrixXd::Zero(m, p);

  double h = 0.0001;
  for (int i = 0; i < n; i++) {
    VectorXd H = VectorXd::Zero(n);
    H(i) = h;
    NamedVector xi = x + H;
    auto fi = ComputeDerivative(xi, u);
    out.A.col(i) = (fi.Get() - f0.Get())/h;
  }
  for (int i = 0; i < p; i++) {
    VectorXd H = VectorXd::Zero(p);
    H(i) = h;
    NamedVector ui = u + H;
    auto fi = ComputeDerivative(x, ui);
    out.B.col(i) = (fi.Get() - f0.Get())/h;
  }
  for (int i = 0; i < n; i++) {
    VectorXd H = VectorXd::Zero(n);
    H(i) = h;
    NamedVector xi = x + H;
    auto yi = ComputeMeasurement(xi, u);
    out.C.col(i) = (yi.Get() - y0.Get())/h;
  }
  for (int i = 0; i < p; i++) {
    VectorXd H = VectorXd::Zero(p);
    H(i) = h;
    NamedVector ui = u + H;
    auto yi = ComputeMeasurement(x, ui);
    out.D.col(i) = (yi.Get() - y0.Get())/h;
  }
  return out;
}

NamedVector GenericModel::ComputeDerivative(
    NamedVector x, NamedVector u) {
  NamedVector state_dot = x;
  state_dot.Set("x", u.Get<VectorXd>("u"));
  return state_dot;
}

NamedVector GenericModel::ComputeMeasurement(
    NamedVector x, NamedVector u) {
  NamedVector y = _output;
  y.Set("x_out", x.Get<VectorXd>("x"));
  return y;
}

void GenericModel::UpdateOutput(NamedVector input) {
  _output = ComputeMeasurement(_states, input);
}

NamedVector GenericModel::GetOutput() {
  return _output;
}

NamedVector GenericModel::GetStates() {
  return _states;
}
  
