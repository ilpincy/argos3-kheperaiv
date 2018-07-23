/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/kheperaiv_measures.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "kheperaiv_measures.h"

/****************************************/
/****************************************/

const Real KHEPERAIV_BASE_RADIUS    = 0.0704;
const Real KHEPERAIV_BASE_ELEVATION = 0.0047;
const Real KHEPERAIV_BASE_HEIGHT    = 0.053;
const Real KHEPERAIV_BASE_TOP       = KHEPERAIV_BASE_ELEVATION + KHEPERAIV_BASE_HEIGHT;

const Real KHEPERAIV_WHEEL_RADIUS        = 0.021;
const Real KHEPERAIV_WHEEL_DISTANCE      = 0.1054;
const Real KHEPERAIV_HALF_WHEEL_DISTANCE = KHEPERAIV_WHEEL_DISTANCE * 0.5;

const Real KHEPERAIV_IR_SENSORS_RING_ELEVATION = 0.0145;
const Real KHEPERAIV_IR_SENSORS_RING_RADIUS    = KHEPERAIV_BASE_RADIUS;
const Real KHEPERAIV_IR_SENSORS_RING_RANGE     = 0.12;

const Real KHEPERAIV_ULTRASOUND_SENSORS_RING_ELEVATION = 0.0145;
const Real KHEPERAIV_ULTRASOUND_SENSORS_RING_RADIUS    = KHEPERAIV_BASE_RADIUS;
const CRange<Real> KHEPERAIV_ULTRASOUND_SENSORS_RING_RANGE(0.25, 2.0);

const CVector2 KHEPERAIV_IR_SENSORS_GROUND_OFFSET[4] = {
   CVector2(0.06140,  0.01),
   CVector2(0.02060,  0.059),
   CVector2(0.02060, -0.059),
   CVector2(0.06140, -0.01)
};

const CVector3 KHEPERAIV_LEDS_OFFSET[3] = {
   CVector3( 0.04,  0.025, KHEPERAIV_BASE_TOP),
   CVector3(-0.05,  0.000, KHEPERAIV_BASE_TOP),
   CVector3( 0.04, -0.025, KHEPERAIV_BASE_TOP)
};

const Real KHEPERAIV_LIDAR_ELEVATION          = KHEPERAIV_BASE_TOP;
const Real KHEPERAIV_LIDAR_SENSORS_FAN_RADIUS = KHEPERAIV_BASE_RADIUS;
const CRadians KHEPERAIV_LIDAR_ANGLE_SPAN(ToRadians(CDegrees(210.0)));
const CRange<Real> KHEPERAIV_LIDAR_SENSORS_RING_RANGE(0.02, 4.0);

/****************************************/
/****************************************/
