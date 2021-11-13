#include "Simulation/simulation_module.h"

#include <eigen3/Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace Simulation {
SimulationModule::SimulationModule() {
  _module_name = "simulation_module";
  _module_period_ms = std::chrono::milliseconds(1);

  // initialize quadcopter
  _quadcopter.Init();
  // get initial states
  _module_data.Add<VectorXd>("x", VectorXd::Zero(3));
  _module_data.Add<VectorXd>("v", VectorXd::Zero(3));
  _module_data.Add<MatrixXd>("R", MatrixXd::Identity(3,3));
  _module_data.Add<VectorXd>("W", VectorXd::Zero(3));
  _module_data.Add<VectorXd>("vdot", VectorXd::Zero(3));
  _module_data.Add<double>("t", 0);


}

void Simulation::SimulationModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
 
  // get quadcopter inputs 
  std::map<std::string, VectorXd> quadcopter_inputs;
  quadcopter_inputs["f"] = data->GetModuleData("controls_module").Get<VectorXd>("f");
  quadcopter_inputs["M"] = data->GetModuleData("controls_module").Get<VectorXd>("M");

  // update states
  _quadcopter.UpdateStates(quadcopter_inputs, _dt_ms/1000);
  _quadcopter.UpdateOutput(quadcopter_inputs);

  // update shared data
  VectorXd Rv = _quadcopter.GetOutput()["R"];
  MatrixXd R = Rv.reshaped(3,3);
  _module_data.Set<VectorXd>("x", _quadcopter.GetOutput()["x"]);
  _module_data.Set<VectorXd>("v", _quadcopter.GetOutput()["v"]);
  _module_data.Set<MatrixXd>("R", R);
  _module_data.Set<VectorXd>("W", _quadcopter.GetOutput()["W"]);
  _module_data.Set<VectorXd>("vdot", _quadcopter.GetOutput()["vdot"]);
  _module_data.Set<double>("t", _module_data.Get<double>("t")+_dt_ms/1000);

}
}
