/****************************************************************************/
/*                                                                          */
/*      Copyright (C) 1992-2003 by TeleSoft International, Inc.             */
/*                                                                          */
/*      These computer program listings and specifications,                 */
/*      herein, are the property of TeleSoft International, Inc.            */
/*      and shall not be reproduced or copied or used in whole or in        */
/*      part without written permission from TeleSoft International, Inc.   */
/*                                                                          */
/*      This version has been modified by PaloVerde Internacional, Inc.     */
/*      to accomodate R2 register signalling variants and the               */
/*      Taiwan Modified R1 protocol.                                        */
/*                                                                          */
/****************************************************************************/
#if !defined(__L4CEL3_H_)
#define __L4CEL3_H_



typedef struct
{
unsigned short   lapdTimerT200;
unsigned short   lapdTimerT203;
unsigned short   N200; /*T200 timer retries */
unsigned short   dummy;
}LapdTmrConfig;

typedef struct
{
 unsigned char   ts;       /*LAPD PP-TS */
 unsigned char   satFlag;  /*1=True  0=False*/
 unsigned short  dummy;    /*padding */
}LapdTsData;



typedef struct
{
LapdTmrConfig  lapdTimerDefault;
LapdTmrConfig  lapdTimerSatellite;
unsigned int   noOfLapdTs;
LapdTsData     lpdTsdetail[80];
}lapdCoreTimerData;

typedef struct
{
    unsigned char  ts;          // Time Slot                 
    unsigned char  lapdTei;      // TEI towards lapd      
    unsigned int   lci_chantype; 
 
}LapdTeiInfo;

typedef struct
{
  unsigned int      count;             /*Range 1..5 */
  LapdTeiInfo lapdTeiInfo[5];
}LapdPegCmd;

typedef struct
{
  LapdTeiInfo lapdTeiInfo[2];
    /* right now we have status get for two tei's only
       in future it may be for multiple then we will implement
       count here as well :- anand */
}LapdLinkStsGet;

typedef struct
{
  unsigned char  tei;          // Time Slot
  unsigned char  OmlSts;      // TEI towards lapd
  unsigned char  RslSts;

}LapdLinkStsResp;


typedef struct
{
  LapdLinkStsResp lapdLinkStsResp[2];
  /* right now we have status get for two tei's only
     in future it may be for multiple then we will implement
     count here as well :- anand */
}LapdLinkStatusResp;


/*
 *  struct and constant definitions common to all interfaces among
 *  the Layer 4, Coordinating Entity, Layer 3 Network Layer Packet (NLP)
 *  and Layer 3 Network Layer Signalling (NLS) entities
 */

/*
 *  mailbox/message structure for each primitive
 *  between Layer 4, the CE, and the NLP and NLS entities
 */
struct l4_ce_l3_msg
{
      unsigned long reserved1; /* reserved for oper sys use           */
      unsigned short reserved2;/* reserved for oper sys use           */
      unsigned char primcode;  /* primitive command code              */
      unsigned char receipt;   /* primitive receipt code              */
      unsigned char d_attrib;  /* data attributes (D-bit,M-bit,Q-bit) */
      unsigned char ss_info;   /* For supplementary services use (*)  */
      unsigned short connid;   /* CONNection ID                       */
      unsigned short datalen;  /* length of buf pointed to by dataptr */
      unsigned short refnum;   /* refnum of buf pointed to by dataptr */
      unsigned char cause[2];  /* cause of DISCONN, RESET, or STATUS  */
      unsigned short lci_chantype; /* Logical Channel Number or Chantype */
      unsigned short lapdTei;   /*Lapd Tei val*/
      unsigned char *dataptr;  /* pointer to prim-specific data       */
}; /* Currently 24 bytes long - (*) the use depend of specific service */


#if defined(TSL3_COMPLETE_API_RECEIVE_ENABLE) || \
   defined(TSL3_COMPLETE_API_TRANSMIT_ENABLE)
#define IPB_FIXED_HDRLEN 70
#else
/* CKS, MR23.02, 08/08/02; CDC, update 7/15/03 */
#define IPB_FIXED_HDRLEN 68
#endif

/*
 *  N_, NLP_, and NLS_ primitive (i.e., L4/CE/L3 prims)
 *  Indirect Parameter Block (IPB) struct definition
 */
/* IMPORTANT NOTE: The IPB_FIXED_HDRLEN define MUST be updated manually
 * as connparms struct members are added or taken away
 */
struct connparms
{
   unsigned short chantype;   /* Interface (top byte) | chan_num (low)*/
   unsigned short src_dlci;   /* Source_DLCI for FRM_RLY MultiCast Group */
   unsigned short profile;     /* Used for passing PPP profile/bundle  */
   unsigned char voice_data;  /* voice/data indicator                 */
   unsigned char svctype;     /* data call service type               */
   unsigned char pvcselect;   /* NLP Permanent Virtual Circuit select */

   /* in-band called address length  */
   unsigned char i_called_addr_len;

   /* in-band called address offset into this indirect parm block */
   unsigned char i_called_addr_offset;

   /* in-band calling address length */
   unsigned char i_calling_addr_len;

   /* in-band calling address offset into this indirect parm block */
   unsigned char i_calling_addr_offset;

   /* out-of-band called address length */
   unsigned char o_called_addr_len;

   /* out-of-band called address offset into this indirect parm block */
   unsigned char o_called_addr_offset;

   /* out-of-band calling address length */
   unsigned char o_calling_addr_len;

