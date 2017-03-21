/*******************************************************************************
**      FILE NAME:
**          lbs.h
**
**      DESCRIPTION:
**              Defines required by Bssap Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/

#ifndef __LBSH__
#define __LBSH__

#define LBS_SW_ITU           1       /* switch - itu */ /*same value as in PSF:CMZSDS_SWTCH_ITU */
#define LBS_SW_ANSI          2       /* switch - ansi 88 */
#define LBS_SW_TST           3       /* switch - test */
/* Network Sap types */

#define SAP_MTP           0          /* MTP Sap */
#define SAP_SCCP          1          /* SCCP Sap */
#define SAP_RM            2          /* RM Sap if PSIF enabled */
#define SAP_M3UA          3          /* M3UA Sap */
#define SAP_APP           4          /* M3UA Sap */

/* subsystem field */

#define SSF_INTER        0           /* international subsystem field */
#define SSF_NAT          2           /* national subsystem field */

/* Debugger flags */
#define BSDBGMASK_PROG  (DBGMASK_LYR << 0 ) /* progress of handling an Event */
#define BSDBGMASK_WARN  (DBGMASK_LYR << 1 ) /* warning , not critical for an event */
#define BSDBGMASK_CERR  (DBGMASK_LYR << 2 ) /* Event specific err*/
#define BSDBGMASK_ERR   (DBGMASK_LYR << 3 ) /* Global error */
#define BSDBGMASK_TMR   (DBGMASK_LYR << 4 ) /* Timer related */
#define BSDBGMASK_STATE (DBGMASK_LYR << 5 ) /* state transition */
#define BSDBGMASK_MF    (DBGMASK_LYR << 6 ) /* mf related prog/warn/error */

/* Type of alarm diagnostic values */

#define LBS_USTA_DGNVAL_NONE        0   /* event identifier */
#define LBS_USTA_DGNVAL_EVENT       1   /* event identifier */
#define LBS_USTA_DGNVAL_SPID        2   /* spId of a SAP */
#define LBS_USTA_DGNVAL_SUID        3   /* suId of a SAP */
#define LBS_USTA_DGNVAL_SPINSTID    4   /* suInstId of a connection */
#define LBS_USTA_DGNVAL_SUINSTID    5   /* spInstId of a connection */
#define LBS_USTA_DGNVAL_CIC         6   /* CIC value of a circuit */
#define LBS_USTA_DGNVAL_DPC         7   /* DPC */
#define LBS_USTA_DGNVAL_BSCID       8  
#define LBS_USTA_DGNVAL_SWTCH       9  /* protocol variant */
#define LBS_USTA_DGNVAL_MSGTYPE     10  
#define LBS_USTA_DGNVAL_STATE       11  /* Connection type */
#define LBS_USTA_DGNVAL_INTF        12   /* Interface */
#define LBS_USTA_DGNVAL_SSN         13  /* Connection type */

#define LBS_USTA_MAX_DGNVAL  4 /* max. number of diagnostics values 
                                        */
/* establishement */

#define E_DEMAND       0x00  /* demand */
#define E_PERM         0x01  /* permanent */

#define OE_EVEN        0x00  /* even number of address signals */
#define OE_ODD         0x01  /* odd number of address signals */

/* interpretation */

#define INT_NAT         0x0  /* national */
#define INT_FIRST      0x04  /* first high layer characteristics */


/* Encoding Schemes */

#define ES_UNKN          0x00      /* Unknown */
#define ES_BCDODD        0x01      /* BCD Odd */
#define ES_BCDEVEN       0x02      /* BCD Even */

#define NAT_IND          0x01      /* National Indication */
#define INAT_IND         0x00      /* International Indication */


/* Sn Management Events */
#define EVTLBSCFGREQ     0x3c             /* Configuration request */
#define EVTLBSSTAREQ     0x40             /* Status request */
#define EVTLBSSTACFM     0x41             /* Status confirm */
#define EVTLBSSTAIND     0x42             /* Status indication */
#define EVTLBSSTSREQ     0x44             /* Statistics request */
#define EVTLBSSTSCFM     0x45             /* Statistics confirm */
#define EVTLBSTRCIND     0x48             /* Trace indication */
#define EVTLBSCNTRLREQ   0x4c             /* Control request */
#define EVTLBSACNTIND    0x56             /* Accounting indication */
#define EVTLBSCFGCFM     0xd0             /* Config confirm  */
#define EVTLBSCNTRLCFM   0xd1             /* Control confirm */


