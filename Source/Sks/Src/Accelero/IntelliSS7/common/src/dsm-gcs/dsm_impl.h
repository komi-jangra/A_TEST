/*****************************************************************************
 *                                                                           *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *             Manufactured in the United States of America.                 *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                           *
 *   This product and related documentation is protected by copyright and    *
 *   distributed under licenses restricting its use, copying, distribution   *
 *   and decompilation.  No part of this product or related documentation    *
 *   may be reproduced in any form by any means without prior written        *
 *   authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                           *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *   government is subject to restrictions as set forth in subparagraph      *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                           *
 *****************************************************************************
 *                                                                           *
 * CONTRACT: INTERNAL                                                        *
 *                                                                           *
 *****************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:23  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:09  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:37  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/01/05 09:25:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:19  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.17  2001/12/19 16:13:45  hdivoux
 * LOG: Removed former macro.
 * LOG:
 * LOG: Revision 5.16  2001/12/17 20:21:08  hdivoux
 * LOG: Update (major) for improved design.
 * LOG:
 * LOG: Revision 5.15  2001/09/28 20:41:14  hdivoux
 * LOG: Update to remove deadlock.
 * LOG:
 * LOG: Revision 5.14  2001/09/27 16:51:11  hdivoux
 * LOG: First version with no lock DSM functions.
 * LOG:
 * LOG: Revision 5.13  2001/09/26 22:57:13  hdivoux
 * LOG: More no lock DSM functions (almost there).
 * LOG:
 * LOG: Revision 5.12  2001/09/25 23:02:49  hdivoux
 * LOG: More no lock DSM functions.
 * LOG:
 * LOG: Revision 5.11  2001/09/24 21:56:45  hdivoux
 * LOG: More no lock DSM functions.
 * LOG:
 * LOG: Revision 5.10  2001/09/21 22:38:55  hdivoux
 * LOG: Start updating for no lock DSM functions.
 * LOG:
 * LOG: Revision 5.9  2001/08/31 15:31:59  hdivoux
 * LOG: Separated state JOINING in JOINING FIRST and JOINING NEXT.
 * LOG:
 * LOG: Revision 5.8  2001/08/31 14:24:03  hdivoux
 * LOG: More state related processing changes.
 * LOG:
 * LOG: Revision 5.7  2001/08/30 21:21:33  hdivoux
 * LOG: Update to start using SYNC SLAVE WAIT state.
 * LOG:
 * LOG: Revision 5.6  2001/08/29 20:28:20  hdivoux
 * LOG: Corrections.
 * LOG:
 * LOG: Revision 5.5  2001/08/27 20:13:00  hdivoux
 * LOG: More sync mem using TCP (almost there).
 * LOG:
 * LOG: Revision 5.4  2001/08/27 16:46:05  hdivoux
 * LOG: More sync mem using TCP.
 * LOG:
 * LOG: Revision 5.3  2001/08/24 22:50:09  hdivoux
 * LOG: More sync mem using TCP.
 * LOG:
 * LOG: Revision 5.2  2001/08/23 23:05:17  hdivoux
 * LOG: Update for dsm-gcs improvements (initialization and begin of TCP rcp).
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:05  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 1.12  2001/08/14 14:52:23  hdivoux
 * LOG: Added SELF-JOIN semaphore.
 * LOG:
 * LOG: Revision 1.11  2001/07/16 18:47:48  hdivoux
 * LOG: Mutex cannot reside in replicated memory. Moved out tables lock.
 * LOG:
 * LOG: Revision 1.10  2001/07/16 17:15:51  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.9  2001/07/16 15:10:37  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.8  2001/07/13 22:22:33  hdivoux
 * LOG: Work in progress (finished all procedures and DSM_* public functions).
 * LOG:
 * LOG: Revision 1.7  2001/07/12 23:00:08  hdivoux
 * LOG: Work in progress (more procedures and DSM public functions).
 * LOG:
 * LOG: Revision 1.6  2001/07/11 20:34:34  hdivoux
 * LOG: Build on Solaris.
 * LOG:
 * LOG: Revision 1.5  2001/07/10 22:21:38  hdivoux
 * LOG: Work in progress (added allocator).
 * LOG:
 * LOG: Revision 1.4  2001/07/09 21:56:31  hdivoux
 * LOG: Work in progress (more DSM_ public functions).
 * LOG:
 * LOG: Revision 1.3  2001/07/06 22:45:29  hdivoux
 * LOG: Work in progress (more procedures).
 * LOG:
 * LOG: Revision 1.2  2001/07/05 23:48:05  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1  2001/07/05 14:35:59  hdivoux
 * LOG: Move dsm-gcs to common/src.
 * LOG:
 * LOG: Revision 1.5  2001/07/03 23:11:39  hdivoux
 * LOG: Work in progress (more procedures).
 * LOG:
 * LOG: Revision 1.4  2001/07/02 21:54:26  hdivoux
 * LOG: Work in progress (start adding procedures).
 * LOG:
 * LOG: Revision 1.3  2001/06/29 22:38:40  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.2  2001/06/28 23:07:26  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1  2001/06/27 21:56:19  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_DSM_IMPL_H_)
#define _DSM_IMPL_H_

#include <its.h>
#include <its_hash.h>
#include <its_list.h>
#include <its_condvar.h>
#include <its_rwlock.h>
#include <its_thread.h>
#include <its_semaphore.h>

#include <gcs_client.h>


#ident "$Id: dsm_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"



/******************************************************************************
 ******************************************************************************
 *
 * Allocator related.
 *
 */

