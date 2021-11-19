#include "model_parameter.h"
#include <random>
#include <math.h>
#include "Utilities/math.h"


void ModelParameter::AddParameter(std::string name, double value, double variance, bool monte_carlo_flag) {
    if (monte_carlo_flag) {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(value, sqrt(variance)); 
        Add(name, distribution(generator));
        return;
    }
    Add(name, value);
} 

void ModelParameter::AddParameter(std::string name, VectorXd value, MatrixXd variance, bool monte_carlo_flag) {
    if (monte_carlo_flag) {
        Utilities::Math::NormalRandomVariable v{variance};
        Add(name, value);
        return;
    }
    Add(name, value);
}
