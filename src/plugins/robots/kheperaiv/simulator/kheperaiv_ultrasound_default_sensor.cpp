/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_ultrasound_default_sensor.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/core/simulator/simulator.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>

#include "kheperaiv_ultrasound_default_sensor.h"

namespace argos {

   /****************************************/
   /****************************************/

   class CUltrasoundSensorImpl : public CProximityDefaultSensor {

      static const CRange<Real> RANGE;

   public:

      virtual void SetRobot(CComposableEntity& c_entity) {
         try {
            m_pcEmbodiedEntity = &(c_entity.GetComponent<CEmbodiedEntity>("body"));
            m_pcControllableEntity = &(c_entity.GetComponent<CControllableEntity>("controller"));
            m_pcProximityEntity = &(c_entity.GetComponent<CProximitySensorEquippedEntity>("proximity_sensors[ultrasound]"));
            m_pcProximityEntity->Enable();
         }
         catch(CARGoSException& ex) {
            THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Khepera IV ultrasound default sensor", ex);
         }
      }

      virtual Real CalculateReading(Real f_distance) {
         return RANGE.NormalizeValue(f_distance);
      }

   };

   const CRange<Real> CUltrasoundSensorImpl::RANGE = CRange<Real>(0.25, 2);

   /****************************************/
   /****************************************/

   CKheperaIVUltrasoundDefaultSensor::CKheperaIVUltrasoundDefaultSensor() :
      m_pcUltrasoundImpl(new CUltrasoundSensorImpl()) {}

   /****************************************/
   /****************************************/

   CKheperaIVUltrasoundDefaultSensor::~CKheperaIVUltrasoundDefaultSensor() {
      delete m_pcUltrasoundImpl;
   }

   /****************************************/
   /****************************************/

   void CKheperaIVUltrasoundDefaultSensor::SetRobot(CComposableEntity& c_entity) {
      try {
         m_pcUltrasoundImpl->SetRobot(c_entity);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Can't set robot for the Khepera IV ultrasound default sensor", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVUltrasoundDefaultSensor::Init(TConfigurationNode& t_tree) {
      m_pcUltrasoundImpl->Init(t_tree);
   }

   /****************************************/
   /****************************************/

   void CKheperaIVUltrasoundDefaultSensor::Update() {
      m_pcUltrasoundImpl->Update();
      for(size_t i = 0; i < m_pcUltrasoundImpl->GetReadings().size(); ++i) {
         m_tReadings[i].Value = m_pcUltrasoundImpl->GetReadings()[i];
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVUltrasoundDefaultSensor::Reset() {
      m_pcUltrasoundImpl->Reset();
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CKheperaIVUltrasoundDefaultSensor,
                   "kheperaiv_ultrasound", "default",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The Khepera IV ultrasound sensor.",
                   "This sensor accesses the Khepera IV ultrasound sensor. For a complete description\n"
                   "of its usage, refer to the ci_kheperaiv_ultrasound_sensor.h interface. For the XML\n"
                   "configuration, refer to the default proximity sensor.\n",
                   "Usable"
		  );

}
