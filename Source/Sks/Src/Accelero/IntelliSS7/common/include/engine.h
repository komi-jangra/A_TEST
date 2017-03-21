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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2.4.1  2005/08/29 09:23:25  adutta
 * LOG: BSSAP configuration
 * LOG:
 * LOG: Revision 9.2  2005/05/06 09:09:19  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:50:43  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2.6.1.6.5  2005/01/19 11:10:04  adutta
 * LOG: Retreiving m2ua data from xml
 * LOG:
 * LOG: Revision 7.4.2.2.6.1.6.4  2005/01/17 09:56:12  mkrishna
 * LOG: separate traces for SIP
 * LOG:
 * LOG: Revision 7.4.2.2.6.1.6.3  2005/01/03 14:37:47  snagesh
 * LOG: Modifications for MTP2 vendor traces
 * LOG:
 * LOG: Revision 7.4.2.2.6.1.6.2  2004/12/28 13:14:45  mkrishna
 * LOG: SIP code propagated from Current Branch
 * LOG:
 * LOG: Revision 7.4.2.2.6.1.6.1  2004/12/15 12:33:18  asingh
 * LOG: separate traces for SCTP/UAL/M3UA
 * LOG:
 * LOG: Revision 7.4.2.2.6.1  2004/09/15 05:29:34  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/05/07 08:45:04  ssingh
 * LOG: Removed r7.4.2.1 changes.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/05/07 08:21:34  ssingh
 * LOG: ISUP related changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 7.4  2002/12/31 09:13:31  ssingh
 * LOG: Added New MACROs while introducing two new variables viz exchange_type
 * LOG: and segmentation_supported
 * LOG:
 * LOG: Revision 7.3  2002/11/09 21:16:26  randresol
 * LOG: Add definitions for Route Reader/Writer lock in DSM
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:46:19  mmiers
 * LOG: Add the deselector to the DTD
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.13  2002/07/02 21:26:20  mmiers
 * LOG: Work on getting debug console interface included in engine.
 * LOG:
 * LOG: Revision 6.12  2002/06/21 22:49:10  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.11  2002/05/08 20:23:56  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.10  2002/05/06 21:15:31  hdivoux
 * LOG: Cleanup after FT/HA integration.
 * LOG:
 * LOG: Revision 6.9  2002/04/30 15:32:05  hdivoux
 * LOG: Removed <<<<<.
 * LOG:
 * LOG: Revision 6.8  2002/04/29 21:29:35  randresol
 * LOG: Add isInterNode flag in border transport specifications
 * LOG:
 * LOG: Revision 6.7  2002/04/16 21:20:30  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.6  2002/04/15 21:04:25  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 6.5  2002/04/09 22:45:19  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.4  2002/04/08 21:51:54  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/04/18 19:24:39  randresol
 * LOG: Add changes for redundant MTP3
 * LOG:
 * LOG: Revision 6.3  2002/04/04 23:38:55  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.2  2002/03/12 16:50:24  mmiers
 * LOG: Add user data.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:04  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.15  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.14  2002/01/30 16:09:59  mmiers
 * LOG: Add termination function.
 * LOG:
 * LOG: Revision 5.13  2002/01/21 20:25:43  mmiers
 * LOG: Add distribution awareness.
 * LOG:
 * LOG: Revision 5.12  2002/01/10 20:30:36  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.11  2001/11/20 18:17:06  mmiers
 * LOG: Hook the debug console into the engine.
 * LOG:
 * LOG: Revision 5.10  2001/10/19 22:45:12  mmiers
 * LOG: Use strings for variant names.
 * LOG:
 * LOG: Revision 5.9  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.8  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.7  2001/09/24 21:37:37  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.6  2001/09/21 16:22:44  hdivoux
 * LOG: Update for comments and const parameters.
 * LOG:
 * LOG: Revision 5.5  2001/09/20 19:17:21  hdivoux
 * LOG: Update for XML GCS configuration attributes.
 * LOG:
 * LOG: Revision 5.4  2001/08/24 17:10:25  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 23:28:54  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 22:51:15  mmiers
 * LOG: Get this in line with new routing scheme
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.17  2001/08/13 20:42:10  mmiers
 * LOG: Add routing key.
 * LOG:
 * LOG: Revision 4.16  2001/07/26 19:04:14  mmiers
 * LOG: Add engine thread pool type for pattern matcher.
 * LOG:
 * LOG: Revision 4.15  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.14  2001/07/23 22:17:13  mmiers
 * LOG: Finish the equality checks.  Finish up diff tomorrow.
 * LOG:
 * LOG: Revision 4.13  2001/07/19 15:36:53  mmiers
 * LOG: This mornging's bug flurry.
 * LOG:
 * LOG: Revision 4.12  2001/07/05 22:48:00  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.11  2001/07/03 21:16:22  mmiers
 * LOG: Move RM and DSM.
 * LOG:
 * LOG: Revision 4.10  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.9  2001/06/22 18:34:10  mmiers
 * LOG: Add RM.
 * LOG:
 * LOG: Revision 4.8  2001/06/21 15:18:37  mmiers
 * LOG: Add HMI and Alarm.
 * LOG:
 * LOG: Revision 4.7  2001/06/18 20:25:01  mmiers
 * LOG: Add diff framework.
 * LOG:
 * LOG: Revision 4.6  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.5  2001/06/15 00:21:43  mmiers
 * LOG: Add class for engine worker.
 * LOG:
 * LOG: Revision 4.4  2001/05/10 16:41:12  mmiers
 * LOG: The rest of the requests.
 * LOG:
 * LOG: Revision 4.3  2001/05/09 23:59:11  mmiers
 * LOG: Add signature for pre/post func.
 * LOG:
 * LOG: Revision 4.2  2001/05/09 23:20:17  mmiers
 * LOG: Name change by request.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.33  2001/04/29 00:10:15  mmiers
 * LOG: Correct the sample XML.
 * LOG:
 * LOG: Revision 1.32  2001/04/25 23:17:04  mmiers
 * LOG: Don't need to expose eventLog; it's available from the service
 * LOG: API.
 * LOG:
 * LOG: Revision 1.31  2001/04/18 20:33:29  mmiers
 * LOG: Add macro and field.  Update comments.
 * LOG:
 * LOG: Revision 1.30  2001/04/06 17:48:58  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 1.29  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 * LOG: Revision 1.28  2001/04/03 23:56:22  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.27  2001/04/03 17:45:41  mmiers
 * LOG: Fix some major engine bugs.
 * LOG:
 * LOG: Revision 1.26  2001/04/02 19:50:14  mmiers
 * LOG: Solaris build.
 * LOG:
 * LOG: Revision 1.25  2001/03/28 22:38:28  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 1.24  2001/03/28 00:44:26  mmiers
 * LOG: Finish management.
 * LOG:
 * LOG: Revision 1.23  2001/03/28 00:18:15  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 1.22  2001/03/27 01:58:40  mmiers
 * LOG: Add options, sanitize the XML.  Need to do features and windows.
 * LOG:
 * LOG: Revision 1.21  2001/03/26 23:02:15  mmiers
 * LOG: Today's installment.  Now that I'm caught up on email, I should
 * LOG: be able to finish the parser tomorrow.
 * LOG:
 * LOG: Revision 1.20  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.19  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 1.18  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.17  2001/03/15 01:27:10  mmiers
 * LOG: Updates for portability (fsm).  I think these were required anyway,
 * LOG: but VC doesn't complain if they aren't there.  The rest is thinking
 * LOG: about the thread pools.  I think I have a handle on this if I can
 * LOG: remember it tomorrow.  The comments should help.
 * LOG:
 * LOG: Revision 1.16  2001/03/14 23:44:01  mmiers
 * LOG: Build the pools and parsing is all that's left.
 * LOG:
 * LOG: Revision 1.15  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.14  2001/03/14 01:58:37  mmiers
 * LOG: Work on the implementation.  If I could get 3-4 uninterrupted
 * LOG: hours, this would be done.  TODO: the trace levels and the
 * LOG: thread pools.  The only other thing to do is the syntax tree
 * LOG: creator.
 * LOG:
 * LOG: Revision 1.13  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.12  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 1.11  2001/03/09 23:51:08  mmiers
 * LOG: Convert the sublayers.  Decide what info engine needs per transport.
 * LOG:
 * LOG: Revision 1.10  2001/03/09 22:55:41  mmiers
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
 * LOG: Revision 1.5  2001/03/01 17:18:57  mmiers
 * LOG: Revamp for engine.  Really just adding more callbacks.
 * LOG:
 * LOG: Revision 1.4  2001/02/28 23:07:32  mmiers
 * LOG: No more need for CORE and CORE++, only CORE now.
 * LOG:
 * LOG: Revision 1.3  2001/02/28 21:58:59  mmiers
 * LOG: Some classes done.
 * LOG:
 * LOG: Revision 1.2  2001/02/28 18:14:06  mmiers
 * LOG: OK, I think I know how this is going to go.  Time to start
 * LOG: implementing.
 * LOG:
 * LOG: Revision 1.1  2001/02/28 17:28:03  mmiers
 * LOG: Start the engine core.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_ENGINE_H_)
#define _ENGINE_H_

#include <its.h>

#ident "$Id: engine.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#include <its_mutex.h>
#include <its_semaphore.h>
#include <its_condvar.h>
#include <its_rwlock.h>
#include <its_alarm.h>
#include <its_hmi.h>
#include <its_assertion.h>
#include <its_callback.h>
#include <its_list.h>
#include <its_mlist.h>
#include <its_emlist.h>
#include <its_factory.h>
#include <its_hash.h>
#include <its_lockable.h>
#include <its_service.h>
#include <its_object.h>
#include <its_transports.h>
#include <its_dlsym.h>
#include <its_route.h>
#include <its_fifo_trans.h>
#include <its_gfifo_trans.h>
#include <its_ip_trans.h>
#include <its_imal_trans.h>
#include <its_tali_trans.h>
#include <its_gdi_trans.h>
#include <its_sctp_trans.h>
#include <its_ss7_trans.h>
#include <its_tq_trans.h>
#include <its_thread_pool.h>
#include <its_gen_disp.h>
#include <its_app.h>
#include <its_trace.h>
#include <its_event_log.h>
#include <its_timers.h>
#include <its_worker.h>
#include <its_work_item.h>
#include <its_work_item_pool.h>
#include <its_dsm.h>
#include <its_ftm.h>
#include <its_route_rwlock.h>

#if defined(USE_CPLUSPLUS)
#include <its_singleton.h>
#include <its_exception.h>
#include <its_exception_log.h>
#include <its_fsm.h>
#endif

#include <dbc_serv.h>

