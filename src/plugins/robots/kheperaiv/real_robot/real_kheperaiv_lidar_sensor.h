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

private:

   int m_nDeviceHandle;

};

#endif // REAL_KHEPERAIV_LIDAR_SENSOR_H
