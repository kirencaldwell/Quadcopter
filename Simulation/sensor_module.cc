#include "sensor_module.h"
#include <map>
#include <string>
#include <eigen3/Eigen/Dense>

using Eigen::VectorXd;
using Eigen::MatrixXd;

// The outline for this file was autogenerated by create_new_module.py
namespace Simulation {
SensorModule::SensorModule() {
	_module_name = "sensor_module";
    _module_period_ms = std::chrono::milliseconds(1);

	_module_data.Add<VectorXd>("x", VectorXd::Zero(3));
	_module_data.Add<VectorXd>("v", VectorXd::Zero(3));
	_module_data.Add<MatrixXd>("R", MatrixXd::Identity(3,3));
	_module_data.Add<VectorXd>("W", VectorXd::Zero(3));
	_module_data.Add<double>("t", 0);

    // initialize sensors
    _gyroscope.Init();
}

void SensorModule::Poll(std::shared_ptr<ModuleDataCollection> data) {
	VectorXd x = data->GetModuleData("simulation_module").Get<VectorXd>("x");
	VectorXd v = data->GetModuleData("simulation_module").Get<VectorXd>("v");
	MatrixXd R = data->GetModuleData("simulation_module").Get<MatrixXd>("R");
	VectorXd W = data->GetModuleData("simulation_module").Get<VectorXd>("W");
	double t = data->GetModuleData("simulation_module").Get<double>("t");

	std::map<std::string, VectorXd> sensor_inputs;
	sensor_inputs["W"] = W;

    // update sensor states
    _gyroscope.UpdateStates(sensor_inputs, _dt_ms/1000);
    _gyroscope.UpdateOutput(sensor_inputs);

	_module_data.Set<VectorXd>("x", x);
	_module_data.Set<VectorXd>("v", v);
	_module_data.Set<MatrixXd>("R", R);
	_module_data.Set<VectorXd>("W", W);
	_module_data.Set<double>("t", t);
}

}