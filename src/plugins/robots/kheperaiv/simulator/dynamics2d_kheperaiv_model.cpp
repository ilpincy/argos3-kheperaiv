/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/dynamics2d_kheperaiv_model.cpp>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#include "dynamics2d_kheperaiv_model.h"
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_gripping.h>
#include <argos3/plugins/simulator/physics_engines/dynamics2d/dynamics2d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   static const Real KHEPERAIV_MASS                = 0.4f;

   static const Real KHEPERAIV_RADIUS              = 0.035f;
   static const Real KHEPERAIV_INTERWHEEL_DISTANCE = 0.053f;
   static const Real KHEPERAIV_HEIGHT              = 0.086f;

   static const Real KHEPERAIV_MAX_FORCE           = 1.5f;
   static const Real KHEPERAIV_MAX_TORQUE          = 1.5f;

   enum KHEPERAIV_WHEELS {
      KHEPERAIV_LEFT_WHEEL = 0,
      KHEPERAIV_RIGHT_WHEEL = 1
   };

   /****************************************/
   /****************************************/

   CDynamics2DKheperaIVModel::CDynamics2DKheperaIVModel(CDynamics2DEngine& c_engine,
                                                CKheperaIVEntity& c_entity) :
      CDynamics2DSingleBodyObjectModel(c_engine, c_entity),
      m_cKheperaIVEntity(c_entity),
      m_cWheeledEntity(m_cKheperaIVEntity.GetWheeledEntity()),
      m_cDiffSteering(c_engine,
                      KHEPERAIV_MAX_FORCE,
                      KHEPERAIV_MAX_TORQUE,
                      KHEPERAIV_INTERWHEEL_DISTANCE),
      m_fCurrentWheelVelocity(m_cWheeledEntity.GetWheelVelocities()) {
      /* Create the body with initial position and orientation */
      cpBody* ptBody =
         cpSpaceAddBody(GetDynamics2DEngine().GetPhysicsSpace(),
                        cpBodyNew(KHEPERAIV_MASS,
                                  cpMomentForCircle(KHEPERAIV_MASS,
                                                    0.0f,
                                                    KHEPERAIV_RADIUS + KHEPERAIV_RADIUS,
                                                    cpvzero)));
      const CVector3& cPosition = GetEmbodiedEntity().GetOriginAnchor().Position;
      ptBody->p = cpv(cPosition.GetX(), cPosition.GetY());
      CRadians cXAngle, cYAngle, cZAngle;
      GetEmbodiedEntity().GetOriginAnchor().Orientation.ToEulerAngles(cZAngle, cYAngle, cXAngle);
      cpBodySetAngle(ptBody, cZAngle.GetValue());
      /* Create the body shape */
      cpShape* ptShape =
         cpSpaceAddShape(GetDynamics2DEngine().GetPhysicsSpace(),
                         cpCircleShapeNew(ptBody,
                                          KHEPERAIV_RADIUS,
                                          cpvzero));
      ptShape->e = 0.0; // No elasticity
      ptShape->u = 0.7; // Lots of friction
      /* Constrain the actual base body to follow the diff steering control */
      m_cDiffSteering.AttachTo(ptBody);
      /* Set the body so that the default methods work as expected */
      SetBody(ptBody, KHEPERAIV_HEIGHT);
   }

   /****************************************/
   /****************************************/

   CDynamics2DKheperaIVModel::~CDynamics2DKheperaIVModel() {
      m_cDiffSteering.Detach();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DKheperaIVModel::Reset() {
      CDynamics2DSingleBodyObjectModel::Reset();
      m_cDiffSteering.Reset();
   }

   /****************************************/
   /****************************************/

   void CDynamics2DKheperaIVModel::UpdateFromEntityStatus() {
      /* Do we want to move? */
      if((m_fCurrentWheelVelocity[KHEPERAIV_LEFT_WHEEL] != 0.0f) ||
         (m_fCurrentWheelVelocity[KHEPERAIV_RIGHT_WHEEL] != 0.0f)) {
         m_cDiffSteering.SetWheelVelocity(m_fCurrentWheelVelocity[KHEPERAIV_LEFT_WHEEL],
                                          m_fCurrentWheelVelocity[KHEPERAIV_RIGHT_WHEEL]);
      }
      else {
         /* No, we don't want to move - zero all speeds */
         m_cDiffSteering.Reset();
      }
   }

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS2D_OPERATIONS_ON_ENTITY(CKheperaIVEntity, CDynamics2DKheperaIVModel);

   /****************************************/
   /****************************************/

}
