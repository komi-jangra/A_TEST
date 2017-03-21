/*******************************************************************************
**      FILE NAME:
**          bs_map.c
**
**      DESCRIPTION:
**              This files defines the source code for Core functionality of BSSAP Stack.
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

#include "lbs.x"           /* layer management */
#include "bs.x"
#include "bsapp.x"
#include "bssapcom.x"
#include "bs_trace.x"
#include "s7_typ.h"
#include "s7_def.h"
#include "s7_api.h"
#include "bs_stgl.h"
#include "bs_msgst.h"
#include "bs_debug.h"

#include <pthread.h>
#include <netinet/in.h>

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


S16bit BsProcessOutDTAPMessage (BSSAPData *bdata,BsIntfCb *intfCb);
S16bit BsProcessOutBSSMAPMessage (BSSAPData *bdata,BsIntfCb *intfCb);


S16bit BsProcessCOMapProcedures (BsCallCb *call,BSSAP_IE *ie,S16bit iecount,Data *databuff,
                                         MsgLen dataLen,U8bit mType,Boolean toApp,BsIntfCb *intfCb);
S16bit BsProcessUDTMapProcedures (U8bit mType,BSSAP_IE *ie,S16bit iecount,Data *databuff,
                                            MsgLen dataLen,Boolean toApp,BsIntfCb *intfCb);

S16bit BsIsUDT (U8bit mType);
S16bit BsDirectionCheck (U8bit evId,Boolean up);
S16bit BsSendDataReq (BsCallCb *call,Data  *sndBuf,MsgLen sndbufLen);
S16bit BsSendUDataReq(Data  *sndBuf,MsgLen sndbufLen,BsIntfCb *intfCb);
extern int bs_log_user_id,source_point_code,rem_pc,bsc_id,bsc_ssn_bssap;
void BsIncrPegsCounter(U8bit isDtapMsgFlag,U8bit msgtype,U8bit directionFlag,BsIntfCb *intfCb);

/*
*
*      Fun:  BsSendFailureMsg
*
*      Desc:  This function send Failure msg to peer
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsSendFailureMsg
(
BsCallCb   *call,
U8bit         msgtype,
S16bit        errcause,
Data       *buffer,
MsgLen     bufLen,
BsIntfCb   *intfCb
)
#else
void BsSendFailureMsg(call,msgtype,errcause,buffer,bufLen,intfCb)
BsCallCb   *call;
U8bit         msgtype;
S16bit        errcause;
Data       *buffer;
MsgLen     bufLen;
BsIntfCb   *intfCb;
#endif
{
  Data  databuff[BSSAP_DATA_LEN];
  MsgLen datalen = 0;
  U8bit ercause;
  S16bit ret ;
  AddIeParam ieparam ;
  S16bit i;
  

  if(intfCb == SS7_NULL)
  {
      LOG_PRINT(CRITICAL,"BsSendFailureMsg():intfCb NULL");
      return ;
  }
  ercause = BSSAP_MAP_ERR_CAUSE(errcause); 
  
   memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
   memset((U8bit *)&ieparam, '\0',  sizeof(AddIeParam));
   
   ieparam.cause = ercause;
   if(msgtype == BSSAP_MSG_CONFUSION)
   {
     BSSAP_DIAG_SET_ERROR_POINTER(ieparam.diagno,DIAG_ERROR_LOCATION_NOT_DETERMINED);
     BSSAP_DIAG_SET_ERROR_BIT_POSITION(ieparam.diagno,DIAG_NO_ERROR);
     ss7_memcpy((U8bit *)ieparam.diagno.message_received,(U8bit *)buffer, bufLen);
     ieparam.diagbuflen = bufLen;
   } 
   ret = BsEncode(msgtype,&ieparam,databuff,&datalen);
   if(ret != SS7_SUCCESS)
   {
      LOG_PRINT(CRITICAL,"In BsSendFailureMsg: BsEncode failed  \n");
      return ;
   }
   if(call)
   {
      LOG_PRINT(INFO,"BS:MSG TO MSC:callrefId[%lu] appId[%lu] Send Failure MsgType[%s] ErrorCause[0x%x] To Peer\n",call->suInstId,call->appId,BSSAP_MSG_TYPE_STR(msgtype),ieparam.cause);
      ret = BsSendDataReq(call,databuff,datalen);
   }
   else
   {
      LOG_PRINT(INFO,"BS:MSG TO MSC:Send Failure MsgType[%s] ErrorCause[0x%x] To Peer\n",BSSAP_MSG_TYPE_STR(msgtype),ieparam.cause);
     ret = BsSendUDataReq(databuff,datalen,intfCb);
   }
   if(ret != SS7_SUCCESS)
   {
      LOG_PRINT(CRITICAL," In BsSendFailureMsg: Dat Send to SCCP  failed  \n");
       return ;
   }
   /*Increment peg counter */
   BsIncrPegsCounter(BSSMAP,msgtype,TRANSMIT,intfCb); 
   return ;
}

/*
*
*      Fun:  BsSendUnEquipCkt
*
*      Desc:  This function send Unequipped Circuit msg to peer
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
void BsSendCktMsg
(
U8bit msgType,
U16bit      cic,
BSSAP_IE *ieCicList,
BsIntfCb  *intfCb
)
#else
void BsSendCktMsg(U8bit msgType,cic,ieCicList,intfCb)
U8bit msgType;
U16bit cic;
BSSAP_IE *ieCicList;
BsIntfCb  *intfCb;
#endif
{
  Data  databuff[BSSAP_DATA_LEN];
  MsgLen datalen = 0;
  AddIeParam ieparam ;
  S16bit ret = SS7_FAILURE;
   

  memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
  memset((U8bit *)&ieparam, '\0',  sizeof(AddIeParam));

  if((msgType == BSSAP_MSG_BLOCK) || (msgType ==BSSAP_MSG_RESET_CIRCUIT))
  {
     ieparam.cause = C_OAMP_INTERVENTION;
     BSSAP_SET_CIC_VALUE(ieparam.cic,cic);
  }
  else if((msgType == BSSAP_MSG_BLOCK_ACK) || (msgType == BSSAP_MSG_UNBLOCK) || (msgType == BSSAP_MSG_UNBLOCK_ACK)|| (msgType == BSSAP_MSG_UNEQUIPPED_CKT)|| (msgType == BSSAP_MSG_RESET_CIRCUIT_ACK))
  {
     BSSAP_SET_CIC_VALUE(ieparam.cic,cic);
  }
  else if ((msgType == BSSAP_MSG_CKT_GRP_BLK_ACK) || ( msgType == BSSAP_MSG_CKT_GRP_UNBLOCK))
  {
     BSSAP_SET_CIC_VALUE(ieparam.cic,cic);
     if(ieCicList == SS7_NULL)
     {
        return ;
     }
     ieparam.cicListlen = ieCicList->param_length;
     ss7_memcpy((U8bit *)&ieparam.cic_list,(U8bit *)&ieCicList->param_data.cic_list,ieCicList->param_length);
  }
  ret = BsEncode(msgType,&ieparam,databuff,&datalen);
  if(ret != SS7_SUCCESS)
  {
      LOG_PRINT(CRITICAL,"In BsSendCktMsg: BsEncode failed  \n");
      return ;
  }
   ret = BsSendUDataReq(databuff,datalen,intfCb);
   if(ret != SS7_SUCCESS)
   {
      LOG_PRINT(CRITICAL," In BsSendCktMsg: BsSendUDataReq failed  \n");
      return ;
   }
   return ;
}

/*
*
*      Fun:  BsSendUDataReq
*
*      Desc:  This function send unit data request
*             primitive to sccp
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsSendUDataReq
(
Data       *sndBuf,
MsgLen     sndbufLen,
BsIntfCb *intfCb
)
#else
S16bit BsSendUDataReq(sndBuf,sndbufLen,intfCb)
Data       *sndBuf;
MsgLen     sndbufLen;
BsIntfCb *intfCb;
#endif
{
  S16bit ret = SS7_SUCCESS;
  U16bit      api_len, data_len ;
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem,* p_len_byte ;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
  sccp_addr_t p_cd_add;
  sccp_addr_t p_cg_add;
	
/* Insert the called party & Calling party details */
    p_cg_add.pc_ind = SS7_TRUE;
    p_cg_add.ssn_ind = SS7_TRUE;
    p_cg_add.gti = SS7_NULL;
    p_cg_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
    p_cg_add.pc = source_point_code;     /* This is derived from BSSAP Interface Configuration */
    p_cg_add.ssn = bsc_ssn_bssap; /* SSN_BSSAP This is derived from Confoguration File 254 */

    p_cd_add.pc_ind = SS7_TRUE;
    p_cd_add.ssn_ind = SS7_TRUE;
    p_cd_add.gti = SS7_NULL;
    p_cd_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
    p_cd_add.pc = rem_pc;     /* phyDpc This is derived from BSSAP Interface Configuration */
    p_cd_add.ssn = bsc_ssn_bssap; /* SSN_BSSAP This is derived from Confoguration File 254 */

