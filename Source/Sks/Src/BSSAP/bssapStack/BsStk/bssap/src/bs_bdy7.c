/*******************************************************************************
**      FILE NAME:
**          bs_bdy7.c
**
**      DESCRIPTION:
**              This file defines the source code for start/stop the timers and the action
**              taken upon a timer's expiry used by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
/* header include files (.h) */

#include "lbs.h"           /* layer management                             */
#include "bs.h"            
#include "bs_err.h"      
#include "bsapp.h"    
#include "bssapcom.h"       
#include "bs_trace.h"

#include <sl.h>

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_api.h"
#include "bs_stgl.h"
#include "bs_msgst.h"
#include "bs_debug.h"

#include <pthread.h>
#include <netinet/in.h>

/* header/extern include files (.x) */
#include "lbs.x"           /* layer management                             */
#include "bs.x"           
#include "bsapp.x"    
#include "bssapcom.x"       
#include "bs_trace.x"

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)

SysAddr slfAddr;
#endif

#ifdef LOGGER_ON_SCREEN
#define LOG_PRINT(a,b,args...) printf(b,##args)
#endif



/* support functions */
void bsHandleAssignReqTimeout (U8bit * cb,S16bit event);
void bsHandleBlkUnBlkTimeout (U8bit * cb,S16bit event);
void bsHandleCktGrpBlkUnBlkTimeout (U8bit * cb,S16bit event);
void bsProcessBlockTimeout (BsCirCb *crec,S16bit event);
void bsProcessUnBlockTimeout (BsCirCb *crec,S16bit event);
void bsProcessCktGrpBlockTimeout (BsCirCb *crec,S16bit event);
void bsProcessCktGrpUnBlockTimeout (BsCirCb *crec,S16bit event);
void bsHandleResetTimeout (U8bit * cb,S16bit event);
void bsHandleResetGuardTimeout (U8bit * cb,S16bit event);
void bsHandleResetCktTimeout (U8bit * cb,S16bit event);
void bsHandleResetIPTimeout (U8bit * cb,S16bit event);
S16bit bsRmvConTq (BsCallCb *con,U8bit tmrNum);
S16bit bsRmvCirTq (BsCirCb *con,U8bit tmrNum);
S16bit bsRmvIntfTq (BsIntfCb *intf,U8bit tmrNum);
void bsStartIntfTmr(U8bit timer,BsIntfCb *cb);
void bsStartCirTmr(S16bit timer,BsCirCb *cir,BsIntfCb *cb);
extern int rem_pc;
extern int bsc_id;

