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
 *  ID: $Id: bssap.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/25 05:52:46  ankur.sharda
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/06/28 04:11:40  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/17 05:32:26  adutta
 * LOG: Variable re-alignment
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_BASE_H_
#define  _BSSAP_BSSAP_H_

#include<its.h>
#include<its++.h>
#include <its_singleton.h>
#include <its_types.h>
#include <its_transports.h>
#include <its_tq_trans.h>
#include<engine.h>


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <ipcfrm_msgdef.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#endif

using namespace its;
using namespace std;


extern "C"
{
 extern TRACE_Data* BSSAP_TraceData;
}
 


#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif


#define BSSAP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define BSSAP_ERROR_STRING           ITS_ERROR_STRING
#define BSSAP_WARNING_STRING         ITS_WARNING_STRING
#define BSSAP_DEBUG_STRING           ITS_DEBUG_STRING
#define BSSAP_EVENT_STRING           ITS_EVENT_STRING

#define BSSAP_STDOUT_STRING          ITS_STDOUT_STRING
#define BSSAP_SYSLOG_STRING          ITS_SYSLOG_STRING
#define BSSAP_FILE_STRING            ITS_FILE_STRING

#define BSSAP_TRACE_CRITICAL_FILE    (void*)".itu-bssap-traceCritical"
#define BSSAP_TRACE_ERROR_FILE       (void*)".itu-bssap-traceError"
#define BSSAP_TRACE_WARNING_FILE     (void*)".itu-bssap-traceWarning"
#define BSSAP_TRACE_DEBUG_FILE       (void*)".itu-bssap-traceDebug"
#define BSSAP_TRACE_EVENT_FILE       (void*)".itu-bssap-traceEvent"

#define BSSAP_TRACE_CRITICAL  0
#define BSSAP_TRACE_ERROR     1
#define BSSAP_TRACE_WARNING   2
#define BSSAP_TRACE_DEBUG     3
#define BSSAP_TRACE_EVENT     4

#define BSSAP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define BSSAP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define BSSAP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define BSSAP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING

#ifdef LOGGER_IMR
#define BSSAP_CRITICAL(args) \
    LOG_PRINT_CRITICAL args;
#else
#define BSSAP_CRITICAL(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_CRITICAL, args)
#endif

#ifdef LOGGER_IMR
#define BSSAP_ERROR(args) \
    LOG_PRINT_CRITICAL args ;
#else
#define BSSAP_ERROR(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_ERROR, args)
#endif

#ifdef LOGGER_IMR
#define BSSAP_WARNING(args) \
   LOG_PRINT_MAJOR args;
#else
#define BSSAP_WARNING(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_WARNING, args)
#endif

#ifdef LOGGER_IMR
#define BSSAP_DEBUG(args) \
    LOG_PRINT_DEBUG args;
#else
#define BSSAP_DEBUG(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_DEBUG, args)
#endif

#define BSSAP_EVENT(args) \
    TRACE(BSSAP_TraceData, BSSAP_TRACE_EVENT, args)

extern "C"
{
#define BSSAPMAX_PC 0x09
#define PCUPSTAT    0x01
#define PCDWNSTAT   0x02
#define SSNALLWD    0x01
#define SSNPROBH    0x02
#define  PCCONGSTAT 0x03
int
setconfig_status(ITS_UINT pc,ITS_UINT PC,ITS_OCTET ssn,ITS_OCTET msgtype,ITS_OCTET ni);

int
 getconfig_status(ITS_BOOLEAN*, ITS_BOOLEAN*, its::ITS_Event&,ITS_OCTET Ssn);
int
getbssap_status(ITS_BOOLEAN *pauseFlag,ITS_BOOLEAN *sspFlag, ITS_OCTET bscId,ITS_OCTET Ssn);
int
 getSccpReq_status(ITS_BOOLEAN*, ITS_BOOLEAN*, its::ITS_Event&,ITS_OCTET Ssn);

/*
typedef struct  
{
  ITS_UINT  PC;
  ITS_OCTET SSN;
  ITS_OCTET PCStatus;
  ITS_OCTET SSNStatus;
}
Conf_Ent;
*/

}
/*change due to Imr REQUIREMENT*/

