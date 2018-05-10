#include "real_kheperaiv_differential_steering_actuator.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

static int KHEPERAIV_POSITIONMARGIN             = 20;
static int KHEPERAIV_PID_P                      = 10;
static int KHEPERAIV_PID_I                      = 5;
static int KHEPERAIV_PID_D                      = 1;
static int KHEPERAIV_SPEEDPROFILE_ACC_INC       = 3;
static int KHEPERAIV_SPEEDPROFILE_ACC_DIV       = 0;
static int KHEPERAIV_SPEEDPROFILE_MIN_SPEED_ACC = 20;
static int KHEPERAIV_SPEEDPROFILE_MIN_SPEED_DEC = 1;
static int KHEPERAIV_SPEEDPROFILE_MAX_SPEED     = 400;

/****************************************/
/****************************************/

CRealKheperaIVDifferentialSteeringActuator::CRealKheperaIVDifferentialSteeringActuator(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
   LOG << "[INFO] Differential Steering actuator parameters:" << std::endl;
   kh4_SetPositionMargin(KHEPERAIV_POSITIONMARGIN, GetDSPic());
   LOG << "[INFO]   Position Margin = "
       << KHEPERAIV_POSITIONMARGIN
       << std::endl;
   kh4_ConfigurePID(KHEPERAIV_PID_P,
                    KHEPERAIV_PID_I,
                    KHEPERAIV_PID_D, GetDSPic());
   LOG << "[INFO]   PID factors = <"
       << KHEPERAIV_PID_P << ", "
       << KHEPERAIV_PID_I << ", "
       << KHEPERAIV_PID_D << ">"
       << std::endl;
   kh4_SetSpeedProfile(KHEPERAIV_SPEEDPROFILE_ACC_INC,
                       KHEPERAIV_SPEEDPROFILE_ACC_DIV,
                       KHEPERAIV_SPEEDPROFILE_MIN_SPEED_ACC,
                       KHEPERAIV_SPEEDPROFILE_MIN_SPEED_DEC,
                       KHEPERAIV_SPEEDPROFILE_MAX_SPEED,
                       GetDSPic());
   LOG << "[INFO]   Speed profile = <"
       << "acc_inc = "       << KHEPERAIV_SPEEDPROFILE_ACC_INC << ", "
       << "acc_div = "       << KHEPERAIV_SPEEDPROFILE_ACC_DIV << ", "
       << "min_speed_acc = " << KHEPERAIV_SPEEDPROFILE_MIN_SPEED_ACC << ", "
       << "min_speed_dec = " << KHEPERAIV_SPEEDPROFILE_MIN_SPEED_DEC << ", "
       << "max_speed = "     << KHEPERAIV_SPEEDPROFILE_MAX_SPEED << ">"
       << std::endl;
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

