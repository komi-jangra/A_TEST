/*******************************************************************************
**      FILE NAME:
**          bs_bdy5.c
**
**      DESCRIPTION:
**              This files defines the source code for find Callptr,IntfPtr,Insert Conn,BuildRLSD .
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

/* local defines */
#define F FALSE
#define T TRUE

/* support functions */
extern int source_point_code;
extern int rem_pc,bs_log_user_id,bsc_id,bsc_ssn_bssap;

BsCb bsCb;

BsIntfCb *bsGetIntfPtr(U8bit bscId,S16bit swtch);
#ifdef SCM_CHG
#include "nwstkscm_msgdef.h"
#include "nwstkscm_hashdefs.h"
extern int bs_intf_id;
#endif

/*
*
*       Fun:   bsGetIntfPtrFrmCallRef
*
*       Desc:  First get intfId from callref and then get the intf pointer.
*
*       Ret:   ROK      - ok
*
*       Notes: None
*/
#ifdef ANSI_PROTO
BsIntfCb* bsGetIntfPtrFrmCallRef
(
U32bit callref,
S16bit swtch
)
#else
PUBLIC BsIntfCb* bsGetIntfPtrFrmCallRef(callref,swtch)
U32bit callref;
S16bit  swtch;
#endif
{
  U8bit  bscId;
  BsIntfCb *bsIntfCb = SS7_NULL;
   /*bscId = mscId in case of Aflex */ 
  /* bscId  is inserted at 2nd MSB  at the time of call */ 
  bscId = ((callref & 0x00ff0000) >> 0x10);
  LOG_PRINT(INFO,"BS: BS:bsGetIntfPtrFrmCallRef :callref[%lu] : bscId [%d] :swtch[%d] \n",callref,bscId,swtch);

  bsIntfCb = bsGetIntfPtr(bscId,swtch); 
  if(bsIntfCb != SS7_NULL)
  {
    LOG_PRINT(INFO,"BS:bsGetIntfPtrFrmCallRef :Found Interface for bscId[%d] intfId[%d] :bsIntfCb[0x%x] \n",bscId,bsIntfCb->intfId,bsIntfCb);
  }
 
  return (bsIntfCb);
}
/*
*
*       Fun:   bsFindCall
*
*       Desc:  Finds a call control block entry from Call list
*              based on callrefId
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/

#ifdef ANSI_PROTO
BsCallCb* bsFindCall
(
BsIntfCb *intfCb,
U32bit id
)
#else
BsCallCb* bsFindCall(intfCb,id)
BsIntfCb *intfCb;
U32bit  id;
#endif
{
  BsLcfRef *CallRef = SS7_NULL;      /* source local reference */
  U32bit index = 0; 
#ifdef BSSAP_HA
  HashEntry *callEntry = NULL;
  int result = -1;
#endif
 // LOG_PRINT(INFO,"bsFindCall:callRef value is %d \n",id);

  if(intfCb == SS7_NULL)
  {
   LOG_PRINT(INFO,"bsFindCall():intfCb NULL \n");
   return ((BsCallCb *) SS7_NULL);
  }
  if(id < 0)
  {
   LOG_PRINT(INFO,"bsFindCall():CallRefId is less than equal to zero \n");
   return ((BsCallCb *) SS7_NULL);
  }
  
   index = id;
  if(index > bsCb.genCfg.nmbMaxCRef)
  {
   LOG_PRINT(INFO,"bsFindCall():Index exceeds bsCb.genCfg.nmbMaxCRef value \n");
   return ((BsCallCb *) SS7_NULL);
  }
#ifdef BSSAP_HA
  result = HashListTbSearch(intfCb->callRefList,BSHASH_TABLE_CALLREF_CTXT,&id,sizeof(U32bit),&callEntry);
  if((result ==  ROK) && (callEntry != NULL))
  {
    LOG_PRINT(INFO,"bsFindCall(): CALL FOUND SUCCESS with callref[%d] in HASH LIST \n",index);
    return((BsCallCb*)callEntry->data);
  }
  else
  {
  //  LOG_PRINT(INFO,"bsFindCall(): %d  Not Found",index);
   return ((BsCallCb *) SS7_NULL);
  }
#else
  CallRef = (intfCb->lcfRef[index-1]);
  if(CallRef)
  { 
    printf("bsFindCall: CALL Found for Callref[%ld] \n",index);
    return (CallRef->callCb);
  }
  else
  {
    LOG_PRINT(INFO,"bsFindCall(): %d  Not Found",index);
   return ((BsCallCb *) SS7_NULL);
  }
#endif
} /* end of bsFindCall */

