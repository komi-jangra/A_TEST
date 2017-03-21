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
 *  ID: $Id: itu-sprc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:34  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:09  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.4  2005/04/08 09:27:34  snagesh
 * LOG: Fix for compilation issue while using cc compiler
 * LOG:
 * LOG: Revision 9.3  2005/04/06 10:46:13  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:23  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:43  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.11  2005/03/21 13:53:49  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6.2.2.2.2.12.2  2005/02/03 12:56:57  ssingh
 * LOG: Bug number #1403, #1415 fix. (Ramesh KV, Abhijit D)
 * LOG:
 * LOG: Revision 7.6.2.2.2.2.12.1  2004/12/17 03:57:46  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.6.2.2.2.2.6.1  2004/10/25 20:34:13  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.6.2.2.2.2  2004/01/20 08:56:31  sjaddu
 * LOG: Removed sctp specific changes made for tcs.
 * LOG:
 * LOG: Revision 7.6.2.2.2.1  2004/01/05 10:04:51  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.6.2.1.2.5  2003/10/27 08:36:41  akumar
 * LOG: Introduced msg based pegs.
 * LOG:
 * LOG: Revision 7.6.2.1.2.4  2003/10/21 06:19:25  akumar
 * LOG: Pause/Resume/Status handling to appl is done.
 * LOG:
 * LOG: Revision 7.6.2.1.2.3  2003/10/10 14:51:26  akumar
 * LOG: sctp specific changes are done here.
 * LOG:
 * LOG: Revision 7.6.2.1.2.2  2003/09/11 06:34:09  akumar
 * LOG: Problem Fix, related to L3 routing.
 * LOG:
 * LOG: Revision 7.6.2.1.2.1  2003/09/05 09:38:34  akumar
 * LOG: Message Based redundancy modifications.
 * LOG:
 * LOG: Revision 7.6.2.1  2003/05/07 10:21:55  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.7  2003/05/02 14:26:58  ssingh
 * LOG: ANSI to ITU propagation.
 * LOG:
 * LOG: Revision 8.6  2003/04/30 13:34:38  sjaddu
 * LOG: ANSI To ITU changes.
 * LOG:
 * LOG: Revision 8.5  2003/04/30 05:10:09  akumar
 * LOG: Congestion Modified.
 * LOG:
 * LOG: Revision 8.4  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.3  2003/04/04 05:04:58  ssingh
 * LOG: defination for SPRC_SendConfToApp removed.
 * LOG:
 * LOG: Revision 8.2  2003/02/13 21:39:13  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:27  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.6  2003/01/29 12:23:34  ssingh
 * LOG: Changed expression for calculating offset value after filling vcic.
 * LOG:
 * LOG: Revision 7.5  2003/01/27 12:33:53  akumar
 * LOG: Fixed Error for PRC variant, Modified MACRO name for compatibility.
 * LOG:
 * LOG: Revision 7.4  2003/01/22 07:20:55  akumar
 * LOG: Modified for ITU COT and ACC Procedures
 * LOG:
 * LOG: Revision 7.3  2003/01/17 15:34:42  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.2  2002/12/31 05:43:20  akumar
 * LOG: Modified for appropriate indications to be received by APPlication
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/08/16 22:07:09  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.9  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.8  2002/07/16 16:21:52  yranade
 * LOG: Get it to compile.
 * LOG:
 * LOG: Revision 6.7  2002/07/16 15:49:46  ssharma
 * LOG: Change format of event sent to ISUP application.
 * LOG:
 * LOG: Revision 6.6.2.3  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.6.2.2  2002/07/10 19:39:47  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.6.2.1  2002/06/29 16:50:38  ssharma
 * LOG: Put CIC in event to application (in addition to VCIC).
 * LOG:
 * LOG: Revision 6.6  2002/06/28 15:27:49  mmiers
 * LOG: Windows doesn't like newlines in strings.
 * LOG:
 * LOG: Revision 6.5  2002/06/24 17:00:44  ssingh
 * LOG: Phase 3 missing functionality and auto timer handling.
 * LOG:
 * LOG: Revision 6.4  2002/06/21 22:49:38  mmiers
 * LOG: Adding support for China variant
 * LOG:
 * LOG: Revision 6.3  2002/05/28 16:20:50  sjaddu
 * LOG: Added CFN Procedures.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:39  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.16.2.10  2002/05/14 18:14:44  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 5.16.2.9  2002/05/09 18:38:10  labuser
 * LOG: Merge from ISUP_APR_19_2002 branch to PR6.
 * LOG:
 * LOG: Revision 5.16.2.8.2.1  2002/05/02 22:31:51  labuser
 * LOG: Addded new function SPRC_SendRLCToMTP3_CCITT to send RLC from stack itself.
 * LOG:
 * LOG: Revision 5.16.2.8  2002/04/04 17:15:17  ssharma
 * LOG: Debug engine based functional test.
 * LOG:
 * LOG: Revision 5.16.2.7  2002/04/03 18:10:55  ssharma
 * LOG: Fix memory leaks.
 * LOG:
 * LOG: Revision 5.16.2.6  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 5.16.2.5  2002/03/22 16:22:04  ssharma
 * LOG: Add helper functions.
 * LOG:
 * LOG: Revision 5.16.2.4  2002/03/19 17:24:05  ssharma
 * LOG: Add a function to send RSC to MTP3.
 * LOG:
 * LOG: Revision 5.16.2.3  2002/03/14 15:31:05  ssharma
 * LOG: Change signature of Validate_RangeStatus, add CSC state machines.
 * LOG:
 * LOG: Revision 5.16.2.2  2002/03/07 20:15:23  ssharma
 * LOG: Add code to initialize BLS/BLR flags, new functions in SPRC.
 * LOG:
 * LOG: Revision 5.16.2.1  2002/03/05 14:54:02  ssharma
 * LOG: Add new file that contains parameter level validation functions.
 * LOG:
 * LOG: Revision 5.16  2002/02/27 23:31:07  ssharma
 * LOG: Fix IAM handling as per the spec.
 * LOG:
 * LOG: Revision 5.15  2002/02/26 23:52:58  ssharma
 * LOG: Send timeout indication as a (pseudo) ISUP message.
 * LOG:
 * LOG: Revision 5.14  2002/02/22 22:36:07  ssharma
 * LOG: Change signature of a function.
 * LOG:
 * LOG: Revision 5.13  2002/02/21 23:50:25  ssharma
 * LOG: Fix error handling and couple of timeout handling cases.
 * LOG:
 * LOG: Revision 5.12  2002/02/19 23:04:07  ssharma
 * LOG: Fix traces, .ini file after functional test.
 * LOG:
 * LOG: Revision 5.11  2002/02/13 18:28:33  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 5.10  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.9  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.8  2002/02/04 21:25:21  mmiers
 * LOG: Integrate with MTP3
 * LOG:
 * LOG: Revision 5.7  2002/02/01 20:51:17  mmiers
 * LOG: Get it building under current.
 * LOG:
 * LOG: Revision 5.6  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.5  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.4  2001/12/15 01:19:50  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.3  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.2  2001/09/06 17:25:02  mmiers
 * LOG: Straighten out routing a bit.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:29  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.5  2001/01/18 22:29:22  hxing
 * LOG: change ComputeMSize to ISUP_ComputeMSize for link error
 * LOG:
 * LOG: Revision 3.4  2000/12/22 00:36:41  mmiers
 * LOG: Traces
 * LOG:
 * LOG: Revision 3.3  2000/12/21 22:20:38  mmiers
 * LOG: Cleanup a little
 * LOG:
 * LOG: Revision 3.2  2000/08/22 22:33:44  mmiers
 * LOG: Prepare for reentrant SCCP, TCAP, and ISUP warning removal.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:38  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/02/03 17:12:06  fhasle
 * LOG:
 * LOG: First shoet at ISUP Stack.
 * LOG:
 *
 *****************************************************************************/


