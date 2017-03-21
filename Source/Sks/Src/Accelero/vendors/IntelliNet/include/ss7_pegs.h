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
 *
 *  ID: $Id: ss7_pegs.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:22:00  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.2  2005/05/06 05:56:20  adutta
 * LOG: MTP route pegs declaration
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:26  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.8  2005/03/21 13:53:22  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.6  2005/02/07 12:16:55  sbabu
 * LOG: MTP3 OAM Bug Fixes
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.5  2005/01/06 19:45:17  snagesh
 * LOG: Modified TCAP PEG #defines
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.4  2005/01/05 05:53:11  sbabu
 * LOG: TCAP Pegs #defines changed
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.3  2005/01/04 06:15:02  snagesh
 * LOG: PEG_MTP3_NUM_PEGS changed to 78
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.2  2004/12/31 06:34:52  sbabu
 * LOG: TCAP and MTP3 OAM Changes
 * LOG:
 * LOG: Revision 7.4.2.2.2.3.8.1  2004/12/29 13:14:33  csireesh
 * LOG: SCCP and ISUP OAM changes
 * LOG:
 * LOG: Revision 7.4.2.2.2.3  2004/08/11 08:25:03  mmanikandan
 * LOG: Compilation Error.
 * LOG:
 * LOG: Revision 7.4.2.2.2.2  2004/08/10 11:50:59  kannanp
 * LOG: Changes for MTP3 pegs & alarms - propagated from TCS.
 * LOG:
 * LOG: Revision 7.4.2.2.2.1  2004/06/22 11:49:34  csireesh
 * LOG: ALARMS and PEGS Propogation from TCS branch.
 * LOG:
 * LOG: Revision 7.4.2.2  2003/12/08 11:05:46  kannanp
 * LOG: Added seperate PEG_MTP3_NUM_PEGS for ANSI and CCITT.
 * LOG:
 * LOG: Revision 7.4.2.1  2003/11/28 08:07:10  kannanp
 * LOG: Peg Fix patch from Current.
 * LOG:
 * LOG: Revision 7.4  2003/02/13 10:18:53  ttipatre
 * LOG: New User Interface for Pegs
 * LOG:
 * LOG: Revision 7.2  2002/12/24 07:35:55  ttipatre
 * LOG: Link Level Pegs.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.8  2002/08/05 20:57:18  ssharma
 * LOG: Move pegs identifiers from vendors to IntelliSS7.
 * LOG:
 * LOG: Revision 1.7  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 1.6.2.1  2002/07/31 22:25:44  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 1.6  2002/06/13 20:31:14  ttipatre
 * LOG: Adding MTP3 Pegs
 * LOG:
 * LOG: Revision 1.5  2002/06/06 19:17:26  mmiers
 * LOG: Add link level pegs
 * LOG:
 * LOG: Revision 1.4  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 1.3  2002/03/07 17:42:30  mmiers
 * LOG: Most of ANSI SCCP merged.
 * LOG:
 * LOG: Revision 1.2  2002/03/01 23:12:06  mmiers
 * LOG: Start the DSM/pegs/alarms merge.  ANSI-TCAP done, 3 left.
 * LOG:
 *
 ****************************************************************************/

#if !defined(_SS7_PEGS_H_)
#define _SS7_PEGS_H_

#include <its_pegs.h>
#include <mtp3_pegs.h>

