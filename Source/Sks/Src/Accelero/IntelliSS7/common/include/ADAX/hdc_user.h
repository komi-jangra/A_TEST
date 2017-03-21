/*
 * Copyright 2000-2004 ADAX, Inc.
 *      Use of this code is subject to your agreement with ADAX, Inc.
 */

/* ver[] = @(#)hdc_user.h	1.16 delta 05/03/03 */

#ifndef _HDC_USER_H 
#define _HDC_USER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define MAXTXFRAME 2040
#define MAXRXFRAME 2100

#define MAXFRAME MAXRXFRAME

#define MODULE_MTP2 1		/* protocol type param passed to SAIOPSHMOD */

/* HDC ioctl defines */
#define AIOCSTAT 1	/* get Modem (CD) status */
#define AIOCTIMR  6	/* Set APC7 link speed. (on HDC does nothing) */
#define AIOCGETCSPEC 8	/* get the CSPEC from HDLC proc */
#define AIOCGETLRT 9	/* get the Lower Receive Table */
#define AIOCGETLTT 10	/* get the Lower Transmit Table */
#define AIOCCSTOP 14	/* Stop channel and remove RTS */
#define AIOCTRANS 16	/* Initialize in Transparent mode */
#define AIOCSMODE 17	/* Set mode register */
#define AIOCGMODE 18	/* Get mode register */
#define	AIOCDIVERT 21	/* Divert received data to control port */
#define	AIOCCOUNTS 22	/* Provide I-frame counts and error counts */
#define	AIOCCZERO 23	/* Zero I-frame counts and error counts */
#define	AIOCLOOPBK 25	/* Start up with loop-back */
#define AIOCBITS 29     /* go read the driver code, it's too complicated */
#define AIOCSBITDLY 30  /* set delay for above routine */
#define	AIOCDEBUG 40	/* Alter debug level */

#define AIOC7HRESET 47  /* Reset hardware to known state */
#define AIOCGETTTS 52	/* Get the Siemens MPC channel time slots */
#define AIOCSETTTS 53	/* Set the Siemens MPC channel time slots */
#define AIOCFREETTS 54	/* Free the Siemens MPC channel time slots */
#define AIOCSETPORT 58	/* Set the port for an HDC user clone open */
#define AIOCGETCURD 59	/* Get the current RX descriptor */
#define AIOCGETCUTD 60	/* Get the current TX descriptor */
#define	AIOCFNDSLT 61	/* find mpc timeslot assignment 'index' for ctl port */
#define AIOCGETTSA 62	/* get all timeslot assignment descriptors */
#define AIOCGETID 63	/* get pci device and vender id.  debugging ioctl */
#define AIOCFISU 64	/* toggle FISU filtering */
#define AIOCTIMSTAMP 65 /* toggle frame timestamping */
#define AIOCSTIMR 66    /* set value of 8254 timr for min isr interval */
#define AIOCSETTSA 67	/* set time slot fill mask for a open channel */
#define AIOCSETCM 68	/* Set channel mode */
#define AIOCSETQ  69	/* Change High/Low water marks of driver */
#define AIOCRIQDMP 70	/* dump receive interrupt queue */
#define AIOCTIQDMP 71	/* dump transmit interrupt queue */
#define AIOCREGDMP 72	/* dump all siemens registers */
#define AIOCSBITORDR 73 /* transmit 3 or 4 byte frame continuously */

#define AIOCGETURT	75	/* get upper receive descriptor table */
#define AIOCGETUTT	76	/* get upper transmit descriptor table */
#define AIOCGETCUURD	77	/* get current upper recevie descriptor */
#define AIOCGETCUUTD	78	/* get current upper transmit descriptor */
#define AIOCMVIP	80	/* H.100/MVIP control (HDC-cPCI only) */
#define AIOCSADCDMP	81	/* dump board HDC_SA_CHAN struct */
#define AIOCHCOUNTS	82	/* get counts from the host */
#define AIOCHCZERO	83	/* zero counts from the host */
#define AIOCGETCRSH	84	/* get crash results from abort handler */
#define AIOCSTACKDMP	85	/* dump stack */
#define AIOCTRACEDMP	86	/* dump strace buffer */
#define AIOCPRINTDMP	87	/* dump printf buffer */
#define AIOCTXCQDMP	88	/* dump command queue to SA */
#define AIOCRXCQDMP	89	/* dump command queue to HOST */

#define AIOCFAULTIND	93	/* dis/enable board fault monitoring */
#define AIOCGSERNUM	94	/* Get Board Serial Number */
#define AIOCGMRL	95	/* Get Board MRL Level */
#define AIOCGMTP2LINKS	96	/* Get number of MTP2 links supported by board
				 * and software */
#define AIOCGBRDTYPE	97	/* Return type of board HDC or HDCII */
#define AIOCSDIMODE	98	/* Set Drop and Insert mode for HDCII-PCI */
#define AIOCGETTXRINGCTRL 99	/* Get GigE Tx Descriptor Info */
#define AIOCGETRXRINGCTRL 100	/* Get GigE Rx Descriptor Info */


#define AIOCRAMLR 200  /* RAM LWORD read    All of these have first lword as */
#define AIOCRAMLW 201  /* RAM LWORD write   offset from HDCs-PCI start */
#define AIOCRAMSR 202  /* RAM 16-bit read   and transfer the remaining data. */
#define AIOCRAMSW 203  /* RAM 16-bit write  Reads return data at buffer start */

