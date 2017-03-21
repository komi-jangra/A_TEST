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
 *  ID: $Id: itu-cco.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/05 06:42:57  adutta
 * LOG: Fix for #1750
 * LOG:
 * LOG: Revision 9.2  2005/04/08 07:35:44  adutta
 * LOG: Fix for BCGI Bug# 624
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:38  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.11  2005/03/21 13:53:42  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.4.6.1.12.4  2005/02/21 14:45:17  sbabu
 * LOG: TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.8.2.4.6.1.12.3  2005/02/03 10:13:40  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.8.2.4.6.1.12.2  2004/12/31 10:07:02  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.4.6.1.12.1  2004/12/17 03:57:43  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.8.2.4.6.1.6.1  2004/10/25 20:34:11  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.8.2.4.6.1  2004/02/16 09:17:50  mmanikandan
 * LOG: Performance Improvement.
 * LOG:
 * LOG: Revision 7.8.2.4  2003/06/12 13:59:54  yranade
 * LOG: Reset the invoke timer in CCOHandleTimeout.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/06/06 15:35:07  yranade
 * LOG: Avoid overriding the invoke context with the correlated invoke context.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/05/15 16:03:38  yranade
 * LOG: Reorganize component handling.
 * LOG:
 * LOG: Revision 7.8.2.1  2003/04/09 08:55:37  yranade
 * LOG: ITS_CTXT related updates.
 * LOG:
 * LOG: Revision 7.8  2003/02/07 13:57:46  tsanthosh
 * LOG: Changes for Pegs & Alarms
 * LOG:
 * LOG: Revision 7.7  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.6  2002/12/04 18:24:56  ngoel
 * LOG: merge PRC changes from PR6.1
 * LOG:
 * LOG: Revision 7.5  2002/12/04 18:19:42  ngoel
 * LOG: merge prc changes from PR6.1
 * LOG:
 * LOG: Revision 7.4  2002/11/14 22:27:20  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.3  2002/10/15 19:41:28  omayor
 * LOG: Use correct includes
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:10:13  omayor
 * LOG: Mnimization of DSM calls
 * LOG:
 * LOG: Revision 6.5  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:31  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.3  2001/09/26 00:36:41  mmiers
 * LOG: Get the fixmes under 100.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2000/09/01 20:11:13  mmiers
 * LOG: Fix a couple of bugs.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:24  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:32  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.2  2000/07/14 17:23:19  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.1  2000/03/18 21:04:58  mmiers
 * LOG: The result of the Tandem port.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.17  1999/10/05 19:01:03  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.16  1999/09/09 17:01:51  ite
 * LOG:
 * LOG: update cleaning invoke context when time out occurs.
 * LOG:
 * LOG: Revision 1.15  1999/09/08 00:20:12  ite
 * LOG:
 * LOG: fhasle: fix class 4 invoke problem (timer was not running -> operation context
 * LOG:         never freed).
 * LOG:
 * LOG: Revision 1.14  1999/09/07 21:02:31  ite
 * LOG:
 * LOG:
 * LOG: Change interface for TCAP such that the dialogue id is not memcpy'd.
 * LOG: This fixes a reject bug.
 * LOG:
 * LOG: Revision 1.13  1999/09/07 19:44:52  mmiers
 * LOG:
 * LOG:
 * LOG: Free invoke context when closing transaction.
 * LOG:
 * LOG: Revision 1.12  1999/09/01 16:23:00  mmiers
 * LOG:
 * LOG:
 * LOG: Add in component reject timer.
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
 * LOG: Revision 1.9  1999/08/26 15:24:13  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.8  1999/08/25 22:40:53  mmiers
 * LOG:
 * LOG:
 * LOG: Sanity checks.
 * LOG:
 * LOG: Revision 1.7  1999/08/04 13:30:34  mmiers
 * LOG:
 * LOG:
 * LOG: Commit my latest version.
 * LOG:
 * LOG: Revision 1.6  1999/06/21 18:53:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up ITU TCAP.  Needs extensive testing.
 * LOG:
 * LOG: Revision 1.5  1999/06/18 22:57:43  mmiers
 * LOG:
 * LOG:
 * LOG: More TCAP sanitization
 * LOG:
 * LOG: Revision 1.4  1999/06/15 15:07:17  mmiers
 * LOG:
 * LOG:
 * LOG: Small modification to ITU TCAP.
 * LOG:
 * LOG: Revision 1.3  1999/05/24 20:31:20  mmiers
 * LOG:
 * LOG:
 * LOG: Codecs have moved into shared library.
 * LOG:
 * LOG: Revision 1.2  1999/05/18 17:00:16  mmiers
 * LOG:
 * LOG:
 * LOG: Initial coding of ITU TCAP complete.  Much testing and fixme
 * LOG: removal to do.
 * LOG:
 * LOG: Revision 1.1  1999/05/17 23:05:37  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 *
 ****************************************************************************/

