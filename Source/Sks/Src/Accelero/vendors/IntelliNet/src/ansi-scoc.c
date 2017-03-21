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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:31  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:06  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/06 13:35:36  mmanikandan
 * LOG: PR6.5.1 Validation Bug Fix. (1804, 1798, 1781, 1784, 1749, 1801,
 * LOG: 1802, 1803).
 * LOG:
 * LOG: Revision 9.2  2005/04/06 11:26:22  mmanikandan
 * LOG: Bug Propagation and Validation bug Fix.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:53:35  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.2.9.2.5.8.4  2005/02/21 09:00:30  csireesh
 * LOG: OAM Validation Bug Fix
 * LOG:
 * LOG: Revision 7.2.2.9.2.5.8.3  2005/01/25 07:26:30  csireesh
 * LOG: Fixed Bug 1445 and removed Tab spaces
 * LOG:
 * LOG: Revision 7.2.2.9.2.5.8.2  2005/01/05 10:00:09  csireesh
 * LOG: Removed unwanted alarms
 * LOG:
 * LOG: Revision 7.2.2.9.2.5.8.1  2004/12/29 13:39:34  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.2.2.9.2.5  2004/09/02 11:55:54  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.2.2.9.2.4  2004/08/05 13:16:40  csireesh
 * LOG: Repeat Release and Interval timers are implemented.
 * LOG:
 * LOG: Revision 7.2.2.9.2.3  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.2.2.9.2.2  2004/02/17 12:58:50  mmanikandan
 * LOG: RepeatRelease and Interval timers are added.
 * LOG:
 * LOG: Revision 7.2.2.9.2.1  2004/01/27 05:45:21  yranade
 * LOG: Porting SCCP-CO Message Based Redundancy Changes from Kineto Branch.
 * LOG:
 * LOG: Revision 7.2.2.9  2003/12/12 09:32:41  aganguly
 * LOG: Change in log.
 * LOG:
 * LOG: Revision 7.2.2.7  2003/10/17 19:36:27  hcho
 * LOG: Handled SCOC routing failure to the user.
 * LOG:
 * LOG: Revision 7.2.2.6  2003/09/18 11:13:42  aganguly
 * LOG: fix for SCCP-CO bugs
 * LOG:
 * LOG: Revision 7.2.2.5  2003/09/05 20:08:51  randresol
 * LOG: Fix CgPA routing problem for SCCP Connection Oriented Messages.
 * LOG:
 * LOG: Revision 7.2.2.4  2003/05/05 07:26:26  aganguly
 * LOG: Modification is done for the sequence check in DT2 message.Also while sending ITcredit value is populated from the connection context.
 * LOG:
 * LOG: Revision 7.2.2.3  2003/04/01 06:11:49  aganguly
 * LOG: Removed warnings which was coming with gcc compiler
 * LOG:
 * LOG: Revision 7.2.2.2  2003/03/27 06:32:02  aganguly
 * LOG: Changes made for SCCP-CO new bugs.
 * LOG:
 * LOG: Revision 7.2.2.1  2003/03/17 14:02:29  aganguly
 * LOG: SCCP CO bug fixes
 * LOG:
 * LOG: Revision 7.2  2003/01/16 16:23:33  mmiers
 * LOG: Tandem port, large context changes.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.13  2002/07/29 18:06:27  ngoel
 * LOG: correct peg type
 * LOG:
 * LOG: Revision 6.12  2002/06/04 15:24:43  ngoel
 * LOG: use correct slr value in RLSD, RLC messages during chaining
 * LOG:
 * LOG: Revision 6.11  2002/05/30 15:14:39  ngoel
 * LOG: correct assocRef for chaining
 * LOG:
 * LOG: Revision 6.10  2002/05/20 21:11:50  mmiers
 * LOG: Flip PCs.  Add OAM implementation.  Try chaining fix.
 * LOG:
 * LOG: Revision 6.9  2002/05/17 20:45:56  mmiers
 * LOG: Typo
 * LOG:
 * LOG: Revision 6.8  2002/05/17 18:28:32  mmiers
 * LOG: Wrong commit.
 * LOG:
 * LOG: Revision 6.7  2002/05/17 17:51:04  mmiers
 * LOG: Cut/paste bug.
 * LOG:
 * LOG: Revision 6.6  2002/04/17 23:02:25  hdivoux
 * LOG: FT/HA integration.
 * LOG:
 * LOG: Revision 6.5  2002/04/01 23:04:49  mmiers
 * LOG: Set the MPC correctly for the canned messages.  The Down
 * LOG: routines need verification code added for MPC.
 * LOG:
 * LOG: Revision 6.4  2002/03/27 17:48:12  mmiers
 * LOG: Convert to using shared timers.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
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
 * LOG: Revision 5.3  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:22  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:28  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/01/26 03:05:46  mmiers
 * LOG:
 * LOG:
 * LOG: Commit some more changes to get us on an OO footing.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:25  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.3  1999/08/26 23:44:55  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.2  1999/03/17 21:37:48  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol framework complete.  Now for implementation.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:43  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.33  1998/11/19 01:31:54  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.32  1998/11/13 17:05:43  mmiers
 * LOG: Fix bad timer message.
 * LOG:
 * LOG: Revision 1.31  1998/11/13 02:49:54  mmiers
 * LOG: Do SST.
 * LOG:
 * LOG: Revision 1.30  1998/11/12 02:48:32  mmiers
 * LOG: Clean up some connection oriented bugs.
 * LOG:
 * LOG: Revision 1.29  1998/11/11 00:45:32  mmiers
 * LOG: Work on CPC/CSSN information.
 * LOG:
 * LOG: Revision 1.28  1998/11/10 16:10:13  mmiers
 * LOG: More work on SCMG.
 * LOG:
 * LOG: Revision 1.27  1998/11/10 02:23:02  mmiers
 * LOG: Fix IT timers, rework stack-sent messages, add guard timer, add
 * LOG: behavior control.
 * LOG:
 * LOG: Revision 1.26  1998/11/10 00:40:58  mmiers
 * LOG: Enable IT release.
 * LOG:
 * LOG: Revision 1.25  1998/11/09 23:30:24  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.24  1998/11/04 02:45:19  mmiers
 * LOG: Enable connection timers, elucidate on pause/resume AFA how to do it.
 * LOG:
 * LOG: Revision 1.23  1998/10/30 21:31:34  whu
 * LOG: Disable connection timers, add mutex around reference allocation.
 * LOG:
 * LOG: Revision 1.22  1998/10/30 00:34:49  whu
 * LOG: Adjust timer handling in scoc.c
 * LOG:
 * LOG: Revision 1.21  1998/10/29 15:32:48  whu
 * LOG: Add DEBUG for timeouts.
 * LOG:
 * LOG: Revision 1.20  1998/10/28 00:40:23  mmiers
 * LOG: SendRLC, not SendCREF, if release times out.
 * LOG:
 * LOG: Revision 1.19  1998/10/20 16:22:28  mmiers
 * LOG: Fix compilation warnings.
 * LOG:
 * LOG: Revision 1.18  1998/10/20 01:40:24  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.17  1998/10/19 23:53:25  mmiers
 * LOG: Start adding in error cases.
 * LOG:
 * LOG: Revision 1.16  1998/10/19 23:45:44  mmiers
 * LOG: More bullet-proofing of SCCP.
 * LOG:
 * LOG: Revision 1.15  1998/10/19 00:40:38  mmiers
 * LOG: Strengthen for PCLASS_3
 * LOG:
 * LOG: Revision 1.14  1998/10/16 20:45:23  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.13  1998/10/16 01:44:47  mmiers
 * LOG: Put my current thoughts into bytes.  This stuff is f*cking confusing,
 * LOG: and needs review.
 * LOG:
 * LOG: Revision 1.12  1998/10/15 14:35:51  mmiers
 * LOG: WIN32 compilation changes.
 * LOG:
 * LOG: Revision 1.11  1998/10/15 03:39:30  mmiers
 * LOG: Get the names right (source), make sure GTT is present (Makefile).
 * LOG:
 * LOG: Revision 1.10  1998/10/15 01:45:04  mmiers
 * LOG: Add -D_REENTRANT for alpha.  Add connRef to SCCP_CONN_CTXT.
 * LOG:
 * LOG: Revision 1.9  1998/10/15 01:19:18  mmiers
 * LOG: Remove assert().  We shouldn't terminate, we should gracefully work
 * LOG: around errors.
 * LOG:
 * LOG: More work on SCCP COC.  Added connection timer, release timer,
 * LOG: reset timer.  Check for proper handling of missing information.
 * LOG:
 * LOG: Revision 1.8  1998/09/28 17:37:53  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.7  1998/09/28 00:41:25  mmiers
 * LOG: More work on connection-oriented.
 * LOG:
 * LOG: Revision 1.6  1998/09/28 00:11:24  mmiers
 * LOG: Work on connection oriented.
 * LOG:
 * LOG: Revision 1.5  1998/09/27 00:17:56  mmiers
 * LOG: More work on SCCP
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:31  mmiers
 * LOG: Continue work on improved SCCP.
 * LOG:
 * LOG: Revision 1.3  1998/09/24 19:24:39  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.2  1998/09/24 17:31:52  mmiers
 * LOG: More working with SCCP.
 * LOG:
 * LOG: Revision 1.1  1998/09/24 16:33:13  mmiers
 * LOG: Rearrange vendor lib a little for smarter SCCP.
 * LOG:
 * LOG:
 *
 ****************************************************************************/

#include <string.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_dsm.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <its_timers.h>
#include <its_redundancy.h>

#ident "$Id: ansi-scoc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/sccp.h>

#include "sccp_intern.h"

int sendConnectionRefuse(MTP3_HEADER* mtp3, ITS_USHORT conref, SCCP_ADDR *cgp);
ITS_USHORT SCCP_UserPartOwner(ITS_OCTET up);
ITS_OCTET CO_slc=0;
/*For LOCAL PATCH*/
#define DSM_LockTable        DSM_LockTableLocal
#define DSM_UnlockTable      DSM_UnlockTableLocal
#define DSM_AllocNoLock      DSM_AllocNoLockLocal
#define DSM_FindNoLock       DSM_FindNoLockLocal
#define DSM_FreeNoLock       DSM_FreeNoLockLocal
#define DSM_CommitNoLock     DSM_CommitNoLockLocal
#define DSM_Alloc            DSM_AllocLocal
#define DSM_Find             DSM_FindLocal
#define DSM_Free             DSM_FreeLocal
#define DSM_Commit           DSM_CommitLocal


/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#define TIMERS_StartSharedTimer  TIMERS_StartTimer
#define TIMERS_StartSharedUTimer TIMERS_StartUTimer
#define TIMERS_CancelSharedTimer TIMERS_CancelTimer
/*Patch:Itika:2-Nov-10:End*/
/*
 * extern
 */
extern int INTELLINET_GetSCCPNextRef_ANSI(ITS_SS7_HANDLE handle,
                                               ITS_CTXT *cref);

/*
 * disable this if connection timers are causing problems
 */
#define CONNECTION_TIMERS

static int
SCCP_SendToAPP(MTP3_HEADER * mtp3, ITS_HDR* hdr, ITS_OCTET type,
               ITS_EVENT* ev, ITS_OCTET ssn)
{
    ITS_USHORT dest;
    SCCP_CONN_CTXT *foundCtxt = NULL;
    ITS_INT error;
    int ret;
    SCCP_MSG_DESC* desc = NULL;
    ITS_SCCP_IE ies[32]; 
    int ieCount;
    ITS_EVENT* tempev = NULL;

    SCCP_DEBUG(("SendToAPP: hdr->context: %02x\n",
                hdr->context.conref));

    switch (type)
    {
        case SCCP_MSG_UDT:
        case SCCP_MSG_XUDT:
        case SCCP_MSG_UDTS:
        case SCCP_MSG_XUDTS:
        case SCCP_MSG_LUDT:
        case SCCP_MSG_LUDTS:
            SCCP_ERROR(("SendToAPP: send connectionless from CO procedure\n"));

            return (ITS_EINVALIDARGS);

        case SCCP_MSG_CR:
            desc = &SCCP_CR_Desc;
            break;
 
        case SCCP_MSG_CC:
            desc = &SCCP_CC_Desc; 
            break;

        case SCCP_MSG_CREF:
            desc = &SCCP_CREF_Desc; 
            break;

        case SCCP_MSG_DT1:
             desc = &SCCP_DT1_Desc;
             break;

        default:
            SCCP_DEBUG(("SendToAPP: send connection-oriented message\n"));

    }
    SCCP_DEBUG(("SendToAPP: send connection initiator\n"));
    tempev = malloc(sizeof(ITS_EVENT));

    memcpy(tempev, ev, sizeof(ITS_EVENT));

 if(type != SCCP_MSG_RLSD)
 {
    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)              
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("SCCP_SendToAPP: Couldn't acquire DSM Row"
                               " mutex.\n")); 
                               
                break;
            case (ITS_EINUSE):
                SCCP_CRITICAL(("SCCP_SendToAPP: DSM Row Locked.\n"));

                break;
            case (ITS_ENOTFOUND):
                SCCP_CRITICAL(("SCCP_SendToAPP: Can't find ConnectionReference"
                               " in DSM table.\n"));

                break;
        }
        if (tempev != NULL)
        {
           free(tempev);
           tempev = NULL;
        }
        return (ITS_ENOCONN);
    }

    if (foundCtxt)
    {
         ssn = foundCtxt->lssn;
    }
/*commit due to Locking problem*/
    error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                            sizeof(hdr->context.conref), foundCtxt);
/*end*/
}
    dest = SCCP_UserPartOwner(ssn);

    if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
    {
        dest = ROUTE_SelectApplication(hdr, ev, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        { 
            SCCP_WARNING(("SendToAPP: no route to dest.\n"));

            if (tempev != NULL)
            {
                free(tempev);

                tempev = NULL;
           }

           ret = ITS_ENOTRANSPORT;
           return ITS_SUCCESS;
        }
    }

    ret = TRANSPORT_PutEvent(dest, ev);

   // SCCP_DEBUG(("SendToAPP: PutEvent returned %d\n", ret));

    if (ret != ITS_SUCCESS)
    {
        if ((ret = SCCP_Decode(ies, &ieCount, tempev, desc)) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SendToAPP:  Couldn't decode SCCP Message" ));
            
            if (tempev != NULL)
            {
                free(tempev);

                tempev = NULL;
            }

            return (ret);
        }
        if (tempev != NULL)
        {
            free(tempev);

            tempev = NULL;
        }

        return SCOCHandleRoutingFailure_ANSI(mtp3,type,ies, ieCount,
                                                  SCCP_REF_DEST_UKNOWN);
    }
    else
    {
        if (tempev != NULL)
        {
            free(tempev);

            tempev = NULL;
        }
        return ret;
    }
}

