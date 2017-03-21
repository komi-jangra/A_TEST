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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:33  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.4  2006/07/18 15:21:33  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/04 12:24:45  gdevanand
 * LOG: Modification according to Q-703 SDL
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:35:50  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-lsc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"
#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 */

static const char *stateNames[] =
{
    "LSC_STATE_POWER_OFF",
    "LSC_STATE_OUT_OF_SERVICE",
    "LSC_STATE_INITIAL_ALIGNMENT",
    "LSC_STATE_ALIGNED_NOT_READY",
    "LSC_STATE_ALIGNED_READY",
    "LSC_STATE_PROCESSOR_OUTAGE",
    "LSC_STATE_IN_SERVICE",
    "LSC_STATE_MAX_STATE"
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
LSC_StateName(LSC_States state)
{
    if (state < LSC_STATE_POWER_OFF || state >= LSC_STATE_MAX_STATE)
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
LSC_Handle_MGMT(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= MGMT_TRIGGER_MIN &&
               trigger <= MGMT_TRIGGER_MAX);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        /* Sheet 1 */
        case MGMT_LSC_TRIGGER_PowerOn:
            /* New state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_Start, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);
            AERM_Main(link, LSC_AERM_TRIGGER_SetTiToTin, NULL, 0);

            /* Initialize variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        /* Sheet 3 */
        case MGMT_LSC_TRIGGER_LocalProcessorOutage:
        case MGMT_LSC_TRIGGER_L3_Failure:
            printk("%d: LSC_Handle_MGMT: Trigger(lpo/l3Fail) = %d \n", __LINE__,trigger);
            link->lscInfo.localProcessorOutage = ITS_TRUE;

            /* remain in state */
            break;

#if 0
        /* DEV : sheet 3 do not say this */
        /* Sheet 3 */
        case MGMT_LSC_TRIGGER_LocalProcessorRecovered:
            printk("%d: LSC_Handle_MGMT: Trigger=MGMT_LSC_TRIGGER_LocalProcessorRecovered\n", __LINE__);

            link->lscInfo.localProcessorOutage = ITS_FALSE;

            /* remain in state */
            break;
#endif

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        /* Sheet 4 */
        case MGMT_LSC_TRIGGER_LocalProcessorOutage:
        case MGMT_LSC_TRIGGER_L3_Failure:
            link->lscInfo.localProcessorOutage = ITS_TRUE;
printk("%d: LSC_Handle_MGMT: Trigger = lpo/l3failure\n", __LINE__);
            /* remain in state */
            break;

        /* Sheet 4 */
        case MGMT_LSC_TRIGGER_LocalProcessorRecovered:

            link->lscInfo.localProcessorOutage = ITS_FALSE;

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        /* Sheet 9 */
        case MGMT_LSC_TRIGGER_LocalProcessorRecovered:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_ALIGNED_READY;

            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_LocalProcessorRecovered, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;

            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_SendFISU, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_AcceptMSUOrFISU, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        /* Sheet 7 */
        case MGMT_LSC_TRIGGER_LocalProcessorOutage:
        case MGMT_LSC_TRIGGER_L3_Failure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_ALIGNED_NOT_READY;

            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_LocalProcessorOutage, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIPO, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_RejectMSUOrFISU, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        /* Sheet 12 */
        case MGMT_LSC_TRIGGER_LocalProcessorOutage:
        case MGMT_LSC_TRIGGER_L3_Failure:
            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_LocalProcessorOutage, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIPO, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 13 */
        case MGMT_LSC_TRIGGER_LocalProcessorRecovered:
            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_LocalProcessorRecovered, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_RetrieveFSNX, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendFISU, NULL, 0);

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 11 */
        case MGMT_LSC_TRIGGER_LocalProcessorOutage:
        case MGMT_LSC_TRIGGER_L3_Failure:
            /* Change state */
/* DEV : wrong state
            link->lscInfo.curState = LSC_STATE_ALIGNED_NOT_READY;
*/
            link->lscInfo.curState = LSC_STATE_PROCESSOR_OUTAGE;

            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_LocalProcessorOutage, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIPO, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_RejectMSUOrFISU, NULL, 0);

            /* Change variables */
            link->lscInfo.processorOutage = ITS_TRUE;
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
LSC_Handle_L3(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= L3_TRIGGER_MIN &&
               trigger <= L3_TRIGGER_MAX);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        /* Sheet 2 */
        case L3_LSC_TRIGGER_Start:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_INITIAL_ALIGNMENT;

            /* Send triggers */
            RC_Main(link, LSC_RC_TRIGGER_Start, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_Start, NULL, 0);

            /* Emergency? */
            if (link->lscInfo.emergency)
            {
                IAC_Main(link, LSC_IAC_TRIGGER_Emergency, NULL, 0);
            }

            IAC_Main(link, LSC_IAC_TRIGGER_Start, NULL, 0);
            break;

        /* Sheet 2 */
        case L3_LSC_TRIGGER_RetrieveBSNT:
            /* Send triggers */
            RC_Main(link, LSC_RC_TRIGGER_RetrieveBSNT, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 2 */
        case L3_LSC_TRIGGER_RetrievalFSNC:
            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_RetrievalFSNC, data, size);

            /* Remain in state */
            break;

        /* Sheet 3 */
        case L3_LSC_TRIGGER_Emergency:
            /* Set variables */
            link->lscInfo.emergency = ITS_TRUE;

            /* Remain in state */
            break;

        /* Sheet 3 */
        case L3_LSC_TRIGGER_EmergencyEnd:
            /* Set variables */
            link->lscInfo.emergency = ITS_FALSE;

            /* Remain in state */
            break;

        /* Sheet 3 */
        case L3_LSC_TRIGGER_LocalProcessorRecovered:
            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        /* Sheet 4 */
        case L3_LSC_TRIGGER_Emergency:
            /* Set variables */
            link->lscInfo.emergency = ITS_TRUE;

            /* Send triggers */
            IAC_Main(link, LSC_IAC_TRIGGER_Emergency, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 5 */
        case L3_LSC_TRIGGER_Stop:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            IAC_Main(link, LSC_IAC_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        /* Sheet 8 */
        case L3_LSC_TRIGGER_Stop:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        /* Sheet 6 */
        case L3_LSC_TRIGGER_Stop:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        /* Sheet 12 */
        case L3_LSC_TRIGGER_RetrievalFSNC:
            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_RetrievalFSNC, data, size);

            /* Remain in state */
            break;

        /* Sheet 12 */
        case L3_LSC_TRIGGER_RetrieveBSNT:
            /* Send triggers */
            RC_Main(link, LSC_RC_TRIGGER_RetrieveBSNT, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 13 */
        case L3_LSC_TRIGGER_FlushBuffers:
            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_FlushBuffers, NULL, 0);
            /* FALL THROUGH */

        /* Sheet 13 */
        case L3_LSC_TRIGGER_Continue:
            link->lscInfo.l3Received = ITS_TRUE;

            /* Check variables */
            if (!link->lscInfo.processorOutage)
            {
                /* Change state */
                link->lscInfo.curState = LSC_STATE_IN_SERVICE;

                link->lscInfo.l3Received = ITS_FALSE;

                /* Send triggers */
                TXC_Main(link, LSC_TXC_TRIGGER_SendFISU, NULL, 0);
                /* Assumption: SDL is misleading here */

                /* Change variables */
                link->lscInfo.localProcessorOutage = ITS_FALSE;

                /* Send triggers */
                RC_Main(link, LSC_RC_TRIGGER_AcceptMSUOrFISU, NULL, 0);
            }
            /* else remain in state */
            break;

        /* Sheet 14 */
        case L3_LSC_TRIGGER_Stop:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
/* DEV : LSC l3 Out of service trigger not shown in SDL
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
*/
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
/* DEV : wrong trigger LSC_RC sto
            POC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 10 */
        case L3_LSC_TRIGGER_Stop:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
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
LSC_Handle_IAC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= IAC_TRIGGER_MIN &&
               trigger <= IAC_TRIGGER_MAX);

