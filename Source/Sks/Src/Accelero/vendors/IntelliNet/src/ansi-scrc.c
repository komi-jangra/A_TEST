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
 *  ID: $Id: ansi-scrc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
 *
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
 * LOG: Revision 9.5  2005/06/02 12:29:51  adutta
 * LOG: Fixed issue# 1919
 * LOG:
 * LOG: Revision 9.4  2005/04/29 12:35:08  ssingh
 * LOG: Revision 9.2 is taken back as breaking ACTIVE-ACTIVE redundancy.
 * LOG:
 * LOG: Revision 9.3  2005/04/06 11:26:23  mmanikandan
 * LOG: Bug Propagation and Validation bug Fix.
 * LOG:
 * LOG: Revision 9.2  2005/04/01 10:29:33  ssingh
 * LOG: Bug Fix Propagation to PR6.5, Bug# 817
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:32  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.7  2005/03/21 13:53:35  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.4.2.3.4.2  2004/12/29 13:41:17  csireesh
 * LOG: SCCP bug propogation and OAM Changes
 * LOG:
 * LOG: Revision 7.6.2.4.2.3.4.1  2004/12/07 11:47:18  mmanikandan
 * LOG: Bug in Event Dump.
 * LOG:
 * LOG: Revision 7.6.2.4.2.3  2004/11/22 12:45:35  yranade
 * LOG: Printing Hex Dumps change done by Abhijit.
 * LOG:
 * LOG: Revision 7.6.2.4.2.2  2004/09/02 11:55:55  csireesh
 * LOG: Validation Bug Fixes for Alarms, Pegs and MML commands.
 * LOG:
 * LOG: Revision 7.6.2.4.2.1  2004/06/22 11:47:52  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.6.2.4  2003/10/17 19:36:27  hcho
 * LOG: Handled SCOC routing failure to the user.
 * LOG:
 * LOG: Revision 7.6.2.3  2003/09/18 11:13:42  aganguly
 * LOG: fix for SCCP-CO bugs
 * LOG:
 * LOG: Revision 7.6.2.2  2003/03/17 10:23:34  aganguly
 * LOG: Check for Protocol Class added - aganguly
 * LOG:
 * LOG: Revision 7.6.2.1  2003/02/25 11:17:59  asingh
 * LOG: Changed SSN to 1 in the function SCRCHandleSCLCMsg_ANSI to correctly route SCMG msgs to CPC
 * LOG:
 * LOG: Revision 7.6  2003/02/03 10:56:39  aganguly
 * LOG: more alarm changes after code review
 * LOG:
 * LOG: Revision 7.5  2003/02/03 07:41:56  aganguly
 * LOG: Changes for SCCP Alarms: Clean up of unwanted alarms left for Release 6.4
 * LOG:
 * LOG: Revision 7.4  2002/12/16 18:12:12  ngoel
 * LOG: use ssn=1 for sst routing
 * LOG:
 * LOG: Revision 7.3  2002/11/09 22:02:25  randresol
 * LOG: Do not invoke ITS_EVENT_TERM when message is passed to our MTP3
 * LOG:
 * LOG: Revision 7.2  2002/10/15 19:43:07  omayor
 * LOG: loadsharing bug
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.9  2002/07/29 18:07:20  ngoel
 * LOG: increment total message peg
 * LOG:
 * LOG: Revision 6.8  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.7  2002/06/20 16:42:22  mmiers
 * LOG: spell it right
 * LOG:
 * LOG: Revision 6.6  2002/06/20 16:41:10  mmiers
 * LOG: hop counter detection
 * LOG:
 * LOG: Revision 6.5  2002/06/20 16:29:02  mmiers
 * LOG: Include the error code.
 * LOG:
 * LOG: Revision 6.4  2002/06/20 16:26:23  mmiers
 * LOG: Allow sending untranslated addresses to upper layers.  Whether
 * LOG: this is legal or not is open to interpretation of the spec,
 * LOG: but I believe it is within limits.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 22:52:31  mmiers
 * LOG: Convert TCAP and SCCP to OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/07 17:42:31  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.9  2002/01/02 19:56:08  mmiers
 * LOG: Convert to using long names (everything but TCAP).
 * LOG:
 * LOG: Revision 5.8  2001/11/08 21:16:44  mmiers
 * LOG: Bug fix for OPC.
 * LOG:
 * LOG: Revision 5.7  2001/10/17 22:03:12  mmiers
 * LOG: More debugging
 * LOG:
 * LOG: Revision 5.6  2001/10/04 21:31:33  mmiers
 * LOG: Today's installment.  Really need hardware at this point.
 * LOG:
 * LOG: Revision 5.5  2001/09/25 21:35:20  mmiers
 * LOG: Fix up SCCP routing and SCMG.
 * LOG:
 * LOG: Revision 5.4  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 21:07:22  mmiers
 * LOG: Small corrections.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:27  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.6  2001/07/13 16:57:45  mmiers
 * LOG: GTT on the way out bug.
 * LOG:
 * LOG: Revision 4.5  2001/06/28 22:38:43  mmiers
 * LOG: Oops, old code left.
 * LOG:
 * LOG: Revision 4.4  2001/06/19 19:51:18  mmiers
 * LOG: Redirect only on input.
 * LOG:
 * LOG: Revision 4.3  2001/06/11 21:42:39  mmiers
 * LOG: Pass the label to the callbacks.
 * LOG:
 * LOG: Revision 4.2  2001/05/10 16:53:58  mmiers
 * LOG: Add user intervention callbacks.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.3  2001/01/18 17:43:03  omayor
 * LOG: Get the PC from the ROuting label in sending SST.
 * LOG:
 * LOG: Revision 3.2  2000/08/24 23:07:23  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:29  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  1999/12/06 21:30:09  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.12.2.1  1999/12/06 21:27:28  mmiers
 * LOG:
 * LOG:
 * LOG: Debug with HP's GDI.
 * LOG:
 * LOG: Revision 1.12  1999/10/13 15:47:07  rsonak
 * LOG:
 * LOG: When GTT is performend, the OPC is now changed to the local PC
 * LOG:
 * LOG: Revision 1.11  1999/08/27 00:51:21  mmiers
 * LOG:
 * LOG:
 * LOG: Commit more work, mostly just formatting, but include ies in
 * LOG: GTT callback.  User can really get himself in trouble now.
 * LOG:
 * LOG: Revision 1.10  1999/08/26 23:44:55  labuser
 * LOG:
 * LOG:
 * LOG: Alter GTT to include original PC (if any) and SSN (if any).
 * LOG:
 * LOG: Revision 1.9  1999/08/26 20:34:01  mmiers
 * LOG:
 * LOG:
 * LOG: Fix warnings.
 * LOG:
 * LOG: Revision 1.8  1999/08/26 19:58:48  rsonak
 * LOG:
 * LOG:
 * LOG: Some protocol fixes.
 * LOG:
 * LOG: Revision 1.7  1999/07/29 21:34:02  rsonak
 * LOG:
 * LOG:
 * LOG: Rework GTT a little.
 * LOG:
 * LOG: Revision 1.6  1999/06/29 15:24:22  mmiers
 * LOG:
 * LOG:
 * LOG: Modify global title behavior a bit (allow setting of DPC only).
 * LOG:
 * LOG: Revision 1.5  1999/06/25 16:24:27  mmiers
 * LOG:
 * LOG:
 * LOG: We must modify the routing label if global title translation results
 * LOG: in a new DPC.
 * LOG:
 * LOG: Revision 1.4  1999/06/22 18:18:49  mmiers
 * LOG:
 * LOG:
 * LOG: Correct GTT handling.
 * LOG:
 * LOG: Revision 1.3  1999/06/22 16:17:25  mmiers
 * LOG:
 * LOG:
 * LOG: Add in global title translation.
 * LOG:
 * LOG: Revision 1.2  1999/06/21 22:57:53  mmiers
 * LOG:
 * LOG:
 * LOG: Fix GTT handling bugs in SCCP.
 * LOG:
 * LOG: Revision 1.1  1999/03/17 18:39:44  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.32  1999/02/26 04:10:22  mmiers
 * LOG:
 * LOG:
 * LOG: Compile with CC.
 * LOG:
 * LOG: Revision 1.31  1998/12/14 23:45:30  rsonak
 * LOG: Tracking down the AT&T routing label bug.  Fixed.
 * LOG:
 * LOG: Revision 1.30  1998/11/25 23:57:38  mmiers
 * LOG: SS7 integration is complete.
 * LOG:
 * LOG: Revision 1.29  1998/11/19 01:32:00  mmiers
 * LOG: Build with warning at max.  5 bugs found.
 * LOG:
 * LOG: Revision 1.28  1998/11/17 22:37:40  mmiers
 * LOG: Propagate SCMG (SSP/SSA)
 * LOG:
 * LOG: Revision 1.27  1998/11/17 03:08:57  mmiers
 * LOG: Finish off SCMG.
 * LOG:
 * LOG: Revision 1.26  1998/11/11 03:47:38  mmiers
 * LOG: Clean up some SCCP stuff.
 * LOG:
 * LOG: Revision 1.25  1998/11/09 23:30:25  mmiers
 * LOG: Put in intermediate node code.
 * LOG:
 * LOG: Revision 1.24  1998/11/02 17:07:48  mmiers
 * LOG: Add DEBUG dump of routing label.
 * LOG:
 * LOG: Revision 1.23  1998/10/28 23:51:48  mmiers
 * LOG: Halfway through SCMG.
 * LOG:
 * LOG: Revision 1.22  1998/10/22 00:51:33  whu
 * LOG: Fix Routing Control so that we forward messages if a) we know the
 * LOG: route to them, and b) the route is available.
 * LOG:
 * LOG: Revision 1.21  1998/10/20 01:40:29  mmiers
 * LOG: include all SCCP timers.  More work on inactivity test.  Thinking
 * LOG: about SCMG.
 * LOG:
 * LOG: Revision 1.20  1998/10/16 20:45:24  mmiers
 * LOG: The "NEW! And IMPROVED!" SCCP.  Let the bug reports begin.
 * LOG:
 * LOG: Revision 1.19  1998/10/16 01:44:49  mmiers
 * LOG: Put my current thoughts into bytes.  This stuff is f*cking confusing,
 * LOG: and needs review.
 * LOG:
 * LOG: Revision 1.18  1998/10/15 23:52:39  mmiers
 * LOG: Update SCCP.  About ready to cut over.
 * LOG:
 * LOG: Revision 1.17  1998/10/01 00:11:48  mmiers
 * LOG: Port to alpha
 * LOG:
 * LOG: Revision 1.16  1998/09/30 14:22:45  mmiers
 * LOG: Fix some overnight bugs from home.
 * LOG:
 * LOG: Revision 1.15  1998/09/30 02:41:01  mmiers
 * LOG: Compromise on what we can do with SCCP.
 * LOG:
 * LOG: Revision 1.14  1998/09/29 21:39:10  mmiers
 * LOG: Revert to previous version.  This needs more thought.
 * LOG:
 * LOG: Revision 1.12  1998/09/29 17:33:06  mmiers
 * LOG: Working on MTP3/SCCP integration.
 * LOG:
 * LOG: Revision 1.11  1998/09/29 01:43:47  mmiers
 * LOG: We need PC in IsSSNAllowed() as our SCCP is process-distributed.
 * LOG:
 * LOG: Revision 1.10  1998/09/28 17:37:54  mmiers
 * LOG: More work on SCCP.  Starting to take better shape.
 * LOG:
 * LOG: Revision 1.9  1998/09/27 00:58:49  mmiers
 * LOG: Minor tweaks preparing for connection-oriented cleanup.  Still need to
 * LOG: propagate MTP3 header to relevant pieces.
 * LOG:
 * LOG: Revision 1.8  1998/09/27 00:53:12  mmiers
 * LOG: Start cleaning up connectionless.
 * LOG:
 * LOG: Revision 1.7  1998/09/27 00:04:18  mmiers
 * LOG: More work on SCCP.
 * LOG:
 * LOG: Revision 1.6  1998/09/26 00:00:46  mmiers
 * LOG: More work on true SCCP.
 * LOG:
 * LOG: Revision 1.5  1998/09/25 21:10:57  mmiers
 * LOG: Fixup for trace.
 * LOG:
 * LOG: Revision 1.4  1998/09/24 23:27:32  mmiers
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
#include <assert.h>
#include <stdlib.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <its.h>
#include <its_hash.h>
#include <its_mutex.h>
#include <its_thread.h>
#include <its_route.h>
#include <its_tq_trans.h>
#include <ansi-sccpstat.h>