/*.interface:ENGINE_
 *****************************************************************************
 *  Interface:
 *      ENGINE_Initialize(), ENGINE_Run()
 *
 *  Purpose:
 *      Ultimately to hide the flexibility and complexity of the toolkit as
 *      much as possible from the user.
 *
 *  Usage:
 *
 *      Sample XML configuration file:
 *
 *  <?xml version="1.0"?>
 * 
 *  <!DOCTYPE Application SYSTEM "file:/home/mmiers/dtd/engine.dtd">
 * 
 *  <!-- Sample XML file for application configuration (INI). -->
 * 
 *  <Application name           = "Gateway"
 *               type           = "console-application"
 *               globalStart    = "ITU-TCAP"
 *               binding        = "CPP"
 *               library        = "libCISCO.so"
 *               ss7Selector    = "RouteSS7"
 *               appSelector    = "RouteAPP">
 * 
 *      <Options
 *          traceFlushAfterWrite         = "yes"
 *          routeUniqueLinkCodesRequired = "yes"
 *          memPoolChecksOn              = "no"
 *      />
 *
 *      <ParserExtension
 *          library         = "libDSM-GCSD.so"
 *          elementName     = "DsmGcsConfig"
 *          startFunc       = "DSM_GCS_ConfigParseStart"
 *          stopFunc        = "DSM_GCS_ConfigParseStop"
 *          xlateFunc       = "DSM_GCS_ConfigConvertParserData"
 *          diffFunc        = "DSM_GCS_ConfigDiff"
 *      />
 *                                          
 *      <FaultTolerance
 *          maxNumFtGroups      = "8"
 *          maxNumProcesses     = "6"
 *          maxNumNodes         = "4"
 *          nodeId              = "1"
 *          processId           = "5"
 *          tcapFtGroupId       = "0"
 *          sccpFtGroupId       = "0"
 *          mtp3FtGroupId       = "0"
 *          isupFtGroupId       = "0"
 *          routingFtGroupId    = "0"
 *          timersFtGroupId     = "0"
 *          mgmtDataFtGroupId   = "0"
 *      >
 *
 *          <Procedures>
 *
 *          </Procedures>
 *
 *          <Callbacks>
 *
 *          </Callbacks>
 *
 *          <FtGroups>
 *
 *              <FtGroup 
 *                  ftGroupId      = "0"
 *                  ftGroupName    = "FtGroup0"
 *              >
 *
 *                  <DsmConfig
 *                      dsmSize         = "20971520"
 *                      dsmBaseAddress  = "0x80000000"
 *                      dsmMaxNumTables = "256"
 *                      dsmType         = "GCS"
 *                  />
 *
 *                  <DsmGcsConfig
 *                      gcsFtGroupId        = "0"
 *                      gcsDaemonName       = "8991"
 *                      gcsSyncMemUseTcp    = "1"
 *                      gcsSyncMemIpAddress = "192.168.2.20"
 *                      gcsSyncMemIpPort    = "8992"
 *                  />
 *
 *                  <!-- Note: MUST include itself. -->
 *
 *                  <FtGroupMembers>
 *
 *                      <FtGroupMember
 *                          nodeId      = "1"
 *                          nodeName    = "Node1"
 *                          processId   = "5"
 *                          processName = "Node1Process5"
 *                      />
 *
 *                      <FtGroupMember
 *                          nodeId      = "2"
 *                          nodeName    = "Node2"
 *                          processId   = "5"
 *                          processName = "Node2Process5"
 *                      />
 *
 *                  </FtGroupMembers>
 *
 *
 *                  <!-- Note: MUST NOT include itself. -->
 *
 *                  <MasterFtGroupMembers>
 *
 *                      <MasterFtGroupMember
 *                          nodeId    = "2"
 *                          processId = "5"
 *                      />
 *
 *                  </MasterFtGroupMembers>
 *
 *                  <Callbacks>
 *              
 *                  </Callbacks>
 *
 *              </FtGroup>
 *
 *          </FtGroups>
 *
 *      </FaultTolerance>
 * 
 *      <WindowsExtras>
 *          <NetworkHome
 *              localInterface  = "192.168.1.1"
 *              localMask       = "255.255.0.0"
 *              localBroadcast  = "192.168.255.255"
 *          />
 *      </WindowsExtras>
 * 
 *      <Feature
 *          name        = "IntelliNet stack"
 *          library     = "libENGINED.so"
 *          classRec    = "itsINTELLISS7_Class"
 *      />
 * 
 *      <Feature
 *          name        = "Keepalive manager"
 *          library     = "libENGINED.so"
 *          classRec    = "itsKEEPALIVE_Class"
 *      />
 * 
 *      <Feature
 *          name        = "SCTP"
 *          library     = "libSCTP.so"
 *          classRec    = "itsSCTP_Class"
 *      />
 * 
 *      <Feature
 *          name        = "CCITT-SUA"
 *          library     = "libCCITT-SUA.so"
 *          classRec    = "itsSUA_CCITT_Class"
 *      />
 * 
 *      <Feature
 *          name                = "UAL"
 *          library             = "libCCITT-UAL.so"
 *          classRec            = "itsUAL_Class">
 * 
 *          <FeatureOption name = "ualAckTimer"     value = "3"/>
 *          <FeatureOption name = "ualPendingTimer" value = "3"/>
 *          <FeatureOption name = "ualTrafficMode"  value = "InterworkingMode"/>
 * 
 *      </Feature>
 * 
 *      <Feature
 *          name                = "GDI"
 *          library             = "libCCITT-GDI.so"
 *          classRec            = "itsGDI_Class">
 * 
 *          <FeatureOption name = "gdiKeepAliveTimer"  value = "20"/>
 *          <FeatureOption name = "gdiTraceKeepAlives" value = "yes"/>
 *          <FeatureOption name = "gdiTracePayload"    value = "yes"/>
 * 
 *      </Feature>
 * 
 *      <Feature
 *          name                = "IMAL"
 *          library             = "libCCITT-IMAL.so"
 *          classRec            = "itsIMAL_Class">
 * 
 *          <FeatureOption name = "imalTraceKeepAlives" value = "yes"/>
 *          <FeatureOption name = "imalTracePayload"    value = "yes"/>
 * 
 *      </Feature>
 * 
 *      <Feature
 *          name                = "TALI"
 *          library             = "libCCITT-TALI.so"
 *          classRec            = "itsTALI_Class">
 * 
 *          <FeatureOption name = "taliTraceKeepAlives" value = "yes"/>
 *          <FeatureOption name = "talitracePayload"    value = "yes"/>
 *          <FeatureOption name = "taliT1"              value = "2"/>
 *          <FeatureOption name = "taliT2"              value = "2"/>
 *          <FeatureOption name = "taliT3"              value = "5"/>
 * 
 *      </Feature>
 * 
 *      <ToolkitTrace>
 *          <Critical  output = "stdout"/>
 *          <Critical  output = "file"/>
 *          <Error     output = "stdout"/>
 *          <Error     output = "file"/>
 *          <Warning   output = "stdout"/>
 *          <Warning   output = "file"/>
 *          <Debug     output = "file"/>
 *      </ToolkitTrace>
 * 
 *      <ApplicationTrace>
 *          <Critical  output = "file"/>
 *          <Error     output = "file"/>
 *          <Warning   output = "file"/>
 *          <Debug     output = "file"/>
 *      </ApplicationTrace>
 * 
 *      <!--///////////////////////////////////////////////////////////////-->
 * 
 *      <WorkerPool stackSize = "0">
 * 
 *          <Transport  type = "TaskQueue">
 *              <Callbacks
 *                  type           = "blocking"
 *                  library        = "libCISCO.so"
 *                  userDispatch   = "CISCOMain"
 *              />
 * 
 *              <!-- possibly -->
 * 
 *              <Route>
 *              </Route>
 *          </Transport>
 * 
 *              <!-- and repeat for all unique transports -->
 *              <!-- for example, "protocol engine" threads like what -->
 *              <!-- we needed for the switch control protocol in the MSC -->
 * 
 *              <!-- or, for true worker (anonymous threads) -->
 * 
 *          <Transport  type    = "TaskQueue"
 *                      count   = "5">
 *              <Callbacks
 *                  type            = "blocking"
 *                  library         = "libCISCO.so"
 *                  userDispatch    = "GenericMain"
 *              />
 *          </Transport>
 * 
 *              <!-- or, a CISCO type solution -->
 * 
 *          <Transport  type    = "TaskQueue">
 *              <Callbacks
 *                  type            = "non-blocking"
 *                  library         = "libCISCO.so"
 *                  userDispatch    = "CISCOMain"
 *              />
 *          </Transport>
 * 
 *      </WorkerPool>
 * 
 *      <!-- AND/OR -->
 * 
 *      <WorkItemPool stackSize = "0">
 * 
 *          <NumWorkers value = "5"/>
 * 
 *          <WorkItem
 *              type            = "repeatable"
 *              library         = "libCISCO.so"
 *              userDispatch    = "CISCOMain"
 *              count           = "50"
 *          />
 * 
 *      </WorkItemPool>
 * 
 *      <!--///////////////////////////////////////////////////////////////-->
 * 
 *      <BorderPool stackSize = "0">
 * 
 *          <Transport  name    = "NMS SS7"
 *                      type    = "SS7"
 *                      family  = "ITU">
 *                     
 *              <Modifier value = "MTP3"/>
 * 
 *              <Vendor name        = "NMS"
 *                      library     = "libCISCO.so"
 *                      vendorRec   = "itsNMS_Class"
 *              />
 * 
 *              <Callbacks
 *                  library         = "libCISCO.so"
 *                  type            = "blocking"
 *                  preInitialize   = "null"
 *                  postInitialize  = "null"
 *                  preNextEvent    = "null"
 *                  nextEventFailed = "null"
 *                  postNextEvent   = "FilterCacheMsgs"
 *                  userDispatch    = "null"
 *                  SCCPDispatch    = "null"
 *                  ISUPDispatch    = "null"
 *                  preTerminate    = "null"
 *                  postTerminate   = "null"
 *              />
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio">
 *                  <DPC        value = "0xFFFFFF"/>
 *                  <SIO        value = "3"/>
 *                  <LinkSet    value = "1"/>
 *                  <LinkCode   value = "1"/>
 *              </Route>
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "InterV7M-1"
 *                      type    = "ServerSocket"
 *                      family  = "ITU">
 *                     
 *              <Modifier value = "IMAL"/>
 *              <Modifier value = "MTP3"/>
 * 
 *              <StreamData socketDomain    = "INET"
 *                          serverHostName  = "127.0.0.1"
 *                          serverPort      = "6666"
 *              />
 * 
 *              <IMAL   imalLocalPC             = "0x01"
 *                      imalAdjacentPC          = "0x02"
 *                      imalKeepAliveTimeOut    = "30"/>
 * 
 *              <Callbacks
 *                  library         = "libCISCO.so"
 *                  type            = "blocking"
 *                  preInitialize   = "null"
 *                  postInitialize  = "null"
 *                  preNextEvent    = "null"
 *                  nextEventFailed = "null"
 *                  postNextEvent   = "FilterCacheMsgs"
 *                  userDispatch    = "null"
 *                  SCCPDispatch    = "null"
 *                  ISUPDispatch    = "null"
 *                  preTerminate    = "null"
 *                  postTerminate   = "null"
 *              />
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC            value = "0x123456"/>
 *                  <SIO            value = "3"/>
 *                  <SSN            value = "5"/>
 *                  <LinkSet        value = "1"/>
 *                  <LinkCode       value = "1"/>
 *              </Route>
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC            value = "0x123456"/>
 *                  <SIO            value = "3"/>
 *                  <SSN            value = "6"/>
 *                  <LinkSet        value = "1"/>
 *                  <LinkCode       value = "1"/>
 *              </Route>
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "InterV7M-2"
 *                      type    = "ClientSocket"
 *                      family  = "ITU">
 * 
 *              <Modifier value = "IMAL"/>
 *              <Modifier value = "MTP3"/>
 * 
 *              <StreamData socketDomain    = "INET"
 *                          serverHostName  = "127.0.0.1"
 *                          serverPort      = "6667"
 *              />
 * 
 *              <IMAL   imalLocalPC             = "0x01"
 *                      imalAdjacentPC          = "0x02"
 *                      imalKeepAliveTimeOut    = "30"/>
 * 
 *              <Callbacks
 *                  library         = "libCISCO.so"
 *                  type            = "blocking"
 *                  preInitialize   = "null"
 *                  postInitialize  = "null"
 *                  preNextEvent    = "null"
 *                  nextEventFailed = "null"
 *                  postNextEvent   = "FilterCacheMsgs"
 *                  userDispatch    = "null"
 *                  SCCPDispatch    = "null"
 *                  ISUPDispatch    = "null"
 *                  preTerminate    = "null"
 *                  postTerminate   = "null"
 *              />
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC        value = "0x123456"/>
 *                  <SIO        value = "3"/>
 *                  <SSN        value = "5"/>
 *                  <LinkSet    value = "1"/>
 *                  <LinkCode   value = "1"/>
 *              </Route>
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC        value = "0x123456"/>
 *                  <SIO        value = "3"/>
 *                  <SSN        value = "6"/>
 *                  <LinkSet    value = "1"/>
 *                  <LinkCode   value = "1"/>
 *              </Route>
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "VB Acceptor"
 *                      type    = "IterativeServerSocket"
 *                      count   = "25"
 *                      family  = "ITU">
 * 
 *              <Modifier value = "IMAL"/>
 *              <Modifier value = "MTP3"/>
 * 
 *              <StreamData socketDomain    = "INET"
 *                          serverHostName  = "127.0.0.1"
 *                          serverPort      = "6668"
 *              />
 * 
 *              <IMAL   imalLocalPC             = "0x01"
 *                      imalAdjacentPC          = "0x02"
 *                      imalKeepAliveTimeOut    = "30"/>
 * 
 *              <Callbacks
 *                  library         = "libCISCO.so"
 *                  type            = "blocking"
 *                  preInitialize   = "null"
 *                  postInitialize  = "GetConfigDir"
 *                  preNextEvent    = "null"
 *                  nextEventFailed = "null"
 *                  postNextEvent   = "FilterUserMsgs"
 *                  userDispatch    = "null"
 *                  SCCPDispatch    = "null"
 *                  ISUPDispatch    = "null"
 *                  onAccept        = "AcceptOne"
 *                  preTerminate    = "null"
 *                  postTerminate   = "null"
 *              />
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "Test SCTP"
 *                      type    = "Datagram"
 *                      family  = "ITU">
 * 
 *              <Modifier value = "MTP3"/>
 *              <Modifier value = "SCTP"/>
 * 
 *              <DatagramData   localHostName   = "127.0.0.1"
 *                              localPort       = "6668">
 *                  <Associate value    = "ASP 1"/>
 *                  <Associate value    = "ASP 2"/>
 *              </DatagramData>
 * 
 *              <SCTP   maxInStreams    = "32"
 *                      numOutStreams   = "32"
 *                      maxAttempts     = "5"
 *                      cookieLife      = "30"
 *                      hbOn            = "yes"
 *                      initTimeOut     = "5,0"
 *                      sendTimeOut     = "5,0"
 *                      recvTimeOut     = "0,300"
 *                      hbTimeOut       = "30,0"
 *                      shutdownTimeOut = "5,0"
 *                      pmtuTimeOut     = "600,0"
 *                      isClient        = "no"
 *                      payloadType     = "CCITT-SUA">
 *                  <OtherHome  localHostName = "192.168.1.1"/>
 *              </SCTP>
 * 
 *              <Callbacks
 *                  library         = "libCISCO.so"
 *                  type            = "blocking"
 *                  preInitialize   = "null"
 *                  postInitialize  = "GetConfigDir"
 *                  preNextEvent    = "null"
 *                  nextEventFailed = "null"
 *                  postNextEvent   = "FilterUserMsgs"
 *                  userDispatch    = "null"
 *                  SCCPDispatch    = "null"
 *                  ISUPDispatch    = "null"
 *                  onAccept        = "null"
 *                  preTerminate    = "null"
 *                  postTerminate   = "null"
 *              />
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "ASP 1"
 *                      type    = "Virtual"
 *                      family  = "ITU">
 * 
 *              <DatagramData   socketDomain    = "INET"
 *                              serverHostName  = "192.168.1.13"
 *                              serverPort      = "7000"
 *              />
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC            value = "0x1234"/>
 *                  <SIO            value = "3"/>
 *                  <SSN            value = "5"/>
 *                  <LinkSet        value = "1"/>
 *                  <LinkCode       value = "1"/>
 *              </Route>
 * 
 *          </Transport>
 * 
 *          <Transport  name    = "ASP 2"
 *                      type    = "Virtual"
 *                      family  = "ITU">
 * 
 *              <DatagramData   socketDomain    = "INET"
 *                              serverHostName  = "192.168.1.14"
 *                              serverPort      = "7000"
 *              />
 * 
 *              <Route  routeType    = "remoteRoute"
 *                      routeStyle   = "dpc-sio-ssn">
 *                  <DPC            value = "0x1234"/>
 *                  <SIO            value = "3"/>
 *                  <SSN            value = "5"/>
 *                  <LinkSet        value = "1"/>
 *                  <LinkCode       value = "2"/>
 *              </Route>
 * 
 *          </Transport>
 * 
 *      </BorderPool>
 * 
 *      <!--///////////////////////////////////////////////////////////////-->
 * 
 *      <SS7-Stacks>
 * 
 *          <ManagementCallbacks
 *              library                         = "libCISCO.so"
 *              MTP3ManagmentCallbackITU        = "HandleMTP3Management"
 *              SCCPManagmentCallbackITU        = "HandleSCCPManagement"
 *              SCCPGlobalTitleCallbackITU      = "HandleGlobalTitle"
 *          />
 * 
 *          <!--///////////////////////////////////////////////////////////-->
 * 
 *          <IntelliNet>
 * 
 *              <ITU-SCCP variant = "WhiteBook">
 *   
 *                  <Variant value = "WhiteBook"/>
 *   
 *                  <StackTrace>
 *                      <Critical output = "stdout"/>
 *                      <Critical output = "file"/>
 *                      <Error    output = "stdout"/>
 *                      <Error    output = "file"/>
 *                      <Warning  output = "stdout"/>
 *                      <Warning  output = "file"/> 
 *                      <Debug    output = "file"/> 
 *                  </StackTrace>
 *   
 *                  <Timers
 *                      TstatInfo    = "30"
 *                      TcoordChg    = "30"
 *                      TignoreSST   = "30"
 *                      TrtgStatInfo = "30"
 *                      Tconnect     = "30"
 *                      Trelease     = "10"
 *                      Treset       = "20"
 *                      Tias         = "300"
 *                      Tiar         = "660"
 *                      Tguard       = "240"
 *                  />
 *   
 *                  <BehaviorControl
 *                      PropagateIT   = "no"
 *                      PropagateERR  = "no"
 *                      PropagateSCMG = "yes"
 *                  />
 *   
 *              </ITU-SCCP>
 *   
 *              <!--///////////////////////////////////////////////////////////////-->
 *   
 *              <ITU-TCAP variant = "WhiteBook">
 *   
 *                  <StackTrace>
 *                      <Critical output = "stdout"/>
 *                      <Critical output = "file"/>
 *                      <Error    output = "stdout"/>
 *                      <Error    output = "file"/>
 *                      <Warning  output = "stdout"/>
 *                      <Warning  output = "file"/> 
 *                      <Debug    output = "file"/> 
 *                  </StackTrace>
 *   
 *                  <Route  routeType    = "localRoute"
 *                          routeStyle   = "dpc-sio-ssn">
 *                      <SIO        value = "3"/>
 *                      <DPC        value = "0"/>
 *                      <SSN        value = "3"/>
 *                      <LinkSet    value = "255"/>
 *                      <LinkCode   value = "255"/>
 *                  </Route>
 *   
 *                  <Timers
 *                      Treject = "5"
 *                  />
 *   
 *              </ITU-TCAP>
 * 
 *          </IntelliNet>
 * 
 *      </SS7-Stacks>
 * 
 *  </Application>
 *
 *****************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Had a bit of an epiphany.  If I marry Hubert's idea of object building
 * with the idea of an engine, an immediate conclusion can be met: if one
 * regards the object building as config items, one can build the config
 * for the application in the way Hubert sees things, but with the resulting
 * object tree being input for the engine configurator.
 *
 * In other words, if the XML parser builds a configuration tree (that can
 * also be built by "hand"), then we can marry the ideas and satisfy both
 * constraints.
 *
 * I know what you're thinking.  If we had a generic list class we wouldn't
 * need to do things this way.  First things first.
 */

