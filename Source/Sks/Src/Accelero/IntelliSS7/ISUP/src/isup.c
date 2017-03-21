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
 *  ID: $Id: isup.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:06  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:02  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:49:58  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.9.2.5.6.1.10.1  2004/12/16 03:35:28  randresol
 * LOG: Merge JAPAN variant implementation from TTC branch
 * LOG:
 * LOG: Revision 7.9.2.5.6.1.6.2  2004/10/25 21:04:35  randresol
 * LOG: Use CCITT definitions for TTC
 * LOG:
 * LOG: Revision 7.9.2.5.6.1.6.1  2004/10/25 20:58:55  randresol
 * LOG: Add SS7 Japan
 * LOG:
 * LOG: Revision 7.9.2.5.6.1  2004/01/05 09:42:37  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.9.2.5.2.2  2003/10/21 06:44:43  akumar
 * LOG: ISUP_ReceiveMgmtIndication func added.
 * LOG:
 * LOG: Revision 7.9.2.5.2.1  2003/09/12 10:43:49  akumar
 * LOG: Removed printf.
 * LOG:
 * LOG: Revision 7.9.2.5  2003/07/30 04:38:12  sjaddu
 * LOG: LOP is moved here from itu 97 var dir.
 * LOG:
 * LOG: Revision 7.9.2.4  2003/06/25 14:30:57  sjaddu
 * LOG: decodemtp3 function is renewed and changes done for service
 * LOG: activation also in 95.
 * LOG:
 * LOG: Revision 7.9.2.3  2003/06/17 06:24:09  tsanthosh
 * LOG: Modified Mtp3Encode func to include routing label.
 * LOG:
 * LOG: Revision 7.9.2.2  2003/06/04 10:45:36  sjaddu
 * LOG: changes to provide 95 variant library to client
 * LOG:
* LOG: Revision 7.9.2.1  2003/05/07 09:22:27  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.5  2003/05/06 09:02:23  sjaddu
 * LOG: ITS_CTXT changes are moved back to ITS_USHOR
 * LOG: (bug fix found by Tandem team during Remote congestion).
 * LOG:
 * LOG: Revision 8.4  2003/04/14 07:28:37  sjaddu
 * LOG: FAC message changes, SendFACRequest() is moved here.
 * LOG:
 * LOG: Revision 8.3  2003/04/04 05:00:18  ssingh
 * LOG: defination for ISUP_ReceiveConformation removed.
 * LOG:
 * LOG: Revision 8.2  2003/02/25 19:42:22  vnitin
 * LOG: Removed assret stmt in ISUP_DECODE function
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:24  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.9  2003/01/29 12:17:35  ssingh
 * LOG: Changed expression for calculating index value to fill header cic.
 * LOG:
 * LOG: Revision 7.8  2003/01/17 15:18:44  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.7  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.6  2003/01/13 23:51:25  vnitin
 * LOG: Add Typecasting changes for Tandem Port
 * LOG:
 * LOG: Revision 7.5  2002/11/26 05:53:11  ssingh
 * LOG: CFN desc got changed as per ANSI.
 * LOG:
 * LOG: Revision 7.4  2002/11/20 14:09:35  sjaddu
 * LOG: Added Cic in the Indication,error ,time out events.
 * LOG:
 * LOG: Revision 7.3  2002/11/13 11:11:03  akumar
 * LOG: Removed Warning, an unused variable in ISUP_Decode() function
 * LOG:
 * LOG: Revision 7.2  2002/11/11 11:28:20  akumar
 * LOG: Modified ISUP Decode function
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.5  2002/08/01 15:48:13  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.4  2002/07/03 19:55:10  mmiers
 * LOG: China fixes
 * LOG:
 * LOG: Revision 6.3.2.2  2002/07/25 21:32:12  ssingh
 * LOG: Added new functions to handle Indications and Conformations.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/07/02 20:16:14  hbalimid
 * LOG: FAC made specific to ITU93 as it is not in
 * LOG: ANSI92 which is a generic variant. FAC is present in
 * LOG: ANSI95 variant which is derived from ANSI92.
 * LOG:
 * LOG: Revision 6.3  2002/06/10 14:50:07  sjaddu
 * LOG: Typo fix.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:31:34  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.13.2.3  2002/05/09 18:22:31  labuser
 * LOG: EOP flag for COT correction.
 * LOG:
 * LOG: Revision 5.13.2.2.2.1  2002/04/29 16:43:26  labuser
 * LOG: fixed the message description for COT
 * LOG:
 * LOG: Revision 5.13.2.2  2002/04/11 14:21:09  ssharma
 * LOG: include tcap.h
 * LOG:
 * LOG: Revision 5.13.2.1  2002/04/04 21:48:18  ssanyal
 * LOG: Adding new msg ISUP_MSG_FAC for ANSI95 .
 * LOG:
 * LOG: Revision 5.13  2002/02/26 23:54:59  ssharma
 * LOG: Add timer and error indications to stack.
 * LOG:
 * LOG: Revision 5.12  2002/02/13 21:21:25  mmiers
 * LOG: Finish up ISUP integration
 * LOG:
 * LOG: Revision 5.11  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.10  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.9  2001/12/19 16:41:04  mmiers
 * LOG: Move GetDescriptor into common code.
 * LOG:
 * LOG: Revision 5.8  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.7  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.6  2001/11/16 02:23:50  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 5.5  2001/11/16 02:22:35  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 20:21:34  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:50:49  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 14:49:50  mmiers
 * LOG: Align with headers.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.6  2000/12/21 22:17:42  mmiers
 * LOG: Change proto
 * LOG:
 * LOG: Revision 3.5  2000/12/21 22:16:00  mmiers
 * LOG: Add prefix
 * LOG:
 * LOG: Revision 3.4  2000/09/20 19:00:59  cbascon
 * LOG: For RES msg change parameter tag array from resVArgs to resMArgs. There
 * LOG: are no variable size mandatory params for RES, only fixed mandatory
 * LOG: params.
 * LOG:
 * LOG: Revision 3.3  2000/09/20 15:30:28  cbascon
 * LOG: Delete 2nd entry of GenerecAddress param tag in iamOArgs[]
 * LOG:
 * LOG: Revision 3.2  2000/09/06 14:17:56  hxing
 * LOG: Init ITS_EVENT for the zero copy change.
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/08/08 17:06:14  hxing
 * LOG: ISUP_SendBLARequest was commented out. Fixed.
 * LOG:
 * LOG: Revision 2.13  2000/07/24 15:46:22  hxing
 * LOG: Fixed bug in ISUP_MessageSanityCheck(..)
 * LOG:
 * LOG: Revision 2.12  2000/07/21 16:03:21  hxing
 * LOG: Add IE natureOfConnectionIndicator to ISUP_ComputeMSize()
 * LOG:
 * LOG: Revision 2.11  2000/07/14 16:08:02  labuser
 * LOG: cbascon: Removed newnet specific send function for RSC response --RLC
 * LOG: with ISUP_RESET primitive.
 * LOG:
 * LOG: Revision 2.10  2000/07/11 14:33:34  hxing
 * LOG: Undo the change of yesterday. Need a better way to fix it.
 * LOG:
 * LOG: Revision 2.9  2000/07/10 19:47:59  hxing
 * LOG: ISUP_SendResetRLCRequest(NewNet) was calling ISUP_SendResetRLCEvent which was not defined,
 * LOG: change it to call ISUP_SendEvent instead.
 * LOG:
 * LOG: Revision 2.8  2000/05/26 20:07:06  cbascon
 * LOG: Deleted CON msg parameter BackwardCallIndicator in Optional Desc.
 * LOG: Should only be in Mandatory Desc
 * LOG:
 * LOG: Revision 2.7  2000/05/16 22:49:08  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.6  2000/02/15 22:42:56  fhasle
 * LOG: Fix for ANSI to compile.
 * LOG:
 * LOG: Revision 2.5  2000/02/03 17:09:34  fhasle
 * LOG: Updated DSP for INCLUDE_CODEC #defines (same as in TCAP). Added
 * LOG: variant to isup.c and created itu-isup_tlv.c (from TVL to/from) MTP3
 * LOG: funcs.
 * LOG:
 * LOG: Revision 2.4  2000/02/01 23:44:57  mmiers
 * LOG: Fix an encoding bug Fred found.
 * LOG:
 * LOG: Revision 2.3  2000/01/06 16:34:17  labuser
 * LOG: cbascon: SuspendResumeIndicator should be fixed not variable
 * LOG:          mandatory parameter
 * LOG:
 * LOG: Revision 2.2  1999/12/30 17:09:32  labuser
 * LOG: ForwardCallIndicator must be listed before CallingPartyCategory in IAM
 * LOG: description.
 * LOG:
 * LOG: Revision 2.1  1999/12/16 02:40:29  mmiers
 * LOG: gcc/g++ -Wall is very unforgiving.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:30  mmiers
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.23  1999/11/10 20:07:58  labuser
 * LOG:  fhasle: fix bug while compiling on UNIX.
 * LOG:
 * LOG: Revision 1.22  1999/11/10 20:02:01  labuser
 * LOG: fhasle: fix bug while compiling on UNIX (ANSI).
 * LOG:
 * LOG: Revision 1.21  1999/11/10 19:57:19  fhasle
 * LOG: Almost done fully ANSI and ITU compatible.
 * LOG:
 * LOG: Revision 1.20  1999/11/01 23:31:40  labuser
 * LOG: fhasle: fix bug in ISUP_SendPAM.
 * LOG:
 * LOG: Revision 1.19  1999/10/28 17:35:37  fhasle
 * LOG: Updated Call Progress, and params, (ANSI). Added Exit, and params, (ANSI)
 * LOG:
 * LOG: Revision 1.18  1999/10/27 15:45:53  mmiers
 * LOG: Remove warning
 * LOG:
 * LOG: Revision 1.17  1999/10/26 22:46:12  fhasle
 * LOG: updated to support ANSI + updated ISUP_SendPAM function call (not all msgs).
 * LOG:
 * LOG: Revision 1.16  1999/06/04 20:16:46  cmarchant
 * LOG: Get INAP tests building after ISUP update.
 * LOG:
 * LOG: Revision 1.15  1999/05/25 22:00:03  mmiers
 * LOG: First pass at ISUP.
 * LOG:
 * LOG: Revision 1.2  1999/05/25 02:10:44  mmiers
 * LOG: Get the descriptors in place.  Sort out ANSI vs. CCITT.
 * LOG:
 * LOG: Revision 1.1  1999/05/25 01:06:46  mmiers
 * LOG: Start cleaning up ISUP.
 * LOG:
 * LOG: Revision 1.20  1999/03/12 23:24:45  mmiers
 * LOG: Finish dual protocol family support.
 * LOG:
 * LOG: Revision 1.19  1998/12/16 16:35:06  rsonak
 * LOG: Bug fixes for trace, crash detection in sccp, remove extra console
 * LOG: print in DBC.
 * LOG:
 * LOG: Revision 1.18  1998/11/13 23:14:13  mmiers
 * LOG: Sanitize the NT build environment.
 * LOG:
 * LOG: Revision 1.17  1998/11/10 00:26:27  mmiers
 * LOG: Add ITU only parameter.
 * LOG:
 * LOG: Revision 1.16  1998/11/02 17:12:25  mmiers
 * LOG: Find routing label in all args, not just numOptionalArgs.
 * LOG:
 * LOG: Revision 1.15  1998/10/27 17:05:45  mmiers
 * LOG: Move some functions/signatures around so that we can share code.
 * LOG:
 * LOG: Revision 1.14  1998/09/26 22:37:12  mmiers
 * LOG: Convert to using message format descriptors.  ISUP needs something like
 * LOG: this as well, for many of the same reasons.
 * LOG:
 * LOG: Revision 1.13  1998/09/15 19:09:16  whu
 * LOG: Limit address encode/decode to one location for simplification.
 * LOG:
 * LOG: Revision 1.12  1998/06/18 16:44:59  mmiers
 * LOG: Forgot to add these.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:31  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.10  1998/06/01 22:31:59  mmiers
 * LOG: Raw documentation for ISUP.
 * LOG:
 * LOG: Revision 1.9  1998/05/14 20:41:43  mmiers
 * LOG: Update ISUP (read implement).  The rest are modifications to get
 * LOG: further the implementation of worker threads.
 * LOG:
 * LOG: Revision 1.8  1998/05/14 02:45:27  mmiers
 * LOG: More work on ISUP.  I think I have the encode done OK, still have to
 * LOG: write the decode.  The PTR table in ISUP messages is a bit of a bitch.
 * LOG: If we ever do the same for ISUP, the IEToEvent code could be reused.
 * LOG: That would give us (minus the ever important *PROCEDURES*) the requirement
 * LOG: of MTP3 and below ONLY.  However, ther are a *LOT* of procedures we
 * LOG: don't do (e.g., SST).
 * LOG:
 * LOG: Revision 1.7  1998/05/06 21:26:50  mmiers
 * LOG: Continue working on IS634 and ISUP.  Add C++ bindings for IS634
 * LOG: ISUP, and TCAP.
 * LOG:
 * LOG: Revision 1.6  1998/05/06 01:19:12  mmiers
 * LOG: Start writing encode for ISUP.
 * LOG:
 * LOG: Revision 1.5  1998/05/04 22:57:37  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.4  1998/05/01 14:22:14  mmiers
 * LOG: Clean up existing workspaces, add IS634 workspace.
 * LOG:
 * LOG: Revision 1.3  1998/05/01 14:04:21  mmiers
 * LOG: Update with interface routines.  Need to fill in checks for mandatory
 * LOG: parms, and call ifc routines.
 * LOG:
 * LOG: Revision 1.2  1998/04/07 15:51:54  mmiers
 * LOG: Update library to reflect vendor changes.
 * LOG:
 * LOG: Revision 1.1  1998/02/25 21:42:28  mmiers
 * LOG: Add in initial implementation of ISUP interface.
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include <its.h>
#include <its_license.h>
#include <its_trace.h>