#ident "$Id: ansi-scrc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#include <ansi/sccp.h>

#include "sccp_intern.h"
#include <its_redundancy.h>

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
SCCP_SendToMTP3(MTP3_HEADER* mtp3, ITS_OCTET mType,
                ITS_SCCP_IE* ies, int ieCount,
                ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_EVENT ev;
    int ret = ITS_EINVALIDARGS;
    ITS_USHORT len;
    ITS_OCTET buf[SCCP_LONG_DATA_MAX];
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK; 
    ITS_INT count;
    ITS_OCTET *buff;
    ITS_OCTET TempBuffer[10];

    switch (mType)
    {
    case SCCP_MSG_CR:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_CR_Desc_ANSI);
        break;

    case SCCP_MSG_CC:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_CC_Desc_ANSI);
        break;

    case SCCP_MSG_CREF:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_CREF_Desc_ANSI);
        break;

    case SCCP_MSG_RLSD:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_RLSD_Desc_ANSI);
        break;

    case SCCP_MSG_RLC:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_RLC_Desc_ANSI);
        break;

    case SCCP_MSG_DT1:
        /* remove slr IE before encode */
        ieCount--;

        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_DT1_Desc_ANSI);
        break;

    case SCCP_MSG_DT2:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_DT2_Desc_ANSI);
        break;

    case SCCP_MSG_AK:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_AK_Desc_ANSI);
        break;

    case SCCP_MSG_UDT:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_UDT_Desc_ANSI);
        break;

    case SCCP_MSG_XUDT:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_XUDT_Desc_ANSI);
        break;

    case SCCP_MSG_UDTS:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_UDTS_Desc_ANSI);
        break;

    case SCCP_MSG_XUDTS:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_XUDTS_Desc_ANSI);
        break;

    case SCCP_MSG_LUDT:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                              ies, ieCount, &SCCP_LUDT_Desc_ANSI);
        break;

    case SCCP_MSG_LUDTS:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                              ies, ieCount, &SCCP_LUDTS_Desc_ANSI);
        break;

    case SCCP_MSG_ED:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_ED_Desc_ANSI);
        break;

    case SCCP_MSG_EA:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_EA_Desc_ANSI);
        break;

    case SCCP_MSG_RSR:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_RSR_Desc_ANSI);
        break;

    case SCCP_MSG_RSC:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_RSC_Desc_ANSI);
        break;

    case SCCP_MSG_ERR:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_ERR_Desc_ANSI);
        break;

    case SCCP_MSG_IT:
        ret = SCCP_EncodeMTP3_ANSI(buf, &len, mType,
                                   ies, ieCount, &SCCP_IT_Desc_ANSI);
        break;
    } /* switch */

    if (ret != ITS_SUCCESS)
    {
         SCCP_ERROR(("SCRCSendToMTP3: Outgoing Message - Discarding Message"
                     "Invalid or Corrupted."));
         return (ret);
    }


    SCCP_DEBUG(("SCRCSendToMTP3: RoutingLabel: SIO %02x OPC %08x "
                "DPC %08x SLS %02x\n",
                mtp3->sio,
                MTP3_RL_GET_OPC_VALUE(mtp3->label),
                MTP3_RL_GET_DPC_VALUE(mtp3->label),
                MTP3_RL_GET_SLS(mtp3->label)));

    if ((ret = MTP3_Encode_ANSI(&ev, MTP3_MSG_USER_DATA, mtp3,
                                buf, len)) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCSendToMTP3: MTP3_Encode_ANSI failed\n"));

        SCCP_ERROR(("SCRCSendToMTP3: Outgoing Message Discarding Message"
                    " Invalid or Corrupted."));

        return (ret);
    }
    ev.src = ITS_SCCP_ANSI_SRC;

    SCCP_DEBUG(("SCRCSendToMTP3: Sending to route: pc %08x ssn %02x\n",
                pc, ssn));

    if (TRACE_IsLevelOn(SCCP_ANSI_TraceData,
                        SCCP_TRACE_DEBUG))
    {
        buff = (ITS_OCTET*)calloc(ev.len*6+1, sizeof(ITS_OCTET));

        for (count = 1; count < ev.len; count++)
        {
            sprintf(TempBuffer, "0x%02x ",ev.data[count]);
            strcat(buff,TempBuffer);
            if (!(count % 15))
            {
                strcat(buff,"\n");
            }
        }
        SCCP_DEBUG(("\n\nData send to MTP: \n\n%s\n\n",buff));
        free(buff);
    }


    /* try to send by SSN routing */
