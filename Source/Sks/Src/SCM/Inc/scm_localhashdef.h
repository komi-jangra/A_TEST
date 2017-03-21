
#define F3    0xff000000
#define F2    0x00ff0000
#define F1    0x0000ff00
#define F0    0x000000ff
/* scm alarms */
#define SS7_UP         104
#define SS7_DOWN       103
#define ISUP_UP        106
#define ISUP_DOWN      105
/*end here */


/* define max opcode on the bases of scm max array size of opcode containing
   varriable */
 #define OPCODEMAX 256
/*end*/

/*nwstk alarm parsing */

 #define  ALARM_DPC_NI_LS	           1
 #define  ALARM_DPC_SSN_NI	         2
 #define  ALARM_LS_LN	               3	                 
 #define  ALARM_DPC_NI	             4
 #define  ALARM_DPC_CIC	             5
 #define  ALARM_DPC_LS_LN           6
 #define  ALARM_PC_SSN	             7
 #define  ALARM_DPC		               8
 #define  ALARM_UP		               9
 #define  ALARM_MSGTYPE	             10
 #define  ALARM_PROTOCOL_CLS	       11
 #define  ALARM_SSN		               12
 #define  ALARM_LS 				           13
 #define  ALARM_NO_ELMNT	           14   
 #define  ALARM_DISCARDED            15

/*end here */

/* error code mapping*/
#define WRONG_CARDTYPE               521
#define ODD_TSVALUE_IN_STRMMAPTBL    523
#define NO_ENTRYFOUND_IN_STRMMAPTBL  522
#define WRONG_ROUTESTYLE_VAL         524
/*end*/

/*AOIP_HA Defines*/
#define SLOT_3   3
#define SLOT_4   4
#define PEER_CMD 2
#define MODULE_SIGTRAN MODULE_TCAP
#define ON  1
#define OFF 0
#define DONE 1
/*AOIP_HA end*/














#define NO_ERROR       0 /* meant for command successfull*/

#define ERROR_PEERSCM_WRITE_FAILED 12

#define NWSTK_CONFIG_COMPLETE                    200/* opcode to sync peer with configuration*/
#define SCM_NWSTKUP                            201/* opcode to inform peer scm about nw stack entity up */
#define ISUP_CONFIG_COMPLETE                   202/* opcode to inform peer scm about isup stack entity up */
#define MAPTCAP_CONFIG_COMPLETE                203/* opcode to inform peer scm about MAP/TCAP stack entity up */ 
#define MAPTCAP_STACK_UP                       204/* AOIP-HA*/

/* map timerid hashdefs */
#define MAP_TIMER_SMALL              0
#define MAP_TIMER_MEDIUM             1
#define MAP_TIMER_MEDIUM_LARGE       2
#define MAP_TIMER_LARGE              3
/*end here */
 
/* hash def for no. of command to be fetch from external DB
  these hashdef values should be 1 greater than actual required no. of cmds*/
 #define NUM_CMDS_MAPTCAP     13 
 #define NUM_CMDS_SIGTRAN     13 /*AOIP: UPDATED*/
 #define NUM_CMDS_BSSAP        2 /*AOIP: ADDED*/
 #define NUM_CMDS_NWSTK       15 
 #define NUM_CMDS_LAPD        2
 #define NUM_CMDS_REDUNDANT_NWSTK 4

/* not exact */


