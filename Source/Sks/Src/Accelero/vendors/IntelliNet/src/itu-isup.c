/****************************************************************************
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
 *  ID: $Id: itu-isup.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/06 09:45:25  mmanikandan
 * LOG: PR6.5.1 Validation Bug(1791) Fix.
 * LOG:
 * LOG: Revision 9.3  2005/04/06 11:21:45  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:21  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.25  2005/03/21 13:53:42  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.13  2005/02/28 09:35:29  mmanikandan
 * LOG: XML Persistancy changes.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.12  2005/02/28 07:48:00  mmanikandan
 * LOG: Changes for XML Persistancy.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.11  2005/02/25 06:42:11  ssingh
 * LOG: Destination specific pegs and mml commands.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.10  2005/02/11 05:54:30  ssingh
 * LOG: Changes to fix bug#1447 [pegs for RSC(T17)/GRS(T23)
 * LOG: timer expiry and respective peg increament.
 * LOG: (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.9  2005/02/03 08:45:29  craghavendra
 * LOG: Fix for GetGeneralCfg.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.8  2005/01/31 11:07:36  snagesh
 * LOG: ISUP OSS APIs added
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.7  2005/01/05 13:11:44  craghavendra
 * LOG: Update the Console Functions for Syslog.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.6  2005/01/05 10:47:13  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.5  2005/01/04 13:43:53  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.4  2004/12/29 14:12:28  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.3  2004/12/23 06:08:13  mkrishna
 * LOG: Avoid crash when mutiple destination r added.
 * LOG: This is propagation from current (Suresh).
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.2  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.9.2.7.2.4.2.1  2004/12/06 14:03:04  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.9.2.7.2.4  2004/11/25 15:28:55  sjaddu
 * LOG: Destination check removed and msgs will not go out in case of backup.
 * LOG:
 * LOG: Revision 7.9.2.7.2.3  2004/09/15 05:46:43  mmanikandan
 * LOG: XML Persistency propagation.
 * LOG:
 * LOG: Revision 7.9.2.7.2.2  2004/01/30 11:12:31  sjaddu
 * LOG: Enabled active-backup configutation
 * LOG:
 * LOG: Revision 7.9.2.7.2.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.9.2.5.2.10  2003/12/17 05:16:53  akumar
 * LOG: Bug fix #730.
 * LOG:
 * LOG: Revision 7.9.2.5.2.9  2003/12/16 10:21:20  ssingh
 * LOG: Bug fix #716
 * LOG:
 * LOG: Revision 7.9.2.5.2.8  2003/12/12 09:56:58  ssingh
 * LOG: Internal fix for ii_get_cic_state MML command.
 * LOG:
 * LOG: Revision 7.9.2.5.2.7  2003/11/24 06:32:32  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.9.2.5.2.6  2003/11/13 10:51:22  akumar
 * LOG: Bug fix 636.
 * LOG:
 * LOG: Revision 7.9.2.5.2.5  2003/10/27 08:40:25  akumar
 * LOG: Introduced msg based PEGs.
 * LOG:
 * LOG: Revision 7.9.2.5.2.4  2003/10/16 12:15:46  akumar
 * LOG: Bug fix 526.
 * LOG:
 * LOG: Revision 7.9.2.5.2.3  2003/10/15 09:11:26  akumar
 * LOG: vcic must start from 1, when ISUP first comes up.
 * LOG:
 * LOG: Revision 7.9.2.5.2.2  2003/10/08 07:42:56  akumar
 * LOG: Vcic in DSM and bug fix.
 * LOG:
 * LOG: Revision 7.9.2.5.2.1  2003/09/05 09:38:34  akumar
 * LOG: Message Based redundancy modifications.
 * LOG:
 * LOG: Revision 7.9.2.5  2003/06/16 14:15:14  sjaddu
 * LOG: Fix for circuit overlap, number circuits can't exeeds limit.
 * LOG:
 * LOG: Revision 7.9.2.4  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.15  2003/04/30 13:34:38  sjaddu
 * LOG: ANSI To ITU changes.
 * LOG:
 * LOG: Revision 8.14  2003/04/30 05:02:14  akumar
 * LOG: MML done. Congestion modified.
 * LOG:
 * LOG: Revision 8.13  2003/04/25 14:04:29  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.12  2003/04/22 08:48:35  akumar
 * LOG: Front Port PR_6.3 MML changes onto current.
 * LOG:
 * LOG: Revision 8.11  2003/04/16 08:30:46  akumar
 * LOG: Congestion related changes.
 * LOG:
 * LOG: Revision 8.10  2003/04/16 08:20:51  sjaddu
 * LOG: Changes for ISUP_UnReserveCIC().
 * LOG:
 * LOG: Revision 8.9  2003/04/04 06:40:52  ssingh
 * LOG: Changes in InitCic/UnreserveCIC.
 * LOG:
 * LOG: Revision 8.8  2003/04/03 15:03:54  sjaddu
 * LOG: ISUP DSM Reorganization.
 * LOG:
 * LOG: Revision 8.7  2003/03/26 10:22:53  ssingh
 * LOG: Defination for UnReserveCIC is added and ReserveCIC modified.
 * LOG:
 * LOG: Revision 8.6  2003/03/06 19:11:42  mmiers
 * LOG: Convert to new tracing, simply by removing file names from
 * LOG: existing trace subsystems.
 * LOG:
 * LOG: Revision 8.5  2003/02/25 22:26:37  mmiers
 * LOG: Finish the split, clean up some warnings.
 * LOG:
 * LOG: Revision 8.4  2003/02/24 22:29:45  mmiers
 * LOG: Vendor library split up.
 * LOG:
 * LOG: Revision 8.3  2003/02/17 06:37:57  akumar
 * LOG: Added ITU MML
 * LOG:
 * LOG: Revision 8.2  2003/02/13 21:39:13  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:26  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.9  2003/02/05 17:27:38  sjaddu
 * LOG: ReserveCic changes for ISUP.
 * LOG:
 * LOG: Revision 7.8  2003/01/22 07:03:03  akumar
 * LOG: Modified for ITU ACC
 * LOG:
 * LOG: Revision 7.7  2003/01/17 15:30:27  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.6  2003/01/14 00:34:21  sjaddu
 * LOG: Cic rule changes and FindOpcDpc() removed from
 * LOG: ValidateCic() function.
 * LOG:
 * LOG: Revision 7.5  2002/12/31 06:05:47  akumar
 * LOG: Modified InitSettings() func to read new variables from the DMP file
 * LOG:
 * LOG: Revision 7.4  2002/11/19 13:48:34  sjaddu
 * LOG: Added one more parameter to AddUsableCics.
 * LOG:
 * LOG: Revision 7.3  2002/10/10 10:54:38  sjaddu
 * LOG: Added ITU ISUP Alarms.
 * LOG:
 * LOG: Revision 7.2  2002/09/26 23:00:10  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/08/21 15:17:23  sjaddu
 * LOG: Removed OpcDpcStat Initialization part.
 * LOG:
 * LOG: Revision 6.9  2002/08/20 16:29:27  mmiers
 * LOG: Use short names
 * LOG:
 * LOG: Revision 6.8  2002/08/19 18:29:32  mmiers
 * LOG: Shortnames
 * LOG:
 * LOG: Revision 6.7  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.6  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.5.2.3  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.5.2.2  2002/07/31 16:12:24  ssharma
 * LOG: Performance improvements.
 * LOG:
 * LOG: Revision 6.5.2.1  2002/07/10 19:39:47  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.5  2002/06/28 19:08:34  ssharma
 * LOG: Redundancy changes.
 * LOG:
 * LOG: Revision 6.4  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.3  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/07 15:44:05  wweng
 * LOG: Rename init/term functions for collision avoidance
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.15.2.10  2002/05/14 18:14:44  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 5.15.2.9  2002/05/09 15:56:37  labuser
 * LOG: Conflict remove after merge.
 * LOG:
 * LOG: Revision 5.15.2.8  2002/05/07 16:12:37  mmiers
 * LOG: Get unique symbol names
 * LOG:
 * LOG: Revision 5.15.2.7.2.1  2002/05/03 15:16:43  labuser
 * LOG: added functionality for PROFILEME
 * LOG:
 * LOG: Revision 5.15.2.7  2002/04/19 01:16:44  hbalimid
 * LOG: modified the ISUP TRACE_LevelInitializer initial traces settings to FALSE
 * LOG:
 * LOG: Revision 5.15.2.6  2002/04/04 17:15:17  ssharma
 * LOG: Debug engine based functional test.
 * LOG:
 * LOG: Revision 5.15.2.5  2002/04/03 18:10:55  ssharma
 * LOG: Fix memory leaks.
 * LOG:
 * LOG: Revision 5.15.2.4  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 5.15.2.3  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 5.15.2.2  2002/03/22 16:21:27  ssharma
 * LOG: Change assert to ITS_C_ASSERT
 * LOG:
 * LOG: Revision 5.15.2.1  2002/03/04 17:37:00  ssharma
 * LOG: Initialize the mtp3 header structure.
 * LOG:
 * LOG: Revision 5.15  2002/02/20 23:24:21  ssharma
 * LOG: Fix traces and Makefile.
 * LOG:
 * LOG: Revision 5.14  2002/02/19 23:04:07  ssharma
 * LOG: Fix traces, .ini file after functional test.
 * LOG:
 * LOG: Revision 5.13  2002/02/14 17:51:40  mmiers
 * LOG: Prototype mismatch
 * LOG:
 * LOG: Revision 5.12  2002/02/13 22:45:23  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.11  2002/02/13 18:28:33  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 5.10  2002/02/12 23:29:04  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.9  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.8  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.7  2002/02/04 21:25:21  mmiers
 * LOG: Integrate with MTP3
 * LOG:
 * LOG: Revision 5.6  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.5  2001/12/17 21:09:22  mmiers
 * LOG: Finish the vendor framework.  Works with NMS MTP2.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.3  2001/08/07 19:11:45  mmiers
 * LOG: Add MTP3 threads.  Also a little cleanup.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 19:18:38  mmiers
 * LOG: Make the stack participate in HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.6  2001/04/04 15:29:17  mmiers
 * LOG: Remove extraneous traces.
 * LOG:
 * LOG: Revision 3.5  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.4  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.3  2001/02/06 17:11:48  mmiers
 * LOG: Multithreaded stack layers are there.  Locking needs to be added
 * LOG: to the context structures.
 * LOG:
 * LOG: Revision 3.2  2000/09/01 20:56:50  mmiers
 * LOG:
 * LOG:
 * LOG: Debugging zero copy.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:34  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/06/28 23:39:56  mmiers
 * LOG:
 * LOG:
 * LOG: Name changes.
 * LOG:
 * LOG: Revision 2.5  2000/03/29 18:29:19  mmiers
 * LOG:
 * LOG: Don't trace for non-errors before the trace settings are established.
 * LOG:
 * LOG: Revision 2.4  2000/02/12 00:41:16  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.3  2000/02/03 17:12:05  fhasle
 * LOG:
 * LOG: First shoet at ISUP Stack.
 * LOG:
 * LOG: Revision 2.2  1999/12/18 00:21:08  mmiers
 * LOG:
 * LOG:
 * LOG: Convert vendor lib to new format.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 23:45:09  mmiers
 * LOG:
 * LOG:
 * LOG: Convert the callback object.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:33  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/10/25 20:24:49  mmiers
 * LOG:
 * LOG:
 * LOG: Corrections for the new transport class.
 * LOG:
 * LOG: Revision 1.7  1999/10/01 14:48:31  mmiers
 * LOG:
 * LOG:
 * LOG: Remove "fileValid" check.  This looks "under the hood" inside
 * LOG: the resource database mechanism and cannot be relied on.
 * LOG:
 * LOG: Revision 1.6  1999/08/26 23:44:58  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.5  1999/08/11 23:08:44  mmiers
 * LOG:
 * LOG:
 * LOG: Trace tweak again.
 * LOG:
 * LOG: Revision 1.4  1999/08/11 19:04:43  mmiers
 * LOG:
 * LOG:
 * LOG: Correct for new trace structures.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 23:59:07  mmiers
 * LOG:
 * LOG:
 * LOG: Standardize the names.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 20:55:07  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:40:37  mmiers
 * LOG:
 * LOG:
 * LOG: Continue dual protocol code.
 * LOG:
 * LOG: Revision 1.17  1999/03/17 15:09:23  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.16  1999/03/12 21:25:44  mmiers
 * LOG:
 * LOG:
 * LOG: Sanitized build.
 * LOG:
 * LOG: Revision 1.15  1999/03/01 20:29:10  mmiers
 * LOG:
 * LOG:
 * LOG: Update this with latest TCAP changes.
 * LOG:
 * LOG: Revision 1.14  1999/02/09 21:46:39  mmiers
 * LOG:
 * LOG:
 * LOG: Use standard thread return type and exit macros.
 * LOG:
 * LOG: Revision 1.13  1998/11/12 00:09:37  mmiers
 * LOG: Debug SSP/SSA.
 * LOG:
 * LOG: Revision 1.12  1998/11/11 00:45:27  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.11  1998/11/10 03:26:35  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.10  1998/11/04 19:00:35  mmiers
 * LOG: Register the pause/resume/status callbacks.
 * LOG:
 * LOG: Revision 1.9  1998/11/04 15:22:20  mmiers
 * LOG: Prep for MTP-PAUSE/RESUME.
 * LOG:
 * LOG: Revision 1.8  1998/11/03 03:04:47  mmiers
 * LOG: Only set started flag after complete initialization.
 * LOG:
 * LOG: Revision 1.7  1998/10/23 00:01:27  whu
 * LOG: Fix debugging flags in INI files.
 * LOG: Fix recently introduced bug in SCCP with connection references.
 * LOG:
 * LOG: Revision 1.6  1998/10/15 14:35:50  mmiers
 * LOG: WIN32 compilation changes.
 * LOG:
 * LOG: Revision 1.5  1998/10/15 01:19:05  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.4  1998/10/14 23:29:35  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 * LOG: Revision 1.3  1998/06/17 21:32:27  mmiers
 * LOG: Get Vendor straightened out.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:31  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 19:57:02  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <its_assertion.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <its.h>
#include <its_app.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_iniparse.h>
#include <its_assertion.h>
#include <its_redundancy.h>
#include <its_ctf.h>

#include <engine.h>
#include <dbc_serv.h>

#ident "$Id: itu-isup.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/isup.h>
#include <china/sccp.h>
#include <china/tcap.h>
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/isup.h>
#include <japan/sccp.h>
#include <japan/tcap.h>
#include <japan/mtp3.h>
#else
#include <itu/isup.h>
#include <itu/sccp.h>
#include <itu/tcap.h>
#include <itu/mtp3.h>
#endif

#include <isup_variants.h>
#include "isup_intern.h"


/* For New Redundancy Scheme */
#include <its_dsm.h>
#include <its_lockable.h>
#include <its_ss7_trans.h>

TQUEUETRAN_Manager *__ISUP_CCITT_RcvQueue;

THREAD_RET_TYPE CCITT_ISUPThread(void *arg);

static void ISUP_Console_CCITT(DBC_Server *dbc, const char *cmdLine);

static ITS_THREAD   *isupThread;
static int numThreads = 1;

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;

extern ITS_BOOLEAN CCITT_ISUP_conglevel1Found;
extern ITS_BOOLEAN CCITT_ISUP_conglevel2Found;

extern ITS_UINT CCITT_ISUP_conglevel1;
extern ITS_UINT CCITT_ISUP_conglevel2;
static ITS_UINT Getlocalconglevel(TQUEUETRAN_Manager *tq);

