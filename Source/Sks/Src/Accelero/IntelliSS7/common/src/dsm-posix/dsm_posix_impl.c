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
 * LOG: Revision 9.1  2005/03/23 12:53:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.4  2003/09/29 12:38:06  mmiers
 * LOG: Update for UNIX build
 * LOG:
 * LOG: Revision 1.3  2003/09/26 14:03:50  mmiers
 * LOG: More updates.
 * LOG:
 * LOG: Revision 1.2  2003/09/23 20:24:44  mmiers
 * LOG: Add the shared mem glue and we're good to go.
 * LOG:
 * LOG: Revision 1.1  2003/09/23 19:59:25  mmiers
 * LOG: New implementation for POSIX shared memory (more later).
 * LOG: Bug fix for index ranges in stub.
 * LOG:
 *
 *****************************************************************************/


#include <its_dsm_posix.h>
#include <dsm_posix_impl.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_timers.h>

#ident "$Id: dsm_posix_impl.c,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/******************************************************************************
 ******************************************************************************
 **
 ** DSM (POSIX) allocator.
 **
 */
/******************************************************************************
 ******************************************************************************
 **
 ** Definitions for portable mmap across Unix variants.
 **
 */

#if !defined(WIN32)

#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>

/* the shared memory name */
#define SHM_FILE        "/shm_seg_ss7"

#define DSM_MAX_RETRY   3

#if !defined(MAP_ANONYMOUS) && defined(MAP_ANON)
#define MAP_ANONYMOUS MAP_ANON
#endif /* !defined(MAP_ANONYMOUS) && defined(MAP_ANON) */

#if !defined(MAP_ANONYMOUS)

static int dev_zero_fd = -1; /* Cached file descriptor for /dev/zero. */

#define MMAP(addr, size, prot, flags) ((dev_zero_fd < 0) ?      \
 (dev_zero_fd = open("/dev/zero", O_RDWR),                      \
  mmap((addr), (size), (prot), (flags), dev_zero_fd, 0)) :      \
   mmap((addr), (size), (prot), (flags), dev_zero_fd, 0))

#else /* defined(MAP_ANONYMOUS) */

#define MMAP(addr, size, prot, flags)                           \
 (mmap((addr), (size), (prot), (flags)|MAP_ANONYMOUS, -1, 0))

#endif /* !defined(MAP_ANONYMOUS) */

#endif /* !defined(WIN32) */

/******************************************************************************
 ******************************************************************************
 **
 ** Allocator related (definitions).
 **
 */

/*
 * MORECORE is the name of the routine to call to obtain more memory
 * from the system.  See below for general guidance on writing
 * alternative MORECORE functions, as well as a version for WIN32 and a
 * sample version for pre-OSX macos.
 */
#if defined(WIN32)
static void *sharedAlloc(DSM_DataObject* dataObj, int incr);
#else
static void *sharedAlloc(DSM_DataObject* dataObj, ptrdiff_t incr);
#endif

#define MORECORE sharedAlloc

/*
 * MORECORE_FAILURE is the value returned upon failure of MORECORE
 * as well as mmap. Since it cannot be an otherwise valid memory address,
 * and must reflect values of standard sys calls, you probably ought not
 * try to redefine it.
 */
#define MORECORE_FAILURE (-1)

/*
 * The system page size. To the extent possible, this malloc manages
 * memory from the system in page-size units.  Note that this value is
 * cached during initialization into a field of malloc_state. So even
 * if malloc_getpagesize is a function, it is only called once.
 *
 * The following mechanics for getpagesize were adapted from bsd/gnu
 * getpagesize.h. If none of the system-probes here apply, a value of
 * 4096 is used, which should be OK: If they don't apply, then using
 * the actual value probably doesn't impact performance.
 */
#ifndef malloc_getpagesize

#  ifdef _SC_PAGESIZE         /* some SVR4 systems omit an underscore */
#    ifndef _SC_PAGE_SIZE
#      define _SC_PAGE_SIZE _SC_PAGESIZE
#    endif
#  endif

#  ifdef _SC_PAGE_SIZE
#    define malloc_getpagesize sysconf(_SC_PAGE_SIZE)
#  else
#    if defined(BSD) || defined(DGUX) || defined(HAVE_GETPAGESIZE)
       extern size_t getpagesize();
#      define malloc_getpagesize getpagesize()
#    else
#      ifdef WIN32 /* use supplied emulation of getpagesize */
#        define malloc_getpagesize getpagesize() 
#      else
#        ifndef LACKS_SYS_PARAM_H
#          include <sys/param.h>
#        endif
#        ifdef EXEC_PAGESIZE
#          define malloc_getpagesize EXEC_PAGESIZE
#        else
#          ifdef NBPG
#            ifndef CLSIZE
#              define malloc_getpagesize NBPG
#            else
#              define malloc_getpagesize (NBPG * CLSIZE)
#            endif
#          else
#            ifdef NBPC
#              define malloc_getpagesize NBPC
#            else
#              ifdef PAGESIZE
#                define malloc_getpagesize PAGESIZE
#              else /* just guess */
#                define malloc_getpagesize (4096) 
#              endif
#            endif
#          endif
#        endif
#      endif
#    endif
#  endif
#endif

/*
 * windows needs a getpagesize()
 */
#if defined(WIN32)

static long getpagesize(void)
{
    static long g_pagesize = 0;

    if (!g_pagesize)
    {
        SYSTEM_INFO system_info;

        GetSystemInfo(&system_info);

        g_pagesize = system_info.dwPageSize;
    }

    return (g_pagesize);
}

#endif

/*
 * M_MXFAST is the maximum request size used for "fastbins", special bins
 * that hold returned chunks without consolidating their spaces. This
 * enables future requests for chunks of the same size to be handled
 * very quickly, but can increase fragmentation, and thus increase the
 * overall memory footprint of a program.
 *
 * This malloc manages fastbins very conservatively yet still
 * efficiently, so fragmentation is rarely a problem for values less
 * than or equal to the default.  The maximum supported value of MXFAST
 * is 80. You wouldn't want it any higher than this anyway.  Fastbins
 * are designed especially for use with many small structs, objects or
 * strings -- the default handles structs/objects/arrays with sizes up
 * to 8 4byte fields, or small strings representing words, tokens,
 * etc. Using fastbins for larger objects normally worsens
 * fragmentation without improving speed.
 *
 * M_MXFAST is set in REQUEST size units. It is internally used in
 * chunksize units, which adds padding and alignment.  You can reduce
 * M_MXFAST to 0 to disable all use of fastbins.  This causes the malloc
 * algorithm to be a closer approximation of fifo-best-fit in all cases,
 * not just for larger requests, but will generally cause it to be
 * slower.
 */
#define DEFAULT_MXFAST     64

/* 
 * Note: memcpy is ONLY invoked with non-overlapping regions,
 * so the (usually slower) memmove is not needed.
 */
#define MALLOC_COPY(dest, src, nbytes)      \
    do                                      \
    {                                       \
        memcpy(dest, src, nbytes);          \
    }                                       \
    while (0)

#define MALLOC_ZERO(dest, nbytes)           \
    do                                      \
    {                                       \
        memset(dest, 0,   nbytes);          \
    }                                       \
    while (0)

/*
 *  malloc_chunk details:
 *
 *   (The following includes lightly edited explanations by Colin Plumb.)
 *
 *   Chunks of memory are maintained using a `boundary tag' method as
 *   described in e.g., Knuth or Standish.  (See the paper by Paul
 *   Wilson ftp://ftp.cs.utexas.edu/pub/garbage/allocsrv.ps for a
 *   survey of such techniques.)  Sizes of free chunks are stored both
 *   in the front of each chunk and at the end.  This makes
 *   consolidating fragmented chunks into bigger chunks very fast.  The
 *   size fields also hold bits representing whether chunks are free or
 *   in use.
 *
 *   An allocated chunk looks like this:
 *
 *
 *     chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Size of previous chunk, if allocated            | |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Size of chunk, in bytes                         |P|
 *       mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             User data starts here...                          .
 *             .                                                               .
 *             .             (malloc_usable_space() bytes)                     .
 *             .                                                               |
 * nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Size of chunk                                     |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *
 *   Where "chunk" is the front of the chunk for the purpose of most of
 *   the malloc code, but "mem" is the pointer that is returned to the
 *   user.  "Nextchunk" is the beginning of the next contiguous chunk.
 *
 *   Chunks always begin on even word boundries, so the mem portion
 *   (which is returned to the user) is also on an even word boundary, and
 *   thus at least double-word aligned.
 *
 *   Free chunks are stored in circular doubly-linked lists, and look like this:
 *
 *     chunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Size of previous chunk                            |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     `head:' |             Size of chunk, in bytes                         |P|
 *       mem-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Forward pointer to next chunk in list             |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Back pointer to previous chunk in list            |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *             |             Unused space (may be 0 bytes long)                .
 *             .                                                               .
 *             .                                                               |
 * nextchunk-> +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *     `foot:' |             Size of chunk, in bytes                           |
 *             +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 *   The P (PREV_INUSE) bit, stored in the unused low-order bit of the
 *   chunk size (which is always a multiple of two words), is an in-use
 *   bit for the *previous* chunk.  If that bit is *clear*, then the
 *   word before the current chunk size contains the previous chunk
 *   size, and can be used to find the front of the previous chunk.
 *   The very first chunk allocated always has this bit set,
 *   preventing access to non-existent (or non-owned) memory. If
 *   prev_inuse is set for any given chunk, then you CANNOT determine
 *   the size of the previous chunk, and might even get a memory
 *   addressing fault when trying to do so.
 *
 *   Note that the `foot' of the current chunk is actually represented
 *   as the prev_size of the NEXT chunk. This makes it easier to
 *   deal with alignments etc but can be very confusing when trying
 *   to extend or adapt this code.
 *
 *   The exception to all this is
 *
 *    1. The special chunk `top' doesn't bother using the
 *       trailing size field since there is no next contiguous chunk
 *       that would have to index off it. After initialization, `top'
 *       is forced to always exist.  If it would become less than
 *       MINSIZE bytes long, it is replenished.
 *
 */

/*
 * ---------- Size and alignment checks and conversions ----------
 */

/* conversion from malloc headers to user pointers, and back */
#define chunk2mem(p) \
    ((void*)((char*)(p) + 2*SIZE_SZ))

#define mem2chunk(mem) \
    ((mchunkptr)((char*)(mem) - 2*SIZE_SZ))

/* Check if m has acceptable alignment */
#define aligned_OK(m) \
    (((unsigned long)((m)) & (MALLOC_ALIGN_MASK)) == 0)

/*
 *  --------------- Physical chunk operations ---------------
 */

/* size field is or'ed with PREV_INUSE when previous adjacent chunk in use */
#define PREV_INUSE  0x1

/* extract inuse bit of previous chunk */
#define prev_inuse(p) \
    ((p)->size & PREV_INUSE)


/* 
 * Bits to mask off when extracting size 
 */
#define SIZE_BITS (PREV_INUSE)

/* Get size, ignoring use bits */
#define chunksize(p) \
    ((p)->size & ~(SIZE_BITS))

/* Ptr to next physical malloc_chunk. */
#define next_chunk(p) \
    ((mchunkptr)( ((char*)(p)) + ((p)->size & ~PREV_INUSE) ))

/* Ptr to previous physical malloc_chunk */
#define prev_chunk(p) \
    ((mchunkptr)( ((char*)(p)) - ((p)->prev_size) ))

/* Treat space at ptr + offset as a chunk */
#define chunk_at_offset(p, s) \
    ((mchunkptr)(((char*)(p)) + (s)))

/* extract p's inuse bit */
#define inuse(p) \
    ((((mchunkptr)(((char*)(p)) + \
      ((p)->size & ~PREV_INUSE)))->size) & PREV_INUSE)

/* set/clear chunk as being inuse without otherwise disturbing */
#define set_inuse(p)                                                    \
    do                                                                  \
    {                                                                   \
        ((mchunkptr)(((char*)(p)) +                                     \
                     ((p)->size & ~PREV_INUSE)))->size |=               \
        PREV_INUSE;                                                     \
    }                                                                   \
    while (0)

#define clear_inuse(p)                                                  \
    do                                                                  \
    {                                                                   \
        ((mchunkptr)(((char*)(p)) +                                     \
                     ((p)->size & ~PREV_INUSE)))->size &=               \
        ~(PREV_INUSE);                                                  \
    }                                                                   \
    while (0)


/* check/set/clear inuse bits in known places */
#define inuse_bit_at_offset(p, s) \
    (((mchunkptr)(((char*)(p)) + (s)))->size & PREV_INUSE)

#define set_inuse_bit_at_offset(p, s)                               \
    do                                                              \
    {                                                               \
        (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE);    \
    }                                                               \
    while (0)

#define clear_inuse_bit_at_offset(p, s)                             \
    do                                                              \
    {                                                               \
        (((mchunkptr)(((char*)(p)) + (s)))->size &= ~(PREV_INUSE)); \
    }                                                               \
    while (0)


/* Set size at head, without disturbing its use bit */
#define set_head_size(p, s)                                 \
    do                                                      \
    {                                                       \
        ((p)->size = (((p)->size & PREV_INUSE) | (s)));     \
    }                                                       \
    while (0)

/* Set size/use field */
#define set_head(p, s)          \
    do                          \
    {                           \
        ((p)->size = (s));      \
    }                           \
    while (0)

/* Set size at footer (only when chunk is not in use) */
#define set_foot(p, s)                                              \
    do                                                              \
    {                                                               \
        (((mchunkptr)((char*)(p) + (s)))->prev_size = (s));         \
    }                                                               \
    while (0)

/*
 * bin functions -------------------------------------------------------
 */

/* addressing -- note that bin_at(0) does not exist */
#define bin_at(m, i) \
    ((mbinptr)((char*)&((m)->bins[(i)<<1]) - (SIZE_SZ<<1)))

/* analog of ++bin */
#define next_bin(b) \
    ((mbinptr)((char*)(b) + (sizeof(mchunkptr)<<1)))

/* Reminders about list directionality within bins */
#define first(b)     ((b)->fd)
#define last(b)      ((b)->bk)

/* Take a chunk off a bin list */
#define unlink(P, BK, FD)   \
    do                      \
    {                       \
        FD = P->fd;         \
        BK = P->bk;         \
        FD->bk = BK;        \
        BK->fd = FD;        \
    }                       \
    while (0)

#define in_smallbin_range(sz) \
    ((unsigned long)(sz) < (unsigned long)MIN_LARGE_SIZE)

#define smallbin_index(sz) \
    (((unsigned)(sz)) >> 3)

#define largebin_index(sz)                                      \
    (((((unsigned long)(sz)) >>  6) <= 32)                      \
        ?  56 + (((unsigned long)(sz)) >>  6)                   \
        : ((((unsigned long)(sz)) >>  9) <= 20)                 \
            ?  91 + (((unsigned long)(sz)) >>  9)               \
            : ((((unsigned long)(sz)) >> 12) <= 10)             \
                ? 110 + (((unsigned long)(sz)) >> 12)           \
                : ((((unsigned long)(sz)) >> 15) <=  4)         \
                    ? 119 + (((unsigned long)(sz)) >> 15)       \
                    : ((((unsigned long)(sz)) >> 18) <=  2)     \
                        ? 124 + (((unsigned long)(sz)) >> 18)   \
                        : 126)

