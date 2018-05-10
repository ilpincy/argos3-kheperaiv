#include "real_kheperaiv_differential_steering_actuator.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

CRealKheperaIVDifferentialSteeringActuator::CRealKheperaIVDifferentialSteeringActuator(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
   kh4_SetPositionMargin(20, GetDSPic());
   kh4_ConfigurePID(10, 5, 1, GetDSPic());
   kh4_SetSpeedProfile(3, 0, 20, 1, 400, GetDSPic());
   kh4_SetMode(kh4RegSpeedProfile, GetDSPic());
}
   
/****************************************/
/****************************************/

CRealKheperaIVDifferentialSteeringActuator::~CRealKheperaIVDifferentialSteeringActuator() {
   kh4_set_speed(0, 0, GetDSPic());
   kh4_SetMode(kh4RegIdle, GetDSPic());
}
   
/****************************************/
/****************************************/

void CRealKheperaIVDifferentialSteeringActuator::Do() {
   kh4_set_speed(m_fCurrentVelocity[0] / KH4_SPEED_TO_MM_S,
                 m_fCurrentVelocity[1] / KH4_SPEED_TO_MM_S,
                 GetDSPic());
}

/****************************************/
/****************************************/

void CRealKheperaIVDifferentialSteeringActuator::SetLinearVelocity(Real f_left_velocity,
                                                                   Real f_right_velocity) {
   m_fCurrentVelocity[0] = f_left_velocity;
   m_fCurrentVelocity[1] = f_right_velocity;
}

/****************************************/
/****************************************/

