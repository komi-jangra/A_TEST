/****************************************************************************/
/*                                                                          */
/*      Copyright (C) 1992-2003 by TeleSoft International, Inc.             */
/*                                                                          */
/*      These computer program listings and specifications,                 */
/*      herein, are the property of TeleSoft International, Inc.            */
/*      and shall not be reproduced or copied or used in whole or in        */
/*      part without written permission from TeleSoft International, Inc.   */
/*                                                                          */
/****************************************************************************/
#if !defined(__CEME_H_)
#define __CEME_H_

/* struct containing counts of LAP message types sent and received */
struct lapd_stats
{
   unsigned int txI;
   unsigned int rxI;
   unsigned int txUI;
   unsigned int rxUI;
   unsigned int txRR_C;
   unsigned int rxRR_C;
   unsigned int txRR_R;
   unsigned int rxRR_R;
   unsigned int txREJ_C;
   unsigned int rxREJ_C;
   unsigned int txREJ_R;
   unsigned int rxREJ_R;
   unsigned int txRNR_C;
   unsigned int rxRNR_C;
   unsigned int txRNR_R;
   unsigned int rxRNR_R;
   unsigned int num_decode_fail;
   unsigned int num_encode_fail;
};

/* L4-to-CE Power-On Reset Parameters */
/* NOTE: If file "ceme\sh_mem.asm" is used (Intel 80X8X processors),
 *       each time that a member is added or removed from this cup_parms
 *       structure or a define constant used in this struct (e.g.,
 *       MAX_B_CH, MAX_SPID_LEN, DN_MAXLEN, MAXPVC) is changed,
 *       "ceme\sh_mem.asm" must have the Shmem_cup_parm array size
 *       (declared in bytes) adjusted.
 *
 *       l4_ifc.h OFFSETs into shared mem must also be changed if
 *       the TsLink3 PC plug-in card example Layer 4 software is used
 */

/******* cup_parms STRUCTURE DEFINITION *******/
struct cup_parms
{
   /* array of Permanent Virtual Circuit descriptors */
   struct
   {
      unsigned short lci;        /* Logical Channel Identifier             */
      unsigned short chantype;   /* Interface (top byte) | chan_num (low)  */
   } pvc[MAXPVC];

   /* see X.25 Appendix A for discussion of Logical Channel ID's (LCI's) */
   unsigned short d2minlci;      /* X.25 D-Channel 2-way Minimum LCI     */
   unsigned short d2maxlci;      /* X.25 D-Channel 2-way Maximum LCI     */
   unsigned short B1_2minlci;    /* X.25 B-Channel One 2-way Minimum LCI */
   unsigned short B1_2maxlci;    /* X.25 B-Channel One 2-way Maximum LCI */
   unsigned short B2_2minlci;    /* X.25 B-Channel Two 2-way Minimum LCI */
   unsigned short B2_2maxlci;    /* X.25 B-Channel Two 2-way Maximum LCI */
   unsigned short d1minlci;      /* X.25 D-Channel 1-way Out Min LCI     */
   unsigned short d1maxlci;      /* X.25 D-Channel 1-way Out Max LCI     */
   unsigned short B1_1minlci;    /* X.25 B-Channel One 1-way Out Min LCI */
   unsigned short B1_1maxlci;    /* X.25 B-Channel One 1-way Out Max LCI */
   unsigned short B2_1minlci;    /* X.25 B-Channel Two 1-way Out Min LCI */
   unsigned short B2_1maxlci;    /* X.25 B-Channel Two 1-way Out Max LCI */

   /* cnt of X.25 Permanent Virtual Circuits active in pvc[] */
   unsigned short pvccount;

#if defined(FRM_RLY)
   unsigned short xni_frag;      /* FR XNI fragmetation? TRUE or FALSE */
   unsigned short xni_frag_size; /* FR XNI fragment size               */
   unsigned short bi_dir_poll;   /* Bi-Directional Polling? TRUE/FALSE */
#endif