static void
SendCREF(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
         ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ITS_OCTET sio;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;

        sio = MTP3_HDR_GET_SIO(ctxt->inLabel);
        sio &= ~MTP3_MPC_MASK;
        sio |= MTP3_MPC_PRI_1;
        MTP3_HDR_SET_SIO(ies[ieCount].param_data.routingLabel, sio);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_REFUSAL_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_REF_CAUSE);
    ies[ieCount].param_data.refusalCause.cause = cause;
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[ieCount].param_length = sizeof(SCCP_ADDR);
    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }
    ieCount++;

    if (toApp)
    {

        SCOCHandleSCRCMsg_ANSI(&ies[0].param_data.routingLabel,
                               SCCP_MSG_CREF, ies, ieCount,
                               0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_ANSI_SRC;
        if (SCCP_Encode_ANSI(ies, ieCount, SCCP_MSG_CREF, &ev, &hdr,
                             &SCCP_CREF_Desc_ANSI) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_ANSI(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendRLSD(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
         ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0,i = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ITS_OCTET sio;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;

        sio = MTP3_HDR_GET_SIO(ctxt->inLabel);
        sio &= ~MTP3_MPC_MASK;
        sio |= MTP3_MPC_PRI_2;
        MTP3_HDR_SET_SIO(ies[ieCount].param_data.routingLabel, sio);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->dlref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->slref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_RELEASE_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_REL_CAUSE);
    ies[ieCount].param_data.releaseCause.cause = cause;
    ieCount++;

 /*one Optional addtion due to extra byte problem*/
    ies[ieCount].param_id = SCCP_PRM_DATA;
    ies[ieCount].param_length = 10 *sizeof(ITS_OCTET);
    for(i=0;i<  ies[ieCount].param_length ;i++)
     {
        ies[ieCount].param_data.userData.data[i]=i; /*garbage*/
     }
    ieCount++;
    

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_ANSI(&ies[0].param_data.routingLabel,
                               SCCP_MSG_RLSD, ies, ieCount,
                               0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_ANSI_SRC;
        if (SCCP_Encode_ANSI(ies, ieCount, SCCP_MSG_RLSD, &ev, &hdr,
                             &SCCP_RLSD_Desc_ANSI) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_ANSI(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendRLC(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
        ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ITS_OCTET sio;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;

        sio = MTP3_HDR_GET_SIO(ctxt->inLabel);
        sio &= ~MTP3_MPC_MASK;
        sio |= MTP3_MPC_PRI_2;
        MTP3_HDR_SET_SIO(ies[ieCount].param_data.routingLabel, sio);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->dlref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                       ctxt->slref);
    }
    ieCount++;

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_ANSI(&ies[0].param_data.routingLabel,
                               SCCP_MSG_RLC, ies, ieCount,
                               0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_ANSI_SRC;
        if (SCCP_Encode_ANSI(ies, ieCount, SCCP_MSG_RLC, &ev, &hdr,
                             &SCCP_RLC_Desc_ANSI) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_ANSI(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendERR(SCCP_CONN_CTXT* ctxt, ITS_OCTET cause,
        ITS_BOOLEAN toApp)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    if (toApp)
    {
        MTP3_POINT_CODE tmp, tmp2;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;
        MTP3_RL_GET_OPC(ctxt->outLabel.label, tmp);
        MTP3_RL_GET_DPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_OPC(ctxt->outLabel.label, tmp2);
        MTP3_RL_SET_DPC(ctxt->outLabel.label, tmp);
    }
    else
    {
        ITS_OCTET sio;

        ies[ieCount].param_data.routingLabel = ctxt->inLabel;

        sio = MTP3_HDR_GET_SIO(ctxt->inLabel);
        sio &= ~MTP3_MPC_MASK;
        sio |= MTP3_MPC_PRI_1;
        MTP3_HDR_SET_SIO(ies[ieCount].param_data.routingLabel, sio);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    if (toApp)
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->slref);
    }
    else
    {
        RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                       ctxt->dlref);
    }
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_ERROR_CAUSE;
    ies[ieCount].param_length = sizeof(SCCP_ERR_CAUSE);
    ies[ieCount].param_data.errorCause.cause = cause;
    ieCount++;

    if (toApp)
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->oaddr;
    }
    else
    {
        ies[ieCount].param_data.calledPartyAddr =
            ctxt->daddr;
    }

    if (toApp)
    {
        SCOCHandleSCRCMsg_ANSI(&ies[0].param_data.routingLabel,
                               SCCP_MSG_ERR, ies, ieCount,
                               0, SCCP_SSN_NONE, ITS_FALSE);
    }
    else
    {
        ITS_EVENT ev;
        ITS_HDR hdr;

        hdr.type = ITS_SCCP;
        hdr.context.conref = ctxt->connRef;

        ev.src = ITS_SCCP_ANSI_SRC;
        if (SCCP_Encode_ANSI(ies, ieCount, SCCP_MSG_ERR, &ev, &hdr,
                             &SCCP_ERR_Desc_ANSI) == ITS_SUCCESS)
        {
            SCOCHandleAPPMsg_ANSI(&ev);
        }

        ITS_EVENT_TERM(&ev);
    }
}

static void
SendIT(SCCP_CONN_CTXT* ctxt)
{
    ITS_SCCP_IE ies[32];
    int ieCount = 0;
    ITS_EVENT ev;
    ITS_HDR hdr;
    ITS_OCTET sio;

    sio = MTP3_HDR_GET_SIO(ctxt->outLabel);
    sio &= ~MTP3_MPC_MASK;
    sio |= MTP3_MPC_PRI_1;

    ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[ieCount].param_length = sizeof(MTP3_HEADER);
    ies[ieCount].param_data.routingLabel = ctxt->outLabel;
    MTP3_HDR_SET_SIO(ies[ieCount].param_data.routingLabel, sio);
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_DEST_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(ies[ieCount].param_data.destinationLocalReference,
                   ctxt->dlref);
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(ies[ieCount].param_data.sourceLocalReference,
                   ctxt->slref);
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_PROTOCOL_CLASS;
    ies[ieCount].param_length = sizeof(SCCP_PROT_CLASS);
    ies[ieCount].param_data.protocolClass.pclass = ctxt->pclass;
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_SEQUENCE_SEGMENT;
    ies[ieCount].param_length = sizeof(SCCP_SEQ_SEG);
    memset(&ies[ieCount].param_data.sequenceSegment, 0,
           sizeof(SCCP_SEQ_SEG));
    ieCount++;

    ies[ieCount].param_id = SCCP_PRM_CREDIT;
    ies[ieCount].param_length = sizeof(SCCP_CREDIT);
    ies[ieCount].param_data.credit.win_size = ctxt->windowSize;

    ieCount++;

    ies[ieCount].param_data.calledPartyAddr = ctxt->daddr;


    hdr.type = ITS_SCCP;
    hdr.context.conref = ctxt->connRef;

    ev.src = ITS_SCCP_ANSI_SRC;
    if (SCCP_Encode_ANSI(ies, ieCount, SCCP_MSG_IT, &ev, &hdr,
                         &SCCP_IT_Desc_ANSI) == ITS_SUCCESS)
    {
        SCOCHandleAPPMsg_ANSI(&ev);
    }

    ITS_EVENT_TERM(&ev);
}


/* sends notification of RLSD message to App */
static int 
NotifyRLSDToApp(ITS_USHORT conref,MTP3_HEADER* mtp3,
           ITS_SCCP_IE* ies,int releasemsgID,ITS_OCTET cause)
{
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    /* Incremented by 2 as ies contains both slr and dlr.Counter releasemsgID
       contains the value of dlr */

    releasemsgID += 2;

    ies[releasemsgID].param_id = SCCP_PRM_RELEASE_CAUSE;
    ies[releasemsgID].param_length = sizeof(SCCP_REL_CAUSE);
    ies[releasemsgID].param_data.errorCause.cause = cause;

    releasemsgID++;

    ies[releasemsgID].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[releasemsgID].param_length = sizeof(MTP3_HEADER);
    ies[releasemsgID].param_data.routingLabel = *mtp3;

    releasemsgID++;

    hdrntfy.type = ITS_SCCP;
    event.src = ITS_SCCP_SRC;
    hdrntfy.context.conref =conref ;
    
    SCCP_DEBUG(("NotifyRLSDToApp: Ntfy for RLSD is send to App\n"));

    if (SCCP_Encode(ies, releasemsgID, SCCP_MSG_RLSD, &event, &hdrntfy,
                  &SCCP_RLSD_Desc)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyRLSDToApp: Error in encoding RLSD message\n"));

        return (ITS_ENOMSG);
    }

    ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

    /* send to the application */

    if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_RLSD, &event, 0)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyRLSDToApp:Error while sending to Application."));
        return (ITS_ENOMSG);
    }
    
    return(ITS_SUCCESS);
}
/* sends notification of ERR to Application */

static int 
NotifyERRToApp(ITS_USHORT conref,MTP3_HEADER* mtp3,
           ITS_SCCP_IE* ies,int errormsgID,ITS_OCTET cause)
{
    ITS_EVENT event;
    ITS_HDR hdrntfy;

    errormsgID++;

    ies[errormsgID].param_id = SCCP_PRM_ERROR_CAUSE;
    ies[errormsgID].param_length = sizeof(SCCP_ERR_CAUSE);
    ies[errormsgID].param_data.errorCause.cause = cause;

    errormsgID++;

    ies[errormsgID].param_id = SCCP_PRM_ROUTING_LABEL;
    ies[errormsgID].param_length = sizeof(MTP3_HEADER);
    ies[errormsgID].param_data.routingLabel = *mtp3;

    errormsgID++;

    hdrntfy.type = ITS_SCCP;
    event.src = ITS_SCCP_ANSI_SRC;
    hdrntfy.context.conref = conref;
    
    SCCP_DEBUG(("NotifyERRToApp: Ntfy for ERR is send to App and resources\
                 are released\n"));

    if (SCCP_Encode(ies, errormsgID, SCCP_MSG_ERR, &event, &hdrntfy,
                  &SCCP_ERR_Desc)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyERRToApp: Error in encoding ERR message\n"));

        return (ITS_ENOMSG);
    }

    ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

    /* send to the application */

    if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_ERR, &event, 0)!=ITS_SUCCESS)
    {
        SCCP_ERROR(("NotifyERRToApp:Error while sending to Application."));
    }

    SCCP_DEBUG(("NotifyERRToApp:Releasing the resources blocked for the\
                                connection\n"));

    SCCP_DeleteLocalReference_ANSI(conref);
    return(ITS_SUCCESS);
}

/*
 * send a connection request to MTP3
 */
static int
HandleAppCR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    SCCP_CREDIT *cred = NULL;
    ITS_OCTET *gttInfo = NULL;
    ITS_USHORT gttLen = 0;
    ITS_OCTET  addrInd = 0;
    ITS_UINT cgppc;
    ITS_OCTET ssn;
    MTP3_HEADER *rl = NULL;
    int i, error;

    SCCP_DEBUG(("HandleAppCR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLING_PARTY_ADDR:
            clp = &ies[i].param_data.callingPartyAddr;
            break;

        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_PROTOCOL_CLASS:
            pc = &ies[i].param_data.protocolClass;
            break;

        case SCCP_PRM_CREDIT:
            cred = &ies[i].param_data.credit;
            break;

        case SCCP_PRM_ROUTING_LABEL:
            rl = &ies[i].param_data.routingLabel;
            break;
        }
    }

    /* user must have allocated the local reference */
    if (clp == NULL || cdp == NULL || sl == NULL || rl == NULL || pc == NULL)
    {
        SCCP_ERROR(("HandleAppCR: ConnectionRequest is missing CDP, "
                    "LocalRef, PClass, or MTP3 label\n"));

        /* Outgoing Message - Missing Mandatory Parameter */

        if (rl == NULL)
        {
            return (ITS_EMISSMAND);
        }
    }

    if (SCCP_DecodeAddr_ANSI(clp, &addrInd, &cgppc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
    {
         SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

         return (ITS_EINVALIDARGS);
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppCR: ConnectionRequest and context mismatch\n"));

        return (ITS_EINVALIDARGS);
    }

    /* process it */

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppCR: Couldn't acquire DSM Row mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppCR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppCR: Can't find ConnectionReference in DSM table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    foundCtxt->lssn = ssn;
    foundCtxt->rlsdntries = 0;
    if (cdp == NULL)
    {
        /* Create copy to use in SendCREF after release Row Lock */
        copyCtxt = *foundCtxt;

        /* Release Row Lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference"
                        "in order to Release Lock.\n"));
        }
        
        SendCREF(&copyCtxt, SCCP_REF_DEST_UKNOWN, ITS_TRUE);

        SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

        return (ITS_ENOCONN);
    }

    if (sl == NULL || pc == NULL)
    {
        /*Create copy to use in SendCREF after release Row Lock */
        copyCtxt = *foundCtxt;

        /* Release Row Lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference"
                        "in order to Release Lock.\n"));
        }

        SendCREF(&copyCtxt, SCCP_REF_UNQUAL, ITS_TRUE);

        SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

        return (ITS_ENOCONN);
    }

    foundCtxt->outLabel = *rl;
    foundCtxt->daddr = *cdp;

    if (clp)
    {
        foundCtxt->oaddr = *clp;
    }

    foundCtxt->sequenceOn = ITS_FALSE;
 /*Patch:Itika:1-nov-10:Redundancy Merge fix*/ 
    //foundCtxt->sequenceSLS = 0;
    foundCtxt->sequenceSLS = CO_slc;
    SCCP_DEBUG(("HandleAppCR:value of SLS for routing %d",foundCtxt->sequenceSLS))
                                   /*round robin fashion*/
    CO_slc++;
    if (CO_slc==0x0f)/*max link can be 15*/
     {
      CO_slc=0;
     }   
 /*Patch:Itika:1-nov-10:End*/ 

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
    case SCCP_PCLASS_2:
        foundCtxt->windowSize = 0;
        foundCtxt->pclass = SCCP_PCLASS_2;
        foundCtxt->fsn = 0;
        foundCtxt->rsn = 0;
        break;

    case SCCP_PCLASS_3:
        if (cred)
        {
            foundCtxt->windowSize = cred->win_size;
        }
        foundCtxt->pclass = SCCP_PCLASS_3;
        foundCtxt->fsn = 0;
        foundCtxt->rsn = 0;
        break;

    default:
        SCCP_WARNING(("HandleAppCR: Invalid protocol class for connection\n"));

        SCCP_Alarm_ANSI(686, __FILE__, __LINE__, "Pclass %d",
                                     pc->pclass);

        /* Release Row Lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference"
                        "in order to Release Lock.\n"));
        }

        return (ITS_ENOCONN);
    }

    foundCtxt->state = SCCP_CONN_OUT_PEND;
#if defined(CONNECTION_TIMERS)
    foundCtxt->connectTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_conn),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
   SCCP_DEBUG(("HandleAppCR:START connectTimer:SERIAL[%d]\n",foundCtxt->connectTimer));	 
#endif
 
    *mtp3 = *rl;
 /*Patch:Itika:1-nov-10:Redundancy Merge fix*/ 
     MTP3_RL_SET_SLS(mtp3->label,foundCtxt->sequenceSLS);
     SCCP_DEBUG(("HandleAppCR:value of SLS for routing %d",foundCtxt->sequenceSLS))
     SCCP_DEBUG(("HandleAppCR:value of SLS for routing MTP3 %d",MTP3_RL_GET_SLS(mtp3->label)))
 /*Patch:Itika:1-nov-10:End*/ 

    /* Release Row Lock */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCR: DSM unable to Commit Reference"
                    "in order to Release Lock.\n"));
    }

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));
/*Patch:Itika:2-Nov-10:Sccp Enhancement*/
#if 0

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }
#endif
/*Patch:Itika:2-Nov-10:End*/

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_CR, ies, ieCount, cdp);
}

static int
HandleDownCR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount,
             ITS_UINT dpc, ITS_OCTET ssn, ITS_BOOLEAN needCouple)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt = NULL, *foundCtxt2 = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_ADDR *cdp = NULL, *clp = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    SCCP_CREDIT *cred = NULL;
    SCCP_HOP_COUNT* hc = NULL;
    MTP3_POINT_CODE tmp, tmp2;
    ITS_INT slref;
    ITS_HDR chain;
    ITS_OCTET *gttInfo = NULL;
    ITS_USHORT gttLen = 0;
    ITS_OCTET  addrInd = 0;
    ITS_UINT cgppc;
    int i, error;
    ITS_UINT PC=0;

    SCCP_DEBUG(("HandleDownCR\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CR_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_CALLING_PARTY_ADDR:
            clp = &ies[i].param_data.callingPartyAddr;
            break;

        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_PROTOCOL_CLASS:
            pc = &ies[i].param_data.protocolClass;
            break;

        case SCCP_PRM_CREDIT:
            cred = &ies[i].param_data.credit;
            break;

        case SCCP_PRM_HOP_COUNTER:
            hc = &ies[i].param_data.hopCount;
            break;
        }
    }

    /* we allocate the reference */
    if (cdp == NULL || sl == NULL)
    {
        SCCP_ERROR(("HandleDownCR: Missing mandatories\n"));

        /* Incoming Message - Missing Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }

    if (SCCP_DecodeAddr_ANSI(cdp, &addrInd, &cgppc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
    {
         SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

         return (ITS_EINVALIDARGS);
    }


    if (INTELLINET_GetSCCPNextRef_ANSI(NULL,
                                       &hdr->context.conref) != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCR: Out of local ConnectionReference numbers\n"));

        return (ITS_ENOMSG);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownCR: Couldn't acquire DSM Row mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownCR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownCR: Can't find ConnectionReference in DSM table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    slref = RN_GET_REF_NUM(*sl);
    SCCP_ERROR(("Slref %d",slref));
    foundCtxt->slref = hdr->context.conref;
    foundCtxt->dlref = slref;
    foundCtxt->oaddr = *cdp;
    foundCtxt->inLabel = *mtp3;
    foundCtxt->outLabel = *mtp3;
    foundCtxt->lssn = ssn;
    foundCtxt->rlsdntries = 0; 
    MTP3_RL_GET_OPC(foundCtxt->outLabel.label, tmp);
    MTP3_RL_GET_DPC(foundCtxt->outLabel.label, tmp2);
    MTP3_RL_SET_OPC(foundCtxt->outLabel.label, tmp2);
    MTP3_RL_SET_DPC(foundCtxt->outLabel.label, tmp);

    if (clp)
    {
        foundCtxt->daddr = *clp;
    }
    else
    {
        /*   fix: daddr is mandatory for our stack to do routing
         **  based on PC&SSN.
         */

    //    ITS_OCTET addrInd = SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;

         PC=MTP3_RL_GET_OPC_VALUE(mtp3->label);
         //printf("\nTest_Trace:PC=%d\n",PC);


        if ((mtp3->sio) & SCCP_CPA_ROUTE_NAT)
         {
            addrInd =SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_NAT|SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;
          //  printf("\nTest_Trace:AddrIn=%d\n",addrInd);

         }
        else if((mtp3->sio) & SCCP_CPA_ROUTE_INT)
         {
           addrInd =SCCP_CPA_HAS_PC|SCCP_CPA_ROUTE_INT|SCCP_CPA_HAS_SSN|SCCP_CPA_ROUTE_SSN;
          // printf("\nTest_Trace:AddrIn=%d\n",addrInd);
         }


        SCCP_EncodeAddr_ANSI(&foundCtxt->daddr, addrInd, PC, ITS_SS7_DEFAULT_SSN,NULL, 0);

   } 

    foundCtxt->sequenceOn = ITS_FALSE;
  //  foundCtxt->sequenceSLS = 0;
    foundCtxt->sequenceSLS = CO_slc;
   SCCP_DEBUG(("HandleDownCR:value of SLS for routing %d",foundCtxt->sequenceSLS));
                                   /*round robin fashion*/
    CO_slc++;
    if (CO_slc==0x0f)/*max link can be 15*/
     {
      CO_slc=0;
     }   

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
    case SCCP_PCLASS_2:
        foundCtxt->windowSize = 0;
        foundCtxt->pclass = SCCP_PCLASS_2;
        foundCtxt->fsn = 0;
        foundCtxt->rsn = 0;
        break;

    case SCCP_PCLASS_3:
        foundCtxt->windowSize = 0;
        foundCtxt->pclass = SCCP_PCLASS_3;
        if (cred)
        {
            foundCtxt->windowSize = cred->win_size;
        }
        foundCtxt->fsn = 0;
        foundCtxt->rsn = 0;
        break;

    default:
        SCCP_WARNING(("HandleDownCR: Invalid protocol class for connection\n"));

        SCCP_Alarm_ANSI(685, __FILE__, __LINE__, " %d",
                                     pc->pclass);

        /* Release Row Lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference"
                        "in order to Release Lock.\n"));
        }

        return (ITS_ENOCONN);
    }

    foundCtxt->state = SCCP_CONN_IN_PEND;
#if defined(CONNECTION_TIMERS)
    foundCtxt->connectTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_conn),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
   SCCP_DEBUG(("HandleDownCR:START connectTimer:SERIAL[%d]\n",foundCtxt->connectTimer));	 
#endif
 
    if (hc && pc && pc->pclass == SCCP_PCLASS_3)
    {
        hc->count--;
        /***   equal-to    or    less-than  **/
        if (hc->count == 0 || hc->count == 255)
        {
            SCCP_ERROR(("HandleDownCR: Hop count exceeded\n"));
            /* Incoming Message - Hop Count Exceeded. */
            PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);

            /* Make a copy of ctxt to use in SendCREF after release row lock. */
            copyCtxt = *foundCtxt;

            /* Release Row Lock */
            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ANSI_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);
            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference"
                            "in order to Release Lock.\n"));
            }

            SendCREF(&copyCtxt, SCCP_REF_SCCP_ORG, ITS_FALSE);

            return (ITS_EMISSMAND);
        }
    }

    if (needCouple)
    {
        ITS_OCTET addrInd = 0;

        foundCtxt->isIntermediate = ITS_TRUE;

        if (((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_INTERNATIONAL) || ((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_SPARE))
        {
            addrInd |= SCCP_CPA_ROUTE_INT;
        }
        else if (((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL) || ((mtp3->sio & MTP3_NIC_MASK) == MTP3_NIC_RESERVED))
        {
            addrInd |= SCCP_CPA_ROUTE_NAT;
        }

        addrInd |= SCCP_CPA_ROUTE_SSN|SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN;
        SCCP_EncodeAddr_ANSI(&foundCtxt->oaddr, addrInd,
                             MTP3_RL_GET_DPC_VALUE(mtp3->label), ssn, NULL, 0);

        if (INTELLINET_GetSCCPNextRef_ANSI(NULL,
                                           &chain.context.conref) != ITS_SUCCESS)
        {
            SCCP_WARNING(("HandleDownCR: Can't allocation coupled connection reference\n"));

            /* Make a copy of ctxt to use in SendCREF after release row lock. */
            copyCtxt = *foundCtxt;

            /* Release Row Lock & save Changes */
            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ANSI_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);
            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference"
                            "in order to Release Lock.\n"));
            }

            SendCREF(&copyCtxt, ITS_FALSE, SCCP_REF_NOT_OBTAINABLE);

            return (ITS_ENOCONN);
        }

        chain.type = ITS_SCCP;
        RN_SET_REF_NUM(*sl, chain.context.conref);

        foundCtxt->assocRef = chain.context.conref;

        if (clp)
        {
            *clp = foundCtxt->oaddr;
        }

        MTP3_RL_GET_DPC(mtp3->label, tmp);
        MTP3_RL_SET_OPC(mtp3->label, tmp);
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc);

        copyCtxt = *foundCtxt;    /* Make copy for use after release Row lock */

        /* Release Row Lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference"
                        "in order to Release Lock.\n"));
        }

        foundCtxt = NULL;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&chain.context.conref, 
                                                sizeof(chain.context.conref), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownCR: Couldn't acquire DSM Row mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownCR: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownCR: Can't find ConnectionReference in DSM table.\n"));
                break;
            }


            SCCP_DeleteLocalReference_ANSI(chain.context.conref);

            SendCREF(&copyCtxt, ITS_FALSE, SCCP_REF_NOT_OBTAINABLE);

            return (ITS_ENOCONN);
        }

        foundCtxt2->isIntermediate = ITS_TRUE;
        foundCtxt2->assocRef = hdr->context.conref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = *mtp3;
        ieCount++;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT, 
                          (ITS_OCTET *)&chain.context.conref,
                       sizeof(chain.context.conref), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in order to Release Lock.\n"));
        }
    }
    else
    {
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCR: DSM unable to Commit Reference in order to Release Lock.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }

    if (needCouple)
    {
        return HandleAppCR(&chain, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send a connection confirm
 */
