
/**
 * @file <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_base_ground_sensor.cpp>
 *
 * @author Carlo Pinciroli <ilpincy@gmail.com>
 */

#include "ci_kheperaiv_ground_sensor.h"

#ifdef ARGOS_WITH_LUA
#include <argos3/core/wrappers/lua/lua_utility.h>
#endif

namespace argos {

   /****************************************/
   /****************************************/

   CCI_KheperaIVBaseGroundSensor::CCI_KheperaIVBaseGroundSensor() :
      m_tReadings(8) {
      // Set the values for the base ground sensor offset (taken from the CAD model, in cm)
      m_tReadings[0].Offset.Set(0.06140,  0.01);
      m_tReadings[1].Offset.Set(0.02060,  0.0059);
      m_tReadings[2].Offset.Set(0.02060, -0.0059);
      m_tReadings[3].Offset.Set(0.06140, -0.01);
   }

   /****************************************/
   /****************************************/

   const CCI_KheperaIVBaseGroundSensor::TReadings& CCI_KheperaIVBaseGroundSensor::GetReadings() const {
     return m_tReadings;
   }
      
   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_KheperaIVBaseGroundSensor::SReading& s_reading) {
      c_os << "Value=<" << s_reading.Value
           << ">, Offset=<" << s_reading.Offset << ">";
      return c_os;
   }

   /****************************************/
   /****************************************/

   std::ostream& operator<<(std::ostream& c_os,
                            const CCI_KheperaIVBaseGroundSensor::TReadings& t_readings) {
      if(! t_readings.empty()) {
         c_os << "{ " << t_readings[0].Value << " }";
         for(UInt32 i = 1; i < t_readings.size(); ++i) {
            c_os << " { " << t_readings[0].Value << " }";
         }
         c_os << std::endl;
      }
      return c_os;
   }

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_KheperaIVBaseGroundSensor::CreateLuaState(lua_State* pt_lua_state) {
      CLuaUtility::OpenRobotStateTable(pt_lua_state, "ground");
      for(size_t i = 0; i < m_tReadings.size(); ++i) {
         CLuaUtility::StartTable(pt_lua_state, i+1                            );
         CLuaUtility::AddToTable(pt_lua_state, "offset", m_tReadings[i].Offset);
         CLuaUtility::AddToTable(pt_lua_state, "value",  m_tReadings[i].Value );
         CLuaUtility::EndTable  (pt_lua_state                                 );
      }
      CLuaUtility::CloseRobotStateTable(pt_lua_state);
   }
#endif

   /****************************************/
   /****************************************/

#ifdef ARGOS_WITH_LUA
   void CCI_KheperaIVBaseGroundSensor::ReadingsToLuaState(lua_State* pt_lua_state) {
      lua_getfield(pt_lua_state, -1, "ground");
      for(size_t i = 0; i < m_tReadings.size(); ++i) {
         lua_pushnumber(pt_lua_state, i+1                 );
         lua_gettable  (pt_lua_state, -2                  );
         lua_pushnumber(pt_lua_state, m_tReadings[i].Value);
         lua_setfield  (pt_lua_state, -2, "value"         );
         lua_pop       (pt_lua_state, 1                   );
      }
      lua_pop(pt_lua_state, 1);
   }
#endif


   /****************************************/
   /****************************************/

}