printk("%d: LSC_Handle_IAC Trigger = %d curstate = %d \n",
       __LINE__, trigger, link->lscInfo.curState);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        /* Sheet 5 */
        case IAC_LSC_TRIGGER_AlignmentComplete:
            /* Send triggers */
            SUERM_Main(link, LSC_SUERM_TRIGGER_Start, NULL, 0);

            /* Start T1 */
            TIMER_Main(link, TIMER_TRIGGER_StartT1, NULL, 0);

            /* Check variable */
            if (link->lscInfo.localProcessorOutage)
            {
                /* Change state */
                link->lscInfo.curState = LSC_STATE_ALIGNED_NOT_READY;

                /* Send triggers */
                POC_Main(link, LSC_POC_TRIGGER_LocalProcessorOutage, NULL, 0);
                TXC_Main(link, LSC_TXC_TRIGGER_SendSIPO, NULL, 0);
                RC_Main(link, LSC_RC_TRIGGER_RejectMSUOrFISU, NULL, 0);
            }
            else
            {
                /* Change state */
                link->lscInfo.curState = LSC_STATE_ALIGNED_READY;

                /* Send triggers */
                TXC_Main(link, LSC_TXC_TRIGGER_SendFISU, NULL, 0);
                RC_Main(link, LSC_RC_TRIGGER_AcceptMSUOrFISU, NULL, 0);

                /* MLM: Special case.  Due to SU filtering, we won't get FISU */
                MTP2_ResetFISUFilter(link);
            }
            break;

        /* Sheet 5 */
        case IAC_LSC_TRIGGER_AlignmentNotPossible:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
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
 *      Handle POC messages
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
LSC_Handle_POC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= POC_TRIGGER_MIN &&
               trigger <= POC_TRIGGER_MAX);

    printk("%d :LSC_Handle_POC Trigger = %d Curstate = %d\n",
            __LINE__, trigger, link->lscInfo.curState);
    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        /* Sheet 13 */
        case POC_LSC_TRIGGER_NoProcessorOutage:
            /* Change variables */
            link->lscInfo.processorOutage = ITS_FALSE;

            /* Check variables */
            if (link->lscInfo.l3Received)
            {
                /* Change state */
                link->lscInfo.curState = LSC_STATE_IN_SERVICE;

                /* Change variables */
                link->lscInfo.l3Received = ITS_FALSE;

                /* Send triggers */
                TXC_Main(link, LSC_TXC_TRIGGER_SendMSU, NULL, 0);
                /* Assumption: SDL is confusing here */

                /* Change variables */
                link->lscInfo.localProcessorOutage = ITS_FALSE;

                /* Send triggers */
                RC_Main(link, LSC_RC_TRIGGER_AcceptMSUOrFISU, NULL, 0);
            }
            /* else remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
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
LSC_Handle_TXC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TXC_TRIGGER_MIN &&
               trigger <= TXC_TRIGGER_MAX);

     printk("%d: LSC_Handle_TXC Trigger = %d Curstate=%d\n",
             __LINE__, trigger, link->lscInfo.curState);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 10 */
        case TXC_LSC_TRIGGER_LinkFailure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
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
LSC_Handle_RC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= RC_TRIGGER_MIN &&
               trigger <= RC_TRIGGER_MAX);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        /* Sheet 5 */
        case RC_LSC_TRIGGER_LinkFailure:
