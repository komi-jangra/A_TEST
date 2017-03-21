#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <assert.h>
#include <sys/sem.h>


#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_syslog.h>
/*#include <ipcfrm_extern.h> */


SysAddr slfAddr;
#define SCM_CRITICAL     CRITICAL
#define SCM_MAJOR        MAJOR
#define SCM_DEBUG        DEBUG
#define SCM_INFO         INFO
#endif
/*scm specific header file from system level header file*/
/* sys Inc files */
#include <sysxxx_alarmmodule.h>
#include <sysxxx_msgopcode.h>
#include <syscmn_hashdefs.h>
#include <sysxxx_alarm.h>
/* end */

/* oam Inc files */
#include <oamxxx_alarmtypedefs.h>
#include <oamxxx_errorcode.h>
/* end */

/* scm Inc files */
#include <scm_msgdef.h>
#include <scm_hashdefs.h>
#include <scm_preconfig_msgdef.h>
/* end */


/* nwstack specific Inc files */
#include <../../../Inc/nwstkscm_hashdefs.h>
#include <../../../Inc/nwstkscm_msgdef.h>
#include <../../DBUTIL/Inc/sksdb_extern.h> 
/* end */


/*AOIP: DB  HEADER*/

#include <dbsxxx_commondefs.h>

/*AOIP END*/

/*AOIP Start*/
#include <../../../Inc/sigtran_scmhashdef.h>
/*AOIP End*/


#ifdef PLATFORM_IMR
#include <bpmxxx_commonDef.h>
#include <bpmxxx_OAM_commonDef.h>
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
void scmBpmAisCallbackFunc(struct sAisParam* param);
#endif


/* msgtype which are not defined in system 
  level header file and use for initial config only*/
#define OAM_SCM_MAP_INIT_CONFIG               (BASE_OPCODE_SCM + 243)
#define OAM_SCM_TCAP_INIT_CONFIG              (BASE_OPCODE_SCM + 244)
#define OAM_SCM_ISUP_INIT_CONFIG              (BASE_OPCODE_SCM + 245)
#define OAM_SCM_ISUP_ALARM_LEVEL_MODIFY       (BASE_OPCODE_SCM + 246)
#define OAM_SCM_ISUP_GEN_CONFIG               (BASE_OPCODE_SCM + 247)
#define OAM_SCM_MAP_ALARM_LEVEL_MODIFY        (BASE_OPCODE_SCM + 248)
#define OAM_SCM_TCAP_ALARM_LEVEL_MODIFY       (BASE_OPCODE_SCM + 249)
#define OAM_SCM_CAP_ALARM_LEVEL_MODIFY        (BASE_OPCODE_SCM + 250)
#define OAM_SCM_MTP3_GEN_CFG                  (BASE_OPCODE_SCM + 0x31U)
#define OAM_SCM_BSSAP_GEN_CFG                 (BASE_OPCODE_SCM + 0x32U)
#define OAM_SCM_SCCP_GEN_CFG                  (BASE_OPCODE_SCM + 0x33U)
#define OAM_SCM_SCCP_BEHAVIOR_CONFIG          (BASE_OPCODE_SCM + 0x65U)    
#define OAM_SCM_LSSN_CONFIG                   (BASE_OPCODE_SCM + 0x66U)
#define OAM_SCM_RSSN_CONFIG                   (BASE_OPCODE_SCM + 0x67U)
#define OAM_SCM_CSSN_CONFIG                   (BASE_OPCODE_SCM +0x68U)
#define OAM_SCM_TCAP_TRACE_LEVEL_MODIFY       (BASE_OPCODE_SCM + 0x70U)

/*#define OAM_SCM_MAP_SEC_CONFIG                (BASE_OPCODE_SCM + 0x71U)*/
#define OAM_SCM_MAP_TIMER_CONFIG              (BASE_OPCODE_SCM + 0x72U)
#define OAM_SCM_TCAP_PEG_GET                  (BASE_OPCODE_SCM + 0x73U)
#define OAM_SCM_MAP_SEC_CONFIG                (BASE_OPCODE_SCM + 0x74U)

