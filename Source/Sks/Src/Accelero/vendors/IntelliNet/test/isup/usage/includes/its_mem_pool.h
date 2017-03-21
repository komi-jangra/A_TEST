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
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.5  2001/11/12 21:42:33  mmiers
 * LOG: Global mempool fixup
 * LOG:
 * LOG: Revision 5.4  2001/11/12 01:00:44  mmiers
 * LOG: Use the global mempool if its not one of our threads
 * LOG:
 * LOG: Revision 5.3  2001/11/08 23:11:03  mmiers
 * LOG: C++ needs a little help with forwards.
 * LOG:
 * LOG: Revision 5.2  2001/11/08 20:47:38  mmiers
 * LOG: A better performing mem pool implementation.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:56  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:13  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.17  2001/04/05 18:44:53  mmiers
 * LOG: Debugging.
 * LOG:
 * LOG: Revision 3.16  2001/04/04 22:01:31  mmiers
 * LOG: Finish debugging.
 * LOG:
 * LOG: Revision 3.15  2001/03/09 18:33:24  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 3.14  2001/03/06 23:54:43  mmiers
 * LOG: Shrink comment blocks for readability.
 * LOG:
 * LOG: Revision 3.13  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.12  2001/02/05 22:05:01  mmiers
 * LOG: Move log back (more complaints than applause).
 * LOG: Make C service take event log.
 * LOG: Rename C++ classes to remove the prefix (its_bc.h provides old
 * LOG: bindings).
 * LOG:
 * LOG: Revision 3.11  2001/01/30 18:11:33  mmiers
 * LOG: Demo log at bottom of file.
 * LOG:
 * LOG: Revision 3.10  2001/01/18 23:19:23  mmiers
 * LOG: Profiling
 * LOG:
 * LOG: Revision 3.9  2001/01/04 16:13:48  hdivoux
 * LOG: constness correction
 * LOG:
 * LOG: Revision 3.8  2001/01/03 23:07:41  hdivoux
 * LOG: Get the modifier right
 * LOG:
 * LOG: Revision 3.7  2000/11/29 23:38:26  mmiers
 * LOG: Portability fixes.
 * LOG:
 * LOG: Revision 3.6  2000/08/24 23:06:36  mmiers
 * LOG:
 * LOG: Zero copy is in.  So is FASTCALL.  Also a bug fix to core.
 * LOG:
 * LOG: Revision 3.5  2000/08/23 00:02:09  mmiers
 * LOG:
 * LOG: Get the fastcall macros working.
 * LOG:
 * LOG: Revision 3.4  2000/08/22 18:53:28  mmiers
 * LOG: Track down the KDD problem.  The MEMPOOL is really finding some tricky
 * LOG: bugs.
 * LOG:
 * LOG: Revision 3.3  2000/08/18 19:56:08  mmiers
 * LOG: Finish up the implementation.
 * LOG:
 * LOG: Revision 3.2  2000/08/18 02:20:13  mmiers
 * LOG: First implementation of stack MEMPOOL.  Smarten realloc needs to be
 * LOG: done.
 * LOG:
 * LOG: Revision 3.1  2000/08/17 23:25:08  mmiers
 * LOG: Add user data to list remove procs.
 * LOG: Add memory pools for quick reclamation.
 * LOG: Add object creation into user supplied buffers.
 * LOG:
 *
 ****************************************************************************/

#ifndef ITS_MEM_POOL_H
#define ITS_MEM_POOL_H

#include <its.h>

#ident "$Id: its_mem_pool.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

#define MEM_POOL_CHECKS_ON_STRING    "memPoolChecksOn"

/*
 * chunk management
 */
typedef struct __memChunk
{
    ITS_UINT            overMagic;
    struct __memChunk*  next;
    ITS_UINT            size;
    const char          *file;
    int                 line;
    ITS_UINT            underMagic;
    char                data[1];
}
MEMPOOL_Chunk;

#define MEMPOOL_PTR_TO_CHUNK(p) \
    ((MEMPOOL_Chunk *)((ITS_POINTER)(p) - offsetof(MEMPOOL_Chunk, data)))

/*
 * region management
 */
