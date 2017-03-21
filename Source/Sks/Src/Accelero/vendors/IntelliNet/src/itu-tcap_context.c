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
 *  ID: $Id: itu-tcap_context.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $
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
 * LOG: Revision 9.3  2005/04/08 07:37:34  adutta
 * LOG: Fix for Bug# 885
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:33:45  yranade
 * LOG: Implementation of changes based on design doc ACC651-SDS-TCEN-V1.0.02
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.13  2005/03/21 13:53:52  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.8.2.6.6.3.2.3  2005/02/03 10:16:41  sbabu
 * LOG: TCAP Peg Bug Fixes
 * LOG:
 * LOG: Revision 7.8.2.6.6.3.2.2  2004/12/31 09:55:47  sbabu
 * LOG: TCAP OAM Changes
 * LOG:
 * LOG: Revision 7.8.2.6.6.3.2.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.8.2.6.6.3  2004/12/01 13:38:32  yranade
 * LOG: Free appropriately in FreeLocalTx.
 * LOG:
 * LOG: Revision 7.8.2.6.6.2  2004/09/17 12:21:00  yranade
 * LOG: Don't allow Backup Node to initiate dialogs.
 * LOG:
 * LOG: Revision 7.8.2.6.6.1  2004/02/16 12:58:21  yranade
 * LOG: TCAP Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.8.2.6  2003/06/12 14:09:55  yranade
 * LOG: In FreeDSMTransactionContext, avoid finding an entry in
 * LOG: DSM DID table for incoming transactions.
 * LOG:
 * LOG: Revision 7.8.2.5  2003/06/10 10:50:31  yranade
 * LOG: Move the cancelling of timers for cpts from FreeDSMTransactionContext
 * LOG: to FreeLocalTx and reset the timer values.
 * LOG:
 * LOG: Revision 7.8.2.4  2003/05/27 06:05:31  yranade
 * LOG: Cancel the timers for components in FreeDSMTransactionContext.
 * LOG:
 * LOG: Revision 7.8.2.3  2003/05/14 08:51:43  yranade
 * LOG: In CopyDSMTxToLocalTx don't copy if localTx already exists. Bug fix 284.
 * LOG:
 * LOG: Revision 7.8.2.2  2003/04/17 20:40:18  rsonak
 * LOG: Create and delete mutexes
 * LOG:
 * LOG: Revision 7.8.2.1  2003/04/04 15:20:15  yranade
 * LOG: ITS_CTXT related updates.
 * LOG:
 * LOG: Revision 7.8  2003/02/07 13:57:46  tsanthosh
 * LOG: Changes for Pegs & Alarms
 * LOG:
 * LOG: Revision 7.7  2003/01/16 16:23:34  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.6  2002/12/04 18:15:44  ngoel
 * LOG: merge prc changes from PR6.1
 * LOG:
 * LOG: Revision 7.5  2002/11/14 22:27:20  omayor
 * LOG: Removed compilation warnings shown by gcc3.2
 * LOG:
 * LOG: Revision 7.4  2002/11/05 22:51:11  omayor
 * LOG: Coding standards!
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
 * LOG: Revision 6.6  2002/08/16 22:07:10  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.5  2002/04/18 14:56:15  hdivoux
 * LOG: More FT/HA integration.
 * LOG:
 * LOG: Revision 6.4  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.3  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:31  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.7  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.6  2001/11/09 20:19:55  mmiers
 * LOG: Don't force the vendor lib to be part of the engine.  Make into
 * LOG: DLL instead.
 * LOG:
 * LOG: Revision 5.5  2001/09/26 00:36:41  mmiers
 * LOG: Get the fixmes under 100.
 * LOG:
 * LOG: Revision 5.4  2001/09/26 00:31:03  mmiers
 * LOG: Remove a couple of warnings and fixmes
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/08/17 20:54:06  mmiers
 * LOG: Remove dead code Olivier noticed.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.5  2001/07/26 23:20:06  mmiers
 * LOG: More MTP3.  Just about got SRM.
 * LOG:
 * LOG: Revision 4.4  2001/07/19 15:37:14  mmiers
 * LOG: Get the TID table right.
 * LOG:
 * LOG: Revision 4.3  2001/07/19 14:55:43  mmiers
 * LOG: Make wraparound reallocate work for incoming like outgoing.
 * LOG:
 * LOG: Revision 4.2  2001/05/15 20:25:17  mmiers
 * LOG: Don't add routes for every TID.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.5  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.4  2000/11/29 17:50:59  mmiers
 * LOG: Weird Cisco len fix.
 * LOG:
 * LOG: Revision 3.3  2000/09/06 16:11:42  mmiers
 * LOG: Suspenders and belts work with prim queue.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 17:28:18  mmiers
 * LOG: Ancient memory leak plugged.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:39  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.5  2000/07/14 17:23:21  fhasle
 * LOG:
 * LOG: updated TCAP to support ITU 97 and Timer Reset.
 * LOG:
 * LOG: Revision 2.4  2000/05/11 14:49:21  mmiers
 * LOG:
 * LOG: Bulletproof the DID range checks.
 * LOG:
 * LOG: Revision 2.3  2000/05/10 23:11:34  mmiers
 * LOG:
 * LOG:
 * LOG: Another rollover bug.
 * LOG:
 * LOG: Revision 2.2  2000/03/10 15:29:04  mmiers
 * LOG: Functions similar to DEC exports for addr and QOS manipulation.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 03:05:48  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/10/05 19:01:05  rsonak
 * LOG:
 * LOG:
 * LOG: Removed the #include <sccp.h> to make sure Split stack works. This is called
 * LOG: from tcap.h with the correct #define.
 * LOG:
 * LOG: Revision 1.4  1999/09/07 19:44:53  mmiers
 * LOG:
 * LOG:
 * LOG: Free invoke context when closing transaction.
 * LOG:
 * LOG: Revision 1.3  1999/08/31 21:25:47  mmiers
 * LOG:
 * LOG:
 * LOG: Correct #defines
 * LOG:
 * LOG: Revision 1.2  1999/08/31 15:00:02  rsonak
 * LOG:
 * LOG:
 * LOG: Work around not finding a TransactionContext when receiving a begin.
 * LOG: Correct allocation code to not look for the TID in the local
 * LOG: table if it is a new incoming dialogue.
 * LOG:
 * LOG: Revision 1.1  1999/08/27 16:51:10  mmiers
 * LOG:
 * LOG:
 * LOG: Split context management into protocol family specific implementations.
 * LOG: This is easier than trying to sanitize out the family specific data.
 * LOG:
 * LOG: Revision 1.17  1999/08/26 23:45:04  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.16  1999/08/26 15:24:14  mmiers
 * LOG:
 * LOG:
 * LOG: If the application selector is the default, when a DID or
 * LOG: CREF is allocated, add the context to the map.
 * LOG:
 * LOG: Revision 1.15  1999/08/04 13:30:34  mmiers
 * LOG:
 * LOG:
 * LOG: Commit my latest version.
 * LOG:
 * LOG: Revision 1.14  1999/08/04 01:36:50  mmiers
 * LOG:
 * LOG:
 * LOG: Update our library to reflect the correct contents.
 * LOG:
 * LOG: Revision 1.13  1999/06/15 22:32:07  mmiers
 * LOG:
 * LOG:
 * LOG: Add missing entry points for CCITT TCAP.
 * LOG:
 * LOG: Revision 1.12  1999/05/27 15:52:47  mmiers
 * LOG:
 * LOG:
 * LOG: Change TCAP protocol flow to use only local TIDs.
 * LOG:
 * LOG: Revision 1.11  1999/05/18 17:00:17  mmiers
 * LOG:
 * LOG:
 * LOG: Initial coding of ITU TCAP complete.  Much testing and fixme
 * LOG: removal to do.
 * LOG:
 * LOG: Revision 1.10  1999/05/17 23:05:38  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ITU TCAP.
 * LOG:
 * LOG: Revision 1.9  1999/04/09 15:45:57  mmiers
 * LOG:
 * LOG:
 * LOG: Tweaks to address check.  Update TODO
 * LOG:
 * LOG: Revision 1.8  1999/03/17 21:37:52  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.7  1999/03/17 20:55:08  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.6  1999/03/17 18:39:58  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.5  1998/10/15 01:19:20  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.4  1998/10/02 04:05:40  mmiers
 * LOG: Improve TCAP component handling.  The only thing that needs verification
 * LOG: is reject handling.
 * LOG:
 * LOG: Revision 1.3  1998/10/02 00:42:13  mmiers
 * LOG: Fix some major CPT handling bugs in TCAP (cmp).
 * LOG:
 * LOG: Revision 1.2  1998/09/30 21:54:40  jrao
 * LOG: Make UNI work with invokes.  Basically, we don't allocate an invoke
 * LOG: context for INVOKE's received in a UNI.  Need to verify this with
 * LOG: T1.114.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 19:24:40  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.7  1998/09/21 17:20:09  mmiers
 * LOG: Add tracing into everything.
 * LOG:
 * LOG: Revision 1.6  1998/07/07 21:11:41  mmiers
 * LOG: Fixes for TCAP timers.
 * LOG:
 * LOG: Revision 1.5  1998/07/01 22:53:36  mmiers
 * LOG: Add timer support in.
 * LOG:
 * LOG: Revision 1.4  1998/07/01 21:57:58  mmiers
 * LOG: Fix TCAP.
 * LOG:
 * LOG: Revision 1.3  1998/06/19 22:25:27  mmiers
 * LOG: Nearing the end for TCAP.  Initial implementation of SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/06/18 23:38:42  mmiers
 * LOG: TCAP debugging.
 * LOG:
 * LOG: Revision 1.1  1998/06/17 20:46:30  mmiers
 * LOG: Add vendor IntelliNet.
 * LOG:
 * LOG: Revision 1.5  1998/06/15 16:29:05  mmiers
 * LOG: Testing TCAP.
 * LOG:
 * LOG: Revision 1.4  1998/04/29 22:45:01  mmiers
 * LOG: Change ITS_TCAP to ITS_TCAP_SRC.
 * LOG:
 * LOG: Revision 1.3  1998/04/29 21:10:17  mmiers
 * LOG: Today's contribution to TCAP.  TODO: invoke context, automatic REJECTs
 * LOG: for protocol errors.
 * LOG:
 * LOG: Revision 1.2  1998/04/29 01:00:25  mmiers
 * LOG: Some false positives.  This is intended to commit the workspace/project
 * LOG: file changes.
 * LOG:
 * LOG: Revision 1.1  1998/04/29 00:23:35  mmiers
 * LOG: Add context routines.
 * LOG:
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
#include <its_hash.h>
#include <its_timers.h>
#include <its_dsm.h>
#include <its_assertion.h>
#include <its_redundancy.h>