/*AOIP OPCODES PRE CONFIGURATION*/
#define OAM_SCM_SCCP_INIT_CONFIG              (BASE_OPCODE_SCM + 0xA0U)
#define OAM_SCM_SCTP_INIT_CONFIG              (BASE_OPCODE_SCM + 0xA1U)
#define OAM_SCM_M3UA_INIT_CONFIG              (BASE_OPCODE_SCM + 0xA2U)
/*AOIP END*/

/* end here */

#ifdef LOGGER_IMR
       extern char *str;
       extern int sv,iv;
       extern char new_str[1000];
       #define SCM_printf(A,STR,args...)       \
               LOG_PRINT (A,STR, ##args);
               
              /* str = STR;                      \
               new_str[sv] = ' ';              \
               sv = 1;                         \
               for (iv=0;iv<strlen(STR);iv++)  \
               {                               \
                    if (str[iv]!='\n' &&       \
                        str[iv]!='\t')         \
                    {                          \
                        new_str[sv] = str[iv]; \
                        sv = sv + 1;           \
                    }                          \
               }                               \
               new_str[sv] = '\0';             \
               LOG_PRINT (A,new_str, ##args);*/
#else
        void SCM_printf(int, const char *, ...);
#endif
#define CREATE_QUEUE(A,C)   \
                       if((A = msgget((key_t)C,0777|IPC_CREAT)) == -1)   \
                       {                                                 \
                            perror("msgget");                            \
                            SCM_printf(SCM_INFO,"TROUBLE IN CREATING MESSAGE QUEUE"); \
                       }    \
                       else \
                       {    \
                            msgctl(A, IPC_RMID, NULL);                       \
                            if((A = msgget((key_t)C,0777|IPC_CREAT)) == -1)  \
                            {                                                \
                                perror("msgget");                            \
                                SCM_printf(SCM_INFO,"TROUBLE IN CREATING MESSAGE QUEUE"); \
                            }                                                \
                            else                                             \
                                SCM_printf(SCM_INFO,"QUEUE ID ALLOCATED : %d\n", A);      \
                       }


typedef unsigned int   U32;
typedef unsigned short  U16;
typedef unsigned char   U8;
//typedef signed int long     SL32;
typedef signed int     S32;
typedef signed short    S16;
typedef signed char     S8;
struct sembuf sem_signal;

typedef struct
        {
         U32 transaction_Id;
         U16 pegrfu; 
         U8 operation;
        }transaction_id;   
/*struct format to put message in sock event queue*/
typedef struct
        {
         U8 entity_id;/* entiy id which comes up*/
         U8 config_req;/* if configuration required or not flag */
        }msg_queue_buff;
/* struct format to store link information while configuration */
typedef struct
        {
         U8   admin_state;
         U8   card_flag;
         U16   link_value;
         U16   linkSetId;
         U32  instaceId; 
         OamScmLinkAdminState scmLinkAdminState; 
        }gvar_link;  


struct link_info
       {
        struct link_info *nxt;
        U16   link_value;
        U16   linkSetId;
        U32  instaceId;
        U8   adminState; 
        OamScmLinkAdminState scmLinkAdminState;
       };
typedef struct link_info link_information;
typedef link_information LinkHashTable;

/* struct format to store linkset information while configuration */

struct linkset_info
       {
        struct linkset_info *nxt;
        U16   linkSetId;
        U8   adminState; 
       };
typedef struct linkset_info linkset_information;
typedef linkset_information LinksetHashTable;

/* message queue struct to write & read from queue*/
typedef struct
         {
          long  mtype;   
          U8 mtext[40];
       }msgbuf;


typedef struct
            {
            U8  api_Id;
            U8  operation;
            U16 opcode;
            U32 tr_Id;
            U8  timer_strt_flag;
            U8  db_oam_stamp;
            U8  no_of_resp;/* store the value no. of cmd resp required for
                            cmd sent to stk*/
            U8 no_of_resp_flag;
            U8 resp_from_peer_cardFlag;/* waiting response flag for response from peer card */
            U8  rollback_flag;/*flag to store rollback operation indication*/
            U8  resp_flag;/*flag to store if any of multiresp is nack*/
            U8  entity; /*this will be used after timer expired */
            U32 resp_error_id;/*to store error_id if multiresp or single resp cmd nack*/
            }timer_exp_ele;/*for timer expiry handling*/

typedef struct
           {
            U8 nwstk_roll_back_flag;
            U8 lapd_roll_back_flag;
            U8 maptcap_roll_back_flag;
            U8 multi_cmd_roll_back_flag;
           }roll_back_flag;

typedef struct 
           {
             U8  config_flag;   /* flag for stack getting config*/
             U8  entity_cfg;    /* entity which is getting config*/
             U8  card_Id;       /*card_Id value stored which is 
                                 derived from platform api*/
             U8  family;        /* family value stored from msc config msg*/
             U8  alarm_level;     /* opc value stored from msc config msg*/
             U8  no_of_config_row_sent;/* this is the count for no. of row sent*/
             U8  isSatellite;     /*to store issatellite flag from 
                                   isup init table*/
             U8  entity_up;       /* flag to store no. of time any entity 
                                     goes down and comes up again*/
             U8  self_nwstk_up;
             U8  peer_nwstk_up;     /* flag to take of peer nwstk state up or down*/
             U8  scm_process_flag; /*this flag will take care of signalling 
                                     semaphore */
             U8  link_config_flag;
             U8  nwstk_cfg_wait; /* flag to wait for configuration while lapd not config*/
             U8  no_of_retry_nwstk_cfg_wait; /*retry count to wait for configuration while lapd not config*/
             U8  nwstk_cfgIndFromPeerCard; 
             U8  nwstk_cfgComplete; 
             U8  noOam_resp_flag;
             U8  link_activated_flag; /* this flag take care of if any of link activated for nwstk*/
             U8  linkset_activated_flag; /* this flag take care of if any of linkset activated for nwstk*/
             U8  *lapd_msg;
             U8  peer_lapd_cmdFlag;
             U8  lapd_standby_respFlag;   
             U8  lapd_cfgComplete;   
             U8  peer_link_del;
             U8  peer_link_del_resp;
             U8  *nwstk_msg; 
             U8  *map_tcap_msg;
             U8  peer_map_tcap_cmdFlag;
             U8  *multicmd_msg; 
             U8  peer_nwstk_cmdFlag;
             U8  peer_multi_cmdFlag;
             U8  nwstk_standby_respFlag;   
             U8  maptcap_standby_respFlag;   
             U8  multicmd_standby_respFlag;   
             U8  timer_Id[4];
             U8  slot_id;
             U8  redundant_status;
             U8  g_card_state; /* to handle alarm in AIP state */
             U8  nwstk_stsUp_sent;
             U8  oam_up;/*flag to take care if oam up more then once*/
             U8  ss7_up_alarm;/*this flag will take care if 
                                ss7 up alarm sent to oam or not*/
             U8  linkset_admingSts; /* this is used storage of linkadmin state
                                      during config transient*/
             U16 config_cmd_resp; /* flag for config cmd waiting response*/
             U16 no_config_cmd_sent; /* no_of command sent to entity 
                                       getting config*/
             U16 no_command_resp_success; /* no config command responded 
                                           succesfully use to declair 
                                           entity configured*/
             U16 propDelay;       /*to store propdelay from isup init table*/
             U16 linksetId;       /*to store linksetId of currently configured link*/
             U32 opc_value;     /* opc value stored from msc config msg*/
             U32 semID;     /* opc value stored from msc config msg*/
             S32 soc_event_q_Id;/* to store sock event q_id*/
             S32 timer_event_q_Id;/* to store timer event q_id*/
             S32 scm_server;    /*to store as scm self server fd*/
             U8  sigtran_cfgComplete;/*AOIP FLAG*/ 
             U8  bssap_cfgComplete;  /*AOIP FLAG*/
             U8  self_stack_up;    /*AOIP HA FLAG*/
             U8  peer_stack_up;   /*AOIP HA FLAG*/
             U8  data_pull_up;   /*AOIP HA FLAG*/
             U8  data_pull_admin_send;   /*AOIP HA FLAG*/
             U8  Conn_Down_alarm_Resp_Pending; /*MANTIS Id :- 0032193*/
             U8  scm_scm_up;            /*MANTIS ID:- 0032492*/
             U8  stby_bssap_config_wait;   /*MANTIS ID:- 0032492*/
             U8  stby_sigtran_config_wait; /*MANTIS ID:-0032492*/
             char  function_string[100]; 
             
          }scm_global_parameter;



 union semnum
        {
              int val;
              struct semid_ds  *buffer;
              unsigned  short  *array;
        } semvalue;



typedef struct
             {
              U8 prv_family;        /* family value stored from msc config msg*/
              U8 prv_opc_value;     /* opc value stored from msc config msg*/
              U8 prv_alarm_level;     /* opc value stored from msc config msg*/
              U8 db_oam_stamp;   /* stamp for db or oam */
              U8 no_of_res;      /* expected no. of responses */
              U8 resp_flag;      /* flag for waiting ack if zero discard resp */
              U8 lock_flag;      /* for lock mechanism */
              U8 api_id;
              U16 msg_type;       /* msg type at array possition */
              U8 *stored_msg;    /* stored message for roll back */ 
              U8 no_of_command_sent; /* store the value of no. of command sent*/
              U8 no_of_command_responded;/*to store no. of command in 
                                           multi cmds are responded */
              U8 roll_back_flag; /* set roll back flag if rollback required 
                                    & this is also the indication that ignore 
                                    the responses in case of roll back*/
             }multiple_cmd_handle;

/* command specific structures which are not stored in header files */
typedef struct 
             {
             ScmHdr     scmhdr;  
             U8   status;
             }peerNwstkSts;

typedef struct 
             {
             ScmHdr     scmhdr;  
             U32  error_flag;
             U8   alarm_level;
             }sMapAlarmConfigTableApi;

typedef struct
             {
             ScmHdr     scmhdr;
             U32  trace_flag;
             U8   trace_level;
             }sMapTraceConfigTableApi;

typedef struct 
             {
               ScmHdr     scmhdr;
               U32   error_flag;
               U8    alarm_level;
            }sIsupAlarmConfigTableApi;

typedef struct 
           {
           ScmHdr     scmhdr;
           U32   trace_flag;
           U8    trace_level;
          }sIsupTraceConfigTableApi;

typedef struct {
                U32   pointCode;
                U32   startCic;
                U32   endCic;
                U32   noOfCic;
                } isup_global_data;

extern isup_global_data g_isup_parameter;


/*end here */




/*extern parameter structure declaration*/
extern link_information *link_node;
extern LinkHashTable    *linkHashTbl[9]; 
extern LinksetHashTable    *linksetHashTbl[9]; 
extern gvar_link        g_linkConfigValue;
extern scm_global_parameter g_parameter;
extern roll_back_flag       g_roll_back_flag; 
extern multiple_cmd_handle multi_cmd[3];
extern fd_set scm_server_fd;
extern fd_set client_fd;
extern fd_set server_fds;
extern timer_exp_ele timer_info[10];
extern transaction_id oam_transaction_Id[256];/*this array is to store oam tr_Id + operation code*/
 extern S8                  *xxx_scm_ip[10];
 extern U32                 xxx_scm_port[10];
 extern S32                 xxx_client_sockfd[9];
 extern S32                 xxx_severread_sockfd[10];
 sigset_t            mask;
 struct timespec nano_sleep, rmndrtime;
 extern U8 transaction_Id[256];/*this array is to store scm tr_Id*/
 extern timer_t os_timer_id[10];

/*AOIP: Reconf CMD flag*/
extern U32 Reconf_Flag;
/*AOIP: End*/



/*stack related structures which are not in header file */

typedef struct 
{
  ScmHdr     scmhdr;
  U8    sksGenCfgalarmLevel;
  U8    sksGenCfgTraceLevel;
  U8    sksGenCfgtraceOutput;
  U8    sksGenCfgtraceOnOff;
}scmSksGenConfig;




typedef struct
{
 ScmHdr     scmhdr;
 U16    sccpConfiglssn;
 U32    sccpConfigpc;
 U16    sccpConfigni;
}OamScmSccpLssnConfig;/*same structure is used for both add/del cmd*/

typedef struct
{
 ScmHdr     scmhdr;
 U16    sccpConfigrssn;
 U32    sccpConfigpc;
 U16    sccpConfigni;
}OamScmSccpRssnConfig;/*same structure is used for both add/del cmd*/


typedef struct
{
 ScmHdr     scmhdr;
 U16    sccpConfigssn;
 U32    sccpConfigpc;
 U16    sccpConfigni;
 U16    sccpConfigcssn;
 U32    sccpConfigcpc;
}OamScmSccpCssnConfig;/*same structure is used for both add/del cmd*/

/*lapd stack structs */


typedef struct
{
  U8     appId;
  U8     len;
} lapd_header_t;

/******** Group Id : LAPD_SCM_ALARM_MSG ********/

/* LAPD ---> SCM */

/* Msg Type : LAPD_SCM_ALARM_IND */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     alarmId;
  U8     alarmLevel;
} lapdScmAlrmInd_t;