/* TODO: do we need all the following (like SCI?). */

/*
 * We need a definition of the allocator for the DSM struct.
 * This is basically a modified version of Doug Lea's allocator.
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
 *
 * DSM related.
 *
 */


/*
 * DSM maximun number of nodes. MUST BE greater than or equal to 1.
 */

#define DSM_MAX_NODES                       (2)

#define DSM_MAX_REMOTE_NODES                (DSM_MAX_NODES - 1)


/*
 * DSM maximum message size (128K + 8K). MUST BE less than GCS maximum message
 * size (i.e. 144000).
 */

#define DSM_MAX_MSG_SIZE                    (1392640)


/*
 * DSM maximum object size (128K). MUST BE less than DSM maximum message size
 * minus 8K (4K for key and 4K extra for sizeof(DSM_Message)).
 */

#define DSM_MAX_OBJECT_SIZE                 (1310720)


/*
 * DSM maximum key length.
 */

#define DSM_MAX_KEY_LENGTH                  (4096)


/*
 * DSM maximum SYNC MEM data size (1K).
 */ 

#define DSM_MAX_SYNC_MEM_DATA_SIZE          (1024)


/*
 * DSM maximum daemon name size.
 */

#define DSM_MAX_DAEMON_NAME_SIZE            (GCS_MAX_GROUP_NAME)


/*
 * DSM maximum group name size.
 */

#define DSM_MAX_GROUP_NAME_SIZE             (GCS_MAX_GROUP_NAME)


/*
 * DSM maximum connection name size.
 */

#define DSM_MAX_CONNECTION_NAME_ROOT_SIZE   (4)


/*
 * DSM maximum IP address size.
 */

#define DSM_MAX_IP_ADDRESS_SIZE             (32)


/*
 * DSM conversions.
 */

#define DSM_MSEC_PER_SEC                    (1000)
#define DSM_USEC_PER_MSEC                   (1000)


/*
 * Distributed Locks (area and tables).
 */
typedef struct
{
    ITS_UINT    counter;
    ITS_UINT    threadId;
    char        memberName[GCS_MAX_GROUP_NAME];
}
DSM_DistributedLock;

/*
 * Area info (distributed lock...).
 */ 

typedef struct
{
    DSM_DistributedLock lock;
}
DSM_AreaInfo;

/*
 * Table info (distributed locks, count of entries...).
 */

typedef struct
{
    DSM_DistributedLock lock;
    ITS_UINT            entries;
}
DSM_TableInfo;

typedef DSM_TableInfo* DSM_TablesInfo;

/*
 * Pending procedures related (used to delay execution of procedures when sync
 * or lock).
 */

