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
 *  ID: $Id: ansi-wait_out_gra_ansi92.c,v 1.1.1.1 2007-10-08 11:12:17 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:52  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:25  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:09  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/06 07:30:01  ssingh
 * LOG: ISUP Bug Fix propagation. BugId #389 (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:53  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:54:00  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1.38.2  2004/12/29 14:35:55  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.5.2.1.38.1  2004/12/06 13:34:50  mmanikandan
 * LOG: Windows Compilation Support
 * LOG:
 * LOG: Revision 7.5.2.1  2003/05/07 10:38:00  ssingh
 * LOG: Latest Changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.5  2003/05/06 13:55:52  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.4  2003/04/28 15:07:15  sjaddu
 * LOG: Removed EVEN TERM every thing is taken care.
 * LOG:
 * LOG: Revision 8.3  2003/04/24 14:13:26  sswami
 * LOG: Bug #317; Alarm Enhancement related changes done.
 * LOG:
 * LOG: Revision 8.2  2003/04/16 06:45:13  akumar
 * LOG: ITS_EVENT_TERM added, to avoid mem leak.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:28  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.5  2002/12/06 05:40:36  akumar
 * LOG: Removed unwanted TABS
 * LOG:
 * LOG: Revision 7.4  2002/11/20 12:55:08  akumar
 * LOG: Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.3  2002/11/12 06:08:20  akumar
 * LOG: Added ANSI ISUP Alarms
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:24:56  sjaddu
 * LOG: Added PEGS for ANSI ISUP.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:29  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.1.2.12  2002/07/30 13:54:55  sjaddu
 * LOG: Added MTP indications and CFN procedures.
 * LOG:
 * LOG: Revision 1.1.2.11  2002/07/18 22:40:28  ssingh
 * LOG: Added Code for handling BLS/BLR/RSC from remote/local.
 * LOG:
 * LOG: Revision 1.1.2.10  2002/07/12 15:25:08  ssingh
 * LOG: Added/Changed CQM/CQR related methods.
 * LOG:
 * LOG: Revision 1.1.2.9  2002/07/10 21:36:58  hbalimid
 * LOG: OGC Answered complete.
 * LOG:
 * LOG: Revision 1.1.2.8  2002/07/10 19:32:12  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.1.2.7  2002/07/10 18:41:38  hbalimid
 * LOG: CPC outgoing statemachine implemented.
 * LOG:
 * LOG: Revision 1.1.2.6  2002/07/09 00:00:16  ssingh
 * LOG: CQR implemented. Bug Fixed.
 * LOG:
 * LOG: Revision 1.1.2.5  2002/07/06 06:09:59  hbalimid
 * LOG: Tookcare of all warnings.
 * LOG:
 * LOG: Revision 1.1.2.4  2002/07/04 23:30:07  hbalimid
 * LOG: USR removed. Not in ANSI92 specs.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/07/04 00:25:42  hbalimid
 * LOG: Typos propagated from CCITT fixed in all files.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/07/03 16:41:16  hbalimid
 * LOG: Modified according to ANSI92.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/07/02 23:22:24  ssingh
 * LOG: Handle GRA in WaitOutGoing GRA.
 * LOG:
 *
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define ANSI

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <ansi/isup.h>
#include <ansi/isup_92.h>
#include <isup_variants.h>

#include "isup_intern.h"

