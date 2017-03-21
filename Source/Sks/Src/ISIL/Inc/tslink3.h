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

#if !defined(__TSLINK3_H_)
#define __TSLINK3_H_

/*                              */
/*      Type Definitions        */
/*                              */

/* Satisfy some compilers that check for presence of variables for macros */
/*
 *  NOTE, This is a placeholder for the RD and WR 16650 macros so that, if
 *  desired, this "variable" may be used to indicate which UART is in use
 *  for multiple UART situations.
 */
#if defined(UART_16550)
#define U16550_num 0
#endif




#define UCHAR  unsigned char
#define USHORT unsigned short
#define ULONG  unsigned long

#if !defined bool
//typedef enum {false, true,END_BOOL=0XFF} bool ;
#endif

/*                              */
/*      Symbol Definitions      */
/*                              */

#define Rd_mem_reg(addr) \
   (unsigned char) *((unsigned char *) (addr))

#define Wr_mem_reg(addr,contents) \
   *((unsigned char *) (addr)) = (unsigned char) (contents)

#if defined(ELINUX_OS)
/*
 *  Some Linux kernels can define NULL as a void pointer, spoiling the TeleSoft
 *  define and causing warning messages.
 *  In order to avoid that we undefine the NULL if defined and forcing
 *  our value.
 */
#if defined(NULL)
#undef NULL
#endif
#endif

//#if !defined(NULL)
#define NULL    0
//#endif

#if defined(MQX)
/*
 *  mqx.h file needs to be included before these definitions to avoid conflict
 *  (although the actual definitions are the same).
 */
#include <mqx.h>
#if defined(TRUE)
#undef TRUE
#endif
#if defined(FALSE)
#undef FALSE
#endif
#endif

#if !(defined(RTWARE) && defined(_KSTART_H_))
#define ON      1
#define OFF     0
#endif

#define INUSE   1

#if !(defined(RTWARE) && defined(_KSTART_H_))
#define YES     1
#define NO      0

#define TRUE    1
#define FALSE   0
#endif

#define COPROC  1
#define LOCPROC 0

#if !(defined(RTWARE) && defined(_KSTART_H_))
#define PASS    0
#define FAIL    (-1)
#endif

#define ADD_LCI 1
#define LOCATE  0

#define ENABLE_DSC  8
#define DISABLE_DSC 7
#define DIS_SAVE    6
#define EN_INT      5
#define ENABLE_ALL  4
#define DISABLE_ALL 3
#define E_O_I       2
#define ENABLE      1
#define DISABLE     0

#define NON_ZERO    1

#define TSL3_NETWORK 0x80 /* Bit used in swv_model to indicate network-side */

#define SWV_NULL    127  /* Switch variant definition for no specific switch variant */
#define SWV_5ESS    0    /* Switch variant definition for AT&T 5ESS switch  */
#define SWV_DMS_100 1    /* Switch variant definition for NT DMS-100 switch */
#define SWV_NET3    2    /* Switch variant definition for ETSI NET3 switch  */
#define SWV_1TR6    3    /* Switch variant definition for DBP 1TR6 switch   */
#define SWV_INS64   4    /* Switch variant definition for NTT INS64 switch  */
#define SWV_US_NI1  5    /* Switch variant definition for US NI1 spec       */
#define SWV_VNX     6    /* Switch variant definition for latest VN-x use   */
#define SWV_US_NI2  7    /* Switch variant definition for US NI2 spec       */
#define SWV_AUS     8    /* Switch variant definition for Austrailian BRI   */
#define SWV_AUTO_CFG 9   /* Auto-configuration definition for NA switch     */
#define SWV_4ESS    10   /* Switch variant definition for AT&T 4ESS switch  */
#define SWV_AUS_PRI 11   /* Switch variant definition for Austrailian PRI   */
#define SWV_5ESS_PRI 12  /* Switch variant definition for AT&T 5ESS PRI switch */
#define SWV_NET5    13   /* Switch variant definition for PRI NET5 switch   */
#define SWV_INS_PRI 14   /* Switch variant definition for NTT INS64 PRI switch */
#define SWV_DMS_PRI 15   /* Switch variant definition for DMS PRI switch    */
#define SWV_US_NI2_PRI 16 /* Switch variant definition for US NI2 PRI switch */