   /* run-time switch selection options depend on which switch
    * variants have been selected during optional "switch variant
    * filtering" and subsequently compiled into the code.
    *
    * The valid switch variant model options are:
    *
    *     NULL                      SWV_NULL     = 127
    *     AT&T 5ESS                 SWV_5ESS     = 0
    *     Northern Telecom DMS-100  SWV_DMS_100  = 1
    *     ETSI NET3                 SWV_NET3     = 2
    *     DBP 1TR6                  SWV_1TR6     = 3
    *     NTT INSnet64              SWV_INS64    = 4
    *     US National ISDN-1        SWV_US_NI1   = 5
    *     France Telecom VNx        SWV_VNX      = 6
    *     US National ISDN-2        SWV_US_NI2   = 7
    *     Australia TS013.1         SWV_AUS      = 8
    *     Dynamic NA Auto Config    SWV_AUTO_CFG = 9
    *     AT&T 4ESS (PRI)           SWV_4ESS     = 10
    *     Australia TS014.1 (PRI)   SWV_AUS_PRI  = 11
    *     AT&T 5ESS (PRI)           SWV_5ESS_PRI = 12
    *     ETSI NET5 PRI             SWV_NET5     = 13
    *     Japan INS-NET 1500 (PRI)  SWV_INS_PRI  = 14
    *     Northern Tel DMS-100(PRI) SWV_DMS_PRI  = 15
    *     US National ISDN-2 (PRI)  SWV_US_NI2_PRI = 16
    *     SWV_CAS_T1_WINK_START = 17 => T1 CAS WINK START (Robbed-Bit)
    *     SWV_CAS_T1_FXS_GROUND_START=18 => T1 CAS FXS GROUND START(Robbed-Bit)
    *     SWV_CAS_T1_FXS_LOOP_START = 19 => T1 CAS FXS LOOP START (Robbed-Bit)
    *     SWV_CAS_E1_R2_ITU = 20 => E1 CAS ITU-T R2 GENERIC
    *     SWV_QSIG = 21 => QSIG
    *     IDSL (U or S ISDN DSL)    SWV_IDSL     = 22
    *     HONG KONG PRI (subvariant of SWV_NET5)  SWV_HONG_KONG_PRI = 23
    *     NOTE:  If cup_parms_load() is NOT used, Hong_Kong_PRI[] must be
    *     explicitly set to 0 or 1 and the variant set to SWV_NET5
    *     Argentina  R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_ARGENTINA = 24
    *     Brazil     R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_BRAZIL    = 25
    *     Chile      R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_CHILE     = 26
    *     China      R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_CHINA     = 27
    *     Colombia   R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_COLOMBIA  = 28
    *     Korea      R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_KOREA     = 29
    *     Mexico     R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_MEXICO    = 30
    *     Nicaragua  R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_NICARAGUA = 31
    *     Singapore  R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_SINGAPORE = 32
    *     "Generic"  R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_GENERIC   = 39
    *     India      R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_INDIA     = 40
    *     Bangladesh R2 (subvariant of SWV_CAS_E1_R2_ITU)  SWV_R2_INDIA     = 41
    *     NOTE:  If cup_parms_load() is NOT used, R2_variant[] must be
    *     explicitly set to the appropriate value and the variant set to
    *     SWV_CAS_E1_R2_ITU.
    *     SWV_CAS_T1_FXO = 33 => T1 CAS FXO (Robbed-Bit)
    *     SWV_CAS_TAIWAN_MDR1_T1 = 34 => T1 CAS Taiwan MDR1
    *     SWV_CAS_TAIWAN_MDR1_E1 = 35 => E1 CAS Taiwan MDR1
    *     HONG KONG BRI (subvariant of SWV_NET3)  SWV_HONG_KONG_BRI = 36
    *     SWV_CAS_T1_IMMED_START = 37 => T1 CAS Immediate Start (Robbed-Bit)
    *     SWV_CAS_T1_DELAY_DIAL = 38 => T1 CAS Delay Dial (Robbed-Bit)
    *     NOTE:  If cup_parms_load() is NOT used, Hong_Kong_BRI[] must be
    *     explicitly set to 0 or 1 and the variant set to SWV_NET3
    *     NOTE:  Value of 39 used for SWV_R2_GENERIC above
    *     NOTE:  Value of 40 used for SWV_R2_INDIA above
    *     NOTE:  Value of 41 used for SWV_R2_BANGLADESH above
    */
   unsigned char swv_model;           /* Switch variant model */

   /*
    *  multipoint selection:
    *  =0 => pt-to-pt
    *  =1 => endpt initializing
    *        multipt
    *  =2 => multipt + US NI-1 MLHG
    */
   unsigned char multipt;

   /* Service Profile Identifier for multipt operation     */
   unsigned char spid[2][MAX_SPID_LEN + 1];

