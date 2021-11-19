#ifndef MODEL_PARAMETER_H
#define MODEL_PARAMETER_H

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <string>
#include "named_vector.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;

class ModelParameter : public NamedVector {
    public:
        // ModelParameter();
        void AddParameter(std::string name, double value, double variance, bool monte_carlo_flag);
        void AddParameter(std::string name, VectorXd value, MatrixXd variance, bool monte_carlo_flag);

};

#endif