#ident "$Id: isup.c,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

#include <isup_sn.h>
#include <isup_cmn.h>

#if defined(ANSI)
#include <ansi/isup.h>
#include <ansi/tcap.h>
#elif defined(CCITT)
#include <itu/isup.h>
#include <itu/tcap.h>
#elif defined(PRC)
#include <itu/isup.h>
#include <china/tcap.h>
#elif defined(TTC)
#include <itu/isup.h>
#include <japan/tcap.h>
#define CCITT
#else
#error Protocol version not defined
#endif

/*
 * Text for ITU Timers.
 */
#if defined(CCITT) || defined(TTC)
static char* __isup_timer_text[] = {
    "No Timer with ID 0.",
    "Release msg was sent; RLC not rcvd.",
    "Controlling exchng rcvd SUS (user) msg; RES not rcvd.",
    "Overload msg was rcvd.",
    "Received MTP-STATUS with cause remote user unavail.",
    "Initial Release msg was sent; RLC not rcvd.",
    "Controlling exchng rcvd SUS (network) msg; RES not rcvd.",
    "IAM msg was sent, ACM/CON not rcvd.",
    "IAM msg was rcvd, with Continuity Check; COT not rcvd.",
    "Natl controlling or outgoing Intl exchng rcvd ACM.",
    "Last digit rcvd in interworking conditions; no fresh info.",    /* 10 */
    "Latest IAM rcvd in interworking situations.",
    "Blocking msg was sent; BLA was not rcvd.",
    "Initial Blocking msg was sent; BLA not rcvd.",
    "Unblocking msg was sent; UBA not rcvd.",
    "Initial Unblocking msg was sent; UBA not rcvd.",
    "RST msg was sent; RLC not rcvd.",
    "Initial RST msg was sent; RLC not rcvd.",
    "CGB msg was sent; CGBA not rcvd.",
    "Initial CGB msg was sent; CGBA not rcvd.",
    "CGU msg was sent; CGUA not rcvd.",                              /* 20 */
    "Initial CGU msg was sent; CGUA not rcvd.",
    "GRS msg was sent; GRA not rcvd.",
    "Initial GRS msg was sent; GRA not rcvd.",
    "Check tone was sent; backward tone not rcvd.",
    "Initial Continuity Check fail detected.",
    "Subsequent Continuity Check fail detected.",
    "Continuity Check fail msg rcvd; CCR not rcvd.",
    "CQM msg was sent; CQR msg not rcvd.",
    "Congestion ind was rcvd, this timer was not running.",
    "Congestion ind was rcvd, T29 timer was not running.",           /* 30 */
    "Release of ISUP signalling connection based on CO-SCCP.",
    "Resp sent to req of end-to-end conn estblmnt; no msg from remote.",
    "INR was sent; INF not rcvd.",
    "Segementation ind on IAM/ACM/CPG/ANM/CON; SGM not rcvd.",
    "Latest digit rcvd prior to min or fixed # of digits.",
    "CCR msg was rcvd at transit/incoming intl exchng; COT/REL not rcvd.",
    "Req for echo control device was sent.",
    "Incoming intl exchng sent SUS (network); RES/REL not rcvd.",
    "Req for MCID was sent (IDR msg); resp not rcvd (IRS msg)."
};
#endif

/*
 * Text for ANSI Timers.
 */