/*
*
*       Fun:   bsFindCallUsingspInstId
*
*       Desc:  Finds a call control block entry from Call list
*              based on spInstId
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/
#ifdef ANSI_PROTO
BsCallCb* bsFindCallUsingspInstId
(BsIntfCb *intfCb,
U32bit  connectionId
)
#else
BsCallCb* bsFindCallUsingspInstId(intfCb,connectionId)
BsIntfCb *intfCb;
U32bit connectionId;
#endif
{
  BsLcfRef *CallRef = SS7_NULL;      /* source local reference */
  U32bit i = 0,index = 0;
 if(intfCb == SS7_NULL)
  {
   LOG_PRINT(INFO,"bsFindCallUsingspInstId: No Interface Configured: intfCb is NULL");
   return ((BsCallCb *) SS7_NULL);
  }
  if(connectionId < 0)
  {
   LOG_PRINT(INFO,"bsFindCallUsingspInstId: Invalid connectionId[%ld] \n",connectionId);
   return ((BsCallCb *) SS7_NULL);
  }
   LOG_PRINT(INFO,"bsFindCallUsingspInstId: Search Callref PTR for connectionId[%ld] \n",connectionId);
	for(i =(intfCb->nextLr); i > 0 ; i--)
 	{
//		LOG_PRINT(INFO,"bsFindCallUsingspInstId: Max Cref loop Search i[%d] \n",i);
     		index = i -1;
		if(intfCb->lcfRef)
		{
     		CallRef = (intfCb->lcfRef[index]);
     		if(CallRef)
     		{
       		   if((CallRef->callCb != SS7_NULL) && (CallRef->callCb->spInstId == connectionId))
       		    {
  			LOG_PRINT(INFO,"bsFindCallUsingspInstId SUCCESS:CALL Found: spInstId[%d] suInstId[%d] connectionId[%d] \n",CallRef->callCb->spInstId,CallRef->callCb->suInstId,connectionId);
	               return (CallRef->callCb);
       		    }
       		    else
      		    {
/*		      LOG_PRINT(INFO,"bsFindCallUsingspInstId:Still searching calllist for connId[%ld] \n",connectionId);*/
		      continue;
       		   }
                }
     		else
     		{
		  /*     LOG_PRINT(INFO,"bsFindCallUsingspInstId: NO CALL Found:Still searching \n"); */
		       continue;
     		}
		}
  	}
		for (i =(bsCb.genCfg.nmbMaxCRef);i > 0;i--)
		{
   
//		LOG_PRINT(INFO,"bsFindCallUsingspInstId: Max Search i[%d] \n",i);
     		index = i -1;
		if(intfCb->lcfRef)
		{
     		CallRef = (intfCb->lcfRef[index]);
     		if(CallRef)
     		{
       		   if((CallRef->callCb != SS7_NULL) && (CallRef->callCb->spInstId == connectionId))
       		    {
  			LOG_PRINT(INFO,"bsFindCallUsingspInstId_MAX_CALL LOOP SUCCESS:CALL Found: spInstId[%d] suInstId[%d] connectionId[%d] \n",CallRef->callCb->spInstId,CallRef->callCb->suInstId,connectionId);
	               return (CallRef->callCb);
       		    }
       		    else
      		    {
		    /*  LOG_PRINT(INFO,"bsFindCallUsingspInstId_MAX_CALL:Still searching calllist for connId[%ld] \n",connectionId); */
		      continue;
       		   }
                }
     		else
     		{
		     /*LOG_PRINT(INFO,"bsFindCallUsingspInstId_MAX_CALL:NO CALL Found:Still searching \n");*/
		       continue;
     		}
		}
		}
	  LOG_PRINT(INFO,"bsFindCallUsingspInstId:FAIL:NO CALL Found for for ConnId[%ld] i[%d]\n",connectionId,i);
  	  return ((BsCallCb *) SS7_NULL);
}

/*
*
*       Fun:   bsBldDisEvt
*
*       Desc:  build disEvt structure for SCCP messages
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:
*
*/

