#include "controls_module.h"
#include <math.h>

void Onboard::ControlsModule::Init(std::shared_ptr<ModuleDataCollection> data) {
  _module_name = "controls_module";
  _module_period_ms = std::chrono::milliseconds(1);
 
  _controller.Init(); 
  _controls_data.f = VectorXd::Zero(1);
  _controls_data.M = VectorXd::Zero(3);

  data->AddModuleData(_controls_data, "controls_data");
}

void Onboard::ControlsModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
  VectorXd x = data->GetModuleData<SensorModuleData>("sensor_data").x;
  VectorXd v = data->GetModuleData<SensorModuleData>("sensor_data").v;
  MatrixXd R = data->GetModuleData<SensorModuleData>("sensor_data").R;
  VectorXd W = data->GetModuleData<SensorModuleData>("sensor_data").W;
  double t = data->GetModuleData<SensorModuleData>("sensor_data").t;
  

  VectorXd xd(3);
  xd << 10*cos(2*M_PI*0.1*t), 10*sin(2*M_PI*0.1*t), -10;

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
  _controls_data.f = controller_output["f"];
  _controls_data.M = controller_output["M"];

  data->SetModuleData(_controls_data, "controls_data");
}

  
