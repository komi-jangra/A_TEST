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
 * LOG: Revision 1.1.2.2  2006/06/12 06:33:57  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-aerm.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include "mtp2_intern.h"

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 *
 * This one is easy.  There's only one sheet.
 */

static const char *stateNames[] =
{
    "AERM_STATE_IDLE",
    "AERM_STATE_MONITORING",
    "AERM_STATE_MAX_STATE"
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
AERM_StateName(AERM_States state)
{
    if (state < AERM_STATE_IDLE || state >= AERM_STATE_MAX_STATE)
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
AERM_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->aermInfo.curState >= AERM_STATE_IDLE &&
               link->aermInfo.curState < AERM_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->aermInfo.curState)
    {
    case AERM_STATE_IDLE:
        switch (trigger)
        {
        case LSC_AERM_TRIGGER_SetTiToTin:
            /* Change variables */
            link->aermInfo.Ti = link->aermInfo.Tin;

            /* remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case AERM_STATE_MONITORING:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state MONITORING\n",
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
AERM_Handle_IAC(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->aermInfo.curState >= AERM_STATE_IDLE &&
               link->aermInfo.curState < AERM_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= IAC_TRIGGER_MIN &&
               trigger <= IAC_TRIGGER_MAX);

    switch (link->aermInfo.curState)
    {
    case AERM_STATE_IDLE:
        switch (trigger)
        {
        case IAC_AERM_TRIGGER_Start:
            /* Change state */
            link->aermInfo.curState = AERM_STATE_MONITORING;

            /* Change variables */
            link->aermInfo.Ca = 0;

            /* Clearly this is all that matters here */
            MTP2_ToggleAERM(link, 1);
            break;

        case IAC_AERM_TRIGGER_SetTiToTie:
            /* Change variables */
            link->aermInfo.Ti = link->aermInfo.Tie;

            /* Remain in state */
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case AERM_STATE_MONITORING:
        switch (trigger)
        {
        case IAC_AERM_TRIGGER_Stop:
            /* Change state */
            link->aermInfo.curState = AERM_STATE_IDLE;

            /* Change variables */
            link->aermInfo.Ti = link->aermInfo.Tin;

            /* Clearly this is all that matters here */
            MTP2_ToggleAERM(link, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state MONITORING\n",
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
AERM_Handle_DAEDR(MTP2_LinkState *link, MTP2_Trigger trigger,
                  ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->aermInfo.curState >= AERM_STATE_IDLE &&
               link->aermInfo.curState < AERM_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= DAEDR_TRIGGER_MIN &&
               trigger <= DAEDR_TRIGGER_MAX);

    switch (link->aermInfo.curState)
    {
    case AERM_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case AERM_STATE_MONITORING:
        switch (trigger)
        {
        case DAEDR_AERM_TRIGGER_SUInError:
            /* Change variables */
            link->aermInfo.Ca = link->aermInfo.Ca + 1;

            /* Check variables */
            if (link->aermInfo.Ca == link->aermInfo.Ti)
            {
                /* Change state */
                link->aermInfo.curState = AERM_STATE_IDLE;

                /* Send triggers */
                IAC_Main(link, AERM_IAC_TRIGGER_AbortProving, NULL, 0);
            }

            /* else remain in state */
            break;
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state MONITORING\n",
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
 *      AERM entry point
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
AERM_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
          ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("AERM_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           AERM_StateName(link->aermInfo.curState));
#endif
    switch (trigger)
    {
    case LSC_AERM_TRIGGER_SetTiToTin:
        AERM_Handle_LSC(link, trigger, data, size);
        break;

    case IAC_AERM_TRIGGER_SetTiToTin:
    case IAC_AERM_TRIGGER_Start:
    case IAC_AERM_TRIGGER_Stop:
        AERM_Handle_IAC(link, trigger, data, size);
        break;

    case DAEDR_AERM_TRIGGER_SUInError:
        AERM_Handle_DAEDR(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for AERM\n",
                    trigger);
        break;
    }
}