#undef ANSI
#undef CCITT
#if !defined(PRC) && !defined(TTC)
#define CCITT
#endif

#include <string.h>
#include <stdlib.h>

#include <its.h>

#ident "$Id: itu-sprc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/isup.h>
#elif defined(TTC)
#include <japan/isup.h>
#else
#include <itu/isup.h>
#endif

#include <isup_variants.h>
#include <isup_intern.h>

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
SPRC_SendIsupToMTP3_CCITT(ITS_EVENT* event, ITS_CTXT vcic)
{   
    MTP3_HEADER mtp3_hdr;
    int result = 0;
    ITS_UINT dpc = 0;
    ITS_OCTET ni;
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_OCTET msgType;
    ISUP_OPC_DPC_INFO config_info;
    ITS_BOOLEAN isdsmlocal= ITS_TRUE;
    ITS_INT transId = 0;
    ITS_INT ret = 0;
 
    /* Getting dpc from ITS_EVENT */
    memcpy(&mtp3_hdr, &event->data[1], sizeof(MTP3_HEADER));
    dpc = MTP3_RL_GET_DPC_VALUE(mtp3_hdr.label);
    ni = MTP3_HDR_GET_SIO(mtp3_hdr) & MTP3_NIC_MASK;

    msgType = event->data[sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT) +
                          sizeof(ITS_USHORT)];
    
    header.type = ITS_ISUP;
    header.context.cic = vcic;

    /*
     * We do not use SSN (since we do not support, for now, ISUP over SCCP).
     * What can we do if we fail to send the msg. not much!
     */

    event->src = ISUP_SRC_APP;

    dest = ROUTE_SelectApplication(&header, event, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendIsupToMTP3_CCITT: Dropping the msg here for"
                    "Vcic = %d \n", vcic));
        ITS_EVENT_TERM(event);
        return ITS_SUCCESS;
    }

    event->src = ITS_ISUP_SRC;

    result = !ITS_SUCCESS;

    /* extract the TransportId from DpcTransport table*/
    if (ISUP_DpcTransFindEntry(dpc, &transId) == ITS_SUCCESS)
    {
        if (transId == DO_ROUTE_CONTEXT)
        {
            ITS_BOOLEAN isUp = ITS_FALSE;

            /* Get the state and return value
             * If the return value is ITS_ENOROUTE than border Transport is
             * INTELLINET MTP3

             * If the return value is ITS_SUCCESS than transport is IMAL/SCTP.
             * In this case isUp flag is checked to see whether transport
             * is up/down */

            ret = ROUTE_GetRouteContextState(dpc ,&isUp, ROUTE_DPC_SIO,
                                             FAMILY_ITU,
                                             ROUTE_SIO_ISUP | ni,
                                             ITS_SS7_DEFAULT_LINK_SET,
                                             ITS_SS7_DEFAULT_LINK_CODE,
                                             ITS_SS7_DEFAULT_LINK_PRI);

            if (ret == ITS_SUCCESS && isUp )
            {
                /* Get the TransportId for this route style*/
                transId = ROUTE_RouteContextExists(dpc , ROUTE_DPC_SIO,
                                                   FAMILY_ITU,
                                                   ROUTE_SIO_ISUP | ni,
                                                   ITS_SS7_DEFAULT_LINK_SET,
                                                   ITS_SS7_DEFAULT_LINK_CODE,
                                                   ITS_SS7_DEFAULT_LINK_PRI);
            }
             else if (ret == ITS_ENOROUTE)
            {
                transId = ITS_MTP3_SRC;
            }
            else
            {
                transId = DO_ROUTE_CONTEXT;
            }

            /* update the TrasportId */
            ISUP_DpcTransUpdateEntry(dpc, transId);
        }

        if (transId != DO_ROUTE_CONTEXT)
        {
            result = TRANSPORT_PutEvent(transId, event);
            if (result != ITS_SUCCESS)
            {
                ISUP_CRITICAL(("SPRC_SendIsupToMTP3_CCITT: PutEvent Failed "
                               " TransportId = %d\n", transId));

                /* Set the TransportId to DO_ROUTE_CONTEXT so that
                 * ROUTE_GetRouteContextState can be called again */

                transId = DO_ROUTE_CONTEXT;

                /* update the TrasportId */
                ISUP_DpcTransUpdateEntry(dpc, transId);
            }
            else
            {
                ISUP_DEBUG(("SPRC_SendIsupToMTP3_CCITT: Success "
                             " TransportId = %d\n", transId ));
            }
        }
    }

    if (result != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendIsupToMTP3_CCITT: Failed (%d) to send msg to"
                       " dpc: %d.\n", result, dpc));
    }
    else
    { 
        /* Get opc-dpc-info to update */
        ISUP_FindOpcDpc(mtp3_hdr, &config_info, isdsmlocal);
        ISUP_IncrementSentPegs(&config_info, msgType);
        PEG_IncrPeg(CCITT_ISUP_Pegs, PEG_ISUP_TOT_MSGS_SENT);
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
 *        ISUPMsgType:VCIC:CIC:MTP3_HEADER:EncodedISUPMsg.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendIsupToApp_CCITT(ITS_CTXT vcic, ITS_EVENT* event)
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
    len = event->len - sizeof(ITS_OCTET) + sizeof(ITS_CTXT);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, len);

    /* Put in the ISUPMsgType */
    index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT);
    ev.data[offset++] = event->data[index];

    /* Put vCIC into ITS_EVENT */
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

    /* Getting the application */
    dest = ROUTE_SelectApplication(&header, &ev, ITS_TRUE);
    if (dest != ITS_INVALID_SRC && dest != ITS_NO_SRC)
    {
        ISUP_DEBUG(("SPRC: Forward ISUP msg to App thread [0x%04x] (vcic: %d)"
                    ".\n", dest, vcic));

        ret = TRANSPORT_PutEvent(dest, &ev);
        if (ret != ITS_SUCCESS)
        {
            ITS_EVENT_TERM(&ev);
        }
    }
    else
    {
        ITS_EVENT_TERM(&ev);
        ISUP_DEBUG(("SPRC_SendIsupToApp_CCITT: Unable to send ISUP msg"
                    " to APP (vcic: %d).\n", vcic));
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
SPRC_SendIndToApp_CCITT(ITS_UINT indId, ISUP_CIC_INFO *cic_rec)
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
                         ind_entry.dpc, ind_entry.cic & 0x000F)
    /* 
     * Format ITS_EVENT as required by App 
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_USHORT) + sizeof(ITS_USHORT) + 
              sizeof(MTP3_HEADER) + sizeof(ISUP_INDICATION_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_IND;

    /* Put vCIC into ITS_EVENT */
    ITS_SET_CTXT(&ev.data[offset], cic_rec->vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT. */
    ev.data[offset++] = cic_rec->pcic.cic & 0xFFU;
    ev.data[offset++] = (cic_rec->pcic.cic >> 8) & 0xFFU;

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
SPRC_SendTimeoutIndicToApp_CCITT(ITS_CTXT vcic, ISUP_TIMER_ENTRY* tdata)
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
                         tdata->cic & 0x000F)
    /* 
     * Format ITS_EVENT as required by App 
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) + 
              sizeof(MTP3_HEADER) + sizeof(ISUP_TIMER_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_TIM;

    /* Put vCIC into ITS_EVENT. */
    ITS_SET_CTXT(&ev.data[offset], vcic);

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT. */
    ev.data[offset++] = tdata->cic & 0xFFU;
    ev.data[offset++] = (tdata->cic >> 8) & 0xFFU;

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
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendErrorToApp_CCITT(ITS_OCTET msgType, ITS_UINT errId, ISUP_CIC_INFO *cic_rec)
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
                         err_entry.dpc, err_entry.cic & 0x000F)
    /* 
     * Format ITS_EVENT as required by App 
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) + 
              sizeof(MTP3_HEADER) + sizeof(ISUP_ERROR_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_ERR;

    /* Put vCIC into ITS_EVENT. */
    ITS_SET_CTXT(&ev.data[offset], cic_rec->vcic);
    offset += sizeof(ITS_CTXT);

   /* Put CIC into ITS_EVENT */
    ev.data[offset++] = cic_rec->pcic.cic & 0xFFU;
    ev.data[offset++] = (cic_rec->pcic.cic >> 8) & 0xFFU;

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
            ISUP_DEBUG(("SPRC: The put event is successful\n"));
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
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendIsupIndToApp_CCITT(ITS_UINT indId, ITS_EVENT* event, ITS_OCTET src)
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
    rcvd_offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER);

    /* Getting the CIC */
    cic |= event->data[rcvd_offset];
    cic |= event->data[rcvd_offset+1] << 8;

    /* Getting sio/opc/dpc out of event mtp3 header*/
    memset((char*)&header, 0, sizeof(MTP3_HEADER));
    memcpy(&header, &event->data[1], sizeof(MTP3_HEADER));

    sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(header) &
                     (MTP3_SIO_UP_MASK|MTP3_NIC_MASK));

    if (src == ISUP_SRC_L3_ITU)
    {
        opc = MTP3_RL_GET_DPC_VALUE(header.label);
        dpc = MTP3_RL_GET_OPC_VALUE(header.label);
    }
    else
    {
        dpc = MTP3_RL_GET_DPC_VALUE(header.label);
        opc = MTP3_RL_GET_OPC_VALUE(header.label);
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

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, (ITS_USHORT)(len));

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
 *      SPRC will send an Loc Cong Ind  to Application (Worker thread). This
 *      is sent when cong occuring in the stack, or detected in the stack.
 *
 *  Input Parameters:
 *      vcic     - The VCIC to be sent to the application.
 *      congdata - Information about congestion in the stack.
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
SPRC_SendLocCongIndicToApp_CCITT(ITS_CTXT vcic, ISUP_CONGESTION_ENTRY *congdata)
{
    ITS_USHORT dest = 0;
    ITS_HDR header;
    ITS_EVENT ev;
    int len = 0, offset = 0;
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

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, (ITS_USHORT)len);

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

        TRANSPORT_PutEvent(dest, &ev);
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
SPRC_SendRELToMTP3_CCITT(ITS_OCTET rel_code, ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[2];
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
                   CI_NO_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                           CI_CS_CCITT);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                         CI_NO_EXTEND);
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
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_REL, ies, ieCount, 
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
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_REL;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * store the event in cic_rec for resends
     */
    memcpy(cic_rec->cpc_msg, event.data, event.len);
    cic_rec->cpc_msg_len = event.len;

    /* 
     * Send the ITS_EVENT with REL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_ResendRELToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;

    ITS_EVENT_INIT(&event, ITS_ISUP_SRC, cic_rec->cpc_msg_len);
    memcpy((void *)(event.data), cic_rec->cpc_msg, cic_rec->cpc_msg_len);

    /* 
     * Send the ITS_EVENT with REL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendRELToMTP3: Failed (%d) to resend REL"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendRELToMTP3: Sent REL to L3."
                    " Result = %s, pcic 0x%08x.\n", 
                      ITS_GetErrorText(ret), cic_rec->pcic));
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
SPRC_SendUCICToMTP3_CCITT(ITS_USHORT cic, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UCIC;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UCIC */

    /* 
     * Send the ITS_EVENT with UCIC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, ITS_ISUP_INV_VCIC);

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
SPRC_SendBLOToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_BLO;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in BLO */

    /* 
     * Send the ITS_EVENT with BLO to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_SendUBLToMTP3_CCITT(ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UBL;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UBL */

    /* 
     * Send the ITS_EVENT with UBL to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_SendHWBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_CGB_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    /* 
     * Encode the params for CGB msg to be sent. 
     */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = 
                                             HARD_FAILURE_ORIENTED;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = 1; 
    memset(ies[index].param_data.rangeAndStatus.status, 0, 1);
    SET_RAS_STATUS(&ies[index].param_data.rangeAndStatus, 1, STATUS_BLOCKING);
    ies[index].param_length = 2;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel), 
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_CGB_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_CGB, ies, ieCount, 
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendHWBToMTP3: Failed (%d) to encode CGB to dpc %d,"
                       " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGB;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* store the message in cic rec */
    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_TRUE, isdsmlocal);
    memcpy(cic_msg->cgb_msg, event.data, event.len);
    cic_msg->cgb_msg_len = event.len;
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, isdsmlocal);

    /* 
     * Send the ITS_EVENT with CGB to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendHWBToMTP3: Failed (%d) to send CGB to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendHWBToMTP3: Sending CGB to L3."
                    " Result = %s, pcic 0x%08x, vcic 0x%04x.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic));
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
SPRC_SendBLAToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_BLA;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in BLA */

    /* 
     * Send the ITS_EVENT with BLA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_SendUBAToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UBA;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UBA */

    /* 
     * Send the ITS_EVENT with UBA to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_ResendCGBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

    ITS_EVENT_INIT(&event, ITS_ISUP_SRC, cic_msg->cgb_msg_len);
    memcpy((void *)(event.data), cic_msg->cgb_msg, cic_msg->cgb_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

    /* 
     * Send the ITS_EVENT with CGB to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendCGBToMTP3: Failed (%d) to resend CGB"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendCGBToMTP3: Sending CGB to L3."
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
SPRC_ResendCGUToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

    ITS_EVENT_INIT(&event, ITS_ISUP_SRC, cic_msg->cgu_msg_len);
    memcpy((void *)(event.data), cic_msg->cgu_msg, cic_msg->cgu_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

    /* 
     * Send the ITS_EVENT with CGU to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendCGUToMTP3: Failed (%d) to resend CGU"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendCGUToMTP3: Sending CGU to L3."
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
SPRC_ResendGRSToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT event;
    int ret;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_CIC_MSG_INFO* cic_msg = NULL;

    cic_msg = ISUP_FindPcicMsgBuf(cic_rec->pcic, ITS_FALSE, isdsmlocal);

    ITS_EVENT_INIT(&event, ITS_ISUP_SRC, cic_msg->grs_msg_len);
    memcpy((void *)(event.data), cic_msg->grs_msg, cic_msg->grs_msg_len);

    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_FALSE, isdsmlocal);

    /* 
     * Send the ITS_EVENT with GRS to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_ResendGRSToMTP3: Failed (%d) to resend CGU"
                       " pcic 0x%08x, vcic %d\n", ret, cic_rec->pcic,
                       cic_rec->vcic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_ResendGRSToMTP3: Sending GRS to L3."
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
SPRC_SendRSCToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_RSC;

    /* Fill in Encoded ISUP message data */
    /* memcpy((char *)&event.data[index], (char *)data, len); 
     * NOTE: No parameters in UBA */

    /* 
     * Send the ITS_EVENT with RSC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRSCToMTP3: Failed (%d) to send RSC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendRSCToMTP3: Sending RSC to L3."
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
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendRLCToMTP3_CCITT(ITS_OCTET rel_code, ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[2];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Check input release cause parameter */
    if (!rel_code)
    {
        /* bad input params */
        ISUP_ERROR(("SPRC_SendRLCToMTP3: No rel_code input. pcic 0x%08x.\n",
                    cic_rec->pcic));
        return;
    }

    /* 
     * Encode the params for RLC msg to be sent. 
     */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 2);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CAUSE_INDICATORS;
    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                   CI_NO_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                           CI_CS_CCITT);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                    CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                         CI_NO_EXTEND);
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                 rel_code);
    ies[index].param_length = 2;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel), 
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_RLC, ies, ieCount, 
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRLCToMTP3: Failed (%d) to encode RLC to dpc %d,"
                       " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_RLC;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* 
     * Send the ITS_EVENT with RLC to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendRLCToMTP3: Failed (%d) to send RLC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendRLCToMTP3: Sending RLC to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }
    return;

}


