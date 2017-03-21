/*******************************************************************************
**      FILE NAME:
**          bs_apphdl.c
**
**      DESCRIPTION:
**              This file sends all the BSSAP TAG Message to the BSC-APPL.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/


#include "lbs.h"           /* layer management */
#include "bs_err.h"        
#include "bsapp.h"      
#include "bssapcom.h"       
#include "bs_trace.h"
#include "sysxxx_msgopcode.h"       

/* header/extern include files (.x) */

#include "lbs.x"           /* layer management */
#include "bs.x"
#include "bsapp.x"
#include "bssapcom.x"      
#include "bs_trace.x"
#include "s7_typ.h"
#include "s7_def.h"
#include "bs_debug.h"

#include <pthread.h>
#include <netinet/in.h>

#define LOGGER_IMR

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


/*
*
*      Fun:  BsDispatchSccpIndToApp
*
*      Desc:  This function send SCCP Indication(for CC) to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchSccpIndToApp
(
BsCallCb   *call,
U8bit        msgType,
U8bit        cause,
BsIntfCb *intfCb
)
#else
Void BsDispatchSccpIndToApp(call,msgType,cause,intfCb)
BsCallCb   *call;
U8bit        msgType;
U8bit        cause;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN +APP_FIX_HDR_LEN+BSSAP_HDR_LEN];
  U8bit index = 28;
  U32bit callrefId;
  U32bit appId = 0;
  U16bit len = 0,totalBuffLen = 0;
  U8bit  handOver = HANDOVER_FALSE;
  U8bit  honewbss = HONEWBSS_FALSE;
  U8bit  hafailure = HANDOVERFAIL_FALSE;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;


  LOG_PRINT(INFO,"BsDispatchSccpIndToApp() : Send SCCP Indication to APP");
  BS_GET_HANDOVER(call->handoverFlagSet,handOver); 
  BS_GET_HONEWBSS(call->handoverFlagSet,honewbss); 
  BS_GET_HANDOVERFAIL(call->handoverFlagSet,hafailure); 
   if(handOver == HANDOVER_TRUE)
   {
       if (honewbss == HONEWBSS_TRUE)
       {
           LOG_PRINT(INFO,"BsDispatchSccpIndToApp() : New Bss HO is present\n");
           if(hafailure == HANDOVERFAIL_TRUE)
           {
              LOG_PRINT(INFO,"BsDispatchSccpIndToApp : HoFailure present in call\n");
              BS_SET_HANDOVERFAIL_FALSE(call->handoverFlagSet); 
              BS_SET_HONEWBSS_FALSE(call->handoverFlagSet);
              BS_SET_HANDOVER_FALSE(call->handoverFlagSet);
              return ;
            }
            else
            {
               LOG_PRINT(INFO,"BsDispatchSccpIndToApp : No HoFailure present in call\n");
            }
         }       
  }
  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN));
  /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
 /* buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;
  /*Tag*/
  buff[index++] = CP_BSSAP_SCCP_TAG;
 
 /* bscId added */
  buff[index++] = intfCb->bscId;

 /* Message Name/Type */
  buff[index++] = msgType;
  
 /*Callreference */
  callrefId = (htonl)(call->suInstId);/*Converting As we need to send callrefId in Network byte order*/
  buff[index++] = callrefId & 0x000000FF;
  buff[index++] = (callrefId & 0x0000FF00) >> 8;
  buff[index++] = (callrefId & 0x00FF0000) >> 16;
  buff[index++] = (callrefId & 0xFF000000) >> 24;

 /*  App Id */
  appId = (htonl)(call->appId);/*Converting As we need to send appId in Network byte order*/
  buff[index++] = appId & 0x000000FF;
  buff[index++] = (appId & 0x0000FF00) >> 8;
  buff[index++] = (appId & 0x00FF0000) >> 16;
  buff[index++] = (appId & 0xFF000000) >> 24;
 LOG_PRINT(INFO,"BsDispatchSccpIndToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));
 if(msgType == BSSAP_CON_ESTD)
 {
    buff[index++] = 0;
    buff[index++] = 0;
    LOG_PRINT(INFO,"BsDispatchSccpIndToApp() : CP_BSSAP_CON_ESTD(CC) with cause is zero\n");
 }
 if(msgType == BSSAP_CON_REL)
 {
    buff[index++] = 0;
    buff[index++] = cause;
    LOG_PRINT(INFO,"BS: BsDispatchSccpIndToApp() : CP_BSSAP_CON_REL with cause %d\n",cause);
 }
 if(msgType == BSSAP_CON_REF)
 {
    buff[index++] = cause;
    buff[index++] = 0;
    LOG_PRINT(INFO,"BS: BsDispatchSccpIndToApp() : CP_BSSAP_CON_REF(CREF) with cause %d\n",cause);
 }
 if(msgType == BSSAP_CON_ERR)
 {
    buff[index++] = 0;
    buff[index++] = 0;
    buff[index++] = cause;
    LOG_PRINT(INFO,"BS: BsDispatchSccpIndToApp() : CP_BSSAP_CON_ERR(CERR) with cause %d\n",cause);
 }
/* Actual length */
  len = index  - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

 /*UPDATE FOR: Send the buff (dtap msg ) to application on socket */
  LOG_PRINT(INFO,"BS: BsDispatchSccpIndToApp : SEND SCCP IND TO  CP  >>>>>>\n");
  totalBuffLen = len + APP_FIX_HDR_LEN;

  LOG_PRINT(INFO,"BsDispatchSccpIndToApp : HEX_DUMP SEND from BSSAP TO BSC_APP");
  BS_Dump(buff,totalBuffLen);	
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

/* Send Data from BSSAP to BSSAP-User through Socket I/F */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
#if 0
	if (buff)
	{
		bssap_free(buff);
	}
#endif
  return;
}
/*
*
*      Fun:  BsDispatchDtapToApp
*
*      Desc:  This function send DTAP msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchDtapToApp
(
BsCallCb   *call,
Data *databuff,
MsgLen dataLen,
U8bit msgType,
BsIntfCb *intfCb
)
#else
Void BsDispatchDtapToApp(call,databuff,dataLen,msgType,intfCb)
BsCallCb   *call;
Data *databuff;
MsgLen dataLen;
U8bit msgType;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN+ BSSAP_HDR_LEN];
  U8bit index = 28;
  U32bit callrefId;
  U32bit appId = 0;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;

  U16bit len = 0,totalBuffLen = 0;

  LOG_PRINT(INFO,"BsDispatchDtapToApp() : Send DTAP Msg to APP\n");

  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));
  /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

  /*Tag*/
  buff[index++] = CP_BSSAP_MSG_TAG;
  /* BSC Id */
  buff[index++] = intfCb->bscId;
  /*Callreference */
  callrefId = htonl(call->suInstId);/*Converting As we need to send callrefId in Network byte order*/
  buff[index++] = callrefId & 0x000000FF;
  buff[index++] = (callrefId & 0x0000FF00) >> 8;
  buff[index++] = (callrefId & 0x00FF0000) >> 16;
  buff[index++] = (callrefId & 0xFF000000) >> 24;

 /*  App Id */
  appId = htonl(call->appId);/*Converting As we need to send appId in Network byte order*/
  buff[index++] = appId & 0x000000FF;
  buff[index++] = (appId & 0x0000FF00) >> 8;
  buff[index++] = (appId & 0x00FF0000) >> 16;
  buff[index++] = (appId & 0xFF000000) >> 24;

  /* Message discriminator */
  buff[index++] = BSSAP_MD_DTAP;

 /* Message Name/Type */
 buff[index++] = msgType;

 LOG_PRINT(INFO,"BS: BsDispatchDtapToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));
 LOG_PRINT(INFO,"BS: DTAP MSG TOAPP :[%s] AppId [%lu] callrefId[%lu]  BscId [%d] \n",Prnt_Dtap(databuff[3],databuff[4]),appId,callrefId,intfCb->bscId);

 /* BSSAP message buffer length */
 buff[index++] = dataLen;

 /* BSSAP messge buffer */
 ss7_memcpy((U8bit *)&buff[index], databuff, dataLen);

  /* Actual length */
    len = (index + dataLen) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

 /*UPDATE FOR: Send the buff (dtap msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchDtapToApp() : SEND DTAP Message TO  APPP\n");
  totalBuffLen = len + APP_FIX_HDR_LEN;
 
  LOG_PRINT(INFO,"BsDispatchDtapToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP");
  BS_Dump(buff,totalBuffLen);	
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);

  return ;
}
/*
*
*      Fun:  BsDispatchTimeoutErrorToApp
*
*      Desc:  This function send timeout error msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchTimeoutErrorToApp
(
BsCallCb *call,
U8bit errType,
U8bit errCode,
U16bit cic,
BsIntfCb *intfCb
)
#else
void BsDispatchTimeoutErrorToApp(call,errType,errCode,cic,intfCb)
BsCallCb *call;
U8bit errType;
U8bit errCode;
U16bit cic;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U16bit len = 0,totalBuffLen = 0;
  U16bit nb_cic = htons(cic);
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
 

  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));
   /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;
 
 /* Tag*/
   buff[index++] = CP_BSSAP_TIMEOUT_TAG;

    /* bscId*/
   buff[index++] = intfCb->bscId;

    /* Message Discriminator*/
   buff[index++] = errType;

    /* Message name*/
   buff[index++] = errCode;

   buff[index++]=CP_BSSAP_CIC_TAG;
  if(intfCb->swtch == LBS_SW_ITU)
  {
     buff[index++]=(nb_cic & 0xFF00) >> 8;
     buff[index++]=(nb_cic & 0x00FF);
  }
  else
  {
     buff[index++]=(nb_cic & 0x00FF);
     buff[index++]=(nb_cic & 0xFF00) >> 8;
  }
  /* Actual length */  
  len = (index ) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;


 /*UPDATE FOR: Send the buff (error msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchTimeoutErrorToApp() : SEND Network Timeout Message TO  CP  >>>>>>\n");
  totalBuffLen = len + APP_FIX_HDR_LEN;

  LOG_PRINT(INFO,"BsDispatchTimeoutErrorToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP");
  BS_Dump(buff,totalBuffLen);	

  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;

}
/*
*
*      Fun:  BsDispatchErrorToApp
*
*      Desc:  This function send error msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchErrorToApp
(
BsCallCb   *call,
U8bit errType,
U8bit errCode,
U16bit cic,
U8bit MssgType,
BsIntfCb *intfCb
)
#else
Void BsDispatchErrorToApp(call,errType,errCode,cic,MssgType,intfCb)
BsCallCb   *call;
U8bit errType;
U8bit errCode;
U16bit cic;
U8bit MssgType;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U32bit callrefId = 0;  
  U32bit appId = 0;
  U16bit len = 0,totalBuffLen = 0 ,nb_cic = htons(cic);
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
 
  LOG_PRINT(INFO,"BsDispatchErrorToApp : Send ERROR Msg to APP\n");
  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;
 
 
  /* Tag */
   buff[index++] = CP_BSSAP_PROTOCOL_TAG;
 
  /* BSC Id */
  if(call)
  {
     LOG_PRINT(INFO,"BSSAP_Interface: DispatchErrorToApp(): cref %ld msgtype 0x%x AppId %ld errType 0x%x errCode 0x%x \n",call->suInstId,call->msgType,call->appId,errType,errCode);
     buff[index++] = intfCb->bscId;
     callrefId = htonl(call->suInstId);/*Converting As we need to send callrefId in Network byte order*/
     appId = htonl(call->appId);/*Converting As we need to send appId in Network byte order*/
  }
  else
  {
     buff[index++]= intfCb->bscId;
     callrefId = 0;
     appId = 0;
  }
        /* Call ref Id */
    buff[index++] = callrefId & 0x000000FF;
    buff[index++] = (callrefId & 0x0000FF00) >> 8;
    buff[index++] = (callrefId & 0x00FF0000) >> 16;
    buff[index++] = (callrefId & 0xFF000000) >> 24;

       /*  App Id */
    buff[index++] = appId & 0x000000FF;
    buff[index++] = (appId & 0x0000FF00) >> 8;
    buff[index++] = (appId & 0x00FF0000) >> 16;
    buff[index++] = (appId & 0xFF000000) >> 24;
 LOG_PRINT(INFO,"BsDispatchErrorToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));
 
       /* Message discriminator */
    buff[index++] = errType;

    /* Message Name/Type */
    buff[index++] = MssgType;

    /* Error code */
    buff[index++] = errCode;

    if(intfCb->swtch == LBS_SW_ITU)
    {
       buff[index++]=(nb_cic & 0xFF00) >> 8;
       buff[index++]=(nb_cic & 0x00FF);
    }
    else
    {
       buff[index++]=(nb_cic & 0x00FF);
       buff[index++]=(nb_cic & 0xFF00) >> 8;
    }
/* Actual length */
    len = (index ) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

 /*UPDATE FOR: Send the buff (error msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchErrorToApp() : SEND ERROR Message TO  CP  >>>>>> \n");
 /* printf("BsDispatchErrorToApp: SEND ERROR Message TO  CP>>>\n");*/
  totalBuffLen = len + APP_FIX_HDR_LEN;
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID; 

  LOG_PRINT(INFO,"BsDispatchErrorToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */
	
  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);

}
/*
*
*      Fun:  BsDispatchAOIPProtocolErrToApp
*
*      Desc:  This function send error msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchAOIPProtocolErrToApp
(
BsCallCb   *call,
U8bit errType,
U8bit errCode,
U32bit *callId,
S16bit  callIdLen,
U8bit MssgType,
BsIntfCb *intfCb
)
#else
Void BsDispatchAOIPProtocolErrToApp(call,errType,errCode,callId,callIdLen,MssgType,intfCb)
BsCallCb   *call;
U8bit errType;
U8bit errCode;
U32bit *callId;
S16bit  callIdLen;
U8bit MssgType;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U32bit callrefId = 0;
  U32bit appId = 0;
  U16bit len = 0,totalBuffLen = 0;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;

  LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp() : Send AOIP Protocol ERROR Msg to APP\n");
  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

  /* Tag */
   buff[index++] = CP_BSSAP_PROTOCOL_TAG;

  /* BSC Id */
  if(call)
  {
     LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp(): cref %ld msgtype 0x%x AppId %ld errType 0x%x errCode 0x%x \n",call->suInstId,call->msgType,call->appId,errType,errCode);
     buff[index++] = intfCb->bscId;
     callrefId = htonl(call->suInstId);/*Converting As we need to send callrefId in Network byte order*/
     appId = htonl(call->appId);/*Converting As we need to send callrefId in Network byte order*/
     LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));
  }
  else
  {
     buff[index++]= intfCb->bscId;
     callrefId = 0;
     appId = 0;
  }
        /* Call ref Id */
    buff[index++] = callrefId & 0x000000FF;
    buff[index++] = (callrefId & 0x0000FF00) >> 8;
    buff[index++] = (callrefId & 0x00FF0000) >> 16;
    buff[index++] = (callrefId & 0xFF000000) >> 24;

       /*  App Id */
    buff[index++] = appId & 0x000000FF;
    buff[index++] = (appId & 0x0000FF00) >> 8;
    buff[index++] = (appId & 0x00FF0000) >> 16;
    buff[index++] = (appId & 0xFF000000) >> 24;
 LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));

       /* Message discriminator */
    buff[index++] = errType;

    /* Message Name/Type */
    buff[index++] = MssgType;

    /* Error code */
    buff[index++] = errCode;

    ss7_memcpy((U8bit*) &buff[index],(U8bit*) callId,callIdLen);
    index = index + callIdLen;

