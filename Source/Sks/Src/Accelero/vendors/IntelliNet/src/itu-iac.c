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
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:08  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.3  2006/07/04 12:04:34  gdevanand
 * LOG: Modification according to Q-703 SDL
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:35:00  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-iac.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include <mtp2_intern.h>

#define MAX_IAC_ABORTS   5

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 */

static const char *stateNames[] =
{
    "IAC_STATE_IDLE",
    "IAC_STATE_NOT_ALIGNED",
    "IAC_STATE_ALIGNED",
    "IAC_STATE_PROVING",
    "IAC_STATE_MAX_STATE"
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
IAC_StateName(IAC_States state)
{
    if (state < IAC_STATE_IDLE || state >= IAC_STATE_MAX_STATE)
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
IAC_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->iacInfo.curState >= IAC_STATE_IDLE &&
               link->iacInfo.curState < IAC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->iacInfo.curState)
    {
    case IAC_STATE_IDLE:
        switch (trigger)
        {
        /* Sheet 1 */
        case LSC_IAC_TRIGGER_Emergency:
            /* Change variables */
            link->iacInfo.emergency = ITS_TRUE;
            /* remain in state */
            break;

        /* Sheet 1 */
        case LSC_IAC_TRIGGER_Start:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_NOT_ALIGNED;

            /* Send triggers */
            TXC_Main(link, IAC_TXC_TRIGGER_SendSIO, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StartT2, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_NOT_ALIGNED:
        switch (trigger)
        {
        /* Sheet 1 */
        case LSC_IAC_TRIGGER_Stop:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT2, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 2 */
        case LSC_IAC_TRIGGER_Emergency:
            /* Change variables */
            link->iacInfo.emergency = ITS_TRUE;

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state NOT_ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_ALIGNED:
        switch (trigger)
        {
        /* Sheet 3 */
        case LSC_IAC_TRIGGER_Emergency:
            /* Send triggers */
            TXC_Main(link, IAC_TXC_TRIGGER_SendSIE, NULL, 0);

            /* Change variables */
            link->configData.T4 = link->iacInfo.Pe;
            printk(" ################ TIMER T4E : %d \n",link->iacInfo.Pe); 

            /* Remain in state */
            break;

        /* Sheet 4 */ 
        case LSC_IAC_TRIGGER_Stop:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT3, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_PROVING:
        switch (trigger)
        {
        /* Sheet 5 */
        case LSC_IAC_TRIGGER_Stop:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);
            AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 6 */
        case LSC_IAC_TRIGGER_Emergency:
            /* Send triggers */
            TXC_Main(link, IAC_TXC_TRIGGER_SendSIE, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);

            /* Change variables */
            link->configData.T4 = link->iacInfo.Pe;

            /* Send triggers */
            AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);
            AERM_Main(link, IAC_AERM_TRIGGER_SetTiToTie, NULL, 0);
            AERM_Main(link, IAC_AERM_TRIGGER_Start, NULL, 0);

            /* Change variables */
            link->iacInfo.furtherProving = ITS_FALSE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StartT4, NULL, 0);

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROVING\n",
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
IAC_Handle_DAEDR(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->iacInfo.curState >= IAC_STATE_IDLE &&
               link->iacInfo.curState < IAC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= DAEDR_TRIGGER_MIN &&
               trigger <= DAEDR_TRIGGER_MAX);

    switch (link->iacInfo.curState)
    {
    case IAC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_NOT_ALIGNED:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state NOT_ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_ALIGNED:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_PROVING:
        switch (trigger)
        {
        /* Sheet 5 */
        case DAEDR_IAC_TRIGGER_CorrectSU:
            /* Check variables */
            if (link->iacInfo.furtherProving)
            {
                /* Send triggers */
                TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);
                AERM_Main(link, IAC_AERM_TRIGGER_Start, NULL, 0);

                /* Change variables */
                link->iacInfo.furtherProving = ITS_FALSE;

                /* Send triggers */
                TIMER_Main(link, TIMER_TRIGGER_StartT4, NULL, 0);

                /* Remain in state */
            }
            /* else remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROVING\n",
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
IAC_Handle_RC(MTP2_LinkState *link, MTP2_Trigger trigger,
              ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->iacInfo.curState >= IAC_STATE_IDLE &&
               link->iacInfo.curState < IAC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= RC_TRIGGER_MIN &&
               trigger <= RC_TRIGGER_MAX);

    switch (link->iacInfo.curState)
    {
    case IAC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_NOT_ALIGNED:
        switch (trigger)
        {
        /* Sheet 2 */
        case RC_IAC_TRIGGER_ReceiveSIO:
        case RC_IAC_TRIGGER_ReceiveSIN:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_ALIGNED;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT2, NULL, 0);

            /* Check variables */
            if (link->iacInfo.emergency)
            {
                /* Change variables */
                link->configData.T4 = link->iacInfo.Pe;

                /* Send triggers */
                TXC_Main(link, IAC_TXC_TRIGGER_SendSIE, NULL, 0);
            }
            else
            {
                /* Change variables */
                link->configData.T4 = link->iacInfo.Pn;

                /* Send triggers */
                TXC_Main(link, IAC_TXC_TRIGGER_SendSIN, NULL, 0);
            }

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StartT3, NULL, 0);
            break;

        /* Sheet 2 */
        case RC_IAC_TRIGGER_ReceiveSIE:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_ALIGNED;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT2, NULL, 0);

            /* Check variables */
            if (link->iacInfo.emergency)
            {
                /* Change variables */
                link->configData.T4 = link->iacInfo.Pe;

                /* Send triggers */
                TXC_Main(link, IAC_TXC_TRIGGER_SendSIE, NULL, 0);
            }
            else
            {
                /* Change variables */
                link->configData.T4 = link->iacInfo.Pe;

                /* Send triggers */
                TXC_Main(link, IAC_TXC_TRIGGER_SendSIN, NULL, 0);
            }

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StartT3, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state NOT_ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_ALIGNED:
        switch (trigger)
        {
        /* Sheet 3 */
        case RC_IAC_TRIGGER_ReceiveSIE:
            /* Change variables */
            link->configData.T4 = link->iacInfo.Pe;

            /* FALL THROUGH */

        case RC_IAC_TRIGGER_ReceiveSIN:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_PROVING;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT3, NULL, 0);

            /* Check variables */
            if (link->configData.T4 == link->iacInfo.Pe)
            {
                /* Send triggers */
                AERM_Main(link, IAC_AERM_TRIGGER_SetTiToTie, NULL, 0);
            }

            /* Send triggers */
            AERM_Main(link, IAC_AERM_TRIGGER_Start, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StartT4, NULL, 0);

            /* Change variables */
            link->iacInfo.Cp = 0;
            link->iacInfo.furtherProving = ITS_FALSE;
            break;

        /* Sheet 4 */
        case RC_IAC_TRIGGER_ReceiveSIOS:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            LSC_Main(link, IAC_LSC_TRIGGER_AlignmentNotPossible, NULL, 0);

/* DEV : Timer T3 need to be stop here, added */
            TIMER_Main(link, TIMER_TRIGGER_StopT3, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_PROVING:
        switch (trigger)
        {
        /* Sheet 5 */
        case RC_IAC_TRIGGER_ReceiveSIO:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_ALIGNED;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);
            AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StartT3, NULL, 0);
            break;

        /* Sheet 5 */
        case RC_IAC_TRIGGER_ReceiveSIOS:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);
            LSC_Main(link, IAC_LSC_TRIGGER_AlignmentNotPossible, NULL, 0);
            AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        /* Sheet 6 */
        case RC_IAC_TRIGGER_ReceiveSIE:
            /* Check variables */
            if (link->configData.T4 != link->iacInfo.Pe)
            {
                /* Send triggers */
/* DEV : sheet 6 do not say to send SIE
                TXC_Main(link, IAC_TXC_TRIGGER_SendSIE, NULL, 0);
*/
                TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);

                /* Change variables */
                link->configData.T4 = link->iacInfo.Pe;

                /* Send triggers */
                AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);
                AERM_Main(link, IAC_AERM_TRIGGER_SetTiToTie, NULL, 0);
                AERM_Main(link, IAC_AERM_TRIGGER_Start, NULL, 0);

                /* Change variables */
                link->iacInfo.furtherProving = ITS_FALSE;

                /* Send triggers */
                TIMER_Main(link, TIMER_TRIGGER_StartT4, NULL, 0);
            }
            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROVING\n",
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
 *      Handle AERM messages
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
IAC_Handle_AERM(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->iacInfo.curState >= IAC_STATE_IDLE &&
               link->iacInfo.curState < IAC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= AERM_TRIGGER_MIN &&
               trigger <= AERM_TRIGGER_MAX);

    switch (link->iacInfo.curState)
    {
    case IAC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_NOT_ALIGNED:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state NOT_ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_ALIGNED:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_PROVING:
        switch (trigger)
        {
        /* Sheet 6 */
        case AERM_IAC_TRIGGER_AbortProving:
            /* Change variables */
            link->iacInfo.Cp++;

            /* Check variables */
            if (link->iacInfo.Cp == MAX_IAC_ABORTS)
            {
                /* Change state */
                link->iacInfo.curState = IAC_STATE_IDLE;

                /* Send triggers */
                LSC_Main(link, IAC_LSC_TRIGGER_AlignmentNotPossible, NULL, 0);
                TIMER_Main(link, TIMER_TRIGGER_StopT4, NULL, 0);
                AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);

                /* Change variables */
                link->iacInfo.emergency = ITS_FALSE;
            }
            else
            {
                /* Change variables */
/* DEV : worng variable changed.
                link->iacInfo.emergency = ITS_FALSE;
                link->iacInfo.furtherProving = ITS_TRUE;
*/

                /* Remain in state */
            }
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROVING\n",
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
IAC_Handle_TIMER(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->iacInfo.curState >= IAC_STATE_IDLE &&
               link->iacInfo.curState < IAC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TIMER_TRIGGER_MIN &&
               trigger <= TIMER_TRIGGER_MAX);

    switch (link->iacInfo.curState)
    {
    case IAC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_NOT_ALIGNED:
        switch (trigger)
        {
        /* Sheet 1 */
        case TIMER_TRIGGER_T2Expired:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            LSC_Main(link, IAC_LSC_TRIGGER_AlignmentNotPossible, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state NOT_ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_ALIGNED:
        switch (trigger)
        {
        /* Sheet 4 */
        case TIMER_TRIGGER_T3Expired:
            /* Change state */
            link->iacInfo.curState = IAC_STATE_IDLE;

            /* Send triggers */
            LSC_Main(link, IAC_LSC_TRIGGER_AlignmentNotPossible, NULL, 0);

            /* Change variables */
            link->iacInfo.emergency = ITS_FALSE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state ALIGNED\n",
                        trigger);
            break;
        }
        break;

    case IAC_STATE_PROVING:
        switch (trigger)
        {
        /* Sheet 5 */
        case TIMER_TRIGGER_T4Expired:
            /* Check variables */
            if (link->iacInfo.furtherProving)
            {
                /* Send triggers */
                AERM_Main(link, IAC_AERM_TRIGGER_Start, NULL, 0);

                /* Change variables */
                link->iacInfo.furtherProving = ITS_FALSE;

                /* Send triggers */
                TIMER_Main(link, TIMER_TRIGGER_StartT4, NULL, 0);

                /* Remain in state */
            }
            else
            {
                /* Change state */
                link->iacInfo.curState = IAC_STATE_IDLE;

                /* Send triggers */
                LSC_Main(link, IAC_LSC_TRIGGER_AlignmentComplete, NULL, 0);
                AERM_Main(link, IAC_AERM_TRIGGER_Stop, NULL, 0);

                /* Change variables */
                link->iacInfo.emergency = ITS_FALSE;
            }
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state PROVING\n",
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
 *      IAC entry point
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
IAC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
         ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("IAC_Main: trigger %s stateName %s\n",
           MTP2_TriggerToString(trigger),
           IAC_StateName(link->iacInfo.curState));
#endif
    switch (trigger)
    {
    case LSC_IAC_TRIGGER_Start:
    case LSC_IAC_TRIGGER_Stop:
    case LSC_IAC_TRIGGER_Emergency:
        IAC_Handle_LSC(link, trigger, data, size);
        break;

    case DAEDR_IAC_TRIGGER_CorrectSU:
        IAC_Handle_DAEDR(link, trigger, data, size);
        break;

    case RC_IAC_TRIGGER_ReceiveSIO:
    case RC_IAC_TRIGGER_ReceiveSIN:
    case RC_IAC_TRIGGER_ReceiveSIE:
    case RC_IAC_TRIGGER_ReceiveSIOS:
        IAC_Handle_RC(link, trigger, data, size);
        break;

    case AERM_IAC_TRIGGER_AbortProving:
        IAC_Handle_AERM(link, trigger, data, size);
        break;

    case TIMER_TRIGGER_T2Expired:
    case TIMER_TRIGGER_T3Expired:
    case TIMER_TRIGGER_T4Expired:
        IAC_Handle_TIMER(link, trigger, data, size);

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for IAC\n",
                    trigger);
        break;
    }
}

