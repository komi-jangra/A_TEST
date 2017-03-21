/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: bssap.cpp,v 1.4 2008-02-07 10:11:56 amaresh.prasad Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.3  2008/02/01 04:22:26  amaresh.prasad
 * LOG: Updated for Alarm & PC status
 * LOG:
 * LOG: Revision 1.2  2007/10/30 06:43:01  amaresh.prasad
 * LOG: Updated for NWMSG for MTP3 & SCCP
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:14  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:41  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.13  2005/12/13 09:47:37  mkrishna
 * LOG: Changed pauseFlag to true
 * LOG:
 * LOG: Revision 1.1.2.12  2005/12/05 09:12:20  mkrishna
 * LOG: Pegs implementation done
 * LOG:
 * LOG: Revision 1.1.2.11  2005/11/24 04:43:40  adutta
 * LOG: Incorporated IMR review changes *.cpp
 * LOG:
 * LOG: Revision 1.1.2.10  2005/10/06 08:29:33  adutta
 * LOG: DBC added
 * LOG:
 * LOG: Revision 1.1.2.9  2005/09/27 09:32:54  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.8  2005/09/06 10:55:12  adutta
 * LOG: Added MAP timers
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/28 18:56:52  adutta
 * LOG: Handover implementation
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/26 06:32:47  adutta
 * LOG: Initialization of FSM
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/21 15:42:17  adutta
 * LOG: Reading timer vlaues from config.
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 06:39:20  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/17 05:30:24  adutta
 * LOG: Variable re-alignment
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/16 10:12:29  adutta
 * LOG: Traces added
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:00:43  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/

#include <bssap.h>
#include <bssap_calldb.h>
#include <bssap_common.h>
#include <bssap_tqhandler.h>
#include <bssap_timer.h>
#include <bssap_map.h>
#include <bssap_dbc.h>
#include <bssap_pegs.h>
#include <bssap-alarm.h> //25-01-08 by Amaresh
#include <bssap_appiddb.h> //04-02-08
#include <bssap_apiid.h> //04-02-08
#include <bssap_cfgdb.h>


#if defined (CCITT)
#define FAMILY               FAMILY_ITU
#else
#define FAMILY               FAMILY_ANSI
#endif

ITS_OCTET TIMER_Tries[BSSAP_NUM_TIMERS];
ITS_BOOLEAN pauseFlag = ITS_TRUE;
ITS_BOOLEAN sspFlag = ITS_FALSE;
TQUEUETRAN_Manager* __BSSAP_RcvQueue = NULL;
static ITS_THREAD   bssapThread;
static ITS_TIME timers[BSSAP_NUM_TIMERS];
TIMERS_DECL_SUBSYS(BSSAP, timers);
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
extern ITS_UINT SccpAllowedFlag;
/*Patch:Itika:2-Nov-10:End*/
extern ITS_UINT LocalRoutePc ;
static ITS_UINT pegs[PEG_BSSAP_NUM_PEGS];
static PEGS_DECL_SUBSYS(BSSAP, pegs);
PEG_Manager *BSSAP_Pegs = &BSSAP_PEGS;
extern ITS_OCTET glb_bscId;

HASH_Table BSCID_Table;
#define LEVEL_MAP_COUNT                5

extern "C"
{

typedef struct  
{
  ITS_UINT  PC;
  ITS_OCTET SSN;
  ITS_OCTET PCStatus;
  ITS_OCTET SSNStatus;
}
Conf_Ent;
ITS_OCTET cnt=0;
Conf_Ent ENTRY[BSSAPMAX_PC];

//SS7_Destination *
ROUTE_Info *
        ROUTE_FindDest(ITS_UINT pointCode, ITS_OCTET ni, SS7_Family family);
static TRACE_OutputInitializer fileCritTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    BSSAP_FILE_STRING,
    ITS_TRUE,
    BSSAP_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    BSSAP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    BSSAP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};


