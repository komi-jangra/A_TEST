/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *  ID: $Id: cpm2_mcc.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:23  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:02  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.2  2006/07/05 13:28:34  gdevanand
 * LOG: Changes for combined MTP2 and LAPD driver (badri)
 * LOG:
 * LOG: Revision 1.1.2.1  2006/06/16 10:43:35  sjaddu
 * LOG: Required for mtp2.
 * LOG:
 * LOG: Revision 1.1.2.2  2006/03/16 21:14:23  lbana
 * LOG: Added padding to the struct and also fixed odd/even bit
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 18:23:52  lbana
 * LOG: define mpc8560 specifics here.
 * LOG:
 ***************************************************************************/
/*
 * CPM2 MCC Control definitions and macros
 * Copyright (c) 2005 Mitch Miers (mmiers@cfl.rr.com)
 *
 * The MCC layout for devices with MCC controllers.  Not all
 * CPM2 devices will have MCCs.
 */
#ifdef __KERNEL__
#ifndef __CPM2_MCC_H__
#define __CPM2_MCC_H__

#include <asm/types.h>

#include <asm/immap_cpm2.h>

#include <asm/cpm2_misc.h>

/*
 * MCC Global Paramters (live in DPRAM)
 */
typedef struct
{
    u32  mccbase;    /* A pointer to starting address of BD rings.            */
    u16  mccstate;   /* Controller state.                                     */
    u16  mrblr;      /* Maximum receive buffer length.                        */
    u16  grfthr;     /* Global receive frame threshold.                       */
    u16  grfcnt;     /* Global receive frame counter.                         */
    u32  rinttmp;    /* Temporary location for receive interrupt table entry. */
    u32  data0;      /* Temporary location for holding data.                  */
    u32  data1;      /* Temporary location for holding data.                  */
    u32  tintbase;   /* Transmit interrupt table base address.                */
    u32  tintptr;    /* Transmit interrupt table pointer.                     */
    u32  tinttmp;    /* Temporary location for Tx interrupt table entry.      */
    u16  sctpbase;   /* A pointer to the super channel transmit table.        */
    u8   res0[2];    /* Reserved area.                                        */
    u32  c_mask32;   /* CRC constant.                                         */
    u16  xtrabase;   /* A pointer to the beginning of extra parameters        */
    u16  c_mask16;   /* CRC constant.                                         */
    u32  rinttmp0;   /* Temporary location for Rx interrupt table entry.      */
    u32  rinttmp1;   /* Temporary location for Rx interrupt table entry.      */
    u32  rinttmp2;   /* Temporary location for Rx interrupt table entry.      */
    u32  rinttmp3;   /* Temporary location for Rx interrupt table entry.      */
    u32  rintbase0;  /* Receive interrupt table base address.                 */
    u32  rintptr0;   /* Receive interrupt table pointer.                      */
    u32  rintbase1;  /* Receive interrupt table base address.                 */
    u32  rintptr1;   /* Receive interrupt table pointer.                      */
    u32  rintbase2;  /* Receive interrupt table base address.                 */
    u32  rintptr2;   /* Receive interrupt table pointer.                      */
    u32  rintbase3;  /* Receive interrupt table base address.                 */
    u32  rintptr3;   /* Receive interrupt table pointer.                      */
    u32  ts_tmp;     /* Temporary location for time stamp.                    */
    u8   res1[0x1c]; /* Reserved.                                             */
}
mcc_global_param_t;

/*
 * Maximum number of channels
 */
#define MCC_COUNT               2
#define MCC_CHANS_PER_TDM_E1    32
#define MCC_CHANS_PER_TDM_T1    32
#define MCC_MAX_CHAN_NORMAL     128
#define MCC_MAX_CHAN_SS7        64
#define MCC_TDMS_PER_MCC        4

/*
 * Channel extra parameters
 */
typedef struct
{
    u16  tbase;    /* TxBD base address.  Offset of TxBD relative to mccbase */
    u16  tptr;     /* TxBD pointer.  Init to tbase                           */
    u16  rbase;    /* RxBD base address.  Offset of RxBD relative to mccbase */
    u16  rptr;     /* RxBD pointer.  Init to rbase                           */
}
mcc_channel_extra_param_t;

/*
 * Super channel entry
 */
typedef struct
{
    u16 channel;   /* Bits 6 through 13 should have the virtual channel num  */
}
mcc_super_channel_param_t;

/*
 * Channel specific (HDLC) parameters.
 */
typedef struct
{
    u32  tstate;     /* Tx internal state.                                   */ 
    u32  zistate;    /* Zero insertion machine state.                        */
    u32  zidata0;    /* Zero insertion high word.                            */
    u32  zidata1;    /* Zero insertion low word.                             */
    u16  tbdflags;   /* Tx internal BD flags.                                */
    u16  tbdcnt;     /* Tx internal byte count.                              */
    u32  tbdptr;     /* Tx internal data pointer.                            */
    u16  intmask;    /* Interrupt mask flags.                                */
    u16  chamr;      /* channel mode register.                               */
    u32  tcrc;       /* Temp receive CRC.                                    */
    u32  rstate;     /* Rx internal state.                                   */ 
    u32  zdstate;    /* Zero deletion machine state.                         */
    u32  zddata0;    /* Zero deletion  high word.                            */
    u32  zddata1;    /* Zero deletion  low word.                             */
    u16  rbdflags;   /* Rx internal BD flags.                                */
    u16  rbdcnt;     /* Rx internal byte count.                              */
    u32  rbdptr;     /* Rx internal data pointer.                            */
    u16  mflr;       /* Max receive frame length.                            */
    u16  maxcnt;     /* Max length counter.  Read only                       */
    u32  rcrc;       /* Temp receive CRC.                                    */
}
mcc_channel_specific_hdlc_t;

