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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:26  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:10  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:16  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:28  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2003/07/03 14:09:14  yranade
 * LOG: Move the base mempool implementation to CORE.
 * LOG:
 * LOG: Revision 8.1  2003/03/06 19:09:15  mmiers
 * LOG: New trace implementation (to one file by default).
 * LOG: Much faster than the original.  Fix a few bugs in hash.
 * LOG: Fix NULL pointer dereference in the license code.
 * LOG: Move mem pool to core.  Add test for new trace.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:02  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.2  2002/10/28 18:42:51  mmiers
 * LOG: Warning removal for 64 bit platforms.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:01  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/04/10 15:51:50  mmiers
 * LOG: Set the maxEntries at a reasonable value rather than
 * LOG: order based.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:24  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10  2002/02/04 20:44:25  mmiers
 * LOG: A few more adjustments.
 * LOG:
 * LOG: Revision 5.9  2002/02/04 20:19:14  mmiers
 * LOG: Fix fencepost error.
 * LOG:
 * LOG: Revision 5.8  2001/11/14 23:18:37  mmiers
 * LOG: Conformance testing fixes.
 * LOG:
 * LOG: Revision 5.7  2001/11/12 22:33:31  mmiers
 * LOG: Clean up on exit.
 * LOG:
 * LOG: Revision 5.6  2001/11/12 21:42:33  mmiers
 * LOG: Global mempool fixup
 * LOG:
 * LOG: Revision 5.5  2001/11/09 16:39:20  mmiers
 * LOG: More mempool work.
 * LOG:
 * LOG: Revision 5.4  2001/11/09 00:27:28  mmiers
 * LOG: Allocate mempool at thread startup.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 00:17:20  mmiers
 * LOG: Get the thread initialization right.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:11  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.24  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.23  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.22  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.21  2001/02/06 00:20:28  mmiers
 * LOG: Continue adding in assertions.
 * LOG:
 * LOG: Revision 3.20  2001/02/05 23:54:35  mmiers
 * LOG: Start adding in assertions
 * LOG:
 * LOG: Revision 3.19  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.18  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.17  2001/01/19 22:47:46  mmiers
 * LOG: cleanup
 * LOG:
 * LOG: Revision 3.16  2001/01/19 19:33:08  mmiers
 * LOG: Mysteries
 * LOG:
 * LOG: Revision 3.15  2001/01/18 23:50:26  mmiers
 * LOG: Ditch the list allocator, use mempool instead.
 * LOG:
 * LOG: Revision 3.14  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.13  2001/01/09 23:54:55  mmiers
 * LOG: Remove the last vestiges of the C++ basis (for VxWorks)
 * LOG:
 * LOG: Revision 3.12  2001/01/03 23:07:41  hdivoux
 * LOG: Get the modifier right
 * LOG:
 * LOG: Revision 3.11  2000/11/29 23:38:26  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 3.10  2000/11/13 19:28:30  mmiers
 * LOG: Try to recover
 * LOG:
 * LOG: Revision 3.10  2000/10/21 22:45:07  mmiers
 * LOG: Surprising results running with efence.
 * LOG:
 * LOG: Revision 3.9  2000/09/02 01:40:47  mmiers
 * LOG: Correct the last (I hope) of the heap allocator bugs.
 * LOG:
 * LOG: Revision 3.8  2000/09/01 23:31:38  lbana
 * LOG:
 * LOG:
 * LOG: Tracking down bugs.
 * LOG:
 * LOG: Revision 3.7  2000/08/24 23:06:41  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.6  2000/08/23 00:02:10  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.5  2000/08/22 18:53:29  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 3.4  2000/08/18 20:41:52  mmiers
 * LOG: Set up mempool feature, dump leaks.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 19:56:08  mmiers
 * LOG: Finish up the implementation.
 * LOG:
 * LOG: Revision 3.2  2000/08/18 02:20:13  mmiers
 * LOG: First implementation of stack MEMPOOL.  Smarten realloc needs to be
 * LOG: done.
 * LOG:
 * LOG: Revision 3.1  2000/08/17 23:27:23  mmiers
 * LOG: Add user data to list remove procs
 * LOG: Add memory pool for quick reclamation
 * LOG: Add object creation into user supplied buffer
 * LOG:
 *
 ****************************************************************************/

#include <stddef.h>
#include <stdlib.h>

#include <its.h>
#include <its_mem_pool.h>
#include <its_trace.h>
#include <its_hash.h>
#include <its_app.h>
#include <its_iniparse.h>
#include <its_assertion.h>

#ident "$Id: its_mem_pool.c,v 1.1.1.1 2007-10-08 11:11:54 bsccs2 Exp $"

#define MEMPOOL_ALLOC_OVER_MAGIC    0xfeeddea1
#define MEMPOOL_ALLOC_UNDER_MAGIC   0xfee1dead

#define MEMPOOL_FREE_OVER_MAGIC     0xdeadbeef
#define MEMPOOL_FREE_UNDER_MAGIC    0xdeadfeed

