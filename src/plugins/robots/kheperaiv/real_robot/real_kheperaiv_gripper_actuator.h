#ifndef REAL_KHEPERAIV_GRIPPER_ACTUATOR_H
#define REAL_KHEPERAIV_GRIPPER_ACTUATOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_gripper_actuator.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>

using namespace argos;

class CRealKheperaIVGripperActuator :
   public CCI_GripperActuator,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVGripperActuator(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVGripperActuator();

   virtual void Do(Real f_elapsed_time);
   
private:

   knet_dev_t* m_ptArm;
   knet_dev_t* m_ptGripper;

};

#endif
