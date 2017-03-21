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
 *  ID: $Id: ansi-sprc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
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
 * LOG: Revision 9.4  2005/04/08 09:27:34  snagesh
 * LOG: Fix for compilation issue while using cc compiler
 * LOG:
 * LOG: Revision 9.3  2005/04/06 10:46:13  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:21  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:33  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.15  2005/03/21 13:53:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.14.2.2.2.2.12.1  2005/02/03 12:56:57  ssingh
 * LOG: Bug number #1403, #1415 fix. (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.14.2.2.2.2  2004/01/20 08:56:32  sjaddu
 * LOG: Removed sctp specific changes made for tcs.
 * LOG:
 * LOG: Revision 7.14.2.2.2.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.14.2.1.2.4  2003/10/27 08:35:07  akumar
 * LOG: Introduced msg based pegs.
 * LOG:
 * LOG: Revision 7.14.2.1.2.3  2003/10/21 06:19:25  akumar
 * LOG: Pause/Resume/Status handling to appl is done.
 * LOG:
 * LOG: Revision 7.14.2.1.2.2  2003/10/10 14:50:59  sjaddu
 * LOG: sctp specific changes are done.
 * LOG:
 * LOG: Revision 7.14.2.1.2.1  2003/09/13 06:23:33  akumar
 * LOG: Msg based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.14.2.1  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.11  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.10  2003/04/24 12:39:32  akumar
 * LOG: Roll-back the Message Priority Procedures.
 * LOG:
 * LOG: Revision 8.9  2003/04/16 06:01:39  akumar
 * LOG: Congestion Related Changes.
 * LOG:
 * LOG: Revision 8.8  2003/04/14 13:52:32  ssingh
 * LOG: Debug statement in sendCQR function added.
 * LOG:
 * LOG: Revision 8.7  2003/04/10 06:46:49  ssingh
 * LOG: Message Proirity (EF bits of SIO) related changes done.
 * LOG:
 * LOG: Revision 8.6  2003/04/10 05:45:47  ssingh
 * LOG: Core Dump removed: Sending CQR for received CQM in unquipped CIC.
 * LOG:
 * LOG: Revision 8.5  2003/04/04 07:09:43  ssingh
 * LOG: ISUP_ReleaseCicMsgBuf related changes done.
 * LOG:
 * LOG: Revision 8.4  2003/03/26 12:11:20  ssingh
 * LOG: Changed done as per ISUPPending List:
 * LOG: ansi-isup_alarms.c  : New Alarms added for HandleMTP3MgmtMsg.
 * LOG: ansi-isup_context.c : Function calls for DPC and Remote ISUP status.
 * LOG:                     : Indication sent; if msg received is on BAD Cic.
 * LOG:                     : Alarms for PAUSE/RESUME/STATUS.
 * LOG: ansi-isup_ifc.c     : Changes to incorporate CIC_INFO changes.
 * LOG: ansi-sprc.c         : CIC_INFO/CIC_MSG_INFO related changes.
 * LOG:                     : SendConfToApp removed, SendIsupIndToApp added.
 * LOG: isup_data.c         : Modified to include CIC_INFO/CIC_MSG_INFO changes.
 * LOG: its-ansi-isup.c     : CIC_INFO related changes.
 * LOG:
 * LOG: Revision 8.3  2003/03/15 12:42:03  ssingh
 * LOG: SPRC_SendCRAToMTP3 added to support CRM/CRA messaging for ANSI.
 * LOG:
 * LOG: Revision 8.2  2003/02/13 21:39:12  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:22  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.14  2003/02/11 14:47:24  akumar
 * LOG: Removed ITS_EVENT_TERM(), while sending ind to Appl
 * LOG:
 * LOG: Revision 7.13  2003/01/29 12:23:34  ssingh
 * LOG: Changed expression for calculating offset value after filling vcic.
 * LOG:
 * LOG: Revision 7.12  2003/01/21 15:28:22  vnitin
 * LOG: Porting to Tandem, also merging Congestion change done by akumar
 * LOG:
 * LOG: Revision 7.10  2003/01/17 15:29:11  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.9  2002/12/27 06:53:02  ssingh
 * LOG: SendCVR is added and SendCQR is changed.
 * LOG:
 * LOG: Revision 7.8  2002/12/06 05:04:04  akumar
 * LOG: Removed unwanted TABS
 * LOG:
 * LOG: Revision 7.7  2002/11/25 15:26:54  ssingh
 * LOG: Changed Send CFN procedure for ext-bit of CAUSE_VALUE.
 * LOG:
 * LOG: Revision 7.6  2002/11/20 14:10:48  sjaddu
 * LOG: Added Added Cic in the Indication,error ,time out events.
 * LOG:
 * LOG: Revision 7.5  2002/11/12 06:35:14  akumar
 * LOG: Added Automatic Congestion Control Procedures
 * LOG:
 * LOG: Revision 7.4  2002/10/30 10:33:37  sjaddu
 * LOG: Added continuity functions.
 * LOG:
 * LOG: Revision 7.3  2002/10/25 13:46:43  ssingh
 * LOG: Code changes done as a part of BUG 141-to-146 fixing.
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:48:01  sjaddu
 * LOG: Added PEGS for ANSI ISUP.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.4  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.3.2.12  2002/07/31 20:49:33  sjaddu
 * LOG: cfn , mtp3 indications testing.
 * LOG:
 * LOG: Revision 6.3.2.11  2002/07/18 18:52:07  ssingh
 * LOG: Added New Functions to send CSC group messages to L3.
 * LOG:
 * LOG: Revision 6.3.2.10  2002/07/12 14:05:26  hbalimid
 * LOG: CQM moved to CSC.
 * LOG:
 * LOG: Revision 6.3.2.9  2002/07/11 17:24:26  hbalimid
 * LOG: SPRC circuit query added.
 * LOG:
 * LOG: Revision 6.3.2.8  2002/07/10 14:09:42  ssingh
 * LOG: Resending CSC messages.
 * LOG:
 * LOG: Revision 6.3.2.7  2002/07/09 00:00:15  ssingh
 * LOG: CQR implemented. Bug Fixed.
 * LOG:
 * LOG: Revision 6.3.2.6  2002/07/08 23:45:23  hbalimid
 * LOG: Test call implemented for Received IAM from L3.
 * LOG:
 * LOG: Revision 6.3.2.5  2002/07/08 15:13:47  ssingh
 * LOG: Code changes to fix BUGS during the ANSI92 testing
 * LOG:
 * LOG: Revision 6.3.2.4  2002/07/07 14:06:56  hbalimid
 * LOG: modified SPRC_SendRLCToMTP3_ANSI.
 * LOG:
 * LOG: Revision 6.3.2.3  2002/07/05 23:26:43  ssingh
 * LOG: Added CGU and CGB.
 * LOG:
 * LOG: Revision 6.3.2.2  2002/07/05 21:57:55  hbalimid
 * LOG: Send CVT to MTP3 added.
 * LOG:
 * LOG: Revision 6.3.2.1  2002/06/29 20:16:23  ssharma
 * LOG: Put CIC in event to application
 * LOG:
 * LOG: Revision 6.3  2002/06/28 16:11:08  ssingh
 * LOG: Changes for ANSI ISUP.
 * LOG:
 * LOG: Revision 6.2  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.1  2002/05/20 22:15:33  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 *
 *****************************************************************************/

