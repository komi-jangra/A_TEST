///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//            Copyright 1999 - 2002 IntelliNet Technologies, Inc.            //
//                          All Rights Reserved.                             //
//              Manufactured in the United States of America.                //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       //
//                                                                           //
//   This product and related documentation is protected by copyright and    //
//   distributed under licenses restricting its use, copying, distribution   //
//   and decompilation.  No part of this product or related documentation    //
//   may be reproduced in any form by any means without prior written        //
//   authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                           //
//   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//   government is subject to restrictions as set forth in subparagraph      //
//   (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//   clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//                                                                           //
// Contract: Internal                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:42  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:20  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:53  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:15  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:01  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:18  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:35  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2002/01/02 23:22:37  hdivoux
// LOG: Update related to XER support.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(_ASNCC_UTIL_H_)
#define _ASNCC_UTIL_H_

#ident "$Id: asncc_util.h,v 1.1.1.1 2007-10-08 11:12:07 bsccs2 Exp $"

#include <asncc.h>

std::string StripPath(const std::string& fileName);

std::string LongToString(long l);

std::string IntToString(int i);

std::string AutoIndent(const std::string& str);

std::string AdaptName(const std::string& str);

std::string AdaptNameToUppercase(const std::string& str);

std::string AdaptNameToLowercase(const std::string& str);

std::string AdaptModuleName(const std::string& str);

void CreateDirectory(const std::string& directoryName);

void WriteTextToFile(
                const std::string& directoryName,
                const std::string& fileNameCore,
                const std::string& fileNameExtension,
                const std::string& text);

#if !defined(HPUX)
std::ostream& operator<<(std::ostream& os, const std::string& str);
#endif

#endif // !defined(_ASNCC_UTIL_H_)