#define AIOCGVERR 240   /* Get the board Version Register */
#define AIOCSHSCR 241   /* Set the Hot Swap Control Register */
#define AIOCGHSCR 242   /* Get the Hot Swap Control Register */
 
#define AIOCGPMEM 243   /* Get the current PCI bus memory addr (use for swap) */
#define AIOCSPMEM 244   /* Set the current PCI bus memory addr (use for swap) */
#define AIOCDPMEM 245   /* Disable PCI bus memory address (use for swap) */
#define AIOCEPMEM 246   /* Enable  PCI bus memory address (use for swap) */
 
#define AIOCGJTAG 247   /* Get the JTAG programming register */
#define AIOCSJTAG 248   /* Set the JTAG programming register */
#define AIOCSSLED 249   /* Set the Status RED/GREEN LED:D0 is Green,D1 is Red */

#define SAIO ('S'<<24)	/* Strong Arm Bound ioctl */
#define COMP ('C'<<24)  /* APC7 Source Code Compatibility Mode ioctl */
#define ETIO ('E'<<24)	/* Ethernet port ioctl */

#define ETIOSETPORT	(ETIO|AIOCSETPORT)	/* set ethernet port */
#define ETIOTRANS	(ETIO|AIOCTRANS)	/* start Rx side of eth port */
#define ETIOGETRT	(ETIO|AIOCGETURT)	/* get ethernet RD */
#define ETIOGETTT	(ETIO|AIOCGETUTT)	/* get ethernet TD */
#define ETIOGETCUTD	(ETIO|AIOCGETCUTD)	/* get current TD */
#define ETIOGETCURD	(ETIO|AIOCGETCURD)	/* get current RD */
#define ETIOCCOUNTS	(ETIO|AIOCCOUNTS)	/* get ethernet stats */
#define ETIOCZERO	(ETIO|AIOCCZERO)	/* zero ethernet stats */
#define ETIOSTAT	(ETIO|AIOCSTAT)		/* Get SCB status from 82559 */
#define ETIOLOOPBACK    (ETIO|AIOCLOOPBK)	/* Toggle Ethernet Loopback */
#define ETIOGETTXRINGCTRL (ETIO|AIOCGETTXRINGCTRL)  /* Get GigE Tx Desc Info */
#define ETIOGETRXRINGCTRL (ETIO|AIOCGETRXRINGCTRL)  /* Get GigE Rx Desc Info */

#define HDIO ('H'<<16)	/* Stream head ioctl */
#define DRIO ('D'<<16)	/* hdc driver ioctl */
#define M2IO ('M'<<16)	/* MTP2 ioctl */
#define LAIO ('L'<<16)	/* LAP(B/D/V5/F) ioctl */

#define SAIOPSHMOD	(SAIO|HDIO|1)	/* push protocol module onto a stream*/
#define SAIOPOPMOD	(SAIO|HDIO|2)	/* pop a protocol module onto a stream*/

#define SAIOCOUNTS	(SAIO|DRIO|AIOCCOUNTS)/* return connection stats */
#define SAIOZERO	(SAIO|DRIO|AIOCCZERO)	/* zero connection stats */
#define SAIOGETCURD	(SAIO|DRIO|AIOCGETCURD)	/* get current rx desc */
#define SAIOGETCUTD	(SAIO|DRIO|AIOCGETCUTD)	/* get current tx desc */

#define SAIOALRMIND     (SAIO|DRIO|108) /* setup for receiving alarm ind. 
					 * (note: same number as ATMX driver) */
#define SAIOGLSSUCNT	(SAIO|DRIO|110)	/* get mtp2 FISU/LSSU counts */
#define SAIOZEROLSSUCNT	(SAIO|DRIO|111)	/* clear mtp2 FISU/LSSU counts */
#define SAIOTXLSSUCNT   (SAIO|DRIO|112) /* enable/disable tx LSSU counts */


/*********** APC7 Source Code Compatibility ************/

/* Compatibility mode ioctls */
#define AIOCCOMPAT (COMP|1) /* Places the HDC Driver into 
			     * APC7 Source Compatibility Mode */
#define AIOCGETIB (COMP|3)  /* Retrieve apc7 compatible IBLOCK structure */
#define AIOCGETRT (COMP|4)  /* Return MK5027 Receive ring entries */
#define AIOCGETTT (COMP|5)  /* Return MK5027 Transmit ring entries */
#define AIOCGETSB (COMP|6)  /* Return MK5027 Status Buffer */
#define AIOCSETIB (COMP|7)  /* Set apc7 compatible IBLOCK structure */
#define AIOCSTOP  (COMP|8)  /* Stop the specified channel, enter OOS */
#define AIOCSTART (COMP|9)  /* Start the MTP2 alignment procedure */
#define AIOCLPO   (COMP|10) /* Enter Local Processor Outage Mode */
#define AIOCLPR   (COMP|11) /* Recover Local Processor Outage Mode */
#define AIOCPON   (COMP|12) /* Enter Power On mode. */
#define AIOCPOFF  (COMP|13) /* Enter Power Off mode. */
#define AIOCINIT  (COMP|14) /* Initialize according to values in IBLOCK */
#define AIOCRBSNT (COMP|15) /* Write contents of MK5027 status block to RAM */
#define AIOCFSNC  (COMP|16) /* Release buffers in retransmit queue up to FSNC */
#define AIOCGETTB (COMP|17) /* Get retransmit buffer at specified index */
#define AIOCGETTQ (COMP|18) /* Retrieve MSU from transmit or streams buffer */
#define AIOCEMRGNCY (COMP|19)  /* Set Emergency Proving Mode */
#define AIOCEMRGEND (COMP|20)  /* End Emergency Proving Mode */
#define AIOCGETTS   (COMP|21)  /* Get number of bytes and number of 
                                * messages to be retrieved */
