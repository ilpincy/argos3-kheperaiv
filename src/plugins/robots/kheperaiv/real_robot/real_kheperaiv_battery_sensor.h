#ifndef REAL_KHEPERAIV_BATTERY_SENSOR_H
#define REAL_KHEPERAIV_BATTERY_SENSOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_battery_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVBatterySensor :
   public CCI_BatterySensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVBatterySensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVBatterySensor();

   virtual void Do(Real f_elapsed_time);
   
};

#endif // REAL_KHEPERAIV_BATTERY_SENSOR_H