#ifdef ANSI
static char* __isup_timer_text[] = {
    "No Timer with ID 0.",
    "Release msg was sent; RLC not rcvd.",
    "Timer is not specified for U.S. networks.",
    "Timer is not specified for U.S. networks.",
    "Timer is not specified for U.S. networks.",
    "Initial Release msg was sent; RLC not rcvd.",
    "Controlling exchng rcvd SUS (network) msg; RES not rcvd.",
    "IAM msg was sent, ACM/CON not rcvd.",
    "IAM msg was rcvd, with Continuity Check; COT not rcvd.",
    "Natl controlling or outgoing Intl exchng rcvd ACM.",
    "Timer is not specified for U.S. networks.",                     /* 10 */
    "Latest IAM rcvd in interworking situations.",
    "Blocking msg was sent; BLA was not rcvd.",
    "Initial Blocking msg was sent; BLA not rcvd.",
    "Unblocking msg was sent; UBA not rcvd.",
    "Initial Unblocking msg was sent; UBA not rcvd.",
    "RST msg was sent; RLC not rcvd.",
    "Initial RST msg was sent; RLC not rcvd.",
    "CGB msg was sent; CGBA not rcvd.",
    "Initial CGB msg was sent; CGBA not rcvd.",
    "CGU msg was sent; CGUA not rcvd.",                              /* 20 */
    "Initial CGU msg was sent; CGUA not rcvd.",
    "GRS msg was sent; GRA not rcvd.",
    "Initial GRS msg was sent; GRA not rcvd.",
    "Check tone was sent; backward tone not rcvd.",
    "Initial Continuity Check fail detected.",
    "Subsequent Continuity Check fail detected.",
    "Continuity Check fail msg rcvd; CCR not rcvd.",
    "CQM msg was sent; CQR msg not rcvd.",
    "Timer is not specified for U.S. networks.",
    "Timer is not specified for U.S. networks.",                     /* 30 */
    "Release of ISUP signalling connection based on CO-SCCP.",
    "Resp sent to req of end-to-end conn estblmnt; no msg from remote.",
    "INR was sent; INF not rcvd.",
    "LPA sent in resp to CCR; COT/REL not rcvd.",
    "Timer is not specified for U.S. networks.",
    "IAM msg was rcvd indic another segmnt; unsolicited INF not rcvd.",
    "ISUP availability test started; no msg from affected end.",
    "Automatic Congestion Control ind was rcvd.",
    "CCR was sent; LPA not rcvd.",
    "Initial COT fail msg was rcvd; CCR msg not rcvd."               /* 40 */
    "CGB msg was rcvd; CGB/CGU not rcvd.",
    "CRA msg was sent; IAM/REL not rcvd.",
    "CRM msg was sent; CRA not rcvd.",
    "CVT msg was sent; CVR not rcvd.",
    "IAM msg was sent to succeeding network.",
    "GRS msg was rcvd; GRS not rcvd.",
    "Carrier lost; carrier not restored.",
    "Initial demand continuity check in SCGA grp fails; success unrpted.",
    "Initial demand continuity check in SCGA grp fails."
};
#endif

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function returns a text string identifying the timer (ANSI).
 *
 *  Input Parameters:
 *      timerid - The ISUP Timer ID.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      A char pointer to the string identifying the timer on success.  
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
SS7DLLAPI char *
ISUP_GetTimerText(ITS_UINT timerid)
{
#if defined(ANSI)
    ITS_UINT maxtimer = ITS_ISUP_TIMER_TSCGAD;
#elif defined(CCITT) 
    ITS_UINT maxtimer = ITS_ISUP_TIMER_T39;
#endif

    if (timerid < ITS_ISUP_TIMER_T1 || timerid > maxtimer)
    {
        return "Input TimerID out of bounds";
    }
    return __isup_timer_text[timerid];
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To get the abbreviation for the the ISUP message type as specified in
 *      the input parameter.
 *
 *  Input Parameters:
 *      msgType - The ISUP message type.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      This function returns a pointer to the string of the abbreviation.
 *
 *  Notes:
 *
 *  See Also:
 *      ISUP_GetMsgFullName( ITS_UINT msgType );
 *
 ****************************************************************************/
SS7DLLAPI char *
ISUP_GetMsgAbbr(ITS_UINT msgType)
{
    switch (msgType)
    {

#ifdef ANSI
        case ISUP_MSG_CRM:
            return "CRM";
        case ISUP_MSG_CRA:
            return "CRA";
        case ISUP_MSG_CVR:
            return "CVR";
        case ISUP_MSG_CVT:
            return "CVT";
        case ISUP_MSG_EXM:
            return "EXM";
#endif
#if defined(CCITT) 
        case ISUP_MSG_CON:
            return "CON";
        case ISUP_MSG_CRG:
            return "CRG";
        case ISUP_MSG_IDR:
            return "IDR";
        case ISUP_MSG_IRS:
            return "IRS";
        case ISUP_MSG_FAA:
            return "FAA";
        case ISUP_MSG_FAC:
            return "FAC";
        case ISUP_MSG_FRJ:
            return "FRJ";
        case ISUP_MSG_FAR:
            return "FAR";
        case ISUP_MSG_NRM:
            return "NRM";
        case ISUP_MSG_OLM:
            return "OLM";
        case ISUP_MSG_SGM:
            return "SGM";
        case ISUP_MSG_SAM:
            return "SAM";
        case ISUP_MSG_UPA:
            return "UPA";
        case ISUP_MSG_UPT:
            return "UPT";
        case ISUP_MSG_USR:
            return "USR";
#endif
        case ISUP_MSG_ACM:
            return "ACM";
        case ISUP_MSG_ANM:
            return "ANM";
        case ISUP_MSG_BLO:
            return "BLO";
        case ISUP_MSG_BLA:
            return "BLA";
        case ISUP_MSG_CPG:
            return "CPG";
        case ISUP_MSG_CGB:
            return "CGB";
        case ISUP_MSG_CGBA:
            return "CGBA";
        case ISUP_MSG_CQM:
            return "CQM";
        case ISUP_MSG_CQR:
            return "CQR";
        case ISUP_MSG_GRS:
            return "GRS";
        case ISUP_MSG_GRA:
            return "GRA";
        case ISUP_MSG_CGU:
            return "CGU";
        case ISUP_MSG_CGUA:
            return "CGUA";
        case ISUP_MSG_CFN:
            return "CFN";
        case ISUP_MSG_COT:
            return "COT";
        case ISUP_MSG_CCR:
            return "CCR";
        case ISUP_MSG_FOT:
            return "FOT";
        case ISUP_MSG_INF:
            return "INF";
        case ISUP_MSG_INR:
            return "INR";
        case ISUP_MSG_IAM:
            return "IAM";
        case ISUP_MSG_LPA:
            return "LPA";
        case ISUP_MSG_PAM:
            return "PAM";
        case ISUP_MSG_REL:
            return "REL";
        case ISUP_MSG_RLC:
            return "RLC";
        case ISUP_MSG_RSC:
            return "RSC";
        case ISUP_MSG_RES:
            return "RES";
        case ISUP_MSG_SUS:
            return "SUS";
        case ISUP_MSG_UBL:
            return "UBL";
        case ISUP_MSG_UBA:
            return "UBA";
        case ISUP_MSG_UCIC:
            return "UCIC";
        default:
            return "UNKNOWN MESSAGE TYPE";
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      To get the full name of the ISUP message type specified in the input
 *      parameter.
 *
 *  Input Parameters:
 *      msgType - The ISUP message type.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      This function returns a pointer to the string of the full name.
 *
 *  Notes:
 *
 *  See Also:
 *      ISUP_GetMsgAbbr( ITS_UINT msgType );
 *
 ****************************************************************************/
SS7DLLAPI char *
ISUP_GetMsgName(ITS_UINT msgType)
{
    switch (msgType)
    {
#ifdef ANSI
        case ISUP_MSG_CRM:
            return "Circuit Reservation";
        case ISUP_MSG_CRA:
            return "Circuit Reservation Acknowledge";
        case ISUP_MSG_CVR:
            return "Circuit Validation Response";
        case ISUP_MSG_CVT:
            return "Circuit Validation Test";
        case ISUP_MSG_EXM:
            return "Exit";
#endif
#if defined( CCITT)
        case ISUP_MSG_CON:
            return "Connect";
        case ISUP_MSG_CRG:
            return "Charge Information";
        case ISUP_MSG_IDR:
            return "Identification Request";
        case ISUP_MSG_IRS:
            return "Identification Response";
        case ISUP_MSG_FAA:
            return "Facility Accepted";
        case ISUP_MSG_FAC:
            return "Facility";
        case ISUP_MSG_FRJ:
            return "Facility Reject";
        case ISUP_MSG_FAR:
            return "Facility Request";
        case ISUP_MSG_NRM:
            return "Network Resource Management";
        case ISUP_MSG_OLM:
            return "Overload";
        case ISUP_MSG_SAM:
            return "Subsequent Address";
        case ISUP_MSG_SGM:
            return "Segementation";
        case ISUP_MSG_UPA:
            return "User Part Available";
        case ISUP_MSG_UPT:
            return "User Part Test";
        case ISUP_MSG_USR:
            return "User-To-User Message";
#endif
        case ISUP_MSG_ACM:
            return "Address Complete Message";
        case ISUP_MSG_ANM:
            return "Answer";
        case ISUP_MSG_BLO:
            return "Blocking";
        case ISUP_MSG_BLA:
            return "Blocking Acknowledgement";
        case ISUP_MSG_CPG:
            return "Call Progress";
        case ISUP_MSG_CGB:
            return "Circuit Group Blocking";
        case ISUP_MSG_CGBA:
            return "Circuit Group Blocking Acknowledge";
        case ISUP_MSG_CQM:
            return "Circuit [Group - ITU] Query";
        case ISUP_MSG_CQR:
            return "Circuit [Group - ITU] Query Response";
        case ISUP_MSG_GRS:
            return "Circuit Group Reset";
        case ISUP_MSG_GRA:
            return "Circuit Group Reset Acknowledgement";
        case ISUP_MSG_CGU:
            return "Circuit Group Unblocking";
        case ISUP_MSG_CGUA:
            return "Circuit Group Unblocking Acknowledgement";
        case ISUP_MSG_CFN:
            return "Confusion";
        case ISUP_MSG_COT:
            return "Continuity";
        case ISUP_MSG_CCR:
            return "Continuity Check Request";
        case ISUP_MSG_FOT:
            return "Forward Transfer";
        case ISUP_MSG_INF:
            return "Information";
        case ISUP_MSG_INR:
            return "Information Request";
        case ISUP_MSG_IAM:
            return "Initial Address";
        case ISUP_MSG_LPA:
            return "Loopback Ack";
        case ISUP_MSG_PAM:
            return "Pass Along";
        case ISUP_MSG_REL:
            return "Release";
        case ISUP_MSG_RLC:
            return "Release Complete";
        case ISUP_MSG_RSC:
            return "Reset";
        case ISUP_MSG_RES:
            return "Resume";
        case ISUP_MSG_SUS:
            return "Suspend";
        case ISUP_MSG_UBL:
            return "Unblocking";
        case ISUP_MSG_UBA:
            return "Unblocking Acknowledgement";
        case ISUP_MSG_UCIC:
            return "Unequipped Circuit Identification Code";
        default:
            return "UNKNOWN MESSAGE TYPE";
    }
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      This method will find the description for an ISUP msg.
 *
 *  Input Parameters:
 *      msg: The type of the ISUP msg.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      a pointer to description for that msg or NULL if it does not exists.
 ****************************************************************************/
SS7DLLAPI ISUP_MSG_DESC *
ISUP_GetDescriptor(ITS_OCTET msgType)
{
    
    /*
     * Based on Table 3/Q.761, There is a minimun msg set 
     * recognized  at the international interface.
     * This does not really apply to C-ISUP since it is proprietary.
     */

    /*
     * This is very very ugly, but will work for now, need think about how to
     * get description based on variant.
     */

    switch (msgType)
    {
    case ISUP_MSG_ACM:
        return &ISUP_ACM_Desc;
        break;

    case ISUP_MSG_ANM:
        return &ISUP_ANM_Desc;
        break;

    case ISUP_MSG_BLO:
        return &ISUP_BLO_Desc;
        break;

    case ISUP_MSG_BLA:
        return &ISUP_BLA_Desc;
        break;

    case ISUP_MSG_CPG:
        return &ISUP_CPG_Desc;
        break;

    case ISUP_MSG_CGB:
        return &ISUP_CGB_Desc;
        break;

    case ISUP_MSG_CGBA:
        return &ISUP_CGBA_Desc;
        break;

    case ISUP_MSG_GRA:
        return &ISUP_GRA_Desc;
        break;

    case ISUP_MSG_GRS:
        return &ISUP_GRS_Desc;
        break;

    case ISUP_MSG_CGU:
        return &ISUP_CGU_Desc;
        break;

    case ISUP_MSG_CGUA:
        return &ISUP_CGUA_Desc;
        break;

    case ISUP_MSG_COT:
        return &ISUP_COT_Desc;
        break;

    case ISUP_MSG_CFN:
        return &ISUP_CFN_Desc;
        break;

    case ISUP_MSG_CCR:
        return &ISUP_CCR_Desc;
        break;

#if defined(CCITT)
    case ISUP_MSG_CON:
        return &ISUP_CON_Desc;

    case ISUP_MSG_FAA:
        return &ISUP_FAA_Desc;
    
    case ISUP_MSG_FRJ:
        return &ISUP_FRJ_Desc;

    case ISUP_MSG_FAR:
        return &ISUP_FAR_Desc;

    case ISUP_MSG_SAM:
        return &ISUP_SAM_Desc;

    case ISUP_MSG_IDR:
        return &ISUP_IDR_Desc;

    case ISUP_MSG_IRS:
        return &ISUP_IRS_Desc;

    case ISUP_MSG_NRM:
        return &ISUP_NRM_Desc;

    case ISUP_MSG_OLM:
        return &ISUP_OLM_Desc;

    case ISUP_MSG_SGM:
        return &ISUP_SGM_Desc;

    case ISUP_MSG_UPA:
        return &ISUP_UPA_Desc;

    case ISUP_MSG_UPT:
        return &ISUP_UPT_Desc;

    case ISUP_MSG_USR:
        return &ISUP_USR_Desc;

    case ISUP_MSG_LOP:
        return &ISUP_LOP_Desc;
#endif
        
    case ISUP_MSG_FOT:
        return &ISUP_FOT_Desc;
        break;

    case ISUP_MSG_IAM:
        return &ISUP_IAM_Desc;
        break;

    case ISUP_MSG_REL:
        return &ISUP_REL_Desc;
        break;

    case ISUP_MSG_RLC:
        return &ISUP_RLC_Desc;
        break;

    case ISUP_MSG_RSC:
        return &ISUP_RSC_Desc;
        break;

    case ISUP_MSG_RES:
        return &ISUP_RES_Desc;
        break;

    case ISUP_MSG_SUS:
        return &ISUP_SUS_Desc;
        break;

    case ISUP_MSG_UBL:
        return &ISUP_UBL_Desc;
        break;

    case ISUP_MSG_UBA:
        return &ISUP_UBA_Desc;
        break;

    case ISUP_MSG_UCIC:
        return &ISUP_UCIC_Desc;
        break;

        /* End of Table 3/Q.761 */

    case ISUP_MSG_CQM:
        return &ISUP_CQM_Desc;
        break;

    case ISUP_MSG_CQR:
        return &ISUP_CQR_Desc;
        break;    

    case ISUP_MSG_INF:
        return &ISUP_INF_Desc;
        break;

    case ISUP_MSG_INR:
        return &ISUP_INR_Desc;
        break;

    case ISUP_MSG_LPA:
        return &ISUP_LPA_Desc;
        break;

    case ISUP_MSG_FAC:
        return &ISUP_FAC_Desc;
        break;
    /*
     * No Description for CRG, thus no Send and Rec func, since the format of 
     * the msg os a national matter (Table 4/Q.763).
     */
    case ISUP_MSG_CRG:
        return NULL;
        break;

    default:
        /*
         * This can be a variant specific msg: Need to add EXM (ANSI Exit),
         * Application Transport (ITU 97 ?????) and Notification (C-ISUP).
         */
        break;
    }
    return NULL;
}

/*
 * compute the size of any fixed sized mandatory IE
 */
SS7DLLAPI ITS_OCTET
ISUP_ComputeMSize(ITS_OCTET which)
{
    switch (which)
    {
    case ISUP_PRM_NATURE_CONN_INDICATORS:
        return sizeof(ISUP_CONNECTION_INDICATORS);

    case ISUP_PRM_BKWD_CALL_INDICATORS:
        return sizeof(ISUP_BKWD_CALL_INDICATORS);

    case ISUP_PRM_EVENT_INFO:
        return sizeof(ISUP_EVENT_INFO);

    case ISUP_PRM_CONTINUITY_INDICATORS:
        return sizeof(ISUP_CONTINUITY_INDICATORS);

    case ISUP_PRM_INFO_INDICATORS:
        return sizeof(ISUP_INFORMATION_INDICATORS);

    case ISUP_PRM_INFO_REQ_INDICATORS:
        return sizeof(ISUP_INFORMATION_REQUEST_INDICATORS);

    case ISUP_PRM_FWD_CALL_INDICATORS:
        return sizeof(ISUP_FORWARD_CALL_INDICATORS);

    case ISUP_PRM_CALLING_PARTY_CATEGORY:
        return sizeof(ISUP_CALLING_PARTY_CATEGORY);

    case ISUP_PRM_SUSP_RESUM_INDICATORS:
        return sizeof(ISUP_SUSPEND_RESUME_INDICATORS);

    case ISUP_PRM_CKT_GRP_SUPRVN_MT_IND:
        return sizeof(ISUP_SUPERVISION_MSG_TYPE);

#ifdef CCITT 
    case ISUP_PRM_FACILITY_INDICATOR:
        return sizeof(ISUP_FACILITY_INDICATOR);

    case ISUP_PRM_TX_MEDIUM_REQMNT:
        return sizeof(ISUP_TX_MEDIUM_REQUIREMENT);
#endif

    default:
        return (0);

    }
}

/*
 * convert an array of IEs to an ITS_EVENT for (MTP3).  Note: as according to
 * the spec, the routing label is NOT part of the ISUP message.
 * margs contains an array of mandatory args, nmargs len
 * vargs contains an array of variable args, nvargs len
 * oargs contains an array of optional args, noargs len
 */
SS7DLLAPI int
ISUP_Encode(ITS_ISUP_IE *ies, int ieCount, ITS_OCTET msgType,
            ITS_EVENT *event, ITS_HDR *hdr, ISUP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset;

    ITS_ISUP_IE* ieRef[ITS_MAX_ISUP_IES];

    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;

    int ptrTableSize = 0;

    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;

    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;

    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;

    MTP3_HEADER *mtp3 = NULL;

    ITS_BOOLEAN msgIsPAM = ITS_FALSE;
    ITS_OCTET msgTypeInPAM = 0x00;
    int startIndex = 0;

#if defined(LOCAL_DEBUG)
    int q;
#endif

#if defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

    /* sanity */
    if (ieCount > ITS_MAX_ISUP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* Check if msg Type is PAM */
    if (msgType == ISUP_MSG_PAM)
    {
        if (ies[0].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            msgTypeInPAM = ies[0].param_data.msgTypeInPAM;
            msgIsPAM = ITS_TRUE;
            startIndex++;
        }
        else
        {
            return (ITS_EMISSMAND);
        }
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory */
    for (i = 0; i < nvargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == vargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }

    /* find the routing label, if present */
    for (i = startIndex; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_ROUTING_LABEL)
        {
            mtp3 = &ies[i].param_data.routingLabel;
            break;
        }
    }

    /* copy them in.  evoffset starts at msgtype + context */
    /* set the event source */
	ITS_EVENT_INIT(event, ITS_ISUP_SRC, MTP2_MAX_MSG_SIZE);    
    /* set the message type */
    event->data[0] = msgType;
    /* context is either ssn or connref */
    evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(MTP3_HEADER);
    /* set the context */
    ITS_SET_CTXT(&event->data[1], hdr->context.cic);

    /* copy the routing label */
    if (mtp3 != NULL)
    {
        memcpy(&event->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
               mtp3, sizeof(MTP3_HEADER));
    }
    else
    {
        memset(&event->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
               0, sizeof(MTP3_HEADER));
    }

    /*
     * Before putting in the params, if the Msg is the PAM, before the params
     * we must have the msg type in the PAM
     */
    if (msgIsPAM)
    {
        event->data[evoffset] = msgTypeInPAM;
        evoffset++;
    }

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        memcpy(&event->data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;
    }

    /* compute the size of the ptr table */
    ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    lastVarOffset = 0;

    /* build the ptr table for mandatory variable args */
    for (i = 0; i < nvargs; i++)
    {
        event->data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
        lastVarOffset += ieRef[nmargs + i]->param_length + 1;
        evoffset++;
    }

    /* if we have *any* optionals, build pointer to that */
    if (haveOpts)
    {
        event->data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
        optPtr = evoffset;
        evoffset++;
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        event->data[evoffset] = ieRef[nmargs + i]->param_length;
        evoffset++;

        memcpy(&event->data[evoffset], &ieRef[nmargs + i]->param_data,
               ieRef[nmargs + i]->param_length);

        evoffset += ieRef[nmargs + i]->param_length;
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        event->data[evoffset] = ieRef[i]->param_id;
        evoffset++;

        event->data[evoffset] = ieRef[i]->param_length;
        evoffset++;

        memcpy(&event->data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        event->data[evoffset] = ISUP_PRM_EOP;
        evoffset++;
    }

    if (haveOpts && !sawOpts)
    {
        event->data[optPtr] = 0;
    }

    /* set final length */
    event->len = (ITS_USHORT) evoffset;

    return (ITS_SUCCESS);
}

/*
 * Now go the other way.  Convert an event into an array of IEs
 */
SS7DLLAPI int
ISUP_Decode(ITS_ISUP_IE *ies, int *ieCount, ITS_EVENT *ev,
            ISUP_MSG_DESC* desc)
{
    int evoffset = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) +
                   sizeof(MTP3_HEADER);
    ITS_OCTET *ptr;
    int i;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
    int noargs = desc->noArgs;
#if defined(LOCAL_DEBUG)
    int q;
#endif

    evoffset += sizeof(ITS_OCTET);

#if defined(TTC)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_TTC_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(ANSI)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ANSI_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#elif defined(CCITT)
    if (!LICENSE_VerifyCapability(ITS_LIC_CAP_ITU_ISUP))
    {
        return (ITS_ENOLICENSE);
    }
#endif

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &ev->data[sizeof(ITS_OCTET) + sizeof(ITS_USHORT)],
           sizeof(MTP3_HEADER));

    /* avoid adding +1 everywhere */
    ies++;

    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        ies[i].param_length = ISUP_ComputeMSize(margs[i]);

        memcpy(&ies[i].param_data.pad.buf,
               &ev->data[evoffset], ies[i].param_length);

        evoffset += ies[i].param_length;
    }

    /* get the variable mandatories */
    ptr = &ev->data[evoffset];

    for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        /* compute the pointer */
        tmp = ptr + *ptr;
        ies[i + nmargs].param_length = *tmp;
        tmp++;

        memcpy(&ies[i + nmargs].param_data.pad.buf,
               tmp, ies[i + nmargs].param_length);
    	ptr++;

    }

    /* get the optionals, if any */
    i = 0;
    if (noargs && *ptr)
    {
        ptr += *ptr;

        while (*ptr != ISUP_PRM_EOP)
        {
            ies[i + nmargs + nvargs].param_id = *ptr;
            ptr++;
            ies[i + nmargs + nvargs].param_length = *ptr;
            ptr++;

            memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                   ptr, ies[i + nmargs + nvargs].param_length);

            ptr += ies[i + nmargs + nvargs].param_length;
            i++;
        }
    }

    /* set the return ieCount.  The '1' is for the MTP3 header */
    *ieCount = nmargs + nvargs + i + 1;

    return (ITS_SUCCESS);
}

/*
 * convert an array of IEs to a ITS_OCTET buf for MTP3.
 */
int 
ISUP_EncodeMTP3(ITS_ISUP_IE *ies, int ieCount, ITS_OCTET msgType,
                ITS_EVENT *event, ITS_HDR *hdr, ISUP_MSG_DESC* desc)
{
    int i, j, offset, evoffset, lastVarOffset;
    ITS_ISUP_IE* ieRef[ITS_MAX_ISUP_IES];
    ITS_BOOLEAN haveOpts = ITS_FALSE, sawOpts = ITS_FALSE;
    int optPtr = 0;
    int ptrTableSize = 0;
    ITS_OCTET *margs = desc->mArgs;
    int nmargs = desc->nmArgs;
    ITS_OCTET *vargs = desc->vArgs;
    int nvargs = desc->nvArgs;
    ITS_OCTET *oargs = desc->oArgs;
    int noargs = desc->noArgs;
    ITS_BOOLEAN msgIsPAM = ITS_FALSE;
    ITS_OCTET msgTypeInPAM = 0x00;
    int startIndex = 0;
    ITS_USHORT len = 0;
    ITS_OCTET data[MAX_ISUP_DATA_LEN];
    ITS_USHORT CIC = hdr->context.cic;

    ITS_TRACE_DEBUG(("ISUP_EncodeMTP3: hdr->context.CIC = %d\n", CIC));

    /* sanity */
    if (ieCount > ITS_MAX_ISUP_IES)
    {
        return (ITS_EOVERFLOW);
    }

    /* Check if msg Type is PAM */
    if (msgType == ISUP_MSG_PAM)
    {
        if (ies[0].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            msgTypeInPAM = ies[0].param_data.msgTypeInPAM;
            msgIsPAM = ITS_TRUE;
            startIndex++;
        }
        else
        {
            return (ITS_EMISSMAND);
        }
    }

    /* start at zero */
    offset = 0;

    /* find the fixed mandatory */
    for (i = 0; i < nmargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == margs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the variable mandatory */
    for (i = 0; i < nvargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == vargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }

        /* is it missing? */
        if (j == ieCount)
        {
            return (ITS_EMISSMAND);
        }
    }

    /* find the optionals */
    for (i = 0; i < noargs; i++)
    {
        for (j = startIndex; j < ieCount; j++)
        {
            if (ies[j].param_id == oargs[i])
            {
                ieRef[offset] = &ies[j];
                offset++;
                break;
            }
        }
        /* if missing, that's ok */
    }

    /* skip extras */
    while (offset < ieCount)
    {
        ieRef[offset] = NULL;
        offset++;
    }
        
    /* set the message type */
    data[0] = msgType;
    
    evoffset = sizeof(ITS_OCTET);    

    /*
     * Before putting in the params, if the Msg is the PAM, before the params
     * we must have the msg type in the PAM
     */
    if (msgIsPAM)
    {
        data[evoffset] = msgTypeInPAM;
        evoffset++;
    }

    /* copy in the mandatories */
    for (i = 0; i < nmargs; i++)
    {
        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* do we have any optionals? */
    if (noargs > 0)
    {
        haveOpts = ITS_TRUE;
    }

    /* compute the size of the ptr table */
    ptrTableSize = nvargs + (haveOpts ? 1 : 0);
    lastVarOffset = 0;

    /* build the ptr table for mandatory variable args */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
        lastVarOffset += ieRef[nmargs + i]->param_length + 1;
        evoffset++;
    }

    /* if we have *any* optionals, build pointer to that */
    if (haveOpts)
    {
        data[evoffset] = (ITS_OCTET)(ptrTableSize + lastVarOffset - i);
        optPtr = evoffset;
        evoffset++;
    }

    /* copy in the variable mandatories */
    for (i = 0; i < nvargs; i++)
    {
        data[evoffset] = ieRef[nmargs + i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[nmargs + i]->param_data,
               ieRef[nmargs + i]->param_length);

        evoffset += ieRef[nmargs + i]->param_length;
    }

    /* copy in the optionals */
    for (i = nmargs + nvargs; i < ieCount; i++)
    {
        if (ieRef[i] == NULL)
        {
            continue;
        }

        sawOpts = ITS_TRUE;

        data[evoffset] = ieRef[i]->param_id;
        evoffset++;

        data[evoffset] = ieRef[i]->param_length;
        evoffset++;

        memcpy(&data[evoffset], &ieRef[i]->param_data,
               ieRef[i]->param_length);

        evoffset += ieRef[i]->param_length;
    }

    /* terminate variable list */
    if (noargs != 0)
    {
        data[evoffset] = ISUP_PRM_EOP;
        evoffset++;
    }

    if (haveOpts && !sawOpts)
    {
        data[optPtr] = 0;
    }

    /* set final length */
    len = (ITS_USHORT)evoffset;

    event->data[0] = MTP3_MSG_USER_DATA;

    /* find the routing label, if present */
    for (i = 0, j = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_ROUTING_LABEL)
        {
            /* Get MTP3 header */
            memcpy(&event->data[1],&ies[i].param_data.routingLabel,
                   sizeof(MTP3_HEADER));
            break;
        }
    }

    /* copy in the (rest of)CIC */
    event->data[1+sizeof(MTP3_HEADER)] = (ITS_OCTET)(CIC & 0xFF);
    event->data[1+sizeof(MTP3_HEADER)+1] = (ITS_OCTET)((CIC >> 8) & 0xFF);
    
    memcpy(&event->data[1 + sizeof(MTP3_HEADER) + 2], data, len);

    event->len = (ITS_USHORT)(sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) +
                 sizeof(ITS_USHORT) + len);

    event->src = ITS_ISUP_SRC;

    /*   -------------------------------------------------
     *   | 1 | MTP3_HEADER | CIC | ISUP message          |
     *   -------------------------------------------------
     *     1   sizeof(^)      2        len
     */

    return (ITS_SUCCESS);
}

