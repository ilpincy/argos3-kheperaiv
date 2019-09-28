#ifndef REAL_KHEPERAIV_H
#define REAL_KHEPERAIV_H

#include <argos3/core/real_robot/real_robot.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>
#include <khepera/khepera.h>

using namespace argos;

class CRealKheperaIV : public CRealRobot {

public:

   CRealKheperaIV();
   virtual ~CRealKheperaIV();
   virtual void InitRobot();
   virtual void Destroy();
   virtual CCI_Actuator* MakeActuator(const std::string& str_name);
   virtual CCI_Sensor* MakeSensor(const std::string& str_name);
   virtual void Sense(Real f_elapsed_time);
   virtual void Act(Real f_elapsed_time);

   inline knet_dev_t* GetDSPic() const {
      return m_ptDSPic;
   }

private:

   knet_dev_t* m_ptDSPic;
   std::vector<CRealKheperaIVDevice*> m_vecActuators;
   std::vector<CRealKheperaIVDevice*> m_vecSensors;
};

#endif // REAL_KHEPERAIV_H
