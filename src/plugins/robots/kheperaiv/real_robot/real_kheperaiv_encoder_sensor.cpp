#include "real_kheperaiv_encoder_sensor.h"

const Real KHEPERAIV_WHEEL_DISTANCE = 0.1054;

/****************************************/
/****************************************/

CRealKheperaIVEncoderSensor::CRealKheperaIVEncoderSensor(knet_dev_t* pt_dspic) :
  CRealKheperaIVDevice(pt_dspic) {
  m_sReading.VelocityLeftWheel = 0.0;
  m_sReading.VelocityRightWheel = 0.0;
  m_sReading.WheelAxisLength = KHEPERAIV_WHEEL_DISTANCE;
}
   
/****************************************/
/****************************************/

CRealKheperaIVEncoderSensor::~CRealKheperaIVEncoderSensor() {
}

/****************************************/
/****************************************/

#define SETREADING(ARGOSIDX, KH4IDX)                                    \
  m_tReadings[ARGOSIDX].Value = (GetBuffer()[KH4IDX*2] | GetBuffer()[KH4IDX*2+1] << 8) / 65536.0;

void CRealKheperaIVEncoderSensor::Do() {
  int nLeft, nRight;
  kh4_get_position(&nLeft, &nRight, GetDSPic());
  m_sReading.CoveredDistanceLeftWheel = nLeft * KH4_PULSE_TO_MM;
  m_sReading.CoveredDistanceRightWheel = nRight * KH4_PULSE_TO_MM;
}

/****************************************/
/****************************************/