/* Actual length */
    len = (index ) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

  LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp(): SEND AOIP PROTOCOL ERROR Message TO  CP>>>\n");
  totalBuffLen = len + APP_FIX_HDR_LEN;

  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

  LOG_PRINT(INFO,"BsDispatchAOIPProtocolErrToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	


/* Send Data from BSSAP to BSSAP-User through Socket I/F  */
  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;
}


/*
*
*      Fun:  BsDispatchSsnStatusToApp
*
*      Desc:  This function send ssn status  msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
void BsDispatchSsnStatusToApp
(
U32bit pc,
U8bit ssn,
U8bit status,
BsIntfCb *intfCb
)
#else
Void BsDispatchSsnStatusToApp(pc,ssn,status,intfCb)
U32bit pc;
U8bit ssn;
U8bit status;
BsIntfCb *intfCb;
#endif
{
   Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
   U8bit index = 28;
   U16bit len = 0,totalBuffLen = 0;
   U32bit  nb_pc = htons(pc);
   src_id_t src_id;
   dst_id_t dst_id;
   error_t ecode;

  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

    /*Tag*/
    buff[index++] = CP_BSSAP_MANAGEMENT_TAG;

    /*bscId*/
    buff[index++] = intfCb->bscId;

    /*Msg Disc*/
    buff[index++] = BSSAP_MD_NETWORK;
   
    /*Ssn status */
    buff[index++] = status;
  
    /*Ssn */
    buff[index++] = ssn;

    buff[index++] = (U8bit)(nb_pc & 0x00FF);
    buff[index++] = (U8bit)((nb_pc >> 8) & 0x00FF);
  