enum
{
    DSM_PROCEDURE_ALLOCATE_ROW              = 1,
    DSM_PROCEDURE_FIND_ROW                  = 2,
    DSM_PROCEDURE_FREE_ROW                  = 3,
    DSM_PROCEDURE_COMMIT_ROW                = 4,
    DSM_PROCEDURE_LOCK_UNLOCK_ROW           = 5,
    DSM_PROCEDURE_LOCK_UNLOCK_TABLE         = 6,
    DSM_PROCEDURE_LOCK_UNLOCK_AREA          = 7,
    DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK   = 8,
};

typedef struct _st_DSM_Procedure
{
    /* Discriminator. */
    ITS_UINT                    type;

    /* Procedure arguments. */
    GCS_SERVICE                 service;
    char                        sender[GCS_MAX_GROUP_NAME];
    ITS_INT                     numGroups;
    char                        groups[DSM_MAX_NODES][GCS_MAX_GROUP_NAME];
    ITS_UINT                    size;

    /* Tid (always relevant). */
    ITS_UINT                    tid;

    /* Table identifier ((ITS_UINT)(-1) if irrelevant). */
    ITS_UINT                    tableId;

    /* Origin DSM-user thread identifier ((ITS_UINT)(-1) if irrelevant). */
    ITS_UINT                    originThreadId;

    /* Origin DSM-user member name (always relevant). */
    char                        originMemberName[GCS_MAX_GROUP_NAME];

    /* Linked list. */
    struct _st_DSM_Procedure*   prev;
    struct _st_DSM_Procedure*   next;

    /* Message itself (must be last). */
    char                        msg[1];
}
DSM_Procedure;

typedef struct
{
    DSM_Procedure*  listHead;
    DSM_Procedure*  listTail;
    size_t          count;
}
DSM_ProcedureManager;


/*
 * DSM shared (through GCS) memory data. Unique instance of this structure is
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
    HASH_Table                  tables;
    DSM_AreaInfo                areaInfo;
    DSM_TablesInfo              tablesInfo;
    DSM_ProcedureManager        procedureManager;
}
DSM_MemData;


/*
 * DSM state related (GCS).
 */

enum
{
    DSM_STATE_INITIAL           = 1,
    DSM_STATE_JOINING_FIRST     = 2,
    DSM_STATE_JOINING_NEXT      = 3,
    DSM_STATE_NORMAL            = 4,
    DSM_STATE_SYNC_SLAVE        = 5,
    DSM_STATE_SYNC_SLAVE_WAIT   = 6,
    DSM_STATE_SYNC_MASTER       = 7,
    DSM_STATE_SYNC_NEUTRAL      = 8,
    DSM_STATE_TERMINAL          = 9
};

#define IsDsmStateInitial(state)        ((state) == DSM_STATE_INITIAL)
#define IsDsmStateJoiningFirst(state)   ((state) == DSM_STATE_JOINING_FIRST)
#define IsDsmStateJoiningNext(state)    ((state) == DSM_STATE_JOINING_NEXT)
#define IsDsmStateNormal(state)         ((state) == DSM_STATE_NORMAL)
#define IsDsmStateSyncSlave(state)      ((state) == DSM_STATE_SYNC_SLAVE)
#define IsDsmStateSyncSlaveWait(state)  ((state) == DSM_STATE_SYNC_SLAVE_WAIT)
#define IsDsmStateSyncMaster(state)     ((state) == DSM_STATE_SYNC_MASTER)
#define IsDsmStateSyncNeutral(state)    ((state) == DSM_STATE_SYNC_NEUTRAL)
#define IsDsmStateTerminal(state)       ((state) == DSM_STATE_TERMINAL)

#define IsDsmStateJoining(state)                    \
            ((state) == DSM_STATE_JOINING_FIRST ||  \
             (state) == DSM_STATE_JOINING_NEXT)

#define IsDsmStateSync(state)                       \
            ((state) == DSM_STATE_SYNC_SLAVE    ||  \
             (state) == DSM_STATE_SYNC_MASTER   ||  \
             (state) == DSM_STATE_SYNC_NEUTRAL)

#define IsDsmStateSyncMasterNeutral(state)          \
            ((state) == DSM_STATE_SYNC_MASTER   ||  \
             (state) == DSM_STATE_SYNC_NEUTRAL)

typedef struct
{
    ITS_MUTEX           lock;
    ITS_UINT            state;
}
DSM_StateData;


/*
 * DSM state related (RM). Two nodes limitation.
 */

