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
 * LOG: Revision 1.1.2.2  2005/09/19 20:52:38  lbana
 * LOG: init element size.
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 16:12:14  lbana
 * LOG: First revision of compiled code from Mitch for MTP2 and IntelliNet
 * LOG: MTP2 vframe implementation.
 * LOG:
 *
 ****************************************************************************/
#ident "$Id: arrayq.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $"

#include "arrayq.h"

#include <linux/kernel.h>
#include <linux/errno.h>
#include <asm/string.h>

#include <its.h>

int
arrayq_init(arrayq_t *q, unsigned exp, unsigned elem_size)
{
    /* disallow queues with 1, 2, or more than 32K entries */
    if (exp == 0 || exp == 1 || exp > 15)
    {
        return 0;
    }

    q->exponent = exp;
    q->size = 1 << exp;
    q->mask = q->size - 1;
    q->elem_size = elem_size;

    q->put = 0;
    q->get = 0;

    spin_lock_init(&q->lock);

    return 1;
}

int
arrayq_empty(arrayq_t *q)
{
    /* simple predicate */
    return (q->get == q->put);
}

int
arrayq_full(arrayq_t *q)
{
    return (((q->put + 1) & q->mask) == q->get);
}

int
arrayq_put(arrayq_t *q, void *base, arrayq_elem_t *data)
{
    spin_lock(&q->lock);

    if (arrayq_full(q))
    {
        spin_unlock(&q->lock);

        return 0;
    }

    if ((data->size + sizeof(arrayq_elem_t)) > q->elem_size)
    {
        spin_unlock(&q->lock);

        return 0;
    }

    memcpy(base + q->put * q->elem_size,
           data,
           data->size + sizeof(arrayq_elem_t));
    q->put++;
    q->put &= q->mask;

    spin_unlock(&q->lock);

    return 1;
}

int
arrayq_get(arrayq_t *q, void *base, arrayq_elem_t *data)
{
    arrayq_elem_t *ent;

    spin_lock(&q->lock);

    if (arrayq_empty(q))
    {
        spin_unlock(&q->lock);

        return 0;
    }

    ent = base + q->get * q->elem_size;
    if (ent->size > data->size)
    {
        spin_unlock(&q->lock);

        return 0;
    }

    memcpy(data,
           ent,
           ent->size + sizeof(arrayq_elem_t));
    q->get++;
    q->get &= q->mask;

    spin_unlock(&q->lock);

    return 1;
}

int
arrayq_peek(arrayq_t *q, void *base, void **data)
{
    spin_lock(&q->lock);

    if (arrayq_empty(q))
    {
        spin_unlock(&q->lock);

        return 0;
    }

    *data = base + q->get * q->elem_size;

    spin_unlock(&q->lock);

    return 1;
}

int
arrayq_peek_next(arrayq_t *q, void *base, void **data)
{
    unsigned where;

    spin_lock(&q->lock);

    if (arrayq_empty(q))
    {
        spin_unlock(&q->lock);

        return 0;
    }

    where = (*data - base) / q->elem_size;
    where = (where + 1) & q->mask;
    if (where == q->put)
    {
        spin_unlock(&q->lock);

        return 0;
    }

    *data = base + where * q->elem_size;

    spin_unlock(&q->lock);

    return 1;
}

#ifdef ARRAYQ_TEST

int
main(int argc, char **argv)
{
    int i;
    struct queue q;
    unsigned val;

    queueInit(&q);

    for (i = 0; i < 9; i++)
    {
        val = (unsigned)i;
        if (!queuePut(&q, val))
            printf("qput failed: %d\n", i);
    }

    for (i = 0; i < 9; i++)
    {
        if (!queueGet(&q, &val))
            printf("qget failed: %d\n", i);
    }

    for (i = 0; i < 6; i++)
    {
        val = (unsigned)i;
        if (!queuePut(&q, val))
            printf("qput failed: %d\n", i);
    }

    for (i = 0; i < 7; i++)
    {
        if (!queueGet(&q, &val))
            printf("qget failed: %d\n", i);
    }

    for (i = 0; i < 9; i++)
    {
        val = (unsigned)i;
        if (!queuePut(&q, val))
            printf("qput failed: %d\n", i);
    }

    return 0;
}

#endif

