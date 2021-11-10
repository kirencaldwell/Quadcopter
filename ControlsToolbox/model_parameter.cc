#include "model_parameter.h"
#include "eigen3/unsupported/Eigen/MatrixFunctions"
#include <random>
#include <math.h>

struct NormalRandomVariable 
{
    NormalRandomVariable(Eigen::MatrixXd const& covar)
        : NormalRandomVariable(Eigen::VectorXd::Zero(covar.rows()), covar)
    {}

    NormalRandomVariable(Eigen::VectorXd const& mean, Eigen::MatrixXd const& covar)
        : mean(mean)
    {
        Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigenSolver(covar);
        transform = eigenSolver.eigenvectors() * eigenSolver.eigenvalues().cwiseSqrt().asDiagonal();
    }

    Eigen::VectorXd mean;
    Eigen::MatrixXd transform;

    Eigen::VectorXd operator()() const
    {
        static std::mt19937 gen{ std::random_device{}() };
        static std::normal_distribution<> dist;

        return mean + transform * Eigen::VectorXd{ mean.size() }.unaryExpr([&](auto x) { return dist(gen); });
    }
};

ModelParameter::ModelParameter(double value, double variance, bool monte_carlo_flag) {
    _dvalue = value;
    if (monte_carlo_flag) {
        std::default_random_engine generator;
        std::normal_distribution<double> distribution(value, sqrt(variance)); 
        _dvalue = distribution(generator);
    }
} 

ModelParameter::ModelParameter(VectorXd value, MatrixXd variance, bool monte_carlo_flag) {
    _vvalue = value;
    if (monte_carlo_flag) {
        NormalRandomVariable v{variance};
        _vvalue = value + v();
    }
}
