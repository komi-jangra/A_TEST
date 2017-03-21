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
 *  ID: $Id: itu-tsm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/05 06:44:28  adutta
 * LOG: Fix for #1752
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:33:45  yranade
 * LOG: Implementation of changes based on design doc ACC651-SDS-TCEN-V1.0.02
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.9  2005/03/21 13:53:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.4.6.1.12.3  2005/02/03 10:15:50  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.7.2.4.6.1.12.2  2004/12/31 10:16:38  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.4.6.1.12.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.7.2.4.6.1.6.1  2004/10/25 20:34:14  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.7.2.4.6.1  2004/02/16 12:58:21  yranade
 * LOG: TCAP Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.7.2.4  2003/06/06 14:59:50  yranade
 * LOG: Update one debug trace.
 * LOG:
 * LOG: Revision 7.7.2.3  2003/05/16 11:53:56  vjatti
 * LOG: Fix for Cleaning of Invoke Timers on receipt of an ABORT.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/05/14 08:54:23  yranade
 * LOG: Update traces and added a comment.
 * LOG:
 * LOG: Revision 7.7.2.1  2003/04/15 15:57:19  vjatti
 * LOG: Fix for Bug 288/289. Don't free the did from the LocalTxTable.
 * LOG:
 * LOG: Revision 7.7  2003/02/07 13:57:47  tsanthosh
 * LOG: Changes for Pegs & Alarms
 * LOG:
 * LOG: Revision 7.6  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.5  2002/12/04 18:24:56  ngoel
 * LOG: merge PRC changes from PR6.1
 * LOG:
 * LOG: Revision 7.4  2002/12/04 18:12:38  ngoel
 * LOG: merge prc changes from PR6.1
 * LOG:
 * LOG: Revision 7.3  2002/10/15 19:41:28  omayor
 * LOG: Use correct includes
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:10:13  omayor
 * LOG: Mnimization of DSM calls
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.6  2002/08/19 18:07:02  mmiers
 * LOG: Correct macro
 * LOG:
 * LOG: Revision 6.5  2002/08/16 22:07:11  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.4  2002/07/03 21:19:49  mmiers
 * LOG: Fixes for DSM, VFrame
 * LOG:
 * LOG: Revision 6.3  2002/04/18 14:56:15  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:31  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2002/01/02 19:56:09  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/21 20:21:31  mmiers
 * LOG: Start adding in the missing code.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2000/11/29 17:50:59  mmiers
 * LOG: Weird Cisco len fix.
 * LOG:
 * LOG: Revision 3.2  2000/09/01 20:11:13  mmiers
 * LOG: Fix a couple of bugs.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:42  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/04/17 21:36:33  mmiers
 * LOG:
 * LOG:
 * LOG: A few bug fixes to ANSI TCAP.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:41  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.10  1999/10/05 19:01:06  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.9  1999/10/04 16:46:06  mmiers
 * LOG:
 * LOG:
 * LOG: Some sanity fixes.
 * LOG:
 * LOG: Revision 1.8  1999/08/27 16:50:14  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.7  1999/08/26 23:45:03  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.6  1999/08/26 02:21:58  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.5  1999/06/21 18:53:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up ITU TCAP.  Needs extensive testing.
 * LOG:
 * LOG: Revision 1.4  1999/06/15 22:32:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.3  1999/05/27 21:46:07  mmiers
 * LOG:
 * LOG:
 * LOG: Adjust the TID management for sanity.
 * LOG:
 * LOG: Revision 1.2  1999/05/27 15:52:47  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.1  1999/05/17 23:05:38  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.2  1999/05/12 22:54:12  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.1  1999/05/11 22:45:37  mmiers
 * LOG:
 * LOG:
 * LOG: Work on ITU TCAP.
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
#include <its_tq_trans.h>
#include <its_dsm.h>
#include <its_ss7_trans.h>

#ident "$Id: itu-tsm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#if defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#else
#include <itu/tcap.h>
#endif

