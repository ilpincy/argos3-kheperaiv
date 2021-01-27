#ifndef REAL_KHEPERAIV_CAMERA_SENSOR_H
#define REAL_KHEPERAIV_CAMERA_SENSOR_H

#include <argos3/plugins/robots/kheperaiv/control_interface/ci_kheperaiv_camera_sensor.h>
#include <argos3/plugins/robots/kheperaiv/real_robot/real_kheperaiv_device.h>
#include <pthread.h>

using namespace argos;

class CRealKheperaIVCameraSensor :
   public CCI_KheperaIVCameraSensor,
   public CRealKheperaIVDevice {

public:

   CRealKheperaIVCameraSensor(knet_dev_t* pt_dspic);
   
   virtual ~CRealKheperaIVCameraSensor();

   virtual void Init(TConfigurationNode& t_node);

   virtual void Destroy();

   virtual const unsigned char* GetPixels() const;

   virtual void Do(Real f_elapsed_time);

public:

   struct SBlobFilter {
      CColor Color;
      CRange<UInt8> Hue;
      CRange<UInt8> Saturation;
      CRange<UInt8> Value;
      UInt32 Tolerance;

      bool Match(const unsigned char* pch_hsv);
   };

   typedef std::vector<SBlobFilter> TBlobFilters;

private:

   /* Image buffer */
   unsigned char* m_pchImgBuffer;
   /* Work buffer for blob detection */
   CCI_KheperaIVCameraSensor::TBlobs m_tBlobWorkBuffer;
   /* Ready buffer for blob detection */
   CCI_KheperaIVCameraSensor::TBlobs m_tBlobReadyBuffer;
   /* Vector of blob filters */
   TBlobFilters m_tBlobFilters;
   /* Thread handle */
   pthread_t m_tThread;
   /* Blob ready buffer mutex */
   pthread_mutex_t m_tBlobReadyMutex;
   /* True when new blob readings are available */
   bool m_bNewBlobReadings;
};

#endif // REAL_KHEPERAIV_CAMERA_SENSOR_H