#if 0
    ret = ROUTE_SendToRouteContext(pc, &ev,
                                   ROUTE_DPC_SIO_SSN,
                                   FAMILY_ITU,
                                   ROUTE_SIO_SCCP | ni,
                                   ssn,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE,
                                   ITS_SS7_DEFAULT_PRI,
                                   ITS_SS7_DEFAULT_SLS);
#endif
    /* MLM: Why this? */
/*Patch:Itika:1-nov-10:Redundancy Merge fix*/
#if 0     /* Ashutosh  20-01-2007  BT  issue*/
    ret = ROUTE_SendToRouteContext(pc, &ev,
                                   ROUTE_DPC_SIO_SSN,
                                   FAMILY_ANSI,
                                   ROUTE_SIO_SCCP | ni,
                                   ssn,
                                   ITS_SS7_DEFAULT_LINK_SET,
                                   ITS_SS7_DEFAULT_LINK_CODE,
                                   ITS_SS7_DEFAULT_PRI,
                                   MTP3_RL_GET_SLS(mtp3->label));

    /* if it failed, give it to MTP3 for delivery */
    if (ret != ITS_SUCCESS && ev.data)
    {
        return  TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
    }
#endif
    if (ev.data)
    {
    return  TRANSPORT_PutEvent(ITS_MTP3_SRC, &ev);
    }
   else
        SCCP_DEBUG(("\n\nEvent  data is Null before putting to  MTP3\n\n"));
      
/*Patch:Itika:1-nov-10:End*/

    ITS_EVENT_TERM(&ev);

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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0576            Sending CREF by swaping the
 *                                               MTP3 Routing Lable. 
 *
 ****************************************************************************/
int
sendConnectionRefuse(MTP3_HEADER* mtp3, ITS_USHORT conref, SCCP_ADDR *cgp)
{
    ITS_SCCP_IE info_elem[32];
    int info_Count = 0;
    MTP3_HEADER localMTP3;
    ITS_OCTET cause = SCCP_REF_DEST_UKNOWN;
    ITS_OCTET mType = SCCP_MSG_CREF;
    ITS_OCTET *gttInfo = NULL;
    ITS_USHORT gttLen = 0;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0;
    ITS_UINT pc, cgppc;
    MTP3_POINT_CODE opc, dpc;

    memset((char *)&info_elem, 0, sizeof(info_elem));

    info_elem[info_Count].param_id = SCCP_PRM_ROUTING_LABEL;
    info_elem[info_Count].param_length = sizeof(MTP3_HEADER);

    MTP3_RL_GET_DPC(mtp3->label, dpc);
    MTP3_RL_GET_OPC(mtp3->label, opc);

    pc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

    MTP3_RL_SET_DPC(localMTP3.label, opc);
    MTP3_RL_SET_OPC(localMTP3.label, dpc);

    localMTP3.sio = mtp3->sio;

    info_elem[info_Count].param_data.routingLabel = localMTP3;
    info_Count++;

    info_elem[info_Count].param_id = SCCP_PRM_DEST_LOCAL_REF;
    info_elem[info_Count].param_length = sizeof(SCCP_REF_NUM);
    RN_SET_REF_NUM(info_elem[info_Count].param_data.destinationLocalReference,
                       conref);
    info_Count++;

    info_elem[info_Count].param_id = SCCP_PRM_REFUSAL_CAUSE;
    info_elem[info_Count].param_length = sizeof(SCCP_REF_CAUSE);
    info_elem[info_Count].param_data.refusalCause.cause = cause;
    info_Count++;

    if (cgp)
    {
        info_elem[info_Count].param_id = SCCP_PRM_CALLED_PARTY_ADDR;
        info_elem[info_Count].param_length = sizeof(SCCP_ADDR);

        info_elem[info_Count].param_data.calledPartyAddr = *cgp; 
        info_Count++;
        if (SCCP_DecodeAddr_ANSI(cgp, &addrInd, &cgppc, &ssn,
                            gttInfo, &gttLen) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

            return (ITS_EINVALIDARGS);
        }
     }

    return SCCP_SendToMTP3(&localMTP3, mType, info_elem, info_Count, pc, ssn);
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
SCRCHandleRoutingFailure(MTP3_HEADER* mtp3, ITS_OCTET mType,
                         ITS_SCCP_IE* ies, int ieCount,
                         ITS_OCTET reason)
{
    switch (mType)
    {
    case SCCP_MSG_UDT:
    case SCCP_MSG_XUDT:
    case SCCP_MSG_UDTS:
    case SCCP_MSG_XUDTS:
    case SCCP_MSG_LUDT:
    case SCCP_MSG_LUDTS:
        return SCLCHandleRoutingFailure_ANSI(mtp3, mType, ies, ieCount, reason);

    default:
        return SCOCHandleRoutingFailure_ANSI(mtp3, mType, ies, ieCount, reason);
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
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0698           Taking NI value from Calling
 *                                                and CalledParty Address. 
 *
 ****************************************************************************/
static int
SCRCDeliverMTP3Ind(MTP3_HEADER* mtp3, ITS_OCTET mType,
                   ITS_SCCP_IE* ies, int ieCount,
                   ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    SCCP_StatInfo Sccp_Info;
    ITS_OCTET ROPT_FLAG = 0;
    int j=0,ret=0;
   // ITS_OCTET ni = (addrInd & SCCP_CPA_ROUTE_NAT);
    ITS_OCTET ni = MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK;
    SCCP_DEBUG(("SCRCDeliverMTP3Ind\n"));

    for (j = 0; j < ieCount; j++)
    {
       if (ies[j].param_id == SCCP_PRM_PROTOCOL_CLASS)
	      {
         	  SCCP_DEBUG (("INSIDE SCCP_PRM_PROTOCOL_CLASS %d\n",ies[j].param_data.userData.data[0]));
        	  if(((ies[j].param_data.userData.data[0])&(0x80))==0x80) 
           	    ROPT_FLAG = 1;
	          else
        	      ROPT_FLAG = 0;
	      }
    }
      SCCP_DEBUG (("!!!!!ROPT_FLAG!!!!!!! %d\n", ROPT_FLAG));
    if (!SCCP_IsSSNEquipped(ni, pc, ssn))
       {
        /* SCCP s   `t's not for us.  We can't be that tough --
         * our SCCP is distributed */
        if (SCCP_IsSSNAllowed(ni, pc, ssn))
        {
            /* deliver it */
            switch (mType)
            {
            case SCCP_MSG_UDT:
            case SCCP_MSG_XUDT:
            case SCCP_MSG_UDTS:
            case SCCP_MSG_XUDTS:
            case SCCP_MSG_LUDT:
            case SCCP_MSG_LUDTS:
                return SCRCHandleSCLCMsg_ANSI(mtp3, mType, ies, ieCount);

            default:
                /* EEK! WE'RE AN INTERMEDIATE!! */
                return SCOCHandleSCRCMsg_ANSI(mtp3, mType, ies, ieCount,
                                              pc, ssn, ITS_TRUE);
            }
        }
        else
        {
            SCCP_DEBUG(("DeliverMTP3Ind: pc %08x ssn %02x\n",
                        pc, ssn));

            SCCP_Alarm_ANSI(643, __FILE__, __LINE__, "PC %x, SSN %d, NI %d",
                                                             pc, ssn, ni);
           	if( ROPT_FLAG == 1)
            {
              SCCP_DEBUG(("DeliverMTP3Ind:ROPT SET")); 
	            Sccp_Info.PC = pc;
        	    ret=SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
              if(ret!=ITS_SUCCESS)
              {
               return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,SCCP_RET_UNEQUIPPED_USER);
              }
              return ret;
            }  
           else
            {
              SCCP_DEBUG(("DeliverMTP3Ind:ROPT NOT SET")); 
               return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,SCCP_RET_UNEQUIPPED_USER);
            }
        }
    }
    else if (!SCCP_IsSSNAllowed(ni, pc, ssn))
    {
        SCCP_Alarm_ANSI(643, __FILE__, __LINE__, "PC %x, SSN %d, NI %d",
                                                             pc, ssn, ni);

           	if( ROPT_FLAG == 1)
            {
              SCCP_DEBUG(("DeliverMTP3Ind:ROPT SET")); 
	            Sccp_Info.PC = pc;
        	    ret=SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
              if(ret!=ITS_SUCCESS)
              {
               return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,SCCP_RET_UNEQUIPPED_USER);
              }
              return ret;
            }
           else
            {   
                SCCP_DEBUG(("DeliverMTP3Ind:ROPT NOT SET")); 
                return SCMGSSPCHandleMsgForProhibitedSSN_ANSI(mtp3, mType, ies, ieCount,
                                                       pc, ssn,
                                                       SCCP_RET_SUBSYS_FAIL);
            }
    }
    else
    {
        /* deliver it */
        switch (mType)
        {
        case SCCP_MSG_UDT:
        case SCCP_MSG_XUDT:
        case SCCP_MSG_UDTS:
        case SCCP_MSG_XUDTS:
        case SCCP_MSG_LUDT:
        case SCCP_MSG_LUDTS:
            return SCLCHandleSCRCMsg_ANSI(mtp3, mType, ies, ieCount,
                                          pc, ssn);

        default:
            return SCOCHandleSCRCMsg_ANSI(mtp3, mType, ies, ieCount,
                                          pc, ssn, ITS_FALSE);
        }
    }

    /* NOTREACHED */
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
static int
SCRCDeliverLocal(MTP3_HEADER* mtp3, ITS_OCTET mType,
                 ITS_SCCP_IE* ies, int ieCount,
                 ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD);
    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        return SCRCDeliverMTP3Ind(mtp3, mType, ies, ieCount,
                                  addrInd, pc, ssn);
    }
    else
    {
        switch (mType)
        {
        case SCCP_MSG_UDT:
        case SCCP_MSG_XUDT:
        case SCCP_MSG_UDTS:
        case SCCP_MSG_XUDTS:
        case SCCP_MSG_LUDT:
        case SCCP_MSG_LUDTS:
            SCCP_ERROR(("SCRCDeliverLocal: Cannot perform local delivery\n"));
            SCCP_Alarm_ANSI(644, __FILE__, __LINE__, NULL);

            return (ITS_EINVALIDARGS);

        default:
            return SCOCHandleSCRCMsg_ANSI(mtp3, mType, ies, ieCount,
                                          pc, ssn, ITS_FALSE);
        }
    }

    /* NOTREACHED */
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
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0698             Taking NI value from Calling
 *                                                and CalledParty Address.
 *
 ****************************************************************************/