printk("Trigger is RC_LSC_TR_Link Failure. in LSC_INITIAL ALIGNMENT.\n");
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            IAC_Main(link, LSC_IAC_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        /* Sheet 8 */
        case RC_LSC_TRIGGER_LinkFailure:
        case RC_LSC_TRIGGER_ReceiveSIO:
        case RC_LSC_TRIGGER_ReceiveSIOS:
printk("Tri failure rcvsio rcvsios. 0x%x \n", trigger);
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

/* DEV : wrong trigger
            POC_Main(link, LSC_TXC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);

            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 9 */
        case RC_LSC_TRIGGER_ReceiveMSUOrFISU:
printk("rc_lsc_rcv_mscorfisu.\n");
            /* Change state: HUH? */
            link->lscInfo.curState = LSC_STATE_PROCESSOR_OUTAGE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_InService, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            break;

        /* Sheet 9 */
        case RC_LSC_TRIGGER_ReceiveSIPO:
printk("rc_lsc_rcvsipo\n");
            /* Change state */
            link->lscInfo.curState = LSC_STATE_PROCESSOR_OUTAGE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_RemoteProcessorOutage, NULL, 0);
            POC_Main(link, LSC_POC_TRIGGER_RemoteProcessorOutage, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        /* Sheet 6 */
        case RC_LSC_TRIGGER_LinkFailure:
        case RC_LSC_TRIGGER_ReceiveSIO:
        case RC_LSC_TRIGGER_ReceiveSIOS:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);
            
            /* Set variables */
            link->lscInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 7 */
        case RC_LSC_TRIGGER_ReceiveSIPO:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_PROCESSOR_OUTAGE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_RemoteProcessorOutage, NULL, 0);
            POC_Main(link, LSC_POC_TRIGGER_RemoteProcessorOutage, NULL, 0);
            break;

        /* Sheet 7 */
        case RC_LSC_TRIGGER_ReceiveMSUOrFISU:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_IN_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_InService, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendMSU, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        /* Sheet 12 */
        case RC_LSC_TRIGGER_ReceiveMSUOrFISU:
            /* Send triggers */
            POC_Main(link, LSC_POC_TRIGGER_RemoteProcessorRecovered, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_RemoteProcessorRecovered, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 12 */
        case RC_LSC_TRIGGER_ReceiveSIPO:
            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_RemoteProcessorOutage, NULL, 0);
            POC_Main(link, LSC_POC_TRIGGER_RemoteProcessorOutage, NULL, 0);

            /* Remain in state */
            break;

        /* Sheet 14 */
        case RC_LSC_TRIGGER_LinkFailure:
        case RC_LSC_TRIGGER_ReceiveSIO:
        case RC_LSC_TRIGGER_ReceiveSIN:
        case RC_LSC_TRIGGER_ReceiveSIE:
        case RC_LSC_TRIGGER_ReceiveSIOS:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