/* Switch variant definitions for CAS switch types (T1 and E1) */
#define CAS_BASE_SWV_MODEL           17
#define SWV_CAS_T1_WINK_START        17   /* robbed-bit CAS */
#define SWV_CAS_T1_FXS_GROUND_START  18   /* robbed-bit CAS */
#define SWV_CAS_T1_FXS_LOOP_START    19   /* robbed-bit CAS */
/* Note: SWV_CAS_T1_FXO   defined as 33 below */
#define SWV_CAS_E1_R2_ITU            20   /* based on ITU-T Q.400-Q.480 */

#define SWV_QSIG 21     /* Switch variant definition for QSIG switch */

/* Switch variants for xDSL */
#define SWV_IDSL 22     /* Switch variant for ISDN U or S interface,
                           always on, no signaling */
#define SWV_HONG_KONG_PRI            23   /* Subvariant of SWV_NET5 */
/*
 *     NOTE:  If cup_parms_load() is NOT used, Hong_Kong_PRI[] must be
 *     explicitly set to 0 or 1 (with the variant set to SWV_NET5)
 */
#define SWV_R2_ARGENTINA 24 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_BRAZIL    25 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_CHILE     26 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_CHINA     27 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_COLOMBIA  28 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_KOREA     29 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_MEXICO    30 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_NICARAGUA 31 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_SINGAPORE 32 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_GENERIC   39 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_INDIA     40 /* Subvariant of SWV_CAS_E1_R2_ITU */
#define SWV_R2_BANGLADESH 41 /* Subvariant of SWV_CAS_E1_R2_ITU */
/*
 *  NOTE:  If cup_parms_load() is NOT used, R2_variant[] must be
 *  explicitly set to the appropriate value and the variant set to
 *  SWV_CAS_E1_R2_ITU.
 */

#define SWV_CAS_T1_FXO   33   /* robbed-bit CAS */

#define SWV_CAS_TAIWAN_MDR1_T1   34   /* T1 Taiwan MDR1 CAS */
#define SWV_CAS_TAIWAN_MDR1_E1   35   /* E1 Taiwan MDR1 CAS */

#define SWV_HONG_KONG_BRI            36   /* Subvariant of SWV_NET3 */

#define SWV_CAS_T1_IMMED_START 37 /* T1 CAS Immediate Start (Robbed-Bit) */
#define SWV_CAS_T1_DELAY_DIAL  38 /* T1 CAS Delay Dial (Robbed-Bit) */
#define CAS_MAX_SWV_MODEL      41
/*
 *  NOTE:  Value of 39 used for SWV_R2_GENERIC above
 *  NOTE:  Value of 40 used for SWV_R2_INDIA above
 *  NOTE:  Value of 41 used for SWV_R2_BANGLADESH above
 */

/*
 *     NOTE:  If cup_parms_load() is NOT used, Hong_Kong_BRI[] must be
 *     explicitly set to 0 or 1 (with the variant set to SWV_NET3)
 */

/*
 *  NOTE: BE SURE TO ADD ANY NEW SWITCH VARIANTS to the SWV case switch
 *  in ceme\cup_parm.c that assigns Interface_type[interface] for each
 *  SWV variant.
 */

#define INTERFACE_TYPE_ISDN_BRI       0
#define INTERFACE_TYPE_HDLC           1
#define INTERFACE_TYPE_ISDN_PRI       2
#define INTERFACE_TYPE_CAS_T1         3
#define INTERFACE_TYPE_CAS_E1         4
#define INTERFACE_TYPE_IDSL           5
#define INTERFACE_TYPE_RAW_PROTOCOL   6

#define R2_UNKNOWN   0xFF

#define CRCPASS     0    /* Number of CRC bytes that are passed from LLD    */

/* Defines used in misc\lld_glob.c and other entities who need to know LLD  */
/* Moved to LLD.H */

/*
 *  The following block of definitions are used by particular types of
 *  device drivers to determine the physical channel definition of the
 *  system.  The following definition group is set up for a BRI system.
 */

#define DCH_PCHAN  (unsigned short) 0
#define DSCPCHAN   (unsigned short) 0
#define ISACSPCHAN (unsigned short) 0
#define D_PCHAN_LO (unsigned short) 0
#define D_PCHAN_HI (unsigned short) 0
#define B1_PCHAN   (unsigned short) 1
#define B2_PCHAN   (unsigned short) 2
#define HSCXPCHAN0 (unsigned short) 0
#define HSCXPCHAN1 (unsigned short) 1
#define HSCXPCHAN2 (unsigned short) 2
#define MON_PCHAN  (unsigned short) 3  /* IOM2 Monitor channel */
#define CI_PCHAN   (unsigned short) 4  /* IOM2 C/I channel */