#define AIOCSIOSON  (COMP|22)  /* Allow sending of SIOS SUs in OOS mode */
#define AIOCSIOSOFF (COMP|23)  /* Stop sending of SIOS SUs in OOS mode */

/* APC7 ioctls that are not supported under 
 * HDC APC7 Source Compatibility Mode.
 * These ioctls will always fail with errno set to ENOENT
 */
#define AIORESET	(COMP|0)
#define AIOCMSTAT	(COMP|0)
#define AIOCREAD	(COMP|0)
#define AIOCRR01	(COMP|0)
#define AIOCLOCK	(COMP|0)
#define AIOCSMODE2	(COMP|0) /* Set mode 2 register */
#define AIOCGMODE2	(COMP|0) /* Get mode 2 register */
#define	AIOCSTWT	(COMP|0) /* Set transmit clock watchdog timer */
#define	AIOCSRWT	(COMP|0) /* Set receive  clock watchdog timer */
#define	AIOCSRSUTE	(COMP|0) /* Set received SU timer  */
#define	AIOCHILOWAT	(COMP|0) /* Set the Stream high and low water marks */
#define	AIOCPRESET	(COMP|0) /* Reset one MK5025 */
#define AIOCTMRSET	(COMP|0) /* Set the SS7 timer values based on */
				 /* clock speed in range 10MHZ - 33MHZ */
#define AIOCCGABAT	(COMP|0) /* Set the congestion abated threshold */
#define AIOCGTABAT	(COMP|0) /* Get congestion relieved threshold value */

#define	AIOCGCSR	(COMP|0) /* Get MK5025 control/status register */
#define	AIOCSCSR	(COMP|0) /* Set MK5025 control/status register */
#define AIOCSFLAG	(COMP|0)

/* Compatibility Mode Indications to MTP3 */
#define DLP_INIT 0        /* initialization complete */ 
#define DLP_INSERVICE 1   /* In Service */
#define DLP_TCW   3       /* Transmit Clock Watchdog timer expired */
#define DLP_RCW   4       /* Receive Clock Watchdog timer expired */
#define DLP_RSUTE 5       /* Receive SU Timer Expired */
#define DLP_ALGNOOS 8     /* Alignment Out of Service */
#define DLP_LSSUOOS 9     /* LSSU Out of Service */
#define DLP_T1OOS 10      /* T1 Out of Service */
#define DLP_TXOOS 11      /* Transmit Out of Service. (T6/T7 expiration) */
#define DLP_RXOOS 12      /* Receive Out of Service. (FIB/BSN errors) */ 
#define DLP_SUERMOOS 13   /* SUERM Out of Service */
#define DLP_RPO 16        /* Remote Processor Outage */
#define DLP_RPOR 17       /* Remote Processor Outage Recovered */
#define DLP_BSNT 18       /* 5027 has written the BSNT to the status buffer */
#define DLP_RETCOMP 19    /* completed retrieval of FSNC, updated Tx table */
#define DLP_RPB 20        /* Remote Processor Busy */
#define DLP_RPBR 21       /* Remote Processor Busy Recovered */
#define DLP_TTCPRI 0x10000

/* Structs and defines for AIOCMVIP */
typedef struct
	{
	unsigned int trunk;
	unsigned int starting_slot;
	unsigned int ending_slot;
	} MVIP_CMD;

/* defines for the MVIP_CMD struct */

/* These defines set the mode for the H.110 bus controller */
#define MVIP_H110_CTL 	 0xC0000000
#define H110_DISABLE	 0x00000000 /* Disconnect HDC-cPCI from H.110 bus */
#define H110_MASTER	 0x00000010 /* Become H.110 bus timing master */
#define H110_SLAVE_NOQCX 0x00000020 /* Become H.110 bus timing slave w/no QCX */
#define H110_SLAVE_QCX 	 0x00000030 /* Become H.110 bus timing slave w/QCX */
#define H110_CLOCK_A	 0x00000000 /* Drive H.110 clock set 'A' */
#define H110_CLOCK_B	 0x00000008 /* Drive H.110 clock set 'B' */
#define H110_TRUNK_MASK	 0x00001F00

/* This define is used to turn on mappings between
 * HDC ports and TDM data streams */
#define MVIP_CTL 		0x80000000

/* This define is used to turn off mappings between HDC
 * ports and TDM data streams */
#define MVIP_DISABLE_CTL	0x00000000

#define MVIP_TRUNK_MASK		0x00001F00
#define MVIP_SUBTRUNK_MASK	0x00000003

/* Compatibility Misc defines */
#define XPC_OWNA 0x8000
#define OWNA 0x8000	/* a synonym for XPC_OWNA */
#define NT 64		/* number of APC7 compatibility transmit descriptors */
#define NR 64 		/* number of APC7 compatibility receive descriptors */

