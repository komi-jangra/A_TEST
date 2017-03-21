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
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.3  2005/03/21 13:51:37  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.2  2004/02/16 12:22:55  yranade
 * LOG: TCAP Act-Act Msg Based Redundancy changes.
 * LOG:
 * LOG: Revision 7.2.10.1  2004/01/05 09:25:44  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.2.6.1  2003/09/05 10:14:44  akumar
 * LOG: Msg based redundancy scheme commit in this branch.
 * LOG:
 * LOG: Revision 7.2.4.2  2003/08/30 16:57:14  randresol
 * LOG: Add logic for message based redundnacy.
 * LOG:
 * LOG: Revision 7.2.4.1  2003/05/05 22:03:45  randresol
 * LOG: Tag for GCS ISUP prototype
 * LOG:
 * LOG: Revision 7.2  2003/01/30 20:46:12  mmiers
 * LOG: Use inheritence.  Start adding infrastructure for DSM to use
 * LOG: different lookup mechanismsm.
 * LOG:
 * LOG: Revision 7.1.4.1  2003/04/08 17:47:56  randresol
 * LOG: Chages for GCS TCAP prototype
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:41:37  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_DSM_GCS_IMPL_H_)
#define _DSM_GCS_IMPL_H_

#include <its.h>
#include <its_dsm.h>
#include <its_hash.h>
#include <its_rb.h>
#include <its_splay.h>
#include <its_list.h>
#include <its_mlist.h>
#include <its_condvar.h>
#include <its_rwlock.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_sockets.h>

#include <gcs_client.h>
#include "dsm_gcs_impl_local.h"

#ident "$Id: dsm_gcs_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

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
 ** Configuration strings (specific to GCS) for Resource Manager database.
 **
 */

/*
 * Configuration strings (specific to GCS) for 'DsmFtGroup[n]' sections.
 * - All optional unless indicated.
 * - All timeouts are in milliseconds.
 */

#define DSM_GCS_DAEMON_NAME_STRING              "dsmGcsDaemonName"
#define DSM_GCS_CONNECT_TIMEOUT_STRING          "dsmGcsConnectTimeout"
#define DSM_GCS_GROUP_NAME_STRING               "dsmGcsGroupName"
#define DSM_GCS_CONNECTION_NAME_ROOT_STRING     "dsmGcsConnectionNameRoot"
#define DSM_GCS_RECEIVER_ALIVE_TIMEOUT_STRING   "dsmGcsReceiverAliveTimeout"
#define DSM_GCS_SYNC_MEM_USE_TCP_STRING         "dsmGcsSyncMemUseTcp"
#define DSM_GCS_SYNC_MEM_USE_GCS_STRING         "dsmGcsSyncMemUseGcs"
#define DSM_GCS_SYNC_MEM_TIMEOUT_STRING         "dsmGcsSyncMemTimeout"
#define DSM_GCS_SYNC_MEM_CONNECT_TIMEOUT_STRING "dsmGcsSyncMemConnectTimeout"

/* Default value is DSM_DEFAULT_SELF_JOIN_TIMEOUT. */
#define DSM_GCS_SELF_JOIN_TIMEOUT_STRING        "dsmGcsSelfJoinTimeout"

/* Default value is DSM_DEFAULT_MASTER_JOIN_TIMEOUT. */
#define DSM_GCS_MASTER_JOIN_TIMEOUT_STRING      "dsmGcsMasterJoinTimeout"

/* Mandatory if DSM GCS procedure sync mem use TCP. */
#define DSM_GCS_SYNC_MEM_IP_ADDRESS_STRING      "dsmGcsSyncMemIpAddress"

/* Mandatory if DSM GCS procedure sync mem use TCP. */
#define DSM_GCS_SYNC_MEM_IP_PORT_STRING         "dsmGcsSyncMemIpPort"



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
 ** DSM (GCS) Data class.
 **
 */

/*
 * DSM (GCS) Data class definition.
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

#define DSM_DATA_CLASS_NAME  "DSM Data Class - GCS"


/*
 * Definitions used by DSM (GCS) Data object.
 */ 

/*
 * DSM maximun number of Fault Tolerance Group members (MUST BE >= 1).
 */

#define DSM_MAX_MEMBERS                     (32)

#define DSM_MAX_REMOTE_MEMBERS              (DSM_MAX_MEMBERS - 1)


