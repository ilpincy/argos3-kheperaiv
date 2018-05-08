#include "real_kheperaiv.h"
#include "real_kheperaiv_differential_steering_actuator.h"
#include "real_kheperaiv_leds_actuator.h"
#include "real_kheperaiv_battery_sensor.h"
#include "real_kheperaiv_ground_sensor.h"
#include "real_kheperaiv_proximity_sensor.h"
#include "real_kheperaiv_ultrasound_sensor.h"

/****************************************/
/****************************************/

CRealKheperaIV::CRealKheperaIV(const std::string& str_conf_fname,
                               const std::string& str_controller_id) :
   CRealRobot(str_conf_fname,
              str_controller_id) {
}

/****************************************/
/****************************************/

CRealKheperaIV::~CRealKheperaIV() {
}

/****************************************/
/****************************************/

void CRealKheperaIV::Init() {
   /* Initialize Khepera */
   if(kh4_init(0,NULL) != 0) {
      THROW_ARGOSEXCEPTION("Error initializing the Khepera IV subsystem (kh4_init)");
   }
   /* Open robot socket and store the handle in its pointer */
   m_ptDSPic = knet_open("Khepera4:dsPic", KNET_BUS_I2C, 0, NULL);
   if(m_ptDSPic == NULL) {
      THROW_ARGOSEXCEPTION("Error initializing communication with Khepera IV dsPic (knet_open)");
   }	
}

/****************************************/
/****************************************/

void CRealKheperaIV::Destroy() {
}

/****************************************/
/****************************************/

#define MAKE_ACTUATOR(CLASSNAME, TAG)           \
   if(str_name == TAG) {                        \
      CLASSNAME* pcAct =                        \
         new CLASSNAME(GetDSPic());             \
      m_vecActuators.push_back(pcAct);          \
      m_pcController->AddActuator(TAG, pcAct);  \
      return pcAct;                             \
   }

CCI_Actuator* CRealKheperaIV::MakeActuator(const std::string& str_name) {
   MAKE_ACTUATOR(CRealKheperaIVDifferentialSteeringActuator,
                 "differential_steering");
   MAKE_ACTUATOR(CRealKheperaIVLEDsActuator,
                 "leds");
   return NULL;
}

/****************************************/
/****************************************/

#define MAKE_SENSOR(CLASSNAME, TAG)             \
   if(str_name == TAG) {                        \
      CLASSNAME* pcSens =                       \
         new CLASSNAME(GetDSPic());             \
      m_vecSensors.push_back(pcSens);           \
      m_pcController->AddSensor(TAG, pcSens);   \
      return pcSens;                            \
   }

CCI_Sensor* CRealKheperaIV::MakeSensor(const std::string& str_name) {
   MAKE_SENSOR(CRealKheperaIVBatterySensor,
               "kheperaiv_battery");
   MAKE_SENSOR(CRealKheperaIVGroundSensor,
               "kheperaiv_ground");
   MAKE_SENSOR(CRealKheperaIVProximitySensor,
               "kheperaiv_proximity");
   MAKE_SENSOR(CRealKheperaIVUltrasoundSensor,
               "kheperaiv_ultrasound");
   return NULL;
}

/****************************************/
/****************************************/

void CRealKheperaIV::Sense() {
   for(size_t i = 0; i < m_vecSensors.size(); ++i) {
      m_vecSensors[i]->Do();
   }
}

/****************************************/
/****************************************/

void CRealKheperaIV::Act() {
   for(size_t i = 0; i < m_vecActuators.size(); ++i) {
      m_vecActuators[i]->Do();
   }
}

/****************************************/
/****************************************/
