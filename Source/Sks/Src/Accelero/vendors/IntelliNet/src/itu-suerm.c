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
 * LOG: Revision 1.3  2007/09/13 09:19:34  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:10  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:38:21  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-suerm.c,v 1.1.1.1 2007-10-08 11:12:16 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 *
 * This one is easy.  There's only one sheet.
 */

static const char *stateNames[] =
{
    "SUERM_STATE_IDLE",
    "SUERM_STATE_IN_SERVICE",
    "SUERM_STATE_MAX_STATE"
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
SUERM_StateName(SUERM_States state)
{
    if (state < SUERM_STATE_IDLE || state >= SUERM_STATE_MAX_STATE)
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
SUERM_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->suermInfo.curState >= SUERM_STATE_IDLE &&
               link->suermInfo.curState < SUERM_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->suermInfo.curState)
    {
    case SUERM_STATE_IDLE:
        switch (trigger)
        {
        case LSC_SUERM_TRIGGER_Start:
            /* Change state */
            link->suermInfo.curState = SUERM_STATE_IN_SERVICE;

            /* Change variables */
            link->suermInfo.Cs = 0;
            link->suermInfo.Nsu = 0;

            /* Clearly this is all that matters here */
            MTP2_ToggleSUERM(link, 1);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case SUERM_STATE_IN_SERVICE:
        switch (trigger)
        {
        case LSC_SUERM_TRIGGER_Stop:
            /* Change state */
            link->suermInfo.curState = SUERM_STATE_IDLE;

            /* Clearly this is all that matters here */
            MTP2_ToggleSUERM(link, 0);
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
SUERM_Handle_DAEDR(MTP2_LinkState *link, MTP2_Trigger trigger,
                   ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->suermInfo.curState >= SUERM_STATE_IDLE &&
               link->suermInfo.curState < SUERM_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= DAEDR_TRIGGER_MIN &&
               trigger <= DAEDR_TRIGGER_MAX);

    switch (link->suermInfo.curState)
    {
    case SUERM_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case SUERM_STATE_IN_SERVICE:
        switch (trigger)
        {
        case DAEDR_SUERM_TRIGGER_SUInError:
            /* Change variables */
            link->suermInfo.Cs = link->suermInfo.Cs + 1;
            link->suermInfo.Nsu = link->suermInfo.Nsu + 1;

            /* Check variables */
            if (link->suermInfo.Cs == link->suermInfo.T)
            {
                /* Change state */
                link->suermInfo.curState = SUERM_STATE_IDLE;

                /* Send triggers */
                LSC_Main(link, SUERM_LSC_TRIGGER_LinkFailure, NULL, 0);
            }
            else
            {
                /* remains in state */
                /* check variables */
                if (link->suermInfo.Nsu == 256)
                {
                    link->suermInfo.Nsu = 0;
                }

                if (link->suermInfo.Cs > 0)
                {
                    link->suermInfo.Cs = link->suermInfo.Cs - 1;
                }
            }
            break;

        case DAEDR_SUERM_TRIGGER_CorrectSU:
            /* Change variables */
            link->suermInfo.Nsu = link->suermInfo.Nsu + 1;

            /* Check variables */
            if (link->suermInfo.Nsu == 256)
            {
                link->suermInfo.Nsu = 0;
            }

            if (link->suermInfo.Cs > 0)
            {
                link->suermInfo.Cs = link->suermInfo.Cs - 1;
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
 *      SUERM entry point
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
SUERM_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
           ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("SUERM_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           SUERM_StateName(link->suermInfo.curState));
#endif
    switch (trigger)
    {
    case LSC_SUERM_TRIGGER_Start:
    case LSC_SUERM_TRIGGER_Stop:
        SUERM_Handle_LSC(link, trigger, data, size);
        break;

    case DAEDR_SUERM_TRIGGER_SUInError:
    case DAEDR_SUERM_TRIGGER_CorrectSU:
        SUERM_Handle_DAEDR(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for SUERM\n",
                    trigger);
        break;
    }
}