static TRACE_LevelInitializer BSSAP_TraceMap[] =
{
    {BSSAP_CRITICAL_STRING, ITS_TRUE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {BSSAP_ERROR_STRING,    ITS_TRUE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {BSSAP_WARNING_STRING,  ITS_TRUE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {BSSAP_DEBUG_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {BSSAP_EVENT_STRING,    ITS_FALSE, 3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

TRACE_Data* BSSAP_TraceData = NULL;

/*implementation:internal
*
* PURPOSE:
*       It sends link(MTP3) status info to application
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0250
*/
static void
BSSAP_MTP3MgmtHandler(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{
#if 0
    ITS_OCTET  ret_code = 0;
    ITS_EVENT *event = ( ITS_EVENT *)callData;
/* Added by Amaresh */
    MTP3_HEADER hdr;
    MTP3_STATUS stat;
    ITS_UINT pc = 0;
/* Addition completed by Amaresh */

    BSSAP_Interface bssIf;

    BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler\n"));

    ret_code = MTP3_MSG_TYPE(event);
/* Added by Amaresh */
   memcpy(&hdr, &event->data[1], sizeof(MTP3_HEADER));

    pc = MTP3_RL_GET_OPC_VALUE(hdr.label);
/* Addition completed by Amaresh */


    if (ret_code == MTP3_MSG_RESUME)
    {
      //  pauseFlag = ITS_FALSE;

     BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler: MTP-RESUME from pc %d\n", pc));
 
    }
    else if (ret_code == MTP3_MSG_PAUSE)
    {
      //  pauseFlag = ITS_TRUE;

    BSSAP_CRITICAL(("BSSAP_MTP3MgmtHandler: MTP-PAUSE from pc %d\n", pc));
    }
    else if (ret_code == MTP3_MSG_STATUS)
    {
  BSSAP_DEBUG(("BSSAP_MTP3MgmtHandler: MTP-STATUS from pc %d\n", pc));
/* Added by Amaresh */
      ITS_UINT len = event->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER));
      memcpy(&stat, &event->data[1 + sizeof(MTP3_HEADER)], len);
      ret_code = stat.cause;
/* Addition completed by Amaresh */
    }

/*    bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code); */
      bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code, pc, 0); /* Added by Amaresh */	
#endif
}

/*implementation:internal
*
* PURPOSE:
*       It sends Routing(SCCP) status info to application
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0250
*/
static void
BSSAP_SCCPMgmtHandler(ITS_POINTER object, ITS_POINTER userData,
                      ITS_POINTER callData)
{
    ITS_OCTET ret_code = 0;
    ITS_OCTET ret_code_mtp3 = 0;
    ITS_EVENT *event = (ITS_EVENT*)callData;
    ITS_EVENT *event_mtp3 = (ITS_EVENT*)callData;
    ITS_SCCP_IE ies[32];
    ITS_HDR hdr;
    MTP3_HEADER hdr_mtp3;
    MTP3_HEADER HDR;
    int ieCount;
    ITS_OCTET *scmgData = NULL;
    ITS_USHORT dlen = 0,j=0;
/* Added by Amaresh */
    ITS_UINT pc = 0;
    ITS_UINT pc_mtp3 = 0;
    ITS_UINT OPC = 0;
    ITS_OCTET ssn = 0;
    MTP3_STATUS stat;
/* Addition completed by Amaresh */

    BSSAP_Interface bssIf;
    ITS_OCTET ni=0;

    BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler\n"));
     memcpy(&HDR, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)], sizeof(MTP3_HEADER));
    if (SCCP_MSG_TYPE(event) != SCCP_MSG_UDT)
    {
        BSSAP_ERROR(("BSSAP_SCCPMgmtHandler: Unknown SCCP mssg. from stack\n"));
        /**************************************************************/    
        ret_code_mtp3 = MTP3_MSG_TYPE(event_mtp3);
        memcpy(&hdr_mtp3, &event_mtp3->data[1], sizeof(MTP3_HEADER));

        pc_mtp3 = MTP3_RL_GET_OPC_VALUE(hdr_mtp3.label);
        if (ret_code_mtp3 == MTP3_MSG_RESUME)
         {
             pauseFlag = ITS_FALSE;
             BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: MTP-RESUME from pc %d\n", pc_mtp3));
             for(j=0;j<=event_mtp3->len;j++)
              {
               // BSSAP_DEBUG ((" \t%02x", event_mtp3->data[j]));
              }
 
         }
         else if (ret_code_mtp3 == MTP3_MSG_PAUSE)
         {
           pauseFlag = ITS_TRUE;
           BSSAP_CRITICAL(("BSSAP_SCCPMgmtHandler: MTP-PAUSE from pc %d\n", pc));
           for(j=0;j<=event_mtp3->len;j++)
              {
           //    BSSAP_DEBUG ((" \t%02x", event_mtp3->data[j]));
              }
         }
         else if (ret_code_mtp3 == MTP3_MSG_STATUS)
         {
           BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: MTP-STATUS from pc %d\n", pc));
           for(j=0;j<=event_mtp3->len;j++)
             {
             //  BSSAP_DEBUG ((" \t%02x", event_mtp3->data[j]));
             }
           ITS_UINT len = event_mtp3->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER));
           memcpy(&stat, &event_mtp3->data[1 + sizeof(MTP3_HEADER)], len);
           ret_code_mtp3 = stat.cause;
          }
          bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code_mtp3, pc_mtp3, 0); 	
          /**************************************************************/    
    }
    else
    {
        if (SCCP_ReceiveUnitData((ITS_HANDLE)ISS7_Stack,
                                 event,&hdr, ies,
                                 &ieCount) != ITS_SUCCESS)
        {
            BSSAP_ERROR(("BSSAP_SCCPMgmtHandler: Error in SCCP mgmt-mssg.\n"));

            return;
        }

        for (int i=0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_DATA)
            {
                scmgData = ies[i].param_data.userData.data;
                dlen = ies[i].param_length;
            }
        }

        OPC = MTP3_RL_GET_OPC_VALUE(HDR.label);
        ni=MTP3_HDR_GET_SIO(HDR) & MTP3_NIC_MASK;
    //    BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: OPC=%d.\n",OPC));
        ret_code = ((SCCP_SCMG *)scmgData)->type;

/* Added by Amaresh */
        //pc = MTP3_PC_GET_VALUE_CCITT(((SCCP_SCMG *)scmgData)->pointCode);
        pc = MTP3_PC_GET_VALUE(((SCCP_SCMG *)scmgData)->pointCode);
        ssn = ((SCCP_SCMG *)scmgData)->ssn;

        BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler:OPC %d SCCP mgmt-mssg from %d %d\n",
                                                                   OPC ,pc, ssn));