   /* out-of-band calling address offset into this indirect parm block */
   unsigned char o_calling_addr_offset;

   /* redirecting address length */
   unsigned char rgn_len;

   /* redirecting address offset into this indirect parm block */
   unsigned char rgn_offset;

   /* suspend/resume call identity length */
   unsigned char call_id_len;

   /* Calling name in use -- 0, not used, 1, present, 2, inf following */
   unsigned char o_calling_name_in_use;

   /* Calling name Presentation Type */
   unsigned char o_calling_name_type;

   /* Calling Name Length */
   unsigned char o_calling_name_len;

   /* Calling name offset into this indirect parm block */
   unsigned char o_calling_name_offset;

   /* suspend/resume call identity offset */
   unsigned char call_id_offset;

   unsigned char receipt_cf_indic;  /* receipt confirmation indicator  */
   unsigned char exped_data_indic;  /* expedited data indicator        */

   /* user data length 1 */
   unsigned char user_data_len1;

   /* user data offset 1 into this indirect parm block */
   unsigned char user_data_offset1;

   /* user data length 2 */
   unsigned char user_data_len2;

   /* user data offset 2 into this indirect parm block */
   unsigned char user_data_offset2;

   /* out-of-band called subaddress length */
   unsigned char o_called_sub_len;

   /* out-of-band called subaddress offset into this indirect parm block */
   unsigned char o_called_sub_offset;

   /* out-of-band calling subaddress length */
   unsigned char o_calling_sub_len;

   /* out-of-band calling subaddress offset into this indirect parm block */
   unsigned char o_calling_sub_offset;

   /* bearer capability information element length */
   unsigned char bc_len;

   /* bearer capability information element offset */
   unsigned char bc_offset;

   /* high layer compatibility information element length */
   unsigned char hlc_len;

   /* high layer compatibility information element offset */
   unsigned char hlc_offset;

   /* low layer compatibility information element length */
   unsigned char llc_len;

   /* low layer compatibility information element offset */
   unsigned char llc_offset;

   /* facility information element length */
   unsigned char facility_len;

   /* facility information element offset */
   unsigned char facility_offset;

   /* notification indicator information element length */
   unsigned char notify_in_len;

   /* notification indicator information element offset */
   unsigned char notify_in_offset;

   /* network-specific facilities information element length IE #1 */
   unsigned char nets_facil_len1;

   /* network-specific facilities information element offset IE #1 */
   unsigned char nets_facil_offset1;

   /* network-specific facilities information element length IE #2 */
   unsigned char nets_facil_len2;

   /* network-specific facilities information element offset IE #2 */
   unsigned char nets_facil_offset2;

   /* transit network select information element length */
   unsigned char transit_select_len;

   /* transit network select information element offset */
   unsigned char transit_select_offset;

   /* locking shift codeset 6 information element list length */
   unsigned char codeset6_len;

   /* locking shift codeset 6 information element list offset */
   unsigned char codeset6_offset;

   /* locking shift codeset 7 information element list length */
   unsigned char codeset7_len;

   /* locking shift codeset 7 information element list offset */
   unsigned char codeset7_offset;

   /*
    *  ss_request - Supplementary Service Request field
    *
    *  This field is used to transfer the request for some Supplementary
    *  Services from Layer 4 to Layer 3, usually during the setup stage
    *
    *  The field is used in bit mode following this format for ETSI :
    *
    *   7  6  5  4  3  2  1  0  bits
    *   |  |  |  |  |  |  +--+- AOC request
    *   |  |  |  |  |  |        00 = AOCS
    *   |  |  |  |  |  |        01 = AOCD
    *   |  |  |  |  |  |        10 = AOCE
    *   |  |  |  |  |  |        11 = No request
    *   |  |  |  |  |  |
    *   |  |  |  |  |  +- 1 = Clir request
    *   |  |  |  |  |
    *   |  |  |  +--+- Call diversion request
    *   |  |  |        00 = CFU
    *   |  |  |        01 = CFB
    *   |  |  |        10 = CFNR
    *   |  |  |        11 = CD
    *   |  |  |
    *   |  +--+- Operation 00 = deactivation
    *   |                  01 = activation
    *   |                  10 = interrogation
    *   +--- 0 = Call Waiting disabled
    *        1 = Call Waiting enabled
    *
    *  AOC request
    *  This field is used to determine which AOC service to enable at the
    *  setup time for the Supplementary Service AOC (ETS 300 182) - it is
    *  set from L4 - see SS.H for the enum - don't move the subfield
    *
    *  CLIR request
    *  This field is used to determine whether or not to send the
    *  Calling party IE at setup time for the Supplementary Service
    *  CLIR (ETS 300 093) - it is set from L4
    *
    *  Call diversion request
    *  This field is used to determine which Call diversion service to
    *  enable for the Supplementary Service (ETS 300 207) - it is
    *  set from L4 - see SS.H for the enum - don't move the subfield
    *
    *  Operation
    *  This field is used to enable or disable or request the interrogation
    *  for a SS - it is a generic field, i.e. can be used by many SS
    *
    *  Call Waiting
    *  This field is used to enable or disable the Call Waiting feature
    *  It is used by the code in the Network side to present and manage a call
    *  under Call Waiting condition
    *  This bit should be set by the application during the N_CONN_RQ
    *
    *=====================================================================
    *
    *  The field is used in bit mode following this format for US SW (5ESS/USNI/USNI2) :
    *
    *   7  6  5  4  3  2  1  0  bits
    *   |  |  |  |  |  |  |  |
    *   |  |  |  |  |  |  |  +- 0 = normal call - 1 = ACO call
    *   |  |  |  |  |  |  |        
    *   |  |  |  |  |  |  |    
    *   |  |  |  |  +--+--+---- 000 -> no interpretation component
    *   |  |  |  |              001 -> interpretation component : discard Invoke if not recognized
    *   |  |  |  |              010 -> interpretation component : discard message if not recognized
    *   |  |  |  |              011 -> interpretation component : discard Invoke if not recognized
    *   |  |  |  |              xxx -> reserved   
    *   |  |  |  +-------------
    *   |  |  +----------------
    *   |  +-------------------
    *   +----------------------
    *
    *  ACO call
    *  This field is used to emit a Setup message for the ACO
    *  This bit should be set by the application during the N_CONN_RQ
    *
    */