/*
*
*       Fun:    bsHandleAssignReqTimeout
*
*       Desc:   Processes T10(Assign Request) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI
void bsHandleAssignReqTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleAssignReqTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
  BsCallCb *call = SS7_NULL;
  BsCallCb *nCb = SS7_NULL;
  U8bit cause;
  U16bit cic =0;
  BsIntfCb  *bsIntfCb = SS7_NULL;
  U32bit callRef = 0;
  U32bit callId = 0;
  U8bit msgtype = 0;

   nCb = (BsCallCb *) cb;
   cause = C_RADIO_INTERFACE_MSG_FAIL;
   
   callRef = nCb->suInstId;
   LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout(): ASSIGNMENT REQUEST Timeout:callref[%ld]\n",callRef);

   bsIntfCb = nCb->intfCb;
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout():Interface pointer is null");
     return ;
   }
   call = bsFindCall(bsIntfCb,callRef);  
   if(call)
   {
      cic = call->cic;
      callId = call->callId;
      if(cic)
      {

        LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout():ASSIGNMENT REQ Timeout for CIC %d \n",cic);
        if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cic].cic == cic))
        {
           BS_SET_CALLSTATE_IDLE(bsIntfCb->cicDataList[cic].flaglistSet);
        }
        else
        {
#if 0
            /*Raise Alarm to Stack Manager */
            msgtype = BSSAP_MSG_ASSIGN_REQUEST;
            bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&msgtype,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

            bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_CIC_CONTEXT_NOT_FOUND, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
        }
       LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout():Send Assignment fail by BSSAP stack for T10 Timeout\n"); 
       BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,bsIntfCb);
       BsDispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EASSREQFAIL,0,0,bsIntfCb);
      }
      else if(callId)
      {
	 LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout(): ASSIGNMENT REQ Timeout for CallId %d \n",callId);
         LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout():Send Assignment fail by BSSAP stack for T10 Timeout\n");
         BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,cause,SS7_NULL,0,bsIntfCb);
         BsDispatchAOIPProtocolErrToApp(call,BSSAP_MD_PROTOCOL,BSSAP_EASSREQFAIL,&callId,sizeof(U32bit),BSSAP_MSG_ASSIGN_REQUEST,bsIntfCb);

      }
      else
      {
         LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout(): Neither CallId nor CIC  found in the Call pointer\n");
         return ;
      }
    }
    else
    {
      LOG_PRINT(CRITICAL,"bsHandleAssignReqTimeout():Absence of Call");
      return ; 
    }
   return ; 
}
/*
*
*       Fun:    bsHandleBlkUnBlkTimeout
*
*       Desc:   Processes T1(Block Unblock) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsHandleBlkUnBlkTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleBlkUnBlkTimeout(cb, event)
U8bit *cb;
S16bit event;
#endif
{
  BsCirCb *nCb = SS7_NULL;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U16bit cic = 0;

  LOG_PRINT(CRITICAL,"BS: bsHandleBlkUnBlkTimeout():  Blk/UnBlk Timeout\n");

  nCb = (BsCirCb *) cb;
  cic = nCb->cic;  
  bsIntfCb = nCb->intfCb;
  if(cic)
  {
     if(bsIntfCb)
     {
         if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cic].cic == cic))
         {
           if(nCb->msgtype ==  BSSAP_MSG_BLOCK)
           {
              LOG_PRINT(CRITICAL,"BS: bsHandleBlkUnBlkTimeout(): ProcessBSSAP BLOCK Timeout for CIC[%lu]\n",cic);
              bsProcessBlockTimeout(nCb,event);
           }
           else if(nCb->msgtype ==  BSSAP_MSG_UNBLOCK)
           {
            LOG_PRINT(CRITICAL,"BS: bsHandleBlkUnBlkTimeout(): ProcessBSSAP UNBLOCK Timeout for CIC[%lu]\n",cic);
            bsProcessUnBlockTimeout(nCb,event);
           }
           else
           {   
              LOG_PRINT(CRITICAL,"BS: bsHandleBlkUnBlkTimeout(): NO  BLOCK/UNBLOCK stored for  CIC[%d]\n",cic);
              LOG_PRINT(INFO,"bsHandleBlkUnBlkTimeout():wrong msg");
           }
         }
         else
         {
              LOG_PRINT(CRITICAL,"bsHandleBlkUnBlkTimeout(): NO cic configured  CIC[%d]\n",cic);
         }
     }
     else
     {
       LOG_PRINT(CRITICAL,"bsHandleBlkUnBlkTimeout():Interface pointer is null");
     } 
  }
  return ;	
}

/*
*
*       Fun:    bsHandleCktGrpBlkUnBlkTimeout
*
*       Desc:   Processes T20(Circuit Group Block Unblock) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsHandleCktGrpBlkUnBlkTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleCktGrpBlkUnBlkTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
  BsCirCb *nCb = SS7_NULL;
  BsIntfCb *bsIntfCb = SS7_NULL;
  U16bit cic = 0;


  LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout(): CKT GROUP Blk/UnBlk Timeout\n");

  nCb = (BsCirCb *) cb;
  cic = nCb->cic;
  bsIntfCb = nCb->intfCb;
  if(cic)
  {
     if(bsIntfCb)
     {
         if((bsIntfCb->cicDataList != SS7_NULL) && (bsIntfCb->cicDataList[cic].cic == cic))
         {
           if(nCb->msgtype ==  BSSAP_MSG_CKT_GROUP_BLOCK)
           {
              LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout(): ProcessBSSAP CIRCUIT GROUP BLOCK Timeout for CIC[%d]",cic);
              bsProcessCktGrpBlockTimeout(nCb,event);
           }
           else if(nCb->msgtype ==  BSSAP_MSG_CKT_GRP_UNBLOCK)
           {
              LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout(): ProcessBSSAP CIRCUIT GROUP UNBLOCK Timeout for CIC[%d]\n",cic);
              bsProcessCktGrpUnBlockTimeout(nCb,event);
           }
           else
           {
              LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout():wrong msg");
           }
         }
         else
         {
            LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout(): NO cic configured  CIC[%d]\n",cic);
         }
     }
     else
     {
        LOG_PRINT(CRITICAL,"bsHandleCktGrpBlkUnBlkTimeout(): No interface found (bsIntfCb NULL) for CIC [%d]",cic);
     }
  }
  return ;

}
/*
*
*       Fun:    bsProcessBlockTimeout
*
*       Desc:   Processes T1(Block) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsProcessBlockTimeout
(
BsCirCb *crec,
S16bit event
)
#else
void bsProcessBlockTimeout(crec,event)
BsCirCb *crec;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   U8bit event1;
  

  LOG_PRINT(CRITICAL,"bsProcessBlockTimeout(): BLOCK Timeout\n");
   event1 = (U8bit)event;
  
   bsIntfCb = crec->intfCb;
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsProcessBlockTimeout(): NO Interface found(bsIntfCb NULL)");
     return ;
   }
   if(crec->blockReqRetryCount < BSSMAP_REQ_TRIES)
   {
        crec->blockReqRetryCount++;
        bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);
        LOG_PRINT(CRITICAL,"bsProcessBlockTimeout(): Sending BLOCK REQ AGAIN for CIC[%d]\n",crec->cic);
        ret = BsSendUDataReq(crec->databuf,crec->datalen,bsIntfCb);
        /*Increment peg counter */
        BsIncrPegsCounter(BSSMAP,BSSAP_MSG_BLOCK,TRANSMIT,bsIntfCb);
   }
   else
   {
     LOG_PRINT(CRITICAL,"bsProcessBlockTimeout():retry exceed");
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_CIC, (PTR) &crec->cic,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_BLOCK_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 
    LOG_PRINT(CRITICAL,"bsProcessBlockTimeout(): Timeout no Block Ack received,exceed blockReqRetryCount[%d]\n",crec->blockReqRetryCount);
    BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENOBLKACK,crec->cic,BSSAP_MSG_BLOCK,bsIntfCb);
   }
     return ;
}
/*
*
*       Fun:    bsProcessUnBlockTimeout
*
*       Desc:   Processes T1(UnBlock) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsProcessUnBlockTimeout
(
BsCirCb *crec,
S16bit event
)
#else
void bsProcessUnBlockTimeout(crec,event)
BsCirCb *crec;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   U8bit event1;

   LOG_PRINT(CRITICAL,"bsProcessUnBlockTimeout(): UNBLOCK Timeout\n");
   event1 = (U8bit)event;
   
   bsIntfCb = crec->intfCb;
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsProcessUnBlockTimeout(): NO Interface found(bsIntfCb NULL) for CIC[%d]\n",crec->cic);
     return ;	
   }
  if(crec->unBlockReqRetryCount < BSSMAP_REQ_TRIES)
  {
        crec->unBlockReqRetryCount++;
        bsStartCirTmr(BSSAP_T_1,crec,bsIntfCb);
        LOG_PRINT(CRITICAL,"bsProcessUnBlockTimeout(): Sending UNBLOCK REQ AGAIN\n");
        ret = BsSendUDataReq(crec->databuf,crec->datalen,bsIntfCb);
        /*Increment peg counter */
        BsIncrPegsCounter(BSSMAP,BSSAP_MSG_UNBLOCK,TRANSMIT,bsIntfCb);
  }
  else
  {
     LOG_PRINT(CRITICAL,"bsProcessGrpUnBlockTimeout():retry exceed");
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_CIC, (PTR) &crec->cic,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_UNBLOCK_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 

/*     printf("bsProcessUnBlockTimeout: Timeout no UnBlock Ack received,exceed unBlockReqRetryCount[%d]\n",crec->unBlockReqRetryCount);*/
     BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENOUNBLKACK,crec->cic,BSSAP_MSG_UNBLOCK,bsIntfCb);
  }
     return ;	
}
/*
*
*       Fun:    bsProcessCktGrpBlockTimeout
*
*       Desc:   Processes T20(Circuit Group Block) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsProcessCktGrpBlockTimeout
(
BsCirCb *crec,
S16bit event
)
#else
void bsProcessCktGrpBlockTimeout(crec,event)
BsCirCb *crec;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   U8bit event1;

   LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout(): CKT GRP BLOCK Timeout\n");
   event1 = (U8bit)event;

   bsIntfCb = crec->intfCb;
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout():INTF CB is NULL");
     return ;
   }
   LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout(): CIRCUIT GROUP BLOCK Timeout For CIC[%d] : Timeout tries [%d]\n",crec->cic,crec->cktGrpblockReqRetryCount);
   if(crec->cktGrpblockReqRetryCount < BSSMAP_REQ_TRIES)
   {
        crec->cktGrpblockReqRetryCount++;
        bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);
        LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout(): Sending CIRCUIT GROUP BLOCK REQ AGAIN for CIC[%d]\n",crec->cic);
        ret = BsSendUDataReq(crec->databuf,crec->datalen,bsIntfCb);
        /*Increment peg counter */
        BsIncrPegsCounter(BSSMAP,BSSAP_MSG_CKT_GROUP_BLOCK,TRANSMIT,bsIntfCb);
   }
   else
   {
     LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout():retry exceed");
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_CIC, (PTR) &crec->cic,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_BLOCK_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 

     LOG_PRINT(CRITICAL,"bsProcessCktGrpBlockTimeout(): Timeout no Block Ack received,exceed cktGrpblockReqRetryCount[%d]\n",crec->cktGrpblockReqRetryCount);
     BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPBLKACK,crec->cic,BSSAP_MSG_CKT_GROUP_BLOCK,bsIntfCb);
   }
   return ;
}
/*
*
*       Fun:    bsProcessCktGrpUnBlockTimeout
*
*       Desc:   Processes T20(Circuit Group UnBlock) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsProcessCktGrpUnBlockTimeout
(
BsCirCb *crec,
S16bit event
)
#else
void bsProcessCktGrpUnBlockTimeout(crec,event)
BsCirCb *crec;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   U8bit event1;

   LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout(): CKT GRP UNBLOCK Timeout\n");
   event1 = (U8bit)event;

   bsIntfCb = crec->intfCb;
   if(bsIntfCb == NULL)
   {
      LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout(): NO Interface found(bsIntfCb NULL) for CIC[%d]\n",crec->cic);
      return ;
   }
   LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout():CIRCUIT GROUP UNBLOCK Timeout for CIC[%d]: Timeout tries [%d]\n",crec->cic,crec->cktGrpUnblockReqRetryCount);
  if(crec->cktGrpUnblockReqRetryCount < BSSMAP_REQ_TRIES)
  {
        crec->cktGrpUnblockReqRetryCount++;
        bsStartCirTmr(BSSAP_T_20,crec,bsIntfCb);
        LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout(): Sending CIRCUIT GROUP UNBLOCK REQ AGAIN\n");
        ret = BsSendUDataReq(crec->databuf,crec->datalen,bsIntfCb);
        /*Increment peg counter */
        BsIncrPegsCounter(BSSMAP,BSSAP_MSG_CKT_GRP_UNBLOCK,TRANSMIT,bsIntfCb);
  }
  else
  {
     LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout():rety exceed");
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_CIC, (PTR) &crec->cic,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_UNBLOCK_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 

     LOG_PRINT(CRITICAL,"bsProcessCktGrpUnBlockTimeout(): Timeout no UnBlock Ack received,exceed cktGrpUnblockReqRetryCount[%d]\n",crec->cktGrpUnblockReqRetryCount);
     BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENOCKTGRPBLKACK,crec->cic,BSSAP_MSG_CKT_GRP_UNBLOCK,bsIntfCb);
 }
   return ;
}