#define bin_index(sz)           \
    ((in_smallbin_range(sz))    \
        ? smallbin_index(sz)    \
        : largebin_index(sz))

/*
 * Unsorted chunks
 *
 *   All remainders from chunk splits, as well as all returned chunks,
 *   are first placed in the "unsorted" bin. They are then placed
 *   in regular bins after malloc gives them ONE chance to be used before
 *   binning. So, basically, the unsorted_chunks list acts as a queue,
 *   with chunks being placed on it in free (and MallocConsolidate),
 *   and taken off (to be either used or placed in bins) in malloc.
 */
/* The otherwise unindexable 1-bin is used to hold unsorted chunks. */
#define unsorted_chunks(M)          (bin_at(M, 1))

/*
 * Top
 *
 *   The top-most available chunk (i.e., the one bordering the end of
 *   available memory) is treated specially. It is never included in
 *   any bin, is used only if no other chunk is available, and is
 *   released back to the system if it is very large (see
 *   M_TRIM_THRESHOLD).  Because top initially
 *   points to its own bin with initial zero size, thus forcing
 *   extension on the first malloc request, we avoid having any special
 *   code in malloc to check whether it even exists yet. But we still
 *   need to do so when getting memory from system, so we make
 *   initial_top treat the bin as a legal but unusable chunk during the
 *   interval between initialization and the first call to
 *   SysMalloc. (This is somewhat delicate, since it relies on
 *   the 2 preceding words to be zero during this interval as well.)
 */
/* Conveniently, the unsorted bin can be used as dummy top on first call */
#define initial_top(M)              (unsorted_chunks(M))

/*
 * bin info -----------------------------------------------------
 */
#define idx2block(i) \
    ((i) >> BINMAPSHIFT)
#define idx2bit(i) \
    ((1U << ((i) & ((1U << BINMAPSHIFT)-1))))

#define get_binmap(m,i) \
    ((m)->binmap[idx2block(i)] &   idx2bit(i))

#define mark_bin(m,i)                                   \
    do                                                  \
    {                                                   \
        ((m)->binmap[idx2block(i)] |=  idx2bit(i));     \
    }                                                   \
    while (0)

#define unmark_bin(m,i)                                 \
    do                                                  \
    {                                                   \
        ((m)->binmap[idx2block(i)] &= ~(idx2bit(i)));   \
    }                                                   \
    while (0)

/*
 * FASTBIN_CONSOLIDATION_THRESHOLD is the size of a chunk in free()
 * that triggers automatic consolidation of possibly-surrounding
 * fastbin chunks. This is a heuristic, so the exact value should not
 * matter too much. It is defined at half the default trim threshold as a
 * compromise heuristic to only attempt consolidation if it is likely
 * to lead to trimming. However, it is not dynamically tunable, since
 * consolidation reduces fragmentation surrounding loarge chunks even 
 * if trimming is not used.
 */
#define FASTBIN_CONSOLIDATION_THRESHOLD  (65536UL)

/*
 * Since the lowest 2 bits in max_fast don't matter in size comparisons, 
 * they are used as flags.
 */

/*
 * FASTCHUNKS_BIT held in max_fast indicates that there are probably
 * some fastbin chunks. It is set true on entering a chunk into any
 * fastbin, and cleared only in MallocConsolidate.
 *
 * The truth value is inverted so that have_fastchunks will be true
 * upon startup (since statics are zero-filled), simplifying
 * initialization checks.
 */
#define FASTCHUNKS_BIT        (1U)

#define have_fastchunks(M) \
    (((M)->max_fast &  FASTCHUNKS_BIT) == 0)

#define clear_fastchunks(M)                 \
    do                                      \
    {                                       \
        ((M)->max_fast |=  FASTCHUNKS_BIT); \
    }                                       \
    while (0)

#define set_fastchunks(M)                   \
    do                                      \
    {                                       \
        ((M)->max_fast &= ~FASTCHUNKS_BIT); \
    }                                       \
    while (0)

/* 
 *  Set value of max_fast. 
 *  Use impossibly small value if 0.
 *  Precondition: there are no existing fastbin chunks.
 *  Setting the value clears fastchunk bit but preserves noncontiguous bit.
 */
#define set_max_fast(M, s)                                  \
    do                                                      \
    {                                                       \
        (M)->max_fast = (((s) == 0)                         \
            ? SMALLBIN_WIDTH                                \
            : request2size(s)) | FASTCHUNKS_BIT;            \
    }                                                       \
    while (0)


/*
 * Allocator API.
 */
static void*  dlmalloc(DSM_DataObject* dataObj, size_t);
static void   dlfree(DSM_DataObject* dataObj, void*);
static void*  dlcalloc(DSM_DataObject* dataObj, size_t, size_t);
static void*  dlrealloc(DSM_DataObject* dataObj, void*, size_t);

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      This function acts as sbrk() for the DSM region.
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void*
sharedAlloc(DSM_DataObject* dataObj, ptrdiff_t size)
{
    if (size < 0)
    {
        return (void *)MORECORE_FAILURE;
    }
    else if (size == 0)
    {
        return (void *)DSM_DATA_MEM_DATA(dataObj)->curbrk;
    }
    else
    {
        if ((DSM_DATA_MEM_DATA(dataObj)->curbrk + size) >=
            DSM_DATA_MEM_DATA(dataObj)->top)
        {
            return (void *)MORECORE_FAILURE;
        }
        else
        {
            void *ret;

            ret = DSM_DATA_MEM_DATA(dataObj)->curbrk;

            DSM_DATA_MEM_DATA(dataObj)->curbrk += size;

            return ret;
        }
    }
}

/*
 * MAIN CONTROL OBJECT:
 *
 *  There is exactly one instance of this struct in this malloc.
 *  If you are adapting this malloc in a way that does NOT use a static
 *  malloc_state, you MUST explicitly zero-fill it before using. This
 *  malloc relies on the property that malloc_state is initialized to
 *  all zeroes (as is true of C statics).
 *
 * NOTE: for DSM, the get_malloc_state macro has a different implementation.
 *
 * static struct malloc_state av_;  * never directly referenced
 */

/*
 *  All uses of av_ are via get_malloc_state(dataObj).
 *  At most one "call" to get_malloc_state is made per invocation of
 *  the public versions of malloc and free, but other routines
 *  that in turn invoke malloc and/or free may call more then once. 
 *  Also, it is called in check* routines if DEBUG is set.
 */
#define get_malloc_state(dataObj) (&DSM_DATA_MEM_DATA(dataObj)->state)

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Initialize a malloc_state struct.
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
 *      None.
 *
 *  Notes:
 *      This is called only from within MallocConsolidate, which needs
 *      be called in the same contexts anyway.  It is never called directly
 *      outside of MallocConsolidate because some optimizing compilers try
 *      to inline it at all call points, which turns out not to be an
 *      optimization at all. (Inlining it in MallocConsolidate is fine though.)
 *
 *  See Also:
 *****************************************************************************/
static void
MallocInitState(mstate av)
{
    int     i;
    mbinptr bin;
    
    /* Establish circular links for normal bins */
    for (i = 1; i < NBINS; ++i)
    {
        bin = bin_at(av,i);
        bin->fd = bin->bk = bin;
    }
    
    set_max_fast(av, DEFAULT_MXFAST);
  
    av->top            = initial_top(av);
    av->pagesize       = malloc_getpagesize;
}

/* 
 *  Other internal utilities operating on mstates
 */
static void*  SysMalloc(DSM_DataObject* dataObj, size_t, mstate);
static void   MallocConsolidate(DSM_DataObject* dataObj, mstate);

/*
 * Debugging support
 *
 * These routines make a number of assertions about the states
 * of data structures that should be true at all times. If any
 * are not true, it's very likely that a user program has somehow
 * trashed memory. (It's also possible that there is a coding error
 * in malloc. In which case, please report it!)
 */
#if ! DEBUG

#define check_chunk(D,P)
#define check_free_chunk(D,P)
#define check_inuse_chunk(D,P)
#define check_remalloced_chunk(D,P,S)
#define check_malloced_chunk(D,P,S)
#define check_malloc_state(D)

