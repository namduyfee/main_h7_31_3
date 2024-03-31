 #ifndef KALMAN_H_
 #define KALMAN_H_
#include "stdint.h"
#include "math.h"

typedef struct 
{
    float _err_measure;
    float _err_estimate;
    float _q;
    
    float _current_estimate;
    float _last_estimate;
    float _kalman_gain;
}Kalmanfilter;

 // class SimpleKalmanFilter
    void SimpleKalmanFilter(Kalmanfilter *kf, float mea_e, float est_e, float q);
    float updateEstimate(Kalmanfilter *kf, float mea);
    void setMeasurementError(Kalmanfilter *kf, float mea_e);
    void setEstimateError(Kalmanfilter *kf, float est_e);
    void setProcessNoise(Kalmanfilter *kf, float q);
    float getKalmanGain(Kalmanfilter *kf);
    float getEstimateError(Kalmanfilter *kf);
 #endif
