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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:35  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/04 12:21:00  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:38:46  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-txc.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 */

static const char *stateNames[] =
{
    "TXC_STATE_IDLE",
    "TXC_STATE_IN_SERVICE",
    "TXC_STATE_MAX_STATE"
};

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Return a string describing the current state
 *
 *  Input Parameters:
 *      state    - the current state
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
static const char *
TXC_StateName(TXC_States state)
{
    if (state < TXC_STATE_IDLE || state >= TXC_STATE_MAX_STATE)
    {
        return "(bad state)";
    }
    else
    {
        return stateNames[state];
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle L3 messages
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
static void
TXC_Handle_L3(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    MTP2_QEntry sig;

    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= L3_TRIGGER_MIN &&
               trigger <= L3_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 5 */
        case L3_TXC_TRIGGER_MessageForTransmission:
            /* Store message in TB.  Once in TB or RTB, "signal" is lost */
            sig.elem.size = size;
            sig.signal.signal = 0;
            sig.signal.linkSet = 0;
            sig.signal.linkCode = 0;
            memcpy(&sig.signal.signal, data, size);
            arrayq_put(&link->tb, link->tbData, &sig.elem);

            /*
             * Assumption: Not sure if it should be different for BASIC
             * The SDL has a place, but the box is empty.  Assume oversight.
             * I think so.  Cm is basically a count of the buffers pending
             */
            link->txcInfo.Cm = link->txcInfo.Cm + 1;

            /* Request Transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle LSC messages
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
static void
TXC_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    RetrievalFSNC *txcRetrievalFSNC = (RetrievalFSNC *)data;
    MTP2_QEntry *ent, sig;
    MTP2_HEADER *mtp2;
    BSNRAlone *bsnr = (BSNRAlone *)data;

    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        /* Sheet 1 */
        case LSC_TXC_TRIGGER_Start:
            /* Change state */
            link->txcInfo.curState = TXC_STATE_IN_SERVICE;

            /* Initialize variables */
            link->txcInfo.LSSUAvailable = ITS_FALSE;
            link->txcInfo.SIBReceived = ITS_FALSE;
            link->txcInfo.RTBFull = ITS_FALSE;
            link->txcInfo.MSUInhibited = ITS_FALSE;

            /* Initialize variables */
            link->txcInfo.FSNL = 127;
            link->txcInfo.FSNX = 0;
            link->txcInfo.FIB = 1;
            link->txcInfo.BIB = 1;
            link->txcInfo.FSNF = 0;
            link->txcInfo.Cm = 0;

            /* Check error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                /* Initialize variables */
                link->txcInfo.FSNT = 127;
            }
            else
            {
                /* PCR */
                /* Initialize variables */
                link->txcInfo.Z = 0;

                link->txcInfo.forcedRetransmission = ITS_FALSE;
            }

            DAEDT_Main(link, TXC_DAEDT_TRIGGER_Start, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case LSC_TXC_TRIGGER_SendSIOS:
            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);

            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_OS;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 2 */
        case LSC_TXC_TRIGGER_SendSIPO:
            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);

            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_PO;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 2 */
        case LSC_TXC_TRIGGER_Start:
            link->txcInfo.SIBReceived = ITS_FALSE;
            link->txcInfo.RTBFull = ITS_FALSE;
            link->txcInfo.MSUInhibited = ITS_FALSE;

            /* Initialize variables */
            link->txcInfo.FSNL = 127;
            link->txcInfo.FSNX = 0;
            link->txcInfo.FIB = 1;
            link->txcInfo.BIB = 1;
            link->txcInfo.FSNF = 0;
            link->txcInfo.Cm = 0;

            /* Check error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                /* Initialize variables */
                link->txcInfo.FSNT = 127;
            }
            else
            {
                /* PCR */
                /* Initialize variables */
                link->txcInfo.Z = 0;

                link->txcInfo.forcedRetransmission = ITS_FALSE;
            }

            /* Remain in state */
            break;

        /* Sheet 5 */
        case LSC_TXC_TRIGGER_SendFISU:
            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);

            /* Change variables */
            link->txcInfo.MSUInhibited = ITS_TRUE;
            link->txcInfo.LSSUAvailable = ITS_FALSE;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 5 */
        case LSC_TXC_TRIGGER_SendMSU:
            /* Check variables */
            /* RTB Empty? */
            if (link->txcInfo.FSNL != SNVAL(link->txcInfo.FSNF - 1))
            {
                TIMER_Main(link, TIMER_TRIGGER_StartT7, NULL, 0);
            }

            /* Change variables */
            link->txcInfo.MSUInhibited = ITS_FALSE;
            link->txcInfo.LSSUAvailable = ITS_FALSE;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 6 */
        case LSC_TXC_TRIGGER_RetrievalFSNC:
            /* INVARIANT */
            ITS_ASSERT(size == sizeof(RetrievalFSNC));

            /* Erase in RTB up to FSN == txcRetrievalFSNC->FSNC */
            if (!arrayq_empty(&link->tb))
            {
                while (1)
                {
                    if (!arrayq_peek(&link->tb, link->tbData, (void **)&ent))
                    {
                        break;
                    }

                    mtp2 = (MTP2_HEADER *)&ent->signal.signal;

                    if (MTP2_GET_FSN(*mtp2) >= txcRetrievalFSNC->FSNC)
                    {
                        break;
                    }

                    sig.elem.size = sizeof(MTP2_QEntry);
                    if (!arrayq_get(&link->tb, link->tbData, &sig.elem))
                    {
                        break;
                    }
                }
            }

            /* Change variables */
            link->txcInfo.FSNF = SNVAL(txcRetrievalFSNC->FSNC + 1);

            /* Error correction type */
            if (!link->configData.PCR)
            {
                link->txcInfo.Z = link->txcInfo.FSNF;
            }

            /* Content of RTB followd bye content of TB */
            sig.elem.size = sizeof(MTP2_QEntry);
            while (arrayq_get(&link->rtb, link->rtbData, &sig.elem))
            {
                /* Send triggers */
                sig.signal.signal = L2_L3_RETRIEVED_MSG;
                L3_Main(link, TXC_L3_TRIGGER_RetrievedMessage,
                        &sig.signal.signal, sig.elem.size);

                sig.elem.size = sizeof(MTP2_QEntry);
            }
            while (arrayq_get(&link->tb, link->tbData, &sig.elem))
            {
                /* Send triggers */
                sig.signal.signal = L2_L3_RETRIEVED_MSG;
                L3_Main(link, TXC_L3_TRIGGER_RetrievedMessage,
                        &sig.signal.signal, sig.elem.size);

                sig.elem.size = sizeof(MTP2_QEntry);
            }

            /* Change variables */
            link->txcInfo.RTBFull = ITS_FALSE;

            /* Send triggers */
            L3_Main(link, TXC_L3_TRIGGER_RetrievalComplete, NULL, 0);

            /* Change variables */
            link->txcInfo.Cm = 0;
            link->txcInfo.FSNL = txcRetrievalFSNC->FSNC;
            link->txcInfo.FSNT = link->txcInfo.FSNL;

            /* Remain in state */
            break;

        /* Sheet 7 */
        case LSC_TXC_TRIGGER_FlushBuffers:
            /* Erase all MSUs in RTB and TB */
            sig.elem.size = sizeof(MTP2_QEntry);
            while (arrayq_get(&link->rtb, link->rtbData, &sig.elem))
            {
                sig.elem.size = sizeof(MTP2_QEntry);
            }
            while (arrayq_get(&link->tb, link->tbData, &sig.elem))
            {
                sig.elem.size = sizeof(MTP2_QEntry);
            }

            /* Change variables */
            link->txcInfo.RTBFull = ITS_FALSE;
            link->txcInfo.Cm = 0;

            /* BSNR comes from first SU terminating the RPO */
            /* Error correction type */
            if (link->configData.PCR)
            {
                /* PCR */
                link->txcInfo.Z = SNVAL(bsnr->BSNR + 1);
            }

            /* Change variables */
            link->txcInfo.FSNF = SNVAL(bsnr->BSNR + 1);
            link->txcInfo.FSNL = bsnr->BSNR;
            link->txcInfo.FSNT = bsnr->BSNR;

            /* Send trigger */
            TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle IAC messages
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
static void
TXC_Handle_IAC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= IAC_TRIGGER_MIN &&
               trigger <= IAC_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case IAC_TXC_TRIGGER_SendSIO:
            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_O;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 2 */
        case IAC_TXC_TRIGGER_SendSIN:
            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_N;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 2 */
        case IAC_TXC_TRIGGER_SendSIE:
            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_E;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle DAEDT messages
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
static void
TXC_Handle_DAEDT(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    FSNTValue txcFSNTValue;
    MTP2_QEntry sig, *ent;
    MTP2_HEADER *mtp2 = (MTP2_HEADER *)&sig.signal;
    ITS_USHORT lsize;

    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= DAEDT_TRIGGER_MIN &&
               trigger <= DAEDT_TRIGGER_MAX);

    memset(mtp2, 0, sizeof(MTP2_HEADER));
    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        case DAEDT_TXC_TRIGGER_TransmissionRequest:
            /*
             * Complex algorithms.  See SDL sheets 3 & 4
             * for both basic and PCR
             */
            if (link->txcInfo.LSSUAvailable)
            {
                /* Insert stored status indication into LSSU */
                MTP2_SET_STATUS(*mtp2, link->txcInfo.statusInd);
                MTP2_SET_LI(*mtp2, 1);

                if (link->txcInfo.statusInd == MTP2_STAT_B)
                {
                    link->txcInfo.LSSUAvailable = ITS_FALSE;
                }

                /* Error correction type */
                if (!link->configData.PCR)
                {
                    /* BASIC */
                    MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                    MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, sizeof(MTP2_HEADER));
                }
                else
                {
                    /* PCR */
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, sizeof(MTP2_HEADER));
                }

                /* remain in state */
                return;
            }
            else if (link->txcInfo.MSUInhibited)
            {
                /* Generate FISU (nothing but header) */
                MTP2_SET_LI(*mtp2, 0);
 
                /* Error correction type */
                if (!link->configData.PCR)
                {
                    /* BASIC */
                    MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                    MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, MTP2_FIXED_HDR_SIZE);
                }
                else
                {
                    /* PCR */
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, MTP2_FIXED_HDR_SIZE);
                }

                /* remain in state */
                return;
            }

            /* From here the error correction types diverge more widely */
            /* Implicitly, this point is !MSUInhibited */
            if (!link->configData.PCR)
            {
                /* Sheets 3 & 4 */
                /* BASIC */
                if (link->txcInfo.FSNT != link->txcInfo.FSNL)
                {
                    /* Fetch MSU from RTB */
                    sig.elem.size = sizeof(MTP2_QEntry);
                    if (arrayq_get(&link->rtb, link->rtbData, &sig.elem))
                    {
                        link->txcInfo.FSNT = SNVAL(link->txcInfo.FSNT + 1);

                        txcFSNTValue.FSNT = link->txcInfo.FSNT;
                        RC_Main(link, TXC_RC_TRIGGER_FSNTValue,
                                (ITS_OCTET *)&txcFSNTValue, sizeof(FSNTValue));

                        lsize = sig.elem.size;
                        if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                        {
                            MTP2_SET_LI(*mtp2, 63);
                        }
                        else
                        {
                            MTP2_SET_LI(*mtp2,
                                        lsize - MTP2_FIXED_HDR_SIZE);
                        }

                        MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                        MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                        MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                        MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                        /* Send trigger */
                        DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                                   (ITS_OCTET *)mtp2, lsize);
                    }

                    /* remain in state */
                }
                else if (link->txcInfo.Cm == 0)
                {
                    /* Generate FISU */
                    MTP2_SET_LI(*mtp2, 0);

                    MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                    MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, MTP2_FIXED_HDR_SIZE);
                }
                else if (link->txcInfo.RTBFull)
                {
                    /* Generate FISU */
                    MTP2_SET_LI(*mtp2, 0);

                    MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                    MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    /* Send trigger */
                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, MTP2_FIXED_HDR_SIZE);
                }
                else
                {
                    /* Fetch MSU from TB */
                    sig.elem.size = sizeof(MTP2_QEntry);
                    if (arrayq_get(&link->tb, link->tbData, &sig.elem))
                    {
                        link->txcInfo.Cm = link->txcInfo.Cm - 1;

                        link->txcInfo.FSNL = SNVAL(link->txcInfo.FSNL + 1);
                        link->txcInfo.FSNT = link->txcInfo.FSNL;

                        /* First message in RTB? */
                        if (link->txcInfo.FSNL == link->txcInfo.FSNF)
                        {
                            TIMER_Main(link, TIMER_TRIGGER_StartT7, NULL, 0);
                        }

                        /*
                         * Store MSU in RTB. This should always succeed,
                         * given the RTBFull logic below.
                         */
                        arrayq_put(&link->rtb, link->rtbData, &sig.elem);

                        txcFSNTValue.FSNT = link->txcInfo.FSNT;
                        RC_Main(link, TXC_RC_TRIGGER_FSNTValue,
                                (ITS_OCTET *)&txcFSNTValue, sizeof(FSNTValue));

                        if (link->txcInfo.FSNL == SNVAL(link->txcInfo.FSNF - 2))
                        {
                            link->txcInfo.RTBFull = ITS_TRUE;
                        }

                        lsize = sig.elem.size;
                        if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                        {
                            MTP2_SET_LI(*mtp2, 63);
                        }
                        else
                        {
                            MTP2_SET_LI(*mtp2,
                                        lsize - MTP2_FIXED_HDR_SIZE);
                        }

                        MTP2_SET_BIB(*mtp2, link->txcInfo.BIB);
                        MTP2_SET_FIB(*mtp2, link->txcInfo.FIB);
                        MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                        MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                        /* Send trigger */
                        DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                                   (ITS_OCTET *)mtp2, lsize);
                    }
                }

                /* Remain in state */
                return;
            }
            else
            {
                /* Sheets 3 & 4 */
                /* PCR */
                if (link->txcInfo.forcedRetransmission)
                {
                    if (link->txcInfo.FSNF != SNVAL(link->txcInfo.FSNL + 1))
                    {
                        /* Fetch MSU in RTB with FSNT = Z */
                        if (arrayq_peek(&link->rtb, link->rtbData,
                                        (void **)&ent))
                        {
                            do
                            {
                                mtp2 = (MTP2_HEADER *)&ent->signal.signal;

                                if (MTP2_GET_FSN(*mtp2) == link->txcInfo.Z)
                                {
                                    link->txcInfo.FSNT = link->txcInfo.Z;

                                    lsize = ent->elem.size;
                                    if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                                    {
                                        MTP2_SET_LI(*mtp2, 63);
                                    }
                                    else
                                    {
                                        MTP2_SET_LI(*mtp2,
                                                    lsize -
                                                        MTP2_FIXED_HDR_SIZE);
                                    }
                                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                                    DAEDT_Main(link,
                                               TXC_DAEDT_TRIGGER_SignalUnit,
                                               (ITS_OCTET *)mtp2,
                                               lsize);

                                    if (link->txcInfo.FSNL == link->txcInfo.Z)
                                    {
                                        link->txcInfo.forcedRetransmission =
                                            ITS_FALSE;
                                    }
                                    else
                                    {
                                        link->txcInfo.Z = link->txcInfo.Z + 1;
                                    }

                                    break; /* out of loop */
                                }
                            }
                            while (arrayq_peek_next(&link->rtb, link->rtbData,
                                                    (void **)&ent));
                        }

                        /* Note the bailout */
                        /* Remain in state */
                        return;
                    }
                    else
                    {
                        link->txcInfo.forcedRetransmission = ITS_FALSE;
                        link->txcInfo.RTBFull = ITS_FALSE;

                        /* Note the lack of a return here */
                        /* FALL THROUGH */
                    }
                }

                /* Not forced retransmission */
                if (link->txcInfo.Cm == 0)
                {
                    if (link->txcInfo.FSNF != SNVAL(link->txcInfo.FSNL + 1))
                    {
                        /* Fetch MSU in RTB with FSNT = Z */
                        if (arrayq_peek(&link->rtb, link->rtbData,
                                        (void **)&ent))
                        {
                            do
                            {
                                link->txcInfo.FSNT = link->txcInfo.Z;

                                lsize = ent->elem.size;
                                if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                                {
                                    MTP2_SET_LI(*mtp2, 63);
                                }
                                else
                                {
                                    MTP2_SET_LI(*mtp2,
                                                lsize -
                                                    MTP2_FIXED_HDR_SIZE);
                                }
                                MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                                MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                                DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                                           (ITS_OCTET *)mtp2, lsize);
                            }
                            while (arrayq_peek_next(&link->rtb, link->rtbData,
                                                    (void **)&ent));
                        }

                        if (link->txcInfo.FSNL == link->txcInfo.Z)
                        {
                            link->txcInfo.forcedRetransmission = ITS_FALSE;
                        }
                        else
                        {
                            link->txcInfo.Z = link->txcInfo.Z + 1;
                        }
                    }
                    else
                    {
                        /* Generate FISU */
                        MTP2_SET_LI(*mtp2, 0);

                        link->txcInfo.FSNT = link->txcInfo.FSNL;

                        MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                        MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                        DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                                   (ITS_OCTET *)mtp2, MTP2_FIXED_HDR_SIZE);
                    }

                    /* Note the bailout */
                    /* Remain in state */
                    return;
                }

                /* Cm != 0 */
                if (link->txcInfo.RTBFull)
                {
                    link->txcInfo.forcedRetransmission = ITS_TRUE;

                    /* Fetch MSU in RTB with FSNT = Z */
                    if (arrayq_peek(&link->rtb, link->rtbData, (void **)&ent))
                    {
                        do
                        {
                            link->txcInfo.FSNT = link->txcInfo.Z;

                            lsize = ent->elem.size;
                            if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                            {
                                MTP2_SET_LI(*mtp2, 63);
                            }
                            else
                            {
                                MTP2_SET_LI(*mtp2,
                                            lsize - MTP2_FIXED_HDR_SIZE);
                            }
                            MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                            MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                            DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                                       (ITS_OCTET *)mtp2, lsize);
                        }
                        while (arrayq_peek_next(&link->rtb, link->rtbData,
                                                (void **)&ent));
                    }

                    if (link->txcInfo.FSNL == link->txcInfo.Z)
                    {
                        link->txcInfo.forcedRetransmission = ITS_FALSE;
                    }
                    else
                    {
                        link->txcInfo.Z = link->txcInfo.Z + 1;
                    }

                    /* Note the bailout */
                    /* Remain in state */
                    return;
                }

                /* !RTBFull */
                /* Fetch MSU from TB */
                sig.elem.size = sizeof(MTP2_QEntry);
                if (arrayq_get(&link->tb, link->tbData, &sig.elem))
                {
                    link->txcInfo.Cm = link->txcInfo.Cm - 1;
                    link->txcInfo.FSNL = SNVAL(link->txcInfo.FSNL + 1);
                    link->txcInfo.FSNT = link->txcInfo.FSNL;

                    /* Store MSU in RTB */
                    arrayq_put(&link->rtb, link->rtbData, &sig.elem);

                    /* First message in RTB? */
                    if (link->txcInfo.FSNL == link->txcInfo.FSNF)
                    {
                        TIMER_Main(link, TIMER_TRIGGER_StartT7, NULL, 0);
                    }

                    /* Update octet count */
                    link->txcInfo.octetCount += sig.elem.size;

                    txcFSNTValue.FSNT = link->txcInfo.FSNT;
                    RC_Main(link, TXC_RC_TRIGGER_FSNTValue,
                            (ITS_OCTET *)&txcFSNTValue, sizeof(FSNTValue));

                    if ((link->txcInfo.FSNL ==
                         SNVAL(link->txcInfo.FSNF + link->txcInfo.N1 - 1)) ||
                        (link->txcInfo.octetCount > link->txcInfo.N2))
                    {
                        link->txcInfo.RTBFull = ITS_TRUE;
                        link->txcInfo.forcedRetransmission = ITS_TRUE;
                    }

                    lsize = sig.elem.size;
                    if ((lsize - MTP2_FIXED_HDR_SIZE) >= 63)
                    {
                        MTP2_SET_LI(*mtp2, 63);
                    }
                    else
                    {
                        MTP2_SET_LI(*mtp2,
                                    lsize - MTP2_FIXED_HDR_SIZE);
                    }
                    MTP2_SET_BSN(*mtp2, SNVAL(link->txcInfo.FSNX - 1));
                    MTP2_SET_FSN(*mtp2, link->txcInfo.FSNT);

                    DAEDT_Main(link, TXC_DAEDT_TRIGGER_SignalUnit,
                               (ITS_OCTET *)mtp2, lsize);
                }
            }
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle RC messages
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
static void
TXC_Handle_RC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    BSNRAndBIBR *txcBSNR = (BSNRAndBIBR *)data;
    FSNXValue *txcFSNX = (FSNXValue *)data;
    MTP2_QEntry *ent, sig;
    MTP2_HEADER *mtp2;

    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= RC_TRIGGER_MIN &&
               trigger <= RC_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 5 */
        case RC_TXC_TRIGGER_NACKToBeSent:
            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                /* Change variables */
                link->txcInfo.BIB = !link->txcInfo.BIB;
            }

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 5 */
        case RC_TXC_TRIGGER_SIBReceived:
            /* Check variables */
            if (!link->txcInfo.SIBReceived)
            {
                /* Send triggers */
                TIMER_Main(link, TIMER_TRIGGER_StartT6, NULL, 0);

                /* Change variables */
                link->txcInfo.SIBReceived = ITS_TRUE;
            }

            /* Remain in state */
            break;

        /* Sheet 6 */
        case RC_TXC_TRIGGER_BSNRAndBIBR:
            /* INVARIANT */
            ITS_ASSERT(size == sizeof(BSNRAndBIBR));

            /* Complex algorithms.  Consult SDL sheet 6 */
            if (link->txcInfo.FSNF != SNVAL(txcBSNR->BSNR + 1))
            {
                if (link->txcInfo.SIBReceived)
                {
                    link->txcInfo.SIBReceived = ITS_FALSE;

                    TIMER_Main(link, TIMER_TRIGGER_StopT6, NULL, 0);
                }

                /* Erase in RTB MSUs up to FSN = BSNR */
                while (1)
                {
                    if (!arrayq_peek(&link->rtb, link->rtbData, (void **)&ent))
                    {
                        break;
                    }

                    mtp2 = (MTP2_HEADER *)&ent->signal.signal;

                    if (MTP2_GET_FSN(*mtp2) >= txcBSNR->BSNR)
                    {
                        break;
                    }

                    sig.elem.size = sizeof(MTP2_QEntry);
                    if (!arrayq_get(&link->rtb, link->rtbData, &sig.elem))
                    {
                        break;
                    }
                }

                link->txcInfo.FSNF = SNVAL(txcBSNR->BSNR + 1);

                /* RTB Empty? */
                if (link->txcInfo.FSNL == SNVAL(link->txcInfo.FSNF - 1))
                {
                    TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);
                }
                else
                {
                    TIMER_Main(link, TIMER_TRIGGER_StartT7, NULL, 0);
                }

                /* Error correction check */
                if (!link->configData.PCR)
                {
                    /* BASIC */
                    link->txcInfo.RTBFull = ITS_FALSE;
                }
                else
                {
                    if (link->txcInfo.octetCount <= link->txcInfo.N2)
                    {
                        link->txcInfo.RTBFull = ITS_FALSE;
                    }
                }
            }

            /* FSNF == BSNR + 1 */
            /* Error correction check */
            if (!link->configData.PCR)
            {
                /* BASIC */
                if (link->txcInfo.FIB == txcBSNR->BIBR)
                {
                    return;
                }

                if (link->txcInfo.SIBReceived)
                {
                    link->txcInfo.SIBReceived = ITS_FALSE;

                    TIMER_Main(link, TIMER_TRIGGER_StopT6, NULL, 0);
                }

                link->txcInfo.FIB = txcBSNR->BIBR;
                link->txcInfo.FSNT = SNVAL(link->txcInfo.FSNF - 1);
            }
            else
            {
                /* PCR */
                if (link->txcInfo.Z <= link->txcInfo.FSNF ||
                    link->txcInfo.Z >= link->txcInfo.FSNL)
                {
                    link->txcInfo.Z = link->txcInfo.FSNF;
                }
            }

            /* Remain in state */
            break;

        case RC_TXC_TRIGGER_FSNXValue:
            /* INVARIANT */
            ITS_ASSERT(size == sizeof(FSNXValue));

            /* Change variable */
            link->txcInfo.FSNX = txcFSNX->FSNX;

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle CC messages
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
static void
TXC_Handle_CC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= CC_TRIGGER_MIN &&
               trigger <= CC_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case CC_TXC_TRIGGER_SendSIB:
            /* Change variables */
            link->txcInfo.LSSUAvailable = ITS_TRUE;
            link->txcInfo.statusInd = MTP2_STAT_B;

            /* Request transmission */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:static
 ************************************************************************
 *  Purpose:
 *      Handle TIMER messages
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
static void
TXC_Handle_TIMER(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->txcInfo.curState >= TXC_STATE_IDLE &&
               link->txcInfo.curState < TXC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TIMER_TRIGGER_MIN &&
               trigger <= TIMER_TRIGGER_MAX);

    switch (link->txcInfo.curState)
    {
    case TXC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case TXC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case TIMER_TRIGGER_T6Expired:
            /* Send triggers */
            LSC_Main(link, TXC_LSC_TRIGGER_LinkFailure, NULL, 0);

            /* Change variables */
            link->txcInfo.SIBReceived = ITS_FALSE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT7, NULL, 0);

            /* remain in state */
            break;

        /* Sheet 5 */
        case TIMER_TRIGGER_T7Expired:
            /* Send triggers */
            LSC_Main(link, TXC_LSC_TRIGGER_LinkFailure, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StopT6, NULL, 0);

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                link->txcInfo.SIBReceived = ITS_FALSE;
            }

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IN_SERVICE\n",
                        trigger);
            break;
        }
        break;

    default:
        /* Should be impossible except via corruption */
        ITS_ASSERT(ITS_FALSE);
        break;
    }
}

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      TXC entry point
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
TXC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
         ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("TXC_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           TXC_StateName(link->txcInfo.curState));
#endif
    switch (trigger)
    {
    case L3_TXC_TRIGGER_MessageForTransmission:
        TXC_Handle_L3(link, trigger, data, size);
        break;

    case LSC_TXC_TRIGGER_Start:
    case LSC_TXC_TRIGGER_RetrievalFSNC:
    case LSC_TXC_TRIGGER_SendSIOS:
    case LSC_TXC_TRIGGER_SendFISU:
    case LSC_TXC_TRIGGER_SendSIPO:
    case LSC_TXC_TRIGGER_SendMSU:
    case LSC_TXC_TRIGGER_FlushBuffers:
        TXC_Handle_LSC(link, trigger, data, size);
        break;

    case IAC_TXC_TRIGGER_SendSIO:
    case IAC_TXC_TRIGGER_SendSIN:
    case IAC_TXC_TRIGGER_SendSIE:
        TXC_Handle_IAC(link, trigger, data, size);
        break;

    case DAEDT_TXC_TRIGGER_TransmissionRequest:
        TXC_Handle_DAEDT(link, trigger, data, size);
        break;

    case RC_TXC_TRIGGER_NACKToBeSent:
    case RC_TXC_TRIGGER_SIBReceived:
    case RC_TXC_TRIGGER_BSNRAndBIBR:
    case RC_TXC_TRIGGER_FSNXValue:
        TXC_Handle_RC(link, trigger, data, size);
        break;

    case CC_TXC_TRIGGER_SendSIB:
        TXC_Handle_CC(link, trigger, data, size);
        break;

    case TIMER_TRIGGER_T6Expired:
    case TIMER_TRIGGER_T7Expired:
        TXC_Handle_TIMER(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for IAC\n",
                    trigger);
        break;
    }
}