/*
 * Channel specific (transparent) parameters
 */
typedef struct
{
    u32  tstate;     /* Tx internal state.                                   */ 
    u32  zistate;    /* Zero insertion machine state.                        */
    u32  zidata0;    /* Zero insertion high word.                            */
    u32  zidata1;    /* Zero insertion low word.                             */
    u16  tbdflags;   /* Tx internal BD flags.                                */
    u16  tbdcnt;     /* Tx internal byte count.                              */
    u32  tbdptr;     /* Tx internal data pointer.                            */
    u16  intmask;    /* Interrupt mask flags.                                */
    u16  chamr;      /* channel mode register.                               */
    u32  reserved;   /* Reserved.                                            */
    u32  rstate;     /* Rx internal state.                                   */ 
    u32  zdstate;    /* Zero deletion machine state.                         */
    u32  zddata0;    /* Zero deletion  high word.                            */
    u32  zddata1;    /* Zero deletion  low word.                             */
    u16  rbdflags;   /* Rx internal BD flags.                                */
    u16  rbdcnt;     /* Rx internal byte count.                              */
    u32  rbdptr;     /* Rx internal data pointer.                            */
    u16  tmrblr;     /* Transparent maximum receive buffer length.           */
    u16  rcvsync;    /* Receive synchronization pattern.                     */
    u32  reserved1;  /* Reserved.                                            */
}
mcc_channel_specific_transparent_t;

/*
 * Channel specific (SS7) parameters
 */
typedef struct
{
    u32  tstate;     /* Tx internal state.                                   */ 
    u32  zistate;    /* Zero insertion machine state.                        */
    u32  zidata0;    /* Zero insertion high word.                            */
    u32  zidata1;    /* Zero insertion low word.                             */
    u16  tbdflags;   /* Tx internal BD flags.                                */
    u16  tbdcnt;     /* Tx internal byte count.                              */
    u32  tbdptr;     /* Tx internal data pointer.                            */
    u32  echamr;     /* Extended channel mode register.                      */
    u32  tcrc;       /* Temporary transmit CRC.                              */
    u32  rstate;     /* Rx internal state.                                   */ 
    u32  zdstate;    /* Zero deletion machine state.                         */
    u32  zddata0;    /* Zero deletion  high word.                            */
    u32  zddata1;    /* Zero deletion  low word.                             */
    u16  rbdflags;   /* Rx internal BD flags.                                */
    u16  rbdcnt;     /* Rx internal byte count.                              */
    u32  rbdptr;     /* Rx internal data pointer.                            */
    u16  mflr;       /* Maximum frame length register.                       */
    u16  max_cnt;    /* Max length counter. Read only.                       */
    u32  rcrc;       /* Temp receive CRC.                                    */
    union
    {
        struct
        {
            u16  n;     /* Interrupt threshold in octet counting mode.       */
            u16  n_cnt; /* Current value of N                                */
            u16  d;     /* SU to SUER ratio.                                 */
            u16  d_cnt; /* Current value of D                                */
        }
        ansi_itu;
        struct
        {
            u32  tmstmp;/* Temporary storage for time stamp.                 */
            u16  d;     /* SU to SUER ratio.                                 */
            u16  delay; /* FISU retransmission delay.                        */
        }
        jtt;
    }
    familydata;
    u32 mask1;       /* Mask for SU filtering, bytes 0-3                     */
    u16 mask2;       /* Mask for SU filtering, byte 4.                       */
    u16 ss7_opt;     /* SS7 configuration register.                          */
    u32 lrb1_tmp;    /* Temp storage for SU filtering.                       */
    u16 lrb2_tmp;    /* Temp storage for SU filtering.                       */
    u16 suerm;       /* SUERM counter.                                       */
    u32 lrb1;        /* First four bytes of last signal.                     */
    u16 lrb2;        /* Fifth byte of last signal.                           */
    u16 t;           /* SUERM error threshold.                               */
    u32 lhdr;        /* BSN, BIB, FSN, FIB, and CRC of last SU.              */
    u32 lhdr_tmp;    /* Temp storage for auto FISU transmission.             */
    u32 efsuc;       /* Error free signal unit counter.                      */
    u32 suec;        /* Signal unit error counter.                           */
    u32 ss7state;    /* Internal state.                                      */
    u32 tmpstmp;     /* Temp storage for time stamp. Japanese only.          */
    u16 delay;       /* FISU transmit delay.  Japanese only.                 */
    u16 m;           /* AERM threshold.  ANSI/ITU only.                      */
    u16 m_cnt;       /* Counter for m. ANSI/ITU only.                        */
    u16 pad;         /* Compiler adds this anyway                            */
}
mcc_channel_specific_ss7_t;

/*
 * TSTATE: Table 33-4
 */
/*
 * Global snooping.  0: off, 1: on
 */
#define MCC_TSTATE_GLB_SHIFT 29
#define MCC_TSTATE_GLB_SNOOP_OFF    (0U<<MCC_TSTATE_GLB_SHIFT)
#define MCC_TSTATE_GLB_SNOOP_ON     (1U<<MCC_TSTATE_GLB_SHIFT)

/*
 * Big endian mode.  One assumes RSVD is little endian
 */
#define MCC_TSTATE_BE_SHIFT 27
#define MCC_TSTATE_BE_RSVD          (0U<<MCC_TSTATE_BE_SHIFT)
#define MCC_TSTATE_BE_BIG_END       (3U<<MCC_TSTATE_BE_SHIFT)

/*
 * Data Bus Indicator.  Selects the bus for accessing data buffers
 */
