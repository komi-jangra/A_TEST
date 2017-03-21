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
 *  ID: $Id: itu_generic_state_itu93.c,v 1.1.1.1 2007-10-08 11:12:19 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:00  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:54:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.3.6.1.12.1  2004/12/29 14:56:05  csireesh
 * LOG: ISUP OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.3.6.1  2004/01/05 10:10:46  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.4.2.3.2.1  2003/09/05 09:48:14  akumar
 * LOG: Modifications for msg based redundancy scheme.
 * LOG:
 * LOG: Revision 7.4.2.3  2003/07/25 05:16:23  akumar
 * LOG: ITU National Stuff and SGM modification done.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/05/07 11:03:13  ssingh
 * LOG: Latest Changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.4  2003/05/02 14:36:17  ssingh
 * LOG: ANSI changes propped to ITU (common and related).
 * LOG:
 * LOG: Revision 8.3  2003/04/30 05:26:15  akumar
 * LOG: Bug Fix #259. Dual Seizure procedure modified.
 * LOG:
 * LOG: Revision 8.2  2003/04/03 15:29:29  sjaddu
 * LOG: ISUP DSM reorganization.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:31  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.4  2003/01/22 08:49:06  akumar
 * LOG: Added Dual Seizure specific func and li'l change wrt COT
 * LOG:
 * LOG: Revision 7.3  2002/12/31 05:36:16  akumar
 * LOG: Segmentation Procedure has been added
 * LOG:
 * LOG: Revision 7.2  2002/10/10 10:40:12  sjaddu
 * LOG: Added Alarms for ITU93/97.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:38  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/08/01 15:57:50  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 1.2.2.1  2002/07/10 19:34:16  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:46:49  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/14 18:08:01  sjaddu
 * LOG: Added file for handling messages occur in all states.
 * LOG:
 *
 ****************************************************************************/

#undef ANSI
#undef CCITT
#define CCITT

#include <stdlib.h>
#include <string.h>

#include <its.h>

#include <itu/isup.h>
#include <isup_intern.h>
#include <isup_93.h>

ITS_BOOLEAN OFCI_Found = ITS_FALSE;
ITS_BOOLEAN OBCI_Found = ITS_FALSE;

