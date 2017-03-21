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
 * LOG: Revision 1.1.2.3  2006/06/14 17:04:31  gdevanand
 * LOG: Commiting after mtp2 testing, 2.2 changes will not be there.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-daedt.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 *
 * This one is easy.  There's only one sheet.
 *
 * A bit of a mislead.  This is where the ISR is going to have
 * to take it from L2.  Alternatively, you implement what's in
 * the comments.
 */

static const char *stateNames[] =
{
    "DAEDT_STATE_IDLE",
    "DAEDT_STATE_IN_SERVICE",
    "DAEDT_STATE_MAX_STATE"
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
DAEDT_StateName(DAEDT_States state)
{
    if (state < DAEDT_STATE_IDLE || state >= DAEDT_STATE_MAX_STATE)
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
DAEDT_Handle_TXC(MTP2_LinkState *link, MTP2_Trigger trigger,
                 ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->daedtInfo.curState >= DAEDT_STATE_IDLE &&
               link->daedtInfo.curState < DAEDT_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= TXC_TRIGGER_MIN &&
               trigger <= TXC_TRIGGER_MAX);

    switch (link->daedtInfo.curState)
    {
    case DAEDT_STATE_IDLE:
        switch (trigger)
        {
        case TXC_DAEDT_TRIGGER_Start:
            /* Change state */
            link->daedtInfo.curState = DAEDT_STATE_IN_SERVICE;

            /* Send triggers */
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);
            break;

        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case DAEDT_STATE_IN_SERVICE:
        switch (trigger)
        {
        case TXC_DAEDT_TRIGGER_SignalUnit:
            /* Send triggers */
            L1_Main(link, DAEDT_L1_TRIGGER_BitsForTransmission, data, size);
#if 0
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);
#endif

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

/*.implementation:extern
 ************************************************************************
 *  Purpose:
 *      DAEDT entry point
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
DAEDT_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
           ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("DAEDT_Main: trigger %s curState %s\n", 
           MTP2_TriggerToString(trigger),
           DAEDT_StateName(link->daedtInfo.curState));
#endif
    switch (trigger)
    {
    case TXC_DAEDT_TRIGGER_Start:
    case TXC_DAEDT_TRIGGER_SignalUnit:
        DAEDT_Handle_TXC(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for DAEDT\n",
                    trigger);
        break;
    }
}