/* BSSAP unsolicited status indications */

/* BSSAP specific categories */

/* BSSAP specific events */
#define   LBS_EVENT_TIME_OUT_NO_BLOCK_ACK_RECEIVED          2150
#define   LBS_EVENT_TIME_OUT_NO_UNBLOCK_ACK_RECEIVED        2151
#define   LBS_EVENT_TIME_OUT_NO_RESET_ACK_RECEIVED          2152
#define   LBS_EVENT_TIME_OUT_NO_RESET_CKT_ACK_RECEIVED      2153
#define   LBS_EVENT_TIME_OUT_NO_RESETIP_ACK_RECEIVED        2154
#define   LBS_EVENT_WRONG_MSG_DIRECTION                     2155
#define   LBS_EVENT_WRONG_MSG_TYPE                          2156
#define   LBS_EVENT_REMOTE_SUBSYSTEM_DOWN                   2157
#define   LBS_EVENT_NETWORK_DOWN                            2158
#define   LBS_EVENT_NEITHER_MAP_NOR_DTAP_MSG                2159
#define   LBS_EVENT_FAILED_TO_DISPATCH_MSG_TO_PEER          2160
#define   LBS_EVENT_CONFIG_DATA_NOT_FOUND                   2161
#define   LBS_EVENT_FAIL_TO_REMOVE_DPC                      2162 /* This will be called when removing interface */
#define   LBS_EVENT_CAN_NOT_ADD_DPC                         2163
#define   LBS_EVENT_CONTEXT_ALREADY_EXIST                   2164
#define   LBS_EVENT_CIC_CONTEXT_NOT_FOUND                   2165
#define   LBS_EVENT_FAILED_TO_REMOVE_CONTEXT                2166 /* This will be called when removing CIC */
#define   LBS_EVENT_COULD_NOT_MODIFIED_CONTEXT              2167
#define   LBS_EVENT_CALL_IN_BUSY_STATE                      2168
#define   LBS_EVENT_CIC_IN_BLOCK_STATE                      2169
#define   LBS_EVENT_CIC_POOL_MISMATCH                       2170
#define   LBS_EVENT_INVALID_CIC                             2171

/* BSSAP specific causes values */
#define LBS_CAUSE_BLOCK              (LCM_CAUSE_LYR_SPECIFIC + 1)
#define LBS_CAUSE_CGUREQ             (LCM_CAUSE_LYR_SPECIFIC + 2)
#define LBS_CAUSE_CIR_MNTACK         (LCM_CAUSE_LYR_SPECIFIC + 3)
#define LBS_CAUSE_CIR_MNTREQ         (LCM_CAUSE_LYR_SPECIFIC + 4)
#define LBS_CAUSE_CONG_LVL1          (LCM_CAUSE_LYR_SPECIFIC + 5)
#define LBS_CAUSE_CONG_LVL2          (LCM_CAUSE_LYR_SPECIFIC + 6)
#define LBS_CAUSE_INV_ADDRS          (LCM_CAUSE_LYR_SPECIFIC + 7)
#define LBS_CAUSE_INV_CGU            (LCM_CAUSE_LYR_SPECIFIC + 8)
#define LBS_CAUSE_INV_CQM            (LCM_CAUSE_LYR_SPECIFIC + 9)
#define LBS_CAUSE_T12_INACTIVE       (LCM_CAUSE_LYR_SPECIFIC + 10)
#define LBS_CAUSE_T14_INACTIVE       (LCM_CAUSE_LYR_SPECIFIC + 11)
#define LBS_CAUSE_T16_INACTIVE       (LCM_CAUSE_LYR_SPECIFIC + 12)
#define LBS_CAUSE_UNEQP_CIR          (LCM_CAUSE_LYR_SPECIFIC + 13)
#define LBS_CAUSE_INV_CDPTY          (LCM_CAUSE_LYR_SPECIFIC + 14)
#define LBS_CAUSE_INV_TNS            (LCM_CAUSE_LYR_SPECIFIC + 15)
#define LBS_CAUSE_SUINSTID_MISMATCH  (LCM_CAUSE_LYR_SPECIFIC + 16)
#define LBS_CAUSE_UNBLOCK            (LCM_CAUSE_LYR_SPECIFIC + 17)
#define LBS_CAUSE_NO_CIRCUIT         (LCM_CAUSE_LYR_SPECIFIC + 18)
#define LBS_CAUSE_INV_CIRCUIT        (LCM_CAUSE_LYR_SPECIFIC + 19)