/******** Group Id : LAPD_SCM_CFG_MSG ********/

/* SCM ---> LAPD */

/* Msg Type : LAPD_SCM_CFG_TS */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     timeSlot;
} ScmLapdTSConfig;
#ifdef LAPD_HA
typedef struct
{
  U8     msgGrpId;
} ScmLapdConfigComplete;

#endif
/* Msg Type : LAPD_SCM_CFG_TEI */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     timeSlot;
  U8     lapdTei;
  U8     appTei;
} ScmLapdTeiConfig;


/* Msg Type : LAPD_SCM_CFG_SAPI */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     timeSlot;
  U8     sapi;
} ScmLapdSapiConfig;


/* LAPD ---> SCM */

/* Msg Type : Request Message Type */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     value;
} lapdScmCfgResp_t;


/******** Group Id : LAPD_SCM_PEGS_MSG ********/

/* SCM ---> LAPD */

/* Msg Type : LAPD_SCM_PEGS_SHOW */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U32      count;             /*Range 1..5 */
  U8       appTeiInfo[5];
  U8       pegResetFlag;

} ScmLapdPegsShow_t;


/* LAPD ---> SCM */

/* Msg Type : LAPD_SCM_PEGS_SHOW */


typedef struct
{
unsigned char     sapi; /* 0 & 62 */
unsigned char     dummy;
unsigned short    dummy1;
unsigned int    pegLapdInfoSend;
unsigned int    pegLapdInfoRecv;
unsigned int    pegLapdUiSend;
unsigned int    pegLapdUiRecv;
unsigned int    pegLapdRrCSend;
unsigned int    pegLapdRrCRecv;
unsigned int    pegLapdRrRSend;
unsigned int    pegLapdRrRRecv;
unsigned int    pegLapdRejCSend;
unsigned int    pegLapdRejCRecv;
unsigned int    pegLapdRejRSend;
unsigned int    pegLapdRejRRecv;
unsigned int    pegLapdRnrCSend;
unsigned int    pegLapdRnrCRecv;
unsigned int    pegLapdRnrRSend;
unsigned int    pegLapdRnrRRecv;
unsigned int    pegLapdMsgDecodeFail;
unsigned int    pegLapdMsgEncodeFail;
}LapdPegInfo;

