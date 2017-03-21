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
 * LOG: Revision 9.1  2005/03/23 12:53:23  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:39  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:53  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.10  2002/06/24 16:03:49  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.9  2002/06/21 21:09:27  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.8  2002/06/21 19:30:43  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.7  2002/06/20 22:48:48  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.6  2002/06/20 19:53:09  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.5  2002/06/14 21:07:50  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.4  2002/06/13 21:52:25  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.3  2002/06/12 21:55:45  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.2  2002/06/10 21:49:51  hdivoux
 * LOG: Work in progress.
 * LOG:
 * LOG: Revision 1.1  2002/04/11 20:42:29  hdivoux
 * LOG: Creation.
 * LOG:
 *
 *****************************************************************************/

#if !defined(_DSM_SCI_IMPL_H_)
#define _DSM_SCI_IMPL_H_

#include <its.h>
#include <its_dsm.h>
#include <its_hash.h>
#include <its_list.h>
#include <its_condvar.h>
#include <its_rwlock.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_sockets.h>

#include <sisci_api.h>

#ident "$Id: dsm_sci_impl.h,v 1.1.1.1 2007-10-08 11:11:52 bsccs2 Exp $"

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
 ** Configuration strings (specific to SCI) for Resource Manager database.
 **
 */

/*
 * Configuration strings (specific to SCI) for 'DsmFtGroup[n]' sections.
 * - All mandatory.
 */

#define DSM_SCI_LOCAL_ADAPTER_NO_STRING     "dsmSciLocalAdapterNo"
#define DSM_SCI_REMOTE_ADAPTER_NO_STRING    "dsmSciRemoteAdapterNo"
#define DSM_SCI_LOCAL_NODE_ID_STRING        "dsmSciLocalNodeId"
#define DSM_SCI_REMOTE_NODE_ID_STRING       "dsmSciRemoteNodeId"
#define DSM_SCI_LOCAL_SEGMENT_ID_STRING     "dsmSciLocalSegmentId"
#define DSM_SCI_REMOTE_SEGMENT_ID_STRING    "dsmSciRemoteSegmentId"
#define DSM_SCI_LOCAL_BASE_IRT_NO_STRING    "dsmSciLocalBaseIrtNo"
#define DSM_SCI_REMOTE_BASE_IRT_NO_STRING   "dsmSciRemoteBaseIrtNo"

/*
 * Configuration strings (specific to SCI) for 'DsmFtGroup[n]' sections.
 * - All optional.
 * - All timeouts and intervals are in milliseconds.
 */

/* Default value is DSM_DEFAULT_IRT_JOIN_TIMEOUT. */
#define DSM_SCI_IRT_JOIN_TIMEOUT_STRING         "dsmSciIrtJoinTimeout"

/* Default value is DSM_DEFAULT_IRT_TRIGGER_TIMEOUT. */
#define DSM_SCI_IRT_TRIGGER_TIMEOUT_STRING      "dsmSciIrtTriggerTimeout"

/* Default value is DSM_DEFAULT_IRT_TRIGGER_INTERVAL. */
#define DSM_SCI_IRT_TRIGGER_INTERVAL_STRING     "dsmSciIrtTriggerInterval"

/* Default value is DSM_DEFAULT_IRT_WAIT_TIMEOUT. */
#define DSM_SCI_IRT_WAIT_TIMEOUT_STRING         "dsmSciIrtWaitTimeout"

/* Default value is DSM_DEFAULT_IRT_CONNECT_TIMEOUT. */
#define DSM_SCI_IRT_CONNECT_TIMEOUT_STRING      "dsmSciIrtConnectTimeout"

/* Default value is DSM_DEFAULT_SEGMENT_CONNECT_TIMEOUT. */
#define DSM_SCI_SEGMENT_CONNECT_TIMEOUT_STRING  "dsmSciSegmentConnectTimeout"

/* Default value is DSM_DEFAULT_SYNC_TIMEOUT. */
#define DSM_SCI_SYNC_TIMEOUT_STRING             "dsmSciSyncTimeout"

/* Default value is DSM_DEFAULT_PING_INTERVAL. */
#define DSM_SCI_PING_INTERVAL_STRING            "dsmSciPingInterval"

/* Default value is DSM_DEFAULT_FLOW_CTRL_WND. */
#define DSM_SCI_FLOW_CTRL_WND_STRING            "dsmSciFlowCtrlWnd"

/* Default value is DSM_DEFAULT_RETRY_VALUE. */
#define DSM_SCI_RETRY_VALUE_STRING              "dsmSciRetryValue"

/* Default value is DSM_DEFAULT_LOCAL_DEBUG. */
#define DSM_SCI_LOCAL_DEBUG_STRING              "dsmSciLocalDebug"


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
 ** DSM (SCI) Data class.
 **
 */

/*
 * DSM (SCI) Data class definition.
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

#define DSM_DATA_CLASS_NAME  "DSM Data Class - SCI"


/*
 * Definitions used by DSM (SCI) Data object.
 */

/*
 * DSM maximun number of Fault Tolerance Group members (MUST BE >= 1).
 * SCI is currently limited to two members.
 */

