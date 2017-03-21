/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: bssap_dtap.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.5  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/26 20:20:16  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/26 06:53:47  adutta
 * LOG: Mutex lock
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 20:09:28  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_DTAP_H_
#define  _BSSAP_DTAP_H_

#include <BSSAP++.h>
#include <bssap_call.h>
#include <bssap_interface.h>



/*.interface:BSSAP_Dtap
 *****************************************************************************
 *  Interface:
 *      BSSAP_Dtap
 *
 *  Purpose:
 *
 *
 *
 *
 *
 *  Usage:
 *
 *****************************************************************************/
class BSSAP_Dtap
{
public:
     void Initialize();
     ITS_INT ProcessInDTAPMessage(BSSAP_Call* call);
     ITS_INT ProcessOutDTAPMessage(BSSAP_Payload* msg);
     ITS_INT ProcessOutL3Message(BSSAP_Call* call);

private:
     
     ITS_INT HandleInCCMessage(BSSAP_Call* call);
     ITS_INT HandleOutCCMessage(BSSAP_Call* call);
     ITS_INT MOSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT MTSanityCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT DirectionCheck(ITS_OCTET evId, ITS_BOOLEAN up);
     ITS_INT ProcessDTAPProcedures(BSSAP_Call* call, ITS_OCTET mType,
                                                        ITS_BOOLEAN toApp);

private:
     static its::Mutex* mutex;
};


#endif