/* called party & Calling party details completed */

  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_UNITDATA_IND_MIN_NELEM; /* 3 Mandatory Variable parts */

  /* mandatory variable elem length */
  api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_cd_add);
  api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_cg_add);
  api_len += SCCP_ELEM_LEN_LEN + sndbufLen;
  api_len += ONE_BYTE_OPT_ELEM_SIZE;/* 4 octets for Sequnce control */
  num_elem++; 
  api_len += ONE_BYTE_OPT_ELEM_SIZE; /* 4 Octets for Return options */
  num_elem++;

  if (SS7_NULL == (p_api = bssap_malloc (api_len)))
  {
    LOG_PRINT(CRITICAL,"BsSendUDataReq(): bssap_malloc failed for p_api\n");
    return;
  }

  sccp_fill_api_header (p_api, SCCP_N_UNITDATA_REQUEST,num_elem, api_len);

  p_elem = p_api + API_HEADER_LEN;

  p_len_byte = p_elem;
  p_elem = sccp_encode_sccp_addr (p_elem+1, &p_cd_add);
  *p_len_byte = *(p_len_byte + 1);
  *(p_len_byte + 1) = 0;

  p_len_byte = p_elem;
  p_elem = sccp_encode_sccp_addr (p_elem+1, &p_cg_add);
  *p_len_byte = *(p_len_byte + 1);
  *(p_len_byte + 1) = 0;

  PUT_2_BYTE_LE(p_elem, sndbufLen);
  p_elem += SCCP_ELEM_LEN_LEN;
  ss7_memcpy (p_elem, sndBuf, sndbufLen);
  p_elem += sndbufLen;

  *p_elem++ = SCCP_ELEM_SEQUENCE_CONTROL;
   PUT_2_BYTE_LE(p_elem, SCCP_ELEM_SEQ_CONTROL_LEN);
   p_elem += SCCP_ELEM_LEN_LEN;
   *p_elem++ = PROTOCOL_CLASS_1;
  
   *p_elem++ = SCCP_ELEM_RETURN_OPTION;
    PUT_2_BYTE_LE(p_elem, SCCP_ELEM_RETURN_OPTION_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;
    *p_elem++ = SCCP_RETURN_MSG;


    src_id = BSSAP_MODULE_ID;
    dst_id = SCCP_MODULE_ID;
    LOG_PRINT(INFO,"BsSendUDataReq(): HEX_DUMP SEND from BSSAP TO SCCP");
    BS_Dump(p_api,api_len);
    /* Send BSSAP Data to SCCP through N-UNIT-DATA REQ */
    send_from_bssap_to_sccp(p_api,api_len,src_id,dst_id,&ecode);
     if(p_api)
    {
        bssap_free (p_api);
    }
    return (SS7_SUCCESS);
}



/*
*
*      Fun:  BsSendDataReq
*
*      Desc:  This function send data request
*             primitive to sccp
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsSendDataReq
(
BsCallCb   *call,
Data       *sndBuf,
MsgLen     sndbufLen
)
#else
S16bit BsSendDataReq(call,sndBuf,sndbufLen)
BsCallCb   *call;
Data       *sndBuf;
MsgLen     sndbufLen;
#endif
{
  S16bit ret = SS7_SUCCESS;
  U16bit      api_len, data_len ;
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
 
  api_len = API_HEADER_LEN;
  num_elem = SCCP_N_DATA_IND_MIN_NELEM;

  /* Fixed parameter length */
  api_len += SCCP_ELEM_CONNECTION_ID_LEN;

  /* mandatory variable parameter */
  api_len += (sndbufLen + SCCP_ELEM_LEN_LEN);
  data_len = sndbufLen;

    /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)bssap_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsSendDataReq(): bssap_malloc failed for p_api\n");
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_DATA_REQUEST,
              num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
  PUT_4_BYTE_LE (p_elem, call->spInstId);
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  /* No Mandatory variable parameter */
  PUT_2_BYTE_LE (p_elem, data_len);
  p_elem += SCCP_ELEM_LEN_LEN;

  /* Put the last segment */
  ss7_memcpy (p_elem, sndBuf, sndbufLen);
  p_elem += sndbufLen;

  src_id = BSSAP_MODULE_ID;
  dst_id = SCCP_MODULE_ID;
  LOG_PRINT(INFO,"BsSendDataReq : HEX_DUMP SEND from BSSAP TO SCCP");
  BS_Dump(p_api,api_len);
/* Send BSSAP Data to SCCP through N-DATA REQ */
  send_from_bssap_to_sccp(p_api,api_len,src_id,dst_id,&ecode);  
  if(p_api)
  {
    bssap_free (p_api);
  }
  return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsSendDisReq
*
*      Desc:  This function send Disconnect Request primitive to SCCP
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsSendDisReq
(
SpConId *conId,
U8bit sccpMsgType,
BsIntfCb   *intfCb
)
#else
S16bit BsSendDisReq(conId,sccpMsgType,intfCb)
SpConId *conId;
U8bit sccpMsgType;
BsIntfCb   *intfCb;
#endif
{
   S16bit ret = SS7_FAILURE;

   if((conId == SS7_NULL) || (intfCb == SS7_NULL))
   {
      LOG_PRINT(CRITICAL,"BsSendDisReq():Input Parameters: conId or intfCb ptr is NULL \n");
      return (SS7_FAILURE);
   }

     LOG_PRINT(CRITICAL,"BsSendDisReq():Sending DISCONNECT REQ to SCCP for callrefId[%ld] connId[%d] \n",conId->suInstId,conId->spInstId);
   ret = bsBldDisEvt(conId,sccpMsgType,intfCb);

   if(ret != SS7_SUCCESS)
   {
     LOG_PRINT(CRITICAL,"BsSendDisReq():bsBldDisEvt failed");
     return (SS7_FAILURE);
   }
     LOG_PRINT(CRITICAL,"BsSendDisReq(): DISCONNECT REQ SEND to SCCP Successfully \n");
   return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsSendConResp
*
*      Desc:  This function send Connect Response primitive to SCCP
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsSendConResp
(
SpConId *conId,
BsIntfCb   *intfCb
)
#else
S16bit BsSendConResp(conId,intfCb)
SpConId *conId;
BsIntfCb   *intfCb;
#endif
{
   S16bit ret = SS7_FAILURE;
   U16bit      api_len ;
   U8bit       num_elem ;
   U8bit       *p_api ;
   U8bit       *p_elem ;
   U8bit       *p_tmp ;
   sccp_addr_t p_cg_add;
   src_id_t src_id;
   dst_id_t dst_id;
   error_t ecode;
 
   if((conId == SS7_NULL) || (intfCb == SS7_NULL))
   {
      LOG_PRINT(CRITICAL,"BsSendConResp():Input Parameters: conId or intfCb is NULL \n");
      return (SS7_FAILURE);
   }
   api_len = API_HEADER_LEN;
   num_elem = SCCP_N_CONNECT_CONF_MIN_NELEM;

  /* Fixed parameter length */
   api_len += (SCCP_ELEM_LOG_USER_ID_LEN +
        SCCP_ELEM_CONNECTION_ID_LEN +
        SCCP_ELEM_PROTOCOL_CLASS_LEN);

     p_cg_add.pc_ind = SS7_TRUE;
     p_cg_add.ssn_ind = SS7_TRUE;
     p_cg_add.gti = SS7_FALSE;
     p_cg_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
     p_cg_add.pc = source_point_code;     /* This is derived from BSSAP Interface Configuration */
     p_cg_add.ssn = bsc_ssn_bssap;/* This is derived from Confoguration File 254 */
    LOG_PRINT(INFO,"BsSendConResp()::N-CONNECT-RSP : source_point_code[%d]: SSN[%d] \n",source_point_code,bsc_ssn_bssap);
   
    /* No mandatory variable parameter */
   /* Optional parameters */
   api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          sccp_addr_len (&p_cg_add));
    num_elem++;


/* allocate a buffer to build the API */
  if ((p_api=(U8bit *)bssap_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsSendConResp(): bssap_malloc failed for p_api \n");
    return ;
  }
  sccp_fill_api_header (p_api, SCCP_N_CONNECT_RESPONSE,num_elem, api_len);
  p_elem = p_api + SS7_API_HEADER_LEN;

  PUT_2_BYTE_LE (p_elem,bs_log_user_id);
  p_elem +=  SCCP_ELEM_LOG_USER_ID_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, conId->spInstId);
#else
  PUT_2_BYTE_LE (p_elem, conId->spInstId);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;
  
  *p_elem =  PROTOCOL_CLASS_2;
  p_elem += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  
  *p_elem = SCCP_ELEM_RESPONDING_ADDR;
  p_elem += SCCP_ELEM_ID_LEN;
  p_tmp = p_elem;
 
  p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_cg_add);
    /* Move the length to the first byte of length field */
  *p_tmp = *(p_tmp + 1);
  *(p_tmp + 1) = (U8bit)SS7_NULL; 

    LOG_PRINT(INFO,"BsSendConResp()::Built sccp_n_connect_response() Primitive from BSSAP to SCCP\n");
    src_id = BSSAP_MODULE_ID;
    dst_id = SCCP_MODULE_ID;
    /* Send BSSAP Data to SCCP through N-SCCP_CONNECT_RESPONSE */
  LOG_PRINT(INFO,"BsSendConResp()::N-CONNECT-RSP: api_len[%d] of N-CONNECT-RSP : Src_Id[%d] : Dst_id[%d] \n",api_len,src_id,dst_id);
    send_from_bssap_to_sccp(p_api,api_len,src_id,dst_id,&ecode);
/*  LOG_PRINT(INFO,"BsSendConResp():: N-CONNECT-RSP Buffer:api_len[%d] \n",api_len);
    BS_Dump(p_api,api_len);
  LOG_PRINT(INFO,"BsSendConResp()::################################################ \n");*/
     if(p_api)
    {
        bssap_free (p_api);
    }
     return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsSendConReq
