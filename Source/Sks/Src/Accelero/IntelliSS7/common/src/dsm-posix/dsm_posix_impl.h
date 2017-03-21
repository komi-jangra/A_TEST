/******************************************************************************
 *                                                                            *
 *  Copyright 2001 - 2002 IntelliNet Technologies, Inc. All Rights Reserved.  *
 *             Manufactured in the United States of America.                  *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.         *
 *                                                                            *
 *   This product and related documentation is protected by copyright and     *
 *   distributed under licenses restricting its use, copying, distribution    *
 *   and decompilation.  No part of this product or related documentation     *
 *   may be reproduced in any form by any means without prior written         *
 *   authorization of IntelliNet Technologies and its licensors, if any.      *
 *                                                                            *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the        *
 *   government is subject to restrictions as set forth in subparagraph       *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software         *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                          *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.3  2003/09/29 12:38:06  mmiers
 * LOG: Update for UNIX build
 * LOG:
 * LOG: Revision 1.2  2003/09/26 14:03:50  mmiers
 * LOG: More updates.
 * LOG:
 * LOG: Revision 1.1  2003/09/23 19:59:25  mmiers
 * LOG: New implementation for POSIX shared memory (more later).
 * LOG: Bug fix for index ranges in stub.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_DSM_POSIX_IMPL_H_)
#define _DSM_POSIX_IMPL_H_

#include <its.h>
#include <its_mutex.h>
#include <its_dsm.h>
#include <its_hash.h>
#include <its_rb.h>
#include <its_splay.h>

#ident "$Id: dsm_posix_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

#if defined(__cplusplus)
extern "C"
{
#endif

/*****************************************************************************
 *                                                                           *
 * Non-public header (implementation).                                       *
 *                                                                           *
 *****************************************************************************/
    
/******************************************************************************
 ******************************************************************************
 **
 ** Allocator related.
 **
 */

/*
 * We need a definition of the allocator for DSM.
 * This is basically an adapted version of Doug Lea's allocator.
 */

/* The corresponding word size */
#define SIZE_SZ                (sizeof(size_t))

/*
 * MALLOC_ALIGNMENT is the minimum alignment for malloc'ed chunks.
 * It must be a power of two at least 2 * SIZE_SZ, even on machines
 * for which smaller alignments would suffice. It may be defined as
 * larger than this though. Note however that code and data structures
 * are optimized for the case of 8-byte alignment.
 */
#define MALLOC_ALIGNMENT       (2 * SIZE_SZ)

/* The corresponding bit mask value */
#define MALLOC_ALIGN_MASK      (MALLOC_ALIGNMENT - 1)

/*
 * -----------------------  Chunk representations -----------------------
 */

/*
 * This struct declaration is misleading (but accurate and necessary).
 * It declares a "view" into memory allowing access to necessary
 * fields at known offsets from a given base. See explanation below.
 */
struct malloc_chunk
{
    size_t      prev_size;    /* Size of previous chunk (if free).  */
    size_t      size;         /* Size in bytes, including overhead. */
    struct malloc_chunk* fd;  /* double links -- used only if free. */
    struct malloc_chunk* bk;
};

typedef struct malloc_chunk* mchunkptr;

/* The smallest possible chunk */
#define MIN_CHUNK_SIZE \
    (sizeof(struct malloc_chunk))

