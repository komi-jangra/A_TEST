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
 *  ID: $Id: malloc.c,v 1.1.1.1 2007-10-08 11:12:03 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:37  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:17  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:31  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:00  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:52:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:29  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:16  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.11  2001/05/15 01:02:22  mmiers
 * LOG: Add some notes.
 * LOG:
 * LOG: Revision 1.10  2001/05/12 21:31:48  mmiers
 * LOG: Got it working.
 * LOG:
 * LOG: Revision 1.9  2001/05/11 23:08:01  mmiers
 * LOG: Set up for reflect.
 * LOG:
 * LOG: Revision 1.8  2001/05/11 20:19:56  mmiers
 * LOG: Mark memory writes.
 * LOG:
 * LOG: Revision 1.7  2001/05/11 19:28:17  mmiers
 * LOG: Startrand
 * LOG:
 * LOG: Revision 1.6  2001/05/11 19:11:29  mmiers
 * LOG: A few more format changes.
 * LOG:
 * LOG: Revision 1.5  2001/05/11 19:05:19  mmiers
 * LOG: OK, it's been trimmed and formatted.  Now I'll try to understand
 * LOG: it.
 * LOG:
 *
 ****************************************************************************/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#if defined(WIN32)

#define WINDOWS_LEAN_AND_MEAN

#include <windows.h>

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

#if defined(MALLOC_TEST)

char *holdbase;
char *rholdbase;
char *base;
char *rbase;
char *curbrk;
char *rcurbrk;
char *top;
char *rtop;

/*
 * REFLECT VALUES
 */
#define REFLECT_MEMCPY(d, s, n)                        \
    do                                                 \
    {                                                  \
        if ((char *)(d) < base - sizeof(struct malloc_state) ||  \
            (char *)(d) > top)                                   \
        {                                              \
            abort();                                   \
        }                                              \
        memcpy(rbase + ((char *)(d) - base), s, n);              \
    }                                                  \
    while (0)
#define REFLECT_MEMSET(d, v, n)                        \
    do                                                 \
    {                                                  \
        if ((char *)(d) < base - sizeof(struct malloc_state) ||  \
            (char *)(d) > top)                                   \
        {                                              \
            abort();                                   \
        }                                              \
        memset(rbase + ((char *)(d) - base), v, n);              \
    }                                                  \
    while (0)
#define REFLECT_SET(d, v)                              \
    do                                                 \
    {                                                  \
        if ((char *)(d) < base - sizeof(struct malloc_state) ||  \
            (char *)(d) > top)                                   \
        {                                              \
            abort();                                   \
        }                                              \
        if (sizeof(v) != sizeof(unsigned long))        \
        {                                              \
            abort();                                   \
        }                                              \
        *(unsigned long *)(rbase + ((char *)(d) - base)) = (unsigned long)(v);  \
    }                                                  \
    while (0)

#endif

/* The corresponding word size */
#define SIZE_SZ                (sizeof(size_t))

/*
 * MALLOC_ALIGNMENT is the minimum alignment for malloc'ed chunks.
 * It must be a power of two at least 2 * SIZE_SZ, even on machines
 * for which smaller alignments would suffice. It may be defined as
 * larger than this though. Note however that code and data structures
 * are optimized for the case of 8-byte alignment.
 */
#ifndef MALLOC_ALIGNMENT
#define MALLOC_ALIGNMENT       (2 * SIZE_SZ)
#endif

/* The corresponding bit mask value */
#define MALLOC_ALIGN_MASK      (MALLOC_ALIGNMENT - 1)

/*
 * MORECORE is the name of the routine to call to obtain more memory
 * from the system.  See below for general guidance on writing
 * alternative MORECORE functions, as well as a version for WIN32 and a
 * sample version for pre-OSX macos.
 */
void *local_alloc(ptrdiff_t incr);

#define MORECORE local_alloc

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

#include "malloc.h"

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
 * MLM: SET
 */
#define MALLOC_COPY(dest, src, nbytes)      \
    do                                      \
    {                                       \
        REFLECT_MEMCPY(dest, src, nbytes);  \
        memcpy(dest, src, nbytes);          \
    }                                       \
    while (0)

#define MALLOC_ZERO(dest, nbytes)           \
    do                                      \
    {                                       \
        REFLECT_MEMSET(dest, 0, nbytes);    \
        memset(dest, 0,   nbytes);          \
    }                                       \
    while (0)

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

/* The smallest possible chunk */
#define MIN_CHUNK_SIZE \
    (sizeof(struct malloc_chunk))

/* The smallest size we can malloc is an aligned minimal chunk */
#define MINSIZE \
    (unsigned long)(((MIN_CHUNK_SIZE+MALLOC_ALIGN_MASK) & ~MALLOC_ALIGN_MASK))

