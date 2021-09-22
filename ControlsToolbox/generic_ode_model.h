#ifndef GENERIC_ODE_MODEL_H 
#define GENERIC_ODE_MODEL_H 

#include <map>
#include <eigen3/Eigen/Dense>
#include <iostream>

using Eigen::VectorXd;
using Eigen::MatrixXd;


class GenericOdeModel {
  public:
    virtual void Init();

    virtual void UpdateStates(std::map<std::string, VectorXd> input, double dt);
    void UpdateOutput(std::map<std::string, VectorXd> input);
    std::map<std::string, VectorXd> GetOutput();
    std::map<std::string, VectorXd> GetStates();
    // TODO: kirencaldwell - implement this
    std::map<std::string, MatrixXd> GetLinearizeModel(
        std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u);
  protected:
    virtual std::map<std::string, VectorXd> StateOde(
            std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u);
    virtual std::map<std::string, VectorXd> MeasurementFunction(
            std::map<std::string, VectorXd> x, std::map<std::string, VectorXd> u);

    std::map<std::string, VectorXd> _states;
    std::map<std::string, VectorXd> _output;
};




#endif