#ifdef MSB_FIRST
    #define EVAL_32(X,K) \
            ((K[X]   << 24) & F3) | \
            ((K[X+1] << 16) & F2) | \
            ((K[X+2] <<  8) & F1) | \
            ((K[X+3]) & F0)

    #define EVAL_24(X,K) \
            ((K[X]   << 16) & F2) | \
            ((K[X+1] <<  8) & F1) | \
            ((K[X+2]) & F0)

    #define EVAL_16(X,K) \
            ((K[X] <<8) & F1)| \
              K[X+1];

    #define EVAL_14(X,K) \
            ((K[X] <<8) & 0x3f00)| \
              K[X+1];

    #define EVAL_12(X,K) \
            ((K[X] <<8) & 0x0f00)| \
              K[X+1];
                           #define EXTRACT_32(A,B,C) \
                              C [A+3] = B & F0; \
                              C [A+2] = (B >> 8)  & F0; \
                              C [A+1] = (B >> 16) & F0; \
                              C [A]   = (B >> 24) & F0;

                           #define EXTRACT_24(A,B,C) \
                              C [A+2] = B & F0; \
                              C [A+1] = (B >> 8)  & F0; \
                              C [A]   = (B >> 16) & F0;

                           #define EXTRACT_16(A,B,C) \
                              C [A+1] = B & F0; \
                              C [A]   = (B >> 8) & F0;

                           #define EXTRACT_14(A,B,C) \
                              C [A+1] = B & F0; \
                              C [A]   = (B >> 8) & 0x3f;

                           #define EXTRACT_12(A,B,C) \
                              C [A+1] = B & F0; \
                              C [A]   = (B >> 8) & 0x0f;

#endif /*END OF MSB_FIRST*/

#define LSB_FIRST
#ifdef LSB_FIRST
    #define EVAL_32(X,K) \
            ((K[X+3] << 24) & F3) | \
            ((K[X+2] << 16) & F2) | \
            ((K[X+1] <<  8) & F1) | \
            ((K[X]) & F0)

    #define EVAL_24(X,K) \
            ((K[X+2]   << 16) & F2) | \
            ((K[X+1] <<  8) & F1) | \
            ((K[X]) & F0)

    #define EVAL_16(X,K) \
            ((K[X+1] <<8) & F1)| \
              K[X];

    #define EVAL_14(X,K) \
            ((K[X+1] <<8) & 0x3f00)| \
              K[X];

    #define EVAL_12(X,K) \
            ((K[X+1] <<8) & 0x0f00)| \
              K[X];
                           #define EXTRACT_32(A,B,C) \
                              C [A] = B & F0; \
                              C [A+1] = (B >> 8)  & F0; \
                              C [A+2] = (B >> 16) & F0; \
                              C [A+3]   = (B >> 24) & F0;

                           #define EXTRACT_24(A,B,C) \
                              C [A] = B & F0; \
                              C [A+1] = (B >> 8)  & F0; \
                              C [A+2]   = (B >> 16) & F0;

                           #define EXTRACT_16(A,B,C) \
                              C [A] = B & F0; \
                              C [A+1]   = (B >> 8) & F0;

                           #define EXTRACT_14(A,B,C) \
                              C [A] = B & F0; \
                              C [A+1]   = (B >> 8) & 0x3f;

                           #define EXTRACT_12(A,B,C) \
                              C [A] = B & F0; \
                              C [A+1]   = (B >> 8) & 0x0f;
#endif /*LSB_FIRST*/

/*family id's*/
#define ITU_FAMILY             0
#define ANSI_FAMILY            1
/*end here */

#ifdef BSC
/* lapd stack related hashdefs */

/*  APP ID       */

#define LAPD_SCM_IF_ID	0xD1

/*  Msg Group Ids     */

#define	LAPD_SCM_CFG_MSG	0x01
#define	LAPD_SCM_PEGS_MSG	0x02
#define	LAPD_SCM_TMR_MSG	0x03
#define	LAPD_SCM_ALARM_MSG	0x04
#define	LAPD_SCM_PEGS_NACK	0x06
#ifdef LAPD_HA
#define LAPD_CONFIG_COMPLETE    0x05
#endif

/* Msg Types	*/