/* Check if m has acceptable alignment */
#define aligned_OK(m) \
    (((unsigned long)((m)) & (MALLOC_ALIGN_MASK)) == 0)


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
/* MLM: SET */
#define set_inuse(p)                                                    \
    do                                                                  \
    {                                                                   \
        REFLECT_SET(&((mchunkptr)(((char*)(p)) +                        \
                                  ((p)->size & ~PREV_INUSE)))->size,    \
                    ((mchunkptr)(((char*)(p)) +                         \
                                 ((p)->size & ~PREV_INUSE)))->size |    \
                    PREV_INUSE);                                        \
        ((mchunkptr)(((char*)(p)) +                                     \
                     ((p)->size & ~PREV_INUSE)))->size |=               \
        PREV_INUSE;                                                     \
    }                                                                   \
    while (0)


/* MLM: SET */
#define clear_inuse(p)                                                  \
    do                                                                  \
    {                                                                   \
        REFLECT_SET(&((mchunkptr)(((char*)(p)) +                        \
                                  ((p)->size & ~PREV_INUSE)))->size &=  \
                    ((mchunkptr)(((char*)(p)) +                         \
                                 ((p)->size & ~PREV_INUSE)))->size &    \
                    (PREV_INUSE));                                      \
        ((mchunkptr)(((char*)(p)) +                                     \
                     ((p)->size & ~PREV_INUSE)))->size &=               \
        ~(PREV_INUSE);                                                  \
    }                                                                   \
    while (0)


/* check/set/clear inuse bits in known places */
#define inuse_bit_at_offset(p, s) \
    (((mchunkptr)(((char*)(p)) + (s)))->size & PREV_INUSE)

/* MLM: SET */
#define set_inuse_bit_at_offset(p, s)                               \
    do                                                              \
    {                                                               \
        REFLECT_SET(&((mchunkptr)(((char*)(p)) + (s)))->size,       \
                    ((mchunkptr)(((char*)(p)) + (s)))->size |       \
                    PREV_INUSE);                                    \
        (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE);    \
    }                                                               \
    while (0)


/* MLM: SET */
#define clear_inuse_bit_at_offset(p, s)                             \
    do                                                              \
    {                                                               \
        REFLECT_SET(&((mchunkptr)(((char*)(p)) + (s)))->size,       \
                    ((mchunkptr)(((char*)(p)) + (s)))->size &       \
                    ~(PREV_INUSE));                                 \
        (((mchunkptr)(((char*)(p)) + (s)))->size &= ~(PREV_INUSE)); \
    }                                                               \
    while (0)


/* Set size at head, without disturbing its use bit */
/* MLM: SET */
#define set_head_size(p, s)                                 \
    do                                                      \
    {                                                       \
        REFLECT_SET(&(p)->size,                             \
                    (((p)->size & PREV_INUSE) | (s)));      \
        ((p)->size = (((p)->size & PREV_INUSE) | (s)));     \
    }                                                       \
    while (0)

/* Set size/use field */
/* MLM: SET */
#define set_head(p, s)          \
    do                          \
    {                           \
        REFLECT_SET(&(p)->size, \
                    (s));       \
        ((p)->size = (s));      \
    }                           \
    while (0)

/* Set size at footer (only when chunk is not in use) */
/* MLM: SET */
#define set_foot(p, s)                                              \
    do                                                              \
    {                                                               \
        REFLECT_SET(&((mchunkptr)((char*)(p) + (s)))->prev_size,    \
                    (s));                                           \
        (((mchunkptr)((char*)(p) + (s)))->prev_size = (s));         \
    }                                                               \
    while (0)

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
/* MLM: SET */
#define unlink(P, BK, FD)   \
    do                      \
    {                       \
        FD = P->fd;         \
        BK = P->bk;         \
        REFLECT_SET(&FD->bk,\
                    BK);    \
        FD->bk = BK;        \
        REFLECT_SET(&BK->fd,\
                    FD);    \
        BK->fd = FD;        \
    }                       \
    while (0)

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
 *   with chunks being placed on it in free (and malloc_consolidate),
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
 *   sysmalloc. (This is somewhat delicate, since it relies on
 *   the 2 preceding words to be zero during this interval as well.)
 */
/* Conveniently, the unsorted bin can be used as dummy top on first call */
#define initial_top(M)              (unsorted_chunks(M))

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

#define idx2block(i) \
    ((i) >> BINMAPSHIFT)
#define idx2bit(i) \
    ((1U << ((i) & ((1U << BINMAPSHIFT)-1))))

#define get_binmap(m,i) \
    ((m)->binmap[idx2block(i)] &   idx2bit(i))
