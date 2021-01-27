#include "real_kheperaiv_encoder_sensor.h"
#include <argos3/core/utility/math/general.h>

const Real KHEPERAIV_WHEEL_DISTANCE = 0.1054;
const int  KHEPERAIV_ENCODER_MAX = 19456; // how many ticks in a full rotation
const Real KHEPERAIV_ENCODER_PULSE_TO_CM = KH4_PULSE_TO_MM / 10.0f;

/****************************************/
/****************************************/

CRealKheperaIVEncoderSensor::CRealKheperaIVEncoderSensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(pt_dspic) {
   /* Set the axis length */
   m_sReading.WheelAxisLength = KHEPERAIV_WHEEL_DISTANCE;
   /* Get initial tick values (i.e., initial wheel rotation) */
   kh4_get_position(&m_nEncoderLeft, &m_nEncoderRight, GetDSPic());
   /* Get data structure common to differential steering (for steering) */
   m_pcDevice = CRealKheperaIVDifferentialSteeringDevice::GetInstance();
}

/****************************************/
/****************************************/

CRealKheperaIVEncoderSensor::~CRealKheperaIVEncoderSensor() {
}

/****************************************/
/****************************************/

void CRealKheperaIVEncoderSensor::Do(Real f_elapsed_time) {
   /*
    * The encoder gives us the current rotation of the wheels (in ticks)
    * To know the distance covered, we consider the difference between the old rotation and the new rotation (in ticks)
    * In calculating the difference, we need to mind the fact that the sign of the velocity matters!
    * The calculated difference is then reported to modulo KHEPERAIV_ENCODER_MAX
    * And finally converted to cm (as expected by ARGoS)
    */
   /* Get current rotation in ticks */
   int nCurLeft, nCurRight;
   int nDiffLeft, nDiffRight;
   kh4_get_position(&nCurLeft, &nCurRight, GetDSPic());
   /* Calculate difference with value */
   nDiffLeft =
      (Sign(m_pcDevice->GetVelocityLeft()) *
       (nCurLeft - m_nEncoderLeft))
      % KHEPERAIV_ENCODER_MAX;
   nDiffRight =
      (Sign(m_pcDevice->GetVelocityRight()) *
       (nCurRight - m_nEncoderRight))
      % KHEPERAIV_ENCODER_MAX;
   /* Save current values for future loops */
   m_nEncoderLeft = nCurLeft;
   m_nEncoderRight = nCurRight;
   /* Convert this to cm to get the final readings */
   m_sReading.CoveredDistanceLeftWheel =
      nDiffLeft * KHEPERAIV_ENCODER_PULSE_TO_CM;
   m_sReading.CoveredDistanceRightWheel =
      nDiffRight * KHEPERAIV_ENCODER_PULSE_TO_CM;
   m_sReading.VelocityLeftWheel =
      Sign(m_pcDevice->GetVelocityLeft()) *
      m_sReading.CoveredDistanceLeftWheel /
      f_elapsed_time;
   m_sReading.VelocityRightWheel =
      Sign(m_pcDevice->GetVelocityRight()) *
      m_sReading.CoveredDistanceRightWheel /
      f_elapsed_time;
}

/****************************************/
/****************************************/