#define LBS_CAUSE_INV_NW_RESOURCE    (LCM_CAUSE_LYR_SPECIFIC + 21)
#define LBS_CAUSE_CIC_BUSY           (LCM_CAUSE_LYR_SPECIFIC + 22)
#define LBS_CAUSE_RMT_BLKED          (LCM_CAUSE_LYR_SPECIFIC + 23)
#define LBS_CAUSE_CAL_REF            (LCM_CAUSE_LYR_SPECIFIC + 24)
#define LBS_CAUSE_NO_MEMORY          (LCM_CAUSE_LYR_SPECIFIC + 25)
#define LBS_CAUSE_INV_MSAP           (LCM_CAUSE_LYR_SPECIFIC + 26)
#define LBS_CAUSE_CIC_IDLE           (LCM_CAUSE_LYR_SPECIFIC + 28)
#define LBS_CAUSE_INV_SUINSTID       (LCM_CAUSE_LYR_SPECIFIC + 29)
#define LBS_CAUSE_UNKNOWN_SUINSTID   (LCM_CAUSE_LYR_SPECIFIC + 30)
#define LBS_CAUSE_INV_EVNT           (LCM_CAUSE_LYR_SPECIFIC + 32)
#define LBS_CAUSE_AVAILABLE          (LCM_CAUSE_LYR_SPECIFIC + 33)
#define LBS_CAUSE_UNAVAILABLE        (LCM_CAUSE_LYR_SPECIFIC + 34)
#define LBS_CAUSE_UNEQUIPPED         (LCM_CAUSE_LYR_SPECIFIC + 35)
#define LBS_CAUSE_INV_SSAP           (LCM_CAUSE_LYR_SPECIFIC + 36)
#define LBS_CAUSE_INVCGBREQ          (LCM_CAUSE_LYR_SPECIFIC + 41)
#define LBS_CAUSE_CIC_STATE_MISMATCH (LCM_CAUSE_LYR_SPECIFIC + 43)
#define LBS_CAUSE_INV_CGB            (LCM_CAUSE_LYR_SPECIFIC + 46)
#define LBS_CAUSE_INV_CGBRSP         (LCM_CAUSE_LYR_SPECIFIC + 47)
#define LBS_CAUSE_INV_CGURSP         (LCM_CAUSE_LYR_SPECIFIC + 49)
#define LBS_CAUSE_INV_RANGE          (LCM_CAUSE_LYR_SPECIFIC + 51)
#define LBS_CAUSE_TMR_EXP            (LCM_CAUSE_LYR_SPECIFIC + 56)
#define LBS_CAUSE_INV_VARIANT        (LCM_CAUSE_LYR_SPECIFIC + 57)
#define LBS_CAUSE_FAILED             (LCM_CAUSE_LYR_SPECIFIC + 58)
#define LBS_CAUSE_SUCCESS            (LCM_CAUSE_LYR_SPECIFIC + 59)
#define LBS_CAUSE_WRONG_CLLI         (LCM_CAUSE_LYR_SPECIFIC + 60)
#define LBS_CAUSE_UBL_ON_IDLE_CIC    (LCM_CAUSE_LYR_SPECIFIC + 61)
#define LBS_CAUSE_INV_CGSMTI         (LCM_CAUSE_LYR_SPECIFIC + 62)
#define LBS_CAUSE_INV_RNGORSTATUS    (LCM_CAUSE_LYR_SPECIFIC + 63)
#define LBS_CAUSE_INV_CHRGINFO       (LCM_CAUSE_LYR_SPECIFIC + 64)
#define LBS_CAUSE_CONG_LVL3          (LCM_CAUSE_LYR_SPECIFIC + 65)
#define LBS_CAUSE_INV_INTF           (LCM_CAUSE_LYR_SPECIFIC + 66)