   unsigned char ss_request;

   /*
    *  Supplementary Services extra parameters
    *
    *  These fields are generig 1 byte fields to convey information related to 
    *  ETSI, USNI and QSIG Supplementary services
    *  See specific documents for the use of these fields (for example for the 
    *  QSIG SS-CT service)
    */
   
   unsigned char ss_param1;
   unsigned char ss_param2; 
   unsigned char ss_param3; 
   unsigned char ss_param4; 

   unsigned char ss_param5_len;
   unsigned char ss_param5_offset;

   unsigned char ss_param6_len;
   unsigned char ss_param6_offset;

   unsigned char ss_param7_len;
   unsigned char ss_param7_offset;

   /* CKS, MR23.02, 08/08/02 */
   unsigned short l4_ifc;     /* L4 interface being used by this connect.*/
                              /*  The upper byte if this field indicates */
                              /*  the L4 interface type. Possible types: */
                              /*  L4_USART, L4_INF, L4_POTS, L4_ROUTER,  */
                              /*  etc. The lower byte is the L4 inter-   */
                              /*  face port number.                      */

#if defined(TSL3_COMPLETE_API_RECEIVE_ENABLE) || \
   defined(TSL3_COMPLETE_API_TRANSMIT_ENABLE)
   /* Complete API information element list length in bytes */
   unsigned char complete_api_len;

   /* Complete API information element list offset in bytes */
   /* facility compatibility information element offset in var_data */
   unsigned char complete_api_offset;
#endif

   /* variable length data area */
   unsigned char var_data[SYSPKTSIZ - IPB_FIXED_HDRLEN];
};

/*
 *  The stat_parms structure is used with the N_STAT_IN(MISC_INFO) primitive
 *  It allows multiple information elements (IEs) to be transferred in a block
 *  to the upper layers.
 */

#define STAT_PARM_HDRLEN 56

struct stat_parms
{
   unsigned char usr_usr_len;
   unsigned char usr_usr_offset;
   unsigned char facil_info_len;
   unsigned char facil_info_offset;
   unsigned char nets_facil_info_len;
   unsigned char nets_facil_info_offset;
   unsigned char keypad_len;
   unsigned char keypad_offset;
   unsigned char called_sub_len;
   unsigned char called_sub_offset;
   unsigned char calling_sub_len;
   unsigned char calling_sub_offset;
   unsigned char llc_len;
   unsigned char llc_offset;
   unsigned char fi_len[20];    /* should be coordinated with MAX_FI_IE in */
   unsigned char fi_offset[20]; /* file include\nlstune.h                  */
   unsigned char prog_indic_len;
   unsigned char prog_indic_offset;
   /* variable length data area */
   /* subtract number of bytes above */
   unsigned char var_data[LBUFLEN - STAT_PARM_HDRLEN];
};



/* CHANNEL TYPES used with "chantype" member                        */
/* chantype value to select the power-on reset defined default chan */

#define CHAN_DEFAULT       0
/*
 *  channel defined by the low order byte of chantype
 *  physical interface unit defined by the high order byte.
 */
#define DCHAN           0x00                         /* D-CHANNEL   */
#define B1CHAN          0x01                         /* B-CHANNEL 1 */
#define B2CHAN          0x02                         /* B-CHANNEL 2 */

/* VOICE/DATA INDICATOR TYPES used with "voice_data" member */
#define DATA_CALL     0           /* Default Data Call      */
#define DATA64_CALL   0           /* 64K Data Call          */
#define VOICE_CALL    1           /* Voice Call             */
#define DSP_CALL      2           /* Digital Signal Processor Call */
#define PDL_CALL      3           /* Parameter Download (US NI-2)  */
#define DATA56_CALL   4           /* KAD 56K Data Call added */
#define DATA56_OVER_VOICE_CALL  5 /* KAD 56K Data over Voice Call added */
#define DATA64_OVER_VOICE_CALL  6 /* KAD 64K Data over Voice Call added */
#define DATA64_TRANSPARENT_CALL 7 /* Application supplied bit transp data */
#define DATA64_V110_CALL        8 /* Software V.110                     */

/*
 *  DATA CALL SERVICE TYPES used with "svctype" member
 *  also used as defines for b*_ch_data struct member
 *  and data_type for AT_CMDBK.C
 */
#define NO_BCH_DATA      0     /* no B-Channel data connections       */
#define SVC_NUP_X25      1     /* Nailed-up X.25                      */
#define SVC_CSW_X25      2     /* Circuit-switched X.25 (X.31 MAX)    */
#define SVC_OND_X25      3     /* On-Demand X.25                      */
/*
 *  NOTE: For On-Demand X.25 service, only the Out-of-band connection
 *       ("|" connection) has svctype==SVC_OND_X25.  The In-band
 *       OND connections have svctype==SVC_NUP_X25.
 */