static int
HandleAppCC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_ADDR *cdp = NULL, local;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    int i, error;
    int isCREFtobesent = 0;
    ITS_EVENT event;
    ITS_HDR hdrntfy;
    int crefid = 0;
    ITS_OCTET creditvalue = 0;

    SCCP_DEBUG(("HandleAppCC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
                crefid = i;
            break;

        case SCCP_PRM_PROTOCOL_CLASS:
            pc = &ies[i].param_data.protocolClass;
            break;

        case SCCP_PRM_CREDIT:
            creditvalue = ies[i].param_data.credit.win_size;  
            if (!(0x0F & creditvalue))
            {
                SCCP_ERROR(("HandleAppCC: CC with credit value zero \n"));
                isCREFtobesent = 1;
            }
            break;

        }
    }

    /* we allocated the local reference */
    if (sl == NULL || dl == NULL || pc == NULL)
    {
        SCCP_ERROR(("HandleAppCC: Missing source, destination reference number "
                    "or PClass\n"));

        return (ITS_EMISSMAND);
    }
    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppCC: ConnectionConfirm and context mismatch\n"));

        return (ITS_EINVALIDARGS);
    }

    /* process it */
    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppCC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppCC: Can't find ConnectionReference in table.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppCC: DSM Row Locked.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
    if (isCREFtobesent == 1)
    {
        SCCP_DEBUG(("HandleAppCC:CREF is sent to the other end\n"));

        SendCREF(foundCtxt,SCCP_REF_BAD_USER_DATA,ITS_FALSE);

        /* Send NTFY to app for CREF */
        RN_SET_REF_NUM(ies[crefid].param_data.destinationLocalReference,
                       foundCtxt->slref);
        crefid++;
                       
        ies[crefid].param_id = SCCP_PRM_REFUSAL_CAUSE;
        ies[crefid].param_length = sizeof(SCCP_REF_CAUSE);
        ies[crefid].param_data.refusalCause.cause = SCCP_REF_BAD_USER_DATA;

        crefid++;
    
        ies[crefid].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[crefid].param_length = sizeof(MTP3_HEADER);
        ies[crefid].param_data.routingLabel = *mtp3;

        crefid++;

        ieCount = crefid;

        hdrntfy.type = ITS_SCCP;
        event.src = ITS_SCCP_SRC;
        hdrntfy.context.conref = foundCtxt->connRef;

        SCCP_DEBUG(("HandleAppCC:Ntfy for CREF is send to App\n"));

        if (SCCP_Encode(ies, ieCount, SCCP_MSG_CREF, &event, &hdrntfy,
                              &SCCP_CREF_Desc)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCC:Error in encoding ERR message\n"));
            return (ITS_ENOMSG);
        }
        ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

        /* send to the application */
        if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_CREF, &event, 0)
                                                               !=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppCC:Error while sending to Application."));
        }
        foundCtxt = NULL;

        return(ITS_ESENDFAIL);
    }

    foundCtxt->state = SCCP_DATA_TRANSFER;
    foundCtxt->dataState = SCCP_DATA_NORMAL;
    *mtp3 = foundCtxt->outLabel;
   SCCP_DEBUG(("HandleAppCC:value of SLS for routing %d",foundCtxt->sequenceSLS));
    MTP3_RL_SET_SLS(mtp3->label,foundCtxt->sequenceSLS);
 //  SCCP_DEBUG(("value of SLS for routing=%d", MTP3_RL_GET_SLS(mtp3->label)));     

    if (cdp == NULL)
    {
        local = foundCtxt->daddr;
        cdp = &local;
    }

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
    case SCCP_PCLASS_2:
        if (foundCtxt->pclass == SCCP_PCLASS_3)
        {
            foundCtxt->windowSize = 0;
            foundCtxt->pclass = SCCP_PCLASS_2;
        }
        break;

    case SCCP_PCLASS_3:
        if (foundCtxt->pclass == SCCP_PCLASS_2)
        {
            SCCP_WARNING(("HandleAppCC:Invalid protocol class for connection\n"));

                /* Outgoing Message - Protocol Class of Message does not 
                   match Connection. */

                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ANSI_SCCP_CTXT,
                                   (ITS_OCTET *)&hdr->context.conref, 
                                   sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleAppCC: DSM unable to free Reference."
                                "\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }


                 return (ITS_ENOCONN);
            }

            if (foundCtxt->windowSize < creditvalue)
            {
                SCCP_DEBUG(("HandleAppCC:Invalid Credit value sent in CC from"
                           " the application, message is discarded\n"));

                return(ITS_EBADCHKSUM);
           }
           break;

        default:
            SCCP_WARNING(("HandleAppCC: Invalid protocol class for connection"
                          "\n"));

            error = DSM_Commit(DSM_SccpFtGroupId,
                               DSM_TABLE_ANSI_SCCP_CTXT,
                               (ITS_OCTET *)&hdr->context.conref, 
                               sizeof(hdr->context.conref), foundCtxt);

            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleAppCC: DSM unable to free Reference.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }


            return (ITS_ENOCONN);
    }

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->connectTimer)
    {
        SCCP_DEBUG(("HandleAppCC: CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
        error = TIMERS_CancelTimer(foundCtxt->connectTimer);
        if(error != ITS_SUCCESS)
        {
          SCCP_ERROR(("HandleAppCC: FAIL To CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
        }
        foundCtxt->connectTimer = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
   SCCP_DEBUG(("HandleAppCC:START sendInactivity Timer:SERIAL[%d]\n",foundCtxt->sendInactivity));	 
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
   SCCP_DEBUG(("HandleAppCC:START receiveInactivity Timer:SERIAL[%d]\n",foundCtxt->receiveInactivity));	 
#endif
 
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCC: DSM unable to free Reference.\n"));
    }

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_CC, ies, ieCount, cdp);
}
/*
 * send released
 */
static int
HandleAppRLSD(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    int releaseID = 0;
    ITS_OCTET cause = 0;
    ITS_HDR hdrntfy;
    ITS_EVENT event;

    SCCP_DEBUG(("HandleAppRLSD\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
            case SCCP_PRM_RELEASE_CAUSE:
                cause =  ies[i].param_data.releaseCause.cause;
                break;
        }
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppRLSD: Released and context mismatch\n"));

        /* Outgoing Message - Local Reference does not match Context*/

        return (ITS_EINVALIDARGS);
    }


    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
  
    
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppRLSD: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppRLSD: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppRLSD: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->state != SCCP_OUT_RELEASE_PEND)
    {
        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleAppRLSD:CANCEL Connect timer is killed: SERIAL [%d]\n",foundCtxt->connectTimer));
            error = TIMERS_CancelTimer(foundCtxt->connectTimer);
            if(error != ITS_SUCCESS)
             {
                SCCP_ERROR(("HandleAppRLSD: FAIL To CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
             }
            foundCtxt->connectTimer = 0;
        }
        if (foundCtxt->releaseTimer)
        {
           // TIMERS_CancelTimer(foundCtxt->receiveInactivity);
           SCCP_DEBUG(("HandleAppRLSD:CANCEL Release timer is killed: SERIAL [%d]\n",foundCtxt->releaseTimer));
           error = TIMERS_CancelTimer(foundCtxt->releaseTimer);
           if(error != ITS_SUCCESS)
           {
              SCCP_ERROR(("HandleAppRLSD: FAIL To CANCEL Release Timer SERIAL [%d]\n",foundCtxt->releaseTimer));
           }
           foundCtxt->releaseTimer = 0;
        }
/*Patch:Itika :For test case SCCP_CO_2.8: Commented as extra releaseTimer is started here*/
/*        foundCtxt->releaseTimer =
            TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));*/
 
        if (foundCtxt->sendInactivity)
        {
            SCCP_DEBUG(("HandleAppRLSD:CANCEL SendInactivity timer is killed:SERIAL [%d]\n",foundCtxt->sendInactivity));
            error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleAppRLSD: FAIL To CANCEL SendInactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
            }
            foundCtxt->sendInactivity = 0;
        }
        if (foundCtxt->receiveInactivity)
        {
            SCCP_DEBUG(("HandleAppRLSD:CANCEL ReceiveInactivity timer is killed:SERIAL [%d]\n",foundCtxt->receiveInactivity));
            error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleAppRLSD: FAIL To CANCEL ReceiveInactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
            }
            foundCtxt->receiveInactivity = 0;
        }
    }
#endif
    /*change for bug 629 (multiple rlsd )*/
  /*  if (foundCtxt->rlsdntries < NumTries)
      foundCtxt->releaseTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppRLSD:Start the Release timer Again\n"));	 
       foundCtxt->rlsdntries++;
     }
   */
   if(foundCtxt->rlsdntries==0)  
    {
      //  if (foundCtxt->releaseTimer)
      //  {
      //     SCCP_DEBUG(("HandleAppRLSD:Release timer is killed\n"));
      //     TIMERS_CancelTimer(foundCtxt->releaseTimer);
      //  }
      SCCP_DEBUG(("HandleAppRLSD:Release Notify to App\n"));
      *mtp3 = foundCtxt->inLabel;

      ieCount++;
      ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
      ies[ieCount].param_length = sizeof(MTP3_HEADER);
      ies[ieCount].param_data.routingLabel = *mtp3;
      ieCount++;

     /*NOT SUPPORT IN ANSI*/
     /* ies[ieCount].param_id = SCCP_PRM_IMPORTANCE;
      ies[ieCount].param_length = sizeof(SCCP_IMPORTANCE);
      ies[ieCount].param_data.importance.importance = 7;
      ieCount++;*/


 /*one Optional addtion due to extra byte problem value 0 -9*/
    ies[ieCount].param_id = SCCP_PRM_DATA;
    ies[ieCount].param_length = 10 *sizeof(ITS_OCTET);
    for(i=0;i<  ies[ieCount].param_length ;i++)
     {
        ies[ieCount].param_data.userData.data[i]=i; /*garbage*/
     }
    ieCount++;


     hdrntfy.type = ITS_SCCP;
     event.src = ITS_SCCP_SRC;
     hdrntfy.context.conref = hdr->context.conref ;

     SCCP_DEBUG(("NotifyRLSDToApp: Ntfy for RLSD is send to App\n"));

    if (SCCP_Encode(ies, ieCount, SCCP_MSG_RLSD, &event, &hdrntfy,
                                                   &SCCP_RLSD_Desc)!=ITS_SUCCESS)
    {
	    error = DSM_Commit(DSM_SccpFtGroupId,
			    DSM_TABLE_ANSI_SCCP_CTXT,
			    (ITS_OCTET *)&hdr->context.conref,
			    sizeof(hdr->context.conref), foundCtxt);

	    if (error != ITS_SUCCESS)
	    {
		    SCCP_ERROR(("HandleAppRLSD: DSM unable to free Reference.\n"));
	    }

	    SCCP_ERROR(("NotifyRLSDToApp: Error in encoding RLSD message\n"));
	    return (ITS_ENOMSG);
    }

    ITS_SET_CTXT(&event.data[1], hdrntfy.context.conref);

    /* send to the application */
    
    if (SCCP_SendToAPP(mtp3, &hdrntfy, SCCP_MSG_RLSD, &event, 0)!=ITS_SUCCESS)
    {
	    error = DSM_Commit(DSM_SccpFtGroupId,
			    DSM_TABLE_ANSI_SCCP_CTXT,
			    (ITS_OCTET *)&hdr->context.conref,
			    sizeof(hdr->context.conref), foundCtxt);

	    if (error != ITS_SUCCESS)
	    {
		    SCCP_ERROR(("HandleAppRLSD: DSM unable to free Reference.\n"));
	    }

	    SCCP_ERROR(("NotifyRLSDToApp:Error while sending to Application."));
	    return (ITS_ENOMSG);
    }
      // SCCP_DeleteLocalReference_ANSI(hdr->context.conref);
   }
   
   if (foundCtxt->rlsdntries < NumTries)
   {

       foundCtxt->releaseTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppRLSD:START the Release timer :SERIAL[%d]\n",foundCtxt->releaseTimer));	 
       foundCtxt->rlsdntries++;
   }
   
     /*
    else
     {
       SCCP_DEBUG(("HandleAppRLSD:Release timer is killed\n"));
       TIMERS_CancelTimer(foundCtxt->releaseTimer);
       SCCP_DeleteLocalReference_ANSI(hdr->context.conref);
     }*/

    foundCtxt->state = SCCP_OUT_RELEASE_PEND;

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRLSD: DSM unable to free Reference.\n"));

    }


    foundCtxt = NULL;

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_RLSD, ies, ieCount, cdp);
}


/*
 * reset request
 */
static int
HandleAppRSR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    
    SCCP_DEBUG(("HandleAppRSR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if ( dl == NULL || sl ==NULL)
    {
         SCCP_ERROR(("HandleAppRSR: Improper reference number\n"));

         /* Incoming Message - Missing Mandatory Parameter." */

         return (ITS_EMISSMAND);
    }


    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppRSR: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppRSR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppRSR: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppRSR: RSR is invalid for protocol class.\n"));

        SCCP_Alarm_ANSI(671, __FILE__, __LINE__, " Pclass %d",
                                     foundCtxt->pclass);

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppRSR: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    foundCtxt->state = SCCP_OUT_RESET_PEND;

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    foundCtxt->resetTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_reset),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppRSR:START resetTimer: SERIAL [%d]\n",foundCtxt->resetTimer));	 
    if (foundCtxt->sendInactivity)
    {
         SCCP_DEBUG(("HandleAppRSR:CANCEL SendInactivity timer is killed: SERIAL [%d]\n",foundCtxt->sendInactivity)); 
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppRSR: FAIL To CANCEL sendInactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppRSR:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
 
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRSR: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_RSR_TO_REMOTE_SENT);


    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_RSR, ies, ieCount, cdp);
}

