#ifndef MODEL_PARAMETER_H
#define MODEL_PARAMETER_H

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <any>

using Eigen::VectorXd;
using Eigen::MatrixXd;

class ModelParameter {
    public:
        ModelParameter() {};
        ModelParameter(double value, double variance, bool monte_carlo_flag);
        ModelParameter(VectorXd value, MatrixXd variance, bool monte_carlo_flag);

        double GetScalar() {return _dvalue;};
        VectorXd GetVector() {return _vvalue;};

    protected:
        double _dvalue;
        double _dvariance;
        VectorXd _vvalue;
        MatrixXd _vvariance;
};

#endif