*
*      Desc:  This function send connection request
*             primitive to sccp
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsSendConReq
(
Data       *sndBuf,
MsgLen     sndbufLen,
U32bit        callref,
BsIntfCb   *intfCb
)
#else
S16bit BsSendConReq(sndBuf,sndbufLen,callref,intfCb)
Data       *sndBuf;
MsgLen     sndbufLen;
U32bit        callref;
BsIntfCb   *intfCb;
#endif
{
  U16bit      api_len ;
  U8bit       num_elem ;
  U8bit       *p_api ;
  U8bit       *p_elem ;
  U8bit       *p_tmp ;  
  src_id_t src_id;
  dst_id_t dst_id;
  error_t ecode;
  sccp_addr_t p_cd_add;
  sccp_addr_t p_cg_add;
 
  if((sndBuf == SS7_NULL) || (intfCb == SS7_NULL))
  {
     LOG_PRINT(CRITICAL,"BsSendConReq(): Input Parameters:sndBuf or intfCb is  NULL");
     return (SS7_SUCCESS);	
  }

    /* Insert the called party & Calling party details */
    p_cg_add.pc_ind = SS7_TRUE;
    p_cg_add.ssn_ind = SS7_TRUE;
    p_cg_add.gti = SS7_NULL;
    p_cg_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
    p_cg_add.pc = intfCb->opc;     /* This is derived from BSSAP Interface Configuration */
    p_cg_add.ssn = bsc_ssn_bssap;/* This is derived from Confoguration File 254 */

    p_cd_add.pc_ind = SS7_TRUE;
    p_cd_add.ssn_ind = SS7_TRUE;
    p_cd_add.gti = SS7_NULL;
    p_cd_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
    p_cd_add.pc = intfCb->phyDpc;     /* This is derived from BSSAP Interface Configuration */
    p_cd_add.ssn = bsc_ssn_bssap;/* This is derived from Confoguration File 254 */

    api_len = API_HEADER_LEN;
    num_elem = SCCP_N_CONNECT_IND_MIN_NELEM + 1;/* 4 i.e MF + MV */

  /* Fixed parameter length */
  api_len += (SCCP_ELEM_LOG_USER_ID_LEN + SCCP_ELEM_CORR_ID_LEN + SCCP_ELEM_PROTOCOL_CLASS_LEN);

  /* mandatory variable parameter p_cd_addr */
  api_len += SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_cd_add);

  /* Optional parameters p_cg_addr */
  api_len += (SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_cg_add));
  num_elem++;
  
 /* Optional parameters User Data */
  api_len += (SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN + sndbufLen);
  num_elem++;

    /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)bssap_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsSendConReq():bssap_malloc failed for p_api\n");
    return (SS7_FAILURE);
  }

   sccp_fill_api_header (p_api,SCCP_N_CONNECT_REQUEST,num_elem, api_len);

   p_elem = p_api + SS7_API_HEADER_LEN;

  LOG_PRINT(INFO,"BsSendConReq(): CallReferenceId is %d",callref);
  LOG_PRINT(INFO,"BsSendConReq(): LogUserId is %d",bs_log_user_id);
  /* Fixed parameters */ 
   PUT_2_BYTE_LE (p_elem, bs_log_user_id); 
   p_elem += SCCP_ELEM_LOG_USER_ID_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, callref); /* Change  2byte  to 4byte as on dated 20-01-16 */
  p_elem += SCCP_ELEM_CORR_ID_LEN;
#endif
  *p_elem = PROTOCOL_CLASS_2;
  p_elem += SCCP_ELEM_PROTOCOL_CLASS_LEN;

  /* Mandatory variable parameter */
  p_tmp = p_elem;
  /* Leave a one byte space as lengths in APIs are two bytes
     and following function assume first byte as a length and
     address is coded in rest of other bytes.
  */
  p_elem = sccp_encode_sccp_addr (p_elem + 1, &p_cd_add);
  /* Move the length to the first byte of length field */
  *p_tmp = *(p_tmp + 1);
  *(p_tmp + 1) = 0;
 
/* Optional parameters Calling Party */
    *p_elem = SCCP_ELEM_CALLING_ADDR;
    p_elem += SCCP_ELEM_ID_LEN;
    p_tmp = p_elem;
    /*   Leave a one byte space as lengths in APIs are two bytes
      and following function assume first byte as a length and
      address is coded in rest of other bytes.
    */
    p_elem = sccp_encode_sccp_addr (p_elem + 1, &p_cg_add);

    /* Move the length to the first byte of length field */
    *p_tmp = *(p_tmp + 1);
    *(p_tmp + 1) = (U8bit)SS7_NULL;

