#include "Simulation/simulation_module.h"

void Simulation::SimulationModule::Init(std::shared_ptr<ModuleDataCollection> data) {
  // intialize simulation
  _module_name = "simulation_module";
  _module_period_ms = std::chrono::milliseconds(1);

  // initialize quadcopter
  _quadcopter.Init();
  // get initial states
  _simulation_data.x = _quadcopter.GetStates()["x"];
  _simulation_data.v = _quadcopter.GetStates()["v"];
  _simulation_data.R = _quadcopter.GetStates()["R"].reshaped(3,3);
  _simulation_data.W = _quadcopter.GetStates()["W"];
  _simulation_data.t = 0;

  // initialize sensors
  _gyroscope.Init();

  // set sensor data
  _sensor_data.x = _simulation_data.x;
  _sensor_data.v = _simulation_data.v;
  _sensor_data.R = _simulation_data.R;
  _sensor_data.W = _simulation_data.W;

  // add initial values to shared data
  data->AddModuleData(_simulation_data, "simulation_data");
  data->AddModuleData(_sensor_data, "sensor_data");
}

void Simulation::SimulationModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
 
  // get quadcopter inputs 
  std::map<std::string, VectorXd> quadcopter_inputs;
  quadcopter_inputs["f"] = data->GetModuleData<Onboard::ControlsModuleData>("controls_data").f;
  quadcopter_inputs["M"] = data->GetModuleData<Onboard::ControlsModuleData>("controls_data").M;

  // update states
  _quadcopter.UpdateStates(quadcopter_inputs, _dt_ms/1000);
  _quadcopter.UpdateOutput(quadcopter_inputs);

  // get sensor inputs
  std::map<std::string, VectorXd> sensor_inputs;
  sensor_inputs["W"] = _quadcopter.GetOutput()["W"];

  // update sensor states
  _gyroscope.UpdateStates(sensor_inputs, _dt_ms/1000);
  _gyroscope.UpdateOutput(sensor_inputs);

  // update shared data
  _simulation_data.x = _quadcopter.GetOutput()["x"];
  _simulation_data.v = _quadcopter.GetOutput()["v"];
  _simulation_data.R = _quadcopter.GetOutput()["R"].reshaped(3,3);
  _simulation_data.W = _quadcopter.GetOutput()["W"];
  _simulation_data.vdot = _quadcopter.GetOutput()["vdot"];
  _simulation_data.t += _dt_ms/1000;

  _sensor_data.x = _simulation_data.x;
  _sensor_data.v = _simulation_data.v;
  _sensor_data.R = _simulation_data.R;
  _sensor_data.W = _gyroscope.GetOutput()["W"];
  _sensor_data.t = _simulation_data.t;

  data->SetModuleData(_simulation_data, "simulation_data");
  data->SetModuleData(_sensor_data, "sensor_data");
}