int 
ISUP_DecodeMTP3(ITS_ISUP_IE *ies, int *ieCount, ITS_EVENT *ev,
                ISUP_MSG_DESC* desc)
{
    int index = 0, i, j = 0;
    ITS_OCTET *ptr;
    ITS_OCTET *margs, *vargs, *oargs;
    int nmargs = 0, nvargs = 0, noargs = 0;
    ITS_BOOLEAN paramFound = ITS_FALSE;
    ITS_USHORT newlen = 0;
    ITS_OCTET *data;
    int len;

    margs = desc->mArgs;
    nmargs = desc->nmArgs;
    vargs = desc->vArgs;
    nvargs = desc->nvArgs;
    oargs = desc->oArgs;
    noargs = desc->noArgs;

    index = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(MTP3_HEADER);

    data = ev->data;
    len  = ev->len - index;

    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &ev->data[index - sizeof(MTP3_HEADER)], sizeof(MTP3_HEADER));
    *ieCount = 1;

    ies++;


    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        ies[i].param_id = margs[i];
        ies[i].param_length = ISUP_ComputeMSize(margs[i]);

        memcpy(&ies[i].param_data.pad.buf,
               &data[index], ies[i].param_length);

        index += ies[i].param_length;
    }


    newlen = index;

    /* get the variable mandatories */
    ptr = &data[index];
   for (i = 0; i < nvargs; i++)
    {
        ITS_OCTET *tmp;

        ies[i + nmargs].param_id = vargs[i];

        /* compute the pointer */
        tmp = ptr + *ptr;
        ies[i + nmargs].param_length = *tmp;
        newlen += (*tmp + 2);
        tmp++;

        memcpy(&ies[i + nmargs].param_data.pad.buf,
               tmp, ies[i + nmargs].param_length);

        ptr++;

    }

    /* get the optionals, if any */
    i = 0;
    if (noargs && *ptr)
    {
        ptr += *ptr;
        newlen++;

        while (*ptr != ISUP_PRM_EOP)
        {
            paramFound = ITS_FALSE;
            for (j =0; j < noargs ;++j)
            {
                if (*ptr == desc->oArgs[j])
                {
                    paramFound = ITS_TRUE;
                }
            }
            if(paramFound)
            {
                ies[i + nmargs + nvargs].param_id = *ptr;
                ptr++;
                ies[i + nmargs + nvargs].param_length = *ptr;
                newlen += (*ptr + 2);
                ptr++;

                memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                       ptr, ies[i + nmargs + nvargs].param_length);
                ptr += ies[i + nmargs + nvargs].param_length;
                i++;
            }
            else
            {
                ies[i + nmargs + nvargs].param_id = ISUP_PRM_PAD_BUF;
                ies[i + nmargs + nvargs].param_length = len - newlen;
                memcpy(&ies[i + nmargs + nvargs].param_data.pad.buf,
                       ptr, len - newlen);
                *ieCount += nmargs + nvargs + i + 1;
                return ITS_EPARAMPRSNT;
            }
        }
    }

    /* set the return ieCount. */
    *ieCount += nmargs + nvargs + i;

    return ITS_SUCCESS;
}

