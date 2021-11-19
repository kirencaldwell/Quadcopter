#ifndef GENERIC_MODEL_H 
#define GENERIC_MODEL_H 

#include <map>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include "model_parameter.h"
#include "named_vector.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

struct LinearModel {
  MatrixXd A;
  MatrixXd B;
  MatrixXd C;
  MatrixXd D;
};

class GenericModel {
  public:
    virtual void Init(bool monte_carlo_flag);

    void Propagate(NamedVector input, double dt);
    void PropagateWithNoise(NamedVector input, double dt);

    // Getters
    ModelParameter GetParameters() {return _parameters;};
    NamedVector GetOutput();
    NamedVector GetStates();
    MatrixXd GetModelCovariance() {return _Q;};
    MatrixXd GetMeasurementCovariance() {return _R;};

    // TODO: kirencaldwell - implement this
    LinearModel GetLinearModel(
        NamedVector x, NamedVector u);
    virtual NamedVector ComputeDerivative(NamedVector x, NamedVector u);
    virtual NamedVector ComputeMeasurement(NamedVector x, 
        NamedVector u);

  protected:
    // add parameters
    void AddParameter(std::string name, double value, double covariance, bool mc_flag);
    void AddParameter(std::string name, VectorXd value, MatrixXd covariance, bool mc_flag);

    // Set model and measurement covariances    
    void SetModelCovariance(MatrixXd Q) {_Q = Q;};
    void SetMeasurementCovariance(MatrixXd R) {_R = R;};

    // integrate ode by time step
    virtual void IntegrateOde(NamedVector input, double dt);
    // update output
    void UpdateOutput(NamedVector input);

    NamedVector AddNoise(NamedVector x, MatrixXd P);

    // container of parameters
    ModelParameter _parameters;
    // states and output variables
    NamedVector _states;
    NamedVector _output;

    // noise covariances
    MatrixXd _Q;
    MatrixXd _R;
};




#endif
