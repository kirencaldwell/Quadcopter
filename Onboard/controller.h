#ifndef CONTROLLER_H
#define CONTROLLER_H


#include <map>
#include <eigen3/Eigen/Dense>
#include <memory>

#include "ControlsToolbox/generic_ode_model.h"
#include "Utilities/math.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Onboard {

class Controller : public GenericOdeModel {
  public:
    void Init() override;

  protected:
    std::map<std::string, VectorXd> StateOde(
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;
    std::map<std::string, VectorXd> MeasurementFunction(
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u) override;

    double _Kx;
    double _Kv;
    double _KR;
    double _KW;
    double _mass;
    MatrixXd _moment_of_inertia = MatrixXd::Zero(3,3);
};

} // Onboard


#endif
