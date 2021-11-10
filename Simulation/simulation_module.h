#ifndef SIMULATION_MODULE_H
#define SIMULATION_MODULE_H

#include <map>
#include <eigen3/Eigen/Dense>
#include <memory>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "quadcopter_model.h"
#include "gyroscope_model.h"
#include "Onboard/sensor_module.h"
#include "Onboard/controls_module.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Simulation {

class SimulationModuleData {
  public:
    VectorXd x;
    VectorXd v;
    MatrixXd R;
    VectorXd W;
    VectorXd vdot;
    double t;
};

class SimulationModule : public BaseModule {
  public:
    void Init(std::shared_ptr<ModuleDataCollection> data) override;    
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

    SimulationModuleData _simulation_data;
    Onboard::SensorModuleData _sensor_data;
    QuadcopterModel _quadcopter;
    GyroscopeModel _gyroscope;
};

} // Simulation

#endif