static int
HandleDownCC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref, slref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR *cdp = NULL;
    SCCP_ADDR *clp = NULL;
    SCCP_PROT_CLASS *pc = NULL;
    ITS_CTXT      tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;
    int isRLSDtobesent = 0;
    ITS_OCTET creditvalue = 0;

    SCCP_DEBUG(("HandleDownCC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_CALLING_PARTY_ADDR:
            clp = &ies[i].param_data.callingPartyAddr;
            break;

        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;

        case SCCP_PRM_PROTOCOL_CLASS:
            pc = &ies[i].param_data.protocolClass;
            break;

        case SCCP_PRM_CREDIT:   
            creditvalue = ies[i].param_data.credit.win_size;
            if (!(0x0F & creditvalue))
            {
                SCCP_ERROR(("HandleAppCC: credit value is zero in CC\n"));
                isRLSDtobesent = 1; 
            }
            break;

        }
    }
    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownCC: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }


    dlref = RN_GET_REF_NUM(*dl); 
/*ASHUTOSH*/
/*
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownCC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownCC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownCC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownCC: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownCC: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownCC:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/

    slref = RN_GET_REF_NUM(*sl);
    if (foundCtxt->state == SCCP_OUT_RELEASE_PEND)
    {
        SCCP_ERROR(("HandleDownCC:CC received in state = %x,dicarded",
                     foundCtxt->state));
        SCCP_Alarm_ANSI(656, __FILE__, __LINE__, NULL); 

         /* Unknown message in this state*/
        return (ITS_EINVALIDARGS); 
    }

    foundCtxt->dlref = slref;
    foundCtxt->inLabel = *mtp3;

    if(foundCtxt->state == SCCP_CONN_IN_PEND
       ||foundCtxt->state == SCCP_DATA_TRANSFER
       || foundCtxt->state == SCCP_IN_RELEASE_PEND
       || isRLSDtobesent == 1)
    {
        SCCP_DEBUG(("HandleDownCC:CC received in state %x",foundCtxt->state));
        SCCP_Alarm_ANSI(656, __FILE__, __LINE__, NULL); 

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));
        }

        SCCP_DEBUG(("HandleDownCC:Notification for RLSD is sent to app and"
                    " RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    foundCtxt->dlref = slref;
    foundCtxt->inLabel = *mtp3;

    foundCtxt->state = SCCP_DATA_TRANSFER;
    foundCtxt->dataState = SCCP_DATA_NORMAL;

    switch ((pc->pclass & SCCP_PCLASS_MASK))
    {
    case SCCP_PCLASS_2:
        if (foundCtxt->pclass == SCCP_PCLASS_3)
        {
            foundCtxt->windowSize = 0;
            foundCtxt->pclass = SCCP_PCLASS_2;
        }
        break;

    case SCCP_PCLASS_3:
        if (foundCtxt->pclass == SCCP_PCLASS_2)
        {
            SCCP_WARNING(("HandleDownCC: Invalid protocol class for connection\n"));

            /* Incoming Message - Protocol Class of Message does not match Connection. */


                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ANSI_SCCP_CTXT,
                                   (ITS_OCTET *)&hdr->context.conref, 
                                    sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleDownCC: DSM unable to free Reference."
                                "\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }

                SCCP_ERROR(("HandleDownCC:Relase procedure is initiated by"
                            " stack,sending RLSD to the remote end\n"));

                SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
                NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                                SCCP_RLC_INCONSISTENT_DATA);

                *sendToApp = ITS_FALSE;
                return (ITS_ENOCONN);
            }

           if (foundCtxt->windowSize < creditvalue)
           {


               SCCP_DEBUG(("HandleDownCC:Invalid Credit value sent in CC from"
                           " the application,message is discarded\n"));

               return(ITS_EBADCHKSUM);
           }

           break;

    default:
        SCCP_WARNING(("HandleDownCC: Invalid protocol class for connection\n"));


        /* Incoming Message - Protocol Class of Message does not match Connection. */


        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));


        }

        return (ITS_ENOCONN);
    }

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->connectTimer)
    {
        SCCP_DEBUG(("HandleDownCC:CANCEL Connect Timer is killed : SERIAL [%d]",foundCtxt->connectTimer));
        error = TIMERS_CancelTimer(foundCtxt->connectTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownCC: FAIL To CANCEL connectTimer SERIAL [%d]\n",foundCtxt->connectTimer));
        }
        foundCtxt->connectTimer = 0;
    }
    if(foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleDownCC:CANCEL ReleaseTimer is killed as waiting CC"
                    "  received.: SERIAL [%d]\n ",foundCtxt->releaseTimer));       

        error = TIMERS_CancelTimer(foundCtxt->releaseTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownCC: FAIL To CANCEL releaseTimer SERIAL [%d]\n",foundCtxt->releaseTimer));
        }
        foundCtxt->releaseTimer= 0;
        
        SCCP_DEBUG(("HandleDownCC:RLSD is sent to the other end for received"
                    "  CC\n"));

        SendRLSD(foundCtxt, SCCP_REF_ACCESS_CONG , ITS_FALSE);

        *sendToApp = ITS_FALSE;

        return(ITS_SUCCESS);
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownCC:START sendInactivity timer :SERIAL[%d]\n",foundCtxt->sendInactivity));	 

    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownCC:START receiveInactivity timer :SERIAL[%d]\n",foundCtxt->receiveInactivity));	 
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownCC: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownCC: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownCC: Can't find ConnectionReference in table.\n"));
                break;
            }
    
            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        if (cdp)
        {
            *cdp = foundCtxt2->daddr;
        }

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        if (cdp)
        {
            *cdp = foundCtxt->oaddr;
        }

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {    
            SCCP_ERROR(("HandleDownCC: DSM unable to free Reference.\n"));
        }

    }


    if (!*sendToApp)
    {
        return HandleAppCC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send connection refused
 */
static int
HandleAppCREF(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_ADDR *cdp = NULL, local;
    SCCP_REF_NUM *dl = NULL;
    int i, error;

    SCCP_DEBUG(("HandleAppCREF\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppCREF: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppCREF: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppCREF: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;

    if (cdp == NULL)
    {
        local = foundCtxt->daddr;
        cdp = &local;
    }

#if defined(CONNECTION_TIMERS)
     if(foundCtxt->connectTimer)
     {
        SCCP_DEBUG(("HandleAppCREF:CANCEL  Connect Timer killed : SERIAL [%d]\n",foundCtxt->connectTimer));
        error = TIMERS_CancelTimer(foundCtxt->connectTimer);
        if(error != ITS_SUCCESS)
        {
          SCCP_ERROR(("HandleAppCREF: FAIL To CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
        }
        foundCtxt->connectTimer = 0;
     }
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppCREF: DSM unable to free Reference.\n"));

    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    /* we allocated this one.  Release it */
    SCCP_DeleteLocalReference_ANSI(hdr->context.conref);
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_CREF_TO_REMOTE_SENT);

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_CREF, ies, ieCount, cdp);
}

static int
HandleDownCREF(ITS_HDR* hdr, MTP3_HEADER* mtp3,
               ITS_SCCP_IE* ies, int ieCount, 
               ITS_BOOLEAN* sendToApp, ITS_OCTET* ssn)
{
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR *cdp = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    SCCP_CONN_CTXT foundCtxtdata;
    ITS_CTXT      tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownCREF\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_CREF_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_CALLED_PARTY_ADDR:
            cdp = &ies[i].param_data.calledPartyAddr;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownCREF: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownCREF:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownCREF:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownCREF: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownCREF: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownCREF: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownCREF:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/
    *ssn  = foundCtxt->lssn;
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_OUT_RELEASE_PEND 
        || foundCtxt->state == SCCP_IN_RELEASE_PEND
        ||  foundCtxt->state == SCCP_DATA_TRANSFER)
    {
        SCCP_DEBUG(("HandleDownCREF:CREF Received in Data Transfer state,\
                     so message is discarded\n"));
        SCCP_Alarm_ANSI(657, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownCREF:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Sends notification to Application*/
         releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

   }

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->connectTimer)
    {
       SCCP_DEBUG(("HandleDownCREF:CANCEL Connect timer is killed : SERIAL [%d]\n",foundCtxt->connectTimer));
        error = TIMERS_CancelTimer(foundCtxt->connectTimer);
        if(error != ITS_SUCCESS)
        {
         SCCP_ERROR(("HandleDownCREF: FAIL To CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
        }
        foundCtxt->connectTimer = 0;
    }
    if(foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleDownCREF:CANCEL ReleaseTimer is killed as waiting CREF"
                    "  received.: SERIAL [%d]",foundCtxt->releaseTimer));

        error = TIMERS_CancelTimer(foundCtxt->releaseTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownCREF: FAIL To CANCEL ReleaseTimer Timer SERIAL [%d]\n",foundCtxt->releaseTimer));
        }
        foundCtxt->releaseTimer = 0;
        SCCP_DEBUG(("HandleDownCREF:RLSD is sent to the other end for"
                     " received CREF\n"));
         memcpy(&foundCtxtdata,foundCtxt,sizeof(SCCP_CONN_CTXT));
         /*Release the lock*/
         error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);
         if (error != ITS_SUCCESS)
         {
             SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));

             /* Unable to Commit Session Context to CTXT Table. */
         }

        foundCtxt = NULL;
        SendRLSD(&foundCtxtdata, SCCP_REF_ACCESS_CONG, ITS_FALSE);
        *sendToApp = ITS_FALSE;

        return(ITS_SUCCESS);
    }
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownCREF: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownCREF: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownCREF: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownCREF: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;
    }

    SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

    if (!*sendToApp)
    {
        return HandleAppCREF(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send release complete
 */
static int
HandleAppRLC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppRLC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (RN_GET_REF_NUM(*sl) != hdr->context.conref)
    {
        SCCP_ERROR(("HandleAppRLC: Released and context mismatch\n"));

        return (ITS_EINVALIDARGS);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppRLC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppRLC: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppRLC: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;
     MTP3_RL_SET_SLS(mtp3->label,foundCtxt->sequenceSLS);

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->releaseTimer)
    {
        SCCP_DEBUG(("HandleAppRLC: Release Timer killed : SERIAL[%d]\n",foundCtxt->releaseTimer));
        error = TIMERS_CancelTimer(foundCtxt->releaseTimer);
        if(error != ITS_SUCCESS)
        {
          SCCP_ERROR(("HandleAppRLC: FAIL To CANCEL ReleaseTimer Timer SERIAL [%d]\n",foundCtxt->releaseTimer));
        }
        foundCtxt->releaseTimer = 0;
    }
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRLC: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    /* we allocated this one.  Release it */
    SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

     if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_RLC, ies, ieCount, cdp);
}

/*****************************************************************************
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference                   Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0630, Bug ID:0621, 
 *                        Bug ID:0622, Bug ID:0623            
 *
 ****************************************************************************/
static int
HandleDownRLSD(ITS_HDR* hdr, MTP3_HEADER* mtp3,
               ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp,
               ITS_OCTET* ssn)
{
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    ITS_INT i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRLSD\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRLSD: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRLSD:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownRLSD:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownRLSD: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownRLSD: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownRLSD: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
    *ssn = foundCtxt->lssn;

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRLSD:Orignating Point Code received not equal\
                     to the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

/*Not Handled at BSSAP 08 APR 09 */
/* 
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                      SCCP_ERR_PC_MISMATCH);
*/
        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRLSD:Connection context dlref mismatch with\
                     the received slref"));
         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));
        }

        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

/*Not Handled at BSSAP 08 APR 09 */
/* 
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_BAD_LRN);
*/
        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;
        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state == SCCP_IN_RELEASE_PEND
        || foundCtxt->state == SCCP_OUT_RELEASE_PEND)
    {
        SCCP_ERROR(("HandleDownRLSD:RLSD received in state = %x,dicarded",
                     foundCtxt->state));

         /* Unknown message in this state*/
        SCCP_Alarm_ANSI(658, __FILE__, __LINE__, NULL);

        SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

        return (ITS_EBADSTATE);
    }

    if (foundCtxt->state == SCCP_CONN_IN_PEND)
    {
        SCCP_DEBUG(("HandleDownRLSD:RLSD received in Incoming Connection"
                    " Pending state\n"));
        SCCP_Alarm_ANSI(658, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownRLSD:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        SCCP_DeleteLocalReference_ANSI(hdr->context.conref);
        
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

   }
 
    foundCtxt->state = SCCP_IN_RELEASE_PEND;

#if defined(CONNECTION_TIMERS)
    foundCtxt->releaseTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_release),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownRLSD:START releaseTimer: SERIAL [%d]\n",foundCtxt->releaseTimer));	 
    if (foundCtxt->receiveInactivity)
    {
        SCCP_DEBUG(("HandleDownRLSD:Receive Inactivity timer is killed: SERIAL[%d]",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRLSD: FAIL To CANCEL ReceiveInactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    if (foundCtxt->sendInactivity)
    {
        SCCP_DEBUG(("HandleDownRLSD:Send Inactivity timer is killed: SERIAL[%d]",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRLSD: FAIL To CANCEL sendInactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));
    }
    
    SCCP_DEBUG(("HandleDownRLSD:RLC is sent to MTP3\n"));

    RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
    releaseID++;

    RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
    releaseID++;

    ieCount = releaseID++;

    if (HandleAppRLC( hdr,mtp3, ies, ieCount) != ITS_SUCCESS)
    {
         SCCP_ERROR(("HandleDownRLSD:Failure in Application RLC\n"));

         return(ITS_ENOCONN);
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownRLSD: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRLSD: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownRLSD: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }


        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLSD: DSM unable to free Reference.\n"));
        }

        SCCP_DEBUG(("HandleDownRLSD:RLC is send to MTP3\n"));

        if (HandleAppRLC( hdr,mtp3, ies, ieCount) != ITS_SUCCESS)
        {
             SCCP_ERROR(("HandleDownRLSD:Failure in HandleAppRLC\n"));

             return(ITS_ENOTFOUND);
        }

        foundCtxt2 = NULL;
    }

    if (!*sendToApp)
    {
        return HandleAppRLSD(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

static int
HandleDownRLC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRLC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRLC:Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRLC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownRLC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownRLC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownRLC: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownRLC: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRLC:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_DATA_TRANSFER
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRLC:RLC received in Invalid State RLSD\
                      is sent\n"));
        SCCP_Alarm_ANSI(659, __FILE__, __LINE__, NULL);

        foundCtxt->dlref = hdr->context.conref;

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownRLC:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);
        
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

   }
    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
       SCCP_DEBUG(("HandleDownRLC:Connection context dlref mismatch with"
                     " the received slref"));

        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->releaseTimer)
    {
       SCCP_DEBUG(("HandleDownRLC:CANCEL Release Timer is killed: SERIAL [%d]",foundCtxt->releaseTimer));
       error =  TIMERS_CancelTimer(foundCtxt->releaseTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRLC: FAIL To CANCEL Release Timer SERIAL [%d]\n",foundCtxt->releaseTimer));
        }
        foundCtxt->releaseTimer = 0;
    }

    if (foundCtxt->repeatReleaseTimer)
    {
       SCCP_DEBUG(("HandleDownRLC:CANCEL Repeat Release Timer is killed: SERIAL [%d]",foundCtxt->releaseTimer));
        error = TIMERS_CancelTimer(foundCtxt->repeatReleaseTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRLC: FAIL To CANCEL Repeat Release Timer SERIAL [%d]\n",foundCtxt->repeatReleaseTimer));
        }
        foundCtxt->repeatReleaseTimer = 0;
    }

    if (foundCtxt->intervalTimer)
    {
       SCCP_DEBUG(("HandleDownRLC:CANCEL Interval Timer is killed: SERIAL [%d]",foundCtxt->intervalTimer));
        error = TIMERS_CancelTimer(foundCtxt->intervalTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRLC: FAIL To CANCEL Interval Timer SERIAL [%d]\n",foundCtxt->intervalTimer));
        }
       foundCtxt->intervalTimer = 0;
    }