/*
 * DSM maximum message size (128K + 8K). MUST BE less than GCS maximum message
 * size (i.e. 144000).
 */
#define DSM_MAX_MSG_SIZE                    (139264)

/*
 * DSM maximum object size (128K). MUST BE less than DSM maximum message size
 * minus 8K (4K for key and 4K extra for sizeof(DSM_Message)).
 */
#define DSM_MAX_OBJECT_SIZE                 (131072)

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
 * DSM maximum connection name root size.
 */
#define DSM_MAX_CONNECTION_NAME_ROOT_SIZE   (2)

/*
 * DSM maximum IP address size.
 */
#define DSM_MAX_IP_ADDRESS_SIZE             (32)

/*
 * DSM default self join timeout. 
 */
#define DSM_DEFAULT_SELF_JOIN_TIMEOUT       (5000)

/*
 * DSM default master join timeout.
 */
#define DSM_DEFAULT_MASTER_JOIN_TIMEOUT     (5000)

/*
 * DSM conversions.
 */
#define DSM_MSEC_PER_SEC                    (1000)
#define DSM_USEC_PER_MSEC                   (1000)


/*
 * Distributed Locks (DSM and tables).
 */
typedef struct
{
    ITS_UINT    counter;
    ITS_UINT    threadId;
    char        memberName[GCS_MAX_GROUP_NAME];
}
DSM_DistributedLock;

/*
 * DSM info (distributed lock...).
 */ 
typedef struct
{
    DSM_DistributedLock lock;
}
DSM_DsmInfo;

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
    DSM_PROCEDURE_LOCK_UNLOCK_DSM           = 7,
    DSM_PROCEDURE_LOCK_UNLOCK_ROW_NO_LOCK   = 8,
    DSM_PROCEDURE_SYNC_REQUEST              = 9,
    DSM_PROCEDURE_SYNC_LOCK                 = 10
};

typedef struct _st_DSM_Procedure
{
    /* Discriminator. */
    ITS_UINT                    type;

    /* Procedure arguments. */
    GCS_SERVICE                 service;
    char                        sender[GCS_MAX_GROUP_NAME];
    ITS_INT                     numGroups;
    char                        groups[DSM_MAX_MEMBERS][GCS_MAX_GROUP_NAME];
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



typedef struct _st_DSM_Procedure_sync
{
    /* Discriminator. */
    ITS_UINT                    type;

    /* Procedure arguments. */
    GCS_SERVICE                 service;
    char                        sender[GCS_MAX_GROUP_NAME];
    ITS_INT                     numGroups;
    char                        groups[DSM_MAX_MEMBERS][GCS_MAX_GROUP_NAME];
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
    char                        msg[DSM_MAX_MSG_SIZE];
}
DSM_Procedure_sync;

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
    DSM_DsmInfo                 dsmInfo;
    DSM_TablesInfo              tablesInfo;
    DSM_ProcedureManager        procedureManager;
}
DSM_MemData;


/*
 * DSM configuration related (GCS).
 */

typedef struct
{
    char        gcsDaemonName[DSM_MAX_DAEMON_NAME_SIZE];
    char        gcsStubDaemonName[DSM_MAX_DAEMON_NAME_SIZE];
    char        groupName[DSM_MAX_GROUP_NAME_SIZE];
    char        connectionNameRoot[DSM_MAX_CONNECTION_NAME_ROOT_SIZE];
    GCS_TIME    connectTimeout;
    GCS_TIME    receiverAliveTimeout;
    ITS_BOOLEAN syncMemUseTcp;
    ITS_BOOLEAN syncMemUseGcs;
    char        syncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT  syncMemIpPort;
    ITS_ULONG   syncMemTimeout;
    ITS_ULONG   syncMemConnectTimeout;
    ITS_ULONG   selfJoinTimeout;
    ITS_ULONG   masterJoinTimeout;
}
DSM_Config;

/*
 * DSM state related (GCS).
 */

enum
{
    DSM_STATE_INITIAL           = 1,
    DSM_STATE_JOINING           = 2,
    DSM_STATE_NORMAL            = 3,
    DSM_STATE_SYNC_WAIT         = 4,
    DSM_STATE_SYNC_SLAVE        = 5,
    DSM_STATE_SYNC_MASTER       = 6,
    DSM_STATE_SYNC_NEUTRAL      = 7,
    DSM_STATE_INVALID           = 8
};

