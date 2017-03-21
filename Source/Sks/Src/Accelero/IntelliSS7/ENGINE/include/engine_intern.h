/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:44  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:41  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:00  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2.6.2  2005/12/21 05:58:24  yranade
 * LOG: Add MTP2 strings.
 * LOG:
 * LOG: Revision 9.2.6.1  2005/08/29 09:22:40  adutta
 * LOG: BSSAP configuration
 * LOG:
 * LOG: Revision 9.2  2005/05/06 09:06:56  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:18  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:49:21  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.42.7  2005/01/19 11:04:35  adutta
 * LOG: M2UA xml changes
 * LOG:
 * LOG: Revision 7.5.42.6  2005/01/17 09:54:45  mkrishna
 * LOG: separate traces for SIP
 * LOG:
 * LOG: Revision 7.5.42.5  2005/01/04 13:47:39  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.5.42.4  2005/01/03 14:41:36  snagesh
 * LOG: Modifications for MTP2 vendor traces
 * LOG:
 * LOG: Revision 7.5.42.3  2004/12/28 13:13:24  mkrishna
 * LOG: SIP code propagated from Current Branch
 * LOG:
 * LOG: Revision 7.5.42.2  2004/12/16 01:48:58  randresol
 * LOG: Add JAPAN variant Implementation
 * LOG:
 * LOG: Revision 7.5.42.1  2004/12/15 12:35:27  asingh
 * LOG: separate traces for SCTP/UAL/M3UA
 * LOG:
 * LOG: Revision 7.5  2002/12/31 09:07:09  akumar
 * LOG: Two new MACROs have been introduced
 * LOG:
 * LOG: Revision 7.4  2002/12/26 22:31:21  mmiers
 * LOG: Let the user specify the instance if they really know what they're
 * LOG: doing.  Don't document this feature, it's mostly for us.
 * LOG:
 * LOG: Revision 7.3  2002/08/29 16:02:11  mmiers
 * LOG: Add default HMI callback
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:46:33  mmiers
 * LOG: Add the deselector to the DTD
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/08/22 20:35:42  omayor
 * LOG: Defining CHINA string.
 * LOG:
 * LOG: Revision 6.4  2002/08/22 14:32:43  mmiers
 * LOG: Add china dispatchers
 * LOG:
 * LOG: Revision 6.3  2002/07/02 21:26:36  mmiers
 * LOG: Work on getting debug console interface added to engine.
 * LOG:
 * LOG: Revision 6.2  2002/04/23 20:48:20  mmiers
 * LOG: Add auto dispatch function for simplification.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/11/20 18:00:02  mmiers
 * LOG: Two new dispatchers
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.2  2001/06/18 20:24:46  mmiers
 * LOG: Add diff framework.  Need to implement.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
 * LOG: Rearrange this to standard form.
 * LOG:
 * LOG: Revision 1.2  2001/04/24 23:13:38  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
 * LOG: Move to a more logical location.
 * LOG:
 * LOG: Revision 1.14  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.13  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.12  2001/03/14 01:58:37  mmiers
 * LOG: Work on the implementation.  If I could get 3-4 uninterrupted
 * LOG: hours, this would be done.  TODO: the trace levels and the
 * LOG: thread pools.  The only other thing to do is the syntax tree
 * LOG: creator.
 * LOG:
 * LOG: Revision 1.11  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.10  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.9  2001/03/02 21:53:29  mmiers
 * LOG: Add management and stack objects.
 * LOG:
 * LOG: Revision 1.8  2001/03/01 23:18:02  mmiers
 * LOG: Add SS7 stack record.
 * LOG:
 * LOG: Revision 1.7  2001/03/01 22:52:10  mmiers
 * LOG: Add application class.
 * LOG:
 * LOG: Revision 1.6  2001/03/01 22:10:46  mmiers
 * LOG: Added thread pool.  Need application and serious thought on how
 * LOG: to glue it together.
 * LOG:
 * LOG: Revision 1.5  2001/03/01 02:38:35  mmiers
 * LOG: Add transport classes.  Think about doing this when
 * LOG: global start has *not* been called.
 * LOG:
 * LOG: Revision 1.4  2001/03/01 01:22:51  mmiers
 * LOG: Add trace config obj.
 * LOG:
 * LOG: Revision 1.3  2001/02/28 23:07:32  mmiers
 * LOG: No more need for CORE and CORE++, only CORE now.
 * LOG:
 * LOG: Revision 1.2  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 1.1  2001/02/28 18:14:06  mmiers
 * LOG: OK, I think I know how this is going to go.  Time to start
 * LOG: implementing.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ENGINE_INTERN_H_)