typedef struct
{
    ITS_UINT            myState;
    ITS_UINT            hisState;
}
DSM_RmStateData;


/*
 * DSM join related.
 */

typedef struct
{
    ITS_UINT            selfTimeout;
    ITS_SEMAPHORE       selfSema;
    ITS_SEMAPHORE       sema;
}
DSM_JoinData;


/*
 * DSM synchronization related (slave to synchronize with master).
 */ 

typedef struct
{
    ITS_RWLOCK              rwLock;
    ITS_SEMAPHORE           sema;
    char                    syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char                    syncMasterMemberName[GCS_MAX_GROUP_NAME];
    LIST_Manager*           procedureQueue;
    ITS_UINT                lastSeq;
    ITS_BOOLEAN             syncMemUseTcp;
    ITS_BOOLEAN             syncMemUseGcs;
    char                    syncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT              syncMemIpPort;
    ITS_ULONG               syncMemTimeout;
    ITS_ULONG               syncMemConnectTimeout;
    ITS_SocketInfo*         sockListen;
    ITS_SocketInfo*         sockServer;
    ITS_SocketInfo*         sockClient;
    ITS_THREAD              thread;
    ITS_BOOLEAN             exitThread;
}
DSM_SyncData;


typedef struct
{
    ITS_THREAD          thread;
    GCS_TIME            aliveTimeout;
}
DSM_Procedures;


typedef struct
{
    GCS_MAILBOX         mailbox;
    GCS_TIME            connectTimeout;
    char                gcsDaemonName[GCS_MAX_GROUP_NAME];
    char                connectionName[GCS_MAX_PRIVATE_NAME];
    char                memberName[GCS_MAX_GROUP_NAME];
    char                groupName[GCS_MAX_GROUP_NAME];
    char                connectionNameRoot[DSM_MAX_CONNECTION_NAME_ROOT_SIZE];
    ITS_USHORT          nodeId;
    ITS_MUTEX           bufAllocateLock;
    ITS_MUTEX           bufFindLock;
    ITS_MUTEX           bufFreeLock;
    ITS_MUTEX           bufCommitLock;
    ITS_MUTEX           bufLockUnlockLock;
}
DSM_LocalMember;


typedef struct
{
    ITS_BOOLEAN         valid;
    ITS_BOOLEAN         normal;
    char                memberName[GCS_MAX_GROUP_NAME];
    char                syncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT          syncMemIpPort;
}
DSM_RemoteMember;


typedef struct
{
    DSM_RemoteMember    members[DSM_MAX_REMOTE_NODES];
}
DSM_RemoteMembers;

/*
 * Result types (passed through Tcb).
 */

enum
{
    DSM_RESULT_ALLOCATE_ROW             = 1,
    DSM_RESULT_FIND_ROW                 = 2,
    DSM_RESULT_FREE_ROW                 = 3,
    DSM_RESULT_COMMIT_ROW               = 4,
    DSM_RESULT_LOCK_UNLOCK_ROW          = 5,
    DSM_RESULT_LOCK_UNLOCK_TABLE        = 6,
    DSM_RESULT_LOCK_UNLOCK_AREA         = 7,
    DSM_RESULT_LOCK_UNLOCK_ROW_NO_LOCK  = 8
};


/*
 * To hold results of various DSM_* public calls (passed through Tcb).
 */

typedef struct
{
    void* allocPtr;
    int error;
}
DSM_ResultAllocateRow;


typedef struct
{
    void* findPtr;
    int error;
}
DSM_ResultFindRow;


typedef struct
{
    int error;
}
DSM_ResultFreeRow;


typedef struct
{
    int error;
}
DSM_ResultCommitRow;

typedef struct
{
    int error;
}
DSM_ResultLockUnlockRow;

typedef struct
{
    int error;
}
DSM_ResultLockUnlockTable;

typedef struct
{
    int error;
}
DSM_ResultLockUnlockArea;

typedef struct
{
    int error;
}
DSM_ResultLockUnlockRowNoLock;