#define SBACNT 25	/* Number of shorts returned from APC7 AIOCGETSB.
			 * HDC's MTP2 returns only an APC7_STATUS structure.
			 * User must supply buffer of at least 50 bytes
			 * to AIOCGETSB to be compatible with both
			 * APC7 AIOCGETSB and HDC AIOCGETSB, but only
			 * the first 16 bytes contain useful information 
			 * in both cases 
			 */

/* Compatibility Mode structures */

/* apc7 status buffer structure */
typedef struct apc7_status {
unsigned char bsnr;        /* last BSN received */
unsigned char bsnt;        /* last BSN transmitted */
unsigned char fsnr;        /* last FSN received */
unsigned char fsnt;        /* last FSN transmitted */
 
unsigned char fsnx;        /* next expected FSN to be received */
unsigned char rfsn;        /* FSN of oldest MSU in rexmit buffer */
unsigned char ridx;        /* index of current Rx descriptor */
unsigned char tidx;        /* index of current Tx descriptor */
 
unsigned char phase;       /* Protocol phase */
unsigned char rtidx;       /* index of current rexmit descriptor */
unsigned char rxstate;     /* Rx state of SS7 HW */
unsigned char txstate;     /* Tx state of SS7 HW */
 
unsigned short rsv_rev;    /* reserved and chip revision level */
unsigned short oct_rtx;    /* number of octets retransmitted */
} APC7_STATUS;

/* APC7 like phases for compatiblity with APC7 */
#define APC7_POWER_OFF			0
#define APC7_OUT_OF_SERVICE		2
#define APC7_INIT_ALIGN_NOT_ALGN	4
#define APC7_INIT_ALIGN_PROVING		6
#define APC7_ALIGN_NOT_READY		7
#define APC7_ALIGN_READY		8
#define APC7_IN_SERVICE			9
#define APC7_PROCESSOR_OUTAGE		10

typedef struct apc7_iblock {
    unsigned short Mode;            /* mode register */
    unsigned short N2_Scaler;       /* N2: (upper bits) count, and scaler */
    unsigned short N2;              /* N2: (lower 16 bits) */
    unsigned short T1timer;         /* T1: aligned ready timer value */
    unsigned short T2timer;         /* T2: not aligned timer value */
    unsigned short T3timer;         /* T3: aligned timeout timer value */
    unsigned short T4ntimer;        /* T4n: normal proving timer value */
    unsigned short T4etimer;        /* T4e: emergency proving timer value */
    unsigned short T5timer;         /* T5: busy transmit timer value */
    unsigned short T6timer;         /* T6: excess busy timer value */
    unsigned short T7timer;         /* T7: excess acknowledge timer value */
    unsigned short Tptimer;         /* TP: transmit polling timer value */
    unsigned short RES1;            /* Reserved field */
    unsigned short PO;              /* Protocol Options */
    unsigned short T_M;             /* SUERM threshold, proving abort lim */
    unsigned short D;               /* SUERM error rate (lower bound) */
    unsigned short Tin_Tie;         /* normal AERM, emerg AERM thresholds */
    unsigned short m;               /* maximum frame before count begins */
    unsigned short RLEN;            /* ring and window lengths */
    unsigned short RDRAl;           /* low 16 bits of Recv desc ring addr*/
    unsigned short TLEN;            /* transmit ring and window lengths */
    unsigned short TDRAl;           /* low 16 bits of xmit desc ring addr*/
    unsigned short SBAh;            /* high byte of status buffer addr */
    unsigned short SBAl;            /* high byte of status buffer addr */
    unsigned short RES2;            /* Reserved */
    unsigned short stats[47];       /* statistics and reserved */
    unsigned short Tftimer;         /* TTC Tf FISU send interval */
    unsigned short Tstimer;         /* TTC Ts SIOS send interval */
    unsigned short Totimer;         /* TTC To SIO send interval */
    unsigned short Tatimer;         /* TTC Ta SIE send interval */
    unsigned short RES3[24];        /* Reserved */
} APC7_IBLOCK;

/* the old name for APC7_IBLOCK in apc7_user.h was IBLOCK */
typedef APC7_IBLOCK IBLOCK;

typedef struct apc7_desc {
	unsigned short DFlags;		/* varius flags, upper 8 bits of addr */
	unsigned short BADRl;		/* low 16 bits of the buffer address */
	unsigned short BCNT;		/* size(in bytes,2's comp)of buffer */
	unsigned short MCNT;		/* size(in bytes,2's comp)of mesg */
} APC7_DESC;

/* the old name for APC7_DESC in apc7_user.h was DENTRY */
typedef APC7_DESC DENTRY;

