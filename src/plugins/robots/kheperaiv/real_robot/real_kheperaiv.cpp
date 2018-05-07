#include "real_kheperaiv.h"

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
}

/****************************************/
/****************************************/

void CRealKheperaIV::Destroy() {
}

/****************************************/
/****************************************/

CCI_Actuator* CRealKheperaIV::MakeActuator(const std::string& str_name) {
   return NULL;
}

/****************************************/
/****************************************/

CCI_Sensor* CRealKheperaIV::MakeSensor(const std::string& str_name) {
   return NULL;
}

/****************************************/
/****************************************/

void CRealKheperaIV::Sense() {
}

/****************************************/
/****************************************/

void CRealKheperaIV::Control() {
}

/****************************************/
/****************************************/

void CRealKheperaIV::Act() {
}

/****************************************/
/****************************************/