/* MLM: SET */
#define mark_bin(m,i)                                   \
    do                                                  \
    {                                                   \
        REFLECT_SET(&(m)->binmap[idx2block(i)],         \
                    (m)->binmap[idx2block(i)] |         \
                    idx2bit(i));                        \
        ((m)->binmap[idx2block(i)] |=  idx2bit(i));     \
    }                                                   \
    while (0)

/* MLM: SET */
#define unmark_bin(m,i)                                 \
    do                                                  \
    {                                                   \
        REFLECT_SET(&(m)->binmap[idx2block(i)],         \
                    (m)->binmap[idx2block(i)] &         \
                    ~(idx2bit(i)));                     \
        ((m)->binmap[idx2block(i)] &= ~(idx2bit(i)));   \
    }                                                   \
    while (0)

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
 * fastbin, and cleared only in malloc_consolidate.
 *
 * The truth value is inverted so that have_fastchunks will be true
 * upon startup (since statics are zero-filled), simplifying
 * initialization checks.
 */
#define FASTCHUNKS_BIT        (1U)

#define have_fastchunks(M) \
    (((M)->max_fast &  FASTCHUNKS_BIT) == 0)

/* MLM: SET */
#define clear_fastchunks(M)                 \
    do                                      \
    {                                       \
        REFLECT_SET(&(M)->max_fast,         \
                    (M)->max_fast |         \
                    FASTCHUNKS_BIT);        \
        ((M)->max_fast |=  FASTCHUNKS_BIT); \
    }                                       \
    while (0)

/* MLM: SET */
#define set_fastchunks(M)                   \
    do                                      \
    {                                       \
        REFLECT_SET(&(M)->max_fast,         \
                    (M)->max_fast &         \
                    ~FASTCHUNKS_BIT);       \
        ((M)->max_fast &= ~FASTCHUNKS_BIT); \
    }                                       \
    while (0)

/* 
 *  Set value of max_fast. 
 *  Use impossibly small value if 0.
 *  Precondition: there are no existing fastbin chunks.
 *  Setting the value clears fastchunk bit but preserves noncontiguous bit.
 */
/* MLM: SET */
#define set_max_fast(M, s)                                  \
    do                                                      \
    {                                                       \
        REFLECT_SET(&(M)->max_fast,                         \
                    (((s) == 0)                             \
                     ? SMALLBIN_WIDTH                       \
                     : request2size(s)) | FASTCHUNKS_BIT);  \
        (M)->max_fast = (((s) == 0)                         \
            ? SMALLBIN_WIDTH                                \
            : request2size(s)) | FASTCHUNKS_BIT;            \
    }                                                       \
    while (0)


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
 * MAIN CONTROL OBJECT:
 *
 *  There is exactly one instance of this struct in this malloc.
 *  If you are adapting this malloc in a way that does NOT use a static
 *  malloc_state, you MUST explicitly zero-fill it before using. This
 *  malloc relies on the property that malloc_state is initialized to
 *  all zeroes (as is true of C statics).
 */
static struct malloc_state av_;  /* never directly referenced */

/*
 *  All uses of av_ are via get_malloc_state().
 *  At most one "call" to get_malloc_state is made per invocation of
 *  the public versions of malloc and free, but other routines
 *  that in turn invoke malloc and/or free may call more then once. 
 *  Also, it is called in check* routines if DEBUG is set.
 */
#if 0
#define get_malloc_state() (&(av_))
#else
#define get_malloc_state() ((struct malloc_state *)(base - sizeof(struct malloc_state)))
#endif

/*
 * Initialize a malloc_state struct.
 *
 * This is called only from within malloc_consolidate, which needs
 * be called in the same contexts anyway.  It is never called directly
 * outside of malloc_consolidate because some optimizing compilers try
 * to inline it at all call points, which turns out not to be an
 * optimization at all. (Inlining it in malloc_consolidate is fine though.)
 */
static void
malloc_init_state(mstate av)
{
    int     i;
    mbinptr bin;
    
    /* Establish circular links for normal bins */
    for (i = 1; i < NBINS; ++i)
    {
        bin = bin_at(av,i);

        REFLECT_SET(&bin->fd, bin);
        REFLECT_SET(&bin->bk, bin);
        bin->fd = bin->bk = bin;    /* MLM: SET */
    }
    
    set_max_fast(av, DEFAULT_MXFAST);
    
    REFLECT_SET(&av->top, initial_top(av));
    av->top            = initial_top(av);    /* MLM: SET */

    REFLECT_SET(&av->pagesize, malloc_getpagesize);
    av->pagesize       = malloc_getpagesize;    /* MLM: SET */
}

/* 
 *  Other internal utilities operating on mstates
 */
static void*  sysmalloc(size_t, mstate);
static void   malloc_consolidate(mstate);

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