/* Addition completed by Amaresh */

        switch (ret_code)
        {
            case SCCP_SCMG_SS_ALLOWED:
                sspFlag = ITS_FALSE;
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SSA\n"));
                break;
            case SCCP_SCMG_SS_PROHIBIT:
                sspFlag = ITS_TRUE;
                BSSAP_CRITICAL(("BSSAP_SCCPMgmtHandler: SCCP-SSP\n"));
                break;
            case SCCP_SCMG_SS_STATUS_TEST:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SST\n"));
                break;
            case SCCP_SCMG_SS_OOS_REQ:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-OSS-REQ\n"));
                break;
            case SCCP_SCMG_SS_OOS_GRANT:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-OSS-GRANT\n "));
                break;
            case SCCP_SCMG_SS_BACKUP_ROUTE:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-BACKUP\n"));
                break;
            case SCCP_SCMG_SS_NORMAL_ROUTE:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-NORMAL\n"));
                break;
            case SCCP_SCMG_SS_ROUTE_STATUS:
                BSSAP_DEBUG(("BSSAP_SCCPMgmtHandler: SCCP-SS-ROUTE-STATUS\n"));
                break;
            default:
                BSSAP_WARNING(("BSSAP_SCCPMgmtHandler: SCCP Management Msg\n"));
                return;
        }

       /* bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code); */
        setconfig_status(OPC,pc,ssn,ret_code,ni);
	  bssIf.DispatchErrorToApp(BSSAP_MD_NETWORK, ret_code, pc, ssn);
    }
}