/*
*
*       Fun:    bsHandleResetTimeout
*
*       Desc:   Processes T4(Reset) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsHandleResetTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleResetTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
   BsIntfCb *bsLIntfCb = SS7_NULL;
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   U8bit event1;
   
   LOG_PRINT(CRITICAL,"bsHandleResetTimeout(): RESET Timeout\n");
   event1 = (U8bit)event;
   bsLIntfCb = (BsIntfCb *) cb;

   bsIntfCb = bsGetIntfPtr(bsc_id,STACK_ITU);
   if(bsIntfCb == SS7_NULL)
    {
      LOG_PRINT(CRITICAL,"bsHandleResetTimeout():No Interface configured \n");
      return SS7_FAILURE;
    }

   
   if(bsLIntfCb->resetRetryCount < BSSMAP_REQ_TRIES)
   {
      bsIntfCb->resetRetryCount = bsLIntfCb->resetRetryCount;
      bsLIntfCb->rstSndtimerId = BSSAP_T_4;     
/* Global BsIntfCb Updated */
      bsIntfCb->resetRetryCount++;
      bsIntfCb->rstSndtimerId = BSSAP_T_4;
      bsIntfCb->databuf = (U8bit *)bssap_malloc(bsLIntfCb->datalen);
      if(bsIntfCb->databuf == SS7_NULL)
      {
      	LOG_PRINT(CRITICAL,"bsHandleResetTimeout():[malloc_fail] \n");
      	return (SS7_FAILURE);
      }
      bsIntfCb->datalen = bsLIntfCb->datalen;
      ss7_memcpy((U8bit*)bsIntfCb->databuf,(U8bit*)bsLIntfCb->databuf,bsLIntfCb->datalen);
      bssap_free(bsLIntfCb->databuf);
      bsLIntfCb->databuf = SS7_NULL;
      bsLIntfCb->datalen = 0;  
