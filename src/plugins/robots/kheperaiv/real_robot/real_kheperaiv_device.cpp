#include "real_kheperaiv_device.h"

/****************************************/
/****************************************/

char CRealKheperaIVDevice::m_pchBuffer[100];

/****************************************/
/****************************************/

CRealKheperaIVDevice::CRealKheperaIVDevice(knet_dev_t* pt_dspic) :
   m_ptDSPic(pt_dspic) {
}

/****************************************/
/****************************************/