#define LBS_CAUSE_PAUSE              (LCM_CAUSE_LYR_SPECIFIC + 67)
#define LBS_CAUSE_RESUME             (LCM_CAUSE_LYR_SPECIFIC + 68)
#define LBS_CAUSE_STPCONG            (LCM_CAUSE_LYR_SPECIFIC + 69)
#define LBS_CAUSE_CONG_LVL0          (LCM_CAUSE_LYR_SPECIFIC + 70)

#define LBS_CAUSE_INV_START_CIC       (LCM_CAUSE_LYR_SPECIFIC + 71) 
            /*  wrong starting cic if checking Q763 table 3 is required*/
#define LBS_CAUSE_NON_CNTCIC_BUSY    (LCM_CAUSE_LYR_SPECIFIC + 72) 
            /* Connection initiation for multirate call with non-controlling 
             * cic busy */
#define LBS_CAUSE_CIC_CAM_MISMATCH   (LCM_CAUSE_LYR_SPECIFIC + 73) 
            /* Mismatch between CIC and CAM          */
#define LBS_CAUSE_UNEX_CAM           (LCM_CAUSE_LYR_SPECIFIC + 74) 
            /* Unexpected CAM for a ckt supporting only contiguous calls */
#define LBS_CAUSE_EVNT_ON_NON_CNTCIC (LCM_CAUSE_LYR_SPECIFIC + 75) 
            /* Recieved event on non-contiguous cic  */
#define LBS_CAUSE_CIR_SPINST_MISMATCH (LCM_CAUSE_LYR_SPECIFIC + 76) 
            /* Mismatch between spInstId with the controlling circuit */
#define LBS_CAUSE_N_CAM_MISMATCH    (LCM_CAUSE_LYR_SPECIFIC + 77) 
            /* Mismatch between N and CAM          */
#define LBS_CAUSE_RSCONBLK    (LCM_CAUSE_LYR_SPECIFIC + 78) 
            /* BSSAP reset the ckt when ckt is locally blocked */
#define LBS_CAUSE_CGB         (LCM_CAUSE_LYR_SPECIFIC + 79) 

/***** additional events for StaInd - OLD (for backward compatibility) ****/
#define BSSAP_INV        60             /* invalid bssap SAP */
#define BSMSAP_INV        61             /* invalid mtp3 SAP */
#define BSSSAP_INV        62             /* invalid sccp SAP */
#define BSMTP_EVTINV      63             /* invalid mtp3 status event */
#define BSGEN_CFG_NOK     64             /* general configuration failed */
#define BSGEN_CFG_OK      65             /* general configuration succeded */
#define BSSAP_CFG_NOK    66             /* bssap SAP configuration failed */
#define BSSAP_CFG_OK     67             /* bssap SAP configuration succeded */
#define BSNSAP_CFG_NOK    68             /* network SAP configuration failed */
#define BSNSAP_CFG_OK     69             /* network SAP configuration succdd */
#define BSCIR_CFG_NOK     70             /* circuit configuration failed */
#define BSCIR_CFG_OK      71             /* circuit SAP configuration succdd */
#define BSROUT_CFG_NOK    72             /* route configuration failed */
#define BSROUT_CFG_OK     73             /* route SAP configuration succeded */
#define BSDELROUT_CFG_NOK 74             /* delete route cofnig failed */
#define BSDELROUT_CFG_OK  75             /* delete route SAP cofnig succeded */
#define BS_STA_NOK        76             /* status failed */
#define BS_STA_OK         77             /* status succdd */
#define BS_STS_NOK        78             /* statistic request failed */
#define BS_STS_OK         79             /* statistic request succeded */
#define BS_CNTRL_NOK      80             /* control request failed */
#define BS_STA_NODBUFF    81             /* no dynamic buffer available */
#define BSCIC_INV         82             /* invalid CIC */
#define BS_CNTRL_OK       83             /* control request succeded */
#define BSMSAP_UBND       84             /* MTP-3 SAP unbound */

