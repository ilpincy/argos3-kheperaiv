/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_entity.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "kheperaiv_entity.h"
#include "kheperaiv_measures.h"

#include <argos3/core/utility/math/matrix/rotationmatrix3.h>
#include <argos3/core/simulator/space/space.h>
#include <argos3/core/simulator/entity/controllable_entity.h>
#include <argos3/core/simulator/entity/embodied_entity.h>
#include <argos3/plugins/simulator/entities/ground_sensor_equipped_entity.h>
#include <argos3/plugins/simulator/entities/led_equipped_entity.h>
#include <argos3/plugins/simulator/entities/light_sensor_equipped_entity.h>
#include <argos3/plugins/simulator/entities/proximity_sensor_equipped_entity.h>
#include <argos3/plugins/simulator/entities/rab_equipped_entity.h>

static CRadians ULTRASOUND_SENSOR_ANGLES[5] = {
   CRadians::ZERO,
   CRadians::PI_OVER_FOUR,
   CRadians::PI_OVER_TWO,
   -CRadians::PI_OVER_TWO,
   -CRadians::PI_OVER_FOUR,
};

namespace argos {

   /****************************************/
   /****************************************/

   CKheperaIVEntity::CKheperaIVEntity() :
      CComposableEntity(NULL),
      m_pcControllableEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_pcGroundSensorEquippedEntity(NULL),
      m_pcLEDEquippedEntity(NULL),
      m_pcLightSensorEquippedEntity(NULL),
      m_pcProximitySensorEquippedEntity(NULL),
      m_pcUltrasoundSensorEquippedEntity(NULL),
      m_pcRABEquippedEntity(NULL),
      m_pcWheeledEntity(NULL) {
   }

   /****************************************/
   /****************************************/
   
