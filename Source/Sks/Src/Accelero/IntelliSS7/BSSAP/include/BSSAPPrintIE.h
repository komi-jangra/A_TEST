/****************************************************************************
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
 *  ID: $Id: BSSAPPrintIE.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:39  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:51:06  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:49:12  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:08:34  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/06/10 16:57:36  ngoel
 * LOG: DTAP merge
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/15 20:49:18  ngoel
 * LOG: after merge with MM
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/09 15:06:02  ngoel
 * LOG: dd print headers
 * LOG:
 * LOG: Revision 6.1.4.1  2002/04/24 22:20:54  hxing
 * LOG: Back port to PR5.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:18  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.3  2001/11/26 15:19:45  dzhang
 * LOG: add DumpIEBSS()
 * LOG:
 * LOG: Revision 1.2  2001/11/12 14:42:52  dzhang
 * LOG: update to latest spec version8.9.0
 * LOG:
 * LOG: Revision 1.1  2001/10/02 21:51:58  dzhang
 * LOG: Initially check in after unit test
 * LOG:
 *
 ****************************************************************************/

#ifndef _BSSAPPRINTIE_H_
#define _BSSAPPRINTIE_H_

#include <string>

#include <BSSAP++.h>

#if defined(ITS_NAMESPACE)
namespace its
{
#endif

// prototypes for helper function
std::string OctetToHex(ITS_OCTET);
std::string UshortToHex(ITS_USHORT);
std::string UintToHex(ITS_UINT);

// prototypes for print BSSAP IEs
void DumpIE(ITS_OCTET, const BSSAP_Element*);
void DumpCCIE(ITS_OCTET, const BSSAP_Element*);
void DumpIEMM(ITS_OCTET, const BSSAP_Element*);

void DumpCellID(ITS_OCTET, BSSAP_CellIDType);
void DumpCellIDList(ITS_OCTET, BSSAP_CellIDT);
void DumpNetID(ITS_OCTET, BSSAP_NetID);
void DumpIEBSS(ITS_OCTET, const BSSAP_Element*);

#if defined(ITS_NAMESPACE)
}
#endif

#endif  // !_BSSAPPRINT_H_