   /*  ss_config = 0  => No Supplementary Services active
    *            = 1  => BRI AT&T 5ESS Type A Supplementary Services active
    *            = 2  => BRI AT&T 5ESS Type B Supplementary Services active
    *            = 3  => BRI AT&T 5ESS Type C Supplementary Services active
    *            = 4  => BRI AT&T 5ESS Type D Supplementary Services active
    *            = 5  => BRI US NI BASIC EKTS Supplementary Services active
    *            = 6  => BRI US NI CACH EKTS  Supplementary Services active
    *            = 7  => BRI ETSI FULL        Supplementary Services active
    *            = 8  => BRI ETSI             Supplementary Services active
    *            = 9  => PRI                  Supplementary Services active
    *            = 10 => QSIG                 Supplementary Services active
    */
   unsigned char ss_config;  /* Supplementary Services configuration type */

   /*  olap_send = 0 => NLS En-bloc sending call setup mode
    *              1 => NLS Overlap Sending call setup mode
    */
   unsigned char olap_send;

   unsigned char dn0[DN_MAXLEN];      /* Directory Number 0              */
   unsigned char dn1[DN_MAXLEN];      /* Directory Number 1              */

   /*
    *  TEI assignment defines
    *
    *  Defined          Decimal
    *  constant          value
    *  ***************  *******
    *                    0-63  Fixed TEI's
    *  AUTO_TEI           240  auto TEI negotiation selected
    *  NO_DX25_TEI        241  D-Chan X.25 not active - no TEI
    *  NO_SIG_TEI         241  Signalling TEI not active - no TEI
    *  DX25_USE_SIGTEI    242  D-Chan X.25 Use same TEI as signalling tei 0
    */
   /*
    *   Only DMS-100 and US NI-1 use more than one signalling tei -- these
    *   switches use a separate signalling TEI for each B-Channel call
    *   that is active simultaneously
    */
   unsigned char sigtei[MAX_B_CH];    /* Signalling/Maintenance TEI's     */
   unsigned char dx25tei;             /* D-Channel X.25 TEI               */

   /* valid values for the B-Channel 1 and B-Channel 2 data service
    * selection global variables B1_ch_data and B2_ch_data:
    *  =0 => no B-Ch data calls,
    *  =1 => Nailed-UP (NUP) B-Ch calls
    *  =2 => Circuit-SWitched X.25 calls
    *  =3 => ON-Demand X.25 calls
    *  =4 => Nailed-UP V.120 calls
    *  =5 => Circuit-SWitched V.120 calls
    *  =6 => Circuit-SWitched V.110 calls
    *  =7 => Circuit-SWitched RAW-HDLC calls
    *  =8 => Circuit-SWitched PPP calls
    */
   unsigned char B1_ch_data;          /* B-Channel 1 data service */
   unsigned char B2_ch_data;          /* B-Channel 2 data service */

   unsigned char ss_max_ca_ces0;      /*
                                       *  Supplementary Services max
                                       *  Call Appearance button number
                                       *  for signalling TEI/CES 0 (US NI only)
                                       *  Call Appearance button numbers
                                       *  greater than this value are used
                                       *  for signalling TEI/CES 1 (US NI only)
                                       */
   unsigned char ss_max_button;       /*
                                       *  Supplementary Services max
                                       *  feature button number
                                       */
   unsigned char ss_max_call_appear;  /*
                                       *  Supplementary Services max
                                       *  Call Appearance button number.
                                       */
   /*
    * Note: The Call Appearance buttons are special (reserved) feature
    *       buttons numbered 1 through ss_max_call_appear.
    */

};

/*
 *  struct type ceprivate - all internal (private) Coordinating Entity
 *                          variables
 */
#ifdef ANKUR
struct ceprivate
{
   /*
    *  Connection Table - each table entry (struct array element) associates
    *  all parameters for a given logical connection
    */
   struct conntbl
   {
      unsigned short chantype;  /* Interface (top byte) | chan_num (low)   */
      unsigned short lci;       /* NLP Logical Channel Identifier          */
      unsigned short l3_pkt_size; /* Layer 3 packet size                   */
      unsigned short l3_reset_time; /* Layer 3 T12/T22 timer               */
      unsigned short l4_ifc;     /* L4 interface being used by this connect.*/
                                /*  The upper byte if this field indicates */
                                /*  the L4 interface type. Possible types: */
                                /*  L4_USART, L4_INF, L4_POTS, L4_ROUTER,  */
                                /*  etc. The lower byte is the L4 inter-   */
                                /*  face port number.                      */
      unsigned short profile;   /* PPP profile information */
      union
      {
         unsigned char tei;     /* Terminal Endpoint Identifier            */
         unsigned short dlci;   /* Data Link Connection Identifier         */
      } tei_select;
      unsigned char connstate;  /* CONNection STATE                        */
      unsigned char voice_data; /* VOICE or DATA indicator                 */
      unsigned char svctype;    /* data call SerViCe TYPE                  */
      unsigned char ces;        /* Connection Endpoint Suffix              */
      unsigned char l3_window_size; /* Layer 3 window size                 */
      unsigned char l3_throughput;  /* Layer 3 throughput (as per 7.2.2.2) */
      unsigned char sapi;       /* Service Access Point Identifier         */
      unsigned char bch_alloc;  /* If non-zero, a B-channel has been alloc */
#if defined(FRM_RLY)
      unsigned char pvc;
#endif
   } conntbl[MAXCONNS];

