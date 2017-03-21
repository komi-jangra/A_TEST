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
 * LOG: $Log: bssapif_dispatcher.h,v $
 * LOG: Revision 1.1.1.1  2007/10/08 11:12:26  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/08/22 05:22:00  vnl
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:36  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:32:00  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 * LOG:
 * ID: $Id: bssapif_dispatcher.h,v 1.1.1.1 2007/10/08 11:12:26 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_dispatcher.h,v 1.1.1.1 2007/10/08 11:12:26 bsccs2 Exp $"

#ifndef BSSAPIF_DISP_H
#define BSSAPIF_DISP_H


#include <iostream>
#include <its++.h>
#include <its_thread_pool.h>
#include <engine++.h>
#include <bssap_interface.h> 

/* Added by Amaresh for BSC-BSSAP */
#define MAXLINE 80
typedef struct bss_cfg
{
    ITS_UINT lpc;
    ITS_UINT dpc;
    ITS_OCTET lssn;
    ITS_OCTET dssn;
}BSS_INFO;
/* Added by Amaresh for BSC-BSSAP */

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
    //Reading the point codes and ssn from files
    BSS_INFO Readfile(); //Added by Amaresh for BSC-BSSAP

private:

     // Process events from socket
     ITS_INT ProcessSCCPMessage(ITS_EVENT* evt); 
     ITS_INT ProcessCICMessage(ITS_EVENT* evt); 
     ITS_INT ProcessCFGMessage(ITS_EVENT* evt); 
     ITS_INT ProcessBSSAPMessage(ITS_EVENT* evt); 

     // Process events from network
     static ITS_INT ProcessNetworkDTAP(BSSDtap* api);
     static ITS_INT ProcessNetworkMAP(BSSMap* api);
		/* Added by Amaresh for HO-FAI as on dated 03-07-08 */
    static ITS_INT ProcessNetworkMAPErr(BSSMap* api);
    /* Added by Amaresh for HO-FAI as on dated 03-07-08 */
     static ITS_INT ProcessNetworkTimeout(BSSAPError* api);
     static ITS_INT ProcessNetworkProtocol(BSSAPError* api);
     static ITS_INT ProcessNetworkStaus(BSSAPError* api);
     static ITS_INT ProcessNetworkSCCPInd(BSSAP_Api* api);
 
/*
     // Process events from network
     static ITS_INT ProcessNetworkDTAP(BSSAP_Api* api);
     static ITS_INT ProcessNetworkMAP(BSSAP_Api* api);
     static ITS_INT ProcessNetworkTimeout(BSSAPError* api);
     static ITS_INT ProcessNetworkProtocol(BSSAPError* api);
     static ITS_INT ProcessNetworkStaus(BSSAPError* api);
     static ITS_INT ProcessNetworkSCCPInd(BSSAP_Api* api);

*/ //Commented by Amaresh for MSC-BSSAP
};

#endif