#define BS_CIR_STOUTSYNC  85          /* circuit states out of sync. */
#define BS_CIR_UNEQPD     86          /* circuit unequipped          */
#define BS_CIR_BLOCK      87          /* circuit blocked             */
#define BS_CIR_TMREXP     88          /* circuit timer expired       */
#define BS_CIR_INVCON     89          /* circuit state prohibits a conneciton */
#define BS_CIR_INVMSG     90          /* invalid msg. for this state of cir. */
#define BS_CG_INVACK      91          /* grp ack does not contain all status */
#define BS_ALM_NWSNDFAIL  92          /* can not send PDU to network */
#define BS_CIR_IDLE       93          /* circuit idled */

#define BS_CIRGRP_BLOCK   94          /* circuit group block */ 

#define BS_STINTF_CFG_OK    95  /* bssap INTF cfg succeded */
#define BS_STINTF_CFG_NOK   96  /* bssap INTF cfg failed */ 
#define BS_UPU_UNEQUIPPED          99  /* rmt USR part unavail - unqueped */
#define BS_ALRM_CIR_UNEQUPD        BS_CIR_UNEQPD
#define BS_ALRM_NOROUTE_DEST       100
#define BS_ALRM_NOCIRTO_ROUTE      101
#define BS_ALRM_RESOURCE_BUSY      102
#define BS_ALRM_RESOURCE_BLKD      103
#define BS_ALRM_MAXCALREF_EXCEEDED 106
#define BS_ALRM_ALOCCON_ERROR      107
#define BS_ALRM_ALOCSPINST_ERROR   108
#define BS_ALRM_NSAP_NOTBOUND      109
#define BS_ALRM_INV_SUINSTID       110
#define BS_ALRM_INV_SPINSTID       111
#define BS_ALRM_INV_CIRID          112 /* wrong cir passed */
#define BS_ALRM_INV_CALREF         113
#define BS_ALRM_INV_EVENT          114
#define BS_ALRM_INV_MSGLEN         115
#define BS_ALRM_FTZ_ENCODEFAIL     116
                                      /* Reset/Unblocking/Blocking          */
#define BS_STCIRGRP        5          /* elmnt for circuit group operations */
#define BS_STCONN          6          /* cntrl->hdr.elmId.elmnt for connections*/
#define BS_STINTF          7          /* cntrl->hdr.elmId.elmnt for dpc cfg */

#define MAX_LBS_TRC       16

#ifdef TDS_ROLL_UPGRADE_SUPPORT
#define LBS_COMMON_DEF_VAL 0x00    /* default value for the field won't used 
                                    * during soak time */
#define LBS_SS7_ANS88_BIT 0x01    /* bit corresponding to flag SS7_ANS88 */
#define LBS_SS7_ANS92_BIT 0x02    /* bit corresponding to flag SS7_ANS92 */
#define LBS_SS7_ANS95_BIT 0x04    /* bit corresponding to flag SS7_ANS95 */
#define LBS_SS7_ITU97_BIT 0x08    /* bit corresponding to flag SS7_ITU97 */
#define LBS_SS7_ETSIV3_BIT  0x10  /* bit corresponding to flag SS7_ETSIV3 */
#define LBS_SS7_ETBS_BIT  0x20  /* bit corresponding to flag SS7_ETSI */
#define LBS_SS7_INDIA_BIT  0x40  /* bit corresponding to flag SS7_INDIA */
#define LBS_SS7_CHINA_BIT  0x80  /* bit corresponding to flag SS7_CHINA */

#define LBS_SS7_NZL_BIT    0x900 /* bit corresponding to flag NZL */
#define LBS_SS7_KZ_BIT     0x100 /* lsi_h_001.main_29 : bit corresponding to flag KZ */
#define LBS_SS7_ITU2000_BIT 0x60 /* bit corresponding to flag ITU 2000 */
#define LBS_SS7_UR_BIT      0x8000 /* bit corresponding to flag Ukraine */
#endif 
#endif

  
/**********************************************************************
 
         End of file:     lbs.h

**********************************************************************/

