#ifndef CONTROLS_MODULE_H 
#define CONTROLS_MODULE_H

#include <eigen3/Eigen/Dense>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "controller.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

namespace Onboard {

class ControlsModuleData {
  public:
    VectorXd f;
    VectorXd M;

};

class ControlsModule : public BaseModule {
  public:
    void Init(std::shared_ptr<ModuleDataCollection> data) override;    
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

    ControlsModuleData _controls_data;
    Controller _controller;
};

} // Onboard 

#endif