/* The smallest size we can malloc is an aligned minimal chunk */
#define MINSIZE \
    (unsigned long)(((MIN_CHUNK_SIZE+MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))

/* 
 *  Check if a request is so large that it would wrap around zero when
 *  padded and aligned. To simplify some other code, the bound is made
 *  low enough so that adding MINSIZE will also not wrap around sero.
 */
#define REQUEST_OUT_OF_RANGE(req)                                   \
    ((unsigned long)(req) >=                                        \
     (unsigned long)(size_t)(-2 * (int)MINSIZE))    

/* pad request bytes into a usable size -- internal version */
#define request2size(req)                                           \
    (((req) + SIZE_SZ + MALLOC_ALIGN_MASK < MINSIZE)                \
        ? MINSIZE                                                   \
        : ((req) + SIZE_SZ + MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK)

/*  Same, except also perform argument check */
#define checked_request2size(req, sz)                               \
    if (REQUEST_OUT_OF_RANGE(req))                                  \
    {                                                               \
        return 0;                                                   \
    }                                                               \
    (sz) = request2size(req);

/*
 * -------------------- Internal data structures --------------------
 *
 *  All internal state is held in an instance of malloc_state defined
 *  below. There are no other static variables, except in two optional
 *  cases: 
 *  * If USE_MALLOC_LOCK is defined, the mALLOC_MUTEx declared above.
 *
 *  Beware of lots of tricks that minimize the total bookkeeping space
 *  requirements. The result is a little over 1K bytes (for 4byte
 *  pointers and size_t.)
 */

/*
 * Bins
 *
 *   An array of bin headers for free chunks. Each bin is doubly
 *   linked.  The bins are approximately proportionally (log) spaced.
 *   There are a lot of these bins (128). This may look excessive, but
 *   works very well in practice.  Most bins hold sizes that are
 *   unusual as malloc request sizes, but are more usual for fragments
 *   and consolidated sets of chunks, which is what these bins hold, so
 *   they can be found quickly.  All procedures maintain the invariant
 *   that no consolidated chunk physically borders another one, so each
 *   chunk in a list is known to be preceeded and followed by either
 *   inuse chunks or the ends of memory.
 *
 *   Chunks in bins are kept in size order, with ties going to the
 *   approximately least recently used chunk. Ordering isn't needed
 *   for the small bins, which all contain the same-sized chunks, but
 *   facilitates best-fit allocation for larger chunks. These lists
 *   are just sequential. Keeping them in order almost never requires
 *   enough traversal to warrant using fancier ordered data
 *   structures.  
 *
 *   Chunks of the same size are linked with the most
 *   recently freed at the front, and allocations are taken from the
 *   back.  This results in LRU (FIFO) allocation order, which tends
 *   to give each chunk an equal opportunity to be consolidated with
 *   adjacent freed chunks, resulting in larger free chunks and less
 *   fragmentation.
 *
 *   To simplify use in double-linked lists, each bin header acts
 *   as a malloc_chunk. This avoids special-casing for headers.
 *   But to conserve space and improve locality, we allocate
 *   only the fd/bk pointers of bins, and then use repositioning tricks
 *   to treat these as the fields of a malloc_chunk*.  
 */
typedef struct malloc_chunk* mbinptr;

/*
 *  Indexing
 *
 *   Bins for sizes < 512 bytes contain chunks of all the same size, spaced
 *   8 bytes apart. Larger bins are approximately logarithmically spaced:
 *
 *   64 bins of size       8
 *   32 bins of size      64
 *   16 bins of size     512
 *    8 bins of size    4096
 *    4 bins of size   32768
 *    2 bins of size  262144
 *    1 bin  of size what's left
 *
 *   There is actually a little bit of slop in the numbers in bin_index
 *   for the sake of speed. This makes no difference elsewhere.
 *
 *   The bins top out around 1MB because we expect to service large
 *   requests via mmap.
 */
#define NBINS             128
#define NSMALLBINS         64
#define SMALLBIN_WIDTH      8
#define MIN_LARGE_SIZE    512

/*
 * Binmap
 *
 *   To help compensate for the large number of bins, a one-level index
 *   structure is used for bin-by-bin searching.  `binmap' is a
 *   bitvector recording whether bins are definitely empty so they can
 *   be skipped over during during traversals.  The bits are NOT always
 *   cleared as soon as bins are empty, but instead only
 *   when they are noticed to be empty during traversal in malloc.
 */
/* Conservatively use 32 bits per map word, even if on 64bit system */
#define BINMAPSHIFT      5
#define BITSPERMAP       (1U << BINMAPSHIFT)
#define BINMAPSIZE       (NBINS / BITSPERMAP)

/*
 * Fastbins
 *
 *   An array of lists holding recently freed small chunks.  Fastbins
 *   are not doubly linked.  It is faster to single-link them, and
 *   since chunks are never removed from the middles of these lists,
 *   double linking is not necessary. Also, unlike regular bins, they
 *   are not even processed in FIFO order (they use faster LIFO) since
 *   ordering doesn't much matter in the transient contexts in which
 *   fastbins are normally used.
 *
 *   Chunks in fastbins keep their inuse bit set, so they cannot
 *   be consolidated with other free chunks. malloc_consolidate
 *   releases all chunks in fastbins and consolidates them with
 *   other free chunks. 
 */
typedef struct malloc_chunk* mfastbinptr;

/* offset 2 to use otherwise unindexable first 2 bins */
#define fastbin_index(sz) \
    ((((unsigned int)(sz)) >> 3) - 2)

/* The maximum fastbin request size we support */
#define MAX_FAST_SIZE     80

#define NFASTBINS  (fastbin_index(request2size(MAX_FAST_SIZE))+1)

/*
 *  ----------- Internal state representation and initialization -----------
 */
typedef struct malloc_state
{
    /* The maximum chunk size to be eligible for fastbin */
    size_t  max_fast;   /* low 2 bits used as flags */

    /* Fastbins */
    mfastbinptr      fastbins[NFASTBINS];

    /* Base of the topmost chunk -- not otherwise kept in a bin */
    mchunkptr        top;

    /* The remainder from the most recent split of a small request */
    mchunkptr        last_remainder;

    /* Normal bins packed as described above */
    mchunkptr        bins[NBINS * 2];

    /* Bitmap of bins */
    unsigned int     binmap[BINMAPSIZE];

    /* Cache malloc_getpagesize */
    unsigned int     pagesize;    

    /* Statistics */
    size_t  sbrked_mem;
    size_t  max_sbrked_mem;
    size_t  max_total_mem;
}
*mstate;

/*
 * cache sizes
 */
#ifdef __sparc
#define DSM_CACHE_SIZE 2097152U
#else
#define DSM_CACHE_SIZE 8192U
#endif

    
/******************************************************************************
 ******************************************************************************
 **
 ** DSM (POSIX) Data class.
 **
 */

/*
 * DSM (POSIX) Data class definition.
 */

typedef struct
{
    void* reserved1;
    void* reserved2;
}
DSM_DataClassPart;

typedef struct
{
    ITS_CoreClassPart   coreClass;
    DSM_DataClassPart   dataClass;

}
DSM_DataClassRec, *DSM_DataClass;

#define DSM_DATA_CLASS_NAME  "DSM Data Class - POSIX"

/*
 * Definitions used by DSM (POSIX) Data object.
 */ 

typedef struct
{
    DSM_TableType       type;
    union
    {
        HASH_Table      hash;
        REDBLACK_Tree   tree;
        SPLAY_Tree      splay;
    }
    table;
} 
DSM_Table;

typedef DSM_Table* DSM_Tables;

/*
 * DSM info (lock...).
 */ 

typedef struct
{
    ITS_MUTEX       lock;
    int             pid;
}
DSM_DsmInfo;

/*
 * Table info (lock, count of entries...).
 */

typedef struct
{
    ITS_MUTEX   lock;
    ITS_UINT    entries;
}
DSM_TableInfo;

typedef DSM_TableInfo* DSM_TablesInfo;

/*
 * DSM shared (through POSIX) memory data. Unique instance of this structure is
 * stored at the zero page in the shared memory.
 */
typedef struct
{
    struct malloc_state         state;
    ITS_UINT                    size;
    ITS_POINTER                 base;
    ITS_POINTER                 top;
    ITS_POINTER                 curbrk;
    ITS_POINTER                 cursync;
    DSM_Tables                  tables;
    DSM_DsmInfo                 dsmInfo;
    DSM_TablesInfo              tablesInfo;
}
DSM_MemData;

/*
 * DSM (POSIX) Data object definition.
 */

typedef struct
{
    DSM_CoreObject* coreObject; /* Access within destroy instance only. */
    DSM_InstObject* instObject; /* Access within destroy instance only. */
    void*           sysMapAddr; /* map base */
    int             fd;         /* shared fd */
    ITS_BOOLEAN     first;      /* true if this process is the creator */
    DSM_MemData*    memData;
}
DSM_DataObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_DataObjectPart  dataObject;
}
DSM_DataObject;


#define DSM_DATA_SYS_MAP_ADDR(x) \
    (((DSM_DataObject*)(x))->dataObject.sysMapAddr)

#define DSM_DATA_FD(x) \
    (((DSM_DataObject*)(x))->dataObject.fd)

#define DSM_DATA_FIRST(x) \
    (((DSM_DataObject*)(x))->dataObject.first)

#define DSM_DATA_CORE_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.coreObject)

#define DSM_DATA_INST_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.instObject)

#define DSM_DATA_MEM_DATA(x) \
    (((DSM_DataObject*)(x))->dataObject.memData)

#define DSM_DATA_DSM_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->dsmInfo)

#define DSM_DATA_TABLES(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->tables)

#define DSM_DATA_TABLES_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->tablesInfo)

#define DSM_DATA_TABLES_LOCK(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->dsmInfo.lock)

#define DSM_DATA_FT_GROUP_ID(x)                         \
    ((DSM_DATA_INST_OBJECT(x) != NULL)               ?  \
     (DSM_INST_FT_GROUP_ID(DSM_DATA_INST_OBJECT(x))) :  \
     (DSM_INVALID_FT_GROUP_ID))

#if defined(__cplusplus)
}
#endif

#endif /* _DSM_POSIX_IMPL_H_ */