#define check_chunk(P)
#define check_free_chunk(P)
#define check_inuse_chunk(P)
#define check_remalloced_chunk(P,N)
#define check_malloced_chunk(P,N)
#define check_malloc_state()

#else
#define check_chunk(P)              do_check_chunk(P)
#define check_free_chunk(P)         do_check_free_chunk(P)
#define check_inuse_chunk(P)        do_check_inuse_chunk(P)
#define check_remalloced_chunk(P,N) do_check_remalloced_chunk(P,N)
#define check_malloced_chunk(P,N)   do_check_malloced_chunk(P,N)
#define check_malloc_state()        do_check_malloc_state()

/*
 * Properties of all chunks
 */
static void
do_check_chunk(mchunkptr p)
{
    mstate av = get_malloc_state();
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

/*
 * Properties of free chunks
 */
static void
do_check_free_chunk(mchunkptr p)
{
    mstate av = get_malloc_state();
    size_t sz = p->size & ~PREV_INUSE;
    mchunkptr next = chunk_at_offset(p, sz);
    
    do_check_chunk(p);
    
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

/*
 * Properties of inuse chunks
 */
static void
do_check_inuse_chunk(mchunkptr p)
{
    mstate av = get_malloc_state();
    mchunkptr next;
    do_check_chunk(p);
    
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
        do_check_free_chunk(prv);
    }
    
    if (next == av->top)
    {
        assert(prev_inuse(next));
        assert(chunksize(next) >= MINSIZE);
    }
    else if (!inuse(next))
    {
        do_check_free_chunk(next);
    }
}

/*
 * Properties of chunks recycled from fastbins
 */
static void
do_check_remalloced_chunk(mchunkptr p, size_t s)
{
    size_t sz = p->size & ~PREV_INUSE;
    
    do_check_inuse_chunk(p);
    
    /* Legal size ... */
    assert((sz & MALLOC_ALIGN_MASK) == 0);
    assert((unsigned long)(sz) >= MINSIZE);
    
    /* ... and alignment */
    assert(aligned_OK(chunk2mem(p)));
    
    /* chunk is less than MINSIZE more than request */
    assert((long)(sz) - (long)(s) >= 0);
    assert((long)(sz) - (long)(s + MINSIZE) < 0);
}

/*
 * Properties of nonrecycled chunks at the point they are malloced
 */
static void
do_check_malloced_chunk(mchunkptr p, size_t s)
{
  /* same as recycled case ... */
  do_check_remalloced_chunk(p, s);

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


/*
 * Properties of malloc_state.
 *
 * This may be useful for debugging malloc, as well as detecting user
 * programmer errors that somehow write into malloc_state.
 *
 * If you are extending or experimenting with this malloc, you can
 * probably figure out how to hack this routine to print out or
 * display chunk addresses, sizes, bins, and other instrumentation.
 */
static void
do_check_malloc_state()
{
    mstate av = get_malloc_state();
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
            do_check_inuse_chunk(p);
            total += chunksize(p);
            
            /* chunk belongs in this bin */
            assert(fastbin_index(chunksize(p)) == i);
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
            do_check_free_chunk(p);
            size = chunksize(p);
            total += size;
            
            if (i >= 2)
            {
                /* chunk belongs in bin */
                idx = bin_index(size);
                assert(idx == i);
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
                do_check_inuse_chunk(q);
            }
        }
    }
    
    /* top chunk is OK */
    check_chunk(av->top);
    
    /* sanity checks for statistics */
    assert(total <= (unsigned long)(av->max_total_mem));
    
    assert((unsigned long)(av->sbrked_mem) <=
        (unsigned long)(av->max_sbrked_mem));
    
    assert((unsigned long)(av->max_total_mem) >=
        (unsigned long)(av->sbrked_mem));
}
#endif


/* ----------- Routines dealing with system allocation -------------- */

/*
 * sysmalloc handles malloc cases requiring more memory from the system.
 * On entry, it is assumed that av->top does not have enough
 * space to service request for nb bytes, thus requiring that av->top
 * be extended or replaced.
 */