#ident "$Id: itu-tcap_context.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#if defined(PRC)
#include <china/tcap.h>
#elif defined(TTC)
#include <japan/tcap.h>
#else
#include <itu/tcap.h>
#endif

#include "tcap_intern.h"

static ITS_BOOLEAN  started = ITS_FALSE;
static ITS_BOOLEAN  stopped = ITS_FALSE;

#define TCAP_NEXT_LTID_KEY          0xFFFFFFFD 
#define TCAP_NEXT_IDID_KEY          0xFFFFFFFE 
#define TCAP_DID_BEING_USED         0xFFFFFFFF

#define TCAP_RID    0

TCAP_TRANS_ENTRY*   LocalTxTable[MAX_NUM_DIALOGS];

extern ITS_MUTEX    __localTxGate;
extern ITS_MUTEX    __DIDGate;

extern ITS_UINT __nextLTID;
extern ITS_CTXT __nextOutDID;
extern ITS_CTXT __nextInDID;

/*
 * ITS_UINT nextIDID = 0;
 */

extern ITS_BOOLEAN isMsgBasedRedundancy;



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
void
TCAP_FormatShortKey(ITS_OCTET *key, ITS_CTXT value)
{
    if (key != NULL)
    {
        ITS_SET_CTXT(key, value);
    }

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
void
TCAP_FormatLongKey(ITS_OCTET *key, ITS_INT value)
{
    if (key != NULL)
    {
        key[0] = ((value >> 24) & 0xFF);
        key[1] = ((value >> 16) & 0xFF);
        key[2] = ((value >> 8) & 0xFF);
        key[3] = (value & 0xFF);
    }

    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
int
TCAP_Init_CCITT()
{
    int ret = ITS_SUCCESS;
    int i;

    splitTIDS = ITS_FALSE;
    splitDIDS = ITS_FALSE;

    /*
     * Here we allocate the DID table, on the DSM space. This will 
     * be use to get the dialogue Id for a ne transaction. 
     */
    if (started)
    {
        return (ITS_SUCCESS);
    }

    started = ITS_TRUE;

    /*
     * Initialize the local transaction table. This table will be used
     * to maintain a local copy of the ctx.
     */
    /* Using LocalTxTable array instead of hash table */

    for (i = 0; i < MAX_NUM_DIALOGS; i++)
    {
         LocalTxTable[i] = NULL;
    }

    if (!splitTIDS)
    {
        int error = 0;
        ITS_UINT *nextLTid = NULL;
        ITS_OCTET nextLTidKey[sizeof(ITS_UINT)];

        /*
         * We reserve the first element of the array for an integer that will
         * be decremented and used as the next localTID
         */
        TCAP_FormatLongKey(nextLTidKey, TCAP_NEXT_LTID_KEY);

        if (DSM_LockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS) == ITS_SUCCESS)
        { 
            nextLTid = DSM_FindNoLock(DSM_TcapFtGroupId, 
                                      DSM_TABLE_ITU_DIDS, 
                                      nextLTidKey, 
                                      sizeof(ITS_UINT), 
                                      &error);
        
            if (error == ITS_ENOTFOUND)
            {
                nextLTid = DSM_AllocNoLock(DSM_TcapFtGroupId, 
                                           DSM_TABLE_ITU_DIDS, 
                                           nextLTidKey, 
                                           sizeof(ITS_UINT), 
                                           sizeof(ITS_UINT), 
                                           &error);
                if (nextLTid != NULL)
                {
                    /* this I got from the HASH_Table module */
                    *nextLTid = -1;

                    ret = DSM_CommitNoLock(DSM_TcapFtGroupId, 
                                           DSM_TABLE_ITU_DIDS, 
                                           nextLTidKey, 
                                           sizeof(ITS_UINT), 
                                           (void *)nextLTid);

                    if (ret != ITS_SUCCESS)
                    {
                        TCAP_CRITICAL(("DSM_Commit Failled, Error Code %d\n", ret));
   
                        /* Unable to Commit Transaction ID to Table */
        
                        /* TCAP failed to Intialize -  No Memory. */

                        DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                        return ret;
                    }
                }
                else
                {
                    TCAP_CRITICAL(("DSM_Alloc Failled, Error Code %d\n", error));

                    /* TCAP failed to Intialize -  No Memory. */

                    DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                    return ITS_ENOMEM;
                }
            }
        }

        DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);
    }

    if (!splitDIDS)
    {
        ITS_OCTET nextIDidKey[sizeof(ITS_UINT)];
        ITS_CTXT *nextIDid = NULL;
        int error = 0;

        /*
         * We also need to reserve one key for generating the next IDID for incoming 
         * transactions. The next incoming DID will be determined in the function
         * TCAP_GetNextIDID().
         */

        if (DSM_LockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS) == ITS_SUCCESS)
        {
            TCAP_FormatLongKey(nextIDidKey, TCAP_NEXT_IDID_KEY);

            nextIDid = DSM_FindNoLock(DSM_TcapFtGroupId, 
                                      DSM_TABLE_ITU_DIDS, 
                                      nextIDidKey, 
                                      sizeof(ITS_UINT), 
                                      &error);

            if (error == ITS_ENOTFOUND)
            {
                nextIDid = (ITS_CTXT *)DSM_AllocNoLock(DSM_TcapFtGroupId, 
                                                       DSM_TABLE_ITU_DIDS,
                                                       nextIDidKey, 
                                                       sizeof(ITS_UINT), 
                                                       sizeof(ITS_CTXT),
                                                       &error);

                if (nextIDid != NULL)
                {
                    *nextIDid = TCAP_DIR_BIT;

                    ret = DSM_CommitNoLock(DSM_TcapFtGroupId,
                                           DSM_TABLE_ITU_DIDS, 
                                           nextIDidKey, 
                                           sizeof(ITS_UINT), 
                                           (void *)nextIDid);

                    if (ret != ITS_SUCCESS)
                    {
                        TCAP_CRITICAL(("DSM_Commit Failled, Error Code %d\n", 
                                       ret));
                        /* Unable to Commit Dialogue ID to Table */
        
                        /* TCAP failed to Intialize -  No Memory. */

                        DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                        return ret;
                    }
                }
                else
                {
                    TCAP_CRITICAL(("DSM_Alloc Failled, Error Code %d\n", error));
           
                    /* TCAP failed to Intialize -  No Memory. */

                    DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                    return ITS_ENOMEM;
                }
            }
        }

        DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);
    }
    else
    {
        /* allocate the DID Table */
#if 0
        nextIDID = txRanges.beginInDID;
#endif
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
void
TCAP_Term_CCITT()
{
    if (stopped)
    {
        return;
    }

    stopped = ITS_TRUE;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name     Date       Reference                 Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005  ACC651-SDS-TCEN-V1.0.02  Initialize the Component List 
 *                       ID :: D0020
 ****************************************************************************/
TCAP_TRANS_ENTRY *
TCAP_AllocateLocalTx_CCITT(ITS_CTXT did)
{
    TCAP_TRANS_ENTRY *tx = NULL;

    if ((tx = (TCAP_TRANS_ENTRY *)calloc(1, sizeof(TCAP_TRANS_ENTRY))) == NULL)
    {
        TCAP_CRITICAL(("AllocateLocalTx_CCITT: NO MEMORY for LocalTx for did %d\n",
                      did));

        return NULL;
    }

    if (LocalTxTable[did] != NULL)
    {
        TCAP_ERROR(("AllocateLocalTx_CCITT: LocalTx already exists for did %d\n",
                      did));

        /* Free tx */
        free(tx);
        return NULL;
    }

    tx->did = did;

    /* Initialize CptList as per Design ID :: D0020 */

    tx->num_CptList = 1;
    tx->cptList.next = NULL;

    if (MUTEX_AcquireMutex(&__localTxGate) != ITS_SUCCESS)
    {
        return (NULL);
    }

    LocalTxTable[did] = tx;

    if (MUTEX_ReleaseMutex(&__localTxGate) != ITS_SUCCESS)
    {
        return (NULL);
    }

    TCAP_DEBUG(("AllocateLocalTx_CCITT: Allocated LocalTx for did %d\n", did));   
    return tx;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
TCAP_TRANS_ENTRY*
TCAP_FindLocalTx_CCITT(ITS_CTXT did)
{
    return LocalTxTable[did];
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int 
TCAP_AllocateThisDID_CCITT(ITS_CTXT nextDID)
{
    int error = 0, ret = ITS_SUCCESS;
    TCAP_TRANS_ENTRY **didPtr;
    ITS_OCTET didKey[sizeof(ITS_CTXT)];
    TCAP_TRANS_ENTRY *localTx = NULL;

    TCAP_FormatShortKey(didKey, nextDID);

    if (DSM_LockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS) != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AllocateThisDID_CCITT: cannot aquire "
                    "mutex !!! \n"));
        /* CRITICAL - Unable to Lock Table. */

        return ITS_EBADMUTEX;
    }

    didPtr = DSM_FindNoLock(DSM_TcapFtGroupId,
                            DSM_TABLE_ITU_DIDS,
                            didKey,
                            sizeof(ITS_CTXT),
                            &error);
    if (didPtr != NULL)
    {
        /* the slot was already allocated, check if the pointer inside
           is NULL */

        if (*didPtr == NULL)
        {
            /* the slot is free, let's use it */

            *didPtr = (TCAP_TRANS_ENTRY *)TCAP_DID_BEING_USED;
#if ROUTE_WANTS_PERFORMANCE
            if (ROUTE_IsApplicationSelectorDefault())
            {
                ITS_HDR hdr;

                hdr.context.dialogue_id = *did;

                hdr.type = ITS_TCAP_CCITT;
                ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, &hdr);
            }
#endif

            ret = DSM_CommitNoLock(DSM_TcapFtGroupId,
                                   DSM_TABLE_ITU_DIDS,
                                   didKey,
                                   sizeof(ITS_CTXT),
                                   (void *)didPtr);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("DSM_Commit failed, Error Code: %d\n", ret));

                /* Unable to Commit Transaction Pointer to Table. */

                DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                return ret;
            }

            DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

            ret = ITS_SUCCESS;
        }
        else
        {
            /* We are screwed if we get here..Unlock and raise an assertion */

            ITS_BOOLEAN did_must_not_already_exist = ITS_FALSE;

            ret = DSM_CommitNoLock(DSM_TcapFtGroupId,
                                   DSM_TABLE_ITU_DIDS,
                                   didKey,
                                   sizeof(ITS_CTXT),
                                   (void *)didPtr);
            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("DSM_Commit failed, Error Code: %d\n", ret));

                /* Unable to Commit Transaction Pointer to Table. */
            }
            ITS_C_ASSERT(did_must_not_already_exist);

        }
    }
    else
    {
        /* first time that did is used, allocate the resources */
        didPtr = (TCAP_TRANS_ENTRY**)DSM_AllocNoLock(DSM_TcapFtGroupId,
                                                     DSM_TABLE_ITU_DIDS,
                                                     didKey,
                                                     sizeof(ITS_CTXT),
                                                     sizeof(TCAP_TRANS_ENTRY*),
                                                     &error);

        if (didPtr != NULL)
        {
            *didPtr = (TCAP_TRANS_ENTRY *)TCAP_DID_BEING_USED;


            ret = DSM_CommitNoLock(DSM_TcapFtGroupId,
                                   DSM_TABLE_ITU_DIDS,
                                   didKey,
                                   sizeof(ITS_CTXT),
                                   (void *)didPtr);

            if (ret != ITS_SUCCESS)
            {
                TCAP_CRITICAL(("DSM_Commit Failled, Error Code %d\n", ret));
                

                /* Unable to Commit Transaction Pointer to Table. */

                DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                return ret;
            }
        }
        else
        {
            TCAP_CRITICAL(("DSM_Alloc Failled, Error Code %d\n", error));

            /* Unable to Allocate Memory for Transaction Pointer in Table. */
            TCAP_Alarm_CCITT(1455, __FILE__, __LINE__, NULL);

            DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

            return ITS_ENOMEM;
        }

        DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

        ret = ITS_SUCCESS;
    }

    if (ret == ITS_SUCCESS)
    {
        localTx = TCAP_AllocateLocalTx_CCITT(nextDID);
        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_AllocateThisDID_CCITT: Cannot Allocate "
                        "Local Tx for did %d.\n", nextDID));

            return ITS_ENOMEM;

        }

        TCAP_DEBUG(("TCAP_AllocateThisDID_CCITT: Allocated "
                    "Local Tx for did %d.\n", nextDID));

        ret = AllocateLTIDinTx_CCITT(localTx);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_AllocateThisDID_CCITT: Cannot Allocate "
                        "LTID for did %d.\n", nextDID));

            return ITS_ENOMEM;

        }

        TCAP_DEBUG(("TCAP_AllocateThisDID_CCITT: Allocated "
                    "LTID for did %d.\n", nextDID));

        ret = ITS_SUCCESS;
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
static int
TCAP_AllocateSharedDID(ITS_CTXT *did)
{
    ITS_USHORT nodeId = 0;
    static ITS_CTXT nextDID = 0;
    int i, error = 0, ret = ITS_SUCCESS;
    TCAP_TRANS_ENTRY **didPtr;
    ITS_OCTET didKey[sizeof(ITS_CTXT)];
    ITS_EVENT evt;

    nodeId = DSM_GetNodeId();

    if (DSM_LockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS) != ITS_SUCCESS)
    {
        TCAP_ERROR(("TCAP_AllocateDialogueId_CCITT: cannot aquire "
                    "mutex !!! \n"));
        /* CRITICAL - Unable to Lock Table. */

        return ITS_EBADMUTEX;
    }

    for (i = 0; i < TCAP_DIR_BIT; i++)
    {
        nextDID++;

        if (isMsgBasedRedundancy && nodeId == 1)
        {
            if (nextDID % 2 == 0) nextDID++;
        }
        if (isMsgBasedRedundancy && nodeId == 2)
        {
            if (nextDID % 2 != 0) nextDID++;
        }

        /* The leading ++ ensures that nextDID is never 0 */

        if (nextDID >= TCAP_DIR_BIT)
        {
            nextDID = 0;

            continue;
        }

        TCAP_FormatShortKey(didKey, nextDID);

        didPtr = DSM_FindNoLock(DSM_TcapFtGroupId, 
                                DSM_TABLE_ITU_DIDS,
                                didKey, 
                                sizeof(ITS_CTXT),
                                &error);
        if (didPtr != NULL)
        {
            /* the slot was already allocated, check if the pointer inside
               is NULL */

            if (*didPtr == NULL)
            {
                /* the slot is free, let's use it */

                *didPtr = (TCAP_TRANS_ENTRY *)TCAP_DID_BEING_USED;

                *did = nextDID;

                 
#if ROUTE_WANTS_PERFORMANCE
                if (ROUTE_IsApplicationSelectorDefault())
                {
                    ITS_HDR hdr;

                    hdr.context.dialogue_id = *did;

                    hdr.type = ITS_TCAP_CCITT;
                    ROUTE_AddApplication(ITS_DEFAULT_USER_SRC, &hdr);
                }
#endif

                ret = DSM_CommitNoLock(DSM_TcapFtGroupId, 
                                       DSM_TABLE_ITU_DIDS,
                                       didKey, 
                                       sizeof(ITS_CTXT), 
                                       (void *)didPtr);

                if (ret != ITS_SUCCESS)
                {
                    TCAP_ERROR(("DSM_Commit failed, Error Code: %d\n", ret));   

                    /* Unable to Commit Transaction Pointer to Table. */

                    DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                    return ret;
                }

                DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                return (ITS_SUCCESS);
            }
            else
            {
                /* the slot is used, unlock and try the next one */

                ret = DSM_CommitNoLock(DSM_TcapFtGroupId, 
                                       DSM_TABLE_ITU_DIDS, 
                                       didKey, 
                                       sizeof(ITS_CTXT), 
                                       (void *)didPtr);
                if (ret != ITS_SUCCESS)
                {
                    TCAP_ERROR(("DSM_Commit failed, Error Code: %d\n", ret));   
                    
                    /* Unable to Commit Transaction Pointer to Table. */
                }

                continue;     
            } 
        }
        else
        {
            /* first time that did is used, allocate the resources */
            didPtr = (TCAP_TRANS_ENTRY**)DSM_AllocNoLock(DSM_TcapFtGroupId, 
                                                         DSM_TABLE_ITU_DIDS,
                                                         didKey, 
                                                         sizeof(ITS_CTXT),
                                                         sizeof(TCAP_TRANS_ENTRY*),
                                                         &error);

            if (didPtr != NULL)
            {
                *didPtr = (TCAP_TRANS_ENTRY *)TCAP_DID_BEING_USED;
 
                ret = DSM_CommitNoLock(DSM_TcapFtGroupId, 
                                       DSM_TABLE_ITU_DIDS,
                                       didKey, 
                                       sizeof(ITS_CTXT), 
                                       (void *)didPtr);

                if (ret != ITS_SUCCESS)
                { 
                     TCAP_CRITICAL(("DSM_Commit Failled, Error Code %d\n", ret));

                    /* Unable to Commit Transaction Pointer to Table. */

                    DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                    return ret;
                }

                PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
            }
            else
            {
                TCAP_CRITICAL(("DSM_Alloc Failled, Error Code %d\n", error));
               
                /* Unable to Allocate Memory for Transaction Pointer in Table. */

                DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

                return ITS_ENOMEM;
            }
           
            *did = nextDID;

            DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

            if (isMsgBasedRedundancy)
            {
                /* Multicast the allocated DID */
                ITS_EVENT_INIT(&evt, ITS_TCAP_DID_REQ, 1 + sizeof(ITS_CTXT) + sizeof (ITS_USHORT));
                evt.data[0] = TCAP_ALLOCATE_DID;
                evt.data[1] = nodeId;
                ITS_SET_CTXT(&evt.data[2], nextDID);

                if (DSM_MulticastStackEventToFtGroupMembers(
                   DSM_TcapFtGroupId,
                   evt,
                   ITS_TCAP_DID_REQ,
                   ITS_TCAP_CCITT_SRC) == ITS_SUCCESS)
                {
                    TCAP_DEBUG(("TCAP_AllocateSharedDID: Succesfully multicasted"
                                "did %d, nodeId %d\n", nextDID, nodeId));
                }
           
                ITS_EVENT_TERM(&evt);
           }
           return ITS_SUCCESS;
        }
    }
    
    /* Unable to Allocate Memory for Transaction Context in Table. */

    DSM_UnlockTable(DSM_TcapFtGroupId, DSM_TABLE_ITU_DIDS);

    return (ITS_ENOMSGSPACE);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This method allocates the next available dialogue id for the user.
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
 *      This method should be used for originating transactions ONLY
 *      (not that the user has visibility into received transactions).
 *
 *  See Also:
 ****************************************************************************/
