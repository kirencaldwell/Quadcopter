#ifndef CONTROLS_MODULE_H 
#define CONTROLS_MODULE_H

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "controller.h"

namespace Onboard {
class ControlsModule : public BaseModule {
  public:
    ControlsModule();
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

    Controller _controller;
};
} // Onboard 

#endif