#ifdef ANSI_PROTO
S16bit bsBldDisEvt
(
SpConId *conId,
U8bit sccpMsgType,
BsIntfCb *intfCb
)
#else
S16bit bsBldDisEvt(conId,sccpMsgType,intfCb)
SpConId *conId;
U8bit sccpMsgType;
BsIntfCb *intfCb;
#endif
{
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
     LOG_PRINT(INFO,"bsBldDisEvt(): Input Parameters NULL");
     return (SS7_SUCCESS);
  }
  if(sccpMsgType == SCCP_MSG_CREF || sccpMsgType == SCCP_MSG_RLSD)
  {
    LOG_PRINT(INFO,"bsBldDisEvt():  Dis Req for callrefId[%ld] conId[%d] \n",conId->suInstId,conId->spInstId);
  	api_len = API_HEADER_LEN;
  	num_elem = SCCP_N_DISCONNECT_IND_NELEM -1; /* 2 MF element */
   
  /* Fixed parameter length */
  	api_len += (SCCP_ELEM_CONNECTION_ID_LEN + SCCP_ELEM_REFUSAL_CAUSE_LEN);

  /* No mandatory variable parameter */

  /* Optional parameters */
/* addressing data */
     /* In case of CREF , rspAddr is  present */
/* Insert the calling party details */
    p_cg_add.pc_ind = SS7_TRUE;
    p_cg_add.ssn_ind = SS7_TRUE;
    p_cg_add.gti = SS7_FALSE;
    p_cg_add.rout_ind = ROUTE_ON_SSN; /* ROUTE_ON_SSN =1 ROUTE_ON_GT=0 */
    p_cg_add.pc = source_point_code;     /* This is derived from BSSAP Interface Configuration */
    p_cg_add.ssn = bsc_ssn_bssap;/* This is derived from Confoguration File 254 */
   
    api_len += (SCCP_ELEM_ID_LEN + SCCP_ELEM_LEN_LEN + sccp_addr_len (&p_cg_add));
    num_elem++;
    
   api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_LOG_USER_ID_LEN);
    num_elem++;

   api_len += (SCCP_ELEM_ID_LEN +
          SCCP_ELEM_LEN_LEN +
          SCCP_ELEM_CORR_ID_LEN);
    num_elem++;

   /* allocate a buffer to build the API */
  if ((p_api=(U8bit *)bssap_malloc(api_len)) == (U8bit *)SS7_NULL)
  {
    LOG_PRINT(INFO,"SCCP::CO: cannot send [malloc_fail]disconnect Req msg to SCCP from BSSAP");
    return ;
  }

  sccp_fill_api_header (p_api, SCCP_N_DISCONNECT_REQUEST, num_elem, api_len);

  p_elem = p_api + SS7_API_HEADER_LEN;

  /* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
  PUT_4_BYTE_LE (p_elem, conId->spInstId);
#else
  PUT_2_BYTE_LE (p_elem, conId->spInstId);
#endif
  p_elem += SCCP_ELEM_CONNECTION_ID_LEN;

  *p_elem =  SCCP_RFC_END_USER_ORIGINATED;
   p_elem += SCCP_ELEM_REFUSAL_CAUSE_LEN;
   
 /* NO Mandatory variable parameter */

  /* Optional parameters */
   /* Responding Address */

   *p_elem = SCCP_ELEM_RESPONDING_ADDR;
    p_elem += SCCP_ELEM_ID_LEN;
    p_tmp = p_elem;
    /*   Leave a one byte space as lengths in APIs are two bytes
      and following function assume first byte as a length and
      address is coded in rest of other bytes.
    */
    p_elem = sccp_encode_sccp_addr ((p_elem + 1), &p_cg_add);

    /* Move the length to the first byte of length field */
    *p_tmp = *(p_tmp + 1);
    *(p_tmp + 1) = (U8bit)SS7_NULL;

	/* LOG_USER_ID */
    *p_elem = SCCP_ELEM_LOG_USER_ID;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_2_BYTE_LE (p_elem, SCCP_ELEM_LOG_USER_ID_LEN);
    p_elem += SCCP_ELEM_LEN_LEN;

    PUT_2_BYTE_LE (p_elem, bs_log_user_id);
    p_elem += SCCP_ELEM_LOG_USER_ID_LEN;

	/* CORR-ID */
    *p_elem = SCCP_ELEM_CORR_ID;
    p_elem += SCCP_ELEM_ID_LEN;

    PUT_4_BYTE_LE (p_elem, SCCP_ELEM_CORR_ID_LEN);/* Change 2byte to 4byte as on dated 20-01-16 */
    p_elem += SCCP_ELEM_LEN_LEN;

#ifdef SCCP_CONNECTION_ID_CHANGES
   PUT_4_BYTE_LE (p_elem, conId->suInstId);
   p_elem += SCCP_ELEM_CORR_ID_LEN;
#endif
  }
    src_id = BSSAP_MODULE_ID;
    dst_id = SCCP_MODULE_ID;
    /* Send BSSAP Data to SCCP through SCCP_N_DISCONNECT_REQUEST REQ */
    send_from_bssap_to_sccp(p_api,api_len,src_id,dst_id,&ecode);
    if(p_api)
    {
        bssap_free (p_api);
    }
    LOG_PRINT(INFO,"bsBldDisEvt(): send disconnect Req  to SCCP from BSSAP:SUCCESS");

  return (SS7_SUCCESS);

}

/*
*
*       Fun:   bsGetIntfPtr
*
*       Desc:  Gets pointer to interface Control Block
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/

#ifdef ANSI_PROTO
BsIntfCb *bsGetIntfPtr
(
U8bit       bscId,
S16bit    swtch
)
#else
BsIntfCb *bsGetIntfPtr(bscId, swtch)
U8bit       bscId;
S16bit    swtch;
#endif
{

  S16bit i;
  BsIntfCb *entry;

  entry = SS7_NULL;

   LOG_PRINT(INFO,"bsGetIntfPtr: GET INTERFACE for bscId[%d] : swtch[%s] \n",bscId,BS_PRINT_SWTCH_TYPE(swtch));
  for (i = 0; i < bsCb.genCfg.nmbMaxIntf; i++)
  {
      entry = BSFINDINTF(i);
      if ((entry != SS7_NULL) && (entry->bscId == bscId)
                  && (BSCMPNT(entry->swtch, swtch)))
      {
        LOG_PRINT(INFO,"bsGetIntfPtr: InterfacePtr[%p] Found for  bscId %d switch %d phyDpc %d\n",entry,bscId,swtch,entry->phyDpc);
         break;
      }
  }

   if (i == bsCb.genCfg.nmbMaxIntf)
   {
       
/*      printf("bsGetIntfPtr:can not get Interface Ptr for bscId %d switch %d: exceeds nmbMaxIntf[%d]\n", bscId,swtch,bsCb.genCfg.nmbMaxIntf);*/
      LOG_PRINT(INFO,"bsGetIntfPtr:exceeds Intf");
      return (SS7_NULL);	
   }

   // LOG_PRINT(INFO,"bsGetIntfPtr: Return InterfacePtr[%x] \n",entry);
   return (entry);

}
/*
*
*       Fun:   bsGetIntfPtrFrmDPC
*
*       Desc:  Gets pointer to interface Control Block based on DPC and variant
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  bs_bdy5.c
*
*/

