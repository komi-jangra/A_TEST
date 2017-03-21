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
 *  ID: $Id: ansi-cmp.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:30  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:05  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:53:29  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.3.2.1.12.2  2005/02/21 14:47:45  sbabu
 * LOG: TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.7.2.3.2.1.12.1  2004/12/31 08:58:31  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.3.2.1  2004/02/16 09:19:45  mmanikandan
 * LOG: Performance Improvement.
 * LOG:
 * LOG: Revision 7.7.2.3  2003/12/22 06:50:49  ssingh
 * LOG: Bug #682, Fixed handling  for INVOKE_NL with unassigned correlationId.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/11/26 06:43:30  ssingh
 * LOG: Function CMPHandleTPCPIMsg is re-organised and fix for bug #682
 * LOG: is been put. re-organisagion is taken from current and costomised.
 * LOG:
 * LOG: Revision 7.7.2.1  2003/04/09 08:55:37  yranade
 * LOG: ITS_CTXT related updates.
 * LOG:
 * LOG: Revision 7.7  2003/02/07 11:41:36  tsanthosh
 * LOG: Modified to add some tcap alarms and tcap pegs.
 * LOG:
 * LOG: Revision 7.6  2003/02/06 10:14:20  vjatti
 * LOG: PR 6.2 Fixes propagated
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:23:33  mmiers
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
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:24:33  labuser
 * LOG: Fix for UNI message. (clin)
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
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:26  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:02  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:21  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:20  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.9  1999/10/05 19:01:01  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.8  1999/10/01 14:48:30  mmiers
 * LOG:
 * LOG:
 * LOG: Remove "fileValid" check.  This looks "under the hood" inside
 * LOG: the resource database mechanism and cannot be relied on.
 * LOG:
 * LOG: Revision 1.7  1999/09/09 14:14:01  lbana
 * LOG:
 * LOG:
 * LOG: Remove NULL pointer dereference as per Lakshma
 * LOG:
 * LOG: Revision 1.6  1999/09/07 21:02:29  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.5  1999/08/27 16:50:10  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.4  1999/08/26 23:44:51  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.3  1999/08/26 15:24:12  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.2  1999/08/25 22:40:52  mmiers
 * LOG:
 * LOG:
 * LOG: Sanity checks.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 20:55:05  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.21  1999/03/17 18:39:45  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.20  1999/02/17 20:45:26  mmiers
 * LOG:
 * LOG:
 * LOG: Get ITU conversion to compile.
 * LOG:
 * LOG: Revision 1.19  1998/10/15 01:19:04  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.18  1998/10/09 16:52:50  mmiers
 * LOG: Remove potential core dump.
 * LOG:
 * LOG: Revision 1.17  1998/10/02 23:18:36  jrao
 * LOG: Apparently, even though the SDL says not, you can send multiple
 * LOG: conversation package types in a row.
 * LOG:
 * LOG: Revision 1.16  1998/10/02 16:40:57  jrao
 * LOG: Fix cmp handling (missing returns).
 * LOG:
 * LOG: Revision 1.15  1998/10/02 04:05:39  mmiers
 * LOG: Improve TCAP component handling.  The only thing that needs verification
 * LOG: is reject handling.
 * LOG:
 * LOG: Revision 1.14  1998/10/02 00:42:12  mmiers
 * LOG: Fix some major CPT handling bugs in TCAP (cmp).
 * LOG:
 * LOG: Revision 1.13  1998/09/30 21:54:39  jrao
 * LOG: Make UNI work with invokes.  Basically, we don't allocate an invoke
 * LOG: context for INVOKE's received in a UNI.  Need to verify this with
 * LOG: T1.114.
 * LOG:
 * LOG: Revision 1.12  1998/09/21 17:20:08  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.11  1998/09/11 18:34:46  whu
 * LOG: Fix timer handling for TCAP invokes.  Was copying the wrong portion of the
 * LOG: returned timer context.
 * LOG:
 * LOG: Revision 1.10  1998/09/06 20:05:47  mmiers
 * LOG: Convert to using ROUTE_SendToApplication where possible.
 * LOG:
 * LOG: Revision 1.9  1998/07/08 16:46:00  mmiers
 * LOG: Restructure the reject method a little differently.
 * LOG:
 * LOG: Revision 1.8  1998/07/08 16:39:14  mmiers
 * LOG: Start thinking about reject cases.  Group into a common function.
 * LOG:
 * LOG: Revision 1.7  1998/07/07 23:53:40  mmiers
 * LOG: Fix copy bug (copy was from wrong event).
 * LOG:
 * LOG: Revision 1.6  1998/07/07 21:11:40  mmiers
 * LOG: Fixes for TCAP timers.
 * LOG:
 * LOG: Revision 1.5  1998/07/01 23:34:20  mmiers
 * LOG: Finish coding INVOKE timers.  Now to debug.
 * LOG:
 * LOG: Revision 1.4  1998/07/01 22:53:35  mmiers
 * LOG: Add timer support in.
 * LOG:
 * LOG: Revision 1.3  1998/07/01 21:57:57  mmiers
 * LOG: Fix TCAP.
 * LOG:
 * LOG: Revision 1.2  1998/06/25 00:22:57  ahanda
 * LOG: Make sure the source for an event is defined (ITS_TCAP).
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:29  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.18  1998/05/20 20:15:28  mmiers
 * LOG: Get test8 (process framework) compiled and linked.  Not
 * LOG: all code is linked in (no sending yet, which will cause more
 * LOG: undefined externals).
 * LOG:
 * LOG: Revision 1.17  1998/05/19 18:04:50  mmiers
 * LOG: More on TCAP++.
 * LOG:
 * LOG: Revision 1.16  1998/05/19 15:49:27  mmiers
 * LOG: Fix the namespace problems.
 * LOG:
 * LOG: Revision 1.15  1998/05/19 02:38:49  mmiers
 * LOG: Modify itu/tcap.h to remove the redundant structures (such as rrl/rrnl,
 * LOG: uerror/lerror, etc.).  If you have problems with this, update tcap.h
 * LOG: using "cvs update -r 1.11 tcap.h (for itu/tcap.h).
 * LOG:
 * LOG: Revision 1.14  1998/05/05 20:24:08  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.13  1998/04/29 22:45:01  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.
 * LOG:
 * LOG: Revision 1.12  1998/04/29 21:10:17  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.11  1998/04/28 22:51:59  mmiers
 * LOG: Complete the pepsy<->ITS conversion code.  This is pretty close to
 * LOG: actually working, now.  Must fill in the context management functions
 * LOG: and then debug.
 * LOG:
 * LOG: Revision 1.10  1998/04/23 23:53:51  mmiers
 * LOG: More work on TCAP.  Down to about 30 fixme's.
 * LOG:
 * LOG: Revision 1.9  1998/04/23 17:04:02  mmiers
 * LOG: Bring TCAP along.  Assembly/disassembly is written.
 * LOG:
 * LOG: Revision 1.8  1998/04/23 02:33:01  mmiers
 * LOG: More work on our TCAP implementation.  Made this single threaded,
 * LOG: multiple threads didn't buy anything, but did cost a *bunch* of
 * LOG: unnecessary hops between threads.  We're down to 3/2 hops in/out
 * LOG: of a process.
 * LOG:
 * LOG: Revision 1.7  1998/04/23 00:11:30  mmiers
 * LOG: Working on TCAP now.
 * LOG:
 * LOG: Revision 1.6  1998/04/16 16:40:02  mmiers
 * LOG: Build on NT, reduce error count.  Need to finish this.
 * LOG:
 * LOG: Revision 1.5  1998/04/03 16:50:08  mmiers
 * LOG: Update tcap internals.
 * LOG:
 * LOG: Revision 1.4  1998/03/19 16:34:37  mmiers
 * LOG: More work on TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/03/13 04:46:44  mmiers
 * LOG: For the most part, TCAP modifications.  Quite a few of these files are false
 * LOG: positive due to timestamps.
 * LOG:
 * LOG: Revision 1.2  1998/03/13 04:15:06  mmiers
 * LOG: More on the TCAP implementation.  By the end of the weekend, I expect a
 * LOG: preliminary implementation of ANSI TCAP.
 * LOG:
 * LOG: Revision 1.1  1998/03/11 23:05:34  mmiers
 * LOG: TCAP implementation for ANSI.  Not quite there yet.
 * LOG:
 * LOG: Revision 1.1.1.1  1997/11/04 20:13:16  mmiers
 * LOG: Baseline
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_types.h>
#include <its_emlist.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_dsm.h>