static void *
sysmalloc(size_t nb, mstate av)
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
        brk = (char*)(MORECORE(size));
    }
    
    if (brk != (char*)(MORECORE_FAILURE))
    {
        REFLECT_SET(&av->sbrked_mem, av->sbrked_mem + size);
        av->sbrked_mem += size;    /* MLM: SET */
        
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
            snd_brk = (char*)(MORECORE(correction));
            
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
                snd_brk = (char*)(MORECORE(0));
            }
            
            /* Adjust top based on results of second sbrk */
            if (snd_brk != (char*)(MORECORE_FAILURE))
            {
                REFLECT_SET(&av->top, (mchunkptr)aligned_brk);
                av->top = (mchunkptr)aligned_brk;    /* MLM: SET */

                set_head(av->top, (snd_brk - aligned_brk + correction) |
                                   PREV_INUSE);

                REFLECT_SET(&av->sbrked_mem, av->sbrked_mem + correction);
                av->sbrked_mem += correction;    /* MLM: SET */
                
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
                    REFLECT_SET(&chunk_at_offset(old_top, old_size)->size,
                                SIZE_SZ|PREV_INUSE);
                    chunk_at_offset(old_top, old_size)->size =
                        SIZE_SZ|PREV_INUSE;    /* MLM: SET */
                    
                    REFLECT_SET(&chunk_at_offset(old_top,
                                                 old_size + SIZE_SZ)->size,
                                SIZE_SZ|PREV_INUSE);
                    chunk_at_offset(old_top, old_size + SIZE_SZ)->size =
                        SIZE_SZ|PREV_INUSE;    /* MLM: SET */
                    
                    /* If possible, release the rest. */
                    if (old_size >= MINSIZE)
                    {
                        dlfree(chunk2mem(old_top));
                    }
                }
            }
        }
        
        /* Update statistics */
        sum = av->sbrked_mem;
        if (sum > (unsigned long)(av->max_sbrked_mem))
        {
            REFLECT_SET(&av->max_sbrked_mem, sum);
            av->max_sbrked_mem = sum;    /* MLM: SET */
        }
        
        if (sum > (unsigned long)(av->max_total_mem))
        {
            REFLECT_SET(&av->max_total_mem, sum);
            av->max_total_mem = sum;    /* MLM: SET */
        }
        
        check_malloc_state();
        
        /* finally, do the allocation */
        p = av->top;
        size = chunksize(p);
        
        /* check that one of the above allocation paths succeeded */
        if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(p, nb);

            REFLECT_SET(&av->top, remainder);
            av->top = remainder;    /* MLM: SET */
            
            set_head(p, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            
            check_malloced_chunk(p, nb);
            
            return chunk2mem(p);
        }
    }
  
    /* catch all failure paths */
    return 0;
}

/*
 * ------------------------------ malloc ------------------------------
 */
void *
dlmalloc(size_t bytes)
{
    mstate av = get_malloc_state();
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
            REFLECT_SET(fb, victim->fd);
            *fb = victim->fd;    /* MLM: SET */

            check_remalloced_chunk(victim, nb);
            
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
                malloc_consolidate(av);
            }
            else
            {
                bck = victim->bk;
                
                set_inuse_bit_at_offset(victim, nb);

                REFLECT_SET(&bin->bk, bck);
                bin->bk = bck;    /* MLM: SET */
                REFLECT_SET(&bck->fd, bin);
                bck->fd = bin;    /* MLM: SET */
                
                check_malloced_chunk(victim, nb);
                
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
            malloc_consolidate(av);
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

                REFLECT_SET(&unsorted_chunks(av)->fd, remainder);
                REFLECT_SET(&unsorted_chunks(av)->bk, remainder);
                unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                REFLECT_SET(&av->last_remainder, remainder);
                av->last_remainder = remainder;     /* MLM: SET */

                REFLECT_SET(&remainder->bk, unsorted_chunks(av));
                REFLECT_SET(&remainder->fd, unsorted_chunks(av));
                remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */
                
                set_head(victim, nb | PREV_INUSE);
                set_head(remainder, remainder_size | PREV_INUSE);
                set_foot(remainder, remainder_size);
                
                check_malloced_chunk(victim, nb);
                
                return chunk2mem(victim);
            }
            
            /* remove from unsorted list */
            REFLECT_SET(&unsorted_chunks(av)->bk, bck);
            unsorted_chunks(av)->bk = bck;    /* MLM: SET */
            REFLECT_SET(&bck->fd, unsorted_chunks(av));
            bck->fd = unsorted_chunks(av);    /* MLM: SET */
            
            /* Take now instead of binning if exact fit */
            if (size == nb)
            {
                set_inuse_bit_at_offset(victim, size);
                check_malloced_chunk(victim, nb);
                
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
            
            REFLECT_SET(&victim->bk, bck);
            victim->bk = bck;    /* MLM: SET */
            REFLECT_SET(&victim->fd, fwd);
            victim->fd = fwd;    /* MLM: SET */
            REFLECT_SET(&fwd->bk, victim);
            fwd->bk = victim;    /* MLM: SET */
            REFLECT_SET(&bck->fd, victim);
            bck->fd = victim;    /* MLM: SET */
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
                    
                    check_malloced_chunk(victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);
                    REFLECT_SET(&unsorted_chunks(av)->bk, remainder);
                    REFLECT_SET(&unsorted_chunks(av)->fd, remainder);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                    REFLECT_SET(&remainder->bk, unsorted_chunks(av));
                    REFLECT_SET(&remainder->fd, unsorted_chunks(av));
                    remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */
                    
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    
                    check_malloced_chunk(victim, nb);
                    
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
                map &= ~bit; /* OUCH */
                REFLECT_SET(&av->binmap[block], map);
                av->binmap[block] = map; /* Write through */    /* MLM: SET */
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
                REFLECT_SET(&bin->bk, bck);
                bin->bk = bck;    /* MLM: SET */
                REFLECT_SET(&bck->fd, bin);
                bck->fd = bin;    /* MLM: SET */
                
                /* Exhaust */
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(victim, size);
                    
                    check_malloced_chunk(victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);

                    REFLECT_SET(&unsorted_chunks(av)->bk, remainder);
                    REFLECT_SET(&unsorted_chunks(av)->fd, remainder);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                    REFLECT_SET(&remainder->bk, unsorted_chunks(av));
                    REFLECT_SET(&remainder->fd, unsorted_chunks(av));
                    remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */

                    /* advertise as last remainder */
                    if (in_smallbin_range(nb)) 
                    {
                        REFLECT_SET(&av->last_remainder, remainder);
                        av->last_remainder = remainder;     /* MLM: SET */
                    }
                    
                    set_head(victim, nb | PREV_INUSE);
                    set_head(remainder, remainder_size | PREV_INUSE);
                    set_foot(remainder, remainder_size);
                    
                    check_malloced_chunk(victim, nb);
                    
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
         * to put in fenceposts in sysmalloc.)
         */
        victim = av->top;
        size = chunksize(victim);
        
        if ((unsigned long)(size) >= (unsigned long)(nb + MINSIZE))
        {
            remainder_size = size - nb;
            remainder = chunk_at_offset(victim, nb);

            REFLECT_SET(&av->top, remainder);
            av->top = remainder;    /* MLM: SET */
            
            set_head(victim, nb | PREV_INUSE);
            set_head(remainder, remainder_size | PREV_INUSE);
            
            check_malloced_chunk(victim, nb);
            
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
            
            malloc_consolidate(av);
            idx = smallbin_index(nb); /* restore original bin index */
        }
        /* 
         *  Otherwise, relay to handle system-dependent cases 
         */
        else 
        {
            return sysmalloc(nb, av);    
        }
    }
}

