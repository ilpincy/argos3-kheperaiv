#ifndef REAL_KHEPERAIV_DIFFERENTIAL_STEERING_DEVICE_H
#define REAL_KHEPERAIV_DIFFERENTIAL_STEERING_DEVICE_H

#include <argos3/core/utility/datatypes/datatypes.h>

using namespace argos;

class CRealKheperaIVDifferentialSteeringDevice {

public:

  static CRealKheperaIVDifferentialSteeringDevice* GetInstance();

  ~CRealKheperaIVDifferentialSteeringDevice() {}

  inline void SetVelocity(Real* f_velocity) {
    m_fVelocityLeft = f_velocity[0];
    m_fVelocityRight = f_velocity[1];
  }

  inline Real GetVelocityLeft() const {
    return m_fVelocityLeft;
  }

  inline Real GetVelocityRight() const {
    return m_fVelocityRight;
  }

private:

  CRealKheperaIVDifferentialSteeringDevice();
   
private:

  static CRealKheperaIVDifferentialSteeringDevice* m_pcInstance;
  Real m_fVelocityLeft;
  Real m_fVelocityRight;
};

#endif