/* Global BsIntfCb Updated */
     
      bsStartIntfTmr(BSSAP_T_4,bsIntfCb);
      bsIntfCb->rstSndtimerId = BSSAP_T_4;
      LOG_PRINT(CRITICAL,"bsHandleResetTimeout(): Sending RESET REQ AGAIN: resetRetryCount[%d]\n",bsIntfCb->resetRetryCount);
      /*Sending RESET REQ AGAIN*/
      LOG_PRINT(INFO,"BS:MSG TO MSC: UDT [BSSMAP] [BSSAP_MSG_RESET] \n");
      ret = BsSendUDataReq(bsIntfCb->databuf,bsIntfCb->datalen,bsIntfCb);
      /*Increment peg counter */
      BsIncrPegsCounter(BSSMAP,BSSAP_MSG_RESET,TRANSMIT,bsIntfCb);
   }
   else
   {
     LOG_PRINT(CRITICAL,"bsHandleResetTimeout():Timeout no Reset Ack received,exceed resetRetryCount[%d]\n",bsIntfCb->resetRetryCount);
      /* resetting the value of resetRetryCount */
      bsIntfCb->resetRetryCount = 0;
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_SWTCH, (PTR) &bsIntfCb->swtch,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_RESET_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 
     BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENORESETACK,0,BSSAP_MSG_RESET,bsIntfCb);
   }
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
   if(ret == RFAILED)
   {
     LOG_PRINT(CRITICAL,"BSSAP_HA:bsHandleResetTimeout(): SendInterfaceAddUpdateToPeer Failed \n");
   }
#endif

   return ;	
}

/*
*
*       Fun:    bsHandleResetIPTimeout
*
*       Desc:   Processes T_RBSC(Reset IP) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsHandleResetIPTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleResetIPTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   S16bit ret;
   BSSAP_IE ies[30];
   BSSAP_Hdr hdr;
   S16bit iecount = 0;
   S16bit  callIdLen;
   U32bit CallIdListBuf[255];
   BSSAP_IE *ieData = SS7_NULL;
   U32bit i = 0;
   U8bit event1;

   LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): RESET IP Timeout\n");
   event1 = (U8bit)event;
   bsIntfCb = (BsIntfCb *) cb;
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): NO Interface found(NULL)");
     return ;
   }
   if(bsIntfCb->resetIPRetryCount < BSSMAP_REQ_TRIES)
   {
      bsIntfCb->resetIPRetryCount++;
      bsStartIntfTmr(BSSAP_T_RBSC,bsIntfCb);
      LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): Sending RESET REQ AGAIN\n");
      /*Sending RESET IP REQ AGAIN*/
      ret = BsSendUDataReq(bsIntfCb->databuf,bsIntfCb->datalen,bsIntfCb);
      /*Increment peg counter */
      BsIncrPegsCounter(BSSMAP,BSSAP_MSG_RESET_IP,TRANSMIT,bsIntfCb);
   }
   else
   {

     LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): Timeout no Reset Ack received,exceed resetRetryCount[%d]\n",bsIntfCb->resetIPRetryCount);
     /* resetting the value of resetRetryCount */
     bsIntfCb->resetIPRetryCount = 0;

     memset((U8bit *)&ies, '\0',  30);
     memset((U8bit *)&hdr, '\0',  sizeof(BSSAP_Hdr));
     memset((U8bit *)&CallIdListBuf, '\0', 255);
     ret = BsDecode(bsIntfCb->databuf,bsIntfCb->datalen,ies,&iecount,&hdr); 
     if(ret != SS7_SUCCESS)
     {
        LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): BsDecode failed for RESET IP\n");
        return ;
     }
     LOG_PRINT(CRITICAL,"bsHandleResetIPTimeout(): calling BsFindIE BSSAP_IEI_CALLID_LIST\n");
     ieData = (BSSAP_IE*)BsFindIE(ies,iecount,BSSAP_IEI_CALLID_LIST);
     if(ieData)
     {
        callIdLen = ieData->param_length; 
     /*      printf("#####CallID length [%ld] \n",callIdLen);*/
        for(i = 0; i < callIdLen/4 ; i++)
        {
/*           printf("#####Copying Call Id [%ld] \n",ieData->param_data.call_id_list.calllist[i].callId);*/
           ss7_memcpy((U8bit*)&CallIdListBuf[i],(U8bit*)&ieData->param_data.call_id_list.calllist[i].callId,sizeof(BSSAP_CallIdentifier)); 
        }
     }
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_SWTCH, (PTR) &bsIntfCb->swtch,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_RESETIP_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 

     BsDispatchAOIPProtocolErrToApp(SS7_NULL,BSSAP_MD_PROTOCOL,BSSAP_ENORESETIPACK,CallIdListBuf,callIdLen,BSSAP_MSG_RESET_IP,bsIntfCb);
   }
   return ;
}
/*
*
*       Fun:    bsHandleResetGuardTimeout
*
*       Desc:   Processes T13(Reset guard) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI
void bsHandleResetGuardTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleResetGuardTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   BsIntfCb  *intfCb = SS7_NULL;
   bsIntfCb = (BsIntfCb *) cb;
   LOG_PRINT(CRITICAL,"bsHandleResetGuardTimeout(): RESET GUARD Timeout\n");
   if(bsIntfCb == NULL)
   {
     LOG_PRINT(CRITICAL,"bsHandleResetGuardTimeout(): NO Interface found(bsIntfCb NULL)\n");
     return ;
   }
   LOG_PRINT(CRITICAL,"bsHandleResetGuardTimeout(): GUARD TIMER T13 EXPIRES for DPC[%d] INTFID[%d] GCNID[%d]\n",bsIntfCb->phyDpc,bsIntfCb->intfId,bsIntfCb->bscId);
   bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;

   intfCb = bsGetIntfPtrFrmDPC(rem_pc,STACK_ITU);
   if((intfCb == SS7_NULL))
   {
      LOG_PRINT(CRITICAL,"bsHandleResetGuardTimeout(): bsGetIntfPtrFrmDPC Failed, No interface present");
      return (SS7_SUCCESS);
   }
   intfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
   intfCb->t13.timer_id_key = SS7_FALSE;
   BsDispatchTimeoutErrorToApp(NULL,BSSAP_MD_TIMEOUT,BSSAP_T_13,0,bsIntfCb);
}
/*
*
*       Fun:    bsHandleResetCktTimeout
*
*       Desc:   Processes T19(Reset_ckt) Timing Expiry Events
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/
#ifdef ANSI_PROTO
void bsHandleResetCktTimeout
(
U8bit * cb,
S16bit event
)
#else
void bsHandleResetCktTimeout(cb, event)
U8bit * cb;
S16bit event;
#endif
{
   BsIntfCb *bsIntfCb = SS7_NULL;
   BsCirCb *crec = SS7_NULL;
   S16bit ret;
   U16bit cic = 0;
   U8bit event1;
   
   LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout(): RESET CKT Timeout\n");
  event1 = (U8bit)event;
  crec = (BsCirCb *) cb;
  if(crec == SS7_NULL)
  {
     LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout():crec null");
     return ;
  }
  cic = crec->cic;

  LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout(): Reset Circuit timeout for CIC[%d]\n",cic);
  bsIntfCb = crec->intfCb;

   if(bsIntfCb)
   {
      LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout(): Interface found(bsIntfCb)");
   }
   else
   {
     LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout():Intf null");
     return ;
   }
   if(crec->resetCktRetryCount < BSSMAP_REQ_TRIES)
   {
      crec->resetCktRetryCount++;
      bsStartCirTmr(BSSAP_T_19,crec,bsIntfCb);
      LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout(): Sending RESET CKT REQ AGAIN\n");
      /*Sending RESET CKT REQ AGAIN*/
      ret = BsSendUDataReq(crec->databuf,crec->datalen,bsIntfCb);
      /*Increment peg counter */
      BsIncrPegsCounter(BSSMAP,BSSAP_MSG_RESET_CIRCUIT,TRANSMIT,bsIntfCb);
   }
   else
   {
     LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout():No Reset Ack");
#if 0
     /*Raise Alarm to Stack Manager */
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_EVENT, (PTR)&event1,
                   LBS_USTA_DGNVAL_CIC, (PTR) &cic,
                   LBS_USTA_DGNVAL_DPC, (PTR) &bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_TIME_OUT_NO_RESET_CKT_ACK_RECEIVED, LCM_CAUSE_TMR_EXPIRED,TRUE);
