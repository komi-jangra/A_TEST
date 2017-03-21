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
 *  ID: $Id: cpm2_si.h,v 1.1.1.1 2007-10-08 11:12:18 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:53  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:26  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:11  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/09/14 18:23:52  lbana
 * LOG: define mpc8560 specifics here.
 * LOG:
 ***************************************************************************/
/*
 * CPM2 SIRAM Control definitions and macros
 * Copyright (c) 2005 Mitch Miers (mmiers@cfl.rr.com)
 *
 * What the other headers don't tell you about this.  Really only useful
 * if you have an MCC.
 */
#ifdef __KERNEL__
#ifndef __CPM2_SI_H__
#define __CPM2_SI_H__

/*
 * SIx RAM
 * RESET: not listed
 * R/W  : both
 */

/*
 * SIxRAM: MCC enable/disable
 */
#define SIxRAM_MCCT_SHIFT 15
#define SIxRAM_MCC_DISABLE (0U<<SIxRAM_MCCT_SHIFT)
#define SIxRAM_MCC_ENABLE  (1U<<SIxRAM_MCCT_SHIFT)

/*
 * SIxRAM: Switch Tx and Rx
 * Mode  : Not MCC
 */
#define SIxRAM_SWTR_SHIFT 14
#define SIxRAM_SWTR_NORMAL  (0U<<SIxRAM_SWTR_SHIFT)
#define SIxRAM_SWTR_INVERT  (1U<<SIxRAM_SWTR_SHIFT)

/*
 * SIxRAM: Strobe Select
 * Mode  : Not MCC
 */
#define SIxRAM_SSEL1_SHIFT 13
#define SIxRAM_SSEL2_SHIFT 12
#define SIxRAM_SSEL3_SHIFT 11
#define SIxRAM_SSEL4_SHIFT 10
#define SIxRAM_SSEL1_OFF    (0U<<SIxRAM_SSEL1_SHIFT)
#define SIxRAM_SSEL1_ON     (1U<<SIxRAM_SSEL1_SHIFT)
#define SIxRAM_SSEL2_OFF    (0U<<SIxRAM_SSEL2_SHIFT)
#define SIxRAM_SSEL2_ON     (1U<<SIxRAM_SSEL2_SHIFT)
#define SIxRAM_SSEL3_OFF    (0U<<SIxRAM_SSEL3_SHIFT)
#define SIxRAM_SSEL3_ON     (1U<<SIxRAM_SSEL3_SHIFT)
#define SIxRAM_SSEL4_OFF    (0U<<SIxRAM_SSEL4_SHIFT)
#define SIxRAM_SSEL4_ON     (1U<<SIxRAM_SSEL4_SHIFT)

/*
 * SIxRAM: Channel Select
 * Mode  : Not MCC
 */
#define SIxRAM_CSEL_SHIFT 5
#define SIxRAM_CSEL_UNSUP1  (0U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_SCC1    (1U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_SCC2    (2U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_SCC3    (3U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_SCC4    (4U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD1   (5U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD2   (6U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_UNSUP2  (7U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_FCC1    (8U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_FCC2    (9U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_FCC3    (10U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD3   (11U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD4   (12U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD5   (13U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD6   (14U<<SIxRAM_CSEL_SHIFT)
#define SIxRAM_CSEL_RSVD7   (15U<<SIxRAM_CSEL_SHIFT)

/*
 * SIxRAM: Loop/Echo
 * Mode  : MCC
 */
#define SIxRAM_LE_SHIFT 14
#define SIxRAM_LE_NORMAL    (0U<<SIxRAM_LE_SHIFT)
#define SIxRAM_LE_LOOP      (1U<<SIxRAM_LE_SHIFT)

/*
 * SIxRAM: Super channel
 * Mode  : MCC
 */
#define SIxRAM_SUP_SHIFT 13
#define SIxRAM_SUP_NOT_SUPER (0U<<SIxRAM_SUP_SHIFT)
#define SIxRAM_SUP_IS_SUPER  (0U<<SIxRAM_SUP_SHIFT)

/*
 * SIxRAM: MCSEL
 * Mode  : MCC
 */
#define SIxRAM_MCSEL_SHIFT 5
#define SIxRAM_MCSEL_CHAN(x) ((x)<<SIxRAM_MCSEL_SHIFT)

