#include <time.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/times.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>


#include <its.h>
#include <its++.h>
#include <its_callback.h>
#include <its_assertion.h>
#include <engine++.h>
#include<mtp3_sn.h>
#include<mtp2_cmn.h>
#include <isup_variants.h>
//#include <its_sctp.h>
#include <engine.h>
//#include <sctp_msgs.h>
#include <its_route_rwlock.h>
#include <stdarg.h>
//#include "trace.h"

#if defined(ITS_NAMESPACE)
using namespace its;
using namespace engine;
#endif

#if defined (ANSI)
#define ITS_MTP2_SRC   ITS_MTP2_ANSI_SRC
#elif defined (CCITT)
#define ITS_MTP2_SRC ITS_MTP2_CCITT_SRC
#endif


#if defined (ANSI)
#define ITS_TCAP_SRC   ITS_TCAP_ANSI_SRC
#elif defined (CCITT)
#define ITS_TCAP_SRC ITS_TCAP_CCITT_SRC
#endif


#if defined (ANSI)
#define ITS_ISUP_SRC  ITS_ISUP_ANSI_SRC
#elif defined (CCITT)
#define ITS_ISUP_SRC ITS_ISUP_CCITT_SRC
#endif

#if defined (ANSI)
#define ITS_MTP2_SRC   ITS_MTP2_ANSI_SRC
#elif defined (CCITT)
 #define ITS_MTP2_SRC ITS_MTP2_CCITT_SRC
#endif

#define SOCK_POLL_ERROR      0x10
#define  SOCK_POLL_ERROR_OOB 0x20
#define BUF_SIZE 128

#define NEED_SOCKS 3
#define MAX_CON    10
#define MAX_FD     10
#define ITS_BSSAP_SRC (0xFFE1U)
#define MAX_DPC  0x60 
#define MAX_SSN  0x06
#define ISIL_TRACE_DEBUG        0x01
#define ISIL_TRACE_ERROR        0x02
#define ISIL_TRACE_WARNING      0x03

#define ISIL_USRDATA     0x21
#define ISIL_MTP3RESUME  0x23
#define ISIL_MTP3PAUSE   0x22 
#define ISIL_MTP3STATUS  0x24 
#define ISIL_USERRESUME  0x36
#define ISIL_USERPAUSE   0x35 
#define ISIL_USERSTATUS  0x37
#define ISIL_PCSTATE_IND 0xb6
//#define ISIL_PCSTATE_RESP
#define ISIL_NSTATE_IND  0xb5
#define ISIL_NSTATE_REQ  0xb7
#define ISIL_SSA         0x01
#define ISIL_SSP         0x02
#define ISIL_SSC         0xf2
//#define ISIL_TCAP_ID1
#define ISIL_TCAP_ID2    0xa7
#define ISIL_MAPUSREG_ID 0xa6  
#define ISIL_ISUP_ID1    0x34
#define ISIL_ISUP_ID2    0x1b
#define ISIL_ISUPREG_ID  0x1a 
//#define ISIL_BSSAP_ID1
#define ISIL_BSSAP_ID2   0xc1
#define ISIL_VERSION1    0x01
#define ISIL_VERSION2    0x02
#define ISIL_VERSION3    0x03
#define ISIL_NOELEM1     0x01
#define ISIL_NOELEM2     0x02
#define ISIL_NOELEM3     0x03
#define ISIL_NOELEM4     0x04
#define ISIL_SPACC       0x03
#define ISIL_CONG        0x02
#define ISIL_SPINACC     0x01
#define ISIL_SSN_CAP1   0xf1
#define ISIL_SSN_CAP2   0xf2
//#define FIX_ENTRY 

#define SCM_REGMSG       0x26U
#define SCM_APPID        0xA0U


#ifdef MTP2SIM
 extern "C"
 {
   extern unsigned int  remote_port[16];
   extern unsigned int  local_port[16];
   extern char remoteIpAddr[16][16];
   extern char localIpAddr[16];
 }
 #endif

extern "C"
{
   int ISILPro_Mtp3IsupManageMsg(ITS_EVENT*);
   int ISILPro_Mtp3Msg(ITS_EVENT* );
 int ISILPro_SccpTcapManageMsg(ITS_EVENT*);
 int ISILPro_Mtp3TcapManageMsg(ITS_EVENT* );
 int  ISILPro_SccpMsg(ITS_EVENT* );
 int TRACE_ON(ITS_EVENT );
 int ISILPro_IsupMsg(ITS_EVENT *);
 int ISILPro_MMMsg(ITS_EVENT *);
 int ISILPro_TcapMsg(ITS_EVENT *);
 int
 Get_SSN(ITS_USHORT ,ITS_USHORT ,ITS_OCTET *,ITS_OCTET );
 extern void
 ISIL_Console_CCITT(DBC_Server *dbc, const char *cmdLine);
// ITS_OCTET dpc;
// ITS_OCTET opc;
 ITS_USHORT gtt_opc;
 ITS_OCTET gtt_ni;
}