#endif

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownRLC: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRLC: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownRLC: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*sl, foundCtxt2->slref);
        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRLC: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    SCCP_DeleteLocalReference_ANSI((ITS_CTXT)dlref);

    if (!*sendToApp)
    {
        return HandleAppRLC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * Send DT1
 */
static int
HandleAppDT1(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    ITS_OCTET    data[SCCP_LONG_DATA_MAX];
    int          dataLen = -1;
    int          dataIndex = -1;
    int          segIndex = -1;
    int          ret = ITS_SUCCESS;
    ITS_OCTET    totalSegment;
    ITS_UINT ref;
    ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    SCCP_DEBUG(("HandleAppDT1\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppDT1: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }

       if (redunClass)
        {
         if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
         {
            SCCP_ERROR(("Backup Node Cannot Initiate Messages.\n"));


            return (ITS_EINVINITSTATE);
         }
       }
    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppDT1: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppDT1: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppDT1: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_2)
    {
        SCCP_ERROR(("HandleAppDT1: DT1 is invalid for protocol class.\n"));

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(672, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */ 

        return (ITS_EINVALIDARGS);
    }


    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownDT1: DT1 is invalid for connection state.\n"));

        /* Outgoing Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_ANSI(660, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;
     MTP3_RL_SET_SLS(mtp3->label,foundCtxt->sequenceSLS);

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppDT1: Send Inactivity Timer is killed: SERIAL[%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppDT1: FAIL To CANCEL SendInactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
       foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppDT1:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
 
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DATA)
        {
            dataIndex = i;
            dataLen = ies[i].param_length;

            memcpy(data, ies[i].param_data.userData.data, dataLen);
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        {
            dataIndex = i;
            dataLen = ies[i].param_data.longData.len;

            memcpy(data, ies[i].param_data.longData.data, dataLen);
            ies[i].param_id = SCCP_PRM_DATA;
        }
        if (ies[i].param_id == SCCP_PRM_SEGMENT_REASSEM)
        {
            segIndex = i;
        }
    }

    totalSegment = dataLen / SCCP_MAX_DATA;

    if (dataIndex < 0)
    {
        SCCP_ERROR(("HandleAppDT1: Missing Data IE \n"));

        /* Outgoing Message - Discarding Message - Missing 
          Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }

    if (dataLen % SCCP_MAX_DATA)
    {
        totalSegment++;
    }

    /* add an extra IE temparay for failure handling */
    ref = hdr->context.conref;
    ies[ieCount].param_id = SCCP_PRM_SRC_LOCAL_REF;
    ies[ieCount].param_length = sizeof(SCCP_REF_NUM);
    ies[ieCount].param_data.sourceLocalReference.refno[0] = (ref >> 16) & 0xFFU;
    ies[ieCount].param_data.sourceLocalReference.refno[1] = (ref >> 8) & 0xFFU;
    ies[ieCount].param_data.sourceLocalReference.refno[2] = (ref) & 0xFFU;
    ieCount++;

    for (i = 0;i < totalSegment; i++)
    {
        if (segIndex < 0)
        {
            SCCP_ERROR(("HandleAppDT1: Missing  segment reassem ie \n"));

            /* Outgoing Message - Discarding Message - Missing 
             Mandatory Parameter. */

            return (ITS_EMISSMAND);
        }

        if (dataLen < (SCCP_MAX_DATA + (i * SCCP_MAX_DATA)))
        {
            ies[dataIndex].param_length = dataLen - (i * SCCP_MAX_DATA);

            memcpy(ies[dataIndex].param_data.userData.data, 
                   &(data[i * SCCP_MAX_DATA]), dataLen - (i * SCCP_MAX_DATA));
        }
        else if (dataLen == i * SCCP_MAX_DATA)
        {
            return ITS_SUCCESS;
        }
        else
        {
            ies[dataIndex].param_length = SCCP_MAX_DATA;

            memcpy(ies[dataIndex].param_data.userData.data, 
                   &(data[i * SCCP_MAX_DATA]), SCCP_MAX_SEG_DATA);
        }

        if(i == (totalSegment - 1))
        {
            /* last segment */
            ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                        SCCP_SR_END_OF_DATA;
        }
        else
        {
            ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                          SCCP_SR_MORE_DATA;
        }

        if (gcsMessageBasedRedundancyIsActive)
        {
            ITS_EVENT dummyEvent;
            ITS_UINT  dest;

            SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

            dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
            dummyEvent.data = 0;

            dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

            if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
            {
                /* Don't send message for routing to the network */
                SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                              hdr->context.conref));

                continue;
            }

        }

        SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                     hdr->context.conref));

        ret = SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_DT1, ies, 
                                      ieCount, cdp);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT, 
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppDT1: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    return ret;
}

static int
HandleDownDT1(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;
    int segIndex = -1;
    int dataIndex = -1;
    ITS_OCTET   dataLen;
    ITS_OCTET   data[SCCP_MAX_DATA];
    int         ret;
    /*Used for sending Error Ntfy to App*/
     ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);   

    SCCP_DEBUG(("HandleDownDT1\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT1_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
        }
        if (ies[i].param_id == SCCP_PRM_SEGMENT_REASSEM)
        {
            segIndex = i;
        }
        if (ies[i].param_id == SCCP_PRM_DATA)
        {
            dataIndex = i;
        }
    }

    if (dataIndex < 0)
    {
        SCCP_ERROR(("HandleAppDT1: Missing data \n"));

        /* Outgoing Message - Discarding Message - Missing Mandatory 
          Parameter. */

        return (ITS_EMISSMAND);
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownDT1: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownDT1:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
//    SCCP_DEBUG(("HandleDownDT1\n............"));
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownDT1:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
       if (redunClass)
        {
         if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
         {
            SCCP_ERROR(("Backup Node Cannot Initiate Messages.\n"));


            return (ITS_EINVINITSTATE);
         }
       }

 //   SCCP_DEBUG(("HandleDownDT1,,,,,,,,,,,\n"));
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;
  //  SCCP_DEBUG(("HandleDownDT1''''''''''''\n"));

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT, 
                                           (ITS_OCTET *)&hdr->context.conref, 
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownDT1: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownDT1: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownDT1: Can't find ConnectionReference in table.\n"));
            break;
        }

            return (ITS_ENOCONN);
      }

   // SCCP_DEBUG(("HandleDownDT1\n"));
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownDT1:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));
        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_2)
    {
        SCCP_ERROR(("HandleDownDT1: DT1 is invalid for protocol class.\n"));
        SCCP_Alarm_ANSI(673, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */ 

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownDT1:DT1 received in State %x",foundCtxt->state));
        SCCP_Alarm_ANSI(661, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownDT1:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Sends notification of RLSD to app*/
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;

        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
   } 

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownDT1: DT1 is invalid for connection state.\n"));
        SCCP_Alarm_ANSI(661, __FILE__, __LINE__, NULL);

        /* Release the lock on row  */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownDT1:CANCEL  Receive Inactivity Timer is killed: SERIAL [%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownDT1: FAIL To CANCEL Receive Inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppDT1:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
 
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    SCCP_DEBUG(("HandleDownDT1 tempIsIntermediate %d\n",tempIsIntermediate));
    /* Release the lock on row */
  /*  error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;*/    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownDT1: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownDT1: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownDT1: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }


        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);

        foundCtxt2 = NULL;    /* Not safe to use with out lock */

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

            /* Unable to Commit Session Context to CTXT Table. */
        }
    }
    else
    {
        SCCP_DEBUG(("HandleDownDT1 segIndex %d\n",segIndex));
        if (segIndex < 0)
        {
            SCCP_ERROR(("HandleDownDT1: Missing segment ie \n"));

            PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_REASSEMBLE_ERR);

            return (ITS_EMISSMAND);
        }

         SCCP_DEBUG(("HandleDownDT1 seg_res %d\n",ies[segIndex].param_data.segmentingReassembly.seg_res));
        if (ies[segIndex].param_data.segmentingReassembly.seg_res == 
                                                          SCCP_SR_MORE_DATA)
        {

            /* If total length of all fragments exceeds LONG_DATA_MAX
             * should not happen usually*/
             SCCP_DEBUG(("HandleDownDT1 len1 %d\n",ies[dataIndex].param_length));
             SCCP_DEBUG(("HandleDownDT1 len2 %d\n",foundCtxt->totalDataLen));
            if (ies[dataIndex].param_length + foundCtxt->totalDataLen >
                                                            SCCP_LONG_DATA_MAX)
            {
                dataLen = ies[dataIndex].param_length;

                memcpy(data, ies[dataIndex].param_data.userData.data, 
                       dataLen);

                if (foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.
                                     longData.data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                      data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }

                foundCtxt->totalDataLen = dataLen;

                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, data, dataLen);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }
            }
            else
            {
               SCCP_ERROR(("SCOC_PutDataInFragList %d \n",foundCtxt->startFragKey));
                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref,
                                        ies[dataIndex].param_data.userData.data,
                                        ies[dataIndex].param_length);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                foundCtxt->totalDataLen += ies[dataIndex].param_length;

                *sendToApp = ITS_FALSE;

                error = DSM_Commit(DSM_SccpFtGroupId,
                                   DSM_TABLE_ANSI_SCCP_CTXT, 
                                   (ITS_OCTET *)&hdr->context.conref, 
                                   sizeof(hdr->context.conref), foundCtxt);

                if (error != ITS_SUCCESS)
                {
                    SCCP_ERROR(("HandleDownDT1: DSM unable to "
                                "free Reference.\n"));

                    /* Unable to Commit Session Context to CTXT Table. */
                }

                return ITS_SUCCESS;
            }
        }
        else
        {
             SCCP_DEBUG(("HandleDownDT1 length %d \n",ies[dataIndex].param_length));
             SCCP_DEBUG(("HandleDownDT1 length %x \n",foundCtxt));
             SCCP_DEBUG(("HandleDownDT1 length2 %d \n",foundCtxt->totalDataLen));
            if ((ies[dataIndex].param_length + foundCtxt->totalDataLen) >
                                                            SCCP_LONG_DATA_MAX)
            {
                dataLen = ies[dataIndex].param_length;
                memcpy(data, ies[dataIndex].param_data.userData.data, 
                       dataLen);

                if (foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.longData.
                                     data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                      data, &(foundCtxt->startFragKey));

                    foundCtxt->startFragKey = 0;

                }

                foundCtxt->totalDataLen = dataLen;

                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, 
                                        data, dataLen);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                ies[segIndex].param_data.segmentingReassembly.seg_res = 
                                                             SCCP_SR_MORE_DATA;
            }
            else
            {
               SCCP_ERROR(("SCOC_PutDataInFragList \n"));
               SCCP_ERROR(("SCOC_PutDataInFragList %d \n",foundCtxt->startFragKey));
                ret = SCOC_PutDataInFragList(&(foundCtxt->startFragKey), 
                                        foundCtxt->slref, 
                                        ies[dataIndex].param_data.userData.data,
                                        ies[dataIndex].param_length);

                if(ret != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCOC_PutDataInFragList Failed \n"));
                }

                foundCtxt->totalDataLen += ies[dataIndex].param_length;

                if(foundCtxt->totalDataLen >= SCCP_MAX_DATA)
                {
                    ies[dataIndex].param_id = SCCP_PRM_LONG_DATA;
                    ies[dataIndex].param_data.longData.len = 
                                                      foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.longData.
                                        data, &(foundCtxt->startFragKey));
                }
                else
                {
                    ies[dataIndex].param_id = SCCP_PRM_DATA;
                    ies[dataIndex].param_length = foundCtxt->totalDataLen;

                    SCOC_GetDataFromFragList(ies[dataIndex].param_data.userData.
                                        data, &(foundCtxt->startFragKey));
                }

                foundCtxt->startFragKey = 0;
                foundCtxt->totalDataLen = 0;
            }
        }
    }
            
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT, 
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownDT1: DSM unable to free Reference.\n"));

        /* Unable to Commit Session Context to CTXT Table. */
    } 

    if (!*sendToApp)
    {
        return HandleAppDT1(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send DT2
 */
static int
HandleAppDT2(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppDT2\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppDT2: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }

 
    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppDT2: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppDT2: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppDT2: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppDT2: DT2 is invalid for protocol class.\n"));

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(674, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppDT2: DT2 is invalid for connection state.\n"));
        SCCP_Alarm_ANSI(662, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppDT2: Send Inactivity Timer is killed: SERIAL[%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppDT2: FAIL To CANCEL Send Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppDT1:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppDT2: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_DT2, ies, ieCount, cdp);
}



static int
HandleDownDT2(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    /* Holds the reference of Previous P(S).*/
    static ITS_OCTET prevSentSeqID = 0;
    int improperDataSeq = 0;

    SCCP_DEBUG(("HandleDownDT2\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_DT2_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
             case SCCP_PRM_DEST_LOCAL_REF:
             dl = &ies[i].param_data.destinationLocalReference;
             releaseID = i;
             break;

             case SCCP_PRM_SEQUENCE_SEGMENT:

             if (prevSentSeqID!=0)
             {
                 if ( prevSentSeqID == ((ies[i].param_data.sequenceSegment.tsn & 0xFE)>>1))
                 {
                     prevSentSeqID++;
                     SCCP_DEBUG (("HandleDownDT2:Sequence number in DT2\
                                    is correct\n"));
                 }
                 else
                 {
                     SCCP_DEBUG(("HandleDownDT2:Mismatch in P(S)\n"));
                     improperDataSeq = 1;
                 }
             }
             else
             {
                 SCCP_DEBUG(("HandleDownDT2:Prev sequence id is assigned\n"));

                 prevSentSeqID = (ies[i].param_data.sequenceSegment.tsn & 0xFE)>>1;
                 prevSentSeqID++;
             }
             break;
        }
        if (improperDataSeq == 1)
        {
            SCCP_DEBUG(("HandleDownDT2: Improper Seq in DT2 recv,checking\
                         for connection context sequence\n"));
            prevSentSeqID = 0;

            break;
        }
        
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownDT2: Missing destination reference number \n"));

        /* Incoming Message - Missing Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }
/*
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownDT2:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownDT2:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownDT2:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownDT2: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownDT2: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownDT2: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownDT2:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownDT2: DT2 is invalid for protocol class.\n"));

        /* Incoming Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(675, __FILE__, __LINE__,"Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownDT2:DT2 received in State %x",foundCtxt->state));
        SCCP_Alarm_ANSI(663, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownDT2:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
        /*Notification of RLSD to Application*/
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        /*Releaseid contains both slr and dlr so it is decemented*/
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
   }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownDT2: DT2 is invalid for connection state.\n"));

        SCCP_Alarm_ANSI(663, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

            /* Was unable to commit row of CTXT Table using DSM_Commit. */
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownDT2:CANCEL  Receive Inactivity is killed : SERIAL [%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
          SCCP_ERROR(("HandleDownDT2: FAIL To CANCEL Receive inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownDT2:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
 
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;
    
    if (improperDataSeq == 1)
    {
        if (foundCtxt->sequenceOn == ITS_TRUE)
        {
            SCCP_DEBUG(("HandleDownDT2:Sequence is on for the Connection\
                         context.\n"));
            /* The value of i is of Seq/segment  hence i is decremented */
            i--;

            RN_SET_REF_NUM(ies[i].param_data.destinationLocalReference,
                           foundCtxt->dlref);
            i++;
            ies[i].param_id = SCCP_PRM_SRC_LOCAL_REF;
            ies[i].param_length = sizeof(SCCP_REF_NUM);

            RN_SET_REF_NUM(ies[i].param_data.sourceLocalReference,
                       foundCtxt->slref);

            i++;

            ies[i].param_id = SCCP_PRM_RESET_CAUSE;
            ies[i].param_length = sizeof(SCCP_RES_CAUSE);
            ies[i].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

            i++;

            ieCount = i;

            SCCP_DEBUG(("HandleDownDT2:RSR is send to the remote end\n"));

            error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
            if (error != ITS_SUCCESS)
            {
                SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));

                /* Unable to Commit Session Context to CTXT Table. */
            }

            return HandleAppRSR(hdr,mtp3,ies,ieCount);
        }
        else
        {
            SCCP_DEBUG(("HandleDownDT2:Sequence is not on for the connection\
                       context.Sequence id is updated for the connection\n"));
            prevSentSeqID++;

        }
    }

    foundCtxt->sequenceOn = ITS_TRUE;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownDT2: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownDT2: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownDT2: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
         /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownDT2: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppDT2(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * send AK
 */
static int
HandleAppAK(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppAK\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppAK: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppAK: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppAK: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppAK: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppAK: AK is invalid for protocol class.\n"));

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(676, __FILE__, __LINE__,"Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppAK: AK is invalid for connection state.\n"));

        SCCP_Alarm_ANSI(664, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppAK:CANCEL Send  Inactivity is killed : SERIAL [%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
          SCCP_ERROR(("HandleAppAK: FAIL To CANCEL Send  Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppAK:START sendInactivity timer :SERIAL[%d]\n",foundCtxt->sendInactivity));	 
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppAK: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_AK, ies, ieCount, cdp);
}

static int
HandleDownAK(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownAK\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownAK: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownAK:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownAK:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

     foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                            DSM_TABLE_ANSI_SCCP_CTXT,
                                            (ITS_OCTET *)&hdr->context.conref,
                                            sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownAK: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownAK: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownAK: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownAK:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));
        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       

        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/
    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownAK: AK is invalid for protocol class.\n"));

        /* Incoming Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(677, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);


        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownAK:AK received in State %x",foundCtxt->state));
        SCCP_Alarm_ANSI(665, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownAK:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
        /*Notification of RLSD to Application*/
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownAK: AK is invalid for connection state.\n"));
        SCCP_Alarm_ANSI(665, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownAK:CANCEL Receive  Inactivity is killed : SERIAL [%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownAK: FAIL To CANCEL Receive Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownAK:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif

    
    /* Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */
    
    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownAK: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownAK: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownAK: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownAK: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppAK(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * expedited data
 */
/*****************************************************************************
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:1613
 *
 ****************************************************************************/
static int
HandleAppED(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppED\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppED: HandleAppEDMissing destination reference number \n"));

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppED: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppED: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppED: Can't find ConnectionReference in table.\n"));
            break;
        }
        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppED: ED is invalid for protocol class.\n"));

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(678, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppED: ED is invalid for connection state.\n"));

        SCCP_Alarm_ANSI(666, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
    case SCCP_DATA_NORMAL:
        foundCtxt->dataState = SCCP_DATA_OUT_ED;
        break;

    case SCCP_DATA_IN_ED:
        foundCtxt->dataState = SCCP_DATA_BOTH_ED;
        break;

    case SCCP_DATA_OUT_ED:
    case SCCP_DATA_BOTH_ED:
        break;
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppED:CANCEL Send  Inactivity is killed : SERIAL [%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppED: FAIL To CANCEL Send  Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }

    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppED:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppED: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_ED, ies, ieCount, cdp);
}


/*
 * Send EA
 */
static int
HandleAppEA(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    
    SCCP_DEBUG(("HandleAppEA\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleAppEA : Missing destination reference number \n"));

        /* Outgoing Message - Missing Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppEA: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppEA: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppEA: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
      }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppEA: EA is invalid for protocol class.\n"));

        SCCP_Alarm_ANSI(679, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleAppEA:EA is invalid for connection state.\n"));

        /* Outgoing Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_ANSI(668, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
        case SCCP_DATA_BOTH_ED:
            foundCtxt->dataState = SCCP_DATA_IN_ED;
            break;

        case SCCP_DATA_IN_ED:
            foundCtxt->dataState = SCCP_DATA_NORMAL;
            break;

        case SCCP_DATA_OUT_ED:
        case SCCP_DATA_NORMAL:
        break;
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppEA:CANCEL Send  Inactivity is killed : SERIAL [%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppEA: FAIL To CANCEL Send  Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppEA:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppEA: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */


    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_EA, ies, ieCount, cdp);
}


static int
HandleDownED(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownED\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ED_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownED: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownED:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownED:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl);
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownED: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownED: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownED: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownED:Orignating Point Code received not equal to"
                    "  the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }
    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownED: ED is invalid for protocol class.\n"));

        SCCP_Alarm_ANSI(680, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_IN_PEND
       || foundCtxt->state == SCCP_CONN_OUT_PEND
       || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownED:ED received in State %x",foundCtxt->state));
        SCCP_Alarm_ANSI(667, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

        }

        SCCP_DEBUG(("HandleDownED:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
        /*Notification of RLSD to Application*/
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
    }
    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownED: ED is invalid for connection state.\n"));
        SCCP_Alarm_ANSI(667, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }


    switch (foundCtxt->dataState)
    {
    case SCCP_DATA_NORMAL:
        foundCtxt->dataState = SCCP_DATA_IN_ED;
        break;

    case SCCP_DATA_OUT_ED:
        foundCtxt->dataState = SCCP_DATA_BOTH_ED;

        break;

    case SCCP_DATA_IN_ED:
    case SCCP_DATA_BOTH_ED:
        break;
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownED:Receive Inactivity timer is killed: SERIAL[%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownED: FAIL To CANCEL receiveInactivity SERIAL [%d]\n",foundCtxt->receiveInactivity ));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownED:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif


    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref,
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));

    }

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT,
                                                (ITS_OCTET *)&tempAssocRef,
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownED: Couldn't acquire mutex.\n"));
                break;

            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownED: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownED: Can't find ConnectionReference in table.\n"));
                break;

            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownED: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppED(hdr, mtp3, ies, ieCount);
    }
    RN_SET_REF_NUM(ies[i].param_data.destinationLocalReference,
                       foundCtxt->dlref);
    if (HandleAppEA( hdr, mtp3, ies,ieCount) != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownED: Failed to sent EA \n"));

        return (ITS_EINVALIDARGS);
    }

    foundCtxt = NULL;


    return (ITS_SUCCESS);
}

static int
HandleDownEA(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownEA\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = 0;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownEA: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownEA:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownEA: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownEA: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownEA: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownEA:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownEA: EA is invalid for protocol class.\n"));

        /* Incoming Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(681, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND) 
    {
        SCCP_DEBUG(("HandleDownEA:EA received in State %x",foundCtxt->state));
        SCCP_Alarm_ANSI(669, __FILE__, __LINE__, NULL);

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));
        }

        SCCP_DEBUG(("HandleDownEA:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);
        /*Notification of RLSD to Application*/
         releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);  

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

    }
    if (foundCtxt->state != SCCP_DATA_TRANSFER)
    {
        SCCP_ERROR(("HandleDownEA: EA is invalid for connection state.\n"));

        /* Incoming Message - Message Type not valid for State of Connection. */
        SCCP_Alarm_ANSI(669, __FILE__, __LINE__, NULL);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EBADSTATE);
    }

    switch (foundCtxt->dataState)
    {
    case SCCP_DATA_BOTH_ED:
        foundCtxt->dataState = SCCP_DATA_OUT_ED;
        break;

    case SCCP_DATA_OUT_ED:
        foundCtxt->dataState = SCCP_DATA_NORMAL;
        break;

    case SCCP_DATA_IN_ED:
    case SCCP_DATA_NORMAL:
        break;
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownEA:Receive Inactivity timer is killed: SERIAL[%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownEA: FAIL To CANCEL Receive Inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownEA:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */
    
    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownEA: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownEA: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownEA: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownEA: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppEA(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

static int
HandleDownRSR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRSR\n"));
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_RSR_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRSR: Missing destination reference number \n"));

        /* Incoming Message - Missing Mandatory Parameter." */

        return (ITS_EMISSMAND);
    }
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRSR:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownRSR: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownRSR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownRSR: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRSR:Orignating Point Code received not equal to\
                    the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                      SCCP_ERR_PC_MISMATCH);

        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRSR:Connection context dlref mismatch with"
                     " the received slref"));
        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_BAD_LRN);
        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleDownRSR: RSR is invalid for protocol class.\n"));

        /* Incoming Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(682, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if(foundCtxt->state == SCCP_CONN_IN_PEND
       || foundCtxt->state == SCCP_CONN_OUT_PEND
       || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRSR:RSR received in State %x",foundCtxt->state));

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownRSR:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);
        
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

   }

    foundCtxt->state = SCCP_IN_RESET_PEND;

#if defined(CONNECTION_TIMERS)
    foundCtxt->resetTimer =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_reset),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownRSR:START resetTimer: SERIAL [%d]\n",foundCtxt->resetTimer));	 

    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownRSR:Receive Inactivity timer is killed: SERIAL[%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRSR: FAIL To CANCEL Receive Inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownRSR:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownRSR: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRSR: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownRSR: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSR: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppRSR(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * reset confirm
 */
static int
HandleAppRSC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
    
    SCCP_DEBUG(("HandleAppRSC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppRSC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppRSC: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppRSC: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("HandleAppRSC: RSC is invalid for protocol class.\n"));

        /* Outgoing Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(683, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleAppRSC: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }

    foundCtxt->state = SCCP_DATA_TRANSFER;

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->resetTimer)
    {
         SCCP_DEBUG(("HandleAppRSC:Reset timer is killed: SERIAL[%d]\n",foundCtxt->resetTimer));
         error = TIMERS_CancelTimer(foundCtxt->resetTimer);
         if(error != ITS_SUCCESS)
         {
            SCCP_ERROR(("HandleAppRSC: FAIL To CANCEL Reset Timer SERIAL [%d]\n",foundCtxt->resetTimer));
         }
         foundCtxt->resetTimer = 0;
    }
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppRSC:CANCEL Send Inactivity timer is killed: SERIAL[%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppRSC: FAIL To CANCEL Send Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppRSC:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppRSC: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_RSC, ies, ieCount, cdp);
}

static int
HandleDownRSC(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_INT dlref;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownRSC\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownRSC: Missing destination reference number \n"));

        /* Incoming Message - Missing Mandatory Parameter. */

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownRSC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownRSC:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownRSC: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownRSC: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownRSC: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownRSC:Orignating Point Coder received not equal to\
                    the Pc stored locally\n"));

        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);

        *sendToApp = ITS_FALSE;

        return(ITS_EINVALIDARGS);
    }

    if (foundCtxt->dlref != RN_GET_REF_NUM(*sl))
    {
        SCCP_DEBUG(("HandleDownRSC:Connection context dlref mismatch with\
                     the received slref"));

        SendERR(foundCtxt, SCCP_ERR_BAD_LRN, ITS_FALSE);

        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_BAD_LRN);

        *sendToApp = ITS_FALSE;

        return (ITS_EINVALIDARGS);
    }

    if (foundCtxt->pclass != SCCP_PCLASS_3)
    {
        SCCP_ERROR(("RSC is invalid for protocol class.\n"));

        /* Incoming Message - Message Type not valid for Protocol Class of Connection. */
        SCCP_Alarm_ANSI(684, __FILE__, __LINE__, "Pclass %d",
                                     foundCtxt->pclass);

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref, 
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */

        return (ITS_EINVALIDARGS);
    }
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownRSC:RSC received in State %x",foundCtxt->state));

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));
        }        

        SCCP_DEBUG(("HandleDownRSC:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);
        
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

    }

    foundCtxt->state = SCCP_DATA_TRANSFER;

#if defined(CONNECTION_TIMERS)
    if(foundCtxt->resetTimer)
    {
        SCCP_DEBUG(("HandleDownRSC:CANCEL resetTimer is killed: SERIAL[%d]\n",foundCtxt->resetTimer));
        error = TIMERS_CancelTimer(foundCtxt->resetTimer);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRSC: FAIL To CANCEL resetTimer SERIAL [%d]\n",foundCtxt->resetTimer));
        }
        foundCtxt->resetTimer = 0;
    }
    if (foundCtxt->receiveInactivity)
    {
        SCCP_DEBUG(("HandleDownRSC:CANCEL receiveInactivity Timer is killed: SERIAL[%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownRSC: FAIL To CANCEL receiveInactivity SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownRSC:START receiveInactivity timer : SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif 

    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownRSC: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownRSC: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownRSC: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);
        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;
        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                            sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownRSC: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppRSC(hdr, mtp3, ies, ieCount);
    }

    return (ITS_SUCCESS);
}

