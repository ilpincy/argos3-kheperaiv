/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_proximity_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include "kheperaiv_proximity_default_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   class CKheperaIVProximitySensorImpl : public CProximityDefaultSensor {

   public:

      virtual void SetRobot(CComposableEntity& c_entity) {
         try {
            m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity = &(c_entity.GetComponent<CProximitySensorEquippedEntity>("proximity_sensors[proximity]"));
            m_pcProximityEntity->Enable();
         }
         catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Khepera IV proximity default sensor", ex);
         }
      }

      virtual Real CalculateReading(Real f_distance) {
         if(f_distance < 0.04) {
            return 1.0;
         }
         else if(f_distance > 0.12){
            return 0.0;
         }
         else {
            return 4.14*exp(-33.0*f_distance)-.085;
         }
      }

   };

   /****************************************/
   /****************************************/

   CKheperaIVProximityDefaultSensor::CKheperaIVProximityDefaultSensor() :
      m_pcProximityImpl(new CKheperaIVProximitySensorImpl()) {}

   /****************************************/
   /****************************************/

   CKheperaIVProximityDefaultSensor::~CKheperaIVProximityDefaultSensor() {
      delete m_pcProximityImpl;
   }

   /****************************************/
   /****************************************/

   void CKheperaIVProximityDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      try {
         m_pcProximityImpl->SetRobot(c_entity);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Khepera IV proximity default sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVProximityDefaultSensor::Init(TConfigurationNode& t_tree) {
      m_pcProximityImpl->Init(t_tree);
   }

   /****************************************/
   /****************************************/

   void CKheperaIVProximityDefaultSensor::Update() {
      m_pcProximityImpl->Update();
      for(size_t i = 0; i < m_pcProximityImpl->GetReadings().size(); ++i) {
         m_tReadings[i].Value = m_pcProximityImpl->GetReadings()[i];
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVProximityDefaultSensor::Reset() {
      m_pcProximityImpl->Reset();
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CKheperaIVProximityDefaultSensor,
                   "kheperaiv_proximity", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The Khepera IV proximity sensor.",
                   "This sensor accesses the Khepera IV proximity sensor. For a complete description\n"
                   "of its usage, refer to the ci_kheperaiv_proximity_sensor.h interface. For the XML\n"
                   "configuration, refer to the default proximity sensor.\n",
                   "Usable"
		  );

}
