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
 * LOG: Revision 9.1.8.1  2005/11/30 10:18:36  sjaddu
 * LOG: Porting to MVL on power pc.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:22  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:51:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.6  2003/01/30 20:48:17  mmiers
 * LOG: Init the superclass pointer.
 * LOG:
 * LOG: Revision 7.5  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.4  2003/01/24 16:41:42  mmiers
 * LOG: Remove HASH defines
 * LOG:
 * LOG: Revision 7.3  2002/10/28 18:52:23  mmiers
 * LOG: 64 bit build cleanup.
 * LOG:
 * LOG: Revision 7.2  2002/09/11 16:22:18  yranade
 * LOG: Forte can't handle non-constant initializers in a struct
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.17  2002/06/24 16:45:59  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.16  2002/06/24 16:03:49  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.15  2002/06/21 21:27:11  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.14  2002/06/21 21:09:27  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.13  2002/06/21 20:01:46  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.12  2002/06/21 19:34:45  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.11  2002/06/21 19:30:43  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.10  2002/06/20 22:48:47  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.9  2002/06/20 20:52:03  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.8  2002/06/20 19:53:09  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.7  2002/06/14 22:20:52  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.6  2002/06/14 21:39:33  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.5  2002/06/14 21:07:50  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.4  2002/06/14 19:06:20  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.3  2002/06/13 21:52:25  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.2  2002/06/12 21:55:45  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:42:29  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#include <its_dsm_sci.h>
#include <dsm_sci_impl.h>
#include <its_app.h>
#include <its_assertion.h>
#include <its_trace.h>
#include <its_timers.h>
#include <its_iniparse.h>
#include <its_thread.h>
#include <engine.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ident "$Id: dsm_sci_impl.c,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"


/*****************************************************************************
 *
 * Note: this file is essentially divided into the following sections:
 *
 *  1) Forward declarations and definitions.
 *  1) Allocator related (definitions).
 *  2) DSMHASH class (table manager).
 *  3) DSM SCI Data class.
 *  4) Allocator related (implementation).
 *  5) DSM SCI Impl (implementation) class.
 *  6) DSM SCI Engine Parser Extension related functions.
 *
 *****************************************************************************/

/* 
 * Wisdom: acetylsalicylic acid required to understand this file -- HLD.
 */


/******************************************************************************
 ******************************************************************************
 **
 ** TODO: to be relocated.
 **
 */

/* Relocate in its.h */

#define ITS_ESCIERROR        -1000


/* Relocate in its_timers.h */

typedef struct {
    ITS_TIME secs;
    ITS_TIME usecs;
} ITS_UTime;

ITS_UTime
TIMERS_GetCurrentUTime()
{
    ITS_UTime utime;
    TIMERS_UTime(&utime.secs, &utime.usecs);
    return utime;
}

ITS_UTime
TIMERS_UTimeFromTime(ITS_TIME time)
{
    ITS_UTime utime;

    utime.secs = time;
    utime.usecs = 0;

    return utime;
}

ITS_UTime
TIMERS_UTimeFromSecs(ITS_ULONG secs)
{
    ITS_UTime utime;

    utime.secs = secs;
    utime.usecs =  0;

    return utime;
}

ITS_UTime
TIMERS_UTimeFromMillisecs(ITS_ULONG millisecs)
{
    ITS_UTime utime;

    utime.secs = millisecs / MILLISEC_PER_SEC;
    utime.usecs = millisecs % MILLISEC_PER_SEC;

    return utime;
}

ITS_UTime
TIMERS_UTimeFromUsecs(ITS_ULONG usecs)
{
    ITS_UTime utime;

    utime.secs = usecs / USEC_PER_SEC;
    utime.usecs = usecs % USEC_PER_SEC;

    return utime;
}


ITS_UTime 
TIMERS_SubUTime(ITS_UTime utime, ITS_UTime delta)
{
    ITS_UTime result;

    result.secs  = utime.secs  - delta.secs;
    result.usecs = utime.usecs - delta.usecs;

    if (result.usecs < 0)
    {
            result.usecs = result.usecs + USEC_PER_SEC;
            result.secs--;
    } 

    return result;
}

ITS_UTime 
TIMERS_AddUTime(ITS_UTime utime, ITS_UTime delta)
{
    ITS_UTime result;

    result.secs  = utime.secs  + delta.secs;
    result.usecs = utime.usecs + delta.usecs;

    if (result.usecs >= USEC_PER_SEC)
    {
            result.usecs = result.usecs - USEC_PER_SEC;
            result.secs++;
    }

    return result;
}

int 
TIMERS_CompareUTime(ITS_UTime utime1, ITS_UTime utime2)
{
    if (utime1.secs  > utime2.secs)
    {
        return 1;
    }
    else if (utime1.secs  < utime2.secs)
    {
        return -1;
    }
    else if (utime1.usecs > utime2.usecs)
    {
        return 1;
    }
    else if (utime1.usecs < utime2.usecs )
    {
        return -1;
    }
    else
    {
        return 0;
    }
}


/******************************************************************************
 ******************************************************************************
 **
 ** Forward declarations and definitions.
 **
 */

/*
 * Common SCI defines.
 */

#define NO_FLAGS      0
#define NO_CALLBACK   0

/*
 * Cache sizes. TODO: review. Where this is coming from?
 */

#ifdef __sparc
#define DSM_CACHE_SIZE 2097152U
#else
#define DSM_CACHE_SIZE 8192U
#endif


static THREAD_RET_TYPE MonitorThread(void* arg);

/*
 * Reflection functions.
 */

static int  MemSet(
                DSM_DataObject* dataObj, 
                ITS_UINT value,
                ITS_UINT size, 
                ITS_UINT offset);

static int  MemCpy(
                DSM_DataObject* dataObj, 
                void* privateSrc,
                ITS_UINT size, 
                ITS_UINT offset);

/*
 * Reflection macros.
 */