/* Actual length */
    len=(index ) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;



   /*UPDATE FOR: Send the buff (error msg ) to application on socket */
    LOG_PRINT(INFO,"BsDispatchSsnStatusToApp() : SEND SSN Status  Message TO  CP  >>>>>>\n");
  /*  printf("BsDispatchSsnStatusToApp: SEND SSN Status Message TO  CP>>>\n");*/
    totalBuffLen = len + APP_FIX_HDR_LEN;
    src_id = BSSAP_MODULE_ID;
    dst_id = BSSAP_USER_MODULE_ID;

  LOG_PRINT(INFO,"BsDispatchSsnStatusToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;
}
/*
*
*      Fun:  BsDispatchPcStatusToApp
*
*      Desc:  This function send point code status  msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
void BsDispatchPcStatusToApp
(
U16bit pc,
U8bit status,
BsIntfCb *intfCb
)
#else
Void BsDispatchPcStatusToApp(pc,status,intfCb)
U16bit pc;
U8bit status;
BsIntfCb *intfCb;
#endif
{
   Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
   U8bit index = 28;
   U16bit len = 0, totalBuffLen = 0;
   src_id_t src_id;
   dst_id_t dst_id;
   error_t ecode;

   U16bit nb_pc = htons(pc);

  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

    /*Tag*/
    buff[index++] = CP_BSSAP_MANAGEMENT_TAG;

    /*bscId*/
    buff[index++] = intfCb->bscId;

    /*Msg Disc*/
    buff[index++] = BSSAP_MD_NETWORK;

    /*point code status */
    buff[index++] = status;

    buff[index++] = (U8bit)(nb_pc & 0x00FF);
    buff[index++] = (U8bit)((nb_pc >> 8) & 0x00FF);