typedef struct
{
unsigned char              applTei;
unsigned char              dummy1;
unsigned short             dummy2;
LapdPegInfo pegInfo[2];
}LapdPeg;

typedef struct
{
unsigned int          count;                  /* Range 1..5 */
LapdPeg lapdPeg[5];       /* Max data. 156*5 = 780*/
}LapdPegResponse;



/******** Group Id : LAPD_SCM_TMR_MSG ********/

/* SCM ---> LAPD */

/* Msg Type : LAPD_SCM_TMR_SET */


typedef struct{
U8     msgGrpId;
U8     msgType;
LapdTimerConfig  lapdTimerDefault;
LapdTimerConfig  lapdTimerSatellite;
U32            noOfLapdTs;
LapdTsDetail     lpdTsdetail[80];
}NwstkScmLapdTimerConfig;

/*********************ENDs Satellite Change*************/





/* LAPD ---> SCM */

/* Msg Type : Request Message Type */
typedef struct
{
  U8     msgGrpId;
  U8     msgType;
  U8     value;
} lapdScmTmrResp_t;


/*end here */




/*all function declaration here*/
/*scm init functions*/
void SCM_DUMP (int , int , unsigned char* , int );
void STRING_DUMP(int , int , unsigned char* , int );

int scm_init();
void init_global_variable();
int read_configfile();
void match_string (unsigned char*, unsigned char*, unsigned char*);
void  locate_entity_down();
int process_config_cmd_and_resp();