/* Connection Endpoint Suffix (CES) constant defines                     */
#define CES_NLS          (252 - MAX_TEI_CNT)   /* Layer 3 NLS            */
#define CES_NLS_VOICE    (252 - MAX_TEI_CNT)   /* Layer 3 NLS - voice    */
#define CES_DL_BROADCAST (252 - MAX_TEI_CNT)   /* Layer 3 NLS - bcast    */
#define CES_NLS_DATA     251   /* Layer 3 NLS stimulus - data            */
#define CES_DNUPX25      252   /* X.25 Layer 3 Nailed-UP on D-Ch.        */
#define CES_BX25         253   /* X.25 Layer 3 on B-Ch.                  */
#define CES_BNUPX25      253   /* X.25 Layer 3 Nailed-UP on B-Ch.        */
#define CES_BCSWX25      253   /* X.25 Layer 3 Circuit-SWitched on B-Ch  */

/* V.120 defines */
#define CES_V120_DEFAULT  1    /* V.120 lowest default CES               */
#define CES_V120_MAX     20    /* V.120 maximum CES value                */
#define CES_V120_SIGNAL  21    /* V.120 signalling CES value             */
#define SAPI_V120         2    /* V.120 SAPI low-end definition          */
#define SAPI_V120_HI     15    /* V.120 SAPI high-end definition         */

/*                              */
/*      Mailbox Receipt Codes   */
/*                              */

#define NOACK       (unsigned char) 0xFF /* prim (if any) not acked yet    */
#define PRIMACK     (unsigned char) 0    /* acknowledge prim               */
#define CMDACK      (unsigned char) 0
#define CODEACK     (unsigned char) 0
#define EVTACK      (unsigned char) 0
#define BADPRIM     (unsigned char) 1    /* problem executing prim         */
#define BADCMD      (unsigned char) 1    /* invalid Command Code code      */
#define BADPARM     (unsigned char) 2    /* invalid Command Parameter code */
#define XMITBSY     (unsigned char) 3    /*  Transmitter Busy              */
#define XMTINACTIVE (unsigned char) 4    /*  Transmitter Inactive          */
#define READREJ     (unsigned char) 5    /*  READ_REQ Buffer Rejected      */
#define CMDFAILED   (unsigned char) 6    /* command execution had a failure*/
#define MBOX_IDLE   (unsigned char) 0x10 /*  Mailbox avail for next prim   */
#define EXECERR     (unsigned char) 0x11 /*  Buffer Request Denied         */

#define NULLFARPTR 0L

#define DEFAULT_MODE   0     /* Original TsLink3 basic protocol mode        */
#define V120_MODE      1     /* TsLink3 V.120 protocol mode for B-channel   */

/* NOTE: If file "ceme\sh_mem.asm" is used (Intel 80X8X processors),
 *       if MAX_SPID_LEN changes, sh_mem.asm Cup_parms_image size must change
 *       as must l4_ifc.h OFFSETs in shared mem if TsLink3 PC plug-in
 *       card example Layer 4 software is used
 */
#define MAX_SPID_LEN  20     /* max length of SPID                          */

#define TEI_BCAST     127    /* Broadcast TEI                               */

#define SAPI_NLS        0    /* NLS Service Access Point ID                 */
#define SAPI_DX25      16    /* X.25 on D-channel SAPI                      */
#define SAPI_MGMT      63    /* Management routine SAPI                     */

/* Supplementary Services Defines used in more than one layer entity */
#define SS_STAT_DEACTIV   0x80
#define SS_STAT_DIAL      0x81
#define SS_STAT_RING      0x82
#define SS_STAT_ALERT     0x83
#define SS_STAT_ACTIVE    0x84
#define SS_STAT_DISC      0x85
#define SS_STAT_HOLD      0x86

