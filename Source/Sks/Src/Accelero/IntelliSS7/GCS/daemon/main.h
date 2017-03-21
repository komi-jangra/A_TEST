 #ifdef PLATFORM_IMR
 #include <bpmxxx_commonDef.h>
 #include <bpmxxx_OAM_commonDef.h>
 #include <bpmxxx_platformLib.h>
 #include <stdlib.h>
 #endif
#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
//#include <ipcfrm_msgdef.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
 SysAddr slfAddr;
#endif

#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

typedef unsigned int     ITS_BOOLEAN;
typedef unsigned char    ITS_OCTET;
typedef unsigned short   ITS_USHORT;
typedef unsigned int     ITS_UINT;
typedef unsigned long    ITS_ULONG;
typedef char             ITS_CHAR;
typedef short            ITS_SHORT;
typedef int              ITS_INT;
typedef long             ITS_LONG;
typedef float            ITS_FLOAT;
typedef double           ITS_DOUBLE;
typedef void *           ITS_HANDLE;
typedef void *           ITS_SS7_HANDLE;
typedef char *           ITS_POINTER;
#define MAXDATASIZE 8192
#define REQUEST 1
#define RESPONSE 2
#define UNLOCK_REQUEST 3
#define UNLOCK_RESPONSE 4
#define COUNTER_UPDATE 5
#define LOCK_ACK 6
#define UNLOCK_ACK 7
#define POSTIVE_ACK 1
#define NEGATIVE_ACK 2


typedef struct 
{
  ITS_USHORT len;
  ITS_USHORT src;
  ITS_OCTET *data;
}
ITS_EVENT;


#define         MAX_GROUP_NAME 32
#define GCS_MAX_GROUP_NAME  MAX_GROUP_NAME
#define DSM_MAX_IP_ADDRESS_SIZE 32


typedef struct  dummy_message_header {
        unsigned int  type;
        char    private_group_name[MAX_GROUP_NAME];
        unsigned int   num_groups;
        unsigned int hint;
        unsigned int    data_len;
} message_header;
#define Get_Endian(type) ((type) & 0x80000080)
#define Equal_Endian(type) (((type) & 0x80000080)== 0x80000080)
#define Set_Endian(type) (((type) & ~0x80000080)| 0x80000080)
#define Clear_Endian(type) (((type) & ~0x80000080))

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
    ITS_UINT    tid;
    char        syncSlaveMemberName[GCS_MAX_GROUP_NAME];
    char        syncMasterMemberName[GCS_MAX_GROUP_NAME];
    ITS_UINT    command;
    ITS_UINT    size;
}
DSM_MsgSyncMemTcp;
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
//        DSM_MsgMulticastEvent       multicastEvent;
    } u;
}
DSM_Message;


typedef struct
{
    ITS_INT     discriminator;

    union
    {
        DSM_MsgMulticastEvent       multicastEvent;
        ITS_UINT  x;
    } u;
}
DSM_Message_1;


void print_time (char *message,...);
#define GCSUTILTRACE(level,args)\
         print_time   args;



#ifdef LOGGER_IMR
#define GCSUTIL_DEBUG_TRACE(args)  LOG_PRINT_DEBUG args;
#else
#define GCSUTIL_DEBUG_TRACE(args)        GCSUTILTRACE(DEBUG ,args)
#endif



#ifdef LOGGER_IMR
#define GCSUTIL_ERROR_TRACE(args)  LOG_PRINT_CRITICAL args;
#else
#define GCSUTIL_ERROR_TRACE(args)        GCSUTILTRACE(ERROR ,args)
#endif



#ifdef LOGGER_IMR
#define GCSUTIL_WARNING_TRACE(args)   LOG_PRINT_MAJOR args;
#else
#define GCSUTIL_WARNING_TRACE(args)      GCSUTILTRACE(WARNING,args)
#endif


void print_time (char *message,...)
{
 struct timeval tv;
 struct tm* ptm;
 char time_string[50];
 long milliseconds;
 va_list ap;

 /* Obtain the time of day, and convert it to a tm struct. */
 gettimeofday (&tv, NULL);
 ptm = localtime (&tv.tv_sec);
 /* Format the date and time, down to a single second. */
 strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
 /* Compute milliseconds from microseconds. */
 milliseconds = tv.tv_usec / 1000;
// milliseconds = tv.tv_usec ;
 /* Print the formatted time, in seconds, followed by a decimal point
   and the milliseconds. */
 printf ("%s.%03ld\t\t", time_string, milliseconds);
 //strcat(time_string,":");
 //strcat(time_string,milliseconds);
 //printf ("%s\n",time_string);
      va_start(ap,message);
      vprintf(message, ap);
      va_end(ap);
 printf("\n");

}

void *UNIX_Recv (void *);
void *Client (void *);
void *UNIX_Server (void *);
void *TCP_Server (void *);
int TCPRECV_Server ();
void *Tcp_Client (void *args);
int UDP_Function ();
int message_processing(int tableId,int msgtype);
void SocketOption(int fd);
void GetSocketOption(int fd);
void SetKeepAliveOption(int fd);
void termination_handler(int signum);
int MUTEX_CreateMutex(pthread_mutex_t *m);
int MUTEX_AcquireMutex(pthread_mutex_t *m);
int MUTEX_ReleaseMutex(pthread_mutex_t *m);
void MessageRetFromLockque();
void print_tid(DSM_Message *msg);
void MessageClearFromLockque();
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
char *strsignal(int sig);
void MessageRetFromLockque_Sync();
void setLockAckFlagOFF(int Table_Id);
void setLockAckFlagON(int Table_Id);
void processLockAck(int Table_Id);
void retrieveUnlock(int Table_Id);
void updateLockAckFlagON(int tableId,int opt);
void processUnlockOnTCPbreak(int tableId);
void StoreLockUnlock(int tableId,char *bufUnixRecv,int len ,int LockUnlockFlag);
void RetriveUnlock_ONSyncUnlock(int Table_Id);
void MessageRetrieve_ON_SYNC_TCP_break();
void ResetAllFlags_OnUnixBreak();
void SendNetworkChangeLeaveMsg();
