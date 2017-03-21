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
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/22 16:29:18  adutta
 * LOG: Removed printf
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:04:35  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: bssapif_socket.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_socket.cpp,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $"

#include <its.h>
#include <its++.h>
#include <its_transports.h>
#include <its_ip_trans.h>

#include <bssapif_socket.h>
#include <bssapif_trace.h>

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif

ITS_Mutex SocketCom::guard(0);
ITS_Mutex SocketCom::lock(0);

static SocketCom* ppCom = NULL;
 

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
SocketCom::SocketCom()
    : bsTransInst(ITS_NO_SRC)
{}

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
int
SocketCom::SendToSocket(its::ITS_Event& evt)
{
    ITS_USHORT trid = 0;
    ITS_HANDLE hdl = NULL;
    ITS_INT count = 0;

    BSSAPIF_TRACE_DEBUG(("SocketCom: SendToSocket"));
    
    switch (evt.GetSource())
    {
     case ITS_BSSAP_SRC:
         trid = bsTransInst;
         hdl = bsTransHandle;
         
         break;
    }

    if (!IsClientTransValid(hdl))
    {
        BSSAPIF_TRACE_ERROR(("SendToSocket: Invalid socket transport"));

        return (ITS_ESENDFAIL);
    }

    if (Transport::PutEvent(trid, evt) == ITS_SUCCESS)
    {
       return (ITS_SUCCESS);
    }

    BSSAPIF_TRACE_ERROR(("SendToSocket: Socket send failed"));

    return ITS_ESENDFAIL;
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
SocketCom* 
SocketCom::GetInstance()
{
    ITS_ASSERT(SocketCom::guard.Acquire() == ITS_SUCCESS);

    BSSAPIF_TRACE_DEBUG(("SocketCom: GetInstance"));

    if (ppCom == NULL)
    {
        ppCom = new SocketCom;
    }

    SocketCom::guard.Release();

    return ppCom;
}