#ident "$Id: ansi-cmp.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/tcap.h>

#include "tcap_intern.h"

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
CMPHandleAPPMsg_ANSI(ITS_EVENT *event)
{
    TCAP_INVOKE_ENTRY *cptCtxt;
    TCAP_CPT cpt;
    ITS_CTXT did;

    did = ITS_GET_CTXT(&event->data[1]);
    memcpy(&cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    TCAP_DEBUG(("CMPHandleAppMsg: did %04x, cpt ptype: %02x\n",
                did, cpt.ptype));

    /*
     * First, check to see if this is a new outgoing operation
     */

    /* note that this is legal for all components as they all have
     * invoke ID in the same place in their structure */
    cptCtxt = TCAP_FindInvokeContext_ANSI(did, &cpt.u.invoke.invoke_id,
                                          INV_OUTGOING);

    if (cptCtxt == NULL)
    {
        TCAP_ERROR(("Cannot find Cpt Entry for did %d, inv_id %d.\n",
                     did, cpt.u.invoke.invoke_id));

        return (ITS_ENOMEM);
    }

    if (!cptCtxt->inUse)
    {
        /* must be new if this is true */
        if (cpt.ptype == TCPPT_TC_INVOKE ||
            cpt.ptype == TCPPT_TC_INVOKE_NL)
        {
            /*
             * an INVOKE_NL cannot be the first invoke in a transaction,
             * I think.  If it could, what would it not be terminating?
             */
            if (cpt.ptype == TCPPT_TC_INVOKE_NL &&
                cpt.u.invoke.correlation_id.len == 0)
            {
                TCAP_ERROR(("CMPHandleAppMsg: Can't initiate remote op with "
                            "INVOKE_NL.\n"));

                __TCAP_SendAppReject_ANSI(did, &cpt,
                                          TCPPROB_INVOKE,
                                          TCPPROB_SPEC_INV_UNREC_COREL_ID,
                                          ITS_TRUE);
               PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
               PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);    
                                 
               TCAP_FreeInvokeContext_ANSI(cptCtxt);

                /* Minor - Outgoing Component - Discarding Component - Rejection Sent by stack. */
                TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X", did, cpt.ptype);

                return (ITS_SUCCESS);
            }


            /*
             * We need to check the correlation id here.  This
             * INVOKE may be in response to one we've received.
             * If so, IF THIS IS INVOKE LAST, only then do we terminate
             * the original invoke.
             */
            if (cpt.u.invoke.correlation_id.len != 0 &&
                cpt.ptype == TCPPT_TC_INVOKE)
            {
                TCAP_DEBUG(("CMPHandleAPPMsg: Terminating correlated invoke "
                            "%02x\n", cpt.u.invoke.linked_id.data[2]));

                cptCtxt = TCAP_FindInvokeContext_ANSI(did,
                                                   &cpt.u.invoke.correlation_id,
                                                   INV_INCOMING);

                if (cptCtxt->inUse)
                {
                    if (cptCtxt->state != ITS_CPT_OP_IN_PROG)
                    {
                        TCAP_ERROR(("CMPHandleTPCPIMsg: invalid state for "
                                    "component.\n"));

                        /* Outgoing Component - Discarding Component  - Invalid State. */
                    }

                    TCAP_FreeInvokeContext_ANSI(cptCtxt);
                }
                else /* grounds for reject */
                {
                    __TCAP_SendAppReject_ANSI(did, &cpt,
                                              TCPPROB_INVOKE,
                                              TCPPROB_SPEC_INV_UNREC_COREL_ID,
                                              ITS_TRUE);
                    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
                    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED); 
                
                    /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                    TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                                        "Dialog-Id %X Component-Type %X",did,cpt.ptype);

                    return (ITS_SUCCESS);

                }
            }

            TCAP_DEBUG(("CMPHandleAppMsg: new remote operation\n"));

            if (TCAP_AllocInvokeContext_ANSI(did, &cpt,
                                cptCtxt, INV_OUTGOING) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP cant allocate invoke "
                            "context.\n"));

                TCAP_FreeInvokeContext_ANSI(cptCtxt);

                return (!ITS_SUCCESS);
            }

            /* Send to TPCPI (just enqueue it) */
            if (TPCPIHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send event to "
                            "TPCPI.\n"));

                TCAP_FreeInvokeContext_ANSI(cptCtxt);

                return (ITS_SUCCESS);
            }
            else
            {
                cptCtxt->state = ITS_CPT_OP_PENDING;

            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_INVOKE_SENT);
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT); 
           } 

            /* invoke has been handled */
            return (ITS_SUCCESS);
        }
        else
        {
            /* else case is fall thru to match against pending
              outbound invokes */
        }
    }
    else /* context is inUse */
    {
        /* look for cancel */
        if (cpt.ptype == TCPPT_TC_CANCEL)
        {
            TCAP_WARNING(("CMPHandleAppMsg: remote operation canceled\n"));

            TCAP_FreeInvokeContext_ANSI(cptCtxt);

            if (TRPHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send CANCEL "
                            "to TRP.\n"));
            }

            return (ITS_SUCCESS);
        }
        else if (cpt.ptype == TCPPT_TC_INVOKE ||
                 cpt.ptype == TCPPT_TC_INVOKE_NL)
        {
            TCAP_ERROR(("CMPHandleAppMsg: App attempted to send while "
                        "remote operation pending.\n"));

            __TCAP_SendAppReject_ANSI(did, &cpt,
                                      TCPPROB_INVOKE,
                                      TCPPROB_SPEC_INV_DUPLICATE_INV_ID,
                                      ITS_TRUE);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);  

            /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                 did, cpt.ptype); 
            return (ITS_SUCCESS);
        }
        else
        {
            /* fallthru for spurious match on RRL, RRNL, ERR, REJ for
             * previously recieved invokes */
        }
    }

    /*
     * next, check to see if we're sending in response to a received
     * invoke.
     */
    /* note that this is legal for all components as they all have
     * invoke ID in the same place in their structure */
    cptCtxt = TCAP_FindInvokeContext_ANSI(did, &cpt.u.invoke.invoke_id,
                                          INV_INCOMING);

    if (cptCtxt == NULL)
    {
        TCAP_ERROR(("NULL CptContext for did %d.\n", did));
        return (ITS_ENOMEM);
    }

    if (!cptCtxt->inUse) /* can't find the operation we're sending to */
    {
        int inv = 0;
        if (cpt.u.invoke.invoke_id.data[1] == 2)
        {
            inv = cpt.u.invoke.invoke_id.data[3];
        }
        else
        {
            inv = cpt.u.invoke.invoke_id.data[2];
        }
        TCAP_ERROR(("CMPHandleAppMsg: attempt to send component to "
                    "non existent operation\n"));
        
        PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_CMP_DISCARDED);
        PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED); 
        switch (cpt.ptype)
        {
        case TCPPT_TC_RESULT_L:
        case TCPPT_TC_RESULT_NL:
            __TCAP_SendAppReject_ANSI(did, &cpt,
                                      TCPPROB_RETURN_RES,
                                      TCPPROB_SPEC_RES_UNEXPECTED_RET_RES,
                                      ITS_TRUE);
            
            /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                did, cpt.ptype);
            break;

        case TCPPT_TC_ERROR:
            __TCAP_SendAppReject_ANSI(did, &cpt,
                                      TCPPROB_RETURN_ERR,
                                      TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR,
                                      ITS_TRUE);
            
            /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                did, cpt.ptype);

            break;
        }
    }
    else /* we were waiting on the application */
    {
        TCAP_DEBUG(("CMPHandleAppMsg: application response to invocation.\n"));

        switch (cpt.ptype)
        {

        case TCPPT_TC_ERROR:
            TCAP_DEBUG(("CMPHandleAppMsg: responding to invoke with "
                        "ERROR.\n"));

            event->src = ITS_TCAP_SRC;

            if (TPCPIHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send event to "
                            "TPCPI.\n"));
            }
            
            else
                {
                    PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_ERROR_SENT);
                    PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_APP_MSG_SENT);
                }

            TCAP_FreeInvokeContext_ANSI(cptCtxt);

            break;

        case TCPPT_TC_RESULT_L:
            TCAP_DEBUG(("CMPHandleAppMsg: responding to invoke with "
                        "RESULT_LAST.\n"));

            event->src = ITS_TCAP_SRC;

            if (TPCPIHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send event to "
                            "TPCPI.\n"));
            }
            else
            {
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_RESULT_SENT);
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            }

            TCAP_FreeInvokeContext_ANSI(cptCtxt);

            break;

        case TCPPT_TC_RESULT_NL:
            TCAP_DEBUG(("CMPHandleAppMsg: responding to invoke with "
                        "RESULT_NOT_LAST.\n"));

            event->src = ITS_TCAP_SRC;

            if (TPCPIHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send event to "
                            "TPCPI.\n"));
            }
            else
            {
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_RESULT_SENT);
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            }
 
            /*
             * In this case, we don't free the local context: the application
             * isn't done responding.
             */

            break;

        case TCPPT_TC_REJECT:
            TCAP_WARNING(("CMPHandleAppMsg: remote operation REJECT.\n"));

            event->src = ITS_TCAP_SRC;

            if (TPCPIHandleCMPMsg_ANSI(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CMPHandleAppMsg: CMP couldn't send event to "
                            "TPCPI.\n"));
            }
            else
            {
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);
            	PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            }

            TCAP_FreeInvokeContext_ANSI(cptCtxt);

            break;

        case TCPPT_TC_INVOKE:
        case TCPPT_TC_INVOKE_NL:
            TCAP_ERROR(("CMPHandleAppMsg: This should be impossible.\n"));
            TCAP_ERROR(("CMPHandleAppMsg: duplicate invoke while op "
                        "progress.\n"));

            /* this is definitely an error */
            __TCAP_SendAppReject_ANSI(did, &cpt,
                                      TCPPROB_INVOKE,
                                      TCPPROB_SPEC_INV_DUPLICATE_INV_ID,
                                      ITS_TRUE);
            
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
            PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED); 
            
            /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
             TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                        "Dialog-Id %X Component-Type %X",
                        did, cpt.ptype);
 
            break;

        default:
            TCAP_WARNING(("CMPHandleAppMsg: Send reject on bad component.\n"));
            __TCAP_SendAppReject_ANSI(did, &cpt,
                                      TCPPROB_GENERAL,
                                      TCPPROB_SPEC_GEN_UNREC_COMP,
                                      ITS_TRUE);

             PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
             PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
 
            /* Minor - Outgoing Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_ANSI(1001, __FILE__, __LINE__,
                        "Dialog-Id %X Component-Type %X",
                        did, cpt.ptype);

            break;
        }
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
 ****************************************************************************/
