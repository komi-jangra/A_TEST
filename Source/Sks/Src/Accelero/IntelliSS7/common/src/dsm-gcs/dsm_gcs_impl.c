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
 * LOG: Revision 9.3.2.1  2005/11/30 10:16:31  sjaddu
 * LOG: Porting to MVL on power pc.
 * LOG:
 * LOG: Revision 9.3  2005/06/02 14:00:02  adutta
 * LOG: Added source for Multiple App binding.
 * LOG:
 * LOG: Revision 9.2  2005/04/01 12:01:22  ssingh
 * LOG: Sigtran related Bug Fix Propagation to PR6.5/current.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.5  2005/03/21 13:51:36  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.5.2.1.8.5.10.5  2005/01/05 07:21:24  craghavendra
 * LOG: 1. Syslog Enhancements.
 * LOG: 2. Critical Traces before abort() calls.
 * LOG:
 * LOG: Revision 7.5.2.1.8.5.10.4  2004/12/29 10:01:54  ssingh
 * LOG: Revision 7.5.2.1.8.5.10.1 corrected.
 * LOG:
 * LOG: Revision 7.5.2.1.8.5.10.3  2004/12/28 11:43:10  mmanikandan
 * LOG: Support for Windows compilation.
 * LOG:
 * LOG: Revision 7.5.2.1.8.5.10.2  2004/12/16 03:30:35  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.5.2.1.8.5.10.1  2004/12/15 17:10:32  dsatish
 * LOG: Changes propagated from SHIM
 * LOG:
 * LOG:
 * LOG: Revision 7.5.2.1.8.5  2004/02/16 12:22:55  yranade
 * LOG: TCAP Act-Act Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.5.2.1.8.4  2004/02/12 13:33:18  sjaddu
 * LOG: In SubProcedureSyncUnlockToMasterInStateSyncMaster()
 * LOG: call join call back only once.
 * LOG:
 * LOG: Revision 7.5.2.1.8.3  2004/01/27 14:02:37  sjaddu
 * LOG: Changes for active-backup configuration.
 * LOG:
 * LOG: Revision 7.5.2.1.8.1  2004/01/05 09:25:43  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.5.2.1.4.5  2003/10/13 10:17:11  akumar
 * LOG: Silly linking error :-)
 * LOG:
 * LOG: Revision 7.5.2.1.4.4  2003/10/13 09:54:15  akumar
 * LOG: Code cleanup, replaced prints with traces.
 * LOG:
 * LOG: Revision 7.5.2.1.4.3  2003/09/22 08:47:56  akumar
 * LOG: New updates in DSM-GCS.
 * LOG:
 * LOG: Revision 7.5.2.1.2.8  2003/09/11 21:32:08  randresol
 * LOG: add BroadCastEventNotificationCallback and fix network change problem
 * LOG:
 * LOG: Revision 7.5.2.1.2.7  2003/09/02 00:45:56  randresol
 * LOG: Fix ANSI-C compatibility bug
 * LOG:
 * LOG: Revision 7.5.2.1.2.6  2003/08/30 16:57:13  randresol
 * LOG: Add logic for message based redundnacy.
 * LOG:
 * LOG: Revision 7.5.2.1.2.5  2003/06/15 20:06:48  randresol
 * LOG: Continue Prototype...
 * LOG:
 * LOG: Revision 7.5.2.1.2.4  2003/06/15 18:44:28  randresol
 * LOG: Prototype continue...
 * LOG:
 * LOG: Revision 7.5.2.1.2.3  2003/06/15 15:36:40  randresol
 * LOG: Print ISUP CIC for GCS PROTOTYPE test
 * LOG:
 * LOG: Revision 7.5.2.1.2.2  2003/06/13 19:32:26  randresol
 * LOG: Changes for GCS ISUP Prototype...
 * LOG:
 * LOG: Revision 7.5.2.1.2.1  2003/05/05 22:03:44  randresol
 * LOG: Tag for GCS ISUP prototype
 * LOG:
 * LOG: Revision 7.5.2.1  2003/02/19 16:20:33  randresol
 * LOG: Initialize the impl class.  Needed for correct inheritance
 * LOG:
 * LOG: Revision 7.5  2003/01/30 20:46:11  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.4  2003/01/24 16:42:53  mmiers
 * LOG: Remove HASH defines
 * LOG:
 * LOG: Revision 7.3.4.4  2003/04/14 18:25:13  randresol
 * LOG: continue GCS prototype...
 * LOG:
 * LOG: Revision 7.3.4.3  2003/04/14 16:53:35  randresol
 * LOG: Continue Prototype...
 * LOG:
 * LOG: Revision 7.3.4.2  2003/04/14 15:42:43  randresol
 * LOG: Modify processing for Dialogue Id allocation
 * LOG:
 * LOG: Revision 7.3.4.1  2003/04/08 17:47:56  randresol
 * LOG: Chages for GCS TCAP prototype
 * LOG:
 * LOG: Revision 7.3  2002/10/22 21:26:23  lbana
 * LOG: Bug fix in parser extension: parser extension is not reading config
 * LOG: parameters specified for the second FT Group configured in xml.
 * LOG:
 * LOG: Revision 7.2  2002/09/26 22:18:59  yranade
 * LOG: 64 bit fixes
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.12  2002/06/12 20:14:15  hdivoux
 * LOG: Correct 'destroy order' in data create instance.
 * LOG:
 * LOG: Revision 1.11  2002/06/11 22:03:07  hdivoux
 * LOG: Typo.
 * LOG:
 * LOG: Revision 1.10  2002/04/25 15:05:40  hdivoux
 * LOG: More correction for assertion in case of self-join.
 * LOG:
 * LOG: Revision 1.9  2002/04/25 14:55:21  hdivoux
 * LOG: Correction for assertion in case of self-join (one more state).
 * LOG:
 * LOG: Revision 1.8  2002/04/23 19:13:51  hdivoux
 * LOG: Added call to membership change callbacks for self.
 * LOG:
 * LOG: Revision 1.7  2002/04/23 15:31:30  hdivoux
 * LOG: Improved hash function (from Mitch input).
 * LOG:
 * LOG: Revision 1.6  2002/04/22 16:35:19  hdivoux
 * LOG: Slightly improved hash function (from Ricardo input).
 * LOG:
 * LOG: Revision 1.5  2002/04/18 20:20:12  hdivoux
 * LOG: More warnings removal.
 * LOG:
 * LOG: Revision 1.4  2002/04/18 20:12:50  hdivoux
 * LOG: Warnings removal.
 * LOG:
 * LOG: Revision 1.3  2002/04/12 19:38:44  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 1.2  2002/04/12 19:33:12  hdivoux
 * LOG: Work in progress: upcoming FT/HA.
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:41:36  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/


#include <its_dsm_gcs.h>
#include <dsm_gcs_impl.h>
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

#include <itu/mtp3.h>
#include <its_redundancy.h>

#ident "$Id: dsm_gcs_impl.c,v 1.1.1.1 2006-12-22 13:34:37 cvsadmin Exp $"

/*****************************************************************************
 *
 * Note: this file is essentially divided into the following sections:
 *
 *  1) Definitions for portable mmap across Unix variants.
 *  2) Forward definitions (procedures...).
 *  3) Allocator related (definitions).
 *  4) DSMHASH class (table manager).
 *  5) DSM GCS Data class.
 *  6) DSM Procedures.
 *  7) Allocator related (implementation).
 *  8) DSM GCS Impl (implementation) class.
 *  9) DSM GCS Engine Parser Extension related functions.
 *
 *****************************************************************************/

/* 
 * Wisdom: acetylsalicylic acid required to understand this file -- HLD.
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

MLIST_Manager* _GCSStack_RcvQueue = NULL;
MLIST_Manager* _GCSAppl_RcvQueue = NULL;

/******************************************************************************
 ******************************************************************************
 **
 ** Forward declarations.
 **
 */
ITS_UINT PEER_MTP3_NODE_STATUS = 1;
static counter =0;

static THREAD_RET_TYPE ProceduresThread(void* arg);
static THREAD_RET_TYPE SyncMemTcpListenThread(void* arg);

static ITS_USHORT MemberNameToNodeId(
                DSM_DataObject* dataObj, 
                const char* memberName);

static ITS_USHORT MemberNameToProcessId(
                DSM_DataObject* dataObj, 
                const char* memberName);

static ITS_USHORT MemberNameToFtGroupId(
                DSM_DataObject* dataObj, 
                const char* memberName);

static void ProcedureAllocateRow(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureFindRow(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureFreeRow(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureCommitRow(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureJoinInfo(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncRequest(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncLock(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncLockRetry(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncUnlock(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncMem(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncMemTcp(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureSyncInvalidMaster(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureJoin(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureLeave(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureDisconnect(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureNetworkChange(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureLockUnlockRow(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureLockUnlockTable(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureLockUnlockDsm(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);

static void ProcedureLockUnlockRowNoLock(
                DSM_DataObject* dataObj,
                GCS_SERVICE service,
                char sender[GCS_MAX_GROUP_NAME],
                ITS_INT numGroups,
                char groups[][GCS_MAX_GROUP_NAME],
                ITS_UINT size,
                char msg[DSM_MAX_MSG_SIZE]);
static int
TablesCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj);
static int
TablesDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj);

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
//define DEFAULT_MXFAST     0

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


/******************************************************************************
 ******************************************************************************
 **
 ** DSMHASH class (table manager).
 **
 */

/*
 * DSM GCS operations to the table manager hash table are applied in the exact
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
CreateTable(ITS_Object obj, va_list args)
{
    DSMHASH_Table db = (DSMHASH_Table)obj;
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

    DSM_RowHeader *rhdr;
    DSM_RowHeader *rhdr1;
    ITS_POINTER   nptr;

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

                rhdr = (DSM_RowHeader *) entry->data;

                rhdr1 = rhdr->next;

                while(rhdr1 != NULL)
                {
                    nptr = (ITS_POINTER) (rhdr1) + sizeof(DSM_RowHeader);

                    res = iterateEntryFn(nptr, in, out);
                    if (res != ITS_SUCCESS)
                    {
                        return res;
                    }
                    rhdr1 = rhdr1->next;
                };
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

    DSM_RowHeader *rhdr;
    DSM_RowHeader *rhdr1;
    ITS_POINTER   nptr;

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

                rhdr = (DSM_RowHeader *) entry->data;

                rhdr1 = rhdr->next;

                while (rhdr1 != NULL)
                {
                    strEntryDump = NULL;

                    nptr = (ITS_POINTER) (rhdr1) + sizeof(DSM_RowHeader);

                    res = dumpEntryFn(nptr, &strEntryDump);

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

                    rhdr1 = rhdr1->next;
                }
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
        (HASH_VTableIterateProc)VTableIterate,/* VTable iterate method    */
        HashAlloc,                          /* allocation method        */
        HashFree                            /* free method              */
    }
};

static ITS_Class itsDSMHASH_Class = (ITS_Class)&itsDSMHASH_ClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (GCS) Data class.
 **
 */

/*
 * Utilities.
 */

static ITS_BOOLEAN
HasFtGroupMember(
    DSM_DataObject* dataObj,
    ITS_USHORT nodeId,
    ITS_USHORT processId)
{
    DSM_InstObject* instObj;
    int i;

    instObj = DSM_DATA_INST_OBJECT(dataObj);

    for (i = 0; i < DSM_INST_NUM_FT_GROUP_MEMBERS(instObj); i++)
    {
        if (DSM_INST_FT_GROUP_MEMBERS(instObj)[i].nodeId == nodeId && 
            DSM_INST_FT_GROUP_MEMBERS(instObj)[i].processId == processId)
        {
            return ITS_TRUE;
        }
    }

    return ITS_FALSE;
}

static ITS_BOOLEAN
HasMasterFtGroupMember(
    DSM_DataObject* dataObj,
    ITS_USHORT nodeId,
    ITS_USHORT processId)
{
    DSM_InstObject* instObj;
    int i;

    instObj = DSM_DATA_INST_OBJECT(dataObj);

    for (i = 0; i < DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(instObj); i++)
    {
        if (DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj)[i].nodeId == nodeId && 
            DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj)[i].processId == 
                processId)
        {
            return ITS_TRUE;
        }
    }

    return ITS_FALSE;
}

/*
 * Retrieve all Fault Tolerance Group Members: remote members AND local member.
 * Argument ftGroupMembers must be an array of 'DSM_MAX_MEMBERS' FtGroupMembers
 * (to be initialized by function).
 */

static void
RemoteMembersToFtGroupMembers(
    DSM_DataObject* dataObj,
    ITS_USHORT* numFtGroupMembers,
    DSM_FtGroupMember* ftGroupMembers)
{
    DSM_CoreObject* coreObj;
    int i, j;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(numFtGroupMembers != NULL);
    ITS_C_REQUIRE(ftGroupMembers != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);

    /* Reset. */
    memset(ftGroupMembers, 0, DSM_MAX_MEMBERS * sizeof(DSM_FtGroupMember));
    *numFtGroupMembers = 0;

    /* Local member. */
    ftGroupMembers[0].nodeId = DSM_CORE_NODE_ID(coreObj);
    ftGroupMembers[0].processId = DSM_CORE_PROCESS_ID(coreObj);
    (*numFtGroupMembers)++;

    /* Remote members. */

    j = 1; /* Index of remote members in ftGroupMembers array. */
    
    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (DSM_DATA_REMOTES(dataObj).members[i].valid)
        {
            char* memberName;
            ITS_USHORT nodeId;
            ITS_USHORT processId;

            memberName = DSM_DATA_REMOTES(dataObj).members[i].memberName;

            nodeId = MemberNameToNodeId(dataObj, memberName);
            processId = MemberNameToProcessId(dataObj, memberName);

            if (nodeId != DSM_INVALID_NODE_ID && 
                processId != DSM_INVALID_PROCESS_ID)
            {
                ITS_C_ASSERT(j < DSM_MAX_MEMBERS);

                ftGroupMembers[j].nodeId = nodeId;
                ftGroupMembers[j].processId = processId;

                (*numFtGroupMembers)++;

                j++;
            }
            else
            {
                /* TODO: add trace. */
            }
        }
    }   
}

static void
CallMembershipChangeCallbacks(
    DSM_DataObject* dataObj,
    const char* memberName,
    DSM_MembershipChangeType membershipChangeType)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    DSM_MembershipChangeCbData membershipChangeCbData;
    DSM_FtGroupMember ftGroupMembers[DSM_MAX_MEMBERS];
    ITS_USHORT numFtGroupMembers;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_TRACE_DEBUG(("$$$$$$$$ CallMembershipChangeCallbacks: dataObj = 0x%x $$$$$$$$\n", dataObj));

    nodeId = MemberNameToNodeId(dataObj, memberName);
    if (nodeId == DSM_INVALID_NODE_ID)
    {
        /* TODO: add trace. */
        return;
    }

    processId = MemberNameToProcessId(dataObj, memberName);
    if (processId == DSM_INVALID_PROCESS_ID)
    {
        /* TODO: add trace. */
        return;
    }

    RemoteMembersToFtGroupMembers(
        dataObj,
        &numFtGroupMembers,
        ftGroupMembers);

    membershipChangeCbData.ftGroupId = DSM_INST_FT_GROUP_ID(instObj);
    membershipChangeCbData.membershipChangeType = membershipChangeType;
    membershipChangeCbData.memberNodeId = nodeId;
    membershipChangeCbData.memberProcessId = processId;
    membershipChangeCbData.numFtGroupMembers = numFtGroupMembers;
    membershipChangeCbData.ftGroupMembers = ftGroupMembers;

    ret = CALLBACK_CallCallbackList(
            DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(instObj),
            (ITS_POINTER)dataObj,
            (ITS_POINTER)&membershipChangeCbData);
    if (ret != ITS_SUCCESS)
    {
        /* TODO: add trace. */
        return;
    }
}

/*.implementation:static
 ******************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *
 *
 *  Input/Output Parameters:
 *
 *    None.
 *
 *  Output Parameters:
 *
 *    None.
 *
 *  Return Value:
 *
 *
 *  Notes:
 *
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference      Description
 * -----------------------------------------------------------------------------
 * ssingh    04-01-2005  BugId: 822     Bug fix propagation. 
 *                                      ISG dumping core when gcs is not running
 *
 *  See Also:
 *
 ******************************************************************************/
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
        ITS_TRACE_CRITICAL(("DSM Subsystem: No Critical Error Notification CallBacks\n"));
        //abort();
        exit(1);

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

DSMDLLAPI extern void
BroadCastEventNotificationCallback(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{

    //DSM_Message *multicastMessage;
    DSM_Message_Multicast *multicastMessage;
    DSM_Message_Multicast *queuedMessage;
    ITS_EVENT ev;
    ITS_EVENT queuedEv;
    int len;
    
   DSM_DataObject *dataObj = (DSM_DataObject*) object; 

/* NOTE: need to dequeue when the state is being changed to NORMAL */

    DSM_MembershipChangeCbData*
        membershipChangeCbData = (DSM_MembershipChangeCbData*)callData;

    if (membershipChangeCbData->
            membershipChangeType == 
                DSM_FT_GROUP_MEMBER_JOIN ) 
    {

        ITS_TRACE_DEBUG(("$$$$BroadCastEventNotificationCallback$$$$\n"));

        ITS_TRACE_DEBUG(("$$$$ dataObj = 0x%x MList = 0x%x $$$$\n",
                         object, DSM_DATA_STACK_MULTICAST_QUEUE(dataObj)));


#if 0
        multicastMessage  = (DSM_Message *) DSM_DATA_LOCAL(dataObj).bufMsg;

        if (TRANSPORT_FindTransport(
                 multicastMessage->u.multicastEvent.dest) != NULL)
#endif
        {
            /* Dequeue all saved messages and send all to thread */

            ITS_TRACE_DEBUG(("$$$$ _GCSStack_RcvQueue count = %d $$$$\n", 
                    MLIST_GetCount(DSM_DATA_STACK_MULTICAST_QUEUE(dataObj))));

            while (MLIST_GetCount(DSM_DATA_STACK_MULTICAST_QUEUE(dataObj)) != 0)
            { 
                EMLIST_RemHead(DSM_DATA_STACK_MULTICAST_QUEUE(object), 
                                   (void**)&queuedMessage, &len);

                             
                ITS_EVENT_INIT(&queuedEv, 
                               queuedMessage->u.multicastEvent.source, 
                               queuedMessage->u.multicastEvent.ev.len);

                memcpy(queuedEv.data, 
                       queuedMessage->u.multicastEvent.data,
                       queuedMessage->u.multicastEvent.ev.len);
                    
                ITS_TRACE_DEBUG(("$$$$BroadCastEventNotificationCallback:: DEQUEUE Ev $$$$\n"));
                if (TRANSPORT_FindTransport(
                    queuedMessage->u.multicastEvent.dest) == NULL)
                {
                    ITS_TRACE_DEBUG(("$$$$Transport %d is down. Re-insert in HEAD $$$$\n", queuedMessage->u.multicastEvent.dest));

                    MLIST_AddHead(DSM_DATA_STACK_MULTICAST_QUEUE(object), 
                                  queuedMessage, sizeof(DSM_Message_Multicast));

                    return;
                }

                if (TRANSPORT_PutEvent(
                                queuedMessage->u.multicastEvent.dest, 
                                &queuedEv) != ITS_SUCCESS)
                {
                     ITS_TRACE_ERROR(("$$$ PutEvent Failed: dest = %d $$$$\n",
                                      queuedMessage->u.multicastEvent.dest));

                     /*TOTO: Enqueue message to _GCSStack_RcvQueue */
 
                }

                free(queuedMessage);

            }
        }
    }

}

/*
 * DataClassInitialize.
 */
static int
DataClassInitialize(
    ITS_Class objClass)
{
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
}

/*
 * DSM message type to string.
 */
static const char*
MsgTypeToStr(
    ITS_UINT msgType)
{
    switch (msgType)
    {
    case DSM_MSG_ALLOCATE_ROW:
        return "ALLOCATE ROW";
    case DSM_MSG_FIND_ROW:
        return "FIND ROW";
    case DSM_MSG_FREE_ROW:
        return "FREE ROW";
    case DSM_MSG_COMMIT_ROW:
        return "COMMIT ROW";
    case DSM_MSG_JOIN_INFO:
        return "JOIN INFO";
    case DSM_MSG_SYNC_LOCK:
        return "SYNC LOCK";
    case DSM_MSG_SYNC_LOCK_RETRY:
        return "SYNC LOCK RETRY";
    case DSM_MSG_SYNC_UNLOCK:
        return "SYNC UNLOCK";
    case DSM_MSG_SYNC_MEM:
        return "SYNC MEM";
    case DSM_MSG_SYNC_INVALID_MASTER:
        return "SYNC INVALID MASTER";
    case DSM_MSG_SYNC_MEM_TCP:
        return "SYNC MEM TCP";
    case DSM_MSG_LOCK_UNLOCK_ROW:
        return "LOCK UNLOCK ROW";
    case DSM_MSG_LOCK_UNLOCK_TABLE:
        return "LOCK UNLOCK TABLE";
    case DSM_MSG_LOCK_UNLOCK_DSM:
        return "LOCK UNLOCK DSM";
    case DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK:
        return "LOCK UNLOCK ROW NO LOCK";
    default:
        return "UNKNOWN";
    }
}

/* 
 * DSM state (GCS) to string.
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
    case DSM_STATE_NORMAL:
        return "NORMAL";
    case DSM_STATE_SYNC_WAIT:
        return "SYNC WAIT";
    case DSM_STATE_SYNC_SLAVE:
        return "SYNC SLAVE";
    case DSM_STATE_SYNC_MASTER:
        return "SYNC MASTER";
    case DSM_STATE_SYNC_NEUTRAL:
        return "SYNC NEUTRAL";
    case DSM_STATE_INVALID:
        return "INVALID";
    default:
        return "UNKNOWN";
    }
}

/*
 * DSM SYNC MEM TCP command to string.
 */
static const char*
SyncMemTcpCmdToStr(
    ITS_UINT cmd)
{
    switch (cmd)
    {
    case DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT:
        return "TCP CMD SLAVE DO CONNECT";
    case DSM_SYNC_MEM_TCP_MASTER_DO_SEND:
        return "TCP CMD MASTER DO SEND";
    case DSM_SYNC_MEM_TCP_SLAVE_DO_RECEIVE:
        return "TCP CMD SLAVE DO RECEIVE";
    case DSM_SYNC_MEM_TCP_MASTER_DO_CLOSE:
        return "TCP CMD MASTER DO CLOSE";
    case DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE:
        return "TCP CMD SLAVE DO CLOSE";
    default:
        return "TCP CMD UNKNOWN";
    }
}

/*
 * DSM procedure type to string.
 */
static const char*
ProcedureTypeToStr(
    ITS_UINT procedureType)
{
    switch (procedureType)
    {
    case DSM_PROCEDURE_ALLOCATE_ROW:
        return "ALLOCATE ROW";
    case DSM_PROCEDURE_FIND_ROW:
        return "FIND ROW";
    case DSM_PROCEDURE_FREE_ROW:
        return "FREE ROW";
    case DSM_PROCEDURE_COMMIT_ROW:
        return "COMMIT ROW";
    case DSM_PROCEDURE_LOCK_UNLOCK_ROW:
        return "LOCK UNLOCK ROW";
    case DSM_PROCEDURE_LOCK_UNLOCK_TABLE:
        return "LOCK UNLOCK TABLE";
    case DSM_PROCEDURE_LOCK_UNLOCK_DSM:
        return "LOCK UNLOCK DSM";
    case DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK:
        return "LOCK UNLOCK ROW NO LOCK";
    case DSM_PROCEDURE_SYNC_REQUEST:
        return "SYNC REQUEST";
    case DSM_PROCEDURE_SYNC_LOCK:
        return "SYNC LOCK";
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

    DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_FALSE;
    DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_FALSE;

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
                            DSM_GCS_CONNECT_TIMEOUT_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            int connectTimeout = RESFILE_ParseNum(value);

            DSM_DATA_CONFIG(dataObj).connectTimeout.sec = 
                connectTimeout / DSM_MSEC_PER_SEC;
            DSM_DATA_CONFIG(dataObj).connectTimeout.usec = 
                (connectTimeout % DSM_MSEC_PER_SEC) * DSM_USEC_PER_MSEC;
        }
        else
        {
            /* Default value. */
            DSM_DATA_CONFIG(dataObj).connectTimeout.sec = 10;
            DSM_DATA_CONFIG(dataObj).connectTimeout.usec = 0;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb,
                            ftGroupSectionName,
                            DSM_GCS_DAEMON_NAME_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            if (strlen(value) >= DSM_MAX_DAEMON_NAME_SIZE)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] Length of string '%s' in the "
                    "configuration must be less than %u\n",
                    ftGroupId,
                    DSM_GCS_DAEMON_NAME_STRING,
                    DSM_MAX_DAEMON_NAME_SIZE));

                abort();
            }

            strcpy(DSM_DATA_CONFIG(dataObj).gcsDaemonName, value);
            strcpy(DSM_DATA_CONFIG(dataObj).gcsStubDaemonName, "9900");
        }
        else
        {
            /* Default value. */
#if defined(WIN32)
            strcpy(DSM_DATA_CONFIG(dataObj).gcsDaemonName, "4803@localhost");
#else /* !defined(WIN32) */
            strcpy(DSM_DATA_CONFIG(dataObj).gcsDaemonName, "4803");
#endif /* defined(WIN32) */

        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_GROUP_NAME_STRING,
                            value,
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            if (strlen(value) >= DSM_MAX_GROUP_NAME_SIZE)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] Length of string '%s' in the "
                    "configuration must be less than %u\n",
                    ftGroupId,
                    DSM_GCS_GROUP_NAME_STRING,
                    DSM_MAX_GROUP_NAME_SIZE));

                abort();
            }

            strcpy(DSM_DATA_CONFIG(dataObj).groupName, value);
        }
        else
        {
            /* Default value. */
            sprintf(buffer, "dsm%u", ftGroupId);
            strcpy(DSM_DATA_CONFIG(dataObj).groupName, buffer);
        }

        if (RESFILE_GetKeyValueOf(
                            configDb,
                            ftGroupSectionName,
                            DSM_GCS_CONNECTION_NAME_ROOT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            if (strlen(value) >= DSM_MAX_CONNECTION_NAME_ROOT_SIZE)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] Length of string '%s' in the "
                    "configuration must be less than %u\n",
                    ftGroupId,
                    DSM_GCS_CONNECTION_NAME_ROOT_STRING,
                    DSM_MAX_CONNECTION_NAME_ROOT_SIZE));

                abort();
            }

            if (strstr(value, "-") != NULL)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] String '%s' in the configuration must not"
                    "contain '-' character\n",
                    ftGroupId,
                    DSM_GCS_CONNECTION_NAME_ROOT_STRING));

                abort();
            }

            strcpy(DSM_DATA_CONFIG(dataObj).connectionNameRoot, value);
        }
        else
        {
            /* Default value. */
            sprintf(buffer, "d");
            strcpy(DSM_DATA_CONFIG(dataObj).connectionNameRoot, buffer);
        }

        if (RESFILE_GetKeyValueOf(
                            configDb,
                            ftGroupSectionName,
                            DSM_GCS_RECEIVER_ALIVE_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            int receiverAliveTimeout = RESFILE_ParseNum(value);

            DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.sec = 
                receiverAliveTimeout / DSM_MSEC_PER_SEC;
            DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.usec = 
                (receiverAliveTimeout % DSM_MSEC_PER_SEC) * DSM_USEC_PER_MSEC;
        }
        else
        {
            /* Default value. */
            DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.sec = 3;
            DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.usec = 0;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_USE_TCP_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            int syncMemUseTcp = RESFILE_ParseNum(value);

            int syncMemUseGcs = 0;

            if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_USE_GCS_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                syncMemUseGcs = RESFILE_ParseNum(value);
            }
            else
            {
                syncMemUseGcs = 0;
            }

            if (syncMemUseTcp && syncMemUseGcs)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] Options '%s' and '%s' are exclusive. You "
                    "must specify one or the other\n",
                    ftGroupId,
                    DSM_GCS_SYNC_MEM_USE_TCP_STRING,
                    DSM_GCS_SYNC_MEM_USE_GCS_STRING));

                abort();
            }
            else if (syncMemUseTcp)
            {
                DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_TRUE;
                DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_FALSE;
            }
            else if (syncMemUseGcs)
            {
                DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_FALSE;
                DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_TRUE;
            }
            else
            {
                DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_TRUE;
                DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_FALSE;
            }
        }
        else
        {
            int syncMemUseGcs = 0;

            if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_USE_GCS_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
            {
                syncMemUseGcs = RESFILE_ParseNum(value);
            }
            else
            {
                syncMemUseGcs = 0;
            }

            if (syncMemUseGcs)
            {
                DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_FALSE;
                DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_TRUE;
            }
            else
            {
                DSM_DATA_CONFIG(dataObj).syncMemUseTcp = ITS_TRUE;
                DSM_DATA_CONFIG(dataObj).syncMemUseGcs = ITS_FALSE;
            }
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).syncMemTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            /* Default value is 60 seconds. */
            DSM_DATA_CONFIG(dataObj).syncMemTimeout = 60000;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_CONNECT_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).syncMemConnectTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            /* Default value is 2 seconds. */
            DSM_DATA_CONFIG(dataObj).syncMemConnectTimeout = 2000;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_IP_ADDRESS_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            if (strlen(value) >= DSM_MAX_IP_ADDRESS_SIZE)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] Length of string '%s' in the "
                    "configuration must be less than %u\n",
                    ftGroupId,
                    DSM_GCS_SYNC_MEM_IP_ADDRESS_STRING,
                    DSM_MAX_IP_ADDRESS_SIZE));

                abort();
            }

            strcpy(DSM_DATA_CONFIG(dataObj).syncMemIpAddress, value);
        }
        else
        {
            if (DSM_DATA_CONFIG(dataObj).syncMemUseTcp)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] You must specify '%s' in the "
                    "configuration if '%s' is specified (specified by "
                    "default)\n",
                    ftGroupId,
                    DSM_GCS_SYNC_MEM_IP_ADDRESS_STRING,
                    DSM_GCS_SYNC_MEM_USE_TCP_STRING));

                abort();
            }

            /* Default value. */
            strcpy(DSM_DATA_CONFIG(dataObj).syncMemIpAddress, "127.0.0.1");
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SYNC_MEM_IP_PORT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).syncMemIpPort = 
                (ITS_USHORT)RESFILE_ParseNum(value);
        }
        else
        {
            if (DSM_DATA_CONFIG(dataObj).syncMemUseTcp)
            {
                ITS_TRACE_CRITICAL((
                    "[FtGroupId: %u] You must specify '%s' in the "
                    "configuration if '%s' is specified (specified by "
                    "default)\n",
                    ftGroupId,
                    DSM_GCS_SYNC_MEM_IP_PORT_STRING,
                    DSM_GCS_SYNC_MEM_USE_TCP_STRING));

                abort();
            }

            /* Default value. */
            DSM_DATA_CONFIG(dataObj).syncMemIpPort = 4804;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_SELF_JOIN_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).selfJoinTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).selfJoinTimeout = 
                DSM_DEFAULT_SELF_JOIN_TIMEOUT;
        }

        if (RESFILE_GetKeyValueOf(
                            configDb, 
                            ftGroupSectionName,
                            DSM_GCS_MASTER_JOIN_TIMEOUT_STRING,
                            value, 
                            DSM_MAX_CONFIG_VALUE_SIZE) == ITS_SUCCESS)
        {
            DSM_DATA_CONFIG(dataObj).masterJoinTimeout = 
                (ITS_ULONG)RESFILE_ParseNum(value);
        }
        else
        {
            DSM_DATA_CONFIG(dataObj).masterJoinTimeout =
                DSM_DEFAULT_MASTER_JOIN_TIMEOUT;
        }
    }
    else
    {
        ITS_TRACE_CRITICAL(("DSM SubSystem: Resource Manager configuration\n")); 
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

    (*tcb)->tid = 0;
    (*tcb)->next = NULL;


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

    tcbManager->table.hash = HASH_CreateTable();
    if (tcbManager->table.hash == NULL)
    {
        ITS_TRACE_ERROR((
            "TcbManagerCreate [FtGroupId: %u]: HASH_CreateTable failed\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_ENOMEM;
    }

    ret = RWLOCK_CreateLock(&tcbManager->tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbManagerCreate [FtGroupId: %u]: RWLOCK_CreateLock failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteTable(tcbManager->table.hash);
        return ret;
    }

    tcbManager->freeList = NULL;

    ret = MUTEX_CreateMutex(&tcbManager->freeListLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "TcbManagerCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteTable(tcbManager->table.hash);
        RWLOCK_DeleteLock(&tcbManager->tableRwLock);
        return ret;
    }

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

    HASH_DeleteTable(tcbManager->table.hash);

    RWLOCK_DeleteLock(&tcbManager->tableRwLock);

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

    MUTEX_DeleteMutex(&tcbManager->freeListLock);

    return ITS_SUCCESS;
}

static int
LocalMemberCreate(
    DSM_DataObject* dataObj,
    ITS_USHORT ftGroupId)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    char connectionName[64];
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

//    DSM_DATA_LOCAL(dataObj).mailbox = 0;
    DSM_DATA_LOCAL(dataObj).Stubmailbox = 0;

    DSM_DATA_LOCAL(dataObj).connectTimeout.sec = 
        DSM_DATA_CONFIG(dataObj).connectTimeout.sec;
    DSM_DATA_LOCAL(dataObj).connectTimeout.usec = 
        DSM_DATA_CONFIG(dataObj).connectTimeout.usec;

    memset(
        DSM_DATA_LOCAL(dataObj).gcsDaemonName, 
        0, 
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_LOCAL(dataObj).gcsStubDaemonName,
        0,
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_LOCAL(dataObj).connectionName, 
        0, 
        GCS_MAX_PRIVATE_NAME * sizeof(char));
    memset(
        DSM_DATA_LOCAL(dataObj).memberName, 
        0, 
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_LOCAL(dataObj).groupName, 
        0, 
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_LOCAL(dataObj).connectionNameRoot, 
        0, 
        DSM_MAX_CONNECTION_NAME_ROOT_SIZE * sizeof(char));

    strcpy(
        DSM_DATA_LOCAL(dataObj).gcsDaemonName, 
        DSM_DATA_CONFIG(dataObj).gcsDaemonName);
    strcpy(
        DSM_DATA_LOCAL(dataObj).gcsStubDaemonName,
        DSM_DATA_CONFIG(dataObj).gcsStubDaemonName);

    strcpy(
        DSM_DATA_LOCAL(dataObj).connectionNameRoot, 
        DSM_DATA_CONFIG(dataObj).connectionNameRoot);

    /* 
     * Build connectionName from connectionNameRoot, nodeId, processId and
     * ftGroupId. 
     */
    sprintf(
        connectionName, 
        "%s-%u-%u-%u",
        DSM_DATA_LOCAL(dataObj).connectionNameRoot, 
        DSM_CORE_NODE_ID(coreObj),
        DSM_CORE_PROCESS_ID(coreObj),
        ftGroupId);
    ITS_C_ASSERT(strlen(connectionName) < GCS_MAX_PRIVATE_NAME);
    strcpy(DSM_DATA_LOCAL(dataObj).connectionName, connectionName);

    strcpy(
        DSM_DATA_LOCAL(dataObj).groupName, 
        DSM_DATA_CONFIG(dataObj).groupName);

    ret = MUTEX_CreateMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        return ret;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        return ret;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        return ret;
    }

    ret = MUTEX_CreateMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        return ret;
    }

    DSM_DATA_LOCAL(dataObj).bufAllocate = 
        (ITS_OCTET*)calloc(
            sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH, 
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufAllocate == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufFind = 
        (ITS_OCTET*)calloc(
            sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH, 
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufFind == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufFree = 
        (ITS_OCTET*)calloc(
            sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH, 
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufFree == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufCommit = 
        (ITS_OCTET*)calloc(
            sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH + DSM_MAX_OBJECT_SIZE,
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufCommit == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufLockUnlock = 
        (ITS_OCTET*)calloc(
            sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH,
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufLockUnlock == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        free(DSM_DATA_LOCAL(dataObj).bufCommit);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufKey = 
        (ITS_OCTET*)calloc(
            DSM_MAX_KEY_LENGTH, 
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufKey == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        free(DSM_DATA_LOCAL(dataObj).bufCommit);
        free(DSM_DATA_LOCAL(dataObj).bufLockUnlock);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufObject = 
        (ITS_OCTET*)calloc(
            DSM_MAX_OBJECT_SIZE + sizeof(ITS_UINT), 
            sizeof(ITS_OCTET));
    if (DSM_DATA_LOCAL(dataObj).bufObject == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        free(DSM_DATA_LOCAL(dataObj).bufCommit);
        free(DSM_DATA_LOCAL(dataObj).bufLockUnlock);
        free(DSM_DATA_LOCAL(dataObj).bufKey);
        return ITS_ENOMEM;
    }

    DSM_DATA_LOCAL(dataObj).bufMsg = 
        (char*)calloc(
            DSM_MAX_MSG_SIZE, 
            sizeof(char));
    if (DSM_DATA_LOCAL(dataObj).bufMsg == NULL)
    {
        ITS_TRACE_ERROR((
            "LocalMemberCreate [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        free(DSM_DATA_LOCAL(dataObj).bufCommit);
        free(DSM_DATA_LOCAL(dataObj).bufLockUnlock);
        free(DSM_DATA_LOCAL(dataObj).bufKey);
        free(DSM_DATA_LOCAL(dataObj).bufObject);
        return ITS_ENOMEM;
    }

    return ITS_SUCCESS;
}

static int
LocalMemberDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
    MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
    MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
    MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
    MUTEX_DeleteMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);

    if (DSM_DATA_LOCAL(dataObj).bufAllocate != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufAllocate);
        DSM_DATA_LOCAL(dataObj).bufAllocate = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufFind != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufFind);
        DSM_DATA_LOCAL(dataObj).bufFind = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufFree != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufFree);
        DSM_DATA_LOCAL(dataObj).bufFree = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufCommit != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufCommit);
        DSM_DATA_LOCAL(dataObj).bufCommit = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufLockUnlock != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufLockUnlock);
        DSM_DATA_LOCAL(dataObj).bufLockUnlock = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufKey != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufKey);
        DSM_DATA_LOCAL(dataObj).bufKey = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufObject != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufObject);
        DSM_DATA_LOCAL(dataObj).bufObject = NULL;
    }

    if (DSM_DATA_LOCAL(dataObj).bufMsg != NULL)
    {
        free(DSM_DATA_LOCAL(dataObj).bufMsg);
        DSM_DATA_LOCAL(dataObj).bufMsg = NULL;
    }

    return ITS_SUCCESS;
}

static int
RemoteMembersCreate(
    DSM_DataObject* dataObj)
{
    int i;

    ITS_C_REQUIRE(dataObj != NULL);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        DSM_DATA_REMOTES(dataObj).members[i].valid                  = 
            ITS_FALSE;
        memset(
            DSM_DATA_REMOTES(dataObj).members[i].memberName, 
            0, 
            GCS_MAX_GROUP_NAME * sizeof(char));
        memset(
            DSM_DATA_REMOTES(dataObj).members[i].syncMemIpAddress,
            0,
            DSM_MAX_IP_ADDRESS_SIZE * sizeof(char));
        DSM_DATA_REMOTES(dataObj).members[i].syncMemIpPort          = 
            4804;
        DSM_DATA_REMOTES(dataObj).members[i].nodeId                 = 
            DSM_INVALID_NODE_ID;
        DSM_DATA_REMOTES(dataObj).members[i].processId              = 
            DSM_INVALID_PROCESS_ID;
        DSM_DATA_REMOTES(dataObj).members[i].lastKnownState         = 
            DSM_STATE_INVALID;
    }

    return ITS_SUCCESS;
}

static int
RemoteMembersDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    /* Nothing to do. */
    return ITS_SUCCESS;
}

static int
GcsDaemonConnectionCreate(
    DSM_DataObject* dataObj)
{
    int ret;
#if 0

    /* Connect to GCS Daemon (MUST be already running). */
    ret = GCS_ConnectTimeout(
                    DSM_DATA_LOCAL(dataObj).gcsDaemonName,
                    DSM_DATA_LOCAL(dataObj).connectionName,
                    0,
                    1,
                    &DSM_DATA_LOCAL(dataObj).mailbox,
                    DSM_DATA_LOCAL(dataObj).memberName,
                    DSM_DATA_LOCAL(dataObj).connectTimeout);
    if (ret != GCS_ACCEPT_SESSION)
    {
        ITS_TRACE_ERROR((
            "GcsDaemonConnectionCreate [FtGroupId: %u]: GCS_ConnectTimeout "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to connect to GCS Daemon. Is it "
            "running?\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_EGCSCONNECTFAIL;
    }
#endif
     /* Connect to GCS Daemon (MUST be already running). */
      ret = GCSStub_ConnectTimeout(
                    DSM_DATA_LOCAL(dataObj).gcsStubDaemonName,
                    DSM_DATA_LOCAL(dataObj).connectionName,
                    0,
                    1,
                    &DSM_DATA_LOCAL(dataObj).Stubmailbox,
                    DSM_DATA_LOCAL(dataObj).memberName,
                    DSM_DATA_LOCAL(dataObj).connectTimeout);
      if (ret != GCS_ACCEPT_SESSION)
      {
        ITS_TRACE_ERROR((
            "GcsDaemonConnectionCreate [FtGroupId: %u]: GCS_ConnectTimeout "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to connect to GCS Daemon. Is it "
            "running?\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_EGCSCONNECTFAIL;
      }
    ITS_TRACE_DEBUG((
        "GcsDaemonConnectionCreate  [FtGroupId: %u]: GCS_ConnectTimeout "
        "succeeded\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    return ITS_SUCCESS;
}

static int
GcsDaemonConnectionDestroy(
    DSM_DataObject* dataObj)
{
    int ret;

    /* Disconnect from GCS Daemon. */
    ret = GCS_Disconnect(DSM_DATA_LOCAL(dataObj).Stubmailbox);
    if (ret != GCS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "GcsDaemonConnectionDestroy [FtGroupId: %u]: GCS_Disconnect "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to disconnect from GCS Daemon\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_EGCSDISCONNECTFAIL;
    }

    ITS_TRACE_DEBUG((
        "GcsDaemonConnectionDestroy [FtGroupId: %u]: GCS_Disconnect "
        "succeeded\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    return ITS_SUCCESS;
}

static int
ProceduresCreate(
    DSM_DataObject* dataObj)
{
    int ret;
    CALLBACK_Manager* cbManager;

    ITS_C_REQUIRE(dataObj != NULL);

    /* Initialize alive timeout. */
    DSM_DATA_PROCEDURES(dataObj).aliveTimeout.sec  = 
        DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.sec;
    DSM_DATA_PROCEDURES(dataObj).aliveTimeout.usec = 
        DSM_DATA_CONFIG(dataObj).receiverAliveTimeout.usec;

    /* Initialize exit thread boolean. */
    DSM_DATA_PROCEDURES(dataObj).exitThread = ITS_FALSE;

    /* Create and start procedures thread. */
    ret = THREAD_CreateThread(
            &DSM_DATA_PROCEDURES(dataObj).thread,
            0,
            ProceduresThread,
            (void*)dataObj,
            ITS_TRUE);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProceduresCreate [FtGroupId: %u]: THREAD_CreateThread failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ITS_TRACE_DEBUG(("$$$$ INITIALIAING DATA_STACK_MULTICAST_QUEUE $$$$\n"));
    if ((DSM_DATA_STACK_MULTICAST_QUEUE(dataObj) = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("** FAIL TO CREATE GCS_STACK_MESSAGE_QUEUE TRANSPORT **\n"));
        ITS_TRACE_ERROR(("ProceduresCreate [FtGroupId: %u]:" 
                         "TQUEUETRAN_CreateTransport failed\n",
                         DSM_DATA_FT_GROUP_ID(dataObj)));

        return ITS_ENOMEM;
        
    }
    ITS_TRACE_DEBUG(("$$$$ dataObj = 0x%x MList = 0x%x $$$$\n",
                     dataObj, DSM_DATA_STACK_MULTICAST_QUEUE(dataObj)));

    ITS_TRACE_DEBUG(("$$$$ INITIALIAING DATA_APPL_MULTICAST_QUEUE $$$$\n"));
    if ((DSM_DATA_APPL_MULTICAST_QUEUE(dataObj) = MLIST_Create()) == NULL)
    {
        ITS_TRACE_ERROR(("** FAIL TO CREATE GCS_APPL_MESSAGE_QUEUE TRANSPORT **\n"));
        ITS_TRACE_ERROR((
           "ProceduresCreate [FtGroupId: %u]:" 
           "TQUEUETRAN_CreateTransport failed\n",
           DSM_DATA_FT_GROUP_ID(dataObj)));

        return ITS_ENOMEM;
        
    }
    ITS_TRACE_DEBUG(("$$$$ dataObj = 0x%x MList = 0x%x $$$$\n",
                     dataObj, DSM_DATA_APPL_MULTICAST_QUEUE(dataObj)));

#if 0
    cbManager = DSM_GetMembershipChangeCallbacks(DSM_IsupFtGroupId);
    if (cbManager == NULL)
    {
        return ITS_ENOMEM;
    }
    ret = CALLBACK_AddCallback(cbManager, 
                               BroadCastEventNotificationCallback, 
                               NULL);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOMEM;
    }
#endif

    return ITS_SUCCESS;
}

static int
ProceduresDestroy(
    DSM_DataObject* dataObj)
{
    int ret;
    void* status = NULL;

    ITS_C_REQUIRE(dataObj != NULL);

    /* Terminate procedures thread. */
    DSM_DATA_PROCEDURES(dataObj).exitThread = ITS_TRUE;

    /* Wait for procedures thread to terminate. */
    ret = THREAD_WaitForThread(&DSM_DATA_PROCEDURES(dataObj).thread, &status);
    if (ret == ITS_SUCCESS)
    {
        ITS_TRACE_DEBUG((
            "ProceduresDestroy [FtGroupId: %u]: procedures thread successfully"
            " terminated\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_ERROR((
            "ProceduresDestroy [FtGroupId: %u]: THREAD_WaitForThread failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    return ITS_SUCCESS;
}

static int
MemDataCreate(
    DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    void* ptr;
    ITS_Object object;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    /*
     *  Create shared memory data (mmap on Unix, VirtualAlloc on W2K/NT).
     */

#if defined(WIN32)

    ptr = VirtualAlloc(
#if defined(WIN32)
                NULL,
#else
                (void*)DSM_INST_DSM_BASE_ADDRESS(instObj),
#endif
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

        return ITS_ENOMEM;
    }

    ITS_TRACE_DEBUG((
        "MemDataCreate [FtGroupId: %u]: VirtualAlloc succeeded: %u bytes at "
        "address 0x%X\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_INST_DSM_SIZE(instObj),
        ptr));

    DSM_DATA_SYS_MAP_ADDR(dataObj) = ptr;

#else /* !defined(WIN32) */

    ptr = MMAP(
            (char*)DSM_INST_DSM_BASE_ADDRESS(instObj), 
            DSM_INST_DSM_SIZE(instObj),
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_FIXED);
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
        return ITS_ENOMEM;
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

    /*
     * NOTE: Chicken/egg problem (again).  The HASH allocator is called
     * from the superclass, so the member variable for the object pointer
     * needs to be set first.  This is because the object is constructed
     * in super to sub order.
     */
    DSMHASH_DATA_OBJECT(DSM_DATA_MEM_DATA(dataObj)->tables) = dataObj;
    object = ITS_ConstructObjectIn(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        itsDSMHASH_Class,
                        dataObj);
    if (object == NULL)
    {
        return ITS_ENOMEM;
    }

    /* 
     * Dsm info related. 
     */

    DSM_DATA_DSM_INFO(dataObj).lock.counter = 0;
    DSM_DATA_DSM_INFO(dataObj).lock.threadId = 0;
    memset(
        DSM_DATA_DSM_INFO(dataObj).lock.memberName,
        0,
        GCS_MAX_GROUP_NAME * sizeof(char));

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

    ret = MUTEX_CreateMutex(&DSM_DATA_TABLES_LOCK(dataObj), 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "MemDataCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /*
     * Procedure Manager related.
     */
    DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = NULL;
    DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = NULL;
    DSM_DATA_PROCEDURE_MANAGER(dataObj).count    = 0;
    ITS_TRACE_ERROR(("MemDataCreate:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    ITS_TRACE_ERROR(("MemDataCreate::   GOING TO CREATE LOCAL HASH\n"));
    TablesCreate(coreObj,instObj,dataObj);
    ITS_TRACE_ERROR(("MemDataCreate::   FINISH  LOCAL HASH\n"));
    return ITS_SUCCESS;
}

static int
MemDataDestroy(
    DSM_DataObject* dataObj)
{
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_C_REQUIRE(dataObj != NULL);

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

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
            return ITS_EBADMEMFREE;
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
            return ITS_EBADMEMFREE;
        }

        ITS_TRACE_DEBUG((
            "MemDataDestroy [FtGroupId: %u]: munmap succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

#endif /* defined(WIN32) */

    return ITS_SUCCESS;
}

static int
StateDataCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

    ret = MUTEX_CreateMutex(&DSM_DATA_STATE_DATA(dataObj).lock, 0);

    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "StateDataCreate [FtGroupId: %u]: MUTEX_CreateMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
StateDataDestroy(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INVALID;

    MUTEX_DeleteMutex(&DSM_DATA_STATE_DATA(dataObj).lock);

    return ITS_SUCCESS;
}

static int
JoinDataCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    DSM_DATA_JOIN_DATA(dataObj).selfTimeout = 
        DSM_DATA_CONFIG(dataObj).selfJoinTimeout;

    ret = SEMA_CreateSemaphore(&DSM_DATA_JOIN_DATA(dataObj).selfSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "JoinDataCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    DSM_DATA_JOIN_DATA(dataObj).masterTimeout = 
        DSM_DATA_CONFIG(dataObj).masterJoinTimeout;

    ret = SEMA_CreateSemaphore(&DSM_DATA_JOIN_DATA(dataObj).masterSema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "JoinDataCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int
JoinDataDestroy(
    DSM_DataObject* dataObj)
{
    SEMA_DeleteSemaphore(&DSM_DATA_JOIN_DATA(dataObj).selfSema);
    SEMA_DeleteSemaphore(&DSM_DATA_JOIN_DATA(dataObj).masterSema);
    return ITS_SUCCESS;
}

static int
SyncDataCreate(
    DSM_DataObject* dataObj)
{
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
        0, 
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
        0, 
        GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpAddress,
        0,
        DSM_MAX_IP_ADDRESS_SIZE * sizeof(char));

    ITS_C_ASSERT(!(DSM_DATA_CONFIG(dataObj).syncMemUseTcp && 
                  DSM_DATA_CONFIG(dataObj).syncMemUseGcs));

    DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp = 
        DSM_DATA_CONFIG(dataObj).syncMemUseTcp;
    DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs = 
        DSM_DATA_CONFIG(dataObj).syncMemUseGcs;

    ITS_C_ASSERT(strlen(DSM_DATA_CONFIG(dataObj).syncMemIpAddress) < 
        DSM_MAX_IP_ADDRESS_SIZE);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpAddress, 
        DSM_DATA_CONFIG(dataObj).syncMemIpAddress);

    DSM_DATA_SYNC_DATA(dataObj).syncMemIpPort = 
        DSM_DATA_CONFIG(dataObj).syncMemIpPort;
    DSM_DATA_SYNC_DATA(dataObj).syncMemTimeout = 
        DSM_DATA_CONFIG(dataObj).syncMemTimeout;
    DSM_DATA_SYNC_DATA(dataObj).syncMemConnectTimeout = 
        DSM_DATA_CONFIG(dataObj).syncMemConnectTimeout;

    ret = RWLOCK_CreateLock(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "SyncDataCreate [FtGroupId: %u]: RWLOCK_CreateLock failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = SEMA_CreateSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema, 0);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "SyncDataCreate [FtGroupId: %u]: SEMA_CreateSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_DeleteLock(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
        return ret;
    }

    DSM_DATA_SYNC_DATA(dataObj).procedureQueue = LIST_Create();
    if (DSM_DATA_SYNC_DATA(dataObj).procedureQueue == NULL)
    {
        ITS_TRACE_ERROR((
            "SyncDataCreate [FtGroupId: %u]: LIST_Create failed\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        RWLOCK_DeleteLock(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
        SEMA_DeleteSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
        return ITS_ENOMEM;
    }

    DSM_DATA_SYNC_DATA(dataObj).lastSeq = 0;

    DSM_DATA_SYNC_DATA(dataObj).sockListen = NULL;
    DSM_DATA_SYNC_DATA(dataObj).sockServer = NULL;
    DSM_DATA_SYNC_DATA(dataObj).sockClient = NULL;

    if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp)
    {
        ret = THREAD_CreateThread(
                &DSM_DATA_SYNC_DATA(dataObj).thread,
                0,
                SyncMemTcpListenThread,
                (void*)dataObj,
                ITS_TRUE);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "SyncDataCreate [FtGroupId: %u]: THREAD_CreateThread failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            RWLOCK_DeleteLock(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
            SEMA_DeleteSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
            LIST_Delete(DSM_DATA_SYNC_DATA(dataObj).procedureQueue);
            return ret;
        }
    }

    DSM_DATA_SYNC_DATA(dataObj).exitThread = ITS_FALSE;
    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState = DSM_STATE_INVALID;

    return ITS_SUCCESS;
}

static int
SyncDataDestroy(
    DSM_DataObject* dataObj)
{
    DSM_Procedure** procedure;
    int len;
    int ret;
    void* status = NULL;
    
    RWLOCK_DeleteLock(&DSM_DATA_SYNC_DATA(dataObj).rwLock);

    SEMA_DeleteSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);

    /* Cleanup procedure queue if not empty. */
    while (!LIST_EmptyP(DSM_DATA_SYNC_DATA(dataObj).procedureQueue))
    {
        ret = LIST_RemTail(
                DSM_DATA_SYNC_DATA(dataObj).procedureQueue,
                (void**)&procedure,
                &len);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "SyncDataDestroy [FtGroupId: %u]: LIST_RemTail failed\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            return ret;
        }

        ITS_C_ASSERT(len = sizeof(DSM_Procedure*));
        ITS_C_ASSERT(*procedure != NULL);

        free(*procedure);
        free(procedure);
    }

    LIST_Delete(DSM_DATA_SYNC_DATA(dataObj).procedureQueue);

    if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp)
    {
        /* Terminate SYNC MEM TCP Listen thread. */
        DSM_DATA_SYNC_DATA(dataObj).exitThread = ITS_TRUE;
        SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockListen);

        /* Wait for SYNC MEM TCP thread to terminate. */
        ret = THREAD_WaitForThread(
                &DSM_DATA_SYNC_DATA(dataObj).thread, 
                &status);
        if (ret == ITS_SUCCESS)
        {
            ITS_TRACE_DEBUG((
                "SyncDataDestroy [FtGroupId: %u]: SYNC MEM TCP Listen thread "
                "successfully terminated\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
        else
        {
            ITS_TRACE_ERROR((
                "SyncDataDestroy [FtGroupId: %u]: THREAD_WaitForThread failed:"
                " %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        }

        if (DSM_DATA_SYNC_DATA(dataObj).sockClient != NULL)
        {
            SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockClient);
            DSM_DATA_SYNC_DATA(dataObj).sockClient = NULL;
        }
    }

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

        tcb->tid = 0;
        tcb->next = NULL;
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
 *  Remote members related.
 */

static ITS_BOOLEAN
HasRemoteMember(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    int i;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (DSM_DATA_REMOTES(dataObj).members[i].valid)
        {
            if (strcmp(
                    DSM_DATA_REMOTES(dataObj).members[i].memberName, 
                    memberName) == 0)
            {
                return ITS_TRUE;
            }
        }
    }

    return ITS_FALSE;
}

static ITS_UINT
RemoteMemberSize(
    DSM_DataObject* dataObj)
{
    int i;
    ITS_UINT result = 0;

    ITS_C_REQUIRE(dataObj != NULL);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (DSM_DATA_REMOTES(dataObj).members[i].valid)
        {
            result++;
        }
    }

    return result;
}

static DSM_RemoteMember* 
RemoteMemberInsert(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    int i;
    DSM_RemoteMember* result = NULL;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(!HasRemoteMember(dataObj, memberName));
    ITS_C_REQUIRE(RemoteMemberSize(dataObj) < DSM_MAX_REMOTE_MEMBERS);
    ITS_C_REQUIRE(strlen(memberName) < GCS_MAX_GROUP_NAME);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (!DSM_DATA_REMOTES(dataObj).members[i].valid)
        {
            DSM_DATA_REMOTES(dataObj).members[i].valid = ITS_TRUE;
            strcpy(
                DSM_DATA_REMOTES(dataObj).members[i].memberName, 
                memberName);
            result = &DSM_DATA_REMOTES(dataObj).members[i];
            break;
        }
    }

    ITS_C_ENSURE(result != NULL);
    return result;
}

static void
RemoteMemberRemove(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    int i;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(HasRemoteMember(dataObj, memberName));

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (strcmp(
                DSM_DATA_REMOTES(dataObj).members[i].memberName,
                memberName) == 0)
        {
            DSM_DATA_REMOTES(dataObj).members[i].valid                  = 
                ITS_FALSE;
            DSM_DATA_REMOTES(dataObj).members[i].memberName[0]          = 
                '\0';
            DSM_DATA_REMOTES(dataObj).members[i].syncMemIpAddress[0]    = 
                '\0';
            DSM_DATA_REMOTES(dataObj).members[i].syncMemIpPort          = 
                4804;
            DSM_DATA_REMOTES(dataObj).members[i].nodeId                 = 
                DSM_INVALID_NODE_ID;
            DSM_DATA_REMOTES(dataObj).members[i].processId              = 
                DSM_INVALID_PROCESS_ID;
            DSM_DATA_REMOTES(dataObj).members[i].lastKnownState         = 
                DSM_STATE_INVALID;
            break;
        }
    }
}

static DSM_RemoteMember*
RemoteMemberRetrieve(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    int i; 
    DSM_RemoteMember* result = NULL;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (strcmp(
                DSM_DATA_REMOTES(dataObj).members[i].memberName,
                memberName) == 0)
        {
            result = &DSM_DATA_REMOTES(dataObj).members[i];
            break;
        }
    }

    return result;
}

static DSM_RemoteMember*
RemoteMemberRetrieveFirstValid(
    DSM_DataObject* dataObj)
{
    DSM_RemoteMember* result = NULL;
    int i;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(RemoteMemberSize(dataObj) > 0);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (DSM_DATA_REMOTES(dataObj).members[i].valid)
        {
            result = &DSM_DATA_REMOTES(dataObj).members[i];
            break;
        }
    }

    ITS_C_ENSURE(result != NULL);
    return result;
}

static DSM_RemoteMember*
RemoteMemberRetrieveFirstValidMaster(
    DSM_DataObject* dataObj)
{
    DSM_RemoteMember* masterRemoteMember;
    DSM_InstObject* instObj;
    ITS_USHORT nodeId;
    ITS_USHORT processId;
    int i, j;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(RemoteMemberSize(dataObj) > 0);

    instObj = DSM_DATA_INST_OBJECT(dataObj);

    for (i = 0; i < DSM_INST_NUM_MASTER_FT_GROUP_MEMBERS(instObj); i++)
    {
        nodeId = DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj)[i].nodeId;
        processId = DSM_INST_MASTER_FT_GROUP_MEMBERS(instObj)[i].processId;

        for (j = 0; j < DSM_MAX_REMOTE_MEMBERS; j++)
        {
            masterRemoteMember = &DSM_DATA_REMOTES(dataObj).members[i];

            if (masterRemoteMember->valid && 
                IsDsmStateNormal(masterRemoteMember->lastKnownState))
            { 
                return masterRemoteMember;
            }
        }
    }

    return NULL;
}

static void
RemoteMemberClear(
    DSM_DataObject* dataObj)
{
    int i;

    ITS_C_REQUIRE(dataObj != NULL);

    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        DSM_DATA_REMOTES(dataObj).members[i].valid                  = 
            ITS_FALSE;
        DSM_DATA_REMOTES(dataObj).members[i].memberName[0]          = 
            '\0';
        DSM_DATA_REMOTES(dataObj).members[i].syncMemIpAddress[0]    = 
            '\0';
        DSM_DATA_REMOTES(dataObj).members[i].syncMemIpPort          = 
            4804;
        DSM_DATA_REMOTES(dataObj).members[i].nodeId                 = 
            DSM_INVALID_NODE_ID;
        DSM_DATA_REMOTES(dataObj).members[i].processId              = 
            DSM_INVALID_PROCESS_ID;
        DSM_DATA_REMOTES(dataObj).members[i].lastKnownState         = 
            DSM_STATE_INVALID;
    }
}

static void
MemberNameToNodeProcessFtGroupIds(
    DSM_DataObject* dataObj,
    const char* memberName,
    ITS_USHORT* nodeId,
    ITS_USHORT* processId,
    ITS_USHORT* ftGroupId)
{
    const char* connectionNameRoot;
    char* ptr;
    unsigned int u1, u2, u3;
    int ret;

    /* 
     * MemberName format is "#s1-u1-u2-u3#s2" where:
     * '#'                  = number sign character.
     * s1 (string)          = DSM_GCS_CONNECTION_NAME_ROOT_STRING.
     * '-'                  = dash character.
     * u1 (unsigned int)    = nodeId.
     * '-'                  = dash character.
     * u2 (unsigned int)    = processId.
     * '-'                  = dash character.
     * u3 (unsigned int)    = ftGroupId.
     * '#'                  = number sign character.
     * s2 (string)          = IP associated name (in configuration).
     */

    if (nodeId != NULL)
    {
        *nodeId = DSM_INVALID_NODE_ID;
    }

    if (processId != NULL)
    {
        *processId = DSM_INVALID_PROCESS_ID;
    }

    if (ftGroupId != NULL)
    {
        *ftGroupId = DSM_INVALID_FT_GROUP_ID;
    }

    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(strlen(memberName) > 0);

    /* Initialize connectionNameRoot (constant). */
    connectionNameRoot = DSM_DATA_CONFIG(dataObj).connectionNameRoot;

    /* Find connectionNameRoot substring. */
    ptr = strstr(memberName, connectionNameRoot);
    if (ptr == NULL || strlen(ptr) == 0)
    {
        return;
    }

    ptr += strlen(connectionNameRoot);

    /* Find first '-' (nodeId marker). */ 
    ptr = strstr(ptr, "-");
    if (ptr == NULL || strlen(ptr) == 0)
    {
        return;
    }

    ITS_C_ASSERT(*ptr == '-');

    if (strlen(++ptr) == 0)
    {
        return;
    }

    /* Retrieve nodeId. */
    ret = sscanf(ptr, "%u", &u1);
    if (ret != 1)
    {
        return;
    }

    if (nodeId != NULL)
    {
        *nodeId = (ITS_USHORT)u1;
    }

    /* Find second '-' (processId marker). */ 
    ptr = strstr(ptr, "-");
    if (ptr == NULL || strlen(ptr) == 0)
    {
        return;
    }

    ITS_C_ASSERT(*ptr == '-');

    if (strlen(++ptr) == 0)
    {
        return;
    }

    /* Retrieve processId. */
    ret = sscanf(ptr, "%u", &u2);
    if (ret != 1)
    {
        return;
    }

    if (processId != NULL)
    {
        *processId = (ITS_USHORT)u2;
    }

    /* Find third '-' (ftGroupId marker). */ 
    ptr = strstr(ptr, "-");
    if (ptr == NULL || strlen(ptr) == 0)
    {
        return;
    }

    ITS_C_ASSERT(*ptr == '-');

    if (strlen(++ptr) == 0)
    {
        return;
    }

    /* Retrieve ftGroupId. */
    ret = sscanf(ptr, "%u", &u3);
    if (ret != 1)
    {
        return;
    }

    if (ftGroupId != NULL)
    {
        *ftGroupId = (ITS_USHORT)u3;
    }
}

static ITS_USHORT
MemberNameToNodeId(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    ITS_USHORT nodeId = DSM_INVALID_NODE_ID;

    MemberNameToNodeProcessFtGroupIds(
        dataObj, 
        memberName, 
        &nodeId, 
        NULL, 
        NULL);

    return nodeId;
}

static ITS_USHORT
MemberNameToProcessId(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    ITS_USHORT processId = DSM_INVALID_PROCESS_ID;

    MemberNameToNodeProcessFtGroupIds(
        dataObj, 
        memberName, 
        NULL, 
        &processId, 
        NULL);

    return processId;
}

static ITS_USHORT
MemberNameToFtGroupId(
    DSM_DataObject* dataObj, 
    const char* memberName)
{
    ITS_USHORT ftGroupId = DSM_INVALID_FT_GROUP_ID;

    MemberNameToNodeProcessFtGroupIds(
        dataObj, 
        memberName, 
        NULL, 
        NULL, 
        &ftGroupId);

    return ftGroupId;
}

/*
 * Distributed Lock related.
 */

static ITS_BOOLEAN
DistributedLockIsLocked(
    DSM_DistributedLock* lock)
{
    ITS_C_REQUIRE(lock != NULL);

    if (lock->counter > 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
DistributedLockIsLockedByMember(
    DSM_DistributedLock* lock,
    const char* memberName)
{
    ITS_C_REQUIRE(lock != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    if (strcmp(lock->memberName, memberName) == 0 && lock->counter > 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
DistributedLockIsLockedByThread(
    DSM_DistributedLock* lock,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(lock != NULL);

    if (lock->threadId == threadId && lock->counter > 0)
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
DistributedLockIsLockedNotByMember(
    DSM_DistributedLock* lock,
    const char* memberName)
{
    if (strcmp(lock->memberName, memberName) != 0 && lock->counter > 0)
    {
       /* printf("DistributedLockIsLockedNotByMember: name = %s lockthr %d lockname = %s counter = %d\n",
                memberName, lock->threadId, lock->memberName, lock->counter);*/

        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static ITS_BOOLEAN
DistributedLockIsLockedNotByThread(
    DSM_DistributedLock* lock,
    ITS_UINT threadId)
{
    if (lock->threadId != threadId  && lock->counter > 0)
    {
        /*printf("DistributedLockIsLockedNotByThread: thrid %d, lockthrid %d, lockconter %d\n", threadId, lock->threadId, lock->counter);*/
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}

static void
DistributedLockLock(
    DSM_DistributedLock* lock,
    const char* memberName,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(lock != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(!DistributedLockIsLockedNotByMember(lock, memberName));
    ITS_C_REQUIRE(!DistributedLockIsLockedNotByThread(lock, threadId));

    if (strcmp(lock->memberName, memberName) == 0 && 
        lock->threadId == threadId)
    {
        lock->counter++;
    }
    else
    {
        memcpy(
            lock->memberName,
            memberName,
            GCS_MAX_GROUP_NAME);

        lock->threadId = threadId;

        lock->counter++;
    }
}

static void
DistributedLockUnlock(
    DSM_DistributedLock* lock,
    const char* memberName,
    ITS_UINT threadId)
{    
    ITS_C_REQUIRE(lock != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(DistributedLockIsLockedByMember(lock, memberName));
    ITS_C_REQUIRE(DistributedLockIsLockedByThread(lock, threadId));
    
    lock->counter--;

    if (lock->counter == 0)
    {
        memset(
            lock->memberName,
            0,
            GCS_MAX_GROUP_NAME);

        lock->threadId = 0;
    }
}

static void
DistributedLockUnlockIfLockedByMember(
    DSM_DistributedLock* lock,
    const char* memberName)
{
    ITS_C_REQUIRE(lock != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    
    if (DistributedLockIsLockedByMember(lock, memberName))
    {
        lock->counter--;

        if (lock->counter == 0)
        {
            memset(
                lock->memberName,
                0,
                GCS_MAX_GROUP_NAME);

            lock->threadId = 0;
        }
    }
}

static ITS_UINT
DistributedLockGetLockCount(
    DSM_DistributedLock* lock)
{    
    ITS_C_REQUIRE(lock != NULL);

    return lock->counter;
}

/* 
 * Dsm and Tables Lock related.
 */

static ITS_BOOLEAN
DsmIsLocked(
    DSM_DataObject* dataObj)
{
    ITS_C_REQUIRE(dataObj != NULL);

    return DistributedLockIsLocked(
                &DSM_DATA_DSM_INFO(dataObj).lock);
}

static ITS_BOOLEAN
DsmIsLockedByMember(
    DSM_DataObject* dataObj,
    const char* memberName)
{
    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    return DistributedLockIsLockedByMember(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                memberName);
}

static ITS_BOOLEAN
DsmIsLockedByThread(
    DSM_DataObject* dataObj,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(dataObj != NULL);

    return DistributedLockIsLockedByThread(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                threadId);
}

static ITS_BOOLEAN
DsmIsLockedNotByMember(
    DSM_DataObject* dataObj,
    const char* memberName)
{
    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    return DistributedLockIsLockedNotByMember(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                memberName);
}

static ITS_BOOLEAN
DsmIsLockedNotByThread(
    DSM_DataObject* dataObj,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(dataObj != NULL);

    return DistributedLockIsLockedNotByThread(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                threadId);
}

static int
DsmLock(
    DSM_DataObject* dataObj, 
    const char* memberName,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(!DsmIsLockedNotByMember(dataObj, memberName));
    ITS_C_REQUIRE(!DsmIsLockedNotByThread(dataObj, threadId));

    DistributedLockLock(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                memberName,
                threadId);

    return ITS_SUCCESS;
}

static int
DsmUnlock(
    DSM_DataObject* dataObj, 
    const char* memberName,
    ITS_UINT threadId)
{
    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(DsmIsLockedByMember(dataObj, memberName));
    ITS_C_REQUIRE(DsmIsLockedByThread(dataObj, threadId));

    DistributedLockUnlock(
                &DSM_DATA_DSM_INFO(dataObj).lock,
                memberName,
                threadId);

    return ITS_SUCCESS;
}

static void
DsmUnlockFullIfLockedByMember(
    DSM_DataObject* dataObj,
    const char* memberName)
{
    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    if (DsmIsLockedByMember(dataObj, memberName))
    {
        size_t i;

        ITS_UINT count = 
            DistributedLockGetLockCount(
                &DSM_DATA_DSM_INFO(dataObj).lock);

        for (i = 0; i < count; i++)
        {
            DistributedLockUnlockIfLockedByMember(
                &DSM_DATA_DSM_INFO(dataObj).lock, 
                memberName);
        }
    }
}

static ITS_BOOLEAN
TableIsLocked(
    DSM_DataObject* dataObj,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));

    return DistributedLockIsLocked(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);
}

static ITS_BOOLEAN
TableIsLockedByMember(
    DSM_DataObject* dataObj,
    const char* memberName,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));

    return DistributedLockIsLockedByMember(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                memberName);
}

static ITS_BOOLEAN
TableIsLockedByThread(
    DSM_DataObject* dataObj,
    ITS_UINT threadId,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));

    return DistributedLockIsLockedByThread(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                threadId);
}

static ITS_BOOLEAN
TableIsLockedNotByMember(
    DSM_DataObject* dataObj,
    const char* memberName,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));

    return DistributedLockIsLockedNotByMember(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                memberName);
}

static ITS_BOOLEAN
TableIsLockedNotByThread(
    DSM_DataObject* dataObj,
    ITS_UINT threadId,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));

    return DistributedLockIsLockedNotByThread(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                threadId);
}

static int
TableLock(
    DSM_DataObject* dataObj, 
    const char* memberName,
    ITS_UINT threadId,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));
    ITS_C_REQUIRE(!TableIsLockedNotByMember(dataObj, memberName, tableId));
    ITS_C_REQUIRE(!TableIsLockedNotByThread(dataObj, threadId, tableId));

    DistributedLockLock(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                memberName,
                threadId);

    return ITS_SUCCESS;
}

static int
TableUnlock(
    DSM_DataObject* dataObj, 
    const char* memberName,
    ITS_UINT threadId,
    ITS_UINT tableId)
{
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);
    ITS_C_REQUIRE(tableId < DSM_INST_MAX_NUM_TABLES(instObj));
    ITS_C_REQUIRE(TableIsLockedByMember(dataObj, memberName, tableId));
    ITS_C_REQUIRE(TableIsLockedByThread(dataObj, threadId, tableId));

    DistributedLockUnlock(
                &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock,
                memberName,
                threadId);

    return ITS_SUCCESS;
}

static void
TablesUnlockFullIfLockedByMember(
    DSM_DataObject* dataObj,
    const char* memberName)
{
    ITS_UINT tableId;
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(memberName != NULL);

    for (tableId = 1; tableId < DSM_INST_MAX_NUM_TABLES(instObj); tableId++)
    {
        if (TableIsLockedByMember(dataObj, memberName, tableId))
        {
            size_t i;

            ITS_UINT count = 
                DistributedLockGetLockCount(
                    &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock);

            for (i = 0; i < count; i++)
            {
                DistributedLockUnlockIfLockedByMember(
                    &DSM_DATA_TABLES_INFO(dataObj)[tableId].lock, 
                    memberName);
            }
        }
    }
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


    /* Check maximum Fault Tolerance Group members (i.e. processes). */
    if (DSM_CORE_MAX_NUM_PROCESSES(coreObj) > DSM_MAX_MEMBERS)
    {
        /* TODO: add trace. */
        return ITS_EINVCONFIG;
    }

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

    /* Local Member create. */
    ret = LocalMemberCreate(dataObj, ftGroupId);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: LocalMemberCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Remote Members create. */
    ret = RemoteMembersCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: RemoteMembersCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        LocalMemberDestroy(dataObj);
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
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
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
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
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
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
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
        /* TODO: review (blocking call...). */
        /* SyncDataDestroy(dataObj);*/
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* GCS Daemon Connection create. */
    ret = GcsDaemonConnectionCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: GcsDaemonConnectionCreate "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MemDataDestroy(dataObj);
        /* TODO: review (blocking call...). */
        /* SyncDataDestroy(dataObj);*/
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
        TcbManagerDestroy(dataObj);
        TidAllocatorDestroy(dataObj);
        ConfigDestroy(dataObj);
        return ret;
    }

    /* Procedures create (MUST BE created last). */
    ret = ProceduresCreate(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataCreateInstance [FtGroupId: %u]: ProceduresCreate failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        GcsDaemonConnectionDestroy(dataObj);
        MemDataDestroy(dataObj);
        /* TODO: review (blocking call...). */
        /* SyncDataDestroy(dataObj);*/
        JoinDataDestroy(dataObj);
        StateDataDestroy(dataObj);
        RemoteMembersDestroy(dataObj);
        LocalMemberDestroy(dataObj);
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

    /* Procedures destroy (MUST BE destroyed first). */
    ret = ProceduresDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: ProceduresDestroy failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /*
     *  TODO: at this point, must ensure that there are no more ongoing calls
     *  of DSM_* public functions (owned by other threads than DSM Procedures).
     *  How?
     */

    /* GCS Daemon Connection destroy. */
    ret = GcsDaemonConnectionDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: GcsDaemonConnectionDestroy "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
    }

    /* Mem Data destroy. */
    ret = MemDataDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: MemDataDestroy failed: %d\n",
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

    /* Remote Members destroy. */
    ret = RemoteMembersDestroy(dataObj);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DataDestroyInstance [FtGroupId: %u]: RemoteMembersDestroy failed:"
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

/*
 * SynchronizeDsm. Can be used either for explicit synchronization (state SYNC
 * WAIT) or forced synchronization (state NORMAL). Return ITS_ENOVALIDMASTER if
 * no master member in NORMAL state available.
 */
static int
SynchronizeDsm(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT msecs)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_Message syncRequestMsg;
    DSM_RemoteMember* masterRemoteMember;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);

    /* TODO: review: only one call at a time should be allowed. */

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Drain SYNC semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema) == 
        ITS_SUCCESS)
    {
    }

    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "SynchronizeDsm [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    if (RemoteMemberSize(dataObj) == 0)
    {
        ITS_TRACE_DEBUG((
            "SynchronizeDsm [FtGroupId: %u]: failed to find a remote member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_ENOREMOTE;
    }

    masterRemoteMember = RemoteMemberRetrieveFirstValidMaster(dataObj);
    if (masterRemoteMember == NULL)
    {
        ITS_TRACE_DEBUG((
            "SynchronizeDsm [FtGroupId: %u]: failed to find a master remote "
            "member in NORMAL state\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_ENOVALIDMASTER;
    }

    /*
     * Send DSM SYNC REQUEST message.
     */

    syncRequestMsg.discriminator = DSM_MSG_SYNC_REQUEST;
    syncRequestMsg.u.syncRequest.tid = AllocateTid(dataObj);
    strcpy(
        syncRequestMsg.u.syncRequest.syncMasterMemberName,
        masterRemoteMember->memberName);
    strcpy(
        syncRequestMsg.u.syncRequest.syncSlaveMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);

    ITS_TRACE_DEBUG((
        "SynchronizeDsm [FtGroupId: %u]: ready to send DSM SYNC REQUEST "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncRequestMsg.u.syncRequest.tid,
        syncRequestMsg.u.syncRequest.syncSlaveMemberName,
        syncRequestMsg.u.syncRequest.syncMasterMemberName));

    ret = GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_SYNC_LOCK,
            sizeof(DSM_Message),
            (const char*)&syncRequestMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "SynchronizeDsm [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ITS_EGCSMULTICASTFAIL; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "SynchronizeDsm [FtGroupId: %u]: DSM SYNC REQUESt message successfully"
        " sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Wait for SYNC semaphore to be posted. */

    ret = SEMA_WaitSemaphoreWithTimeOut(
                    &DSM_DATA_SYNC_DATA(dataObj).sema,
                    msecs);
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        ITS_TRACE_ERROR((
            "SynchronizeDsm [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        ITS_TRACE_DEBUG((
            "SynchronizeDsm [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_ERROR((
            "SynchronizeDsm [FtGroupId: %u]: failed due to timeout\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ret;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "SynchronizeDsm [FtGroupId: %u]: succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }

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
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_C_ASSERT(IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state));

    /* Drain SELF-JOIN semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_JOIN_DATA(dataObj).selfSema) == 
        ITS_SUCCESS)
    {
    }

    /* Drain MASTER-JOIN semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_JOIN_DATA(dataObj).masterSema) == 
        ITS_SUCCESS)
    {
    }

    /* Drain SYNC semaphore. */
    while (SEMA_TryWaitSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema) == 
        ITS_SUCCESS)
    {
    }

    /* Join DSM Fault Tolerance Group. */
    ret = GCS_Join(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            DSM_DATA_LOCAL(dataObj).groupName);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "JoinFtGroup [FtGroupId: %u]: GCS_Join failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to join DSM Fault Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_EGCSJOINFAIL;
    }

    ITS_TRACE_DEBUG((
        "JoinFtGroup [FtGroupId: %u]: GCS_Join succeeded\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* 
     * Wait for SELF-JOIN semaphore to be posted (by SELF-JOIN membership
     * message).
     */

    ret = SEMA_WaitSemaphoreWithTimeOut(
                    &DSM_DATA_JOIN_DATA(dataObj).selfSema,
                    DSM_DATA_JOIN_DATA(dataObj).selfTimeout);
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        ITS_TRACE_ERROR((
            "JoinFtGroup (SELF) [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut"
            " failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        /* Leave DSM Fault Tolerance Group (ignore errors). */
        GCS_Leave(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            DSM_DATA_LOCAL(dataObj).groupName);
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup (SELF) [FtGroupId: %u]: SEMA_WaitSemaphoreWithTimeOut"
            " failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to receive SELF-JOIN membership message. "
            "Is GCS Deamon still running?\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        /* Leave DSM Fault Tolerance Group (ignore errors). */
        GCS_Leave(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            DSM_DATA_LOCAL(dataObj).groupName);
        return ret;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup [FtGroupId: %u]: SELF-JOIN succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        /* Continue with following step (MASTER-JOIN). */
    }

    ITS_C_ASSERT(
        IsDsmStateJoining(DSM_DATA_STATE_DATA(dataObj).state)   ||
        IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state)    ||
        IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state)  ||
        IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state));

    /* 
     * Wait for MASTER-JOIN semaphore to be posted (either first member to join
     * or receive DSM JOIN INFO message from a master remote member in NORMAL
     * state).
     */

    ret = SEMA_WaitSemaphoreWithTimeOut(
                    &DSM_DATA_JOIN_DATA(dataObj).masterSema, 
                    DSM_DATA_JOIN_DATA(dataObj).masterTimeout);
    if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
    {
        ITS_TRACE_ERROR((
            "JoinFtGroup (MASTER) [FtGroupId: %u]: "
            "SEMA_WaitSemaphoreWithTimeOut failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        /* Leave DSM Fault Tolerance Group (ignore errors). */
        GCS_Leave(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            DSM_DATA_LOCAL(dataObj).groupName);
        return ret;
    }
    else if (ret == ITS_ETIMEOUT)
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup (MASTER) [FtGroupId: %u]: "
            "SEMA_WaitSemaphoreWithTimeOut timed out\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to receive DSM JOIN INFO message(s). "
            "Is GCS Deamon still running?\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        /* Leave DSM Fault Tolerance Group (ignore errors). */
        GCS_Leave(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            DSM_DATA_LOCAL(dataObj).groupName);
        return ret;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "JoinFtGroup [FtGroupId: %u]: MASTER-JOIN succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        /* Continue with following step (SYNC, if required). */
    }

    ITS_C_ASSERT(
        IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state)    ||
        IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state)  ||
        IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state));

    /* 
     * Wait for SYNC semaphore to be posted (unless explicit synchronization).
     */

    if (!DSM_INST_DSM_SYNC_EXPLICIT(instObj))
    {
        ret = SEMA_WaitSemaphoreWithTimeOut(
                        &DSM_DATA_SYNC_DATA(dataObj).sema,
                        DSM_INST_DSM_JOIN_FT_GROUP_TIMEOUT(instObj));
        if (ret != ITS_SUCCESS && ret != ITS_ETIMEOUT)
        {
            ITS_TRACE_ERROR((
                "JoinFtGroup (SYNC) [FtGroupId: %u]: "
                "SEMA_WaitSemaphoreWithTimeOut failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            /* Leave DSM Fault Tolerance Group (ignore errors). */
            GCS_Leave(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                DSM_DATA_LOCAL(dataObj).groupName);
            return ret;
        }
        else if (ret == ITS_ETIMEOUT)
        {
            ITS_TRACE_DEBUG((
                "JoinFtGroup (SYNC) [FtGroupId: %u]: "
                "SEMA_WaitSemaphoreWithTimeOut failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            ITS_TRACE_ERROR((
                "JoinFtGroup (SYNC) [FtGroupId: %u]: failed due to timeout\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
            /* Leave DSM Fault Tolerance Group (ignore errors). */
            GCS_Leave(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                DSM_DATA_LOCAL(dataObj).groupName);
            return ret;
        }
        else
        {
            ITS_TRACE_DEBUG((
                "JoinFtGroup [FtGroupId: %u]: SYNC succeeded\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
    }

    /* Always (even if explicit synchronization). */
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

    /* Leave DSM Fault Tolerance Group. */
    ret = GCS_Leave(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                DSM_DATA_LOCAL(dataObj).groupName);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "LeaveFtGroup [FtGroupId: %u]: GCS_Leave failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        ITS_TRACE_CRITICAL((
            "[FtGroupId: %u] Failed to leave DSM Fault Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        return ITS_EGCSLEAVEFAIL;
    }

    ITS_TRACE_DEBUG((
        "LeaveFtGroup [FtGroupId: %u]: GCS_Leave succeeded\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_INST_FT_GROUP_JOINED(instObj) = ITS_FALSE;

    return ITS_SUCCESS;
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
 *
 * Procedures thread alive event function.
 *
 */
static void
ProceduresThreadAliveEventFunction(
    int code, 
    void* data)
{
    DSM_DataObject* dataObj = (DSM_DataObject*)data;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "ProceduresThreadAliveEventFunction [FtGroupId: %u]: procedures thread"
        " alive\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     *  TODO: find a way to notify Health Manager that DSM GCS Procedures 
     *  Thread is alive.
     */
}

/******************************************************************************
 *
 * Receive message event function.
 *
 */

static long newCounter = 0;

static void 
StubReceiveMessageEventFunction(
    int fd, 
    int code, 
    void* data)
{
    GCS_SERVICE service = 0;
    char        sender[GCS_MAX_GROUP_NAME];
    char        groups[DSM_MAX_MEMBERS + 4][GCS_MAX_GROUP_NAME];
    ITS_INT     maxGroups = DSM_MAX_MEMBERS + 4; /* TODO: why +4 ? */
    ITS_INT     numGroups = 0;
    ITS_SHORT   msgType = 0;
    ITS_INT     endianMismatch = 0;
    int         ret = ITS_SUCCESS;

    DSM_DataObject* dataObj = (DSM_DataObject*)data;

    ++newCounter;
    if (newCounter %1000 == 0)
    {
        printf("StubReceiveMessageEventFunction  :: counter :%ld\n", newCounter);
    }

    ITS_C_REQUIRE(dataObj != NULL);

/*
 * Should include memset of DSM_DATA_LOCAL(dataObj).bufMsg but it is too time 
 * consuming even for debug builds.
 */
#if defined(DEBUG) || defined(_DEBUG)
    memset(sender, 0, GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        groups, 
        0, 
        (DSM_MAX_MEMBERS + 4) * GCS_MAX_GROUP_NAME * sizeof(char));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    ITS_TRACE_DEBUG((
        "StubReceiveMessageEventFunction [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     *  Blocking call, but event function will be called only and only if there
     *  is something to receive (using select underneath), so in practice not a
     *  blocking call.
     */

    ret = GCS_Receive(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                &service,
                sender,
                maxGroups,
                &numGroups,
                groups,
                &msgType,
                &endianMismatch,
                DSM_MAX_MSG_SIZE,
                DSM_DATA_LOCAL(dataObj).bufMsg);
    if (ret < 0)
    {
        if (ret == GCS_GROUPS_TOO_SHORT)
        {
            /* Should never be reached. */

            ITS_TRACE_ERROR((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: groups buffer "
                "too short: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_WARNING((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: message "
                "dropped\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            return;
        }
        else if (ret == GCS_BUFFER_TOO_SHORT)
        {
            /* Should never be reached. */

            ITS_TRACE_ERROR((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: message buffer "
                "too short: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_WARNING((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: message "
                "dropped\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            return;
        }
        else
        {
            ITS_TRACE_ERROR((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: GCS_Receive "
                "failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: unable to "
                "recover from previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: unable to "
                "recover from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }
    }
    else
    {
        ITS_C_ASSERT(ret >= 0);

        if (TRACE_DebugTraceOn())
        {
            char msgStr[3072 + 128];
            char hexStr[4];
            int dumpSize;
            int i;

            msgStr[0] = '\0';
            hexStr[0] = '\0';

            dumpSize = (ret < 1024) ? ret : 1024;

            for (i = 0; i < dumpSize; i++)
            {
                if (i !=0 && i % 24 == 0)
                {
                    strcat(msgStr, "\n");
                }

                sprintf(
                    hexStr, 
                    "%02X ", 
                    (ITS_OCTET)DSM_DATA_LOCAL(dataObj).bufMsg[i]);

                ITS_C_ASSERT(strlen(hexStr) == 3);

                strcat(msgStr, hexStr);
            }

            ITS_C_ASSERT(strlen(msgStr) < 3072 + 128);

            ITS_TRACE_DEBUG((
                "StubReceiveMessageEventFunction  [FtGroupId: %u]: Received message"
                " hex dump:\n%s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                msgStr));
        }

        if (GCS_IsRegularMsg(service))
        {
            if (TRACE_DebugTraceOn())
            {
                char serviceStr[32];

                if (GCS_IsUnreliableMsg(service))
                {
                    strcpy(serviceStr, "UNRELIABLE");
                }
                else if (GCS_IsReliableMsg(service))
                {
                    strcpy(serviceStr, "RELIABLE");
                }
                else if (GCS_IsFifoMsg(service))
                {
                    strcpy(serviceStr, "FIFO");
                }
                else if (GCS_IsCausalMsg(service))
                {
                    strcpy(serviceStr, "CAUSAL");
                }
                else if (GCS_IsAgreedMsg(service))
                {
                    strcpy(serviceStr, "AGREED");
                }
                else if (GCS_IsSafeMsg(service))
                {
                    strcpy(serviceStr, "SAFE");
                }
                else
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;

                    strcpy(serviceStr, "UNKNOWN");

                    ITS_C_ASSERT(must_not_be_reached);
                }

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received %s regular message from %s | "
                    "type: %s | "
                    "endian: %d | "
                    "number of groups: %d | "
                    "size: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    serviceStr,
                    sender,
                    MsgTypeToStr(msgType),
                    endianMismatch,
                    numGroups,
                    ret));
            }

            switch (msgType)
            {
            case DSM_MSG_ALLOCATE_ROW:

                ProcedureAllocateRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_FIND_ROW:

                ProcedureFindRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_FREE_ROW:

                ProcedureFreeRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_COMMIT_ROW:
                
                ProcedureCommitRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_JOIN_INFO:

                ProcedureJoinInfo(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_REQUEST:

                ProcedureSyncRequest(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_LOCK:

                ProcedureSyncLock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_LOCK_RETRY:

                ProcedureSyncLockRetry(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_UNLOCK:

                ProcedureSyncUnlock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_MEM:

                ProcedureSyncMem(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_MEM_TCP:

                ProcedureSyncMemTcp(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_INVALID_MASTER:

                ProcedureSyncInvalidMaster(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_ROW:

                ProcedureLockUnlockRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_TABLE:

                ProcedureLockUnlockTable(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_DSM:

                ProcedureLockUnlockDsm(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK:

                ProcedureLockUnlockRowNoLock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_MULTICAST_EVENT:
            {    
                DSM_Message_Multicast *multicastMessage;
                DSM_Message_Multicast *queuedMessage;
                ITS_EVENT ev;
                ITS_EVENT queuedEv;
                int len;

                if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state) || 
                    IsDsmStateJoining(DSM_DATA_STATE_DATA(dataObj).state) || 
                    IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state)  
                   )
                {
                    ITS_TRACE_CRITICAL(("** InitialState: DISCARD Message** \n"));
                    break;
                }

                if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) )
	        {

                    multicastMessage  = (DSM_Message_Multicast *) 
                                  DSM_DATA_LOCAL(dataObj).bufMsg;

                    if (TRANSPORT_FindTransport(
                           multicastMessage->u.multicastEvent.dest) != NULL)
                    {
                        /* Dequeue all saved messages and send all to thread */
                         while (MLIST_GetCount(
				 DSM_DATA_STACK_MULTICAST_QUEUE(dataObj)) != 0)
		         { 
                             EMLIST_RemHead(
                                DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                                (void**)&queuedMessage, &len);

                             
                            ITS_EVENT_INIT(
                                &queuedEv, 
                                queuedMessage->u.multicastEvent.source, 
                                queuedMessage->u.multicastEvent.ev.len);

                             memcpy(queuedEv.data, 
                                    queuedMessage->u.multicastEvent.data,
                                    queuedMessage->u.multicastEvent.ev.len);

             ITS_TRACE_DEBUG(("$$$$ STACK DEQUEUE: src %d, dest %d, len %d, " 
                             "evSrc %d, evLen %d $$$$\n",
                              queuedMessage->u.multicastEvent.source, 
                              queuedMessage->u.multicastEvent.dest,
                              len,
                              queuedMessage->u.multicastEvent.ev.src,
                              queuedMessage->u.multicastEvent.ev.len));


                             if (TRANSPORT_PutEvent(
                                    queuedMessage->u.multicastEvent.dest, 
				    &queuedEv) != ITS_SUCCESS)
                             {
                                 ITS_TRACE_ERROR(("$$$ PutEvent Failed: "
                                 "dest = %d $$$$\n",
                                         queuedMessage->u.multicastEvent.dest));
 
                             }

                             free(queuedMessage);
                             queuedMessage = NULL;

                         }


                        ITS_EVENT_INIT(
                             &ev, 
                             multicastMessage->u.multicastEvent.source, 
                             multicastMessage->u.multicastEvent.ev.len);

                        memcpy(ev.data, multicastMessage->u.multicastEvent.data,
                               multicastMessage->u.multicastEvent.ev.len);

                        TRANSPORT_PutEvent(
                            multicastMessage->u.multicastEvent.dest, 
                            &ev);
                    }
                    else
                    {
                        DSM_Message_Multicast *multicastEvent;

                        /* TODO: Save the message in a Message Queue */
                    
                        multicastEvent =  (DSM_Message_Multicast*) malloc(sizeof(DSM_Message_Multicast) );
                        memcpy(multicastEvent, DSM_DATA_LOCAL(dataObj).bufMsg,
                               sizeof(DSM_Message_Multicast));
#if 0
                         ITS_TRACE_ERROR(("$$$$ Transport is down: "
                                           "QEUEUE Message src %d, dest %d, len %d, evSrc %d, evLen %d $$$$\n",
                         multicastEvent->u.multicastEvent.source, 
                         multicastEvent->u.multicastEvent.dest,
                         len,
                         multicastEvent->u.multicastEvent.ev.src,
                         multicastEvent->u.multicastEvent.ev.len));
#endif
                        MLIST_AddTail(
                            DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                            multicastEvent, sizeof(DSM_Message_Multicast));
                    }
                 }
	         else
                 {
                     DSM_Message_Multicast *multicastEvent;

                    multicastMessage  = (DSM_Message_Multicast *) 
                                  DSM_DATA_LOCAL(dataObj).bufMsg;

                     /*Save message in Queue due to Lock or Sync */

                     multicastEvent =  (DSM_Message_Multicast*) malloc(sizeof(DSM_Message_Multicast));

                     memcpy(multicastEvent, DSM_DATA_LOCAL(dataObj).bufMsg,
                            sizeof(DSM_Message_Multicast));
                
                     ITS_TRACE_ERROR(("$$$$ State is not normal: "
                                       "QEUEUE Message src %d, dest %d, len %d, evSrc %d, evLen %d $$$$\n",
                                      multicastEvent->u.multicastEvent.source, 
                                      multicastEvent->u.multicastEvent.dest,
                                      len,
                                      multicastEvent->u.multicastEvent.ev.src,
                                      multicastEvent->u.multicastEvent.ev.len));


                     MLIST_AddTail(DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                                   multicastEvent, sizeof(DSM_Message_Multicast));

                 }

                break;
            }
            case  ITS_STATE_CHANGE_EVENT:
            {
                /* 
                 * This is state change event from mate, handle it 
                 * call the change over call back by setting leave
                 */ 

                DSM_MembershipChangeCbData membershipChangeCbData;
                DSM_Message_Multicast *multicastMessage = (DSM_Message_Multicast *)
                                  DSM_DATA_LOCAL(dataObj).bufMsg;

                /* Discard this event on the same node, who does multicast*/
                if (multicastMessage->u.multicastEvent.data[2] ==
                        DSM_GetNodeId())
                {
                    ITS_TRACE_CRITICAL(("Drop Received state change even\n"));
                    break;
                }

                membershipChangeCbData.membershipChangeType = 
                                    multicastMessage->u.multicastEvent.data[0];

                ITS_TRACE_CRITICAL(("********Received state change even\n"));
                CALLBACK_CallCallbackList(
                               DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(
                               DSM_DATA_INST_OBJECT(dataObj)),
                               (ITS_POINTER)dataObj,
                               (ITS_POINTER)&membershipChangeCbData);
            break;
            }
            default:
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                    ITS_C_ASSERT(must_not_be_reached);
                }
            }
        }
        else if (GCS_IsMembershipMsg(service))
        {
            if (GCS_IsRegMembMsg(service))
            {
                int numBytes = 0;
                GCS_GROUP_ID* groupId;
                ITS_INT* numVs;
                char* vsMembers;

                groupId = (GCS_GROUP_ID*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(GCS_GROUP_ID);
                numVs = (ITS_INT*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(ITS_INT);
                vsMembers = &DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];

                if (TRACE_DebugTraceOn())
                {
                    char infoStr[1024];
                    int i; 

                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Received REGULAR membership message "
                        "for Fault Tolerance Group: %s | number of members: %d"
                        " | I am member: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        sender,
                        numGroups,
                        msgType));

                    sprintf(
                        infoStr, 
                        "[FtGroupId: %u] Membership message list of "
                        "members:\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    for (i = 0; i < numGroups; i++)
                    {
                        strcat(infoStr, "\t");
                        strcat(infoStr, groups[i]);
                        strcat(infoStr, "\n");
                    }

                    ITS_C_ASSERT(strlen(infoStr) < 1024);

                    ITS_TRACE_DEBUG(("%s", infoStr));

                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message Fault Tolerance "
                        "Group id: %d %d %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        groupId->id[0],
                        groupId->id[1],
                        groupId->id[2]));
                }

                if (GCS_IsCausedJoinMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to JOIN of "
                        "%s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureJoin(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedLeaveMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to LEAVE of "
                        "%s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureLeave(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedDisconnectMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to DISCONNECT "
                        "of %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureDisconnect(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedNetworkMsg(service))
                {   
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to NETWORK "
                        "change\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    if (TRACE_DebugTraceOn())
                    {
                        char infoStr[1024];
                        int i;

                        sprintf(
                            infoStr, 
                            "[FtGroupId: %u] Membership message due to NETWORK"
                            " change has %d VS members:\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            *numVs);

                        for (i = 0; 
                             i < *numVs;
                             i++, vsMembers += GCS_MAX_GROUP_NAME)
                        {
                            strcat(infoStr, "\t");
                            strcat(infoStr, vsMembers);
                            strcat(infoStr, "\n");
                        }
                    }

                    ProcedureNetworkChange(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);                    
                }
                else
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                    ITS_C_ASSERT(must_not_be_reached);
                }
            }
            else if (GCS_IsTransitionMsg(service))
            {
                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received TRANSITIONAL membership message"
                    " for Fault Tolerance Group: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    sender));
            }
            else if (GCS_IsCausedLeaveMsg(service))
            {
                int numBytes = 0;
                GCS_GROUP_ID* groupId;
                ITS_INT* numVs;
                char* vsMembers;

                groupId = 
                    (GCS_GROUP_ID*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(GCS_GROUP_ID);
                numVs = (ITS_INT*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(ITS_INT);
                vsMembers = &DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received self-leave membership message "
                    "for Fault Tolerance Group: %s | I am leaving member: "
                    "%s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    sender,
                    DSM_DATA_LOCAL(dataObj).memberName));

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Membership message (non-regular) due to"
                    " self-leave of: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    DSM_DATA_LOCAL(dataObj).memberName));

                ProcedureLeave(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);
            }
            else
            {
                ITS_TRACE_ERROR((
                    "[FtGroupId: %u] Received invalid membership message of "
                    "type 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    service));
            }
        }
        else if (GCS_IsRejectMsg(service))
        {
            ITS_TRACE_DEBUG((
                "[FtGroupId: %u] Received REJECTED message from: %s | "
                "service: 0x%X | "
                "type: %d | "
                "number of groups: %d | "
                "size: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                sender,
                service,
                msgType,
                endianMismatch,
                numGroups,
                ret));
        }
        else
        {
            ITS_TRACE_ERROR((
                "[FtGroupId: %u] Receive unknown message from: %s | "
                "service (unknown): 0x%X | "
                "size: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                sender,
                service,
                ret));
        }
    }
}
static void 
ReceiveMessageEventFunction(
    int fd, 
    int code, 
    void* data)
{
    GCS_SERVICE service = 0;
    char        sender[GCS_MAX_GROUP_NAME];
    char        groups[DSM_MAX_MEMBERS + 4][GCS_MAX_GROUP_NAME];
    ITS_INT     maxGroups = DSM_MAX_MEMBERS + 4; /* TODO: why +4 ? */
    ITS_INT     numGroups = 0;
    ITS_SHORT   msgType = 0;
    ITS_INT     endianMismatch = 0;
    int         ret = ITS_SUCCESS;

    DSM_DataObject* dataObj = (DSM_DataObject*)data;

    ++newCounter;
    if (newCounter %1000 == 0)
    {
        printf("ReceiveMessageEventFunction :: counter :%ld\n", newCounter);
    }

    ITS_C_REQUIRE(dataObj != NULL);

/*
 * Should include memset of DSM_DATA_LOCAL(dataObj).bufMsg but it is too time 
 * consuming even for debug builds.
 */
#if defined(DEBUG) || defined(_DEBUG)
    memset(sender, 0, GCS_MAX_GROUP_NAME * sizeof(char));
    memset(
        groups, 
        0, 
        (DSM_MAX_MEMBERS + 4) * GCS_MAX_GROUP_NAME * sizeof(char));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    ITS_TRACE_DEBUG((
        "ReceiveMessageEventFunction [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     *  Blocking call, but event function will be called only and only if there
     *  is something to receive (using select underneath), so in practice not a
     *  blocking call.
     */

    ret = GCS_Receive(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                &service,
                sender,
                maxGroups,
                &numGroups,
                groups,
                &msgType,
                &endianMismatch,
                DSM_MAX_MSG_SIZE,
                DSM_DATA_LOCAL(dataObj).bufMsg);
    if (ret < 0)
    {
        if (ret == GCS_GROUPS_TOO_SHORT)
        {
            /* Should never be reached. */

            ITS_TRACE_ERROR((
                "ReceiveMessageEventFunction [FtGroupId: %u]: groups buffer "
                "too short: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_WARNING((
                "ReceiveMessageEventFunction [FtGroupId: %u]: message "
                "dropped\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            return;
        }
        else if (ret == GCS_BUFFER_TOO_SHORT)
        {
            /* Should never be reached. */

            ITS_TRACE_ERROR((
                "ReceiveMessageEventFunction [FtGroupId: %u]: message buffer "
                "too short: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_WARNING((
                "ReceiveMessageEventFunction [FtGroupId: %u]: message "
                "dropped\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            return;
        }
        else
        {
            ITS_TRACE_ERROR((
                "ReceiveMessageEventFunction [FtGroupId: %u]: GCS_Receive "
                "failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "ReceiveMessageEventFunction [FtGroupId: %u]: unable to "
                "recover from previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ReceiveMessageEventFunction [FtGroupId: %u]: unable to "
                "recover from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }
    }
    else
    {
        ITS_C_ASSERT(ret >= 0);

        if (TRACE_DebugTraceOn())
        {
            char msgStr[3072 + 128];
            char hexStr[4];
            int dumpSize;
            int i;

            msgStr[0] = '\0';
            hexStr[0] = '\0';

            dumpSize = (ret < 1024) ? ret : 1024;

            for (i = 0; i < dumpSize; i++)
            {
                if (i !=0 && i % 24 == 0)
                {
                    strcat(msgStr, "\n");
                }

                sprintf(
                    hexStr, 
                    "%02X ", 
                    (ITS_OCTET)DSM_DATA_LOCAL(dataObj).bufMsg[i]);

                ITS_C_ASSERT(strlen(hexStr) == 3);

                strcat(msgStr, hexStr);
            }

            ITS_C_ASSERT(strlen(msgStr) < 3072 + 128);

            ITS_TRACE_DEBUG((
                "ReceiveMessageEventFunction [FtGroupId: %u]: Received message"
                " hex dump:\n%s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                msgStr));
        }

        if (GCS_IsRegularMsg(service))
        {
            if (TRACE_DebugTraceOn())
            {
                char serviceStr[32];

                if (GCS_IsUnreliableMsg(service))
                {
                    strcpy(serviceStr, "UNRELIABLE");
                }
                else if (GCS_IsReliableMsg(service))
                {
                    strcpy(serviceStr, "RELIABLE");
                }
                else if (GCS_IsFifoMsg(service))
                {
                    strcpy(serviceStr, "FIFO");
                }
                else if (GCS_IsCausalMsg(service))
                {
                    strcpy(serviceStr, "CAUSAL");
                }
                else if (GCS_IsAgreedMsg(service))
                {
                    strcpy(serviceStr, "AGREED");
                }
                else if (GCS_IsSafeMsg(service))
                {
                    strcpy(serviceStr, "SAFE");
                }
                else
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;

                    strcpy(serviceStr, "UNKNOWN");

                    ITS_C_ASSERT(must_not_be_reached);
                }

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received %s regular message from %s | "
                    "type: %s | "
                    "endian: %d | "
                    "number of groups: %d | "
                    "size: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    serviceStr,
                    sender,
                    MsgTypeToStr(msgType),
                    endianMismatch,
                    numGroups,
                    ret));
            }

            switch (msgType)
            {
            case DSM_MSG_ALLOCATE_ROW:

                ProcedureAllocateRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_FIND_ROW:

                ProcedureFindRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_FREE_ROW:

                ProcedureFreeRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_COMMIT_ROW:
                
                ProcedureCommitRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_JOIN_INFO:

                ProcedureJoinInfo(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_REQUEST:

                ProcedureSyncRequest(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_LOCK:

                ProcedureSyncLock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_LOCK_RETRY:

                ProcedureSyncLockRetry(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_UNLOCK:

                ProcedureSyncUnlock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_MEM:

                ProcedureSyncMem(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_MEM_TCP:

                ProcedureSyncMemTcp(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_SYNC_INVALID_MASTER:

                ProcedureSyncInvalidMaster(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_ROW:

                ProcedureLockUnlockRow(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_TABLE:

                ProcedureLockUnlockTable(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_DSM:

                ProcedureLockUnlockDsm(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK:

                ProcedureLockUnlockRowNoLock(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);

                break;

            case DSM_MSG_MULTICAST_EVENT:
            {    
                DSM_Message_Multicast *multicastMessage;
                DSM_Message_Multicast *queuedMessage;
                ITS_EVENT ev;
                ITS_EVENT queuedEv;
                int len;

                if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state) || 
                    IsDsmStateJoining(DSM_DATA_STATE_DATA(dataObj).state) || 
                    IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state)  
                   )
                {
                    ITS_TRACE_CRITICAL(("** InitialState: DISCARD Message** \n"));
                    break;
                }

                if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) )
	        {

                    multicastMessage  = (DSM_Message_Multicast *) 
                                  DSM_DATA_LOCAL(dataObj).bufMsg;
             ITS_TRACE_CRITICAL(("$$$$ MULITICAST DESTINATION RECEIVED: dest [%x] ", multicastMessage->u.multicastEvent.dest));

                    if (TRANSPORT_FindTransport(
                           multicastMessage->u.multicastEvent.dest) != NULL)
                    {
                        /* Dequeue all saved messages and send all to thread */
                         while (MLIST_GetCount(
				 DSM_DATA_STACK_MULTICAST_QUEUE(dataObj)) != 0)
		         { 
                             EMLIST_RemHead(
                                DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                                (void**)&queuedMessage, &len);

                             
                            ITS_EVENT_INIT(
                                &queuedEv, 
                                queuedMessage->u.multicastEvent.source, 
                                queuedMessage->u.multicastEvent.ev.len);

                             memcpy(queuedEv.data, 
                                    queuedMessage->u.multicastEvent.data,
                                    queuedMessage->u.multicastEvent.ev.len);

             ITS_TRACE_DEBUG(("$$$$ STACK DEQUEUE: src %d, dest %d, len %d, " 
                             "evSrc %d, evLen %d $$$$\n",
                              queuedMessage->u.multicastEvent.source, 
                              queuedMessage->u.multicastEvent.dest,
                              len,
                              queuedMessage->u.multicastEvent.ev.src,
                              queuedMessage->u.multicastEvent.ev.len));


                             if (TRANSPORT_PutEvent(
                                    queuedMessage->u.multicastEvent.dest, 
				    &queuedEv) != ITS_SUCCESS)
                             {
                                 ITS_TRACE_ERROR(("$$$ PutEvent Failed: "
                                 "dest = %d $$$$\n",
                                         queuedMessage->u.multicastEvent.dest));
 
                             }

                             free(queuedMessage);
                             queuedMessage = NULL;

                         }


                        ITS_EVENT_INIT(
                             &ev, 
                             multicastMessage->u.multicastEvent.source, 
                             multicastMessage->u.multicastEvent.ev.len);

                        memcpy(ev.data, multicastMessage->u.multicastEvent.data,
                               multicastMessage->u.multicastEvent.ev.len);

                        TRANSPORT_PutEvent(
                            multicastMessage->u.multicastEvent.dest, 
                            &ev);
                    }
                    else
                    {
                        DSM_Message_Multicast *multicastEvent;

                        /* TODO: Save the message in a Message Queue */
                    
                        multicastEvent =  (DSM_Message_Multicast*) malloc(sizeof(DSM_Message_Multicast) );
                        memcpy(multicastEvent, DSM_DATA_LOCAL(dataObj).bufMsg,
                               sizeof(DSM_Message_Multicast));
#if 0
                         ITS_TRACE_ERROR(("$$$$ Transport is down: "
                                           "QEUEUE Message src %d, dest %d, len %d, evSrc %d, evLen %d $$$$\n",
                         multicastEvent->u.multicastEvent.source, 
                         multicastEvent->u.multicastEvent.dest,
                         len,
                         multicastEvent->u.multicastEvent.ev.src,
                         multicastEvent->u.multicastEvent.ev.len));
#endif
                        MLIST_AddTail(
                            DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                            multicastEvent, sizeof(DSM_Message_Multicast));
                    }
                 }
	         else
                 {
                     DSM_Message_Multicast *multicastEvent;

                    multicastMessage  = (DSM_Message_Multicast *) 
                                  DSM_DATA_LOCAL(dataObj).bufMsg;

                     /*Save message in Queue due to Lock or Sync */

                     multicastEvent =  (DSM_Message_Multicast*) malloc(sizeof(DSM_Message_Multicast));

                     memcpy(multicastEvent, DSM_DATA_LOCAL(dataObj).bufMsg,
                            sizeof(DSM_Message_Multicast));
                
                     ITS_TRACE_ERROR(("$$$$ State is not normal: "
                                       "QEUEUE Message src %d, dest %d, len %d, evSrc %d, evLen %d $$$$\n",
                                      multicastEvent->u.multicastEvent.source, 
                                      multicastEvent->u.multicastEvent.dest,
                                      len,
                                      multicastEvent->u.multicastEvent.ev.src,
                                      multicastEvent->u.multicastEvent.ev.len));


                     MLIST_AddTail(DSM_DATA_STACK_MULTICAST_QUEUE(dataObj), 
                                   multicastEvent, sizeof(DSM_Message_Multicast));

                 }

                break;
            }
            case  ITS_STATE_CHANGE_EVENT:
            {
                /* 
                 * This is state change event from mate, handle it 
                 * call the change over call back by setting leave
                 */ 

                DSM_MembershipChangeCbData membershipChangeCbData;
                DSM_Message_Multicast *multicastMessage = (DSM_Message_Multicast *)
                                  DSM_DATA_LOCAL(dataObj).bufMsg;

                /* Discard this event on the same node, who does multicast*/
                if (multicastMessage->u.multicastEvent.data[2] ==
                        DSM_GetNodeId())
                {
                    ITS_TRACE_CRITICAL(("Drop Received state change even\n"));
                    break;
                }

                membershipChangeCbData.membershipChangeType = 
                                    multicastMessage->u.multicastEvent.data[0];

                ITS_TRACE_CRITICAL(("********Received state change even\n"));
                CALLBACK_CallCallbackList(
                               DSM_INST_MEMBERSHIP_CHANGE_CALLBACKS(
                               DSM_DATA_INST_OBJECT(dataObj)),
                               (ITS_POINTER)dataObj,
                               (ITS_POINTER)&membershipChangeCbData);
            break;
            }
            default:
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                    ITS_C_ASSERT(must_not_be_reached);
                }
            }
        }
        else if (GCS_IsMembershipMsg(service))
        {
            if (GCS_IsRegMembMsg(service))
            {
                int numBytes = 0;
                GCS_GROUP_ID* groupId;
                ITS_INT* numVs;
                char* vsMembers;

                groupId = (GCS_GROUP_ID*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(GCS_GROUP_ID);
                numVs = (ITS_INT*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(ITS_INT);
                vsMembers = &DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];

                if (TRACE_DebugTraceOn())
                {
                    char infoStr[1024];
                    int i; 

                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Received REGULAR membership message "
                        "for Fault Tolerance Group: %s | number of members: %d"
                        " | I am member: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        sender,
                        numGroups,
                        msgType));

                    sprintf(
                        infoStr, 
                        "[FtGroupId: %u] Membership message list of "
                        "members:\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    for (i = 0; i < numGroups; i++)
                    {
                        strcat(infoStr, "\t");
                        strcat(infoStr, groups[i]);
                        strcat(infoStr, "\n");
                    }

                    ITS_C_ASSERT(strlen(infoStr) < 1024);

                    ITS_TRACE_DEBUG(("%s", infoStr));

                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message Fault Tolerance "
                        "Group id: %d %d %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        groupId->id[0],
                        groupId->id[1],
                        groupId->id[2]));
                }

                if (GCS_IsCausedJoinMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to JOIN of "
                        "%s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureJoin(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedLeaveMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to LEAVE of "
                        "%s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureLeave(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedDisconnectMsg(service))
                {
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to DISCONNECT "
                        "of %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        vsMembers));

                    ProcedureDisconnect(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);
                }
                else if (GCS_IsCausedNetworkMsg(service))
                {   
                    ITS_TRACE_DEBUG((
                        "[FtGroupId: %u] Membership message due to NETWORK "
                        "change\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    if (TRACE_DebugTraceOn())
                    {
                        char infoStr[1024];
                        int i;

                        sprintf(
                            infoStr, 
                            "[FtGroupId: %u] Membership message due to NETWORK"
                            " change has %d VS members:\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            *numVs);

                        for (i = 0; 
                             i < *numVs;
                             i++, vsMembers += GCS_MAX_GROUP_NAME)
                        {
                            strcat(infoStr, "\t");
                            strcat(infoStr, vsMembers);
                            strcat(infoStr, "\n");
                        }
                    }

                    ProcedureNetworkChange(
                        dataObj,
                        service,
                        sender,
                        numGroups,
                        groups,
                        ret,
                        DSM_DATA_LOCAL(dataObj).bufMsg);                    
                }
                else
                {
                    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                    ITS_C_ASSERT(must_not_be_reached);
                }
            }
            else if (GCS_IsTransitionMsg(service))
            {
                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received TRANSITIONAL membership message"
                    " for Fault Tolerance Group: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    sender));
            }
            else if (GCS_IsCausedLeaveMsg(service))
            {
                int numBytes = 0;
                GCS_GROUP_ID* groupId;
                ITS_INT* numVs;
                char* vsMembers;

                groupId = 
                    (GCS_GROUP_ID*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(GCS_GROUP_ID);
                numVs = (ITS_INT*)&DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];
                numBytes += sizeof(ITS_INT);
                vsMembers = &DSM_DATA_LOCAL(dataObj).bufMsg[numBytes];

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Received self-leave membership message "
                    "for Fault Tolerance Group: %s | I am leaving member: "
                    "%s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    sender,
                    DSM_DATA_LOCAL(dataObj).memberName));

                ITS_TRACE_DEBUG((
                    "[FtGroupId: %u] Membership message (non-regular) due to"
                    " self-leave of: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    DSM_DATA_LOCAL(dataObj).memberName));

                ProcedureLeave(
                    dataObj,
                    service,
                    sender,
                    numGroups,
                    groups,
                    ret,
                    DSM_DATA_LOCAL(dataObj).bufMsg);
            }
            else
            {
                ITS_TRACE_ERROR((
                    "[FtGroupId: %u] Received invalid membership message of "
                    "type 0x%X\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    service));
            }
        }
        else if (GCS_IsRejectMsg(service))
        {
            ITS_TRACE_DEBUG((
                "[FtGroupId: %u] Received REJECTED message from: %s | "
                "service: 0x%X | "
                "type: %d | "
                "number of groups: %d | "
                "size: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                sender,
                service,
                msgType,
                endianMismatch,
                numGroups,
                ret));
        }
        else
        {
            ITS_TRACE_ERROR((
                "[FtGroupId: %u] Receive unknown message from: %s | "
                "service (unknown): 0x%X | "
                "size: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                sender,
                service,
                ret));
        }
    }
}

static void
ReceiveExceptionEventFunction(
    int fd, 
    int code, 
    void* data)
{
    DSM_DataObject* dataObj = (DSM_DataObject*)data;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_ERROR((
        "ReceiveExceptionEventFunction [FtGroupId: %u]: handler function "
        "called\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     * Note: if handler function called then probably lost connection with
     * GCS Daemon. Shared memory not in sync anymore. Unable to recover.
     */

    ITS_TRACE_CRITICAL((
        "ReceiveExceptionEventFunction [FtGroupId: %u]: unable to recover from"
        "previous error: abort\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Must abort process. */
    CallCriticalErrorNotificationCallbacks(
        dataObj,
        __LINE__,
        "ReceiveExceptionEventFunction [FtGroupId: %u]: unable to recover "
        "from error\n",
        DSM_DATA_FT_GROUP_ID(dataObj));

    /* Not reached. */
}

/******************************************************************************
 *
 * Procedures thread function.
 *
 */
static THREAD_RET_TYPE 
ProceduresThread(
    void* arg)
{
//    GCS_MAILBOX_POLL_INFO mailboxPollInfos[2];
    GCS_MAILBOX_POLL_INFO mailboxPollInfos[1];
    DSM_DataObject* dataObj;
    GCS_TIME timeout;
    GCS_TIME timeoutSigma;
    int ret;

    dataObj = (DSM_DataObject*)arg;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "ProceduresThread [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     *  Initialization.
     */

    ITS_TRACE_DEBUG((
        "ProceduresThread [FtGroupId: %u]: initialization\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    timeoutSigma.sec = 0;
    timeoutSigma.usec = 0;


    /*
     * Event handling forever loop.
     */

    ITS_TRACE_DEBUG((
        "ProceduresThread [FtGroupId: %u]: event handling forever loop\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    while (!DSM_DATA_PROCEDURES(dataObj).exitThread)
    {
#if 0
        mailboxPollInfos[0].mailbox = DSM_DATA_LOCAL(dataObj).mailbox;
       // mailboxPollInfos[0].Stubmailbox = DSM_DATA_LOCAL(dataObj).Stubmailbox;
        mailboxPollInfos[0].lookFor = 0;
        mailboxPollInfos[0].lookFor |= GCS_POLL_READ;
        mailboxPollInfos[0].lookFor |= GCS_POLL_ERROR;
        mailboxPollInfos[1].mailbox = DSM_DATA_LOCAL(dataObj).Stubmailbox;
       // mailboxPollInfos[1].Stubmailbox = DSM_DATA_LOCAL(dataObj).Stubmailbox;
        mailboxPollInfos[1].lookFor = 0;
        mailboxPollInfos[1].lookFor |= GCS_POLL_READ;
        mailboxPollInfos[1].lookFor |= GCS_POLL_ERROR;
#endif

        mailboxPollInfos[0].mailbox = DSM_DATA_LOCAL(dataObj).Stubmailbox;
       // mailboxPollInfos[1].Stubmailbox = DSM_DATA_LOCAL(dataObj).Stubmailbox;
        mailboxPollInfos[0].lookFor = 0;
        mailboxPollInfos[0].lookFor |= GCS_POLL_READ;
        mailboxPollInfos[0].lookFor |= GCS_POLL_ERROR;

        /* 100 milliseconds timeout. */
        timeout.sec = 0;
        timeout.usec = 100000;

       ITS_TRACE_DEBUG((" POLLING STARTED:: \n"));
        ret = GCS_MailboxPoll(
                    mailboxPollInfos,
                    1,
                    &timeout);
       ITS_TRACE_DEBUG((" POLLING END:: \n"));
//        if (ret == 1 || ret == 2)
        if (ret == 1)
        {
            if (mailboxPollInfos[0].wasSet & GCS_POLL_ERROR)
            {
                ReceiveExceptionEventFunction(
                    DSM_DATA_LOCAL(dataObj).mailbox,
                    0,
                    (void*)dataObj);
            }
#if 0

            if (mailboxPollInfos[0].wasSet & GCS_POLL_READ)
            {
               ITS_TRACE_DEBUG(("ReceiveMessageEventFunction:: \n"));
                ReceiveMessageEventFunction(
                    DSM_DATA_LOCAL(dataObj).mailbox,
                    0,
                    (void*)dataObj);
            }
           if(mailboxPollInfos[1].wasSet & GCS_POLL_READ)
            {
               ITS_TRACE_DEBUG(("StubReceiveMessageEventFunction:: \n"));
               StubReceiveMessageEventFunction(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
                    0,
                    (void*)dataObj);
            }
#endif
           if(mailboxPollInfos[0].wasSet & GCS_POLL_READ)
            {
               ITS_TRACE_DEBUG(("StubReceiveMessageEventFunction::MESSAGE RECV AT STUB \n"));
               StubReceiveMessageEventFunction(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
                    0,
                    (void*)dataObj);
            }
        }
        else if (ret == 0)
        {
            /* Timeout => continue. */
        }
        else
        {
            ITS_TRACE_ERROR((
                "ProceduresThread [FtGroupId: %u]: GCS_MailboxPoll failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "ProceduresThread [FtGroupId: %u]: unable to recover from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProceduresThread [FtGroupId: %u]: unable to recover from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
            THREAD_NORMAL_EXIT;
        }

        timeoutSigma = GCS_AddTime(timeoutSigma, timeout);

        if (GCS_CompareTime(
                DSM_DATA_PROCEDURES(dataObj).aliveTimeout, 
                timeoutSigma) < 0)
        {
            timeoutSigma.sec = 0;
            timeoutSigma.usec = 0;

            ProceduresThreadAliveEventFunction(0, (void*)dataObj);
        }
    }

    ITS_TRACE_DEBUG((
        "ProceduresThread [FtGroupId: %u]: termination\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* If reached event handling forever loop is terminated. */
    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INVALID;

    /*
     * TODO: must notify all the DSM_* public functions that are blocked on 
     * condition variables, although that might be done by ProceduresDestroy.
     */

    ITS_TRACE_DEBUG((
        "ProceduresThread [FtGroupId: %u]: normal exit\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    THREAD_NORMAL_EXIT;
}


/******************************************************************************
 ******************************************************************************
 **
 ** DSM Procedures.
 **
 */

/* 
 * Helper functions related to pending procedures (sync and lock).
 */

static int
InsertPendingProcedureDueToSync(
    DSM_DataObject* dataObj,
    ITS_UINT type,
    ITS_UINT tid,
    ITS_UINT tableId,
    ITS_UINT originThreadId,
    char originMemberName[GCS_MAX_GROUP_NAME],
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_INT size,
    char msg[DSM_MAX_MSG_SIZE],
    const char* calledFromProc)
{
    DSM_InstObject* instObj;
    DSM_Procedure* procedure;
    int ret;

    instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(type >= DSM_PROCEDURE_ALLOCATE_ROW);
    ITS_C_REQUIRE(type <= DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK);
    ITS_C_REQUIRE(
        tableId < DSM_INST_MAX_NUM_TABLES(instObj) || 
        tableId == (ITS_UINT)(-1));
    ITS_C_REQUIRE(originMemberName != NULL);

    /* See maximum size for groups member in DSM_Procedure structure. */
    ITS_C_ASSERT(numGroups <= DSM_MAX_MEMBERS);

    ITS_TRACE_DEBUG((
        "InsertPendingProcedureDueToSync [FtGroupId: %u]: called from: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        calledFromProc));

    ITS_TRACE_DEBUG((
        "InsertPendingProcedureDueToSync [FtGroupId: %u]: inserting "
        "PROCEDURE %s | "
        "tid: %u | "
        "tableId: %u | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        ProcedureTypeToStr(type),
        tid,
        tableId,
        originThreadId,
        originMemberName));

    procedure = (DSM_Procedure*)malloc(sizeof(DSM_Procedure) + size);
    if (procedure == NULL)
    {
        ITS_TRACE_ERROR((
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_ERROR((
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: unable to insert"
            " pending procedure\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_CRITICAL((
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: unacceptable "
            "state from previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: unable to "
            "recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return ITS_ENOMEM; /* Not reached. */
    }

    procedure->type = type;
    procedure->tid = tid;
    procedure->tableId = tableId;
    procedure->originThreadId = originThreadId;
    memcpy(procedure->originMemberName, originMemberName, GCS_MAX_GROUP_NAME);
    procedure->service = service;
    memcpy(procedure->sender, sender, GCS_MAX_GROUP_NAME);
    procedure->numGroups = numGroups;
    memcpy(procedure->groups, groups, numGroups * GCS_MAX_GROUP_NAME);
    procedure->size = size;
    memcpy(procedure->msg, msg, size);

    procedure->prev = NULL; /* Not used for sync. */
    procedure->next = NULL; /* Not used for sync. */

    ret = LIST_AddHead(
                DSM_DATA_SYNC_DATA(dataObj).procedureQueue, 
                &procedure, 
                sizeof(DSM_Procedure*));

    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: LIST_AddHead "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        free(procedure);

        ITS_TRACE_CRITICAL((
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: unacceptable "
            "state from previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "InsertPendingProcedureDueToSync [FtGroupId: %u]: unable to "
            "recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return ret; /* Not reached. */
    }

    return ITS_SUCCESS;
}

static int
InsertPendingProcedureDueToLock(
    DSM_DataObject* dataObj,
    ITS_UINT type,
    ITS_UINT tid,
    ITS_UINT tableId,
    ITS_UINT originThreadId,
    char originMemberName[GCS_MAX_GROUP_NAME],
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_INT size,
    char msg[DSM_MAX_MSG_SIZE],
    const char* calledFromProc)
{
    DSM_Procedure* procedure;
    DSM_InstObject* instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(type >= DSM_PROCEDURE_ALLOCATE_ROW);
    ITS_C_REQUIRE(type <= DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK);
    ITS_C_REQUIRE(
        tableId < DSM_INST_MAX_NUM_TABLES(instObj) ||
        tableId == (ITS_UINT)(-1));
    ITS_C_REQUIRE(originMemberName != NULL);

    /* See maximum size for groups member in DSM_Procedure structure. */
    ITS_C_ASSERT(numGroups <= DSM_MAX_MEMBERS);

    ITS_TRACE_DEBUG((
        "InsertPendingProcedure [FtGroupId: %u]: called from: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        calledFromProc));

    ITS_TRACE_DEBUG((
        "InsertPendingProcedure[FtGroupId:%u]:inserting %s | "
        "tid:%u| "
        "tableId:%u| "
        "orig memb: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        ProcedureTypeToStr(type),
        tid,
        tableId,
        originMemberName));

    //procedure = (DSM_Procedure*)dlmalloc( dataObj, sizeof(DSM_Procedure) + size);
/*Note:Reverting back to dlmalloc as on backup node after memory sync,list consists of 2 procedure pending 
       and whose pointer are invalid due to local malloc on active node*/
    procedure = (DSM_Procedure*)malloc(sizeof(DSM_Procedure) + size);
    if (procedure == NULL)
    {
        ITS_TRACE_ERROR((
            "InsertPendingProcedure [FtGroupId: %u]: out of memory\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_ERROR((
            "InsertPendingProcedure [FtGroupId: %u]: unable to insert pending"
            " procedure\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_CRITICAL((
            "InsertPendingProcedure [FtGroupId: %u]: unacceptable state from"
            " previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "InsertPendingProcedure [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return ITS_ENOMEM; /* Not reached. */
    }

    procedure->type = type;
    procedure->tid = tid;
    procedure->tableId = tableId;
    procedure->originThreadId = originThreadId;
    memcpy(procedure->originMemberName, originMemberName, GCS_MAX_GROUP_NAME);
    procedure->service = service;
    memcpy(procedure->sender, sender, GCS_MAX_GROUP_NAME);
    procedure->numGroups = numGroups;
    memcpy(procedure->groups, groups, numGroups * GCS_MAX_GROUP_NAME);
    procedure->size = size;
    memcpy(procedure->msg, msg, size);

    if (DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead == NULL)
    {
        ITS_C_ASSERT(DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail == NULL);

        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = procedure;
        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = procedure;
        procedure->prev = NULL;
        procedure->next = NULL;
    }
    else if (DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail == NULL)
    {
        ITS_C_ASSERT(DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead == NULL);

        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = procedure;
        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = procedure;
        procedure->prev = NULL;
        procedure->next = NULL;
    }
    else
    {
        ITS_C_ASSERT(DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead != NULL);
        ITS_C_ASSERT(DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail != NULL);

        procedure->prev = NULL;
        procedure->next = DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead;
        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead->prev = procedure;
        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = procedure;
    }

    DSM_DATA_PROCEDURE_MANAGER(dataObj).count++;
    //ITS_TRACE_ERROR(("InsertPendingProcedureDueToLock:: listHead[%x] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead));
    //ITS_TRACE_ERROR(("InsertPendingProcedureDueToLock:: listTail[%x] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail));
    //ITS_TRACE_ERROR(("InsertPendingProcedureDueToLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    return ITS_SUCCESS;
}

static int
ExecutePendingProceduresDueToSync(
    DSM_DataObject* dataObj,
    const char* calledFromProc)
{
    DSM_Procedure** procedure;
    int len;
    int ret;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "ExecutePendingProceduresDueToSync [FtGroupId: %u]: called from: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        calledFromProc));

    while (!LIST_EmptyP(DSM_DATA_SYNC_DATA(dataObj).procedureQueue))
    {
        ret = LIST_RemTail(
                    DSM_DATA_SYNC_DATA(dataObj).procedureQueue,
                    (void**)&procedure,
                    &len);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                "LIST_RemTail failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            return ret;
        }

        ITS_C_ASSERT(len = sizeof(DSM_Procedure*));
        ITS_C_ASSERT(*procedure != NULL);

        ITS_TRACE_DEBUG((
            "ExecutePendingProceduresDueToSync [FtGroupId: %u]: retrieved "
            "PROCEDURE %s | "
            "tid: %u | "
            "tableId: %u | "
            "origin threadId: %u | "
            "origin member: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ProcedureTypeToStr((*procedure)->type),
            (*procedure)->tid,
            (*procedure)->tableId,
            (*procedure)->originThreadId,
            (*procedure)->originMemberName));

        switch ((*procedure)->type)
        {
        case DSM_PROCEDURE_ALLOCATE_ROW:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureAllocateRow (queued while in SYNC state) by "
                "resending DSM ALLOCATE ROW message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_ALLOCATE_ROW,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                "DSM ALLOCATE ROW message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_FIND_ROW:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureFindRow (queued while in SYNC state) by resending "
                "DSM FIND ROW message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_FIND_ROW,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM FIND "
                "ROW message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_FREE_ROW:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureFreeRow (queued while in SYNC state) by resending "
                "DSM FREE ROW message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_FREE_ROW,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM FREE "
                "ROW message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_COMMIT_ROW:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureCommitRow (queued while in SYNC state) by resending "
                "DSM COMMIT ROW message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_COMMIT_ROW,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM COMMIT"
                " ROW message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_LOCK_UNLOCK_ROW:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync  [FtGroupId: %u]: call "
                "ProcedureLockUnlockRow (queued while in SYNC state) by "
                "resending DSM LOCK UNLOCK ROW message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_LOCK_UNLOCK_ROW,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM LOCK "
                "UNLOCK ROW message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_LOCK_UNLOCK_TABLE:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureLockUnlockTable (queued while in SYNC state) by "
                "resending DSM LOCK UNLOCK TABLE message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_LOCK_UNLOCK_TABLE,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM LOCK "
                "UNLOCK TABLE message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_LOCK_UNLOCK_DSM:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureLockUnlockDsm (queued while in SYNC state) by "
                "resending DSM LOCK UNLOCK DSM message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_LOCK_UNLOCK_DSM,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM LOCK "
                "UNLOCK DSM message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureLockUnlockRowNoLock (queued while in SYNC state) by "
                "resending DSM LOCK UNLOCK ROW NO LOCK message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM LOCK "
                "UNLOCK ROW NO LOCK message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_SYNC_REQUEST:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureSyncRequest (queued while in SYNC state) by "
                "resending DSM SYNC REQUEST message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_SYNC_REQUEST,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM SYNC "
                "REQUEST message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        case DSM_PROCEDURE_SYNC_LOCK:

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: call "
                "ProcedureSyncLock (queued while in SYNC state) by "
                "resending DSM SYNC LOCK message to GCS\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* TODO: add trace of message to be resent. */

            ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_SYNC_LOCK,
                        (*procedure)->size,
                        (*procedure)->msg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: "
                    "GCS_Multicast failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ExecutePendingProceduresDueToSync [FtGroupId: %u]: unable"
                    " to recover from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                break; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToSync [FtGroupId: %u]: DSM SYNC "
                "LOCK message successfully resent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            break;

        default:
            {
                /* TODO: review. */
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
            }
        }

        free(*procedure);
    }

    return ITS_SUCCESS;
}

static void
ExecutePendingProcedure(
    DSM_DataObject* dataObj,
    ITS_UINT type,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_INT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    ITS_C_REQUIRE(dataObj != NULL);

    switch (type)
    {
    case DSM_PROCEDURE_ALLOCATE_ROW:

        ProcedureAllocateRow(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_FIND_ROW:

        ProcedureFindRow(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_FREE_ROW:

        ProcedureFreeRow(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_COMMIT_ROW:
        
        ProcedureCommitRow(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_LOCK_UNLOCK_ROW:

        ProcedureLockUnlockRow(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_LOCK_UNLOCK_TABLE:

        ProcedureLockUnlockTable(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_LOCK_UNLOCK_DSM:

        ProcedureLockUnlockDsm(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    case DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK:

        ProcedureLockUnlockRowNoLock(
            dataObj,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg);

        break;

    default:
        {
            /* TODO: review. */
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
        }
    }
}

static int
ExecutePendingProceduresDueToLock(
    DSM_DataObject* dataObj,
    const char* calledFromProc)
{
    DSM_Procedure* procedure;
    ITS_UINT type;
    ITS_UINT tableId;
    ITS_UINT threadId;
    char* memberName;
    ITS_BOOLEAN executed;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "ExecutePendingProceduresDueToLock [FtGroupId: %u]: called from: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        calledFromProc));

    ITS_TRACE_DEBUG((
        "ExecutePendingProceduresDueToLock [FtGroupId: %u]: begin with %u "
        "procedures pending\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
  //  ITS_TRACE_ERROR(("ExecutePendingProceduresDueToLock:: listHead[%x] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead));
  //  ITS_TRACE_ERROR(("ExecutePendingProceduresDueToLock:: listTail[%x] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail));
  //  ITS_TRACE_ERROR(("ExecutePendingProceduresDueToLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    procedure = DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail;

    while (procedure != NULL)
    {
        DSM_Procedure* nextIterProcedure = procedure->prev;

        executed = ITS_FALSE;

        type = procedure->type;
        tableId = procedure->tableId;
        threadId = procedure->originThreadId;
        memberName = procedure->originMemberName;

    /*    ITS_TRACE_ERROR((
            "ExecutePendingProceduresDueToLock[FtGroupId:%u]:iterating "
            "PROC %s| "
            "tid:%u| "
            "tableId:%u| "
            "orig memb: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ProcedureTypeToStr(procedure->type),
            procedure->tid,
            procedure->tableId,
            procedure->originMemberName));*/

        if (type == DSM_PROCEDURE_LOCK_UNLOCK_DSM)
        {
            if (DsmIsLockedByMember(dataObj, memberName) &&
                DsmIsLockedByThread(dataObj, threadId))
            {
                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "locked by member and thread: execute iterated "
                    "procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
            else if (DsmIsLockedNotByMember(dataObj, memberName) ||
                     DsmIsLockedNotByThread(dataObj, threadId))
            {
                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "locked by another member or thread: do not execute "
                    "iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked: execute iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
        }
        else if (type == DSM_PROCEDURE_LOCK_UNLOCK_TABLE)
        {
            if (DsmIsLocked(dataObj))
            {
                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "locked: do not execute iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else if (TableIsLockedByMember(dataObj, memberName, tableId) &&
                     TableIsLockedByThread(dataObj, threadId, tableId))
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and table locked by member and thread: execute"
                    " iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
            else if (TableIsLockedNotByMember(dataObj, memberName, tableId) ||
                     TableIsLockedNotByThread(dataObj, threadId, tableId))
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and Table locked by another member or thread: "
                    "do not execute iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));
                ITS_C_ASSERT(!TableIsLocked(dataObj, tableId));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and Table not locked: execute iterated "
                    "procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
        }
        else if (type == DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK)
        {
            if (DsmIsLocked(dataObj))
            {
                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "locked: do not execute iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));

                /* 
                 * Table identifier absent => ignore Table Lock if any. In
                 * practice should be semantically acceptable. 
                 */

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and ignore Table lock: execute iterated "
                    "procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
        }
        else
        {
            if (DsmIsLocked(dataObj))
            {
                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "locked: do not execute iterated procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else if (TableIsLocked(dataObj, tableId))
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and Table locked: do not execute iterated "
                    "procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                executed = ITS_FALSE;
            }
            else
            {
                ITS_C_ASSERT(!DsmIsLocked(dataObj));
                ITS_C_ASSERT(!TableIsLocked(dataObj, tableId));

                ITS_TRACE_DEBUG((
                    "ExecutePendingProceduresDueToLock [FtGroupId: %u]: Dsm "
                    "not locked and Table not locked: execute iterated "
                    "procedure\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ExecutePendingProcedure(
                    dataObj,
                    procedure->type,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg);

                executed = ITS_TRUE;
            }
        }

        if (executed)
        {
            ITS_TRACE_DEBUG((
                "ExecutePendingProceduresDueToLock [FtGroupId: %u]: remove "
                "executed procedure\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            if (procedure == DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                procedure == DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->prev == NULL);
                ITS_C_ASSERT(procedure->next == NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = NULL;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

               // dlfree(dataObj, procedure);

                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else if (procedure == 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                     procedure != 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->next != NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = procedure->next;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead->prev = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

              //  dlfree(dataObj, procedure);

                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else if (procedure != 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                     procedure == 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->prev != NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = procedure->prev;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail->next = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

               // dlfree(dataObj, procedure);

                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else
            {
                DSM_Procedure* prevProcedure = procedure->prev;
                DSM_Procedure* nextProcedure = procedure->next;

                ITS_C_ASSERT(procedure->prev != NULL);
                ITS_C_ASSERT(procedure->next != NULL);

                prevProcedure->next = nextProcedure;
                nextProcedure->prev = prevProcedure;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

              //  dlfree(dataObj, procedure);
                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
        }

        procedure = nextIterProcedure;
    }
  //  ITS_TRACE_ERROR(("ExecutePendingProceduresDueToLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ITS_TRACE_DEBUG((
        "ExecutePendingProceduresDueToLock [FtGroupId: %u]: end with %u "
        "procedures pending\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    return ITS_SUCCESS;
}

static int
RemovePendingProceduresFromMemberDueToLock(
    DSM_DataObject* dataObj,
    char originMemberName[GCS_MAX_GROUP_NAME],
    const char* calledFromProc)
{
    DSM_Procedure* procedure;
    ITS_UINT type;
    ITS_UINT tableId;
    ITS_UINT threadId;
    char* memberName;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "RemovePendingProceduresFromMemberDueToLock [FtGroupId: %u]: begin "
        "with %u procedures pending\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
   // ITS_TRACE_ERROR(("RemovePendingProceduresFromMemberDueToLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    procedure = DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail;

    while (procedure != NULL)
    {
        DSM_Procedure* nextIterProcedure = procedure->prev;

        type = procedure->type;
        tableId = procedure->tableId;
        threadId = procedure->originThreadId;
        memberName = procedure->originMemberName;

        ITS_TRACE_DEBUG((
            "RemovePendingProceduresFromMemberDueToLock [FtGroupId: %u]: "
            "iterating PROCEDURE %s | "
            "tid: %u | "
            "tableId: %u | "
            "origin threadId: %u | "
            "origin member: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ProcedureTypeToStr(procedure->type),
            procedure->tid,
            procedure->tableId,
            procedure->originThreadId,
            procedure->originMemberName));

        if (strcmp(originMemberName, memberName) == 0)
        {
            ITS_TRACE_DEBUG((
                "RemovePendingProceduresFromMemberDueToLock [FtGroupId: %u]: "
                "remove procedure from origin member: %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                originMemberName));

            if (procedure == DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                procedure == DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->prev == NULL);
                ITS_C_ASSERT(procedure->next == NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = NULL;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

              //  dlfree(dataObj, procedure);
                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else if (procedure == 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                     procedure != 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->next != NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead = procedure->next;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead->prev = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

              //  dlfree(dataObj, procedure);
                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else if (procedure != 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead &&
                     procedure == 
                        DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail)
            {
                ITS_C_ASSERT(procedure->prev != NULL);

                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail = procedure->prev;
                DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail->next = NULL;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

               // dlfree(dataObj, procedure);

                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
            else
            {
                DSM_Procedure* prevProcedure = procedure->prev;
                DSM_Procedure* nextProcedure = procedure->next;

                ITS_C_ASSERT(procedure->prev != NULL);
                ITS_C_ASSERT(procedure->next != NULL);

                prevProcedure->next = nextProcedure;
                nextProcedure->prev = prevProcedure;

                DSM_DATA_PROCEDURE_MANAGER(dataObj).count--;

              //  dlfree(dataObj, procedure);
                if(procedure != NULL)
                {
                   free(procedure);
                   procedure = NULL;
                }
            }
        }

        procedure = nextIterProcedure;
    }
  //  ITS_TRACE_ERROR(("RemovePendingProceduresFromMemberDueToLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ITS_TRACE_DEBUG((
        "RemovePendingProceduresFromMemberDueToLock [FtGroupId: %u]: end with "
        "%u procedures pending\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        DSM_DATA_PROCEDURE_MANAGER(dataObj).count));          

    return ITS_SUCCESS;
}

/******************************************************************************
 *
 * ProcedureAllocateRow.
 *
 */
static void 
ProcedureAllocateRow(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* allocateRowMsg;
    char* trailer;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureAllocateRow [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    allocateRowMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(allocateRowMsg->discriminator == DSM_MSG_ALLOCATE_ROW);

    /* Deserialize trailer (i.e. key). */
    ITS_C_ASSERT(allocateRowMsg->u.allocateRow.klen <= DSM_MAX_KEY_LENGTH);
    trailer = msg;
    trailer += sizeof(DSM_Message);
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufKey, 
        trailer, 
        allocateRowMsg->u.allocateRow.klen);
    allocateRowMsg->u.allocateRow.key = DSM_DATA_LOCAL(dataObj).bufKey;

    /* Check total size validity. */
    ITS_C_ASSERT(size == 
        sizeof(DSM_Message) + 
        allocateRowMsg->u.allocateRow.klen);

    /* TODO: improve tracing by adding klen and key? */
   /* ITS_TRACE_ERROR((
        "ProcedureAllocateRow[FtGroupId:%u]:received"
        "tid:%u| "
        "tableId:%u| "
        "orig memb:%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        allocateRowMsg->u.allocateRow.tid,
        allocateRowMsg->u.allocateRow.tableId,
        allocateRowMsg->u.allocateRow.originMemberName));*/

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* allocPtr = NULL;
        DSM_RowHeader* tmp;
        DSM_RowHeader** list;
        ITS_TIME now;
        ITS_INT hash = 0;
        ITS_UINT round;
        ITS_UINT rowSize = allocateRowMsg->u.allocateRow.size;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if DSM or Table is locked by another member or
         * thread.
         */

        if (keepOn &&  
                (DsmIsLockedNotByMember(
                    dataObj,
                    allocateRowMsg->u.allocateRow.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    allocateRowMsg->u.allocateRow.originThreadId)))
        {
            allocPtr = NULL;
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_ALLOCATE_ROW,
                    allocateRowMsg->u.allocateRow.tid,
                    allocateRowMsg->u.allocateRow.tableId,
                    allocateRowMsg->u.allocateRow.originThreadId,
                    allocateRowMsg->u.allocateRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureAllocateRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureAllocateRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureAllocateRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureAllocateRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    allocateRowMsg->u.allocateRow.originMemberName,
                    allocateRowMsg->u.allocateRow.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    allocateRowMsg->u.allocateRow.originThreadId,
                    allocateRowMsg->u.allocateRow.tableId)))
        {
            allocPtr = NULL;
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_ALLOCATE_ROW,
                    allocateRowMsg->u.allocateRow.tid,
                    allocateRowMsg->u.allocateRow.tableId,
                    allocateRowMsg->u.allocateRow.originThreadId,
                    allocateRowMsg->u.allocateRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureAllocateRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureAllocateRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureAllocateRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureAllocateRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /* 
         * ALLOCATE ROW identical in all processes that are in NORMAL state.
         */
#if 0
/* ricardo FIX for prototype */

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Alloc [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Alloc [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }


/* END FIX */
#endif
        /* Add row header to rowSize and make it a multiple of word size. */
        /* Add extra word size (for malloc chunk size rounding). */
        if (keepOn)
        {
            rowSize += sizeof(DSM_RowHeader) + sizeof(ITS_UINT) - 1;
            rowSize &= ~(sizeof(ITS_UINT) - 1);
            rowSize += sizeof(ITS_UINT);
        }

        /* Allocate entry. */
        if (keepOn)
        {
            allocPtr = dlcalloc(dataObj, 1, rowSize);
            if (allocPtr == NULL)
            {
                error = ITS_ENOMEM;
                keepOn = ITS_FALSE;
            }
           // ITS_TRACE_ERROR(("dlcalloc ALLOCATE POINTER(%x)-------\n",allocPtr));
        }

        /* Allocate key. */
        if (keepOn)
        {
            round = allocateRowMsg->u.allocateRow.klen + sizeof(ITS_UINT) - 1;
            round &= ~(sizeof(ITS_UINT) - 1);

            allocPtr->key = dlcalloc(dataObj, 1, round);
            if (allocPtr->key == NULL)
            {
                dlfree(dataObj, allocPtr);
                error = ITS_ENOMEM;
                keepOn = ITS_FALSE;
                allocPtr = NULL;
            }                   
        //    ITS_TRACE_ERROR(("dlcalloc ALLOCATE KEY POINTER(%x)-------\n",allocPtr->key));
        }
   // ITS_TRACE_ERROR(("ProcedureAllocateRow:received tid %d|key %x|prt %x", allocateRowMsg->u.allocateRow.tid,allocPtr->key,allocPtr));

        /* Compute hash value. */
        if (keepOn)
        {
            hash = LocalHash(
                        allocateRowMsg->u.allocateRow.key,
                        allocateRowMsg->u.allocateRow.klen);
        }

        /* Lock hash table. */
        if (keepOn)
        {
            ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureAllocateRow [FtGroupId: %u]: MUTEX_AcquireMutex"
                    " failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
                dlfree(dataObj, allocPtr->key);
                dlfree(dataObj, allocPtr);
                error = ret;
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
     //       ITS_TRACE_ERROR(("ProcedureAllocateRow::HASH_FindEntry"));
            ret = HASH_FindEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        allocateRowMsg->u.allocateRow.tableId,
                        hash, 
                        (ITS_POINTER*)&tmp);

            if (ret == ITS_SUCCESS)
            {
                for (list = &tmp->next; 
                     (*list) != NULL; 
                     list = &((*list)->next))
                {
                    /* Check for duplicate keys. */
                    if ((*list)->klen == allocateRowMsg->u.allocateRow.klen &&
                        memcmp(
                            (*list)->key, 
                            allocateRowMsg->u.allocateRow.key, 
                            allocateRowMsg->u.allocateRow.klen) == 0)
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
                            allocateRowMsg->u.allocateRow.tableId,
                            hash,
                            (ITS_POINTER)allocPtr);
       //     ITS_TRACE_ERROR(("ProcedureAllocateRow::HASH_AddEntry"));

                if (ret != ITS_SUCCESS)
                {
                    dlfree(dataObj, allocPtr->key);
                    dlfree(dataObj, allocPtr);
                    error = ret;
                    keepOn = ITS_FALSE;
                    allocPtr = NULL;
                }
            }
        }

        /* Store key info. */
        if (keepOn)
        {
            memcpy(
                allocPtr->key,
                allocateRowMsg->u.allocateRow.key,
                allocateRowMsg->u.allocateRow.klen);
            allocPtr->klen = allocateRowMsg->u.allocateRow.klen;
         //   ITS_TRACE_ERROR(("ALLOCATE POINTER(%x)-------\n",allocPtr));
        }

        /* Lock row only if required. */
        if (keepOn && allocateRowMsg->u.allocateRow.withLock)
        {
            allocPtr->locked = ITS_TRUE;
            now = TIMERS_Time();
            allocPtr->lockTime = now;
        }

        /* Adjust number of entries in table. */
        if (keepOn)
        {
            DSM_DATA_TABLES_INFO(dataObj)
                [allocateRowMsg->u.allocateRow.tableId].entries++;
        }

        /* Adjust pointer to user data (row header is before). */
        if (keepOn)
        {
            allocPtr = allocPtr + 1;
//            ITS_TRACE_ERROR(("ProcedureAllocateRow:allocPtr %x",allocPtr));

        }
#if 0
/* ricardo FIX for prototype */

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Alloc [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Alloc [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }


/* END FIX for prototype */
#endif

        /* Unlock hash table if locked. */
        if (tablesLocked)
        {
            ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureAllocateRow [FtGroupId: %u]: MUTEX_ReleaseMutex "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    allocateRowMsg->u.allocateRow.originMemberName) == 0)
            {
                /* ALLOCATE ROW message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureAllocateRow [FtGroupId: %u]: DSM ALLOCATE ROW "
                    "message to self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: "
                        "RWLOCK_LockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            allocateRowMsg->u.allocateRow.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to find "
                        "Tcb for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        allocateRowMsg->u.allocateRow.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureAllocateRow [FtGroupId: %u]: found Tcb for Tid:"
                    " %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    allocateRowMsg->u.allocateRow.tid));

                /* Pass result of ALLOCATE ROW through Tcb. */
                tcb->result.discriminator = DSM_RESULT_ALLOCATE_ROW;
                tcb->result.u.allocateRow.allocPtr = allocPtr;
                tcb->result.u.allocateRow.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: "
                        "MUTEX_AcquireMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: CONDVAR_Signal "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureAllocateRow [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    allocateRowMsg->u.allocateRow.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureAllocateRow [FtGroupId: %u]: "
                        "RWLOCK_UnlockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureAllocateRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureAllocateRow [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* ALLOCATE ROW message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureAllocateRow [FtGroupId: %u]: DSM ALLOCATE ROW "
                    "message to other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any node) and before the SYNC LOCK message has been 
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            allocateRowMsg->u.allocateRow.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_ALLOCATE_ROW,
                    allocateRowMsg->u.allocateRow.tid,
                    allocateRowMsg->u.allocateRow.tableId,
                    allocateRowMsg->u.allocateRow.originThreadId,
                    allocateRowMsg->u.allocateRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureAllocateRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureAllocateRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureAllocateRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureAllocateRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureAllocateRow [FtGroupId: %u]: DSM ALLOCATE ROW message "
            "dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureAllocateRow [FtGroupId: %u]: DSM ALLOCATE ROW message "
            "dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureAllocateRow [FtGroupId: %u]: DSM ALLOCATE ROW message "
            "dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureAllocateRow [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureFindRow.
 *
 */
static void 
ProcedureFindRow(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_InstObject* instObj;
    DSM_Message* findRowMsg;
    char* trailer;
    int ret;

    instObj = DSM_DATA_INST_OBJECT(dataObj);

    ITS_TRACE_DEBUG((
        "ProcedureFindRow [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    findRowMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(findRowMsg->discriminator == DSM_MSG_FIND_ROW);

    /* Deserialize trailer (i.e. key). */
    ITS_C_ASSERT(findRowMsg->u.findRow.klen <= DSM_MAX_KEY_LENGTH);
    trailer = msg;
    trailer += sizeof(DSM_Message);
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufKey, 
        trailer, 
        findRowMsg->u.findRow.klen);
    findRowMsg->u.findRow.key = DSM_DATA_LOCAL(dataObj).bufKey;

    /* Check total size validity. */
    ITS_C_ASSERT(size == 
        sizeof(DSM_Message) + 
        findRowMsg->u.findRow.klen);

    /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "ProcedureFindRow [FtGroupId: %u]: received DSM FIND ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        findRowMsg->u.findRow.tid,
        findRowMsg->u.findRow.tableId,
        findRowMsg->u.findRow.withLock ? "true" : "false",
        findRowMsg->u.findRow.originThreadId,
        findRowMsg->u.findRow.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* findPtr = NULL;
        DSM_RowHeader* row;
        ITS_INT hash;
        ITS_TIME now;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if Dsm or Table is locked by another member or
         * thread.
         */

        if (keepOn &&  
                (DsmIsLockedNotByMember(
                    dataObj,
                    findRowMsg->u.findRow.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    findRowMsg->u.findRow.originThreadId)))
        {
            findPtr = NULL;
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_FIND_ROW,
                    findRowMsg->u.findRow.tid,
                    findRowMsg->u.findRow.tableId,
                    findRowMsg->u.findRow.originThreadId,
                    findRowMsg->u.findRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFindRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFindRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFindRow [FtGroupId: %u]: unacceptable state from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFindRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    findRowMsg->u.findRow.originMemberName,
                    findRowMsg->u.findRow.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    findRowMsg->u.findRow.originThreadId,
                    findRowMsg->u.findRow.tableId)))
        {
            findPtr = NULL;
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_FIND_ROW,
                    findRowMsg->u.findRow.tid,
                    findRowMsg->u.findRow.tableId,
                    findRowMsg->u.findRow.originThreadId,
                    findRowMsg->u.findRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFindRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFindRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFindRow [FtGroupId: %u]: unacceptable state from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFindRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /* 
         * FIND ROW identical in all processes that are in NORMAL state.
         */

        if (keepOn)
        {
            /* Compute hash value. */
            hash = LocalHash(
                        findRowMsg->u.findRow.key,
                        findRowMsg->u.findRow.klen);

            /* Lock hash table. */
            ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFindRow [FtGroupId: %u]: "
                    "MUTEX_AcquireMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
                error = ret;
                keepOn = ITS_FALSE;
                findPtr = NULL;
            }
            else
            {
                tablesLocked = ITS_TRUE;
            }
        }

        /* Lookup for row list in table according to hash value. */
        if (keepOn)
        {
            ret = HASH_FindEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        findRowMsg->u.findRow.tableId,
                        hash,
                        (ITS_POINTER*)&row);
            if (ret != ITS_SUCCESS)
            {
                error = ITS_ENOTFOUND;
                keepOn = ITS_FALSE;
                findPtr = NULL;
            }
        }

        /* Scan row list for correct row. */
        if (keepOn)
        {
            while (row != NULL)
            {
                if (row->klen == findRowMsg->u.findRow.klen && 
                    memcmp(
                        row->key, 
                        findRowMsg->u.findRow.key, 
                        findRowMsg->u.findRow.klen) == 0)
                {
                    break;
                }

                row = row->next;
            }

            if (row == NULL)
            {
                error = ITS_ENOTFOUND;
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
                error = ITS_EINUSE;
                keepOn = ITS_FALSE;
                findPtr = NULL;
            }
        }

        /* Lock row only if required. */
        if (keepOn && findRowMsg->u.findRow.withLock)
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
                    "ProcedureFindRow [FtGroupId: %u]: "
                    "MUTEX_ReleaseMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    findRowMsg->u.findRow.originMemberName) == 0)
            {
                /* FIND ROW message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureFindRow [FtGroupId: %u]: DSM FIND ROW message to"
                    " self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: "
                        "RWLOCK_LockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            findRowMsg->u.findRow.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: unable to find Tcb "
                        "for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        findRowMsg->u.findRow.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureFindRow [FtGroupId: %u]: found Tcb for Tid: "
                    "%u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    findRowMsg->u.findRow.tid));

                /* Pass result of FIND ROW through Tcb. */
                tcb->result.discriminator = DSM_RESULT_FIND_ROW;
                tcb->result.u.findRow.findPtr = findPtr;
                tcb->result.u.findRow.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: MUTEX_AcquireMutex "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: CONDVAR_Signal "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: MUTEX_ReleaseMutex "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureFindRow [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    findRowMsg->u.findRow.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFindRow [FtGroupId: %u]: RWLOCK_UnlockShared"
                        " failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureFindRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFindRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* FIND ROW message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureFindRow [FtGroupId: %u]: DSM FIND ROW message to"
                    " other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            findRowMsg->u.findRow.originMemberName) == 0)
        {        
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_FIND_ROW,
                    findRowMsg->u.findRow.tid,
                    findRowMsg->u.findRow.tableId,
                    findRowMsg->u.findRow.originThreadId,
                    findRowMsg->u.findRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFindRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFindRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFindRow [FtGroupId: %u]: unacceptable state from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFindRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFindRow [FtGroupId: %u]: DSM FIND ROW message dropped "
            "due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFindRow [FtGroupId: %u]: DSM FIND ROW message dropped "
            "due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFindRow [FtGroupId: %u]: DSM FIND ROW message dropped "
            "due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureFindRow [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureFreeRow.
 *
 */
static void
ProcedureFreeRow(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* freeRowMsg;
    char* trailer;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureFreeRow [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    freeRowMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(freeRowMsg->discriminator == DSM_MSG_FREE_ROW);

    /* Deserialize trailer (i.e. key). */
    ITS_C_ASSERT(freeRowMsg->u.freeRow.klen <= DSM_MAX_KEY_LENGTH);
    trailer = msg;
    trailer += sizeof(DSM_Message);
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufKey, 
        trailer, 
        freeRowMsg->u.freeRow.klen);
    freeRowMsg->u.freeRow.key = DSM_DATA_LOCAL(dataObj).bufKey;

    /* Check total size validity. */
    ITS_C_ASSERT(size == 
        sizeof(DSM_Message) + 
        freeRowMsg->u.freeRow.klen);

    /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "ProcedureFreeRow [FtGroupId: %u]: received DSM FREE ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "dataObject: 0x%X | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        freeRowMsg->u.freeRow.tid,
        freeRowMsg->u.freeRow.tableId,
        freeRowMsg->u.freeRow.objectInTable,
        freeRowMsg->u.freeRow.withLock ? "true" : "false",
        freeRowMsg->u.freeRow.originThreadId,
        freeRowMsg->u.freeRow.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        DSM_RowHeader* head;
        DSM_RowHeader** list;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if DSM or Table is locked by another member or
         * thread.
         */
        if (keepOn &&  
                 (DsmIsLockedNotByMember(
                    dataObj,
                    freeRowMsg->u.freeRow.originMemberName) ||
                  DsmIsLockedNotByThread(
                    dataObj,
                    freeRowMsg->u.freeRow.originThreadId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_FREE_ROW,
                    freeRowMsg->u.freeRow.tid,
                    freeRowMsg->u.freeRow.tableId,
                    freeRowMsg->u.freeRow.originThreadId,
                    freeRowMsg->u.freeRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFreeRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFreeRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFreeRow [FtGroupId: %u]: unacceptable state from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFreeRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    freeRowMsg->u.freeRow.originMemberName,
                    freeRowMsg->u.freeRow.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    freeRowMsg->u.freeRow.originThreadId,
                    freeRowMsg->u.freeRow.tableId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_FREE_ROW,
                    freeRowMsg->u.freeRow.tid,
                    freeRowMsg->u.freeRow.tableId,
                    freeRowMsg->u.freeRow.originThreadId,
                    freeRowMsg->u.freeRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFreeRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFreeRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFreeRow [FtGroupId: %u]: unacceptable state from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFreeRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /* 
         * FREE ROW identical in all processes that are in NORMAL state.
         */
#if 0
/* ricardo FIX for prototype */

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Alloc [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Alloc [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

/* FIX END */
#endif

        if (keepOn)
        {
            /* Deduce actual row pointer from object pointer. */
            row = (DSM_RowHeader*)
                    ((char*)freeRowMsg->u.freeRow.objectInTable - 
                        sizeof(DSM_RowHeader));

            /* Compute hash value. */
            hash = LocalHash(
                    freeRowMsg->u.freeRow.key,
                    freeRowMsg->u.freeRow.klen);

            /* Lock hash table. */
            ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFreeRow [FtGroupId: %u]: "
                    "MUTEX_AcquireMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
                error = ret;
                keepOn = ITS_FALSE;
            }
            else
            {
                tablesLocked = ITS_TRUE;
            }
        }

        /* Lookup for row list in table according to hash value. */
        if (keepOn)
        {
            ret = HASH_FindEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        freeRowMsg->u.freeRow.tableId,
                        hash,
                        (ITS_POINTER*)&head);
            if (ret != ITS_SUCCESS)
            {
                error = ITS_ENOTFOUND;
                keepOn = ITS_FALSE;
            }
        }

        /* Scan row list for correct row. */
        if (keepOn)
        {
            tmp = head;
            while (tmp != NULL)
            {
              //      ITS_TRACE_ERROR(("ROW TO BE FREED(%x)\n",row));
                if (tmp->klen == freeRowMsg->u.freeRow.klen &&
                    memcmp(
                        tmp->key,
                        freeRowMsg->u.freeRow.key,
                        freeRowMsg->u.freeRow.klen) == 0 &&
                    tmp == row)
                {
               //     ITS_TRACE_ERROR(("FOUND FREE ROW(%x)\n",tmp));
                    break;
                }
                
                tmp = tmp->next;
            }

            ITS_C_ASSERT(tmp != NULL);

            if (tmp == NULL)
            {
                error = ITS_EINVALIDARGS;
                keepOn = ITS_FALSE;
            }
        }

        /* Check row locked only if required. */
        if (keepOn && freeRowMsg->u.freeRow.withLock)
        {
            ITS_C_ASSERT(row->locked);

            if (!row->locked)
            {
                error = ITS_EROWNOTLOCKED;
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
                            freeRowMsg->u.freeRow.tableId,
                            hash);
                if (ret != ITS_SUCCESS)
                {
                    dlfree(dataObj, row->key);
                    dlfree(dataObj, row);

                    error = ret;
                    keepOn = ITS_FALSE;
                }
            }
            else
            {
                ret = HASH_AddEntry(
                            DSM_DATA_MEM_DATA(dataObj)->tables,
                            freeRowMsg->u.freeRow.tableId,
                            hash, 
                            (ITS_POINTER)head);
                if (ret != ITS_SUCCESS)
                {
                    dlfree(dataObj, row->key);
                    dlfree(dataObj, row);

                    error = ret;
                    keepOn = ITS_FALSE;
                }
            }
        }

        if (keepOn)
        {
       //     ITS_TRACE_ERROR(("FREED POINTER(%x)-------\n",row));
            dlfree(dataObj, row->key);
            dlfree(dataObj, row);
        }

        /* Adjust number of entries in table. */
        if (keepOn)
        {
            if (DSM_DATA_TABLES_INFO(dataObj)
                    [freeRowMsg->u.freeRow.tableId].entries > 0)
            {
                DSM_DATA_TABLES_INFO(dataObj)
                    [freeRowMsg->u.freeRow.tableId].entries--;
            }
        }

        /* Unlock hash table if locked. */
        if (tablesLocked)
        {
            ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFreeRow [FtGroupId: %u]: MUTEX_ReleaseMutex "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

#if 0
/* ricardo FIX for PROTOTYPE */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Alloc [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Alloc [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }



/* FIX END */
#endif

        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    freeRowMsg->u.freeRow.originMemberName) == 0)
            {
                /* FREE ROW message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureFreeRow [FtGroupId: %u]: DSM FREE ROW message to"
                    " self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: RWLOCK_LockShared "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            freeRowMsg->u.freeRow.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: unable to find Tcb "
                        "for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        freeRowMsg->u.freeRow.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureFreeRow [FtGroupId: %u]: found Tcb for Tid: "
                    "%u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    freeRowMsg->u.freeRow.tid));

                /* Pass result of FREE ROW through Tcb. */
                tcb->result.discriminator = DSM_RESULT_FREE_ROW;
                tcb->result.u.freeRow.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: MUTEX_AcquireMutex "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: CONDVAR_Signal "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureFreeRow [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    freeRowMsg->u.freeRow.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureFreeRow [FtGroupId: %u]: RWLOCK_UnlockShared"
                        " failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureFreeRow [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureFreeRow [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* FREE ROW message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureFreeRow [FtGroupId: %u]: DSM FREE ROW message to"
                    " other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            freeRowMsg->u.freeRow.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_FREE_ROW,
                    freeRowMsg->u.freeRow.tid,
                    freeRowMsg->u.freeRow.tableId,
                    freeRowMsg->u.freeRow.originThreadId,
                    freeRowMsg->u.freeRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureFreeRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureFreeRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureFreeRow [FtGroupId: %u]: unacceptable state from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureFreeRow [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFreeRow [FtGroupId: %u]: DSM FREE ROW message dropped "
            "due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFreeRow [FtGroupId: %u]: DSM FREE ROW message dropped "
            "due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureFreeRow [FtGroupId: %u]: DSM FREE ROW message dropped "
            "due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureFreeRow [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureCommitRow.
 *
 */
static void
ProcedureCommitRow(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* commitRowMsg;
    char* trailer;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureCommitRow [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    commitRowMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(commitRowMsg->discriminator == DSM_MSG_COMMIT_ROW);

    /* Deserialize trailer #1 (i.e. key). */
    ITS_C_ASSERT(commitRowMsg->u.commitRow.klen <= DSM_MAX_KEY_LENGTH);
    trailer = msg;
    trailer += sizeof(DSM_Message);
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufKey, 
        trailer, 
        commitRowMsg->u.commitRow.klen);
    commitRowMsg->u.commitRow.key = DSM_DATA_LOCAL(dataObj).bufKey;

    /* Deserialize trailer #2 (i.e. dataObject). */
    ITS_C_ASSERT(commitRowMsg->u.commitRow.size <= DSM_MAX_OBJECT_SIZE);
    trailer += commitRowMsg->u.commitRow.klen;
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufObject, 
        trailer, 
        commitRowMsg->u.commitRow.size);
    commitRowMsg->u.commitRow.object = 
        (ITS_POINTER)DSM_DATA_LOCAL(dataObj).bufObject;

    /* Check total size validity. */
    ITS_C_ASSERT(size == 
        sizeof(DSM_Message) + 
        commitRowMsg->u.commitRow.klen +
        commitRowMsg->u.commitRow.size);

    /* TODO: improve tracing by adding klen, key and contents of dataObject? */
   /* ITS_TRACE_ERROR((
        "ProcedureCommitRow[FtGroupId:%u]:received|"
        "tid:%u| "
        "tableId:%u| "
        "orig memb:%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        commitRowMsg->u.commitRow.tid,
        commitRowMsg->u.commitRow.tableId,
        commitRowMsg->u.commitRow.originMemberName));*/

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if Dsm or Table is locked by another member or
         * thread.
         */

        if (keepOn &&  
                (DsmIsLockedNotByMember(
                    dataObj,
                    commitRowMsg->u.commitRow.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    commitRowMsg->u.commitRow.originThreadId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

                ITS_TRACE_CRITICAL((
                    "ProcedureCommitRow :TableId[%d] Tid[%d] 1. INSERTING COMMIT IN PENDING LIST ",
                    commitRowMsg->u.commitRow.tableId,commitRowMsg->u.commitRow.tid));
            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_COMMIT_ROW,
                    commitRowMsg->u.commitRow.tid,
                    commitRowMsg->u.commitRow.tableId,
                    commitRowMsg->u.commitRow.originThreadId,
                    commitRowMsg->u.commitRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureCommitRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureCommitRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureCommitRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureCommitRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    commitRowMsg->u.commitRow.originMemberName,
                    commitRowMsg->u.commitRow.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    commitRowMsg->u.commitRow.originThreadId,
                    commitRowMsg->u.commitRow.tableId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

                ITS_TRACE_CRITICAL((
                    "ProcedureCommitRow :TableId[%d] Tid[%d] 2. INSERTING COMMIT IN PENDING LIST ",
                    commitRowMsg->u.commitRow.tableId,commitRowMsg->u.commitRow.tid));
            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_COMMIT_ROW,
                    commitRowMsg->u.commitRow.tid,
                    commitRowMsg->u.commitRow.tableId,
                    commitRowMsg->u.commitRow.originThreadId,
                    commitRowMsg->u.commitRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureCommitRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureCommitRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureCommitRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureCommitRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /*
         * COMMIT ROW identical in all processes that are in NORMAL state.
         */

#if 0
/* ricardo FIX for prototype */
    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Commit [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Commit [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

/* FIX END */
#endif

        if (keepOn)
        {
            /* Deduce actual row pointer from object pointer. */
            row = (DSM_RowHeader*)
                    ((char*)commitRowMsg->u.commitRow.objectInTable - 
                        sizeof(DSM_RowHeader));

            /* Compute hash value. */
            hash = LocalHash(
                    commitRowMsg->u.commitRow.key,
                    commitRowMsg->u.commitRow.klen);

            /* Lock hash table. */
            ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureCommitRow [FtGroupId: %u]: "
                    "MUTEX_AcquireMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
                error = ret;
                keepOn = ITS_FALSE;
            }
            else
            {
                tablesLocked = ITS_TRUE;
            }
        }

        /* Look up for row list in table according to hash value. */
        if (keepOn)
        {
            ret = HASH_FindEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        commitRowMsg->u.commitRow.tableId,
                        hash,
                        (ITS_POINTER*)&tmp);

            if (ret != ITS_SUCCESS)
            {
                error = ITS_ENOTFOUND;
                keepOn = ITS_FALSE;
            }
        }

        /* Scan row list for correct row. */
        if (keepOn)
        {
            while (tmp != NULL)
            {
                if (tmp->klen == commitRowMsg->u.commitRow.klen &&
                    memcmp(
                        tmp->key,
                        commitRowMsg->u.commitRow.key,
                        commitRowMsg->u.commitRow.klen) == 0 &&
                    tmp == row)
                {
   //             ITS_TRACE_ERROR(("FOUND COMMIT POINTER(%x)-------\n",tmp));
                    break;
                }
    //            ITS_TRACE_ERROR(("COMMIT POINTER(%x)-------\n",tmp));
                
                tmp = tmp->next;
            }

            ITS_C_ASSERT(tmp != NULL);

            if (tmp == NULL)
            {
                error = ITS_EINVALIDARGS;
                keepOn = ITS_FALSE;
            }
        }

        /* Check row locked only if required. */
        if (keepOn && commitRowMsg->u.commitRow.withLock)
        {
            ITS_C_ASSERT(row->locked);

            if (!row->locked)
            {
                error = ITS_EROWNOTLOCKED;
                keepOn = ITS_FALSE;
            }
        }

        /* Update object. */
        if (keepOn)
        {
            memcpy(
                commitRowMsg->u.commitRow.objectInTable,
                commitRowMsg->u.commitRow.object,
                commitRowMsg->u.commitRow.size);
        }
        
        /* Unlock row only if required. */
        if (keepOn && commitRowMsg->u.commitRow.withLock)
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
                    "ProcedureCommitRow [FtGroupId: %u]: MUTEX_ReleaseMutex "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

#if 0
/* ricardo FIX for prototype */

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Commit [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Commit [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }


/* FIX END */
#endif

        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    commitRowMsg->u.commitRow.originMemberName) == 0)
            {
                /* COMMIT ROW message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureCommitRow [FtGroupId: %u]: DSM COMMIT ROW "
                    "message to self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: RWLOCK_LockShared"
                        " failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            commitRowMsg->u.commitRow.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: unable to find "
                        "Tcb for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        commitRowMsg->u.commitRow.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureCommitRow [FtGroupId: %u]: found Tcb for Tid: "
                    "%u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    commitRowMsg->u.commitRow.tid));

                /* Pass result of COMMIT ROW through Tcb. */
                tcb->result.discriminator = DSM_RESULT_COMMIT_ROW;
                tcb->result.u.commitRow.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: "
                        "MUTEX_AcquireMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: CONDVAR_Signal "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureCommitRow [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    commitRowMsg->u.commitRow.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureCommitRow [FtGroupId: %u]: "
                        "RWLOCK_UnlockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureCommitRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureCommitRow [FtGroupId: %u]: unable to recover"
                        " from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* COMMIT ROW message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureCommitRow [FtGroupId: %u]: DSM COMMIT ROW "
                    "message to other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            commitRowMsg->u.commitRow.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_COMMIT_ROW,
                    commitRowMsg->u.commitRow.tid,
                    commitRowMsg->u.commitRow.tableId,
                    commitRowMsg->u.commitRow.originThreadId,
                    commitRowMsg->u.commitRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureCommitRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureCommitRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureCommitRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureCommitRow [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureCommitRow [FtGroupId: %u]: DSM COMMIT ROW message "
            "dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureCommitRow [FtGroupId: %u]: DSM COMMIT ROW message "
            "dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureCommitRow [FtGroupId: %u]: DSM COMMIT ROW message "
            "dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureCommitRow [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureJoinInfo.
 *
 */
static void 
ProcedureJoinInfo(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* joinInfoMsg;
    DSM_Message syncLockMsg;
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureJoinInfo [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_ERROR((
        "ProcedureJoinInfo [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size == sizeof(DSM_Message));

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    joinInfoMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(joinInfoMsg->discriminator == DSM_MSG_JOIN_INFO);

    ITS_TRACE_ERROR((
        "ProcedureJoinInfo [FtGroupId: %u]: received DSM JOIN INFO message | "
        "tid: %u | "
        "origin member name: %s | "
        "destination member name: %s | "
        "origin member sync mem IP address: %s | "
        "origin member sync mem IP port: %u | "
        "origin member nodeId: %u | "
        "origin member processId: %u | "
        "origin member state: %s | "
        "DSM_DATA_LOCAL(dataObj).memberName : %s \n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        joinInfoMsg->u.joinInfo.tid,
        joinInfoMsg->u.joinInfo.originMemberName,
        joinInfoMsg->u.joinInfo.destinationMemberName,
        joinInfoMsg->u.joinInfo.originMemberSyncMemIpAddress,
        joinInfoMsg->u.joinInfo.originMemberSyncMemIpPort,
        joinInfoMsg->u.joinInfo.originMemberNodeId,
        joinInfoMsg->u.joinInfo.originMemberProcessId,
        StateToStr(joinInfoMsg->u.joinInfo.originMemberState),
        DSM_DATA_LOCAL(dataObj).memberName));
     ITS_TRACE_ERROR(( "ProcedureJoinInfo :DSM_DATA_LOCAL(dataObj).memberName : %s \n",DSM_DATA_LOCAL(dataObj).memberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            joinInfoMsg->u.joinInfo.originMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoinInfo [FtGroupId: %u]: DSM JOIN INFO message to "
            "origin (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do (ignore). */
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                joinInfoMsg->u.joinInfo.destinationMemberName) == 0)
    {
        DSM_RemoteMember* remoteMember;

        ITS_TRACE_ERROR((
            "ProcedureJoinInfo [FtGroupId: %u]: DSM JOIN INFO message to "
            "destination (i.e. previously joining member)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* 
         * Specific processing in state JOINING plus other conditions (see
         * afterward).
         */

        /* Update remote member fields: 
         * - syncMemIpAddress.
         * - syncMemIpPort.
         * - nodeId.
         * - processId.
         * - lastKnownState.
         */
        remoteMember = 
            RemoteMemberRetrieve(
                dataObj, 
                joinInfoMsg->u.joinInfo.originMemberName);

        if (remoteMember != NULL)
        {
            strcpy(
                remoteMember->syncMemIpAddress, 
                joinInfoMsg->u.joinInfo.originMemberSyncMemIpAddress);
            remoteMember->syncMemIpPort = 
                joinInfoMsg->u.joinInfo.originMemberSyncMemIpPort;
            remoteMember->nodeId =
                joinInfoMsg->u.joinInfo.originMemberNodeId;
            remoteMember->processId =
                joinInfoMsg->u.joinInfo.originMemberProcessId;
            remoteMember->lastKnownState =
                joinInfoMsg->u.joinInfo.originMemberState;
        }
        else
        {
            ITS_TRACE_ERROR((
                "ProcedureJoinInfo [FtGroupId: %u]: failed to find remote "
                "member %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                joinInfoMsg->u.joinInfo.originMemberName));
        }

        /*
         * If state is JOINING and remote member is a master member in NORMAL
         * state then transit to SYNC WAIT, post MASTER-JOIN semaphore and if
         * synchronization is implicit send DSM SYNC LOCK message to master 
         * member.
         */

        if (IsDsmStateJoining(DSM_DATA_STATE_DATA(dataObj).state) &&
            remoteMember != NULL &&
            HasMasterFtGroupMember(
                dataObj, 
                remoteMember->nodeId, 
                remoteMember->processId) &&
            IsDsmStateNormal(remoteMember->lastKnownState))
        {
            /* Change state to SYNC WAIT. */
            ITS_TRACE_ERROR((
                "ProcedureJoinInfo [FtGroupId: %u]: change state to SYNC "
                "WAIT\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_WAIT;

            /* Post MASTER-JOIN semaphore. */
            ITS_TRACE_ERROR((
                "ProcedureJoinInfo [FtGroupId: %u]: ready to post MASTER-JOIN "
                "semaphore\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).masterSema);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureJoinInfo [FtGroupId: %u]: SEMA_PostSemaphore "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureJoinInfo [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureJoinInfo [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ITS_TRACE_ERROR((
                "ProcedureJoinInfo [FtGroupId: %u]: MASTER-JOIN semaphore "
                "posted\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            if (!DSM_INST_DSM_SYNC_EXPLICIT(instObj))
            {
                /* 
                 * Update SYNC related data (future slave). Done again in 
                 * ProcedureSyncLock. Used as a marker of DSM SYNC LOCK message
                 * already sent by ProcedureLeave, ProcedureDisconnect and 
                 * ProcedureNetworkChange.
                 */
                strcpy(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
                    DSM_DATA_LOCAL(dataObj).memberName);
                strcpy(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
                    remoteMember->memberName);

                syncLockMsg.discriminator = DSM_MSG_SYNC_LOCK;
                syncLockMsg.u.syncLock.tid = AllocateTid(dataObj);
                strcpy(
                    syncLockMsg.u.syncLock.syncMasterMemberName,
                    remoteMember->memberName);
                strcpy(
                    syncLockMsg.u.syncLock.syncSlaveMemberName,
                    DSM_DATA_LOCAL(dataObj).memberName);

                ITS_TRACE_ERROR((
                    "ProcedureJoinInfo [FtGroupId: %u]: ready to send DSM SYNC"
                    " LOCK message | "
                    "tid: %u | "
                    "slave member name: %s | "
                    "master member name: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    syncLockMsg.u.syncLock.tid,
                    syncLockMsg.u.syncLock.syncSlaveMemberName,
                    syncLockMsg.u.syncLock.syncMasterMemberName));
  //  ITS_TRACE_ERROR(("ProcedureJoinInfo:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

                ret = GCS_Multicast(
                        DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
                        DSM_DATA_LOCAL(dataObj).groupName,
                        DSM_MSG_SYNC_LOCK,
                        sizeof(DSM_Message),
                        (const char*)&syncLockMsg);
                if (ret < 0)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureJoinInfo [FtGroupId: %u]: GCS_Multicast "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureJoinInfo [FtGroupId: %u]: unable to recover "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureJoinInfo [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_ERROR((
                    "ProcedureJoinInfo [FtGroupId: %u]: DSM SYNC LOCK message "
                    "successfully sent\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }
        }
        else
        {
            /* Nothing to do. */
        }
    }
    else if (strcmp(
                "others",
                joinInfoMsg->u.joinInfo.destinationMemberName) == 0)
    {
        DSM_RemoteMember* remoteMember;

        ITS_TRACE_ERROR((
            "ProcedureJoinInfo [FtGroupId: %u]: DSM JOIN INFO message to "
            "others (i.e. from previously joining member)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Update remote member fields: 
         * - syncMemIpAddress.
         * - syncMemIpPort.
         * - nodeId.
         * - processId.
         * - lastKnownState.
         */
        remoteMember = 
            RemoteMemberRetrieve(
                dataObj, 
                joinInfoMsg->u.joinInfo.originMemberName);

        if (remoteMember != NULL)
        {
            strcpy(
                remoteMember->syncMemIpAddress, 
                joinInfoMsg->u.joinInfo.originMemberSyncMemIpAddress);
            remoteMember->syncMemIpPort = 
                joinInfoMsg->u.joinInfo.originMemberSyncMemIpPort;
            remoteMember->nodeId =
                joinInfoMsg->u.joinInfo.originMemberNodeId;
            remoteMember->processId =
                joinInfoMsg->u.joinInfo.originMemberProcessId;
            remoteMember->lastKnownState =
                joinInfoMsg->u.joinInfo.originMemberState;
        }
        else
        {
            ITS_TRACE_ERROR((
                "ProcedureJoinInfo [FtGroupId: %u]: failed to find remote "
                "member %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                joinInfoMsg->u.joinInfo.originMemberName));
        }
    }
    else
    {
        ITS_TRACE_ERROR((
            "ProcedureJoinInfo [FtGroupId: %u]: DSM JOIN INFO message to "
            "non-destination (i.e. from others to previously joining "
            "member)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do. */
    }

    ITS_TRACE_ERROR((
        "ProcedureJoinInfo [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncRequest.
 *
 */

static void
SubProcedureSyncRequestToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncRequestMsg)
{
    /* Nothing to do (ignore request). */
}

static void
SubProcedureSyncRequestToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncRequestMsg)
{
    /* Nothing to do (ignore request). */
}

static void
SubProcedureSyncRequestToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncRequestMsg)
{
    DSM_Message syncLockMsg;
    int ret;

    /* 
     * Update of SYNC related data (since upcoming slave). Done again in
     * ProcedureSyncLock. Used as a marker of DSM SYNC LOCK message already
     * sent by ProcedureLeave, ProcedureDisconnect and ProcedureNetworkChange.
     */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        syncRequestMsg->u.syncRequest.syncMasterMemberName);

    syncLockMsg.discriminator = DSM_MSG_SYNC_LOCK;
    syncLockMsg.u.syncLock.tid = AllocateTid(dataObj);
    strcpy(
        syncLockMsg.u.syncLock.syncMasterMemberName,
        syncRequestMsg->u.syncRequest.syncMasterMemberName);
    strcpy(
        syncLockMsg.u.syncLock.syncSlaveMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]: ready to send DSM SYNC LOCK"
        " message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncLockMsg.u.syncLock.tid,
        syncLockMsg.u.syncLock.syncSlaveMemberName,
        syncLockMsg.u.syncLock.syncMasterMemberName));

    ret = GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_SYNC_LOCK,
            sizeof(DSM_Message),
            (const char*)&syncLockMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncRequest [FtGroupId: %u]: GCS_Multicast failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncRequest [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncRequest [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]: DSM SYNC LOCK message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
SubProcedureSyncRequestToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncRequestMsg)
{
    SubProcedureSyncRequestToSlaveInStateNormal(
        dataObj,
        syncRequestMsg);
}

static void
SubProcedureSyncRequestToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncRequestMsg)
{
    /* TODO: review. Possible only if repetitive calls to SynchronizeDsm. */

    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncRequestToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE],
    DSM_Message* syncRequestMsg)
{
    int ret;

    ret = InsertPendingProcedureDueToSync(
            dataObj,
            DSM_PROCEDURE_SYNC_REQUEST,
            syncRequestMsg->u.syncRequest.tid,
            (ITS_UINT)(-1), /* Irrelevant. */
            (ITS_UINT)(-1), /* Irrelevant. */
            syncRequestMsg->u.syncRequest.syncSlaveMemberName,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg,
            "ProcedureSyncRequest");
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncRequest [FtGroupId: %u]: "
            "InsertPendingProcedureDueToSync failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncRequest [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncRequest [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }
}

static void
SubProcedureSyncRequestToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE],
    DSM_Message* syncRequestMsg)
{
    SubProcedureSyncRequestToSlaveInStateSyncMaster(
        dataObj,
        service,
        sender,
        numGroups,
        groups,
        size,
        msg,
        syncRequestMsg);
}

static void
SubProcedureSyncRequestToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncRequest(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncRequestMsg;

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size == sizeof(DSM_Message));

    syncRequestMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncRequestMsg->discriminator == DSM_MSG_SYNC_REQUEST);

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]: received DSM SYNC REQUEST "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncRequestMsg->u.syncRequest.tid,
        syncRequestMsg->u.syncRequest.syncSlaveMemberName,
        syncRequestMsg->u.syncRequest.syncMasterMemberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncRequestMsg->u.syncRequest.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncRequest [FtGroupId: %u]: DSM SYNC REQUEST message to"
            " slave (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncRequestToSlaveInStateInitial(
                dataObj,
                syncRequestMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncRequestToSlaveInStateJoining(
                dataObj,
                syncRequestMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncRequestToSlaveInStateNormal(
                dataObj,
                syncRequestMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncRequestToSlaveInStateSyncWait(
                dataObj,
                syncRequestMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncRequestToSlaveInStateSyncSlave(
                dataObj,
                syncRequestMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncRequestToSlaveInStateSyncMaster(
                dataObj,
                service,
                sender,
                numGroups,
                groups,
                size,
                msg,
                syncRequestMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncRequestToSlaveInStateSyncNeutral(
                dataObj,
                service,
                sender,
                numGroups,
                groups,
                size,
                msg,
                syncRequestMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncRequestToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }

        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncRequestMsg->u.syncRequest.syncMasterMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncRequest [FtGroupId: %u]: DSM SYNC REQUEST message to"
            " master\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do. */
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncRequest [FtGroupId: %u]: DSM SYNC REQUEST message to"
            " non-slave and non-master member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncRequest [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncLock.
 *
 */

static void
SubProcedureSyncLockToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do (ignore request). */
}

static void
SubProcedureSyncLockToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do (ignore request). */
}

static void
SubProcedureSyncLockToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    int ret;

    /* 
     * Lock state: must not change to SYNC state if locked by another thread. 
     */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Change state to SYNC SLAVE. */
    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: change state to SYNC SLAVE\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_SLAVE;

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Update SYNC related data. */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        syncLockMsg->u.syncLock.syncMasterMemberName);

    /* 
     * Acquire SYNC RWLock with write priviledge. To be released by
     * other procedures (e.g. ProcedureSyncUnlock).
     */

    ret = RWLOCK_LockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }
}

static void
SubProcedureSyncLockToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToSlaveInStateNormal(
        dataObj,
        syncLockMsg);
}

static void
SubProcedureSyncLockToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE],
    DSM_Message* syncLockMsg)
{
    int ret;

    ret = InsertPendingProcedureDueToSync(
            dataObj,
            DSM_PROCEDURE_SYNC_LOCK,
            syncLockMsg->u.syncLock.tid,
            (ITS_UINT)(-1), /* Irrelevant. */
            (ITS_UINT)(-1), /* Irrelevant. */
            syncLockMsg->u.syncLock.syncSlaveMemberName,
            service,
            sender,
            numGroups,
            groups,
            size,
            msg,
            "ProcedureSyncLock");
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: "
            "InsertPendingProcedureDueToSync failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }
}

static void
SubProcedureSyncLockToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE],
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToSlaveInStateSyncSlave(
        dataObj,
        service,
        sender,
        numGroups,
        groups,
        size,
        msg,
        syncLockMsg);
}

static void
SubProcedureSyncLockToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE],
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToSlaveInStateSyncSlave(
        dataObj,
        service,
        sender,
        numGroups,
        groups,
        size,
        msg,
        syncLockMsg);
}

static void
SubProcedureSyncLockToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockToMasterInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    DSM_Message syncInvalidMasterMsg;
    ITS_UINT tid;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: master state is not NORMAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Multicast invalid master (chosen master state is not NORMAL). */

    tid = AllocateTid(dataObj);

    syncInvalidMasterMsg.discriminator = DSM_MSG_SYNC_INVALID_MASTER;

    syncInvalidMasterMsg.u.syncInvalidMaster.tid = tid;
    strcpy(
        syncInvalidMasterMsg.u.syncInvalidMaster.syncMasterMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    strcpy(
        syncInvalidMasterMsg.u.syncInvalidMaster.syncSlaveMemberName,
        syncLockMsg->u.syncLock.syncSlaveMemberName);
    syncInvalidMasterMsg.u.syncInvalidMaster.masterState = 
        DSM_DATA_STATE_DATA(dataObj).state;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: ready to send DSM SYNC INVALID "
        "MASTER "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "master state: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncInvalidMasterMsg.u.syncInvalidMaster.tid,
        syncInvalidMasterMsg.u.syncInvalidMaster.syncSlaveMemberName,
        syncInvalidMasterMsg.u.syncInvalidMaster.syncMasterMemberName,
        syncInvalidMasterMsg.u.syncInvalidMaster.masterState));

    ret = GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_INVALID_MASTER,
                sizeof(DSM_Message),
                (const char*)&syncInvalidMasterMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC INVALID MASTER message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
SubProcedureSyncLockToMasterInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToMasterInStateInitial(
        dataObj,
        syncLockMsg);
}

static void
SubProcedureSyncLockToMasterInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    ITS_UINT numSyncMemMsg      = 0;
    ITS_UINT syncSize           = 0;
    ITS_UINT dataSize           = 0;
    ITS_UINT remainderDataSize  = 0;

    DSM_Message* syncMemMsg;
    char buf[sizeof(DSM_Message) + DSM_MAX_SYNC_MEM_DATA_SIZE];
    ITS_UINT i;
    int ret;

    /* 
     * Lock state: must not change to SYNC state if locked by another thread. 
     */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Change state to SYNC MASTER. */
    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: change state to SYNC MASTER\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_MASTER;

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Update SYNC related data. */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        syncLockMsg->u.syncLock.syncSlaveMemberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);

    /* 
     * Acquire SYNC RWLock with write priviledge. To be released by other
     * procedures (e.g. ProcedureSyncUnlock).
     */

    ret = RWLOCK_LockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);

    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_C_ASSERT(
        !(DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp && 
          DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs));

    ITS_C_ASSERT(
        DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp ||
        DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs);

    if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp)
    {
        DSM_Message syncMemTcpMsg;

        /*
         * Synchronize slave DSM memory with master DSM memory using
         * TCP. 
         */

        /* 
         * Send SYNC MEM TCP message (command SLAVE DO CONNECT).
         */

        syncMemTcpMsg.discriminator = DSM_MSG_SYNC_MEM_TCP;
        syncMemTcpMsg.u.syncMemTcp.tid = AllocateTid(dataObj);
        strcpy(
            syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
            DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName);
        strcpy(
            syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
            DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName);
        syncMemTcpMsg.u.syncMemTcp.command = 
            DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT;
        syncMemTcpMsg.u.syncMemTcp.size = 0;

        ITS_TRACE_DEBUG((
            "ProcedureSyncLock [FtGroupId: %u]: ready to send DSM SYNC MEM TCP"
            " message | "
            "tid: %u | "
            "slave member name: %s | "
            "master member name: %s | "
            "command: %s | "
            "size: %u\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncMemTcpMsg.u.syncMemTcp.tid,
            syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
            syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
            SyncMemTcpCmdToStr(syncMemTcpMsg.u.syncMemTcp.command),
            syncMemTcpMsg.u.syncMemTcp.size));

        ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_MEM_TCP,
                sizeof(DSM_Message),
                (const char*)&syncMemTcpMsg);
        if (ret < 0)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncLock [FtGroupId: %u]: GCS_Multicast failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        
            ITS_TRACE_CRITICAL((
                "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }

        ITS_TRACE_DEBUG((
            "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC MEM TCP message "
            "successfully sent\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs)
    {
        /*
         * Synchronize slave DSM memory with master DSM memory using
         * GCS. 
         */

        /* 
         * Loop to send as many SYNC MEM messages as necessary to 
         * synchronize DSM memory of slave with DSM memory of master. 
         * Last SYNC MEM message is marked as last to allow the slave
         * to send back a SYNC UNLOCK message. The case of SYNC UNLOCK
         * message never received is handled through membership change
         * (and messages).
         */

        /* 
         * Synchronize only relevant (i.e. already allocated) 
         * memory. 
         */
        syncSize = DSM_DATA_MEM_DATA(dataObj)->curbrk - 
                        (ITS_POINTER)DSM_DATA_SYS_MAP_ADDR(dataObj);

        ITS_C_ASSERT(syncSize <= DSM_DATA_MEM_DATA(dataObj)->size);
    
        numSyncMemMsg = syncSize / DSM_MAX_SYNC_MEM_DATA_SIZE;

        remainderDataSize = syncSize % DSM_MAX_SYNC_MEM_DATA_SIZE;

        if (remainderDataSize > 0)
        {
            numSyncMemMsg++;
        }

        /* At least one SYNC MEM message (even if empty). */
        if (numSyncMemMsg == 0)
        {
            numSyncMemMsg++; 
        }

        /* Special case for SYNC MEM last message. */
        if (remainderDataSize == 0)
        {
            remainderDataSize = DSM_MAX_SYNC_MEM_DATA_SIZE;
        }

        /* Reset. */
        DSM_DATA_MEM_DATA(dataObj)->cursync = DSM_DATA_SYS_MAP_ADDR(dataObj);

        for (i = 1; i <= numSyncMemMsg; i++)
        {
            if (i != numSyncMemMsg)
            {
                /* Not last one. */

                dataSize = DSM_MAX_SYNC_MEM_DATA_SIZE;
            }
            else
            {
                /* Last one. */

                dataSize = remainderDataSize; /* might be zero. */
            }

#if defined(DEBUG) || defined(_DEBUG)
            memset(
                buf, 
                0, 
                sizeof(DSM_Message) + DSM_MAX_SYNC_MEM_DATA_SIZE);
#endif /* defined(DEBUG) || defined(_DEBUG) */

            syncMemMsg = (DSM_Message*)buf;
            syncMemMsg->discriminator   = DSM_MSG_SYNC_MEM;
            syncMemMsg->u.syncMem.tid   = AllocateTid(dataObj);
            syncMemMsg->u.syncMem.seq   = i;
            if (i == numSyncMemMsg)
            {
                syncMemMsg->u.syncMem.last = ITS_TRUE;
            }
			else
			{
				syncMemMsg->u.syncMem.last = ITS_FALSE;
			}
            memcpy(
                syncMemMsg->u.syncMem.syncSlaveMemberName,
                syncLockMsg->u.syncLock.syncSlaveMemberName,
                GCS_MAX_GROUP_NAME);
            memcpy(
                syncMemMsg->u.syncMem.syncMasterMemberName,
                DSM_DATA_LOCAL(dataObj).memberName,
                GCS_MAX_GROUP_NAME);
            syncMemMsg->u.syncMem.size = dataSize;
            memcpy(
                syncMemMsg->u.syncMem.data,
                DSM_DATA_MEM_DATA(dataObj)->cursync,
                dataSize);

            DSM_DATA_MEM_DATA(dataObj)->cursync += dataSize;

            ITS_TRACE_DEBUG((
                "ProcedureSyncLock [FtGroupId: %u]: ready to send DSM SYNC MEM"
                " message | "
                "tid: %u | "
                "seq: %u | "
                "last: %s | "
                "slave member name: %s | "
                "master member name: %s | "
                "size: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                syncMemMsg->u.syncMem.tid,
                syncMemMsg->u.syncMem.seq,
                syncMemMsg->u.syncMem.last ? "true" : "false",
                syncMemMsg->u.syncMem.syncSlaveMemberName,
                syncMemMsg->u.syncMem.syncMasterMemberName,
                syncMemMsg->u.syncMem.size));

            /*
             * Note: by default use UNICAST by using slave member name
             * instead of DSM_DATA_LOCAL(dataObj).groupName. 
             */

            ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
#if defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        DSM_DATA_LOCAL(dataObj).groupName,
#else // !defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        syncLockMsg->u.syncLock.syncSlaveMemberName,
#endif // defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        DSM_MSG_SYNC_MEM,
                        sizeof(DSM_Message) + dataSize,
                        (const char*)syncMemMsg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ProcedureSyncLock [FtGroupId: %u]: GCS_Multicast failed: "
                    "%d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureSyncLock [FtGroupId: %u]: unable to recover from"
                    " previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureSyncLock [FtGroupId: %u]: unable to recover from"
                    " error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC MEM message "
                "successfully sent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }
}

static void
SubProcedureSyncLockToMasterInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToMasterInStateInitial(
        dataObj,
        syncLockMsg);
}

static void
SubProcedureSyncLockToMasterInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */

    /* TODO: review. */
}

static void
SubProcedureSyncLockToMasterInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */

    /* TODO: review. */
}

static void
SubProcedureSyncLockToMasterInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */

    /* TODO: review. */
}

static void
SubProcedureSyncLockToMasterInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockToNeutralInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    int ret;

    /* 
     * Lock state: must not change to SYNC state if locked by an other thread. 
     */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Save neutral member state. */
    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState = 
        DSM_DATA_STATE_DATA(dataObj).state;

    /* Change state to SYNC NEUTRAL. */
    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: change state to SYNC NEUTRAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_NEUTRAL;

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Update SYNC related data. */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        syncLockMsg->u.syncLock.syncSlaveMemberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        syncLockMsg->u.syncLock.syncMasterMemberName);

    /* 
     * Acquire SYNC RWLock with write priviledge. To be released by other
     * procedures (e.g. ProcedureSyncUnlock).
     */

    ret = RWLOCK_LockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }
}

static void
SubProcedureSyncLockToNeutralInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToNeutralInStateInitial(
        dataObj,
        syncLockMsg);
}

static void
SubProcedureSyncLockToNeutralInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    SubProcedureSyncLockToNeutralInStateInitial(
        dataObj,
        syncLockMsg);
}

static void
SubProcedureSyncLockToNeutralInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockToNeutralInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockToNeutralInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockToNeutralInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockToNeutralInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncLock(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncLockMsg;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_ERROR((
        "ProcedureSyncLock [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
 //   ITS_TRACE_ERROR(("ProcedureSyncLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size == sizeof(DSM_Message));

    syncLockMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncLockMsg->discriminator == DSM_MSG_SYNC_LOCK);

    ITS_TRACE_ERROR((
        "ProcedureSyncLock [FtGroupId: %u]: received DSM SYNC LOCK message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncLockMsg->u.syncLock.tid,
        syncLockMsg->u.syncLock.syncSlaveMemberName,
        syncLockMsg->u.syncLock.syncMasterMemberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncLockMsg->u.syncLock.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC LOCK message to "
            "slave (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockToSlaveInStateInitial(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockToSlaveInStateJoining(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncLockToSlaveInStateNormal(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockToSlaveInStateSyncWait(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockToSlaveInStateSyncSlave(
                dataObj,
                service,
                sender,
                numGroups,
                groups,
                size,
                msg,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockToSlaveInStateSyncMaster(
                dataObj,
                service,
                sender,
                numGroups,
                groups,
                size,
                msg,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockToSlaveInStateSyncNeutral(
                dataObj,
                service,
                sender,
                numGroups,
                groups,
                size,
                msg,
                syncLockMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncLockMsg->u.syncLock.syncMasterMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC LOCK message to "
            "master\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockToMasterInStateInitial(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockToMasterInStateJoining(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockToMasterInStateSyncWait(
                dataObj,
                syncLockMsg);

            break;
        
        case DSM_STATE_NORMAL:

            SubProcedureSyncLockToMasterInStateNormal(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockToMasterInStateSyncSlave(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockToMasterInStateSyncMaster(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockToMasterInStateSyncNeutral(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockToMasterInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC LOCK message to "
            "neutral member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockToNeutralInStateInitial(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockToNeutralInStateJoining(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncLockToNeutralInStateNormal(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockToNeutralInStateSyncWait(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockToNeutralInStateSyncSlave(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockToNeutralInStateSyncMaster(
                dataObj,
                syncLockMsg);
            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockToNeutralInStateSyncNeutral(
                dataObj,
                syncLockMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockToNeutralInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncLock [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncLockRetry.
 *
 */

static void
SubProcedureSyncLockRetryToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockRetryToMasterInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    DSM_Message syncInvalidMasterMsg;
    ITS_UINT tid;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: master state is not NORMAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Multicast invalid master (chosen master state is not NORMAL). */

    tid = AllocateTid(dataObj);

    syncInvalidMasterMsg.discriminator = DSM_MSG_SYNC_INVALID_MASTER;

    syncInvalidMasterMsg.u.syncInvalidMaster.tid = tid;
    strcpy(
        syncInvalidMasterMsg.u.syncInvalidMaster.syncMasterMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    strcpy(
        syncInvalidMasterMsg.u.syncInvalidMaster.syncSlaveMemberName,
        syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName);
    syncInvalidMasterMsg.u.syncInvalidMaster.masterState = 
        DSM_DATA_STATE_DATA(dataObj).state;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: ready to send DSM SYNC "
        "INVALID MASTER message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "master state: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncInvalidMasterMsg.u.syncInvalidMaster.tid,
        syncInvalidMasterMsg.u.syncInvalidMaster.syncSlaveMemberName,
        syncInvalidMasterMsg.u.syncInvalidMaster.syncMasterMemberName,
        syncInvalidMasterMsg.u.syncInvalidMaster.masterState));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_INVALID_MASTER,
                sizeof(DSM_Message),
                (const char*)&syncInvalidMasterMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLockRetry [FtGroupId: %u]: GCS_Multicast failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC INVALID MASTER "
        "message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
SubProcedureSyncLockRetryToMasterInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    SubProcedureSyncLockRetryToMasterInStateInitial(
        dataObj,
        syncLockRetryMsg);
}

static void
SubProcedureSyncLockRetryToMasterInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockRetryToMasterInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    SubProcedureSyncLockRetryToMasterInStateInitial(
        dataObj,
        syncLockRetryMsg);
}

static void
SubProcedureSyncLockRetryToMasterInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockRetryToMasterInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockRetryToMasterInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    ITS_UINT numSyncMemMsg      = 0;
    ITS_UINT syncSize           = 0;
    ITS_UINT dataSize           = 0;
    ITS_UINT remainderDataSize  = 0;

    DSM_Message* syncMemMsg;
    char buf[sizeof(DSM_Message) + DSM_MAX_SYNC_MEM_DATA_SIZE];
    ITS_UINT i;
    int ret;

    /* 
     * Lock state: must not change to SYNC state if locked by another thread. 
     */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLockRetry [FtGroupId: %u]: MUTEX_AcquireMutex "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLockRetry [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Change state to SYNC MASTER. */
    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: change state to SYNC "
        "MASTER\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_SYNC_MASTER;

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncLockRetry [FtGroupId: %u]: MUTEX_ReleaseMutex "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncLockRetry [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Update SYNC related data. */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);

    ITS_C_ASSERT(
        !(DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp && 
          DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs));

    ITS_C_ASSERT(
        DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp ||
        DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs);

    if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseTcp)
    {
        DSM_Message syncMemTcpMsg;

        /*
         * Synchronize slave DSM memory with master DSM memory using
         * TCP. 
         */

        /* 
         * Send SYNC MEM TCP message (command SLAVE DO CONNECT).
         */

        syncMemTcpMsg.discriminator = DSM_MSG_SYNC_MEM_TCP;
        syncMemTcpMsg.u.syncMemTcp.tid = AllocateTid(dataObj);
        strcpy(
            syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
            DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName);
        strcpy(
            syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
            DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName);
        syncMemTcpMsg.u.syncMemTcp.command = 
            DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT;
        syncMemTcpMsg.u.syncMemTcp.size = 0;

        ITS_TRACE_ERROR((
            "ProcedureSyncLockRetry [FtGroupId: %u]: ready to send DSM SYNC "
            "MEM TCP message | "
            "tid: %u | "
            "slave member name: %s | "
            "master member name: %s | "
            "command: %s | "
            "size: %u\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncMemTcpMsg.u.syncMemTcp.tid,
            syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
            syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
            SyncMemTcpCmdToStr(syncMemTcpMsg.u.syncMemTcp.command),
            syncMemTcpMsg.u.syncMemTcp.size));

        ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_MEM_TCP,
                sizeof(DSM_Message),
                (const char*)&syncMemTcpMsg);
        if (ret < 0)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncLockRetry [FtGroupId: %u]: GCS_Multicast failed:"
                " %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
        
            ITS_TRACE_CRITICAL((
                "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover "
                "from previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover "
                "from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }

        ITS_TRACE_DEBUG((
            "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC MEM TCP message "
            "successfully sent\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else if (DSM_DATA_SYNC_DATA(dataObj).syncMemUseGcs)
    {
        /*
         * Synchronize slave DSM memory with master DSM memory using GCS. 
         */

        /* 
         * Loop to send as many SYNC MEM messages as necessary to 
         * synchronize DSM memory of slave with DSM memory of master. 
         * Last SYNC MEM message is marked as last to allow the slave
         * to send back a SYNC UNLOCK message. The case of SYNC UNLOCK
         * message never received is handled through membership change
         * (and messages).
         */

        /* 
         * Synchronize only relevant (i.e. already allocated) memory. 
         */
        syncSize = DSM_DATA_MEM_DATA(dataObj)->curbrk - 
                        (ITS_POINTER)DSM_DATA_SYS_MAP_ADDR(dataObj);

        ITS_C_ASSERT(syncSize <= DSM_DATA_MEM_DATA(dataObj)->size);
    
        numSyncMemMsg = syncSize / DSM_MAX_SYNC_MEM_DATA_SIZE;

        remainderDataSize = syncSize % DSM_MAX_SYNC_MEM_DATA_SIZE;

        if (remainderDataSize > 0)
        {
            numSyncMemMsg++;
        }

        /* At least one SYNC MEM message (even if empty). */
        if (numSyncMemMsg == 0)
        {
            numSyncMemMsg++; 
        }

        /* Special case for SYNC MEM last message. */
        if (remainderDataSize == 0)
        {
            remainderDataSize = DSM_MAX_SYNC_MEM_DATA_SIZE;
        }

        /* Reset. */
        DSM_DATA_MEM_DATA(dataObj)->cursync = DSM_DATA_SYS_MAP_ADDR(dataObj);

        for (i = 1; i <= numSyncMemMsg; i++)
        {
            if (i != numSyncMemMsg)
            {
                /* Not last one. */

                dataSize = DSM_MAX_SYNC_MEM_DATA_SIZE;
            }
            else
            {
                /* Last one. */

                dataSize = remainderDataSize; /* might be zero. */
            }

#if defined(DEBUG) || defined(_DEBUG)
            memset(
                buf, 
                0, 
                sizeof(DSM_Message) + DSM_MAX_SYNC_MEM_DATA_SIZE);
#endif /* defined(DEBUG) || defined(_DEBUG) */

            syncMemMsg = (DSM_Message*)buf;
            syncMemMsg->discriminator   = DSM_MSG_SYNC_MEM;
            syncMemMsg->u.syncMem.tid   = AllocateTid(dataObj);
            syncMemMsg->u.syncMem.seq   = i;
            if (i == numSyncMemMsg)
            {
                syncMemMsg->u.syncMem.last = ITS_TRUE;
            }
			else
			{
				syncMemMsg->u.syncMem.last = ITS_FALSE;
			}
            memcpy(
                syncMemMsg->u.syncMem.syncSlaveMemberName,
                syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName,
                GCS_MAX_GROUP_NAME);
            memcpy(
                syncMemMsg->u.syncMem.syncMasterMemberName,
                DSM_DATA_LOCAL(dataObj).memberName,
                GCS_MAX_GROUP_NAME);
            syncMemMsg->u.syncMem.size = dataSize;
            memcpy(
                syncMemMsg->u.syncMem.data,
                DSM_DATA_MEM_DATA(dataObj)->cursync,
                dataSize);

            DSM_DATA_MEM_DATA(dataObj)->cursync += dataSize;

            ITS_TRACE_DEBUG((
                "ProcedureSyncLockRetry [FtGroupId: %u]: ready to send DSM "
                "SYNC MEM message | "
                "tid: %u | "
                "seq: %u | "
                "last: %s | "
                "slave member name: %s | "
                "master member name: %s | "
                "size: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                syncMemMsg->u.syncMem.tid,
                syncMemMsg->u.syncMem.seq,
                syncMemMsg->u.syncMem.last ? "true" : "false",
                syncMemMsg->u.syncMem.syncSlaveMemberName,
                syncMemMsg->u.syncMem.syncMasterMemberName,
                syncMemMsg->u.syncMem.size));

            /*
             * Note: by default use UNICAST by using slave member name
             * instead of DSM_DATA_LOCAL(dataObj).groupName. 
             */

            ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                        GCS_SAFE_MSG,
#if defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        DSM_DATA_LOCAL(dataObj).groupName,
#else // !defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName,
#endif // defined(DSM_GCS_SYNC_MEM_NO_UNICAST)
                        DSM_MSG_SYNC_MEM,
                        sizeof(DSM_Message) + dataSize,
                        (const char*)syncMemMsg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "ProcedureSyncLockRetry [FtGroupId: %u]: GCS_Multicast "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover"
                    " from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureSyncLockRetry [FtGroupId: %u]: unable to recover"
                    " from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC MEM message "
                "successfully sent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }
}

static void
SubProcedureSyncLockRetryToMasterInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncLockRetryToNeutralInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncLockRetryMsg)
{
    /* Update SYNC related data. */
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName);
    strcpy(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        syncLockRetryMsg->u.syncLockRetry.syncMasterMemberName);

    /* Nothing else to do. */
}

static void
SubProcedureSyncLockRetryToNeutralInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncLockRetry(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncLockRetryMsg;

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: begin with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size == sizeof(DSM_Message));

    syncLockRetryMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncLockRetryMsg->discriminator == DSM_MSG_SYNC_LOCK_RETRY);

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: received DSM SYNC LOCK RETRY "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncLockRetryMsg->u.syncLockRetry.tid,
        syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName,
        syncLockRetryMsg->u.syncLockRetry.syncMasterMemberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncLockRetryMsg->u.syncLockRetry.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC LOCK RETRY "
            "message to slave (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockRetryToSlaveInStateInitial(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockRetryToSlaveInStateJoining(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncLockRetryToSlaveInStateNormal(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockRetryToSlaveInStateSyncWait(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockRetryToSlaveInStateSyncSlave(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockRetryToSlaveInStateSyncMaster(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockRetryToSlaveInStateSyncNeutral(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockRetryToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncLockRetryMsg->u.syncLockRetry.syncMasterMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC LOCK RETRY "
            "message to master\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockRetryToMasterInStateInitial(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockRetryToMasterInStateJoining(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncLockRetryToMasterInStateNormal(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockRetryToMasterInStateSyncWait(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockRetryToMasterInStateSyncSlave(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockRetryToMasterInStateSyncMaster(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockRetryToMasterInStateSyncNeutral(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockRetryToMasterInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncLockRetry [FtGroupId: %u]: DSM SYNC LOCK RETRY "
            "message to neutral member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncLockRetryToNeutralInStateInitial(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncLockRetryToNeutralInStateJoining(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncLockRetryToNeutralInStateNormal(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncLockRetryToNeutralInStateSyncWait(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncLockRetryToNeutralInStateSyncSlave(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncLockRetryToNeutralInStateSyncMaster(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncLockRetryToNeutralInStateSyncNeutral(
                dataObj,
                syncLockRetryMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncLockRetryToNeutralInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncLockRetry [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncUnlock.
 *
 */

static void
SubProcedureSyncUnlockToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    int ret;

    CallMembershipChangeCallbacks(
        dataObj,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);

    ITS_TRACE_ERROR((
        "ProcedureSyncUnlock [FtGroupId: %u]: change state to NORMAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

    /*
     * Release SYNC RWLock (with write priviledge).
     */

    ret = RWLOCK_UnlockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: RWLOCK_UnlockExclusive "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncUnlock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncUnlock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Reset SYNC related data. */
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        0,
        GCS_MAX_GROUP_NAME);
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        0,
        GCS_MAX_GROUP_NAME);

    /* Post SYNC semaphore. */
    ITS_TRACE_ERROR((
        "ProcedureSyncUnlock [FtGroupId: %u]: ready to post SYNC semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: SEMA_PostSemaphore failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncUnlock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncUnlock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncUnlock [FtGroupId: %u]: SYNC semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
SubProcedureSyncUnlockToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncUnlockToMasterInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    int ret;

    /*
     * Don't why this called twice, but deffenetly not reuiqred
    CallMembershipChangeCallbacks(
        dataObj,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);
    */

    ITS_TRACE_ERROR((
        "ProcedureSyncUnlock [FtGroupId: %u]: change state to NORMAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

    CallMembershipChangeCallbacks(
        dataObj,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);

    /*
     * Release SYNC RWLock (with write priviledge).
     */

    ret = RWLOCK_UnlockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: RWLOCK_UnlockExclusive "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncUnlock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncUnlock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Reset SYNC related data. */
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        0,
        GCS_MAX_GROUP_NAME);
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        0,
        GCS_MAX_GROUP_NAME);
}

static void
SubProcedureSyncUnlockToMasterInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToMasterInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void
SubProcedureSyncUnlockToNeutralInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncUnlockToNeutralInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncUnlockMsg)
{
    int ret;

    CallMembershipChangeCallbacks(
        dataObj,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);

    ITS_TRACE_DEBUG((
        "ProcedureSyncUnlock [FtGroupId: %u]: change state to neutral member "
        "saved state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState)));

    /* Restore neutral member saved state. */
    DSM_DATA_STATE_DATA(dataObj).state = 
        DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState;

    CallMembershipChangeCallbacks(
        dataObj,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);

    /*
     * Release SYNC RWLock (with write priviledge).
     */

    ret = RWLOCK_UnlockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: RWLOCK_UnlockExclusive "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncUnlock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncUnlock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Reset SYNC related data. */
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
        0,
        GCS_MAX_GROUP_NAME);
    memset(
        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
        0,
        GCS_MAX_GROUP_NAME);
    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState = 
        DSM_STATE_INVALID;
}

static void
SubProcedureSyncUnlockToNeutralInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncUnlock(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncUnlockMsg;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureSyncUnlock [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_ERROR((
        "ProcedureSyncUnlock [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
  //  ITS_TRACE_ERROR(("ProcedureSyncUnLock:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size = sizeof(DSM_Message));

    syncUnlockMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncUnlockMsg->discriminator == DSM_MSG_SYNC_UNLOCK);

    ITS_TRACE_ERROR((
        "ProcedureSyncUnlock [FtGroupId: %u]: received DSM SYNC UNLOCK "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncUnlockMsg->u.syncUnlock.tid,
        syncUnlockMsg->u.syncUnlock.syncSlaveMemberName,
        syncUnlockMsg->u.syncUnlock.syncMasterMemberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncUnlockMsg->u.syncUnlock.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: DSM SYNC UNLOCK message to "
            "slave (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncUnlockToSlaveInStateInitial(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncUnlockToSlaveInStateJoining(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncUnlockToSlaveInStateNormal(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncUnlockToSlaveInStateSyncWait(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncUnlockToSlaveInStateSyncSlave(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncUnlockToSlaveInStateSyncMaster(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncUnlockToSlaveInStateSyncNeutral(
                dataObj,
                syncUnlockMsg);

            break;
        
        case DSM_STATE_INVALID:

            SubProcedureSyncUnlockToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncUnlockMsg->u.syncUnlock.syncMasterMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: DSM SYNC UNLOCK message to "
            "master\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncUnlockToMasterInStateInitial(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncUnlockToMasterInStateJoining(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncUnlockToMasterInStateNormal(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncUnlockToMasterInStateSyncWait(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncUnlockToMasterInStateSyncSlave(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncUnlockToMasterInStateSyncMaster(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncUnlockToMasterInStateSyncNeutral(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncUnlockToMasterInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncUnlock [FtGroupId: %u]: DSM SYNC UNLOCK message to "
            "neutral member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncUnlockToNeutralInStateInitial(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncUnlockToNeutralInStateJoining(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncUnlockToNeutralInStateNormal(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncUnlockToNeutralInStateSyncWait(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncUnlockToNeutralInStateSyncSlave(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncUnlockToNeutralInStateSyncMaster(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncUnlockToNeutralInStateSyncNeutral(
                dataObj,
                syncUnlockMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncUnlockToNeutralInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }

    /*
     * Call pending procedure(s) stored in SYNC procedure queue if any.
     */

    ret = ExecutePendingProceduresDueToSync(dataObj, "ProcedureSyncUnlock");
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncUnlock [FtGroupId: %u]: ExecuteSyncProcedureQueue "
            "failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncUnlock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncUnlock [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncUnlock [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncMem.
 *
 */

static void
SubProcedureSyncMemToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    int ret;

    if (DSM_DATA_SYNC_DATA(dataObj).lastSeq + 1 != 
        syncMemMsg->u.syncMem.seq)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMem [FtGroupId: %u]: inconsistent sequence number | "
            "SYNC DATA last seq: %u | "
            "DSM SYNC MEM message seq: %u\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            DSM_DATA_SYNC_DATA(dataObj).lastSeq,
            syncMemMsg->u.syncMem.seq));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMem [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMem [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /*
         * Note: following is what should be done to resync lastSeq
         * (not reached due to previous abort).
         */

        DSM_DATA_SYNC_DATA(dataObj).lastSeq = syncMemMsg->u.syncMem.seq; 

        return; /* Not reached. */
    }
    else
    {
        DSM_DATA_SYNC_DATA(dataObj).lastSeq++;
    }

    /*
     * Synchronize DSM memory of slave with DSM memory of master. 
     */

    ITS_TRACE_DEBUG((
        "ProcedureSyncMem [FtGroupId: %u]: synchronizing slave DSM memory with"
        " master DSM memory | "
        "number of bytes: %u | "
        "location: 0x%X | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemMsg->u.syncMem.size,
        DSM_DATA_MEM_DATA(dataObj)->cursync,
        DSM_DATA_LOCAL(dataObj).memberName,
        syncMemMsg->u.syncMem.syncMasterMemberName));

    memcpy(
        DSM_DATA_MEM_DATA(dataObj)->cursync,
        syncMemMsg->u.syncMem.data,
        syncMemMsg->u.syncMem.size);

    DSM_DATA_MEM_DATA(dataObj)->cursync += syncMemMsg->u.syncMem.size;

    /* Is last DSM SYNC MEM message? */
    if (syncMemMsg->u.syncMem.last)
    {
        DSM_Message syncUnlockMsg;
    
        /* Reset cursync. */
        DSM_DATA_MEM_DATA(dataObj)->cursync = 
            DSM_DATA_SYS_MAP_ADDR(dataObj);

        /* Reset lastSeq. */
        DSM_DATA_SYNC_DATA(dataObj).lastSeq = 0;

        /* 
         * Set valid class (itsDSMHASH_Class) pointer for 
         * DSM_DATA_MEM_DATA(dataObj)->tables ITS_Object.
         */
        DSM_DATA_MEM_DATA(dataObj)->tables->core.objClass = itsDSMHASH_Class;

        /*
         * Set valid (local) DSM_DataObject pointer within
         * DSM_DATA_MEM_DATA(dataObj)->tables ITS_Object. 
         */
        DSMHASH_DATA_OBJECT(DSM_DATA_MEM_DATA(dataObj)->tables) = dataObj;

        /* 
         * Send DSM SYNC UNLOCK message. 
         */

        syncUnlockMsg.discriminator = DSM_MSG_SYNC_UNLOCK;
        syncUnlockMsg.u.syncUnlock.tid = AllocateTid(dataObj);
        memcpy(
            syncUnlockMsg.u.syncUnlock.syncSlaveMemberName,
            DSM_DATA_LOCAL(dataObj).memberName,
            GCS_MAX_GROUP_NAME);
        memcpy(
            syncUnlockMsg.u.syncUnlock.syncMasterMemberName,
            syncMemMsg->u.syncMem.syncMasterMemberName,
            GCS_MAX_GROUP_NAME);

        ITS_TRACE_ERROR((
            "ProcedureSyncMem [FtGroupId: %u]: ready to send DSM SYNC UNLOCK "
            "message | "
            "tid: %u | "
            "slave member name: %s | "
            "master member name: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncUnlockMsg.u.syncUnlock.tid,
            syncUnlockMsg.u.syncUnlock.syncSlaveMemberName,
            syncUnlockMsg.u.syncUnlock.syncMasterMemberName));
  //  ITS_TRACE_ERROR(("ProcedureSyncMem:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

        ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                    GCS_SAFE_MSG,
                    DSM_DATA_LOCAL(dataObj).groupName,
                    DSM_MSG_SYNC_UNLOCK,
                    sizeof(DSM_Message),
                    (const char*)&syncUnlockMsg);
        if (ret < 0)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncMem [FtGroupId: %u]: GCS_Multicast failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "ProcedureSyncMem [FtGroupId: %u]: unable to recover from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureSyncMem [FtGroupId: %u]: unable to recover from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }

        ITS_TRACE_DEBUG((
            "ProcedureSyncLock [FtGroupId: %u]: DSM SYNC UNLOCK message "
            "successfully sent\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
}

static void
SubProcedureSyncMemToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncMem(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncMemMsg;

    ITS_TRACE_DEBUG((
        "ProcedureSyncMem [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureSyncMem [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));

    syncMemMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncMemMsg->discriminator == DSM_MSG_SYNC_MEM);

    ITS_TRACE_DEBUG((
        "ProcedureSyncMem [FtGroupId: %u]: received DSM SYNC MEM message | "
        "tid: %u | "
        "seq: %u | "
        "last: %u | "
        "size: %u | "
        "slave member name: %s | "
        "master member Name: %s \n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemMsg->u.syncMem.tid,
        syncMemMsg->u.syncMem.seq,
        syncMemMsg->u.syncMem.last,
        syncMemMsg->u.syncMem.size,
        syncMemMsg->u.syncMem.syncSlaveMemberName,
        syncMemMsg->u.syncMem.syncMasterMemberName));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncMemMsg->u.syncMem.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncMem [FtGroupId: %u]: DSM SYNC MEM message to slave "
            "(relevant)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncMemToSlaveInStateInitial(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncMemToSlaveInStateJoining(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncMemToSlaveInStateNormal(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncMemToSlaveInStateSyncWait(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncMemToSlaveInStateSyncSlave(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncMemToSlaveInStateSyncMaster(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncMemToSlaveInStateSyncNeutral(
                dataObj,
                syncMemMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncMemToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncMemMsg->u.syncMem.syncMasterMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncMem [FtGroupId: %u]: DSM SYNC MEM message to master "
            "(self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do. */

        /* 
         * Note: might not be reached if UNICAST is used for DSM SYNC MEM
         * message.
         */
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncMem [FtGroupId: %u]: DSM SYNC MEM message to neutral"
            " member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to do. */

        /* 
         * Note: might not be reached if UNICAST is used for DSM SYNC MEM
         * message.
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMem [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * SYNC MEM TCP Listen thread function (thread running only if SYNC MEM TCP).
 *
 */
static THREAD_RET_TYPE
SyncMemTcpListenThread(void* arg)
{
    int ret;
    DSM_DataObject* dataObj = (DSM_DataObject*)arg;
    ITS_BOOLEAN keepOn;
    ITS_SocketInfo* sockServer;
    DSM_Message syncMemTcpMsg;

    ITS_C_REQUIRE(dataObj != NULL);

    ITS_TRACE_DEBUG((
        "SyncMemTcpListenThread [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SOCK_ServerOpen(
            &DSM_DATA_SYNC_DATA(dataObj).sockListen,
            INET_DOMAIN,
            DSM_DATA_SYNC_DATA(dataObj).syncMemIpAddress,
            DSM_DATA_SYNC_DATA(dataObj).syncMemIpPort);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "SyncMemTcpListenThread [FtGroupId: %u]: SOCK_ServerOpen failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "SyncMemTcpListenThread [FtGroupId: %u]: failed to open server "
            "socket for SYNC MEM TCP\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_DEBUG((
            "SyncMemTcpListenThread [FtGroupId: %u]: abnormal exit\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        THREAD_NORMAL_EXIT;
    }

    keepOn = ITS_TRUE;

    while (keepOn)
    {
        ret = SOCK_ServerAccept(
                DSM_DATA_SYNC_DATA(dataObj).sockListen,
                &sockServer);

        if (ret != ITS_SUCCESS)
        {
            if (DSM_DATA_SYNC_DATA(dataObj).exitThread)
            {
                /* Listen socket already closed by SyncDataDestroy. */

                DSM_DATA_SYNC_DATA(dataObj).sockListen = NULL;

                if (DSM_DATA_SYNC_DATA(dataObj).sockServer != NULL)
                {
                    SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockServer);
                    DSM_DATA_SYNC_DATA(dataObj).sockServer = NULL;
                }

                keepOn = ITS_FALSE;
            }
            else
            {
                ITS_TRACE_ERROR((
                    "SyncMemTcpListenThread [FtGroupId: %u]: SOCK_ServerAccept"
                    " failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                /* Try again later: sleep 500 millisecs. */
                TIMERS_USleep(500 * DSM_USEC_PER_MSEC);
            }
        }
        else
        {
            ITS_C_ASSERT(sockServer != NULL);


            if (!IsDsmStateSyncMaster(DSM_DATA_STATE_DATA(dataObj).state))
            {
                ITS_TRACE_ERROR((
                    "SyncMemTcpListenThread [FtGroupId: %u]: SOCK_ServerAccept"
                    " succeeded but state is not SYNC MASTER\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ITS_TRACE_DEBUG((
                    "SyncMemTcpListenThread [FtGroupId: %u]: connection "
                    "rejected due to invalid state of MASTER: %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

                SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockServer);
                DSM_DATA_SYNC_DATA(dataObj).sockServer = NULL;

                continue;
            }

            /* 
             * TODO: add a check to be sure that accepted connection is from
             * SLAVE. If not from SLAVE then reject it (by closing the socket).
             */

            if (DSM_DATA_SYNC_DATA(dataObj).sockServer != NULL)
            {
                SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockServer);
            }

            DSM_DATA_SYNC_DATA(dataObj).sockServer = sockServer;

            ITS_TRACE_DEBUG((
                "SyncMemTcpListenThread [FtGroupId: %u]: SOCK_ServerAccept "
                "succeeded\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /*
             * Send SYNC MEM TCP message (command MASTER DO SEND).
             */

            syncMemTcpMsg.discriminator = DSM_MSG_SYNC_MEM_TCP;
            syncMemTcpMsg.u.syncMemTcp.tid = AllocateTid(dataObj);
            strcpy(
                syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
                DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName);
            strcpy(
                syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
                DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName);
            syncMemTcpMsg.u.syncMemTcp.command = 
                DSM_SYNC_MEM_TCP_MASTER_DO_SEND;
            syncMemTcpMsg.u.syncMemTcp.size = 0;

            ITS_TRACE_ERROR((
                "SyncMemTcpListenThread [FtGroupId: %u]: ready to send DSM "
                "SYNC MEM TCP message | "
                "tid: %u | "
                "slave member name: %s | "
                "master member name: %s | "
                "command: %s | "
                "size: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                syncMemTcpMsg.u.syncMemTcp.tid,
                syncMemTcpMsg.u.syncMemTcp.syncSlaveMemberName,
                syncMemTcpMsg.u.syncMemTcp.syncMasterMemberName,
                SyncMemTcpCmdToStr(syncMemTcpMsg.u.syncMemTcp.command),
                syncMemTcpMsg.u.syncMemTcp.size));

            ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
                    GCS_SAFE_MSG,
                    DSM_DATA_LOCAL(dataObj).groupName,
                    DSM_MSG_SYNC_MEM_TCP,
                    sizeof(DSM_Message),
                    (const char*)&syncMemTcpMsg);
            if (ret < 0)
            {
                ITS_TRACE_ERROR((
                    "SyncMemTcpListenThread [FtGroupId: %u]: GCS_Multicast "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "SyncMemTcpListenThread [FtGroupId: %u]: unable to recover"
                    " from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "SyncMemTcpListenThread [FtGroupId: %u]: unable to recover"
                    " from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "SyncMemTcpListenThread [FtGroupId: %u]: DSM SYNC MEM TCP "
                "message successfully sent\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
    }

    ITS_TRACE_DEBUG((
        "SyncMemTcpListenThread [FtGroupId: %u]: termination\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "SyncMemTcpListenThread [FtGroupId: %u]: normal exit\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
    THREAD_NORMAL_EXIT;
}

/******************************************************************************
 *
 * ProcedureSyncMemTcp.
 *
 */

static void
SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoConnect(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemTcpToMasterCmdTcpMasterDoSend(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    DSM_Message syncMemTcpMsgSend;
    DSM_Procedure *procedure;
    DSM_Procedure_sync newprocedure;
    ITS_UINT syncSize = 0;
    ITS_TIME sendTimeout;
    ITS_TIME sendStart;
    ITS_TIME sendFinish;
    int ret;
    int i=0;

    /*
     * Synchronize only relevant (i.e. already allocated) memory.
     */

    syncSize = DSM_DATA_MEM_DATA(dataObj)->curbrk - 
                    (ITS_POINTER)DSM_DATA_SYS_MAP_ADDR(dataObj);

    ITS_C_ASSERT(syncSize <= DSM_DATA_MEM_DATA(dataObj)->size);

    /*
     * Send SYNC MEM TCP message (command SLAVE DO RECEIVE).
     */

    syncMemTcpMsgSend.discriminator = DSM_MSG_SYNC_MEM_TCP;
    syncMemTcpMsgSend.u.syncMemTcp.tid = AllocateTid(dataObj);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName);
    syncMemTcpMsgSend.u.syncMemTcp.command = 
        DSM_SYNC_MEM_TCP_SLAVE_DO_RECEIVE;
    syncMemTcpMsgSend.u.syncMemTcp.size = syncSize;

    ITS_TRACE_ERROR((
        "ProcedureSyncMemTcp [FtGroupId: %u]: ready to send DSM SYNC MEM TCP "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "command: %s | "
        "size: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemTcpMsgSend.u.syncMemTcp.tid,
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        SyncMemTcpCmdToStr(syncMemTcpMsgSend.u.syncMemTcp.command),
        syncMemTcpMsgSend.u.syncMemTcp.size));

    ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_SYNC_MEM_TCP,
            sizeof(DSM_Message),
            (const char*)&syncMemTcpMsgSend);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    sendTimeout = 
        DSM_DATA_SYNC_DATA(dataObj).syncMemTimeout / DSM_MSEC_PER_SEC;

    ITS_TRACE_ERROR((
        "ProcedureSyncMemTcp [FtGroupId: %u]: Sync Addr %x MASTER ready to send %u "
        "octets\n",
        DSM_DATA_FT_GROUP_ID(dataObj),DSM_DATA_SYS_MAP_ADDR(dataObj),
        syncSize));
  //  ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    sendStart = TIMERS_Time();

    ret = SOCK_NonBlockingWrite(
                    DSM_DATA_SYNC_DATA(dataObj).sockServer,
                    DSM_DATA_SYS_MAP_ADDR(dataObj),
                    syncSize,
                    sendTimeout);

    sendFinish = TIMERS_Time();

    if (ret == 0 || ret < 0)
    {
        if (sendFinish - sendStart >= sendTimeout)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingWrite "
                "failed (most likely timeout)\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
        else
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingWrite "
                "failed (most likely socket error)\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }

        /* Nothing else to do (MASTER). */
    }
    else if ((ITS_UINT)ret < syncSize)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingWrite "
            "failed: only %u octets written instead of %u octets\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret,
            syncSize));

        /* Nothing else to do (MASTER). */
    }
    else if ((ITS_UINT)ret == syncSize)
    {
        ITS_C_ASSERT(sendFinish - sendStart >= 0);

        ITS_TRACE_DEBUG((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingWrite "
            "succeeded: %u octets written in %u seconds\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncSize,
            sendFinish - sendStart));
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }
     
    procedure = DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead;
    for(i=0; i< DSM_DATA_PROCEDURE_MANAGER(dataObj).count;i++)
    {
      if(procedure==NULL)
      {
         ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: End of Entry[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
         break;
      } 
       ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: Count Value for PENDING LIST UPDATE[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
     memset(&newprocedure,0,sizeof(DSM_Procedure_sync));
    // memcpy(&newprocedure,procedure,sizeof(DSM_Procedure));
    newprocedure.type = procedure->type;
    newprocedure.tid = procedure->tid;
    newprocedure.tableId = procedure->tableId;
    newprocedure.originThreadId = procedure->originThreadId;
    memcpy(newprocedure.originMemberName, procedure->originMemberName, GCS_MAX_GROUP_NAME);
    newprocedure.service = procedure->service;
    memcpy(newprocedure.sender, procedure->sender, GCS_MAX_GROUP_NAME);
    newprocedure.numGroups = procedure->numGroups;
    memcpy(newprocedure.groups, procedure->groups, procedure->numGroups * GCS_MAX_GROUP_NAME);
    newprocedure.size = procedure->size;
    memcpy(newprocedure.msg, procedure->msg, procedure->size);

     ret = SOCK_NonBlockingWrite(
                    DSM_DATA_SYNC_DATA(dataObj).sockServer,
                    (char*)&newprocedure,
                    sizeof(DSM_Procedure_sync),
                    sendTimeout);
      if(ret <= 0)
    {
       ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: Write Fail count [%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    }
    else
    {
       ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: Write successful count [%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    }

       procedure = procedure->next;
   }



  //  ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
}

static void
SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoReceive(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemTcpToMasterCmdTcpMasterDoClose(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Close server socket. */
    if (DSM_DATA_SYNC_DATA(dataObj).sockServer != NULL)
    {
        SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockServer);
        DSM_DATA_SYNC_DATA(dataObj).sockServer = NULL;
    }
}

static void
SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoClose(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoConnect(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    DSM_RemoteMember* masterRemoteMember;
    ITS_TIME connectStart;
    ITS_TIME connectTimeout;
    ITS_BOOLEAN connectSucceeded;
    int ret;

    /*
     * Retrieve MASTER from DSM SYNC MEM TCP message.
     */

    masterRemoteMember = 
        RemoteMemberRetrieve(
            dataObj, 
            syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName);

    if (masterRemoteMember == NULL)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: failed to find master remote"
            " member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* Open client socket. */
    ret = SOCK_ClientOpen(
            &DSM_DATA_SYNC_DATA(dataObj).sockClient,
            INET_DOMAIN,
            masterRemoteMember->syncMemIpAddress,
            masterRemoteMember->syncMemIpPort);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_ClientOpen failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* 
     * Connect to server (master).
     */

    connectStart = TIMERS_Time();

    connectTimeout = 
        DSM_DATA_SYNC_DATA(dataObj).syncMemConnectTimeout / DSM_MSEC_PER_SEC;

    connectSucceeded = ITS_FALSE;

    do 
    {
        /* 
         * Note: connect should be fast enough (typically less than
         * 2 seconds). While processing connect membership changes 
         * are not processed. If this becomes unacceptable connect
         * should be done asynchronously using select through 
         * GCS_EventAttachFd.
         */

        /* TODO: check that this loop is fast enough. */

        /* TODO: cannot use non-blocking connect (see WIN32). */

        ret = SOCK_ClientConnect(DSM_DATA_SYNC_DATA(dataObj).sockClient);
        
        if (ret != ITS_SUCCESS)
        {
            /* 
             * Note: is this useful (connect timeout if blocking 
             * socket)? Connect should be very fast...
             */

            /* Try again later: sleep 100 millisecs. */
            TIMERS_USleep(100 * DSM_USEC_PER_MSEC);
        }
        else
        {
            connectSucceeded = ITS_TRUE;
            break;
        }
    }
    while ((TIMERS_Time() - connectStart) < connectTimeout);

    if (connectSucceeded)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_ClientConnect "
            "succeeded\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Nothing else to do. */
    }
    else
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_ClientConnect failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));
        
        return; /* Not reached. */
    }
}

static void
SubProcedureSyncMemTcpToSlaveCmdTcpMasterDoSend(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Nothing to do. */
}
/*SYNC ISSUE:Itika Changes*/
static void
SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList(
    DSM_DataObject* dataObj,
    DSM_Procedure_sync *procedure)
{
  int ret;
  ITS_TRACE_CRITICAL((
             "Received  DSM SYNC MEM TCP message for UPDATING PENDING LIST AT SLAVE"));


  if(procedure != NULL)
  {
     ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    procedure->type,
                    procedure->tid,
                    procedure->tableId,
                    procedure->originThreadId,
                    procedure->originMemberName,
                    procedure->service,
                    procedure->sender,
                    procedure->numGroups,
                    procedure->groups,
                    procedure->size,
                    procedure->msg,
                    "SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList[FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList[FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList[FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
  ITS_TRACE_CRITICAL((
             "PENDING LIST NODE Added successfully dataObj[%x]  TID[%d] \n",dataObj,procedure->tid));
   }
}

static void
SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoReceive(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    DSM_Message syncMemTcpMsgSend;
    DSM_Procedure_sync *newprocedure ;
    ITS_UINT syncSize = 0;
    ITS_TIME receiveTimeout;
    ITS_TIME receiveStart;
    ITS_TIME receiveFinish;
    int ret,countValue = 0;
    int i=0;

    syncSize = syncMemTcpMsgRecv->u.syncMemTcp.size;

    receiveTimeout = 
        DSM_DATA_SYNC_DATA(dataObj).syncMemTimeout / DSM_MSEC_PER_SEC;

    ITS_TRACE_CRITICAL((
        "ProcedureSyncMemTcp [FtGroupId: %u]: Sync Addr %x SLAVE ready to receive %u "
        "octets\n",
        DSM_DATA_FT_GROUP_ID(dataObj),DSM_DATA_SYS_MAP_ADDR(dataObj),
        syncSize));

    receiveStart = TIMERS_Time();
    ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ret = SOCK_NonBlockingRead(
                DSM_DATA_SYNC_DATA(dataObj).sockClient,
                DSM_DATA_SYS_MAP_ADDR(dataObj),
                syncSize,
                receiveTimeout);

    receiveFinish = TIMERS_Time();

    if (ret == 0 || ret < 0)
    {
        if (receiveFinish - receiveStart >= receiveTimeout)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingRead "
                "failed (most likely timeout)\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }
        else
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingRead "
                "failed (most likely socket error)\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
        }

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    else if ((ITS_UINT)ret < syncSize)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingRead failed:"
            " only %u octets read instead of %u octets\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret,
            syncSize));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    else if ((ITS_UINT)ret == syncSize)
    {
        ITS_C_ASSERT(receiveFinish - receiveStart >= 0);

        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: SOCK_NonBlockingRead "
            "succeeded: %u octets read in %u seconds\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncSize,
            receiveFinish - receiveStart));
    ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    }
    else
    {
        ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
        ITS_C_ASSERT(must_not_be_reached);
    }

    
     DSM_DATA_PROCEDURE_MANAGER(dataObj).listHead=NULL;
     DSM_DATA_PROCEDURE_MANAGER(dataObj).listTail=NULL;
     countValue = DSM_DATA_PROCEDURE_MANAGER(dataObj).count;
    for(i=0; i< countValue;i++)
    {
       ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: Count Value for PENDING LIST UPDATE[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    // memset(&newprocedure,0,sizeof(DSM_Procedure_sync));
     newprocedure = NULL; 
     newprocedure = malloc(sizeof(DSM_Procedure_sync)); 
     if(newprocedure == NULL)
     {
       ITS_TRACE_ERROR(("ProcedureSyncMemTcp:  Malloc fail for newprocedure\n"));

     }
     ret = SOCK_NonBlockingRead(
                    DSM_DATA_SYNC_DATA(dataObj).sockClient,
                    (char*)newprocedure,
                    sizeof(DSM_Procedure_sync),
                    receiveTimeout);
    if(ret <= 0)
    {
       ITS_TRACE_CRITICAL(("ProcedureSyncMemTcp: Read Fail[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));
    }
    else
    {
       SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoUpdatePendingList(dataObj,newprocedure);
    }  

    }
    DSM_DATA_PROCEDURE_MANAGER(dataObj).count = countValue;
    ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: FINAL Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));


   

    /* 
     * Set valid class (itsDSMHASH_Class) pointer for
     * DSM_DATA_MEM_DATA(dataObj)->tables ITS_Object.
     */
    DSM_DATA_MEM_DATA(dataObj)->tables->core.objClass = itsDSMHASH_Class;

    /*
     * Set valid (local) DSM_DataObject pointer within
     * DSM_DATA_MEM_DATA(dataObj)->tables ITS_Object. 
     */
    DSMHASH_DATA_OBJECT(DSM_DATA_MEM_DATA(dataObj)->tables) = dataObj;

    /*
     * Send SYNC MEM TCP message (command SLAVE DO CLOSE).
     */

    syncMemTcpMsgSend.discriminator = DSM_MSG_SYNC_MEM_TCP;
    syncMemTcpMsgSend.u.syncMemTcp.tid = AllocateTid(dataObj);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName);
    syncMemTcpMsgSend.u.syncMemTcp.command = 
        DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE;
    syncMemTcpMsgSend.u.syncMemTcp.size = 0;

    ITS_TRACE_CRITICAL((
        "ProcedureSyncMemTcp [FtGroupId: %u]: ready to send DSM SYNC MEM TCP "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "command: %s | "
        "size: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemTcpMsgSend.u.syncMemTcp.tid,
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        SyncMemTcpCmdToStr(syncMemTcpMsgSend.u.syncMemTcp.command),
        syncMemTcpMsgSend.u.syncMemTcp.size));

    ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_SYNC_MEM_TCP,
            sizeof(DSM_Message),
            (const char*)&syncMemTcpMsgSend);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /*
     * Send SYNC MEM TCP message (command MASTER DO CLOSE).
     */

    syncMemTcpMsgSend.discriminator = DSM_MSG_SYNC_MEM_TCP;
    syncMemTcpMsgSend.u.syncMemTcp.tid = AllocateTid(dataObj);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName);
    strcpy(
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName);
    syncMemTcpMsgSend.u.syncMemTcp.command = 
        DSM_SYNC_MEM_TCP_MASTER_DO_CLOSE;
    syncMemTcpMsgSend.u.syncMemTcp.size = 0;

    ITS_TRACE_CRITICAL((
        "ProcedureSyncMemTcp [FtGroupId: %u]: ready to send DSM SYNC MEM TCP "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "command: %s | "
        "size: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemTcpMsgSend.u.syncMemTcp.tid,
        syncMemTcpMsgSend.u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgSend.u.syncMemTcp.syncMasterMemberName,
        SyncMemTcpCmdToStr(syncMemTcpMsgSend.u.syncMemTcp.command),
        syncMemTcpMsgSend.u.syncMemTcp.size));

    ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_SYNC_MEM_TCP,
            sizeof(DSM_Message),
            (const char*)&syncMemTcpMsgSend);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP "
        "message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
SubProcedureSyncMemTcpToSlaveCmdTcpMasterDoClose(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoClose(
    DSM_DataObject* dataObj,
    DSM_Message* syncMemTcpMsgRecv)
{
    DSM_Message syncUnlockMsg;
    int ret;

    /* Close client socket. */
    if (DSM_DATA_SYNC_DATA(dataObj).sockClient != NULL)
    {
        SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockClient);
        DSM_DATA_SYNC_DATA(dataObj).sockClient = NULL;
    }

    /* 
     * Send DSM SYNC UNLOCK message. 
     */

    syncUnlockMsg.discriminator = DSM_MSG_SYNC_UNLOCK;
    syncUnlockMsg.u.syncUnlock.tid = AllocateTid(dataObj);
    strcpy(
        syncUnlockMsg.u.syncUnlock.syncSlaveMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName);
    strcpy(
        syncUnlockMsg.u.syncUnlock.syncMasterMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName);

    ITS_TRACE_ERROR((
        "ProcedureSyncMemTcp [FtGroupId: %u]: ready to send DSM SYNC UNLOCK "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncUnlockMsg.u.syncUnlock.tid,
        syncUnlockMsg.u.syncUnlock.syncSlaveMemberName,
        syncUnlockMsg.u.syncUnlock.syncMasterMemberName));
//    ITS_TRACE_ERROR(("ProcedureSyncMemTcp:: Count[%d] \n",DSM_DATA_PROCEDURE_MANAGER(dataObj).count));

    ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_UNLOCK,
                sizeof(DSM_Message),
                (const char*)&syncUnlockMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncMemTcp [FtGroupId: %u]: unable to recover from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void 
ProcedureSyncMemTcp(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncMemTcpMsgRecv;

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_ERROR((
        "ProcedureSyncMemTcp [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));

    syncMemTcpMsgRecv = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncMemTcpMsgRecv->discriminator == DSM_MSG_SYNC_MEM_TCP);

    ITS_TRACE_ERROR((
        "ProcedureSyncMemTcp [FtGroupId: %u]: received DSM SYNC MEM TCP "
        "message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member Name: %s | "
        "command: %s | "
        "size: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncMemTcpMsgRecv->u.syncMemTcp.tid,
        syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName,
        syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName,
        SyncMemTcpCmdToStr(syncMemTcpMsgRecv->u.syncMemTcp.command),
        syncMemTcpMsgRecv->u.syncMemTcp.size));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncMemTcpMsgRecv->u.syncMemTcp.syncMasterMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message to "
            "master\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        if (!IsDsmStateSyncMaster(DSM_DATA_STATE_DATA(dataObj).state))
        {
            ITS_TRACE_DEBUG((
                "ProcedureSyncMemTcp [FtGroupId: %u]: master is not in state "
                "SYNC MASTER: discard procedure and close server socket\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            if (DSM_DATA_SYNC_DATA(dataObj).sockServer != NULL)
            {
                SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockServer);
                DSM_DATA_SYNC_DATA(dataObj).sockServer = NULL;
            }

            ITS_TRACE_DEBUG((
                "ProcedureSyncMemTcp [FtGroupId: %u]: end with current state:"
                " %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

            return;
        }

        switch (syncMemTcpMsgRecv->u.syncMemTcp.command)
        {
        case DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT:

            SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoConnect(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_MASTER_DO_SEND:

            SubProcedureSyncMemTcpToMasterCmdTcpMasterDoSend(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_SLAVE_DO_RECEIVE:

            SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoReceive(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_MASTER_DO_CLOSE:

            SubProcedureSyncMemTcpToMasterCmdTcpMasterDoClose(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE:

            SubProcedureSyncMemTcpToMasterCmdTcpSlaveDoClose(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);    
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncMemTcpMsgRecv->u.syncMemTcp.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message to "
            "slave\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        if (!IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
        {
            ITS_TRACE_DEBUG((
                "ProcedureSyncMemTcp [FtGroupId: %u]: slave is not in state "
                "SYNC SLAVE: discard procedure and close client socket\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            if (DSM_DATA_SYNC_DATA(dataObj).sockClient != NULL)
            {
                SOCK_Close(DSM_DATA_SYNC_DATA(dataObj).sockClient);
                DSM_DATA_SYNC_DATA(dataObj).sockClient = NULL;
            }

            ITS_TRACE_DEBUG((
                "ProcedureSyncMemTcp [FtGroupId: %u]: end with current state:"
                " %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

            return;
        }

        switch (syncMemTcpMsgRecv->u.syncMemTcp.command)
        {
        case DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT:

            SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoConnect(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_MASTER_DO_SEND:

            SubProcedureSyncMemTcpToSlaveCmdTcpMasterDoSend(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_SLAVE_DO_RECEIVE:

            SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoReceive(
                dataObj,
                syncMemTcpMsgRecv);

            break;
            
        case DSM_SYNC_MEM_TCP_MASTER_DO_CLOSE:

            SubProcedureSyncMemTcpToSlaveCmdTcpMasterDoClose(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        case DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE:

            SubProcedureSyncMemTcpToSlaveCmdTcpSlaveDoClose(
                dataObj,
                syncMemTcpMsgRecv);

            break;

        default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);    
            break;
        }

        }
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncMemTcp [FtGroupId: %u]: DSM SYNC MEM TCP message to "
            "neutral member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Nothing to do. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncMemTcp [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureSyncInvalidMaster.
 *
 */

static void
SubProcedureSyncInvalidMasterToSlaveInStateInitial(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateJoining(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateNormal(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateSyncWait(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateSyncSlave(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    DSM_Message syncLockRetryMsg;
    DSM_RemoteMember* masterRemoteMember;
    int ret;

    /*
     * Update invalid master last known state.
     */

    ITS_C_ASSERT(
        !IsDsmStateNormal(
            syncInvalidMasterMsg->u.syncInvalidMaster.masterState));

    masterRemoteMember = 
        RemoteMemberRetrieve(
            dataObj,
            syncInvalidMasterMsg->
                u.syncInvalidMaster.syncMasterMemberName);

    if (masterRemoteMember != NULL)
    {
        masterRemoteMember->lastKnownState =
            syncInvalidMasterMsg->u.syncInvalidMaster.masterState;
    }

    /*
     * Try another master if one available.
     */

    masterRemoteMember = RemoteMemberRetrieveFirstValidMaster(dataObj);
    if (masterRemoteMember != NULL)
    {

        /* Update SYNC related data. */
        strcpy(
            DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
            DSM_DATA_LOCAL(dataObj).memberName);
        strcpy(
            DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
            masterRemoteMember->memberName);

        /* 
         * Send SYNC LOCK RETRY message. 
         */

        syncLockRetryMsg.discriminator = DSM_MSG_SYNC_LOCK_RETRY;
        syncLockRetryMsg.u.syncLockRetry.tid = AllocateTid(dataObj);
        strcpy(
            syncLockRetryMsg.u.syncLockRetry.syncMasterMemberName,
            masterRemoteMember->memberName);
        strcpy(
            syncLockRetryMsg.u.syncLockRetry.syncSlaveMemberName,
            DSM_DATA_LOCAL(dataObj).memberName);

        ITS_TRACE_DEBUG((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: ready to send DSM "
            "SYNC LOCK RETRY message | "
            "tid: %u | "
            "slave member name: %s | "
            "master member name: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            syncLockRetryMsg.u.syncLock.tid,
            syncLockRetryMsg.u.syncLock.syncSlaveMemberName,
            syncLockRetryMsg.u.syncLock.syncMasterMemberName));

        ret = GCS_Multicast(
                    DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_SYNC_LOCK_RETRY,
                sizeof(DSM_Message),
                (const char*)&syncLockRetryMsg);
        if (ret < 0)
        {
            ITS_TRACE_ERROR((
                "ProcedureSyncInvalidMaster [FtGroupId: %u]: GCS_Multicast "
                "failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "ProcedureSyncInvalidMaster [FtGroupId: %u]: unable to recover"
                " from previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureSyncInvalidMaster [FtGroupId: %u]: unable to recover"
                " from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }

        ITS_TRACE_DEBUG((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: DSM SYNC LOCK RETRY "
            "message successfully sent\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: detected total "
            "failure in N processes Fault Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ITS_TRACE_CRITICAL((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: unable to recover "
            "from previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: unable to recover "
            "from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateSyncMaster(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateSyncNeutral(
    DSM_DataObject* dataObj,
    DSM_Message* syncInvalidMasterMsg)
{
    /* Nothing to do. */
}

static void
SubProcedureSyncInvalidMasterToSlaveInStateInvalid(
    DSM_DataObject* dataObj)
{
    ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
    ITS_C_ASSERT(must_not_be_reached);
}

static void 
ProcedureSyncInvalidMaster(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* syncInvalidMasterMsg;

    ITS_TRACE_DEBUG((
        "ProcedureSyncInvalidMaster [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureSyncInvalidMaster [FtGroupId: %u]: begin with current state:"
        " %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size == sizeof(DSM_Message));

    syncInvalidMasterMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(syncInvalidMasterMsg->discriminator == 
        DSM_MSG_SYNC_INVALID_MASTER);

    ITS_TRACE_DEBUG((
        "ProcedureSyncInvalidMaster [FtGroupId: %u]: received DSM SYNC INVALID"
        " MASTER message | "
        "tid: %u | "
        "slave member name: %s | "
        "master member name: %s | "
        "master state: %u\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        syncInvalidMasterMsg->u.syncInvalidMaster.tid,
        syncInvalidMasterMsg->u.syncInvalidMaster.syncSlaveMemberName,
        syncInvalidMasterMsg->u.syncInvalidMaster.syncMasterMemberName,
        syncInvalidMasterMsg->u.syncInvalidMaster.masterState));

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName,
            syncInvalidMasterMsg->
                u.syncInvalidMaster.syncSlaveMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: DSM SYNC INVALID "
            "MASTER message to slave\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:

            SubProcedureSyncInvalidMasterToSlaveInStateInitial(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_JOINING:

            SubProcedureSyncInvalidMasterToSlaveInStateJoining(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_NORMAL:

            SubProcedureSyncInvalidMasterToSlaveInStateNormal(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_SYNC_WAIT:

            SubProcedureSyncInvalidMasterToSlaveInStateSyncWait(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_SYNC_SLAVE:

            SubProcedureSyncInvalidMasterToSlaveInStateSyncSlave(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_SYNC_MASTER:

            SubProcedureSyncInvalidMasterToSlaveInStateSyncMaster(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_SYNC_NEUTRAL:

            SubProcedureSyncInvalidMasterToSlaveInStateSyncNeutral(
                dataObj,
                syncInvalidMasterMsg);

            break;

        case DSM_STATE_INVALID:

            SubProcedureSyncInvalidMasterToSlaveInStateInvalid(
                dataObj);

            break;

        default:
            {
                ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
                ITS_C_ASSERT(must_not_be_reached);
                break;
            }
        }
    }
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                syncInvalidMasterMsg->
                    u.syncInvalidMaster.syncMasterMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: DSM SYNC INVALID "
            "MASTER message to master (self)\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to be done. */
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureSyncInvalidMaster [FtGroupId: %u]: DSM SYNC INVALID "
            "MASTER message to neutral member\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Identical processing in all states. */

        /* Nothing to be done. */
    }

    ITS_TRACE_DEBUG((
        "ProcedureSyncInvalidMaster [FtGroupId: %u]: end with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureJoin.
 *
 */

static void 
SubProcedureJoinFirstMember(
    DSM_DataObject* dataObj,
    DSM_InstObject* instObj,
    DSM_CoreObject* coreObj,
    const char* joiningMemberName)
{
    int ret;

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: member %s first in Fault Tolerance"
        " Group\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        joiningMemberName));

    ITS_C_ASSERT(IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state));

    ITS_C_ASSERT(
        strcmp(
            DSM_DATA_LOCAL(dataObj).memberName, 
            joiningMemberName) == 0);

    ITS_C_ASSERT(RemoteMemberSize(dataObj) == 0);

    CallMembershipChangeCallbacks(
        dataObj,
        joiningMemberName,
        DSM_FT_GROUP_MEMBER_ALIVE);

    /* Change state to JOINING. */
    ITS_TRACE_CRITICAL((
        "ProcedureJoin [FtGroupId: %u]: change state to JOINING\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_JOINING;

    /* Post SELF-JOIN semaphore. */
    ITS_TRACE_CRITICAL((
        "ProcedureJoin [FtGroupId: %u]: ready to post SELF-JOIN semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).selfSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureJoin [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_CRITICAL((
        "ProcedureJoin [FtGroupId: %u]: SELF-JOIN semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    CallMembershipChangeCallbacks(
        dataObj,
        joiningMemberName,
        DSM_FT_GROUP_MEMBER_JOIN);

    /* Change state to NORMAL (implicit or explicit synchronization). */
    ITS_TRACE_DEBUG((
        "ProcedureJoin [FtGroupId: %u]: change state to NORMAL\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

    /* Post MASTER-JOIN semaphore. */
    ITS_TRACE_CRITICAL((
        "ProcedureJoin [FtGroupId: %u]: ready to post MASTER-JOIN semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).masterSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureJoin [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_CRITICAL((
        "ProcedureJoin [FtGroupId: %u]: MASTER-JOIN semaphore posted\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    if (!DSM_INST_DSM_SYNC_EXPLICIT(instObj))
    {
        /* Post SYNC semaphore. */
        ITS_TRACE_DEBUG((
            "ProcedureJoin [FtGroupId: %u]: ready to post SYNC semaphore\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        ret = SEMA_PostSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "ProcedureJoin [FtGroupId: %u]: SEMA_PostSemaphore failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "ProcedureJoin [FtGroupId: %u]: unacceptable state from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureJoin [FtGroupId: %u]: unable to recover from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            return; /* Not reached. */
        }

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: SYNC semaphore posted\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
}

static void 
SubProcedureJoinNotFirstMemberSelf(
    DSM_DataObject* dataObj,
    DSM_InstObject* instObj,
    DSM_CoreObject* coreObj,
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    const char* joiningMemberName)
{
    DSM_Message joinInfoMsg;
    int i;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureJoin [FtGroupId: %u]: join membership message from self\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_C_ASSERT(IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state));

    ITS_TRACE_DEBUG((
        "ProcedureJoin [FtGroupId: %u]: INTIAL STATE:numGroups[%d] RemoteMemberSize(dataObj)[%d]\n",
        DSM_DATA_FT_GROUP_ID(dataObj),numGroups, RemoteMemberSize(dataObj)));
    /* Update remote members. */
    ITS_C_ASSERT(numGroups <= DSM_MAX_MEMBERS);
    ITS_C_ASSERT(RemoteMemberSize(dataObj) == 0);

    ITS_TRACE_DEBUG((
        "ProcedureJoin : #######numGroups[%d] joiningMemberName[%s] \n",numGroups,joiningMemberName));
    for (i = 0; i < numGroups; i++)
    {
        if (strcmp(groups[i], joiningMemberName) != 0)
        {
            /* Check for duplicates. */
            ITS_C_ASSERT(!HasRemoteMember(dataObj, groups[i]));   
            RemoteMemberInsert(dataObj, groups[i]);
        }
    }

    CallMembershipChangeCallbacks(
        dataObj,
        joiningMemberName,
        DSM_FT_GROUP_MEMBER_ALIVE);

    /* 
     * Change state to JOINING (waiting for DSM JOIN INFO messages from
     * other members).
     */
    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: change state to JOINING\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_JOINING;

    /* Post SELF-JOIN semaphore. */
    ITS_TRACE_DEBUG((
        "ProcedureJoin [FtGroupId: %u]: ready to post SELF-JOIN semaphore\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ret = SEMA_PostSemaphore(&DSM_DATA_JOIN_DATA(dataObj).selfSema);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: SEMA_PostSemaphore failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureJoin [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    /* 
     * Send DSM JOIN INFO message to other members. 
     */

    joinInfoMsg.discriminator = DSM_MSG_JOIN_INFO;
    joinInfoMsg.u.joinInfo.tid = AllocateTid(dataObj);
    strcpy(
        joinInfoMsg.u.joinInfo.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    ITS_C_ASSERT(RemoteMemberSize(dataObj) == 1);
    strcpy(
        joinInfoMsg.u.joinInfo.destinationMemberName,
        "others");
    strcpy(
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpAddress,
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpAddress);
    joinInfoMsg.u.joinInfo.originMemberSyncMemIpPort =
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpPort;
    joinInfoMsg.u.joinInfo.originMemberNodeId =
        DSM_CORE_NODE_ID(coreObj);
    joinInfoMsg.u.joinInfo.originMemberProcessId =
        DSM_CORE_PROCESS_ID(coreObj);
    joinInfoMsg.u.joinInfo.originMemberState =
        DSM_DATA_STATE_DATA(dataObj).state;

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: ready to send DSM JOIN INFO message | "
        "tid: %u | "
        "origin member name: %s | "
        "destination member name: %s | "
        "origin member sync mem IP address: %s | "
        "origin member sync mem IP port: %u | "
        "origin member nodeId: %u | "
        "origin member processId: %u | "
        "origin member state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        joinInfoMsg.u.joinInfo.tid,
        joinInfoMsg.u.joinInfo.originMemberName,
        joinInfoMsg.u.joinInfo.destinationMemberName,
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpAddress,
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpPort,
        joinInfoMsg.u.joinInfo.originMemberNodeId,
        joinInfoMsg.u.joinInfo.originMemberProcessId,
        StateToStr(joinInfoMsg.u.joinInfo.originMemberState)));

    ret = GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_JOIN_INFO,
            sizeof(DSM_Message),
            (const char*)&joinInfoMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureJoin [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: DSM JOIN INFO message successfully "
        "sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void 
SubProcedureJoinNotFirstMemberNotSelf(
    DSM_DataObject* dataObj,
    DSM_InstObject* instObj,
    DSM_CoreObject* coreObj,
    const char* joiningMemberName)
{
    DSM_Message joinInfoMsg;
    int ret;

    /* Identical processing in all states. */

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: join membership message not from "
        "self\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Update remote members. */
    if (HasRemoteMember(dataObj, joiningMemberName))
    {
        /* Check for duplicate. */
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: found duplicate remote member "
            "%s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            joiningMemberName));
    }
    else if (RemoteMemberSize(dataObj) >= DSM_MAX_REMOTE_MEMBERS)
    {
        /* Check for too many. */
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: too many remote members\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
    }
    else
    {
        ITS_TRACE_ERROR((
        "ProcedureJoin :Inserting RemoteMemberInsert:: joiningMemberName[%s]\n",joiningMemberName));
        RemoteMemberInsert(dataObj, joiningMemberName);
    }

    CallMembershipChangeCallbacks(
        dataObj,
        joiningMemberName,
        DSM_FT_GROUP_MEMBER_ALIVE);

    /* 
     * Send DSM JOIN INFO message to joining member. 
     */

    joinInfoMsg.discriminator = DSM_MSG_JOIN_INFO;
    joinInfoMsg.u.joinInfo.tid = AllocateTid(dataObj);
    strcpy(
        joinInfoMsg.u.joinInfo.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName);
    strcpy(
        joinInfoMsg.u.joinInfo.destinationMemberName,
        joiningMemberName);
    strcpy(
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpAddress,
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpAddress);
    joinInfoMsg.u.joinInfo.originMemberSyncMemIpPort = 
        DSM_DATA_SYNC_DATA(dataObj).syncMemIpPort;
    joinInfoMsg.u.joinInfo.originMemberNodeId =
        DSM_CORE_NODE_ID(coreObj);
    joinInfoMsg.u.joinInfo.originMemberProcessId =
        DSM_CORE_PROCESS_ID(coreObj);
    joinInfoMsg.u.joinInfo.originMemberState =
        DSM_DATA_STATE_DATA(dataObj).state;

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: ready to send DSM JOIN INFO message | "
        "tid: %u | "
        "origin member name: %s | "
        "destination member name: %s | "
        "origin member sync mem IP address: %s | "
        "origin member sync mem IP port: %u | "
        "origin member nodeId: %u | "
        "origin member processId: %u | "
        "origin member state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        joinInfoMsg.u.joinInfo.tid,
        joinInfoMsg.u.joinInfo.originMemberName,
        joinInfoMsg.u.joinInfo.destinationMemberName,
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpAddress,
        joinInfoMsg.u.joinInfo.originMemberSyncMemIpPort,
        joinInfoMsg.u.joinInfo.originMemberNodeId,
        joinInfoMsg.u.joinInfo.originMemberProcessId,
        StateToStr(joinInfoMsg.u.joinInfo.originMemberState)));

    ret = GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            DSM_MSG_JOIN_INFO,
            sizeof(DSM_Message),
            (const char*)&joinInfoMsg);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "ProcedureJoin [FtGroupId: %u]: unable to recover from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "ProcedureJoin [FtGroupId: %u]: unable to recover from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        return; /* Not reached. */
    }

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: DSM JOIN INFO message successfully "
        "sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
}

static void
ProcedureJoin(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    int numBytes = 0;
    GCS_GROUP_ID* groupId;
    ITS_INT* numMembers;
    const char* joiningMemberName;
    DSM_CoreObject* coreObj;
    DSM_InstObject* instObj;

    ITS_TRACE_DEBUG((
        "ProcedureJoin [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state))) ;

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsMembershipMsg(service));
    ITS_C_REQUIRE(GCS_IsCausedJoinMsg(service));

    groupId = (GCS_GROUP_ID*)&msg[numBytes];
    numBytes += sizeof(GCS_GROUP_ID);
    numMembers = (ITS_INT*)&msg[numBytes];
    numBytes += sizeof(ITS_INT);
    joiningMemberName = &msg[numBytes];

    coreObj = DSM_DATA_CORE_OBJECT(dataObj);
    instObj = DSM_DATA_INST_OBJECT(dataObj);

    if (numGroups == 1)
    {
     ITS_TRACE_ERROR(("ProcedureJoin::FIRST NODE:joiningMemberName[%s] NUMGROUP[%d] \n",joiningMemberName,numGroups));
        /* First member of Fault Tolerance Group (implies from self). */

        SubProcedureJoinFirstMember(
            dataObj,
            instObj,
            coreObj,
            joiningMemberName);
    }
    else
    {
        /* Not first member of Fault Tolerance Group. */
      PEER_MTP3_NODE_STATUS  = 0;
 ITS_TRACE_ERROR(("ProcedureJoin::SECOND NODE joiningMemberName[%s] NUMGROUP[%d] PEER_MTP3_NODE_STATUS[%d] \n",joiningMemberName,numGroups,PEER_MTP3_NODE_STATUS));
        ITS_TRACE_ERROR((
            "ProcedureJoin [FtGroupId: %u]: member %s not first in Fault "
            "Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            joiningMemberName));

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName, joiningMemberName) == 0)
        {
            /* Not first member of Fault Tolerance Group from self. */

            SubProcedureJoinNotFirstMemberSelf(
                dataObj,
                instObj,
                coreObj,
                numGroups,
                groups,
                joiningMemberName);
        }
        else
        {
            /* Not first member of Fault Tolerance Group not from self. */

            SubProcedureJoinNotFirstMemberNotSelf(
                dataObj,
                instObj,
                coreObj,
                joiningMemberName);
        }
    }

    ITS_TRACE_ERROR((
        "ProcedureJoin [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureLeave.
 *
 */

static void
ProcedureLeave(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    int numBytes = 0;
    GCS_GROUP_ID* groupId;
    ITS_INT* numMembers;
    char* leavingMemberName;
    DSM_Message syncLockRetryMsg;
    DSM_RemoteMember* masterRemoteMember;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureLeave [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureLeave [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsMembershipMsg(service));
    ITS_C_REQUIRE(GCS_IsCausedLeaveMsg(service));

    groupId = (GCS_GROUP_ID*)&msg[numBytes];
    numBytes += sizeof(GCS_GROUP_ID);
    numMembers = (ITS_INT*)&msg[numBytes];
    numBytes += sizeof(ITS_INT);
    leavingMemberName = &msg[numBytes];

	if (size == 0)
	{
		/* Alternative: msg of null size if self-leave. */

		/* TODO: figure out why. */

		ITS_TRACE_DEBUG((
			"ProcedureLeave [FtGroupId: %u]: member %s self-leaving Fault "
            "Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
			DSM_DATA_LOCAL(dataObj).memberName));

        /* Clear remote members. */
        RemoteMemberClear(dataObj);

        ITS_TRACE_DEBUG((
            "ProcedureLeave [FtGroupId: %u]: change state to INITIAL\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

        /* TODO: what else should be done? */

        /* TODO: might need to release all DSM user threads? */
	}
    else if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName, 
                leavingMemberName) == 0)
    {
        ITS_TRACE_DEBUG((
            "ProcedureLeave [FtGroupId: %u]: member %s self-leaving Fault "
            "Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            leavingMemberName));

        /* TODO: figure out if self-leave can be reached. */

        /* Semantic of underlying GCS in case of self-leaving message. */
        ITS_C_ASSERT(*numMembers == 1);
        ITS_C_ASSERT(numGroups == 0);

        /* Clear remote members. */
        RemoteMemberClear(dataObj);

        ITS_TRACE_DEBUG((
            "ProcedureLeave [FtGroupId: %u]: change state to INITIAL\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;

        /* TODO: what else should be done? */

        /* TODO: might need to release all DSM user threads? */
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureLeave [FtGroupId: %u]: member %s leaving Fault Tolerance"
            " Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            leavingMemberName));

        /* Update remote members. */
        if (HasRemoteMember(dataObj, leavingMemberName))
        {
            RemoteMemberRemove(dataObj, leavingMemberName);
        }
        else
        {
            /* Check for missing remote members. */
            ITS_TRACE_ERROR((
                "ProcedureLeave [FtGroupId: %u]: missing remote member leaving"
                " %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                leavingMemberName));
        }

        CallMembershipChangeCallbacks(
            dataObj,
            leavingMemberName,
            DSM_FT_GROUP_MEMBER_LEAVE);

        CallMembershipChangeCallbacks(
            dataObj,
            leavingMemberName,
            DSM_FT_GROUP_MEMBER_DEAD);

        /* Check and update DSM lock. */
        DsmUnlockFullIfLockedByMember(dataObj, leavingMemberName);

        /* Check and update table locks. */
        TablesUnlockFullIfLockedByMember(dataObj, leavingMemberName);

        ret = RemovePendingProceduresFromMemberDueToLock(
                dataObj,
                leavingMemberName,
                "ProcedureLeave");
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "ProcedureLeave [FtGroupId: %u]: "
                "RemovePendingProceduresFromMemberDueToLock failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            
            /* Ignore non-fatal error (continue). */
        }

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:
        {
            /* Nothing to do. */
            break;
        }

        case DSM_STATE_JOINING:
        {
            if (numGroups == 1)
            {
                /* Only member left in Fault Tolerance Group. */

                ITS_C_ASSERT(RemoteMemberSize(dataObj) == 0);

                /* Change state to NORMAL. */
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: change state to NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /* Post MASTER-JOIN semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: ready to post MASTER-JOIN"
                    " semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(
                        &DSM_DATA_JOIN_DATA(dataObj).masterSema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                    "ProcedureLeave [FtGroupId: %u]: SEMA_PostSemaphore "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: MASTER-JOIN semaphore "
                    "posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Post SYNC semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: ready to post SYNC "
                    "semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLeave [FtGroupId: %u]: SEMA_PostSemaphore "
                        "failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: SYNC semaphore posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_NORMAL:
        {
            ret = ExecutePendingProceduresDueToLock(
                    dataObj,
                    "ProcedureLeave");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLeave [FtGroupId: %u]: "
                    "ExecutePendingProceduresDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLeave [FtGroupId: %u]: unacceptable state from "
                    "previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLeave [FtGroupId: %u]: unable to recover from "
                    "error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */   
            }

            break;
        }

        case DSM_STATE_SYNC_WAIT:
        case DSM_STATE_SYNC_SLAVE:
        {
            if (strcmp(leavingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: leaving member is SYNC "
                    "master",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /*
                 * Note: in case of SYNC WAIT a DSM SYNC LOCK message has
                 * already been sent by slave in ProcedureJoinInfo (because
                 * state is SYNC WAIT and SYNC master member name is valid).
                 * That makes states SYNC WAIT and SYNC SLAVE equivalent in
                 * current context.
                 */

                /*
                 * Try another master if one available.
                 */

                masterRemoteMember = 
                    RemoteMemberRetrieveFirstValidMaster(dataObj);
                if (masterRemoteMember != NULL)
                {
                    /* Update SYNC related data. */
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
                        masterRemoteMember->memberName);

                    /* 
                     * Send SYNC LOCK RETRY message. 
                     */

                    syncLockRetryMsg.discriminator = DSM_MSG_SYNC_LOCK_RETRY;
                    syncLockRetryMsg.u.syncLockRetry.tid = 
                        AllocateTid(dataObj);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncMasterMemberName,
                        masterRemoteMember->memberName);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);

                    ITS_TRACE_DEBUG((
                        "ProcedureLeave [FtGroupId: %u]: ready to send DSM "
                        "SYNC LOCK RETRY message | "
                        "tid: %u | "
                        "slave member name: %s | "
                        "master member name: %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        syncLockRetryMsg.u.syncLock.tid,
                        syncLockRetryMsg.u.syncLock.syncSlaveMemberName,
                        syncLockRetryMsg.u.syncLock.syncMasterMemberName));

                    ret = GCS_Multicast(
                            DSM_DATA_LOCAL(dataObj).Stubmailbox,
                            GCS_SAFE_MSG,
                            DSM_DATA_LOCAL(dataObj).groupName,
                            DSM_MSG_SYNC_LOCK_RETRY,
                            sizeof(DSM_Message),
                            (const char*)&syncLockRetryMsg);
                    if (ret < 0)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLeave [FtGroupId: %u]: GCS_Multicast "
                            "failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));

                        ITS_TRACE_CRITICAL((
                            "ProcedureLeave [FtGroupId: %u]: unable to recover"
                            " from previous error: abort\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));

                        /* Must abort process. */
                        CallCriticalErrorNotificationCallbacks(
                            dataObj,
                            __LINE__,
                            "ProcedureLeave [FtGroupId: %u]: unable to recover"
                            " from error\n",
                            DSM_DATA_FT_GROUP_ID(dataObj));

                        return; /* Not reached. */
                    }

                    ITS_TRACE_DEBUG((
                        "ProcedureLeave [FtGroupId: %u]: DSM SYNC LOCK RETRY "
                        "message successfully sent\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                }
                else
                {
                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: detected total "
                        "failure in N processes Fault Tolerance Group\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_MASTER:
        {
            if (strcmp(leavingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: leaving member is SYNC "
                    "slave",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: change state to NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(
                        &DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLeave [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureLeave");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLeave [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_NEUTRAL:
        {
            if (strcmp(leavingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: leaving member is SYNC "
                    "slave",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ITS_TRACE_DEBUG((
                    "ProcedureLeave [FtGroupId: %u]: change state to "
                    "previously saved state\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = 
                    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(
                        &DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLeave [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureLeave");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLeave [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLeave [FtGroupId: %u]: unacceptable state "
                        "from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLeave [FtGroupId: %u]: unable to recover "
                        "from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_INVALID:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);

            break;
        }

        default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
            break;
        }

        }
    }

    ITS_TRACE_DEBUG((
        "ProcedureLeave [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureDisconnect.
 *
 */

static void
ProcedureDisconnect(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    int numBytes = 0;
    GCS_GROUP_ID* groupId;
    ITS_INT* numMembers;
    char* disconnectingMemberName;
    DSM_Message syncLockRetryMsg;
    DSM_RemoteMember* masterRemoteMember;
    int ret;
    
    ITS_TRACE_DEBUG((
        "ProcedureDisconnect [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureDisconnect [FtGroupId: %u]: begin with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsMembershipMsg(service));
    ITS_C_REQUIRE(GCS_IsCausedDisconnectMsg(service));

    groupId = (GCS_GROUP_ID*)&msg[numBytes];
    numBytes += sizeof(GCS_GROUP_ID);
    numMembers = (ITS_INT*)&msg[numBytes];
    numBytes += sizeof(ITS_INT);
    disconnectingMemberName = &msg[numBytes];

    if (strcmp(
            DSM_DATA_LOCAL(dataObj).memberName, 
            disconnectingMemberName) == 0)
    {
        ITS_TRACE_ERROR((
            "ProcedureDisconnect [FtGroupId: %u]: detected member %s "
            "self-disconnecting\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            disconnectingMemberName));

        ITS_TRACE_CRITICAL((
            "ProcedureDisconnect [FtGroupId: %u]: inconsistent state\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Clear remote members. */
        RemoteMemberClear(dataObj);

        ITS_TRACE_DEBUG((
            "ProcedureDisconnect [FtGroupId: %u]: change state to INITIAL\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_INITIAL;
    }
    else
    {
        ITS_TRACE_DEBUG((
            "ProcedureDisconnect [FtGroupId: %u]: member %s disconnecting from"
            " Fault Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            disconnectingMemberName));

        /* Update remote members. */
        if (HasRemoteMember(dataObj, disconnectingMemberName))
        {
            RemoteMemberRemove(dataObj, disconnectingMemberName);
        }
        else
        {
            /* Check for missing remote members. */

            ITS_TRACE_ERROR((
                "ProcedureDisconnect [FtGroupId: %u]: missing remote member "
                "disconnecting %s\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                disconnectingMemberName));
        }

        CallMembershipChangeCallbacks(
            dataObj,
            disconnectingMemberName,
            DSM_FT_GROUP_MEMBER_LEAVE);

        CallMembershipChangeCallbacks(
            dataObj,
            disconnectingMemberName,
            DSM_FT_GROUP_MEMBER_DEAD);

        /* Check and update DSM lock. */
        DsmUnlockFullIfLockedByMember(dataObj, disconnectingMemberName);

        /* Check and update table locks. */
        TablesUnlockFullIfLockedByMember(dataObj, disconnectingMemberName);

        ret = RemovePendingProceduresFromMemberDueToLock(
                dataObj,
                disconnectingMemberName,
                "ProcedureDisconnect");
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "ProcedureDisconnect [FtGroupId: %u]: "
                "RemovePendingProceduresFromMemberDueToLock failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));
            
            /* Ignore non-fatal error (continue). */
        }

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:
        {
            /* Nothing to do. */
            break;
        }

        case DSM_STATE_JOINING:
        {
            if (numGroups == 1)
            {
                /* Only member left in Fault Tolerance Group. */

                ITS_C_ASSERT(RemoteMemberSize(dataObj) == 0);

                /* Change state to NORMAL. */
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: change state to "
                    "NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /* Post MASTER-JOIN semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: ready to post "
                    "MASTER-JOIN semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(
                        &DSM_DATA_JOIN_DATA(dataObj).masterSema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                    "ProcedureDisconnect [FtGroupId: %u]: SEMA_PostSemaphore "
                    "failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: MASTER-JOIN "
                    "semaphore posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Post SYNC semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: ready to post SYNC "
                    "semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureDisconnect [FtGroupId: %u]: "
                        "SEMA_PostSemaphore failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: SYNC semaphore "
                    "posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_NORMAL:
        {
            ret = ExecutePendingProceduresDueToLock(
                    dataObj,
                    "ProcedureDisconnect");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureDisconnect [FtGroupId: %u]: "
                    "ExecutePendingProceduresDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureDisconnect [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureDisconnect [FtGroupId: %u]: unable to recover "
                    "from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */   
            }

            break;
        }

        case DSM_STATE_SYNC_WAIT:
        case DSM_STATE_SYNC_SLAVE:
        {
            if (strcmp(disconnectingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: leaving member is "
                    "SYNC master",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /*
                 * Note: in case of SYNC WAIT a DSM SYNC LOCK message has
                 * already been sent by slave in ProcedureJoinInfo (because
                 * state is SYNC WAIT and SYNC master member name is valid).
                 * That makes states SYNC WAIT and SYNC SLAVE equivalent in
                 * current context.
                 */

                /*
                 * Try another master if one available.
                 */

                masterRemoteMember = 
                    RemoteMemberRetrieveFirstValidMaster(dataObj);
                if (masterRemoteMember != NULL)
                {
                    /* Update SYNC related data. */
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
                        masterRemoteMember->memberName);

                    /* 
                     * Send SYNC LOCK RETRY message. 
                     */

                    syncLockRetryMsg.discriminator = DSM_MSG_SYNC_LOCK_RETRY;
                    syncLockRetryMsg.u.syncLockRetry.tid = 
                        AllocateTid(dataObj);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncMasterMemberName,
                        masterRemoteMember->memberName);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);

                    ITS_TRACE_DEBUG((
                        "ProcedureDisconnect [FtGroupId: %u]: ready to send "
                        "DSM SYNC LOCK RETRY message | "
                        "tid: %u | "
                        "slave member name: %s | "
                        "master member name: %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        syncLockRetryMsg.u.syncLock.tid,
                        syncLockRetryMsg.u.syncLock.syncSlaveMemberName,
                        syncLockRetryMsg.u.syncLock.syncMasterMemberName));

                    ret = GCS_Multicast(
                            DSM_DATA_LOCAL(dataObj).Stubmailbox,
                            GCS_SAFE_MSG,
                            DSM_DATA_LOCAL(dataObj).groupName,
                            DSM_MSG_SYNC_LOCK_RETRY,
                            sizeof(DSM_Message),
                            (const char*)&syncLockRetryMsg);
                    if (ret < 0)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureDisconnect [FtGroupId: %u]: "
                            "GCS_Multicast failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));

                        ITS_TRACE_CRITICAL((
                            "ProcedureDisconnect [FtGroupId: %u]: unable to "
                            "recover from previous error: abort\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));

                        /* Must abort process. */
                        CallCriticalErrorNotificationCallbacks(
                            dataObj,
                            __LINE__,
                            "ProcedureDisconnect [FtGroupId: %u]: unable to "
                            "recover from error\n",
                            DSM_DATA_FT_GROUP_ID(dataObj));

                        return; /* Not reached. */
                    }

                    ITS_TRACE_DEBUG((
                        "ProcedureDisconnect [FtGroupId: %u]: DSM SYNC LOCK "
                        "RETRY message successfully sent\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                }
                else
                {
                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: detected total "
                        "failure in N processes Fault Tolerance Group\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_MASTER:
        {
            if (strcmp(disconnectingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: leaving member is "
                    "SYNC slave",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: change state to "
                    "NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureDisconnect [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureDisconnect");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureDisconnect [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_NEUTRAL:
        {
            if (strcmp(disconnectingMemberName, 
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: leaving member is "
                    "SYNC slave",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ITS_TRACE_DEBUG((
                    "ProcedureDisconnect [FtGroupId: %u]: change state to "
                    "previously saved state\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = 
                    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(
                        &DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureDisconnect [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureDisconnect");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureDisconnect [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureDisconnect [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureDisconnect [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_INVALID:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);

            break;
        }

        default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
            break;
        }

        }
    }

    ITS_TRACE_DEBUG((
        "ProcedureDisconnect [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureNetworkChange.
 *
 */

static void
ProcedureNetworkChange(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    int numBytes = 0;
    GCS_GROUP_ID* groupId;
    ITS_INT* numMembers;
    char transMembers[DSM_MAX_MEMBERS][GCS_MAX_GROUP_NAME];
    char missingMemberNames[DSM_MAX_MEMBERS][GCS_MAX_GROUP_NAME];
    ITS_UINT numMissingMembers;
    DSM_Message syncLockRetryMsg;
    DSM_RemoteMember* masterRemoteMember;
    int i;
    int j;
    int ret;

    ITS_TRACE_ERROR(("$$$$$ ProcedureNetworkChange [FtGroupId: %u]: $$$$$\n",
                     DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureNetworkChange [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureNetworkChange [FtGroupId: %u]: begin with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsMembershipMsg(service));
    ITS_C_REQUIRE(GCS_IsCausedNetworkMsg(service));

    groupId = (GCS_GROUP_ID*)&msg[numBytes];
    numBytes += sizeof(GCS_GROUP_ID);
    numMembers = (ITS_INT*)&msg[numBytes];
    numBytes += sizeof(ITS_INT);
    
    ITS_C_ASSERT(*numMembers <= DSM_MAX_MEMBERS);

    for (i = 0; i <= *numMembers; i++)
    {
        memcpy(transMembers[i], &msg[numBytes], GCS_MAX_GROUP_NAME);
        numBytes += GCS_MAX_GROUP_NAME * sizeof(char);
    }

    /* Reset. */
    memset(missingMemberNames, 0, GCS_MAX_GROUP_NAME * DSM_MAX_MEMBERS);
    numMissingMembers = 0;

    /* Deduce missing members after network change. */
    for (i = 0; i < DSM_MAX_REMOTE_MEMBERS; i++)
    {
        if (DSM_DATA_REMOTES(dataObj).members[i].valid == ITS_TRUE)
        {
          ITS_TRACE_ERROR(("###########VALID REMOTE MEMBER EXISTS###################\n"));
            for (j = 0; j < *numMembers; j++)
            {
               /* if (strcmp(
                        DSM_DATA_REMOTES(dataObj).members[i].memberName, 
                        transMembers[j]) == 0)problem with check while opp card jack out*/
                         ITS_TRACE_ERROR(("DSM_DATA_REMOTES(dataObj).members[i].memberName %s\n",DSM_DATA_REMOTES(dataObj).members[i].memberName));
                         ITS_TRACE_ERROR(("transMembers[%d]=%s\n",j,transMembers[j]));
                if (strcmp(DSM_DATA_REMOTES(dataObj).members[i].memberName,transMembers[j]) != 0)
                {
                    strcpy(missingMemberNames[numMissingMembers],DSM_DATA_REMOTES(dataObj).members[i].memberName);
                    ITS_TRACE_ERROR(("missingMemberNames %s\n",missingMemberNames[numMissingMembers]));
                    numMissingMembers++;
                }
            }
        }
    }

    for (i = 0; i < *numMembers; i++)
    {
				ITS_TRACE_ERROR(("DSM_DATA_LOCAL(dataObj).memberName%s\n",DSM_DATA_LOCAL(dataObj).memberName));
				ITS_TRACE_ERROR(("transMembers[i] %s\n",transMembers[i]));
				
        //if (strcmp(DSM_DATA_LOCAL(dataObj).memberName, transMembers[i]) == 0)
        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName, missingMemberNames[i]) == 0)
        {
            ITS_TRACE_DEBUG((
                "ProcedureNetworkChange [FtGroupId: %u]: detected member %s "
                "self-missing\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                transMembers[i]));

            ITS_TRACE_DEBUG((
                "ProcedureNetworkChange [FtGroupId: %u]: inconsistent state\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));
#if 0

  /* FIXME: Do not understand yet why we must abort the process. Why can't 
         we just ignore the message.*/

            /**  Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "ProcedureNetworkChange [FtGroupId: %u]: unable to recover "
                "from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));
#endif

            return; /* Not reached. */   
        }
    }

    if (numMissingMembers == 0)
    {
        ITS_TRACE_CRITICAL((
            "ProcedureNetworkChange [FtGroupId: %u]: unable to find missing "
            "member in N processes Fault Tolerance Group\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Nothing to do. */
    }
    else
    {
        for (i = 0; i < (int)numMissingMembers; i++)
        {
            ITS_TRACE_DEBUG((
                "ProcedureNetworkChange [FtGroupId: %u]: member %s missing "
                "from Fault Tolerance Group\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                missingMemberNames[i]));

            /* Update remote members. */
            if (HasRemoteMember(dataObj, missingMemberNames[i]))
            {
                RemoteMemberRemove(dataObj, missingMemberNames[i]);
            }
            else
            {
                /* Check for missing remote members. */

                ITS_TRACE_ERROR((
                    "ProcedureNetworkChange [FtGroupId: %u]: missing remote "
                    "member missing %s\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    missingMemberNames[i]));
            }

            CallMembershipChangeCallbacks(
                dataObj,
                missingMemberNames[i],
                DSM_FT_GROUP_MEMBER_LEAVE);

            CallMembershipChangeCallbacks(
                dataObj,
                missingMemberNames[i],
                DSM_FT_GROUP_MEMBER_DEAD);


            /* Check and update DSM lock. */
            DsmUnlockFullIfLockedByMember(dataObj, missingMemberNames[i]);

            /* Check and update table locks. */
            TablesUnlockFullIfLockedByMember(dataObj, missingMemberNames[i]);

            ret = RemovePendingProceduresFromMemberDueToLock(
                    dataObj,
                    missingMemberNames[i],
                    "ProcedureNetworkChange");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureNetworkChange [FtGroupId: %u]: "
                    "RemovePendingProceduresFromMemberDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            
                /* Ignore non-fatal error (continue). */
            }
        }

        /* Specific processing according to state. */

        switch (DSM_DATA_STATE_DATA(dataObj).state)
        {
        case DSM_STATE_INITIAL:
        {
            /* Nothing to do. */
            break;
        }

        case DSM_STATE_JOINING:
        {
            if (numGroups == 1)
            {
                /* Only member left in Fault Tolerance Group. */

                ITS_C_ASSERT(RemoteMemberSize(dataObj) == 0);

                /* Change state to NORMAL. */
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: change state to "
                    "NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /* Post MASTER-JOIN semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: ready to post "
                    "MASTER-JOIN semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(
                        &DSM_DATA_JOIN_DATA(dataObj).masterSema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                    "ProcedureNetworkChange [FtGroupId: %u]: "
                    "SEMA_PostSemaphore failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: MASTER-JOIN "
                    "semaphore posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Post SYNC semaphore. */
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: ready to post "
                    "SYNC semaphore\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                ret = SEMA_PostSemaphore(&DSM_DATA_SYNC_DATA(dataObj).sema);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureNetworkChange [FtGroupId: %u]: "
                        "SEMA_PostSemaphore failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: SYNC semaphore "
                    "posted\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_NORMAL:
        {
            ret = ExecutePendingProceduresDueToLock(
                    dataObj,
                    "ProcedureNetworkChange");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureNetworkChange [FtGroupId: %u]: "
                    "ExecutePendingProceduresDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureNetworkChange [FtGroupId: %u]: unable to recover"
                    " from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */   
            }

            break;
        }

        case DSM_STATE_SYNC_WAIT:
        case DSM_STATE_SYNC_SLAVE:
        {
            ITS_BOOLEAN missingMaster = ITS_FALSE;

            /* Deduce if master is missing. */
            for (i = 0; i < (int)numMissingMembers; i++)
            {
                if (strcmp(
                        missingMemberNames[i],
                        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName) == 0)
                {
                    missingMaster = ITS_TRUE;
                    break;
                }
            }

            if (missingMaster)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: missing member %s"
                    " is SYNC master",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName));

                /*
                 * Note: in case of SYNC WAIT a DSM SYNC LOCK message has
                 * already been sent by slave in ProcedureJoinInfo (because
                 * state is SYNC WAIT and SYNC master member name is valid).
                 * That makes states SYNC WAIT and SYNC SLAVE equivalent in
                 * current context.
                 */

                /*
                 * Try another master if one available.
                 */

                masterRemoteMember = 
                    RemoteMemberRetrieveFirstValidMaster(dataObj);
                if (masterRemoteMember != NULL)
                {
                    /* Update SYNC related data. */
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);
                    strcpy(
                        DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName,
                        masterRemoteMember->memberName);

                    /* 
                     * Send SYNC LOCK RETRY message. 
                     */

                    syncLockRetryMsg.discriminator = DSM_MSG_SYNC_LOCK_RETRY;
                    syncLockRetryMsg.u.syncLockRetry.tid = AllocateTid(dataObj);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncMasterMemberName,
                        masterRemoteMember->memberName);
                    strcpy(
                        syncLockRetryMsg.u.syncLockRetry.syncSlaveMemberName,
                        DSM_DATA_LOCAL(dataObj).memberName);

                    ITS_TRACE_DEBUG((
                        "ProcedureNetworkChange [FtGroupId: %u]: ready to send"
                        " DSM SYNC LOCK RETRY message | "
                        "tid: %u | "
                        "slave member name: %s | "
                        "master member name: %s\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        syncLockRetryMsg.u.syncLock.tid,
                        syncLockRetryMsg.u.syncLock.syncSlaveMemberName,
                        syncLockRetryMsg.u.syncLock.syncMasterMemberName));

                    ret = GCS_Multicast(
                            DSM_DATA_LOCAL(dataObj).Stubmailbox,
                            GCS_SAFE_MSG,
                            DSM_DATA_LOCAL(dataObj).groupName,
                            DSM_MSG_SYNC_LOCK_RETRY,
                            sizeof(DSM_Message),
                            (const char*)&syncLockRetryMsg);
                    if (ret < 0)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureNetworkChange [FtGroupId: %u]: "
                            "GCS_Multicast failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));

                        ITS_TRACE_CRITICAL((
                            "ProcedureNetworkChange [FtGroupId: %u]: unable to"
                            " recover from previous error: abort\n",
                            DSM_DATA_FT_GROUP_ID(dataObj)));

                        /* Must abort process. */
                        CallCriticalErrorNotificationCallbacks(
                            dataObj,
                            __LINE__,
                            "ProcedureNetworkChange [FtGroupId: %u]: unable to"
                            " recover from error\n",
                            DSM_DATA_FT_GROUP_ID(dataObj));

                        return; /* Not reached. */
                    }

                    ITS_TRACE_DEBUG((
                        "ProcedureNetworkChange [FtGroupId: %u]: DSM SYNC LOCK"
                        " RETRY message successfully sent\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));
                }
                else
                {
                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: detected "
                        "total failure in N processes Fault Tolerance Group\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* Nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_MASTER:
        {
            ITS_BOOLEAN missingSlave = ITS_FALSE;

            /* Deduce if slave is missing. */
            for (i = 0; i < (int)numMissingMembers; i++)
            {
                if (strcmp(
                        missingMemberNames[i],
                        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
                {
                    missingSlave = ITS_TRUE;
                    break;
                }
            }

            if (missingSlave)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: missing member %s"
                    " is SYNC slave",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName));

                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: change state to "
                    "NORMAL\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = DSM_STATE_NORMAL;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(
                        &DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureNetworkChange [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable"
                        " state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureNetworkChange");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureNetworkChange [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_SYNC_NEUTRAL:
        {
            ITS_BOOLEAN missingSlave = ITS_FALSE;

            /* Deduce if slave is missing. */
            for (i = 0; i < (int)numMissingMembers; i++)
            {
                if (strcmp(
                        missingMemberNames[i],
                        DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName) == 0)
                {
                    missingSlave = ITS_TRUE;
                    break;
                }
            }

            if (missingSlave)
            {
                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: missing member %s"
                    " is SYNC slave",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName));

                ITS_TRACE_DEBUG((
                    "ProcedureNetworkChange [FtGroupId: %u]: change state to "
                    "previously saved state\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                DSM_DATA_STATE_DATA(dataObj).state = 
                    DSM_DATA_SYNC_DATA(dataObj).neutralMemberSavedState;

                /*
                 * Release SYNC RWLock (with write priviledge).
                 */
                ret = RWLOCK_UnlockExclusive(
                        &DSM_DATA_SYNC_DATA(dataObj).rwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureNetworkChange [FtGroupId: %u]: "
                        "RWLOCK_UnlockExclusive failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Reset SYNC related data. */
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncSlaveMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);
                memset(
                    DSM_DATA_SYNC_DATA(dataObj).syncMasterMemberName, 
                    0, 
                    GCS_MAX_GROUP_NAME);

                /*
                 * Call procedure(s) stored in SYNC procedure queue if any.
                 */

                ret = ExecutePendingProceduresDueToSync(
                        dataObj, 
                        "ProcedureNetworkChange");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureNetworkChange [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToSync failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureNetworkChange [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureNetworkChange [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* TODO: figure out if there is nothing to do. */
            }

            break;
        }

        case DSM_STATE_INVALID:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);

            break;
        }

        default:
        {
            ITS_BOOLEAN must_not_be_reached = ITS_FALSE;
            ITS_C_ASSERT(must_not_be_reached);
            break;
        }

        }
    }

    ITS_TRACE_DEBUG((
        "ProcedureNetworkChange [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureLockUnlockRow.
 *
 */

static void
ProcedureLockUnlockRow(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* lockUnlockRowMsg;
    char* trailer;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRow [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRow [FtGroupId: %u]: begin with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    lockUnlockRowMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(lockUnlockRowMsg->discriminator == DSM_MSG_LOCK_UNLOCK_ROW);

    /* Deserialize trailer (i.e. key). */
    ITS_C_ASSERT(lockUnlockRowMsg->u.lockUnlockRow.klen <= 
        DSM_MAX_KEY_LENGTH);
    trailer = msg;
    trailer += sizeof(DSM_Message);
    memcpy(
        DSM_DATA_LOCAL(dataObj).bufKey, 
        trailer, 
        lockUnlockRowMsg->u.lockUnlockRow.klen);
    lockUnlockRowMsg->u.lockUnlockRow.key = DSM_DATA_LOCAL(dataObj).bufKey;

    /* Check total size validity. */
    ITS_C_ASSERT(size == 
        sizeof(DSM_Message) + 
        lockUnlockRowMsg->u.lockUnlockRow.klen);

    /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRow [FtGroupId: %u]: received DSM LOCK UNLOCK ROW "
        "message | "
        "tid: %u | "
        "tableId: %u | "
        "object: 0x%X | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        lockUnlockRowMsg->u.lockUnlockRow.tid,
        lockUnlockRowMsg->u.lockUnlockRow.tableId,
        lockUnlockRowMsg->u.lockUnlockRow.objectInTable,
        lockUnlockRowMsg->u.lockUnlockRow.lockUnlockToggle ? "true" : "false",
        lockUnlockRowMsg->u.lockUnlockRow.originThreadId,
        lockUnlockRowMsg->u.lockUnlockRow.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        DSM_RowHeader* head;
        ITS_INT hash;
        ITS_TIME now;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if DSM or Table is locked by another member or
         * thread.
         */

        if (keepOn &&  
                (DsmIsLockedNotByMember(
                    dataObj,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    lockUnlockRowMsg->u.lockUnlockRow.originThreadId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_ROW,
                    lockUnlockRowMsg->u.lockUnlockRow.tid,
                    lockUnlockRowMsg->u.lockUnlockRow.tableId,
                    lockUnlockRowMsg->u.lockUnlockRow.originThreadId,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName,
                    lockUnlockRowMsg->u.lockUnlockRow.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    lockUnlockRowMsg->u.lockUnlockRow.originThreadId,
                    lockUnlockRowMsg->u.lockUnlockRow.tableId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_ROW,
                    lockUnlockRowMsg->u.lockUnlockRow.tid,
                    lockUnlockRowMsg->u.lockUnlockRow.tableId,
                    lockUnlockRowMsg->u.lockUnlockRow.originThreadId,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /* 
         * LOCK UNLOCK ROW identical in all processes that are in NORMAL state.
         */

        if (keepOn)
        {
            /* Deduce actual row pointer from object pointer. */
            row = (DSM_RowHeader*)
                    ((char*)lockUnlockRowMsg->u.lockUnlockRow.objectInTable - 
                        sizeof(DSM_RowHeader));
            
            /* Compute hash value. */
            hash = LocalHash(
                    lockUnlockRowMsg->u.lockUnlockRow.key,
                    lockUnlockRowMsg->u.lockUnlockRow.klen);

            /* Lock hash table. */
            ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: "
                    "MUTEX_AcquireMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
                error = ret;
                keepOn = ITS_FALSE;
            }
            else
            {
                tablesLocked = ITS_TRUE;
            }
        }

        /* Lookup for row list in table according to hash value. */
        if (keepOn)
        {
            ret = HASH_FindEntry(
                        DSM_DATA_MEM_DATA(dataObj)->tables,
                        lockUnlockRowMsg->u.lockUnlockRow.tableId,
                        hash,
                        (ITS_POINTER*)&head);
            if (ret != ITS_SUCCESS)
            {
                error = ITS_ENOTFOUND;
                keepOn = ITS_FALSE;
            }
        }

        /* Scan row list for correct row. */
        if (keepOn)
        {
            tmp = head;
            while (tmp != NULL)
            {
                if (tmp->klen == lockUnlockRowMsg->u.lockUnlockRow.klen &&
                    memcmp(
                        tmp->key,
                        lockUnlockRowMsg->u.lockUnlockRow.key,
                        lockUnlockRowMsg->u.lockUnlockRow.klen) == 0 &&
                    tmp == row)
                {
                    break;
                }
                
                tmp = tmp->next;
            }

            ITS_C_ASSERT(tmp != NULL);

            if (tmp == NULL)
            {
                error = ITS_EINVALIDARGS;
                keepOn = ITS_FALSE;
            }
        }

        /* Lock or unlock row according to lock/unlock toggle. */
        if (keepOn)
        {
            if (lockUnlockRowMsg->u.lockUnlockRow.lockUnlockToggle)
            {
                row->locked = ITS_TRUE;
                now = TIMERS_Time();
                row->lockTime = now;
            }
            else
            {
                row->locked = ITS_FALSE;
                row->lockTime = 0;
            }
        }

        /* Unlock hash table if locked. */
        if (tablesLocked)
        {
            ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: "
                    "MUTEX_ReleaseMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName) == 0)
            {
                /* LOCK UNLOCK ROW message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: DSM LOCK UNLOCK "
                    "ROW message to self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: "
                        "RWLOCK_LockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            lockUnlockRowMsg->u.lockUnlockRow.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "find Tcb for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        lockUnlockRowMsg->u.lockUnlockRow.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: found Tcb for "
                    "Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockRowMsg->u.lockUnlockRow.tid));

                /* Pass result of LOCK UNLOCK ROW through Tcb. */
                tcb->result.discriminator = DSM_RESULT_LOCK_UNLOCK_ROW;
                tcb->result.u.lockUnlockRow.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: "
                        "MUTEX_AcquireMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: "
                        "CONDVAR_Signal failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockRowMsg->u.lockUnlockRow.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: "
                        "RWLOCK_UnlockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockRow [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* LOCK UNLOCK ROW message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: DSM LOCK UNLOCK "
                    "ROW message to other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            lockUnlockRowMsg->u.lockUnlockRow.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_ROW,
                    lockUnlockRowMsg->u.lockUnlockRow.tid,
                    lockUnlockRowMsg->u.lockUnlockRow.tableId,
                    lockUnlockRowMsg->u.lockUnlockRow.originThreadId,
                    lockUnlockRowMsg->u.lockUnlockRow.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockRow");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unacceptable state "
                    "from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRow [FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRow [FtGroupId: %u]: DSM LOCK UNLOCK ROW "
            "message dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRow [FtGroupId: %u]: DSM LOCK UNLOCK ROW "
            "message dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRow [FtGroupId: %u]: DSM LOCK UNLOCK ROW "
            "message dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRow [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureLockUnlockTable.
 *
 */

static void
ProcedureLockUnlockTable(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* lockUnlockTableMsg;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockTable [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockTable [FtGroupId: %u]: begin with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    lockUnlockTableMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(lockUnlockTableMsg->discriminator == 
        DSM_MSG_LOCK_UNLOCK_TABLE);

    /* Check size validity. */
    ITS_C_ASSERT(size == sizeof(DSM_Message));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockTable[FtGroupId:%u]:received"
        "tid:%u|"
        "tableId:%u| "
        "Toggle:%s| "
        "origmemb:%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        lockUnlockTableMsg->
            u.lockUnlockTable.tid,
        lockUnlockTableMsg->
            u.lockUnlockTable.tableId,
        lockUnlockTableMsg->
            u.lockUnlockTable.lockUnlockToggle ? "true" : "false",
        lockUnlockTableMsg->
            u.lockUnlockTable.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if Dsm or Table is locked by another member or
         * thread.
         */

        if (keepOn &&  
                (DsmIsLockedNotByMember(
                    dataObj,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    lockUnlockTableMsg->u.lockUnlockTable.originThreadId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_TABLE,
                    lockUnlockTableMsg->u.lockUnlockTable.tid,
                    lockUnlockTableMsg->u.lockUnlockTable.tableId,
                    lockUnlockTableMsg->u.lockUnlockTable.originThreadId,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockTable");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        if (keepOn && 
                (TableIsLockedNotByMember(
                    dataObj,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName,
                    lockUnlockTableMsg->u.lockUnlockTable.tableId) ||
                 TableIsLockedNotByThread(
                    dataObj,
                    lockUnlockTableMsg->u.lockUnlockTable.originThreadId,
                    lockUnlockTableMsg->u.lockUnlockTable.tableId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_TABLE,
                    lockUnlockTableMsg->u.lockUnlockTable.tid,
                    lockUnlockTableMsg->u.lockUnlockTable.tableId,
                    lockUnlockTableMsg->u.lockUnlockTable.originThreadId,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockTable");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            return; /* Pending procedure to be executed later. */
        }

        /* 
         * LOCK UNLOCK TABLE identical in all processes that are in NORMAL
         * state (specific handling by the process that is locking the table).
         */

    /* FIXME: Ricardo Try to fix race condition */
    /*ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        
    }*/
    

        if (keepOn)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    lockUnlockTableMsg->
                        u.lockUnlockTable.originMemberName) != 0)
            {
                /* LOCK UNLOCK TABLE message to other (i.e. not to self). */

                /* Lock/unlock table. */

                if (lockUnlockTableMsg->u.lockUnlockTable.lockUnlockToggle)
                {
                    ret = TableLock(
                            dataObj, 
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originMemberName,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originThreadId,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.tableId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockTable [FtGroupId: %u]: "
                            "TableLock failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
                else
                {
                    ret = TableUnlock(
                            dataObj, 
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originMemberName,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originThreadId,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.tableId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockTable [FtGroupId: %u]: "
                            "TableUnlock failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
            }
            else
            {
                /* LOCK UNLOCK TABLE message to self. */
                
                /* Lock/unlock table. */

                if (lockUnlockTableMsg->u.lockUnlockTable.lockUnlockToggle)
                {
                    ret = TableLock(
                            dataObj, 
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originMemberName,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originThreadId,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.tableId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockTable [FtGroupId: %u]: "
                            "TableLock failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
                else
                {
                    ret = TableUnlock(
                            dataObj, 
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originMemberName,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.originThreadId,
                            lockUnlockTableMsg->
                                u.lockUnlockTable.tableId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockTable [FtGroupId: %u]: "
                            "TableUnlock failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
            }
        }

    /* FIXME: Ricardo Try to fix race condition */
    /*ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {

    }*/
    


        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName) == 
                    0)
            {
                /* LOCK UNLOCK TABLE message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK"
                    " TABLE message to self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "RWLOCK_LockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            lockUnlockTableMsg->u.lockUnlockTable.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "find Tcb for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        lockUnlockTableMsg->u.lockUnlockTable.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: found Tcb for "
                    "Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockTableMsg->u.lockUnlockTable.tid));

                /* Pass result of LOCK UNLOCK TABLE through Tcb. */
                tcb->result.discriminator = DSM_RESULT_LOCK_UNLOCK_TABLE;
                tcb->result.u.lockUnlockTable.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "MUTEX_AcquireMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "CONDVAR_Signal failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: DSM user thread"
                    " released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockTableMsg->u.lockUnlockTable.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "RWLOCK_UnlockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* LOCK UNLOCK TABLE message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK"
                    " TABLE message to other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }

        /*
         * If table is unlocked execute pending procedures identically in all
         * processes that are in NORMAL state.
         */

        if (keepOn)
        {
            if (!TableIsLocked(
                    dataObj, 
                    lockUnlockTableMsg->u.lockUnlockTable.tableId))
            {
                ret = ExecutePendingProceduresDueToLock(
                        dataObj,
                        "ProcedureLockUnlockTable");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToLock failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockTable [FtGroupId: %u]: "
                        "unacceptable state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */   
                }
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            lockUnlockTableMsg->u.lockUnlockTable.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_TABLE,
                    lockUnlockTableMsg->u.lockUnlockTable.tid,
                    lockUnlockTableMsg->u.lockUnlockTable.tableId,
                    lockUnlockTableMsg->u.lockUnlockTable.originThreadId,
                    lockUnlockTableMsg->u.lockUnlockTable.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockTable");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockTable [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK TABLE "
            "message dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK TABLE "
            "message dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK TABLE "
            "message dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockTable [FtGroupId: %u]: end with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}

/******************************************************************************
 *
 * ProcedureLockUnlockDsm.
 *
 */

static void
ProcedureLockUnlockDsm(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* lockUnlockDsmMsg;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockDsm [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockDsm [FtGroupId: %u]: begin with current state: "
        "%s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    lockUnlockDsmMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(lockUnlockDsmMsg->discriminator == 
        DSM_MSG_LOCK_UNLOCK_DSM);

    /* Check size validity. */
    ITS_C_ASSERT(size == sizeof(DSM_Message));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockDsm [FtGroupId: %u]: received DSM LOCK UNLOCK DSM "
        "message | "
        "tid: %u | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        lockUnlockDsmMsg->
            u.lockUnlockDsm.tid,
        lockUnlockDsmMsg->
            u.lockUnlockDsm.lockUnlockToggle ? "true" : "false",
        lockUnlockDsmMsg->
            u.lockUnlockDsm.originThreadId,
        lockUnlockDsmMsg->
            u.lockUnlockDsm.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN keepOnTransaction = ITS_TRUE;
        int error = ITS_SUCCESS;

        /*
         * Preliminary: check if Dsm is locked by another member or thread.
         */
        if (keepOn && 
                (DsmIsLockedNotByMember(
                    dataObj,
                    lockUnlockDsmMsg->u.lockUnlockDsm.originMemberName) ||
                 DsmIsLockedNotByThread(
                    dataObj,
                    lockUnlockDsmMsg->u.lockUnlockDsm.originThreadId)))
        {
            keepOn = ITS_FALSE;
            keepOnTransaction = ITS_FALSE;

            ret = InsertPendingProcedureDueToLock(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_DSM,
                    lockUnlockDsmMsg->u.lockUnlockDsm.tid,
                    (ITS_UINT)(-1),
                    lockUnlockDsmMsg->u.lockUnlockDsm.originThreadId,
                    lockUnlockDsmMsg->u.lockUnlockDsm.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockDsm");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToLock failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }

        /* 
         * LOCK UNLOCK DSM identical in all processes that are in NORMAL state
         * (specific handling by the process that is locking DSM).
         */

        if (keepOn)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    lockUnlockDsmMsg->
                        u.lockUnlockDsm.originMemberName) != 0)
            {
                /* LOCK UNLOCK DSM message to other (i.e. not to self). */

                /* Lock/unlock DSM. */

                if (lockUnlockDsmMsg->u.lockUnlockDsm.lockUnlockToggle)
                {
                    ret = DsmLock(
                            dataObj, 
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originMemberName,
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originThreadId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockDsm [FtGroupId: %u]: DsmLock "
                            "failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
                else
                {
                    ret = DsmUnlock(
                            dataObj, 
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originMemberName,
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originThreadId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockDsm [FtGroupId: %u]: DsmUnlock"
                            " failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
            }
            else
            {
                /* LOCK UNLOCK DSM message to self. */
                
                /* Lock/unlock DSM. */

                if (lockUnlockDsmMsg->u.lockUnlockDsm.lockUnlockToggle)
                {
                    ret = DsmLock(
                            dataObj, 
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originMemberName,
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originThreadId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockDsm [FtGroupId: %u]: DsmLock "
                            "failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
                else
                {
                    ret = DsmUnlock(
                            dataObj, 
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originMemberName,
                            lockUnlockDsmMsg->
                                u.lockUnlockDsm.originThreadId);
                    if (ret != ITS_SUCCESS)
                    {
                        ITS_TRACE_ERROR((
                            "ProcedureLockUnlockDsm [FtGroupId: %u]: DsmUnlock"
                            " failed: %d\n",
                            DSM_DATA_FT_GROUP_ID(dataObj),
                            ret));
                        error = ret;
                        keepOn = ITS_FALSE;
                    }
                }
            }
        }
        
        if (keepOnTransaction)
        {
            if (strcmp(
                    DSM_DATA_LOCAL(dataObj).memberName,
                    lockUnlockDsmMsg->u.lockUnlockDsm.originMemberName) == 0)
            {
                /* LOCK UNLOCK DSM message to self. */

                DSM_Tcb* tcb;

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK "
                    "DSM message to self\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Lock Tcb table (read lock). */
                ret = RWLOCK_LockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "RWLOCK_LockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                /* Retrieve Tcb from Tid. */
                ret = HASH_FindEntry(
                            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                            0,
                            lockUnlockDsmMsg->u.lockUnlockDsm.tid,
                            (ITS_POINTER*)&tcb);

                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "find Tcb for Tid: %u\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        lockUnlockDsmMsg->u.lockUnlockDsm.tid));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: found Tcb for "
                    "Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockDsmMsg->u.lockUnlockDsm.tid));

                /* Pass result of LOCK UNLOCK DSM through Tcb. */
                tcb->result.discriminator = DSM_RESULT_LOCK_UNLOCK_DSM;
                tcb->result.u.lockUnlockDsm.error = error;

                /* 
                 * Release associated DSM user thread. 
                 */

                ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "MUTEX_AcquireMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = CONDVAR_Signal(&tcb->condVar);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "CONDVAR_Signal failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                    MUTEX_ReleaseMutex(&tcb->condVarGuard);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "MUTEX_ReleaseMutex failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    RWLOCK_UnlockShared(
                        &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM user thread "
                    "released for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockDsmMsg->u.lockUnlockDsm.tid));

                /* Unlock Tcb table (read unlock). */
                ret = RWLOCK_UnlockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "RWLOCK_UnlockShared failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
            else
            {
                /* LOCK UNLOCK DSM message to other (i.e. not to self). */

                ITS_TRACE_DEBUG((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK "
                    "DSM message to other\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Nothing to do. */
            }
        }

        /*
         * If DSM is unlocked execute pending procedures identically in all
         * processes that are in NORMAL state.
         */

        if (keepOn)
        {
            if (!DsmIsLocked(dataObj))
            {
                ret = ExecutePendingProceduresDueToLock(
                        dataObj,
                        "ProcedureLockUnlockDsm");
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                        "ExecutePendingProceduresDueToLock failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));

                    ITS_TRACE_CRITICAL((
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                        "state from previous error: abort\n",
                        DSM_DATA_FT_GROUP_ID(dataObj)));

                    /* Must abort process. */
                    CallCriticalErrorNotificationCallbacks(
                        dataObj,
                        __LINE__,
                        "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to "
                        "recover from from error\n",
                        DSM_DATA_FT_GROUP_ID(dataObj));

                    return; /* Not reached. */
                }
            }
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            lockUnlockDsmMsg->u.lockUnlockDsm.originMemberName) == 0)
        {
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_DSM,
                    lockUnlockDsmMsg->u.lockUnlockDsm.tid,
                    (ITS_UINT)(-1),
                    lockUnlockDsmMsg->u.lockUnlockDsm.originThreadId,
                    lockUnlockDsmMsg->u.lockUnlockDsm.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockDsm");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: unacceptable "
                    "state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockDsm [FtGroupId: %u]: unable to recover"
                    " from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK DSM "
            "message dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK DSM "
            "message dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK DSM "
            "message dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockDsm [FtGroupId: %u]: end with current state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));        
}

/******************************************************************************
 *
 * ProcedureLockUnlockRowNoLock.
 *
 */

static void
ProcedureLockUnlockRowNoLock(
    DSM_DataObject* dataObj,
    GCS_SERVICE service,
    char sender[GCS_MAX_GROUP_NAME],
    ITS_INT numGroups,
    char groups[][GCS_MAX_GROUP_NAME],
    ITS_UINT size,
    char msg[DSM_MAX_MSG_SIZE])
{
    DSM_Message* lockUnlockRowNoLockMsg;
    int ret;

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRowNoLock [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: begin with current "
        "state: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));

    ITS_C_REQUIRE(dataObj != NULL);
    ITS_C_REQUIRE(GCS_IsRegularMsg(service));
    ITS_C_REQUIRE(size >= sizeof(DSM_Message));

    lockUnlockRowNoLockMsg = (DSM_Message*)msg;

    ITS_C_REQUIRE(lockUnlockRowNoLockMsg->discriminator == 
        DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK);

    /* Check size validity. */
    ITS_C_ASSERT(size == sizeof(DSM_Message));

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: received DSM LOCK "
        "UNLOCK ROW NO LOCK message | "
        "tid: %u | "
        "object: 0x%X | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        lockUnlockRowNoLockMsg->
            u.lockUnlockRowNoLock.tid,
        lockUnlockRowNoLockMsg->
            u.lockUnlockRowNoLock.objectInTable,
        lockUnlockRowNoLockMsg->
            u.lockUnlockRowNoLock.lockUnlockToggle ? "true" : "false",
        lockUnlockRowNoLockMsg->
            u.lockUnlockRowNoLock.originThreadId,
        lockUnlockRowNoLockMsg->
            u.lockUnlockRowNoLock.originMemberName));

    if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        ITS_TIME now;
        int error = ITS_SUCCESS;

        /* 
         * LOCK UNLOCK ROW NO LOCK identical in all processes that are in
         * NORMAL state.
         */

        /* Deduce actual row pointer from object pointer. */
        row = (DSM_RowHeader*)
                ((char*)lockUnlockRowNoLockMsg->
                    u.lockUnlockRowNoLock.objectInTable - 
                        sizeof(DSM_RowHeader));

        /* Lock or unlock row according to lock/unlock toggle. */
        if (lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.lockUnlockToggle)
        {
            row->locked = ITS_TRUE;
            now = TIMERS_Time();
            row->lockTime = now;
        }
        else
        {
            row->locked = ITS_FALSE;
            row->lockTime = 0;
        }

        if (strcmp(
                DSM_DATA_LOCAL(dataObj).memberName,
                lockUnlockRowNoLockMsg->
                    u.lockUnlockRowNoLock.originMemberName) == 0)
        {
            /* LOCK UNLOCK ROW NO LOCK message to self. */

            DSM_Tcb* tcb;

            ITS_TRACE_DEBUG((
                "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM LOCK UNLOCK"
                " ROW NO LOCK message to self\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Lock Tcb table (read lock). */
            ret = RWLOCK_LockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "RWLOCK_LockShared failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            /* Retrieve Tcb from Tid. */
            ret = HASH_FindEntry(
                        DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                        0,
                        lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.tid,
                        (ITS_POINTER*)&tcb);

            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "find Tcb for Tid: %u\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.tid));

                RWLOCK_UnlockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: found Tcb for "
                "Tid: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.tid));

            /* Pass result of LOCK UNLOCK ROW NO LOCK through Tcb. */
            tcb->result.discriminator = DSM_RESULT_LOCK_UNLOCK_ROW_NO_LOCK;
            tcb->result.u.lockUnlockRowNoLock.error = error;

            /* 
             * Release associated DSM user thread. 
             */

            ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "MUTEX_AcquireMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                RWLOCK_UnlockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ret = CONDVAR_Signal(&tcb->condVar);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "CONDVAR_Signal failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                RWLOCK_UnlockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
                MUTEX_ReleaseMutex(&tcb->condVarGuard);

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "MUTEX_ReleaseMutex failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                RWLOCK_UnlockShared(
                    &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }

            ITS_TRACE_DEBUG((
                "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM user thread"
                " released for Tid: %u\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.tid));

            /* Unlock Tcb table (read unlock). */
            ret = RWLOCK_UnlockShared(
                &DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "RWLOCK_UnlockShared failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
        else
        {
            /* LOCK UNLOCK ROW NO LOCK message to other (i.e. not to self). */

            ITS_TRACE_DEBUG((
                "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM LOCK UNLOCK"
                " ROW NO LOCK message to other\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Nothing to do. */
        }
    }
    else if (IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        /* 
         * Reached if a DSM_* call has been done after a SYNC LOCK message has
         * been sent (by any process) and before the SYNC LOCK message has been
         * received and processed (normal and possible race condition).
         */

        /*
         * Save procedure in queue (to be called again later when returning
         * from state SYNC to NORMAL).
         */

        if (strcmp(DSM_DATA_LOCAL(dataObj).memberName,
            lockUnlockRowNoLockMsg->
                u.lockUnlockRowNoLock.originMemberName) == 0)
        {        
            ret = InsertPendingProcedureDueToSync(
                    dataObj,
                    DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK,
                    lockUnlockRowNoLockMsg->u.lockUnlockRowNoLock.tid,
                    (ITS_UINT)(-1),
                    lockUnlockRowNoLockMsg->
                        u.lockUnlockRowNoLock.originThreadId,
                    lockUnlockRowNoLockMsg->
                        u.lockUnlockRowNoLock.originMemberName,
                    service,
                    sender,
                    numGroups,
                    groups,
                    size,
                    msg,
                    "ProcedureLockUnlockRowNoLock");
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: "
                    "InsertPendingProcedureDueToSync failed: %d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));

                ITS_TRACE_CRITICAL((
                    "ProcedurelockUnlockRowNoLock [FtGroupId: %u]: "
                    "unacceptable state from previous error: abort\n",
                    DSM_DATA_FT_GROUP_ID(dataObj)));

                /* Must abort process. */
                CallCriticalErrorNotificationCallbacks(
                    dataObj,
                    __LINE__,
                    "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: unable to "
                    "recover from from error\n",
                    DSM_DATA_FT_GROUP_ID(dataObj));

                return; /* Not reached. */
            }
        }
    }
    else if (IsDsmStateSyncSlave(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM LOCK UNLOCK ROW"
            " NO LOCK message dropped due to state SYNC SLAVE\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else if (IsDsmStateSyncWait(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM LOCK UNLOCK ROW"
            " NO LOCK message dropped due to state SYNC WAIT\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));    
    }
    else
    {
        ITS_TRACE_CRITICAL((
            "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: DSM LOCK UNLOCK ROW"
            " NO LOCK message dropped due to states INITIAL or JOINING\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /*
         * Note: Tcb(s) should be processed (including releasing associated DSM
         * user thread(s) by the procedure that is responsible for the
         * transition to state INITIAL (irrelevant for state JOINING).
         */
    }

    ITS_TRACE_DEBUG((
        "ProcedureLockUnlockRowNoLock [FtGroupId: %u]: end with current state:"
        " %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
}


/******************************************************************************
 ******************************************************************************
 **
 ** Allocator related (implementation).
 **
 */

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
    mchunkptr next_1;
    mchunkptr prev;
    do_check_chunk(dataObj, p);
//    ITS_TRACE_ERROR(("Checking CUREENT POINTER(%x) INUSE bit(%d)\n",p,inuse(p)));    
    /* Check whether it claims to be in use ... */
    assert(inuse(p));
    
    next = next_chunk(p);
    next_1 = next_chunk(next);
    prev = prev_chunk(p);
    
 //   ITS_TRACE_ERROR(("Checking PREVIOUS POINTER(%x) INUSE bit(%d)\n",prev,prev_inuse(p)));    
  //  ITS_TRACE_ERROR(("Checking NEXT POINTER(%x) INUSE bit(%d)\n",next,inuse(next_1)));    
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
         //   ITS_TRACE_ERROR(("1.dlmalloc::victim pointer(%x) \n",victim));
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
                
          //  ITS_TRACE_ERROR(("2.INUSE BIT BEFORE SETTING(%x) \n",inuse(victim)));
                set_inuse_bit_at_offset(victim, nb);

                bin->bk = bck;
                bck->fd = bin;
                
                check_malloced_chunk(dataObj, victim, nb);
                
           // ITS_TRACE_ERROR(("2.dlmalloc::victim pointer(%x) \n",victim));
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
                
            //ITS_TRACE_ERROR(("3.dlmalloc::victim pointer(%x) \n",victim));
                return chunk2mem(victim);
            }
            
            /* remove from unsorted list */
            unsorted_chunks(av)->bk = bck;
            bck->fd = unsorted_chunks(av);
            
            /* Take now instead of binning if exact fit */
            if (size == nb)
            {
            //ITS_TRACE_ERROR(("4.INUSE BIT BEFORE SETTING(%x) \n",inuse(victim)));
                set_inuse_bit_at_offset(victim, size);
                check_malloced_chunk(dataObj, victim, nb);
                
            //ITS_TRACE_ERROR(("4.dlmalloc::victim pointer(%x) \n",victim));
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
            //ITS_TRACE_ERROR(("5.INUSE BIT BEFORE SETTING(%x) \n",inuse(victim)));
                    set_inuse_bit_at_offset(victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
            //ITS_TRACE_ERROR(("5.dlmalloc::victim pointer(%x) \n",victim));
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
                    
            //ITS_TRACE_ERROR(("6.dlmalloc::victim pointer(%x) \n",victim));
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
            //ITS_TRACE_ERROR(("7.INUSE BIT BEFORE SETTING(%x) \n",inuse(victim)));
                    set_inuse_bit_at_offset(victim, size);
                    
                    check_malloced_chunk(dataObj, victim, nb);
                    
            //ITS_TRACE_ERROR(("7.dlmalloc::victim pointer(%x) \n",victim));
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
                    
            //ITS_TRACE_ERROR(("8.dlmalloc::victim pointer(%x) \n",victim));
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
            
            //ITS_TRACE_ERROR(("9.dlmalloc::victim pointer(%x) \n",victim));
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
    static int count = 0;
    count++; 
//    ITS_TRACE_CRITICAL(("dlfree count(%d) \n",count)); 
    
    /* free(0) has no effect */
//       ITS_TRACE_CRITICAL(("dlFree:Freed Pointer[%x] \n",mem)); 
    if (mem != 0)
    {
        p = mem2chunk(mem);
        size = chunksize(p);
        
        check_inuse_chunk(dataObj, p);
//       ITS_TRACE_ERROR(("ENTRY:IN dlfree \n")); 
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

 //      ITS_TRACE_ERROR(("EXIT:INUSE BIT AFTER FREE (%d) \n",inuse(p))); 
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
    static int count = 0;
    count++; 
//    ITS_TRACE_CRITICAL(("dlcalloc count(%d) \n",count)); 
    void* mem = dlmalloc(dataObj, n_elements * elem_size);
//    ITS_TRACE_ERROR(("dlmalloc return pointer(%x) \n",mem)); 
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
//    ITS_TRACE_CRITICAL(("dlcalloc pointer ALLOCATED [%x]",mem));
    return mem;
}


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (GCS) Impl (implementation) class.
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
    DSM_Message     allocateRowMsg;
    char*           trailer;
    void*           result;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(error != NULL);
    ITS_C_REQUIRE(size <= DSM_MAX_OBJECT_SIZE);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    threadId = THREAD_GetCurrentThreadID();
    
    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Alloc [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Alloc [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * Alloc allowed in INITIAL state (special case: current process allocation
     * only - to be synchronized later).
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* allocPtr;
        DSM_RowHeader* tmp;
        DSM_RowHeader** list;
        ITS_TIME now;
        ITS_INT hash = 0;
        ITS_UINT round;
        ITS_UINT rowSize = size;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Alloc [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Alloc [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return allocPtr;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Alloc [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Alloc [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Alloc [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        *error = ITS_ECALLREJECTED;
        return NULL;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }
    
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

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* 
     * Send DSM ALLOCATE ROW message to GCS. 
     */

    allocateRowMsg.discriminator            = DSM_MSG_ALLOCATE_ROW;
    allocateRowMsg.u.allocateRow.tid        = tid;
    allocateRowMsg.u.allocateRow.tableId    = tableId;
    allocateRowMsg.u.allocateRow.key        = NULL; /* key is trailer. */
    allocateRowMsg.u.allocateRow.klen       = klen;
    allocateRowMsg.u.allocateRow.size       = size;
    allocateRowMsg.u.allocateRow.withLock   = withLock;
    allocateRowMsg.u.allocateRow.originThreadId = threadId;
    memcpy(
        allocateRowMsg.u.allocateRow.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

    /* Lock bufAllocate (not thread-safe). */
    ret = MUTEX_AcquireMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

#if defined(DEBUG) || defined(_DEBUG)
    memset(
        DSM_DATA_LOCAL(dataObj).bufAllocate, 
        0, 
        sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH);
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(
        DSM_DATA_LOCAL(dataObj).bufAllocate, 
        &allocateRowMsg, 
        sizeof(DSM_Message));

    /* Serialize trailer (i.e. key). */
    trailer = (char*)DSM_DATA_LOCAL(dataObj).bufAllocate;
    trailer += sizeof(DSM_Message);
    memcpy(trailer, key, klen);

    /* 
     * Acquire Tcb condition variable associated mutex BEFORE sending ALLOCATE
     * ROW message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        *error = ret;
        return NULL;
    }

     /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: ready to send DSM ALLOCATE ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "size: %u | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        size,
        withLock ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_ALLOCATE_ROW,
                sizeof(DSM_Message) + klen,
                (const char*)DSM_DATA_LOCAL(dataObj).bufAllocate);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        *error = ITS_EGCSMULTICASTFAIL;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: DSM ALLOCATE ROW message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Unlock bufAllocate (not thread-safe). */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufAllocateLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        *error = ret;
        return NULL;
    }

    /* 
     * Wait on Tcb condition variable for ALLOCATE ROW message to be handled
     * (message sent to all processes through GCS). Condition variable 
     * associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        *error = ret;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Alloc [FtGroupId: %u]: Finished to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Alloc [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        *error = ITS_ECALLREJECTED;
        return NULL;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_ALLOCATE_ROW);

    result = tcb->result.u.allocateRow.allocPtr;
    *error = tcb->result.u.allocateRow.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        *error = ret;
        return NULL;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    return result;
}

/*
 * AllocLocal.
 */
static void*
AllocLocal(
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
    DSM_Message     allocateRowMsg;
    char*           trailer;
    void*           result;
    int             ret;
    DSM_RowHeader* allocPtr;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(error != NULL);
    ITS_C_REQUIRE(size <= DSM_MAX_OBJECT_SIZE);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Alloc [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Alloc [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /*
     * Alloc allowed in INITIAL state (special case: current process allocation
     * only - to be synchronized later).
     */
    /*if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))*/
    /*if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))*/
    {
        DSM_RowHeader* tmp;
        DSM_RowHeader** list;
        ITS_TIME now;
        ITS_INT hash = 0;
        ITS_UINT round;
        ITS_UINT rowSize = size;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Alloc [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Alloc [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Alloc [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

    }

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
    DSM_Message     findRowMsg;
    char*           trailer;
    void*           result;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Find [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Find [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * Find allowed in INITIAL state (special case: current process find only -
     * to be synchronized later). Special case for FindNoLock (can be local to
     * process to improve performance).
     */
#if defined(DSM_GCS_FIND_NO_LOCK_NOT_LOCAL)
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
#else // !defined(DSM_GCS_FIND_NO_LOCK_NOT_LOCAL)
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state) || !withLock)
#endif // defined(DSM_GCS_FIND_NO_LOCK_NOT_LOCAL)
    {
        DSM_RowHeader* findPtr = NULL;
        DSM_RowHeader* row;
        ITS_INT hash;
        ITS_TIME now;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Find [FtGroupId: %u]: unacceptable state from previous error:"
                " abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Find [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }
if ( tableId == 31)
{
    counter ++;
    if (counter == 528)
    {
        int x = 0;
        while(x < 5)
        {
#if defined(WIN32)
            Sleep(1);
#else
            sleep(1);
#endif
            x++;
        }
    }
    if (*error == -65)
    {
    }
}

        return findPtr;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Find [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Find [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Find [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        *error = ITS_ECALLREJECTED;
        return NULL;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }
    
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

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        *error = ret;
        return NULL;
    }

    /* 
     * Send DSM FIND ROW message. 
     */

    findRowMsg.discriminator        = DSM_MSG_FIND_ROW;
    findRowMsg.u.findRow.tid        = tid;
    findRowMsg.u.findRow.tableId    = tableId;
    findRowMsg.u.findRow.key        = NULL; /* key is trailer. */
    findRowMsg.u.findRow.klen       = klen;
    findRowMsg.u.findRow.withLock   = withLock;
    findRowMsg.u.findRow.originThreadId = threadId;
    memcpy(
        findRowMsg.u.findRow.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

    /* Lock bufFind (not thread-safe). */
    ret = MUTEX_AcquireMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

#if defined(DEBUG) || defined(_DEBUG)
    memset(
        DSM_DATA_LOCAL(dataObj).bufFind, 
        0, 
        sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH);
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(DSM_DATA_LOCAL(dataObj).bufFind, &findRowMsg, sizeof(DSM_Message));

    /* Serialize trailer (i.e. key). */
    trailer = (char*)DSM_DATA_LOCAL(dataObj).bufFind;
    trailer += sizeof(DSM_Message);
    memcpy(trailer, key, klen);

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending FIND ROW
     * message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        *error = ret;
        return NULL;
    }

     /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: ready to send DSM FIND ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        withLock ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_FIND_ROW,
                sizeof(DSM_Message) + klen,
                (const char*)DSM_DATA_LOCAL(dataObj).bufFind);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        *error = ITS_EGCSMULTICASTFAIL;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: DSM FIND ROW message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Unlock bufFind (not thread-safe). */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFindLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        *error = ret;
        return NULL;
    }

    /* 
     * Wait on Tcb condition variable for FIND ROW message to be handled
     * (message sent to all processes through GCS). Condition variable
     * associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        *error = ret;
        return NULL;
    }

    ITS_TRACE_DEBUG((
        "Find [FtGroupId: %u]: Finished to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Find [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        *error = ITS_ECALLREJECTED;
        return NULL;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_FIND_ROW);

    result = tcb->result.u.findRow.findPtr;
    *error = tcb->result.u.findRow.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        *error = ret;
        return NULL;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Find [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        *error = ret;
        return NULL;
    }
    return result;
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
    DSM_Message     freeRowMsg;
    char*           trailer;
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(object != NULL);

    /* 
     * Check that row is locked must be done in ProcedureFreeRow for thread
     * safety reasons. 
     */

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Free [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Free [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * Free allowed in INITIAL state (special case: current process free only -
     * to be synchronized later). 
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        DSM_RowHeader* head;
        DSM_RowHeader** list;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Free [FtGroupId: %u]: unacceptable state from previous error:"
                " abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Free [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return result;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Free [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Free [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    
    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Free [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
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

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM FREE ROW message. 
     */

    freeRowMsg.discriminator            = DSM_MSG_FREE_ROW;
    freeRowMsg.u.freeRow.tid            = tid;
    freeRowMsg.u.freeRow.tableId        = tableId;
    freeRowMsg.u.freeRow.key            = NULL; /* key is trailer. */
    freeRowMsg.u.freeRow.klen           = klen;
    freeRowMsg.u.freeRow.objectInTable  = object; /* Ptr value relevant. */
    freeRowMsg.u.freeRow.withLock       = withLock;
    freeRowMsg.u.freeRow.originThreadId = threadId;
    memcpy(
        freeRowMsg.u.freeRow.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

    /* Lock bufFree (not thread-safe). */
    ret = MUTEX_AcquireMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        return ret;
    }

#if defined(DEBUG) || defined(_DEBUG)
    memset(
        DSM_DATA_LOCAL(dataObj).bufFree, 
        0, 
        sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH);
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(DSM_DATA_LOCAL(dataObj).bufFree, &freeRowMsg, sizeof(DSM_Message));

    /* Serialize trailer (i.e. key). */
    trailer = (char*)DSM_DATA_LOCAL(dataObj).bufFree;
    trailer += sizeof(DSM_Message);
    memcpy(trailer, key, klen);

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending FREE ROW
     * message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        return ret;
    }

     /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: ready to send DSM FREE ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "object: 0x%X | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        object,
        withLock ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_FREE_ROW,
                sizeof(DSM_Message) + klen,
                (const char*)DSM_DATA_LOCAL(dataObj).bufFree);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: DSM FREE ROW message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Unlock bufFree (not thread-safe). */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufFreeLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    /* 
     * Wait on Tcb condition variable for FREE ROW message to be handled
     * (message sent to all processes through GCS). Condition variable 
     * associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "Free [FtGroupId: %u]: Finished to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Free [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_FREE_ROW);
    result = tcb->result.u.freeRow.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
}

/*
 * FreeLocal.
 */
static int
FreeLocal(
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
    DSM_Message     freeRowMsg;
    char*           trailer;
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(object != NULL);

    /*
     * Check that row is locked must be done in ProcedureFreeRow for thread
     * safety reasons.
     */

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Free [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Free [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /*
     * Free allowed in INITIAL state (special case: current process free only -
     * to be synchronized later).
     */
    /*if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))*/
    /*if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))*/
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        DSM_RowHeader* head;
        DSM_RowHeader** list;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Free [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Free [FtGroupId: %u]: unacceptable state from previous error:"
                " abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Free [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

    }

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
    ITS_UINT        size;
    DSM_RowHeader*  row;
    mchunkptr       mem;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     commitRowMsg;
    char*           trailer;
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(object != NULL);

    /* 
     * Check that row is locked must be done in ProcedureCommitRow for thread
     * safety reasons. 
     */

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

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

    /* Must always be true (even if memory alignment). */
    ITS_C_ASSERT(size <= DSM_MAX_OBJECT_SIZE + sizeof(ITS_UINT));
 //   ITS_TRACE_ERROR(("1.Before Commmit Mutx\n"));
    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
  //  ITS_TRACE_ERROR(("1.After Commmit Mutx\n"));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Commit [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Commit [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * Commit allowed in INITIAL state (special case: current process commit 
     * only - to be synchronized later). 
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* tmp;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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

        /* No need to update object locally. */

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Commit [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Commit [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }
        return result;
    }


    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Commit [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Commit [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Commit [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    //ITS_TRACE_ERROR(("2.Before Commmit Mutx\n"));
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    //ITS_TRACE_ERROR(("2.After Commmit Mutx\n"));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
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

    /* Lock Tcb table (write lock). */
    //ITS_TRACE_ERROR(("3.Before Commmit Mutx\n"));
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    //ITS_TRACE_ERROR(("3.After Commmit Mutx\n"));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM COMMIT ROW message. 
     */

    commitRowMsg.discriminator              = DSM_MSG_COMMIT_ROW;
    commitRowMsg.u.commitRow.tid            = tid;
    commitRowMsg.u.commitRow.tableId        = tableId;
    commitRowMsg.u.commitRow.key            = NULL; /* key is trailer #1. */
    commitRowMsg.u.commitRow.klen           = klen;
    commitRowMsg.u.commitRow.object         = NULL; /* object is trailer #2. */
    commitRowMsg.u.commitRow.size           = size;
    commitRowMsg.u.commitRow.objectInTable  = object; /* Ptr value relevant. */
    commitRowMsg.u.commitRow.withLock       = withLock;
    commitRowMsg.u.commitRow.originThreadId = threadId;
    memcpy(
        commitRowMsg.u.commitRow.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

    /* Lock bufCommit (not thread-safe). */
    ret = MUTEX_AcquireMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

/* 
 * Appropriate count of memset should include DSM_MAX_OBJECT_SIZE but it is too
 * time consuming even for debug builds.
 */
#if defined(DEBUG) || defined(_DEBUG)
    memset(
        DSM_DATA_LOCAL(dataObj).bufCommit, 
        0, 
        sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH);
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(
        DSM_DATA_LOCAL(dataObj).bufCommit, 
        &commitRowMsg, 
        sizeof(DSM_Message));

    /* Serialize trailer #1 (i.e. key). */
    trailer = (char*)DSM_DATA_LOCAL(dataObj).bufCommit;
    trailer += sizeof(DSM_Message);
    memcpy(trailer, key, klen);

    /* Serialize trailer #2 (i.e. object). */
    trailer += klen;
    memcpy(trailer, object, size);

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending COMMIT
     * ROW message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        return ret;
    }

     /* TODO: improve tracing by adding klen, key, object contents? */
    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: ready to send DSM COMMIT ROW message | "
        "tid: %u | "
        "tableId: %u | "
        "size: %u | "
        "object: 0x%X | "
        "withLock: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        size,
        object,
        withLock ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_COMMIT_ROW,
                sizeof(DSM_Message) + klen + size,
                (const char*)DSM_DATA_LOCAL(dataObj).bufCommit);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: DSM COMMIT ROW message successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Unlock bufCommit (not thread-safe). */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufCommitLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    /* 
     * Wait on Tcb condition variable for COMMIT ROW message to be handled
     * (message sent to all processes through GCS). Condition variable 
     * associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "Commit [FtGroupId: %u]: Finished to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "Commit [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_COMMIT_ROW);
    result = tcb->result.u.commitRow.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
}

/*
 * CommitLocal.
 */
static int
CommitLocal(
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
    ITS_UINT        size;
    DSM_RowHeader*  row;
    mchunkptr       mem;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     commitRowMsg;
    char*           trailer;
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(object != NULL);

    /*
     * Check that row is locked must be done in ProcedureCommitRow for thread
     * safety reasons.
     */

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

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

    /* Must always be true (even if memory alignment). */
    ITS_C_ASSERT(size <= DSM_MAX_OBJECT_SIZE + sizeof(ITS_UINT));

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "Commit [FtGroupId: %u]: unacceptable state from previous error: "
            "abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "Commit [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /*
     * Commit allowed in INITIAL state (special case: current process commit
     * only - to be synchronized later).
     */
    /*if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))*/
    /*if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))*/
    {
        DSM_RowHeader* tmp;
        ITS_INT hash;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

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
                        DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                       // DSM_DATA_MEM_DATA(dataObj)->tables,
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

        /* No need to update object locally. */

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

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "Commit [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "Commit [FtGroupId: %u]: unacceptable state from previous "
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "Commit [FtGroupId: %u]: unable to recover from from error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

    }

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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     lockUnlockRowMsg;
    char*           trailer;
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen > 0);
    ITS_C_REQUIRE(klen <= (ITS_UINT)DSM_MAX_KEY_LENGTH);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlock [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlock [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * LockUnlock allowed in INITIAL state (special case: current process
     * lock/unlock only - to be synchronized later). 
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        DSM_RowHeader* tmp;
        DSM_RowHeader* head;
        ITS_INT hash;
        ITS_TIME now;
        ITS_BOOLEAN keepOn = ITS_TRUE;
        ITS_BOOLEAN tablesLocked = ITS_FALSE;

        /* Deduce actual row pointer from object pointer. */
        row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

        /* Compute hash value. */
        hash = LocalHash(key, klen);

        /* Lock hash table. */
        ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlock [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
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

        /* Lock or unlock row according to lock/unlock toggle. */
        if (keepOn)
        {
            if (lockUnlockToggle)
            {
                row->locked = ITS_TRUE;
                now = TIMERS_Time();
                row->lockTime = now;
            }
            else
            {
                row->locked = ITS_FALSE;
                row->lockTime = 0;
            }
        }

        /* Unlock hash table if locked. */
        if (tablesLocked)
        {
            ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
            if (ret != ITS_SUCCESS)
            {
                ITS_TRACE_ERROR((
                    "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
                    "%d\n",
                    DSM_DATA_FT_GROUP_ID(dataObj),
                    ret));
            }
        }

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "LockUnlock [FtGroupId: %u]: unacceptable state from previous"
                "error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "LockUnlock [FtGroupId: %u]: unable to recover from from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return result;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlock [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlock [FtGroupId: %u]: unable to recover from from error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    
    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlock [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM LOCK UNLOCK ROW message. 
     */

    lockUnlockRowMsg.discriminator = 
        DSM_MSG_LOCK_UNLOCK_ROW;
    lockUnlockRowMsg.u.lockUnlockRow.tid = 
        tid;
    lockUnlockRowMsg.u.lockUnlockRow.tableId = 
        tableId;
    lockUnlockRowMsg.u.lockUnlockRow.key = 
        NULL; /* key is trailer. */
    lockUnlockRowMsg.u.lockUnlockRow.klen = 
        klen;
    lockUnlockRowMsg.u.lockUnlockRow.objectInTable = 
        object; /* Ptr value relevant. */
    lockUnlockRowMsg.u.lockUnlockRow.lockUnlockToggle = 
        lockUnlockToggle;
    lockUnlockRowMsg.u.lockUnlockRow.originThreadId =
        threadId;
    memcpy(
        lockUnlockRowMsg.u.lockUnlockRow.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

    /* Lock bufLockUnlock (not thread-safe). */
    ret = MUTEX_AcquireMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

#if defined(DEBUG) || defined(_DEBUG)
    memset(
        DSM_DATA_LOCAL(dataObj).bufLockUnlock, 
        0, 
        sizeof(DSM_Message) + DSM_MAX_KEY_LENGTH);
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(
        DSM_DATA_LOCAL(dataObj).bufLockUnlock, 
        &lockUnlockRowMsg, 
        sizeof(DSM_Message));

    /* Serialize trailer (i.e. key). */
    trailer = (char*)DSM_DATA_LOCAL(dataObj).bufLockUnlock;
    trailer += sizeof(DSM_Message);
    memcpy(trailer, key, klen);

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending LOCK 
     * UNLOCK ROW message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        return ret;
    }

     /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "LockUnlock [FtGroupId: %u]: ready to send DSM LOCK UNLOCK ROW "
        "message | "
        "tid: %u | "
        "tableId: %u | "
        "object: 0x%X | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        object,
        lockUnlockToggle ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_LOCK_UNLOCK_ROW,
                sizeof(DSM_Message) + klen,
                (const char*)DSM_DATA_LOCAL(dataObj).bufLockUnlock);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "LockUnlock [FtGroupId: %u]: DSM LOCK UNLOCK ROW message successfully "
        "sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* Unlock bufLockUnlock (not thread-safe). */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_LOCAL(dataObj).bufLockUnlockLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    /* 
     * Wait on Tcb condition variable for LOCK UNLOCK ROW message to be 
     * handled (message sent to all processes through GCS). Condition
     * variable associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "LockUnlock [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlock [FtGroupId: %u]: Finished to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlock [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_LOCK_UNLOCK_ROW);
    result = tcb->result.u.lockUnlockRow.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlock [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     lockUnlockRowNoLockMsg;
    char            bufLockUnlockNoLock[sizeof(DSM_Message)];
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockNoLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockNoLock [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* 
     * LockUnlockNoLock allowed in INITIAL state (special case: current process
     * lock/unlock no lock only - to be synchronized later). 
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        DSM_RowHeader* row;
        ITS_TIME now;

        /* Deduce actual row pointer from object pointer. */
        row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

        /* Lock or unlock row according to lock/unlock toggle. */
        if (lockUnlockToggle)
        {
            row->locked = ITS_TRUE;
            now = TIMERS_Time();
            row->lockTime = now;
        }
        else
        {
            row->locked = ITS_FALSE;
            row->lockTime = 0;
        }

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlockNoLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "LockUnlockNoLock [FtGroupId: %u]: unacceptable state from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "LockUnlockNoLock [FtGroupId: %u]: unable to recover from from"
                " error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return result;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockNoLock [FtGroupId: %u]: unacceptable state from "
            "previous error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockNoLock [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockNoLock [FtGroupId: %u]: invalid call due to state: "
            "%s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_UnlockShared failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM LOCK UNLOCK ROW NO LOCK message. 
     */

    lockUnlockRowNoLockMsg.discriminator = 
        DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK;
    lockUnlockRowNoLockMsg.u.lockUnlockRowNoLock.tid = 
        tid;
    lockUnlockRowNoLockMsg.u.lockUnlockRowNoLock.objectInTable = 
        object; /* Ptr value relevant. */
    lockUnlockRowNoLockMsg.u.lockUnlockRowNoLock.lockUnlockToggle = 
        lockUnlockToggle;
    lockUnlockRowNoLockMsg.u.lockUnlockRowNoLock.originThreadId = 
        threadId;
    memcpy(
        lockUnlockRowNoLockMsg.u.lockUnlockRowNoLock.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);


#if defined(DEBUG) || defined(_DEBUG)
    memset(bufLockUnlockNoLock, 0, sizeof(DSM_Message));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(bufLockUnlockNoLock, &lockUnlockRowNoLockMsg, sizeof(DSM_Message));

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending LOCK 
     * UNLOCK ROW NO LOCK message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

     /* TODO: improve tracing by adding klen and key? */
    ITS_TRACE_DEBUG((
        "LockUnlockNoLock [FtGroupId: %u]: ready to send DSM LOCK UNLOCK ROW "
        "NO LOCK message | "
        "tid: %u | "
        "object: 0x%X | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        object,
        lockUnlockToggle ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK,
                sizeof(DSM_Message),
                bufLockUnlockNoLock);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockNoLock [FtGroupId: %u]: DSM LOCK UNLOCK ROW NO LOCK message"
        " successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* 
     * Wait on Tcb condition variable for LOCK UNLOCK ROW NO LOCK message to
     * be handled (message sent to all processes through GCS). Condition
     * variable associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "LockUnlockNoLock [FtGroupId: %u]: Ready to wait on condition variable"
        " | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockNoLock [FtGroupId: %u]: Finished to wait on condition "
        "variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockNoLock [FtGroupId: %u]: invalid call due to state: "
            "%s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == 
        DSM_RESULT_LOCK_UNLOCK_ROW_NO_LOCK);
    result = tcb->result.u.lockUnlockRowNoLock.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockNoLock [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT    threadId;
    ITS_UINT    tid;
    DSM_Tcb*    tcb;
    DSM_Message lockUnlockDsmMsg;
    char        bufLockUnlockDsm[sizeof(DSM_Message)];
    int         result = ITS_SUCCESS;
    int         ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockDsm [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockDsm [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /*
     * LockUnlockDsm allowed in INITIAL state (special case: current process
     * lock/unlock only - to be synchronized later).
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_BOOLEAN keepOn = ITS_TRUE;

        if (keepOn)
        {
            if (lockUnlockToggle)
            {
                ret = DsmLock(
                        dataObj, 
                        DSM_DATA_LOCAL(dataObj).memberName, 
                        threadId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockDsm [FtGroupId: %u]: DsmLock failed: %d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
            else
            {
                ret = DsmUnlock(
                        dataObj, 
                        DSM_DATA_LOCAL(dataObj).memberName, 
                        threadId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockDsm [FtGroupId: %u]: DsmUnlock failed: "
                        "%d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
        }

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlockDsm [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "LockUnlockDsm [FtGroupId: %u]: unacceptable state from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "LockUnlockDsm [FtGroupId: %u]: unable to recover from from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return result;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockDsm [FtGroupId: %u]: unacceptable state from previous "
            "error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockDsm [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    
    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockDsm [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_UnlockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM LOCK UNLOCK DSM message. 
     */

    lockUnlockDsmMsg.discriminator = 
        DSM_MSG_LOCK_UNLOCK_DSM;
    lockUnlockDsmMsg.u.lockUnlockDsm.tid = 
        tid;
    lockUnlockDsmMsg.u.lockUnlockDsm.lockUnlockToggle = 
        lockUnlockToggle;
    lockUnlockDsmMsg.u.lockUnlockDsm.originThreadId =
        threadId;
    memcpy(
        lockUnlockDsmMsg.u.lockUnlockDsm.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

#if defined(DEBUG) || defined(_DEBUG)
    memset(bufLockUnlockDsm, 0, sizeof(DSM_Message));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(bufLockUnlockDsm, &lockUnlockDsmMsg, sizeof(DSM_Message));

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending LOCK
     * UNLOCK DSM message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockDsm [FtGroupId: %u]: ready to send DSM LOCK UNLOCK DSM "
        "message | "
        "tid: %u | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        lockUnlockToggle ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_LOCK_UNLOCK_DSM,
                sizeof(DSM_Message),
                bufLockUnlockDsm);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockDsm [FtGroupId: %u]: DSM LOCK UNLOCK DSM message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* 
     * Wait on Tcb condition variable for LOCK UNLOCK DSM message to be 
     * handled (message sent to all processes through GCS). Condition
     * variable associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "LockUnlockDsm [FtGroupId: %u]: Ready to wait on condition variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockDsm [FtGroupId: %u]: Finished to wait on condition variable"
        " | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockDsm [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_LOCK_UNLOCK_DSM);
    result = tcb->result.u.lockUnlockDsm.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_LockExclusive failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockDsm [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     lockUnlockTableMsg;
    char            bufLockUnlockTable[sizeof(DSM_Message)];
    int             result = ITS_SUCCESS;
    int             ret;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    threadId = THREAD_GetCurrentThreadID();

    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockTable [FtGroupId: %u]: unacceptable state from previous"
            " error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockTable [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    /*
     * LockUnlockTable allowed in INITIAL state (special case: current process
     * lock/unlock only - to be synchronized later).
     */
    if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_BOOLEAN keepOn = ITS_TRUE;

        if (keepOn)
        {
            if (lockUnlockToggle)
            {
                ret = TableLock(
                        dataObj,
                        DSM_DATA_LOCAL(dataObj).memberName,
                        threadId,
                        tableId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockTable [FtGroupId: %u]: TableLock failed: "
                        "%d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
            else
            {
                ret = TableUnlock(
                        dataObj,
                        DSM_DATA_LOCAL(dataObj).memberName,
                        threadId,
                        tableId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockTable [FtGroupId: %u]: TableUnlock failed: "
                        "%d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
        }

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "LockUnlockTable [FtGroupId: %u]: unacceptable state from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "LockUnlockTable [FtGroupId: %u]: unable to recover from from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

        return result;
    }

    /* Unlock state. */
    ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockTable [FtGroupId: %u]: unacceptable state from previous"
            " error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));

        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockTable [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }
    
    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockTable [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Acquire and release SYNC RWLock (i.e. to block if SYNC in progress). */

    /* Acquire SYNC RWLock (read lock). */
    ret = RWLOCK_LockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_LockShared failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Release SYNC RWLock (read lock). */
    ret = RWLOCK_UnlockShared(&DSM_DATA_SYNC_DATA(dataObj).rwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_UnlockShared failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }
    
    /* Allocate Tid and Tcb. */
    tid = AllocateTid(dataObj);

    ret = AllocateTcb(dataObj, &tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: AllocateTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Initialize Tcb with Tid. */
    tcb->tid = tid;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Insert Tcb. */
    ret = HASH_AddEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid,
                (ITS_POINTER)tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: HASH_AddEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        HASH_DeleteEntry(
            DSM_DATA_TCB_MANAGER(dataObj).table.hash,
            0,
            tid);
        FreeTcb(dataObj, tcb);
        return ret;
    }

    /* 
     * Send DSM LOCK UNLOCK TABLE message. 
     */

    lockUnlockTableMsg.discriminator = 
        DSM_MSG_LOCK_UNLOCK_TABLE;
    lockUnlockTableMsg.u.lockUnlockTable.tid = 
        tid;
    lockUnlockTableMsg.u.lockUnlockTable.tableId = 
        tableId;
    lockUnlockTableMsg.u.lockUnlockTable.lockUnlockToggle = 
        lockUnlockToggle;
    lockUnlockTableMsg.u.lockUnlockTable.originThreadId =
        threadId;
    memcpy(
        lockUnlockTableMsg.u.lockUnlockTable.originMemberName,
        DSM_DATA_LOCAL(dataObj).memberName,
        GCS_MAX_GROUP_NAME);

#if defined(DEBUG) || defined(_DEBUG)
    memset(bufLockUnlockTable, 0, sizeof(DSM_Message));
#endif /* defined(DEBUG) || defined(_DEBUG) */

    memcpy(bufLockUnlockTable, &lockUnlockTableMsg, sizeof(DSM_Message));

    /*
     * Acquire Tcb condition variable associated mutex BEFORE sending LOCK
     * UNLOCK TABLE message.
     */
    ret = MUTEX_AcquireMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: MUTEX_AcquireMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockTable [FtGroupId: %u]: ready to send DSM LOCK UNLOCK TABLE "
        "message | "
        "tid: %u | "
        "tableId: %u | "
        "lockUnlockToggle: %s | "
        "origin threadId: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        tableId,
        lockUnlockToggle ? "true" : "false",
        threadId,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                DSM_MSG_LOCK_UNLOCK_TABLE,
                sizeof(DSM_Message),
                bufLockUnlockTable);
    if (ret < 0)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: GCS_Multicast failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        /* Note: most likely a fatal error but still try to keep on. */
        return ITS_EGCSMULTICASTFAIL;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockTable [FtGroupId: %u]: DSM LOCK UNLOCK TABLE message "
        "successfully sent\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));

    /* 
     * Wait on Tcb condition variable for LOCK UNLOCK TABLE message to be 
     * handled (message sent to all processes through GCS). Condition
     * variable associated mutex has been acquired before sending message.
     */
    ITS_TRACE_DEBUG((
        "LockUnlockTable [FtGroupId: %u]: Ready to wait on condition variable"
        " | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    /* Actual wait. */
    ret = CONDVAR_Wait(&tcb->condVar, &tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: CONDVAR_Wait failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&tcb->condVarGuard);
        return ret;
    }

    ITS_TRACE_DEBUG((
        "LockUnlockTable [FtGroupId: %u]: Finished to wait on condition "
        "variable | "
        "tid: %u | "
        "origin member: %s\n",
        DSM_DATA_FT_GROUP_ID(dataObj),
        tid,
        DSM_DATA_LOCAL(dataObj).memberName));

    ret = MUTEX_ReleaseMutex(&tcb->condVarGuard);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Check for NORMAL or SYNC (MASTER or NEUTRAL) state. */
    if (!IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state) &&
        !IsDsmStateSyncMasterNeutral(DSM_DATA_STATE_DATA(dataObj).state))
    {
        ITS_TRACE_DEBUG((
            "LockUnlockTable [FtGroupId: %u]: invalid call due to state: %s\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            StateToStr(DSM_DATA_STATE_DATA(dataObj).state)));
        return ITS_ECALLREJECTED;
    }

    /* Retrieve result from Tcb. */
    ITS_C_ASSERT(tcb->result.discriminator == DSM_RESULT_LOCK_UNLOCK_TABLE);
    result = tcb->result.u.lockUnlockTable.error;

    /* Lock Tcb table (write lock). */
    ret = RWLOCK_LockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_LockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Remove Tcb. */
    ret = HASH_DeleteEntry(
                DSM_DATA_TCB_MANAGER(dataObj).table.hash,
                0,
                tid);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: HASH_DeleteEntry failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
        return ret;
    }

    /* Unlock Tcb table (write unlock). */
    ret = RWLOCK_UnlockExclusive(&DSM_DATA_TCB_MANAGER(dataObj).tableRwLock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: RWLOCK_UnlockExclusive failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    /* Free Tcb. */
    ret = FreeTcb(dataObj, tcb);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: FreeTcb failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return result;
}

/*
 * LockUnlockTableLocal.
 */
static int
LockUnlockTableLocal(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_BOOLEAN lockUnlockToggle)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    ITS_UINT        threadId;
    ITS_UINT        tid;
    DSM_Tcb*        tcb;
    DSM_Message     lockUnlockTableMsg;
    char            bufLockUnlockTable[sizeof(DSM_Message)];
    int             result = ITS_SUCCESS;
    int             ret;

    ITS_BOOLEAN tableIsLocked = ITS_FALSE;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);


    threadId = THREAD_GetCurrentThreadID();

   
do
{


    /* Lock state. */
    ret = MUTEX_AcquireMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));

        ITS_TRACE_CRITICAL((
            "LockUnlockTable [FtGroupId: %u]: unacceptable state from previous"
            " error: abort\n",
            DSM_DATA_FT_GROUP_ID(dataObj)));
        /* Must abort process. */
        CallCriticalErrorNotificationCallbacks(
            dataObj,
            __LINE__,
            "LockUnlockTable [FtGroupId: %u]: unable to recover from from "
            "error\n",
            DSM_DATA_FT_GROUP_ID(dataObj));

        /* Not reached. */
    }

    tableIsLocked =  TableIsLockedNotByMember(dataObj, DSM_DATA_LOCAL(dataObj).memberName, tableId) || TableIsLockedNotByThread(dataObj, threadId, tableId);

    if (tableIsLocked)
    {
        MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        TIMERS_USleep(200);
    }

} while (tableIsLocked); 


    /*
     * LockUnlockTable allowed in INITIAL state (special case: current process
     * lock/unlock only - to be synchronized later).
     */
    /*if (IsDsmStateInitial(DSM_DATA_STATE_DATA(dataObj).state))*/
    /*if (IsDsmStateNormal(DSM_DATA_STATE_DATA(dataObj).state))*/
    {
        ITS_BOOLEAN keepOn = ITS_TRUE;

        if (keepOn)
        {
            if (lockUnlockToggle)
            {
                ret = TableLock(
                        dataObj,
                        DSM_DATA_LOCAL(dataObj).memberName,
                        threadId,
                        tableId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockTable [FtGroupId: %u]: TableLock failed: "
                        "%d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
            else
            {
                ret = TableUnlock(
                        dataObj,
                        DSM_DATA_LOCAL(dataObj).memberName,
                        threadId,
                        tableId);
                if (ret != ITS_SUCCESS)
                {
                    ITS_TRACE_ERROR((
                        "LockUnlockTable [FtGroupId: %u]: TableUnlock failed: "
                        "%d\n",
                        DSM_DATA_FT_GROUP_ID(dataObj),
                        ret));
                    result = ret;
                    keepOn = ITS_FALSE;
                }
            }
        }

        /* Unlock state. */
        ret = MUTEX_ReleaseMutex(&DSM_DATA_STATE_DATA(dataObj).lock);
        if (ret != ITS_SUCCESS)
        {
            ITS_TRACE_ERROR((
                "LockUnlockTable [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
                "%d\n",
                DSM_DATA_FT_GROUP_ID(dataObj),
                ret));

            ITS_TRACE_CRITICAL((
                "LockUnlockTable [FtGroupId: %u]: unacceptable state from "
                "previous error: abort\n",
                DSM_DATA_FT_GROUP_ID(dataObj)));

            /* Must abort process. */
            CallCriticalErrorNotificationCallbacks(
                dataObj,
                __LINE__,
                "LockUnlockTable [FtGroupId: %u]: unable to recover from from "
                "error\n",
                DSM_DATA_FT_GROUP_ID(dataObj));

            /* Not reached. */
        }

    }

    return result;

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

int
DSM_LockTableLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId)
{
    return LockUnlockTableLocal(
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

int
DSM_UnlockTableLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId)
{
    return LockUnlockTableLocal(
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
#if 0
void*
DSM_AllocNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    ITS_UINT size,
    int* error)
{
    return AllocLocal(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error,
                ITS_FALSE);
}
#endif

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
#if 0
void*
DSM_FindNoLockLocalImpl(
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
#endif 


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
#if 0
int 
DSM_FreeNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return FreeLocal(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
}
#endif
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

int
DSM_CommitNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key,
    ITS_UINT klen,
    void* object)
{
    return CommitLocal(
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
#if 0
static int 
DSM_LockRowNoLockLocalImpl(
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
#endif

static int
DSM_LockRowNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    void* object)
{
    DSM_RowHeader* row;

    ITS_C_REQUIRE(object != NULL);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    row->locked = ITS_TRUE;
    row->lockTime = TIMERS_Time();

    return ITS_SUCCESS;
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

static int 
DSM_UnlockRowNoLockLocalImpl(
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
#if 0
void* 
DSM_AllocLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    return AllocLocal(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                size,
                error,
                ITS_FALSE);
}
#endif 


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
#if 0
void* 
DSM_FindLocalImpl(
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
#endif 

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
#if 0
int 
DSM_FreeLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return FreeLocal(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
}
#endif

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

int 
DSM_CommitLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    return CommitLocal(
                coreObj,
                ftGroupId,
                tableId,
                key,
                klen,
                object,
                ITS_FALSE);
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
DSM_TableIterateLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    void* in, 
    void* out,
    DSM_IterateEntryProc iterateEntryFn)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(iterateEntryFn != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_TRACE_ERROR((
        "DSM_TableIterateImpl [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
    
   ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = VTableIterate(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    in,
                    out,
                    iterateEntryFn);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: VTableIterate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        return ret;
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;

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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(iterateEntryFn != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_TRACE_DEBUG((
        "DSM_TableIterateImpl [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
    
   ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = VTableIterate(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId,
                    in,
                    out,
                    iterateEntryFn);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: VTableIterate failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        return ret;
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableIterateImpl [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

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
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(pStrDump != NULL);
    ITS_C_REQUIRE(dumpEntryFn != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_TRACE_DEBUG((
        "DSM_TableDumpImpl [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableDumpImpl [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = VTableDump(
                    DSM_DATA_MEM_DATA(dataObj)->tables,
                    tableId, 
                    pStrDump, 
                    dumpEntryFn);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableDumpImpl [FtGroupId: %u]: VTableDump failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        return ret;
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableDumpImpl [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    return ITS_SUCCESS;
}

static int 
DSM_TableGetSizeImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId, 
    ITS_UINT* size)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(size != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    ITS_TRACE_DEBUG((
        "DSM_TableGetSizeImpl [FtGroupId: %u]:\n",
        DSM_DATA_FT_GROUP_ID(dataObj)));
    
    ret = MUTEX_AcquireMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableGetSizeImpl [FtGroupId: %u]: MUTEX_AcquireMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

    ret = VTableGetSize(
                dataObj,
                tableId,
                size);
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableGetSizeImpl [FtGroupId: %u]: VTableGetSize failed: %d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
        return ret;
    }

    ret = MUTEX_ReleaseMutex(&DSM_DATA_TABLES_LOCK(dataObj));
    if (ret != ITS_SUCCESS)
    {
        ITS_TRACE_ERROR((
            "DSM_TableGetSizeImpl [FtGroupId: %u]: MUTEX_ReleaseMutex failed: "
            "%d\n",
            DSM_DATA_FT_GROUP_ID(dataObj),
            ret));
        return ret;
    }

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
DSM_MulticastStackEventToFtGroupMembersImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_EVENT event,
    ITS_USHORT source,
    ITS_USHORT destination)
{

    DSM_DataObject* dataObj;
    DSM_InstObject* instObj;

    DSM_Message_Multicast multicastMessage;

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);


    switch(destination)
    {

    case ITS_ISUP_CCITT_SRC:
    case ITS_ISUP_ANSI_SRC:
    case ITS_ISUP_PRC_SRC:
    case ITS_ISUP_TTC_SRC:
    case ITS_SCCP_CCITT_SRC:
    case ITS_SCCP_ANSI_SRC:
    case ITS_SCCP_PRC_SRC:
    case ITS_SCCP_TTC_SRC:
    case ITS_TCAP_CCITT_SRC:
    case ITS_TCAP_ANSI_SRC: 
    case ITS_TCAP_PRC_SRC: 
    case ITS_TCAP_TTC_SRC: 
    case ITS_MAB_SRC:
    case ITS_BSSAP_SRC:


        if ( (event.src  != ITS_MTP3_CCITT_SRC)              && 
             (event.src  != ITS_MTP3_ANSI_SRC)               &&
             (event.src  != ITS_MTP3_PRC_SRC)                &&
             (event.src  != ITS_MTP3_TTC_SRC)                &&
             ((event.src == ITS_ISUP_CCITT_SRC)        || 
             (event.src == ITS_ISUP_ANSI_SRC)          || 
             (event.src == ITS_ISUP_PRC_SRC)           || 
             (event.src == ITS_ISUP_TTC_SRC)           || 
             (event.src  == ITS_TIMER_SRC)             || 
             (event.src  == ITS_SCCP_LOCAL_REF_RESPONSE) ||
             (event.src  == ITS_GCS_EVENT_FROM_STACK)  || 
             (event.src  == ITS_GCS_EVENT_FROM_APPL)   ||
              event.src ==  ITS_GCS_EVENT_FROM_APPL_CL3I  ))

        {
            /* These events must not be multicasted, they must  
             * be processed immidiately by ISUP stack.      
             */     
            return ITS_ENOMSG;
        }



        ITS_C_REQUIRE(DSM_IsPreInitialized());
        ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

        multicastMessage.u.multicastEvent.ev.src = event.src;
        multicastMessage.u.multicastEvent.ev.len = event.len;
        multicastMessage.u.multicastEvent.ev.data = 0;

        ITS_C_REQUIRE
            (event.len < sizeof(multicastMessage.u.multicastEvent.data));

        memcpy(multicastMessage.u.multicastEvent.data, 
               event.data, event.len);

        multicastMessage.discriminator = DSM_MSG_MULTICAST_EVENT;
        multicastMessage.u.multicastEvent.dest = destination;
        multicastMessage.u.multicastEvent.source = source;
       //ITS_TRACE_CRITICAL(("$$$$ MULITICAST DESTINATION SEND: dest [%x] ", multicastMessage.u.multicastEvent.dest));
       
        /* now... multicast new stack message */
        GCS_Multicast(
            DSM_DATA_LOCAL(dataObj).Stubmailbox,
            GCS_SAFE_MSG,
            DSM_DATA_LOCAL(dataObj).groupName,
            multicastMessage.discriminator,
            sizeof(DSM_Message_Multicast),
            (const char*)&multicastMessage);

        return ITS_SUCCESS;

  
    
    default:

        if (event.data[0] == ITS_STATE_CHANGE_EVENT)
        {
            ITS_C_REQUIRE(DSM_IsPreInitialized());
            ITS_C_REQUIRE(DSM_IsInitialized(ftGroupId));

            multicastMessage.u.multicastEvent.ev.src = event.src;
            multicastMessage.u.multicastEvent.ev.len = event.len;
            multicastMessage.u.multicastEvent.ev.data = 0;

            ITS_C_REQUIRE
                (event.len < sizeof(multicastMessage.u.multicastEvent.data));

            memcpy(multicastMessage.u.multicastEvent.data, 
                   event.data, event.len);

            multicastMessage.discriminator = ITS_STATE_CHANGE_EVENT;
            multicastMessage.u.multicastEvent.dest = destination;
            multicastMessage.u.multicastEvent.source = source;
           
            /* now... multicast new stack message */
            GCS_Multicast(
                DSM_DATA_LOCAL(dataObj).Stubmailbox,
                GCS_SAFE_MSG,
                DSM_DATA_LOCAL(dataObj).groupName,
                multicastMessage.discriminator,
                sizeof(DSM_Message_Multicast),
                (const char*)&multicastMessage);
            ITS_TRACE_CRITICAL(("********MUlticasting state change even\n"));
            return ITS_SUCCESS;
        }
        else
        {
            ITS_TRACE_ERROR(("$$$$ Unsupported stack redundancy $$$$\n"));
        }

    }

    return ITS_ENOMSG;
}


static int
ImplClassInit(ITS_Class objClass)
{
    ITS_CLASS_SUPERCLASS(itsDSMHASH_Class) = itsHASH_Class;

    return ITS_SUCCESS;
}

#define DSM_GCS_IMPL_CLASS_NAME "DSM Implementation Class - GCS"

DSM_ImplClassRec itsDSM_GcsImplClassRec =
{
    /* core part */
    {
        NULL,                               /* no superclass in a DLL   */
        0,                                  /* sizeof(instance)         */
        ITS_FALSE,                          /* not initted              */
        0,                                  /* initial ref count        */
        DSM_GCS_IMPL_CLASS_NAME,            /* class name               */
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
        "GCS",
        DSM_ImplDataCreateInstanceImpl,
        DSM_ImplDataDestroyInstanceImpl,
        DSM_JoinFtGroupImpl,
        DSM_LeaveFtGroupImpl,
        DSM_SynchronizeDsmImpl,
        DSM_AllocImpl,
        DSM_AllocLocalImpl,
        DSM_FindImpl,
        DSM_FindLocalImpl,
        DSM_FreeImpl,
        DSM_FreeLocalImpl,
        DSM_CommitImpl,
        DSM_CommitLocalImpl,
        DSM_LockRowImpl,
        DSM_LockRowImpl,
        DSM_UnlockRowImpl,
        DSM_UnlockRowImpl,
        DSM_LockDsmImpl,
        DSM_UnlockDsmImpl,
        DSM_LockTableImpl,
        DSM_LockTableLocalImpl,
        DSM_UnlockTableImpl,
        DSM_UnlockTableLocalImpl,
        DSM_AllocNoLockImpl,
        DSM_AllocNoLockLocalImpl,
        DSM_FindNoLockImpl,
        DSM_FindNoLockLocalImpl,
        DSM_FreeNoLockImpl,
        DSM_FreeNoLockLocalImpl,
        DSM_CommitNoLockImpl,
        DSM_CommitNoLockLocalImpl,
        DSM_LockRowNoLockImpl,
        DSM_LockRowNoLockLocalImpl,
        DSM_UnlockRowNoLockImpl,
        DSM_UnlockRowNoLockLocalImpl,
        DSM_TableIterateImpl,
        DSM_TableDumpImpl,
        DSM_TableGetSizeImpl,
        DSM_MulticastEventToFtGroupMembersImpl,
        DSM_MulticastStackEventToFtGroupMembersImpl,
        DSM_TableIterateLocalImpl
    }
};

DSMDLLAPI ITS_Class itsDSM_GcsImplClass = (ITS_Class)&itsDSM_GcsImplClassRec;


/******************************************************************************
 ******************************************************************************
 **
 ** DSM (GCS) Engine Parser Extension related.
 **
 */



#define DSM_GCS_CONFIG_STRING               "DsmGcsConfig"

#define GCS_FT_GROUP_ID_STRING              "gcsFtGroupId"
#define GCS_DAEMON_NAME_STRING              "gcsDaemonName"
#define GCS_STUBDAEMON_NAME_STRING           "gcsStubDaemonName"
#define GCS_CONNECT_TIMEOUT_STRING          "gcsConnectTimeout"
#define GCS_GROUP_NAME_STRING               "gcsGroupName"
#define GCS_CONNECTION_NAME_ROOT_STRING     "gcsConnectionNameRoot"
#define GCS_RECEIVER_ALIVE_TIMEOUT_STRING   "gcsReceiverAliveTimeout"
#define GCS_SYNC_MEM_USE_TCP_STRING         "gcsSyncMemUseTcp"
#define GCS_SYNC_MEM_USE_GCS_STRING         "gcsSyncMemUseGcs"
#define GCS_SYNC_MEM_TIMEOUT_STRING         "gcsSyncMemTimeout"
#define GCS_SYNC_MEM_CONNECT_TIMEOUT_STRING "gcsSyncMemConnectTimeout"
#define GCS_SELF_JOIN_TIMEOUT_STRING        "gcsSelfJoinTimeout"
#define GCS_MASTER_JOIN_TIMEOUT_STRING      "gcsMasterJoinTimeout"
#define GCS_SYNC_MEM_IP_ADDRESS_STRING      "gcsSyncMemIpAddress"
#define GCS_SYNC_MEM_IP_PORT_STRING         "gcsSyncMemIpPort"


#define DSM_GCS_CONFIG_DATA_PTR(x) ((DSM_GCS_Config *)ENGINE_PE_USER_DATA(x))

typedef struct _DSM_GCS_Config
{
    char* ftGroupId;
    char* daemonName;
    char* connectTimeout;
    char* groupName;
    char* connectionNameRoot;
    char* receiverAliveTimeout;
    char* syncMemUseTcp;
    char* syncMemUseGcs;
    char* syncMemTimeout;
    char* syncMemConnectTimeout;
    char* selfJoinTimeout;
    char* masterJoinTimeout;
    char* syncMemIpAddress;
    char* syncMemIpPort;
    struct _DSM_GCS_Config *next; 
} DSM_GCS_Config;

DSMDLLAPI void
DSM_GCS_ConfigParseStart(
    ENGINE_ParserExtension ext, 
    const char* elem, 
    const char** attr)
{
    DSM_GCS_Config *gcs_tmp, *gcs_ptr;

    gcs_tmp = ENGINE_PE_USER_DATA(ext);

    if (strcmp(elem, DSM_GCS_CONFIG_STRING) == 0)
    {
        if(gcs_tmp == NULL)
        {
            ENGINE_PE_USER_DATA(ext) = calloc(1, sizeof(DSM_GCS_Config));
        }
        else
        {
            gcs_ptr = (DSM_GCS_Config *)calloc(1, sizeof(DSM_GCS_Config));

            ENGINE_PE_USER_DATA(ext) = gcs_ptr;

            gcs_ptr->next = gcs_tmp;
        }
 
        ITS_C_ASSERT(ENGINE_PE_USER_DATA(ext) != NULL);

        while (*attr)
        {
            if (strcmp(*attr, GCS_FT_GROUP_ID_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    ftGroupId = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        ftGroupId !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_DAEMON_NAME_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    daemonName = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        daemonName !=
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_CONNECT_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    connectTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        connectTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_GROUP_NAME_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    groupName = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        groupName != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_CONNECTION_NAME_ROOT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    connectionNameRoot = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        connectionNameRoot != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_RECEIVER_ALIVE_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    receiverAliveTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        receiverAliveTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_USE_TCP_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemUseTcp = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemUseTcp != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_USE_GCS_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemUseGcs = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemUseGcs != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_CONNECT_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemConnectTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemConnectTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SELF_JOIN_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    selfJoinTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        selfJoinTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_MASTER_JOIN_TIMEOUT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    masterJoinTimeout = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        masterJoinTimeout != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_IP_ADDRESS_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemIpAddress = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemIpAddress != 
                            NULL);

                attr++;
            }
            else if (strcmp(*attr, GCS_SYNC_MEM_IP_PORT_STRING) == 0)
            {
                attr++;

                DSM_GCS_CONFIG_DATA_PTR(ext)->
                    syncMemIpPort = 
                        strdup(*attr);

                ITS_C_ASSERT(
                    DSM_GCS_CONFIG_DATA_PTR(ext)->
                        syncMemIpPort != 
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
DSM_GCS_ConfigParseStop(
    ENGINE_ParserExtension ext, 
    const char* elem) 
{
    ITS_C_ASSERT(ext != NULL);

    if (strcmp(elem, DSM_GCS_CONFIG_STRING) == 0)
    {
        /* Nothing to do. */
    }
    else
    {
        /* Ignore. */
    }
}

DSMDLLAPI void
DSM_GCS_ConfigConvertParserData(
    RESFILE_Manager* appRes,
    ENGINE_ParserExtension ext)
{
    DSM_GCS_Config* gcsConfig = (DSM_GCS_Config*)ENGINE_PE_USER_DATA(ext);
    DSM_GCS_Config* gcs_tmp;
    char ftGroupName[64];
    int ret;

    while (gcsConfig != NULL)
    {
        sprintf(
            ftGroupName, 
            "%s%s", 
            DSM_FT_GROUP_STRING, 
            gcsConfig->ftGroupId);

        /* Ignore errors (section should already exist). */
        RESFILE_AddSection(
            appRes,
            ftGroupName);

        if (gcsConfig->daemonName && 
            strlen(gcsConfig->daemonName) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_DAEMON_NAME_STRING,
                    gcsConfig->daemonName);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->connectTimeout && 
            strlen(gcsConfig->connectTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_CONNECT_TIMEOUT_STRING,
                    gcsConfig->connectTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }
        
        if (gcsConfig->groupName && 
            strlen(gcsConfig->groupName) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_GROUP_NAME_STRING,
                    gcsConfig->groupName);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->connectionNameRoot && 
            strlen(gcsConfig->connectionNameRoot) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_CONNECTION_NAME_ROOT_STRING,
                    gcsConfig->connectionNameRoot);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->connectionNameRoot && 
            strlen(gcsConfig->connectionNameRoot) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_CONNECTION_NAME_ROOT_STRING,
                    gcsConfig->connectionNameRoot);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->receiverAliveTimeout && 
            strlen(gcsConfig->receiverAliveTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_RECEIVER_ALIVE_TIMEOUT_STRING,
                    gcsConfig->receiverAliveTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemUseTcp && 
            strlen(gcsConfig->syncMemUseTcp) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_USE_TCP_STRING,
                    gcsConfig->syncMemUseTcp);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemUseGcs && 
            strlen(gcsConfig->syncMemUseGcs) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_USE_GCS_STRING,
                    gcsConfig->syncMemUseGcs);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemTimeout && 
            strlen(gcsConfig->syncMemTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_TIMEOUT_STRING,
                    gcsConfig->syncMemTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemConnectTimeout && 
            strlen(gcsConfig->syncMemConnectTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_CONNECT_TIMEOUT_STRING,
                    gcsConfig->syncMemConnectTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->selfJoinTimeout && 
            strlen(gcsConfig->selfJoinTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SELF_JOIN_TIMEOUT_STRING,
                    gcsConfig->selfJoinTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->masterJoinTimeout && 
            strlen(gcsConfig->masterJoinTimeout) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_MASTER_JOIN_TIMEOUT_STRING,
                    gcsConfig->masterJoinTimeout);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemIpAddress && 
            strlen(gcsConfig->syncMemIpAddress) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_IP_ADDRESS_STRING,
                    gcsConfig->syncMemIpAddress);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        if (gcsConfig->syncMemIpPort && 
            strlen(gcsConfig->syncMemIpPort) != 0)
        {
            ret = RESFILE_AddKeyValue(
                    appRes,
                    ftGroupName,
                    DSM_GCS_SYNC_MEM_IP_PORT_STRING,
                    gcsConfig->syncMemIpPort);
            ITS_C_ASSERT(ret == ITS_SUCCESS);
        }

        /* 
         * Free gcsConfig data members (not used afterward). 
         */

        if (gcsConfig->daemonName)
        {
            free(gcsConfig->daemonName);
            gcsConfig->daemonName = NULL;
        }

        if (gcsConfig->connectTimeout)
        {   
            free(gcsConfig->connectTimeout);
            gcsConfig->connectTimeout = NULL;
        }
        
        if (gcsConfig->groupName)
        {
            free(gcsConfig->groupName);
            gcsConfig->groupName = NULL;
        }

        if (gcsConfig->connectionNameRoot)
        {
            free(gcsConfig->connectionNameRoot);
            gcsConfig->connectionNameRoot = NULL;
        }

        if (gcsConfig->connectionNameRoot)
        {
            free(gcsConfig->connectionNameRoot);
            gcsConfig->connectionNameRoot = NULL;
        }

        if (gcsConfig->receiverAliveTimeout)
        {
            free(gcsConfig->receiverAliveTimeout);
            gcsConfig->receiverAliveTimeout = NULL;
        }

        if (gcsConfig->syncMemUseTcp)
        {
            free(gcsConfig->syncMemUseTcp);
            gcsConfig->syncMemUseTcp = NULL;
        }

        if (gcsConfig->syncMemUseGcs)
        {
            free(gcsConfig->syncMemUseGcs);
            gcsConfig->syncMemUseGcs = NULL;
        }

        if (gcsConfig->syncMemTimeout)
        {
            free(gcsConfig->syncMemTimeout);
            gcsConfig->syncMemTimeout = NULL;
        }

        if (gcsConfig->syncMemConnectTimeout)
        {
            free(gcsConfig->syncMemConnectTimeout);
            gcsConfig->syncMemConnectTimeout = NULL;
        }

        if (gcsConfig->selfJoinTimeout)
        {
            free(gcsConfig->selfJoinTimeout);
            gcsConfig->selfJoinTimeout = NULL;
        }

        if (gcsConfig->masterJoinTimeout)
        {
            free(gcsConfig->masterJoinTimeout);
            gcsConfig->masterJoinTimeout = NULL;
        }

        if (gcsConfig->syncMemIpAddress)
        {
            free(gcsConfig->syncMemIpAddress);
            gcsConfig->syncMemIpAddress = NULL;
        }

        if (gcsConfig->syncMemIpPort)
        {
            free(gcsConfig->syncMemIpPort);
            gcsConfig->syncMemIpPort = NULL;
        }

        gcs_tmp   = gcsConfig;
        gcsConfig = gcsConfig->next;
        free(gcs_tmp);
    }
}

DSMDLLAPI void
DSM_GCS_ConfigDiff(
    RESFILE_Manager* appRes,
    ENGINE_ParserExtension ext1,
    ENGINE_ParserExtension ext2)
{
    /* Nothing to do. */
}





void* 
DSM_AllocNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* allocPtr;
    DSM_RowHeader* tmp;
    DSM_RowHeader** list;
    ITS_INT hash;
    ITS_UINT round;
    ITS_UINT rowSize = size;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Add row header to rowSize and make it a multiple of word size. */
    rowSize += sizeof(DSM_RowHeader) + sizeof(ITS_UINT) - 1;
    rowSize &= ~(sizeof(ITS_UINT) - 1);

    /* Allocate entry. */
    allocPtr = calloc(1, rowSize);
    if (allocPtr == NULL)
    {
        *error = ITS_ENOMEM;
        return NULL;
    }

    /* Allocate key. */
    round = klen + sizeof(ITS_UINT) - 1;
    round &= ~(sizeof(ITS_UINT) - 1);

    allocPtr->key = calloc(1, round);
    if (allocPtr->key == NULL)
    {
        free(allocPtr);
        *error = ITS_ENOMEM;
        return NULL;
    }

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Add to hash table. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
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
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash,
                    (ITS_POINTER)allocPtr);
        if (ret != ITS_SUCCESS)
        {
            free(allocPtr->key);
            free(allocPtr);
            *error = ret;
            return NULL;
        }
    }

    /* Store key info. */
    memcpy(allocPtr->key, key, klen);
    allocPtr->klen = klen;

    /* Adjust number of entries in table. */
    DSM_DATA_TABLES_INFO(dataObj)[tableId].entries++;

    /* Adjust pointer to user data (row header is before). */
    allocPtr = allocPtr + 1;

    return allocPtr;
}



int 
DSM_FreeNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,           
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* row;
    DSM_RowHeader* tmp;
    DSM_RowHeader* head;
    DSM_RowHeader** list;
    ITS_INT hash;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(object != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader*)((char*)object - sizeof(DSM_RowHeader));

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Lookup for row list in table according to hash value. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash,
                (ITS_POINTER*)&head);
    if (ret != ITS_SUCCESS)
    {
        return ITS_ENOTFOUND;
    }

    /* Scan row list for correct row. */
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
        return ITS_EINVALIDARGS;
    }

    /* Remove from list. */
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

    /* Update hash accordingly. */
    if (head == NULL)
    {
        ret = HASH_DeleteEntry(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash);

        if (ret != ITS_SUCCESS)
        {
            free(row->key);
            free(row);
            return ret;
        }
    }
    else
    {
        ret = HASH_AddEntry(
                    DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                    tableId,
                    hash, 
                    (ITS_POINTER)head);

        if (ret != ITS_SUCCESS)
        {
            free(row->key);
            free(row);
            return ret;
        }
    }
            
    free(row->key);
    free(row);

    /* Adjust number of entries in table. */
    if (DSM_DATA_TABLES_INFO(dataObj)[tableId].entries > 0)
    {
        DSM_DATA_TABLES_INFO(dataObj)[tableId].entries--;
    }    

    return ITS_SUCCESS;
}

int 
DSM_FreeLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    void* object)
{
    DSM_RowHeader* row;
    int ret;

    ITS_C_REQUIRE(object != NULL);

    ret = DSM_LockTableLocalImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    /* Deduce actual row pointer from object pointer. */
    row = (DSM_RowHeader *)((char *)object - sizeof(DSM_RowHeader));

    ITS_C_ASSERT(row->locked);

    if (!row->locked)
    {
        DSM_UnlockTableLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId);

        return ITS_EROWNOTLOCKED;
    }

    ret = DSM_FreeNoLockLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId,
                    key,
                    klen,
                    object);
    if (ret != ITS_SUCCESS)
    {
        DSM_UnlockTableLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
        
        return ret;
    }
    
    ret = DSM_UnlockTableLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        return ret;
    }

    return ITS_SUCCESS;
}



void* 
DSM_AllocLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    ITS_UINT size, 
    int* error)
{
    void* allocPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableLocalImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;
        return NULL;
    }

    allocPtr = DSM_AllocNoLockLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen, 
                    size, 
                    error);
    if (allocPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockLocalImpl(
                    coreObj,
                    ftGroupId,
                    allocPtr);
    }

    ret = DSM_UnlockTableLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return allocPtr;
}

static int
MemCmp(void *k1, ITS_UINT k1Len, void *k2, ITS_UINT k2Len)
{
    return memcmp(k1, k2, k1Len > k2Len ? k1Len : k2Len);
}
static int
TablesCreate(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i, j;

    DSM_DATA_TABLES(dataObj) =
        calloc(DSM_INST_MAX_NUM_TABLES(instObj), sizeof(DSM_Table));
    if (DSM_DATA_TABLES(dataObj) == NULL)
    {
        /* TODO: add trace. */
        return ITS_ENOMEM;
    }

    /* FIXME: Right now, the calloc() forces all the table types to DSM_TABLE_HASH */

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            DSM_DATA_TABLES(dataObj)[i].table.hash = HASH_CreateTable();
            if (DSM_DATA_TABLES(dataObj)[i].table.hash == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        case DSM_TABLE_REDBLACK:
            DSM_DATA_TABLES(dataObj)[i].table.tree = RB_InitTree(MemCmp, ITS_TRUE);
            if (DSM_DATA_TABLES(dataObj)[i].table.tree == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        case DSM_TABLE_SPLAY:
            DSM_DATA_TABLES(dataObj)[i].table.splay = SPLAY_InitSplay(MemCmp, ITS_TRUE);
            if (DSM_DATA_TABLES(dataObj)[i].table.splay == NULL)
            {
                /* TODO: add trace. */

                for (j = 0; j < i; j++)
                {
                    switch (DSM_DATA_TABLES(dataObj)[i].type)
                    {
                    case DSM_TABLE_HASH:
                        HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                        DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                        break;
                    case DSM_TABLE_REDBLACK:
                        RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                        DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                        break;

                    case DSM_TABLE_SPLAY:
                        SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                        DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                        break;

                    default:
                        break;
                    }
                }

                return ITS_ENOMEM;
            }
            break;

        default:
            /* FIXME: Trace */

            for (j = 0; j < i; j++)
            {
                switch (DSM_DATA_TABLES(dataObj)[i].type)
                {
                case DSM_TABLE_HASH:
                    HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[j].table.hash);
                    DSM_DATA_TABLES(dataObj)[j].table.hash = NULL;
                    break;
                case DSM_TABLE_REDBLACK:
                    RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
                    DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
                    break;

                case DSM_TABLE_SPLAY:
                    SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
                    DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
                    break;

                default:
                    break;
                }
            }

            return ITS_ENOMEM;
        }
    }

    return ITS_SUCCESS;
}

static int
TablesDestroy(
    DSM_CoreObject* coreObj,
    DSM_InstObject* instObj,
    DSM_DataObject* dataObj)
{
    ITS_UINT i;

    for (i = 0; i < DSM_INST_MAX_NUM_TABLES(instObj); i++)
    {
        switch (DSM_DATA_TABLES(dataObj)[i].type)
        {
        case DSM_TABLE_HASH:
            HASH_DeleteTable(DSM_DATA_TABLES(dataObj)[i].table.hash);
            DSM_DATA_TABLES(dataObj)[i].table.hash = NULL;
            break;

        case DSM_TABLE_REDBLACK:
            RB_FreeTree(DSM_DATA_TABLES(dataObj)[i].table.tree);
            DSM_DATA_TABLES(dataObj)[i].table.tree = NULL;
            break;

        case DSM_TABLE_SPLAY:
            SPLAY_FreeSplay(DSM_DATA_TABLES(dataObj)[i].table.splay);
            DSM_DATA_TABLES(dataObj)[i].table.splay = NULL;
            break;

        default:
            break;
        }
    }

    return ITS_SUCCESS;
}

void*
DSM_FindNoLockLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    DSM_InstObject* instObj;
    DSM_DataObject* dataObj;
    DSM_RowHeader* findPtr;
    DSM_RowHeader* row;
    ITS_INT hash;
    int ret;

    ITS_C_REQUIRE(coreObj != NULL);
    ITS_C_REQUIRE(key != NULL);
    ITS_C_REQUIRE(klen != 0);
    ITS_C_REQUIRE(error != NULL);

    instObj = DSM_CORE_FT_GROUPS(coreObj)[ftGroupId];
    dataObj = (DSM_DataObject*)DSM_INST_IMPL_DATA(instObj);

    *error = ITS_SUCCESS;

    /* Compute hash value. */
    hash = HASH_MakeKey((char *)key, klen);

    /* Lookup for row list in table according to hash value. */
    ret = HASH_FindEntry(
                DSM_DATA_TABLES(dataObj)[tableId].table.hash,
                tableId,
                hash,
                (ITS_POINTER*)&row);
    if (ret != ITS_SUCCESS)
    {
        *error = ITS_ENOTFOUND;
        return NULL;
    }

    /* Scan row list for correct row. */
    while (row != NULL)
    {
        if (row->klen == klen && memcmp(row->key, key, klen) == 0)
        {
            break;
        }

        row = row->next;
    }

    /* Make sure it was found. */
    if (row == NULL)
    {
        *error = ITS_ENOTFOUND;
        return NULL;
    }

    /* Adjust pointer to user data (row header is before). */
    findPtr = row;
    findPtr = findPtr + 1;

    return findPtr;
}

void* 
DSM_FindLocalImpl(
    DSM_CoreObject* coreObj,
    ITS_USHORT ftGroupId,
    ITS_UINT tableId,
    ITS_OCTET* key, 
    ITS_UINT klen,
    int* error)
{
    void* findPtr;
    int ret;

    *error = ITS_SUCCESS;

    ret = DSM_LockTableLocalImpl(
                    coreObj, 
                    ftGroupId, 
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        *error = ret;
        return NULL;
    }

    findPtr = DSM_FindNoLockLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId, 
                    key, 
                    klen,  
                    error);
    if (findPtr != NULL && *error == ITS_SUCCESS)
    {
        *error = DSM_LockRowNoLockLocalImpl(
                    coreObj,
                    ftGroupId,
                    findPtr);
    }

    ret = DSM_UnlockTableLocalImpl(
                    coreObj,
                    ftGroupId,
                    tableId);
    if (ret != ITS_SUCCESS)
    {
        /* Precedence to report errors from most important functions. */
        if (*error == ITS_SUCCESS)
        {
            *error = ret;
        }
    }

    return findPtr;
}