#define DSM_MAX_MEMBERS                     (2)

#define DSM_MAX_REMOTE_MEMBERS              (DSM_MAX_MEMBERS - 1)

/*
 * DSM default IRT join timeout. 
 */
#define DSM_DEFAULT_IRT_JOIN_TIMEOUT        (1000)

/*
 * DSM default IRT trigger timeout. MUST BE >= 3 * (default IRT wait timeout).
 */
#define DSM_DEFAULT_IRT_TRIGGER_TIMEOUT     (500)

/*
 * DSM default IRT trigger interval. MUST BE <= 1/4 * (default IRT trigger timeout).
 */
#define DSM_DEFAULT_IRT_TRIGGER_INTERVAL    (125)

/*
 * DSM default IRT wait timeout.
 */
#define DSM_DEFAULT_IRT_WAIT_TIMEOUT        (167)

/*
 * DSM default IRT connect timeout.
 */
#define DSM_DEFAULT_IRT_CONNECT_TIMEOUT     (250)

/*
 * DSM default Segment connect timeout.
 */
#define DSM_DEFAULT_SEGMENT_CONNECT_TIMEOUT (250)

/*
 * DSM default sync timeout.
 */
#define DSM_DEFAULT_SYNC_TIMEOUT            (4000)

/*
 * DSM default ping interval.
 */
#define DSM_DEFAULT_PING_INTERVAL           (250)

/*
 * DSM default flow control window.
 */
#define DSM_DEFAULT_FLOW_CTRL_WND           (40)

/*
 * DSM default retry value.
 */
#define DSM_DEFAULT_RETRY_VALUE             (5)

/*
 * DSM default local debug.
 */
#define DSM_DEFAULT_LOCAL_DEBUG             (0)


/*
 * Main Lock.
 */
typedef struct
{
    ITS_UINT    nodeId;
}
DSM_MainLock;

/*
 * Distributed Locks (DSM and tables).
 */
