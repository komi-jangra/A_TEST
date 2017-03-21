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
 * LOG: Revision 1.1.2.4  2006/07/18 15:21:32  sjaddu
 * LOG: MTP2 : 2 link alignment changes
 * LOG:
 * LOG: Revision 1.1.2.3  2006/06/14 17:03:11  gdevanand
 * LOG: Commiting after mtp2 testing, 2.2 changes will not be there.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: itu-daedr.c,v 1.1.1.1 2007-10-08 11:12:15 bsccs2 Exp $"

#include <mtp2_intern.h>

/*
 * This code is intended to be self documenting.  Find the
 * corresponding state in the SDLs for this subsystem.  Then
 * find the trigger source.  The actions should then be obvious.
 *
 * This one is easy.  There's only two sheets.
 *
 * A bit of a mislead.  This is where the ISR is going to have
 * to pump.  Alternatively, you implement what's in the comments.
 */

static const char *stateNames[] =
{
    "DAEDR_STATE_IDLE",
    "DAEDR_STATE_IN_SERVICE",
    "DAEDR_STATE_MAX_STATE"
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
DAEDR_StateName(DAEDR_States state)
{
    if (state < DAEDR_STATE_IDLE || state >= DAEDR_STATE_MAX_STATE)
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
DAEDR_Handle_RC(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->daedrInfo.curState >= DAEDR_STATE_IDLE &&
               link->daedrInfo.curState < DAEDR_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= RC_TRIGGER_MIN &&
               trigger <= RC_TRIGGER_MAX);

    switch (link->daedrInfo.curState)
    {
    case DAEDR_STATE_IDLE:
        switch (trigger)
        {
        /* Sheet 1 */
        case RC_DAEDR_TRIGGER_Start:
            /* Change state */
            link->daedrInfo.curState = DAEDR_STATE_IN_SERVICE;

            /*
             * The SDL says lots of nice stuff.  We're going to
             * ignore it, because we have hardware to do the
             * tedious bits for us.
             *
             * Oh, if you really must know:
             *
             * o Start zero deletion
             * o Start flag detection
             * o Start bit counting [Number of bits between flags]
             * o Start octet counting [output every m+7 octets and every 16]
             * o Start detection of 7 consecutive ones
             * o Start check bit control
             */
            /* Well, one trigger */
#if 0
            TXC_Main(link, DAEDT_TXC_TRIGGER_TransmissionRequest, NULL, 0);
#else
            L1_Main(link, DAEDR_L1_TRIGGER_Start, NULL, 0);
#endif
            break;
 
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case DAEDR_STATE_IN_SERVICE:
        printk("%s:%d State in Service \n",__FILE__, __LINE__);
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
 *      Handle L1 messages
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
DAEDR_Handle_L1(MTP2_LinkState *link, MTP2_Trigger trigger,
                ITS_OCTET *data, ITS_USHORT size)
{
    ITS_ASSERT(link->daedrInfo.curState >= DAEDR_STATE_IDLE &&
               link->daedrInfo.curState < DAEDR_STATE_MAX_STATE);
    ITS_ASSERT(trigger >= L1_TRIGGER_MIN &&
               trigger <= L1_TRIGGER_MAX);

    switch (link->daedrInfo.curState)
    {
    case DAEDR_STATE_IDLE:
        switch (trigger)
        {
        default:
            MTP2_DEBUG(link,
                       "Invalid trigger %d for state IDLE\n",
                        trigger);
            break;
        }
        break;

    case DAEDR_STATE_IN_SERVICE:
        switch (trigger)
        {
        /* Sheets 1 & 2.  We'll expect the hardware to inject these */
        case L1_DAEDR_TRIGGER_OctetCountingMode:
            /* Change variables */
            link->daedrInfo.octetCountingMode = ITS_TRUE;
            break;

        case L1_DAEDR_TRIGGER_16_Octets:
            /* Check variables */
            if (link->daedrInfo.octetCountingMode)
            {
                /* Send triggers */
                SUERM_Main(link, DAEDR_SUERM_TRIGGER_SUInError, NULL, 0);
                AERM_Main(link, DAEDR_AERM_TRIGGER_SUInError, NULL, 0);
            }
            /* remain in state */
            break;

        case L1_DAEDR_TRIGGER_BadCheckSum:
            /* Check variables */
            if (link->daedrInfo.octetCountingMode)
            {
                /* Send triggers */
                SUERM_Main(link, DAEDR_SUERM_TRIGGER_SUInError, NULL, 0);
                AERM_Main(link, DAEDR_AERM_TRIGGER_SUInError, NULL, 0);
            }
            /* remain in state */
            break;

        case L1_DAEDR_TRIGGER_SignalUnit:
            /* Good SU */

            /* Check variables */
            if (link->daedrInfo.octetCountingMode)
            {
                link->daedrInfo.octetCountingMode = ITS_FALSE;
            }

            /* Send triggers */
            RC_Main(link, DAEDR_RC_TRIGGER_SignalUnit, data, size);
            IAC_Main(link, DAEDR_IAC_TRIGGER_CorrectSU, NULL, 0);
            SUERM_Main(link, DAEDR_SUERM_TRIGGER_CorrectSU, NULL, 0);

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
 *      DAEDR entry point
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
DAEDR_Main(MTP2_LinkState *link, MTP2_Trigger trigger,
           ITS_OCTET *data, ITS_USHORT size)
{
#if defined(DEBUG_TRIGGERS)
    printk("DAEDR_Main: trigger %s curState %s\n",
           MTP2_TriggerToString(trigger),
           DAEDR_StateName(link->daedrInfo.curState));
#endif
    if (size && data != NULL)
    {
        printk("Got data channel %d size %d %02x %02x %02x %02x\n",
               link->linkNum, size, data[0], data[1], data[2], data[3]);
    }
    switch (trigger)
    {
    case RC_DAEDR_TRIGGER_Start:
        DAEDR_Handle_RC(link, trigger, data, size);
        break;

    case L1_DAEDR_TRIGGER_BadCheckSum:
    case L1_DAEDR_TRIGGER_OctetCountingMode:
    case L1_DAEDR_TRIGGER_16_Octets:
    case L1_DAEDR_TRIGGER_SignalUnit:
        DAEDR_Handle_L1(link, trigger, data, size);
        break;

    default:
        MTP2_DEBUG(link,
                   "Invalid trigger %d for DAEDR\n",
                    trigger);
        break;
    }
}