#else
#define check_chunk(D,P)                do_check_chunk(D,P)
#define check_free_chunk(D,P)           do_check_free_chunk(D,P)
#define check_inuse_chunk(D,P)          do_check_inuse_chunk(D,P)
#define check_remalloced_chunk(D,P,S)   do_check_remalloced_chunk(D,P,S)
#define check_malloced_chunk(D,P,S)     do_check_malloced_chunk(D,P,S)
#define check_malloc_state(D)           do_check_malloc_state(D)

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of all chunks
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
do_check_chunk(DSM_DataObject* dataObj, mchunkptr p)
{
    mstate av = get_malloc_state(dataObj);
    unsigned long sz = chunksize(p);
    /* min and max possible addresses assuming contiguous allocation */
    char* max_address = (char*)(av->top) + chunksize(av->top);
    char* min_address = max_address - av->sbrked_mem;
    
    /* Has legal address ... */
    if (p != av->top)
    {
        assert(((char*)p) >= min_address);

        assert(((char*)p + sz) <= ((char*)(av->top)));
    }
    else
    {
        /* top size is always at least MINSIZE */
        assert((unsigned long)(sz) >= MINSIZE);

        /* top predecessor always marked inuse */
        assert(prev_inuse(p));
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of free chunks
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
do_check_free_chunk(DSM_DataObject* dataObj, mchunkptr p)
{
    mstate av = get_malloc_state(dataObj);
    size_t sz = p->size & ~PREV_INUSE;
    mchunkptr next = chunk_at_offset(p, sz);
    
    do_check_chunk(dataObj, p);
    
    /* Chunk must claim to be free ... */
    assert(!inuse(p));
    
    /* Unless a special marker, must have OK fields */
    if ((unsigned long)(sz) >= MINSIZE)
    {
        assert((sz & MALLOC_ALIGN_MASK) == 0);
        assert(aligned_OK(chunk2mem(p)));

        /* ... matching footer field */
        assert(next->prev_size == sz);

        /* ... and is fully consolidated */
        assert(prev_inuse(p));
        assert (next == av->top || inuse(next));
        
        /* ... and has minimally sane links */
        assert(p->fd->bk == p);
        assert(p->bk->fd == p);
    }
    else /* markers are always of size SIZE_SZ */
    {
        assert(sz == SIZE_SZ);
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of inuse chunks
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
do_check_inuse_chunk(DSM_DataObject* dataObj, mchunkptr p)
{
    mstate av = get_malloc_state(dataObj);
    mchunkptr next;
    do_check_chunk(dataObj, p);
    
    /* Check whether it claims to be in use ... */
    assert(inuse(p));
    
    next = next_chunk(p);
    
    /*
     * ... and is surrounded by OK chunks.
     * Since more things can be checked with free chunks than inuse ones,
     * if an inuse chunk borders them and debug is on, it's worth doing them.
     */
    if (!prev_inuse(p))
    {
        /* Note that we cannot even look at prev unless it is not inuse */
        mchunkptr prv = prev_chunk(p);
        assert(next_chunk(prv) == p);
        do_check_free_chunk(dataObj, prv);
    }
    
    if (next == av->top)
    {
        assert(prev_inuse(next));
        assert(chunksize(next) >= MINSIZE);
    }
    else if (!inuse(next))
    {
        do_check_free_chunk(dataObj, next);
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of chunks recycled from fastbins
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
do_check_remalloced_chunk(DSM_DataObject* dataObj, mchunkptr p, size_t s)
{
    size_t sz = p->size & ~PREV_INUSE;
    
    do_check_inuse_chunk(dataObj, p);
    
    /* Legal size ... */
    assert((sz & MALLOC_ALIGN_MASK) == 0);
    assert((unsigned long)(sz) >= MINSIZE);
    
    /* ... and alignment */
    assert(aligned_OK(chunk2mem(p)));
    
    /* chunk is less than MINSIZE more than request */
    assert((long)(sz) - (long)(s) >= 0);
    assert((long)(sz) - (long)(s + MINSIZE) < 0);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of nonrecycled chunks at the point they are malloced
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
do_check_malloced_chunk(DSM_DataObject* dataObj, mchunkptr p, size_t s)
{
    /* same as recycled case ... */
    do_check_remalloced_chunk(dataObj, p, s);
    
    /*
     * ... plus,  must obey implementation invariant that prev_inuse is
     * always true of any allocated chunk; i.e., that each allocated
     * chunk borders either a previously allocated and still in-use
     * chunk, or the base of its memory arena. This is ensured
     * by making all allocations from the the `lowest' part of any found
     * chunk.  This does not necessarily hold however for chunks
     * recycled via fastbins.
     */
    assert(prev_inuse(p));
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Properties of malloc_state.
 *
 *  Input Parameters:
 *      None.
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
 *      This may be useful for debugging malloc, as well as detecting user
 *      programmer errors that somehow write into malloc_state.
 *
 *      If you are extending or experimenting with this malloc, you can
 *      probably figure out how to hack this routine to print out or
 *      display chunk addresses, sizes, bins, and other instrumentation.
 *
 *  See Also:
 *****************************************************************************/
static void
do_check_malloc_state(DSM_DataObject* dataObj)
{
    mstate av = get_malloc_state(dataObj);
    int i;
    mchunkptr p;
    mchunkptr q;
    mbinptr b;
    unsigned int binbit;
    int empty;
    unsigned int idx;
    size_t size;
    unsigned long total = 0;
    int max_fast_bin;
    
    /* internal size_t must be no wider than pointer type */
    assert(sizeof(size_t) <= sizeof(char*));
    
    /* alignment is a power of 2 */
    assert((MALLOC_ALIGNMENT & (MALLOC_ALIGNMENT-1)) == 0);
    
    /* cannot run remaining checks until fully initialized */
    if (av->top == 0 || av->top == initial_top(av))
    {
        return;
    }
    
    /* pagesize is a power of 2 */
    assert((av->pagesize & (av->pagesize-1)) == 0);
    
    /* properties of fastbins */
    
    /* max_fast is in allowed range */
    assert((av->max_fast & ~1) <= request2size(MAX_FAST_SIZE));
    
    max_fast_bin = fastbin_index(av->max_fast);
    
    for (i = 0; i < NFASTBINS; ++i)
    {
        p = av->fastbins[i];
        
        /* all bins past max_fast are empty */
        if (i > max_fast_bin)
        {
            assert(p == 0);
        }
        
        while (p != 0)
        {
            /* each chunk claims to be inuse */
            do_check_inuse_chunk(dataObj, p);
            total += chunksize(p);
            
            /* chunk belongs in this bin */
            assert(fastbin_index(chunksize(p)) == (unsigned)i);
            p = p->fd;
        }
    }
    
    if (total != 0)
    {
        assert(have_fastchunks(av));
    }
    else if (!have_fastchunks(av))
    {
        assert(total == 0);
    }
    
    /* check normal bins */
    for (i = 1; i < NBINS; ++i)
    {
        b = bin_at(av,i);
        
        /* binmap is accurate (except for bin 1 == unsorted_chunks) */
        if (i >= 2)
        {
            binbit = get_binmap(av,i);
            empty = last(b) == b;
            if (!binbit)
            {
                assert(empty);
            }
            else if (!empty)
            {
                assert(binbit);
            }
        }
        
        for (p = last(b); p != b; p = p->bk)
        {
            /* each chunk claims to be free */
            do_check_free_chunk(dataObj, p);
            size = chunksize(p);
            total += size;
            
            if (i >= 2)
            {
                /* chunk belongs in bin */
                idx = bin_index(size);
                assert(idx == (unsigned)i);
                /* lists are sorted */
                assert(p->bk == b || 
                    (unsigned long)chunksize(p->bk) >= (unsigned long)chunksize(p));
            }
            
            /* chunk is followed by a legal chain of inuse chunks */
            for (q = next_chunk(p);
                 (q != av->top && inuse(q) && 
                  (unsigned long)(chunksize(q)) >= MINSIZE);
                 q = next_chunk(q))
            {
                do_check_inuse_chunk(dataObj, q);
            }
        }
    }
    
    /* top chunk is OK */
    check_chunk(dataObj, av->top);
    
    /* sanity checks for statistics */
    assert(total <= (unsigned long)(av->max_total_mem));
    
    assert((unsigned long)(av->sbrked_mem) <=
        (unsigned long)(av->max_sbrked_mem));
    
    assert((unsigned long)(av->max_total_mem) >=
        (unsigned long)(av->sbrked_mem));
}
#endif


/* ----------- Routines dealing with system allocation -------------- */

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      SysMalloc handles malloc cases requiring more memory from the system.
 *      On entry, it is assumed that av->top does not have enough
 *      space to service request for nb bytes, thus requiring that av->top
 *      be extended or replaced.
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void *
SysMalloc(DSM_DataObject* dataObj, size_t nb, mstate av)
{
    mchunkptr       old_top;        /* incoming value of av->top */
    size_t          old_size;       /* its size */
    char*           old_end;        /* its end address */
    long            size;           /* arg to first MORECORE or mmap call */
    char*           brk;            /* return value from MORECORE */
    long            correction;     /* arg to 2nd MORECORE call */
    char*           snd_brk;        /* 2nd return val */
    size_t          front_misalign; /* unusable bytes at front of new space */
    size_t          end_misalign;   /* partial page left at end of new space */
    char*           aligned_brk;    /* aligned offset into brk */
    mchunkptr       p;              /* the allocated/returned chunk */
    mchunkptr       remainder;      /* remainder from allocation */
    unsigned long   remainder_size; /* its size */
    unsigned long   sum;            /* for updating stats */
    size_t          pagemask  = av->pagesize - 1;
    
    /* Record incoming configuration of top */
    old_top  = av->top;
    old_size = chunksize(old_top);
    old_end  = (char*)(chunk_at_offset(old_top, old_size));
    
    brk = snd_brk = (char*)(MORECORE_FAILURE); 
    
    /* 
     *  If not the first time through, we require old_size to be
     *  at least MINSIZE and to have prev_inuse set.
     */
    assert((old_top == initial_top(av) && old_size == 0) || 
        ((unsigned long) (old_size) >= MINSIZE &&
        prev_inuse(old_top)));
    
    /* Precondition: not enough current space to satisfy nb request */
    assert((unsigned long)(old_size) < (unsigned long)(nb + MINSIZE));
    
    /* Precondition: all fastbins are consolidated */
    assert(!have_fastchunks(av));
    
    /* Request enough space for nb + pad + overhead */
    size = nb + MINSIZE;
    
    /*
     * If contiguous, we can subtract out existing space that we hope to
     * combine with new space. We add it back later only if
     * we don't actually get contiguous space.
     */
    size -= old_size;
    
    /*
     * Round to a multiple of page size.
     * If MORECORE is not contiguous, this ensures that we only call it
     * with whole-page arguments.  And if MORECORE is contiguous and
     * this is not first time through, this preserves page-alignment of
     * previous calls. Otherwise, we correct to page-align below.
     */
    size = (size + pagemask) & ~pagemask;
    
    /*
     * Don't try to call MORECORE if argument is so big as to appear
     * negative. Note that since mmap takes size_t arg, it may succeed
     * below even if we cannot call MORECORE.
     */
    if (size > 0) 
    {
        brk = (char*)(MORECORE(dataObj, size));
    }
    
    if (brk != (char*)(MORECORE_FAILURE))
    {
        av->sbrked_mem += size;
        
        /*
         * If MORECORE extends previous space, we can likewise extend top size.
         */
        if (brk == old_end && snd_brk == (char*)(MORECORE_FAILURE))
        {
            set_head(old_top, (size + old_size) | PREV_INUSE);
        }
        /*
         * Otherwise, make adjustments:
         * 
         * * If the first time through or noncontiguous, we need to call sbrk
         *   just to find out where the end of memory lies.
         *
         * * We need to ensure that all returned chunks from malloc will meet
         *   MALLOC_ALIGNMENT
         *
         * * If there was an intervening foreign sbrk, we need to adjust sbrk
         *   request size to account for fact that we will not be able to
         *   combine new space with existing space in old_top.
         *
         * * Almost all systems internally allocate whole pages at a time, in
         *   which case we might as well use the whole last page of request.
         *   So we allocate enough more memory to hit a page boundary now,
         *   which in turn causes future contiguous calls to page-align.
         */
        else
        {
            front_misalign = 0;
            end_misalign = 0;
            correction = 0;
            aligned_brk = brk;
            
            /* handle contiguous cases */
            /* Guarantee alignment of first new chunk made from this space */
            front_misalign = (size_t)chunk2mem(brk) & MALLOC_ALIGN_MASK;
            if (front_misalign > 0)
            {
                /*
                 * Skip over some bytes to arrive at an aligned position.
                 * We don't need to specially mark these wasted front bytes.
                 * They will never be accessed anyway because
                 * prev_inuse of av->top (and any chunk created from its start)
                 * is always true after initialization.
                 */
                correction = MALLOC_ALIGNMENT - front_misalign;
                aligned_brk += correction;
            }
            
            /*
             * If this isn't adjacent to existing space, then we will not
             * be able to merge with old_top space, so must add to 2nd request.
             */
            correction += old_size;
            
            /* Extend the end address to hit a page boundary */
            end_misalign = (size_t)(brk + size + correction);
            correction += ((end_misalign + pagemask) & ~pagemask) - end_misalign;
            
            assert(correction >= 0);
            snd_brk = (char*)(MORECORE(dataObj, correction));
            
            /*
             * If can't allocate correction, try to at least find out current
             * brk.  It might be enough to proceed without failing.
             * 
             * Note that if second sbrk did NOT fail, we assume that space
             * is contiguous with first sbrk. This is a safe assumption unless
             * program is multithreaded but doesn't use locks and a foreign sbrk
             * occurred between our first and second calls.
             */
            if (snd_brk == (char*)(MORECORE_FAILURE))
            {
                correction = 0;
                snd_brk = (char*)(MORECORE(dataObj, 0));
            }
            
            /* Adjust top based on results of second sbrk */
            if (snd_brk != (char*)(MORECORE_FAILURE))
            {
                av->top = (mchunkptr)aligned_brk;

                set_head(av->top, (snd_brk - aligned_brk + correction) |
                                   PREV_INUSE);

                av->sbrked_mem += correction;
                
                /*
                 * If not the first time through, we either have a
                 * gap due to foreign sbrk or a non-contiguous region.  Insert a
                 * double fencepost at old_top to prevent consolidation with space
                 * we don't own. These fenceposts are artificial chunks that are
                 * marked as inuse and are in any case too small to use.  We need
                 * two to make sizes and alignments work out.
                 */
                if (old_size != 0)
                {
                    /* 
                     *  Shrink old_top to insert fenceposts, keeping size a
                     *  multiple of MALLOC_ALIGNMENT. We know there is at least
                     *  enough space in old_top to do this.
                     */
                    old_size = (old_size - 3*SIZE_SZ) & ~MALLOC_ALIGN_MASK;
                    set_head(old_top, old_size | PREV_INUSE);
                    
                    /*
                     * Note that the following assignments completely overwrite
                     * old_top when old_size was previously MINSIZE.  This is
                     * intentional. We need the fencepost, even if old_top otherwise gets
                     * lost.
                     */
                    chunk_at_offset(old_top, old_size)->size =
                        SIZE_SZ|PREV_INUSE;
                    
                    chunk_at_offset(old_top, old_size + SIZE_SZ)->size =
                        SIZE_SZ|PREV_INUSE;
                    
                    /* If possible, release the rest. */
                    if (old_size >= MINSIZE)
                    {
                        dlfree(dataObj, chunk2mem(old_top));
                    }
                }
            }
        }
        
        /* Update statistics */
        sum = av->sbrked_mem;
        if (sum > (unsigned long)(av->max_sbrked_mem))
        {
            av->max_sbrked_mem = sum;
        }
        
        if (sum > (unsigned long)(av->max_total_mem))
        {
            av->max_total_mem = sum;
        }
        
        check_malloc_state(dataObj);
        
        /* finally, do the allocation */
        p = av->top;
        size = chunksize(p);
        
        /* check that one of the above allocation paths succeeded */
        if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(p, nb);

            av->top = remainder;
            
            set_head(p, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            
            check_malloced_chunk(dataObj, p, nb);
            
            return chunk2mem(p);
        }
    }
  
    /* catch all failure paths */
    return 0;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      allocate space
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void *
dlmalloc(DSM_DataObject* dataObj, size_t bytes)
{
    mstate av = get_malloc_state(dataObj);
    size_t          nb;               /* normalized request size */
    unsigned int    idx;              /* associated bin index */
    mbinptr         bin;              /* associated bin */
    mfastbinptr*    fb;               /* associated fastbin */
    mchunkptr       victim;           /* inspected/selected chunk */
    size_t          size;             /* its size */
    int             victim_index;     /* its bin index */
    mchunkptr       remainder;        /* remainder from a split */
    unsigned long   remainder_size;   /* its size */
    unsigned int    block;            /* bit map traverser */
    unsigned int    bit;              /* bit map traverser */
    unsigned int    map;              /* current word of binmap */
    mchunkptr       fwd;              /* misc temp for linking */
    mchunkptr       bck;              /* misc temp for linking */
    
    /*
     * Convert request size to internal form by adding SIZE_SZ bytes
     * overhead plus possibly more to obtain necessary alignment and/or
     * to obtain a size of at least MINSIZE, the smallest allocatable
     * size. Also, checked_request2size traps (returning 0) request sizes
     * that are so large that they wrap around zero when padded and
     * aligned.
     */
    checked_request2size(bytes, nb);
    
    /*
     * If the size qualifies as a fastbin, first check corresponding bin.
     * This code is safe to execute even if av is not yet initialized, so we
     * can try it without checking, which saves some time on this fast path.
     */
    if ((unsigned long)(nb) <= (unsigned long)(av->max_fast))
    { 
        fb = &(av->fastbins[(fastbin_index(nb))]);
        
        if ( (victim = *fb) != 0)
        {
            *fb = victim->fd;

            check_remalloced_chunk(dataObj, victim, nb);
            return chunk2mem(victim);
        }
    }
    
    /*
     * If a small request, check regular bin.  Since these "smallbins"
     * hold one size each, no searching within bins is necessary.
     * (For a large request, we need to wait until unsorted chunks are
     * processed to find best fit. But for small ones, fits are exact
     * anyway, so we can check now, which is faster.)
     */
    if (in_smallbin_range(nb))
    {
        idx = smallbin_index(nb);
        bin = bin_at(av,idx);
        
        if ( (victim = last(bin)) != bin)
        {
            if (victim == 0) /* initialization check */
            {
                MallocConsolidate(dataObj, av);
            }
            else
            {
                bck = victim->bk;
                
                set_inuse_bit_at_offset(victim, nb);

                bin->bk = bck;
                bck->fd = bin;
                
                check_malloced_chunk(dataObj, victim, nb);
                
                return chunk2mem(victim);
            }
        }
    }
    /* 
     *  If this is a large request, consolidate fastbins before continuing.
     *  While it might look excessive to kill all fastbins before
     *  even seeing if there is space available, this avoids
     *  fragmentation problems normally associated with fastbins.
     *  Also, in practice, programs tend to have runs of either small or
     *  large requests, but less often mixtures, so consolidation is not 
     *  invoked all that often in most programs. And the programs that
     *  it is called frequently in otherwise tend to fragment.
     */
    else
    {
        idx = largebin_index(nb);
        
        if (have_fastchunks(av)) 
        {
            MallocConsolidate(dataObj, av);
        }
    }
    
    /*
     * Process recently freed or remaindered chunks, taking one only if
     * it is exact fit, or, if this a small request, the chunk is remainder from
     * the most recent non-exact fit.  Place other traversed chunks in
     * bins.  Note that this step is the only place in any routine where
     * chunks are placed in bins.
     *
     * The outer loop here is needed because we might not realize until
     * near the end of malloc that we should have consolidated, so must
     * do so and retry. This happens at most once, and only when we would
     * otherwise need to expand memory to service a "small" request.
     */
    for(;;)
    {    
        while ( (victim = unsorted_chunks(av)->bk) != unsorted_chunks(av))
        {
            bck = victim->bk;
            size = chunksize(victim);
            
            /* 
             *  If a small request, try to use last remainder if it is the
             *  only chunk in unsorted bin.  This helps promote locality for
             *  runs of consecutive small requests. This is the only
             *  exception to best-fit, and applies only when there is
             *  no exact fit for a small chunk.
             */
            if (in_smallbin_range(nb) && 
                bck == unsorted_chunks(av) &&
                victim == av->last_remainder &&
                (unsigned long)(size) > (unsigned long)(nb + MINSIZE))
            {
                /* split and reattach remainder */
                remainder_size = size - nb;
                remainder = chunk_at_offset(victim, nb);

                unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;

                av->last_remainder = remainder;

                remainder->bk = remainder->fd = unsorted_chunks(av);
                
                set_head(victim, nb | PREV_INUSE);
                set_head(remainder, remainder_size | PREV_INUSE);
                set_foot(remainder, remainder_size);
                
                check_malloced_chunk(dataObj, victim, nb);
                
                return chunk2mem(victim);
            }
            
            /* remove from unsorted list */
            unsorted_chunks(av)->bk = bck;
            bck->fd = unsorted_chunks(av);
            
            /* Take now instead of binning if exact fit */
            if (size == nb)
            {
                set_inuse_bit_at_offset(victim, size);
                check_malloced_chunk(dataObj, victim, nb);
                
                return chunk2mem(victim);
            }
            
            /* place chunk in bin */
            
            if (in_smallbin_range(size))
            {
                victim_index = smallbin_index(size);
                
                bck = bin_at(av, victim_index);
                fwd = bck->fd;
            }
            else
            {
                victim_index = largebin_index(size);
                
                bck = bin_at(av, victim_index);
                fwd = bck->fd;
                
                /* maintain large bins in sorted order */
                if (fwd != bck)
                {
                    size |= PREV_INUSE; /* Or with inuse bit to speed comparisons */

                    /* if smaller than smallest, bypass loop below */
                    if ((unsigned long)(size) <= (unsigned long)(bck->bk->size))
                    {
                        fwd = bck;
                        bck = bck->bk;
                    }
                    else
                    {
                        while ((unsigned long)(size) < (unsigned long)(fwd->size)) 
                        {
                            fwd = fwd->fd;
                        }
                        bck = fwd->bk;
                    }
                }
            }
            
            mark_bin(av, victim_index);
            
            victim->bk = bck;
            victim->fd = fwd;
            fwd->bk = victim;
            bck->fd = victim;
        }
        
        /*
         * If a large request, scan through the chunks of current bin in
         * sorted order to find smallest that fits.  This is the only step
         * where an unbounded number of chunks might be scanned without doing
         * anything useful with them. However the lists tend to be short.
         */
        if (!in_smallbin_range(nb))
        {
            bin = bin_at(av, idx);
            
            /* skip scan if empty or largest chunk is too small */
            if ((victim = last(bin)) != bin &&
                (unsigned long)(first(bin)->size) >= (unsigned long)(nb))
            {
                
                while (((unsigned long)(size = chunksize(victim)) < 
                    (unsigned long)(nb)))
                {
                    victim = victim->bk;
                }
                
                remainder_size = size - nb;
                unlink(victim, bck, fwd);
                
                /* Exhaust */
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;

                    remainder->bk = remainder->fd = unsorted_chunks(av);
                    
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                } 
            }
        }    
        
        /*
         * Search for a chunk by scanning bins, starting with next largest
         * bin. This search is strictly by best-fit; i.e., the smallest
         * (with ties going to approximately the least recently used) chunk
         * that fits is selected.
         * 
         * The bitmap avoids needing to check that most blocks are nonempty.
         * The particular case of skipping all bins during warm-up phases
         * when no chunks have been returned yet is faster than it might look.
         */
        ++idx;
        
        bin = bin_at(av,idx);
        block = idx2block(idx);
        map = av->binmap[block];
        bit = idx2bit(idx);
        
        for (;;)
        {
            
            /* Skip rest of block if there are no more set bits in this block.  */
            if (bit > map || bit == 0)
            {
                do
                {
                    if (++block >= BINMAPSIZE)  /* out of bins */
                    {
                        goto use_top;
                    }
                }
                while ( (map = av->binmap[block]) == 0);
                
                bin = bin_at(av, (block << BINMAPSHIFT));
                bit = 1;
            }
            
            /* Advance to bin with set bit. There must be one. */
            while ((bit & map) == 0)
            {
                bin = next_bin(bin);
                bit <<= 1;
                
                assert(bit != 0);
            }
            
            /* Inspect the bin. It is likely to be non-empty */
            victim = last(bin);
            
            /*  If a false alarm (empty bin), clear the bit. */
            if (victim == bin)
            {
                map &= ~bit;
                av->binmap[block] = map; /* Write through */
                bin = next_bin(bin);
                bit <<= 1;
            }
            else
            {
                size = chunksize(victim);
                
                /*  We know the first chunk in this bin is big enough to use. */
                assert((unsigned long)(size) >= (unsigned long)(nb));
                
                remainder_size = size - nb;
                
                /* unlink */
                bck = victim->bk;
                bin->bk = bck;
                bck->fd = bin;
                
                /* Exhaust */
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);

                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;

                    remainder->bk = remainder->fd = unsorted_chunks(av);

                    /* advertise as last remainder */
                    if (in_smallbin_range(nb)) 
                    {
                        av->last_remainder = remainder;
                    }
                    
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                }
            }
        }
        
use_top:    
        /*
         * If large enough, split off the chunk bordering the end of memory
         * (held in av->top). Note that this is in accord with the best-fit
         * search rule.  In effect, av->top is treated as larger (and thus
         * less well fitting) than any other available chunk since it can
         * be extended to be as large as necessary (up to system
         * limitations).
         *
         * We require that av->top always exists (i.e., has size >=
         * MINSIZE) after initialization, so if it would otherwise be
         * exhuasted by current request, it is replenished. (The main
         * reason for ensuring it exists is that we may need MINSIZE space
         * to put in fenceposts in SysMalloc.)
         */
        victim = av->top;
        size = chunksize(victim);
        
        if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(victim, nb);

            av->top = remainder;
            
            set_head(victim, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            
            check_malloced_chunk(dataObj, victim, nb);
            
            return chunk2mem(victim);
        }
        /*
         * If there is space available in fastbins, consolidate and retry,
         * to possibly avoid expanding memory. This can occur only if nb is
         * in smallbin range so we didn't consolidate upon entry.
         */
        else if (have_fastchunks(av))
        {
            assert(in_smallbin_range(nb));
            
            MallocConsolidate(dataObj, av);
            idx = smallbin_index(nb); /* restore original bin index */
        }
        /* 
         *  Otherwise, relay to handle system-dependent cases 
         */
        else 
        {
            return SysMalloc(dataObj, nb, av);    
        }
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      free space
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
dlfree(DSM_DataObject* dataObj, void* mem)
{
    mstate av = get_malloc_state(dataObj);
    
    mchunkptr       p;           /* chunk corresponding to mem */
    size_t          size;        /* its size */
    mfastbinptr*    fb;          /* associated fastbin */
    mchunkptr       nextchunk;   /* next contiguous chunk */
    size_t          nextsize;    /* its size */
    int             nextinuse;   /* true if nextchunk is used */
    size_t          prevsize;    /* size of previous contiguous chunk */
    mchunkptr       bck;         /* misc temp for linking */
    mchunkptr       fwd;         /* misc temp for linking */
    
    /* free(0) has no effect */
    if (mem != 0)
    {
        p = mem2chunk(mem);
        size = chunksize(p);
        
        check_inuse_chunk(dataObj, p);
        
        /*
         * If eligible, place chunk on a fastbin so it can be found
         * and used quickly in malloc.
         */
        if ((unsigned long)(size) <= (unsigned long)(av->max_fast))
        {
            set_fastchunks(av);
            
            fb = &(av->fastbins[fastbin_index(size)]);

            p->fd = *fb;
            *fb = p;
        }
        /*
         *  Consolidate other non-mmapped chunks as they arrive.
         */
        else
        {
            nextchunk = chunk_at_offset(p, size);
            nextsize = chunksize(nextchunk);
            
            /* consolidate backward */
            if (!prev_inuse(p))
            {
                prevsize = p->prev_size;
                size += prevsize;
                
                p = chunk_at_offset(p, -((long) prevsize));
                
                unlink(p, bck, fwd);
            }
            
            if (nextchunk != av->top)
            {
                /* get and clear inuse bit */
                nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                set_head(nextchunk, nextsize);
                
                /* consolidate forward */
                if (!nextinuse)
                {
                    unlink(nextchunk, bck, fwd);
                    
                    size += nextsize;
                }
                
                /*
                 * Place the chunk in unsorted chunk list. Chunks are
                 * not placed into regular bins until after they have
                 * been given one chance to be used in malloc.
                 */
                bck = unsorted_chunks(av);
                fwd = bck->fd;

                p->bk = bck;
                p->fd = fwd;
                bck->fd = p;
                fwd->bk = p;
                
                set_head(p, size | PREV_INUSE);
                set_foot(p, size);
                
                check_free_chunk(dataObj, p);
            }
            /*
             *  If the chunk borders the current high end of memory,
             *  consolidate into top
             */
            else
            {
                size += nextsize;
                set_head(p, size | PREV_INUSE);

                av->top = p;

                check_chunk(dataObj, p);
            }

            /*
             * If freeing a large space, consolidate possibly-surrounding
             * chunks. Then, if the total unused topmost memory exceeds trim
             * threshold, ask malloc_trim to reduce top.
             *
             * Unless max_fast is 0, we don't know if there are fastbins
             * bordering top, so we cannot tell for sure whether threshold
             * has been reached unless fastbins are consolidated.  But we
             * don't want to consolidate on each free.  As a compromise,
             * consolidation is performed if FASTBIN_CONSOLIDATION_THRESHOLD
             * is reached.
             */
            if ((unsigned long)(size) >= FASTBIN_CONSOLIDATION_THRESHOLD)
            { 
                if (have_fastchunks(av)) 
                {
                    MallocConsolidate(dataObj, av);
                }
            }
        }
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      MallocConsolidate is a specialized version of free() that tears
 *      down chunks held in fastbins.  Free itself cannot be used for this
 *      purpose since, among other things, it might place chunks back onto
 *      fastbins.  So, instead, we need to use a minor variant of the same
 *      code.
 * 
 *      Also, because this routine needs to be called the first time through
 *      malloc anyway, it turns out to be the perfect place to trigger
 *      initialization code.
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void
MallocConsolidate(DSM_DataObject* dataObj, mstate av)
{
    mfastbinptr*    fb;                 /* current fastbin being consolidated */
    mfastbinptr*    maxfb;              /* last fastbin (for loop control) */
    mchunkptr       p;                  /* current chunk being consolidated */
    mchunkptr       nextp;              /* next chunk to consolidate */
    mchunkptr       unsorted_bin;       /* bin header */
    mchunkptr       first_unsorted;     /* chunk to link to */
    
    /* These have same use as in free() */
    mchunkptr       nextchunk;
    size_t size;
    size_t nextsize;
    size_t prevsize;
    int             nextinuse;
    mchunkptr       bck;
    mchunkptr       fwd;
    
    /*
     * If max_fast is 0, we know that av hasn't
     * yet been initialized, in which case do so below
     */
    if (av->max_fast != 0)
    {
        clear_fastchunks(av);
        
        unsorted_bin = unsorted_chunks(av);
        
        /*
         * Remove each chunk from fast bin and consolidate it, placing it
         * then in unsorted bin. Among other reasons for doing this,
         * placing in unsorted bin avoids needing to calculate actual bins
         * until malloc is sure that chunks aren't immediately going to be
         * reused anyway.
         */
        maxfb = &(av->fastbins[fastbin_index(av->max_fast)]);
        fb = &(av->fastbins[0]);
        
        do
        {
            if ( (p = *fb) != 0)
            {
                *fb = 0;
                
                do
                {
                    check_inuse_chunk(dataObj, p);
                    
                    nextp = p->fd;
                    
                    /* Slightly streamlined version of consolidation code in free() */
                    size = p->size & ~PREV_INUSE;
                    nextchunk = chunk_at_offset(p, size);
                    nextsize = chunksize(nextchunk);
                    
                    if (!prev_inuse(p))
                    {
                        prevsize = p->prev_size;
                        size += prevsize;
                        p = chunk_at_offset(p, -((long) prevsize));
                        unlink(p, bck, fwd);
                    }
                    
                    if (nextchunk != av->top)
                    {
                        nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                        set_head(nextchunk, nextsize);
                        
                        if (!nextinuse)
                        {
                            size += nextsize;
                            unlink(nextchunk, bck, fwd);
                        }
                        
                        first_unsorted = unsorted_bin->fd;

                        unsorted_bin->fd = p;
                        first_unsorted->bk = p;
                        
                        set_head(p, size | PREV_INUSE);

                        p->bk = unsorted_bin;
                        p->fd = first_unsorted;

                        set_foot(p, size);
                    }
                    else
                    {
                        size += nextsize;
                        set_head(p, size | PREV_INUSE);

                        av->top = p;
                    }
                }
                while ( (p = nextp) != 0);
                
            }
        }
        while (fb++ != maxfb);
    }
    else
    {
        MallocInitState(av);
        
        check_malloc_state(dataObj);
    }
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      reallocate space
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void *
dlrealloc(DSM_DataObject* dataObj, void* oldmem, size_t bytes)
{
    mstate av = get_malloc_state(dataObj);
    size_t           nb;              /* padded request size */
    mchunkptr        oldp;            /* chunk corresponding to oldmem */
    size_t           oldsize;         /* its size */
    mchunkptr        newp;            /* chunk to return */
    size_t           newsize;         /* its size */
    void*            newmem;          /* corresponding user mem */
    mchunkptr        next;            /* next contiguous chunk after oldp */
    mchunkptr        remainder;       /* extra space at end of newp */
    unsigned long    remainder_size;  /* its size */
    mchunkptr        bck;             /* misc temp for linking */
    mchunkptr        fwd;             /* misc temp for linking */
    unsigned long    copysize;        /* bytes to copy */
    unsigned int     ncopies;         /* size_t words to copy */
    size_t*          s;               /* copy source */ 
    size_t*          d;               /* copy destination */
    
    /* realloc of null is supposed to be same as malloc */
    if (oldmem == 0)
    {
        return dlmalloc(dataObj, bytes);
    }
    
    checked_request2size(bytes, nb);
    
    oldp    = mem2chunk(oldmem);
    oldsize = chunksize(oldp);
    
    check_inuse_chunk(dataObj, oldp);
    
    if ((unsigned long)(oldsize) >= (unsigned long)(nb))
    {
        /* already big enough; split below */
        newp = oldp;
        newsize = oldsize;
    }
    else
    {
        next = chunk_at_offset(oldp, oldsize);
        
        /* Try to expand forward into top */
        if (next == av->top &&
            (unsigned long)(newsize = oldsize + chunksize(next)) >=
            (unsigned long)(nb + MINSIZE))
        {
            set_head_size(oldp, nb);

            av->top = chunk_at_offset(oldp, nb);
            
            set_head(av->top, (newsize - nb) | PREV_INUSE);
            
            return chunk2mem(oldp);
        }
        
        /* Try to expand forward into next chunk;  split off remainder below */
        else if (next != av->top && 
                 !inuse(next) &&
                 (unsigned long)(newsize = oldsize + chunksize(next)) >=
                 (unsigned long)(nb))
        {
            newp = oldp;
            unlink(next, bck, fwd);
        }
        /* allocate, copy, free */
        else
        {
            newmem = dlmalloc(dataObj, nb - MALLOC_ALIGN_MASK);
            if (newmem == 0)
            {
                return 0; /* propagate failure */
            }
            
            newp = mem2chunk(newmem);
            newsize = chunksize(newp);
            
            /*
            * Avoid copy if newp is next chunk after oldp.
            */
            if (newp == next)
            {
                newsize += oldsize;
                newp = oldp;
            }
            else
            {
                /*
                 * Unroll copy of <= 36 bytes (72 if 8byte sizes)
                 * We know that contents have an odd number of
                 * size_t-sized words; minimally 3.
                 */
                copysize = oldsize - SIZE_SZ;
                s = (size_t*)(oldmem);
                d = (size_t*)(newmem);
                ncopies = copysize / sizeof(size_t);
                assert(ncopies >= 3);
                
                if (ncopies > 9)
                {
                    MALLOC_COPY(d, s, copysize);
                }
                else
                {
                    *(d+0) = *(s+0);
                    *(d+1) = *(s+1);
                    *(d+2) = *(s+2);
                    if (ncopies > 4)
                    {
                        *(d+3) = *(s+3);
                        *(d+4) = *(s+4);
                        if (ncopies > 6)
                        {
                            *(d+5) = *(s+5);
                            *(d+6) = *(s+6);
                            if (ncopies > 8)
                            {
                                *(d+7) = *(s+7);
                                *(d+8) = *(s+8);
                            }
                        }
                    }
                }
                
                dlfree(dataObj, oldmem);
                
                check_inuse_chunk(dataObj, newp);
                
                return chunk2mem(newp);
            }
        }
        
        /* If possible, free extra space in old or extended chunk */
        assert((unsigned long)(newsize) >= (unsigned long)(nb));
        
        remainder_size = newsize - nb;
        
        if (remainder_size < MINSIZE) /* not enough extra to split off */
        {
            set_head_size(newp, newsize);
            set_inuse_bit_at_offset(newp, newsize);
        }
        else /* split remainder */
        {
            remainder = chunk_at_offset(newp, nb);
            
            set_head_size(newp, nb);
            set_head(remainder, remainder_size | PREV_INUSE);
            
            /* Mark remainder as inuse so free() won't complain */
            set_inuse_bit_at_offset(remainder, remainder_size);
            dlfree(dataObj, chunk2mem(remainder)); 
        }
        
        check_inuse_chunk(dataObj, newp);
        
        return chunk2mem(newp);
    }
  
    check_malloc_state(dataObj);
  
    return 0;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      allocate on a specific alignment space
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void *
dlmemalign(DSM_DataObject* dataObj, size_t alignment, size_t bytes)
{
    size_t          nb;             /* padded  request size */
    char*           m;              /* memory returned by malloc call */
    mchunkptr       p;              /* corresponding chunk */
    char*           brk;            /* alignment point within p */
    mchunkptr       newp;           /* chunk to return */
    size_t          newsize;        /* its size */
    size_t          leadsize;       /* leading space before alignment point */
    mchunkptr       remainder;      /* spare room at end to split off */
    unsigned long   remainder_size; /* its size */
    size_t          size;
    
    /* If need less alignment than we give anyway, just relay to malloc */
    if (alignment <= MALLOC_ALIGNMENT)
    {
        return dlmalloc(dataObj, bytes);
    }
    
    /* Otherwise, ensure that it is at least a minimum chunk size */
    if (alignment <  MINSIZE)
    {
        alignment = MINSIZE;
    }
    
    /* Make sure alignment is power of 2 (in case MINSIZE is not).  */
    if ((alignment & (alignment - 1)) != 0)
    {
        size_t a = MALLOC_ALIGNMENT * 2;
        
        while ((unsigned long)a < (unsigned long)alignment)
        {
            a <<= 1;
        }
        
        alignment = a;
    }
    
    checked_request2size(bytes, nb);
    
    /*
     * Strategy: find a spot within that chunk that meets the alignment
     * request, and then possibly free the leading and trailing space.
     */
    /* Call malloc with worst case padding to hit alignment. */
    m  = (char *)(dlmalloc(dataObj, nb + alignment + MINSIZE));
    
    if (m == 0)
    {
        return 0; /* propagate failure */
    }
    
    p = mem2chunk(m);
    
    if ((((unsigned long)(m)) % alignment) != 0) /* misaligned */
    {
        /*
         * Find an aligned spot inside chunk.  Since we need to give back
         * leading space in a chunk of at least MINSIZE, if the first
         * calculation places us at a spot with less than MINSIZE leader,
         * we can move to the next aligned spot -- we've allocated enough
         * total room so that this is always possible.
         */
        brk = (char*)mem2chunk(((unsigned long)(m + alignment - 1)) &
            -((signed long) alignment));
        
        if ((unsigned long)(brk - (char*)(p)) < MINSIZE)
        {
            brk += alignment;
        }
        
        newp = (mchunkptr)brk;
        leadsize = brk - (char*)(p);
        newsize = chunksize(p) - leadsize;
        
        /* Otherwise, give back leader, use the rest */
        set_head(newp, newsize | PREV_INUSE);
        set_inuse_bit_at_offset(newp, newsize);
        set_head_size(p, leadsize);
        
        dlfree(dataObj, chunk2mem(p));
        
        p = newp;
        
        assert (newsize >= nb &&
            (((unsigned long)(chunk2mem(p))) % alignment) == 0);
    }
    
    /* Also give back spare room at the end */
    size = chunksize(p);
    if ((unsigned long)(size) > (unsigned long)(nb + MINSIZE))
    {
        remainder_size = size - nb;
        remainder = chunk_at_offset(p, nb);
        
        set_head(remainder, remainder_size | PREV_INUSE);
        set_head_size(p, nb);
        
        dlfree(dataObj, chunk2mem(remainder));
    }
    
    check_inuse_chunk(dataObj, p);
    
    return chunk2mem(p);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      allocate space and clear it
 *
 *  Input Parameters:
 *      None.
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
 *****************************************************************************/
static void *
dlcalloc(DSM_DataObject* dataObj, size_t n_elements, size_t elem_size)
{
    mchunkptr p;
    unsigned long clearsize;
    unsigned long nclears;
    size_t* d;
    
    void* mem = dlmalloc(dataObj, n_elements * elem_size);
    
    if (mem != 0)
    {
        p = mem2chunk(mem);
        
        /*
         * Unroll clear of <= 36 bytes (72 if 8byte sizes)
         * We know that contents have an odd number of
         * size_t-sized words; minimally 3.
         */
        d = (size_t*)mem;
        clearsize = chunksize(p) - SIZE_SZ;
        nclears = clearsize / sizeof(size_t);
        assert(nclears >= 3);
        
        if (nclears > 9)
        {
            MALLOC_ZERO(d, clearsize);
        }
        else
        {
            *(d+0) = 0;
            *(d+1) = 0;
            *(d+2) = 0;
            if (nclears > 4)
            {
                *(d+3) = 0;
                *(d+4) = 0;
                if (nclears > 6)
                {
                    *(d+5) = 0;
                    *(d+6) = 0;
                    if (nclears > 8)
                    {
                        *(d+7) = 0;
                        *(d+8) = 0;
                    }
                }
            }
        }
    }

    return mem;
}

/******************************************************************************
 ******************************************************************************
 **
 ** DSMHASH class (table manager).
 **
 */

/*
 * DSM POSIX operations to the table manager hash table are applied in the exact
 * same order in all the (active) processes (guaranteed by GCS total order).
 */

/*
 * DSMHASH object definition.
 */

typedef struct
{
    DSM_DataObject* dataObj;
}
DSMHASH_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    HASH_TableObjectPart    hash;
    DSMHASH_ObjectPart      dsm;
}
DSMHASH_TableRec, *DSMHASH_Table;

#define DSMHASH_DATA_OBJECT(x) \
    (((DSMHASH_Table)(x))->dsm.dataObj)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Allocate for the DSM HASH
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      n - number of objects
 *      size - size of each object
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
 ****************************************************************************/
static void *
HashAlloc(HASH_Table db, ITS_UINT n, ITS_UINT size)
{
    DSM_DataObject* dataObj = DSMHASH_DATA_OBJECT(db);

    return dlcalloc(dataObj, n, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for the DSM HASH
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      data - pointer to region to free
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
 ****************************************************************************/
static void
HashFree(HASH_Table db, void *data)
{
    DSM_DataObject* dataObj = DSMHASH_DATA_OBJECT(db);

    dlfree(dataObj, data);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      get the next unique context.  Pretty simple algo, the table takes
 *      care of the compaction.
 *
 *  Input Parameters:
 *      db - the hash table to generate the unique key for.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The next unique context value.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static ITS_INT
UniqueKey(HASH_Table db)
{
    return ITS_EINVALIDARGS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 *****************************************************************************/
static int
HashCreateTable(ITS_Object obj, va_list args)
{
    DSMHASH_Table db = (DSMHASH_Table)obj;
    DSM_DataObject* dataObj;

    ITS_TRACE_DEBUG(("CreateTable:\n"));

    dataObj = va_arg(args, DSM_DataObject*);

    DSMHASH_DATA_OBJECT(db) = dataObj;

    return (ITS_SUCCESS);
}

static HASH_ClassRec itsDSMHASH_ClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        sizeof(DSMHASH_TableRec),           /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        HASH_CLASS_NAME,                    /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        HashCreateTable,                    /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* hash part */
    {
        UniqueKey,                          /* unique key generator     */
        NULL,                               /* add entry method         */
        NULL,                               /* find entry method        */
        NULL,                               /* delete entry method      */
        NULL,                               /* VTable dump method       */
        NULL,                               /* VTable iterate method    */
        HashAlloc,                          /* allocation method        */
        HashFree                            /* free method              */
    }
};

static ITS_Class itsDSMHASH_Class = (ITS_Class)&itsDSMHASH_ClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSMSPLAY class (table manager).
 **
 */

/*
 * DSM POSIX operations to the table manager hash table are applied in the exact
 * same order in all the (active) processes (guaranteed by GCS total order).
 */

/*
 * DSMHASH object definition.
 */

typedef struct
{
    DSM_DataObject* dataObj;
}
DSMSPLAY_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    SPLAY_ObjectPart        splay;
    DSMSPLAY_ObjectPart     dsm;
}
DSMSPLAY_TreeRec, *DSMSPLAY_Tree;

#define DSMSPLAY_DATA_OBJECT(x) \
    (((DSMSPLAY_Tree)(x))->dsm.dataObj)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Allocate for the DSM SPLAY
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      n - number of objects
 *      size - size of each object
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
 ****************************************************************************/
static void *
SplayAlloc(SPLAY_Tree db, ITS_UINT n, ITS_UINT size)
{
    DSM_DataObject* dataObj = DSMSPLAY_DATA_OBJECT(db);

    return dlcalloc(dataObj, n, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for the DSM SPLAY
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      data - pointer to region to free
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
 ****************************************************************************/
static void
SplayFree(SPLAY_Tree db, void *data)
{
    DSM_DataObject* dataObj = DSMSPLAY_DATA_OBJECT(db);

    dlfree(dataObj, data);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 *****************************************************************************/
static int
SplayCreateTable(ITS_Object obj, va_list args)
{
    DSMSPLAY_Tree db = (DSMSPLAY_Tree)obj;
    DSM_DataObject* dataObj;

    ITS_TRACE_DEBUG(("CreateTable:\n"));

    dataObj = va_arg(args, DSM_DataObject*);

    DSMSPLAY_DATA_OBJECT(db) = dataObj;

    return (ITS_SUCCESS);
}

static SPLAY_ClassRec itsDSMSPLAY_ClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        sizeof(DSMSPLAY_TreeRec),           /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        SPLAY_CLASS_NAME,                   /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        SplayCreateTable,                   /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* splay part */
    {
        NULL,                               /* insert entry method      */
        NULL,                               /* destroy entry method     */
        NULL,                               /* find nearest entry method*/
        NULL,                               /* find exact entry method  */
        NULL,                               /* iterate entry method     */
        NULL,                               /* riterate entry method    */
        SplayAlloc,                         /* allocation method        */
        SplayFree                           /* free method              */
    }
};

static ITS_Class itsDSMSPLAY_Class = (ITS_Class)&itsDSMSPLAY_ClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSMREDBLACK class (table manager).
 **
 */

/*
 * DSM POSIX operations to the table manager hash table are applied in the exact
 * same order in all the (active) processes (guaranteed by GCS total order).
 */

/*
 * DSMHASH object definition.
 */

typedef struct
{
    DSM_DataObject* dataObj;
}
DSMREDBLACK_ObjectPart;

typedef struct
{
    ITS_CoreObjectPart      core;
    REDBLACK_ObjectPart     redBlack;
    DSMREDBLACK_ObjectPart  dsm;
}
DSMREDBLACK_TreeRec, *DSMREDBLACK_Tree;

#define DSMREDBLACK_DATA_OBJECT(x) \
    (((DSMREDBLACK_Tree)(x))->dsm.dataObj)

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Allocate for the DSM REDBLACK
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      n - number of objects
 *      size - size of each object
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
 ****************************************************************************/
static void *
RedBlackAlloc(REDBLACK_Tree db, ITS_UINT n, ITS_UINT size)
{
    DSM_DataObject* dataObj = DSMREDBLACK_DATA_OBJECT(db);

    return dlcalloc(dataObj, n, size);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Free for the DSM REDBLACK
 *
 *  Input Parameters:
 *      db - hash table to allocate in
 *      data - pointer to region to free
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
 ****************************************************************************/
static void
RedBlackFree(REDBLACK_Tree db, void *data)
{
    DSM_DataObject* dataObj = DSMREDBLACK_DATA_OBJECT(db);

    dlfree(dataObj, data);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Create the hash table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      pdb = the address of the hash table to create.
 *
 *  Return Value:
 *      If the table is created successfully, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *      HASH_DeleteTable()
 *****************************************************************************/
static int
RedBlackCreateTable(ITS_Object obj, va_list args)
{
    DSMREDBLACK_Tree db = (DSMREDBLACK_Tree)obj;
    DSM_DataObject* dataObj;

    ITS_TRACE_DEBUG(("CreateTable:\n"));

    dataObj = va_arg(args, DSM_DataObject*);

    DSMREDBLACK_DATA_OBJECT(db) = dataObj;

    return (ITS_SUCCESS);
}

static REDBLACK_ClassRec itsDSMREDBLACK_ClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        sizeof(DSMREDBLACK_TreeRec),        /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        REDBLACK_CLASS_NAME,                /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        RedBlackCreateTable,                /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* redblack part */
    {
        NULL,                               /* find nearest entry method*/
        NULL,                               /* find exact entry method  */
        NULL,                               /* insert before entry method*/
        NULL,                               /* insert after entry method*/
        NULL,                               /* insert entry method      */
        NULL,                               /* destroy entry method     */
        NULL,                               /* iterate entry method     */
        NULL,                               /* riterate entry method    */
        RedBlackAlloc,                      /* allocation method        */
        RedBlackFree                        /* free method              */
    }
};

static ITS_Class itsDSMREDBLACK_Class = (ITS_Class)&itsDSMREDBLACK_ClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (POSIX) Data class.
 **
 */

static int
CheckCreator(DSM_CoreObject* coreObj,
             DSM_InstObject* instObj,
             DSM_DataObject* dataObj)
{
    if (kill(DSM_DATA_DSM_INFO(dataObj).pid, 0) < 0 &&
        errno == ESRCH)
    {
        DSM_DATA_DSM_INFO(dataObj).pid = getpid();
        DSM_DATA_FIRST(dataObj) = ITS_TRUE;
    }
    
    return (ITS_SUCCESS);
}

static int
DsmInfoCreate(DSM_CoreObject* coreObj,
              DSM_InstObject* instObj,
              DSM_DataObject* dataObj)
{
    int ret;

    ret = MUTEX_CreateMutex(&DSM_DATA_DSM_INFO(dataObj).lock, 0);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return (ret);
    }

#if !defined(WIN32)
    /* if we're the creator (otherwise this wouldn't get called,
     * we own the segment.  Barring error checking. */
    DSM_DATA_DSM_INFO(dataObj).pid = getpid();
#endif
    
    return (ITS_SUCCESS);
}

static int
DsmInfoDestroy(DSM_CoreObject* coreObj,
               DSM_InstObject* instObj,
               DSM_DataObject* dataObj)
{
    MUTEX_DeleteMutex(&DSM_DATA_DSM_INFO(dataObj).lock);

    return (ITS_SUCCESS);
}

static int
MemCmp(void *k1, ITS_UINT k1Len, void *k2, ITS_UINT k2Len)
{
    return memcmp(k1, k2, k1Len > k2Len ? k1Len : k2Len);
}

static int
FreeTablesRange(DSM_DataObject* dataObj, ITS_UINT max)
{
    ITS_UINT i;

    for (i = 0; i < max; i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            BHASH_DeleteTable(DSM_DATA_TABLES(dataObj)[i].table.hash);
            dlfree(dataObj, DSM_DATA_TABLES(dataObj)[i].table.splay);
            DSM_DATA_TABLES(dataObj)[i].table.hash = NULL;
            break;

        case DSM_TABLE_REDBLACK:
            RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
            dlfree(dataObj, DSM_DATA_TABLES(dataObj)[i].table.tree);
            DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
            break;

        case DSM_TABLE_SPLAY:
            SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
            dlfree(dataObj, DSM_DATA_TABLES(dataObj)[i].table.splay);
            DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
            break;

        default:
            break;
        }
    }

    return (ITS_SUCCESS);
}

static int
TablesCreate(DSM_CoreObject* coreObj,
             DSM_InstObject* instObj,
             DSM_DataObject* dataObj)
{
    ITS_UINT i;
    ITS_Object ptr = NULL;

    DSM_DATA_TABLES(dataObj) =
        dlcalloc(dataObj, DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_Table));
    if (DSM_DATA_TABLES(dataObj) == NULL)
    {
        /* TODO: add trace. */

        return (ITS_ENOMEM);
    }

    /* FIXME: Right now, the calloc() forces all the table types to DSM_TABLE_HASH */

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            DSM_DATA_TABLES(dataObj)[i].table.hash =
                (HASH_Table)dlcalloc(dataObj, 1, sizeof(DSMHASH_TableRec));

            if (DSM_DATA_TABLES(dataObj)[i].table.hash != NULL)
            {
                ptr = ITS_ConstructObjectIn(DSM_DATA_TABLES(dataObj)[i].table.hash,
                                            itsDSMHASH_Class,
                                            ITS_TRUE,
                                            dataObj);
            }

            if (DSM_DATA_TABLES(dataObj)[i].table.hash == NULL ||
                ptr != (ITS_Object)DSM_DATA_TABLES(dataObj)[i].table.hash)
            {
                /* TODO: add trace. */

                FreeTablesRange(dataObj, i);

                return (ITS_ENOMEM);
            }
            break;

        case DSM_TABLE_REDBLACK:
            DSM_DATA_TABLES(dataObj)[i].table.tree =
                (REDBLACK_Tree)dlcalloc(dataObj, 1, sizeof(DSMREDBLACK_TreeRec));

            if (DSM_DATA_TABLES(dataObj)[i].table.tree != NULL)
            {
                ptr = ITS_ConstructObjectIn(DSM_DATA_TABLES(dataObj)[i].table.tree,
                                            itsDSMREDBLACK_Class,
                                            MemCmp, ITS_TRUE,
                                            dataObj);
            }

            if (DSM_DATA_TABLES(dataObj)[i].table.tree == NULL ||
                ptr != (ITS_Object)DSM_DATA_TABLES(dataObj)[i].table.tree)
            {
                /* TODO: add trace. */

                FreeTablesRange(dataObj, i);

                return (ITS_ENOMEM);
            }
            break;

        case DSM_TABLE_SPLAY:
            DSM_DATA_TABLES(dataObj)[i].table.splay =
                (SPLAY_Tree)dlcalloc(dataObj, 1, sizeof(DSMSPLAY_TreeRec));

            if (DSM_DATA_TABLES(dataObj)[i].table.splay != NULL)
            {
                ptr = ITS_ConstructObjectIn(DSM_DATA_TABLES(dataObj)[i].table.splay,
                                            itsDSMSPLAY_Class,
                                            MemCmp, ITS_TRUE,
                                            dataObj);
            }

            if (DSM_DATA_TABLES(dataObj)[i].table.splay == NULL ||
                ptr != (ITS_Object)DSM_DATA_TABLES(dataObj)[i].table.splay)
            {
                /* TODO: add trace. */

                FreeTablesRange(dataObj, i);

                return (ITS_ENOMEM);
            }
            break;

        default:
            /* FIXME: Trace */

            FreeTablesRange(dataObj, i);

            return (ITS_ENOMEM);
        }
    }

    return (ITS_SUCCESS);
}

static int
TablesDestroy(DSM_CoreObject* coreObj,
              DSM_InstObject* instObj,
              DSM_DataObject* dataObj)
{
    FreeTablesRange(dataObj, DSM_INST_MAX_NUM_TABLES(instObj));

    return (ITS_SUCCESS);
}

static int 
TablesInfoCreate(DSM_CoreObject* coreObj,
                 DSM_InstObject* instObj,
                 DSM_DataObject* dataObj)
{
    ITS_UINT i, j;
    int ret;

    DSM_DATA_TABLES_INFO(dataObj) =
        dlcalloc(dataObj, DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_TableInfo));
    if (DSM_DATA_TABLES_INFO(dataObj) == NULL)
    {
        /* TODO: add trace. */
        return (ITS_ENOMEM);
    }

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        ret = MUTEX_CreateMutex(&DSM_DATA_TABLES_INFO(dataObj)[i].lock, 0);
        if (ret != ITS_SUCCESS)
        {
            /* TODO: add trace. */

            for (j = 0; j < i; j++)
            {
                MUTEX_DeleteMutex(&DSM_DATA_TABLES_INFO(dataObj)[j].lock);
            }

            return (ret);
        }

        DSM_DATA_TABLES_INFO(dataObj)[i].entries = 0;
    }

    return (ITS_SUCCESS);
}

static int
TablesInfoDestroy(DSM_CoreObject* coreObj,
                  DSM_InstObject* instObj,
                  DSM_DataObject* dataObj)
{
    ITS_UINT i;

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        MUTEX_DeleteMutex(&DSM_DATA_TABLES_INFO(dataObj)[i].lock);
    }

    return (ITS_SUCCESS);
}

static int
GetSharedMem(DSM_CoreObject* coreObj,
             DSM_InstObject* instObj,
             DSM_DataObject* dataObj)
{
    void* ptr;
    int retry = 0;

    ITS_C_REQUIRE(dataObj != NULL);

#if defined(WIN32)

    ptr = VirtualAlloc((void*)DSM_INST_DSM_BASE_ADDRESS(instObj),
                       DSM_INST_DSM_SIZE(instObj),
                       MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, 
                       PAGE_READWRITE);
    if (ptr == NULL)
    {
        ITS_TRACE_ERROR((
            "MemDataCreate [FtGroupId: %u]: VirtualAlloc failed with "
            "GetLastError: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            GetLastError()));

        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to allocate DSM on Win32 system\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        DSM_DATA_SYS_MAP_ADDR(dataObj) = NULL;

        return (ITS_ENOMEM);
    }

    ITS_TRACE_DEBUG((
        "MemDataCreate [FtGroupId: %u]: VirtualAlloc succeeded: %u bytes at "
        "address 0x%X\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_INST_DSM_SIZE(instObj),
        ptr));

    DSM_DATA_SYS_MAP_ADDR(dataObj) = ptr;

#else /* !defined(WIN32) */

    /* create the segment */
retry:
    DSM_DATA_FD(dataObj) =
            shm_open(SHM_FILE, O_RDWR, S_IRUSR|S_IWUSR);
    
    /* doesn't exist yet? */
    if (DSM_DATA_FD(dataObj) < 0)
    {
        /* try to create it.  We might race with our peer, so do a retry. */
        DSM_DATA_FD(dataObj) =
                shm_open(SHM_FILE, O_CREAT|O_EXCL|O_TRUNC|O_RDWR,
                         S_IRUSR|S_IWUSR);
        
        if (DSM_DATA_FD(dataObj) < 0)
        {
            /* maybe we raced.  Try to reopen. */
            if (retry < DSM_MAX_RETRY)
            {
                retry++;
                
                TIMERS_Sleep(1);
                
                goto retry;
            }
            
            return (ITS_ENOMEM);
        }
        
        /* if we got here, we created the segment */
        DSM_DATA_FIRST(dataObj) = ITS_TRUE;
    }

    /* may need to trunc() here.  The docs are unclear on this point */
    
    /* map the segment in */    
    ptr = mmap((char*)DSM_INST_DSM_BASE_ADDRESS(instObj), 
               DSM_INST_DSM_SIZE(instObj),
               PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_FIXED,
               DSM_DATA_FD(dataObj),
               0);
    
    if (ptr == MAP_FAILED || ptr == NULL)
    {
        ITS_TRACE_ERROR((
            "MemDataCreate [FtGroupId: %u]: mmap for base %p failed with "
            "errno: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            DSM_INST_DSM_BASE_ADDRESS(instObj),
            errno));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to allocate DSM on Unix system\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        DSM_DATA_SYS_MAP_ADDR(dataObj) = NULL;
        
        return (ITS_ENOMEM);
    }

    ITS_TRACE_DEBUG((
        "MemDataCreate [FtGroupId: %u]: mmap succeeded: %u bytes at address "
        "0x%X\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_INST_DSM_SIZE(instObj),
        ptr));

    DSM_DATA_SYS_MAP_ADDR(dataObj) = ptr;

#endif /* defined(WIN32) */

    /* 
     * Initialize shared memory data. 
     */

    DSM_DATA_MEM_DATA(dataObj) = (DSM_MemData *)DSM_DATA_SYS_MAP_ADDR(dataObj);

    if (!DSM_DATA_FIRST(dataObj))
    {
        CheckCreator(coreObj, instObj, dataObj);
    }
    
    /* this should be done only ONCE */
    if (DSM_DATA_FIRST(dataObj))
    {
        /* MUST be initialized to zero (contains struct malloc state). */
        memset(DSM_DATA_MEM_DATA(dataObj), 0, sizeof(DSM_MemData));

#if defined(DEBUG) || defined(_DEBUG)
        memset(DSM_DATA_SYS_MAP_ADDR(dataObj), 0, DSM_INST_DSM_SIZE(instObj));
#endif /* defined(DEBUG) || defined(_DEBUG) */

        DSM_DATA_MEM_DATA(dataObj)->size    = 
            DSM_INST_DSM_SIZE(instObj);
        DSM_DATA_MEM_DATA(dataObj)->base    = 
            (ITS_POINTER)DSM_DATA_SYS_MAP_ADDR(dataObj) + 
                malloc_getpagesize;
        DSM_DATA_MEM_DATA(dataObj)->curbrk  = 
            DSM_DATA_MEM_DATA(dataObj)->base;
        DSM_DATA_MEM_DATA(dataObj)->cursync = 
            DSM_DATA_SYS_MAP_ADDR(dataObj);
        DSM_DATA_MEM_DATA(dataObj)->top     = 
            (ITS_POINTER)DSM_DATA_SYS_MAP_ADDR(dataObj) + 
                DSM_INST_DSM_SIZE(instObj);
    }
    
    return (ITS_SUCCESS);
}

static void
FreeSharedMem(DSM_CoreObject* coreObj,
              DSM_InstObject* instObj,
              DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    MUTEX_DeleteMutex(&DSM_DATA_TABLES_LOCK(dataObj));

#if defined(WIN32)

    if (DSM_DATA_SYS_MAP_ADDR(dataObj))
    {
        BOOL bRes;

        bRes = VirtualFree(
                    DSM_DATA_SYS_MAP_ADDR(dataObj),
                    0,
                    MEM_RELEASE);
        if (!bRes)
        {
            ITS_TRACE_ERROR((
                "MemDataDestroy [FtGroupId: %u]: VirtualFree failed with "
                "GetLastError: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                GetLastError()));
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] Failed to deallocate DSM on Win32 system\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            return;
        }

        ITS_TRACE_DEBUG((
            "MemDataDestroy [FtGroupId: %u]: VirtualFree succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

#else /* !defined(WIN32) */

    if (DSM_DATA_SYS_MAP_ADDR(dataObj))
    {
        int ret;

        ret = munmap(
                DSM_DATA_SYS_MAP_ADDR(dataObj),
                DSM_INST_DSM_SIZE(instObj));
        if (ret != 0)
        {
            ITS_TRACE_ERROR((
                "MemDataDestroy [FtGroupId: %u]: munmap failed with errno: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                errno));
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] Failed to deallocate DSM on Unix system\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }

        ITS_TRACE_DEBUG((
            "MemDataDestroy [FtGroupId: %u]: munmap succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

#endif /* defined(WIN32) */
}

/*
 * DataClassInitialize.
 */
static int
DataClassInitialize(ITS_Class objClass)
{
    /* Nothing to do. */
    return (ITS_SUCCESS);
}

/*
 * DataClassTerminate.
 */
static void
DataClassTerminate(ITS_Class objClass)
{
    /* Nothing to do. */
    return;
}

/*
 * DataCreateInstance.
 */
static int
DataCreateInstance(ITS_Object obj, va_list args)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_USHORT ftGroupId;
    int ret;

    coreObj     = va_arg(args, DSM_CoreObject*);
    instObj     = va_arg(args, DSM_InstObject*);
    ftGroupId   = (ITS_USHORT)va_arg(args, int);

    dataObj     = (DSM_DataObject*)obj;

    /* Access within destroy instance only. */
    DSM_DATA_CORE_OBJECT(dataObj) = coreObj;
    DSM_DATA_INST_OBJECT(dataObj) = instObj;

    /* create or find the shared region */
    ret = GetSharedMem(coreObj, instObj, dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance: GetSharedMem failed: %d\n", ret));
        return (ret);
    }

    if (DSM_DATA_FIRST(dataObj))
    {            
        ret = DsmInfoCreate(coreObj, instObj, dataObj);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "DataCreateInstance: DsmInfoCreate failed: %d\n", ret));

            FreeSharedMem(coreObj, instObj, dataObj);

            return (ret);
        }

        ret = TablesCreate(coreObj, instObj, dataObj);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("DataCreateInstance: TablesCreate failed: %d\n", ret));

            FreeSharedMem(coreObj, instObj, dataObj);
            DsmInfoDestroy(coreObj, instObj, dataObj);
            
            return (ret);
        }

        ret = TablesInfoCreate(coreObj, instObj, dataObj);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR(("DataCreateInstance: TablesInfoCreate failed: %d\n", ret));

            FreeSharedMem(coreObj, instObj, dataObj);
            DsmInfoDestroy(coreObj, instObj, dataObj);
            TablesDestroy(coreObj, instObj, dataObj);

            return (ret);
        }
    }
    else
    {
        /* Racy.  There's got to be a better way */
        TIMERS_Sleep(1);
    }

    return (ITS_SUCCESS);
}

/*
 * DataDestroyInstance.
 */
static void
DataDestroyInstance(ITS_Object obj)
{
    TablesInfoDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    TablesDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    DsmInfoDestroy(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    FreeSharedMem(
        DSM_DATA_CORE_OBJECT(obj),
        DSM_DATA_INST_OBJECT(obj),
        (DSM_DataObject*)obj);

    DSM_DATA_CORE_OBJECT(obj) = NULL;
    DSM_DATA_INST_OBJECT(obj) = NULL;
}

static DSM_DataClassRec itsDSM_DataClassRec =
{
    /* core part */
    {
        NULL,                               /* no super class in DLL    */
        sizeof(DSM_DataObject),             /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_DATA_CLASS_NAME,                /* class name               */
        DataClassInitialize,                /* class init               */
        DataClassTerminate,                 /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        DataCreateInstance,                 /* instance create          */
        DataDestroyInstance,                /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* data part */
    {
        NULL,
        NULL
    }
};

static ITS_Class itsDSM_DataClass = (ITS_Class)&itsDSM_DataClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (POSIX) Impl (implementation) class.
 **
 */

static void
CallMembershipChangeCallbacks(DSM_CoreObject* coreObj,
                              DSM_InstObject* instObj,
                              ITS_USHORT ftGroupId,
                              DSM_MembershipChangeType membershipChangeType)
{
    DSM_MembershipChangeCbData membershipChangeCbData;
    DSM_FtGroupMember ftGroupMembers[1];
    ITS_USHORT numFtGroupMembers;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(instObj != NULL);

    nodeId      = DSM_CORE_NODE_ID(coreObj);
    processId   = DSM_CORE_PROCESS_ID(coreObj);

    numFtGroupMembers = 1;

    ftGroupMembers[0].nodeId    = nodeId;
    ftGroupMembers[0].processId = processId;

    membershipChangeCbData.ftGroupId = ftGroupId;
    membershipChangeCbData.membershipChangeType = membershipChangeType;
    membershipChangeCbData.memberNodeId = nodeId;
    membershipChangeCbData.memberProcessId = processId;
    membershipChangeCbData.numFtGroupMembers = numFtGroupMembers;
    membershipChangeCbData.ftGroupMembers = ftGroupMembers;

    ret = CALLBACK_CallCallbackList(DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(instObj),
                                    (ITS_POINTER)coreObj,
                                    (ITS_POINTER)&membershipChangeCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }
}

static int 
DSM_ImplDataCreateInstanceImpl(DSM_CoreObject* coreObj,
                               DSM_InstObject* instObj,
                               ITS_USHORT ftGroupId)
{
    DSM_DataObject* dataObj;
    
    dataObj = (DSM_DataObject*)ITS_ConstructObject(
                                        itsDSM_DataClass,
                                        coreObj,
                                        instObj,
                                        (int)ftGroupId);
    if (dataObj == NULL)
    {
        /* TODO: add trace. */
        return (ITS_EIMPLINITFAIL);
    }

    DSM_INST_IMPL_DATA(instObj) = (ITS_Object)dataObj;

    return (ITS_SUCCESS);
}

static int 
DSM_ImplDataDestroyInstanceImpl(DSM_CoreObject* coreObj,
                                DSM_InstObject* instObj,
                                ITS_USHORT  ftGroupId)
{
    DSM_DataObject* dataObj;

    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_DestructObject((ITS_Object)dataObj);

    return (ITS_SUCCESS);
}

static int 
DSM_JoinFtGroupImpl(DSM_CoreObject* coreObj,
                    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_TRUE;

    CallMembershipChangeCallbacks(coreObj,
                                  instObj,
                                  ftGroupId,
                                  DSM_FT_GROUP_MEMBER_ALIVE);

    CallMembershipChangeCallbacks(coreObj,
                                  instObj,
                                  ftGroupId,
                                  DSM_FT_GROUP_MEMBER_JOIN);

    return (ITS_SUCCESS);
}

static int 
DSM_LeaveFtGroupImpl(DSM_CoreObject* coreObj,
                     ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_FALSE;

    CallMembershipChangeCallbacks(coreObj,
                                  instObj,
                                  ftGroupId,
                                  DSM_FT_GROUP_MEMBER_LEAVE);

    CallMembershipChangeCallbacks(coreObj,
                                  instObj,
                                  ftGroupId,
                                  DSM_FT_GROUP_MEMBER_DEAD);

    return (ITS_SUCCESS);
}

static int 
DSM_SynchronizeDsmImpl(DSM_CoreObject* coreObj,
                       ITS_USHORT ftGroupId,
                       ITS_UINT msecs)
{
    /* Nothing to do for POSIX implementation. */
    return ITS_SUCCESS;
}

static int 
DSM_LockDsmImpl(DSM_CoreObject* coreObj,
                ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_DSM_INFO(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_LockDsmImpl: MUTEX_AcquireMutex failed: %d\n", ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_UnlockDsmImpl(DSM_CoreObject* coreObj,
                  ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_ReleaseMutex(&DSM_DATA_DSM_INFO(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_UnlockDsmImpl: MUTEX_ReleaseMutex failed: %d\n", ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_LockTableImpl(DSM_CoreObject* coreObj,
                  ITS_USHORT ftGroupId, 
                  ITS_UINT tableId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_LockTableImpl: MUTEX_AcquireMutex failed: %d\n", ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_UnlockTableImpl(DSM_CoreObject* coreObj,
                    ITS_USHORT ftGroupId, 
                    ITS_UINT tableId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR(("DSM_UnlockTableImpl: MUTEX_ReleaseMutex failed: %d\n", ret));

        return (ret);
    }

    return (ITS_SUCCESS);
}

static void *
DSM_AllocNoLockImpl(DSM_CoreObject* coreObj,
                    ITS_USHORT ftGroupId,
                    ITS_UINT tableId,
                    ITS_OCTET* key, ITS_UINT klen,
                    ITS_UINT size,
                    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    ITS_UINT rowSize = size;
    DSM_RowHeader *allocPtr;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Add row header to rowSize and make it a multiple of word size. */
    rowSize += sizeof(DSM_RowHeader) + sizeof(ITS_UINT) - 1;
    rowSize &= ~(sizeof(ITS_UINT) - 1);

    /* Add to table. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        bhNode = BHASH_AddEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                tableId, key, klen, NULL, rowSize);
        if (bhNode == NULL)
        {
            *error = ITS_ENOMEM;

            return (NULL);
        }

        allocPtr = bhNode->data;
        break;

    case DSM_TABLE_REDBLACK:
        rbNode = RB_InsertNode(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                               key, klen, NULL, rowSize);
        if (rbNode == NULL)
        {
            *error = ITS_ENOMEM;

            return (NULL);
        }

        allocPtr = rbNode->data;
        break;

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_InsertNode(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                  key, klen, NULL, rowSize);
        if (spNode == NULL)
        {
            *error = ITS_ENOMEM;

            return (NULL);
        }

        allocPtr = spNode->data;
        break;

    default:
        *error = ITS_EINVALIDARGS;
        return (NULL);
    }

    /* Adjust number of entries in table. */
    DSM_DATA_TABLES_INFO(dataObj)[tableId].entries++;

    /* Adjust pointer to user data (row header is before). */
    allocPtr = allocPtr + 1;

    return allocPtr;
}

static void*
DSM_FindNoLockImpl(DSM_CoreObject* coreObj,
                   ITS_USHORT ftGroupId,
                   ITS_UINT tableId,
                   ITS_OCTET* key, ITS_UINT klen,
                   int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader* row = NULL;
    DSM_RowHeader* findPtr;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        bhNode = BHASH_FindEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                 tableId, key, klen);
        if (bhNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        row = bhNode->data;
        break;

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                              key, klen);
        if (rbNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        row = rbNode->data;
        break;

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                 key, klen);
        if (spNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        row = spNode->data;
        break;

    default:
        *error = ITS_EINVALIDARGS;
        break;
    }

    /* Make sure it was found. */
    if (row == NULL)
    {
        *error = ITS_ENOTFOUND;

        return (NULL);
    }

    /* Adjust pointer to user data (row header is before). */
    findPtr = row;
    findPtr = findPtr + 1;

    return findPtr;
}

static void *
DSM_FindPrevNoLockImpl(DSM_CoreObject* coreObj,
                       ITS_USHORT ftGroupId,
                       ITS_UINT tableId,
                       ITS_OCTET* key, 
                       ITS_UINT klen,
                       void *object,
                       int *error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader* row = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        /* find the first matching key */
        bhNode = BHASH_FindEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                 tableId, key, klen);
        if (bhNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (bhNode != NULL)
        {
            if (bhNode->klen == klen && 
                memcmp(bhNode->key, key, klen) == 0 &&
                bhNode->data == row)
            {
                break;
            }

            bhNode = BHASH_FindNext(bhNode);
        }

        /* make sure we have one */
        if (bhNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        bhNode = BHASH_FindPrev(bhNode);
        if (bhNode)
        {
            row = bhNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                              key, klen);
        if (rbNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (rbNode != NULL)
        {
            if (rbNode->klen == klen && 
                memcmp(rbNode->key, key, klen) == 0 &&
                rbNode->data == row)
            {
                break;
            }

            rbNode = RB_FindNext(rbNode);
        }

        /* make sure we have one */
        if (rbNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        rbNode = RB_FindPrev(rbNode);
        if (rbNode)
        {
            row = rbNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                 key, klen);
        if (spNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (spNode != NULL)
        {
            if (spNode->klen == klen && 
                memcmp(spNode->key, key, klen) == 0 &&
                spNode->data == row)
            {
                break;
            }

            spNode = SPLAY_FindNext(spNode);
        }

        /* make sure we have one */
        if (spNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        spNode = SPLAY_FindPrev(spNode);
        if (spNode)
        {
            row = spNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    default:
        *error = ITS_EINVALIDARGS;
        return (NULL);
    }
}

static void *
DSM_FindNextNoLockImpl(DSM_CoreObject *coreObj,
                       ITS_USHORT ftGroupId,
                       ITS_UINT tableId,
                       ITS_OCTET* key, 
                       ITS_UINT klen,
                       void *object,
                       int *error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader* row = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        /* find the first matching key */
        bhNode = BHASH_FindEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                 tableId, key, klen);
        if (bhNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (bhNode != NULL)
        {
            if (bhNode->klen == klen && 
                memcmp(bhNode->key, key, klen) == 0 &&
                bhNode->data == row)
            {
                break;
            }

            bhNode = BHASH_FindNext(bhNode);
        }

        /* make sure we have one */
        if (bhNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        bhNode = BHASH_FindNext(bhNode);
        if (bhNode)
        {
            row = bhNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                              key, klen);
        if (rbNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (rbNode != NULL)
        {
            if (rbNode->klen == klen && 
                memcmp(rbNode->key, key, klen) == 0 &&
                rbNode->data == row)
            {
                break;
            }

            rbNode = RB_FindNext(rbNode);
        }

        /* make sure we have one */
        if (rbNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        rbNode = RB_FindNext(rbNode);
        if (rbNode)
        {
            row = rbNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                 key, klen);
        if (spNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* look for exact match */
        while (spNode != NULL)
        {
            if (spNode->klen == klen && 
                memcmp(spNode->key, key, klen) == 0 &&
                spNode->data == row)
            {
                break;
            }

            spNode = SPLAY_FindNext(spNode);
        }

        /* make sure we have one */
        if (spNode == NULL)
        {
            *error = ITS_EINVALIDARGS;

            return (NULL);
        }

        /* and get prev */
        spNode = SPLAY_FindNext(spNode);
        if (spNode)
        {
            row = spNode->data;

            return (row + 1);
        }

        *error = ITS_ENOTFOUND;
        return (NULL);

    default:
        *error = ITS_EINVALIDARGS;
        return (NULL);
    }
}

static void* 
DSM_FindFirstNoLockImpl(DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        ITS_UINT tableId,
                        int *error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader* row = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        *error = ITS_EINVALIDARGS;
        return (NULL);

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindFirst(DSM_DATA_TABLES(dataObj)[tableId].table.tree);
        if (rbNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* get data pointer */
        row = rbNode->data;
        return (row + 1);

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindFirst(DSM_DATA_TABLES(dataObj)[tableId].table.splay);
        if (spNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* get data pointer */
        row = spNode->data;
        return (row + 1);

    default:
        *error = ITS_EINVALIDARGS;
        return (NULL);
    }
}

static void* 
DSM_FindLastNoLockImpl(DSM_CoreObject* coreObj,
                       ITS_USHORT ftGroupId,
                       ITS_UINT tableId,
                       int *error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader* row = NULL;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        *error = ITS_EINVALIDARGS;
        return (NULL);

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindLast(DSM_DATA_TABLES(dataObj)[tableId].table.tree);
        if (rbNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* get data pointer */
        row = rbNode->data;
        return (row + 1);

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindLast(DSM_DATA_TABLES(dataObj)[tableId].table.splay);
        if (spNode == NULL)
        {
            *error = ITS_ENOTFOUND;

            return (NULL);
        }

        /* get data pointer */
        row = spNode->data;
        return (row + 1);

    default:
        *error = ITS_EINVALIDARGS;
        return (NULL);
    }
}

static int 
DSM_FreeNoLockImpl(DSM_CoreObject* coreObj,
                   ITS_USHORT ftGroupId,
                   ITS_UINT tableId,           
                   ITS_OCTET* key, ITS_UINT klen,
                   void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader *row;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        /* find the first matching key */
        bhNode = BHASH_FindEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                 tableId, key, klen);
        if (bhNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (bhNode != NULL)
        {
            if (bhNode->klen == klen && 
                memcmp(bhNode->key, key, klen) == 0 &&
                bhNode->data == row)
            {
                break;
            }

            bhNode = BHASH_FindNext(bhNode);
        }

        /* make sure we have one */
        if (bhNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* and delete it */
        BHASH_DeleteEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                          tableId, bhNode);
        break;

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                              key, klen);
        if (rbNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (rbNode != NULL)
        {
            if (rbNode->klen == klen && 
                memcmp(rbNode->key, key, klen) == 0 &&
                rbNode->data == row)
            {
                break;
            }

            rbNode = RB_FindNext(rbNode);
        }

        /* make sure we have one */
        if (rbNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* and delete it */
        RB_DeleteNode(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                      rbNode);
        break;

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                 key, klen);
        if (spNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (spNode != NULL)
        {
            if (spNode->klen == klen && 
                memcmp(spNode->key, key, klen) == 0 &&
                spNode->data == row)
            {
                break;
            }

            spNode = SPLAY_FindNext(spNode);
        }

        /* make sure we have one */
        if (spNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* and delete it */
        SPLAY_DeleteNode(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                         spNode);
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    /* Adjust number of entries in table. */
    if (DSM_DATA_TABLES_INFO(dataObj)[tableId].entries > 0)
    {
        DSM_DATA_TABLES_INFO(dataObj)[tableId].entries--;
    }    

    return (ITS_SUCCESS);
}

static int 
DSM_CommitNoLockImpl(DSM_CoreObject* coreObj,
                     ITS_USHORT ftGroupId,
                     ITS_UINT tableId,
                     ITS_OCTET* key, ITS_UINT klen,
                     void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    BHASH_Node *bhNode = NULL;
    REDBLACK_Node *rbNode = NULL;
    SPLAY_Node *spNode = NULL;
    DSM_RowHeader *row;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Scan row list for correct row. */
    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        /* find the first matching key */
        bhNode = BHASH_FindEntry(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                                 tableId, key, klen);
        if (bhNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (bhNode != NULL)
        {
            if (bhNode->klen == klen && 
                memcmp(bhNode->key, key, klen) == 0 &&
                bhNode->data == row)
            {
                break;
            }

            bhNode = BHASH_FindNext(bhNode);
        }

        /* make sure we have one */
        if (bhNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* nothing else to do */
        break;

    case DSM_TABLE_REDBLACK:
        rbNode = RB_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                              key, klen);
        if (rbNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (rbNode != NULL)
        {
            if (rbNode->klen == klen && 
                memcmp(rbNode->key, key, klen) == 0 &&
                rbNode->data == row)
            {
                break;
            }

            rbNode = RB_FindNext(rbNode);
        }

        /* make sure we have one */
        if (rbNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* nothing else to do */
        break;

    case DSM_TABLE_SPLAY:
        spNode = SPLAY_FindExact(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                                 key, klen);
        if (spNode == NULL)
        {
            return (ITS_ENOTFOUND);
        }

        /* look for exact match */
        while (spNode != NULL)
        {
            if (spNode->klen == klen && 
                memcmp(spNode->key, key, klen) == 0 &&
                spNode->data == row)
            {
                break;
            }

            spNode = SPLAY_FindNext(spNode);
        }

        /* make sure we have one */
        if (spNode == NULL)
        {
            return (ITS_EINVALIDARGS);
        }

        /* nothing else to do */
        break;

    default:
        return (ITS_EINVALIDARGS);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_LockRowNoLockImpl(DSM_CoreObject* coreObj,
                      ITS_USHORT ftGroupId,
                      void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_TRUE;
    row->lockTime = TIMERS_Time();

    return (ITS_SUCCESS);
}

static int 
DSM_UnlockRowNoLockImpl(DSM_CoreObject* coreObj,
                        ITS_USHORT ftGroupId,
                        void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_FALSE;
    row->lockTime = 0;

    return (ITS_SUCCESS);
}

static void * 
DSM_AllocImpl(DSM_CoreObject* coreObj,
              ITS_USHORT ftGroupId,
              ITS_UINT tableId,
              ITS_OCTET* key, ITS_UINT klen,
              ITS_UINT size, 
              int* error)
{
    void* allocPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;

        return (NULL);
    }

    allocPtr = DSM_AllocNoLockImpl(coreObj,
                                   ftGroupId, tableId, 
                                   key, klen, 
                                   size, 
                                   error);
    if (allocPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockImpl(coreObj, ftGroupId, allocPtr);
    }

    ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return (allocPtr);
}

static void * 
DSM_FindImpl(DSM_CoreObject* coreObj,
             ITS_USHORT ftGroupId,
             ITS_UINT tableId,
             ITS_OCTET* key, ITS_UINT klen,
             int* error)
{
    void* findPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;

        return (NULL);
    }

    findPtr = DSM_FindNoLockImpl(coreObj,
                                 ftGroupId,
                                 tableId, 
                                 key, klen,  
                                 error);
    if (findPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockImpl(coreObj, ftGroupId, findPtr);
    }

    ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return (findPtr);
}

static int 
DSM_FreeImpl(DSM_CoreObject* coreObj,
             ITS_USHORT ftGroupId,
             ITS_UINT tableId,
             ITS_OCTET* key, ITS_UINT klen,
             void* object)
{
    DSM_RowHeader* row;
    int ret;

    ITS_C_REQUIRE(object != NULL);

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader *)((char *)object - sizeof(DSM_RowHeader));

    ITS_C_ASSERT(row->locked);

    if (!row->locked)
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return (ITS_EROWNOTLOCKED);
    }

    ret = DSM_FreeNoLockImpl(coreObj,
                             ftGroupId,
                             tableId,
                             key, klen,
                             object);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
        
        return (ret);
    }
    
    ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_CommitImpl(DSM_CoreObject* coreObj,
               ITS_USHORT ftGroupId,
               ITS_UINT tableId,
               ITS_OCTET* key, ITS_UINT klen,
               void* object)
{
    DSM_RowHeader* row;
    int ret;

    ITS_C_REQUIRE(object != NULL);

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader *)((char *)object - sizeof(DSM_RowHeader));

    ITS_C_ASSERT(row->locked);

    if (!row->locked)
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return (ITS_EROWNOTLOCKED);
    }

    ret = DSM_CommitNoLockImpl(coreObj,
                               ftGroupId,
                               tableId,
                               key, klen,
                               object);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
        
        return (ret);
    }
    
    ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    return (ITS_SUCCESS);
}

static int 
DSM_LockRowImpl(DSM_CoreObject* coreObj,
                ITS_USHORT ftGroupId,
                ITS_UINT tableId,
                ITS_OCTET* key, ITS_UINT klen,
                void* object)
{
    void* findPtr;
    int error;
    int ret;

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    findPtr = DSM_FindNoLockImpl(coreObj,
                                 ftGroupId,
                                 tableId, 
                                 key, klen,  
                                 &error);
    if (findPtr != NULL && error == ITS_SUCCESS)
    {
        ret = DSM_LockRowNoLockImpl(coreObj, ftGroupId, findPtr);
    }

    if (error != ITS_SUCCESS)
    {
        ret = error;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }
    else
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return (ret);
    }
        
    return (ITS_SUCCESS);
}

static int 
DSM_UnlockRowImpl(DSM_CoreObject* coreObj,
                  ITS_USHORT ftGroupId,
                  ITS_UINT tableId,
                  ITS_OCTET* key, ITS_UINT klen,
                  void* object)
{
    void* findPtr;
    int error;
    int ret;

    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    findPtr = DSM_FindNoLockImpl(coreObj,
                                 ftGroupId,
                                 tableId, 
                                 key, klen,  
                                 &error);
    if (findPtr != NULL && error == ITS_SUCCESS)
    {
        ret = DSM_UnlockRowNoLockImpl(coreObj, ftGroupId, findPtr);
    }

    if (error != ITS_SUCCESS)
    {
        ret = error;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);
        if (ret != ITS_SUCCESS)
        {
            return (ret);
        }
    }
    else
    {
        DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return ret;
    }
        
    return (ITS_SUCCESS);
}

/*
 * Iterate procs require a little help.  Note the stack tricks we're
 * playing here.
 */
typedef struct
{
    DSM_IterateEntryProc    proc;
    void *                  in;
}
IterArg;

static int
IterateBHASH(BHASH_Node *node, void *in, void *out)
{
    IterArg *arg = (IterArg *)in;
    ITS_POINTER base = node->data;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return (*arg->proc)(base, arg->in, out);
}

static int
IterateREDBLACK(REDBLACK_Node *node, void *in, void *out)
{
    IterArg *arg = (IterArg *)in;
    ITS_POINTER base = node->data;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return (*arg->proc)(base, arg->in, out);
}

static int
IterateSPLAY(SPLAY_Node *node, void *in, void *out)
{
    IterArg *arg = (IterArg *)in;
    ITS_POINTER base = node->data;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return (*arg->proc)(base, arg->in, out);
}

static int 
DSM_TableIterateImpl(DSM_CoreObject* coreObj,
                     ITS_USHORT ftGroupId,
                     ITS_UINT tableId, 
                     void* in, 
                     void* out,
                     DSM_IterateEntryProc iterateEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    IterArg arg;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(iterateEntryFn != NULL);

    ITS_TRACE_DEBUG(("DSM_TableIterateImpl:\n"));

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    /* set up the arg */
    arg.proc = iterateEntryFn;
    arg.in = in;

    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        ret = BHASH_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                            tableId, &arg, out, IterateBHASH);
        break;

    case DSM_TABLE_REDBLACK:
        ret = RB_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                         &arg, out, IterateREDBLACK);
        break;

    case DSM_TABLE_SPLAY:
        ret = SPLAY_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                            &arg, out, IterateSPLAY);
        break;

    default:
        ret = ITS_EINVALIDARGS;
        break;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return (ret);
    }

    DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

    return (ret);
}

/*
 * Dump procs require a little help.  Note the argument tricks we're
 * playing here.
 */
static int
DoEntry(DSM_DumpEntryProc proc, ITS_POINTER ptr, char **pStrDump)
{
    ITS_POINTER strEntryDump = NULL;
    int ret;

    /* Initialization. */
    if (*pStrDump == NULL)
    {
        *pStrDump = (char *)malloc(1 * sizeof(char));
        if (*pStrDump == NULL)
        {
            ITS_TRACE_ERROR(("DSM_TableDumpImpl: out of memory\n"));

            return (ITS_ENOMEM);
        }

        **pStrDump = '\0'; 
    }

    ret = (*proc)(ptr, &strEntryDump);
    if (ret != ITS_SUCCESS)
    {
        if (strEntryDump != NULL)
        {
            free(strEntryDump);
        }

        return (ret);
    }

    if (strEntryDump == NULL)
    {
        return (ITS_SUCCESS);
    }

    /* + 1 = security. */
    *pStrDump = (char *)realloc(*pStrDump,
                                strlen(*pStrDump) * sizeof(char) +
                                strlen(strEntryDump) + sizeof(char));

    if (*pStrDump == NULL)
    {
        free(strEntryDump);

        return (ITS_ENOMEM);
    }

    strcat(*pStrDump, strEntryDump);

    free(strEntryDump);

    return (ITS_SUCCESS);
}

static int
DumpBHASH(BHASH_Node *node, void *in, void *out)
{
    ITS_POINTER base = node->data;
    char **pStrDump = (char **)in;
    DSM_DumpEntryProc proc = (DSM_DumpEntryProc)out;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return DoEntry(proc, base, pStrDump);
}

static int
DumpREDBLACK(REDBLACK_Node *node, void *in, void *out)
{
    ITS_POINTER base = node->data;
    char **pStrDump = (char **)in;
    DSM_DumpEntryProc proc = (DSM_DumpEntryProc)out;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return DoEntry(proc, base, pStrDump);
}

static int
DumpSPLAY(SPLAY_Node *node, void *in, void *out)
{
    ITS_POINTER base = node->data;
    char **pStrDump = (char **)in;
    DSM_DumpEntryProc proc = (DSM_DumpEntryProc)out;

    ITS_C_ASSERT(base != NULL);

    base += sizeof(DSM_RowHeader);

    return DoEntry(proc, base, pStrDump);
}

static int 
DSM_TableDumpImpl(DSM_CoreObject* coreObj,
                  ITS_USHORT ftGroupId,
                  ITS_UINT tableId, 
                  char** pStrDump,                            
                  DSM_DumpEntryProc dumpEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(pStrDump != NULL);
    ITS_C_REQUIRE(dumpEntryFn != NULL);

    ITS_TRACE_DEBUG(("DSM_TableDumpImpl:\n"));

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);
    
    ret = DSM_LockTableImpl(coreObj, ftGroupId, tableId);
    if (ret != ITS_SUCCESS)
    {
        return (ret);
    }

    *pStrDump = NULL;

    switch (DSM_DATA_TABLES(dataObj)[tableId].type)
    {
    case DSM_TABLE_HASH:
        ret = BHASH_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                            tableId, pStrDump, dumpEntryFn, DumpBHASH);
        break;

    case DSM_TABLE_REDBLACK:
        ret = RB_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.tree,
                         pStrDump, dumpEntryFn, DumpREDBLACK);
        break;

    case DSM_TABLE_SPLAY:
        ret = SPLAY_Iterate(DSM_DATA_TABLES(dataObj)[tableId].table.splay,
                            pStrDump, dumpEntryFn, DumpSPLAY);
        break;

    default:
        ret = ITS_EINVALIDARGS;
        break;
    }

    /* Precedence to report errors from most important functions. */
    if (ret == ITS_SUCCESS)
    {
        ret = DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

        return (ret);
    }

    DSM_UnlockTableImpl(coreObj, ftGroupId, tableId);

    return (ret);
}

static int 
DSM_TableGetSizeImpl(DSM_CoreObject* coreObj,
                     ITS_USHORT ftGroupId,
                     ITS_UINT tableId, 
                     ITS_UINT* size)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(size != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *size = DSM_DATA_TABLES_INFO(dataObj)[tableId].entries;

    return ITS_SUCCESS;
}

static int 
DSM_MulticastEventToFtGroupMembersImpl(DSM_CoreObject* coreObj,
                                       ITS_USHORT ftGroupId,
                                       const ITS_EVENT* event)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return (ITS_SUCCESS);
}


#define DSM_POSIX_IMPL_CLASS_NAME "DSM Implementation Class - POSIX"

DSM_ImplClassRec itsDSM_PosixImplClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_POSIX_IMPL_CLASS_NAME,          /* class name               */
        ITS_CLASS_NO_INIT,                  /* class init               */
        ITS_CLASS_NO_DEST,                  /* class destroy            */
        ITS_CLASS_PART_NO_INIT,             /* class part init          */
        ITS_CLASS_PART_NO_DEST,             /* class part destroy       */
        ITS_INST_NO_CONST,                  /* instance create          */
        ITS_INST_NO_DEST,                   /* instance delete          */
        ITS_INST_CLONE_INHERIT,             /* inherit clone            */
        ITS_INST_PRINT_INHERIT,             /* inherit print            */
        ITS_INST_SERIAL_INHERIT,            /* inherit serial           */
        ITS_INST_EQUALS_INHERIT,            /* inherit equals           */
        NULL                                /* no extension of interest */
    },
    /* impl part */
    {
        "POSIX",
        DSM_ImplDataCreateInstanceImpl,
        DSM_ImplDataDestroyInstanceImpl,
        DSM_JoinFtGroupImpl,
        DSM_LeaveFtGroupImpl,
        DSM_SynchronizeDsmImpl,
        DSM_AllocImpl,
        DSM_FindImpl,
        DSM_FreeImpl,
        DSM_CommitImpl,
        DSM_LockRowImpl,
        DSM_UnlockRowImpl,
        DSM_LockDsmImpl,
        DSM_UnlockDsmImpl,
        DSM_LockTableImpl,
        DSM_UnlockTableImpl,
        DSM_AllocNoLockImpl,
        DSM_FindNoLockImpl,
        DSM_FreeNoLockImpl,
        DSM_CommitNoLockImpl,
        DSM_LockRowNoLockImpl,
        DSM_UnlockRowNoLockImpl,
        DSM_FindPrevNoLockImpl,
        DSM_FindNextNoLockImpl,
        DSM_FindFirstNoLockImpl,
        DSM_FindLastNoLockImpl,
        DSM_TableIterateImpl,
        DSM_TableDumpImpl,
        DSM_TableGetSizeImpl,
        DSM_MulticastEventToFtGroupMembersImpl
    }
};

DSMDLLAPI ITS_Class itsDSM_PosixImplClass = (ITS_Class)&itsDSM_PosixImplClassRec;


