/**
 * @file <argos3/plugins/robots/kheperaiv/simulator/qtopengl_kheperaiv.h>
 *
 * @author Carlo Pinciroli - <ilpincy@gmail.com>
 */

#ifndef QTOPENGL_KHEPERAIV_H
#define QTOPENGL_KHEPERAIV_H

namespace argos {
   class CQTOpenGLKheperaIV;
   class CKheperaIVEntity;
}

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

namespace argos {

   class CQTOpenGLKheperaIV {

   public:

      CQTOpenGLKheperaIV();

      virtual ~CQTOpenGLKheperaIV();

      virtual void Draw(CKheperaIVEntity& c_entity);

   protected:

      /** Sets a white plastic material */
      void SetWhitePlasticMaterial();
      /** Sets a blue plastic material */
      void SetBluePlasticMaterial();
      /** Sets a colored LED material */
      void SetLEDMaterial(GLfloat f_red,
                          GLfloat f_green,
                          GLfloat f_blue);

      /** Renders the base */
      void RenderBase();
      /** A single LED of the ring */
      void RenderLED();

   private:

      /** Start of the display list index */
      GLuint m_unLists;

      /** Base display list */
      GLuint m_unBaseList;

      /** LED display list */
      GLuint m_unLEDList;

      /** Number of vertices to display the round parts
          (wheels, chassis, etc.) */
      GLuint m_unVertices;

   };

}

#endif
