/******************************************************************************
 FILE NAME         :  oamstrxh_trxdspcontroller.h
 PURPOSE           :  Header file for DspTrxController include files,function
                      declarations and HashDefs.
 PROJECT           :  BSS
 SUBSYSTEM         :  OAM
 AUTHOR            :  Nidhi Tomar
 CSCI ID           :
 VERSION           :  V0.1
*******************************************************************************/

#ifndef __OAMSCELLH_MAPLTRXPTRENT_H
#define __OAMSCELLH_MAPLTRXPTRENT_H

#ifdef CPLUSPLUS
EXTERN "C"
{
#endif

I_S32 CreateTrxhDspAvailabilityInd(I_U8 trxId);

I_S32 trxMsgHandler(I_U32 trxId);

#ifdef CPLUSPLUS
}
#endif


#endif


