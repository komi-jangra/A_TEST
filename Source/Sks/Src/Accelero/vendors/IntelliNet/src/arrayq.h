/*********************************-*-C-*-************************************
 *                                                                          *
 *     Copyright 2005 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *                  
 * CONTRACT: INTERNAL
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 ****************************************************************************/
#ident "$Id: arrayq.h,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#if !defined(_ARRAYQ_H_)
#define _ARRAYQ_H_

#include <linux/sched.h>
#include <linux/spinlock.h>

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * Queue manipulation via bitfield trickery, but done explicitly for
 * clarity.
 *
 * Usage: arrayq_init() MUST be given the size of an element INCLUDING
 * a per element header of size 'sizeof(arrayq_elem_t)'.
 * HOWEVER, the 'size' member of the arrayq_elem_t header on the struct
 * passed to arrayq_put() MUST NOT include the size of header, just
 * the size of the struct passed.
 * The 'size' member of the arrayq_elem_t header on the struct passed
 * to arrayq_get() MUST be at least as large as the maximum size of the
 * struct that follows.  It should not include the header size, just
 * like when passed to arrayq_put().
 */
typedef struct
{
    unsigned   exponent;
    unsigned   size;
    unsigned   mask;
    unsigned   put;
    unsigned   get;
    unsigned   elem_size;
    spinlock_t lock;
}
arrayq_t;

/*
 * embed this as the first member of your elements
 */
typedef struct
{
    unsigned size;
}
arrayq_elem_t;

/*
 * prototypes
 */
int arrayq_init(arrayq_t *q, unsigned exp, unsigned elem_size);
int arrayq_empty(arrayq_t *q);
int arrayq_full(arrayq_t *q);
int arrayq_put(arrayq_t *q, void *base, arrayq_elem_t *data);
int arrayq_get(arrayq_t *q, void *base, arrayq_elem_t *data);
int arrayq_peek(arrayq_t *q, void *base, void **data);
int arrayq_peek_next(arrayq_t *q, void *base, void **data);


#if defined(__cplusplus)
}
#endif

#endif /* _ARRAYQ_H_ */