static int
SCRCDeliverRemote(MTP3_HEADER* mtp3, ITS_OCTET mType,
                  ITS_SCCP_IE* ies, int ieCount,
                  ITS_OCTET addrInd, ITS_UINT pc, ITS_OCTET ssn)
{
    ITS_OCTET ni = MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK;
   // ITS_OCTET ni = (addrInd & SCCP_CPA_ROUTE_NAT);
  SCCP_StatInfo Sccp_Info;
  ITS_OCTET ROPT_FLAG = 0;
  ITS_UINT j = 0;
  SCCP_ADDR *cdp = NULL;
  ITS_UINT pc_pr;
  ITS_OCTET ssn_pr = SCCP_SSN_NONE, addrInd_pr = 0, gttInfo[32] = { '\0', };
  ITS_USHORT gttLen = 0;
  ITS_BOOLEAN pauseFlag;
  ITS_BOOLEAN sspFlag;


  for (j = 0; j < ieCount; j++)
    {
      if (ies[j].param_id == SCCP_PRM_PROTOCOL_CLASS)
	{
	  SCCP_DEBUG (("INSIDE SCCP_PRM_PROTOCOL_CLASS %d\n",
		       ies[j].param_data.userData.data[0]));
	  if(((ies[j].param_data.userData.data[0])&(0x80))==0x80) 
	    ROPT_FLAG = 1;
	  else
	    ROPT_FLAG = 0;
	}
    }
  SCCP_DEBUG (("!!!!!ROPT_FLAG!!!!!!! %d\n", ROPT_FLAG));
  SCCP_DEBUG (("SCRCDeliverRemote: RoutingLabel: SIO %02x OPC %08x "
	       "DPC %08x SLS %02x\n",
	       mtp3->sio,
	       MTP3_RL_GET_OPC_VALUE (mtp3->label),
	       MTP3_RL_GET_DPC_VALUE (mtp3->label),
	       MTP3_RL_GET_SLS (mtp3->label)));

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        SCCP_DEBUG(("DeliverRemote: pc %08x ssn %02x\n", pc, ssn));

        if (!SCCP_IsSSNAllowed_ANSI(ni, pc, ssn))
        {
            SCCP_DEBUG(("DeliverRemote: pc %08x ssn %02x\n",
                        pc, ssn));

            /* SSN is not allowed */
            SCCP_Alarm_ANSI(648, __FILE__, __LINE__,"PC %x SSN %d",
                             pc, ssn);
	  Sccp_Info.PC = pc;
          if (ROPT_FLAG)
          {
                SCCP_DEBUG (("ANSI:Retrun OPTION IS SET \n"));
                return SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
           }
           else
          {
                SCCP_DEBUG (("Retrun OPTION IS NOT SET \n"));
                return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,SCCP_RET_NETWORK_FAIL);
           }
 
        }

        if (SCCP_IsSSNCongested_ANSI(ni, pc, ssn))
        {
            SCCP_DEBUG(("DeliverRemote: pc %08x ssn %02x\n",
                        pc, ssn));

            return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_CONG);
        }
    }
  if (ROPT_FLAG)
    {
      for (j = 0; j < ieCount; j++)
	{
	  if (ies[j].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
	    {
	      cdp = &ies[j].param_data.calledPartyAddr;
	    }
	}
      /* Decode Called Party address into component parts  */
      if (SCCP_DecodeAddr
	  (cdp, &addrInd_pr, &pc_pr, &ssn_pr, gttInfo,
	   &gttLen) != ITS_SUCCESS)
	{
	  SCCP_ERROR (("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));
	  return (ITS_EINVALIDARGS);
	}
      SCCP_DEBUG (("SCRCDeliverRemote: RoutingLabel: SIO %02x OPC %08x "
		   "DPC %08x SLS %02x,SSN %d\n",
		   mtp3->sio,
		   MTP3_RL_GET_OPC_VALUE (mtp3->label),
		   MTP3_RL_GET_DPC_VALUE (mtp3->label),
		   MTP3_RL_GET_SLS (mtp3->label), ssn_pr));
      SCCP_DEBUG (("ROPT_FLAG::::%d||||||||||Network Indicator ==%d\n",
		   ROPT_FLAG, (mtp3->sio & 0xc0)));
      GetSsnStatus_DSM (MTP3_RL_GET_DPC_VALUE (mtp3->label),MTP3_RL_GET_OPC_VALUE (mtp3->label),
			(mtp3->sio & 0xc0), &pauseFlag, &sspFlag, ssn_pr);

      SCCP_DEBUG (("pauseFlag->%d---- sspFlag=%d", pauseFlag, sspFlag));
      if (pauseFlag == ITS_TRUE && sspFlag == ITS_TRUE)
           return	SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
      else
          	return SCCP_SendToMTP3 (mtp3, mType, ies, ieCount, pc, ssn);
    }
  else
    return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, pc, ssn);
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
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0698             Taking NI value from Calling
 *                                                and CalledParty Address.
 *
 ****************************************************************************/
static int
SCRCDeliverByGTT(MTP3_HEADER* mtp3, ITS_OCTET mType,
                 ITS_SCCP_IE* ies, int ieCount, ITS_OCTET ai,
                 ITS_UINT pc, ITS_OCTET ssn,
                 ITS_OCTET *gttInfo, ITS_USHORT gttLen,ITS_BOOLEAN toApp)
{
    SCCP_ADDR transAddr;
    ITS_UINT dpc, npc, thispc,PC;
    ITS_OCTET nssn = SCCP_SSN_NONE, addrInd = 0;
    ITS_OCTET ni=MTP3_NIC_INTERNATIONAL;
    ITS_BOOLEAN isAllowed;
    int i,ret=0;
    SCCP_StatInfo Sccp_Info;
    ITS_OCTET ROPT_FLAG = 0, Tmp=0;
    ITS_UINT j = 0;
    SCCP_ADDR *cdp=NULL;
    ITS_UINT pc_pr=0;
    ITS_OCTET ssn_pr = SCCP_SSN_NONE, addrInd_pr = 0, gttInfo_pr[32] = { '\0', };
    ITS_USHORT gttLen_pr = 0;
/*Patch:Itika:16-jun-10:Fix in ANSI & ITU :Updated for ANSI SCCP  CL*/
    ITS_BOOLEAN pauseFlag = ITS_TRUE;
    ITS_BOOLEAN sspFlag = ITS_TRUE;
/*End:Updated for ANSI SCCP  CL*/
    for (j = 0; j < ieCount; j++)
    {
      if (ies[j].param_id == SCCP_PRM_PROTOCOL_CLASS)
     	{
	       SCCP_DEBUG (("INSIDE SCCP_PRM_PROTOCOL_CLASS %d\n",ies[j].param_data.userData.data[0]));
      	 Tmp = ies[i].param_data.userData.data[0];
         if (((ies[j].param_data.userData.data[0] )&0x80)==0x80)
          	         ROPT_FLAG = 1;
	       else
	                  ROPT_FLAG = 0;
	   }
   }
    SCCP_DEBUG((" ->>>>>>>>ROPT===%d<-----pc %d-------\n",ROPT_FLAG,pc));
    if (SCCP_GTTTranslate_ANSI(mtp3, &dpc, ai, pc, ssn, gttInfo, gttLen,
                                &transAddr, ies, ieCount) != ITS_SUCCESS)
    {
        /* Inform maintenance */
        SCCP_WARNING(("SCRCDeliverByGTT: GTT Translation failed.\n"));

        /* GTT - Global Title Translation failed. */
        SCCP_Alarm_ANSI(645, __FILE__, __LINE__, NULL);
        Sccp_Info.PC=dpc;
        SCCP_DEBUG((" ROPT===%d\n",ROPT_FLAG));
        if (ROPT_FLAG)
         {
            	ret=SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_FALSE, SCCP_RET_NO_TRANS_THIS_ADDR);
                          if(ret!=ITS_SUCCESS)
                          {
	                           return SCRCHandleRoutingFailure (mtp3, mType, ies, ieCount,SCCP_RET_NETWORK_FAIL);
                          }                   
                          return ret; 
         }
        else
         {
            	SCCP_DEBUG (("Retrun OPTION IS NOT SET \n"));
              return SCRCHandleRoutingFailure (mtp3, mType, ies, ieCount,SCCP_RET_NO_TRANS_THIS_ADDR);
         }
    }
    SCCP_DEBUG((" ->>>>>>>>-----pc %d-------\n",pc));

    ni = MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK;


    /* replace the CDP with the translated info */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            ies[i].param_data.calledPartyAddr = transAddr;
            SCCP_ERROR(("SCRCDeliverByGTT:  Called Party len=%d\n",ies[i].param_length));
            if(ies[i].param_length!=transAddr.len)
            {
              ies[i].param_length=transAddr.len;
              SCCP_ERROR(("SCRCDeliverByGTT:  Called Party len=%d\n",ies[i].param_length));

            } 
        }
        else if (ies[i].param_id == SCCP_PRM_HOP_COUNTER)
        {
            if (ies[i].param_data.hopCount.count <= 0)
            {
                ies[i].param_data.hopCount.count = 0;

                PEG_IncrPeg(ANSI_SCCP_Pegs,PEG_SCCP_HOP_COUNTER_VIOLATION_ERR);

                return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,
                                                SCCP_RET_HOP_COUNT_EXCEEDED);
            }
            ies[i].param_data.hopCount.count--;
        }
    }

    /* we must get a point code back from this */
    if (SCCP_DecodeAddr_ANSI(&transAddr, &addrInd, &npc, &nssn,
                        NULL, NULL) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCDeliverByGTT:  Couldn't decode translated addr\n"));

        /* GTT - Global Title Translation returned invalid address. */
        SCCP_Alarm_ANSI(646, __FILE__, __LINE__, NULL);

        return (ITS_EINVALIDARGS);
    }
    SCCP_DEBUG((" ->>>>>>>>-----addrInd %d-------\n",addrInd));

    if(nssn==0)
    {
     nssn=ITS_SS7_DEFAULT_SSN;
    }
      /*change by IMR because of GTT*/

     if(ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                            ROUTE_SIO_SCCP|(MTP3_NIC_INTERNATIONAL),  
                                                  nssn,ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,
                                                         ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
         {
             if(ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                              ROUTE_SIO_SCCP|(MTP3_NIC_SPARE),nssn,
                                                ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,                                                                           ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
              {
                 if(ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                                 ROUTE_SIO_SCCP|(MTP3_NIC_NATIONAL),nssn,
                                                   ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,                                                                           ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                   {
                       if(ROUTE_GetRouteContextStatus(dpc, &isAllowed,ROUTE_DPC_SIO_SSN,FAMILY_ANSI,
                                                             ROUTE_SIO_SCCP|(MTP3_NIC_RESERVED),nssn,
                                                              ITS_SS7_DEFAULT_LINK_SET,ITS_SS7_DEFAULT_LINK_CODE,                                                                           ITS_SS7_DEFAULT_PRI,ITS_SS7_DEFAULT_SLS)!= ITS_SUCCESS)
                        {
                           SCCP_ERROR(("SCRCDeliverByGTT:RETRIVAL FAIL \n"));
                        }
                        else
                        {
                          ni=MTP3_NIC_RESERVED;
                        }
                   }
                   else
                   {
                          ni=MTP3_NIC_NATIONAL;
                   }                        
              }
             else
              { 
                  ni=MTP3_NIC_SPARE;
              }
        }
     else
        {
                  ni=MTP3_NIC_INTERNATIONAL;
        } 

        mtp3->sio=mtp3->sio|ni;

    /*
     * Now we can go ahead and change the DPC as follows.
     * We can do this unconditionally, as the user has to specify
     * it (whether it changed or not).
     */

    /*
     * we need to check the point code.
     */
    thispc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
    if(toApp)
    {
      PC = MTP3_RL_GET_DPC_VALUE(mtp3->label);
      SCCP_DEBUG(("SCRCDeliverByGTT:Value of OPC =%d\n",PC));
    }
   else
    {
      PC = MTP3_RL_GET_OPC_VALUE(mtp3->label);
      SCCP_DEBUG(("SCRCDeliverByGTT:Value of OPC =%d\n",PC));
    }
    if (!(addrInd & SCCP_CPA_HAS_PC))
    {
        MTP3_RL_SET_DPC_VALUE(mtp3->label, dpc);
        npc = dpc;
    }
    else
    {
        /* we have to change the DPC in the routing label.  This is
         * akin to what we did above with the called party addr */
        MTP3_RL_SET_DPC_VALUE(mtp3->label, npc);
        dpc = npc;
    }

    /*
     * now we have a problem.  We've got one of:
     * 1. DPC
     * 2. DPC+SSN
     * 3. DPC+GTT
     * 4. DPC+GTT+SSN
     *
     * Cases 2 and 4 are ok, we know how to deliver those.  Cases 1 and 3
     * are a problem, as our internal routing is by PC+SSN, so we don't
     * quite know which destination to deliver on, as we don't have the
     * SSN.
     *
     * How to fix this?  Well, here's the solution: GTT that translates
     * into NO SSN PRESENT *MUST* *NOT* terminate to our point code.
     * We will have to force this issue.
     */

    // addrInd=(addrInd & 0x7f)|ni;/*change by IMR*/
     SCCP_DEBUG(("SCRCDeliverByGTT:Value of addrInd=%d\n",addrInd));
    if (!(addrInd & SCCP_CPA_HAS_SSN))
    {
        /* without an SSN we don't know who to deliver to */
        /* force it by seeing if the pc matches a known local route */
//        if (SCCP_IsSSNEquipped_ANSI(ni, npc, SCCP_SSN_SCCPMGMT))
        if (SCCP_IsSSNEquipped_ANSI(ni, npc,nssn))
        {
            SCCP_DEBUG(("DeliverGTT: npc %08x ssn %02x\n",
                        npc, nssn));

            /* Incr discard counter for this Msg Type */
            Sccp_Info.PC=npc;
        	  if (ROPT_FLAG)
        	    SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_FALSE,SCCP_RET_NO_TRANS_THIS_ADDR);
	         else
            {
          	    SCCP_DEBUG (("Retrun OPTION IS NOT SET \n"));
	              return SCRCHandleRoutingFailure (mtp3, mType, ies, ieCount,SCCP_RET_NETWORK_FAIL);
            }
        }
        else
        {
            /*
             * It isn't going to us, so we need to set a new OPC (us).
             * We need to change the OPC to the local Point Code (which
             * is equal to the DPC in the RL now)
             */

            /*MTP3_RL_SET_OPC_VALUE(mtp3->label, thispc);

            return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                     addrInd, npc, SCCP_SSN_NONE);*/

            Sccp_Info.PC=npc;
      	    if (ROPT_FLAG)
	           {
	             for (j = 0; j < ieCount; j++)
            		{
             		  if (ies[j].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
		                {
                        SCCP_ERROR(("SCRCDeliverByGTT:  iCalled Party len=%d\n",ies[j].param_length));
               		      cdp = &ies[j].param_data.calledPartyAddr;
		                }
		            }
	           /* Decode Called Party address into component parts  */
  	          if (SCCP_DecodeAddr(cdp, &addrInd_pr, &pc_pr, &ssn_pr, gttInfo_pr, &gttLen_pr) != ITS_SUCCESS)
 	  	         {
             		  SCCP_ERROR (("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));
		              return (ITS_EINVALIDARGS);
		           }
	              GetSsnStatus_DSM (MTP3_RL_GET_DPC_VALUE (mtp3->label),PC,
                                            (mtp3->sio & 0xc0), &pauseFlag, &sspFlag,ssn_pr);
        	      SCCP_DEBUG (("pauseFlag->%d---- sspFlag=%d", pauseFlag, sspFlag));
               if(MTP3_RL_GET_DPC_VALUE (mtp3->label) == dpc)
               {
   	            if (pauseFlag == ITS_TRUE && sspFlag == ITS_TRUE)
	  	                     return SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
                else
                      		return SCCP_SendToMTP3 (mtp3, mType, ies, ieCount, npc,SCCP_SSN_NONE);
               }
	           }
	       else
	               return SCCP_SendToMTP3 (mtp3, mType, ies, ieCount, npc, SCCP_SSN_NONE);
	        }
      }
     else if (!(addrInd & SCCP_CPA_ROUTE_SSN))
      {
        /*
         * By definition, this CANNOT be local.  We cannot be
         * asked to perform two translations, as this would
         * allow recursion.  Exception: translation says that
         * the new addres *is* local, but translation doesn't
         * change the CdPA.
         */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
					 // if (SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), npc, nssn))
            if (SCCP_IsSSNEquipped_ANSI(ni, npc, nssn))
            {
                SCCP_DEBUG(("DeliverGTT: npc %08x nssn %02x\n",
                            npc, nssn));

                /*
                 * Don't change the OPC, we are delivering a message to ourself
                 * even though we performed translation
                 */
                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, npc, nssn);
            }
            else
            {
                /*
                 * It isn't going to us, so we need to set a new DPC.
                 * We need to change the OPC to the local Point Code (which
                 * is equal to the DPC in the RL now)
                 */
                  /*MTP3_RL_SET_OPC_VALUE(mtp3->label, thispc); cnage by IMR 
                  return SCRCDeliverRemote(mtp3, mType, ies, ieCount,addrInd, npc, nssn);*/
                  Sccp_Info.PC=npc;
  	               if (ROPT_FLAG)
                		{
                   		  for (j = 0; j < ieCount; j++)
                		    {
               		      if (ies[j].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
                    			{
                  			   cdp = &ies[j].param_data.calledPartyAddr;
                           SCCP_ERROR(("SCRCDeliverByGTT:  iCalled Party len=%d\n",ies[j].param_length));
			                    }
		                    }
                		  /* Decode Called Party address into component parts  */
               		  if (SCCP_DecodeAddr(cdp, &addrInd_pr, &pc_pr, &ssn_pr, gttInfo_pr,&gttLen_pr) != ITS_SUCCESS)
		                 {
                  		      SCCP_ERROR (("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));
                  		      return (ITS_EINVALIDARGS);
		                 } 
           		    GetSsnStatus_DSM (MTP3_RL_GET_DPC_VALUE (mtp3->label),PC,
                                                   (mtp3->sio & 0xc0), &pauseFlag, &sspFlag,ssn_pr);
            		  SCCP_DEBUG (("pauseFlag->%d---- sspFlag=%d", pauseFlag,sspFlag));
            		  if (pauseFlag == ITS_TRUE && sspFlag == ITS_TRUE)
                    {
                		      ret=SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE, SCCP_RET_NETWORK_FAIL);
                          if(ret!=ITS_SUCCESS)
                          {
	                           return SCRCHandleRoutingFailure (mtp3, mType, ies, ieCount,SCCP_RET_NETWORK_FAIL);
                          }                   
                          return ret; 
                    }
             		  else
                  		    return SCCP_SendToMTP3 (mtp3, mType, ies, ieCount, npc,SCCP_SSN_NONE);
		               }
                 else 		return SCCP_SendToMTP3 (mtp3, mType, ies, ieCount, npc,SCCP_SSN_NONE);
               
            }
        }
        else
        {
            /* Incr discard counter for this Msg Type */
             Sccp_Info.PC=npc;		
          	  if (ROPT_FLAG)
             	   return SCCP_EventProcforReturn (ies, ieCount, &Sccp_Info, ITS_TRUE,SCCP_RET_NETWORK_FAIL);
	           else
              {
          	     SCCP_DEBUG (("Retrun OPTION IS NOT SET \n"));
                    return SCRCHandleRoutingFailure(mtp3, mType, ies, ieCount,SCCP_RET_NETWORK_FAIL);
              }
         }
     }
    else
    {
        /*
         * Don't change the OPC, we are delivering a message to ourself
         * even though we performed translation
         */
        return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                addrInd, npc, nssn);
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh  03-06-2005  Issue ID::1919          Protcol Class Check Added
 *
 ****************************************************************************/
int
SCRCHandleMTP3Msg_ANSI(ITS_EVENT* ev)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32],lpclass = 0;
    ITS_USHORT gttLen = 0;
    ITS_OCTET mType;
    SCCP_ADDR* cdp = NULL;
    MTP3_HEADER hdr3;
    ITS_OCTET data[SCCP_LONG_DATA_MAX];
    ITS_USHORT len;
    ITS_SCCP_IE ies[32];
    int ieCount, i;
      ITS_Class redunClass = ITS_FindFeature(REDUNDANCY_CLASS_NAME);

    SCCP_DEBUG(("SCRCHandleMTP3Msg:\n"));
     /*change for redudnancy*/
     if (redunClass)
           {
             if (REDUNDANCY_GET_NODE_STATE(redunClass) != ITS_STATE_PRIMARY)
             {
                SCCP_ERROR(("Backup Node Cannot Initiate Messages.\n"));
                return (ITS_EINVINITSTATE);
             }
         }
      /*change for redundancy*/
    if (MTP3_Decode_ANSI(ev, &mType, &hdr3, data, &len) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

        return (ITS_EINVALIDARGS);
    }

    SCCP_DEBUG(("SCRCHandleMTP3Msg: RoutingLabel: SIO %02x OPC %08x "
                "DPC %08x SLS %02x\n",
                hdr3.sio,
                MTP3_RL_GET_OPC_VALUE(hdr3.label),
                MTP3_RL_GET_DPC_VALUE(hdr3.label),
                MTP3_RL_GET_SLS(hdr3.label)));

    if (mType != MTP3_MSG_USER_DATA)
    {
        return SCMGHandleMTP3Msg_ANSI(&hdr3, mType, data, len);
    }

    /* get the new message type */
    mType = data[0];

    /* figure out how to handle it */
    switch (mType)
    {
    case SCCP_MSG_CC:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_CC_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_CREF:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_CREF_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_RLSD:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_RLSD_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_RLC:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_RLC_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_DT1:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_DT1_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));


            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_DT2:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_DT2_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_AK:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_AK_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_ED:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_ED_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_EA:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_EA_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_RSR:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_RSR_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_RSC:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_RSC_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_ERR:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_ERR_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    case SCCP_MSG_IT:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_IT_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        return SCOCHandleSCRCMsg_ANSI(&hdr3, mType, ies, ieCount,
                                      0, ssn, ITS_FALSE);

    /*
     * everything after this point falls into the rest of the function
     */
    case SCCP_MSG_CR:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_CR_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_UDT:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_UDT_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                if (lpclass == SCCP_PCLASS_1)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg_ANSI: \
                                  Protocol class 1 received\n"));
                }
                else if (lpclass == SCCP_PCLASS_0)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg: \
                                  Protocol class 0 received\n"));
                }
                else
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid prot class\n"));
                    SCCP_Alarm_ANSI(670, __FILE__, __LINE__, "Pclass %d",
                                     lpclass);

                    return (ITS_EINVALIDARGS);
                }

                break;
            }
        }
        break;

    case SCCP_MSG_XUDT:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_XUDT_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                if (lpclass == SCCP_PCLASS_2 || lpclass == SCCP_PCLASS_3)
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                    return (ITS_EINVALIDARGS);
                }

                break;
            }
        }

        break;

    case SCCP_MSG_UDTS:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_UDTS_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            return (ITS_EINVALIDARGS);
        }

        break;

    case SCCP_MSG_XUDTS:
        if (SCCP_DecodeMTP3_ANSI(data, len, &mType,
                                 ies, &ieCount,
                                 &SCCP_XUDTS_Desc_ANSI) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));
        
            return (ITS_EINVALIDARGS);
        }

        break;

        case SCCP_MSG_LUDT:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_LUDT_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        for (i = 0; i < ieCount; i++)
        {
            if (ies[i].param_id == SCCP_PRM_PROTOCOL_CLASS)
            {
                lpclass = (0x0F & ies[i].param_data.protocolClass.pclass);

                if (lpclass == SCCP_PCLASS_1)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg_ANSI: \
                                  Protocol class 1 received\n"));

                }
                else if (lpclass == SCCP_PCLASS_0)
                {
                     SCCP_DEBUG(("SCRCHandleMTP3Msg: \
                                  Protocol class 0 received\n"));
                }
                else
                {
                    SCCP_ERROR(("SCRCHandleMTP3Msg:Invalid protocol class\n"));

                    SCCP_Alarm_ANSI(670, __FILE__, __LINE__, "Pclass %d",
                                     lpclass);

                    return (ITS_EINVALIDARGS);
                }

                break;
            }
        }

        break;

        case SCCP_MSG_LUDTS:
        if (SCCP_DecodeMTP3(data, len, &mType,
                            ies, &ieCount,
                            &SCCP_LUDTS_Desc) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

            /* Incr message discard counter for this type message */

            return (ITS_EINVALIDARGS);
        }

        break;

    default:
        SCCP_ERROR(("SCRCHandleMTP3Msg: invalid message type\n"));

        SCCP_Alarm_ANSI(636, __FILE__, __LINE__,"Message Type: %d", mType);

        return (ITS_EINVALIDARGS);
    }

    /*
     * this is fallthru for CR, UDT, XUDT, UDTS, XUDTS
     */

    /*
     * find the CalledPartyAddress
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;

            break;
        }
    }

    if (i == ieCount)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't find called party\n"));

        /* Called party is absent in Address Indicator. */
        SCCP_Alarm_ANSI(647, __FILE__, __LINE__, "Point Code: "
                        "%x",MTP3_RL_GET_OPC_VALUE(hdr3.label));
        
        return (ITS_EINVALIDARGS);
    }

    /*
     * decode CalledPartyAddress
     */
    if (SCCP_DecodeAddr_ANSI(cdp, &addrInd, &pc, &ssn,
                             gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleMTP3Msg:  Couldn't decode called party\n"));
        SCCP_Alarm_ANSI(647, __FILE__, __LINE__, "Point Code: "
                        "%x",MTP3_RL_GET_OPC_VALUE(hdr3.label));

        return (ITS_EINVALIDARGS);
    }

    if (!(addrInd & SCCP_CPA_HAS_PC))
    {
        pc = MTP3_RL_GET_DPC_VALUE(hdr3.label);
    }

    /* do we have GTT */
    if (addrInd & SCCP_CPA_ROUTE_SSN)
    {
        SCCP_ADDR transAddr;

        /* copy the address */
        transAddr = *cdp;

        /* possible user intervention */
        if (SCCP_UserIntervention_ANSI(&hdr3, addrInd, pc, ssn,
                                       gttInfo, gttLen, &transAddr,
                                       ies, ieCount) != ITS_SUCCESS)

        {
            /* Inform maintenance */
            SCCP_WARNING(("SCRCHandleMTP3Msg: User intervention failed.\n"));

            return SCRCHandleRoutingFailure(&hdr3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }

        /* replace the CDP with the translated info */
        *cdp = transAddr;

        /* we might get a point code back from this */
        if (SCCP_DecodeAddr_ANSI(&transAddr, &addrInd, &pc, &ssn,
                                 NULL, NULL) != ITS_SUCCESS)
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg_ANSI: Couldn't decode translated addr\n"));

            return (ITS_EINVALIDARGS);
        }

        if (!(addrInd & SCCP_CPA_ROUTE_SSN))
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg_ANSI: User on fire (intervention failed)\n"));

            return (ITS_EINVALIDARGS);
        }

        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(hdr3.label);
            }

            return SCRCDeliverMTP3Ind(&hdr3, mType, ies, ieCount,
                                      addrInd, pc, ssn);
        }
        else
        {
            SCCP_ERROR(("SCRCHandleMTP3Msg: MTP3Indication is "
                        "undeliverable (no SSN).\n"));

            SCCP_Alarm_ANSI(644, __FILE__, __LINE__,"Message Type: %d", mType);

            return SCRCHandleRoutingFailure(&hdr3, mType, ies, ieCount,
                                            SCCP_RET_NETWORK_FAIL);
        }
    }
    else
    {
        /* Send to Routing Control to Route on GT */
        return SCRCDeliverByGTT(&hdr3, mType, ies, ieCount, addrInd,
                                pc, ssn, gttInfo, gttLen,ITS_TRUE);
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0698    Taking NI value from Calling
 *                                        and CalledParty Address.
 *
 *  ssingh     04-01-2005  BugId: 817     Bug Fix propagation.
 *                                        Outgoing SCLC messages based
 *                                        on App Route Selector Criteria.
 *
 *  ssingh    04-29-2005  BugId: 1771    Removed the bug (817) propagation
 *                                       fix as ACTIVE-ACTIVE redundancy
 *                                       is not working with.
 ****************************************************************************/
int
SCRCHandleSCLCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
    ITS_USHORT gttLen = 0;
    SCCP_ADDR* cdp = NULL, *clp = NULL;
   // ITS_OCTET *scmgData = NULL;
    ITS_OCTET scmgData[254];
    ITS_USHORT dlen = 0;
    int i;
    SCCP_StatInfo Sccp_Info;
    /*
     * find the CalledPartyAddress
     */
    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
        {
            cdp = &ies[i].param_data.calledPartyAddr;
        }
        else if (ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
        {
            clp = &ies[i].param_data.callingPartyAddr;  
        }
        else if (ies[i].param_id == SCCP_PRM_DATA)
        {
//            scmgData = ies[i].param_data.userData.data;
           /*  data = &ies[i].param_data.userData;  */
            dlen = ies[i].param_length;
            memcpy(scmgData,ies[i].param_data.userData.data,dlen);
        }
        else if (ies[i].param_id == SCCP_PRM_LONG_DATA)
        { 
  //          scmgData = ies[i].param_data.longData.data;
            dlen = ies[i].param_data.longData.len;
            memcpy(scmgData,ies[i].param_data.userData.data,dlen);
        }
    }

    if (cdp == NULL)
    {
        SCCP_ERROR(("SCRCHandleSCLCMsg:  Couldn't find called party\n"));

        return (ITS_EINVALIDARGS);
    }



    if (SCCP_DecodeAddr_ANSI(cdp, &addrInd, &pc, &ssn,
                        gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));

        return (ITS_EINVALIDARGS);
    }

    /*
     * WARNING: If this condition is true:
     * 1.  This message MUST be from local SCMG
     * 2.  This message MUST be outbound ONLY.
     * 3.  SSN is the only thing present in the addr.
     */
    if (BEHAVIORS_GetBehavior(&ANSI_SCCP_Behaviors,
                              SCCP_B_use_SCMG) &&
        (addrInd & SCCP_CPA_HAS_SSN) && ssn == SCCP_SSN_SCCPMGMT)
    {
        /*
         * Now it gets fun.  This message is one of two types.  It's either
         * 1. Notification of change of status of a local subsystem.
         * 2. Notification of change of status of a concerned subsystem.
         *
         * The problem is we don't necessarily *know* the destination, as it
         * may have a point code that is part of our distributed local PC.
         * If we were a "real" SCCP, this wouldn't be an issue as the SCCP
         * wouldn't be distributed.
         *
         * How to fix?  Well, by kludging SCMG, of course.  What we'll do
         * is put the destination ssn in the calling party address.
         * 1. If DPC/SSN is equipped (local), we shouldn't get here, so
         *    we discard.
         * 2. If DPC/SSN is not equipped (remote), we want to send to the
         *    route that has that DPC/SSN as a destination.  NOTE THAT THIS
         *    may be a wild-card destination! So use ROUTE_SelectRoute().
         */
        SCCP_SCMG_ANSI scmg;
        ITS_UINT dpc, opc;
        ITS_OCTET gttI[SCCP_MAX_ADDR_LEN];
        ITS_USHORT gttLen;

        SCCP_DEBUG(("SCRCHandleSCLCMsg: Handle SCMG message\n"));

        if (dlen != sizeof(SCCP_SCMG_ANSI) || clp == NULL)
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Invalid SCMG message\n"));

            return (ITS_EMISSMAND);
        }

