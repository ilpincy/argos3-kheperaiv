#ifndef REAL_KHEPERAIV_LIDAR_SENSOR_H
#define REAL_KHEPERAIV_LIDAR_SENSOR_H

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_lidar_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVLIDARSensor :
   public CCI_KheperaIVLIDARSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVLIDARSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVLIDARSensor();

   virtual void Do();

   virtual long GetReading(UInt32 un_idx) const;

   virtual size_t GetNumReadings() const;

   virtual void PowerOn();
   
   virtual void PowerOff();

   virtual void LaserOn();

   virtual void LaserOff();
   
private:

   /** LIDAR board handle */
   int m_nDeviceHandle;

   /** Power and Laser states */
   UInt8 m_unPowerLaserState;

};

#endif // REAL_KHEPERAIV_LIDAR_SENSOR_H
