#include "real_kheperaiv_battery_sensor.h"

/****************************************/
/****************************************/

CRealKheperaIVBatterySensor::CRealKheperaIVBatterySensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealKheperaIVBatterySensor::~CRealKheperaIVBatterySensor() {
}

/****************************************/
/****************************************/

void CRealKheperaIVBatterySensor::Do(Real f_elapsed_time) {
   kh4_battery_status(GetBuffer(), GetDSPic());
   m_sReading.AvailableCharge = GetBuffer()[3] / 100.0;
   m_sReading.TimeLeft = -1.0; // TODO
}

/****************************************/
/****************************************/
