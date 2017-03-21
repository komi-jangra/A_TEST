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
 *  ID: $Id: itu-isup_context.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/05/09 06:02:41  adutta
 * LOG: Fix compilation error for PRC
 * LOG:
 * LOG: Revision 9.2  2005/04/06 11:33:14  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:41  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.11  2005/03/21 13:53:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.5.2.2.2.3  2005/02/25 07:02:53  ssingh
 * LOG: changes done to support Destination Specific Peg Increament.
 * LOG:
 * LOG: Revision 7.7.2.5.2.2.2.2  2004/12/29 14:16:26  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.7.2.5.2.2.2.1  2004/12/17 03:57:44  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.7.2.5.2.2  2004/11/25 15:28:55  sjaddu
 * LOG: Destination check removed and msgs will not go out in case of backup.
 * LOG:
 * LOG: Revision 7.7.2.5.2.1  2004/01/05 10:04:51  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.7.2.4.2.5  2003/11/24 06:32:33  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.7.2.4.2.4  2003/10/30 14:38:08  sjaddu
 * LOG: Changed some alram formats and cleanup.
 * LOG:
 * LOG: Revision 7.7.2.4.2.3  2003/10/27 08:33:50  akumar
 * LOG: Introduced msg based pegs.
 * LOG:
 * LOG: Revision 7.7.2.4.2.2  2003/10/21 06:19:25  akumar
 * LOG: Pause/Resume/Status handling to appl is done.
 * LOG:
 * LOG: Revision 7.7.2.4.2.1  2003/09/05 09:38:34  akumar
 * LOG: Message Based redundancy modifications.
 * LOG:
 * LOG: Revision 7.7.2.4  2003/07/25 05:03:45  akumar
 * LOG: National Matter - UCIC stuff.
 * LOG:
 * LOG: Revision 7.7.2.3  2003/06/12 10:57:47  akumar
 * LOG: Fixed BUG #372, UCIC related one, Now compatible with Q.784 also.
 * LOG:
 * LOG: Revision 7.7.2.2  2003/05/07 10:21:55  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.6  2003/05/05 06:18:25  akumar
 * LOG: Segmentation Bug Fixed.
 * LOG:
 * LOG: Revision 8.5  2003/05/02 14:26:58  ssingh
 * LOG: ANSI to ITU propagation.
 * LOG:
 * LOG: Revision 8.4  2003/04/30 05:05:12  akumar
 * LOG: Congestion modified. Fixed bug #268.
 * LOG:
 * LOG: Revision 8.3  2003/04/28 15:28:08  sjaddu
 * LOG: Event TERM related changes.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:13:46  sjaddu
 * LOG: ISUP DSM reorg.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:26  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.7  2003/01/22 07:08:49  akumar
 * LOG: Modified for ITU ACC
 * LOG:
 * LOG: Revision 7.6  2003/01/10 23:27:48  sjaddu
 * LOG: DSM_Q changes in MTP3Hamdle();
 * LOG:
 * LOG: Revision 7.5  2003/01/02 19:38:06  sjaddu
 * LOG: warming removal type mismatch changed IDLE to SSI_IDLE.
 * LOG:
 * LOG: Revision 7.4  2002/12/31 10:17:53  akumar
 * LOG: Segmentation Procedure related stuff added
 * LOG:
 * LOG: Revision 7.3  2002/12/31 05:48:18  akumar
 * LOG: Segmentation Procedure has been added, formatted little bit
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:54:38  sjaddu
 * LOG: Added ITU ISUP Alarms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.12  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.11  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.10  2002/07/03 20:19:18  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.9.2.3  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.9.2.2  2002/07/10 19:39:47  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.9.2.1  2002/07/06 20:06:42  hbalimid
 * LOG: Fixed all warnings.
 * LOG:
 * LOG: Revision 6.9  2002/06/17 22:23:57  sjaddu
 * LOG: fixed bug introduced in mtp3 indications.
 * LOG:
 * LOG: Revision 6.8  2002/06/12 20:00:02  sjaddu
 * LOG: fixed warnings on NT.
 * LOG:
 * LOG: Revision 6.7  2002/06/11 18:47:07  sjaddu
 * LOG: Removed unwanted code.
 * LOG:
 * LOG: Revision 6.6  2002/06/03 16:22:29  sjaddu
 * LOG: Added Param level confusion.
 * LOG:
 * LOG: Revision 6.5  2002/05/28 18:45:40  sjaddu
 * LOG: compilation problem fixed.
 * LOG:
 * LOG: Revision 6.4  2002/05/28 16:19:44  sjaddu
 * LOG: Added CFN Procedures.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 21:00:33  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.9.2.6  2002/05/14 18:14:44  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 5.9.2.5  2002/04/05 19:56:56  ssharma
 * LOG: Fix typo in call to timer handler.
 * LOG:
 * LOG: Revision 5.9.2.4  2002/04/05 19:37:44  ssharma
 * LOG: Add parameter to timeout handling procedures.
 * LOG:
 * LOG: Revision 5.9.2.3  2002/04/03 18:10:55  ssharma
 * LOG: Fix memory leaks.
 * LOG:
 * LOG: Revision 5.9.2.2  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 5.9.2.1  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 5.9  2002/02/21 23:50:25  ssharma
 * LOG: Fix error handling and couple of timeout handling cases.
 * LOG:
 * LOG: Revision 5.8  2002/02/20 23:24:21  ssharma
 * LOG: Fix traces and Makefile.
 * LOG:
 * LOG: Revision 5.7  2002/02/13 22:45:23  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.6  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.5  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.4  2002/02/01 20:07:31  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.3  2002/01/02 21:02:44  mmiers
 * LOG: Back out the routing label change.  It breaks hybrid stack builds.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:06  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.5  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.4  2001/01/04 18:03:06  hdivoux
 * LOG: Cleanup
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:07:25  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 22:33:43  mmiers
 * LOG: Prepare for reentrant SCCP, TCAP, and ISUP warning removal.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:34  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.3  2000/06/28 23:39:57  mmiers
 * LOG:
 * LOG:
 * LOG: Name changes.
 * LOG:
 * LOG: Revision 2.2  2000/02/12 00:41:16  mmiers
 * LOG:
 * LOG: Convert vendor to new CORE code.
 * LOG:
 * LOG: Revision 2.1  2000/02/03 17:12:05  fhasle
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

#include <stdlib.h>
#include <string.h>

#include <its.h>
#include <its_hash.h>
#include <its_assertion.h>

#ident "$Id: itu-isup_context.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#if defined(PRC)
#include <china/isup.h>
#elif defined(TTC)
#include <japan/isup.h>
#else
#include <itu/isup.h>
#endif

#include <isup_variants.h>

#include "isup_intern.h"