static TRACE_OutputInitializer fileCritTrace =
{
    ISUP_FILE_STRING,
    ITS_TRUE,
    ISUP_TRACE_CRITICAL_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileErrTrace =
{
    ISUP_FILE_STRING,
    ITS_TRUE,
    ISUP_TRACE_ERROR_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileWarnTrace =
{
    ISUP_FILE_STRING,
    ITS_TRUE,
    ISUP_TRACE_WARNING_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileDebugTrace =
{
    ISUP_FILE_STRING,
    ITS_TRUE,
    ISUP_TRACE_DEBUG_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer fileEventTrace =
{
    ISUP_FILE_STRING,
    ITS_TRUE,
    ISUP_TRACE_EVENT_FILE,
    TRACE_TO_FILE
};

static TRACE_OutputInitializer stdoutTrace =
{
    ISUP_STDOUT_STRING,
    ITS_TRUE,
    NULL,
    TRACE_TO_DISPLAY
};

static TRACE_OutputInitializer syslogTrace =
{
    ISUP_SYSLOG_STRING,
    ITS_TRUE,
    NULL,
#if defined(WIN32)
    TRACE_TO_NT_EVENT_LOG
#else
    TRACE_TO_SYSLOG
#endif
};

static TRACE_LevelInitializer ISUP_TraceMap[] =
{
    {ISUP_CRITICAL_STRING, ITS_FALSE,  3, { &stdoutTrace, &fileCritTrace, &syslogTrace  } },
    {ISUP_ERROR_STRING,    ITS_FALSE,  3, { &stdoutTrace, &fileErrTrace, &syslogTrace   } },
    {ISUP_WARNING_STRING,  ITS_FALSE,  3, { &stdoutTrace, &fileWarnTrace, &syslogTrace  } },
    {ISUP_DEBUG_STRING,    ITS_FALSE,  3, { &stdoutTrace, &fileDebugTrace, &syslogTrace } },
    {ISUP_EVENT_STRING,    ITS_FALSE,  3, { &stdoutTrace, &fileEventTrace, &syslogTrace } }
};

TDATADLLAPI TRACE_Data* ISUP_CCITT_TraceData = NULL;

static char CPCFsmState[][64] = { "IDLE",
                                       "WAIT_INCOMING_ACM",
                                       "WAIT_INCOMING_ANM",
                                       "RCVD_INCOMING_ANM",
                                       "WAIT_INCOMING_RLC",
                                       "WAIT_INCOMING_RES",
                                       "WAIT_OUTGOING_ACM",
                                       "WAIT_OUTGOING_ANM",
                                       "SENT_OUTGOING_ANM",
                                       "WAIT_OUTGOING_RLC",
                                       "WAIT_OUTGOING_RES",
                                       "WAIT_OUTGOING_REL",
                                       "WAIT_OUTGOING_RSC",
                                       "WAIT_OUTGOING_GRA",
                                       "WAIT_CONTINUITY_REPORT",
                                       "WAIT_INCOMING_COT" };

static char BLSFsmState[][64] = { "BLS_IDLE",
                                      "BLS_WAIT_FOR_BLA",
                                      "BLS_LBLOCKED",
                                      "BLS_WAIT_FOR_UBA" };

static char BLRFsmState[][64] = { "BLR_IDLE",
                                      "BLR_WAIT_FOR_BLO_RESP",
                                      "BLR_RBLOCKED",
                                      "BLR_RBLOCKED",
                                      "BLR_WAIT_FOR_UBL_RESP" };

static char MGBSFsmState[][64] = { "MGBS_IDLE",
                                       "MGBS_WAIT_FOR_CGBA",
                                       "MGBS_WAIT_FOR_CGUA" };

static char MGBRFsmState[][64] = { "MGBR_IDLE",
                                       "MGBR_WAIT_FOR_BLO_RESP",
                                       "MGBR_WAIT_FOR_UBL_RESP" };

static char HLBFsmState[][64] = { "HLB_IDLE", "HLB_LBLOCKED" };

static char HRBFsmState[][64] = { "HRB_IDLE", "HRB_RBLOCKED" };

static char HGBSFsmState[][64] = { "HGBS_IDLE",
                                       "HGBS_WAIT_FOR_CGBA",
                                       "HGBS_WAIT_FOR_CGUA" };

static char HGBRFsmState[][64] = { "HGBR_IDLE",
                                       "HGBR_WAIT_FOR_BLO_RESP",
                                       "HGBR_WAIT_FOR_UBL_RESP" };

static char CRSFsmState[][64] = { "CRS_IDLE",
                                       "CRS_WAIT_FOR_RELEASE" };

static char CRRFsmState[][64] = { "CRR_IDLE",
                                       "CRR_WAIT_FOR_RESPONSE" };

static char CGRSFsmState[][64] = { "CGRS_IDLE",
                                       "CGRS_WAIT_FOR_GRA" };

static char CGRRFsmState[][64] = { "CGRR_IDLE",
                                       "CGRR_WAIT_FOR_GROUP_RESET_COMPLETE" };
#define ISUP_ITU_MAX_CICS_IN_DEST  4096

static ITS_UINT pegs[PEG_ISUP_NUM_PEGS];
static PEGS_DECL_SUBSYS(CCITT_ISUP, pegs);
PEG_Manager *CCITT_ISUP_Pegs = &CCITT_ISUP_PEGS;

/* Default values if not specified in the XML file */
ITS_UINT CCITT_ISUP_conglevel1 = 10000;
ITS_UINT CCITT_ISUP_conglevel2 = 20000;
ITS_BOOLEAN CCITT_ISUP_conglevel1Found = ITS_FALSE;
ITS_BOOLEAN CCITT_ISUP_conglevel2Found = ITS_FALSE;
ITS_UINT CCITT_ISUP_localcongtimer = 200;
ITS_SERIAL __ISUP_T99_Serial = 0;

/* Repeat reset timer val (5 min * 2) */
ITS_UINT repeat_rsc_timerval = 600;

static int DBCVarifyCicState(ITS_OCTET cic_state, DBC_Server *dbc);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Parse an ISUP timer
 *
 *  Input Parameters:
 *      key - key from the key-val pair
 *      val - val form the key-val pair
 *      odInfo - configuration information pertaining to the destination
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int 
ParseTimer(char *key, char *val, ISUP_OPC_DPC_STAT *odInfo)
{
    ISUP_TMR_HNDL timeoutHndl;
    ITS_OCTET timer_id = 0;

    timer_id = ISUP_StringToTimer(key);

    if (timer_id >= ISUP_MAX_TMRS)
    {
        ISUP_ERROR(("TimerId incorrect: %s\n", timer_id));
    }
    else
    {
        char *tmp;

        if ((tmp = strchr(val, ',')) != NULL)
        {
            ITS_INT timeout;

            /* split the val string into value and handling */
            *tmp = 0;
            tmp++;

            timeout = RESFILE_ParseNum(val);
            if (timeout < 0)
            {
                /* use the default which is already set */
            }
            else if (timeout == 0)
            {
                /* set it to 0 */
                odInfo->tmr_hndl_info[timer_id].tmr_value = 0;
            }
            else
            {
                /* set it to the value specified */
                odInfo->tmr_hndl_info[timer_id].tmr_value = timeout;
            }

            timeoutHndl = ISUP_StringToTimerHandler(tmp);
            ITS_C_ASSERT(timeoutHndl != ISUP_TMR_HNDL_INVALID);

            odInfo->tmr_hndl_info[timer_id].tmr_hndl_layer = timeoutHndl;
       }
       else
       {
           ISUP_ERROR(("Bad format for ISUP timer string %s=%s\n",
                             key, val));
       }
   }
    return ITS_SUCCESS;

}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Read the resource manager database and populate the local data
 *      structures
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
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                         ID::D0010               enhancement 
 *
 *  Ramesh KV  04-05-2005  BCGI Problem            Optimization of ISUP Stack
 *                         #421 & #423             Initialization.
 ****************************************************************************/
static void
InitSettings(RESFILE_Manager *res, const char *section)
{
    char key[ITS_PATH_MAX << 2], val[ITS_PATH_MAX << 2];

    ITS_BOOLEAN localpcFound = ITS_FALSE;
    ITS_BOOLEAN remotepcFound = ITS_FALSE;
    ITS_BOOLEAN variantFound = ITS_FALSE;
    ITS_BOOLEAN startCicFound = ITS_FALSE;
    ITS_BOOLEAN cicRuleFound = ITS_FALSE;
    ITS_BOOLEAN odInfoIsValid = ITS_FALSE;
    ITS_BOOLEAN sioFound = ITS_FALSE;
    ITS_BOOLEAN segmentationSupported = ITS_FALSE;

    char localpc[32];
    char remotepc[32];
    ITS_UINT    local         = 0;
    ITS_UINT    remote        = 0;
    ITS_OCTET   sio           = 0;
    ITS_OCTET   exchangeType  = 0;

    ISUP_PCIC   startPcic;
    ITS_USHORT  gpid          = 255;
    ITS_CTXT    vcic          = 1;
    ITS_USHORT  cic_index     = 0;
    ITS_UINT    cic_count     = 0;
    ITS_USHORT  startCic      = 0;
    ITS_USHORT  number_cics   = 0;
    ITS_OCTET   cicRule       = ISUP_CKGP_CTRL_DEF;
    ITS_CTXT *current_vcic        = NULL;
    ISUP_OPC_DPC_STAT *odInfo     = NULL;
    const char        *className  = NULL;
    ISUP_CKGP_INFO    ckgp_info;
    MTP3_HEADER hdr;
    ITS_UINT rsctimerval = 0;

    ITS_BOOLEAN isdsmlocal = ITS_FALSE;
    int ret= 0, i;

    /* critical */
    if (RESFILE_GetKeyValueOf(res, section, ISUP_TRACE_CRITICAL_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, ISUP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_CRITICAL_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_CRITICAL_STRING, ITS_FALSE);
        }
    }

    /* error */
    if (RESFILE_GetKeyValueOf(res, section, ISUP_TRACE_ERROR_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, ISUP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_ERROR_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_ERROR_STRING, ITS_FALSE);
        }
    }

    /* warning */
    if (RESFILE_GetKeyValueOf(res, section, ISUP_TRACE_WARNING_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, ISUP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_WARNING_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_WARNING_STRING, ITS_FALSE);
        }
    }

    /* debug */
    if (RESFILE_GetKeyValueOf(res, section, ISUP_TRACE_DEBUG_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;

        if (strstr(val, ISUP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_DEBUG_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_DEBUG_STRING, ITS_FALSE);
        }
    }

    /* Event */
    if (RESFILE_GetKeyValueOf(res, section, ISUP_TRACE_EVENT_STRING,
                              val, ITS_PATH_MAX) == ITS_SUCCESS)
    {
        ITS_BOOLEAN std = ITS_FALSE, fil = ITS_FALSE, sys = ITS_FALSE;
                                                                                           
        if (strstr(val, ISUP_STDOUT_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_STDOUT_STRING, ITS_TRUE);
            std = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_STDOUT_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_FILE_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_FILE_STRING, ITS_TRUE);
            fil = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_FILE_STRING, ITS_FALSE);
        }
        if (strstr(val, ISUP_SYSLOG_STRING) != NULL)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_SYSLOG_STRING, ITS_TRUE);
            sys = ITS_TRUE;
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_SYSLOG_STRING, ITS_FALSE);
        }

        if (std || fil || sys)  
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_EVENT_STRING, ITS_FALSE);
        }
    }
    /* Lock the opc_dpc_stat table so other nodes will wait here*/
    ret = ISUP_LockOpcDpcStatTable();
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("ISUP_LockOpcDpcStatTable: Table Locked\n"));
    }

    ITS_C_ASSERT(ret == ITS_SUCCESS);

    RESFILE_Rewind(res, section);
    RESFILE_Lock(res);

    while (RESFILE_GetKeyName(res, section, key, ITS_PATH_MAX)
                                                   == ITS_SUCCESS &&
           RESFILE_GetKeyValue(res, section, val, ITS_PATH_MAX)
                                                   == ITS_SUCCESS)
    {
        if (strcmp(DEST_POINT_CODE_STRING, key) == 0)
        {
            strcpy(remotepc, val);
            remotepcFound = ITS_TRUE;
            remote = RESFILE_ParseNum(remotepc);
            ISUP_DpcTransAddEntry(remote);
            
            if (startCicFound == ITS_TRUE || cicRuleFound == ITS_TRUE)
            {
               ISUP_ERROR (("Failed to configure Last Circuit group for "
                            "previous Destination; Current Desitnation %s\n",
                            val));

               ISUP_UnLockOpcDpcStatTable();
               RESFILE_Unlock(res);
               return;
            }

            if (odInfoIsValid)
            {
                ISUP_SyncOpcDpcInfoWithStat(odInfo);
                ISUP_ReleaseOpcDpcStat(odInfo, isdsmlocal);

                /* Initialize other static variables */
                localpcFound = ITS_FALSE;
                sioFound = ITS_FALSE;
                variantFound = ITS_FALSE;
                startCicFound = ITS_FALSE;
                cicRuleFound = ITS_FALSE;

                startCic = 0;
                cic_index = 0;
                number_cics = 0;
                cic_count = 0;
            }
        }
        else if (strcmp(LOCAL_POINT_CODE_STRING, key) == 0)
        {
            strcpy(localpc, val);
            localpcFound = ITS_TRUE;
        }
        else if (strcmp(SIO_STRING, key) == 0)
        {
            sioFound = ITS_TRUE;
            sio = (ITS_OCTET)RESFILE_ParseNum(val);
        }
        else if (strcmp(ISUP_XCHANGE_TYPE_STR, key) == 0)
        {
            exchangeType = ISUP_StringToXchangeType(val);

            if (exchangeType == ISUP_XCHANGE_TYPE_INV)
            {
                ISUP_ERROR(("Exchange Type Incorrect: %s\n", val));
                odInfo->exchange_type = ISUP_XCHANGE_TYPE_A;
            }
            else
            {
                ISUP_DEBUG(("Exchange Type: %s\n", val));
                odInfo->exchange_type = exchangeType;
            }
        }
        else if (strcmp(ISUP_SEG_SUPPORT_STR, key) == 0)
        {
            segmentationSupported = ISUP_StringToSegSupport(val);
            odInfo->segmentation_supported = segmentationSupported;
        }
        else if (strcmp(DI_ISUP_VAR_STRING, key) == 0)
        {
            ITS_OCTET varType = ISUP_ITU_MIN;

            variantFound = ITS_TRUE;

            if(!remotepcFound || !localpcFound || !sioFound)
            {
                if (!remotepcFound)
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check RemotePC\n"));
                }
                else if (!localpcFound)
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check LocalPC\n"));
                }
                else
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check SIO\n"));
                }

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            varType = ISUP_StringToVariant(val);

            if (varType == ISUP_UNKNOWN)
            {
                ISUP_ERROR(("Variant %s unknown\n", val));

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            if (ISUP_VariantStringIsCCITT(val))
            {
                local = RESFILE_StrToPointCode_ANSI(localpc);
                if(local == RESFILE_BAD_POINT_CODE)
                {
                   local = RESFILE_ParseNum(localpc);
                }

                remote = RESFILE_StrToPointCode_ANSI(remotepc);
                if(remote == RESFILE_BAD_POINT_CODE)
                {
                   remote = RESFILE_ParseNum(remotepc);
                }
            }
            else
            {
                ISUP_ERROR(("Invalid variant %s for ITU\n", val));

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            memset(&hdr, 0, sizeof(MTP3_HEADER));

            MTP3_HDR_SET_SIO_CCITT(hdr, sio);
            MTP3_RL_SET_OPC_VALUE(hdr.label, local);
            MTP3_RL_SET_DPC_VALUE(hdr.label, remote);

            /* This will tell us ISUP is already initialized */
            if(__ISUP_IsInitialized(hdr))
            {
                ISUP_AllocAllLocalTables();

                /*Set these values, these are local variabels*/
                if (RESFILE_GetKeyValueOf(res, section, ISUP_CONG_LEVEL1_STR,
                                          val, ITS_PATH_MAX) == ITS_SUCCESS)
                {
                    CCITT_ISUP_conglevel1 = (ITS_LONG)RESFILE_ParseNum(val);
                }

                if (RESFILE_GetKeyValueOf(res, section, ISUP_CONG_LEVEL2_STR,
                                          val, ITS_PATH_MAX) == ITS_SUCCESS)
                {
                    CCITT_ISUP_conglevel2 = (ITS_LONG)RESFILE_ParseNum(val);
                }

                if (RESFILE_GetKeyValueOf(res, section, ISUP_LOCCONG_TIMER_STR,
                                          val, ITS_PATH_MAX) == ITS_SUCCESS)
                {
                    CCITT_ISUP_localcongtimer = (ITS_LONG)RESFILE_ParseNum(val);
                }

                RESFILE_Unlock(res);

                ret = ISUP_UnLockOpcDpcStatTable();
                if(ret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("ISUP_UnLockOpcDpcStatTable: Failed to UnLock Table\n"));
                }
                else
                {
                    ISUP_DEBUG(("ISUP_UnLockOpcDpcStatTable: UnLocking Table \n"));
                }

                ITS_C_ASSERT(ret == ITS_SUCCESS);
                return;
            }

            odInfo = ISUP_AllocOpcDpcStat(hdr, varType);
            if (odInfo == NULL)
            {
                ISUP_ERROR(("ISUP_AllocOpcDpcStat: Failed to Alloc OpcDpcStat\n"));

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                ITS_C_ASSERT(odInfo != NULL);
                return;
            }

            odInfoIsValid = ITS_TRUE;

        }
        else if(    (strcmp(ISUP_TIMER_T1_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T2_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T3_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T4_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T5_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T6_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T7_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T8_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T9_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T10_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T11_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T12_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T13_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T14_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T15_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T16_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T17_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T18_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T19_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T20_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T21_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T22_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T23_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T24_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T25_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T26_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T27_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T28_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T29_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T30_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T31_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T32_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T33_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T34_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T35_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T36_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T37_STRING, key) == 0) ||
                    (strcmp(ISUP_TIMER_T38_STRING, key) == 0) || 
                    (strcmp(ISUP_TIMER_T39_STRING, key) == 0) )
        {
            ret = ParseTimer(key, val, odInfo);
            if (ret != ITS_SUCCESS)
            {
                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }
        }
        else if (strcmp(ISUP_CIC_RULE_STR, key) == 0)
        {
            /*
             * Check: Mandatory params.
             * OPC / DPC / Variant should be set by now
             */
            if (!localpcFound || !remotepcFound || !variantFound)
            {
                if (!remotepcFound)
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check RemotePC\n"));

                }
                else if (!localpcFound)
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check LocalPC\n"));

                }
                else
                {
                    ISUP_ERROR(("Incomplete Configuration Info: "
                                "Check Variant string\n"));

                }

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            if (cicRuleFound == ITS_TRUE)
            {
                if(startCicFound == ITS_TRUE)
                {
                   ISUP_ERROR(("Failed to get number of Cics for Group; StartCIC : %d\n",
                                startCic));
                }
                else
                {
                   ISUP_ERROR(("Failed to get StartCic and NumberOfCics for Group \n"));
                }

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            startCicFound = ITS_FALSE;
            number_cics = 0;

            cicRule = ISUP_StringToCkgpCtrl(val);
            if (cicRule == ISUP_CKGP_CTRL_INV)
            {
                ISUP_ERROR(("CIC rule Incorrect: %s\n", val));
                cicRuleFound = ITS_FALSE;
            }
            else
            {
                ISUP_DEBUG(("cic rule: %s\n", val));
                cicRuleFound = ITS_TRUE;
            }
        }
        else if (strcmp(ISUP_START_CIC_STR, key) == 0)
        {
            if(cicRuleFound != ITS_TRUE)
            {
                ISUP_ERROR (("CIC Rule not defined; StartCIC %s\n", val));

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }   

            startCic = (ITS_USHORT)RESFILE_ParseNum(val);
            ISUP_DEBUG(("start cic : %d\n", startCic));
            startCicFound = ITS_TRUE;
        }
        else if (strcmp(ISUP_NUM_CICS_STR, key) == 0)
        {
            if (startCicFound == ITS_FALSE)
            {
                ISUP_ERROR(("Failed to get Start Cic\n"));

                ISUP_UnLockOpcDpcStatTable();
                RESFILE_Unlock(res);
                return;
            }

            number_cics = (ITS_USHORT)RESFILE_ParseNum(val);
            ISUP_DEBUG(("number of cics : %d\n", number_cics));

            cic_count += number_cics;

            if (startCicFound)
            {
                if (cic_count > ISUP_ITU_MAX_CICS_IN_DEST)
                {
                    ISUP_ERROR(("Number of CICs exeeding the MAX allowed"
                                " in ITU ISUP 4096 (2^12)\n"));
                    ISUP_ERROR(("\n\nExiting the Initialization: Correct above "
                                "Errors first\n"));
                    ISUP_UnLockOpcDpcStatTable();
                    RESFILE_Unlock(res);
                    return;     
                }

                memset(&startPcic, 0, sizeof(startPcic));

                ISUP_PCICFromParts(&startPcic, local, remote, sio, startCic);

                ret = ISUP_AllocCics(vcic, startPcic, number_cics, cicRule);

                if (ret != ITS_SUCCESS)
                {
                    ISUP_ERROR(("Invalid CIC configuration: Reason CICs are"
                                " overlaping please check this range"
                                " Start CIC = %d  and count = %d\n",
                                startCic, number_cics));
                    ISUP_ERROR(("\n\nExiting the Initialization: Correct above "
                                "Errors first\n"));

                    ISUP_UnLockOpcDpcStatTable();
                    RESFILE_Unlock(res);
                    return;
                }
                ISUP_DEBUG(("Going to insert ckgp info: gpid %d.\n", gpid));

                vcic += number_cics;

                className = ISUP_VariantToString(odInfo->isup_var_type);

                for(i = 0; i < number_cics ; ++i)
                {
                    ITS_INT exists;
                    ISUP_CKGP_LIST *ckgp_list = NULL;
                    ITS_USHORT acic = (ITS_USHORT)(startCic + i);
                    int j = 0;
                    ITS_USHORT numCics = 0;

                    VAR_GetCkgpFromCIC (ITS_FindFeature(className),
                                        acic,
                                        &cic_index,
                                        &gpid,
                                        &numCics);

                    ISUP_InitCkgp(&ckgp_info, gpid);

                    ckgp_list = ISUP_FindCktGrpInfo (odInfo, gpid,
                                                     &ckgp_info, &exists);

                    for (j = 0; (j < numCics) && (i < number_cics); ++j)
                    {
                        ISUP_AddUsableCic (odInfo, &ckgp_info,
                                           cic_index, cicRule);
                        cic_index++;
                        i++;
                    }

                    --i;

                    if (exists == ITS_SUCCESS)
                    {
                        ISUP_UpdateCktGrpInfo (odInfo, gpid , &ckgp_info,
                                                              ckgp_list);
                    }
                    else
                    {
                        ISUP_InsertCktGrpInfo (odInfo, &ckgp_info, ckgp_list);
                    }
                }

                ISUP_DEBUG(("Ckgp %d provisioned.\n", gpid));

                number_cics = 0;
                startCicFound = ITS_FALSE;
                cicRuleFound  = ITS_FALSE;
           }
        }
        else if (strcmp(ISUP_CONG_LEVEL1_STR, key) == 0)
        {
            CCITT_ISUP_conglevel1 = (ITS_LONG)RESFILE_ParseNum(val);
        }
        else if (strcmp(ISUP_CONG_LEVEL2_STR, key) == 0)
        {
            CCITT_ISUP_conglevel2 = (ITS_LONG)RESFILE_ParseNum(val);
        }
        else if (strcmp(ISUP_LOCCONG_TIMER_STR, key) == 0)
        {
            CCITT_ISUP_localcongtimer = (ITS_LONG)RESFILE_ParseNum(val);
        }
        else if (strcmp(ISUP_AUTORSC_TIMER_STR, key) == 0)
        {
            rsctimerval = (ITS_LONG)RESFILE_ParseNum(val);
            if (rsctimerval == 0)
            {
                odInfo->repeat_rsc_timerval = repeat_rsc_timerval;
            }
            else
            {
                odInfo->repeat_rsc_timerval = (ITS_LONG)RESFILE_ParseNum(val);
            }
            ISUP_DEBUG(("\n---value of repeat_rsc_timer is %d---\n",
                       odInfo->repeat_rsc_timerval));
        }
    }

    RESFILE_Unlock(res);

    if (cicRuleFound == ITS_TRUE)
    {
        if(startCicFound == ITS_TRUE)
        {
            ISUP_ERROR(("Failed to get number of Cics for Group; StartCIC : %d\n", startCic));
        }
        else
        {
            ISUP_ERROR(("Failed to get StartCic and NumberOfCics\n"));

            ISUP_UnLockOpcDpcStatTable();
            return;
        }
    }

    /* Allocate space for current_vcic in hash table */
    current_vcic = ISUP_AllocVcic();

    *current_vcic = vcic;

    /* Save it back in the Table */
    ISUP_ReleaseVcic(current_vcic);

    if (odInfoIsValid)
    {
        ISUP_SyncOpcDpcInfoWithStat(odInfo);
        ISUP_ReleaseOpcDpcStat(odInfo, isdsmlocal);
    }

    /* Un Lock the opc_dpc_stat table so other nodes will resume */
    ret = ISUP_UnLockOpcDpcStatTable();
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("ISUP_UnLockOpcDpcStatTable: Un Locking Table  \n"));
    }
    else
    {
        ISUP_ERROR(("ISUP_UnLockOpcDpcStatTable: Failed to UnLock Table\n"));
    }

    ITS_C_ASSERT(ret == ITS_SUCCESS);
    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To validate a particular CIC for use in a call or other operation to
 *      be initiated by the user application.
 *
 *  Input Parameters:
 *      h   - handle for the transport
 *      sio - sio containing the network indicator
 *      opc - The Originating Point Code (the node on which this ISUP stack
 *            is running) for which this cic is configured.
 *      dpc - The Destination Point Code (the remote node) for which this cic
 *            is configured.
 *      cic - The CIC to be validated.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      cic_state - the circuit state for the specified CIC.
 *      vcic - virtual cic corresponding to the cic
 *
 *  Return Value:
 *      On Success - ITS_SUCCESS is returned.
 *      On Failure - One of the following values indicates the failure.
 *          ITS_ENOTCONFIG - The specified CIC is not configured between this
 *                           opc-dpc pair.
 *          ITS_EINVOPC - The opc specified is not part of the configuration.
 *          ITS_EINVDPC - The dpc specified is not part of the configuration.
 *          ITS_ECICBUSY - The specified CIC is currently occupied in a call.
 *          ITS_ECICBLOCK - The specified CIC in a blocked state as given by
 *                          the output cic_state.
 *          ITS_ENOTCONTRLD - The CIC is configured so that the application is
 *                            not the master.
 *
 *  Notes:
 *      Order of checks to validate CIC:
 *          1. OPC info
 *          2. DPC info
 *          3. CIC config info
 *          4. Call state of CIC
 *          5. Maintenance state of CIC
 *          6. Hardware state of CIC
 *          7. Control of CIC
 *
 ****************************************************************************/
