/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2005 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *      
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:51  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:39:51  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: l3-ifc.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * L2:L3 glue
 */

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      L3 entry point
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      trigger - the event that's happening
 *      data    - buffer
 *      len     - sizeof buffer
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
 *
 ************************************************************************/
void
L3_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
        ITS_OCTET *data, ITS_USHORT size)
{
    MTP2_QEntry sig;

#if defined(DEBUG_TRIGGERS)
    printk("L3_Main: trigger %s\n",
           MTP2_TriggerToString(trigger));
#endif
    switch (trigger)
    {
    case LSC_L3_TRIGGER_InService:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_IN_SERVICE;
        QueueOutgoing(link, &sig);
        break;

    case LSC_L3_TRIGGER_OutOfService:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_OUT_OF_SERVICE;
        QueueOutgoing(link, &sig);
        break;

    case LSC_L3_TRIGGER_Stop:
        /*
         * While layer 2 talks about this, layer three doesn't do anything
         * with it.  Ignore it.
         */
         break;

    case LSC_L3_TRIGGER_RemoteProcessorOutage:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_REMOTE_PROCESSOR_OUT;
        QueueOutgoing(link, &sig);
        break;

    case LSC_L3_TRIGGER_RemoteProcessorRecovered:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_REMOTE_PROCESSOR_REC;
        QueueOutgoing(link, &sig);
        break;

    case TXC_L3_TRIGGER_RetrievedMessage:
        sig.elem.size = size;
        sig.signal.signal = L2_L3_RETRIEVED_MSG;
        memcpy(sig.signal.data.sif, data, size);
        QueueOutgoing(link, &sig);
        break;

    case TXC_L3_TRIGGER_RetrievalComplete:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_RETRIEVAL_COMPLETE;
        QueueOutgoing(link, &sig);
        break;

    case RC_L3_TRIGGER_ReceivedMessage:
        sig.elem.size = size;
        memcpy(&sig.signal, data, size);
        sig.signal.signal = L2_L3_DATA;
        QueueOutgoing(link, &sig);
        break;

    case RC_L3_TRIGGER_BSNT:
        ITS_ASSERT(size == sizeof(ITS_OCTET));
        sig.elem.size = MTP2_FIXED_HDR_SIZE + sizeof(ITS_OCTET);
        sig.signal.signal = L2_L3_BSNT;
        sig.signal.data.bsnt = data[0];
        QueueOutgoing(link, &sig);
        break;

    case RC_L3_TRIGGER_BSNTNotRetrievable:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_BSNT_NOT_RETRIEVABLE;
        QueueOutgoing(link, &sig);
        break;

    case TXC_L3_TRIGGER_RetrievalNotPossible:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_RETRIEVAL_NOT_POSSIBLE;
        QueueOutgoing(link, &sig);
        break;

    case TXC_L3_TRIGGER_RTBCleared:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_RTB_CLEARED;
        QueueOutgoing(link, &sig);
        break;

    case RC_L3_TRIGGER_RBCleared:
        sig.elem.size = MTP2_FIXED_HDR_SIZE;
        sig.signal.signal = L2_L3_RB_CLEARED;
        QueueOutgoing(link, &sig);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for IAC\n",
                    trigger);
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Buffer a message for processing
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      signal  - the signal to add
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
 *
 ************************************************************************/
int
L3_Buffer(MTP2_LinkState *link, MTP2_QEntry *sig)
{
printk("L3_Buffer: got data signal = 0x%x\n", sig->signal.signal);
    /* Most signals just consist of a signal value */
    switch (sig->signal.signal)
    {
    case MTP2_T1:
    case MTP2_T2:
    case MTP2_T3:
    case MTP2_T4:
    case MTP2_T5:
    case MTP2_T6:
    case MTP2_T7:
    case MTP2_QUEUED_TRIG:
    case L3_L2_START:
    case L3_L2_STOP:
    case L3_L2_RESUME:
    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
    case L3_L2_EMERGENCY:
    case L3_L2_EMERGENCY_CEASE:
    case L3_L2_RETRIEVE_BSNT:
    case L3_L2_FLOW_CONTROL_START:
    case L3_L2_FLOW_CONTROL_STOP:
    case L3_L2_LOCAL_PROCESSOR_OUT:
    case L3_L2_LOCAL_PROCESSOR_REC:
    case L3_L2_GET_TRACE:
    case L3_L2_GET_CONFIG:
    case L3_L2_GET_STATS:
        if (sig->elem.size != MTP2_FIXED_HDR_SIZE)
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n",__LINE__,
                                                  sig->elem.size, MTP2_FIXED_HDR_SIZE);
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    case L3_L2_DATA:
        if (sig->elem.size > sizeof(MTP2_Signal))
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n", __LINE__, sig->elem.size, 
                                                  sizeof(MTP2_Signal));
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    case L3_L2_RETRIEVE_MSGS:
        if (sig->elem.size != MTP2_FIXED_HDR_SIZE + sizeof(ITS_OCTET))
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n", __LINE__, sig->elem.size,
                                                   MTP2_FIXED_HDR_SIZE+1);
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    case L3_L2_SET_TRACE:
        if (sig->elem.size != MTP2_FIXED_HDR_SIZE + sizeof(MTP2_TraceData))
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n", __LINE__, sig->elem.size, 
                   MTP2_FIXED_HDR_SIZE+sizeof(MTP2_TraceData));
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    case L3_L2_SET_CONFIG:
        if (sig->elem.size != MTP2_FIXED_HDR_SIZE + sizeof(MTP2_ConfigData))
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n", __LINE__, sig->elem.size, 
                   MTP2_FIXED_HDR_SIZE+sizeof(MTP2_ConfigData));
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    case L3_L2_RESET_STATS:
        if (sig->elem.size != MTP2_FIXED_HDR_SIZE + sizeof(MTP2_StatsData))
        {
            printk("L3_Buffer:%d sz=%d FHSZ=%d\n", __LINE__, sig->elem.size, 
                   MTP2_FIXED_HDR_SIZE+sizeof(MTP2_StatsData));
            return -EPROTO;
        }
        return QueueIncoming(link, sig);

    default:
