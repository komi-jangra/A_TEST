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
 *  ID: $Id: itu-tco.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:34  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:53:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.3.34.3  2005/02/21 14:46:56  sbabu
 * LOG:  TCAP OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.6.2.3.34.2  2004/12/31 10:11:27  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.3.34.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.6.2.3.28.1  2004/10/25 20:34:14  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.6.2.3  2003/06/06 14:58:13  yranade
 * LOG: Update some error traces.
 * LOG:
 * LOG: Revision 7.6.2.2  2003/05/16 07:16:36  vjatti
 * LOG: Fix for Bug 302: Added Remote TID verification.
 * LOG:
 * LOG: Revision 7.6.2.1  2003/05/13 03:10:39  vjatti
 * LOG: Fix for Bug 298: Setting the correct cause.
 * LOG: Fix for Bug 299. Sending Abort on incorrect Continue Msg.
 * LOG:
 * LOG: Revision 7.6  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.5  2002/12/04 17:29:27  ngoel
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
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/08/19 18:07:02  mmiers
 * LOG: Correct macro
 * LOG:
 * LOG: Revision 6.6  2002/08/16 22:07:10  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.5  2002/07/29 17:54:35  ngoel
 * LOG: increment total message peg
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
 * LOG: Revision 5.4  2001/12/17 00:15:35  mmiers
 * LOG: Get this building on UNIX
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/30 15:42:33  labuser
 * LOG: Added receive LUDT/LUDTS to itu-tco.c
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/02/08 23:37:32  mmiers
 * LOG: Need to find the correct trCtxt for UDTS/XUDTS.
 * LOG:
 * LOG: Revision 3.2  2000/11/29 17:50:59  mmiers
 * LOG: Weird Cisco len fix.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:41  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:41  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.15  1999/10/05 19:01:06  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.14  1999/09/22 19:49:16  mmiers
 * LOG:
 * LOG:
 * LOG: Play around a bit with P-ABORT.
 * LOG:
 * LOG: Revision 1.13  1999/09/17 23:04:05  mmiers
 * LOG:
 * LOG:
 * LOG: Change return values for PAbort
 * LOG:
 * LOG: Revision 1.12  1999/09/10 23:10:24  mmiers
 * LOG:
 * LOG:
 * LOG: Split out white book and blue book variant behavior.
 * LOG:
 * LOG: Revision 1.11  1999/09/01 15:51:02  mmiers
 * LOG:
 * LOG:
 * LOG: More fixes for Fred's testing.
 * LOG:
 * LOG: Revision 1.10  1999/08/31 15:00:03  rsonak
 * LOG:
 * LOG:
 * LOG: Work around not finding a TransactionContext when receiving a begin.
 * LOG: Correct allocation code to not look for the TID in the local
 * LOG: table if it is a new incoming dialogue.
 * LOG:
 * LOG: Revision 1.9  1999/08/27 16:50:13  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol families.  This is
 * LOG: easier than trying to sanitize them of family specific data.
 * LOG:
 * LOG: Revision 1.8  1999/08/26 23:45:03  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.7  1999/08/26 02:21:58  mmiers
 * LOG:
 * LOG:
 * LOG: Automate QOS reflection.  Fix UNI handling (newly added code would have
 * LOG: rejected UNIs).  Try to be clearer about the position of the routing
 * LOG: label.  There is still most likely a hole (or more specifically, to
 * LOG: much override) when building a routing label after the user has
 * LOG: overriden certain fields.
 * LOG:
 * LOG: Revision 1.6  1999/06/21 18:53:57  mmiers
 * LOG:
 * LOG:
 * LOG: Finish up ITU TCAP.  Needs extensive testing.
 * LOG:
 * LOG: Revision 1.5  1999/06/15 22:32:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.4  1999/05/27 15:52:47  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.3  1999/05/17 23:05:38  mmiers
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
#include <string.h>

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

#ident "$Id: itu-tco.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"


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
 ****************************************************************************/
