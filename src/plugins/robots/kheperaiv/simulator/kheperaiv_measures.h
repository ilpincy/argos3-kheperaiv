/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef KHEPERAIV_MEASURES_H
#define KHEPERAIV_MEASURES_H

#include <argos3/core/utility/datatypes/datatypes.h>
#include <argos3/core/utility/math/vector2.h>
#include <argos3/core/utility/math/vector3.h>

using namespace argos;

extern const Real KHEPERAIV_BASE_RADIUS;
extern const Real KHEPERAIV_BASE_ELEVATION;
extern const Real KHEPERAIV_BASE_HEIGHT;
extern const Real KHEPERAIV_BASE_TOP;

extern const Real KHEPERAIV_WHEEL_RADIUS;
extern const Real KHEPERAIV_WHEEL_DISTANCE;
extern const Real KHEPERAIV_HALF_WHEEL_DISTANCE;

extern const Real KHEPERAIV_IR_SENSORS_RING_ELEVATION;
extern const Real KHEPERAIV_IR_SENSORS_RING_RADIUS;
extern const Real KHEPERAIV_IR_SENSORS_RING_RANGE;

extern const Real KHEPERAIV_ULTRASOUND_SENSORS_RING_ELEVATION;
extern const Real KHEPERAIV_ULTRASOUND_SENSORS_RING_RADIUS;
extern const CRange<Real> KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE;

extern const CVector2 KHEPERAIV_IR_SENSORS_GROUND_OFFSET[4];

extern const CVector3 KHEPERAIV_LEDS_OFFSET[3];

extern const Real KHEPERAIV_LIDAR_ELEVATION;
extern const Real KHEPERAIV_LIDAR_SENSORS_FAN_RADIUS;
extern const CRadians KHEPERAIV_LIDAR_ANGLE_SPAN;
extern const CRange<Real> KHEPERAIV_LIDAR_SENSORS_RING_RANGE;

#endif