#ifdef ANSI_PROTO
BsIntfCb *bsGetIntfPtrFrmDPC
(
U32bit   aDPC,
S16bit   swtch
)
#else
BsIntfCb *bsGetIntfPtrFrmDPC(aDPC, swtch)
U32bit    aDPC;
S16bit    swtch;
#endif
{

  S16bit i;
  BsIntfCb *entry = SS7_NULL;

  entry = SS7_NULL;

  for (i = 0; i < bsCb.genCfg.nmbMaxIntf; i++)
  {
      entry = BSFINDINTF(i);
      if ((entry != SS7_NULL) && (entry->phyDpc == aDPC)
                  && (BSCMPNT(entry->swtch, swtch)))
      {
        LOG_PRINT(INFO,"bsGetIntfPtrFrmDPC: InterfacePtr[%x] found for  switch %d phyDpc %d\n",entry,swtch,entry->phyDpc);
         break;
      }
  }

   if (i == bsCb.genCfg.nmbMaxIntf)
   {
       
      LOG_PRINT(INFO,"bsGetIntfPtrFrmDPC:exceeds Intf");
      return (SS7_NULL);	
   }
	return (entry);

}

/*
*
*       Fun:   bsCreate_InsertConRe
*
*       Desc:  This function will allocate new callref value
*
*       Ret:   ROK      - ok
*              RFAILED  - if failure in addition
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/
#ifdef ANSI_PROTO
BsCallCb *bsCreate_InsertConRef
(
BsIntfCb   *intfCb
)
#else
BsCallCb *bsCreate_InsertConRef(intfCb)
BsIntfCb   *intfCb;
#endif
{

   BsLcfRef *CallRef =SS7_NULL;      /* source local reference */
   BsLcfRef *Call =SS7_NULL;      /* source local reference */
   U8bit found =SS7_FALSE;           /* flag to indicate entry found or not */
   U32bit i;              /* loop counter */
   U32bit j;              /* loop counter */
   U32bit nextLr;         /* next lclRef */
   U32bit newLr;         /* next lclRef */
   BsCallCb *cb;
   S16bit ret;
#ifdef BSSAP_HA
   int result = -1;
#endif
   if(intfCb == SS7_NULL)
   {
      LOG_PRINT(INFO,"bsCreate_InsertConRef:intfCb NULL");
      return SS7_NULL;
   }
   if (intfCb->nmbLr == bsCb.genCfg.nmbMaxCRef)
   {
#if (ERRCLASS & ERRCLS_DEBUG)
         BSLOGERROR(ERRCLS_ADD_RES, EBS783, (ErrVal) ret,
                    "bsCreate_InsertConRef(): nmbLr equal to  nmbMaxCRef\n");
#endif
      LOG_PRINT(INFO,"bsCreate_InsertConRef:nmbLr equal to  nmbMaxCRef\n");
      BSERRORPRINT("BS: bsCreate_InsertConRef(): nmbLr[%lu] : nmbMaxCRef[%lu] \n",intfCb->nmbLr,bsCb.genCfg.nmbMaxCRef);
      LOG_PRINT(INFO,"bsCreate_InsertConRef:nmbLr equal to  nmbMaxCRef");
    /*  return SS7_NULL;*//* Commented  not to return NULL */
   }
/* Added  start for Check MAX value */
 if(intfCb->nextLr == bsCb.genCfg.nmbMaxCRef)/* Before only == */
  {
    intfCb->nextLr=0;
  }

/* Added stop for Check MAX value */
  nextLr = intfCb->nextLr; /*initial set by zero*/

      //LOG_PRINT(INFO,"bsCreate_InsertConRef:nextLr [%d]\n ",nextLr);
 /* printf("bsCreate_InsertConRef:nextLr[%ld]\n",nextLr);*/
  for (i = nextLr, j = 0; j < bsCb.genCfg.nmbMaxCRef; j++)
   {
      /*Call = intfCb->lcfRef[i];*/
       Call = *(intfCb->lcfRef + i);
      if (Call == (BsLcfRef *) SS7_NULL)
      {
         found = SS7_TRUE;
         newLr=i;  
         break;
      }

      i++;
      LOG_PRINT(INFO,"bsCreate_InsertConRef:value of i  [%d]",i);
      if (i == bsCb.genCfg.nmbMaxCRef)
         i = 0;
   }
    if (!found)
      return SS7_NULL;
	
/*    ret = SGetSBuf(bsCb.init.region, bsCb.init.pool,
                     (Data **) &CallRef,
                     (Size)(sizeof(BsLcfRef)));*/

    CallRef  =  (unsigned char *)bssap_malloc((sizeof(BsLcfRef)));
 
    if (CallRef == SS7_NULL)
    {
         LOG_PRINT(CRITICAL,"bsCreate_InsertConRef(): bssap_malloc failed for lcfRef\n");
	 return SS7_NULL;
    }

   /* Get the buffer */
