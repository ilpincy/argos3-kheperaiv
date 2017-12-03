/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef KHEPERAIV_ENTITY_H
#define KHEPERAIV_ENTITY_H

namespace argos {
   class CControllableEntity;
   class CEmbodiedEntity;
   class CKheperaIVEntity;
   class CGroundSensorEquippedEntity;
   class CLEDEquippedEntity;
   class CLightSensorEquippedEntity;
   class CProximitySensorEquippedEntity;
   class CRABEquippedEntity;
   class CBatteryEquippedEntity;
}

#include <argos3/core/simulator/entity/composable_entity.h>
#include <argos3/plugins/simulator/entities/wheeled_entity.h>

namespace argos {

   class CKheperaIVEntity : public CComposableEntity {

   public:

      ENABLE_VTABLE();

   public:

      CKheperaIVEntity();

      CKheperaIVEntity(const std::string& str_id,
                       const std::string& str_controller_id,
                       const CVector3& c_position = CVector3(),
                       const CQuaternion& c_orientation = CQuaternion(),
                       Real f_rab_range = 3.0f,
                       size_t un_rab_data_size = 50,
                       UInt16 un_bat_full_capacity = 3400,
                       Real f_bat_ideal_discharge = 0,
                       Real f_bat_moving_discharge = 0);
      
      virtual void Init(TConfigurationNode& t_tree);
      virtual void Reset();
      virtual void Destroy();

      virtual void UpdateComponents();
      
      inline CControllableEntity& GetControllableEntity() {
         return *m_pcControllableEntity;
      }

      inline CEmbodiedEntity& GetEmbodiedEntity() {
         return *m_pcEmbodiedEntity;
      }

      inline CGroundSensorEquippedEntity& GetGroundSensorEquippedEntity() {
         return *m_pcGroundSensorEquippedEntity;
      }

      inline CLEDEquippedEntity& GetLEDEquippedEntity() {
         return *m_pcLEDEquippedEntity;
      }

      inline CLightSensorEquippedEntity& GetLightSensorEquippedEntity() {
         return *m_pcLightSensorEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetProximitySensorEquippedEntity() {
         return *m_pcProximitySensorEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetUltrasoundSensorEquippedEntity() {
         return *m_pcUltrasoundSensorEquippedEntity;
      }

      inline CProximitySensorEquippedEntity& GetLIDARSensorEquippedEntity() {
         return *m_pcLIDARSensorEquippedEntity;
      }

      inline CRABEquippedEntity& GetRABEquippedEntity() {
         return *m_pcRABEquippedEntity;
      }

      inline CWheeledEntity& GetWheeledEntity() {
         return *m_pcWheeledEntity;
      }

      inline CBatteryEquippedEntity& GetBatterySensorEquippedEntity() {
          return *m_pcBatteryEquippedEntity;
      }

      virtual std::string GetTypeDescription() const {
         return "kheperaiv";
      }

   private:

      void SetLEDPosition();

   private:

      CControllableEntity*            m_pcControllableEntity;
      CEmbodiedEntity*                m_pcEmbodiedEntity;
      CGroundSensorEquippedEntity*    m_pcGroundSensorEquippedEntity;
      CLEDEquippedEntity*             m_pcLEDEquippedEntity;
      CLightSensorEquippedEntity*     m_pcLightSensorEquippedEntity;
      CProximitySensorEquippedEntity* m_pcProximitySensorEquippedEntity;
      CProximitySensorEquippedEntity* m_pcUltrasoundSensorEquippedEntity;
      CProximitySensorEquippedEntity* m_pcLIDARSensorEquippedEntity;
      CRABEquippedEntity*             m_pcRABEquippedEntity;
      CWheeledEntity*                 m_pcWheeledEntity;
      CBatteryEquippedEntity*         m_pcBatteryEquippedEntity;
   };

}

#endif