typedef struct
{
    ITS_INT     discriminator;

    union
    {
        DSM_ResultAllocateRow           allocateRow;
        DSM_ResultFindRow               findRow;
        DSM_ResultFreeRow               freeRow;
        DSM_ResultCommitRow             commitRow;
        DSM_ResultLockUnlockRow         lockUnlockRow;
        DSM_ResultLockUnlockTable       lockUnlockTable;
        DSM_ResultLockUnlockArea        lockUnlockArea;
        DSM_ResultLockUnlockRowNoLock   lockUnlockRowNoLock;
    } u;
}
DSM_Result;


/*
 * Transaction Control Block (one transaction associated for every message
 * send through GCS).
 */

typedef struct _st_DSM_Tcb
{
    ITS_UINT            tid;
    ITS_CONDVAR         condVar;
    ITS_MUTEX           condVarGuard;
    DSM_Result          result;

    struct _st_DSM_Tcb* next;
}
DSM_Tcb;


/*
 * Tcb Manager.
 */

typedef struct 
{
    HASH_Table          table;
    ITS_RWLOCK          tableRwLock;
    DSM_Tcb*            freeList;
    ITS_MUTEX           freeListLock;
}
DSM_TcbManager;


/*
 * Tid allocator.
 */

typedef struct
{
    ITS_UINT            currentTid;
    ITS_MUTEX           lock;
}
DSM_TidAllocator;


/*
 * Message types send through GCS.
 */

enum 
{
    DSM_MSG_ALLOCATE_ROW            = 1,
    DSM_MSG_FIND_ROW                = 2,
    DSM_MSG_FREE_ROW                = 3,
    DSM_MSG_COMMIT_ROW              = 4,
    DSM_MSG_JOIN_INFO               = 5,
    DSM_MSG_SYNC_LOCK               = 6,
    DSM_MSG_SYNC_UNLOCK             = 7,
    DSM_MSG_SYNC_MEM                = 8,
    DSM_MSG_SYNC_INVALID_MASTER     = 9,
    DSM_MSG_SYNC_MEM_TCP            = 10,
    DSM_MSG_LOCK_UNLOCK_ROW         = 11,
    DSM_MSG_LOCK_UNLOCK_TABLE       = 12,
    DSM_MSG_LOCK_UNLOCK_AREA        = 13,
    DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK = 14
};


/*
 * Message definitions send through GCS (serialized/deserialized).
 */

/* DSM_MsgAllcateRow serialization => struct + key. */

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_OCTET*  key;
    ITS_UINT    klen;
    ITS_UINT    size;
    ITS_BOOLEAN withLock;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgAllocateRow;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_OCTET*  key;
    ITS_UINT    klen;
    ITS_BOOLEAN withLock;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgFindRow;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_OCTET*  key;
    ITS_UINT    klen;
    ITS_POINTER objectInTable;
    ITS_BOOLEAN withLock;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgFreeRow;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_OCTET*  key;
    ITS_UINT    klen;
    ITS_POINTER object;
    ITS_UINT    size;
    ITS_POINTER objectInTable;
    ITS_BOOLEAN withLock;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgCommitRow;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    originMemberState;
    char        originMemberName[GCS_MAX_GROUP_NAME];
    char        destinationMemberName[GCS_MAX_GROUP_NAME];
    char        originMemberSyncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT  originMemberSyncMemIpPort;
}
DSM_MsgJoinInfo;

typedef struct
{
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];


}
DSM_MsgSyncLock;

typedef struct
{
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];


}
DSM_MsgSyncUnlock;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    seq;
    ITS_BOOLEAN last;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];
    ITS_UINT    size;
    char        data[1];
}
DSM_MsgSyncMem;

typedef struct
{
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];
    ITS_UINT    masterState;
}
DSM_MsgSyncInvalidMaster;

/*
 * DSM SYNC MEM TCP commands.
 */

enum
{
    DSM_SYNC_MEM_TCP_SLAVE_DO_CONNECT   = 1,
    DSM_SYNC_MEM_TCP_MASTER_DO_SEND     = 2,
    DSM_SYNC_MEM_TCP_SLAVE_DO_RECEIVE   = 3,
    DSM_SYNC_MEM_TCP_MASTER_DO_CLOSE    = 4,
    DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE     = 5
};

typedef struct
{
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];
    ITS_UINT    command;
    ITS_UINT    size;
}
DSM_MsgSyncMemTcp;

