#include "real_kheperaiv_gripper_actuator.h"

/****************************************/
/****************************************/

CRealKheperaIVGripperActuator::CRealKheperaIVGripperActuator(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
   /* Initialize gripper */
   kgripper_init();
   /* Open sockets to gripper components */
   m_ptArm = knet_open( "Kgripper:Arm", KNET_BUS_I2C, 0, NULL);
   if(m_ptArm == NULL) {
      THROW_ARGOSEXCEPTION("Can't connect to Khepera IV arm");
   }
   m_ptGripper = knet_open( "Kgripper:Gripper", KNET_BUS_I2C, 0, NULL);
   if(m_ptArm == NULL) {
      THROW_ARGOSEXCEPTION("Can't connect to Khepera IV gripper");
   }
}
   
/****************************************/
/****************************************/

CRealKheperaIVGripperActuator::~CRealKheperaIVGripperActuator() {
}
   
/****************************************/
/****************************************/

void CRealKheperaIVGripperActuator::Do() {
}

/****************************************/
/****************************************/