typedef struct _applicationRec  *ENGINE_Application;

/****************************************************************************/
/*
 * the library cache record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_LibCacheClass, app, libName);
 */
typedef struct _libCacheRec
{
    ITS_Object          next;
    ENGINE_Application  app;
    char                *libName;
    DLSYM_Manager       *library;
}
ENGINE_LibCachePart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_LibCachePart libCache;
}
ENGINE_LibCacheRec, *ENGINE_LibCache;

#define ENGINE_LC_NEXT(x) \
    (((ENGINE_LibCacheRec *)(x))->libCache.next)

#define ENGINE_LC_APP(x) \
    (((ENGINE_LibCacheRec *)(x))->libCache.app)

#define ENGINE_LC_LIB_NAME(x) \
    (((ENGINE_LibCacheRec *)(x))->libCache.libName)

#define ENGINE_LC_LIBRARY(x) \
    (((ENGINE_LibCacheRec *)(x))->libCache.library)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_LibCacheClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_LibCacheClass;

ITSDLLAPI ENGINE_LibCache ENGINE_LibGet(ENGINE_Application, const char *);

/****************************************************************************/

/****************************************************************************/
/*
 * parser extensions
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ParserExtensionClass, app,
 *                          "libNMS.so", "NMS_Data"
 *                          "NMS_ParseStart", "NMS_ParseEnd",
 *                          "NMS_ConvertParserData", "NMS_Diff");
 */