   unsigned char *dtmf_addr[NUM_IFC];   /* DTMF dial digit buf address    */

   /* refnum of buf currently in use in L4-to-CE direction  */
   unsigned short L4CErefnum;
   /* refnum of buf currently in use in CE-to-L4 direction  */
   unsigned short CEL4refnum;
   /* connid of voice call in progress (if any)             */
#if defined(MULT_VOICE)
   unsigned short voice1_connid[NUM_IFC];
   unsigned short voice2_connid[NUM_IFC];
#else
   unsigned short voice_connid[NUM_IFC];
#endif
   /* Reference Number (Ri) for pending Identity Request */
   unsigned short Ri_pend[NUM_IFC][MAX_TEI_CNT];
   /* Circuit-SWitched NLS Connid       */
   unsigned short csw_connid[NUM_IFC][HDLC_PCHAN];
   unsigned short dtmf_cnt[NUM_IFC];    /* DTMF dial digit total cnt      */
   unsigned short dtmf_idx[NUM_IFC];    /* DTMF dial digit index into buf */
   unsigned short dtmf_refnum[NUM_IFC]; /* DTMF dial digit buf refnum     */

   unsigned char ucDchState;
   unsigned char cestate[NUM_IFC];     /* Coordinating Entity global state */
   /* CCITT Line Activation Retry Cnt  */
   unsigned char activ_retry_cnt[NUM_IFC];
   unsigned char CEL4inuse;       /* =1 => CEL4 mailbox in use        */

   /*
    *  current DSC LIU B-Channels 1 and 2 enable/disable state
    *  (Note: bch_enab[0] not used at present)
    */
   unsigned char bch_enab[NUM_IFC][3];

   /* TEI Administration Parameters */
   /* id_rq_pend indicates whether TEI Admin Identity Request is pending */
   unsigned char id_rq_pend[NUM_IFC][MAX_TEI_CNT];

   /* TEI Admin N202 Transmission Count */
   unsigned char N202_cnt[NUM_IFC][MAX_TEI_CNT];

   /* X.25 Logical Channel Identifier (LCI) allocation arrays         */
   /* D-Ch 1-way outgoing LCIs */
   unsigned char d1lci[NUM_IFC][(MAX_D1_LCI / 8) + 1];
   /* D-Ch 2-way LCIs          */
   unsigned char d2lci[NUM_IFC][(MAX_D2_LCI / 8) + 1];
   /* B-Ch 1-way outgoing LCIs */
   unsigned char B1_1lci[NUM_IFC][(MAX_B1_LCI / 8) + 1];
   /* B-Ch 2-way LCIs          */
   unsigned char B1_2lci[NUM_IFC][(MAX_B2_LCI / 8) + 1];
   /* B-Ch 1-way outgoing LCIs */
   unsigned char B2_1lci[NUM_IFC][(MAX2_B1_LCI / 8) + 1];
   /* B-Ch 2-way LCIs          */
   unsigned char B2_2lci[NUM_IFC][(MAX2_B2_LCI / 8) + 1];

   unsigned char csw_data_cnt[NUM_IFC][HDLC_PCHAN];
                                 /*
                                  *  Circuit-SWitched data active
                                  *  logical channel count -
                                  *    = 0 => Data B-Ch hardware disabled
                                  *    > 0 => Data B-Ch hardware enabled
                                  *  Only V.120 uses this method at present
                                  */
   unsigned char dx25_use_sigtei[NUM_IFC];
                                 /*
                                  *  Remember whether original
                                  *  dx25tei == DX25_USE_SIGTEI
                                  */
};
#endif //ANKUR

#define CE_L4_BUF_IDLE  0xFF     /* no CEL4refum in use this prim     */

/* CONNECTION STATE "connstate" defines */
#define IDLE_CONN             0    /* idle connection                 */
#define ACTIVE_CONN        0x80    /* connid is active (in use)       */
#define CSW_CONN_IN_PEND   0x01    /*
                                    *  Circuit-SWitched data call NLP
                                    *  connect indication call setup pending
                                    */