/*implementation:internal
*
* PURPOSE:
*       set configuration details with default values.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Ashutosh  20-07-2007  
*/
/* Get the NI set at the SCCP and MTP3 level and send NI from BSSAP Accordingly Guru-National MTP Routing Problem -190107*/
ITS_OCTET
GET_NetworkInd(ITS_UINT dpc,ITS_OCTET rssn,ITS_OCTET *ni)
{
   ITS_BOOLEAN isAllowed=ITS_TRUE;
   ITS_BOOLEAN isNational=ITS_FALSE;
       if (ROUTE_GetRouteContextStatus(dpc,&isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,(MTP3_NIC_INTERNATIONAL| MTP3_SIO_SCCP),                                          rssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                            ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
         {
            if (ROUTE_GetRouteContextStatus(dpc,&isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_SPARE | MTP3_SIO_SCCP),rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if (ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_NATIONAL | MTP3_SIO_SCCP),rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                  {
                      if (ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY,
                                               (MTP3_NIC_RESERVED | MTP3_SIO_SCCP),rssn,ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                      {

                                 printf("SET SSN FAIL");
                      }
                      else
                      {
                             *ni=MTP3_NIC_RESERVED;
                             isNational=ITS_TRUE;
                      }
                  }
                  else
                  {
                      *ni=MTP3_NIC_NATIONAL;
                      isNational=ITS_TRUE;
                  }
                }
              else
              {
                 *ni=MTP3_NIC_SPARE;
              }
         }
         else
         {
               *ni=MTP3_NIC_INTERNATIONAL;
         }

           BSSAP_CRITICAL(("BSSAP_SetConfig: NI=%d\n",*ni));

}


int 
setconfig_status(ITS_UINT OPC,ITS_UINT DPC,ITS_OCTET Ssn,ITS_OCTET msgtype,ITS_OCTET ni)
{   
 ROUTE_Info* destPtr ,*rInfo;
 ITS_INT routeId=0;
 ITS_UINT key;
 ITS_OCTET sio=0;
 int ret=!ITS_SUCCESS;
// BSSAP_DEBUG(("BSSAP_SetConfig: START\n"));

   if(ni == 0)
   {
      GET_NetworkInd(DPC,Ssn,&ni);
   }

   BSSAP_CRITICAL(("BSSAP_SetConfig: OPC %d NI=%d FAMILY %d\n",OPC,ni,FAMILY));
   destPtr = ROUTE_FindDest(OPC, ni, FAMILY);
   if (destPtr == NULL)
      {
           BSSAP_CRITICAL(("BSSAP_SetConfig: Destination not Found\n"));
           return(!ITS_SUCCESS);
      }

          sio=ni| MTP3_SIO_SCCP;
          ni=sio & MTP3_NIC_MASK;
        for (rInfo = destPtr ; rInfo != NULL; rInfo = rInfo->next)

          {
              //      BSSAP_DEBUG(("BSSAP_setConfig:Style=%d\n",rInfo->basic.style));
              //      BSSAP_DEBUG(("BSSAP_setConfig:basictype=%d\n",rInfo->basic.type));

            if (rInfo->basic.style == ROUTE_DPC_OPC_SIO_SSN
                        &&  rInfo->basic.type == CONCERNED_ROUTE)
             {
               //    BSSAP_DEBUG(("BSSAP_setConfig:PC=%d\n",rInfo->basic.dpc));
               //    BSSAP_DEBUG(("BSSAP_setConfig:SSN=%d\n",rInfo->basic.criteria.ssn));
               //    BSSAP_DEBUG(("BSSAP_setConfig:SSN Status=%d\n",rInfo->basic.criteria.ssnstatus));

                 switch(msgtype)
                  {
                       case SCCP_SCMG_SS_ALLOWED:
                             if( rInfo->basic.dpc==DPC &&  rInfo->basic.criteria.ssn==Ssn)
                               {
                                  BSSAP_CRITICAL(("BSSAP_SetConfig: SCCP-SSA\n"));
                                  rInfo->basic.criteria.ssnstatus=SSNALLWD;
                                  SccpAllowedFlag = 1;
                                 //BSSAP_DEBUG(("BSSAP_setConfig:SSN Status=%d\n",rInfo->basic.criteria.ssnstatus));
                                  if(rInfo)
                                         {
                                           key = OPC | ((ni ) << 24) ;
                                          //           BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
                                    #if defined (CCITT)
                                           ret = DSM_Commit(DSM_SccpFtGroupId,
                                                         DSM_TABLE_ITU_SCCP_LPC,
                                                          (ITS_OCTET *)&key,
                                                          sizeof(ITS_UINT),
                                                          destPtr);
                                    #else
                                           ret = DSM_Commit(DSM_SccpFtGroupId,
                                                         DSM_TABLE_ANSI_SCCP_LPC,
                                                          (ITS_OCTET *)&key,
                                                          sizeof(ITS_UINT),
                                                          destPtr);
                                    #endif
                                          if(ret!=ITS_SUCCESS)
                                            {
                                                  BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

                                            }
                                         //          BSSAP_CRITICAL(("BSSAP_SetConfig: SUCESS\n"));
                                       }
                                } 

                        break;
                        case SCCP_SCMG_SS_PROHIBIT:
                             if( rInfo->basic.dpc==DPC &&  rInfo->basic.criteria.ssn==Ssn)
                                {
                                  BSSAP_CRITICAL(("BSSAP_SetConfig: SCCP-SSP\n"));
                                  rInfo->basic.criteria.ssnstatus=SSNPROBH;
                                  SccpAllowedFlag = 0;
                                  //   BSSAP_DEBUG(("BSSAP_setConfig:SSNStatus=%d\n",rInfo->basic.criteria.ssnstatus));
                                  key = OPC | ((ni ) << 24) ;
                                 //       BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
                                 #if defined (CCITT)
                                  ret = DSM_Commit(DSM_SccpFtGroupId,
                                                    DSM_TABLE_ITU_SCCP_LPC,
                                                       (ITS_OCTET *)&key,
                                                        sizeof(ITS_UINT),
                                                               destPtr);
                                 #else
                                  ret = DSM_Commit(DSM_SccpFtGroupId,
                                                    DSM_TABLE_ANSI_SCCP_LPC,
                                                       (ITS_OCTET *)&key,
                                                        sizeof(ITS_UINT),
                                                               destPtr);
                                 #endif
                                  if(ret!=ITS_SUCCESS)
                                  {
                                       BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

                                  }
                                }

                        break;
                        case MTP3_MSG_RESUME:
                              BSSAP_CRITICAL(("BSSAP_SetConfig: RESUME\n"));
                             if(rInfo)
                               { 
                                   key = OPC | ((ni ) << 24) ;
                             //      BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));

                                  #if defined (CCITT)
                                   ret = DSM_Commit(DSM_SccpFtGroupId,
                                                     DSM_TABLE_ITU_SCCP_LPC,
                                                     (ITS_OCTET *)&key,
                                                     sizeof(ITS_UINT),
                                                     destPtr);
                                  #else
                                   ret = DSM_Commit(DSM_SccpFtGroupId,
                                                     DSM_TABLE_ANSI_SCCP_LPC,
                                                     (ITS_OCTET *)&key,
                                                     sizeof(ITS_UINT),
                                                     destPtr);
                                  #endif
                                  if(ret!=ITS_SUCCESS)
                                    {
                                          BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

                                    }
                                 }
           
                              // destPtr->status=DESTINATION_AVAILABLE;
                        break;
                        case  MTP3_MSG_PAUSE:
                              if(rInfo)
                               {
                                 key = OPC | ((ni ) << 24) ;
                                //    BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
                                #if defined (CCITT)

                                ret = DSM_Commit(DSM_SccpFtGroupId,
                                                  DSM_TABLE_ITU_SCCP_LPC,
                                                  (ITS_OCTET *)&key,
                                                   sizeof(ITS_UINT),
                                                              destPtr);
                                #else
                                ret = DSM_Commit(DSM_SccpFtGroupId,
                                                  DSM_TABLE_ANSI_SCCP_LPC,
                                                  (ITS_OCTET *)&key,
                                                   sizeof(ITS_UINT),
                                                              destPtr);
                                #endif
                                 if(ret!=ITS_SUCCESS)
                                 {
                                      BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

                                 }
                              }
           

                            BSSAP_CRITICAL(("BSSAP_SetConfig: PAUSE\n"));
                     break;
                     case MTP3_MSG_STATUS:
                          if(rInfo)
                          {
                                key = OPC | ((ni ) << 24) ;
                               //  BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
                                #if defined (CCITT)
                                ret = DSM_Commit(DSM_SccpFtGroupId,
                                           DSM_TABLE_ITU_SCCP_LPC,
                                             (ITS_OCTET *)&key,
                                           sizeof(ITS_UINT),
                                           destPtr);
                               #else
                                ret = DSM_Commit(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_LPC,
                                             (ITS_OCTET *)&key,
                                           sizeof(ITS_UINT),
                                           destPtr);
                               #endif
                                if(ret!=ITS_SUCCESS) 
                                 {
                                       BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

                                 }
                           }
           
                      //     BSSAP_CRITICAL(("BSSAP_SetConfig: STATUS\n"));

                   break;
                  // deault:
   
                }/*end of switch*/
              }/*end of if*/
            }/*end of for*/


        return (ret);

}



/*implementation:internal
*
* PURPOSE:
*       get configuration details with default values.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* Ashutosh  20-07-2007  
*/
int 
getconfig_status(ITS_BOOLEAN *pauseFlag,ITS_BOOLEAN *sspFlag,ITS_Event& ev,ITS_OCTET Ssn)
{   

 BSSAPData data;
 ITS_EVENT evt;
 ITS_OCTET bscId;
 BSSAP_CfgDB db;
 CFGData* cfgdata = NULL; 
 ITS_UINT Pc=0;
 ITS_UINT OPC=0;
 ITS_OCTET i=0;
 ITS_OCTET ni=0;
 SS7_Destination* dest = NULL;
 ROUTE_Info * destPtr, *rInfo;
 ITS_INT routeId=0;
 ITS_UINT key;
 ITS_OCTET sio=0;
 int ret = !ITS_SUCCESS;

   evt = ev.GetEvent();
   memcpy(&data, evt.data, sizeof(BSSAPData)); 
   BSSAP_Api* mssg = new BSSAP_Api(&data);

   bscId= mssg->GetBssId();
   cfgdata = db.FetchRPCEntry(bscId);
   if (cfgdata)
    {
     Pc=cfgdata->rpc;
     OPC=cfgdata->lpc;
     LocalRoutePc = OPC;
     BSSAP_DEBUG(("BSSAP_getConfig:PC=%d\n",Pc));
    }
    else
    {
     BSSAP_DEBUG(("BSSAP_getConfig fail\n"));
    }

   if(ni == 0)
   {
      GET_NetworkInd(Pc,Ssn,&ni);
   }
    BSSAP_CRITICAL(("BSSAP_SetConfig: NI=%d\n",ni));
    destPtr = ROUTE_FindDest(OPC, ni, FAMILY);
    if (destPtr == NULL)
     {
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;
            key = OPC | ((ni ) << 24) ;
 //           BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                              DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
            #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
            #endif
            if(ret!=ITS_SUCCESS)
            {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));
            }
        return ITS_SUCCESS;
     }
 //   BSSAP_DEBUG(("BSSAP_SetConfig:  Route Entry=%x\n",destPtr));




   for (rInfo = destPtr ; rInfo != NULL; rInfo = rInfo->next)
   {
   //   BSSAP_DEBUG(("BSSAP_setConfig:Style=%d\n",rInfo->basic.style));
   //   BSSAP_DEBUG(("BSSAP_setConfig:basictype=%d\n",rInfo->basic.type));
     if( rInfo->basic.dpc==Pc
             &&  rInfo->basic.criteria.ssn==Ssn
                &&  rInfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
      {
//              BSSAP_DEBUG(("BSSAP_getConfig:SSNFLAG=%d\n",rInfo->basic.criteria.ssnstatus));


            if(rInfo->basic.criteria.ssnstatus==SSNALLWD)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN UP\n"));
             *sspFlag=ITS_FALSE;      
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/ 
              SccpAllowedFlag = 1;    
/*Patch:Itika:2-Nov-10:End*/

            }

            else if(rInfo->basic.criteria.ssnstatus==SSNPROBH)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN DWN\n"));
              BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d ssn %d",Pc,Ssn);

             *sspFlag=ITS_TRUE;          
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/ 
              SccpAllowedFlag = 0;    
/*Patch:Itika:2-Nov-10:End*/

            }
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;

            key = OPC | ((ni) << 24) ;
     //       BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
           #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
           #endif
                                  
          if(ret!=ITS_SUCCESS)
           {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

           }
      }
   }
   dest = ROUTE_FindDestination(Pc, ni, FAMILY);
   if(dest == NULL)
   {
     return ITS_SUCCESS;
   }
   for(routeId = 0; routeId < dest->numEntries; routeId++)
    {
       if( dest->entries[routeId]->basic.dpc==Pc
             &&  dest->entries[routeId]->basic.criteria.ssn==Ssn
                 && dest->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN )
      {
  //           BSSAP_DEBUG(("BSSAP_getConfig:PCSTAUTS=%d\n",dest->status));

            if(dest->status==DESTINATION_AVAILABLE )
            {
               BSSAP_DEBUG(("BSSAP_getConfig:PC UP \n"));
              *pauseFlag=ITS_FALSE;

            }
   

            else if(dest->status==DESTINATION_UNAVAILABLE)  
            {
              BSSAP_DEBUG(("BSSAP_getConfig:PC DWN \n"));
              BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d ",Pc);
 
             *pauseFlag=ITS_TRUE;

            }  

      }

  }
   
     BSSAP_WARNING(("BSSAP_getConfig:sspFlag=%d pauseFlag =%d \n",*sspFlag,*pauseFlag));


    delete mssg;
     mssg = NULL;


}

