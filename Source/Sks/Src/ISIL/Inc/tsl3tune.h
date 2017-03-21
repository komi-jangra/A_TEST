/**********************************************************************/
/*                                                                    */
/*  Copyright (C) 1992-2004 by TeleSoft International, Inc.           */
/*                                                                    */
/*  These computer program listings and specifications,               */
/*  herein, are the property of TeleSoft International, Inc.          */
/*  and shall not be reproduced or copied or used in whole or in      */
/*  part without written permission from TeleSoft International, Inc. */
/*                                                                    */
/**********************************************************************/

#if !defined(__TSL3TUNE_H_)
#define __TSL3TUNE_H_

/*
 *  Extensive comments and explanations are now available in the file
 *  'tsl3tune.txt' which may be found in the 'src\include' directory.
 *
 *  This file is for a Embedded Planet EP8280 board, and is used for
 *  development and test of various MPC82XX drivers.
 */

#define CODE_MCC_IFC	/* Uncomment this to compile for MCC loopback */
#undef ARCHIVE

/* TEST DEFINES
 */

/* Define one of these:
 */
#define TEST_FRAME_RELAY 

#if defined(TEST_FRAME_RELAY)
/* Enable this flag to test UNI - NNI - NNI - UNI
 */

#if !defined NNI_DEMO
#else
#define BI_DIRECTIONAL_POLL
#endif
#endif

/*
 *  After this point BE CAREFUL to modify the defines !
 */
#define LINUX_APP /* for L4CE & CEL4 prim printfs in TSL3_APP */

/*
 *  GLOBAL CONFIGURATION CONDITIONAL COMPILATION DEFINES
 */
#define LINUX

#define DEMO /* for generating L4CE and CEL4 prim printfs in TSL3_APP */

/*
 *  GLOBAL CONFIGURATION CONDITIONAL COMPILATION DEFINES
 */

#define MULT_IFC
#define LAPD_ONLY
#if defined(NNI_DEMO)
#define NUM_IFC         8
#else
#define NUM_IFC         80
#endif /* NNI_DEMO */

#define TRANS_PCHAN     1

#if defined(TEST_FRAME_RELAY)
#define FRM_RLY
#endif /* TEST_FRAME_RELAY */

/*
 *  OPERATIONAL and LOGGING DEFINES
 */
#define LOG_ERRS
#define NLS_TRACE /* enables logging of NLS functions entries */
#define TSI_LOG
#define LOG_TO_LINUX_CONSOLE
#define LOG_NO_LF_CR	/* Comment this define if you want all the log_hex terminate with a CR/LF */
#define ONE_SEC_MESSAGE "#"

/* Supplementary Services miscellaneous defines */
#define SS_MAX_CALL_APPEAR    10
#define DISP_LINE_MAXLEN      80

/*
 *  BEARER CAPABILITY SUPPORT DEFINES
 */
#if defined(TEST_FRAME_RELAY)
#define TSL3_B_DATA
#endif /* TEST_FRAME_RELAY */

/* US NI2 Bearer Capability Defines */
#define BC0
#define BC1
#define BC3

/*
 *  maximum number of X.25 Permanent Virtual Circuits supported
 *  NOTE: If file "ceme\sh_mem.asm" is used (Intel 80X8X processors),
 *       if MAXPVC changes, sh_mem.asm Shmem_cup_parm size must change
 *       as must l4_ifc.h OFFSETs in shared mem if TsLink3 PC plug-in
 *       card example Layer 4 software is used
 */
#if defined(TEST_FRAME_RELAY)
#define MAXPVC         6
#else
#define MAXPVC         2
#endif /* TEST_FRAME_RELAY */

/* defines related to X.25 Logical Channel Indentifier (LCI) */
#define MAX_D1_LCI  8   /* max number of D-Ch. 1-way outgoing LCIs     */
#define MAX_D2_LCI  8   /* max number of D-Ch. 2-way LCIs              */
#define MAX_B1_LCI  8   /* max number of B-Ch. 1-way outgoing LCIs     */
#define MAX_B2_LCI  8   /* max number of B-Ch. 2-way LCIs              */
#define MAX2_B1_LCI 8   /* max number of 2nd B-Ch. 1-way outgoing LCIs */
#define MAX2_B2_LCI 8   /* max number of 2nd B-Ch. 2-way LCIs          */

#define NO_V110_LLC

/*
 *  HARDWARE PLATFORM DEFINES
 */