#define	LAPD_SCM_CFG_ADD_TS		0x01
#define	LAPD_SCM_CFG_REM_TS		0x02
#define	LAPD_SCM_CFG_ADD_TEI		0x03
#define	LAPD_SCM_CFG_REM_TEI		0x04
#define	LAPD_SCM_CFG_ADD_SAPI		0x05
#define	LAPD_SCM_CFG_REM_SAPI		0x06
#define	LAPD_SCM_PEGS_SHOW		0x07
#define	LAPD_SCM_PEGS_CLEAR		0x08
#define	LAPD_SCM_TMR_SET			0x09
#define	LAPD_SCM_TMR_TRY			0x0A
#define	LAPD_SCM_ALARM_IND		0x0B


/* Timer Ids  */

#define   LAPD_T_200		(0x01U) 
#define   LAPD_T_201		(0x02U) 
#define   LAPD_T_202		(0x03U) 
#define   LAPD_T_203		(0x04U) 


/*  PEG Var Ids  */

#define	  PEG_LAPD_INFO_SEND      		0x01
#define	  PEG_LAPD_INFO_RECV      		0x02
#define	  PEG_LAPD_UI_SEND      		0x03
#define	  PEG_LAPD_UI_RECV      		0x04
#define	  PEG_LAPD_RR_C_SEND      		0x05
#define	  PEG_LAPD_RR_C_RECV      		0x06
#define	  PEG_LAPD_RR_R_SEND      		0x07
#define	  PEG_LAPD_RR_R_RECV      		0x08
#define	  PEG_LAPD_REJ_C_SEND      	0x09
#define	  PEG_LAPD_REJ_C_RECV      	0x0A
#define	  PEG_LAPD_REJ_R_SEND      	0x0B
#define	  PEG_LAPD_REJ_R_RECV      	0x0C
#define	  PEG_LAPD_RNR_C_SEND      	0x0D
#define	  PEG_LAPD_RNR_C_RECV      	0x0E
#define	  PEG_LAPD_RNR_R_SEND      	0x0F
#define	  PEG_LAPD_RNR_R_RECV      	0x10
#define	  PEG_LAPD_MSG_DECODE_FAIL      	0x11
#define	  PEG_LAPD_MSG_ENCODE_FAIL      	0x12


/*  Response Value    */

#define	  LAPD_SCM_SUCCESS    		0x00
#define	  LAPD_SCM_ERROR      		0x01


/*  Alarm Ids	*/

#define LAPD_ALARM_CROSS_MAX_TIMER_TRY	0x01   
#define LAPD_ALARM_MSG_ENCODE_FAIL		0x02   
#define LAPD_ALARM_MSG_DECODE_FAIL		0x03   
#define LAPD_ALARM_REJ_MSG_SEND		0x04   
#define LAPD_ALARM_RNR_MSG_SEND		0x05   
#define LAPD_ALARM_LINK_UP			0x06   
#define LAPD_ALARM_LINK_DOWN			0x07   


/*  Alarm Level    */

#define  LAPD_ALARM_LEVEL_INFO			0x01
#define  LAPD_ALARM_LEVEL_MINOR		0x02
#define  LAPD_ALARM_LEVEL_MAJOR		0x03
#define  LAPD_ALARM_LEVEL_CRITICAL		0x04

/* end here */
#endif


/* transaction Id hashdef values */
#define ISUP_TR_ID              1
#define NWSTK_TR_ID             2
#define CAP_TR_ID               3
#define MAPTCAP_TR_ID           4
#define NWSTK_MSC_CONFIG_TR_ID  5
#define OAM_MSC_CONFIG_TR_ID    6
/*end here */

/* handle hashdef*/
#define HANDLE1 1
#define HANDLE2 2
#define HANDLE3 3
/*end here */

/*Declaration of flags*/
#define EXIT_SCM exit (0);
#define SS7_FALSE   0
#define SS7_TRUE    1
#define SS7_ERROR  -1
#define SS7_NULL    NULL
/*end here*/
/*timer value declaration*/
#define TIMER_VAL              8
#define TIMER_NWSTK            1
#define TIMER_CAP              2
#define TIMER_MAPTCAP          3
#define TIMER_ISUP             4
#define TIMER_MULTICMD         5
#define TIMER_LAPD             6
#define TIMER_NWSTK_CONFIG     7