/*
 * err
 */
static int
HandleAppERR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;

    SCCP_DEBUG(("HandleAppERR\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_DEST_LOCAL_REF)
        {
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppERR: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppERR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppERR: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    *mtp3 = foundCtxt->outLabel;

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppERR:Send inactivity timer is killed: SERIAL[%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppERR: FAIL To CANCEL Send inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppERR:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
    
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppERR: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_ERR_TO_REMOTE_SENT);

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_ERR, ies, ieCount, cdp);
}

static int
HandleDownERR(ITS_HDR* hdr, MTP3_HEADER* mtp3,
              ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_INT dlref;
    SCCP_REF_NUM *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt, *foundCtxt2;
    ITS_CTXT        tempAssocRef;
    ITS_BOOLEAN     tempIsIntermediate;
    int i, error;
    int releaseID = 0;
    ITS_OCTET cause = 0 ;

    SCCP_DEBUG(("HandleDownERR\n"));

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_ERR_RCVD);

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;


            case SCCP_PRM_ERROR_CAUSE:
                cause =  ies[i].param_data.errorCause.cause;
                break;
        }
    }

    if (dl == NULL)
    {
        SCCP_ERROR(("HandleDownERR: Missing destination reference number \n"));

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownERR:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[2] != 0)
    {
        SCCP_DEBUG(("HandleDownERR:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif
    dlref = RN_GET_REF_NUM(*dl); 
    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownERR: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownERR: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownERR: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownERR:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));

        return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/
    if (foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND)
    {
        SCCP_DEBUG(("HandleDownERR:ERR received in State %x",foundCtxt->state));

        /*Release the DSM lock */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownERR: DSM unable to free Reference.\n"));
        }

        SCCP_DEBUG(("HandleDownERR:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Notification of RLSD to Application*/
        releaseID++;

        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID--;

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);

        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);

   }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownERR:receiveInactivity timer is killed: SERIAL[%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownERR: FAIL To CANCEL receiveInactivity SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownERR:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
    
    /*Save these fields so can use after release lock on row */
    tempAssocRef = foundCtxt->assocRef;
    tempIsIntermediate = foundCtxt->isIntermediate;

    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownERR: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (tempIsIntermediate)
    {
        *sendToApp = ITS_FALSE;

        foundCtxt2 = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT, 
                                                (ITS_OCTET *)&tempAssocRef, 
                                                sizeof(tempAssocRef), &error);
        if (error != ITS_SUCCESS)
        {
            switch(error)
            {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("HandleDownERR: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("HandleDownERR: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("HandleDownERR: Can't find ConnectionReference in table.\n"));
                break;
            }

            return (ITS_ENOCONN);

        }

        RN_SET_REF_NUM(*dl, foundCtxt2->dlref);

        *mtp3 = foundCtxt2->outLabel;

        hdr->context.conref = foundCtxt2->slref;

        ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
        ies[ieCount].param_length = sizeof(MTP3_HEADER);
        ies[ieCount].param_data.routingLabel = foundCtxt2->outLabel;
        ieCount++;

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempAssocRef, 
                           sizeof(tempAssocRef), foundCtxt2);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownERR: DSM unable to free Reference.\n"));
        }

        foundCtxt2 = NULL;    /* Not safe to use with out lock */
    }

    if (!*sendToApp)
    {
        return HandleAppERR(hdr, mtp3, ies, ieCount);
    }

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_ERR))
    {
        *sendToApp = ITS_FALSE;
    }
    if (cause == SCCP_ERR_SCLASS_MIS)
    {
        *sendToApp = ITS_FALSE;
        SCCP_DEBUG(("HandleDownERR:RLSD is sent to the remote end as the error"
                    " cause is service class mismatch"));

        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);

        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_SRC_LOCAL_REF;
        ies[releaseID].param_length = sizeof(SCCP_REF_NUM);
        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RELEASE_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_REL_CAUSE);
        ies[releaseID].param_data.releaseCause.cause =
                                                  SCCP_RLC_INCONSISTENT_DATA;
        releaseID++;
        ieCount = releaseID;

        return(HandleAppRLSD(hdr, mtp3, ies, ieCount));
    }  
    else 
    {
#if defined(CONNECTION_TIMERS)
        SCCP_ERROR(("HandleDownERR:All the timers for the connection"
                     " are killed"));

        if (foundCtxt->receiveInactivity)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Receive Inactivity timer is killed: SERIAL [%d]\n",foundCtxt->receiveInactivity));
            error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Receive Inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
            }
            foundCtxt->receiveInactivity = 0;
        }

        if (foundCtxt->connectTimer)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Connect timer is killed: SERIAL [%d]\n",foundCtxt->connectTimer));
            error = TIMERS_CancelTimer(foundCtxt->connectTimer);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Connect Timer SERIAL [%d]\n",foundCtxt->connectTimer));
            }
            foundCtxt->connectTimer = 0;
        }

        if (foundCtxt->sendInactivity)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Send Inactivity timer is killed: SERIAL [%d]\n",foundCtxt->sendInactivity));
            error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Send Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
            }
            foundCtxt->sendInactivity = 0;
        }

        if (foundCtxt->releaseTimer)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Release  timer is killed: SERIAL [%d]\n",foundCtxt->releaseTimer));
            error = TIMERS_CancelTimer(foundCtxt->releaseTimer);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Release Timer SERIAL [%d]\n",foundCtxt->releaseTimer));
            }
            foundCtxt->releaseTimer = 0;
        }

        if (foundCtxt->repeatReleaseTimer)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Repeat Release timer is killed: SERIAL [%d]\n",foundCtxt->repeatReleaseTimer));
            error = TIMERS_CancelTimer(foundCtxt->repeatReleaseTimer);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Repeat Release Timer SERIAL [%d]\n",foundCtxt->repeatReleaseTimer));
            }
            foundCtxt->repeatReleaseTimer = 0;
        }

        if (foundCtxt->intervalTimer)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Interval timer is killed: SERIAL [%d]\n",foundCtxt->intervalTimer));
            error = TIMERS_CancelTimer(foundCtxt->intervalTimer);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Interval Timer SERIAL [%d]\n",foundCtxt->intervalTimer));
            }
            foundCtxt->intervalTimer = 0;
        }

        if(foundCtxt->resetTimer)
        {
            SCCP_DEBUG(("HandleDownERR:CANCEL Reset timer is killed: SERIAL [%d]\n",foundCtxt->resetTimer));
            error = TIMERS_CancelTimer(foundCtxt->resetTimer);
            if(error != ITS_SUCCESS)
            {
              SCCP_ERROR(("HandleDownERR: FAIL To CANCEL Reset Timer SERIAL [%d]\n",foundCtxt->resetTimer));
            }
            foundCtxt->resetTimer = 0;
        }
#endif
        SCCP_DEBUG(("HandleDownERR:Connection reference is cleared\n"));

        SCCP_DeleteLocalReference_ANSI(hdr->context.conref);

    }

    foundCtxt = NULL;

    return (ITS_SUCCESS);
}

/*
 * IT
 */
static int
HandleAppIT(ITS_HDR* hdr, MTP3_HEADER* mtp3,
            ITS_SCCP_IE* ies, int ieCount)
{
    SCCP_CONN_CTXT *foundCtxt;
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_ADDR local, *cdp = &local;
    int i, error;
       
    SCCP_DEBUG(("HandleAppIT\n"));

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
        case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

        case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            break;
        }
    }

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleAppIT: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleAppIT: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleAppIT: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
    *mtp3 = foundCtxt->outLabel;
     MTP3_RL_SET_SLS(mtp3->label,foundCtxt->sequenceSLS);

    local = foundCtxt->daddr;

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->sendInactivity)
    {
            SCCP_DEBUG(("HandleAppIT:CANCEL Send Inactivity timer is killed: SERIAL [%d]\n",foundCtxt->sendInactivity));
        error = TIMERS_CancelTimer(foundCtxt->sendInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleAppIT: FAIL To CANCEL Send Inactivity Timer SERIAL [%d]\n",foundCtxt->sendInactivity));
        }
        foundCtxt->sendInactivity = 0;
    }
    foundCtxt->sendInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_ias),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleAppIT:START sendInactivity: SERIAL [%d]\n",foundCtxt->sendInactivity));	 