extern "C"
{
int InitClientMtp3();
int InitClientIsup();
void* Receive(void* );
int InitClientSccp();
int InitClientMM();
int InitClientTcap();


THREAD_RET_TYPE ReceiveEventFromStack(void *);
int ReadEvent(ITS_SocketInfo*, ITS_EVENT*);
int IMRSOCK_Poll(ITS_SockPollInfo* , int ,int );
void *Client(void * );
void *SEND(void * );
void *Server(void * );
void *Receive(void * );
int ProcessMsg(ITS_EVENT*);
extern  int CL_WriteEventTcap(ITS_HANDLE , ITS_EVENT*);
extern  int CL_WriteEventIsup(ITS_HANDLE, ITS_EVENT*);
extern   int CL_WriteEventMM(ITS_HANDLE , ITS_EVENT*);

void  add_connection(ITS_SocketInfo *connect);
void  close_connection(ITS_SocketInfo *connect);

void
IMRSCCPMgmt(ITS_POINTER , ITS_POINTER , ITS_POINTER );
void
IMRMTP3ISUPMgmt(ITS_POINTER , ITS_POINTER , ITS_POINTER );
void
IMRMTP3TCAPMgmt(ITS_POINTER , ITS_POINTER , ITS_POINTER );
void
IMR_GTT(ITS_POINTER , ITS_POINTER , ITS_POINTER );
extern int  ISILPro_SCMMsg(ITS_EVENT *ev);

char hostIpAddress[15];
int   isupClientPort;
int   mmClientPort;
int   tcapClientPort;
int   ServerPort;
int   isupServerPort;
int   mmServerPort;
int   tcapServerPort;
char CpIpAddress[15];
char PpIpAddress[15];
ITS_BOOLEAN cntr=0;


TQUEUETRAN_Manager *recvQ;
ITS_MUTEX CON_WriteMutexLock;
ITS_OCTET ssn[7]={0,0,0,0,0,0,0};
ITS_OCTET counter=0;
int MMFLAG=0;
int ISUPFLAG=0;
int TCAPFLAG=0;
char USRREGISTER_FLAG=0;
extern ITS_HANDLE CL_Handle_ISUP=0;
extern ITS_HANDLE CL_Handle_MM=0;
extern ITS_HANDLE CL_Handle_TCAP=0;
ITS_HANDLE CL_Handle_SCM=0;
extern ITS_MUTEX CL_WriteMutexLock;
extern ITS_MUTEX CL_ReadMutexLock;

#define MAX_DPC  0x60
#define MAX_SSN  0x06
#define GTT_VALUE 0x10
#define IMR_IGACII  0x30
#define GTI_SHIFT  0x02
ITS_OCTET NEW_TABLE=0;
ITS_OCTET ENDNEW_TABLE=0;
ITS_OCTET LASTDPCSSN_ENTRYEND=0;
ITS_OCTET LASTDPC_ENTRYEND=0;
ITS_OCTET LASTSSN_ENTRYEND=0;
ITS_USHORT cdp_dpc=0;
ITS_USHORT clp_opc=0;
ITS_USHORT mtp3_dpc=0;
ITS_USHORT mtp3_opc=0;


static ITS_THREAD thread;
static ITS_THREAD *IFThread;
static int numThreads = 1;
static ITS_UINT bssapIfInstance;
//static  SCTP_Manager imrSocketManager;
static   ITS_SocketInfo *Sock;
ITS_OCTET RESUME_SSN[MAX_SSN]={6,7,8,9,241,242};
ITS_OCTET CHECKISUP_RESUME=0;
ITS_OCTET CHECKMM_RESUME=0;
ITS_OCTET CHECKTCAP_RESUME=0;
ITS_OCTET NI_RES=0;
ITS_OCTET dpcCount=0;

void  ISIL_TRACE(int trace ,const char *ftstring, ...);

void   ISIL_TRACE(int trace ,const char *ftstring, ...)
  {
        va_list args;
        va_start(args,ftstring);
        time_t now;
        struct tm *now_time, tbuf;
        char temptime[80];
        char outString[1024];
        char temp[20];

        time(&now);
        now_time=localtime_r(&now,&tbuf);
        strftime(temptime,80, "[%b%d %Y %H:%M:%S]: ", &tbuf);                                       /* [MMMDD YY, H
H:MM:SS\0]  */
        sprintf(outString, "%s", temptime);


        if (trace==ISIL_TRACE_DEBUG)
         {
            strcpy(temp,"ISIL\t:Debug\t:\n");
         }
        if (trace==ISIL_TRACE_ERROR)
         {
            strcpy(temp,"ISIL\t:Error\t:\n");

         }
        if (trace==ISIL_TRACE_WARNING)
         {
            strcpy(temp,"ISIL\t:Warning\t:\n");
         }
         strcat(outString,temp);
         strcat(outString,ftstring);
         vprintf(outString,args);

      va_end(args);
}


#define ISIL_MAX_LINKSET 256
#define ISIL_MAX_LINK    16
#define ISIL_INTERNODE_BT  20002/*samevalue is using at its_ss7_route.c :line 6166*/
typedef enum
{
 ISIL_STATE_PRIMARY=0,
 ISIL_STATE_BACKUP
}
ISIL_NODE_STATE;

typedef struct
{
ISIL_NODE_STATE state;
}
ISIL_STATE;


ITSDLLAPI extern CALLBACK_Manager   *HMI_Health_Callbacks ;
/*************************************************************
Changes due to VNL PLATFORM
*************************************************************/

typedef enum
{
PLATFORM_ACT_NOTIF_EVENT=0xCA,
PLATFORM_BKUP_NOTIF_EVENT = 0xCB
}
DSM_MembershipChangeType_tmp;


typedef struct
{
    ITS_USHORT ftGroupId;
    DSM_MembershipChangeType_tmp  membershipChangeType;
    ITS_USHORT memberNodeId;
    ITS_USHORT memberProcessId;
    ITS_USHORT numFtGroupMembers;               /* Valid for join and leave. */
    const DSM_FtGroupMember* ftGroupMembers;    /* Valid for join and leave. */
} DSM_MembershipChangeCbData_temp;



}/*end of extern*/
