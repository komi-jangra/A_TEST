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
 *  ID: $Id: ansi-trp.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/05/30 11:39:45  adutta
 * LOG: XUDT implementation in ANSI
 * LOG:
 * LOG: Revision 9.3  2005/05/05 06:41:46  adutta
 * LOG: Fix for #1751
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:33:45  yranade
 * LOG: Implementation of changes based on design doc ACC651-SDS-TCEN-V1.0.02
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.14  2005/03/21 13:53:40  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.8.2.1.12.4  2005/02/21 14:49:11  sbabu
 * LOG: TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.8.2.8.2.1.12.3  2005/02/03 10:20:52  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.8.2.8.2.1.12.2  2005/01/31 09:32:45  dsatish
 * LOG: ANSI over TTC, ANSI over PRC split stack changes merged in DVLP branch.
 * LOG:
 * LOG: Revision 7.8.2.8.2.1.12.1  2004/12/31 09:08:03  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.8.2.1  2004/02/16 12:58:21  yranade
 * LOG: TCAP Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.8.2.8  2003/11/25 11:23:45  ssingh
 * LOG: Bug #685, Handling of P-Abort from Network in QWOP_SENT state changed.
 * LOG:
 * LOG: Revision 7.8.2.7  2003/11/25 09:40:16  ssingh
 * LOG: Bug #681, handling of RESP and ABORT from Application been
 * LOG: corrected in case of CWOP_SENT transection state.
 * LOG: Also changed is handling of RESP/ABORT from Network in case
 * LOG: of CWOP_RCVD transection state.
 * LOG:
 * LOG: Revision 7.8.2.6  2003/04/08 15:01:25  yranade
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 7.8.2.5  2003/04/07 09:04:24  vjatti
 * LOG: Fix for Bug 193.
 * LOG: Bug 193. Don't update the state before call to TPCPIHandleTRPMsg_ANSI.
 * LOG: Add the check for  states ITS_TCAP_QWOP_SENT & ITS_TCAP_QWIP_SENT.
 * LOG:
 * LOG: Revision 7.8.2.4  2003/04/02 05:18:11  vjatti
 * LOG: Fix Bug 232. Invoke timer not getting cleared on receipt of
 * LOG: an ABORT for the transaction to abort.
 * LOG: The Invoke context was not getting cleared for the transaction context
 * LOG: to be terminated on receipt of an ABORT.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/03/27 11:50:58  yranade
 * LOG: Free sharedTx when sharedTx != NULL, Bug Fix: 201: Propagate from 6.2.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/03/10 07:41:47  vjatti
 * LOG: Fix for bug 236
 * LOG:
 * LOG: Revision 7.8.2.1  2003/03/04 13:20:08  vjatti
 * LOG: Fix for Bug 230
 * LOG:
 * LOG: Revision 7.8  2003/02/13 05:18:29  yranade
 * LOG: Fixes for errors caused while committing alarm changes.
 * LOG:
 * LOG: Revision 7.7  2003/02/07 11:47:17  tsanthosh
 * LOG: Modified to add some tcap alarms and pegs.
 * LOG:
 * LOG: Revision 7.6  2003/02/06 10:14:20  vjatti
 * LOG: PR 6.2 Fixes propagated
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.4  2002/11/14 22:27:20  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.3  2002/10/15 19:40:34  omayor
 * LOG: Use correct includes
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:22:39  omayor
 * LOG: Minimization of DSM calls
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.9  2002/07/29 17:56:22  ngoel
 * LOG: increment total message peg
 * LOG:
 * LOG: Revision 6.8  2002/07/16 16:24:03  labuser
 * LOG: Remove the error trace. (clin)
 * LOG:
 * LOG: Revision 6.7  2002/07/09 14:28:36  omayor
 * LOG: ANSI-96 changes after testing in PR5 ported to current. Now to be tested.
 * LOG:
 * LOG: Revision 6.6  2002/07/03 21:19:48  mmiers
 * LOG: Fixes for DSM, VFrame
 * LOG:
 * LOG: Revision 6.5  2002/06/14 19:29:02  mmiers
 * LOG: Change signature
 * LOG:
 * LOG: Revision 6.4  2002/06/12 21:32:37  mmiers
 * LOG: Add ANSI abort processing.
 * LOG:
 * LOG: Revision 6.3  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.2  2002/03/01 23:12:06  mmiers
 * LOG: Start the DSM/pegs/alarms merge.  ANSI-TCAP done, 3 left.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2001/02/08 23:37:32  mmiers
 * LOG: Need to find the correct trCtxt for UDTS/XUDTS.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:31  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/04/27 19:22:07  mmiers
 * LOG:
 * LOG:
 * LOG: Don't barf on a CONVERSATION with a bad TID.
 * LOG:
 * LOG: Revision 2.1  2000/04/17 21:36:32  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes to ANSI TCAP.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:29  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.14  1999/10/05 19:01:03  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.13  1999/09/07 21:02:31  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.12  1999/08/31 15:00:02  rsonak
 * LOG:
 * LOG:
 * LOG: Work around not finding a TransactionContext when receiving a begin.
 * LOG: Correct allocation code to not look for the TID in the local
 * LOG: table if it is a new incoming dialogue.
 * LOG:
 * LOG: Revision 1.11  1999/08/27 16:50:12  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.10  1999/08/26 23:44:57  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.9  1999/08/26 02:21:57  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.8  1999/06/15 22:32:06  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.7  1999/05/27 21:46:07  mmiers
 * LOG:
 * LOG:
 * LOG: Adjust the TID management for sanity.
 * LOG:
 * LOG: Revision 1.6  1999/05/27 15:52:46  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.5  1999/05/24 20:31:19  mmiers
 * LOG:
 * LOG:
 * LOG: Codecs have moved into shared library.
 * LOG:
 * LOG: Revision 1.4  1999/05/12 22:54:12  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1999/05/11 00:54:34  mmiers
 * LOG:
 * LOG:
 * LOG: Slight bug fixes.
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:50  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 20:55:06  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.20  1999/03/17 18:40:00  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.19  1998/12/14 23:45:31  rsonak
 * LOG: Tracking down the AT&T routing label bug.  Fixed.
 * LOG:
 * LOG: Revision 1.18  1998/12/10 20:03:36  rsonak
 * LOG: Reflect the MTP3 header when external systems invoke us.
 * LOG:
 * LOG: Revision 1.17  1998/11/19 01:32:23  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.16  1998/10/15 01:19:28  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.15  1998/10/02 23:18:37  jrao
 * LOG: Apparently, even though the SDL says not, you can send multiple
 * LOG: conversation package types in a row.
 * LOG:
 * LOG: Revision 1.14  1998/10/02 00:42:13  mmiers
 * LOG: Fix some major CPT handling bugs in TCAP (cmp).
 * LOG:
 * LOG: Revision 1.13  1998/09/30 21:54:41  jrao
 * LOG: Make UNI work with invokes.  Basically, we don't allocate an invoke
 * LOG: context for INVOKE's received in a UNI.  Need to verify this with
 * LOG: T1.114.
 * LOG:
 * LOG: Revision 1.12  1998/09/21 17:20:11  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.11  1998/09/15 19:09:46  whu
 * LOG: Move SCCP address encode/decode to one location for simplification.
 * LOG:
 * LOG: Revision 1.10  1998/09/10 21:00:25  whu
 * LOG: Must have point code when handling UDT, XUDT messages in SCCP.  Need to
 * LOG: check that the PC received in a UDT is the "localPC" in TCAP.  HOLE.
 * LOG:
 * LOG: Revision 1.9  1998/07/17 16:27:13  ahanda
 * LOG: Correct logic for TIDs where local end did NOT originate the transaction.
 * LOG:
 * LOG: Revision 1.8  1998/07/08 20:01:09  mmiers
 * LOG: More work on TCAP rejects.
 * LOG:
 * LOG: Revision 1.7  1998/07/08 16:46:02  mmiers
 * LOG: Restructure the reject method a little differently.
 * LOG:
 * LOG: Revision 1.6  1998/07/08 16:39:16  mmiers
 * LOG: Start thinking about reject cases.  Group into a common function.
 * LOG:
 * LOG: Revision 1.5  1998/07/03 19:42:20  mmiers
 * LOG: SCCP as a separate thread.
 * LOG:
 * LOG: Revision 1.4  1998/06/29 19:27:22  mmiers
 * LOG: Convert TCAP to use SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:30  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:38:44  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:34  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.17  1998/06/16 21:52:11  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.16  1998/05/05 20:24:10  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.15  1998/04/29 22:45:03  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.
 * LOG:
 * LOG: Revision 1.14  1998/04/29 21:10:20  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.13  1998/04/29 00:23:18  mmiers
 * LOG: Start putting in context functions.  Should be starting debug
 * LOG: tommorrow.
 * LOG:
 * LOG: Revision 1.12  1998/04/28 22:52:00  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.11  1998/04/23 23:53:53  mmiers
 * LOG: More work on TCAP.  Down to about 30 fixme's.
 * LOG:
 * LOG: Revision 1.10  1998/04/23 17:04:04  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.9  1998/04/23 02:33:02  mmiers
 * LOG: More work on our TCAP implementation.  Made this single threaded,
 * LOG: multiple threads didn't buy anything, but did cost a *bunch* of
 * LOG: unnecessary hops between threads.  We're down to 3/2 hops in/out
 * LOG: of a process.
 * LOG:
 * LOG: Revision 1.8  1998/04/16 16:40:04  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.7  1998/04/03 16:50:09  mmiers
 * LOG: Update tcap internals.
 * LOG:
 * LOG: Revision 1.6  1998/03/20 02:53:10  mmiers
 * LOG: Add some preliminary code for tpcpi<->trp communication.
 * LOG:
 * LOG: Revision 1.5  1998/03/20 02:47:46  mmiers
 * LOG: More work on TCAP.  I think I've got the way for TPCPI to talk to TRP, and
 * LOG: TRP to talk to SCCP.  Need to translate to/from SCCP_IE sooner than I thought.
 * LOG: May need to have a non-standard way to talk to/from TPCPI to TRP (dialogue id,
 * LOG: pType).
 * LOG:
 * LOG: Revision 1.4  1998/03/19 16:34:39  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/03/13 04:46:45  mmiers
 * LOG: For the most part, TCAP modifications.  Quite a few of these files are false
 * LOG: positive due to timestamps.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:15:07  mmiers
 * LOG: More on the TCAP implementation.  By the end of the weekend, I expect a
 * LOG: preliminary implementation of ANSI TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:36  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>