typedef struct
{
    ITS_UINT        power;
    ITS_UINT        numEntries;
    ITS_UINT        maxEntries;
    MEMPOOL_Chunk   *entries;
}
MEMPOOL_Region;

/*
 * a pool.
 */
typedef struct
{
    ITS_UINT        size;
    void *          regions;
    union
    {
        void *          curLoc;
        struct
        {
            ITS_MUTEX       lock;
            void *          inUse;
            ITS_BOOLEAN     doChecks;
        }
        heapInfo;
    }
    specific;
}
MEMPOOL_ObjPart;

/*
 * a pool object
 */
typedef struct
{
    ITS_CoreObjectPart  core;
    MEMPOOL_ObjPart     mempool;
}
MEMPOOL_Manager;

#define MEMPOOL_HEAP_REGIONS(x)                 \
    ((MEMPOOL_Region *)(((MEMPOOL_Manager *)(x))->mempool.regions))

#define MEMPOOL_VOID_HEAP_REGIONS(x)            \
    (((MEMPOOL_Manager *)(x))->mempool.regions)

#define MEMPOOL_HEAP_NUM_REGIONS(x)             \
    (((MEMPOOL_Manager *)(x))->mempool.size)

#define MEMPOOL_HEAP_LOCK(x)                    \
    (((MEMPOOL_Manager *)(x))->mempool.specific.heapInfo.lock)

#define MEMPOOL_HEAP_HASH(x)                    \
    (((MEMPOOL_Manager *)(x))->mempool.specific.heapInfo.inUse)

#define MEMPOOL_HEAP_CHECK(x)                   \
    (((MEMPOOL_Manager *)(x))->mempool.specific.heapInfo.doChecks)

#define MEMPOOL_STACK_REGIONS(x)                \
    (((MEMPOOL_Manager *)(x))->mempool.regions)

#define MEMPOOL_STACK_REGION_SIZE(x)            \
    (((MEMPOOL_Manager *)(x))->mempool.size)

#define MEMPOOL_STACK_CUR_LOC(x)                \
    (((MEMPOOL_Manager *)(x))->mempool.specific.curLoc)

#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * default number of powers we manage
 */
#define MEMPOOL_POWERS_DEFAULT  16

typedef void *(*MEMPOOL_LowAllocProc)(MEMPOOL_Manager *, ITS_UINT);
typedef void  (*MEMPOOL_LowFreeProc)(MEMPOOL_Manager *, void *);
typedef void *(*MEMPOOL_AllocProc)(MEMPOOL_Manager *, ITS_UINT,
                                   const char *, int);
typedef void *(*MEMPOOL_ClearAllocProc)(MEMPOOL_Manager *, ITS_UINT, ITS_UINT,
                                        const char *, int);
typedef void *(*MEMPOOL_ReallocProc)(MEMPOOL_Manager *, void *, ITS_UINT,
                                     const char *, int);
typedef void  (*MEMPOOL_FreeProc)(MEMPOOL_Manager *, void *,
                                  const char *, int);

#define MEMPOOL_HEAP_CLASS_NAME     "MEMPOOL HEAP"
#define MEMPOOL_STACK_CLASS_NAME    "MEMPOOL STACK"

typedef struct
{
    MEMPOOL_LowAllocProc    lowAlloc;
    MEMPOOL_LowFreeProc     lowFree;
    MEMPOOL_AllocProc       alloc;
    MEMPOOL_ClearAllocProc  clearalloc;
    MEMPOOL_ReallocProc     change;
    MEMPOOL_FreeProc        release;
}
MEMPOOL_ClassPart;

typedef struct
{
    ITS_CoreClassPart       coreClass;
    MEMPOOL_ClassPart       mempoolClass;
}
MEMPOOL_ClassRec, *MEMPOOL_Class;

#define MEMPOOL_CLASS_LOW_ALLOC(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.lowAlloc)

#define MEMPOOL_CLASS_LOW_FREE(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.lowFree)

#define MEMPOOL_CLASS_MALLOC(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.alloc)

#define MEMPOOL_CLASS_CALLOC(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.clearalloc)

#define MEMPOOL_CLASS_REALLOC(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.change)