#include "tcap_intern.h"

#if defined(SPLIT_STACK)
#define WHICH_STACK     (ITS_HANDLE)ISS7_ANSI_Stack
#elif defined(PRC)
#define WHICH_STACK     (ITS_HANDLE)ISS7_PRC_Stack
#elif defined(TTC)
#define WHICH_STACK     (ITS_HANDLE)ISS7_TTC_Stack
#else
#define WHICH_STACK     (ITS_HANDLE)ISS7_CCITT_Stack
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
 *
 * 
 * --------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * --------------------------------------------------------------------------
 * sbabu     05-04-2005  PBN Issuse ID#1752     Warning trace is seen in the 
 *                                              Successful message exchange 
 *
 *                                               
 *
 ****************************************************************************/
int
TSMHandleTCOCSLMsg_CCITT(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount)
{
    TCAP_TRANS_ENTRY *trCtxt = NULL, *sharedTx = NULL;
    ITS_OCTET pType, ssn;
    ITS_UINT tid1 = 0, tid2 = 0, tid1Len = 0, tid2Len = 0;
    SCCP_ADDR cdp, clp;
    ITS_HDR hdr;
    ITS_UINT pc = 0;
    MTP3_HEADER *mtp3 = NULL;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0, ret = ITS_SUCCESS;
    ITS_BOOLEAN sendToSCCP = ITS_FALSE;

    memset(&cdp, 0, sizeof(SCCP_ADDR));
    memset(&clp, 0, sizeof(SCCP_ADDR));

    TCAP_DEBUG(("TCOHandleCSLMsg:\n"));

    trCtxt = TCAP_FindLocalTx_CCITT(did);
    if (trCtxt == NULL)
    {
        TCAP_ERROR(("TCOHandleCSLMsg: Missing Local Tx for did %d ",
                    did));

    }

    if (FindPTypeAndTID_CCITT(ies, ieCount, &pType,
                              &tid1, &tid1Len, &tid2, &tid2Len,
                              &cdp, &clp) == ITS_NO)
    {
        TCAP_ERROR(("TCOHandleCSLMsg: Could not successfully decode "
                    "PType/TID\n"));
        /* Outgoing Message - Discarding Message - Invalid or Corrupted. */

        TCAP_FreeLocalTx_CCITT(did);

        return (ITS_SUCCESS);
    }

    if (did & TCAP_DIR_BIT) /* originated by remote */
    {
        int i;

        /* can't be a BEGIN.  Has to be END or CONTINUE */
        TCAP_DEBUG(("TCOHandleCSLMsg: remote msg:\n"));
        TCAP_DEBUG(("   ptype: %02x tid1 %08x tid2 %08x\n",
                    pType, tid1, tid2));

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
         * I think this is done but it needs to be tested: fixme.
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
        TCAP_DEBUG(("TCOHandleCSLMsg: local msg:\n"));
        TCAP_DEBUG(("   ptype: %02x tid1 %08x tid2 %08x\n",
                    pType, tid1, tid2));
    }

    hdr.type = ITS_TCAP;
    SCCP_DecodeAddr(&clp, NULL, &pc, &ssn, NULL, NULL);
    hdr.context.ssn = ssn;

    if (trCtxt == NULL)
    {
        TCAP_DEBUG(("TCOHandleCSLMsg: no trCtxt.  New transaction.\n"));

        TCAP_ERROR(("TCOHandleCSLMsg: NULL transaction context for did.: %d\n",
                        did));

        /* Outgoing Message - Discarding Message - Invalid State. */

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        return ITS_SUCCESS;
    }
    else if (trCtxt->state == ITS_TCAP_IDLE)
    {
        TCAP_DEBUG(("TCOHandleCSLMsg: ITS_TCAP_IDLE state.  New transaction.\n"));

        switch (pType)
        {
        case TCPPT_TC_UNI:

            sendToSCCP = ITS_TRUE;

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_UNI_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
  
            break;
       
        case TCPPT_TC_BEGIN:

            trCtxt->state = ITS_TCAP_BEGIN_SENT;
            
            /* new transaction need to allocate */
            sharedTx = TCAP_AllocTransactionContext_CCITT(trCtxt->ltid,
                                                          tidKey, &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for did"
                            "%d.\n", did));

                TCAP_FreeLocalTx_CCITT(did);
                return ITS_SUCCESS;
            }

            sendToSCCP = ITS_TRUE;

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_BEGIN_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            
            break;

        default:
            /* something's foul */
            TCAP_ERROR(("TCOHandleCSLMsg: Invalid PType for state.: %02x\n",
                        pType));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_CCITT(1443, __FILE__, __LINE__,"PType %X Dialog-Id %X", pType, did);

            TCAP_FreeLocalTx_CCITT(did);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return ITS_SUCCESS;
        }
    }
    else if (trCtxt->state == ITS_TCAP_BEGIN_RCVD)
    {
        TCAP_DEBUG(("TCOHandleCSLMsg: state is BEGIN_RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONTINUE:
           
            trCtxt->state = ITS_TCAP_ACTIVE;

            /* Yogi: Do we need a DSM lookup here? 
             * Why do a FindTransactionContext, since in the BEGIN_RCVD
             * state we can be sure that it won't exist. In fact if
             * it exists it should amount to an error condition.
             * I don't really think it affects redundancy...but I am not sure
             * so although not changing the code. Just adding this comment.
             */

            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_DEBUG(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));

                /* new transaction need to allocate */
                /* This might be the first Continue going out as a 
                   Response to an Incoming Begin. So there is no 
                   DSM Tx for it at this point*/

                sharedTx = TCAP_AllocTransactionContext_CCITT(trCtxt->ltid,
                                                              tidKey, &tidKeyLen);

                if (sharedTx == NULL)
                {
                    TCAP_ERROR(("TCOHandleCSLMsg: Cannot allocate DSM Tx for "
                                "did %d.\n", did));

                    TCAP_FreeLocalTx_CCITT(did);
                    return ITS_SUCCESS;
                }
            }

            sendToSCCP = ITS_TRUE;
         
           PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CONT_SENT);
           PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);

           break;

        case TCPPT_TC_END:
        /*
         * Do we need this? Use DSM on receiving side?
         */

            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, 
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

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            sendToSCCP = ITS_TRUE;

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_END_SENT);

            PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS); 

            TCAP_FreeLocalTx_CCITT(did);

            trCtxt = NULL;

            break;

        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:

            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, 
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

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            TCAP_FreeLocalTx_CCITT(did);
            
            sendToSCCP = ITS_TRUE;

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);
            PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS); 

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TCOHandleCSLMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_CCITT(1444, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, did); 

            TCAP_FreeLocalTx_CCITT(did);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return ITS_SUCCESS;
        }
    }
    else if (trCtxt->state == ITS_TCAP_BEGIN_SENT)
    {
        TCAP_DEBUG(("TCOHandleCSLMsg: state is BEGIN_SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_END:
        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:
            
            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, 
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

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            TCAP_FreeLocalTx_CCITT(did);

            /* Spec says no action for these two.  Dunno why */

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TCOHandleCSLMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
            TCAP_Alarm_CCITT(1445, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, did); 

            TCAP_FreeLocalTx_CCITT(did);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return ITS_SUCCESS;
        }
    }
    else if (trCtxt->state == ITS_TCAP_ACTIVE)
    {
        TCAP_DEBUG(("TCOHandleCSLMsg: state is ACTIVE.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONTINUE:
            
            trCtxt->state = ITS_TCAP_ACTIVE;
            
            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, tidKey,
                                                         &tidKeyLen);
            if (sharedTx == NULL)
            {
                TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for did"
                            "%d.\n", did));
            }

            sendToSCCP = ITS_TRUE;
          
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_CONT_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            
            break;

        case TCPPT_TC_END:

            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, 
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

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            if (trCtxt->prearranged)
            {
                TCAP_FreeLocalTx_CCITT(did);
            }
            else
            {
                TCAP_FreeLocalTx_CCITT(did);
                
                sendToSCCP = ITS_TRUE;

                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_END_SENT);

                PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);
            }

            trCtxt = NULL;

            break;

        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:
            
            sharedTx = TCAP_FindTransactionContext_CCITT(trCtxt->ltid, 
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

                TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
            }

            TCAP_FreeLocalTx_CCITT(did);
            
            sendToSCCP = ITS_TRUE;
            
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_SENT);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_ABORT_SENT);

            PEG_DecrPeg(CCITT_TCAP_Pegs,PEG_TCAP_ACTIVE_TRANSACTIONS);

            trCtxt = NULL;

            break;

        default:
            /* error case */
            TCAP_ERROR(("TCOHandleCSLMsg: Invalid PType for state.\n"));
            
            /* Outgoing Message - Discarding Message - Invalid State. */
             
            TCAP_Alarm_CCITT(1446, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, did);

            TCAP_FreeLocalTx_CCITT(did);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

            return ITS_SUCCESS;
        }
    }
    else
    {
        /* error condition */
        TCAP_ERROR(("TCOHandleCSLMsg: Invalid state for PType.\n"));
            
        /* Outgoing Message - Discarding Message - Invalid State. */

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);

        return ITS_SUCCESS;
    }

    /* - DSM Stuff - commit any changes made to the  */
    /*  only if the message is a Begin or a Continue */

    if (pType == TCPPT_TC_CONTINUE ||
        pType == TCPPT_TC_BEGIN)
    {
        /* copy local ctxt in the DSM */
        memcpy(sharedTx, trCtxt, sizeof(TCAP_TRANS_ENTRY));

        ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ITU_TCAP_DLG,
                         tidKey, tidKeyLen, (void *)sharedTx);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TSMHandleTCOCSLMsg_CCITT: DSM_Commit "
                        "failed, error code: %d\n", ret));
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_APP_MSG_DISCARDED);
         
        }
        else
        {
            TCAP_DEBUG(("TSMHandleTCOCSLMsg_CCITT: DSM-Commit the DSM Tx for "
                        "did %d, pType = %d\n", did, pType));
        }

        /* Clean up local Tx */
        /* Don't free the did from the LocalTxTable here - Commenting it out
        TCAP_FreeLocalTx_CCITT(did);
        */
    }
    else
    {
         PEG_DecrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
         TCAP_DEBUG(("TSMHandleTCOCSLMsg: No DSM-Commits; Message is neither Begin"
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
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005   ACC651-SDS-TCEN-V1.0.02  Free CptList in case of
 *                        ID :: D0060              Abort
 *                                              
 ****************************************************************************/
int
TSMHandleTCOSCCPMsg_CCITT(ITS_OCTET pType, ITS_SCCP_IE *ies, int ieCount,
                          TCAP_TRANS_ENTRY **trCtxt)
{
    int i;
    TCAP_INVOKE_ENTRY *cptCtxt;
    TCAP_CPT_LIST *cptList = NULL;

    switch ((*trCtxt)->state)
    {
    case ITS_TCAP_IDLE:
        /* send to CSL */
        if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) == ITS_SUCCESS)
        {
            (*trCtxt)->state = ITS_TCAP_BEGIN_RCVD;

            for (i = 0; i < ieCount; i++)
            {
                if (ies[i].param_id == SCCP_PRM_ROUTING_LABEL)
                {
                    (*trCtxt)->label = ies[i].param_data.routingLabel;
                    break;
                }
            }
        }
        else
        {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

        }

        return (ITS_SUCCESS);

    case ITS_TCAP_BEGIN_SENT:
        TCAP_DEBUG(("TCOHandleSCCP: state is BEGIN SENT.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONTINUE:
            /* send to CSL */
            if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) == ITS_SUCCESS)
            {
                (*trCtxt)->state = ITS_TCAP_ACTIVE;
            }
            else
            {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

            }
            break;

        case TCPPT_TC_END:
        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:
            /* send to CSL */
            if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

            }

            /* Fix for cleaning invoke timer on receipt of ABORT */
            if (pType == TCPPT_TC_U_ABORT ||
                pType == TCPPT_TC_P_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &(*trCtxt)->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if ((*trCtxt)->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_CCITT(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                }
            }

            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);

            *trCtxt = NULL;

            break;

        default:
            TCAP_ERROR(("TCOHandleSCCP: bad pType for state, send REJECT.\n"));

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_INCORRECT_TRANS_PORT);

            /* Incomming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);
            TCAP_Alarm_CCITT(1451, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, (*trCtxt)->did);

            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);
            
            break;
        }
        break;

    case ITS_TCAP_BEGIN_RCVD:
        TCAP_DEBUG(("TCOHandleSCCP: state is BEGIN RCVD.\n"));

        switch (pType)
        {
        case TCPPT_TC_END:
        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:
            /* send to CSL */
            if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

            }

            /* Fix for cleaning invoke timer on receipt of ABORT */
            if (pType == TCPPT_TC_U_ABORT ||
                pType == TCPPT_TC_P_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &(*trCtxt)->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if ((*trCtxt)->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_CCITT(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                } 
            }

            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);

            *trCtxt = NULL;

            break;

        default:
            TCAP_ERROR(("TCOHandleSCCP: bad pType for state, send REJECT.\n"));

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_INCORRECT_TRANS_PORT);
            
            /* Incomming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_Alarm_CCITT(1450, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, (*trCtxt)->did);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);

            *trCtxt = NULL;

            break;
        }
        break;

    case ITS_TCAP_ACTIVE:
        TCAP_DEBUG(("TCOHandleSCCP: state is ACTIVE.\n"));

        switch (pType)
        {
        case TCPPT_TC_CONTINUE:
            /* send to CSL */
            if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

            }
            break;

        case TCPPT_TC_END:
        case TCPPT_TC_U_ABORT:
        case TCPPT_TC_P_ABORT:
            /* send to CSL */
            if (DHAHandleTCOMsg_CCITT(ies, ieCount, *trCtxt) != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCO couldn't send event to CSL.\n"));

            }

            /* Fix for cleaning invoke timer on receipt of ABORT */
            if (pType == TCPPT_TC_U_ABORT ||
                pType == TCPPT_TC_P_ABORT)
            {
                /* Update as per Design ID :: D0060 */
                cptList = &(*trCtxt)->cptList;
                while (cptList != NULL)
                {
                    for (i = 0; i < TCAP_CTX_MAX_CPT_ENTRIES; i++)
                    {
                        if ((cptCtxt = &cptList->cptEntry[i]) != NULL)
                        {
                            if ((*trCtxt)->did == cptCtxt->did)
                            {
                                TCAP_FreeInvokeContext_CCITT(cptCtxt);
                            }
                        }
                    }
                    cptList = cptList->next;
                } 
            }

            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);

            *trCtxt = NULL;

            break;

        default:
            TCAP_ERROR(("TCOHandleSCCP: bad pType for state, send REJECT.\n"));

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_INCORRECT_TRANS_PORT);
            
            /* Incomming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
            TCAP_FreeLocalTx_CCITT((*trCtxt)->did);

            TCAP_Alarm_CCITT(1452, __FILE__, __LINE__, "PType %X Dialog-Id %X", pType, (*trCtxt)->did);
            PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

            break;
        }
        break;

    default:
        /* error condition */
        TCAP_ERROR(("TCOHandleSCCP: bad state for pType.\n"));

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_MSG_DISCARDED);

        TCAP_FreeLocalTx_CCITT((*trCtxt)->did);
            
        /* Incomming Dialogue - Discarding Dialogue - Invalid or Corrupted. */
    }

    return (ITS_SUCCESS);
}


