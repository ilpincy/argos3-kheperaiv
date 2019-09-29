#ifndef REAL_KHEPERAIV_ENCODER_SENSOR_H
#define REAL_KHEPERAIV_ENCODER_SENSOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_differential_steering_device.h>

using namespace argos;

class CRealKheperaIVEncoderSensor :
   public CCI_DifferentialSteeringSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVEncoderSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVEncoderSensor();

   virtual void Do(Real f_elapsed_time);

private:

   int m_nEncoderLeft;
   int m_nEncoderRight;
   CRealKheperaIVDifferentialSteeringDevice* m_pcDevice;

};

#endif // REAL_KHEPERAIV_ENCODER_SENSOR_H