#include <string.h>

#undef CCITT
#undef ANSI
#undef PRC
#undef TTC
#define ANSI

#include <its.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_dsm.h>

#ident "$Id: ansi-trp.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include <ansi/tcap.h>

#include "sccp_intern.h"
#include "tcap_intern.h"

#if defined(SPLIT_STACK)
#if defined(USE_TTC_SCCP)
#define WHICH_STACK     (ITS_HANDLE)ISS7_TTC_Stack
#elif defined(USE_PRC_SCCP)
#define WHICH_STACK     (ITS_HANDLE)ISS7_PRC_Stack
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_CCITT_Stack
#endif
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_ANSI_Stack
#endif

extern ITS_BOOLEAN isMsgBasedRedundancy;

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
TRPHandleCMPMsg_ANSI(ITS_EVENT *event)
{
    TCAP_TRANS_ENTRY *trCtxt;
    TCAP_TRANS_ENTRY *sharedTx;
    ITS_CTXT did;

    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;
    int ret = ITS_SUCCESS;

    did = ITS_GET_CTXT(&event->data[1]);

    TCAP_DEBUG(("TRPHandleCMPMsg: did %d\n", did));

    trCtxt = TCAP_FindLocalTx_ANSI(did);

    if (trCtxt == NULL)
    {
        /* error condition */
        TCAP_ERROR(("TRPHandleCMPMsg: no Local Trans context\n"));

        /* Unable to commit transaction context to table */

        return ITS_BADTCAPMESSAGE;
    }

    sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey, 
                                                &tidKeyLen);
    if (sharedTx == NULL)
    {
        /* error condition */
        TCAP_ERROR(("TRPHandleCMPMsg: no Local Trans context\n"));
        return ITS_BADTCAPMESSAGE;
    }

    if (trCtxt->state == ITS_TCAP_QWOP_SENT)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_QWIP_SENT)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_QWOP_RCVD)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_QWIP_RCVD)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_CWOP_SENT)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_CWIP_SENT)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_CWOP_RCVD)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else if (trCtxt->state == ITS_TCAP_CWIP_RCVD)
    {
        TCAP_FreeDSMTransactionContext_ANSI(sharedTx);

        TCAP_FreeLocalTx_ANSI(did);

        TCAP_ERROR(("TRPHandleCMPMsg: this shouldn't happen did %d\n", did));
    }
    else
    {
        /* error condition */
        TCAP_DEBUG(("TRPHandleCMPMsg: unknown state did %d\n", did));

        ret = DSM_Commit(DSM_TcapFtGroupId,
                         DSM_TABLE_ANSI_TCAP_DLG, 
                         tidKey, tidKeyLen, 
                         (void *)sharedTx);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleCMPMsg, DSM_Commit "
                        "returned code: %d, did %d\n", ret, did));
         
            /* Unable to Commit Transaction Context to Table. */
       }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The event structure expects the package type in octet 0 of the data,
 *      the dialogue id in octets 1 and 2 of the data.
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
 *
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     05-04-2005  PBN Bug ID#1751         Error trace is seen during 
 *                                               success message exchange  
 *
 *                                              
 *
 ****************************************************************************/