#define _ENGINE_INTERN_H_

#ident "$Id: engine_intern.h,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * private strings
 */
#define DRIVER_MAIN_STRING          "DRIVER_Main"
#define DRIVER_DIFF_STRING          "DRIVER_Diff"

#if defined(WIN32)

#define DRIVER_CPP_DEBUG_STRING     "DRIVER++D.DLL"
#define DRIVER_CPP_STRING           "DRIVER++.DLL"
#define DRIVER_C_DEBUG_STRING       "DRIVERD.DLL"
#define DRIVER_C_STRING             "DRIVER.DLL"

#else

    
#if defined(CCITT)
#define DRIVER_CPP_DEBUG_STRING     "libCCITT-DRIVER++D.so"
#define DRIVER_CPP_STRING           "libCCITT-RIVER++.so"
#define DRIVER_C_DEBUG_STRING       "libCCITT-RIVERD.so"
#define DRIVER_C_STRING             "libCCITT-RIVER.so"

#else    
    
#define DRIVER_CPP_DEBUG_STRING     "libANSI-DRIVER++D.so"
#define DRIVER_CPP_STRING           "libANSI-DRIVER++.so"
#define DRIVER_C_DEBUG_STRING       "libANSI-DRIVERD.so"
#define DRIVER_C_STRING             "libANSI-DRIVER.so"
#endif

#endif

#define XML_EXT_STRING      "xml"
#define INI_EXT_STRING      "ini"

/*
 * Parser strings
 */
#define APPL_STRING                     "Application"
#define OPTIONS_STRING                  "AppOptions"
#define WINDOWS_STRING                  "WindowsExtras"
#define FEATURE_STRING                  "Feature"
#define FEAT_OPTION_STRING              "FeatureOption"
#define TK_TRACE_STRING                 "ToolkitTrace"
#define SIP_TRACE_STRING                "SIPTrace"
#define APP_TRACE_STRING                "ApplicationTrace"
#define STACK_TRACE_STRING              "StackTrace"
#define WORK_POOL_STRING                "WorkerPool"
#define ITEM_POOL_STRING                "WorkItemPool"
#define BORDER_POOL_STRING              "BorderPool"
#define TRANSPORT_STRING                "Transport"
#define CALLBACK_STRING                 "Callbacks"
#define CUSTOM_DISP_STRING              "CustomDispatch"
#define MODIFIER_STRING                 "Modifier"
#define ROUTE_STRING                    "Route"
#define WORK_ITEM_STRING                "WorkItem"
#define VENDOR_STRING                   "Vendor"
#define STACKS_STRING                   "SS7-Stacks"
#define PEXT_STRING                     "ParserExtension"
#define LINK_SET_STRING                 "LinkSet"
#define LINK_STRING                     "Link"
#define DEST_STRING                     "Destination"
#define FAULT_TOLERANCE_STRING          "FaultTolerance"
#define PROCS_STRING                    "Procedures"
#define FT_GRPS_STRING                  "FtGroups"
#define FT_GRP_STRING                   "FtGroup"
#define DSM_CFG_STRING                  "DsmConfig"
#define FT_GRP_MBS_STRING               "FtGroupMembers"
#define FT_GRP_MB_STRING                "FtGroupMember"
#define MASTER_FT_GRP_MBS_STRING        "MasterFtGroupMembers"
#define MASTER_FT_GRP_MB_STRING         "MasterFtGroupMember"
#define FTM_PRE_EXEC_LOGIC_PROC_STRING  "FtmPreExecuteLogicProcedure"
#define FTM_LOOP_EXEC_LOGIC_PROC_STRING "FtmLoopExecuteLogicProcedure"
#define FTM_POST_EXEC_LOGIC_PROC_STRING "FtmPostExecuteLogicProcedure"
#define MB_CHANGE_ALL_FT_GRPS_CB_STRING "MembershipChangeAllFtGroupsCallback"
#define EVT_FR_ALL_FT_GRP_MBS_CB_STRING "EventFromAllFtGroupMembersCallback"
#define MB_CHANGE_CB_STRING             "MembershipChangeCallback"
#define EVT_FR_FT_GRP_MB_CB_STRING      "EventFromFtGroupMemberCallback"

#define BSSAP_STACK_STRING               "BSSAP"
#define CODEC_STACK_STRING               "Codec-Stacks"
#define CODEC_TRACE_STRING               "CodecTrace"