/* apc7 statistics structure from the IBLOCK */
typedef struct apc7_stats {
        unsigned short SLFail_abnorm;  /* link failures due to abn. FIB, BSN */
        unsigned short SLFail_T7;      /* link failures due to T7 exp. */
        unsigned short SLFail_suerm;   /* link failures due to SUERM. */
        unsigned short SLFail_cong;    /* link failures due to T6 exp. */
        unsigned short ALFail_T2T3;    /* alignment failures due to T2 or T3*/
        unsigned short ALFail_aerm;    /* alignment failures due to aerm */
        unsigned short numNegAck;      /* number of neg. acks */
        unsigned short numErrSu;       /* number of SUs in error */
        unsigned char  reserved[56];   /* reserved as zeros */
        unsigned short SIBtx;          /* SIB tx'd */
        unsigned short SIBrx;          /* SIB rx'd */
        unsigned short N1rtx;          /* num of rtx events due to N1 exceeded*/
        unsigned short N2rtx;          /* num of rtx events due to N2 exceeded*/
        unsigned short MSUrtx;         /* num MSUs retransmitted */
        unsigned short MSUrtx_octets;  /* num MSU octets retransmitted */
        unsigned char  reserved2[10];  /* reserved as zeros */
} APC7_STATS;

typedef struct apc7_counts {
   struct apc7_stats stat;            /* SS7 stats from IBLOCK */
   unsigned char res[2];             /* reserved */
   unsigned int MSUsrx;              /* number of MSUs Rx'd by host */
   unsigned int MSUstx;              /* number of MSUs Tx'd by host */
} APC7_COUNTS;
/********** END COMPATIBILITY SECTION **********/

/* Control port flag for AIOCSETTTS */
#define CTL_PORT_REQ 0x80000000

/* Flags and bitmasks for AIOCSETCM */
#define CSPEC_MODE     0x00000006 /* 6=HDLC mode, 0=TMA mode */
#define CSPEC_HDLC     0x00000006 /* 6=HDLC mode */
#define CSPEC_TMA      0x00000000 /* 0=TMA mode */

#define CSPEC_FA       0x00000008 /* flag filtering in TMA mode */
#define CSPEC_INV      0x00000080 /* Data inversion mode */
#define CSPEC_TFLAG    0x0000ff00 /* mask for supplying a FLAG for TMA mode */

/* AIOCSBITORDR ioctl defines */
#define PROTO_Q921	0 /* Set Least Significant Bit first ordering in 
			   * TMA mode (default) */

#define PROTO_G711_RX	1 /* Set Most Significant Bit first ordering in TMA mode
			   * but swap only received data.  This assumes that
			   * the transmit data is already bit swapped into
			   * least significant bit first (Q.921) format */

#define PROTO_G711_RXTX 2 /* Set Most Significant Bit first ordering in TMA 
			   * mode and bit swap transmit and receive data.  
			   */
/* Flags returned from AIOCSTAT */
#define M_ERR      0x0020	/* Modem error */
#define W_ERROR    0x0008	/* not used by HDC */
#define W_DONE     0x0002	/* not used by HDC */

/* flags for setting loopback mode */
#define LOOP_OFF 	0x0	/* turn off loop back mode(regardless of type)*/
#define LOOP_COMPI	0x1	/* Turn on complete internal loopback */
#define LOOP_COMPE	0x2	/* Turn on complete external loopback */
#define LOOP_CHANI	0x5	/* Turn on Channel-wise internal loopback */
#define LOOP_CHANE	0x6	/* Turn on Channel-wise external loopback */

/* status LED register defines for AIOCSSLED */
#define STAT_LED_GREEN  0x1
#define STAT_LED_RED    0x2
#define STAT_LED_YELLOW 0x3
#define STAT_LED_OFF    0x0
#define STAT_LED_MASK   (STAT_LED_GREEN|STAT_LED_RED|STAT_LED_YELLOW)

/* hot_swap register bits */
#define HOTSWAP_EDM	0x01
#define HOTSWAP_INS	0x02
#define HOTSWAP_EXT	0x04
#define HOTSWAP_LOO	0x08
#define HOTSWAP_MASK	(HOTSWAP_EDM|HOTSWAP_INS|HOTSWAP_EXT|HOTSWAP_LOO)

/* types of crashes for AIOCGETCRSH */
#define UNDEF_HANDLER		0x55
#define SWI_HANDLER		0x53
#define PREFETCH_HANDLER	0x51
#define ABORT_HANDLER		0x49
#define FIQ_HANDLER		0x47

/* defines for AIOCFISU */
#define FILTER_NONE	0  /* No fisu filtering */
#define FILTER_MTP2	1  /* Fisu filtering suitable for an MTP2 upper layer */
#define FILTER_ALL	2  /* All frames less than fisu_filterlen are removed */


/* Control structures for requests sent to the HDC driver from the user. */
#define DL_LOOP_REQ 0xf0000002 /* Sent down in the control part of a written
                                * message to indicate that this message 
                                * should be looped until stopped.
                                */ 

#define DL_CRCERR_REQ 0xf0000003 /* Sent down in the control part of a written
                                  * message to indicate that this message 
                                  * should be transmitted with a CRC error.
                                  */ 

/* Control structures for indications sent to the user from the HDC driver. */

/* If the SAIOALRMIND ioctl enables alarm indications,
 * then a DLP_ALRM_IND indication will be received as a M_PROTO  
 * message when there is a change in alarm status and the
 * alarm is stable for the debouncing period
 */
/* defines for SAIOALRMIND */
#define DLP_ALRM_IND    0xf0000003  /* alarm status change indication */
#define ALRM_NONE	0x00000000  /* No longer an alarm on this trunk */
#define ALRM_IND	0x00000001  /* An alarm occured on this trunk */

/* defines for AIOCFAULTIND */
#define DLP_BOARD_FAULT 0xf0000004  /* Board has failed. */