#if defined(CCITT) 

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the ISUP msg is valid for the protocol
 *      family.  This particular function is intended for vendor
 *      implementations, not for the end user.
 *
 *  Input Parameters:
 *      ies - the ISUP msg to check sanity for.
 *      ieCount - Number of ies in the ISUP msg.
 *      desc - The description of the message type of the ISUP msg to check.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADISUPMESSAGE - the ISUP message is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
ISUP_MessageSanityCheck_CCITT(ITS_OCTET type, ITS_ISUP_IE *ies, int ieCount,
                              ISUP_MSG_DESC *desc)
{
    /* To know if we found the param in the description.*/
    ITS_BOOLEAN param_found = ITS_FALSE;

    /* Nb of F and V params */
    int nb_mandatory_params = desc->nmArgs + desc->nvArgs;

    /* Nb of F and V params found. */
    int  nb_Fparams_found = 0, nb_Vparams_found = 0, nb_Oparams_found = 0;

    /* Max nb of params allowed for that msg */
    int nb_params = desc->nmArgs + desc->nvArgs + desc->noArgs;

    /* Index to browse through ie and description */
    int ie_index = 0, desc_index = 0, startIndex = 0;

    /* If the ISUP msg is PAM, first expected ie is the msg within the PAM.*/
    if (type == ISUP_MSG_PAM)
    {
        if (ies[startIndex].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            /* inc startIndex to skip this ie */
            startIndex++;
            
            /*
             * +1 to include first IE: Type of Msg in PAM.
             * nb_mandatory_params and nb_params only use for quick check.
             */
            nb_mandatory_params++;
            nb_params++;
        }
        else
        {
            return (ITS_BADISUPMESSAGE);
        }
    }

    /* If msgDesc only contains O params && ieCount == 0, message is valid */
    if ((nb_mandatory_params == 0) && (ieCount == 0))
    {
        return (ITS_SUCCESS);
    }

    /* 
     * Quick first check:
     * a) nb of ies is at least equal to nb of F + V params.
     * b) no overflow: nb of ies less than ITS_MAX_ISUP_IES and less than
     *    or equal to max nb of params for this msg.
     */    
    if ((ieCount < nb_mandatory_params) || (ieCount > ITS_MAX_ISUP_IES) ||
        (ieCount > nb_params))
    {
        return (ITS_BADISUPMESSAGE);
    }    

    for (ie_index = startIndex; ie_index < ieCount; ie_index++)
    {
        /* reset param_found */
        param_found = ITS_FALSE;

        /* F params */
        if (nb_Fparams_found != desc->nmArgs)
        {
            for (desc_index = 0; desc_index < desc->nmArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->mArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Fparams_found++;
                    break;
                }
            }
            if (param_found)
            {
                /* We found the param, it is a F param. Next param */
                continue;
            }
        }

        /* V params */
        if (nb_Vparams_found != desc->nvArgs)
        {
            for (desc_index = 0; desc_index < desc->nvArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->vArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Vparams_found++;
                    break;
                }
            }
            if (param_found)
            {
                /* We found the param, it is a V param. Next param */
                continue;
            }
        }

        /* O params */
        if (nb_Oparams_found != desc->noArgs)
        {
            for (desc_index = 0; desc_index < desc->noArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->oArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Oparams_found++;
                    break;
                }
            }
            if (!param_found)
            {
                /* We did not find the param, Error */
                break;
            }
        }
    }
    
    /*
     * If we are missing a F or V params, or we did not find a param in the
     * description, it is a bad ISUP msg.
     */
    if ((!param_found) || (nb_Fparams_found != desc->nmArgs) ||
        (nb_Vparams_found != desc->nvArgs))
    {
        return (ITS_BADISUPMESSAGE);
    }

    return (ITS_SUCCESS);
}

#endif /* ifdef CCITT */

#if defined (ANSI)

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method ensures that the ISUP msg is valid for the protocol
 *      family.  This particular function is intended for vendor
 *      implementations, not for the end user.
 *
 *  Input Parameters:
 *      ies - the ISUP msg to check sanity for.
 *      ieCount - Number of ies in the ISUP msg.
 *      desc - The description of the message type of the ISUP msg to check.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - the component is coherent
 *      ITS_BADISUPMESSAGE - the ISUP message is inconsistent.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
ISUP_MessageSanityCheck_ANSI(ITS_OCTET type, ITS_ISUP_IE *ies, int ieCount,
                             ISUP_MSG_DESC *desc)
{
    /* To know if we found the param in the description*/
    ITS_BOOLEAN param_found = ITS_FALSE;

    /* Nb of F and V params */
    int nb_mandatory_params = desc->nmArgs + desc->nvArgs;

    /* Nb of F and V params found. */
    int  nb_Fparams_found = 0, nb_Vparams_found = 0, nb_Oparams_found = 0;

    /* Max nb of params allowed for that msg */
    int nb_params = desc->nmArgs + desc->nvArgs + desc->noArgs;

    /* Index to browse through ie and description */
    int ie_index = 0, desc_index = 0, startIndex = 0;

    /* If the ISUP msg is PAM, first expected ie is the msg within the PAM.*/
    if (type == ISUP_MSG_PAM)
    {
        if (ies[startIndex].param_id == ISUP_PRM_MSG_IN_PAM)
        {
            /* inc startIndex to skip this ie */
            startIndex++;

            /*
             * +1 to include first IE: Type of Msg in PAM.
             * nb_mandatory_params and nb_params only use for quick check.
             */
            nb_mandatory_params++;
            nb_params++;
        }
        else
        {
            return (ITS_BADISUPMESSAGE);
        }
    }


    /* If msgDesc only contains O params && ieCount == 0, message is valid */
    if ((nb_mandatory_params == 0) && (ieCount == 0))
    {
        return (ITS_SUCCESS);
    }

    /* 
     * Quick first check:
     * a) nb of ies is at least equal to nb of F + V params.
     * b) no overflow: nb of ies less than ITS_MAX_ISUP_IES and less than
     *    or equal to max nb of params for this msg.
     */
    if ((ieCount < nb_mandatory_params) || (ieCount > ITS_MAX_ISUP_IES) ||
        (ieCount > nb_params))
    {
        return (ITS_BADISUPMESSAGE);
    }

    /*
     * Using the description, make sure that F params (if present) and/or
     * V params (if present) are present in the ISUP msg, and no extra
     * params are added.
     */
    for (ie_index = startIndex; ie_index < ieCount; ie_index++)
    {
        /* reset param_found */
        param_found = ITS_FALSE;

        /* F params */
        if (nb_Fparams_found != desc->nmArgs)
        {
            for (desc_index = 0; desc_index < desc->nmArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->mArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Fparams_found++;
                    break;
                }
            }
            if (param_found)
            {
                /* We found the param, it is a F param. Next param */
                continue;
            }
        }

        /* V params */
        if (nb_Vparams_found != desc->nvArgs)
        {
            for (desc_index = 0; desc_index < desc->nvArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->vArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Vparams_found++;
                    break;
                }
            }
            if (param_found)
            {
                /* We found the param, it is a V param. Next param */
                continue;
            }
        }

        /* O params */
        if (nb_Oparams_found != desc->noArgs)
        {
            for (desc_index = 0; desc_index < desc->noArgs; desc_index++)
            {
                if (ies[ie_index].param_id == desc->oArgs[desc_index])
                {
                    /* We found the param */
                    param_found = ITS_TRUE;
                    nb_Oparams_found++;
                    break;
                }
            }
            if (!param_found)
            {
                /* We did not find the param, Error */
                break;
            }
        }
    }

    /*
     * If we are missing a F or V params, or we did not find a param in the
     * description, it is a bad ISUP msg.
     */
    if ((!param_found) || (nb_Fparams_found != desc->nmArgs) ||
        (nb_Vparams_found != desc->nvArgs))
    {
        return (ITS_BADISUPMESSAGE);
    }

    return (ITS_SUCCESS);
}

#endif /* ifdef ANSI  */


/*** ACM ***/
static ITS_OCTET    acmMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};
static ITS_OCTET    acmOArgs[] =
{
#ifdef ANSI
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
    ISUP_PRM_REDIRECTION_INFO,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM,
#endif
#endif /*ANSI*/

#ifdef CCITT 
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS,
#endif
#endif /*CCITT*/

    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC ISUP_ACM_Desc =
{
    ITS_TRUE,
    acmMArgs, sizeof(acmMArgs),
    NULL, 0,
    acmOArgs, sizeof(acmOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function builds and sends a ConnectionRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      hdr - the context for this message
 *      ies - the information elements that make up the message
 *      ieCount - the number of information elements
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the message is successfully sent, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendACMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_ACM, hdr, ies, ieCount,
                          &ISUP_ACM_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function decodes a ConnectionRequest
 *      message.
 *
 *  Input Parameters:
 *      handle - the transport handle
 *      ev - the event to receive from
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      hdr - the context to receive into
 *      ies - the information elements to receive into
 *      ieCount - the number of information elements to receive
 *
 *  Return Value:
 *      If the message is successfully received, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
SS7DLLAPI int
ISUP_ReceiveACMIndication(ITS_HANDLE handle, ITS_EVENT *ev,
                          ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && ev != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, ev, hdr, ies, ieCount,
                             &ISUP_ACM_Desc);
}

/*** ANM ***/
static ITS_OCTET anmOArgs[] =
{
#if defined ANSI
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM,
#endif
#endif
#ifdef CCITT 
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO, 
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
    ISUP_PRM_ECHO_CTRL_INFO,    
    ISUP_PRM_GENERIC_NUM,    
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_DISPLAY_INFORMATION,
#endif
#endif
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,    
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_ANM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    anmOArgs, sizeof(anmOArgs)
};
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
SS7DLLAPI int
ISUP_SendANMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_ANM, hdr,
                          ies, ieCount, &ISUP_ANM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveANMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_ANM_Desc);
}

/*** CFN ***/
static ITS_OCTET cfnVArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};

#if defined(ANSI)
static ITS_OCTET cfnOrgs[] =
{
    ISUP_PRM_EOP
};
#endif