ITSSS7DLLAPI void
SPRC_SendUPTToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

#if 0

    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_ISUP_IE ies;

    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 1);

     /* There is optional parameter in this message don't bother rite now */
    ies.param_id = ISUP_PRM_PARAM_COMPAT_INFO;

#endif

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_UPT;

    /*
     * Send the ITS_EVENT with UPT to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendUPTToMTP3: Failed (%d) to send RSC to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendUPTToMTP3: Sending UPT to L3."
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
SPRC_SendHWGBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info,
                         ISUP_RANGE_AND_STATUS rs_ie)
{
    int ret = ITS_SUCCESS;
    int ieCount = 0;
    int index = 0;
    ITS_ISUP_IE ies[2];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_CGB_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Encode the params for CGB msg to be sent. */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 3);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CKT_GRP_SUPRVN_MT_IND;
    ies[index].param_data.supervisionMsgType.sup_mt = HARD_FAILURE_ORIENTED;
    ies[index].param_length = sizeof(ISUP_SUPERVISION_MSG_TYPE);

    index++;

    /* Fill in range and status parameter. */
    ies[index].param_id = ISUP_PRM_RANGE_STATUS;
    ies[index].param_data.rangeAndStatus.range = rs_ie.range;
    memcpy(ies[index].param_data.rangeAndStatus.status, rs_ie.status, 32);

    ies[index].param_length = sizeof(ISUP_RANGE_AND_STATUS);

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;
    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label,
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label,
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_CGB_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_CGB, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendHWGBToMTP3: Failed (%d) to encode CGB to dpc "
                       "%d," " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CGB;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CGB to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendHWGBToMTP3: Failed (%d) to send CGB to dpc %d,"
                       " cic 0x%04x.\n", ret, dpc_val, cic));
    }
    else
    {
        ISUP_DEBUG(("SPRC_SendHWGBToMTP3: Sending CGB to L3."
                    " Result = %s, dpc %d, cic 0x%04x.\n",
                    ITS_GetErrorText(ret), dpc_val, cic));
    }
    return;
}

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send an Confusion to Network (Worker thread) from stack.
 *
 *  Input Parameters:
 *      cause_ind - The Indication ID to be sent to the Network.
 *      msgType - Type of ISUP msg.
 *      cic_rec - The CIC record for which this indication is being generated.
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
 ****************************************************************************/