int
TRPHandleTPCPIMsg_ANSI(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount)
{
    TCAP_TRANS_ENTRY* trCtxt = NULL;
    TCAP_TRANS_ENTRY* sharedTx = NULL;
    ITS_OCTET pType, ssn;
    ITS_UINT tid1 = 0, tid2 = 0;
    SCCP_ADDR cdp, clp;
    ITS_HDR hdr;
    ITS_UINT pc = 0;
    MTP3_HEADER *mtp3 = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0, ret = ITS_SUCCESS;
    ITS_BOOLEAN sendToSCCP = ITS_FALSE;

    memset(&cdp, 0, sizeof(SCCP_ADDR));
    memset(&clp, 0, sizeof(SCCP_ADDR));

    TCAP_DEBUG(("TRPHandleTPCPIMsg:\n"));

    trCtxt = TCAP_FindLocalTx_ANSI(did);
    if (trCtxt == NULL)
    {
        TCAP_ERROR(("TCOHandleCSLMsg: Missing Local Tx for did %d ",
                    did));
        
        /* Unable to commit transaction conext to table */
    }

    if (FindPTypeAndTID_ANSI(ies, ieCount, &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        TCAP_ERROR(("TRPHandleTPCPIMsg: Could not successfully decode "
                    "PType/TID\n"));
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        /* Outgoing Message - Discarding Message - Invalid or Corrupted. */
        TCAP_FreeLocalTx_ANSI(did);
        return (ITS_SUCCESS);
    }

    if (did & TCAP_DIR_BIT) /* originated by remote */
    {
        int i;

        /* can't be a QWIP or QWOP.  Has to be RESP or CWIP, CWOP */
        TCAP_DEBUG(("TRPHandleTPCPIMsg: remote msg:\n"));
        TCAP_DEBUG(("   ptype: %02x tid1 %08x tid2 %08x\n", pType, tid1, tid2));

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                mtp3 = &ies[i].param_data.routingLabel;
                break;
            }
        }

        /*
         * this looks like paranoia, especially after the trouble
         * we went through in DHA to build the point codes
         * (BuildRoutingLabel). However, it's only here that we concern
         * ourselves with it, so we repeat it here out of paranoia.
         * Think this through so that the user can specify a
         * different point code than that specified in the SCCP address.
         * I think this is fixed but it needs testing: fixme.
         */
        if (mtp3 != NULL)
        {
            MTP3_POINT_CODE tmp1, tmp2;

            if (trCtxt != NULL)
            {
                MTP3_POINT_CODE tmp1, tmp2;

                *mtp3 = trCtxt->label;

                MTP3_RL_GET_OPC(mtp3->label, tmp1);
                MTP3_RL_GET_DPC(mtp3->label, tmp2);
                MTP3_RL_SET_OPC(mtp3->label, tmp2);
                MTP3_RL_SET_DPC(mtp3->label, tmp1);
            }
            else
            {
                MTP3_RL_GET_OPC(mtp3->label, tmp1);
                MTP3_RL_GET_DPC(mtp3->label, tmp2);
                MTP3_RL_SET_OPC(mtp3->label, tmp2);
                MTP3_RL_SET_DPC(mtp3->label, tmp1);
            }

            TCAP_DEBUG(("SendPackage: opc %08x dpc %08x\n",
                        MTP3_RL_GET_OPC_VALUE(mtp3->label),
                        MTP3_RL_GET_DPC_VALUE(mtp3->label)));
        }
        else if (trCtxt != NULL)
        {
            MTP3_POINT_CODE tmp1, tmp2;

            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = trCtxt->label;
            MTP3_RL_GET_OPC(ies[ieCount].param_data.routingLabel.label,
                            tmp1);
            MTP3_RL_GET_DPC(ies[ieCount].param_data.routingLabel.label,
                            tmp2);
            MTP3_RL_SET_OPC(ies[ieCount].param_data.routingLabel.label,
                            tmp2);
            MTP3_RL_SET_DPC(ies[ieCount].param_data.routingLabel.label,
                            tmp1);
            ieCount++;
        }
    }
    else /* originated locally */
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: local msg:\n"));
        TCAP_DEBUG(("   ptype: %02x tid1 %08x tid2 %08x\n",
                    pType, tid1, tid2));
    }

    hdr.type = ITS_TCAP;
    SCCP_DecodeAddr(&clp, NULL, &pc, &ssn, NULL, NULL);
    hdr.context.ssn = ssn;

    if (trCtxt == NULL)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: NULL trCtxt.\n"));

        /* something's foul */
        TCAP_ERROR(("TRPHandleTPCPIMsg: NULL trCtxt for did %d\n", did));
        
        /* Outgoing Message - Discarding Message - NULL trCtxt. */

        return ITS_SUCCESS;
    }
    else if (trCtxt->state == ITS_TCAP_IDLE)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: TCAP_IDLE State.  New transaction.\n"));

        switch (pType)
        {
        case TCPPT_TC_UNI:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_UNI_SENT);
          
            sendToSCCP = ITS_TRUE;

            /* TBD
            TCAP_CleanInvokeContext_ANSI(did);
            */
            break;

        case TCPPT_TC_QUERY_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_QWIP_SENT);

            trCtxt->state = ITS_TCAP_QWIP_SENT;

            /* new transaction need to allocate */
            sharedTx = TCAP_AllocTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for did"
                            "%d", did));

                TCAP_FreeLocalTx_ANSI(did);
                return ITS_SUCCESS;
            }

            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_QUERY_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_QWOP_SENT);

            trCtxt->state = ITS_TCAP_QWOP_SENT;

            /* new transaction need to allocate */
            sharedTx = TCAP_AllocTransactionContext_ANSI(trCtxt->ltid,
                                                          tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for did"
                            "%d", did));

                TCAP_FreeLocalTx_ANSI(did);
                return ITS_SUCCESS;
            }

            sendToSCCP = ITS_TRUE;

            break;

        default:

            /* something's foul */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.: %02x\n",
                        pType));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_ANSI(1043, __FILE__, __LINE__,
                            "Dialog_Id %X PType %X", did, pType);

            TCAP_FreeLocalTx_ANSI(did);

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return ITS_SUCCESS;
        }
    }
    else if (trCtxt->state == ITS_TCAP_QWOP_RCVD ||
             trCtxt->state == ITS_TCAP_QWOP_SENT)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: state is QWOP_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_WO_PERM:
        case TCPPT_TC_CONV_W_PERM:

            if (pType == TCPPT_TC_CONV_WO_PERM)
            {
                trCtxt->state = ITS_TCAP_CWOP_SENT;
            }
            else if (pType == TCPPT_TC_CONV_W_PERM)
            {
                trCtxt->state = ITS_TCAP_CWIP_SENT;
            }

            /* Yogi: Do we need a DSM lookup here?
             * Why do a FindTransactionContext, since in the QWIP_RCVD
             * state we can be sure that it won't exist. In fact if
             * it exists it should amount to an error condition.
             * I don't really think it affects redundancy...but I am not sure
             * so although not changing the code. Just adding this comment.
             */

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d", did));

                /* new transaction need to allocate */
                /* This might be the first Continue going out as a
                   Response to an Incoming Begin. So there is no
                   DSM Tx for it at this point*/

                sharedTx = TCAP_AllocTransactionContext_ANSI(trCtxt->ltid,
                                                          tidKey, &tidKeyLen);

                if (sharedTx == NULL)
                {
                    TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for "
                                "did %d", did));

                    TCAP_FreeLocalTx_ANSI(did);
                    return ITS_SUCCESS;
                }
            }

            if (pType == TCPPT_TC_CONV_WO_PERM)
            {
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);
            }
            else
            {
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);
            }

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

            sendToSCCP = ITS_TRUE;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_ANSI(1044, __FILE__, __LINE__,
                            "Dialog_Id %X PType %X", did, pType);

            TCAP_FreeLocalTx_ANSI(did);

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
        }
    }
    else if (trCtxt->state == ITS_TCAP_QWIP_RCVD ||
             trCtxt->state == ITS_TCAP_QWIP_SENT)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: state is QWIP_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_WO_PERM:
        case TCPPT_TC_CONV_W_PERM:

            if (pType == TCPPT_TC_CONV_WO_PERM)
            {
                trCtxt->state = ITS_TCAP_CWOP_SENT;
            }
            else if (pType == TCPPT_TC_CONV_W_PERM)
            {
                trCtxt->state = ITS_TCAP_CWIP_SENT;
            }

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d", did));

                /* new transaction need to allocate */
                /* This might be the first Continue going out as a
                   Response to an Incoming Begin. So there is no
                   DSM Tx for it at this point*/

                sharedTx = TCAP_AllocTransactionContext_ANSI(trCtxt->ltid,
                                                          tidKey, &tidKeyLen);

                if (sharedTx == NULL)
                {
                    TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for "
                                "did %d", did));

                    TCAP_FreeLocalTx_ANSI(did);
                    return ITS_SUCCESS;
                }
            }

            if (pType == TCPPT_TC_CONV_WO_PERM)
            {
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);
            }
            else
            {
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);
            }

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_RESP:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_RESP_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

        /*
         * TBD: Do we need this? Use DSM on receiving side?
         */
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            sendToSCCP = ITS_TRUE;

            TCAP_FreeLocalTx_ANSI(did);

            trCtxt = NULL;

            break;

        case TCPPT_TC_ABORT:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_ABORT_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
             
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            TCAP_FreeLocalTx_ANSI(did);

            sendToSCCP = ITS_TRUE;

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_ANSI(1045, __FILE__, __LINE__,
                            "Dialog_Id %X PType %X", did, pType);
 
            TCAP_FreeLocalTx_ANSI(did);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        }
    }
    else if (trCtxt->state == ITS_TCAP_CWOP_RCVD)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: state is CWOP_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

            trCtxt->state = ITS_TCAP_CWIP_SENT;

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_CONV_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);

            trCtxt->state = ITS_TCAP_CWOP_SENT;
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }

            sendToSCCP = ITS_TRUE;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_ANSI(1041, __FILE__, __LINE__,
                            "Dialog_Id %X PType %X", did, pType);

            TCAP_FreeLocalTx_ANSI(did);

            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
        }
    }
    else if (trCtxt->state == ITS_TCAP_CWOP_SENT)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: state is CWOP_SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);

            trCtxt->state = ITS_TCAP_CWIP_SENT;

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }

            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_CONV_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);

            trCtxt->state = ITS_TCAP_CWOP_SENT;
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }

            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_RESP:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_RESP_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
 
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            if (trCtxt->prearranged)
            {
                TCAP_FreeLocalTx_ANSI(did);
            }
            else
            {
                TCAP_FreeLocalTx_ANSI(did);

                sendToSCCP = ITS_TRUE;
            }

            trCtxt = NULL;

            break;

        case TCPPT_TC_ABORT:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS); 

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            TCAP_FreeLocalTx_ANSI(did);

            sendToSCCP = ITS_TRUE;

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            

            TCAP_FreeLocalTx_ANSI(did);
        }
    }
    else if (trCtxt->state == ITS_TCAP_CWIP_RCVD ||
             trCtxt->state == ITS_TCAP_CWIP_SENT)
    {
        TCAP_DEBUG(("TRPHandleTPCPIMsg: state is CWIP_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_W_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWIP_SENT);

            trCtxt->state = ITS_TCAP_CWIP_SENT;
            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }

            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_CONV_WO_PERM:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CWOP_SENT);

            trCtxt->state = ITS_TCAP_CWOP_SENT;

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            sendToSCCP = ITS_TRUE;

            break;

        case TCPPT_TC_RESP:
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_RESP_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            if (trCtxt->prearranged)
            {
               TCAP_FreeLocalTx_ANSI(did);
            }
            else
            {
                TCAP_FreeLocalTx_ANSI(did);

                sendToSCCP = ITS_TRUE;
            }

            trCtxt = NULL;

            break;

        case TCPPT_TC_ABORT:
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_ABORT_SENT);

            PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

            sharedTx = TCAP_FindTransactionContext_ANSI(trCtxt->ltid,
                                                         tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }
            else
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
            }

            TCAP_FreeLocalTx_ANSI(did);

            sendToSCCP = ITS_TRUE;

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_ANSI(1042, __FILE__, __LINE__,
                            "Dialog_Id %X PType %X", did, pType);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        }
    }
    else
    {
        /* error condition */
        TCAP_ERROR(("TRPHandleTPCPIMsg: Invalid state for PType.\n"));
            
        /* Outgoing Message - Discarding Message - Invalid State. */
     

        TCAP_FreeLocalTx_ANSI(did);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
    }

    /* - DSM Stuff - commit any changes made to the  */
    /*  only if the message is a Begin or a Continue */

    if (pType == TCPPT_TC_QUERY_W_PERM ||
        pType == TCPPT_TC_QUERY_WO_PERM || 
        pType == TCPPT_TC_CONV_W_PERM ||
        pType == TCPPT_TC_CONV_WO_PERM) 
    {
        /* copy local ctxt in the DSM */
        memcpy(sharedTx, trCtxt, sizeof(TCAP_TRANS_ENTRY));

        ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG,
                         tidKey, tidKeyLen, (void *)sharedTx);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleTPCPIMsg_ANSI: DSM_Commit "
                        "failed, error code: %d\n", ret));

            /* Unable to Commit Transaction Context to Table. */
        }
        else
        {
            TCAP_DEBUG(("TRPHandleTPCPIMsg: DSM-Commit the DSM Tx for did %d,"
                        " pType = %d\n", did, pType));
        }

        /* Clean up local Tx */

        /* Don't free the did from the LocalTxTable here - Commenting it out
        TCAP_FreeLocalTx_ANSI(did);
        */
    }
    else
    {
         PEG_DecrPeg(ANSI_TCAP_Pegs,PEG_TCAP_ACTIVE_DIALOGUE);
         
         TCAP_DEBUG(("TRPHandleTPCPIMsg: No DSM-Commits; Message is neither Begin"
                     " nor a Continue: pType = %d for did %d\n", pType, did));
    }

    if (sendToSCCP)
    {
        if (isMsgBasedRedundancy)
        {
            ITS_EVENT dummyEvent;
            ITS_UINT  dest;
            ITS_HDR dummyHdr;

            TCAP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

            dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
            dummyEvent.data = 0;

            dummyHdr.type = ITS_TCAP;
            dummyHdr.context.dialogue_id = did;

            dest = ROUTE_SelectApplication(&dummyHdr, &dummyEvent, ITS_TRUE);

            if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
            {
                /* Don't send message for routing to the network */
                TCAP_WARNING(("Message is consumed by TCAP: DID = 0x%x\n", did));

                return ITS_SUCCESS;
            }
        }

        SCCP_SendUnitData(WHICH_STACK, &hdr, ies, ieCount);
    }

    return (ITS_SUCCESS);
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
 *  Notes:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005   ACC651-SDS-TCEN-V1.0.02  Free CptList in case of
 *                        ID :: D0060              Abort
 *                                              
 * csireesh  20-05-2005   ID::R0170 to R0210       XUDT/XUDTS Implementation
 *
 ****************************************************************************/