#endif
     
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleAppIT: DSM unable to free Reference.\n"));
    }

    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (gcsMessageBasedRedundancyIsActive)
    {
        ITS_EVENT dummyEvent;
        ITS_UINT  dest;

        SCCP_DEBUG(("GCS Message Based Redundancy is ACTIVE\n"));

        dummyEvent.src  = ITS_GCS_EVENT_TO_NETWORK;
        dummyEvent.data = 0;

        dest = ROUTE_SelectApplication(hdr, &dummyEvent, ITS_TRUE);

        if (dest == ITS_NO_SRC || dest == ITS_INVALID_SRC)
        {
            /* Don't send message for routing to the network */
            SCCP_WARNING(("Message is consumed by SCCP: ctxt = 0x%x\n",
                          hdr->context.conref));
            return ITS_SUCCESS;
        }

    }

    SCCP_DEBUG(("Sending message to Network: ctxt = 0x%x  $$$\n",
                 hdr->context.conref));

    return SCRCHandleSCOCMsg_ANSI(mtp3, SCCP_MSG_IT, ies, ieCount, cdp);
}

static int
HandleDownIT(ITS_HDR* hdr, MTP3_HEADER* mtp3,
             ITS_SCCP_IE* ies, int ieCount, ITS_BOOLEAN* sendToApp)
{
    ITS_UINT dlref;
/*Patch:Itika :4-oct-10:Fix for incorrect slr recv in IT from peer*/
    ITS_UINT slref;
/*Patch:Itika :4-oct-10:Fix end*/
    SCCP_REF_NUM *sl = NULL, *dl = NULL;
    SCCP_CONN_CTXT *foundCtxt;
    ITS_OCTET pclass = 0;
    ITS_OCTET creditvalue = 0;
    int i, error;
    int releaseID = 0;

    SCCP_DEBUG(("HandleDownIT\n"));

    *sendToApp = ITS_FALSE;

    /* get some IEs we need */
    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
         case SCCP_PRM_SRC_LOCAL_REF:
            sl = &ies[i].param_data.sourceLocalReference;
            break;

         case SCCP_PRM_DEST_LOCAL_REF:
            dl = &ies[i].param_data.destinationLocalReference;
            releaseID = i;
            break;
        
         case SCCP_PRM_PROTOCOL_CLASS:
            pclass = ies[i].param_data.protocolClass.pclass;
            break;
          
         case SCCP_PRM_CREDIT:
            creditvalue = ies[i].param_data.credit.win_size;
            break;
        }
    }

/*Patch:Itika :4-oct-10:Fix for incorrect slr recv in IT from peer*/
    if ((dl == NULL) || (sl == NULL))
/*Patch:Itika :4-oct-10:Fix end*/
    {
        SCCP_ERROR(("HandleDownIT:Missing either SLR or DLR  number \n"));

        /* Incoming Message - Discarding Message - Missing Mandatory 
           Parameter. */

        return (ITS_EMISSMAND);
    }
/*ASHUTOSH
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownIT:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
        return (ITS_EMISSMAND);
    }
#endif

*/
#ifndef NEED_LARGE_CONTEXT
    if (dl->refno[0] != 0)
    {
        SCCP_DEBUG(("HandleDownIT:DLR is received is not  proper from remote\n"));
        return (ITS_EMISSMAND);
    }
#endif

    dlref = RN_GET_REF_NUM(*dl); 
/*Patch:Itika :4-oct-10:Fix for incorrect slr recv in IT from peer*/
    slref = RN_GET_REF_NUM(*sl); 
/*Patch:Itika :4-oct-10:Fix end*/

    hdr->context.conref = (ITS_CTXT)dlref;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr->context.conref,
                                           sizeof(hdr->context.conref), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("HandleDownIT: Couldn't acquire mutex.\n"));
            break;
        case (ITS_EINUSE):
            SCCP_ERROR(("HandleDownIT: DSM Row Locked.\n"));
            break;
        case (ITS_ENOTFOUND):
            SCCP_ERROR(("HandleDownIT: Can't find ConnectionReference in table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }
/*Patch:Itika :4-oct-10:Fix opc & dpc in routing label in IT from peer*/
    if (MTP3_RL_GET_DPC_VALUE(foundCtxt->outLabel.label)!=
        MTP3_RL_GET_OPC_VALUE(mtp3->label))
    {
        SCCP_ERROR(("HandleDownIT:Orignating Point Code received not equal to\
                     the Pc stored locally hence the msg is discarded\n"));
        SendERR(foundCtxt, SCCP_ERR_PC_MISMATCH, ITS_FALSE);
        
        NotifyERRToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_ERR_PC_MISMATCH);
        *sendToApp = ITS_FALSE;
       
         return(ITS_EINVALIDARGS);
    }
/*Patch:Itika :4-oct-10:Fix end*/
    if (((( pclass & SCCP_PCLASS_MASK) != foundCtxt->pclass)
      //  || (dlref != foundCtxt->slref))
/*Patch:Itika :4-oct-10:Fix for incorrect slr recv in IT from peer*/
/*Comparing the SLR in IT message with DLR stored locally*/
        || (slref != foundCtxt->dlref))
/*Patch:Itika :4-oct-10:Fix end*/
        ||(foundCtxt->state == SCCP_CONN_IN_PEND
        || foundCtxt->state == SCCP_CONN_OUT_PEND
        || foundCtxt->state == SCCP_IN_RELEASE_PEND))
    {
        /* Protocol class missmatching so RLSD is send for the connection*/

        SCCP_DEBUG(("HandleDownIT:Protocol class or Source reference number"
                    " missmatch  or state %x is invalid\n",foundCtxt->state));

        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&hdr->context.conref,
                           sizeof(hdr->context.conref), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));

        }
        SCCP_DEBUG(("HandleDownIT:Notification for RLSD is sent to app and"
                    "RLSD is sent to remote\n"));

        SendRLSD(foundCtxt, SCCP_RLC_INCONSISTENT_DATA , ITS_FALSE);

        /*Notification of RLSD to Application*/

        NotifyRLSDToApp(hdr->context.conref, mtp3, ies, releaseID,
                       SCCP_RLC_INCONSISTENT_DATA);
        foundCtxt = NULL;
        *sendToApp = ITS_FALSE;

        return(ITS_EBADSTATE);
     
    }

#if defined(CONNECTION_TIMERS)
    if (foundCtxt->receiveInactivity)
    {
            SCCP_DEBUG(("HandleDownIT:CANCEL Receive  Inactivity timer is killed: SERIAL [%d]\n",foundCtxt->receiveInactivity));
        error = TIMERS_CancelTimer(foundCtxt->receiveInactivity);
        if(error != ITS_SUCCESS)
        {
           SCCP_ERROR(("HandleDownIT: FAIL To CANCEL Receive  Inactivity Timer SERIAL [%d]\n",foundCtxt->receiveInactivity));
        }
        foundCtxt->receiveInactivity = 0;
    }
    foundCtxt->receiveInactivity =
        TIMERS_StartSharedTimer(ITS_SCCP_ANSI_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_iar),
                                foundCtxt, sizeof(SCCP_CONN_CTXT));
       SCCP_DEBUG(("HandleDownIT:START receiveInactivity: SERIAL [%d]\n",foundCtxt->receiveInactivity));	 