/*AOIP TIMERS*/
#define TIMER_BSSAP     TIMER_ISUP
#define TIMER_SIGTRAN   TIMER_MAPTCAP
/*AOIP END*/

#define STK_PROCESS_TID 1
#define  PROTOCOL_ERROR      1
#define  SYSTEM_ERROR        2
#define  SYSTEM_RES_ERROR    3
#define  API_ERROR           4
#define  NW_ELEMENT_STATUS_ERROR 5
#define ALL_ERROR       6
#define ALL_TRACE       11
#define MAP_TCAP_ALL_TRACE       3
#define MAP_ALL_ERROR   4
#define MAP_PROTOCOL_ERROR  0
#define MAP_SYSTEM_ERROR   1
#define MAP_API_ERROR     2
#define MAP_MISC_ERROR    3
/*end here*/

#define PORT 1
#define IP   2
/* these hashdefs are to store fd, ip and port add. */
#define ENT_NWSTK_DBG   0
#define ENT_NWSTK       1
#define ENT_OAM      2
#define ENT_PEER_SCM 3
#define ENT_MAP_TCAP 4
#define ENT_ISUP     5
/*AOIP ENTITIES*/
#define ENT_SIGTRAN  4
#define ENT_BSSAP    5
/*AOIP END*/
#define ENT_CAP      6
#define ENT_SCM      7
#define ENT_LAPD     8
#define ENTITY_SCM   160 /*use to form scm header for processing */
#define ENTITY_DB    100    
#if 0
#define ENTITY_SCM   160 /*use to form scm header for processing */
#define ENTITY_DB    100    

#define ENTITY_OAM      0
#define ENTITY_NWSTK    1 
#define ENTITY_CAP      2
#define ENTITY_MAPTCAP  3
#define ENTITY_ISUP     4
#endif 

#define MULTI_CMD       0 /* this hashdef is used for multicmd processing */
#define FROM_IMTCS      5 /* use to read from ISUP, MAPTCAP, CAP & PEER SCM */

/*instance ids for peer and self in case of link add cmd*/
#define SCM_PEER_INSTANCEID 20002
#define SCM_SELF_INSTANCEID 65524


#define DB_STAMP       1
#define OAM_STAMP      2
#define SCM_ACTIVE     1
#define SCM_STANDBY    2
#define SCM_AIP        3

#define SELF SCM_ACTIVE
#define PEER SCM_STANDBY
#define CARD_LINK_UP  5 /* temporary done */

/* hashdef for route add command i.e. local route or remote route*/
#define LOCAL_ROUTE              0
#define REMOTE_ROUTE             1

/* actual APPID'S */
/*cap is of default case */
#define APP_ID_PEER_SCM       100
#define APP_ID_TCAP           234 /*In case alarm app_id is 99 for isup, maptcap */
#define TCAP_API              0xe9   
#define SIGTRAN_M3UA_API      0xc2 /* Added by Amaresh for Sigtran */  
#define RESP_SIGTRAN_M3UA_API 0xc3 /* Added by Amaresh for Sigtran */  
#define APP_ID_MAP            242
#define APP_ID_ISUP           0xa4
#define RESP_APP_ID_ISUP      163
#define RESP_APP_ID_MAP       242
#define RESP_APP_ID
#define APP_ID_IMTC_ALARM      99      /* hashdef forisup map, tcap alarm , CAP*/
#define APP_ID_NWSTK          160
#define APP_ID_OAM            165 
#define APP_ID_CAP            102     /* this hashdef value is scm proprietary*/
#define APP_ID_MTP3           88/* MTP3 */
#define APP_ID_SCCP           90/* SCCP */
#define APP_ID_BSSAP          83/* BSSAP */
#define APP_ID_ISIL           86/*ISIL */
#define APP_ID_LAPD           96
#define ISUP_SKS_INDEX        84/*ISIL */
#define MAPTCAP_SKS_INDEX     87/*ISIL */
#define ISMAP_TCAP_ALARM        103    /* this hashdef value is scm proprietary*/