#define MEMPOOL_CLASS_FREE(x) \
    (((MEMPOOL_Class)(x))->mempoolClass.release)

ITSDLLAPI extern MEMPOOL_ClassRec itsHEAPPOOL_ClassRec;
ITSDLLAPI extern ITS_Class        itsHEAPPOOL_Class;
ITSDLLAPI extern MEMPOOL_ClassRec itsLOCKHEAPPOOL_ClassRec;
ITSDLLAPI extern ITS_Class        itsLOCKHEAPPOOL_Class;
ITSDLLAPI extern MEMPOOL_ClassRec itsSTACKPOOL_ClassRec;
ITSDLLAPI extern ITS_Class        itsSTACKPOOL_Class;

/*
 * support's pool
 */
ITSDLLAPI extern ITS_ClassRec     itsMEMPOOL_ClassRec;
ITSDLLAPI extern ITS_Class        itsMEMPOOL_Class;

ITSDLLAPI extern MEMPOOL_Manager* MEMPOOL_Pool;

/*.interface:MEMPOOL
 *****************************************************************************
 *  Interface:
 *      MEMPOOL_*
 *
 *  Purpose:
 *      This is a simple, fast allocator.  It does not try to reclaim
 *      memory, merge segments, etc.  It merely maintains a global
 *      pool that does not shrink of allocated memory.  Max allocation
 *      size is determined by the pool itself.
 *
 *  Usage:
 *****************************************************************************/

#if !defined(ITS_FASTCALL)

ITSDLLAPI MEMPOOL_Manager *MEMPOOL_CreateHeapPool(ITS_UINT powers);
ITSDLLAPI MEMPOOL_Manager *MEMPOOL_CreateLockHeapPool(ITS_UINT powers);
ITSDLLAPI MEMPOOL_Manager *MEMPOOL_CreateStackPool(void *pool, ITS_UINT psize);
ITSDLLAPI void MEMPOOL_DestroyPool(MEMPOOL_Manager *);
ITSDLLAPI void *MEMPOOL_Alloc(MEMPOOL_Manager *m, ITS_UINT size);
ITSDLLAPI void *MEMPOOL_ClearAlloc(MEMPOOL_Manager *m, ITS_UINT count, ITS_UINT size);
ITSDLLAPI void *MEMPOOL_Realloc(MEMPOOL_Manager *m, void *chunk, ITS_UINT newSize);
ITSDLLAPI void  MEMPOOL_Free(MEMPOOL_Manager *m, void *chunk);

#else /* defined(ITS_FASTCALL) */

#define MEMPOOL_CreateHeapPool(powers)                              \
    (MEMPOOL_Manager *)ITS_ConstructObject(itsHEAPPOOL_Class,       \
                                           (powers), NULL)          \

#define MEMPOOL_CreateLockHeapPool(powers)                          \
    (MEMPOOL_Manager *)ITS_ConstructObject(itsLOCKHEAPPOOL_Class,   \
                                           (powers), NULL)          \

#define MEMPOOL_CreateStackPool(powers, pool, psize)                \
    (MEMPOOL_Manager *)ITS_ConstructObjectIn(ITS_OBJ_ALIGN(pool),   \
                                             itsHEAPPOOL_Class,     \
                                             (pool), (psize) -      \
                                              ITS_OBJ_OFFSET(pool), \
                                             NULL)

#define MEMPOOL_DestroyPool(m)                              \
    ITS_DestructObject((ITS_Object)(m))

#define MEMPOOL_Alloc(m, s)                                 \
    MEMPOOL_CLASS_MALLOC(ITS_OBJ_CLASS(m))((m), (s),        \
                         __FILE__, __LINE__)

#define MEMPOOL_ClearAlloc(m, c, s)                         \
    MEMPOOL_CLASS_CALLOC(ITS_OBJ_CLASS(m))((m), (c), (s),   \
                         __FILE__, __LINE__)

#define MEMPOOL_Realloc(m, o, s)                            \
    MEMPOOL_CLASS_REALLOC(ITS_OBJ_CLASS(m))((m), (o), (s),  \
                          __FILE__, __LINE__)