#define SIGTRAN_STACK_STRING             "Sigtran-Stacks"
#define SIGTRAN_TRACE_STRING             "SigtranTrace"
#define SCTP_STACK_STRING                "SCTP"
#define UAL_STACK_STRING                 "UAL"
#define M3UA_STACK_STRING                "M3UA"
#define M2UA_STACK_STRING                "M2UA"

/* For Vendor Traces */
#define VENDORS_STRING                  "Vendors"
#define VENDOR_TRACE_STRING             "VendorTrace"
#define ADAX_MTP2_STRING                "ADAX-MTP2"
#define NMS_MTP2_STRING                 "NMS-MTP2"

#define ADAX_INI_SECTION_NAME           "ADAX-TRACE"
#define NMS_INI_SECTION_NAME            "NMS-TRACE"


/*
 * attributes
 */
#define PRIMARY_STRING      "primary"
#define NAME_STRING         "name"
#define TYPE_STRING         "type"
#define STYLE_STRING        "style"
#define VALUE_STRING        "value"
#define VARIANT_STRING      "variant"
#define GS_STRING           "globalStart"
#define BINDING_STRING      "binding"
#define SERVICE_STRING      "service"
#define LIBRARY_STRING      "library"
#define SS7_SELECT_STRING   "ss7Selector"
#define APP_SELECT_STRING   "appSelector"
#define APP_DESELECT_STRING "appDeselector"
#define HMI_CB_STRING       "hmiCallback"
#define ALARM_CB_STRING     "alarmCallback"
#define PRE_FUNC_STRING     "preFunc"
#define POST_FUNC_STRING    "postFunc"