#ident "$Id: ansi-sprc.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $"

#undef ANSI
#undef CCITT
#define ANSI

#include <string.h>
#include <stdlib.h>

#include <its.h>

#include <ansi/isup.h>
#include <isup_variants.h>
#include <isup_intern.h>

static void ISUP_SetMessagePriority(ITS_OCTET msgType, ITS_OCTET *sio);
static void ISUP_IncrementSentPegs(ISUP_OPC_DPC_INFO *config_info,
                                   ITS_OCTET msgType);

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an ISUP msg to L3 (Network).
 *
 *  Input Parameters:
 *      event: pointer to the event to send.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success
 *      other value for failure
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                         ID::D0010               enhancement 
 *
 *   snagesh   04-08-2005  None                    Fix for compilaton issue
 *                                                 using cc compiler
 *
 ****************************************************************************/
ITSSS7DLLAPI int
SPRC_SendIsupToMTP3_ANSI(ITS_EVENT* event, ITS_CTXT vcic)
{   
    MTP3_HEADER_ANSI mtp3_hdr;
    int result = 0;
    ITS_UINT dpc = 0;
    ITS_OCTET ni;
    ITS_OCTET msgOffset = 0;
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ISUP_OPC_DPC_INFO config_info;
    ITS_OCTET msgType;
    ITS_BOOLEAN isdsmlocal= ITS_TRUE;
    ITS_INT trpId = 0;
    ITS_INT ret = 0;

    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /* Getting dpc from ITS_EVENT */
    memcpy(&mtp3_hdr, &event->data[1], sizeof(MTP3_HEADER_ANSI));
    dpc = MTP3_RL_GET_DPC_VALUE_ANSI(mtp3_hdr.label);
    ni = (ITS_OCTET)(MTP3_HDR_GET_SIO(mtp3_hdr) & MTP3_NIC_MASK);
    
    msgOffset = sizeof(ITS_OCTET) +
                sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT);

    msgType =  event->data[msgOffset];

    /* we know that here we are giving to app */
    event->src = ISUP_SRC_APP;

    dest = ROUTE_SelectApplication(&header, event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
    }
    else
    {
        ISUP_DEBUG(("Dropping the messge here for Vcic= %d\n", vcic ));
        return ITS_SUCCESS;
    }

    /* Set priority of Outgoing Message */
    ISUP_SetMessagePriority(event->data[msgOffset], &event->data[1]);

    /*
     * We do not use SSN (since we do not support, for now, ISUP over SCCP).
     * What can we do if we fail to send the msg. not much!
     */
    event->src = ITS_ISUP_ANSI_SRC;

    result = !ITS_SUCCESS;

    /* extract the TransportId from DpcTransport table*/
    if (ISUP_DpcTransFindEntry(dpc, &trpId) == ITS_SUCCESS)
    {
        if (trpId == DO_ROUTE_CONTEXT)
        {
            ITS_BOOLEAN isUp = ITS_FALSE;

            /* Get the state and return value
             * If the return value is ITS_ENOROUTE than border Transport is
             * INTELLINET MTP3

             * If the return value is ITS_SUCCESS than transport is IMAL/SCTP.
             * In this case isUp flag is checked to see whether transport
             * is up/down */

            ret = ROUTE_GetRouteContextState(dpc ,&isUp, ROUTE_DPC_SIO,
                                             FAMILY_ANSI,
                                             ROUTE_SIO_ISUP | ni,
                                             ITS_SS7_DEFAULT_LINK_SET,
                                             ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_LINK_PRI);

            if (ret == ITS_SUCCESS && isUp )
            {
                /* Get the TransportId for this route style*/
                trpId = ROUTE_RouteContextExists(dpc , ROUTE_DPC_SIO,
                                                 FAMILY_ANSI,
                                                 ROUTE_SIO_ISUP | ni,
                                                 ITS_SS7_DEFAULT_LINK_SET,
                                                 ITS_SS7_DEFAULT_LINK_CODE,
                                                 ITS_SS7_DEFAULT_LINK_PRI);
            }
            else if (ret == ITS_ENOROUTE)
            {
                trpId = ITS_MTP3_SRC;
            }
            else
            {
                trpId = DO_ROUTE_CONTEXT;
            }

            /* update the TrasportId */
            ISUP_DpcTransUpdateEntry(dpc, trpId);
        }

        if (trpId != DO_ROUTE_CONTEXT)
        {
            result = TRANSPORT_PutEvent(trpId, event);
            if (result != ITS_SUCCESS)
            {
                ISUP_CRITICAL(("SPRC_SendIsupToMTP3_ANSI: PutEvent Failed "
                               " TransportId = %d\n", trpId));

                /* Set the TransportId to DO_ROUTE_CONTEXT so that
                 * ROUTE_GetRouteContextState can be called again */

                trpId = DO_ROUTE_CONTEXT;

                /* update the TrasportId */
                ISUP_DpcTransUpdateEntry(dpc, trpId);
            }
            else
            {
                ISUP_DEBUG(("SPRC_SendIsupToMTP3_ANSI: Success "
                             " TransportId = %d\n", trpId ));
            }
        }
    }

    if (result != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendIsupToMTP3_ANSI: Failed (%d) to send msg to"
                       " dpc: %d.\n", result, dpc));
    }
    else
    {
        ISUP_FindOpcDpc(mtp3_hdr, &config_info, isdsmlocal);
        ISUP_IncrementSentPegs(&config_info, msgType);
        PEG_IncrPeg(ANSI_ISUP_Pegs, PEG_ISUP_TOT_MSGS_SENT);
        ISUP_UpdateOpcDpc(&config_info);
        ISUP_ReleaseOpcDpc(&config_info);
    }
    return result;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an ISUP msg to Application (Worker thread).
 *
 *  Input Parameters:
 *      vcic - The virtual cic used by the Routing Subsystem.
 *      event - pointer to the event received from MTP3.
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
 *      The format of the event sent to the application is:
 *        ISUPMsgType:CIC:MTP3_HEADER:EncodedISUPMsg.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendIsupToApp_ANSI(ITS_CTXT vcic, ITS_EVENT* event)
{
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, index = 0, offset = 0, ret;

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /* 
     * Reformat ITS_EVENT as required by App 
     */
    /* The new length does not include the MTP3MsgType */
    len = (ITS_INT)(event->len - sizeof(ITS_OCTET) + sizeof(ITS_CTXT));

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT);
    ev.data[offset++] = event->data[index];

    ITS_SET_CTXT(&ev.data[offset], vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = event->data[sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)];
    ev.data[offset++] = event->data[sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)
                                                      + sizeof(ITS_OCTET)];

    /* Put in the MTP3_HEADER */
    memcpy(&ev.data[offset], &event->data[1], sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Rest of the Encoded ISUP msg */
    index += sizeof(ITS_OCTET);
    memcpy(&ev.data[offset], &event->data[index], (event->len - index));
   
    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward ISUP msg to App thread [0x%04x] (vcic: %d).\n",
                    dest, vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC_SendIsupToApp_ANSI: Unable to send ISUP msg"
                    " to APP (vcic: %d).\n", vcic));
    }
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a timeout indication to Application (Worker thread).
 *
 *  Input Parameters:
 *      vcic - The virtual cic used by the Routing Subsystem.
 *      tdata - pointer to the timer data.
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
 *      The format of the event sent to the application is:
 *        ISUPMsgType:CIC:MTP3Header:TimerData.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendTimeoutIndicToApp_ANSI(ITS_CTXT vcic, ISUP_TIMER_ENTRY* tdata)
{
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0, ret;
    MTP3_HEADER mtp_hdr;

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /* Setting mtp header */
    ISUP_SET_MTP3_HEADER(mtp_hdr, tdata->sio, tdata->opc, tdata->dpc,
                         (ITS_OCTET)(tdata->cic & 0x000F))
    /* 
     * Format ITS_EVENT as required by App 
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_TIMER_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_TIM;

    ITS_SET_CTXT(&ev.data[offset], vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = (ITS_OCTET)(tdata->cic & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((tdata->cic >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Timer data */
    memcpy(&ev.data[offset], tdata, sizeof(ISUP_TIMER_ENTRY));
   
    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward timeout indication to App thread [0x%04x]"
                    " (vcic: %d).\n", dest, vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Unable to send timeout indication "
                    " to APP (vcic: %d).\n", vcic));
    }

}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an Error msg to Application (Worker thread). This is
 *      caused by an error occuring in the stack, or detected in the stack.
 *
 *  Input Parameters:
 *      vcic     - The VCIC to be sent to the Application.
 *      congdata - Information about Congestion in the stack. 
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
ITSSS7DLLAPI void
SPRC_SendLocCongIndicToApp_ANSI(ITS_CTXT vcic, ISUP_CONGESTION_ENTRY *congdata)
{
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0, ret;
    MTP3_HEADER mtp_hdr;

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /* Setting mtp header */
    ISUP_SET_MTP3_HEADER(mtp_hdr, congdata->sio, congdata->opc, congdata->dpc,
                         (ITS_OCTET)(ITS_ISUP_INV_CIC & 0x000F))
    /*
     * Format ITS_EVENT as required by App
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_CONGESTION_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_LCONG;

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = (ITS_OCTET)(ITS_ISUP_INV_CIC & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((ITS_ISUP_INV_CIC >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Local Cong Data */
    memcpy(&ev.data[offset], congdata, sizeof(ISUP_CONGESTION_ENTRY));

    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward local cong indication to App thread [0x%04x]"
                    " (vcic: %d).\n", dest, vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Unable to send local cong indication "
                    " to APP.\n"));
    }
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an Error msg to Application (Worker thread). This is 
 *      caused by an error occuring in the stack, or detected in the stack.
 *
 *  Input Parameters:
 *      errId - The Error ID to be sent to the Application.
 *      cic_rec - The CIC record for which this error is being generated.
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
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendErrorToApp_ANSI(ITS_OCTET msgType,
                          ITS_UINT errId, ISUP_CIC_INFO *cic_rec)
{
    ISUP_ERROR_ENTRY err_entry;
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0, ret;
    MTP3_HEADER mtp_hdr;

    memset((char*)&err_entry, 0, sizeof(ISUP_ERROR_ENTRY));
    
    /* Fill in Error data to be sent to app. */
    err_entry.errorId = errId;
    err_entry.msgType = msgType;
    err_entry.cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);
    err_entry.sio = ISUP_PCIC_TO_SIO(cic_rec->pcic);
    err_entry.opc = ISUP_PCIC_TO_OPC(cic_rec->pcic);
    err_entry.dpc = ISUP_PCIC_TO_DPC(cic_rec->pcic);

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = cic_rec->vcic;

    /* Setting mtp header */
    ISUP_SET_MTP3_HEADER(mtp_hdr, err_entry.sio, err_entry.opc,
                         err_entry.dpc, (ITS_OCTET)(err_entry.cic & 0x000F))
    /* 
     * Format ITS_EVENT as required by App 
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_ERROR_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_ERR;

    ITS_SET_CTXT(&ev.data[offset], cic_rec->vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = (ITS_OCTET)(cic_rec->pcic.cic & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((cic_rec->pcic.cic >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Error data */
    memcpy(&ev.data[offset], &err_entry, sizeof(ISUP_ERROR_ENTRY));
   
    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);
 
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward error indication to App thread [0x%04x]"
                    " (vcic: %d).\n", dest, cic_rec->vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Unable to send error indication "
                    " to APP (vcic: %d).\n", cic_rec->vcic));
    }

}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an  Indication to Application (Worker thread) from stack.
 *
 *  Input Parameters:
 *      indId - The Indication ID to be sent to the Application.
 *      cic_rec - The CIC record for which this indication is being generated.
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
ITSSS7DLLAPI void
SPRC_SendIndToApp_ANSI(ITS_UINT indId, ISUP_CIC_INFO *cic_rec)
{
    ISUP_INDICATION_ENTRY ind_entry;
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0, ret;
    MTP3_HEADER mtp_hdr;

    memset((char*)&ind_entry, 0, sizeof(ISUP_INDICATION_ENTRY));

    /* Fill in Indication data to be sent to app. */
    ind_entry.indId = indId;
    ind_entry.cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);
    ind_entry.sio = ISUP_PCIC_TO_SIO(cic_rec->pcic);
    ind_entry.opc = ISUP_PCIC_TO_OPC(cic_rec->pcic);
    ind_entry.dpc = ISUP_PCIC_TO_DPC(cic_rec->pcic);

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = cic_rec->vcic;

    /* Setting mtp header */
    ISUP_SET_MTP3_HEADER(mtp_hdr, ind_entry.sio, ind_entry.opc,
                         ind_entry.dpc, (ITS_OCTET)(ind_entry.cic & 0x000F))
    /*
     * Format ITS_EVENT as required by App
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_INDICATION_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)(len));

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_IND;

    ITS_SET_CTXT(&ev.data[offset], cic_rec->vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT. */
    ev.data[offset++] = (ITS_OCTET)(cic_rec->pcic.cic & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((cic_rec->pcic.cic >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Indication data */
    memcpy(&ev.data[offset], &ind_entry, sizeof(ISUP_INDICATION_ENTRY));

    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward CPC indication to App thread [0x%04x]"
                    " (vcic: %d).\n", dest, cic_rec->vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Unable to send CPC indication "
                    " to APP (vcic: %d).\n", cic_rec->vcic));
    }

}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a REL msg to L3 (network). This is sent if an error 
 *      is detected in the stack, which can be automatically replied to.
 *
 *  Input Parameters:
 *      rel_code - The cause value in the REL message to be sent.
 *      cic_rec - The CIC record for which this REL is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