/* DEV : LSC RC stop tigger is wrong
            POC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 10 */
        case RC_LSC_TRIGGER_LinkFailure:
        case RC_LSC_TRIGGER_ReceiveSIO:
        case RC_LSC_TRIGGER_ReceiveSIN:
        case RC_LSC_TRIGGER_ReceiveSIE:
        case RC_LSC_TRIGGER_ReceiveSIOS:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 11 */
        case RC_LSC_TRIGGER_ReceiveSIPO:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_PROCESSOR_OUTAGE;

            /* Send triggers */
            TXC_Main(link, LSC_TXC_TRIGGER_SendFISU, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_RemoteProcessorOutage, NULL, 0);
            POC_Main(link, LSC_POC_TRIGGER_RemoteProcessorOutage, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_TRUE;
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
 *      Handle SUERM messages
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
LSC_Handle_SUERM(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= SUERM_TRIGGER_MIN &&
               trigger <= SUERM_TRIGGER_MAX);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        /* Sheet 8 */
        case SUERM_LSC_TRIGGER_LinkFailure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

/* DEV : wrong trigger
            POC_Main(link, LSC_TXC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);

            /* Set variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        /* Sheet 6 */
        case SUERM_LSC_TRIGGER_LinkFailure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT1, NULL, 0);
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Set variables */
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        /* Sheet 14 */
        case SUERM_LSC_TRIGGER_LinkFailure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