#define SVC_NUP_V120     4     /* Nailed-up V.120 data                */
#define SVC_CSW_V120     5     /* Circuit-switched V.120 data         */
#define SVC_CSW_V110     6     /* Circuit-switched V.110 data         */
#define SVC_CSW_RAW_HDLC 7     /* Circuit-switched RAW_HDLC KAD added */
#define SVC_CSW_PPP      8     /* Circuit-switched PPP KAD added */
#define SVC_CSW_ASYNC_TO_SYNC 9   /* Circuit-switched ASYNC_TO_SYNC PPP KAD added */
#define SVC_CSW_X75_SLP  10    /* Circuit-switched X.75 SLP  PR 02/05/97 */
#define SVC_NUP_FRM_RLY  11    /* "Nailed-Up" Frame Relay (PVCs)      */
#define SVC_CSW_FRM_RLY  12    /* Circuit-switched Frame Relay (SVCs) */
#define SVC_NUP_RAW_DATA 13    /* Nailed-up Raw Data */
#define SVC_NUP_BRIDGE   14    /* Nailed-up Bridged (RFC 1483) Ethernet */
#define SVC_CSW_DATA     15    /* Circuit-switched clear channel data */

#define SVC_VOICE        16    /* Special voice "service type"        */
/* Non-Call Associated Temporary Signaling Connection */
#define SVC_NCA_TSC      17
#define SVC_NUP_PPP      18    /* Nailed-up PPP and ML-PPP */
#define SVC_MAX          18    /* To be defined as "maximum" svctype  */

/* Permanent Virtual Circuit DEFINES used with "pvcselect" member        */
#define NO_PVC          0   /* PVC not used this logical connection      */
/*
 *  bit mask to cause to the low order 7-bits of "pvcselect" to
 *  be a valid index into the "pvc[]" array in the power-on
 *  reset parameter struct
 */
#define PVC_ACTIVE   0x80

/* EXPEDITED DATA DEFINES */

/* expedited data feature IS NOT supported during this data call */
#define NOT_EXPEDITED    0
/* expedited data feature IS supported during this data call     */
#define EXPEDITED        1

/* RECEIPT CONFIRMATION DATA DEFINES */

/* receipt confirm feature IS NOT supported during this data call */
#define NOT_RECEIPT_CONFIRM    0
/* receipt confirm feature IS supported during this data call     */
#define RECEIPT_CONFIRM        1

/* Service Access Point ID( SAPI) constant defines                    */
#define SAPI_DNUPX25    16   /* X.25 Layer 3 Nailed-UP on D-Ch.       */

/* DATA ATTRIBUTES DEFINES */
#define D_BIT_DATA   0x01
#define M_BIT_DATA   0x02
#define Q_BIT_DATA   0x04
#define ACK_DATA     0x08       /* Acknowledge transmit data to Layer 4 */

/*
 *  Layer 4 and Coordinating Entity interface struct and constant
 *  definitions
 */

/*
 *  Primitive command codes for the interface from Layer 4 to
 *  the Coordinating Entity.  These must correspond with the codes defined
 *  for the CE to L3 and L3 to CE primitives.
 */

