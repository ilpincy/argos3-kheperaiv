#ifndef REAL_KHEPERAIV_PROXIMITY_SENSOR_H
#define REAL_KHEPERAIV_PROXIMITY_SENSOR_H

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_proximity_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVProximitySensor :
   public CCI_KheperaIVProximitySensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVProximitySensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVProximitySensor();

   virtual void Do(Real f_elapsed_time);

};

#endif // REAL_KHEPERAIV_PROXIMITY_SENSOR_H
