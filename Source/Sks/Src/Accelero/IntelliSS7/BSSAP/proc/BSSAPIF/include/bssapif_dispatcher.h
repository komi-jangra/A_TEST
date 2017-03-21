/*********************************-*-C-*-************************************
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
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 * LOG:
 * ID: $Id: bssapif_dispatcher.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_dispatcher.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $"

#ifndef BSSAPIF_DISP_H
#define BSSAPIF_DISP_H


#include <iostream>
#include <its++.h>
#include <its_thread_pool.h>
#include <engine++.h>
#include <bssap_msc-interface.h>

/*.Interface: BSSAPDispatcher
 *****************************************************************************
 *  Interface:
 *      BSSAPDispatcher Class
 *
 *  Purpose:
 *      Implement the BSSAP Message processing functionality
 *****************************************************************************/
class BSSAPDispatcher
{
public:

    static ITS_INT ProcessNetworkEvent(its::ITS_Event& evt);
    ITS_INT ProcessSocketEvent(its::ITS_Event* evt);

private:

     // Process events from socket
     ITS_INT ProcessSCCPMessage(ITS_EVENT* evt); 
     ITS_INT ProcessCICMessage(ITS_EVENT* evt); 
     ITS_INT ProcessCFGMessage(ITS_EVENT* evt); 
     ITS_INT ProcessBSSAPMessage(ITS_EVENT* evt); 

     // Process events from network
     static ITS_INT ProcessNetworkDTAP(BSSAP_Api* api);
     static ITS_INT ProcessNetworkMAP(BSSAP_Api* api);
     static ITS_INT ProcessNetworkTimeout(BSSAPError* api);
     static ITS_INT ProcessNetworkProtocol(BSSAPError* api);
     static ITS_INT ProcessNetworkStaus(BSSAPError* api);
     static ITS_INT ProcessNetworkSCCPInd(BSSAP_Api* api);
};

#endif