#endif 

   LOG_PRINT(CRITICAL,"bsHandleResetCktTimeout(): Timeout no Reset Circuit Ack received,exceed resetCktRetryCount[%d]\n",crec->resetCktRetryCount);
     BsDispatchErrorToApp(SS7_NULL, BSSAP_MD_PROTOCOL, BSSAP_ENORESETCKTACK,0,BSSAP_MSG_RESET_CIRCUIT,bsIntfCb);
   }
   return ;
}

/*
*
*       Fun:   bsStartConTmr
*
*       Desc:  start network connection timer
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  
*
*/

#ifdef ANSI_PROTO
void bsStartConTmr
(
U8bit timer,
BsCallCb *con,
BsIntfCb *cb
)
#else
void bsStartConTmr(timer, con, cb)
U8bit timer;
BsCallCb *con;
BsIntfCb *cb;
#endif
{
   U16bit wait;
   error_t  p_ecode ;
   return_t    result = SS7_SUCCESS;
   timer_id_t  bs_timer_key =  SS7_FALSE;
   sl_time_val tv;
   pvoid   timer_start_buf;
   unsigned char* t_buf;
   s7_len_t         mesg_len;

   if (cb == SS7_NULL)
   {
      LOG_PRINT(CRITICAL,"bsStartConTmr():cb null \n");
      return ;
   }
   wait = 0;
   switch(timer)
   {
      case BSSAP_T_7:
         if (cb->t7.enb == SS7_TRUE)
         {
            wait = cb->t7.val;
            wait = wait * 100;
            LOG_PRINT(INFO,"bsStartConTmr(): callrefId[%d] T7 VAL %d \n",con->suInstId,wait);
         }
         break;
      case BSSAP_T_8:
         if (cb->t8.enb == SS7_TRUE)
         { 
            wait = cb->t8.val;
            wait = wait * 100;
            LOG_PRINT(INFO,"bsStartConTmr(): callrefId[%d] T8 VAL %d \n",con->suInstId,wait);
         }
         break;
      case BSSAP_T_10:
         if (cb->t10.enb == SS7_TRUE)
         {
            wait = cb->t10.val;
            wait = wait * 100;
            LOG_PRINT(INFO,"bsStartConTmr(): callrefId[%d] T10 VAL %d \n",con->suInstId,wait);
         }
         break;
      case BSSAP_T_11:
         if (cb->t11.enb == SS7_TRUE)
         {
            wait = cb->t11.val;
            wait = wait * 100;
            LOG_PRINT(INFO,"bsStartConTmr(): callrefId[%d] T11 VAL %d \n",con->suInstId,wait);
         }
         break;
      default:
         LOG_PRINT(CRITICAL,"bsStartConTmr():invalid timer \n");
         return;;
   }
   if (wait != 0)
   {
    mesg_len    = 6 + sizeof(BsCallCb);
    timer_start_buf =   ss7_mem_get(mesg_len);
    t_buf   = timer_start_buf;

  /* Create the buffer in API format */
    *(t_buf)      =   SS7_TIMER_API_ID;
    *(t_buf + 1)  =   1;
    *(t_buf + 2)  =   1;
    *(t_buf + 3)  =   (mesg_len & 0x00FF);
    *(t_buf + 4)  =   ((mesg_len & 0xFF00) >> 8 );
    *(t_buf + 5)  =   timer;

    ss7_memcpy((void *)(t_buf + 6),(void *)con, sizeof(BsCallCb));
    /* Assuming timer_val expresses in 10s of millisecond*/
    tv.s = wait / 100;
    tv.us = (wait % 100) * 10000;
    bs_timer_key = (timer_id_t)sl_timer_start (&tv, timer_start_buf);

    if (result == SS7_SUCCESS)
    {

      switch(timer)
    {
        case BSSAP_T_7:
         if (cb->t7.enb == SS7_TRUE)
         {
             con->timer_key[0] = bs_timer_key;
         }
         break;
      case BSSAP_T_8:
         if (cb->t8.enb == SS7_TRUE)
         {
             con->timer_key[1] = bs_timer_key;
         }
         break;
      case BSSAP_T_10:
         if (cb->t10.enb == SS7_TRUE)
         {
             con->timer_key[2] = bs_timer_key;
         }
         break;
      case BSSAP_T_11:
         if (cb->t11.enb == SS7_TRUE)
         {
             con->timer_key[3] = bs_timer_key;
         }
         break;
			
      default:
         LOG_PRINT(CRITICAL,"bsStartConTmr():invalid timer \n");
         return ;
    	}

  	 
    }
    else
    {
      LOG_PRINT(CRITICAL,"bsStartConTmr():Timer Start Failure for BsCallCb\n");
    }
  
    if (result == SS7_SUCCESS)
    {
        con->timerId = timer;
      LOG_PRINT(INFO,"bsStartConTmr(): STARTED TIMER[%s] for callrefId[%d] \n",BS_PRINT_TMR_EVT_STR(timer),con->suInstId);
    }
    else
    {
        LOG_PRINT(CRITICAL,"bsStartConTmr():Timer Start Failure for BsCallCb\n");
    }
 
   }
   else
   {
      LOG_PRINT(INFO,"bsStartConTmr():zero time \n");
   }
   return ;
} /* end of bsStartConTmr */