char* get_entity(int);
int write_in_sock_event_q(int);
void process_message_queue();
void* scm_cm_function (void*);
int setup_scm_server( unsigned short );
int setup_client(unsigned char*, unsigned short);
void sig_act();
signed int send_sync_mesg();/* to be implement */
/*all processing functions are here*/
int  process_config_cmd_and_resp();
/*send cmd functions*/
int process_nw_stack_init_config_cmd (unsigned char*);
int process_nw_stack_init_config_cmd_set2 (U16, U8);
int process_nw_stack_init_config_cmd_set3 (U16, U8);
int process_nw_stack_init_config_cmd_set4 (U16, U8);
int process_roll_back(unsigned char *);
void process_event_on_sockfd( unsigned char* );
int check_entity_configured( unsigned char );
/*all processing functions are here*/
void process_nwstk_resp(unsigned char*, unsigned char*);
void process_alarm_nwstk(unsigned char*);
int process_maptcapstk_resp(unsigned char*, unsigned char*);

/*processing of oam & peer scm message */
int process_oam_message(unsigned char*);
void process_peerscm_message(unsigned char*);
int form_isup_header(unsigned char*, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short);
void Fill_CAP_Header (int , int );
int process_maptcap_stack_cmd (unsigned char*);
int process_isup_stack_cmd (unsigned char*);
int  process_cap_stack_cmd (unsigned char*);
void process_isup_map_tcap_alarm(int,  unsigned char*, int);
int send_isup_update(U8*);