int 
getSccpReq_status(ITS_BOOLEAN *pauseFlag,ITS_BOOLEAN *sspFlag,ITS_Event& ev,ITS_OCTET Ssn)
{   

 BSSAPData data;
 ITS_EVENT evt;
 ITS_OCTET bscId;
 BSSAP_CfgDB db;
 CFGData* cfgdata = NULL; 
 ITS_UINT Pc=0;
 ITS_UINT OPC=0;
 ITS_OCTET i=0;
 ITS_OCTET ni=0;
 SS7_Destination* dest = NULL;
 ROUTE_Info * destPtr, *rInfo;
 ITS_INT routeId=0;
 ITS_UINT key;
 ITS_OCTET sio=0;
 int ret = !ITS_SUCCESS;

   evt = ev.GetEvent();
   memcpy(&data, evt.data, sizeof(BSSAPData)); 
   BSSAP_Api* mssg = new BSSAP_Api(&data);

   bscId= glb_bscId;
   cfgdata = db.FetchRPCEntry(bscId);
   if (cfgdata)
    {
     Pc=cfgdata->rpc;
     OPC=cfgdata->lpc;
     LocalRoutePc = OPC;
     BSSAP_DEBUG(("BSSAP_getConfig:PC=%d\n",Pc));
    }
    else
    {
     BSSAP_DEBUG(("BSSAP_getConfig fail\n"));
    }

   if(ni == 0)
   {
      GET_NetworkInd(Pc,Ssn,&ni);
   }
    BSSAP_CRITICAL(("BSSAP_SetConfig: NI=%d\n",ni));
    destPtr = ROUTE_FindDest(OPC, ni, FAMILY);
    if (destPtr == NULL)
     {
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;
            key = OPC | ((ni ) << 24) ;
 //           BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                              DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
            #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                              DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
            #endif
            if(ret!=ITS_SUCCESS)
            {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));
            }
        return ITS_SUCCESS;
     }
 //   BSSAP_DEBUG(("BSSAP_SetConfig:  Route Entry=%x\n",destPtr));




   for (rInfo = destPtr ; rInfo != NULL; rInfo = rInfo->next)
   {
   //   BSSAP_DEBUG(("BSSAP_setConfig:Style=%d\n",rInfo->basic.style));
   //   BSSAP_DEBUG(("BSSAP_setConfig:basictype=%d\n",rInfo->basic.type));
     if( rInfo->basic.dpc==Pc
             &&  rInfo->basic.criteria.ssn==Ssn
                &&  rInfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
      {
//              BSSAP_DEBUG(("BSSAP_getConfig:SSNFLAG=%d\n",rInfo->basic.criteria.ssnstatus));


            if(rInfo->basic.criteria.ssnstatus==SSNALLWD)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN UP\n"));
             *sspFlag=ITS_FALSE;      
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/ 
              SccpAllowedFlag = 1;    
/*Patch:Itika:2-Nov-10:End*/

            }

            else if(rInfo->basic.criteria.ssnstatus==SSNPROBH)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN DWN\n"));
              BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d ssn %d",Pc,Ssn);

             *sspFlag=ITS_TRUE;          
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/ 
              SccpAllowedFlag = 0;    
/*Patch:Itika:2-Nov-10:End*/

            }
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;

            key = OPC | ((ni) << 24) ;
     //       BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
           #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_UINT),
                                   destPtr);
           #endif
                                  
          if(ret!=ITS_SUCCESS)
           {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

           }
      }
   }
   dest = ROUTE_FindDestination(Pc, ni, FAMILY);
   if(dest == NULL)
   {
     return ITS_SUCCESS;
   }
   for(routeId = 0; routeId < dest->numEntries; routeId++)
    {
       if( dest->entries[routeId]->basic.dpc==Pc
             &&  dest->entries[routeId]->basic.criteria.ssn==Ssn
                 && dest->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN )
      {
  //           BSSAP_DEBUG(("BSSAP_getConfig:PCSTAUTS=%d\n",dest->status));

            if(dest->status==DESTINATION_AVAILABLE )
            {
               BSSAP_DEBUG(("BSSAP_getConfig:PC UP \n"));
              *pauseFlag=ITS_FALSE;

            }
   

            else if(dest->status==DESTINATION_UNAVAILABLE)  
            {
              BSSAP_DEBUG(("BSSAP_getConfig:PC DWN \n"));
              BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d ",Pc);
 
             *pauseFlag=ITS_TRUE;

            }  

      }

  }
   
     BSSAP_WARNING(("BSSAP_getConfig:sspFlag=%d pauseFlag =%d \n",*sspFlag,*pauseFlag));


    delete mssg;
     mssg = NULL;


}