//        memcpy(&scmg, data->data, sizeof(SCCP_SCMG_ANSI));

//        SCCP_DEBUG(("SCRCHandleSCLCMsg: SCMG type %02x\n", scmg.type));
         SCCP_DEBUG(("SCRCHandleSCLCMsg: SCMG type %02x\n",scmgData[0] ));

        switch (scmgData[0])
        {
        case SCCP_SCMG_SS_UIS:
        case SCCP_SCMG_SS_UOS:
        case SCCP_SCMG_SS_CONG:
            /* deliver these to local SCCP MGMT */
            break;
        case SCCP_SCMG_SS_STATUS_TEST:
            ssn = SCCP_SSN_SCCPMGMT;
            dpc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            /*
             * We *need* this information, at the destination, IF THE DEST
             * IS US.  Else we cannot determine who to send the response to!
             */
            if (pc != opc)
            {
                if (SCCP_EncodeAddr_ANSI(clp, addrInd, opc, SCCP_SSN_SCCPMGMT,
                                         NULL, 0) != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCRCHandleSCLCMsg:  Bad addr info\n"));

                    return (ITS_EINVALIDARGS);
                }
            }

            SCCP_DEBUG(("SCRCHandleSCLCMsg: Sending SCMG message\n"));

            /* pc is 0 so use dpc in SendToMTP3 */

            return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, dpc, ssn);

        default:
            pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            opc = MTP3_RL_GET_OPC_VALUE(mtp3->label);

            if (SCCP_DecodeAddr_ANSI(clp, &addrInd, &dpc, &ssn,
                                gttI, &gttLen) != ITS_SUCCESS)
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg:  Couldn't decode addr\n"));

                return (ITS_EINVALIDARGS);
            }

            if (!(addrInd & SCCP_CPA_HAS_SSN))
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg:  Invalid addr\n"));

                return (ITS_EINVALIDARGS);
            }
            SCCP_DEBUG(("SCRCHandleSCLC: Send to %08x:%02x\n", pc, ssn));

            /*
             * We *need* this information, at the destination, IF THE DEST
             * IS US.  Else we cannot determine who to send the response to!
             */
            if (pc != opc)
            {
                if (SCCP_EncodeAddr_ANSI(clp, addrInd, dpc, SCCP_SSN_SCCPMGMT,
                                    gttI, gttLen) != ITS_SUCCESS)
                {
                    SCCP_ERROR(("SCRCHandleSCLCMsg:  Bad addr info\n"));

                    return (ITS_EINVALIDARGS);
                }
            }

            SCCP_DEBUG(("SCRCHandleSCLCMsg: Sending SCMG message\n"));

            return SCCP_SendToMTP3(mtp3, mType, ies, ieCount, pc, ssn);
        }
    }

    /* is GTT? */
    if (addrInd & SCCP_CPA_ROUTE_SSN)
    {
        /* No. */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }

