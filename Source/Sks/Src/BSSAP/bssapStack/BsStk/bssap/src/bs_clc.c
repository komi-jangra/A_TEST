/***************************************************************************
**
**  FILE NAME:
**      bs_clc.c
**
****************************************************************************
**
**  DESCRIPTION:This files defines the source code for Handelling all Lower Layer Api's received from **							SCCP Stack.
**
**  DATE     NAME               REF#      REASON
**  -------  ----------------   -----     -------------------------------------
**  02Jan2014 Amaresh Prasad Grahacharya 
**
**  Copyright 2005, VNL Software Systems
**
***************************************************************************/

#include "bs_stgl.h"
#include "bs_msgst.h"

#ifdef SCCP_MT_SAFE
#include "sccp_mtlib_proc.h"

extern S32bit concurrent_count_sem;
extern S32bit part_concurrent_count_sem;
#endif

/* header include files (.h) */

#include "lbs.h"           /* layer management                             */
#include "bs.h"
#include "bs_err.h"
#include "bsapp.h"
#include "bssapcom.h"
#include "bs_trace.h"

#include "s7_typ.h"
#include "s7_def.h"
#include "s7_api.h"
#include "bs_stgl.h"
#include "bs_prov.h"
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

extern int bsc_ssn_bssap;

extern int rem_pc,bs_log_user_id,bsc_id,source_point_code;
#ifdef BSSAP_HA
extern int TcpClient;
extern int TcpServer;
#endif

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event
**         N-STATE Indication [ SCCP -> BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/
return_t sccp_n_state_ind
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api;
#endif
{
        BsIntfCb  *intfCb = SS7_NULL;
        return_t ret_val;
        error_t p_ecode;
        U8bit * p_elem, num_opt_elem;
        U32bit aDpc,aOpc;
        U8bit  databuff[BSSAP_DATA_LEN];
        S32bit  dataLen = 0;
        U8bit dataAvl = SS7_FALSE;
        BsCallCb *newCall = SS7_NULL;
        U8bit ssnStatus = 0;
        U8bit pcStatus = 0;
	U16bit ssn = 0,status = 0,affected_ssn = 0;           /* affected SSN */
	U16bit pc;            /* affected PC */
	U8bit ss_mult_ind;
#ifdef BSSAP_HA
        int ret = RFAILED;
#endif
        LOG_PRINT(INFO,"sccp_n_state_ind():FROM SCCP:RECV N-STATE INDICATION(SSN Status): \n");

        p_elem = p_api + API_HEADER_LEN;
	ssn = *p_elem;
	p_elem++;

	pc = GET_PC(p_elem);
	p_elem += PC_SIZE;
	affected_ssn = *p_elem;
	p_elem++;
	status = *p_elem;

  	LOG_PRINT(INFO,"sccp_n_state_ind():pc[%d]:ssn[%d]:affected_ssn[%d]status[%d]",pc,ssn,affected_ssn,status);
	/* Get the interface based on Dpc and switch(variant)*/
	intfCb = bsGetIntfPtrFrmDPC(pc,STACK_ITU);
  	if(intfCb == SS7_NULL)
   	{
	   LOG_PRINT(INFO,"sccp_n_state_ind():No Interface configured");
      	   return (SS7_SUCCESS);
   	}

   if((status == SCCP_USER_IN_SERVICE) && (affected_ssn == bsc_ssn_bssap))
  {
    BS_SET_SSN_STATUS_UP(intfCb->PcSsnStatusInd);
    LOG_PRINT(INFO,"sccp_n_state_ind(): SSN STATUS UP \n");
#ifdef BSSAP_HA
    ret = SendInterfaceAddUpdateToPeer(intfCb);
    if(ret == ROK)
    {
      LOG_PRINT(INFO,"BSSAP_HA:sccp_n_state_ind(): Send Interface Update Success for SSN STATUS UP \n");
    }
    else
    {
      LOG_PRINT(CRITICAL,"BSSAP_HA:sccp_n_state_ind(): Fail to Send Peer Interface Update for SSN STATUS UP \n");
    }
#endif
		BsDispatchPcStatusToApp(pc,SCCP_SCMG_SS_ALLOWED,intfCb);
   /* BsDispatchSsnStatusToApp(pc,ssn,MTP3_MSG_RESUME,intfCb);*//* Commented 26-02-16 only SSA for N-STATE*/
  }
  else if((status == SCCP_USER_OUT_OF_SERVICE) && (affected_ssn == bsc_ssn_bssap))
  {
     BS_SET_SSN_STATUS_DOWN(intfCb->PcSsnStatusInd);
     LOG_PRINT(INFO,"sccp_n_state_ind(): SSN STATUS DOWN \n");
#ifdef BSSAP_HA
     ret = SendInterfaceAddUpdateToPeer(intfCb);
     if(ret == ROK)
     {
       LOG_PRINT(INFO,"BSSAP_HA:sccp_n_state_ind(): Send Interface Update Success for SSN STATUS DOWN \n");
     }
     else
     {
       LOG_PRINT(CRITICAL,"BSSAP_HA:sccp_n_state_ind(): Fail to Send Peer Interface Update for SSN STATUS DOWN \n");
     }
#endif
#if 0
       /*Raise Alarm to Stack Manager*/
     bsInitUstaDgn(LBS_USTA_DGNVAL_SSN, (PTR) &aSsn,
                   LBS_USTA_DGNVAL_BSCID, (PTR)&intfCb->bscId,
                   LBS_USTA_DGNVAL_SWTCH, (PTR)&intfCb->swtch,
                   LBS_USTA_DGNVAL_DPC, (PTR)&intfCb->phyDpc);

     bsGenAlarmNew(&bsCb.init.lmPst, LCM_CATEGORY_PROTOCOL,
                    LBS_EVENT_REMOTE_SUBSYSTEM_DOWN, LCM_CAUSE_PROT_NOT_ACTIVE,TRUE);
#endif  
		BsDispatchPcStatusToApp(pc,SCCP_SCMG_SS_PROHIBIT,intfCb);/* Commented 26-02-16 only SSP for N-STATE */
    /* BsDispatchSsnStatusToApp(pc,ssn,MTP3_MSG_PAUSE,intfCb);*/
  /*   printf("BsLiSptSteInd() Failed, Subsystem user out of service \n",0);*/
      return (SS7_SUCCESS);
  }
  else
  {
      LOG_PRINT(INFO,"sccp_n_state_ind(): Failed, status value is neither OOS nor IS \n");
      return (SS7_SUCCESS);
  }	
      LOG_PRINT(INFO,"sccp_n_state_ind():PROCESSED Successfully SSN STATE IND  from SCCP \n");

      return (SS7_SUCCESS);
 }



/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event
**         N-PCSTATE Indication [ SCCP -> BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/
return_t sccp_n_pcstate_ind
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api;
#endif
{
        BsIntfCb  *intfCb = SS7_NULL;
        return_t ret_val;
        error_t p_ecode;
        U8bit * p_elem, num_opt_elem;
        U32bit aDpc, aOpc;
        U8bit  databuff[BSSAP_DATA_LEN];
        S32bit  dataLen = 0;
        U8bit dataAvl = SS7_FALSE;
        BsCallCb *newCall = SS7_NULL;
        U8bit ssnStatus = 0;
        U8bit pcStatus = 0;
	U8bit ssn,sps = 0;           /* affected SSN */
	U16bit pc;            /* affected PC */
	U8bit ss_mult_ind;

        LOG_PRINT(INFO,"sccp_n_pcstate_ind():FROM SCCP:RECV PC-STATE INDICATION(PC Status): \n");

        p_elem = p_api + API_HEADER_LEN;
	ssn = *p_elem;     /* SSN */
	p_elem++;

	pc = GET_PC(p_elem);  /* Affected Signalling Point */
	p_elem += PC_SIZE;
	
	sps = *p_elem; /* Signalling Point Status */

  	LOG_PRINT(INFO,"sccp_n_pcstate_ind():pc[%d]:ssn[%d]:signallingpointstatus[%d]",pc,ssn,sps);
	/* Get the interface based on Dpc and switch(variant)*/
	intfCb = bsGetIntfPtrFrmDPC(pc,STACK_ITU);
  	if(intfCb == SS7_NULL)
   	{
	   LOG_PRINT(INFO,"sccp_n_pcstate_ind():No Interface configured");
      	   return (SS7_SUCCESS);
   	}

	switch(sps)
   	{
       	case SP_ACCESSIBLE:
  	    LOG_PRINT(INFO,"sccp_n_pcstate_ind():SCCP_SCMG_SS_ALLOWED: Pc Status is AVAILABLE :DPC[%d]",intfCb->phyDpc);
            if (ssn == bsc_ssn_bssap)
	    {	
            	BS_SET_PC_STATUS_UP(intfCb->PcSsnStatusInd);
           /* 	BsDispatchPcStatusToApp(pc,SCCP_SCMG_SS_ALLOWED,intfCb); *//* commented SST 26-02-16 */
	    }	
            break;
       case SP_INACCESSIBLE:
  	    LOG_PRINT(INFO,"sccp_n_pcstate_ind():SCCP_SCMG_SS_PROHIBIT:Pc Status is UNAVAILABLE :DPC[%d]",intfCb->phyDpc);
            if (ssn == bsc_ssn_bssap)
	    {	
            	BS_SET_PC_STATUS_DOWN(intfCb->PcSsnStatusInd);
          /* 	BsDispatchPcStatusToApp(pc,SCCP_SCMG_SS_PROHIBIT,intfCb);*//* commented for SST 26-02-16 */

	    }			
            break;
	case SP_CONGESTED:
  	    LOG_PRINT(INFO,"sccp_n_pcstate_ind():SP_CONGESTED: Pc Status is CONGESTED: DPC[%d]",intfCb->phyDpc);
            if (ssn == bsc_ssn_bssap)
	    {	
            	BS_SET_PC_STATUS_CONG(intfCb->PcSsnStatusInd);
            	BsDispatchPcStatusToApp(pc,MTP3_MSG_STATUS,intfCb);
	    }
            break;
       default:
      	    LOG_PRINT(INFO,"sccp_n_pcstate_ind(): Failed, Unknown sps value for Pc status Ind ");
      	    return (SS7_SUCCESS);
   	}
      LOG_PRINT(INFO,"sccp_n_pcstate_ind():PROCESSED Successfully PC STATE IND  from SCCP \n");
     return (SS7_SUCCESS);
}

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event 
**         N-UNITDATA Indication [ SCCP -> BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/

return_t sccp_n_unitdata_ind
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	BsIntfCb  *intfCb = SS7_NULL;
	return_t ret_val,ret = SS7_FAILURE;
	error_t p_ecode;
        sccp_addr_t p_cd_add;
        sccp_addr_t p_cg_add;
        U8bit * p_elem, num_opt_elem,*p_addr;
	U32bit aDpc, aOpc;
	U8bit  databuff[BSSAP_DATA_LEN];
	S32bit  dataLen = 0;
	U8bit dataAvl = SS7_FALSE;
	BsCallCb *newCall = SS7_NULL;
	U8bit ssnStatus = 0;
	U8bit pcStatus = 0;
	
        LOG_PRINT(INFO,"sccp_n_unitdata_ind():FROM SCCP:RECV UNITDATA INDICATION(UDT): \n");
	
         p_elem = p_api + API_HEADER_LEN;

  	*(p_elem+1) = *p_elem;
  	if (SS7_FAILURE == sccp_decode_sccp_addr (p_elem+1, &p_cd_add))
  	{
        LOG_PRINT(CRITICAL,"sccp_n_unitdata_ind():sccp_decode_sccp_addr failed for p_cd_add \n");
    		return (SS7_FAILURE);
  	}
  	p_elem += *p_elem + SCCP_ELEM_LEN_LEN;
  	*(p_elem+1) = *p_elem;
  	if (SS7_FAILURE == sccp_decode_sccp_addr (p_elem+1, &p_cg_add))
  	{
        LOG_PRINT(CRITICAL,"sccp_n_unitdata_ind():sccp_decode_sccp_addr failed for p_cg_add \n");
    		return (SS7_FAILURE);
  	}
  	p_elem += *p_elem + SCCP_ELEM_LEN_LEN;
	/* data */
  	dataLen = GET_2_BYTE_LE (p_elem);
      	memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
  
	if( dataLen<MIN_DATA_LEN)
  	{
        LOG_PRINT(CRITICAL,"sccp_n_unitdata_ind():failed dataLen < MIN_DATA_LEN \n");
    		p_ecode = ESS7_INVALID_API_ELEMENT;
    		return(SS7_FAILURE);
  	}
  if (databuff != SS7_NULL)
  ss7_memcpy (databuff,p_elem + SCCP_ELEM_LEN_LEN,dataLen);
#if 0
  p_info->data.p   = p_elem + SCCP_ELEM_LEN_LEN;
#endif
  p_elem += SCCP_ELEM_LEN_LEN;
  p_elem += dataLen;

  num_opt_elem = GET_API_NELEM(p_api) - SCCP_N_UNITDATA_IND_MIN_NELEM;
  LOG_PRINT(INFO,"sccp_n_unitdata_ind():Number of optional Elements in UDT Receive from SCCP",num_opt_elem); 

#if 0
  while (num_opt_elem--)
  {
    switch (*p_elem++)
    {
      case SCCP_ELEM_SEQUENCE_CONTROL:
        p_elem += SCCP_ELEM_LEN_LEN;
        p_info->proto_class |= 1;
        p_info->sls = *p_elem++;
        BS_CL_TRC (("SCCP::SCLC: sequence control elem %d\n",
                   p_info->sls));
        break;

	case SCCP_ELEM_RETURN_OPTION:
        BS_CL_TRC (("SCCP::SCLC: return option present\n"));
        p_elem += SCCP_ELEM_LEN_LEN;
        if (SCCP_RETURN_MSG == *p_elem)
        {
          CL_TRC (("SCCP::SCLC: return option set\n"));
          p_info->proto_class |= RET_OPTN_MASK;
        }
        else
          CL_TRC (("SCCP::SCLC: return option not set\n"));
        p_elem++;
        break;
      case SCCP_ELEM_IMPORTANCE:
        {
          p_elem += SCCP_ELEM_LEN_LEN;
          p_info->importance = *p_elem++;
          SET_IMPORTANCE_PRESENT(p_info);
          CL_TRC (("SCCP::SCLC: importance %d\n",
                     p_info->importance));
        }
        break;
default:
        break;
    }
  }
#endif /* Stop Parse the UDT Sequence control,Return option & Importance */
	  
	   aDpc = p_cg_add.pc;
	   aOpc = p_cd_add.pc;

/* Get the interface based on Dpc and switch(variant)*/
  intfCb = bsGetIntfPtrFrmDPC(aDpc,STACK_ITU);

   if((intfCb == SS7_NULL))
   {
      LOG_PRINT(INFO,"sccp_n_unitdata_ind():bsGetIntfPtrFrmDPC Failed, No interface present");
      return (SS7_SUCCESS);
   }

   LOG_PRINT(INFO,"sccp_n_unitdata_ind(): intfCb[0x%x] for dpc[%d] \n",intfCb,aDpc);
   /*Setting SSn Status UP on receiving UDT from SCCP*/
   BS_SET_SSN_STATUS_UP(intfCb->PcSsnStatusInd);
   BS_SET_PC_STATUS_UP(intfCb->PcSsnStatusInd);
   LOG_PRINT(INFO,"sccp_n_unitdata_ind():(UDT from Sccp):Setting SSNSTATUS  and PCSTATUS as UP in case UDT from SCCP: PcSsnStatusInd[0x%x]\n",intfCb->PcSsnStatusInd);

#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(intfCb);
   if(ret == ROK)
   {
     LOG_PRINT(INFO,"BSSAP_HA:sccp_n_unitdata_ind(): Send Interface Update Success for SSN STATUS UP \n");
   }
   else
   {
     LOG_PRINT(CRITICAL,"BSSAP_HA:sccp_n_unitdata_ind(): Fail to Send Peer Interface Update for SSN STATUS UP \n");
   }
#endif
  BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
  BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);
  if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  {
    LOG_PRINT(CRITICAL,"sccp_n_unitdata_ind():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
    return (SS7_FAILURE);
  }
   if(dataLen != 0)
  {
    dataAvl = SS7_TRUE;
  }

      LOG_PRINT(INFO,"BS: SCCP_MSG_UDT FRM MSC DUMP START:-\n");
      BSSAP_HEX_DUMP(API_TRACE,DETAILED_TRACE,databuff,dataLen);
      LOG_PRINT(INFO,"BS: SCCP_MSG_UDT FRM MSC DUMP END:-\n");

      ret  = BsProcessUserData(databuff,dataLen,SS7_NULL,intfCb);
      if (ret != SS7_SUCCESS)
      {
        LOG_PRINT(CRITICAL, "sccp_n_unitdata_ind():Fail to processs MSC data(UDT)\n");
        return (SS7_FAILURE);
      }	
      LOG_PRINT(INFO,"sccp_n_unitdata_ind():PROCESSED Successfully UNIT DATA IND(UDT)  from SCCP \n");
        return (SS7_SUCCESS);

}



/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event 
**         N-CONNECT Indication [ SCCP -> BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/


return_t sccp_n_connect_ind
#ifdef ANSI_PROTO
	(U8bit * p_api)
#else
	(p_api)
	U8bit * p_api;
#endif
{
	BsIntfCb  *intfCb = SS7_NULL;
        BsCallCb   call;
	return_t ret_val,ret = SS7_FAILURE; 
	error_t p_ecode;
        sccp_addr_t p_cd_add;
        sccp_addr_t p_cg_add;
        U8bit  *p_api_end, *p_ie;
	U8bit   num_elems, num_elems_p,proto_class,credit;
	U8bit  param_id, param_len;
	U32bit aDpc, aOpc,connectionId;
	U8bit  databuff[BSSAP_DATA_LEN];
	S32bit  dataLen = 0;
	U8bit dataAvl = SS7_FALSE;
	BsCallCb *newCall = SS7_NULL;
	U8bit ssnStatus = 0;
	U8bit pcStatus = 0;
        SpConId ConId;
	
        LOG_PRINT(INFO,"sccp_n_connect_ind():FROM SCCP:RECV CONNECTION INDICATION(CR): \n");

	num_elems_p = 0;
	p_api_end = p_api + GET_API_LEN (p_api);
	num_elems = GET_API_NELEM(p_api);
        p_ie = p_api + API_HEADER_LEN;

 /* Mandatory Fixed parameters */
	/* Parsing ConnectionId */
#ifdef SCCP_CONNECTION_ID_CHANGES
  connectionId = GET_4_BYTE_LE (p_ie);
#else
 connectionId = GET_2_BYTE_LE (p_ie);
#endif
	p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
	num_elems_p++;
  /* Parsing Protocol class */
	proto_class = *p_ie;
	p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
	num_elems_p++;

 /* Mandatory Variable parameters */
	/* Parsing Called Address */
	*(p_ie + 1) = *p_ie;
  	if (SS7_FAILURE == sccp_decode_sccp_addr ((p_ie + 1), &p_cd_add))
  	{
	  return (SS7_FAILURE);
	}
	
	p_ie += *p_ie + SCCP_ELEM_LEN_LEN;
	num_elems_p++;
  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
     LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): Part of the API missing.\n") ;
      return (SS7_FAILURE);
    }
    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_CALLING_ADDR :
        p_ie -= SCCP_ELEM_LEN_LEN ;
        *(p_ie + 1) = *p_ie ;
	 if(SS7_FAILURE== sccp_decode_sccp_addr ((p_ie + 1), &p_cg_add))
    	{
	  LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): sccp_decode_sccp_addr failed for p_cg_add\n") ;
      		return (SS7_FAILURE);
    	}
        if (*p_ie != sccp_addr_len (&p_cg_add))
        {
          /* Incorrectly coded address */
	  LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): failed Called address length incorrect\n") ;
          return (SS7_FAILURE) ;
        }
        p_ie += *p_ie + SCCP_ELEM_LEN_LEN ;
	  LOG_PRINT(INFO,"sccp_n_connect_ind(): Responding Address Present\n") ;
        break ;

    case SCCP_ELEM_CREDIT:
        if (proto_class == PROTOCOL_CLASS_2)
        {
          /* credit element present in case of protocol class 3 only */
	  LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): failed, Unsupported parameter(%d) for CLASS 2 \n") ;
          return (SS7_FAILURE);
        }
        credit = *p_ie;
        p_ie += param_len;
	  LOG_PRINT(INFO,"sccp_n_connect_ind(): Credit present(%d)\n",credit) ;
        break;
        case SCCP_ELEM_USER_DATA:
        dataLen = param_len;
        memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
  	if(dataLen > MAX_OPTIONAL_DATA_LEN)
  	{
	  LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): failed, User Data length (len %d). Exceeds 128 bytes \n",dataLen) ;
    		return SS7_FAILURE;
  	}
        if( dataLen<MIN_DATA_LEN)
        {
                p_ecode = ESS7_INVALID_API_ELEMENT;
                return(SS7_FAILURE);
        }
	if (databuff != SS7_NULL)
  	  ss7_memcpy (databuff,p_ie,dataLen);
        p_ie += param_len;
	  LOG_PRINT(INFO,"sccp_n_connect_ind(): User Data Present\n") ;
        break;
	default:
        LOG_PRINT(CRITICAL,"sccp_n_connect_ind(): Unsupported parameter(%d).\n",param_id);
        return (SS7_FAILURE);
    }
  }
    if (num_elems_p == num_elems)
   {
     LOG_PRINT(INFO,"sccp_n_connect_ind():Parsing sccp_n_connect_ind is SUCCESSFULLY no of elems(%d)\n",num_elems_p);
     /*return (SS7_SUCCESS); */
      ret = SS7_SUCCESS;
   }
   else
   {
     LOG_PRINT(INFO,"sccp_n_connect_ind():Incorrect number of elems in Parsing sccp_n_connect_ind (%d).\n",num_elems_p) ;
     return (SS7_FAILURE) ;
   }
	if (p_cg_add.pc == rem_pc)
	{
		aDpc = p_cg_add.pc;	
    LOG_PRINT(INFO,"sccp_n_connect_ind(): p_cg_add.pc present (%d).\n",p_cg_add.pc) ;
	}
	else
	{
			aDpc = rem_pc;
    LOG_PRINT(INFO,"sccp_n_connect_ind():  Extract from Global dpc (%d).\n",aDpc) ;
	}
	/*   aDpc = p_cg_add.pc;*/
           aOpc = p_cd_add.pc;

