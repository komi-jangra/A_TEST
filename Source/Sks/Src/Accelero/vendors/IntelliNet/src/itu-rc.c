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
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:09  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.4  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/04 12:17:25  gdevanand
 * LOG: Combined driver for MTP and LAPD (Badri)
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:37:55  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-rc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include "../include/mtp2_intern.h"

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 */

static const char *stateNames[] =
{
    "RC_STATE_IDLE",
    "RC_STATE_IN_SERVICE",
    "RC_STATE_MAX_STATE"
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
RC_StateName(RC_States state)
{
    if (state < RC_STATE_IDLE || state >= RC_STATE_MAX_STATE)
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
 *      Handle MGMT messages
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
RC_Handle_MGMT(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    FSNXValue rcFSNXValue;

    ITS_ASSERT(link->rcInfo.curState >= RC_STATE_IDLE &&
               link->rcInfo.curState < RC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= MGMT_TRIGGER_MIN &&
               trigger <= MGMT_TRIGGER_MAX);

    switch (link->rcInfo.curState)
    {
    case RC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case RC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 6 (basic), 5 (PCR) */
        case MGMT_RC_TRIGGER_CongestionAccept:
            /* Change variables */
            link->rcInfo.congestionAccept = ITS_TRUE;

            /* Remain in state */
            break;

        /* Sheet 6 (basic), 5 (PCR) */
        case MGMT_RC_TRIGGER_CongestionDiscard:
            /* Change variables */
            link->rcInfo.congestionDiscard = ITS_TRUE;

            /* Remain in state */
            break;

        /* Sheet 6 (basic), 5 (PCR) */
        case MGMT_RC_TRIGGER_NoCongestion:
            /* Change variables */
            link->rcInfo.congestionAccept = ITS_FALSE;
            link->rcInfo.congestionDiscard = ITS_FALSE;

            /* Send triggers */
            CC_Main(link, RC_CC_TRIGGER_Normal, NULL, 0);

            rcFSNXValue.FSNX = link->rcInfo.FSNX;
            TXC_Main(link, RC_TXC_TRIGGER_FSNXValue,
                     (ITS_OCTET *)&rcFSNXValue, sizeof(FSNXValue));

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                if (link->rcInfo.RTR)
                {
                    TXC_Main(link, RC_TXC_TRIGGER_NACKToBeSent, NULL, 0);

                    link->rcInfo.FIBX = !link->rcInfo.FIBX;
                }
            }

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
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
RC_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    FSNXValue rcFSNXValue;
    RetrieveBSNT rcRetrieveBSNT;

    ITS_ASSERT(link->rcInfo.curState >= RC_STATE_IDLE &&
               link->rcInfo.curState < RC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->rcInfo.curState)
    {
    case RC_STATE_IDLE:
        switch (trigger)
        {
        /* Sheet 1 */
        case LSC_RC_TRIGGER_Start:
            /* Change state */
            link->rcInfo.curState = RC_STATE_IN_SERVICE;

            /* Send triggers */
            DAEDR_Main(link, RC_DAEDR_TRIGGER_Start, NULL, 0);

            /* Initialize variables */
            link->rcInfo.FSNX = 0;
            link->rcInfo.FIBX = 1;
            link->rcInfo.FSNF = 0;
            link->rcInfo.FSNT = 127;

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                link->rcInfo.RTR = 0;
            }

            link->rcInfo.FISUOrMSUAccepted = ITS_FALSE;
            link->rcInfo.abnormalBSNR = ITS_FALSE;

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                link->rcInfo.abnormalFIBR = ITS_FALSE;
            }

            link->rcInfo.congestionDiscard = ITS_FALSE;
            link->rcInfo.congestionAccept = ITS_FALSE;
            break;

        /* Sheet 1 */
        case LSC_RC_TRIGGER_RetrieveBSNT:
            /* Change variables */
            rcRetrieveBSNT.BSNT = SNVAL(link->rcInfo.FSNX - 1);

            /* Send triggers */
            L3_Main(link, RC_L3_TRIGGER_BSNT,
                    (ITS_OCTET *)&rcRetrieveBSNT, sizeof(RetrieveBSNT));
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case RC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case LSC_RC_TRIGGER_Stop:
            /* Change state */
            link->rcInfo.curState = RC_STATE_IDLE;

            /* Send triggers */
            CC_Main(link, RC_CC_TRIGGER_Normal, NULL, 0);
            break;

        /* Sheet 2 */
        case LSC_RC_TRIGGER_RejectMSUOrFISU:
            /* Change variables */
            link->rcInfo.FISUOrMSUAccepted = ITS_FALSE;

            /* Remain in state */
            break;

        /* Sheet 2 */
        case LSC_RC_TRIGGER_AcceptMSUOrFISU:
            /* change variables */
            link->rcInfo.FISUOrMSUAccepted = ITS_TRUE;

            /* Remain in state */
            break;

        /* Sheet 6 (basic), 5 (PCR) */
        case LSC_RC_TRIGGER_RetrieveBSNT:
            rcRetrieveBSNT.BSNT = SNVAL(link->rcInfo.FSNX - 1);

            /* Send triggers */
            L3_Main(link, RC_L3_TRIGGER_BSNT,
                    (ITS_OCTET *)&rcRetrieveBSNT, sizeof(RetrieveBSNT));

            /* Remain in state */
            break;

        /* Sheet 7 (basic), 6 (PCR) */
        case LSC_RC_TRIGGER_RetrieveFSNX:
            /* Send triggers */
            rcFSNXValue.FSNX = link->rcInfo.FSNX;
            TXC_Main(link, RC_TXC_TRIGGER_FSNXValue,
                     (ITS_OCTET *)&rcFSNXValue, sizeof(FSNXValue));

            /* Update variables */
            link->rcInfo.congestionAccept = ITS_FALSE;
            link->rcInfo.congestionDiscard = ITS_FALSE;

            /* Send triggers */
            CC_Main(link, RC_CC_TRIGGER_Normal, NULL, 0);

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                link->rcInfo.RTR = 0;
            }

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
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
 *      Handle DAEDR messages
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
RC_Handle_DAEDR(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    BSNRAndBIBR rcBSNRAndBIBR;
    FSNXValue rcFSNXValue;
    MTP2_HEADER *hdr = (MTP2_HEADER *)data;

    ITS_ASSERT(link->rcInfo.curState >= RC_STATE_IDLE &&
               link->rcInfo.curState < RC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= DAEDR_TRIGGER_MIN &&
               trigger <= DAEDR_TRIGGER_MAX);

    switch (link->rcInfo.curState)
    {
    case RC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case RC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheets 3,4,5 (basic), 3,4 (PCR) */
        case DAEDR_RC_TRIGGER_SignalUnit:
            ITS_ASSERT(hdr != (void *)0);
            ITS_ASSERT(size >= sizeof(MTP2_HEADER) - 1);

            /* Check variables */
            if (MTP2_MSG_TYPE(*hdr) == MTP2_MSG_LSSU)
            {
                switch (MTP2_GET_STATUS(*hdr))
                {
                case MTP2_STAT_N:
                    /* Send trigger */
                    LSC_Main(link, RC_LSC_TRIGGER_ReceiveSIN, NULL, 0);
                    IAC_Main(link, RC_IAC_TRIGGER_ReceiveSIN, NULL, 0);
                    break;

                case MTP2_STAT_E:
                    /* Send trigger */
                    LSC_Main(link, RC_LSC_TRIGGER_ReceiveSIE, NULL, 0);
                    IAC_Main(link, RC_IAC_TRIGGER_ReceiveSIE, NULL, 0);
                    break;

                case MTP2_STAT_O:
                    /* Send trigger */
                    LSC_Main(link, RC_LSC_TRIGGER_ReceiveSIO, NULL, 0);
                    IAC_Main(link, RC_IAC_TRIGGER_ReceiveSIO, NULL, 0);
                    break;

                case MTP2_STAT_OS:
                    /* Send trigger */
                    LSC_Main(link, RC_LSC_TRIGGER_ReceiveSIOS, NULL, 0);
                    IAC_Main(link, RC_IAC_TRIGGER_ReceiveSIOS, NULL, 0);
                    break;

                case MTP2_STAT_PO:
                    /* Send trigger */
                    LSC_Main(link, RC_LSC_TRIGGER_ReceiveSIPO, NULL, 0);
                    break;

                case MTP2_STAT_B:
                    /* Send trigger */
                    TXC_Main(link, RC_TXC_TRIGGER_SIBReceived, NULL, 0);
                    break;

                default:
                    /* Should be impossible */
                    MTP2_DEBUG(link,
                               "Invalid LSSU status %d\n",
                                MTP2_GET_STATUS(*hdr));
                    break;
                }

                /* remain in state */
                return;
            }
#if 1
printk("Got an !LSSU when in service: fsnf %02x fsnf - 1 %02x bsn %02x fsnt %02x\n",
       link->rcInfo.FSNF, (int)(link->rcInfo.FSNF - 1),
       MTP2_GET_BSN(*hdr), link->rcInfo.FSNT);
#endif

            /* !LSSU */
            /* Is the BSNR not in RTB or not the same as previous BSNR? */
            if (((int)(link->rcInfo.FSNF - 1) > (int)MTP2_GET_BSN(*hdr)) ||
                (MTP2_GET_BSN(*hdr) > link->rcInfo.FSNT))
            {
                /* Discard Signal Unit */
                if (link->rcInfo.abnormalBSNR)
                {
                    /* Change state */
                    link->rcInfo.curState = RC_STATE_IDLE;
printk("abnormalBSNR %s:%d\n", __FILE__, __LINE__);
                    /* Send triggers */
                    LSC_Main(link, RC_LSC_TRIGGER_LinkFailure, NULL, 0);
                    return;
                }

                /* Normal BSNR */
                link->rcInfo.abnormalBSNR = ITS_TRUE;
                link->rcInfo.UNB = 0;

                /* remain in state */
                return;
            }

            /* The BSNR is in the RTB or the same as the previous BSNR. */
            if (link->rcInfo.abnormalBSNR)
            {
printk("abnormal BSNR.\n");
                if (link->rcInfo.UNB != 1)
                {
                    link->rcInfo.UNB = 1;

                    /* Discard Signal Unit */

                    /* Remain in state */
                    return;
                }

                /* Normal BSNR */
                link->rcInfo.abnormalBSNR = ITS_FALSE;

                /* FALL THROUGH */
            }

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                if (MTP2_GET_FIB(*hdr) != link->rcInfo.FIBX)
                {
                    /* Discard Signal Unit */

                    if (link->rcInfo.abnormalFIBR)
                    {
                        /* Change state */
                        link->rcInfo.curState = RC_STATE_IDLE;
printk("abnormalFIBR. %s:%d FIB=%x FIBX=%x \n", __FILE__, __LINE__, MTP2_GET_FIB(*hdr),link->rcInfo.FIBX);
                        /* Send trigger */
                        LSC_Main(link, RC_LSC_TRIGGER_LinkFailure, NULL, 0);

                        /* Remain in state */
                        return;
                    }

                    /* Normal FIBR */
                    if (link->rcInfo.RTR == 1)
                    {
                        /* Send trigger */
                        /* BSNR and BIBR come from Signal Unit */
                        rcBSNRAndBIBR.BIBR = MTP2_GET_BIB(*hdr);
                        rcBSNRAndBIBR.BSNR = MTP2_GET_BSN(*hdr);
                        TXC_Main(link, RC_TXC_TRIGGER_BSNRAndBIBR,
                                 (ITS_OCTET *)&rcBSNRAndBIBR,
                                 sizeof(BSNRAndBIBR));

                        /* Change variables */
                        link->rcInfo.FSNF = SNVAL(MTP2_GET_BSN(*hdr) + 1);
                    }
                    else
                    {
                        /* Change variables */
                        link->rcInfo.abnormalFIBR = ITS_TRUE;
                        link->rcInfo.UNF = 0;
                    }

                    /* Remain in state */
                    return;
                }
                /* else FALL THROUGH */

                /* FIBR = FIBX */
                if (link->rcInfo.abnormalFIBR)
                {
                    if (link->rcInfo.UNF != 1)
                    {
                        link->rcInfo.UNF = 1;

                        /* Discard Signal Unit */

                        /* Remain in state */
                        return;
                    }
                    else
                    {
                        link->rcInfo.abnormalFIBR = ITS_FALSE;
                    }
                    /* else FALL THROUGH */
                }
                /* else FALL THROUGH */
            }
            /* else FALL THROUGH */

            /*
             * Note in the error correction specific code above,
             * there are carefully crafted non-returns that can
             * get us to this point.  This matches the SDLs.
             */

            /* Send triggers */
            LSC_Main(link, RC_LSC_TRIGGER_ReceiveMSUOrFISU, NULL, 0);
            /* BSNR and BIBR come from Signal Unit */
            rcBSNRAndBIBR.BIBR = MTP2_GET_BIB(*hdr);
            rcBSNRAndBIBR.BSNR = MTP2_GET_BSN(*hdr);
            TXC_Main(link, RC_TXC_TRIGGER_BSNRAndBIBR,
                     (ITS_OCTET *)&rcBSNRAndBIBR, sizeof(BSNRAndBIBR));

            /* Change variables */
            link->rcInfo.FSNF = SNVAL(MTP2_GET_BSN(*hdr) + 1);

            /* Check variables */
            if (!link->rcInfo.FISUOrMSUAccepted)
            {
                /* Discard Signal Unit */

                /* Remain in state */
                return;
            }

            /* Check variables */
            if (link->rcInfo.congestionDiscard)
            {
                /* Error correction type */
                if (!link->configData.PCR)
                {
                    /* BASIC */
                    if (MTP2_MSG_TYPE(*hdr) == MTP2_MSG_MSU)
                    {
                        link->rcInfo.RTR = 1;
                    }
                } /* Discard Signal Unit */

                /* Send triggers */
                CC_Main(link, RC_CC_TRIGGER_Busy, NULL, 0);

                /* Remain in state */
                return;
            }

            /* Error correction type */
            if (!link->configData.PCR)
            {
                /* BASIC */
                if (MTP2_GET_FSN(*hdr) == link->rcInfo.FSNX)
                {
                    if (MTP2_MSG_TYPE(*hdr) == MTP2_MSG_MSU)
                    {
                        /* Send triggers */
                        L3_Main(link, RC_L3_TRIGGER_ReceivedMessage, data, size);

                        /* Change variables */
                        link->rcInfo.FSNX = SNVAL(link->rcInfo.FSNX + 1);
                        link->rcInfo.RTR = 0;

                        /* Check variables */
                        if (link->rcInfo.congestionAccept)
                        {
                            /* Send triggers */
                            CC_Main(link, RC_CC_TRIGGER_Busy, NULL, 0);
                        }
                        else
                        {
                            /* Send triggers */
                            rcFSNXValue.FSNX = link->rcInfo.FSNX;
                            TXC_Main(link, RC_TXC_TRIGGER_FSNXValue,
                                     (ITS_OCTET *)&rcFSNXValue,
                                     sizeof(FSNXValue));
                        }
                    }
                    /* Signal Unit is not MSU */
                    else
                    {
                        /* Check variables */
                        if (link->rcInfo.congestionAccept)
                        {
                            /* Send triggers */
                            CC_Main(link, RC_CC_TRIGGER_Busy, NULL, 0);

                            /* Discard Signal Unit */
                        }
                        else
                        {
                            /* Send triggers */
                            TXC_Main(link, RC_TXC_TRIGGER_NACKToBeSent, NULL, 0);

                            /* Change variables */
                            link->rcInfo.RTR = 1;
                            link->rcInfo.FIBX = !link->rcInfo.FIBX;

                            /* Discard Signal Unit */
                        }
                    }
                }
                /* else FSNR != FSNX */
                else if (MTP2_GET_FSN(*hdr) != SNVAL(link->rcInfo.FSNX - 1))
                {
                    /* Check variables */
                    if (link->rcInfo.congestionAccept)
                    {
                        /* Send triggers */
                        CC_Main(link, RC_CC_TRIGGER_Busy, NULL, 0);

                        /* Discard Signal Unit */
                    }
                    else
                    {
                        /* Send triggers */
                        TXC_Main(link, RC_TXC_TRIGGER_NACKToBeSent, NULL, 0);

                        /* Change variables */
                        link->rcInfo.RTR = 1;
                        link->rcInfo.FIBX = !link->rcInfo.FIBX;

                        /* Discard Signal Unit */
                    }
                }
                else
                {
                    /* Discard Signal Unit */
                }
            }
            else
            {
                /* PCR */
                if (MTP2_GET_FSN(*hdr) == link->rcInfo.FSNX)
                {
                    if (MTP2_MSG_TYPE(*hdr) == MTP2_MSG_MSU)
                    {
                        /* Send triggers */
                        L3_Main(link, RC_L3_TRIGGER_ReceivedMessage, data, size);

                        /* Change variables */
                        link->rcInfo.FSNX = SNVAL(link->rcInfo.FSNX + 1);

                        /* Check variables */
                        if (link->rcInfo.congestionAccept)
                        {
                            /* Send triggers */
                            CC_Main(link, RC_CC_TRIGGER_Busy, NULL, 0);
                        }
                        else
                        {
                            /* Send triggers */
                            rcFSNXValue.FSNX = link->rcInfo.FSNX;
                            TXC_Main(link, RC_TXC_TRIGGER_FSNXValue,
                                     (ITS_OCTET *)&rcFSNXValue,
                                     sizeof(FSNXValue));
                        }
                    }
                    /* Signal Unit is not MSU */
                    else
                    {
                        /* Discard Signal Unit */
                    }
                }
                /* FSNR != FSNX */
                {
                    /* Discard Signal Unit */
                }
            }

            /* Remain in state */
            break;
                     
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
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
 *      Handle TXC messages
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
RC_Handle_TXC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    FSNTValue *rcFSNTValue = (FSNTValue *)data;

    ITS_ASSERT(link->rcInfo.curState >= RC_STATE_IDLE &&
               link->rcInfo.curState < RC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TXC_TRIGGER_MIN &&
               trigger <= TXC_TRIGGER_MAX);

    switch (link->rcInfo.curState)
    {
    case RC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case RC_STATE_IN_SERVICE:
        switch (trigger)
        {
        case TXC_RC_TRIGGER_FSNTValue:
            /* INVARIANT */
            ITS_ASSERT(size == sizeof(FSNTValue));

            /* Change variables */
            link->rcInfo.FSNT = rcFSNTValue->FSNT;

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
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
 *      RC entry point
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
RC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
        ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("RC_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           RC_StateName(link->rcInfo.curState));
#endif
    switch (trigger)
    {
    case MGMT_RC_TRIGGER_CongestionAccept:
    case MGMT_RC_TRIGGER_CongestionDiscard:
    case MGMT_RC_TRIGGER_NoCongestion:
        RC_Handle_MGMT(link, trigger, data, size);
        break;

    case LSC_RC_TRIGGER_Start:
    case LSC_RC_TRIGGER_Stop:
    case LSC_RC_TRIGGER_RetrieveBSNT:
    case LSC_RC_TRIGGER_RetrieveFSNX:
    case LSC_RC_TRIGGER_AcceptMSUOrFISU:
    case LSC_RC_TRIGGER_RejectMSUOrFISU:
        RC_Handle_LSC(link, trigger, data, size);
        break;

    case DAEDR_RC_TRIGGER_SignalUnit:
        RC_Handle_DAEDR(link, trigger, data, size);
        break;

    case TXC_RC_TRIGGER_FSNTValue:
        RC_Handle_TXC(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for IAC\n",
                    trigger);
        break;
    }
}

