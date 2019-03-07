/**
 * @file <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_camera_sensor.h>
 *
 * @brief This file provides the definition of the Khepera IV camera sensor.
 *
 * This file provides the definition of the Khepera IV camera sensor.
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef CCI_KHEPERAIV_CAMERA_SENSOR_H
#define CCI_KHEPERAIV_CAMERA_SENSOR_H

namespace argos {
   class CCI_KheperaIVCameraSensor;
}

#include <argos3/core/control_interface/ci_sensor.h>
#include <argos3/core/utility/datatypes/color.h>
#include <argos3/core/utility/math/vector2.h>
#include <vector>

namespace argos {

   class CCI_KheperaIVCameraSensor : public CCI_Sensor {

   public:

      struct SBlob {
         CColor Color;
         CVector2 Min;
         CVector2 Max;

         SBlob(const CColor& c_color,
               const CVector2& c_pos) :
            Color(c_color),
            Min(c_pos),
            Max(c_pos) {
         }
      };

      typedef std::vector<SBlob> TBlobs;

   public:

      CCI_KheperaIVCameraSensor();
      virtual ~CCI_KheperaIVCameraSensor() {}

      UInt32 GetWidth() const;

      UInt32 GetHeight() const;

      virtual const unsigned char* GetPixels() const = 0;

      const TBlobs& GetBlobs() const;

#ifdef ARGOS_WITH_LUA
      virtual void CreateLuaState(lua_State* pt_lua_state);

      virtual void ReadingsToLuaState(lua_State* pt_lua_state);
#endif

   protected:

      UInt32 m_unWidth;
      UInt32 m_unHeight;
      TBlobs m_tBlobs;
   };

   std::ostream& operator<<(std::ostream& c_os, const CCI_KheperaIVCameraSensor::SBlob& s_blob);
   std::ostream& operator<<(std::ostream& c_os, const CCI_KheperaIVCameraSensor::TBlobs& t_blobs);

}

#endif