typedef struct _ENGINE_ParserExtension    *ENGINE_ParserExtension;

typedef void    (*ENGINE_ParseStartFunc)(ENGINE_ParserExtension ext,
                                         const char *el, const char **attr);
typedef void    (*ENGINE_ParseStopFunc)(ENGINE_ParserExtension ext,
                                        const char *el);
typedef void    (*ENGINE_ResourceXlateFunc)(RESFILE_Manager *appRes,
                                            ENGINE_ParserExtension ext);
typedef void    (*ENGINE_ExtensionDiffFunc)(RESFILE_Manager *appRes,
                                            ENGINE_ParserExtension ext1,
                                            ENGINE_ParserExtension ext2);
typedef void    (*ENGINE_ExtensionCommitFunc)(FILE* fp);


typedef struct
{
    ITS_Object                  next;
    ENGINE_LibCache             lib;
    char                        *elementName;
    char                        *startFuncName;
    char                        *stopFuncName;
    char                        *xlateFuncName;
    char                        *diffFuncName;
    char                        *commitFuncName;
    ENGINE_ParseStartFunc       startFunc;
    ENGINE_ParseStopFunc        stopFunc;
    ENGINE_ResourceXlateFunc    xlateFunc;
    ENGINE_ExtensionDiffFunc    diffFunc;
    ENGINE_ExtensionCommitFunc  commitFunc;
    void                        *userData;
    int                         elementDataCount;
    char                        **elementData;
}
ENGINE_ParserExtensionPart;

typedef struct _ENGINE_ParserExtension
{
    ITS_CoreObjectPart          core;
    ENGINE_ParserExtensionPart  ext;
}
ENGINE_ParserExtensionRec;

#define ENGINE_PE_NEXT(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.next)

#define ENGINE_PE_LIB_CACHE_ENTRY(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.lib)

#define ENGINE_PE_ELEMENT_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.elementName)

#define ENGINE_PE_START_FUNC_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.startFuncName)

#define ENGINE_PE_STOP_FUNC_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.stopFuncName)

#define ENGINE_PE_XLATE_FUNC_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.xlateFuncName)

#define ENGINE_PE_DIFF_FUNC_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.diffFuncName)

#define ENGINE_PE_COMMIT_FUNC_NAME(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.commitFuncName)

#define ENGINE_PE_START_FUNC(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.startFunc)

#define ENGINE_PE_STOP_FUNC(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.stopFunc)

#define ENGINE_PE_XLATE_FUNC(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.xlateFunc)

#define ENGINE_PE_DIFF_FUNC(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.diffFunc)

#define ENGINE_PE_COMMIT_FUNC(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.commitFunc)

#define ENGINE_PE_USER_DATA(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.userData)

#define ENGINE_PE_ELEMENT_DATA_COUNT(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.elementDataCount)

#define ENGINE_PE_ELEMENT_DATA(x) \
    (((ENGINE_ParserExtensionRec *)(x))->ext.elementData)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ParserExtensionClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ParserExtensionClass;

/****************************************************************************/

/****************************************************************************/
/*
 * features to add at start
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_FeatureClass, app, "SCTP",
 *                          "libSCTP.so", "itsSCTP_Class",
 *                          options, numOptions);
 */
typedef struct _featureRec
{
    ITS_Object          next;
    ITS_Object          prev;
    ENGINE_Application  app;
    char                *featureName;
    ENGINE_LibCache     lib;
    ITS_Class           classRecord;
    char                *className;
    char                **options;
    int                 numOptions;
}
ENGINE_FeaturePart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_FeaturePart  feature;
}
ENGINE_FeatureRec, *ENGINE_Feature;

#define ENGINE_FEAT_NEXT(x) \
    (((ENGINE_FeatureRec *)(x))->feature.next)

#define ENGINE_FEAT_PREV(x) \
    (((ENGINE_FeatureRec *)(x))->feature.prev)

#define ENGINE_FEAT_APP(x) \
    (((ENGINE_FeatureRec *)(x))->feature.app)

#define ENGINE_FEAT_NAME(x) \
    (((ENGINE_FeatureRec *)(x))->feature.featureName)

#define ENGINE_FEAT_LIB_CACHE_ENTRY(x) \
    (((ENGINE_FeatureRec *)(x))->feature.lib)

#define ENGINE_FEAT_CLASS_REC(x) \
    (((ENGINE_FeatureRec *)(x))->feature.classRecord)

#define ENGINE_FEAT_CLASS_NAME(x) \
    (((ENGINE_FeatureRec *)(x))->feature.className)

#define ENGINE_FEAT_OPTIONS(x) \
    (((ENGINE_FeatureRec *)(x))->feature.options)

#define ENGINE_FEAT_NUM_OPTIONS(x) \
    (((ENGINE_FeatureRec *)(x))->feature.numOptions)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_FeatureClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_FeatureClass;

/****************************************************************************/

/****************************************************************************/
/*
 * trace levels specific to this application
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_TraceClass, traceList, "levelName",
 *                          levelMask);
 */
typedef struct _traceRec
{
    ITS_Object          next;
    char                *levelName;
    int                 levelMask;
}
ENGINE_TracePart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_TracePart    trace;
}
ENGINE_TraceRec, *ENGINE_Trace;

#define ENGINE_TL_NEXT(x) \
    (((ENGINE_TraceRec *)(x))->trace.next)

#define ENGINE_TL_LEVEL_NAME(x) \
    (((ENGINE_TraceRec *)(x))->trace.levelName)

#define ENGINE_TL_LEVEL_MASK(x) \
    (((ENGINE_TraceRec *)(x))->trace.levelMask)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_TraceClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_TraceClass;

/****************************************************************************/

/****************************************************************************/
/*
 * route records for a transport
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_RouteClass, &routeList, pointCode,
 *                          type, style, ...);
 */
typedef struct _routeRec
{
    ITS_Object      next;
    ROUTE_MatchInfo rinfo;
}
ENGINE_RoutePart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_RoutePart    route;
}
ENGINE_RouteRec, *ENGINE_Route;

#define ENGINE_RT_NEXT(x) \
    (((ENGINE_RouteRec *)(x))->route.next)

#define ENGINE_RT_INFO(x) \
    (((ENGINE_RouteRec *)(x))->route.rinfo)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_RouteClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_RouteClass;

/****************************************************************************/

/****************************************************************************/
/*
 * ISUP Timer record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ISUPTimerClass, isupAttributes,
 *                          id, value, handler);
 */
typedef struct
{
    ITS_Object      next;
    char *          id;
    char *          value;
    char *          handler;
}
ENGINE_ISUPTimerPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_ISUPTimerPart    timer;
}
ENGINE_ISUPTimerRec, *ENGINE_ISUPTimer;

#define ENGINE_IT_NEXT(x) \
    (((ENGINE_ISUPTimerRec *)(x))->timer.next)

#define ENGINE_IT_ID(x) \
    (((ENGINE_ISUPTimerRec *)(x))->timer.id)

#define ENGINE_IT_VALUE(x) \
    (((ENGINE_ISUPTimerRec *)(x))->timer.value)

#define ENGINE_IT_HANDLER(x) \
    (((ENGINE_ISUPTimerRec *)(x))->timer.handler)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ISUPTimerClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ISUPTimerClass;

/****************************************************************************/

/****************************************************************************/
/*
 * ISUP Circuit Codes record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_CICsClass, circuitGroup,
 *                          start, count);
 */
typedef struct
{
    ITS_Object      next;
    ITS_UINT        start;
    ITS_UINT        count;
}
ENGINE_CICsPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_CICsPart         cics;
}
ENGINE_CICsRec, *ENGINE_CICs;

#define ENGINE_IC_NEXT(x) \
    (((ENGINE_CICsRec *)(x))->cics.next)

#define ENGINE_IC_START(x) \
    (((ENGINE_CICsRec *)(x))->cics.start)

#define ENGINE_IC_COUNT(x) \
    (((ENGINE_CICsRec *)(x))->cics.count)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_CICsClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_CICsClass;

/****************************************************************************/

/****************************************************************************/
/*
 * ISUP Circuit Group record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_CircuitGroupClass, isupAttr,
 *                          huntRule);
 */
typedef struct
{
    ITS_Object      next;
    char            *huntRule;
    ITS_Object      circuitCodes;
}
ENGINE_CircuitGroupPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_CircuitGroupPart group;
}
ENGINE_CircuitGroupRec, *ENGINE_CircuitGroup;

#define ENGINE_CG_NEXT(x) \
    (((ENGINE_CircuitGroupRec *)(x))->group.next)

#define ENGINE_CG_HUNT_RULE(x) \
    (((ENGINE_CircuitGroupRec *)(x))->group.huntRule)

#define ENGINE_CG_CODES(x) \
    (((ENGINE_CircuitGroupRec *)(x))->group.circuitCodes)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_CircuitGroupClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_CircuitGroupClass;

/****************************************************************************/

/****************************************************************************/
/*
 * ISUP Attributes record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ISUPAttrClass,
 *                          application, destination,
 *                          localPointCode, sio, classRec, library);
 */
typedef struct
{
    ITS_UINT        lpc;
    ITS_UINT        sio;
    char            *xchangeType;
    char            *segmentationSupported;
    char *          classRec;
    ENGINE_LibCache lib;
    ITS_Object      timers;
    ITS_Object      groups;
}
ENGINE_ISUPAttrPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_ISUPAttrPart     attrs;
}
ENGINE_ISUPAttrRec, *ENGINE_ISUPAttr;

#define ENGINE_IA_LPC(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.lpc)

#define ENGINE_IA_SIO(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.sio)

#define ENGINE_IA_XTYPE(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.xchangeType)

#define ENGINE_IA_SEGMENTATIONSUPPORT(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.segmentationSupported)

#define ENGINE_IA_CLASS_REC(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.classRec)

#define ENGINE_IA_LIB(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.lib)

#define ENGINE_IA_TIMERS(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.timers)

#define ENGINE_IA_GROUPS(x) \
    (((ENGINE_ISUPAttrRec *)(x))->attrs.groups)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ISUPAttrClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ISUPAttrClass;

/****************************************************************************/

/****************************************************************************/
/*
 * SIP Timer record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_SIPTimerClass, sipAttributes,
 *                          id, value);
 */
typedef struct
{
    ITS_Object      next;
    char *          id;
    char *          value;
}
ENGINE_SIPTimerPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_SIPTimerPart    timer;
}
ENGINE_SIPTimerRec, *ENGINE_SIPTimer;

#define ENGINE_ST_NEXT(x) \
    (((ENGINE_SIPTimerRec *)(x))->timer.next)

#define ENGINE_ST_ID(x) \
    (((ENGINE_SIPTimerRec *)(x))->timer.id)

