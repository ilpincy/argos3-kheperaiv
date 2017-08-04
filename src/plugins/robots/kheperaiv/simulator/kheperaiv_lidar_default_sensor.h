/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_lidar_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef KHEPERAIV_LIDAR_DEFAULT_SENSOR_H
#define KHEPERAIV_LIDAR_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CKheperaIVLIDARDefaultSensor;
}

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_lidar_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CKheperaIVLIDARDefaultSensor : public CCI_KheperaIVLIDARSensor,
                                        public CSimulatedSensor {

   public:

      CKheperaIVLIDARDefaultSensor();

      virtual ~CKheperaIVLIDARDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      /** Reference to embodied entity associated to this sensor */
      CEmbodiedEntity* m_pcEmbodiedEntity;

      /** Reference to proximity sensor equipped entity associated to this sensor */
      CProximitySensorEquippedEntity* m_pcProximityEntity;

      /** Reference to controllable entity associated to this sensor */
      CControllableEntity* m_pcControllableEntity;

      /** Flag to show rays in the simulator */
      bool m_bShowRays;

      /** Random number generator */
      CRandom::CRNG* m_pcRNG;

      /** Whether to add noise or not */
      bool m_bAddNoise;

      /** Noise range */
      CRange<Real> m_cNoiseRange;

      /** Reference to the space */
      CSpace& m_cSpace;
   };

}

#endif