/*AOIP APPID NEW*/
#define APP_ID_SIGTRAN        APP_ID_TCAP 
#define APP_ID_BS             APP_ID_ISUP/*BSSAP AOIP APP ID*/
#define SIGTRAN_ALARM         ISMAP_TCAP_ALARM /*modified hashdef*/
/*AOIP END*/

/*CAP Timer types*/
#define CssfTimerNonUi                    0
#define CssfTimerUi                       1
#define CssfTimerTccd                     2
#define CssfTimerOperAcr                  3
#define CssfTimerOperCirReport            4
#define CssfTimerOperEventReport          5
#define CssfTimerOperInitialDp            6
#define CssfTimerOperSpecResourceReport   7
#define CssfTimerSmsOperEventReport       8
#define CssfTimerSmsOperInitialDp         9
#define CssfTimerSmsTssf                  10


/*  OAM  --> SCM (MAP) */

/* API ID : 233 */
/* COMMAND CATEGORY : 1 */
#define OAM_MAP_ADD_PLMN_ID                     235
#define OAM_MAP_DEL_PLMN_ID                     236
#define OAM_MAP_INIT                            237
#define OAM_MAP_TIMER_CONFIG                    238
#define MAP_SET_ERROR_LEVEL_REQUEST             0xef
#define MAP_GET_ERROR_LEVEL_REQUEST             0xf0


/*  OAM  <--SCM (MAP) */

/* API ID : 242 */
/* COMMAND CATEGORY : 1 */
#define OAM_MAP_ADD_PLMN_ID_RESP                235
#define OAM_MAP_DEL_PLMN_ID_RESP                236
#define OAM_MAP_INIT_RESP                       237
#define OAM_MAP_TIMER_CONFIG_RESP               238


/*  OAM  --> SCM (TCAP) */

/* API ID : 233 */
/* COMMAND CATEGORY : 0 */
#define OAM_TCAP_ENCODE                         1
/* COMMAND CATEGORY : 1 */
#define OAM_DEINIT_TCAP                         19
#define OAM_INIT_TCAP                           20
/* COMMAND CATEGORY : 2 */
#define OAM_TCAP_SS7_SM_INIT_STATS              0
#define OAM_TCAP_SS7_SM_GET_STATS               1
#define OAM_TCAP_SS7_SM_DISABLE_STATS           2
#define OAM_TCAP_SS7_SM_ENABLE_STATS            3
/* COMMAND CATEGORY : 3 */
#define OAM_TCAP_SS7_SM_GET_TRACE_LEVEL         0
#define OAM_TCAP_SS7_SM_SET_TRACE_LEVEL         1
/* COMMAND CATEGORY : 4 */
#define OAM_TCAP_SS7_SM_GET_ERR_LEVEL_RESP              0
#define OAM_TCAP_SS7_SM_SET_ERR_LEVEL_RESP              1
/* COMMAND CATEGORY : 5 */
#define OAM_TCAP_SS7_SM_INIT_REDN_DATA_RESP             0
#define OAM_TCAP_SS7_SM_ACTIVATE_MODULE_RESP            3
/* COMMAND CATEGORY : 6 */
#define OAM_TCAP_SS7_DISPLAY_MODULE_VERSION_RESP        4

/* TCAP/ISUP TRACE LEVEL */
#define TCAP_TRACE_LEVEL_INFO                           3
#define ISUP_TRACE_LEVEL_INFO                           3
/*end */

/*  OAM  <-- SCM (TCAP) */