int
INTELLINET_ReserveCIC_CCITT(ITS_HANDLE h,
                            ITS_OCTET sio, ITS_UINT opc, ITS_UINT dpc,
                            ITS_USHORT cic, ITS_OCTET* cic_state,
                            ITS_CTXT *vcic)
{
    ISUP_PCIC pcic;
    ITS_UINT ret  = 0;
    ISUP_CIC_INFO *cic_rec = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;


    if (vcic == NULL || cic_state == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Convert cic, opc, dpc to pcic */
    ISUP_PCICFromParts(&pcic, opc, dpc, sio, cic);

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    /*FIX ME check the usability of the cic*/
    if(cic_rec->resrv_ind)
    {
        ret = ITS_ECICBUSY;
    }

    /* copy the context back to the user */
    *vcic = cic_rec->vcic;

    /* Update output parameter with the cic state */
    *cic_state = cic_rec->cic_state;


    /* Check CIC state from the cic_rec. */
    if (ISUP_CIC_GET_CALL(cic_rec->cic_state) != CKTS_IDLE_CTK)
    {
        /* call-state is BUSY */
        ret = ITS_ECICBUSY;
    }
    else
    {
        /* mtce-state may be L/R-BLOCKED. */
        if (ISUP_CIC_GET_MAINT(cic_rec->cic_state) != CKTS_ACTIVE)
        {
            /* Blocking bit is set */
            ret = ITS_ECICBLOCK;
        }
    }

    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseCic(cic_rec, isdsmlocal);
        return ret;
    }

    if (cic_rec->cic_rule == ISUP_CKGP_CTRL_ALL)
    {
        ret = ITS_SUCCESS;
    }
    else if (cic_rec->cic_rule == ISUP_CKGP_CTRL_NONE)
    {
        ret = ITS_ENOTCONTRLD;
    }
    else if ((cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_EVEN))
    {
        /* cic is odd, but control is EVEN */
        ret = ITS_ENOTCONTRLD;
    }
    else if (!(cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_ODD))
    {
        /* cic is even, but control is ODD */
        ret = ITS_ENOTCONTRLD;
    }

    if(ret == ITS_SUCCESS)
    {
        cic_rec->resrv_ind = ITS_TRUE;
    }

    ret = ISUP_ReleaseCic(cic_rec, isdsmlocal);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will start a timer and store the relevant information
 *      in the CIC record. It will also restart an expired timer and update
 *      the CIC record appropriately.
 *
 *  Input Parameters:
 *      cic_rec - the record of the cic for which this timer is to be started
 *      timerId - the Id of the timer to start.
 *      timerValue - The value of the timer (in seconds).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS if timer was started successfully. 
 *      Otherwise, values indicate failure to start timer.
 *
 *  See Also:
 *      __ISUP_StopTimer(ISUP_CIC_INFO *cic_rec, ITS_OCTET timerId);
 *
 ****************************************************************************/
ITSSS7DLLAPI int
__ISUP_StartTimer_CCITT(ISUP_CIC_INFO *cic_rec, ITS_OCTET timerId,
                        int timerValue)
{
    ISUP_TIMER_ENTRY timerInfo;
    ISUP_PNDG_TMR_INFO pend_timer, p_timer;
    ITS_SERIAL t_serial = 0;
    int ret = ITS_SUCCESS;

    memset((char*)&timerInfo, 0, sizeof(ISUP_TIMER_ENTRY));
    
    timerInfo.timerId = timerId;
    timerInfo.cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);
    timerInfo.opc = ISUP_PCIC_TO_OPC(cic_rec->pcic);
    timerInfo.dpc = ISUP_PCIC_TO_DPC(cic_rec->pcic);
    timerInfo.sio = ISUP_PCIC_TO_SIO(cic_rec->pcic);

    if ((t_serial = TIMERS_StartSharedTimer(ITS_ISUP_SRC, timerValue,
                                      (void*)&timerInfo,
                                      sizeof(ISUP_TIMER_ENTRY))) == 0)
    {
        ISUP_CRITICAL((
            "__ISUP_StartTimer: Failed to start timer T%d.\n", timerId));

#ifdef CCITT
        /* ISUP_Alarm_CCITT(3402, __FILE__, __LINE__, "Timer is T%d", timerId); */
#endif

        return ITS_ETIMERSTARTFAIL;
    }

    ISUP_DEBUG(("__ISUP_StartTimer: Started timer T%d.\n", timerId));

    memset((char *)&pend_timer, 0, sizeof(ISUP_PNDG_TMR_INFO));

    pend_timer.tmr_id = timerId;
    pend_timer.tmr_serial = t_serial;

    /* Search for timer already present, in which case update info */
    ret = ISUP_FindPndgTmrInfo(cic_rec, timerId, &p_timer);
    if (ret != ITS_SUCCESS)
    {
        ret = ISUP_InsertPndgTmrInfo(cic_rec, &pend_timer);
        if (ret != ITS_SUCCESS)
        {
            ISUP_CRITICAL(("StartTimer: Failed to insert timer t%d.\n", timerId));
        }
    }
    else
    {
        ret = ISUP_UpdatePndgTmrInfo(cic_rec, timerId, &pend_timer);
        if (ret != ITS_SUCCESS)
        {
            ISUP_CRITICAL(("StartTimer: Failed to update timer t%d.\n", timerId));
        }
    }
    return ret;
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will stop a timer that is running. 
 *
 *  Input Parameters:
 *      cic_rec - the record of the cic for which this timer is to be stopped
 *      timerId - the Id of the timer to stop.
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
 *  See Also:
 *      __ISUP_StartTimer(ISUP_CIC_INFO *cic_rec, ITS_OCTET timerId, 
 *                        int timerValue);
 *
 ****************************************************************************/
ITSSS7DLLAPI void
__ISUP_StopTimer_CCITT(ISUP_CIC_INFO *cic_rec, ITS_OCTET timerId)
{
    int ret = ITS_SUCCESS;
    ISUP_PNDG_TMR_INFO pend_timer;

    ret = ISUP_FindPndgTmrInfo(cic_rec, timerId, &pend_timer);
    if (ret != ITS_SUCCESS)
    {
        return;
    }

    TIMERS_CancelSharedTimer(pend_timer.tmr_serial);

    ISUP_DEBUG(("__ISUP_StopTimer: Stopped timer T%d.\n", timerId));
    
    ret = ISUP_DeletePndgTmrInfo(cic_rec, timerId);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("StopTimer: Couldn't delete timer info from CIC rec.\n"));

#ifdef CCITT
        /* ISUP_Alarm_CCITT(3403, __FILE__, __LINE__, "Timer is T%d", timerId); */
#endif

    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This is a call back method state changes
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
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ISUP_StateChangeCallback(ITS_POINTER object,
                         ITS_POINTER userData,
                         ITS_POINTER callData)
{
    ITS_EVENT *evt = (ITS_EVENT*)callData;

    if (evt->data[1] == ITS_STATE_PRIMARY)
    {
        ISUP_CRITICAL(("Request received for change state to active\n"));
    }
    else
    {
        /* Here we have lot of work to do, changing state from active to
         * back up, clean up the  existing transaction TBD
         */
        ISUP_CRITICAL(("Request received for change state to backup\n"));
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes the ISUP subsystem for use.
 *
 *  Input Parameters:
 *      handle - the ss7 transport handle.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the subsystem is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISUP_Init_CCITT(RESFILE_Manager *res, const char *section)
{
    int ret;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    /* The context for the timer */
    ISUP_TIMER_ENTRY timerInfo;

    if ((ISUP_CCITT_TraceData = TRACE_Constructor("ITU-ISUP",
                                                  ISUP_TraceMap, 5)) == NULL)
    {
        return (ITS_ENOMEM);
    }

    ret = __ISUP_Init_HashTables_CCITT();
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ISUP_Initialize: couldn't context tables.\n"));

        return ret;
    }

    /* read the INI */
    if (res)
    {
        InitSettings(res, section);
    }

    /*Check what kind of reduancy type is configured, could be stub also*/
    if (redunClass != NULL)
    {
        /* Means this not stub, it could be either active-standby or
         * active-active, find what config from redundancy class
         */
        if (REDUNDANCY_CONFIGURED_TYPE(redunClass)  == ITS_ACTIVE_STANDBY)
        {
            /* active-stand is configured , register a call back 
             * to receive state changes
             */
            CALLBACK_AddCallback(REDUNDANCY_CALLBACK_MGR(redunClass), 
                                 ISUP_StateChangeCallback, NULL);

            ISUP_DEBUG(("ACTIVE-STANDBY configured registering call back\n"));
        }
        else
        {
            ISUP_DEBUG(("ACTIVE-ACTIVE configured no need to register\n"));
        }
    }
    
    /* We need to start a timer to monitor local congestion
     * control, every time this Timer expires, check ISUP
     * local congestion, if not restart the timer with the
     * same val, else with reduced value. Since, this timer
     * is independent of cic (cic_rec). We will have a unique
     * symbol given T99.
     *
     * Start Local Congestion Control Timer T99 */

    memset((char*)&timerInfo, 0, sizeof(ISUP_TIMER_ENTRY));

    /* Fil up the Timer Id */
    timerInfo.timerId = ITS_ISUP_TIMER_T99;

    if (!CCITT_ISUP_localcongtimer)
    {
         /* Assign Def Value if not configured frm XML */
         CCITT_ISUP_localcongtimer = 10;
    }
    if (TIMERS_StartTimer(ITS_ISUP_CCITT_SRC, (int)CCITT_ISUP_localcongtimer,
                                     (void*)&timerInfo,
                                      sizeof(ISUP_TIMER_ENTRY)) == 0)
    {
        ISUP_CRITICAL((
            "__ISUP_StartTimer: Failed to start timer T%d.\n",
                                          timerInfo.timerId));
        return ITS_ETIMERSTARTFAIL;
    }
    ISUP_DEBUG(("\n ***Started Local Cong T99 Timer val %d  ***\n",
                CCITT_ISUP_localcongtimer));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the ISUP subsystem.  Well behaved
 *      applications should call this function before exiting.
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
 *      If the subsystem is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
void
ISUP_Term_CCITT()
{
    ISUP_DpcTransTableIterate();

    __ISUP_Term_HashTables_CCITT();

    TRACE_Destructor(ISUP_CCITT_TraceData);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI ISUPGeneralCfg*
ISUP_GetGeneralCfg_CCITT()
{
    ISUPGeneralCfg *ret;

    ret = calloc(1, sizeof(ISUPGeneralCfg));
    if (ret == NULL)
    {
        return (NULL);
    }

    ret->traceOn = (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_DEBUG) &&
                    (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      0) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      1) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      2))) ||
                   (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_WARNING) &&
                    (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      0) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      1) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      2))) ||
                   (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                   ISUP_TRACE_ERROR) &&
                    (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      0) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      1) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      2))) ||
                   (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_CRITICAL) &&
                    (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      0) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      1) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      2))) ||
                   (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_EVENT) &&
                    (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      0) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      1) ||
                     TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      2)));
    ret->alarmLevel = ISUP_AlarmLevel_CCITT;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_SetGeneralCfg_CCITT(ISUPGeneralCfg *data)
{
    ISUP_AlarmLevel_CCITT = data->alarmLevel;

    if (strstr(data->traceType, "all") != NULL)
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_CRITICAL_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_ERROR_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_WARNING_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_DEBUG_STRING, ITS_TRUE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      ISUP_EVENT_STRING, ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       data->traceOutput, ITS_FALSE);

            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       data->traceOutput, ITS_FALSE);
        }
    }
    else
    {
        if (data->traceOn == ITS_TRUE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_TRUE);
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData,
                                      data->traceType, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       data->traceType,
                                       data->traceOutput, ITS_FALSE);
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int ISUP_GetDestCfgInfo_CCITT(ISUP_CFG_KEY cfg,
                              ISUP_CFG_DEST_INFO* info)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni,cfg.sio);


    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    memcpy(&info->cfg, &cfg , sizeof(cfg));
    info->variant =  config_stat->isup_var_type;

    info->congesInd = (ISUP_CFG_CONGES)config_stat->isup_rmt_conglev;
    info->dest_reachable = (ISUP_CFG_DEST_STATUS)config_stat->dest_stat;
    info->remote_isup_stat = (ISUP_CFG_REMOTE_ISUP_STATUS)
                            config_stat->remote_isup_stat;
    info->exchange_type = (ISUP_CFG_EXCHANGE_TYPE)
                            config_stat->exchange_type;
    memcpy(info->timer_info,  config_stat->tmr_hndl_info,
                               sizeof(ISUP_CFG_TMR_INFO)*ISUP_CFG_MAX_TIMERS);

    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Add New destination for ISUP.
 *
 *  Input Parameters:
 *      cfg -  is type of ISUP_CFG_KEY.
 *      varType - Varaint Name.
 *      exType  - Exchange Type.
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *          ITS_ENOROUTE
 *          ITS_EINVXCHANGE
 *          ITS_ENOFEATURE
 *          ITS_EINUSE
 *          ITS_ENOMEM
 *          ITS_SUCCESS
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_AddDestCfgInfo_CCITT(ISUP_CFG_KEY cfg,
                          char *varType, char *exType)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat;
    ISUP_VAR_TYPE variant;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

#if 0
    /* Check for Destination its self */
    if (!ISUP_IsRouteExists(cfg.dpc, cfg.sio))
    {
        return ITS_ENOROUTE;
    }