#define MCC_TSTATE_DTB_SHIFT 25
#define MCC_TSTATE_DTB_SYSTEM       (0U<<MCC_TSTATE_DTB_SHIFT)
#define MCC_TSTATE_DTB_LOCAL        (1U<<MCC_TSTATE_DTB_SHIFT)

/*
 * Buffer Descriptor indicator.  Selects the bus for accessing BDs.
 */
#define MCC_TSTATE_BDB_SHIFT 24
#define MCC_TSTATE_BDB_SYSTEM       (0U<<MCC_TSTATE_BDB_SHIFT)
#define MCC_TSTATE_BDB_LOCAL        (1U<<MCC_TSTATE_BDB_SHIFT)

/*
 * Start bit
 */
#define MCC_TSTATE_START_SHIFT 23
#define MCC_TSTATE_START            (1U<<MCC_TSTATE_START_SHIFT)

/*
 * Mask
 */
#define MCC_TSTATE_MASK             (0xFF800000U)

/*
 * ZISTATE: Zero Insertion state
 */
#define MCC_ZISTATE_REGULAR         (0x10000207U)
#define MCC_ZISTATE_INVERTED        (0x30000207U)

/*
 * ZINSERT: user intialization for high/low word
 */
#define MCC_ZIDATA_HL_WORD          (0xFFFFFFFFU) 

/*
 * ZDSTATE: Zero Deletion state
 */
#define MCC_ZDSTATE_REGULAR         (0x00FFFFE0U)
#define MCC_ZDSTATE_INVERTED        (0x20FFFFE0U)

/*
 * For transparent only.  Value of CHAMR[SYNC] and regular or inverted 
 * determines which value to use.
 */
#define MCC_ZDSTATE_SYNC_RSYNC0_REG (0x00FFFFE0U)
#define MCC_ZDSTATE_SYNC_RSYNC0_INV (0x00000000U)
#define MCC_ZDSTATE_NOSYNC_REG      (0x50FFFFE0U)
#define MCC_ZDSTATE_NOSYNC_INV      (0x70FFFFE0U)

/*
 * ZDELETE: user initialization for high/low word
 */
#define MCC_ZDDATA_HL_WORD          (0xFFFFFFFFU)

/*
 * Interrupt Mask (INTMASK) Register. 
 * To enable an interrupt, set the corresponding bit. If a bit is cleared,
 * no interrupt request is generated and no new entry is written in the
 * circular interrupt table. The user must initialize INTMSK prior to
 * operation. Reserved bits are cleared. 
 */
#define MCC_IM_OCT_SHIFT 13
#define MCC_INTMASK_OCT       (1U<<MCC_IM_OCT_SHIFT)

#define MCC_IM_SUERM_SHIFT 12
#define MCC_INTMASK_SUERM     (1U<<MCC_IM_SUERM_SHIFT)

#define MCC_IM_FISU_SHIFT 11
#define MCC_INTMASK_FISU      (1U<<MCC_IM_FISU_SHIFT)

#define MCC_IM_UN_SHIFT 9
#define MCC_INTMASK_UN        (1U<<MCC_IM_UN_SHIFT)

#define MCC_IM_TXB_SHIFT 8
#define MCC_INTMASK_TXB       (1U<<MCC_IM_TXB_SHIFT)

#define MCC_IM_AERM_SHIFT 6
#define MCC_INTMASK_AERM      (1U<<MCC_IM_AERM_SHIFT)

#define MCC_IM_NID_SHIFT 5
#define MCC_INTMASK_NID       (1U<<MCC_IM_NID_SHIFT)

#define MCC_IM_IDL_SHIFT 4
#define MCC_INTMASK_IDL       (1U<<MCC_IM_IDL_SHIFT)

#define MCC_IM_MRF_SHIFT 3
#define MCC_INTMASK_MRF       (1U<<MCC_IM_MRF_SHIFT)

#define MCC_IM_RXF_SHIFT 2
#define MCC_INTMASK_RXF       (1U<<MCC_IM_RXF_SHIFT)

#define MCC_IM_BSY_SHIFT 1
#define MCC_INTMASK_BSY       (1U<<MCC_IM_BSY_SHIFT)

#define MCC_IM_RXB_SHIFT 0
#define MCC_INTMASK_RXB       (1U<<MCC_IM_RXB_SHIFT)
                                         
/*
 * Channel Mode Register (CHAMR).
 */
/*
 * Mode: Determines transparent or HDLC
 */
#define MCC_CHAMR_MODE_SHIFT 15
#define MCC_CHAMR_MODE_TRANS     (0U<<MCC_CHAMR_MODE_SHIFT)
#define MCC_CHAMR_MODE_HDLC      (1U<<MCC_CHAMR_MODE_SHIFT)

/*
 * Polling: Determines polling of TxBDs
 */
#define MCC_CHAMR_POL_SHIFT 14
#define MCC_CHAMR_POL_DISABLE    (0U<<MCC_CHAMR_POL_SHIFT)
#define MCC_CHAMR_POL_ENABLE     (1U<<MCC_CHAMR_POL_SHIFT)

/*
 * Fixed bits.  Must be set.
 */
#define MCC_CHAMR_FIXED_BITS_HDLC ((1U<<13)|(0U<<11)|(0U<<9)|(0U<<8)|(0U<<6))
#define MCC_CHAMR_FIXED_BITS_TRAN ((3U<<12)|(0U<<7)|(0U<<6)|(0U<<2)|(0U<<1)|0U)
#define MCC_CHAMR_RESET_HDLC     MCC_CHAMR_FIXED_BITS_HDLC
#define MCC_CHAMR_RESET_TRAN     MCC_CHAMR_FIXED_BITS_TRAN

