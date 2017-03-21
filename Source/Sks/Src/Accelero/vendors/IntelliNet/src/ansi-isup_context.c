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
 *  ID: $Id: ansi-isup_context.c,v 1.1.1.1 2007-10-08 11:12:13 bsccs2 Exp $
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
 * LOG: Revision 9.2  2005/04/06 11:33:14  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:30  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.15  2005/03/21 13:53:30  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.16.2.3.2.2.2.2  2005/02/25 07:02:53  ssingh
 * LOG: changes done to support Destination Specific Peg Increament.
 * LOG:
 * LOG: Revision 7.16.2.3.2.2.2.1  2004/12/29 14:24:57  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.16.2.3.2.2  2004/11/25 15:28:55  sjaddu
 * LOG: Destination check removed and msgs will not go out in case of backup.
 * LOG:
 * LOG: Revision 7.16.2.3.2.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.16.2.2.2.5  2003/11/24 06:32:32  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.16.2.2.2.4  2003/10/30 14:40:37  sjaddu
 * LOG: Alarms format changes.
 * LOG:
 * LOG: Revision 7.16.2.2.2.3  2003/10/27 08:32:36  akumar
 * LOG: Introduced msg based pegs.
 * LOG:
 * LOG: Revision 7.16.2.2.2.2  2003/10/21 06:19:25  akumar
 * LOG: Pause/Resume/Status handling to appl is done.
 * LOG:
 * LOG: Revision 7.16.2.2.2.1  2003/09/13 06:23:33  akumar
 * LOG: Msg based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.16.2.2  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.11  2003/05/06 13:51:35  sswami
 * LOG: Alarm related changes :opc information included.
 * LOG:
 * LOG: Revision 8.10  2003/05/06 11:12:44  ssingh
 * LOG: Debug Trace for checking Remote Congestion; For REL with ACL param only.
 * LOG:
 * LOG: Revision 8.9  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.8  2003/04/25 12:04:19  akumar
 * LOG: Bug# 317; Alarm Enhancement related changes.
 * LOG:
 * LOG: Revision 8.7  2003/04/24 12:10:24  akumar
 * LOG: Bug FIX #311.
 * LOG:
 * LOG: Revision 8.6  2003/04/16 06:05:46  akumar
 * LOG: Congestion and ITS_EVENT_TERM add/removal changes.
 * LOG:
 * LOG: Revision 8.5  2003/04/03 15:08:04  sjaddu
 * LOG: ISUP DSM reorganization.
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
 * LOG: Revision 8.3  2003/03/14 09:53:10  ssingh
 * LOG: Bug fix for #241 is propped from PR6.3
 * LOG:
 * LOG: Revision 8.2  2003/02/13 21:39:12  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:21  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.16  2003/02/05 00:55:06  sjaddu
 * LOG: Bug fix incase for cic rec is NULL.
 * LOG:
 * LOG: Revision 7.15  2003/01/28 14:11:06  ssingh
 * LOG: Changes done in ValidateCIC to check cic_state.
 * LOG:
 * LOG: Revision 7.14  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.13  2003/01/21 15:34:18  vnitin
 * LOG: Tandem Port for ISUP, mostly type casting
 * LOG:
 * LOG: Revision 7.12  2003/01/17 15:23:05  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.11  2003/01/10 22:46:32  sjaddu
 * LOG: DSM_que changes in MTP3HandleMsg().
 * LOG:
 * LOG: Revision 7.10  2002/12/31 12:42:42  ssingh
 * LOG: To check CQM range and Status, function added.
 * LOG:
 * LOG: Revision 7.9  2002/12/27 06:50:39  ssingh
 * LOG: Handing of CQM/CVT/UCIC(received) from L3 is modified.
 * LOG:
 * LOG: Revision 7.8  2002/12/09 10:34:09  ssingh
 * LOG: Changed UPU handleing in case of Remote ISUP UNEQUIPPED.
 * LOG:
 * LOG: Revision 7.7  2002/11/28 07:10:49  sjaddu
 * LOG: Handling invalid cic with unrecognized msg,and some indentaion.
 * LOG:
 * LOG: Revision 7.6  2002/11/20 12:06:33  akumar
 * LOG: Removed the inlined ACC procedure with __ISUP_CheckRmtCongestion() fn
 * LOG: and Worked on ALARMS indentation
 * LOG:
 * LOG: Revision 7.5  2002/11/20 10:40:35  ssingh
 * LOG: Added fix to Support repeated parameters occurance in message(sent).
 * LOG:
 * LOG: Revision 7.4  2002/11/19 05:26:08  ssingh
 * LOG: Validate Msg Parsing function is been modified.
 * LOG:
 * LOG: Revision 7.3  2002/11/12 06:26:03  akumar
 * LOG: Added ANSI ISUP Alarms, Automatic Congestion Control Procedures
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:48:01  sjaddu
 * LOG: Added PEGS for ANSI ISUP.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.7  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.6  2002/07/03 20:19:18  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 1.5.2.10  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 1.5.2.9  2002/07/31 20:45:32  sjaddu
 * LOG: CFN and mtp3 indications testing.
 * LOG:
 * LOG: Revision 1.5.2.8  2002/07/30 13:42:20  sjaddu
 * LOG: Added MTP indications and cfn procedures.
 * LOG:
 * LOG: Revision 1.5.2.7  2002/07/25 22:12:28  ssingh
 * LOG: ReleaseCic is removed from __ISUP_HandleMsg for Bad MsgType.
 * LOG:
 * LOG: Revision 1.5.2.6  2002/07/11 13:36:36  hbalimid
 * LOG: Modified functionality for UCIC.
 * LOG:
 * LOG: Revision 1.5.2.5  2002/07/10 19:39:46  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.5.2.4  2002/07/06 06:32:39  hbalimid
 * LOG: Removed unused variables.
 * LOG:
 * LOG: Revision 1.5.2.3  2002/07/05 14:31:07  ssingh
 * LOG: Traces fixed.
 * LOG:
 * LOG: Revision 1.5.2.2  2002/07/05 13:53:02  hbalimid
 * LOG: Fixed bug for release cic.
 * LOG:
 * LOG: Revision 1.5.2.1  2002/07/04 23:25:54  hbalimid
 * LOG: added warnings whereever necessary.
 * LOG:
 * LOG: Revision 1.5  2002/06/17 22:16:52  sjaddu
 * LOG: Added mtp3 indications handling.
 * LOG:
 * LOG: Revision 1.4  2002/06/11 18:38:17  sjaddu
 * LOG: Release cic rec and config info rec.
 * LOG:
 * LOG: Revision 1.3  2002/06/04 16:53:38  hxing
 * LOG: Fix some management bugs.  Not completely done
 * LOG:
 * LOG: Revision 1.2  2002/05/20 16:08:23  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/04/18 19:25:57  ssanyal
 * LOG: Added new file
 * LOG:
 * LOG: 
 *****************************************************************************/

#undef ANSI
#undef CCITT
#define ANSI 

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_hash.h>
#include <its_assertion.h>

#include <ansi/isup.h>
#include <ansi/isup_92.h>
#include <isup_variants.h>

#include "isup_intern.h"


static int __ISUP_CheckCQMRangeStatus(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                                      ISUP_OPC_DPC_INFO *config_info, 
                                      ITS_ISUP_IE *rs_ie, ITS_USHORT *cic);

extern int CheckLocalCongestion(ITS_EVENT *event);

static void
ISUP_IncrementRcvdPegs(ISUP_OPC_DPC_INFO *config_info,
                       ITS_OCTET msgType);

static void ISUP_UpdateLocalCongLevel (ITS_UINT localcong_level);