SS7DLLAPI ISUP_MSG_DESC   ISUP_CFN_Desc =
{
    ITS_TRUE,
    NULL, 0,
    cfnVArgs, sizeof(cfnVArgs),
#if defined(ANSI)
    cfnOrgs, 1
#else
    NULL, 0
#endif
};

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
SS7DLLAPI int
ISUP_SendCFNRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CFN, hdr,
                          ies, ieCount, &ISUP_CFN_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCFNIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CFN_Desc);
}


/*** CPG ***/
static ITS_OCTET cpgMArgs[] =
{
    ISUP_PRM_EVENT_INFO
};

static ITS_OCTET cpgOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BKWD_CALL_INDICATORS,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CAUSE_INDICATORS,
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
#ifdef ANSI
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_INFO_INDICATORS,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_NOTIFICATION,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_TRANSMISSION_MEDIUM_USED,
    ISUP_PRM_USER_TO_USER_INDS,
    ISUP_PRM_USER_TO_USER_INFORM
#endif
#endif
#ifdef CCITT 
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALL_DIVERSION_INFO,
    ISUP_PRM_SERVICE_ACTIVATION,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_UID_ACTION_INDICATORS,
#endif
    ISUP_PRM_REDIRECTION_NUM_RESTRICT
#endif
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_CPG_Desc =
{
    ITS_TRUE,
    cpgMArgs, sizeof(cpgMArgs),
    NULL, 0,
    cpgOArgs, sizeof(cpgOArgs),
};

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
SS7DLLAPI int
ISUP_SendCPGRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CPG, hdr,
                          ies, ieCount, &ISUP_CPG_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCPGIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CPG_Desc);
}


/*** IAM ***/
static ITS_OCTET iamMArgs[] =
{
    ISUP_PRM_NATURE_CONN_INDICATORS,
    ISUP_PRM_FWD_CALL_INDICATORS,
    ISUP_PRM_CALLING_PARTY_CATEGORY,
#ifdef CCITT 
    ISUP_PRM_TX_MEDIUM_REQMNT
#endif
};
static ITS_OCTET iamVArgs[] =
{
#ifdef ANSI
    ISUP_PRM_USER_SERVICE_INFO,
#endif
    ISUP_PRM_CALLED_PARTY_NUM
};
static ITS_OCTET iamOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_GENERIC_DIGITS,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_ORIG_CALLED_NUM,
    ISUP_PRM_TRANSIT_NTWK_SELECT,
#ifdef ANSI
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CARRIER_ID,
    ISUP_PRM_CARRIER_SELECTION_INFO,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_EGRESS_SERVICE,
    ISUP_PRM_GENERIC_ADDR,
    ISUP_PRM_INFO_REQ_INDICATORS,
    ISUP_PRM_JURISDICTION,
    ISUP_PRM_NTWK_TRANSPORT,
    ISUP_PRM_ORIG_LINE_INFO,
    ISUP_PRM_SERVICE_CODE,
    ISUP_PRM_SPECIAL_PROCESS_REQUEST,
    ISUP_PRM_TRANSACTION_REQUEST,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_CIRCUIT_ASSIGN_MAP,
    ISUP_PRM_GENERIC_NAME,
    ISUP_PRM_HOP_CTR,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_OPERATOR_SERVICES_INFO,
    ISUP_PRM_PRECEDENCE,
    ISUP_PRM_USER_SERVICE_INFORM_PRIME,
    ISUP_PRM_USER_TO_USER_INFORM,
    ISUP_PRM_REMOTE_OPERATIONS
#else
    ISUP_PRM_SERVICE_ACTIVATION_ANSI92,
#endif
#endif /*ANSI*/
#ifdef CCITT 
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_SERVICE_INFO,
    ISUP_PRM_OPT_FWD_CALL_INDICATORS,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE,    
    ISUP_PRM_PROP_DELAY_COUNTER,
    ISUP_PRM_USER_SERVICE_INFO_PRIME,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NUM,
    ISUP_PRM_ORIG_ISC_PC,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_GENERIC_REF,
    ISUP_PRM_MLPP_PRECEDENCE,
    ISUP_PRM_TX_MEDIUM_REQMNT_PRIME,
    ISUP_PRM_SERVICE_ACTIVATION,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_USER_TELESERVICE_INFO,
    ISUP_PRM_FORWARD_GVNS,
    ISUP_PRM_CCSS,
    ISUP_PRM_NETWORK_MANAGEMENT_CONTROLS,
    ISUP_PRM_CIRCUIT_ASSIGNMENT_MAP,
    ISUP_PRM_CORRELATION_ID,
    ISUP_PRM_CALL_DIV_TREAT_INDICATORS,
    ISUP_PRM_CALLED_IN_NUMBER,
    ISUP_PRM_CALL_OFF_TREAT_INDICATORS,
    ISUP_PRM_CONF_TREAT_INDICATORS,
    ISUP_PRM_SCF_ID,
    ISUP_PRM_UID_CAPABILITY_INDICATORS,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_HOP_COUNTER,
    ISUP_PRM_COLLECT_CALL_REQUEST,
#endif
    ISUP_PRM_LOCATION_NUM
#endif
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_IAM_Desc =
{
    ITS_TRUE,
    iamMArgs, sizeof(iamMArgs),
    iamVArgs, sizeof(iamVArgs),
    iamOArgs, sizeof(iamOArgs)
};

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
SS7DLLAPI int
ISUP_SendIAMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_IAM, hdr,
                          ies, ieCount, &ISUP_IAM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveIAMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_IAM_Desc);
}

/*** RLC ***/
#ifdef CCITT
static ITS_OCTET rlcOArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_RLC_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    rlcOArgs, sizeof(rlcOArgs)
};
#endif
#ifdef ANSI
SS7DLLAPI ISUP_MSG_DESC   ISUP_RLC_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};
#endif

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
SS7DLLAPI int
ISUP_SendRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_RLC, hdr,
                          ies, ieCount, &ISUP_RLC_Desc);
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
SS7DLLAPI int
ISUP_ReceiveRLCIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_RLC_Desc);
}

/*** REL ***/
static ITS_OCTET relVArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};
static ITS_OCTET relOArgs[] =
{
#ifdef ANSI
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_GENERIC_ADDR,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_USER_TO_USER_INFORM,
#else
    ISUP_PRM_SERVICE_ACTIVATION_ANSI92,
#endif
#endif
#ifdef CCITT 
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,

    ISUP_PRM_REDIRECTION_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SIGNALLING_POINT_CODE,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REDIRECTION_NUM_RESTRICT,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_DISPLAY_INFORMATION,
    ISUP_PRM_REMOTE_OPS,
#endif
#endif
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_AUTO_CONGEST_LEVEL
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_REL_Desc =
{
    ITS_TRUE,
    NULL, 0,
    relVArgs, sizeof(relVArgs),
    relOArgs, sizeof(relOArgs)
};


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
SS7DLLAPI int
ISUP_SendRELRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_REL, hdr,
                          ies, ieCount, &ISUP_REL_Desc);
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
SS7DLLAPI int
ISUP_ReceiveRELIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_REL_Desc);
}


/*** INF ***/
static ITS_OCTET infMArgs[] =
{
    ISUP_PRM_INFO_INDICATORS
};
static ITS_OCTET infOArgs[] =
{
#if defined ANSI
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_BUSINESS_GROUP,
    ISUP_PRM_CHARGE_NUMBER,
    ISUP_PRM_ORIG_LINE_INFO,
    ISUP_PRM_REDIRECTING_NUM,
    ISUP_PRM_REDIRECTION_INFO,
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    ISUP_PRM_USER_TO_USER_INFORM,
#endif
#endif
#ifdef CCITT
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
#endif
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CALLING_PARTY_CATEGORY,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_CONNECTION_REQ
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_INF_Desc =
{
    ITS_TRUE,
    infMArgs, sizeof(infMArgs),
    NULL, 0,
    infOArgs, sizeof(infOArgs)
};

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
SS7DLLAPI int
ISUP_SendINFRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_INF, hdr,
                          ies, ieCount, &ISUP_INF_Desc);
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
SS7DLLAPI int
ISUP_ReceiveINFIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_INF_Desc);
}

/*** INR ***/
static ITS_OCTET inrMArgs[] =
{
    ISUP_PRM_INFO_REQ_INDICATORS
};
static ITS_OCTET inrOArgs[] =
{
#ifdef ANSI
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_NTWK_TRANSPORT,
#endif
#ifdef CCITT 
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_PARAM_COMPAT_INFO,
#endif
    ISUP_PRM_CALL_REF,
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_INR_Desc =
{
    ITS_TRUE,
    inrMArgs, sizeof(inrMArgs),
    NULL, 0,
    inrOArgs, sizeof(inrOArgs)
};

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
SS7DLLAPI int
ISUP_SendINRRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_INR, hdr,
                          ies, ieCount, &ISUP_INR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveINRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_INR_Desc);
}

/*** FOT ***/
static ITS_OCTET fotOArgs[] =
{
    ISUP_PRM_CALL_REF
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_FOT_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    fotOArgs, sizeof(fotOArgs)
};

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
SS7DLLAPI int
ISUP_SendFOTRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_FOT, hdr,
                          ies, ieCount, &ISUP_FOT_Desc);
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
SS7DLLAPI int
ISUP_ReceiveFOTIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_FOT_Desc);
}


#if defined(CCITT) 
/*** FAC ***/
static ITS_OCTET facOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REMOTE_OPS,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_CALL_TRANSFER_NUMBER,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_GENERIC_NOTIFICATION,
#endif
    ISUP_PRM_SERVICE_ACTIVATION
};

#elif ANSI /* This is for ANSI */

static ITS_OCTET facOArgs[] =
{
    ISUP_PRM_REMOTE_OPERATIONS,
    ISUP_PRM_SERVICE_ACTIVATION
};

#endif

SS7DLLAPI ISUP_MSG_DESC   ISUP_FAC_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    facOArgs, sizeof(facOArgs)
};
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
SS7DLLAPI int
ISUP_SendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount,
                    TCAP_CPT *cpt)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_FAC, hdr,
                          ies, ieCount, &ISUP_FAC_Desc);
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
convert_ro_to_cpt(TCAP_CPT *cpt, ITS_ISUP_IE *ie)
{
    /*
     * I suspect this is going to be a call to the ITU TCAP codec.
     * Don't remember, this was from 1997.
     */
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
SS7DLLAPI int
ISUP_ReceiveFACIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount,
                          TCAP_CPT *cpt)
{
    int i, ret;
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL && cpt != NULL);
#endif
    ret = ISUP_ReceiveEvent(handle, event, hdr,
                            ies, ieCount, &ISUP_FAC_Desc);

    memset(cpt, 0, sizeof(TCAP_CPT));

    for (i = 0; i < *ieCount; i++)
    {
#ifdef CCITT 
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPS)
#elif ANSI
        if (ies[i].param_id == ISUP_PRM_REMOTE_OPERATIONS)
#endif
        {
            convert_ro_to_cpt(cpt, &ies[i]);
        }
    }

    return ret;
}


/*** BLO ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_BLO_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendBLORequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_BLO, hdr,
                          ies, ieCount, &ISUP_BLO_Desc);
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
SS7DLLAPI int
ISUP_ReceiveBLOIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_BLO_Desc);
}

/*** BLA ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_BLA_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendBLARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                   ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_BLA, hdr,
                          ies, ieCount, &ISUP_BLA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveBLAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_BLA_Desc);
}

/*** UBL ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_UBL_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendUBLRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_UBL, hdr,
                          ies, ieCount, &ISUP_UBL_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUBLIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_UBL_Desc);
}

/*** UBA ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_UBA_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendUBARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    /* STACK DOES THIS */
    return ISUP_SendEvent(handle, ISUP_MSG_UBA, hdr,
                          ies, ieCount, &ISUP_UBA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUBAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_UBA_Desc);
}

/*** CQM ***/
static ITS_OCTET cqmVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};

#if (defined MULTI_CLIENT && ANSI_ISUP_95)
static ITS_OCTET cqmOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};
#endif