/* structure sent up in control part if timestamping is enabled */
typedef struct hdc_unitdata_ind {
unsigned int prim;      /* Always set to the constant
                         * DL_UNITDATA_IND from dlpi.h */
unsigned int unix_time; /* Unix LBOLT timestamp */
unsigned int len;       /* length in bytes of data part of message */
unsigned int timestamp; /* 32 bit timestamp from board level
                         * stream head */
unsigned int fisus_filtered; /* number of fisus filtered before this frame */
} hdc_unitdata_ind_t;

/* structure sent up in control part if fisu filterring is 
 * set to FILTER_MTP2 */
typedef struct hdc_error_ind {
unsigned int prim;      /* Always set to the constant
                         * DL_UDERROR_IND from dlpi.h */
unsigned int unix_time; /* Unix LBOLT timestamp */
unsigned int len;       /* length in bytes of data part of message */
unsigned int timestamp; /* 32 bit timestamp from board level
                         * stream head */
unsigned int fisus_filtered; /* number of fisus filtered before this frame */
} hdc_error_ind_t;

/* MTP2 error codes reported in the data part of hdc_error_ind_t messages */
#define	MTP2_7_CONSECUTIVE_1	0x01
#define	MTP2_FCS_ERROR		0x02
#define	MTP2_16_OCTETS		0x04
#define	MTP2_SU_LEN_EXCEED	0x08

/* stats kept for each link returned from the SAIOCOUNTS ioctl */
typedef struct Lstats {
	unsigned short ncrc_err;	/* count of CRC errors encountered */
	unsigned short creads;		/* count of RX ring reorganizations */
	unsigned short n_null1;		/* count of T1 timeouts */
	unsigned short n_rejsrx;	/* count of rejs recv'd */
	unsigned short n_rejstx;	/* count of rejs sent */
	unsigned short n_shortf;	/* count of short frames received */
	unsigned int frames_in;		/* count of I-frames received */
	unsigned int frames_out;	/* count of I-frames out to network */
	unsigned int fisus;		/* count of recvd FISUs */
	unsigned int rxintrs;		/* number of Rx intr vectors */
	unsigned int txintrs;		/* number of Tx intr vectors */
	unsigned int rx_fiint;		/* num of Rx FI intrs */
	unsigned int tx_fiint;		/* num of Tx FI intrs */
	unsigned int rx_errint;		/* num of Rx ERR intrs */
	unsigned int tx_errint;		/* num of Tx ERR intrs */
	unsigned int rx_foint;		/* num of Rx FO intrs */
	unsigned int tx_foint;		/* num of Tx FO intrs */
	unsigned int rx_sfint;		/* num of Rx SF intrs */
	unsigned int tx_fe2int;		/* num of Tx FE2 intrs */
	unsigned int rx_ra;		/* num of Rx RA descriptors */
	unsigned int rx_rof;		/* num of Rx ROF descriptors */
	unsigned int rx_loss;		/* num of Rx LOSS descriptors */
	unsigned int rx_nob;		/* num of Rx NOB descriptors */
	unsigned int rx_lfd;		/* num of Rx LFD descriptors */
	} LSTATS;

/* Structure returned from the SAIOGLSSUCNT ioctl */
typedef struct mtp2_lssustats {
	unsigned int rx_fisu;	/* FISUs received */
	unsigned int rx_lssu;	/* Total LSSUs received */

        unsigned int tx_fisu;   /* FISUs transmitted */
        unsigned int tx_lssu;   /* Total LSSUs transmitted */

	unsigned int rx_sio;	/* SIO LSSUs received (HDCII only) */
	unsigned int rx_sin;	/* SIN LSSUs received (HDCII only) */
	unsigned int rx_sie;	/* SIE LSSUs received (HDCII only) */
	unsigned int rx_sios;	/* SIOS LSSUs received (HDCII only) */
	unsigned int rx_sipo;	/* SIPO LSSUs received (HDCII only) */
	unsigned int rx_sib;	/* SIB LSSUs received (HDCII only) */

        unsigned int tx_sio;    /* SIO LSSUs transmitted (HDCII only) */
        unsigned int tx_sin;    /* SIN LSSUs transmitted (HDCII only) */
        unsigned int tx_sie;    /* SIE LSSUs transmitted (HDCII only) */
        unsigned int tx_sios;   /* SIOS LSSUs transmitted (HDCII only) */
        unsigned int tx_sipo;   /* SIPO LSSUs transmitted (HDCII only) */
        unsigned int tx_sib;    /* SIB LSSUs transmitted (HDCII only) */
} mtp2_lssustats_t;

/* stats kept by the host */
typedef struct Hstats {
	unsigned int frames_in;		/* count of I-frames received */
	unsigned int frames_out;	/* count of I-frames out to network */
	unsigned int rputfail;		/* count of rsrv canput failures */
	unsigned int rxintrs;
	unsigned int txintrs;
} HSTATS;