/* Supplementary Services ss_config types */
#define NO_SS                0   /* reserved */
#define SS_5ESS_TYPE_A       1   /* also used for US NI non-EKTS SS */
#define SS_5ESS_TYPE_B       2
#define SS_5ESS_TYPE_C       3
#define SS_5ESS_TYPE_D       4
#define SS_US_NI_BASIC_EKTS  5
#define SS_US_NI_CACH_EKTS   6
#define SS_ETSI_FULL         7
#define SS_ETSI              8
#define SS_PRI               9
#define SS_QSIG              10

#define NULL_CA   0                  /* Null Call Appearance                */

#define ONHOOK    0
#define OFFHOOK   1

#define UNUSED_CID      0xFFFF       /* Unused Connid                       */

#define mXchgW(pWord)    \
    (((((unsigned short) pWord) & 0x00FF) << 8) | ((((unsigned short) pWord) & 0xFF00) >> 8) )

#define mXchgD(pDWord)   \
   (((unsigned long)mXchgW(((unsigned long) pDWord) & 0x0000FFFFL) << 16) | \
   (mXchgW((unsigned short)(((unsigned long) pDWord >> 16) & 0x0000FFFFL))))

#define INTERFACE_0            0    /* physical interface 0 */
#define DONT_CARE_BCH_CONN  0xF0    /* arbitrary value */

#if defined(MIDAS_EXTERNAL)
/*
 *  MIDAS_EXTERNAL LED defines
 */
#define LED_CNTRL *((unsigned char *) 0x301800)
#define POWER_LED    0x01
#define SD_LED       0x02
#define RD_LED       0x04
#define AA_LED       0x08
#define TE1_LED      0x10
#define TE2_LED      0x20
#define LINK_LED     0x40
#define TWO_BCH_LED  0x80
#endif

/*
 *  The following defines used to be in the tsl3tune.h file.
 *  They were removed to avoid duplication and clutter.  They are not truly
 *  "tuneable" because changes to them require change to the software.
 */

/*
 *  The purpose is to allow use of a special "Freebuf(a,b)" macro that can
 *  be used *  to define additional debugging information associated with
 *  freeing a buffer.
 */
#define Freebuf(a,b) freebuf(a,b)

/*
 *  The purpose is for setting up data structures associated with the
 *  needs of the complete system (particularly for multi-interface systems)
 */
/* max number of physical channels */
#define MAX_PCHAN (((HDLC_PCHAN * NUM_IFC) > 2) ? (HDLC_PCHAN * NUM_IFC) : 3)

/*
 *  The following defined constants are needed for the standard TsLink3
 *  L4_IFC test program, as well as host-based APIs.  Although they are
 *  directly used only for the MIDAS-ULC active board, they should be defined
 *  for all systems so that a decision on co-processor hardware can be done
 *  on a runtime basis, rather than compile-time.
 *
 */
#define MIDAS_INTCOP    0x0fff       /* interrupt co-processer        */
#define MIDAS_INTHST    0x0ffe       /* interrupt host                */
#define MIDAS_IMASK     0x1000       /* enable-disable host interrupt */
#define MIDAS_RSTCOP    0x1001       /* reset co-processer            */

/*
 *  The AUS_CONFORM_TEST flag is set to run code that is illustrated
 *  to be correct in the Test Specification but is in conflict with
 *  the AUS Q931 Spec.
 */
#define AUS_CONFORM_TEST

/*
 *  The following defines should be kept in each tsl3tune.h file created.  The
 *  purpose is to allow use of the TsLink3 "header hole" which allows room for
 *  Any header information to be added before data without extra copies.
 *
 *  Note that the standard L2HDRSIZE has now been changed to always include
 *  room for V.120.  This allows for no need to specially compile a different
 *  user interface for V.120/non-V.120.  The extra space is compensated for
 *  in LAP in the entry points for data if V_120 is not defined.
 *
 *  If PPP is to be used without any other protocols, it is possible to define
 *  HDRSSIZE to be equal to PPPHDRSIZE.
 */
#if defined(LAPV5_EF_ENABLED)
#define LAPV5_EF_HDRLEN 2
#else
#define LAPV5_EF_HDRLEN 0
#endif

#define V120HDRSIZE  0
#define PPPPADSIZE   0
#define L2HDRSIZE    (4 + LAPV5_EF_HDRLEN + V120HDRSIZE + PPPPADSIZE)
#define P3HDRSIZE    3
#define PPPHDRSIZE   8

#define TRAILERSIZE  7