extern ITS_SERIAL __ISUP_T99_Serial;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The ISUP stack has received a msg from the network (L3) or the
 *      application. It will perform the common job, before forwarding
 *      the msg to the appropriate module.
 *
 *  Input Parameters:
 *      event - pointer to the ISUP event we just received. Event will have 
 *              the format "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
 *      src - the source of the event (L3 or APP).
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date        Reference       Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BugId: 389     Added Message type in the
 *                                          Error indication to application.
 *
 ****************************************************************************/
int
__ISUP_HandleMsg_ANSI(ITS_EVENT* event, ITS_OCTET src)
{
    MTP3_HEADER_ANSI header;
    ITS_USHORT cic = 0, paramlen = 0;
    ITS_OCTET msgType = 0, startOfParam = 0, sio;
    ISUP_PCIC pcic;
    ITS_UINT opc = 0, dpc = 0;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    ISUP_MSG_DESC *msg_desc = NULL;
    __ISUP_MsgHandlerProc msgProc = NULL;
    int ret;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ITS_BOOLEAN retVal = ITS_SUCCESS;
    ITS_ISUP_IE rs_ie;
    ITS_USHORT  startCic;

    ISUP_DEST_STATUS dpc_state;
    ISUP_REMOTE_ISUP_STATUS remote_isup_state;
    /*
     * The len of the event should be at least: the len of the header +
     * the cic plus of the msgtype.
     */
    if (event->len < (sizeof(MTP3_HEADER_ANSI) + sizeof(ITS_USHORT) + 1))
    {
        ISUP_ERROR(("__ISUP_HandleMsg: Bad event (from %s), discard.",
                    ((src == ISUP_SRC_L3_ANSI) ? "L3" : "App")));

        return (ITS_SUCCESS);
    }

    /* Check for MTP3 Management msgs */
    if (src == ISUP_SRC_L3_ANSI)
    {
        if (event->data[0] != MTP3_MSG_USER_DATA)
        {
            ret = __ISUP_HandleMTP3MgmtMsg_ANSI(event);
            return ret;
        }
    }

    /* Getting the Header */
    memset((char*)&header, 0, sizeof(MTP3_HEADER_ANSI));
    memcpy(&header, &event->data[1], sizeof(MTP3_HEADER_ANSI));

    sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(header) &
               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

    /* Get the OPC and DPC from header */
    if (src == ISUP_SRC_L3_ANSI)
    {
        /* OPC as seen by this node is the DPC sent from the remote node */
        opc = MTP3_RL_GET_DPC_VALUE_ANSI(header.label);
    
        /* DPC as seen by this node is the OPC sent from the remote node */
        dpc = MTP3_RL_GET_OPC_VALUE_ANSI(header.label);
        PEG_IncrPeg(ANSI_ISUP_Pegs, PEG_ISUP_TOT_MSGS_RCVD);
    }
    else
    {
        dpc = MTP3_RL_GET_DPC_VALUE_ANSI(header.label);
        opc = MTP3_RL_GET_OPC_VALUE_ANSI(header.label);
    }

    startOfParam = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_ANSI);

    /* Getting the CIC */
    cic |= event->data[startOfParam++]; /* LSB 8 bits */
    cic |= event->data[startOfParam++] << 8; /* MSB 4 bits + 4 spare */

    /* Getting the ISUP msgType */
    msgType = event->data[startOfParam++];

    /* Obtain PCIC from CIC, OPC & DPC */
    ISUP_PCICFromParts(&pcic, opc, dpc, sio, cic);
    
    /* First look for config info for this opc-dpc */
    ret = ISUP_FindOpcDpc(ISUP_PCIC_TO_OPC_DPC(pcic), &config_info, isdsmlocal);

    if (ret != ITS_SUCCESS)
    {
        ISUP_ERROR(("__ISUP_HandleMsg: Could not find config OPC (%d) DPC (%d)"
                    " SIO (%d), MsgType 0x%02x from %s\n",
                    ((src == ISUP_SRC_L3_ANSI) ? dpc : opc),
                    ((src == ISUP_SRC_L3_ANSI) ? opc : dpc),
                    sio, msgType, ((src == ISUP_SRC_L3_ANSI) ? "L3" : "App")));

        ISUP_Alarm_ANSI(3005, __FILE__, __LINE__, 
                         "MsgType is %x OPC %x  DPC %x from %s",
                          msgType, opc, dpc,
                          ((src == ISUP_SRC_L3_ITU) ? "Remote" : "App"));
        return ITS_ENOTCONFIG;
    }
    else
    {
        if (src == ISUP_SRC_L3_ANSI)
        {
            /* msg pegs are incremented here */
            ISUP_IncrementRcvdPegs(&config_info, msgType);
            ISUP_UpdateOpcDpc(&config_info);
        }
    }

    /* Now look for CIC information */
    cic_rec = ISUP_FindPcic(pcic, isdsmlocal);

    /* Check if CIC is valid. */
    if (cic_rec == NULL)
    {
        /* Error not a valid CIC for this OPC-DPC pair */
        ISUP_ERROR(("__ISUP_HandleMsg: Bad CIC (%d) from %s. MsgType 0x%02x."
                    " OPC %d, DPC %d.\n", cic,
                    ((src == ISUP_SRC_L3_ANSI) ? "L3" : "App"), msgType,
                    ((src == ISUP_SRC_L3_ANSI) ? dpc : opc),
                    ((src == ISUP_SRC_L3_ANSI) ? opc : dpc)));

        ISUP_Alarm_ANSI(3006, __FILE__, __LINE__, "Message: %x, Cic: %d",
                                                   msgType, cic);

        if(src == ISUP_SRC_L3_ANSI)
        {
            /* Get msgDesc from variant class. */
            msg_desc = VAR_GetMsgDescription(config_info.isup_var_class, 
                                             msgType );
            if (msg_desc == NULL)
            {
                ISUP_ReleaseOpcDpc(&config_info);
                SPRC_SendCFNToMTP3_ANSI(CI_CAUSE_MSG_TYPE_BAD,msgType,cic,
                                                              &config_info);
                return ITS_ENOTCONFIG;
            }

            if (__ISUP_ValidateParameters_ANSI(config_info.isup_var_class,
                                         event, msgType) != ITS_SUCCESS)
            {
                SPRC_SendCFNToMTP3_ANSI(CI_CAUSE_MSG_TYPE_BAD,
                                        msgType,cic, &config_info);
                ISUP_ReleaseOpcDpc(&config_info);
                return ITS_SUCCESS;
            }

           /* check message type, if message CQM/CVT/CQR/CVR/UCIC
            * proceed further. Don't send UCIC
            */
            switch (msgType)
            {
                case ISUP_MSG_CQM:
                    /* Send CQR to remote as included cic is unequipped */
                    retVal=__ISUP_CheckCQMRangeStatus(event, cic_rec, 
                                                      &config_info, 
                                                      &rs_ie, &startCic);
                    if (retVal != ITS_SUCCESS)
                    {
                       ISUP_ERROR(("CQM RangeStatus check failed \n" ));
                       ISUP_ReleaseOpcDpc(&config_info);
                       return ITS_SUCCESS;
                    }
                    SPRC_SendCQRToMTP3_ANSI(cic_rec, &config_info, &rs_ie, cic);
                    ISUP_ReleaseOpcDpc(&config_info);
                    return ITS_SUCCESS;

                case ISUP_MSG_CVT:
                    /* Send Auto CVR(failed)to remote and Discard the Message */
                    SPRC_SendCVRToMTP3_ANSI(cic, &config_info);
                    ISUP_ReleaseOpcDpc(&config_info);
                    return ITS_SUCCESS;

                case ISUP_MSG_CQR:
                case ISUP_MSG_CVR:
                case ISUP_MSG_UCIC:

                    SPRC_SendIsupToApp_ANSI(ITS_ISUP_INV_VCIC, event);
                    ISUP_ReleaseOpcDpc(&config_info);
                    return ITS_SUCCESS;

                default:
                    /* send UCIC to remote end and discard the message */
                    SPRC_SendUCICToMTP3_ANSI(cic, &config_info);
                    ISUP_ReleaseOpcDpc(&config_info);
                    return ITS_SUCCESS;
            }
        }
        else
        {
            /* Send Indication to App */
            SPRC_SendIsupIndToApp_ANSI(ITS_ISUP_BAD_CIC_STIND, event, src);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }
    }

    /* Check if there is any confusion in the message */

    /* Check if msg is encoded correctly. Only for msgs from MTP3 */
    if (src == ISUP_SRC_L3_ANSI)
    {
        /* Check for msg validity using variant class pointer */
        if (!VAR_IsMsgSupported(config_info.isup_var_class, msgType))
        {
            /* Error not a valid CIC for this OPC-DPC pair */
            ISUP_ERROR(("__ISUP_HandleMsg: Bad MsgType 0x%02x for %s from %s. "
                        "CIC (%d). OPC %d, DPC %d.\n", msgType,
                        ISUP_VariantToString(config_info.isup_var_type), 
                        ((src == ISUP_SRC_L3_ANSI) ? "L3" : "App"), cic,
                        ((src == ISUP_SRC_L3_ANSI) ? dpc : opc),
                        ((src == ISUP_SRC_L3_ANSI) ? opc : dpc)));
            ISUP_Alarm_ANSI(3007, __FILE__, __LINE__,
                                     "MsgType : %x", msgType);

            /* Send CFN to Network & Discard the message */

            SPRC_SendCFNToMTP3_ANSI(CI_CAUSE_MSG_TYPE_BAD,msgType,cic,
                                                                  &config_info);
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_MSG_FORMAT_ERR);
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }

        /* Get msgDesc from variant class. */
        msg_desc = VAR_GetMsgDescription( config_info.isup_var_class, 
                                          msgType );
        if (msg_desc == NULL)
        {
            ISUP_ReleaseCic( cic_rec, isdsmlocal );
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_ENOTCONFIG;
        }
        paramlen = (ITS_USHORT)(event->len - (sizeof(ITS_OCTET)
                                 + sizeof(MTP3_HEADER_ANSI)
                                 + sizeof(ITS_USHORT) + sizeof(ITS_OCTET)));
        if (!__ISUP_ValidateMsgParsing_ANSI( msgType, msg_desc, 
                                              &event->data[startOfParam], 
                                              paramlen))
        {
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_MSG_FORMAT_ERR);
            ISUP_ReleaseCic( cic_rec, isdsmlocal );
            ISUP_ReleaseOpcDpc(&config_info);
            ISUP_Alarm_ANSI(3008, __FILE__, __LINE__,
                                   "MsgType : %x", msgType);
            return ITS_SUCCESS;
        }
        else
        {
            /*check if the msg type is CFN ,if yes discard it */
            if(msgType == ISUP_MSG_CFN)
            {
                SPRC_SendIndToApp_ANSI(ITS_ISUP_CFN_ALERT_IND,cic_rec);
                ISUP_ReleaseCic(cic_rec, isdsmlocal);
                ISUP_ReleaseOpcDpc(&config_info);
                return ITS_SUCCESS;
            }
        }

        /*
         * Check the remote ISUP status ISUP_REMOTE_ISUP_STATUS 
         */
        ISUP_GetRemoteIsupState(&config_info, &remote_isup_state);

        if( remote_isup_state == ISUP_REMOTE_UNAVAILABLE || 
            remote_isup_state == ISUP_REMOTE_UNEQUIPPED)
        {
            ISUP_OPC_DPC_STAT * config_stat = NULL;

            /* This is exception here we have to update in the STAT
             * as well
             */
            config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, isdsmlocal);
            if(config_stat == NULL)
            {
               /* Are u kidding */
               ISUP_ERROR(("What is going on Find Stat failed"));
               return ITS_SUCCESS;
            }

            config_stat->remote_isup_stat = ISUP_REMOTE_AVAILABLE;
            PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_AVAIL);
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            
            config_info.remote_isup_stat = ISUP_REMOTE_AVAILABLE;
            PEG_IncrPeg(&config_info.ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_AVAIL);
            ISUP_UpdateOpcDpc(&config_info);
        }

        /* Check for the presence of Automatic Congestion Control 
         * parameter in REL msg for Remote Node
         */
        if (msgType == ISUP_MSG_REL)
        {
            __ISUP_CheckRmtCongestion(event, msg_desc, cic_rec, config_info);
        }
    }
    else
    {
        /*  
         *  This message is from application ,Check for the 
         *  destination is reachable or not,if not drop the message
         *  and send error message to app.
         */
        ISUP_GetDpcState(&config_info, &dpc_state);
 
        /***** Removed this ckeck, because of prob active-backup redundacy 
        if (dpc_state  == ISUP_DEST_UNREACHABLE)
        {
            ISUP_CRITICAL(("__ISUP_HandleMsg_ANSI:Destination DPC %d NOT"
                            " Reachable.\n",dpc));
            ISUP_Alarm_ANSI(3013, __FILE__, __LINE__,
                                "msgType : %x dpc: %d opc: %d",
                                 msgType, dpc, opc);

            SPRC_SendErrorToApp_ANSI(msgType, ITS_ISUP_DEST_UNREACHABLE_ERR, cic_rec);
            
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }
        *****/

        /*  
         *  This message is from application ,Check for the 
         *  user part is available on the remote or not,if not
         *  drop the message and send error message to app.
         */
        ISUP_GetRemoteIsupState(&config_info, &remote_isup_state);

        if(remote_isup_state == ISUP_REMOTE_UNAVAILABLE ||
           remote_isup_state == ISUP_REMOTE_UNEQUIPPED)
        {
            ISUP_CRITICAL(("__ISUP_HandleMsg_ANSI:User Part UNAVAILABLE/UNEQUIPPED"
                           " DPC %d\n",dpc));

            SPRC_SendErrorToApp_ANSI(msgType, ITS_ISUP_REMOTE_UNAVAILABLE_ERR, cic_rec);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);

            return ITS_SUCCESS;
        }
    }

    /* Get MsgHandlerProc from variant class pointer using 
     * the call_state (fsm_state) and the msgType
     */
    msgProc = VAR_GetMsgProc( config_info.isup_var_class, msgType, 
                              cic_rec->fsm_state );

    /* Call MsgHandler with appropriate input params */
    (*msgProc)(event, cic_rec, &config_info, src);

    ISUP_ReleaseCic(cic_rec, isdsmlocal);
    ISUP_ReleaseOpcDpc(&config_info);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will handle a timeout event received from the ITS.
 *
 *  Input Parameters:
 *      event: The event holding the timeout.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 *      ITS_SUCCESS.
 ****************************************************************************/