int
TRPHandleSCCPMsg_ANSI(ITS_EVENT *event)
{
    TCAP_TRANS_ENTRY *localTx = NULL, *sharedTx = NULL;
    ITS_OCTET pType = 0;
    ITS_UINT tid1 = 0, tid2 = 0;
    SCCP_ADDR cdp, clp;
    ITS_OCTET type;
    ITS_SCCP_IE ies[32];
    int ieCount, i;
    ITS_HDR hdr;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;
    int ret = ITS_SUCCESS;
    ITS_CTXT did = 0;
    TCAP_INVOKE_ENTRY *cptCtxt;
    TCAP_CPT_LIST *cptList = NULL;

    memset(&cdp, 0, sizeof(SCCP_ADDR));
    memset(&clp, 0, sizeof(SCCP_ADDR));

    type = SCCP_MSG_TYPE(event);

    /* Count SCCP Msg Received by Type */
    TCAP_DEBUG(("TRPHandleSCCPMsg: SCCPmsgType %02x.\n", type));

    switch (type)
    {
    case SCCP_MSG_UDT:

        if (SCCP_ReceiveUnitData(WHICH_STACK, event,
                                 &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP: Couldn't receive UDT.\n"));
        
            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }

        break;

    case SCCP_MSG_XUDT:
        
        if (SCCP_ReceiveExtendedUnitData(WHICH_STACK, event,
                                         &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP: Couldn't receive XUDT.\n"));
        
            /* Unable to retrive incoming message. */
           

            return (ITS_SUCCESS);
        }
        
        
        break;

    case SCCP_MSG_UDTS:
        
        if (SCCP_ReceiveUnitDataService(WHICH_STACK, event,
                                        &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP: Couldn't receive UDTS.\n"));
        
            /* Unable to retrive incoming message. */
       
            return (ITS_SUCCESS);
        }
 
        break;

    case SCCP_MSG_XUDTS:
        
        if (SCCP_ReceiveExtendedUnitDataService(WHICH_STACK,
                                                event,
                                                &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP: Couldn't receive XUDTS.\n"));
        
            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_LUDT:
        if (SCCP_ReceiveLongUnitData(WHICH_STACK, event,
                                     &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP: Couldn't receive LUDT.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    default:
        TCAP_ERROR(("TRPHandleSCCP: SCCP message is neither UDT nor XUDT\n"));

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_INVALID_SCCP_RCVD);

        /* Incoming Message - Discarding Message - Invalid or Corrupted. */

        return (ITS_SUCCESS);
    }

    if (FindPTypeAndTID_ANSI(ies, ieCount,
                             &pType, &tid1, &tid2,
                             &cdp, &clp) == ITS_NO)
    {
        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_DLG_SEND_APP_FAIL); 
        PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_MSG_DISCARDED);

        if (pType)
        {
             TCAP_Alarm_ANSI(1053, __FILE__, __LINE__, "PType %X",pType); 

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                TCAP_ERROR(("TRPHandleSCCP: Incorrect Transaction Portion, send ABORT.\n"));

                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI);
            }
            else
            {
                TCAP_ERROR(("TRPHandleSCCP: Incorrect Transaction Portion, send REJECT.\n"));

                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_TRANS_ID);
            }
        }
        else
        {
            TCAP_Alarm_ANSI(1048, __FILE__, __LINE__,
                            "PType %X Transaction-id %X",pType,tid2);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                TCAP_ERROR(("TRPHandleSCCP: bad package type, send ABORT.\n"));

                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                TCAP_ERROR(("TRPHandleSCCP: bad package type, send REJECT.\n"));

                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }
        }
        return (ITS_SUCCESS);
    }

    if (type == SCCP_MSG_UDTS || type == SCCP_MSG_XUDTS)
    {
        /* Olivier TODO, FIXME the following does not make sense as we look 
           for a Ctx and then pass NULL no matter what, I think we dont need
           to look for a context here since we just send NOTICE to the user
           end then return an error.....*/

        sharedTx = TCAP_FindTransactionContext_ANSI(tid1,
                                                    tidKey, &tidKeyLen);
        if (sharedTx != NULL)
        {
             localTx = TCAP_CopyDSMTxToLocalTx_ANSI(sharedTx);

             TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
        }

        if (localTx != NULL)
        {
            TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx);
        }

        return (ITS_SUCCESS);

    } /* if */


    /* handle a completely new transaction */
    switch (pType)
    {
    case TCPPT_TC_UNI:
        /* send to TPCPI */
        TCAP_DEBUG(("TRPHandleSCCPMsg: handle UNI.\n"));

        if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, NULL) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
        }

        return (ITS_SUCCESS);

    case TCPPT_TC_QUERY_W_PERM:
    case TCPPT_TC_QUERY_WO_PERM:
        /* DID 0 is ok here (in fact required), the Alloc routine will
         * create a DID for us */

        ret = TCAP_GetNextIDID_ANSI(&did);
        if (ret != ITS_SUCCESS)
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_RES_UNAVAIL_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCAP_PROB_TRANS_PORTION_ANSI,
                                            TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI);
            }

            /* Incoming Message - Discarding Message - Rejection Sent by stack. */

            return (ITS_SUCCESS);
        }

        localTx =  TCAP_AllocateLocalTx_ANSI(did);

        /* unavailable resources */
        if (localTx == NULL)
        {
            /* what to do.  ANSI has no ABORT, so we'll try a REJECT */
            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_RES_UNAVAIL_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCAP_PROB_TRANS_PORTION_ANSI,
                                            TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI);
            }

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */

            return (ITS_SUCCESS);
        }

        AllocateLTIDinTx_ANSI(localTx);

        /* TBD : What should be the tid1Len? Puting it zero for now!! */

        ret = TCAP_PopulateLocalTx_ANSI(localTx, did, tid1, 0, &cdp, &clp);
        if (ret != ITS_SUCCESS)
        {
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_RES_UNAVAIL_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCAP_PROB_TRANS_PORTION_ANSI,
                                            TCAP_PROB_SPEC_TRANS_RES_UNAVAIL_ANSI);
            }

            TCAP_FreeLocalTx_ANSI(did);


            return (ITS_SUCCESS);
        }

        /* send to TPCPI */
        if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
        } /* if */

        if (pType == TCPPT_TC_QUERY_W_PERM)
        { 
            localTx->state = ITS_TCAP_QWIP_RCVD;
        }
        else if (pType == TCPPT_TC_QUERY_WO_PERM)
        {
            localTx->state = ITS_TCAP_QWOP_RCVD;
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
            {
                localTx->label = ies[i].param_data.routingLabel;

                break;
            }
        }

        return (ITS_SUCCESS);
    }

    /*
     * If we get here, we've gotten an indication for a transaction
     * already in progress
     */
    if (pType == TCPPT_TC_CONV_W_PERM || pType == TCPPT_TC_CONV_WO_PERM)
    {
        /* either way (transaction initiator or receiver), we've got
         * a local entry already */
        sharedTx = TCAP_FindTransactionContext_ANSI(tid2, tidKey, &tidKeyLen);
   
        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_ANSI(sharedTx);

           /* We simply commit here (just for the sake of Unlock).
            * We will operate on localTx, and we will do the 'real'
            * commit when sending response out
            */ 

            ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG,
                             tidKey, tidKeyLen,
                             (void *)sharedTx);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCOHandleSCCPMsg_ANSI: DSM_Commit failed "
                            "returned code: %d\n", ret));

                /* Unable to Commit Transaction Context to Table. */
                 
            }
        }
        else
        {
            TCAP_Alarm_ANSI(1047, __FILE__, __LINE__,
                            "Transaction-id %X", tid2);

            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                           "%u.\n", tid2));

            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCPABT_REASON_UNREC_TRANS_ID);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCAP_PROB_TRANS_PORTION_ANSI,
                                            TCPPROB_SPEC_TRANS_UNREC_TRANS_ID);
            }
            
            /* Incoming Message - Discarding Message - Rejection Sent by stack. */
              PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

             return ITS_SUCCESS;
        }

        if (localTx)
        {
            localTx->rtid = tid1;
        }
    }
    else if (pType == TCPPT_TC_RESP)
    {
        sharedTx = TCAP_FindTransactionContext_ANSI(tid2, tidKey, &tidKeyLen);

        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_ANSI(sharedTx);

            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", localTx->did));

            TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
        }
        else
        {
            TCAP_Alarm_ANSI(1047, __FILE__, __LINE__,
                            "Transaction-id %X", tid2);

            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));

            return ITS_SUCCESS;
        }
    }
    else if (pType == TCAP_PT_TC_ABORT_ANSI)
    {
        sharedTx = TCAP_FindTransactionContext_ANSI(tid2, tidKey, &tidKeyLen);

        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_ANSI(sharedTx);

            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", localTx->did));

            TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
        }
        else
        {
           TCAP_Alarm_ANSI(1047, __FILE__, __LINE__,
                            "Transaction-id %X", tid2);

            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));

            return ITS_SUCCESS;
        }
    }
    else
    {
        /* something really bad happened to get here */
         
         TCAP_Alarm_ANSI(1048, __FILE__, __LINE__,
                        "PType %X Transaction-id %X",pType,tid2);

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            TCAP_ERROR(("TRPHandleSCCP: bad package type, send ABORT.\n"));

            __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                       TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
        }
        else
        {
            TCAP_ERROR(("TRPHandleSCCP: bad package type, send REJECT.\n"));

            __TCAP_SendTransReject_ANSI(ies, ieCount,
                                        TCPPROB_TRANS_PORTION,
                                        TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
         PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);  

        sharedTx = TCAP_FindTransactionContext_ANSI(tid2, tidKey, &tidKeyLen);

        if (sharedTx)
        {
            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", sharedTx->did));

            TCAP_FreeDSMTransactionContext_ANSI(sharedTx);
        }

        return ITS_SUCCESS;
    }

    if (localTx == NULL)
    {
        TCAP_ERROR(("TRPHandleSCCP: bad TID(s), send REJECT.\n"));

        /* If variant == ANSI-88, send REJECT.  Else send ABORT */
        if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
        {
            __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                       TCAP_ABT_REASON_UNREC_TRANS_ID_ANSI);
        }
        else
        {
            __TCAP_SendTransReject_ANSI(ies, ieCount,
                                        TCPPROB_TRANS_PORTION,
                                        TCPPROB_SPEC_TRANS_UNREC_TRANS_ID);
        }

        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_ANSI(1053, __FILE__, __LINE__, "PType %X",pType);
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        return (ITS_SUCCESS);
    }