#endif
    
    /* Release the lock on row */
    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr->context.conref, 
                       sizeof(hdr->context.conref), foundCtxt);
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("HandleDownIT: DSM unable to free Reference.\n"));
    }
    if (creditvalue != foundCtxt->windowSize) 
    {
        SCCP_DEBUG(("HandleDownIT:Credit value missmatch so RSR is send\n"));


        RN_SET_REF_NUM(ies[releaseID].param_data.destinationLocalReference,
                       foundCtxt->dlref);
        releaseID++;
        RN_SET_REF_NUM(ies[releaseID].param_data.sourceLocalReference,
                       foundCtxt->slref);
        releaseID++;

        ies[releaseID].param_id = SCCP_PRM_RESET_CAUSE;
        ies[releaseID].param_length = sizeof(SCCP_RES_CAUSE);
        ies[releaseID].param_data.resetCause.cause =SCCP_RES_NETWORK_OP;

        releaseID++;
        ieCount = releaseID;
        
        if(HandleAppRSR(hdr, mtp3, ies, ieCount)!=ITS_SUCCESS)
        {
            SCCP_ERROR(("HandleDownIT:Error in sending RSR to the "
                         "other end\n"));
            return(ITS_ENOMSG);
        }
    }


    foundCtxt = NULL;    /* Not safe to use with out lock */

    if (!BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors, SCCP_B_propagate_IT))
    {
        *sendToApp = ITS_FALSE;
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0576            Sending CREF by swaping the
 *                                                MTP3 Routing Lable.
 *  csireesh   06-05-2005  Bug ID:1801, 1802      Sending CREF if DSM Find failed 
 *                                                in Invalied Connection State.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SCOCHandleRoutingFailure_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                              ITS_SCCP_IE* ies, int ieCount,
                              ITS_OCTET reason)
{
    ITS_INT opc, dpc;
    ITS_OCTET sls;
    SCCP_CONN_CTXT *foundCtxt = NULL;
    SCCP_REF_NUM *sl = NULL;
    SCCP_REF_NUM *dl = NULL;
    int error, i;
    ITS_HDR hdr;
    ITS_BOOLEAN toApp = ITS_FALSE;
    ITS_OCTET ni = MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK;
    SCCP_ADDR *cgp = NULL;

    SCCP_DEBUG(("SCOCHandleRoutingFailure:\n"));

    /* INCR Number of Routing Failures */
    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_ROUTING_FAILURE);

    opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    sls = MTP3_RL_GET_SLS(mtp3->label);

    if (mType == SCCP_MSG_RLC || mType == SCCP_MSG_CREF)
    {
        SCCP_DEBUG(("SCOCHandleRoutingFailure: Drop the message\n")); 

        return (ITS_SUCCESS);
    } 

    if (SCCP_IsSSNEquipped(ni, opc, SCCP_SSN_SCCPMGMT))
    {
        toApp = ITS_TRUE;
        SCCP_DEBUG(("SCOCHandleRoutingFailure: for local\n"));
    }
    else if (SCCP_IsSSNEquipped(ni, dpc, SCCP_SSN_SCCPMGMT))
    {
        toApp = ITS_FALSE;
        SCCP_DEBUG(("SCOCHandleRoutingFailure: for remote\n"));
    }
    else
    {
        /* Not much we can do - bail out */
        return ITS_SUCCESS;
    }

    for (i = 0; i < ieCount; i++)
    {
        switch (ies[i].param_id)
        {
            case SCCP_PRM_SRC_LOCAL_REF:
                sl = &ies[i].param_data.sourceLocalReference;
                break;

            case SCCP_PRM_DEST_LOCAL_REF:
                dl = &ies[i].param_data.destinationLocalReference;
                break;

            case SCCP_PRM_CALLING_PARTY_ADDR:
                cgp = &ies[i].param_data.callingPartyAddr;
                break;

        }
    }

    hdr.type = ITS_SCCP;

    if (toApp)  
    {
        if (sl)
        {
            hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*sl);
        }
    }
    else
    {
        if (dl)
        {
            hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*dl);
        }
        else
        {
            hdr.context.conref = (ITS_CTXT)RN_GET_REF_NUM(*sl);
            sendConnectionRefuse(mtp3, hdr.context.conref, cgp); 
            return (ITS_ENOCONN);
        }
    }
       
    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT,
                                           (ITS_OCTET *)&hdr.context.conref,
                                           sizeof(hdr.context.conref), &error);
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            SCCP_CRITICAL(("SCOCHandleRoutingFailure: Couldn't acquire DSM Row "
                           "mutex.\n"));
            break;

        case (ITS_EINUSE):
            SCCP_ERROR(("SCOCHandleRoutingFailure: DSM Row Locked.\n"));
            break;

        case (ITS_ENOTFOUND):
            sendConnectionRefuse(mtp3, hdr.context.conref, cgp); 
            SCCP_ERROR(("SCOCHandleRoutingFailure: Can't find "
                        "ConnectionReference in DSM table.\n"));
            break;
        }

        return (ITS_ENOCONN);
    }

    error = DSM_Commit(DSM_SccpFtGroupId,
                       DSM_TABLE_ANSI_SCCP_CTXT,
                       (ITS_OCTET *)&hdr.context.conref,
                       sizeof(hdr.context.conref), foundCtxt);

    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCOCHandleRoutingFailure: DSM unable to Commit"
                    "Reference in order to Release Lock.\n"));
    }

    switch (mType)
    {
        case SCCP_MSG_CR:
            SendCREF(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: CREF sent\n"));
            break;

        case SCCP_MSG_RLSD:
            SendRLC(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: RLC sent\n"));
            break;

        case SCCP_MSG_CC:
        case SCCP_MSG_DT1:
            if (toApp)
            {   
                /* To send back to app, fake it from remote */
                MTP3_POINT_CODE tmp, tmp2;

                MTP3_RL_GET_OPC(foundCtxt->outLabel.label, tmp);
                MTP3_RL_GET_DPC(foundCtxt->outLabel.label, tmp2);
                MTP3_RL_SET_OPC(foundCtxt->outLabel.label, tmp2);
                MTP3_RL_SET_DPC(foundCtxt->outLabel.label, tmp);
            }

            SendRLSD(foundCtxt, SCCP_REF_DEST_UNAVAIL, toApp);
            SCCP_DEBUG(("SCOCHandleRoutingFailure: RLSD sent\n"));
            break;
    }

    foundCtxt = NULL;

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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SCOCHandleAPPMsg_ANSI(ITS_EVENT *event)
{
    MTP3_HEADER localStore, *mtp3 = &localStore;
    ITS_SCCP_IE ies[32];
    ITS_HDR hdr;
    int ieCount, ret;
     ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);
/*change for redudnancy*/ 
     if (redunClass)
           {
             if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
             {
                SCCP_ERROR(("Backup Node Cannot Initiate Messages.\n"));
                return (ITS_EINVINITSTATE);
             }
           }
/*change for redudnancy*/ 


    hdr.type = ITS_SCCP;
    hdr.context.conref = ITS_GET_CTXT(&event->data[1]);
    PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_USER_MSG_SENT);

    /* process based on type */
    switch (SCCP_MSG_TYPE(event))
    {
    case SCCP_MSG_CR:
        PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_USER_CR_SENT);
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_CR_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppCR(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_CC:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_CC_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppCC(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_CREF:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_CREF_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppCREF(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_RLSD:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_INITIATED_RLS);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_RLSD_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppRLSD(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_RLC:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_RLC_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppRLC(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_DT1:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_DT1_SENT);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_DT1_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppDT1(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_DT2:
        PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_USER_DT2_SENT);
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_DT2_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppDT2(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_AK:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_AK_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppAK(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_ED:
        PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_USER_ED_SENT);
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_ED_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppED(&hdr, mtp3, ies, ieCount);
    
    case SCCP_MSG_EA:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_EA_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppEA(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_RSR:
        PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_USER_INITITATED_RESET);

        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_RSR_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppRSR(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_RSC:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_RSC_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppRSC(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_ERR:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_ERR_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppERR(&hdr, mtp3, ies, ieCount);

    case SCCP_MSG_IT:
        if ((ret = SCCP_Decode_ANSI(ies, &ieCount, event,
                                    &SCCP_IT_Desc_ANSI)) != ITS_SUCCESS)
        {
            return (ret);
        }

        return HandleAppIT(&hdr, mtp3, ies, ieCount);

    default:
        SCCP_ERROR(("SCOCHandleAPPMsg_ANSI: Invalid msg type.\n"));


        return (ITS_ENOCONN);
    }
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
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
SCOCHandleSCRCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount,
                       ITS_UINT pc, ITS_OCTET ssn, ITS_BOOLEAN needCouple)
{
    ITS_HDR hdr;
    ITS_EVENT event;
    int ret = ITS_EINVALIDARGS;
    ITS_BOOLEAN sendToApp = ITS_TRUE;

    PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_REMOTE_MSG_RECEIVED);

    /* process based on type */
    switch (mType)
    {
    case SCCP_MSG_CR:
        ret = HandleDownCR(&hdr, mtp3, ies, ieCount, pc, ssn, needCouple);

        if (needCouple)
        {
            return (ret);
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_CR_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_CC:
        ret = HandleDownCC(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_CC_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_CREF:
        ret = HandleDownCREF(&hdr, mtp3, ies, ieCount, &sendToApp,&ssn);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_CREF_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
            return ret;
        }
        break;

    case SCCP_MSG_RLSD:
        ret = HandleDownRLSD(&hdr, mtp3, ies, ieCount, &sendToApp,&ssn);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_RLSD_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
            return ret;
        }
        break;

    case SCCP_MSG_RLC:
        ret = HandleDownRLC(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_RLC_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_DT1:
        ret = HandleDownDT1(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_DT1_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_DT2:
        ret = HandleDownDT2(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_DT2_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_AK:
        ret = HandleDownAK(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_AK_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_ED:
        ret = HandleDownED(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_ED_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));
            SCCP_Alarm_ANSI(667, __FILE__, __LINE__, NULL);

            return ret;
        }
        break;

    case SCCP_MSG_EA:
        ret = HandleDownEA(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_EA_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_RSR:
        ret = HandleDownRSR(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_RSR_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_RSC:
        ret = HandleDownRSC(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_RSC_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_ERR:
        ret = HandleDownERR(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_ERR_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    case SCCP_MSG_IT:
        ret = HandleDownIT(&hdr, mtp3, ies, ieCount, &sendToApp);

        if (!sendToApp)
        {
            return ret;
        }

        if (ret == ITS_SUCCESS)
        {
            ies[ieCount].param_id = SCCP_PRM_ROUTING_LABEL;
            ies[ieCount].param_length = sizeof(MTP3_HEADER);
            ies[ieCount].param_data.routingLabel = *mtp3;
            ieCount++;

            ret = SCCP_Encode_ANSI(ies, ieCount, mType, &event, &hdr,
                                   &SCCP_IT_Desc_ANSI);
        }
        else
        {
            SCCP_ERROR(("HandleSCRCMsg: Couldn't process message\n"));

            return ret;
        }
        break;

    default:
        SCCP_ERROR(("SCOCHandleSCRCMsg: Discard unknown type\n"));
        break;
    }

    if (ret != ITS_SUCCESS)
    {
        /* Incoming Message - Discarding Message - Invalid or Corrupted */

        return ret;
    }

    hdr.type = ITS_SCCP;

    event.src = ITS_SCCP_ANSI_SRC;
    ITS_SET_CTXT(&event.data[1], hdr.context.conref);

    /* send to the application */
    ret = SCCP_SendToAPP(mtp3, &hdr, mType, &event,ssn);

    ITS_EVENT_TERM(&event);

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
int
SCOCHandleTimer_ANSI(ITS_TimerData* td)
{
    SCCP_CONN_CTXT copyCtxt, *foundCtxt = NULL;
    ITS_CTXT        tempConnRef;
    int error;
    int isDel = 0;

    memcpy(&copyCtxt, td->context, sizeof(SCCP_CONN_CTXT));
    tempConnRef = copyCtxt.connRef;

    foundCtxt = (SCCP_CONN_CTXT *)DSM_Find(DSM_SccpFtGroupId,
                                           DSM_TABLE_ANSI_SCCP_CTXT, 
                                           (ITS_OCTET *)&tempConnRef, 
                                           sizeof(tempConnRef), &error);

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
            case (ITS_EBADMUTEX):
                SCCP_CRITICAL(("SCOCHandleTimer_ANSI: Couldn't acquire mutex.\n"));
                break;
            case (ITS_EINUSE):
                SCCP_ERROR(("SCOCHandleTimer_ANSI: DSM Row Locked.\n"));
                break;
            case (ITS_ENOTFOUND):
                SCCP_ERROR(("SCOCHandleTimer_ANSI: Can't find ConnectionReference in table.\n"));
                break;
        }

        return (ITS_ENOCONN);
    }


    copyCtxt = *foundCtxt;
    if((copyCtxt.state != SCCP_CONN_OUT_PEND) &&
       (copyCtxt.state != SCCP_CONN_IN_PEND) &&
       (copyCtxt.state != SCCP_OUT_RESET_PEND) &&
       (copyCtxt.state != SCCP_IN_RESET_PEND) &&
       (copyCtxt.state != SCCP_OUT_RELEASE_PEND) &&
       (copyCtxt.state != SCCP_IN_RELEASE_PEND))
    {
       if (td->serial == copyCtxt.sendInactivity)
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: Send Inactivity :Setting Serial zero"));
         foundCtxt->sendInactivity = 0;
       }
       else if (td->serial == copyCtxt.receiveInactivity) 
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: Receive Inactivity :Setting Serial zero"));
         foundCtxt->receiveInactivity = 0;
       }
       else if (td->serial == copyCtxt.releaseTimer)
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: ReleaseTimer :Setting Serial zero"));
         foundCtxt->releaseTimer = 0;
       }
       else if (td->serial == copyCtxt.repeatReleaseTimer)
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: Repeat ReleaseTimer :Setting Serial zero"));
         foundCtxt->repeatReleaseTimer = 0;
       }
       else if (td->serial == copyCtxt.intervalTimer)
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: Interval Timer :Setting Serial zero"));
         foundCtxt->intervalTimer = 0;
       }
       else
       {
         SCCP_DEBUG(("SCOCHandleTimer_ANSI: Unknown timer:SERIAL[%d]",td->serial));
       }
    } 

    switch (copyCtxt.state)
    {
        case SCCP_CONN_OUT_PEND:
        case SCCP_CONN_IN_PEND:
            SCCP_ERROR(("HandleTIMER: Connection segment expired: ref %04x\n",
                        copyCtxt.connRef));

            /* Message - Inbound or Outbound Message Segment not received within time limit. */

            /* send CREF to originator */
            if (copyCtxt.state == SCCP_CONN_IN_PEND)
            {
                SendCREF(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_FALSE);
            }
            else if (copyCtxt.state == SCCP_CONN_OUT_PEND)
            {
                SendCREF(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_TRUE);
            }
    
            SCCP_DeleteLocalReference_ANSI(copyCtxt.connRef);
            break;
    
        case SCCP_OUT_RESET_PEND:
        case SCCP_IN_RESET_PEND:
            SCCP_ERROR(("HandleTIMER: Reset expired: ref %04x\n",
                        copyCtxt.connRef));

            SCCP_DEBUG(("On expiry of Reset Timer RLSD is send \
                         to the other end\n")); 

            SendRLSD(&copyCtxt,SCCP_REF_CONN_EXPIRY, ITS_FALSE);
            break;

        case SCCP_OUT_RELEASE_PEND:
        case SCCP_IN_RELEASE_PEND:

            SCCP_ERROR(("HandleTIMER: Release expired: ref %04x serial %08x\n",
                        copyCtxt.connRef, td->serial));
            /* SCCP Context - Inbound or Outbound Release timer expired - Sending Release Complete. */

            /* delete local context, send RLC to originator */
            if (copyCtxt.state == SCCP_IN_RELEASE_PEND)
            {
                SendRLC(&copyCtxt, SCCP_REF_CONN_EXPIRY, ITS_FALSE);
                SCCP_DeleteLocalReference_ANSI(copyCtxt.connRef);
            }
            else if (copyCtxt.state == SCCP_OUT_RELEASE_PEND)
            {
                if (td->serial == copyCtxt.releaseTimer)
                {
                    SCCP_DEBUG(("SCOCHandleTimer_ANSI: Release Timer Expired : ref %04x serial %08x\n",
                          copyCtxt.connRef, td->serial));
#if defined(CONNECTION_TIMERS)
                    if(foundCtxt->repeatReleaseTimer)
                    {
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:RepeatReleaseTimer  is killed:SERIAL[%d]\n",foundCtxt->repeatReleaseTimer));
                       error = TIMERS_CancelTimer(foundCtxt->repeatReleaseTimer);
                       if(error != ITS_SUCCESS)
                       {
                          SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL RepeatReleaseTimer  SERIAL [%d]\n",foundCtxt->receiveInactivity));
                       }
                       foundCtxt->repeatReleaseTimer = 0;
                    }
                    foundCtxt->repeatReleaseTimer =
                        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:RepeatReleaseTimer  is STARTED :SERIAL[%d]\n",foundCtxt->repeatReleaseTimer));
                    if(foundCtxt->intervalTimer)
                    {
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:IntervalTimer  is killed:SERIAL[%d]\n",foundCtxt->intervalTimer));
                       error = TIMERS_CancelTimer(foundCtxt->intervalTimer);
                       if(error != ITS_SUCCESS)
                       {
                          SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL IntervalTimer Timer SERIAL [%d]\n",foundCtxt->intervalTimer));
                       }
                       foundCtxt->intervalTimer = 0;
                    }

                    foundCtxt->intervalTimer =
                        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_interval),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:IntervalTimer  is STARTED:SERIAL[%d]\n",foundCtxt->intervalTimer));
#endif

                    SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
                }
                else if (td->serial == copyCtxt.repeatReleaseTimer)
                {
                    SCCP_DEBUG(("SCOCHandleTimer_ANSI: Repeat Release Timer Expired : ref %04x serial %08x\n",
                          copyCtxt.connRef, td->serial));

#if defined(CONNECTION_TIMERS)
                    foundCtxt->repeatReleaseTimer =
                        TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:repeatReleaseTimer  is STARTED:SERIAL[%d]\n",foundCtxt->repeatReleaseTimer));
#endif
                    SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
                }
                else if (td->serial == copyCtxt.intervalTimer)
                {
                    SCCP_DEBUG(("SCOCHandleTimer_ANSI: Interval Timer Expired : ref %04x serial %08x\n",
                          copyCtxt.connRef, td->serial));
                    if (copyCtxt.repeatReleaseTimer)
                    {
                        error = TIMERS_CancelTimer(copyCtxt.repeatReleaseTimer);
                       if(error != ITS_SUCCESS)
                       {
                          SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL repeatReleaseTimer SERIAL [%d]\n",copyCtxt.repeatReleaseTimer));
                       }
                       copyCtxt.repeatReleaseTimer = 0;
                    }

                    /* Release the lock on row */
                    error = DSM_Commit(DSM_SccpFtGroupId,
                                       DSM_TABLE_ANSI_SCCP_CTXT,
                                       (ITS_OCTET *)&tempConnRef,
                                       sizeof(tempConnRef), foundCtxt);
                    if (error != ITS_SUCCESS)
                    {
                        SCCP_ERROR(("SCOCHandleTimer_ANSI: DSM unable to free Reference.\n"));
                    }

                    foundCtxt = NULL;    /* Not safe to use with out lock */

                    SCCP_DeleteLocalReference_ANSI(copyCtxt.connRef);
                    isDel = 1;
                }
                else
                {
                    SCCP_DEBUG(("Unknown timer: ref %04x serial %08x\n",
                              copyCtxt.connRef, td->serial));
                }
            }

            break;

        default:
            if (td->serial == copyCtxt.sendInactivity)
            {
                SCCP_DEBUG(("SendInactivity: ref %04x\n",
                              copyCtxt.connRef));
                /* send inactivity */
                SendIT(&copyCtxt);
            }
            else if (td->serial == copyCtxt.receiveInactivity)
            {
                 SCCP_DEBUG(("RecieveInactivity: ref %04x\n",
                              copyCtxt.connRef));
                /* receive inactivity */
                /* should release connection on this. */

                 SCCP_DEBUG(("SCOCHandleTimer_ANSI:Released send to MTP3\n"));
                 PEG_IncrPeg(ANSI_SCCP_Pegs, PEG_SCCP_TIMER_TIAR_EXPIRY);

                 SendRLSD(&copyCtxt, SCCP_RLC_INACT_EXPIRY,ITS_FALSE);
            }
            else if (td->serial == copyCtxt.releaseTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_ANSI: Release Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

#if defined(CONNECTION_TIMERS)
                 if(copyCtxt.repeatReleaseTimer)
                 {
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:CANCEL RepeatReleaseTimer timer is killed :SERIAL [%d] \n",copyCtxt.repeatReleaseTimer));
                       error = TIMERS_CancelTimer(copyCtxt.repeatReleaseTimer);
                       if(error != ITS_SUCCESS)
                       {
                          SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL RepeatReleaseTimer Timer SERIAL [%d]\n",copyCtxt.repeatReleaseTimer));
                       }
                       copyCtxt.repeatReleaseTimer = 0;
                 }
 
                copyCtxt.repeatReleaseTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:repeatReleaseTimer  is STARTED:SERIAL[%d]\n",copyCtxt.repeatReleaseTimer));

                 if(copyCtxt.intervalTimer)
                 {
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:CANCEL IntervalTimer is killed:SERIAL [%d] \n",copyCtxt.intervalTimer));
                       error = TIMERS_CancelTimer(copyCtxt.intervalTimer);
                       if(error != ITS_SUCCESS)
                       {
                          SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL Interval Timer SERIAL [%d]\n",copyCtxt.intervalTimer));
                       }
                       copyCtxt.intervalTimer = 0;
                 }
                copyCtxt.intervalTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_interval),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:intervalTimer  is STARTED:SERIAL[%d]\n",copyCtxt.repeatReleaseTimer));
#endif
                SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
            }
            else if (td->serial == copyCtxt.repeatReleaseTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_ANSI: Repeat Release Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

#if defined(CONNECTION_TIMERS)
                copyCtxt.repeatReleaseTimer =
                    TIMERS_StartSharedTimer(ITS_SCCP_SRC,
                                TIMERS_GetTimerValue(&ANSI_SCCP_Timers,
                                                     SCCP_T_repeatRelease),
                                &copyCtxt, sizeof(SCCP_CONN_CTXT));
                       SCCP_DEBUG(("SCOCHandleTimer_ANSI:repeatReleaseTimer  is STARTED:SERIAL[%d]\n",copyCtxt.repeatReleaseTimer));
#endif
                SendRLSD(&copyCtxt, SCCP_RLC_RPC_ERROR,ITS_FALSE);
            }
            else if (td->serial == copyCtxt.intervalTimer)
            {
                SCCP_DEBUG(("SCOCHandleTimer_ANSI: Interval Timer Expired : ref %04x\n",
                          copyCtxt.connRef));

                if (copyCtxt.repeatReleaseTimer)
                {
                    SCCP_DEBUG(("SCOCHandleTimer_ANSI:CANCEL Repeat Release timer is killed: SERIAL [%d]\n",copyCtxt.repeatReleaseTimer));
                    error = TIMERS_CancelTimer(copyCtxt.repeatReleaseTimer);
                    if(error != ITS_SUCCESS)
                    {
                       SCCP_ERROR(("SCOCHandleTimer_ANSI: FAIL To CANCEL repeatReleaseTimer SERIAL [%d]\n",copyCtxt.repeatReleaseTimer));
                    }
                    copyCtxt.repeatReleaseTimer = 0;
                }

                SCCP_DeleteLocalReference_ANSI(copyCtxt.connRef);
            } 
            else
            {
                SCCP_DEBUG(("Unknown timer: ref %04x serial %08x\n",
                              copyCtxt.connRef, td->serial));
            }
            break;
    }

    if (!isDel)
    {
        /* Release the lock on row */
        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&tempConnRef,
                           sizeof(tempConnRef), foundCtxt);
        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCOCHandleTimer_ANSI: DSM unable to free Reference.\n"));
        }

        foundCtxt = NULL;    /* Not safe to use with out lock */
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
SCOC_PutDataInFragList(ITS_UINT *startKey, ITS_UINT segRefNum, ITS_OCTET *data, 
                  ITS_OCTET len)
{
    SCCP_DATA_FRAG* fptr;  
    int size = sizeof(SCCP_DATA_FRAG);
    int error;
    int key = *startKey;
  
   SCCP_ERROR(("Key %x",startKey));    
   SCCP_ERROR(("Key %d",*startKey));    
    if(*startKey == 0)
    {
        *startKey = segRefNum | 0x80000000;
        key = *startKey;

        fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                          DSM_TABLE_ANSI_SCCP_CTXT,
                                          (ITS_OCTET *)&key, 
                                          sizeof(key), &error);

        if (error != ITS_ENOTFOUND && (error != ITS_SUCCESS))
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));

            /* Segmention Fragment already in use in CTXT Table. */
    
            return (ITS_ENOMEM);
        }

        if (error == ITS_ENOTFOUND)
        {

            fptr = (SCCP_DATA_FRAG *) DSM_Alloc(DSM_SccpFtGroupId,
                                                DSM_TABLE_ANSI_SCCP_CTXT,
                                                (ITS_OCTET *)&key, 
                                                sizeof(key), size, 
                                                &error);

            if (error != ITS_SUCCESS)
            {
                switch(error)
                {
                    case (ITS_EBADMUTEX):
                        SCCP_CRITICAL(("GetNextLocalRef: Couldn't acquire"
                                       " mutex.\n"));
                        break;
                    case (ITS_ENOMEM):
                        SCCP_CRITICAL(("GetNextLocalRef: No Memory.\n"));
                        break;
                }

                /* Unable to Allocate Memory for Segmention Fragment in CTXT 
                   Table. */

                return (error);
            }
        }
        SCCP_ERROR(("::::::fraglen %d\n",len )); 
        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&key, 
                           sizeof(key), fptr);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

            /* Unable to Commit Segmention Fragment to CTXT Table. */

            return (error);
        }
    }
    else
    {
        fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                          DSM_TABLE_ANSI_SCCP_CTXT,
                                          (ITS_OCTET *)&key, 
                                          sizeof(key), &error);

        if (error == ITS_ENOTFOUND)
        {
            SCCP_CRITICAL(("PutDataInFragList: Couldn't alloc segment.\n"));
    
            /* Segmention Fragment not found in CTXT Table.*/

            return (ITS_ENOMEM);
        }
       SCCP_ERROR(("fraglen %d\n",len ));
        memcpy(&(fptr->data[fptr->len]), data, len);
        fptr->len += len;

        error = DSM_Commit(DSM_SccpFtGroupId,
                           DSM_TABLE_ANSI_SCCP_CTXT,
                           (ITS_OCTET *)&key, 
                           sizeof(key), fptr);

        if (error != ITS_SUCCESS)
        {
            SCCP_ERROR(("PutDataInFragList: Couldn't add context.\n"));

            /* Unable to Commit Segmention Fragment to CTXT Table. */

            return (error);
        }
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
int
SCOC_GetDataFromFragList(ITS_OCTET *data, ITS_UINT *startKey)
{
    SCCP_DATA_FRAG* fptr;
    int error;

    fptr = (SCCP_DATA_FRAG *)DSM_Find(DSM_SccpFtGroupId,
                                      DSM_TABLE_ANSI_SCCP_CTXT,
                                      (ITS_OCTET *)startKey, 
                                      sizeof(startKey), &error);

    if (error == ITS_ENOTFOUND)
    {
        SCCP_CRITICAL(("GetDataInFragList: Couldn't alloc segment.\n"));

        /* Segmention Fragment not found in CTXT Table. */

        return (ITS_ENOMEM);
    }

    memcpy(data, fptr->data, fptr->len);

    error = DSM_Free(DSM_SccpFtGroupId,
                     DSM_TABLE_ANSI_SCCP_CTXT, 
                     (ITS_OCTET *)startKey,
                     sizeof(startKey), fptr);

    *startKey = 0;
    if (error != ITS_SUCCESS)
    {
        SCCP_ERROR(("GetDataFromFragList: DSM unable to free Segment.\n"));

        /* Unable to Free Segment Reference in CTXT Table. */
    }
    
    return ITS_SUCCESS;
}