int
__ISUP_HandleTimeout_ANSI(ITS_EVENT *event)
{
    ISUP_PCIC pcic;
    ISUP_TIMER_ENTRY timerInfo;
    ITS_TimerData *timerData;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    __ISUP_TimeoutHandlerProc timerProc;
    int ret ,i;
    ITS_BOOLEAN found = ITS_FALSE;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    timerData = (ITS_TimerData*)event->data;
    memcpy( (char *)&timerInfo, (char *)timerData->context, 
            sizeof(ISUP_TIMER_ENTRY));

    /* Check if time out for Local Cong Timer */
    if (timerInfo.timerId == ITS_ISUP_TIMER_T99)
    {
        ITS_UINT localcong_level;

        localcong_level = CheckLocalCongestion(event);

        /*
         * This is for TANDEM but should not impact behavior on Unix.
         * We want to make sure that we restart the T99 if and only if
         * we are handling the timeout from the timer instance that we
         * started not another process (IN or OUT). We want to avoid
         * having a process start too many T99 instances. So we make
         * sure that the serial in the timeout data is equal to the
         * one we started. If not we don't restart T99 this time.
         */

        if (localcong_level && (__ISUP_T99_Serial == timerData->serial))
        {
            /* Start with reduced Value
             * 1/4 th or 1/2 of T99
             * this value will be 4 sec
             */
            __ISUP_T99_Serial = TIMERS_StartTimer(ITS_ISUP_ANSI_SRC,
                                                  (int)LOCAL_CONG_TIMER2,
                                                  (void*)&timerInfo,
                                                  sizeof(ISUP_TIMER_ENTRY));
        }
        else if (__ISUP_T99_Serial == timerData->serial)
        {
            __ISUP_T99_Serial = TIMERS_StartTimer(ITS_ISUP_ANSI_SRC,
                                                  (int)ANSI_ISUP_localcongtimer,
                                                  (void*)&timerInfo,
                                                  sizeof(ISUP_TIMER_ENTRY));
        }

        ISUP_UpdateLocalCongLevel (localcong_level);
        ITS_EVENT_TERM(event);
        return ITS_SUCCESS;

    }

    /* Check if CIC is valid */
    ISUP_PCICFromParts(&pcic, timerInfo.opc, timerInfo.dpc,
                       timerInfo.sio, timerInfo.cic);
    cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
    if (cic_rec == NULL)
    {
        /* Error not a valid CIC for this OPC-DPC pair */
        ISUP_ERROR(("__ISUP_HandleTimeout: Not a valid CIC. Discarded. CIC %d,"
                    "OPC %d, DPC %d, SIO %d, Timeout T%d.",
                    timerInfo.cic, timerInfo.opc,
                    timerInfo.dpc, timerInfo.sio, timerInfo.timerId));
        return ITS_SUCCESS;
    }

    /* Check if time out for repeat reset timer */
    if (timerInfo.timerId == ITS_ISUP_TIMER_T98)
    {
        /* Raise an Alarm, and send an indication to the app for
           intervention */

        /* Remove info about timer from cic_rec */
        ret = ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T98);

        ISUP_DEBUG(("\n$$$$Repeat RSC Attempts timer timeout for cic %d$$$$\n",
                    cic_rec->pcic.cic));
        ISUP_Alarm_ANSI(3068, __FILE__, __LINE__, NULL);
        SPRC_SendIndToApp_ANSI(ITS_ISUP_REPEATRSC_FAILURE_IND, cic_rec);
        return ITS_SUCCESS;
    }

    for (i = 0; i < ISUP_MAX_PNDG_TMRS; ++i)
    {
        if (cic_rec->pndg_tmrs[i].tmr_id == timerInfo.timerId)
        {
            found = ITS_TRUE;
            break;
        }
    }

    if (!found)
    {
        ISUP_ReleaseCic(cic_rec, isdsmlocal);
        return ITS_SUCCESS;
    }

    /* Get config info for OPC-DPC to access variant class ptr. */
    ret = ISUP_FindOpcDpc(ISUP_PCIC_TO_OPC_DPC(pcic), &config_info, isdsmlocal);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* 
     * Get TimeoutHandlerProc from variant class pointer using call_state
     * and TimerId.
     */
    timerProc = VAR_GetTimeoutProc( config_info.isup_var_class, 
                                    timerInfo.timerId, cic_rec->fsm_state );

    /* Call MsgHandler with appropriate input params */
    (*timerProc)(&timerInfo, cic_rec, &config_info);

    ISUP_ReleaseCic(cic_rec, isdsmlocal);
    ISUP_ReleaseOpcDpc(&config_info);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To ensure that any ISUP msg received from a remote endpoint can be
 *      parsed correctly.
 *
 *  Input Parameters:
 *      msgType - the msg we need to validate.
 *      mDesc - pointer to description of msg, as per the variant.
 *      params - pointer to start of params.
 *      len - length of params.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - Msg parsing success, continue normal processing.
 *      ITS_FALSE -  Msg parsing failure, a CFN is sent and we remain in 
 *                   same state.
 *
 *  Notes:
 *      This is done as per Sec. 2.9.5 of 
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_ValidateMsgParsing_ANSI(ITS_OCTET msgType, ISUP_MSG_DESC* msgDesc, 
                                ITS_OCTET* params, ITS_USHORT len)
{
    /* ISUP_MSG_DESC *msgDesc = NULL; */
    ITS_OCTET mandatoryFPartLen = 0x00, nbOfPointers = 0x00;
    int index = 0;

    if (msgDesc == NULL)
    {
        ISUP_CRITICAL(("__ISUP_ValidateMsgParsing_ANSI: no desc for msg: %x",
                       msgType));
        return (ITS_FALSE);
    }

    /* Get total size of mandatory part */
    for (index = 0; index < msgDesc->nmArgs; index++)
    {
        mandatoryFPartLen += ISUP_ComputeMSize(msgDesc->mArgs[index]);
    }

    /* get number of pointers for the optional part */
    nbOfPointers = (ITS_OCTET)(msgDesc->nvArgs);
    if (msgDesc->hasEOP)
    {
        nbOfPointers++;
    }

    /* Check 1: msg len less than len for F mandatory parts and nb pointers */
    if (len < (mandatoryFPartLen + nbOfPointers))
    {
        ISUP_WARNING(("__ISUP_ValidateMsgParsing_ANSI: Msg format error: %x: Discard",
                      msgType));
        return (ITS_FALSE);
    }

    /*
     * Check 2: a V or start of O params pointer points afer msg len.
     * Check 3.a: a V param len exceeds msg len.
     */
    index = 0;
    for (index = mandatoryFPartLen; index < (mandatoryFPartLen + nbOfPointers); index++)
    {
        if (params[index] >= len)
        {
            ISUP_WARNING(("__ISUP_ValidateMsgParsing_ANSI: Msg format error: %x:"
                          " Discard", msgType));
            return (ITS_FALSE);
        }

        /* Check to skip start of O params for V param len check. */
        if (!(msgDesc->hasEOP &&
            (index == (mandatoryFPartLen + nbOfPointers -1))))
        {
            if (params[index + params[index]] > len)
            {
                ISUP_WARNING(("__ISUP_ValidateMsgParsing_ANSI: Msg format error: %x:"
                              " Discard", msgType));
                return (ITS_FALSE);
            }
        }
    }
    
    /* Check 3.b: Same as 3.a but for O params now. */
    if (msgDesc->hasEOP)
    {
        /* index points at the start of optional param pointer */
        index = (mandatoryFPartLen + nbOfPointers - 1);

        if (params[index] != 0x00)
        {        

            for (index = (index + params[index]); index < len ; )
            {
                if (params[index++] == 0x00)
                {
                    /* Found EOP */
                    break;
                }

                /* index is pointing at the Tag */
                if (params[index] > len)
                {
                    ISUP_WARNING(("__ISUP_ValidateMsgParsing_ANSI: Msg format error: "
                                  "%x: Discard", msgType));
                    return (ITS_FALSE);
                }

                index += params[index]+1;
            }
        }
    }
    return (ITS_TRUE);
}