int
CMPHandleTPCPIMsg_ANSI(ITS_CTXT did, TCAP_CPT *cpt)
{
    TCAP_INVOKE_ENTRY *cptCtxt, *corCtxt;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_BOOLEAN isLast;

    TCAP_DEBUG(("CMPHandleTPCPIMsg: did %04x, cpt ptype: %02x\n",
                did, cpt->ptype));

    if (TCAP_VendorComponentSanityCheck(cpt) != ITS_SUCCESS)
    {

        PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

        TCAP_ERROR(("CMPHandleTPCPI: Sanity check failed.\n"));

        /* Incoming - Discarding Component - Invalid or Corrupted. */
        TCAP_Alarm_ANSI(1004, __FILE__, __LINE__,
                        "Dialog-Id %X, Component-Type %X", did, cpt->ptype);

        return ITS_BADTCAPMESSAGE;
    }

    isLast = (cpt->last_component == 1 ? ITS_TRUE:ITS_FALSE);

    switch (cpt->ptype)
    {
    case TCPPT_TC_INVOKE:
    case TCPPT_TC_INVOKE_NL:
        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */
        cptCtxt = TCAP_FindInvokeContext_ANSI(did,
                                              &cpt->u.invoke.invoke_id,
                                              INV_INCOMING);

        if (did && (cptCtxt == NULL))
        {
            TCAP_ERROR(("CMPHandleTPCPIMsg: Invoke Context Not Found for did %d\n", did));

            return (ITS_ENOMEM);
        }

        if (cptCtxt == NULL || !cptCtxt->inUse)
        {
            ITS_USHORT dest;

            TCAP_DEBUG(("CMPHandleTPCPIMsg: inbound INVOKE received\n"));

            /* NOTE: For UNI the did is 0 */

            if (did)
            {
                if (TCAP_AllocInvokeContext_ANSI(did, cpt,
                                                cptCtxt, INV_INCOMING) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CMPHandleAppMsg: CMP cant allocate invoke "
                                "context.\n"));

                    TCAP_FreeInvokeContext_ANSI(cptCtxt);

                    return (!ITS_SUCCESS);
                }

                /*
                 * We need to check the correlation id here.  This
                 * INVOKE may be in response to one we've already sent.
                 * If so, IF THIS IS INVOKE LAST, only then do we terminate
                 * the original invoke.
                 */
                if (cpt->u.invoke.correlation_id.len == 0)
                {
                    if (cpt->ptype == TCPPT_TC_INVOKE_NL)
                    {
                        /* Send Reject */
                        TCAP_ERROR(("CMPHandleTPCPIMsg: Can't initiate op with "
                                    "INVOKE_NL.\n"));

                        __TCAP_SendAppReject_ANSI(did, cpt,
                                                  TCPPROB_INVOKE,
                                                  TCPPROB_SPEC_INV_UNREC_COREL_ID,
                                                  isLast);

                        __TCAP_SendReject_ANSI(did, cpt,
                                               TCPPROB_INVOKE,
                                               TCPPROB_SPEC_INV_UNREC_COREL_ID);
                          
                         
                        PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_CMP_DISCARDED);                                                    

                        /* Incoming Component - Discarding Component
                         * Rejection Sent by stack.
                         */

                        TCAP_FreeInvokeContext_ANSI(cptCtxt);

                        return (ITS_SUCCESS);
                    }
                }
                else
                {
                    /* Check for correlation ID */
                    TCAP_DEBUG(("CMPHandleTPCPIMsg: Terminating correlated invoke "
                                "%02x\n", cpt->u.invoke.linked_id.data[2]));

                    corCtxt = TCAP_FindInvokeContext_ANSI(did,
                                               &cpt->u.invoke.correlation_id,
                                               INV_OUTGOING);

                    if (corCtxt && corCtxt->inUse)
                    {
                        if (cpt->ptype == TCPPT_TC_INVOKE)
                        {
                            if (corCtxt->state != ITS_CPT_OP_PENDING)
                            {
                                TCAP_ERROR(("CMPHandleTPCPIMsg: invalid state for "
                                            "component.\n"));

                                /* Incoming - Discarding Component - Invalid State. */
                            }

                            TCAP_FreeInvokeContext_ANSI(corCtxt);
                        }
                    }
                    else /* ground for reject */
                    {
                        __TCAP_SendAppReject_ANSI(did, cpt,
                                                  TCPPROB_INVOKE,
                                                  TCPPROB_SPEC_INV_UNREC_COREL_ID,
                                                  isLast);

                        __TCAP_SendReject_ANSI(did, cpt,
                                               TCPPROB_INVOKE,
                                               TCPPROB_SPEC_INV_UNREC_COREL_ID);

                        /* Incoming Component - Discarding Component
                         * Rejection Sent by stack.
                         */

                        return (ITS_SUCCESS);
                    }
                }
            }

            ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                           1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));

            ev.data[0] = ITS_TCAP_CPT;
            ITS_SET_CTXT(&ev.data[1], did);
            memcpy(&ev.data[1 + sizeof(ITS_CTXT)], cpt, sizeof(TCAP_CPT));

            hdr.type = ITS_TCAP;
            hdr.context.dialogue_id = did;

            dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);
            if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
            {
                TCAP_DEBUG(("CMPHandleTPCPIMsg: sending INVOKE to app: %04x\n",
                            dest));

                TRANSPORT_PutEvent(dest, &ev);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                TCAP_DEBUG(("CMPHandleTPCPIMsg: failed to send INVOKE:\n"));
                TCAP_DEBUG(("CMPHandleTPCPIMsg:   hdr.type %02x "
                            "hdr.context %04x\n",
                            hdr.type, hdr.context.dialogue_id));

                ITS_EVENT_TERM(&ev);
                /* Incoming - Discarding Component - No Route to Application. */

                return (ITS_SUCCESS);
            }

            if (did)
            {
                cptCtxt->state = ITS_CPT_OP_IN_PROG;
            }

            /* invoke has been handled */
            return (ITS_SUCCESS);
        }
        else  /* context is not NULL */
        {
            TCAP_ERROR(("CMPHandleTPCPIMsg: received duplicate invoke id.\n"));

            __TCAP_SendAppReject_ANSI(did, cpt,
                                      TCPPROB_INVOKE,
                                      TCPPROB_SPEC_INV_DUPLICATE_INV_ID,
                                      isLast);
            __TCAP_SendReject_ANSI(did, cpt,
                                   TCPPROB_INVOKE,
                                   TCPPROB_SPEC_INV_DUPLICATE_INV_ID);

            PEG_IncrPeg(ANSI_TCAP_Pegs,PEG_TCAP_REMOTE_CMP_DISCARDED);

            /* Incoming Component - Discarding Component
             * Rejection Sent by stack.
             */
             TCAP_Alarm_ANSI(1006, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                did, cpt->ptype);

            return (ITS_SUCCESS);
        }

    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
    case TCPPT_TC_ERROR:
    case TCPPT_TC_REJECT:

        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */
        cptCtxt = TCAP_FindInvokeContext_ANSI(did,
                                              &cpt->u.invoke.invoke_id,
                                              INV_OUTGOING);

        if (cptCtxt == NULL)
        {
            TCAP_ERROR(("NULL CptCtxt for did %d\n", did));

            return (ITS_ENOMEM);
        }

        if (!cptCtxt->inUse) /* can't find the operation we're receiving on */
        {

            /* we're in our initial state, and somebody sent us a naked component
             * without us doing an invoke.  This has to be an error, yes?  Send
             * a reject to the remote. */
            switch (cpt->ptype)
            {
            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_RESULT_NL:

                __TCAP_SendAppReject_ANSI(did, cpt,
                                          TCPPROB_RETURN_RES,
                                          TCPPROB_SPEC_RES_UNREC_COREL_ID,
                                          isLast);
                __TCAP_SendReject_ANSI(did, cpt,
                                       TCPPROB_RETURN_RES,
                                       TCPPROB_SPEC_RES_UNREC_COREL_ID);
                 
                 PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                /* Incoming Component - Discarding Component
                 * Rejection Sent by stack.
                 */
                TCAP_Alarm_ANSI(1006, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                did, cpt->ptype);

                break;

            case TCPPT_TC_ERROR:

                __TCAP_SendAppReject_ANSI(did, cpt,
                                          TCPPROB_RETURN_ERR,
                                          TCPPROB_SPEC_ERR_UNREC_COREL_ID,
                                          isLast);
                __TCAP_SendReject_ANSI(did, cpt,
                                       TCPPROB_RETURN_ERR,
                                       TCPPROB_SPEC_ERR_UNREC_COREL_ID);
                
                 PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);
                /* Incoming Component - Discarding Component
                 * Rejection Sent by stack.
                 */
                TCAP_Alarm_ANSI(1006, __FILE__, __LINE__,
                                "Dialog-Id %X Component-Type %X",
                                did, cpt->ptype);

                break;

            case TCPPT_TC_REJECT:
                /* send the component to the application */
                ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                               1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
                ev.data[0] = ITS_TCAP_CPT;
                ITS_SET_CTXT(&ev.data[1], did);
                memcpy(&ev.data[1 + sizeof(ITS_CTXT)],
                       cpt, sizeof(TCAP_CPT));

                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;

                if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
                {
                    TCAP_WARNING(("CMPHandleTPCPIMsg: unable to send reject.\n"));
                    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                    /* Incoming - Discarding Component
                     * No Route to Application.
                     */
                }

                ITS_EVENT_TERM(&ev);

                TCAP_FreeInvokeContext_ANSI( cptCtxt);

                break;
            }
        }
        else /* we were waiting on the remote */
        {
            TCAP_DEBUG(("CMPHandleTPCPIMsg: pending operation.\n"));

            switch (cpt->ptype)
            {
            case TCPPT_TC_RESULT_NL:
                /*
                 * the difference between result last and result not last is
                 * whether or not the responded-to invoke is terminated
                 */
                TCAP_DEBUG(("CMPHandleTPCPIMsg: response to pending operation.\n"));

                ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                               1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
                ev.data[0] = ITS_TCAP_CPT;
                ITS_SET_CTXT(&ev.data[1], did);
                memcpy(&ev.data[1 + sizeof(ITS_CTXT)],
                       cpt, sizeof(TCAP_CPT));

                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;
                if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
                {
                    TCAP_WARNING(("CMPHandleTPCPIMsg: unable to send response.\n"));

                    /* Incoming - Discarding Component - No Route to Application. */
                }

                break;

            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_ERROR:
                TCAP_DEBUG(("CMPHandleTPCPIMsg: response to pending operation.\n"));

                ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                               1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
                ev.data[0] = ITS_TCAP_CPT;
                ITS_SET_CTXT(&ev.data[1], did);
                memcpy(&ev.data[1 + sizeof(ITS_CTXT)],
                       cpt, sizeof(TCAP_CPT));

                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;
                if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
                {
                    TCAP_WARNING(("CMPHandleTPCPIMsg: unable to send response.\n"));

                    /* Incoming - Discarding Component
                     * No Route to Application.
                     */
                }

                ITS_EVENT_TERM(&ev);

                TCAP_FreeInvokeContext_ANSI(cptCtxt);

                break;

            case TCPPT_TC_REJECT:
                /* send the component to the application */
                ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                               1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
                ev.data[0] = ITS_TCAP_CPT;
                ITS_SET_CTXT(&ev.data[1], did);
                memcpy(&ev.data[1 + sizeof(ITS_CTXT)],
                       cpt, sizeof(TCAP_CPT));

                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;

                if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
                {
                    TCAP_WARNING(("CMPHandleTPCPIMsg: unable to send reject.\n"));

                    /*Incoming - Discarding Component No Route to Application */
                }

                ITS_EVENT_TERM(&ev);

                TCAP_FreeInvokeContext_ANSI(cptCtxt);

                break;
            }
        }
        break;

    default:

        TCAP_ERROR(("CMPHandleTPCPIMsg: Unknown component type!\n"));

        __TCAP_SendAppReject_ANSI(did, cpt,
                                  TCPPROB_GENERAL,
                                  TCPPROB_SPEC_GEN_UNREC_COMP,
                                  isLast);
        __TCAP_SendReject_ANSI(did, cpt,
                               TCPPROB_GENERAL,
                               TCPPROB_SPEC_GEN_UNREC_COMP);

          PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

        /* Incoming Component - Discarding Component
         * Rejection Sent by stack.
         */
        break;
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
 ****************************************************************************/