int
TCOHandleCSLMsg_CCITT(ITS_CTXT did, ITS_SCCP_IE *ies, int ieCount)
{
    return TSMHandleTCOCSLMsg_CCITT(did, ies, ieCount);
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
TCOHandleSCCPMsg_CCITT(ITS_EVENT *event)
{
    TCAP_TRANS_ENTRY *localTx = NULL, *sharedTx = NULL;
    ITS_OCTET pType = 0;
    ITS_UINT tid1 = 0, tid2 = 0, tid1Len = 0, tid2Len = 0;
    SCCP_ADDR cdp, clp;
    ITS_OCTET type;
    ITS_SCCP_IE ies[32];
    int ieCount;
    ITS_HDR hdr;
    int ret = ITS_SUCCESS;
    ITS_OCTET tidKey[4];
    int tidKeyLen = 0;
    ITS_CTXT did = 0;

    memset(&cdp, 0, sizeof(SCCP_ADDR));
    memset(&clp, 0, sizeof(SCCP_ADDR));

    type = SCCP_MSG_TYPE(event);

    TCAP_DEBUG(("TCOHandleSCCPMsg: SCCPmsgType %02x.\n", type));

    switch (type)
    {
    case SCCP_MSG_UDT:
        if (SCCP_ReceiveUnitData(WHICH_STACK, event,
                                 &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive UDT.\n"));
            
            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_XUDT:
        if (SCCP_ReceiveExtendedUnitData(WHICH_STACK, event,
                                         &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive XUDT.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_LUDT:
        if (SCCP_ReceiveLongUnitData(WHICH_STACK, event,
                                     &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive LUDT.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_UDTS:
        if (SCCP_ReceiveUnitDataService(WHICH_STACK, event,
                                        &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive UDTS.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_LUDTS:
        if (SCCP_ReceiveLongUnitDataService(WHICH_STACK, event,
                                            &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive LUDTS.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        break;

    case SCCP_MSG_XUDTS:
        if (SCCP_ReceiveExtendedUnitDataService(WHICH_STACK,
                                                event,
                                                &hdr, ies, &ieCount) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCOHandleSCCP: Couldn't receive XUDTS.\n"));

            /* Unable to retrive incoming message. */

            return (ITS_SUCCESS);
        }
        return (ITS_SUCCESS);

    default:
        TCAP_ERROR(("TCOHandleSCCP: SCCP message is neither UDT nor XUDT\n"));
            
        /* Incoming Message - Discarding Message - Invalid or Corrupted. */
        TCAP_Alarm_CCITT(1446, __FILE__, __LINE__, NULL);
        
        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_INVALID_SCCP_RCVD);

        return (ITS_SUCCESS);
    }

    if (FindPTypeAndTID_CCITT(ies, ieCount,
                              &pType, &tid1, &tid1Len, &tid2, &tid2Len,
                              &cdp, &clp) == ITS_NO)
    {
        /* something really bad happened to get here */
        PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_DLG_SEND_APP_FAIL);
        PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_REMOTE_MSG_DISCARDED);
        
        /* Fix for Bug 298. Set the Abort reason correctly */
        if (!pType)
        {
            TCAP_ERROR(("TCOHandleSCCP: Unrecognized Message Type.\n"));

            TCAP_Alarm_CCITT(1448, __FILE__, __LINE__,"PType %X Tx-id %X",pType,tid2);

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_UNREC_MSG_TYPE);

           PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD);
 
        }
        else
        {
            TCAP_ERROR(("TCOHandleSCCP: Bad TID(s).\n"));

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_INCORRECT_TRANS_PORT);

            TCAP_Alarm_CCITT(1453, __FILE__, __LINE__, "PType %X", pType);
        }

        /* Incoming Message - Discarding Dialogue - Rejection Sent by stack. */
        return (ITS_SUCCESS);
    }

    if (type == SCCP_MSG_UDTS || type == SCCP_MSG_XUDTS)
    {
        sharedTx = TCAP_FindTransactionContext_CCITT(tid1,
                                                     tidKey, &tidKeyLen);
        if (sharedTx != NULL)
        {
             localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);

             TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
        }

        if (localTx != NULL)
        {
            DHAHandleTCOMsg_CCITT(ies, ieCount, localTx);
        }

        return (ITS_SUCCESS);
    }

    switch (pType)
    {
    case TCPPT_TC_UNI:

        /* handle a completely new transaction */
        /* send to CSL */
        TCAP_DEBUG(("TCOHandleSCCPMsg: handle UNI.\n"));

        if (DHAHandleTCOMsg_CCITT(ies, ieCount, NULL) != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCO couldn't send event to CSL.\n"));
        
            /* Incoming Message - Discarding Message - Invalid or Corrupted. */
            TCAP_Alarm_CCITT(1446, __FILE__, __LINE__, NULL);
        }

        return (ITS_SUCCESS);

    case TCPPT_TC_BEGIN:

        /* handle a completely new transaction */
        ret = TCAP_GetNextIDID_CCITT(&did);

        if (ret != ITS_SUCCESS)
        {
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_RES_UNAVAIL);
        
            /* Incoming Message - Discarding Message - Rejection Sent by stack. */

            return (ITS_SUCCESS);
        }

        localTx =  TCAP_AllocateLocalTx_CCITT(did);

        if (localTx == NULL)
        {
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_RES_UNAVAIL);
            
            TCAP_Alarm_CCITT(1447, __FILE__, __LINE__, "Transaction-id %X PType %X", tid2, pType); 
 
            return (ITS_SUCCESS);
        }

        AllocateLTIDinTx_CCITT(localTx);

        ret = TCAP_PopulateLocalTx_CCITT(localTx, did, tid1, tid1Len, &cdp, &clp);

        if (ret != ITS_SUCCESS)
        {
            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_RES_UNAVAIL);
        
            TCAP_FreeLocalTx_CCITT(did);

            return (ITS_SUCCESS);
        }

        ret = TSMHandleTCOSCCPMsg_CCITT(pType, ies, ieCount, &localTx);

/*
 *      On receiving a Begin? do we really need to use DSM. 
 *      Because we are anyways going to use LocalTx on the way out. 
 */

#if 0
        if (ret == ITS_SUCCESS)
        {
            sharedTx = TCAP_AllocTransactionContext_CCITT(localTx->ltid,
                                                          tidKey, &tidKeyLen);
            if (sharedTx != NULL)
            {
                memcpy(sharedTx, localTx, sizeof(TCAP_TRANS_ENTRY));
            
                ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ITU_TCAP_DLG,
                                 tidKey, tidKeyLen, (void *)sharedTx);
                if (ret != ITS_SUCCESS)
                {
                    TCAP_ERROR(("TCAP_FreeTransactionContext_CCITT: DSM_Commit "
                                "failed, error code: %d\n", ret));
                
                    /* Unable to Commit Transaction Pointer to Table. */
                }
            }
            else
            {
                ret = ITS_ENOMEM;
            }

            /* Note: Dont delete the localTx here, as we want to respond using 
               the same localTx. This imples that whoever receives, responds. */
            /* 
             * TCAP_FreeLocalTx_CCITT(did);
             */
        }
#endif

        return (ret);
    
    case TCPPT_TC_CONTINUE:
        /*
         * we've gotten an indication for a transaction
         * already in progress
         * either way (transaction initiator or receiver), we've got
         * a local entry already 
         */

        sharedTx = TCAP_FindTransactionContext_CCITT(tid2, tidKey, &tidKeyLen);

        if (sharedTx)
        {
            if (sharedTx->rtidLen)
            {
                /* Added Remote TID verification */
                if (tid1 != sharedTx->rtid)
                {
                    TCAP_ERROR(("TCOHandleSCCP: bad TID(s), %08x send ABORT.\n", tid2));

                    __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                                 TCPABT_REASON_UNREC_TRANS_ID);

                    /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */

                    TCAP_Alarm_CCITT(1453, __FILE__, __LINE__, "PType %X", pType); 

                    return (ITS_SUCCESS);
                }
            }

            localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);

            if (localTx)
            {
                localTx->rtid = tid1;
                localTx->rtidLen = tid1Len;
            }

           /* We simply commit here (just for the sake of Unlock). 
            * We will operate on localTx, and we will do the 'real' 
            * commit when sending response out 
            */  

            ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ITU_TCAP_DLG,
                             tidKey, tidKeyLen,
                             (void *)sharedTx);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCOHandleSCCPMsg_CCITT: DSM_Commit failed "
                            "returned code: %d\n", ret));

                /* Unable to Commit Transaction Context to Table. */
            }
        }
        else
        {
            TCAP_ERROR(("TCOHandleSCCPMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));

            TCAP_ERROR(("TCOHandleSCCP: bad TID(s), %08x send ABORT.\n", tid2));

            PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_DLG_SEND_APP_FAIL);
            PEG_IncrPeg(CCITT_TCAP_Pegs,PEG_TCAP_REMOTE_MSG_DISCARDED);
 

            __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                         TCPABT_REASON_UNREC_TRANS_ID);

            /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
           TCAP_Alarm_CCITT(1453, __FILE__, __LINE__, "PType %X", pType);
           TCAP_Alarm_CCITT(1447, __FILE__, __LINE__, "Transaction-id %X PType %X", tid2, pType);

           return ITS_SUCCESS; 
        }
        break;
 
    case TCPPT_TC_END:

        sharedTx = TCAP_FindTransactionContext_CCITT(tid2, tidKey, &tidKeyLen);
   
        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);

            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", localTx->did));

            TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
        }
        else
        {
            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));
 
            return ITS_SUCCESS; 
        }
        break;

    case TCPPT_TC_P_ABORT:

        sharedTx = TCAP_FindTransactionContext_CCITT(tid2, tidKey, &tidKeyLen);
    
        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);

            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", localTx->did));

            TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
        }
        else
        {
            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));

             TCAP_Alarm_CCITT(1447, __FILE__, __LINE__, "Transaction-id %X PType %X", tid2, pType);

            return ITS_SUCCESS; 
        }
        break;

    case TCPPT_TC_U_ABORT:

        sharedTx = TCAP_FindTransactionContext_CCITT(tid2, tidKey, &tidKeyLen);
    
        if (sharedTx)
        {
            localTx = TCAP_CopyDSMTxToLocalTx_CCITT(sharedTx);

            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", localTx->did));

            TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
        }
        else
        {
            TCAP_ERROR(("TCOHandleCSLMsg: Cannot Find DSM Tx for tid"
                        "%u.\n", tid2));

            return ITS_SUCCESS; 
        }
        break;

    default: 

        /* something really bad happened to get here */
        TCAP_ERROR(("TCOHandleSCCP: bad package type, send P_ABORT.\n"));

        __TCAP_SendTransPAbort_CCITT(ies, ieCount,
                                     TCPABT_REASON_UNREC_MSG_TYPE);
            
        /* Incoming Dialogue - Discarding Dialogue - Rejection Sent by stack. */
        TCAP_Alarm_CCITT(1448, __FILE__, __LINE__, "PType %X Tx-id %X", pType, tid2);  

        sharedTx = TCAP_FindTransactionContext_CCITT(tid2, tidKey, &tidKeyLen);

        if (sharedTx)
        {
            TCAP_DEBUG(("TCOHandleCSLMsg: Freeing DSM Tx for did"
                        "%d.\n", sharedTx->did));

            TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
        }

        return ITS_SUCCESS;
    }

    did = localTx->did;

    ret = TSMHandleTCOSCCPMsg_CCITT(pType, ies, ieCount, &localTx);

#if 0
    /*
     *Do we really need to commit the sharedTx in DSM here?
     *We are going to operate on localTx only till we send out the message.
     */

    /* - DSM Stuff - commit the changes made to the context */
    if (localTx != NULL)  /* only if it was not freed before */
    {
        if (sharedTx != NULL)
        {
            memcpy(sharedTx, localTx, sizeof(TCAP_TRANS_ENTRY));

            ret = DSM_Commit(DSM_TcapFtGroupId, DSM_TABLE_ITU_TCAP_DLG, 
                             tidKey, tidKeyLen, 
                             (void *)sharedTx);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCOHandleSCCPMsg_CCITT: DSM_Commit failed "
                            "returned code: %d\n", ret));           
                
                /* Unable to Commit Transaction Context to Table. */
            }
       }
       else
       {
           TCAP_ERROR(("TCOHandleSCCPMsg_CCITT: SharedTx is NULL for did %d ",
                        localTx->did));
       
           TCAP_FreeLocalTx_CCITT(localTx->did);
       }
    }
    else
    {
           TCAP_DEBUG(("TCOHandleSCCPMsg_CCITT: LocalTx has been freed for "
                       "did %d ",did));
    }
#endif

    return (ret);

}