#if defined(NUP_PPP)
#define HDRSSIZE     (PPPPADSIZE + PPPHDRSIZE)
/* System buffer size for DATA packets */
#define SYSBUFSIZ 1536   /* CUSTOMIZATION REQUIRED */
#else
#define HDRSSIZE     (L2HDRSIZE + P3HDRSIZE)
/* System buffer size for DATA packets */
#define SYSBUFSIZ 800 /* anand: changes done for lapd pegs *///(SYSPKTSIZ + HDRSSIZE + TRAILERSIZE)
#endif


/*
 *  DEFINEs related to Management Entity buffer allocation service
 *  The purpose is to define the buffer sizes used within the system.
 *  TsLink3 uses two fixed-length buffer pools -- one for short frames
 *  and one for unknown or long frames.  EDX operating system needs a
 *  minimum of 32 bytes for intertask messages.
 */
#if defined(EDX_OS)
#define SBUFLEN     32
#else
#if !defined(ALWAYS_ON_PPP)
#define SBUFLEN    (HDRSSIZE + TRAILERSIZE) /* Should end up a multiple of 4 */
#else
#define SBUFLEN    156
#endif
#endif
#define MBUFLEN    (128 + HDRSSIZE + TRAILERSIZE)
#define LBUFLEN    SYSBUFSIZ

/* Define size of buffer to be used for receiving data by the USART */
#define UBUFLEN    SYSBUFSIZ

/* DSC DLC Init Default Parameters */
/*
 *  These are used primarily for the DSC (AMD 79C30A), but occasionally
 *  are used by other LLDs.
 */
/* DSC DLC Init Default Parameters */
#if defined(MED_BUFS)
#define MAXPKTSZ        (unsigned short) MBUFLEN
#else
#define MAXPKTSZ        (unsigned short) SYSBUFSIZ
#endif
#define MINPKTSZ        (unsigned char) 3
#define XMTTHRSH        (unsigned char) 4
#define RCVTHRSH        (unsigned char) 4

#define FLAG            (unsigned char) 0
#define MARK            (unsigned char) 1
#define IDLEFLAG        MARK

#define CR_IGNORE       ENABLE
#define ADDRLEN         (unsigned char) 2
#define ADDRSEL         (unsigned char) 1

#define REQMODE         ENABLE

/*
 *  CUSTOMIZATION REQUIRED
 *
 *  The following defines are used as the Mask values for the function call
 *  to Disable or Enable interrupts. These calls may be overridden by placing
 *  their definitions in TSL3TUNE.H.
 */
#if !defined(MASK_TO_SYSTEM_LEVEL)
#define MASK_TO_SYSTEM_LEVEL    0
#endif
#if !defined(MASK_NO_INTERRUPT_LEVEL)
#define MASK_NO_INTERRUPT_LEVEL 0xFFFFFFFF
#endif

/*
 *  CUSTOMIZATION REQUIRED
 *
 *  The following defines are used on some processors (particularly TES, or
 *  Intel-based) for masking interrupts used within the system.  Examples are
 *  given based on standard TES configuration.
 *
 *  Masks of TES interrupts which must be coordinated with startup.asm
 */
#define TIMERMASK   0x0001           /* TES  timer interrupt mask           */

#if defined(DSC)
#define DSCMASK     0x0010           /* interrupt controller mask register  */
#endif

#if defined(ACFA)
#define ACFAMASK    0x0040           /* interrupt controller mask register  */
#endif

#if defined(ISAC)
#define ISACSMASK   0x0010           /* interrupt controller mask register  */
#endif

#if defined(T7250C)
#define T725CMASK   0x0010           /* interrupt controller mask register  */
#endif

#if defined(TES)
#define L4_CEMASK   0x0020           /* TES layer 4-to-CE mask BIT POSITION */
#endif
#if defined(SIPB_7500)
#define L4_CEMASK   0x0080           /* TES layer 4-to-CE mask BIT POSITION */
#endif

#if defined(HSCX) || defined(MU32)
#if defined(M68K)
#define BCH_MASK   0x00         /* Don't really care for Motorola 68K  */
#endif
#if defined(_AM29K)
#define BCH_MASK   0x80         /* Don't really care for AMD 29K       */
#endif
#if defined(TES)
#define BCH_MASK   0x80          /* no DMA interrupts for HSCX        */
#endif
#if defined(SIPB_7500)
#define BCH_MASK   0x20          /* no DMA interrupts for HSCX        */
#endif
#endif /* end of if defined(HSCX) */

