#ifndef SENSOR_MODULE_H 
#define SENSOR_MODULE_H 

#include <map>
#include <eigen3/Eigen/Dense>
#include <memory>

#include "external/ConcurrentModuleFramework/src/base_module.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Onboard {

class SensorModuleData {
  public:
    VectorXd x;
    VectorXd v;
    MatrixXd R;
    VectorXd W;
    double t;
};

class SensorModule : public BaseModule {
  public:
    void Init(std::shared_ptr<ModuleDataCollection> data) override;    
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;
};

} // Simulation

#endif