#define IsDsmStateInitial(state)        ((state) == DSM_STATE_INITIAL)
#define IsDsmStateJoining(state)        ((state) == DSM_STATE_JOINING)
#define IsDsmStateNormal(state)         ((state) == DSM_STATE_NORMAL)
#define IsDsmStateSyncWait(state)       ((state) == DSM_STATE_SYNC_WAIT)
#define IsDsmStateSyncSlave(state)      ((state) == DSM_STATE_SYNC_SLAVE)
#define IsDsmStateSyncMaster(state)     ((state) == DSM_STATE_SYNC_MASTER)
#define IsDsmStateSyncNeutral(state)    ((state) == DSM_STATE_SYNC_NEUTRAL)
#define IsDsmStateInvalid(state)        ((state) == DSM_STATE_INVALID)

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
 * DSM join related.
 */
typedef struct
{
    ITS_ULONG           selfTimeout;
    ITS_SEMAPHORE       selfSema;
    ITS_ULONG           masterTimeout;
    ITS_SEMAPHORE       masterSema;
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
    ITS_BOOLEAN             explicitSyncInProgress;
    ITS_UINT                neutralMemberSavedState;
}
DSM_SyncData;


typedef struct
{
    ITS_THREAD          thread;
    GCS_TIME            aliveTimeout;
    ITS_BOOLEAN         exitThread;
}
DSM_Procedures;



typedef struct
{
    GCS_MAILBOX         mailbox;
    GCS_MAILBOX         Stubmailbox;
    GCS_TIME            connectTimeout;
    char                gcsDaemonName[GCS_MAX_GROUP_NAME];
    char                gcsStubDaemonName[GCS_MAX_GROUP_NAME];
    char                connectionName[GCS_MAX_PRIVATE_NAME];
    char                memberName[GCS_MAX_GROUP_NAME];
    char                groupName[GCS_MAX_GROUP_NAME];
    char                connectionNameRoot[DSM_MAX_CONNECTION_NAME_ROOT_SIZE];
    ITS_MUTEX           bufAllocateLock;
    ITS_MUTEX           bufFindLock;
    ITS_MUTEX           bufFreeLock;
    ITS_MUTEX           bufCommitLock;
    ITS_MUTEX           bufLockUnlockLock;
    ITS_OCTET*          bufAllocate;    /* Mutex required. */
    ITS_OCTET*          bufFind;        /* Mutex required. */
    ITS_OCTET*          bufFree;        /* Mutex required. */
    ITS_OCTET*          bufCommit;      /* Mutex required. */
    ITS_OCTET*          bufLockUnlock;  /* Mutex required. */
    ITS_OCTET*          bufKey;         /* Used only by ProceduresThread. */
    ITS_OCTET*          bufObject;      /* Used only by ProceduresThread. */
    char*               bufMsg;         /* Used only by ProceduresThread. */  
}
DSM_LocalMember;


typedef struct
{
    ITS_BOOLEAN         valid;
    char                memberName[GCS_MAX_GROUP_NAME];
    char                syncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT          syncMemIpPort;
    ITS_USHORT          nodeId;
    ITS_USHORT          processId;
    ITS_UINT            lastKnownState;
}
DSM_RemoteMember;


typedef struct
{
    DSM_RemoteMember    members[DSM_MAX_REMOTE_MEMBERS];
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
    DSM_RESULT_LOCK_UNLOCK_DSM          = 7,
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
DSM_ResultLockUnlockDsm;

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
        DSM_ResultLockUnlockDsm         lockUnlockDsm;
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
    union
    {
        HASH_Table          hash;
        REDBLACK_Tree       *tree;
        SPLAY_Tree          *splay;
    }
    table;
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
    DSM_MSG_SYNC_REQUEST            = 6,
    DSM_MSG_SYNC_LOCK               = 7,
    DSM_MSG_SYNC_LOCK_RETRY         = 8,
    DSM_MSG_SYNC_UNLOCK             = 9,
    DSM_MSG_SYNC_MEM                = 10,
    DSM_MSG_SYNC_INVALID_MASTER     = 11,
    DSM_MSG_SYNC_MEM_TCP            = 12,
    DSM_MSG_LOCK_UNLOCK_ROW         = 13,
    DSM_MSG_LOCK_UNLOCK_TABLE       = 14,
    DSM_MSG_LOCK_UNLOCK_DSM         = 15,
    DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK = 16,
    DSM_MSG_MULTICAST_EVENT         = 17,
    DSM_MSG_TO_TCAP_FROM_SCCP       = 18,
    DSM_MSG_TO_TCAP_FROM_APPL       = 19,
    DSM_MSG_TCAP_ALLOCATE_DID       = 20 
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
    char        originMemberName[GCS_MAX_GROUP_NAME];
    char        destinationMemberName[GCS_MAX_GROUP_NAME];
    char        originMemberSyncMemIpAddress[DSM_MAX_IP_ADDRESS_SIZE];
    ITS_USHORT  originMemberSyncMemIpPort;
    ITS_USHORT  originMemberNodeId;
    ITS_USHORT  originMemberProcessId;
    ITS_UINT    originMemberState;
}
DSM_MsgJoinInfo;

