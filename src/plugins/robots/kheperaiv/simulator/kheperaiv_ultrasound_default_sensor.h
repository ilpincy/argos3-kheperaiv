/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_ultrasound_default_sensor.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef KHEPERAIV_ULTRASOUND_DEFAULT_SENSOR_H
#define KHEPERAIV_ULTRASOUND_DEFAULT_SENSOR_H

#include <string>
#include <map>

namespace argos {
   class CKheperaIVUltrasoundDefaultSensor;
}

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ultrasound_sensor.h>
#include <argos3/plugins/robots/generic/simulator/proximity_default_sensor.h>

namespace argos {

   class CKheperaIVUltrasoundDefaultSensor : public CCI_KheperaIVUltrasoundSensor,
                                             public CSimulatedSensor {

   public:

      CKheperaIVUltrasoundDefaultSensor();

      virtual ~CKheperaIVUltrasoundDefaultSensor();

      virtual void SetRobot(CComposableEntity& c_entity);

      virtual void Init(TConfigurationNode& t_tree);

      virtual void Update();

      virtual void Reset();

   private:

      CProximityDefaultSensor* m_pcUltrasoundImpl;

   };

}

#endif
