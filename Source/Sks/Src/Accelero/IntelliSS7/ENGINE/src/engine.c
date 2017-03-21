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
 * LOG: Revision 9.2.4.3  2006/02/23 06:35:57  sjaddu
 * LOG: Making va_args compatable to mvlppc.
 * LOG:
 * LOG: Revision 9.2.4.2  2005/09/16 15:32:48  lbana
 * LOG: Added MTP2 stack layer configuration.
 * LOG:
 * LOG: Revision 9.2.4.1  2005/08/29 09:20:40  adutta
 * LOG: BSSAP configuration
 * LOG:
 * LOG: Revision 9.2  2005/05/06 09:07:52  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:19  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/23 07:26:05  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.10.5.6.9  2005/02/10 13:08:59  snagesh
 * LOG: Fix to solve the issue of core dump when a signal is received or when the
 * LOG: MML m*_shutdown is executed(Bug 1439). Function ExtensionDestroy modified.
 * LOG: 2nd attempt to free ENGINE_PE_USER_DATA commented.
 * LOG:
 * LOG: Revision 7.8.10.5.6.8  2005/01/19 11:00:28  adutta
 * LOG: Retreiving M2UA data from xml
 * LOG:
 * LOG: Revision 7.8.10.5.6.7  2005/01/17 09:49:19  mkrishna
 * LOG: Separate traces for SIP
 * LOG:
 * LOG: Revision 7.8.10.5.6.6  2005/01/05 07:21:23  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.8.10.5.6.5  2005/01/04 13:46:44  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.8.10.5.6.4  2005/01/03 15:00:42  snagesh
 * LOG: Modifications for MTP2 vendor traces
 * LOG:
 * LOG: Revision 7.8.10.5.6.3  2004/12/28 13:12:09  mkrishna
 * LOG: SIP code propagated from Current Branch
 * LOG:
 * LOG: Revision 7.8.10.5.6.2  2004/12/16 01:48:58  randresol
 * LOG: Add JAPAN variant Implementation
 * LOG:
 * LOG: Revision 7.8.10.5.6.1  2004/12/15 12:37:32  asingh
 * LOG: separate traces for SCTP/UAL/M3UA
 * LOG:
 * LOG: Revision 7.8.10.5  2004/09/28 06:30:32  mmanikandan
 * LOG: Application not coming up on 6.4.1 bug resolved.
 * LOG:
 * LOG: Revision 7.8.10.4  2004/09/15 06:50:43  mmanikandan
 * LOG: Unnecessary log is removed.
 * LOG:
 * LOG: Revision 7.8.10.3  2004/09/15 05:27:33  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.8.10.2.2.1  2004/10/25 20:39:55  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.8.10.2  2004/07/26 10:18:45  sswami
 * LOG: Reverted all SIP changes.
 * LOG:
 * LOG: Revision 7.8.10.1  2004/07/20 06:06:24  mkrishna
 * LOG: SIP changes merged with PR6_3_GA_FT_HA
 * LOG:
 * LOG: Revision 7.8  2003/01/29 13:15:53  yranade
 * LOG: Missing argument inst to ConstructObject in function EndTransport.
 * LOG:
 * LOG: Revision 7.7  2003/01/09 11:28:19  yranade
 * LOG: Avoid a core dump, which otherwise happening if the variables are not
 * LOG: defined in the XML file
 * LOG:
 * LOG: Revision 7.6  2002/12/31 09:04:53  akumar
 * LOG: Code to Parse the XML file and dump it in DMP file for variables
 * LOG: exchange_type and segmentation_supported
 * LOG:
 * LOG: Revision 7.5  2002/12/26 22:31:21  mmiers
 * LOG: Let the user specify the instance if they really know what they're
 * LOG: doing.  Don't document this feature, it's mostly for us.
 * LOG:
 * LOG: Revision 7.4  2002/12/04 02:42:17  randresol
 * LOG: Add PRC mask for MTP2 modifier
 * LOG:
 * LOG: Revision 7.3  2002/09/26 22:59:44  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.2  2002/08/29 15:46:33  mmiers
 * LOG: Add the deselector to the DTD
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:41  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.23  2002/08/22 20:34:03  omayor
 * LOG: Missing CHINA in Getting the mask for GlobalStart.
 * LOG:
 * LOG: Revision 6.22  2002/08/22 14:32:43  mmiers
 * LOG: Add china dispatchers
 * LOG:
 * LOG: Revision 6.21  2002/08/12 23:05:07  randresol
 * LOG: fix bug in StartPool for the workItemPool creation
 * LOG:
 * LOG: Revision 6.20  2002/07/30 16:52:56  mmiers
 * LOG: Avoid a core dump
 * LOG:
 * LOG: Revision 6.19  2002/07/05 22:24:12  yranade
 * LOG: Fix flag bug.
 * LOG:
 * LOG: Revision 6.18  2002/07/02 21:26:36  mmiers
 * LOG: Work on getting debug console interface added to engine.
 * LOG:
 * LOG: Revision 6.17  2002/06/27 22:38:34  ssharma
 * LOG: Bug fix for family.
 * LOG:
 * LOG: Revision 6.16  2002/06/21 22:49:20  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.15  2002/05/31 20:42:05  mmiers
 * LOG: Fixes for concerned routes
 * LOG:
 * LOG: Revision 6.14  2002/05/20 15:21:41  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.13  2002/05/17 17:36:59  lbana
 * LOG: pass routing jkey value while constructing engine route object
 * LOG:
 * LOG: Revision 6.12  2002/05/15 16:27:55  hdivoux
 * LOG: Replaced functionName by function.
 * LOG:
 * LOG: Revision 6.11  2002/05/06 21:15:53  hdivoux
 * LOG: Cleanup after FT/HA integration.
 * LOG:
 * LOG: Revision 6.10  2002/04/30 15:31:20  hdivoux
 * LOG: Removed <<<<.
 * LOG:
 * LOG: Revision 6.9  2002/04/29 21:39:20  randresol
 * LOG: Add isInterNode flag in Border Transports definition
 * LOG:
 * LOG: Revision 6.8  2002/04/16 21:21:09  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.7  2002/04/15 21:06:58  hdivoux
 * LOG: Added configurable FtGroups.
 * LOG:
 * LOG: Revision 6.6  2002/04/09 22:45:44  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.5.2.1  2002/04/18 19:05:04  randresol
 * LOG: Add "isInterNode" field in Border Transports configuration
 * LOG:
 * LOG: Revision 6.5  2002/04/08 21:52:17  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.4  2002/04/05 23:29:19  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.3  2002/04/04 23:38:26  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 6.2  2002/03/14 16:20:36  mmiers
 * LOG: Typo in GDI parse code.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.26.2.1  2002/03/22 17:29:58  ssharma
 * LOG: Fix the ISUP Attributes section.
 * LOG:
 * LOG: Revision 5.26  2002/02/14 19:43:14  mmiers
 * LOG: Bug fixes
 * LOG:
 * LOG: Revision 5.25  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.24  2002/02/01 22:47:00  mmiers
 * LOG: Bad strings.
 * LOG:
 * LOG: Revision 5.23  2002/01/30 16:09:45  mmiers
 * LOG: Add termination function.
 * LOG:
 * LOG: Revision 5.22  2002/01/21 20:27:21  mmiers
 * LOG: Add distribution awareness.
 * LOG:
 * LOG: Revision 5.21  2002/01/10 20:30:36  mmiers
 * LOG: Add SAAL capability
 * LOG:
 * LOG: Revision 5.20  2001/11/20 17:58:34  mmiers
 * LOG: Add debug console.
 * LOG:
 * LOG: Revision 5.19  2001/11/15 23:53:55  mmiers
 * LOG: Today's testing of MTP3.
 * LOG:
 * LOG: Revision 5.18  2001/11/13 17:37:29  mmiers
 * LOG: Make it work with windows too.
 * LOG:
 * LOG: Revision 5.17  2001/11/13 17:28:23  mmiers
 * LOG: NDEBUG isn't defined by Forte.
 * LOG:
 * LOG: Revision 5.16  2001/10/19 22:45:12  mmiers
 * LOG: Use strings for variant names.
 * LOG:
 * LOG: Revision 5.15  2001/10/19 20:50:33  mmiers
 * LOG: Get MTP3 working with the engine.
 * LOG:
 * LOG: Revision 5.14  2001/10/18 22:06:42  mmiers
 * LOG: Add MTP2 capability to the SS7 dispatchers.
 * LOG:
 * LOG: Revision 5.13  2001/10/18 21:33:40  mmiers
 * LOG: Update engine to use destinations.
 * LOG:
 * LOG: Revision 5.12  2001/10/18 19:16:42  mmiers
 * LOG: Get engine in sync, add missing C++ guards in headers.
 * LOG:
 * LOG: Revision 5.11  2001/10/17 00:56:57  mmiers
 * LOG: Remove SLS stuff from engine.
 * LOG:
 * LOG: Revision 5.10  2001/10/16 20:25:07  hdivoux
 * LOG: Change in memset of static rinfo object to use sizeof of correct type.
 * LOG:
 * LOG: Revision 5.9  2001/10/02 21:44:10  mmiers
 * LOG: Dead route style removal.
 * LOG:
 * LOG: Revision 5.8  2001/09/24 21:37:17  mmiers
 * LOG: ENGINE link, linkSet, C++ API.
 * LOG:
 * LOG: Revision 5.7  2001/09/21 16:23:14  hdivoux
 * LOG: Update for comments.
 * LOG:
 * LOG: Revision 5.6  2001/09/20 19:16:15  hdivoux
 * LOG: Update for XML GCS configuration attributes.
 * LOG:
 * LOG: Revision 5.5  2001/08/31 14:23:09  mmiers
 * LOG: Brainstorming on MTP3, routing fixes.
 * LOG:
 * LOG: Revision 5.4  2001/08/24 17:10:24  mmiers
 * LOG: Routing, take three.
 * LOG:
 * LOG: Revision 5.3  2001/08/20 23:28:40  mmiers
 * LOG: Finish route work.
 * LOG:
 * LOG: Revision 5.2  2001/08/20 22:50:54  mmiers
 * LOG: Get this in line with new routing scheme.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:15  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.31  2001/08/14 15:26:45  mmiers
 * LOG: Add link priority.
 * LOG:
 * LOG: Revision 4.30  2001/08/13 20:42:00  mmiers
 * LOG: Add routing key.
 * LOG:
 * LOG: Revision 4.29  2001/08/10 19:53:08  lbana
 * LOG: Remove tabs.
 * LOG:
 * LOG: Revision 4.28  2001/08/10 19:43:18  lbana
 * LOG: Add break when handling parser extension.
 * LOG:
 * LOG: Revision 4.27  2001/08/10 17:00:39  mmiers
 * LOG: Macro abuse.
 * LOG:
 * LOG: Revision 4.26  2001/08/07 14:59:28  mmiers
 * LOG: Fix numThreads leakage.
 * LOG:
 * LOG: Revision 4.25  2001/07/26 16:49:41  mmiers
 * LOG: UAL needed engine parse help.  Added this as an example.
 * LOG:
 * LOG: Revision 4.24  2001/07/25 23:41:26  mmiers
 * LOG: Diff's about done.
 * LOG:
 * LOG: Revision 4.23  2001/07/23 22:17:13  mmiers
 * LOG: Finish the equality checks.  Finish up diff tomorrow.
 * LOG:
 * LOG: Revision 4.22  2001/07/19 22:02:40  mmiers
 * LOG: Continue adding equality checks.
 * LOG:
 * LOG: Revision 4.21  2001/07/19 16:58:33  mmiers
 * LOG: Make RM not bomb if ss7RM not present.  Continue diff.
 * LOG:
 * LOG: Revision 4.20  2001/07/18 23:10:35  mmiers
 * LOG: Fix a few cut/paste bugs Sandeep found.  Add info on the extensions
 * LOG: (will move to document end of PR5 devel).
 * LOG:
 * LOG: Revision 4.19  2001/07/18 21:43:41  mmiers
 * LOG: Start committing the buildable diff parts.
 * LOG:
 * LOG: Revision 4.18  2001/07/05 22:48:00  mmiers
 * LOG: Update for DMA.  Need to finish timers.
 * LOG:
 * LOG: Revision 4.17  2001/06/22 21:01:06  mmiers
 * LOG: Finish integrating DSM and RM.  Need to add PeerDead notification
 * LOG: to complete.
 * LOG:
 * LOG: Revision 4.16  2001/06/22 18:33:27  mmiers
 * LOG: Move DSM to ENGINE.
 * LOG:
 * LOG: Revision 4.15  2001/06/21 15:18:19  mmiers
 * LOG: Add HMI and Alarm.
 * LOG:
 * LOG: Revision 4.14  2001/06/18 20:24:46  mmiers
 * LOG: Add diff framework.  Need to implement.
 * LOG:
 * LOG: Revision 4.13  2001/06/18 19:52:08  mmiers
 * LOG: Add parser extensions, work on HMI a bit.
 * LOG:
 * LOG: Revision 4.12  2001/06/16 00:35:47  mmiers
 * LOG: Don't keep the handle around.
 * LOG:
 * LOG: Revision 4.11  2001/06/16 00:05:32  mmiers
 * LOG: Add redundancy info
 * LOG:
 * LOG: Revision 4.10  2001/06/14 23:17:25  mmiers
 * LOG: Add redundancy info
 * LOG:
 * LOG: Revision 4.9  2001/06/12 21:01:56  mmiers
 * LOG: Forgot to set the routes.
 * LOG:
 * LOG: Revision 4.8  2001/05/10 22:50:34  mmiers
 * LOG: Add AppOptions
 * LOG:
 * LOG: Revision 4.7  2001/05/10 22:37:14  mmiers
 * LOG: Better naming for work items.
 * LOG:
 * LOG: Revision 4.6  2001/05/10 21:05:51  mmiers
 * LOG: Add pre/post func to obj create.
 * LOG:
 * LOG: Revision 4.5  2001/05/10 17:00:31  mmiers
 * LOG: Forgot to parse UI cbs.
 * LOG:
 * LOG: Revision 4.4  2001/05/10 16:51:44  mmiers
 * LOG: User requested stuff (user intervention).
 * LOG:
 * LOG: Revision 4.3  2001/05/10 00:28:12  mmiers
 * LOG: Add custom dispatch.
 * LOG:
 * LOG: Revision 4.2  2001/05/09 23:19:48  mmiers
 * LOG: PR4 requests.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:02  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.2  2001/04/29 00:05:39  mmiers
 * LOG: A few changes required by the validating parser.
 * LOG:
 * LOG: Revision 1.1  2001/04/28 23:38:20  mmiers
 * LOG: Rearrange this to standard form.
 * LOG:
 * LOG: Revision 1.7  2001/04/27 21:42:53  yranade
 * LOG: Missing check for NULL after resolve.
 * LOG:
 * LOG: Revision 1.6  2001/04/26 16:01:22  mmiers
 * LOG: Spew error messages.
 * LOG:
 * LOG: Revision 1.5  2001/04/26 00:35:27  mmiers
 * LOG: Make the library name optional (resolve within the executable if
 * LOG: possible).
 * LOG:
 * LOG: Revision 1.4  2001/04/25 00:21:04  mmiers
 * LOG: Missing callback.
 * LOG:
 * LOG: Revision 1.3  2001/04/19 19:21:51  labuser
 * LOG: Debug.  Need to supply resources even for ITER
 * LOG:
 * LOG: Revision 1.2  2001/04/18 20:17:34  mmiers
 * LOG: Update the driver project files and add preAccept.
 * LOG:
 * LOG: Revision 1.1  2001/04/12 20:10:26  salaoui
 * LOG: Move to a more logical location.
 * LOG:
 * LOG: Revision 1.44  2001/04/12 19:13:41  labuser
 * LOG: Debugging with Yogesh.
 * LOG:
 * LOG: Revision 1.43  2001/04/06 17:48:58  mmiers
 * LOG: Updates.
 * LOG:
 * LOG: Revision 1.42  2001/04/05 23:07:00  mmiers
 * LOG: Debugging C++ API.
 * LOG:
 * LOG: Revision 1.41  2001/04/04 01:15:23  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.40  2001/04/03 23:56:47  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.39  2001/04/03 22:13:17  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.38  2001/04/03 20:38:06  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 1.37  2001/04/02 23:36:31  mmiers
 * LOG: Remove printf.
 * LOG:
 * LOG: Revision 1.36  2001/04/02 23:36:11  mmiers
 * LOG: PIC
 * LOG:
 * LOG: Revision 1.35  2001/04/02 21:21:51  mmiers
 * LOG: Align strings with parser.
 * LOG:
 * LOG: Revision 1.34  2001/04/02 19:50:41  mmiers
 * LOG: Solaris cleanup.
 * LOG:
 * LOG: Revision 1.33  2001/03/30 23:38:00  mmiers
 * LOG: More engine debugging.
 * LOG:
 * LOG: Revision 1.32  2001/03/30 21:03:34  mmiers
 * LOG: Testing.
 * LOG:
 * LOG: Revision 1.31  2001/03/29 18:21:15  mmiers
 * LOG: Debugging the engine.  Runs now.
 * LOG:
 * LOG: Revision 1.30  2001/03/29 17:36:10  mmiers
 * LOG: Make shared libs.
 * LOG:
 * LOG: Revision 1.29  2001/03/29 03:07:33  mmiers
 * LOG: Start debugging.
 * LOG:
 * LOG: Revision 1.28  2001/03/28 23:37:42  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 1.27  2001/03/28 22:38:29  mmiers
 * LOG: It is coded.
 * LOG:
 * LOG: Revision 1.26  2001/03/28 00:44:26  mmiers
 * LOG: Finish management.
 * LOG:
 * LOG: Revision 1.25  2001/03/28 00:18:16  mmiers
 * LOG: Finish up the parser.  TODO: write config object for IntelliNet
 * LOG: stack.  Tomorrow.
 * LOG:
 * LOG: Revision 1.24  2001/03/27 01:58:40  mmiers
 * LOG: Add options, sanitize the XML.  Need to do features and windows.
 * LOG:
 * LOG: Revision 1.23  2001/03/26 23:02:15  mmiers
 * LOG: Today's installment.  Now that I'm caught up on email, I should
 * LOG: be able to finish the parser tomorrow.
 * LOG:
 * LOG: Revision 1.22  2001/03/17 01:12:15  mmiers
 * LOG: Small cleanups for portability.
 * LOG:
 * LOG: Revision 1.21  2001/03/16 20:56:07  mmiers
 * LOG:
 * LOG: Ok, only resdb and parsing left.
 * LOG:
 * LOG: Revision 1.20  2001/03/15 23:17:04  mmiers
 * LOG: Implement the pools.  TODO is Worker and WorkItem (and CPP bindings).
 * LOG: Finish tomorrow.
 * LOG:
 * LOG: Revision 1.19  2001/03/15 01:27:10  mmiers
 * LOG: Updates for portability (fsm).  I think these were required anyway,
 * LOG: but VC doesn't complain if they aren't there.  The rest is thinking
 * LOG: about the thread pools.  I think I have a handle on this if I can
 * LOG: remember it tomorrow.  The comments should help.
 * LOG:
 * LOG: Revision 1.18  2001/03/14 23:44:01  mmiers
 * LOG: Build the pools and parsing is all that's left.
 * LOG:
 * LOG: Revision 1.17  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 1.16  2001/03/14 01:58:37  mmiers
 * LOG: Work on the implementation.  If I could get 3-4 uninterrupted
 * LOG: hours, this would be done.  TODO: the trace levels and the
 * LOG: thread pools.  The only other thing to do is the syntax tree
 * LOG: creator.
 * LOG:
 * LOG: Revision 1.15  2001/03/13 23:30:17  mmiers
 * LOG: A touchup.
 * LOG:
 * LOG: Revision 1.14  2001/03/13 23:21:13  mmiers
 * LOG: Various updates for the engine.
 * LOG:
 * LOG: Revision 1.13  2001/03/13 00:37:32  mmiers
 * LOG: All DLLs built.
 * LOG:
 * LOG: Revision 1.12  2001/03/09 22:55:42  mmiers
 * LOG: Finish up the infrastructure changes.  The engine will get built
 * LOG: over the weekend.
 * LOG:
 * LOG: Revision 1.11  2001/03/09 21:26:23  mmiers
 * LOG: Get DLL linkage working.
 * LOG:
 * LOG: Revision 1.10  2001/03/02 22:44:14  mmiers
 * LOG: DLSYM needs to be in CORE.  CORE and ENGINE will be present
 * LOG: always.  The rest will be loaded on demand.
 * LOG:
 * LOG: Revision 1.9  2001/03/02 21:53:29  mmiers
 * LOG: Add management and stack objects.
 * LOG:
 * LOG: Revision 1.8  2001/03/02 20:56:06  mmiers
 * LOG: Add the WorkItemPool.
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

#include <its.h>

#ident "$Id: engine.c,v 1.1.1.1 2007-10-08 11:11:16 bsccs2 Exp $"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include <engine.h>
#include <expat.h>
#include "engine_intern.h"

ITSDLLAPI ENGINE_Application    application = NULL;

static ENGINE_Application       tmpApp = NULL;
static ENGINE_LibCache          driver = NULL;

static XML_Parser   parser;

/*
 * forward
 */
static ITS_Object   curLayer = NULL;
static ITS_BOOLEAN  inParser = ITS_FALSE;
static ITS_Object   curSigLayer = NULL;
static ITS_Object   curCodecLayer = NULL;
static ITS_Object curSIPAttr = NULL;

#undef ITS_C_ASSERT
#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
        if (inParser)                                                         \
        {                                                                     \
            fprintf(stderr, "At around line %d column %d in parsed text.\n",  \
                    XML_GetCurrentLineNumber(parser),                         \
                    XML_GetCurrentColumnNumber(parser));                      \
        }                                                                     \
        abort();                                                              \
    }

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a lib cache object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LibCacheClass, app, libName);
 *
 *  See Also:
 ****************************************************************************/
static int
CacheCreate(ITS_Object obj, va_list args)
{
    char *libName, buf[ITS_PATH_MAX];
    ENGINE_LibCache crec = (ENGINE_LibCache)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);

    ITS_C_REQUIRE(app != NULL);

    /* init the rec */
    ENGINE_LC_NEXT(crec) = NULL;
    ENGINE_LC_APP(crec) = app;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_LC_LIB_NAME(crec) = strdup(libName);

        ITS_C_ASSERT(ENGINE_LC_LIB_NAME(crec) != NULL);
    }

    /* lookup local */
    ENGINE_LC_LIBRARY(crec) = DLSYM_Create(ENGINE_LC_LIB_NAME(crec));

    /* if not found, try global */
    if (ENGINE_LC_LIBRARY(crec) == NULL)
    {
        strcpy(buf, APPL_GetLibDir());
        strcat(buf, ENGINE_LC_LIB_NAME(crec));

        ENGINE_LC_LIBRARY(crec) = DLSYM_Create(buf);

        if (ENGINE_LC_LIBRARY(crec) == NULL)
        {
            free(ENGINE_LC_LIB_NAME(crec));

            return (ITS_ENOTFOUND);
        }
    }

    /* tail add */
    for (list = &ENGINE_APP_LIB_CACHE(app);
         *list;
         list = &ENGINE_LC_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a lib cache object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
CacheDestroy(ITS_Object obj)
{
    ENGINE_LibCache crec = (ENGINE_LibCache)obj;

    DLSYM_Destroy(ENGINE_LC_LIBRARY(crec));

    if (ENGINE_LC_LIB_NAME(crec))
    {
        free(ENGINE_LC_LIB_NAME(crec));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare cache records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CacheCompare(ITS_Object o1, ITS_Object o2)
{
    /* init the rec */
    if ((!ENGINE_LC_LIB_NAME(o1) && !ENGINE_LC_LIB_NAME(o2)) ||
        (ENGINE_LC_LIB_NAME(o1) && ENGINE_LC_LIB_NAME(o2) &&
         !strlen(ENGINE_LC_LIB_NAME(o1)) && !strlen(ENGINE_LC_LIB_NAME(o2))) ||
        (ENGINE_LC_LIB_NAME(o1) && ENGINE_LC_LIB_NAME(o2) &&
         strlen(ENGINE_LC_LIB_NAME(o1)) && strlen(ENGINE_LC_LIB_NAME(o2)) &&
         strcmp(ENGINE_LC_LIB_NAME(o1), ENGINE_LC_LIB_NAME(o2)) == 0))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LibCacheClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LibCacheRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Lib Cache Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CacheCreate,                    /* instantiate */
        CacheDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CacheCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LibCacheClass = &itsENGINE_LibCacheClassRec;

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find (or create) a library within this application
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ENGINE_LibCache
ENGINE_LibGet(ENGINE_Application app, const char *libName)
{
    ITS_Object list;
    ENGINE_LibCache tmp;

    list = ENGINE_APP_LIB_CACHE(app);

    while (list != NULL)
    {
        if (libName == NULL && ENGINE_LC_LIB_NAME(list) == NULL)
        {
            return ((ENGINE_LibCache)list);
        }

        if (libName && ENGINE_LC_LIB_NAME(list) &&
            strcmp(ENGINE_LC_LIB_NAME(list), libName) == 0)
        {
            return ((ENGINE_LibCache)list);
        }

        list = ENGINE_LC_NEXT(list);
    }

    tmp = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                               app, libName);

    if (tmp == NULL &&
        (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
         SERVICE_GetType() == ST_NOT_SET))
    {
        printf("Error loading library: %s\n", DLSYM_Error());
        fflush(stdout);
    }

    return (tmp);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a parser extension object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ParserExtensionClass, app,
 *                          "libNMS.so", "NMS-Data"
 *                          "NMS_ParseStart", "NMS_ParseEnd",
 *                          "NMS_ConvertParserData");
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  04-04-2005  Bug ID:1763
 *
 *  See Also:
 ****************************************************************************/
static int
ExtensionCreate(ITS_Object obj, va_list args)
{
    char *libName, *elemName;
    char *start = NULL, *stop = NULL, *xlate = NULL, *diff = NULL, *commit = NULL;
    ENGINE_ParserExtension pext = (ENGINE_ParserExtension)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);
    elemName = va_arg(args, char *);
    start = va_arg(args, char *);
    stop = va_arg(args, char *);
    xlate = va_arg(args, char *);
    diff = va_arg(args, char *);
    commit = va_arg(args, char*);

    ITS_C_REQUIRE(app != NULL);
    ITS_C_REQUIRE(elemName != NULL && strlen(elemName) != 0);

    ENGINE_PE_NEXT(pext) = NULL;
    ENGINE_PE_ELEMENT_NAME(pext) = strdup(elemName);
    ENGINE_PE_LIB_CACHE_ENTRY(pext) = ENGINE_LibGet(app, libName);
    ENGINE_PE_USER_DATA(pext) = NULL;

    ITS_C_ASSERT(ENGINE_PE_ELEMENT_NAME(pext) != NULL);
    ITS_C_ASSERT(ENGINE_PE_LIB_CACHE_ENTRY(pext) != NULL);

    if (start == NULL && stop == NULL && xlate == NULL)
    {
        printf("Are you kidding me?\n");

        return (ITS_EINVALIDARGS);
    }

    if (start && strlen(start) != 0)
    {
        ENGINE_PE_START_FUNC(pext) = (ENGINE_ParseStartFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          start);

        if (ENGINE_PE_START_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       start, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_START_FUNC_NAME(pext) = strdup(start);
        }
    }
    if (stop && strlen(stop) != 0)
    {
        ENGINE_PE_STOP_FUNC(pext) = (ENGINE_ParseStopFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          stop);

        if (ENGINE_PE_STOP_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       stop, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_STOP_FUNC_NAME(pext) = strdup(stop);
        }
    }
    if (xlate && strlen(xlate) != 0)
    {
        ENGINE_PE_XLATE_FUNC(pext) = (ENGINE_ResourceXlateFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          xlate);

        if (ENGINE_PE_XLATE_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       xlate, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_XLATE_FUNC_NAME(pext) = strdup(xlate);
        }
    }
    if (diff && strlen(diff) != 0)
    {
        ENGINE_PE_DIFF_FUNC(pext) = (ENGINE_ExtensionDiffFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          diff);

        if (ENGINE_PE_DIFF_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       diff, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_DIFF_FUNC_NAME(pext) = strdup(diff);
        }
    }

    if (commit && strlen(commit) != 0)
    {
        ENGINE_PE_COMMIT_FUNC(pext) = (ENGINE_ExtensionCommitFunc)
            DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_PE_LIB_CACHE_ENTRY(pext)),
                          commit);

        if (ENGINE_PE_COMMIT_FUNC(pext) == NULL)
        {
            if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
                SERVICE_GetType() == ST_NOT_SET)
            {
                printf("Error resolving symbol %s : %s\n",
                       commit, DLSYM_Error());
                fflush(stdout);
            }

            return (ITS_ENOTFOUND);
        }
        else
        {
            ENGINE_PE_COMMIT_FUNC_NAME(pext) = strdup(commit);
        }
    }

    /* tail add */
    for (list = &ENGINE_APP_PARSER_EXTENSIONS(app);
         *list;
         list = &ENGINE_PE_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ExtensionDestroy(ITS_Object obj)
{
    ENGINE_ParserExtension pext = (ENGINE_ParserExtension)obj;

    free(ENGINE_PE_ELEMENT_NAME(pext));
    if (ENGINE_PE_USER_DATA(pext))
    {
        free(ENGINE_PE_USER_DATA(pext));
    }

    if (ENGINE_PE_START_FUNC_NAME(pext))
    {
        free(ENGINE_PE_START_FUNC_NAME(pext));
    }

    if (ENGINE_PE_STOP_FUNC_NAME(pext))
    {
        free(ENGINE_PE_STOP_FUNC_NAME(pext));
    }

    if (ENGINE_PE_XLATE_FUNC_NAME(pext))
    {
        free(ENGINE_PE_XLATE_FUNC_NAME(pext));
    }

    if (ENGINE_PE_DIFF_FUNC_NAME(pext))
    {
        free(ENGINE_PE_DIFF_FUNC_NAME(pext));
    }

#if 0
    if (ENGINE_PE_USER_DATA(pext))
    {
        free(ENGINE_PE_USER_DATA(pext));
    }
#endif

    if (ENGINE_PE_ELEMENT_DATA(pext))
    {
        int idx;
        for (idx = 0;
             idx < ENGINE_PE_ELEMENT_DATA_COUNT(pext);
             idx++)
        {
            free(ENGINE_PE_ELEMENT_DATA(pext)[idx]);
        }
        free(ENGINE_PE_ELEMENT_DATA(pext));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare extension records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ExtensionCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_PE_ELEMENT_NAME(o1) == NULL) ^ 
         (ENGINE_PE_ELEMENT_NAME(o2) == NULL)) ||
        (ENGINE_PE_ELEMENT_NAME(o1) &&
         strcmp(ENGINE_PE_ELEMENT_NAME(o1),
                ENGINE_PE_ELEMENT_NAME(o2)) != 0) ||
        ENGINE_PE_LIB_CACHE_ENTRY(o1) != ENGINE_PE_LIB_CACHE_ENTRY(o2) ||
        ENGINE_PE_START_FUNC(o1) != ENGINE_PE_START_FUNC(o2) ||
        ENGINE_PE_STOP_FUNC(o1) != ENGINE_PE_STOP_FUNC(o2) ||
        ENGINE_PE_XLATE_FUNC(o1) != ENGINE_PE_XLATE_FUNC(o2) ||
        ENGINE_PE_DIFF_FUNC(o1) != ENGINE_PE_DIFF_FUNC(o2))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ParserExtensionClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ParserExtensionRec),/* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Extension Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ExtensionCreate,                /* instantiate */
        ExtensionDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ExtensionCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ParserExtensionClass =
    &itsENGINE_ParserExtensionClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_FeatureClass, app, "SCTP",
 *                          "libSCTP.so", "itsSCTP_Class",
 *                          options, numOptions);
 *
 *  See Also:
 ****************************************************************************/