#endif
        
    if (ISUP_XCHANGE_TYPE_INV == ISUP_StringToXchangeType(exType))
    {
        return ITS_EINVXCHANGE;
    }

    variant = ISUP_StringToVariant(varType);
    if (!(variant == ISUP_ITU_97 || variant == ISUP_ITU_GENERIC_93))
    {
        return ITS_ENOTFOUND;
    }
        
    if (ITS_FindFeature(varType) == NULL)
    { 
        return ITS_ENOFEATURE;
    }

    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat != NULL)
    {
        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
        return ITS_EINUSE;
    }

    config_stat = ISUP_AllocOpcDpcStat(opc_dpc_ni,
                                       ISUP_StringToVariant(varType));
    if (config_stat == NULL)
    {
        return ITS_ENOMEM;
    }
    config_stat->exchange_type = ISUP_StringToXchangeType(exType);

    ISUP_SyncOpcDpcInfoWithStat(config_stat);
    return ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
}
/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int ISUP_GetTimerCfgInfo_CCITT (ISUP_CFG_KEY cfg, int tId,
                                ISUP_CFG_TMR_INFO* info)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni,cfg.sio);

    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL || tId > ISUP_CFG_MAX_TIMERS)
    {
        return ITS_ENOTCONFIG;
    }

    memcpy(info, &config_stat->tmr_hndl_info[tId],
                 sizeof(ISUP_CFG_TMR_INFO));

    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
    return ITS_SUCCESS;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int ISUP_GetAllTimerCfgInfo_CCITT (ISUP_CFG_KEY cfg,
                                   ISUP_CFG_TMR_INFO* tEnt)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni,cfg.sio);

    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    memcpy(tEnt, config_stat->tmr_hndl_info,
           sizeof(ISUP_CFG_TMR_INFO)*ISUP_CFG_MAX_TIMERS);
    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
    return ITS_SUCCESS;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_SetTimerCfgInfo_CCITT (ISUP_CFG_KEY cfg, int tId,
                               int tVal,
                               ISUP_CFG_TMR_HNDL handlBy)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = 0;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    if ((tId) > ISUP_CFG_MAX_TIMERS)
    {
        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
        return ITS_ENOTCONFIG;
    }
    else
    {
        /* FIXME --
        switch((tId))
        {
        case ITS_ISUP_TIMER_T2:
        case ITS_ISUP_TIMER_T3:
        case ITS_ISUP_TIMER_T4:
        case ITS_ISUP_TIMER_T10:
        case ITS_ISUP_TIMER_T29:
        case ITS_ISUP_TIMER_T30:
        case ITS_ISUP_TIMER_T35:
            ISUP_ReleaseOpcDpcStat(config_stat);
            return ITS_ENOTCONFIG;
        }
        --*/
        config_stat->tmr_hndl_info[tId].tmr_value = tVal; 
        config_stat->tmr_hndl_info[tId].tmr_hndl_layer = (ISUP_TMR_HNDL) handlBy;
    }
    ISUP_SyncOpcDpcInfoWithStat(config_stat); 
    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_AddCicsCfg_CCITT(ISUP_CFG_KEY cfg,
                          ITS_USHORT scic,
                          ITS_USHORT count,
                          ITS_OCTET cicRule)
{
    int i = 0;
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat =  NULL;
    const char *className = 0;
    ITS_Class feature;
    ITS_CTXT *current_vcic = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    ISUP_PCIC startPcic;
    ISUP_CKGP_INFO ckgp_info;
    ITS_USHORT cic_index = 0;
    ITS_USHORT gpid = 0;
    ITS_USHORT numCics = 0;

    if ((scic + count) > ISUP_ITU_MAX_CICS_IN_DEST )
    {
        return ITS_EINVALIDARGS;
    }

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    for(i = 0; i < count; ++i)
    {
        if (ISUP_IsCicUsable(config_stat, (ITS_USHORT)(scic+i)))
        {
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            return ITS_EINVCIC;
        }
    }

    className = ISUP_VariantToString(config_stat->isup_var_type);
    feature = ITS_FindFeature(className);
    memset(&startPcic, 0, sizeof(startPcic));

    ISUP_PCICFromParts(&startPcic, cfg.opc, cfg.dpc, cfg.sio, scic);

    /* Get current Vcic from the Hash Table */
    current_vcic = ISUP_FindVcic();

    ISUP_AllocCics(*current_vcic,
                   startPcic, count, cicRule);
    *current_vcic += count;

    ISUP_ReleaseVcic(current_vcic);

    for(i = 0; i < count ; ++i)
    {
        ITS_BOOLEAN exists;
        ITS_USHORT acic = (ITS_USHORT)(scic + i);
        int j = 0;

        VAR_GetCkgpFromCIC(feature, acic,
                           &cic_index, &gpid, &numCics);
        ISUP_InitCkgp(&ckgp_info, gpid);

        if ((exists = ISUP_CkgpExists(config_stat, gpid)))
        {
            ISUP_FindCkgpInfo(config_stat, gpid, &ckgp_info);
        }

        for (j = 0; (j < numCics) && (i < count); ++j)
        {
            ISUP_AddUsableCic(config_stat, &ckgp_info,
                          cic_index, cicRule);
            cic_index++;
            i++;
        }

        --i;

        if (exists)
        {
            ISUP_UpdateCkgpInfo(config_stat, gpid , &ckgp_info);
        }
        else
        {
            ISUP_InsertCkgpInfo(config_stat, &ckgp_info);
        }
    }


    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_DelCicsCfg_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT scic, ITS_USHORT count)
{
    int  i = 0;
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = NULL;

    ISUP_PCIC startPcic;
    ISUP_CKGP_INFO ckgp_info;
    ITS_USHORT cic_index = 0;
    ITS_USHORT gpid = 0;
    const char *className = 0;
    ITS_Class feature;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    /* First look for config info for this opc-dpc */
    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (config_stat == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    memset(&startPcic, 0, sizeof(startPcic));
    className = ISUP_VariantToString(config_stat->isup_var_type);
    feature = ITS_FindFeature(className);

    for (i = 0; i < count; ++i)
    {
        ISUP_CIC_INFO *cic_info = NULL;
        if (!ISUP_IsCicUsable(config_stat,(ITS_USHORT)(scic + i)))
        {
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            return ITS_EINVCIC;
        }

        ISUP_PCICFromParts(&startPcic, cfg.opc, cfg.dpc, cfg.sio,
                              (ITS_USHORT)((scic + i)));

        cic_info = ISUP_FindPcic(startPcic, isdsmlocal);
        if (cic_info != NULL)
        {
            if ((ISUP_CIC_STATE_GET_DC(cic_info->cic_state) != CKTS_IDLE_CTK))
            {
                ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
                ISUP_ReleaseCic(cic_info, isdsmlocal);
                return ITS_ECICBUSY;
            } 
            ISUP_ReleaseCic(cic_info, isdsmlocal);
        }
        else
        {
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            return ITS_ENOTCONFIG;
        }
    }

    for (i = 0; i < count; ++i)
    {
        ISUP_PCICFromParts(&startPcic,
           MTP3_RL_GET_OPC_VALUE(config_stat->opc_dpc_ni.label),
           MTP3_RL_GET_DPC_VALUE(config_stat->opc_dpc_ni.label),
           MTP3_HDR_GET_SIO(config_stat->opc_dpc_ni), (ITS_USHORT)(scic + i));

        VAR_GetCkgpFromCIC(feature, (ITS_USHORT)(scic + i),
                           &cic_index,&gpid,NULL);

        ISUP_FindCkgpInfo(config_stat, gpid, &ckgp_info);

        ISUP_DelUsableCic(config_stat, &ckgp_info, cic_index);

        ISUP_UpdateCkgpInfo(config_stat, gpid , &ckgp_info);

        if (ISUP_DeleteCic(startPcic) != ITS_SUCCESS)
        {
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            return !ITS_SUCCESS;
        }

    }

    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_GetAllCicsCfg_CCITT(ISUP_CFG_KEY cfg,
                         ISUP_CFG_CKGP_INFO** ckgps,
                         int* noEnt)
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_CKGP_INFO  ckpg;
    ITS_UINT count;
    ISUP_CKGP_LIST *ckgp_list;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));

    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    ckgp_list = ISUP_FindCkgpList(opc_dpc_ni, isdsmlocal);
    if(ckgp_list == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    *noEnt = 0;
    *ckgps = NULL;

    for (count = 0; count < ISUP_MAX_CKGPS; ++count)
    {
        if (ckgp_list->ckgp_info[count].ckgp_id == ISUP_INV_CKGP_ID)
        {
            continue;
        }

        (*noEnt)++;
        *ckgps = (ISUP_CFG_CKGP_INFO *)realloc(*ckgps,
                                   (*noEnt) * sizeof(ISUP_CFG_CKGP_INFO));
        memcpy(&ckpg, &ckgp_list->ckgp_info[count], sizeof(ISUP_CKGP_INFO));
        ((*ckgps)[(*noEnt) - 1]).ckgp_id =  ckpg.ckgp_id;
        memcpy(((*ckgps)[(*noEnt) - 1]).usable_cics, &ckpg.usable_cics[0],
               sizeof(ITS_UINT));
        memcpy(((*ckgps)[(*noEnt) - 1]).contl, &ckpg.ckgp_control[0],
               ISUP_ITU_MAX_CICS_IN_GP*sizeof(ITS_OCTET));
    }
    return ISUP_ReleaseCkgpList(ckgp_list, isdsmlocal);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   DSM Alloc problem related changes.
 *                           #496          
 ****************************************************************************/
int
ISUP_GetCicStateInfo_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic,
                                        ITS_OCTET* cicState)
{
    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    /* Convert cic, opc, dpc to pcic */
    ISUP_PCICFromParts( &pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    *cicState = cic_rec->cic_state;

    ISUP_ReleasePcic(cic_rec, pcic);

    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_SetCicStateInfo_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET state)
{
    ISUP_PCIC pcic;
    ISUP_CIC_INFO * cic_rec =0;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    cic_rec->cic_state = state;

    ISUP_ReleaseCic(cic_rec, isdsmlocal);
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_GetCicPegs_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic,
                      ISUP_CFG_PEGS *cicPeg)
{
    int i =0;
    ISUP_CIC_INFO* cic_rec;
    ISUP_PCIC pcic;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    /* Get cic_rec using the pcic as key */
    cic_rec = ISUP_FindPcic( pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        cicPeg[i].pegId  =  i;
        cicPeg[i].pegVal  = cic_rec->pegs[i];
        memcpy(cicPeg[i].pegDesc, ISUP_CIC_Peg_Desc[i], strlen(ISUP_CIC_Peg_Desc[i]));
    }
    ISUP_ReleaseCic(cic_rec, isdsmlocal);
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      To Unreserve the particular CIC , previously reserverd for use in call
 *      or other operation.
 *
 *  Input Parameters:
 *      cic - The CIC to be Unreserved.
 *      opc - The Originating Point Code (the node on which this ISUP stack
 *            is running) for which this cic is configured.
 *      dpc - The Destination Point Code (the remote node) for which this cic
 *            is configured.
 *      h   - The handle.
 *      sio - The SIO value
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Return Value:
 *      On Success - ITS_SUCCESS is returned.
 *      On Failure - Respective Failure value is returned.
 *
 *  Notes:
 *
 ****************************************************************************/
int
INTELLINET_UnReserveCIC_CCITT(ITS_HANDLE h, ITS_OCTET sio, ITS_UINT opc,
                        ITS_UINT dpc, ITS_USHORT cic)
{
    ISUP_PCIC pcic;
    ISUP_CIC_INFO *cic_rec = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    /* Convert cic, opc, dpc to pcic */
    ISUP_PCICFromParts(&pcic, opc, dpc, sio, cic);

    /* Get cic_rec */
    cic_rec = ISUP_FindPcic(pcic, isdsmlocal);

    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    /* FIXME: Some checks */

    cic_rec->resrv_ind = ITS_FALSE;

    return (ISUP_ReleaseCic(cic_rec, isdsmlocal));
}

/* From its-itu-isup.c */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Handle MTP3 management indications.
 *
 *  Input Parameters:
 *      object
 *      userData
 *      callData
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
HandleMTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT* ev = (ITS_EVENT *)callData;
    ITS_EVENT tmp;

    ITS_EVENT_INIT(&tmp, ev->src, ev->len);
    memcpy(tmp.data, ev->data, ev->len);

    if (TRANSPORT_PutEvent(ITS_ISUP_SRC, ev) != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&tmp);
    }
    else
    {
        *ev = tmp;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called for LOcal Automatic Congestion Control.
 *
 *  Input Parameters:
 *      ITS_EVENT.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      int - Level of Congestion.
 *
 *  Notes:
 *      None.
 *
 *  See Also:
 ****************************************************************************/
int 
CheckLocalCongestion(ITS_EVENT *event)
{
    ITS_UINT lvl = 0;
    ISUP_CONGESTION_ENTRY localcong_ind;
    static ITS_UINT previous_level = 0;
    ITS_UINT current_level = 0;

    /* Get the ISUP Transport Queue Length */
    lvl = Getlocalconglevel(__ISUP_CCITT_RcvQueue);

    /* Set Current Level of Congestion */
    if (lvl < CCITT_ISUP_conglevel1)
    {
        current_level = 0;
    }
    else if (lvl >= CCITT_ISUP_conglevel1 && lvl < CCITT_ISUP_conglevel2)
    {
        current_level = CCITT_ISUP_conglevel1;
    }
    else if (lvl >= CCITT_ISUP_conglevel2)
    {
        current_level = CCITT_ISUP_conglevel2;
    }

    /* Check If we need to Report Congestion */
    if (!current_level && !previous_level)
    {
        /* No Previous and current congestion */
        return current_level;
    }
    else if (current_level == previous_level)
    {
        /* No Change in Cong Level */
        return current_level;
    }
    else if (!current_level &&  previous_level)
    {
        /* Congestion removed, report */
        localcong_ind.congId = ITS_ISUP_LOC_NOCONG_IND;
        CCITT_ISUP_conglevel1Found = ITS_FALSE;
        CCITT_ISUP_conglevel2Found = ITS_FALSE;
        previous_level = 0;
        ISUP_DEBUG(("\n Local Congestion Ceased !!\n"));
        /* FIXME - Generate an Alarm */
    }

    /* Congestion level is either changed (up/down) or reported
     * for the first time. Report to Application
     */
    else if (current_level == CCITT_ISUP_conglevel1 )
    {
        ISUP_DEBUG(("\n Local Congestion of LEVEL 1 detected \n"));
        localcong_ind.congId = ITS_ISUP_LOC_CONGLEVEL1_IND;
        CCITT_ISUP_conglevel1Found = ITS_TRUE;
        CCITT_ISUP_conglevel2Found = ITS_FALSE;
        previous_level = CCITT_ISUP_conglevel1;
        /* FIXME - Generate an Alarm */
    }
    else if (current_level == CCITT_ISUP_conglevel2)
    {
        ISUP_DEBUG(("\n Local Congestion of LEVEL 2 detected \n"));
        localcong_ind.congId = ITS_ISUP_LOC_CONGLEVEL2_IND;
        CCITT_ISUP_conglevel1Found = ITS_FALSE;
        CCITT_ISUP_conglevel2Found = ITS_TRUE;
        previous_level = CCITT_ISUP_conglevel2;
        /* FIXME - Generate an Alarm */
    }
    else
    {
        /*just to be safe*/
        return current_level;
    }

    /* Fill in Indication data to be sent to app. */
    localcong_ind.sio = 0;
    localcong_ind.opc = 0;
    localcong_ind.dpc = 0;

    /* Send a congestion level indication to the application */
    SPRC_SendLocCongIndicToApp_CCITT(ITS_ISUP_INV_VCIC, &localcong_ind);

    return previous_level;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method initializes the ISUP subsystem for use.
 *
 *  Input Parameters:
 *      handle - the ss7 transport handle.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the subsystem is successfully initialized, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
IISUP_Initialize_CCITT(ITS_SS7_HANDLE handle)
{
    int i, j, ret;
    ITS_Class dbClass;
    RESFILE_Manager *res;
    const char *section;
    char val[ITS_PATH_MAX << 2];

    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    if ((__ISUP_CCITT_RcvQueue = TQUEUETRAN_CreateTransport("ITU-ISUP",
                                                            ITS_ISUP_SRC,
                                                            ITS_ISUP))
        == NULL)
    {
        started = ITS_FALSE;

        return (ITS_ENOTRANSPORT);
    }

    res = TRANSPORT_RES(__ISUP_CCITT_RcvQueue);
    section = TRANSPORT_NAME(__ISUP_CCITT_RcvQueue);

    ret = ISUP_Init_CCITT(res, section);
    if (ret != ITS_SUCCESS)
    {
        TQUEUETRAN_DeleteTransport(__ISUP_CCITT_RcvQueue);

        return (ret);
    }

    if (res)
    {
        /* get the number of threads */
        if (RESFILE_GetKeyValueOf(res, section, NUM_THREADS_STRING,
                                  val, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            numThreads = RESFILE_ParseNum(val);
            if (numThreads < 1)
            {
                numThreads = 1;
            }
        }
    }

    if ((isupThread = (ITS_THREAD *)malloc(numThreads *
                                           sizeof(ITS_THREAD))) == NULL)
    {
        ISUP_CRITICAL(("ISUP_Init: Couldn't create thread array.\n"));

        ISUP_Term_CCITT();

        TQUEUETRAN_DeleteTransport(__ISUP_CCITT_RcvQueue);

        started = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    for (i = 0; i < numThreads; i++)
    {
        if (THREAD_CreateThread(&isupThread[i], 0, CCITT_ISUPThread,
                                NULL, ITS_TRUE) != ITS_SUCCESS)
        {
            ISUP_CRITICAL(("ISUP_Init: Couldn't create ISUP thread.\n"));

            /* ISUP failed to Intialize -  couldn't create thread */
            ISUP_Alarm_CCITT(3401, __FILE__, __LINE__, NULL);

            for (j = 0; j < i; j++)
            {
                THREAD_KillThread(&isupThread[j]);

                THREAD_DeleteThread(&isupThread[j]);
            }

            free(isupThread);

            ISUP_Term_CCITT();

            TQUEUETRAN_DeleteTransport(__ISUP_CCITT_RcvQueue);

            started = ITS_FALSE;

            return (ITS_EBADTHREAD);
        }
    }

    CALLBACK_AddCallback(MTP3_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    /* INFORMATIONAL - ISUP Intialized Successfully */
    ISUP_Alarm_CCITT(3402, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_AddDoCommand(ISUP_Console_CCITT);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function terminates the ISUP subsystem.  Well behaved
 *      applications should call this function before exiting.
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
 *      If the subsystem is successfully terminated, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 processing error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
IISUP_Terminate_CCITT(ITS_SS7_HANDLE handle)
{
    ITS_EVENT ev;
    void *status;
    int i;
    ITS_Class dbClass;

    if (!started || stopped)
    {
        return;
    }

    stopped = ITS_TRUE;

    ISUP_CRITICAL(("ISUP_Terminate_CCITT.\n"));

    /* ISUP Terminating */
    ISUP_Alarm_CCITT(3403, __FILE__, __LINE__, NULL);

    if ((dbClass = ITS_FindFeature(DBC_CLASS_NAME)) != NULL)
    {
        DBC_RemDoCommand(ISUP_Console_CCITT);
    }

    CALLBACK_RemCallback(MTP3_ManagementCallbacks, HandleMTP3Mgmt, NULL);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, 0);

    for (i = 0; i < numThreads; i++)
    {
        TRANSPORT_PutEvent(ITS_ISUP_SRC, &ev);
    }

    for (i = 0; i < numThreads; i++)
    {
        THREAD_WaitForThread(&isupThread[i], &status);

        THREAD_DeleteThread(&isupThread[i]);
    }

    free(isupThread);

    assert(__ISUP_CCITT_RcvQueue != NULL);

    TQUEUETRAN_DeleteTransport(__ISUP_CCITT_RcvQueue);

    ISUP_Term_CCITT();
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the entry point for the ITU ISUP thread.
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
 *
 *  Notes:
 *      This method should be considered an undocumented internal
 *      ISUP function.
 *
 *  See Also:
 ****************************************************************************/

#undef PROFILEME
/*#define PROFILEME */

#if defined(PROFILEME)
#include <sys/time.h>
#include <sys/timeb.h>
#endif

THREAD_RET_TYPE
CCITT_ISUPThread(void *arg)
{
#if defined(PROFILEME)
struct timeb st;
struct timeb en;
#endif

    ITS_EVENT isupEvent;
    ITS_BOOLEAN cont;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    MTP3_EnableUserPart(MTP3_SIO_ISUP, ITS_ISUP_SRC);

    memset(&isupEvent, 0, sizeof(ITS_EVENT));

    /* 
     * Before waiting for ISUP events, we must set the context for the
     * Variant in used (such as: Message and Parameter Sets supported).
     */

    cont = ITS_TRUE;

    TRANSPORT_IS_ACTIVE(__ISUP_CCITT_RcvQueue) = ITS_TRUE;

    while (cont &&
           TRANSPORT_CLASS_GET_NEXT_EVENT(ITS_OBJ_CLASS(__ISUP_CCITT_RcvQueue))
                                                        (__ISUP_CCITT_RcvQueue,
                                                         &isupEvent)
           == ITS_SUCCESS)
    {
        if (TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT))
        {
            if ((isupEvent.src != ITS_GCS_EVENT_FROM_STACK) &&
                (isupEvent.src != ITS_GCS_EVENT_FROM_APPL) &&
                (isupEvent.src != ITS_ISUP_SRC) &&
                (isupEvent.src != ITS_TIMER_SRC))
            {
                ITS_INT output = 0;
                if(TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      0))
                {
                    output += 1;
                }
                if(TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      1))
                {
                    output += 2;
                }
                CTF_TraceEvent(isupEvent.src, ITS_ISUP_CCITT_SRC,
                    output, &isupEvent);
            }
        }

        if (DSM_MulticastStackEventToFtGroupMembers(
               DSM_IsupFtGroupId,
               isupEvent,
               (isupEvent.src == ITS_MTP3_SRC) ?
                     ITS_GCS_EVENT_FROM_STACK  :
                     ITS_GCS_EVENT_FROM_APPL,
               ITS_ISUP_CCITT_SRC) == ITS_SUCCESS )
        {
            continue;
        }

        switch (isupEvent.src)
        {
        case ITS_GCS_EVENT_FROM_STACK:
        case ITS_MTP3_SRC:
            ISUP_DEBUG(("ISUP_Main: process ISUP event.\n"));
#if defined(PROFILEME)
if(ftime(&st) < 0)
perror("HandleREL:ftime()"), exit(1);
#endif

            __ISUP_HandleMsg_CCITT(&isupEvent, ISUP_SRC_L3_ITU);

#if defined(PROFILEME)
if(ftime(&en) < 0)
perror("ISUP Thread:ftime()"), exit(1);

printf("For processing L3::Time in ISUP Thread = %d\n",
(((en.time*1000)+(en.millitm) ) - ( (st.time*1000)+(st.millitm))));
#endif

            break;

        case ITS_ISUP_SRC:
            ISUP_CRITICAL(("ISUP_Main: termination event.\n"));

            TRANSPORT_IS_ACTIVE(__ISUP_CCITT_RcvQueue) = ITS_FALSE;

            cont = ITS_FALSE;
            break;

        case ITS_TIMER_SRC:
            ISUP_DEBUG(("ISUP_Main: process TIMER event.\n"));
            __ISUP_HandleTimeout_CCITT(&isupEvent);

            /* FIXME */
            break;

        case ITS_GCS_EVENT_FROM_APPL:
        default:
            ISUP_DEBUG(("ISUP_Main: process APP event.\n"));

           if (redunClass != NULL)
           {
               if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
               {
                   ISUP_ERROR(("Msg received from application in backup"
                               "State, ignoring \n"));
                   break;
               }
           }


#if defined(PROFILEME)
if(ftime(&st) < 0)
perror("HandleREL:ftime()"), exit(1);
#endif

            __ISUP_HandleMsg_CCITT(&isupEvent, ISUP_SRC_APP_ITU);

#if defined(PROFILEME)
if(ftime(&en) < 0)
perror("ISUPThread:ftime()"), exit(1);

printf("For processing App Request::Time in ISUP Thread = %d\n",
(((en.time*1000)+(en.millitm) ) - ( (st.time*1000)+(st.millitm))));
#endif

            /* FIXME */
            break;
        }
    }

    TRANSPORT_IS_ACTIVE(__ISUP_CCITT_RcvQueue) = ITS_FALSE;

    /* ISUP aborting */
    ISUP_Alarm_CCITT(3404, __FILE__, __LINE__, NULL);

    MTP3_DisableUserPart(MTP3_SIO_ISUP);

    THREAD_NORMAL_EXIT;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Start parsing ISUP ACC information in XML files.
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
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_ParseStart(ENGINE_ParserExtension ext, const char *el, const char **attr)
{
    XML_ParseData *pd;
    ISUP_CONG_CONTEXT *ctxt;

    pd = calloc(1, sizeof(XML_ParseData));
    ITS_C_ASSERT(pd != NULL);
    pd->next = ENGINE_PE_USER_DATA(ext);
    ENGINE_PE_USER_DATA(ext) = pd;

    ctxt = (ISUP_CONG_CONTEXT *)&pd->ctxt;

    while (*attr)
    {
        if (strcmp(*attr, "sectionName") == 0)
        {
            attr++;

            pd->sectionName = strdup(*attr);
            ITS_C_ASSERT(pd->sectionName != NULL);

            attr++;
        }
        if (strcmp(*attr, "congLevel1") == 0)
        {
            attr++;

            ctxt->congLevel1 = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "congLevel2") == 0)
        {
            attr++;

            ctxt->congLevel2 = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "localcongTimer") == 0)
        {
            attr++;

            ctxt->localcongTimer = RESFILE_ParseNum(*attr);

            attr++;
        }
        else if (strcmp(*attr, "repeatrsctimerVal") == 0)
        {
            attr++;

            ctxt->repeatrsctimerVal = RESFILE_ParseNum(*attr);

            attr++;
        }
        else
        {
            attr += 2;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Term parsing ISUP ACC information in XML files.
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
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_ParseEnd(ENGINE_ParserExtension ext, const char *el)
{
    /* don't care */
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Convert ISUP ACC information in XML files.
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
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_ConvertParserData(RESFILE_Manager *appRes, ENGINE_ParserExtension ext)
{
    int ret;
    char tmp[ITS_PATH_MAX];
    XML_ParseData *pd = (XML_ParseData *)ENGINE_PE_USER_DATA(ext);
    ISUP_CONG_CONTEXT *ctxt;


    while (pd != NULL)
    {
        ctxt = (ISUP_CONG_CONTEXT *)&pd->ctxt;

        /* convert the extension data to resources */
        sprintf(tmp, "%d", ctxt->congLevel1);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "congLevel1", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->congLevel2);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "congLevel2", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->localcongTimer);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "localcongTimer", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        sprintf(tmp, "%d", ctxt->repeatrsctimerVal);
        ret = RESFILE_AddKeyValue(appRes, pd->sectionName,
                                  "repeatrsctimerVal", tmp);
        ITS_C_ASSERT(ret == ITS_SUCCESS);

        pd = pd->next;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Diff ISUP ACC information in XML files.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_Diff(RESFILE_Manager *appRes, ENGINE_ParserExtension ext1,
                                   ENGINE_ParserExtension ext2)
{
    /* don't care */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Get Local ISUP Congestion Level by measuring the ISUP Q length.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
static ITS_UINT
Getlocalconglevel(TQUEUETRAN_Manager *tq)
{
    return(LIST_COUNT(TQUEUETRAN_EMLIST(tq)));
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
int
ISUP_SetCong_CCITT(ITS_UINT congLev, ITS_UINT congVal)
{
    if (congLev == 1)
    {
       /* set the Congestion Level1 to the congVal */
       CCITT_ISUP_conglevel1 = congVal;
    }
    else
    {
       /* set the Congestion Level2 to the congVal */
       CCITT_ISUP_conglevel2 = congVal;
    }
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
ISUP_PrintCong_CCITT(ITS_UINT congLev, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];

    if (congLev == 1)
    {
       /* Print the Congestion Level 1 Value */

       sprintf(buf,"\nCongLevel1:    %d\n",CCITT_ISUP_conglevel1);
       DBC_AppendText(dbc, buf);
    }
    else
    {
       /* Print the Congestion Level 2 Value */
       sprintf(buf,"\nCongLevel2:    %d\n",CCITT_ISUP_conglevel2);
       DBC_AppendText(dbc, buf);
    }
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintAllCicsCfg(ISUP_CFG_CKGP_INFO *ckgp,int noEnt, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];
    ITS_UINT count;
    int cicsInckg = 32;
    int j =0;
    ITS_USHORT cic = 0, startcic = 0;
    ITS_OCTET cicrule = ISUP_CKGP_CTRL_DEF;
    ITS_BOOLEAN cics_present = ITS_FALSE;
    ITS_BOOLEAN startcicFound = ITS_FALSE;

    /* how to find the number of CICs configured, what if
     * there is no CIC configured, it's good to print, the
     * following statement, Will it ever reach here
     */
    if (noEnt == 0)
    {
        sprintf(buf,"\nCics Provisioned: NONE\n");
        DBC_AppendText(dbc, buf);
        return;
    }

    for (count = 0; count < (ITS_UINT)noEnt; ++count)
    {
        if (ckgp[count].usable_cics[0] == 0)
        {
            continue;
        }

        sprintf(buf,"\nCircuit group id = %d ", ckgp[count].ckgp_id);
        DBC_AppendText(dbc, buf);

        sprintf(buf,"\nProvisioned cicRange        cicRule\n");
        DBC_AppendText(dbc, buf);

        startcicFound = ITS_FALSE;

        for (j = 0; j < cicsInckg; j++)
        {
            if ((ckgp[count].usable_cics[0] & (0x00000001 << j)) != 0)
            {
                cics_present = ITS_TRUE;
                cic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);

                if (!startcicFound)
                {
                    startcic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);
                    startcicFound = ITS_TRUE;
                }
                else if (cicrule != ckgp[count].contl[j])
                {
                     sprintf(buf,"    %5d-%d %20s \n",
                             startcic, cic - 1,
                             ISUP_CkgpCtrlToString(cicrule));
                     DBC_AppendText(dbc, buf);
                     startcic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);
                }
            }
            else
            {
                if (startcicFound)
                {
                     sprintf(buf,"    %5d-%d %20s \n",
                             startcic, cic,
                             ISUP_CkgpCtrlToString(cicrule));
                     DBC_AppendText(dbc, buf);
                }
                startcicFound = ITS_FALSE;
            }

            cicrule = ckgp[count].contl[j];
        }

        if (startcicFound)
        {
            sprintf(buf,"    %5d-%d %20s \n",
                    startcic, cic, ISUP_CkgpCtrlToString(cicrule));
            DBC_AppendText(dbc, buf);
        }
    }
}


 /*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintDestPegs(ISUP_CFG_PEGS *destPeg, DBC_Server *dbc)
{
    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                       Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                       --------\n");
    DBC_AppendText(dbc, buf);
    
    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
        value = destPeg[i].pegVal;
        switch (i)
        {
        case  PEG_ISUP_DEST_REM_AVAIL :
            sprintf(buf,"\n%s %15d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case  PEG_ISUP_DEST_REM_UNAVAIL :
            sprintf(buf,"%s %13d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case   PEG_ISUP_DEST_REM_CONGES :
            sprintf(buf,"%s %14d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case   PEG_ISUP_DEST_REM_CONGES_SEIZED :
                  sprintf(buf,"%s %7d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case  PEG_ISUP_DEST_PAUSE  :
            sprintf(buf,"%s %19d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_DEST_RESUME :
            sprintf(buf,"%s %18d\n",ISUP_Dest_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

          }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintDestCfgInfo(ISUP_CFG_DEST_INFO *config_info, DBC_Server *db_c)
{
    char buf[ITS_PATH_MAX];
    int ret =0;
    ISUP_CFG_CKGP_INFO * info;
    int noEnt;

    sprintf(buf,"\nVARIANT TYPE  =  %s \n",
            ISUP_VariantToString(config_info->variant));
    DBC_AppendText(db_c, buf);

    sprintf(buf,"OPC = %d \n", config_info->cfg.opc);
    DBC_AppendText(db_c, buf);
    sprintf(buf,"DPC = %d \n", config_info->cfg.dpc);
    DBC_AppendText(db_c, buf);
    sprintf(buf,"SIO = %d \n", config_info->cfg.sio);
    DBC_AppendText(db_c, buf);

    ret = ISUP_GetAllCicsCfg_CCITT(config_info->cfg, &info, &noEnt);
    if (ret == ITS_SUCCESS)
    {
        DBCPrintAllCicsCfg(info, noEnt, db_c);
        free(info);
    }

    switch(config_info->congesInd)
    {
    case ISUP_CFG_RMTCONGES_LEVEL1:

        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL1");
        break;
    case ISUP_CFG_RMTCONGES_LEVEL2:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL2");
        break;
    case ISUP_CFG_RMTCONGES_LEVEL3:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_LEVEL3");
        break;
    case ISUP_CFG_RMTCONGES_OFF:
        sprintf(buf,"\nRemote ISUP_CONGES Indicator:  %s\n","ISUP_RMT_CONGES_OFF");
        break;
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->remote_isup_stat)
    {
    case ISUP_CFG_REMOTE_AVAILABLE:
        sprintf(buf,"\nRemote ISUP Status:   %s\n",
                "REMOTE ISUP AVAILABLE");
        break;

    case ISUP_CFG_REMOTE_UNAVAILABLE:
        sprintf(buf,"\nRemote ISUP Status:   %s\n",
                   "REMOTE ISUP UNAVAILABLE");
        break;

    case ISUP_CFG_REMOTE_UNEQUIPPED:
        sprintf(buf,"\nRemote ISUP Status:   %s\n",
                   "REMOTE ISUP UNEQUIPPED");
        break;
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->dest_reachable)
    {
    case ISUP_CFG_DEST_UNREACHABLE:
        sprintf(buf,"\nDestination Status:   %s\n","DESTINATION UNREACHABLE");
        break;

    case ISUP_CFG_DEST_REACHABLE:
        sprintf(buf,"\nDestination Status:   %s\n","DESTINATION REACHABLE");
        break;
    }
    DBC_AppendText(db_c, buf);

    switch(config_info->exchange_type)
    {
    case ISUP_XCHANGE_TYPE_A:
        sprintf(buf, "\nLocal Exchange Type:   %s\n", "TYPE_A");
        break;

    case ISUP_XCHANGE_TYPE_B:
        sprintf(buf, "\nLocal Exchange Type:   %s\n", "TYPE_B");
        break;

    case ISUP_XCHANGE_TYPE_INV:
        sprintf(buf, "\nLocal Exchange Type:   %s\n", "TYPE_INV");
        break;
    }
    DBC_AppendText(db_c, buf);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
DBCPrintCicState(ISUP_CIC_INFO *cic_rec, DBC_Server *dbc)
{
    char buf[ITS_PATH_MAX];

    sprintf(buf, "\n======================================================================\n");
    DBC_AppendText(dbc, buf);

    sprintf(buf, "CIC States for cic %d:\n",cic_rec->pcic.cic);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "----------------------\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\ncic number = %d\n", cic_rec->pcic.cic);
    DBC_AppendText(dbc, buf);

    switch(cic_rec->cic_state & 0x0cU) /* check bits DC */
    {
        case 0x00: /* DC is 00 */
            /* Now check for BA */
            switch(cic_rec->cic_state & 0x03)
            {
                case 0x00:
                    sprintf(buf, "cic Maintenance blocking state: TRANSIENT\n");
                    DBC_AppendText(dbc, buf);
                    break;

                case 0x11:
                    sprintf(buf, "cic Maintenance blocking state: UNEQUIPPED\n");
                    DBC_AppendText(dbc, buf);
                    break;

                default:
                    sprintf(buf, "Spare!\n");
                    DBC_AppendText(dbc, buf);
                    break;
            }
        goto printstates;
    }

    /* Bits DC not equal to 00 */
    switch(cic_rec->cic_state & 0x03U) /* Bits BA */
    {
        case 0x00:
            sprintf(buf, "cic Maintenance blocking state: UNBLOCKED (ACTIVE)\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x01:
            sprintf(buf, "cic Maintenance blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x02:
            sprintf(buf, "cic Maintenance blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x03:
            sprintf(buf, "cic Maintenance blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "cic Maintenance state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            break;
    }

    switch(cic_rec->cic_state & 0x0cU) /* Bits DC */
    {
        case 0x04:
            sprintf(buf, "cic Call processing state: CIRCUIT INCOMING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x08:
            sprintf(buf, "cic Call processing state: CIRCUIT OUTGOING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x0c:
            sprintf(buf, "cic Call processing state: IDLE\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "cic Call processing state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            break;
    }

    switch(cic_rec->cic_state & 0x30U)
    {
        case 0x00:
            sprintf(buf, "cic Hardware blocking state: UNBLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x10:
            sprintf(buf, "cic Hardware blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x20:
            sprintf(buf, "cic Hardware blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x30:
            sprintf(buf, "cic Hardware blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "cic Hardware blocking state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            break;
    }



printstates:
    sprintf(buf, "\n");;
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CPC  FSM State: %s\n", CPCFsmState[cic_rec->fsm_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "BLS  FSM State: %s\n", BLSFsmState[cic_rec->bls_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "BLR  FSM State: %s\n", BLRFsmState[cic_rec->blr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "MGBS FSM State: %s\n", MGBSFsmState[cic_rec->mgbs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "MGBR FSM State: %s\n", MGBRFsmState[cic_rec->mgbr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "HLB  FSM State: %s\n", HLBFsmState[cic_rec->hlb_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "HRB  FSM State: %s\n", HRBFsmState[cic_rec->hrb_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "HGBS FSM State: %s\n", HGBSFsmState[cic_rec->hgbs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "HGBR FSM State: %s\n", HGBRFsmState[cic_rec->hgbr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CRS  FSM State: %s\n", CRSFsmState[cic_rec->crs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CRR  FSM State: %s\n", CRRFsmState[cic_rec->crr_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CGRS FSM State: %s\n", CGRSFsmState[cic_rec->cgrs_state]);
    DBC_AppendText(dbc, buf);
    sprintf(buf, "CGRR FSM State: %s\n", CGRRFsmState[cic_rec->cgrr_state]);
    DBC_AppendText(dbc, buf);

    sprintf(buf, "\n======================================================================\n");
    DBC_AppendText(dbc, buf);
    sprintf(buf, "\n");;
    DBC_AppendText(dbc, buf);

    /* release cic_rec */
    ISUP_ReleaseCic(cic_rec, ITS_TRUE);

    return 0;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintTimerCfg(ISUP_CFG_TMR_INFO *cfg,int *tId, DBC_Server *dbc)
{
    ITS_OCTET i =0;
    ISUP_CFG_TMR_INFO tmr_info;
    const char *tmr_hndl_str;
    const char *tmr_id_str;
    char buf[ITS_PATH_MAX];

    if (tId == NULL)
    {
        sprintf(buf,"\nTimer   Value    Handled By  \n\n");

        DBC_AppendText(dbc,buf);

        sprintf(buf,"        (sec)   \n\n");
        DBC_AppendText(dbc,buf);

        for (i = 1; i < ITS_ISUP_TIMER_LAST; i++)
        {
            tmr_id_str = ISUP_TimerToString(i);
            ITS_C_ASSERT(tmr_id_str != NULL);

            tmr_info = cfg[i];

            tmr_hndl_str = ISUP_TimerHandlerToString((ISUP_TMR_HNDL)tmr_info.tmr_cfg_hndl_layer);

            ITS_C_ASSERT(tmr_hndl_str != NULL);

            if (tmr_info.tmr_cfg_value != 0)
            {

                sprintf(buf,"%5s%8d%14s \n\n",tmr_id_str,
                                       tmr_info.tmr_cfg_value, tmr_hndl_str);
                DBC_AppendText(dbc,buf);
            }
            else
            {
                /* Don't do anything ?? */
            }
        }
    }
    else
    {
        ISUP_CFG_TMR_INFO tmr_info;

        if (*tId > ISUP_CFG_MAX_TIMERS)
        {
            sprintf(buf, "\n**** Invalid Timer Id *******\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        tmr_info = cfg[*tId];

        if (tmr_info.tmr_cfg_value == 0)
        {
            sprintf(buf,"\nTimer   %s Not Supported/Turned Off.",
                   ISUP_TimerToString((ITS_OCTET)*tId));

        }
        else
        {
            sprintf(buf,"\nTimer:   %s  Value:  %d secs   HandledBy:    %s\n\n",
                   ISUP_TimerToString((ITS_OCTET)*tId),
                   tmr_info.tmr_cfg_value,
                   ISUP_TimerHandlerToString((ISUP_TMR_HNDL)tmr_info.tmr_cfg_hndl_layer));
        }
        DBC_AppendText(dbc, buf);
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintGeneralPegs(DBC_Server *dbc)
{

    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name              Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------              ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
    {
        switch(i)
        {
        case PEG_ISUP_TOT_MSGS_SENT:
            value = PEG_GetPeg(CCITT_ISUP_Pegs, i);
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case PEG_ISUP_TOT_MSGS_RCVD:
            value = PEG_GetPeg(CCITT_ISUP_Pegs, i);
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintGeneralPegType(DBC_Server *dbc)
{

    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name              Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------              ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
    {
        switch(i)
        {
        case PEG_ISUP_TOT_MSGS_SENT:
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case PEG_ISUP_TOT_MSGS_RCVD:
            value = PEG_GetPeg(CCITT_ISUP_Pegs, i);
            sprintf(buf,"%s    %5d\n",ISUP_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
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
 ****************************************************************************/
static void
DBCPrintCicPegs(ISUP_CFG_PEGS *cicPeg, DBC_Server *dbc)
{
    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                       Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                       --------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        value = cicPeg[i].pegVal;
        switch (i)
        {
        case    PEG_ISUP_CIC_NO_ACK_RSC_T17:
            sprintf(buf,"\n%s %13d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_GRA_T23:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_RLC_T5:
            sprintf(buf,"%s %18d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_REL_ABNORMAL:
            sprintf(buf,"%s %15d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGBA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGUA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK :
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK:
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_BLA_T13:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_UBA_T15:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGBA_T19:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGUA_T21:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MSG_FORMAT_ERR:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_MSG_RCVD:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_REL_UNRECOG_INFO:
            sprintf(buf,"%s %11d\n",ISUP_CIC_Peg_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintCicPegsType(DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];

    sprintf(buf,"\n     Peg Name                       Peg id \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                       ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        switch (i)
        {

        case    PEG_ISUP_CIC_NO_ACK_RSC_T17:
            sprintf(buf,"\n%s %13d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_GRA_T23:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_RLC_T5:
            sprintf(buf,"%s %18d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_REL_ABNORMAL:
            sprintf(buf,"%s %15d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGBA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MISSING_ACK_IN_CGUA:
            sprintf(buf,"%s %8d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA:
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],i);
            sprintf(buf,"%s %7d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK:
            sprintf(buf,"%s %4d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK :
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK:
            sprintf(buf,"%s %5d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_BLA_T13:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_UBA_T15:
            sprintf(buf,"%s %17d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGBA_T19:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_NO_CGUA_T21:
            sprintf(buf,"%s %16d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_MSG_FORMAT_ERR:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_UNEXP_MSG_RCVD:
            sprintf(buf,"%s %13d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        case    PEG_ISUP_CIC_REL_UNRECOG_INFO:
            sprintf(buf,"%s %11d\n",ISUP_CIC_Peg_Desc[i],i);
            DBC_AppendText(dbc, buf);
            break;
        }
    }
}

/*.implementation:Static
 ****************************************************************************
 *  Purpose:
 *    None
 *
 *  Input Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
****************************************************************************/
static void
DBCPrintMsgRcvdPegs(ISUP_CFG_PEGS *RcvdPegs, int noEnt, DBC_Server *dbc)
{
    int i =0;
    char buf[ITS_PATH_MAX];
    ITS_UINT value;

    sprintf(buf,"\n     Peg Name                             Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                             ------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < noEnt - 1 ; i++)
    {
        value = RcvdPegs[i].pegVal;
        switch (i)
        {
        case PEG_ISUP_REMOTE_IAM_RCVD:
            sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ACM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_ANM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_REL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RLC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLO_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBL_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_BLA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CPG_RCVD :
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGB_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGBA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CQR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_GRA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGU_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CGUA_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CRG_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CFN_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_COT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CCR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FOT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INF_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_INR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_LPA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_PAM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RSC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_RES_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_SUS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UBA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UCIC_RCVD:
            sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_IDR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_IRS_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FAA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_CON_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FRJ_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FAC_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_FAR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_NRM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_OLM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_SAM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_SGM_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UPA_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_UPT_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

        case PEG_ISUP_REMOTE_USR_RCVD:
            sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
            DBC_AppendText(dbc, buf);
            break;

      case PEG_ISUP_LOP_SENT_TO_REMOTE:
           sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Rcvd_Desc[i],value);
           DBC_AppendText(dbc, buf);
           break;

        }
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static void
DBCPrintMsgSentPegs(ISUP_CFG_PEGS *SentPegs,int noEnt, DBC_Server *dbc)
{
    int i =0;
    ITS_UINT value;
    char buf[ITS_PATH_MAX];
    printf("No of Ent::%d",noEnt);

    sprintf(buf,"\n     Peg Name                             Peg Count \n");
    DBC_AppendText(dbc, buf);
    sprintf(buf,"     --------                             --------\n");
    DBC_AppendText(dbc, buf);

    for (i = 0; i < noEnt -1 ; i++)
    {
        value = SentPegs[i].pegVal;
        switch (i)
        {
            case PEG_ISUP_IAM_SENT_TO_REMOTE:
                sprintf(buf,"\n%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_ACM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_ANM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_REL_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_RLC_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_BLO_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_UBL_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_BLA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CPG_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CGB_SENT_TO_REMOTE :
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CGBA_SENT_TO_REMOTE:
                sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CQM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CQR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_GRS_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_GRA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CGU_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CGUA_SENT_TO_REMOTE:
                sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CRG_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CFN_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_COT_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CCR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_FOT_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_INF_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_INR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_LPA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_PAM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_RSC_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_RES_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_SUS_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_UBA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_UCIC_SENT_TO_REMOTE:
                sprintf(buf,"%s %17d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_IDR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_IRS_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_FAA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_CON_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_FRJ_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_FAC_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_FAR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_NRM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_OLM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_SAM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_SGM_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_UPA_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_UPT_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_USR_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;

            case PEG_ISUP_LOP_SENT_TO_REMOTE:
                sprintf(buf,"%s %18d\n",ISUP_Msg_Pegs_Sent_Desc[i],value);
                DBC_AppendText(dbc, buf);
                break;
        }
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
ISUP_DestIterProc_CCITT(ITS_INT context, ITS_POINTER data, void *in, void *out)
{
    ISUP_OPC_DPC_INFO *config_info;
    ISUP_CFG_DEST_INFO info;
    int i =0;

    ITS_C_ASSERT(data != NULL);
    ITS_C_ASSERT(in != NULL);

    config_info = (ISUP_OPC_DPC_INFO *)data;

    info.cfg.opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    info.cfg.dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
    info.cfg.sio = config_info->opc_dpc_ni.sio;

    info.variant =  config_info->isup_var_type;
    info.congesInd = (ISUP_CFG_CONGES)config_info->isup_rmt_conglev;
    info.dest_reachable = (ISUP_CFG_DEST_STATUS)config_info->dest_stat;
    info.exchange_type = (ISUP_CFG_EXCHANGE_TYPE)
                          config_info->exchange_type;
    info.remote_isup_stat =(ISUP_CFG_REMOTE_ISUP_STATUS) config_info->remote_isup_stat;

    for( i = 0;i < ISUP_CFG_MAX_TIMERS ; ++i)
    {
        info.timer_info[i].tmr_cfg_hndl_layer = (ISUP_CFG_TMR_HNDL)config_info->tmr_hndl_info[i].tmr_hndl_layer;

        info.timer_info[i].tmr_cfg_value = config_info->tmr_hndl_info[i].tmr_value;
    }

    DBCPrintDestCfgInfo(&info, (DBC_Server*) in);
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
ISUP_SendMsgMMLToStack_CCITT(ISUP_PCIC pcic, ITS_OCTET type,
                             ITS_ISUP_IE *ies, int ieCount)
{
    int ret;
    ITS_USHORT len =0;
    int index = 0;
    ISUP_MSG_DESC *msg_desc = NULL;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_EVENT ev;

    ret = ISUP_FindOpcDpc(ISUP_PCIC_TO_OPC_DPC(pcic),&config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }

    /* Get cic_rec using the pcic as key
     * Why do we need it at 1st place, just to
     * see if it is not NULL ?? 
     */
    cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
    if (cic_rec == NULL)
    {
        return ITS_EINVCIC;
    }

    /* CIC record no longer needed. */
    ISUP_ReleaseCic(cic_rec, ITS_TRUE);

    /* Check the Message Type */
    if (!VAR_IsMsgSupported( config_info.isup_var_class, type ))
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_EINVISUPMSGTYPE;
    }

    /* Get MSG_DESC from Variant record */
    msg_desc = VAR_GetMsgDescription( config_info.isup_var_class, type );
    if (msg_desc == NULL)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ITS_ENOTCONFIG;
    }

    ret = ISUP_MessageSanityCheck(type, ies, ieCount, msg_desc);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    memset( (char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_CCITT( data, &len, type, ies, ieCount,
                                 config_info.isup_var_class );
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpc(&config_info);
        return ret;
    }

    ret = ISUP_ReleaseOpcDpc(&config_info);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */

    ITS_EVENT_INIT( (&ev), ISUP_SRC_APP_ITU, (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len) );

    /* Fill in MTP3 Message Type */
    ev.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy( (char *)&ev.data[index], (char *)&pcic.hdr,
             sizeof(MTP3_HEADER) );

    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    ev.data[index++] = (ITS_OCTET)(pcic.cic & 0xFFU);
    ev.data[index++] = (ITS_OCTET)(( pcic.cic >> 8) & 0xFFU);

    /* Fill in the ISUP message type */
    ev.data[index++] = type;

    /* Fill in Encoded ISUP message data */
    memcpy( (char *)&ev.data[index], (char *)data, len );
    ret = TRANSPORT_PutEvent(ITS_ISUP_CCITT_SRC, &ev);
    if (ret != ITS_SUCCESS)
    {
        ITS_EVENT_TERM(&ev);
    }
    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      None. 
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 ****************************************************************************/
static void
ISUP_Console_CCITT(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    ITS_UINT i;
    int ret = 0;

    ITS_C_ASSERT(dbc != NULL);
    if (DBC_Cmd(dbc, "ii_get_gen_cfg", "ISUP Get General Config", "", ""))
    {
        ISUPGeneralCfg *cfg = 0;
        cfg =  ISUP_GetGeneralCfg_CCITT();

        sprintf(buf, "\n*********** ISUP General Config *************\n");
        DBC_AppendText(dbc, buf);

        i = cfg->alarmLevel;

        switch(i)
        {
            case ALARM_LVL_CRIT :
                sprintf(buf, "    Alarm Level = CRITICAL\n");
            break;

            case ALARM_LVL_MAJOR :
                sprintf(buf, "    Alarm Level = MAJOR\n");
            break;

            case ALARM_LVL_MINOR :
                sprintf(buf, "    Alarm Level = MINOR\n");
            break;

            case ALARM_LVL_INFO :
                sprintf(buf, "    Alarm Level = INFO\n");
            break;

            case ALARM_LVL_OFF :
                sprintf(buf, "    Alarm Level = OFF\n");
            break;

            default :
                sprintf(buf, "    Alarm Level Not Set\n");
            break;
        }

        DBC_AppendText(dbc, buf);

        strcpy(buf, "    ISUP Trace -\n");
        DBC_AppendText(dbc, buf);

        if ( cfg->traceOn)
        {
           if (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_DEBUG))
           {
               strcpy(buf, "        Debug     = ");
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_DEBUG,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Debug     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_CRITICAL))
           {
               strcpy(buf, "        Critical  = ");
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_CRITICAL,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Critical  = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_WARNING))
           {
               strcpy(buf, "        Warning   = ");
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      0))
               {
                  strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      1))
               {
                  strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_WARNING,
                                      2))
               {
                    strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Warning   = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_ERROR))
           {
               strcpy(buf, "        Error     = ");
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      0))
               {
                   strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      1))
               {
                   strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_ERROR,
                                      2))
               {
                   strcat(buf, " syslog");
               }
           }
           else
           {
               strcpy(buf, "        Error     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);

           if (TRACE_IsLevelOn(ISUP_CCITT_TraceData,
                                    ISUP_TRACE_EVENT))
           {
               strcpy(buf, "        Event     = ");
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      0))
               {
                    strcat(buf, " stdout");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      1))
               {
                    strcat(buf, " file");
               }
               if (TRACE_IsOutputOn(ISUP_CCITT_TraceData,
                                      ISUP_TRACE_EVENT,
                                      2))
               {
                    strcat(buf, " syslog");
               }  
           }
           else
           {
               strcpy(buf, "        Event     = null");
           }
           strcat(buf, "\n");
           DBC_AppendText(dbc, buf);
       }
       else
       {
           strcpy(buf, "        Debug     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Critical  = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Warning   = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Error     = null\n");
           DBC_AppendText(dbc, buf);
           strcpy(buf, "        Event    = null\n");
           DBC_AppendText(dbc, buf);
       }

       sprintf(buf, "*********** End of ISUP General Config ***********\n");
       DBC_AppendText(dbc, buf);

    }
    else if (DBC_Cmd(dbc, "ii_set_gen_cfg", "ISUP Set General Config",
                      "<alarm level> <Trace Type> <traceOutput> <On/Off>", ""))

    {
        ISUPGeneralCfg cfg;
        char alarmLevel[ITS_PATH_MAX];
        char traceOn[ITS_PATH_MAX];
        char traceType[ITS_PATH_MAX];
        char traceOutput[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, alarmLevel, traceType,
                     traceOutput, traceOn);

        if (ret != 5)
        {

            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_set_gen_cfg <alarmlevel> <tracetype> " 
                         "<trOutput> <On/Off>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(alarmLevel, "CRITICAL") != NULL ||
            strstr(alarmLevel, "critical") != NULL)
        {
            cfg.alarmLevel = ALARM_LVL_CRIT;
        }
        else if (strstr(alarmLevel, "MAJOR") ||
                strstr(alarmLevel, "major") )
        {
            cfg.alarmLevel = ALARM_LVL_MAJOR;
        }
        else if (strstr(alarmLevel, "MINOR") ||
                strstr(alarmLevel, "minor"))
        {
            cfg.alarmLevel = ALARM_LVL_MINOR;
        }
        else if (strstr(alarmLevel, "INFO") ||
                 strstr(alarmLevel, "info"))
        {
            cfg.alarmLevel = ALARM_LVL_INFO;
        }
        else if (strstr(alarmLevel, "OFF") ||
                strstr(alarmLevel, "off") )
        {
            cfg.alarmLevel = ALARM_LVL_OFF;
        }
        else
        {
            sprintf(buf, "Invalid Alarm Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOn, "ON") || strstr(traceOn, "on"))
        {
            cfg.traceOn = ITS_TRUE;
        }
        else if (strstr(traceOn, "OFF") || strstr(traceOn, "off"))
        {
            cfg.traceOn = ITS_FALSE;
        }
        else
        {
            sprintf(buf, "Invalid Trace Level\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceType, "CRITICAL") || strstr(traceType, "critical"))
        {
            strcpy(cfg.traceType, ISUP_CRITICAL_STRING);
        }
        else if (strstr(traceType, "DEBUG") || strstr(traceType, "debug"))
        {
            strcpy(cfg.traceType, ISUP_DEBUG_STRING);
        }
        else if (strstr(traceType, "WARNING") || strstr(traceType, "warning"))
        {
            strcpy(cfg.traceType, ISUP_WARNING_STRING);
        }
        else if (strstr(traceType, "ERROR") || strstr(traceType, "error"))
        {
            strcpy(cfg.traceType, ISUP_ERROR_STRING);
        }
        else if (strstr(traceType, "EVENT") || strstr(traceType, "event"))
        {
            strcpy(cfg.traceType, ISUP_EVENT_STRING);
        }
        else if (strstr(traceType, "ALL") || strstr(traceType, "all"))
        {
            strcpy(cfg.traceType, "all");
        }
        else
        {
            sprintf(buf, "Invalid Trace Type\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if (strstr(traceOutput, "STDOUT") || strstr(traceOutput, "stdout"))
        {
            strcpy(cfg.traceOutput, ISUP_STDOUT_STRING);
        }
        else if (strstr(traceOutput, "FILE") || strstr(traceOutput, "file"))
        {
            strcpy(cfg.traceOutput, ISUP_FILE_STRING);
        }
        else if (strstr(traceOutput, "SYSLOG") || strstr(traceOutput, "syslog"))
        {
            strcpy(cfg.traceOutput, ISUP_SYSLOG_STRING);
        }
        else
        {
            sprintf(buf, "Invalid Trace Output\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ret =  ISUP_SetGeneralCfg_CCITT(&cfg);
        if (ret != ITS_SUCCESS)
        {
            sprintf(buf, "********* ISUP Set Gen Cfg Failed***********\n");
            DBC_AppendText(dbc, buf);
            return;
        }
       sprintf(buf, "\n********* ISUP General Config Set Successful*******\n");
       DBC_AppendText(dbc, buf);
    }
    else if (DBC_Cmd(dbc, "ii_get_dest_info", "ISUP Get Destination Info",
                      "<opc> <dpc> <sio> or  <*>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char astrix[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            if (ret == 2)

            {
                sscanf(cmdLine," %s %s",buf,astrix);
                if (strcmp(astrix,"*") == 0)
                {
                    ISUP_HashTableIterate(ISUP_DestIterProc_CCITT,(void*)dbc,
                                                                  NULL);
                }
                else
                {
                    sprintf(buf, "\n**** Invalid Command Arguments *******\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                       "Usage: ii_get_dest_info <opc> <dpc> <sio> or  <*>\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else
        {
            ISUP_CFG_DEST_INFO dest_info;
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetDestCfgInfo_CCITT(cfg, &dest_info);
            if(ret == ITS_SUCCESS)
            {
                DBCPrintDestCfgInfo(&dest_info, dbc);

            }
            else if(ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_add_dest_info", "ISUP Add Destination Info",
             "<opc> <dpc> <sio> <VariantType> <ExchangeType>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char varName[ITS_PATH_MAX];
        char exchangeType[ITS_PATH_MAX];
        ISUP_CFG_KEY cfg;

        ret = sscanf(cmdLine, "%s %s %s %s %s %s", buf, opc, dpc, sio, varName, 
                     exchangeType);
        if (ret != 6)
        {
            sprintf(buf,"\n*** Add Destination Failed: "
                        "\nUsage: ii_add_dest_info <opc> <dpc> <sio>"
                        " <variant type>  <exchange type>");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_AddDestCfgInfo_CCITT(cfg, varName, exchangeType);
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n *** Added Destination Successfully ***\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOROUTE)
            {
                sprintf(buf,"\n Route Not Found For Destination : "
                              "See help To Add Route First\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINVXCHANGE)
            {
                sprintf(buf,"\n Exchange Type is Invalid: "
                              "See help To see Valid Exchange Types\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOFEATURE)
            {
                sprintf(buf,"\n Variant Feature: %s is Not Loaded: "
                            "Try to add Variant first (ii_add_variant)\n",
                             varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINUSE)
            {
                sprintf(buf,"\nAdd Destination Failed: Destinatoin Already "
                            "Configured\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf,"Add Destination Failed: %s Variant Not Supported", 
                            varName);
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n*** Add Destination Failed: ,See help"
                            "\nUsage: ii_add_dest_info <opc> <dpc> <sio>"
                            " <variant type>  <exchange type>\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_add_variant", "ISUP Add Variant Feature ",
             "<Variant Name>",""))
    {
        char varName[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, varName);
        if (ret != 2)
        {
            sprintf(buf,"\n *** Add variant failed, check the parameters: "
                    "\nUsage: ii_add_variant  <Variant Type>\n");
            DBC_AppendText(dbc, buf);
        }
        else
        {
            ret = ISUP_AddVariantFeature_CCITT(varName);
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n Variant Successfully Added\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOFEATURE)
            {
                sprintf(buf,"\n Invalid Variant Type: %s (or) Not supported\n",
                        varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINVVARIANT)
            {
                sprintf(buf,"\nAdd Variant Failed: %s Invalid Variant Entered\n ",
                            varName);
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_EINUSE)
            {
                sprintf(buf,"\nAdd Variant Failed: Variant Already Exists\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTFOUND)
            {
                sprintf(buf,"\nAdd Variant Failed: Required varaint library"
                            " not found in the LD path\n");
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n *** Add Variant Failed ,check the parameters: "
                            "\nUsage: ii_add_dest_info  <Variant Type>");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_timers",
                          "ISUP Get Timer Info",
                          "<opc> <dpc> <sio> [<Tid> (or) <*>]",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char tId[ITS_PATH_MAX];
        ITS_INT timeId;
        ISUP_CFG_KEY cfg;
        ISUP_CFG_TMR_INFO tmr_info[ISUP_CFG_MAX_TIMERS];


        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio, tId);
        if (ret == 5)
        {
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            if (strcmp(tId,"*") == 0)
            {
                ret = ISUP_GetAllTimerCfgInfo_CCITT(cfg, tmr_info);

                if(ret == ITS_SUCCESS)
                {
                    DBCPrintTimerCfg(tmr_info, NULL, dbc);
                }
                else if(ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
            }
            else
            {
                timeId = atoi(tId);
                ret = ISUP_GetAllTimerCfgInfo_CCITT(cfg, tmr_info);
                if (ret == ITS_SUCCESS)
                {
                    DBCPrintTimerCfg(tmr_info, &timeId, dbc);
                }
                else if(ret == ITS_ENOTCONFIG)
                {
                    sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                    DBC_AppendText(dbc, buf);
                }
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                  "Usage: ii_get_timers <opc> <dpc> <sio> [<Tid> (or) <*>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_set_timers",
                          "ISUP Set Timer Info",
                          "<opc> <dpc> <sio> <Tid> <TimerVal> <HandledBy>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char tId[ITS_PATH_MAX];
        char tVal[ITS_PATH_MAX];
        char tHand[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s %s", buf, opc, dpc, sio,
                     tId,tVal,tHand);
        if (ret == 7)
        {
            MTP3_HEADER opc_dpc_ni;
            ISUP_OPC_DPC_STAT *config_stat = NULL;
            ISUP_TMR_HNDL_INFO tmr_info;

            memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
            MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
            MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

            if ((strcmp(tHand, "STACK") == 0) || (strcmp(tHand, "APP") == 0))
            {
            }
            else
            {
                sprintf(buf, "\n *** Invalid Handle argument  Valid are:"
                             " STACK  or APP\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            /* First look for config info for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
            if (config_stat == NULL)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
                return;
            }

            if (atoi(tId) > ISUP_CFG_MAX_TIMERS)
            {
                sprintf(buf, "\n**** Invalid Timer Id *******\n");
                DBC_AppendText(dbc, buf);
                return;
            }

            tmr_info = config_stat->tmr_hndl_info[atoi(tId)];
            tmr_info.tmr_value = atoi(tVal);
            tmr_info.tmr_hndl_layer = ISUP_StringToTimerHandler(tHand);
            config_stat->tmr_hndl_info[atoi(tId)] = tmr_info;

            sprintf(buf, "\n**** ISUP Set Timer Successful********\n");
            DBC_AppendText(dbc, buf);

            ISUP_ReleaseOpcDpcStat(config_stat, ITS_FALSE);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_set_timers <opc> <dpc> <sio>"
                         " <Tid> <TimerVal> <HandledBy>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_cics",
                          "ISUP Get Circuit Info",
                          "<opc> <dpc> <sio>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret == 4)
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_CKGP_INFO * info;
            int noEnt;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetAllCicsCfg_CCITT(cfg, &info, &noEnt);
            if (ret == ITS_SUCCESS)
            {
                DBCPrintAllCicsCfg(info, noEnt, dbc);
                free(info);
            }
            else if(ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_get_cics  <opc> <dpc> <sio>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_add_cics",
                          "ISUP Add Circuit Info",
                          "<opc> <dpc> <sio> <startCic> <count> <control>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char startCic[ITS_PATH_MAX];
        char count[ITS_PATH_MAX];
        char contl[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s %s", buf, opc, dpc,
                     sio, startCic, count,contl);
        if (ret == 7)
        {
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            switch(ISUP_StringToCkgpCtrl(contl))
            {
                case ISUP_CFG_CKGP_CTRL_NONE:
                case ISUP_CFG_CKGP_CTRL_EVEN:
                case ISUP_CFG_CKGP_CTRL_ODD:
                case ISUP_CFG_CKGP_CTRL_ALL:
                case ISUP_CFG_CKGP_CTRL_DEF:
                    break;
                default:
                    sprintf(buf,"\nCic Rule is Invalid try again "
                                 "Possile Values are NONE, ALL, ODD, "
                                 "EVEN, DEF \n");
                    DBC_AppendText(dbc, buf);
                    return;
            }

            ret =ISUP_AddCicsCfg_CCITT(cfg, (ITS_USHORT)atoi(startCic),
                              (ITS_USHORT)atoi(count),
                              ISUP_StringToCkgpCtrl(contl));
            if(ret == ITS_SUCCESS)
            {
                sprintf(buf,"\nSuccessfully added Cic(s)\n");
            }
            else if(ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
            }
            else if(ret == ITS_EINVCIC)
            {
                sprintf(buf,"\nInvalid range of Cics\n");
            }
            else
            {
                sprintf(buf,"\nInvalid arguments\n");
            }
            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_add_cics  <opc> <dpc> <sio> "
                         "<startCic> <count> <control>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_del_cics",
                          "ISUP Del Circuit Info",
                          "<opc> <dpc> <sio> <startCic> <count>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char startCic[ITS_PATH_MAX];
        char count[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s %s %s ", buf, opc, dpc,
                     sio, startCic, count);
        if (ret == 6)
        {
            int ret;
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_DelCicsCfg_CCITT(cfg,
                                  (ITS_USHORT)atoi(startCic),
                                  (ITS_USHORT)atoi(count));
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf,"\n**** Successfully deleted Cic(s)\n");
            }
            else if (ret == ITS_ECICBUSY)

            {
                sprintf(buf,"\n**** One or more Cics are BUSY ***\n");
            }
            else if(ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n",atoi(opc),atoi(dpc),atoi(sio));
            }
            else
            {
                sprintf(buf,"\n*** Invalid range of Cics entered\n");
            }

            DBC_AppendText(dbc, buf);
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_del_cics  <opc> <dpc> <sio> "
                                             "<startCic> <count>\n ");
            DBC_AppendText(dbc, buf);
            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_cic_state",
                          "ISUP Get specified Circuit State ",
                          "<opc> <dpc> <sio> <cic> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT  cic;
        ISUP_PCIC pcic;
        ISUP_CIC_INFO *cic_rec = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret == 5)
        {
            ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

            /* Get cic_rec using the pcic as key */
            cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);

            if (cic_rec == NULL)
            {
                sprintf(buf,"\nCic record not found for given cic %d. Check inputs\n", cic);
                DBC_AppendText(dbc, buf);
            }
            else
            {
                DBCPrintCicState(cic_rec, dbc);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_get_cic_state  <opc> <dpc> <sio> <cic>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ii_set_cic_state",
                          "ISUP Set specified Circuit State ",
                          "<opc> <dpc> <sio> <cic> <state> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char cic[ITS_PATH_MAX];
        ITS_UINT state;

        ret = sscanf(cmdLine, "%s %s %s %s %s %d", buf, opc, dpc, sio, cic,
                                                                  &state);
        if (ret == 6)
        {
            ISUP_CFG_KEY cfg;

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret  = DBCVarifyCicState(state, dbc);
            if(ret != ITS_SUCCESS)
            {
                sprintf(buf, "\nInvalid CiC state try again\n");
                DBC_AppendText(dbc, buf);
                return;
            }
            ret = ISUP_SetCicStateInfo_CCITT(cfg, (ITS_USHORT)RESFILE_ParseNum(cic),
                                             (ITS_OCTET)state);
            if(ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\nCic record not found for given cic %d, check inputs.\n",atoi(cic));
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf, "\n** Set cic state successful **\n");
                DBC_AppendText(dbc, buf);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_set_cic_state <opc> <dpc> <sio> <cic> <state>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_gen_pegs", "ISUP Get Genaral Pegs"," "," "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintGeneralPegs(dbc);
    }
    else if (DBC_Cmd(dbc, "ii_get_gen_pegid", "ISUP Get Genaral Peg Type"," "," "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintGeneralPegType(dbc);
    }
    else if (DBC_Cmd(dbc, "ii_get_msgsent_pegs",
                      "ISUP Get Message Sent pegs","<opc> <dpc> <sio>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        int noEnt;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                     "Usage: ii_get_msgsent_pegs <opc> <dpc> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ISUP_CFG_KEY cfg;
            ISUP_CFG_PEGS SentPegs[ISUP_MAX_MSG_CODE];

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetMsgSentPegs_CCITT(cfg,SentPegs, &noEnt);

            if (ret == ITS_SUCCESS)
            {
                DBCPrintMsgSentPegs(SentPegs, noEnt, dbc);

            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n ii_get_msgsent_pegs Error:Check Arguments\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_clr_msgsent_pegs", "ISUP Reset All "
                       "Message sent Pegs","[<opc> <dpc> <sio>]",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char buf[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);

        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_clr_msgsent_pegs [<opc> <dpc> <sio>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ISUP_CFG_KEY cfg;
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_ClearAllMsgSentPegs_CCITT(cfg);

            if (ret == ITS_SUCCESS)
            {
                sprintf(buf, "\n* Cleared all ISUP Message Pegs *\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_clr_msgrcvd_pegs", "ISUP Reset All "
                        "Received Message Pegs","[<opc> <dpc> <sio>]",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char buf[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);

        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_clr_msgrcvd_pegs [<opc> <dpc> <sio>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            ISUP_CFG_KEY cfg;
            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_ClearAllMsgRcvdPegs_CCITT(cfg);
            if (ret == ITS_SUCCESS)
            {
                sprintf(buf, "\n* Cleared all ISUP Message pegs *\n");
                DBC_AppendText(dbc, buf);
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_msgrcvd_pegs",
                       "ISUP Get Received Message pegs","<opc> <dpc> <sio>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        int noEnt;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_get_msgrcvd_pegs <opc> <dpc> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {

            ISUP_CFG_KEY cfg;
            ISUP_CFG_PEGS RcvdPegs[ISUP_MAX_MSG_CODE];

            cfg.opc = atoi(opc);
            cfg.dpc = atoi(dpc);
            cfg.sio = atoi(sio);

            ret = ISUP_GetMsgRcvdPegs_CCITT(cfg,RcvdPegs,&noEnt);
            if (ret == ITS_SUCCESS)
            {
                DBCPrintMsgRcvdPegs(RcvdPegs, noEnt, dbc);
            }
            else if (ret == ITS_ENOTCONFIG)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                           " SIO (%d) ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\n*ii_get_msgrcvd_pegs Error:Check Arguments\n");
                DBC_AppendText(dbc, buf);
            }
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_cic_pegs", "ISUP Get CIC Pegs",
                                            "<opc> <dpc> <sio> <cic>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_CFG_KEY cfg;
        ISUP_CFG_PEGS cicPegs[PEG_ISUP_CIC_NUM_PEGS];

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_get_cic_pegs <opc> <dpc> <sio> <cic>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        cfg.opc = atoi(opc);
        cfg.dpc = atoi(dpc);
        cfg.sio = atoi(sio);

        ret = ISUP_GetCicPegs_CCITT(cfg, (ITS_USHORT)cic, cicPegs);
        if(ret == ITS_SUCCESS)
        {
            DBCPrintCicPegs(cicPegs, dbc);
        }
        else if(ret == ITS_ENOTCONFIG)
        {
            sprintf(buf, "\n**** Cic record not found ***\n");
            DBC_AppendText(dbc, buf);

            return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_cic_pegid", "ISUP Get CIC Pegs Type"," ",
" "))
    {
        char pgName[ITS_PATH_MAX];
        ret = sscanf(cmdLine, "%s %s", buf, pgName);

        DBCPrintCicPegsType(dbc);
    }
    else if (DBC_Cmd(dbc, "ii_clr_gen_pegs", "ISUP Reset a particular gen Peg",
                          "[<Pegid> (or) <All/all>]",""))
    {
        char buf[ITS_PATH_MAX];
        char pegType[ITS_PATH_MAX];

        ret = sscanf(cmdLine, "%s %s", buf, pegType);

        if (ret != 2)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_clr_gen_pegs [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((strncmp(pegType, "All", 3) == 0) ||
            (strncmp(pegType, "all", 3) == 0) ||
            (atoi(pegType) == ALL_ISUP_PEGS))

        {
           for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
           {
               PEG_ClearPeg(CCITT_ISUP_Pegs, i);
           }

           sprintf(buf, "\n** Cleared all ISUP gen pegs **\n");
           DBC_AppendText(dbc, buf);
           return;
        }
        else
        {
           if(!isdigit((int)pegType[0]))
           {
              sprintf(buf, "\n**** Unrecognized Peg *****\n");
              DBC_AppendText(dbc, buf);
              return;
           }
        }

        if ( atoi(pegType) > PEG_ISUP_NUM_PEGS - 1)
        {
             sprintf(buf, "\n** ISUP general peg %d does not exist **\n",
                                                       atoi(pegType));
             DBC_AppendText(dbc, buf);
             return;
         }

         for (i = 0; i < PEG_ISUP_NUM_PEGS; i++)
         {
             if (i == (ITS_UINT)RESFILE_ParseNum(pegType))
             {
                 PEG_ClearPeg(CCITT_ISUP_Pegs, i);
                 sprintf(buf, "\n** Cleared ISUP general peg id %d **\n", i);

                 DBC_AppendText(dbc, buf);
                 break;
             }
         }
    }
    else if (DBC_Cmd(dbc, "ii_clr_cic_pegs", "ISUP Clear particular Cic Peg",
                          "<opc> <dpc> <sio> <cic> [<Pegid> (or) <All/all>]",
""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;
        char pegType[ITS_PATH_MAX];
        ISUP_CIC_INFO *cic_rec = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %d %s", buf, opc, dpc, sio, &cic,
                                                                  pegType);
        if (ret != 6)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
            "Usage: ii_clr_cic_pegs <opc> <dpc> <sio> <cic> [<Pegid> (or) <All/all>]\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((atoi(pegType) > PEG_ISUP_CIC_NUM_PEGS - 1) &&
            (atoi(pegType) != ALL_ISUP_PEGS))
        {
            sprintf(buf, "\n** ISUP CIC peg %d does not exist **\n", atoi(pegType)
);
            DBC_AppendText(dbc, buf);
            return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        /* Get cic_rec using the pcic as key */
        cic_rec = ISUP_FindPcic( pcic, ITS_FALSE);
        if (cic_rec == NULL)
        {
            sprintf(buf, "\n**** Cic record not found ***\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((strncmp(pegType, "All", 3) == 0) ||
            (strncmp(pegType, "all", 3) == 0) ||
            (atoi(pegType) == ALL_ISUP_PEGS))
        {
           for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
           {
               PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, i);
           }

           sprintf(buf, "\n** Cleared all cic pegs for CIC %d **\n", cic);
           DBC_AppendText(dbc, buf);
           ISUP_ReleaseCic(cic_rec, ITS_FALSE);
           return;
         }
         else
         {
            if(!isdigit((int)pegType[0]))
            {
               sprintf(buf, "\n**** Unrecognized Peg *****\n");
               DBC_AppendText(dbc, buf);
               ISUP_ReleaseCic(cic_rec, ITS_FALSE);
               return;
            }
         }

        for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
        {
            if ((ITS_UINT)RESFILE_ParseNum(pegType) == i)
            {
               PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, i);
               sprintf(buf, "\n** Cleared peg id %d for CIC %d **\n", i, cic);
               DBC_AppendText(dbc, buf);
               break;
            }
        }
        ISUP_ReleaseCic(cic_rec, ITS_FALSE);
    }
    else if (DBC_Cmd(dbc, "ii_set_cong_lev", "ISUP Set Congestion Levels",
                       "<congLevel> <congValue>",""))
    {
        char congLevel[ITS_PATH_MAX];
        char congValue[ITS_PATH_MAX];
        int congLev, congVal, ret;

        ret = sscanf(cmdLine, "%s %s %s", buf, congLevel, congValue);

        congLev = atoi(congLevel);
        congVal = atoi(congValue);

        if (ret == 3)
        {
            if (congLev == 1 || congLev == 2)
            {
            }
            else
            {
                sprintf(buf, "\n *** Invalid congLevel argument  Valid are:"
                               " 1 or 2 ");
                DBC_AppendText(dbc, buf);
                return;
            }
            ret = ISUP_SetCong_CCITT(congLev, congVal);

            if (ret == ITS_SUCCESS)
            {
                sprintf(buf, "\n *** Successfully Set Cong Level ***\n");
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf, "\n *** New Cong Level NOT set ***\n");
                DBC_AppendText(dbc, buf);
            }
        }
        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
           "Usage: ii_set_cong_lev <congLevel> <congValue>\n");
            DBC_AppendText(dbc, buf);
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_cong_lev", "ISUP Get Congestion Levels",
                       "<congLevel> ",""))
    {
        char congLevel[ITS_PATH_MAX];
        int congLev;

        ret = sscanf(cmdLine, "%s %s", buf, congLevel);

        congLev = atoi(congLevel);

        if (ret == 2)
        {
            if (congLev == 1 || congLev == 2)
            {
            }
            else
            {
                sprintf(buf, "\n *** Invalid congLevel argument  Valid are:"
                               " 1 or 2");
                DBC_AppendText(dbc, buf);
                return;
            }
            ISUP_PrintCong_CCITT(congLev, dbc);
        }

        else
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
           "Usage: ii_get_cong_lev <congLevel: 1 or 2>\n");
            DBC_AppendText(dbc, buf);
        }

    }
    else if (DBC_Cmd(dbc, "ii_get_xchange_type", "ISUP Get Local Exchange Type",
                          "<opc> <dpc> <sio>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char astrix[ITS_PATH_MAX];

        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            if (ret == 2)
            {
                sscanf(cmdLine," %s %s",buf,astrix);
                if (strcmp(astrix,"*") == 0)
                {
                }
                else
                {
                    sprintf(buf, "\n**** Invalid Command Arguments *******\n");
                    DBC_AppendText(dbc, buf);
                    return;
                }
            }
            else
            {
                sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                        "Usage: ii_get_xchange_type <opc> <dpc> <sio>\n");
                DBC_AppendText(dbc, buf);
                return;
            }
        }
        else
        {
            memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
            MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
            MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

            /* First look for config info for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_TRUE);
            if (config_stat == NULL)
            {
                sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                       " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
                DBC_AppendText(dbc, buf);
                return;
            }
            else
            {
                /* Print Exchange Type from config info */
                if (config_stat->exchange_type == 0)
                {
                    sprintf(buf,"\nLocal ExchangeType: TYPE_A\n");
                    DBC_AppendText(dbc, buf);
                }
                else if (config_stat->exchange_type == 1)
                {
                    sprintf(buf,"\nLocal ExchangeType: TYPE_B\n");
                    DBC_AppendText(dbc, buf);
                }
                else
                {
                    sprintf(buf,"\nLocal ExchangeType: INVALID\n");
                    DBC_AppendText(dbc, buf);
                }
            }
        }
        ISUP_ReleaseOpcDpcStat(config_stat, ITS_TRUE);
    }
    else if (DBC_Cmd(dbc, "ii_set_xchange_type", "ISUP Set Local Exchange Type",
                          "<opc> <dpc> <sio> <xchangeType> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char xchangeType[ITS_PATH_MAX];
        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio,
                                                      xchangeType);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_set_xchange_type <opc> <dpc> <sio> <xchangeType>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((strcmp(xchangeType, "TYPE_A") == 0) ||
                               (strcmp(xchangeType, "TYPE_B") == 0))
        {
        }
        else
        {
            sprintf(buf, "\n *** Invalid xchangeType argument  Valid are:"
                         " TYPE_A  or TYPE_B \n");
            DBC_AppendText(dbc, buf);
            return;
        }

        memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
        MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
        MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
        MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

        /* First look for config info for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
        if (config_stat == NULL)
        {
            sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                    " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            config_stat->exchange_type =  ISUP_StringToXchangeType(xchangeType);
            sprintf(buf,"\n ****** Set Exchange Type Successful *******\n");
            DBC_AppendText(dbc, buf);
        }
        ISUP_ReleaseOpcDpcStat(config_stat, ITS_FALSE);
    }
    else if (DBC_Cmd(dbc, "ii_get_segsup_status", "ISUP Find Segmentation Supported Status",
                       "<opc> <dpc> <sio>",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat = NULL;

        ret = sscanf(cmdLine, "%s %s %s %s", buf, opc, dpc, sio);
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_get_segsupported_status <opc> <dpc> <sio>\n");
            DBC_AppendText(dbc, buf);
            return;
        }
        memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
        MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
        MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
        MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

        /* First look for config info for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_TRUE);
        if (config_stat == NULL)
        {
            sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                   " SIO (%d) \n",atoi(opc),atoi(dpc),atoi(sio));
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            /* Print segmentation_supported from config info */
            if (config_stat->segmentation_supported == 0)
            {
                sprintf(buf,"\nSegmentation Supported: no\n");
                DBC_AppendText(dbc, buf);
            }
            else
            {
                sprintf(buf,"\nSegmentation Supported: yes\n");
                DBC_AppendText(dbc, buf);
            }
        }
        ISUP_ReleaseOpcDpcStat(config_stat, ITS_TRUE);
    }
    else if (DBC_Cmd(dbc, "ii_set_segsup_status", "ISUP Set Segmentation Supported yes/no",
                       "<opc> <dpc> <sio> <segFlag> ",""))
    {
        char dpc[ITS_PATH_MAX];
        char opc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        char segFlag[ITS_PATH_MAX];
        MTP3_HEADER opc_dpc_ni;
        ISUP_OPC_DPC_STAT *config_stat =  NULL;

        ret = sscanf(cmdLine, "%s %s %s %s %s", buf, opc, dpc, sio,
                                                          segFlag);
        if (ret != 5)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_set_segsupported_status <opc> <dpc> <sio> <segFlag>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        if ((strcmp(segFlag, "yes") == 0) ||
                               (strcmp(segFlag, "no") == 0))
        {
        }
        else
        {
            sprintf(buf, "\n *** Invalid segFlag argument  Valid are:"
                         "yes or no\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
        MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,atoi(opc));
        MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,atoi(dpc));
        MTP3_HDR_SET_SIO(opc_dpc_ni,atoi(sio));

        /* First look for config info for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
        if (config_stat == NULL)
        {
            sprintf(buf,"\n *** Could not find config OPC (%d)  DPC (%d)"
                    " SIO (%d)\n ",atoi(opc),atoi(dpc),atoi(sio));
            DBC_AppendText(dbc, buf);
            return;
        }
        else
        {
            if (strcmp(segFlag, "yes") == 0)
            {
                config_stat->segmentation_supported = 0x01;
                sprintf(buf,"\n ****** Set Segmentation Supported Successful *******\n");
            }
            else
            {
                config_stat->segmentation_supported = 0x00;
                sprintf(buf,"\n ****** Set Segmentation Supported Successful *******\n");
            }
            DBC_AppendText(dbc, buf);
        }
        ISUP_ReleaseOpcDpcStat(config_stat, ITS_FALSE);
    }

    /*
     * All MML commands to send the CSC Messages follows
     */

    else if (DBC_Cmd(dbc, "ii_send_ubl", "ISUP Send Unblocking Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_UBL, ies, ieCount);

        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent UBL msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send UBL msg *******\n"
                          "Usage: ii_send_ubl <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_rsc", "ISUP Send Reset circuit Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_RSC, ies, ieCount);

        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent RSC msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send RSC msg *******\n"
                          "Usage: ii_send_rsc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_blo", "ISUP Send Blocking Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_BLO, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent BLO msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send BLO msg *******\n"
                          "Usage: ii_send_blo <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_cgb", "ISUP Send Circuit group reset Msg",
                          "<opc> <dpc> <sio> <cic> <supMsgType> "
                          "<range> <status> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT supMsgType = 0;
        ITS_UINT range = 0;
        ITS_UINT status = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d  %d  %d ", buf, opc, dpc, sio,
                               &cic, &supMsgType, &range, &status);
        if (ret != 8)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_cgb <opc> <dpc> <sio> <cic>"
                          " <supMsgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
        ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
        ies[0].param_data.supervisionMsgType.sup_mt = supMsgType;

        ies[1].param_id = ISUP_PRM_RANGE_STATUS;
        ies[1].param_length = 5;
        ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
        ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
        ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
        ies[1].param_data.rangeAndStatus.status[3] = (ITS_OCTET)(status >> 24);
        ieCount = 2;

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CGB, ies, ieCount);

        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent CGB msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send CGB msg *******\n"
                          "Usage: ii_send_cgb <opc> <dpc> <sio> <cic>"
                          "<msgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_cgu", "ISUP Send Circuit group unblocking Msg",
                          "<opc> <dpc> <sio> <cic> <supMsgType> "
                          "<range> <status> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT supMsgType = 0;
        ITS_UINT range = 0;
        ITS_UINT status = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d  %d  %d ", buf, opc, dpc, sio,
                               &cic, &supMsgType, &range, &status);
        if (ret != 8)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_cgu <opc> <dpc> <sio> <cic>"
                          " <supMsgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));
        ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
        ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
        ies[0].param_data.supervisionMsgType.sup_mt = supMsgType;

        ies[1].param_id = ISUP_PRM_RANGE_STATUS;
        ies[1].param_length = 5;
        ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
        ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
        ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
        ies[1].param_data.rangeAndStatus.status[3] = (ITS_OCTET)(status >> 24);

        ieCount = 2;

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CGU, ies, ieCount);

        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent CGU msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_cgu <opc> <dpc> <sio> <cic>"
                          " <supMsgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_cgu <opc> <dpc> <sio> <cic>"
                          " <supMsgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send CGU msg *******\n"
                          "Usage: ii_send_cgu <opc> <dpc> <sio> <cic>"
                          " <supMsgType> <range> <status>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_grs", "ISUP Send Group reset Msg",
                          "<opc> <dpc> <sio> <cic> <range>",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT range = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d", buf, opc, dpc, sio,
                               &cic, &range);
        if (ret != 6)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                         "Usage: ii_send_grs <opc> <dpc> <sio> <cic>"
                         " <range>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ies[0].param_id = ISUP_PRM_RANGE_STATUS;
        ies[0].param_length = 1;
        ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;

        ieCount = 1;

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_GRS, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent GRS msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_grs <opc> <dpc> <sio> <cic>"
                          " <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_grs <opc> <dpc> <sio> <cic>"
                          " <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send GRS msg *******\n"
                          "Usage: ii_send_grs <opc> <dpc> <sio> <cic>"
                          " <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_send_cqm", "ISUP Send Circuit query Msg",
                          "<opc> <dpc> <sio> <cic> <range> "
                          "<msgType> ",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic = 0;
        ITS_UINT range = 0;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d %d", buf, opc, dpc, sio,
                               &cic, &range);
        if (ret != 6)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                      "Usage: ii_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
            DBC_AppendText(dbc, buf);
            return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));
        ies[0].param_id = ISUP_PRM_RANGE_STATUS;
        ies[0].param_length = 1;
        ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;
        ieCount = 1;

        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CQM, ies, ieCount);
        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent CQM msg *******\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                      "Usage: ii_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                      "Usage: ii_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send CQM msg *******\n"
                      "Usage: ii_send_cqm <opc> <dpc> <sio> <cic> <range>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
    else if (DBC_Cmd(dbc, "ii_get_dest_pegs", "ISUP Get Destination Pegs",
                                            "<opc> <dpc> <sio>",""))
    {
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ISUP_CFG_KEY cfg;
        ISUP_CFG_PEGS destPegs[PEG_ISUP_DEST_NUM_PEGS];
        ret = sscanf(cmdLine, "%s %s %s %s ", buf, opc, dpc, sio );
        if (ret != 4)
        {
            sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                    "Usage: ii_get_dest_pegs <opc> <dpc> <sio> \n");
            DBC_AppendText(dbc, buf);
            return;
        }

       cfg.opc = atoi(opc);
       cfg.dpc = atoi(dpc);
       cfg.sio = atoi(sio);

       ret = ISUP_GetDestPegs_CCITT(cfg,destPegs);
       if (ret == ITS_SUCCESS)
       {
            DBCPrintDestPegs(destPegs, dbc);
       }

    }
    else if (DBC_Cmd(dbc, "ii_send_rlc", "ISUP Send Release confirmation Msg",
                          "<opc> <dpc> <sio> <cic>",""))
    {
        int ieCount = 0;
        ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
        char opc[ITS_PATH_MAX];
        char dpc[ITS_PATH_MAX];
        char sio[ITS_PATH_MAX];
        ITS_UINT cic;
        ISUP_PCIC pcic;

        ret = sscanf(cmdLine, "%s %s %s %s %d", buf, opc, dpc, sio, &cic);
        if (ret != 5)
        {
             sprintf(buf, "\n**** Invalid Command Arguments *******\n"
                          "Usage: ii_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }

        ISUP_PCICFromParts(&pcic, atoi(opc), atoi(dpc), atoi(sio), cic);

        memset((char *)&ies, 0, sizeof(ies));

        ies[0].param_id = ISUP_PRM_CAUSE_INDICATORS;
        ies[0].param_length = 2;

        SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                   CI_NO_EXTEND);
        SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                           CI_CS_CCITT);
        SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
        SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                         CI_NO_EXTEND);
        SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                 CI_CAUSE_NORMAL);

        ieCount = 1;
        ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_RLC, ies, ieCount);

        if (ret == ITS_SUCCESS)
        {
             sprintf(buf, "\n**** Successfully sent rlc msg *******\n");
             DBC_AppendText(dbc, buf);
        }
        else if (ret == ITS_ENOTCONFIG)
        {
             sprintf(buf, "\n**** Configuration not found  *******\n"
                          "Usage: ii_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else if (ret == ITS_EINVCIC)
        {
             sprintf(buf, "\n**** Invalid Cic Entered *******\n"
                          "Usage: ii_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
        else
        {
             sprintf(buf, "\n**** Failed to send rlc msg *******\n"
                          "Usage: ii_send_rlc <opc> <dpc> <sio> <cic>\n");
             DBC_AppendText(dbc, buf);
             return;
        }
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check the Route exits or not
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *     dpc - pc
 *     sio - service octet
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI ITS_BOOLEAN
ISUP_IsRouteExists_CCITT(ITS_UINT dpc, ITS_OCTET sio) 
{
    SS7_Destination *dest = NULL;

    dest = ROUTE_FindDestination(dpc, sio, FAMILY_ITU);
    if (dest == NULL)
    {
        return ITS_FALSE;;
    }
    ROUTE_CommitDestination(dest, dpc, sio, FAMILY_ITU);
    return ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add Varaint feature dynamically.
 *
 *  Input Parameters:
 *          varType  -  Variant Name
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *          ITS_EINVVARIANT
 *          ITS_ENOFEATURE
 *          ITS_EINUSE
 *          ITS_ENOTFOUND
 *          ITS_SUCCESS if operation succesds.
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_AddVariantFeature_CCITT(const char *varType)
{
    ITS_Class isup_Class = NULL;
    int ret;
    DLSYM_Manager *mgr = NULL;
    ISUP_VAR_TYPE variant;

    variant = ISUP_StringToVariant(varType);

    if (variant == ISUP_UNKNOWN)
    {
        return ITS_EINVVARIANT;
    }

    if (!(variant == ISUP_ITU_97 || variant == ISUP_ITU_GENERIC_93))
    {
        return ITS_ENOFEATURE;
    }

    if (ITS_FindFeature(varType) != NULL)
    {
        return ITS_EINUSE;
    }

    if (strcmp(varType, "ITU_ISUP_97") == ITS_SUCCESS)
    {
        mgr = DLSYM_Create("libITU_ISUP_97.so");
        if (mgr == NULL)
        {
            mgr = DLSYM_Create("libITU_ISUP_97D.so");
            if (mgr == NULL)
            {
                return ITS_ENOTFOUND;
            }
        }

        isup_Class = (ITS_Class) DLSYM_Resolve(mgr, "isupITU97_Class");
    }
    else if (strcmp(varType, "ITU_GENERIC_93") == ITS_SUCCESS)
    {
        mgr = DLSYM_Create("libITU_GENERIC_93.so");
        if (mgr == NULL)
        {
            mgr = DLSYM_Create("libITU_GENERIC_93D.so");
            if (mgr == NULL)
            {
                return ITS_ENOTFOUND;
            }
        }
        isup_Class = (ITS_Class) DLSYM_Resolve(mgr, "isupITU93_Class");
    }
    else
    {
        return !ITS_SUCCESS;
    }

    if (!isup_Class)
    {
        DLSYM_Destroy(mgr);
        return !ITS_SUCCESS;
    }

    /* I don't why I can't use isup_Class */
    ret  = ITS_InitializeClass(ITS_CLASS_SUPERCLASS(isup_Class));
    if (ret != ITS_SUCCESS)
    {
        DLSYM_Destroy(mgr);
        return ret;
    }

    ISUP_DEBUG(("ISUP_AddVariantFeature %s: Initialize Class ret Val %d\n",
                 varType, ret));

    return ITS_AddFeature(ITS_CLASS_SUPERCLASS(isup_Class));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Destination Specific pegs
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *          ITS_ENOTFOUND
 *          ITS_SUCCESS if operation succesds.
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_GetDestPegs_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_PEGS *destPegs )
{
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_INFO config_info;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;
    int ret,i;

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    ret = ISUP_FindOpcDpc(opc_dpc_ni, &config_info, isdsmlocal);

    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }

    /* Now retrive the PEG values from the config_info */
    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
       destPegs[i].pegId  =  i;
       destPegs[i].pegVal  = config_info.pegs[i];
       memcpy(destPegs[i].pegDesc, ISUP_Dest_Peg_Desc[i], strlen(ISUP_Dest_Peg_Desc[i]));
    }
    ISUP_ReleaseOpcDpc(&config_info);
    return ITS_SUCCESS;
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Destination (DPC) state.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_GetDpcState(ISUP_OPC_DPC_INFO *config_info,
                 ISUP_DEST_STATUS *state)
{
     *state = config_info->dest_stat;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set Destination (DPC) state.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_SetDpcState(ISUP_OPC_DPC_INFO *config_info, ISUP_DEST_STATUS state)
{
     config_info->dest_stat = state;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get Remote ISUP status.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_GetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info,
                        ISUP_REMOTE_ISUP_STATUS *state)
{
     *state = config_info->remote_isup_stat;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Set Remote ISUP Status.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
ITSSS7DLLAPI void
ISUP_SetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info,
                        ISUP_REMOTE_ISUP_STATUS state)
{
     config_info->remote_isup_stat = state;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_GetMsgSentPegs_CCITT(ISUP_CFG_KEY cfg,ISUP_CFG_PEGS *SentPeg, int* noEnt)
{
    int ret,i;
    MTP3_HEADER mtp3_hdr;
    ISUP_OPC_DPC_INFO config_info;
    memset(&mtp3_hdr,0,sizeof(MTP3_HEADER));
    MTP3_HDR_SET_SIO(mtp3_hdr,cfg.sio);
    MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label,cfg.dpc);
    MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label,cfg.opc);

    ret = ISUP_FindOpcDpc(mtp3_hdr, &config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }

    *noEnt = 0;

    for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
    {
        if (ISUP_Msg_Pegs_Sent_Desc[i] != NULL)
        {
            if ((config_info.isup_var_type == ISUP_ITU_GENERIC_93) &&
                                             (i == PEG_ISUP_LOP_SENT_TO_REMOTE))
            {
                continue;
            }
            (*noEnt)++;
            SentPeg[i].pegId = i;
            SentPeg[i].pegVal = config_info.pegs_msg_sent[i];
            memcpy(SentPeg[i].pegDesc,ISUP_Msg_Pegs_Sent_Desc[i],
            strlen(ISUP_Msg_Pegs_Sent_Desc[i]));
        }
        else
        {
            break;
        }
    }
    ISUP_ReleaseOpcDpc(&config_info);
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_ClearAllMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg)
{
    int i,ret;
    MTP3_HEADER mtp3_hdr;
    ISUP_OPC_DPC_INFO config_info;

    memset(&mtp3_hdr,0,sizeof(MTP3_HEADER));
    MTP3_HDR_SET_SIO(mtp3_hdr,cfg.sio);
    MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label,cfg.dpc);
    MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label,cfg.opc);
    ret = ISUP_FindOpcDpc(mtp3_hdr, &config_info, ITS_TRUE);

    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }
    else if (ret == ITS_SUCCESS)
    {
        for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
        {
            config_info.pegs_msg_rcvd[i] = 0;
        }
        ret = ISUP_UpdateOpcDpc(&config_info);
        ISUP_ReleaseOpcDpc(&config_info);
    }
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_ClearAllMsgSentPegs_CCITT(ISUP_CFG_KEY cfg)
{
    int i,ret;
    MTP3_HEADER mtp3_hdr;
    ISUP_OPC_DPC_INFO config_info;

    memset(&mtp3_hdr,0,sizeof(MTP3_HEADER));
    MTP3_HDR_SET_SIO(mtp3_hdr,cfg.sio);
    MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label,cfg.dpc);
    MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label,cfg.opc);
    ret = ISUP_FindOpcDpc(mtp3_hdr, &config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }
    else if (ret == ITS_SUCCESS)
    {
        for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
        {
            config_info.pegs_msg_sent[i] = 0;
        }
        ret = ISUP_UpdateOpcDpc(&config_info);
        ISUP_ReleaseOpcDpc(&config_info);
    }
    return ret;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_GetMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg,ISUP_CFG_PEGS *RcvdPeg, int* noEnt )
{
    int ret,i;
    MTP3_HEADER mtp3_hdr;
    ISUP_OPC_DPC_INFO config_info;
    memset(&mtp3_hdr,0,sizeof(MTP3_HEADER));
    MTP3_HDR_SET_SIO(mtp3_hdr,cfg.sio);
    MTP3_RL_SET_DPC_VALUE(mtp3_hdr.label,cfg.dpc);
    MTP3_RL_SET_OPC_VALUE(mtp3_hdr.label,cfg.opc);
    ret = ISUP_FindOpcDpc(mtp3_hdr, &config_info, ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTCONFIG;
    }
    *noEnt = 0;

    for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
    {
        if (ISUP_Msg_Pegs_Rcvd_Desc[i] != NULL)
        {

            if ((config_info.isup_var_type == ISUP_ITU_GENERIC_93) &&
                                            (i == PEG_ISUP_REMOTE_LOP_RCVD))
            {
                continue;
            }

            (*noEnt)++;
            RcvdPeg[i].pegId = i;
            RcvdPeg[i].pegVal = config_info.pegs_msg_rcvd[i];
            memcpy(RcvdPeg[i].pegDesc,ISUP_Msg_Pegs_Rcvd_Desc[i],
            strlen(ISUP_Msg_Pegs_Rcvd_Desc[i]));
        }
        else
        {
            break;
        }
    }
    ISUP_ReleaseOpcDpc(&config_info);
    return ITS_SUCCESS;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
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
 ****************************************************************************/
static int
DBCVarifyCicState(ITS_OCTET cic_state, DBC_Server *dbc)
{
    int ret = ITS_SUCCESS;
    char buf[ITS_PATH_MAX];

    switch(cic_state & 0x0cU) /* check bits DC */
    {
        case 0x00: /* DC is 00 */
            /* Now check for BA */
            switch(cic_state & 0x03)
            {
                case 0x00:
                    sprintf(buf, "Maintenance blocking state: TRANSIENT\n");
                    DBC_AppendText(dbc, buf);
                    break;

                case 0x11:
                    sprintf(buf, "Maintenance blocking state: UNEQUIPPED\n");
                    DBC_AppendText(dbc, buf);
                    break;

                default:
                    sprintf(buf, "Spare!\n");
                    DBC_AppendText(dbc, buf);
                    ret = !ITS_SUCCESS;
                    break;
            }
    }

    /* Bits DC not equal to 00 */
    switch(cic_state & 0x03U) /* Bits BA */
    {
        case 0x00:
            sprintf(buf, "Maintenance blocking state: UNBLOCKED (ACTIVE)\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x01:
            sprintf(buf, "Maintenance blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x02:
            sprintf(buf, "Maintenance blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x03:
            sprintf(buf, "Maintenance blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Maintenance state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }

    switch(cic_state & 0x0cU) /* Bits DC */
    {
        case 0x04:
            sprintf(buf, "Call processing state: CIRCUIT INCOMING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x08:
            sprintf(buf, "Call processing state: CIRCUIT OUTGOING BUSY\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x0c:
            sprintf(buf, "Call processing state: IDLE\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Call processing state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }

    switch(cic_state & 0x30U)
    {
        case 0x00:
            sprintf(buf, "Hardware blocking state: UNBLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x10:
            sprintf(buf, "Hardware blocking state: LOCALLY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x20:
            sprintf(buf, "Hardware blocking state: REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        case 0x30:
            sprintf(buf, "Hardware blocking state: LOCALLY & REMOTELY BLOCKED\n");
            DBC_AppendText(dbc, buf);
            break;

        default:
            sprintf(buf, "Hardware blocking state: INVALID STATE!\n");
            DBC_AppendText(dbc, buf);
            ret = !ITS_SUCCESS;
            break;
    }
    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the configured stack information for itu isup.
 *
 *  Input Parameters:
 *      Pointer to a file.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the stack informations written successfully on the given file
 *      it returns ITS_SUCCESS else if file pointer is null it will return
 *      ITS_ENULLPTR.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name          Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  Manikandan  05-05-2005  Bug ID:1791
 *
 ****************************************************************************/

int
INTELLINET_ISUP_Commit_CCITT(FILE* fp, int pos, int opc, int dpc, int sio)
{
    if (fp == NULL)
    {
        return ITS_ENULLPTR;
    }

    switch (pos)
    {
        case 1:
        {
            int count = 0;
            TRACE_Data* td = ISUP_CCITT_TraceData;

            if (td != NULL)
            {
                fprintf(fp, "\t\t\t<StackTrace>\n");
                
                if (TRACE_IsLevelOn(td, ISUP_TRACE_CRITICAL))
                {
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_CRITICAL, 0))
                    {
                        fprintf(fp, "\t\t\t\t<Critical output = \"stdout\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_CRITICAL, 1))
                    {
                        fprintf(fp, "\t\t\t\t<Critical output = \"file\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_CRITICAL, 2))
                    {
                        fprintf(fp, "\t\t\t\t<Critical output = \"syslog\" />\n");
                    }
                }
                
                if (TRACE_IsLevelOn(td, ISUP_TRACE_ERROR))
                {
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_ERROR, 0))
                    {
                        fprintf(fp, "\t\t\t\t<Error output = \"stdout\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_ERROR, 1))
                    {
                        fprintf(fp, "\t\t\t\t<Error output = \"file\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_ERROR, 2))
                    {
                        fprintf(fp, "\t\t\t\t<Error output = \"syslog\" />\n");
                    }
                }
                
                if (TRACE_IsLevelOn(td, ISUP_TRACE_WARNING))
                {
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_WARNING, 0))
                    {
                        fprintf(fp, "\t\t\t\t<Warning output = \"stdout\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_WARNING, 1))
                    {
                        fprintf(fp, "\t\t\t\t<Warning output = \"file\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_WARNING, 2))
                    {
                        fprintf(fp, "\t\t\t\t<Warning output = \"syslog\" />\n");
                    }
                }
                
                if (TRACE_IsLevelOn(td, ISUP_TRACE_DEBUG))
                {
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_DEBUG, 0))
                    {
                        fprintf(fp, "\t\t\t\t<Debug output = \"stdout\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_DEBUG, 1))
                    {
                        fprintf(fp, "\t\t\t\t<Debug output = \"file\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_DEBUG, 2))
                    {
                        fprintf(fp, "\t\t\t\t<Debug output = \"syslog\" />\n");
                    }
                }
                
                if (TRACE_IsLevelOn(td, ISUP_TRACE_EVENT))
                {
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_EVENT, 0))
                    {
                        fprintf(fp, "\t\t\t\t<Event output = \"stdout\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_EVENT, 1))
                    {
                        fprintf(fp, "\t\t\t\t<Event output = \"file\" />\n");
                    }
                    if (TRACE_IsOutputOn(td, ISUP_TRACE_EVENT, 2))
                    {
                        fprintf(fp, "\t\t\t\t<Event output = \"syslog\" />\n");
                    }
                }
                
                fprintf(fp, "\t\t\t</StackTrace>\n");
            }

            break;
        }
        case 2:
        {
            MTP3_HEADER opc_dpc_ni;
            ISUP_OPC_DPC_STAT *config_stat = NULL;

            memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
            MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,opc);
            MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,dpc);
            MTP3_HDR_SET_SIO(opc_dpc_ni,sio);
            config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_TRUE);

            if (config_stat != NULL)
            {
                fprintf(fp,
                        "\t\t                segmentationSupported = \"%s\"\n",
                        (config_stat->segmentation_supported == 0)?
                              "no" : "yes");
                fprintf(fp,
                        "\t\t                exchangeType   = \"%s\"\n",
                        (config_stat->exchange_type == 0)?
                              "TYPE_A" : "TYPE_B");
            }
            break;
        }
        case 3:
        {
            ISUP_CFG_TMR_INFO tmr_info[ISUP_CFG_MAX_TIMERS];
            ISUP_CFG_KEY cfg;
            ISUP_CFG_CKGP_INFO *ckgp;
            int noEnt;
            ITS_BOOLEAN startcicFound = ITS_FALSE;
            ITS_BOOLEAN cics_present = ITS_FALSE;
            ITS_OCTET cicrule = ISUP_CKGP_CTRL_DEF;
            int cicsInckg = 32;
            ITS_USHORT cic = 0, startcic = 0;
            int i, j, count;
            int ret = !ITS_SUCCESS;

            cfg.opc = opc;
            cfg.dpc = dpc;
            cfg.sio = sio;

            ret = ISUP_GetAllTimerCfgInfo_CCITT(cfg, tmr_info);

            if (ret == ITS_SUCCESS)
            {
                for (i = 1; i <=ISUP_CFG_MAX_TIMERS_CCITT; i++)
                {
                    fprintf(fp,
                            "\t\t\t<Timer name = \"%s\"\n",
                            ISUP_TimerToString((ITS_OCTET)i));
                    fprintf(fp,
                            "\t\t\t       value = \"%d\"\n",
                            tmr_info[i].tmr_cfg_value);
                    fprintf(fp,
                            "\t\t\t       handledBy = \"%s\"/>\n",
                            ISUP_TimerHandlerToString(
                              (ISUP_TMR_HNDL) tmr_info[i].tmr_cfg_hndl_layer));
                }
            }

            ret = !ITS_SUCCESS;
            ret = ISUP_GetAllCicsCfg_CCITT(cfg, &ckgp, &noEnt);
            if (ret == ITS_SUCCESS)
            {
                for(count = 0; count < noEnt; ++count)
                {
                    if (ckgp[count].usable_cics[0] == 0)
                    {
                        continue;
                    }

                    startcicFound = ITS_FALSE;

                    for(j = 0; j < cicsInckg; j++)
                    {
                        if ((ckgp[count].usable_cics[0] &
                            (0x00000001 << j)) != 0)
                        {
                            cics_present = ITS_TRUE;
                            cic = (ckgp[count].ckgp_id * cicsInckg) + (j+1);

                            if (!startcicFound)
                            {
                                startcic = (ckgp[count].ckgp_id * cicsInckg) +
                                           (j+1);
                                startcicFound = ITS_TRUE;
                            }
                            else if (cicrule != ckgp[count].contl[j])
                            {
                                fprintf(fp,
                                        "\t\t\t<CircuitGroup huntRule"
                                        " = \"%s\">\n",
                                        ISUP_CkgpCtrlToString(cicrule));
                                fprintf(fp,
                                        "\t\t\t\t<CircuitCodes start"
                                        " = \"%d\"\n",
                                        startcic);
                                fprintf(fp,
                                        "\t\t\t\t              "
                                        "count = \"%d\"/>\n",
                                        cic - startcic);
                                fprintf(fp, "\t\t\t</CircuitGroup>\n");
                                startcic = (ckgp[count].ckgp_id * cicsInckg) +
                                           (j+1);
                            }
                        }
                        else
                        {
                            if (startcicFound)
                            {
                                fprintf(fp,
                                        "\t\t\t<CircuitGroup huntRule"
                                        " = \"%s\">\n",
                                        ISUP_CkgpCtrlToString(cicrule));
                                fprintf(fp,
                                        "\t\t\t\t<CircuitCodes start"
                                        " = \"%d\"\n",
                                        startcic);
                                fprintf(fp,
                                        "\t\t\t\t              "
                                        "count = \"%d\"/>\n",
                                        cic - startcic + 1);
                                fprintf(fp, "\t\t\t</CircuitGroup>\n");
                            }

                            startcicFound = ITS_FALSE;
                        }

                        cicrule = ckgp[count].contl[j];
                    }

                    if (startcicFound)
                    {
                        fprintf(fp,
                                "\t\t\t<CircuitGroup huntRule = \"%s\">\n",
                                ISUP_CkgpCtrlToString(cicrule));
                        fprintf(fp,
                                "\t\t\t\t<CircuitCodes start = \"%d\"\n",
                                startcic);
                        fprintf(fp,
                                "\t\t\t\t              count = \"%d\"/>\n",
                                cic - startcic + 1);
                        fprintf(fp, "\t\t\t</CircuitGroup>\n");
                    }
                }
            }
            break;
        }
        case 4:
        {
            fprintf(fp,
                    "\t\t\tcongLevel1 = \"%d\"\n",
                    CCITT_ISUP_conglevel1);
            fprintf(fp,
                    "\t\t\tcongLevel2 = \"%d\"\n",
                    CCITT_ISUP_conglevel2);
            fprintf(fp,
                    "\t\t\tlocalcongTimer = \"%d\"\n",
                    CCITT_ISUP_localcongtimer);
            break;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Sets all ISUP General Config
 *
 *  Input Parameters:
 *      ISUP_GeneralCfg*    genCfg
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    ISUP_AlarmLevel_CCITT = genCfg->alarmLevel;

    if (genCfg->debugTrace)
    {
        TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_DEBUG_STRING,  ITS_TRUE);

        if (genCfg->debugTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->debugTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_DEBUG_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_DEBUG_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->warningTrace)
    {
        TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_WARNING_STRING,  ITS_TRUE);

        if (genCfg->warningTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->warningTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_WARNING_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_WARNING_STRING,  ITS_FALSE);
        }
    }

    if (genCfg->errorTrace)
    {
        TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_ERROR_STRING,  ITS_TRUE);

        if (genCfg->errorTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->errorTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_ERROR_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_ERROR_STRING,  ITS_FALSE);
        }
   }

    if (genCfg->criticalTrace)
    {
        TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_CRITICAL_STRING,  ITS_TRUE);

        if (genCfg->criticalTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->criticalTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_CRITICAL_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_CRITICAL_STRING,  ITS_FALSE);
        }
    }
    
    if (genCfg->eventTrace)
    {
        TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_EVENT_STRING,  ITS_TRUE);

        if (genCfg->eventTraceOutput & TRACE_TO_DISPLAY)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_FILE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_SYSLOG)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_TRUE);
        }
        else
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);
        }

        if (genCfg->eventTraceOutput & TRACE_TO_NONE)
        {
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_STDOUT_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_FILE_STRING,
                                       ITS_FALSE);
            TRACE_SetOutputOnOffByName(ISUP_CCITT_TraceData,
                                       ISUP_EVENT_STRING,
                                       ISUP_SYSLOG_STRING,
                                       ITS_FALSE);

            // Set trace level to false
            TRACE_SetLevelOnOffByName(ISUP_CCITT_TraceData, ISUP_EVENT_STRING,  ITS_FALSE);
        }
    }
    
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Gets all ISUP General Config
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      ISUP_GeneralCfg*    genCfg
 *
 *  Return Value:
 *      None
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
ISUP_OSS_GetGeneralCfg_CCITT(ISUP_GeneralCfg* genCfg)
{
    if (genCfg == NULL)
        return ITS_ENOMEM;

    genCfg->alarmLevel = (MGMT_AlarmLevel)ISUP_AlarmLevel_CCITT;

    genCfg->debugTrace = TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG);
    if (genCfg->debugTrace)
    {
        genCfg->debugTraceOutput = 0;
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG, 1))
        {
            genCfg->debugTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG, 2))
        {
            genCfg->debugTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG, 0))
        {
            genCfg->debugTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->warningTrace = TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING);
    if (genCfg->warningTrace)
    {
        genCfg->warningTraceOutput = 0;
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING, 1))
        {
            genCfg->warningTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING, 2))
        {
            genCfg->warningTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING, 0))
        {
            genCfg->warningTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->errorTrace = TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR);
    if (genCfg->errorTrace)
    {
        genCfg->errorTraceOutput = 0;
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR, 1))
        {
            genCfg->errorTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR, 2))
        {
            genCfg->errorTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR, 0))
        {
            genCfg->errorTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->criticalTrace = TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL);
    if (genCfg->criticalTrace)
    {
        genCfg->criticalTraceOutput = 0;
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL, 1))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL, 2))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL, 0))
        {
            genCfg->criticalTraceOutput |= TRACE_TO_NONE;
        }
    }

    genCfg->eventTrace = TRACE_IsLevelOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT);
    if (genCfg->eventTrace)
    {
        genCfg->eventTraceOutput = 0;
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_DISPLAY;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT, 1))
        {
            genCfg->eventTraceOutput |= TRACE_TO_FILE;
        }
        if (TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT, 2))
        {
            genCfg->eventTraceOutput |= TRACE_TO_SYSLOG;
        }
        else if (!TRACE_IsOutputOn(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT, 0))
        {
            genCfg->eventTraceOutput |= TRACE_TO_NONE;
        }
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specifed CICs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      startCic
 *      ITS_USHORT      range
 *      ITS_OCTET       ctrl
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI 
ITS_INT ISUP_OSS_AddCics_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT startCic, 
                               ITS_USHORT range, ITS_OCTET ctrl)
{
    int ret = ITS_SUCCESS;

    switch(ctrl)
    {
        case ISUP_CFG_CKGP_CTRL_NONE:
        case ISUP_CFG_CKGP_CTRL_EVEN:
        case ISUP_CFG_CKGP_CTRL_ODD:
        case ISUP_CFG_CKGP_CTRL_ALL:
        case ISUP_CFG_CKGP_CTRL_DEF:
            break;

        default:
            ISUP_ERROR(("CIC Rule is Invalid try again\n"));
            return ITS_ENOTFOUND;
    }

    ret = ISUP_AddCicsCfg_CCITT(cfg, startCic, range, ctrl);
    if(ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("%d CIC(s) added starting from CIC %d\n", range, startCic));
    }
    else if(ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("CIC(s) addition failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if(ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("CIC(s) addition failed. Invalid range of CICs\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Deletes the specifed CICs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      startCic
 *      ITS_USHORT      range
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_DeleteCics_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT startCic, ITS_USHORT range)
{
    int ret = ITS_SUCCESS;

    ret = ISUP_DelCicsCfg_CCITT(cfg, startCic, range); 
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("%d CIC(s) deleted starting from CIC %d\n", range, startCic));
    }
    else if (ret == ITS_ECICBUSY)
    {
        ISUP_ERROR(("CIC(s) deletion failed. One or more CIC(s) are busy\n"));
    }
    else if(ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("CIC(s) deletion failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else
    {
        ISUP_ERROR(("CIC(s) deletion failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets the configured CICs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY            cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_CKGP_INFO**    cics
 *      int*                    numCics
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetCics_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_CKGP_INFO** cics, int* numCics)
{
    int ret = ITS_SUCCESS;

    if (cics == NULL || numCics == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetAllCicsCfg_CCITT(cfg, cics, numCics);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("Get CIC(s) successful\n"));
    }
    else if(ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("Get CIC(s) failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sets the CIC state 
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *      ITS_OCTET       cicState
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SetCicState_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET cicState)
{
    ITS_INT ret = ITS_SUCCESS;

    ret = ISUP_SetCicStateInfo_CCITT(cfg, cic, cicState);
    if(ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Set CIC state failed\n"));
    }
    else
    {
        ISUP_DEBUG(("CIC state set\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets the CIC state 
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      ITS_OCTET*       cicState
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetCicState_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET *cicState)
{
    ITS_INT ret = ITS_SUCCESS;

    if (cicState == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetCicStateInfo_CCITT(cfg, cic, cicState);
    if(ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Get CIC state failed\n"));
    }
    else
    {
        ISUP_DEBUG(("CIC state %x\n", *cicState));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Adds the specified Destination Info
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY            cfg
 *      ISUP_VAR_TYPE           variant
 *      ISUP_CFG_EXCHANGE_TYPE  exchType
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_AddDestInfo_CCITT(ISUP_CFG_KEY cfg, ISUP_VAR_TYPE variant, ISUP_CFG_EXCHANGE_TYPE exchType)
{
    int ret = ITS_SUCCESS;
    char exchangeType[ITS_PATH_MAX];
    char variantType[ITS_PATH_MAX];

    if (exchType == ISUP_CFG_EXCHANGE_TYPE_A)
    {
        strcpy(exchangeType, "TYPE_A");
    }
    else if (exchType == ISUP_CFG_EXCHANGE_TYPE_B)
    {
        strcpy(exchangeType, "TYPE_B");
    }
    else
    {
        ISUP_ERROR(("Invalid Exchange Type\n"));
        return ITS_EINVALIDARGS;
    }

    strcpy(variantType, ISUP_VariantToString(variant));

    ret = ISUP_AddDestCfgInfo_CCITT(cfg, variantType, exchangeType);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("Dest Info added\n"));
    }
    else if (ret == ITS_ENOROUTE)
    {
        ISUP_ERROR(("Add Dest Info failed. Route not found for destination\n"));
    }
    else if (ret == ITS_EINVXCHANGE)
    {
        ISUP_ERROR(("Add Dest Info failed. Exchange Type is invalid\n"));
    }
    else if (ret == ITS_ENOFEATURE)
    {
        ISUP_ERROR(("Add Dest Info failed. Variant feature is not loaded\n"));
    }
    else if (ret == ITS_EINUSE)
    {
        ISUP_ERROR(("Add Dest Info failed. Destination already exists\n"));
    }
    else if (ret == ITS_ENOTFOUND)
    {
        ISUP_ERROR(("Add Dest Info failed. Variant not supported\n"));
    }
    else
    {
        ISUP_ERROR(("Add Dest Info failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets the configured Destination
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_DEST_INFO* destInfo
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetDestInfo_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_DEST_INFO* destInfo)
{
    int ret = ITS_SUCCESS;

    if (destInfo == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetDestCfgInfo_CCITT(cfg, destInfo);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("Get Dest Info success\n"));

    }
    else if(ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("Get Dest Info failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sets the exchange type
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY            cfg
 *      ISUP_CFG_EXCHANGE_TYPE  exchType
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SetExchangeType_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_EXCHANGE_TYPE exchType)
{
    ITS_INT ret = ITS_SUCCESS;
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = NULL;

    if ((exchType != ISUP_CFG_EXCHANGE_TYPE_A) &&
        (exchType != ISUP_CFG_EXCHANGE_TYPE_B))
    {
        ISUP_ERROR(("Invalid Exchange Type\n"));
        return ITS_EINVALIDARGS;
    }

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
    if (config_stat == NULL)
    {
        ISUP_ERROR(("Set Exchange Type failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
        return ITS_ENOTFOUND;
    }
    else
    {
        config_stat->exchange_type = exchType;
        ISUP_DEBUG(("Exchange Type Set\n"));
    }
    ISUP_ReleaseOpcDpcStat(config_stat, ITS_FALSE);

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets the exchange type
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY            cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_EXCHANGE_TYPE*  exchType
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetExchangeType_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_EXCHANGE_TYPE* exchType)
{
    ITS_INT ret = ITS_SUCCESS;
    MTP3_HEADER opc_dpc_ni;
    ISUP_OPC_DPC_STAT *config_stat = NULL;

    if (exchType == NULL)
    {
        return ITS_ENOMEM;
    }

    memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
    MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label, cfg.opc);
    MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label, cfg.dpc);
    MTP3_HDR_SET_SIO(opc_dpc_ni, cfg.sio);

    config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
    if (config_stat == NULL)
    {
        ISUP_ERROR(("Get Exchange Type failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
        return ITS_ENOTFOUND;
    }
    else
    {
        *exchType = config_stat->exchange_type;
        ISUP_DEBUG(("Get Exchange Type success\n"));
    }
    ISUP_ReleaseOpcDpcStat(config_stat, ITS_FALSE);

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sets the congestion value
 *
 *  Input Parameters:
 *      ITS_OCTET   congLevel
 *      ITS_UINT    congValue
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SetCongLevel_CCITT(ITS_OCTET congLevel, ITS_UINT congValue)
{
    int ret = ITS_SUCCESS;

    if (congLevel != 1 && congLevel != 2)
    {
        ISUP_ERROR(("Invalid Congestion Level\n"));
        return ITS_EINVALIDARGS;
    }

    ret = ISUP_SetCong_CCITT(congLevel, congValue);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Set Congestion Level failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Congestion Level Set\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets the congestion value
 *
 *  Input Parameters:
 *      ITS_OCTET   congLevel
 *
 *  Output Parameters:
 *      ITS_UINT*  congValue
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetCongLevel_CCITT(ITS_OCTET congLevel, ITS_UINT* congValue)
{
    int ret = ITS_SUCCESS;

    if (congValue == NULL)
    {
        return ITS_ENOMEM;
    }

    if (congLevel == 1)
    {
        *congValue = CCITT_ISUP_conglevel1;
    }
    else if (congLevel == 2)
    {
        *congValue = CCITT_ISUP_conglevel2;
    }
    else
    {
        ISUP_ERROR(("Invalid Congestion Level\n"));
        return ITS_EINVALIDARGS;
    }

    return ret;

}

/****************************************************************************
 *  Purpose:
 *      Adds the specified ISUP variant
 *
 *  Input Parameters:
 *      ISUP_VAR_TYPE   variant
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_AddVariant_CCITT(ISUP_VAR_TYPE variant)
{
    int ret = ITS_SUCCESS;

    ret = ISUP_AddVariantFeature_CCITT(ISUP_VariantToString(variant));
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("Variant %s added\n", ISUP_VariantToString(variant)));
    }
    else if (ret == ITS_ENOFEATURE)
    {
        ISUP_ERROR(("Add Variant failed. Invalid Variant Type %s or not supported\n",
                    ISUP_VariantToString(variant)));
    }
    else if (ret == ITS_EINVVARIANT)
    {
        ISUP_ERROR(("Add Variant failed. Invalid Variant Entered %s\n",
                    ISUP_VariantToString(variant)));
    }
    else if (ret == ITS_EINUSE)
    {
        ISUP_ERROR(("Add Variant failed. Variant already exists\n"));
    }
    else if (ret == ITS_ENOTFOUND)
    {
        ISUP_ERROR(("Add Variant failed. Required variant library not found\n"));
    }
    else
    {
        ISUP_ERROR(("Add Variant failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sets the specified timer value
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY        cfg
 *      ITS_UINT            timerId
 *      ITS_UINT            timerVal
 *      ISUP_CFG_TMR_HNDL   handlBy
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SetTimer_CCITT(ISUP_CFG_KEY cfg, ITS_UINT timerId, 
                        ITS_UINT timerVal, ISUP_CFG_TMR_HNDL handlBy)
{
    int ret = ITS_SUCCESS;

    ret = ISUP_SetTimerCfgInfo_CCITT(cfg, timerId, timerVal, handlBy); 
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Set Timer failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Timer set\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sets the timer values
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY        cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_TMR_INFO*  timers
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetTimers_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_TMR_INFO* timers)
{
    int ret = ITS_SUCCESS;

    if (timers == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetAllTimerCfgInfo_CCITT(cfg, timers);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Set Timer failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Timer set\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends UBL for the specified CIC
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendUBL_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_UBL, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("UBL Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("UBL Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("UBL Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("UBL Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends BLO for the specified CIC
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendBLO_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_BLO, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("BLO Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("BLO Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("BLO Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("BLO Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends RSC for the specified CIC
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendRSC_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_RSC, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("RSC Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("RSC Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("RSC Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("RSC Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends RLC for the specified CIC
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendRLC_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ies[0].param_id = ISUP_PRM_CAUSE_INDICATORS;
    ies[0].param_length = 2;

    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                   CI_NO_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                           CI_CS_CCITT);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                         CI_NO_EXTEND);
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[0].param_data.causeIndicator,
                 CI_CAUSE_NORMAL);

    ieCount = 1;

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_RLC, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("RLC Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("RLC Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("RLC Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("RLC Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends GRS for the specified CIC range
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *      ITS_USHORT      range
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendGRS_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_USHORT range)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ies[0].param_id = ISUP_PRM_RANGE_STATUS;
    ies[0].param_length = 1;
    ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;

    ieCount = 1;

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_GRS, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("GRS Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("GRS Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("GRS Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("GRS Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends CGU for the specified CIC range
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *      ITS_OCTET       msgType
 *      ITS_USHORT      range
 *      ITS_UINT        status
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendCGU_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET msgType,
                       ITS_USHORT range, ITS_UINT status)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
    ies[0].param_data.supervisionMsgType.sup_mt = msgType;

    ies[1].param_id = ISUP_PRM_RANGE_STATUS;
    ies[1].param_length = 5;
    ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
    ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
    ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
    ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
    ies[1].param_data.rangeAndStatus.status[3] = (ITS_OCTET)(status >> 24);

    ieCount = 2;

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CGU, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("CGU Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("CGU Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("CGU Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("CGU Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends CGB for the specified CIC range
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *      ITS_OCTET       msgType
 *      ITS_USHORT      range
 *      ITS_UINT        status
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendCGB_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET msgType,
                       ITS_USHORT range, ITS_UINT status)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ies[0].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[0].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);
    ies[0].param_data.supervisionMsgType.sup_mt = msgType;

    ies[1].param_id = ISUP_PRM_RANGE_STATUS;
    ies[1].param_length = 5;
    ies[1].param_data.rangeAndStatus.range = (ITS_OCTET)range;
    ies[1].param_data.rangeAndStatus.status[0] = (ITS_OCTET)status;
    ies[1].param_data.rangeAndStatus.status[1] = (ITS_OCTET)(status >> 8);
    ies[1].param_data.rangeAndStatus.status[2] = (ITS_OCTET)(status >> 16);
    ies[1].param_data.rangeAndStatus.status[3] = (ITS_OCTET)(status >> 24);

    ieCount = 2;

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CGB, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("CGB Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("CGB Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("CGB Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("CGB Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Sends CQM for the specified CIC range
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *      ITS_USHORT      range
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_SendCQM_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_USHORT range)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ISUP_PCIC pcic;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    memset((char *)&ies, 0, sizeof(ies));

    ies[0].param_id = ISUP_PRM_RANGE_STATUS;
    ies[0].param_length = 1;
    ies[0].param_data.rangeAndStatus.range = (ITS_OCTET)range;

    ieCount = 1;

    ret = ISUP_SendMsgMMLToStack_CCITT(pcic, ISUP_MSG_CQM, ies, ieCount);
    if (ret == ITS_SUCCESS)
    {
        ISUP_DEBUG(("CQM Msg sent\n"));
    }
    else if (ret == ITS_ENOTCONFIG)
    {
        ISUP_ERROR(("CQM Msg send failed. Could not find config OPC %d DPC %d SIO %x\n",
                    cfg.opc, cfg.dpc, cfg.sio));
    }
    else if (ret == ITS_EINVCIC)
    {
        ISUP_ERROR(("CQM Msg send failed. Invalid CIC\n"));
    }
    else
    {
        ISUP_ERROR(("CQM Msg send failed\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the General pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      ISUP_CFG_PEGS*  genPegs
 *      int*            numPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetGenPegs_CCITT(ISUP_CFG_PEGS* genPegs, int* numPegs)
{
    ITS_OCTET pegNum = 0;

    if (genPegs == NULL || numPegs == NULL)
    {
        return ITS_ENOMEM;
    }

    for (pegNum = 0; pegNum < PEG_ISUP_NUM_PEGS; pegNum++)
    {
        genPegs[pegNum].pegId = pegNum;
        genPegs[pegNum].pegVal = PEG_GetPeg(CCITT_ISUP_Pegs, pegNum);
        memcpy(genPegs[pegNum].pegDesc, ISUP_Peg_Desc[pegNum], strlen(ISUP_Peg_Desc[pegNum]));
    }
    *numPegs = PEG_ISUP_NUM_PEGS;

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the specified general peg or all general pegs
 *
 *  Input Parameters:
 *      None
 *
 *  Output Parameters:
 *      ITS_OCTET   pegId
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
ISUP_OSS_ClearGenPeg_CCITT(ITS_OCTET pegId)
{
    if (pegId == ISUP_ALL_PEGS)
    {
        PEG_ClearBlock(CCITT_ISUP_Pegs);
    }
    else
    {
        if (pegId >= PEG_ISUP_NUM_PEGS)
        {
            ISUP_ERROR(("Peg Id %d not found\n", pegId));
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(CCITT_ISUP_Pegs, pegId);
        }
    }

    ISUP_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the Message Sent pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_PEGS*  sentPegs
 *      int*            numPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetMsgSentPegs_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_PEGS* sentPegs, int* numPegs)
{
    int ret = ITS_SUCCESS;

    if (sentPegs == NULL || numPegs == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetMsgSentPegs_CCITT(cfg, sentPegs, numPegs);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Get Msg Sent Pegs failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Get Msg Sent Pegs success\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Clears all the Message Sent pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_ClearMsgSentPegs_CCITT(ISUP_CFG_KEY cfg)
{
    int ret = ITS_SUCCESS;

    ret = ISUP_ClearAllMsgSentPegs_CCITT(cfg);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Clear Msg Sent Pegs failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Clear Msg Sent Pegs success\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the Message Received pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *
 *  Output Parameters:
 *      ISUP_CFG_PEGS*  rcvdPegs
 *      int*            numPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_GetMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg, ISUP_CFG_PEGS* rcvdPegs, int* numPegs)
{
    int ret = ITS_SUCCESS;

    if (rcvdPegs == NULL || numPegs == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetMsgRcvdPegs_CCITT(cfg, rcvdPegs, numPegs);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Get Msg Rcvd Pegs failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Get Msg Rcvd Pegs success\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Clears all the Message Received pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT 
ISUP_OSS_ClearMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg)
{
    int ret = ITS_SUCCESS;

    ret = ISUP_ClearAllMsgRcvdPegs_CCITT(cfg);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("Clear Msg Rcvd Pegs failed\n"));
    }
    else
    {
        ISUP_DEBUG(("Clear Msg Rcvd Pegs success\n"));
    }

    return ret;
}

/****************************************************************************
 *  Purpose:
 *      Gets all the CIC Pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      ISUP_CFG_PEGS*  cicPegs
 *      ITS_OCTET*      numPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
ISUP_OSS_GetCicPegs_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ISUP_CFG_PEGS* cicPegs, 
                       ITS_OCTET* numPegs)
{
    int ret = ITS_SUCCESS;

    if (cicPegs == NULL || numPegs == NULL)
    {
        return ITS_ENOMEM;
    }

    ret = ISUP_GetCicPegs_CCITT(cfg, cic, cicPegs);
    if (ret != ITS_SUCCESS)
    {
        ISUP_DEBUG(("Get CIC Pegs failed\n"));
    }
    else
    {
        *numPegs = PEG_ISUP_CIC_NUM_PEGS;
        ISUP_DEBUG(("Get CIC Pegs success\n"));
    }

    return ITS_SUCCESS;
}

/****************************************************************************
 *  Purpose:
 *      Clears the specified CIC peg or all CIC pegs
 *
 *  Input Parameters:
 *      ISUP_CFG_KEY    cfg
 *      ITS_USHORT      cic
 *
 *  Output Parameters:
 *      ISUP_CFG_PEGS*  pegs
 *      ITS_OCTET*      numPegs
 *
 *  Return Value:
 *      ITS_INT
 ****************************************************************************/
ITSSS7DLLAPI ITS_INT
ISUP_OSS_ClearCicPeg_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic, ITS_OCTET pegId)
{
    ISUP_CIC_INFO* cic_rec;
    ISUP_PCIC pcic;
    ITS_BOOLEAN isdsmlocal = ITS_FALSE;

    ISUP_PCICFromParts(&pcic, cfg.opc, cfg.dpc, cfg.sio, cic);

    cic_rec = ISUP_FindPcic( pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    if (pegId == ISUP_ALL_PEGS)
    {
        PEG_ClearBlock(&cic_rec->ISUP_CIC_PEGS);
    }
    else
    {
        if (pegId >= PEG_ISUP_CIC_NUM_PEGS)
        {
            ISUP_ERROR(("Peg Id %d not found\n", pegId));
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            return ITS_ENOTFOUND;
        }
        else
        {
            PEG_ClearPeg(&cic_rec->ISUP_CIC_PEGS, pegId);
        }
    }


    ISUP_ReleaseCic(cic_rec, isdsmlocal);

    ISUP_DEBUG(("Peg(s) cleared\n"));
    return ITS_SUCCESS;
}


/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 ****************************************************************************/
int
ISUP_GetAllDestCfgInfo_CCITT(ISUP_CFG_DEST_INFO **cfg, int* noEnts)
{
    ISUP_CFG_ALLDEST_INFO inf;
    inf.info = cfg;
    inf.noEnt = noEnts;
    ISUP_HashTableIterate(ISUP_GetDestIterProc_CCITT, (void *)&inf,
                                                       noEnts);
    return ITS_SUCCESS;
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      None.
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 ****************************************************************************/
int
ISUP_GetDestIterProc_CCITT(ITS_INT context, ITS_POINTER data,
                          void *in, void *out)
{
    ISUP_OPC_DPC_INFO *config_info;
    int i = 0;
    static int j = 0;
    ISUP_CFG_ALLDEST_INFO *inf;
    inf = (ISUP_CFG_ALLDEST_INFO *)in;
    config_info = (ISUP_OPC_DPC_INFO *)data;

    j++;

    *inf->info = (ISUP_CFG_DEST_INFO *)realloc(*inf->info,
                       (j) * sizeof(ISUP_CFG_DEST_INFO));

    if(!config_info)
    {
        return !ITS_SUCCESS;
    }

    *inf->noEnt = j;
    ((*inf->info)[j - 1]).cfg.opc =
                    MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    ((*inf->info)[j - 1]).cfg.dpc =
                    MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
    ((*inf->info)[j - 1]).cfg.sio = config_info->opc_dpc_ni.sio;
    ((*inf->info)[j - 1]).variant =  config_info->isup_var_type;
    ((*inf->info)[j - 1]).congesInd =
                       (ISUP_CFG_CONGES)config_info->isup_rmt_conglev;
    ((*inf->info)[j - 1]).exchange_type =
                       (ISUP_CFG_EXCHANGE_TYPE)config_info->exchange_type;
    ((*inf->info)[j - 1]).dest_reachable =
                       (ISUP_CFG_DEST_STATUS)config_info->dest_stat;
    ((*inf->info)[j - 1]).remote_isup_stat =
                    (ISUP_CFG_REMOTE_ISUP_STATUS) config_info->remote_isup_stat;

    for (i = 0; i < ISUP_CFG_MAX_TIMERS; ++i)
    {
        ((*inf->info)[j - 1]).timer_info[i].tmr_cfg_hndl_layer =
             (ISUP_CFG_TMR_HNDL)config_info->tmr_hndl_info[i].tmr_hndl_layer;

        ((*inf->info)[j - 1]).timer_info[i].tmr_cfg_value =
                config_info->tmr_hndl_info[i].tmr_value;
    }

    (*(inf->noEnt)) = j;
    return ITS_SUCCESS;
}

