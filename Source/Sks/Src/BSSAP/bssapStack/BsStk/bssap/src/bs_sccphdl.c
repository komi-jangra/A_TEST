/*******************************************************************************
**      FILE NAME:
**          bs_sccphdl.c
**
**      DESCRIPTION:
**              This files defines all the IEIS handelling of BSSAP Messages.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#include "lbs.h"           /* layer management                             */
#include "bs.h"
#include "bs_err.h"
#include "bsapp.h"
#include "bssapcom.h"
#include "bs_trace.h"

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_api.h"
#include "bs_debug.h"

#include <pthread.h>
#include <netinet/in.h>

/* header/extern include files (.x) */
#include "lbs.x"           /* layer management                             */
#include "bs.x"
#include "bsapp.x"
#include "bssapcom.x"
#include "bssapmf.x"
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

S16bit BsDecode(Data *buf,U8bit len,BSSAP_IE *ies,S16bit *iecount,BSSAP_Hdr *hdr);
S16bit BsCheckMsgToByPass(U8bit msgType);

/*
*
*      Fun:  BsProcessUserData
*
*      Desc:  This function provides incoming 
*              User data  from sccp 
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessUserData
(
Data *userdatabuff,
MsgLen userdataLen,
BsCallCb   *call,
BsIntfCb   *bsIntfCb
)
#else
S16bit BsProcessUserData(userdatabuff,userdataLen,call,bsIntfCb)
Data *userdatabuff;
MsgLen userdataLen;
BsCallCb   *call;
BsIntfCb   *bsIntfCb;
#endif
{ 
  BSSAP_IE ies[30];
  BSSAP_Hdr hdr;
  S16bit iecount = 0;
  S16bit ret;
  S16bit i;
   
   if(bsIntfCb == SS7_NULL)
   {
      LOG_PRINT(CRITICAL,"BsProcessUserData(): No Interface present(bsIntfCb is NULL)  \n");
      return (SS7_FAILURE);
   }

   memset((U8bit *)&ies, '\0',  30);
   memset((U8bit *)&hdr, '\0',  sizeof(BSSAP_Hdr));
   ret = BsDecode(userdatabuff,userdataLen,ies,&iecount,&hdr);
   if(ret != SS7_SUCCESS)
   {
        LOG_PRINT(CRITICAL,"BsProcessUserData():DECODING FAIL For INCOMMING MSG \n");
         if(ret == RIGNORE)
         {
#if 0
            /*Raise Alarm to Stack Manager*/
            bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_SWTCH, (PTR)&bsIntfCb->swtch,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&hdr.msgType,
                   LBS_USTA_DGNVAL_DPC, (PTR)&bsIntfCb->phyDpc);

            bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_WRONG_MSG_TYPE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 

         }
         BsHandleDecodeFailure(call,&hdr,userdatabuff,userdataLen,bsIntfCb,ret);
         /*Increment peg counter */
         LOG_PRINT(CRITICAL,"BsProcessUserData(): Incrementing msgDecodeFail counter \n");
         bsIntfCb->sts.genStat.msgDecodeFail++;
	 return (SS7_FAILURE);
   }
   if (hdr.mDisc == BSSAP_MD_DTAP)
   {
        LOG_PRINT(INFO,"BS:MSG FROM MSC:callrefId[%lu] appId[%lu] [DTAP][%s] \n",call->suInstId,call->appId, Prnt_Dtap(userdatabuff[3],userdatabuff[4]));
        if (!call)
        {
            LOG_PRINT(CRITICAL,"BsProcessUserData():DTAP suspected in UDT: call ptr NULL \n");
            BsSendFailureMsg(call,BSSAP_MSG_CONFUSION,C_PROTOCOL_ERROR,NULL,0,bsIntfCb);
	    return (SS7_FAILURE);
        }
         /*Increment peg counter */
         BsIncrPegsCounter(DTAP,hdr.msgType,RECEIVE,bsIntfCb);
         /* Send it to application transparently*/
         BsDispatchDtapToApp(call,userdatabuff,userdataLen,hdr.msgType,bsIntfCb);

   }
   else if (hdr.mDisc == BSSAP_MD_BSSMAP)
   {
     if (call)
     {
       LOG_PRINT(INFO,"BS:MSG FROM MSC:callrefId[%lu] appId[%lu] [BSSMAP][%s] \n",call->suInstId,call->appId,BSSAP_MSG_TYPE_STR(hdr.msgType));
       ret = BsProcessInBSSMAPMessage(call,ies,iecount,bsIntfCb,userdatabuff,userdataLen,hdr.msgType);
     }
     else /* UDT MAP */
     {
       LOG_PRINT(INFO,"BS:MSG FROM MSC: UDT [BSSMAP][%s] \n",BSSAP_MSG_TYPE_STR(hdr.msgType));
       ret = BsProcessInBSSMAPUDTMessage(ies,iecount,bsIntfCb,userdatabuff,userdataLen,hdr.msgType);
     }
     if (ret != SS7_SUCCESS)
     {
        LOG_PRINT(CRITICAL,"BsProcessUserData():Unable to process MsgType[%s] \n",BSSAP_MSG_TYPE_STR(hdr.msgType));
	return (SS7_FAILURE);
     }
    /*Increment peg counter */
     BsIncrPegsCounter(BSSMAP,hdr.msgType,RECEIVE,bsIntfCb);
   
   }
   else 
   {
#if 0
       /*Raise Alarm to Stack Manager*/
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&bsIntfCb->bscId,
                   LBS_USTA_DGNVAL_SWTCH, (PTR)&bsIntfCb->swtch,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&hdr.msgType,
                   LBS_USTA_DGNVAL_DPC, (PTR)&bsIntfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_NEITHER_MAP_NOR_DTAP_MSG, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif /* Amaresh */
      LOG_PRINT(INFO,"BsProcessUserData():neither map nor dtap");
   }
	return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsGetOptMandParam
