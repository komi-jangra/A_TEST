
#ifndef __BS_HASHFUNCH__
#define __BS_HASHFUNCH__ 

#include "cm_hash.h"
#include "cm_hash.x"
#include "lbs.x"

#define FAILURE -1
#define MAX_MESSAGE_SIZE 14000
#define BS_HASHTABLE_NUM 2

/* DSM error code */
#define ITS_SUCCESS           0

/* opcode */
#define INSERT 1
#define DELETE 2 
#define UPDATE 3
#define SEARCH 4


/*Response type */
#define POSTIVE_ACK 1
#define NEGATIVE_ACK 2

/* Mutex type defines*/
#define SYNC_MUTEX  1
#define THREAD_MUTEX 2

/*Token*/
#define SYNC_LOCK 10
#define SYNC_UNLOCK 20

#define HA_CARDSTATE_INIT 70
#define HA_CARDSTATE_PLATFORM_INS 71
#define HA_CARDSTATE_IN_SERVICE 72
#define HA_CARDSTATE_ACTIVE 73
#define HA_CARDSTATE_STANDBY 74
#define HA_CARDSTATE_OUT_OF_SERVICE 75
#define HA_CARDSTATE_RECOVERY 76
#define HA_CARDSTATE_FAIL 77
#define HA_CARDSTATE_TEST 78
#define HA_CARDSTATE_ABSENT 79

#define PRINT_OPCODE(x) ((x==INSERT)?"INSERT":\
                        ((x==DELETE)?"DELETE":\
			((x==UPDATE)?"UPDATE":\
			((x==SEARCH)?"SEARCH":\
			"UNKNOWN"))))

#define PRINT_CARDSTATE(x) ((x==HA_CARDSTATE_INIT)?"HA_CARDSTATE_INIT":\
                        ((x==HA_CARDSTATE_PLATFORM_INS)?"HA_CARDSTATE_PLATFORM_INS":\
                        ((x==HA_CARDSTATE_IN_SERVICE)?"HA_CARDSTATE_IN_SERVICE":\
                        ((x==HA_CARDSTATE_ACTIVE)?"HA_CARDSTATE_ACTIVE":\
                        ((x==HA_CARDSTATE_STANDBY)?"HA_CARDSTATE_STANDBY":\
                        ((x==HA_CARDSTATE_OUT_OF_SERVICE)?"HA_CARDSTATE_OUT_OF_SERVICE":\
                        ((x==HA_CARDSTATE_RECOVERY)?"HA_CARDSTATE_RECOVERY":\
                        ((x==HA_CARDSTATE_FAIL)?"HA_CARDSTATE_FAIL":\
                        ((x==HA_CARDSTATE_TEST)?"HA_CARDSTATE_TEST":\
                        ((x==HA_CARDSTATE_ABSENT)?"HA_CARDSTATE_ABSENT":\
			"UNKNOWN"))))))))))

#define PRINT_TOKEN(x) ((x==SYNC_LOCK)?"SYNC_LOCK":\
                        ((x==SYNC_UNLOCK)?"SYNC_UNLOCK":\
			"UNKNOWN"))

/*
 * Pre-claimed tables.
 */
#define BSHASH_TABLE_CALLREF_CTXT   1 
#define BSHASH_TABLE_CALLID_CTXT    2            
#define BSHASH_TABLE_INTF           3           

/* Structure defination */

struct hashEntry
{ 
  CmHashListEnt hl;
  unsigned char* key;
  unsigned int keylen;
  unsigned int tableId;
  int intfId;
  int datalen;
  void *data;
};
typedef struct hashEntry HashEntry;

#define BSSMAP_CALLDB_UPDATE 0x01
#define BSSMAP_CALLIDDB_UPDATE 0x02
#define BSSMAP_INTFDB_UPDATE 0x03

typedef struct _updCalldb
{
    U32 intfId;
    U32 suInstId;
    U32 spInstId;
    U16 cic;
    U8 timerId;
    U32 callId;
    U32 appId;
    U8 msgType;
    U8 callType;
    U8 handoverFlagSet;
    U8 hofaicause;
    Bool channelAlloc;
}
BsUpdCallDb;
typedef struct _intfdb
{
  U32  intfId;
  U8   bscId;          /* bsc Id                   */
  U8   ni;          /* Sub service field             */
  U16  opc;           /* physical originating point code          */
  U16  phyDpc;        /* physical destination point code          */
  S16  swtch;         /* Protocol Switch                          */
  TmrCfg   t1;
  TmrCfg   t4;
  TmrCfg   t10;
  TmrCfg   t11;
  TmrCfg   t13;
  TmrCfg   t17;
  TmrCfg   t18;
  TmrCfg   t25;
  TmrCfg   trbsc;
  U8   resetRetryCount;
  U8   resetIPRetryCount;
  U8   rstRcvtimerId;
  U8   rstSndtimerId;
  U8   PcSsnStatusInd;
  U8   overloadT17;
  U8   overloadT18;
  U8   Fistoverld;
  U8   TrbsctimerId;
  U8   Data[100];
  S16  len ;
}
BsUpdIntfDb;

typedef struct _updmsg /* General Configuration */
{
  U8 msgType;
  union
  {
    BsUpdCallDb Calldb;
    BsUpdIntfDb intfdb;
  }u;
}
UPDMsg;

typedef struct _callIdDb
{
   U32 callId;
   U32 callRefId;
}
CallIdCb;

typedef int (*BS_HASH_IterateEntryProc)(char* data, void* in, void* out);

int HashListTbInsert(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen,
		     void *dataptr,
		     int datalen);
int HashListTbDelete(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen);
int HashListTbUpdate(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen,
		     void *dataptr);
int HashListTbSearch(CmHashListCp *hashListCp,
                     unsigned int tableId,
                     unsigned char* key,
		     int keylen,
		     HashEntry **entry);
void print_buf(unsigned char *bufprt,int buflen);
void BsHashInitialize(void);
void BsHashInvoke(int haState);
void BsHashInitHashList(int intfId);
void BsHashDeInitHashList(int intfId);

#endif /* __MAINH__ */