/* Layer 4 to Coordinating Entity Mailbox Codes              */
#define N_CONN_RQ       0x00     /* N_CONNECT_REQUEST        */
#define N_CONN_RS       0x01     /* N_CONNECT_RESPONSE       */
#define N_DISC_RQ       0x02     /* N_DISCONNECT_REQUEST     */
#define N_REL_RQ        0x03     /* N_RELEASE_REQUEST        */
#define N_DATA_RQ       0x04     /* N_DATA_REQUEST           */
#define N_DACK_RQ       0x05     /* N_DATA_ACK_REQUEST       */
#define N_EXP_RQ        0x06     /* N_EXPEDITED_DATA_REQUEST */
#define N_STAT_RQ       0x07     /* N_STATUS_REQUEST         */
#define N_RES_RQ        0x08     /* N_RESET_REQUEST          */
#define N_RES_RS        0x09     /* N_RESET_RESPONSE         */
#define N_START_RQ      0x0A     /* N_START_REQUEST          */
#define N_RELOAD_RQ     0x0B     /* N_RELOAD_REQUEST         */
#define N_KEYPAD_RQ     0x0C     /* N_KEYPAD_REQUEST         */
#define N_DISPLAY_RQ    0x0D     /* N_DISPLAY_REQUEST        */
#define N_SS_RQ         0x10     /* N_SUPPLEMENTARY_SERVICES */
#define N_DV_RQ         0x11     /* N_DIGITIZED_VOICE_REQUEST*/
#define N_VOL_RQ        0x12     /* N_VOLUME_REQUEST         */
#define N_MAP_RQ        0x13     /* N_MAP_REQUEST            */
#define N_MIC_RQ        0x14     /* N_MIC_REQUEST            */
#define N_BCHAN_LOOP    0x15     /* N_B_CHANNEL_LOOPBACK_RQ  */
#define N_DCHAN_LOOP    0x16     /* N_D_CHANNEL_LOOPBACK_RQ  */
#define N_SUS_RQ        0x20     /* N_SUSPEND_REQUEST        */
#define N_REM_RQ        0x21     /* N_RESUME_REQUEST         */
#define N_MORE_INFO_RQ  0x24     /* N_MORE_INFO_RQ           */
#define N_SUS_RS        0x27     /* N_SUSPEND_RESPONSE       */
#define N_REM_RS        0x28     /* N_RESUME_RESPONSE        */
#define N_PDL_RQ        0x30     /* N_Parameter_DownLoad_REQUEST  */
#define N_BAP_RQ        0x31     /* BACP                     */
#define N_ALERT_RQ      0x32     /* N_ALERT_REQUEST (for U9) */
#define N_REST_CHAN_RQ  0x33     /* N_RESTART_CHANNEL_REQUEST*/
#define N_SND_BOM       0x34     /* CGB  970120  Added       */
#define N_PRI_STAT_RQ   0x35     /* CGB  970120  Added       */
#define N_CALL_PROC_RQ  0x36     /* CGB  970120  Added       */
#define N_FMIC_SIMPLEX_RQ 0x37   /* KAD  970603  Added       */
#define N_FMIC_DUPLEX_RQ  0x38   /* KAD  970603  Added       */
#define N_FMIC_DISC_RQ  0x39     /* KAD  970603  Added       */
#define N_PROG_RQ       0x3A     /* CB  19970703  Added      */
#define N_CONN_ACK_RQ   0x3B     /* N_CONN_ACK_REQUEST       */
#define N_PRI_CONTEXT_RQ        0x3C
#define N_PRI_CONTEXT_SET_RQ    0x3D
#define N_PRI_CONTEXT_ACT_RQ    0x3E
#define N_SET_CHAN_STAT_RQ      0x3F
#define N_RAW_Q931_RQ           0x40
#define N_CONGESTION_CONTROL_RQ 0x41
#define N_FACILITY_RQ           0x42
#define N_FACILITY_ACK_RQ       0x43
#define N_FACILITY_REJ_RQ       0x44
#define N_REGISTER_RQ           0x45
#define N_USER_INFO_RQ          0x46
#define N_DIAG_RQ               0x47   /* misc diagnostic cmd */
#define N_SET_LAYER_PARM_RQ     0x50 /* N_SET_LAYER_PARM_REQUEST    */
#define N_GET_LAYER_PARM_RQ     0x51 /* N_GET_LAYER_PARM_REQUEST    */
#define N_GET_LAYER_STATS_RQ    0x52 /* N_GET_LAYER_STATS_REQUEST   */
#define N_RESET_LAYER_STATS_RQ  0x53 /* N_RESET_LAYER_STATS_REQUEST */
#define N_GET_CALL_TABLE_RQ     0x54 /* N_GET_CALL_TABLE_REQUEST    */
#define N_MB_ADD_LINK_RQ        0x60 /* MFR Bundle Add Link Request */
#define N_MB_REMOVE_LINK_RQ     0x61 /* MFR Bundle Rem Link Request */
#define N_ML_ADD_CVC_RQ         0x62 /* ML AVC Add PVC Request      */
#define N_ML_REMOVE_CVC_RQ      0x63 /* ML AVC Remove PVC Request   */
#define N_PVC_CTRL_RQ           0x64 /* PVC Control Request         */
#define N_MODIRY_LAYER_TIMER_RQ 0x65 /* MODIFY LAPD TIMER VAL       */
#define N_GET_LINK_STATUS_RQ    0x66 /* Get lapd link status req       */

/*
 *  STATUS INDICATION DEFINES (N*_STAT_IN)
 */
#define STAT_ONHOOK     0x00
#define STAT_OFFHOOK    0x01
#define FATAL_ERROR     0x02
#define START_ALERT     0x03
#define STOP_ALERT      0x04
#define CAUSE_IND       0x05   /* Cause IE indication        */
#define DISPLAY_INFO    0x06   /* Display information        */
#define SIGNAL_IND      0x07   /* Signal IE indicator        */
#define PROGRESS_IND    0x08   /* Progress IE indicator      */
#define FEATURE_IND     0x09   /* Feature Indicator IE       */
#define LINE_NOT_ACTIVE 0x0A   /* Line not currently active  */
#define LINE_ACTIVE     0x0B   /* Line currently active      */
#define TEI_REMOVED     0x0C   /* TEI Removed                */
#define DISC_RCV        0x0D   /* Q.931 DISC pkt received    */
#define UPDATE_PCHAN    0x0E   /* Update PCHAN for a connid  */
#define SPID_ERR        0x0F   /* err in term init rq        */
#define NO_CHAN_ERR     0x10   /* no channel avail           */
#define FACILITY_IND    0x11   /* Facility IE indication     */
#define NOTIFY_IND      0x12   /* Notify Indic IE indication */
#define INFO_RQ_IND     0x13   /* Info Request IE indication */
#define TEI_REM_INFO    0x14   /* TEI Removed information    */
#define SCREEN_UPDATE   0x15   /* Update Screen after PDL    */
#define MISC_INFO       0x16   /* Miscellaneous information  */
#define ISDN_MSG        0x17   /* ISDN MSG HEX DUMP          */
#define PPP_ACTIVE      0x18   /* PPP Active                 */
#define PPP_UPDATE_PROF 0x19   /* Update the PPP Profile     */
#define LINE_NOT_READY  0x1A   /* Line not ready for calls   */
#define LINE_READY      0x1B   /* Line now ready for calls   */
#define FMIC_CONN       0x1C   /* KAD */