*
*      Desc:  This function provides gives no of optional
*             and mandatory parameter based on msgtype
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
BsMsgArgsList* BsGetOptMandParam
(
U8bit msgtype
)
#else
BsMsgArgsList* BsGetOptMandParam(msgtype)
U8bit msgtype;
#endif
{
  switch(msgtype)
  {
    case BSSAP_MSG_ASSIGN_REQUEST:
        RETVALUE (&BSSAP_AssignReq);
    case BSSAP_MSG_ASSIGN_COMPLETE:
        RETVALUE (&BSSAP_AssignCom);
    case BSSAP_MSG_ASSIGN_FAILURE:
        RETVALUE (&BSSAP_AssignFail);
    case BSSAP_MSG_HANDOVER_REQUEST:
        RETVALUE(&BSSAP_HandoverReqst);
    case BSSAP_MSG_HANDOVER_REQUIRED:
        RETVALUE(&BSSAP_HandoverRequired);
    case BSSAP_MSG_HANDOVER_REQUEST_ACK:
        RETVALUE(&BSSAP_HandoverReqstAck);
    case BSSAP_MSG_HANDOVER_COMPLETE:
        RETVALUE(&BSSAP_HandoverComp);
    case BSSAP_MSG_HANDOVER_FAILURE:
        RETVALUE(&BSSAP_HandoverFail);
    case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
        RETVALUE(&BSSAP_HandoverRequiredRej);
    case BSSAP_MSG_RESET_CIRCUIT:
        RETVALUE(&BSSAP_ResetCircuit);
    case BSSAP_MSG_RESET_CIRCUIT_ACK:
        RETVALUE(&BSSAP_ResetCircuitAcknowledge);
    case BSSAP_MSG_RESET:
        RETVALUE(&BSSAP_Reset);
    case BSSAP_MSG_RESET_ACK:
        RETVALUE(&BSSAP_ResetAcknowledge);
    case BSSAP_MSG_BLOCK:
        RETVALUE(&BSSAP_Block);
    case BSSAP_MSG_BLOCK_ACK:
        RETVALUE(&BSSAP_BlockAcknowledge);
    case BSSAP_MSG_UNBLOCK:
        RETVALUE(&BSSAP_Unblock);
    case BSSAP_MSG_UNBLOCK_ACK:
        RETVALUE(&BSSAP_UnblockAcknowledge);
    case BSSAP_MSG_CKT_GROUP_BLOCK:
        RETVALUE(&BSSAP_CircuitGroupBlock);
    case BSSAP_MSG_CKT_GRP_UNBLOCK:
        RETVALUE(&BSSAP_CircuitGroupUnblock);
    case BSSAP_MSG_CKT_GRP_BLK_ACK:
        RETVALUE(&BSSAP_CircuitGroupBlockAcknowledge);
    case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
        RETVALUE(&BSSAP_CircuitGroupUnblockAck);
    case BSSAP_MSG_UNEQUIPPED_CKT:
        RETVALUE(&BSSAP_UnequippedCircuit);
    case BSSAP_MSG_CLEAR_REQUEST:
        RETVALUE(&BSSAP_ClearRequest);
    case BSSAP_MSG_CLEAR_COMMAND:
        RETVALUE(&BSSAP_ClearCommand);
    case BSSAP_MSG_CLEAR_COMPLETE:
        RETVALUE(&BSSAP_ClearComplete);
    case BSSAP_MSG_COMPLETE_LAYER3_INFO:
        RETVALUE(&BSSAP_CompleteLayer3Information);
    case BSSAP_MSG_OVERLOAD:          
        RETVALUE(&BSSAP_Overload);     
    case BSSAP_MSG_CHANGE_CKT:  
        RETVALUE(&BSSAP_ChangeCkt); 
    case BSSAP_MSG_CHANGE_CKT_ACK:       
        RETVALUE(&BSSAP_ChangeCktAck);    
    case BSSAP_MSG_CONFUSION:       
        RETVALUE(&BSSAP_Confusion);    
    case BSSAP_MSG_RESET_IP:
        RETVALUE (&BSSAP_ResetIP);
    case BSSAP_MSG_RESET_IP_ACK:
        RETVALUE (&BSSAP_ResetIP_Ack); 
    case BSSAP_MSG_PAGING:
        RETVALUE (&BSSAP_Paging); 
    case BSSAP_MSG_INTERNAL_HANDOVER_COMMAND:
        RETVALUE (&BSSAP_InternalhandoverCmd); 
    case BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED:
        RETVALUE (&BSSAP_InternalhandoverReq); 
    case BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT:
        RETVALUE (&BSSAP_InternalhandoverReqReject); 
    default:
        return SS7_NULL;
   }
        return SS7_NULL;
}

/*
*
*      Fun:  BsComputeParamSize
*
*      Desc:  This function calculate the IE length 
*             
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsComputeParamSize
(
U8bit which,
S16bit knownlen
)
#else
S16bit BsComputeParamSize(which,knownlen)
U8bit which;
S16bit knownlen;
#endif
{
  S16bit len = 0;

  switch(which)
  {
     case BSSAP_IEI_CHANNEL_TYPE:
        len = knownlen + 2 * sizeof(U8bit);/*max length 11 +ie +len*/
