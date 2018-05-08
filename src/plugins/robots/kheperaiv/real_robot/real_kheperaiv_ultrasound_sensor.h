#ifndef REAL_KHEPERAIV_ULTRASOUND_SENSOR_H
#define REAL_KHEPERAIV_ULTRASOUND_SENSOR_H

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ultrasound_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVUltrasoundSensor :
   public CCI_KheperaIVUltrasoundSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVUltrasoundSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVUltrasoundSensor();

   virtual void Do();

};

#endif // REAL_KHEPERAIV_ULTRASOUND_SENSOR_H
