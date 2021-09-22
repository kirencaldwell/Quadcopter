#ifndef QUADCOPTER_MODEL_H
#define QUADCOPTER_MODEL_H

#include <map>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>

#include "Utilities/math.h"
#include "ControlsToolbox/generic_ode_model.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Simulation {

class QuadcopterModel : public GenericOdeModel {
  public:
    void Init();
    void UpdateStates(std::map<std::string, VectorXd> input, double dt) override;

  protected:
    std::map<std::string, VectorXd> StateOde( 
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;
    std::map<std::string, VectorXd> MeasurementFunction(
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;

    MatrixXd _moment_of_inertia = MatrixXd::Zero(3,3);
    double _mass;
    double _motor_arm;
    double _c_tau;
};

} // Simulation

#endif