/*   ret = SGetSBuf(bsCb.init.region, bsCb.init.pool, (Data **) &cb,
                  (Size) sizeof(BsCallCb));*/
 
   cb  =  (unsigned char *)bssap_malloc((sizeof(BsCallCb)));
    
   if (cb == SS7_NULL)
    {
         LOG_PRINT(CRITICAL,"bsCreate_InsertConRef(): bssap_malloc failed for call ptr (cb)\n");
	 return SS7_NULL;
   }
   /* zero out control block */
  ss7_mem_zero((U8bit *) cb, sizeof(BsCallCb));
  cb->timerId = BSSAP_INVALID_TMRID;
  cb->intfCb = intfCb;
  *(intfCb->lcfRef + newLr) = CallRef;
  cb->suInstId= newLr+1; /*always include from 1 value  from 0 onwards */
  cb->spInstId= 0x0000FFFF; /*always include from 1 value  from 0 onwards */
  intfCb->nmbLr++;
  intfCb->nextLr++;
  CallRef->callCb = cb;
      LOG_PRINT(INFO,"bsCreate_InsertConRef(): Adding CALL for intfId[%d] intfCb->nmbLr[%d] intfCb->nextLr++[%d] \n",intfCb->intfId,intfCb->nmbLr,intfCb->nextLr);
/* Commented start for MAX */
#if 0
 if(cb->intfCb->nextLr == bsCb.genCfg.nmbMaxCRef)/* Before only == */
  {
    cb->intfCb->nextLr=0;
  }
#endif
/* Commented  stop for MAX */
  CallRef->allocateFfg= SS7_TRUE;
/* Pending Activity for Timers */
/*  cmInitTimers(cb->timers, MAXSIMTIMER);*//* Need to be modified  Later*/
/*  printf(" New Call Refernce Allocated [%ld] : nmbLr[%ld]: nextLr[%ld] \n",cb->suInstId,intfCb->nmbLr,intfCb->nextLr);*/
#ifdef BSSAP_HA
  result = HashListTbInsert(intfCb->callRefList,intfCb->intfId,BSHASH_TABLE_CALLREF_CTXT,&cb->suInstId,sizeof(U32bit),cb,sizeof(BsCallCb));
  if(result == ROK)
  {
   LOG_PRINT(INFO,"BSSAP_HA:bsCreate_InsertConRef() : Callref[%d] Added Successfully \n",cb->suInstId);
   return cb;
  } 
  else
  {
   LOG_PRINT(CRITICAL,"BSSAP_HA:bsCreate_InsertConRef(): CALL with callref[%d]:intfId[%d]  INSERT Failed  \n",cb->suInstId,intfCb->intfId);
   bssap_free((BsCallCb *) cb);
   return SS7_NULL;
  }
#else
   LOG_PRINT(INFO,"bsCreate_InsertConRef(): Callref[%d] Added Successfully \n",cb->suInstId);
  return cb;
#endif
}
/*
*
*       Fun:   bsDeallocateConRef
*
*       Desc:  This function will deallocate given callref value
*
*       Ret:   ROK      - ok
*              RFAILED  - if failure in addition
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/
#ifdef ANSI_PROTO
S16bit bsDeallocateConRef
(
BsCallCb   *cb
)
#else
S16bit bsDeallocateConRef(cb)
BsCallCb   *cb;
#endif
{
   BsLcfRef *CallRef = SS7_NULL;
   U32bit index= 0;
#ifdef BSSAP_HA
   int result = -1;
#endif

   if(cb == SS7_NULL)
   {
     LOG_PRINT(CRITICAL,"bsDeallocateConRef(): CALL Pointer is NULL \n");
     return (SS7_FAILURE);
   }
   index = (cb->suInstId  & 0x0000ffff) -1; /* Change (cb->suInstId  & 0x0000ffff ) -1  */ 
/*     printf("bsDeallocateConRef: DeAllocating Call with callrefValue[%ld] index [%ld] CallPtr[%x]\n",(cb->suInstId & 0x0000ffff),index,cb);*/
   if(index < 0)
   {
     LOG_PRINT(CRITICAL,"bsDeallocateConRef(): index value less than zero \n");
     return (SS7_FAILURE);
   }
   if(cb->intfCb == SS7_NULL)
   {
     LOG_PRINT(CRITICAL,"bsDeallocateConRef(): Interface pointer in call is NULL \n");
     return (SS7_FAILURE);
   }
   CallRef = cb->intfCb->lcfRef[index];
   if(CallRef == (BsLcfRef *) SS7_NULL)
   {
     LOG_PRINT(CRITICAL,"bsDeallocateConRef(): CallRef pointer (type BsLcfRef) is NULL \n");
     return (SS7_FAILURE);
   }
  // LOG_PRINT(INFO,"bsDeallocateConRef: CALL DELETE for suInstId[%lu]spInstId[%lu]:AppId[%lu] nmbLr[%lu] \n",cb->suInstId,cb->spInstId,cb->appId,cb->intfCb->nmbLr);
     
#ifdef BSSAP_HA
   result = HashListTbDelete(cb->intfCb->callRefList,
                             cb->intfCb->intfId,
			     BSHASH_TABLE_CALLREF_CTXT,
			     &cb->suInstId,
			     sizeof(U32bit));
   if(result == ROK)
   {
   
     cb->intfCb->nmbLr--;
     bssap_free((BsLcfRef *) CallRef);
     CallRef = SS7_NULL;
     cb->intfCb->lcfRef[index]=SS7_NULL;
     bssap_free((BsCallCb *) cb);
     cb = SS7_NULL;
     LOG_PRINT(INFO,"BSSAP_HA:bsDeallocateConRef(): Call deallocated successfully \n");
     return (SS7_SUCCESS);
   } 
   else
   {
     LOG_PRINT(CRITICAL,"BSSAP_HA:bsDeallocateConRef(): fail to deallocate call \n");
     return (SS7_FAILURE);
   }