#define MEMPOOL_Free(m, r)                                  \
    MEMPOOL_CLASS_FREE(ITS_OBJ_CLASS(m))((m), (r),          \
                       __FILE__, __LINE__)

#endif /* defined(ITS_FASTCALL) */

/*
 * chicken/egg avoidance
 */
ITSDLLAPI void *  THREAD_GetLocalStorage();
ITSDLLAPI int     THREAD_SetLocalStorage(void *);

/*
 * global allocation in support
 */
#if !defined(USE_HEAP)

#define ITS_Malloc(sz)                                                  \
    MEMPOOL_Alloc(THREAD_GetLocalStorage() != NULL                      \
                     ? (MEMPOOL_Manager *)THREAD_GetLocalStorage()      \
                     : MEMPOOL_Pool,                                    \
                  (sz))
#define ITS_Calloc(cnt, sz)                                             \
    MEMPOOL_ClearAlloc(THREAD_GetLocalStorage() != NULL                 \
                         ? (MEMPOOL_Manager *)THREAD_GetLocalStorage()  \
                         : MEMPOOL_Pool,                                \
                       (cnt), (sz))
#define ITS_Realloc(old, newSz)                                         \
    MEMPOOL_Realloc(THREAD_GetLocalStorage() != NULL                    \
                     ? (MEMPOOL_Manager *)THREAD_GetLocalStorage()      \
                     : MEMPOOL_Pool,                                    \
                    (old), (newSz))
#define ITS_Free(r)                                                     \
    MEMPOOL_Free((MEMPOOL_Manager *)THREAD_GetLocalStorage()            \
                     ? (MEMPOOL_Manager *)THREAD_GetLocalStorage()      \
                     : MEMPOOL_Pool,                                    \
                 (r))

#else

#define ITS_Malloc(sz)          malloc(sz)
#define ITS_Calloc(cnt, sz)     calloc(cnt, sz)
#define ITS_Realloc(old, ns)    realloc(old, ns)
#define ITS_Free(r)             free(r)

#endif

#if defined(__cplusplus)
}
#endif

#if defined(USE_CPLUSPLUS)

/*.interface:MEMPOOL
 *****************************************************************************
 *  Interface:
 *      MEMPOOL_*
 *
 *  Purpose:
 *      This interface describes a fast allocator pool for C.
 *
 *  Usage:
 *****************************************************************************/
class MemPool
{
public:
    /*.implementation:public,inline,MemPool
     **************************************************************************
     *  Purpose:
     *      Link this C++ object to a C memory pool.
     *
     *  Input Parameters:
     *      m - mempool to contain.
     *
     **************************************************************************/
    MemPool(MEMPOOL_Manager *m)
        : manager(m)
    {
    }

    /*.implementation:public,inline,MemPool
     **************************************************************************
     *  Purpose:
     *      Allocate a region from a memory pool.
     *
     *  Input Parameters:
     *      size - sizeof region to allocate
     *
     *  Return Value:
     *      pointer to the allocated region or NULL
     *
     **************************************************************************/
    void *
    Alloc(ITS_UINT size)
    {
        return MEMPOOL_Alloc(manager, size);
    }

    /*.implementation:public,inline,MemPool
     **************************************************************************
     *  Purpose:
     *      Reallocate a region from a memory pool.
     *
     *  Input Parameters:
     *      old - pointer to old region
     *      newSize - new size of region
     *
     *  Return Value:
     *      pointer to reallocated region or NULL on failure
     *
     **************************************************************************/
    void *
    Realloc(void *old, ITS_UINT newSize)
    {
        return MEMPOOL_Realloc(manager, old, newSize);
    }

    /*.implementation:public,inline,MemPool
     **************************************************************************
     *  Purpose:
     *      Return a region to a memory pool.
     *
     *  Input Parameters:
     *      old - region to free
     *
     **************************************************************************/
    void
    Free(void *old)
    {
        MEMPOOL_Free(manager, old);
    }

private:
    MemPool() {}    /* must have an object to manage. */

    MEMPOOL_Manager *manager;
};

#endif /* USE_CPLUSPLUS */

#endif /* ITS_MEM_POOL_H */
