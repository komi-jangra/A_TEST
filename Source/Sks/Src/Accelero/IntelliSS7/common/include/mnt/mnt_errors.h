///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     //
//             Manufactured in the United States of America.                 //
//       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
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
// CONTRACT: INTERNAL                                                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:08  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:48:59  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:13:55  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:52:56  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:51:02  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:09:43  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:14  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:45:59  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 1.4  2001/08/15 22:33:37  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.3  2001/08/08 20:37:07  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.2  2001/08/07 21:52:41  hdivoux
// LOG: Improvements.
// LOG:
// LOG: Revision 1.1  2001/08/03 23:07:15  hdivoux
// LOG: Creation.
// LOG:
//
///////////////////////////////////////////////////////////////////////////////

#ident "$Id: mnt_errors.h,v 1.1.1.1 2007-10-08 11:11:38 bsccs2 Exp $"

//
//
// mnt_errors.h: MNT errors.
//
//


#if !defined(_MNT_ERRORS_H_)
#define _MNT_ERRORS_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <its++.h>

#include <mnt.h>


#if defined(ITS_NAMESPACE)
namespace mnt
{
#endif // defined(ITS_NAMESPACE)


enum MntErrorType {

    MNT_E_PARSE_SYNTAX_ERROR                = -1,
    MNT_E_INVALID_OPERATION_ERROR           = -2,
    MNT_E_INVALID_COMMAND_ERROR             = -3,
    MNT_E_INVALID_NB_OF_ARGS_ERROR          = -4,
    MNT_E_INVALID_ARG_TYPE_ERROR            = -5,
    MNT_E_INVALID_RET_VAL_TYPE_ERROR        = -6,
    MNT_E_INVALID_VAR_NAME_ERROR            = -7,
    MNT_E_INVALID_EXPR_TYPE_ERROR           = -8,
    MNT_E_INVALID_OUT_ARG_ERROR             = -9,
    MNT_E_INVALID_ARRAY_VAR_ERROR           = -10,
    MNT_E_INVALID_ARRAY_VAR_NAME_ERROR      = -11,
    MNT_E_INVALID_ARRAY_INDEX_TYPE_ERROR    = -12,
    MNT_E_INVALID_ARRAY_INDEX_VALUE_ERROR   = -13,
    MNT_E_INVALID_VAR_TYPE_ERROR            = -14
};


std::string MntErrorGetText(MntErrorType error);


#if defined(ITS_NAMESPACE)
}
#endif // defined(ITS_NAMESPACE)

#endif // !defined(_MNT_ERRORS_H_)