#define ENGINE_ST_VALUE(x) \
    (((ENGINE_SIPTimerRec *)(x))->timer.value)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_SIPTimerClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_SIPTimerClass;

/****************************************************************************/

/****************************************************************************/
/*
 * SIP Attributes record
 *
 * Usage:
 *      ITS_ConstructObject(itsENGINE_SIPAttrClass,
 *                          UDPPortNo, TCPPortNo, ipAddr);
 */
typedef struct
{
    ITS_USHORT      UDPPortNo;
    ITS_USHORT      TCPPortNo;
    char            *ipAddr;
    ITS_Object      timers;
    ITS_Object      trace;
}
ENGINE_SIPAttrPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_SIPAttrPart     attrs;
}
ENGINE_SIPAttrRec, *ENGINE_SIPAttr;

#define ENGINE_SIP_UDPPORT(x) \
    (((ENGINE_SIPAttrRec *)(x))->attrs.UDPPortNo)

#define ENGINE_SIP_TCPPORT(x) \
    (((ENGINE_SIPAttrRec *)(x))->attrs.TCPPortNo)

#define ENGINE_SIP_IPADDR(x) \
    (((ENGINE_SIPAttrRec *)(x))->attrs.ipAddr)

#define ENGINE_SIP_TIMERS(x) \
    (((ENGINE_SIPAttrRec *)(x))->attrs.timers)

#define ENGINE_SIP_TRACE(x) \
    (((ENGINE_SIPAttrRec *)(x))->attrs.trace)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_SIPAttrClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_SIPAttrClass;

/****************************************************************************/

/****************************************************************************/
/*
 * destination records
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_DestinationClass, app,
 *                          pointCode, ni,
 *                          mtp3Var, isupVar, sccpVar, tcapVar,
 *                          tupVar, dupVar);
 */
typedef struct _destRec
{
    ITS_Object      next;
    ITS_UINT        pc;
    ITS_OCTET       ni;
    SS7_Family      family;
    ITS_INT         mtp3Var;
    char *          isupVar;
    ITS_INT         sccpVar;
    ITS_INT         tcapVar;
    ITS_INT         tupVar;
    ITS_INT         dupVar;
    ITS_Object      isupAttr;
}
ENGINE_DestPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_DestPart     dest;
}
ENGINE_DestRec, *ENGINE_Dest;

#define ENGINE_DE_NEXT(x) \
    (((ENGINE_DestRec *)(x))->dest.next)

#define ENGINE_DE_PC(x) \
    (((ENGINE_DestRec *)(x))->dest.pc)

#define ENGINE_DE_NI(x) \
    (((ENGINE_DestRec *)(x))->dest.ni)

#define ENGINE_DE_FAMILY(x) \
    (((ENGINE_DestRec *)(x))->dest.family)

#define ENGINE_DE_MTP3(x) \
    (((ENGINE_DestRec *)(x))->dest.mtp3Var)

#define ENGINE_DE_ISUP(x) \
    (((ENGINE_DestRec *)(x))->dest.isupVar)

#define ENGINE_DE_SCCP(x) \
    (((ENGINE_DestRec *)(x))->dest.sccpVar)

#define ENGINE_DE_TCAP(x) \
    (((ENGINE_DestRec *)(x))->dest.tcapVar)

#define ENGINE_DE_TUP(x) \
    (((ENGINE_DestRec *)(x))->dest.tupVar)

#define ENGINE_DE_DUP(x) \
    (((ENGINE_DestRec *)(x))->dest.dupVar)

#define ENGINE_DE_ISUP_ATTR(x) \
    (((ENGINE_DestRec *)(x))->dest.isupAttr)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_DestClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_DestClass;

/****************************************************************************/

/****************************************************************************/
/*
 * linkset record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_LinkSetClass, adjacent, id);
 */
typedef struct _linkSet
{
    ITS_Object      next;
    ITS_UINT        adjacent;
    ITS_UINT        lpc;
    ITS_OCTET       linkSet;
    ITS_OCTET       ni;
    ITS_USHORT      pad;
    ITS_UINT        numToStart;
    ITS_BOOLEAN     adjacentSTP;
    ITS_BOOLEAN     isC;
    ITS_BOOLEAN     is5Bit;
    SS7_Family      family;
}
ENGINE_LinkSetPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_LinkSetPart  linkSet;
}
ENGINE_LinkSetRec, *ENGINE_LinkSet;

#define ENGINE_LS_NEXT(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.next)

#define ENGINE_LS_ADJ(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.adjacent)

#define ENGINE_LS_LOC(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.lpc)

#define ENGINE_LS_ID(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.linkSet)

#define ENGINE_LS_NI(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.ni)

#define ENGINE_LS_NUM_TO_START(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.numToStart)

#define ENGINE_LS_ADJACENT_STP(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.adjacentSTP)

#define ENGINE_LS_IS_C(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.isC)

#define ENGINE_LS_IS_5BIT(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.is5Bit)

#define ENGINE_LS_FAMILY(x) \
    (((ENGINE_LinkSetRec *)(x))->linkSet.family)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_LinkSetClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_LinkSetClass;

/****************************************************************************/

/****************************************************************************/
/*
 * link record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_LinkClass, list,
 *                          set, code, pri, initActive,
 *                          termFixed, linkFixed, term, link);
 */
typedef struct _link
{
    ITS_Object      next;
    ITS_OCTET       linkSet;
    ITS_OCTET       linkCode;
    ITS_OCTET       linkPri;
    ITS_OCTET       pad;
    ITS_BOOLEAN     initActive;
    ITS_BOOLEAN     termFixed;
    ITS_BOOLEAN     linkFixed;
    ITS_BOOLEAN     isSAAL;
    ITS_BOOLEAN     isLocal;
    ITS_USHORT      terminal;
    ITS_USHORT      circuit;
    SS7_Family      family;
}
ENGINE_LinkPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_LinkPart     link;
}
ENGINE_LinkRec, *ENGINE_Link;

#define ENGINE_LN_NEXT(x) \
    (((ENGINE_LinkRec *)(x))->link.next)

#define ENGINE_LN_SET(x) \
    (((ENGINE_LinkRec *)(x))->link.linkSet)

#define ENGINE_LN_CODE(x) \
    (((ENGINE_LinkRec *)(x))->link.linkCode)

#define ENGINE_LN_PRI(x) \
    (((ENGINE_LinkRec *)(x))->link.linkPri)

#define ENGINE_LN_INIT_ACTIVE(x) \
    (((ENGINE_LinkRec *)(x))->link.initActive)

#define ENGINE_LN_TERM_FIXED(x) \
    (((ENGINE_LinkRec *)(x))->link.termFixed)

#define ENGINE_LN_LINK_FIXED(x) \
    (((ENGINE_LinkRec *)(x))->link.linkFixed)

#define ENGINE_LN_IS_SAAL(x) \
    (((ENGINE_LinkRec *)(x))->link.isSAAL)

#define ENGINE_LN_IS_LOCAL(x) \
    (((ENGINE_LinkRec *)(x))->link.isSAAL)

#define ENGINE_LN_TERMINAL(x) \
    (((ENGINE_LinkRec *)(x))->link.terminal)

#define ENGINE_LN_CIRCUIT(x) \
    (((ENGINE_LinkRec *)(x))->link.circuit)

#define ENGINE_LN_FAMILY(x) \
    (((ENGINE_LinkRec *)(x))->link.family)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_LinkClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_LinkClass;

/****************************************************************************/

/****************************************************************************/
/*
 * transport specifics
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
 *                          mask, ...);
 */
typedef struct
{
    ITS_UINT mask;
    union
    {
        struct fifoSpecs
        {
            char    *clientPath;
            char    *serverPath;
        }
        fifoSpecs;
        struct tcpSpecs
        {
            char    *socketDomain;
            char    *serverPath;
            char    *serverPort;
            char    *retryDelay;
            char    *retryCount;
        }
        tcpSpecs;
        struct udpSpecs
        {
            char    *localHost;
            char    *localPort;
            char    **associates;
            int     numAssociates;
        }
        udpSpecs;
        struct gdiSpecs
        {
            struct tcpSpecs tcpPart;
            char            *localPC;
            char            *remotePC;
            char            *remoteSSN;
        }
        gdiSpecs;
        struct imalSpecs
        {
            struct tcpSpecs tcpPart;
            char            *localPC;
            char            *adjacentPC;
            char            *keepAliveTimeOut;
        }
        imalSpecs;
        struct taliSpecs
        {
            struct tcpSpecs tcpPart;
            char            *localPC;
            char            *adjacentPC;
            char            *localAllowedOnOpen;
            char            *useUpperLayer;
        }
        taliSpecs;
        struct sctpSpecs
        {
            struct udpSpecs udpPart;
            char            **extraHomes;
            int             numExtraHomes;
            char            *maxInStreams;
            char            *numOutStreams;
            char            *maxAttempts;
            char            *cookieLife;
            char            *hbOn;
            char            *initTimeOut;
            char            *sendTimeOut;
            char            *recvTimeOut;
            char            *hbTimeOut;
            char            *shutdownTimeOut;
            char            *pmtuTimeOut;
            char            *isClient;
            char            *payloadType;
        }
        sctpSpecs;
        struct ss7Specs
        {
            char *vendorName;
            char *vendorLib;
            char *vendorClass;
        }
        ss7Specs;
    }
    data;
}
ENGINE_TransportSpecificsPart;

typedef struct
{
    ITS_CoreObjectPart             core;
    ENGINE_TransportSpecificsPart  specifics;
}
ENGINE_TransportSpecificsRec, *ENGINE_TransportSpecifics;

#define ENGINE_TS_MASK(x) \
    (((ENGINE_TransportSpecificsRec *)(x))->specifics.mask)

#define ENGINE_TS_DATA(x) \
    (((ENGINE_TransportSpecificsRec *)(x))->specifics.data)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_TransportSpecificsClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_TransportSpecificsClass;

int ENGINE_ParseTransportSpecifics(ENGINE_TransportSpecifics specs,
                                   va_list args);
void ENGINE_FreeTransportSpecifics(ENGINE_TransportSpecifics specs);

/****************************************************************************/

/****************************************************************************/
/*
 * callbacks record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_TransportCallbacksClass, app,
 *                          "libCISCO.so", notTrueSS7,
 *                          DISP_PROT_USER, DISP_BLOCKING,
 *                          "PreInit", "PostInit",
 *                          "PreNext", "NextEventFailed", "PostNext",
 *                          "DispatchUSER", "DispatchISUP", "DispatchSCCP",
 *                          "PreAccept", "OnAccept",
 *                          "PreTerminate", "PostTerminate",
 *                          DISP_PROT_USER);
 */