SS7DLLAPI ISUP_MSG_DESC   ISUP_CQM_Desc =
{
    ITS_FALSE,
    NULL, 0,
    cqmVArgs, sizeof(cqmVArgs),
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    cqmOArgs, sizeof(cqmOArgs)
#else
    NULL, 0
#endif
};

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
SS7DLLAPI int
ISUP_SendCQMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CQM, hdr,
                          ies, ieCount, &ISUP_CQM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCQMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CQM_Desc);
}

/*** CQR ***/
static ITS_OCTET cqrVArgs[] =
{
    ISUP_PRM_RANGE_STATUS,
    ISUP_PRM_CKT_STATE_INDICATOR
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_CQR_Desc =
{
    ITS_FALSE,
    NULL, 0,
    cqrVArgs, sizeof(cqrVArgs),
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCQRRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CQR, hdr,
                          ies, ieCount, &ISUP_CQR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCQRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CQR_Desc);
}

/*** CGB ***/
static ITS_OCTET cgbMArgs[] =
{
    ISUP_PRM_CKT_GRP_SUPRVN_MT_IND
};
static ITS_OCTET cgbVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_CGB_Desc =
{
    ITS_FALSE,
    cgbMArgs, sizeof(cgbMArgs),
    cgbVArgs, sizeof(cgbVArgs),
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCGBRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CGB, hdr,
                          ies, ieCount, &ISUP_CGB_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCGBIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CGB_Desc);
}

/*** CGBA ***/
static ITS_OCTET cgbaMArgs[] =
{
    ISUP_PRM_CKT_GRP_SUPRVN_MT_IND
};
static ITS_OCTET cgbaVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_CGBA_Desc =
{
    ITS_FALSE,
    cgbaMArgs, sizeof(cgbaMArgs),
    cgbaVArgs, sizeof(cgbaVArgs),
    NULL, 0
};


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
SS7DLLAPI int
ISUP_SendCGBARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                     ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CGBA, hdr,
                          ies, ieCount, &ISUP_CGBA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCGBAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                           ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CGBA_Desc);
}

/*** CGU ***/
static ITS_OCTET cguMArgs[] =
{
    ISUP_PRM_CKT_GRP_SUPRVN_MT_IND
};
static ITS_OCTET cguVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_CGU_Desc =
{
    ITS_FALSE,
    cguMArgs, sizeof(cguMArgs),
    cguVArgs, sizeof(cguVArgs),
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCGURequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CGU, hdr,
                          ies, ieCount, &ISUP_CGU_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCGUIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CGU_Desc);
}

/*** CGUA ***/
static ITS_OCTET cguaMArgs[] =
{
    ISUP_PRM_CKT_GRP_SUPRVN_MT_IND
};
static ITS_OCTET cguaVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_CGUA_Desc =
{
    ITS_FALSE,
    cguaMArgs, sizeof(cguaMArgs),
    cguaVArgs, sizeof(cguaVArgs),
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                     ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CGUA, hdr,
                          ies, ieCount, &ISUP_CGUA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCGUAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                           ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CGUA_Desc);
}

/*** GRS ***/
static ITS_OCTET grsVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};

#if (defined MULTI_CLIENT && ANSI_ISUP_95)
static ITS_OCTET grsOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};
#endif

SS7DLLAPI ISUP_MSG_DESC   ISUP_GRS_Desc =
{
    ITS_FALSE,
    NULL, 0,
    grsVArgs, sizeof(grsVArgs),
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    grsOArgs, sizeof(grsOArgs)
#else
    NULL, 0
#endif
};

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
SS7DLLAPI int
ISUP_SendGRSRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_GRS, hdr,
                          ies, ieCount, &ISUP_GRS_Desc);
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
SS7DLLAPI int
ISUP_ReceiveGRSIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_GRS_Desc);
}

/*** GRA ***/
static ITS_OCTET graVArgs[] =
{
    ISUP_PRM_RANGE_STATUS
};

#if (defined MULTI_CLIENT && ANSI_ISUP_95)
static ITS_OCTET graOArgs[] =
{
    ISUP_PRM_CIRCUIT_ASSIGN_MAP
};
#endif

SS7DLLAPI ISUP_MSG_DESC   ISUP_GRA_Desc =
{
    ITS_FALSE,
    NULL, 0,
    graVArgs, sizeof(graVArgs),
#if (defined MULTI_CLIENT && ANSI_ISUP_95)
    graOArgs, sizeof(graOArgs)
#else
    NULL, 0
#endif
};

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
SS7DLLAPI int
ISUP_SendGRARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_GRA, hdr,
                          ies, ieCount, &ISUP_GRA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveGRAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_GRA_Desc);
}

/*** RSC ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_RSC_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendRSCRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_RSC, hdr,
                          ies, ieCount, &ISUP_RSC_Desc);
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
SS7DLLAPI int
ISUP_ReceiveRSCIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_RSC_Desc);
}

/*** SUS ***/
static ITS_OCTET susMArgs[] =
{
    ISUP_PRM_SUSP_RESUM_INDICATORS
};
static ITS_OCTET susOArgs[] =
{
    ISUP_PRM_CALL_REF
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_SUS_Desc =
{
    ITS_TRUE,
    susMArgs, sizeof(susMArgs),
    NULL, 0,
    susOArgs, sizeof(susOArgs)
};

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
SS7DLLAPI int
ISUP_SendSUSRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_SUS, hdr,
                          ies, ieCount, &ISUP_SUS_Desc);
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
SS7DLLAPI int
ISUP_ReceiveSUSIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_SUS_Desc);
}

/*** RES ***/
static ITS_OCTET resMArgs[] =
{
    ISUP_PRM_SUSP_RESUM_INDICATORS
};
static ITS_OCTET resOArgs[] =
{
    ISUP_PRM_CALL_REF
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_RES_Desc =
{
    ITS_TRUE,
    resMArgs, sizeof(resMArgs),
    NULL, 0,
    resOArgs, sizeof(resOArgs)
};

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
SS7DLLAPI int
ISUP_SendRESRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_RES, hdr,
                          ies, ieCount, &ISUP_RES_Desc);
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
SS7DLLAPI int
ISUP_ReceiveRESIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_RES_Desc);
}

/*** COT ***/
static ITS_OCTET cotMArgs[] =
{
    ISUP_PRM_CONTINUITY_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_COT_Desc =
{
    ITS_FALSE,
    cotMArgs, sizeof(cotMArgs),
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCOTRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_COT, hdr,
                          ies, ieCount, &ISUP_COT_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCOTIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_COT_Desc);
}

/*** CCR ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_CCR_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCCRRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CCR, hdr,
                          ies, ieCount, &ISUP_CCR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCCRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CCR_Desc);
}

/*** LPA ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_LPA_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendLPARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_LPA, hdr,
                          ies, ieCount, &ISUP_LPA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveLPAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_LPA_Desc);
}


/*** UCIC ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_UCIC_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendUCICRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_UCIC, hdr,
                          ies, ieCount, &ISUP_UCIC_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUCICIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_UCIC_Desc);
}

/*** PAM ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_PAM_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendPAMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    if (ies[0].param_id != ISUP_PRM_MSG_IN_PAM)
    {
        return (ITS_BADISUPMESSAGE);
    }

    /*
     * We are going to update the ISUP description,
     * based of the msg in the PAM (since the PAM description is "NULL").
     */
    switch (ies[0].param_data.msgTypeInPAM)
    {
    case ISUP_MSG_ACM:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_ACM_Desc);
        break;

    case ISUP_MSG_ANM:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_ANM_Desc);
        break;

    case ISUP_MSG_CFN:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_CFN_Desc);
        break;

    case ISUP_MSG_COT:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_COT_Desc);
        break;

    case ISUP_MSG_IAM:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_IAM_Desc);
        break;

    case ISUP_MSG_INF:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_INF_Desc);
        break;

    case ISUP_MSG_INR:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_INR_Desc);
        break;

    case ISUP_MSG_REL:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_REL_Desc);
        break;

    case ISUP_MSG_RLC:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_RLC_Desc);
        break;

    case ISUP_MSG_UCIC:
        return ISUP_SendEvent(handle, ISUP_MSG_PAM, hdr,
                              ies, ieCount, &ISUP_UCIC_Desc);
        break;

    default:
        return (ITS_BADISUPMESSAGE);
        break;
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
SS7DLLAPI int
ISUP_ReceivePAMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_PAM_Desc);
}


#ifdef ANSI     /* ANSI only messages */

/*** CRA ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_CRA_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCRARequest(ITS_HANDLE handle, ITS_HDR *hdr, ITS_ISUP_IE *ies,
                    int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CRA, hdr,
                          ies, ieCount, &ISUP_CRA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCRAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CRA_Desc);
}


/*** CRM ***/
static ITS_OCTET crmMArgs[] =
{   
    ISUP_PRM_NATURE_CONN_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_CRM_Desc =
{
    ITS_FALSE,
    crmMArgs, sizeof(crmMArgs),
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCRMRequest(ITS_HANDLE handle, ITS_HDR *hdr, ITS_ISUP_IE *ies,
                    int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CRM, hdr,
                          ies, ieCount, &ISUP_CRM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCRMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CRM_Desc);
}


/*** CVR ***/
static ITS_OCTET cvrMArgs[] =
{   
    ISUP_PRM_CKT_VALIDATION_RESP,
    ISUP_PRM_CKT_GRP_CHARACTERISTIC
};
static ITS_OCTET cvrOArgs[] =
{   
    ISUP_PRM_CKT_IDENTIFICATION_NAME,
    ISUP_PRM_CLLI_CODE
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_CVR_Desc =
{
    ITS_TRUE,
    cvrMArgs, sizeof(cvrMArgs),
    NULL, 0,
    cvrOArgs, sizeof(cvrOArgs)
};

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
SS7DLLAPI int
ISUP_SendCVRRequest(ITS_HANDLE handle, ITS_HDR *hdr, ITS_ISUP_IE *ies,
                    int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CVR, hdr,
                          ies, ieCount, &ISUP_CVR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCVRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CVR_Desc);
}


/*** CVT ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_CVT_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendCVTRequest(ITS_HANDLE handle, ITS_HDR *hdr, ITS_ISUP_IE *ies,
                    int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CVT, hdr,
                          ies, ieCount, &ISUP_CVT_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCVTIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CVT_Desc);
}


/*** EXM ***/
static ITS_OCTET exmOArgs[] =
{   
    ISUP_PRM_OUTGOING_TRUNK_GRP_NUM
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_EXM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    exmOArgs, sizeof(exmOArgs)
};

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
SS7DLLAPI int
ISUP_SendEXMRequest(ITS_HANDLE handle, ITS_HDR *hdr, ITS_ISUP_IE *ies,
                    int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_EXM, hdr,
                          ies, ieCount, &ISUP_EXM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveEXMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_EXM_Desc);
}
#endif      /* ANSI only messages */

#ifdef CCITT        /* CCITT only messages */ 
/*** CON ***/
static ITS_OCTET    conMArgs[] =
{
    ISUP_PRM_BKWD_CALL_INDICATORS
};

static ITS_OCTET    conOArgs[] =
{
    ISUP_PRM_OPT_BKWD_CALL_INDICATORS,
    ISUP_PRM_CONNECTED_NUM,
    ISUP_PRM_CALL_REF,
    ISUP_PRM_USER_TO_USER_INDICATORS,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_NTWK_SPECIFIC_FACILITIES,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_REMOTE_OPS,
    ISUP_PRM_TX_MEDIUM_USED,
    ISUP_PRM_ECHO_CTRL_INFO,
    ISUP_PRM_ACCESS_DELIVERY_INFO,
    ISUP_PRM_CALL_HISTORY_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_REDIRECTION_NUM,
    ISUP_PRM_SERVICE_ACTIVATION,
    ISUP_PRM_GENERIC_NUM,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_BACKWARD_GVNS,
    ISUP_PRM_CONF_TREAT_INDICATORS,
#endif
    ISUP_PRM_REDIRECTION_NUM_RESTRICT
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_CON_Desc =
{
    ITS_TRUE,
    conMArgs, sizeof(conMArgs),
    NULL, 0,
    conOArgs, sizeof(conOArgs)
};

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
SS7DLLAPI int
ISUP_SendCONRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_CON, hdr,
                          ies, ieCount, &ISUP_CON_Desc);
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
SS7DLLAPI int
ISUP_ReceiveCONIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_CON_Desc);
}