#define CALLW_ASK       0x1D   /* CAll waiting asking        */
#define CALLW_NOT       0x1E   /* Call Waiting notify        */
#define REMUSER_SUS     0x1F   /* Remote user Suspended      */
#define REMUSER_RES     0x20   /* Remote user Resumed        */
#define SEND_COMPLETE   0x21   /* End of digits for overlap sending */
#define CONN_RCV        0x22   /* CONN received in response (network-side) */
#define STATE_0_RCV     0x23   /* STATUS w/CS=0 received in N19            */
#define DIVERTING_NOT   0x24   /* Diverting notify           */
#define DIVERTED_NOT    0x25   /* Diverted notify            */
#define REMUSER_HOLD    0x26   /* Remote user in Hold        */
#define REMUSER_ENDHOLD 0x27   /* Remote user finish hold    */
#define ECT_ALERTING    0x28   /* ECT in alerting            */
#define ECT_ACTIVE      0x29   /* ECT active                 */
#define TPTY_ACTIVE     0x2A   /* 3Pty conference On         */
#define TPTY_DEACTIVE   0x2B   /* 3Pty conference Off        */
#define TPTY_HOLD       0x2C   /* 3Pty user in hold          */
#define PCHAN_NOT_ACTIVE 0x2D  /* Frame Relay PCHAN Trouble          */
#define PCHAN_ACTIVE     0x2E  /* Frame Relay PCHAN Active           */
#define DLCI_INFO        0x2F  /* Frame Relay DLCI data              */
#define ERR_REPORT       0x30  /* Frame Relay Frame Error Detected   */
#define LINK_READY       0x31  /* Frame Relay Link Becomes Ready     */
#define LINK_NOT_READY   0x32  /* Frame Relay Link Becomes Not_Ready */
#define BIT_RATE_CHANGE  0x33  /* Frame Relay Link Bit Rate Change   */
#if defined(CAS_R2)
#define CAS_R2_GROUP_I_TONE_RECEIVED  0x34 /* CAS Group I tone received */
#define CAS_R2_GROUP_II_TONE_RECEIVED 0x35 /* CAS Group II tone received */
#define CAS_R2_GROUP_A_TONE_RECEIVED  0x36 /* CAS Group A tone received */
#define CAS_R2_GROUP_B_TONE_RECEIVED  0x37 /* CAS Group B tone received */
#define CAS_R2_GROUP_III_TONE_RECEIVED 0x38 /* CAS Group III tone received */
#define CAS_R2_GROUP_C_TONE_RECEIVED  0x39 /* CAS Group C tone received */
#define CAS_R2_DIALING_DONE           0x3A /* Outgoing dialing complete */
#endif
#if defined(CAS_TAIWAN_MDR1)
#define CAS_TAIWAN_MDR1_CALL_STARTING 0x34 /* A seizure has been sent/rcvd */
#define CAS_TAIWAN_MDR1_CALL_ABORTED  0x35 /* A seizure has been sent/rcvd */
#define CAS_TAIWAN_MDR1_DIALING_DONE  0x36 /* Outgoing dialing complete    */
#define CAS_TAIWAN_MDR1_ANSWERED      0x37 /* We have answered the call    */
#endif
#define SWV_INFO         0x3B  /* Send Switch variant        */
#define LINE_PARMS_IN    0x3C  /* Line parameters notification         */
#define MORE_INFO_INDICATION   0x3D  /* QSIG */
#define RESTART_INCOMPAT_STATE 0x3E  /* QSIG */
#define T302_TIMEOUT           0x3F

#define RESTART_STATUS   0x40

#define DISPLAY_CNAME    0x41   /* Caller ID Name information */

/*
 * Delivery needs defining somewhere
 */
#define DUMMY_DATA_IN    0x42
#define DUMMY_U_DATA_IN  0x43
#define L2_EST_IN        0x44
#define L2_EST_CF        0x45
#define L2_REL_IN        0x46
#define L2_REL_CF        0x47

/*
 *  STATUS REQUEST DEFINES (N*_STAT_RQ)
 */

#define RESTART          0x00   /* N_STAT_RQ RESTART          */
#define LAP_FLOW_OFF     0x01   /* turn off flow control      */
#define LAP_FLOW_ON      0x02   /* turn on flow control       */
#define DUMMY_DATA       0x03   /* N_STAT_RQ L2 I frame RQ    */
#define RELEASE_REQ      0x04   /* N_STAT_RQ L2 Release RQ    */
#define S3_REL_REQ       0x05   /* N_STAT_RQ S3 Release RQ    */
#define BEG_RLOOP        0x06   /* N_STAT_RQ Remote loopback  */
#define END_RLOOP        0x07   /* N_STAT_RQ Remote loopback  */
#define USART_RCVRDY_ON  0x08   /* USART Receive Ready on     */
#define USART_RCVRDY_OFF 0x09   /* USART Receive Ready off    */
#define USART_MODE_CHG   0x0A   /* USART Mode change          */
#define FLOW_OFF_LNK     0x0B   /* turn off flow control for logical link */
#define FLOW_ON_LNK      0x0C   /* turn on flow control for logical link  */
#define TEI_ASS_REQ      0x0D   /* Force removal and reassign of TEIs */
#define L2_EST_REQ       0x0E   /* N_STAT_RQ L2 Establish RQ   */
#define B_CH_OOS         0x0F   /* N_STAT_RQ Out-of-Serv B-ch  */
#define B_CH_INS         0x10   /* N_STAT_RQ Out-of-Serv B-ch  */
#define CUP_PARMS_LOAD   0x11   /* Load from Cup_parms_image area */
#define NOTIFY_RQ        0x12   /* Send NOTIFY information        */
#define GET_DLCI         0x13   /* get dlci for frame relay connection    */
#define SET_LINE_PARMS   0x14   /* Set Line parameter information          */
#define GET_LINE_PARMS   0x15   /* Get Line (& L3) parameter information   */
#define FACILITY_RQ      0x16   /* Send FACILITY information        */
#define SEND_CNAME       0x17   /* Caller ID Name information */
#define BACKUP_D_MOOS    0x30   /* PRI BACKUP D-Ch Maintenance Out-of-Service */
#define BACKUP_D_IS      0x31   /* PRI BACKUP D-Ch Maintenance In-Service */
#define DUMMY_U_DATA     0x32   /* N_STAT_RQ L2 UI frame RQ    */
#define ESS_EPSM_PRIM    0x80   /* 5ESS M&M EPSM primitive    */
#define I_DP_CONFIG_REQ  0x90   /* I_DP DP RAM addr and IRQ config rq */