/* Get the interface based on Dpc and switch(variant)*/
  intfCb = bsGetIntfPtrFrmDPC(aDpc,STACK_ITU);
  memset((U8bit*)&ConId,'\0',sizeof(SpConId));
  ConId.suId = 0;
  ConId.spId = 0;
  ConId.suInstId = 0;
  ConId.spInstId = connectionId;


   if((intfCb == SS7_NULL))
   {
    LOG_PRINT(CRITICAL,"sccp_n_connect_ind():  Failed, No interface present\n");
      ret = BsSendDisReq(&ConId,SCCP_MSG_CREF,intfCb); /* Enhanced */
      if(ret != SS7_SUCCESS)
      {
          LOG_PRINT(CRITICAL,"sccp_n_connect_ind():Unable to send Disconnect Request to SCCP");
      }
      return (SS7_SUCCESS);
   }
   /*Setting SSn Status UP on receiving CR from SCCP*/
   BS_SET_SSN_STATUS_UP(intfCb->PcSsnStatusInd);
   BS_SET_PC_STATUS_UP(intfCb->PcSsnStatusInd);
#ifdef BSSAP_HA
   ret = SendInterfaceAddUpdateToPeer(intfCb);
   if(ret == ROK)
   {
     LOG_PRINT(INFO,"BSSAP_HA:sccp_n_connect_ind(): RECV CR From SCCP:Send Interface Update Success for SSN & PC STATUS UP \n");
   }
   else
   {
     LOG_PRINT(CRITICAL,"BSSAP_HA:sccp_n_connect_ind():RECV CR From SCCP:Fail to Send Peer Interface Update for SSN & PC STATUS UP \n");
   }