typedef struct
{
    char                *libName;
    DISP_HandlerType    handlerType;
    DISP_Type           type;
    char                *main;
    char                *preInit;
    char                *postInit;
    char                *preNextEvent;
    char                *nextEventFailed;
    char                *postNextEvent;
    char                *dispUser;
    char                *dispISUP;
    char                *dispSCCP;
    char                *preAccept;
    char                *onAccept;
    char                *preTerm;
    char                *postTerm;
    DISP_HandlerType    acceptHandlerType;
}
ENGINE_TransportCallbacksPart;

typedef struct
{
    ITS_CoreObjectPart              core;
    ENGINE_TransportCallbacksPart   callbacks;
}
ENGINE_TransportCallbacksRec, *ENGINE_TransportCallbacks;

#define ENGINE_TC_LIB_NAME(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.libName)

#define ENGINE_TC_HANDLER_TYPE(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.handlerType)

#define ENGINE_TC_TYPE(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.type)

#define ENGINE_TC_MAIN(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.main)

#define ENGINE_TC_PRE_INIT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.preInit)

#define ENGINE_TC_POST_INIT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.postInit)

#define ENGINE_TC_PRE_NEXT_EVENT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.preNextEvent)

#define ENGINE_TC_NEXT_EVENT_FAIL(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.nextEventFailed)

#define ENGINE_TC_POST_NEXT_EVENT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.postNextEvent)

#define ENGINE_TC_DISP_USER(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.dispUser)

#define ENGINE_TC_DISP_ISUP(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.dispISUP)

#define ENGINE_TC_DISP_SCCP(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.dispSCCP)

#define ENGINE_TC_PRE_ACCEPT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.preAccept)

#define ENGINE_TC_ON_ACCEPT(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.onAccept)

#define ENGINE_TC_PRE_TERM(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.preTerm)

#define ENGINE_TC_POST_TERM(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.postTerm)

#define ENGINE_TC_ACCEPT_HANDLER_TYPE(x) \
    (((ENGINE_TransportCallbacksRec *)(x))->callbacks.acceptHandlerType)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_TransportCallbacksClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_TransportCallbacksClass;

/****************************************************************************/

/****************************************************************************/
/*
 * transport record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_TransportClass, threadPool,
 *                          name, mask, isInterNode, specifics, callbacks,
 *                          routes, workItems);
 */
typedef struct _transportRec
{
    ITS_Object              next;
    ITS_Object              pool;
    char                    *name;
    ITS_BOOLEAN             isInterNode;
    ITS_USHORT              inst;
    ITS_UINT                mask;
    ITS_UINT                numAssociates;
    ITS_Object              specialization;
    ITS_Object              callbacks;
    ITS_Object              links;
    ITS_Object              workItems;
}
ENGINE_TransportPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_TransportPart    transport;
}
ENGINE_TransportRec, *ENGINE_Transport;

#define ENGINE_TR_NEXT(x) \
    (((ENGINE_TransportRec *)(x))->transport.next)

#define ENGINE_TR_POOL(x) \
    (((ENGINE_TransportRec *)(x))->transport.pool)

#define ENGINE_TR_NAME(x) \
    (((ENGINE_TransportRec *)(x))->transport.name)

#define ENGINE_TR_IS_INTERNODE(x) \
    (((ENGINE_TransportRec *)(x))->transport.isInterNode)

#define ENGINE_TR_INST(x) \
    (((ENGINE_TransportRec *)(x))->transport.inst)

#define ENGINE_TR_MASK(x) \
    (((ENGINE_TransportRec *)(x))->transport.mask)

#define ENGINE_TR_NUM_ASSOCIATES(x) \
    (((ENGINE_TransportRec *)(x))->transport.numAssociates)

#define ENGINE_TR_SPECIFICS(x) \
    (((ENGINE_TransportRec *)(x))->transport.specialization)

#define ENGINE_TR_CALLBACKS(x) \
    (((ENGINE_TransportRec *)(x))->transport.callbacks)

#define ENGINE_TR_LINKS(x) \
    (((ENGINE_TransportRec *)(x))->transport.links)

#define ENGINE_TR_WORK_ITEMS(x) \
    (((ENGINE_TransportRec *)(x))->transport.workItems)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_TransportClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_TransportClass;

/****************************************************************************/

/****************************************************************************/
/*
 * work item record
 */
/* Usage:
 *      ITS_ConstructObject(itsENGINE_WorkItemClass, transport,
 *                          ITS_TRUE, 20, "libCISCO.so", "WorkItemDelegate");
 */
typedef struct
{
    ITS_Object          next;
    ENGINE_Transport    transport;
    ITS_BOOLEAN         persist;
    int                 repeat;
    char                *libName;
    char                *delegate;
}
ENGINE_WorkItemPart;

typedef struct
{
    ITS_CoreObjectPart  core;
    ENGINE_WorkItemPart workItem;
}
ENGINE_WorkItemRec, *ENGINE_WorkItem;

#define ENGINE_WI_NEXT(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.next)

#define ENGINE_WI_TRANSPORT(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.transport)

#define ENGINE_WI_PERSIST(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.persist)

#define ENGINE_WI_REPEAT(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.repeat)

#define ENGINE_WI_LIB_NAME(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.libName)

#define ENGINE_WI_DELEGATE(x) \
    (((ENGINE_WorkItemRec *)(x))->workItem.delegate)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_WorkItemClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_WorkItemClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ThreadPoolClass, app,
 *                          stackSize, TPOOL_WORKERS);
 */
typedef enum
{
    TP_BORDERS,
    TP_WORKERS,
    TP_WORK_ITEMS
}
ENGINE_ThreadPoolType;

/*
 * thread pool record
 */
typedef struct _threadPool
{
    ITS_Object              next;
    ENGINE_Application      app;
    int                     stackSize;
    ENGINE_ThreadPoolType   type;
    ITS_Object              transports;
}
ENGINE_ThreadPoolPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_ThreadPoolPart   threadPool;
}
ENGINE_ThreadPoolRec, *ENGINE_ThreadPool;

#define ENGINE_TP_NEXT(x) \
    (((ENGINE_ThreadPoolRec *)(x))->threadPool.next)

#define ENGINE_TP_APP(x) \
    (((ENGINE_ThreadPoolRec *)(x))->threadPool.app)

#define ENGINE_TP_STACK_SIZE(x) \
    (((ENGINE_ThreadPoolRec *)(x))->threadPool.stackSize)

#define ENGINE_TP_TYPE(x) \
    (((ENGINE_ThreadPoolRec *)(x))->threadPool.type)

#define ENGINE_TP_TRANSPORTS(x) \
    (((ENGINE_ThreadPoolRec *)(x))->threadPool.transports)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ThreadPoolClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ThreadPoolClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(itsENGINE_SS7StackMgmtClass, app,
 *                          "libCISCO.so",
 *                          "MTP3MgmtANSI", NULL,
 *                          "ISUPMgmtANSI", NULL,
 *                          "SCCPMgmtANSI", NULL,
 *                          "GTTMgmtANSI", NULL,
 *                          "SSNRouteANSI", NULL);
 */
typedef struct _ss7StackMgmt
{
    ENGINE_Application  app;
    char                *libName;
    char                *mtp3MgmtANSI;
    char                *mtp3MgmtCCITT;
    char                *isupMgmtANSI;
    char                *isupMgmtCCITT;
    char                *sccpMgmtANSI;
    char                *sccpMgmtCCITT;
    char                *sccpGTTANSI;
    char                *sccpGTTCCITT;
    char                *sccpSSNRouteANSI;
    char                *sccpSSNRouteCCITT;
}
ENGINE_SS7StackMgmtPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_SS7StackMgmtPart ss7StackMgmt;
}
ENGINE_SS7StackMgmtRec, *ENGINE_SS7StackMgmt;

#define ENGINE_S7_APP(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.app)

#define ENGINE_S7_LIB_NAME(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.libName)

#define ENGINE_S7_MTP3_MGMT_ANSI(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.mtp3MgmtANSI)

#define ENGINE_S7_MTP3_MGMT_CCITT(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.mtp3MgmtCCITT)

#define ENGINE_S7_ISUP_MGMT_ANSI(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.isupMgmtANSI)

#define ENGINE_S7_ISUP_MGMT_CCITT(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.isupMgmtCCITT)

#define ENGINE_S7_SCCP_MGMT_ANSI(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpMgmtANSI)

#define ENGINE_S7_SCCP_MGMT_CCITT(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpMgmtCCITT)

#define ENGINE_S7_SCCP_GTT_ANSI(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpGTTANSI)

#define ENGINE_S7_SCCP_GTT_CCITT(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpGTTCCITT)

#define ENGINE_S7_SCCP_SSN_ROUTE_ANSI(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpSSNRouteANSI)

#define ENGINE_S7_SCCP_SSN_ROUTE_CCITT(x) \
    (((ENGINE_SS7StackMgmtRec *)(x))->ss7StackMgmt.sccpSSNRouteCCITT)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_SS7StackMgmtClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_SS7StackMgmtClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ISS7StackClass, app, name, variant,
 *                          numThreads);
 */

typedef struct
{
    ITS_Object  next;
    char        *name;
    char        *variant_name;
    int         variant;
    int         numThreads;
    ITS_Object  trace;
    ITS_Object  links;
    char        **timers;
    int         numTimers;
    char        **modifiers;
    int         numModifiers;
}
ENGINE_ISS7StackPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_ISS7StackPart    stack;
}
ENGINE_ISS7StackRec, *ENGINE_ISS7Stack;

#define ENGINE_ISS7_NEXT(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.next)

#define ENGINE_ISS7_NAME(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.name)

#define ENGINE_ISS7_VARIANT_NAME(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.variant_name)

#define ENGINE_ISS7_VARIANT(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.variant)

#define ENGINE_ISS7_NUM_THREADS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.numThreads)

#define ENGINE_ISS7_TRACE(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.trace)

#define ENGINE_ISS7_LINKS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.links)

#define ENGINE_ISS7_TIMERS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.timers)

#define ENGINE_ISS7_NUM_TIMERS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.numTimers)

#define ENGINE_ISS7_MODIFIERS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.modifiers)

#define ENGINE_ISS7_NUM_MODIFIERS(x) \
    (((ENGINE_ISS7StackRec *)(x))->stack.numModifiers)

extern ITSDLLAPI ITS_ClassRec itsENGINE_ISS7StackClassRec;
extern ITSDLLAPI ITS_Class    itsENGINE_ISS7StackClass;

/********************************************************/
/* Added to separate sigtran m2ua iid*/
/* Usage:
 *      ITS_ConstructObject(itsENGINE_M2UA_IIDClass, linkSet, LinkCode,
 *                          IID, assoName);
 */
typedef struct _iid
{
    ITS_Object  next;
    ITS_OCTET   linkSet;
    ITS_OCTET   linkCode;
    char        *IID;
    char        *assoName;
}
ENGINE_M2UA_IIDPart;

typedef struct
{
    ITS_CoreObjectPart       core;
    ENGINE_M2UA_IIDPart      iid;
}
ENGINE_M2UA_IIDRec, *ENGINE_M2UA_IID;

