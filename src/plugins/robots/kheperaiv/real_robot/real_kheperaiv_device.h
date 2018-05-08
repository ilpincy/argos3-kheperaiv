#ifndef REAL_KHEPERAIV_DEVICE_H
#define REAL_KHEPERAIV_DEVICE_H

#include <khepera/khepera.h>

class CRealKheperaIVDevice {

public:

   CRealKheperaIVDevice(knet_dev_t* pt_dspic) {}
   virtual ~CRealKheperaIVDevice() {}

   virtual void Do() = 0;

   inline knet_dev_t* GetDSPic() const {
      return m_ptDSPic;
   }

   inline char* GetBuffer() {
      return m_pchBuffer;
   }

private:

   knet_dev_t* m_ptDSPic;
   static char m_pchBuffer[100];
   
};

#endif // REAL_KHEPERAIV_DEVICE_H