/* Optional parameters User Data */

    *p_elem = SCCP_ELEM_USER_DATA;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, sndbufLen);
    p_elem += SCCP_ELEM_LEN_LEN;

    ss7_memcpy (p_elem, sndBuf,sndbufLen);
    p_elem += sndbufLen;
   
    LOG_PRINT(INFO,"BsSendConReq():Built CONNECT_REQUEST(CR) Message from BSSAP to SCCP\n");

    src_id = BSSAP_MODULE_ID;
    dst_id = SCCP_MODULE_ID;
    LOG_PRINT(INFO,"BsSendConReq(): HEX_DUMP SEND from BSSAP TO SCCP");
    BS_Dump(p_api,api_len);
    /* Send BSSAP Data to SCCP through SCCP_N_CONNECT_REQUEST */
    send_from_bssap_to_sccp(p_api,api_len,src_id,dst_id,&ecode);
     if(p_api)
    {
        bssap_free (p_api);
    }
     return (SS7_SUCCESS);
}
/*
*
*      Fun:  BsIsUDT
*
*      Desc:  This function check whether msg is Bssap CL(UDT)
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsIsUDT
(
U8bit mType
)
#else
S16bit BsIsUDT(mType)
U8bit mType;
#endif

{
  S16bit ret = SS7_FALSE;
    switch (mType)
    {
        case BSSAP_MSG_RESET:
        case BSSAP_MSG_RESET_ACK:
        case BSSAP_MSG_RESET_CIRCUIT:
        case BSSAP_MSG_RESET_CIRCUIT_ACK:
        case BSSAP_MSG_RESET_IP:
        case BSSAP_MSG_RESET_IP_ACK:
        case BSSAP_MSG_PAGING:
        case BSSAP_MSG_BLOCK:
        case BSSAP_MSG_BLOCK_ACK:
        case BSSAP_MSG_UNBLOCK:
        case BSSAP_MSG_UNBLOCK_ACK:
        case BSSAP_MSG_CKT_GROUP_BLOCK:
        case BSSAP_MSG_CKT_GRP_BLK_ACK:
        case BSSAP_MSG_CKT_GRP_UNBLOCK:
        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
        case BSSAP_MSG_OVERLOAD:
        case BSSAP_MSG_UNEQUIPPED_CKT:
        case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
        case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
        case BSSAP_MSG_RESOURCE_INDICATION:
        case BSSAP_MSG_RESOURCE_REQUEST:
        case BSSAP_MSG_LOAD_INDICATION:
        case BSSAP_MSG_CONNECTIONLESS_INFORMATION:
        case BSSAP_MSG_CONFUSION:
            ret = SS7_TRUE;
        break;
    }

    return (ret);
}

/*
*
*      Fun:  BsProcessInBSSMAPMessage
*
*      Desc:  This function process incoming CO Bssap msg 
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessInBSSMAPMessage
(
BsCallCb   *call,
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb,
Data *databuff,
MsgLen dataLen,
U8bit mType
)
#else
S16bit BsProcessInBSSMAPMessage(call,ie,iecount,intfCb,databuff,dataLen,mType)
BsCallCb   *call;
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
Data *databuff;
MsgLen dataLen;
U8bit mType;
#endif
{
   S16bit ret ;

   if (BsIsUDT(mType) && (mType != BSSAP_MSG_CONFUSION))
   {
      LOG_PRINT(CRITICAL,"BsProcessInBSSMAPMessage():Failure : Recv. UDT MAP as CO \n");
      BsSendFailureMsg(call,BSSAP_MSG_CONFUSION,C_PROTOCOL_ERROR, databuff, dataLen,intfCb);
      return (SS7_FAILURE);
  }
  ret = BsDirectionCheck(mType,SS7_TRUE);
  if(ret !=  SS7_SUCCESS)
  {
     LOG_PRINT(CRITICAL,"BsProcessInBSSMAPMessage():Wrong direction MsgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
#if 0
     /*Raise Alarm to Stack Manager*/
     bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_SWTCH, (PTR)&intfCb->swtch,
                   LBS_USTA_DGNVAL_MSGTYPE,(PTR)&mType,
                   LBS_USTA_DGNVAL_DPC, (PTR)&intfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_WRONG_MSG_DIRECTION, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif

     BsSendFailureMsg(call,BSSAP_MSG_CONFUSION,C_PROTOCOL_ERROR, databuff, dataLen,intfCb);
     return (SS7_FAILURE);
  }
  if(mType == BSSAP_MSG_HANDOVER_REQUEST)
  {
     call->callType = HO_CALL;
     /*call->handOver = TRUE;*/
     BS_SET_HANDOVER_TRUE(call->handoverFlagSet);
     /*call->honewbss = TRUE; */
     BS_SET_HONEWBSS_TRUE(call->handoverFlagSet); 
     call->appId = 0;
  }
  ret = BsProcessCOMapProcedures(call,ie,iecount,databuff,dataLen,mType,SS7_TRUE,intfCb);
  if (ret == SS7_SUCCESS)
  {
      LOG_PRINT(INFO,"BsProcessInBSSMAPMessage():Sending MsgType:%s to APP \n",BSSAP_MSG_TYPE_STR(mType));
      BsDispatchMapToApp(call,databuff,dataLen,mType,intfCb);
  }
  else
  {
      LOG_PRINT(CRITICAL,"BsProcessInBSSMAPMessage():BsProcessCOMapProcedures failed for MsgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
     return (SS7_FAILURE);
  }
  return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsProcessInBSSMAPUDTMessage
*
*      Desc:  This function process incoming CO Bssap msg
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessInBSSMAPUDTMessage
(
BSSAP_IE *ie,
S16bit iecount,
BsIntfCb *intfCb,
Data *databuff,
MsgLen dataLen,
U8bit mType
)
#else
S16bit BsProcessInBSSMAPUDTMessage(ie,iecount,intfCb,databuff,dataLen,mType)
BSSAP_IE *ie;
S16bit iecount;
BsIntfCb *intfCb;
Data *databuff;
MsgLen dataLen;
U8bit mType;
#endif
{
   S16bit ret ;
   
  if((ie == SS7_NULL) || (databuff == SS7_NULL) ||  (intfCb == SS7_NULL))
  {
     LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage():Input Parameters : ie or databuff or intfCb is NULL \n");
     return (SS7_SUCCESS);
  }

   if (BsIsUDT(mType))
   {
        ret = BsProcessUDTMapProcedures(mType,ie,iecount,databuff,dataLen,SS7_TRUE,intfCb);
        if (ret == SS7_SUCCESS)
        {
	      LOG_PRINT(INFO,"BsProcessInBSSMAPUDTMessage(): Sending UDT msg to APP in case of SUCCESS \n");
              BsDispatchMapUDTtoApp(mType,databuff,dataLen,intfCb);
        }
        else
        {
            LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage(): Fail to process UDT msgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
            BsDispatchMapUDTtoApp(mType,databuff,dataLen,intfCb);
     	    return (SS7_FAILURE);
        }
   }
   else 
   {
       LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage(): Recv. CO MAP as UDT,Therefore Sending failure msg to Peer \n");
       switch(mType)
       {
            case BSSAP_MSG_ASSIGN_REQUEST:
                 LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage:sending Assignment failure \n");
                 BsSendFailureMsg(NULL,BSSAP_MSG_ASSIGN_FAILURE,C_PROTOCOL_ERROR,NULL,0,intfCb);
              break;
            case BSSAP_MSG_CIPHER_MODE_CMD:
                 LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage:sending Cipher Mode Reject \n");
                 BsSendFailureMsg(NULL,BSSAP_MSG_CIPHER_MODE_REJECT,C_PROTOCOL_ERROR,NULL,0,intfCb);
              break;
            case BSSAP_MSG_HANDOVER_REQUEST:
                 LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage:sending Handover Failure \n");
                 BsSendFailureMsg(NULL,BSSAP_MSG_HANDOVER_FAILURE,C_PROTOCOL_ERROR,NULL,0,intfCb);
                 break;
            default:
                 LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage:do nothing only send Confusion msg to peer \n");
                break;
         }

       LOG_PRINT(CRITICAL,"BsProcessInBSSMAPUDTMessage():Sending CONFUSION msg to peer \n");
       BsSendFailureMsg(NULL,BSSAP_MSG_CONFUSION,C_PROTOCOL_ERROR, databuff, dataLen,intfCb);
       return (SS7_FAILURE);
  }
       return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsHandleDecodeFailure
*
*      Desc:  This function decode failure msg
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
void BsHandleDecodeFailure
(
BsCallCb   *call,
BSSAP_Hdr *hdr,
Data *databuff,
MsgLen dataLen,
BsIntfCb *intfCb,
S16bit retcause
)
#else
void  BsHandleDecodeFailure(call,hdr,databuff,dataLen,intfCb,retcause)
BsCallCb   *call;
BSSAP_Hdr *hdr;
Data *databuff;
MsgLen dataLen;
BsIntfCb *intfCb;
S16bit retcause;
#endif
{
 U8bit ercause;

   if((hdr->mDisc != BSSAP_MD_BSSMAP) && (hdr->mDisc != BSSAP_MD_DTAP))
   {
     LOG_PRINT(CRITICAL,"BsHandleDecodeFailure() :Unknown message discriminator:mDisc[0x%x] \n",hdr->mDisc);
   }
      if((hdr->msgType == BSSAP_MSG_CIPHER_MODE_CMD)
         || (hdr->msgType == BSSAP_MSG_ASSIGN_REQUEST)
           || (hdr->msgType == BSSAP_MSG_CLEAR_COMMAND)
              || (hdr->msgType == BSSAP_MSG_HANDOVER_REQUEST)
                || (hdr->msgType == BSSAP_MSG_HANDOVER_COMMAND)
                  || (hdr->msgType == BSSAP_MSG_CLASSMARK_UPDATE)
                    || (hdr->msgType == BSSAP_MSG_CLASSMARK_REQUEST)
                      || (hdr->msgType == BSSAP_MSG_CONFUSION)
                        || (hdr->msgType == BSSAP_MSG_HANDOVER_REQUIRED_REJECT)
                          || (hdr->msgType == BSSAP_MSG_HANDOVER_SUCCEEDED)
                            || (hdr->msgType == BSSAP_MSG_MSC_INVOKE_TRACE))
         {
           LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Decoding of Bssap MsgType:%s  Failed\n",BSSAP_MSG_TYPE_STR(hdr->msgType));
         }
         else
         {
           LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Decoding of Bssap MsgType:%s Failed,Sending CONFUSION Msg to Peer \n",BSSAP_MSG_TYPE_STR(hdr->msgType));
             BsSendFailureMsg(call,BSSAP_MSG_CONFUSION,BSSAP_EUNKNOWN_MSG_TYPE, databuff, dataLen,intfCb);
             return ;
         }
         ercause = BSSAP_MAP_ERR_CAUSE(retcause);

         BsDispatchErrorToApp(call, BSSAP_MD_PROTOCOL,BSSAP_EDECODE,0,0,intfCb);
         switch(hdr->msgType)
         {
            case BSSAP_MSG_ASSIGN_REQUEST:
                 LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Sending BSSAP_MSG_ASSIGN_FAILURE To Peer\n");
                 BsSendFailureMsg(call,BSSAP_MSG_ASSIGN_FAILURE,ercause,NULL,0,intfCb);
              break;
            case BSSAP_MSG_CIPHER_MODE_CMD:
                 LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Sending BSSAP_MSG_CIPHER_MODE_REJECT To Peer \n");
                 BsSendFailureMsg(call,BSSAP_MSG_CIPHER_MODE_REJECT,ercause,NULL,0,intfCb);
              break;
           case BSSAP_MSG_HANDOVER_REQUEST:
                 LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Sending BSSAP_MSG_HANDOVER_FAILURE To Peer \n");
                 call->callType = HO_CALL;
                 /*call->honewbss = TRUE;*/
                 BS_SET_HONEWBSS_TRUE(call->handoverFlagSet);
                 call->appId = 0;
                 BsSendFailureMsg(call,BSSAP_MSG_HANDOVER_FAILURE,ercause,NULL,0,intfCb);
                 BsDispatchMapErrToApp(call,BSSAP_EDECODE,databuff,dataLen,BSSAP_MSG_HANDOVER_REQUEST,intfCb);
                 break;
            default:
                 LOG_PRINT(CRITICAL,"BsHandleDecodeFailure:default case reached  \n");
         }
                 
	 LOG_PRINT(CRITICAL,"BsHandleDecodeFailure():Sending BSSAP_MSG_CONFUSION To Peer \n");
         BsSendFailureMsg(call,BSSAP_MSG_CONFUSION,retcause, databuff, dataLen,intfCb);

   return ;
}
/*
*
*      Fun:  BsIncrPegsCounter
*
*      Desc:  This function increment peg counters
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
void BsIncrPegsCounter
(
U8bit isDtapMsgFlag,
U8bit msgtype,
U8bit directionFlag,
BsIntfCb *intfCb
)
#else
void BsIncrPegsCounter(isDtapMsgFlag,msgtype,directionFlag,intfCb)
U8bit isDtapMsgFlag;
U8bit msgtype;
U8bit directionFlag;
BsIntfCb *intfCb;
#endif
{
  if(intfCb == SS7_NULL)
  {
     LOG_PRINT(CRITICAL,"BsIncrPegsCounter: No Interface present(intfCb is NULL) \n");
     return ;
  }

   if(isDtapMsgFlag == DTAP)
   {
     if(directionFlag == RECEIVE)
     {
      LOG_PRINT(INFO,"DTAP:RECEIVE: Counter Updated for [%s] \n",BS_DTAP_MSG_TYPE_STR(msgtype));
         intfCb->sts.genStat.totalDtapMsgRx++;  
     }
     else if (directionFlag == TRANSMIT)
     {
      LOG_PRINT(INFO,"DTAP:TRANSMIT: Counter Updated for [%s] \n",BS_DTAP_MSG_TYPE_STR(msgtype));
      intfCb->sts.genStat.totalMapMsgRx++;
     }
   }
   else if(isDtapMsgFlag == BSSMAP)
   {
     if(directionFlag == RECEIVE)
     {
      LOG_PRINT(INFO,"BSSMAP:RECEIVE: Counter Updated for [%s] \n",BSSAP_MSG_TYPE_STR(msgtype));
      switch(msgtype)
      {
        case BSSAP_MSG_ASSIGN_REQUEST:
          intfCb->sts.genStat.AssRegRx++;
         break;
        case BSSAP_MSG_HANDOVER_REQUEST:
          intfCb->sts.genStat.handoverReqRx++;
         break;
        case BSSAP_MSG_CLEAR_COMMAND:
         intfCb->sts.genStat.clearCmdRx++;
         break;
        case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
         intfCb->sts.genStat.handoverCandEnqRx++;
         break;
        case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
         intfCb->sts.genStat.handoverRequiredRejRx++;        
         break;
        case BSSAP_MSG_HANDOVER_COMMAND:
         intfCb->sts.genStat.handoverCmdRx++;
         break;
        case BSSAP_MSG_HANDOVER_SUCCEEDED:
         intfCb->sts.genStat.handoverSuccRx++;
         break;
        case BSSAP_MSG_RESOURCE_REQUEST:
         intfCb->sts.genStat.resourceReqRx++;
         break; 
        case BSSAP_MSG_PAGING:
         intfCb->sts.genStat.pagingRx++;
         break; 
        case BSSAP_MSG_CLASSMARK_REQUEST:
         intfCb->sts.genStat.ClassmarkReqRx++;
         break;
        case BSSAP_MSG_CIPHER_MODE_CMD:
         intfCb->sts.genStat.cipherModeCmdRx++;
         break;
        case BSSAP_MSG_CHANGE_CKT:
         intfCb->sts.genStat.changeCktRx++;
         break;
        case BSSAP_MSG_COMMON_ID:
         intfCb->sts.genStat.commonIdRx++;
         break;
        case BSSAP_MSG_LSA_INFORMATION:
         intfCb->sts.genStat.lsaInfoRx++;
         break;
        case BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT:
         intfCb->sts.genStat.intHandoverReqRejRx++;
         break;
        case BSSAP_MSG_INTERNAL_HANDOVER_COMMAND:
         intfCb->sts.genStat.intHandoverCmdRx++;
         break;
        case BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY:
         intfCb->sts.genStat.intHandoverEnqRx++;
         break;
        case BSSAP_MSG_BLOCK:
         intfCb->sts.cktStat.blockRx++;
         break;
        case BSSAP_MSG_BLOCK_ACK:
         intfCb->sts.cktStat.blockAckRx++;
         break;
        case BSSAP_MSG_UNBLOCK:
         intfCb->sts.cktStat.unblockRx++;
         break;
        case BSSAP_MSG_UNBLOCK_ACK:
         intfCb->sts.cktStat.unblockAckRx++;
         break;
        case BSSAP_MSG_RESET_CIRCUIT:
         intfCb->sts.cktStat.resCirRx++;
         break;
        case BSSAP_MSG_RESET_CIRCUIT_ACK:
         intfCb->sts.cktStat.resCirAckRx++;
         break;
        case BSSAP_MSG_CKT_GROUP_BLOCK:
         intfCb->sts.cktStat.cirGrBlockRx++;
         break;
        case BSSAP_MSG_CKT_GRP_BLK_ACK:
         intfCb->sts.cktStat.cirGrBlockAckRx++;
         break;
        case BSSAP_MSG_CKT_GRP_UNBLOCK:
         intfCb->sts.cktStat.cirGrUnBlockRx++;
         break;
        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
         intfCb->sts.cktStat.cirGrUnBlockAckRx++;
         break;
        case BSSAP_MSG_OVERLOAD:
         intfCb->sts.cktStat.overloadRx++;
         break;
        case BSSAP_MSG_CONFUSION:
         intfCb->sts.cktStat.confusionRx++;
         break;
        case BSSAP_MSG_LOAD_INDICATION:
         intfCb->sts.cktStat.loadIndRx++;
         break;
        case BSSAP_MSG_UNEQUIPPED_CKT:
         intfCb->sts.cktStat.unequippedRx++;
         break;
        case BSSAP_MSG_RESET_IP:
         intfCb->sts.cktStat.resetIpResourceRx++;
         break;
        case BSSAP_MSG_RESET_IP_ACK:
         intfCb->sts.cktStat.resetIpResourceAckRx++;
         break;
	case BSSAP_MSG_RESET:
	case BSSAP_MSG_RESET_ACK:
         break;
        default:
             LOG_PRINT(CRITICAL,"BsIncrPegsCounter():default case reached, Unknown MAP msg receive \n");
         break;
             
      }
     }
     else if(directionFlag == TRANSMIT)
     {
      LOG_PRINT(INFO,"BSSMAP:TRANSMIT: Counter Updated for [%s] \n",BSSAP_MSG_TYPE_STR(msgtype));
      switch(msgtype)
      {
        case BSSAP_MSG_ASSIGN_COMPLETE:
          intfCb->sts.genStat.AssCmpTx++;
          break;
        case BSSAP_MSG_ASSIGN_FAILURE:
          intfCb->sts.genStat.AssFailTx++;  
          break;
        case BSSAP_MSG_CHAN_MOD_REQUEST:
          intfCb->sts.genStat.chanModReqTx++;
          break;
        case BSSAP_MSG_CLEAR_COMPLETE:
          intfCb->sts.genStat.clearCompTx++;  
          break;
        case BSSAP_MSG_CLEAR_REQUEST:
          intfCb->sts.genStat.clearReqTx++;
          break;
        case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
          intfCb->sts.genStat.handoverCandRspTx++;
          break;
        case BSSAP_MSG_HANDOVER_REQUIRED:
          intfCb->sts.genStat.handoverReqTx++;
          break;
        case BSSAP_MSG_HANDOVER_REQUEST_ACK:
          intfCb->sts.genStat.handoverReqAckTx++;
          break;
        case BSSAP_MSG_HANDOVER_COMPLETE:
          intfCb->sts.genStat.handoverCmpTx++;
          break;
        case BSSAP_MSG_HANDOVER_FAILURE:
          intfCb->sts.genStat.handoverFailTx++;
          break;
        case BSSAP_MSG_HANDOVER_PERFORMED:
          intfCb->sts.genStat.handoverPerfTx++;
          break;
        case BSSAP_MSG_HANDOVER_DETECT:
          intfCb->sts.genStat.handoverDetTx++;
          break;
        case BSSAP_MSG_RESOURCE_INDICATION:
          intfCb->sts.genStat.resourceIndTx++;
          break;
        case BSSAP_MSG_CIPHER_MODE_COMPLETE:
          intfCb->sts.genStat.cipherModeCompTx++;
          break;
        case BSSAP_MSG_CIPHER_MODE_REJECT:
          intfCb->sts.genStat.cipherModeRejTx++;
          break;
        case BSSAP_MSG_COMPLETE_LAYER3_INFO:
          intfCb->sts.genStat.cl3ITx++;
          break;
        case BSSAP_MSG_CHANGE_CKT_ACK:
          intfCb->sts.genStat.changeCktAckTx++;
          break;
        case BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED:
          intfCb->sts.genStat.indHandoverReqTx++;
          break;
        case BSSAP_MSG_BLOCK:
         intfCb->sts.cktStat.blockTx++;
         break;
        case BSSAP_MSG_BLOCK_ACK:
         intfCb->sts.cktStat.blockAckTx++;
         break;
        case BSSAP_MSG_UNBLOCK:
         intfCb->sts.cktStat.unblockTx++;
         break;
        case BSSAP_MSG_UNBLOCK_ACK:
         intfCb->sts.cktStat.unblockAckTx++;
         break;
        case BSSAP_MSG_RESET_CIRCUIT:
         intfCb->sts.cktStat.resCirTx++;
         break;
        case BSSAP_MSG_RESET_CIRCUIT_ACK:
         intfCb->sts.cktStat.resCirAckTx++;
         break;
        case BSSAP_MSG_CKT_GROUP_BLOCK:
         intfCb->sts.cktStat.cirGrBlockTx++;
         break;
        case BSSAP_MSG_CKT_GRP_BLK_ACK:
         intfCb->sts.cktStat.cirGrBlockAckTx++;
         break;
        case BSSAP_MSG_CKT_GRP_UNBLOCK:
         intfCb->sts.cktStat.cirGrUnBlockTx++;
         break;
        case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
         intfCb->sts.cktStat.cirGrUnBlockAckTx++;
         break;
        case BSSAP_MSG_OVERLOAD:
         intfCb->sts.cktStat.overloadTx++;
         break;
        case BSSAP_MSG_CONFUSION:
         intfCb->sts.cktStat.confusionTx++;
         break;
        case BSSAP_MSG_LOAD_INDICATION:
         intfCb->sts.cktStat.loadIndTx++;
         break;
        case BSSAP_MSG_UNEQUIPPED_CKT:
         intfCb->sts.cktStat.unequippedTx++;
         break;
        case BSSAP_MSG_RESET_IP:
         intfCb->sts.cktStat.resetIpResourceTx++;
         break;
        case BSSAP_MSG_RESET_IP_ACK:
         intfCb->sts.cktStat.resetIpResourceAckTx++;
         break;
	case BSSAP_MSG_RESET:
	case BSSAP_MSG_RESET_ACK:
         break;
        default:
             LOG_PRINT(CRITICAL,"BsIncrPegsCounter():default case reached, Unknown MAP msg Transmit \n");
        break;
      }
     }
   }
   return ;
}
/*
*
*      Fun:  BsDirectionCheck
*
*      Desc:  This function will check direction of BSSMAP msg
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsDirectionCheck
(
U8bit evId,
Boolean up
)
#else
S16bit BsDirectionCheck(evId,up)
U8bit evId;
Boolean up;
#endif

{
    LOG_PRINT(INFO,"BsDirectionCheck: Checking direction of received msg \n");

    if (up)
    {
        LOG_PRINT(INFO,"BsDirectionCheck: Down (MSC -> BSS) event \n");
        switch (evId)
        {
            case BSSAP_MSG_CIPHER_MODE_CMD:
            case BSSAP_MSG_ASSIGN_REQUEST:
            case BSSAP_MSG_CLEAR_COMMAND:
            case BSSAP_MSG_HANDOVER_REQUEST:
            case BSSAP_MSG_HANDOVER_COMMAND:
            case BSSAP_MSG_CLASSMARK_UPDATE:
            case BSSAP_MSG_CLASSMARK_REQUEST:
            case BSSAP_MSG_CONFUSION:
            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
            case BSSAP_MSG_HANDOVER_SUCCEEDED:
            case BSSAP_MSG_MSC_INVOKE_TRACE:
            case BSSAP_MSG_INTERNAL_HANDOVER_COMMAND:
            case BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY:
            case BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT:
	    case BSSAP_MSG_PERFORM_LOCATION_REQUEST:
	    case BSSAP_MSG_LSA_INFORMATION:
            case BSSAP_MSG_LCLS_CONNECT_CONTROL: 
            return SS7_SUCCESS;

            default:
              break;
        }
    }
    else
    {
        LOG_PRINT(INFO,"BsDirectionCheck: Up (BSS -> MSC) event \n");
        switch (evId)
        {
            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
            case BSSAP_MSG_CIPHER_MODE_REJECT:
            case BSSAP_MSG_ASSIGN_COMPLETE:
            case BSSAP_MSG_ASSIGN_FAILURE:
            case BSSAP_MSG_CLEAR_COMPLETE:
            case BSSAP_MSG_HANDOVER_REQUIRED:
            case BSSAP_MSG_HANDOVER_FAILURE:
            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
            case BSSAP_MSG_HANDOVER_COMPLETE:
            case BSSAP_MSG_HANDOVER_DETECT:
            case BSSAP_MSG_CLASSMARK_UPDATE:
            case BSSAP_MSG_CLEAR_REQUEST:
            case BSSAP_MSG_HANDOVER_PERFORMED:
            case BSSAP_MSG_BSS_INVOKE_TRACE:
            case BSSAP_MSG_QUEUING_INDICATION:
            case BSSAP_MSG_SAPI_N_REJECT:
            case BSSAP_MSG_COMPLETE_LAYER3_INFO:
            case BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED:
	    case BSSAP_MSG_PERFORM_LOCATION_RESPONSE:
            case BSSAP_MSG_PERFORM_LOCATION_ABORT:
            case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK:
            case BSSAP_MSG_LCLS_NOTIFICATION:
            return SS7_SUCCESS;
            default:
              break;
        }
    }
            return SS7_FAILURE;
}
/*
*
*      Fun:  BsProcessCOMapProcedures
*
*      Desc:  This function will process CO BSSMAP Msgs 
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessCOMapProcedures
(
BsCallCb *call,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
U8bit mType,
Boolean toApp,
BsIntfCb *intfCb
)
#else
S16bit BsProcessCOMapProcedures(call,ie,iecount,databuff,dataLen,mType,toApp,intfCb);
BsCallCb *call;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
BsNSAPCb *sCb;
U8bit mType;
Boolean toApp;
BsIntfCb *intfCb;
#endif
{
  U8bit callType = 0;
  BsCallCb *newCall = SS7_NULL;
  S16bit ret = SS7_SUCCESS;
#ifdef BSSAP_HA
  HashEntry *callIdEntry = NULL;
  U32 *callIdVal = NULL;
  int result = RFAILED;
  U32 callId = 0;
#endif

    if(call == SS7_NULL)
    {
      return SS7_FAILURE;
    }
  callType = call->callType;
  if (callType != MO_CALL && callType != MT_CALL && callType != HO_CALL &&
      callType != LU_CALL && callType != IMSI_DETACH )
  {
    LOG_PRINT(CRITICAL,"BsProcessCOMapProcedures():BSS-MAP procedure w/o call \n");
      return SS7_FAILURE;
  }
  LOG_PRINT(INFO,"In BsProcessCOMapProcedures:MsgType:%s \n",BSSAP_MSG_TYPE_STR(mType));
  if(toApp)
  {
    /*MSC -> BSS: MSG RECEIVE FROM MSC */

    switch (mType)
    {
      case BSSAP_MSG_ASSIGN_REQUEST:
	ret = BsProcessAssignmentRequest(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_CLEAR_COMMAND:
	ret = BsProcessClearCommand(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_INTERNAL_HANDOVER_COMMAND:
	ret = BsProcessInternalHandoverCmd(call,ie,iecount,databuff,dataLen,intfCb);
	break;
      case BSSAP_MSG_INTERNAL_HANDOVER_REQ_REJECT:
	ret = BsProcessInternalHandoverRequiredReject(call,ie,iecount,databuff,dataLen,intfCb);
	break;
      case BSSAP_MSG_HANDOVER_REQUEST:
	ret = BsProcessHandoverRequest(call,ie,iecount,databuff,dataLen,intfCb);
	if(ret == SS7_SUCCESS)
	{
	  newCall = bsCreate_InsertConRef(intfCb);
	  if(newCall == SS7_NULL)
	  {
	    LOG_PRINT(CRITICAL,"BsProcessCOMapProcedures():Unable to allocate callref for New connection \n");
#ifdef BSSAP_HA
	    if(call->callId != 0)
	    {
	      callId = call->callId;
	      result = HashListTbSearch(intfCb->callIdList,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId),&callIdEntry);
	      if(result != ROK)
	      {
		LOG_PRINT(CRITICAL,"BsProcessCOMapProcedures():BSSAP_MSG_HANDOVER_REQUEST:CALLID[%d] not found  hash list\n",callId);
		return (SS7_FAILURE);
	      }
	      callIdVal = callIdEntry->data;
	      result = HashListTbDelete(intfCb->callIdList,intfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(U8 *)&(callId),sizeof(callId));
	      if(result != ROK)
	      {
		LOG_PRINT(CRITICAL,"BsProcessCOMapProcedures():HashListTbDelete failed for CALLID[%d]\n",callId);
		return (SS7_FAILURE);
	      }
	      if(callIdVal)
	      {
		bssap_free((U32*)callIdVal);
		callIdVal = NULL;
	      }
	    }
#endif
	    return (SS7_FAILURE);	
	  }
	  newCall->spInstId = call->spInstId;
	  call->suInstId = newCall->suInstId;
	  newCall->callType = call->callType;
	  newCall->handoverFlagSet = call->handoverFlagSet;
	  newCall->appId = call->appId;
	  newCall->callId = call->callId;
	  newCall->cic = call->cic;
	  LOG_PRINT(INFO,"BsProcessCOMapProcedures():Call Added to Call db: callrefId[%ld] appId[%ld] newCall[%x]\n",newCall->suInstId,newCall->appId,newCall);
	}
	break;
      case BSSAP_MSG_CONFUSION:
	/*No handling at Stack as it need to only pass msg to Application*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_SUCCEEDED:
	/*No handling at Stack as it need to only pass msg to Application*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CHANGE_CKT:
	/*No handling at Stack as it need to only pass msg to Application*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_COMMAND:
	/*No handling at Stack as it need to only pass msg to Application*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_MSC_INVOKE_TRACE:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CIPHER_MODE_CMD:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CLASSMARK_REQUEST:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CLASSMARK_UPDATE:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_PERFORM_LOCATION_REQUEST:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_LSA_INFORMATION:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_PERFORM_LOCATION_ABORT:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_COMMON_ID:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_INTERNAL_HANDOVER_ENQUIRY:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_LCLS_CONNECT_CONTROL:
	/*No handling at Stack as it need to only pass msg to Application*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s] msg to APP\n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
    }
    if(ret == SS7_SUCCESS)
    {
      call->msgType = mType;
    }
  }
  else
  {
    /*BSC -> MSS: MSG SEND to MSC */
    LOG_PRINT(INFO,"BS:MSG TO MSC :callrefId[%lu] appId[%lu] [BSSMAP][%s] \n",call->suInstId,call->appId,BSSAP_MSG_TYPE_STR(mType));
    switch (mType)
    {
      case BSSAP_MSG_COMPLETE_LAYER3_INFO:
	ret = BsProcessCompleteLayer3Info(call,ie,iecount,databuff,dataLen,intfCb);
	break;
      case BSSAP_MSG_ASSIGN_COMPLETE:
	ret = BsProcessAssignmentComplete(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_ASSIGN_FAILURE:
	ret = BsProcessAssignmentFailure(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_CIPHER_MODE_COMPLETE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	 LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CIPHER_MODE_REJECT:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_PERFORM_LOCATION_RESPONSE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_SAPI_N_REJECT:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_BSS_INVOKE_TRACE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CLASSMARK_UPDATE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_QUEUING_INDICATION:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_SUSPEND:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_RESUME:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_CLEAR_REQUEST:
	ret = BsProcessClearRequest(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_CLEAR_COMPLETE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_REQUIRED:
	ret = BsProcessHandoverRequired(call,ie,iecount);
	break;
      case BSSAP_MSG_HANDOVER_FAILURE:
	ret = BsProcessHandoverFailure(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_HANDOVER_REQUEST_ACK:
	ret = BsProcessHandoverReqAck(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_HANDOVER_COMPLETE:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_DETECT:
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
	break;
      case BSSAP_MSG_HANDOVER_PERFORMED:
	ret = BsProcessHandoverPerformed(call,ie,iecount);
	break;
      case BSSAP_MSG_CHANGE_CKT_ACK:
	ret = BsProcessChangeCircuitAck(call,ie,iecount,intfCb);
	break;
      case BSSAP_MSG_INTERNAL_HANDOVER_REQUIRED:
	ret = BsProcessInternalHandoverRequired(call,ie,iecount,databuff,dataLen,intfCb);
	break;
      case BSSAP_MSG_LCLS_CONNECT_CONTROL_ACK: 
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
      case BSSAP_MSG_LCLS_NOTIFICATION: 
	/*No handling at Stack as it need to only pass msg to MSC*/
	LOG_PRINT(INFO,"BsProcessCOMapProcedures():No-Need to Handle Just Pass [%s]MSG to MSC \n",BSSAP_MSG_TYPE_STR(mType));
	ret = SS7_SUCCESS;
    }
    if(ret == SS7_SUCCESS)
    {
      call->msgType = mType;
    }
    if((ret == SS7_SUCCESS) && (mType != BSSAP_MSG_COMPLETE_LAYER3_INFO))
    {
      ret = BsSendDataReq(call,databuff,dataLen);
    }

  }
  return(ret);
}
/*
*
*      Fun:  BsProcessUDTMapProcedures
*
*      Desc:  This function will process BSSMAP UDT Msgs
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/

#ifdef ANSI_PROTO
S16bit BsProcessUDTMapProcedures
(
U8bit mType,
BSSAP_IE *ie,
S16bit iecount,
Data *databuff,
MsgLen dataLen,
Boolean toApp,
BsIntfCb *intfCb
)
#else
S16bit BsProcessUDTMapProcedures(mType,ie,iecount,databuff,dataLen,toApp,intfCb);
U8bit mType;
BSSAP_IE *ie;
S16bit iecount;
Data *databuff;
MsgLen dataLen;
Boolean toApp;
BsIntfCb *intfCb;
#endif
{
   S16bit ret = SS7_FAILURE;

   if (toApp)
   {
        LOG_PRINT(INFO,"BsProcessUDTMapProcedures() : BSSMAP(UDT) MSG TOAPP[%s]\n",BSSAP_MSG_TYPE_STR(mType));
        switch (mType)
        {
            case BSSAP_MSG_BLOCK:
                 ret = BsProcessBlockInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_BLOCK_ACK:
                 ret = BsProcessBlockAckInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_UNBLOCK:
                 ret = BsProcessUnBlockInd(ie,iecount,intfCb);
            break;
            case BSSAP_MSG_UNBLOCK_ACK:
                 ret = BsProcessUnBlockAckInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_RESET_ACK:
                 ret = BsProcessResetAckInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_RESET:
                 ret = BsProcessResetInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_RESET_CIRCUIT:
                 ret = BsProcessResetCktInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_RESET_CIRCUIT_ACK:
                 ret = BsProcessResetCktAckInd(ie,iecount,intfCb);;
            break;

            case BSSAP_MSG_UNEQUIPPED_CKT:
                 ret = BsProcessUnequippedCktInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_OVERLOAD:
                 ret = BsProcessOverloadInd(intfCb);
            break;
            case BSSAP_MSG_CKT_GROUP_BLOCK:
                 ret = BsProcessCktGroupBlockInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                 ret = BsProcessCktGroupBlockAckInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                 ret = BsProcessCktGroupUnBlockInd(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                 ret = BsProcessCktGroupUnBlockAckInd(ie,iecount,intfCb);
            break;
            case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_CONFUSION:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_RESOURCE_REQUEST:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_LOAD_INDICATION:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_PAGING:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_RESET_IP:
                 /*No handling , directly pass to App */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to BSC \n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_RESET_IP_ACK:
                 ret = BsProcessResetIPAckInd(ie,iecount,intfCb);
            break;
          default:  
            LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): Unknown Incoming UDT msg  \n");
            return (SS7_FAILURE);
             
        }
   }
   else
   {
        switch (mType)
        {
            case BSSAP_MSG_BLOCK:
                 ret = BsProcessBlockRequest(ie,iecount,databuff,dataLen,intfCb);
            break;

            case BSSAP_MSG_BLOCK_ACK:
                 ret = BsProcessBlockAckReq(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_UNBLOCK:
                 ret = BsProcessUnBlockRequest(ie,iecount,databuff,dataLen,intfCb);
            break;

            case BSSAP_MSG_RESET:
                 ret = BsProcessResetReq(ie,iecount,databuff,dataLen,intfCb);
            break;

            case BSSAP_MSG_RESET_ACK:
                 ret = BsProcessResetAckReq(ie,iecount,intfCb);
            break;

            case BSSAP_MSG_RESET_CIRCUIT:
                 ret = BsProcessResetCktReq(ie,iecount,databuff,dataLen,intfCb);
            break;

            case BSSAP_MSG_RESET_CIRCUIT_ACK:
                 ret = BsProcessResetCktAckReq(ie,iecount,intfCb);
            break;
            case BSSAP_MSG_UNEQUIPPED_CKT:
                 ret = BsProcessUnequippedCktReq(ie,iecount,intfCb);
            break;
            case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_RESOURCE_INDICATION:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_LOAD_INDICATION:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_CKT_GROUP_BLOCK:
                 ret = BsProcessCktGroupBlockReq(ie,iecount,databuff,dataLen,intfCb);
            break;
            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                 ret = BsProcessCktGroupUnblockReq(ie,iecount,databuff,dataLen,intfCb);
            break;

            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;
            case BSSAP_MSG_RESET_IP:
                 ret = BsProcessResetIPReq(ie,iecount,databuff,dataLen,intfCb);
            break;
            case BSSAP_MSG_RESET_IP_ACK:
                 /*No handling , directly pass to MSC */
                 LOG_PRINT(INFO,"BsProcessUDTMapProcedures(): No-Need to Handle Just Pass Msgtype[%s] to MSC\n",BSSAP_MSG_TYPE_STR(mType));
                 ret = SS7_SUCCESS;
            break;

          default:  
            LOG_PRINT(CRITICAL,"BsProcessUDTMapProcedures() : Unknown Outgoing UDT msg  \n");
            return (SS7_FAILURE);
        }
        if (ret == SS7_SUCCESS)
        {
           ret = BsSendUDataReq(databuff,dataLen,intfCb);
        }
   }
  return (SS7_SUCCESS); 
}




/*
*
*      Fun:  BsProcessOutBSSAPMessage
*
*      Desc:  This function will process BSSAP(User Data) Msgs coming from APP
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI
S16bit BsProcessOutBSSAPMessage
(
BSSAPData *bdata,
BsIntfCb *intfCb
)
#else
S16bit BsProcessOutBSSAPMessage(bdata,intfCb)
BSSAPData *bdata;
BsIntfCb *intfCb;
#endif
{
   S16bit ret = SS7_SUCCESS;
   BsIntfCb *bsIntfCb = SS7_NULL;
   bsIntfCb = intfCb;
   BsCallCb *call = SS7_NULL;
   
  if(bsIntfCb == SS7_NULL)
   {
     LOG_PRINT(INFO,"BsProcessOutBSSAPMessage():bsIntfCb Null\n");
     return SS7_FAILURE;
   }

   if(bdata->bssId !=  bsIntfCb->bscId)
   {
	LOG_PRINT(INFO,"BsProcessOutBSSAPMessage():BscId mismatch %d",bdata->bssId);
        return SS7_FAILURE;
   } 
   if (bdata->mssgDisc == BSSAP_MD_DTAP)
   {
    LOG_PRINT(INFO,"BS:MSG TO MSC:callrefId[%lu] appId [%lu] [DTAP][%s] \n",bdata->callrefId,bdata->appId,BS_DTAP_MSG_TYPE_STR(bdata->mssgType));
        ret = BsProcessOutDTAPMessage(bdata,bsIntfCb);
        if (ret != SS7_SUCCESS)
        {
          LOG_PRINT(INFO,"BsProcessOutBSSAPMessage: BsProcessOutDTAPMessage failed  \n");
          return SS7_FAILURE;
        }
         /*Increment peg counter */
        BsIncrPegsCounter(DTAP,bdata->mssgType,TRANSMIT,bsIntfCb);
        
    }
    else if (bdata->mssgDisc == BSSAP_MD_BSSMAP)
    {
        ret = BsProcessOutBSSMAPMessage(bdata,bsIntfCb);
        if (ret != SS7_SUCCESS)
        {
          LOG_PRINT(INFO,"BsProcessOutBSSAPMessage: BsProcessOutBSSMAPMessage failed  \n");
          return SS7_FAILURE;
        }
        /*Increment peg counter */
        BsIncrPegsCounter(BSSMAP,bdata->mssgType,TRANSMIT,bsIntfCb);
    }
    else if(bdata->mssgDisc == BSSAP_MD_PROP)
    {
      if(bdata->mssgType == BSSAP_CHG_APPID_CALLREFID_REQ)
      {
        call =  bsFindCall(bsIntfCb,bdata->callrefId); 
        if(call)
        {
         LOG_PRINT(INFO,"BS:MSG TO MSC:[BSSMAP(PROP)]:BSSAP_CHG_APPID_CALLREFID_REQ NwAppId[%d] OldAppId[%d] NwCallRef[%d] 		\n",bdata->appId,call->appId,bdata->callrefId);
          call->appId=bdata->appId;
        }
       else
        {
          /* printf("CallRef Not Found\n");*/
           LOG_PRINT(CRITICAL,"BsProcessOutBSSAPMessage():bsFindCall() No CallRef Found fail");
           return SS7_FAILURE;
        }
     }
    else
     {
        /*  printf("Wrong Msg Type \n");*/
      LOG_PRINT(CRITICAL,"BsProcessOutBSSAPMessage():Wrong Msg PROP CHECK");
     return SS7_FAILURE;
     } 
              
    }
    else
    {
      LOG_PRINT(CRITICAL,"BsProcessOutBSSAPMessage():Invalid MSG Disc: %d ",bdata->mssgDisc);
     return SS7_FAILURE;
    }

     return SS7_SUCCESS;
}

/*
*
*      Fun:  BsProcessOutDTAPMessage
*
*      Desc:  This function will process BSSAP(DTAP Data) Msgs coming from APP
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessOutDTAPMessage
(
BSSAPData *bdata,
BsIntfCb *intfCb
)
#else
S16bit BsProcessOutDTAPMessage(bdata,intfCb)
BSSAPData *bdata;
BsIntfCb *intfCb;
#endif
{
  BsCallCb   *call = SS7_NULL;
  U32bit  callRef;
  S16bit ret = SS7_SUCCESS;
  int i = 0;

  callRef = bdata->callrefId;
      /* find connection */
  call = bsFindCall(intfCb,callRef);
  if (call == SS7_NULL)
  {
     LOG_PRINT(INFO,"In BsProcessOutDTAPMessage:Cannot find the Call pointer in Call list\n");
     return SS7_FAILURE;
  }
  if(call->appId != bdata->appId)
  {
    LOG_PRINT(INFO,"In BsProcessOutDTAPMessage:Recv AppId and  call AppId Mistmatch:call->appId[%d] : bdata->appId[%d] \n",call->appId,bdata->appId);
    return SS7_FAILURE;
  }

/* Here I want to send message to ARICENT SCCP through Socket I/F */

  call->suInstId = bdata->callrefId; 
  /*Send Data Request primitive to SCCP */
  /*printf("SENDIND DT1 for DTAP MSG from BSSAP to SCCP \n");*/
/*  printf("DTAPdata.len = %d \n",bdata->u.DTAPdata.len);*/
  /*for(i = 0; i < bdata->u.DTAPdata.len ; i++)
  {
      printf("DTAP buff[%d] = 0x%x \n",i,bdata->u.DTAPdata.dtapMsg[i]);
  }*/
  ret = BsSendDataReq(call,bdata->u.DTAPdata.dtapMsg,bdata->u.DTAPdata.len);
  if(ret != SS7_SUCCESS)
  {
      LOG_PRINT(CRITICAL,"BsProcessOutDTAPMessage(): BsSendDataReq failed  \n");
      return (SS7_FAILURE);
  }
      return (SS7_SUCCESS);
}

/*
*
*      Fun:  BsProcessOutBSSMAPMessage
*
*      Desc:  This function will process BSSAP(BSSMAP Data) Msgs coming from APP
*
*      Ret:   SS7_SUCCESS   - ok
*
*      Notes: None
*
*      File:
*
*/
#ifdef ANSI_PROTO
S16bit BsProcessOutBSSMAPMessage
(
BSSAPData *bdata,
BsIntfCb *intfCb
)
#else
S16bit BsProcessOutBSSMAPMessage(bdata,intfCb)
BSSAPData *bdata;
BsIntfCb *intfCb;
#endif
{
  Data databuff[BSSAP_DATA_LEN];
  BSSAP_IE ie[100];
  S16bit iecount = 0;
  BSSAP_Hdr hdr;
  U8bit mType = 0;
  BsCallCb   *call = SS7_NULL;
  U32bit  callRef;
  S16bit dataLen = 0;
  S16bit ret = SS7_FAILURE;
  U8bit ssnStatus = 0;
  U8bit pcStatus = 0;

  if(intfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage():No Interface found \n");
    return SS7_FAILURE;
  }

#ifdef Mantis_25390  
  BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
  BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);

  if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  {
    LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
    return SS7_FAILURE;
  }
#endif

  memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
  dataLen = bdata->u.MAPdata.len;
  ss7_memcpy((U8bit *)databuff,(U8bit *)bdata->u.MAPdata.mapMsg,dataLen);

  ret = BsDecode(databuff,dataLen,ie,&iecount,&hdr);
  if(ret != SS7_SUCCESS)
  {
    LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage():Unable to Decode Message \n");
    if(ret == RIGNORE)
    {
      /*Raise Alarm to Stack Manager commented not to send Alarm */
#if 0
      bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
	  LBS_USTA_DGNVAL_SWTCH, (PTR)&intfCb->swtch,
	  LBS_USTA_DGNVAL_MSGTYPE,(PTR)&hdr.msgType,
	  LBS_USTA_DGNVAL_DPC, (PTR)&intfCb->phyDpc);

      bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
	  LBS_EVENT_WRONG_MSG_TYPE, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif 
    }

    BsDispatchErrorToApp(call, BSSAP_MD_PROTOCOL, BSSAP_EDECODE,0,0,intfCb);
    return SS7_FAILURE;
  }
  mType = hdr.msgType;
  if (!BsIsUDT(mType))
  {
    LOG_PRINT(INFO, "BsProcessOutBSSMAPMessage() :Sending to MSC : BSSMAP (DT1) MsgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
    ret = BsDirectionCheck(mType,SS7_FALSE);
    if(ret !=  SS7_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage():Wrong direction MsgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
      /*Raise Alarm to Stack Manager */
#if 0
      bsInitUstaDgn(LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
	  LBS_USTA_DGNVAL_SWTCH, (PTR)&intfCb->swtch,
	  LBS_USTA_DGNVAL_MSGTYPE,(PTR)&mType,
	  LBS_USTA_DGNVAL_DPC, (PTR)&intfCb->phyDpc);

      bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
	  LBS_EVENT_WRONG_MSG_DIRECTION, LCM_CAUSE_INV_PAR_VAL,TRUE);
#endif
      return SS7_FAILURE;

    }
    if(mType == BSSAP_MSG_COMPLETE_LAYER3_INFO)
    {
      /*Allocate a new Callref value in case of CL3I msg from APP*/  
      call = bsCreate_InsertConRef(intfCb);
      if(call == SS7_NULL)
      {
	LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage() :Unable to New Call reference Value\n");
	return SS7_FAILURE;
      }
      call->appId = bdata->appId;
      call->msgType = BSSAP_MSG_COMPLETE_LAYER3_INFO;
      /*Setting calltype as LU_CALL  and this will later update after processing CL3I msg in BsProcessCOMapProcedures
	function*/
      call->callType = LU_CALL;
      LOG_PRINT(INFO,"BS:MSG TO MSC:callrefId[%lu] appId[%lu] [BSSMAP][BSSAP_MSG_COMPLETE_LAYER3_INFO]:CALL ADDED \n",call->suInstId,call->appId);
    } 
    else
    {
      callRef = bdata->callrefId;
      /* find connection */
      call =  bsFindCall(intfCb,callRef);
      if (call == SS7_NULL)
      {
	LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage():Cannot find the Call pointer in Call hash list\n");
	return SS7_FAILURE;
      }
      if(bdata->mssgType == BSSAP_MSG_HANDOVER_REQUEST_ACK)
      {
	LOG_PRINT(INFO,"BsProcessOutBSSMAPMessage():Filling App Id in case of BSSAP_MSG_HANDOVER_REQUEST_ACK from APP \n");
	call->appId = bdata->appId;
      }
      LOG_PRINT(INFO,"BS:MSG TO MSC:callrefId[%lu] appId[%lu] [BSSMAP] [%s] \n",call->suInstId,call->appId,BSSAP_MSG_TYPE_STR(bdata->mssgType));
    }
    ret = BsProcessCOMapProcedures(call,ie,iecount,databuff,dataLen,mType,SS7_FALSE,intfCb);
    if(ret !=  SS7_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage() :BsProcessCOMapProcedures failed for MsgType:%s  \n",BSSAP_MSG_TYPE_STR(mType));
      return (SS7_FAILURE);
    }
  }
  else
  {
    LOG_PRINT(INFO,"BS:MSG TO MSC: UDT [BSSMAP] [%s] \n",BSSAP_MSG_TYPE_STR(mType));

    ret = BsProcessUDTMapProcedures(mType,ie,iecount,databuff,dataLen,SS7_FALSE,intfCb);
    if(ret != SS7_SUCCESS)
    {
      LOG_PRINT(CRITICAL,"BsProcessOutBSSMAPMessage(): BsProcessUDTMapProcedures failed  \n");
      return (SS7_FAILURE);
    }

  }
      return (SS7_SUCCESS);
}