int 
getbssap_status(ITS_BOOLEAN *pauseFlag,ITS_BOOLEAN *sspFlag, ITS_OCTET bscId,ITS_OCTET Ssn)
{   

 BSSAPData data;
 ITS_EVENT evt;
 BSSAP_CfgDB db;
 CFGData* cfgdata = NULL; 
 ITS_UINT Pc=0;
 ITS_UINT OPC=0;
 ITS_OCTET i=0;

 ITS_OCTET ni=0;
 SS7_Destination* dest = NULL;
 ROUTE_Info* destPtr ,*rInfo;
 ITS_INT routeId=0;
 ITS_UINT key;
 ITS_OCTET sio=0;
 int ret = !ITS_SUCCESS;

   cfgdata = db.FetchRPCEntry(bscId);
   if (cfgdata)
    {
     Pc=cfgdata->rpc;
     OPC=cfgdata->lpc;
     BSSAP_DEBUG(("BSSAP_getConfig:PC=%d\n",Pc));
    }
    else
    {
     BSSAP_DEBUG(("BSSAP_getConfig fail\n"));
    }

   if(ni == 0)
   {
      GET_NetworkInd(Pc,Ssn,&ni);
   }
    BSSAP_CRITICAL(("BSSAP_SetConfig: NI=%d\n",ni));

    destPtr = ROUTE_FindDest(OPC, ni, FAMILY);
    if (destPtr == NULL)
     {
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;
            key = OPC | ((ni ) << 24) ;
    //        BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_INT),
                                   destPtr);
            #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_INT),
                                   destPtr);
            #endif
          if(ret!=ITS_SUCCESS)
           {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));
           }
        return ITS_SUCCESS;
     }
  //  BSSAP_DEBUG(("BSSAP_SetConfig:  Route Entry=%x\n",destPtr));

 //  for(routeId = 0; routeId < destPtr->numEntries; routeId++)
   for (rInfo = destPtr ; rInfo != NULL; rInfo = rInfo->next)
    {
      if( rInfo->basic.dpc==Pc
             &&  rInfo->basic.criteria.ssn==Ssn
                &&  rInfo->basic.style == ROUTE_DPC_OPC_SIO_SSN)
      {
              BSSAP_DEBUG(("BSSAP_getConfig:SSNFLAG=%d\n",rInfo->basic.criteria.ssnstatus));


            if(rInfo->basic.criteria.ssnstatus==SSNALLWD)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN UP\n"));
             *sspFlag=ITS_FALSE;          

            }

            else if(rInfo->basic.criteria.ssnstatus==SSNPROBH)
            {
              BSSAP_DEBUG(("BSSAP_getConfig: SSN DWN\n"));
              BSSAP_Alarm_CCITT(5117,__FILE__,__LINE__,"dpc %d ssn %d",Pc,Ssn);
             *sspFlag=ITS_TRUE;          

            }
            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;

            key = OPC | ((ni & ROUTE_NI_MASK) << 24) ;
            //        BSSAP_CRITICAL(("BSSAP_SetConfig: Key=%d\n",key));
            #if defined (CCITT)

            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ITU_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_INT),
                                   destPtr);
           #else
            ret = DSM_Commit(DSM_SccpFtGroupId,
                             DSM_TABLE_ANSI_SCCP_LPC,
                                   (ITS_OCTET *)&key,
                                   sizeof(ITS_INT),
                                   destPtr);
           #endif
                                  
          if(ret!=ITS_SUCCESS)
           {
              BSSAP_CRITICAL(("BSSAP_SetConfig: Fail\n"));

           }
  

      }

   }
    dest = ROUTE_FindDestination(Pc, ni, FAMILY);
    for(routeId = 0; routeId < dest->numEntries; routeId++)
    {
       if( dest->entries[routeId]->basic.dpc==Pc
             &&  dest->entries[routeId]->basic.criteria.ssn==Ssn
                 && dest->entries[routeId]->basic.style == ROUTE_DPC_SIO_SSN )
      {
        //             BSSAP_DEBUG(("BSSAP_getConfig:SSNFLAG=%d\n",dest->entries[routeId]->basic.criteria.ssnstatus));
            BSSAP_DEBUG(("BSSAP_getConfig:PCSTAUTS=%d\n",dest->status));

            if(dest->status==DESTINATION_AVAILABLE )
            {
               BSSAP_DEBUG(("BSSAP_getConfig:PC UP \n"));
              *pauseFlag=ITS_FALSE;

            }
   

            else if(dest->status==DESTINATION_UNAVAILABLE)  
            {
              BSSAP_DEBUG(("BSSAP_getConfig:PC DWN \n"));
              BSSAP_Alarm_CCITT(5118,__FILE__,__LINE__,"dpc %d ",Pc);
             *pauseFlag=ITS_TRUE;

            }  

      }

   }
     BSSAP_DEBUG(("BSSAP_getConfig:sspFlag=%d pauseFlag =%d \n",*sspFlag,*pauseFlag));
        return (ret);

}




