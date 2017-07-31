/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_proximity_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef KHEPERAIV_PROXIMITY_DEFAULT_SENSOR_H
#define KHEPERAIV_PROXIMITY_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CKheperaIVProximityDefaultSensor;
}

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_proximity_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CKheperaIVProximityDefaultSensor : public CCI_KheperaIVProximitySensor,
                                            public CSimulatedSensor {

   public:

      CKheperaIVProximityDefaultSensor();

      virtual ~CKheperaIVProximityDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      CProximityDefaultSensor* m_pcProximityImpl;

   };

}

#endif