#define CSW_DISC_PEND      0x02    /*
                                    *  Circuit-SWitched data call NLS
                                    *  call teardown is pending
                                    */
#define CSW_CONN_RQ_PEND   0x04    /*
                                    *  Circuit-SWitched data call NLP
                                    *  connect request call setup pending
                                    */

/* Coordinating Entity global state defines */
/* NOTE: The low-order bit of cestate is reserved for OFFHOOK/ONHOOK  */
#define VOICE_ACTIVE       0x80    /* voice connection active         */

/* LCI allocation array defines */
#define LCI_READY      0     /* LCI in X.25 "ready" state, i.e., idle */
#define LCI_IN_USE     1

/* TEI assignment defines */
#define AUTO_TEI        240  /* auto TEI negotiation selected         */
#define NO_DX25_TEI     241  /* D-Chan X.25 not active - no TEI       */
#define NO_SIG_TEI      241  /* D-Chan X.25 not active - no TEI       */
#define DX25_USE_SIGTEI 242  /* D-Chan X.25 use signalling TEI        */

/* North American Auto-configuration switch variant detect states     */
#define AUTO_CFG_NULL      0 /* Beginning state for detection         */
#define AUTO_CFG_TIMER     1 /* T_WAIT_TIMER started for TEIs         */
#define AUTO_CFG_EST_RQ    2 /* Establishment requested               */
#define AUTO_CFG_SPID_SENT 3 /* DMS-100/NI-1 SPID INFO message sent   */
#define AUTO_CFG_MIM_SENT  4 /* AT&T Custom MIM message sent          */
#define AUTO_CFG_NI1_SPID  7 /* NorTel/NI-1 SPID accepted             */
#define AUTO_CFG_DMS_PVC   8 /* NorTel Custom/NI-1 PVC accepted       */
#define AUTO_CFG_ATT_MIM   9 /* AT&T Custom MIM received or accepted  */
#define AUTO_CFG_5ESS   0x10 /* AT&T Custom determined to be variant  */
#define AUTO_CFG_DMS    0x11 /* NorTel Custom determined to be variant */
#define AUTO_CFG_ATTNI1 0x15 /* Non-NorTel US NI-1 is variant (ATT/Siemens) */
#define AUTO_CFG_FAIL   0xFF /* Could not figure out switch variant   */

#define LIU_ST_INCR   2   /* DSC LIU STATUS REG STATUS INCREMENT      */
#define MAP_SIDE      3   /* DSC MAP SIDE ARGUMENT FOR ALLOCB LLD CMD */

#define SBP1_SIDE     6   /* DSC SBP1 SIDE ARGUMENT FOR ALLOC B1 LLD CMD */

#if defined(HSCX) || (defined(M302) || defined(M360) || defined(M860)) 
#define SBP2_SIDE     7   /* DSC SBP2 SIDE ARGUMENT FOR ALLOC B2 LLD CMD */
#else
#define SBP2_SIDE     6   /* DSC SBP2 SIDE ARGUMENT FOR ALLOC B2 LLD CMD */
#endif

#define B1_MCR     0   /* DSC MUX CTRL REG # used for B-Ch 1 */
#define B2_MCR     1   /* DSC MUX CTRL REG # used for B-Ch 2 */

/* L4 interface types in conn_tbl */
#define L4_USART     0x1100    /* USART type L4 interface */
#define L4_INF       0x2200    /* Shared memory L4 mailbox */
#define L4_POTS      0x3300    /* POTS type L4 interface */
#define L4_IPC       0x4400    /* CEL4 IPC interface */
#define L4_ROUTER    0x4400    /* Interface to router software at L4 */

/*
**    DN blacklisting structures
**
**    Note: implemented only for SWV_INS64
*/
#define ERROR_TM_RECOV         1
#define ERROR_TRX_DISC_RCV     2
#define ERROR_INVALID_NR       3
#define ERROR_INCORRECT_FRAME  4
#define ERROR_DM_RCV  5
#define ERROR_FRMR_RCV  6
#define ERROR_RED_HAND  7



struct repeat_call_list
{
   unsigned short connid;
   unsigned short guard_time;
   unsigned char  in_use;
   unsigned char  dn_len;
   unsigned char  dialed_dn[DN_MAXLEN];
   unsigned char  subdn_len;
   unsigned char  dialed_subdn[SDN_MAXLEN];
};


#endif  /* end of if !defined(__CEME_H_) */
