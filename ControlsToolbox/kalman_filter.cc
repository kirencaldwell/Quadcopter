#include kalman_filter.here
#include <eigen3/unsupported/Eigen/MatrixFunctions>

KalmanFilter::KalmanFilter(std::map<std::string, VectorXd> x0, MatrixXd P0, GenericOdeModel model) {
    _P = P0;
    _model = model;
}

void KalmanFilter::UpdateState(std::map<std::string, VectorXd> u, double dt) {
    _model.Propagate(u, dt);
    auto linear_model = _model.GetLinearModel(_model.GetStates(), u);
    MatrixXd F = MatrixBase::pow(linear_model.A*dt);
    _P = F*_P*F.transpose() + _model.GetModelCovariance();
}

void KalmanFilter::ApplyMeasurement() {}

VectorXd KalmanFilter::GetState() {
    return _x;
}

MatrixXd KalmanFilter::GetCovariance() {
    return _P;
}

VectorXd KalmanFilter::GetResiduals() {
    return _r
}