#define ENGINE_M2UA_IID_NEXT(x) \
    (((ENGINE_M2UA_IIDRec *)(x))->iid.next)

#define ENGINE_M2UA_IID_LINKSET(x) \
    (((ENGINE_M2UA_IIDRec *)(x))->iid.linkSet)

#define ENGINE_M2UA_IID_LINKCODE(x) \
    (((ENGINE_M2UA_IIDRec *)(x))->iid.linkCode)

#define ENGINE_M2UA_IID_IID(x) \
    (((ENGINE_M2UA_IIDRec *)(x))->iid.IID)

#define ENGINE_M2UA_IID_ASSONAME(x) \
    (((ENGINE_M2UA_IIDRec *)(x))->iid.assoName)

extern ITSDLLAPI ITS_ClassRec itsENGINE_M2UA_IIDClassRec; 
extern ITSDLLAPI ITS_Class    itsENGINE_M2UA_IIDClass;

/********************************************************/

/* Added to separate sigtran tracing from toolkit trace */
typedef struct
{
    ITS_Object  next;
    char        *name;
    ITS_Object  trace;
    ITS_Object  iid;
}
ENGINE_SIGTRANStackPart;

typedef struct
{
    ITS_CoreObjectPart         core;
    ENGINE_SIGTRANStackPart    stack;
}
ENGINE_SIGTRANStackRec, *ENGINE_SIGTRANStack;

#define ENGINE_SIGTRAN_NEXT(x) \
    (((ENGINE_SIGTRANStackRec *)(x))->stack.next)

#define ENGINE_SIGTRAN_NAME(x) \
    (((ENGINE_SIGTRANStackRec *)(x))->stack.name)

#define ENGINE_SIGTRAN_TRACE(x) \
    (((ENGINE_SIGTRANStackRec *)(x))->stack.trace)

#define ENGINE_SIGTRAN_IID(x) \
    (((ENGINE_SIGTRANStackRec *)(x))->stack.iid)

extern ITSDLLAPI ITS_ClassRec itsENGINE_SIGTRANStackClassRec;
extern ITSDLLAPI ITS_Class    itsENGINE_SIGTRANStackClass;


/****************************************************************************/

/********************************************************/

/* Added to separate codec stack tracing from toolkit trace */
typedef struct
{
    ITS_Object  next;
    char        *name;
    ITS_Object  trace;
    char        **timers;
    int         numTimers;
}
ENGINE_CODECStackPart;

typedef struct
{
    ITS_CoreObjectPart         core;
    ENGINE_CODECStackPart    stack;
}
ENGINE_CODECStackRec, *ENGINE_CODECStack;

#define ENGINE_CODEC_NEXT(x) \
    (((ENGINE_CODECStackRec *)(x))->stack.next)

#define ENGINE_CODEC_NAME(x) \
    (((ENGINE_CODECStackRec *)(x))->stack.name)

#define ENGINE_CODEC_TRACE(x) \
    (((ENGINE_CODECStackRec *)(x))->stack.trace)

#define ENGINE_CODEC_TIMERS(x) \
    (((ENGINE_CODECStackRec *)(x))->stack.timers)

#define ENGINE_CODEC_NUM_TIMERS(x) \
    (((ENGINE_CODECStackRec *)(x))->stack.numTimers)


extern ITSDLLAPI ITS_ClassRec itsENGINE_CODECstackClassRec;
extern ITSDLLAPI ITS_Class    itsENGINE_CODECStackClass;


/****************************************************************************/


/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(
 *              itsENGINE_FtCallbackClass,
 *              list,
 *              type, 
 *              functionName,
 *              libraryName);
 */

typedef enum
{
    FT_CALLBACK_MEMBERSHIP_CHANGE_ALL_FT_GROUPS,
    FT_CALLBACK_EVENT_FROM_ALL_FT_GROUP_MEMBERS,
    FT_CALLBACK_MEMBERSHIP_CHANGE,
    FT_CALLBACK_EVENT_FROM_FT_GROUP_MEMBER
}
ENGINE_FtCallbackType;

typedef struct
{
    ITS_Object              next;
    ENGINE_FtCallbackType   type;
    char*                   functionName;
    char*                   libraryName;
}
ENGINE_FtCallbackPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    ENGINE_FtCallbackPart   ftCallback;
}
ENGINE_FtCallbackRec, *ENGINE_FtCallback;

#define ENGINE_FT_CALLBACK_NEXT(x) \
    (((ENGINE_FtCallbackRec *)(x))->ftCallback.next)

#define ENGINE_FT_CALLBACK_TYPE(x) \
    (((ENGINE_FtCallbackRec *)(x))->ftCallback.type)

#define ENGINE_FT_CALLBACK_FUNCTION_NAME(x) \
    (((ENGINE_FtCallbackRec *)(x))->ftCallback.functionName)

#define ENGINE_FT_CALLBACK_LIBRARY_NAME(x) \
    (((ENGINE_FtCallbackRec *)(x))->ftCallback.libraryName)

extern ITSDLLAPI ITS_ClassRec     itsENGINE_FtCallbackClassRec;
extern ITSDLLAPI ITS_Class        itsENGINE_FtCallbackClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupMemberClass,
 *              list,
 *              type,
 *              nodeId,
 *              nodeName,
 *              processId,
 *              processName);
 */

typedef enum
{
    FT_GROUP_MEMBER_NORMAL,
    FT_GROUP_MEMBER_MASTER
}
ENGINE_FtGroupMemberType;

typedef struct
{
    ITS_Object                  next;
    ENGINE_FtGroupMemberType    type;
    ITS_USHORT                  nodeId;
    char*                       nodeName;
    ITS_USHORT                  processId;
    char*                       processName;
}
ENGINE_FtGroupMemberPart;

typedef struct
{
    ITS_CoreObjectPart          core;
    ENGINE_FtGroupMemberPart    ftGroupMember;
}
ENGINE_FtGroupMemberRec, *ENGINE_FtGroupMember;

#define ENGINE_FT_GROUP_MEMBER_NEXT(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.next)

#define ENGINE_FT_GROUP_MEMBER_TYPE(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.type)

#define ENGINE_FT_GROUP_MEMBER_NODE_ID(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.nodeId)

#define ENGINE_FT_GROUP_MEMBER_NODE_NAME(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.nodeName)

#define ENGINE_FT_GROUP_MEMBER_PROCESS_ID(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.processId)

#define ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(x) \
    (((ENGINE_FtGroupMemberRec *)(x))->ftGroupMember.processName)

extern ITSDLLAPI ITS_ClassRec     itsENGINE_FtGroupMemberClassRec;
extern ITSDLLAPI ITS_Class        itsENGINE_FtGroupMemberClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupClass,
 *              list,
 *              ftGroupId,
 *              ftGroupName,
 *              dsmSize,
 *              dsmBaseAddress,
 *              dsmMaxNumTables,
 *              dsmType);
 */

typedef struct
{
    ITS_Object      next;
    ITS_USHORT      ftGroupId;
    char*           ftGroupName;
    ITS_UINT        dsmSize;
    char*           dsmBaseAddress;
    ITS_UINT        dsmMaxNumTables;
    char*           dsmType;
    ITS_Object      ftGroupMembers;
    ITS_Object      masterFtGroupMembers;
    ITS_Object      callbacks;
}
ENGINE_FtGroupPart;

typedef struct
{
    ITS_CoreObjectPart   core;
    ENGINE_FtGroupPart   ftGroup;
}
ENGINE_FtGroupRec, *ENGINE_FtGroup;

#define ENGINE_FT_GROUP_NEXT(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.next)

#define ENGINE_FT_GROUP_FT_GROUP_ID(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.ftGroupId)

#define ENGINE_FT_GROUP_FT_GROUP_NAME(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.ftGroupName)

#define ENGINE_FT_GROUP_DSM_SIZE(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.dsmSize)

#define ENGINE_FT_GROUP_DSM_BASE_ADDRESS(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.dsmBaseAddress)

#define ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.dsmMaxNumTables)

#define ENGINE_FT_GROUP_DSM_TYPE(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.dsmType)

#define ENGINE_FT_GROUP_FT_GROUP_MEMBERS(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.ftGroupMembers)

#define ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.masterFtGroupMembers)

#define ENGINE_FT_GROUP_FT_CALLBACKS(x) \
    (((ENGINE_FtGroupRec *)(x))->ftGroup.callbacks)

extern ITSDLLAPI ITS_ClassRec     itsENGINE_FtGroupClassRec;
extern ITSDLLAPI ITS_Class        itsENGINE_FtGroupClass;

/****************************************************************************/

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(
 *              itsENGINE_FaultToleranceClass,
 *              app,
 *              maxNumFtGroups,
 *              maxNumProcesses,
 *              maxNumNodes,
 *              nodeId,
 *              processId,
 *              tcapFtGroupId,
 *              sccpFtGroupId,
 *              mtp3FtGroupId,
 *              isupFtGroupId,
 *              routingFtGroupId,
 *              timersFtGroupId,
 *              mgmtDataFtGroupId,
 *              ftmPreExecLogicProcName,
 *              ftmPreExecLogicProcLibName,
 *              ftmLoopExecLogicProcName,
 *              ftmLoopExecLogicProcLibName, 
 *              ftmPostExecLogicProcName,
 *              ftmPostExecLogicProcLibName);
 *
 */

typedef struct
{
    ITS_USHORT maxNumFtGroups;
    ITS_USHORT maxNumProcesses;
    ITS_USHORT maxNumNodes;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    ITS_USHORT tcapFtGroupId;
    ITS_USHORT sccpFtGroupId;
    ITS_USHORT mtp3FtGroupId;
    ITS_USHORT isupFtGroupId;
    ITS_USHORT routingFtGroupId;
    ITS_USHORT timersFtGroupId;
    ITS_USHORT mgmtDataFtGroupId;
    char* ftmPreExecLogicProcName;
    char* ftmPreExecLogicProcLibName;
    char* ftmLoopExecLogicProcName;
    char* ftmLoopExecLogicProcLibName;
    char* ftmPostExecLogicProcName;
    char* ftmPostExecLogicProcLibName;
    ITS_Object callbacks;
    ITS_Object ftGroups;
}
ENGINE_FaultTolerancePart;

typedef struct
{
    ITS_CoreObjectPart          core;
    ENGINE_FaultTolerancePart   ft;
}
ENGINE_FaultToleranceRec, *ENGINE_FaultTolerance;

#define ENGINE_FT_MAX_NUM_FT_GROUPS(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.maxNumFtGroups)

#define ENGINE_FT_MAX_NUM_PROCESSES(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.maxNumProcesses)

#define ENGINE_FT_MAX_NUM_NODES(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.maxNumNodes)

#define ENGINE_FT_NODE_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.nodeId)

#define ENGINE_FT_PROCESS_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.processId)

#define ENGINE_FT_TCAP_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.tcapFtGroupId)