/*
 * SIxRAM: Count
 */
#define SIxRAM_CNT_SHIFT 2
#define SIxRAM_CNT_1_UNIT   (0U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_2_UNIT   (1U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_3_UNIT   (2U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_4_UNIT   (3U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_5_UNIT   (4U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_6_UNIT   (5U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_7_UNIT   (6U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_8_UNIT   (7U<<SIxRAM_CNT_SHIFT)

#define SIxRAM_CNT_1ST      (0U<<SIxRAM_CNT_SHIFT)
#define SIxRAM_CNT_NOT_1ST  (7U<<SIxRAM_CNT_SHIFT)

/*
 * SIxRAM: Byte Resolution
 */
#define SIxRAM_BYT_SHIFT 1
#define SIxRAM_BYT_BITS     (0U<<SIxRAM_BYT_SHIFT)
#define SIxRAM_BYT_BYTES    (1U<<SIxRAM_BYT_SHIFT)

/*
 * SIxRAM: Last
 */
#define SIxRAM_LST_NOT_LAST (0U)
#define SIxRAM_LST_LAST     (1U)

/*
 * SIGMR: Global Mode Register, all bits
 * RESET: 0
 * R/W  : both
 */
#define SIGMR_STZD  (1U<<7) /* clear: normal                             */
#define SIGMR_STZC  (1U<<6) /* set  : L1TXDd=0 until serial clocks are   */
#define SIGMR_STZB  (1U<<5) /*        available, which is useful for GCI */
#define SIGMR_STZA  (1U<<4) /*        activation                         */
#define SIGMR_END   (1U<<3) /* clear: TDM is disable                     */
#define SIGMR_ENC   (1U<<2) /* set  : TDM is enabled.  Activation is the */
#define SIGMR_ENB   (1U<<1) /*        last thing to do during init.      */
#define SIGMR_ENA   (1U)

/*
 * SIxMR: Mode Registers (A,B,C,D) 16 bits
 * RESET: 0
 * R/W  : both
 */
/*
 * SIxMR: Starting bank address (SAD)
 */
#define SIxMR_SAD_SHIFT 12
#define SIxMR_SAD_1BF32 (0U<<SIxMR_SAD_SHIFT) /* First bank, first 32   */
#define SIxMR_SAD_1BS32 (1U<<SIxMR_SAD_SHIFT) /* First bank, second 32  */
#define SIxMR_SAD_2BF32 (2U<<SIxMR_SAD_SHIFT) /* Second bank, first 32  */
#define SIxMR_SAD_2BS32 (3U<<SIxMR_SAD_SHIFT) /* Second bank, second 32 */
#define SIxMR_SAD_3BF32 (4U<<SIxMR_SAD_SHIFT) /* Third bank, first 32   */
#define SIxMR_SAD_3BS32 (5U<<SIxMR_SAD_SHIFT) /* Third bank, second 32  */
#define SIxMR_SAD_4BF32 (6U<<SIxMR_SAD_SHIFT) /* Forth bank, first 32   */
#define SIxMR_SAD_4BS32 (7U<<SIxMR_SAD_SHIFT) /* Forth bank, second 32  */

/*
 * SIxMR: SI Diagnostic Mode
 */
#define SIxMR_SDM_SHIFT 10
#define SIxMR_SDM_NORMAL     (0U<<SIxMR_SDM_SHIFT) /* normal mode       */
#define SIxMR_SDM_AUTO_ECHO  (1U<<SIxMR_SDM_SHIFT) /* auto echo         */
#define SIxMR_SDM_INT_LOOP   (2U<<SIxMR_SDM_SHIFT) /* internal loopback */
#define SIxMR_SDM_LOOP_CONT  (3U<<SIxMR_SDM_SHIFT) /* loopback control  */

/*
 * SIxMR: Receive Frame Sync Delay
 */
#define SIxMR_RFSD_SHIFT 8
#define SIxMR_RFSD_NO_DELAY  (0U<<SIxMR_RFSD_SHIFT) /* 0 bit delay      */
#define SIxMR_RFSD_1_BIT     (1U<<SIxMR_RFSD_SHIFT) /* 1 bit delay      */
#define SIxMR_RFSD_2_BIT     (1U<<SIxMR_RFSD_SHIFT) /* 2 bit delay      */
#define SIxMR_RFSD_3_BIT     (1U<<SIxMR_RFSD_SHIFT) /* 3 bit delay      */