#define M8280
#if defined(M8260) || defined(M8280)
#define M82XX
#endif
#define MCP60 /* Moto MC68360, MCP860, or similar device with QUIC 60 CPM */
#define CLKF 25 /* CLKF, CPU frequency; should match AFLAGS */
#define SYS_CLK_PERIOD 8000 /* 8 msec */

#define I_DP

#define SPLITFLOW
#define MED_BUFS          /* Added support for medium size buffers. */

/*
 *  DUAL-PORT RAM DEFINES
 */
#define BUFS_NOT_SHARED
#define ONLY_LOG_IN_SH_MEM        /* place only the log in shared RAM */
#define SHARE_MEM_SIZE  0x1000    /* MIDAS-ULC = 4k bytes */
#define SWAP_SH_MEM_BYTES

/*
 *  OPERATING SYSTEM DEFINES
 */
#define ELINUX_OS
#define OS_TASK_STACK_SIZE 8192  /* total bytes for each task stack*/

#define ELINUX_OS

/*
 *  GLOBAL PARAMETER DEFINES
 */
#define HDLC_PCHAN 3
/*
 *  NOTE: For the M302/M360, HDLC_PCHAN is set to 3 whether one SCC is
 *       configured as a UART or not.  This is because the M302/M360 UART
 *       SCC is processed in much the same way as an HDLC SCC.
 */
#define MAX_DN        2
#define MAX_TEI_CNT   2

#if defined(TEST_FRAME_RELAY)
#define SYSPKTSIZ 512   /* System packet size for DATA packets        */
#else
#define SYSPKTSIZ 320   /* System packet size for DATA packets        */
#endif

#define SYS_CONNS ((NUM_IFC * 31) + 1)     /* Number of logical connections supported    */

#define V110_NUM_CONNS   1 /* Number of V110 connections possible at one time */

/*
 *  NOTE: If file "ceme\sh_mem.asm" is used (Intel 80X8X processors),
 *        if MAX_B_CH changes, sh_mem.asm Shmem_cup_parm size must change
 *        as must l4_ifc.h OFFSETs in shared mem if TsLink3 PC plug-in
 *        card example Layer 4 software is used
 */
#define MAX_B_CH_T1   23   /*  T1     */
#define MAX_B_CH_CEPT 30   /*  CEPT   */
#define MAX_B_CH   10

/*
 *  NOTE: If file "ceme\sh_mem.asm" is used (Intel 80X8X processors),
 *       if DN_MAXLEN changes, sh_mem.asm Shmem_cup_parm size must change
 *       as must l4_ifc.h OFFSETs in shared mem if TsLink3 PC plug-in
 *       card example Layer 4 software is used
 *
 *  NOTE: A value of 20 only allows 19 digits - must have room for
 *       terminating null
 */
#define DN_MAXLEN       41 /* Q.931 Directory Number Max Length  */
#define SDN_MAXLEN      24 /* Q.931 Subaddress Number Max Length */

/* note both DN and SDN lengths include one space for the terminating null
 * in SAVEDN length one is used for a null, the other is used for the delimiter
 */
#define  SAVEDN_MAXLEN   DN_MAXLEN+SDN_MAXLEN

#define  PROG_NAME  "TsLink3(R) M8280 Ver 11.6"
#define  PRNM_LNTH  26

#define MAX_DATA_BCHAN    1     /* VERY 2 */

/*
 *  LLD DEFINES
 *
 *  This files contains 2 different setting for test purpose
 *  The first one is the Hw support (the one will be enabled at the end of the development)
 *  The second one is the one under test
 */

/*
 * Start of section 3a
 */
#if defined(CODE_MCC_IFC)

#define D_MCC_HDLC	0x2006

void reg_mcc();

#define MAX_LLDS 12 /* Number of LLDs to be registered by this implementation */
#define LOAD_LLD_DEBUG
#define LOAD_ULLD_DEBUG
#define DEBUG_LLD

#define LLD_REGS { \
    reg_mcc();     \
}

#define LLD_ARRAY { \
    D_MCC_HDLC,     \
    0xffff          \
}

//#include <lld.h>

#endif
/*
 * End of section 3a
 */

/*
 *  Include the file tslink3.h, which contains some configuration items which
 *  are not really "tuneable" since, if changed, they require modifications
 *  to the software.
 *
 *  Note that this should be included at the end of the file, since some
 *  defined constants are dependent on values defined within tsl3tune.h
 */

//#include <tslink3.h>
//#include <compiler.h>

#endif /* __TSL3TUNE_H_ */