static int
FeatureCreate(ITS_Object obj, va_list args)
{
    char *featName, *libName, *className, **options;
    ENGINE_Feature feat = (ENGINE_Feature)obj;
    ENGINE_Application app;
    ITS_Object *list, tail;
    int numOptions;
    ITS_Class *cl;

    app = va_arg(args, ENGINE_Application);
    featName = va_arg(args, char *);
    libName = va_arg(args, char *);
    className = va_arg(args, char *);
    options = va_arg(args, char **);
    numOptions = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);
    ITS_C_REQUIRE(featName != NULL && strlen(featName) != 0);
    ITS_C_REQUIRE(className != NULL && strlen(className) != 0);
    if (numOptions)
    {
        ITS_C_REQUIRE(options != NULL);
    }

    ENGINE_FEAT_NEXT(feat) = NULL;
    ENGINE_FEAT_PREV(feat) = NULL;
    ENGINE_FEAT_APP(feat) = app;
    ENGINE_FEAT_NAME(feat) = strdup(featName);
    ENGINE_FEAT_CLASS_NAME(feat)=strdup(className);
    ENGINE_FEAT_LIB_CACHE_ENTRY(feat) = ENGINE_LibGet(app, libName);

    ITS_C_ASSERT(ENGINE_FEAT_NAME(feat) != NULL);
    ITS_C_ASSERT(ENGINE_FEAT_LIB_CACHE_ENTRY(feat) != NULL);

    cl = (ITS_Class *)
        DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_FEAT_LIB_CACHE_ENTRY(feat)),
                      className);

    if (cl == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   className, DLSYM_Error());
            fflush(stdout);
        }

        return (ITS_ENOTFOUND);
    }

    ENGINE_FEAT_CLASS_REC(feat) = *cl;

    ENGINE_FEAT_OPTIONS(feat) = options;
    ENGINE_FEAT_NUM_OPTIONS(feat) = numOptions;

    /* tail add */
    for (list = &ENGINE_APP_FEATURES(app), tail = ENGINE_APP_FEATURES(app);
         *list;
         tail = *list, list = &ENGINE_FEAT_NEXT(*list))
    {
    }
    *list = obj;
    ENGINE_FEAT_PREV(feat) = tail;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
FeatureDestroy(ITS_Object obj)
{
    ENGINE_Feature feat = (ENGINE_Feature)obj;
    int i;

    free(ENGINE_FEAT_NAME(feat));

    if (ENGINE_FEAT_CLASS_NAME(feat))
    {
        free(ENGINE_FEAT_CLASS_NAME(feat));
    }

    if (ENGINE_FEAT_NUM_OPTIONS(feat))
    {
        for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(feat); i++)
        {
            free(ENGINE_FEAT_OPTIONS(feat)[i]);
        }

        free(ENGINE_FEAT_OPTIONS(feat));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FeatureCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (strcmp(ENGINE_FEAT_NAME(o1), ENGINE_FEAT_NAME(o2)) != 0 ||
        ENGINE_FEAT_LIB_CACHE_ENTRY(o1) != ENGINE_FEAT_LIB_CACHE_ENTRY(o2) ||
        ENGINE_FEAT_CLASS_REC(o1) != ENGINE_FEAT_CLASS_REC(o2) ||
        ENGINE_FEAT_NUM_OPTIONS(o1) != ENGINE_FEAT_NUM_OPTIONS(o2))
    {
        return (ITS_FALSE);
    }

    for (i = 0; i < ENGINE_FEAT_NUM_OPTIONS(o1); i++)
    {
        if (strcmp(ENGINE_FEAT_OPTIONS(o1)[i],
                   ENGINE_FEAT_OPTIONS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_FeatureClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_FeatureRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Feature Class",         /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        FeatureCreate,                  /* instantiate */
        FeatureDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        FeatureCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FeatureClass = &itsENGINE_FeatureClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a trace config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TraceClass, traceList, "levelName",
 *                          levelMask);
 *
 *  See Also:
 ****************************************************************************/
static int
TraceCreate(ITS_Object obj, va_list args)
{
    char *levelName;
    ENGINE_Trace trace = (ENGINE_Trace)obj;
    ITS_Object* traceList;
    int levelMask;
    ITS_Object *list;

    traceList = va_arg(args, ITS_Object *);
    levelName = va_arg(args, char *);
    levelMask = va_arg(args, int);

    ITS_C_REQUIRE(traceList != NULL);
    ITS_C_REQUIRE(levelName != NULL && strlen(levelName) != 0);
    ITS_C_REQUIRE(levelMask != 0);

    ENGINE_TL_NEXT(trace) = NULL;
    ENGINE_TL_LEVEL_NAME(trace) = strdup(levelName);
    ENGINE_TL_LEVEL_MASK(trace) = levelMask;

    ITS_C_ASSERT(ENGINE_TL_LEVEL_NAME(trace) != NULL);

    /* tail add */
    for (list = traceList;
         *list;
         list = &ENGINE_TL_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a trace config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
TraceDestroy(ITS_Object obj)
{
    ENGINE_Trace trace = (ENGINE_Trace)obj;

    free(ENGINE_TL_LEVEL_NAME(trace));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare trace records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TraceCompare(ITS_Object o1, ITS_Object o2)
{
    /*
     * don't bother with this.  It's simpler just to adjust the trace levels
     */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TraceClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_TraceRec),        /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Trace Class",           /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        TraceCreate,                    /* instantiate */
        TraceDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        TraceCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TraceClass = &itsENGINE_TraceClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_RouteClass, application, pointCode,
 *                          type, style, ...);
 *
 *  See Also:
 ****************************************************************************/
static int
RouteCreate(ITS_Object obj, va_list args)
{
    ENGINE_Route route = (ENGINE_Route)obj;
    ITS_UINT pointCode, mask;
    ROUTE_TYPE type;
    ROUTE_CRITERIA style;
    SS7_Family family;
    ENGINE_Application app;
    ITS_Object *list;
    int ret;
    va_list *targs = NULL; 

    app = va_arg(args, ENGINE_Application);
    mask = va_arg(args, ITS_UINT);
    pointCode = va_arg(args, ITS_UINT);
    type = va_arg(args, ROUTE_TYPE);
    style = va_arg(args, ROUTE_CRITERIA);
    family = va_arg(args, SS7_Family);

    ITS_C_ASSERT(app != NULL);

    ENGINE_RT_NEXT(route) = NULL;

    targs = (va_list *)malloc(sizeof(args));
    __va_copy(*targs, args);
    ret = ROUTE_ParseRouteMatchInfo(&ENGINE_RT_INFO(route), pointCode,
                                    type, style, family, targs);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ENGINE_RT_INFO(route).basic.mask = mask;

    /* tail add */
    for (list = &ENGINE_APP_ROUTES(app);
         *list;
         list = &ENGINE_RT_NEXT(*list))
    {
    }
    *list = obj;

    free(targs);
    targs = NULL;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
RouteDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare route records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
RouteCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_RT_INFO(o1).basic.type != ENGINE_RT_INFO(o2).basic.type ||
        ENGINE_RT_INFO(o1).basic.style != ENGINE_RT_INFO(o2).basic.style ||
        ENGINE_RT_INFO(o1).basic.dpc != ENGINE_RT_INFO(o2).basic.dpc ||
        ENGINE_RT_INFO(o1).priority != ENGINE_RT_INFO(o2).priority)
    {
        return (ITS_FALSE);
    }

    switch (ENGINE_RT_INFO(o1).basic.style)
    {
    case ROUTE_DPC_NI:
        if ((ENGINE_RT_INFO(o1).basic.criteria.sio & ROUTE_NI_MASK) !=
            (ENGINE_RT_INFO(o2).basic.criteria.sio & ROUTE_NI_MASK))
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_NI:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            (ENGINE_RT_INFO(o1).basic.criteria.sio & ROUTE_NI_MASK) !=
            (ENGINE_RT_INFO(o2).basic.criteria.sio & ROUTE_NI_MASK))
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_SSN_RANGE:
    case ROUTE_DPC_SIO_CIC_RANGE:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.range.begin !=
            ENGINE_RT_INFO(o2).basic.criteria.range.begin ||
            ENGINE_RT_INFO(o1).basic.criteria.range.end !=
            ENGINE_RT_INFO(o2).basic.criteria.range.end)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_SSN:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.ssn !=
            ENGINE_RT_INFO(o2).basic.criteria.ssn)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_SIO_CIC:
        if (ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.cic !=
            ENGINE_RT_INFO(o2).basic.criteria.cic)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.range.begin !=
            ENGINE_RT_INFO(o2).basic.criteria.range.begin ||
            ENGINE_RT_INFO(o1).basic.criteria.range.end !=
            ENGINE_RT_INFO(o2).basic.criteria.range.end)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_SSN:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.ssn !=
            ENGINE_RT_INFO(o2).basic.criteria.ssn)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_OPC_SIO_CIC:
        if (ENGINE_RT_INFO(o1).basic.criteria.opc !=
            ENGINE_RT_INFO(o2).basic.criteria.opc ||
            ENGINE_RT_INFO(o1).basic.criteria.sio !=
            ENGINE_RT_INFO(o2).basic.criteria.sio ||
            ENGINE_RT_INFO(o1).basic.criteria.cic !=
            ENGINE_RT_INFO(o2).basic.criteria.cic)
        {
            return (ITS_FALSE);
        }
        return (ITS_TRUE);

    case ROUTE_DPC_UDEF:
        return (ITS_FALSE);

    default:
        return (ITS_FALSE);
    }
    
    /* NOTREACHED */
}

ITSDLLAPI ITS_ClassRec itsENGINE_RouteClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_RouteRec),        /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Route Class",           /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        RouteCreate,                    /* instantiate */
        RouteDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        RouteCompare,                   /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_RouteClass = &itsENGINE_RouteClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_DestinationClass, app,
 *                          pointCode, ni,
 *                          mtp3Var, isupVar, sccpVar, tcapVar,
 *                          tupVar, dupVar);
 *
 *  See Also:
 ****************************************************************************/