/*
 * Idle mode (HDLC only)
 */
#define MCC_CHAMR_IDLE_SHIFT 12
#define MCC_CHAMR_IDLM_OFF       (0U<<MCC_CHAMR_IDLE_SHIFT)
#define MCC_CHAMR_IDLM_ON        (1U<<MCC_CHAMR_IDLE_SHIFT)

/*
 * Empty Polarity (Transparent only)
 */
#define MCC_CHAMR_PE_SHIFT 11
#define MCC_CHAMR_PE_POS         (0U<<MCC_CHAMR_IDLE_SHIFT)
#define MCC_CHAMR_PE_NEG         (1U<<MCC_CHAMR_IDLE_SHIFT)

/*
 * Reverse bits
 */
#define MCC_CHAMR_RD_SHIFT 10
#define MCC_CHAMR_RD_NORMAL      (0U<<MCC_CHAMR_RD_SHIFT)
#define MCC_CHAMR_RD_REVERSE     (1U<<MCC_CHAMR_RD_SHIFT)

/*
 * Sync (Transparent only)
 */
#define MCC_CHAMR_SYNC_SHIFT 8
#define MCC_CHAMR_SYNC_NONE      (0U<<MCC_CHAMR_SYNC_SHIFT)
#define MCC_CHAMR_SYNC_SLOT      (1U<<MCC_CHAMR_SYNC_SHIFT)
#define MCC_CHAMR_SYNC_8BIT      (2U<<MCC_CHAMR_SYNC_SHIFT)
#define MCC_CHAMR_SYNC_16BIT     (3U<<MCC_CHAMR_SYNC_SHIFT)

/*
 * CRC type (HDLC only)
 */
#define MCC_CHAMR_CRC_SHIFT 7
#define MCC_CHAMR_CRC_16         (0U<<MCC_CHAMR_CRC_SHIFT)
#define MCC_CHAMR_CRC_32         (1U<<MCC_CHAMR_CRC_SHIFT)

/*
 * TimeStamp
 */
#define MCC_CHAMR_TS_SHIFT 5
#define MCC_CHAMR_TS_OFF         (0U<<MCC_CHAMR_TS_SHIFT)
#define MCC_CHAMR_TS_ON          (1U<<MCC_CHAMR_TS_SHIFT)

/*
 * Receive Queue Number
 */
#define MCC_CHAMR_RQN_SHIFT 3
#define MCC_CHAMR_RQN_MASK       (3U<<MCC_CHAMR_TS_SHIFT)
#define MCC_CHAMR_RQN_0          (0U<<MCC_CHAMR_TS_SHIFT)
#define MCC_CHAMR_RQN_1          (1U<<MCC_CHAMR_TS_SHIFT)
#define MCC_CHAMR_RQN_2          (2U<<MCC_CHAMR_TS_SHIFT)
#define MCC_CHAMR_RQN_3          (3U<<MCC_CHAMR_TS_SHIFT)

/*
 * Number of flags (HDLC only)
 */
#define MCC_CHAMR_NOF_SHIFT 0
#define MCC_CHAMR_NOF_MASK       (7U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_1          (0U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_2          (1U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_3          (2U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_4          (3U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_5          (4U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_6          (5U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_7          (6U<<MCC_CHAMR_NOF_SHIFT)
#define MCC_CHAMR_NOF_8          (7U<<MCC_CHAMR_NOF_SHIFT)

/*
 * RSTATE: Table 33-6
 */
/*
 * Global snooping.  0: off, 1: on
 */
#define MCC_RSTATE_GLB_SHIFT 29
#define MCC_RSTATE_GLB_SNOOP_OFF    (0U<<MCC_RSTATE_GLB_SHIFT)
#define MCC_RSTATE_GLB_SNOOP_ON     (1U<<MCC_RSTATE_GLB_SHIFT)

/*
 * Big endian mode.  One assumes RSVD is little endian
 */
#define MCC_RSTATE_BE_SHIFT 27
#define MCC_RSTATE_BE_RSVD          (0U<<MCC_RSTATE_BE_SHIFT)
#define MCC_RSTATE_BE_BIG_END       (3U<<MCC_RSTATE_BE_SHIFT)

/*
 * Data Bus Indicator.  Selects the bus for accessing data buffers
 */
#define MCC_RSTATE_DTB_SHIFT 25
#define MCC_RSTATE_DTB_SYSTEM       (0U<<MCC_RSTATE_DTB_SHIFT)
#define MCC_RSTATE_DTB_LOCAL        (1U<<MCC_RSTATE_DTB_SHIFT)

/*
 * Buffer Descriptor indicator.  Selects the bus for accessing BDs.
 */
#define MCC_RSTATE_BDB_SHIFT 24
#define MCC_RSTATE_BDB_SYSTEM       (0U<<MCC_RSTATE_BDB_SHIFT)
#define MCC_RSTATE_BDB_LOCAL        (1U<<MCC_RSTATE_BDB_SHIFT)

/*
 * Start bit
 */
#define MCC_RSTATE_START_SHIFT 23
#define MCC_RSTATE_START            (1U<<MCC_RSTATE_START_SHIFT)

/*
 * Mask
 */
#define MCC_RSTATE_MASK             (0xFF800000U)

/*
 * SS7 Specific parameters
 */