#define MAX_PRIM_ALIGN	    sizeof(ITS_DOUBLE)

#define HEAP_MIN_ORDER      3

#define MAX_ENTRIES         32

static ITS_UINT aligns[MAX_PRIM_ALIGN] =
{
    sizeof(ITS_OCTET),
    sizeof(ITS_USHORT),
    sizeof(ITS_UINT),
    sizeof(ITS_UINT),
    sizeof(ITS_DOUBLE),
    sizeof(ITS_DOUBLE),
    sizeof(ITS_DOUBLE),
    sizeof(ITS_DOUBLE)
};

static ITS_BOOLEAN  checksOn = ITS_FALSE;

#undef ITS_TRACE_DEBUG
#undef ITS_TRACE_WARNING
#undef ITS_TRACE_ERROR
#undef ITS_TRACE_CRITICAL

#define ITS_TRACE_DEBUG(x)
#define ITS_TRACE_WARNING(x)
#define ITS_TRACE_ERROR(x)
#define ITS_TRACE_CRITICAL(x)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Dump the hash table to see leaked memory.
 *
 *  Input Parameters:
 *      m - the MEMPOOL_Manager to unload.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
DumpLeaks(MEMPOOL_Manager *m)
{
    HASH_Table ht = MEMPOOL_HEAP_HASH(m);
    HASH_TableEntry he;
    int i;
    ITS_UINT numLeaks = 0;

    for (i = 0; i < HASH_NUM_ENTRIES(ht); i++)
    {
        for (he = HASH_TABLE(ht)[i]; he != NULL; he = he->next)
        {
            MEMPOOL_Chunk* ch = (MEMPOOL_Chunk *)he->data;

            ITS_TRACE_WARNING(("Memory leak: %d bytes in file %s at %d\n",
                             ch->size, ch->file, ch->line));

            numLeaks++;

            free(ch);
        }
    }

    ITS_TRACE_WARNING(("MEMPOOL: %d leaks detected\n", numLeaks));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a MEMPOOL for heap data.
 *
 *  Input Parameters:
 *      Standard object construction args.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - pool allocated.  Anything else indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
HeapObjCreate(MEMPOOL_Manager *obj, ITS_UINT powers)
{
    ITS_UINT i;

    ITS_TRACE_DEBUG(("HeapObjCreate\n"));

    /* figure out how many entries */
    if (powers <= HEAP_MIN_ORDER)
    {
        powers = HEAP_MIN_ORDER + 1;
    }

    MEMPOOL_HEAP_NUM_REGIONS(obj) = powers - HEAP_MIN_ORDER;

    /* alloc and init the regions */
    if ((MEMPOOL_VOID_HEAP_REGIONS(obj) =
            (MEMPOOL_Region *)calloc(powers - HEAP_MIN_ORDER,
                                     sizeof(MEMPOOL_Region))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    for (i = HEAP_MIN_ORDER;
         i < MEMPOOL_HEAP_NUM_REGIONS(obj) + HEAP_MIN_ORDER;
         i++)
    {
        MEMPOOL_Region *r = &MEMPOOL_HEAP_REGIONS(obj)[i - HEAP_MIN_ORDER];

        r->power = i;
        r->numEntries = 0;
        /*
         * NOTE: for a global pool I used to do
         * (1 << (powers + HEAP_MIN_ORDER - i));
         * This is not so good for a per-thread pool.  For now, let's
         * just use a single number for all orders.
         */
        r->maxEntries = MAX_ENTRIES;
        r->entries = NULL;
    }

    /* build the check hash */
    MEMPOOL_HEAP_HASH(obj) = HASH_CreateTable();
    if (MEMPOOL_HEAP_HASH(obj) == NULL)
    {
        return (ITS_ENOMEM);
    }

    MEMPOOL_HEAP_CHECK(obj) = checksOn;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a heap based mem pool.
 *
 *  Input Parameters:
 *      Standard object destruction args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
HeapObjDestroy(MEMPOOL_Manager *obj)
{
    ITS_UINT i;

    ITS_TRACE_DEBUG(("HeapObjDestroy\n"));

    if (MEMPOOL_HEAP_REGIONS(obj) == NULL)
    {
        return;
    }

    if (MEMPOOL_HEAP_CHECK((MEMPOOL_Manager *)obj))
    {
        DumpLeaks((MEMPOOL_Manager *)obj);
    }

    HASH_DeleteTable(MEMPOOL_HEAP_HASH(obj));

    for (i = HEAP_MIN_ORDER;
         i < MEMPOOL_HEAP_NUM_REGIONS(obj) + HEAP_MIN_ORDER;
         i++)
    {
        MEMPOOL_Region *r = &MEMPOOL_HEAP_REGIONS(obj)[i - HEAP_MIN_ORDER];
        MEMPOOL_Chunk *ch, *ch2;

        for (ch = r->entries; ch != NULL; ch = ch2)
        {
            ch2 = ch->next;

            free(ch);
        }
    }

    free(MEMPOOL_HEAP_REGIONS(obj));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a MEMPOOL for heap data.
 *
 *  Input Parameters:
 *      Standard object construction args.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - pool allocated.  Anything else indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
MPHeapCreate(ITS_Object obj, va_list alist)
{
    ITS_UINT powers;

    powers = va_arg(alist, ITS_UINT);

    return HeapObjCreate((MEMPOOL_Manager *)obj, powers);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a heap based mem pool.
 *
 *  Input Parameters:
 *      Standard object destruction args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
MPHeapDestroy(ITS_Object obj)
{
    HeapObjDestroy((MEMPOOL_Manager *)obj);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a MEMPOOL for heap data.
 *
 *  Input Parameters:
 *      Standard object construction args.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - pool allocated.  Anything else indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
MPLockHeapCreate(ITS_Object obj, va_list alist)
{
    ITS_UINT powers;
    int ret;

    powers = va_arg(alist, ITS_UINT);

    /* build the lock */
    if (MUTEX_CreateMutex(&MEMPOOL_HEAP_LOCK(obj), 0) != ITS_SUCCESS)
    {
        return (ITS_EBADMUTEX);
    }

    ret = HeapObjCreate((MEMPOOL_Manager *)obj, powers);

    if (ret != ITS_SUCCESS)
    {
        MUTEX_DeleteMutex(&MEMPOOL_HEAP_LOCK(obj));
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a heap based mem pool.
 *
 *  Input Parameters:
 *      Standard object destruction args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
MPLockHeapDestroy(ITS_Object obj)
{
    HeapObjDestroy((MEMPOOL_Manager *)obj);

    MUTEX_DeleteMutex(&MEMPOOL_HEAP_LOCK(obj));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapFree()
 ****************************************************************************/
static void *
LowHeapAlloc(MEMPOOL_Manager *m, ITS_UINT size)
{
    ITS_UINT comp, index, asize;
    MEMPOOL_Chunk *ch;

    ITS_TRACE_DEBUG(("LowHeapAlloc\n"));

    ITS_C_REQUIRE(m != NULL); /* you need to call GlobalStart() */

    /* find its bucket */
    index = 0;
    if (size > (1 << HEAP_MIN_ORDER))
    {
        for (comp = size; comp >= (1 << HEAP_MIN_ORDER); index++)
        {
            comp >>= 1;
        }
    }

    /* see if a chunk is waiting for reuse */
    if (index < MEMPOOL_HEAP_NUM_REGIONS(m))
    {
        MEMPOOL_Region *r = &MEMPOOL_HEAP_REGIONS(m)[index];

        ch = r->entries;

        if (ch != NULL)
        {
            /* checks? */
            if (MEMPOOL_HEAP_CHECK(m))
            {
                if (ch->overMagic != MEMPOOL_FREE_OVER_MAGIC ||
                    ch->underMagic != MEMPOOL_FREE_UNDER_MAGIC)
                {
                    ITS_TRACE_ERROR(("Corrupted node in free list!\n"));

                    abort();
                }

                if (ch->size < size)
                {
                    ITS_TRACE_ERROR(("Free node is too small! %d vs %d\n",
                                     ch->size, size));

                    abort();
                }

                /* put it in the alloc pool */
                /* note that this is TRUNCATE on 64 bit platforms!!! */
                HASH_AddEntry(MEMPOOL_HEAP_HASH(m), 0,
                              (ITS_INT)((ITS_LONG)ch), (ITS_POINTER)ch);
            }

            r->entries = ch->next;
            r->numEntries--;
            ch->size = size;
           
            if (MEMPOOL_HEAP_CHECK(m))
            {
                ch->overMagic = MEMPOOL_ALLOC_OVER_MAGIC;
                ch->next = NULL;
                ch->file = NULL;
                ch->line = 0;
                ch->underMagic = MEMPOOL_ALLOC_UNDER_MAGIC;
            }

            return (ch->data);
        }

        /* no buffer, get size */
        asize = sizeof(MEMPOOL_Chunk) + (1 << r->power);
    }
    else
    {
        /* too big, we don't track these */
        asize = sizeof(MEMPOOL_Chunk) + size;
    }

    ch = (MEMPOOL_Chunk *)malloc(asize);

    /* got some? */
    if (ch == NULL)
    {
        return (NULL);
    }

    /* fill it in */
    ch->size = size;
    if (MEMPOOL_HEAP_CHECK(m))
    {
        ch->overMagic = MEMPOOL_ALLOC_OVER_MAGIC;
        ch->next = NULL;
        ch->file = NULL;
        ch->line = 0;
        ch->underMagic = MEMPOOL_ALLOC_UNDER_MAGIC;

        /* note that this is TRUNCATE on 64 bit platforms!!! */
        HASH_AddEntry(MEMPOOL_HEAP_HASH(m), 0,
                      (ITS_INT)((ITS_LONG)ch), (ITS_POINTER)ch);
    }

    return (ch->data);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called both by MEMPOOL code and the user to return
 *      objects associated with this MEMPOOL_Manager to the manager's buffer
 *      pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapAlloc()
 ****************************************************************************/
static void
LowHeapFree(MEMPOOL_Manager *m, void *toFree)
{
    ITS_UINT comp, index;
    MEMPOOL_Chunk *ch;
    ITS_POINTER dummy;
    MEMPOOL_Region *r;

    ITS_TRACE_DEBUG(("LowHeapFree\n"));

    ITS_C_REQUIRE(m != NULL);

    if (toFree == NULL)
    {
        ITS_TRACE_ERROR(("Attempt free of NULL pointer\n"));

        return;
    }

    ch = MEMPOOL_PTR_TO_CHUNK(toFree);

    /* perform checks? */
    if (MEMPOOL_HEAP_CHECK(m))
    {
        if (ch->overMagic == MEMPOOL_FREE_OVER_MAGIC ||
            ch->underMagic == MEMPOOL_FREE_UNDER_MAGIC)
        {
            ITS_C_ASSERT(ITS_FALSE);

            ITS_TRACE_ERROR(("HeapFree: Free twice! %08x\n", toFree));

            return;
        }

        if (ch->overMagic != MEMPOOL_ALLOC_OVER_MAGIC ||
            ch->underMagic != MEMPOOL_ALLOC_UNDER_MAGIC)
        {
            ITS_C_ASSERT(ITS_FALSE);

            ITS_TRACE_ERROR(("HeapFree: Free non-pool memory! %08x\n",
                             toFree));

            return;
        }

        /* remove from free list */
        /* note that this is TRUNCATE on 64 bit platforms!!! */
        if (HASH_FindEntry(MEMPOOL_HEAP_HASH(m), 0,
                           (ITS_INT)((ITS_LONG)ch), &dummy) != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("HeapFree: Not in free list! %08x\n", ch));

            return;
        }

        /* note that this is TRUNCATE on 64 bit platforms!!! */
        HASH_DeleteEntry(MEMPOOL_HEAP_HASH(m), 0, (ITS_INT)((ITS_LONG)ch));
    }

    /* find its bucket */
    index = 0;
    if (ch->size > (1 << HEAP_MIN_ORDER))
    {
        for (comp = ch->size; comp >= (1 << HEAP_MIN_ORDER); index++)
        {
            comp >>= 1;
        }
    }

    /* if it's too big, just leave */
    if (index >= MEMPOOL_HEAP_NUM_REGIONS(m))
    {
        free(ch);

        return;
    }

    r = &MEMPOOL_HEAP_REGIONS(m)[index];

    /*
     * see if we've overflowed.
     */
    r->numEntries++;
    if (r->numEntries >= r->maxEntries)
    {
        r->numEntries--;

        free(ch);

        return;
    }

    /* otherwise put it in it's list and reset */
    if (MEMPOOL_HEAP_CHECK(m))
    {
        ch->overMagic = MEMPOOL_FREE_OVER_MAGIC;
        ch->underMagic = MEMPOOL_FREE_UNDER_MAGIC;
        /* preserve file and line because it might be interesting where
         * this was freed */
    }

    ch->size = 1 << r->power;

    ch->next = r->entries;
    r->entries = ch;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapFree()
 ****************************************************************************/
static void *
MPLowHeapAlloc(MEMPOOL_Manager *m, ITS_UINT size)
{
    return LowHeapAlloc(m, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called both by MEMPOOL code and the user to return
 *      objects associated with this MEMPOOL_Manager to the manager's buffer
 *      pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapAlloc()
 ****************************************************************************/
static void
MPLowHeapFree(MEMPOOL_Manager *m, void *toFree)
{
    LowHeapFree(m, toFree);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapFree()
 ****************************************************************************/
static void *
MPLowLockHeapAlloc(MEMPOOL_Manager *m, ITS_UINT size)
{
    void *ret;

    if (MUTEX_AcquireMutex(&MEMPOOL_HEAP_LOCK(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Can't acquire heap mutex\n"));

        return (NULL);
    }

    ret = LowHeapAlloc(m, size);

    MUTEX_ReleaseMutex(&MEMPOOL_HEAP_LOCK(m));

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called both by MEMPOOL code and the user to return
 *      objects associated with this MEMPOOL_Manager to the manager's buffer
 *      pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *      LowHeapAlloc()
 ****************************************************************************/
static void
MPLowLockHeapFree(MEMPOOL_Manager *m, void *toFree)
{
    if (MUTEX_AcquireMutex(&MEMPOOL_HEAP_LOCK(m)) != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("Can't acquire heap mutex\n"));

        return;
    }

    LowHeapFree(m, toFree);

    MUTEX_ReleaseMutex(&MEMPOOL_HEAP_LOCK(m));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to return a region in the pool of at least
 *      size bytes.  If not enough memory remains, NULL is returned.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPHeapFree()
 ****************************************************************************/
static void *
MPHeapAlloc(MEMPOOL_Manager *m, ITS_UINT size, const char *file, int line)
{
    MEMPOOL_Chunk *ch;
    void *ret;

    ITS_C_ASSERT(m != NULL);

    ret = MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, size);

    if (ret == NULL)
    {
        return (ret);
    }

    ch = MEMPOOL_PTR_TO_CHUNK(ret);

    ch->file = file;
    ch->line = line;

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to allocate (count * size) bytes in the pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      cnt = the number of size regions to allocate.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPHeapFree()
 ****************************************************************************/
static void *
MPHeapClearAlloc(MEMPOOL_Manager *m, ITS_UINT count, ITS_UINT size,
                 const char *file, int line)
{
    MEMPOOL_Chunk *ch;
    void *ret;

    ITS_C_ASSERT(m != NULL);

    if (size < MAX_PRIM_ALIGN)
    {
        size = aligns[size];
    }
    else
    {
        size = ((size + MAX_PRIM_ALIGN - 1) & ~(MAX_PRIM_ALIGN - 1));
    }

    ret = MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, size * count);

    if (ret == NULL)
    {
        return (ret);
    }

    ch = MEMPOOL_PTR_TO_CHUNK(ret);

    ch->file = file;
    ch->line = line;

    memset(ch->data, 0, size * count);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to allocate a region in the pool with the
 *      new requested size.  The amount of memory copied from the old
 *      region is the lesser of the old and new sizes.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      old - the region to reallocate
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPHeapFree()
 ****************************************************************************/
static void *
MPHeapRealloc(MEMPOOL_Manager *m, void *old, ITS_UINT newSize,
              const char *file, int line)
{
    MEMPOOL_Chunk *ch, *ch2;
    void *ret;
    ITS_UINT size;

    ITS_C_ASSERT(m != NULL);

    ch = MEMPOOL_PTR_TO_CHUNK(old);

    /* perform checks? */
    if (MEMPOOL_HEAP_CHECK(m))
    {
        if (ch->overMagic == MEMPOOL_FREE_OVER_MAGIC ||
            ch->underMagic == MEMPOOL_FREE_UNDER_MAGIC)
        {
            ITS_C_ASSERT(ITS_FALSE);

            ITS_TRACE_ERROR(("HeapRealloc: realloc of free mem! %08x\n",
                             old));

            return (NULL);
        }

        if (ch->overMagic != MEMPOOL_ALLOC_OVER_MAGIC ||
            ch->underMagic != MEMPOOL_ALLOC_UNDER_MAGIC)
        {
            ITS_C_ASSERT(ITS_FALSE);

            ITS_TRACE_ERROR(("HeapFree: realloc non-pool memory! %08x\n",
                             old));

            return (NULL);
        }
    }

    size = (ch->size < newSize) ? ch->size : newSize;

    ret = MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, newSize);

    if (ret == NULL)
    {
        return (ret);
    }

    ch2 = MEMPOOL_PTR_TO_CHUNK(ret);

    ch->file = ch2->file = file;
    ch->line = ch2->line = line;

    memcpy(ch2->data, ch->data, size);

    MEMPOOL_CLASS_LOW_FREE(ITS_OBJ_CLASS(m))(m, old);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called by the user to return objects associated
 *      with this MEMPOOL_Manager to the manager's buffer pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Users MUST use this function to return data objects to the free
 *      pool after processing.  Failure to do so will cause the pool
 *      to grow without bound.
 *
 *  See Also:
 *      Alloc()
 ****************************************************************************/
static void
MPHeapFree(MEMPOOL_Manager *m, void *toFree, const char *file, int line)
{
    MEMPOOL_Chunk *ch;

    if (toFree == NULL)
    {
        return;
    }

    /*
     * this enforces that nobody does a free() before they alloc().
     */
    ITS_C_ASSERT(m != NULL);

    ch = MEMPOOL_PTR_TO_CHUNK(toFree);

    MEMPOOL_CLASS_LOW_FREE(ITS_OBJ_CLASS(m))(m, toFree);

    /* if it's too big, don't mark it */
    if (ch->size <= (ITS_UINT)(1 << (MEMPOOL_HEAP_NUM_REGIONS(m) +
                                     HEAP_MIN_ORDER)))
    {
        ch->file = file;
        ch->line = line;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Create a "heap" allocation area around a space allocated by
 *      the user.  No attempt is made to make this thread safe, even
 *      though it is reentrant.
 *
 *  Input Parameters:
 *      Standard object construction args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - pool allocated.  Anything else indicates an error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
MPStackCreate(ITS_Object obj, va_list alist)
{
    void *pool;
    ITS_UINT size;

    ITS_TRACE_DEBUG(("StackObjCreate\n"));

    pool = va_arg(alist, void *);
    size = va_arg(alist, ITS_UINT);

    ITS_C_ASSERT(pool == obj);

    /* it's too late for the object if this assertion fails */
    ITS_C_ASSERT(pool == ITS_OBJ_ALIGN(pool));

    if (size < sizeof(MEMPOOL_Manager))
    {
        return (ITS_ENOMEM);
    }

    MEMPOOL_STACK_REGIONS(obj) = (void *)((ITS_POINTER)pool +
                                          sizeof(MEMPOOL_Manager));

    MEMPOOL_STACK_REGION_SIZE(obj) = size - sizeof(MEMPOOL_Manager);

    MEMPOOL_STACK_CUR_LOC(obj) = MEMPOOL_STACK_REGIONS(obj);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Destroy a stack based mem pool.
 *
 *  Input Parameters:
 *      Standard object destruction args
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
MPStackDestroy(ITS_Object obj)
{
    ITS_TRACE_DEBUG(("StackObjDestroy\n"));
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to allocate a region in the pool of
 *      at least size bytes.  If not enough region remains, the function
 *      will fail.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *      There is an implicit assumption that align(ITS_UINT) ==
 *      sizeof(ITS_UINT).  DEC should show if this is an unsafe assumption.
 *
 *  See Also:
 *      MPLowStackFree()
 ****************************************************************************/
static void *
MPLowStackAlloc(MEMPOOL_Manager *m, ITS_UINT size)
{
    ITS_UINT align;
    ITS_POINTER base;

    ITS_C_REQUIRE(m != NULL);

    if (size < sizeof(ITS_UINT))
    {
        align = sizeof(ITS_UINT);
    }
    else
    {
        align = MAX_PRIM_ALIGN;
    }

    /* compute the aligned pointer. */
    base = (ITS_POINTER)MEMPOOL_STACK_CUR_LOC(m) +
               (((ITS_LONG)MEMPOOL_STACK_CUR_LOC(m) + align - 1) &
                (~(align - 1)));

    /* make sure we have room to store the size of this allocation */
    if ((ITS_UINT)(base - (ITS_POINTER)MEMPOOL_STACK_CUR_LOC(m)) <
        sizeof(ITS_UINT))
    {
        base += align;
    }

    /* see if we have the room for the allocation itself */
    if ((base + size) >= ((ITS_POINTER)MEMPOOL_STACK_REGIONS(m) +
                          MEMPOOL_STACK_REGION_SIZE(m)))
    {
        return (NULL);
    }

    /* update end of allocation */
    MEMPOOL_STACK_CUR_LOC(m) = (void *)(base + size);

    /* store the size */
    *(ITS_UINT *)(base - sizeof(ITS_UINT)) = size;

    return (base);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is used to return a freed region to the pool
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      This function is a no-op.
 *
 *  See Also:
 *      MPLowStackAlloc()
 ****************************************************************************/
static void
MPLowStackFree(MEMPOOL_Manager *m, void *toFree)
{
    /* this is fast, not smart */
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to return a region in the pool of at least
 *      size bytes.  If not enough memory remains, NULL is returned.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPStackFree()
 ****************************************************************************/
static void *
MPStackAlloc(MEMPOOL_Manager *m, ITS_UINT size, const char *file, int line)
{
    return MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to allocate (count * size) bytes in the pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      cnt = the number of size regions to allocate.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPStackFree()
 ****************************************************************************/
static void *
MPStackClearAlloc(MEMPOOL_Manager *m, ITS_UINT count, ITS_UINT size,
                  const char *file, int line)
{
    void *ret;

    /* if we are allocating structs, size might not be a multiple of
     * alignment.  Force this if not true */
    if (size < MAX_PRIM_ALIGN)
    {
        size = aligns[size];
    }
    else
    {
        size = ((size + MAX_PRIM_ALIGN - 1) & ~(MAX_PRIM_ALIGN - 1));
    }

    ret = MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, count * size);

    /* if we got the region, clear it */
    if (ret)
    {
        memset(ret, 0, count * size);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to allocate a region in the pool with the
 *      new requested size.  The amount of memory copied from the old
 *      region is the lesser of the old and new sizes.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      old - the region to reallocate
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *
 *  See Also:
 *      MPStackFree()
 ****************************************************************************/
static void *
MPStackRealloc(MEMPOOL_Manager *m, void *old, ITS_UINT newSize,
               const char *file, int line)
{
    ITS_UINT osize, csize;
    void *ret;

    osize = *(ITS_UINT *)((ITS_POINTER)old - sizeof(ITS_UINT));

    /* FIXME: are we reallocating that last alloc?  If so, see if we can
     * grow/shrink.  Right now, we just blindly allocate. */
    csize = (osize < newSize) ? osize : newSize;

    ret = MEMPOOL_CLASS_LOW_ALLOC(ITS_OBJ_CLASS(m))(m, newSize);

    if (ret)
    {
        /* clear extra bytes, as needed */
        if (newSize > osize)
        {
            memset(&((ITS_POINTER)ret)[osize], 0, newSize - osize);
        }

        memcpy(ret, old, csize);
    }

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function is called by the user to return objects associated
 *      with this MEMPOOL_Manager to the manager's buffer pool.
 *
 *  Input Parameters:
 *      m - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Users MUST use this function to return data objects to the free
 *      pool after processing.  Failure to do so will cause the pool
 *      to grow without bound.
 *
 *  See Also:
 *      Alloc()
 ****************************************************************************/
static void
MPStackFree(MEMPOOL_Manager *m, void *toFree, const char *file, int line)
{
    MEMPOOL_CLASS_LOW_FREE(ITS_OBJ_CLASS(m))(m, toFree);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassPartInitialize(ITS_Class objClass)
{
    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassPartDestroy(ITS_Class objClass)
{
    return;
}

/*
 * heap class record
 */
ITSDLLAPI MEMPOOL_ClassRec itsHEAPPOOL_ClassRec =
{
    /* core */
    {
        &itsCORE_ClassRec,
        sizeof(MEMPOOL_Manager),
        ITS_FALSE,
        0,
        MEMPOOL_HEAP_CLASS_NAME,
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ClassPartInitialize,
        ClassPartDestroy,
        MPHeapCreate,
        MPHeapDestroy,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    },
    /* mempool */
    {
        MPLowHeapAlloc,
        MPLowHeapFree,
        MPHeapAlloc,
        MPHeapClearAlloc,
        MPHeapRealloc,
        MPHeapFree
    }
};

ITSDLLAPI ITS_Class itsHEAPPOOL_Class = (ITS_Class)&itsHEAPPOOL_ClassRec;

/*
 * lock heap class record
 */
ITSDLLAPI MEMPOOL_ClassRec itsLOCKHEAPPOOL_ClassRec =
{
    /* core */
    {
        &itsCORE_ClassRec,
        sizeof(MEMPOOL_Manager),
        ITS_FALSE,
        0,
        MEMPOOL_HEAP_CLASS_NAME,
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ClassPartInitialize,
        ClassPartDestroy,
        MPLockHeapCreate,
        MPLockHeapDestroy,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    },
    /* mempool */
    {
        MPLowLockHeapAlloc,
        MPLowLockHeapFree,
        MPHeapAlloc,
        MPHeapClearAlloc,
        MPHeapRealloc,
        MPHeapFree
    }
};

ITSDLLAPI ITS_Class itsLOCKHEAPPOOL_Class = (ITS_Class)&itsLOCKHEAPPOOL_ClassRec;
/*
 * stack class record.
 */
ITSDLLAPI MEMPOOL_ClassRec itsSTACKPOOL_ClassRec =
{
    /* core */
    {
        &itsCORE_ClassRec,
        sizeof(MEMPOOL_Manager),
        ITS_FALSE,
        0,
        MEMPOOL_STACK_CLASS_NAME,
        ITS_CLASS_NO_INIT,
        ITS_CLASS_NO_DEST,
        ClassPartInitialize,
        ClassPartDestroy,
        MPStackCreate,
        MPStackDestroy,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    },
    /* mempool */
    {
        MPLowStackAlloc,
        MPLowStackFree,
        MPStackAlloc,
        MPStackClearAlloc,
        MPStackRealloc,
        MPStackFree
    }
};

ITSDLLAPI ITS_Class itsSTACKPOOL_Class = (ITS_Class)&itsSTACKPOOL_ClassRec;

#undef MEMPOOL_CreateStackPool
#undef MEMPOOL_CreateHeapPool
#undef MEMPOOL_DestroyPool
#undef MEMPOOL_Alloc
#undef MEMPOOL_ClearAlloc
#undef MEMPOOL_Realloc
#undef MEMPOOL_Free

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI MEMPOOL_Manager *
MEMPOOL_CreateHeapPool(ITS_UINT powers)
{
    return (MEMPOOL_Manager *)ITS_ConstructObject(itsHEAPPOOL_Class,
                                                  powers, NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI MEMPOOL_Manager *
MEMPOOL_CreateStackPool(void *pool, ITS_UINT psize)
{
    return (MEMPOOL_Manager *)ITS_ConstructObjectIn(pool, itsHEAPPOOL_Class,
                                                    pool, psize, NULL);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI void
MEMPOOL_DestroyPool(MEMPOOL_Manager *m)
{
    ITS_DestructObject((ITS_Object)m);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      lm - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *      When a user removes an entry from the list (via, Remove(),
 *      RemHead(), or RemTail()), the data object returned by
 *      the removal function must be returned to the MEMPOOL when the user
 *      has completed processing of that item.  The item is returned to
 *      the MEMPOOL via Free().
 *
 *  See Also:
 *      Free()
 ****************************************************************************/
ITSDLLAPI void *
MEMPOOL_Alloc(MEMPOOL_Manager *m, ITS_UINT size)
{
    return MEMPOOL_CLASS_MALLOC(ITS_OBJ_CLASS(m))(m, size,
                                                  __FILE__, __LINE__);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      lm - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *      When a user removes an entry from the list (via, Remove(),
 *      RemHead(), or RemTail()), the data object returned by
 *      the removal function must be returned to the MEMPOOL when the user
 *      has completed processing of that item.  The item is returned to
 *      the MEMPOOL via Free().
 *
 *  See Also:
 *      Free()
 ****************************************************************************/
ITSDLLAPI void *
MEMPOOL_ClearAlloc(MEMPOOL_Manager *m, ITS_UINT count, ITS_UINT size)
{
    return MEMPOOL_CLASS_CALLOC(ITS_OBJ_CLASS(m))(m, count, size,
                                                  __FILE__, __LINE__);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function attempts to find an entry in the buffer pool associated
 *      with this MEMPOOL_Manager that is at least large enough to satisfy
 *      the requested allocation size.  If no such object is found, a new
 *      entry is malloc'ed and returned.  When the created object is no
 *      longer in use, it is added to the buffer pool.  In this way, the
 *      pool *can* grow forever, but in practice does not, as entries are
 *      returned to the free pool (BY THE USER) after they are handled.
 *
 *  Input Parameters:
 *      lm - a pointer to the MEMPOOL_Manager associated with this allocation.
 *      size = the requested size of the allocation.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      returns a pointer to the object that was a) either on the free list,
 *          or b) was allocated.
 *      On error, this function returns NULL.
 *
 *  Notes:
 *      When a user removes an entry from the list (via, Remove(),
 *      RemHead(), or RemTail()), the data object returned by
 *      the removal function must be returned to the MEMPOOL when the user
 *      has completed processing of that item.  The item is returned to
 *      the MEMPOOL via Free().
 *
 *  See Also:
 *      Free()
 ****************************************************************************/
ITSDLLAPI void *
MEMPOOL_Realloc(MEMPOOL_Manager *m, void *old, ITS_UINT newSize)
{
    return MEMPOOL_CLASS_REALLOC(ITS_OBJ_CLASS(m))(m, old, newSize,
                                                   __FILE__, __LINE__);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function is called both by MEMPOOL code and the user to return
 *      objects associated with this MEMPOOL_Manager to the manager's buffer
 *      pool.
 *
 *  Input Parameters:
 *      lm - a pointer to the MEMPOOL_Manager from which this data object
 *          came.
 *      data - a pointer to the data object to be returned to the free pool.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *      Users MUST use this function to return data objects to the free
 *      pool after processing.  Failure to do so will cause the pool
 *      to grow without bound.
 *
 *  See Also:
 *      Alloc()
 ****************************************************************************/
ITSDLLAPI void
MEMPOOL_Free(MEMPOOL_Manager *m, void *toFree)
{
    MEMPOOL_CLASS_FREE(ITS_OBJ_CLASS(m))(m, toFree,
                                         __FILE__, __LINE__);
}

/*
 * support's pool
 */
ITSDLLAPI MEMPOOL_Manager *MEMPOOL_Pool = NULL;

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static int
ClassInitialize(ITS_Class objClass)
{
    RESFILE_Manager *globalRes = NULL;
    static char value[ITS_PATH_MAX];
    const char *name = APPL_GetConfigFileName();

    /*
     * and a locking pool for non-participating threads
     */
    if ((MEMPOOL_Pool = MEMPOOL_CreateLockHeapPool(MEMPOOL_POWERS_DEFAULT)) ==
        NULL)
    {
        return (ITS_ENOMEM);
    }

    globalRes = RESFILE_CreateResourceManager(name);

    if (globalRes)
    {
        if (RESFILE_GetKeyValueOf(globalRes, NULL,
                                  MEM_POOL_CHECKS_ON_STRING,
                                  value, ITS_PATH_MAX) == ITS_SUCCESS)
        {
            checksOn = strstr(value, "yes") != NULL ||
                        strstr(value, "YES") != NULL;
        }
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
ClassDestroy(ITS_Class objClass)
{
    /*
     * destroy the locking pool
     */
    MEMPOOL_DestroyPool(MEMPOOL_Pool);
}

/*
 * stack class record.
 */
ITSDLLAPI ITS_ClassRec itsMEMPOOLS_ClassRec =
{
    {
        &itsCORE_ClassRec,
        sizeof(MEMPOOL_Manager),
        ITS_FALSE,
        0,
        MEMPOOL_STACK_CLASS_NAME,
        ClassInitialize,
        ClassDestroy,
        ITS_CLASS_PART_NO_INIT,
        ITS_CLASS_PART_NO_DEST,
        ITS_INST_NO_CONST,
        ITS_INST_NO_DEST,
        ITS_INST_CLONE_INHERIT,
        ITS_INST_PRINT_INHERIT,
        ITS_INST_SERIAL_INHERIT,
        ITS_INST_EQUALS_INHERIT,
        ITS_INST_HASH_INHERIT,
        NULL
    }
};

ITSDLLAPI ITS_Class itsMEMPOOLS_Class = &itsMEMPOOLS_ClassRec;
