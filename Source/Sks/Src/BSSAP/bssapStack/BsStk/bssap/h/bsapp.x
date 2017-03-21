/*******************************************************************************
**      FILE NAME:
**          bsapp.x
**
**      DESCRIPTION:
**              Defines Api-Structure required by Bssap Stack and Bssap-User.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/


#ifndef __BSAPPX__
#define __BSAPPX__

#include "s7_typ.h"

typedef struct
{
    U8bit  error_code;
    U16bit  pcm;
    U8bit  ts;
    U8bit ssn;
    U32bit pc;
}
ERROR_DATA;

typedef struct
{
    U8bit  mapMsg[BSSAP_DATA_LEN];
    U16bit len;
}
MAP_DATA;

typedef struct
{
    U8bit  dtapMsg[BSSAP_DATA_LEN];
    U16bit len;
}
DTAP_DATA;

typedef struct
{
    U32bit   callrefId;
    U32bit   appId;
    U8bit  bssId;
    U8bit  mssgDisc;
    U8bit  mssgType;
    U8bit  hofacause;
    union
    {
        DTAP_DATA  DTAPdata;
        MAP_DATA   MAPdata;
        ERROR_DATA ERRdata;
    }
    u;
}
BSSAPData;

#if 0
/*Function prototype */
EXTERN Void BsDispatchDtapToApp ARGS((BsCallCb  *call,Data *databuff,MsgLen dataLen,U8bit msgType,BsIntfCb *intfCb));
EXTERN Void BsDispatchErrorToApp ARGS((BsCallCb *call,U8bit errType,U8bit errCode,U16bit cic,U8bit MssgType,BsIntfCb *intfCb));
EXTERN Void BsDispatchAOIPProtocolErrToApp ARGS((BsCallCb *call,U8bit errType,U8bit errCode,U32bit *callId,S16 callIdLen,U8bit MssgType,BsIntfCb *intfCb));

EXTERN Void BsDispatchTimeoutErrorToApp ARGS((BsCallCb *call,U8bit errType,U8bit errCode,U16bit cic,BsIntfCb *intfCb));
EXTERN Void BsDispatchMapErrToApp ARGS((BsCallCb *call,U8bit errCause,Data *databuff,MsgLen dataLen,U8bit msgType,BsIntfCb *intfCb));
EXTERN Void BsDispatchMapToApp ARGS((BsCallCb *call,Data *databuff,MsgLen dataLen,U8bit msgType,BsIntfCb *intfCb));
EXTERN Void BsDispatchMapUDTtoApp ARGS((U8bit msgType,Data *databuff,MsgLen dataLen,BsIntfCb *intfCb));
EXTERN Void BsProcessAppMsg ARGS((Data *buffer,MsgLen bufLen));
EXTERN Void BsDispatchSccpIndToApp ARGS((BsCallCb *call,U8bit msgType,U8bit cause,BsIntfCb *intfCb));
EXTERN Void BsDispatchSsnStatusToApp ARGS((Dpc pc,U8bit ssn,U8bit status,BsIntfCb *intfCb));
EXTERN Void BsDispatchPcStatusToApp ARGS((Dpc pc,U8bit status,BsIntfCb *intfCb));
EXTERN S16 BsPrepareAppEvt ARGS((Data *buffer,MsgLen bufLen));
EXTERN S16 cmPkBsAppReq ARGS((Pst *pst,Data *appBuf,MsgLen appBufLen));
EXTERN S16 cmUnPkBsAppReq ARGS((Pst *pst,Buffer *mBuf));

#endif /* Commented by Amaresh */
#endif /* end of __BSAPPX__*/