typedef struct
{
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];
}
DSM_MsgSyncRequest;

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
DSM_MsgSyncLockRetry;

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
    DSM_SYNC_MEM_TCP_SLAVE_DO_CLOSE     = 5,
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
DSM_MsgLockUnlockDsm;

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
    ITS_USHORT source;
    ITS_USHORT dest;
    ITS_EVENT ev;
    ITS_OCTET data[768];
}
DSM_MsgMulticastEvent;

typedef struct
{
    ITS_EVENT ev;
    ITS_OCTET data[772];
}
DSM_MsgToTcap;

typedef struct
{
    ITS_USHORT originNodeId;
    ITS_USHORT did;
}
DSM_MsgTcapAllocateDid;

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
        DSM_MsgSyncRequest          syncRequest;
        DSM_MsgSyncLock             syncLock;
        DSM_MsgSyncLockRetry        syncLockRetry;
        DSM_MsgSyncUnlock           syncUnlock;
        DSM_MsgSyncMem              syncMem;
        DSM_MsgSyncInvalidMaster    syncInvalidMaster;
        DSM_MsgSyncMemTcp           syncMemTcp;
        DSM_MsgLockUnlockRow        lockUnlockRow;
        DSM_MsgLockUnlockTable      lockUnlockTable;
        DSM_MsgLockUnlockDsm        lockUnlockDsm;
        DSM_MsgLockUnlockRowNoLock  lockUnlockRowNoLock;
        //DSM_MsgMulticastEvent       multicastEvent;
    } u;
}
DSM_Message;
/* DSM Message multi cast Event structure */
typedef struct
{
    ITS_INT     discriminator;
    union
    {
        DSM_MsgMulticastEvent       multicastEvent;
    } u;
}DSM_Message_Multicast;





/*
 * DSM (GCS) Data object definition.
 */

typedef struct
{
    void*                       sysMapAddr;
    ITS_MUTEX                   tablesLock;
    DSM_Config                  config;
    DSM_TcbManager              tcbManager;
    DSM_TidAllocator            tidAllocator;
    DSM_LocalMember             local;
    DSM_RemoteMembers           remotes;
    DSM_Procedures              procedures;
    DSM_StateData               stateData;
    DSM_JoinData                joinData;
    DSM_SyncData                syncData;
    DSM_MemData*                memData;
    DSM_CoreObject*             coreObject;
    DSM_InstObject*             instObject;
    DSM_Tables                  tables;
    MLIST_Manager*              stackMulticastQueue;
    MLIST_Manager*              applMulticastQueue;
}
DSM_DataObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_DataObjectPart  dataObject;
}
DSM_DataObject;


#define DSM_DATA_MAP_ADDR(x) \
    (((DSM_DataObject*)(x))->dataObject.mapAddr)

#define DSM_DATA_SYS_MAP_ADDR(x) \
    (((DSM_DataObject*)(x))->dataObject.sysMapAddr)

#define DSM_DATA_TABLES_LOCK(x) \
    (((DSM_DataObject*)(x))->dataObject.tablesLock)

#define DSM_DATA_CONFIG(x) \
    (((DSM_DataObject*)(x))->dataObject.config)

#define DSM_DATA_TCB_MANAGER(x) \
    (((DSM_DataObject*)(x))->dataObject.tcbManager)

#define DSM_DATA_TID_ALLOCATOR(x) \
    (((DSM_DataObject*)(x))->dataObject.tidAllocator)

#define DSM_DATA_LOCAL(x) \
    (((DSM_DataObject*)(x))->dataObject.local)