#define MCC_SS7MODE_N_INIT         16U
#define MCC_SS7MODE_N_CNT_INIT     MCC_SS7MODE_N_INIT
#define MCC_SS7MODE_D_INIT         256U
#define MCC_SS7MODE_JSS7_D_INIT    16U
#define MCC_SS7MODE_D_CNT_INIT     MCC_SS7MODE_D_INIT
#define MCC_SS7MODE_JTTDELAY_INIT  (0x2FU)
#define MCC_SS7MODE_SUERM_INIT     0U
#define MCC_SS7MODE_T_INIT         64U
#define MCC_SS7MODE_JSS7_T_INIT    285U
#define MCC_SS7MODE_EFSUC_INIT     0U
#define MCC_SS7MODE_SUEC_INIT      0U
#define MCC_SS7MODE_SS7STATE_INIT  0U
#define MCC_SS7MODE_JTRDELAY_INIT  (0x2FU)
#define MCC_SS7MODE_M_INIT         5U
#define MCC_SS7MODE_M_CNT_INIT     0U

/*
 * ECHAMR
 */
/* 0th & 16th bits are set for ss7 */
#define MCC_ECHAMR_MODE_SS7          ((1U<<31)|(1U<<15))

/*
 * Clear 1, 5, 8 and 20-25 position bits
 * Set bit 18.
 */
#define MCC_ECHAMR_RESERVED_BITS     ((0U<<30)|(0U<<26)|(0U<<23)|(1U<<13)|\
                                      (0U<<11)|(0U<<10)|(0U<<9)|(0U<<8)|\
                                      (0U<<7)|(0U<<6))

/*
 * Interrupt bits.  These extend the HDLC/transparent mask (the astute
 * reader will catch that INTMASK and CHAMR are replaced with ECHAMR).
 * The V and W bits MUST NOT be set in the interrupt mask.
 */
#define MCC_ECHAMR_INTS_SHIFT 16

/*
 * SS7OPT register
 */
#define MCC_SS7OPT_AERM_SHIFT 11
#define MCC_SS7OPT_AERM_DISABLE      (0U<<MCC_SS7OPT_AERM_SHIFT)
#define MCC_SS7OPT_AERM_ENABLE       (1U<<MCC_SS7OPT_AERM_SHIFT)

#define MCC_SS7OPT_SUERM_DIS_SHIFT 10
#define MCC_SS7OPT_ENABLE_SUERM      (0U<<MCC_SS7OPT_SUERM_DIS_SHIFT)
#define MCC_SS7OPT_DISABLE_SU_A_ERM  (1U<<MCC_SS7OPT_SUERM_DIS_SHIFT)

#define MCC_SS7OPT_STD_SHIFT 9
#define MCC_SS7OPT_ANSI_ITU          (0U<<MCC_SS7OPT_STD_SHIFT)
#define MCC_SS7OPT_JSS7              (1U<<MCC_SS7OPT_STD_SHIFT)

#define MCC_SS7OPT_SF_DIS_SHIFT 8
#define MCC_SS7OPT_SF_DIS_KEEP       (0U<<MCC_SS7OPT_SF_DIS_SHIFT)
#define MCC_SS7OPT_SF_DIS_TOSS       (1U<<MCC_SS7OPT_SF_DIS_SHIFT)

#define MCC_SS7OPT_SU_FIL_SHIFT 7
#define MCC_SS7OPT_SU_FIL_DISABLE    (0U<<MCC_SS7OPT_SU_FIL_SHIFT)
#define MCC_SS7OPT_SU_FIL_ENABLE     (1U<<MCC_SS7OPT_SU_FIL_SHIFT)

#define MCC_SS7OPT_SEN_FIS_SHIFT 6
#define MCC_SS7OPT_SEN_FIS_FLAGS     (0U<<MCC_SS7OPT_SEN_FIS_SHIFT)
#define MCC_SS7OPT_SEN_FIS_FISUS     (1U<<MCC_SS7OPT_SEN_FIS_SHIFT)

#define MCC_SS7OPT_O_ORN_SHIFT 5
#define MCC_SS7OPT_O_ORN_DISABLE     (0U<<MCC_SS7OPT_O_ORN_SHIFT)
#define MCC_SS7OPT_O_ORN_ENABLE      (1U<<MCC_SS7OPT_O_ORN_SHIFT)

#define MCC_SS7OPT_O_ITUT_SHIFT 4
#define MCC_SS7OPT_O_ITUT_DISABLE    (0U<<MCC_SS7OPT_O_ITUT_SHIFT)
#define MCC_SS7OPT_O_ITUT_ENABLE     (1U<<MCC_SS7OPT_O_ITUT_SHIFT)

#define MCC_SS7OPT_FISU_PAD_SHIFT 0
#define MCC_SS7OPT_FISU_PAD_0        (0U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_1        (1U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_2        (2U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_3        (3U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_4        (4U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_5        (5U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_6        (6U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_7        (7U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_8        (8U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_9        (9U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_10       (10U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_11       (11U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_12       (12U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_13       (13U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_14       (14U<<MCC_SS7OPT_FISU_PAD_SHIFT)
#define MCC_SS7OPT_FISU_PAD_15       (15U<<MCC_SS7OPT_FISU_PAD_SHIFT)

/*
 * MCCF: MCC Configuration Register
 *
 * Group x of channels is used by TDM y shown below:
 * 00=Group x is used by TDM A
 * 01=Group x is used by TDM B
 * 10=Group x is used by TDM C
 * 11=Group x is used by TDM D
 *
 *       Group               Channels
 *  Group 1 in MCCF1          0-31
 *  Group 2 in MCCF1          32-63
 *  Group 3 in MCCF1          64-95
 *  Group 4 in MCCF1          96-127
 *  Group 1 in MCCF2          128-159
 *  Group 2 in MCCF2          160-191
 *  Group 3 in MCCF2          192-223
 *  Group 4 in MCCF2          224-255
 */