printk("invalid signal %s:%d", __FILE__, __LINE__);
        return -EINVAL;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      Act on a queued message
 *
 *  Input Parameters:
 *      link    - the link to act on
 *      entry   - the queued message to act on
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
 *
 ************************************************************************/
void
L3_Dispatch(MTP2_LinkState *link, MTP2_QEntry *data)
{
    MTP2_Signal *signal = &data->signal;
    MTP2_QEntry reply;
    MTP2_StatsData stats;
    int i;

    switch (signal->signal)
    {
    case L3_L2_START:
        LSC_Main(link, L3_LSC_TRIGGER_Start, NULL, 0);
        break;

    case L3_L2_STOP:
        LSC_Main(link, L3_LSC_TRIGGER_Stop, NULL, 0);
        break;

    case L3_L2_RESUME:
        LSC_Main(link, L3_LSC_TRIGGER_Continue, NULL, 0);
        break;

    case L3_L2_CLEAR_BUFFERS:
    case L3_L2_CLEAR_RTB:
        LSC_Main(link, L3_LSC_TRIGGER_FlushBuffers, NULL, 0);
        break;

    case L3_L2_EMERGENCY:
        LSC_Main(link, L3_LSC_TRIGGER_Emergency, NULL, 0);
        break;

    case L3_L2_EMERGENCY_CEASE:
        LSC_Main(link, L3_LSC_TRIGGER_EmergencyEnd, NULL, 0);
        break;

    case L3_L2_DATA:
        TXC_Main(link, L3_TXC_TRIGGER_MessageForTransmission,
                 (ITS_OCTET *)signal, data->elem.size);
        break;

    case L3_L2_RETRIEVE_BSNT:
        LSC_Main(link, L3_LSC_TRIGGER_RetrieveBSNT, NULL, 0);
        break;

    case L3_L2_RETRIEVE_MSGS:
        LSC_Main(link, L3_LSC_TRIGGER_RetrievalFSNC,
                 &signal->data.bsnt, sizeof(ITS_OCTET));
        break;

    case L3_L2_FLOW_CONTROL_START:
        break;

    case L3_L2_FLOW_CONTROL_STOP:
        break;

    case L3_L2_LOCAL_PROCESSOR_OUT:
        LSC_Main(link, MGMT_LSC_TRIGGER_LocalProcessorOutage, NULL, 0);
        break;

    case L3_L2_LOCAL_PROCESSOR_REC:
        LSC_Main(link, MGMT_LSC_TRIGGER_LocalProcessorRecovered, NULL, 0);
        LSC_Main(link, L3_LSC_TRIGGER_LocalProcessorRecovered, NULL, 0);
        break;

    case L3_L2_GET_TRACE:
        reply.elem.size = sizeof(MTP2_TraceData) + MTP2_FIXED_HDR_SIZE;
        reply.signal.signal = L2_L3_CURRENT_TRACE;
        memcpy(&reply.signal.data.traceData, &link->traceData,
               sizeof(MTP2_TraceData));
        arrayq_put(&link->rq, link->rqData, &reply.elem);
        break;

    case L3_L2_SET_TRACE:
        memcpy(&link->traceData, &signal->data.traceData,
               sizeof(MTP2_TraceData));
        break;

    case L3_L2_GET_CONFIG:
        reply.elem.size = sizeof(MTP2_ConfigData) + MTP2_FIXED_HDR_SIZE;
        reply.signal.signal = L2_L3_CURRENT_CONFIG;
        memcpy(&reply.signal.data.sif, &link->configData,
               sizeof(MTP2_ConfigData));
        arrayq_put(&link->rq, link->rqData, &reply.elem);
        break;

    case L3_L2_SET_CONFIG:
        /* Add sanity check */
        memcpy(&link->configData, signal->data.sif,
               sizeof(MTP2_ConfigData));
        break;

    case L3_L2_GET_STATS:
        reply.elem.size = sizeof(MTP2_StatsData) + MTP2_FIXED_HDR_SIZE;
        reply.signal.signal = L2_L3_CURRENT_STATS;
        memcpy(&reply.signal.data.sif, &link->statsData,
               sizeof(MTP2_StatsData));
        arrayq_put(&link->rq, link->rqData, &reply.elem);
        break;

    case L3_L2_RESET_STATS:
        memcpy(&stats, signal->data.sif, sizeof(MTP2_StatsData));
        for (i = 0; i < MTP2_MAX_STATS; i++)
        {
          
            link->statsData.peg[i] -= stats.peg[i];
            /* Check underflow in case of wraparound */
            if (link->statsData.peg[i] < 0)
            {
                link->statsData.peg[i] = 0;
            }
        }
        break;

    case MTP2_T1:
        LSC_Main(link, TIMER_TRIGGER_T1Expired, NULL, 0);
        break;

    case MTP2_T2:
        IAC_Main(link, TIMER_TRIGGER_T2Expired, NULL, 0);
        break;

    case MTP2_T3:
        IAC_Main(link, TIMER_TRIGGER_T3Expired, NULL, 0);
        break;

    case MTP2_T4:
        IAC_Main(link, TIMER_TRIGGER_T4Expired, NULL, 0);
        break;

    case MTP2_T5:
        CC_Main(link, TIMER_TRIGGER_T5Expired, NULL, 0);
        break;

    case MTP2_T6:
        TXC_Main(link, TIMER_TRIGGER_T6Expired, NULL, 0);
        break;

    case MTP2_T7:
        TXC_Main(link, TIMER_TRIGGER_T7Expired, NULL, 0);
        break;

    case MTP2_QUEUED_TRIG:
        switch (data->signal.linkSet)
        {
        case MGMT_LSC_TRIGGER_PowerOn:
            LSC_Main(link, MGMT_LSC_TRIGGER_PowerOn, NULL, 0);
            break;

        case MGMT_LSC_TRIGGER_L3_Failure:
            LSC_Main(link, MGMT_LSC_TRIGGER_L3_Failure, NULL, 0);
            break;

        case L1_DAEDR_TRIGGER_SignalUnit:
            /*
             * Needless to say, a special case.  We need to adjust to what
             * the interrupt gave us.  In this case, when we get somethnig
             * from L1, the full MTP2 header is going to be in it.  This
             * leads to a different assumption of how the signal looks as
             * compared to when we buffer (MTP2 header starts at signal
             * there).
             */
            DAEDR_Main(link, L1_DAEDR_TRIGGER_SignalUnit,
                       data->signal.data.sif,
                       data->elem.size - MTP2_FIXED_HDR_SIZE);
            break;

        case L1_DAEDR_TRIGGER_OctetCountingMode:
            DAEDR_Main(link, L1_DAEDR_TRIGGER_OctetCountingMode, NULL, 0);
            break;

        case L1_DAEDR_TRIGGER_BadCheckSum:
            DAEDR_Main(link, L1_DAEDR_TRIGGER_BadCheckSum, NULL, 0);
            break;

        case L1_DAEDR_TRIGGER_16_Octets:
            DAEDR_Main(link, L1_DAEDR_TRIGGER_16_Octets, NULL, 0);
            break;

        case SUERM_LSC_TRIGGER_LinkFailure:
            LSC_Main(link, SUERM_LSC_TRIGGER_LinkFailure, NULL, 0);
            break;

        case AERM_IAC_TRIGGER_AbortProving:
            IAC_Main(link, AERM_IAC_TRIGGER_AbortProving, NULL, 0);
            break;

        case DAEDT_TXC_TRIGGER_TransmissionRequest:
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);
            break;

        default:
            printk("UKNOWN QUEUE TRIGGER: %s\n",
                   MTP2_TriggerToString(data->signal.linkSet));
            break;
        }
        break;

    default:
        break;
    }
}