#else
   cb->intfCb->nmbLr--;
   bssap_free((BsLcfRef *) CallRef);
   CallRef = SS7_NULL;
   cb->intfCb->lcfRef[index]=SS7_NULL;
   bssap_free((BsCallCb *) cb);
   cb = SS7_NULL;
   LOG_PRINT(INFO,"bsDeallocateConRef(): Call deallocated successfully \n");
   return (SS7_SUCCESS);
#endif
}

/*
*
*       Fun:   bsFindCallForAbnormalRLSD
*
*       Desc:  Finds a call control block entry from Call list
*              based on appID
*
*       Ret:   ROK      - ok
*
*       Notes: None
*
*       File:  ci_bdy5.c
*
*/

#ifdef ANSI_PROTO
BsCallCb* bsFindCallForAbnormalRLSD
(
BsIntfCb *intfCb,
U32bit appid
)
#else
BsCallCb* bsFindCallForAbnormalRLSD(intfCb,appid)
BsIntfCb *intfCb;
U32bit appid;
#endif
{

  BsLcfRef *CallRef = SS7_NULL;      /* source local reference */
  U32bit i = 0,index = 0;

   LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): appId[%d]\n",appid);
  if(intfCb == SS7_NULL)
  {
   LOG_PRINT(CRITICAL,"bsFindCallForAbnormalRLSD(): No Interface Configured: intfCb is NULL  \n");
   return ((BsCallCb *) SS7_NULL);
  }
  if(appid <= 0)
  {
   LOG_PRINT(CRITICAL,"bsFindCallForAbnormalRLSD(): Invalid appid[%ld] \n",appid);
   return ((BsCallCb *) SS7_NULL);
  }
 LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): Start Searching Calllist for AppId[%ld] \n",appid);
 LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): intfCb->nextLr[%ld] \n",intfCb->nextLr);
 for(i =(intfCb->nextLr); i > 0 ; i--)
 {
     index = i -1;
     CallRef = (intfCb->lcfRef[index]);
     LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): CallRefPtr [%x] callrefValue[%ld] \n",CallRef,i);
     if(CallRef)
     {
	LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): CallRef->callCb[%x] CallRef->callCb->appId[%ld] \n",CallRef->callCb,CallRef->callCb->appId);
       if((CallRef->callCb != SS7_NULL) && (CallRef->callCb->appId == appid))
       {
          LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD():SUCESS:CALL Found for AppId [%ld] with Callref[%ld] \n",appid,i);
          RETVALUE(CallRef->callCb);
       }
       else
       {
          LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): Still searching calllist for AppId[%ld] \n",appid);
          continue;
       }
     }
     else
     {
       LOG_PRINT(INFO,"bsFindCallForAbnormalRLSD(): NO CALL Found:Still searching \n");
       continue;
     }
  }

   LOG_PRINT(CRITICAL,"bsFindCallForAbnormalRLSD():FAIL:NO CALL Found for for AppId[%ld] \n",appid);
  
  return ((BsCallCb *) SS7_NULL);
}
#ifdef SCM_CHG
int bsCfgIntfCb(ScmBsInterfaceConfig *cfg)
{
    
  BsIntfCb *bsIntfCb = SS7_NULL;   
  int ret = 0;

  if(cfg == NULL)
  {
    LOG_PRINT(CRITICAL,"bsCfgIntfCb():cfg ptr is NULL \n");
    return NWSTK_WRONG_PARAM;
  }
    
  LOG_PRINT(INFO,"bsCfgIntfCb():Request to Add Interface with intfId[%d] recv from SCM\n",cfg->bscId);
 
  bs_intf_id = cfg->bscId;   
  if(bs_intf_id >= (S16bit) bsCb.genCfg.nmbMaxIntf)
  {
    LOG_PRINT(CRITICAL,"bsCfgIntfCb():Interface Id greater than nmbMaxIntf value[%d]\n",bsCb.genCfg.nmbMaxIntf);
    return NWSTK_INVAILD_BSCID;
  }
  bsIntfCb = BSFINDINTF(bs_intf_id);
  if (bsIntfCb != SS7_NULL)
  {
    LOG_PRINT(INFO,"bsCfgIntfCb():Interface with intfId[%d] Is already Configured, Reconfiguring it \n",bs_intf_id);
    if(cfg->timer_T1)
    {
      bsIntfCb->t1.enb = SS7_TRUE;
      bsIntfCb->t1.val = cfg->timer_T1;
      bsIntfCb->t1.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T4)
    {
      bsIntfCb->t4.enb = SS7_TRUE;
      bsIntfCb->t4.val = cfg->timer_T4;
      bsIntfCb->t4.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T10)
    {
      bsIntfCb->t10.enb = SS7_TRUE;
      bsIntfCb->t10.val = cfg->timer_T10;
      bsIntfCb->t10.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T11)
    {
      bsIntfCb->t11.enb = SS7_TRUE;
      bsIntfCb->t11.val = cfg->timer_T11;
      bsIntfCb->t11.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T13)
    {
      bsIntfCb->t13.enb = SS7_TRUE;
      bsIntfCb->t13.val = cfg->timer_T13;
      bsIntfCb->t13.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T17)
    {
      bsIntfCb->t17.enb = SS7_TRUE;
      bsIntfCb->t17.val = cfg->timer_T17;
      bsIntfCb->t17.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T25)
    {
      bsIntfCb->t25.enb = SS7_TRUE;
      bsIntfCb->t25.val = cfg->timer_T25;
      bsIntfCb->t25.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_Trbsc)
    {
      bsIntfCb->trbsc.enb = SS7_TRUE;
      bsIntfCb->trbsc.val = cfg->timer_Trbsc;
      bsIntfCb->trbsc.timer_id_key = SS7_FALSE;
    }

    ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
    if(ret == RFAILED)
    {
      LOG_PRINT(CRITICAL,"bsCfgIntfCb(): SendInterfaceAddUpdateToPeer Failed \n");
    }
    LOG_PRINT(INFO,"bsCfgIntfCb():Interface with intfId[%d]  Reconfigured Successfully \n",bs_intf_id);
    return NWSTK_CMD_CNG_SUCCESS;
  }
  else
  {
    LOG_PRINT(INFO,"bsCfgIntfCb():Adding NEW Interface intfId[%d]\n",bs_intf_id);
    /* Allocate memory for the Interface control block */
    bsIntfCb  = (BsIntfCb *) bssap_malloc (sizeof(BsIntfCb));
    if(bsIntfCb == SS7_NULL)
    {
      LOG_PRINT(CRITICAL,"bsCfgIntfCb():could not allocate memory to bsIntfCb ptr");
      return NWSTK_BSSAPCFGADD_FAIL;
    }
    memset((U8bit *)bsIntfCb,0,sizeof(BsIntfCb));

    bsIntfCb->intfId = bs_intf_id;
    bsIntfCb->bscId = cfg->bscId;
    bsIntfCb->ni = cfg->ni;
    bsIntfCb->opc = cfg->opc;
    bsIntfCb->phyDpc = cfg->dpc;
    /* Updating global variable for src & destination PointCode */
    source_point_code = cfg->opc;
    rem_pc            = cfg->dpc;
    bsIntfCb->swtch = cfg->variant;       /* user */
    if(cfg->timer_T1)
    {
      bsIntfCb->t1.enb = SS7_TRUE;
      bsIntfCb->t1.val = cfg->timer_T1;
      bsIntfCb->t1.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T4)
    {
      bsIntfCb->t4.enb = SS7_TRUE;
      bsIntfCb->t4.val = cfg->timer_T4;
      bsIntfCb->t4.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T10)
    {
      bsIntfCb->t10.enb = SS7_TRUE;
      bsIntfCb->t10.val = cfg->timer_T10;
      bsIntfCb->t10.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T11)
    {
      bsIntfCb->t11.enb = SS7_TRUE;
      bsIntfCb->t11.val = cfg->timer_T11;
      bsIntfCb->t11.timer_id_key = SS7_FALSE;
    }
  
    if(cfg->timer_T13)
    {
      bsIntfCb->t13.enb = SS7_TRUE;
      bsIntfCb->t13.val = cfg->timer_T13;
      bsIntfCb->t13.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T17)
    {
      bsIntfCb->t17.enb = SS7_TRUE;
      bsIntfCb->t17.val = cfg->timer_T17;
      bsIntfCb->t17.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T18)
    {
      bsIntfCb->t18.enb = SS7_TRUE;
      bsIntfCb->t18.val = cfg->timer_T18;
      bsIntfCb->t18.timer_id_key = SS7_FALSE;
    }
    if(cfg->timer_T25)
    {
      bsIntfCb->t25.enb = SS7_TRUE;
      bsIntfCb->t25.val = cfg->timer_T25;
      bsIntfCb->t25.timer_id_key = SS7_FALSE;
    }
  
    if(cfg->timer_Trbsc)
    {
      bsIntfCb->trbsc.enb = SS7_TRUE;
      bsIntfCb->trbsc.val = cfg->timer_Trbsc;
      bsIntfCb->trbsc.timer_id_key = SS7_FALSE;
    }
  
    bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->rstSndtimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->TrbsctimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->overloadT17 = BSSAP_INVALID_TMRID;
    bsIntfCb->overloadT18 = BSSAP_INVALID_TMRID;
    bsIntfCb->resetRetryCount = 0;
    bsIntfCb->resetIPRetryCount = 0;
    /* Allocate memory for the Interface control block */
    bsIntfCb->lcfRef  = (BsLcfRef *) bssap_malloc ((bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));
    if(bsIntfCb->lcfRef == SS7_NULL)
    {
      LOG_PRINT(CRITICAL,"bsCfgIntfCb():could not allocate memory to bsIntfCb->lcfRef ptr \n");
      bssap_free(bsIntfCb);
      bsIntfCb = SS7_NULL;
      return NWSTK_BSSAPCFGADD_FAIL;
    }
    bsIntfCb->databuf = SS7_NULL;
    memset((U8bit *)bsIntfCb->lcfRef, 0 ,(bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));
    *(bsCb.intfLst + bs_intf_id) = bsIntfCb;
    bsCb.nmIntf++;
#ifdef BSSAP_HA
    BsHashInitHashList(bs_intf_id);
#endif
/*Note : Start:To BE Removed:For local testing only */
#ifdef BSSAP_HA
#ifdef LOGGER_ON_SCREEN
      BsHashInvoke(HA_CARDSTATE_ACTIVE);
#endif
#endif
/*Note : End:To BE Removed:For local testing only */
   
    ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
    if(ret == RFAILED)
    {
      LOG_PRINT(CRITICAL,"bsCfgIntfCb(): SendInterfaceAddUpdateToPeer Failed \n");
    }
    LOG_PRINT(INFO,"bsCfgIntfCb():Interface Added Successfully \n");

/*Note : Start:To BE Removed:For local testing only */
#ifdef BSSAP_HA
#ifdef LOGGER_ON_SCREEN
      FillHashTableTillMaxVal(BSHASH_TABLE_CALLREF_CTXT,bs_intf_id);
#endif
#endif
/*End:To BE Removed:For local testing only */
    return NWSTK_CMD_CNG_SUCCESS;
  }  
}
int bsDelIntfCb(ScmBsInterfaceConfig *cfg)
{
  BsIntfCb *bsIntfCb = SS7_NULL;   
  int i,ret = RFAILED;
  BsCallCb *call = NULL;

  if(cfg == NULL)
  {
    LOG_PRINT(CRITICAL,"bsDelIntfCb():cfg ptr is NULL \n");
    return NWSTK_WRONG_PARAM;
  }
  
  bs_intf_id = cfg->bscId;   
  LOG_PRINT(INFO,"bsDelIntfCb():Request to Delete Interface with intfId[%d] recv from SCM\n",cfg->bscId);
  
  if(bs_intf_id >= (S16bit) bsCb.genCfg.nmbMaxIntf)
  {
    LOG_PRINT(CRITICAL,"bsDelIntfCb():Interface Id greater than nmbMaxIntf value[%d]\n",bsCb.genCfg.nmbMaxIntf);
    return NWSTK_INVAILD_BSCID;
  }
  bsIntfCb = BSFINDINTF(bs_intf_id);
  if (bsIntfCb == SS7_NULL)
  {
    LOG_PRINT(CRITICAL,"bsDelIntfCb():No Interface Configured, hence cannot delete interface with intfId[%d] \n",bs_intf_id);
    return NWSTK_BSSAPCFGDEL_FAIL;
  }
  else
  {
    LOG_PRINT(INFO,"bsDelIntfCb():Found interface with intfId[%d] bsIntfCb[%p]\n",bs_intf_id,bsIntfCb);
        
    for(i = 1; i <= bsIntfCb->nextLr; i++)
    {
      call = bsFindCall(bsIntfCb,i);
      if(call)
      {
    
	LOG_PRINT(CRITICAL,"bsDelIntfCb():Clearing call[%d] for  interface with intfId[%d] bsIntfCb[%p]\n",i,bs_intf_id,bsIntfCb);
	/* Stopping any running timer for this call */
	bsStopConTmr(call,TMR_ALL);
	/*Deallocating Call pointer */
	bsDeallocateConRef(call);
      }
    }

    /*stop Interface timer*/
	
    LOG_PRINT(CRITICAL,"bsDelIntfCb():Stopping Interface timer if running for  interface with intfId[%d] bsIntfCb[%p]\n",bs_intf_id,bsIntfCb);
    bsStopIntfTmr(bsIntfCb,TMR_ALL);
    
    ret = cmHashListDeinit(bsIntfCb->callRefList);
    if(ret == RFAILED)
    {
       LOG_PRINT(CRITICAL,"bsDelIntfCb():cmHashListDeinit Failed for callRefList of intfId[%d] \n",bs_intf_id);
    }
    bsIntfCb->callRefList = NULL;
       LOG_PRINT(INFO,"bsDelIntfCb():cmHashListDeinit Success for callRefList of intfId[%d] \n",bs_intf_id);
    ret = cmHashListDeinit(bsIntfCb->callIdList);
    if(ret == RFAILED)
    {
       LOG_PRINT(CRITICAL,"bsDelIntfCb():cmHashListDeinit Failed for  callIdList of intfId[%d] \n",bs_intf_id);
    }
    bsIntfCb->callIdList = NULL;
       LOG_PRINT(INFO,"bsDelIntfCb():cmHashListDeinit Success for  callIdList of intfId[%d] \n",bs_intf_id);
    //LOG_PRINT(CRITICAL,"bsDelIntfCb:bsIntfCb->databuf[%p]\n",bsIntfCb->databuf);
    if(bsIntfCb->databuf)
    {
       LOG_PRINT(INFO,"bsDelIntfCb():databuf present of intfId[%d] \n",bs_intf_id);
      bssap_free(bsIntfCb->databuf);
      bsIntfCb->databuf = NULL;
    }
    LOG_PRINT(INFO,"bsDelIntfCb():Now free bsIntfCb ptr for  intfId[%d] \n",bs_intf_id);
    bssap_free(bsIntfCb);
    bsIntfCb = NULL;
    bsCb.nmIntf--;
    *(bsCb.intfLst + bs_intf_id) = NULL;
       
    LOG_PRINT(INFO,"bsDelIntfCb():Interface Ptr Success for  intfId[%d] \n",bs_intf_id);
    ret = SendInterfaceDelUpdateToPeer(bs_intf_id);
    if(ret == RFAILED)
    {
      LOG_PRINT(CRITICAL,"bsDelIntfCb(): Failed to Send Interface Delete Update with intfId[%d] \n",bs_intf_id);
    }
    LOG_PRINT(INFO,"bsDelIntfCb():Interface  deleted Success with intfId[%d] \n",bs_intf_id);
    return NWSTK_CMD_CNG_SUCCESS;
  }
} 
#endif
