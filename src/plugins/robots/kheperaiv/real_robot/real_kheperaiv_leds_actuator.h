#ifndef REAL_KHEPERAIV_LEDS_ACTUATOR_H
#define REAL_KHEPERAIV_LEDS_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_leds_actuator.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVLEDsActuator :
   public CCI_LEDsActuator,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVLEDsActuator(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVLEDsActuator();

   virtual void Do();
   
};

#endif