ITSSS7DLLAPI void
SPRC_SendRELToMTP3_ANSI(ITS_OCTET rel_code, ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    ISUP_OPC_DPC_STAT  *config_stat = NULL;
    ISUP_LOC_CONGES    locCongLevel;
    ITS_BOOLEAN        locCongFound = ITS_FALSE;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    /* Check input release cause parameter */
    if (!rel_code)
    {
        /* bad input params */
        ISUP_ERROR(("SPRC_SendRELToMTP3: No rel_code input. pcic 0x%08x.\n",
                    cic_rec->pcic));
        return;
    }


    /* Get the local congestion level */
    config_stat = ISUP_FindOpcDpcStat(config_info->opc_dpc_ni, isdsmlocal);
    locCongLevel = ISUP_GET_OPC_DPC_LOC_CONG(config_stat);
    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

    /*
     * Encode the params for REL msg to be sent.
     */

    if (locCongLevel == ISUP_LOC_CONGES_OFF)
    {
        memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 2);
    }
    else
    {
        memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);
        locCongFound = ITS_TRUE;
    }

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CAUSE_INDICATORS;
    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                   CI_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                           CI_CS_ANSI);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                         CI_EXTEND);
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                 rel_code);
    ies[index].param_length = 2;

    index++;
    
    /* Fill in the optional Automatic Congestion Level parameter
     * based on the if the congestion is there and type of congestion
     */
    if (locCongFound)
    {
        ies[index].param_id = ISUP_PRM_AUTO_CONGEST_LEVEL;
        ies[index].param_length = 1;

        switch (locCongLevel)
        {
             case ISUP_LOC_CONGES_LEVEL1:
                  ies[index].param_data.autoCongestionLevel.level = AUTO_CONGESTION_LEVEL1;
                  break;

             case ISUP_LOC_CONGES_LEVEL2:
                  ies[index].param_data.autoCongestionLevel.level = AUTO_CONGESTION_LEVEL2;
                  break;

             case ISUP_LOC_CONGES_OFF:
             default:
                  ies[index].param_data.autoCongestionLevel.level = AUTO_CONGESTION_OFF;
                  break;
        }
        index++;
    }
    
    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_REL, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRELToMTP3: Failed (%d) to encode REL to dpc %d,"
                       " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_REL;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* store the event in cic_rec for resends */
    memcpy(cic_rec->cpc_msg, event.data, event.len);
    cic_rec->cpc_msg_len = event.len;

    /*
     * Send the ITS_EVENT with REL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRELToMTP3: Failed (%d) to send REL to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
       ISUP_DEBUG(("SPRC_SendRELToMTP3: Sent REL to L3."
                   " Result = %s, dpc %d, cic 0x%04x.\n",
                     ITS_GetErrorText(ret), dpc_val, cic));
       PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_REL_ABNORMAL);
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will resend a REL msg to L3 (network).
 *
 *  Input Parameters:
 *      cic_rec - The record CIC for which this REL is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_ResendRELToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;

    ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_rec->cpc_msg_len);
    memcpy((void *)(event.data), cic_rec->cpc_msg, cic_rec->cpc_msg_len);

    /*
     * Send the ITS_EVENT with REL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendRELToMTP3: Failed (%d) to resend REL"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a UCIC msg to L3 (network). This is sent if an error 
 *      is detected in the stack, which can be automatically replied to.
 *
 *  Input Parameters:
 *      cic - The CIC for which this UCIC is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendUCICToMTP3_ANSI(ITS_USHORT cic, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UCIC;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UCIC */

    /* 
     * Send the ITS_EVENT with UCIC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, ITS_ISUP_INV_VCIC);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendUCICToMTP3: Failed (%d) to send UCIC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendUCICToMTP3: Sending UCIC to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a BLO msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this BLO is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendBLOToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_BLO;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in BLO */

    /* 
     * Send the ITS_EVENT with BLO to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendBLOToMTP3: Failed (%d) to send BLO to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendBLOToMTP3: Sending BLO to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a UBL msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this UBL is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendUBLToMTP3_ANSI(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UBL;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UBL */

    /* 
     * Send the ITS_EVENT with UBL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendUBLToMTP3: Failed (%d) to send UBL to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendUBLToMTP3: Sending UBL to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a BLA msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this BLA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendBLAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_BLA;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in BLA */

    /* 
     * Send the ITS_EVENT with BLA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendBLAToMTP3: Failed (%d) to send BLA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendBLAToMTP3: Sending BLA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a UBA msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this UBA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendUBAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UBA;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UBA */

    /* 
     * Send the ITS_EVENT with UBA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendUBAToMTP3: Failed (%d) to send UBA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendUBAToMTP3: Sending UBA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will resend a CGB msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic_rec - The record CIC for which this CGB is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_ResendCGBToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_msg->cgb_msg_len);
    memcpy((void *)(event.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    /* 
     * Send the ITS_EVENT with CGB to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendCGBToMTP3: Failed (%d) to resend CGB"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendCGBToMTP3_ANSI: Sending CGB to L3."
                    " Result = %s, pcic 0x%08x, vcic 0x%04x.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will resend a CGU msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic_rec - The record CIC for which this CGU is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_ResendCGUToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_msg->cgu_msg_len);
    memcpy((void *)(event.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    /* 
     * Send the ITS_EVENT with CGU to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendCGUToMTP3_ANSI: Failed (%d) to resend CGU"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendCGUToMTP3_ANSI: Sending CGU to L3."
                    " Result = %s, pcic 0x%08x, vcic 0x%04x.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will resend a GRS msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic_rec - The record CIC for which this CGU is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_ResendGRSToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, ITS_TRUE);

    ITS_EVENT_INIT(&event, ITS_ISUP_ANSI_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, ITS_TRUE);

    /* 
     * Send the ITS_EVENT with GRS to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendGRSToMTP3: Failed (%d) to resend GRS"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendGRSToMTP3_ANSI: Sending GRS to L3."
                    " Result = %s, pcic 0x%08x, vcic 0x%04x.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a RSC msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this RSC is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendRSCToMTP3_ANSI(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_RSC;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in RSC */

    /* 
     * Send the ITS_EVENT with RSC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRSCToMTP3: Failed (%d) to send RSC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendRSCToMTP3_ANSI: Sending RSC to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a RLC msg to L3 (network). This is sent if an error 
 *      is detected in the stack, which can be automatically replied to.
 *
 *  Input Parameters:
 *      cic_rec - The CIC record for which this REL is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendRLCToMTP3_ANSI(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_RLC;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in RLC */

    /* 
     * Send the ITS_EVENT with RLC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRLCToMTP3: Failed (%d) to send RLC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendRLCToMTP3_ANSI: Sending RLC to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CRA msg to L3 (network). This is sent in respose 
 *      to CRM received from Network to Resurve the CIC for further callp.
 *
 *  Input Parameters:
 *      cic_rec - The CIC record for which this REL is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCRAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CRA;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in RLC */

    /* 
     * Send the ITS_EVENT with RLC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCRAToMTP3: Failed (%d) to send CRA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCRAToMTP3_ANSI: Sending CRA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an indication to Application (Worker thread).
 *      Irrespective of any cic_rec associated with.
 *
 *  Input Parameters:
 *      indId - The indication ID to be sent to the Application.
 *      event - Event resulting this indication.
 *      src   - Event src.
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
ITSSS7DLLAPI void 
SPRC_SendIsupIndToApp_ANSI(ITS_UINT indId, ITS_EVENT* event, ITS_OCTET src)
{
    ISUP_INDICATION_ENTRY ind_entry;
    MTP3_HEADER           header;
    ITS_USHORT            dest = 0;
    ITS_HDR               hdr;
    ITS_EVENT             ev;
    int                   len = 0, ret;
    int                   rcvd_offset = 0, send_offset = 0;
    ITS_USHORT            cic = 0;
    ITS_UINT              opc = 0, dpc = 0;
    ITS_OCTET             sio;

    /* Getting cic out of event */
    rcvd_offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_ANSI);

    /* Getting the CIC */
    cic |= event->data[rcvd_offset]; 
    cic |= event->data[rcvd_offset+1] << 8;

    /* Getting sio/opc/dpc out of event mtp3 header*/
    memset((char*)&header, 0, sizeof(MTP3_HEADER_ANSI));
    memcpy(&header, &event->data[1], sizeof(MTP3_HEADER_ANSI));

    sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(header) & 
                     (MTP3_SIO_UP_MASK|MTP3_NIC_MASK));

    if (src == ISUP_SRC_L3_ANSI)
    {
        opc = MTP3_RL_GET_DPC_VALUE_ANSI(header.label);
        dpc = MTP3_RL_GET_OPC_VALUE_ANSI(header.label);
    }
    else
    {
        dpc = MTP3_RL_GET_DPC_VALUE_ANSI(header.label);
        opc = MTP3_RL_GET_OPC_VALUE_ANSI(header.label);
    }

    memset((char*)&ind_entry, 0, sizeof(ISUP_INDICATION_ENTRY));

    /* Fill in Indication data to be sent to app. */
    ind_entry.indId = indId;
    ind_entry.cic = cic;
    ind_entry.sio = sio;
    ind_entry.opc = opc;
    ind_entry.dpc = dpc;

    /* Setting the event Header context*/
    memset((char*)&hdr, 0, sizeof(ITS_HDR));
    hdr.type = ITS_ISUP;

    hdr.context.cic = 0;

    /* Format ITS_EVENT as required by App */

    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_INDICATION_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)(len));

    /* Put in the ISUPMsgType */
    ev.data[send_offset++] = ISUP_MSG_IND;

    ITS_SET_CTXT(&ev.data[send_offset], 0);
    send_offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[send_offset++] = (ITS_OCTET) event->data[rcvd_offset];
    ev.data[send_offset++] = (ITS_OCTET) event->data[rcvd_offset+1] << 8;

    /* Put mtp header */
    memcpy(&ev.data[send_offset], &header, sizeof(MTP3_HEADER));
    send_offset += sizeof(MTP3_HEADER);

    /* Indication data */
    memcpy(&ev.data[send_offset], &ind_entry, sizeof(ISUP_INDICATION_ENTRY));

    /* Getting the destination */
    dest = ROUTE_SelectApplication(&hdr, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Send ISUP indication to App [0x%04x] (vcic: %d).\n",
                    dest, 0));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Send ISUP indication to APP Failed (vcic: %d)\n",0));
    }
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CFN msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CFN is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCFNToMTP3_ANSI(ITS_OCTET cause_ind,
                         ITS_OCTET msgType,
                         ITS_USHORT cic,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[2];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0;
    ITS_UINT dpc_val = 0;

    /* Check input release cause parameter */
    if (!cause_ind)
    {
        /* bad input params */
        ISUP_ERROR(("SPRC_SendCFN: No rel_code input. pcic 0x%08x.\n",
                    cic));
        return;
    }

    /*
     * Encode the params for CFN msg to be sent.
     */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 2);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CAUSE_INDICATORS;

    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index]. \
                            param_data.causeIndicator, CI_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[index]. \
                            param_data.causeIndicator, CI_CS_ANSI);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[index]. \
                            param_data.causeIndicator, CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index]. \
                            param_data.causeIndicator, CI_NO_EXTEND );
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[index]. \
                            param_data.causeIndicator, cause_ind);
    ies[index].param_data.causeIndicator.diagnostics[0] = msgType;
    ies[index].param_length = 3;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                     MTP3_RL_GET_DPC_VALUE_ANSI(config_info->opc_dpc_ni.label));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                     MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CFN, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCFN: Failed (%d) to encode CFN to dpc %d,"
                       " cic 0x%08x.\n", ret, dpc_val, cic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

   /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CFN;


    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CFN to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, ITS_ISUP_INV_VCIC);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCFNToMTP3: Failed (%d) to send CFN to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCFNToMTP3: Sending CFN to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CGU msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CGU is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCGUToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info,
                        ISUP_RANGE_AND_STATUS rs_ie,
                        ITS_OCTET sup_msg_type)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Encode the params for CGB msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = sup_msg_type;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;
    memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 3);

    ies[index].param_length = 4;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CGU, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGUToMTP3: Failed (%d) to encode CGU to dpc "
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGU;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* store the event in cic_msg for resends */
    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);
    memcpy(cic_msg->cgu_msg, event.data, event.len);
    cic_msg->cgu_msg_len = event.len;
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

    /*
     * Send the ITS_EVENT with CGU to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGUToMTP3: Failed (%d) to send CGU to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCGUToMTP3: Sending CGU to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CGB msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CGB is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCGBToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info,
                        ISUP_RANGE_AND_STATUS rs_ie,
                        ITS_OCTET sup_msg_type)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* Encode the params for CGB msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = sup_msg_type;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;
    memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 3);

    ies[index].param_length = 4;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CGB, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGBToMTP3: Failed (%d) to encode CGB to dpc "
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGB;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* store the event in cic_msg for resends */
    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, ITS_TRUE);
    memcpy(cic_msg->cgb_msg, event.data, event.len);
    cic_msg->cgb_msg_len = event.len;
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_TRUE);

    /*
     * Send the ITS_EVENT with CGB to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGBToMTP3: Failed (%d) to send CGB to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCGBToMTP3: Sending CGB to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CVT msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which this UBA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCVTToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CVT;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in CVT */

    /* 
     * Send the ITS_EVENT with CVT to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCVTToMTP3: Failed (%d) to send CVT to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCVTToMTP3: Sending CVT to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CQR msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CQR is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCQRToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ITS_ISUP_IE* rs_ie,
                         ITS_USHORT cic)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0;
    ITS_UINT dpc_val = 0;
    ITS_OCTET cic_state[32];
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;

    for (i = 0; i <= rs_ie->param_data.rangeAndStatus.range; i++)
    {
        if (i == 0)
        {
            affected_cic_rec = cic_rec;
        }
        else
        {
            opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
            dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);
            ni = MTP3_HDR_GET_SIO(config_info->opc_dpc_ni);

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, (ITS_USHORT)(cic + i));
            affected_cic_rec = ISUP_FindPcic(pcic, ITS_TRUE);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
            cic_state[i] = 0x03;
        }
        else
        {
            cic_state[i] = affected_cic_rec->cic_state;

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != cic) 
            {
                ISUP_ReleaseCic(affected_cic_rec, ITS_TRUE);
            }
        }
    }

    /*
     * Encode the params for CQR msg to be sent.
     */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range =
                          rs_ie->param_data.rangeAndStatus.range;
    ies[index].param_length = 1;

    index++;

    /* Fill in circuit state indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_STATE_INDICATOR;
    for (i = 0; i <= rs_ie->param_data.rangeAndStatus.range; i++)
    {
        ies[index].param_data.circuitStateIndicators.states[i] = cic_state[i];
    }
    ies[index].param_length = (ITS_OCTET)(rs_ie->param_data.rangeAndStatus.range
                                          + 1);

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    if(cic_rec != NULL)
    {
        MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                   ISUP_PCIC_TO_OPC(cic_rec->pcic));
        MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                   ISUP_PCIC_TO_DPC(cic_rec->pcic));
    }
    else
    {
        opc = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);
        dpc = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);
        MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                   dpc);
        MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                   opc);
    }

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */


    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CQR, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCQRToMTP3: Failed (%d) to encode CQR to dpc %d," 
                       " cic 0x%08x.\n", ret, dpc_val, cic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CQR;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CQR to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCQRToMTP3: Failed (%d) to send CQR to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCQRToMTP3: Sending CQR to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                      ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}