/* API ID : 234 */
/* COMMAND CATEGORY : 0 */
#define OAM_TCAP_ENCODE_RESP                            1
/* COMMAND CATEGORY : 1 */
#define OAM_DEINIT_TCAP_RESP                            19
#define OAM_INIT_TCAP_RESP                              20
/* COMMAND CATEGORY : 2 */
#define OAM_TCAP_SS7_SM_INIT_STATS_RESP                 0
#define OAM_TCAP_SS7_SM_GET_STATS_RESP                  1
#define OAM_TCAP_SS7_SM_DISABLE_STATS_RESP              2
#define OAM_TCAP_SS7_SM_ENABLE_STATS_RESP               3
/* COMMAND CATEGORY : 3 */
#define OAM_TCAP_SS7_SM_GET_TRACE_LEVEL_RESP            0
#define OAM_TCAP_SS7_SM_SET_TRACE_LEVEL_RESP            1
/* COMMAND CATEGORY : 4 */
#define OAM_TCAP_SS7_SM_GET_ERR_LEVEL_RESP              0
#define OAM_TCAP_SS7_SM_SET_ERR_LEVEL_RESP              1
/* COMMAND CATEGORY : 5 */
#define OAM_TCAP_SS7_SM_INIT_REDN_DATA_RESP             0
#define OAM_TCAP_SS7_SM_ACTIVATE_MODULE_RESP            3
/* COMMAND CATEGORY : 6 */
#define OAM_TCAP_SS7_DISPLAY_MODULE_VERSION_RESP        4

/******************************************************
********* stats defines           ********************
******************************************************/


#define STATS_API               0x01
#define STATS_PROTO_Q752        0x02
#define STATS_PROTO_INTERNAL    0x03
#define STATS_TRAFFIC           0x04
#define STATS_ERROR             0x05
#define STATS_ALL               0x06 

/* add more stats definition here */
/* COMMAND CATEGORY : 0 */
#define OAM_ISUP_PROV_CKT_GRP                   0
#define OAM_ISUP_UNPROV_CKT_GRP                 1
#define OAM_ISUP_INIT_TIMERS                    2
#define OAM_ISUP_PROV_GRP_RANGE                 3
#define OAM_ISUP_INIT_TIMERS_TENS_MS            4
#define OAM_ISUP_PROV_GET_CKT_GRP_INFO          5
/* COMMAND CATEGORY : 1 */
#define OAM_ISUP_INIT                           0
/* COMMAND CATEGORY : 2 */
#define OAM_ISUP_SS7_SM_INIT_STATS              0
#define OAM_ISUP_SS7_SM_GET_STATS               1
#define OAM_ISUP_SS7_SM_DISABLE_STATS           2
#define OAM_ISUP_SS7_SM_ENABLE_STATS            3
/* COMMAND CATEGORY : 3 */
#define OAM_ISUP_SS7_SM_GET_TRACE_LEVEL         0
#define OAM_ISUP_SS7_SM_SET_TRACE_LEVEL         1
/* COMMAND CATEGORY : 4 */
#define OAM_ISUP_SS7_SM_GET_ERR_LEVEL           0
#define OAM_ISUP_SS7_SM_SET_ERR_LEVEL           1
/* COMMAND CATEGORY : 5 */
#define OAM_ISUP_SS7_SM_INIT_REDN_DATA          0
#define OAM_ISUP_SS7_SM_ACTIVATE_MODULE         3
/* COMMAND CATEGORY : 6 */
#define OAM_ISUP_SS7_DISPLAY_MODULE_VERSION     4


/*  OAM  <-- SCM (ISUP) */

