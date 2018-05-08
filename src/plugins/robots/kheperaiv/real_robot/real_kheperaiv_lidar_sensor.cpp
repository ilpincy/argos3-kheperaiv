#include "real_kheperaiv_lidar_sensor.h"

/****************************************/
/****************************************/

/* Device where the LRF is connected: here USB port */
#define LRF_DEVICE "/dev/ttyACM0"

/****************************************/
/****************************************/

CRealKheperaIVLIDARSensor::CRealKheperaIVLIDARSensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
   /* Resize readings vector */
   m_tReadings.resize(LRF_DATA_NB);
   /* Activate the power supply battery module */
   kb_lrf_Power_On();
   /* Initialize LIDAR */
   m_nDeviceHandle = kb_lrf_Init(LRF_DEVICE);
   if(m_nDeviceHandle < 0) {
      kb_lrf_Power_Off();
      THROW_ARGOSEXCEPTION("Can't initialize LIDAR");
   }
   if(kb_lrf_GetDistances(m_nDeviceHandle) < 0) {
      kb_lrf_Close(m_nDeviceHandle);
      kb_lrf_Power_Off();
      THROW_ARGOSEXCEPTION("Can't get distance readings from LIDAR");
   }
}

/****************************************/
/****************************************/

CRealKheperaIVLIDARSensor::~CRealKheperaIVLIDARSensor() {
   kb_lrf_Close(m_nDeviceHandle);
   kb_lrf_Power_Off();
}

/****************************************/
/****************************************/

void CRealKheperaIVLIDARSensor::Do() {
   kb_lrf_GetDistances(m_nDeviceHandle);
   for(size_t i = 0; i < LRF_DATA_NB; ++i) {
      m_tReadings[i] = kb_lrf_DistanceData[LRF_DATA_NB - i - 1];
   }
}

/****************************************/
/****************************************/
