/**
 * @file <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_lidar_sensor.h>
 *
 * @brief This file provides the definition of the Khepera IV LIDAR sensor.
 *
 * This file provides the definition of the Khepera IV LIDAR sensor.
 * The sensor readings are evenly spaced on a slice around the body of
 * the robot.
 * 
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#ifndef CCI_KHEPERAIV_LIDAR_SENSOR_H
#define CCI_KHEPERAIV_LIDAR_SENSOR_H

namespace argos {
   class CCI_KheperaIVLIDARSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/angles.h>

namespace argos {

   class CCI_KheperaIVLIDARSensor : public CCI_Sensor {

   public:

      typedef std::vector<Real> TReadings;

   public:

      /**
       * Class constructor
       */
      CCI_KheperaIVLIDARSensor();

      /**
       * Class destructor
       */
      virtual ~CCI_KheperaIVLIDARSensor() {}

      /**
       * Returns the readings of this sensor
       */
      const TReadings& GetReadings() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      TReadings m_tReadings;

   };

}

#endif