int
CMPHandleTimeout_ANSI(ITS_EVENT *event)
{
    TCAP_INVOKE_ENTRY ie, *tmp;
    TCAP_TRANS_ENTRY *localTx = NULL, *sharedTx = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;
    TCAP_CPT cpt;
    ITS_HDR hdr;
    ITS_EVENT ev;
    ITS_TimerData *td;
    int ret = ITS_SUCCESS;

    td = (ITS_TimerData*)event->data;
    memcpy(&ie, td->context, sizeof(TCAP_INVOKE_ENTRY));

    /* make sure the dialogue is still with us */
    TCAP_WARNING(("CMPHandleTimeout: did %d, tid %u, invoke-id %d, timer %d\n", 
                   ie.did, ie.ltid, ie.invoke_id, td->serial));

    sharedTx = TCAP_FindTransactionContext_ANSI(ie.ltid,
                                                 tidKey, &tidKeyLen);
    if (sharedTx)
    {
       localTx = TCAP_CopyDSMTxToLocalTx_ANSI(sharedTx);
       /* Dont do the DSM-Commit here. Do it after the the InvokeContext is freed */
    }
    else
    {
        TCAP_WARNING(("CMPHandleTimeout: Cannot Find DSM Tx for tid"
                    "%u.\n", ie.ltid));

        return ITS_SUCCESS;
    }

    /* tmp is a pointer to localTx */

    tmp = TCAP_FindInvokeContextWithTimer_ANSI(ie.did,
                                               ie.invoke_id, 
                                               td->serial);
    if (tmp == NULL)
    {
        TCAP_WARNING(("CMPHandleTimeout: invoke %d not found for timer %d.\n",
                      ie.invoke_id, td->serial));
        return (ITS_SUCCESS);
    }

    /* free up the context */

    TCAP_FreeInvokeContext_ANSI(tmp);
    
    /* copy local ctxt in the DSM */
    memcpy(sharedTx, localTx, sizeof(TCAP_TRANS_ENTRY));

    ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ANSI_TCAP_DLG,
                     tidKey, tidKeyLen, (void *)sharedTx);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("CMPHandleTimeout: DSM_Commit "
                     "failed, error code: %d\n", ret));

        /* Unable to Commit Transaction Context to Table. */

        /* Should we return or should we keep going? */
        /*return ITS_SUCCESS;*/
    }
    else
    {
        TCAP_DEBUG(("CMPHandleTimeout: DSM-Commit of updated DSM Tx; invoke %d did %d.\n",
                     ie.invoke_id, localTx->did));
    }

    cpt.last_component = 1;
    cpt.ptype = TCPPT_TC_CANCEL;
    cpt.u.cancel.invoke_id.len = 3;
    cpt.u.cancel.invoke_id.data[0] = TCPPN_COMPONENT_ID;
    cpt.u.cancel.invoke_id.data[1] = 1;
    cpt.u.cancel.invoke_id.data[2] = ie.invoke_id;

    if (TCAP_VendorComponentSanityCheck(&cpt) != ITS_SUCCESS)
    {
        TCAP_ERROR(("CMPHandleTimeout: Sanity check failed.\n"));

	 // Component sanity check failed
         return ITS_BADTCAPMESSAGE;
    }

    hdr.type = ITS_TCAP;
    hdr.context.dialogue_id = ie.did;

    ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                   1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
    ev.data[0] = ITS_TCAP_CPT;
    ITS_SET_CTXT(&ev.data[1], ie.did);
    memcpy(&ev.data[1 + sizeof(ITS_CTXT)], &cpt, sizeof(TCAP_CPT));
     
    /* Incr Local cancel sent counter */
    PEG_IncrPeg(ANSI_TCAP_Pegs, PEG_TCAP_LOCAL_CANCEL);

    if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
    {
        /* Incr Local cancel discard counter */
      

        TCAP_WARNING(("CMPHandleTimeout: unable to send cancel to app.\n"));
                
        /* Incoming - Discarding Component - No Route to Application. */
    }

    ITS_EVENT_TERM(&ev);

    return (ITS_SUCCESS);
}