typedef struct
{
    ITS_UINT    counter;
    ITS_UINT    threadId;
    ITS_USHORT  nodeId;
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
 * DSM shared (through SCI) memory data. Unique instance of this structure is
 * stored at the zero page in the shared memory.
 */

typedef struct
{
    struct malloc_state     state;
    ITS_UINT                size;
    ITS_POINTER             base;
    ITS_POINTER             top;
    ITS_POINTER             curbrk;
    HASH_Table              tables;
    DSM_MainLock            mainLock;
    DSM_DsmInfo             dsmInfo;
    DSM_TablesInfo          tablesInfo;
}
DSM_MemData;

/*
 * DSM configuration related (SCI).
 */

typedef struct
{
    ITS_ULONG   irtJoinTimeout;
    ITS_ULONG   irtTriggerTimeout;
    ITS_ULONG   irtTriggerInterval;
    ITS_ULONG   irtWaitTimeout;
    ITS_ULONG   irtConnectTimeout;
    ITS_ULONG   segmentConnectTimeout;
    ITS_ULONG   syncTimeout;
    ITS_ULONG   pingInterval;
    ITS_ULONG   flowCtrlWnd;
    ITS_ULONG   retryValue;
    ITS_ULONG   localDebug;
}
DSM_Config;

/*
 * DSM monitor related.
 */
typedef struct
{
    ITS_THREAD      thread;
    ITS_BOOLEAN     exitThread;
    ITS_SEMAPHORE   startSema;
    ITS_SEMAPHORE   stopSema;
    ITS_BOOLEAN     started;
    ITS_UINT        waitingTrans;
    ITS_MUTEX       waitingTransLock;
    ITS_UINT        pendingTrans;
    ITS_MUTEX       pendingTransLock;
}
DSM_Monitor;

/*
 * DSM state related (SCI).
 */

enum
{
    DSM_STATE_INITIAL           = 1,
    DSM_STATE_JOINING           = 2,
    DSM_STATE_SYNC_SLAVE        = 3,
    DSM_STATE_SYNC_MASTER       = 4,
    DSM_STATE_OP_ONE_MB         = 5,
    DSM_STATE_OP_TWO_MB         = 6
};

#define IsDsmStateInitial(state)        ((state) == DSM_STATE_INITIAL)
#define IsDsmStateJoining(state)        ((state) == DSM_STATE_JOINING)
#define IsDsmStateSyncSlave(state)      ((state) == DSM_STATE_SYNC_SLAVE)
#define IsDsmStateSyncMaster(state)     ((state) == DSM_STATE_SYNC_MASTER)
#define IsDsmStateOpOneMb(state)        ((state) == DSM_STATE_OP_ONE_MB)
#define IsDsmStateOpTwoMb(state)        ((state) == DSM_STATE_OP_TWO_MB)

#define IsDsmStateSync(state)                       \
            ((state) == DSM_STATE_SYNC_SLAVE    ||  \
             (state) == DSM_STATE_SYNC_MASTER)

typedef struct
{
    ITS_UINT    state;
    ITS_BOOLEAN requestOpOneMb;
}
DSM_StateData;


/*
 * DSM join/leave related.
 */
typedef struct
{
    ITS_SEMAPHORE   joinSema;
    ITS_SEMAPHORE   leaveSema;
}
DSM_JoinData;


/*
 * DSM synchronization related (slave to synchronize with master).
 */ 
typedef struct
{
    ITS_UINT    dummy;
}
DSM_SyncData;

/*
 * DSM connection releated (SCI).
 */

typedef struct
{
    sci_desc_t  sd;
}
DSM_Connection;

/*
 * DSM local member related.
 */

typedef struct
{
    ITS_UINT                    adapterNo;
    ITS_UINT                    nodeId;
    ITS_UINT                    slaveIrtNo;
    ITS_UINT                    masterIrtNo;
    ITS_UINT                    syncIrtNo;
    ITS_UINT                    opIrtNo;
    sci_local_interrupt_t       slaveIrt;
    sci_local_interrupt_t       masterIrt;
    sci_local_interrupt_t       syncIrt;
    sci_local_interrupt_t       opIrt;
    ITS_UINT                    segmentId;
    volatile void*              mapAddr;
    sci_map_t                   map;
    sci_local_segment_t         segment;
}
DSM_LocalMember;

/*
 * DSM remote member related.
 */ 

typedef struct
{
    ITS_UINT                    adapterNo;
    ITS_UINT                    nodeId;
    ITS_UINT                    slaveIrtNo;
    ITS_UINT                    masterIrtNo;
    ITS_UINT                    syncIrtNo;
    ITS_UINT                    opIrtNo;
    sci_remote_interrupt_t      slaveIrt;
    sci_remote_interrupt_t      masterIrt;
    sci_remote_interrupt_t      syncIrt;
    sci_remote_interrupt_t      opIrt;
    ITS_UINT                    segmentId;
    volatile void*              mapAddr;
    sci_map_t                   map;
    sci_remote_segment_t        segment;
    sci_sequence_t              sequence;
}
DSM_RemoteMember;

/*
 * Transaction Control Block (one transaction associated with each DSM call).
 */

typedef struct _DSM_Tcb
{
    ITS_UINT            tid;
    ITS_ULONG           threadId;
    ITS_UINT            tableId;
    ITS_CONDVAR         condVar;
    ITS_MUTEX           condVarGuard;

    struct _DSM_Tcb*    next;
}
DSM_Tcb;


/*
 * Tcb Manager.
 */

typedef struct 
{
    DSM_Tcb*            activeListHead;
    DSM_Tcb*            activeListTail;
    ITS_MUTEX           activeListLock;
    ITS_UINT            activeEntries;
    DSM_Tcb*            freeList;
    ITS_MUTEX           freeListLock;
    ITS_UINT            freeEntries;
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
 * DSM (SCI) Data object definition.
 */

typedef struct
{
    ITS_MUTEX               tablesLock;
    DSM_Config              config;
    DSM_TcbManager          tcbManager;
    DSM_TidAllocator        tidAllocator;
    DSM_Connection          connection;
    DSM_LocalMember         localMember;
    DSM_RemoteMember        remoteMember;
    DSM_Monitor             monitor;
    DSM_StateData           stateData;
    DSM_JoinData            joinData;
    DSM_SyncData            syncData;
    DSM_MemData*            memData;
    DSM_CoreObject*         coreObject;
    DSM_InstObject*         instObject;
}
DSM_DataObjectPart;

typedef struct
{
    ITS_CoreObjectPart  coreObject;
    DSM_DataObjectPart  dataObject;
}
DSM_DataObject;


#define DSM_DATA_CORE_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.coreObject)

#define DSM_DATA_INST_OBJECT(x) \
    (((DSM_DataObject*)(x))->dataObject.instObject)

#define DSM_DATA_TABLES_LOCK(x) \
    (((DSM_DataObject*)(x))->dataObject.tablesLock)

#define DSM_DATA_CONFIG(x) \
    (((DSM_DataObject*)(x))->dataObject.config)

#define DSM_DATA_TCB_MANAGER(x) \
    (((DSM_DataObject*)(x))->dataObject.tcbManager)

#define DSM_DATA_TID_ALLOCATOR(x) \
    (((DSM_DataObject*)(x))->dataObject.tidAllocator)

#define DSM_DATA_CONNECTION(x) \
    (((DSM_DataObject*)(x))->dataObject.connection)

#define DSM_DATA_LOCAL_MEMBER(x) \
    (((DSM_DataObject*)(x))->dataObject.localMember)

#define DSM_DATA_REMOTE_MEMBER(x) \
    (((DSM_DataObject*)(x))->dataObject.remoteMember)

#define DSM_DATA_MONITOR(x) \
    (((DSM_DataObject*)(x))->dataObject.monitor)

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

#define DSM_DATA_FT_GROUP_ID(x)                         \
    ((DSM_DATA_INST_OBJECT(x) != NULL)               ?  \
     (DSM_INST_FT_GROUP_ID(DSM_DATA_INST_OBJECT(x))) :  \
     (DSM_INVALID_FT_GROUP_ID))

#if defined(__cplusplus)
}
#endif

#endif /* _DSM_SCI_IMPL_H_ */