//            if (SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), pc, ssn))
            if (SCCP_IsSSNEquipped((MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK), pc, ssn))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                            pc, ssn));
                 
               Sccp_Info.PC=pc;
             /*  SCCP_EventProcforReturn( ies,ieCount,&Sccp_Info,ITS_TRUE,
                      SCCP_RET_NETWORK_FAIL);*/
                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
        else
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                        "undeliverable (no SSN).\n"));

            SCCP_Alarm_ANSI(644, __FILE__, __LINE__, "Message Type: %d", mType);

            return (ITS_EMISSMAND);
        }
    }
#ifdef ASHUTOSH
    else
    {
        /* We (IntelliSS7) cannot deliver without SSN. */
        if (addrInd & SCCP_CPA_HAS_SSN)
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }
            if (SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), pc, ssn))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                            pc, ssn));

                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
        else
        {
            if (!(addrInd & SCCP_CPA_HAS_PC))
            {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
            }

            if (!SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), 
                                          pc, ITS_SS7_DEFAULT_SSN))
            {
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                            pc, ssn));


                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ITS_SS7_DEFAULT_SSN);
            }

            return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                    pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen,ITS_FALSE);
        }
    }
#endif
  else
   {
      if (!(addrInd & SCCP_CPA_HAS_PC))
         {
            pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
         }
                SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC ROUTE ON GTT :: DPC %d\n",pc));
       return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                    pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen,ITS_FALSE);
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
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name      Date        Reference               Description
 *  --------------------------------------------------------------------------
 *  csireesh   04-04-2005  Bug ID:0698             Taking NI value from Calling
 *                                                and CalledParty Address.
 *
 ****************************************************************************/