ITSSS7DLLAPI void
SPRC_SendCFNToMTP3_CCITT(ITS_OCTET cause_ind,
                         ITS_OCTET msgType,                                                               ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[2];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;

    /* Check input release cause parameter */
    if (!cause_ind)
    {
        /* bad input params */
        ISUP_ERROR(("SPRC_SendCFN: No rel_code input. pcic 0x%08x.\n",
                    cic_rec->pcic));
        return;
    }

    /*
     * Encode the params for CFN msg to be sent.
     */
    memset((char *)&ies, 0, sizeof(ITS_ISUP_IE) * 2);

    /* Fill in Cause Indicators parameter. */
    ies[index].param_id = ISUP_PRM_CAUSE_INDICATORS;
    SET_CI_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator, CI_EXTEND);
    SET_CI_CODING_STANDARD((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator, CI_CS_CCITT);
    SET_CI_LOCATION((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator
, CI_LOC_TRANSIT);
    SET_CI_CAUSE_EXT_IND((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator, CI_EXTEND );
    SET_CI_CAUSE((ISUP_CAUSE_INDICATOR *)&ies[index].param_data.causeIndicator,
                 cause_ind);
    ies[index].param_data.causeIndicator.diagnostics[0] = msgType;
    ies[index].param_length = 3;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel),
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label,
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label,
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_CFN, ies, ieCount,
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCFN: Failed (%d) to encode CFN to dpc %d,"
                       " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

   /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CFN;


    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /*
     * Send the ITS_EVENT with CFN to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_SendCQRToMTP3_CCITT(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info, 
                         ITS_ISUP_IE* rs_ie)
{
    int ret = ITS_SUCCESS, ieCount = 0, index = 0;
    ITS_ISUP_IE ies[3];
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    ITS_UINT dpc_val = 0;
    ITS_OCTET cic_state[32];
    ISUP_CIC_INFO *affected_cic_rec;
    int i;
    ISUP_PCIC pcic;
    ITS_UINT opc, dpc;
    ITS_OCTET ni;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

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

            ISUP_PCICFromParts(&pcic, opc, dpc, ni, cic + i);
            affected_cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
        }

        if (affected_cic_rec == NULL)
        {
            ISUP_ERROR(("Could not find PCIC\n"));
            cic_state[i] = 0x00; 
        }
        else
        {
            cic_state[i] = affected_cic_rec->cic_state;

            if (ISUP_PCIC_TO_CIC(affected_cic_rec->pcic) != cic)
            {
                ISUP_ReleaseCic(affected_cic_rec, isdsmlocal);
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
    ies[index].param_length = rs_ie->param_data.rangeAndStatus.range + 1;

    index++;

    /* Format MTP3_HEADER type parameter */
    ies[index].param_id = ISUP_PRM_ROUTING_LABEL;
    memcpy((char *)&(ies[index].param_data.routingLabel), 
            (char *)&(config_info->out_hdr), sizeof(MTP3_HEADER));
    /* SIO: Netwk Ind - Intl (0), Priority - (0), Srvc Ind Code - ISUP (5) */
    ies[index].param_data.routingLabel.sio |= MTP3_SIO_ISUP;

    MTP3_RL_SET_DPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_OPC(cic_rec->pcic));
    MTP3_RL_SET_OPC_VALUE(ies[index].param_data.routingLabel.label, 
                          ISUP_PCIC_TO_DPC(cic_rec->pcic));

    ies[index].param_length = sizeof(MTP3_HEADER);

    ieCount = index + 1;  /* array index is one less than the count */


    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /* ISUP_MTP3Encode_CCITT(); */
    memset((char *)data, 0, ISUP_MAX_MSG_LEN);
    ret = ISUP_MTP3Encode_CCITT(data, &len, ISUP_MSG_CQR, ies, ieCount, 
                                 config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SPRC_SendCQRToMTP3: Failed (%d) to encode CQR to dpc %d,"
                       " pcic 0x%08x.\n", ret, dpc_val, cic_rec->pcic));
        return;
    }

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 - 
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg" 
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_SRC), (sizeof(ITS_OCTET)
                           + sizeof(MTP3_HEADER) + sizeof(ITS_USHORT)
                           + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr), 
            sizeof(MTP3_HEADER));
    index += sizeof(MTP3_HEADER);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_CQR;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* 
     * Send the ITS_EVENT with CQR to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
 *      SPRC will send a CCR msg to L3 (network). 
 *
 *  Input Parameters:
 *      cic - The CIC for which T25 or T26 Expires 
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
SPRC_SendCCRToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_CCITT_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET)));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_CCITT));
    index += sizeof(MTP3_HEADER_CCITT);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index] = ISUP_MSG_CCR;

    /*
     * Send the ITS_EVENT with CCR to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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

/*.implementation: extern
 ****************************************************************************
 *  Purpose:
 *      SPRC will send a COT msg to L3 (network).
 *
 *  Input Parameters:
 *      cic_rec - The CIC record for which this COT is being generated 
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
SPRC_SendCOTToMTP3_CCITT(ITS_OCTET ind, ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info)
{
    int ret = ITS_SUCCESS;
    ITS_UINT dpc_val = 0, index = 0;
    ITS_EVENT event;
    ITS_USHORT cic;

    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    dpc_val = MTP3_RL_GET_DPC_VALUE(config_info->out_hdr.label);

    /*
     * Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_CCITT_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET) *2));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_CCITT));
    index += sizeof(MTP3_HEADER_CCITT);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = ISUP_MSG_COT;
    event.data[index] = ind;

    /*
     * Send the ITS_EVENT with COT to MTP3.
     */
    ret = SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

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
SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_CTXT vcic, ISUP_MTP3MGMT_ENTRY *mgmtdata)
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
    ISUP_SET_MTP3_HEADER(mtp_hdr, mgmtdata->sio, mgmtdata->opc, mgmtdata->dpc,
                         (ITS_OCTET)(ITS_ISUP_INV_CIC & 0x000F))
    /*
     * Format ITS_EVENT as required by App
     */
    /* Set the length */
    len = sizeof(ITS_OCTET) + sizeof(ITS_CTXT) + sizeof(ITS_USHORT) +
              sizeof(MTP3_HEADER) + sizeof(ISUP_MTP3MGMT_ENTRY);

    ITS_EVENT_INIT(&ev, ITS_ISUP_SRC, (ITS_USHORT)len);

    /* Put in the ISUPMsgType */
    ev.data[offset++] = ISUP_MSG_STAT;

    offset += sizeof(ITS_CTXT);

    /* Put CIC into ITS_EVENT */
    ev.data[offset++] = (ITS_OCTET)(ITS_ISUP_INV_CIC & 0xFFU);
    ev.data[offset++] = (ITS_OCTET)((ITS_ISUP_INV_CIC >> 8) & 0xFFU);

    /* Put mtp header */
    memcpy(&ev.data[offset], &mtp_hdr, sizeof(MTP3_HEADER));
    offset += sizeof(MTP3_HEADER);

    /* Local Mgmt Data */
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

    case ISUP_MSG_CON:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_CON_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_IDR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_IDR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_IRS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_IRS_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FAA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FAA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FAC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FAC_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FRJ:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FRJ_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_FAR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_FAR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_NRM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_NRM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_OLM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_OLM_SENT_TO_REMOTE);
        break;


    case ISUP_MSG_SAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_SAM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_SGM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_SGM_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_UPA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_UPA_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_UPT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_UPT_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_USR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_USR_SENT_TO_REMOTE);
        break;

    case ISUP_MSG_LOP:
        PEG_IncrPeg(&config_info->ISUP_PEGS_SENT,
                                  PEG_ISUP_LOP_SENT_TO_REMOTE);
        break;

    default:
        break;
    }
}