/*
 * Functions for handling messages in the Wait_Outgoing_GRA state for 
 * ANSI92.
 * This is considered to be the generic ANSI variant, and all other ANSI variants
 * use these functions as defaults if they do not have different behaviour.
 */


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLA received in the WAIT_OUTGOING_GRA 
 *      state is done here. The message is forwarded to the application if 
 *      received from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_BLA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an BLO received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_BLO(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_BLO(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGB received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CGB(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGB(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGBA received in the WAIT_OUT_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CGBA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGBA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGU received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CGU(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGU(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CGUA received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CGUA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CGUA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQM received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CQM(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQM(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an CQR received in the WAIT_IN_RLC state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_CQR(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_CQR(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRA received in the WAIT_IN_RLC state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_GRA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an GRS received in the WAIT_IN_RLC state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_GRS(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_GRS(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an REL received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_REL(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward REL appropriately */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_DEBUG(("Received REL in WAIT_OUT_GRA from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to app */
        SPRC_SendIsupToApp_ANSI(cic_rec->vcic, msg);

        /* Change state to WAIT_OUTGOING_GRA */
    }
    else 
    {
        /* App sent REL instead of RLC: error condition. */
        ISUP_ERROR(("Received REL in WAIT_OUT_GRA from APP instead of RLC, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
        /* Change state to WAIT_OUTGOING_GRA, i.e., no change. */


      ISUP_Alarm_ANSI(3114, __FILE__, __LINE__, "Message %x cic : %x",
                      msg->data[sizeof(MTP3_HEADER_ANSI) + 
                      sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                      ISUP_PCIC_TO_CIC(cic_rec->pcic));

      /* Send error indication to application. */
      SPRC_SendErrorToApp_ANSI(ISUP_MSG_REL,
                               ITS_ISUP_UNEXP_APPMSG_WAITOUT_GRA_ERR,
                               cic_rec);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RLC received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_RLC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Forward RLC to app */
    if (src == ISUP_SRC_L3_ANSI)
    {
        /* 
         * Technically, this msg is out of sequence. However, RLC indicates
         * cleanup of call, regardless of other outstanding call-related msgs.
         */
        ISUP_DEBUG(("Received unexpected RLC in WAIT_OUT_GRS_COMPLETE from "
                    "MTP3, pcic 0x%08x, vcic %d.\n", 
                    cic_rec->pcic, cic_rec->vcic));

        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);


        ISUP_Alarm_ANSI(3115, __FILE__, __LINE__, "dpc: %d opc: %d "
                        "cic: %x  Message: %x",
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        msg->data[sizeof(MTP3_HEADER_ANSI) + 
                        sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);
    }
    else 
    {
        ISUP_DEBUG(("Received RLC in WAIT_OUT_GRS_COMPLETE from APP, "
                    "pcic 0x%08x, vcic %d.\n", cic_rec->pcic, cic_rec->vcic));

        /*
        __ISUP_ResetCompleteCPCToCGRR(msg, cic_rec, config_info);
         */

        /* Change state to IDLE - clear cic_rec */
        ISUP_ClearCic(cic_rec);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an RSC received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_RSC(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_RSC(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBA received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_UBA(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBA(msg, cic_rec, config_info, src);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UBL received in the WAIT_OUTGOING_GRA state 
 *      is done here. The message is forwarded to the application if received 
 *      from the network, or vice versa.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_UBL(ITS_EVENT *msg,  ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    __ISUP_CSC_Received_UBL(msg, cic_rec, config_info, src);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a message not expected in 
 *      the WAIT_OUTGOING_GRA state. It also serves as a default handler for 
 *      any errors arising from out-of-range function calls.
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      src - Indicates if the ITS_EVENT came from the app or L3. 
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
static void
__ISUP_Received_UnexpectedMsg(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src)
{
    /* Log error, update stats and drop msg */
    if (src == ISUP_SRC_L3_ANSI)
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from MTP3 in WAIT_OUT_GRA. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
        /* Could print out mtp3 header or entire ITS_EVENT */ 

        PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_UNEXP_MSG_RCVD);

        ISUP_Alarm_ANSI(3116, __FILE__, __LINE__, "dpc: %d opc: %d "
                        "cic: %x  Message: %x",
                        MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                        ISUP_PCIC_TO_CIC(cic_rec->pcic),
                        msg->data[sizeof(MTP3_HEADER_ANSI) + 
                        sizeof(ITS_USHORT) + sizeof(ITS_OCTET)]);
    }
    else
    {
        ISUP_ERROR(("Rcvd Unexpected msg 0x%02x from App in WAIT_OUT_GRA. "
                    "cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                    msg->data[sizeof(MTP3_HEADER_ANSI) + sizeof (ITS_USHORT) +
                    sizeof(ITS_OCTET)],
                    cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));

        ISUP_Alarm_ANSI(3117, __FILE__, __LINE__, "Message %x cic : %x",
                         msg->data[sizeof(MTP3_HEADER_ANSI) + 
                         sizeof(ITS_USHORT) + sizeof(ITS_OCTET)],
                         ISUP_PCIC_TO_CIC(cic_rec->pcic));
    

        /* Send error indication to application. */
        SPRC_SendErrorToApp_ANSI(msg->data[sizeof(MTP3_HEADER_ANSI) +
                               sizeof (ITS_USHORT) + sizeof(ITS_OCTET)],
                               ITS_ISUP_UNEXP_APPMSG_WAITOUT_GRA_ERR,
                               cic_rec);
    }
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a valid pointer to a message handler function
 *      for the WAIT_OUTGOING_GRA state, based on the msgType received.
 *
 *  Input Parameters:
 *      msgType: the type of the message received.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Pointer to a message handler function.
 *
 ****************************************************************************/
ITSSS7DLLAPI __ISUP_MsgHandlerProc
__ISUP_GetMsgProc_WaitOutgoingGra_ANSI92(ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_ACM:
        break;
    case ISUP_MSG_ANM:
        break;
    case ISUP_MSG_CFN:
        break;
    case ISUP_MSG_CPG:
        break;
    case ISUP_MSG_IAM:
        break;
    case ISUP_MSG_REL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_REL;
    case ISUP_MSG_RLC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RLC;
    case ISUP_MSG_RSC:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_RSC;
    case ISUP_MSG_UCIC:
        break;
    
    case ISUP_MSG_BLO:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLO;
    case ISUP_MSG_BLA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_BLA;
    case ISUP_MSG_CGB:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGB;
    case ISUP_MSG_CGBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGBA;
    case ISUP_MSG_CQM:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQM;

    case ISUP_MSG_CQR:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CQR;
    case ISUP_MSG_GRS:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRS;
    case ISUP_MSG_GRA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_GRA;
    case ISUP_MSG_CGU:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGU;
    case ISUP_MSG_CGUA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_CGUA;
    case ISUP_MSG_COT:
    case ISUP_MSG_CCR:

    case ISUP_MSG_FOT:
    case ISUP_MSG_INF:
    case ISUP_MSG_INR:
    case ISUP_MSG_LPA:
    case ISUP_MSG_PAM:
    case ISUP_MSG_RES:
    case ISUP_MSG_SUS:
        break;
    case ISUP_MSG_UBL:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBL;
    case ISUP_MSG_UBA:
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UBA;
    case ISUP_MSG_CRG:

    case ISUP_MSG_CRA:
        break;
    case ISUP_MSG_CRM:
        break;
    case ISUP_MSG_CVR:
        break;
    case ISUP_MSG_CVT:
        break;
    case ISUP_MSG_EXM:
        break;

    default:
        /* Unknown message type for ISUP.
         * Send back Confusion message.
         */
        return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
    }
    return (__ISUP_MsgHandlerProc)__ISUP_Received_UnexpectedMsg;
}


/* TIMEOUT Handling */

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T12 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT12(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT12(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T13 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT13(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT13(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T14 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT14(ISUP_TIMER_ENTRY* t_entry,  ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info) 
{
    __ISUP_CSC_Received_TimeoutT14(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T15 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT15(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT15(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T16 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT16(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT16(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T17 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT17(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT17(t_entry, cic_rec, config_info);
}


/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T18 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT18(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT18(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T19 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT19(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT19(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T20 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT20(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT20(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T21 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT21(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT21(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T22 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT22(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT22(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T23 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT23(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    __ISUP_CSC_Received_TimeoutT23(t_entry, cic_rec, config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T28 timer in the 
 *      WAIT_OUTGOING_GRA state. 
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_TimeoutT28(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info)  
{
    int ret = ITS_SUCCESS;

    ISUP_DEBUG(("TimeoutT28 event received in WAIT_OUT_GRA state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                 cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Nothing to be done at expiry except notify maintenance */
    ISUP_CRITICAL(("Timer T28 expired, pcic 0x%08x, vcic %d.\n",
                        cic_rec->pcic, cic_rec->vcic));

    ISUP_Alarm_ANSI(3118, __FILE__, __LINE__, "dpc: %d opc: %d cic: %x",
                MTP3_RL_GET_DPC_VALUE_ANSI(config_info->out_hdr.label),
                MTP3_RL_GET_OPC_VALUE_ANSI(config_info->opc_dpc_ni.label),
                ISUP_PCIC_TO_CIC(cic_rec->pcic));



    /* Remove info about timer from cic_rec */
    ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T28);
    if (ret != ITS_SUCCESS)
    {
        /* log error */
        ISUP_ERROR(("TimeoutT28 in WAIT_OUT_GRA state: Unable to remove T28 info "
                    "from CIC rec. Error %s. pcic 0x%08x, vcic %d, cic %d.\n",
                    ITS_GetErrorText(ret), cic_rec->pcic, cic_rec->vcic,
                    ISUP_PCIC_TO_CIC(cic_rec->pcic)));
    }

    /* 
     * Send the timeout data to user app. 
     * This will be done whether the procedure is automated or not. 
     */
    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing of a timeout not expected in 
 *      the WAIT_OUTGOING_GRA state. It also serves as a default handler for 
 *      any errors arising from out-of-range function calls.
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
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
static void
__ISUP_Received_UnexpectedTimeout(ISUP_TIMER_ENTRY* t_entry, 
                                  ISUP_CIC_INFO *cic_rec,
                                  ISUP_OPC_DPC_INFO *config_info)
{
    /* Log error, update stats and drop msg */
    ISUP_ERROR(("Rcvd Unexpected Timeout T%d for CIC %d from MTP3 in "
                "WAIT_OUT_GRA. cic state 0x%02x, pcic 0x%08x, vcic %d.\n", 
                t_entry->cic, t_entry->timerId,
                cic_rec->cic_state, cic_rec->pcic, cic_rec->vcic));
    /* Could print out mtp3 header or entire ITS_EVENT */ 


    ISUP_Alarm_ANSI(3119, __FILE__, __LINE__, "State: %x Timer id: T%d",
                          cic_rec->cic_state,t_entry->timerId);

    SPRC_SendTimeoutIndicToApp_ANSI(cic_rec->vcic, t_entry);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function returns a pointer to a timout handler procedure for  
 *      the WAIT_OUTGOING_GRA state, based on the ID of the timer that has 
 *      expired.
 *
 *  Input Parameters:
 *      timerID: the ID of the timer that expired, per ISUP.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      Valid pointer to a function.
 *
 ****************************************************************************/
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc
__ISUP_GetTimeoutProc_WaitOutgoingGra_ANSI92(ITS_UINT timerID)
{
    switch(timerID)
    {
    case ITS_ISUP_TIMER_T1: /*  1    First RLC timer        */
        break;
    case ITS_ISUP_TIMER_T5: /*  5    Second RLC timer       */
        break;
    case ITS_ISUP_TIMER_T6: /*  6    RES timer (network)    */
        break;
    case ITS_ISUP_TIMER_T7: /*  7    ACM timer              */
        break;
    case ITS_ISUP_TIMER_T8: /*  8    COT timer              */
        break;
    case ITS_ISUP_TIMER_T9: /*  9    ANM timer              */
        break;
    case ITS_ISUP_TIMER_T10: /* 10   Unused                 */
        break;
    case ITS_ISUP_TIMER_T11: /* 11   Unused                 */
        break;
    case ITS_ISUP_TIMER_T12: /* 12   First BLA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT12;
    case ITS_ISUP_TIMER_T13: /* 13   Second BLA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT13;
    case ITS_ISUP_TIMER_T14: /* 14   First UBA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT14;
    case ITS_ISUP_TIMER_T15: /* 15   Second UBA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT15;
    case ITS_ISUP_TIMER_T16: /* 16   First RSC response timer   */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT16;
    case ITS_ISUP_TIMER_T17: /* 17   Second RSC response timer  */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT17;
    case ITS_ISUP_TIMER_T18: /* 18   First CGBA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT18;
    case ITS_ISUP_TIMER_T19: /* 19   Second CGBA timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT19;
    case ITS_ISUP_TIMER_T20: /* 20   First CGUA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT20;
    case ITS_ISUP_TIMER_T21: /* 21   Second CGUA timer      */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT21;
    case ITS_ISUP_TIMER_T22: /* 22   First GRA timer        */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT22;
    case ITS_ISUP_TIMER_T23: /* 23   Second GRA timer       */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT23;
    case ITS_ISUP_TIMER_T24: /* 24   Continuity toner timer */
        break;
    case ITS_ISUP_TIMER_T25: /* 25   CCR timing timer       */
        break;
    case ITS_ISUP_TIMER_T26: /* 26   CCR response timer     */
        break;
    case ITS_ISUP_TIMER_T27: /* 27   CCR receive timer      */
        break;
    case ITS_ISUP_TIMER_T28: /* 28   CQR timer              */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT28;
    case ITS_ISUP_TIMER_T29: /* 29   First congestion       */
        break;
    case ITS_ISUP_TIMER_T30: /* 30   First congestion indication    */
        break;
    case ITS_ISUP_TIMER_T31: /* 31   Unused         */
        break;
    case ITS_ISUP_TIMER_T32: /* 32   Unused         */
        break;
    case ITS_ISUP_TIMER_T33: /* 33   Unused         */
        break;
    case ITS_ISUP_TIMER_T34: /* 34   Circuit query timer    */
        break;
    case ITS_ISUP_TIMER_T35: /* 35          */
        break;
    case ITS_ISUP_TIMER_T36: /* 36          */
        break;
    case ITS_ISUP_TIMER_T37: /* 37          */
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_TimeoutT37_ANSI92;
        break;

    default:
        return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
    }
    return (__ISUP_TimeoutHandlerProc)__ISUP_Received_UnexpectedTimeout;
}