#define BSSAP_MSG_TYPE_STR(x) ((x==BSSAP_MSG_ASSIGN_COMPLETE)?"BSSAP_MSG_ASSIGN_COMPLETE":\
                    ((x==BSSAP_MSG_ASSIGN_FAILURE)?"BSSAP_MSG_ASSIGN_FAILURE":\
                    ((x==BSSAP_MSG_ASSIGN_REQUEST)?"BSSAP_MSG_ASSIGN_REQUEST":\
                    ((x==BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE)?"BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE":\
                    ((x==BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE)?"BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE":\
                    ((x==BSSAP_MSG_HANDOVER_COMMAND)?"BSSAP_MSG_HANDOVER_COMMAND":\
                    ((x==BSSAP_MSG_HANDOVER_COMPLETE)?"BSSAP_MSG_HANDOVER_COMPLETE":\
                    ((x==BSSAP_MSG_HANDOVER_DETECT)?"BSSAP_MSG_HANDOVER_DETECT":\
                    ((x==BSSAP_MSG_HANDOVER_FAILURE)?"BSSAP_MSG_HANDOVER_FAILURE":\
                    ((x==BSSAP_MSG_HANDOVER_PERFORMED)?"BSSAP_MSG_HANDOVER_PERFORMED":\
                    ((x==BSSAP_MSG_HANDOVER_REQUEST)?"BSSAP_MSG_HANDOVER_REQUEST":\
                    ((x==BSSAP_MSG_HANDOVER_REQUEST_ACK)?"BSSAP_MSG_HANDOVER_REQUEST_ACK":\
                    ((x==BSSAP_MSG_HANDOVER_REQUIRED)?"BSSAP_MSG_HANDOVER_REQUIRED":\
                    ((x==BSSAP_MSG_HANDOVER_REQUIRED_REJECT)?"BSSAP_MSG_HANDOVER_REQUIRED_REJECT":\
                    ((x==BSSAP_MSG_HANDOVER_SUCCEEDED)?"BSSAP_MSG_HANDOVER_SUCCEEDED":\
                    ((x==BSSAP_MSG_CLEAR_COMMAND)?"BSSAP_MSG_CLEAR_COMMAND":\
                    ((x==BSSAP_MSG_CLEAR_COMPLETE)?"BSSAP_MSG_CLEAR_COMPLETE":\
                    ((x==BSSAP_MSG_CLEAR_REQUEST)?"BSSAP_MSG_CLEAR_REQUEST":\
                    ((x==BSSAP_MSG_SAPI_N_REJECT)?"BSSAP_MSG_SAPI_N_REJECT":\
                    ((x==BSSAP_MSG_CONFUSION)?"BSSAP_MSG_CONFUSION":\
                    ((x==BSSAP_MSG_SUSPEND)?"BSSAP_MSG_SUSPEND":\
                    ((x==BSSAP_MSG_RESUME)?"BSSAP_MSG_RESUME":\
                    ((x==BSSAP_MSG_RESET)?"BSSAP_MSG_RESET":\
                    ((x==BSSAP_MSG_RESET_ACK)?"BSSAP_MSG_RESET_ACK":\
                    ((x==BSSAP_MSG_RESET_CIRCUIT)?"BSSAP_MSG_RESET_CIRCUIT":\
                    ((x==BSSAP_MSG_RESET_CIRCUIT_ACK)?"BSSAP_MSG_RESET_CIRCUIT_ACK":\
                    ((x==BSSAP_MSG_OVERLOAD)?"BSSAP_MSG_OVERLOAD":\
                    ((x==BSSAP_MSG_MSC_INVOKE_TRACE)?"BSSAP_MSG_MSC_INVOKE_TRACE":\
                    ((x==BSSAP_MSG_BSS_INVOKE_TRACE)?"BSSAP_MSG_BSS_INVOKE_TRACE":\
                    ((x==BSSAP_MSG_BLOCK)?"BSSAP_MSG_BLOCK":\
                    ((x==BSSAP_MSG_BLOCK_ACK)?"BSSAP_MSG_BLOCK_ACK":\
                    ((x==BSSAP_MSG_UNBLOCK)?"BSSAP_MSG_UNBLOCK":\
                    ((x==BSSAP_MSG_UNBLOCK_ACK)?"BSSAP_MSG_UNBLOCK_ACK":\
                    ((x==BSSAP_MSG_CKT_GROUP_BLOCK)?"BSSAP_MSG_CKT_GROUP_BLOCK":\
                    ((x==BSSAP_MSG_CKT_GRP_BLK_ACK)?"BSSAP_MSG_CKT_GRP_BLK_ACK":\
                    ((x==BSSAP_MSG_CKT_GRP_UNBLOCK)?"BSSAP_MSG_CKT_GRP_UNBLOCK":\
                    ((x==BSSAP_MSG_CKT_GRP_UNBLKING_ACK)?"BSSAP_MSG_CKT_GRP_UNBLKING_ACK":\
                    ((x==BSSAP_MSG_UNEQUIPPED_CKT)?"BSSAP_MSG_UNEQUIPPED_CKT":\
                    ((x==BSSAP_MSG_CHANGE_CKT)?"BSSAP_MSG_CHANGE_CKT":\
                    ((x==BSSAP_MSG_CHANGE_CKT_ACK)?"BSSAP_MSG_CHANGE_CKT_ACK":\
                    ((x==BSSAP_MSG_RESOURCE_REQUEST)?"BSSAP_MSG_RESOURCE_REQUEST":\
                    ((x==BSSAP_MSG_RESOURCE_INDICATION)?"BSSAP_MSG_RESOURCE_INDICATION":\
                    ((x==BSSAP_MSG_PAGING)?"BSSAP_MSG_PAGING":\
                    ((x==BSSAP_MSG_PAGING_RESPONSE)?"BSSAP_MSG_PAGING_RESPONSE":\
                    ((x==BSSAP_MSG_CIPHER_MODE_CMD)?"BSSAP_MSG_CIPHER_MODE_CMD":\
                    ((x==BSSAP_MSG_CIPHER_MODE_COMPLETE)?"BSSAP_MSG_CIPHER_MODE_COMPLETE":\
                    ((x==BSSAP_MSG_CIPHER_MODE_REJECT)?"BSSAP_MSG_CIPHER_MODE_REJECT":\
                    ((x==BSSAP_MSG_CLASSMARK_UPDATE)?"BSSAP_MSG_CLASSMARK_UPDATE":\
                    ((x==BSSAP_MSG_CLASSMARK_REQUEST)?"BSSAP_MSG_CLASSMARK_REQUEST":\
                    ((x==BSSAP_MSG_COMPLETE_LAYER3_INFO)?"BSSAP_MSG_COMPLETE_LAYER3_INFO":\
                    ((x==BSSAP_MSG_LOAD_INDICATION)?"BSSAP_MSG_LOAD_INDICATION":\
                    ((x==BSSAP_MSG_QUEUING_INDICATION)?"BSSAP_MSG_QUEUING_INDICATION":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP)?"BSSAP_MSG_VGCS_VBS_SETUP":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP_ACK)?"BSSAP_MSG_VGCS_VBS_SETUP_ACK":\
                    ((x==BSSAP_MSG_VGCS_VBS_SETUP_REFUSE)?"BSSAP_MSG_VGCS_VBS_SETUP_REFUSE":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_REQUEST":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_RESULT":\
                    ((x==BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE)?"BSSAP_MSG_VGCS_VBS_ASSIGNMENT_FAILURE":\
                    ((x==BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION)?"BSSAP_MSG_VGCS_VBS_QUEUING_INDICATION":\
                    ((x==BSSAP_MSG_UPLINK_REQUEST)?"BSSAP_MSG_UPLINK_REQUEST":\
                    ((x==BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION)?"BSSAP_MSG_UPLINK_REQUEST_CONFIRMATION":\
                    ((x==BSSAP_MSG_UPLINK_RELEASE_INDICATION)?"BSSAP_MSG_UPLINK_RELEASE_INDICATION":\
                    ((x==BSSAP_MSG_UPLINK_REJECT_COMMAND)?"BSSAP_MSG_UPLINK_REJECT_COMMAND":\
                    ((x==BSSAP_MSG_UPLINK_RELEASE_COMMAND)?"BSSAP_MSG_UPLINK_RELEASE_COMMAND":\
                    ((x==BSSAP_MSG_UPLINK_SEIZED_COMMAND)?"BSSAP_MSG_UPLINK_SEIZED_COMMAND":\
                    ((x==BSSAP_MSG_LSA_INFORMATION)?"BSSAP_MSG_LSA_INFORMATION":\
                    "UNKNOWN"))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#endif