#define CDISP_STRING        "dispatch"
#define NET_HOME_STRING     "NetworkHome"
#define INTERFACE_STRING    "interface"
#define MASK_STRING         "mask"
#define BROADCAST_STRING    "broadcast"
#define CLASS_REC_STRING    "classRec"
#define VENDOR_REC_STRING   "vendorRec"
#define CRIT_STRING         "Critical"
#define ERR_STRING          "Error"
#define WARN_STRING         "Warning"
#define DBG_STRING          "Debug"
#define EVENT_STRING        "Event"
#define OUTPUT_STRING       "output"
#define MOD_DATA_STRING     "DATA"
#define MOD_GDI_STRING      "GDI"
#define MOD_RUDP_STRING     "RUDP"
#define MOD_TALI_STRING     "TALI"
#define MOD_IMAL_STRING     "IMAL"
#define MOD_SCTP_STRING     "SCTP"
#define MOD_MTP2_STRING     "MTP2"
#define MOD_MTP3_STRING     "MTP3"
#define MOD_SCCP_STRING     "SCCP"
#define MOD_ISUP_STRING     "ISUP"
#define MOD_TCAP_STRING     "TCAP"
#define T_SS7_STRING        "SS7"
#define T_FIFO_STRING       "FIFO"
#define T_GFIFO_STRING      "GatedFIFO"
#define T_CSOCK_STRING      "ClientSocket"
#define T_SSOCK_STRING      "ServerSocket"
#define T_ISOCK_STRING      "IterativeServerSocket"
#define T_DSOCK_STRING      "Datagram"
#define T_VIRT_STRING       "Virtual"
#define T_TQ_STRING         "TaskQueue"
#define COUNT_STRING        "count"
#define NUM_WORKERS_STRING  "NumWorkers"
#define STACK_SIZE_STRING   "stackSize"
#define BLOCK_STRING        "blocking"
#define NBLOCK_STRING       "non-blocking"
#define TYPE_DBC_STRING     "debug-console"
#define REPEAT_STRING       "repeatable"
#define NREPEAT_STRING      "non-repeatable"
#define ITU_STRING          "ITU"
#define ANSI_STRING         "ANSI"
#define CHINA_STRING        "CHINA"
#define JAPAN_STRING        "JAPAN"
#define PRE_INIT_STRING     "preInitialize"
#define POST_INIT_STRING    "postInitialize"
#define PRE_NEXT_STRING     "preNextEvent"
#define NEXT_FAIL_STRING    "nextEventFailed"
#define POST_NEXT_STRING    "postNextEvent"
#define UDISP_STRING        "userMsgHandler"
#define IDISP_STRING        "ISUPMsgHandler"
#define SDISP_STRING        "SCCPMsgHandler"
#define WDISP_STRING        "userDelegate"
#define PRE_ACCEPT_STRING   "preAccept"
#define ON_ACCEPT_STRING    "onAccept"
#define PRE_TERM_STRING     "preTerminate"
#define POST_TERM_STRING    "postTerminate"
#define STREAM_DATA_STRING  "StreamData"
#define FIFO_DATA_STRING    "FIFOData"
#define DGRAM_DATA_STRING   "DatagramData"
#define ASSOCIATE_STRING    "Associate"
#define OTHER_HOME_STRING   "OtherHome"
#define MGMT_CBS_STRING     "ManagementCallbacks"
#define MGMT_A_MTP3_STRING  "MTP3ManagementCallbackANSI"
#define MGMT_A_ISUP_STRING  "ISUPManagementCallbackANSI"
#define MGMT_A_SCCP_STRING  "SCCPManagementCallbackANSI"
#define MGMT_A_GTT_STRING   "SCCPGlobalTitleCallbackANSI"
#define MGMT_A_RC_STRING    "SCCPSSNRoutingCallbackANSI"
#define MGMT_I_MTP3_STRING  "MTP3ManagementCallbackITU"
#define MGMT_I_ISUP_STRING  "ISUPManagementCallbackITU"
#define MGMT_I_SCCP_STRING  "SCCPManagementCallbackITU"
#define MGMT_I_GTT_STRING   "SCCPGlobalTitleCallbackITU"
#define MGMT_I_RC_STRING    "SCCPSSNRoutingCallbackITU"
#define INTELLINET_STRING   "IntelliNet"
#define ITU_MTP3_STRING     "ITU-MTP3"
#define ITU_MTP2_STRING     "ITU-MTP2"
#define ITU_ISUP_STRING     "ITU-ISUP"
#define ITU_SCCP_STRING     "ITU-SCCP"
#define ITU_TCAP_STRING     "ITU-TCAP"
#define ANSI_MTP3_STRING    "ANSI-MTP3"
#define ANSI_MTP2_STRING    "ANSI-MTP2"
#define ANSI_ISUP_STRING    "ANSI-ISUP"
#define ANSI_SCCP_STRING    "ANSI-SCCP"
#define ANSI_TCAP_STRING    "ANSI-TCAP"
#define TIMERS_STRING       "Timers"
#define BEHAVIOR_STRING     "BehaviorControl"
#define NULL_STRING         "null"
#define ELEM_NAME_STRING    "elementName"
#define START_FUNC_STRING   "startFunc"
#define STOP_FUNC_STRING    "stopFunc"
#define XLATE_FUNC_STRING   "xlateFunc"
#define DIFF_FUNC_STRING    "diffFunc"
#define COMMIT_FUNC_STRING  "commitFunc"
#define NUM_THREADS_STRING  "numThreads"
#define ID_STRING           "id"
#define PC_STRING           "pointCode"
#define ENI_STRING          "networkInd"
#define ISUP_ATTR_STRING    "ISUPAttributes"
#define LPC_STRING          "localPointCode"
#define TIMER_STRING        "Timer"
#define HANDLED_BY_STRING   "handledBy"
#define CIRC_CODE_STRING    "CircuitCodes"
#define START_STRING        "start"
#define CIRC_GRP_STRING     "CircuitGroup"
#define HUNT_RULE_STRING    "huntRule"
#define INSTANCE_STRING     "instance"
#define ISUP_XCHANGE_TYPE_STR   "exchangeType"
#define ISUP_SEG_SUPPORT_STR    "segmentationSupported"
#define SIP_ATTR_STRING      "SIPAttributes"
#define SIP_IPADDR_STRING    "ipAddr"
#define SIP_UDPPORTNO_STRING "UDPPortNo"
#define SIP_TCPPORTNO_STRING "TCPPortNo"
#define SIP_TIMERS_STRING    "sipTimer"

/*
 * M2UA Attributes
 */
#define M2UA_IID_MAP_STRING         "IID-MAP"
#define M2UA_LINK_SET_STRING        "linkSet"
#define M2UA_LINK_CODE_STRING       "linkCode"
#define M2UA_IID_STRING             "IID"
#define M2UA_ASSO_NAME_STRING       "assoName"

#define IID_INFO_STRING             "interfaceInfo"
#define IID_BEGIN_STRING            "begin"
#define IID_END_STRING              "end"