#if defined(ITAC)
#define BCH_MASK   0x40         /* ITAC interrupt */
#endif
#if defined(PASSIVE)
#define BCH_MASK   0x00          /*don't care for passive             */
#endif
/*  End of CUSTOMIZATION REQUIRED section */

/*  The purpose is to define H0 defines for the use of PRI. */

/* PRI H0 channels */
#define H0_1_6          0x40  /* B-channels 1-6   */
#define H0_7_12         0x41  /* B-channels 7-12  */
#define H0_13_18        0x42  /* B-channels 13-18 */
#define H0_19_24        0x43  /* B-channels 19-24 */
/* CEPT only */
#define H0_25_30        0x44  /* B-channels 25-30 */
#define H11             0x45  /*  all B-channels on a single interface */

/*
 *  NO_DV should usually be defined -- code changes required otherwise
 *  Current implementation of Digitized Voice support requires DSC and
 *  can only be used under an assembly language interrupt service routine
 */
#define NO_DV     /* NO Digitized Voice */

/*
 *  TIMERS should usually be defined -- code changes required otherwise
 *  when set, hardware timers are active
 */
#if defined(PASSIVE)
#if !defined(WIN_31)
/*
 *    place code and data into locked segments
 */
#pragma code_seg("_LTEXT")
#pragma data_seg("_LDATA")
#endif
#else
#define TIMERS  /* when set, hardware timers are active */
#endif

/*
 *  The purpose is for removing TsLink3 logging calls if TSI_LOG is not defined.
 *
 *  CUSTOMIZATION may be needed if the pre-processor will not remove the
 *  calls to log_msg() and log_hex()
 */
#if !defined(TSI_LOG)
#define log_hex(a) /* log_hex REMOVED */
#define log_hex_string(a, b) /* log_hex_string REMOVED */
#define log_msg(a) /* log_msg REMOVED */
#endif

/* NUCLEUS does not use the set_reg() to reset A5, so null out the define */
#if defined(NUCLEUS_PLUS)
#define set_reg()
#endif

/* MQX does not use the set_reg to reset A5 */
#if defined(MQX)
#define set_reg()
#endif

#if defined(MIDAS_EXTERNAL)
#define pulseLED(mask) \
{extern unsigned char Led_pulse; Led_pulse |= mask;}
#endif

#if defined(CAS_R2)
#define MF_TONE_1                               '1'
#define MF_TONE_2                               '2'
#define MF_TONE_3                               '3'
#define MF_TONE_4                               '4'
#define MF_TONE_5                               '5'
#define MF_TONE_6                               '6'
#define MF_TONE_7                               '7'
#define MF_TONE_8                               '8'
#define MF_TONE_9                               '9'
#define MF_TONE_10                              'A'
#define MF_TONE_11                              'B'
#define MF_TONE_12                              'C'
#define MF_TONE_13                              'D'
#define MF_TONE_14                              'E'
#define MF_TONE_15                              'F'
#endif

/* defines for supported combinations of T1 framing/line code/AB bits */
#define T1_ESF_B8ZS_ABCD             20   /* arbitrary non-zero value */
#define T1_D4_B7ZS_AB                40   /* arbitrary non-zero value */
/* SB Add to support AMI */
#define T1_ESF_AMI_ABCD              21   /* arbitrary non-zero value */

/* PRI BACKUP D-CHANNEL STATE DEFINES */
#define BACKUP_D_STATE_OOS                  0x01
#define BACKUP_D_STATE_WAIT                 0x02
#define BACKUP_D_STATE_IS                   0x03
#define BACKUP_D_STATE_MB                   0x04
#define BACKUP_D_STATE_STBY                 0x05
#define BACKUP_D_STATE_MOOS                 0x06
#define BACKUP_D_NOT_IN_USE                 0x07

/* TsLink3 Linux app-to-loadable module write request struct */
struct  req_data_xfer {
        int                 requestor_pid; /* process ID */
        struct l4_ce_l3_msg *l4_ce_ptr;
        unsigned short      *connid;       /* only used for N_CONN_RQ */
        unsigned char       *tsl3_ipb_ptr; /* Indirect Parm Block */
        unsigned short      datalen;       /* length of IPB */
};


#endif /* end of #if !defined(__TSLINK3_H_) */