#include <stdlib.h>

#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif


#include <its.h>
#include <its_types.h>
#include <its_emlist.h>
#include <its_trace.h>
#include <its_route.h>
#include <its_dsm.h>

#ident "$Id: itu-cco.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#else
#include <itu/tcap.h>
#endif


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
 *
 *  Revision History:
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     04-07-2005  BCGI Helpdesk# 624      Fix for stack handling of
 *                                               outgoing REJECT
 *
 *
 * sbabu     04-21-2005  PBN Issue 1750          Fix for stack sending out a 
 *                                               reject for a non existing 
 *                                               invoke id    
 *
 ****************************************************************************/
int
CCOHandleAPPMsg_CCITT(ITS_EVENT *event)
{
    /*
     * function has been updated to handle ITU 97. You will notice
     * no check for ITU variant here, since it was done previously in
     * the TCAP interface module (Component sanity check).
     */
    TCAP_INVOKE_ENTRY *cptCtxt = NULL, *corCtxt = NULL;
    TCAP_CPT cpt;
    ITS_CTXT did;
    ITS_OCTET invId;

    did = ITS_GET_CTXT(&event->data[1]);
    memcpy(&cpt, &event->data[sizeof(ITS_OCTET) + sizeof(ITS_CTXT)],
           sizeof(TCAP_CPT));

    TCAP_DEBUG(("CCOHandleAppMsg: did %d, cpt ptype: %02x\n",
                did, cpt.ptype));

    if (cpt.u.invoke.invoke_id.data[1] == 2)
    {
        invId = cpt.u.invoke.invoke_id.data[3];
    }
    else
    {
        invId = cpt.u.invoke.invoke_id.data[2];
    }

    switch (cpt.ptype)
    {
    case TCPPT_TC_INVOKE:
    case TCAP_PT_TC_TIMER_RESET:
    case TCPPT_TC_U_CANCEL:

        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */
        cptCtxt = TCAP_FindInvokeContext_CCITT(did, &cpt.u.invoke.invoke_id, 
                                               INV_OUTGOING);

        if (cptCtxt == NULL)
        {
            TCAP_ERROR(("Cannot find Cpt Entry for did %d, inv_id %d.\n",
                         did, invId));

            return (ITS_ENOMEM);
        }

        if (!cptCtxt->inUse)
        {
            /* must be new if this is true */
            switch (cpt.ptype)
            {
            case TCPPT_TC_INVOKE:

                TCAP_DEBUG(("CCOHandleAppMsg: new remote operation\n"));

                if (TCAP_AllocInvokeContext_CCITT(did, &cpt, 
                                                  cptCtxt, INV_OUTGOING) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO cant allocate invoke "
                                "context.\n"));

                    TCAP_FreeInvokeContext_CCITT(cptCtxt);

                    return (!ITS_SUCCESS);
                }
                
                /*
                 * We need to check the correlation id here.
                 */
                if (cpt.u.invoke.correlation_id.len != 0)
                {
                    TCAP_DEBUG(("CCOHandleAPPMsg: correlated invoke "
                                "%02x\n", cpt.u.invoke.linked_id.data[2]));

                    corCtxt = TCAP_FindInvokeContext_CCITT(did,
                                                           &cpt.u.invoke.correlation_id,
                                                           INV_INCOMING);
                                          
                    if (corCtxt == NULL || !corCtxt->inUse)
                    {
                        __TCAP_SendAppReject_CCITT(did, &cpt,
                                                   TCPPROB_INVOKE,
                                                   TCPPROB_SPEC_INV_UNREC_LINKED_ID,
                                                   ITS_TRUE);
                        
                        PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_APP_CMP_DISCARDED);
                        PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_APP_MSG_DISCARDED);
 
                        /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                        TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 

                        return (ITS_SUCCESS);
                    }
                }

                /* Send to DHA (just enqueue it) */
                if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                                "DHA.\n"));
                    TCAP_FreeInvokeContext_CCITT(cptCtxt);

                    return (ITS_SUCCESS);
                }
                else
                {
                    switch (cpt.u.invoke.opClass)
                    {
                    case 1:
                        cptCtxt->state = ITS_CPT_OP_CLASS1_SENT;
                        break;
                    case 2:
                        cptCtxt->state = ITS_CPT_OP_CLASS2_SENT;
                        break;
                    case 3:
                        cptCtxt->state = ITS_CPT_OP_CLASS3_SENT;
                        break;
                    case 4:
                        cptCtxt->state = ITS_CPT_OP_CLASS4_SENT;
                        break;
                    default:
                        __TCAP_SendAppReject_CCITT(did, &cpt,
                                                   TCPPROB_INVOKE,
                                                   TCPPROB_SPEC_INV_MISTYPED_PARAM,
                                                   ITS_TRUE);

                        /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                         TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 
                  
                        /* TODO add the PEGs that got removed */

                        break;
                    }
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_INVOKE_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
                }
                break;

            case TCAP_PT_TC_TIMER_RESET:

                /* TC_User wants to reset timer of non-existent operation */
                TCAP_ERROR(("CCOHandleAppMsg: Reset Timer failed for non-existent "
                            "operation [did: %d, invk: 0x%02x] \n",
                            did,cpt.u.timerReset.invoke_id.data[2]));
                
                /* Discarding Reset Timer Request for non-existent invoke operation. */
                 TCAP_Alarm_CCITT(1403, __FILE__, __LINE__, "Dialog-Id %X", did); 
                
                break;
            }
            return (ITS_SUCCESS);            
        }
        else /* context is inUse */
        {
            switch (cpt.ptype)
            {
            case TCPPT_TC_U_CANCEL:

                TCAP_WARNING(("CCOHandleAppMsg: remote operation canceled\n"));

                TCAP_FreeInvokeContext_CCITT(cptCtxt);

                if (DHAHandleCCOCancelMsg_CCITT(did,
                                                &cpt.u.invoke.invoke_id)
                    != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send CANCEL "
                                "to TRP.\n"));
                }

                break;

            case TCAP_PT_TC_TIMER_RESET:

                if (DHAHandleCCOResetTimerMsg_CCITT(cptCtxt) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: Timer Reset failed for operation"
                                " [did: %d, invk: 0x%02x] \n",
                                cptCtxt->did ,cptCtxt->invoke_id));

                    /* Timer request failed for Operation */
                }

                TCAP_WARNING(("CCOHandleAppMsg: Timer Reset for operation "
                              "[did: %d, invk: 0x%02x] \n",
                              cptCtxt->did ,cptCtxt->invoke_id));

                break;

            case TCPPT_TC_INVOKE:

                TCAP_ERROR(("CCOHandleAppMsg: App attempted to send while "
                            "remote operation pending.\n"));

                __TCAP_SendAppReject_CCITT(did, &cpt,
                                           TCPPROB_INVOKE,
                                           TCPPROB_SPEC_INV_DUPLICATE_INV_ID,
                                           ITS_TRUE);

                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);  
                
                /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                 TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 

                break;
            }

            return (ITS_SUCCESS);
       }

       break;

    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
    case TCPPT_TC_U_ERROR:

        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */
        cptCtxt = TCAP_FindInvokeContext_CCITT(did, &cpt.u.invoke.invoke_id,
                                               INV_INCOMING);

        if (cptCtxt == NULL)
        {
            TCAP_ERROR(("Cannot find Cpt Entry for did %d, inv_id %d.\n",
                         did, invId));

            return (ITS_ENOMEM);
        }

        if (!cptCtxt->inUse) /* can't find the operation we're sending to */
        {
            TCAP_ERROR(("CCOHandleAppMsg: attempt to send component to "
                        "non existent operation\n"));

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            switch (cpt.ptype)
            {
            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_RESULT_NL:
                __TCAP_SendAppReject_CCITT(did, &cpt,
                                          TCPPROB_RETURN_RES,
                                          TCPPROB_SPEC_RES_UNEXPECTED_RET_RES,
                                          ITS_TRUE);
                
                /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 

                break;

            case TCPPT_TC_U_ERROR:
                __TCAP_SendAppReject_CCITT(did, &cpt,
                                          TCPPROB_RETURN_ERR,
                                          TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR,
                                          ITS_TRUE);
                
                /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 

                break;
            }
        }
        else /* we were waiting on the application */
        {
            TCAP_DEBUG(("CCOHandleAppMsg: application response to invocation.\n"));

            switch (cpt.ptype)
            {
            case TCPPT_TC_U_ERROR:

                TCAP_DEBUG(("CCOHandleAppMsg: responding to invoke with "
                            "ERROR.\n"));

                event->src = ITS_TCAP_SRC;

                if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                                "DHA.\n"));

                    /* Failed to send event to DHA */
                }
                else
                {
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_ERROR_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT); 
                }

                TCAP_FreeInvokeContext_CCITT(cptCtxt);

                break;

            case TCPPT_TC_RESULT_L:

                TCAP_DEBUG(("CCOHandleAppMsg: responding to invoke with "
                            "RESULT_LAST.\n"));

                event->src = ITS_TCAP_SRC;

                if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                                "DHA.\n"));

                    /* Failed to send event to DHA */
                
                }
                else
                {
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_RESULT_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT); 
                }

                TCAP_FreeInvokeContext_CCITT(cptCtxt);

                break;

            case TCPPT_TC_RESULT_NL:

                TCAP_DEBUG(("CCOHandleAppMsg: responding to invoke with "
                            "RESULT_NOT_LAST.\n"));

                event->src = ITS_TCAP_SRC;

                if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                                "DHA.\n"));

                    /* Failed to send event to DHA */
                }
                else
                {
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_RESULT_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
                }
 
                /*
                 * In this case, we don't free the local context: the application
                 * isn't done responding.
                 */

                break;
            }
        }
        break;

    case TCPPT_TC_U_REJECT:
    case TCPPT_TC_R_REJECT:

        cptCtxt = TCAP_FindInvokeContext_CCITT(did, &cpt.u.invoke.invoke_id,
                                               INV_OUTGOING);
        /*
         * In that case it is tricky to find the invoke context. In ITU
         * INCOMING and OUTGOING ops can have the same inv id. Since a
         * Reject can be sent in response to Invoke or RRL or ERR, we
         * look first for OUTGOING then if not found for INCOMING. If
         * not found at all it is an error.
         */

        cptCtxt = TCAP_FindInvokeContext_CCITT(did, &cpt.u.invoke.invoke_id,
                                               INV_OUTGOING);


        if (cptCtxt && (cptCtxt->inUse)) /* if NULL try INV_INCOMING */
        {
            /*
             * if we are not in AWAIT_REJECT state, that means, the we have
             * sent an invoke and are waiting for the answer still. so
             * try INCOMING. Remember that in ITU we can have 2 invokeCtxt
             * with the same invoke ID but different DIR.
             */

            if (cptCtxt->state == ITS_CPT_OP_AWAIT_REJECT)
            {
                /*
                * This means we are rejecting of result, and Reject timer is
                * running
                */
                TCAP_DEBUG(("CCOHandleAppMsg: REJECT for received result/error.\n"));

                event->src = ITS_TCAP_SRC;

                if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                                "DHA.\n"));
                }

                else
                {
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                    PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT); 
                } 

                TCAP_FreeInvokeContext_CCITT(cptCtxt);
            
                return (ITS_SUCCESS);
            }

            /*
             * if not in that state that just means that we have sent an invoke and
             * are waiting for RR. This Reject must be for an INCOMING Invoke...
             */
        }

        /*
         * it was not OUTGOING, try INCOMING
         */
 
        cptCtxt = TCAP_FindInvokeContext_CCITT(did, &cpt.u.invoke.invoke_id,
                                               INV_INCOMING);

        if (cptCtxt == NULL)
        {
            TCAP_ERROR(("Cannot find Cpt Entry for did %d, inv_id %d.\n",
                         did, invId));

            return (ITS_ENOMEM);
        }

        if (!cptCtxt->inUse) /* can't find the operation we're sending to */
        {
            /* If invoke context is not in use, then the reject component
             * is discarded and a local reject is sent to the app
             */
            __TCAP_SendAppReject_CCITT(did, &cpt,
                                       TCPPROB_GENERAL,
                                       TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP,
                                       ITS_TRUE);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did);
        }
        else
        {
            TCAP_WARNING(("CCOHandleAppMsg: remote operation REJECT.\n"));

            event->src = ITS_TCAP_SRC;

            if (DHAHandleCCOMsg_CCITT(event) != ITS_SUCCESS)
            {
                TCAP_ERROR(("CCOHandleAppMsg: CCO couldn't send event to "
                            "DHA.\n"));

                /* Failed to send event to DHA */
            }
            else
            {
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_REJECT_SENT);
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_SENT);
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            }

            TCAP_FreeInvokeContext_CCITT(cptCtxt);
        }
        break; 


    default:

        TCAP_WARNING(("CCOHandleAppMsg: Send reject on bad component.\n"));
        __TCAP_SendAppReject_CCITT(did, &cpt,
                                   TCPPROB_GENERAL,
                                   TCPPROB_SPEC_GEN_UNREC_COMP,
                                   ITS_TRUE);

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
 
                
         /* Outgoing Component - Discarding Component - Rejection Sent by stack. */
         TCAP_Alarm_CCITT(1401, __FILE__, __LINE__, "Dialog-Id %X",did); 

         break;
     }

    /* context has been freed before hence released, no need to commit */ 
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
 *  Revision History:
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     04-07-2005  Personeta Bug Id #739   Added Missing check for NULL  
 *                                               invoke ctxt. 
 *                                               
 ****************************************************************************/