/*
*
*       Fun:    bsStopConTmr
*
*       Desc:   Stops all Connection Timers
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
 void bsStopConTmr
(
BsCallCb *con,
S16bit timer
)
#else
void bsStopConTmr(con, timer)
BsCallCb *con;
S16bit timer;
#endif
{
   U8bit tmrNum;
   error_t  p_ecode ;

   if(timer != BSSAP_INVALID_TMRID)
   {
     bsRmvConTq(con, timer);
   }
   return ;
} /* end of bsStopConTmr */

/*
*
*       Fun:    bsRmvConTq
*
*       Desc:   Removes Connection from Timing Queue
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
S16bit bsRmvConTq
(
BsCallCb *con,
U8bit tmrNum
)
#else
S16bit bsRmvConTq(con, tmrNum)
BsCallCb *con;
U8bit tmrNum;
#endif
{
   error_t  p_ecode ;
   return_t    result = SS7_SUCCESS ;
   timer_id_t  timer_id;

   LOG_PRINT(INFO,"BS: bsRmvConTq(): STOPPING TIMER[%s] tmrNum[%d] \n",BS_PRINT_TMR_EVT_STR(tmrNum),tmrNum);

   switch (tmrNum)
    {
        case BSSAP_T_7:
             timer_id = con->timer_key[0];
         break;
      case BSSAP_T_8:
             timer_id = con->timer_key[1];
         break;
      case BSSAP_T_10:
             timer_id = con->timer_key[2];
         break;
      case BSSAP_T_11:
             timer_id = con->timer_key[3];
         break;
      default:
         LOG_PRINT(INFO,"bsRmvConTq():invalid timer \n");
         return ;
     }
    LOG_PRINT(INFO,"bsRmvConTq():Timer-Key to stop the timer %ul \n",timer_id);
    if (timer_id != SS7_FALSE)
   {
    result = ss7_stop_timer (timer_id, p_ecode) ;
   }
   else
   {
       LOG_PRINT(INFO,"bsRmvConTq():Timer Key is SS7_FALSE \n");
       return (SS7_SUCCESS);
   }
   if (result != SS7_SUCCESS)
  {
    LOG_PRINT(CRITICAL,"bsRmvConTq()::ss7_stop_timer failed ,Couldn't stop Timer,tmrNum[%d]\n",tmrNum);
    return(SS7_FAILURE);
  }
  else
  {
    LOG_PRINT(INFO,"bsRmvConTq()::STOPPED [%s] Timer Successfully having ,tmrNum[%d]\n",BS_PRINT_TMR_EVT_STR(tmrNum),tmrNum);
    con->timerId = BSSAP_INVALID_TMRID;
    return (SS7_SUCCESS) ;
  }

} /* end of bsRmvConTq */
/*
*
*       Fun:   bsStartCirTmr
*
*       Desc:  start timer for a particular circuit
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:
*
*/