/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will return the circuit status
 *
 *  Input Parameters:
 *      cic_rec - The CIC record on which query is needed
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
ITSSS7DLLAPI ITS_OCTET
SPRC_QueryCircuitStatus(const ISUP_CIC_INFO *cic_rec)
{

    /* cic_state Bits:
    * H G F E  D C B A
    * 0 0 0 0  0 0 0 0    0x00 - Transient
    * 0 0 0 0  0 0 0 1    0x01 - Spare (no interpretation)
    * 0 0 0 0  0 0 1 0    0x02 - Spare (no interpretation)
    * 0 0 0 0  0 0 1 1    0x03 - Unequipped
    * 0 0 0 0  0 1 0 0    0x04 - (CPC) Incoming Busy, (MPC) Active
    * 0 0 0 0  0 1 0 1    0x05 - (CPC) Incoming Busy, (MPC) Locally Blocked
    * 0 0 0 0  0 1 1 0    0x06 - (CPC) Incoming Busy, (MPC) Remotely Blocked 
    * 0 0 0 0  0 1 1 1    0x07 - (CPC) Incoming Busy, (MPC) Loc & Rem Blocked
    * 0 0 0 0  1 0 0 0    0x08 - (CPC) Outgoing Busy, (MPC) Active
    * 0 0 0 0  1 0 0 1    0x09 - (CPC) Outgoing Busy, (MPC) Locally Blocked
    * 0 0 0 0  1 0 1 0    0x0A - (CPC) Outgoing Busy, (MPC) Remotely Blocked
    * 0 0 0 0  1 0 1 1    0x0B - (CPC) Outgoing Busy, (MPC) Loc & Rem Blocked
    * 0 0 0 0  1 1 0 0    0x0C - (CPC) Idle,          (MPC) Active
    * 0 0 0 0  1 1 0 1    0x0D - (CPC) Idle,          (MPC) Locally Blocked
    * 0 0 0 0  1 1 1 0    0x0E - (CPC) Idle,          (MPC) Remotely Blocked
    * 0 0 0 0  1 1 1 1    0x0F - (CPC) Idle,          (MPC) Loc & Rem Blocked
    */

    /* Better to get the whole cic record from calling function
     * Infuture we might need some other members of this cic record
     */

    switch(cic_rec->cic_state)
    {
        case 0x00: /* Transient */
            return (SPRC_CKTS_TRANSIENT);

        case 0x01: /* spare (no interpretation) */
            return (SPRC_CKTS_SPARE1);

        case 0x02: /* spare (no interpretation) */
            return (SPRC_CKTS_SPARE2);

        case 0x03: /* Unequipped */
            return (SPRC_CKTS_UNEQUIPPED);

        case 0x04: /* Incoming Circuit Busy, Active */
            return (SPRC_CKTS_INBUSY_ACTIVE);

        case 0x05: /* Incoming Circuit Busy, Locally Blocked */
            return (SPRC_CKTS_INBUSY_LBLOCKED);

        case 0x06: /* Incoming Circuit Busy, Remotely Blocked */
            return (SPRC_CKTS_INBUSY_RBLOCKED);

        case 0x07: /* Incoming Circuit Busy, Locally & Remotely Blocked */
            return (SPRC_CKTS_INBUSY_LRBLOCKED);

        case 0x08: /* Outgoing Circuit Busy, Active */
            return (SPRC_CKTS_OUTBUSY_ACTIVE);

        case 0x09: /* Outgoing Circuit Busy, Locally Blocked */
            return (SPRC_CKTS_OUTBUSY_LBLOCKED);

        case 0x0A: /* Outgoing Circuit Busy, Remotely Blocked */
            return (SPRC_CKTS_OUTBUSY_RBLOCKED);

        case 0x0B: /* Outgoing Circuit Busy, Locally & Remotely Blocked */
            return (SPRC_CKTS_OUTBUSY_LRBLOCKED);

        case 0x0C: /* Idle, local UNblok, remote UNblock*/
            return (SPRC_CKTS_IDLE_ACTIVE);

        case 0x0D: /* Idle, Locally Blocked */
            return (SPRC_CKTS_IDLE_LBLOCKED);

        case 0x0E: /* Idle, Remotely Blocked */
            return (SPRC_CKTS_IDLE_RBLOCKED);

        case 0x0F: /* Idle, Locally & Remotely Blocked */
            return (SPRC_CKTS_IDLE_LRBLOCKED);

        default:
            return (SPRC_CKTS_INVALID);
    }

}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a GRA msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this GRA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendGRAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info,
                        ISUP_RANGE_AND_STATUS rs_ie)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[2];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Encode the params for GRA msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 2);

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;

    if(rs_ie.range != 0)
    {
       memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 3);

       ies[index].param_length = 4;
    }
    else
    {
       ies[index].param_length = 1;
    }

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));

    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_GRA, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendGRAToMTP3: Failed (%d) to encode GRA to dpc "
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_GRA;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with GRA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendGRAToMTP3: Failed (%d) to send GRA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendGRAToMTP3: Sending GRA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CGBA msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CGBA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCGBAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info,
                        ISUP_RANGE_AND_STATUS rs_ie,
                        ITS_OCTET sup_msg_type)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Encode the params for CGBA msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = sup_msg_type;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;

    if(rs_ie.range != 0)
    {
       memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 3);

       ies[index].param_length = 4;
    }
    else
    {
       ies[index].param_length =  1;
    }

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CGBA, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGBAToMTP3: Failed (%d) to encode CGBA to dpc"
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGBA;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CGBA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
       ISUP_CRITICAL(("SPRC_SendCGBAToMTP3: Failed (%d) to send CGBA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCGBAToMTP3: Sending CGBA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CGUA msg to L3 (network).
 *
 *  Input Parameters:
 *      cic - The CIC for which this CGUA is being generated.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCGUAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                        ISUP_OPC_DPC_INFO *config_info,
                        ISUP_RANGE_AND_STATUS rs_ie,
                        ITS_OCTET sup_msg_type)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Encode the params for CGB msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = sup_msg_type;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;
   
    if(rs_ie.range != 0)
    {
       memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 3);

       ies[index].param_length = 4;
    } 
    else
    {
       ies[index].param_length =  1;
    }
    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                                ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data, &len, ISUP_MSG_CGUA, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCGUAToMTP3: Failed (%d) to encode CGUA to dpc "
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (ITS_USHORT)(sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGUA;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CGUA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
       ISUP_CRITICAL(("SPRC_SendCGUAToMTP3: Failed (%d) to send CGUA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCGUAToMTP3: Sending CGUA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

ITSSS7DLLAPI void
SPRC_SendCOTToMTP3_ANSI(ITS_OCTET ind, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET) *2));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_COT;

    event.data[index] = ind;

    /* 
     * Send the ITS_EVENT with COT to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCOTToMTP3: Failed (%d) to send COT to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCOTToMTP3: Sending COT to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

ITSSS7DLLAPI void
SPRC_SendCCRToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index] = ISUP_MSG_CCR;

    /* 
     * Send the ITS_EVENT with CCR to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCCRToMTP3: Failed (%d) to send CCR to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCCRToMTP3: Sending CCR to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

ITSSS7DLLAPI void
SPRC_SendLPAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_ANSI_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER_ANSI));
    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_LPA;

    /* 
     * Send the ITS_EVENT with LPA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendLPA: Failed (%d) to send LPA to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendLPA: Sending LPA to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }


    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a CVR msg to L3 (network). This is sent when CVT is
 *       received on an unequipped cic so can be automatically replied to.
 *
 *  Input Parameters:
 *      cic - The CIC for which CVT received from L3.
 *      config_info - The configuration info for the relevant OPC-DPC pair.
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
SPRC_SendCVRToMTP3_ANSI(ITS_USHORT cic,
                        ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0;
    ITS_UINT opc, dpc;
    ITS_UINT dpc_val = 0;

    /* Encode the params for CVR msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Indicator parameter. */
    ies[index].param_id = ISUP_PRM_CKT_VALIDATION_RESP;
    ies[index].param_length = sizeof(ITS_OCTET);

    /* Valication response is set to Failure */
    ies[index].param_data.circuitValidationResponse.indicator= 01;
    index++;

    /* Fill in other parameter . */
    ies[index].param_id = ISUP_PRM_CKT_GRP_CHARACTERISTIC;
    ies[index].param_length = sizeof(ITS_OCTET);

    /* All Unknown as Circuit is not provisioned in near end */
    ies[index].param_data.circuitGrpCharacteristic.indicator= 00;
    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
           (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER_ANSI));

    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    opc = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);
    dpc = MTP3_RL_GET_OPC_VALUE_ANSI(config_info->out_hdr.label);

    MTP3_RL_SET_DPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                               dpc);
    MTP3_RL_SET_OPC_VALUE_ANSI(ies[index].param_data.routingLabel.label,
                               opc);

    ies[index].param_length = sizeof(MTP3_HEADER_ANSI);

    ieCount = index + 1;  /* array index is one less than the count */

    dpc_val = MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_ANSI(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_ANSI(data,
                               &len,
                               ISUP_MSG_CVR,
                               ies,
                               ieCount,
                               config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCVRToMTP3: Failed (%d) to encode CVR to dpc "
                       "%d\n", ret, dpc_val));
        return;
    }


    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event),
                   (ITS_ISUP_ANSI_SRC),
                   (ITS_USHORT)(sizeof(ITS_OCTET) +
                    sizeof(MTP3_HEADER_ANSI) +
                    sizeof(ITS_USHORT) +
                    sizeof(ITS_OCTET) +
                    len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index],
           (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_ANSI));

    index += sizeof(MTP3_HEADER_ANSI);

    /* Fill in the CIC */
    event.data[index++] = (ITS_OCTET)(cic & 0xFFU); /* LSB 8 bits */
    event.data[index++] = (ITS_OCTET)((cic >> 8) & 0xFFU); /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CVR;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* Send the ITS_EVENT to MTP3. */
    ret = SPRC_SendIsupToMTP3_ANSI(&event, ITS_ISUP_INV_VCIC);

    if (ret != ITS_SUCCESS)
    {
       ISUP_CRITICAL(("SPRC_SendCVRToMTP3: Failed (%d) to send CVR to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendCVRToMTP3: Sending CVR to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }

    return;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function fills priority for ISUP message.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *
 *  Output Parameters:
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
#if defined(ANSI)
static void
ISUP_SetMessagePriority(ITS_OCTET msgType, ITS_OCTET *sio)
{
    *sio = (ITS_OCTET) (*sio & (MTP3_NIC_MASK | MTP3_SIO_UP_MASK));

    switch(msgType)
    {
    /* Following CPC messages; Priority=0 */
    case ISUP_MSG_IAM:
    case ISUP_MSG_CFN:
        *sio |= 0x00;
        break;

    /* Following CPC messages; Priority=1 */
    case ISUP_MSG_REL:
    case ISUP_MSG_ACM:
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
    case ISUP_MSG_CCR:
    case ISUP_MSG_LPA:
    case ISUP_MSG_CPG:
    case ISUP_MSG_COT:
    case ISUP_MSG_FOT:
    case ISUP_MSG_INF:
    case ISUP_MSG_INR:
    case ISUP_MSG_UCIC:
        *sio |= 0x10;
        break;

    /* Following CPC messages; Priority=2 */
    case ISUP_MSG_RLC:
    case ISUP_MSG_ANM:
        *sio |= 0x20;
        break;

    /* Following CSC messages; Priority = 0  */
    case ISUP_MSG_BLO:
    case ISUP_MSG_BLA:
    case ISUP_MSG_UBL:
    case ISUP_MSG_UBA:
    case ISUP_MSG_RSC:
    case ISUP_MSG_CQM:
    case ISUP_MSG_CQR:
    case ISUP_MSG_GRS:
    case ISUP_MSG_GRA:
    case ISUP_MSG_CGB:
    case ISUP_MSG_CGBA:
    case ISUP_MSG_CGU:
    case ISUP_MSG_CGUA:
    case ISUP_MSG_CVT:
    case ISUP_MSG_CVR:
    case ISUP_MSG_CRA:
    case ISUP_MSG_CRM:
        *sio |= 0x00;
        break;

    /* Priority will be of message it contains */
    case ISUP_MSG_PAM:
        break;

    /* Further Study is needed on the exect assignment of priority */
    case ISUP_MSG_FAC:
        break;

    /* Intra network Applications only */
    case ISUP_MSG_EXM:
        break;

    default:
        /* Should Not come here */
        break;
    }
}
#endif

ITSSS7DLLAPI void
SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_CTXT vcic, ISUP_MTP3MGMT_ENTRY *mgmtdata)
{
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0, ret;
    MTP3_HEADER mtp_hdr;

    /* Setting the Header */
    memset((char*)&header, 0, sizeof(ITS_HDR));
    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /* Adjust the user part */
    mgmtdata->sio |= 0x05;

    /* Setting mtp header */
    ISUP_SET_MTP3_HEADER(mtp_hdr, mgmtdata->sio, mgmtdata->opc, mgmtdata->dpc,
                         (ITS_OCTET)(ITS_ISUP_INV_CIC & 0x000F))
    /*
     * Format ITS_EVENT as required by App
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_MTP3MGMT_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_ANSI_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_STAT;

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = (ITS_OCTET)(ITS_ISUP_INV_CIC & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((ITS_ISUP_INV_CIC >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Local Cong Data */
    memcpy(&ev.data[offset], mgmtdata, sizeof(ISUP_MTP3MGMT_ENTRY));

    /* Getting the destination */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);

    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward MTP3 mgmt indication to App thread [0x%04x]"
                    " (vcic: %d).\n", dest, vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ISUP_ERROR(("SPRC: Unable to send MTP3 mgmt indication "
                    " to APP.\n"));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  This function increments the COUNT of Sent Pegs.(Destination Msg pegs)
 *
 *  Input Parameters:
 *  CONFIG INFO, MSGTYPE
 *
 *  Output Parameters:
 *   None.
 *
 *  Return Value:
 *  None
 ****************************************************************************/

static void
ISUP_IncrementSentPegs(ISUP_OPC_DPC_INFO *config_info, ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_IAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_IAM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_ACM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_ACM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_ANM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_ANM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_REL:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_REL_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_RLC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_RLC_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_BLO:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_BLO_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_UBL:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_UBL_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_BLA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_BLA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CPG:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_CPG_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CGB:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_CGB_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CGBA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_CGBA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CQM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_CQM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CQR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                 PEG_ISUP_CQR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_GRS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_GRS_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_GRA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_GRA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CGU:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CGU_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CGUA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CGUA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CRG:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CRG_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CFN:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CFN_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_COT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_COT_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CCR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CCR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FOT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FOT_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_INF:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_INF_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_INR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_INR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_LPA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_LPA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_PAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_PAM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_RSC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_RSC_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_RES:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_RES_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_SUS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_SUS_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_UBA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_UBA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_UCIC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_UCIC_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CRM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CRM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CRA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CRA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CVR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CVR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_CVT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CVT_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_EXM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_EXM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FAC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FAC_SENT_TO_REMOTE);
        break;

    default:
        break;
    }
}