int
__ISUP_HandleMTP3MgmtMsg_ANSI(ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS, count =0, j = 0, cicsInckg;
    MTP3_HEADER hdr,ohdr;
    ITS_OCTET mType = 0, sio;
    ITS_OCTET data[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT len = 0 ;
    ISUP_OPC_DPC_STAT *config_stat;
    ISUP_OPC_DPC_INFO config_info;
    MTP3_STATUS_ANSI stat;
    MTP3_PAUSE_RESUME_ANSI pr;
    ISUP_CIC_INFO *cic_rec = NULL;
    ITS_UINT opc = 0, dpc = 0;
    ISUP_PCIC pcic;
    ITS_USHORT cic = 0;
    ISUP_CKGP_INFO ckgp_info;
    ITS_BOOLEAN cont = ITS_TRUE;
    ISUP_CKGP_LIST *ckgp_list;
    const char *className = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;
    ISUP_MTP3MGMT_ENTRY mgmtdata_ind;

    if (MTP3_Decode_ANSI(evt, &mType, &hdr, data, &len) != ITS_SUCCESS)
    {
        ISUP_ERROR(("ISUPHandleMTP3Msg:  Couldn't decode MTP-TRANSFER\n"));

        ITS_EVENT_TERM(evt);
        return (ITS_EINVALIDARGS);
    }


    /*MTP3_RL_SET_DPC_VALUE(ohdr.label,MTP3_RL_GET_OPC_VALUE(hdr.label));*/
    MTP3_RL_SET_OPC_VALUE(ohdr.label,MTP3_RL_GET_DPC_VALUE(hdr.label));
    ISUP_DEBUG(("MTP3 Indication Type %d recieved \n",mType));

    switch (mType)
    {
    case MTP3_MSG_PAUSE:

        memcpy(&pr,data,sizeof(MTP3_PAUSE_RESUME_ANSI));  
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((pr.affected.data[2] << 16)|
                                          (pr.affected.data[1] << 8) |
                                           pr.affected.data[0] ));
        ohdr.sio = (ITS_OCTET)(hdr.sio | 0x05); /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_WARNING(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                        MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label),
                        MTP3_RL_GET_OPC_VALUE_ANSI(ohdr.label)));

            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        /*
         * Change the DEST status to Unreachable 
         */
        if (config_stat->dest_stat == ISUP_DEST_REACHABLE)
        {
            config_stat->dest_stat = ISUP_DEST_UNREACHABLE;
        }

        ISUP_CRITICAL(("__ISUP_HandleMTP3MgmtMsg_ANSI:Recieved MTP3 "
                       " PAUSE Destination DPC %d NOT Reachable.\n",
                         MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label)));

        PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS,PEG_ISUP_DEST_PAUSE);

        ISUP_SyncOpcDpcInfoWithStat(config_stat);
        ret = ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        /* Alert the maintenance; Alarm */
        ISUP_Alarm_ANSI(3049, __FILE__, __LINE__, "dpc : %d",
                        MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label)); 

        mgmtdata_ind.statId = ITS_ISUP_MTP3_PAUSE_IND;
        mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
        mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);
        mgmtdata_ind.sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(hdr) &
                           (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

        SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
        break;

    case MTP3_MSG_RESUME:

        memcpy(&pr,data,sizeof(MTP3_PAUSE_RESUME_ANSI));  
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((pr.affected.data[2] << 16)|
                                         (pr.affected.data[1] << 8) |
                                          pr.affected.data[0] ));
        ohdr.sio = (ITS_OCTET)(hdr.sio | 0x05); /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_WARNING(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                         MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label),
                         MTP3_RL_GET_OPC_VALUE_ANSI(ohdr.label)));
            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        /*
         * Change the DEST status to Reachable
         */
        if (config_stat->dest_stat == ISUP_DEST_UNREACHABLE)

        {
            config_stat->dest_stat = ISUP_DEST_REACHABLE;
        }

        ISUP_DEBUG(("__ISUP_HandleMTP3MgmtMsg_ANSI:Recieved MTP3"
                       " RESUME Destination DPC %d Reachable.\n",
                         MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label)));

        PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_RESUME);

        ISUP_SyncOpcDpcInfoWithStat(config_stat);
        ret = ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        ISUP_Alarm_ANSI(3050, __FILE__, __LINE__, "dpc : %d", 
                        MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label));

        mgmtdata_ind.statId = ITS_ISUP_MTP3_RESUME_IND;
        mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
        mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);

        mgmtdata_ind.sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(hdr) &
                           (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

        SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
        break;

    case MTP3_MSG_STATUS:

        memcpy(&stat,data,sizeof(MTP3_STATUS_ANSI));
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((stat.affected.data[2] << 16)|
                                         (stat.affected.data[1] << 8) |
                                          stat.affected.data[0] ));
        /* FIXME we are not supposed to this*/
        ohdr.sio = (ITS_OCTET)(hdr.sio | 0x05); /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_DEBUG(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                         MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label),
                         MTP3_RL_GET_OPC_VALUE_ANSI(ohdr.label)));

            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        if ((ohdr.sio & MTP3_SIO_UP_MASK) != 0x05 /*ISUP_SERVICE*/ )
        {
            ret = ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
            break;
        }

        switch(stat.cause)
        {
        case MTP3_STATUS_CONGESTED:

            break;

        case MTP3_STATUS_UPU_INACCESS: 

            if (config_stat->remote_isup_stat == ISUP_REMOTE_UNAVAILABLE)
            {
                /* We already handling this */
                break;
            } 

            /* OPC as seen by this node is the DPC sent from the remote node */
            dpc = MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label);

            /* DPC as seen by this node is the OPC sent from the remote node */
            opc = MTP3_RL_GET_OPC_VALUE_ANSI(ohdr.label);

            sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(ohdr)
                      & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

            ISUP_CRITICAL(("__ISUP_HandleMTP3MgmtMsg_ANSI:Recieved "
                         "MTP3 STATUS_UPU_UNAVAILABLE Destination PC %d\n",dpc));
            ckgp_list = ISUP_FindCkgpList(config_stat->opc_dpc_ni, isdsmlocal);
            if (ckgp_list == NULL)
            {
                ITS_EVENT_TERM(evt);
                return !ITS_SUCCESS;
            }

            PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_UNAVAIL);

            /* Alert the maintenance; Alarm */
            ISUP_Alarm_ANSI(3052, __FILE__, __LINE__, "dpc : %d", dpc);

            className = ISUP_VariantToString(config_stat->isup_var_type);
            cicsInckg = ISUP_CLASS_INFO(ITS_FindFeature(className))->CICsInCkgp;

            for (count = 0; count < ISUP_MAX_CKGPS; ++count)
            {
                if (ckgp_list->ckgp_info[count].ckgp_id == ISUP_INV_CKGP_ID)
                {
                    continue;
                }
                memcpy(&ckgp_info, &ckgp_list->ckgp_info[count],
                       sizeof(ISUP_CKGP_INFO));

                for (j = 0; j < cicsInckg ; ++j)
                {
                    if ((ckgp_info.usable_cics[0] & (0x00000001 << j)) != 0)
                    {
                        cic = (ITS_USHORT)((ckgp_info.ckgp_id * cicsInckg)
                                  + (j+1));
                        cont = ITS_FALSE;
                        break;
                    }
                }
                if (cont == ITS_FALSE) 
                {
                    break;
                }
            }
            ISUP_ReleaseCkgpList(ckgp_list, isdsmlocal);

            /* CIC not found for that DPC */
            if (cont)
            {
                ret = ITS_ENOTCONFIG;
                break;
            }

            /* Obtain PCIC from CIC, OPC & DPC */
            ISUP_PCICFromParts(&pcic, opc, dpc, sio, cic);

            cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
            if (cic_rec == NULL)
            {
                ISUP_ERROR(("HandleMTP3MgmtMsg::CiC Record not found %d\n",cic));
                break;
            }
            ret = ISUP_FindOpcDpc(config_stat->opc_dpc_ni, &config_info,
                                                            isdsmlocal);

            SPRC_SendCVTToMTP3_ANSI(cic_rec,&config_info);
            ISUP_ReleaseOpcDpc(&config_info);
            cic_rec->cvts_state = CVTS_WAIT_FOR_CVR_UPT;

            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T37,
                                    config_info.tmr_hndl_info
                                            [ITS_ISUP_TIMER_T37].tmr_value);
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            
            /* 
             *  Change the status to ISUP_REMOTE_UNAVAILABLE 
             *  to restrict further traffic.
             */
            config_stat->remote_isup_stat = ISUP_REMOTE_UNAVAILABLE;

            mgmtdata_ind.statId = ITS_ISUP_UPU_INACCESS_IND;
            mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
            mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);

            mgmtdata_ind.sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(hdr) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

            SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_ISUP_INV_VCIC, &mgmtdata_ind);

            break;

        case MTP3_STATUS_UPU_UNEQUIP:
            
            /* OPC as seen by this node is the DPC sent from the remote node */
            dpc = MTP3_RL_GET_DPC_VALUE_ANSI(ohdr.label);

            ISUP_CRITICAL(("HandleMTP3Msg:Recived DPC %d User Part"
                          " Unequipped on the Remote side.\n",dpc));
 
            if (config_stat->remote_isup_stat == ISUP_REMOTE_UNEQUIPPED)
            {
                /* We already handling this */
                break;
            }

            /* Change the status to ISUP_REMOTE_UNEQUIPPED
             * to restrict further traffic.
             */
            config_stat->remote_isup_stat = ISUP_REMOTE_UNEQUIPPED;

            /* When user part recieves this message we will inform to
             * management system to restrict further traffic.We shall
             * not initiate the availablity test.
             */
            PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_UNAVAIL);

            ISUP_Alarm_ANSI(3014, __FILE__, __LINE__, "dpc : %d opc: %d",
                             dpc, opc);

            mgmtdata_ind.statId = ITS_ISUP_UPU_UNEQUIPPED_IND;
            mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
            mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);

            mgmtdata_ind.sio = (ITS_OCTET)(MTP3_HDR_GET_SIO(hdr) &
                               (MTP3_SIO_UP_MASK | MTP3_NIC_MASK));

            SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_ISUP_INV_VCIC, &mgmtdata_ind);

            break;

        default :
            ISUP_ERROR(("Unknown MTP3 Status message recieved \n"));

            ISUP_Alarm_ANSI(3015, __FILE__, __LINE__, "dpc : %d", dpc);
            break;

        } 
        ISUP_SyncOpcDpcInfoWithStat(config_stat);
        ret = ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        break;

    default :

        break;
    }
    ITS_EVENT_TERM(evt);
    return ret;
}