/*** FAA ***/
static ITS_OCTET faaMArgs[] =
{
    ISUP_PRM_FACILITY_INDICATOR
};
static ITS_OCTET faaOArgs[] =
{
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS,
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_FAA_Desc =
{
    ITS_TRUE,
    faaMArgs, sizeof(faaMArgs),
    NULL, 0,
    faaOArgs, sizeof(faaOArgs)
};

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
SS7DLLAPI int
ISUP_SendFAARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_FAA, hdr,
                          ies, ieCount, &ISUP_FAA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveFAAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_FAA_Desc);
}


/*** FAR ***/
static ITS_OCTET farMArgs[] =
{
    ISUP_PRM_FACILITY_INDICATOR
};
static ITS_OCTET farOArgs[] =
{
    ISUP_PRM_CALL_REF,
    ISUP_PRM_CONNECTION_REQ,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_USER_TO_USER_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_FAR_Desc =
{
    ITS_TRUE,
    farMArgs, sizeof(farMArgs),
    NULL, 0,
    farOArgs, sizeof(farOArgs)
};

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
SS7DLLAPI int
ISUP_SendFARRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_FAR, hdr,
                          ies, ieCount, &ISUP_FAR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveFARIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_FAR_Desc);
}


/*** FRJ ***/
static ITS_OCTET frjMArgs[] =
{
    ISUP_PRM_FACILITY_INDICATOR
};
static ITS_OCTET frjVArgs[] =
{
    ISUP_PRM_CAUSE_INDICATORS
};
static ITS_OCTET frjOArgs[] =
{
    ISUP_PRM_USER_TO_USER_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_FRJ_Desc =
{
    ITS_TRUE,
    frjMArgs, sizeof(frjMArgs),
    frjVArgs, sizeof(frjVArgs),
    frjOArgs, sizeof(frjOArgs)
};

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
SS7DLLAPI int
ISUP_SendFRJRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_FRJ, hdr,
                          ies, ieCount, &ISUP_FRJ_Desc);
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
SS7DLLAPI int
ISUP_ReceiveFRJIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_FRJ_Desc);
}


/*** IDR ***/
static ITS_OCTET idrOArgs[] =
{
    ISUP_PRM_MCID_REQ_INDICATOR,
    ISUP_PRM_MSG_COMPAT_INFO,
#if (defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_CHARGED_PARTY_IDENTIFICATION,
#endif
    ISUP_PRM_PARAM_COMPAT_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_IDR_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    idrOArgs, sizeof(idrOArgs)
};

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
SS7DLLAPI int
ISUP_SendIDRRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_IDR, hdr,
                          ies, ieCount, &ISUP_IDR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveIDRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_IDR_Desc);
}

#ifdef CCITT /* LOP */ 
/*
 * LOOP PREVENTION (LOP)
 * This message is specific to ITU97 variant
 */
static ITS_OCTET lopOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALL_TRANSFER_REFERENCE,
    ISUP_PRM_LOOP_PREVENTION_INDICATORS
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_LOP_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    lopOArgs, sizeof(lopOArgs)
};

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Send LOP.
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
SS7DLLAPI int
ISUP_SendLOPRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL && ies != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_LOP, hdr,
                          ies, ieCount, &ISUP_LOP_Desc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Receive LOP.
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
SS7DLLAPI int
ISUP_ReceiveLOPIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_LOP_Desc);
}
#endif /* LOP */

/*** IRS ***/
static ITS_OCTET irsOArgs[] =
{
    ISUP_PRM_MCID_RESP_INDICATOR,
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
    ISUP_PRM_CALLING_PARTY_NUM,
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_GENERIC_NUM
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_IRS_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    irsOArgs, sizeof(irsOArgs)
};

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
SS7DLLAPI int
ISUP_SendIRSRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_IRS, hdr,
                          ies, ieCount, &ISUP_IRS_Desc);
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
SS7DLLAPI int
ISUP_ReceiveIRSIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_IRS_Desc);
}

/*** NRM ***/
static ITS_OCTET nrmOArgs[] =
{
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_PARAM_COMPAT_INFO,
#if !(defined MULTI_CLIENT && ITU_ISUP_97)
    ISUP_PRM_TX_MEDIUM_USED,
#endif
    ISUP_PRM_ECHO_CTRL_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_NRM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    nrmOArgs, sizeof(nrmOArgs)
};

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
SS7DLLAPI int
ISUP_SendNRMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_NRM, hdr,
                          ies, ieCount, &ISUP_NRM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveNRMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_NRM_Desc);
}

/*** OLM ***/
SS7DLLAPI ISUP_MSG_DESC   ISUP_OLM_Desc =
{
    ITS_FALSE,
    NULL, 0,
    NULL, 0,
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendOLMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_OLM, hdr,
                          ies, ieCount, &ISUP_OLM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveOLMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_OLM_Desc);
}


/*** SAM ***/
static ITS_OCTET samVArgs[] =
{
    ISUP_PRM_SUBSEQUENT_NUM
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_SAM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    samVArgs, sizeof(samVArgs),
    NULL, 0
};

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
SS7DLLAPI int
ISUP_SendSAMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_SAM, hdr,
                          ies, ieCount, &ISUP_SAM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveSAMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_SAM_Desc);
}


/*** SGM ***/
static ITS_OCTET sgmOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT,
    ISUP_PRM_MSG_COMPAT_INFO,
    ISUP_PRM_GENERIC_DIGITS,
    ISUP_PRM_GENERIC_NOTIFICATION,
    ISUP_PRM_USER_TO_USER_INFO,
    ISUP_PRM_GENERIC_NUM
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_SGM_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    sgmOArgs, sizeof(sgmOArgs)
};

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
SS7DLLAPI int
ISUP_SendSGMRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_SGM, hdr,
                          ies, ieCount, &ISUP_SGM_Desc);
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
SS7DLLAPI int
ISUP_ReceiveSGMIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_SGM_Desc);
}


/*** USR ***/
static ITS_OCTET usrVArgs[] =
{
    ISUP_PRM_USER_TO_USER_INFO
};

static ITS_OCTET usrOArgs[] =
{
    ISUP_PRM_ACCESS_TRANSPORT
};
SS7DLLAPI ISUP_MSG_DESC   ISUP_USR_Desc =
{
    ITS_TRUE,
    NULL, 0,
    usrVArgs, sizeof(usrVArgs),
    usrOArgs, sizeof(usrOArgs)
};

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
0 *  Return Value:
 *      None.
 ****************************************************************************/
SS7DLLAPI int
ISUP_SendUSRRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_USR, hdr,
                          ies, ieCount, &ISUP_USR_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUSRIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_USR_Desc);
}

/*** UPT ***/
static ITS_OCTET uptOArgs[] =
{
    ISUP_PRM_PARAM_COMPAT_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_UPT_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    uptOArgs, sizeof(uptOArgs)
};

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
SS7DLLAPI int
ISUP_SendUPTRequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_UPT, hdr,
                          ies, ieCount, &ISUP_UPT_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUPTIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_UPT_Desc);
}

/*** UPA ***/
static ITS_OCTET upaOArgs[] =
{
    ISUP_PRM_PARAM_COMPAT_INFO
};

SS7DLLAPI ISUP_MSG_DESC   ISUP_UPA_Desc =
{
    ITS_TRUE,
    NULL, 0,
    NULL, 0,
    upaOArgs, sizeof(upaOArgs)
};

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
SS7DLLAPI int
ISUP_SendUPARequest(ITS_HANDLE handle, ITS_HDR *hdr,
                    ITS_ISUP_IE *ies, int ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && hdr != NULL);
#endif

    return ISUP_SendEvent(handle, ISUP_MSG_UPA, hdr,
                          ies, ieCount, &ISUP_UPA_Desc);
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
SS7DLLAPI int
ISUP_ReceiveUPAIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    return ISUP_ReceiveEvent(handle, event, hdr,
                             ies, ieCount, &ISUP_UPA_Desc);
}

#endif /* CCITT only messages */


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
SS7DLLAPI int
ISUP_ReceiveTimeoutIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                              ITS_ISUP_IE *ies, int *ieCount)
{
    int ret = ITS_SUCCESS;
    int offset = 0, index = 0;
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    /* skip the message type,vcic  and cic */
    offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &event->data[offset], sizeof(MTP3_HEADER));

    offset += sizeof(MTP3_HEADER);

    /* copy the timeout data over */
    ies[1].param_id = ISUP_PRM_TIMEOUT_DATA;
    ies[1].param_length = sizeof(ISUP_TIMER_ENTRY);
    memcpy(&ies[1].param_data.timerData,
           &event->data[offset], sizeof(ISUP_TIMER_ENTRY));

    /* populate the ie count */
    *ieCount = 2;

    index += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* populate header */
    hdr->type = ITS_ISUP;
    hdr->context.cic = (event->data[index - sizeof(ITS_OCTET)] << 8) |
                        event->data[index - sizeof(ITS_USHORT)];

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
SS7DLLAPI int
ISUP_ReceiveErrorIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                          ITS_ISUP_IE *ies, int *ieCount)
{
    int ret = ITS_SUCCESS;
    int offset = 0, index =0;
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    /* skip the message type,vcic  and cic */
    offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &event->data[offset], sizeof(MTP3_HEADER));

    offset += sizeof(MTP3_HEADER);

    /* copy the error data over */
    ies[1].param_id = ISUP_PRM_ERROR_DATA;
    ies[1].param_length = sizeof(ISUP_ERROR_ENTRY);
    memcpy(&ies[1].param_data.errorData,
           &event->data[offset], sizeof(ISUP_ERROR_ENTRY));

    /* populate the ie count */
    *ieCount = 2;

    index += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* populate header */
    hdr->type = ITS_ISUP;
    hdr->context.cic = (event->data[index - sizeof(ITS_OCTET)] << 8) |
                        event->data[index - sizeof(ITS_USHORT)];
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
SS7DLLAPI int
ISUP_ReceiveIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                       ITS_ISUP_IE *ies, int *ieCount)
{
    int ret = ITS_SUCCESS;
    int offset = 0, index = 0;
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    /* skip the message type,vcic  and cic */
    offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &event->data[offset], sizeof(MTP3_HEADER));

    offset += sizeof(MTP3_HEADER);

    /* copy the error data over */
    ies[1].param_id = ISUP_PRM_INDICATION_DATA;
    ies[1].param_length = sizeof(ISUP_INDICATION_ENTRY);
    memcpy(&ies[1].param_data.indData,
           &event->data[offset], sizeof(ISUP_INDICATION_ENTRY));

    /* populate the ie count */
    *ieCount = 2;

    index += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* populate header */
    hdr->type = ITS_ISUP;
    hdr->context.cic = (event->data[index - sizeof(ITS_OCTET)] << 8) |
                        event->data[index - sizeof(ITS_USHORT)];
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
SS7DLLAPI int
ISUP_ReceiveMgmtIndication(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr,
                       ITS_ISUP_IE *ies, int *ieCount)
{
    int ret = ITS_SUCCESS;
    int offset = 0, index = 0;
#ifdef DEBUG
    assert(handle != NULL && event != NULL && hdr != NULL &&
           ies != NULL && ieCount != NULL);
#endif

    /* skip the message type,vcic  and cic */
    offset += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* copy the MTP3 header over */
    ies[0].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);
    memcpy(&ies[0].param_data.routingLabel,
           &event->data[offset], sizeof(MTP3_HEADER));

    offset += sizeof(MTP3_HEADER);

    /* copy the mgmt data over */
    ies[1].param_id = ISUP_PRM_MGMTIND_DATA;
    ies[1].param_length = sizeof(ISUP_MTP3MGMT_ENTRY);
    memcpy(&ies[1].param_data.indData,
           &event->data[offset], sizeof(ISUP_MTP3MGMT_ENTRY));

    /* populate the ie count */
    *ieCount = 2;

    index += sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT);

    /* populate header */
    hdr->type = ITS_ISUP;
    hdr->context.cic = (event->data[index - sizeof(ITS_OCTET)] << 8) |
                        event->data[index - sizeof(ITS_USHORT)];
    return (ret);
}