#define PPP_START        0xA0   /* Start a session PPP-ML-PPP on an interface */
#define PPP_STOP         0xA1   /* Stop  a session PPP-ML-PPP on an interface */

/*
 *  Primitive command codes for the interface from
 *  the Coordinating Entity to Layer 4
 */

/* Coordinating Entity to Layer 4 Mailbox Codes                 */
#define N_CONN_IN       0x00     /* N_CONNECT_INDICATION        */
#define N_CONN_CF       0x01     /* N_CONNECT_CONFIRM           */
#define N_DISC_IN       0x02     /* N_DISCONNECT_INDICATION     */
#define N_DISC_CF       0x03     /* N_DISCONNECT_CONFIRM        */
#define N_DATA_IN       0x04     /* N_DATA_INDICATION           */
#define N_DACK_IN       0x05     /* N_DATA_ACK_INDICATION       */
#define N_EXP_IN        0x06     /* N_EXPEDITED_DATA_INDICATION */
#define N_STAT_IN       0x07     /* N_STATUS_INDICATION         */
#define N_RES_IN        0x08     /* N_RESET_INDICATION          */
#define N_RES_CF        0x09     /* N_RESET_CONFIRM             */
#define N_REL_IN        0x0A     /* N_RELEASE_INDICATION        */
#define N_SS_IN         0x10     /* N_SUPPLEMENTARY_SERVICES    */
#define N_SUS_CF        0x20     /* N_SUSPEND_CONFIRM           */
#define N_REM_CF        0x21     /* N_RESUME_CONFIRM            */
#define N_SUS_IN        0x22     /* N_SUSPEND_INDICATION        */
#define N_REM_IN        0x23     /* N_RESUME_INDICATION         */
#define N_KEYPAD_IN     0x26     /* N_KEYPAD_INDICATION         */
#define N_PDL_CF        0x30     /* N_Parameter_DownLoad_CONFIRM*/
#define N_PDL_END       0x31     /* N_Parameter_DownLoad_END    */
#define N_CONN_ACK_IN   0x32     /* N_CONN_ACK_INDICATION       */
#define N_BAP_IN        0x33     /* BACP                        */
#define N_XMIT_ACK_IN   0x34     /* Transmit Data Acknowledge   */
#define N_CALL_PROC_IN  0x35     /* N_CALL_PROCEEDING_INDICATION */
#define N_ALERT_IN      0x36     /* N_ALERTING_INDICATION        */
#define N_PROG_IN       0x37     /* N_PROGRESS_INDICATION        */
#define N_CALL_PRES_IN  0x38     /* N_CALL_PRESENT_INDICATION   */
#define N_PRI_CONTEXT_IN        0x39
#define N_PRI_CONTEXT_CF        0x3A
#define N_RAW_Q931_IN           0x40
#define N_CONGESTION_CONTROL_IN 0x41
#define N_FACILITY_IN           0x42
#define N_FACILITY_ACK_IN       0x43
#define N_FACILITY_REJ_IN       0x44
#define N_REGISTER_IN           0x45
#define N_USER_INFO_IN          0x46
#define N_GET_LAYER_PARM_CF     0x50 /* N_GET_LAYER_PARM_CONFIRM    */
#define N_GET_LAYER_STATS_CF    0x51 /* N_GET_LAYER_STATS_CONFIRM   */
#define N_GET_CALL_TABLE_CF     0x52 /* N_GET_CALL_TABLE_CONFIRM    */
#define N_MB_ADD_LINK_IND       0x60 /* MFR Bundle Add Link Ind     */
#define N_MB_REMOVE_LINK_IND    0x61 /* MFR Bundle Rem Link Ind     */
#define N_MB_ERROR_IND          0x62 /* MFR Bundle Error Indication */


/* Supplementary Services N_SS_RQ Request Types (cause[1]) */
#define SS_HOLD_RQ       0     /* Hold Request                   */
#define SS_TRANS_RQ      1     /* Transfer Request               */
#define SS_CONF_RQ       2     /* Conference Request             */
#define SS_RECONN_RQ     3     /* Reconnect Request              */
#define SS_DROP_RQ       4     /* Drop Request                   */
#define SS_FEAT_BTN_RQ   5     /* Feature Button Request         */
#define SS_SWH_RQ        6     /* Switchhook State Change Request*/
#define SS_CCBS_EN_RQ    7     /* CCBS activate request          */
#define SS_CCBS_DS_RQ    8     /* CCBS deactivate request        */
#define SS_CCBS_IN_RQ    9     /* CCBS interrogate request       */
#define SS_CCBS_CALL_RQ  10    /* CCBS recall command            */
#define SS_DIVERSION_RQ  11    /* Call diversion  CFU/CFB/CFNR   */
#define SS_DEFLECTION_RQ 12    /* Call deflection CD             */
#define SS_ECT_RQ        13    /* ECT request                    */
#define SS_TPTY_EN_RQ    14    /* 3PTY begin request             */
#define SS_TPTY_DS_RQ_HELD 15  /* 3PTY end request for Held call */
#define SS_TPTY_DS_RQ_IDLE 16  /* 3PTY end request for Idle call */
#define SS_MCID_RQ       17    /* MCID request                   */