int
__ISUP_ValidateParameters_ANSI(ITS_Class V_Class,ITS_EVENT *event,
                                                                ITS_OCTET mType)
{
    int index = 0, i , unknowParamInd =0 ;
    ITS_OCTET *ptr;
    ITS_OCTET *margs, *vargs, *oargs;
    int nmargs = 0, nvargs = 0, noargs = 0;
    ITS_BOOLEAN paramFound = ITS_FALSE;
    ITS_UINT compLen =0;


    ISUP_MSG_DESC *desc = NULL;
    ITS_OCTET *tmp;
    __ISUP_ComputeMSizeProc computeMSize = NULL;

    ISUP_DEBUG(("---- __ISUP_ValidateParamCompatability_ANSI -----\n"));
    /* Get MSG_DESC from Variant record */
    desc = VAR_GetMsgDescription(V_Class, mType);
    if (desc == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    index =  sizeof(ITS_OCTET)*2 + sizeof(ITS_USHORT) +
                   sizeof(MTP3_HEADER);

    margs = desc->mArgs;
    nmargs = desc->nmArgs;
    vargs = desc->vArgs;
    nvargs = desc->nvArgs;
    oargs = desc->oArgs;
    noargs = desc->noArgs;


    /* Get ComputeMSize from Variant info. */
    computeMSize = VAR_ComputeMsize(V_Class);

    /* Get the fixed mandatories */
    for (i = 0; i < nmargs; i++)
    {
        if (computeMSize != NULL)
        {
            compLen = (*computeMSize)(V_Class, margs[i]);
        }
        else
        {
            compLen = ISUP_ComputeMSize(margs[i]);
        }

        /* ISUP_ComputeMSize() return value should > 0,
         * otherwise there is bug */
        if (compLen <= 0)
        {
            return !ITS_SUCCESS;
        }

        index += compLen;
    }

    /* get the variable mandatories */
    ptr = &event->data[index];

    for (i = 0; i < nvargs; i++)
    {
        /* compute the pointer */
        tmp = ptr + *ptr;
        tmp++;
        ptr++;
    }

    /* get the optionals, if any */
    if (noargs && *ptr)
    {
        ptr += *ptr;

        while (*ptr != ISUP_PRM_EOP)
        {
            paramFound = ITS_FALSE;
            for (i =0; i < noargs ;++i)
            {
                if (*ptr == desc->oArgs[i])
                {
                    paramFound = ITS_TRUE;
                }
            }

            if(!paramFound)
            {
                unknowParamInd++;
            }
            ptr++;
            compLen = *ptr;
            ptr += compLen +1;
        }

        /* We didn't find some param in our list */
        if (unknowParamInd)
        {
            return ISUP_SEND_CFN_MSG;
        }
        else
        {
            return ITS_SUCCESS;
        }
    }
    else
    {
        return ITS_SUCCESS;
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *     This function checks Remote cong on each REL msg received frm NET. 
 *
 *  Input Parameters:
 *      event: event containing the rel msg 
 *      msg_desc: isup mesg desc
 *      cic_rec: cic record for the cic pertaining to the message
 *      config_info: config infor for the opc dpc pair
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
void
__ISUP_CheckRmtCongestion(ITS_EVENT* event, ISUP_MSG_DESC *msg_desc,
                          ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO config_info)
{
    int i = 0, nOptparams = 0, ieCount = 0;
    ITS_OCTET congLev = 0;
    ITS_ISUP_IE ies[6];
    ITS_UINT dpc = 0,opc = 0;
    ITS_BOOLEAN conglevparamFound = ITS_FALSE;
    static ITS_BOOLEAN conglev1indSent = ITS_FALSE;
    static ITS_BOOLEAN conglev2indSent = ITS_FALSE;
    static ITS_BOOLEAN conglev3indSent = ITS_FALSE;

    ISUP_OPC_DPC_STAT *config_stat;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ITS_BOOLEAN firstTime  = ITS_FALSE;

    /* Get the dpc for Alarm prints */
    dpc = MTP3_RL_GET_DPC_VALUE(config_info.opc_dpc_ni.label); 
    opc = MTP3_RL_GET_OPC_VALUE(config_info.opc_dpc_ni.label);

    /* Decode the REL msg for optional ACL param 
     * Call generic Msg Decoder for this purpose
     */
    ISUP_Decode(ies, &ieCount, event, msg_desc);
           
    /* Get the number of Optional Parameters */
    nOptparams = ieCount - (msg_desc->nmArgs) - (msg_desc->nvArgs) - 1;

    /* See if nOptparams > 0 */
    if (nOptparams > 0)
    {
        for (i = 0; i < ieCount; ++i)
        {
            switch (ies[i].param_id)
            {
            case ISUP_PRM_AUTO_CONGEST_LEVEL:
                ISUP_DEBUG(("\n---- __ISUP_CheckRmtCongestion -----\n"));

                congLev = ies[i].param_data.autoCongestionLevel.level;
                conglevparamFound = ITS_TRUE;

                if (congLev == AUTO_CONGESTION_LEVEL1)
                {
                    /* Send an indication the application
                     * to control the traffic
                     */
                    if (!conglev1indSent)
                    {
                        if ((!conglev2indSent) && (!conglev3indSent))
                        {
                           PEG_IncrPeg(&config_info.ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES); 
                           firstTime = ITS_TRUE;
                        }    

                        conglev1indSent = ITS_TRUE;
                        conglev2indSent = ITS_FALSE;
                        conglev3indSent = ITS_FALSE;
                        SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_CONGLEVEL1_IND,
                                               cic_rec);
                        /* Raise an Alarm */
                        ISUP_Alarm_ANSI(3009, __FILE__, __LINE__, 
                                        "Remote Cong Level: %x dpc: %d "
                                         "opc: %d", congLev, dpc,opc);
                    
                        /* Set the Remote Congestion Level to 1 */
                        config_info.isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL1;

                        ISUP_UpdateOpcDpc(&config_info);

                        /* look and update config stat for this opc-dpc */
                        config_stat
                                 = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni,
                                                                   isdsmlocal);
                        config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL1;

                        if (firstTime == ITS_TRUE)
                        {
                           PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES); 
                        }

                        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
                    }

                    /* Start TACCr Timer */
                    __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TACCR,
                                      config_info.tmr_hndl_info
                                      [ITS_ISUP_TIMER_TACCR].tmr_value);
                }
                else if (congLev == AUTO_CONGESTION_LEVEL2)
                {
                    /* Send an indication the application
                     * to control the traffic
                     */
                    if (!conglev2indSent)
                    {
                        if ((!conglev1indSent) && (!conglev3indSent))
                        {
                           PEG_IncrPeg(&config_info.ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES);

                           firstTime = ITS_TRUE;
                        }
                        conglev2indSent = ITS_TRUE;
                        conglev1indSent = ITS_FALSE;
                        conglev3indSent = ITS_FALSE;
                        SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_CONGLEVEL2_IND,
                                                      cic_rec);
                        /* Raise an Alarm */
                        ISUP_Alarm_ANSI(3010, __FILE__, __LINE__, 
                              "Remote Cong Level: %x dpc: %d opc: %d",
                               congLev, dpc,opc);

                        /* Set the Remote Congestion Level to 2 */
                        config_info.isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL2;
                        ISUP_UpdateOpcDpc(&config_info);

                        /* look and update config stat for this opc-dpc */
                        config_stat =
                                   ISUP_FindOpcDpcStat(config_info.opc_dpc_ni,
                                                                  isdsmlocal);
                        config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL2;

                        if (firstTime == ITS_TRUE)
                        {
                           PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES);
                        }

                        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
                    }

                    /* Start TACCr Timer */
                    __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TACCR,
                                      config_info.tmr_hndl_info
                                      [ITS_ISUP_TIMER_TACCR].tmr_value);
                }
                else if (congLev == AUTO_CONGESTION_LEVEL3) 
                {
                   /* Send an indication the application
                    * to control the traffic
                    */
                    if (!conglev3indSent)
                    {
                        if ((!conglev1indSent) && (!conglev2indSent))
                        {
                           PEG_IncrPeg(&config_info.ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES);

                           firstTime = ITS_TRUE;
                        }

                        conglev3indSent = ITS_TRUE;
                        conglev1indSent = ITS_FALSE;
                        conglev2indSent = ITS_FALSE;
                        SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_CONGLEVEL3_IND,
                                                   cic_rec);
                        /* Raise an Alarm */
                        ISUP_Alarm_ANSI(3011, __FILE__, __LINE__, 
                                  "Remote Cong Level: %x dpc: %d opc: %d",
                                   congLev, dpc, opc);

                        /* Set the Remote Congestion Level to 3 */
                        config_info.isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL3;
                        ISUP_UpdateOpcDpc(&config_info);

                        /* look and update config stat for this opc-dpc */
                        config_stat = 
                                  ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, 
                                                                 isdsmlocal);
                        config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_LEVEL3;

                        if (firstTime == ITS_TRUE)
                        {
                           PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS,
                                        PEG_ISUP_DEST_REM_CONGES);
                        }

                        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
                    }
                    /* Start TACCr Timer */
                    __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_TACCR,
                                      config_info.tmr_hndl_info
                                            [ITS_ISUP_TIMER_TACCR].tmr_value);
                }
                else if ((congLev != AUTO_CONGESTION_LEVEL1 &&
                          congLev != AUTO_CONGESTION_LEVEL2 &&
                          congLev != AUTO_CONGESTION_LEVEL3 ) &&
                          config_info.isup_rmt_conglev)
                {
                    /* Send an indication the application
                     * to cease the congestion control
                     */
                    PEG_IncrPeg(&config_info.ISUP_DEST_PEGS,
                                 PEG_ISUP_DEST_REM_CONGES_SEIZED);

                    conglev1indSent = ITS_FALSE;
                    conglev2indSent = ITS_FALSE;
                    conglev3indSent = ITS_FALSE;
                    SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_NOCONG_IND,
                                                cic_rec);

                    /* Set the Remote Congestion Level to off */
                    config_info.isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
                    ISUP_UpdateOpcDpc(&config_info);

                    /* look and update config stat for this opc-dpc */
                    config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, 
                                                                 isdsmlocal);
                    config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;

                    PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS,
                                 PEG_ISUP_DEST_REM_CONGES_SEIZED);

                    ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

                    /* Raise an Alarm */
                    ISUP_Alarm_ANSI(3012, __FILE__, __LINE__,
                               "Remote Cong Level : %x dpc: %d opc: %d",
                                congLev, dpc, opc);

                }
                break;

            case ISUP_PRM_ACCESS_TRANSPORT:
            case ISUP_PRM_CALL_REF:
            case ISUP_PRM_CAUSE_INDICATORS:
            case ISUP_PRM_GENERIC_ADDR:
            case ISUP_PRM_CHARGE_NUMBER:
            case ISUP_PRM_SERVICE_ACTIVATION:
            case ISUP_PRM_USER_TO_USER_INFORM:
                break;

            default:
                break;
            }
        }
        if (!conglevparamFound && config_info.isup_rmt_conglev)
        {
            /* The ACL param is not present in the REL
             * msg, cease the congestion, if already there
             */
            conglev1indSent = ITS_FALSE;
            conglev2indSent = ITS_FALSE;
            conglev3indSent = ITS_FALSE;
            /* Set the Remote Congestion Level to off */
            config_info.isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
            ISUP_UpdateOpcDpc(&config_info);

            /* look and update config stat for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, isdsmlocal);
            config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

            SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_NOCONG_IND, cic_rec);
            ISUP_Alarm_ANSI(3012, __FILE__, __LINE__,
                             "Remote Cong Level: %x dpc: %d opc: %d ",
                              congLev, dpc,opc);
        }
    }
    else if (config_info.isup_rmt_conglev)
    {
        /* No Optional IE in the REL message 
         * Send an indication to remove the 
         * congestion control, if already there
         */
        conglev1indSent = ITS_FALSE;
        conglev2indSent = ITS_FALSE;
        conglev3indSent = ITS_FALSE;

        /* Set the Remote Congestion Level to off */
        config_info.isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
        ISUP_UpdateOpcDpc(&config_info);

        /* look and update config stat for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, isdsmlocal);
        config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        SPRC_SendIndToApp_ANSI(ITS_ISUP_RMT_NOCONG_IND, cic_rec);
        ISUP_Alarm_ANSI(3012, __FILE__, __LINE__,
                         "Remote Cong Level: %x dpc: %d opc: %d ",
                          congLev, dpc, opc);
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *      Validate contents of a CQM RangeAndStatus param
 *
 *  Input Parameters:
 *      msg: the message containing the param
 *      cic_rec: cic record for the cic pertaining to the message
 *      config_info: config infor for the opc dpc pair
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      rs_ie: range and status IE from the message
 *      cic: cic in the message
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 ****************************************************************************/
static int
__ISUP_CheckCQMRangeStatus(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info,
                           ITS_ISUP_IE *rs_ie, ITS_USHORT *cic)
{
    int ret = ITS_SUCCESS;
    int index = 0;
    ITS_USHORT paramlen = 0;
    ITS_ISUP_IE ies[5];
    int ieCount = 0;
    ITS_OCTET range; /* range value */
    ITS_OCTET rslen; /* rangestatus param len */
    ITS_OCTET slen;  /* status len */
    int i;
    ITS_OCTET cic_index;

    ISUP_DEBUG(("---- __ISUP_CheckCQMRangeStatus -----\n"));

    /* initialize local */
    memset((char *)ies, 0, sizeof(ITS_ISUP_IE) * 5);

    /* initialize output params */
    memset((char *)rs_ie, 0, sizeof(ITS_ISUP_IE));
    *cic = 0;

    /* MTP3MessageType: MTP3Header: CIC: Message Type: Params */

    /* get cic from message: CIC is two bytes: LSB and MSB (4 bits) */
    cic_index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_ANSI);
    *cic = (ITS_USHORT)((msg->data[cic_index + 1] << 8) + msg->data[cic_index]);

    paramlen = (ITS_USHORT)(msg->len - sizeof(ITS_OCTET) - sizeof(ITS_USHORT)
                       - sizeof(MTP3_HEADER_ANSI));
    index = msg->len - paramlen;

    /* Need to do a Decode as TLV style is not being used. */
    ret = ISUP_MTP3Decode_ANSI(&msg->data[index + 1], paramlen,
                                msg->data[index], ies,
                                &ieCount, config_info->isup_var_class);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    for (i = 0; i < ieCount; i++)
    {
        if (ies[i].param_id == ISUP_PRM_RANGE_STATUS)
        {
            rslen = ies[i].param_length;

            if (rslen > 1)
            {
                return ITS_BADISUPMESSAGE;
            }

            /* subtract 1 for range */
            slen = (ITS_OCTET)(ies[i].param_length - 1);
            range  = ies[i].param_data.rangeAndStatus.range;

            if (slen != 0 || (range > 23))
            {
                return ITS_BADISUPMESSAGE;
            }

            *rs_ie = ies[i];
        }
    }

    return ITS_SUCCESS;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *  This function increments the COUNT of Received Pegs.(Destination Msg pegs)
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
ISUP_IncrementRcvdPegs(ISUP_OPC_DPC_INFO *config_info,
                       ITS_OCTET msgType)
{
    switch(msgType)
    {
    case ISUP_MSG_IAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_IAM_RCVD);
        break;

    case ISUP_MSG_ACM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_ACM_RCVD);
        break;
    case ISUP_MSG_ANM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_ANM_RCVD);
        break;

    case ISUP_MSG_REL:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_REL_RCVD);
        break;

    case ISUP_MSG_RLC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_RLC_RCVD);
        break;

    case ISUP_MSG_BLO:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_BLO_RCVD);
        break;

    case ISUP_MSG_UBL:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_UBL_RCVD);
        break;

    case ISUP_MSG_BLA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_BLA_RCVD);
        break;

    case ISUP_MSG_CPG:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_CPG_RCVD);
        break;

    case ISUP_MSG_CGB:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_CGB_RCVD);
        break;

    case ISUP_MSG_CGBA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_CGBA_RCVD);
        break;

    case ISUP_MSG_CQM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_CQM_RCVD);
        break;

    case ISUP_MSG_CQR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                 PEG_ISUP_REMOTE_CQR_RCVD);
        break;

    case ISUP_MSG_GRS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_GRS_RCVD);
        break;

    case ISUP_MSG_GRA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_GRA_RCVD);
        break;

    case ISUP_MSG_CGU:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CGU_RCVD);
        break;

    case ISUP_MSG_CGUA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CGUA_RCVD);
        break;

    case ISUP_MSG_CRG:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CRG_RCVD);
        break;

    case ISUP_MSG_CFN:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CFN_RCVD);
        break;

    case ISUP_MSG_COT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_COT_RCVD);
        break;

    case ISUP_MSG_CCR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CCR_RCVD);
        break;

    case ISUP_MSG_FOT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_FOT_RCVD);
        break;

    case ISUP_MSG_INF:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_INF_RCVD);
        break;

    case ISUP_MSG_INR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_INR_RCVD);
        break;

    case ISUP_MSG_LPA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_LPA_RCVD);
        break;

    case ISUP_MSG_PAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_PAM_RCVD);
        break;

    case ISUP_MSG_RSC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_RSC_RCVD);
        break;

    case ISUP_MSG_RES:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_RES_RCVD);
        break;

    case ISUP_MSG_SUS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_SUS_RCVD);
        break;

    case ISUP_MSG_UBA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_UBA_RCVD);
        break;

    case ISUP_MSG_UCIC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_UCIC_RCVD);
        break;

    case ISUP_MSG_CRM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CRM_RCVD);
        break;

    case ISUP_MSG_CRA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CRA_RCVD);
        break;
    case ISUP_MSG_CVR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CVR_RCVD);
        break;

    case ISUP_MSG_CVT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CVT_RCVD);
        break;

    case ISUP_MSG_EXM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_EXM_RCVD);
        break;

    case ISUP_MSG_FAC:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_FAC_RCVD);
        break;

    default:
        break;
    }
}

