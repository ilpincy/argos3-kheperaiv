/**
 * @file <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_ground_sensor.h>
 *
 * @brief This file provides the interface of the Khepera IV ground sensor.
 *
 * The ground sensors are located on the bottom of the robot, and can
 * be used to perform line following.
 *
 * The readings are in the following order (seeing the robot from TOP,
 * battery socket is the BACK):
 *
 *      front
 *
 *      0   3    r
 * l             i
 * e  1       2  g
 * f             h
 * t             t
 *
 *       back
 *
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#ifndef CCI_KHEPERAIV_GROUND_SENSOR_H
#define CCI_KHEPERAIV_GROUND_SENSOR_H

namespace argos {
   class CCI_KheperaIVGroundSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/math/vector2.h>
#include <vector>

namespace argos {

   class CCI_KheperaIVGroundSensor : virtual public CCI_Sensor {

   public:

      struct SReading {
         Real Value;
         CVector2 Offset;
	 
         SReading() :
            Value(0.0f) {}
	 
         SReading(Real f_value,
                  const CVector2& c_offset) :
            Value(f_value),
            Offset(c_offset) {}
      };

      typedef std::vector<SReading> TReadings;

   public:

      CCI_KheperaIVGroundSensor();

      virtual ~CCI_KheperaIVGroundSensor() {}
      
      const TReadings& GetReadings() const;
      
#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      TReadings m_tReadings;

   };

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_KheperaIVGroundSensor::SReading& s_reading);

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_KheperaIVGroundSensor::TReadings& t_readings);

}

#endif