int
INTELLINET_AllocateDID_CCITT(ITS_SS7_HANDLE handle,
                             ITS_CTXT *did)
{
    int ret = ITS_SUCCESS;
    ITS_CTXT i = 0;
    TCAP_TRANS_ENTRY *localTx = NULL;
    ITS_BOOLEAN didAllocated = ITS_FALSE;

    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    if (redunClass)
    {
        if (REDUNDANCY_CONFIGURED_TYPE(redunClass) == ITS_ACTIVE_STANDBY)
        {
            if (REDUNDANCY_GET_NODE_STATE(redunClass) == ITS_STATE_BACKUP)
            {
                TCAP_ERROR(("Backup Node Cannot Initiate Messages.\n"));

                *did = 0;

                return (ITS_EINVINITSTATE);
            }
        }
    }
    splitDIDS = ITS_FALSE;

    if (!splitDIDS)
    {
        ret = TCAP_AllocateSharedDID(did);
        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("Cannot Allocate Shared Tx Ctxt for did %d.\n", *did));
            return ret;
        }
        else
        {
            didAllocated = ITS_TRUE;
        }
    }
    else
    {
        ITS_BOOLEAN locked = ITS_FALSE;

        TCAP_DEBUG(("SplitDIDs! Total TCAP nodes = %d, This TCAP node = %d\n",
                     totalTCAPNodes, localTCAPNodeID));

        /*
         * Note: if all dids are used, we loop bask to first did
         * what if it is also in use then we will never return
         */

        if (MUTEX_AcquireMutex(&__DIDGate) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        locked = ITS_TRUE;

        for (i = txRanges.beginOutDID; i <= txRanges.endOutDID; i++)
        {
            __nextOutDID++;

            /* The leading ++ ensures that nextDID is never 0 */
            if (__nextOutDID > txRanges.endOutDID)
            {
                __nextOutDID = txRanges.beginOutDID;
            }

            if (LocalTxTable[__nextOutDID] == NULL)
            {
                *did = __nextOutDID;
                didAllocated = ITS_TRUE;

                if (locked && MUTEX_ReleaseMutex(&__DIDGate) != ITS_SUCCESS)
                {
                    return (ITS_EBADMUTEX);
                }

                locked = ITS_FALSE;

                break; 
            }
        }

        if (locked && MUTEX_ReleaseMutex(&__DIDGate) != ITS_SUCCESS)
        {
            return (ITS_EBADMUTEX);
        }

        locked = ITS_FALSE;
    }

    if (!didAllocated)
    {
        TCAP_CRITICAL(("INTELLINET_AllocateDID_CCITT: Cannot Allocate DID"));

         TCAP_Alarm_CCITT(1455, __FILE__, __LINE__, NULL);
 
        return ITS_ENOMSGSPACE;
    }

    localTx = TCAP_AllocateLocalTx_CCITT(*did);
    if (localTx == NULL)
    {
        TCAP_ERROR(("INTELLINET_AllocateDID_CCITT: Cannot Allocate "
                    "Local Tx for did %d.\n", *did));

        ret = ITS_ENOMEM;
        return ret;
    }

    TCAP_DEBUG(("INTELLINET_AllocateDID_CCITT: Allocated "
                "Local Tx for did %d.\n", *did));

    ret = AllocateLTIDinTx_CCITT(localTx);

    if (ret != ITS_SUCCESS)
    {
        TCAP_ERROR(("INTELLINET_AllocateDID_CCITT: Cannot Allocate "
                    "LTID for did %d.\n", *did));

        ret = ITS_ENOMEM;
        return ret;
    }

    TCAP_DEBUG(("INTELLINET_AllocateDID_CCITT: Allocated "
                "LTID for did %d.\n", *did));

    return ret;
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
TCAP_GetNextSharedIDID(ITS_CTXT *idid)
{
    ITS_CTXT *nextIDid = NULL;
    int error = 0, ret = ITS_SUCCESS;
    ITS_OCTET nextIDidKey[sizeof(ITS_UINT)];

    TCAP_FormatLongKey(nextIDidKey, TCAP_NEXT_IDID_KEY);

    while ((nextIDid = (ITS_CTXT *)DSM_Find(DSM_TcapFtGroupId, 
                                            DSM_TABLE_ITU_DIDS, 
                                            nextIDidKey, 
                                            sizeof(ITS_UINT),
                                            &error)) == NULL)
    {
        TIMERS_USleep(100);
    }

    if (nextIDid != NULL)
    {
        (*nextIDid)++;
        
        if (*nextIDid < TCAP_DIR_BIT)
        {
            *nextIDid = TCAP_DIR_BIT;
        }

        *idid = *nextIDid;

        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         nextIDidKey, 
                         sizeof(ITS_UINT), 
                         (void *)nextIDid);

        if (ret != ITS_SUCCESS)
        {
            TCAP_CRITICAL(("TCAP_GetNextSharedIDID: DSM_Commit Failed, Error "
                           "Code %d\n", ret));
            
            /* Unable to Commit Dialogue ID to Table. */

            return ret;
        }

	PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_DIALOGUE);
    }
    else
    {
        TCAP_CRITICAL(("TCAP_GetNextSharedIDID: DSM_Find returned NULL, Error "
                       "Code %d\n", error));
            
        /* Unable to find entry for Dialogue ID in Table. */

        return error;
    }

    return ret;
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
TCAP_GetNextIDID_CCITT(ITS_CTXT *idid)
{
    int ret = ITS_SUCCESS;

    splitDIDS = ITS_FALSE;

    if (!splitDIDS)
    {
        ret = TCAP_GetNextSharedIDID(idid);
    }
    else
    { 
        ITS_CTXT i;

        for (i = txRanges.beginInDID; i <= txRanges.endInDID; i++)
        {
            __nextInDID++;

            if (__nextInDID > txRanges.endInDID)
            {
                __nextInDID = txRanges.beginInDID;
            }

            if (LocalTxTable[__nextInDID] == NULL)
            {
                *idid = __nextInDID;

                return (ITS_SUCCESS);
            }
        }

        ret = ITS_ENOMSGSPACE;
    }

    return ret;
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
static ITS_INT
TCAP_GetNextSharedLTID()
{
    ITS_UINT *nextLTid = NULL, ret = ITS_SUCCESS;
    ITS_UINT ltid = 0;
    int error = 0;
    
    ITS_OCTET nextLTidKey[sizeof(ITS_UINT)];

    TCAP_FormatLongKey(nextLTidKey, TCAP_NEXT_LTID_KEY);

    while ((nextLTid = DSM_Find(DSM_TcapFtGroupId, 
                                DSM_TABLE_ITU_DIDS, 
                                nextLTidKey, 
                                sizeof(ITS_UINT), 
                                &error)) == NULL)
    {
        TIMERS_USleep(100);
    }

    if (nextLTid != NULL)
    {
        /* this was taken from the IntelliSS7 Hash table module GetUniqueKey */
        (*nextLTid)--;

        ltid = *nextLTid;

        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         nextLTidKey, 
                         sizeof(ITS_UINT), 
                         (void *)nextLTid);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_GetNextLTID, DSM_Commit returned code: %d\n"));
            
            /* Unable to Commit Transaction ID to Table. */

            return 0;
        }
    }
    else
    {
        TCAP_ERROR(("TCAP_GetNextLTID, DSM_Find returned NULL\n"));
        
        /* Unable to find entry for Transaction ID in Table. */

        return 0;
    }

    return ltid;

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
static ITS_INT
TCAP_GetNextLTID()
{
    ITS_INT ret = ITS_SUCCESS;

    splitTIDS = ITS_FALSE;
    if (!splitTIDS)
    {
        ret = TCAP_GetNextSharedLTID();
    }
    else
    {
        __nextLTID++;

        if (__nextLTID > txRanges.endTID)
        {
            __nextLTID = txRanges.beginTID;
        }

        ret = __nextLTID;
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
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
TCAP_TRANS_ENTRY *
TCAP_AllocTransactionContext_CCITT(ITS_UINT ltid, ITS_OCTET *key, int *klen)
{
    TCAP_TRANS_ENTRY *tx = NULL;
    int error = 0;
    ITS_OCTET nextLTidKey[sizeof(ITS_UINT)];

    TCAP_FormatLongKey(nextLTidKey, ltid);

    tx = DSM_Alloc(DSM_TcapFtGroupId, 
                   DSM_TABLE_ITU_TCAP_DLG, 
                   nextLTidKey, 
                   sizeof(ITS_UINT), 
                   sizeof(TCAP_TRANS_ENTRY), 
                   &error);

    if (tx == NULL)
    {
        TCAP_CRITICAL(("TCAP_AllocTransactionContext_CCITT: DSM_Alloc " 
                       "failed, error code: %d\n", error));        
        /* Unable to Allocate Memory for Transaction Context in Table. */

        return NULL;
    }
    
    /* give the key to the context to the caller so he can call DSM_Commit */
    if (key != NULL)
    {
        *klen = 4;

        memcpy(key, nextLTidKey, 4);
    }

    return (tx);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
int
AllocateLTIDinTx_CCITT(TCAP_TRANS_ENTRY* tx)
{
    ITS_UINT nextLTid = 0;

    /* Allocate LTID here only, as we need that in the invoke context 
       When the invoke-timer pops, the only way it can retrieve the 
       Invoke-Context is by DSM lookup on LTID. 
    */
    nextLTid = TCAP_GetNextLTID();

    TCAP_DEBUG(("TCAP_AllocateLocalTx_CCITT: DID <---> TID : %d <---> %u\n",
                tx->did, nextLTid));

    tx->ltid = nextLTid;

    return ITS_SUCCESS;
}
   
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
int
TCAP_PopulateLocalTx_CCITT(TCAP_TRANS_ENTRY *tx, ITS_CTXT did,
                           ITS_UINT tid, ITS_UINT tidLen,
                           SCCP_ADDR *cdp, SCCP_ADDR *clp)
{
    int dir;

    if (did == 0) /* incoming transaction */
    {
        TCAP_CRITICAL(("TCAP_PopulateLocalTx_CCITT: I-DID is ZERO!!!!\n"));

        return ITS_ENOMEM;

#if 0
        if (TCAP_GetNextIDID_CCITT(&did) != ITS_SUCCESS)
        {
            return ITS_ENOMEM;
        }
#endif

    }

    if (did & TCAP_DIR_BIT)
    {
        dir = DLG_INCOMING;
    }
    else
    {
        dir = DLG_OUTGOING;
    }

    if (tx != NULL)
    {
        tx->ctime = time(NULL);
        tx->oaddr = *clp;
        tx->daddr = *cdp;
        tx->dir = dir;
        tx->state = ITS_TCAP_IDLE;
        tx->dstate = ITS_DLG_NONE;
        tx->rtid = tid;
        tx->rtidLen = tidLen;

        PEG_IncrPeg(CCITT_TCAP_Pegs, PEG_TCAP_ACTIVE_TRANSACTIONS);
    }
    else
    {
        TCAP_CRITICAL(("TCAP_PopulateTransactionTx_CCITT: Tx is NULL\n"));

        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name     Date        Reference                Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005  ACC651-SDS-TCEN-V1.0.02  Free CptList in DSM if
 *                       ID :: D0050              allocated. Refer FindInvokeContext
 ****************************************************************************/
int
TCAP_FreeLocalTx_CCITT(ITS_CTXT did)
{
    TCAP_TRANS_ENTRY *localTx = NULL;
    TCAP_CPT_LIST *CptList = NULL;
    TCAP_CPT_LIST *temp = NULL;
    TCAP_CPT_LIST *nextNode = NULL;
    ITS_OCTET invKey[sizeof(ITS_UINT)];
    int i, j, ret;

    if ((localTx = TCAP_FindLocalTx_CCITT(did)))
    {
        /* Reorganize the Code Per Design ID :: D0050 */

        CptList = &localTx->cptList;

        for (i = 0; i < localTx->num_CptList; i++)
        {
            if (CptList != NULL)
            {
                for (j = 0; j < TCAP_CTX_MAX_CPT_ENTRIES; j++)
                {
                    if (CptList->cptEntry[j].inUse &&
                        CptList->cptEntry[j].timer)
                    {
                        TCAP_DEBUG(("TCAP_FreeLocalTx_CCITT: Cancelling running timer "
                                    "for cpt in use, did %d, InvkId %d, timer %d\n",
                                    localTx->did, CptList->cptEntry[j].invoke_id,
                                    CptList->cptEntry[j].timer));

                        TIMERS_CancelSharedTimer(CptList->cptEntry[j].timer);

                        CptList->cptEntry[j].timer = TIMER_BAD_SERIAL;
                    }
                }

                if (i > 0)
                {
                    temp = CptList;
                    nextNode = temp->next;
                    CptList = nextNode;

                    TCAP_FormatLongKey(invKey, ((did << 8) | i));

                    /* Free the Array from DSM */
                    ret = DSM_Free(DSM_TcapFtGroupId,
                                   DSM_TABLE_ITU_TCAP_DLG,
                                   invKey,
                                   sizeof(ITS_UINT),
                                   (void *)temp);

                    if (ret != ITS_SUCCESS)
                    {
                        TCAP_ERROR(("TCAP_FreeLocalTx_CCITT: DSM_Free "
                                    "failed for did %d, error code: %d\n", did, ret));
                    }
                    else
                    {
                        TCAP_DEBUG(("TCAP_FreeLocalTx_CCITT: DSM_Free Cpt List %d "
                                    "for did %d\n", i, did));
                    }
                }
                else
                {
                    CptList = CptList->next;
                }
            }
        }

        free(LocalTxTable[did]);

        TCAP_DEBUG(("FreeLocalTx_CCITT: Freed LocalTx for did %d\n", did));
    }
    else
    {
        TCAP_DEBUG(("FreeLocalTx_CCITT: Cannot find LocalTx for did %d\n", did));
        return ITS_ENOTFOUND;
    }

    /* Empty the queue */
    if (DHAHandleDIDClean_CCITT(did) == ITS_SUCCESS)
    { 
        TCAP_DEBUG(("FreeLocalTx_CCITT: Emptied the component queue for did %d\n", 
                     did));
    }
    else
    {
        TCAP_ERROR(("FreeLocalTx_CCITT: Cannot empty the component queue "
                    "for did %d\n", 
                     did));
    }
   
    if (MUTEX_AcquireMutex(&__localTxGate) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    LocalTxTable[did] = NULL;

    if (MUTEX_ReleaseMutex(&__localTxGate) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    return ITS_SUCCESS; 
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
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference               Description
 * -----------------------------------------------------------------------------
 * sbabu     04-07-2005  Bug Id #885             During the Success call Warning 
 *                                               trace are generated by TCAP 
 *                                               stack. 
 ****************************************************************************/
TCAP_TRANS_ENTRY *
TCAP_FindTransactionContext_CCITT(ITS_UINT tid, ITS_OCTET *key, int *klen)
{
    TCAP_TRANS_ENTRY *tx = NULL;
    int error = 0;
    ITS_OCTET tidKey[sizeof(ITS_UINT)];

    /* 
     * TODO... think about this more as ther might still be some race 
     * condition in doing this that way .... if 2 redundant sys are running
     * at the same time.....
     */

    TCAP_FormatLongKey(tidKey, tid);
    
    tx = DSM_Find(DSM_TcapFtGroupId, 
                  DSM_TABLE_ITU_TCAP_DLG, 
                  tidKey, 
                  sizeof(ITS_UINT),
                  &error);

    if (tx != NULL)
    {
        if (key != NULL)
        {
            *klen = 4;
            memcpy(key, tidKey, 4);
        }
        else
        {
            TCAP_ERROR(("NULL key for DSM_Find : did %d.\n", tx->did));
        }

        TCAP_DEBUG(("TCAP_FindTransactionContext: DSM context found"
                    "for did %d, tid %u.\n", tx->did, tid));

        return tx;

        /*
         * !!!!!!! caller will have to release the time lock by calling 
         * DSM_Commit() !!!!!
         */
    }
#if 0                 
    TCAP_WARNING(("TCAP_FindTransactionContext: DSM context NOT found.\n"));
#endif

    /* Unable to find entry for Transaction Context in Table. */

    /* do not need to unlock if Find retruns NULL */
    return (NULL);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      used from SCCP UP 
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
 ****************************************************************************/
TCAP_TRANS_ENTRY *
TCAP_CopyDSMTxToLocalTx_CCITT(TCAP_TRANS_ENTRY *sharedTx)
{
    TCAP_TRANS_ENTRY *localTx = NULL;

    if ((localTx = TCAP_FindLocalTx_CCITT(sharedTx->did)) == NULL)
    {
        localTx = TCAP_AllocateLocalTx_CCITT(sharedTx->did);
        if (localTx == NULL)
        {
            TCAP_ERROR(("TCAP_CopyDSMTxToLocalTx_CCITT: Cannot allocate local context"
                         "for did %d.\n", sharedTx->did));
            return NULL;
        }

        memcpy(localTx, sharedTx, sizeof(TCAP_TRANS_ENTRY));

        TCAP_DEBUG(("TCAP_CopyDSMTxToLocalTx_CCITT: Copied DSMTx to LocalTx"
                    "for did %d.\n", sharedTx->did));
    }
    else
    {
        /* Yogi: I don't understand the need to update the localTx from the
         * sharedTx. Since "ideally" they should be in synch. And in case 
         * they are not, the localTx should be the recent/updated one.
         * see bug 284. In that case, the sharedTx didn't have any entry
         * whereas the localTx had an entry which is correct. In any case I
         * didn't see any issue with commenting this out. But if need be
         * this can be put back. But the HandleTimeout function would need
         * modification. 
         */
#if 0
        TCAP_WARNING(("TCAP_CopyDSMTxToLocalTx_CCITT: Found existing local "
                      "context for did %d with tid %u.\n",
                      sharedTx->did, sharedTx->ltid));

        TCAP_WARNING(("Existing local context for did %d is probably due "          
                      "to a timeout received earlier.\n", sharedTx->did));

        memcpy(localTx, sharedTx, sizeof(TCAP_TRANS_ENTRY));

        TCAP_DEBUG(("TCAP_CopyDSMTxToLocalTx_CCITT: Copied DSMTx to LocalTx"
                    "for did %d.\n", sharedTx->did));

        /*return NULL*/; /* NULL is being returned to catch the errors */
        /* Dont return NULL. If an existing localTx is found, 
           update it with the sharedTx */
#endif
    }

    return localTx;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
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
 *      void
 *
 *  Notes:
 *      
 *  See Also:
 ****************************************************************************/
void 
TCAP_FindAndFreeTransactionContext_CCITT(ITS_UINT ltid, ITS_OCTET* tidKey, int* tidKeyLen)
{
    TCAP_TRANS_ENTRY *sharedTx = NULL;

    sharedTx = TCAP_FindTransactionContext_CCITT(ltid,
                                                 tidKey, tidKeyLen);
    if (sharedTx == NULL)
    {
        TCAP_DEBUG(("TCAP_FindAndFreeTransactionContext_CCITT: Cannot Find DSM Tx for tid"
                    "%u.\n", ltid));
    }
    else
    {
        TCAP_DEBUG(("TCAP_FindAndFreeTransactionContext_CCITT: Freeing DSM Tx for ltid"
                    "%u.\n", ltid));

        TCAP_FreeDSMTransactionContext_CCITT(sharedTx);
    }
    
    return;
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
void
TCAP_FreeDSMTransactionContext_CCITT(TCAP_TRANS_ENTRY *trCtxt)
{
    int error = 0, ret = ITS_SUCCESS; 
    TCAP_TRANS_ENTRY **didPtr = NULL;
    ITS_CTXT did = 0;
    ITS_OCTET didKey[sizeof(ITS_CTXT)];
    ITS_OCTET tidKey[sizeof(ITS_UINT)];

    TCAP_FormatShortKey(didKey, trCtxt->did);

    did = trCtxt->did;

    splitDIDS = ITS_FALSE;

    if (!splitDIDS && trCtxt->did < TCAP_DIR_BIT)
    {
        /* clean the DID table */
        didPtr = DSM_Find(DSM_TcapFtGroupId, 
                          DSM_TABLE_ITU_DIDS,
                          didKey, 
                          sizeof(ITS_CTXT), 
                          &error);

        if (didPtr != NULL)
        {
            *didPtr = NULL;

            ret = DSM_Commit(DSM_TcapFtGroupId, 
                             DSM_TABLE_ITU_DIDS,
                             didKey, 
                             sizeof(ITS_CTXT),
                             (void *)didPtr);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_FreeTransactionContext_CCITT: DSM_Commit "
                            "failed for did %d, error code: %d\n", did, ret));
                
                /* Unable to Commit Transaction Pointer to Table. */
            }
        }
        else
        {
            TCAP_WARNING(("TCAP_FreeTransactionContext_CCITT: DSM_Find "
                          "failed for did %d, error code: %d\n", did, error));

           
            /* Unable to find entry for Transaction Pointer in Table. */

        }
    }
    TCAP_FormatLongKey(tidKey, trCtxt->ltid);

    /* clean the TID table on DSM */

    ret = DSM_Free(DSM_TcapFtGroupId, 
                   DSM_TABLE_ITU_TCAP_DLG,
                   tidKey, 
                   sizeof(ITS_UINT),
                   (void *)trCtxt);

    if (ret != ITS_SUCCESS)
    {   
        TCAP_ERROR(("TCAP_DSMFreeTransactionContext: DSM_Free "
                    "failed for did %d, error code: %d\n", did, ret));
    
        /* Unable to Free Transaction Context to Table. */
    }       
    else
    {
        TCAP_DEBUG(("TCAP_DSMFreeTransactionContext: DSM context freed "
                    "for did %d.\n", did));

        trCtxt = NULL;
    }

    return;
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
int
INTELLINET_FetchAddrs_CCITT(ITS_SS7_HANDLE handle,
                            ITS_CTXT did,
                            SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    TCAP_TRANS_ENTRY *tx;
    int error = 0, ret = ITS_SUCCESS;

    ITS_OCTET didKey[sizeof(ITS_CTXT)];

    TCAP_FormatShortKey(didKey, did);

    tx = DSM_Find(DSM_TcapFtGroupId, 
                  DSM_TABLE_ITU_DIDS, 
                  didKey,
                  sizeof(ITS_CTXT), 
                  &error);

    if (tx != NULL)
    {
        if (oaddr)
        {
            *oaddr = tx->oaddr;
        }

        if (daddr)
        {
            *daddr = tx->daddr;
        }

        /* - TODO - here we do not realy need a real commit */
        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         didKey,
                         sizeof(ITS_CTXT), 
                         tx);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_FetchAddrs_CCITT: DSM_Commit failed, error "
                        "code %d\n", ret));
            
            /* Unable to Commit Transaction Pointer to Table. */

            return ret;
        }
    }
    else
    {
        /* Unable to find entry for Transaction Pointer in Table. */

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
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
int
INTELLINET_SetAddrs_CCITT(ITS_HANDLE handle, ITS_CTXT did,
                          SCCP_ADDR *oaddr, SCCP_ADDR *daddr)
{
    TCAP_TRANS_ENTRY *tx, **txPtr = NULL;
    int error = 0, ret = ITS_SUCCESS;
    ITS_UINT tid;

    ITS_OCTET didKey[sizeof(ITS_CTXT)];
    ITS_OCTET tidKey[sizeof(ITS_UINT)];

    TCAP_FormatShortKey(didKey, did);

    txPtr = (TCAP_TRANS_ENTRY**)DSM_Find(DSM_TcapFtGroupId, 
                                         DSM_TABLE_ITU_DIDS, 
                                         didKey, 
                                         sizeof(ITS_CTXT), 
                                         &error);

    if (txPtr!= NULL)
    {
        tid = (*txPtr)->ltid;

        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         didKey, 
                         sizeof(ITS_CTXT), txPtr);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_SetAddrs_CCITT: DSM_Commit failed, error "
                        "code %d\n", ret));
            
            /* Unable to Commit Transaction Pointer to Table. */

            return ret;
        }
        
        TCAP_FormatLongKey(tidKey, tid);
    
        tx = DSM_Find(DSM_TcapFtGroupId, 
                      DSM_TABLE_ITU_TCAP_DLG, 
                      tidKey, 
                      sizeof(ITS_UINT),
                      &error);

        if (tx != NULL)
        {
            if (oaddr)
            {
                tx->oaddr = *oaddr;
            }   

            if (daddr)
            {
                tx->daddr = *daddr;
            }

            ret = DSM_Commit(DSM_TcapFtGroupId, 
                             DSM_TABLE_ITU_TCAP_DLG,
                             tidKey, 
                             sizeof(ITS_UINT), 
                             tx);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_SetQOS_CCITT: DSM_Commit failed, error "
                            "code %d\n", ret));
                return ret;
            }
        }
        else
        {
            TCAP_ERROR(("TCAP_SetAddrs_CCITT: Could not find Trans Ctxt, tid: %u\n",
                        tid));

            return (ITS_ENOTFOUND);
        }
    }
    else
    {
        /* Unable to find entry for Transaction Pointer in Table. */

        TCAP_ERROR(("TCAP_SetAddrs_CCITT: Could not find DID entry, DID: %d\n",
                     did));

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
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
int
INTELLINET_FetchQOS_CCITT(ITS_SS7_HANDLE handle,
                          ITS_CTXT did, DLG_QOS *qos)
{
    TCAP_TRANS_ENTRY *tx;
    int error = 0, ret = ITS_SUCCESS;

    ITS_OCTET didKey[sizeof(ITS_CTXT)];

    TCAP_FormatShortKey(didKey, did);

    tx = DSM_Find(DSM_TcapFtGroupId, 
                  DSM_TABLE_ITU_DIDS, 
                  didKey,
                  sizeof(ITS_CTXT), 
                  &error);

    if (tx != NULL)
    {

        *qos = tx->qos;

        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         didKey,
                         sizeof(ITS_CTXT), 
                         tx);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_FetchAddrs_CCITT: DSM_Commit failed, error "
                        "code %d\n", ret));
            
            /* Unable to Commit Transaction Pointer to Table. */

            return ret;
        }
    }
    else
    {
        /* Unable to find entry for Transaction Pointer in Table. */

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
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
int
INTELLINET_SetQOS_CCITT(ITS_SS7_HANDLE handle,
                        ITS_CTXT did, DLG_QOS *qos)
{
    TCAP_TRANS_ENTRY *tx, **txPtr = NULL;
    int error = 0, ret = ITS_SUCCESS;
    ITS_UINT tid;
    ITS_OCTET didKey[sizeof(ITS_CTXT)];
    ITS_OCTET tidKey[sizeof(ITS_UINT)];

    TCAP_FormatShortKey(didKey, did);

    txPtr = DSM_Find(DSM_TcapFtGroupId, 
                     DSM_TABLE_ITU_DIDS, 
                     didKey,
                     sizeof(ITS_CTXT), 
                     &error);

    if (txPtr != NULL)
    {
        tid = (*txPtr)->ltid;

        ret = DSM_Commit(DSM_TcapFtGroupId, 
                         DSM_TABLE_ITU_DIDS, 
                         didKey,
                         sizeof(ITS_CTXT), 
                         txPtr);

        if (ret != ITS_SUCCESS)
        {
            TCAP_ERROR(("TCAP_SetQOS_CCITT: DSM_Commit failed, error "
                        "code %d\n", ret));
            
            /* Unable to Commit Transaction Pointer to Table. */

            return ret;
        }

        TCAP_FormatLongKey(tidKey, tid);
    
        tx = DSM_Find(DSM_TcapFtGroupId, 
                      DSM_TABLE_ITU_TCAP_DLG,
                      tidKey, 
                      sizeof(ITS_UINT),
                      &error);

        if (tx != NULL)
        {
            *qos = tx->qos;
            
            ret = DSM_Commit(DSM_TcapFtGroupId, 
                             DSM_TABLE_ITU_TCAP_DLG,
                             tidKey, 
                             sizeof(ITS_UINT), 
                             tx);

            if (ret != ITS_SUCCESS)
            {
                TCAP_ERROR(("TCAP_SetQOS_CCITT: DSM_Commit failed, error "
                            "code %d\n", ret));
                return ret;
            }
        }
        else
        {
            TCAP_ERROR(("TCAP_SetQOS_CCITT: Could not find Trans Ctxt, tid: %u\n",
                        tid));

            return (ITS_ENOTFOUND);
        }
    }
    else
    {
        /* Unable to find entry for Transaction Pointer in Table. */

        
        TCAP_ERROR(("TCAP_SetQOS_CCITT: Could not find DID entry, DID: %d\n",
                     did));

        return (ITS_ENOTFOUND);
    }

    return (ITS_SUCCESS);
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name     Date         Reference                Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005   ACC651-SDS-TCEN-V1.0.02  Memory Allocation for new 
 *                        ID :: D0030              added node(array of 8 cpt) 
 *
 ****************************************************************************/
TCAP_INVOKE_ENTRY *
TCAP_FindInvokeContext_CCITT(ITS_CTXT did,
                             CPT_INV_ID *invokeId,
                             int dir)
{
    int error = 0, ret = ITS_SUCCESS;
    ITS_OCTET inv;
    TCAP_TRANS_ENTRY* tx = NULL;
    TCAP_INVOKE_ENTRY* tmp = NULL;
    TCAP_CPT_LIST *cptL = NULL;
    TCAP_CPT_LIST *cptList = NULL;
    ITS_OCTET invKey[sizeof(ITS_UINT)];
    ITS_UINT j;

    if (invokeId->data[1] == 2)
    {
        inv = invokeId->data[3];
    }
    else
    {
        inv = invokeId->data[2];
    }

    if ((tx = LocalTxTable[did]) != NULL)
    {
        cptList = &tx->cptList;
        while (cptList != NULL)
        {
            for (j = 0; j < TCAP_CTX_MAX_CPT_ENTRIES; j++)
            {
                if (cptList->cptEntry[j].invoke_id == inv &&
                    cptList->cptEntry[j].dir == dir &&
                    cptList->cptEntry[j].inUse)
                {

                    TCAP_DEBUG(("CPT Ctxt Found being used, did %d, IvkId %d,"
                                 "dir %d.\n", did, inv, dir));

                    return &cptList->cptEntry[j];
                }
                /* While you are looping, keep track of the first free
                   cptEntry */
                if (!tmp && !(cptList->cptEntry[j].inUse))
                {
                    tmp = &cptList->cptEntry[j];
                }
            }

            /* Changes per Design ID :: D0030 
             * Creates new node(TCAP_CPT_LIST) once TCAP_CTX_MAX_CPT_ENTRIES reaches and
             * add node to the list. Form a linked array list if it crosses multiples
             * of TCAP_CTX_MAX_CPT_ENTRIES 
             */

            if (tmp == NULL && cptList->next == NULL)
            {
                TCAP_FormatLongKey(invKey, ((did << 8) | tx->num_CptList));

                cptL = DSM_Find(DSM_TcapFtGroupId,
                                DSM_TABLE_ITU_TCAP_DLG,
                                invKey,
                                sizeof(ITS_UINT),
                                &error);

                if (error == ITS_ENOTFOUND)
                {
                    cptL = DSM_Alloc(DSM_TcapFtGroupId,
                                     DSM_TABLE_ITU_TCAP_DLG,
                                     invKey,
                                     sizeof(ITS_UINT),
                                     sizeof(TCAP_CPT_LIST),
                                     &error);

                    if (cptL != NULL)
                    {
                        cptL->next = NULL;
                        cptList->next = cptL;

                        /* update number of Cptlist in transaction */
                        tx->num_CptList = tx->num_CptList + 1;

                        ret = DSM_Commit(DSM_TcapFtGroupId,
                                         DSM_TABLE_ITU_TCAP_DLG,
                                         invKey,
                                         sizeof(ITS_UINT),
                                         (void *)cptL);

                        if (ret != ITS_SUCCESS)
                        {
                            TCAP_ERROR(("TCAP_FindInvokeContext_CCITT: DSM_Commit failed, error "
                                        "code %d\n", ret));

                            return (NULL);
                        }
                        else
                        {
                            TCAP_DEBUG(("TCAP_FindInvokeContext_CCITT: Successfully allocated "
                                        "Cpt List %d for did %d\n", tx->num_CptList - 1, did));
                        }
                    }
                    else
                    {
                        TCAP_CRITICAL(("TCAP_FindInvokeContext_CCITT: DSM_Alloc "
                                       "failed, error code: %d\n", error));

                        return (NULL);
                    }
                }
            }
            cptList = cptList->next;
        }

        TCAP_DEBUG(("CPT Ctxt Not Found, did %d, IvkId %d, dir %d." 
                    "Returning the first free entry in the cpt-array.\n",
                    did, inv, dir));

        /*If not found, then return the first free entry*/
        return tmp; 
    }
    else
    {
        TCAP_DEBUG(("LocalTx Entry Not Found for did %d, \n", did));
    }
    
    /* Unable to commit Invoke context in Table */

    return (NULL);
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
 *
 *  Revision History:
 *
 * -------------------------------------------------------------------------
 *  Name       Date         Reference              Description 
 * -------------------------------------------------------------------------
 * mkrishna  06-04-2005   ACC651-SDS-TCEN-V1.0.02  Update to search in 
 *                        ID :: D0040              CptList 
 *
 ****************************************************************************/
TCAP_INVOKE_ENTRY *
TCAP_FindInvokeContextWithTimer_CCITT(ITS_CTXT did,
                                      ITS_OCTET invokeId, 
                                      ITS_SERIAL timer)
{
    TCAP_TRANS_ENTRY* tx = NULL;
    TCAP_CPT_LIST *CptLst = NULL;
    ITS_UINT j;

    if ((tx = LocalTxTable[did]) != NULL)
    {
        CptLst = &tx->cptList;
        while (CptLst != NULL)
        {
            for (j = 0; j < TCAP_CTX_MAX_CPT_ENTRIES; j++)
            {
                if (CptLst->cptEntry[j].invoke_id == invokeId &&
                    CptLst->cptEntry[j].timer == timer)
                {
                    return &CptLst->cptEntry[j];
                }
            }
            CptLst = CptLst->next;
        } 

        TCAP_DEBUG(("TCAP_FindInvokeContextWithTimer: CPT Ctxt Not Found, "
                    "did %d, IvkId %d Timer %d.\n", 
                     did, invokeId, timer));
    }
    else
    {
        TCAP_DEBUG(("TCAP_FindInvokeContextWithTimer: LocalTx Entry Not "
                    "Found for did %d, \n", did));
    }

    return NULL;
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
int
TCAP_AllocInvokeContext_CCITT(ITS_CTXT did, TCAP_CPT *cpt, 
                              TCAP_INVOKE_ENTRY *invoke,
                              int dir)
{
    TCAP_TRANS_ENTRY* tx = NULL;
    CPT_INV_ID *tmpInvId = &(cpt->u.invoke.invoke_id); 
    ITS_OCTET inv = 0;
   
    if (tmpInvId->data[1] == 2)
    {
        inv = tmpInvId->data[3];
    }
    else
    {
        inv = tmpInvId->data[2];
    }

    invoke->invoke_id = inv;
    invoke->did = did;
    invoke->dir = dir;
    invoke->inUse = ITS_TRUE;

    tx = TCAP_FindLocalTx_CCITT(did);
    if (tx == NULL)
    {
        TCAP_ERROR(("TCAP_AllocInvokeContext: LocalTx Entry Not "
                    "Found for did %d, \n", did));

        /* Unable to Commit Invoke Context to Table. */

        return !ITS_SUCCESS;
    }

    invoke->ltid = tx->ltid;

    /* start the timer */
    if (cpt->u.invoke.timeout != 0)
    {
         if ((invoke->timer = TIMERS_StartSharedTimer(ITS_TCAP_SRC,
                                                   cpt->u.invoke.timeout,
                                                   invoke,
                                                   sizeof(TCAP_INVOKE_ENTRY)))
              == 0)
         {
             TCAP_ERROR(("Failed to start Timer, did %d, InvkId %d.\n", 
                          did, inv));

             /* Failed to start the shared timer */

             return ITS_ETIMERSTARTFAIL;
         }

         TCAP_DEBUG(("Started Shared Timer %d for did %d, InvkId %d\n",
                      invoke->timer, did, inv));
 
         /* Storing the timeout value if user wants to reset it. */
         invoke->timeout = cpt->u.invoke.timeout;
    }

    return ITS_SUCCESS;
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
void
TCAP_FreeInvokeContext_CCITT(TCAP_INVOKE_ENTRY *invoke)
{
    if (invoke == NULL)
    {
        TCAP_ERROR(("TCAP_FreeInvokeContext: Invoke not found!!!!"));

        /* Invalid Arguments passed */

        return;
    }

    invoke->inUse = ITS_FALSE;

    TCAP_DEBUG(("TCAP_FreeInvokeContext: Freeing invoke Context for invoke "
                "did %d, invoke_id = %d\n",invoke->did, invoke->invoke_id));

    /* take care of the timer */
    if (invoke->timer)
    {
        TIMERS_CancelSharedTimer(invoke->timer);
        invoke->timer = TIMER_BAD_SERIAL;
    }
}
