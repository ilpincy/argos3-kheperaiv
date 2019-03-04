#ifndef REAL_KHEPERAIV_CAMERA_SENSOR_H
#define REAL_KHEPERAIV_CAMERA_SENSOR_H

#include <argos3/plugins/robots/generic/control_interface/ci_camera_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>
#include <pthread.h>

using namespace argos;

class CRealKheperaIVCameraSensor :
   public CCI_CameraSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVCameraSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVCameraSensor();

   virtual void Init(TConfigurationNode& t_node);

   virtual void Destroy();

   virtual void Do();

private:

   /* Thread handle */
   pthread_t m_tThread;
   /* Data mutex */
   pthread_mutex_t m_tDataMutex;
   /* Image buffer */
   unsigned char* m_pchBuffer;
};

#endif // REAL_KHEPERAIV_CAMERA_SENSOR_H
