#include "real_kheperaiv_ground_sensor.h"

/****************************************/
/****************************************/

CRealKheperaIVGroundSensor::CRealKheperaIVGroundSensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
}
   
/****************************************/
/****************************************/

CRealKheperaIVGroundSensor::~CRealKheperaIVGroundSensor() {
}

/****************************************/
/****************************************/

#define SETREADING(ARGOSIDX, KH4IDX)                                    \
   m_tReadings[ARGOSIDX].Value = (GetBuffer()[KH4IDX*2] | GetBuffer()[KH4IDX*2+1] << 8) / 65536.0;

void CRealKheperaIVGroundSensor::Do(Real f_elapsed_time) {
   kh4_proximity_ir(GetBuffer(), GetDSPic());
   SETREADING(0, 9);
   SETREADING(1, 8);
   SETREADING(2, 11);
   SETREADING(3, 10);
}

/****************************************/
/****************************************/
