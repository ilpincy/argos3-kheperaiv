#include "real_kheperaiv_lidar_sensor.h"

/****************************************/
/****************************************/

/* Device where the LRF is connected: here USB port */
static char  KHEPERAIV_LRF_DEVICE[]    = "/dev/ttyACM0";
static UInt8 KHEPERAIV_POWERON_LASERON = 3;

/****************************************/
/****************************************/

CRealKheperaIVLIDARSensor::CRealKheperaIVLIDARSensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic),
   m_unPowerLaserState(KHEPERAIV_POWERON_LASERON) {
   /* Initialize LIDAR */
   m_nDeviceHandle = kb_lrf_Init(KHEPERAIV_LRF_DEVICE);
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

void CRealKheperaIVLIDARSensor::Do(Real f_elapsed_time) {
   if(m_unPowerLaserState != KHEPERAIV_POWERON_LASERON)
      return;
   kb_lrf_GetDistances(m_nDeviceHandle);
}

/****************************************/
/****************************************/

long CRealKheperaIVLIDARSensor::GetReading(UInt32 un_idx) const {
   return kb_lrf_DistanceData[LRF_DATA_NB - un_idx - 1];
}

/****************************************/
/****************************************/

size_t CRealKheperaIVLIDARSensor::GetNumReadings() const {
   return LRF_DATA_NB;
}

/****************************************/
/****************************************/

void CRealKheperaIVLIDARSensor::PowerOn() {
   m_unPowerLaserState = m_unPowerLaserState | 0x1;
   kb_lrf_Power_On();
}

/****************************************/
/****************************************/

void CRealKheperaIVLIDARSensor::PowerOff() {
   m_unPowerLaserState = m_unPowerLaserState & 0xFE;
   kb_lrf_Power_Off();
}

/****************************************/
/****************************************/

void CRealKheperaIVLIDARSensor::LaserOn() {
   m_unPowerLaserState = m_unPowerLaserState | 0x2;
   kb_lrf_Laser_On(m_nDeviceHandle);
}

/****************************************/
/****************************************/

void CRealKheperaIVLIDARSensor::LaserOff() {
   m_unPowerLaserState = m_unPowerLaserState & 0xFD;
   kb_lrf_Laser_Off(m_nDeviceHandle);
}

/****************************************/
/****************************************/