#define MAX_NUM_FT_GRPS_STRING      "maxNumFtGroups"
#define MAX_NUM_PROCS_STRING        "maxNumProcesses"
#define MAX_NUM_NODES_STRING        "maxNumNodes"
#define NODE_ID_STRING              "nodeId"
#define PROC_ID_STRING              "processId"
#define FUNCTION_STRING             "function"
#define DSM_SIZE_STRING             "dsmSize"
#define DSM_BASE_ADDR_STRING        "dsmBaseAddress"
#define DSM_MAX_NUM_TBLS_STRING     "dsmMaxNumTables"
#define DSM_TYPE_STRING             "dsmType"
#define NODE_NAME_STRING            "nodeName"
#define PROC_NAME_STRING            "processName"
#define FT_GRP_ID_STRING            "ftGroupId"
#define FT_GRP_NAME_STRING          "ftGroupName"
#define TCAP_FT_GRP_ID_STRING       "tcapFtGroupId"
#define SCCP_FT_GRP_ID_STRING       "sccpFtGroupId"
#define MTP3_FT_GRP_ID_STRING       "mtp3FtGroupId"
#define ISUP_FT_GRP_ID_STRING       "isupFtGroupId"
#define ROUTING_FT_GRP_ID_STRING    "routingFtGroupId"
#define TIMERS_FT_GRP_ID_STRING     "timersFtGroupId"
#define MGMT_DATA_FT_GRP_ID_STRING  "mgmtDataFtGroupId"  

/*
 * shared strings
 */
#define DISP_SS7_CCITT_CPP_STRING   "DISP_Dispatch_SS7_CCITT_CPP"
#define DISP_SS7_ANSI_CPP_STRING    "DISP_Dispatch_SS7_ANSI_CPP"
#define DISP_SS7_PRC_CPP_STRING     "DISP_Dispatch_SS7_PRC_CPP"
#define DISP_SS7_TTC_CPP_STRING     "DISP_Dispatch_SS7_TTC_CPP"
#define DISP_CCITT_CPP_STRING       "DISP_Dispatch_CCITT_CPP"
#define DISP_ANSI_CPP_STRING        "DISP_Dispatch_ANSI_CPP"
#define DISP_PRC_CPP_STRING         "DISP_Dispatch_PRC_CPP"
#define DISP_TTC_CPP_STRING         "DISP_Dispatch_TTC_CPP"
#define DISP_USER_CPP_STRING        "DISP_Dispatch_USER_CPP"
#define DISP_ITERATIVE_CPP_STRING   "DISP_Dispatch_ITERATIVE_CPP" 
#define DISP_DBC_CPP_STRING         "DISP_Dispatch_DBC_CPP" 
#define DISP_SS7_CCITT_STRING       "DISP_Dispatch_SS7_CCITT"
#define DISP_SS7_ANSI_STRING        "DISP_Dispatch_SS7_ANSI"
#define DISP_SS7_PRC_STRING         "DISP_Dispatch_SS7_PRC"
#define DISP_SS7_TTC_STRING         "DISP_Dispatch_SS7_TTC"
#define DISP_CCITT_STRING           "DISP_Dispatch_CCITT"
#define DISP_ANSI_STRING            "DISP_Dispatch_ANSI"
#define DISP_PRC_STRING             "DISP_Dispatch_PRC"
#define DISP_TTC_STRING             "DISP_Dispatch_TTC"
#define DISP_USER_STRING            "DISP_Dispatch_USER"
#define DISP_ITERATIVE_STRING       "DISP_Dispatch_ITERATIVE"
#define DISP_DBC_STRING             "DISP_Dispatch_DBC"

#define DISP_WORK_ITEM_STRING       "DISP_Dispatch_WORK_ITEM";

#define DEFAULT_SHM_SIZE            (64 * 1024 * 1024)

/*
 * engine main.
 */
typedef int (*DRIVER_MainFunc)(int argc, const char **argv);
typedef int (*DRIVER_DiffFunc)(ENGINE_Application,
                               ENGINE_Application);

ITSDLLAPI int           DRIVER_Main(int argc, const char **argv);
ITSDLLAPI int           DRIVER_Diff(ENGINE_Application oldTree,
                                    ENGINE_Application newTree);
ITSDLLAPI ITS_USHORT    DRIVER_AppSelector(ITS_HDR* hdr,
                                           ITS_EVENT* ev);
ITSDLLAPI void          DRIVER_HandleHMI(ITS_POINTER obj,
                                         ITS_POINTER userData,
                                         ITS_POINTER callData);

#if defined(__cplusplus)
}
#endif

#endif /* _ENGINE_INTERN_H_ */