#ifdef  DEC_PRT
      printf("BS: BsComputeParamSize:BSSAP_IEI_CHANNEL_TYPE:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LAYER3_INFORMATION:
        len = knownlen + 2 * sizeof(U8bit); /*protocol disc + trans id +ie+len*/
#ifdef DEC_PRT
       printf("BS: BsComputeParamSize:BSSAP_IEI_LAYER3_INFORMATION:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LAYER3_HEADER_INFORMATION:
        len = knownlen + 2 * sizeof(U8bit); /*protocol disc + trans id +ie+len*/
#ifdef DEC_PRT
       printf("BS: BsComputeParamSize:BSSAP_IEI_LAYER3_HEADER_INFORMATION:: ret-len =%d , knownlen %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_PRIORITY:
        len = knownlen + 2 * sizeof(U8bit);/*priorty 1 octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_PRIORITY:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CIRCUIT_IDENTITY_CODE:
        len=sizeof(U8bit) + sizeof(BSSAP_CircuitIdentityCode);/*ie+ 2 octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CIRCUIT_IDENTITY_CODE:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_DOWNLINK_DTX_FLAG:
        len=sizeof(U8bit) + sizeof(BSSAP_DownLinkDTX);/* ie + 1 octet */
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_DOWNLINK_DTX_FLAG::ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED:
        len=sizeof(U8bit) + sizeof(BSSAP_InterferenceBandToBeUsed);/* ie + 1 octet band used*/
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED::ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2:
        len=knownlen + 2 * sizeof(U8bit);/*ie +len +3 octet */
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1:
        len=sizeof(BSSAP_ClassmarkInfoType1) + sizeof(U8bit);/*ie +1 octet */
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_GROUP_CALL_REFERENCE:
        len = knownlen + 2 * sizeof(U8bit);/*ie + len+ + 5 octet */
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_GROUP_CALL_REFERENCE:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_TALKER_FLAG:
        len=sizeof(U8bit);/*only IE*/
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_TALKER_FLAG:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:
        len=sizeof(U8bit) + sizeof(BSSAP_ConfigEvolutionInd);/* ie + 1 octet*/
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:
        len= sizeof(U8bit) + sizeof(BSSAP_LsaAccessCtrlSuppr);/*ie + 1 octet*/
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_SERVICE_HANDOVER:
        len=knownlen + 2 * sizeof(U8bit) /* ie + 1 len octet*/;
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_SERVICE_HANDOVER:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_RR_CAUSE:
        len = sizeof(U8bit);
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_RR_CAUSE:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CELL_IDENTIFIER:
        len=knownlen + 2 * sizeof(U8bit); /*ie + 1 len octet*/
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_CELL_IDENTIFIER:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:
        len = sizeof(U8bit) + sizeof(BSSAP_ChosenEncryptAlgorithm);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CIRCUIT_POOL:
        len=(sizeof(BSSAP_CircuitPool) + sizeof(U8bit));
#ifdef DEC_PRT
     printf("BS: BsComputeParamSize:BSSAP_IEI_CIRCUIT_POOL:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CHANNEL_NEEDED:
        len=(sizeof(BSSAP_ChannelNeeded) + sizeof(U8bit));
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CHANNEL_NEEDED:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_eMLPP_PRIORITY:
        len=(sizeof(BSSAP_emlppPriorty) + sizeof(U8bit));
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_eMLPP_PRIORITY:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_TMSI:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_TMSI:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CELL_IDENTIFIER_LIST:
        len=knownlen + 2 * sizeof(U8bit); /*ie + 1 len octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CELL_IDENTIFIER_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_RESPONSE_REQUEST:
        len=sizeof(U8bit);/*only IE*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_RESPONSE_REQUEST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CIRCUIT_POOL_LIST:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CIRCUIT_POOL_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CURRENT_CHANNEL_TYPE_1:
        len = sizeof(U8bit) + sizeof(BSSAP_CurrentChannelType1);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CURRENT_CHANNEL_TYPE_1:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_QUEUING_INDICATOR:
        len = sizeof(U8bit) + sizeof(BSSAP_QueuingIndicator);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_QUEUING_INDICATOR:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_ENCRYPTION_INFORMATION:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_ENCRYPTION_INFORMATION:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:
        len = knownlen + 2 * sizeof(U8bit);/*ie +1 len octet*/
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_SPEECH_VERSION:
        len = sizeof(U8bit) + sizeof(BSSAP_SpeechVersion);
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_SPEECH_VERSION:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LSA_INFORMATION:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
    printf("BS: BsComputeParamSize:BSSAP_IEI_LSA_INFORMATION:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_IMSI:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_IMSI:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CHOSEN_CHANNEL:
        len = sizeof(U8bit) + sizeof(BSSAP_ChosenChannel);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CHOSEN_CHANNEL:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO:
        len = knownlen + 2 * sizeof(U8bit); /*ie +1 len octet*/
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_INTER_SYSTEM_INFO:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_INTER_SYSTEM_INFO ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_GERAN_CLASSMARK:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_GERAN_CLASSMARK ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_NUMBER_OF_MS:
        len = sizeof(U8bit) + sizeof(BSSAP_NumberOfMs);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_NUMBER_OF_MS ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CAUSE:
        len=knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CAUSE ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CONNECTION_RELEASE_REQUESTED:
        len=sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CONNECTION_RELEASE_REQUESTED ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:
        len=knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LSA_IDENTIFIER_LIST:
        len=knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_LSA_IDENTIFIER_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_APDU:
        len = knownlen + 3 * sizeof(U8bit);
#ifdef DEC_PRT
       printf("BS: BsComputeParamSize:BSSAP_IEI_APDU:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_DIAGNOSTICS:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BsComputeParamSize:BSSAP_IEI_DIAGNOSTICS:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
     case BSSAP_IEI_SPEECH_CODEC : 
       len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
       printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_SPEECH_CODEC:: ret-len =%d , pass-len %d \n",len,knownlen); 
#endif
       RETVALUE(len);
     case BSSAP_IEI_TALKER_PRIORITY:
        len =  2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_TALKER_PRIORITY:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_AOIP:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_AOIP:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CODEC_LIST:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_CODEC_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CALL_ID :
        len = sizeof(U8bit) + sizeof(BSSAP_CallIdentifier);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_CALL_ID:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_PROFILE_ID:
        len = knownlen +  2 *sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_PROFILE_ID:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_CALLID_LIST:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_CALLID_LIST:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_AIF_SELECTOR:
        len = 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_AIF_SELCETOR:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
#ifdef LCLS_PARAM_DECODE
     case BSSAP_IEI_KC128:
        len = knownlen + sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_KC128: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_GLB_CALL_REF:
        len = knownlen + 2 * sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_GLB_CALL_REF:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LCLS_CONFIG:
        len = sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_LCLS_CONFIG:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LCLS_CONN_STATUS_CNTRL:
        len = sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_LCLS_CONN_STATUS_CNTRL:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LCLS_CORR_NOT_NED:
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_LCLS_CORR_NOT_NED:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LCLS_BSS_STATUS:
        len =  sizeof(U8bit);
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_LCLS_BSS_STATUS:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
     case BSSAP_IEI_LCLS_BRK_REQ:
#ifdef DEC_PRT
        printf("BS: BSSAP_ComputeParamSize:BSSAP_IEI_LCLS_BRK_REQ:: ret-len =%d , pass-len %d \n",len,knownlen);
#endif
        RETVALUE(len);
#endif
     default :
           RETVALUE(len);
  }
  RETVALUE(len);
}
/*
*
*      Fun:  BsValidateIElen
*
*      Desc:  This function validate IE len
*             
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsValidateIElen
(
S16bit ie,
S16bit actual_len
)
#else
S16bit BsValidateIElen(ie,actual_len)
S16bit ie;
S16bit actual_len;
#endif
{
 S16bit len = 0;
 
 switch(ie)
 {
   case BSSAP_IEI_CHANNEL_TYPE:
      if((actual_len >= 5) && (actual_len <= 12 ))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CHANNEL_TYPE: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_LAYER3_HEADER_INFORMATION:
     /* if(actual_len == (sizeof(BSSAP_Layer3HeaderInfo) + 2 * sizeof(U8bit)));*/
      if(actual_len > (2 * sizeof(U8bit)));
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LAYER3_HEADER_INFORMATION: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_LAYER3_INFORMATION:
      if(actual_len >  2 * sizeof(U8bit));
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LAYER3_INFORMATION: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_PRIORITY:
      if(actual_len == (sizeof(BSSAP_Priority) + 2 * sizeof(U8bit)) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_PRIORITY: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_IDENTITY_CODE:
      if(actual_len == (sizeof(BSSAP_CircuitIdentityCode) + sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CIRCUIT_IDENTITY_CODE: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_DOWNLINK_DTX_FLAG:
      if((actual_len ==(sizeof(BSSAP_DownLinkDTX) +  sizeof(U8bit) )))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_DOWNLINK_DTX_FLAG: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED:
      if(actual_len == sizeof(BSSAP_InterferenceBandToBeUsed) + 2 * sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2:
      if(actual_len ==(sizeof(BSSAP_ClassmarkInfoType2) + 2 * sizeof(U8bit) ))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1:
      if(actual_len ==(sizeof(BSSAP_ClassmarkInfoType1) +  sizeof(U8bit) ))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_GROUP_CALL_REFERENCE:
      if(actual_len ==(sizeof(BSSAP_GroupCallReference) + 2 * sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_GROUP_CALL_REFERENCE: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len = actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_TALKER_FLAG:
      if(actual_len == sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_TALKER_FLAG: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:
      if(actual_len == (sizeof(BSSAP_ConfigEvolutionInd) +  sizeof(U8bit)) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:
      if(actual_len == sizeof(BSSAP_LsaAccessCtrlSuppr)+  sizeof(U8bit) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_RR_CAUSE:
      if(actual_len == sizeof(BSSAP_RRCause))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_RR_CAUSE:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CELL_IDENTIFIER:
      /*if((actual_len ==  (2 *sizeof(U8bit) + sizeof(BSSAP_CellIdentifier))) && (actual_len > 2) )*/
      if(actual_len >= (3 *sizeof(U8bit))) /*ie type + length + cell disc octet*/ 
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CELL_IDENTIFIER:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CHOSEN_CHANNEL:
      if(actual_len ==  (sizeof(BSSAP_ChosenChannel) + sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CHOSEN_CHANNEL:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:
      if(actual_len ==  (sizeof(BSSAP_ChosenEncryptAlgorithm) + sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_POOL:
      if(actual_len == (sizeof(BSSAP_CircuitPool) + sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CIRCUIT_POOL:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CHANNEL_NEEDED:
      if(actual_len == sizeof(BSSAP_ChannelNeeded) + sizeof(U8bit) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CHANNEL_NEEDED:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_eMLPP_PRIORITY:
      if(actual_len == sizeof(BSSAP_emlppPriorty) + sizeof(U8bit) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_eMLPP_PRIORITY:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_IMSI:
      if(actual_len > (2 *sizeof(U8bit))  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_IMSI:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_TMSI:
      if(actual_len > (2 *sizeof(U8bit))  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_TMSI:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CELL_IDENTIFIER_LIST:
      if(actual_len >= (2 *sizeof(U8bit))  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CELL_IDENTIFIER_LIST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_RESPONSE_REQUEST:
      if(actual_len == sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_RESPONSE_REQUEST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_POOL_LIST:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CIRCUIT_POOL_LIST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_QUEUING_INDICATOR:
      if(actual_len == (sizeof(BSSAP_QueuingIndicator) + sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_QUEUING_INDICATOR:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_ENCRYPTION_INFORMATION:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_ENCRYPTION_INFORMATION:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:
      if(actual_len >= (sizeof(BSSAP_ClassmarkInfoType3) + 2 * sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_SPEECH_VERSION:
      if(actual_len == sizeof(BSSAP_SpeechVersion) + sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_SPEECH_VERSION:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_LSA_INFORMATION:
      if(actual_len > 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LSA_INFORMATION:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_SERVICE_HANDOVER:
      if(actual_len == sizeof(BSSAP_ServiceHandover) + 2 *sizeof(U8bit) )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_SERVICE_HANDOVER:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_INTER_SYSTEM_INFO:
      if(actual_len >= 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_INTER_SYSTEM_INFO:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_GERAN_CLASSMARK:
      if(actual_len >= 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_GERAN_CLASSMARK:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_NUMBER_OF_MS:
      if(actual_len == 2 *sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_NUMBER_OF_MS:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
    case BSSAP_IEI_CAUSE:
       if ((actual_len >= sizeof(BSSAP_Cause) + 2 * sizeof(U8bit)) ||
        (actual_len <= sizeof(BSSAP_Cause) + 2 * sizeof(U8bit) + 1))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CAUSE:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CONNECTION_RELEASE_REQUESTED:
      if(actual_len == sizeof(U8bit)  )
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CONNECTION_RELEASE_REQUESTED:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:
      if(actual_len >= 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_LSA_IDENTIFIER_LIST:
      if(actual_len >= 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LSA_IDENTIFIER_LIST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_APDU:
      if(actual_len >= 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_APDU:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE(len=actual_len);
      }
      RETVALUE(0);
    case BSSAP_IEI_SPEECH_CODEC :
      if(actual_len >= 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_SPEECH_CODEC: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);

   case BSSAP_IEI_TALKER_PRIORITY:
      if(actual_len == 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_TALKER_PRIORITY:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_AOIP:
      if(actual_len == 2 *sizeof(U8bit) +sizeof(BSSAP_Aoip_Ip))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_AOIP:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CODEC_LIST:
      if(actual_len > 2 *sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CODEC_LIST:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_CALL_ID :
      if(actual_len == sizeof(U8bit)+ sizeof(BSSAP_CallIdentifier))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CALL_ID: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_PROFILE_ID:
      if(actual_len == 2 *sizeof(U8bit) + sizeof(BSSAP_ProfileId))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_PROFILE_ID:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
   case BSSAP_IEI_CALLID_LIST :
      if(actual_len >= 2*sizeof(U8bit) + sizeof(BSSAP_CallIdentifier))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CALLID_LIST: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_AIF_SELECTOR :
      if(actual_len == 2*sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_AIF_SELECTOR: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_CURRENT_CHANNEL_TYPE_1:
        if(actual_len == sizeof(U8bit) + sizeof(BSSAP_CurrentChannelType1))
          {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_CURRENT_CHANNEL_TYPE_1 ret-len =%d , pass-len %d\n",len,actual_len);
#endif
        RETVALUE (len=actual_len);
          }
      RETVALUE(0);
#ifdef LCLS_PARAM_DECODE
 case BSSAP_IEI_KC128:
      if(actual_len == sizeof(BSSAP_KC128)+ sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_KC128: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_GLB_CALL_REF:
      if(actual_len >2* sizeof(U8bit))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_GLB_CALL_REF:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_LCLS_CONFIG:
      if(actual_len == (sizeof(BSSAP_LcLsConfig)+ sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LCLS_CONFIG:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_LCLS_CONN_STATUS_CNTRL:
      if(actual_len == (sizeof(BSSAP_LcLsConnStatCntrl)+ sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LCLS_CONN_STATUS_CNTRL:: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_LCLS_CORR_NOT_NED:
      if(actual_len == sizeof(BSSAP_LcLsCorrelNotNeed))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LCLS_CORR_NOT_NED: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_LCLS_BSS_STATUS:
      if(actual_len == (sizeof(BSSAP_LcLsBssStatus)+ sizeof(U8bit)))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LCLS_BSS_STATUS: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);
 case BSSAP_IEI_LCLS_BRK_REQ:
      if(actual_len == sizeof(BSSAP_LcLsBrkReq))
      {
#ifdef DEC_PRT
        printf("BS: BsValidateIElen:BSSAP_IEI_LCLS_BRK_REQ: ret-len =%d , pass-len %d\n",len,actual_len);
#endif
          RETVALUE (len=actual_len);
      }
      RETVALUE(0);

#endif
   default:
      RETVALUE(0);
 }
 RETVALUE(0);
}
/*
*
*      Fun:  BsGetIEDatalen
*
*      Desc:  This function validate IE len
*             
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsGetIEDatalen
(
S16bit ie,
S16bit actual_len,
U8bit  *pos
)
#else
S16bit BsGetIEDatalen(ie,actual_len,pos)
S16bit ie;
S16bit actual_len;
U8bit  *pos;
#endif
{
 S16bit len = 0;
 switch(ie)
 {
   case BSSAP_IEI_CHANNEL_TYPE:
       *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_LAYER3_HEADER_INFORMATION:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_LAYER3_INFORMATION:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_PRIORITY:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CIRCUIT_IDENTITY_CODE:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_DOWNLINK_DTX_FLAG:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
       RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_GROUP_CALL_REFERENCE:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_TALKER_FLAG:
        /*only ie type present*/
        *(pos) = 0;
        RETVALUE(0);
   case BSSAP_IEI_CONFIGURATION_EVOLUTION_IND:
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR:
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_RR_CAUSE:
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CELL_IDENTIFIER:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CHOSEN_CHANNEL:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CIRCUIT_POOL:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CHANNEL_NEEDED:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_eMLPP_PRIORITY:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CALL_ID:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_CALLID_LIST:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CELL_IDENTIFIER_LIST:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_RESPONSE_REQUEST:
        /*only ie type present*/
        *(pos) = 0;
        RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_POOL_LIST:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_QUEUING_INDICATOR:
        /*no length octet*/
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_ENCRYPTION_INFORMATION:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_SPEECH_CODEC:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_SPEECH_VERSION:
        *(pos) = sizeof(U8bit);
        RETVALUE(len = (actual_len - sizeof(U8bit)));
   case BSSAP_IEI_LSA_INFORMATION:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_SERVICE_HANDOVER:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_IMSI:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_NEW_BSS_TO_OLD_BSS_INFO:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_INTER_SYSTEM_INFO:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_GERAN_CLASSMARK:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_NUMBER_OF_MS:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
    case BSSAP_IEI_CAUSE:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
    case BSSAP_IEI_AOIP:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CONNECTION_RELEASE_REQUESTED:
        /*only ie type present*/
        *(pos) = 0;
        RETVALUE(0);
   case BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_LSA_IDENTIFIER_LIST:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_APDU:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_TMSI:
        *(pos) =  2 * sizeof(U8bit);
        RETVALUE(len = (actual_len- 2 * sizeof(U8bit)));
   case BSSAP_IEI_CURRENT_CHANNEL_TYPE_1:
        *(pos) =   sizeof(U8bit);
        RETVALUE(len = (actual_len-  sizeof(U8bit))); /* TAG+VAL*/
   default:
      RETVALUE(0);
 }
 RETVALUE(0);
}

/*
*
*      Fun:  BsDecode
*
*      Desc:  This function provides decode Bssap message
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsDecode
(
Data *buf,
U8bit len,
BSSAP_IE *ies,
S16bit *iecount,
BSSAP_Hdr *hdr
)
#else
S16bit BsDecode(buf,len,ies,iecount,hdr)
Data *buf;
U8bit len;
BSSAP_IE *ies;
S16bit *iecount;
BSSAP_Hdr *hdr;
#endif
{

    BsMsgArgsList* desc =NULL;
    U8bit *margs = NULL;
    S16bit nmargs = 0;
    U8bit *oargs =NULL;
    S16bit noargs = 0;
    S16bit iepos=0;
    S16bit i = 0,j = 0,k = 0;
    U16bit totalParamLen=0;
    S16bit countElem = 0;
    U8bit  pos = 0;
    U8bit  paramLen = 0;
    U8bit cnt=0;
    U8bit counter = 0;
    S16bit ret;
    U8bit found = 0;

   
    if(hdr == NULL)
    {
       LOG_PRINT(CRITICAL,"BS:BsDecode(): Hdr pointer is NULL \n");
       return SS7_FAILURE;
    }

    /* Message DISC (BSSMAP ==0 ) 1 Bytes
       length 1 Bytes     MsgType   1 Bytes*/

    if((buf[0]== BSSAP_MD_BSSMAP) && (buf[1]== (len-2)))
    {
      hdr->mDisc = BSSAP_MD_BSSMAP;
      hdr->msgType = buf[2];
      iepos=iepos + 3;
    }
    /* 1.Message DISC (DTAP == 1)
      2.DLCI 3.Lenght 4.L3h (Transaction/skip 4 bits + Protocol disc 4 bits)
      5.MsgType (0 1 bits + N(SD) 1 bit + Message type 6  bits)
    */
    else if((buf[0]== BSSAP_MD_DTAP) && (buf[2]==(len-3)))
    {
      hdr->mDisc = BSSAP_MD_DTAP;
      hdr->dlci = buf[1];
      hdr->l3h = buf[3];
      hdr->msgType = buf[4];
#ifdef DEC_PRT
     LOG_PRINT(INFO,"BS: BsDecode(): DTAP MSG No DECODE REQUIRED\n");
#endif
       return SS7_SUCCESS;
    }
   else
    {
     LOG_PRINT(CRITICAL,"BS:BsDecode():Fail: Invalid Msg disc or length value \n");
       return SS7_FAILURE;
    }

    LOG_PRINT(INFO,"BS: BsDecode(): msgType[%s] hdr->msgType[0x%x]\n",BSSAP_MSG_TYPE_STR(hdr->msgType),hdr->msgType);

    ret = BsCheckMsgToByPass(hdr->msgType);
    if(ret == SS7_SUCCESS)
    {
#ifdef DEC_PRT
       LOG_PRINT(INFO,"BS:BsDecode(): Check Msg Type and pass [%s] Returning frm decode\n",BSSAP_MSG_TYPE_STR(hdr->msgType));
#endif
       return SS7_SUCCESS;
    }
    LOG_PRINT(INFO,"BS: BsDecode(): Need to Decode Msg\n");
    totalParamLen = (buf[1] - 1);

   /*retrive BSSAP message mand and optional structure*/
   desc = BsGetOptMandParam(hdr->msgType);
   if(desc == SS7_NULL)
   {
     LOG_PRINT(INFO,"BS:BsDecode():Fail: BsGetOptMandParam fail ,Param Missing \n");
       //return RIGNORE;
       return BSSAP_EUNKNOWN_MSG_TYPE;
   }
  else
   {
      margs = desc->mArgs;
      if(margs == NULL)
      {
#ifdef DEC_PRT
        LOG_PRINT(INFO,"BS:BsDecode(): No mandatory args for this msg \n");
#endif
        nmargs = 0; 
        /*RETVALUE(SS7_NULL);*/
      } 
      nmargs = desc->nmArgs;
      oargs = desc->oArgs;
      if(oargs == SS7_NULL)
      {
#ifdef DEC_PRT
         LOG_PRINT(INFO,"BS:BsDecode(): No Optional args for this msg  \n");
#endif
      }
      noargs = desc->noArgs;
   }
   if((nmargs == 0) && (noargs == 0))
   {
#ifdef DEC_PRT
  LOG_PRINT(INFO,"BS:BsDecode():NO manadatory and optional  IEs in Msgtype[%s] \n",BSSAP_MSG_TYPE_STR(hdr->msgType));
#endif
       return SS7_SUCCESS;
   }
   if(totalParamLen <= 0)
   {
     LOG_PRINT(CRITICAL,"BS:BsDecode():Fail:totalParamLen is <= zero",hdr->msgType);
       return SS7_FAILURE;
   }
#ifdef DEC_PRT
   LOG_PRINT(INFO,"BS: BsDecode(): nmargs[%d] : noargs[%d] totalParamLen[%d] \n",nmargs,noargs,totalParamLen);
#endif
   for (i = 0; i < (nmargs); i++)
    {
      if(totalParamLen >0)
      {
        if(buf[iepos] == margs[cnt])
        {
        ies[countElem].param_id = margs[cnt];
        ies[countElem].param_length = BsComputeParamSize(margs[cnt],buf[iepos+1]);/*total len is tag+len+val*/
        len = BsValidateIElen(ies[countElem].param_id,ies[countElem].param_length);/*here len include tag and len*/
        if(len > 0)
        {
          paramLen = BsGetIEDatalen(ies[countElem].param_id,len,&pos);/* here param_len- 2 */
          if(paramLen > 0)
          {
             ss7_memcpy((U8bit*)&ies[countElem].param_data,(U8bit*)&buf[iepos+pos],paramLen);
          }
          iepos = iepos+ies[countElem].param_length;
          totalParamLen-=ies[countElem].param_length;
          LOG_PRINT(INFO,"BS: MANDATORY ELM DECODE SUCESS  0x%x len %d iepos %d \n",ies[countElem].param_id,ies[countElem].param_length,iepos);
          cnt++;
          countElem++;
        }
        else
        {
           LOG_PRINT(CRITICAL,"BS:BsDecode():Fail:IE len invalid",hdr->msgType);
	   //return SS7_FAILURE;
	   return BSSAP_EINVARGSLEN;
        }
       }
       else
       {
             LOG_PRINT(INFO,"BS:BsDecode(): Found Optionall ARG B/W Manadatory 0x%x\n",buf[iepos]);

              if(hdr->msgType == BSSAP_MSG_HANDOVER_REQUEST)
               {
                  if((margs[cnt] == BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2) ||(margs[cnt] == BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1))
                   {
                        cnt++;
                        continue;
                   }
               }
                 if(oargs == SS7_NULL)
                  {
LOG_PRINT(CRITICAL,"BS:BsDecode():Fail:No optional exist and  Mandatory IE(0x%x) missing in Msgtype[%s]\n",margs[cnt],BSSAP_MSG_TYPE_STR(hdr->msgType));
	   //return SS7_FAILURE;
	   return BSSAP_EMISSMAND;
                  } 
                    while(counter < noargs)
                    {
                         if(totalParamLen >0)
                         {
                             if(buf[iepos] == oargs[counter])
                              {
                                  ies[countElem].param_id = oargs[counter];
                                  ies[countElem].param_length = BsComputeParamSize(oargs[counter],buf[iepos+1]);
                                  len = BsValidateIElen(ies[countElem].param_id,ies[countElem].param_length);
                                  if(len > 0)
                                   {
                                    paramLen = BsGetIEDatalen(ies[countElem].param_id,len,&pos);
                                    if(paramLen > 0)
                                      {
                                        ss7_memcpy((U8bit*)&ies[countElem].param_data,(U8bit*)&buf[iepos+pos],paramLen);
                                      }
                                     iepos = iepos+ies[countElem].param_length;
                                     totalParamLen-=ies[countElem].param_length;
                                     LOG_PRINT(INFO,"BS: BsDecode: OPTIONAL ELMT 0x%x len %d epos %d\n",ies[countElem].param_id,ies[countElem].param_length,iepos);
                                     countElem++;
                                     i--;
                                     found = SS7_TRUE; 
                                     break; 
                                  }
                      
                              }
                             counter++;
                         }
                       
                    }
                 if(found)
                 {
#ifdef DEC_PRT
                    BSDEBUGPRINT("BS: BsDecode(): Still Searching for mandatory \n",0);
#endif
                    continue;
                 }
                 else
                 {
                   LOG_PRINT(CRITICAL,"BS: BsDecode():Fail:No Match with Optional args\n");
		    //return SS7_FAILURE;	
		    return BSSAP_EUNKNOWN_IE;	
                 }

               
       LOG_PRINT(INFO,"BS:BsDecode():Fail: Mandatory IE(0x%x) missing in Msgtype[%s]\n",margs[cnt],BSSAP_MSG_TYPE_STR(hdr->msgType));
		    //return SS7_FAILURE;	
		    return BSSAP_EMISSMAND;	
       } 
      }
      else
      {
     LOG_PRINT(CRITICAL,"BS:BsDecode():####Missing  manadatory IE[0x%x] in Msgtype[%s]\n",margs[cnt],BSSAP_MSG_TYPE_STR(hdr->msgType));
	    //return SS7_FAILURE;	
	    return BSSAP_EMISSMAND;	

      }/*total len greater than ZERO IF*/
    } /*End of For LOOP*/
#ifdef DEC_PRT
   LOG_PRINT(INFO,"BS: BsDecode(): After mandatory decoding : countElem[%d] totalParamLen[%d] iepos[%d]\n",countElem,totalParamLen,iepos);
#endif
  for(j = countElem,k=0;(j < (countElem + noargs)) && (k < noargs); j++,k++)
  {
     if(totalParamLen >0)
      {
        ies[j].param_id = oargs[k];
#ifdef DEC_PRT
        LOG_PRINT(INFO,"BS:BsDecode(): totalParamLen[%d]: ies[%d].param_id = %d :  buf[iepos] = %d  at j = %d , K = %d\n",totalParamLen,j,ies[j].param_id, buf[iepos],j,k);
#endif
       if( ies[j].param_id != buf[iepos])
         {
           j--;
#ifdef DEC_PRT
           LOG_PRINT(INFO,"BS: BsDecode(): Still searching for other Optional arguments \n");
#endif
          continue;
         }
         
        ies[j].param_length = BsComputeParamSize(oargs[k],buf[iepos+1]);
        len = BsValidateIElen(ies[j].param_id,ies[j].param_length);
        if(len > 0)
        {
           paramLen = BsGetIEDatalen(ies[j].param_id,len,&pos);
           if(paramLen > 0)
           {
              ss7_memcpy((U8bit*)&ies[j].param_data,(U8bit*)&buf[iepos+pos],paramLen);
           }
           iepos = iepos+ies[j].param_length;
           totalParamLen-=ies[j].param_length;
	   LOG_PRINT(INFO,"BS: 2..BsDecode: OPTIONAL ELMT 0x%x len %d epos %d\n",ies[j].param_id,ies[j].param_length,iepos);
           countElem++;
        }
        else
        {
          LOG_PRINT(INFO,"BS: BsDecode():Fail: len from BsValidateIElen is less than zero \n");
	  //return SS7_FAILURE;
	  return BSSAP_EINVARGSLEN;
        }
       }
       else
       {
#ifdef DEC_PRT
         LOG_PRINT(INFO,"BS:BsDecode(): totalParamLen less than zero \n");
#endif
        break;
       }
    }
   *(iecount) = countElem;
#ifdef DEC_PRT
   LOG_PRINT(INFO,"BS: BsDecode(): after all decoding : countElem[%d] \n",countElem);
#endif
 return SS7_SUCCESS;
}
/*
*
*      Fun:  BsGetInputData
*
*      Desc:  This function fill the input value of arguments
*             in the buf for different msgs to be encoded
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsGetInputData
(
U8bit msgtype,
U8bit args,
AddIeParam *ieparam,
U8bit *buf,
S16bit *len
)
#else
void BsGetInputData(msgtype,args,ieparam,buf,len)
U8bit msgtype;
U8bit args;
AddIeParam *ieparam;
U8bit *buf;
S16bit *len;
#endif
{
 
  switch(msgtype)
  {
     case BSSAP_MSG_ASSIGN_FAILURE:
        if(args == BSSAP_IEI_CAUSE)
         {
          *len=BsComputeParamSize(BSSAP_IEI_CAUSE,sizeof(U8bit));    
          *len = *(len)-2;
           printf("ieparam->cause = %x\n",ieparam->cause);
           ss7_memcpy((U8bit*)&buf,(U8bit*)&ieparam->cause,sizeof(U8bit));
         }
         break;
     case BSSAP_MSG_CIPHER_MODE_REJECT:
        if(args == BSSAP_IEI_CAUSE)
         {
          *len=BsComputeParamSize(BSSAP_IEI_CAUSE,sizeof(U8bit));    
          *len = *(len)-2;
           printf("ieparam->cause = %x\n",ieparam->cause);
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cause,sizeof(U8bit));
         }
         break;
     case BSSAP_MSG_HANDOVER_FAILURE:
        if(args == BSSAP_IEI_CAUSE)
         {
          *len=BsComputeParamSize(BSSAP_IEI_CAUSE,sizeof(U8bit));    
          *len = *(len)-2;
           printf("ieparam->cause = %x\n",ieparam->cause);
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cause,sizeof(U8bit));
         }
         break;
     case BSSAP_MSG_CONFUSION:
        if(args == BSSAP_IEI_CAUSE)
         {
          *len=BsComputeParamSize(BSSAP_IEI_CAUSE,sizeof(U8bit));    
          *len = *(len)-2;
           printf("ieparam->cause = %x\n",ieparam->cause);
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cause,sizeof(U8bit));
         }
        else if(args == BSSAP_IEI_DIAGNOSTICS)
        {
          *len=BsComputeParamSize(BSSAP_IEI_DIAGNOSTICS,ieparam->diagbuflen); 
          *len = *(len)-2;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->diagno,ieparam->diagbuflen);
        }
       break;
    case BSSAP_MSG_BLOCK:                                   
         if(args == BSSAP_IEI_CAUSE)                        
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CAUSE,sizeof(U8bit));    
          *len = *(len)-2;
           printf("ieparam->cause = %x\n",ieparam->cause);
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cause,sizeof(U8bit));
         }                                                  
        else if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)   
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));    
          *len = *(len)-1;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));   
         }                                                  
    break;                                                  
    case BSSAP_MSG_BLOCK_ACK:                               
        if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)        
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));    
          *len = *(len)-1;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));   
         }                                                  
    break ;                                                 
    case BSSAP_MSG_UNBLOCK:                                 
        if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)        
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));    
          *len = *(len)-1;
           printf("Encode: ieparam->cic.cic[0] = 0x%x : ieparam->cic.cic[1] = 0x%x \n",ieparam->cic.cic[0],ieparam->cic.cic[1]); 
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));   
           printf("Encode: buf[0] = 0x%x : buf[1] = 0x%x \n",buf[0],buf[1]); 
         }                                                  
    break ;                                                 
    case BSSAP_MSG_UNBLOCK_ACK:                             
        if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)        
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));    
          *len = *(len)-1;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));   
         }                                                  
    break ;                                                 
    case BSSAP_MSG_UNEQUIPPED_CKT:                          
        if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)        
         {                                                  
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));    
          *len = *(len)-1;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));   
         }                                                  
    break ;
    case BSSAP_MSG_CKT_GRP_BLK_ACK:
    case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
        if (args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE)
         {
          *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE,sizeof(U8bit));
          *len = *(len)-1;
           ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic,(2*sizeof(U8bit)));
         }
         else if(args == BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST)
         {
           *len=BsComputeParamSize(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST,sizeof(U8bit));
           *len = *(len)-2;
            ss7_memcpy((U8bit*)buf,(U8bit*)&ieparam->cic_list,ieparam->cicListlen);
         }
    break ;
           
   default :
       break;
  }
  return ;
}
/*
*
*      Fun:  BsGetStatusBit
*
*      Desc:  This function give the status bit value
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
U8bit  BsGetStatusBit
(
U16bit startcic,
U16bit Endcic,
BSSAP_IE *ielist
)
#else
 U8bit  BsGetStatusBit(startcic,Endcic,ielist)
U16bit startcic;
U16bit Endcic;
BSSAP_IE *ielist;
#endif

{
  U32bit arry_position =0;
  U8bit mask=0x01;
  U8bit bit_position = 0;
  
  arry_position=(Endcic - startcic)/8 ;
  bit_position = (Endcic - startcic) % 8;
  return ((ielist->param_data.cic_list.status[arry_position] >> bit_position) & mask );
}
/*
*
*      Fun:  BsSetStatusBit
*
*      Desc:  This function set the status bit value
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
void  BsSetStatusBit
(
BSSAP_IE *ieCiclist,
U8bit type,
U32bit bitn
)
#else
void  BsSetStatusBit(ieCiclist,type,bitn)
BSSAP_IE *ieCiclist;
U8bit type;
U32bit bitn;
#endif
{
    U32bit   nb, no;
    U32bit  mask;
    U32bit range = 0;

    BS_GET_CICLIST_RANGE(ieCiclist->param_data.cic_list,range);
    if (!range)
    {
        return ;
    }
    
    if ( bitn > range)
    {
        return ;
    }

    nb = (bitn % 8) + 1;
    no = (bitn / 8 );
    mask = (1 << (nb - 1));

    ieCiclist->param_data.cic_list.status[no] |= ((type << (nb - 1)) & mask);

    ieCiclist->param_length = sizeof(ieCiclist->param_data.cic_list) + no;
    return ;
}

/*
*
*      Fun:  BsCheckIELen
*
*      Desc:  This function check whether is present for the IE or not
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsCheckIELen
(
S16bit ie,
MsgLen len
)
#else
S16bit BsCheckIELen(ie,len)
S16bit ie;
MsgLen len;
#endif
{
   switch(ie)
   {
       case BSSAP_IEI_CIRCUIT_IDENTITY_CODE:
       case BSSAP_IEI_DOWNLINK_DTX_FLAG:
       case BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED:
       case BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1:
       printf(" NO IE length present for ie type[%x]\n",ie);
	return (SS7_NULL);
       default:
          break;
   }
	return (len);
}
/*
*
*      Fun:  BsEncode
*
*      Desc:  This function provides encode Bssap message
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsEncode
(
U8bit msgtype,
AddIeParam *ieparamlist,
Data *databuf,
MsgLen *datalen
)
#else
 S16bit BsEncode(msgtype,ieparamlist,databuf,datalen)
U8bit msgtype;
AddIeParam *ieparamlist;
Data *databuf;
MsgLen *datalen;
#endif
{
   BsMsgArgsList* desc = SS7_NULL;
   U8bit *margs = SS7_NULL;
   S16bit nmargs = 0;
   U8bit *oargs =SS7_NULL;
   S16bit noargs = 0;
   S16bit len =0,i = 0;
   U8bit curpos = 0;
   U8bit buf[255];
   MsgLen paramLen = 0; 


   memset((U8bit *)buf, 0, 255); 

   if(databuf == SS7_NULL )
   {
      return (SS7_FAILURE);	
   }
   if(ieparamlist == SS7_NULL)
   {
      return (SS7_FAILURE);	
   }
   desc = BsGetOptMandParam(msgtype);
   if(desc == SS7_NULL)
   {
      return (SS7_FAILURE);	
   }
  else
   {
      margs = desc->mArgs;
      if(margs == SS7_NULL)
      return (SS7_NULL);	
      nmargs = desc->nmArgs;
      oargs = desc->oArgs;
      /*if(oargs == SS7_NULL)RETVALUE(SS7_NULL);*/ /*while encoding some msg can have no optional params */
      noargs = desc->noArgs;
   }
    /*msg Header */
   databuf[curpos++] = 0;/*msg Disc*/
   databuf[curpos++] = 0; /*fill the lenght at the end*/
   databuf[curpos++] = msgtype;
   for (i = 0; i < nmargs; i++)
   {
     databuf[curpos++] = margs[i] ; /*element identifier fro cause ie */
     BsGetInputData(msgtype,margs[i],ieparamlist,buf,&len);
     paramLen = BsCheckIELen(margs[i],len);
     if(paramLen > 0)
     {
       LOG_PRINT(INFO,"IE length present for ie type[%x]\n",margs[i]);
       databuf[curpos++] = len ;    /*-2 for removing ie type and length octets*/       
     }
     ss7_memcpy((U8bit *)&databuf[curpos],(U8bit *)buf,len);
     curpos=curpos+len;
   }
   databuf[1]=curpos -2 *sizeof(U8bit);
   *datalen = curpos;
	
      return (SS7_SUCCESS);	
}
/*
*
*      Fun:  BsCheckMsgToByPass
*
*      Desc:  This function provides check Bssap message type
*             and decide whether to decode this msg or bypass it
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsCheckMsgToByPass
(
U8bit msgType
)
#else
S16bit BsCheckMsgToByPass(msgType)
U8bit msgType;
#endif
{

   switch(msgType)
   {
      case BSSAP_MSG_CONFUSION:
      case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
      case BSSAP_MSG_CHANGE_CKT:
      case BSSAP_MSG_HANDOVER_COMMAND:
      case BSSAP_MSG_MSC_INVOKE_TRACE:
      case BSSAP_MSG_CIPHER_MODE_CMD:
      case BSSAP_MSG_CLASSMARK_REQUEST:
      case BSSAP_MSG_CLASSMARK_UPDATE:
      case BSSAP_MSG_PERFORM_LOCATION_REQUEST:
      case BSSAP_MSG_LSA_INFORMATION:
      case BSSAP_MSG_PERFORM_LOCATION_ABORT:
      case BSSAP_MSG_COMMON_ID:
      case BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY:
      case BSSAP_MSG_CIPHER_MODE_COMPLETE:
      case BSSAP_MSG_CIPHER_MODE_REJECT:
      case BSSAP_MSG_PERFORM_LOCATION_RESPONSE:
      case BSSAP_MSG_SAPI_N_REJECT:
      case BSSAP_MSG_BSS_INVOKE_TRACE:
      case BSSAP_MSG_QUEUING_INDICATION:
      case BSSAP_MSG_SUSPEND:
      case BSSAP_MSG_RESUME:
      case BSSAP_MSG_HANDOVER_COMPLETE:
      case BSSAP_MSG_HANDOVER_DETECT:
      case BSSAP_MSG_HANDOVER_PERFORMED:
      case BSSAP_MSG_HANDOVER_SUCCEEDED:
      case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
      case BSSAP_MSG_RESOURCE_REQUEST:
      case BSSAP_MSG_LOAD_INDICATION:
      case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
      case BSSAP_MSG_RESOURCE_INDICATION:
      case BSSAP_MSG_LCLS_CONNECT_CONTROL:
      case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK:
      case BSSAP_MSG_LCLS_NOTIFICATION:
       /*printf(" BY PASS BSSAP MSGTYPE[%s] \n",BSSAP_MSG_TYPE_STR(msgType));*/
      return SS7_SUCCESS;
      default:
         break;
   }
      return SS7_FAILURE;
}