/*
 * SIxMR: Double Speed Clock
 */
#define SIxMR_DSC_SHIFT 7
#define SIxMR_DSC_EQUAL      (0U<<SIxMR_DSC_SHIFT)  /* Normal speed */
#define SIxMR_DSC_DOUBLE     (1U<<SIxMR_DSC_SHIFT)  /* Double speed */

/*
 * SIxMR: Common Receive and Transmit
 */
#define SIxMR_CRT_SHIFT 6
#define SIxMR_CRT_SEPARATE   (0U<<SIxMR_CRT_SHIFT)  /* Separate pins */
#define SIxMR_CRT_COMMON     (1U<<SIxMR_CRT_SHIFT)  /* Common pins   */

/*
 * SIxMR: Sync Level
 */
#define SIxMR_SL_SHIFT 5
#define SIxMR_SL_ON_ONE      (0U<<SIxMR_SL_SHIFT)   /* Sync on one */
#define SIxMR_SL_ON_ZERO     (1U<<SIxMR_SL_SHIFT)   /* Sync on one */

/*
 * SIxMR: Clock Edge
 */
#define SIxMR_CE_SHIFT 4
#define SIxMR_CE_DSC0_RISE_FALL (0U<<SIxMR_CE_SHIFT) /* Rising when DSC = 0  */
#define SIxMR_CE_DSC0_FALL_RISE (1U<<SIxMR_CE_SHIFT) /* Falling when DSC = 0 */
#define SIxMR_CE_DSC1_FALL_RISE (0U<<SIxMR_CE_SHIFT) /* Falling when DSC = 1 */
#define SIxMR_CE_DSC1_RISE_FALL (1U<<SIxMR_CE_SHIFT) /* Rising when DSC = 1  */

/*
 * SIxMR: Frame sync Edge
 */
#define SIxMR_FE_SHIFT 3
#define SIxMR_FE_FALL        (0U<<SIxMR_FE_SHIFT)    /* on falling edge */
#define SIxMR_FE_RISE        (1U<<SIxMR_FE_SHIFT)    /* on rising edge  */

/*
 * SIxMR: Grant Mode
 */
#define SIxMR_GM_SHIFT 2
#define SIxMR_GM_GCI_SCIT (0U<<SIxMR_GM_SHIFT)       /* GCI/SCIT mode */
#define SIxMR_GM_IDL      (1U<<SIxMR_GM_SHIFT)       /* IDL mode      */

/*
 * SIxMR: Transmit Frame Sync Delay
 */
#define SIxMR_TFSD_SHIFT 0
#define SIxMR_TFSD_NO_DELAY     (0U<<SIxMR_TFSD_SHIFT) /* 0 bit delay */
#define SIxMR_TFSD_1_BIT        (1U<<SIxMR_TFSD_SHIFT) /* 1 bit delay */
#define SIxMR_TFSD_2_BIT        (2U<<SIxMR_TFSD_SHIFT) /* 2 bit delay */
#define SIxMR_TFSD_3_BIT        (3U<<SIxMR_TFSD_SHIFT) /* 3 bit delay */

/*
 * SIxRSR: RAM Shadow Address Register (1,2), 16 bits
 * RESET : 0
 * R/W   : both
 */
#define SIxRSR_SSADA_SHIFT 12
#define SIxRSR_SSADB_SHIFT 8
#define SIxRSR_SSADC_SHIFT 4
#define SIxRSR_SSADD_SHIFT 0
#define SIxRSR_SSAD_1BF32  0U
#define SIxRSR_SSAD_1BS32  1U
#define SIxRSR_SSAD_2BF32  2U
#define SIxRSR_SSAD_2BS32  3U
#define SIxRSR_SSAD_3BF32  4U
#define SIxRSR_SSAD_3BS32  5U
#define SIxRSR_SSAD_4BF32  6U
#define SIxRSR_SSAD_4BS32  7U

