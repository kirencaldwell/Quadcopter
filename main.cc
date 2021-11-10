#include <iostream>
#include <eigen3/Eigen/Dense>
#include <memory>
#include <math.h>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "external/ConcurrentModuleFramework/src/module_manager.h"
#include "Onboard/controls_module.h"
#include "Onboard/telemetry_logging_module.h"
#include "Simulation/simulation_module.h"

int main() {

  std::unique_ptr<BaseModule> controls_module(new Onboard::ControlsModule);
  std::unique_ptr<BaseModule> simulation_module(
    new Simulation::SimulationModule);
  std::unique_ptr<BaseModule> telemetry_logging_module(new Onboard::TelemetryLoggingModule);

  ModuleManager manager;
  manager.AddModule(std::move(controls_module));
  manager.AddModule(std::move(simulation_module));
  manager.AddModule(std::move(telemetry_logging_module));

  manager.InitModules();

  manager.StartModules(20);

  return 0;
}
