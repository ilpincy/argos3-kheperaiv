#ifndef REAL_KHEPERAIV_H
#define REAL_KHEPERAIV_H

#include <argos3/core/real_robot/real_robot.h>

using namespace argos;

class CRealKheperaIV : public CRealRobot {

public:

   CRealKheperaIV(const std::string& str_conf_fname,
                  const std::string& str_controller_id);
   virtual ~CRealKheperaIV();
   virtual void Init();
   virtual void Destroy();
   virtual CCI_Actuator* MakeActuator(const std::string& str_name);
   virtual CCI_Sensor* MakeSensor(const std::string& str_name);
   virtual void Sense();
   virtual void Control();
   virtual void Act();

};

#endif // REAL_KHEPERAIV_H