#define MCCF_GROUP_TDMa       0
#define MCCF_GROUP_TDMb       1
#define MCCF_GROUP_TDMc       2
#define MCCF_GROUP_TDMd       3

#define MCCF_GROUP1_SHIFT     6U
#define MCCF_GROUP1_MASK      (3U<<MCCF_GROUP1_SHIFT)

#define MCCF_GROUP2_SHIFT     4U
#define MCCF_GROUP2_MASK      (3U<<MCCF_GROUP2_SHIFT

#define MCCF_GROUP3_SHIFT     2U
#define MCCF_GROUP3_MASK      (3U<<MCCF_GROUP3_SHIFT)

#define MCCF_GROUP4_SHIFT     0U
#define MCCF_GROUP4_MASK      (3U<<MCCF_GROUP4_SHIFT)

/*
 * MCCE,MCCM: MCC Event Register/Mask Register
 */
#define MCCE_RQOV0       (1U<<15)  /* Rx interrupt queue overflow */
#define MCCE_RINT0       (1U<<14)  /* Rx interrupt */
#define MCCE_RQOV1       (1U<<13)  /* Rx interrupt queue overflow */
#define MCCE_RINT1       (1U<<12)  /* Rx interrupt */
#define MCCE_RQOV2       (1U<<11)  /* Rx interrupt queue overflow */
#define MCCE_RINT2       (1U<<10)  /* Rx interrupt */
#define MCCE_RQOV3       (1U<<9)   /* Rx interrupt queue overflow */
#define MCCE_RINT3       (1U<<8)   /* Rx interrupt */
#define MCCE_TQOV        (1U<<3)   /* Tx interrupt queue overflow */
#define MCCE_TINT        (1U<<2)   /* Tx interrupt */
#define MCCE_GUN         (1U<<1)   /* Global transmitter underrun */
#define MCCE_GOV         (1U)      /* Global receiver overrun */

/*
 * Read interrupts only
 */
#define MCCE_RINT        (MCCE_RINT0|MCCE_RINT1|MCCE_RINT2|MCCE_RINT3)

/*
 * Enable all interrupts
 */
#define MCCM_SET         (MCCE_RINT0|MCCE_RINT1|MCCE_RINT2|MCCE_RINT3| \
                          MCCE_RQOV0|MCCE_RQOV1|MCCE_RQOV2|MCCE_RQOV3| \
                          MCCE_TINT |MCCE_TQOV |MCCE_GOV  |MCCE_GUN)
/*
 * Clear bits (writing zeros has no effect)
 */
#define MCCE_CLEAR       0xFFFF

/*
 * Interrupt Circular Table Entry.
 */
typedef struct
{
   u16  status;     /* high byte - V bit, W bit, and  interrupt flags. */
   u16  channel;    /* channel number */
}
mcc_interrupt_table_entry_t;
  
/*
 * High word definitions for mcc_interrupt_table_entry_t.
 */
#define MCC_ICTE_V     (1U<<15)  /* Valid entry                   */ 
#define MCC_ICTE_W     (1U<<14)  /* Wrap (last entry)             */ 
#define MCC_ICTE_OCT   (1U<<13)  /* N octets received             */
#define MCC_ICTE_SUERM (1U<<12)  /* SUERM threshold T reached     */
#define MCC_ICTE_FISU  (1U<<11)  /* FISU transmission started     */
#define MCC_ICTE_RSVD1 (1U<<10)  /* Underrun                      */
#define MCC_ICTE_UN    (1U<<9)   /* Reserved                      */
#define MCC_ICTE_TXB   (1U<<8)   /* Tx buffer transmitted         */
#define MCC_ICTE_RSVD2 (1U<<7)   /* Reserved                      */
#define MCC_ICTE_AERM  (1U<<6)   /* AERM threshold M reached      */
#define MCC_ICTE_NID   (1U<<5)   /* Non idle pattern              */
#define MCC_ICTE_IDLE  (1U<<4)   /* Idle                          */
#define MCC_ICTE_MRF   (1U<<3)   /* Max Rx frame length violation */
#define MCC_ICTE_RXF   (1U<<2)   /* Rx Frame received             */
#define MCC_ICTE_BSY   (1U<<1)   /* Busy                          */
#define MCC_ICTE_RXB   (1U)      /* Rx buffer, but not last       */ 

#define MCC_ICTE_SHIFT 16

/*
 * For HDLC ...
 */
#define MCC_ICTE_HDLC  (MCC_ICTE_RXB|MCC_ICTE_BSY|MCC_ICTE_RXF|MCC_ICTE_MRF|\
                        MCC_ICTE_IDLE|MCC_ICTE_NID|MCC_ICTE_TXB|MCC_ICTE_UN)


/*
 * For SS7
 */
#define MCC_ICTE_SS7   (MCC_ICTE_RXB|MCC_ICTE_BSY|MCC_ICTE_RXF|MCC_ICTE_MRF|\
                        MCC_ICTE_IDLE|MCCC_ICTE_NID|MCC_ICTE_AERM|MCC_ICTE_TXB|\
                        MCC_ICTE_UN|MCC_ICTE_FISU|MCC_ICTE_SUERM|MCC_ICTE_OCT)

/*
 * Channel field
 */
#define MCC_ICTE_CHANNEL_SHIFT 6
#define MCC_ICTE_CHANNEL         (0x00003FC0U)

/*
 * BD type
 */
typedef struct
{
    u16 status;
    u16 length;
    u8 *buffer;
}
mcc_channel_bd_t;
    
/*
 * MCC Buffer Descriptor (MCC RxBD).
 */
#define MCC_RXBD_E           (1U<<15) /* Empty.
                                       * 0=Data buffer has been filled 
                                       * 1=Data buffer is empty. Don't write
                                       */ 
