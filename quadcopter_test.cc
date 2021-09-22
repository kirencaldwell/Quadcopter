#include <iostream>
#include <eigen3/Eigen/Dense>
#include <memory>
#include <math.h>

#include "external/ConcurrentModuleFramework/src/base_module.h"
#include "external/ConcurrentModuleFramework/src/module_manager.h"
#include "external/ConcurrentModuleFramework/src/telemetry_logging.h"
#include "Onboard/controller.h"
#include "Onboard/controls_module.h"
#include "Onboard/sensor_module.h"
#include "Simulation/simulation_module.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

int main() {
    std::cout.flush();

    TelemetryLogging tlm;
    tlm.OpenFile("quadcopter_test.csv");

    double t = 0;
    double dt = 0.001;
    double Tf = 10;
    tlm.AddSignal("t", &t);

    VectorXd xd(3);
    xd << 10, 0, 0;
    VectorXd b1d(3);
    b1d << 1, 0, 0;
    b1d.normalized();

    Simulation::QuadcopterModel quadcopter;
    quadcopter.Init();
    VectorXd x(3), W(3);
    MatrixXd R(3,3);
    tlm.AddSignal("x", &x);
    tlm.AddSignal("W", &W);
    tlm.AddSignal("R", &R);

    Onboard::Controller controller;
    controller.Init();
    VectorXd f(1);
    VectorXd M(3);
    MatrixXd Rd(3,3);
    VectorXd A(3);
    tlm.AddSignal("f", &f);
    tlm.AddSignal("M", &M);
    tlm.AddSignal("Rd", &Rd);
    tlm.AddSignal("A", &A);

    std::map<std::string, VectorXd> controller_inputs;
    std::map<std::string, VectorXd> u;
    std::map<std::string, VectorXd> states;
    tlm.CreateLogHeader();
    while (t <= Tf) {            
        std::cout << "t = " << t << std::endl;
        tlm.LogSignals();
        states = quadcopter.GetStates();
        x = states["x"];
        R = states["R"].reshaped(3,3);
        W = states["W"];


        xd << 10*cos(2*M_PI*0.1*t), 10*sin(2*M_PI*0.1*t), -5;

        controller_inputs["x"] = states["x"];
        controller_inputs["v"] = states["v"];
        controller_inputs["R"] = states["R"];
        controller_inputs["W"] = states["W"];
        controller_inputs["xd"] = xd;
        controller_inputs["b1d"] = b1d;

        controller.UpdateOutput(controller_inputs);
        u = controller.GetOutput();
        f = u["f"];
        M = u["M"];
        Rd = u["Rd"].reshaped(3,3);
        A = u["A"];

        quadcopter.UpdateStates(u, dt);
        t += dt;
    }
    tlm.EndLogging();
    return 0;
}