static ITS_BOOLEAN SSI_Found = ITS_FALSE;
extern int CheckLocalCongestion(ITS_EVENT *event);
static void ISUP_IncrementRcvdPegs(ISUP_OPC_DPC_INFO *config_info,
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
 *      ITS_SUCCESS for success
 *      any other value for failure
 *
 ****************************************************************************/
int
__ISUP_HandleMsg_CCITT(ITS_EVENT* event, ITS_OCTET src)
{   
    MTP3_HEADER header;
    ITS_USHORT cic = 0, paramlen = 0;
    ITS_OCTET msgType = 0, startOfParam = 0, sio;
    ISUP_PCIC pcic;
    ITS_UINT opc = 0, dpc = 0;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    ISUP_MSG_DESC *msg_desc = NULL;
    __ISUP_MsgHandlerProc msgProc = NULL;
    __ISUP_HandleUnrecMsgProc unrecMsgProc = NULL;
    int ret;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    ISUP_DEST_STATUS dpc_state;
    ISUP_REMOTE_ISUP_STATUS remote_isup_state;

    /*
     * The len of the event should be at least: the len of the header +
     * the cic plus of the msgtype.
     */
    if (event->len < (sizeof(MTP3_HEADER) + sizeof(ITS_USHORT) + 1))
    {
        ISUP_ERROR(("__ISUP_HandleMsg: Bad event (from %s), discard.",
                    ((src == ISUP_SRC_L3_ITU) ? "L3" : "App")));

#if 0
        ISUP_Alarm_CCITT(3404, __FILE__, __LINE__, "From %s",
                           ((src == ISUP_SRC_L3_ITU) ? "L3" : "App"));
#endif

        return (ITS_SUCCESS);
    }

    /* Check for MTP3 Management msgs */
    if (src == ISUP_SRC_L3_ITU)
    {
        if (event->data[0] != MTP3_MSG_USER_DATA)
        {
            return __ISUP_HandleMTP3MgmtMsg_CCITT(event);
        }
    }

    /* Getting the Header */
    memset((char*)&header, 0, sizeof(MTP3_HEADER));
    memcpy(&header, &event->data[1], sizeof(MTP3_HEADER));

    sio = MTP3_HDR_GET_SIO(header) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);

    /* Get the OPC and DPC from header */
    if (src == ISUP_SRC_L3_ITU)
    {
        /* OPC as seen by this node is the DPC sent from the remote node */
        opc = MTP3_RL_GET_DPC_VALUE(header.label);
    
        /* DPC as seen by this node is the OPC sent from the remote node */
        dpc = MTP3_RL_GET_OPC_VALUE(header.label);

        PEG_IncrPeg(CCITT_ISUP_Pegs, PEG_ISUP_TOT_MSGS_RCVD);

    }
    else
    {
        dpc = MTP3_RL_GET_DPC_VALUE(header.label);
        opc = MTP3_RL_GET_OPC_VALUE(header.label);
    }

    startOfParam = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER);

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
                    " SIO (%d), MsgType 0x%02x from %s", opc, dpc, sio, 
                    msgType, ((src == ISUP_SRC_L3_ITU) ? "L3" : "App")));

        ISUP_Alarm_CCITT(3405, __FILE__, __LINE__, 
                         "MsgType is %x OPC %x  DPC %x from %s",
                          msgType, opc, dpc,
                          ((src == ISUP_SRC_L3_ITU) ? "Remote" : "App"));

        return ITS_ENOTCONFIG;
    }
    else
    {
        if (src == ISUP_SRC_L3_ITU)
        {
            /* Destination related msg pegs are incremented here */
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
                    " OPC %d, DPC %d.", cic,
                    ((src == ISUP_SRC_L3_ITU) ? "L3" : "App"), msgType,
                    opc, dpc));

        ISUP_Alarm_CCITT(3406, __FILE__, __LINE__,
                         "Message is %x  CIC %x", msgType, cic);

        /* Check if the msg has National or International Significance
         * if National, Send UCIC to the remote else drop the msg
         * received from the Network
         */

        if (src == ISUP_SRC_L3_ITU)
        {
           if ((sio & MTP3_NIC_MASK) == MTP3_NIC_NATIONAL)
           {
               /* National Network, Send a UCIC back to the network */
               SPRC_SendUCICToMTP3_CCITT(cic, &config_info);

           }
           else if ((sio & MTP3_NIC_MASK) == MTP3_NIC_INTERNATIONAL)
           {
               /* International Network */
               ISUP_ERROR(("Msg 0x%02x Received on Invalid/Unequipped CIC "
                           "from Network, DROPPED..\n", msgType));
           }
           ISUP_ReleaseOpcDpc(&config_info);
           return ITS_SUCCESS;
        }
        else
        {
            /* Send Indication to App */
            SPRC_SendIsupIndToApp_CCITT(ITS_ISUP_BAD_CIC_STIND, event, src);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }
    }


    /* Check if msg is encoded correctly. Only for msgs from MTP3 */
    if (src == ISUP_SRC_L3_ITU)
    {
        /* Check for msg validity using variant class pointer */
        if (!VAR_IsMsgSupported(config_info.isup_var_class, msgType))
        {
            /*  If msg not supported look for msg cmp parameter
             *    and handle accordingly 
             */
            unrecMsgProc = ISUP_HANDLE_UNREC_MSG(config_info.isup_var_class);
            switch(unrecMsgProc(config_info.isup_var_class ,event))
            {
            case ISUP_RELEASE_CALL:
                /* Send Alarm To Management */
                SPRC_SendRELToMTP3_CCITT(CI_CAUSE_MSG_TYPE_BAD,cic_rec,
                                                             &config_info);
                PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS,
                                            PEG_ISUP_CIC_REL_UNRECOG_INFO);

                break;

            case ISUP_SEND_CFN_MSG:
                SPRC_SendCFNToMTP3_CCITT(CI_CAUSE_MSG_TYPE_BAD,msgType,cic_rec,
                                                                  &config_info);
                break;

            case ISUP_DISCARD_MSG:
                break;

            case ISUP_PASS_ON_MSG:
                SPRC_SendIsupToApp_CCITT(cic_rec->vcic,event);

                break;

            default :
                break;
            }       

            /* Error not a valid MSG for this pair */
            ISUP_ERROR(("__ISUP_HandleMsg: Bad MsgType 0x%02x for %s from %s. "
                        "CIC (%d). OPC %d, DPC %d.", msgType,
                        ISUP_VariantToString(config_info.isup_var_type), 
                        ((src == ISUP_SRC_L3_ITU) ? "L3" : "App"), cic,
                        opc, dpc));

            ISUP_Alarm_CCITT(3407, __FILE__, __LINE__, "MsgType : %x",
                                                                 msgType);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }

        /* Get msgDesc from variant class. */
        msg_desc = VAR_GetMsgDescription(config_info.isup_var_class, 
                                          msgType);
        if (msg_desc == NULL) 
        {
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_ENOTCONFIG;
        }
        paramlen = event->len - (sizeof(ITS_OCTET) + sizeof(MTP3_HEADER)
                                 + sizeof(ITS_USHORT) + sizeof(ITS_OCTET));
        if (!__ISUP_ValidateMsgParsing_CCITT(msgType, msg_desc, 
                                              &event->data[startOfParam], 
                                              paramlen))
        {
            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_MSG_FORMAT_ERR);

            /* : Log error and send CFN msg back to remote end. */
            ISUP_Alarm_CCITT(3411, __FILE__, __LINE__, "MsgType : %x",
                                                                 msgType);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;
        }
        else
        {
            /*check if the msg type is CFN ,if yes discard it */
            if(msgType == ISUP_MSG_CFN)
            {
                SPRC_SendIndToApp_CCITT(ITS_ISUP_CFN_ALERT_IND,cic_rec);
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
            config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni,
                                                         isdsmlocal);
            if(config_stat == NULL)
            {
               return ITS_SUCCESS;
            }
            config_stat->remote_isup_stat = ISUP_REMOTE_AVAILABLE;
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

            /* Stop T4 timer and change status to ISUP_REMOTE_AVAILABLE */

            config_info.remote_isup_stat = ISUP_REMOTE_AVAILABLE;
    
            PEG_IncrPeg(&config_info.ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_AVAIL);

            ISUP_UpdateOpcDpc(&config_info);
        } 
        
        switch(__ISUP_ValidateParamCompatability_CCITT(
                                                    config_info.isup_var_class,
                                                    event,msgType))
        {
        case ISUP_RELEASE_CALL:
            /* Send Alarm To Management */
            SPRC_SendRELToMTP3_CCITT(0x99,cic_rec,&config_info);

            ISUP_Alarm_CCITT(3408, __FILE__, __LINE__, "vcic is %d",
                                                     cic_rec->vcic);

            PEG_IncrPeg(&cic_rec->ISUP_CIC_PEGS, PEG_ISUP_CIC_REL_UNRECOG_INFO);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;

        case ISUP_SEND_CFN_MSG:
            SPRC_SendCFNToMTP3_CCITT(0x99,msgType,cic_rec,&config_info);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;

        case ISUP_DISCARD_MSG:
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;

        case ISUP_PASS_ON_MSG:
            SPRC_SendIsupToApp_CCITT(cic_rec->vcic,event);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            return ITS_SUCCESS;

        case ISUP_SEGMENT_MSG:
            /* Check if Segmentation/Reassembly procedure
             * has to be performed, SSI bit 
             * check is already been performed
             */

            SSI_Found = ITS_FALSE;

            if (config_info.segmentation_supported)
            {
                /* Store the Message in cic_rec and RETURN */
                __ISUP_StoreOverlenMsg_CCITT(event, cic_rec, &config_info,
                                                                 msgType);
                ISUP_ReleaseCic(cic_rec, isdsmlocal);
                ISUP_ReleaseOpcDpc(&config_info);
                return ITS_SUCCESS;
            }
            else
            {
                /* Won't perform Segmentation/Reassembly function
                 * just, Continue
                 */
                break;
            }

        default :
            ISUP_DEBUG(("Handle_MSG Default *******\n"));
            break;
        }
        
        if (cic_rec->ssi_state)
        {
            /* Stop the Timer T34 */
            __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T34);

            /* Reset the Simple Segmentation State to
             * IDLE in cic_rec
             */
            cic_rec->ssi_state = SSI_IDLE;

            if (msgType == ISUP_MSG_SGM)
            {
                /* Assemble the message (stored + segmentation message) 
                 * and send it to the FSM
                 */
                __ISUP_AssembleOverlenMsg_CCITT(msgProc, event, cic_rec,
                                                       &config_info, src);
                return (ITS_SUCCESS);
            }
            else 
            {
                /* First Send the Stored Message to the FSM
                 * followed by the New Received Message
                 *
                 * Get MsgHandlerProc from variant class pointer using
                 * the  call_state (fsm_state) and the msgType
                 */
                 msgProc = VAR_GetMsgProc(config_info.isup_var_class,
                                cic_rec->lastOverlenMsg, cic_rec->fsm_state);

                 __ISUP_HandleOverlenMsg_CCITT(msgProc, cic_rec, &config_info);

                /* Get MsgHandlerProc from variant class pointer using
                 * the  new call_state (fsm_state) and the msgType
                 */
            }
        }
        if (msgType == ISUP_MSG_SGM)
        {
            /* Received the message, When r not Waiting for it
             * Discard the Message and RETURN 
             */
            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);
            ISUP_DEBUG(("\n----The SGM Message is Discarded, Unexpected---\n"));
            return ITS_SUCCESS;
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
            ISUP_CRITICAL(("__ISUP_HandleMsg_CCITT:Destination DPC %d NOT"
                            " Reachable.\n",dpc));

            SPRC_SendErrorToApp_CCITT(msgType, ITS_ISUP_DEST_UNREACHABLE_ERR, cic_rec);

            ISUP_Alarm_CCITT(3409, __FILE__, __LINE__, "msgType : %x", msgType);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);

            return ITS_SUCCESS;
        }
        ********/

        /*  
         *  This message is from application ,Check for the 
         *  user part is available on the remote or not,if not
         *  drop the message and send error message to app.
         */
        ISUP_GetRemoteIsupState(&config_info, &remote_isup_state);

        if(remote_isup_state == ISUP_REMOTE_UNAVAILABLE ||
           remote_isup_state == ISUP_REMOTE_UNEQUIPPED)
        {
            ISUP_CRITICAL(("__ISUP_HandleMsg_CCITT:User Part UNAVAILABLE/UNEQUIPPED "
                           " DPC %d\n",dpc));

            SPRC_SendErrorToApp_CCITT(msgType, ITS_ISUP_REMOTE_UNAVAILABLE_ERR, cic_rec);

            ISUP_Alarm_CCITT(3410, __FILE__, __LINE__, "msgType : %x",
                                                                 msgType);

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            ISUP_ReleaseOpcDpc(&config_info);

            return ITS_SUCCESS;
        }

        /* Check for the Mesg from Application, while in WAIT_in_SS
         * state, if it is REL/RSC/GRS, stop the TIMER and go to IDLE and
         * send the MSG to the FSM
         */
        if (cic_rec->ssi_state)
        {
            if (msgType == ISUP_MSG_REL || msgType == ISUP_MSG_RSC ||
                msgType == ISUP_MSG_GRS)
            {
                ISUP_DEBUG(("\n--Recvd 0x%02x while in WAIT_in_SS--\n",
                            msgType));
                /* Stop the Timer T34 */
                __ISUP_StopTimer(cic_rec, ITS_ISUP_TIMER_T34);

                /* Reset the Simple Segmentation State to
                 * IDLE in cic_rec
                 */
                cic_rec->ssi_state = SSI_IDLE;

                /* Send the Msg to MsgHandler */
            }
            else 
            {
                /* Discard the message */
                /* Don't do anything */
                ISUP_DEBUG(("\n--Recvd MSG 0x%0x while WAIT_in_SS, DISCARD--\n",
                                                                    msgType));

                ISUP_ReleaseCic(cic_rec, isdsmlocal);
                ISUP_ReleaseOpcDpc(&config_info);
            
                /* Inform the Application
                 * that Why the message has been discarded
                 */
                SPRC_SendIndToApp_CCITT(ITS_ISUP_SGM_WAIT_IND, cic_rec);

                /* Send an Alarm */

                return ITS_SUCCESS;
            }
        }
    }

    /* Get MsgHandlerProc from variant class pointer using call_state
           and msgType */
    msgProc = VAR_GetMsgProc(config_info.isup_var_class, msgType, 
                              cic_rec->fsm_state);

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
__ISUP_HandleTimeout_CCITT(ITS_EVENT *event)
{
    ISUP_PCIC pcic;
    ISUP_TIMER_ENTRY timerInfo;
    ITS_TimerData *timerData;
    ISUP_CIC_INFO *cic_rec = NULL;
    ISUP_OPC_DPC_INFO config_info;
    __ISUP_TimeoutHandlerProc timerProc;
    int ret, i;
    ITS_BOOLEAN found = ITS_FALSE;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;

    timerData = (ITS_TimerData*)event->data;
    memcpy((char *)&timerInfo, (char *)timerData->context, 
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

            __ISUP_T99_Serial = TIMERS_StartTimer(ITS_ISUP_CCITT_SRC, 
                                     (int)LOCAL_CONG_TIMER2,
                                     (void*)&timerInfo,
                                      sizeof(ISUP_TIMER_ENTRY));
        }
        else if (__ISUP_T99_Serial == timerData->serial)
        {
            __ISUP_T99_Serial = TIMERS_StartTimer(ITS_ISUP_CCITT_SRC, 
                                     (int)CCITT_ISUP_localcongtimer,
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
        /* ISUP_Alarm_CCITT(3416, __FILE__, __LINE__, NULL); */
        SPRC_SendIndToApp_CCITT(ITS_ISUP_REPEATRSC_FAILURE_IND, cic_rec);
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
    ITS_C_ASSERT(ret == ITS_SUCCESS);

    /* 
     * Get TimeoutHandlerProc from variant class pointer using call_state
     * and TimerId.
     */
    timerProc = VAR_GetTimeoutProc(config_info.isup_var_class, 
                                    timerInfo.timerId, cic_rec->fsm_state);

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
__ISUP_ValidateMsgParsing_CCITT(ITS_OCTET msgType, ISUP_MSG_DESC* msgDesc, 
                                ITS_OCTET* params, ITS_USHORT len)
{
    /* ISUP_MSG_DESC *msgDesc = NULL; */
    ITS_OCTET mandatoryFPartLen = 0x00, nbOfPointers = 0x00;
    int index = 0;

    if (msgDesc == NULL)
    {
        ISUP_CRITICAL(("__ISUP_ValidateMsgParsing_CCITT: no desc for msg: %x",
                       msgType));
        return (ITS_FALSE);
    }

    /* Get total size of mandatory part */
    for (index = 0; index < msgDesc->nmArgs; index++)
    {
        mandatoryFPartLen += ISUP_ComputeMSize(msgDesc->mArgs[index]);
    }

    /* get number of pointers for the optional part */
    nbOfPointers = msgDesc->nvArgs;
    if (msgDesc->hasEOP)
    {
        nbOfPointers++;
    }

    /* Check 1: msg len less than len for F mandatory parts and nb pointers */
    if (len < (mandatoryFPartLen + nbOfPointers))
    {
        ISUP_WARNING(("__ISUP_ValidateMsgParsing_CCITT: Msg format error: %x: Discard",
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
            ISUP_WARNING(("__ISUP_ValidateMsgParsing_CCITT: Msg format error: %x:"
                          " Discard", msgType));
            return (ITS_FALSE);
        }

        /* Check to skip start of O params for V param len check. */
        if (!(msgDesc->hasEOP &&
            (index == (mandatoryFPartLen + nbOfPointers -1))))
        {
            if (params[index + params[index]] > len)
            {
                ISUP_WARNING(("__ISUP_ValidateMsgParsing_CCITT: Msg format error: %x:"
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

            for (index = (index + params[index]); index < len ;)
            {
                if (params[index++] == 0x00)
                {
                    /* Found EOP */
                    break;
                }

                /* index is pointing at the Tag */
                if (params[index++] > len)
                {
                    ISUP_WARNING(("__ISUP_ValidateMsgParsing_CCITT: Msg format error: "
                                  "%x: Discard", msgType));
                    return (ITS_FALSE);
                }

                index += params[index];
            }
        }
    }
    return (ITS_TRUE);
}

int
__ISUP_HandleMTP3MgmtMsg_CCITT(ITS_EVENT *evt)
{
    int ret = ITS_SUCCESS, j = 0, cicsInckg;
    MTP3_HEADER hdr,ohdr;
    ITS_OCTET mType = 0, sio;
    ITS_OCTET data[MTP3_MAX_SIF_LENGTH];
    ITS_USHORT len = 0 ;
    ISUP_OPC_DPC_STAT *config_stat;
    ISUP_OPC_DPC_INFO config_info;
    MTP3_STATUS_CCITT stat;
    MTP3_PAUSE_RESUME_CCITT pr;
    ISUP_CIC_INFO *cic_rec = NULL;
    ITS_UINT opc = 0, dpc = 0;
    ISUP_PCIC pcic;
    ITS_USHORT cic = 0;
    ISUP_CKGP_INFO ckgp_info;
    ITS_BOOLEAN cont = ITS_TRUE;
    ITS_UINT count;
    ISUP_CKGP_LIST *ckgp_list;
    const char *className = NULL;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;
    ISUP_MTP3MGMT_ENTRY mgmtdata_ind;

    if (MTP3_Decode(evt, &mType, &hdr, data, &len) != ITS_SUCCESS)
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

        memcpy(&pr,data,sizeof(MTP3_PAUSE_RESUME_CCITT));  
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((pr.affected.data[1] << 8) |
                                           pr.affected.data[0]));
        ohdr.sio = hdr.sio | 0x05; /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_DEBUG(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                        MTP3_RL_GET_DPC_VALUE(ohdr.label),
                        MTP3_RL_GET_OPC_VALUE(ohdr.label)));
 
            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        /*
         * Change the DEST status to Unreachable 
         */
        if(config_stat->dest_stat == ISUP_DEST_REACHABLE)
        {
            config_stat->dest_stat = ISUP_DEST_UNREACHABLE;
        }


        ISUP_CRITICAL(("__ISUP_HandleMTP3MgmtMsg_CCITT:Recieved MTP3 "
                       " PAUSE Destination DPC %d NOT Reachable.\n",
                         MTP3_RL_GET_DPC_VALUE(ohdr.label)));

        PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_PAUSE);

        ISUP_Alarm_CCITT(3411, __FILE__, __LINE__, "DPC : %d", 
                            MTP3_RL_GET_DPC_VALUE(ohdr.label));

        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        mgmtdata_ind.statId = ITS_ISUP_MTP3_PAUSE_IND;
        mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
        mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);
        mgmtdata_ind.sio = ohdr.sio;
        SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
        break;

    case MTP3_MSG_RESUME:

        memcpy(&pr,data,sizeof(MTP3_PAUSE_RESUME_CCITT));  
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((pr.affected.data[1] << 8) |
                                           pr.affected.data[0] ));
        ohdr.sio = hdr.sio | 0x05; /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_DEBUG(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                         MTP3_RL_GET_DPC_VALUE(ohdr.label),
                         MTP3_RL_GET_OPC_VALUE(ohdr.label)));
            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        /*
         * Change the DEST status to Unreachable
         */
        if(config_stat->dest_stat == ISUP_DEST_UNREACHABLE)
        {
            config_stat->dest_stat = ISUP_DEST_REACHABLE;
        }

        ISUP_DEBUG(("__ISUP_HandleMTP3MgmtMsg_CCITT:Recieved MTP3"
                    " RESUME Destination DPC %d Reachable.\n",
                      MTP3_RL_GET_DPC_VALUE(ohdr.label)));

        PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_RESUME);

        ISUP_Alarm_CCITT(3412, __FILE__, __LINE__, "DPC : %d",
                            MTP3_RL_GET_DPC_VALUE(ohdr.label));

        ISUP_SyncOpcDpcInfoWithStat(config_stat);
        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        mgmtdata_ind.statId = ITS_ISUP_MTP3_RESUME_IND;
        mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
        mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);
        mgmtdata_ind.sio = ohdr.sio; 
        SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
        break;

    case MTP3_MSG_STATUS:

        memcpy(&stat,data,sizeof(MTP3_STATUS_CCITT));
        MTP3_RL_SET_DPC_VALUE(ohdr.label,((stat.affected.data[1] << 8) |
                                           stat.affected.data[0] ));
        /* FIXME we are not supposed to this*/
        ohdr.sio = hdr.sio | 0x05; /*set to ISUP service ID */

        config_stat = ISUP_FindOpcDpcStat(ohdr, isdsmlocal);
        if (config_stat == NULL)
        {
            ISUP_DEBUG(("Failed ISUP_FindOpcDpc DPC  %d  OPC  %d \n",
                         MTP3_RL_GET_DPC_VALUE(ohdr.label),
                         MTP3_RL_GET_OPC_VALUE(ohdr.label)));

            ITS_EVENT_TERM(evt);
            return ITS_ENOTCONFIG;
        }

        if ((ohdr.sio & MTP3_SIO_UP_MASK) != 0x05 /*ISUP_SERVICE*/ )
        {
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);
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
                ret = ITS_SUCCESS;
                break;
            } 

            /* OPC as seen by this node is the DPC sent from the remote node */
            dpc = MTP3_RL_GET_DPC_VALUE(ohdr.label);

            /* DPC as seen by this node is the OPC sent from the remote node */
            opc = MTP3_RL_GET_OPC_VALUE(ohdr.label);

            sio = MTP3_HDR_GET_SIO(ohdr) & (MTP3_SIO_UP_MASK | MTP3_NIC_MASK);

            ISUP_CRITICAL(("__ISUP_HandleMTP3MgmtMsg_CCITT:Recieved "
                         "MTP3 STATUS_UPU_UNAVAILABLE Destination PC %d\n",dpc));


            ckgp_list = ISUP_FindCkgpList(config_stat->opc_dpc_ni, isdsmlocal);
            if (ckgp_list == NULL)
            {
                ITS_EVENT_TERM(evt);
                return !ITS_SUCCESS;
            }

            PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_UNAVAIL);
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

                for(j = 0; j < cicsInckg ; ++j)
                {
                    if ((ckgp_info.usable_cics[0] & (0x00000001 << j)) != 0)
                    {
                        cic = (ckgp_info.ckgp_id * cicsInckg) + (j+1);
                        cont = ITS_FALSE;
                        break;
                    }
                }
                if(cont == ITS_FALSE) 
                {
                    break;
                }
            }
            ISUP_ReleaseCkgpList(ckgp_list, isdsmlocal);

            /* CIC not found for that DPC */
            if(cont)
            {
                ret = ITS_ENOTCONFIG;
                break;
            }
                
            /* Obtain PCIC from CIC, OPC & DPC */
            ISUP_PCICFromParts(&pcic, opc, dpc, sio, cic);

            cic_rec = ISUP_FindPcic(pcic, isdsmlocal);
            if(cic_rec == NULL)
            {
                ISUP_ERROR(("HandleMTP3MgmtMsg::CiC Record not found %d\n",cic));
                break;
            }

            ret = ISUP_FindOpcDpc(config_stat->opc_dpc_ni, &config_info,
                                                            isdsmlocal);
            if (ret != ITS_SUCCESS)
            {
                 ISUP_ERROR(("HandleMTP3MgmtMsg::Erorr "));
            }
            SPRC_SendUPTToMTP3_CCITT(cic_rec, &config_info);
            ISUP_ReleaseOpcDpc(&config_info);

            ret = __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T4,
                      config_stat->tmr_hndl_info[ITS_ISUP_TIMER_T4].tmr_value);

            if (ret != ITS_SUCCESS)
            {
                ISUP_ERROR(("ITS_ISUP_TIMER_T4 :Failed to start T4. pcic 0x%08x,"
                            " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
            }

            ISUP_ReleaseCic(cic_rec, isdsmlocal);
            
            /* 
             *  Change the status to ISUP_REMOTE_UNAVAILABLE 
             *  to restrict further traffic.
             */
            config_stat->remote_isup_stat = ISUP_REMOTE_UNAVAILABLE;


            ISUP_Alarm_CCITT(3413, __FILE__, __LINE__, "DPC : %d", 
                             MTP3_RL_GET_OPC_VALUE(hdr.label));

            mgmtdata_ind.statId = ITS_ISUP_UPU_INACCESS_IND;
            mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
            mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);
            mgmtdata_ind.sio = ohdr.sio; 
            SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
            break;

        case MTP3_STATUS_UPU_UNEQUIP:
            /* DPC sent from the remote node */
            dpc = MTP3_RL_GET_DPC_VALUE(ohdr.label);
            
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

            PEG_IncrPeg(&config_stat->ISUP_DEST_PEGS, PEG_ISUP_DEST_REM_UNAVAIL);

            ISUP_Alarm_CCITT(3414, __FILE__, __LINE__, "DPC : %d", 
                             MTP3_RL_GET_OPC_VALUE(hdr.label));

            /*
             *  When user part recieves this message we will inform to
             *  management system to restrict further traffic.We shall
             *  not initiate the availablity test.
             */

            mgmtdata_ind.statId = ITS_ISUP_UPU_UNEQUIPPED_IND;
            mgmtdata_ind.dpc = MTP3_RL_GET_OPC_VALUE(hdr.label);
            mgmtdata_ind.opc = MTP3_RL_GET_DPC_VALUE(hdr.label);
            mgmtdata_ind.sio = ohdr.sio; 
            SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_ISUP_INV_VCIC, &mgmtdata_ind);
            break;

        default :
            ISUP_ERROR(("Unknown MTP3 Status message recieved \n"));
            break;

        } 

        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        break;

    default :

        break;
    }

    ITS_EVENT_TERM(evt);
    return ret;
}

