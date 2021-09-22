#ifndef TELEMETRY_LOGGING_MODULE_H 
#define TELEMETRY_LOGGING_MODULE_H

#include <map>
#include <eigen3/Eigen/Dense>
#include <memory>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "sensor_module.h"
#include "controls_module.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Onboard {

class TelemetryLoggingModule : public BaseModule {
  public:
    void Init(std::shared_ptr<ModuleDataCollection> data) override;    
    ~TelemetryLoggingModule();
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

    double _t;
    VectorXd _x = VectorXd::Zero(3);
    VectorXd _v = VectorXd::Zero(3);
    VectorXd _W = VectorXd::Zero(3);
    VectorXd _M = VectorXd::Zero(3);
    MatrixXd _R = MatrixXd::Zero(3,3);
    MatrixXd _Rd = MatrixXd::Zero(3,3);
    TelemetryLogging _tlm;
};

} // Onboard 

#endif