#define MCC_RXBD_W           (1U<<13) /* Wrap (final BD in table):
                                       * 0=Not the last BD in the RxBD table
                                       * 1=Last BD in the RxBD table
                                       */
#define MCC_RXBD_I           (1U<<12) /* Interrupt:
                                       * 0=RXB bit is not set
                                       * 1=RXB or RXF bit in HDLC interrupt 
                                       * circular table entry is set
                                       */
#define MCC_RXBD_L           (1U<<11) /* Last in frame (only for HDLC). */
#define MCC_RXBD_F           (1U<<10) /* First in frame. HDLC sets F=1 for 1st
                                       * buffer in a frame. Transparent, F 
                                       * indicates that there was a sync before
                                       * receiving data in this BD:
                                       * 0=Not the 1st buffer in a frame
                                       * 1=This is the 1st buffer in a frame
                                       */
#define MCC_RXBD_CM          (1U<<9)  /* Continuous mode:
                                       * 0=Normal operation.
                                       * 1=The empty bit (E) is not cleared by
                                       * the CP after this BD is closed.
                                       */
#define MCC_RXBD_UB          (1U<<7)  /* User bit. UB is a user-defined bit that
                                       * the CPM never sets or clears.
                                       */  
#define MCC_RXBD_LG          (1U<<5)  /* Rx frame length violation (HDLC only)
                                       */  
#define MCC_RXBD_NO          (1U<<4)  /* Rx nonoctet-aligned frame */
#define MCC_RXBD_AB          (1U<<3)  /* Rx abort sequence */  
#define MCC_RXBD_CR          (1U<<2)  /* Rx CRC error */
#define MCC_RXBD_SF          (1U<<1)  /* Short frame indication (SS7 only) */


/*
 * MCC Transmit Buffer Descriptor (MCC TxBD).
 */
#define MCC_TXBD_R           (1U<<15)  /* Ready:
                                        * 0=Buffer is not ready for Tx
                                        * 1=Buffer is ready for Tx.
                                        */
#define MCC_TXBD_RT          (1U<<14)  /* Retransmit (SS7 only)
                                        * 0=Normal operation
                                        * 1=CP will retransmit this BD until
                                        * this bit is cleared.  Useful for
                                        * auto LSSU retransmission.
                                        */
#define MCC_TXBD_W           (1U<<13)  /* Wrap (final BD in table). */
#define MCC_TXBD_I           (1U<<12)  /* Interrupt:
                                        * 0=No interrupt is generated
                                        * 1=TXB in circular interrupt table
                                        * entry is set when this buffer has
                                        * been serviced by the MCC.
                                        */
#define MCC_TXBD_L           (1U<<11)  /* Last:
                                        * 0=Not the last buffer in frame
                                        * 1=Last buffer in frame.
                                        */ 
#define MCC_TXBD_TC          (1U<<10)  /* Tx CRC. Valid only when L=1:
                                        * 0=Transmit the closing flag after the
                                        * last data byte. For testing.
                                        * 1=Transmit the CRC sequence after the
                                        * last data byte.
                                        */
#define MCC_TXBD_CM          (1U<<9)   /* Continuous mode:
                                        * 0=Normal operation
                                        * 1=CP does not clear R-bit after this 
                                        * BD is closed.
                                        */
#define MCC_TXBD_UB          (1U<<7)   /* User bit. */
#define MCC_TXBD_SUD         (1U<<4)   /* Signal unit delay (SS7 only)
                                        * 0=no delay
                                        * 1=delay of JTTDelay * 512 before
                                        * transmitting.
                                        */
#define MCC_TXBD_PAD_MASK    (0x0FU)   /* Pad characters. These four bits
                                        * indicate number of PAD characters
                                        * (0x7E or 0xFF depending on the IDLM
                                        * mode selected in the CHAMR register)
                                        * that the Tx sends after the closing
                                        * flag.
                                        */ 

/*
 * Tx/Rx BDs must be 8 byte aligned.
 */
#define MCC_BD_ALIGN      8
#define MCC_BUF_ALIGN     8

/*
 * CRC values used by MCC driver.
 */
#define MASK_32BIT_CRC    0xdebb20e3
#define MASK_16BIT_CRC    0x0000f0b8

/*
 * Need this for user interface.  May want to move
 */

/*
 * Error types
 */
typedef enum
{
   TX_ERR_UN,
   RX_ERR_BSY,
   RX_ERR_MFV,
   MCC_ERR_GOV,
   MCC_ERR_GUN,
   MCC_ERR_TQOV,
   MCC_ERR_RQOV0,
   MCC_ERR_RQOV1,
   MCC_ERR_RQOV2,
   MCC_ERR_RQOV3,
   UNKNOWN_ERR
}
mcc_isr_error_t;

/*
 * Channel mode
 */
typedef enum
{
    MCC_TYPE_SS7,
    MCC_TYPE_HDLC,
    MCC_TYPE_TRANS,
    MCC_TYPE_LAPD
}
mcc_chan_mode_t;

/*
 * Channel type
 */
typedef enum
{
    MCC_TXRX,
    MCC_TX,
    MCC_RX
}
mcc_chan_type_t;

/*
 * Error statistics.
 */
typedef struct
{
    u32  rxLengthViolation;  /* Rx frame length violation              */
    u32  rxNonAligned;       /* Rx nonoctet-aligned frame              */
    u32  rxAbort;            /* Rx abort sequence                      */
    u32  rxCRCError;         /* Rx CRC error                           */
    u32  rxOverflow;         /* Rx overflow - frame was too big to fit */
    u32  rxFrames;
    u32  txFrames;
    u32  sigIdle;
    u32  sigNonIdle;
    u32  sigAERM;
    u32  sigFISU;
    u32  sigSUERM;
    u32  sigOCT;
}
mcc_channel_stats_t;