/* struct returned from ETIOCCOUNTS */
typedef struct
	{
	unsigned int aeth_opackets;	/* Good Tx frames */
	unsigned int aeth_maxcol;	/* Tx max coll */
	unsigned int aeth_tlcol;	/* Tx late coll */
	unsigned int aeth_uflo;		/* tx underrun errors */
	unsigned int aeth_tnocar;	/* tx lost carrier sense */
	unsigned int aeth_defer;	/* tx deferred */
	unsigned int aeth_fstcol;	/* Tx single (first) collisions */
	unsigned int aeth_multi_collisions;	/* Tx multi collisions */
	unsigned int aeth_coll;		/* Tx total collisions */

	unsigned int aeth_ipackets;	/* Good Rx frames */
	unsigned int aeth_crc;		/* Rx CRC errors */
	unsigned int aeth_fram;		/* Rx alignment errors */
	unsigned int aeth_buff;		/* "bufffer" errors (really
					 * rx resource errors) */
	unsigned int aeth_oflo;		/* Rx overflow (overrun) errors */
	unsigned int aeth_clsn;		/* Rx collision detect errors */
	unsigned int aeth_runt;		/* Rx "runt" (short frame) errors */

	unsigned int aeth_ierrors;
	unsigned int aeth_oerrors;

	unsigned int aeth_ifspeed;
	unsigned int aeth_missed;
	unsigned int aeth_nocanput;
	unsigned int aeth_allocbfail;

	/*
	 * MIB II variables
	 */
	unsigned int aeth_rcvbytes;	/* # bytes received */
	unsigned int aeth_xmtbytes;	/* # bytes transmitted */
	unsigned int aeth_multircv;	/* # multicast packets received */
	unsigned int aeth_multixmt;	/* # multicast packets for xmit */
	unsigned int aeth_brdcstrcv;	/* # broadcast packets received */
	unsigned int aeth_brdcstxmt;	/* # broadcast packets for xmit */
	unsigned int aeth_norcvbuf;	/* # rcv packets discarded */
	unsigned int aeth_noxmtbuf;	/* # xmit packets discarded */

	/*
	 * RFE's (Request for Enhancements)
	 */
	unsigned int link_duplex;
	/*
	 * Debuging kstats
	 */
	unsigned int inits;
	unsigned int rxinits;
	unsigned int txinits;
	unsigned int link_down_cnt;
	} HOST_ETHER_STATS;

#define NUTPC 16 	/* number of upper TXDESC per channel */
#define NURPC 16	/* number of upper RXDESC per channel */
#define NTPC 16		/* number of lower TXDESC per channel */ 
#define NRPC 32		/* number of lower RXDESC per channel */

/* Upper Receive Descriptor */
typedef struct urxdesc {
	volatile unsigned int rhold_hi;	/* timestamp from board.ZZZchange name*/
	volatile unsigned int baddr;	/* pointer to data area */
	/* rbno_stat is now a conglomeration of things:
	 * bits 
	 * 31       30      29-16	    15-13	12-0
	 * CTRL msg ERR msg fisus_filtered  len offset	total len of frame
	 * CTRL msg indicates to the driver that this is a contol msg.
	 * ERR  msg indicates ERR msg (for hdc_error_ind_t) 
	 * fisus_filtered is count of FISUs filtered for AIOCFISU ioctl
	 * len offset is offset from start from mbuff so that driver knows
	 *            how long the first descriptor is.
	 * total len is the total length of the frame */
	volatile unsigned int rbno_stat;
	volatile unsigned int pm;	/* board rel. mblk address. */
	} URXDESC;

/* Lower Receive Descriptor */
typedef struct rxdesc {
	volatile unsigned int rhold_hi;	/* flags: hold,h_int,rx max len,null */
	volatile unsigned int next;	/* next ptr; CACHED board rel */
	volatile unsigned int baddr;	/* CACHED-type buffer address */
	volatile unsigned int rbno_stat;/* flags: fe,c,rx buff len,stat */
	} RXDESC;

/* Upper Transmit Descriptor */
typedef struct txdesc {
	/* tbno_fnum is now a conglomeration of things:
	 * bits 
	 * 31 30            17 16            12-0
	 * ctl msg bits     jt/ntt PRI bits  total len of frame
	 * ctl == 0 == Regular data.
	 * ctl == 1 == Indicates to the board that this msg should be looped.
	 * ctl == 2 == Indicates to the board that it should stop looping
	 *             a previously looping msg.
	 * ctl == 3 == Indicates that the message should be sent with a CRC err.
	 *
	 * total len is the total length of the frame 
	 */
	volatile unsigned int tbno_fnum;
	volatile unsigned int baddr;	/* NON-CACHED-type buffer address */	
	} TXDESC;

/* Lower Transmit Descriptor */
typedef struct ltxdesc {
	volatile unsigned int tbno_fnum;/* various flags, tx len, fill count */
	volatile unsigned int next;	/* next ptr; CACHED board rel */
	volatile unsigned int baddr;	/* CACHED-type buffer address */
	volatile unsigned int pm;	/* Ptr to mblk_t that holds the */
	} LTXDESC;			/* data buffer baddr points to. */

/* Structure and defines for AIOCTRACEDMP */
#define TRACELEN 1024
typedef struct {
	unsigned int lbolt;	/* time of trace entry */
	unsigned char hdc_num;
	unsigned char scc_num;
	char chno;
	unsigned char type;	/* type of message being traced, one of 
				 * M_DATA, M_PROTO, M_CTL, or M_IOCTL */
	unsigned int len;	/* length of data for M_DATA or M_PROTO ,
				 * length of opt data for M_CTL or M_IOCTL */
	unsigned int opt1;	/* command type for M_IOCTL, others ZZZZ */
} hdc_trace_info_t;