static int
DestCreate(ITS_Object obj, va_list args)
{
    ENGINE_Dest dest = (ENGINE_Dest)obj;
    ENGINE_Application app;
    ITS_Object *list;
    char *isupVar;

    app = va_arg(args, ENGINE_Application);
    ENGINE_DE_PC(dest) = va_arg(args, ITS_UINT);
    ENGINE_DE_NI(dest) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_DE_FAMILY(dest) = va_arg(args, SS7_Family);
    ENGINE_DE_MTP3(dest) = va_arg(args, ITS_INT);
    isupVar = va_arg(args, char *);
    ENGINE_DE_SCCP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_TCAP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_TUP(dest) = va_arg(args, ITS_INT);
    ENGINE_DE_DUP(dest) = va_arg(args, ITS_INT);

    ITS_C_ASSERT(app != NULL);

    if (isupVar)
    {
        ENGINE_DE_ISUP(dest) = strdup(isupVar);
        if (ENGINE_DE_ISUP(dest) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    ENGINE_DE_NEXT(dest) = NULL;

    /* tail add */
    for (list = &ENGINE_APP_DESTS(app);
         *list;
         list = &ENGINE_DE_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DestDestroy(ITS_Object obj)
{
    if (ENGINE_DE_ISUP(obj))
    {
        free(ENGINE_DE_ISUP(obj));
    }

    if (ENGINE_DE_ISUP_ATTR(obj))
    {
        ITS_DestructObject(ENGINE_DE_ISUP_ATTR(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare route records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
DestCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_DE_PC(o1) == ENGINE_DE_PC(o2) &&
        ENGINE_DE_NI(o1) == ENGINE_DE_NI(o2) &&
        ENGINE_DE_FAMILY(o1) == ENGINE_DE_FAMILY(o2) &&
        ENGINE_DE_MTP3(o1) == ENGINE_DE_MTP3(o2) &&
        (ENGINE_DE_ISUP(o1) != NULL && ENGINE_DE_ISUP(o2) != NULL &&
         strcmp(ENGINE_DE_ISUP(o1), ENGINE_DE_ISUP(o2)) == 0) &&
        ENGINE_DE_SCCP(o1) == ENGINE_DE_SCCP(o2) &&
        ENGINE_DE_TCAP(o1) == ENGINE_DE_TCAP(o2) &&
        ENGINE_DE_TUP(o1) == ENGINE_DE_TUP(o2) &&
        ENGINE_DE_DUP(o1) == ENGINE_DE_DUP(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_DestClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_DestRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Dest Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        DestCreate,                     /* instantiate */
        DestDestroy,                    /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        DestCompare,                    /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_DestClass = &itsENGINE_DestClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an isup timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISUPTimerClass, isupAttributes,
 *                          id, value, handler);
 *
 *  See Also:
 ****************************************************************************/
static int
ISUPTimerCreate(ITS_Object obj, va_list args)
{
    ENGINE_ISUPTimer timer = (ENGINE_ISUPTimer)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *id, *value, *handler;

    attr = va_arg(args, ITS_Object);
    id = va_arg(args, char *);
    value = va_arg(args, char *);
    handler = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);
    ITS_C_ASSERT(id != NULL);

    ENGINE_IT_NEXT(timer) = NULL;

    ENGINE_IT_ID(timer) = strdup(id);
    if (ENGINE_IT_ID(timer) == NULL)
    {
        return (ITS_ENOMEM);
    }
    if (value)
    {
        ENGINE_IT_VALUE(timer) = strdup(value);
        if (ENGINE_IT_VALUE(timer) == NULL)
        {
            free(ENGINE_IT_ID(timer));

            return (ITS_ENOMEM);
        }
    }
    if (handler)
    {
        ENGINE_IT_HANDLER(timer) = strdup(handler);
        if (ENGINE_IT_HANDLER(timer) == NULL)
        {
            free(ENGINE_IT_ID(timer));
            if (ENGINE_IT_VALUE(timer));
            {
                free(ENGINE_IT_VALUE(timer));
            }

            return (ITS_ENOMEM);
        }
    }

    /* tail add */
    tlist = &ENGINE_IA_TIMERS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_IT_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ISUPTimerDestroy(ITS_Object obj)
{
    free(ENGINE_IT_ID(obj));
    if (ENGINE_IT_VALUE(obj))
    {
        free(ENGINE_IT_VALUE(obj));
    }
    if (ENGINE_IT_HANDLER(obj))
    {
        free(ENGINE_IT_HANDLER(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISUPTimerCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_IT_ID(o1), ENGINE_IT_ID(o2)) == 0 &&
        ((ENGINE_IT_VALUE(o1) == NULL && ENGINE_IT_VALUE(o2) == NULL) ||
         (ENGINE_IT_VALUE(o1) != NULL && ENGINE_IT_VALUE(o2) != NULL &&
          strcmp(ENGINE_IT_VALUE(o1), ENGINE_IT_VALUE(o2)) == 0)) &&
        ((ENGINE_IT_HANDLER(o1) == NULL && ENGINE_IT_HANDLER(o2) == NULL) ||
         (ENGINE_IT_HANDLER(o1) != NULL && ENGINE_IT_HANDLER(o2) != NULL &&
          strcmp(ENGINE_IT_HANDLER(o1), ENGINE_IT_HANDLER(o2)) == 0)))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISUPTimerClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISUPTimerRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISUP Timer Class",      /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISUPTimerCreate,                /* instantiate */
        ISUPTimerDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISUPTimerCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISUPTimerClass = &itsENGINE_ISUPTimerClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an isup timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_CICsClass, circuitGroup,
 *                          start, count);
 *
 *  See Also:
 ****************************************************************************/
static int
CircuitCodeCreate(ITS_Object obj, va_list args)
{
    ENGINE_CICs cics = (ENGINE_CICs)obj;
    ITS_Object cg;
    ITS_Object *tlist;
    ITS_Object *list;

    cg = va_arg(args, ITS_Object);
    ENGINE_IC_START(cics) = va_arg(args, ITS_UINT);
    ENGINE_IC_COUNT(cics) = va_arg(args, ITS_UINT);

    ITS_C_ASSERT(cg != NULL);
    ENGINE_IC_NEXT(cics) = NULL;

    /* tail add */
    tlist = &ENGINE_CG_CODES(cg);
    for (list = tlist;
         *list;
         list = &ENGINE_IC_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
CircuitCodeDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CircuitCodeCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_IC_START(o1) == ENGINE_IC_START(o2) &&
        ENGINE_IC_COUNT(o1) == ENGINE_IC_COUNT(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_CICsClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_CICsRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE CICs Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CircuitCodeCreate,              /* instantiate */
        CircuitCodeDestroy,             /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CircuitCodeCompare,             /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_CICsClass = &itsENGINE_CICsClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a circuit group object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_CircuitGroupClass, isupAttr,
 *                          huntRule);
 *
 *  See Also:
 ****************************************************************************/
static int
CircuitGroupCreate(ITS_Object obj, va_list args)
{
    ENGINE_CircuitGroup group = (ENGINE_CircuitGroup)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *huntRule;

    attr = va_arg(args, ITS_Object);
    huntRule = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);

    ENGINE_CG_NEXT(group) = NULL;

    if (huntRule)
    {
        ENGINE_CG_HUNT_RULE(group) = strdup(huntRule);
        if (ENGINE_CG_HUNT_RULE(group) == NULL)
        {
            return (ITS_ENOMEM);
        }
    }

    /* tail add */
    tlist = &ENGINE_IA_GROUPS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_CG_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
CircuitGroupDestroy(ITS_Object obj)
{
    if (ENGINE_CG_HUNT_RULE(obj))
    {
        free(ENGINE_CG_HUNT_RULE(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
CircuitGroupCompare(ITS_Object o1, ITS_Object o2)
{
    if ((ENGINE_CG_HUNT_RULE(o1) == NULL && ENGINE_CG_HUNT_RULE(o2) == NULL) ||
        (ENGINE_CG_HUNT_RULE(o1) != NULL && ENGINE_CG_HUNT_RULE(o2) != NULL &&
         strcmp(ENGINE_CG_HUNT_RULE(o1), ENGINE_CG_HUNT_RULE(o2)) == 0))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_CircuitGroupClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_CircuitGroupRec), /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE CircuitGroup Class",    /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        CircuitGroupCreate,             /* instantiate */
        CircuitGroupDestroy,            /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        CircuitGroupCompare,            /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_CircuitGroupClass = &itsENGINE_CircuitGroupClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISUPAttrClass,
 *                          application, destination,
 *                          localPointCode, classRec, library);
 *
 *  See Also:
 ****************************************************************************/
static int
ISUPAttrCreate(ITS_Object obj, va_list args)
{
    char *libName, *className;
    ENGINE_ISUPAttr isupAttr = (ENGINE_ISUPAttr)obj;
    ENGINE_Application app;
    ENGINE_Dest dest;
    ITS_Class *cl;
    char *xchangeType = NULL;
    char *segmentationSupported = NULL;

    app = va_arg(args, ENGINE_Application);
    dest = va_arg(args, ENGINE_Dest);
    ENGINE_IA_LPC(isupAttr) = va_arg(args, ITS_UINT);
    className = va_arg(args, char *);
    libName = va_arg(args, char *);
    ENGINE_IA_SIO(isupAttr) = va_arg(args, ITS_UINT);

    xchangeType = va_arg(args, char *);
    if (xchangeType == NULL)
    {
        ENGINE_IA_XTYPE(isupAttr) = xchangeType;
    }
    else
    {
        ENGINE_IA_XTYPE(isupAttr) = strdup(xchangeType);
    }

    segmentationSupported = va_arg(args, char *);
    if (segmentationSupported == NULL)
    {
        ENGINE_IA_XTYPE(isupAttr) = xchangeType;
    }
    else
    {
       ENGINE_IA_SEGMENTATIONSUPPORT(isupAttr) = strdup(segmentationSupported);
    }

    ITS_C_REQUIRE(dest != NULL);
    ITS_C_REQUIRE(className != NULL && strlen(className) != 0);

    ENGINE_IA_CLASS_REC(isupAttr) = strdup(className);
    ENGINE_IA_LIB(isupAttr) = ENGINE_LibGet(app, libName);

    ITS_C_ASSERT(ENGINE_IA_CLASS_REC(isupAttr) != NULL);
    ITS_C_ASSERT(ENGINE_IA_LIB(isupAttr) != NULL);

    dest->dest.isupAttr = obj;

    cl = (ITS_Class *)
        DLSYM_Resolve(ENGINE_LC_LIBRARY(ENGINE_IA_LIB(isupAttr)),
                      className);

    if (cl == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   className, DLSYM_Error());
            fflush(stdout);
        }

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a feature object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ISUPAttrDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    free(ENGINE_IA_CLASS_REC(obj));

    for (list = ENGINE_IA_TIMERS(obj); list; list = tmp)
    {
        tmp = ENGINE_IT_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_IA_GROUPS(obj); list; list = tmp)
    {
        tmp = ENGINE_CG_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISUPAttrCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_IA_LPC(o1) == ENGINE_IA_LPC(o2) &&
        strcmp(ENGINE_IA_CLASS_REC(o1), ENGINE_IA_CLASS_REC(o2)) == 0 &&
        ENGINE_FEAT_LIB_CACHE_ENTRY(o1) == ENGINE_FEAT_LIB_CACHE_ENTRY(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISUPAttrClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISUPAttrRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISUP Attr Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISUPAttrCreate,                 /* instantiate */
        ISUPAttrDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISUPAttrCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISUPAttrClass = &itsENGINE_ISUPAttrClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create an sip timer object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SIPTimerClass, sipttributes,
 *                          id, value);
 *
 *  See Also:
 ****************************************************************************/
static int
SIPTimerCreate(ITS_Object obj, va_list args)
{
    ENGINE_SIPTimer timer = (ENGINE_SIPTimer)obj;
    ITS_Object attr;
    ITS_Object *tlist;
    ITS_Object *list;
    char *id, *value;

    attr = va_arg(args, ITS_Object);
    id = va_arg(args, char *);
    value = va_arg(args, char *);

    ITS_C_ASSERT(attr != NULL);
    ITS_C_ASSERT(id != NULL);

    ENGINE_ST_NEXT(timer) = NULL;

    ENGINE_ST_ID(timer) = strdup(id);
    if (ENGINE_ST_ID(timer) == NULL)
    {
        return (ITS_ENOMEM);
    }
    if (value)
    {
        ENGINE_ST_VALUE(timer) = strdup(value);
        if (ENGINE_ST_VALUE(timer) == NULL)
        {
            free(ENGINE_ST_ID(timer));

            return (ITS_ENOMEM);
        }
    }
    /* tail add */
    tlist = &ENGINE_SIP_TIMERS(attr);
    for (list = tlist;
         *list;
         list = &ENGINE_ST_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SIP Timer object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SIPTimerDestroy(ITS_Object obj)
{
    free(ENGINE_ST_ID(obj));
    if (ENGINE_ST_VALUE(obj))
    {
        free(ENGINE_ST_VALUE(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare timer records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
SIPTimerCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_ST_ID(o1), ENGINE_ST_ID(o2)) == 0 &&
        ((ENGINE_ST_VALUE(o1) == NULL && ENGINE_ST_VALUE(o2) == NULL) ||
         (ENGINE_ST_VALUE(o1) != NULL && ENGINE_ST_VALUE(o2) != NULL &&
          strcmp(ENGINE_ST_VALUE(o1), ENGINE_ST_VALUE(o2)) == 0)))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SIPTimerClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SIPTimerRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SIP Timer Class",      /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        SIPTimerCreate,                 /* instantiate */
        SIPTimerDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        SIPTimerCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SIPTimerClass = &itsENGINE_SIPTimerClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SIP object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SIPAttrClass,
 *                          application,
 *                          UDPPortNo, TCPPortNo, ipAddr);
 *
 *  See Also:
 ****************************************************************************/
static int
SIPAttrCreate(ITS_Object obj, va_list args)
{
    ENGINE_SIPAttr sipAttr = (ENGINE_SIPAttr)obj;
    ENGINE_Application app;
    char *ipAddr = NULL;

    app = va_arg(args, ENGINE_Application);
    ENGINE_SIP_UDPPORT(sipAttr) = va_arg(args, int);
    ENGINE_SIP_TCPPORT(sipAttr) = va_arg(args, int);

    ipAddr = va_arg(args, char *);
    if (ipAddr == NULL)
    {
        ENGINE_SIP_IPADDR(sipAttr) = ipAddr;
    }
    else
    {
        ENGINE_SIP_IPADDR(sipAttr) = strdup(ipAddr);
    }

    app->application.sipAttributes = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SIP object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SIPAttrDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    if (ENGINE_SIP_IPADDR(obj))
    {
        free(ENGINE_SIP_IPADDR(obj));
    }

    for (list = ENGINE_SIP_TIMERS(obj); list; list = tmp)
    {
        tmp = ENGINE_ST_NEXT(list);
        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare feature records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
SIPAttrCompare(ITS_Object o1, ITS_Object o2)
{
    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SIPAttrClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SIPAttrRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SIP Attr Class",        /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        SIPAttrCreate,                  /* instantiate */
        SIPAttrDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        SIPAttrCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SIPAttrClass = &itsENGINE_SIPAttrClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a link set config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LinkSetClass, application,
 *                          adjacent, lpc, id, ni, numToStart,
 *                          adjacentSTP, isCLinkSet, is5Bit);
 *
 *  See Also:
 ****************************************************************************/
static int
LinkSetCreate(ITS_Object obj, va_list args)
{
    ENGINE_LinkSet linkSet = (ENGINE_LinkSet)obj;
    ENGINE_Application app;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    ENGINE_LS_ADJ(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_LOC(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_ID(linkSet) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LS_NI(linkSet) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LS_NUM_TO_START(linkSet) = va_arg(args, ITS_UINT);
    ENGINE_LS_ADJACENT_STP(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_IS_C(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_IS_5BIT(linkSet) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LS_FAMILY(linkSet) = va_arg(args, SS7_Family);
    ENGINE_LS_NEXT(linkSet) = NULL;

    ITS_C_ASSERT(app != NULL);

    /* tail add */
    for (list = &ENGINE_APP_LINK_SETS(app);
         *list;
         list = &ENGINE_LS_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a route config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
LinkSetDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare linkSet records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
LinkSetCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_LS_ADJ(o1) == ENGINE_LS_ADJ(o2) &&
        ENGINE_LS_ID(o1) == ENGINE_LS_ID(o2) &&
        ENGINE_LS_FAMILY(o1) == ENGINE_LS_FAMILY(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LinkSetClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LinkSetRec),      /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE LinkSet Class",         /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        LinkSetCreate,                  /* instantiate */
        LinkSetDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        LinkSetCompare,                 /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LinkSetClass = &itsENGINE_LinkSetClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a link config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_LinkClass, &linkList,
 *                          set, code, pri, initActive,
 *                          termFixed, linkFixed, terminal, link);
 *
 *  See Also:
 ****************************************************************************/
static int
LinkCreate(ITS_Object obj, va_list args)
{
    ENGINE_Link link = (ENGINE_Link)obj;
    ITS_Object *rlist, *list;

    rlist = va_arg(args, ITS_Object *);
    ENGINE_LN_SET(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_CODE(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_PRI(link) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_LN_INIT_ACTIVE(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_TERM_FIXED(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_LINK_FIXED(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_TERMINAL(link) = (ITS_USHORT)va_arg(args, ITS_UINT);
    ENGINE_LN_CIRCUIT(link) = (ITS_USHORT)va_arg(args, ITS_UINT);
    ENGINE_LN_IS_SAAL(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_IS_LOCAL(link) = va_arg(args, ITS_BOOLEAN);
    ENGINE_LN_FAMILY(link) = va_arg(args, SS7_Family);
    ENGINE_LN_NEXT(link) = NULL;

    ITS_C_ASSERT(rlist != NULL);

    /* tail add */
    for (list = rlist; *list; list = &ENGINE_LN_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a link config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
LinkDestroy(ITS_Object obj)
{
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare link records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
LinkCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_LN_SET(o1) == ENGINE_LN_SET(o2) &&
        ENGINE_LN_CODE(o1) == ENGINE_LN_CODE(o2) &&
        ENGINE_LN_PRI(o1) == ENGINE_LN_PRI(o2))
    {
        return (ITS_TRUE);
    }

    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_LinkClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_LinkRec),         /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Link Class",            /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        LinkCreate,                     /* instantiate */
        LinkDestroy,                    /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        LinkCompare,                    /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_LinkClass = &itsENGINE_LinkClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport specifics config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
 *                          mask, ...);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportSpecificsCreate(ITS_Object obj, va_list args)
{
    ENGINE_TransportSpecifics ts = (ENGINE_TransportSpecifics)obj;
    ITS_UINT mask;
    int ret;

    mask = va_arg(args, ITS_UINT);

    ENGINE_TS_MASK(ts) = mask;

    ret = ENGINE_ParseTransportSpecifics(ts, args);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport specific config object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
TransportSpecificsDestroy(ITS_Object obj)
{
    ENGINE_FreeTransportSpecifics((ENGINE_TransportSpecifics)obj);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport specifics records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportSpecificsCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o1)) !=
        ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o2)))
    {
        return (ITS_FALSE);
    }

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(o1)))
    {
    case ITS_TRANSPORT_SS7:
        if (strcmp(ENGINE_TS_DATA(o1).ss7Specs.vendorLib,
                   ENGINE_TS_DATA(o2).ss7Specs.vendorLib) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).ss7Specs.vendorClass,
                   ENGINE_TS_DATA(o2).ss7Specs.vendorClass) != 0)
        {
            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        if (strcmp(ENGINE_TS_DATA(o1).fifoSpecs.clientPath,
                   ENGINE_TS_DATA(o2).fifoSpecs.clientPath) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).fifoSpecs.serverPath,
                   ENGINE_TS_DATA(o2).fifoSpecs.serverPath) != 0)
        {
            return (ITS_FALSE);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        if (strcmp(ENGINE_TS_DATA(o1).tcpSpecs.socketDomain,
                   ENGINE_TS_DATA(o2).tcpSpecs.socketDomain) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.serverPath,
                   ENGINE_TS_DATA(o2).tcpSpecs.serverPath) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.serverPort,
                   ENGINE_TS_DATA(o2).tcpSpecs.serverPort) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ENGINE_TS_DATA(o1).tcpSpecs.retryDelay == NULL) ^
            (ENGINE_TS_DATA(o2).tcpSpecs.retryDelay == NULL))
        {
            return (ITS_FALSE);
        }
        if (ENGINE_TS_DATA(o1).tcpSpecs.retryDelay != NULL &&
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.retryDelay,
                   ENGINE_TS_DATA(o2).tcpSpecs.retryDelay) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ENGINE_TS_DATA(o1).tcpSpecs.retryCount == NULL) ^
            (ENGINE_TS_DATA(o2).tcpSpecs.retryCount == NULL))
        {
            return (ITS_FALSE);
        }
        if (ENGINE_TS_DATA(o1).tcpSpecs.retryCount != NULL &&
            strcmp(ENGINE_TS_DATA(o1).tcpSpecs.retryCount,
                   ENGINE_TS_DATA(o2).tcpSpecs.retryCount) != 0)
        {
            return (ITS_FALSE);
        }

        if ((ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
             ITS_TRANSPORT_SOCKP_MASK) != 
            (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o2)) &
             ITS_TRANSPORT_SOCKP_MASK))
        {
            return (ITS_FALSE);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).gdiSpecs.localPC,
                       ENGINE_TS_DATA(o2).gdiSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).gdiSpecs.remotePC,
                       ENGINE_TS_DATA(o2).gdiSpecs.remotePC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).gdiSpecs.remoteSSN,
                       ENGINE_TS_DATA(o2).gdiSpecs.remoteSSN) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).taliSpecs.localPC,
                       ENGINE_TS_DATA(o2).taliSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.adjacentPC,
                       ENGINE_TS_DATA(o2).taliSpecs.adjacentPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.localAllowedOnOpen,
                       ENGINE_TS_DATA(o2).taliSpecs.localAllowedOnOpen) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).taliSpecs.useUpperLayer,
                       ENGINE_TS_DATA(o2).taliSpecs.useUpperLayer) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            if (strcmp(ENGINE_TS_DATA(o1).imalSpecs.localPC,
                       ENGINE_TS_DATA(o2).imalSpecs.localPC) != 0 ||
                strcmp(ENGINE_TS_DATA(o1).imalSpecs.adjacentPC,
                       ENGINE_TS_DATA(o2).imalSpecs.adjacentPC) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).imalSpecs.keepAliveTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).imalSpecs.keepAliveTimeOut,
                       ENGINE_TS_DATA(o2).imalSpecs.keepAliveTimeOut) != 0)
            {
                return (ITS_FALSE);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        if (strcmp(ENGINE_TS_DATA(o1).udpSpecs.localHost,
                   ENGINE_TS_DATA(o2).udpSpecs.localHost) != 0 ||
            strcmp(ENGINE_TS_DATA(o1).udpSpecs.localPort,
                   ENGINE_TS_DATA(o2).udpSpecs.localPort) != 0)
        {
            return (ITS_FALSE);
        }

        /* associates */
        if (ENGINE_TS_DATA(o1).udpSpecs.numAssociates !=
            ENGINE_TS_DATA(o2).udpSpecs.numAssociates)
        {
            return (ITS_FALSE);
        }

        for (i = 0; i < ENGINE_TS_DATA(o1).udpSpecs.numAssociates; i++)
        {
            if (strcmp(ENGINE_TS_DATA(o1).udpSpecs.associates[i],
                       ENGINE_TS_DATA(o1).udpSpecs.associates[i]) != 0)
            {
                return (ITS_FALSE);
            }
        }

        if ((ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
             ITS_TRANSPORT_SOCKP_MASK) != 
            (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o2)) &
             ITS_TRANSPORT_SOCKP_MASK))
        {
            return (ITS_FALSE);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(o1)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (ENGINE_TS_DATA(o1).sctpSpecs.numExtraHomes !=
                ENGINE_TS_DATA(o2).sctpSpecs.numExtraHomes)
            {
                return (ITS_FALSE);
            }

            for (i = 0; i < ENGINE_TS_DATA(o1).sctpSpecs.numExtraHomes; i++)
            {
                if (strcmp(ENGINE_TS_DATA(o1).sctpSpecs.extraHomes[i],
                           ENGINE_TS_DATA(o2).sctpSpecs.extraHomes[i]) != 0)
                {
                    return (ITS_FALSE);
                }
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.maxInStreams == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.maxInStreams,
                       ENGINE_TS_DATA(o2).sctpSpecs.maxInStreams) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.numOutStreams == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.numOutStreams,
                       ENGINE_TS_DATA(o2).sctpSpecs.numOutStreams) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.maxAttempts == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.maxAttempts,
                       ENGINE_TS_DATA(o2).sctpSpecs.maxAttempts) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.cookieLife == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.cookieLife == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.cookieLife &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.cookieLife,
                       ENGINE_TS_DATA(o2).sctpSpecs.cookieLife) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.hbOn == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.hbOn == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.hbOn &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.hbOn,
                       ENGINE_TS_DATA(o2).sctpSpecs.hbOn) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.initTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.initTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.initTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.sendTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.sendTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.sendTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.recvTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.recvTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.recvTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.hbTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.hbTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.hbTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.shutdownTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.shutdownTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.shutdownTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.pmtuTimeOut == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.pmtuTimeOut,
                       ENGINE_TS_DATA(o2).sctpSpecs.pmtuTimeOut) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.isClient == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.isClient == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.isClient &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.isClient,
                       ENGINE_TS_DATA(o2).sctpSpecs.isClient) != 0)
            {
                return (ITS_FALSE);
            }

            if ((ENGINE_TS_DATA(o1).sctpSpecs.payloadType == NULL) ^
                (ENGINE_TS_DATA(o2).sctpSpecs.payloadType == NULL))
            {
                return (ITS_FALSE);
            }
            if (ENGINE_TS_DATA(o1).sctpSpecs.payloadType &&
                strcmp(ENGINE_TS_DATA(o1).sctpSpecs.payloadType,
                       ENGINE_TS_DATA(o2).sctpSpecs.payloadType) != 0)
            {
                return (ITS_FALSE);
            }

            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportSpecificsClassRec =
{
    {
        &itsCORE_ClassRec,                      /* superclass */
        sizeof(ENGINE_TransportSpecificsRec),   /* instance size */
        ITS_FALSE,                              /* class initted */
        0,                                      /* class ref count */
        "ENGINE Transport Specifics Class",     /* class name */
        ITS_CLASS_NO_INIT,                      /* class init */
        ITS_CLASS_NO_DEST,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        TransportSpecificsCreate,               /* instantiate */
        TransportSpecificsDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,                 /* clone */
        ITS_INST_PRINT_INHERIT,                 /* print */
        ITS_INST_SERIAL_INHERIT,                /* serialize */
        TransportSpecificsCompare,              /* equals */
        ITS_INST_HASH_INHERIT                   /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportSpecificsClass =
    &itsENGINE_TransportSpecificsClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse transport specific information
 *
 *  Input Parameters:
 *      part = the part to parse into
 *      args = the transport specific args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ENGINE_ParseTransportSpecifics(ENGINE_TransportSpecifics specs,
                               va_list args)
{
    char *tmp;

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(specs)))
    {
    case ITS_TRANSPORT_SS7:
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorName = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorName != NULL);

        /* vendor lib */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorLib = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorLib != NULL);

        /* vendor class */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).ss7Specs.vendorClass = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).ss7Specs.vendorClass != NULL);
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        /* client path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).fifoSpecs.clientPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).fifoSpecs.clientPath != NULL);

        /* server path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).fifoSpecs.serverPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).fifoSpecs.serverPath != NULL);
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        /* socket domain */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.socketDomain = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.socketDomain != NULL);

        /* server path */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.serverPath = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.serverPath != NULL);

        /* server port */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).tcpSpecs.serverPort = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.serverPort != NULL);

        /* retry delay (optional) */
        tmp = va_arg(args, char *);
        if (tmp && strlen(tmp) != 0)
        {
            ENGINE_TS_DATA(specs).tcpSpecs.retryDelay = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.retryDelay != NULL);
        }

        /* retry count (optional) */
        tmp = va_arg(args, char *);
        if (tmp && strlen(tmp) != 0)
        {
            ENGINE_TS_DATA(specs).tcpSpecs.retryCount = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).tcpSpecs.retryCount != NULL);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.localPC != NULL);

            /* remote PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.remotePC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.remotePC != NULL);

            /* remote SSN */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN != NULL);
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.localPC != NULL);

            /* adjacent PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.adjacentPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.adjacentPC != NULL);

            /* allowed on open */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen != NULL);

            /* user upper layer */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer != NULL);
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* local PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).imalSpecs.localPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.localPC != NULL);

            /* adjacent PC */
            tmp = va_arg(args, char *);
            ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

            ENGINE_TS_DATA(specs).imalSpecs.adjacentPC = strdup(tmp);
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.adjacentPC != NULL);

            /* timeout */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut != NULL);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        /* local host */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).udpSpecs.localHost = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.localHost != NULL);

        /* local port */
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp != NULL && strlen(tmp) != 0);

        ENGINE_TS_DATA(specs).udpSpecs.localPort = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.localPort != NULL);

        /* associates */
        ENGINE_TS_DATA(specs).udpSpecs.associates =
            va_arg(args, char **);
        ENGINE_TS_DATA(specs).udpSpecs.numAssociates = va_arg(args, int);
        if (ENGINE_TS_DATA(specs).udpSpecs.numAssociates)
        {
            ITS_C_ASSERT(ENGINE_TS_DATA(specs).udpSpecs.associates != NULL);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            ENGINE_TS_DATA(specs).sctpSpecs.extraHomes = va_arg(args, char **);
            ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes = va_arg(args, int);

            if (ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes)
            {
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes != NULL);
            }

            /* max in streams */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams != NULL);
            }

            /* num out streams */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams != NULL);
            }

            /* max attempts */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts != NULL);
            }

            /* cookie life */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.cookieLife = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.cookieLife != NULL);
            }

            /* hb on */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.hbOn = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.hbOn != NULL);
            }

            /* init time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut != NULL);
            }

            /* send time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut != NULL);
            }

            /* recv time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut != NULL);
            }

            /* hb time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut != NULL);
            }

            /* shutdown time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut != NULL);
            }

            /* pmtu time out */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut != NULL);
            }

            /* is client */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.isClient = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.isClient != NULL);
            }

            /* payload type */
            tmp = va_arg(args, char *);
            if (tmp && strlen(tmp) != 0)
            {
                ENGINE_TS_DATA(specs).sctpSpecs.payloadType = strdup(tmp);
                ITS_C_ASSERT(ENGINE_TS_DATA(specs).sctpSpecs.payloadType != NULL);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free transport specific args
 *
 *  Input Parameters:
 *      part - the part to free
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ENGINE_FreeTransportSpecifics(ENGINE_TransportSpecifics specs)
{
    int i;

    switch (ITS_GET_TRANSPORT_TYPE(ENGINE_TS_MASK(specs)))
    {
    case ITS_TRANSPORT_SS7:
        /* vendor lib */
        free(ENGINE_TS_DATA(specs).ss7Specs.vendorLib);

        /* vendor class */
        free(ENGINE_TS_DATA(specs).ss7Specs.vendorClass);
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        /* client path */
        free(ENGINE_TS_DATA(specs).fifoSpecs.clientPath);

        /* server path */
        free(ENGINE_TS_DATA(specs).fifoSpecs.serverPath);
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        /* socket domain */
        free(ENGINE_TS_DATA(specs).tcpSpecs.socketDomain);

        /* server path */
        free(ENGINE_TS_DATA(specs).tcpSpecs.serverPath);

        /* server port */
        free(ENGINE_TS_DATA(specs).tcpSpecs.serverPort);

        /* retry delay (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryDelay)
        {
            free(ENGINE_TS_DATA(specs).tcpSpecs.retryDelay);
        }

        /* retry count (optional) */
        if (ENGINE_TS_DATA(specs).tcpSpecs.retryCount)
        {
            free(ENGINE_TS_DATA(specs).tcpSpecs.retryCount);
        }

        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).gdiSpecs.localPC);

            /* remote PC */
            free(ENGINE_TS_DATA(specs).gdiSpecs.remotePC);

            /* remote SSN */
            free(ENGINE_TS_DATA(specs).gdiSpecs.remoteSSN);
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).taliSpecs.localPC);

            /* adjacent PC */
            free(ENGINE_TS_DATA(specs).taliSpecs.adjacentPC);

            /* allowed on open */
            free(ENGINE_TS_DATA(specs).taliSpecs.localAllowedOnOpen);

            /* user upper layer */
            free(ENGINE_TS_DATA(specs).taliSpecs.useUpperLayer);
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* local PC */
            free(ENGINE_TS_DATA(specs).imalSpecs.localPC);

            /* adjacent PC */
            free(ENGINE_TS_DATA(specs).imalSpecs.adjacentPC);

            /* keepalive */
            if (ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut)
            {
                free(ENGINE_TS_DATA(specs).imalSpecs.keepAliveTimeOut);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        /* none */
        break;

    case ITS_TRANSPORT_DATAGRAM:
        /* local host */
        free(ENGINE_TS_DATA(specs).udpSpecs.localHost);

        /* local port */
        free(ENGINE_TS_DATA(specs).udpSpecs.localPort);

        /* associates */
        if (ENGINE_TS_DATA(specs).udpSpecs.associates)
        {
            for (i = 0; i < ENGINE_TS_DATA(specs).udpSpecs.numAssociates; i++)
            {
                free(ENGINE_TS_DATA(specs).udpSpecs.associates[i]);
            }

            free(ENGINE_TS_DATA(specs).udpSpecs.associates);
        }

        /* handle SCTP, RUDP */
        switch (ITS_GET_TRANSPORT_FLAGS(ENGINE_TS_MASK(specs)) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (ENGINE_TS_DATA(specs).sctpSpecs.extraHomes)
            {
                for (i = 0; i < ENGINE_TS_DATA(specs).sctpSpecs.numExtraHomes; i++)
                {
                    free(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes[i]);
                }

                free(ENGINE_TS_DATA(specs).sctpSpecs.extraHomes);
            }

            /* max in streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.maxInStreams);
            }

            /* num out streams */
            if (ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.numOutStreams);
            }

            /* max attempts */
            if (ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.maxAttempts);
            }

            /* cookie life */
            if (ENGINE_TS_DATA(specs).sctpSpecs.cookieLife)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.cookieLife);
            }

            /* hb on */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbOn)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.hbOn);
            }

            /* init time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.initTimeOut);
            }

            /* send time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.sendTimeOut);
            }

            /* recv time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.recvTimeOut);
            }

            /* hb time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.hbTimeOut);
            }

            /* shutdown time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.shutdownTimeOut);
            }

            /* pmtu time out */
            if (ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.pmtuTimeOut);
            }

            /* is client */
            if (ENGINE_TS_DATA(specs).sctpSpecs.isClient)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.isClient);
            }

            /* payload type */
            if (ENGINE_TS_DATA(specs).sctpSpecs.payloadType)
            {
                free(ENGINE_TS_DATA(specs).sctpSpecs.payloadType);
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport callback config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportCallbacksClass, app,
 *                          "libCISCO.so", notTrueSS7,
 *                          DISP_PROT_USER, DISP_BLOCKING,
 *                          "PreInit", "PostInit",
 *                          "PreNext", "NextEventFailed", "PostNext",
 *                          "DispatchUSER", "DispatchISUP", "DispatchSCCP",
 *                          "PreAccept", "OnAccept",
 *                          "PreTerminate", "PostTerminate",
 *                          DISP_PROT_USER);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportCallbacksCreate(ITS_Object obj, va_list args)
{
    ENGINE_TransportCallbacks tc = (ENGINE_TransportCallbacks)obj;
    ENGINE_Application app;
    ITS_BOOLEAN trueSS7;
    char *tmp;

    app = va_arg(args, ENGINE_Application);
    tmp = va_arg(args, char *);
    trueSS7 = va_arg(args, ITS_BOOLEAN);
    ENGINE_TC_HANDLER_TYPE(tc) = va_arg(args, int);
    ENGINE_TC_TYPE(tc) = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);

    if (tmp && strlen(tmp) != 0)
    {
        ENGINE_TC_LIB_NAME(tc) = strdup(tmp);

        ITS_C_ASSERT(ENGINE_TC_LIB_NAME(tc) != NULL);
    }

    switch (ENGINE_TC_HANDLER_TYPE(tc))
    {
    case DISP_PROT_CCITT:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_CCITT_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_CCITT_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_CCITT_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_CCITT_STRING;
            }
        }
        break;

    case DISP_PROT_ANSI:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_ANSI_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_ANSI_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_ANSI_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_ANSI_STRING;
            }
        }
        break;

    case DISP_PROT_PRC:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_PRC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_PRC_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_PRC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_PRC_STRING;
            }
        }
        break;

    case DISP_PROT_TTC:
        if (trueSS7)
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_TTC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_SS7_TTC_STRING;
            }
        }
        else
        {
            if (ENGINE_APP_CPP_BINDING(app))
            {
                ENGINE_TC_MAIN(tc) = DISP_TTC_CPP_STRING;
            }
            else
            {
                ENGINE_TC_MAIN(tc) = DISP_TTC_STRING;
            }
        }
        break;

    case DISP_PROT_USER:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_USER_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_USER_STRING;
        }
        break;

    case DISP_PROT_ITERATIVE:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_ITERATIVE_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_ITERATIVE_STRING;
        }
        break;

    case DISP_PROT_WORK_ITEM:
        ENGINE_TC_MAIN(tc) = DISP_WORK_ITEM_STRING;
        break;

    case DISP_PROT_DBC:
        if (ENGINE_APP_CPP_BINDING(app))
        {
            ENGINE_TC_MAIN(tc) = DISP_DBC_CPP_STRING;
        }
        else
        {
            ENGINE_TC_MAIN(tc) = DISP_DBC_STRING;
        }
        break;

    case DISP_PROT_CUSTOM:
        tmp = va_arg(args, char *);
        ITS_C_ASSERT(tmp && strlen(tmp) != 0);
        ENGINE_TC_MAIN(tc) = strdup(tmp);
        return (ITS_SUCCESS);

    default:
        ITS_C_ASSERT(ITS_FALSE);
        break;
    }

    /* get bindings */
    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_INIT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_INIT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_INIT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_INIT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_INIT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_INIT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_NEXT_EVENT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_NEXT_EVENT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_NEXT_EVENT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_NEXT_EVENT_FAIL(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_NEXT_EVENT_FAIL(tc) != NULL);
    }
    else
    {
        ENGINE_TC_NEXT_EVENT_FAIL(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_NEXT_EVENT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_NEXT_EVENT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_NEXT_EVENT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_USER(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_USER(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_USER(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_ISUP(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_ISUP(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_ISUP(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_DISP_SCCP(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_DISP_SCCP(tc) != NULL);
    }
    else
    {
        ENGINE_TC_DISP_SCCP(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_ACCEPT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_ACCEPT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_ACCEPT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_ON_ACCEPT(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_ON_ACCEPT(tc) != NULL);
    }
    else
    {
        ENGINE_TC_ON_ACCEPT(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_PRE_TERM(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_PRE_TERM(tc) != NULL);
    }
    else
    {
        ENGINE_TC_PRE_TERM(tc) = NULL;
    }

    tmp = va_arg(args, char *);
    if (tmp && strlen(tmp) != 0 && strcmp(tmp, NULL_STRING) != 0)
    {
        ENGINE_TC_POST_TERM(tc) = strdup(tmp);
        ITS_C_ASSERT(ENGINE_TC_POST_TERM(tc) != NULL);
    }
    else
    {
        ENGINE_TC_POST_TERM(tc) = NULL;
    }

    ENGINE_TC_ACCEPT_HANDLER_TYPE(tc) = va_arg(args, int);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport callback config object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
TransportCallbacksDestroy(ITS_Object obj)
{
    if (ENGINE_TC_LIB_NAME(obj))
    {
        free(ENGINE_TC_LIB_NAME(obj));
    }

    if (ENGINE_TC_HANDLER_TYPE(obj) == DISP_PROT_CUSTOM)
    {
        free(ENGINE_TC_MAIN(obj));
    }

    if (ENGINE_TC_PRE_INIT(obj))
    {
        free(ENGINE_TC_PRE_INIT(obj));
    }
    if (ENGINE_TC_POST_INIT(obj))
    {
        free(ENGINE_TC_POST_INIT(obj));
    }
    if (ENGINE_TC_PRE_NEXT_EVENT(obj))
    {
        free(ENGINE_TC_PRE_NEXT_EVENT(obj));
    }
    if (ENGINE_TC_NEXT_EVENT_FAIL(obj))
    {
        free(ENGINE_TC_NEXT_EVENT_FAIL(obj));
    }
    if (ENGINE_TC_POST_NEXT_EVENT(obj))
    {
        free(ENGINE_TC_POST_NEXT_EVENT(obj));
    }
    if (ENGINE_TC_DISP_USER(obj))
    {
        free(ENGINE_TC_DISP_USER(obj));
    }
    if (ENGINE_TC_DISP_ISUP(obj))
    {
        free(ENGINE_TC_DISP_ISUP(obj));
    }
    if (ENGINE_TC_DISP_SCCP(obj))
    {
        free(ENGINE_TC_DISP_SCCP(obj));
    }
    if (ENGINE_TC_PRE_TERM(obj))
    {
        free(ENGINE_TC_PRE_TERM(obj));
    }
    if (ENGINE_TC_POST_TERM(obj))
    {
        free(ENGINE_TC_POST_TERM(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport callback records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportCallbacksCompare(ITS_Object o1, ITS_Object o2)
{
    if (strcmp(ENGINE_TC_MAIN(o1), ENGINE_TC_MAIN(o2)) != 0)
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_INIT(o1) == NULL) ^
         (ENGINE_TC_PRE_INIT(o2) == NULL)) ||
        (ENGINE_TC_PRE_INIT(o1) &&
         strcmp(ENGINE_TC_PRE_INIT(o1), ENGINE_TC_PRE_INIT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_INIT(o1) == NULL) ^
         (ENGINE_TC_POST_INIT(o2) == NULL)) ||
        (ENGINE_TC_POST_INIT(o1) &&
         strcmp(ENGINE_TC_POST_INIT(o1), ENGINE_TC_POST_INIT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_NEXT_EVENT(o1) == NULL) ^
         (ENGINE_TC_PRE_NEXT_EVENT(o2) == NULL)) ||
        (ENGINE_TC_PRE_NEXT_EVENT(o1) &&
         strcmp(ENGINE_TC_PRE_NEXT_EVENT(o1),
                ENGINE_TC_PRE_NEXT_EVENT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_NEXT_EVENT_FAIL(o1) == NULL) ^
         (ENGINE_TC_NEXT_EVENT_FAIL(o2) == NULL)) ||
        (ENGINE_TC_NEXT_EVENT_FAIL(o1) &&
         strcmp(ENGINE_TC_NEXT_EVENT_FAIL(o1),
                ENGINE_TC_NEXT_EVENT_FAIL(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_NEXT_EVENT(o1) == NULL) ^
         (ENGINE_TC_POST_NEXT_EVENT(o2) == NULL)) ||
        (ENGINE_TC_POST_NEXT_EVENT(o1) &&
         strcmp(ENGINE_TC_POST_NEXT_EVENT(o1),
                ENGINE_TC_POST_NEXT_EVENT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_USER(o1) == NULL) ^
         (ENGINE_TC_DISP_USER(o2) == NULL)) ||
        (ENGINE_TC_DISP_USER(o1) &&
         strcmp(ENGINE_TC_DISP_USER(o1),
                ENGINE_TC_DISP_USER(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_ISUP(o1) == NULL) ^
         (ENGINE_TC_DISP_ISUP(o2) == NULL)) ||
        (ENGINE_TC_DISP_ISUP(o1) &&
         strcmp(ENGINE_TC_DISP_ISUP(o1),
                ENGINE_TC_DISP_ISUP(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_DISP_SCCP(o1) == NULL) ^
         (ENGINE_TC_DISP_SCCP(o2) == NULL)) ||
        (ENGINE_TC_DISP_SCCP(o1) &&
         strcmp(ENGINE_TC_DISP_SCCP(o1),
                ENGINE_TC_DISP_SCCP(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_ACCEPT(o1) == NULL) ^
         (ENGINE_TC_PRE_ACCEPT(o2) == NULL)) ||
        (ENGINE_TC_PRE_ACCEPT(o1) &&
         strcmp(ENGINE_TC_PRE_ACCEPT(o1), ENGINE_TC_PRE_ACCEPT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_ON_ACCEPT(o1) == NULL) ^
         (ENGINE_TC_ON_ACCEPT(o2) == NULL)) ||
        (ENGINE_TC_ON_ACCEPT(o1) &&
         strcmp(ENGINE_TC_ON_ACCEPT(o1), ENGINE_TC_ON_ACCEPT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_PRE_TERM(o1) == NULL) ^
         (ENGINE_TC_PRE_TERM(o2) == NULL)) ||
        (ENGINE_TC_PRE_TERM(o1) &&
         strcmp(ENGINE_TC_PRE_TERM(o1), ENGINE_TC_PRE_TERM(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_TC_POST_TERM(o1) == NULL) ^
         (ENGINE_TC_POST_TERM(o2) == NULL)) ||
        (ENGINE_TC_POST_TERM(o1) &&
         strcmp(ENGINE_TC_POST_TERM(o1), ENGINE_TC_POST_TERM(o2)) != 0))
    {
        return (ITS_FALSE);
    }


    if (ENGINE_TC_ACCEPT_HANDLER_TYPE(o1) != 
        ENGINE_TC_ACCEPT_HANDLER_TYPE(o2))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportCallbacksClassRec =
{
    {
        &itsCORE_ClassRec,                      /* superclass */
        sizeof(ENGINE_TransportCallbacksRec),   /* instance size */
        ITS_FALSE,                              /* class initted */
        0,                                      /* class ref count */
        "ENGINE Transport Callbacks Class",     /* class name */
        ITS_CLASS_NO_INIT,                      /* class init */
        ITS_CLASS_NO_DEST,                      /* class destroy */
        ITS_CLASS_PART_NO_INIT,                 /* class part init */
        ITS_CLASS_PART_NO_DEST,                 /* class part destroy */
        TransportCallbacksCreate,               /* instantiate */
        TransportCallbacksDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,                 /* clone */
        ITS_INST_PRINT_INHERIT,                 /* print */
        ITS_INST_SERIAL_INHERIT,                /* serialize */
        TransportCallbacksCompare,              /* equals */
        ITS_INST_HASH_INHERIT                   /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportCallbacksClass =
    &itsENGINE_TransportCallbacksClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a transport config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_TransportClass, threadPool,
 *                          name, mask, instance, isInterNode,
 *                          specifics, callbacks, routes, workItems);
 *
 *  See Also:
 ****************************************************************************/
static int
TransportCreate(ITS_Object obj, va_list args)
{
    ENGINE_Transport trans = (ENGINE_Transport)obj;
    ITS_Object tp;
    char *name;
    ITS_UINT mask;
    ITS_USHORT inst;
    ITS_BOOLEAN isInterNode;
    ITS_Object specifics;
    ITS_Object callbacks;
    ITS_Object links;
    ITS_Object workItems;
    ITS_Object *list;

    tp = va_arg(args, ITS_Object);
    name = va_arg(args, char *);
    mask = va_arg(args, ITS_UINT);
    inst = (ITS_USHORT)va_arg(args, ITS_UINT);
    isInterNode = va_arg(args, ITS_BOOLEAN);
    specifics = va_arg(args, ITS_Object);
    callbacks = va_arg(args, ITS_Object);
    links = va_arg(args, ITS_Object);
    workItems = va_arg(args, ITS_Object);

    ITS_C_ASSERT(callbacks != NULL);

    ENGINE_TR_NEXT(trans) = NULL;
    ENGINE_TR_POOL(trans) = tp;
    if (name && strlen(name) != 0)
    {
        ENGINE_TR_NAME(trans) = strdup(name);
        ITS_C_ASSERT(ENGINE_TR_NAME(trans) != NULL);
    }
    ENGINE_TR_MASK(trans) = mask;
    ENGINE_TR_INST(trans) = inst;
    ENGINE_TR_IS_INTERNODE(trans) = isInterNode;
    ENGINE_TR_SPECIFICS(trans) = specifics;
    ENGINE_TR_CALLBACKS(trans) = callbacks;
    ENGINE_TR_LINKS(trans) = links;
    ENGINE_TR_WORK_ITEMS(trans) = workItems;

    /* tail add */
    if (tp)
    {
        for (list = &ENGINE_TP_TRANSPORTS(tp);
             *list;
             list = &ENGINE_TR_NEXT(*list))
        {
        }
        *list = obj;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a transport config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
TransportDestroy(ITS_Object obj)
{
    ITS_Object list, tmp;

    free(ENGINE_TR_NAME(obj));

    ITS_DestructObject(ENGINE_TR_SPECIFICS(obj));
    ITS_DestructObject(ENGINE_TR_CALLBACKS(obj));

    for (list = ENGINE_TR_LINKS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LN_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_TR_WORK_ITEMS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_WI_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare transport records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
TransportCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_TR_NAME(o1) == NULL) ^
         (ENGINE_TR_NAME(o2) == NULL)) ||
        (ENGINE_TR_NAME(o1) &&
         strcmp(ENGINE_TR_NAME(o1), ENGINE_TR_NAME(o2)) != 0) ||
        ENGINE_TR_MASK(o1) != ENGINE_TR_MASK(o2)    ||
        ENGINE_TR_IS_INTERNODE(o1) != ENGINE_TR_IS_INTERNODE(o2))
    {
        return (ITS_FALSE);
    }

    if (!ITS_Equals(ENGINE_TR_SPECIFICS(o1), ENGINE_TR_SPECIFICS(o2)))
    {
        return (ITS_FALSE);
    }

    if (!ITS_Equals(ENGINE_TR_CALLBACKS(o1), ENGINE_TR_CALLBACKS(o2)))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_TransportClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_TransportRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Transport Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        TransportCreate,                /* instantiate */
        TransportDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        TransportCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_TransportClass = &itsENGINE_TransportClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a workItem object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_WorkItemClass, transport,
 *                          ITS_TRUE, 20, "libCISCO.so", "WorkItemDelegate");
 *
 *  See Also:
 ****************************************************************************/
static int
WorkItemCreate(ITS_Object obj, va_list args)
{
    char *libName, *delegate;
    ENGINE_WorkItem wi = (ENGINE_WorkItem)obj;
    ENGINE_Transport trans;
    ITS_BOOLEAN persist;
    ITS_UINT repeat;
    ITS_Object *list;

    trans = va_arg(args, ENGINE_Transport);
    persist = va_arg(args, ITS_BOOLEAN);
    repeat = va_arg(args, int);
    libName = va_arg(args, char *);
    delegate = va_arg(args, char *);

    ITS_C_REQUIRE(trans);
    ITS_C_REQUIRE(delegate != NULL && strlen(delegate) != 0);

    ENGINE_WI_NEXT(wi) = NULL;
    ENGINE_WI_TRANSPORT(wi) = trans;
    ENGINE_WI_PERSIST(wi) = persist;
    ENGINE_WI_REPEAT(wi) = repeat;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_WI_LIB_NAME(wi) = strdup(libName);

        ITS_C_ASSERT(ENGINE_WI_LIB_NAME(wi) != NULL);
    }

    ENGINE_WI_DELEGATE(wi) = strdup(delegate);

    ITS_C_ASSERT(ENGINE_WI_DELEGATE(wi) != NULL);

    /* tail add */
    for (list = &ENGINE_TR_WORK_ITEMS(trans);
         *list;
         list = &ENGINE_WI_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a work item object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
WorkItemDestroy(ITS_Object obj)
{
    if (ENGINE_WI_LIB_NAME(obj))
    {
        free(ENGINE_WI_LIB_NAME(obj));
    }

    free(ENGINE_WI_DELEGATE(obj));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare workitem records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
WorkItemCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_WI_PERSIST(o1) != ENGINE_WI_PERSIST(o2) ||
        ENGINE_WI_REPEAT(o1) != ENGINE_WI_REPEAT(o2))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_WI_LIB_NAME(o1) == NULL) ^
         (ENGINE_WI_LIB_NAME(o2) == NULL)) ||
        (ENGINE_WI_LIB_NAME(o1) &&
         strcmp(ENGINE_WI_LIB_NAME(o1), ENGINE_WI_LIB_NAME(o2)) != 0) ||
        strcmp(ENGINE_WI_DELEGATE(o1), ENGINE_WI_DELEGATE(o2)) != 0)
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_WorkItemClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_WorkItemRec),     /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Work Item Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        WorkItemCreate,                 /* instantiate */
        WorkItemDestroy,                /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        WorkItemCompare,                /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_WorkItemClass = &itsENGINE_WorkItemClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a threadPool object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ThreadPoolClass, app,
 *                          stackSize, TPOOL_WORKERS);
 *
 *  See Also:
 ****************************************************************************/
static int
ThreadPoolCreate(ITS_Object obj, va_list args)
{
    ENGINE_ThreadPool tp = (ENGINE_ThreadPool)obj;
    ENGINE_Application app;
    int stackSize;
    ENGINE_ThreadPoolType type;
    ITS_Object *list;

    app = va_arg(args, ENGINE_Application);
    stackSize = va_arg(args, int);
    type = va_arg(args, int);

    ITS_C_REQUIRE(app != NULL);

    ENGINE_TP_NEXT(tp) = NULL;
    ENGINE_TP_APP(tp) = app;
    ENGINE_TP_STACK_SIZE(tp) = stackSize;
    ENGINE_TP_TYPE(tp) = type;
    ENGINE_TP_TRANSPORTS(tp) = NULL;

    /* tail add */
    for (list = &ENGINE_APP_POOLS(app);
         *list;
         list = &ENGINE_TP_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a thread pool object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ThreadPoolDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    for (list = ENGINE_TP_TRANSPORTS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TR_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare thread pool records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ThreadPoolCompare(ITS_Object o1, ITS_Object o2)
{
    /* not particularly useful. */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ThreadPoolClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ThreadPoolRec),   /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Thread Pool Class",     /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ThreadPoolCreate,               /* instantiate */
        ThreadPoolDestroy,              /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ThreadPoolCompare,              /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ThreadPoolClass = &itsENGINE_ThreadPoolClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SS7 stack mgmt object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SS7StackMgmtClass, app,
 *                          "libCISCO.so",
 *                          "MTP3MgmtANSI", NULL,
 *                          "ISUPMgmtANSI", NULL,
 *                          "SCCPMgmtANSI", NULL,
 *                          "GTTMgmtANSI", NULL);
 *
 *  See Also:
 ****************************************************************************/
static int
StackMgmtCreate(ITS_Object obj, va_list args)
{
    ENGINE_SS7StackMgmt stack = (ENGINE_SS7StackMgmt)obj;
    ENGINE_Application app;
    char *libName;
    char *mtp3ANSI, *mtp3CCITT;
    char *isupANSI, *isupCCITT;
    char *sccpANSI, *sccpCCITT;
    char *gttANSI, *gttCCITT;
    char *ssnRouteANSI, *ssnRouteCCITT;

    app = va_arg(args, ENGINE_Application);
    libName = va_arg(args, char *);
    mtp3ANSI = va_arg(args, char *);
    mtp3CCITT = va_arg(args, char *);
    isupANSI = va_arg(args, char *);
    isupCCITT = va_arg(args, char *);
    sccpANSI = va_arg(args, char *);
    sccpCCITT = va_arg(args, char *);
    gttANSI = va_arg(args, char *);
    gttCCITT = va_arg(args, char *);
    ssnRouteANSI = va_arg(args, char *);
    ssnRouteCCITT = va_arg(args, char *);

    ITS_C_REQUIRE(app != NULL);

    ENGINE_S7_APP(stack) = app;
    ENGINE_APP_SS7_STACK_MGMT(app) = obj;

    /* optional user lib */
    if (libName && strlen(libName) != 0)
    {
        ENGINE_S7_LIB_NAME(stack) = strdup(libName);

        ITS_C_ASSERT(ENGINE_S7_LIB_NAME(stack) != NULL);
    }

    /* optional callbacks */
    if (mtp3ANSI && strlen(mtp3ANSI) != 0)
    {
        ENGINE_S7_MTP3_MGMT_ANSI(stack) = strdup(mtp3ANSI);

        ITS_C_ASSERT(ENGINE_S7_MTP3_MGMT_ANSI(stack) != NULL);
    }
    if (mtp3CCITT && strlen(mtp3CCITT) != 0)
    {
        ENGINE_S7_MTP3_MGMT_CCITT(stack) = strdup(mtp3CCITT);

        ITS_C_ASSERT(ENGINE_S7_MTP3_MGMT_CCITT(stack) != NULL);
    }

    if (isupANSI && strlen(isupANSI) != 0)
    {
        ENGINE_S7_ISUP_MGMT_ANSI(stack) = strdup(isupANSI);

        ITS_C_ASSERT(ENGINE_S7_ISUP_MGMT_ANSI(stack) != NULL);
    }
    if (isupCCITT && strlen(isupCCITT) != 0)
    {
        ENGINE_S7_ISUP_MGMT_CCITT(stack) = strdup(isupCCITT);

        ITS_C_ASSERT(ENGINE_S7_ISUP_MGMT_CCITT(stack) != NULL);
    }

    if (sccpANSI && strlen(sccpANSI) != 0)
    {
        ENGINE_S7_SCCP_MGMT_ANSI(stack) = strdup(sccpANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_MGMT_ANSI(stack) != NULL);
    }
    if (sccpCCITT && strlen(sccpCCITT) != 0)
    {
        ENGINE_S7_SCCP_MGMT_CCITT(stack) = strdup(sccpCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_MGMT_CCITT(stack) != NULL);
    }

    if (gttANSI && strlen(gttANSI) != 0)
    {
        ENGINE_S7_SCCP_GTT_ANSI(stack) = strdup(gttANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_GTT_ANSI(stack) != NULL);
    }
    if (gttCCITT && strlen(gttCCITT) != 0)
    {
        ENGINE_S7_SCCP_GTT_CCITT(stack) = strdup(gttCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_GTT_CCITT(stack) != NULL);
    }

    if (ssnRouteANSI && strlen(ssnRouteANSI) != 0)
    {
        ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stack) = strdup(ssnRouteANSI);

        ITS_C_ASSERT(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(stack) != NULL);
    }
    if (ssnRouteCCITT && strlen(ssnRouteCCITT) != 0)
    {
        ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stack) = strdup(ssnRouteCCITT);

        ITS_C_ASSERT(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(stack) != NULL);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SS7 stack mgmt object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
StackMgmtDestroy(ITS_Object obj)
{
    if (ENGINE_S7_LIB_NAME(obj))
    {
        free(ENGINE_S7_LIB_NAME(obj));
    }

    if (ENGINE_S7_MTP3_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_MTP3_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_MTP3_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_MTP3_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_ISUP_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_ISUP_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_ISUP_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_ISUP_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_MGMT_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_MGMT_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_MGMT_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_MGMT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_GTT_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_GTT_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_GTT_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_GTT_CCITT(obj));
    }

    if (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(obj))
    {
        free(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(obj));
    }
    if (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(obj))
    {
        free(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare stack management records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
StackMgmtCompare(ITS_Object o1, ITS_Object o2)
{
    if (((ENGINE_S7_LIB_NAME(o1) == NULL) ^
         (ENGINE_S7_LIB_NAME(o2) == NULL)) ||
        (ENGINE_S7_LIB_NAME(o1) &&
         strcmp(ENGINE_S7_LIB_NAME(o1), ENGINE_S7_LIB_NAME(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_MTP3_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_MTP3_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_MTP3_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_MTP3_MGMT_ANSI(o1),
                ENGINE_S7_MTP3_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_MTP3_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_MTP3_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_MTP3_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_MTP3_MGMT_CCITT(o1),
                ENGINE_S7_MTP3_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_ISUP_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_ISUP_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_ISUP_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_ISUP_MGMT_ANSI(o1),
                ENGINE_S7_ISUP_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_ISUP_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_ISUP_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_ISUP_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_ISUP_MGMT_CCITT(o1),
                ENGINE_S7_ISUP_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_MGMT_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_MGMT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_MGMT_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_MGMT_ANSI(o1),
                ENGINE_S7_SCCP_MGMT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_MGMT_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_MGMT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_MGMT_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_MGMT_CCITT(o1),
                ENGINE_S7_SCCP_MGMT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_GTT_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_GTT_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_GTT_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_GTT_ANSI(o1),
                ENGINE_S7_SCCP_GTT_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_GTT_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_GTT_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_GTT_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_GTT_CCITT(o1),
                ENGINE_S7_SCCP_GTT_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    if (((ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1) == NULL) ^
         (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o2) == NULL)) ||
        (ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1) &&
         strcmp(ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o1),
                ENGINE_S7_SCCP_SSN_ROUTE_ANSI(o2)) != 0))
    {
        return (ITS_FALSE);
    }
    if (((ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1) == NULL) ^
         (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o2) == NULL)) ||
        (ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1) &&
         strcmp(ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o1),
                ENGINE_S7_SCCP_SSN_ROUTE_CCITT(o2)) != 0))
    {
        return (ITS_FALSE);
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_SS7StackMgmtClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_SS7StackMgmtRec), /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE SS7 Stack Mgmt Class",  /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        StackMgmtCreate,                /* instantiate */
        StackMgmtDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        StackMgmtCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SS7StackMgmtClass = &itsENGINE_SS7StackMgmtClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a ISS7Stack object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ISS7StackClass, app, name,
                            variant, numThreads);
 *
 *  See Also:
 ****************************************************************************/
static int
ISS7StackCreate(ITS_Object obj, va_list args)
{
    ENGINE_ISS7Stack stack = (ENGINE_ISS7Stack)obj;
    ENGINE_Application app;
    char *name;
    int variant;
    ITS_Object *list;
    int numThreads;

    app = va_arg(args, ENGINE_Application);
    name = va_arg(args, char *);
    variant = va_arg(args, int);
    numThreads = va_arg(args, int);

    ITS_C_ASSERT(app != NULL);
    ITS_C_ASSERT(name != NULL && strlen(name) != 0);

    ENGINE_ISS7_NAME(stack) = strdup(name);
    ITS_C_ASSERT(ENGINE_ISS7_NAME(stack) != NULL);

    if (numThreads <= 0)
    {
        numThreads = 1;
    }
    ENGINE_ISS7_NUM_THREADS(stack) = numThreads;

    if (variant)
    {
        ENGINE_ISS7_VARIANT(stack) = variant;
    }

    /* tail add */
    for (list = &ENGINE_APP_ISS7_STACK_CTRL(app);
         *list;
         list = &ENGINE_ISS7_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a ISS7 object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1788
 *
 ****************************************************************************/
static void
ISS7StackDestroy(ITS_Object obj)
{
    int i;
    ITS_Object list, tmp;

    free(ENGINE_ISS7_NAME(obj));

    for (list = ENGINE_ISS7_TRACE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_ISS7_LINKS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LN_NEXT(list);

        ITS_DestructObject(list);
    }

    if (ENGINE_ISS7_NUM_TIMERS(obj))
    {
        for (i = 0; i < ENGINE_ISS7_NUM_TIMERS(obj); i++)
        {
            free(ENGINE_ISS7_TIMERS(obj)[i]);
        }

        free(ENGINE_ISS7_TIMERS(obj));
    }

    if (ENGINE_ISS7_NUM_MODIFIERS(obj))
    {
        for (i = 0; i < ENGINE_ISS7_NUM_MODIFIERS(obj); i++)
        {
            free(ENGINE_ISS7_MODIFIERS(obj)[i]);
        }

        free(ENGINE_ISS7_MODIFIERS(obj));
    }

    if (ENGINE_ISS7_VARIANT_NAME(obj))
    {
        free(ENGINE_ISS7_VARIANT_NAME(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare ISS7 stack records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ISS7StackCompare(ITS_Object o1, ITS_Object o2)
{
    int i;

    if (strcmp(ENGINE_ISS7_NAME(o1), ENGINE_ISS7_NAME(o2)) != 0 ||
        ENGINE_ISS7_NUM_THREADS(o1) != ENGINE_ISS7_NUM_THREADS(o2))
    {
        return (ITS_FALSE);
    }

    if (ENGINE_ISS7_VARIANT(o1) != ENGINE_ISS7_VARIANT(o2))
    {
        return (ITS_FALSE);
    }

    if (ENGINE_ISS7_NUM_TIMERS(o1) != ENGINE_ISS7_NUM_TIMERS(o2) ||
        ENGINE_ISS7_NUM_MODIFIERS(o1) != ENGINE_ISS7_NUM_MODIFIERS(o2))
    {
        return (ITS_FALSE);
    }

    for (i = 0; i < ENGINE_ISS7_NUM_TIMERS(o1); i++)
    {
        if (strcmp(ENGINE_ISS7_TIMERS(o1)[i],
                   ENGINE_ISS7_TIMERS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    for (i = 0; i < ENGINE_ISS7_NUM_MODIFIERS(o1); i++)
    {
        if (strcmp(ENGINE_ISS7_MODIFIERS(o1)[i],
                   ENGINE_ISS7_MODIFIERS(o2)[i]) != 0)
        {
            return (ITS_FALSE);
        }
    }

    return (ITS_TRUE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ISS7StackClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ISS7StackRec),    /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE ISS7Stack Class",       /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ISS7StackCreate,                /* instantiate */
        ISS7StackDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ISS7StackCompare,               /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ISS7StackClass = &itsENGINE_ISS7StackClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtCallback object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtCallbackClass,
 *              list,
 *              type, 
 *              functionName,
 *              libraryName);
 *
 *  See Also:
 ****************************************************************************/
static int
FtCallbackCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtCallback ftCallback = (ENGINE_FtCallback)obj;
    ENGINE_FtCallbackType type;
    char* functionName;
    char* libraryName;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    type = (ENGINE_FtCallbackType)va_arg(args, int);
    functionName = va_arg(args, char*);
    libraryName = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_CALLBACK_TYPE(ftCallback) = type;

    if (functionName && strlen(functionName) != 0)
    {
        ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) = 
            strdup(functionName);

        ITS_C_ASSERT(ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) != NULL);
    }

    if (libraryName && strlen(libraryName) != 0)
    {
        ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) = 
            strdup(libraryName);

        ITS_C_ASSERT(ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) != NULL);
    }

    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_CALLBACK_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtCallback object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
FtCallbackDestroy(ITS_Object obj)
{
    ENGINE_FtCallback ftCallback = (ENGINE_FtCallback)obj;

    if (ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback) != NULL)
    {
        free(ENGINE_FT_CALLBACK_FUNCTION_NAME(ftCallback));
    }

    if (ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback) != NULL)
    {
        free(ENGINE_FT_CALLBACK_LIBRARY_NAME(ftCallback));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtCallback records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtCallbackCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtCallbackClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtCallbackRec),       /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtCallback Class",          /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtCallbackCreate,                   /* instance create          */
        FtCallbackDestroy,                  /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtCallbackCompare,                  /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtCallbackClass = &itsENGINE_FtCallbackClassRec;



/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtGroup Member object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupMemberClass,
 *              list,
 *              type,
 *              nodeId,
 *              nodeName,
 *              processId,
 *              processName);
 *
 *  See Also:
 ****************************************************************************/
static int
FtGroupMemberCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtGroupMember ftGroupMember = (ENGINE_FtGroupMember)obj;
    ENGINE_FtGroupMemberType type;
    ITS_USHORT nodeId;
    char* nodeName;
    ITS_USHORT processId;
    char* processName;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    type = (ENGINE_FtGroupMemberType)va_arg(args, int);
    nodeId = (ITS_USHORT)va_arg(args, int);
    nodeName = va_arg(args, char*);
    processId = (ITS_USHORT)va_arg(args, int);
    processName = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_GROUP_MEMBER_TYPE(ftGroupMember) = type;
    ENGINE_FT_GROUP_MEMBER_NODE_ID(ftGroupMember) = nodeId;

    if (nodeName && strlen(nodeName) != 0)
    {
        ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) =
            strdup(nodeName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) != NULL);
    }

    ENGINE_FT_GROUP_MEMBER_PROCESS_ID(ftGroupMember) = processId;

    if (processName && strlen(processName) != 0)
    {
        ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) =
            strdup(processName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) != NULL);
    }
    
    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_GROUP_MEMBER_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtGroup Member object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
FtGroupMemberDestroy(ITS_Object obj)
{
    ENGINE_FtGroupMember ftGroupMember = (ENGINE_FtGroupMember)obj;

    if (ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember) != NULL)
    {
        free(ENGINE_FT_GROUP_MEMBER_NODE_NAME(ftGroupMember));
    }

    if (ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember) != NULL)
    {
        free(ENGINE_FT_GROUP_MEMBER_PROCESS_NAME(ftGroupMember));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtGroupMember records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtGroupMemberCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtGroupMemberClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtGroupMemberRec),    /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtGroup Member Class",      /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtGroupMemberCreate,                /* instance create          */
        FtGroupMemberDestroy,               /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtGroupMemberCompare,               /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtGroupMemberClass = &itsENGINE_FtGroupMemberClassRec;


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a FtGroup object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
 *      ITS_ConstructObject(
 *              itsENGINE_FtGroupClass,
 *              list,
 *              ftGroupId,
 *              ftGroupName,
 *              dsmSize,
 *              dsmBaseAddress,
 *              dsmMaxNumTables,
 *              dsmType);
 *
 *  See Also:
 ****************************************************************************/
static int
FtGroupCreate(ITS_Object obj, va_list args)
{
    ENGINE_FtGroup ftGroup = (ENGINE_FtGroup)obj;
    ITS_USHORT ftGroupId;
    char* ftGroupName;
    ITS_UINT dsmSize;
    char* dsmBaseAddress;
    ITS_UINT dsmMaxNumTables;
    char* dsmType;
    ITS_Object* rlist;
    ITS_Object* list;

    rlist = va_arg(args, ITS_Object*);
    ftGroupId = (ITS_USHORT)va_arg(args, int);
    ftGroupName = va_arg(args, char*);
    dsmSize = (ITS_UINT)va_arg(args, int);
    dsmBaseAddress = va_arg(args, char*);
    dsmMaxNumTables = (ITS_UINT)va_arg(args, int);
    dsmType = va_arg(args, char*);

    ITS_C_REQUIRE(rlist != NULL);

    ENGINE_FT_GROUP_FT_GROUP_ID(ftGroup) = ftGroupId;

    if (ftGroupName && strlen(ftGroupName) != 0)
    {
        ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) =
            strdup(ftGroupName);

        ITS_C_ASSERT(ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_SIZE(ftGroup) = dsmSize;

    if (dsmBaseAddress && strlen(dsmBaseAddress) != 0)
    {
        ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) =
            strdup(dsmBaseAddress);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftGroup) = dsmMaxNumTables;

    if (dsmType && strlen(dsmType) != 0)
    {
        ENGINE_FT_GROUP_DSM_TYPE(ftGroup) = 
            strdup(dsmType);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL);
    }

    /* Add to tail. */
    for (list = rlist; *list; list = &ENGINE_FT_GROUP_NEXT(*list))
    {
    }
    *list = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a FtGroup object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
FtGroupDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    ENGINE_FtGroup ftGroup = (ENGINE_FtGroup)obj;

    if (ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_FT_GROUP_NAME(ftGroup));
    }

    if (ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup));
    }

    if (ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL)
    {
        free(ENGINE_FT_GROUP_DSM_TYPE(ftGroup));
    }

    for (
        list = ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup); 
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_GROUP_MEMBER_NEXT(list);

        ITS_DestructObject(list);
    }

    for (
        list = ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup);
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_GROUP_MEMBER_NEXT(list);

        ITS_DestructObject(list);
    }

    for (
        list = ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup); 
        list != NULL; 
        list = tmp)
    {
        tmp = ENGINE_FT_CALLBACK_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare FtGroup records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FtGroupCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FtGroupClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FtGroupRec),          /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE FtGroup Class",             /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FtGroupCreate,                      /* instance create          */
        FtGroupDestroy,                     /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FtGroupCompare,                     /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FtGroupClass = &itsENGINE_FtGroupClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a Fault Tolerance object.
 *
 *  Input Parameters:
 *      obj - object to create.
 *      args - variable list of arguments.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation.
 *
 *  Notes:
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
 *  See Also:
 ****************************************************************************/
static int
FaultToleranceCreate(ITS_Object obj, va_list args)
{
    ENGINE_FaultTolerance ft = (ENGINE_FaultTolerance)obj;
    ENGINE_Application app;
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

    app = va_arg(args, ENGINE_Application);
    maxNumFtGroups = (ITS_USHORT)va_arg(args, int);
    maxNumProcesses = (ITS_USHORT)va_arg(args, int);
    maxNumNodes = (ITS_USHORT)va_arg(args, int);
    nodeId = (ITS_USHORT)va_arg(args, int);
    processId = (ITS_USHORT)va_arg(args, int);
    tcapFtGroupId = (ITS_USHORT)va_arg(args, int);
    sccpFtGroupId = (ITS_USHORT)va_arg(args, int);
    mtp3FtGroupId = (ITS_USHORT)va_arg(args, int);
    isupFtGroupId = (ITS_USHORT)va_arg(args, int);
    routingFtGroupId = (ITS_USHORT)va_arg(args, int);
    timersFtGroupId = (ITS_USHORT)va_arg(args, int);
    mgmtDataFtGroupId = (ITS_USHORT)va_arg(args, int);
    ftmPreExecLogicProcName = va_arg(args, char*);
    ftmPreExecLogicProcLibName = va_arg(args, char*);
    ftmLoopExecLogicProcName = va_arg(args, char*);
    ftmLoopExecLogicProcLibName = va_arg(args, char*);
    ftmPostExecLogicProcName = va_arg(args, char*);
    ftmPostExecLogicProcLibName = va_arg(args, char*);

    ITS_C_REQUIRE(obj != NULL);
    ITS_C_REQUIRE(app != NULL);
    ITS_C_ASSERT(ENGINE_APP_FAULT_TOLERANCE(app) == NULL);

    ENGINE_FT_MAX_NUM_FT_GROUPS(ft) = maxNumFtGroups;
    ENGINE_FT_MAX_NUM_PROCESSES(ft) = maxNumProcesses;
    ENGINE_FT_MAX_NUM_NODES(ft) = maxNumNodes;
    ENGINE_FT_NODE_ID(ft) = nodeId;
    ENGINE_FT_PROCESS_ID(ft) = processId;
    ENGINE_FT_TCAP_FT_GROUP_ID(ft) = tcapFtGroupId;
    ENGINE_FT_SCCP_FT_GROUP_ID(ft) = sccpFtGroupId;
    ENGINE_FT_MTP3_FT_GROUP_ID(ft) = mtp3FtGroupId;
    ENGINE_FT_ISUP_FT_GROUP_ID(ft) = isupFtGroupId;
    ENGINE_FT_ROUTING_FT_GROUP_ID(ft) = routingFtGroupId;
    ENGINE_FT_TIMERS_FT_GROUP_ID(ft) = timersFtGroupId;
    ENGINE_FT_MGMT_DATA_FT_GROUP_ID(ft) = mgmtDataFtGroupId;

    if (ftmPreExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPreExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPreExecLogicProcLibName && 
        strlen(ftmPreExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPreExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcName && 
        strlen(ftmLoopExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmLoopExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcLibName && 
        strlen(ftmLoopExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmLoopExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPostExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcLibName && 
        strlen(ftmPostExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPostExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }

    ENGINE_APP_FAULT_TOLERANCE(app) = obj;

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a Fault Tolerance object.
 *
 *  Input Parameters:
 *      obj - object to destroy.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
FaultToleranceDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;

    ENGINE_FaultTolerance ft = (ENGINE_FaultTolerance)obj;

    if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft));
    }

    if (ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL)
    {
        free(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft));
    }

    for (list = ENGINE_FT_CALLBACKS(ft); list != NULL; list = tmp)
    {
        tmp = ENGINE_FT_CALLBACK_NEXT(list);

        ITS_DestructObject(list);
    }

    for (list = ENGINE_FT_FT_GROUPS(ft); list != NULL; list = tmp)
    {
        tmp = ENGINE_FT_GROUP_NEXT(list);

        ITS_DestructObject(list);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare Fault Tolerance records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - objects to compare.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent. ITS_FALSE otherwise.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
FaultToleranceCompare(ITS_Object o1, ITS_Object o2)
{
    /* Irrelevant. */
    return ITS_FALSE;
}

ITSDLLAPI ITS_ClassRec itsENGINE_FaultToleranceClassRec =
{
    {
        &itsCORE_ClassRec,                  /* CORE is superclass       */
        sizeof(ENGINE_FaultToleranceRec),   /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        "ENGINE Fault Tolerance Class",     /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        FaultToleranceCreate,               /* instance create          */
        FaultToleranceDestroy,              /* instance destroy         */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serialize        */
        FaultToleranceCompare,              /* equals                   */
        NULL                                /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsENGINE_FaultToleranceClass = &itsENGINE_FaultToleranceClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a application object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ApplicationClass, isService,
 *                          usesCPP, globalStartMask, "libCISCO.so",
 *                          "ss7Selector", "appSelector", "appDeselector");
 *
 *  See Also:
 ****************************************************************************/
static int
ApplicationCreate(ITS_Object obj, va_list args)
{
    ENGINE_Application app = (ENGINE_Application)obj;
    ITS_BOOLEAN isService;
    ITS_BOOLEAN usesCpp;
    ITS_UINT gsMask;
    char *libName, *ss7Selector, *appSelector, *appDeselector, *hmi, *alarm;
    char *preFunc, *postFunc;

    isService = va_arg(args, ITS_BOOLEAN);
    usesCpp = va_arg(args, ITS_BOOLEAN);
    gsMask = va_arg(args, ITS_UINT);
    libName = va_arg(args, char *);
    ss7Selector = va_arg(args, char *);
    appSelector = va_arg(args, char *);
    appDeselector = va_arg(args, char *);
    hmi = va_arg(args, char *);
    alarm = va_arg(args, char *);
    preFunc = va_arg(args, char *);
    postFunc = va_arg(args, char *);

    ENGINE_APP_IS_SERVICE(app) = isService;
    ENGINE_APP_CPP_BINDING(app) = usesCpp;
    ENGINE_APP_GS_MASK(app) = gsMask;
    if (libName && strlen(libName) != 0)
    {
        ENGINE_APP_LIB_NAME(app) = strdup(libName);

        ITS_C_ASSERT(ENGINE_APP_LIB_NAME(app) != NULL);
    }
    if (ss7Selector && strlen(ss7Selector) != 0)
    {
        ENGINE_APP_SS7_SELECTOR(app) = strdup(ss7Selector);

        ITS_C_ASSERT(ENGINE_APP_SS7_SELECTOR(app) != NULL);
    }
    if (appSelector && strlen(appSelector) != 0)
    {
        ENGINE_APP_APP_SELECTOR(app) = strdup(appSelector);

        ITS_C_ASSERT(ENGINE_APP_APP_SELECTOR(app) != NULL);
    }
    if (appDeselector && strlen(appDeselector) != 0)
    {
        ENGINE_APP_APP_DESELECTOR(app) = strdup(appDeselector);

        ITS_C_ASSERT(ENGINE_APP_APP_DESELECTOR(app) != NULL);
    }
    if (hmi && strlen(hmi) != 0)
    {
        ENGINE_APP_HMI_CB(app) = strdup(alarm);

        ITS_C_ASSERT(ENGINE_APP_HMI_CB(app) != NULL);
    }
    if (alarm && strlen(alarm) != 0)
    {
        ENGINE_APP_ALARM_CB(app) = strdup(alarm);

        ITS_C_ASSERT(ENGINE_APP_ALARM_CB(app) != NULL);
    }
    if (preFunc && strlen(preFunc) != 0)
    {
        ENGINE_APP_PRE_FUNC(app) = strdup(preFunc);

        ITS_C_ASSERT(ENGINE_APP_PRE_FUNC(app) != NULL);
    }
    if (postFunc && strlen(postFunc) != 0)
    {
        ENGINE_APP_POST_FUNC(app) = strdup(postFunc);

        ITS_C_ASSERT(ENGINE_APP_POST_FUNC(app) != NULL);
    }

    ENGINE_APP_OPTIONS(app) = NULL;
    ENGINE_APP_NUM_OPTIONS(app) = 0;
    ENGINE_APP_LIB_CACHE(app) = NULL;
    ENGINE_APP_TRACE_LEVELS(app) = NULL;
    ENGINE_APP_FEATURES(app) = NULL;
    ENGINE_APP_POOLS(app) = NULL;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a application object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ApplicationDestroy(ITS_Object obj)
{
    ITS_Object tmp, list;
    int i;

    if (ENGINE_APP_LIB_NAME(obj))
    {
        free(ENGINE_APP_LIB_NAME(obj));
    }

    if (ENGINE_APP_SS7_SELECTOR(obj))
    {
        free(ENGINE_APP_SS7_SELECTOR(obj));
    }

    if (ENGINE_APP_APP_SELECTOR(obj))
    {
        free(ENGINE_APP_APP_SELECTOR(obj));
    }

    if (ENGINE_APP_PRE_FUNC(obj))
    {
        free(ENGINE_APP_PRE_FUNC(obj));
    }

    if (ENGINE_APP_POST_FUNC(obj))
    {
        free(ENGINE_APP_POST_FUNC(obj));
    }

    for (list = ENGINE_APP_LIB_CACHE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_LC_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_TRACE_LEVELS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_FEATURES(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_FEAT_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_POOLS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TP_NEXT(list);

        ITS_DestructObject(list);
    }
    for (list = ENGINE_APP_PARSER_EXTENSIONS(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_PE_NEXT(list);

        ITS_DestructObject(list);
    }

    if (ENGINE_APP_FAULT_TOLERANCE(obj))
    {
        ITS_DestructObject(ENGINE_APP_FAULT_TOLERANCE(obj));
    }

    if (ENGINE_APP_NUM_OPTIONS(obj))
    {
        for (i = 0; i < ENGINE_APP_NUM_OPTIONS(obj); i++)
        {
            free(ENGINE_APP_OPTIONS(obj)[i]);
        }

        free(ENGINE_APP_OPTIONS(obj));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare application records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
ApplicationCompare(ITS_Object o1, ITS_Object o2)
{
    /* no point */
    return (ITS_FALSE);
}

ITSDLLAPI ITS_ClassRec itsENGINE_ApplicationClassRec =
{
    {
        &itsCORE_ClassRec,              /* superclass */
        sizeof(ENGINE_ApplicationRec),  /* instance size */
        ITS_FALSE,                      /* class initted */
        0,                              /* class ref count */
        "ENGINE Application Class",     /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ApplicationCreate,              /* instantiate */
        ApplicationDestroy,             /* destroy */
        ITS_INST_CLONE_INHERIT,         /* clone */
        ITS_INST_PRINT_INHERIT,         /* print */
        ITS_INST_SERIAL_INHERIT,        /* serialize */
        ApplicationCompare,             /* equals */
        ITS_INST_HASH_INHERIT           /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_ApplicationClass = &itsENGINE_ApplicationClassRec;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize the necessary engine classes.
 *
 ****************************************************************************/
static void
InitClasses()
{
    int ret;

    ret = ITS_InitializeClass(itsCORE_Class);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LibCacheClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_FeatureClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TraceClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_RouteClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_DestClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LinkSetClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_LinkClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportSpecificsClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportCallbacksClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_TransportClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_WorkItemClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ThreadPoolClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_SS7StackMgmtClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ISS7StackClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_FaultToleranceClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ParserExtensionClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    ret = ITS_InitializeClass(itsENGINE_ApplicationClass);

    ITS_C_ASSERT(ret == ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Terminate the necessary engine classes.
 *
 ****************************************************************************/
static void
TermClasses()
{
    ITS_DestroyClass(itsENGINE_ApplicationClass);
    ITS_DestroyClass(itsENGINE_ParserExtensionClass);
    ITS_DestroyClass(itsENGINE_FaultToleranceClass);
    ITS_DestroyClass(itsENGINE_ISS7StackClass);
    ITS_DestroyClass(itsENGINE_SS7StackMgmtClass);
    ITS_DestroyClass(itsENGINE_ThreadPoolClass);
    ITS_DestroyClass(itsENGINE_WorkItemClass);
    ITS_DestroyClass(itsENGINE_TransportCallbacksClass);
    ITS_DestroyClass(itsENGINE_TransportSpecificsClass);
    ITS_DestroyClass(itsENGINE_TransportClass);
    ITS_DestroyClass(itsENGINE_LinkClass);
    ITS_DestroyClass(itsENGINE_LinkSetClass);
    ITS_DestroyClass(itsENGINE_DestClass);
    ITS_DestroyClass(itsENGINE_RouteClass);
    ITS_DestroyClass(itsENGINE_TraceClass);
    ITS_DestroyClass(itsENGINE_FeatureClass);
    ITS_DestroyClass(itsENGINE_LibCacheClass);
}

static char *ANSI_Variants[] =
{
    NULL,
    "ANSI_88",
    "ANSI_92",
    "ANSI_96",
    NULL
};

static char *CCITT_Variants[] =
{
    NULL,
    "BlueBook",
    "WhiteBook",
    "WhiteBook_97",
    NULL
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Figure out variant by name
 *
 *  Input Parameters:
 *      string - variant string
 *
 *  Notes:
 ****************************************************************************/
static int
GetANSIVariant(const char *name)
{
    int i;

    for (i = 1; ANSI_Variants[i] != NULL; i++)
    {
        if (strcmp(name, ANSI_Variants[i]) == 0)
        {
            return (i);
        }
    }

    return (ITS_LATEST_GEN);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Figure out variant by name
 *
 *  Input Parameters:
 *      string - variant string
 *
 *  Notes:
 ****************************************************************************/
static int
GetCCITTVariant(const char *name)
{
    int i;

    for (i = 1; CCITT_Variants[i] != NULL; i++)
    {
        if (strcmp(name, CCITT_Variants[i]) == 0)
        {
            return (i);
        }
    }

    return (ITS_LATEST_GEN);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse application level attributes
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_ApplicationClass, isService,
 *                          usesCPP, globalStartMask, "libCISCO.so",
 *                          "ss7Selector", "appSelector", "appDeselector",
 *                          "hmi", "alarm", "preFunc", "postFunc");
 ****************************************************************************/
static void
HandleApplication(const char **attr)
{
    ITS_BOOLEAN cppBinding = ITS_TRUE;
    ITS_BOOLEAN isService = ITS_FALSE;
    ITS_UINT mask = 0;
    const char *lib = NULL, *ss7 = NULL, *app = NULL, *appD = NULL;
    const char *hmi = NULL, *alarm = NULL;
    const char *preFunc = NULL, *postFunc = NULL;

    /* parse the attributes */
    while (*attr)
    {
        const char *tattr = *attr;

        attr++;
        if (strcmp(tattr, NAME_STRING) == 0)
        {
            APPL_SetName(*attr);
        }
        else if (strcmp(tattr, TYPE_STRING) == 0)
        {
            if (strcmp(*attr, SERVICE_STRING) == 0)
            {
                isService = ITS_TRUE;
            }
        }
        else if (strcmp(tattr, BINDING_STRING) == 0)
        {
            if (strcmp(*attr, "C") == 0)
            {
                cppBinding = ITS_FALSE;
            }
        }
        else if (strcmp(tattr, LIBRARY_STRING) == 0)
        {
            lib = *attr;
        }
        else if (strcmp(tattr, SS7_SELECT_STRING) == 0)
        {
            ss7 = *attr;
        }
        else if (strcmp(tattr, APP_SELECT_STRING) == 0)
        {
            app = *attr;
        }
        else if (strcmp(tattr, APP_DESELECT_STRING) == 0)
        {
            appD = *attr;
        }
        else if (strcmp(tattr, HMI_CB_STRING) == 0)
        {
            hmi = *attr;
        }
        else if (strcmp(tattr, ALARM_CB_STRING) == 0)
        {
            alarm = *attr;
        }
        else if (strcmp(tattr, PRE_FUNC_STRING) == 0)
        {
            preFunc = *attr;
        }
        else if (strcmp(tattr, POST_FUNC_STRING) == 0)
        {
            postFunc = *attr;
        }
        else if (strcmp(tattr, GS_STRING) == 0)
        {
            /* filter it out here */
            /* hardcode the strings.  These will never change. */
            if (strstr(*attr, "ANSI-MTP3") != NULL)
            {
                mask |= ITS_MTP3_ANSI;
            }
            if (strstr(*attr, "ANSI-ISUP") != NULL)
            {
                mask |= ITS_ISUP_ANSI;
            }
            if (strstr(*attr, "ANSI-SCCP") != NULL)
            {
                mask |= ITS_SCCP_ANSI;
            }
            if (strstr(*attr, "ANSI-TCAP") != NULL)
            {
                mask |= ITS_TCAP_ANSI;
            }
            if (strstr(*attr, "ANSI-MTP2") != NULL)
            {
                mask |= ITS_MTP2_ANSI;
            }
            if (strstr(*attr, "ITU-MTP2") != NULL)
            {
                mask |= ITS_MTP2_CCITT;
            }
            if (strstr(*attr, "ITU-MTP3") != NULL)
            {
                mask |= ITS_MTP3_CCITT;
            }
            if (strstr(*attr, "ITU-ISUP") != NULL)
            {
                mask |= ITS_ISUP_CCITT;
            }
            if (strstr(*attr, "ITU-SCCP") != NULL)
            {
                mask |= ITS_SCCP_CCITT;
            }
            if (strstr(*attr, "ITU-TCAP") != NULL)
            {
                mask |= ITS_TCAP_CCITT;
            }
            if (strstr(*attr, "PRC-MTP3") != NULL)
            {
                mask |= ITS_MTP3_PRC;
            }
            if (strstr(*attr, "PRC-ISUP") != NULL)
            {
                mask |= ITS_ISUP_PRC;
            }
            if (strstr(*attr, "PRC-SCCP") != NULL)
            {
                mask |= ITS_SCCP_PRC;
            }
            if (strstr(*attr, "PRC-TCAP") != NULL)
            {
                mask |= ITS_TCAP_PRC;
            } 
            if (strstr(*attr, "TTC-MTP3") != NULL)
            {
                mask |= ITS_MTP3_TTC;
            }
            if (strstr(*attr, "TTC-ISUP") != NULL)
            {
                mask |= ITS_ISUP_TTC;
            }
            if (strstr(*attr, "TTC-SCCP") != NULL)
            {
                mask |= ITS_SCCP_TTC;
            }
            if (strstr(*attr, "TTC-TCAP") != NULL)
            {
                mask |= ITS_TCAP_TTC;
            } 

        }

        attr++;
    }

    /* build the config object */
    application = (ENGINE_Application)
                    ITS_ConstructObject(itsENGINE_ApplicationClass,
                                        isService, cppBinding,
                                        mask, lib, ss7, app, appD,
                                        hmi, alarm,
                                        preFunc, postFunc);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse application level options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleOption(const char **attr)
{
    char buf[ITS_PATH_MAX];
    char **opts = NULL;
    int numOpts = 0;
    const char *name = NULL, *value = NULL;

    ITS_C_ASSERT(application != NULL);

    opts = ENGINE_APP_OPTIONS(application);
    numOpts = ENGINE_APP_NUM_OPTIONS(application);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            name = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(name && value);

    sprintf(buf, "%s=%s", name, value);

    numOpts++;

    opts = (char **)realloc(opts, numOpts * sizeof(char *));
    ITS_C_ASSERT(opts != NULL);

    opts[numOpts - 1] = malloc(strlen(buf) + 1);
    ITS_C_ASSERT(opts[numOpts - 1] != NULL);

    strcpy(opts[numOpts - 1], buf);

    ENGINE_APP_NUM_OPTIONS(application) = numOpts;
    ENGINE_APP_OPTIONS(application) = opts;
}

static ITS_BOOLEAN inFaultTolerance = ITS_FALSE;
static ENGINE_FaultTolerance faultTolerance = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start Fault Tolerance.
 *
 *  Input Parameters:
 *      attr - Fault Tolerance element attributes.
 *
 ****************************************************************************/
static void
StartFaultTolerance(const char** attr)
{
    ITS_USHORT maxNumFtGroups           = 0;
    ITS_USHORT maxNumProcesses          = 0;
    ITS_USHORT maxNumNodes              = 0;
    ITS_USHORT nodeId                   = (ITS_USHORT)(-1);
    ITS_USHORT processId                = (ITS_USHORT)(-1);
    ITS_USHORT tcapFtGroupId            = 0;
    ITS_USHORT sccpFtGroupId            = 0;
    ITS_USHORT mtp3FtGroupId            = 0;
    ITS_USHORT isupFtGroupId            = 0;
    ITS_USHORT routingFtGroupId         = 0;
    ITS_USHORT timersFtGroupId          = 0;
    ITS_USHORT mgmtDataFtGroupId        = 0;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, MAX_NUM_FT_GRPS_STRING) == 0)
        {
            attr++;
            maxNumFtGroups = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MAX_NUM_PROCS_STRING) == 0)
        {
            attr++;
            maxNumProcesses = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MAX_NUM_NODES_STRING) == 0)
        {
            attr++;
            maxNumNodes = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, TCAP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            tcapFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, SCCP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            sccpFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MTP3_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            mtp3FtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, ISUP_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            isupFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, ROUTING_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            routingFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, TIMERS_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            timersFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, MGMT_DATA_FT_GRP_ID_STRING) == 0)
        {
            attr++;
            mgmtDataFtGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    object = ITS_ConstructObject(
                    itsENGINE_FaultToleranceClass,
                    application,
                    (int)maxNumFtGroups,
                    (int)maxNumProcesses,
                    (int)maxNumNodes,
                    (int)nodeId,
                    (int)processId,
                    (int)tcapFtGroupId,
                    (int)sccpFtGroupId,
                    (int)mtp3FtGroupId,
                    (int)isupFtGroupId,
                    (int)routingFtGroupId,
                    (int)timersFtGroupId,
                    (int)mgmtDataFtGroupId,
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    NULL  /* To be overwritten. */);

    ITS_C_ASSERT(object != NULL);

    faultTolerance = (ENGINE_FaultTolerance)object;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      End Fault Tolerance.
 *
 ****************************************************************************/
static void
EndFaultTolerance()
{
    faultTolerance = NULL;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmPreExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmPreExecuteLogicProcedure(const char** attr)
{
    const char* ftmPreExecLogicProcName = NULL;
    const char* ftmPreExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmPreExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmPreExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmPreExecLogicProcName && 
        strlen(ftmPreExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPreExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPreExecLogicProcLibName && 
        strlen(ftmPreExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPreExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_PRE_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmLoopExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmLoopExecuteLogicProcedure(const char** attr)
{
    const char* ftmLoopExecLogicProcName = NULL;
    const char* ftmLoopExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmLoopExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmLoopExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmLoopExecLogicProcName && 
        strlen(ftmLoopExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmLoopExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmLoopExecLogicProcLibName && 
        strlen(ftmLoopExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmLoopExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_LOOP_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtmPostExecuteLogicProcedure.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtmPostExecuteLogicProcedure(const char** attr)
{
    const char* ftmPostExecLogicProcName = NULL;
    const char* ftmPostExecLogicProcLibName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            ftmPostExecLogicProcLibName = *attr;
            attr++;
        }
        else if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            ftmPostExecLogicProcName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    /* 
     * Overwrites. 
     */

    if (ftmPostExecLogicProcName && 
        strlen(ftmPostExecLogicProcName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) = 
            strdup(ftmPostExecLogicProcName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_NAME(ft) != NULL);
    }

    if (ftmPostExecLogicProcLibName && 
        strlen(ftmPostExecLogicProcLibName) != 0)
    {
        ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) = 
            strdup(ftmPostExecLogicProcLibName);

        ITS_C_ASSERT(ENGINE_FT_FTM_POST_EXEC_LOGIC_PROC_LIB_NAME(ft) != NULL);
    }   
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MembershipChangeAllFtGroupsCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMembershipChangeAllFtGroupsCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_CALLBACKS(ft),
                    (int)FT_CALLBACK_MEMBERSHIP_CHANGE_ALL_FT_GROUPS,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle EventFromAllFtGroupMembersCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleEventFromAllFtGroupMembersCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_CALLBACKS(ft),
                    (int)FT_CALLBACK_EVENT_FROM_ALL_FT_GROUP_MEMBERS,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

static ITS_BOOLEAN inFtGroup = ITS_FALSE;
static ENGINE_FtGroup currentFtGroup = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start FtGroup.
 *
 *  Input Parameters:
 *      attr - FtGroup element attributes.
 *
 ****************************************************************************/
static void
StartFtGroup(const char** attr)
{
    ITS_USHORT ftGroupId    = (ITS_USHORT)(-1);
    const char* ftGroupName = NULL;
    ENGINE_FaultTolerance ft = faultTolerance;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FT_GRP_ID_STRING) == 0)
        {
            attr++;
            ftGroupId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, FT_GRP_NAME_STRING) == 0)
        {
            attr++;
            ftGroupName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ft != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupClass,
                    &ENGINE_FT_FT_GROUPS(ft),
                    (int)ftGroupId,
                    ftGroupName,
                    0,    /* To be overwritten. */
                    NULL, /* To be overwritten. */
                    0,    /* To be overwritten. */
                    NULL  /* To be overwritten. */);

    ITS_C_ASSERT(object != NULL);

    currentFtGroup = (ENGINE_FtGroup)object;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      End Fault Tolerance.
 *
 ****************************************************************************/
static void
EndFtGroup()
{
    currentFtGroup = NULL;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle DsmConfig.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleDsmConfig(const char** attr)
{
    ITS_UINT dsmSize = 0;
    const char* dsmBaseAddress = NULL;
    ITS_UINT dsmMaxNumTables = 0;
    const char* dsmType = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;

    while (*attr)
    {
        if (strcmp(*attr, DSM_SIZE_STRING) == 0)
        {
            attr++;
            dsmSize = (ITS_UINT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, DSM_BASE_ADDR_STRING) == 0)
        {
            attr++;
            dsmBaseAddress = *attr;
            attr++;
        }
        else if (strcmp(*attr, DSM_MAX_NUM_TBLS_STRING) == 0)
        {
            attr++;
            dsmMaxNumTables = (ITS_UINT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, DSM_TYPE_STRING) == 0)
        {
            attr++;
            dsmType = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    /* 
     * Overwrites. 
     */

    ENGINE_FT_GROUP_DSM_SIZE(ftGroup) = dsmSize;

    if (dsmBaseAddress && strlen(dsmBaseAddress) != 0)
    {
        ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) = strdup(dsmBaseAddress);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_BASE_ADDRESS(ftGroup) != NULL);
    }

    ENGINE_FT_GROUP_DSM_MAX_NUM_TABLES(ftGroup) = dsmMaxNumTables;

    if (dsmType && strlen(dsmType) != 0)
    {
        ENGINE_FT_GROUP_DSM_TYPE(ftGroup) = strdup(dsmType);

        ITS_C_ASSERT(ENGINE_FT_GROUP_DSM_TYPE(ftGroup) != NULL);
    }       
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle FtGroupMember.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleFtGroupMember(const char** attr)
{
    ITS_USHORT nodeId = (ITS_USHORT)(-1);
    const char* nodeName = NULL;
    ITS_USHORT processId = (ITS_USHORT)(-1);
    const char* processName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_NAME_STRING) == 0)
        {
            attr++;
            nodeName = *attr;
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_NAME_STRING) == 0)
        {
            attr++;
            processName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupMemberClass,
                    &ENGINE_FT_GROUP_FT_GROUP_MEMBERS(ftGroup),
                    (int)FT_GROUP_MEMBER_NORMAL,
                    (int)nodeId,
                    nodeName,
                    (int)processId,
                    processName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MasterFtGroupMember.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMasterFtGroupMember(const char** attr)
{
    ITS_USHORT nodeId = (ITS_USHORT)(-1);
    const char* nodeName = NULL;
    ITS_USHORT processId = (ITS_USHORT)(-1);
    const char* processName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, NODE_ID_STRING) == 0)
        {
            attr++;
            nodeId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, NODE_NAME_STRING) == 0)
        {
            attr++;
            nodeName = *attr;
            attr++;
        }
        else if (strcmp(*attr, PROC_ID_STRING) == 0)
        {
            attr++;
            processId = (ITS_USHORT)atoi(*attr);
            attr++;
        }
        else if (strcmp(*attr, PROC_NAME_STRING) == 0)
        {
            attr++;
            processName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtGroupMemberClass,
                    &ENGINE_FT_GROUP_MASTER_FT_GROUP_MEMBERS(ftGroup),
                    (int)FT_GROUP_MEMBER_MASTER,
                    (int)nodeId,
                    nodeName,
                    (int)processId,
                    processName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MembershipChangeCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleMembershipChangeCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup),
                    (int)FT_CALLBACK_MEMBERSHIP_CHANGE,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle EventFromFtGroupMemberCallback.
 *
 *  Input Parameters:
 *      attr - element's attributes.
 *
 ****************************************************************************/
static void
HandleEventFromFtGroupMemberCallback(const char** attr)
{
    const char* functionName = NULL;
    const char* libraryName = NULL;
    ENGINE_FtGroup ftGroup = currentFtGroup;
    ITS_Object object;

    while (*attr)
    {
        if (strcmp(*attr, FUNCTION_STRING) == 0)
        {
            attr++;
            functionName = *attr;
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            libraryName = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(ftGroup != NULL);

    object = ITS_ConstructObject(
                    itsENGINE_FtCallbackClass,
                    &ENGINE_FT_GROUP_FT_CALLBACKS(ftGroup),
                    (int)FT_CALLBACK_EVENT_FROM_FT_GROUP_MEMBER,
                    functionName,
                    libraryName);

    ITS_C_ASSERT(object != NULL);
}


static ITS_BOOLEAN inWindows = ITS_FALSE;
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse windows crap.
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleWindows(const char **attr)
{
    char buf[ITS_PATH_MAX];
    const char *ifc = NULL, *mask = NULL, *bcast = NULL;
    char **opts = NULL;
    int numOpts = 0;

    ITS_C_ASSERT(application != NULL);

    opts = ENGINE_APP_OPTIONS(application);
    numOpts = ENGINE_APP_NUM_OPTIONS(application);

    while (*attr)
    {
        if (strcmp(*attr, LOCAL_INTERFACE_STRING) == 0)
        {
            attr++;
            ifc = *attr;
            attr++;
        }
        else if (strcmp(*attr, LOCAL_MASK_STRING) == 0)
        {
            attr++;
            mask = *attr;
            attr++;
        }
        else if (strcmp(*attr, LOCAL_BCAST_STRING) == 0)
        {
            attr++;
            bcast = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }

        if (ifc && mask && bcast)
        {
            numOpts += 3;

            opts = (char **)realloc(opts, numOpts * sizeof(char *));
            ITS_C_ASSERT(opts != NULL);

            /* interface */
            sprintf(buf, "%s=%s", LOCAL_INTERFACE_STRING, ifc);
            opts[numOpts - 3] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 3] != NULL);
            strcpy(opts[numOpts - 3], buf);

            /* mask */
            sprintf(buf, "%s=%s", LOCAL_MASK_STRING, mask);
            opts[numOpts - 2] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 2] != NULL);
            strcpy(opts[numOpts - 2], buf);

            /* broadcast */
            sprintf(buf, "%s=%s", LOCAL_BCAST_STRING, bcast);
            opts[numOpts - 1] = (char *)malloc(strlen(buf) + 1);
            ITS_C_ASSERT(opts[numOpts - 1] != NULL);
            strcpy(opts[numOpts - 1], buf);
        }
    }

    ENGINE_APP_OPTIONS(application) = opts;
    ENGINE_APP_NUM_OPTIONS(application) = numOpts;
}

static ITS_BOOLEAN inFeature = ITS_FALSE;
static struct
{
    char *name;
    char *library;
    char *classRec;
    char **opts;
    int  numOpts;
}
curFeature;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse features
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartFeature(const char **attr)
{
    memset(&curFeature, 0, sizeof(curFeature));

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;
            curFeature.name = strdup(*attr);
            ITS_C_ASSERT(curFeature.name != NULL);
            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;
            curFeature.library = strdup(*attr);
            ITS_C_ASSERT(curFeature.library != NULL);
            attr++;
        }
        else if (strcmp(*attr, CLASS_REC_STRING) == 0)
        {
            attr++;
            curFeature.classRec = strdup(*attr);
            ITS_C_ASSERT(curFeature.classRec != NULL);
            attr++;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse feature options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleFeatureOption(const char **attr)
{
    char buf[ITS_PATH_MAX];
    const char *name = NULL, *value = NULL;

    ITS_C_REQUIRE(inFeature);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;
            name = *attr;
            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;
            value = *attr;
            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(name != NULL && value != NULL);

    sprintf(buf, "%s=%s", name, value);

    curFeature.numOpts++;

    curFeature.opts = (char **)realloc(curFeature.opts,
                            curFeature.numOpts * sizeof(char *));
    ITS_C_ASSERT(curFeature.opts != NULL);

    curFeature.opts[curFeature.numOpts - 1] = (char *)malloc(strlen(buf) + 1);
    ITS_C_ASSERT(curFeature.opts[curFeature.numOpts - 1] != NULL);
    strcpy(curFeature.opts[curFeature.numOpts - 1], buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse feature options
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndFeature()
{
    ITS_Object obj;

    obj = ITS_ConstructObject(itsENGINE_FeatureClass, application,
                              curFeature.name, curFeature.library,
                              curFeature.classRec,
                              curFeature.opts, curFeature.numOpts);
    ITS_C_ASSERT(obj != NULL);
}

/*
 * trace data
 */
static ITS_BOOLEAN tkTrace = ITS_FALSE;
static ITS_BOOLEAN sipTrace = ITS_FALSE;
static ITS_BOOLEAN appTrace = ITS_FALSE;
static ITS_BOOLEAN stackTrace = ITS_FALSE;
static ITS_BOOLEAN sigtranTrace = ITS_FALSE;
static ITS_BOOLEAN codecTrace = ITS_FALSE;
static ITS_BOOLEAN vendorTrace = ITS_FALSE;

static int critMask;
static int errMask;
static int warnMask;
static int dbgMask;
static int eventMask;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartTrace(const char **attr)
{
    critMask = TRACE_TO_NONE;
    errMask = TRACE_TO_NONE;
    warnMask = TRACE_TO_NONE;
    dbgMask = TRACE_TO_NONE;
    eventMask = TRACE_TO_NONE;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      parse trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleTrace(const char *el, const char **attr)
{
    int *mask = NULL;

    if (strcmp(el, CRIT_STRING) == 0)
    {
        mask = &critMask;
    }
    else if (strcmp(el, ERR_STRING) == 0)
    {
        mask = &errMask;
    }
    else if (strcmp(el, WARN_STRING) == 0)
    {
        mask = &warnMask;
    }
    else if (strcmp(el, DBG_STRING) == 0)
    {
        mask = &dbgMask;
    }
    else if (strcmp(el, EVENT_STRING) == 0)
    {
        mask = &eventMask;
    }
    else
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, OUTPUT_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ITS_STDOUT_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_DISPLAY;
            }
            else if (strcmp(*attr, ITS_SYSLOG_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_SYSLOG;
            }
            else if (strcmp(*attr, ITS_FILE_STRING) == 0)
            {
                *mask &= ~TRACE_TO_NONE;
                *mask |= TRACE_TO_FILE;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

static ITS_CHAR  vendorName[ITS_PATH_MAX];

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording trace info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndTrace()
{
    ITS_Object *tmp = NULL, level;

    if (tkTrace)
    {
        tmp = &ENGINE_APP_SUPPORT_LEVELS(application);
    }
    else if (sipTrace)
    {
        ITS_C_ASSERT(curSIPAttr != NULL);

        tmp = &ENGINE_SIP_TRACE(curSIPAttr);
    } 
    else if (stackTrace)
    {
        ITS_C_ASSERT(curLayer != NULL);

        tmp = &ENGINE_ISS7_TRACE(curLayer);
    }
    else if (sigtranTrace)
    {
        ITS_C_ASSERT(curSigLayer != NULL);
        tmp = &ENGINE_SIGTRAN_TRACE(curSigLayer);
    }
    else if (codecTrace)
    {
        ITS_C_ASSERT(curCodecLayer != NULL);
        tmp = &ENGINE_CODEC_TRACE(curCodecLayer);
    }
    else if (vendorTrace)
    {
        if (strcmp(vendorName, ADAX_MTP2_STRING) == 0)
            tmp = &ENGINE_APP_VENDOR_ONE_LEVELS(application);
        else if (strcmp(vendorName, NMS_MTP2_STRING) == 0)
            tmp = &ENGINE_APP_VENDOR_TWO_LEVELS(application);
    }
    else
    {
        tmp = &ENGINE_APP_TRACE_LEVELS(application);
    }

    /* create the levels */
    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_CRITICAL_STRING, critMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_ERROR_STRING, errMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_WARNING_STRING, warnMask);
    ITS_C_ASSERT(level != NULL);

    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_DEBUG_STRING, dbgMask);
    ITS_C_ASSERT(level != NULL);
    
    level = ITS_ConstructObject(itsENGINE_TraceClass, tmp,
                                ITS_EVENT_STRING, eventMask);
    ITS_C_ASSERT(level != NULL);
}

static ITS_BOOLEAN  inWorkPool = ITS_FALSE;
static ITS_BOOLEAN  inItemPool = ITS_FALSE;
static ITS_BOOLEAN  inBorderPool = ITS_FALSE;
static ITS_Object   curPool = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording pool info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartPool(const char *el, const char **attr)
{
    ENGINE_ThreadPoolType type;
    int stackSize = 0;

    ITS_C_ASSERT(curPool == NULL);

    if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        type = TP_WORKERS;
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        type = TP_WORK_ITEMS;
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        type = TP_BORDERS;
    }
    else
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, STACK_SIZE_STRING) == 0)
        {
            attr++;

            stackSize = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    curPool = ITS_ConstructObject(itsENGINE_ThreadPoolClass, application,
                                  stackSize, type);
    ITS_C_ASSERT(curPool != NULL);

    if (type == TP_WORK_ITEMS)
    {
        ENGINE_TransportPart thisTrans;
        ITS_Object ret;

        memset(&thisTrans, 0, sizeof(ENGINE_TransportPart));

        /* go ahead and create this transport */
        thisTrans.callbacks =
                  ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                      application, NULL, ITS_FALSE,
                                      DISP_PROT_WORK_ITEM, DISP_BLOCKING,
                                      NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL,
                                      NULL, NULL, DISP_PROT_WORK_ITEM);
        ITS_C_ASSERT(thisTrans.callbacks != NULL);

        thisTrans.mask = ITS_TRANSPORT_TQUEUE;

        ret = ITS_ConstructObject(itsENGINE_TransportClass, curPool,
                                  thisTrans.name, thisTrans.mask, thisTrans.inst,
                                  ITS_FALSE,
                                  thisTrans.specialization, thisTrans.callbacks,
                                  thisTrans.links, thisTrans.workItems);
        ITS_C_ASSERT(ret != NULL);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording pool info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndPool(const char *el)
{
    curPool = NULL;
}

static ITS_BOOLEAN  inTransport = ITS_FALSE;
static ITS_BOOLEAN  isITU = ITS_FALSE;
static ITS_BOOLEAN  isANSI = ITS_FALSE;
static ITS_BOOLEAN  isCHINA = ITS_FALSE;
static ITS_BOOLEAN  isJAPAN = ITS_FALSE;
static int trCount = 0;
static ENGINE_TransportPart thisTrans;
static ENGINE_TransportSpecificsPart thisSpecs;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording transport info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartTransport(const char **attr)
{
    ITS_C_ASSERT(inTransport);
    ITS_C_ASSERT(application != NULL);

    memset(&thisTrans, 0, sizeof(ENGINE_TransportPart));
    memset(&thisSpecs, 0, sizeof(ENGINE_TransportSpecificsPart));
    isITU = ITS_FALSE;
    isANSI = ITS_FALSE;
    isCHINA = ITS_FALSE;
    isJAPAN = ITS_FALSE;
    trCount = 0;

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, T_SS7_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SS7 |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_FIFO_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_FIFO |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_GFIFO_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_GFIFO |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_CSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_CSOCKET |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_SSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SSOCKET |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_ISOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_SSOCKET |
                                    ITS_TRANSPORT_SSOCKET_ITER |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_DSOCK_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_DATAGRAM |
                                    ITS_TRANSPORT_DELAY_CREATE;
            }
            else if (strcmp(*attr, T_VIRT_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_DATAGRAM |
                                    ITS_TRANSPORT_DGRAM_VIRT;
            }
            else if (strcmp(*attr, T_TQ_STRING) == 0)
            {
                thisTrans.mask = ITS_TRANSPORT_TQUEUE;
            }
            else
            {
                ITS_C_ASSERT(ITS_FALSE);
            }

            attr++;
        }
        else if (strcmp(*attr, INSTANCE_STRING) == 0)
        {
            attr++;

            thisTrans.inst = atoi(*attr);

            attr++;
        }
        else if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            thisTrans.name = strdup(*attr);
            ITS_C_ASSERT(thisTrans.name != NULL);

            attr++;
        }
        else if (strcmp(*attr, INTERNODE_STRING) == 0)
        {
            attr++;
 
            thisTrans.isInterNode = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ITU_STRING) == 0)
            {
                isITU = ITS_TRUE;
            }
            else if (strcmp(*attr, ANSI_STRING) == 0)
            {
                isANSI = ITS_TRUE;
            }
            else if (strcmp(*attr, CHINA_STRING) == 0)
            {
                isCHINA = ITS_TRUE;
            }
            else if (strcmp(*attr, JAPAN_STRING) == 0)
            {
                isJAPAN = ITS_TRUE;
            }

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            trCount = atoi(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record transport specifics info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleTransport(const char *el, const char **attr)
{
    switch (ITS_GET_TRANSPORT_TYPE(thisTrans.mask))
    {
    case ITS_TRANSPORT_SS7:
        if (strcmp(el, VENDOR_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, LIBRARY_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorLib = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorLib != NULL);

                    attr++;
                }
                else if (strcmp(*attr, NAME_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorName = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorName != NULL);

                    attr++;
                }
                else if (strcmp(*attr, VENDOR_REC_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.ss7Specs.vendorClass = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.ss7Specs.vendorClass != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        if (strcmp(el, FIFO_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, FIFO_CLIENT_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.fifoSpecs.clientPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.fifoSpecs.clientPath != NULL);

                    attr++;
                }
                else if (strcmp(*attr, FIFO_SERVER_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.fifoSpecs.serverPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.fifoSpecs.serverPath != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        if (strcmp(el, STREAM_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, SOCKET_DOMAIN_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.socketDomain = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.socketDomain != NULL);

                    attr++;
                }
                else if (strcmp(*attr, SERVER_PATH_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.serverPath = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.serverPath != NULL);

                    attr++;
                }
                else if (strcmp(*attr, SERVER_PORT_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.serverPort = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.serverPort != NULL);

                    attr++;
                }
                else if (strcmp(*attr, RETRY_DELAY_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.retryDelay = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.retryDelay != NULL);

                    attr++;
                }
                else if (strcmp(*attr, RETRY_COUNT_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.tcpSpecs.retryCount = strdup(*attr);
                    ITS_C_ASSERT(thisSpecs.data.tcpSpecs.retryCount != NULL);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            if (strcmp(el, MOD_GDI_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, GDI_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, GDI_REMOTE_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.remotePC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.remotePC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, GDI_REMOTE_SSN_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.gdiSpecs.remoteSSN = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.gdiSpecs.remoteSSN != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            if (strcmp(el, MOD_TALI_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, TALI_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_ADJ_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.adjacentPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.adjacentPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_LOCALLY_ALLOWED_ON_OPEN_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.localAllowedOnOpen = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.localAllowedOnOpen != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, TALI_USE_UPPER_LAYER_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.taliSpecs.useUpperLayer = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.taliSpecs.useUpperLayer != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            if (strcmp(el, MOD_IMAL_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, IMAL_LOCAL_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.localPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.localPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IMAL_ADJ_PC_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.adjacentPC = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.adjacentPC != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IMAL_KEEPALIVE_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.imalSpecs.keepAliveTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.imalSpecs.keepAliveTimeOut != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:
        if (strcmp(el, DGRAM_DATA_STRING) == 0)
        {
            while (*attr)
            {
                if (thisTrans.mask & ITS_TRANSPORT_DGRAM_VIRT)
                {
                    if (strcmp(*attr, SERVER_PATH_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localHost = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localHost != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SERVER_PORT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localPort = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localPort != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
                else
                {
                    if (strcmp(*attr, LOCAL_HOST_NAME_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localHost = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localHost != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, LOCAL_PORT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.udpSpecs.localPort = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.udpSpecs.localPort != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
        }
        else if (strcmp(el, ASSOCIATE_STRING) == 0)
        {
            while (*attr)
            {
                if (strcmp(*attr, VALUE_STRING) == 0)
                {
                    attr++;

                    thisSpecs.data.udpSpecs.numAssociates++;

                    thisSpecs.data.udpSpecs.associates = (char **)
                                            realloc(thisSpecs.data.udpSpecs.associates,
                                                    thisSpecs.data.udpSpecs.numAssociates *
                                                        sizeof(char *));
                    ITS_C_ASSERT(thisSpecs.data.udpSpecs.associates != NULL);

                    thisSpecs.data.udpSpecs.associates[thisSpecs.data.udpSpecs.numAssociates - 1] =
                        malloc(strlen(*attr) + 1);
                    ITS_C_ASSERT(thisSpecs.data.udpSpecs.associates
                                    [thisSpecs.data.udpSpecs.numAssociates - 1] != NULL);

                    strcpy(thisSpecs.data.udpSpecs.associates
                            [thisSpecs.data.udpSpecs.numAssociates - 1],
                           *attr);

                    attr++;
                }
                else
                {
                    attr += 2;
                }
            }
        }

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            break;

        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing */
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */
            break;

        case ITS_TRANSPORT_SCTP_SOCKET:
            /* other homes */
            if (strcmp(el, OTHER_HOME_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, LOCAL_HOST_NAME_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.numExtraHomes++;

                        thisSpecs.data.sctpSpecs.extraHomes = (char **)
                                                realloc(thisSpecs.data.sctpSpecs.extraHomes,
                                                        thisSpecs.data.sctpSpecs.numExtraHomes *
                                                            sizeof(char *));
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.extraHomes != NULL);

                        thisSpecs.data.sctpSpecs.extraHomes
                            [thisSpecs.data.sctpSpecs.numExtraHomes - 1] = malloc(strlen(*attr) + 1);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.extraHomes
                                        [thisSpecs.data.sctpSpecs.numExtraHomes - 1] != NULL);

                        strcpy(thisSpecs.data.sctpSpecs.extraHomes
                                [thisSpecs.data.sctpSpecs.numExtraHomes - 1],
                               *attr);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            else if (strcmp(el, MOD_SCTP_STRING) == 0)
            {
                while (*attr)
                {
                    if (strcmp(*attr, MAX_IN_STREAMS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.maxInStreams = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.maxInStreams != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, NUM_OUT_STREAMS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.numOutStreams = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.numOutStreams != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, MAX_ATTEMPTS_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.maxAttempts = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.maxAttempts != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_COOKIE_LIFE_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.cookieLife = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.cookieLife != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_HB_ON_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.hbOn = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.hbOn != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, INIT_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.initTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.initTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SEND_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.sendTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.sendTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, RECV_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.recvTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.recvTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, HB_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.hbTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.hbTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, SHUT_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.shutdownTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.shutdownTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, PMTU_TIMEOUT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.pmtuTimeOut = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.pmtuTimeOut != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, IS_CLIENT_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.isClient = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.isClient != NULL);

                        attr++;
                    }
                    else if (strcmp(*attr, PAYLOAD_TYPE_STRING) == 0)
                    {
                        attr++;

                        thisSpecs.data.sctpSpecs.payloadType = strdup(*attr);
                        ITS_C_ASSERT(thisSpecs.data.sctpSpecs.payloadType != NULL);

                        attr++;
                    }
                    else
                    {
                        attr += 2;
                    }
                }
            }
            break;

        default:
            ITS_C_ASSERT(ITS_FALSE);
            break;
        }
        break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording transport info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndTransport()
{
    ITS_Object ret;

    /* deal with undefined callbacks */
    if (thisTrans.callbacks == NULL)
    {
        DISP_HandlerType htype, atype = DISP_PROT_USER;
        ITS_BOOLEAN realSS7 = ITS_FALSE;

        if (thisTrans.mask & ITS_TRANSPORT_SS7)
        {
            realSS7 = ITS_TRUE;
        }

        if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
        {
            htype = DISP_PROT_ITERATIVE;

            if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
            {
                atype = DISP_PROT_ANSI;
            }
            else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
            {
                atype = DISP_PROT_CCITT;
            }
            else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
            {
                atype = DISP_PROT_PRC;
            }
            else if ((thisTrans.mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
            {
                atype = DISP_PROT_TTC;
            }
            else
            {
                atype = DISP_PROT_USER;
            }
        }
        else if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            htype = DISP_PROT_ANSI;
        }
        else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            htype = DISP_PROT_CCITT;
        }
        else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            htype = DISP_PROT_PRC;
        }
        else if ((thisTrans.mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            htype = DISP_PROT_TTC;
        }
        else
        {
            htype = DISP_PROT_USER;
        }

        thisTrans.callbacks =
                  ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                      application, NULL, realSS7,
                                      htype, DISP_BLOCKING,
                                      NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL, NULL,
                                      NULL, NULL,
                                      NULL, NULL, atype);
        ITS_C_ASSERT(thisTrans.callbacks != NULL);
    }

    /* create the specifics */
    switch (ITS_GET_TRANSPORT_TYPE(thisTrans.mask))
    {
    case ITS_TRANSPORT_SS7:
        thisTrans.specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                thisTrans.mask,
                                thisSpecs.data.ss7Specs.vendorName, 
                                thisSpecs.data.ss7Specs.vendorLib,
                                thisSpecs.data.ss7Specs.vendorClass);
        ITS_C_ASSERT(thisTrans.specialization != NULL);


        if (thisSpecs.data.ss7Specs.vendorName)
        {
            free(thisSpecs.data.ss7Specs.vendorName);
        }

        if (thisSpecs.data.ss7Specs.vendorLib)
        {
            free(thisSpecs.data.ss7Specs.vendorLib);
        }
        if (thisSpecs.data.ss7Specs.vendorClass)
        {
            free(thisSpecs.data.ss7Specs.vendorClass);
        }
        break;

    case ITS_TRANSPORT_FIFO:
    case ITS_TRANSPORT_GFIFO:
        thisTrans.specialization =
            ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                thisTrans.mask,
                                thisSpecs.data.fifoSpecs.clientPath,
                                thisSpecs.data.fifoSpecs.serverPath);

        if (thisSpecs.data.fifoSpecs.clientPath)
        {
            free(thisSpecs.data.fifoSpecs.clientPath);
        }
        if (thisSpecs.data.fifoSpecs.serverPath)
        {
            free(thisSpecs.data.fifoSpecs.serverPath);
        }
        break;

    case ITS_TRANSPORT_CSOCKET:
    case ITS_TRANSPORT_SSOCKET:
        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_DATA_SOCKET:
            /* nothing set (nothing is required to be) */
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            break;

        case ITS_TRANSPORT_GDI_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.gdiSpecs.localPC,
                                    thisSpecs.data.gdiSpecs.remotePC,
                                    thisSpecs.data.gdiSpecs.remoteSSN);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.gdiSpecs.localPC)
            {
                free(thisSpecs.data.gdiSpecs.localPC);
            }
            if (thisSpecs.data.gdiSpecs.remotePC)
            {
                free(thisSpecs.data.gdiSpecs.remotePC);
            }
            if (thisSpecs.data.gdiSpecs.remoteSSN)
            {
                free(thisSpecs.data.gdiSpecs.remoteSSN);
            }
            break;

        case ITS_TRANSPORT_TALI_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.taliSpecs.localPC,
                                    thisSpecs.data.taliSpecs.adjacentPC,
                                    thisSpecs.data.taliSpecs.localAllowedOnOpen,
                                    thisSpecs.data.taliSpecs.useUpperLayer);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.taliSpecs.localPC)
            {
                free(thisSpecs.data.taliSpecs.localPC);
            }
            if (thisSpecs.data.taliSpecs.adjacentPC)
            {
                free(thisSpecs.data.taliSpecs.adjacentPC);
            }
            if (thisSpecs.data.taliSpecs.localAllowedOnOpen)
            {
                free(thisSpecs.data.taliSpecs.localAllowedOnOpen);
            }
            if (thisSpecs.data.taliSpecs.useUpperLayer)
            {
                free(thisSpecs.data.taliSpecs.useUpperLayer);
            }
            break;

        case ITS_TRANSPORT_IMAL_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount,
                                    thisSpecs.data.imalSpecs.localPC,
                                    thisSpecs.data.imalSpecs.adjacentPC,
                                    thisSpecs.data.imalSpecs.keepAliveTimeOut);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            if (thisSpecs.data.imalSpecs.localPC)
            {
                free(thisSpecs.data.imalSpecs.localPC);
            }
            if (thisSpecs.data.imalSpecs.adjacentPC)
            {
                free(thisSpecs.data.imalSpecs.adjacentPC);
            }
            if (thisSpecs.data.imalSpecs.keepAliveTimeOut)
            {
                free(thisSpecs.data.imalSpecs.keepAliveTimeOut);
            }
            break;

        default:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.tcpSpecs.socketDomain,
                                    thisSpecs.data.tcpSpecs.serverPath,
                                    thisSpecs.data.tcpSpecs.serverPort,
                                    thisSpecs.data.tcpSpecs.retryDelay,
                                    thisSpecs.data.tcpSpecs.retryCount);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.tcpSpecs.socketDomain)
            {
                free(thisSpecs.data.tcpSpecs.socketDomain);
            }
            if (thisSpecs.data.tcpSpecs.serverPath)
            {
                free(thisSpecs.data.tcpSpecs.serverPath);
            }
            if (thisSpecs.data.tcpSpecs.serverPort)
            {
                free(thisSpecs.data.tcpSpecs.serverPort);
            }
            if (thisSpecs.data.tcpSpecs.retryDelay)
            {
                free(thisSpecs.data.tcpSpecs.retryDelay);
            }
            if (thisSpecs.data.tcpSpecs.retryCount)
            {
                free(thisSpecs.data.tcpSpecs.retryCount);
            }
            break;
        }
        break;

    case ITS_TRANSPORT_TQUEUE:
        break;

    case ITS_TRANSPORT_DATAGRAM:

        switch (ITS_GET_TRANSPORT_FLAGS(thisTrans.mask) &
                ITS_TRANSPORT_SOCKP_MASK)
        {
        case ITS_TRANSPORT_SCTP_SOCKET:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.udpSpecs.localHost,
                                    thisSpecs.data.udpSpecs.localPort,
                                    thisSpecs.data.udpSpecs.associates,
                                    thisSpecs.data.udpSpecs.numAssociates,
                                    thisSpecs.data.sctpSpecs.extraHomes,
                                    thisSpecs.data.sctpSpecs.numExtraHomes,
                                    thisSpecs.data.sctpSpecs.maxInStreams,
                                    thisSpecs.data.sctpSpecs.numOutStreams,
                                    thisSpecs.data.sctpSpecs.maxAttempts,
                                    thisSpecs.data.sctpSpecs.cookieLife,
                                    thisSpecs.data.sctpSpecs.hbOn,
                                    thisSpecs.data.sctpSpecs.initTimeOut,
                                    thisSpecs.data.sctpSpecs.sendTimeOut,
                                    thisSpecs.data.sctpSpecs.recvTimeOut,
                                    thisSpecs.data.sctpSpecs.hbTimeOut,
                                    thisSpecs.data.sctpSpecs.shutdownTimeOut,
                                    thisSpecs.data.sctpSpecs.pmtuTimeOut,
                                    thisSpecs.data.sctpSpecs.isClient,
                                    thisSpecs.data.sctpSpecs.payloadType);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.udpSpecs.localHost)
            {
                free(thisSpecs.data.udpSpecs.localHost);
            }
            if (thisSpecs.data.udpSpecs.localPort)
            {
                free(thisSpecs.data.udpSpecs.localPort);
            }
            if (thisSpecs.data.sctpSpecs.maxInStreams)
            {
                free(thisSpecs.data.sctpSpecs.maxInStreams);
            }
            if (thisSpecs.data.sctpSpecs.numOutStreams)
            {
                free(thisSpecs.data.sctpSpecs.numOutStreams);
            }
            if (thisSpecs.data.sctpSpecs.maxAttempts)
            {
                free(thisSpecs.data.sctpSpecs.maxAttempts);
            }
            if (thisSpecs.data.sctpSpecs.cookieLife)
            {
                free(thisSpecs.data.sctpSpecs.cookieLife);
            }
            if (thisSpecs.data.sctpSpecs.hbOn)
            {
                free(thisSpecs.data.sctpSpecs.hbOn);
            }
            if (thisSpecs.data.sctpSpecs.initTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.initTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.sendTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.sendTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.recvTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.recvTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.hbTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.hbTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.shutdownTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.shutdownTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.pmtuTimeOut)
            {
                free(thisSpecs.data.sctpSpecs.pmtuTimeOut);
            }
            if (thisSpecs.data.sctpSpecs.isClient)
            {
                free(thisSpecs.data.sctpSpecs.isClient);
            }
            if (thisSpecs.data.sctpSpecs.payloadType)
            {
                free(thisSpecs.data.sctpSpecs.payloadType);
            }
            break;

        case ITS_TRANSPORT_DATA_SOCKET:
        case ITS_TRANSPORT_RUDP_SOCKET:
            /* nothing yet */

        case ITS_TRANSPORT_IMAL_SOCKET:
            /* not now */

        default:
            thisTrans.specialization =
                ITS_ConstructObject(itsENGINE_TransportSpecificsClass,
                                    thisTrans.mask,
                                    thisSpecs.data.udpSpecs.localHost,
                                    thisSpecs.data.udpSpecs.localPort,
                                    thisSpecs.data.udpSpecs.associates,
                                    thisSpecs.data.udpSpecs.numAssociates);
            ITS_C_ASSERT(thisTrans.specialization != NULL);

            if (thisSpecs.data.udpSpecs.localHost)
            {
                free(thisSpecs.data.udpSpecs.localHost);
            }
            if (thisSpecs.data.udpSpecs.localPort)
            {
                free(thisSpecs.data.udpSpecs.localPort);
            }
            break;
        }
        break;
    }

    /* create the transport */
    ret = ITS_ConstructObject(itsENGINE_TransportClass, curPool,
                              thisTrans.name, thisTrans.mask, thisTrans.inst,
                              thisTrans.isInterNode,
                              thisTrans.specialization, thisTrans.callbacks,
                              thisTrans.links, thisTrans.workItems);
    ITS_C_ASSERT(ret != NULL);

    ENGINE_TR_NUM_ASSOCIATES(ret) = trCount;

    if (thisTrans.name)
    {
        free(thisTrans.name);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle a modifier
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleModifier(const char **attr)
{
    ITS_C_ASSERT(inTransport);

    while (*attr)
    {
        if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, MOD_DATA_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_DATA_SOCKET;
            }
            else if (strcmp(*attr, MOD_GDI_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_GDI_SOCKET;
            }
            else if (strcmp(*attr, MOD_RUDP_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & ITS_TRANSPORT_DATAGRAM);
                thisTrans.mask |= ITS_TRANSPORT_RUDP_SOCKET;
            }
            else if (strcmp(*attr, MOD_TALI_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET));
                thisTrans.mask |= ITS_TRANSPORT_TALI_SOCKET;
            }
            else if (strcmp(*attr, MOD_IMAL_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & (ITS_TRANSPORT_CSOCKET |
                                               ITS_TRANSPORT_SSOCKET |
                                               ITS_TRANSPORT_DATAGRAM));
                thisTrans.mask |= ITS_TRANSPORT_IMAL_SOCKET;
            }
            else if (strcmp(*attr, MOD_SCTP_STRING) == 0)
            {
                ITS_C_ASSERT(thisTrans.mask & ITS_TRANSPORT_DATAGRAM);
                thisTrans.mask |= ITS_TRANSPORT_SCTP_SOCKET;
            }
            else if (strcmp(*attr, MOD_MTP2_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_MTP2_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_MTP2_ANSI;
                }
                if (isCHINA)
                {
                    thisTrans.mask |= ITS_MTP2_PRC;
                }
                if (isJAPAN)
                {
                    thisTrans.mask |= ITS_MTP2_TTC;
                }
            }
            else if (strcmp(*attr, MOD_MTP3_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_MTP3_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_MTP3_ANSI;
                }
                if (isCHINA)
                {
                    thisTrans.mask |= ITS_MTP3_PRC;
                }
                if (isJAPAN)
                {
                    thisTrans.mask |= ITS_MTP3_TTC;
                }
            }
            else if (strcmp(*attr, MOD_ISUP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_ISUP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_ISUP_ANSI;
                }
            }
            else if (strcmp(*attr, MOD_SCCP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_SCCP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_SCCP_ANSI;
                }
            }
            else if (strcmp(*attr, MOD_TCAP_STRING) == 0)
            {
                if (isITU)
                {
                    thisTrans.mask |= ITS_TCAP_CCITT;
                }
                if (isANSI)
                {
                    thisTrans.mask |= ITS_TCAP_ANSI;
                }
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle callbacks
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCustomDispatch(const char **attr)
{
    const char *library = NULL, *cdisp = NULL;

    ITS_C_ASSERT(thisTrans.callbacks == NULL);

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            library = strdup(*attr);
            ITS_C_ASSERT(library != NULL);

            attr++;
        }
        else if (strcmp(*attr, CDISP_STRING) == 0)
        {
            attr++;

            cdisp = strdup(*attr);
            ITS_C_ASSERT(cdisp != NULL);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    thisTrans.callbacks =
              ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                  application, library, ITS_FALSE,
                                  DISP_PROT_CUSTOM, DISP_BLOCKING,
                                  cdisp, NULL,
                                  NULL, NULL, NULL,
                                  NULL, NULL, NULL,
                                  NULL, NULL,
                                  NULL, NULL, DISP_PROT_USER);
    ITS_C_ASSERT(thisTrans.callbacks != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle callbacks
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCallbacks(const char **attr)
{
    ITS_BOOLEAN realSS7 = ITS_FALSE;
    ITS_BOOLEAN blocking = ITS_TRUE;
    DISP_HandlerType htype, atype = DISP_PROT_USER;
    const char *libName = NULL, *preInit = NULL, *postInit = NULL;
    const char *preNext = NULL, *nextFailed = NULL, *postNext = NULL;
    const char *dispUser = NULL, *dispISUP = NULL, *dispSCCP = NULL;
    const char *preAccept = NULL, *onAccept = NULL;
    const char *preTerm = NULL, *postTerm = NULL;

    ITS_C_ASSERT(inTransport);
    ITS_C_ASSERT(thisTrans.callbacks == NULL);

    if (thisTrans.mask & ITS_TRANSPORT_SS7)
    {
        realSS7 = ITS_TRUE;
    }

    if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
    {
        htype = DISP_PROT_ITERATIVE;

        if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
        {
            atype = DISP_PROT_ANSI;
        }
        else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
        {
            atype = DISP_PROT_CCITT;
        }
        else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
        {
            atype = DISP_PROT_PRC;
        }
        else if ((thisTrans.mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
        {
            atype = DISP_PROT_TTC;
        }
        else
        {
            atype = DISP_PROT_USER;
        }
    }
    else if ((thisTrans.mask & ITS_FLAG_ANSI) == ITS_FLAG_ANSI)
    {
        htype = DISP_PROT_ANSI;
    }
    else if ((thisTrans.mask & ITS_FLAG_CCITT) == ITS_FLAG_CCITT)
    {
        htype = DISP_PROT_CCITT;
    }
    else if ((thisTrans.mask & ITS_FLAG_PRC) == ITS_FLAG_PRC)
    {
        htype = DISP_PROT_PRC;
    }
    else if ((thisTrans.mask & ITS_FLAG_TTC) == ITS_FLAG_TTC)
    {
        htype = DISP_PROT_TTC;
    }
    else
    {
        htype = DISP_PROT_USER;
    }

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, NBLOCK_STRING) == 0)
            {
                blocking = ITS_FALSE;
            }
            else if (strcmp(*attr, TYPE_DBC_STRING) == 0)
            {
                if (thisTrans.mask & ITS_TRANSPORT_SSOCKET_ITER)
                {
                    atype = DISP_PROT_DBC;
                }
                else
                {
                    htype = DISP_PROT_DBC;
                }
            }

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_INIT_STRING) == 0)
        {
            attr++;

            preInit = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_INIT_STRING) == 0)
        {
            attr++;

            postInit = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_NEXT_STRING) == 0)
        {
            attr++;

            preNext = *attr;

            attr++;
        }
        else if (strcmp(*attr, NEXT_FAIL_STRING) == 0)
        {
            attr++;

            nextFailed = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_NEXT_STRING) == 0)
        {
            attr++;

            postNext = *attr;

            attr++;
        }
        else if (strcmp(*attr, UDISP_STRING) == 0)
        {
            attr++;

            dispUser = *attr;

            attr++;
        }
        else if (strcmp(*attr, IDISP_STRING) == 0)
        {
            attr++;

            dispISUP = *attr;

            attr++;
        }
        else if (strcmp(*attr, SDISP_STRING) == 0)
        {
            attr++;

            dispSCCP = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_ACCEPT_STRING) == 0)
        {
            attr++;

            preAccept = *attr;

            attr++;
        }
        else if (strcmp(*attr, ON_ACCEPT_STRING) == 0)
        {
            attr++;

            onAccept = *attr;

            attr++;
        }
        else if (strcmp(*attr, PRE_TERM_STRING) == 0)
        {
            attr++;

            preTerm = *attr;

            attr++;
        }
        else if (strcmp(*attr, POST_TERM_STRING) == 0)
        {
            attr++;

            postTerm = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    thisTrans.callbacks =
              ITS_ConstructObject(itsENGINE_TransportCallbacksClass,
                                  application, libName, realSS7,
                                  htype, (blocking ? DISP_BLOCKING
                                                   : DISP_NON_BLOCKING),
                                  preInit, postInit,
                                  preNext, nextFailed, postNext,
                                  dispUser, dispISUP, dispSCCP,
                                  preAccept, onAccept,
                                  preTerm, postTerm, atype);
    ITS_C_ASSERT(thisTrans.callbacks != NULL);
}

static ITS_BOOLEAN      inRoute = ITS_FALSE;
static ROUTE_MatchInfo  rinfo;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      start recording route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartRoute(const char **attr)
{
    memset(&rinfo, 0, sizeof(ROUTE_MatchInfo));
    rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ROUTE_TYPE_LOCAL_STRING) == 0)
            {
                rinfo.basic.type = LOCAL_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_REMOTE_STRING) == 0)
            {
                rinfo.basic.type = REMOTE_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_CONCERNED_STRING) == 0)
            {
                rinfo.basic.type = CONCERNED_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_DUPLICATE_STRING) == 0)
            {
                rinfo.basic.type = DUPLICATED_ROUTE;
            }
            else if (strcmp(*attr, ROUTE_TYPE_ROUTING_KEY_STRING) == 0)
            {
                rinfo.basic.type = ROUTING_KEY_ROUTE;
            }

            attr++;
        }
        else if (strcmp(*attr, STYLE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, ROUTE_STYLE_DPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_NI;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_NI;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_SSN;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_SIO_CIC;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
            }
            else if (strcmp(*attr, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
            {
                rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;
            }

            attr++;
        }
        else if (strcmp(*attr, PRIORITY_STRING) == 0)
        {
            attr++;

            rinfo.priority = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINKSET_SET_STRING) == 0)
        {
            attr++;

            rinfo.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                rinfo.basic.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleRoute(const char *el, const char **attr)
{
    ITS_C_ASSERT(inRoute);

    if (strcmp(el, ROUTING_KEY_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.rkey = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, DEST_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.dpc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, ORIG_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.opc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.opc = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, SIO_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.sio = (ITS_OCTET)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, ROUTE_MASK_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.mask = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, SSN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.ssn = (ITS_OCTET)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_SSN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, CIC_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.cic = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, RANGE_BEGIN_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.range.begin = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, RANGE_END_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                rinfo.basic.criteria.range.end = (ITS_USHORT)RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      stop recording route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndRoute()
{
    ITS_Object ret;

    /* NOTE: rinfo.sls is irrelevent (always zero) */
    switch (rinfo.basic.style)
    {
    case ROUTE_DPC_NI:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_NI:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_SSN_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_CIC_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_SSN:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.ssn,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_SIO_CIC:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.cic,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_SSN_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_CIC_RANGE:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.range.begin,
                                  rinfo.basic.criteria.range.end,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    case ROUTE_DPC_OPC_SIO_SSN:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.ssn,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        /* for concerned routes */
        ENGINE_RT_INFO(ret).basic.criteria.cic = rinfo.basic.criteria.cic;
        break;

    case ROUTE_DPC_OPC_SIO_CIC:
        ret = ITS_ConstructObject(itsENGINE_RouteClass, application,
                                  rinfo.basic.mask,
                                  rinfo.basic.dpc,
                                  rinfo.basic.type, rinfo.basic.style,
                                  rinfo.basic.family,
                                  rinfo.basic.criteria.opc,
                                  rinfo.basic.criteria.sio,
                                  rinfo.basic.criteria.cic,
                                  rinfo.linkSet,
                                  ITS_SS7_DEFAULT_LINK_CODE,
                                  rinfo.priority,
                                  rinfo.sls,
                                  rinfo.rkey);
        break;

    default:
        ITS_C_ASSERT(ITS_FALSE);
    }
}

/*
 * for link set
 */
static ENGINE_LinkSetPart linkSet;
static ITS_BOOLEAN haveAPC, haveLPC, haveNI;
static ITS_BOOLEAN inLinkSet = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
StartLinkSet(const char *el, const char **attr)
{
    ITS_BOOLEAN haveID = ITS_FALSE;

    haveAPC = ITS_FALSE;
    haveLPC = ITS_FALSE;
    haveNI = ITS_FALSE;

    memset(&linkSet, 0, sizeof(ENGINE_LinkSetPart));

    while (*attr)
    {
        if (strcmp(*attr, ID_STRING) == 0)
        {
            attr++;

            linkSet.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveID = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_NUM_TO_START_STRING) == 0)
        {
            attr++;

            linkSet.numToStart = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINKSET_ADJ_STP_STRING) == 0)
        {
            attr++;

            linkSet.adjacentSTP = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_IS_CLINK_STRING) == 0)
        {
            attr++;

            linkSet.isC = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINKSET_IS_5BIT_STRING) == 0)
        {
            attr++;

            linkSet.is5Bit = strstr(*attr, "yes") != NULL ||
                                    strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                linkSet.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                linkSet.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                linkSet.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                linkSet.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(haveID);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleLinkSet(const char *el, const char **attr)
{
    if (strcmp(el, ADJ_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.adjacent = RESFILE_ParseNum(*attr);
                haveAPC = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, NI_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.ni = (ITS_OCTET)RESFILE_ParseNum(*attr);
                haveNI = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else if (strcmp(el, LOCAL_POINT_CODE_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                linkSet.lpc = RESFILE_ParseNum(*attr);
                haveLPC = ITS_TRUE;

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record linkset info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
EndLinkSet()
{
    ITS_Object ret;

    ITS_C_ASSERT(haveAPC && haveLPC && haveNI);

    ret = ITS_ConstructObject(itsENGINE_LinkSetClass, application,
                              linkSet.adjacent, linkSet.lpc,
                              linkSet.linkSet,
                              linkSet.ni, linkSet.numToStart,
                              linkSet.adjacentSTP, linkSet.isC,
                              linkSet.is5Bit, linkSet.family);

    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleLink(const char *el, const char **attr)
{
    ENGINE_LinkPart link;
    ITS_BOOLEAN haveSet = ITS_FALSE, haveCode = ITS_FALSE,
                havePri = ITS_FALSE;
    ITS_Object ret;
    ITS_Object *list;

    ITS_C_ASSERT(inTransport || curLayer != NULL);
    if (curLayer == NULL)
    {
        list = &thisTrans.links;
    }
    else
    {
        list = &ENGINE_ISS7_LINKS(curLayer);
    }

    memset(&link, 0, sizeof(ENGINE_LinkPart));

    link.initActive = ITS_TRUE;
    link.termFixed = ITS_TRUE;
    link.linkFixed = ITS_TRUE;

    while (*attr)
    {
        if (strcmp(*attr, LINKSET_SET_STRING) == 0)
        {
            attr++;

            link.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveSet = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, ID_STRING) == 0)
        {
            attr++;

            link.linkCode = (ITS_OCTET)RESFILE_ParseNum(*attr);
            haveCode = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, PRIORITY_STRING) == 0)
        {
            attr++;

            link.linkPri = (ITS_OCTET)RESFILE_ParseNum(*attr);
            havePri = ITS_TRUE;

            attr++;
        }
        else if (strcmp(*attr, LINK_INIT_ACTIVE_STRING) == 0)
        {
            attr++;

            link.initActive = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_TERMINAL_FIXED_STRING) == 0)
        {
            attr++;

            link.termFixed = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_FIXED_STRING) == 0)
        {
            attr++;

            link.linkFixed = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_TERMINAL_STRING) == 0)
        {
            attr++;

            link.terminal = (ITS_USHORT)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINK_DATA_LINK_STRING) == 0)
        {
            attr++;

            link.circuit = (ITS_USHORT)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, LINK_SAAL_LINK_STRING) == 0)
        {
            attr++;

            link.isSAAL = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, LINK_LOCAL_STRING) == 0)
        {
            attr++;

            link.isLocal = strstr(*attr, "yes") != NULL ||
                                strstr(*attr, "YES") != NULL;

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                link.family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                link.family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                link.family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                link.family = FAMILY_JAPAN;
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ITS_C_ASSERT(haveSet && haveCode && havePri);

    ret = ITS_ConstructObject(itsENGINE_LinkClass, list,
                              link.linkSet, link.linkCode, link.linkPri,
                              link.initActive, link.termFixed, link.linkFixed,
                              link.terminal, link.circuit,
                              link.isSAAL, link.isLocal, link.family);
    ITS_C_ASSERT(ret != NULL);
}

static ITS_Object curDest = NULL;
static ITS_Object curISUPAttr = NULL;
static ITS_Object curGroup = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record destination info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleDestination(const char *el, const char **attr)
{
    ITS_UINT pc;
    ITS_OCTET ni;
    ITS_INT mtp3, sccp, tcap, tup, dup;
    SS7_Family family;
    const char *isup = NULL;
    ITS_Object ret;

    pc = 0;
    ni = 0;
    family = FAMILY_ANSI;
    mtp3 = ITS_THIRD_GEN;
    isup = NULL;
    sccp = ITS_THIRD_GEN;
    tcap = ITS_THIRD_GEN;
    tup = ITS_THIRD_GEN;
    dup = ITS_THIRD_GEN;

    while (*attr)
    {
        if (strcmp(*attr, PC_STRING) == 0)
        {
            attr++;

            pc = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, FAMILY_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, FAMILY_ANSI_STRING) == 0)
            {
                family = FAMILY_ANSI;
            }
            else if (strcmp(*attr, FAMILY_CCITT_STRING) == 0)
            {
                family = FAMILY_ITU;
            }
            else if (strcmp(*attr, FAMILY_CHINA_STRING) == 0)
            {
                family = FAMILY_CHINA;
            }
            else if (strcmp(*attr, FAMILY_JAPAN_STRING) == 0)
            {
                family = FAMILY_JAPAN;
            }

            attr++;
        }
        else if (strcmp(*attr, ENI_STRING) == 0)
        {
            attr++;

            ni = (ITS_OCTET)RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, DI_MTP3_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                mtp3 = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                mtp3 = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_ISUP_VAR_STRING) == 0)
        {
            attr++;

            isup = *attr;

            attr++;
        }
        else if (strcmp(*attr, DI_SCCP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                sccp = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                sccp = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_TCAP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                tcap = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                tcap = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_TUP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                tup = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                tup = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else if (strcmp(*attr, DI_DUP_VAR_STRING) == 0)
        {
            attr++;

            if (family == FAMILY_ANSI)
            {
                dup = GetANSIVariant(*attr);
            }
            else if (family == FAMILY_ITU)
            {
                dup = GetCCITTVariant(*attr);
            }

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_DestClass, application,
                              pc, ni, family,
                              mtp3, isup, sccp, tcap, tup, dup);
    ITS_C_ASSERT(ret != NULL);

    curDest = ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record route info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleISUPTimer(const char *el, const char **attr)
{
    const char *id = NULL, *value = NULL, *handler = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curDest != NULL);
    ITS_C_ASSERT(curISUPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            id = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else if (strcmp(*attr, HANDLED_BY_STRING) == 0)
        {
            attr++;

            handler = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ISUPTimerClass,
                              curISUPAttr,
                              id, value, handler);
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record circuit group info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCircuitGroup(const char *el, const char **attr)
{
    const char *huntRule = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curDest != NULL);
    ITS_C_ASSERT(curISUPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, HUNT_RULE_STRING) == 0)
        {
            attr++;

            huntRule = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_CircuitGroupClass,
                              curISUPAttr,
                              huntRule);
    ITS_C_ASSERT(ret != NULL);

    curGroup = ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record CIC info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleCICs(const char *el, const char **attr)
{
    ITS_Object ret;
    ITS_UINT start = 0, count = 1;

    ITS_C_ASSERT(curDest != NULL);
    ITS_C_ASSERT(curISUPAttr != NULL);
    ITS_C_ASSERT(curGroup != NULL);

    while (*attr)
    {
        if (strcmp(*attr, START_STRING) == 0)
        {
            attr++;

            start = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            count = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_CICsClass,
                              curGroup,
                              start, count);
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record ISUP attributes info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleISUPAttr(const char *el, const char **attr)
{
    ITS_UINT lpc = 0;
    ITS_UINT sio = 0;
    const char *xchangeType = NULL;
    const char *segmentationSupported = NULL;
    const char *classRec = NULL;
    const char *libName = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curDest != NULL);

    while (*attr)
    {
        if (strcmp(*attr, LPC_STRING) == 0)
        {
            attr++;

            lpc = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, CLASS_REC_STRING) == 0)
        {
            attr++;

            classRec = *attr;

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, SIO_STRING) == 0)
        {
            attr++;

            sio = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, ISUP_XCHANGE_TYPE_STR) == 0)
        {
            attr++;

            xchangeType = *attr;

            attr++;
        }
        else if (strcmp(*attr, ISUP_SEG_SUPPORT_STR) == 0)
        {
            attr++;

            segmentationSupported = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ISUPAttrClass,
                              application, curDest,
                              lpc, classRec, libName, sio,
                              xchangeType, segmentationSupported);
    curISUPAttr = ret;
    ITS_C_ASSERT(ret != NULL);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      handle SIP timer info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleSIPTimer(const char *el, const char **attr)
{
    const char *id = NULL, *value = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(curSIPAttr != NULL);

    while (*attr)
    {
        if (strcmp(*attr, NAME_STRING) == 0)
        {
            attr++;

            id = *attr;

            attr++;
        }
        else if (strcmp(*attr, VALUE_STRING) == 0)
        {
            attr++;

            value = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_SIPTimerClass,
                              curSIPAttr,
                              id, value);
    ITS_C_ASSERT(ret != NULL);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record SIP attributes info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleSIPAttr(const char *el, const char **attr)
{
    ITS_USHORT UDPPortNo = 0, TCPPortNo = 0;
    const char *ipAddr = NULL;
    ITS_Object ret;

    while (*attr)
    {
        if (strcmp(*attr, SIP_UDPPORTNO_STRING) == 0)
        {
            attr++;

            UDPPortNo = RESFILE_ParseNum(*attr);

            attr++;
        }
        if (strcmp(*attr, SIP_TCPPORTNO_STRING) == 0)
        {
            attr++;

            TCPPortNo = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, SIP_IPADDR_STRING) == 0)
        {
            attr++;

            ipAddr = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
    ret = ITS_ConstructObject(itsENGINE_SIPAttrClass, application,
                              UDPPortNo, TCPPortNo, ipAddr);
    curSIPAttr = ret;
    ITS_C_ASSERT(ret != NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record work item info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleWorkItem(const char *el, const char **attr)
{
    const char *libName = NULL, *userDisp = NULL;
    ITS_BOOLEAN persist = ITS_TRUE;
    ITS_Object tmp;
    ITS_UINT count = 1;

    ITS_C_ASSERT(inItemPool);
    ITS_C_ASSERT(ENGINE_TP_TRANSPORTS(curPool) != NULL);

    tmp = ENGINE_TP_TRANSPORTS(curPool);

    if (strcmp(el, NUM_WORKERS_STRING) == 0)
    {
        while (*attr)
        {
            if (strcmp(*attr, VALUE_STRING) == 0)
            {
                attr++;

                ENGINE_TR_NUM_ASSOCIATES(tmp) = RESFILE_ParseNum(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        return;
    }

    /* has to be a work item record or we're hosed. */
    if (strcmp(el, WORK_ITEM_STRING) != 0)
    {
        return;
    }

    while (*attr)
    {
        if (strcmp(*attr, TYPE_STRING) == 0)
        {
            attr++;

            if (strcmp(*attr, NREPEAT_STRING) == 0)
            {
                persist = ITS_FALSE;
            }

            attr++;
        }
        else if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, WDISP_STRING) == 0)
        {
            attr++;

            userDisp = *attr;

            attr++;
        }
        else if (strcmp(*attr, COUNT_STRING) == 0)
        {
            attr++;

            count = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    tmp = ITS_ConstructObject(itsENGINE_WorkItemClass, tmp,
                              persist, count, libName, userDisp);
    ITS_C_ASSERT(tmp != NULL);
}

static ITS_BOOLEAN  inManagement = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record stack management info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleManagement(const char **attr)
{
    const char *libName = NULL;
    const char *mtp3A = NULL, *isupA = NULL, *sccpA = NULL, *gttA = NULL;
    const char *mtp3I = NULL, *isupI = NULL, *sccpI = NULL, *gttI = NULL;
    const char *rcA = NULL, *rcI = NULL;
    ITS_Object ret;

    ITS_C_ASSERT(application != NULL);
    ITS_C_ASSERT(inManagement);

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_MTP3_STRING) == 0)
        {
            attr++;

            mtp3A = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_ISUP_STRING) == 0)
        {
            attr++;

            isupA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_SCCP_STRING) == 0)
        {
            attr++;

            sccpA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_GTT_STRING) == 0)
        {
            attr++;

            gttA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_A_RC_STRING) == 0)
        {
            attr++;

            rcA = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_MTP3_STRING) == 0)
        {
            attr++;

            mtp3I = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_ISUP_STRING) == 0)
        {
            attr++;

            isupI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_SCCP_STRING) == 0)
        {
            attr++;

            sccpI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_GTT_STRING) == 0)
        {
            attr++;

            gttI = *attr;

            attr++;
        }
        else if (strcmp(*attr, MGMT_I_RC_STRING) == 0)
        {
            attr++;

            rcI = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_SS7StackMgmtClass,
                              application, libName,
                              mtp3A, mtp3I, isupA, isupI,
                              sccpA, sccpI, gttA, gttI,
                              rcA, rcI);

    ITS_C_ASSERT(ret != NULL);
}

static ITS_BOOLEAN  inStacks = ITS_FALSE;
static ITS_BOOLEAN  inIntelliNet = ITS_FALSE;
static ITS_BOOLEAN  codecStacks = ITS_FALSE;
static ITS_BOOLEAN  inLayer = ITS_FALSE;
static ITS_BOOLEAN  sigStacks = ITS_FALSE;
static ITS_BOOLEAN  inVendors = ITS_FALSE;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record stack info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1788
 *
 ****************************************************************************/
static void
HandleStack(const char *el, const char **attr)
{
    printf("\nHandleStack Func Called :: %s\n",__FILE__);
    const char *name = NULL;
    int variant = ITS_LATEST_GEN;
    char* variant_name = NULL;
    int numThreads = 0;

    ITS_C_ASSERT(application != NULL);

    if (strcmp(el, ITU_MTP2_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);
        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_MTP3_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_ISUP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_SCCP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ITU_TCAP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetCCITTVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el,ANSI_MTP2_STRING) == 0)
    {
        printf("\n ANSI_MTP2_STRING inLayer %d",inLayer);
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);
        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_MTP3_STRING) == 0)
    {
        printf("\n ANSI_MTP3_STRING inLayer %d",inLayer);
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_ISUP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_SCCP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, ANSI_TCAP_STRING) == 0)
    {
        ITS_C_ASSERT(inIntelliNet);
        ITS_C_ASSERT(!inLayer);

        name = el;
        while (*attr)
        {
            if (strcmp(*attr, VARIANT_STRING) == 0)
            {
                attr++;

                variant_name = *attr;
                variant = GetANSIVariant(*attr);

                attr++;
            }
            else if (strcmp(*attr, NUM_THREADS_STRING) == 0)
            {
                attr++;

                numThreads = atoi(*attr);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }

        curLayer = ITS_ConstructObject(itsENGINE_ISS7StackClass, application,
                                       name, variant, numThreads);

        if (variant_name)
        {
            ENGINE_ISS7_VARIANT_NAME(curLayer) = strdup(variant_name);
        }

        inLayer = ITS_TRUE;
    }
    else if (strcmp(el, TIMERS_STRING) == 0)
    {
        ITS_C_ASSERT(inLayer);
        ITS_C_ASSERT(curLayer != NULL);

        while (*attr)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=%s", attr[0], attr[1]);

            ENGINE_ISS7_NUM_TIMERS(curLayer)++;

            ENGINE_ISS7_TIMERS(curLayer) = (char **)
                                    realloc(ENGINE_ISS7_TIMERS(curLayer),
                                            ENGINE_ISS7_NUM_TIMERS(curLayer) *
                                                sizeof(char *));
            ITS_C_ASSERT(ENGINE_ISS7_TIMERS(curLayer) != NULL);

            ENGINE_ISS7_TIMERS(curLayer)
                [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1] =
                    malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_ISS7_TIMERS(curLayer)
                            [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1] != NULL);

            strcpy(ENGINE_ISS7_TIMERS(curLayer)
                    [ENGINE_ISS7_NUM_TIMERS(curLayer) - 1],
                   buf);

            attr += 2;
        }
    }
    else if (strcmp(el, BEHAVIOR_STRING) == 0)
    {
        ITS_C_ASSERT(inLayer);
        ITS_C_ASSERT(curLayer != NULL);

        while (*attr)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=%s", attr[0], attr[1]);

            ENGINE_ISS7_NUM_MODIFIERS(curLayer)++;

            ENGINE_ISS7_MODIFIERS(curLayer) = (char **)
                                    realloc(ENGINE_ISS7_MODIFIERS(curLayer),
                                            ENGINE_ISS7_NUM_MODIFIERS(curLayer) *
                                                sizeof(char *));
            ITS_C_ASSERT(ENGINE_ISS7_MODIFIERS(curLayer) != NULL);

            ENGINE_ISS7_MODIFIERS(curLayer)
                [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1] =
                    malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_ISS7_MODIFIERS(curLayer)
                            [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1] != NULL);

            strcpy(ENGINE_ISS7_MODIFIERS(curLayer)
                    [ENGINE_ISS7_NUM_MODIFIERS(curLayer) - 1],
                   buf);

            attr += 2;
        }
    }
}

static void
HandleCodecStack(const char *el, const char **attr)
{
    const char *name = NULL;

    ITS_C_ASSERT(application != NULL);

    if (strcmp(el, BSSAP_STACK_STRING) == 0)
    {
        ITS_C_ASSERT(codecStacks);

        name = el;

        curCodecLayer = ITS_ConstructObject(itsENGINE_CODECStackClass,
                                          application, name);
        /*inLayer = ITS_TRUE; */
    }
    else if (strcmp(el, TIMERS_STRING) == 0)
    {
        ITS_C_ASSERT(codecStacks);
        ITS_C_ASSERT(curCodecLayer != NULL);

        while (*attr)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=%s", attr[0], attr[1]);

            ENGINE_CODEC_NUM_TIMERS(curCodecLayer)++;

            ENGINE_CODEC_TIMERS(curCodecLayer) = (char **)
                                    realloc(ENGINE_CODEC_TIMERS(curCodecLayer),
                                        ENGINE_CODEC_NUM_TIMERS(curCodecLayer) *
                                                sizeof(char *));
            ITS_C_ASSERT(ENGINE_CODEC_TIMERS(curCodecLayer) != NULL);

            ENGINE_CODEC_TIMERS(curCodecLayer)
                [ENGINE_CODEC_NUM_TIMERS(curCodecLayer) - 1] =
                    malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_CODEC_TIMERS(curCodecLayer)
                            [ENGINE_CODEC_NUM_TIMERS(curCodecLayer) - 1] != NULL);

            strcpy(ENGINE_CODEC_TIMERS(curCodecLayer)
                    [ENGINE_CODEC_NUM_TIMERS(curCodecLayer) - 1],
                   buf);

            attr += 2;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      record sigtran stack info
 *
 *  Input Parameters:
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleSigtranStack(const char *el, const char **attr)
{
    const char *name = NULL;
    ENGINE_M2UA_IIDPart iidMap;
    ITS_BOOLEAN haveLS = ITS_FALSE, haveLC = ITS_FALSE; 
    ITS_BOOLEAN haveIID = ITS_FALSE, haveAssoName = ITS_FALSE;
    ITS_Object ret;
    ITS_Object *list;

    ITS_C_ASSERT(application != NULL);

    if (strcmp(el, SCTP_STACK_STRING) == 0)
    {
        ITS_C_ASSERT(sigStacks);

        name = el;

        curSigLayer = ITS_ConstructObject(itsENGINE_SIGTRANStackClass,
                                          application, name);
        /*inLayer = ITS_TRUE; */
    }
    else if (strcmp(el, UAL_STACK_STRING) == 0)
    {
        ITS_C_ASSERT(sigStacks);

        name = el;

        curSigLayer = ITS_ConstructObject(itsENGINE_SIGTRANStackClass,
                                          application, name);

        /*inLayer = ITS_TRUE; */
    }
    else if (strcmp(el, M3UA_STACK_STRING) == 0)
    {
        ITS_C_ASSERT(sigStacks);

        name = el;

        curSigLayer = ITS_ConstructObject(itsENGINE_SIGTRANStackClass,
                                          application, name);
        /*inLayer = ITS_TRUE; */
    }
    else if (strcmp(el, M2UA_STACK_STRING) == 0)
    {
        ITS_C_ASSERT(sigStacks);

        name = el;

        curSigLayer = ITS_ConstructObject(itsENGINE_SIGTRANStackClass,
                                          application, name);
        /*inLayer = ITS_TRUE; */
    }
    else if (strcmp(el, M2UA_IID_MAP_STRING) == 0)
    {
    	ITS_C_ASSERT(sigStacks);

        name = el;

    	ITS_C_ASSERT(sigStacks || curSigLayer != NULL);

        list = &ENGINE_SIGTRAN_IID(curSigLayer);
    	
    	memset(&iidMap, 0, sizeof(ENGINE_M2UA_IIDPart));

    	while (*attr)
    	{
    		if (strcmp(*attr, M2UA_LINK_SET_STRING) == 0)
            {
                attr++;
                iidMap.linkSet = (ITS_OCTET)RESFILE_ParseNum(*attr);
                attr++;
                haveLS = ITS_TRUE;
            }
                                                                                
            else if (strcmp(*attr, M2UA_LINK_CODE_STRING) == 0)
            {
                attr++;
                iidMap.linkCode = (ITS_OCTET)RESFILE_ParseNum(*attr);
                attr++;
                haveLC = ITS_TRUE;
            }
                                                                                
            else if (strcmp(*attr, M2UA_IID_STRING) == 0)
            {
                attr++;
                iidMap.IID = *attr;
                attr++;
                haveIID = ITS_TRUE;
            }
                                                                                
            else if (strcmp(*attr, M2UA_ASSO_NAME_STRING) == 0)
            {
                attr++;
                iidMap.assoName = *attr;
                attr++;
                haveAssoName = ITS_TRUE;
            }
    		else 
    		{
    			attr +=2;
    		}
    	} /* end of while*/

    	ITS_C_ASSERT(haveLS && haveLC && haveIID && haveAssoName);
                                                                                
        ret = ITS_ConstructObject(itsENGINE_M2UA_IIDClass,
                                    list, 
                                    iidMap.linkSet,
                                    iidMap.linkCode,
                                    iidMap.IID,
                                    iidMap.assoName);
        ITS_C_ASSERT(ret != NULL);

    } /* end of if*/
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handles the vendor section in XML for vendor traces
 *
 *  Input Parameters:
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleVendor(const char *el, const char **attr)
{
    const char *name = NULL;

    ITS_C_ASSERT(application != NULL);

    if (strcmp(el, ADAX_MTP2_STRING) == 0 || strcmp(el, NMS_MTP2_STRING) == 0)
    {
        ITS_C_ASSERT(inVendors);
        ITS_C_ASSERT(!inLayer);

        strcpy(vendorName, el);
        inLayer = ITS_TRUE;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Build a parser extension record.
 *
 *  Input Parameters:
 *      el - the element
 *      attr - the element's attributes
 *
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1763
 *
 ****************************************************************************/
static void
HandleParserExtension(const char **attr)
{
    const char *libName = NULL, *elemName = NULL;
    const char *start = NULL, *stop = NULL, *xlate = NULL, *diff = NULL, *commit = NULL;
    ITS_Object ret;

    while (*attr)
    {
        if (strcmp(*attr, LIBRARY_STRING) == 0)
        {
            attr++;

            libName = *attr;

            attr++;
        }
        else if (strcmp(*attr, ELEM_NAME_STRING) == 0)
        {
            attr++;

            elemName = *attr;

            attr++;
        }
        else if (strcmp(*attr, START_FUNC_STRING) == 0)
        {
            attr++;

            start = *attr;

            attr++;
        }
        else if (strcmp(*attr, STOP_FUNC_STRING) == 0)
        {
            attr++;

            stop = *attr;

            attr++;
        }
        else if (strcmp(*attr, XLATE_FUNC_STRING) == 0)
        {
            attr++;

            xlate = *attr;

            attr++;
        }
        else if (strcmp(*attr, DIFF_FUNC_STRING) == 0)
        {
            attr++;

            diff = *attr;

            attr++;
        }
        else if (strcmp(*attr, COMMIT_FUNC_STRING) == 0)
        {
            attr++;

            commit = *attr;

            attr++;
        }
        else
        {
            attr += 2;
        }
    }

    ret = ITS_ConstructObject(itsENGINE_ParserExtensionClass,
                              application, libName, elemName,
                              start, stop, xlate, diff, commit);

    ITS_C_ASSERT(ret != NULL);
}

static ITS_BOOLEAN inExtension = ITS_FALSE;
static ENGINE_ParserExtension curExt = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function for parser unknown symbols
 *
 *  Input Parameters:
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
HandleExtensionStart(const char *el, const char **attr)
{
    if (inExtension)
    {
        ITS_C_ASSERT(curExt != NULL);
    }
    else
    {
        ITS_Object tmp;

        for (tmp = ENGINE_APP_PARSER_EXTENSIONS(application);
             tmp != NULL;
             tmp = ENGINE_PE_NEXT(tmp))
        {
            if (strcmp(ENGINE_PE_ELEMENT_NAME(tmp), el) == 0)
            {
                curExt = (ENGINE_ParserExtension)tmp;
                inExtension = ITS_TRUE;

                break;
            }
        }

        if (tmp == NULL)
        {
            return;
        }
    }

    if (ENGINE_PE_START_FUNC(curExt))
    {
        const char** temp = attr;
        int count = 0;
        ENGINE_PE_ELEMENT_DATA_COUNT(curExt) = 0;

        while (*temp)
        {
            char buf[ITS_PATH_MAX];

            sprintf(buf, "%s=\"%s\"", temp[0], temp[1]);
            count++;
            ENGINE_PE_ELEMENT_DATA(curExt) = (char **)
                                    realloc(ENGINE_PE_ELEMENT_DATA(curExt),
                                            count * sizeof(char *));
            ITS_C_ASSERT(ENGINE_PE_ELEMENT_DATA(curExt) != NULL);

            ENGINE_PE_ELEMENT_DATA(curExt) [count-1] = malloc(strlen(buf) + 1);
            ITS_C_ASSERT(ENGINE_PE_ELEMENT_DATA(curExt)[count-1] != NULL);

            strcpy(ENGINE_PE_ELEMENT_DATA(curExt)[count-1], buf);

            temp += 2;
        }

        ENGINE_PE_ELEMENT_DATA_COUNT(curExt) = count;
        ENGINE_PE_START_FUNC(curExt)(curExt, el, attr);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element stop function for parser unknown symbols
 *
 *  Input Parameters:
 *      el - the element
 *
 ****************************************************************************/
static void
HandleExtensionStop(const char *el)
{
    if (!inExtension)
    {
        return;
    }

    ITS_C_ASSERT(curExt != NULL);

    if (ENGINE_PE_STOP_FUNC(curExt))
    {
        ENGINE_PE_STOP_FUNC(curExt)(curExt, el);
    }

    if (strcmp(ENGINE_PE_ELEMENT_NAME(curExt), el) == 0)
    {
        curExt = NULL;
        inExtension = ITS_FALSE;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element start function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 ****************************************************************************/
static void
ElementStart(void *data, const char *el, const char **attr)
{
    if (strcmp(el, APPL_STRING) == 0)
    {
        HandleApplication(attr);
    }
    else if (strcmp(el, OPTIONS_STRING) == 0)
    {
        HandleOption(attr);
    }
    else if (strcmp(el, FAULT_TOLERANCE_STRING) == 0)
    {
        inFaultTolerance = ITS_TRUE;
        StartFaultTolerance(attr);
    }
    else if (strcmp(el, FTM_PRE_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmPreExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, FTM_LOOP_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmLoopExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, FTM_POST_EXEC_LOGIC_PROC_STRING) == 0)
    {
        HandleFtmPostExecuteLogicProcedure(attr);
    }
    else if (strcmp(el, MB_CHANGE_ALL_FT_GRPS_CB_STRING) == 0)
    {
        HandleMembershipChangeAllFtGroupsCallback(attr);
    }
    else if (strcmp(el, EVT_FR_ALL_FT_GRP_MBS_CB_STRING) == 0)
    {
        HandleEventFromAllFtGroupMembersCallback(attr);
    }
    else if (strcmp(el, FT_GRP_STRING) == 0)
    {
        inFtGroup = ITS_TRUE;
        StartFtGroup(attr);
    }
    else if (strcmp(el, DSM_CFG_STRING) == 0)
    {
        HandleDsmConfig(attr);
    }
    else if (strcmp(el, FT_GRP_MB_STRING) == 0)
    {
        HandleFtGroupMember(attr);
    }
    else if (strcmp(el, MASTER_FT_GRP_MB_STRING) == 0)
    {
        HandleMasterFtGroupMember(attr);
    }
    else if (strcmp(el, MB_CHANGE_CB_STRING) == 0)
    {
        HandleMembershipChangeCallback(attr);
    }
    else if (strcmp(el, EVT_FR_FT_GRP_MB_CB_STRING) == 0)
    {
        HandleEventFromFtGroupMemberCallback(attr);
    }
    /**/
    else if (strcmp(el, WINDOWS_STRING) == 0)
    {
        inWindows = ITS_TRUE;
    }
    else if (strcmp(el, NET_HOME_STRING) == 0)
    {
        if (inWindows)
        {
            HandleWindows(attr);
        }
    }
    else if (strcmp(el, FEATURE_STRING) == 0)
    {
        inFeature = ITS_TRUE;
        StartFeature(attr);
    }
    else if (strcmp(el, FEAT_OPTION_STRING) == 0)
    {
        HandleFeatureOption(attr);
    }
    else if (strcmp(el, TK_TRACE_STRING) == 0)
    {
        tkTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, SIP_TRACE_STRING) == 0)
    {
        sipTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, APP_TRACE_STRING) == 0)
    {
        appTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, STACK_TRACE_STRING) == 0)
    {
        stackTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, SIGTRAN_TRACE_STRING) == 0)
    {
        sigtranTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, CODEC_TRACE_STRING) == 0)
    {
        codecTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, VENDOR_TRACE_STRING) == 0)
    {
        vendorTrace = ITS_TRUE;
        StartTrace(attr);
    }
    else if (strcmp(el, CRIT_STRING) == 0)
    {
        if (tkTrace  || sipTrace || appTrace || stackTrace 
                || codecTrace || sigtranTrace || vendorTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, ERR_STRING) == 0)
    {
        if (tkTrace || sipTrace || appTrace || stackTrace 
                || codecTrace || sigtranTrace || vendorTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, WARN_STRING) == 0)
    {
        if (tkTrace || sipTrace || appTrace || stackTrace 
               || codecTrace || sigtranTrace || vendorTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, DBG_STRING) == 0)
    {
        if (tkTrace || sipTrace || appTrace || stackTrace 
              || codecTrace || sigtranTrace || vendorTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, EVENT_STRING) == 0)
    {
        if (tkTrace || sipTrace || appTrace || stackTrace 
              || codecTrace || sigtranTrace || vendorTrace)
        {
            HandleTrace(el, attr);
        }
    }
    else if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        inWorkPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        inItemPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        inBorderPool = ITS_TRUE;
        StartPool(el, attr);
    }
    else if (strcmp(el, TRANSPORT_STRING) == 0)
    {
        inTransport = ITS_TRUE;
        StartTransport(attr);
    }
    else if (strcmp(el, CUSTOM_DISP_STRING) == 0)
    {
        HandleCustomDispatch(attr);
    }
    else if (strcmp(el, CALLBACK_STRING) == 0)
    {
        if (inTransport)
        {
            HandleCallbacks(attr);
        }
    }
    else if (strcmp(el, MODIFIER_STRING) == 0)
    {
        HandleModifier(attr);
    }
    else if (strcmp(el, ROUTE_STRING) == 0)
    {
        inRoute = ITS_TRUE;
        StartRoute(attr);
    }
    else if (strcmp(el, WORK_ITEM_STRING) == 0)
    {
        HandleWorkItem(el, attr);
    }
    else if (strcmp(el, NUM_WORKERS_STRING) == 0)
    {
        HandleWorkItem(el, attr);
    }
    else if (strcmp(el, STACKS_STRING) == 0)
    {
        inStacks = ITS_TRUE;
    }
    else if (strcmp(el, SIGTRAN_STACK_STRING) == 0)
    {
        sigStacks = ITS_TRUE;
    }
    else if (strcmp(el, MGMT_CBS_STRING) == 0)
    {
        inManagement = ITS_TRUE;
        HandleManagement(attr);
    }
    else if (strcmp(el, INTELLINET_STRING) == 0)
    {
        inIntelliNet = ITS_TRUE;
    }
     else if (strcmp(el, CODEC_STACK_STRING) == 0)
    {
        codecStacks = ITS_TRUE;
    }
    else if (strcmp(el, VENDORS_STRING) == 0)
    {
        inVendors = ITS_TRUE;
    }
    else if (strcmp(el, PEXT_STRING) == 0)
    {
        HandleParserExtension(attr);
    }
    else if (strcmp(el, LINK_SET_STRING) == 0)
    {
        inLinkSet = ITS_TRUE;
        StartLinkSet(el, attr);
    }
    else if (strcmp(el, LINK_STRING) == 0)
    {
        HandleLink(el, attr);
    }
    else if (strcmp(el, DEST_STRING) == 0)
    {
        HandleDestination(el, attr);
    }
    else if (strcmp(el, ISUP_ATTR_STRING) == 0)
    {
        HandleISUPAttr(el, attr);
    }
    else if (strcmp(el, CIRC_GRP_STRING) == 0)
    {
        HandleCircuitGroup(el, attr);
    }
    else if (strcmp(el, CIRC_CODE_STRING) == 0)
    {
        HandleCICs(el, attr);
    }
    else if (strcmp(el, TIMER_STRING) == 0)
    {
        HandleISUPTimer(el, attr);
    }
    else if (inRoute)
    {
        HandleRoute(el, attr);
    }
    else if (inTransport)
    {
        HandleTransport(el, attr);
    }
    else if (inStacks && inIntelliNet)
    {
        HandleStack(el, attr);
    }
    else if (inStacks && codecStacks)
    {
        HandleCodecStack(el, attr);
    }
    else if (sigStacks)
    {
        HandleSigtranStack(el, attr);
    }
    else if (inStacks && inVendors)
    {
        HandleVendor(el, attr);
    }
    else if (inLinkSet)
    {
        HandleLinkSet(el, attr);
    }
    else if (strcmp(el, SIP_ATTR_STRING) == 0)
    {
        HandleSIPAttr(el, attr);
    }
    else if (strcmp(el, SIP_TIMERS_STRING) == 0)
    {
        HandleSIPTimer(el, attr);
    }
    else
    {
        HandleExtensionStart(el, attr);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Xml parser element end function
 *
 *  Input Parameters:
 *      data - dunno
 *      el - the element
 *      attr - the element's attributes
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
static void
ElementEnd(void *data, const char *el)
{
    if (strcmp(el, FAULT_TOLERANCE_STRING) == 0)
    {
        EndFaultTolerance();
        inFaultTolerance = ITS_FALSE;
    }
    else if (strcmp(el, FT_GRP_ID_STRING) == 0)
    {
        EndFtGroup();
        inFtGroup = ITS_FALSE;
    }
    else if (strcmp(el, WINDOWS_STRING) == 0)
    {
        inWindows = ITS_FALSE;
    }
    else if (strcmp(el, FEATURE_STRING) == 0)
    {
        EndFeature();
        inFeature = ITS_FALSE;
    }
    else if (strcmp(el, TK_TRACE_STRING) == 0)
    {
        EndTrace();
        tkTrace = ITS_FALSE;
    }
    else if (strcmp(el, SIP_TRACE_STRING) == 0)
    {
        EndTrace();
        sipTrace = ITS_FALSE;
    }
    else if (strcmp(el, APP_TRACE_STRING) == 0)
    {
        EndTrace();
        appTrace = ITS_FALSE;
    }
    else if (strcmp(el, STACK_TRACE_STRING) == 0)
    {
        EndTrace();
        stackTrace = ITS_FALSE;
    }
    else if (strcmp(el, SIGTRAN_TRACE_STRING) == 0)
    {
        EndTrace();
        sigtranTrace = ITS_FALSE;
    }
    else if (strcmp(el, CODEC_TRACE_STRING) == 0)
    {
        EndTrace();
        codecTrace = ITS_FALSE;
    }
    else if (strcmp(el, VENDOR_TRACE_STRING) == 0)
    {
        EndTrace();
        vendorTrace = ITS_FALSE;
    }
    else if (strcmp(el, WORK_POOL_STRING) == 0)
    {
        EndPool(el);
        inWorkPool = ITS_FALSE;
    }
    else if (strcmp(el, ITEM_POOL_STRING) == 0)
    {
        EndPool(el);
        inItemPool = ITS_FALSE;
    }
    else if (strcmp(el, BORDER_POOL_STRING) == 0)
    {
        EndPool(el);
        inBorderPool = ITS_FALSE;
    }
    else if (strcmp(el, TRANSPORT_STRING) == 0)
    {
        EndTransport();
        inTransport = ITS_FALSE;
    }
    else if (strcmp(el, ROUTE_STRING) == 0)
    {
        EndRoute();
        inRoute = ITS_FALSE;
    }
    else if (strcmp(el, DEST_STRING) == 0)
    {
        curDest = NULL;
    }
    else if (strcmp(el, CIRC_GRP_STRING) == 0)
    {
        curGroup = NULL;
    }
    else if (strcmp(el, ISUP_ATTR_STRING) == 0)
    {
        curISUPAttr = NULL;
    }
    else if (strcmp(el, STACKS_STRING) == 0)
    {
        inStacks = ITS_FALSE;
    }
    else if (strcmp(el, SIGTRAN_STACK_STRING) == 0)
    {
        sigStacks = ITS_FALSE;
    }
    else if (strcmp(el, MGMT_CBS_STRING) == 0)
    {
        ITS_C_ASSERT(inStacks);
        inManagement = ITS_FALSE;
    }
    else if (strcmp(el, LINK_SET_STRING) == 0)
    {
        inLinkSet = ITS_FALSE;
        EndLinkSet();
    }
    else if (strcmp(el, INTELLINET_STRING) == 0)
    {
        inIntelliNet = ITS_FALSE;
    }
    else if (strcmp(el, CODEC_STACK_STRING) == 0)
    {
        codecStacks = ITS_FALSE;
    }
    else if (strcmp(el, VENDORS_STRING) == 0)
    {
        inVendors = ITS_FALSE;
    }
    else if (strcmp(el, ITU_MTP2_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_MTP3_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_ISUP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_SCCP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ITU_TCAP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_MTP3_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_ISUP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_SCCP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, ANSI_TCAP_STRING) == 0)
    {
        inLayer = ITS_FALSE;
        curLayer = NULL;
    }
    else if (strcmp(el, BSSAP_STACK_STRING) == 0)
    {
        /* inLayer = ITS_FALSE; */
        curCodecLayer = NULL;
    }
    else if (strcmp(el, SCTP_STACK_STRING) == 0)
    {
        /* inLayer = ITS_FALSE; */
        curSigLayer = NULL;
    }
    else if (strcmp(el, UAL_STACK_STRING) == 0)
    {
        /* inLayer = ITS_FALSE; */
        curSigLayer = NULL;
    }
    else if (strcmp(el, M3UA_STACK_STRING) == 0)
    {
        /*inLayer = ITS_FALSE; */
        curSigLayer = NULL;
    }
    else if (strcmp(el, M2UA_STACK_STRING) == 0)
    {
        /*inLayer = ITS_FALSE; */
        curSigLayer = NULL;
    }
    else if (strcmp(el, ADAX_MTP2_STRING) == 0 || strcmp(el, NMS_MTP2_STRING) == 0)
    {
        inLayer = ITS_FALSE;
    }
    else if (strcmp(el, SIP_ATTR_STRING) == 0)
    {
         curSIPAttr = NULL;
    }
    else
    {
        HandleExtensionStop(el);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process the command line and parse the XML configuration.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *      xmlData - buffer containing the XML config
 *      xmlSize - size of xmlData
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ENGINE_Initialize(int argc, const char **argv, char *xmlData, int xmlSize)
{
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    /* init the syntax tree classes */
    InitClasses();

    /* set some defaults */
    SERVICE_InternalName = ITS_StripPath(argv[0]);
    SERVICE_DisplayedName = ITS_StripPath(argv[0]);

    /* set the config file extension */
    APPL_SetConfigFileExtension(XML_EXT_STRING);

    /* get some info from the command line */
    SERVICE_ProcessCommandLine(argc, argv);

    /* parse the XML config. */
    parser = XML_ParserCreate(NULL);
    ITS_C_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, ElementStart, ElementEnd);

    /* open the ini */
#if !defined(NO_FILESYSTEM)
    xml = fopen(APPL_GetConfigFileName(), "r");
    ITS_C_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    ITS_C_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    ITS_C_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = malloc(size);
    ITS_C_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    ITS_C_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NUL */
    buf[size - 1] = 0;

    inParser = ITS_TRUE;
    if (xmlSize != 0)
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_FALSE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    else
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
#endif /* NO_FILESYSTEM */

    inParser = ITS_TRUE;
    if (xmlSize)
    {
        parseSuccessful = XML_Parse(parser, xmlData, xmlSize, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    inParser = ITS_FALSE;

    XML_ParserFree(parser);

#if !defined(NO_FILESYSTEM)
    /* clean up */
    if (buf)
    {
        free(buf);
    }
#endif

    /* reset for the resdb. */
    free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) = NULL;
    APPL_SetConfigFileExtension(INI_EXT_STRING);

    /* make sure we have an application */
    ITS_C_ASSERT(application != NULL);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Run the engine.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *
 *  Return Value:
 *      Returns the service exit code.
 *
 ****************************************************************************/
ITSDLLAPI int
ENGINE_Run(int argc, const char **argv)
{
    DRIVER_MainFunc libMain;
    int ret;

    /* make sure we have a config */
    ITS_C_REQUIRE(application != NULL);

    /* Hook up the DBC. */
    DBC_Commit = ENGINE_Commit;

    /* load the driver and go */
    if (ENGINE_APP_CPP_BINDING(application))
    {
        /* CPP binding? */
#if defined(DEBUG) || defined(_DEBUG)
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_CPP_DEBUG_STRING);
#else /* NDEBUG */
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_CPP_STRING);
#endif /* NDEBUG */
    }
    else
    {
        /* Nope.  C binding. */
#if defined(DEBUG) || defined(_DEBUG)
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_C_DEBUG_STRING);
#else /* NDEBUG */
        driver = (ENGINE_LibCache)ITS_ConstructObject(itsENGINE_LibCacheClass,
                                                      application,
                                                      DRIVER_C_STRING);
#endif /* NDEBUG */
    }

    ITS_C_ASSERT(driver != NULL);

    /* lookup main */
    libMain = (DRIVER_MainFunc)DLSYM_Resolve(ENGINE_LC_LIBRARY(driver),
                                             DRIVER_MAIN_STRING);
    if (libMain == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   DRIVER_MAIN_STRING, DLSYM_Error());
            fflush(stdout);
        }
    }

    ITS_C_ASSERT(libMain != NULL);

    ret = (libMain)(argc, argv);

    /* clean up after the engine. */
    ITS_DestructObject((ITS_Object)application);
    application = NULL;
    driver = NULL;

    TermClasses();

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Process the command line and parse the XML configuration, compare
 *      it with the current configuration and add/remove components as
 *      necessary.
 *
 *  Input Parameters:
 *      argc - arg count
 *      argv - arg vector
 *      xmlData - buffer containing the XML config
 *      xmlSize - size of xmlData
 *
 *  Notes:
 *      If difficulties are encountered either in parsing or setup, an
 *      assertion is raised.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
ENGINE_Diff(int argc, const char **argv,
            char *xmlData, int xmlSize)
{
    DRIVER_DiffFunc diffMain;
    FILE *xml;
    long size;
    char *buf;
    size_t count;
    int parseSuccessful, ret;

    buf = NULL;
    size = 0;

    /* make sure we're running and have a driver */
    ITS_C_ASSERT(application != NULL);
    ITS_C_ASSERT(driver != NULL);

    /* save current config */
    tmpApp = application;
    application = NULL;

    /* set the config file extension */
    APPL_SetConfigFileExtension(XML_EXT_STRING);

    /* get some info from the command line */
    SERVICE_ProcessCommandLine(argc, argv);

    /* parse the XML config. */
    parser = XML_ParserCreate(NULL);
    ITS_C_ASSERT(parser != NULL);

    /* set the token functions */
    XML_SetElementHandler(parser, ElementStart, ElementEnd);

    /* open the ini */
#if !defined(NO_FILESYSTEM)
    xml = fopen(APPL_GetConfigFileName(), "r");
    ITS_C_ASSERT(xml != NULL);

    /* go to the end */
    ret = fseek(xml, 0, SEEK_END);
    ITS_C_ASSERT(ret == 0);

    /* how big a buffer */
    size = ftell(xml);
    ITS_C_ASSERT(size >= 0);

    /* rewind */
    rewind(xml);

    /* add space for a trailing NUL */
    size++;

    /* get the buffer */
    buf = malloc(size);
    ITS_C_ASSERT(buf != NULL);

    /* read the file */
    count = fread(buf, sizeof(char), size - 1, xml);

    /* don't need the handle anymore */
    fclose(xml);

#if !defined(WIN32)
    /* this doesn't work due to that stupid everpresent CR/LF issue */
    ITS_C_ASSERT(count == (size_t)(size - 1));
#endif

    /* add NUL */
    buf[size - 1] = 0;

    inParser = ITS_TRUE;
    if (xmlSize != 0)
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_FALSE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    else
    {
        parseSuccessful = XML_Parse(parser, buf, size, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
#endif /* NO_FILESYSTEM */

    inParser = ITS_TRUE;
    if (xmlSize)
    {
        parseSuccessful = XML_Parse(parser, xmlData, xmlSize, ITS_TRUE);
        ITS_C_ASSERT(parseSuccessful == 0);
    }
    inParser = ITS_FALSE;

    XML_ParserFree(parser);

#if !defined(NO_FILESYSTEM)
    /* clean up */
    if (buf)
    {
        free(buf);
    }
#endif

    /* reset for the resdb. */
    free(APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class));
    APPLICATION_CLASS_CONFIG_FILE_NAME(itsAPPLICATION_Class) = NULL;
    APPL_SetConfigFileExtension(INI_EXT_STRING);

    /* diff the trees */
    diffMain = (DRIVER_DiffFunc)DLSYM_Resolve(ENGINE_LC_LIBRARY(driver),
                                              DRIVER_DIFF_STRING);
    if (diffMain == NULL)
    {
        if (SERVICE_GetType() == ST_CONSOLE_APPLICATION ||
            SERVICE_GetType() == ST_NOT_SET)
        {
            printf("Error resolving symbol %s : %s\n",
                   DRIVER_DIFF_STRING, DLSYM_Error());
            fflush(stdout);
        }
    }

    ITS_C_ASSERT(diffMain != NULL);

    ret = (diffMain)(tmpApp, application);

    /* restore environment */
    ITS_DestructObject((ITS_Object)tmpApp);

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Stop the main loop.
 *
 *  Input Parameters:
 *      None.
 *
 *  Notes:
 *      This function does not synchronously stop the ENGINE.  Instead,
 *      it marks the main loop with a termination flag.  The engine will
 *      then wait for the thread pools to complete termination before
 *      returning (from ENGINE_Run).
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
ENGINE_Terminate()
{
    SERVICE_SetStopped();
}

/****************************************************************************/
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SIGTRAN M2UA Stack object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_M2UA_IIDClass,
 *                              &LinkList,
 *                              linkSet,
 *                              linkCode,
 *                              IID,
 *                              assoName);
 *
 *  See Also:
 ***************************************************************************/
static int
M2UA_IIDCreate(ITS_Object obj, va_list args)
{
    ENGINE_M2UA_IID iid = (ENGINE_M2UA_IID)obj;
    ITS_Object *rlist, *list;
    char *tmpIid =NULL;
    char *tmpAssoName = NULL;
                                                                                
    rlist = va_arg(args, ITS_Object *);
    ENGINE_M2UA_IID_LINKSET(iid) = (ITS_OCTET)va_arg(args, ITS_UINT);
    ENGINE_M2UA_IID_LINKCODE(iid) = (ITS_OCTET)va_arg(args, ITS_UINT);
                                                                                
    tmpIid = va_arg(args, char *);
    if (tmpIid == NULL)
    {
        ENGINE_M2UA_IID_IID(iid) = tmpIid;
    }
    else
    {
        ENGINE_M2UA_IID_IID(iid) = strdup(tmpIid);
    }
                                                                                
    tmpAssoName = va_arg(args, char *);
    if (tmpAssoName == NULL)
    {
        ENGINE_M2UA_IID_ASSONAME(iid) = tmpAssoName;
    }
    else
    {
        ENGINE_M2UA_IID_ASSONAME(iid) = strdup(tmpAssoName);
    }
    ENGINE_M2UA_IID_NEXT(iid) = NULL;
    ITS_C_ASSERT(rlist != NULL);
                                                                                
    /* tail add */
    for (list = rlist; *list; list = &ENGINE_M2UA_IID_NEXT(*list))
    {
    }
    *list = obj;
                                                                                
    return (ITS_SUCCESS);
                                                                                
}
                                                                                
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a M2ua IID config object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
M2UA_IIDDestroy(ITS_Object obj)
{
}
                                                                                
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Compare IID records for equality.
 *
 *  Input Parameters:
 *      o1, o2 - the objects to compare
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - objects are equivalent.  ITS_FALSE otherwise
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static ITS_BOOLEAN
M2UA_IIDCompare(ITS_Object o1, ITS_Object o2)
{
    if (ENGINE_M2UA_IID_LINKSET(o1) == ENGINE_M2UA_IID_LINKSET(o2) &&
        ENGINE_M2UA_IID_LINKCODE(o1) == ENGINE_M2UA_IID_LINKCODE(o2) &&
        ENGINE_M2UA_IID_IID(o1) == ENGINE_M2UA_IID_IID(o2))
    {
        return (ITS_TRUE);
    }
                                                                                
    return (ITS_FALSE);
}


ITSDLLAPI ITS_ClassRec itsENGINE_M2UA_IIDClassRec =
{
    {
        &itsCORE_ClassRec,                 /* superclass */
        sizeof(ENGINE_M2UA_IIDRec),        /* instance size */
        ITS_FALSE,                         /* class initted */
        0,                                 /* class ref count */
        "ENGINE M2UA_IID Class",           /* class name */
        ITS_CLASS_NO_INIT,                 /* class init */
        ITS_CLASS_NO_DEST,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,            /* class part init */
        ITS_CLASS_PART_NO_DEST,            /* class part destroy */
        M2UA_IIDCreate,                    /* instantiate */
        M2UA_IIDDestroy,                   /* destroy */
        ITS_INST_CLONE_INHERIT,            /* clone */
        ITS_INST_PRINT_INHERIT,            /* print */
        ITS_INST_SERIAL_INHERIT,           /* serialize */
        M2UA_IIDCompare,               	   /* equals */
        ITS_INST_HASH_INHERIT              /* hash */
    }
};
                                                                                
ITSDLLAPI ITS_Class itsENGINE_M2UA_IIDClass =
                                               &itsENGINE_M2UA_IIDClassRec;
                                                                                
/****************************************************************************/
                                                                                

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a SIGTRANStack object
 *
 *  Input Parameters:
 *      obj - the obj to create
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - successful creation
 *
 *  Notes:
 *      ITS_ConstructObject(itsENGINE_SIGTRANStackClass, app, name,
                            variant, numThreads);
 *
 *  See Also:
 ****************************************************************************/
static int
SIGTRANStackCreate(ITS_Object obj, va_list args)
{
    ENGINE_SIGTRANStack stack = (ENGINE_SIGTRANStack)obj;
    ENGINE_Application app;
    char *name;
    int variant;
    ITS_Object *list;
    int numThreads;



    app = va_arg(args, ENGINE_Application);
    name = va_arg(args, char *);


    ITS_C_ASSERT(app != NULL);
    ITS_C_ASSERT(name != NULL && strlen(name) != 0);

    ENGINE_SIGTRAN_NAME(stack) = strdup(name);
    ITS_C_ASSERT(ENGINE_SIGTRAN_NAME(stack) != NULL);

    /* tail add */
    for (list = &ENGINE_APP_SIGTRAN_STACK_CTRL(app);
         *list;
         list = &ENGINE_SIGTRAN_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}

static int
CODECStackCreate(ITS_Object obj, va_list args)
{
    ENGINE_CODECStack stack = (ENGINE_CODECStack)obj;
    ENGINE_Application app;
    char *name;
    int variant;
    ITS_Object *list;
    int numThreads;

    app = va_arg(args, ENGINE_Application);
    name = va_arg(args, char *);


    ITS_C_ASSERT(app != NULL);
    ITS_C_ASSERT(name != NULL && strlen(name) != 0);

    ENGINE_CODEC_NAME(stack) = strdup(name);
    ITS_C_ASSERT(ENGINE_CODEC_NAME(stack) != NULL);

    /* tail add */
    for (list = &ENGINE_APP_CODEC_STACK_CTRL(app);
         *list;
         list = &ENGINE_CODEC_NEXT(*list))
    {
    }
    *list = obj;

    return (ITS_SUCCESS);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a SIGTRAN object
 *
 *  Input Parameters:
 *      obj - the obj to destroy
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
SIGTRANStackDestroy(ITS_Object obj)
{
    int i;
    ITS_Object list, tmp;

    free(ENGINE_SIGTRAN_NAME(obj));

    for (list = ENGINE_SIGTRAN_TRACE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }
}

static void
CODECStackDestroy(ITS_Object obj)
{
    int i;
    ITS_Object list, tmp;

    free(ENGINE_CODEC_NAME(obj));

    for (list = ENGINE_CODEC_TRACE(obj); list != NULL; list = tmp)
    {
        tmp = ENGINE_TL_NEXT(list);

        ITS_DestructObject(list);
    }

    if (ENGINE_CODEC_NUM_TIMERS(obj))
    {
        for (i = 0; i < ENGINE_CODEC_NUM_TIMERS(obj); i++)
        {
            free(ENGINE_CODEC_TIMERS(obj)[i]);
        }

        free(ENGINE_CODEC_TIMERS(obj));
    }
}


ITSDLLAPI ITS_ClassRec itsENGINE_SIGTRANStackClassRec =
{
    {
        &itsCORE_ClassRec,                 /* superclass */
        sizeof(ENGINE_SIGTRANStackRec),    /* instance size */
        ITS_FALSE,                         /* class initted */
        0,                                 /* class ref count */
        "ENGINE SIGTRANStack Class",       /* class name */
        ITS_CLASS_NO_INIT,                 /* class init */
        ITS_CLASS_NO_DEST,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,            /* class part init */
        ITS_CLASS_PART_NO_DEST,            /* class part destroy */
        SIGTRANStackCreate,                /* instantiate */
        SIGTRANStackDestroy,               /* destroy */
        ITS_INST_CLONE_INHERIT,            /* clone */
        ITS_INST_PRINT_INHERIT,            /* print */
        ITS_INST_SERIAL_INHERIT,           /* serialize */
        ITS_INST_EQUALS_INHERIT,           /* equals */
        ITS_INST_HASH_INHERIT              /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_SIGTRANStackClass =
                                               &itsENGINE_SIGTRANStackClassRec;

ITSDLLAPI ITS_ClassRec itsENGINE_CODECStackClassRec =
{
    {
        &itsCORE_ClassRec,                 /* superclass */
        sizeof(ENGINE_CODECStackRec),      /* instance size */
        ITS_FALSE,                         /* class initted */
        0,                                 /* class ref count */
        "ENGINE CODECStack Class",         /* class name */
        ITS_CLASS_NO_INIT,                 /* class init */
        ITS_CLASS_NO_DEST,                 /* class destroy */
        ITS_CLASS_PART_NO_INIT,            /* class part init */
        ITS_CLASS_PART_NO_DEST,            /* class part destroy */
        CODECStackCreate,                  /* instantiate */
        CODECStackDestroy,                 /* destroy */
        ITS_INST_CLONE_INHERIT,            /* clone */
        ITS_INST_PRINT_INHERIT,            /* print */
        ITS_INST_SERIAL_INHERIT,           /* serialize */
        ITS_INST_EQUALS_INHERIT,           /* equals */
        ITS_INST_HASH_INHERIT              /* hash */
    }
};

ITSDLLAPI ITS_Class itsENGINE_CODECStackClass =
                                               &itsENGINE_CODECStackClassRec;