#endif
   LOG_PRINT(INFO,"sccp_n_connect_ind():(CR from SCCP): Setting SSNSTATUS  and PCSTATUS as UP in case UDT from SCCP: PcSsnStatusInd[0x%x]\n",intfCb->PcSsnStatusInd);
   /*printf("BsLiSptConInd: Setting SSN STATUS UP on Receipt of CR \n");*/

   memset((U8bit *)&call, '\0',  sizeof(BsCallCb));

   call.suInstId = 0;
   call.spInstId = connectionId;
  LOG_PRINT(INFO,"sccp_n_connect_ind(): CR RECV: connectionId[%d] \n",connectionId);

  BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
  BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);
  LOG_PRINT(INFO,"sccp_n_connect_ind():ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
  if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  {
    LOG_PRINT(CRITICAL,"sccp_n_connect_ind():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
    return (SS7_FAILURE);
  }
  if(dataLen != 0)
  {
    dataAvl = SS7_TRUE;
  }
   if (dataAvl)
  {
   	ret  = BsProcessUserData(databuff,dataLen,&call,intfCb);
  }
  else
  {
	LOG_PRINT(INFO,"sccp_n_connect_ind():CR received from remote have no user data \n");
        newCall = bsCreate_InsertConRef(intfCb);
        if(newCall == SS7_NULL)
        {
          LOG_PRINT(CRITICAL,"sccp_n_connect_ind():Unable to allocate callref for New connection \n");
          ret = SS7_FAILURE;
        }
        BS_SET_DT1HOREQ_TRUE(newCall->handoverFlagSet);
        newCall->spInstId = connectionId;
        call.suInstId = newCall->suInstId;
        ret = SS7_SUCCESS;
	
  }	
   if (ret != SS7_SUCCESS)
      {
        LOG_PRINT(CRITICAL,"sccp_n_connect_ind():Fail to processs MSC data(CR) So Send Disconnect Req to SCCP \n");
        ret = BsSendDisReq(&ConId,SCCP_MSG_CREF,intfCb);
        if(ret != SS7_SUCCESS)
        {
          LOG_PRINT (CRITICAL,"sccp_n_connect_ind():Unable to send Disconnect Request to SCCP");
        }
        return (SS7_SUCCESS);
      }
      else
      {
      	/*Sending CC to PEER by sending sccp_n_connect_response primitive to SCCP layer*/
         LOG_PRINT(INFO,"sccp_n_connect_ind():Sending sccp_n_connect_response primitive to SCCP \n");
	 ConId.suInstId = call.suInstId;
      	ret = BsSendConResp(&ConId,intfCb);
      	if (ret != SS7_SUCCESS)
      	{
           LOG_PRINT(CRITICAL,"sccp_n_connect_ind():Unable to send Connection Resp Primitive to SCCP \n");
           return (SS7_SUCCESS);
      	}
      }
   /* release message buffer */
      LOG_PRINT(INFO,"sccp_n_connect_ind():PROCESSED Successfully CONNECT IND(CR)  from SCCP \n");
    	return (SS7_SUCCESS);
   }

/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event
**         SCCP-N-CONNECT Confirm [  SCCP->BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/
return_t sccp_n_connect_cnf
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api;
#endif
{
        BsIntfCb  *intfCb = SS7_NULL;
        U32bit  callRef;
        BsCallCb   *call = SS7_NULL;
        return_t ret_val,ret = SS7_FAILURE;
        error_t p_ecode;
        sccp_addr_t p_cd_add;
        sccp_addr_t p_cg_add;
        U8bit  *p_api_end, *p_ie;
        U8bit   num_elems, num_elems_p,proto_class;
        U8bit  param_id, param_len;
        U32bit aDpc, aOpc,connectionId,credit,importance;
        U8bit  databuff[BSSAP_DATA_LEN];
        S32bit  dataLen = 0;
	U8bit dataAvl = SS7_FALSE;
        BsCallCb *newCall = SS7_NULL;
        U8bit ssnStatus = 0;
        U8bit pcStatus = 0;
        U32bit corrId;
        LOG_PRINT(INFO,"sccp_n_connect_cnf():FROM SCCP:RECV CONNECTION CONFIRM(CC): \n");

        num_elems_p = 0;
        p_api_end = p_api + GET_API_LEN (p_api);
        num_elems = GET_API_NELEM(p_api);
        p_ie = p_api + API_HEADER_LEN;
#ifdef BSSAP_HA
	int result = RFAILED;
#endif

 /* Mandatory Fixed parameters */
	/*Parsing Corr-Id */
#ifdef SCCP_CONNECTION_ID_CHANGES
	corrId =  GET_4_BYTE_LE (p_ie); /* Change 2byte to  4byte as on dated 20-01-16 */
#else
	corrId =  *p_ie;
#endif
	p_ie += SCCP_ELEM_CORR_ID_LEN;
  	num_elems_p++;
        /* Parsing ConnectionId */
#ifdef SCCP_CONNECTION_ID_CHANGES
  connectionId = GET_4_BYTE_LE (p_ie);
#else
 connectionId = GET_2_BYTE_LE (p_ie);
#endif
      LOG_PRINT(INFO,"sccp_n_connect_cnf(): having corrId %d",corrId);
      LOG_PRINT(INFO,"sccp_n_connect_cnf(): having connectionId %d",connectionId);
	p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
	num_elems_p++;
	/* Parsing Protcol class */
	proto_class = *p_ie;
  	p_ie += SCCP_ELEM_PROTOCOL_CLASS_LEN;
  	num_elems_p++;

/* No Mandatory variable part */
  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;
    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():Part of the API missing.\n") ;
      return (SS7_FAILURE);
    }
    num_elems_p++ ;
    switch (param_id)
    {
      case SCCP_ELEM_RESPONDING_ADDR :
        p_ie -= SCCP_ELEM_LEN_LEN ;
        *(p_ie + 1) = *p_ie ;
    if(SS7_FAILURE== sccp_decode_sccp_addr ((p_ie + 1), &p_cg_add))
    {
      LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():sccp_decode_sccp_addr failed for p_cg_add\n") ;
      return (SS7_FAILURE);
    }
    if (*p_ie != sccp_addr_len (&p_cg_add))
        {
          /* Incorrectly coded address */
          LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():Called address length incorrect.\n") ;
          return (SS7_FAILURE) ;
        }
        p_ie += *p_ie + SCCP_ELEM_LEN_LEN ;
        LOG_PRINT(INFO,"sccp_n_connect_cnf():Responding Address Present\n");
        break ;
     case SCCP_ELEM_CREDIT :
    	if (proto_class == PROTOCOL_CLASS_2)
    	{
          	LOG_PRINT(CRITICAL,"sccp_n_connect_cnf(): Credit not supported for Class 2.\n") ;
      		return (SS7_FAILURE);
    	}
        credit = *p_ie ;
        p_ie += param_len ;
        LOG_PRINT(INFO,"sccp_n_connect_cnf():Credit present(%d)\n",credit);
        break ;
    case SCCP_ELEM_USER_DATA :
	dataLen = param_len;
        memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
        if(dataLen > MAX_OPTIONAL_DATA_LEN)
        {
                LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():User Data length (len %d). Exceeds 128 bytes\n",dataLen);
                return SS7_FAILURE;
        }
        if( dataLen<MIN_DATA_LEN)
        {
                p_ecode = ESS7_INVALID_API_ELEMENT;
                LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():dataLen<MIN_DATA_LEN\n",dataLen);
                return(SS7_FAILURE);
        }
        if (databuff != SS7_NULL)
         	 ss7_memcpy (databuff,p_ie,dataLen);
        	p_ie += param_len;
	break ;
        case SCCP_ELEM_IMPORTANCE :
          importance = *p_ie ;
          p_ie += param_len ;
          LOG_PRINT(INFO,"sccp_n_connect_cnf():Importance present(%d)\n",importance) ;
          break ;
	
	default:
        LOG_PRINT(INFO,"sccp_n_connect_cnf():Unsupported parameter(%d).\n",param_id) ;
        return (SS7_FAILURE) ;
    }
  }
  if (num_elems_p == num_elems)
  { 
    LOG_PRINT(INFO,"sccp_n_connect_cnf():Parsing sccp_n_connect_cnf is SUCCESSFULLY DONE having no of elems(%d).\n",num_elems_p);
    /*return (SS7_SUCCESS); */
     ret = SS7_SUCCESS;
  }
  else
  {
    LOG_PRINT(INFO,"sccp_n_connect_cnf():Incorrect number of elems(%d).\n",num_elems_p);
    return (SS7_FAILURE) ;
  }
	if (p_cg_add.pc == rem_pc)
	{
		aDpc = p_cg_add.pc;	
    LOG_PRINT(INFO,"sccp_n_connect_cnf(): p_cg_add.pc present (%d).\n",p_cg_add.pc);
	}
	else
	{
			aDpc = rem_pc;
    LOG_PRINT(INFO,"sccp_n_connect_cnf(): Extract from Global dpc (%d)\n",aDpc);
	}

/* Get the interface based on Dpc and switch(variant)*/
  intfCb = bsGetIntfPtrFrmDPC(aDpc,STACK_ITU);
   if((intfCb == SS7_NULL))
   {
      LOG_PRINT(CRITICAL,"sccp_n_connect_cnf(): Failed, No interface present");
      return (SS7_SUCCESS);
   }
   callRef = corrId;
   /* find connection */
   call = bsFindCall(intfCb,callRef);
   if (call == SS7_NULL)
   {
      LOG_PRINT(INFO,"sccp_n_connect_cnf():Cannot find the Call pointer in Call list(For DT1)");
      return (SS7_SUCCESS);
   }
   if (corrId == connectionId)
	 {
      LOG_PRINT(INFO,"sccp_n_connect_cnf():  corrid= connectionid");
	 }
	 else
   { 
      LOG_PRINT(INFO,"sccp_n_connect_cnf():modified connId %d",connectionId);
	 }
   call->spInstId = connectionId;
  /* call->suInstId = connectionId;*//* Added for MAX issue 27-04-16 */
      LOG_PRINT(INFO,"sccp_n_connect_cnf():modified spInstId[%d] suInstId[%d]",call->spInstId,call->suInstId);
   /* No cause for CC message  */
    BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
    BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);
  LOG_PRINT(INFO,"sccp_n_connect_cnf():ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
  if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  {
    LOG_PRINT(INFO,"sccp_n_connect_cnf():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
    return (SS7_FAILURE);
  }
  if(dataLen != 0)
  {
    dataAvl = SS7_TRUE;
  }
  BsDispatchSccpIndToApp(call,BSSAP_CON_ESTD,0,intfCb);
  if(dataAvl)
    {
      ret  = BsProcessUserData(databuff,dataLen,call,intfCb);
      if (ret != SS7_SUCCESS)
        {
          LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():Fail to processs Connection Confirm\n");
    	  return (SS7_FAILURE);
        }
     }
#ifdef BSSAP_HA
  /*Updating CALL DB to PEER */
  if((TcpClient > 0) && (TcpServer > 0))
  {
    result = HashListTbUpdate(intfCb->callRefList,
                         intfCb->intfId,
			 BSHASH_TABLE_CALLREF_CTXT,
			 &call->suInstId,
			 sizeof(U32bit),
			 call);
    if(result == RFAILED)
    {
      LOG_PRINT(CRITICAL,"sccp_n_connect_cnf():Recv Connection Confirm: HashListTbUpdate Fail for Callref[%d]  \n",call->suInstId);
    }
  }
#endif
      LOG_PRINT(INFO,"sccp_n_connect_cnf():PROCESSED Successfully CONNECT CONFIRM(CC) from SCCP \n");
        return (SS7_SUCCESS);
} /* end of sccp_n_connect_cnf */


/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event
**         SCCP-N-DATA Indication [  SCCP->BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**
**      NOTE :
**
***************************************************************************/
return_t sccp_n_data_ind
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api;
#endif
{
        BsIntfCb  *intfCb = SS7_NULL;
        return_t ret_val;
        error_t p_ecode;
        U8bit  *p_api_end, *p_ie;
        U8bit   num_elems, num_elems_p,proto_class;
        U8bit  param_id, param_len;
        U32bit connectionId,importance;
        U8bit  databuff[BSSAP_DATA_LEN];
        S32bit  dataLen = 0;
        U8bit dataAvl = SS7_FALSE;
	BsCallCb   *call = SS7_NULL;
	U32bit  callRef;
	S16bit ret = SS7_SUCCESS;
        U8bit ssnStatus = 0;
        U8bit pcStatus = 0;
#ifdef BSSAP_HA
	int result = RFAILED;
#endif
        LOG_PRINT(INFO,"sccp_n_data_ind():FROM SCCP:RECV DATA INDICATION (DT1): \n");

        num_elems_p = 0;
        p_api_end = p_api + GET_API_LEN (p_api);
        num_elems = GET_API_NELEM(p_api);
        p_ie = p_api + API_HEADER_LEN;

	/* Parsing the parameters started */

	/* Mandatory Fixed parameters */
	/* Parsing ConnectionId */
#ifdef SCCP_CONNECTION_ID_CHANGES
	  connectionId =  GET_4_BYTE_LE (p_ie);
#else
	  connectionId =  GET_2_BYTE_LE (p_ie);
#endif
   	  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
	  num_elems_p++;

	 /* No Mandatory variable part */
	  dataLen = GET_2_BYTE_LE (p_ie);
	  p_ie += SCCP_ELEM_LEN_LEN;
	  if ((p_ie + dataLen) > p_api_end)
  	  {
	    LOG_PRINT(CRITICAL,"sccp_n_data_ind():Part of the API missing.\n") ;
	    return (SS7_FAILURE);
  	  }
  	  if(dataLen < MIN_DATA_LEN)
	  return (SS7_FAILURE);
	  memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
	  if (databuff != SS7_NULL)
          ss7_memcpy (databuff,p_ie,dataLen);
          p_ie += dataLen;
	  num_elems_p++;
	/* Optional Parts */
	while (SS7_TRUE)
  	{
	    if (p_ie == p_api_end)
      	    break;
    	    param_id = *p_ie;
    	    p_ie += SCCP_ELEM_ID_LEN;
    	    param_len = GET_2_BYTE_LE(p_ie);
	    p_ie += SCCP_ELEM_LEN_LEN;
    	    if ((p_ie + param_len) > p_api_end)
    	    {
	      LOG_PRINT(CRITICAL,"sccp_n_data_ind():Part of the API missing.\n") ;
	      return (SS7_FAILURE);
    	    }
	    num_elems_p++;
	    switch (param_id)
    	    {
	      case SCCP_ELEM_IMPORTANCE:
                importance = *p_ie;
          	p_ie += param_len;
          	LOG_PRINT(INFO,"sccp_n_data_ind():Importance present(%d)",importance);
          	break;

      		default:
        	LOG_PRINT(CRITICAL,"sccp_n_data_ind():Unsupported parameter(%d).\n",param_id);
        	return (SS7_FAILURE);
    	     }
  	  }
 if (num_elems_p == num_elems)
   {
     LOG_PRINT(INFO,"sccp_n_data_ind(): Parsing is SUCCESS having no of elems(%d) .\n",num_elems_p);
     /*return (SS7_SUCCESS); */
      ret = SS7_SUCCESS;
   }
   else
   {
     LOG_PRINT(CRITICAL,"sccp_n_data_ind(): Incorrect number of elems(%d).\n",num_elems_p);
     return (SS7_FAILURE) ;
   }
	/* Parsing the parameters completed */
	intfCb = bsGetIntfPtr(bsc_id,STACK_ITU);
	if(intfCb != SS7_NULL)
  	{
	    LOG_PRINT(INFO,"sccp_n_data_ind():Found Interface for bscId[%d] intfId[%d]\n",bsc_id,intfCb->intfId);
  	}
         if((intfCb == SS7_NULL))
  	{
    	  LOG_PRINT(INFO,"sccp_n_data_ind():No interface is present\n");
    	  return (SS7_SUCCESS);
  	}
	/* find connection by bsFindCallUsingspInstId New API added  */

	  call = bsFindCallUsingspInstId(intfCb,connectionId);
	  if (call == SS7_NULL)
  	  {
	      LOG_PRINT(INFO,"sccp_n_data_ind():Cannot find the Call pointer in Call list(For DT1)");
    	      return (SS7_SUCCESS);
    	  }
		 /* find connection */
#if 0
	   call = bsFindCall(intfCb,connectionId);
  	 if (call == SS7_NULL)
   		{
      	LOG_PRINT(INFO,"sccp_n_data_ind:Cannot find the Call pointer in Call list(For DT1)");
      	return (SS7_SUCCESS);
   		}

#endif /* Commented  27-04-16 */
	    BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
	    BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);
	    LOG_PRINT(INFO,"sccp_n_data_ind():ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
	    if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  	    {
	       LOG_PRINT(CRITICAL,"sccp_n_data_ind():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
		    return (SS7_FAILURE);
  	    }
	   if(dataLen != 0)
  	   {
	      dataAvl = SS7_TRUE;
  	   }
	   if(dataAvl)
 	   {
        	ret  = BsProcessUserData(databuff,dataLen,call,intfCb);
        	if (ret != SS7_SUCCESS)
        	{
	          LOG_PRINT(CRITICAL,"sccp_n_data_ind():BsProcessUserData Fail to processs MSC data(DT1)");
		  return (SS7_FAILURE);
        	}
      	   }
#ifdef BSSAP_HA
	   if((TcpClient > 0) && (TcpServer > 0))
	   {
	     /*Updating CALL DB to PEER */
	     result = HashListTbUpdate(intfCb->callRefList,
                         intfCb->intfId,
			 BSHASH_TABLE_CALLREF_CTXT,
			 &call->suInstId,
			 sizeof(U32bit),
			 call);
	     if(result == RFAILED)
	     {
	       LOG_PRINT(CRITICAL,"BSSAP_HA:sccp_n_data_ind():Recv DT1: HashListTbUpdate Failed for Callref[%d]  \n",call->suInstId);
	     }
	   }
#endif
      LOG_PRINT(INFO,"sccp_n_data_ind():PROCESSED Successfully DATA IND(DT1)  from SCCP \n");
      return (SS7_SUCCESS);
} /* end of sccp_n_data_ind */


/***************************************************************************
**
**      FUNCTION :
**         corresponds to Q.714/C.12/sheet-6 on the event
**         SCCP-N-DISCONNECT Indication [  SCCP->BSSAP ]
****************************************************************************
**
**      DESCRIPTION :
**         assigns SLS and calls routing function
**
**      NOTE :
**
***************************************************************************/
return_t sccp_n_disconnect_ind
#ifdef ANSI_PROTO
        (U8bit * p_api)
#else
        (p_api)
        U8bit * p_api;
#endif
{
	BsIntfCb  *intfCb = SS7_NULL;
        return_t ret_val;
        error_t p_ecode;
        U8bit  *p_api_end, *p_ie;
        U8bit   num_elems, num_elems_p,proto_class;
        U8bit  param_id, param_len,rel_cause,originator;
        sccp_addr_t p_cd_add;
        sccp_addr_t p_cg_add;
        U32bit connectionId,importance,corrId;
        U8bit  databuff[BSSAP_DATA_LEN];
        S32bit  dataLen = 0;
        U8bit dataAvl = SS7_FALSE;
        BsCallCb   *call = SS7_NULL;
        U32bit  callRef;
        S16bit ret = SS7_SUCCESS;
        U8bit ssnStatus = 0;
        U8bit pcStatus = 0;
	U16bit log_userId;

        LOG_PRINT(INFO,"sccp_n_disconnect_ind():FROM SCCP:RECV DISCONNECT INDICATION : \n");
		corrId = 0;
  	num_elems_p = 0;
  	p_api_end = p_api + GET_API_LEN (p_api);
  	num_elems = GET_API_NELEM(p_api);
  	p_ie = p_api + API_HEADER_LEN;

	/* Fixed parameters */
#ifdef SCCP_CONNECTION_ID_CHANGES
	  connectionId =  GET_4_BYTE_LE (p_ie);
#else
 	  connectionId =  GET_2_BYTE_LE (p_ie);
#endif
	  p_ie += SCCP_ELEM_CONNECTION_ID_LEN;
	  num_elems_p++;

	  rel_cause = *p_ie;
	  p_ie += SCCP_ELEM_REFUSAL_CAUSE_LEN;
	  num_elems_p++;
 
	  originator = 	*p_ie;
	  p_ie += SCCP_ELEM_DISC_ORG_LEN;
	  num_elems_p++;

 /* No Mandatory variable part */

 /* Optional part */
  while (SS7_TRUE)
  {
    if (p_ie == p_api_end)
      break;

    param_id = *p_ie;
    p_ie += SCCP_ELEM_ID_LEN;

    param_len = GET_2_BYTE_LE(p_ie);
    p_ie += SCCP_ELEM_LEN_LEN;

    if ((p_ie + param_len) > p_api_end)
    {
      LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind():Part of the API missing.\n") ;
      return (SS7_FAILURE);
    }
    num_elems_p++;
    switch (param_id)
    {
      case SCCP_ELEM_RESPONDING_ADDR:
      LOG_PRINT(INFO,"sccp_n_disconnect_ind(): SCCP_ELEM_RESPONDING_ADDR present.\n") ;
        p_ie -= SCCP_ELEM_LEN_LEN;
        *(p_ie + 1) = *p_ie;
        if (SS7_FAILURE ==sccp_decode_sccp_addr ((p_ie + 1), &p_cg_add))
        {
      LOG_PRINT(INFO,"sccp_n_disconnect_ind(): sccp_decode_sccp_addr failed for p_cg_add\n") ;
      		return (SS7_FAILURE);
    	}	
        if (*p_ie != sccp_addr_len (&p_cg_add))
        {
          /* Incorrectly coded address */
          LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind():Called address length no correct.\n");
          return (SS7_FAILURE);
        }
        p_ie += *p_ie + SCCP_ELEM_LEN_LEN;
        break;

      case SCCP_ELEM_USER_DATA:
        memset((U8bit *)databuff, 0,  BSSAP_DATA_LEN);
        dataLen = param_len;
  	if(dataLen > MAX_OPTIONAL_DATA_LEN)
  	{
  	/* change of maximum data length from 130 to 128 */
            LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind():User Data length (len %d). Exceeds 128 bytes\n",dataLen);
    	    return SS7_FAILURE;
  	}
	if (databuff != SS7_NULL)
        ss7_memcpy (databuff,p_ie,dataLen);
        p_ie += param_len;
	LOG_PRINT(INFO,"sccp_n_disconnect_ind():user Data present(len %d)",dataLen);
        break;
	case SCCP_ELEM_LOG_USER_ID:
        log_userId = GET_2_BYTE_LE(p_ie);
        p_ie += param_len;
        LOG_PRINT(INFO,"sccp_n_disconnect_ind():logical user id present(%d)",log_userId);
        break;

      case SCCP_ELEM_CORR_ID:
#ifdef SCCP_CONNECTION_ID_CHANGES
        corrId = GET_4_BYTE_LE(p_ie);
#else
        corrId = *p_ie;
#endif
        p_ie += param_len;
        LOG_PRINT(INFO,"sccp_n_disconnect_ind():Correlation id present CREF case:Correlation id  %d",corrId);
        break;

      case SCCP_ELEM_IMPORTANCE:
          importance = *p_ie;
          p_ie += param_len;
          LOG_PRINT(INFO,"sccp_n_disconnect_ind():Importance present(%d)",importance);
          break;

      default:
        LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind():Unsupported parameter(%d).\n",param_id);
        return (SS7_FAILURE);
    }
  }

   if (num_elems_p == num_elems)
   {
     LOG_PRINT(INFO,"sccp_n_disconnect_ind(): Parsing sccp_n_disconnect_ind is SUCCESSFULLY no of elems(%d)\n",num_elems_p);
     /*return (SS7_SUCCESS); */
      ret = SS7_SUCCESS;
   }
   else
   {
     LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind(): Incorrect number of elems in Parsing sccp_n_disconnect_ind (%d).\n",num_elems_p) ;
     return (SS7_FAILURE) ;
   }

       intfCb = bsGetIntfPtr(bsc_id,STACK_ITU);
        if(intfCb != SS7_NULL)
        {
            LOG_PRINT(INFO,"sccp_n_disconnect_ind():bsGetIntfPtrFrmCallRef :Found Interface for bscId[%d] intfId[%d]\n",bsc_id,intfCb->intfId);
        }
         if((intfCb == SS7_NULL))
        {
          LOG_PRINT(CRITICAL,"sccp_n_disconnect_ind():No interface is present\n");
          return (SS7_SUCCESS);
        }
				if (corrId == 0)
				{
						/* find connection by bsFindCallUsingspInstId New API added  */
          	call = bsFindCallUsingspInstId(intfCb,connectionId);
          	if (call == SS7_NULL)
          	{
            	LOG_PRINT(INFO,"sccp_n_disconnect_ind():Cannot find the Call pointer in Call list(For DT1)");
              return (SS7_SUCCESS);
          	}
				}
				else
				{
					callRef = corrId;
   				/* find connection */
   				call = bsFindCall(intfCb,callRef);
   				if (call == SS7_NULL)
   				{
      				LOG_PRINT(INFO,"sccp_n_disconnect_ind():CREF cannot find the Call pointer");
      				return (SS7_SUCCESS);
   				}
   				if (corrId == connectionId)
   				{
      				LOG_PRINT(INFO,"sccp_n_disconnect_ind():CREF corrid= connectionid");
   				}
   				else
   				{
      				LOG_PRINT(INFO,"sccp_n_disconnect_ind():CREF modified connId %d",connectionId);
   				}
   				call->spInstId = connectionId;
      		LOG_PRINT(INFO,"sccp_n_disconnect_ind():CREF spInstId[%d] suInstId[%d]",call->spInstId,call->suInstId);
				}
#if 0 
		 /* find connection */
		     call = bsFindCall(intfCb,connectionId);
				 if (call == SS7_NULL)
          {
            LOG_PRINT(INFO,"sccp_n_disconnect_ind:Cannot find the Call pointer in Call list(For DT1)");
             return (SS7_SUCCESS);
          }
	
#endif

	  BS_GET_SSN_STATUS(intfCb->PcSsnStatusInd,ssnStatus);
	  BS_GET_PC_STATUS(intfCb->PcSsnStatusInd,pcStatus);
	  LOG_PRINT(INFO,"sccp_n_disconnect_ind():ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
	if((ssnStatus != SSN_UP) || (pcStatus != PC_UP))
  	{
    		LOG_PRINT(INFO,"sccp_n_disconnect_ind():Either PC or SSN status down:ssnStatus[%d] : pcStatus[%d] \n",ssnStatus,pcStatus);
    		return (SS7_FAILURE);
  	}
	  if(dataLen != 0)
  	{
    	   dataAvl = SS7_TRUE;
  	}
/*	if(p_cg_add.pc == rem_pc || p_cg_add.pc == source_point_code)*//* Orig Code  */
		if (corrId != 0)
   	{
         LOG_PRINT(INFO,"sccp_n_disconnect_ind():Sending BSSAP_CON_REF to BSC-APP");
	       BsDispatchSccpIndToApp(call,BSSAP_CON_REF,rel_cause,intfCb);
	      /*Deallocate call reference */
      		ret = bsDeallocateConRef(call);
      		if(ret == SS7_SUCCESS)
      		{
        	  call = SS7_NULL;
        	  LOG_PRINT(INFO,"sccp_n_disconnect_ind(): Call deallocated successfully on RLSD \n");
      		} 
   	}
   	else
   	{
      	if(call->timerId  != BSSAP_INVALID_TMRID)
        {
            switch(call->timerId)
            {
              case BSSAP_T_7:
                   LOG_PRINT(INFO,"sccp_n_disconnect_ind():Stopping Timer BSSAP_T_7 in case of RLSD");
                   bsStopConTmr(call, BSSAP_T_7);
                   break;
              case BSSAP_T_8:
                   LOG_PRINT(INFO,"sccp_n_disconnect_ind():Stopping Timer BSSAP_T_8 in case of RLSD");
                   bsStopConTmr(call,BSSAP_T_8);
                   break;
              case BSSAP_T_10:
                   LOG_PRINT(INFO,"sccp_n_disconnect_ind():Stopping Timer BSSAP_T_10 in case of RLSD");
                   bsStopConTmr(call,BSSAP_T_10);
                   break;
              case BSSAP_T_11:
                   LOG_PRINT(INFO,"sccp_n_disconnect_ind():Stopping Timer BSSAP_T_11 in case of RLSD");
                   bsStopConTmr(call,BSSAP_T_11);
                   break;
              default:
                   LOG_PRINT(INFO,"sccp_n_disconnect_ind():Unknown timer exist in case of RLSD");
                   break;
            }
        }
        LOG_PRINT(INFO,"sccp_n_disconnect_ind():Sending BSSAP_CON_REL to BSC-APP");
				BsDispatchSccpIndToApp(call,BSSAP_CON_REL,rel_cause,intfCb);
      /*Free CIC for this call */
      if(call->cic > 0)
      {
        if((intfCb->cicDataList != SS7_NULL) && (intfCb->cicDataList[call->cic].cic == call->cic))
        {
          BS_SET_CALLSTATE_IDLE(intfCb->cicDataList[call->cic].flaglistSet);
        }
        call->cic = 0;
      }
      /*Deallocate call reference */
      ret = bsDeallocateConRef(call);
      if(ret == SS7_SUCCESS)
      {
        call = SS7_NULL;
        LOG_PRINT(INFO,"sccp_n_disconnect_ind():():bsDeallocateConRef(RLSD): call released successfully \n");
      }
   }
   if (ret != SS7_SUCCESS)
   {
      LOG_PRINT(INFO,"sccp_n_disconnect_ind():Unable to process incoming message");
      return (SS7_SUCCESS);
   }
      LOG_PRINT(INFO,"sccp_n_disconnect_ind():PROCESSED Successfully DISCONNECT IND(RLSD)  from SCCP \n");
    return (SS7_SUCCESS);
 /* release message buffer */
}		