#define GLOBAL_PEGID_TO_TEXT(x)  \
        ((x==PEG_MTP3_MSG_PAUSE)     ? "PEG_MTP3_MSG_PAUSE"  :     \
        ((x==PEG_MTP3_MSG_RESUME)  ? "PEG_MTP3_MSG_RESUME" :    \
        ((x==PEG_MTP3_MSG_STATUS)    ? "PEG_MTP3_MSG_STATUS" :     \
        ((x==PEG_MTP3_INITIALIZE)           ? "PEG_MTP3_INITIALIZE" : \
        ((x==PEG_MTP3_TERMINATE)     ? "PEG_MTP3_TERMINATE"  :     \
        ((x==PEG_MTP3_MSG_RECEIVED_INERROR)     ? "PEG_MTP3_MSG_RECEIVED_INERROR"  :     \
        ((x==PEG_MTP3_CHANGEOVER)     ? "PEG_MTP3_CHANGEOVER"  :     \
        ((x==PEG_MTP3_CHANGEBACK)     ? "PEG_MTP3_CHANGEBACK"  :     \
        ((x==PEG_MTP3_SL_UNAVAILABLE)     ? "PEG_MTP3_SL_UNAVAILABLE"  :     \
        ((x==PEG_MTP3_LINK_INHIBIT)     ? "PEG_MTP3_LINK_INHIBIT"  :     \
        ((x==PEG_MTP3_LINK_UNINHIBIT)     ? "PEG_MTP3_LINK_UNINHIBIT"  :     \
        ((x==PEG_MTP3_LINK_FORCE_UNINHIBIT)     ? "PEG_MTP3_LINK_FORCE_UNINHIBIT"  :     \
        ((x==PEG_MTP3_CONGESTION)     ? "PEG_MTP3_CONGESTION"  :     \
        ((x==PEG_MTP3_SLS_UNAVAILABLE)     ? "PEG_MTP3_SLS_UNAVAILABLE"  :     \
        ((x==PEG_MTP3_TFC_RECEIVED)     ? "PEG_MTP3_TFC_RECEIVED"  :     \
        ((x==PEG_MTP3_TFA_RECEIVED)     ? "PEG_MTP3_TFA_RECEIVED"  :     \
        ((x==PEG_MTP3_ROUTESET_UNAVAILABLE)     ? "PEG_MTP3_ROUTESET_UNAVAILABLE"  :     \
        ((x==PEG_MTP3_ADJECENT_SP_UNACCESIBLE)     ? "PEG_MTP3_ADJECENT_SP_UNACCESIBLE"  :     \
        ((x==PEG_MTP3_USERPART_ENABLE)     ? "PEG_MTP3_USERPART_ENABLE"  :     \
        ((x==PEG_MTP3_USERPART_DISABLE)     ? "PEG_MTP3_USERPART_DISABLE"  :     \
        ((x==PEG_MTP3_T1_EXPIRED)     ? "PEG_MTP3_T1_EXPIRED"  :     \
        ((x==PEG_MTP3_T2_EXPIRED)     ? "PEG_MTP3_T2_EXPIRED"  :     \
        ((x==PEG_MTP3_T3_EXPIRED)     ? "PEG_MTP3_T3_EXPIRED"  :     \
        ((x==PEG_MTP3_T4_EXPIRED)     ? "PEG_MTP3_T4_EXPIRED"  :     \
        ((x==PEG_MTP3_T5_EXPIRED)     ? "PEG_MTP3_T5_EXPIRED"  :     \
        ((x==PEG_MTP3_T6_EXPIRED)     ? "PEG_MTP3_T6_EXPIRED"  :     \
        ((x==PEG_MTP3_T7_EXPIRED)     ? "PEG_MTP3_T7_EXPIRED"  :     \
        ((x==PEG_MTP3_T8_EXPIRED)     ? "PEG_MTP3_T8_EXPIRED"  :     \
        ((x==PEG_MTP3_T9_EXPIRED)     ? "PEG_MTP3_T9_EXPIRED"  :     \
        ((x==PEG_MTP3_T10_EXPIRED)     ? "PEG_MTP3_T10_EXPIRED"  :     \
        ((x==PEG_MTP3_T11_EXPIRED)     ? "PEG_MTP3_T11_EXPIRED"  :     \
        ((x==PEG_MTP3_T12_EXPIRED)     ? "PEG_MTP3_T12_EXPIRED"  :     \
        ((x==PEG_MTP3_T13_EXPIRED)     ? "PEG_MTP3_T13_EXPIRED"  :     \
        ((x==PEG_MTP3_T14_EXPIRED)     ? "PEG_MTP3_T14_EXPIRED"  :     \
        ((x==PEG_MTP3_T15_EXPIRED)     ? "PEG_MTP3_T15_EXPIRED"  :     \
        ((x==PEG_MTP3_T16_EXPIRED)     ? "PEG_MTP3_T16_EXPIRED"  :     \
        ((x==PEG_MTP3_T17_EXPIRED)     ? "PEG_MTP3_T17_EXPIRED"  :     \
        ((x==PEG_MTP3_T18_EXPIRED)     ? "PEG_MTP3_T18_EXPIRED"  :     \
        ((x==PEG_MTP3_T19_EXPIRED)     ? "PEG_MTP3_T19_EXPIRED"  :     \
        ((x==PEG_MTP3_T20_EXPIRED)     ? "PEG_MTP3_T20_EXPIRED"  :     \
        ((x==PEG_MTP3_T21_EXPIRED)     ? "PEG_MTP3_T21_EXPIRED"  :     \
        ((x==PEG_MTP3_T22_EXPIRED)     ? "PEG_MTP3_T22_EXPIRED"  :     \
        ((x==PEG_MTP3_T23_EXPIRED)     ? "PEG_MTP3_T23_EXPIRED"  :     \
        ((x==PEG_MTP3_T24_EXPIRED)     ? "PEG_MTP3_T24_EXPIRED"  :     \
        ((x==PEG_MTP3_T25_EXPIRED)     ? "PEG_MTP3_T25_EXPIRED"  :     \
        ((x==PEG_MTP3_T26_EXPIRED)     ? "PEG_MTP3_T26_EXPIRED"  :     \
        ((x==PEG_MTP3_T27_EXPIRED)     ? "PEG_MTP3_T27_EXPIRED"  :     \
        ((x==PEG_MTP3_T28_EXPIRED)     ? "PEG_MTP3_T28_EXPIRED"  :     \
        ((x==PEG_MTP3_T29_EXPIRED)     ? "PEG_MTP3_T29_EXPIRED"  :     \
        ((x==PEG_MTP3_T30_EXPIRED)     ? "PEG_MTP3_T30_EXPIRED"  :     \
        ((x==PEG_MTP3_T31_EXPIRED)     ? "PEG_MTP3_T31_EXPIRED"  :     \
        ((x==PEG_MTP3_T32_EXPIRED)     ? "PEG_MTP3_T32_EXPIRED"  :     \
        ((x==PEG_MTP3_T33_EXPIRED)     ? "PEG_MTP3_T33_EXPIRED"  :     \
        ((x==PEG_MTP3_T34_EXPIRED)     ? "PEG_MTP3_T34_EXPIRED"  :     \
        ((x==PEG_MTP3_LINK_INHIBIT_DNY)  ? "PEG_MTP3_LINK_INHIBIT_DNY"  : \
        ((x==PEG_MTP3_LINK_BLOCK)  ? "PEG_MTP3_LINK_BLOCK"  :            \
        ((x==PEG_MTP3_LINK_UNBLOCK)  ? "PEG_MTP3_LINK_UNBLOCK"  :     \
        ((x==PEG_MTP3_LINK_ACTIVATION)  ? "PEG_MTP3_LINK_ACTIVATION"  :     \
        ((x==PEG_MTP3_LINK_DEACTIVATION) ? "PEG_MTP3_LINK_DEACTIVATION" :   \
        ((x==PEG_MTP3_CONGESTION_DETECT) ? "PEG_MTP3_CONGESTION_DETECT" :   \
        ((x==PEG_MTP3_MSU_TX) ? "PEG_MTP3_MSU_TX" :   \
        ((x==PEG_MTP3_MSU_RX) ? "PEG_MTP3_MSU_RX" :   \
        ((x==PEG_MTP3_SLTM_TX) ? "PEG_MTP3_SLTM_TX" :   \
        ((x==PEG_MTP3_SLTM_RX) ? "PEG_MTP3_SLTM_RX" :   \
        ((x==PEG_MTP3_SLTA_TX) ? "PEG_MTP3_SLTA_TX" :   \
        ((x==PEG_MTP3_SLTA_RX) ? "PEG_MTP3_SLTA_RX" :   \
        ((x==PEG_MTP3_SLT_PASSED) ? "PEG_MTP3_SLT_PASSED" :   \
        ((x==PEG_MTP3_SLT_FAILED) ? "PEG_MTP3_SLT_FAILED" :   \
        ((x==PEG_MTP3_TFP_TX) ? "PEG_MTP3_TFP_TX" :   \
        ((x==PEG_MTP3_TFP_RX) ? "PEG_MTP3_TFP_RX" :   \
        ((x==PEG_MTP3_TFA_TX) ? "PEG_MTP3_TFA_TX" :   \
        ((x==PEG_MTP3_TFA_RX) ? "PEG_MTP3_TFA_RX" :   \
        ((x==PEG_MTP3_REMOTE_ROUTE_FAILURE) ? "PEG_MTP3_REMOTE_ROUTE_FAILURE": \
        ((x==PEG_MTP3_USERPART_ROUTE_FAILURE) ? "PEG_MTP3_USERPART_ROUTE_FAILURE" :   \
        ((x==PEG_MTP3_LINK_OUT_OF_SERVICE) ? "PEG_MTP3_LINK_OUT_OF_SERVICE" : \
        ((x==PEG_MTP3_RESTART) ? "PEG_MTP3_RESTART" :   \
        ((x==PEG_MTP3_EMER_CHANGEOVER) ? "PEG_MTP3_EMER_CHANGEOVER" :   \
         "UNKNOWN PEG ID")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
       
#define LINK_PEGID_TO_TEXT(x)  \
        ((x==PEG_MTP3_LINK_MSU_TX)     ? "PEG_MTP3_LINK_MSU_TX"  :     \
        ((x==PEG_MTP3_LINK_MSU_RX)  ? "PEG_MTP3_LINK_MSU_RX" :    \
        ((x==PEG_MTP3_LINK_OCTETS_TX)    ? "PEG_MTP3_LINK_OCTETS_TX" :     \
        ((x==PEG_MTP3_LINK_OCTETS_RX)           ? "PEG_MTP3_LINK_OCTETS_RX" : \
        ((x==PEG_MTP3_LINK_COO_TX )     ? "PEG_MTP3_LINK_COO_TX "  :     \
        ((x==PEG_MTP3_LINK_COO_RX )     ? "PEG_MTP3_LINK_COO_RX "  :     \
        ((x==PEG_MTP3_LINK_COA_TX )     ? "PEG_MTP3_LINK_COA_TX "  :     \
        ((x==PEG_MTP3_LINK_COA_RX)     ? "PEG_MTP3_LINK_COA_RX"  :     \
        ((x== PEG_MTP3_LINK_ECO_TX)     ? "PEG_MTP3_LINK_ECO_TX"  :     \
        ((x==PEG_MTP3_LINK_ECO_RX)     ? "PEG_MTP3_LINK_ECO_RX"  :     \
        ((x==PEG_MTP3_LINK_ECA_TX  )     ? "PEG_MTP3_LINK_ECA_TX  "  :     \
        ((x==PEG_MTP3_LINK_ECA_RX)     ? "PEG_MTP3_LINK_ECA_RX"  :     \
        ((x==PEG_MTP3_LINK_CBD_TX )     ? "PEG_MTP3_LINK_CBD_TX "  :     \
        ((x==PEG_MTP3_LINK_CBD_RX )     ? "PEG_MTP3_LINK_CBD_RX "  :     \
        ((x==PEG_MTP3_LINK_CBA_TX)     ? "PEG_MTP3_LINK_CBA_TX"  :     \
        ((x==PEG_MTP3_LINK_CBA_RX )     ? "PEG_MTP3_LINK_CBA_RX"  :     \
        ((x==PEG_MTP3_LINK_LIN_TX)     ? "PEG_MTP3_LINK_LIN_TX"  :     \
        ((x==PEG_MTP3_LINK_LIN_RX )     ? "PEG_MTP3_LINK_LIN_RX "  :     \
        ((x==PEG_MTP3_LINK_LIA_TX)     ? "PEG_MTP3_LINK_LIA_TX"  :     \
        ((x==PEG_MTP3_LINK_LIA_RX)     ? "PEG_MTP3_LINK_LIA_RX"  :     \
        ((x==PEG_MTP3_LINK_LUN_TX)     ? "PEG_MTP3_LINK_LUN_TX"  :     \
        ((x==PEG_MTP3_LINK_LUN_RX)     ? "PEG_MTP3_LINK_LUN_RX"  :     \
        ((x==PEG_MTP3_LINK_LUA_TX)     ? "PEG_MTP3_LINK_LUA_TX"  :     \
        ((x==PEG_MTP3_LINK_LUA_RX)     ? "PEG_MTP3_LINK_LUA_RX"  :     \
        ((x==PEG_MTP3_LINK_LID_TX)     ? "PEG_MTP3_LINK_LID_TX"  :     \
        ((x==PEG_MTP3_LINK_LID_RX)     ? "PEG_MTP3_LINK_LID_RX"  :     \
        ((x==PEG_MTP3_LINK_LFU_TX)     ? "PEG_MTP3_LINK_LFU_TX"  :     \
        ((x==PEG_MTP3_LINK_LFU_RX )     ? "PEG_MTP3_LINK_LFU_RX "  :     \
        ((x==PEG_MTP3_LINK_LLI_TX )     ? "PEG_MTP3_LINK_LLI_TX "  :     \
        ((x==PEG_MTP3_LINK_LLI_RX)     ? "PEG_MTP3_LINK_LLI_RX"  :     \
        ((x==PEG_MTP3_LINK_LRI_TX)     ? "PEG_MTP3_LINK_LRI_TX"  :     \
        ((x==PEG_MTP3_LINK_LRI_RX)     ? "PEG_MTP3_LINK_LRI_RX"  :     \
        ((x==PEG_MTP3_LINK_DLC_TX )     ? "PEG_MTP3_LINK_DLC_TX "  :     \
        ((x==PEG_MTP3_LINK_DLC_RX )     ? "PEG_MTP3_LINK_DLC_RX "  :     \
        ((x==PEG_MTP3_LINK_CSS_TX)     ? "PEG_MTP3_LINK_CSS_TX"  :     \
        ((x==PEG_MTP3_LINK_CSS_RX)     ? "PEG_MTP3_LINK_CSS_RX"  :     \
        ((x==PEG_MTP3_LINK_CNS_TX)     ? "PEG_MTP3_LINK_CNS_TX"  :     \
        ((x==PEG_MTP3_LINK_CNS_RX)     ? "PEG_MTP3_LINK_CNS_RX"  :     \
        ((x==PEG_MTP3_LINK_CNP_TX)     ? "PEG_MTP3_LINK_CNP_TX"  :     \
        ((x==PEG_MTP3_LINK_CNP_RX)     ? "PEG_MTP3_LINK_CNP_RX"  :     \
        ((x==PEG_MTP3_LINK_UPU_TX)     ? "PEG_MTP3_LINK_UPU_TX"  :     \
        ((x==PEG_MTP3_LINK_UPU_RX)     ? "PEG_MTP3_LINK_UPU_RX"  :     \
        ((x==PEG_MTP3_LINK_SLTM_TX)     ? "PEG_MTP3_LINK_SLTM_TX"  :     \
        ((x==PEG_MTP3_LINK_SLTM_RX)     ? "PEG_MTP3_LINK_SLTM_RX"  :     \
        ((x==PEG_MTP3_LINK_SLTA_TX)     ? "PEG_MTP3_LINK_SLTA_TX"  :     \
        ((x==PEG_MTP3_LINK_SLTA_RX)     ? "PEG_MTP3_LINK_SLTA_RX"  :     \
        ((x==PEG_LINK_OUT_OF_SERVICE)     ? "PEG_LINK_OUT_OF_SERVICE"  :     \
        ((x==PEG_LINK_IN_SERVICE)     ? "PEG_LINK_IN_SERVICE"  :     \
        ((x== PEG_LINK_NORMAL_CH_OVER)     ? "PEG_LINK_NORMAL_CH_OVER"  :     \
        ((x==PEG_LINK_EMERG_CH_OVER)     ? "PEG_LINK_EMERG_CH_OVER"  :     \
        ((x==PEG_LINK_CHANGE_BACK )     ? "PEG_LINK_CHANGE_BACK "  :     \
        ((x==PEG_LINK_INHIBIT_SUCCESS )     ? "PEG_LINK_INHIBIT_SUCCESS "  :     \
        ((x==PEG_LINK_INHIBIT_DENY)     ? "PEG_LINK_INHIBIT_DENY"  :     \
        ((x==PEG_LINK_INHIBIT_FAILURE)     ? "PEG_LINK_INHIBIT_FAILURE"  :     \
        ((x==PEG_LINK_UNINHIBIT_SUCCESS)     ? "PEG_LINK_UNINHIBIT_SUCCESS"  :     \
        ((x==PEG_LINK_UNINHIBIT_FAILS)     ? "PEG_LINK_UNINHIBIT_FAILS"  :     \
        ((x==PEG_LINK_FORCE_UNINHIBIT_SUCCESS )     ? "PEG_LINK_FORCE_UNINHIBIT_SUCCESS "  :     \
        ((x==PEG_LINK_FORCE_UNINHIBIT_FAILS)     ? "PEG_LINK_FORCE_UNINHIBIT_FAILS"  :     \
        ((x==PEG_LINK_BLOCK)     ? "PEG_LINK_BLOCK"  :     \
        ((x==PEG_LINK_UNBLOCK)     ? "PEG_LINK_UNBLOCK"  :     \
        ((x==PEG_LINK_ACTIVATION)  ? "PEG_LINK_ACTIVATION"  :     \
        ((x==PEG_LINK_DEACTIVATION) ? "PEG_LINK_DEACTIVATION" :   \
        ((x==PEG_LINK_CONGESTION_DETECT) ? "PEG_LINK_CONGESTION_DETECT" :   \
        ((x==PEG_LINK_MSU_TX) ? "PEG_LINK_MSU_TX" :   \
        ((x==PEG_LINK_MSU_RX) ? "PEG_LINK_MSU_RX" :   \
        ((x==PEG_LINK_SLTM_TX) ? "PEG_LINK_SLTM_TX" :   \
        ((x==PEG_LINK_SLTM_RX) ? "PEG_LINK_SLTM_RX" :   \
        ((x==PEG_LINK_SLTA_TX) ? "PEG_LINK_SLTA_TX" :   \
        ((x==PEG_LINK_SLTA_RX) ? "PEG_LINK_SLTA_RX" :   \
        ((x==PEG_LINK_SLT_PASSED) ? "PEG_LINK_SLT_PASSED" :   \
        ((x==PEG_MTP3_SLT_FAILED) ? "PEG_LINK_SLT_FAILED" :   \
        "UNKNOWN PEG ID")))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))

#define DPC_PEGID_TO_TEXT(x)  \
        ((x==PEG_MTP3_DPC_TFA_TX)     ? "PEG_MTP3_DPC_TFA_TX"  :     \
        ((x==PEG_MTP3_DPC_TFA_RX)  ? "PEG_MTP3_DPC_TFA_RX" :    \
        ((x==PEG_MTP3_DPC_TFP_TX)    ? "PEG_MTP3_DPC_TFP_TX" :     \
        ((x==PEG_MTP3_DPC_TFP_RX)           ? "PEG_MTP3_DPC_TFP_RX" : \
        ((x==PEG_MTP3_DPC_RST_TX)           ? "PEG_MTP3_DPC_RST_TX" : \
        ((x==PEG_MTP3_DPC_RST_RX)           ? "PEG_MTP3_DPC_RST_RX" : \
        ((x==PEG_MTP3_DPC_TFR_RX)           ? "PEG_MTP3_DPC_TFR_RX" : \
        ((x==PEG_MTP3_DPC_TFC_TX)           ? "PEG_MTP3_DPC_TFC_TX" : \
        ((x==PEG_MTP3_DPC_TFC_RX)           ? "PEG_MTP3_DPC_TFC_RX" : \
        ((x==PEG_MTP3_DPC_SIF_TX)           ? "PEG_MTP3_DPC_SIF_TX" : \
        "UNKNOWN PEG ID"))))))))))
         
/*
 * MTP3 pegs
 */

#define ALL_MTP3_PEGS                          99

#define PEG_MTP3_MSG_PAUSE                      0
#define PEG_MTP3_MSG_RESUME                     1
#define PEG_MTP3_MSG_STATUS                     2
#define PEG_MTP3_INITIALIZE                     3
#define PEG_MTP3_TERMINATE                      4
#define PEG_MTP3_MSG_RECEIVED_INERROR           5
#define PEG_MTP3_CHANGEOVER                     6
#define PEG_MTP3_CHANGEBACK                     7
#define PEG_MTP3_SL_UNAVAILABLE                 8
#define PEG_MTP3_LINK_INHIBIT                   9
#define PEG_MTP3_LINK_UNINHIBIT                 10
#define PEG_MTP3_LINK_FORCE_UNINHIBIT           11
#define PEG_MTP3_CONGESTION                     12
#define PEG_MTP3_SLS_UNAVAILABLE                13
#define PEG_MTP3_TFC_RECEIVED                   14
#define PEG_MTP3_TFA_RECEIVED                   15
#define PEG_MTP3_ROUTESET_UNAVAILABLE           16
#define PEG_MTP3_ADJECENT_SP_UNACCESIBLE        17
#define PEG_MTP3_USERPART_ENABLE                18
#define PEG_MTP3_USERPART_DISABLE               19
#define PEG_MTP3_T1_EXPIRED                     20
#define PEG_MTP3_T2_EXPIRED                     21
#define PEG_MTP3_T3_EXPIRED                     22
#define PEG_MTP3_T4_EXPIRED                     23
#define PEG_MTP3_T5_EXPIRED                     24
#define PEG_MTP3_T6_EXPIRED                     25
#define PEG_MTP3_T7_EXPIRED                     26
#define PEG_MTP3_T8_EXPIRED                     27
#define PEG_MTP3_T9_EXPIRED                     28
#define PEG_MTP3_T10_EXPIRED                    29
#define PEG_MTP3_T11_EXPIRED                    30 
#define PEG_MTP3_T12_EXPIRED                    31
#define PEG_MTP3_T13_EXPIRED                    32
#define PEG_MTP3_T14_EXPIRED                    33
#define PEG_MTP3_T15_EXPIRED                    34
#define PEG_MTP3_T16_EXPIRED                    35
#define PEG_MTP3_T17_EXPIRED                    36
#define PEG_MTP3_T18_EXPIRED                    37
#define PEG_MTP3_T19_EXPIRED                    38
#define PEG_MTP3_T20_EXPIRED                    39
#define PEG_MTP3_T21_EXPIRED                    40 
#define PEG_MTP3_T22_EXPIRED                    41
#define PEG_MTP3_T23_EXPIRED                    42
#define PEG_MTP3_T24_EXPIRED                    43
#define PEG_MTP3_T25_EXPIRED                    44
#define PEG_MTP3_T26_EXPIRED                    45
#define PEG_MTP3_T27_EXPIRED                    46
#define PEG_MTP3_T28_EXPIRED                    47
#define PEG_MTP3_T29_EXPIRED                    48
#define PEG_MTP3_T30_EXPIRED                    49
#define PEG_MTP3_T31_EXPIRED                    50
#define PEG_MTP3_T32_EXPIRED                    51
#define PEG_MTP3_T33_EXPIRED                    52
#define PEG_MTP3_T34_EXPIRED                    53
#define PEG_MTP3_LINK_INHIBIT_DNY               54
#define PEG_MTP3_LINK_BLOCK                     55
#define PEG_MTP3_LINK_UNBLOCK                   56
#define PEG_MTP3_LINK_ACTIVATION                57
#define PEG_MTP3_LINK_DEACTIVATION              58
#define PEG_MTP3_CONGESTION_DETECT              59
#define PEG_MTP3_MSU_TX                         60 
#define PEG_MTP3_MSU_RX                         61 
#define PEG_MTP3_SLTM_TX                        62 
#define PEG_MTP3_SLTM_RX                        63 
#define PEG_MTP3_SLTA_TX                        64 
#define PEG_MTP3_SLTA_RX                        65 
#define PEG_MTP3_SLT_PASSED                     66 
#define PEG_MTP3_SLT_FAILED                     67 
#define PEG_MTP3_TFP_TX                         68 
#define PEG_MTP3_TFP_RX                         69 
#define PEG_MTP3_TFA_TX                         70 
#define PEG_MTP3_TFA_RX                         71 
#define PEG_MTP3_REMOTE_ROUTE_FAILURE           72 
#define PEG_MTP3_USERPART_ROUTE_FAILURE         73 
#define PEG_MTP3_LINK_OUT_OF_SERVICE            74 
#define PEG_MTP3_LINK_IN_SERVICE                75 
#define PEG_MTP3_RESTART                        76 
#define PEG_MTP3_EMER_CHANGEOVER                77 

/* always keep this adjusted*/
#define PEG_MTP3_NUM_PEGS                       78 
#define PEG_MTP3_NUM_PEGS_ANSI                  78 
#define PEG_MTP3_NUM_PEGS_CCITT                 78

/* per link pegs */
#define PEG_MTP3_LINK_MSU_TX                    0
#define PEG_MTP3_LINK_MSU_RX                    1
#define PEG_MTP3_LINK_OCTETS_TX                 2
#define PEG_MTP3_LINK_OCTETS_RX                 3
#define PEG_MTP3_LINK_COO_TX                    4
#define PEG_MTP3_LINK_COO_RX                    5
#define PEG_MTP3_LINK_COA_TX                    6
#define PEG_MTP3_LINK_COA_RX                    7
#define PEG_MTP3_LINK_ECO_TX                    8
#define PEG_MTP3_LINK_ECO_RX                    9
#define PEG_MTP3_LINK_ECA_TX                    10
#define PEG_MTP3_LINK_ECA_RX                    11
#define PEG_MTP3_LINK_CBD_TX                    12
#define PEG_MTP3_LINK_CBD_RX                    13
#define PEG_MTP3_LINK_CBA_TX                    14
#define PEG_MTP3_LINK_CBA_RX                    15
#define PEG_MTP3_LINK_LIN_TX                    16
#define PEG_MTP3_LINK_LIN_RX                    17
#define PEG_MTP3_LINK_LIA_TX                    18
#define PEG_MTP3_LINK_LIA_RX                    19
#define PEG_MTP3_LINK_LUN_TX                    20
#define PEG_MTP3_LINK_LUN_RX                    21
#define PEG_MTP3_LINK_LUA_TX                    22
#define PEG_MTP3_LINK_LUA_RX                    23
#define PEG_MTP3_LINK_LID_TX                    24
#define PEG_MTP3_LINK_LID_RX                    25
#define PEG_MTP3_LINK_LFU_TX                    26
#define PEG_MTP3_LINK_LFU_RX                    27
#define PEG_MTP3_LINK_LLI_TX                    28
#define PEG_MTP3_LINK_LLI_RX                    29
#define PEG_MTP3_LINK_LRI_TX                    30
#define PEG_MTP3_LINK_LRI_RX                    31
#define PEG_MTP3_LINK_DLC_TX                    32
#define PEG_MTP3_LINK_DLC_RX                    33
#define PEG_MTP3_LINK_CSS_TX                    34
#define PEG_MTP3_LINK_CSS_RX                    35
#define PEG_MTP3_LINK_CNS_TX                    36
#define PEG_MTP3_LINK_CNS_RX                    37
#define PEG_MTP3_LINK_CNP_TX                    38
#define PEG_MTP3_LINK_CNP_RX                    39
#define PEG_MTP3_LINK_UPU_TX                    40
#define PEG_MTP3_LINK_UPU_RX                    41
#define PEG_MTP3_LINK_SLTM_TX                   42
#define PEG_MTP3_LINK_SLTM_RX                   43
#define PEG_MTP3_LINK_SLTA_TX                   44
#define PEG_MTP3_LINK_SLTA_RX                   45

#define PEG_LINK_OUT_OF_SERVICE                 46
#define PEG_LINK_IN_SERVICE                     47
#define PEG_LINK_NORMAL_CH_OVER                 48
#define PEG_LINK_EMERG_CH_OVER                  49
#define PEG_LINK_CHANGE_BACK                    50
#define PEG_LINK_INHIBIT_SUCCESS                51
#define PEG_LINK_INHIBIT_DENY                   52
#define PEG_LINK_INHIBIT_FAILURE                53
#define PEG_LINK_UNINHIBIT_SUCCESS              54
#define PEG_LINK_UNINHIBIT_FAILS                55
#define PEG_LINK_FORCE_UNINHIBIT_SUCCESS        56
#define PEG_LINK_FORCE_UNINHIBIT_FAILS          57
#define PEG_LINK_BLOCK                          58
#define PEG_LINK_UNBLOCK                        59
#define PEG_LINK_ACTIVATION                     60
#define PEG_LINK_DEACTIVATION                   61
#define PEG_LINK_CONGESTION_DETECT              62
#define PEG_LINK_MSU_TX                         63
#define PEG_LINK_MSU_RX                         64
#define PEG_LINK_SLTM_TX                        65
#define PEG_LINK_SLTM_RX                        66
#define PEG_LINK_SLTA_TX                        67
#define PEG_LINK_SLTA_RX                        68
#define PEG_LINK_SLT_PASSED                     69
#define PEG_LINK_SLT_FAILED                     70

/* Keep this adjusted in file its_link.h */
#define PEG_MTP3_NUM_LINK_PEGS                  46

/* per dpc pegs */

#define PEG_MTP3_DPC_TFA_TX                          0 
#define PEG_MTP3_DPC_TFA_RX                          1
#define PEG_MTP3_DPC_TFP_TX                          2
#define PEG_MTP3_DPC_TFP_RX                          3
#define PEG_MTP3_DPC_RST_TX                          4 
#define PEG_MTP3_DPC_RST_RX                          5 

#define PEG_MTP3_DPC_TFR_RX                          6

#define PEG_MTP3_DPC_TFC_TX                          7 
#define PEG_MTP3_DPC_TFC_RX                          8 

#define PEG_MTP3_DPC_SIF_TX                          9

#define PEG_MTP3_NUM_DPC_PEGS                        9 


/*
 * ISUP pegs
 */

#define ALL_ISUP_PEGS                          99

#define PEG_ISUP_STRT_LCL_UNAV_FAIL             0  /*10.1*/
#define PEG_ISUP_STRT_LCL_UNAV_MAINT            1  /*10.2*/
#define PEG_ISUP_AVAILABLE                      2  /*10.3*/
#define PEG_ISUP_TOT_DUR_UNAVAIL                3  /*10.4*/
#define PEG_ISUP_STRT_LCL_CONGES                4  /*10.5*/
#define PEG_ISUP_STOP_LCL_CONGES                5  /*10.6*/
#define PEG_ISUP_DUR_LCL_CONGES                 6  /*10.7*/
#define PEG_ISUP_TOT_MSGS_SENT                  7  /*11.1*/
#define PEG_ISUP_TOT_MSGS_RCVD                  8  /*11.2*/
/* always keep this adjusted*/
#define PEG_ISUP_NUM_PEGS                       9

/* 
 * ISUP Destination and CIC specific pegs are defined in 
 * $ITS_ROOT/ISUP/include/isup_variants.h 
 */


/*
 * SCCP pegs
 */

#define ALL_SCCP_PEGS                          99

#define PEG_SCCP_USER_MSG_SENT                  0
#define PEG_SCCP_REMOTE_MSG_RECEIVED            1
#define PEG_SCCP_ROUTING_FAILURE                2  /*7.1-7.7,7.9*/
#define PEG_SCCP_REMOTE_GTT_REQUEST             3
#define PEG_SCCP_REMOTE_GTT_SUCCESS             4
#define PEG_SCCP_REMOTE_GTT_FAILURE             5

#define PEG_SCCP_REMOTE_MSG_DECODE_ERR          6
#define PEG_SCCP_USER_MSG_ENCODE_ERR            7

#define PEG_SCCP_REMOTE_REASSEMBLE_ERR          8  /*7.10-7.12,7.21*/
#define PEG_SCCP_HOP_COUNTER_VIOLATION_ERR      9  /*7.13 */
#define PEG_SCCP_USER_SEGMENTATION_ERR          10 /*7.14,7.19-7.20*/
#define PEG_SCCP_TIMER_TIAR_EXPIRY              11 /*7.16*/
#define PEG_SCCP_USER_INITIATED_RLS             12 /*7.18*/
#define PEG_SCCP_USER_INITITATED_RESET          13 /*7.17*/
#define PEG_SCCP_REMOTE_UDT_RCVD                14 /* 9 bis 3*/
#define PEG_SCCP_REMOTE_XUDT_RCVD               15 /* 9 bis 15 */
#define PEG_SCCP_REMOTE_UDTS_RCVD               16 /* 9.2*/
#define PEG_SCCP_REMOTE_XUDTS_RCVD              17 /* 9 bis 16 */
#define PEG_SCCP_REMOTE_LUDT_RCVD               18 /*9 bis 19*/
#define PEG_SCCP_REMOTE_LUDTS_RCVD              19 /*9 bis 20*/
#define PEG_SCCP_USER_UDT_SENT                  20 /*9 bis 1*/
#define PEG_SCCP_USER_XUDT_SENT                 21 /*9 bis 13*/
#define PEG_SCCP_USER_UDTS_SENT                 22 /*9.1*/
#define PEG_SCCP_USER_XUDTS_SENT                23 /*9 bis 14*/
#define PEG_SCCP_USER_LUDT_SENT                 24 /*9 bis 17*/
#define PEG_SCCP_USER_LUDTS_SENT                25 /*9 bis 18*/
#define PEG_SCCP_USER_CR_SENT                   26 /* 9 bis 5*/
#define PEG_SCCP_CREF_TO_REMOTE_SENT            27 /* 9 bis 6*/
#define PEG_SCCP_RSR_TO_REMOTE_SENT             28 /*7.17*/
#define PEG_SCCP_ERR_TO_REMOTE_SENT             29 /*9 bis 11*/
#define PEG_SCCP_REMOTE_CR_RCVD                 30 /*9 bis 7*/
#define PEG_SCCP_REMOTE_CREF_RCVD               31 /* 9 bis 8*/
#define PEG_SCCP_REMOTE_RSR_RCVD                32 /* 9 bis 10*/
#define PEG_SCCP_REMOTE_ERR_RCVD                33 /* 9 bis 12*/
#define PEG_SCCP_REMOTE_MSG_FOR_LOCAL_SS_RCVD   34 /*9.4*/
#define PEG_SCCP_USER_DT1_SENT                  35 /* 9.10 */
#define PEG_SCCP_REMOTE_DT1_RCVD                36 /* 9.9 */
#define PEG_SCCP_USER_DT2_SENT                  37 /* 9.12*/
#define PEG_SCCP_REMOTE_DT2_RCVD                38 /* 9.11 */
#define PEG_SCCP_USER_ED_SENT                   39 /* 9.13*/
#define PEG_SCCP_REMOTE_ED_RCVD                 40 /*9.14*/
#define PEG_SCCP_REMOTE_SSP_RCVD                41 /*8.11*/
#define PEG_SCCP_REMOTE_SSA_RCVD                42 /*8.12*/
#define PEG_SCCP_REMOTE_SSC_RCVD                43 /*8.8*/
#define PEG_SCCP_LOCAL_SS_PROHIBITED            44 /*8.9*/
#define PEG_SCCP_LOCAL_SS_ALLOWED               45 /*8.12*/
#define PEG_SCCP_LOCAL_SS_CONGESTED             46 /*8.8*/

/* always keep this adjusted*/
 #define PEG_SCCP_NUM_PEGS                      47


/********************************************
 *
 *          TCAP PEGS
 *
 *******************************************/

#define ALL_TCAP_PEGS                          	  99

#define PEG_TCAP_APP_MSG_SENT                     0
#define PEG_TCAP_APP_MSG_DISCARDED                1
#define PEG_TCAP_APP_CMP_SENT                     2
#define PEG_TCAP_APP_CMP_DISCARDED                3
#define PEG_TCAP_APP_DLG_SENT                     4
#define PEG_TCAP_REMOTE_DLG_RCVD                  5
#define PEG_TCAP_REMOTE_CMP_RCVD                  6
#define PEG_TCAP_REMOTE_CMP_DISCARDED             7
#define PEG_TCAP_REMOTE_MSG_RCVD                  8
#define PEG_TCAP_REMOTE_UNKNOWN_MSG_RCVD          9
#define PEG_TCAP_REMOTE_MSG_DISCARDED            10
#define PEG_TCAP_ACTIVE_DIALOGUE                 11
#define PEG_TCAP_ACTIVE_TRANSACTIONS             12
#define PEG_TCAP_APP_PREARRANGED_END_SENT        13
#define PEG_TCAP_INVALID_SCCP_RCVD               14
#define PEG_TCAP_REMOTE_SCCP_CLASS_0_RCVD        15
#define PEG_TCAP_REMOTE_SCCP_CLASS_1_RCVD        16
#define PEG_TCAP_REMOTE_UNI_RCVD                 17
#define PEG_TCAP_APP_SCCP_CLASS_0_SENT           18
#define PEG_TCAP_APP_SCCP_CLASS_1_SENT           19
#define PEG_TCAP_APP_UNI_SENT                    20
#define PEG_TCAP_APP_ABORT_SENT                  21
#define PEG_TCAP_REMOTE_ABORT_RCVD               22
#define PEG_TCAP_APP_REJECT_SENT                 23
#define PEG_TCAP_REMOTE_REJECT_RCVD              24
#define PEG_TCAP_LOCAL_CANCEL                    25
#define PEG_TCAP_DLG_SEND_REMOTE_FAIL            26
#define PEG_TCAP_DLG_SEND_APP_FAIL               27
#define PEG_TCAP_APP_INVOKE_SENT                 28
#define PEG_TCAP_APP_RESULT_SENT                 29
#define PEG_TCAP_APP_ERROR_SENT                  30
#define PEG_TCAP_REMOTE_INVOKE_RCVD              31
#define PEG_TCAP_REMOTE_RESULT_RCVD              32
#define PEG_TCAP_REMOTE_ERROR_RCVD               33

/* ITU Specific ones */
#define PEG_TCAP_APP_OP_CLASS_1_SENT             34
#define PEG_TCAP_APP_OP_CLASS_2_SENT             35
#define PEG_TCAP_APP_OP_CLASS_3_SENT             36
#define PEG_TCAP_APP_OP_CLASS_4_SENT             37
#define PEG_TCAP_APP_BEGIN_SENT                  38
#define PEG_TCAP_REMOTE_BEGIN_RCVD               39
#define PEG_TCAP_APP_CONT_SENT                   40
#define PEG_TCAP_APP_END_SENT                    41
#define PEG_TCAP_REMOTE_END_RCVD                 42
#define PEG_TCAP_REMOTE_CONT_RCVD                43

/*ANSI specific */
#define PEG_TCAP_APP_QWOP_SENT                   44
#define PEG_TCAP_REMOTE_QWOP_RCVD                45
#define PEG_TCAP_APP_QWIP_SENT                   46
#define PEG_TCAP_REMOTE_QWIP_RCVD                47
#define PEG_TCAP_APP_RESP_SENT                   48
#define PEG_TCAP_REMOTE_RESP_RCVD                49
#define PEG_TCAP_APP_CWOP_SENT                   50
#define PEG_TCAP_REMOTE_CWOP_RCVD                51
#define PEG_TCAP_APP_CWIP_SENT                   52
#define PEG_TCAP_REMOTE_CWIP_RCVD                53

/* always keep this adjusted*/
#define PEG_TCAP_NUM_PEGS                        54

#define PEG_TCAP_NUM_GEN_PEGS                    34

#define PEG_TCAP_ITU_PEGS_START                  34
#define PEG_TCAP_ITU_PEGS_END                    43

#define PEG_TCAP_ANSI_PEGS_START                 44
#define PEG_TCAP_ANSI_PEGS_END                   53

/*
 * peg managers
 */
extern PEG_Manager* ANSI_MTP3_Pegs;
extern PEG_Manager* CCITT_MTP3_Pegs;
extern PEG_Manager* ANSI_ISUP_Pegs;
extern PEG_Manager* CCITT_ISUP_Pegs;
extern PEG_Manager* ANSI_SCCP_Pegs;
extern PEG_Manager* CCITT_SCCP_Pegs;
extern PEG_Manager* ANSI_TCAP_Pegs;
extern PEG_Manager* CCITT_TCAP_Pegs;

#endif /* !defined(SS7_PEGS_H) */