int
SCRCHandleSCOCMsg_ANSI(MTP3_HEADER* mtp3, ITS_OCTET mType,
                       ITS_SCCP_IE* ies, int ieCount,
                       SCCP_ADDR* cdp)
{
    ITS_UINT pc;
    ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
    ITS_OCTET ni = MTP3_HDR_GET_SIO_ANSI(*mtp3) & MTP3_NIC_MASK;
    ITS_USHORT gttLen = 0;

    /* we always get CDP, so don't check the return code */
    if (SCCP_DecodeAddr_ANSI(cdp, &addrInd, &pc, &ssn,
                        gttInfo, &gttLen) != ITS_SUCCESS)
    {
        SCCP_ERROR(("SCRCHandleSCOCMsg:  Couldn't decode addr\n"));

        return (ITS_EINVALIDARGS);
    }

    if (mType != SCCP_MSG_CR)
    {
        if (!(addrInd & SCCP_CPA_HAS_PC))
        {
            pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
       }

        /* we never do GTT for this, as we got a CC,
         * and we recorded the calling party from that */
        if (!(addrInd & SCCP_CPA_HAS_SSN))
        {
            SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                        "undeliverable (no SSN).\n"));

            SCCP_Alarm_ANSI(644, __FILE__, __LINE__, "Message Type: %d", mType);

            return (ITS_EMISSMAND);
        }
        else
        {
            /* local delivery? */
           // if (SCCP_IsSSNEquipped((addrInd & SCCP_CPA_ROUTE_NAT), pc, ssn))
            if (SCCP_IsSSNEquipped(((MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK)), pc, ssn))
            {
                return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                        addrInd, pc, ssn);
            }
            else
            {
                return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                         addrInd, pc, ssn);
            }
        }
    }
    else
    {
        /*
         * This is an outbound connection request.
         *
         * If we are an intermediate node, we formulated this
         * based on the received connection request handled
         * as an MTP3 indication via DeliverMTP3Ind.
         */
        /* is GTT? */
        if (addrInd & SCCP_CPA_ROUTE_SSN)
        {
            /* No. */
            if (addrInd & SCCP_CPA_HAS_SSN)
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }

                //if (SCCP_IsSSNEquipped((addrInd & SCCP_CPA_ROUTE_NAT), 
                if (SCCP_IsSSNEquipped((MTP3_HDR_GET_SIO(*mtp3) & MTP3_NIC_MASK), 
                                        pc, ssn))
                {
                    return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                            addrInd, pc, ssn);
                }
                else
                {
                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ssn);
                }
            }
            else
            {
                SCCP_ERROR(("SCRCHandleSCLCMsg: Package is "
                            "undeliverable (no SSN).\n"));

                SCCP_Alarm_ANSI(644, __FILE__, __LINE__, "Message Type: %d", mType);
        
                return (ITS_EMISSMAND);
            }
        }
