#include "FEE_Kalman_Filter.h"

void SimpleKalmanFilter(Kalmanfilter *kf, float mea_e, float est_e, float q)
{
    kf->_err_measure=mea_e;
    kf->_err_estimate=est_e;
    kf->_q = q;
}

float updateEstimate(Kalmanfilter *kf, float mea)
{
    kf->_kalman_gain = kf->_err_estimate/(kf->_err_estimate + kf->_err_measure);
    kf->_current_estimate = kf->_last_estimate + kf->_kalman_gain * (mea - kf->_last_estimate);
    kf->_err_estimate =  (1.0 - kf->_kalman_gain)*kf->_err_estimate + fabs(kf->_last_estimate-kf->_current_estimate)*kf->_q;
    kf->_last_estimate=kf->_current_estimate;
    return kf->_current_estimate;
}

void setMeasurementError(Kalmanfilter *kf, float mea_e)
{
    kf->_err_measure = mea_e;
}

void setEstimateError(Kalmanfilter *kf, float est_e)
{
    kf->_err_estimate = est_e;
}

void setProcessNoise(Kalmanfilter *kf, float q)
{
    kf->_q=q;
}

float getKalmanGain(Kalmanfilter *kf) {
    return kf->_kalman_gain;
}

float getEstimateError(Kalmanfilter *kf) {
    return kf->_err_estimate;
}
