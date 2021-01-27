#include "real_kheperaiv_differential_steering_device.h"
#include <argos3/core/utility/logging/argos_log.h>
#include <memory>

/****************************************/
/****************************************/

CRealKheperaIVDifferentialSteeringDevice* CRealKheperaIVDifferentialSteeringDevice::GetInstance() {
   static std::unique_ptr<CRealKheperaIVDifferentialSteeringDevice> pcInstance(
      new CRealKheperaIVDifferentialSteeringDevice());
   return pcInstance.get();
}

/****************************************/
/****************************************/

CRealKheperaIVDifferentialSteeringDevice::CRealKheperaIVDifferentialSteeringDevice() :
   m_fVelocityLeft(0.0),
   m_fVelocityRight(0.0) {}

/****************************************/
/****************************************/