#ifdef ANSI_PROTO
void bsStartCirTmr
(
S16bit timer,
BsCirCb *cir,
BsIntfCb *cb
)
#else
void bsStartCirTmr(timer, cir, cb)
S16bit timer;
BsCirCb *cir;
BsIntfCb *cb;
#endif
{
   U16bit   wait;
   error_t  p_ecode;
   return_t    result = SS7_SUCCESS;
   timer_id_t  bs_timer_key =  SS7_FALSE;
   sl_time_val tv;
   pvoid   timer_start_buf;
   unsigned char* t_buf;
   s7_len_t         mesg_len;


   if (cb == SS7_NULL)
   {
      LOG_PRINT(INFO,"bsStartCirTmr():cb null \n");
      return ;
   }
   wait = 0;
   switch(timer)
   {
      case BSSAP_T_1:
         if (cb->t1.enb == SS7_TRUE)
         {
            wait = cb->t1.val;
            wait = wait * 100;
         }
         break;
      case BSSAP_T_19:
         if (cb->t19.enb == SS7_TRUE)
         {
            wait = cb->t19.val;
            wait = wait * 100;
         }
         break;
      case BSSAP_T_20:
         if (cb->t20.enb == SS7_TRUE)
         {
            wait = cb->t20.val;
            wait = wait * 100;
         }
         break;
      default:
       LOG_PRINT(INFO,"bsStartCirTmr():invalid timer \n");
      return ;
   }
   if (wait != 0)
   {
		mesg_len    = 6 + sizeof(BsCirCb);
    timer_start_buf =   ss7_mem_get(mesg_len);
    t_buf   = timer_start_buf;

  /* Create the buffer in API format */
    *(t_buf)      =   SS7_TIMER_API_ID;
    *(t_buf + 1)  =   1;
    *(t_buf + 2)  =   1;
    *(t_buf + 3)  =   (mesg_len & 0x00FF);
    *(t_buf + 4)  =   ((mesg_len & 0xFF00) >> 8 );
    *(t_buf + 5)  =   timer;

    ss7_memcpy((void *)(t_buf + 6),(void *)cir, sizeof(BsCirCb));
    /* Assuming timer_val expresses in 10s of millisecond*/
    tv.s = wait / 100;
    tv.us = (wait % 100) * 10000;
    bs_timer_key = (timer_id_t)sl_timer_start (&tv, timer_start_buf);

 //LOG_PRINT(DEBUG,"[ENCAPS:: ] timer_key value after sl_timer_start with Timer-Id is %ul %d ",bs_timer_key,timer);
if (result == SS7_SUCCESS)
  {
      /*  cb->rstRcvtimerId = timer;*/
    switch(timer)
    {

      case BSSAP_T_1:
         if (cb->t1.enb == SS7_TRUE)
         {
             cir->timer_key[0] = bs_timer_key; 
         }
         break;
     case BSSAP_T_19:
         if (cb->t19.enb == SS7_TRUE)
         {
             cir->timer_key[1] = bs_timer_key; 
         }
         break;
     case BSSAP_T_20:
         if (cb->t20.enb == SS7_TRUE)
         {
             cir->timer_key[2] = bs_timer_key; 
         }
         break;
		     
     default:
         LOG_PRINT(CRITICAL,"bsStartCirTmr():invalid timer \n");
         return ;
     }
   }
   else
   {
      LOG_PRINT(INFO,"bsStartCirTmr():Timer Start Failure for BsCirCb\n");
   }
   if (result == SS7_SUCCESS)
     {
        cir->timerId = timer;
      LOG_PRINT(INFO,"bsStartCirTmr(): STARTED TIMER[%s] for intfCb[%d] CIC[%d] \n",BS_PRINT_TMR_EVT_STR(timer),cb->intfId,cir->cic);
     }
     else
     {
        LOG_PRINT(CRITICAL,"bsStartCirTmr():Timer Start Failure for BsCirCb\n");
     }

   }
   else
   {
      LOG_PRINT(INFO,"bsStartCirTmr():zero time \n");
   }
   return ;
} /* end of bsStartCirTmr */
/*
*
*       Fun:   bsStartIntfTmr
*
*       Desc:  start timer for a particular interface
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:
*
*/
#ifdef ANSI_PROTO
void bsStartIntfTmr
(
U8bit timer,
BsIntfCb *cb
)
#else
void bsStartIntfTmr(timer,cb)
U8bit timer;
BsIntfCb *cb;
#endif
{
   U16bit      wait;
   error_t     p_ecode;
   return_t    result = SS7_SUCCESS;
   timer_id_t  bs_timer_key =  SS7_FALSE;
   sl_time_val tv;
   pvoid   timer_start_buf;
   unsigned char* t_buf;
   s7_len_t         mesg_len;

   if (cb == SS7_NULL)
   {
      LOG_PRINT(INFO,"bsStartIntfTmr():cb null\n");
      return ;
   }
   wait = 0;
   switch(timer)
   {
      case BSSAP_T_4:
         if (cb->t4.enb == SS7_TRUE)
         {
            wait = cb->t4.val;
	    wait = wait * 100;	
            LOG_PRINT(INFO,"bsStartIntfTmr(): intfId[%d] T7 VAL %d \n",cb->intfId,wait);
         }
         break;
      case BSSAP_T_13:
         if (cb->t13.enb == SS7_TRUE)
         {
            wait = cb->t13.val;
	    wait = wait * 100;	
            LOG_PRINT(INFO,"bsStartIntfTmr(): intfId[%d] T13 VAL %d \n",cb->intfId,wait);
         }
         break;
      case BSSAP_T_17:
         if (cb->t17.enb == SS7_TRUE)
         {
            wait = cb->t17.val;
	    wait = wait * 100;	
            LOG_PRINT(INFO,"bsStartIntfTmr(): intfId[%d] T17 VAL %d \n",cb->intfId,wait);
         }
         break;
      case BSSAP_T_18:
         if (cb->t18.enb == SS7_TRUE)
         {
            wait = cb->t18.val;
	    wait = wait * 100;	
            LOG_PRINT(INFO,"bsStartIntfTmr(): intfId[%d] T18 VAL %d \n",cb->intfId,wait);
         }
         break;
     case BSSAP_T_RBSC:
         if (cb->trbsc.enb == SS7_TRUE)
         {
            wait = cb->trbsc.val;
	    wait = wait * 100;	
            LOG_PRINT(INFO,"bsStartIntfTmr(): intfId[%d] Trbsc VAL %d \n",cb->intfId,wait);
         }
         break;
      default:
        LOG_PRINT(INFO,"bsStartIntfTmr():invalid timer \n");
      return ;
   }
   if (wait != 0)
   {
    mesg_len    = 6 + sizeof(BsIntfCb);
    timer_start_buf =   ss7_mem_get(mesg_len);
    t_buf   = timer_start_buf;

  /* Create the buffer in API format */
    *(t_buf)      =   SS7_TIMER_API_ID;
    *(t_buf + 1)  =   1;
    *(t_buf + 2)  =   1;
    *(t_buf + 3)  =   (mesg_len & 0x00FF);
    *(t_buf + 4)  =   ((mesg_len & 0xFF00) >> 8 );
    *(t_buf + 5)  =   timer;

    ss7_memcpy((void *)(t_buf + 6),(void *)cb, sizeof(BsIntfCb));
    /* Assuming timer_val expresses in 10s of millisecond*/
    tv.s = wait / 100;
    tv.us = (wait % 100) * 10000;
    bs_timer_key = (timer_id_t)sl_timer_start (&tv, timer_start_buf);


     if (result == SS7_SUCCESS)
     {
      /*  cb->rstRcvtimerId = timer;*/
   	switch(timer)
   	{
      	case BSSAP_T_4:
         if (cb->t4.enb == SS7_TRUE)
         {
             cb->t4.timer_id_key = bs_timer_key;
         }
         break;
      case BSSAP_T_13:
         if (cb->t13.enb == SS7_TRUE)
         {
             cb->t13.timer_id_key = bs_timer_key;
         }
         break;
      case BSSAP_T_17:
         if (cb->t17.enb == SS7_TRUE)
         {
             cb->t17.timer_id_key = bs_timer_key;
         }
         break;
      case BSSAP_T_18:
         if (cb->t18.enb == SS7_TRUE)
         {
             cb->t18.timer_id_key = bs_timer_key;
         }
         break;
     case BSSAP_T_RBSC:
         if (cb->trbsc.enb == SS7_TRUE)
         {
            cb->trbsc.timer_id_key = bs_timer_key;
         }
         break;
      default:
         LOG_PRINT(INFO,"bsStartIntfTmr():invalid timer \n");
         return ;
     }
      LOG_PRINT(INFO,"bsStartIntfTmr(): STARTED TIMER[%s] for intfId[%d] \n",BS_PRINT_TMR_EVT_STR(timer),cb->intfId);
   }
   else
   {
      LOG_PRINT(INFO,"bsStartIntfTmr():Timer Start Failure for intfId[%d]\n",cb->intfId);
   }

   }
   else
   {
      LOG_PRINT(INFO,"bsStartIntfTmr():Invalid time \n");
   }
   return ;

}
/*
*
*       Fun:    bsStopCirTmr
*
*       Desc:   Stops all Connection Timers
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
void bsStopCirTmr
(
BsCirCb *cir,
S16bit timer
)
#else
void bsStopCirTmr(cir, timer)
BsCirCb *cir;
S16bit timer;
#endif
{
   U8bit tmrNum;

   bsRmvCirTq(cir, timer);
	 return;
} /* end of bsStopCirTmr */
/*
*
*       Fun:    bsRmvCirTq
*
*       Desc:   Removes Circuit from Timing Queue
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
S16bit bsRmvCirTq
(
BsCirCb *cir,
U8bit tmrNum
)
#else
S16bit bsRmvCirTq(cir, tmrNum)
BsCirCb *cir;
U8bit tmrNum;
#endif
{
   error_t  p_ecode ;
   return_t    result = SS7_SUCCESS ;
   timer_id_t  timer_id;

   
     LOG_PRINT(INFO,"BS: bsRmvCirTq(): STOPPING TIMER[%s] CIC[%d] INTFID[%d]\n",BS_PRINT_TMR_EVT_STR(tmrNum),cir->cic,cir->intfCb->intfId);

     switch (tmrNum)
    {
        case BSSAP_T_1:
             timer_id = cir->timer_key[0];
             break;
        case BSSAP_T_19:
             timer_id = cir->timer_key[1];
             break;
        case BSSAP_T_20:
             timer_id = cir->timer_key[2];
             break;

	default:
         LOG_PRINT(CRITICAL,"bsRmvCirTq():invalid timer \n");
         return ;
     }
     if (timer_id != SS7_FALSE)
     {
       result = ss7_stop_timer (timer_id, p_ecode) ;
     }
     else
     {
       LOG_PRINT(INFO,"bsRmvCirTq():Timer Key is SS7_FALSE\n");
       return (SS7_SUCCESS);
     }
     if (result != SS7_SUCCESS)
     {
       LOG_PRINT(INFO,"bsRmvCirTq():ss7_stop_timer failed , Couldn't stop Timer,tmrNum[%d]\n",tmrNum);
       return(SS7_FAILURE);
     }
     else
     {
       LOG_PRINT(INFO,"bsRmvCirTq()::STOPPED [%s]  Timer Successfully having ,tmrNum[%d]\n",BS_PRINT_TMR_EVT_STR(tmrNum),tmrNum);
       cir->timerId = BSSAP_INVALID_TMRID;
       return (SS7_SUCCESS) ;
     }

}/* end of bsRmvCirTq */

