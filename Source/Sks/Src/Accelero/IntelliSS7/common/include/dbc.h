////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1999 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:00  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:35  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:46  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:50:43  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:04  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:12  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
// LOG: Convert RCSID to ident.
// LOG:
// LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
// LOG: Move log back (more complaints than applause).
// LOG: Make C service take event log.
// LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
// LOG: bindings).
// LOG:
// LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
// LOG: Demo log at bottom of file.
// LOG:
// LOG: Revision 3.1  2000/08/16 00:03:07  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:25:28  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.2  1999/07/09 23:39:56  hdivoux
// LOG: General update for improved version.
// LOG:
// LOG: Revision 1.1  1998/11/17 17:44:25  mmiers
// LOG: Move DBC into common to sanitize the build.
// LOG:
// LOG: Revision 1.2  1998/11/05 21:20:50  mmiers
// LOG: Portability build.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////

//
// Shared info between DBC server and client (i.e. DBC protocol).
//

#if !defined(_DBC_H_)
#define _DBC_H_

#ident "$Id: dbc.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

// Namespaces.

#if defined(ITS_NAMESPACE)
namespace its
{
#endif    // defined(ITS_NAMESPACE)


enum {
    DBC_MORE_EVT,
    DBC_LAST_EVT,
    DBC_QUIT_EVT,
    DBC_HELP_EVT
};



#if defined(ITS_NAMESPACE)
}
#endif    // defined(ITS_NAMESPACE)

#endif  // !defined(_DBC_H_)
