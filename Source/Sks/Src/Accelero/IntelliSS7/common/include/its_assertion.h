/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:56  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:36  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:47  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:50:44  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2  2003/01/06 19:52:55  mmiers
 * LOG: Result of the Tandem port.  Things actually get simpler.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:35  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:12  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:55  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.7  2001/04/24 23:13:38  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 3.6  2001/03/29 18:21:15  mmiers
 * LOG: Debugging the engine.  Runs now.
 * LOG:
 * LOG: Revision 3.5  2001/03/08 23:18:29  mmiers
 * LOG: DLL-ize CORE.  Start doing this for DISPATCH, but this is going to
 * LOG: get interesting because the DLL won't be built until we have an
 * LOG: application.
 * LOG:
 * LOG: Revision 3.4  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.3  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.2  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:03:09  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 1.2  2000/05/11 02:06:12  mmiers
 * LOG:
 * LOG:
 * LOG: tools: warning removal.  Hubert needs to take over for the comps.
 * LOG: common: updates for KASOCK_TRANS.  Set up links for IMAL. TALI
 * LOG: needs more work (TALI message formats).  IMAL is ok from SUPPORT
 * LOG: perspective, but IMAL class needs implementation.
 * LOG: config.vars: correct platform flags for Linux.
 * LOG:
 * LOG: Revision 1.1  2000/05/01 19:33:05  hdivoux
 * LOG: Creation.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_ASSERTION_H_
#define _ITS_ASSERTION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(WIN32)
#include <crtdbg.h>
#endif /* defined(WIN32) */

#include <its.h>

#ident "$Id: its_assertion.h,v 1.1.1.1 2007-10-08 11:11:31 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */


/*
 *  Strip path function declaration.
 */

ITSDLLAPI const char* ITS_StripPath(const char* str);



#if defined(DEBUG) || defined(_DEBUG)

#define ITS_C_PRECONDITION_PRINT(assertion)                                   \
    fprintf(stderr, "\n[ITS Precondition <%s> failed | "                      \
                    "File <%s> | Line <%u>]\n",                               \
            #assertion,                                                       \
            ITS_StripPath(__FILE__),                                          \
            __LINE__);

#define ITS_C_POSTCONDITION_PRINT(assertion)                                  \
    fprintf(stderr, "\n[ITS Postcondition <%s> failed | "                     \
                    "File <%s> | Line <%u>]\n",                               \
            #assertion,                                                       \
            ITS_StripPath(__FILE__),                                          \
            __LINE__);

#define ITS_C_INVARIANT_PRINT(assertion)                                      \
    fprintf(stderr, "\n[ITS Invariant <%s> failed | "                         \
                    "File <%s> | Line <%u>]\n",                               \
            #assertion,                                                       \
            ITS_StripPath(__FILE__),                                          \
            __LINE__);

#define ITS_C_ASSERT_PRINT(assertion)                                         \
    fprintf(stderr, "\n[ITS Assertion <%s> failed | "                         \
                    "File <%s> | Line <%u>]\n",                               \
            #assertion,                                                       \
            ITS_StripPath(__FILE__),                                          \
            __LINE__);


#if defined(WIN32)

#define ITS_C_REQUIRE(assertion)                                              \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_PRECONDITION_PRINT(assertion);                                  \
    }                                                                         \
    _ASSERTE(assertion);

#define ITS_C_ENSURE(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_POSTCONDITION_PRINT(assertion);                                 \
    }                                                                         \
    _ASSERTE(assertion);

#define ITS_C_INVARIANT(assertion)                                            \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_INVARIANT_PRINT(assertion);                                     \
    }                                                                         \
    _ASSERTE(assertion);

#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
    }                                                                         \
    _ASSERTE(assertion);

#else /* !defined(WIN32) */

#define ITS_C_REQUIRE(assertion)                                              \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_PRECONDITION_PRINT(assertion);                                  \
        abort();                                                              \
    }

#define ITS_C_ENSURE(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_POSTCONDITION_PRINT(assertion);                                 \
        abort();                                                              \
    }

#define ITS_C_INVARIANT(assertion)                                            \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_INVARIANT_PRINT(assertion);                                     \
        abort();                                                              \
    }

#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
        abort();                                                              \
    }

#endif /* defined(WIN32) */

#else /* !(defined(DEBUG) || defined(_DEBUG)) */

#define ITS_C_PRECONDITION_PRINT(assertion)

#define ITS_C_POSTCONDITION_PRINT(assertion)

#define ITS_C_INVARIANT_PRINT(assertion)

#define ITS_C_ASSERT_PRINT(assertion)

#define ITS_C_REQUIRE(assertion)                                              \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_PRECONDITION_PRINT(assertion);                                  \
        abort();                                                              \
    }

#define ITS_C_ENSURE(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_POSTCONDITION_PRINT(assertion);                                 \
        abort();                                                              \
    }

#define ITS_C_INVARIANT(assertion)                                            \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_INVARIANT_PRINT(assertion);                                     \
        abort();                                                              \
    }

#define ITS_C_ASSERT(assertion)                                               \
    if (!(assertion))                                                         \
    {                                                                         \
        ITS_C_ASSERT_PRINT(assertion);                                        \
        abort();                                                              \
    }

#endif /* defined(DEBUG) || defined(_DEBUG) */


#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */


#endif /* !defined(_ITS_ASSERTION_H_) */