/*
 * ------------------------------ free ------------------------------
 */
void
dlfree(void* mem)
{
    mstate av = get_malloc_state();
    
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
        
        check_inuse_chunk(p);
        
        /*
         * If eligible, place chunk on a fastbin so it can be found
         * and used quickly in malloc.
         */
        if ((unsigned long)(size) <= (unsigned long)(av->max_fast))
        {
            set_fastchunks(av);
            
            fb = &(av->fastbins[fastbin_index(size)]);

            REFLECT_SET(&p->fd, *fb);
            p->fd = *fb;    /* MLM: SET */
            REFLECT_SET(fb, p);
            *fb = p;    /* MLM: SET */
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

                REFLECT_SET(&p->bk, bck);
                p->bk = bck;    /* MLM: SET */
                REFLECT_SET(&p->fd, fwd);
                p->fd = fwd;    /* MLM: SET */
                REFLECT_SET(&bck->fd, p);
                bck->fd = p;    /* MLM: SET */
                REFLECT_SET(&bck->bk, p);
                fwd->bk = p;    /* MLM: SET */
                
                set_head(p, size | PREV_INUSE);
                set_foot(p, size);
                
                check_free_chunk(p);
            }
            /*
             *  If the chunk borders the current high end of memory,
             *  consolidate into top
             */
            else
            {
                size += nextsize;
                set_head(p, size | PREV_INUSE);

                REFLECT_SET(&av->top, p);
                av->top = p;    /* MLM: SET */

                check_chunk(p);
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
                    malloc_consolidate(av);
                }
            }
        }
    }
}

/*
 * ------------------------- malloc_consolidate -------------------------
 *
 * malloc_consolidate is a specialized version of free() that tears
 * down chunks held in fastbins.  Free itself cannot be used for this
 * purpose since, among other things, it might place chunks back onto
 * fastbins.  So, instead, we need to use a minor variant of the same
 * code.
 * 
 * Also, because this routine needs to be called the first time through
 * malloc anyway, it turns out to be the perfect place to trigger
 * initialization code.
 */