/* The following is equivalent to ITU's TSMHandleTCOSCCPmessage */

    if (localTx->state == ITS_TCAP_QWOP_SENT)
    {
        TCAP_DEBUG(("TRPHandleSCCP: state is QWOP SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_W_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWIP_RCVD;
            break;

        case TCPPT_TC_CONV_WO_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWOP_RCVD;
            break;

        case TCPPT_TC_ABORT:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            /* Update as per Design ID :: D0060 */
            cptList = &localTx->cptList;
            while (cptList != NULL)
            {
                for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                {
                    if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                    {
                        if (localTx->did == cptCtxt->did)
                        {
                            TCAP_FreeInvokeContext_ANSI(cptCtxt);
                        }
                    }
                }
                cptList = cptList->next;
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);

            localTx = NULL;

            break;

        default:
            
            TCAP_ERROR(("TRPHandleSCCP: bad pType for state, send REJECT.\n"));

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);
            
            localTx = NULL;

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1056, __FILE__, __LINE__,
                            "PType %X Dialog-Id %X",pType, did);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            break;
        }
    }
    else if (localTx->state == ITS_TCAP_QWIP_SENT)
    {
        TCAP_DEBUG(("TRPHandleSCCP: state is QWIP SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_W_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWIP_RCVD;
            break;

        case TCPPT_TC_CONV_WO_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWOP_RCVD;
            break;

        case TCPPT_TC_RESP:
        case TCPPT_TC_ABORT:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }
           
            if (pType == TCPPT_TC_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &localTx->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if (localTx->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_ANSI(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                }
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);
            
            localTx = NULL;

            break;

        default:
            TCAP_ERROR(("TRPHandleSCCP: bad pType for state, send REJECT.\n"));

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);
            
            localTx = NULL;

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1057, __FILE__, __LINE__,
                            "PType %X Dialog-Id %X",pType, did);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            break;
        }
    }
    else if (localTx->state == ITS_TCAP_CWOP_SENT)
    {
        TCAP_DEBUG(("TRPHandleSCCP: state is CWOP_SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_WO_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWOP_RCVD;
            break;

        case TCPPT_TC_CONV_W_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWIP_RCVD;
            break;

        default:
            TCAP_ERROR(("TRPHandleSCCP: bad pType for state, send REJECT.\n"));

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);
            
            localTx = NULL;

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
             TCAP_Alarm_ANSI(1058, __FILE__, __LINE__,
                            "PType %X Dialog-Id %X",pType, did);

            break;
        }
    }
    else if (localTx->state == ITS_TCAP_CWOP_RCVD)
    {
        TCAP_DEBUG(("TRPHandleSCCP: state is CWOP_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_WO_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWOP_RCVD;
            break;

        case TCPPT_TC_CONV_W_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWIP_RCVD;
            break;

        case TCPPT_TC_RESP:
        case TCPPT_TC_ABORT:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            } /* if */

            if (pType == TCPPT_TC_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &localTx->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if (localTx->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_ANSI(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                }
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);

            localTx = NULL;

            break;

        default:
            TCAP_ERROR(("TRPHandleSCCP: bad pType for state, send REJECT.\n"));

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);
            
            localTx = NULL;

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1058, __FILE__, __LINE__,
                            "PType %X Dialog-Id %X",pType, did);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            break;
        }
    }
    else if (localTx->state == ITS_TCAP_CWIP_SENT ||
             localTx->state == ITS_TCAP_CWIP_RCVD)
    {
        TCAP_DEBUG(("TRPHandleSCCP: state is CWIP SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONV_WO_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWOP_RCVD;
            break;

        case TCPPT_TC_CONV_W_PERM:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            }

            localTx->state = ITS_TCAP_CWIP_RCVD;
            break;

        case TCPPT_TC_RESP:
        case TCPPT_TC_ABORT:
            /* send to TPCPI */
            if (TPCPIHandleTRPMsg_ANSI(ies, ieCount, localTx) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TRP couldn't send event to TPCPI.\n"));
            } /* if */
            
            if (pType == TCPPT_TC_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &localTx->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if (localTx->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_ANSI(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                }
            }
 
            TCAP_FreeLocalTx_ANSI(localTx->did);

            localTx = NULL;

            break;

        default:
            TCAP_ERROR(("TRPHandleSCCP: bad pType for state, send REJECT.\n"));

            /* If variant == ANSI-88, send REJECT.  Else send ABORT */
            if (ANSI_TCAP_Variant > ANSI_TCAP_1988)
            {
                __TCAP_SendTransAbort_ANSI(ies, ieCount,
                                           TCAP_ABT_REASON_UNREC_PACK_TYPE_ANSI);
            }
            else
            {
                __TCAP_SendTransReject_ANSI(ies, ieCount,
                                            TCPPROB_TRANS_PORTION,
                                            TCPPROB_SPEC_TRANS_UNREC_PACK_TYPE);
            }

            TCAP_FreeLocalTx_ANSI(localTx->did);

            localTx = NULL;

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
             TCAP_Alarm_ANSI(1059, __FILE__, __LINE__,
                            "PType %X Dialog-Id %X",pType, did);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            break;
        }
    }
    else
    {
        /* error condition */
        TCAP_ERROR(("TRPHandleSCCP: bad state for pType.\n"));
        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        /* Invalid state for primitive type */

        TCAP_FreeLocalTx_ANSI(localTx->did);

        localTx = NULL;

    }

#if 0
    /*
     *Do we really need to commit the sharedTx in DSM here?
     *We are going to operate on localTx only till we send out the message.
     */

    if (trCtxt != NULL)
    {
        ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG, 
                         tidKey, keyLen, 
                         (void *)trCtxt);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TRPHandleSCCP, DSM_Commit "
                        "returned code: %d\n", ret));

            /* Unable to Commit Transaction Context to Table. */
        }
    }
#endif

    return (ITS_SUCCESS);
}