#define DSM_DATA_REMOTES(x) \
    (((DSM_DataObject*)(x))->dataObject.remotes)

#define DSM_DATA_PROCEDURES(x) \
    (((DSM_DataObject*)(x))->dataObject.procedures)

#define DSM_DATA_STATE_DATA(x) \
    (((DSM_DataObject*)(x))->dataObject.stateData)

#define DSM_DATA_JOIN_DATA(x) \
    (((DSM_DataObject*)(x))->dataObject.joinData)

#define DSM_DATA_SYNC_DATA(x) \
    (((DSM_DataObject*)(x))->dataObject.syncData)

#define DSM_DATA_MEM_DATA(x) \
    (((DSM_DataObject*)(x))->dataObject.memData)

#define DSM_DATA_DSM_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->dsmInfo)

#define DSM_DATA_TABLES_INFO(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->tablesInfo)

#define DSM_DATA_PROCEDURE_MANAGER(x) \
    (((DSM_DataObject*)(x))->dataObject.memData->procedureManager)

#define DSM_DATA_CORE_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.coreObject)

#define DSM_DATA_INST_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.instObject)

#define DSM_DATA_STACK_MULTICAST_QUEUE(x) \
    (((DSM_DataObject*)(x))->dataObject.stackMulticastQueue)

#define DSM_DATA_APPL_MULTICAST_QUEUE(x) \
    (((DSM_DataObject*)(x))->dataObject.applMulticastQueue)

#define DSM_DATA_FT_GROUP_ID(x)                         \
    ((DSM_DATA_INST_OBJECT(x) != NULL)               ?  \
     (DSM_INST_FT_GROUP_ID(DSM_DATA_INST_OBJECT(x))) :  \
     (DSM_INVALID_FT_GROUP_ID))

/* For the Prototype */

int DSM_LockTableLocalImpl( DSM_CoreObject* coreObj, 
                            ITS_USHORT ftGroupId,
                            ITS_UINT tableId);

int DSM_UnlockTableLocalImpl( DSM_CoreObject* coreObj,
                              ITS_USHORT ftGroupId,
                              ITS_UINT tableId);

void* DSM_AllocNoLockLocalImpl( DSM_CoreObject* coreObj,
                                ITS_USHORT ftGroupId,
                                ITS_UINT tableId,
                                ITS_OCTET* key,
                                ITS_UINT klen,
                                ITS_UINT size,
                                int* error);

void* DSM_FindNoLockLocalImpl( DSM_CoreObject* coreObj,
                               ITS_USHORT ftGroupId,
                               ITS_UINT tableId,
                               ITS_OCTET* key,
                               ITS_UINT klen,
                               int* error);

int DSM_FreeNoLockLocalImpl( DSM_CoreObject* coreObj,
                             ITS_USHORT ftGroupId,
                             ITS_UINT tableId,
                             ITS_OCTET* key,
                             ITS_UINT klen,
                             void* object);

int DSM_CommitNoLockLocalImpl( DSM_CoreObject* coreObj,
                               ITS_USHORT ftGroupId,
                               ITS_UINT tableId,
                               ITS_OCTET* key,
                               ITS_UINT klen,
                               void* object);

void* DSM_AllocLocalImpl( DSM_CoreObject* coreObj,
                          ITS_USHORT ftGroupId,
                          ITS_UINT tableId,
                          ITS_OCTET* key,
                          ITS_UINT klen,
                          ITS_UINT size,
                          int* error);

void* DSM_FindLocalImpl( DSM_CoreObject* coreObj,
                         ITS_USHORT ftGroupId,
                         ITS_UINT tableId,
                         ITS_OCTET* key,
                         ITS_UINT klen,
                         int* error);

int DSM_FreeLocalImpl( DSM_CoreObject* coreObj,
                       ITS_USHORT ftGroupId,
                       ITS_UINT tableId,
                       ITS_OCTET* key,
                       ITS_UINT klen,
                       void* object);

int DSM_CommitLocalImpl( DSM_CoreObject* coreObj,
                         ITS_USHORT ftGroupId,
                         ITS_UINT tableId,
                         ITS_OCTET* key,
                         ITS_UINT klen,
                         void* object);


void
BroadCastEventNotificationCallback( ITS_POINTER object,
                                    ITS_POINTER userData,
                                    ITS_POINTER callData);




#if defined(__cplusplus)
}
#endif

#endif /* _DSM_GCS_IMPL_H_ */


