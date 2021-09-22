#include "controller.h"


void Onboard::Controller::Init() {
  _Kx = 5;
  _Kv = 7;
  _KR = 25;
  _KW = 10;
  _mass = 4.34;
  _moment_of_inertia << 0.0820, 0, 0,
                        0, 0.0845, 0,
                        0, 0, 0.1377;
}

std::map<std::string, VectorXd> Onboard::Controller::StateOde(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  return x;
}

std::map<std::string, VectorXd> Onboard::Controller::MeasurementFunction(
    std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) {
  // constants
  double g = 9.81;
  VectorXd e3(3);
  e3 << 0, 0, 1;
  VectorXd gg(3);
  gg << 1, 0.9, 0.8;
  MatrixXd G = gg.asDiagonal();

  // get quadcopter states
  VectorXd pos = u["x"];
  VectorXd vel = u["v"];
  MatrixXd R(3,3);
  R = u["R"].reshaped(3,3);
  VectorXd W = u["W"];
  // get references
  VectorXd xd = u["xd"];
  VectorXd vd = VectorXd::Zero(3);
  // VectorXd vd = u["vd"];
  VectorXd ad = VectorXd::Zero(3);
  // VectorXd ad = u["ad"];
  VectorXd b1d = u["b1d"];
  VectorXd Wd = VectorXd::Zero(3);
  // VectorXd Wd = u["Wd"];
  // VectorXd Wd_dot = u["Wd_dot"];
  VectorXd Wd_dot = VectorXd::Zero(3);

  // compute error terms
  VectorXd ex = pos - xd;
  VectorXd ev = vel - vd;  

  // compute translational feedback
  VectorXd A = -_Kx*ex - _Kv*ev - _mass*g*e3 - _mass*ad;
  double fd = A.norm();
  VectorXd f(1);
  f << fd;

  // compute desired rotation matrix
  MatrixXd Rd(3,3);
  VectorXd b2d(3);
  VectorXd b3d(3);
  if (A.norm() != 0) {
    b3d = -A.normalized();
  }
  else {
    b3d << 0, 0, 1;
  }
  b2d = Utilities::Math::Hat(b3d)*b1d; 
  b2d = b2d.normalized();
  b1d = Utilities::Math::Hat(b2d)*b3d;
  Rd.col(0) = b1d;
  Rd.col(1) = b2d;
  Rd.col(2) = b3d;

  // compute rotational error terms
  VectorXd eR = 0.5 * Utilities::Math::Vee(Rd.transpose()*G*R - R.transpose()*G.transpose()*Rd);
  VectorXd eW = W - Wd;

  // compute attitude feedback
  VectorXd M = -_KR*eR - _KW*eW + Utilities::Math::Hat(W)*_moment_of_inertia*W 
    - _moment_of_inertia*(Utilities::Math::Hat(W)*R.transpose()*Rd*Wd - R.transpose()*Rd*Wd_dot);
  
  // return controller output
  std::map<std::string, VectorXd> y;
  y["f"] = f;
  y["M"] = M;
  y["Rd"] = Rd.reshaped(9,1);
  y["A"] = A;
  return y; 
}


