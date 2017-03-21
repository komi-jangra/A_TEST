/*********************************-*-CPP-*-**********************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:04  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:02  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: bssapif_trace.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_trace.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"

#include <engine++.h>
#include <bssapif_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void EnableBSSAPIFTracing()
{
    //TraceSubSystem::GetTrace().SetSubSystemName("BSC8560");

    // Add the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().AddLevel(BSSAPIF_DEBUG, AppDebugTrace);
    TraceSubSystem::
        GetTrace().AddLevel(BSSAPIF_WARNING, AppWarningTrace);
    TraceSubSystem::
        GetTrace().AddLevel(BSSAPIF_ERROR, AppErrorTrace);
    TraceSubSystem::
        GetTrace().AddLevel(BSSAPIF_CRITICAL, AppCriticalTrace);

    //
    //  Turn on BSSSAPIF's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //
    TraceSubSystem::GetTrace().GetLevel(BSSAPIF_CRITICAL)->Enable();
    TraceSubSystem::GetTrace().GetLevel(BSSAPIF_ERROR)->Enable();
    TraceSubSystem::GetTrace().GetLevel(BSSAPIF_WARNING)->Enable();
    TraceSubSystem::GetTrace().GetLevel(BSSAPIF_DEBUG)->Enable();


}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *  
 *  Input/Output Parameters:
 *      None.
 *  
 *  Output Parameters:
 *      None.
 *  
 *  Return Value:
 *  
 *  Notes:
 *  
 *  See Also:
 ****************************************************************************/
void DisableBSCTracing()
{
    //
    //  Turn off BSSAPIF's trace levels (based on IntelliSS7 trace
    //  mechanism).
    //

    ITS_TraceSubSystem::GetTrace().GetLevel(BSSAPIF_CRITICAL)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(BSSAPIF_ERROR)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(BSSAPIF_WARNING)->Disable();
    ITS_TraceSubSystem::GetTrace().GetLevel(BSSAPIF_DEBUG)->Disable();

    // Remove the trace levels to the subsystem.
    TraceSubSystem::
        GetTrace().RemLevel(BSSAPIF_DEBUG);
    TraceSubSystem::
        GetTrace().RemLevel(BSSAPIF_WARNING);
    TraceSubSystem::
        GetTrace().RemLevel(BSSAPIF_ERROR);
    TraceSubSystem::
        GetTrace().RemLevel(BSSAPIF_CRITICAL);
}