/*a5 00 06 9a 00 00 00 00  00 00 00 20 e2 05 01 bb
54 58 5b 04 02 00 00 f8  00 00 11 01 00 00 00 fe  */
		if (status == SCCP_SCMG_SS_ALLOWED)
		{
		buff[index++] = 0xa5;
		buff[index++] = 0x00;
		buff[index++] = 0x06;
		buff[index++] = 0x9a;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x20;
		buff[index++] = 0xe2;
		buff[index++] = 0x05;
		buff[index++] = 0x01;  /* ALaram Id for SSA is 443 */
		buff[index++] = 0xbb;  /* SSA Alaram Id is 443 */
		buff[index++] = 0x54;
		buff[index++] = 0x58;
		buff[index++] = 0x5b;
		buff[index++] = 0x04;
		buff[index++] = 0x02;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0xf8;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = (U8bit)(nb_pc & 0x00FF);
		buff[index++] = (U8bit)((nb_pc >> 8) & 0x00FF);
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0xfe;

	}
	else
	{
		buff[index++] = 0xa5;
		buff[index++] = 0x00;
		buff[index++] = 0x06;
		buff[index++] = 0x9a;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x20;
		buff[index++] = 0xe2;
		buff[index++] = 0x05;
		buff[index++] = 0x01; /* ALaram Id for SSP is 444 */
		buff[index++] = 0xbc;  /* SSP Alaram Id is 444 */
		buff[index++] = 0x54;
		buff[index++] = 0x58;
		buff[index++] = 0x5b;
		buff[index++] = 0x04;
		buff[index++] = 0x02;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0xf8;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = (U8bit)(nb_pc & 0x00FF);
		buff[index++] = (U8bit)((nb_pc >> 8) & 0x00FF);
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0x00;
		buff[index++] = 0xfe;


	}     