ITS_OCTET
__ISUP_ValidateParamCompatability_CCITT(ITS_Class V_Class,ITS_EVENT *event,
                                                                ITS_OCTET mType)
{
    int index = 0, i , compLen =0,optLen=0 ,unknowParamInd =0 ;
    ITS_OCTET *ptr;
    ITS_OCTET *margs, *vargs, *oargs;
    int nmargs = 0, nvargs = 0, noargs = 0;
    ITS_BOOLEAN paramFound = ITS_FALSE, compParamFound = ITS_FALSE;
    __ISUP_HandleUnrecParamProc unrecParamProc = NULL;
    ITS_OCTET ret;
    ISUP_PARAM_COMPAT_INFO_DATA compInfo;
    

    ISUP_MSG_DESC *desc = NULL;
    ITS_OCTET *tmp;
    __ISUP_ComputeMSizeProc computeMSize = NULL;

    ISUP_DEBUG(("---- __ISUP_ValidateParamCompatability_CCITT -----\n"));
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
        ITS_C_ASSERT(compLen > 0);

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
                ISUP_DEBUG(("Unknown Param Found in Optional 0x%x\n", *ptr));
                unknowParamInd++;
            }

            if (*ptr == ISUP_PRM_PARAM_COMPAT_INFO)
            {
                tmp = 0;
                tmp = ptr;
                ptr++;
                compLen = *ptr;
                ptr++;
                memcpy(&compInfo,ptr,compLen);
                ptr += compLen;
                compParamFound = ITS_TRUE;
                continue;
            }
            else if (*ptr == ISUP_PRM_OPT_FWD_CALL_INDICATORS ||
                            *ptr == ISUP_PRM_OPT_BKWD_CALL_INDICATORS )
            {
                /* Skip the Tag and Length to get the value */
                ptr += 2; 
                
                /* Check for the presence of SSI */
                if (*ptr | OFWD_ADDITNL_INFO_SENT)
                {
                    SSI_Found = ITS_TRUE;
                }
                ptr++;
                continue;
            }

 
            if(compParamFound)
            {
                optLen += compLen+2;
            }

            ptr++;
            compLen = *ptr;
            ptr += compLen +1;
        }

        /* We didn't find some param in our list */
        if (unknowParamInd)
        {
            if (compParamFound)
            {
                /* Call the variant handlling function */
                unrecParamProc = ISUP_HANDLE_UNREC_PARAM(V_Class);
                ret = unrecParamProc(V_Class,mType,compInfo.instructions);
                if(ret == ISUP_DISCARD_PARAM)
                {
                    /* FIXME discard parameter from the event*/
                    return ITS_SUCCESS;
                }
                else
                {
                    return ret;
                }
            }
            else
            {
                if (ISUP_CLASS_INFO(V_Class)->pass_on_flag != ITS_TRUE)
                {
                    return ISUP_SEND_CFN_MSG;
                }
                else
                {
                    return ISUP_PASS_ON_MSG;
                
                }
            }
        }
        else
        {
            if (SSI_Found)
            {
                return ISUP_SEGMENT_MSG;
            }
            else
            {
                return ITS_SUCCESS;
            }
        }
    }
    else
    {
        return ITS_SUCCESS;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will handle Overlen Mesg for Segmentation purpose 
 *
 *  Input Parameters:
 *
 *      msgProc
 *      cic_rec 
 *      config_info
 *      src - Source of the event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NONE.
 ****************************************************************************/
void
__ISUP_HandleOverlenMsg_CCITT(__ISUP_MsgHandlerProc msgProc, 
                        ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_EVENT saved_event;
    ITS_OCTET src;
    ITS_UINT offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT) +
                                                  sizeof(ITS_USHORT);

    ISUP_DEBUG(("--- Sending the Saved Event to FSM ---\n"));

    src =  ISUP_SRC_L3_ITU;

    switch(cic_rec->lastOverlenMsg)
    {
    case ISUP_MSG_IAM:
       ITS_EVENT_INIT(&saved_event, ITS_MTP3_CCITT_SRC,
                                  cic_rec->cpc_msg_len + offset);
       __ISUP_FillLabel_CCITT(&saved_event, cic_rec, config_info);
       memcpy(&saved_event.data[offset], cic_rec->cpc_msg,
                                     cic_rec->cpc_msg_len);

       /* Send the stored message to the message handler */
       (*msgProc)(&saved_event, cic_rec, config_info, src);
       break;

    case ISUP_MSG_ACM:
       ITS_EVENT_INIT(&saved_event, ITS_MTP3_CCITT_SRC, 
                                  cic_rec->cpc_msg_len + offset);
       __ISUP_FillLabel_CCITT(&saved_event, cic_rec, config_info);
       memcpy(&saved_event.data[offset], cic_rec->cpc_msg,
                                    cic_rec->cpc_msg_len);

       /* Send the stored message to the message handler */
       (*msgProc)(&saved_event, cic_rec, config_info, src);
       break;

    case ISUP_MSG_ANM:
       ITS_EVENT_INIT(&saved_event, ITS_MTP3_CCITT_SRC,
                                 cic_rec->cpc_msg_len + offset);
       __ISUP_FillLabel_CCITT(&saved_event, cic_rec, config_info);
       memcpy(&saved_event.data[offset], cic_rec->cpc_msg,
                                    cic_rec->cpc_msg_len);

       /* Send the stored message to the message handler */
       (*msgProc)(&saved_event, cic_rec, config_info, src);
       break;

    case ISUP_MSG_CPG:
       ITS_EVENT_INIT(&saved_event, ITS_MTP3_CCITT_SRC,
                                cic_rec->cpc_msg_len + offset);
       __ISUP_FillLabel_CCITT(&saved_event, cic_rec, config_info);
       memcpy(&saved_event.data[offset], cic_rec->cpc_msg,
                                    cic_rec->cpc_msg_len);

       /* Send the stored message to the message handler */
       (*msgProc)(&saved_event, cic_rec, config_info, src);
       break;

    case ISUP_MSG_CON:
       ITS_EVENT_INIT(&saved_event, ITS_MTP3_CCITT_SRC,
                               cic_rec->cpc_msg_len + offset);
       __ISUP_FillLabel_CCITT(&saved_event, cic_rec, config_info);
       memcpy(&saved_event.data[offset], cic_rec->cpc_msg,
                                    cic_rec->cpc_msg_len);

       /* Send the stored message to the message handler */
       (*msgProc)(&saved_event, cic_rec, config_info, src);
       break;

    default:
       break;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will store Overlen Mesg for Segmentation purpose
 *
 *  Input Parameters:
 *
 *      event
 *      cic_rec
 *      config_info
 *      msgType - Message Type 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NONE.
 ****************************************************************************/
void
__ISUP_StoreOverlenMsg_CCITT(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET msgType)  
{
    ITS_USHORT offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT)
                                                 + sizeof(ITS_USHORT);

    ISUP_DEBUG(("\n ---- Received Overlen Message of Type 0x%0x -------\n",
                                                                 msgType));
    switch(msgType)
    {
    case ISUP_MSG_IAM:
        /* Store the message in cic_rec */
        cic_rec->cpc_msg_len = event->len - offset;
        memcpy(cic_rec->cpc_msg, &event->data[offset], cic_rec->cpc_msg_len);
        break;

    case ISUP_MSG_ACM:
        /* Store the message in cic_rec */
        cic_rec->cpc_msg_len = event->len - offset;
        memcpy(cic_rec->cpc_msg, &event->data[offset],cic_rec->cpc_msg_len); 
        break;

    case ISUP_MSG_ANM:
        /* Store the message in cic_rec */
        cic_rec->cpc_msg_len = event->len - offset;
        memcpy(cic_rec->cpc_msg, &event->data[offset], cic_rec->cpc_msg_len); 
        break;

    case ISUP_MSG_CPG:
        /* Store the message in cic_rec */
        cic_rec->cpc_msg_len = event->len - offset;
        memcpy(cic_rec->cpc_msg, &event->data[offset], cic_rec->cpc_msg_len); 
        break;

    case ISUP_MSG_CON:
        /* Store the message in cic_rec */
        cic_rec->cpc_msg_len = event->len - offset;
        memcpy(cic_rec->cpc_msg, &event->data[offset], cic_rec->cpc_msg_len);
        break;

    default:
        return;

    }

    /* Start the Timer T34 */
    __ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T34,
                           config_info->tmr_hndl_info
                                  [ITS_ISUP_TIMER_T34].tmr_value);
    /* Raise an Alarm */

    /* Set the Simple Segmentation State to
     * WAIT_for_SGM in cic_rec
     */
    cic_rec->ssi_state = SSI_WAIT_FOR_SGM;

    /* Save this msgType in cic_rec */
    cic_rec->lastOverlenMsg = msgType;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will assemble Overlen Mesg for Segmentation purpose
 *
 *  Input Parameters:
 *
 *      event
 *      cic_rec
 *      config_info
 *      msgType - Message Type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NONE.
 ****************************************************************************/
void
__ISUP_AssembleOverlenMsg_CCITT(__ISUP_MsgHandlerProc msgProc, ITS_EVENT *ev,
                      ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info,
                                                               ITS_OCTET src)
{
    ITS_EVENT new_event;
    ITS_USHORT len = 0, index = 0, offset = 0;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;
   
    ISUP_DEBUG(("\n-- Assembling the Stored and SGM Message --\n"));


    /* Get the offset to reach the Encoded message
     * in SGM
     */
    offset = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER) +
                                                sizeof(ITS_USHORT);
    len = (ev->len) - offset - 1;
    
    switch(cic_rec->lastOverlenMsg)
    {
    case ISUP_MSG_IAM:
    
        index = cic_rec->cpc_msg_len - 1;
        ITS_EVENT_INIT(&new_event, ITS_MTP3_SRC, index + ev->len);
        __ISUP_FillLabel_CCITT(&new_event, cic_rec, config_info);
        memcpy((char *)&new_event.data[offset],(char *)cic_rec->cpc_msg,
                                                  cic_rec->cpc_msg_len);

        /* Override the End of Optional Param 
         * Copy the SGM mesg param into newly formed event 
         */
        memcpy((char *)&new_event.data[index + offset],
                                 (char *)&ev->data[offset + 2], len);
        break;

    case ISUP_MSG_ACM:
        index = cic_rec->cpc_msg_len - 1;
        ITS_EVENT_INIT(&new_event, ITS_MTP3_SRC, index + ev->len);
        __ISUP_FillLabel_CCITT(&new_event, cic_rec, config_info);
        memcpy(&new_event.data[offset], cic_rec->cpc_msg,
                                              cic_rec->cpc_msg_len);

        /* Override the End of Optional Param 
         * Copy the SGM mesg param into newly formed event 
         */
        memcpy((char *)&new_event.data[index + offset],
                                   (char *)&ev->data[offset + 2], len);
        break;

    case ISUP_MSG_ANM:
        index = cic_rec->cpc_msg_len - 1;
        ITS_EVENT_INIT(&new_event, ITS_MTP3_SRC, index + ev->len);
        __ISUP_FillLabel_CCITT(&new_event, cic_rec, config_info);
        memcpy(&new_event.data[offset], cic_rec->cpc_msg,
                                             cic_rec->cpc_msg_len);

        /* Override the End of Optional Param 
         * Copy the SGM mesg param into newly formed event 
         */
        memcpy((char *)&new_event.data[index + offset],
                                   (char *)&ev->data[offset + 2], len);
        break;

    case ISUP_MSG_CPG:
        index = cic_rec->cpc_msg_len - 1;
        ITS_EVENT_INIT(&new_event, ITS_MTP3_SRC, index + ev->len);
        __ISUP_FillLabel_CCITT(&new_event, cic_rec, config_info);
        memcpy(&new_event.data[offset], cic_rec->cpc_msg,
                                            cic_rec->cpc_msg_len);

        /* Override the End of Optional Param 
         * Copy the SGM mesg param into newly formed event 
         */
        memcpy((char *)&new_event.data[index + offset],
                                   (char *)&ev->data[offset + 2], len);
        break;

    case ISUP_MSG_CON:
        index = cic_rec->cpc_msg_len - 1;
        ITS_EVENT_INIT(&new_event, ITS_MTP3_SRC, index + ev->len);
        __ISUP_FillLabel_CCITT(&new_event, cic_rec, config_info);
        memcpy(&new_event.data[offset], cic_rec->cpc_msg,
                                           cic_rec->cpc_msg_len);

        /* Override the End of Optional Param 
         * Copy the SGM mesg param into newly formed event 
         */
        memcpy((char *)&new_event.data[index + offset],
                                   (char *)&ev->data[offset + 2], len);
        break;

    default:
        break;
    }

    /* Free the event carrying SGM message */
    /* This rite thing to do, but follow the consistancy
     * This is taken care by the GetNextEven() of TransTaskQue
     */
    /* ITS_EVENT_TER(ev);*/

    /* Get MsgHandlerProc from variant class pointer using call_state
           and msgType */
    msgProc = VAR_GetMsgProc(config_info->isup_var_class,
                            cic_rec->lastOverlenMsg, cic_rec->fsm_state);

    /* Call MsgHandler with appropriate input params */
    (*msgProc)(&new_event, cic_rec, config_info, src);

    ISUP_ReleaseCic(cic_rec, isdsmlocal);
    ISUP_ReleaseOpcDpc(config_info);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will Fill the MTP3 Header to the EVENT 
 *
 *  Input Parameters:
 *
 *      event
 *      cic_rec
 *      config_info
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NONE.
 ****************************************************************************/
void
__ISUP_FillLabel_CCITT(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                                         ISUP_OPC_DPC_INFO *config_info)
{
    ITS_USHORT cic = 0;
    int index = 0;

    /* Fill in MTP3 Message Type */
    event->data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event->data[index], (char *)&(config_info->in_hdr),
            sizeof(MTP3_HEADER_CCITT));
    index += sizeof(MTP3_HEADER_CCITT);

    /* Get the cic */
    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    /* Fill in the CIC */
    event->data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event->data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    /* event->data[index] = type; */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function will Check the presence of ACL parameter in REL
 *      Message and start the Timers, Send an indication to HOLD/UnHOLD
 *      the Traffic 
 *
 *  Input Parameters:
 *
 *      event
 *      mesg_desc
 *      cic_rec
 *      config_info
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NONE.
 ****************************************************************************/
void
__ISUP_CheckRmtCongestion(ITS_EVENT* event, ISUP_MSG_DESC *msg_desc,
                   ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO config_info)
{
    int i = 0, nOptparams = 0, ieCount = 0;
    ITS_OCTET congLev = 0;
    ITS_ISUP_IE ies[14];
    ITS_BOOLEAN conglevparamFound = ITS_FALSE;
    static ITS_BOOLEAN conglev1indSent = ITS_FALSE;
    static ITS_BOOLEAN conglev2indSent = ITS_FALSE;

    ISUP_OPC_DPC_STAT *config_stat;
    ITS_BOOLEAN isdsmlocal = ITS_TRUE;
    ITS_BOOLEAN firstTime  = ITS_FALSE;

    ISUP_DEBUG(("\n---- __ISUP_CheckRmtCongestion -----\n"));

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
                congLev = ies[i].param_data.autoCongestionLevel.level;
                conglevparamFound = ITS_TRUE;

                if (congLev == AUTO_CONGESTION_LEVEL1)
                {
                     /* Send an indication the application
                     * to control the traffic
                     */
                    if (!conglev1indSent)
                    {
	                if(!conglev2indSent)
		        {
                           PEG_IncrPeg(&(config_info.ISUP_DEST_PEGS), PEG_ISUP_DEST_REM_CONGES);
                           firstTime = ITS_TRUE;
			}

                        conglev1indSent = ITS_TRUE;
                        conglev2indSent = ITS_FALSE;
                        SPRC_SendIndToApp_CCITT(ITS_ISUP_RMT_CONGLEVEL1_IND,
                                                cic_rec);

                        /* FIXME - Raise an Alarm */

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

                }
                else if (congLev == AUTO_CONGESTION_LEVEL2)
                {
                    /* Send an indication the application
                     * to control the traffic
                     */
                    if (!conglev2indSent)
                    {
                         if(!conglev1indSent)
                        {
                           PEG_IncrPeg(&(config_info.ISUP_DEST_PEGS),PEG_ISUP_DEST_REM_CONGES);
                           firstTime = ITS_TRUE;
                        }

                        conglev2indSent = ITS_TRUE;
                        conglev1indSent = ITS_FALSE;
                        SPRC_SendIndToApp_CCITT(ITS_ISUP_RMT_CONGLEVEL2_IND,
                                                      cic_rec);
                        /* FIXME - Raise an Alarm */

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

                }
                else if ((congLev != AUTO_CONGESTION_LEVEL1 &&
                          congLev != AUTO_CONGESTION_LEVEL2 ) &&
                          config_info.isup_rmt_conglev)
                {
                    /* Send an indication the application
                     * to cease the congestion control
                     */
                    PEG_IncrPeg(&(config_info.ISUP_DEST_PEGS),PEG_ISUP_DEST_REM_CONGES_SEIZED);

                    conglev1indSent = ITS_FALSE;
                    conglev2indSent = ITS_FALSE;

                    SPRC_SendIndToApp_CCITT(ITS_ISUP_RMT_NOCONG_IND,
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

                    /* FIXME - Raise an Alarm */
                }
                break;

            case ISUP_PRM_ACCESS_DELIVERY_INFO:
            case ISUP_PRM_CAUSE_INDICATORS:
            case ISUP_PRM_REDIRECTING_NUM:
            case ISUP_PRM_REDIRECTION_INFO:
            case ISUP_PRM_USER_TO_USER_INFO:
            case ISUP_PRM_NTWK_SPECIFIC_FACILITIES:
            case ISUP_PRM_SIGNALLING_POINT_CODE:
            case ISUP_PRM_PARAM_COMPAT_INFO:
            case ISUP_PRM_REDIRECTION_NUM_RESTRICT:
            case ISUP_PRM_USER_TO_USER_INDICATORS:
            case ISUP_PRM_ACCESS_TRANSPORT:
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
            /* Set the Remote Congestion Level to off */
            config_info.isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
            ISUP_UpdateOpcDpc(&config_info);

            /* look and update config stat for this opc-dpc */
            config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, isdsmlocal);
            config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
            ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

            SPRC_SendIndToApp_CCITT(ITS_ISUP_RMT_NOCONG_IND, cic_rec);
            /* FIXME - Raise an Alarm */
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

        /* Set the Remote Congestion Level to off */
        config_info.isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
        ISUP_UpdateOpcDpc(&config_info);

        /* look and update config stat for this opc-dpc */
        config_stat = ISUP_FindOpcDpcStat(config_info.opc_dpc_ni, isdsmlocal);
        config_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
        ISUP_ReleaseOpcDpcStat(config_stat, isdsmlocal);

        SPRC_SendIndToApp_CCITT(ITS_ISUP_RMT_NOCONG_IND, cic_rec);
        /* FIXME - Raise an Alarm */
    }
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
ISUP_IncrementRcvdPegs(ISUP_OPC_DPC_INFO *config_info, ITS_OCTET msgType)
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

    case ISUP_MSG_CON:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_CON_RCVD);
        break;

    case ISUP_MSG_IDR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_IDR_RCVD);
        break;

    case ISUP_MSG_IRS:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_IRS_RCVD);
        break;

    case ISUP_MSG_FAA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_FAA_RCVD);
        break;

    case ISUP_MSG_NRM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_NRM_RCVD);
        break;

    case ISUP_MSG_OLM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_OLM_RCVD);
        break;

    case ISUP_MSG_SAM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_SAM_RCVD);
        break;

    case ISUP_MSG_SGM:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_SGM_RCVD);
        break;

    case ISUP_MSG_UPA:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_UPA_RCVD);
        break;

    case ISUP_MSG_UPT:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_UPT_RCVD);
        break;

    case ISUP_MSG_USR:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_USR_RCVD);
        break;

    case ISUP_MSG_LOP:
        PEG_IncrPeg(&config_info->ISUP_PEGS_RCVD,
                                  PEG_ISUP_REMOTE_LOP_RCVD);
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
 *  Ramesh K V  05-09-2005   BCGI Problem   Short name used to resolve compile
 *                                          error in PRC
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
    ISUP_GetAllDestCfgInfo_CCITT(&dest_info, &noEnts);

    for ( j = 0; j < noEnts; j++)
    {
        memset(&opc_dpc_ni, 0, sizeof(MTP3_HEADER));
        MTP3_RL_SET_OPC_VALUE(opc_dpc_ni.label,
                                   (*(&dest_info))[j].cfg.opc);
        MTP3_RL_SET_DPC_VALUE(opc_dpc_ni.label,
                                   (*(&dest_info))[j].cfg.dpc);
        MTP3_HDR_SET_SIO(opc_dpc_ni,
                              (*(&dest_info))[j].cfg.sio);

        config_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
        if (config_stat == NULL)
        {
           ISUP_WARNING(("Failed to find Opc %d Dpc  %d\n",
                          MTP3_RL_GET_OPC_VALUE(opc_dpc_ni.label), 
                          MTP3_RL_GET_DPC_VALUE(opc_dpc_ni.label)));
        }
        else
        {
           if(localcong_level == CCITT_ISUP_conglevel1)
           {
              /* if change in level; set level to 1 */
              ISUP_SET_OPC_DPC_LOC_CONG(config_stat, ISUP_LOC_CONGES_LEVEL1);
           }
           else if(localcong_level == CCITT_ISUP_conglevel2)
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

