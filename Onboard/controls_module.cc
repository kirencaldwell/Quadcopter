#include "controls_module.h"

#include <eigen3/Eigen/Dense>
#include <map>
#include <math.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

namespace Onboard {
ControlsModule::ControlsModule() {
  _module_name = "controls_module";
  _module_period_ms = std::chrono::milliseconds(1);
 
  _controller.Init(); 
  _module_data.Add<VectorXd>("f", VectorXd::Zero(1));
  _module_data.Add<VectorXd>("M", VectorXd::Zero(3));

}

void ControlsModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
  VectorXd x = data->GetModuleData("navigation_module").Get<VectorXd>("x");
  VectorXd v = data->GetModuleData("navigation_module").Get<VectorXd>("v");
  MatrixXd R = data->GetModuleData("navigation_module").Get<MatrixXd>("R");
  VectorXd W = data->GetModuleData("navigation_module").Get<VectorXd>("W");
  VectorXd xd = data->GetModuleData("guidance_module").Get<VectorXd>("xd");

  std::map<std::string, VectorXd> controller_inputs;
  controller_inputs["x"] = x;
  controller_inputs["v"] = v;
  controller_inputs["x"] = x;
  controller_inputs["R"] = R.reshaped(9,1);
  controller_inputs["W"] = W;
  controller_inputs["xd"] = xd;
  controller_inputs["b1d"] = xd;

  _controller.UpdateOutput(controller_inputs);
  auto controller_output = _controller.GetOutput();
  _module_data.Set<VectorXd>("f", controller_output["f"]);
  _module_data.Set<VectorXd>("M", controller_output["M"]);

}
}
  