/* Actual length */
   len=index  - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

   /*UPDATE FOR: Send the buff (error msg ) to application on socket */
    totalBuffLen = len + APP_FIX_HDR_LEN;
    src_id = BSSAP_MODULE_ID;
    dst_id = BSSAP_USER_MODULE_ID;


/* Send Data from BSSAP to BSSAP-User through Socket I/F  */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  LOG_PRINT(INFO,"BsDispatchPcStatusToApp() : SEND PC Status  Message TO  CP  >>>>>>\n");

  LOG_PRINT(INFO,"BsDispatchPcStatusToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP\n");
  BS_Dump(buff,totalBuffLen);	
  return;

}
/*
*
*      Fun:  BsDispatchMapErrToApp
*
*      Desc:  This function send error msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchMapErrToApp
(
BsCallCb   *call,
U8bit errCause,
Data *databuff,
MsgLen dataLen,
U8bit msgType,
BsIntfCb *intfCb
)
#else
void BsDispatchMapErrToApp(call,errType,errCause,databuff,dataLen,msgType,intfCb)
BsCallCb   *call;
U8bit errCause;
Data *databuff;
MsgLen dataLen;
U8bit msgType;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U16bit len = 0,totalBuffLen = 0;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;

  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

  LOG_PRINT(INFO,"BsDispatchMapErrorToApp() : Send MAP ERROR Msg to APP\n");
 
  call->msgType = BSSAP_HANDOVER_FAILURE_IND;
  call->hofaicause = errCause;  
     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
/*  buff[16] = (BSSAP_CSAPP_UNIT_DATA_IND & 0xff);
  buff[17] = 0x00;*/
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

  
  /* Tag */
  buff[index++] = CP_BSSAP_FAILURE_TAG;

 /* bscId */
  buff[index++] = intfCb->bscId;

 /* Message discriminator */
  buff[index++] = BSSAP_FAILURE_IND;

 /* Message Name/Type */
 buff[index++] = msgType;

 /*Bssap cause */
  buff[index++] = call->hofaicause;

 /* BSSAP message buffer length */
 buff[index++] = dataLen;

 /* BSSAP messge buffer */
 ss7_memcpy((U8bit *)&buff[index], databuff, dataLen);
  
 /* Actual length */
  len = (index + dataLen) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

 /*UPDATE FOR: Send the buff (dtap msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchMapErrorToApp() : SEND BSSMAP HO-FAIL Err  Message TO  CP  >>>>>>\n");

  totalBuffLen = len + APP_FIX_HDR_LEN;
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

  LOG_PRINT(INFO,"BsDispatchMapErrorToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */

  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;
}

