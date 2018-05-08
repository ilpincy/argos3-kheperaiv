#ifndef REAL_KHEPERAIV_GROUND_SENSOR_H
#define REAL_KHEPERAIV_GROUND_SENSOR_H

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ground_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVGroundSensor :
   public CCI_KheperaIVGroundSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVGroundSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVGroundSensor();

   virtual void Do();
   
};

#endif // REAL_KHEPERAIV_GROUND_SENSOR_H