typedef int (*mcc_chan_init_proc_t)(int chan);
typedef void (*mcc_writen_proc_t)(int chan);
typedef void (*mcc_bd_proc_t)(int chan, volatile mcc_channel_bd_t *);
typedef void (*mcc_signal_proc_t)(int chan, u32 signal);
typedef int  (*mcc_prot_cfg_proc_t)(void *arg);

typedef struct
{
    u8                  chan;
    u8                  mode;
    u8                  chan_type;
    u8                  loopback;
    mcc_bd_proc_t       onread;
    mcc_writen_proc_t   onwrite;
    mcc_signal_proc_t   onsignal;
    mcc_channel_stats_t *stats;
}
mcc_chan_config_t;

/*
 * Error types in interrupt
 */
typedef enum
{
   TX_ERR,
   RX_ERR,
   MCC_ERR,
   MAX_ERR_TYPE
}
mcc_error_type_t;

/*
 * Define modes of activation
 */
typedef enum
{
   MCH_NOT_ACTIVE     = 0x0000,
   MCH_RX_ACTIVATE    = 0x0001,
   MCH_TX_ACTIVATE    = 0x0010,
   MCH_RX_TX_ACTIVATE = 0x0011,
   MAX_MCH_ACTIVE_MODE
}
mcc_active_mode_t;

/*
 * Channel management structure
 */
typedef struct
{
    union
    {
        volatile mcc_channel_specific_transparent_t *transparent;
        volatile mcc_channel_specific_hdlc_t        *hdlc;
        volatile mcc_channel_specific_ss7_t         *ss7;
    }
    type;
    volatile mcc_channel_extra_param_t     *extra;
    volatile mcc_channel_bd_t              *rxbase;
    volatile mcc_channel_bd_t              *rx;
    volatile mcc_channel_bd_t              *txbase;
    volatile mcc_channel_bd_t              *tx;
    mcc_channel_stats_t                    *stats;
    mcc_channel_stats_t                    lstats;
    u32                                    valid;
    u32                                    mode;
    mcc_bd_proc_t                          onread;
    mcc_writen_proc_t                      onwrite;
    mcc_signal_proc_t                      onsignal;
}
mcc_channel_run_t;

/*
 * How to configure the MCCs.  The memory map is up to us.
 * Note: tablesize is the size of one table; however, the map
 * needs enough space for a total of five tables that size.
 */
typedef struct
{
    u32      dpbase;    /* To base of DPRAM.  Channel specific.  */
    u32      bdbase;    /* To Tx/Rx BD table area. Pointer type. */
    u32      intbase;   /* Interrupt table area.  Pointer type.  */
    u32      intsize;   /* Sizeof _1_ table.  There are 5 tables */
    u32      bufbase;   /* BD buffer area.  Pointer type.        */
    u16      sctpbase;  /* Superchannel area.  Array offset.     */
    u16      xtrabase;  /* Extra area.  Array offset.            */
    u32      bds_per;   /* BD count per channel.                 */
    u32      base_chan; /* Starting channel.  MCC1: 0, MCC2: 128 */
}
mcc_config_t;

/*
 * Interrupt statistics for the MCC
 */
typedef struct
{
    u32                                   txintcnt;
    u32                                   rxintcnt;
    u32                                   txunderflow;
    u32                                   rxbusy;
    u32                                   mfv;
    u32                                   gov;
    u32                                   gun;
    u32                                   tqov;
    u32                                   tint;
    u32                                   rqov0;
    u32                                   rint0;
    u32                                   rqov1;
    u32                                   rint1;
    u32                                   rqov2;
    u32                                   rint2;
    u32                                   rqov3;
    u32                                   rint3;
    u32                                   unknown;
}
mcc_stats_t;

/*
 * MCC management structure
 */
typedef struct
{
    volatile mcc_t                        *mcc_regs;
    volatile mcc_global_param_t           *mcc_params;
    volatile siramctl_t                   *siramctl;
    volatile u16                          *sitxram;
    volatile u16                          *sirxram;
    mcc_config_t                          config;
    u32                                   page;
    u32                                   code;
    mcc_stats_t                           stats;
    volatile mcc_interrupt_table_entry_t  *txints;
    volatile mcc_interrupt_table_entry_t  *txintbase;
    volatile mcc_interrupt_table_entry_t  *rxints[4];
    volatile mcc_interrupt_table_entry_t  *rxintbases[4];
    mcc_channel_run_t                     *channels;
}
mcc_run_t;

/*
 * Signatures
 */
/*
void mcc_enable_si(mcc_run_t *mcc);
void mcc_disable_si(mcc_run_t *mcc);
void mcc_enable_ints(mcc_run_t *mcc, u32 mch, u16 bits);
void mcc_disable_ints(mcc_run_t *mcc, u32 mch, u16 bits);
*/

void mcc_issue_command(mcc_run_t *mcc, u32 command, int channel);
void mcc_start_channel_rx(mcc_run_t *mcc, int channel);
void mcc_start_channel_tx(mcc_run_t *mcc, int channel);
void mcc_start_channel_trx(mcc_run_t *mcc, int channel);
void mcc_stop_channel_rx(mcc_run_t *mcc, int channel);
void mcc_stop_channel_tx(mcc_run_t *mcc, int channel);
//void mcc_reset_filter(mcc_run_t *mcc, int channel);
int  mcc_send_data(mcc_run_t *mcc, int channel, void *buf, u32 size);

#endif /* __CPM2_MCC_H__ */
#endif /* __KERNEL__ */