#define SS_HOLD_ACK      18    /* Hold granted                   */
#define SS_HOLD_REJ      19    /* Hold rejected                  */
#define SS_RECONN_ACK    20    /* Reconnect granted              */
#define SS_RECONN_REJ    21    /* Reconnect rejected             */

#define SS_CT_RQ         22    /* QSIG Call Transfer request     */
#define SS_DIV_RQ        23    /* QSIG Call Diversion request    */
#define SS_MWI_RQ        24    /* Message Waiting request        */
#define SS_MWI_ACK       24    /* Message Waiting indication     */

#define SS_DEBUG         30    /* SS generic debug command       */

/* Supplementary Services N_SS_IN Indication Types (cause[1]) */
#define SS_IN_DISPLAY    0     /* Display Type                       */
#define SS_IN_FI         1     /* Feature Indication Type            */

#define SS_ACT_AOC       2     /* AOC accepted                       */
#define SS_RJE_AOC       3     /* AOC rejected/error                 */
#define SS_ERR_AOC       4     /* AOC rejected/error                 */
#define SS_INT_AOC       5     /* AOC update display Type            */

#define SS_ACT_CCBS      6     /* CCBS activated                     */
#define SS_RJE_CCBS      7     /* CCBS request rejected/refused      */
#define SS_ERR_CCBS      8     /* CCBS generic error notice          */
#define SS_ENB_CCBS      9     /* CCBS can be enabled                */
#define SS_DIS_CCBS      10    /* CCBS information is erased         */
#define SS_DCT_CCBS      11    /* CCBS deactivated                   */
#define SS_RUFREE_CCBS   12    /* CCBS remote user free              */
#define SS_BFREE_CCBS    13    /* CCBS B channel free                */

#define SS_ACT_CDIV      14    /* Call diversion accepted            */
#define SS_RJE_CDIV      15    /* Call diversion rejected            */
#define SS_ERR_CDIV      16    /* Call diversion error               */
#define SS_INT_CDIV      17    /* Call diversion information         */

#define SS_ACT_CDEF      18    /* Call deflection accepted           */
#define SS_RJE_CDEF      19    /* Call deflection rejected           */
#define SS_ERR_CDEF      20    /* Call deflection rejected           */

#define SS_ACT_ECT       21    /* ECT accepted                       */
#define SS_RJE_ECT       22    /* ECT rejected                       */
#define SS_ERR_ECT       23    /* ECT error                          */

#define SS_ACT_TPTY      24    /* 3PTY accepted                      */
#define SS_ERR_TPTY      25    /* 3PTY error                         */
#define SS_RJE_TPTY      26    /* 3PTY rejected                      */
#define SS_END_TPTY      27    /* 3PTY terminated                    */

#define SS_ACT_MCID      28    /* MCID accepted                      */
#define SS_ERR_MCID      29    /* MCID error                         */
#define SS_RJE_MCID      30    /* MCID rejected                      */

#define SS_HOLD_IN       31    /* Hold request received              */
#define SS_RETRIEVE_IN   32    /* Retrieve request received          */
#define SS_HELD_IN       33    /* Hold activated                     */
#define SS_END_HOLD_IN   34    /* Hold released (reconnect)          */

#define SS_START_TPTY_IN 35    /* 3PTY start request received        */
#define SS_END_TPTY_IN   36    /* 3PTY end request received          */

#define SS_START_CDIV_IN 37    /* Call Diversion start request received */
#define SS_END_CDIV_IN   38    /* Call Diversion end request received   */

#define SS_START_CDEF_IN 39    /* Call Deflection start request received */

#define SS_START_IM_ECT_IN  40 /* Implicit ECT request received          */
#define SS_START_EX_ECT_IN  41 /* Explicit ECT request received          */
#define SS_LINKID_ECT_IN 42    /* Link Id assignment                     */

#define SS_DROP_IN       43    /* Drop Indication                */

#define SS_CT_IN         44    /* QSIG Call Transfer request received    */
#define SS_DIV_IN        45    /* QSIG Call Diversion received    */
#define SS_MWI_IN        46    /* Message Waiting received   */

#define SS_ACT_MWI       47    /* MWI  accepted                      */
#define SS_ERR_MWI       48    /* MWI  error                         */
#define SS_RJE_MWI       49    /* MWI  rejected                      */


#define SS_IN_BLANK      0xF0  /* Blank call appearance status field */
#define SS_IN_UPDATE_SCA 0xF1  /* Update Selected Call Appear        */
/* Note: SS_IN_UPDATE_SCA only used for 5ESS Terminal Management SS  */

/* RESUME & SUSPEND Confirm Types                     */
#define RESUME_ACK       0
#define RESUME_REJ       1
#define SUSPEND_ACK      0
#define SUSPEND_REJ      1

#define CONNPARMS_LEN    LBUFLEN  /* total connparms struct length */

#endif  /* end of if !defined(__L4CEL3_H_) */
