#include "telemetry_logging_module.h"

void Onboard::TelemetryLoggingModule::Init(std::shared_ptr<ModuleDataCollection> data) {
  _module_name = "telemetry_logging_module";
  _module_period_ms = std::chrono::milliseconds(10);

  _tlm.OpenFile("quadcopter_onboard.csv");
  _tlm.AddSignal("t", &_t);
  _tlm.AddSignal("x", &_x);
  _tlm.AddSignal("v", &_v);
  _tlm.AddSignal("R", &_R);
  _tlm.AddSignal("W", &_W);
  _tlm.AddSignal("M", &_M);
  _tlm.AddSignal("Rd", &_Rd);

  _tlm.CreateLogHeader();
}

Onboard::TelemetryLoggingModule::~TelemetryLoggingModule() {
  _tlm.EndLogging();
}

void Onboard::TelemetryLoggingModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
  _t = data->GetModuleData<SensorModuleData>("sensor_data").t;
  _x = data->GetModuleData<SensorModuleData>("sensor_data").x;
  _v = data->GetModuleData<SensorModuleData>("sensor_data").v;
  _R = data->GetModuleData<SensorModuleData>("sensor_data").R.reshaped(3,3);
  _W = data->GetModuleData<SensorModuleData>("sensor_data").W;

  _M = data->GetModuleData<ControlsModuleData>("controls_data").M;

  _tlm.LogSignals();

}

  
