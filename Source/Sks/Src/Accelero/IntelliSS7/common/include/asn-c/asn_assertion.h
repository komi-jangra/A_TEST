/*----------------------------------------------------------------------------*
 *                                                                            *
 *      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 *----------------------------------------------------------------------------*
 *
 *  ID: $Id: asn_assertion.h,v 1.1.1.1 2007-10-08 11:11:35 bsccs2 Exp $
 *
 *----------------------------------------------------------------------------*/

#if !defined(_C_ASN_ASSERTION_H_)
#define _C_ASN_ASSERTION_H_

#include <stdio.h>
#include <its.h>

#if defined(WIN32)                                       
#include <crtdbg.h>                    
#endif /* defined(WIN32) */

#if defined(__cplusplus)
extern "C"
{
#endif /* defined(__cplusplus) */

const char* AsnStripPath(const char* str);


#if defined(DEBUG) || defined(_DEBUG)

#if defined(WIN32)

#define ASN_C_REQUIRE(assertion)                                                        \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Precondition <%s> failed | File <%s> | Line <%lu>]\n",    \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }                                                                                   \
    _ASSERTE(assertion);

#define ASN_C_ENSURE(assertion)                                                         \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Postcondition <%s> failed | File <%s> | Line <%lu>]\n",   \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }                                                                                   \
    _ASSERTE(assertion);

#define ASN_C_ASSERT(assertion)                                                         \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Assertion <%s> failed | File <%s> | Line <%lu>]\n",       \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }                                                                                   \
    _ASSERTE(assertion);

#else /* !defined(WIN32) */

#define ASN_C_REQUIRE(assertion)                                                        \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Precondition <%s> failed | File <%s> | Line <%lu>]\n",    \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }

#define ASN_C_ENSURE(assertion)                                                         \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Postcondition <%s> failed | File <%s> | Line <%lu>]\n",   \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }

#define ASN_C_ASSERT(assertion)                                                         \
    if (!(assertion))                                                                   \
    {                                                                                   \
        fprintf(                                                                        \
            stderr,                                                                     \
            "\n[ASN C Runtime Assertion <%s> failed | File <%s> | Line <%lu>]\n",       \
            #assertion,                                                                 \
            AsnStripPath(__FILE__),                                                     \
            __LINE__);                                                                  \
    }

#endif /* defined(WIN32) */

#else /* !defined(DEBUG) */

#define ASN_C_REQUIRE(assertion)

#define ASN_C_ENSURE(assertion)

#define ASN_C_ASSERT(assertion)

#endif /* defined(DEBUG) */

#if defined(__cplusplus)
}
#endif /* defined(__cplusplus) */

#endif /* !defined(_C_ASN_ASSERTION_H_) */
