#include "real_kheperaiv_camera_sensor.h"
#include <argos3/core/utility/logging/argos_log.h>

/****************************************/
/****************************************/

static std::string InitErrorMsg(int n_errcode) {
   switch(n_errcode) {
      case -1:
         return "no device /dev/video0";
      case -2:
         return "no video capture device";
      case -3:
         return "capabilities error";
      case -4:
         return "cannot open the device";
      case -5:
         return "cannot call system for media-ctl pipes";
      case -6:
         return "media-ctl pipes command exited with error";
      case -7:
         return "cannot call system for media-ctl formats";
      case -8:
         return "media-ctl formats command exited with error";
   }
   return "no error";
}

static std::string CaptureErrorMsg(int n_errcode) {
   switch(n_errcode) {
      case -1:
         return "device not open";
      case -2:
         return "device not initialised";
      case -3:
         return "capture start error";
      case -4:
         return "unknown error";
      case -5:
         return "error stopping capture";
      case -6:
         return "read error into frameRead";
      case -7:
         return "VIDIOC_DQBUF error into frameRead";
      case -8:
         return "xioctl error into frameRead";
      case -9:
         return "try again into frameRead";
      case -10:
         return "buffer size error into frameRead";
   }
   return "no error";
}

/****************************************/
/****************************************/

struct SCameraThreadParams {
   pthread_mutex_t* DataMutex;
   unsigned char* Buffer;
};

static void* CameraThread(void* pvoid_params) {
   /* Get parameters */
   SCameraThreadParams* ptParams =
      reinterpret_cast<SCameraThreadParams*>(pvoid_params);
   /* Data collection loop */
   int nErrCode;
   while(1) {
      /* Cancellation point */
      pthread_testcancel();
      /* Get frame */
      nErrCode = take_one_image(ptParams->Buffer);
      if(nErrCode == 0) {
         /* Process frame */
         // TODO
         /* Cancellation point */
         pthread_testcancel();
         /* Set new readings */
         pthread_mutex_trylock(ptParams->DataMutex);
         // TODO Set readings
         pthread_mutex_unlock(ptParams->DataMutex);
      }
      else {
         LOGERR << "[WARNING] Error capturing camera frame: "
                << CaptureErrorMsg(nErrCode)
                << std::endl;
      }
   }
}

/****************************************/
/****************************************/

CRealKheperaIVCameraSensor::CRealKheperaIVCameraSensor(knet_dev_t* pt_dspic) :
   CRealKheperaIVDevice(NULL) {
}
   
/****************************************/
/****************************************/

CRealKheperaIVCameraSensor::~CRealKheperaIVCameraSensor() {
}

/****************************************/
/****************************************/

void CRealKheperaIVCameraSensor::Init(TConfigurationNode& t_node) {
   try {
      /* Parse XML */
      unsigned int unWidth = 640;
      unsigned int unHeight = 480;
      GetNodeAttributeOrDefault(t_node, "image_width",  unWidth,  unWidth);
      GetNodeAttributeOrDefault(t_node, "image_height", unHeight, unHeight);
      /* Initialize camera resources */
      int x = kb_camera_init(&unWidth, &unHeight);
      if(x < 0) {
         THROW_ARGOSEXCEPTION(InitErrorMsg(x));
      }
      m_pchBuffer = new unsigned char[3 * unWidth * unHeight];
      LOG << "[INFO] Camera initialized with image size ("
          << unWidth
          << ","
          << unHeight
          << ")" << std::endl;
      /* Create data mutex */
      if(pthread_mutex_init(&m_tDataMutex, NULL) != 0) {
         kb_camera_release();
         delete[] m_pchBuffer;
         THROW_ARGOSEXCEPTION("pthread_mutex_init: " << strerror(errno));
      }
      /* Spawn worker thread */
      SCameraThreadParams sCameraThreadParams;
      sCameraThreadParams.DataMutex = &m_tDataMutex;
      sCameraThreadParams.Buffer    = m_pchBuffer;
      if(pthread_create(&m_tThread, NULL, CameraThread, &sCameraThreadParams) != 0) {
         kb_camera_release();
         delete[] m_pchBuffer;
         THROW_ARGOSEXCEPTION("pthread_create: " << strerror(errno));
      }
      LOG << "[INFO] Camera started" << std::endl;
   }
   catch(CARGoSException& ex) {
      THROW_ARGOSEXCEPTION_NESTED("Error initializing the camera", ex);
   }
}

/****************************************/
/****************************************/

void CRealKheperaIVCameraSensor::Destroy() {
   /* Stop worker thread */
   pthread_cancel(m_tThread);
   pthread_join(m_tThread, NULL);
   /* Release camera resources */
   kb_camera_release();
   /* Dispose of image buffer */
   delete[] m_pchBuffer;
   LOG << "[INFO] Camera stopped" << std::endl;
}

/****************************************/
/****************************************/

void CRealKheperaIVCameraSensor::Do() {
   /* Take latest reading from worker thread */
   pthread_mutex_trylock(&m_tDataMutex);
   // TODO Get reading
   pthread_mutex_unlock(&m_tDataMutex);
}

/****************************************/
/****************************************/