/*
*
*       Fun:    bsStopIntfTmr
*
*       Desc:   Stops Interface Timers
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
void bsStopIntfTmr
(
BsIntfCb *intf,
U8bit timer
)
#else
void bsStopIntfTmr(intf, timer)
BsIntfCb *intf;
U8bit timer;
#endif
{
   U8bit tmrNum;

   if(timer != BSSAP_INVALID_TMRID)
   {
      bsRmvIntfTq(intf, timer);
   }
   return ;
} /* end of bsStopIntfTmr */

/*
*
*       Fun:    bsRmvIntfTq
*
*       Desc:   Removes Interface timer from Timing Queue
*
*       Ret:    ROK     - ok
*
*       Notes:  None
*
*       File:   ci_bdy7.c
*
*/

#ifdef ANSI_PROTO
S16bit bsRmvIntfTq
(
BsIntfCb *intf,
U8bit tmrNum
)
#else
S16bit bsRmvIntfTq(intf, tmrNum)
BsIntfCb *intf;
U8bit tmrNum;
#endif
{
   error_t  p_ecode ;
   return_t    result = SS7_SUCCESS ;
   timer_id_t  timer_id; 
       
   LOG_PRINT(INFO,"bsRmvIntfTq():Timer-Id to stop the timer %d \n",tmrNum);
 
      switch (tmrNum)
   	{
      	case BSSAP_T_4:
         if (intf->t4.enb == SS7_TRUE)
         {
             timer_id = intf->t4.timer_id_key;
         }
         break;
      case BSSAP_T_13:
         if (intf->t13.enb == SS7_TRUE)
         {
            timer_id  = intf->t13.timer_id_key;
         }
         break;
      case BSSAP_T_17:
         if (intf->t17.enb == SS7_TRUE)
         {
            timer_id  = intf->t17.timer_id_key;
         }
         break;
      case BSSAP_T_18:
         if (intf->t18.enb == SS7_TRUE)
         {
            timer_id  = intf->t18.timer_id_key;
         }
         break;
     case BSSAP_T_RBSC:
         if (intf->trbsc.enb == SS7_TRUE)
         {
            timer_id  = intf->trbsc.timer_id_key;
         }
         break;
      default:
         LOG_PRINT(CRITICAL,"bsRmvIntfTq():invalid timer  \n");
         return ;
     }

   if (timer_id != SS7_FALSE)
   {	
   	result = ss7_stop_timer (timer_id, p_ecode) ;
   }
   else
   {			
       LOG_PRINT(INFO,"bsRmvIntfTq():Timer Key is SS7_FALSE \n");
       return (SS7_SUCCESS);
   }
   if (result != SS7_SUCCESS)
  {
    LOG_PRINT(INFO,"bsRmvIntfTq():ss7_stop_timer [%s] failed , Couldn't stop Timer,tmrNum[%d]\n",BS_PRINT_TMR_EVT_STR(tmrNum),tmrNum);
    return(SS7_FAILURE);
  }
  else
  {
    LOG_PRINT(INFO,"bsRmvIntfTq()::STOPPED [%s] Timer Successfully having ,tmrNum[%d]\n",BS_PRINT_TMR_EVT_STR(tmrNum),tmrNum);
    return (SS7_SUCCESS) ;
  }
} /* end of bsRmvIntfTq */