int
CCOHandleDHAMsg_CCITT(ITS_CTXT did, TCAP_CPT *cpt)
{
    TCAP_INVOKE_ENTRY *cptCtxt = NULL, *corCtxt = NULL;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_BOOLEAN isLast;
    
    TCAP_DEBUG(("CCOHandleDHAMsg: did %04x, cpt ptype: %02x\n",
                did, cpt->ptype));

    if (TCAP_VendorComponentSanityCheck(cpt) != ITS_SUCCESS)
    {
        TCAP_ERROR(("CCOHandleDHAMsg: Sanity check failed.\n"));
            
        /* Incoming Component - Discarding Component - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1404, __FILE__, __LINE__, "Dialog-Id %X  Component Type %X",did,cpt->ptype); 

        return ITS_BADTCAPMESSAGE;
    }

    isLast = (cpt->last_component == 1 ? ITS_TRUE:ITS_FALSE);

    switch (cpt->ptype)
    {
        case TCPPT_TC_INVOKE:
        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */

        cptCtxt = TCAP_FindInvokeContext_CCITT(did,
                                               &cpt->u.invoke.invoke_id,
                                               INV_INCOMING);
         if (did && (cptCtxt == NULL))
        {
            TCAP_ERROR(("CCOHandleDHAMsg: Invoke Context Not Found for did %d\n", did));

            return (ITS_ENOMEM);
        }

        if (cptCtxt == NULL || !cptCtxt->inUse)
        {
            /* Not found entry in the local table */
            ITS_USHORT dest;

            TCAP_DEBUG(("CCOHandleDHAMsg: inbound INVOKE received\n"));

            if (did)
            {
                if (TCAP_AllocInvokeContext_CCITT(did, cpt,
                                                  cptCtxt,
                                                  INV_INCOMING)
                   != ITS_SUCCESS)
                {
                    TCAP_ERROR(("CCOHandleAPPMsg: CCO cant allocate invoke "
                                "context.\n"));

                    TCAP_FreeInvokeContext_CCITT(cptCtxt);

                    return (!ITS_SUCCESS);
                }

                /*
                 * We need to check the correlation id here.
                 */

                if (cpt->u.invoke.correlation_id.len != 0)
                {
                    TCAP_DEBUG(("CCOHandleDHAMsg: correlated with invoke "
                                "%02x\n", cpt->u.invoke.linked_id.data[2]));
                    /*
                     * - DSM Stuff - commit the INCOMING, before looking for
                     * the OUTGOING
                     */

                    corCtxt = TCAP_FindInvokeContext_CCITT(did,
                                                           &cpt->u.invoke.correlation_id,
                                                           INV_OUTGOING);

                    if (corCtxt == NULL || !corCtxt->inUse)
                    {
                        __TCAP_SendRemoteReject_CCITT(did, cpt,
                                                      TCPPROB_INVOKE,
                                                      TCPPROB_SPEC_INV_UNREC_LINKED_ID);

                        __TCAP_SendAppReject_CCITT(did, cpt,
                                                   TCPPROB_INVOKE,
                                                   TCPPROB_SPEC_INV_UNREC_LINKED_ID,
                                                   isLast);

                         PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED); 
                         
                        /* Incoming Component - Discarding Component - Rejection Sent by stack. */
                        TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did); 
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
                TCAP_DEBUG(("CCOHandleDHAMsg: sending INVOKE to app: %04x\n",
                            dest));

                TRANSPORT_PutEvent(dest, &ev);

                ITS_EVENT_TERM(&ev);
            }
            else
            {
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                TCAP_DEBUG(("CCOHandleDHAMsg: failed to send INVOKE:\n"));
                TCAP_DEBUG(("CCOHandleDHAMsg:   hdr.type %02x "
                            "hdr.context %04x\n",
                            hdr.type, hdr.context.dialogue_id));

                ITS_EVENT_TERM(&ev);

                /* Incoming Component - Discarding Component - Invalid or Corrupted. */
                TCAP_Alarm_CCITT(1404, __FILE__, __LINE__, "Dialog-Id %X Component Type %X",did,cpt->ptype); 

                return (ITS_SUCCESS);
            }

            if (did)
            {
                cptCtxt->state = ITS_CPT_OP_IN_PROG;
            }

            return (ITS_SUCCESS);

        }
        else  /* context is not NULL */
        {
            TCAP_ERROR(("CCOHandleDHAMsg: received duplicate invoke id.\n"));

            __TCAP_SendAppReject_CCITT(did, cpt,
                                       TCPPROB_INVOKE,
                                       TCPPROB_SPEC_INV_DUPLICATE_INV_ID,
                                       isLast);

            __TCAP_SendRemoteReject_CCITT(did, cpt,
                                          TCPPROB_INVOKE,
                                          TCPPROB_SPEC_INV_DUPLICATE_INV_ID);
              
             PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED); 
            /* Incoming Component - Discarding Component - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did); 

            return (ITS_SUCCESS);
        }

        break;
   
    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
    case TCPPT_TC_U_ERROR:
    case TCPPT_TC_R_REJECT:
    case TCPPT_TC_U_REJECT:

        /* note that this is legal for all components as they all have
         * invoke ID in the same place in their structure */

        cptCtxt = TCAP_FindInvokeContext_CCITT(did,
                                               &cpt->u.invoke.invoke_id,
                                               INV_OUTGOING);

        if (cptCtxt == NULL)
        {
            TCAP_ERROR(("Invoke Context Not Found for did %d\n", did));

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
                __TCAP_SendAppReject_CCITT(did, cpt,
                                           TCPPROB_RETURN_RES,
                                           TCPPROB_SPEC_RES_UNREC_INVOKE_ID,
                                           isLast);

                __TCAP_SendRemoteReject_CCITT(did, cpt,
                                              TCPPROB_RETURN_RES,
                                              TCPPROB_SPEC_RES_UNREC_INVOKE_ID);
                    
                /* Incoming Component - Discarding Component - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did); 

                break;

            case TCPPT_TC_U_ERROR:
                __TCAP_SendAppReject_CCITT(did, cpt,
                                           TCPPROB_RETURN_ERR,
                                           TCPPROB_SPEC_ERR_UNREC_INVOKE_ID,
                                           isLast);

                __TCAP_SendRemoteReject_CCITT(did, cpt,
                                              TCPPROB_RETURN_ERR,
                                              TCPPROB_SPEC_ERR_UNREC_INVOKE_ID);

                /* Incoming Component - Discarding Component - Rejection Sent by stack. */
                TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id%X", did);               
 
                break;

            case TCPPT_TC_R_REJECT:
            case TCPPT_TC_U_REJECT:
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
                    TCAP_WARNING(("CCOHandleDHAMsg: unable to send reject.\n"));

                    /* Incoming Component - Discarding Component - No Route to Application. */
                }

                ITS_EVENT_TERM(&ev);

                TCAP_FreeInvokeContext_CCITT( cptCtxt);

                break;
            }
        }
        else /* we were waiting on the remote */
        {
            TCAP_DEBUG(("CCOHandleDHAMsg: pending operation.\n"));

            switch (cpt->ptype)
            {
            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_RESULT_NL:
                if (cptCtxt->state != ITS_CPT_OP_CLASS1_SENT &&
                    cptCtxt->state != ITS_CPT_OP_CLASS3_SENT)
                {
                    __TCAP_SendAppReject_CCITT(did, cpt, 
                                               TCPPROB_RETURN_RES,
                                               TCPPROB_SPEC_RES_UNEXPECTED_RET_RES,
                                               isLast);
            
                    __TCAP_SendRemoteReject_CCITT(did, cpt,
                                                  TCPPROB_RETURN_RES,
                                                  TCPPROB_SPEC_RES_UNEXPECTED_RET_RES);

                     PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);

                    /* Incoming Component - Discarding Component - Rejection Sent by stack. */
                    TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did);                      
                    TCAP_FreeInvokeContext_CCITT(cptCtxt);
            
                    return (ITS_SUCCESS);
                 }

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
                     TCAP_WARNING(("CCOHandleDHAMsg: unable to send RESULT CPT to APP.\n"));

                     /* Incoming Component - Discarding Component - No Route to Application. */
                 }

                 ITS_EVENT_TERM(&ev);

                 /*
                  * the difference between result last and result not last is
                  * whether or not the responded-to invoke is terminated
                  */

                 if (cpt->ptype == TCPPT_TC_RESULT_L)
                 {
                     /* move to WAIT_FOR_REJECT */
                     if (TIMERS_GetTimerValue(&CCITT_TCAP_Timers, TCAP_T_reject))
                     {
                         TCAP_DEBUG(("CCOHandleDHAMsg: starting __T_reject\n"));

                         cptCtxt->state = ITS_CPT_OP_AWAIT_REJECT;

                         if (cptCtxt->timer)
                         {
                             TIMERS_CancelSharedTimer(cptCtxt->timer);

                             TCAP_DEBUG(("CCOHandleDHAMsg: Cancel Shared Invoke Timer %d "
                                         "for did %d InvokeId %d\n",
                                         cptCtxt->timer, did, cptCtxt->invoke_id));
                         }

                         if ((cptCtxt->timer =
                                 TIMERS_StartSharedTimer(ITS_TCAP_SRC,
                                                         TIMERS_GetTimerValue(&CCITT_TCAP_Timers,
                                                         TCAP_T_reject),
                                                         cptCtxt,
                                                         sizeof(TCAP_INVOKE_ENTRY))) == 0)
                         {
                             TCAP_ERROR(("CCOHandleDHAMsg: unable to start reject timer.\n"));
    
                             TCAP_FreeInvokeContext_CCITT(cptCtxt);
    
                             cptCtxt = NULL;
                         }
    
                         TCAP_DEBUG(("CCOHandleDHAMsg: Started Shared Reject Timer %d "
                                     "for did %d InvokeId %d\n",
                                     cptCtxt->timer, did, cptCtxt->invoke_id));
                     }
                     else
                     {
                         TCAP_DEBUG(("CCOHandleDHAMsg: __T_reject is 0, not waiting...\n"));

                         TCAP_FreeInvokeContext_CCITT(cptCtxt);

                         cptCtxt = NULL;
                     }
                 }
                 break;
    
            case TCPPT_TC_U_ERROR:
                TCAP_DEBUG(("CCOHandleDHAMsg: response to pending operation.\n"));
    
                if (cptCtxt->state != ITS_CPT_OP_CLASS1_SENT &&
                    cptCtxt->state != ITS_CPT_OP_CLASS2_SENT)
                {
                    __TCAP_SendAppReject_CCITT(did, cpt,
                                               TCPPROB_RETURN_ERR,
                                               TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR,
                                               isLast);
                    __TCAP_SendRemoteReject_CCITT(did, cpt,
                                                  TCPPROB_RETURN_ERR,
                                                  TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR);

                      PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CMP_DISCARDED);
 
                    /* Incoming Component - Discarding Component - Rejection Sent by stack. */
                    TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did);                   
 
                    TCAP_FreeInvokeContext_CCITT(cptCtxt);

                    return (ITS_SUCCESS);
                }

                ITS_EVENT_INIT(&ev, ITS_TCAP_SRC,
                               1 + sizeof(ITS_CTXT) + sizeof(TCAP_CPT));
                ev.data[0] = ITS_TCAP_CPT;
                ITS_SET_CTXT(&ev.data[1], did);
                memcpy(&ev.data[1 + sizeof(ITS_CTXT)],
                       cpt, sizeof(TCAP_CPT));

                hdr.type = ITS_TCAP;
                hdr.context.dialogue_id = did;

                TCAP_DEBUG(("CCOHandleDHAMsg: Sending ERROR Cpt to Application.\n"));

                if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
                {
                    TCAP_WARNING(("CCOHandleDHAMsg: unable to send response.\n"));
                
                    /* Incoming Component - Discarding Component - No Route to Application. */
                }

                ITS_EVENT_TERM(&ev);

                /* move to WAIT_FOR_REJECT */
                if (TIMERS_GetTimerValue(&CCITT_TCAP_Timers, TCAP_T_reject))
                {
                    TCAP_DEBUG(("CCOHandleDHAMsg: starting __T_reject\n"));

                    cptCtxt->state = ITS_CPT_OP_AWAIT_REJECT;

                    if (cptCtxt->timer)
                    {
                        TIMERS_CancelSharedTimer(cptCtxt->timer);
                    }

                    if ((cptCtxt->timer =
                            TIMERS_StartSharedTimer(ITS_TCAP_SRC,
                                                    TIMERS_GetTimerValue(&CCITT_TCAP_Timers,
                                                                         TCAP_T_reject),
                                                    cptCtxt, sizeof(TCAP_INVOKE_ENTRY)))
                        == 0)
                    {
                        TCAP_ERROR(("CCOHandleDHAMsg: unable to start reject timer.\n"));

                        TCAP_FreeInvokeContext_CCITT(cptCtxt);

                        cptCtxt = NULL;
                    }
                }
                else
                {
                    TCAP_DEBUG(("CCOHandleDHAMsg: __T_reject is 0, not waiting...\n"));

                    TCAP_FreeInvokeContext_CCITT(cptCtxt);

                    cptCtxt = NULL;
                }
                break;

            case TCPPT_TC_U_REJECT:
            case TCPPT_TC_R_REJECT:
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
                    TCAP_WARNING(("CCOHandleDHAMsg: unable to send reject.\n"));
                
                    /* Incoming Component - Discarding Component - No Route to Application. */
                 }

                ITS_EVENT_TERM(&ev);

                TCAP_FreeInvokeContext_CCITT(cptCtxt);

                cptCtxt = NULL;

                break;
            }
        }
        break;

    default:
        TCAP_ERROR(("CCOHandleDHAMsg: Unknown component type!\n"));

        __TCAP_SendAppReject_CCITT(did, cpt,
                                   TCPPROB_GENERAL,
                                   TCPPROB_SPEC_GEN_UNREC_COMP,
                                   isLast);
        __TCAP_SendRemoteReject_CCITT(did, cpt,
                                      TCPPROB_GENERAL,
                                      TCPPROB_SPEC_GEN_UNREC_COMP);

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_CMP_DISCARDED);
 
        /* Incoming Component - Discarding Component - Rejection Sent by stack. */
        TCAP_Alarm_CCITT(1406, __FILE__, __LINE__, "Dialog-Id %X", did); 

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
CCOHandleTimeout_CCITT(ITS_EVENT *event)
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
    TCAP_WARNING(("CCOHandleTimeout: did %d, tid %u, invoke-id %d, timer %d\n", 
                   ie.did, ie.ltid, ie.invoke_id, td->serial));

    sharedTx = TCAP_FindTransactionContext_CCITT(ie.ltid,
                                                 tidKey, &tidKeyLen);
    if (sharedTx)
    {
       localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);
    }
    else
    {
        TCAP_WARNING(("CCOHandleTimeout: Cannot Find DSM Tx for tid"
                    "%u.\n", ie.ltid));

        return ITS_SUCCESS;
    }

    /* tmp is a pointer to localTx */

    tmp = TCAP_FindInvokeContextWithTimer_CCITT(ie.did,
                                                ie.invoke_id, 
                                                td->serial);                                                
    if (tmp == NULL)
    {
        TCAP_WARNING(("CCOHandleTimeout: invoke %d not found for timer %d.\n",
                      ie.invoke_id, td->serial));

        return (ITS_SUCCESS);
    }

    /* Reset the timer */
    if (tmp->timer)
    {
        tmp->timer = TIMER_BAD_SERIAL;
    }

    TCAP_FreeInvokeContext_CCITT(tmp);

    /* copy local ctxt in the DSM */
    memcpy(sharedTx, localTx, sizeof(TCAP_TRANS_ENTRY));

    ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ITU_TCAP_DLG,
                     tidKey, tidKeyLen, (void *)sharedTx);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("CCOHandleTimeout: DSM_Commit "
                    "failed, error code: %d\n", ret));

        /* Unable to Commit Transaction Context to Table. */

        /* Should we return or should we keep going? */
        /*return ITS_SUCCESS;*/
    }
    else
    {
        TCAP_DEBUG(("CCOHandleTimeout: DSM-Commit of updated DSM Tx; invoke %d did %d.\n",
                      ie.invoke_id, localTx->did));
    }

    cpt.last_component = 1;
    cpt.ptype = TCPPT_TC_L_CANCEL;
    cpt.u.cancel.invoke_id.len = 3;
    cpt.u.cancel.invoke_id.data[0] = TCPPN_INVOKE_TAG;
    cpt.u.cancel.invoke_id.data[1] = 1;
    cpt.u.cancel.invoke_id.data[2] = ie.invoke_id;

    /* if this is not an await U_REJECT timer, send L-CANCEL */
    if (ie.state != ITS_CPT_OP_AWAIT_REJECT)
    {
        TCAP_WARNING(("CCOHandleTimeout: Send L-CANCEL.\n"));

        if (TCAP_VendorComponentSanityCheck(&cpt) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCOHandleTimeout: Sanity check failed.\n"));
            /* Incoming as in Toward Application */
            /* Incoming Component - Discarding Component - Invalid or Corrupted. */

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
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_LOCAL_CANCEL);

        if (ROUTE_SendToApplication(&hdr, &ev) != ITS_SUCCESS)
        {
            TCAP_WARNING(("CCOHandleTimeout: unable to send cancel to app.\n"));
            /* Incoming as in Toward Application */
            /* Incoming Component - Discarding Component - No Route to Application. */
        }

        ITS_EVENT_TERM(&ev);
    }

    /*
     * Dont free localTx here because we need it around 
     * if PreArranged End is sent
     */

    /*TCAP_FreeLocalTx_CCITT(ie.did);*/

    return (ITS_SUCCESS);
}