/* structure for use with the AIOCGMTP2LNKS ioctl */
typedef struct hdc_gmtp2links {
	unsigned int board_links;    /* number of links supported by board */
	unsigned int software_links; /* number of links supported by software */
} hdc_gmtp2links_t;

/* HDC_BC 'board_type' defines returned from AIOCGBRDTYPE and AIOCGVERR */
#define BT_UNKNOWN	0x0	/* Unknown */
#define BT_HDCII	0x1	/* HDCII */
#define BT_HDC		0x2	/* HDC */

/* structure for use with the AIOCGVERR ioctl */
typedef struct hdc_board_ver {
	unsigned int board_type;	/* board type; HDC or HDCII */
	unsigned int dev_type;		/* HDCII: device type */
	unsigned int pci_revid;		/* PCI Configuration Space revision ID*/
	unsigned int prom_ver;		/* HDCII: firmware PROM version */
	unsigned int mach_ver;		/* HDCII: MACH version */
	unsigned int serial_number;	/* Board serial number */
	unsigned int board_mtp2_links;/* Num of MTP2 links supported by board */
	unsigned int sw_mtp2_links; /* Num of MTP2 links supported by software*/
	unsigned int ether_links;	/* Num of ethernet links supported */
	unsigned int tdm_links;		/* Num of physical TDM links supported*/
	char mrl[8];			/* Board Manufactoring Rev Level */
	char driver_ver[40];		/* hdc host driver version string */
} hdc_board_ver_t;

/* defines for dev_type field of hdc_board_ver_t returned from AIOCGVERR */
#define DT_UNKNWN	0x0
#define DT_PMC		0x40
#define DT_PCI_41	0x41
#define DT_PCI_32	0x42

/* Defines for 82559 status retreived from ETIOSTAT */
#define SCB_CUS_MASK            (BIT_6 | BIT_7)	/* CUS 2-bit Mask */
#define SCB_CUS_IDLE            0		/* CU Idle */
#define SCB_CUS_SUSPEND         BIT_6		/* CU Suspended */
#define SCB_CUS_ACTIVE          BIT_7		/* CU Active */

#define SCB_RUS_MASK            BIT_2_5		/* RUS 4-bit Mask */
#define SCB_RUS_IDLE            0		/* RU Idle */
#define SCB_RUS_SUSPEND         BIT_2		/* RU Suspended */
#define SCB_RUS_NO_RESOURCES    BIT_3		/* RU Out Of Resources */
#define SCB_RUS_READY           BIT_4		/* RU Ready */
#define SCB_RUS_SUSP_NO_RBDS    (BIT_2 | BIT_5)	/* RU No More RBDs */
#define SCB_RUS_NO_RBDS         (BIT_3 | BIT_5)	/* RU No More RBDs */
#define SCB_RUS_READY_NO_RBDS   (BIT_4 | BIT_5)	/* RU Ready, No RBDs */

/* Ethernet Bit Mask definitions */
#define BIT_0       0x0001
#define BIT_1       0x0002
#define BIT_2       0x0004
#define BIT_3       0x0008
#define BIT_4       0x0010
#define BIT_5       0x0020
#define BIT_6       0x0040
#define BIT_7       0x0080
#define BIT_8       0x0100
#define BIT_9       0x0200
#define BIT_10      0x0400
#define BIT_11      0x0800
#define BIT_12      0x1000
#define BIT_13      0x2000
#define BIT_14      0x4000
#define BIT_15      0x8000
#define BIT_16      0x10000
#define BIT_17      0x20000
#define BIT_18      0x40000
#define BIT_19      0x80000
#define BIT_20      0x100000
#define BIT_21      0x200000
#define BIT_22      0x400000
#define BIT_23      0x800000
#define BIT_24      0x1000000
#define BIT_25      0x2000000
#define BIT_26      0x4000000
#define BIT_27      0x8000000
#define BIT_28      0x10000000
#define BIT_29      0x20000000
#define BIT_30      0x40000000
#define BIT_31      0x80000000

#define BIT_0_2     0x0007
#define BIT_0_3     0x000F
#define BIT_0_4     0x001F
#define BIT_0_5     0x003F
#define BIT_0_6     0x007F
#define BIT_0_7     0x00FF
#define BIT_0_8     0x01FF
#define BIT_0_13    0x3FFF
#define BIT_0_15    0xFFFF
#define BIT_1_2     0x0006
#define BIT_1_3     0x000E
#define BIT_2_5     0x003C
#define BIT_3_4     0x0018
#define BIT_4_5     0x0030
#define BIT_4_6     0x0070
#define BIT_4_7     0x00F0
#define BIT_5_7     0x00E0
#define BIT_5_12    0x1FE0
#define BIT_5_15    0xFFE0
#define BIT_6_7     0x00C0
#define BIT_7_11    0x0F80
#define BIT_8_10    0x0700
#define BIT_9_13    0x3E00
#define BIT_12_15   0xF000
#define BIT_8_15    0xFF00

#define BIT_16_18   0x00070000
#define BIT_16_20   0x001F0000
#define BIT_21_25   0x03E00000
#define BIT_26_27   0x0C000000

#ifdef	__cplusplus
}
#endif
#endif	/* _HDC_USER_H */