#ifdef ASHUTOSH

        else
        {
            /* We (IntelliSS7) cannot deliver without SSN. */
            if (addrInd & SCCP_CPA_HAS_SSN)
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }
                if (SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), pc, ssn))
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverLocal(mtp3, mType, ies, ieCount,
                                            addrInd, pc, ssn);
                }
                else
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Remote pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ssn);
                }
            }
            else
            {
                if (!(addrInd & SCCP_CPA_HAS_PC))
                {
                    pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
                }

                if (!SCCP_IsSSNEquipped_ANSI((addrInd & SCCP_CPA_ROUTE_NAT), 
                                              pc, ITS_SS7_DEFAULT_SSN))
                {
                    SCCP_DEBUG(("SCRCHandleSCLCMsg: SCLC Local pc %08x ssn %02x\n",
                                pc, ssn));

                    return SCRCDeliverRemote(mtp3, mType, ies, ieCount,
                                             addrInd, pc, ITS_SS7_DEFAULT_SSN);
                }

                return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                        pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen,ITS_FALSE);
            }
        }
#endif
      else
    {

      if (!(addrInd & SCCP_CPA_HAS_PC))
           {
                pc = MTP3_RL_GET_DPC_VALUE(mtp3->label);
           }
      return SCRCDeliverByGTT(mtp3, mType, ies, ieCount, addrInd,
                                        pc, ITS_SS7_DEFAULT_SSN, gttInfo, gttLen,ITS_FALSE);

    }

  }


}