/* API ID : 163 */
/* COMMAND CATEGORY : 0 */
#define OAM_ISUP_PROV_CKT_GRP_RESP                      0
#define OAM_ISUP_UNPROV_CKT_GRP_RESP                    1
#define OAM_ISUP_INIT_TIMERS_RESP                       2
#define OAM_ISUP_PROV_GRP_RANGE_RESP                    3
#define OAM_ISUP_INIT_TIMERS_TENS_MS_RESP               4
#define OAM_ISUP_PROV_GET_CKT_GRP_INFO_RESP             5
/* COMMAND CATEGORY : 1 */
#define OAM_ISUP_INIT_RESP                              0
/* COMMAND CATEGORY : 2 */
#define OAM_ISUP_SS7_SM_INIT_STATS_RESP                 0
#define OAM_ISUP_SS7_SM_GET_STATS_RESP                  1
#define OAM_ISUP_SS7_SM_DISABLE_STATS_RESP              2
#define OAM_ISUP_SS7_SM_ENABLE_STATS_RESP               3
/* COMMAND CATEGORY : 3 */
#define OAM_ISUP_SS7_SM_GET_TRACE_LEVEL                 0
#define OAM_ISUP_SS7_SM_SET_TRACE_LEVEL_RESP            1
/* COMMAND CATEGORY : 4 */
#define OAM_ISUP_SS7_SM_GET_ERR_LEVEL_RESP              0
#define OAM_ISUP_SS7_SM_SET_ERR_LEVEL_RESP              1
/* COMMAND CATEGORY : 5 */
#define OAM_ISUP_SS7_SM_INIT_REDN_DATA_RESP             0
#define OAM_ISUP_SS7_SM_REQ_REDUNDANT_DATA              1
#define OAM_ISUP_SS7_SM_UPDATE_WITHRED_DATA             2
#define OAM_ISUP_SS7_SM_ACTIVATE_MODULE_RESP            3
/****** ISUP redn data types ********************/

#define ISUP_REDN_DATA_DPC          0x01
#define ISUP_REDN_DATA_CSC_LM   0x02
#define ISUP_REDN_DATA_CSC_RM   0x03
#define ISUP_REDN_DATA_CPC          0x04
/* spr - 16636 MNA Changes */
#define ISUP_REDN_DATA_REG_ENTRY    0x05
#define ISUP_REDN_DATA_DEREG_ENTRY    0x06

/****** Stack Entity STATES *******/
/* COMMAND CATEGORY : 6 */
#define OAM_ISUP_SS7_DISPLAY_MODULE_VERSION_RESP        4


 

/*return value of read function for entity */
#define FROM_MTI          1
#define FROM_CAP          2


/* Alarm ranges for ISUP, MAP TCAP */
#define ISUP_ALRM_RNG1         1862 
#define ISUP_ALRM_RNG2         2175
#define ISUP_ALRM_RNG3         2215 
#define ISUP_ALRM_RNG4         2218
#define ISUP_ALRM_RNG5         2219   

#define TCAP_ALRM_RNG1         3074
#define TCAP_ALRM_RNG2         3088
#define TCAP_ALRM_RNG3         3096
#define TCAP_ALRM_RNG4         3102

#define MAP_ALRM_RNG1                    4001
#define MAP_ALRM_RNG2                    4003
#define MAP_ALRM_RNG3                    4007
#define MAP_ALRM_RNG4                    4009
#define MAP_ALRM_RNG5                    4010
#define MAP_ALRM_RNG6                    4033
#define MAP_ALRM_RNG7                    4035
#define MAP_ALRM_RNG8                    4037
#define MAP_ALRM_RNG9                    4039
#define MAP_ALRM_RNG10                   4040
#define MAP_ALRM_RNG11                   4129
#define MAP_ALRM_RNG12                   4131
#define MAP_ALRM_RNG13                   4134
#define MAP_ALRM_RNG14                   4136

#define CAP_ALRM_RNG1                   6001 
#define CAP_ALRM_RNG2                   6011 
#define CAP_ALRM_RNG3                   6018 
#define CAP_ALRM_RNG4                   6025 
#define CAP_ALRM_RNG5                   6052 
#define CAP_ALRM_RNG6                   6059 
#define CAP_ALRM_RNG7                   6061 
#define CAP_ALRM_RNG8                   6062 
#define CAP_ALRM_RNG9                   6065 
#define CAP_ALRM_RNG10                  6070 
/* Alarm ranges end here */
#ifdef BSC
#define LAPD_MIN_ALARM_VAL               202
#define LAPD_MAX_ALARM_VAL               205
#endif
 
