#define SIxRSR_SSADA_1BF32 (SIxRSR_SSAD_1BF32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_1BS32 (SIxRSR_SSAD_1BS32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_2BF32 (SIxRSR_SSAD_2BF32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_2BS32 (SIxRSR_SSAD_2BS32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_3BF32 (SIxRSR_SSAD_3BF32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_3BS32 (SIxRSR_SSAD_3BS32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_4BF32 (SIxRSR_SSAD_4BF32<<SIxRSR_SSADA_SHIFT)
#define SIxRSR_SSADA_4BS32 (SIxRSR_SSAD_4BS32<<SIxRSR_SSADA_SHIFT)

#define SIxRSR_SSADB_1BF32 (SIxRSR_SSAD_1BF32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_1BS32 (SIxRSR_SSAD_1BS32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_2BF32 (SIxRSR_SSAD_2BF32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_2BS32 (SIxRSR_SSAD_2BS32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_3BF32 (SIxRSR_SSAD_3BF32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_3BS32 (SIxRSR_SSAD_3BS32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_4BF32 (SIxRSR_SSAD_4BF32<<SIxRSR_SSADB_SHIFT)
#define SIxRSR_SSADB_4BS32 (SIxRSR_SSAD_4BS32<<SIxRSR_SSADB_SHIFT)

#define SIxRSR_SSADC_1BF32 (SIxRSR_SSAD_1BF32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_1BS32 (SIxRSR_SSAD_1BS32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_2BF32 (SIxRSR_SSAD_2BF32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_2BS32 (SIxRSR_SSAD_2BS32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_3BF32 (SIxRSR_SSAD_3BF32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_3BS32 (SIxRSR_SSAD_3BS32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_4BF32 (SIxRSR_SSAD_4BF32<<SIxRSR_SSADC_SHIFT)
#define SIxRSR_SSADC_4BS32 (SIxRSR_SSAD_4BS32<<SIxRSR_SSADC_SHIFT)

#define SIxRSR_SSADD_1BF32 (SIxRSR_SSAD_1BF32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_1BS32 (SIxRSR_SSAD_1BS32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_2BF32 (SIxRSR_SSAD_2BF32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_2BS32 (SIxRSR_SSAD_2BS32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_3BF32 (SIxRSR_SSAD_3BF32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_3BS32 (SIxRSR_SSAD_3BS32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_4BF32 (SIxRSR_SSAD_4BF32<<SIxRSR_SSADD_SHIFT)
#define SIxRSR_SSADD_4BS32 (SIxRSR_SSAD_4BS32<<SIxRSR_SSADD_SHIFT)

/*
 * SIxCMDR: Command Register (1,2), 8 bits
 * RESET  : 0
 * R/W    : both
 */
#define SIxCMDR_CSRRA  (1U<<7)  /* clear: shadow RAM is not valid */
#define SIxCMDR_CSRRB  (1U<<5)  /* set  : shadow RAM is valid     */
#define SIxCMDR_CSRRC  (1U<<3)  /*        Set by user, cleared by */
#define SIxCMDR_CSRRD  (1U<<1)  /*        SI.  Cleared on switch  */
#define SIxCMDR_CSRTA  (1U<<6)  /* clear: shadow RAM is not valid */
#define SIxCMDR_CSRTB  (1U<<4)  /* set  : shadow RAM is valid     */
#define SIxCMDR_CSRTC  (1U<<2)  /*        Set by user, cleared by */
#define SIxCMDR_CSRTD  (1U)     /*        SI.  Cleared on switch  */

/*
 * SIxSTR: Status Register (1,2), 8 bits
 * RESET : 0
 * R/W   : both
 */
#define SIxSTR_CRORA   (1U<<7)  /* clear: current route RAM is in */
#define SIxSTR_CRORB   (1U<<5)  /*        lower area              */
#define SIxSTR_CRORC   (1U<<3)  /* set  : current route RAM is in */
#define SIxSTR_CRORD   (1U<<1)  /*        upper area              */
#define SIxSTR_CROTA   (1U<<6)  /* clear: current route RAM is in */
#define SIxSTR_CROTB   (1U<<4)  /*        lower area              */
#define SIxSTR_CROTC   (1U<<2)  /* set  : current route RAM is in */
#define SIxSTR_CROTD   (1U)     /*        upper area              */

#endif /* CPM2_SI_H */
#endif /* __KERNEL__ */