signed int scm_dispatch_buffer(unsigned char*, unsigned char, unsigned short);

void process_multicmd_resp(unsigned char*, unsigned char*);
void send_resp_to_oam(U16, unsigned char, U32, U16, U16 , unsigned char*, unsigned short, U8);
void form_oam_header(U8*, U16, U8, U32, U16 , U16);
void form_scm_header( unsigned char*, U16, unsigned char, U32, unsigned short);
int form_nwstk_header(unsigned char*, unsigned char, unsigned char, unsigned char, unsigned short);
unsigned char get_entity_appid(U16, U8*, U8);
int form_maptcap_header(unsigned char *, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned short);
int set_stack_alarm_reporting_level (unsigned char* );
int process_nw_stack_cmd (unsigned char*);
int process_maptcap_stack_cmd (unsigned char*);
void SCM_DUMP(int , int , unsigned char* , int );
void STRING_DUMP(int , int , unsigned char*, int );
void report_alarm_to_oam (U16, U8, U8);
int literal_present(unsigned char);
void process_isup_map_tcap_alarm(int,  unsigned char*, int);
int fetch_and_send_nxt_cmd_to_stack(unsigned char);
int check_entity_configured( unsigned char);
void* scm_cm_function (void*);
int accept_connction_on_server();
int setup_scm_server( unsigned short);
int scm_read_from_socket (S32 , U8* , U8 , U8* );
int SS7_read(S32 , unsigned char*, unsigned short);
signed int scm_write( unsigned char, U32 , unsigned char*, unsigned short);
int start_timer (U8, unsigned char, U32, unsigned char*);
int stop_timer ( U8 );
void sig_act();
void process_timer_exp_queue();
int get_no_of_resp_required(U8*, U16);
void process_cap_alarm(U8*);
void match_resp_opcode(U16, U16*);
void form_resp_error_code(U32 , U16*, U8);
S32 GetCurTimeStamp(U32*);
U32 check_if_previous_cmd_in_progress(U8 );
void catch_signal(int );
S32 check_entiy_up(U8);
void check_peer_cmd_flag_and_roll_back(U8);
int send_cofigComplete_ind_to_peerScm(U8 );
void set_stackFlag_to_respond_peer_scm(U16);
void process_response_from_peer_scm(U8*); 
int send_config_update_to_peer_scm();
int get_app_id_from_resp_opcode(U16);
int  checkAndUpdate_linkValue_in_linkHashTable(U8, U32, U16, U16, U8*, U8);
void init_hash_table();
int insert_value_in_hash_table(U16, U32, U16, U16);
int delete_value_from_hash_table(U16, U16);
int search_link_from_hash_table(U16, U16, U8*, U8);
void get_key(U16*, U16);
void* scm_malloc( size_t );
void delete_link_hashTbl();
void process_scm_alarm(U16);
void scm_signal();
void scm_wait();
signed int send_stack_enity_up_to_peerscm(U8);

