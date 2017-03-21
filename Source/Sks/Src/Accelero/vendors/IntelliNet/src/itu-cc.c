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
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:34:31  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-cc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 */

static const char *stateNames[] =
{
    "CC_STATE_IDLE",
    "CC_STATE_L2_CONGESTION",
    "CC_STATE_MAX_STATE"
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
CC_StateName(CC_States state)
{
    if (state < CC_STATE_IDLE || state >= CC_STATE_MAX_STATE)
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
CC_Handle_RC(MTP2_LinkState *link, MTP2_Trigger trigger,
             ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->ccInfo.curState >= CC_STATE_IDLE &&
               link->ccInfo.curState < CC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= RC_TRIGGER_MIN &&
               trigger <= RC_TRIGGER_MAX);

    switch (link->ccInfo.curState)
    {
    case CC_STATE_IDLE:
        switch (trigger)
        {
        case RC_CC_TRIGGER_Busy:
            /* Change state */
            link->ccInfo.curState = CC_STATE_L2_CONGESTION;

            /* Send triggers */
            TXC_Main(link, CC_TXC_TRIGGER_SendSIB, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StartT5, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case CC_STATE_L2_CONGESTION:
        switch (trigger)
        {
        case RC_CC_TRIGGER_Busy:
            /* remain in state */
            break;

        case RC_CC_TRIGGER_Normal:
            /* Change state */
            link->ccInfo.curState = CC_STATE_IDLE;

            /* Send triggers */
            TIMER_Main(link, TIMER_TRIGGER_StopT5, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state L2_CONGESTION\n",
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
CC_Handle_TIMER(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->ccInfo.curState >= CC_STATE_IDLE &&
               link->ccInfo.curState < CC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TIMER_TRIGGER_MIN &&
               trigger <= TIMER_TRIGGER_MAX);

    switch (link->ccInfo.curState)
    {
    case CC_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case CC_STATE_L2_CONGESTION:
        switch (trigger)
        {
        case TIMER_TRIGGER_T5Expired:
            /* Send triggers */
            TXC_Main(link, CC_TXC_TRIGGER_SendSIB, NULL, 0);
            TIMER_Main(link, TIMER_TRIGGER_StartT5, NULL, 0);

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state L2_CONGESTION\n",
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
 *      CC entry point
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
CC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
        ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("CC_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           CC_StateName(link->ccInfo.curState));
#endif
    switch (trigger)
    {
    case RC_CC_TRIGGER_Normal:
    case RC_CC_TRIGGER_Busy:
        CC_Handle_RC(link, trigger, data, size);
        break;

    case TIMER_TRIGGER_T5Expired:
        CC_Handle_TIMER(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for CC\n",
                    trigger);
        break;
    }
}