static void
malloc_consolidate(mstate av)
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
                REFLECT_SET(fb, 0);
                *fb = 0;    /* MLM: SET */
                
                do
                {
                    check_inuse_chunk(p);
                    
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

                        REFLECT_SET(&unsorted_bin->fd, p);
                        unsorted_bin->fd = p;    /* MLM: SET */
                        REFLECT_SET(&first_unsorted->bk, p);
                        first_unsorted->bk = p;    /* MLM: SET */
                        
                        set_head(p, size | PREV_INUSE);

                        REFLECT_SET(&p->bk, unsorted_bin);
                        p->bk = unsorted_bin;    /* MLM: SET */
                        REFLECT_SET(&p->fd, first_unsorted);
                        p->fd = first_unsorted;    /* MLM: SET */

                        set_foot(p, size);
                    }
                    else
                    {
                        size += nextsize;
                        set_head(p, size | PREV_INUSE);

                        REFLECT_SET(&av->top, p);
                        av->top = p;    /* MLM: SET */
                    }
                }
                while ( (p = nextp) != 0);
                
            }
        }
        while (fb++ != maxfb);
    }
    else
    {
        malloc_init_state(av);
        
        check_malloc_state();
    }
}

/*
 * ------------------------------ realloc ------------------------------
 */
void *
dlrealloc(void* oldmem, size_t bytes)
{
    mstate av = get_malloc_state();
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
        return dlmalloc(bytes);
    }
    
    checked_request2size(bytes, nb);
    
    oldp    = mem2chunk(oldmem);
    oldsize = chunksize(oldp);
    
    check_inuse_chunk(oldp);
    
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

            REFLECT_SET(&av->top, chunk_at_offset(oldp, nb));
            av->top = chunk_at_offset(oldp, nb);    /* MLM: SET */
            
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
            newmem = dlmalloc(nb - MALLOC_ALIGN_MASK);
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
                    REFLECT_SET(d+0, *(s+0));
                    *(d+0) = *(s+0);    /* MLM: SET */
                    REFLECT_SET(d+1, *(s+1));
                    *(d+1) = *(s+1);    /* MLM: SET */
                    REFLECT_SET(d+2, *(s+2));
                    *(d+2) = *(s+2);    /* MLM: SET */
                    if (ncopies > 4)
                    {
                        REFLECT_SET(d+3, *(s+3));
                        *(d+3) = *(s+3);    /* MLM: SET */
                        REFLECT_SET(d+4, *(s+4));
                        *(d+4) = *(s+4);    /* MLM: SET */
                        if (ncopies > 6)
                        {
                            REFLECT_SET(d+5, *(s+5));
                            *(d+5) = *(s+5);    /* MLM: SET */
                            REFLECT_SET(d+6, *(s+6));
                            *(d+6) = *(s+6);    /* MLM: SET */
                            if (ncopies > 8)
                            {
                                REFLECT_SET(d+7, *(s+7));
                                *(d+7) = *(s+7);    /* MLM: SET */
                                REFLECT_SET(d+8, *(s+8));
                                *(d+8) = *(s+8);    /* MLM: SET */
                            }
                        }
                    }
                }
                
                dlfree(oldmem);
                
                check_inuse_chunk(newp);
                
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
            dlfree(chunk2mem(remainder)); 
        }
        
        check_inuse_chunk(newp);
        
        return chunk2mem(newp);
    }
  
    check_malloc_state();
  
    return 0;
}

/*
 * ------------------------------ memalign ------------------------------
 */
void *
dlmemalign(size_t alignment, size_t bytes)
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
        return dlmalloc(bytes);
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
    m  = (char *)(dlmalloc(nb + alignment + MINSIZE));
    
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
        
        dlfree(chunk2mem(p));
        
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
        
        dlfree(chunk2mem(remainder));
    }
    
    check_inuse_chunk(p);
    
    return chunk2mem(p);
}

/*
 * ------------------------------ calloc ------------------------------
 */
void *
dlcalloc(size_t n_elements, size_t elem_size)
{
    mchunkptr p;
    unsigned long clearsize;
    unsigned long nclears;
    size_t* d;
    
    void* mem = dlmalloc(n_elements * elem_size);
    
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
            REFLECT_SET(d+0, 0);
            *(d+0) = 0;    /* MLM: SET */
            REFLECT_SET(d+1, 0);
            *(d+1) = 0;    /* MLM: SET */
            REFLECT_SET(d+2, 0);
            *(d+2) = 0;    /* MLM: SET */
            if (nclears > 4)
            {
                REFLECT_SET(d+3, 0);
                *(d+3) = 0;    /* MLM: SET */
                REFLECT_SET(d+4, 0);
                *(d+4) = 0;    /* MLM: SET */
                if (nclears > 6)
                {
                    REFLECT_SET(d+5, 0);
                    *(d+5) = 0;    /* MLM: SET */
                    REFLECT_SET(d+6, 0);
                    *(d+6) = 0;    /* MLM: SET */
                    if (nclears > 8)
                    {
                        REFLECT_SET(d+7, 0);
                        *(d+7) = 0;    /* MLM: SET */
                        REFLECT_SET(d+8, 0);
                        *(d+8) = 0;    /* MLM: SET */
                    }
                }
            }
        }
    }

    return mem;
}