   CKheperaIVEntity::CKheperaIVEntity(const std::string& str_id,
                                      const std::string& str_controller_id,
                                      const CVector3& c_position,
                                      const CQuaternion& c_orientation,
                                      Real f_rab_range,
                                      size_t un_rab_data_size) :
      CComposableEntity(NULL, str_id),
      m_pcControllableEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_pcGroundSensorEquippedEntity(NULL),
      m_pcLEDEquippedEntity(NULL),
      m_pcLightSensorEquippedEntity(NULL),
      m_pcProximitySensorEquippedEntity(NULL),
      m_pcUltrasoundSensorEquippedEntity(NULL),
      m_pcRABEquippedEntity(NULL),
      m_pcWheeledEntity(NULL) {
      try {
         /*
          * Create and init components
          */
         /* Embodied entity */
         m_pcEmbodiedEntity = new CEmbodiedEntity(this, "body_0", c_position, c_orientation);
         AddComponent(*m_pcEmbodiedEntity);
         /* Wheeled entity and wheel positions (left, right) */
         m_pcWheeledEntity = new CWheeledEntity(this, "wheels_0", 2);
         AddComponent(*m_pcWheeledEntity);
         m_pcWheeledEntity->SetWheel(0, CVector3(0.0f,  KHEPERAIV_HALF_WHEEL_DISTANCE, 0.0f), KHEPERAIV_WHEEL_RADIUS);
         m_pcWheeledEntity->SetWheel(1, CVector3(0.0f, -KHEPERAIV_HALF_WHEEL_DISTANCE, 0.0f), KHEPERAIV_WHEEL_RADIUS);
         /* LED equipped entity */
         m_pcLEDEquippedEntity = new CLEDEquippedEntity(this, "leds_0");
         AddComponent(*m_pcLEDEquippedEntity);
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[0],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[1],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[2],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         /* Proximity sensor equipped entity */
         m_pcProximitySensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "proximity");
         AddComponent(*m_pcProximitySensorEquippedEntity);
         m_pcProximitySensorEquippedEntity->AddSensorRing(
            CVector3(0.0f, 0.0f, KHEPERAIV_IR_SENSORS_RING_ELEVATION),
            KHEPERAIV_IR_SENSORS_RING_RADIUS,
            CRadians::ZERO,
            KHEPERAIV_IR_SENSORS_RING_RANGE,
            8,
            m_pcEmbodiedEntity->GetOriginAnchor());
         /* Ultrasound sensor equipped entity */
         m_pcUltrasoundSensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "ultrasound");
         AddComponent(*m_pcUltrasoundSensorEquippedEntity);
         for(UInt32 i = 0; i < 5; ++i) {
            m_pcUltrasoundSensorEquippedEntity->AddSensor(
               CVector3(KHEPERAIV_ULTRASOUND_SENSORS_RING_RADIUS +
                        KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE.GetMin(),
                        CRadians::ZERO,
                        ULTRASOUND_SENSOR_ANGLES[i]), // offset
               CVector3(1.0,
                        CRadians::ZERO,
                        ULTRASOUND_SENSOR_ANGLES[i]), // direction
               KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE.GetMax(),
               m_pcEmbodiedEntity->GetOriginAnchor());
         }
         /* LIDAR sensor equipped entity */
         m_pcLIDARSensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "lidar");
         AddComponent(*m_pcLIDARSensorEquippedEntity);
         /* Light sensor equipped entity */
         m_pcLightSensorEquippedEntity =
            new CLightSensorEquippedEntity(this,
                                           "light_0");
         AddComponent(*m_pcLightSensorEquippedEntity);
         m_pcLightSensorEquippedEntity->AddSensorRing(
            CVector3(0.0f, 0.0f, KHEPERAIV_IR_SENSORS_RING_ELEVATION),
            KHEPERAIV_IR_SENSORS_RING_RADIUS,
            CRadians::ZERO,
            KHEPERAIV_IR_SENSORS_RING_RANGE,
            8,
            m_pcEmbodiedEntity->GetOriginAnchor());
         /* Ground sensor equipped entity */
         m_pcGroundSensorEquippedEntity =
            new CGroundSensorEquippedEntity(this,
                                            "ground_0");
         AddComponent(*m_pcGroundSensorEquippedEntity);
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[0],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[1],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[2],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[3],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         /* RAB equipped entity */
         m_pcRABEquippedEntity =
            new CRABEquippedEntity(this,
                                   "rab_0",
                                   un_rab_data_size,
                                   f_rab_range,
                                   m_pcEmbodiedEntity->GetOriginAnchor(),
                                   *m_pcEmbodiedEntity,
                                   CVector3(0.0f, 0.0f, KHEPERAIV_BASE_TOP));
         AddComponent(*m_pcRABEquippedEntity);
         /* Controllable entity
            It must be the last one, for actuators/sensors to link to composing entities correctly */
         m_pcControllableEntity = new CControllableEntity(this, "controller_0");
         AddComponent(*m_pcControllableEntity);
         m_pcControllableEntity->SetController(str_controller_id);
         /* Update components */
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVEntity::Init(TConfigurationNode& t_tree) {
      try {
         /*
          * Init parent
          */
         CComposableEntity::Init(t_tree);
         /*
          * Create and init components
          */
         /* Embodied entity */
         m_pcEmbodiedEntity = new CEmbodiedEntity(this);
         AddComponent(*m_pcEmbodiedEntity);
         m_pcEmbodiedEntity->Init(GetNode(t_tree, "body"));
         /* Wheeled entity and wheel positions (left, right) */
         m_pcWheeledEntity = new CWheeledEntity(this, "wheels_0", 2);
         AddComponent(*m_pcWheeledEntity);
         m_pcWheeledEntity->SetWheel(0, CVector3(0.0f,  KHEPERAIV_HALF_WHEEL_DISTANCE, 0.0f), KHEPERAIV_WHEEL_RADIUS);
         m_pcWheeledEntity->SetWheel(1, CVector3(0.0f, -KHEPERAIV_HALF_WHEEL_DISTANCE, 0.0f), KHEPERAIV_WHEEL_RADIUS);
         /* LED equipped entity, with LEDs [0-11] and beacon [12] */
         m_pcLEDEquippedEntity = new CLEDEquippedEntity(this, "leds_0");
         AddComponent(*m_pcLEDEquippedEntity);
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[0],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[1],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcLEDEquippedEntity->AddLED(KHEPERAIV_LEDS_OFFSET[2],
                                       m_pcEmbodiedEntity->GetOriginAnchor());
         /* Proximity sensor equipped entity */
         m_pcProximitySensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "proximity");
         AddComponent(*m_pcProximitySensorEquippedEntity);
         m_pcProximitySensorEquippedEntity->AddSensorRing(
            CVector3(0.0f, 0.0f, KHEPERAIV_IR_SENSORS_RING_ELEVATION),
            KHEPERAIV_IR_SENSORS_RING_RADIUS,
            CRadians::ZERO,
            KHEPERAIV_IR_SENSORS_RING_RANGE,
            8,
            m_pcEmbodiedEntity->GetOriginAnchor());
         /* Ultrasound sensor equipped entity */
         m_pcUltrasoundSensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "ultrasound");
         AddComponent(*m_pcUltrasoundSensorEquippedEntity);
         for(UInt32 i = 0; i < 5; ++i) {
            m_pcUltrasoundSensorEquippedEntity->AddSensor(
               CVector3(KHEPERAIV_ULTRASOUND_SENSORS_RING_RADIUS +
                        KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE.GetMin(),
                        CRadians::PI_OVER_TWO,
                        ULTRASOUND_SENSOR_ANGLES[i]), // offset
               CVector3(1.0,
                        CRadians::PI_OVER_TWO,
                        ULTRASOUND_SENSOR_ANGLES[i]), // direction
               KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE.GetMax(),
               m_pcEmbodiedEntity->GetOriginAnchor());
         }
         /* LIDAR sensor equipped entity */
         m_pcLIDARSensorEquippedEntity =
            new CProximitySensorEquippedEntity(this,
                                               "lidar");
         AddComponent(*m_pcLIDARSensorEquippedEntity);
         /* Light sensor equipped entity */
         m_pcLightSensorEquippedEntity =
            new CLightSensorEquippedEntity(this,
                                           "light_0");
         AddComponent(*m_pcLightSensorEquippedEntity);
         m_pcLightSensorEquippedEntity->AddSensorRing(
            CVector3(0.0f, 0.0f, KHEPERAIV_IR_SENSORS_RING_ELEVATION),
            KHEPERAIV_IR_SENSORS_RING_RADIUS,
            CRadians::ZERO,
            KHEPERAIV_IR_SENSORS_RING_RANGE,
            8,
            m_pcEmbodiedEntity->GetOriginAnchor());
         /* Ground sensor equipped entity */
         m_pcGroundSensorEquippedEntity =
            new CGroundSensorEquippedEntity(this,
                                            "ground_0");
         AddComponent(*m_pcGroundSensorEquippedEntity);
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[0],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[1],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[2],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         m_pcGroundSensorEquippedEntity->AddSensor(KHEPERAIV_IR_SENSORS_GROUND_OFFSET[3],
                                                   CGroundSensorEquippedEntity::TYPE_GRAYSCALE,
                                                   m_pcEmbodiedEntity->GetOriginAnchor());
         /* RAB equipped entity */
         Real fRange = 3.0f;
         GetNodeAttributeOrDefault(t_tree, "rab_range", fRange, fRange);
         UInt32 unDataSize = 10;
         GetNodeAttributeOrDefault(t_tree, "rab_data_size", unDataSize, unDataSize);
         m_pcRABEquippedEntity =
            new CRABEquippedEntity(this,
                                   "rab_0",
                                   unDataSize,
                                   fRange,
                                   m_pcEmbodiedEntity->GetOriginAnchor(),
                                   *m_pcEmbodiedEntity,
                                   CVector3(0.0f, 0.0f, KHEPERAIV_BASE_TOP));
         AddComponent(*m_pcRABEquippedEntity);
         /* Controllable entity
            It must be the last one, for actuators/sensors to link to composing entities correctly */
         m_pcControllableEntity = new CControllableEntity(this);
         AddComponent(*m_pcControllableEntity);
         m_pcControllableEntity->Init(GetNode(t_tree, "controller"));
         /* Update components */
         UpdateComponents();
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Failed to initialize entity \"" << GetId() << "\".", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CKheperaIVEntity::Reset() {
      /* Reset all components */
      CComposableEntity::Reset();
      /* Update components */
      UpdateComponents();
   }

   /****************************************/
   /****************************************/

   void CKheperaIVEntity::Destroy() {
      CComposableEntity::Destroy();
   }

   /****************************************/
   /****************************************/

   void CKheperaIVEntity::UpdateComponents() {
      if(m_pcLEDEquippedEntity->IsEnabled())
         m_pcLEDEquippedEntity->Update();
      if(m_pcRABEquippedEntity->IsEnabled())
         m_pcRABEquippedEntity->Update();
   }

   /****************************************/
   /****************************************/
   
   REGISTER_ENTITY(CKheperaIVEntity,
                   "kheperaiv",
                   "Carlo Pinciroli [ilpincy@gmail.com]",
                   "1.0",
                   "The Khepera IV robot.",
                   "The Khepera IV is a commercial, extensible robot produced by K-Teams. More\n"
                   "information is available at https://www.k-team.com/khepera-iv.\n\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <kheperaiv id=\"eb0\">\n"
                   "      <body position=\"0.4,2.3,0.25\" orientation=\"45,90,0\" />\n"
                   "      <controller config=\"mycntrl\" />\n"
                   "    </kheperaiv>\n"
                   "    ...\n"
                   "  </arena>\n\n"
                   "The 'id' attribute is necessary and must be unique among the entities. If two\n"
                   "entities share the same id, initialization aborts.\n"
                   "The 'body/position' attribute specifies the position of the pucktom point of the\n"
                   "Khepera IV in the arena. When the robot is untranslated and unrotated, the\n"
                   "pucktom point is in the origin and it is defined as the middle point between\n"
                   "the two wheels on the XY plane and the lowest point of the robot on the Z\n"
                   "axis, that is the point where the wheels touch the floor. The attribute values\n"
                   "are in the X,Y,Z order.\n"
                   "The 'body/orientation' attribute specifies the orientation of the Khepera IV.\n"
                   "All rotations are performed with respect to the pucktom point. The order of the\n"
                   "angles is Z,Y,X, which means that the first number corresponds to the rotation\n"
                   "around the Z axis, the second around Y and the last around X. This reflects\n"
                   "the internal convention used in ARGoS, in which rotations are performed in\n"
                   "that order. Angles are expressed in degrees. When the robot is unrotated, it\n"
                   "is oriented along the X axis.\n"
                   "The 'controller/config' attribute is used to assign a controller to the\n"
                   "Khepera IV. The value of the attribute must be set to the id of a previously\n"
                   "defined controller. Controllers are defined in the <controllers> XML subtree.\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "You can set the emission range of the range-and-bearing system. By default, a\n"
                   "message sent by a Khepera IV can be received up to 3m. By using the 'rab_range'\n"
                   "attribute, you can change it to, i.e., 4m as follows:\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <kheperaiv id=\"fb0\" rab_range=\"4\">\n"
                   "      <body position=\"0.4,2.3,0.25\" orientation=\"45,0,0\" />\n"
                   "      <controller config=\"mycntrl\" />\n"
                   "    </kheperaiv>\n"
                   "    ...\n"
                   "  </arena>\n\n"
                   "You can also set the data sent at each time step through the range-and-bearing"
                   "system. By default, a message sent by a khepera is 50 bytes long. By using the"
                   "'rab_data_size' attribute, you can change it to, i.e., 100 bytes as follows:\n\n"
                   "  <arena ...>\n"
                   "    ...\n"
                   "    <kheperaiv id=\"fb0\" rab_data_size=\"100\">\n"
                   "      <body position=\"0.4,2.3,0.25\" orientation=\"45,0,0\" />\n"
                   "      <controller config=\"mycntrl\" />\n"
                   "    </kheperaiv>\n"
                   "    ...\n"
                   "  </arena>\n\n",
                   "Under development"
      );

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_SPACE_OPERATIONS_ON_COMPOSABLE(CKheperaIVEntity);

   /****************************************/
   /****************************************/

}