//SS7_Destination *
ROUTE_Info *
ROUTE_FindDest(ITS_UINT pointCode, ITS_OCTET ni, SS7_Family family)
{
            ITS_INT key;
      //      SS7_Destination *ent;
           ROUTE_Info *ent = NULL;
            int error;
           ITS_OCTET sio=0;

            sio=ni| MTP3_SIO_SCCP;
            ni=sio & MTP3_NIC_MASK;
            /* work out the pkey */
            key = pointCode | ((ni ) << 24) ;
      //       BSSAP_DEBUG(("BSSAP_getConfig:key=%d\n", key));

            ent = NULL;
            #if defined (CCITT)

            ent = (ROUTE_Info *)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_ITU_SCCP_LPC,
                                 (ITS_OCTET *)&key,
                                 sizeof(ITS_INT),
                                 &error);
            #else
            ent = (ROUTE_Info *)DSM_Find(DSM_SccpFtGroupId,
                                 DSM_TABLE_ANSI_SCCP_LPC,
                                 (ITS_OCTET *)&key,
                                 sizeof(ITS_INT),
                                 &error);
            #endif


            if (error != ITS_SUCCESS)
            {
             BSSAP_DEBUG(("BSSAP_getConfig:PC Not Found\n"));
                return (NULL);
            }

            return (ent);
}

/*implementation:internal
*
* PURPOSE:
*       Intializing configuration details with default values.
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D1060, ID :: D1070,
*                        ID :: D1080, ID :: D1090 
*/
static void
InitSettings()
{
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_1, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_4, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_7, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_8, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_10, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_11, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_13, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_17, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_18, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_19, 60);
    TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_20, 60);

    for (int i = 0; i < BSSAP_NUM_TIMERS; i++)
    {
        // Setting 1 for retries by default
        TIMER_Tries[i] = 1;
    }


    if (TRANSPORT_RES(__BSSAP_RcvQueue) != NULL)
    {
        char value[ITS_PATH_MAX];
        RESFILE_Manager *res = TRANSPORT_RES(__BSSAP_RcvQueue);
        char *name = TRANSPORT_NAME(__BSSAP_RcvQueue);

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T1_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_1, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T4_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_4, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T7_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_7, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T8_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_8, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T10_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_10, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T11_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_11, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T13_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_13, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T17_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_17, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T18_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_18, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T19_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_19, atoi(value));
        }

        if (RESFILE_GetKeyValueOf(res, name, BSSAP_T20_INFO_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            TIMERS_SetTimerValue(&BSSAP_Timers, BSSAP_T_20, atoi(value));
        }

        // critical 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_CRITICAL_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_CRITICAL_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_CRITICAL_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_CRITICAL_STRING, ITS_FALSE);
            }
        }

        // error 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_ERROR_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);

                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_ERROR_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_ERROR_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_ERROR_STRING, ITS_FALSE);
            }
        }

        // warning
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_WARNING_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_WARNING_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_WARNING_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_WARNING_STRING, ITS_FALSE);
            }
        }

        // debug 
        if (RESFILE_GetKeyValueOf(res, name, BSSAP_TRACE_DEBUG_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

            if (strstr(value, BSSAP_STDOUT_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_STDOUT_STRING, ITS_TRUE);
                std = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_STDOUT_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_FILE_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_FILE_STRING, ITS_TRUE);
                fil = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_FILE_STRING, ITS_FALSE);
            }

            if (strstr(value, BSSAP_SYSLOG_STRING) != NULL)
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_TRUE);
                sys = ITS_TRUE;
            }
            else
            {
                TRACE_SetOutputOnOffByName(BSSAP_TraceData,
                                           BSSAP_DEBUG_STRING,
                                           BSSAP_SYSLOG_STRING, ITS_FALSE);
            }

            if (std || fil || sys)

            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_DEBUG_STRING, ITS_TRUE);
            }
            else
            {
                TRACE_SetLevelOnOffByName(BSSAP_TraceData,
                                          BSSAP_DEBUG_STRING, ITS_FALSE);
            }
        }
    }
}