/*
 * Functions for handling messages in the generic state for ITU93 variant.
 * This is considered to be the generic ITU variant, and all other ITU variants
 * use these functions as defaults if they do not have different behaviour.
 */
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an UPA received is done here.
 *      The message is forwarded to the application if received from the
 *      network, or vice versa.
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
void
__ISUP_Received_UPA_ITU93( ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src )
{
    if (src == ISUP_SRC_L3_ITU)
    {
        ISUP_DEBUG(("Received UPA in from MTP3, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));

        /* chage the status ISUP_REMOTE_ISUP_STATUS */
        config_info->remote_isup_stat = ISUP_REMOTE_AVAILABLE;

        /* Stop timers T4 */
        __ISUP_StopTimer(cic_rec,ITS_ISUP_TIMER_T4);
    }
    else
    {
        ISUP_DEBUG(("Received UPA in IDLE from APP, pcic 0x%08x, vcic %d.\n",
                     cic_rec->pcic, cic_rec->vcic));
        /* Send to L3 */
        SPRC_SendIsupToMTP3_CCITT(msg, cic_rec->vcic);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      The processing for an T4 time out received is done here.
 *      The message is forwarded to the application if received from the
 *      network, or vice versa.
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
void
__ISUP_Received_TimeoutT4_ITU93(ISUP_TIMER_ENTRY* t_entry,
                                ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info)
{
    if (config_info->remote_isup_stat == ISUP_REMOTE_AVAILABLE)
    {
        /* FIXME : we never stop the T4 timer */
        return ; 
    }

    ISUP_Alarm_CCITT(3499, __FILE__, __LINE__, "pcic %x", cic_rec->pcic);

    /* Resend UPT */
    SPRC_SendUPTToMTP3_CCITT(cic_rec,config_info);

    /* If T4 expires the procedure is re started (Q.764 2.13.2) */
    if (__ISUP_StartTimer(cic_rec, ITS_ISUP_TIMER_T4,
        config_info->tmr_hndl_info[ITS_ISUP_TIMER_T4].tmr_value) != ITS_SUCCESS)
    {
        ISUP_ERROR(("ITS_ISUP_TIMER_T4 :Failed to start T4. pcic 0x%08x,"
                    " vcic %d.\n", cic_rec->pcic, cic_rec->vcic));
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is the main function for Segmentation Procedure, it
 *      will be called from FSM, whenever an Overlen MSG is received by the
 *      stack, It performs the Segmentation and then encode the messages to
 *      be sent to L3.
 *
 *  Input Parameters:
 *      event - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      len - Message Length 
 *      type - Message Type
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
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
__ISUP_SegmentOverlenMsg_ITU93(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                                 ITS_OCTET type, ISUP_OPC_DPC_INFO *config_info)
{
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    ITS_ISUP_IE  origMsgParam[ITS_MAX_ISUP_IES];
    ITS_ISUP_IE  segmentMsgParam[ITS_MAX_ISUP_IES];
    ITS_ISUP_IE  newSegmentMsgParam[ITS_MAX_ISUP_IES];
    ITS_BOOLEAN optcallindFound = ITS_FALSE;
    ITS_USHORT index = 0, data_len = 0;
    int ieCount = 0, origMsgParamCount = 0, segmentMsgParamCount = 0;
    int i = 0, k = 0, newSegmentMsgParamCount = 0, sgm_length = 0;
    
    ISUP_DEBUG(("\n--- Overlen Mesg received of TYPE 0x%02x from APP ---\n",
                                                                     type));

    memset((char *)&ies, 0, sizeof(ies));
    memset((char *)&origMsgParam, 0, sizeof(origMsgParam));
    memset((char *)&segmentMsgParam, 0, sizeof(segmentMsgParam));
    memset((char *)&newSegmentMsgParam, 0, sizeof(newSegmentMsgParam));

    index = sizeof(ITS_OCTET) + sizeof(MTP3_HEADER_CCITT) +
                  sizeof(ITS_USHORT) + sizeof(ITS_OCTET);
    data_len = event->len - index;

    /* Decode the Received event into array of IEs */
    ISUP_MTP3Decode_CCITT(&event->data[index], data_len, type, ies, &ieCount,
                                            config_info->isup_var_class);

    optcallindFound = __ISUP_SplitOverlenMsg_ITU93(ies, ieCount, origMsgParam,
                                          &origMsgParamCount, segmentMsgParam,
                                          &segmentMsgParamCount, &sgm_length);
    switch (type)
    {
    case ISUP_MSG_IAM:

       /* See if the OFCI is not there
        * Include the OFCI in the message
        * set the SSI
        */
       if (!optcallindFound)
       {
          origMsgParam[origMsgParamCount].param_id =
                                   ISUP_PRM_OPT_FWD_CALL_INDICATORS;
          origMsgParam[origMsgParamCount].param_length = 1;
          origMsgParam[origMsgParamCount].param_data.
                  optFwdCallIndicators.indics = OFWD_ADDITNL_INFO_SENT;
          origMsgParamCount++;
       }
       break;

    case ISUP_MSG_ACM:
    case ISUP_MSG_ANM:
    case ISUP_MSG_CON:
    case ISUP_MSG_CPG:

       /* See if the OBCI is not there
        * Include the OBCI in the message
        * set the SSI
        */
       if (!optcallindFound)
       {
          origMsgParam[origMsgParamCount].param_id =
                                   ISUP_PRM_OPT_BKWD_CALL_INDICATORS;
          origMsgParam[origMsgParamCount].param_length = 1;
          origMsgParam[origMsgParamCount].param_data.
                  optBkwdCallIndicators.obkwd_ind = OBWD_ADDITNL_INFO_SENT;
          origMsgParamCount++;
       }
       break;

    default:
       break;

    }
 
 
    /* Convert the message into an Event and send to L3 */
    __ISUP_SendOverlenMsg_ITU93(type, cic_rec, config_info, origMsgParam,
                                                       origMsgParamCount);

    /* If the SGM msg size is > 272 octets, Remove UUI and Unrec
     * parameters - Only UUI is removed at the moment
     */
    if (sgm_length > MTP3_MAX_SIF_LENGTH)
    {
       for (i = 0; i < segmentMsgParamCount; i++)
       {
          switch (segmentMsgParam[i].param_id)
          {
          case ISUP_PRM_USER_TO_USER_INFO:
               break;
          case ISUP_PRM_GENERIC_NOTIFICATION:
          case ISUP_PRM_GENERIC_NUM:
          case ISUP_PRM_GENERIC_DIGITS:
          case ISUP_PRM_ACCESS_TRANSPORT:
               /* Copy the Old SGM msg param into new one */
               newSegmentMsgParam[k].param_id =
                         segmentMsgParam[i].param_id;
               newSegmentMsgParam[k].param_length =
                         segmentMsgParam[i].param_length;
               memcpy(&newSegmentMsgParam[k].param_data,
                              &segmentMsgParam[i].param_data,
                              segmentMsgParam[i].param_length);
               k++;
               break;
          }
       }
       newSegmentMsgParamCount = k;
       /* Create the SGM Message and send to L3 */
       __ISUP_SendOverlenMsg_ITU93(ISUP_MSG_SGM, cic_rec, config_info,
                                   newSegmentMsgParam, newSegmentMsgParamCount);
    }
    else
    {
        /* Create the SGM Message and send to L3 */
        __ISUP_SendOverlenMsg_ITU93(ISUP_MSG_SGM, cic_rec, config_info,
                                      segmentMsgParam, segmentMsgParamCount);
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function shall Segment the Overlen Message in two IEs, One 
        hold the IEs without the SGM param and the other hold SGM IE 
 *
 *  Input Parameters:
 *      ies - Original Array containing all the IEs including the SGM
 *      ieCount - Original Array Count
 *      savedMsgParam - IEs array without SGM ie
 *      savedMsgParamCount - savedMsgParam Count
 *      segmentMsgParam - Array of SGM Message IEs
 *      origMsgParamCount - Array of SGM Message Count
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
ITS_BOOLEAN
__ISUP_SplitOverlenMsg_ITU93(ITS_ISUP_IE *ies, int ieCount,
                                   ITS_ISUP_IE *savedMsgParam,
                                      int *savedMsgParamCount,
                                 ITS_ISUP_IE *segmentMsgParam,
                                    int *segmentMsgParamCount, int *sgm_length)
{
    ITS_BOOLEAN optcallindFound = ITS_FALSE; 
    ITS_UINT i = 0, j = 0, savedMsgIndex = 0;

    for (i = 0; i < ieCount; i++)
    {
         switch(ies[i].param_id)
         {
         case ISUP_PRM_GENERIC_NOTIFICATION:
         case ISUP_PRM_GENERIC_NUM:
         case ISUP_PRM_GENERIC_DIGITS:
         case ISUP_PRM_USER_TO_USER_INFO:
         case ISUP_PRM_ACCESS_TRANSPORT:

             /* Found the Optional Parameter for SGM message */
             segmentMsgParam[j].param_id = ies[i].param_id;
             segmentMsgParam[j].param_length = ies[i].param_length;
             memcpy(&segmentMsgParam[j].param_data,
                            &ies[i].param_data, ies[i].param_length);
             *sgm_length += ies[i].param_length + 2;
             j++;
             break;

         case ISUP_PRM_OPT_BKWD_CALL_INDICATORS:

             /* Found the Optional B/W call indicator */
             optcallindFound = ITS_TRUE;

             savedMsgParam[savedMsgIndex].param_id = ies[i].param_id;
             savedMsgParam[savedMsgIndex].param_length = ies[i].param_length;
             memcpy(&savedMsgParam[savedMsgIndex].param_data,
                    &ies[i].param_data, ies[i].param_length);
             savedMsgParam[savedMsgIndex].param_data.
                        optBkwdCallIndicators.obkwd_ind |= 0x04;
             savedMsgIndex++;
             break;

         case ISUP_PRM_OPT_FWD_CALL_INDICATORS:

             /* Found the Optional F/W call indicator */
             optcallindFound = ITS_TRUE;

             savedMsgParam[savedMsgIndex].param_id = ies[i].param_id;
             savedMsgParam[savedMsgIndex].param_length = ies[i].param_length;
             memcpy(&savedMsgParam[savedMsgIndex].param_data,
                    &ies[i].param_data, ies[i].param_length);
             savedMsgParam[savedMsgIndex].param_data.
                             optFwdCallIndicators.indics |= 0x04;
             savedMsgIndex++;
             break;

         default:
             /* Fixed M, Variable M and Ramaining optional param */

             savedMsgParam[savedMsgIndex].param_id = ies[i].param_id;
             savedMsgParam[savedMsgIndex].param_length = ies[i].param_length;
             memcpy(&savedMsgParam[savedMsgIndex].param_data,
                       &ies[i].param_data, ies[i].param_length);
             savedMsgIndex++;
             break;
         }
    }

    *segmentMsgParamCount = j;
    *savedMsgParamCount = savedMsgIndex;
    return optcallindFound;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function shall Encode the Saved Overlen Message and send
 *      it to L3.
 *
 *  Input Parameters:
 *      type - Message Type 
 *      cic_rec - pointer to the CIC record relevant for this msg.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC.
 *      origMsgParam - Array of Saved Message 
 *      origMsgParamCount - Array of Saved Message Count
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
__ISUP_SendOverlenMsg_ITU93(ITS_OCTET type, ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_ISUP_IE *ies, int ieCount)
{
    ITS_EVENT event;
    ITS_OCTET data[ISUP_MAX_MSG_LEN];
    ITS_USHORT len = 0, cic = 0;
    int index = 0, i = 0; 

    memset((char *)data, 0, ISUP_MAX_MSG_LEN);

    ISUP_MTP3Encode_CCITT(data, &len, type, ies,
                          ieCount, config_info->isup_var_class);

    /* Put data into the ITS_EVENT in the order required by MTP3 -
     * "MTP3MsgType:MTP3_HEADER:CIC:ISUPMsgType:EncodedMsg"
     */
    ITS_EVENT_INIT((&event), (ITS_ISUP_CCITT_SRC), (sizeof(ITS_OCTET)
                    + sizeof(MTP3_HEADER_CCITT) + sizeof(ITS_USHORT)
                    + sizeof(ITS_OCTET) + len));

    /* Fill in MTP3 Message Type */
    index = 0;
    event.data[index++] = MTP3_MSG_USER_DATA;

    /* Fill in MTP3_HEADER */
    memcpy((char *)&event.data[index], (char *)&(config_info->out_hdr),
            sizeof(MTP3_HEADER_CCITT));
    index += sizeof(MTP3_HEADER_CCITT);

    /* Get the cic */
    cic = ISUP_PCIC_TO_CIC(cic_rec->pcic);

    /* Fill in the CIC */
    event.data[index++] = cic & 0xFFU; /* LSB 8 bits */
    event.data[index++] = (cic >> 8) & 0xFFU; /* MSB 4 bits + 4 */

    /* Fill in the ISUP message type */
    event.data[index++] = type;

    /* Fill in Encoded ISUP message data */
    memcpy((char *)&event.data[index], (char *)data, len);

    /* Send the ITS_EVENT with MSG to MTP3 */
    SPRC_SendIsupToMTP3_CCITT(&event, cic_rec->vcic);

    ISUP_DEBUG(("\n--- Sent Overlen/SGM Mesg of TYPE 0x%02x to L3 ---\n",
                                                                  type));

    ITS_EVENT_TERM(&event);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This procedure determines the controlliing exchange
 *
 *  Input Parameters:
 *      msg - the ISUP msg received by the stack as an ITS_EVENT.
 *      cic_rec - cic record for the cic in message
 *      config_info - configuration info for the destination
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
ITS_BOOLEAN
__ISUP_IsExchangeControlling(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info)
{
    ITS_UINT opc, dpc;

    /* Get opc and dpc from config_info structure */
    opc = MTP3_RL_GET_OPC_VALUE(config_info->opc_dpc_ni.label);
    dpc = MTP3_RL_GET_DPC_VALUE(config_info->opc_dpc_ni.label);

    if ((cic_rec->cic_rule == ISUP_CKGP_CTRL_NONE) ||
       ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_EVEN))
       || (!(cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_ODD))
       || ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF)
                                                         && (opc > dpc))
       || (!(cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF)
                                                        && (opc < dpc)))
    {
        /* non-controlling exchange for this call (cic) */
        return ITS_FALSE;
    }
    else if ((cic_rec->cic_rule == ISUP_CKGP_CTRL_ALL) ||
            ((cic_rec->pcic.cic % 2) && (cic_rec->cic_rule == ISUP_CKGP_CTRL_ODD))
            || (!(cic_rec->pcic.cic % 2) &&
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_EVEN))
            || (!(cic_rec->pcic.cic % 2) &&
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF) && (opc > dpc))
            || ((cic_rec->pcic.cic % 2) &&
               (cic_rec->cic_rule == ISUP_CKGP_CTRL_DEF) && (opc < dpc)))
    {
        /* controlling exchange for this call (cic) */
        return ITS_TRUE;
    }

    /* Ideally it should be NEVER reach here */
    return ITS_TRUE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function handles the processing at expiry of T34 timer in the
 *      IDLE, WAITi_IN_COT, WAIT_IN_ACM, WAIT_IN_ANM state.
 *
 *  Input Parameters:
 *      t_entry - The data corresponding to this timeout indication.
 *      cic_rec - The relevant CIC record.
 *      config_info - Configuration info for the OPC-DPC pair for this CIC. 
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
__ISUP_Received_TimeoutT34(ISUP_TIMER_ENTRY* t_entry, ISUP_CIC_INFO *cic_rec,
                                              ISUP_OPC_DPC_INFO *config_info)
{
    __ISUP_MsgHandlerProc msgProc = NULL;

    ISUP_DEBUG(("TimeoutT34 event received in **** state. "
                "Info from CIC rec: pcic 0x%08x, vcic %d, cic %d.\n",
                cic_rec->pcic, cic_rec->vcic, ISUP_PCIC_TO_CIC(cic_rec->pcic)));

    /* Reset the Simple Segmentation State to
     * IDLE in cic_rec
     */
    cic_rec->ssi_state = IDLE;

    /* Remove info about timer from cic_rec */
    ISUP_DeletePndgTmrInfo(cic_rec, ITS_ISUP_TIMER_T34);

    /* Get MsgHandlerProc from variant class pointer using call_state
     * and msgType
     */
    msgProc = VAR_GetMsgProc(config_info->isup_var_class,
                             cic_rec->lastOverlenMsg, cic_rec->fsm_state);

    /* Send the Saved Message to the FSM */
    __ISUP_HandleOverlenMsg_CCITT(msgProc, cic_rec, config_info);

    /* Send the Timeout Indication to the APP */
    SPRC_SendTimeoutIndicToApp_CCITT(cic_rec->vcic, t_entry);
}
