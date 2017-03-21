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
 * LOG: Revision 1.1.2.3  2006/07/04 12:13:54  gdevanand
 * LOG: Modification according to Q-703 SDL
 * LOG:
 * LOG: Revision 1.1.2.2  2006/06/12 06:37:13  gdevanand
 * LOG: Changes for mcc driver (Badri).
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-poc.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"
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
    "POC_STATE_IDLE",
    "POC_STATE_LOCAL_PROCESSOR_OUTAGE",
    "POC_STATE_REMOTE_PROCESSOR_OUTAGE",
    "POC_STATE_BOTH_PROCESSORS_OUT",
    "POC_STATE_MAX_STATE"
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
POC_StateName(POC_States state)
{
    if (state < POC_STATE_IDLE || state >= POC_STATE_MAX_STATE)
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
POC_Handle_LSC(MTP2_LinkState *link, MTP2_Trigger trigger,
               ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->pocInfo.curState >= POC_STATE_IDLE &&
               link->pocInfo.curState < POC_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= LSC_TRIGGER_MIN &&
               trigger <= LSC_TRIGGER_MAX);

    switch (link->pocInfo.curState)
    {
    case POC_STATE_IDLE:
        switch (trigger)
        {
        case LSC_POC_TRIGGER_LocalProcessorOutage:
            /* Change state */
            link->pocInfo.curState = POC_STATE_LOCAL_PROCESSOR_OUTAGE;
            break;

        case LSC_POC_TRIGGER_RemoteProcessorOutage:
            /* Change state */
            link->pocInfo.curState = POC_STATE_REMOTE_PROCESSOR_OUTAGE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case POC_STATE_LOCAL_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        case LSC_POC_TRIGGER_Stop:
            /* Change state */
            link->pocInfo.curState = POC_STATE_IDLE;
            break;

        case LSC_POC_TRIGGER_RemoteProcessorOutage:
            /* Change state */
            link->pocInfo.curState = POC_STATE_BOTH_PROCESSORS_OUT;
            break;

        case LSC_POC_TRIGGER_LocalProcessorRecovered:
            /* Send trigger */
            LSC_Main(link, POC_LSC_TRIGGER_NoProcessorOutage, NULL, 0);

            /* Change state */
            link->pocInfo.curState = POC_STATE_IDLE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state LOCAL_PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case POC_STATE_REMOTE_PROCESSOR_OUTAGE:
        switch (trigger)
        {
        case LSC_POC_TRIGGER_LocalProcessorOutage:
            /* Change state */
            link->pocInfo.curState = POC_STATE_BOTH_PROCESSORS_OUT;
            break;

        case LSC_POC_TRIGGER_RemoteProcessorRecovered:
            /* Change state */
/* DEV : SDL says state should be IDLE
            link->pocInfo.curState = POC_STATE_LOCAL_PROCESSOR_OUTAGE;
*/
            link->pocInfo.curState = POC_STATE_IDLE;

            /* Send trigger */
            LSC_Main(link, POC_LSC_TRIGGER_NoProcessorOutage, NULL, 0);
            break;

        case LSC_POC_TRIGGER_Stop:
            /* Change state */
            link->pocInfo.curState = POC_STATE_IDLE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state REMOTE_PROCESSOR_OUTAGE\n",
                        trigger);
            break;
        }
        break;

    case POC_STATE_BOTH_PROCESSORS_OUT:
        switch (trigger)
        {
        case LSC_POC_TRIGGER_RemoteProcessorRecovered:
            /* Change state */
            link->pocInfo.curState = POC_STATE_LOCAL_PROCESSOR_OUTAGE;
            break;

        case LSC_POC_TRIGGER_LocalProcessorRecovered:
            /* Change state */
            link->pocInfo.curState = POC_STATE_REMOTE_PROCESSOR_OUTAGE;
            break;

        case LSC_POC_TRIGGER_Stop:
            /* Change state */
            link->pocInfo.curState = POC_STATE_IDLE;
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state BOTH_PROCESSORS_OUT\n",
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
 *      POC entry point
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
POC_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
         ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("POC_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           POC_StateName(link->pocInfo.curState));
#endif
    switch (trigger)
    {
    case LSC_POC_TRIGGER_Stop:
    case LSC_POC_TRIGGER_LocalProcessorOutage:
    case LSC_POC_TRIGGER_LocalProcessorRecovered:
    case LSC_POC_TRIGGER_RemoteProcessorOutage:
    case LSC_POC_TRIGGER_RemoteProcessorRecovered:
    case LSC_POC_TRIGGER_NoProcessorOutage:
        POC_Handle_LSC(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for POC\n",
                    trigger);
        break;
    }
}