/*
 * Lock/Unlock related.
 */

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_OCTET*  key;
    ITS_UINT    klen;
    ITS_POINTER objectInTable;
    ITS_BOOLEAN lockUnlockToggle;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgLockUnlockRow;

typedef struct
{
    ITS_UINT    tid;
    ITS_UINT    tableId;
    ITS_BOOLEAN lockUnlockToggle;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgLockUnlockTable;

typedef struct
{
    ITS_UINT    tid;
    ITS_BOOLEAN lockUnlockToggle;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgLockUnlockArea;

typedef struct
{
    ITS_UINT    tid;
    ITS_POINTER objectInTable;
    ITS_BOOLEAN lockUnlockToggle;
    ITS_UINT    originThreadId;
    char        originMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgLockUnlockRowNoLock;

typedef struct
{
    ITS_INT     discriminator;

    union
    {
        DSM_MsgAllocateRow          allocateRow;
        DSM_MsgFindRow              findRow;
        DSM_MsgFreeRow              freeRow;
        DSM_MsgCommitRow            commitRow;
        DSM_MsgJoinInfo             joinInfo;
        DSM_MsgSyncLock             syncLock;
        DSM_MsgSyncUnlock           syncUnlock;
        DSM_MsgSyncMem              syncMem;
        DSM_MsgSyncInvalidMaster    syncInvalidMaster;
        DSM_MsgSyncMemTcp           syncMemTcp;
        DSM_MsgLockUnlockRow        lockUnlockRow;
        DSM_MsgLockUnlockTable      lockUnlockTable;
        DSM_MsgLockUnlockArea       lockUnlockArea;
        DSM_MsgLockUnlockRowNoLock  lockUnlockRowNoLock;
    } u;
}
DSM_Message;


/*
 * Object part. 
 */

typedef struct
{
    void*                       mapAddr;
    void*                       sysMapAddr;
    ITS_UINT                    size;
    ITS_MUTEX                   tablesLock;
    DSM_TcbManager              tcbManager;
    DSM_TidAllocator            tidAllocator;
    DSM_LocalMember             local;
    DSM_RemoteMembers           remotes;
    DSM_Procedures              procedures;
    DSM_StateData               stateData;
    DSM_RmStateData             rmStateData;
    DSM_JoinData                joinData;
    DSM_SyncData                syncData;
    DSM_MemData*                memData;         
}
DSM_ObjectPart;


#define DSM_MAP_ADDR(x) \
    (((DSM_Area*)(x))->dsm.mapAddr)

#define DSM_SYS_MAP_ADDR(x) \
    (((DSM_Area*)(x))->dsm.sysMapAddr)

#define DSM_SIZE(x) \
    (((DSM_Area*)(x))->dsm.size)

#define DSM_TABLES_LOCK(x) \
    (((DSM_Area*)(x))->dsm.tablesLock)

#define DSM_TCB_MANAGER(x) \
    (((DSM_Area*)(x))->dsm.tcbManager)

#define DSM_TID_ALLOCATOR(x) \
    (((DSM_Area*)(x))->dsm.tidAllocator)

#define DSM_LOCAL(x) \
    (((DSM_Area*)(x))->dsm.local)

#define DSM_REMOTES(x) \
    (((DSM_Area*)(x))->dsm.remotes)

#define DSM_PROCEDURES(x) \
    (((DSM_Area*)(x))->dsm.procedures)

#define DSM_STATE_DATA(x) \
    (((DSM_Area*)(x))->dsm.stateData)

#define DSM_RM_STATE_DATA(x) \
    (((DSM_Area*)(x))->dsm.rmStateData)

#define DSM_JOIN_DATA(x) \
    (((DSM_Area*)(x))->dsm.joinData)

#define DSM_SYNC_DATA(x) \
    (((DSM_Area*)(x))->dsm.syncData)

#define DSM_MEM_DATA(x) \
    (((DSM_Area*)(x))->dsm.memData)

#define DSM_AREA_INFO(x) \
    (((DSM_Area*)(x))->dsm.memData->areaInfo)

#define DSM_TABLES_INFO(x) \
    (((DSM_Area*)(x))->dsm.memData->tablesInfo)

#define DSM_PROCEDURE_MANAGER(x) \
    (((DSM_Area*)(x))->dsm.memData->procedureManager)

#endif /* _DSM_IMPL_H_ */

