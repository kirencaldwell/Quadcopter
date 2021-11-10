#ifndef GYROSCOPE_MODEL_H
#define GYROSCOPE_MODEL_H

#include <map>
#include <iostream>
#include <eigen3/Eigen/Dense>
#include <eigen3/unsupported/Eigen/MatrixFunctions>

#include "Utilities/math.h"
#include "ControlsToolbox/generic_ode_model.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Simulation {

class GyroscopeModel: public GenericOdeModel {
  public:
    void Init();
    void UpdateStates(std::map<std::string, VectorXd> input, double dt) override;

  protected:
    std::map<std::string, VectorXd> StateOde( 
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;
    std::map<std::string, VectorXd> MeasurementFunction(
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;

};

} // Simulation

#endif