#define ENGINE_FT_SCCP_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.sccpFtGroupId)

#define ENGINE_FT_MTP3_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.mtp3FtGroupId)

#define ENGINE_FT_ISUP_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.isupFtGroupId)

#define ENGINE_FT_ROUTING_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.routingFtGroupId)

#define ENGINE_FT_TIMERS_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.timersFtGroupId)

#define ENGINE_FT_MGMT_DATA_FT_GROUP_ID(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.mgmtDataFtGroupId)

#define ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmPreExecLogicProcName)

#define ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmPreExecLogicProcLibName)

#define ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmLoopExecLogicProcName)

#define ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmLoopExecLogicProcLibName)

#define ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmPostExecLogicProcName)

#define ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftmPostExecLogicProcLibName)

#define ENGINE_FT_CALLBACKS(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.callbacks)

#define ENGINE_FT_FT_GROUPS(x) \
    (((ENGINE_FaultToleranceRec *)(x))->ft.ftGroups)

extern ITSDLLAPI ITS_ClassRec itsENGINE_FaultToleranceClassRec;
extern ITSDLLAPI ITS_Class    itsENGINE_FaultToleranceClass;

/****************************************************************************/
/* Usage:
 *      ITS_ConstructObject(itsENGINE_ApplicationClass, isService,
 *                          usesCPP, globalStartMask, "libCISCO.so",
 *                          "ss7Selector", "appSelector",
 *                          "preFunc", "postFunc");
 */
typedef struct _application
{
    ITS_BOOLEAN             isService;
    ITS_BOOLEAN             cppBinding;
    ITS_UINT                globalStartMask;
    char                    *libName;
    char                    *ss7Selector;
    char                    *appSelector;
    char                    *appDeselector;
    char                    *alarmCallback;
    char                    *hmiCallback;
    char                    *preFunc;
    char                    *postFunc;
    char                    **options;
    int                     numOptions;
    ITS_Object              libCache;
    ITS_Object              supportLevels;
    ITS_Object              traceLevels;
    ITS_Object              vendorLevels1;          /* Trace Levels for ADAX Vendor */
    ITS_Object              vendorLevels2;          /* Trace Levels for NMS Vendor */
    ITS_Object              features;
    ITS_Object              pools;
    ITS_Object              ss7StackMgmt;
    ITS_Object              iss7StackControl;
    ITS_Object              sigtranStackControl;
    ITS_Object              codecStackControl;
    ITS_Object              parserExtensions;
    ITS_Object              faultTolerance;
    ITS_Object              routes;
    ITS_Object              linkSets;
    ITS_Object              destinations;
    ITS_Object              sipAttributes;
}
ENGINE_ApplicationPart;

typedef struct _applicationRec
{
    ITS_CoreObjectPart      core;
    ENGINE_ApplicationPart  application;
}
ENGINE_ApplicationRec;

#define ENGINE_APP_IS_SERVICE(x) \
    (((ENGINE_ApplicationRec *)(x))->application.isService)

#define ENGINE_APP_CPP_BINDING(x) \
    (((ENGINE_ApplicationRec *)(x))->application.cppBinding)

#define ENGINE_APP_GS_MASK(x) \
    (((ENGINE_ApplicationRec *)(x))->application.globalStartMask)

#define ENGINE_APP_LIB_NAME(x) \
    (((ENGINE_ApplicationRec *)(x))->application.libName)

#define ENGINE_APP_SS7_SELECTOR(x) \
    (((ENGINE_ApplicationRec *)(x))->application.ss7Selector)

#define ENGINE_APP_APP_SELECTOR(x) \
    (((ENGINE_ApplicationRec *)(x))->application.appSelector)

#define ENGINE_APP_APP_DESELECTOR(x) \
    (((ENGINE_ApplicationRec *)(x))->application.appDeselector)

#define ENGINE_APP_HMI_CB(x) \
    (((ENGINE_ApplicationRec *)(x))->application.hmiCallback)

#define ENGINE_APP_ALARM_CB(x) \
    (((ENGINE_ApplicationRec *)(x))->application.alarmCallback)

#define ENGINE_APP_PRE_FUNC(x) \
    (((ENGINE_ApplicationRec *)(x))->application.preFunc)

#define ENGINE_APP_POST_FUNC(x) \
    (((ENGINE_ApplicationRec *)(x))->application.postFunc)

#define ENGINE_APP_OPTIONS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.options)

#define ENGINE_APP_NUM_OPTIONS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.numOptions)

#define ENGINE_APP_LIB_CACHE(x) \
    (((ENGINE_ApplicationRec *)(x))->application.libCache)

#define ENGINE_APP_SUPPORT_LEVELS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.supportLevels)

#define ENGINE_APP_TRACE_LEVELS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.traceLevels)

#define ENGINE_APP_VENDOR_ONE_LEVELS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.vendorLevels1)

#define ENGINE_APP_VENDOR_TWO_LEVELS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.vendorLevels2)

#define ENGINE_APP_FEATURES(x) \
    (((ENGINE_ApplicationRec *)(x))->application.features)

#define ENGINE_APP_POOLS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.pools)

#define ENGINE_APP_SS7_STACK_MGMT(x) \
    (((ENGINE_ApplicationRec *)(x))->application.ss7StackMgmt)

#define ENGINE_APP_ISS7_STACK_CTRL(x) \
    (((ENGINE_ApplicationRec *)(x))->application.iss7StackControl)

#define ENGINE_APP_SIGTRAN_STACK_CTRL(x) \
    (((ENGINE_ApplicationRec *)(x))->application.sigtranStackControl)

#define ENGINE_APP_CODEC_STACK_CTRL(x) \
    (((ENGINE_ApplicationRec *)(x))->application.codecStackControl)

#define ENGINE_APP_PARSER_EXTENSIONS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.parserExtensions)

#define ENGINE_APP_RED_INFO(x) \
    (((ENGINE_ApplicationRec *)(x))->application.redundancyInfo)

#define ENGINE_APP_FAULT_TOLERANCE(x) \
    (((ENGINE_ApplicationRec *)(x))->application.faultTolerance)

#define ENGINE_APP_ROUTES(x) \
    (((ENGINE_ApplicationRec *)(x))->application.routes)

#define ENGINE_APP_LINK_SETS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.linkSets)

#define ENGINE_APP_DESTS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.destinations)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ApplicationClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ApplicationClass;

#define ENGINE_APP_PARSER_EXTENSIONS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.parserExtensions)

#define ENGINE_APP_RED_INFO(x) \
    (((ENGINE_ApplicationRec *)(x))->application.redundancyInfo)

#define ENGINE_APP_FAULT_TOLERANCE(x) \
    (((ENGINE_ApplicationRec *)(x))->application.faultTolerance)

#define ENGINE_APP_ROUTES(x) \
    (((ENGINE_ApplicationRec *)(x))->application.routes)

#define ENGINE_APP_LINK_SETS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.linkSets)

#define ENGINE_APP_DESTS(x) \
    (((ENGINE_ApplicationRec *)(x))->application.destinations)

#define ENGINE_APP_SIP(x) \
    (((ENGINE_ApplicationRec *)(x))->application.sipAttributes)

extern ITSDLLAPI ITS_ClassRec    itsENGINE_ApplicationClassRec;
extern ITSDLLAPI ITS_Class       itsENGINE_ApplicationClass;

/****************************************************************************/

/*
 * globals
 */
ITSDLLAPI extern ENGINE_Application application;

/*
 * the application pre and post callbacks don't have a defined
 * signature, so give them here.
 */
typedef void (*ENGINE_PrePostFunc)(void);

/*
 * the main API
 */
ITSDLLAPI extern void   ENGINE_Initialize(int argc,
                                          const char **argv,
                                          char *xmlData,
                                          int xmlSize);
ITSDLLAPI extern int    ENGINE_Run(int argc, const char **argv);

/*
 * change current setup
 */
ITSDLLAPI extern int    ENGINE_Diff(int argc, const char **argv,
                                    char *xmlData, int xmlSize);

/*
 * To save the current configuration
 */
ITSDLLAPI extern int ENGINE_Commit(char* filename,
                                   char** bakfile);

/*
 * mark the main loop for exiting.
 */
ITSDLLAPI extern void   ENGINE_Terminate();

#ifdef __cplusplus
}
#endif

#if !defined(DRIVER_IMPLEMENTATION)
#define DRVDLLAPI   ITSDLLAPI
#else
#if defined(WIN32)
#define DRVDLLAPI   __declspec(dllexport)
#else
#define DRVDLLAPI
#endif
#endif

/*
 * maximum number of any type of pool (future use)
 */
#define ENGINE_MAX_NUM_POOLS    8

#if !defined(USE_CPLUSPLUS)

#if defined(__cplusplus)
extern "C"
{
#endif

DRVDLLAPI extern TPOOL              *borderPool;
DRVDLLAPI extern TPOOL              *workerPool;
DRVDLLAPI extern WORKITEMPOOL       *workItemPool;
DRVDLLAPI extern DBC_Server         *debugConsole;

/*
 * special engine worker class
 */
/*
 * instance part
 */
typedef struct
{
    ITS_Object  configRec;
    void        *userData;
}
ENGINEWORKER_ObjectPart;

/*
 * instance record.  This needs to be rethought.  We should use
 * ITS_Object for ITS_THREAD and TPOOL_THREAD.
 */
typedef struct
{
    ITS_CoreObjectPart      core;
    ITS_ThreadPart          thread;
    TPOOL_ThreadObjectPart  tpool;
    WORKER_ObjectPart       worker;
    ENGINEWORKER_ObjectPart engine;
}
ENGINEWORKER_Control;

#define ENGINEWORKER_CONFIG_REC(x) \
    (((ENGINEWORKER_Control *)(x))->engine.configRec)

#define ENGINEWORKER_USER_DATA(x) \
    (((ENGINEWORKER_Control *)(x))->engine.userData)

DRVDLLAPI extern WORKER_ClassRec itsENGINEWORKER_ClassRec;
DRVDLLAPI extern ITS_Class       itsENGINEWORKER_Class;

DRVDLLAPI ENGINEWORKER_Control* ENGINEWORKER_InitWorker(
                                    int stackSize,
                                    const char *name,
                                    ITS_USHORT instance,
                                    ITS_UINT mask);
DRVDLLAPI void                  ENGINEWORKER_DeleteWorker(
                                    ENGINEWORKER_Control* worker);

DRVDLLAPI void                  ENGINEWORKER_SetUserData(
                                    ENGINEWORKER_Control *worker,
                                    void *data);
DRVDLLAPI void *                ENGINEWORKER_GetUserData(
                                    ENGINEWORKER_Control *worker);

typedef int (*Sig_Callback)(FILE*);

DRVDLLAPI void AddCommitCallback (char* prot, Sig_Callback sigC);

#if defined(__cplusplus)
}
#endif

#endif /* USE_CPLUSPLUS */

#endif /* _ENGINE_H_ */
