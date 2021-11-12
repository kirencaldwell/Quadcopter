#include <iostream>
#include <eigen3/Eigen/Dense>
#include <memory>
#include <math.h>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "external/ConcurrentModuleFramework/src/module_manager.h"
#include "Onboard/controls_module.h"
#include "Onboard/guidance_module.h"
#include "Onboard/navigation_module.h"
#include "Simulation/simulation_module.h"
#include "Simulation/sensor_module.h"

int main() {

  std::unique_ptr<BaseModule> controls_module(new Onboard::ControlsModule);
  std::unique_ptr<BaseModule> guidance_module(new Onboard::GuidanceModule);
  std::unique_ptr<BaseModule> navigation_module(new Onboard::NavigationModule);

  std::unique_ptr<BaseModule> simulation_module(
    new Simulation::SimulationModule);
  std::unique_ptr<BaseModule> sensor_module(
    new Simulation::SensorModule);

  ModuleManager manager;
  manager.AddModule(std::move(controls_module));
  manager.AddModule(std::move(guidance_module));
  manager.AddModule(std::move(navigation_module));
  manager.AddModule(std::move(simulation_module));
  manager.AddModule(std::move(sensor_module));

  manager.InitModules();

  manager.StartModules(9);

  return 0;
}