/* DEV : LSC RC stop trigger is wrong
            POC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheet 10 */
        case SUERM_LSC_TRIGGER_LinkFailure:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
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
LSC_Handle_TIMER(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->lscInfo.curState >= LSC_STATE_POWER_OFF &&
               link->lscInfo.curState < LSC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TIMER_TRIGGER_MIN &&
               trigger <= TIMER_TRIGGER_MAX);

    switch (link->lscInfo.curState)
    {
    case LSC_STATE_POWER_OFF:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state POWER_OFF\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_OUT_OF_SERVICE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state OUT_OF_SERVICE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_INITIAL_ALIGNMENT:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state INITIAL_ALIGNMENT\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_NOT_READY:
        switch (trigger)
        {
        /* Sheet 8 */
        case TIMER_TRIGGER_T1Expired:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

/* DEV : missing trigger LSC_L3 Out of Service added */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);

            L3_Main(link, LSC_L3_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

/* DEV : wrong trigger
            POC_Main(link, LSC_TXC_TRIGGER_Stop, NULL, 0);
*/
            POC_Main(link, LSC_POC_TRIGGER_Stop, NULL, 0);


            /* Change variables */
            link->lscInfo.localProcessorOutage = ITS_FALSE;
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_NOT_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_ALIGNED_READY:
        switch (trigger)
        {
        /* Sheet 6 */
        case TIMER_TRIGGER_T1Expired:
            /* Change state */
            link->lscInfo.curState = LSC_STATE_OUT_OF_SERVICE;

            /* Send triggers */
            L3_Main(link, LSC_L3_TRIGGER_OutOfService, NULL, 0);
            RC_Main(link, LSC_RC_TRIGGER_Stop, NULL, 0);
            SUERM_Main(link, LSC_SUERM_TRIGGER_Stop, NULL, 0);
            TXC_Main(link, LSC_TXC_TRIGGER_SendSIOS, NULL, 0);

            /* Change variables */
            link->lscInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED_READY\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case LSC_STATE_IN_SERVICE:
        switch (trigger)
        {
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
 *      LSC entry point
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
LSC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
         ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("LSC_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           LSC_StateName(link->lscInfo.curState));
#endif
    switch (trigger)
    {
    case MGMT_LSC_TRIGGER_PowerOn:
    case MGMT_LSC_TRIGGER_L3_Failure:
    case MGMT_LSC_TRIGGER_LocalProcessorOutage:
    case MGMT_LSC_TRIGGER_LocalProcessorRecovered:
        LSC_Handle_MGMT(link, trigger, data, size);
        break;

    case L3_LSC_TRIGGER_Start:
    case L3_LSC_TRIGGER_Stop:
    case L3_LSC_TRIGGER_Continue:
    case L3_LSC_TRIGGER_RetrieveBSNT:
    case L3_LSC_TRIGGER_RetrievalFSNC:
    case L3_LSC_TRIGGER_Emergency:
    case L3_LSC_TRIGGER_EmergencyEnd:
    case L3_LSC_TRIGGER_LocalProcessorRecovered:
    case L3_LSC_TRIGGER_FlushBuffers:
        LSC_Handle_L3(link, trigger, data, size);
        break;

    case IAC_LSC_TRIGGER_AlignmentComplete:
    case IAC_LSC_TRIGGER_AlignmentNotPossible:
        LSC_Handle_IAC(link, trigger, data, size);
        break;

    case POC_LSC_TRIGGER_NoProcessorOutage:
        LSC_Handle_POC(link, trigger, data, size);
        break;

    case TXC_LSC_TRIGGER_LinkFailure:
        LSC_Handle_TXC(link, trigger, data, size);
        break;

    case RC_LSC_TRIGGER_LinkFailure:
    case RC_LSC_TRIGGER_ReceiveSIO:
    case RC_LSC_TRIGGER_ReceiveSIN:
    case RC_LSC_TRIGGER_ReceiveSIE:
    case RC_LSC_TRIGGER_ReceiveSIOS:
    case RC_LSC_TRIGGER_ReceiveSIPO:
    case RC_LSC_TRIGGER_ReceiveMSUOrFISU:
        LSC_Handle_RC(link, trigger, data, size);
        break;

    case SUERM_LSC_TRIGGER_LinkFailure:
        LSC_Handle_SUERM(link, trigger, data, size);
        break;

    case TIMER_TRIGGER_T1Expired:
        LSC_Handle_TIMER(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for LSC\n",
                    trigger);
        break;
    }
}