/*implementation:internal
*
* PURPOSE:
*      Initialize the BSSAP subsystem.
* INPUT:
*      objClass - BSSAP stack object.
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*      ITS_SUCCES - success.  Any other value indicates an IntelliSS7
*      processing error.
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0270
*/
static ITS_INT 
BSSAP_Initialize(ITS_Class objClass)
{
    ITS_INT ret = 0;
    BSSAP_Map map;
    ITS_Class dbClass;
    BSSAP_Alarm_CCITT(5106,__FILE__,__LINE__,NULL,NULL); //25-01-08 by Amaresh OAM 	

    if ((BSSAP_TraceData = TRACE_Constructor("BSSAP",
                                                  BSSAP_TraceMap, 
                                                      LEVEL_MAP_COUNT)) == NULL)
    {
        return (ITS_ENOMEM);
    }


    __BSSAP_RcvQueue  = TQUEUETRAN_CreateTransport("BSSAP",
                                                   ITS_BSSAP_SRC,
                                                   ITS_SS7_MASK);
    if (!__BSSAP_RcvQueue)
    {
        printf("BSSAP_Initialize: Failed to create BSSAP Message queue\n");

        return (!ITS_SUCCESS);
    }
    else
    {
        printf("BSSAP_Initialize: BSSAP Message queue created\n");
    }

    TRANSPORT_IS_ACTIVE(__BSSAP_RcvQueue) = ITS_TRUE;

    InitSettings();

    if (!BSSAP_CallDB::IsInitialized())
    {
        ret = BSSAP_CallDB::Initialize();
        if (ret != ITS_SUCCESS)
        {
            printf("BSSAP_Initialize: Failed to initialize call table\n");

            return (!ITS_SUCCESS);
        }
    }
/* Added by Amaresh for Appid DB initialize 04-02-08*/
        if (!BSSAP_AppidDB::IsInitialized())
    {
        ret = BSSAP_AppidDB::Initialize();
        if (ret != ITS_SUCCESS)
        {
            printf("BSSAP_Initialize: Failed to initialize Appid table\n");

            return (!ITS_SUCCESS);
        }
    }
/* Addition completed by Amaresh for Appid DB initialize 04-02-08 */

    map.Initialize();


    if (THREAD_CreateThread(&bssapThread, 0, BSSAP_MssgHandler,
                            __BSSAP_RcvQueue, ITS_TRUE) != ITS_SUCCESS)
    {

        printf("BSSAP_Initialize: Failed to create BSSAP Stack thread\n"); 

        THREAD_KillThread(&bssapThread);

        THREAD_DeleteThread(&bssapThread);

        return (!ITS_SUCCESS);
    }

    DBC_ServerCreate("Demo", NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        printf("BSSAP_Initialize: Debug Console active\n");

        DBC_AddDoCommand(BSSAP_ConsoleCommand);
    }

    CALLBACK_AddCallback(MTP3_ManagementCallbacks, BSSAP_MTP3MgmtHandler, NULL);
    CALLBACK_AddCallback(SCCP_ManagementCallbacks, BSSAP_SCCPMgmtHandler, NULL);
    BSCID_Table=HASH_CreateTable();

    return (ITS_SUCCESS);
}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0260
*/
static void
BSSAP_Terminate(ITS_Class objClass)
{
	BSSAP_Alarm_CCITT(5107,__FILE__,__LINE__,NULL,NULL); //25-01-08 by Amaresh
}

}

/*implementation:internal
*
* PURPOSE:
*       None
* INPUT:
*       None
* INPUT/OUTPUT:
*       None
* OUTPUT:
*       None
* RETURNS:
*       None
* COMMENTS:
*       None
* HISTORY:
* -------------------------------------------------------------------------
*  Name     Date         Reference                  Description
* -------------------------------------------------------------------------
* mkrishna  23-11-2005   IMR-BSS-SDS-BSAP-V1.0.03
*                        ID :: D0260
*/
ITS_ClassRec itsBSSAP_ClassRec =
{
    /* core */
    {
        NULL,
        0,
        ITS_FALSE,
        0,
        "BSSAP",
        BSSAP_Initialize,
        BSSAP_Terminate,
        NULL,
        NULL,
        NULL
    }
};

ITS_Class itsBSSAP_Class = &itsBSSAP_ClassRec;

 