/*
*
*      Fun:  BsDispatchMapToApp
*
*      Desc:  This function send BSSMAP msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchMapToApp
(
BsCallCb   *call,
Data *databuff,
MsgLen dataLen,
U8bit msgType,
BsIntfCb *intfCb
)
#else
void BsDispatchMapToApp(call,databuff,dataLen,msgType,intfCb)
BsCallCb   *call;
Data *databuff;
MsgLen dataLen;
U8bit msgType;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U16bit len = 0,totalBuffLen = 0;
  U32bit callrefId = 0;  
  U32bit appId = 0;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode; 
  
  memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));
     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

   /*Fill: msgType */
  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

  /* Tag*/
  buff[index++] = CP_BSSAP_MSG_TAG;

  /* BSC Id */
  buff[index++] = intfCb->bscId;

  /* Call ref Id */
  callrefId = htonl(call->suInstId);/*Converting As we need to send callrefId in Network byte order*/
  buff[index++] = callrefId & 0x000000FF;
  buff[index++] = (callrefId & 0x0000FF00) >> 8;
  buff[index++] = (callrefId & 0x00FF0000) >> 16;
  buff[index++] = (callrefId & 0xFF000000) >> 24;

  /* App Id */
  appId =htonl(call->appId);/*Converting As we need to send callrefId in Network byte order*/
  buff[index++] = appId & 0x000000FF;
  buff[index++] = (appId & 0x0000FF00) >> 8;
  buff[index++] = (appId & 0x00FF0000) >> 16;
  buff[index++] = (appId & 0xFF000000) >> 24;
  printf("BS: BsDispatchMapToApp NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));

 LOG_PRINT(INFO,"BsDispatchMapToApp NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));
  /* Message discriminator */
  buff[index++] = BSSAP_MD_BSSMAP;

  /* Message Name/Type */
  buff[index++] = msgType;

 /* BSSAP message buffer length */
 buff[index++] = dataLen;

 /* BSSAP messge buffer */
 memcpy((U8bit *)&buff[index], databuff, dataLen);
 
/* Actual length */
  len = (index + dataLen) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;

 
/*UPDATE FOR: Send the buff (dtap msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchMapToApp() : SEND BSSMAP MAP Message TO  CP  >>>>>>\n");
   LOG_PRINT(INFO,"BS: BSSMAP MSG TOAPP :[%s] callrefId[%lu] appId[%lu] bscId[%d] intfId[%d] Dispatched\n",BSSAP_MSG_TYPE_STR(msgType),callrefId,appId,intfCb->bscId,intfCb->intfId);
  /*printf("BsDispatchMapToApp : SEND BSSMAP MAP Message TO  CP  >>>>>>\n");*/
  totalBuffLen = len + APP_FIX_HDR_LEN;
  
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

  LOG_PRINT(INFO,"BsDispatchMapToApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */
  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;
}
/*
*
*      Fun:  BsDispatchMapUDTtoApp
*
*      Desc:  This function send MAP UDT msg to App
*
*      Ret:   ROK   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsDispatchMapUDTtoApp
(
U8bit msgType,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb
)
#else
void BsDispatchMapUDTtoApp(mType,databuff,dataLen,intfCb)
U8bit msgType;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
#endif
{
  Data  buff[BSSAP_DATA_LEN + APP_FIX_HDR_LEN + BSSAP_HDR_LEN];
  U8bit index = 28;
  U16bit len = 0,totalBuffLen = 0;
  U32bit callrefId = 0;
  U32bit appId = 0;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
  
   LOG_PRINT(INFO,"BsDispatchMapUDTtoApp() : Send BSSMAP UDT Msg to APP\n");
   memset((U8bit *)buff, 0,  (BSSAP_DATA_LEN +APP_FIX_HDR_LEN + BSSAP_HDR_LEN));

     /*Fill SysAddr: Src */
  buff[0] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[1] = APP_BSSAP_ENTID; /*SysAddr:entity:ENT_SKS_BSSAP   83 for BSSAP */
  buff[2] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[3] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[4] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[5] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[6] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[7] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */


  /*Fill SysAddr: dest */
  buff[8] = 0x00; /* SysAddr:rfu1: Reserved for future use Default Value (0)*/
  buff[9] = 0x8E; /*SysAddr:entity:ENT_CSAPP_AIFDHM(142) for AIFDHM */
  buff[10] = 0x00; /*SysAddr:clsId:Tau Model specific - Default Value (0)    */
  buff[11] = 0x00; /*SysAddr:rfu2:Reserved for future use Default Value (0) */
  buff[12] = 0x00; /*SysAddr:inst(U32bit):Tau Model Specific - Default Value (0)    */
  buff[13] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[14] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */
  buff[15] = 0x00; /*SysAddr:inst:Tau Model Specific - Default Value (0)    */

  *((U16bit *)(buff+16))=htons(EXT_BSSAP_MSG);

   /*Fill version Id:version Id shall be used for Rolling S/W upgrade - default value(0)*/
  buff[18] = 0x00;

  /*Fill priority:SA_MSG_MESSAGE_HIGHEST_PRIORITY 0 or SA_MSG_MESSAGE_LOWEST_PRIORITY 3 */
  buff[19] = 0x00;

  /* Fill TRX Id:Interface specific - Default Value(0) */
  buff[24] = 0x00;
  buff[25] = 0x00;
  buff[26] = 0x00;
  buff[27] = 0x00;

  /* Tag*/
  buff[index++] = CP_BSSAP_MSG_TAG;

  /* BSC Id */
  buff[index++] = intfCb->bscId;

  /* Call ref Id */
  buff[index++] = callrefId & 0x000000FF;
  buff[index++] = (callrefId & 0x0000FF00) >> 8;
  buff[index++] = (callrefId & 0x00FF0000) >> 16;
  buff[index++] = (callrefId & 0xFF000000) >> 24;


  /* App Id */
  buff[index++] = appId & 0x000000FF;
  buff[index++] = (appId & 0x0000FF00) >> 8;
  buff[index++] = (appId & 0x00FF0000) >> 16;
  buff[index++] = (appId & 0xFF000000) >> 24;
 
LOG_PRINT(INFO,"BsDispatchMapToApp(): NB callrefId[%lu]  NB appId[%lu]  callrefId[%lu]  appId[%lu]\n",callrefId,appId,ntohl(callrefId),ntohl(appId));

  /* Message discriminator */
  buff[index++] = BSSAP_MD_BSSMAP;

  /* Message Name/Type */
  buff[index++] = msgType;

 /* BSSAP message buffer length */
 buff[index++] = dataLen;

 /* BSSAP messge buffer */
 memcpy((U8bit *)&buff[index], databuff, dataLen);

/* Actual length */
  len = (index + dataLen) - APP_FIX_HDR_LEN;
  buff[23] = len & 0x000000FF;
  buff[22] = (len & 0x0000FF00) >> 8;
  buff[21] = (len & 0x00FF0000) >> 16;
  buff[20] = (len & 0xFF000000) >> 24;



/*UPDATE FOR: Send the buff (dtap msg ) to application on socket */
  LOG_PRINT(INFO,"BsDispatchMapUDTtoApp() : SEND BSSMAP UDT Message TO  CP  >>>>>>\n");

   LOG_PRINT(INFO,"BS: BSSMAP(UDT) MSG TOAPP :[%s] callrefId[%lu] appId[%lu] bscId[%d] intfId[%d] Dispatched\n",BSSAP_MSG_TYPE_STR(msgType),callrefId,appId,intfCb->bscId,intfCb->intfId);
  totalBuffLen = len + APP_FIX_HDR_LEN;
  
  src_id = BSSAP_MODULE_ID;
  dst_id = BSSAP_USER_MODULE_ID;

  LOG_PRINT(INFO,"BsDispatchMapUDTtoApp() : HEX_DUMP SEND from BSSAP TO BSC_APP \n");
  BS_Dump(buff,totalBuffLen);	

/* Send Data from BSSAP to BSSAP-User through Socket I/F  */
  send_from_bssap_to_user(buff,totalBuffLen,src_id,dst_id,&ecode);
  return ;
}