#define REFLECT_MEMCPY(dataObj, d, s, n)                                    \
    do                                                                      \
    {                                                                       \
        if ((char *)(d) < (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr || \
            (char *)(d) >= DSM_DATA_MEM_DATA(dataObj)->top)                 \
        {                                                                   \
            abort();                                                        \
        }                                                                   \
        MemCpy(                                                             \
            dataObj,                                                        \
            (ITS_UINT *)s,                                                  \
            (ITS_UINT)n,                                                    \
            ((char *)(d) - (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr));\
    }                                                                       \
    while (0)

#define REFLECT_MEMSET(dataObj, d, v, n)                                    \
    do                                                                      \
    {                                                                       \
        if ((char *)(d) < (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr || \
            (char *)(d) >= DSM_DATA_MEM_DATA(dataObj)->top)                 \
        {                                                                   \
            abort();                                                        \
        }                                                                   \
        MemSet(                                                             \
            dataObj,                                                        \
            (ITS_UINT)(v),                                                  \
            (n),                                                            \
            ((char *)(d) - (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr));\
    }                                                                       \
    while (0)

#define REFLECT_SET(dataObj, d, v)                                          \
    do                                                                      \
    {                                                                       \
        if ((char *)(d) < (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr || \
            (char *)(d) >= DSM_DATA_MEM_DATA(dataObj)->top)                 \
        {                                                                   \
            abort();                                                        \
        }                                                                   \
        if (sizeof(v) != sizeof(unsigned long))                             \
        {                                                                   \
            abort();                                                        \
        }                                                                   \
        MemSet(                                                             \
            dataObj,                                                        \
            (ITS_ULONG)(v),                                                  \
            sizeof(unsigned long),                                          \
            ((char *)(d) - (char *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr));\
    }                                                                       \
    while (0)

/*
 * Other functions.
 */

static void MonitorWaitForPendingTrans(DSM_DataObject* dataObj);


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
/* MLM: SET */
#define MALLOC_COPY(dataObj, dest, src, nbytes)     \
    do                                              \
    {                                               \
        REFLECT_MEMCPY(dataObj, dest, src, nbytes); \
        memcpy(dest, src, nbytes);                  \
    }                                               \
    while (0)

/* MLM: SET */
#define MALLOC_ZERO(dataObj, dest, nbytes)          \
    do                                              \
    {                                               \
        REFLECT_MEMSET(dataObj, dest, 0, nbytes);   \
        memset(dest, 0, nbytes);                    \
    }                                               \
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
/* MLM: SET */
#define set_inuse(dataObj, p)                                           \
    do                                                                  \
    {                                                                   \
        REFLECT_SET(dataObj,                                            \
                    &((mchunkptr)(((char*)(p)) +                        \
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
#define clear_inuse(dataObj, p)                                         \
    do                                                                  \
    {                                                                   \
        REFLECT_SET(dataObj,                                            \
                    &((mchunkptr)(((char*)(p)) +                        \
                                  ((p)->size & ~PREV_INUSE)))->size =   \
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
#define set_inuse_bit_at_offset(dataObj, p, s)                      \
    do                                                              \
    {                                                               \
        REFLECT_SET(dataObj,                                        \
                    &((mchunkptr)(((char*)(p)) + (s)))->size,       \
                    ((mchunkptr)(((char*)(p)) + (s)))->size |       \
                    PREV_INUSE);                                    \
        (((mchunkptr)(((char*)(p)) + (s)))->size |= PREV_INUSE);    \
    }                                                               \
    while (0)


/* MLM: SET */
#define clear_inuse_bit_at_offset(dataObj, p, s)                    \
    do                                                              \
    {                                                               \
        REFLECT_SET(dataObj,                                        \
                    &((mchunkptr)(((char*)(p)) + (s)))->size,       \
                    ((mchunkptr)(((char*)(p)) + (s)))->size &       \
                    ~(PREV_INUSE));                                 \
        (((mchunkptr)(((char*)(p)) + (s)))->size &= ~(PREV_INUSE)); \
    }                                                               \
    while (0)


/* Set size at head, without disturbing its use bit */
/* MLM: SET */
#define set_head_size(dataObj, p, s)                        \
    do                                                      \
    {                                                       \
        REFLECT_SET(dataObj,                                \
                    &(p)->size,                             \
                    (((p)->size & PREV_INUSE) | (s)));      \
        ((p)->size = (((p)->size & PREV_INUSE) | (s)));     \
    }                                                       \
    while (0)

/* Set size/use field */
/* MLM: SET */
#define set_head(dataObj, p, s) \
    do                          \
    {                           \
        REFLECT_SET(dataObj,    \
                    &(p)->size, \
                    (s));       \
        ((p)->size = (s));      \
    }                           \
    while (0)

/* Set size at footer (only when chunk is not in use) */
/* MLM: SET */
#define set_foot(dataObj, p, s)                                     \
    do                                                              \
    {                                                               \
        REFLECT_SET(dataObj,                                        \
                    &((mchunkptr)((char*)(p) + (s)))->prev_size,    \
                    (s));                                           \
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
/* MLM: SET */
#define unlink(dataObj, P, BK, FD)  \
    do                              \
    {                               \
        FD = P->fd;                 \
        BK = P->bk;                 \
        REFLECT_SET(dataObj,        \
                    &FD->bk,        \
                    BK);            \
        FD->bk = BK;                \
        REFLECT_SET(dataObj,        \
                    &BK->fd,        \
                    FD);            \
        BK->fd = FD;                \
    }                               \
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

/* MLM: SET */
#define mark_bin(dataObj,m,i)                           \
    do                                                  \
    {                                                   \
        REFLECT_SET(dataObj,                            \
                    &(m)->binmap[idx2block(i)],         \
                    (m)->binmap[idx2block(i)] |         \
                    idx2bit(i));                        \
        ((m)->binmap[idx2block(i)] |=  idx2bit(i));     \
    }                                                   \
    while (0)

/* MLM: SET */
#define unmark_bin(dataObj, m,i)                        \
    do                                                  \
    {                                                   \
        REFLECT_SET(dataObj,                            \
                    &(m)->binmap[idx2block(i)],         \
                    (m)->binmap[idx2block(i)] &         \
                    ~(idx2bit(i)));                     \
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

/* MLM: SET */
#define clear_fastchunks(dataObj, M)        \
    do                                      \
    {                                       \
        REFLECT_SET(dataObj,                \
                    &(M)->max_fast,         \
                    (M)->max_fast |         \
                    FASTCHUNKS_BIT);        \
        ((M)->max_fast |=  FASTCHUNKS_BIT); \
    }                                       \
    while (0)

/* MLM: SET */
#define set_fastchunks(dataObj, M)          \
    do                                      \
    {                                       \
        REFLECT_SET(dataObj,                \
                    &(M)->max_fast,         \
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
#define set_max_fast(dataObj, M, s)                         \
    do                                                      \
    {                                                       \
        REFLECT_SET(dataObj,                                \
                    &(M)->max_fast,                         \
                    (((s) == 0)                             \
                     ? SMALLBIN_WIDTH                       \
                     : request2size(s)) | FASTCHUNKS_BIT);  \
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


/******************************************************************************
 ******************************************************************************
 **
 ** DSMHASH class (table manager).
 **
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
UniqueKey(
    HASH_Table db)
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
CreateTable(ITS_Object obj, va_list args)
{
    HASH_Table db  = (HASH_Table)obj;
    DSM_DataObject* dataObj;

    ITS_TRACE_DEBUG(("CreateTable:\n"));

    dataObj = va_arg(args, DSM_DataObject*);

    DSMHASH_DATA_OBJECT(db) = dataObj;

    return (ITS_SUCCESS);
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Iterate a virtual hashtable (identified by its resource id or rid). 
 *      The input parameter iterateEntryDataFn is a pointer to a function with
 *      the signature [int Function(ITS_POINTER data, void* in, void* out)]. 
 *      This iterate function must be user provided and depends of the purpose
 *      of the iteration.
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      in - pointer to input data passed to iterate entry function.
 *      iterateEntryFn - pointer to iterate entry function.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to output data passed to iterate entry function.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static int 
VTableIterate(
    HASH_Table db, 
    ITS_UINT rid,
    void* in, 
    void* out, 
    DSM_IterateEntryProc iterateEntryFn)
{
    HASH_TableEntry* pentry;
    HASH_TableEntry entry, next;
    int i;
    int res;

    ITS_TRACE_DEBUG(("VTableIterate:\n"));

    if (db == NULL || iterateEntryFn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == rid)
            {
                ITS_POINTER ptr = entry->data + sizeof(DSM_RowHeader);

                res = iterateEntryFn(ptr, in, out);

                if (res != ITS_SUCCESS)
                {
                    return res;
                }
            }
        
            next = entry->next;
        }
    }

    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Size of a virtual hashtable.
 *
 *  Input Parameters:
 *      dataObj - DSM implementation specific data.
 *      tableId - virtual hashtable table identifier.      
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      size - number of entries in the virtual hashtable.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static int 
VTableGetSize(
    DSM_DataObject* dataObj, 
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG(("VTableGetSize:\n"));

    if (size == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    *size = DSM_DATA_TABLES_INFO(dataObj)[tableId].entries;

    return ITS_SUCCESS;
}

/*.implementation:static
 *****************************************************************************
 *  Purpose:
 *      Dump a virtual hashtable (identified by its resource id or rid). The
 *      input parameter dumpEntryDataFn is a pointer to a function with the
 *      signature [int Function(ITS_POINTER data, char** pStrDump)]. This 
 *      dump function must be user provided and depends of the type of the
 *      data stored in the hashtable. It must allocate a character string
 *      (using *pStrDump = malloc...) and return ITS_SUCCESS or an ITS error
 *      code. The character string will be deallocated by HASH_VTableDump
 *      after use. Nothing specific is done to separate the dumps of each
 *      entries, therefore this must be done inside the dump function (e.g.
 *      adding '\n' and/or "----------").
 *
 *  Input Parameters:
 *      db - hashtable.
 *      rid - resource id (identifies a virtual hashtable).
 *      dumpEntryFn - pointer to function that allows to dump the data of an
 *          entry.
 *
 *  Input/Output Parameters:
 *      pStrDump - pointer to a character string. The character string is 
 *          allocated by HASH_VTableDump and therefore must be deallocated
 *          by the user (after usage).
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS or an ITS error code.
 *
 *  Notes:
 *
 *  See Also:
 *****************************************************************************/
static int 
VTableDump(
    HASH_Table db, 
    ITS_UINT rid,
    char** pStrDump, 
    HASH_DumpEntryData dumpEntryFn)
{
    HASH_TableEntry* pentry;
    HASH_TableEntry entry, next;
    int i;
    int res;
    char* strEntryDump;

    ITS_TRACE_DEBUG(("VTableDump:\n"));

    if (db == NULL || pStrDump == NULL || dumpEntryFn == NULL)
    {
        return ITS_EINVALIDARGS;
    }

    /* Initialization. */
    *pStrDump = (char *)malloc(1 * sizeof(char));
    if (*pStrDump == NULL)
    {
        ITS_TRACE_ERROR(("VTableDump: out of memory\n"));

        return ITS_ENOMEM;
    }

    **pStrDump = '\0'; 

    /* Iterate hashtable. */
    for (i = HASH_MASK(db) + 1, pentry = HASH_TABLE(db); --i >= 0; pentry++)
    {
        for (entry = *pentry; entry; entry = next)
        {
            if (entry->rid == rid)
            {
                ITS_POINTER ptr = entry->data + sizeof(DSM_RowHeader);

                strEntryDump = NULL;

                res = dumpEntryFn(ptr, &strEntryDump);

                if (res != ITS_SUCCESS)
                {
                    if (strEntryDump != NULL)
                    {
                        free(strEntryDump);
                    }

                    return res;
                }

                /* + 1 = security. */
                *pStrDump = (char *)realloc(
                                *pStrDump,
                                strlen(*pStrDump) * sizeof(char) +
                                    strlen(strEntryDump) * sizeof(char) + 1);
                if (*pStrDump == NULL)
                {
                    free(strEntryDump);
                    return ITS_ENOMEM;
                }

                strcat(*pStrDump, strEntryDump);
                free(strEntryDump);
            }
        
            next = entry->next;
        }
    }

    return ITS_SUCCESS;
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
        CreateTable,                        /* instance create          */
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
        VTableDump,                         /* VTable dump method       */
        (HASH_VTableIterateProc)VTableIterate,/* iterate entry method   */
        HashAlloc,                          /* Allocation procedure     */
        HashFree                            /* Free procedure           */
    }
};

static ITS_Class itsDSMHASH_Class = (ITS_Class)&itsDSMHASH_ClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (SCI) Data class.
 **
 */


/*
 * DMAs local memory to remote.
 */
static int
Dma(
    DSM_DataObject* dataObj,
    ITS_UINT size, 
    ITS_UINT offset)
{
    sci_dma_queue_t         dmaQueue;
    sci_error_t             error;

    ITS_C_REQUIRE(IsDsmStateSyncMaster(DSM_DATA_STATE_DATA(dataObj).state));

    SCICreateDMAQueue(DSM_DATA_CONNECTION(dataObj).sd,
        &dmaQueue,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        1,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "Dma [FtGroupId: %u]: SCICreateDMAQueue failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    SCIEnqueueDMATransfer(
        dmaQueue,
        DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        DSM_DATA_REMOTE_MEMBER(dataObj).segment,
        offset,
        offset,
        size,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "Dma [FtGroupId: %u]: SCIEnqueueDMATransfer failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    SCIPostDMAQueue(
        dmaQueue,
        NO_CALLBACK,
        NULL,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "Dma [FtGroupId: %u]: SCIPostDMAQueue failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    /* TODO: review. We might not want infinite timeout. */
    SCIWaitForDMAQueue(
        dmaQueue,
        SCI_INFINITE_TIMEOUT,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "Dma [FtGroupId: %u]: SCIWaitForDMAQueue failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    SCIRemoveDMAQueue(
        dmaQueue, 
        NO_FLAGS, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "Dma [FtGroupId: %u]: SCIRemoveDMAQueue failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

/*
 * Memcopies private memory to remote.
 */
static int
MemCpy(
    DSM_DataObject* dataObj, 
    void* privateSrc, 
    ITS_UINT size, 
    ITS_UINT offset)
{
    sci_sequence_status_t   status;
    sci_error_t             error;
    int                     retryValue;
#if !defined(WIN32)
    unsigned int            fullsize;
    unsigned int            offsize = 0;
#endif /* !defined(WIN32) */

    if (!IsDsmStateOpTwoMb(DSM_DATA_STATE_DATA(dataObj).state))
    {
        return ITS_SUCCESS;
    }

    retryValue = (int)DSM_DATA_CONFIG(dataObj).retryValue;

    do 
    {
        status = SCIStartSequence(
                    DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                    NO_FLAGS,
                    &error);
        if (error != SCI_ERR_OK) 
        {
            ITS_TRACE_ERROR((
                "MemCpy [FtGroupId: %u]: SCIStartSequence failed: 0x%X\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                error));
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }
    } 
    while (status != SCI_SEQ_OK && retryValue-- > 0);

    if (status != SCI_SEQ_OK || retryValue < 0)
    {
        ITS_TRACE_DEBUG((
            "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due to "
            "error with remote\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
        return ITS_ESCIERROR;
    }

    /**************************************************************************
     *
     * Transfer of data begin.
     *
     */

#if defined(WIN32)

    memcpy(
        (char *)DSM_DATA_REMOTE_MEMBER(dataObj).mapAddr + offset, 
        privateSrc, 
        size);

#else /* !defined(WIN32) */

    if (size <= DSM_CACHE_SIZE)
    {
        SCIMemCopy(
            privateSrc,
            DSM_DATA_REMOTE_MEMBER(dataObj).map,
            offset, 
            size,
            NO_FLAGS,
            &error);
        if (error != SCI_ERR_OK)
        {
            ITS_TRACE_ERROR((
                "MemCpy [FtGroupId: %u]: SCIMemCopy failed: 0x%X\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                error));
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }
    }
    else
    {
        fullsize = size;

        while (size > DSM_CACHE_SIZE)
        {
            size    = size / 2;
            offsize = size;
        }

        while (offsize <= fullsize)
        {
            SCIMemCopy(
                (((ITS_UINT *)privateSrc) + ((offsize - size) / 4)),
                DSM_DATA_REMOTE_MEMBER(dataObj).map, 
                (offsize - size + offset),
                size,
                NO_FLAGS,
                &error);
            if (error != SCI_ERR_OK)
            {
                ITS_TRACE_ERROR((
                    "MemCpy [FtGroupId: %u]: SCIMemCopy failed: 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE MB"
                    " due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }

            offsize = size + offsize;
        }

        size = fullsize;
        offsize = 0;
    }

#endif /* defined(WIN32) */

    /*
     * Transfer of data end.
     *
     *************************************************************************/

    status = SCICheckSequence(
                DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                NO_FLAGS,
                &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "MemCpy [FtGroupId: %u]: SCICheckSequence failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        ITS_TRACE_DEBUG((
            "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due to "
            "error with remote\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
        return ITS_ESCIERROR;
    }

    retryValue = (int)DSM_DATA_CONFIG(dataObj).retryValue;

    while (status != SCI_SEQ_OK && retryValue-- > 0) 
    {
        int retryValueBis = (int)DSM_DATA_CONFIG(dataObj).retryValue;

        switch (status) 
        {
        case SCI_SEQ_RETRIABLE:
            break;

        case SCI_SEQ_PENDING:
        case SCI_SEQ_NOT_RETRIABLE:
            do 
            {
                status = SCIStartSequence(
                            DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                            NO_FLAGS,
                            &error);
                if (error != SCI_ERR_OK) 
                {
                    ITS_TRACE_ERROR((
                        "MemCpy [FtGroupId: %u]: SCIStartSequence failed: "
                        "0x%X\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        error));
                    ITS_TRACE_DEBUG((
                        "MemCpy [FtGroupId: %u]: request change state to OP "
                        "ONE MB due to error with remote\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                    return ITS_ESCIERROR;
                }
            } 
            while (status != SCI_SEQ_OK && retryValueBis-- > 0);

            if (status != SCI_SEQ_OK || retryValueBis < 0)
            {
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE MB"
                    " due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }
            break;

        default:
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }

        /**********************************************************************
         *
         * Transfer of data begin.
         *
         */

#if defined(WIN32)

        memcpy(
            (char *)DSM_DATA_REMOTE_MEMBER(dataObj).mapAddr + offset,
            privateSrc,
            size);

#else /* !defined(WIN32) */

        if (size <= DSM_CACHE_SIZE)
        {
            SCIMemCopy(
                privateSrc,
                DSM_DATA_REMOTE_MEMBER(dataObj).map,
                offset, 
                size,
                NO_FLAGS,
                &error);
            if (error != SCI_ERR_OK)
            {
                ITS_TRACE_ERROR((
                    "MemCpy [FtGroupId: %u]: SCIMemCopy failed: 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE "
                    "MB due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }
        }
        else
        {
            fullsize = size;

            while (size > DSM_CACHE_SIZE)
            {
                size    = size / 2;
                offsize = size;
            }

            while (offsize <= fullsize)
            {
                SCIMemCopy(
                    (((ITS_UINT *)privateSrc) + ((offsize - size) / 4)),
                    DSM_DATA_REMOTE_MEMBER(dataObj).map, 
                    (offsize - size + offset),
                    size,
                    NO_FLAGS,
                    &error);
                if (error != SCI_ERR_OK)
                {
                    ITS_TRACE_ERROR((
                        "MemCpy [FtGroupId: %u]: SCIMemCopy failed: 0x%X\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        error));
                    ITS_TRACE_DEBUG((
                        "MemCpy [FtGroupId: %u]: request change state to OP "
                        "ONE MB due to error with remote\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                    return ITS_ESCIERROR;
                }

                offsize = size + offsize;
            }

            size = fullsize;
            offsize = 0;
        }

#endif /* defined(WIN32) */

        /*
         * Transfer of data end.
         *
         *********************************************************************/

        status = SCICheckSequence(
                    DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                    NO_FLAGS,
                    &error);
        if (error != SCI_ERR_OK)
        {
            ITS_TRACE_ERROR((
                "MemCpy [FtGroupId: %u]: SCICheckSequence failed: 0x%X\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                error));
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }
    }

    if (status != SCI_SEQ_OK || retryValue < 0)
    {
        ITS_TRACE_DEBUG((
            "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due to "
            "error with remote\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

/*
 * Memsets private memory to remote.
 */
static int
MemSet(
    DSM_DataObject* dataObj, 
    ITS_UINT value, 
    ITS_UINT size, 
    ITS_UINT offset)
{
    sci_sequence_status_t   status;
    sci_error_t             error;
    int                     retryValue;
    unsigned int            j;
    unsigned int            nostores;

    if (!IsDsmStateOpTwoMb(DSM_DATA_STATE_DATA(dataObj).state))
    {
        return ITS_SUCCESS;
    }

    nostores = size / sizeof(unsigned int);

    for (j = (offset / 4); j < ((offset / 4) + nostores); j++)
    {
        retryValue = (int)DSM_DATA_CONFIG(dataObj).retryValue;

        do 
        {
            status = SCIStartSequence(
                        DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                        NO_FLAGS,
                        &error);
            if (error != SCI_ERR_OK) 
            {
                ITS_TRACE_ERROR((
                    "MemCpy [FtGroupId: %u]: SCIStartSequence failed: 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE "
                    "MB due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }
        } 
        while (status != SCI_SEQ_OK && retryValue-- > 0);

        if (status != SCI_SEQ_OK || retryValue < 0)
        {
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }

        /**********************************************************************
         *
         * Transfer of data begin.
         *
         */

        ((ITS_UINT *)DSM_DATA_REMOTE_MEMBER(dataObj).mapAddr)[j] = value;

        /*
         * Transfer of data end.
         *
         *********************************************************************/

        status = SCICheckSequence(
                    DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                    NO_FLAGS,
                    &error);
        if (error != SCI_ERR_OK)
        {
            ITS_TRACE_ERROR((
                "MemCpy [FtGroupId: %u]: SCICheckSequence failed: 0x%X\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                error));
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }

        retryValue = (int)DSM_DATA_CONFIG(dataObj).retryValue;

        while (status != SCI_SEQ_OK && retryValue-- > 0) 
        {
            int retryValueBis = (int)DSM_DATA_CONFIG(dataObj).retryValue;

            switch (status) 
            {
            case SCI_SEQ_RETRIABLE:
                break;

            case SCI_SEQ_PENDING:
            case SCI_SEQ_NOT_RETRIABLE:
                do 
                {
                    status = SCIStartSequence(
                                DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                                NO_FLAGS,
                                &error);
                    if (error != SCI_ERR_OK) 
                    {
                        ITS_TRACE_ERROR((
                            "MemCpy [FtGroupId: %u]: SCIStartSequence failed: "
                            "0x%X\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            error));
                        ITS_TRACE_DEBUG((
                            "MemCpy [FtGroupId: %u]: request change state to "
                            "OP ONE MB due to error with remote\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));
                        DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                        return ITS_ESCIERROR;
                    }
                } 
                while (status != SCI_SEQ_OK && retryValueBis-- > 0);

                if (status != SCI_SEQ_OK || retryValueBis < 0)
                {
                    ITS_TRACE_DEBUG((
                        "MemCpy [FtGroupId: %u]: request change state to OP "
                        "ONE MB due to error with remote\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                    return ITS_ESCIERROR;
                }
                break;

            default:
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE MB"
                    " due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }

            /******************************************************************
             *
             * Transfer of data begin.
             *
             */

            ((ITS_UINT *)DSM_DATA_REMOTE_MEMBER(dataObj).mapAddr)[j] = value;

            /*
             * Transfer of data end.
             *
             *****************************************************************/

            status = SCICheckSequence(
                        DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
                        NO_FLAGS,
                        &error);
            if (error != SCI_ERR_OK)
            {
                ITS_TRACE_ERROR((
                    "MemCpy [FtGroupId: %u]: SCICheckSequence failed: 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));
                ITS_TRACE_DEBUG((
                    "MemCpy [FtGroupId: %u]: request change state to OP ONE "
                    "MB due to error with remote\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
                return ITS_ESCIERROR;
            }
        }

        if (status != SCI_SEQ_OK || retryValue < 0)
        {
            ITS_TRACE_DEBUG((
                "MemCpy [FtGroupId: %u]: request change state to OP ONE MB due"
                " to error with remote\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_TRUE;
            return ITS_ESCIERROR;
        }
    }

    return ITS_SUCCESS;
}

static void
CallMembershipChangeCallbacks(
    DSM_DataObject* dataObj,
    DSM_MembershipChangeType membershipChangeType)
{
    /* TODO: review. */
}

static void
CallCriticalErrorNotificationCallbacks(
    DSM_DataObject* dataObj,
    int lineNumber,
    const char* format,
    ...)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_CriticalErrorNotificationCbData criticalErrorNotificationCbData;
    va_list alist;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(format != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    if (CALLBACK_IsListEmpty(
            DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(coreObj)))
    {
        /* 
         * No critical error notification callbacks => abort in DSM subsystem.
         */

        abort();

        return; /* Not reached. */
    }

    /* Initialize variable arguments. */
    va_start(alist, format);

    criticalErrorNotificationCbData.ftGroupId = DSM_INST_FT_GROUP_ID(instObj);
    criticalErrorNotificationCbData.fileName = __FILE__;
    criticalErrorNotificationCbData.lineNumber = lineNumber;
    criticalErrorNotificationCbData.format = format;
    /*   
    criticalErrorNotificationCbData.alist = alist;
    */
    __va_copy( criticalErrorNotificationCbData.alist, alist );

    ret = CALLBACK_CallCallbackList(
                DSM_CORE_CRITICAL_ERROR_NOTIFICATION_CALLBACKS(coreObj),
                (ITS_POINTER)coreObj,
                (ITS_POINTER)&criticalErrorNotificationCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }

    /* Reset variable arguments. */
    va_end(alist);
}


/*
 * DataClassInitialize.
 */
static int
DataClassInitialize(
    ITS_Class objClass)
{
    sci_error_t error;

    SCIInitialize(NO_FLAGS, &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_CRITICAL((
            "SCIInitialize failed: 0x%X\n", error));
        return ITS_ESCIERROR;
    }

    /* Dependency on socket subsystem. */
    return ITS_InitializeClass(itsSOCKET_Class);
}

/*
 * DataClassTerminate.
 */
static void
DataClassTerminate(
    ITS_Class objClass)
{
    /* Dependency on socket subsystem. */
    ITS_DestroyClass(itsSOCKET_Class);

    SCITerminate();
}

/* 
 * DSM state (SCI) to string.
 */
static const char*
StateToStr(
    ITS_UINT state)
{
    switch (state)
    {
    case DSM_STATE_INITIAL:
        return "INITIAL";
    case DSM_STATE_JOINING:
        return "JOINING";
    case DSM_STATE_SYNC_SLAVE:
        return "SYNC SLAVE";
    case DSM_STATE_SYNC_MASTER:
        return "SYNC MASTER";
    case DSM_STATE_OP_ONE_MB:
        return "OP ONE MB";
    case DSM_STATE_OP_TWO_MB:
        return "OP TWO MB";
    default:
        return "UNKNOWN";
    }
}

static int
ConfigCreate(
    DSM_DataObject* dataObj,
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    RESFILE_Manager* configDb;
    char value[DSM_MAX_CONFIG_VALUE_SIZE];
    char ftGroupSectionName[DSM_MAX_CONFIG_SECTION_NAME_SIZE];
    char buffer[16];

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    /* Build Fault Tolerance Group associated section name. */
    strcpy(ftGroupSectionName, DSM_FT_GROUP_STRING);
    sprintf(buffer, "%u", ftGroupId);
    strcat(ftGroupSectionName, buffer);

    configDb = DSM_CORE_CONFIG_DB(coreObj);

    if (configDb)
    {
        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_LOCAL_ADAPTER_NO_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_LOCAL_ADAPTER_NO_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_REMOTE_ADAPTER_NO_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_REMOTE_MEMBER(dataObj).adapterNo = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_REMOTE_ADAPTER_NO_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_LOCAL_NODE_ID_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_LOCAL_MEMBER(dataObj).nodeId = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_LOCAL_NODE_ID_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_REMOTE_NODE_ID_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_REMOTE_MEMBER(dataObj).nodeId = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_REMOTE_NODE_ID_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_LOCAL_SEGMENT_ID_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_LOCAL_MEMBER(dataObj).segmentId = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_LOCAL_SEGMENT_ID_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_REMOTE_SEGMENT_ID_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_REMOTE_MEMBER(dataObj).segmentId = 
                (ITS_UINT)RESFILE_ParseNum(value);
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_REMOTE_SEGMENT_ID_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_LOCAL_BASE_IRT_NO_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 0;

            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 1;

            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrtNo =
                (ITS_UINT)RESFILE_ParseNum(value) + 2;

            DSM_DATA_LOCAL_MEMBER(dataObj).opIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 3;
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_LOCAL_BASE_IRT_NO_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_REMOTE_BASE_IRT_NO_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 0;

            DSM_DATA_REMOTE_MEMBER(dataObj).masterIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 1;
            
            DSM_DATA_REMOTE_MEMBER(dataObj).syncIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 2;

            DSM_DATA_REMOTE_MEMBER(dataObj).opIrtNo = 
                (ITS_UINT)RESFILE_ParseNum(value) + 3;
        }
        else
        {
            ITS_TRACE_CRITICAL((
                "[FtGroupId: %u] You must specify '%s' in the configuration\n",
                ftGroupId,
                DSM_SCI_REMOTE_BASE_IRT_NO_STRING));
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_IRT_JOIN_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).irtJoinTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).irtJoinTimeout = 
                DSM_DEFAULT_IRT_JOIN_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_IRT_TRIGGER_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).irtTriggerTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).irtTriggerTimeout = 
                DSM_DEFAULT_IRT_TRIGGER_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_IRT_TRIGGER_INTERVAL_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).irtTriggerInterval = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).irtTriggerInterval = 
                DSM_DEFAULT_IRT_TRIGGER_INTERVAL;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_IRT_WAIT_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).irtWaitTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).irtWaitTimeout = 
                DSM_DEFAULT_IRT_WAIT_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_IRT_CONNECT_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).irtConnectTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).irtConnectTimeout = 
                DSM_DEFAULT_IRT_CONNECT_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_SEGMENT_CONNECT_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).segmentConnectTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).segmentConnectTimeout = 
                DSM_DEFAULT_SEGMENT_CONNECT_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_SYNC_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).syncTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).syncTimeout = 
                DSM_DEFAULT_SYNC_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_PING_INTERVAL_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).pingInterval = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).pingInterval = 
                DSM_DEFAULT_PING_INTERVAL;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_FLOW_CTRL_WND_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).flowCtrlWnd = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).flowCtrlWnd = 
                DSM_DEFAULT_FLOW_CTRL_WND;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_RETRY_VALUE_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).retryValue = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).retryValue = 
                DSM_DEFAULT_RETRY_VALUE;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_SCI_LOCAL_DEBUG_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).localDebug = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).localDebug = 
                DSM_DEFAULT_LOCAL_DEBUG;
        }
    }
    else
    {
        abort();
    }

    return ITS_SUCCESS;
}

static int
ConfigDestroy(
    DSM_DataObject* dataObj)
{
    /* Nothing to do. */
    return ITS_SUCCESS;
}

static int
TidAllocatorCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_TID_ALLOCATOR(dataObj).currentTid = 0;

    ret = MUTEX_CreateMutex(&DSM_DATA_TID_ALLOCATOR(dataObj).lock, 0);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TidAllocatorDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    MUTEX_DeleteMutex(&DSM_DATA_TID_ALLOCATOR(dataObj).lock);

    return ITS_SUCCESS;
}

static int
TcbCreate(
    DSM_DataObject* dataObj,
    DSM_Tcb** tcb)
{
    int ret;

    ITS_C_REQUIRE(tcb != NULL);

    *tcb = calloc(1, sizeof(DSM_Tcb));

    if (*tcb == NULL)
    {
        ITS_TRACE_ERROR((
            "TcbCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_ENOMEM;
    }

    (*tcb)->tid         = 0;
    (*tcb)->threadId    = 0;
    (*tcb)->tableId     = 0;
    (*tcb)->next        = NULL;

    ret = MUTEX_CreateMutex(&(*tcb)->condVarGuard, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        free(*tcb);
        *tcb = NULL;
        return ret;
    }


    ret = CONDVAR_Create(&(*tcb)->condVar);

    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbCreate [FtGroupId: %u]: CONDVAR_Create failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_DeleteMutex(&(*tcb)->condVarGuard);
        free(*tcb);
        *tcb = NULL;
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TcbDestroy(
    DSM_DataObject* dataObj,
    DSM_Tcb* tcb)
{
    ITS_C_REQUIRE(tcb != NULL);

    MUTEX_DeleteMutex(&tcb->condVarGuard);
    CONDVAR_Delete(&tcb->condVar);
    free(tcb);
    return ITS_SUCCESS;
}

static int
TcbManagerCreate(
    DSM_DataObject* dataObj)
{
    int ret;
    DSM_TcbManager* tcbManager;

    ITS_C_REQUIRE(dataObj != NULL);

    tcbManager = &DSM_DATA_TCB_MANAGER(dataObj);

    ITS_C_ASSERT(tcbManager != NULL);

    tcbManager->activeListHead = NULL;
    tcbManager->activeListTail = NULL;

    ret = MUTEX_CreateMutex(&tcbManager->activeListLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbManagerCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    tcbManager->activeEntries = 0;

    tcbManager->freeList = NULL;

    ret = MUTEX_CreateMutex(&tcbManager->freeListLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbManagerCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&tcbManager->activeListLock);
        return ret;
    }

    tcbManager->freeEntries = 0;

    return ITS_SUCCESS;
}

static int 
TcbManagerDestroy(
    DSM_DataObject* dataObj)
{
    int ret;
    DSM_TcbManager* tcbManager;
    DSM_Tcb* tmp;

    ITS_C_REQUIRE(dataObj != NULL);

    tcbManager = &DSM_DATA_TCB_MANAGER(dataObj);

    ITS_C_ASSERT(tcbManager != NULL);

    for (tmp = tcbManager->activeListHead; 
         tmp != NULL; 
         tcbManager->activeListHead = tmp)
    {
        tmp = tcbManager->activeListHead->next;

        ret = TcbDestroy(dataObj, tcbManager->activeListHead);

        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "TcbManagerDestroy [FtGroupId: %u]: TcbDestroy failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    tcbManager->activeListHead  = NULL;
    tcbManager->activeListTail  = NULL;
    tcbManager->activeEntries   = 0;

    MUTEX_DeleteMutex(&tcbManager->activeListLock);

    for (tmp = tcbManager->freeList; tmp != NULL; tcbManager->freeList = tmp)
    {
        tmp = tcbManager->freeList->next;

        ret = TcbDestroy(dataObj, tcbManager->freeList);

        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "TcbManagerDestroy [FtGroupId: %u]: TcbDestroy failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    tcbManager->freeList    = NULL;
    tcbManager->freeEntries = 0;

    MUTEX_DeleteMutex(&tcbManager->freeListLock);

    return ITS_SUCCESS;
}

static int
SciVirtualDeviceCreate(
    DSM_DataObject* dataObj)
{
    sci_error_t error;

    SCIOpen(&DSM_DATA_CONNECTION(dataObj).sd, NO_FLAGS, &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "SciVirtualDeviceCreate [FtGroupId: %u]: SCIOpen failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

static int
SciVirtualDeviceDestroy(
    DSM_DataObject* dataObj)
{
    sci_error_t error;

    SCIClose(DSM_DATA_CONNECTION(dataObj).sd, NO_FLAGS, &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "SciVirtualDeviceDestroy [FtGroupId: %u]: SCIClose failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

static int
LocalMemberCreate(
    DSM_DataObject* dataObj,
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    sci_error_t error;
    volatile void* addr;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    SCICreateInterrupt(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        &DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrtNo,
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCICreateInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    SCICreateInterrupt(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        &DSM_DATA_LOCAL_MEMBER(dataObj).masterIrtNo,
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCICreateInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    SCICreateInterrupt(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        &DSM_DATA_LOCAL_MEMBER(dataObj).syncIrtNo,
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCICreateInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    SCICreateInterrupt(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        &DSM_DATA_LOCAL_MEMBER(dataObj).opIrtNo,
        NO_CALLBACK, 
        NULL, 
        SCI_FLAG_FIXED_INTNO, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCICreateInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    SCICreateSegment(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        DSM_DATA_LOCAL_MEMBER(dataObj).segmentId,
        DSM_INST_DSM_SIZE(instObj),
        NO_CALLBACK,
        NULL,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCICreateSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    SCIPrepareSegment(
        DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCIPrepareSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveSegment(
            DSM_DATA_LOCAL_MEMBER(dataObj).segment,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    addr = SCIMapLocalSegment(
                DSM_DATA_LOCAL_MEMBER(dataObj).segment,
                &DSM_DATA_LOCAL_MEMBER(dataObj).map,
                0,
                DSM_INST_DSM_SIZE(instObj),
                (void*)DSM_INST_DSM_BASE_ADDRESS(instObj),
                SCI_FLAG_FIXED_MAP_ADDR,
                &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCIMapLocalSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIRemoveSegment(
            DSM_DATA_LOCAL_MEMBER(dataObj).segment,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    ITS_TRACE_DEBUG((
        "LocalMemberCreate [FtGroupId: %u]: SCIMapLocalSegment succeeded: %u "
        "bytes at address 0x%X\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_INST_DSM_SIZE(instObj),
        addr));

    DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr = addr;

    SCISetSegmentAvailable(
        DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: SCISetSegmentAvailable failed:"
            " 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIUnmapSegment(
            DSM_DATA_LOCAL_MEMBER(dataObj).map, 
            NO_FLAGS, 
            &error);
        SCIRemoveSegment(
            DSM_DATA_LOCAL_MEMBER(dataObj).segment,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
            NO_FLAGS,
            &error);
        SCIRemoveInterrupt(
            DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

static int
LocalMemberDestroy(
    DSM_DataObject* dataObj)
{
    sci_error_t error;

    ITS_C_REQUIRE(dataObj != NULL);

    SCISetSegmentUnavailable(
        DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCISetSegmentUnavailable "
            "failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIUnmapSegment(
        DSM_DATA_LOCAL_MEMBER(dataObj).map, 
        NO_FLAGS, 
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIUnmapSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIRemoveSegment(
        DSM_DATA_LOCAL_MEMBER(dataObj).segment,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIRemoveSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIRemoveInterrupt(
        DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIRemoveInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIRemoveInterrupt(
        DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIRemoveInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIRemoveInterrupt(
        DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIRemoveInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIRemoveInterrupt(
        DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "LocalMemberDestroy [FtGroupId: %u]: SCIRemoveInterrupt failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    return ITS_SUCCESS;
}

static int
RemoteMemberCreate(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    /* Nothing to do. */
    return ITS_SUCCESS;
}

static int
RemoteMemberDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    /* Nothing to do. */
    return ITS_SUCCESS;
}

static int
MemDataCreate(
    DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_Object object;
    size_t i;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    /* 
     * Initialize shared memory data. 
     */

    DSM_DATA_MEM_DATA(dataObj) = 
        (DSM_MemData *)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr;

    /* MUST be initialized to zero (contains struct malloc state). */
    memset(DSM_DATA_MEM_DATA(dataObj), 0, sizeof(DSM_MemData));

#if defined(DEBUG) || defined(_DEBUG)
    memset(
        (ITS_POINTER)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr, 
        0, 
        DSM_INST_DSM_SIZE(instObj));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    DSM_DATA_MEM_DATA(dataObj)->size    = 
        DSM_INST_DSM_SIZE(instObj);
    DSM_DATA_MEM_DATA(dataObj)->base    = 
        (ITS_POINTER)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr + 
            malloc_getpagesize;
    DSM_DATA_MEM_DATA(dataObj)->curbrk  = 
        DSM_DATA_MEM_DATA(dataObj)->base;
    DSM_DATA_MEM_DATA(dataObj)->top     = 
        (ITS_POINTER)DSM_DATA_LOCAL_MEMBER(dataObj).mapAddr + 
            DSM_INST_DSM_SIZE(instObj);

    /*
     * First allocation is guaranteed to behave identically in all processes. 
     * Therefore the hash table creation does not need synchronization.
     *
     * If current process end-ups being a slave (that will do synchronization
     * with a master), the first allocation will be wiped out and replaced by
     * the master data.
     *
     * Note: This table MUST NEVER be freed.
     */

    DSM_DATA_MEM_DATA(dataObj)->tables = 
        dlcalloc(dataObj, 1, sizeof(DSMHASH_TableRec));

    if (DSM_DATA_MEM_DATA(dataObj)->tables == NULL)
    {
        return ITS_ENOMEM;
    }

    object = ITS_ConstructObjectIn(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        itsDSMHASH_Class,
                        dataObj);
    if (object == NULL)
    {
        return ITS_ENOMEM;
    }

    /*
     * Main lock related.
     */

    DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId = 
        (ITS_UINT)DSM_INVALID_NODE_ID;

    /* 
     * Dsm info related. 
     */

    DSM_DATA_DSM_INFO(dataObj).lock.counter     = 0;
    DSM_DATA_DSM_INFO(dataObj).lock.threadId    = 0;
    DSM_DATA_DSM_INFO(dataObj).lock.nodeId      = DSM_INVALID_NODE_ID;

    /*
     * Tables info related.
     */

    DSM_DATA_TABLES_INFO(dataObj) = 
        dlcalloc(
            dataObj, 
            DSM_INST_MAX_NUM_TABLES(instObj), 
            sizeof(DSM_TableInfo));
    if (DSM_DATA_TABLES_INFO(dataObj) == NULL)
    {
        return ITS_ENOMEM;
    }

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        DSM_DATA_TABLES_INFO(dataObj)[i].lock.nodeId = DSM_INVALID_NODE_ID;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_TABLES_LOCK(dataObj), 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MemDataCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
MemDataDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    MUTEX_DeleteMutex(&DSM_DATA_TABLES_LOCK(dataObj));

    return ITS_SUCCESS;
}

static int
MonitorCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = SEMA_CreateSemaphore(&DSM_DATA_MONITOR(dataObj).startSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MonitorCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = SEMA_CreateSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MonitorCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);
        return ret;
    }

    /* Initialize exit thread boolean. */
    DSM_DATA_MONITOR(dataObj).exitThread = ITS_FALSE;

    /* Initialize started boolean. */
    DSM_DATA_MONITOR(dataObj).started = ITS_FALSE;

    ret = MUTEX_CreateMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MonitorCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);
        return ret;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MonitorCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);
        return ret;
    }

    /* Initialize waiting transactions. */
    DSM_DATA_MONITOR(dataObj).waitingTrans = 0;

    /* Initialize pending transactions. */
    DSM_DATA_MONITOR(dataObj).pendingTrans = 0;

    /* Create and start monitor thread. */
    ret = THREAD_CreateThread(
            &DSM_DATA_MONITOR(dataObj).thread,
            0,
            MonitorThread,
            (void*)dataObj,
            ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MonitorCreate [FtGroupId: %u]: THREAD_CreateThread failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
        MUTEX_DeleteMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
        SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);
        return ret;
    }

    return ITS_SUCCESS;
}

static int
MonitorDestroy(
    DSM_DataObject* dataObj)
{
    int ret;
    void* status = NULL;

    ITS_C_REQUIRE(dataObj != NULL);

    /* Terminate procedures thread. */
    DSM_DATA_MONITOR(dataObj).exitThread = ITS_TRUE;

    /* Wait for procedures thread to terminate. */
    ret = THREAD_WaitForThread(&DSM_DATA_MONITOR(dataObj).thread, &status);
    if (ret == ITS_SUCCESS)
    {
        ITS_TRACE_DEBUG((
            "MonitorDestroy [FtGroupId: %u]: monitor thread successfully"
            " terminated\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_ERROR((
            "MonitorDestroy [FtGroupId: %u]: THREAD_WaitForThread failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    MUTEX_DeleteMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    MUTEX_DeleteMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
    SEMA_DeleteSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);

    return ITS_SUCCESS;
}

static int
StateDataCreate(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_FALSE;

    return ITS_SUCCESS;
}

static int
StateDataDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_FALSE;

    return ITS_SUCCESS;
}

static int
JoinDataCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = SEMA_CreateSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "JoinDataCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = SEMA_CreateSemaphore(&DSM_DATA_JOIN_DATA(dataObj).leaveSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "JoinDataCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        SEMA_DeleteSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema);
        return ret;
    }

    return ITS_SUCCESS;
}

static int
JoinDataDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    SEMA_DeleteSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema);
    SEMA_DeleteSemaphore(&DSM_DATA_JOIN_DATA(dataObj).leaveSema);

    return ITS_SUCCESS;
}

static int
SyncDataCreate(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    return ITS_SUCCESS;
}

static int
SyncDataDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    return ITS_SUCCESS;
}


/*
 * LocalHash.
 */
#define DSM_HASH_SMALL_PRIME        (7)
#define DSM_HASH_MEDIAN_PRIME       (131)
#define DSM_HASH_16_BITS_MAX_PRIME  (65531)
#define DSM_HASH_16_BITS_MASK       (0x0000FFFF)

static ITS_INT
LocalHash(
    ITS_OCTET *key, 
    ITS_UINT klen)
{
    ITS_INT ret = DSM_HASH_MEDIAN_PRIME;
    ITS_UINT i;

    for (i = 0; i < klen; i++)
    {
        /* Protect against an input of all 1's with a small prime. */
        if (key[i] == 1)
        {
            ret *= DSM_HASH_SMALL_PRIME;
        }
        /* Protect againt zero killing the hash. */
        else if (key[i])
        {
            ret *= key[i];
        }
        /* If zero then square. */
        else
        {
            ret *= ret;
        }

        /* 
         * Multiplications may have resulted in a zeroed lower half word. If
         * lower word is clear then permute things a bit.
         */
        if (!(ret & DSM_HASH_16_BITS_MASK))
        {
            ret += DSM_HASH_16_BITS_MAX_PRIME;
        }
    }

    return (ret);
}

/*
 * Allocate a Tcb.
 */
static int
AllocateTcb(
    DSM_DataObject* dataObj, 
    DSM_Tcb** tcb)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(tcb != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "AllocateTcb [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    if (DSM_DATA_TCB_MANAGER(dataObj).freeList != NULL)
    {
        *tcb = DSM_DATA_TCB_MANAGER(dataObj).freeList;

        DSM_DATA_TCB_MANAGER(dataObj).freeList = (*tcb)->next;

        (*tcb)->tid = 0;
        (*tcb)->next = NULL;

        ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "AllocateTcb [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            return ret;
        }

        return ITS_SUCCESS;
    }
    else
    {
        ret = TcbCreate(dataObj, tcb);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "AllocateTcb [FtGroupId: %u]: TcbCreate failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
            return ret;
        }

        ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "AllocateTcb [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            return ret;
        }

        return ITS_SUCCESS;
    }
}

/*
 * Free Tcb (in practice, return it to the free list).
 */
static int
FreeTcb(
    DSM_DataObject* dataObj, 
    DSM_Tcb* tcb)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(tcb != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "FreeTcb [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    if (DSM_DATA_TCB_MANAGER(dataObj).freeList != NULL)
    {
        DSM_Tcb* tmp = DSM_DATA_TCB_MANAGER(dataObj).freeList;

        DSM_DATA_TCB_MANAGER(dataObj).freeList = tcb;

        tcb->next = tmp;
    }
    else
    {
        DSM_DATA_TCB_MANAGER(dataObj).freeList = tcb;

        tcb->tid        = 0;
        tcb->threadId   = 0;
        tcb->tableId    = 0;
        tcb->next       = NULL;
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).freeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "FreeTcb [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

/*
 *  Allocate a Tid.
 */
static ITS_UINT
AllocateTid(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_UINT result = 0;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_TID_ALLOCATOR(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "AllocateTid [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    DSM_DATA_TID_ALLOCATOR(dataObj).currentTid++;

    result = DSM_DATA_TID_ALLOCATOR(dataObj).currentTid;

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TID_ALLOCATOR(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "AllocateTid [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    return result;
}

/*
 * Lock related.
 */

static ITS_BOOLEAN
MainLockIsLockedBySelf(DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj = DSM_DATA_CORE_OBJECT(dataObj);

    if (DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId == 
        (ITS_UINT)DSM_CORE_NODE_ID(coreObj))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
MainLockIsLockedByOther(DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj = DSM_DATA_CORE_OBJECT(dataObj);

    if ((DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId != 
         (ITS_UINT)DSM_CORE_NODE_ID(coreObj)) &&
        (DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId !=
         (ITS_UINT)DSM_INVALID_NODE_ID))
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
MainLockIsUnlocked(DSM_DataObject* dataObj)
{
    if (DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId == 
        (ITS_UINT)DSM_INVALID_NODE_ID)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static int
MainLockLock(DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj = DSM_DATA_CORE_OBJECT(dataObj);

    ITS_C_REQUIRE(MainLockIsUnlocked(dataObj));

    DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId = 
        (ITS_UINT)DSM_CORE_NODE_ID(coreObj);

    REFLECT_MEMSET(
        dataObj,
        &DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId,
        (ITS_UINT)DSM_CORE_NODE_ID(coreObj),
        sizeof(ITS_UINT));

    ITS_C_ENSURE(MainLockIsLockedBySelf(dataObj));

    return ITS_SUCCESS;
}

static int
MainLockUnlock(DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(MainLockIsLockedBySelf(dataObj));

    DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId = 
        (ITS_UINT)DSM_INVALID_NODE_ID;

    REFLECT_MEMSET(
        dataObj,
        &DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId,
        (ITS_UINT)DSM_INVALID_NODE_ID,
        sizeof(ITS_UINT));

    ITS_C_ENSURE(MainLockIsUnlocked(dataObj));

    return ITS_SUCCESS;
}

static void
WaitingTransInc(DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }

    if (DSM_DATA_MONITOR(dataObj).waitingTrans < ((ITS_UINT)(-1)))
    {
        DSM_DATA_MONITOR(dataObj).waitingTrans++;
    }
    else
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: waitingTrans overflow\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }
}

static void
WaitingTransDec(DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }

    if (DSM_DATA_MONITOR(dataObj).waitingTrans > 0)
    {
        DSM_DATA_MONITOR(dataObj).waitingTrans--;
    }
    else
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: waitingTrans underflow\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }
}

static ITS_UINT
GetWaitingTrans(DSM_DataObject* dataObj)
{
    ITS_UINT result;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return 0;
    }

    result = DSM_DATA_MONITOR(dataObj).waitingTrans;

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).waitingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "WaitingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "WaitingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "WaitingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return 0;
    }

    return result;
}

static void
PendingTransInc(DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }

    if (DSM_DATA_MONITOR(dataObj).pendingTrans < ((ITS_UINT)(-1)))
    {
        DSM_DATA_MONITOR(dataObj).pendingTrans++;
    }
    else
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: pendingTrans overflow\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }
}

static void
PendingTransDec(DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }

    if (DSM_DATA_MONITOR(dataObj).pendingTrans > 0)
    {
        DSM_DATA_MONITOR(dataObj).pendingTrans--;
    }
    else
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: pendingTrans underflow\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return;
    }
}

static ITS_UINT
GetPendingTrans(DSM_DataObject* dataObj)
{
    ITS_UINT result;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return 0;
    }

    result = DSM_DATA_MONITOR(dataObj).pendingTrans;

    ret = MUTEX_ReleaseMutex(&DSM_DATA_MONITOR(dataObj).pendingTransLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "PendingTransInc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "PendingTransInc [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "PendingTransInc [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
        return 0;
    }

    return result;
}


/*
 * DataCreateInstance.
 */
static int
DataCreateInstance(
    ITS_Object obj, 
    va_list args)
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

    DSM_DATA_CORE_OBJECT(dataObj) = coreObj;
    DSM_DATA_INST_OBJECT(dataObj) = instObj;

    /* TODO: review. */
    /* Check maximum Fault Tolerance Group members (i.e. processes). */
    /*if (DSM_CORE_MAX_NUM_PROCESSES(coreObj) > DSM_MAX_MEMBERS)     */
    /*{                                                              */
        /* TODO: add trace. */
        /*return ITS_EINVCONFIG;*/
    /*}*/

    /* Config create. */
    ret = ConfigCreate(dataObj, ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: ConfigCreate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Tid Allocator create. */
    ret = TidAllocatorCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: TidAllocatorCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Tcb Manager create. */
    ret = TcbManagerCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: TcbManagerCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* SCI Virtual Device create. */
    ret = SciVirtualDeviceCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: SciVirtualDeviceCreate "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Local Member create. */
    ret = LocalMemberCreate(dataObj, ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: LocalMemberCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Remote Member create. */
    ret = RemoteMemberCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: RemoteMemberCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* State Data create. */
    ret = StateDataCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: StateDataCreate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RemoteMemberDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Join Data create. */
    ret = JoinDataCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: JoinDataCreate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        StateDataDestroy(dataObj);
        RemoteMemberDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Sync Data create. */
    ret = SyncDataCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: SyncDataCreate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMemberDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Mem Data create. */
    ret = MemDataCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: MemDataCreate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        SyncDataDestroy(dataObj);
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMemberDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Monitor create (MUST BE created last). */
    ret = MonitorCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: MonitorCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MemDataDestroy(dataObj);
        SyncDataDestroy(dataObj);
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMemberDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        SciVirtualDeviceDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    return ITS_SUCCESS;
}

/*
 * DataDestroyInstance.
 */
static void
DataDestroyInstance(
    ITS_Object obj)
{
    DSM_DataObject* dataObj;
    int ret;

    dataObj = (DSM_DataObject*)obj;

    /* Monitor destroy (MUST BE destroyed first). */
    ret = MonitorDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: MonitorDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Mem Data destroy. */
    ret = MemDataDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: MemDataDestroy "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Sync Data destroy. */
    ret = SyncDataDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: SyncDataDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Join Data destroy. */
    ret = JoinDataDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: JoinDataDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* State Data destroy. */
    ret = StateDataDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: StateDataDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Remote Member destroy. */
    ret = RemoteMemberDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: RemoteMemberDestroy failed:"
            " %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Local Member destroy. */
    ret = LocalMemberDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: LocalMemberDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* SCI Virtual Device destroy. */
    ret = SciVirtualDeviceDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: SciVirtualDeviceDestroy "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Tcb Manager destroy. */
    ret = TcbManagerDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: TcbManagerDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Tid Allocator destroy. */
    ret = TidAllocatorDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: TidAllocatorDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
   }

    /* Config destroy. */
    ret = ConfigDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: ConfigDestroy failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    DSM_DATA_CORE_OBJECT(dataObj) = NULL;
    DSM_DATA_INST_OBJECT(dataObj) = NULL;
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


static int
RemoteMemberConnect(
    DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    sci_error_t error;
    volatile void* addr;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    SCIConnectSegment(
        DSM_DATA_CONNECTION(dataObj).sd,
        &DSM_DATA_REMOTE_MEMBER(dataObj).segment,
        DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
        DSM_DATA_REMOTE_MEMBER(dataObj).segmentId,
        DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
        NO_CALLBACK,
        NULL,
        DSM_DATA_CONFIG(dataObj).segmentConnectTimeout,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberConnect [FtGroupId: %u]: SCIConnectSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        return ITS_ESCIERROR;
    }

    addr = SCIMapRemoteSegment(
                DSM_DATA_REMOTE_MEMBER(dataObj).segment,
                &DSM_DATA_REMOTE_MEMBER(dataObj).map,
                0,
                DSM_INST_DSM_SIZE(instObj),
                NULL,
                NO_FLAGS,
                &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberConnect [FtGroupId: %u]: SCIMapRemoteSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIDisconnectSegment(
            DSM_DATA_REMOTE_MEMBER(dataObj).segment,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    ITS_TRACE_DEBUG((
        "RemoteMemberConnect [FtGroupId: %u]: SCIMapRemoteSegment succeeded: %u "
        "bytes at address 0x%X\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_INST_DSM_SIZE(instObj),
        addr));

    DSM_DATA_REMOTE_MEMBER(dataObj).mapAddr = addr;

    SCICreateMapSequence(
        DSM_DATA_REMOTE_MEMBER(dataObj).map,
        &DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberConnect [FtGroupId: %u]: SCICreateMapSequence failed:"
            " 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
        SCIUnmapSegment(
            DSM_DATA_REMOTE_MEMBER(dataObj).map,
            NO_FLAGS,
            &error);
        SCIDisconnectSegment(
            DSM_DATA_REMOTE_MEMBER(dataObj).segment,
            NO_FLAGS,
            &error);
        return ITS_ESCIERROR;
    }

    return ITS_SUCCESS;
}

static int
RemoteMemberDisconnect(
    DSM_DataObject* dataObj)
{
    sci_error_t error;

    SCIRemoveSequence(
        DSM_DATA_REMOTE_MEMBER(dataObj).sequence,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberDisconnect [FtGroupId: %u]: SCIRemoveSequence failed:"
            " 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIUnmapSegment(
        DSM_DATA_REMOTE_MEMBER(dataObj).map,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberDisconnect [FtGroupId: %u]: SCIUnmapSegment failed: "
            "0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    SCIDisconnectSegment(
        DSM_DATA_REMOTE_MEMBER(dataObj).segment,
        NO_FLAGS,
        &error);
    if (error != SCI_ERR_OK)
    {
        ITS_TRACE_ERROR((
            "RemoteMemberDisconnect [FtGroupId: %u]: SCIDisconnectSegment "
            "failed: 0x%X\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            error));
    }

    return ITS_SUCCESS;
}

/*
 * SynchronizeDsm.
 */
static int
SynchronizeDsm(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    /*int ret;*/

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* TODO: to be implemented. */

    return ITS_SUCCESS;
}

/*
 * JoinFtGroup.
 */
static int
JoinFtGroup(
    DSM_CoreObject* coreObj, 
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_TIME startPollTime;
    ITS_TIME stopPollTime;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_C_ASSERT(IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state));

    /* Drain join semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema) == 
        ITS_SUCCESS)
    {
    }

    startPollTime = TIMERS_Time();

    stopPollTime = 
        startPollTime + 
            DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(instObj) / MILLISEC_PER_SEC;

    if (startPollTime == stopPollTime)
    {
        stopPollTime += 2;
    }

    while (!DSM_DATA_MONITOR(dataObj).started)
    {
        if (TIMERS_Time() >= stopPollTime)
        {
            ITS_TRACE_ERROR((
                "JoinFtGroup [FtGroupId: %u]: monitor thread not started\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            return ITS_ETIMEOUT;
        }

        TIMERS_Sleep(1);
    }

    /* Post monitor start semaphore. */
    ITS_TRACE_DEBUG((
        "JoinFtGroup [FtGroupId: %u]: ready to post monitor start semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_MONITOR(dataObj).startSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "JoinFtGroup [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        return ret;
    }

    ITS_TRACE_DEBUG((
        "JoinFtGroup [FtGroupId: %u]: monitor start semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     * Change state to JOINING (asynchronous change is OK).
     */

    ITS_TRACE_DEBUG((
        "JoinFtGroup [FtGroupId: %u]: change state to JOINING\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_JOINING;

    /* Wait for join semaphore to be posted. */
    ret = SEMA_WaitSemaphoreWithTimeOut(
            &DSM_DATA_JOIN_DATA(dataObj).joinSema,
            DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(instObj));
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        ITS_TRACE_ERROR((
            "JoinFtGroup [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_ERROR((
            "JoinFtGroup [FtGroupId: %u]: failed due to timeout\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ret;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup [FtGroupId: %u]: succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_TRUE;

    return ITS_SUCCESS;
}

/*
 * LeaveFtGroup.
 */
static int
LeaveFtGroup(
    DSM_CoreObject* coreObj, 
    ITS_USHORT ftGroupId)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Drain leave semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_JOIN_DATA(dataObj).leaveSema) == 
        ITS_SUCCESS)
    {
    }

    /* Post monitor stop semaphore. */
    ITS_TRACE_DEBUG((
        "LeaveFtGroup [FtGroupId: %u]: ready to post monitor stop semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LeaveFtGroup [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        return ret;
    }

    ITS_TRACE_DEBUG((
        "LeaveFtGroup [FtGroupId: %u]: monitor stop semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Wait for leave semaphore to be posted. */
    ret = SEMA_WaitSemaphoreWithTimeOut(
            &DSM_DATA_JOIN_DATA(dataObj).leaveSema,
            DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(instObj));
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        ITS_TRACE_ERROR((
            "LeaveFtGroup [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        ITS_TRACE_DEBUG((
            "LeaveFtGroup [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_ERROR((
            "LeaveFtGroup [FtGroupId: %u]: failed due to timeout\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ret;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "LeaveFtGroup [FtGroupId: %u]: succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_FALSE;

    return ITS_SUCCESS;
}

/******************************************************************************
 *
 * State transitions related functions.
 *
 */

static int
TransitionJoiningToOpOneMb(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionJoiningToOpOneMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Post monitor start semaphore. */
    ITS_TRACE_DEBUG((
        "TransitionJoiningToOpOneMb [FtGroupId: %u]: ready to post join semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionJoiningToOpOneMb [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }


    ITS_TRACE_DEBUG((
        "TransitionJoiningToOpOneMb [FtGroupId: %u]: join semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    return ITS_SUCCESS;
}

static int
TransitionJoiningToSyncSlave(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionJoiningToSyncSlave [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = RemoteMemberConnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionJoiningToSyncSlave [FtGroupId: %u]: RemoteMemberConnect"
            " failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionOpOneMbToSyncMaster(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionOpOneMbToSyncMaster [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    MonitorWaitForPendingTrans(dataObj);

    ret = RemoteMemberConnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionOpOneMbToSyncMaster [FtGroupId: %u]: "
            "RemoteMemberConnect failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionOpOneMbToSyncSlave(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionOpOneMbToSyncSlave [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    MonitorWaitForPendingTrans(dataObj);

    ret = RemoteMemberConnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionOpOneMbToSyncSlave [FtGroupId: %u]: RemoteMemberConnect"
            " failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionOpTwoMbToOpOneMb(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionOpTwoMbToOpOneMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = RemoteMemberDisconnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionOpTwoMbToOpOneMb [FtGroupId: %u]: "
            "RemoteMemberDisconnect failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionSyncSlaveToOpOneMb(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionSyncSlaveToOpOneMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));



    ret = RemoteMemberDisconnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionSyncSlaveToOpOneMb [FtGroupId: %u]: "
            "RemoteMemberDisconnect failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionSyncMasterToOpOneMb(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionSyncMasterToOpOneMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));



    ret = RemoteMemberDisconnect(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionSyncMasterToOpOneMb [FtGroupId: %u]: "
            "RemoteMemberDisconnect failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
TransitionSyncSlaveToOpTwoMb(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_TRACE_DEBUG((
        "TransitionSyncSlaveToOpTwoMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "TransitionSyncSlaveToOpTwoMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Post monitor start semaphore. */
    ITS_TRACE_DEBUG((
        "TransitionSyncSlaveToOpTwoMb [FtGroupId: %u]: ready to post join semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).joinSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TransitionSyncSlaveToOpTwoMb [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ITS_TRACE_DEBUG((
        "TransitionSyncSlaveToOpTwoMb [FtGroupId: %u]: join semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    return ITS_SUCCESS;
}

static int
TransitionSyncMasterToOpTwoMb(
    DSM_DataObject* dataObj)
{
    /*int ret;*/

    ITS_TRACE_DEBUG((
        "TransitionSyncMasterToOpTwoMb [FtGroupId: %u]: begin\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    return ITS_SUCCESS;
}


static void
MonitorWaitForPendingTrans(DSM_DataObject* dataObj)
{
    /* A simple function that does polling on the pending transactions
       number. Wait until there are no more pending transactions.
       To be used within state transitions. No timeout.
    */

    ITS_TRACE_DEBUG((
        "MonitorWaitForPendingTrans [FtGroupId: %u]: begin with %u pending transactions\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        GetPendingTrans(dataObj)));

    while (GetPendingTrans(dataObj) > 0)
    {
        TIMERS_USleep(
            DSM_DATA_CONFIG(dataObj).irtTriggerInterval * 
                USEC_PER_MILLISEC);
    }

    ITS_TRACE_DEBUG((
        "MonitorWaitForPendingTrans [FtGroupId: %u]: end\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
MonitorEnableTrans(DSM_DataObject* dataObj, ITS_UINT maxTransToEnable)
{
    ITS_UINT transEnabled;
    DSM_TcbManager* tcbManager;
    DSM_Tcb** iter;
    DSM_Tcb* prev;
    DSM_Tcb* tcb;
    int ret;


    /* TODO:
        This is where we browse the list of active TCB. For each Transaction 
        that is there (up to maxNumOfTrans) signal the condition variable. 
        Obvioulsy in the future will have to take into account the DsmLock,
        the TableLocks from the threadId and tableId available in the TCB 
        before deciding if a transaction can be enabled.
        It is in the transaction main code (i.e. DSM_CommitImpl) that the 
        waitingTrans has been incremented (before waiting on the TCB CondVar)
        therefore it is in the transaction main code that the waitingTrans is
        decremeted. But it is here in this function that the pendingTrans is 
        incremeted (decremented at the end of the transaction main code) or
        there is a race...
        As long as there will be pending transaction the MainLock will be 
        hold by the current node.
    */

    /* Remember that when doing state transitions, some cleanup will have to
       be done. There are also multiple synchronization pb when going into
       Sync slave or Sync master. Not transactions should be enabled there.
    */

    ITS_C_REQUIRE(dataObj != NULL);

    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add fatal error processing. */
        return;
    }

    transEnabled = 0;

    tcbManager = &DSM_DATA_TCB_MANAGER(dataObj);

    ITS_C_ASSERT(tcbManager != NULL);

    iter = &tcbManager->activeListHead;

    prev = NULL;
    
    while (*iter && transEnabled < maxTransToEnable)
    {
        tcb = *iter;

        /* TODO: add conditions on tcb: tableId, threadId... */
        if (ITS_TRUE) 
        {
            *iter = tcb->next;

            PendingTransInc(dataObj);

            /* 
             * Release DSM user thread (associated with transaction).
             */

            ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "MonitorEnableTrans [FtGroupId: %u]: MUTEX_AcquireMutex "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                MUTEX_ReleaseMutex(
                    &DSM_DATA_TCB_MANAGER(dataObj).activeListLock);

                ITS_TRACE_CRITICAL((
                    "MonitorEnableTrans [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorEnableTrans [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ret = CONDVAR_Signal(&tcb->condVar);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "MonitorEnableTrans [FtGroupId: %u]: CONDVAR_Signal "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                MUTEX_ReleaseMutex(
                    &DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
                MUTEX_ReleaseMutex(&tcb->condVarGuard);

                ITS_TRACE_CRITICAL((
                    "MonitorEnableTrans [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorEnableTrans [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "MonitorEnableTrans [FtGroupId: %u]: "
                    "MUTEX_ReleaseMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                MUTEX_ReleaseMutex(
                    &DSM_DATA_TCB_MANAGER(dataObj).activeListLock);

                ITS_TRACE_CRITICAL((
                    "MonitorEnableTrans [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorEnableTrans [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            if (DSM_DATA_CONFIG(dataObj).localDebug)
            {

                ITS_TRACE_DEBUG((
                    "MonitorEnableTrans [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    tcb->tid));
            }

            transEnabled++;

            tcbManager->activeEntries--;

            /* TODO: check return. */
            FreeTcb(dataObj, tcb);

            if (*iter == NULL)
            {
                tcbManager->activeListTail = prev;
            }
        }
        else
        {
            prev = *iter;

            iter = &((*iter)->next);
        }
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add fatal error processing. */
        return;
    }

    if (DSM_DATA_CONFIG(dataObj).localDebug)
    {
        ITS_TRACE_DEBUG((
            "MonitorEnableTrans [FtGroupId: %u]: %u transactions enabled\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            transEnabled));
    }
}

static void
MonitorManageTrans(DSM_DataObject* dataObj)
{
    if (IsDsmStateOpOneMb(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* TODO: enable all transactions. Review. */
        MonitorEnableTrans(dataObj, (ITS_UINT)(-1));

        return;
    }
    else if (IsDsmStateOpTwoMb(DSM_DATA_STATE_DATA(dataObj).state))
    {
        if (DSM_DATA_CONFIG(dataObj).localDebug)
        {
            ITS_TRACE_DEBUG((
                "MonitorManageTrans [FtGroupId: %u]: MainLock nodeId before: "
                "%u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId));
        }

        if (MainLockIsLockedBySelf(dataObj))
        {
            if (DSM_DATA_CONFIG(dataObj).localDebug)
            {
                ITS_TRACE_DEBUG((
                    "MonitorManageTrans [FtGroupId: %u]: MainLock locked by "
                    "self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }

            if (GetPendingTrans(dataObj) == 0)
            {
                if (DSM_DATA_CONFIG(dataObj).localDebug)
                {
                    ITS_TRACE_DEBUG((
                        "MonitorManageTrans [FtGroupId: %u]: MainLock locked "
                        "by self and no pending transactions: unlock\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                }

                MainLockUnlock(dataObj);
            }
        }
        else if (MainLockIsLockedByOther(dataObj))
        {
            if (DSM_DATA_CONFIG(dataObj).localDebug)
            {
                ITS_TRACE_DEBUG((
                    "MonitorManageTrans [FtGroupId: %u]: MainLock locked by "
                    "other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }
        }
        else if (MainLockIsUnlocked(dataObj))
        {
            if (DSM_DATA_CONFIG(dataObj).localDebug)
            {
                ITS_TRACE_DEBUG((
                    "MonitorManageTrans [FtGroupId: %u]: MainLock unlocked\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }

            if (GetWaitingTrans(dataObj) > 0)
            {
                if (DSM_DATA_CONFIG(dataObj).localDebug)
                {
                    ITS_TRACE_DEBUG((
                        "MonitorManageTrans [FtGroupId: %u]: MainLock unlocked "
                        "and waiting transactions: lock\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                }

                MainLockLock(dataObj);

                if (DSM_DATA_CONFIG(dataObj).localDebug)
                {
                    ITS_TRACE_DEBUG((
                        "MonitorManageTrans [FtGroupId: %u]: %u waiting "
                        "transactions. Enabling up to %u transactions\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        GetWaitingTrans(dataObj),
                        DSM_DATA_CONFIG(dataObj).flowCtrlWnd));
                }

                MonitorEnableTrans(
                    dataObj, 
                    DSM_DATA_CONFIG(dataObj).flowCtrlWnd);
            }
        }
        else
        {
            /* Ignore. */
        }

        if (DSM_DATA_CONFIG(dataObj).localDebug)
        {
            ITS_TRACE_DEBUG((
                "MonitorManageTrans [FtGroupId: %u]: MainLock nodeId "
                "after: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                DSM_DATA_MEM_DATA(dataObj)->mainLock.nodeId));
        }
    }
    else
    {
        /* TODO: review. Anything to do? */
    }
}

/******************************************************************************
 *
 * Monitor loop function (called repetitively by Monitor thread function).
 *
 */
static void
MonitorLoop(
    DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    ITS_UTime beginTriggerTime;
    ITS_UTime endTriggerTime;
    sci_error_t error;
    int ret;

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    if (DSM_DATA_CONFIG(dataObj).localDebug)
    {
        ITS_TRACE_DEBUG((
            "MonitorLoop [FtGroupId: %u]: current state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
    }

    switch (DSM_DATA_STATE_DATA(dataObj).state)
    {
    case DSM_STATE_INITIAL:
        TIMERS_Sleep(1);
        break;

    case DSM_STATE_JOINING:
        {
            SCIWaitForInterrupt(
                DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
                DSM_DATA_CONFIG(dataObj).irtJoinTimeout,
                NO_FLAGS,
                &error);
            if (error == SCI_ERR_TIMEOUT)
            {
                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionJoiningToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;
            }
            else if (error == SCI_ERR_OK)
            {
                SCIConnectInterrupt(
                    DSM_DATA_CONNECTION(dataObj).sd,
                    &DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                    DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                    DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                    DSM_DATA_REMOTE_MEMBER(dataObj).masterIrtNo,
                    DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error != SCI_ERR_OK)
                {
                    /*
                     * Change state to OP ONE MB.
                     */

                    ret = TransitionJoiningToOpOneMb(dataObj);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: review. */
                    }

                    ITS_TRACE_DEBUG((
                        "MonitorLoop [FtGroupId: %u]: change state to OP ONE "
                        "MB\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                    break;
                }

                /* 
                 * Trigger remote master interrupt.
                 */

                beginTriggerTime = TIMERS_GetCurrentUTime();

                endTriggerTime = 
                    TIMERS_AddUTime(
                        beginTriggerTime, 
                        TIMERS_UTimeFromMillisecs(
                            DSM_DATA_CONFIG(dataObj).irtTriggerTimeout));

                do
                {
                    SCITriggerInterrupt(
                        DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                        NO_FLAGS, 
                        &error);
                    if (error != SCI_ERR_OK)
                    {
                        ITS_TRACE_ERROR((
                            "MonitorLoop [FtGroupId: %u]: SCITriggerInterrupt "
                            "failed: 0x%X\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            error));

                        /* Ignore errors. */
                        SCIDisconnectInterrupt(
                            DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                            NO_FLAGS, 
                            &error);

                        /*
                         * Change state to OP ONE MB.
                         */

                        ret = TransitionJoiningToOpOneMb(dataObj);
                        if (ret != ITS_SUCCESS)
                        {
                            /* TODO: review. */
                        }

                        ITS_TRACE_DEBUG((
                            "MonitorLoop [FtGroupId: %u]: change state to OP ONE "
                            "MB\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));

                        DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                        break; /* Out of loop. */
                    } 
                    
                    TIMERS_USleep(
                        DSM_DATA_CONFIG(dataObj).irtTriggerInterval * 
                            USEC_PER_MILLISEC);
                }
                while (TIMERS_CompareUTime(
                            TIMERS_GetCurrentUTime(), 
                            endTriggerTime) <= 0);

                if (IsDsmStateOpOneMb(DSM_DATA_STATE_DATA(dataObj).state))
                {
                    break;
                }

                /* Ignore errors. */
                SCIDisconnectInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                    NO_FLAGS, 
                    &error);

                /*
                 * Change state to SYNC SLAVE.
                 */

                ret = TransitionJoiningToSyncSlave(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to SYNC SLAVE\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_SLAVE;
            }
            else
            {
                ITS_TRACE_ERROR((
                    "MonitorLoop [FtGroupId: %u]: SCIWaitForInterrupt failed: "
                    "0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));

                ITS_TRACE_CRITICAL((
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
                return;
            }
        }
        break;

    case DSM_STATE_SYNC_SLAVE:
        {
            SCIWaitForInterrupt(
                DSM_DATA_LOCAL_MEMBER(dataObj).syncIrt,
                DSM_DATA_CONFIG(dataObj).syncTimeout,
                NO_FLAGS,
                &error);
            if (error == SCI_ERR_TIMEOUT)
            {
                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionSyncSlaveToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;
            }
            else if (error == SCI_ERR_OK)
            {
                /*
                 * Change state to OP TWO MB.
                 */

                ret = TransitionSyncSlaveToOpTwoMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP TWO MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_TWO_MB;
            }
            else
            {
                ITS_TRACE_ERROR((
                    "MonitorLoop [FtGroupId: %u]: SCIWaitForInterrupt failed: "
                    "0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));

                ITS_TRACE_CRITICAL((
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
                return;
            }
        }
        break;


    case DSM_STATE_SYNC_MASTER:
        {
            /* 
             * To be sure that slave is waiting for sync interrupt (and not 
             * still triggering the master).
             */

            TIMERS_USleep(
                DSM_DATA_CONFIG(dataObj).irtTriggerTimeout * 
                    USEC_PER_MILLISEC);

            ret = Dma(
                    dataObj,
                    DSM_INST_DSM_SIZE(instObj),
                    0);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "MonitorLoop [FtGroupId: %u]: Dma failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionSyncMasterToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                break;
            }

            /* 
             * Slave should be waiting on sync interrupt. 
             */

            SCIConnectInterrupt(
                DSM_DATA_CONNECTION(dataObj).sd,
                &DSM_DATA_REMOTE_MEMBER(dataObj).syncIrt,
                DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                DSM_DATA_REMOTE_MEMBER(dataObj).syncIrtNo,
                DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                NO_FLAGS,
                &error);
            if (error != SCI_ERR_OK)
            {
                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionSyncMasterToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                break;
            }

            SCITriggerInterrupt(
                DSM_DATA_REMOTE_MEMBER(dataObj).syncIrt,
                NO_FLAGS,
                &error);
            if (error != SCI_ERR_OK)
            {

                /* Ignore errors. */
                SCIDisconnectInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).syncIrt,
                    NO_FLAGS,
                    &error);

                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionSyncMasterToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                break;
            }

            /* Ignore errors. */
            SCIDisconnectInterrupt(
                DSM_DATA_REMOTE_MEMBER(dataObj).syncIrt,
                NO_FLAGS,
                &error);

            /*
             * Change state to OP TWO MB.
             */

            ret = TransitionSyncMasterToOpTwoMb(dataObj);
            if (ret != ITS_SUCCESS)
            {
                /* TODO: review. */
            }

            ITS_TRACE_DEBUG((
                "MonitorLoop [FtGroupId: %u]: change state to OP TWO MB\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_TWO_MB;
        }
        break;


    case DSM_STATE_OP_ONE_MB:
        {
            SCIConnectInterrupt(
                DSM_DATA_CONNECTION(dataObj).sd,
                &DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrtNo,
                DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                NO_FLAGS,
                &error);
            if (error == SCI_ERR_OK)
            {
                /* Ignore errors. */
                SCITriggerInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                    NO_FLAGS, 
                    &error);
                
                /* Ignore errors. */
                SCIDisconnectInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                    NO_FLAGS, 
                    &error);
            }

            SCIWaitForInterrupt(
                DSM_DATA_LOCAL_MEMBER(dataObj).masterIrt,
                DSM_DATA_CONFIG(dataObj).irtWaitTimeout,
                NO_FLAGS, 
                &error);
            if (error == SCI_ERR_TIMEOUT)
            {
                /* Nothing to do. Just continue the loop. */
            }
            else if (error == SCI_ERR_OK)
            {
                SCIConnectInterrupt(
                    DSM_DATA_CONNECTION(dataObj).sd,
                    &DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                    DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                    DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                    DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrtNo,
                    DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error == SCI_ERR_OK)
                {
                    /* Trigger remote slave interrupt. */
                    beginTriggerTime = TIMERS_GetCurrentUTime();

                    endTriggerTime = 
                        TIMERS_AddUTime(
                            beginTriggerTime, 
                            TIMERS_UTimeFromMillisecs(
                                DSM_DATA_CONFIG(dataObj).irtTriggerTimeout));

                    do
                    {
                        SCITriggerInterrupt(
                            DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                            NO_FLAGS,
                            &error);
                        if (error != SCI_ERR_OK)
                        {
                            ITS_TRACE_ERROR((
                                "MonitorLoop [FtGroupId: %u]: "
                                "SCITriggerInterrupt failed: 0x%X\n",
                                DSM_DATA_FT_GROUP_ID(dataObj),
                                error));

                            break; /* Out of loop. */
                        }   
                        
                        TIMERS_USleep(
                            DSM_DATA_CONFIG(dataObj).irtTriggerInterval * 
                                USEC_PER_MILLISEC);
                    }
                    while (TIMERS_CompareUTime(
                                TIMERS_GetCurrentUTime(), 
                                endTriggerTime) <= 0);


                    /* Ignore errors. */
                    SCIDisconnectInterrupt(
                        DSM_DATA_REMOTE_MEMBER(dataObj).slaveIrt,
                        NO_FLAGS, 
                        &error);

                    /*
                     * Change state to SYNC MASTER.
                     */

                    ret = TransitionOpOneMbToSyncMaster(dataObj);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: review. */
                    }

                    ITS_TRACE_DEBUG((
                        "MonitorLoop [FtGroupId: %u]: change state to SYNC MASTER\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_MASTER;
                }
                else
                {
                    /* Nothing to do. Stay in state OP_ONE_MB. */
                }
            }
            else
            {
                ITS_TRACE_ERROR((
                    "MonitorLoop [FtGroupId: %u]: SCIWaitForInterrupt failed: "
                    "0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));

                ITS_TRACE_CRITICAL((
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
                return;
            }

            if (DSM_DATA_STATE_DATA(dataObj).state == DSM_STATE_SYNC_MASTER)
            {
                break;
            }

            SCIConnectInterrupt(
                DSM_DATA_CONNECTION(dataObj).sd,
                &DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                DSM_DATA_REMOTE_MEMBER(dataObj).masterIrtNo,
                DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                NO_FLAGS,
                &error);
            if (error == SCI_ERR_OK)
            {
                /* Ignore errors. */
                SCITriggerInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                    NO_FLAGS, 
                    &error);
                
                /* Ignore errors. */
                SCIDisconnectInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                    NO_FLAGS, 
                    &error);
            }

            SCIWaitForInterrupt(
                DSM_DATA_LOCAL_MEMBER(dataObj).slaveIrt,
                DSM_DATA_CONFIG(dataObj).irtWaitTimeout,
                NO_FLAGS, 
                &error);
            if (error == SCI_ERR_TIMEOUT)
            {
                /* Nothing to do. Just continue the loop. */
            }
            else if (error == SCI_ERR_OK)
            {
                SCIConnectInterrupt(
                    DSM_DATA_CONNECTION(dataObj).sd,
                    &DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                    DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                    DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                    DSM_DATA_REMOTE_MEMBER(dataObj).masterIrtNo,
                    DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                    NO_FLAGS,
                    &error);
                if (error == SCI_ERR_OK)
                {
                    /* Trigger remote master interrupt. */
                    beginTriggerTime = TIMERS_GetCurrentUTime();

                    endTriggerTime = 
                        TIMERS_AddUTime(
                            beginTriggerTime, 
                            TIMERS_UTimeFromMillisecs(
                                DSM_DATA_CONFIG(dataObj).irtTriggerTimeout));

                    do
                    {
                        SCITriggerInterrupt(
                            DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                            NO_FLAGS, 
                            &error);
                        if (error != SCI_ERR_OK)
                        {
                            ITS_TRACE_ERROR((
                                "MonitorLoop [FtGroupId: %u]: "
                                "SCITriggerInterrupt failed: 0x%X\n",
                                DSM_DATA_FT_GROUP_ID(dataObj),
                                error));

                            break; /* Out of loop. */
                        }   

                        TIMERS_USleep(
                            DSM_DATA_CONFIG(dataObj).irtTriggerInterval * 
                                USEC_PER_MILLISEC);
                    }
                    while (TIMERS_CompareUTime(
                                TIMERS_GetCurrentUTime(), 
                                endTriggerTime) <= 0);

                    /* Ignore errors. */
                    SCIDisconnectInterrupt(
                        DSM_DATA_REMOTE_MEMBER(dataObj).masterIrt,
                        NO_FLAGS, 
                        &error);

                    /*
                     * Change state to SYNC SLAVE.
                     */

                    ret = TransitionOpOneMbToSyncSlave(dataObj);
                    if (ret != ITS_SUCCESS)
                    {
                        /* TODO: review. */
                    }

                    ITS_TRACE_DEBUG((
                        "MonitorLoop [FtGroupId: %u]: change state to SYNC SLAVE\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_SLAVE;
                }
                else
                {
                    /* Nothing to do. Stay in OP_ONE_MB. */
                }
            }
            else
            {
                ITS_TRACE_ERROR((
                    "MonitorLoop [FtGroupId: %u]: SCIWaitForInterrupt failed: "
                    "0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    error));

                ITS_TRACE_CRITICAL((
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorLoop [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
                return;
            }

            if (DSM_DATA_STATE_DATA(dataObj).state == DSM_STATE_SYNC_SLAVE)
            {
                break;
            }

            MonitorManageTrans(dataObj);

        }
        break;

    case DSM_STATE_OP_TWO_MB:
        {
            unsigned int missCount = 0;

            SCIConnectInterrupt(
                DSM_DATA_CONNECTION(dataObj).sd,
                &DSM_DATA_REMOTE_MEMBER(dataObj).opIrt,
                DSM_DATA_REMOTE_MEMBER(dataObj).nodeId,
                DSM_DATA_LOCAL_MEMBER(dataObj).adapterNo,
                DSM_DATA_REMOTE_MEMBER(dataObj).opIrtNo,
                DSM_DATA_CONFIG(dataObj).irtConnectTimeout,
                NO_FLAGS,
                &error);
            if (error != SCI_ERR_OK)
            {
                /*
                 * Change state to OP ONE MB.
                 */

                ret = TransitionOpTwoMbToOpOneMb(dataObj);
                if (ret != ITS_SUCCESS)
                {
                    /* TODO: review. */
                }

                ITS_TRACE_DEBUG((
                    "MonitorLoop [FtGroupId: %u]: change state to OP ONE MB\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_OP_ONE_MB;

                break;
            }

            while (!DSM_DATA_MONITOR(dataObj).exitThread)
            {
                if (DSM_DATA_CONFIG(dataObj).localDebug)
                {
                    ITS_TRACE_DEBUG((
                        "MonitorLoop [FtGroupId: %u]: current state: %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
                }

                SCITriggerInterrupt(
                    DSM_DATA_REMOTE_MEMBER(dataObj).opIrt,
                    NO_FLAGS, 
                    &error);
                if (error != SCI_ERR_OK)
                {
                    ITS_TRACE_ERROR((
                        "MonitorLoop [FtGroupId: %u]: SCITriggerInterrupt "
                        "failed: 0x%X\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        error));

                    /* Continue. MissCount will stop the loop if necessary. */
                }

                SCIWaitForInterrupt(
                    DSM_DATA_LOCAL_MEMBER(dataObj).opIrt,
                    DSM_DATA_CONFIG(dataObj).pingInterval * 2,
                    NO_FLAGS, 
                    &error);
                if (error == SCI_ERR_TIMEOUT)
                {
                    missCount++;
                    if (missCount >= 3)
                    {
                        /* Ignore errors. */
                        SCIDisconnectInterrupt(
                            DSM_DATA_REMOTE_MEMBER(dataObj).opIrt,
                            NO_FLAGS,
                            &error);

                        /*
                         * Change state to OP ONE MB.
                         */

                        ret = TransitionOpTwoMbToOpOneMb(dataObj);
                        if (ret != ITS_SUCCESS)
                        {
                            /* TODO: review. */
                        }

                        ITS_TRACE_DEBUG((
                            "MonitorLoop [FtGroupId: %u]: change state to OP "
                            "ONE MB\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));

                        DSM_DATA_STATE_DATA(dataObj).state = 
                            DSM_STATE_OP_ONE_MB;

                        break;
                    }
                }
                else if (error == SCI_ERR_OK)
                {
                    /* Nothing to do. Continue. */
                }
                else
                {
                    ITS_TRACE_ERROR((
                        "MonitorLoop [FtGroupId: %u]: SCIWaitForInterrupt "
                        "failed: 0x%X\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        error));

                    ITS_TRACE_CRITICAL((
                        "MonitorLoop [FtGroupId: %u]: unable to recover from "
                        "previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "MonitorLoop [FtGroupId: %u]: unable to recover from "
                        "error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    /* Not reached. */
                    return;
                }

                MonitorManageTrans(dataObj);

                /*
                 * Change to state OP ONE MB if error with remote.
                 */
                if (DSM_DATA_STATE_DATA(dataObj).requestOpOneMb)
                {
                    DSM_DATA_STATE_DATA(dataObj).requestOpOneMb = ITS_FALSE;

                    /* Ignore errors. */
                    SCIDisconnectInterrupt(
                        DSM_DATA_REMOTE_MEMBER(dataObj).opIrt,
                        NO_FLAGS,
                        &error);

                    ITS_TRACE_DEBUG((
                        "MonitorLoop [FtGroupId: %u]: change state to OP ONE "
                        "MB\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    DSM_DATA_STATE_DATA(dataObj).state = 
                        DSM_STATE_OP_ONE_MB;

                    break;
                }

                /* 
                 * Need to measure the time they take and remove that from the
                 * pingInterval sleep. 
                 */

                TIMERS_USleep(
                    DSM_DATA_CONFIG(dataObj).pingInterval * USEC_PER_MILLISEC);
            }

            /* Ignore errors. */
            SCIDisconnectInterrupt(
                DSM_DATA_REMOTE_MEMBER(dataObj).opIrt,
                NO_FLAGS, 
                &error);
        }
        break;

    default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
        }
    }
}

/******************************************************************************
 *
 * Monitor thread function.
 *
 */
static THREAD_RET_TYPE 
MonitorThread(
    void* arg)
{
    DSM_DataObject* dataObj;
    int ret;

    dataObj = (DSM_DataObject*)arg;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "MonitorThread [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     *  Initialization.
     */

    ITS_TRACE_DEBUG((
        "MonitorThread [FtGroupId: %u]: initialization\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Drain start semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_MONITOR(dataObj).startSema) == 
        ITS_SUCCESS)
    {
    }

    /* Drain stop semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema) == 
        ITS_SUCCESS)
    {
    }

    DSM_DATA_MONITOR(dataObj).started = ITS_TRUE;

    /*
     * Monitor forever loop.
     */

    ITS_TRACE_DEBUG((
        "MonitorThread [FtGroupId: %u]: monitor forever loop\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    while (!DSM_DATA_MONITOR(dataObj).exitThread)
    {
        while (!DSM_DATA_MONITOR(dataObj).exitThread)
        {
            ret = SEMA_WaitSemaphoreWithTimeOut(
                    &DSM_DATA_MONITOR(dataObj).startSema,
                    1000);
            if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
            {
                ITS_TRACE_ERROR((
                    "MonitorThread [FtGroupId: %u]: "
                    "SEMA_WaitSemaphoreWithTimeOut failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "MonitorThread [FtGroupId: %u]: unable to recover from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "MonitorThread [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
                THREAD_NORMAL_EXIT;
            }
            else if (ret == ITS_ETIMEOUT)
            {
                continue;
            }
            else
            {
                ITS_TRACE_DEBUG((
                    "MonitorThread [FtGroupId: %u]: start semaphore posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                break;
            }
        }

        while (!DSM_DATA_MONITOR(dataObj).exitThread)
        {
            MonitorLoop(dataObj);

            ret = SEMA_TryWaitSemaphore(&DSM_DATA_MONITOR(dataObj).stopSema);
            if (ret == ITS_SUCCESS)
            {
                ITS_TRACE_DEBUG((
                    "MonitorThread [FtGroupId: %u]: stop semaphore posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
                break;                    
            }
            else
            {
                continue;
            }
        }
    }

    ITS_TRACE_DEBUG((
        "MonitorThread [FtGroupId: %u]: termination\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* If monitor forever loop is terminated. */
    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

    ITS_TRACE_DEBUG((
        "MonitorThread [FtGroupId: %u]: normal exit\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    THREAD_NORMAL_EXIT;
}


/******************************************************************************
 ******************************************************************************
 **
 ** Allocator related (implementation).
 **
 */

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
static void *
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

            REFLECT_SET(dataObj,
                        &DSM_DATA_MEM_DATA(dataObj)->curbrk,
                        DSM_DATA_MEM_DATA(dataObj)->curbrk + size);
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
 *  All uses of av_ are via get_malloc_state().
 *  At most one "call" to get_malloc_state is made per invocation of
 *  the public versions of malloc and free, but other routines
 *  that in turn invoke malloc and/or free may call more then once. 
 *  Also, it is called in check* routines if DEBUG is set.
 */
#define get_malloc_state(dataObj) (&DSM_DATA_MEM_DATA(dataObj)->state)

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
static void
MallocInitState(DSM_DataObject* dataObj, mstate av)
{
    int     i;
    mbinptr bin;
    
    /* Establish circular links for normal bins */
    for (i = 1; i < NBINS; ++i)
    {
        bin = bin_at(av,i);

        REFLECT_SET(dataObj, &bin->fd, bin);
        REFLECT_SET(dataObj, &bin->bk, bin);
        bin->fd = bin->bk = bin;    /* MLM: SET */
    }
    
    set_max_fast(dataObj, av, DEFAULT_MXFAST);
    
    REFLECT_SET(dataObj, &av->top, initial_top(av));
    av->top            = initial_top(av);   /* MLM: SET */

    REFLECT_SET(dataObj, &av->pagesize, malloc_getpagesize);
    av->pagesize       = malloc_getpagesize;    /* MLM: SET */
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
 ****************************************************************************
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
 ****************************************************************************/
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
        REFLECT_SET(dataObj, &av->sbrked_mem, av->sbrked_mem + size);
        av->sbrked_mem += size;    /* MLM: SET */
        
        /*
         * If MORECORE extends previous space, we can likewise extend top size.
         */
        if (brk == old_end && snd_brk == (char*)(MORECORE_FAILURE))
        {
            set_head(dataObj, old_top, (size + old_size) | PREV_INUSE);
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
                REFLECT_SET(dataObj, &av->top, (mchunkptr)aligned_brk);
                av->top = (mchunkptr)aligned_brk;    /* MLM: SET */

                set_head(dataObj, av->top, (snd_brk - aligned_brk + correction) |
                                   PREV_INUSE);

                REFLECT_SET(dataObj, &av->sbrked_mem, av->sbrked_mem + correction);
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
                    set_head(dataObj, old_top, old_size | PREV_INUSE);
                    
                    /*
                     * Note that the following assignments completely overwrite
                     * old_top when old_size was previously MINSIZE.  This is
                     * intentional. We need the fencepost, even if old_top otherwise gets
                     * lost.
                     */
                    REFLECT_SET(dataObj, &chunk_at_offset(old_top, old_size)->size,
                                SIZE_SZ|PREV_INUSE);
                    chunk_at_offset(old_top, old_size)->size =
                        SIZE_SZ|PREV_INUSE;    /* MLM: SET */
                    
                    REFLECT_SET(dataObj, &chunk_at_offset(old_top,
                                old_size + SIZE_SZ)->size,
                                SIZE_SZ|PREV_INUSE);
                    chunk_at_offset(old_top, old_size + SIZE_SZ)->size =
                        SIZE_SZ|PREV_INUSE;    /* MLM: SET */
                    
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
            REFLECT_SET(dataObj, &av->max_sbrked_mem, sum);
            av->max_sbrked_mem = sum;    /* MLM: SET */
        }
        
        if (sum > (unsigned long)(av->max_total_mem))
        {
            REFLECT_SET(dataObj, &av->max_total_mem, sum);
            av->max_total_mem = sum;    /* MLM: SET */
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

            REFLECT_SET(dataObj, &av->top, remainder);
            av->top = remainder;    /* MLM: SET */
            
            set_head(dataObj, p, nb | PREV_INUSE);
            set_head(dataObj, remainder, remainder_size | PREV_INUSE);
            
            check_malloced_chunk(dataObj, p, nb);
            
            return chunk2mem(p);
        }
    }
  
    /* catch all failure paths */
    return 0;
}

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
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
            REFLECT_SET(dataObj, fb, victim->fd);
            *fb = victim->fd;    /* MLM: SET */

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
                
                set_inuse_bit_at_offset(dataObj, victim, nb);

                REFLECT_SET(dataObj, &bin->bk, bck);
                bin->bk = bck;    /* MLM: SET */
                REFLECT_SET(dataObj, &bck->fd, bin);
                bck->fd = bin;    /* MLM: SET */
                
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

                REFLECT_SET(dataObj, &unsorted_chunks(av)->fd, remainder);
                REFLECT_SET(dataObj, &unsorted_chunks(av)->bk, remainder);
                unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                REFLECT_SET(dataObj, &av->last_remainder, remainder);
                av->last_remainder = remainder;     /* MLM: SET */

                REFLECT_SET(dataObj, &remainder->bk, unsorted_chunks(av));
                REFLECT_SET(dataObj, &remainder->fd, unsorted_chunks(av));
                remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */
                
                set_head(dataObj, victim, nb | PREV_INUSE);
                set_head(dataObj, remainder, remainder_size | PREV_INUSE);
                set_foot(dataObj, remainder, remainder_size);
                
                check_malloced_chunk(dataObj, victim, nb);
                
                return chunk2mem(victim);
            }
            
            /* remove from unsorted list */
            REFLECT_SET(dataObj, &unsorted_chunks(av)->bk, bck);
            unsorted_chunks(av)->bk = bck;    /* MLM: SET */
            REFLECT_SET(dataObj, &bck->fd, unsorted_chunks(av));
            bck->fd = unsorted_chunks(av);    /* MLM: SET */
            
            /* Take now instead of binning if exact fit */
            if (size == nb)
            {
                set_inuse_bit_at_offset(dataObj, victim, size);
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
            
            mark_bin(dataObj, av, victim_index);
            
            REFLECT_SET(dataObj, &victim->bk, bck);
            victim->bk = bck;    /* MLM: SET */
            REFLECT_SET(dataObj, &victim->fd, fwd);
            victim->fd = fwd;    /* MLM: SET */
            REFLECT_SET(dataObj, &fwd->bk, victim);
            fwd->bk = victim;    /* MLM: SET */
            REFLECT_SET(dataObj, &bck->fd, victim);
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
                unlink(dataObj, victim, bck, fwd);
                
                /* Exhaust */
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(dataObj, victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);
                    REFLECT_SET(dataObj, &unsorted_chunks(av)->bk, remainder);
                    REFLECT_SET(dataObj, &unsorted_chunks(av)->fd, remainder);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                    REFLECT_SET(dataObj, &remainder->bk, unsorted_chunks(av));
                    REFLECT_SET(dataObj, &remainder->fd, unsorted_chunks(av));
                    remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */
                    
                    set_head(dataObj, victim, nb | PREV_INUSE);
                    set_head(dataObj, remainder, remainder_size | PREV_INUSE);
                    set_foot(dataObj, remainder, remainder_size);
                    
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
                REFLECT_SET(dataObj, &av->binmap[block], map);
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
                REFLECT_SET(dataObj, &bin->bk, bck);
                bin->bk = bck;    /* MLM: SET */
                REFLECT_SET(dataObj, &bck->fd, bin);
                bck->fd = bin;    /* MLM: SET */
                
                /* Exhaust */
                if (remainder_size < MINSIZE)
                {
                    set_inuse_bit_at_offset(dataObj, victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
                    return chunk2mem(victim);
                }
                /* Split */
                else
                {
                    remainder = chunk_at_offset(victim, nb);

                    REFLECT_SET(dataObj, &unsorted_chunks(av)->bk, remainder);
                    REFLECT_SET(dataObj, &unsorted_chunks(av)->fd, remainder);
                    unsorted_chunks(av)->bk = unsorted_chunks(av)->fd = remainder;    /* MLM: SET */

                    REFLECT_SET(dataObj, &remainder->bk, unsorted_chunks(av));
                    REFLECT_SET(dataObj, &remainder->fd, unsorted_chunks(av));
                    remainder->bk = remainder->fd = unsorted_chunks(av);    /* MLM: SET */

                    /* advertise as last remainder */
                    if (in_smallbin_range(nb)) 
                    {
                        REFLECT_SET(dataObj, &av->last_remainder, remainder);
                        av->last_remainder = remainder;     /* MLM: SET */
                    }
                    
                    set_head(dataObj, victim, nb | PREV_INUSE);
                    set_head(dataObj, remainder, remainder_size | PREV_INUSE);
                    set_foot(dataObj, remainder, remainder_size);
                    
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

            REFLECT_SET(dataObj, &av->top, remainder);
            av->top = remainder;    /* MLM: SET */
            
            set_head(dataObj, victim, nb | PREV_INUSE);
            set_head(dataObj, remainder, remainder_size | PREV_INUSE);
            
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
 ****************************************************************************
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
 ****************************************************************************/
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
            set_fastchunks(dataObj, av);
            
            fb = &(av->fastbins[fastbin_index(size)]);

            REFLECT_SET(dataObj, &p->fd, *fb);
            p->fd = *fb;    /* MLM: SET */
            REFLECT_SET(dataObj, fb, p);
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
                
                unlink(dataObj, p, bck, fwd);
            }
            
            if (nextchunk != av->top)
            {
                /* get and clear inuse bit */
                nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                set_head(dataObj, nextchunk, nextsize);
                
                /* consolidate forward */
                if (!nextinuse)
                {
                    unlink(dataObj, nextchunk, bck, fwd);
                    
                    size += nextsize;
                }
                
                /*
                 * Place the chunk in unsorted chunk list. Chunks are
                 * not placed into regular bins until after they have
                 * been given one chance to be used in malloc.
                 */
                bck = unsorted_chunks(av);
                fwd = bck->fd;

                REFLECT_SET(dataObj, &p->bk, bck);
                p->bk = bck;    /* MLM: SET */
                REFLECT_SET(dataObj, &p->fd, fwd);
                p->fd = fwd;    /* MLM: SET */
                REFLECT_SET(dataObj, &bck->fd, p);
                bck->fd = p;    /* MLM: SET */
                REFLECT_SET(dataObj, &fwd->bk, p);
                fwd->bk = p;    /* MLM: SET */
                
                set_head(dataObj, p, size | PREV_INUSE);
                set_foot(dataObj, p, size);
                
                check_free_chunk(dataObj, p);
            }
            /*
             *  If the chunk borders the current high end of memory,
             *  consolidate into top
             */
            else
            {
                size += nextsize;
                set_head(dataObj, p, size | PREV_INUSE);

                REFLECT_SET(dataObj, &av->top, p);
                av->top = p;    /* MLM: SET */

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
 ****************************************************************************
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
 ****************************************************************************/
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
        clear_fastchunks(dataObj, av);
        
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
                REFLECT_SET(dataObj, fb, 0);
                *fb = 0;    /* MLM: SET */
                
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
                        unlink(dataObj, p, bck, fwd);
                    }
                    
                    if (nextchunk != av->top)
                    {
                        nextinuse = inuse_bit_at_offset(nextchunk, nextsize);
                        set_head(dataObj, nextchunk, nextsize);
                        
                        if (!nextinuse)
                        {
                            size += nextsize;
                            unlink(dataObj, nextchunk, bck, fwd);
                        }
                        
                        first_unsorted = unsorted_bin->fd;

                        REFLECT_SET(dataObj, &unsorted_bin->fd, p);
                        unsorted_bin->fd = p;    /* MLM: SET */
                        REFLECT_SET(dataObj, &first_unsorted->bk, p);
                        first_unsorted->bk = p;    /* MLM: SET */
                        
                        set_head(dataObj, p, size | PREV_INUSE);

                        REFLECT_SET(dataObj, &p->bk, unsorted_bin);
                        p->bk = unsorted_bin;    /* MLM: SET */
                        REFLECT_SET(dataObj, &p->fd, first_unsorted);
                        p->fd = first_unsorted;    /* MLM: SET */

                        set_foot(dataObj, p, size);
                    }
                    else
                    {
                        size += nextsize;
                        set_head(dataObj, p, size | PREV_INUSE);

                        REFLECT_SET(dataObj, &av->top, p);
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
        MallocInitState(dataObj, av);
        
        check_malloc_state(dataObj);
    }
}

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
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
            set_head_size(dataObj, oldp, nb);

            REFLECT_SET(dataObj, &av->top, chunk_at_offset(oldp, nb));
            av->top = chunk_at_offset(oldp, nb);    /* MLM: SET */
            
            set_head(dataObj, av->top, (newsize - nb) | PREV_INUSE);
            
            return chunk2mem(oldp);
        }
        
        /* Try to expand forward into next chunk;  split off remainder below */
        else if (next != av->top && 
                 !inuse(next) &&
                 (unsigned long)(newsize = oldsize + chunksize(next)) >=
                 (unsigned long)(nb))
        {
            newp = oldp;
            unlink(dataObj, next, bck, fwd);
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
                    MALLOC_COPY(dataObj, d, s, copysize);
                }
                else
                {
                    REFLECT_SET(dataObj, d+0, *(s+0));
                    *(d+0) = *(s+0);    /* MLM: SET */
                    REFLECT_SET(dataObj, d+1, *(s+1));
                    *(d+1) = *(s+1);    /* MLM: SET */
                    REFLECT_SET(dataObj, d+2, *(s+2));
                    *(d+2) = *(s+2);    /* MLM: SET */
                    if (ncopies > 4)
                    {
                        REFLECT_SET(dataObj, d+3, *(s+3));
                        *(d+3) = *(s+3);    /* MLM: SET */
                        REFLECT_SET(dataObj, d+4, *(s+4));
                        *(d+4) = *(s+4);    /* MLM: SET */
                        if (ncopies > 6)
                        {
                            REFLECT_SET(dataObj, d+5, *(s+5));
                            *(d+5) = *(s+5);    /* MLM: SET */
                            REFLECT_SET(dataObj, d+6, *(s+6));
                            *(d+6) = *(s+6);    /* MLM: SET */
                            if (ncopies > 8)
                            {
                                REFLECT_SET(dataObj, d+7, *(s+7));
                                *(d+7) = *(s+7);    /* MLM: SET */
                                REFLECT_SET(dataObj, d+8, *(s+8));
                                *(d+8) = *(s+8);    /* MLM: SET */
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
            set_head_size(dataObj, newp, newsize);
            set_inuse_bit_at_offset(dataObj, newp, newsize);
        }
        else /* split remainder */
        {
            remainder = chunk_at_offset(newp, nb);
            
            set_head_size(dataObj, newp, nb);
            set_head(dataObj, remainder, remainder_size | PREV_INUSE);
            
            /* Mark remainder as inuse so free() won't complain */
            set_inuse_bit_at_offset(dataObj, remainder, remainder_size);
            dlfree(dataObj, chunk2mem(remainder)); 
        }
        
        check_inuse_chunk(dataObj, newp);
        
        return chunk2mem(newp);
    }
  
    check_malloc_state(dataObj);
  
    return 0;
}

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
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
        set_head(dataObj, newp, newsize | PREV_INUSE);
        set_inuse_bit_at_offset(dataObj, newp, newsize);
        set_head_size(dataObj, p, leadsize);
        
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
        
        set_head(dataObj, remainder, remainder_size | PREV_INUSE);
        set_head_size(dataObj, p, nb);
        
        dlfree(dataObj, chunk2mem(remainder));
    }
    
    check_inuse_chunk(dataObj, p);
    
    return chunk2mem(p);
}

/*.implementation:static
 ****************************************************************************
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
 ****************************************************************************/
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
            MALLOC_ZERO(dataObj, d, clearsize);
        }
        else
        {
            REFLECT_SET(dataObj, d+0, 0);
            *(d+0) = 0;    /* MLM: SET */
            REFLECT_SET(dataObj, d+1, 0);
            *(d+1) = 0;    /* MLM: SET */
            REFLECT_SET(dataObj, d+2, 0);
            *(d+2) = 0;    /* MLM: SET */
            if (nclears > 4)
            {
                REFLECT_SET(dataObj, d+3, 0);
                *(d+3) = 0;    /* MLM: SET */
                REFLECT_SET(dataObj, d+4, 0);
                *(d+4) = 0;    /* MLM: SET */
                if (nclears > 6)
                {
                    REFLECT_SET(dataObj, d+5, 0);
                    *(d+5) = 0;    /* MLM: SET */
                    REFLECT_SET(dataObj, d+6, 0);
                    *(d+6) = 0;    /* MLM: SET */
                    if (nclears > 8)
                    {
                        REFLECT_SET(dataObj, d+7, 0);
                        *(d+7) = 0;    /* MLM: SET */
                        REFLECT_SET(dataObj, d+8, 0);
                        *(d+8) = 0;    /* MLM: SET */
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
 ** DSM (SCI) Impl (implementation) class.
 **
 */

/*
 * Alloc.
 */
static void*
Alloc(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error,
    ITS_BOOLEAN withLock)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_RowHeader*  allocPtr;
    DSM_RowHeader*  tmp;
    DSM_RowHeader** list;
    ITS_TIME        now;
    ITS_UINT        round;
    ITS_INT         hash            = 0;
    ITS_UINT        rowSize         = size;
    ITS_BOOLEAN     keepOn          = ITS_TRUE;
    ITS_BOOLEAN     tablesLocked    = ITS_FALSE;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    threadId = THREAD_GetCurrentThreadID();

    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Other Tcb initializations. */
    tcb->threadId   = threadId;
    tcb->tableId    = tableId;

    /* Lock Tcb active list. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Insert Tcb. */
    if (DSM_DATA_TCB_MANAGER(dataObj).activeListHead != NULL)
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail != NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail->next = tcb;
    }
    else
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail == NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListHead = tcb;
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail = tcb;
    }

    DSM_DATA_TCB_MANAGER(dataObj).activeEntries++;

    WaitingTransInc(dataObj);

    /* 
     * Acquire Tcb condition variable associated mutex BEFORE unlocking Tcb
     * active list.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }    

    /* Unlock Tcb active list. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    /* 
     * Wait on Tcb condition variable. 
     */
    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: ready to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: finished to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    WaitingTransDec(dataObj);

    /* Add row header to rowSize and make it a multiple of word size. */
    /* Add extra word size (for malloc chunk size rounding). */
    rowSize += sizeof(DSM_RowHeader) + sizeof(ITS_UINT) - 1;
    rowSize &= ~(sizeof(ITS_UINT) - 1);
    rowSize += sizeof(ITS_UINT);

    /* Allocate entry. */
    if (keepOn)
    {
        allocPtr = dlcalloc(dataObj, 1, rowSize);
        if (allocPtr == NULL)
        {
            *error = ITS_ENOMEM;
            keepOn = ITS_FALSE;
        }
    }

    /* Allocate key. */
    if (keepOn)
    {
        round = klen + sizeof(ITS_UINT) - 1;
        round &= ~(sizeof(ITS_UINT) - 1);

        allocPtr->key = dlcalloc(dataObj, 1, round);
        if (allocPtr->key == NULL)
        {
            dlfree(dataObj, allocPtr);
            *error = ITS_ENOMEM;
            keepOn = ITS_FALSE;
            allocPtr = NULL;
        }
    }

    /* Compute hash value. */
    if (keepOn)
    {
        hash = LocalHash(key, klen);
    }

    /* Lock hash table. */
    if (keepOn)
    {
        ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            dlfree(dataObj, allocPtr->key);
            dlfree(dataObj, allocPtr);
            *error = ret;
            keepOn = ITS_FALSE;
            allocPtr = NULL;
        }
        else
        {
            tablesLocked = ITS_TRUE;
        }
    }

    /* Add to hash table. */
    if (keepOn)
    {
        ret = HASH_FindEntry(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId,
                    hash, 
                    (ITS_POINTER*)&tmp);
        if (ret == ITS_SUCCESS)
        {
            for (list = &tmp->next; 
                 (*list) != NULL; 
                 list = &((*list)->next))
            {
                /* Check for duplicate keys. */
                if ((*list)->klen == klen && 
                    memcmp((*list)->key, key, klen) == 0)
                {
                    /* TODO: add debug trace. */
                }
            }

            *list = allocPtr;
        }
        else
        {
            ret = HASH_AddEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        tableId,
                        hash,
                        (ITS_POINTER)allocPtr);

            if (ret != ITS_SUCCESS)
            {
                dlfree(dataObj, allocPtr->key);
                dlfree(dataObj, allocPtr);
                *error = ret;
                keepOn = ITS_FALSE;
                allocPtr = NULL;
            }
        }
    }

    /* Store key info. */
    if (keepOn)
    {
        memcpy(allocPtr->key, key, klen);
        allocPtr->klen = klen;
    }

    /* Lock row only if required. */
    if (keepOn && withLock)
    {
        allocPtr->locked = ITS_TRUE;
        now = TIMERS_Time();
        allocPtr->lockTime = now;
    }

    /* Adjust number of entries in table. */
    if (keepOn)
    {
        DSM_DATA_TABLES_INFO(dataObj)[tableId].entries++;
    }

    /* Adjust pointer to user data (row header is before). */
    if (keepOn)
    {
        allocPtr = allocPtr + 1;
    }

    /* Unlock hash table if locked. */
    if (tablesLocked)
    {
        ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    PendingTransDec(dataObj);

    return allocPtr;
}

/*
 * Find.
 */
static void*
Find(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    int* error,
    ITS_BOOLEAN withLock)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_RowHeader*  findPtr         = NULL;
    DSM_RowHeader*  row;
    ITS_INT         hash;
    ITS_TIME        now;
    ITS_BOOLEAN     keepOn          = ITS_TRUE;
    ITS_BOOLEAN     tablesLocked    = ITS_FALSE;
    int ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    threadId = THREAD_GetCurrentThreadID();

    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Other Tcb initializations. */
    tcb->threadId   = threadId;
    tcb->tableId    = tableId;

    /* Lock Tcb active list. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Insert Tcb. */
    if (DSM_DATA_TCB_MANAGER(dataObj).activeListHead != NULL)
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail != NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail->next = tcb;
    }
    else
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail == NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListHead = tcb;
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail = tcb;
    }

    DSM_DATA_TCB_MANAGER(dataObj).activeEntries++;

    WaitingTransInc(dataObj);

    /* 
     * Acquire Tcb condition variable associated mutex BEFORE unlocking Tcb
     * active list.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }    

    /* Unlock Tcb active list. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    /* 
     * Wait on Tcb condition variable. 
     */
    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: ready to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: finished to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        WaitingTransDec(dataObj);
        *error = ret;
        return NULL;
    }

    WaitingTransDec(dataObj);

    /* Compute hash value. */
    hash = LocalHash(key, klen);

    /* Lock hash table. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        keepOn = ITS_FALSE;
        findPtr = NULL;
    }
    else
    {
        tablesLocked = ITS_TRUE;
    }

    /* Lookup for row list in table according to hash value. */
    if (keepOn)
    {
        ret = HASH_FindEntry(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId,
                    hash,
                    (ITS_POINTER*)&row);
        if (ret != ITS_SUCCESS)
        {
            *error = ITS_ENOTFOUND;
            keepOn = ITS_FALSE;
            findPtr = NULL;
        }
    }

    /* Scan row list for correct row. */
    if (keepOn)
    {
        while (row != NULL)
        {
            if (row->klen == klen && memcmp(row->key, key, klen) == 0)
            {
                break;
            }

            row = row->next;
        }

        if (row == NULL)
        {
            *error = ITS_ENOTFOUND;
            keepOn = ITS_FALSE;
            findPtr = NULL;
        }
    }

    /* For FIND always check if row locked. */
    if (keepOn)
    {
        if (row->locked &&
            (TIMERS_Time() - row->lockTime) < 
                (ITS_INT)DSM_INST_DSM_ROW_LOCK_TIMEOUT(instObj))
        {
            *error = ITS_EINUSE;
            keepOn = ITS_FALSE;
            findPtr = NULL;
        }
    }

    /* Lock row only if required. */
    if (keepOn && withLock)
    {
        row->locked = ITS_TRUE;
        now = TIMERS_Time();
        row->lockTime = now;
    }

    /* Adjust pointer to user data (row header is before). */
    if (keepOn)
    {
        findPtr = row;
        findPtr = findPtr + 1;
    }

    /* Unlock hash table if locked. */
    if (tablesLocked)
    {
        ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    PendingTransDec(dataObj);

    return findPtr;
}

/*
 * Free.
 */
static int
Free(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_OCTET* key, 
    ITS_UINT klen, 
    void* object,
    ITS_BOOLEAN withLock)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_RowHeader*  row;
    DSM_RowHeader*  tmp;
    DSM_RowHeader*  head;
    DSM_RowHeader** list;
    ITS_INT         hash;
    ITS_BOOLEAN     keepOn          = ITS_TRUE;
    ITS_BOOLEAN     tablesLocked    = ITS_FALSE;
    int             result          = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Other Tcb initializations. */
    tcb->threadId   = threadId;
    tcb->tableId    = tableId;

    /* Lock Tcb active list. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    if (DSM_DATA_TCB_MANAGER(dataObj).activeListHead != NULL)
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail != NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail->next = tcb;
    }
    else
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail == NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListHead = tcb;
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail = tcb;
    }

    DSM_DATA_TCB_MANAGER(dataObj).activeEntries++;

    WaitingTransInc(dataObj);

    /* 
     * Acquire Tcb condition variable associated mutex BEFORE unlocking Tcb
     * active list.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        return ret;
    }    

    /* Unlock Tcb active list. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        return ret;
    }

    /* 
     * Wait on Tcb condition variable. 
     */
    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: ready to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        WaitingTransDec(dataObj);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: finished to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        WaitingTransDec(dataObj);
        return ret;
    }

    WaitingTransDec(dataObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Compute hash value. */
    hash = LocalHash(key, klen);

    /* Lock hash table. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        result = ret;
        keepOn = ITS_FALSE;
    }
    else
    {
        tablesLocked = ITS_TRUE;
    }

    /* Lookup for row list in table according to hash value. */
    if (keepOn)
    {
        ret = HASH_FindEntry(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId,
                    hash,
                    (ITS_POINTER*)&head);
        if (ret != ITS_SUCCESS)
        {
            result = ITS_ENOTFOUND;
            keepOn = ITS_FALSE;
        }
    }

    /* Scan row list for correct row. */
    if (keepOn)
    {
        tmp = head;
        while (tmp != NULL)
        {
            if (tmp->klen == klen &&
                memcmp(tmp->key, key, klen) == 0 &&
                tmp == row)
            {
                break;
            }
            
            tmp = tmp->next;
        }

        ITS_C_ASSERT(tmp != NULL);

        if (tmp == NULL)
        {
            result = ITS_EINVALIDARGS;
            keepOn = ITS_FALSE;
        }
    }

    /* Check row locked only if required. */
    if (keepOn && withLock)
    {
        ITS_C_ASSERT(row->locked);

        if (!row->locked)
        {
            result = ITS_EROWNOTLOCKED;
            keepOn = ITS_FALSE;
        }
    }

    /* Remove from list. */
    if (keepOn)
    {
        list = &head;
        while (*list)
        {
            if (*list == row)
            {
                *list = row->next;
                break;
            }

            list = &((*list)->next);
        }
    }

    /* Update hash accordingly. */
    if (keepOn)
    {
        if (head == NULL)
        {
            ret = HASH_DeleteEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        tableId,
                        hash);
            if (ret != ITS_SUCCESS)
            {
                dlfree(dataObj, row->key);
                dlfree(dataObj, row);
                result = ret;
                keepOn = ITS_FALSE;
            }
        }
        else
        {
            ret = HASH_AddEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        tableId,
                        hash, 
                        (ITS_POINTER)head);
            if (ret != ITS_SUCCESS)
            {
                dlfree(dataObj, row->key);
                dlfree(dataObj, row);
                result = ret;
                keepOn = ITS_FALSE;
            }
        }
    }

    if (keepOn)
    {
        dlfree(dataObj, row->key);
        dlfree(dataObj, row);
        result = ITS_SUCCESS;
    }

    /* Adjust number of entries in table. */
    if (keepOn)
    {
        if (DSM_DATA_TABLES_INFO(dataObj)[tableId].entries > 0)
        {
            DSM_DATA_TABLES_INFO(dataObj)[tableId].entries--;
        }
    }

    /* Unlock hash table if locked. */
    if (tablesLocked)
    {
        ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    PendingTransDec(dataObj);

    return result;
}

/*
 * Commit.
 */
static int
Commit(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_OCTET* key, 
    ITS_UINT klen, 
    void* object,
    ITS_BOOLEAN withLock)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    ITS_UINT        size;
    mchunkptr       mem;
    DSM_RowHeader*  row;
    DSM_RowHeader*  tmp;
    ITS_INT         hash;
    ITS_BOOLEAN     keepOn          = ITS_TRUE;
    ITS_BOOLEAN     tablesLocked    = ITS_FALSE;
    int             result          = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Other Tcb initializations. */
    tcb->threadId   = threadId;
    tcb->tableId    = tableId;

    /* Lock Tcb active list. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    if (DSM_DATA_TCB_MANAGER(dataObj).activeListHead != NULL)
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail != NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail->next = tcb;
    }
    else
    {
        ITS_C_ASSERT(DSM_DATA_TCB_MANAGER(dataObj).activeListTail == NULL);
        DSM_DATA_TCB_MANAGER(dataObj).activeListHead = tcb;
        DSM_DATA_TCB_MANAGER(dataObj).activeListTail = tcb;
    }

    DSM_DATA_TCB_MANAGER(dataObj).activeEntries++;

    WaitingTransInc(dataObj);

    /* 
     * Acquire Tcb condition variable associated mutex BEFORE unlocking Tcb
     * active list.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        return ret;
    }    

    /* Unlock Tcb active list. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_TCB_MANAGER(dataObj).activeListLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        FreeTcb(dataObj, tcb);
        WaitingTransDec(dataObj);
        return ret;
    }

    /* 
     * Wait on Tcb condition variable. 
     */
    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: ready to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        WaitingTransDec(dataObj);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: finished to wait on condition variable. Tid: "
        "%u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        WaitingTransDec(dataObj);
        return ret;
    }

    WaitingTransDec(dataObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* 
     * Retrieve size of object from row (exact size or greather than exact size
     * due to memory alignment).
     */
    mem = mem2chunk(row);

    size = chunksize(mem) - 
                sizeof(DSM_RowHeader) - 
                    (size_t)((char*)row - (char*)mem);

    /* Must be true by design. */
    ITS_C_ASSERT((size_t)row >= (size_t)mem);

    /* Compute hash value. */
    hash = LocalHash(key, klen);

    /* Lock hash table. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        result = ret;
        keepOn = ITS_FALSE;
    }
    else
    {
        tablesLocked = ITS_TRUE;
    }

    /* Look up for row list in table according to hash value. */
    if (keepOn)
    {
        ret = HASH_FindEntry(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId,
                    hash,
                    (ITS_POINTER*)&tmp);
        if (ret != ITS_SUCCESS)
        {
            result = ITS_ENOTFOUND;
            keepOn = ITS_FALSE;
        }
    }

    /* Scan row list for correct row. */
    if (keepOn)
    {
        while (tmp != NULL)
        {
            if (tmp->klen == klen &&
                memcmp(tmp->key, key, klen) == 0 &&
                tmp == row)
            {
                break;
            }
            
            tmp = tmp->next;
        }

        ITS_C_ASSERT(tmp != NULL);

        if (tmp == NULL)
        {
            result = ITS_EINVALIDARGS;
            keepOn = ITS_FALSE;
        }
    }

    /* Check row locked only if required. */
    if (keepOn && withLock)
    {
        ITS_C_ASSERT(row->locked);

        if (!row->locked)
        {
            result = ITS_EROWNOTLOCKED;
            keepOn = ITS_FALSE;
        }
    }

    REFLECT_MEMCPY(dataObj, row, row, size);

    /* Unlock row only if required. */
    if (keepOn && withLock)
    {            
        row->locked = ITS_FALSE;
        row->lockTime = 0;
    }

    /* Unlock hash table if locked. */
    if (tablesLocked)
    {
        ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }
    }

    PendingTransDec(dataObj);

    return result;
}

/*
 * LockUnlock.
 */
static int
LockUnlock(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_OCTET* key, 
    ITS_UINT klen, 
    void* object,
    ITS_BOOLEAN lockUnlockToggle)
{
    return ITS_SUCCESS;
}

/*
 * LockUnlockNoLock.
 */
static int
LockUnlockNoLock(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object,
    ITS_BOOLEAN lockUnlockToggle)
{
    return ITS_SUCCESS;
}

/*
 * LockUnlockDsm.
 */
static int
LockUnlockDsm(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_BOOLEAN lockUnlockToggle)
{
    return ITS_SUCCESS;
}

/*
 * LockUnlockTable.
 */
static int
LockUnlockTable(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_BOOLEAN lockUnlockToggle)
{
    return ITS_SUCCESS;
}

static int 
DSM_ImplDataCreateInstanceImpl(
    DSM_CoreObject* coreObj,
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
        return ITS_EIMPLINITFAIL;
    }

    DSM_INST_IMPL_DATA(instObj) = (ITS_Object)dataObj;

    return ITS_SUCCESS;
}

static int 
DSM_ImplDataDestroyInstanceImpl(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    ITS_USHORT  ftGroupId)
{
    DSM_DataObject* dataObj;

    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_DestructObject((ITS_Object)dataObj);

    return ITS_SUCCESS;
}

static int 
DSM_JoinFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    return JoinFtGroup(
                coreObj, 
                ftGroupId);
}

static int 
DSM_LeaveFtGroupImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    return LeaveFtGroup(
                coreObj, 
                ftGroupId);
}

static int 
DSM_SynchronizeDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    return SynchronizeDsm(
                coreObj, 
                ftGroupId,
                msecs);
}

static int 
DSM_LockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    return LockUnlockDsm(
                coreObj, 
                ftGroupId, 
                ITS_TRUE);
}

static int 
DSM_UnlockDsmImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId)
{
    return LockUnlockDsm(
                coreObj, 
                ftGroupId, 
                ITS_FALSE);
}

static int 
DSM_LockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    return LockUnlockTable(
                coreObj,
                ftGroupId,
                tableId,
                ITS_TRUE);
}

static int 
DSM_UnlockTableImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId, 
    ITS_UINT tableId)
{
    return LockUnlockTable(
                coreObj,
                ftGroupId,
                tableId,
                ITS_FALSE);
}


static void* 
DSM_AllocNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    return Alloc(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error,
                ITS_FALSE);
}

static void*
DSM_FindNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    return Find(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                error,
                ITS_FALSE);
}

static int 
DSM_FreeNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return Free(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
}

static int 
DSM_CommitNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return Commit(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
}

static int 
DSM_LockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    return LockUnlockNoLock(
                coreObj,
                ftGroupId,
                object,
                ITS_TRUE);
}

static int 
DSM_UnlockRowNoLockImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    return LockUnlockNoLock(
                coreObj,
                ftGroupId,
                object,
                ITS_FALSE);
}


static void* 
DSM_AllocImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    return Alloc(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error,
                ITS_TRUE);
}

static void* 
DSM_FindImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    return Find(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                error,
                ITS_TRUE);
}

static int 
DSM_FreeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return Free(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_TRUE);
}

static int 
DSM_CommitImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return Commit(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_TRUE);
}

static int 
DSM_LockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return LockUnlock(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_TRUE);
}

static int 
DSM_UnlockRowImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return LockUnlock(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
}

static int 
DSM_TableIterateImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return ITS_SUCCESS;
}

static int 
DSM_TableDumpImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    char** pStrDump,                            
    DSM_DumpEntryProc dumpEntryFn)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return ITS_SUCCESS;
}

static int 
DSM_TableGetSizeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return ITS_SUCCESS;
}

static int 
DSM_MulticastEventToFtGroupMembersImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    const ITS_EVENT* event)
{
    ITS_BOOLEAN not_implemented = ITS_FALSE;
    ITS_C_ASSERT(not_implemented);

    return ITS_SUCCESS;
}

static int
ImplClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsDSMHASH_Class) = itsHASH_Class;

    return ITS_SUCCESS;
}

#define DSM_SCI_IMPL_CLASS_NAME "DSM Implementation Class - SCI"

DSM_ImplClassRec itsDSM_SciImplClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_SCI_IMPL_CLASS_NAME,            /* class name               */
        ImplClassInit,                      /* class init               */
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
        "SCI",
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
        DSM_TableIterateImpl,
        DSM_TableDumpImpl,
        DSM_TableGetSizeImpl,
        DSM_MulticastEventToFtGroupMembersImpl
    }
};

DSMDLLAPI ITS_Class itsDSM_SciImplClass = (ITS_Class)&itsDSM_SciImplClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (SCI) Engine Parser Extension related.
 **
 */


#define DSM_SCI_CONFIG_STRING               "DsmSciConfig"


#define SCI_FT_GROUP_ID_STRING              "sciFtGroupId"

#define SCI_LOCAL_ADAPTER_NO_STRING         "sciLocalAdapterNo"
#define SCI_REMOTE_ADAPTER_NO_STRING        "sciRemoteAdapterNo"
#define SCI_LOCAL_NODE_ID_STRING            "sciLocalNodeId"
#define SCI_REMOTE_NODE_ID_STRING           "sciRemoteNodeId"
#define SCI_LOCAL_SEGMENT_ID_STRING         "sciLocalSegmentId"
#define SCI_REMOTE_SEGMENT_ID_STRING        "sciRemoteSegmentId"
#define SCI_LOCAL_BASE_IRT_NO_STRING        "sciLocalBaseIrtNo"
#define SCI_REMOTE_BASE_IRT_NO_STRING       "sciRemoteBaseIrtNo"
#define SCI_IRT_JOIN_TIMEOUT_STRING         "sciIrtJoinTimeout"
#define SCI_IRT_TRIGGER_TIMEOUT_STRING      "sciIrtTriggerTimeout"
#define SCI_IRT_TRIGGER_INTERVAL_STRING     "sciIrtTriggerInterval"
#define SCI_IRT_WAIT_TIMEOUT_STRING         "sciIrtWaitTimeout"
#define SCI_IRT_CONNECT_TIMEOUT_STRING      "sciIrtConnectTimeout"
#define SCI_SEGMENT_CONNECT_TIMEOUT_STRING  "sciSegmentConnectTimeout"
#define SCI_SYNC_TIMEOUT_STRING             "sciSyncTimeout"
#define SCI_PING_INTERVAL_STRING            "sciPingInterval"
#define SCI_FLOW_CTRL_WND_STRING            "sciFlowCtrlWnd"
#define SCI_RETRY_VALUE_STRING              "sciRetryValue"
#define SCI_LOCAL_DEBUG_STRING              "sciLocalDebug"

#define DSM_SCI_CONFIG_DATA_PTR(x) ((DSM_SCI_Config *)ENGINE_PE_USER_DATA(x))

typedef struct
{
    char* ftGroupId;
    char* localAdapterNo;
    char* remoteAdapterNo;
    char* localNodeId;
    char* remoteNodeId;
    char* localSegmentId;
    char* remoteSegmentId;
    char* localBaseIrtNo;
    char* remoteBaseIrtNo;
    char* irtJoinTimeout;
    char* irtTriggerTimeout;
    char* irtTriggerInterval;
    char* irtWaitTimeout;
    char* irtConnectTimeout;
    char* segmentConnectTimeout;
    char* syncTimeout;
    char* pingInterval;
    char* flowCtrlWnd;
    char* retryValue;
    char* localDebug;
} DSM_SCI_Config;

DSMDLLAPI void
DSM_SCI_ConfigParseStart(
    ENGINE_ParserExtension ext, 
    const char* elem, 
    const char** attr)
{
    if (strcmp(elem, DSM_SCI_CONFIG_STRING) == 0)
    {
        ENGINE_PE_USER_DATA(ext) = calloc(1, sizeof(DSM_SCI_Config));

        ITS_C_ASSERT(ENGINE_PE_USER_DATA(ext) != NULL);

        while (*attr)
        {
            if (strcmp(*attr, SCI_FT_GROUP_ID_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    ftGroupId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        ftGroupId !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_LOCAL_ADAPTER_NO_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    localAdapterNo = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        localAdapterNo !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_REMOTE_ADAPTER_NO_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    remoteAdapterNo = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        remoteAdapterNo !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_LOCAL_NODE_ID_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    localNodeId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        localNodeId != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_REMOTE_NODE_ID_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    remoteNodeId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        remoteNodeId != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_LOCAL_SEGMENT_ID_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    localSegmentId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        localSegmentId != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_REMOTE_SEGMENT_ID_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    remoteSegmentId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        remoteSegmentId != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_LOCAL_BASE_IRT_NO_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    localBaseIrtNo = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        localBaseIrtNo !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_REMOTE_BASE_IRT_NO_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    remoteBaseIrtNo = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        remoteBaseIrtNo !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_IRT_JOIN_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    irtJoinTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        irtJoinTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_IRT_TRIGGER_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    irtTriggerTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        irtTriggerTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_IRT_TRIGGER_INTERVAL_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    irtTriggerInterval = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        irtTriggerInterval !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_IRT_WAIT_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    irtWaitTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        irtWaitTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_IRT_CONNECT_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    irtConnectTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        irtConnectTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_SEGMENT_CONNECT_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    segmentConnectTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        segmentConnectTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_SYNC_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    syncTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        syncTimeout !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_PING_INTERVAL_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    pingInterval = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        pingInterval !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_FLOW_CTRL_WND_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    flowCtrlWnd = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        flowCtrlWnd !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_RETRY_VALUE_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    retryValue = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        retryValue !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, SCI_LOCAL_DEBUG_STRING) == 0)
            {
                attr++;

                DSM_SCI_CONFIG_DATA_PTR(ext)->
                    localDebug = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_SCI_CONFIG_DATA_PTR(ext)->
                        localDebug !=
                            NULL);

                attr++;
            }
            else
            {
                attr += 2;
            }
        }
    }
    else
    {
        /* Ignore. */
    }
}


DSMDLLAPI void
DSM_SCI_ConfigParseStop(
    ENGINE_ParserExtension ext, 
    const char* elem) 
{
    ITS_C_ASSERT(ext != NULL);

    if (strcmp(elem, DSM_SCI_CONFIG_STRING) == 0)
    {
        /* Nothing to do. */
    }
    else
    {
        /* Ignore. */
    }
}

DSMDLLAPI void
DSM_SCI_ConfigConvertParserData(
    RESFILE_Manager* appRes,
    ENGINE_ParserExtension ext)
{
    DSM_SCI_Config* sciConfig = (DSM_SCI_Config*)ENGINE_PE_USER_DATA(ext);
    char ftGroupName[64];
    int ret;

    if (sciConfig != NULL)
    {
        sprintf(
            ftGroupName, 
            "%s%s", 
            DSM_FT_GROUP_STRING, 
            sciConfig->ftGroupId);

        /* Ignore errors (section should already exist). */
        RESFILE_AddSection(
            appRes,
            ftGroupName);

        if (sciConfig->localAdapterNo && 
            strlen(sciConfig->localAdapterNo) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_LOCAL_ADAPTER_NO_STRING,
                    sciConfig->localAdapterNo);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->remoteAdapterNo && 
            strlen(sciConfig->remoteAdapterNo) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_REMOTE_ADAPTER_NO_STRING,
                    sciConfig->remoteAdapterNo);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->localNodeId && 
            strlen(sciConfig->localNodeId) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_LOCAL_NODE_ID_STRING,
                    sciConfig->localNodeId);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->remoteNodeId && 
            strlen(sciConfig->remoteNodeId) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_REMOTE_NODE_ID_STRING,
                    sciConfig->remoteNodeId);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->localSegmentId && 
            strlen(sciConfig->localSegmentId) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_LOCAL_SEGMENT_ID_STRING,
                    sciConfig->localSegmentId);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->remoteSegmentId && 
            strlen(sciConfig->remoteSegmentId) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_REMOTE_SEGMENT_ID_STRING,
                    sciConfig->remoteSegmentId);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->localBaseIrtNo && 
            strlen(sciConfig->localBaseIrtNo) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_LOCAL_BASE_IRT_NO_STRING,
                    sciConfig->localBaseIrtNo);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->remoteBaseIrtNo && 
            strlen(sciConfig->remoteBaseIrtNo) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_REMOTE_BASE_IRT_NO_STRING,
                    sciConfig->remoteBaseIrtNo);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->irtJoinTimeout && 
            strlen(sciConfig->irtJoinTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_IRT_JOIN_TIMEOUT_STRING,
                    sciConfig->irtJoinTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->irtTriggerTimeout && 
            strlen(sciConfig->irtTriggerTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_IRT_TRIGGER_TIMEOUT_STRING,
                    sciConfig->irtTriggerTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->irtTriggerInterval && 
            strlen(sciConfig->irtTriggerInterval) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_IRT_TRIGGER_INTERVAL_STRING,
                    sciConfig->irtTriggerInterval);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->irtWaitTimeout && 
            strlen(sciConfig->irtWaitTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_IRT_WAIT_TIMEOUT_STRING,
                    sciConfig->irtWaitTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->irtConnectTimeout && 
            strlen(sciConfig->irtConnectTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_IRT_CONNECT_TIMEOUT_STRING,
                    sciConfig->irtConnectTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->segmentConnectTimeout && 
            strlen(sciConfig->segmentConnectTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_SEGMENT_CONNECT_TIMEOUT_STRING,
                    sciConfig->segmentConnectTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->syncTimeout && 
            strlen(sciConfig->syncTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_SYNC_TIMEOUT_STRING,
                    sciConfig->syncTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->pingInterval && 
            strlen(sciConfig->pingInterval) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_PING_INTERVAL_STRING,
                    sciConfig->pingInterval);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->flowCtrlWnd && 
            strlen(sciConfig->flowCtrlWnd) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_FLOW_CTRL_WND_STRING,
                    sciConfig->flowCtrlWnd);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->retryValue && 
            strlen(sciConfig->retryValue) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_RETRY_VALUE_STRING,
                    sciConfig->retryValue);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (sciConfig->localDebug && 
            strlen(sciConfig->localDebug) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_SCI_LOCAL_DEBUG_STRING,
                    sciConfig->localDebug);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }


        /* 
         * Free sciConfig data members (not used afterward). 
         */

        if (sciConfig->localAdapterNo)
        {
            free(sciConfig->localAdapterNo);
            sciConfig->localAdapterNo = NULL;
        }

        if (sciConfig->remoteAdapterNo)
        {
            free(sciConfig->remoteAdapterNo);
            sciConfig->remoteAdapterNo = NULL;
        }

        if (sciConfig->localNodeId)
        {
            free(sciConfig->localNodeId);
            sciConfig->localNodeId = NULL;
        }

        if (sciConfig->remoteNodeId)
        {
            free(sciConfig->remoteNodeId);
            sciConfig->remoteNodeId = NULL;
        }

        if (sciConfig->localSegmentId)
        {
            free(sciConfig->localSegmentId);
            sciConfig->localSegmentId = NULL;
        }

        if (sciConfig->remoteSegmentId)
        {
            free(sciConfig->remoteSegmentId);
            sciConfig->remoteSegmentId = NULL;
        }

        if (sciConfig->localBaseIrtNo)
        {
            free(sciConfig->localBaseIrtNo);
            sciConfig->localBaseIrtNo = NULL;
        }

        if (sciConfig->remoteBaseIrtNo)
        {
            free(sciConfig->remoteBaseIrtNo);
            sciConfig->remoteBaseIrtNo = NULL;
        }

        if (sciConfig->irtJoinTimeout)
        {
            free(sciConfig->irtJoinTimeout);
            sciConfig->irtJoinTimeout = NULL;
        }

        if (sciConfig->irtTriggerTimeout)
        {
            free(sciConfig->irtTriggerTimeout);
            sciConfig->irtTriggerTimeout = NULL;
        }

        if (sciConfig->irtTriggerInterval)
        {
            free(sciConfig->irtTriggerInterval);
            sciConfig->irtTriggerInterval = NULL;
        }

        if (sciConfig->irtWaitTimeout)
        {
            free(sciConfig->irtWaitTimeout);
            sciConfig->irtWaitTimeout = NULL;
        }

        if (sciConfig->irtConnectTimeout)
        {
            free(sciConfig->irtConnectTimeout);
            sciConfig->irtConnectTimeout = NULL;
        }

        if (sciConfig->segmentConnectTimeout)
        {
            free(sciConfig->segmentConnectTimeout);
            sciConfig->segmentConnectTimeout = NULL;
        }

        if (sciConfig->syncTimeout)
        {
            free(sciConfig->syncTimeout);
            sciConfig->syncTimeout = NULL;
        }

        if (sciConfig->pingInterval)
        {
            free(sciConfig->pingInterval);
            sciConfig->pingInterval = NULL;
        }

        if (sciConfig->flowCtrlWnd)
        {
            free(sciConfig->flowCtrlWnd);
            sciConfig->flowCtrlWnd = NULL;
        }

        if (sciConfig->retryValue)
        {
            free(sciConfig->retryValue);
            sciConfig->retryValue = NULL;
        }

        if (sciConfig->localDebug)
        {
            free(sciConfig->localDebug);
            sciConfig->localDebug = NULL;
        }
    }
}

DSMDLLAPI void
DSM_SCI_ConfigDiff(
    RESFILE_Manager* appRes,
    ENGINE_ParserExtension ext1,
    ENGINE_ParserExtension ext2)
{
    /* Nothing to do. */
}







