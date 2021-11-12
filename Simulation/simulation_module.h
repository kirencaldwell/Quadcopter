#ifndef SIMULATION_MODULE_H
#define SIMULATION_MODULE_H

#include <memory>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "external/ConcurrentModuleFramework/src/base_module_data.h"
#include "quadcopter_model.h"
#include "gyroscope_model.h"


namespace Simulation {
class SimulationModule : public BaseModule {
  public:
    SimulationModule();
  private:
    void Poll(std::shared_ptr<ModuleDataCollection> data) override;

    QuadcopterModel _quadcopter;
    GyroscopeModel _gyroscope;
    BaseModuleData _sensor_data; 
};
} // Simulation

#endif
