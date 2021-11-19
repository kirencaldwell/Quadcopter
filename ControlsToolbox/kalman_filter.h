#include <eigen3/Eigen/Dense>
#include <map>
#include <string>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class KalmanFilter {
    public:
        KalmanFilter(VectorXd x0, MatrixXd P0, GenericOdeModel model);

        VectorXd GetState();
        MatrixXd GetCovariance();
        VectorXd GetResiduals();

        void UpdateState(std::map<std::string, VectorXd> u, double dt);
        virtual void ApplyMeasurement();
    
    private:
        VectorXd GetPredictedMeasurememnt(
            std::map<std::string, GenericOdeModel*> sensors);
    protected:
        std::map<std::string, VectorXd> _x;
        MatrixXd _P
        GenericOdeModel _model;
        std::map<std::string, VectorXd> _r;
}