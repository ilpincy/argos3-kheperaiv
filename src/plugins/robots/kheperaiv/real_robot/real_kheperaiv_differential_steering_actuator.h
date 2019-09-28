#ifndef REAL_KHEPERAIV_DIFFERENTIAL_STEERING_ACTUATOR_H
#define REAL_KHEPERAIV_DIFFERENTIAL_STEERING_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_differential_steering_actuator.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_differential_steering_device.h>

using namespace argos;

class CRealKheperaIVDifferentialSteeringActuator :
   public CCI_DifferentialSteeringActuator,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVDifferentialSteeringActuator(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVDifferentialSteeringActuator();

   virtual void Do(Real f_elapsed_time);
   
   virtual void SetLinearVelocity(Real f_left_velocity,
                                  Real f_right_velocity);

private:

  CRealKheperaIVDifferentialSteeringDevice* m_pcDevice;
};

#endif