int getAll_linkAdminstate_and_modify_in_peer_nwstack();
int modify_linkadminstate_in_linkHash_table(U16, U16, U8 );
void  process_link_adminStateModiy_cmd_from_peerScm(U8*);
int validate_length_of_messag(U16, U16);
void init_global_config_parm();
int  checkAndUpdate_linksetValue_in_linksetHashTable(U8, U16, U8);
int modify_linksetadminstate_in_linksetHash_table(U16, U16, U8);
void init_linkset_hash_table();
int getAll_linksetAdminstate_and_modify_in_peer_nwstack();
int insert_linksetvalue_in_hash_table(U16,  U16);
int delete_linksetvalue_from_hash_table(U16, U16);
int search_linkset_from_hash_table(U16, U16);
void delete_linkset_hashTbl();
void  process_linkset_adminStateModiy_cmd_from_peerScm(U8* msg_buff);
void free_peer_update_pointer();
void checkNoOfElementToReport(U32 ,U32*, U32*, U32);   
void  CheckIfPegRespFailed(U16*, U16);
void process_lapdstk_response (U8*, U8* );
int process_lapd_stack_cmd (U8*);
void process_Lapd_alarm(unsigned char*);
void handle_ln_del_resp();
int handle_client_connect(int sock, void*);

void scmSigintHandler();
void scmSigquitHandler();
void scmSigstopHandler();
void scmSigsegvHandler();
void scmSigbusHandler();
void scmSigillHandler();
void scmSigfpeHandler();
void scmSigchldHandler();
void scmSiguser1Handler();
void scmSiguser2Handler();
void scmSigtermHandler();
void scmSigpipeHandler();

void scmSigcontHandler();
void scmSigabrtHandler();
void scmSigtrapHandler();
void scmSigtstpHandler();

void scmSigInit();


#ifdef LAPD_HA
void send_lapd_config_complete();
#endif

/*AOIP Db routines Decl*/
I_S32  GetLocalAspAdminStatePtr (SigtranM3uaLAspConfigTableApi  **, U8 *);
I_S32  GetBsIntfTbl(OamScmBsInterfaceConfig **);
I_S32  GetSpInitConfigData(OamScmSccpInitConfig **, U8 *);
I_S32  GetSpConfigData(OamScmSccpSpConfig   **, U8 *);
I_S32  GetSsConfigData(OamScmSccpSsConfig   **, U8 *);
I_S32  GetCssConfigData(OamScmSccpCssConfig **, U8 *);
I_S32  GetSccpCspConfigData(OamScmSccpCspConfig  **, U8 *);
I_S32  GetM3uaInitConfigData (OamScmM3uaInitConfig **, U8 *);
I_S32  GetLocalAspConfigData (OamScmM3uaLocalAspConfig  **, U8 *);
I_S32  GetRemoteAspConfigData(OamScmM3uaRemoteAspConfig  **, U8 *);
I_S32  GetLocalAsConfigData (OamScmM3uaLocalAsConfig **, U8 *);
I_S32  GetRemoteAsConfigData (OamScmM3uaRemoteAsConfig  **, U8 *);
I_S32  GetSctpInitConfigData( OamScmSctpInitConfig **, U8 *);
I_S32  GetSctpConfigData(OamScmSctpConfig **, U8 *);
I_S32  GetSccpTmrConfigData(OamScmSccpTmrConfig **, I_U16 );
I_S32  GetSccpCspToReconfig(OamScmSccpCspConfig  **, U16);
I_S32  GetSctpTimerData( OamScmSctpTimerConfig **);
I_S32  GetM3uaTmrConfigData(OamScmM3uaTimerConfig  **, U16);
/*AOIP End*/

/*AOIP routines*/
I_S32  process_bssap_stack_cmd(U8*); 
U16    Check_Peer_psp_and_Bss_state(U16 *, U16 *, U16 *);
U16    Check_Self_psp_and_Bss_state(U16 *, U16 *, U16 *);
void   process_sigtran_stack_alarm(S32,  U8*, S32);
void process_bssap_stack_resp(U8* msg_buff, U8* nxt_cmd_flg);
const char *get_alarm_string(U16); /*returning strings*/
U16 Check_Self_Admin_and_Opr_state(U16 *, U16 *, U16 *);
/*AOIP_HA end*/


/*#ifdef LOGGER_ON_SCREEN    
#define SCM_printf(a,b,args...) printf(b,##args);        
#endif*/                         