#if defined(MALLOC_TEST)

#define CORE_SIZE   (16 * 1024 * 1024)

void *
local_alloc(ptrdiff_t size)
{
    if (size < 0)
    {
        return (void *)MORECORE_FAILURE;
    }
    else if (size == 0)
    {
        return (void *)curbrk;
    }
    else
    {
        if ((curbrk + size) >= top)
        {
            return (void *)MORECORE_FAILURE;
        }
        else
        {
            void *ret;

            ret = curbrk;
            curbrk += size;

            return ret;
        }
    }
}

int
main(int argc, char **argv)
{
    int i, j, nelts;
    char **elts;
    int *eltsz;
    int tot;

    base = malloc(CORE_SIZE + malloc_getpagesize);
    memset(base, 0, CORE_SIZE + malloc_getpagesize);
    rbase = malloc(CORE_SIZE + malloc_getpagesize);
    memset(rbase, 0, CORE_SIZE + malloc_getpagesize);
    if (base == NULL || rbase == NULL)
    {
        fprintf(stderr, "Not enough memory\n");

        exit(0);
    }

    if (CORE_SIZE == 0)
    {
        printf("CORE_SIZE is 0\n");

        exit(0);
    }

    /* align base */
    holdbase = base;
    rholdbase = rbase;
    base = (char *)((int)(base + malloc_getpagesize) &
                    ~(malloc_getpagesize - 1));
    rbase = (char *)((int)(rbase + malloc_getpagesize) &
                     ~(malloc_getpagesize - 1));

    if (base - holdbase < sizeof(struct malloc_state) ||
        rbase - rholdbase < sizeof(struct malloc_state))
    {
        fprintf(stderr, "No space for state\n");

        exit(0);
    }
    curbrk = base;
    rcurbrk = rbase;
    top = base + CORE_SIZE;
    rtop = rbase + CORE_SIZE;

    srand((unsigned)time(NULL));

    for (i = 0; i < 1000; i++)
    {
        nelts = rand() % 1024;

        elts = (char **)dlmalloc(nelts * sizeof(char *));
        if (elts == NULL)
        {
            printf("elts went NULL at %d for eltsz %d\n",
                   i, nelts);

            abort();
        }

        eltsz = (int *)dlmalloc(nelts * sizeof(int));
        if (eltsz == NULL)
        {
            printf("eltsz went NULL at %d for eltsz %d\n",
                   i, nelts);

            abort();
        }

        tot = 0;
        for (j = 0; j < nelts; j++)
        {
            eltsz[j] = (rand() % 32767) + 1;
            REFLECT_SET(&eltsz[j], eltsz[j]);
            elts[j] = dlmalloc(eltsz[j]);
            REFLECT_SET(&elts[j], elts[j]);

            tot += eltsz[j];

            if (elts[j])
            {
                REFLECT_MEMSET(elts[j], j % 255, eltsz[j]);
                memset(elts[j], j % 255, eltsz[j]);
            }
        }

        printf("total allocated: %gM\n", (double)tot / (double)(1024*1024));

        for (j = 0; j < nelts; j++)
        {
            if (elts[j])
            {
                dlfree(elts[j]);
            }
            else
            {
                printf("elts[%d] is NULL at i %d size %d\n", j, i, eltsz[j]);
            }
        }
        dlfree(eltsz);
        dlfree(elts);
    }

    if (memcmp(base - sizeof(struct malloc_state),
               rbase - sizeof(struct malloc_state),
               CORE_SIZE + sizeof(struct malloc_state)) != 0)
    {
        unsigned long *b, *r;

        printf("Bzzt.  You failed\n");

        b = (unsigned long *)(base - sizeof(struct malloc_state));
        r = (unsigned long *)(rbase - sizeof(struct malloc_state));
        if ((char *)b + sizeof(struct malloc_state) != base ||
            (char *)r + sizeof(struct malloc_state) != rbase)
        {
            printf("POINTER MISMATCH\n");
        }
        for (i = 0; i < (CORE_SIZE + sizeof(struct malloc_state)) / sizeof(unsigned long); i++)
        {
            if (*b != *r)
            {
                printf("diff at %d: %08lx vs %08lx ", i * sizeof(unsigned long), *b, *r);
                printf("offset %d vs %d\n", (char *)b - base, (char *)r - rbase);
            }
            b++;
            r++;
        }
    }

    free(holdbase);
    free(rholdbase);

    return (0);
}
#endif