/*.implementation:
 ****************************************************************************
 *  Purpose:
 *     This function updates the local congestion level in OPC_DPC_STAT
 *
 *  Input Parameters:
 *      localcong_level 
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
 *  Ramesh K V  04-05-2005   BCGI Problem   updating local Congestion level
 *                           # 488          in opc/dpc record.
 *
 ****************************************************************************/
static void
ISUP_UpdateLocalCongLevel (ITS_UINT localcong_level)
{
    MTP3_HEADER          opc_dpc_ni;
    ISUP_OPC_DPC_STAT  *config_stat = NULL;
    ISUP_CFG_DEST_INFO *dest_info   = NULL;
    int noEnts = 0;
    int j = 0;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    /* Save local congestion level in DSM table for all the
     * destinations, so that can be used for REL messages
     * going out from STACK to Netowork.
     */
    ISUP_GetAllDestCfgInfo_ANSI(&dest_info, &noEnts);

    for ( j = 0; j < noEnts; j++)
    {
        memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
        MTP3_RL_SET_OPC_VALUE_ANSI(opc_dpc_ni.label,
                                   (*(&dest_info))[j].cfg.opc);
        MTP3_RL_SET_DPC_VALUE_ANSI(opc_dpc_ni.label,
                                   (*(&dest_info))[j].cfg.dpc);
        MTP3_HDR_SET_SIO_ANSI(opc_dpc_ni,
                              (*(&dest_info))[j].cfg.sio);

        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
        if (config_stat == NULL)
        {
           ISUP_WARNING(("Failed to find Opc %d Dpc  %d\n",
                          opc_dpc_ni.label.opc, opc_dpc_ni.label.dpc));
        }
        else
        {
           if(localcong_level == ANSI_ISUP_conglevel1)
           {
              /* if change in level; set level to 1 */
              ISUP_SET_OPC_DPC_LOC_CONG(config_stat, ISUP_LOC_CONGES_LEVEL1);
           }
           else if(localcong_level == ANSI_ISUP_conglevel2)
           {
              /* if change in level; set level to 2 */
              ISUP_SET_OPC_DPC_LOC_CONG(config_stat, ISUP_LOC_CONGES_LEVEL2);
           }
           else
           {
              /* if no congestion; set level to 0 */
              ISUP_SET_OPC_DPC_LOC_CONG(config_stat, ISUP_LOC_CONGES_OFF);
           }
           ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
        }
    }

    free(dest_info);
}

