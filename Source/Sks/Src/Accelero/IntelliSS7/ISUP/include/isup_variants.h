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
 *  ID: $Id: isup_variants.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:43  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:05  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.2  2005/04/06 09:30:23  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.12  2005/03/21 13:49:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.16.2.3.2.1.10.2  2005/02/25 06:26:42  ssingh
 * LOG: added/updated destination specific pegs (Ramesh KV)
 * LOG:
 * LOG: Revision 7.16.2.3.2.1.10.1  2004/12/16 03:35:28  randresol
 * LOG: Merge JAPAN variant implementation from TTC branch
 * LOG:
 * LOG: Revision 7.16.2.3.2.1.6.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.16.2.3.2.1  2004/01/05 09:43:43  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG: CVg: Committing in .
 * LOG:
 * LOG: Revision 7.16.2.2.2.2  2003/11/24 06:24:37  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.16.2.2.2.1  2003/10/27 08:57:40  akumar
 * LOG: Introduced msg based PEGs.
 * LOG:
 * LOG: Revision 7.16.2.2  2003/05/07 09:08:45  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.9  2003/05/02 13:54:34  ssingh
 * LOG: ANSI changes propped to ITU. (ISUP_CIC_INFO)
 * LOG:
 * LOG: Revision 8.8  2003/04/25 13:24:47  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.7  2003/04/22 08:26:16  akumar
 * LOG: Front port 6.3 to Current Branch (Mainly MML)
 * LOG:
 * LOG: Revision 8.6  2003/04/16 05:34:53  akumar
 * LOG: Changes related to congestion.
 * LOG:
 * LOG: Revision 8.5  2003/04/05 06:12:40  ssingh
 * LOG: Build Error: segmentation_supported in INFO/STAT for PRC too added.
 * LOG:
 * LOG: Revision 8.4  2003/04/03 14:21:00  sjaddu
 * LOG: DSM reorganisation.
 * LOG:
 * LOG: Revision 8.3  2003/03/26 10:21:20  ssingh
 * LOG: Changes done in files:
 * LOG: isup_cmn.h      : Indications added for COT reset/release.
 * LOG: isup_sn.h       : UnReserveCIC short name added
 * LOG: ansi/isup.h     : UnReserveCIC declared.
 * LOG: itu/isup.       : UnReserveCIC declared.
 * LOG: isup_variants.h : CIC_INFO is modified for ANSI.
 * LOG:
 * LOG: Revision 8.2  2003/03/15 12:32:09  ssingh
 * LOG: To support CRM/CRA ANSI messaging, states and indications added.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:24  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.16  2003/02/05 00:50:23  sjaddu
 * LOG: Cic reserve changes.
 * LOG:
 * LOG: Revision 7.15  2003/01/31 12:59:11  ssingh
 * LOG: New macros are added for getting Message proc and Timer proc key.
 * LOG: Macro is added for accessing event type from event received to App.
 * LOG:
 * LOG: Revision 7.14  2003/01/29 19:01:56  sjaddu
 * LOG: Added one more state for CRI state.
 * LOG:
 * LOG: Revision 7.13  2003/01/22 15:16:15  vnitin
 * LOG: Tandem Port Ansi ISUP
 * LOG:
 * LOG: Revision 7.12  2003/01/22 09:45:15  akumar
 * LOG: Modified cic structure to accomodate ITU variant for COT handling
 * LOG:
 * LOG: Revision 7.11  2003/01/21 15:37:27  vnitin
 * LOG: Tandem port partial changes
 * LOG:
 * LOG: Revision 7.10  2003/01/17 15:16:45  sjaddu
 * LOG: vcic changes ITS_USHORT to ITS_CTXT.
 * LOG:
 * LOG: Revision 7.9  2003/01/14 00:26:18  sjaddu
 * LOG: Added Cic rule in the cic record.
 * LOG:
 * LOG: Revision 7.8  2003/01/10 22:42:00  sjaddu
 * LOG: Removed ckgp_list from OPC_DPC_INFO.
 * LOG:
 * LOG: Revision 7.7  2003/01/03 11:10:04  akumar
 * LOG: Added PRC as Preprocessor Directive along with CCITT
 * LOG:
 * LOG: Revision 7.6  2002/12/31 08:54:42  akumar
 * LOG: Modified for Segmentation Procedure and Brand new variable exchange_type
 * LOG: has been added
 * LOG:
 * LOG: Revision 7.5  2002/12/09 10:18:14  ssingh
 * LOG: Added 1 more type in status of remote ISUP indicators.
 * LOG:
 * LOG: Revision 7.4  2002/11/19 12:47:44  sjaddu
 * LOG: Added current_vcic to the opc dpc stat struct.
 * LOG:
 * LOG: Revision 7.3  2002/10/30 06:09:37  sjaddu
 * LOG: Added Continuity states.
 * LOG:
 * LOG: Revision 7.2  2002/10/21 12:26:49  ssingh
 * LOG: Added functions to support CQR (received) for ANSI implementation.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.10  2002/08/16 22:09:03  mmiers
 * LOG: Add the china variant
 * LOG:
 * LOG: Revision 6.9  2002/08/05 20:29:44  ssharma
 * LOG: Move CIC and dest pegs to isup_variants.h
 * LOG:
 * LOG: Revision 6.8  2002/08/01 15:47:44  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.7.2.11  2002/07/31 22:27:32  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.7.2.10  2002/07/30 13:19:13  sjaddu
 * LOG: Added one more state for cvts.
 * LOG:
 * LOG: Revision 6.7.2.9  2002/07/23 20:58:53  ssingh
 * LOG: Added/Removed/Changed FSM States as per ANSI/ITU.
 * LOG:
 * LOG: Revision 6.7.2.8  2002/07/15 21:16:20  hbalimid
 * LOG: Added new macros.
 * LOG:
 * LOG: Revision 6.7.2.7  2002/07/13 02:31:00  hbalimid
 * LOG: Added new macros for ANSI.
 * LOG:
 * LOG: Revision 6.7.2.6  2002/07/12 19:53:11  hbalimid
 * LOG: Hardware blocking specific to CCITT
 * LOG:
 * LOG: Revision 6.7.2.5  2002/07/11 17:25:48  hbalimid
 * LOG: SPRC circuit query states added.
 * LOG:
 * LOG: Revision 6.7.2.4  2002/07/10 19:27:11  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.7.2.3  2002/07/10 14:03:04  hbalimid
 * LOG: comments modified.
 * LOG:
 * LOG: Revision 6.7.2.2  2002/07/06 18:41:46  hbalimid
 * LOG: CVTR state for ANSI added.
 * LOG:
 * LOG: Revision 6.7.2.1  2002/07/05 21:53:28  hbalimid
 * LOG: Added ANSI CVT states to cic record.
 * LOG:
 * LOG: Revision 6.7  2002/06/28 18:36:26  ssharma
 * LOG: Changes for distributed ISUP.
 * LOG:
 * LOG: Revision 6.6  2002/06/24 17:07:48  ssingh
 * LOG: Add new state for GRA, add confirmations and indications.
 * LOG:
 * LOG: Revision 6.5  2002/06/03 16:25:48  sjaddu
 * LOG: Added Param level confusion.
 * LOG:
 * LOG: Revision 6.4  2002/05/28 16:46:08  sjaddu
 * LOG: Added CFN Procedures.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 21:22:36  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:28:59  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.4.2.7  2002/05/14 20:51:28  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 5.4.2.6  2002/04/18 19:03:16  ssanyal
 * LOG: petty changes for documantation
 * LOG:
 * LOG: Revision 5.4.2.5  2002/04/05 19:35:50  ssharma
 * LOG: Add parameter to TimeoutHandlerProc
 * LOG:
 * LOG: Revision 5.4.2.4  2002/03/22 16:17:47  ssharma
 * LOG: Add a timer counter to CIC record.
 * LOG:
 * LOG: Revision 5.4.2.3  2002/03/19 17:31:01  ssharma
 * LOG: Add states for Circuit reset state machines.
 * LOG:
 * LOG: Revision 5.4.2.2  2002/03/14 15:26:27  ssharma
 * LOG: Add timer counts and CSC states.
 * LOG:
 * LOG: Revision 5.4.2.1  2002/03/07 20:17:38  ssharma
 * LOG: New flags in CIC_INFO, new error codes for ISUP error indications.
 * LOG:
 * LOG: Revision 5.4  2002/02/20 23:21:30  ssharma
 * LOG: Fix the number of states.
 * LOG:
 * LOG: Revision 5.3  2002/02/19 23:09:03  ssharma
 * LOG: Add macro to get SIO from PCIC.
 * LOG:
 * LOG: Revision 5.2  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 5.1  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 *
 ****************************************************************************/
/*******************************************************************************
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * kramesh   05-04-2005  BCGI bugs       Local Congestion level enum.
 *                       BugId:488,      new CRO state.
 *                         421,423
 ******************************************************************************/

#if !defined(ISUP_VARIANTS_H)
#define ISUP_VARIANTS_H

#if defined(PRC)
#include <china/isup.h>
#elif defined(TTC)
#include <japan/isup.h>
#elif defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#include <isup_cmn.h>
#include <isup_sn.h>
#include <its_mlist.h>
#include <its_hash.h>
#include <its_pegs.h>

#if defined(__cplusplus)
extern "C"
{
#endif


#define ISUP_MAX_CKGPS    700

/* ISUP Message PEGS (Common To both ANSI and ITU) 
 * Pegs sent fromn Application/Stack to remote are defined here
 */

#define PEG_ISUP_IAM_SENT_TO_REMOTE        0
#define PEG_ISUP_ACM_SENT_TO_REMOTE        1
#define PEG_ISUP_ANM_SENT_TO_REMOTE        2
#define PEG_ISUP_REL_SENT_TO_REMOTE        3
#define PEG_ISUP_RLC_SENT_TO_REMOTE        4
#define PEG_ISUP_BLO_SENT_TO_REMOTE        5
#define PEG_ISUP_UBL_SENT_TO_REMOTE        6
#define PEG_ISUP_BLA_SENT_TO_REMOTE        7
#define PEG_ISUP_CPG_SENT_TO_REMOTE        8
#define PEG_ISUP_CGB_SENT_TO_REMOTE        9
#define PEG_ISUP_CGBA_SENT_TO_REMOTE      10
#define PEG_ISUP_CQM_SENT_TO_REMOTE       11
#define PEG_ISUP_CQR_SENT_TO_REMOTE       12
#define PEG_ISUP_GRS_SENT_TO_REMOTE       13
#define PEG_ISUP_GRA_SENT_TO_REMOTE       14
#define PEG_ISUP_CGU_SENT_TO_REMOTE       15
#define PEG_ISUP_CGUA_SENT_TO_REMOTE      16
#define PEG_ISUP_CRG_SENT_TO_REMOTE       17
#define PEG_ISUP_CFN_SENT_TO_REMOTE       18
#define PEG_ISUP_COT_SENT_TO_REMOTE       19
#define PEG_ISUP_CCR_SENT_TO_REMOTE       20
#define PEG_ISUP_FOT_SENT_TO_REMOTE       21
#define PEG_ISUP_INF_SENT_TO_REMOTE       22
#define PEG_ISUP_INR_SENT_TO_REMOTE       23
#define PEG_ISUP_LPA_SENT_TO_REMOTE       24
#define PEG_ISUP_PAM_SENT_TO_REMOTE       25
#define PEG_ISUP_RSC_SENT_TO_REMOTE       26
#define PEG_ISUP_RES_SENT_TO_REMOTE       27
#define PEG_ISUP_SUS_SENT_TO_REMOTE       28
#define PEG_ISUP_UBA_SENT_TO_REMOTE       29
#define PEG_ISUP_UCIC_SENT_TO_REMOTE      30


/* ISUP Destination related Pegs 
 * Pegs recevied from Remote are defined here
 */

#define PEG_ISUP_REMOTE_IAM_RCVD     0
#define PEG_ISUP_REMOTE_ACM_RCVD     1
#define PEG_ISUP_REMOTE_ANM_RCVD     2
#define PEG_ISUP_REMOTE_REL_RCVD     3
#define PEG_ISUP_REMOTE_RLC_RCVD     4
#define PEG_ISUP_REMOTE_BLO_RCVD     5
#define PEG_ISUP_REMOTE_UBL_RCVD     6
#define PEG_ISUP_REMOTE_BLA_RCVD     7
#define PEG_ISUP_REMOTE_CPG_RCVD     8
#define PEG_ISUP_REMOTE_CGB_RCVD     9
#define PEG_ISUP_REMOTE_CGBA_RCVD   10
#define PEG_ISUP_REMOTE_CQM_RCVD    11
#define PEG_ISUP_REMOTE_CQR_RCVD    12
#define PEG_ISUP_REMOTE_GRS_RCVD    13
#define PEG_ISUP_REMOTE_GRA_RCVD    14
#define PEG_ISUP_REMOTE_CGU_RCVD    15
#define PEG_ISUP_REMOTE_CGUA_RCVD   16
#define PEG_ISUP_REMOTE_CRG_RCVD    17
#define PEG_ISUP_REMOTE_CFN_RCVD    18
#define PEG_ISUP_REMOTE_COT_RCVD    19
#define PEG_ISUP_REMOTE_CCR_RCVD    20
#define PEG_ISUP_REMOTE_FOT_RCVD    21
#define PEG_ISUP_REMOTE_INF_RCVD    22
#define PEG_ISUP_REMOTE_INR_RCVD    23
#define PEG_ISUP_REMOTE_LPA_RCVD    24
#define PEG_ISUP_REMOTE_PAM_RCVD    25
#define PEG_ISUP_REMOTE_RSC_RCVD    26
#define PEG_ISUP_REMOTE_RES_RCVD    27
#define PEG_ISUP_REMOTE_SUS_RCVD    28
#define PEG_ISUP_REMOTE_UBA_RCVD    29
#define PEG_ISUP_REMOTE_UCIC_RCVD   30

/* Always keep this adjusted */
#define ISUP_MAX_MSG_CODE           255




/*
 * ISUP Destination and CIC specific pegs
 */
#define PEG_ISUP_DEST_REM_AVAIL            0 
#define PEG_ISUP_DEST_REM_UNAVAIL          1 
#define PEG_ISUP_DEST_REM_CONGES           2 
#define PEG_ISUP_DEST_REM_CONGES_SEIZED    3 
#define PEG_ISUP_DEST_PAUSE                4
#define PEG_ISUP_DEST_RESUME               5

/* always keep this adjusted*/
#define PEG_ISUP_DEST_NUM_PEGS                  6

#define PEG_ISUP_CIC_NO_ACK_RSC_T17             0  /*12.1*/
#define PEG_ISUP_CIC_NO_GRA_T23                 1  /*12.2*/
#define PEG_ISUP_CIC_NO_RLC_T5                  2  /*12.5*/
#define PEG_ISUP_CIC_REL_ABNORMAL               3  /*12.6*/
#define PEG_ISUP_CIC_BLO_CRC_ERR                4  /*12.7*/
#define PEG_ISUP_CIC_MISSING_ACK_IN_CGBA        5  /*12.8*/
#define PEG_ISUP_CIC_MISSING_ACK_IN_CGUA        6  /*12.9*/
#define PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA       7  /*12.10*/
#define PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA       8  /*12.11*/
#define PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK    9  /*12.12*/
#define PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK    10  /*12.13*/
#define PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK     11  /*12.14*/
#define PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK     12  /*12.15*/
#define PEG_ISUP_CIC_NO_BLA_T13                 13  /*12.16*/
#define PEG_ISUP_CIC_NO_UBA_T15                 14  /*12.17*/
#define PEG_ISUP_CIC_NO_CGBA_T19                15  /*12.18*/
#define PEG_ISUP_CIC_NO_CGUA_T21                16  /*12.19*/
#define PEG_ISUP_CIC_MSG_FORMAT_ERR             17  /*12.20*/
#define PEG_ISUP_CIC_UNEXP_MSG_RCVD             18  /*12.21*/
#define PEG_ISUP_CIC_REL_UNRECOG_INFO           19  /*12.22*/
#define PEG_ISUP_CIC_UNABLE_RELEASE_CKT         20  /*12.23*/
/* always keep this adjusted*/
#define PEG_ISUP_CIC_NUM_PEGS                   21

/********************************************************************
 * Global (independent of variant) data structures.
 *******************************************************************/

/*
 * The structure of PCIC (Physical CIC) is given here..
 * Byte 0 - SIO
 * Byte 1-4 - routing label
 * Byte 5-6 - CIC
 */
typedef struct
{
    MTP3_HEADER     hdr;
    ITS_USHORT      cic;
}
ISUP_PCIC;

#define ISUP_PCIC_TO_CIC(physical_cic) \
        (physical_cic.cic)

#define ISUP_PCIC_TO_OPC(physical_cic) \
        MTP3_RL_GET_OPC_VALUE(physical_cic.hdr.label)

#define ISUP_PCIC_TO_DPC(physical_cic) \
        MTP3_RL_GET_DPC_VALUE(physical_cic.hdr.label)

#define ISUP_PCIC_TO_OPC_DPC(physical_cic) \
        (physical_cic.hdr)

#define ISUP_PCIC_TO_SIO(physical_cic) \
        (physical_cic.hdr.sio)

/*
 * PCIC (Physical CIC) Function signatures
 */
/*
 * PCIC (Physical CIC) Functions
 */

/*
 *      Set physical CIC from its components
 *
 *  Input Parameters:
 *      opcid - logical opc id
 *      dpcid - logical dpc id
 *      cic - 16 bit cic number
 *
 *  Output Parameters:
 *      pcic - representation of the pcic.
 */
#define ISUP_PCICFromParts(p, o, d, s, c)           \
    do                                              \
    {                                               \
        memset((p), 0, sizeof(ISUP_PCIC));          \
        MTP3_HDR_SET_SIO((p)->hdr, (s));            \
        MTP3_RL_SET_OPC_VALUE((p)->hdr.label, (o)); \
        MTP3_RL_SET_DPC_VALUE((p)->hdr.label, (d)); \
        MTP3_RL_SET_SLS((p)->hdr.label, (ITS_OCTET)(c));       \
        (p)->cic = (c);                             \
    }                                               \
    while (0)

/*
 *      Get components from a physical CIC
 *
 *  Input Parameters:
 *      pcic - representation of the pcic.
 *
 *  Output Parameters:
 *      opcid - logical opc id
 *      dpcid - logical dpc id
 *      cic - 16 bit cic number
 */
#define ISUP_PCICToParts(p, o, d, s, c)             \
    do                                              \
    {                                               \
        *(c) = ISUP_PCIC_TO_CIC(p);                 \
        *(o) = ISUP_PCIC_TO_OPC(p);                 \
        *(d) = ISUP_PCIC_TO_DPC(p);                 \
        *(s) = MTP3_HDR_GET_SIO((p).hdr);           \
    }                                               \
    while (0)

/********************************************************************
 * Global (independent of variant) hash tables.
 *******************************************************************/

/********************************************************************
 * Hash Table 1
 *
 * Key:      opcid_dpcid
 * Value:   -variant class info (integer denoting the variant, variant class
 *           record)
 *          -array of timer handling structure (boolean indicating who handles
 *           the timer, timer value)
 *          -linked list of circuit groups information (start cirtcuit number, 
 *           number of circuits, ciccontrol)
 *          -boolean congestion_indicator
 *
 *******************************************************************/

/*
 * who handles a timer and value of that timer. the index in the array
 * denotes the timer id.
 */
typedef struct
{
    ISUP_TMR_HNDL   tmr_hndl_layer;
    ITS_UINT        tmr_value;
} 
ISUP_TMR_HNDL_INFO;

#define ISUP_TMR_VAL_INV 0xFFFFFFFF

#define ISUP_TMR_VAL_DEF 15

#define ISUP_TMR_LAYER(tmr_hndl_info) \
        (tmr_hndl_info->tmr_hndl_layer)

#define ISUP_TMR_VAL(tmr_hndl_info) \
        (tmr_hndl_info->tmr_value)

/*
 * max num of timers
 */
#define ISUP_MAX_TMRS 64

/*
 * Possible messaging states for stack procedures.
 */
typedef enum
{
    IDLE,              /* Idle State = NULL Context. */
    WAIT_INCOMING_ACM, /* IAM sent to network, waiting for ACM. */
    WAIT_INCOMING_ANM, /* ACM sent to network, waiting for ANM. */
    RCVD_INCOMING_ANM, /* ANM rcvd from network, call established. */
    WAIT_INCOMING_RLC, /* REL sent to network, waiting for RLC. */
    WAIT_INCOMING_RES, /* SUS rcvd from network, call suspended, */
                       /* waiting for RES. */
    WAIT_OUTGOING_ACM, /* IAM rcvd from network, waiting to send ACM. */
    WAIT_OUTGOING_ANM, /* ACM rcvd from network, waiting to send ANM. */    
    SENT_OUTGOING_ANM, /* ANM sent to network, call established. */
    WAIT_OUTGOING_RLC, /* REL rcvd from network, waiting to send RLC. */
    WAIT_OUTGOING_RES, /* SUS sent to network, call suspended, */
                       /* waiting to send RES to network. */
    WAIT_OUTGOING_REL, /* Timeout/error, waiting to send REL to network. */
    WAIT_OUTGOING_RSC, /* RSC sent to network, waiting for RLC. */
    WAIT_OUTGOING_GRA, /* GRS rcvd from network,waiting to send GRA to network*/

    WAIT_CONTINUITY_REPORT, /* wait for cot report ,when cot outgoing*/
    WAIT_INCOMING_COT,  /* wait for incoming cot */

    WAIT_COT_REPORTS_AND_CRA,  /* Wait for COT from App and CRA from Network */
    WAIT_COT_REPORTS_HAVE_CRA, /* Wait for COT reports from App, CRA received */
    WAIT_INCOMING_CRA,         /* Wait for CRA from Netowrk, COt received */
    WAIT_OUTGOING_IAM,         /* Wait for IAM from App, CRM/CRA completed */
    WAIT_INCOMING_IAM,         /* Wait IAM from network after CRM/CRA test */
    WAIT_INCOMING_COT_AND_IAM  /* Wait for COT-n-IAM from network after CRM */
}
ITS_ISUP_STATE;

/*
 * all information about a circuit group
 */

/* Max number of cics in a ckt grp */

#if defined(CCITT) || defined(PRC) || defined(TTC)
#define MAX_CICS_PER_CKGP  32
#elif defined(ANSI)
#define MAX_CICS_PER_CKGP  24
#endif

#define ISUP_INV_CKGP_ID 0xFFFF

typedef struct _ISUP_CKGP_INFO
{
    ITS_USHORT     ckgp_id;
    ITS_UINT       usable_cics[1];
    ITS_OCTET      ckgp_control[MAX_CICS_PER_CKGP];
}
ISUP_CKGP_INFO;

typedef struct _ISUP_CKGPS
{
    MTP3_HEADER         opc_dpc_ni;
    ITS_USHORT          noCkgps;
    ISUP_CKGP_INFO      ckgp_info[ISUP_MAX_CKGPS];
} 
ISUP_CKGP_LIST;

#define ISUP_CKGP_ID(isup_ckgp_info) \
        (isup_ckgp_info->ckgp_id)

#define ISUP_CKGP_USABLE_CICS(isup_ckgp_info) \
        (isup_ckgp_info->usable_cics)

#define ISUP_CKGP_CONTROL(isup_ckgp_info) \
        (isup_ckgp_info->ckgp_control)


#define ISUP_SET_BIT(byte, bit) \
        (byte |= (0x01 << bit));

#define ISUP_UNSET_BIT(byte, bit) \
        (byte &= ~(0x01 << bit));

#define ISUP_GET_BIT(byte, bit) \
        ((byte >> bit) & 0x01)


/*
 * remote congestion level indicator 
 */
typedef enum
{
    ISUP_RMT_CONGES_OFF,
    ISUP_RMT_CONGES_LEVEL1,
    ISUP_RMT_CONGES_LEVEL2,
    ISUP_RMT_CONGES_LEVEL3
} 
ISUP_CONGES;

/*
 * local congestion level indicator
 */
typedef enum
{
    ISUP_LOC_CONGES_OFF,
    ISUP_LOC_CONGES_LEVEL1,
    ISUP_LOC_CONGES_LEVEL2,
    ISUP_LOC_CONGES_LEVEL3,
}
ISUP_LOC_CONGES;



/*
 *  This parameter indicates status of the 
 *  destination,whether it is available or not.
 *  This parameter is set when MTP3 PAUSE/RESUME comes.
 */
typedef enum
{
    ISUP_DEST_UNREACHABLE = 0,
    ISUP_DEST_REACHABLE   
}
ISUP_DEST_STATUS;

/*
 *  This parameter indicates status of the 
 *  remote ISUP,whether it is available or not.
 *  This parameter is set when MTP3 STATUS comes
 *  with cause user part inaccessible.
 */
typedef enum
{
    ISUP_REMOTE_AVAILABLE = 0,
    ISUP_REMOTE_UNAVAILABLE,
    ISUP_REMOTE_UNEQUIPPED
}
ISUP_REMOTE_ISUP_STATUS;


/*
 * To store OPC DPC dynamic status information. This is stored
 * as part of the OPC DPC information table and is shared between
 * the nodes
*/
typedef struct
{
    MTP3_HEADER                 opc_dpc_ni;
    ISUP_VAR_TYPE               isup_var_type;
    ISUP_TMR_HNDL_INFO          tmr_hndl_info[ISUP_MAX_TMRS];
    ISUP_CONGES                 isup_rmt_conglev;
    ISUP_DEST_STATUS            dest_stat;
    ISUP_REMOTE_ISUP_STATUS     remote_isup_stat;
    ISUP_XCHANGE_TYPE           exchange_type;
    ISUP_LOC_CONGES             isup_loc_conglev;
#if defined (CCITT) || defined(PRC) || defined(TTC)
    ITS_BOOLEAN                 segmentation_supported;
#endif
    ITS_UINT                    pegs[PEG_ISUP_DEST_NUM_PEGS];
    PEG_Manager                 ISUP_DEST_PEGS;            
    ITS_UINT                    repeat_rsc_timerval;
}
ISUP_OPC_DPC_STAT;

#define ISUP_SET_OPC_DPC_LOC_CONG(opc_dpc_info, conglev) \
        ((opc_dpc_info)->isup_loc_conglev = conglev)

#define ISUP_GET_OPC_DPC_LOC_CONG(opc_dpc_info) \
        ((opc_dpc_info)->isup_loc_conglev)


#define ISUP_SYNC_TIMER_VAL   3* 60 /*3 minutues define in ms*/

/*
 * hash table info structure, this is local copy of stat
 */
typedef struct _isup_opc_dpc_info
{
    struct _isup_opc_dpc_info   *next;
    MTP3_HEADER                 opc_dpc_ni;
    MTP3_HEADER                 in_hdr;
    MTP3_HEADER                 out_hdr;
    ISUP_VAR_TYPE               isup_var_type;
    ITS_Class                   isup_var_class;
    ISUP_TMR_HNDL_INFO          tmr_hndl_info[ISUP_MAX_TMRS];
    ISUP_CONGES                 isup_rmt_conglev;
    ISUP_DEST_STATUS            dest_stat;
    ISUP_REMOTE_ISUP_STATUS     remote_isup_stat;
    ISUP_XCHANGE_TYPE           exchange_type;
#if defined (CCITT) || defined(PRC) || defined(TTC)
    ITS_BOOLEAN                 segmentation_supported;
#endif
    ITS_TIME                    syncTime;
    ITS_UINT                    pegs[PEG_ISUP_DEST_NUM_PEGS];
    ITS_UINT                    pegs_msg_sent[ISUP_MAX_MSG_CODE];
    ITS_UINT                    pegs_msg_rcvd[ISUP_MAX_MSG_CODE];
    PEG_Manager                 ISUP_DEST_PEGS;            
    PEG_Manager                 ISUP_PEGS_SENT;
    PEG_Manager                 ISUP_PEGS_RCVD;
    ITS_UINT                    repeat_rsc_timerval;
}
ISUP_OPC_DPC_INFO;

/*
 * helper macros
 */
#define ISUP_OPC_DPC_KEY(opc_dpc_info) \
        ((opc_dpc_info)->opc_dpc_ni)

#define ISUP_OPC_DPC_VAR_TYPE(opc_dpc_info) \
        ((opc_dpc_info)->isup_var_type)

#define ISUP_OPC_DPC_VAR_CLASS(opc_dpc_info) \
        ((opc_dpc_info)->isup_var_class)

#define ISUP_OPC_DPC_TMR(opc_dpc_info, index) \
        ((index >= 0) && (index < ISUP_MAX_TMRS)) ? \
        ((opc_dpc_info)->opc_dpc_stat->tmr_hndl_info[index]) : NULL

#define ISUP_OPC_DPC_CKGP_LIST(opc_dpc_info) \
        ((opc_dpc_info)->ckgp_info_list)

#define ISUP_OPC_DPC_CONGES(opc_dpc_info) \
        ((opc_dpc_info)->opc_dpc_stat->conges_indic)

#define ISUP_OPC_DPC_IN_HDR(opc_dpc_info) \
        ((opc_dpc_info)->in_hdr)

#define ISUP_OPC_DPC_OUT_HDR(opc_dpc_info) \
        ((opc_dpc_info)->out_hdr)

/* Macros for getting MSG/TMR proc key */
#define ISUP_MSG_PROC_KEY(state, msg) \
        (((state << 8) & 0x0000FF00) | msg)

#define ISUP_TMR_PROC_KEY(state, tmr) \
        (((state << 8) & 0x0000FF00) | tmr)

/* Macro for Application to access event type */
#define ISUP_GetISUPMsgType(event) \
        (event->data[0])

/********************************************************************
 * Hash Table 6
 *
 * Key:      vcic
 * Value:    information about that cic..
 *              vcic
 *              pcic
 *              cic_state
 *              fsm_state
 *              mtp3 header of message
 *              Release message contents
 *              IAM message contents
 *              Record lock information
 *
 *******************************************************************/

/********************************************************************
 * Hash Table 7
 *
 * Key:      pcic
 * Value:    information about that cic..
 *              vcic
 *              pcic
 *              cic_state
 *              fsm_state
 *              mtp3 header of message
 *              Release message contents
 *              IAM message contents
 *              Record lock information
 *
 *******************************************************************/

/*
 * NOTE NOTE NOTE NOTE NOTE
 * 
 * The two hash tables are meant to provide different access keys. The 
 * cic information is only allocated once and a pointer to the information
 * is put in both the tables. The developer using the public API is not
 * aware that there are two underlying tables. 
 *
 */

 /********************************************************************
 * The following codes are used in each circuit state indicator octet:
 * 
 * a)   for bits D C = 00 (00 = Out of Order)
 *      bits
 *      B A     Maintenance blocking state
 *      0 0     transient
 *      0 1     spare
 *      1 0     spare
 *      1 1     unequipped
 *      bits H-E    Spare
 *
 * b)   for bits D C not equal to 00
 *      bits
 *      BA      Maintenance blocking state
 *      0 0     no blocking (active)
 *      0 1     locally blocked
 *      1 0     remotely blocked
 *      1 1     locally and remotely blocked
 *      
 *      bits
 *      D C     Call processing state
 *      0 1     circuit incoming busy
 *      1 0     circuit outgoing busy
 *      1 1     idle
 *      
 *      bits
 *      F E     Hardware blocking state (Note)
 *      0 0     no blocking (active)
 *      0 1     locally blocked
 *      1 0     remotely blocked
 *      1 1     locally and remotely blocked
 *      
 *      bits H-G    Spare
 *      
 *      NOTE - If bits F E are not coded 0 0, bits D C must be coded 1 1.
 *******************************************************************/

/*
 * data structures and helper macros
 */
#define ISUP_CIC_STATE_BA_MASK 0xFC
#define ISUP_CIC_STATE_DC_MASK 0xF3
#define ISUP_CIC_STATE_FE_MASK 0xCF
#define ISUP_CIC_STATE_HG_MASK 0x3F

#define ISUP_CIC_STATE_SET_BA(state, ba) \
        (state &= ISUP_CIC_STATE_BA_MASK); \
        (state |= ba)

#define ISUP_CIC_STATE_SET_DC(state, dc) \
        (state &= ISUP_CIC_STATE_DC_MASK); \
        (state |= (dc << 2))

#define ISUP_CIC_STATE_SET_FE(state, fe) \
        (state &= ISUP_CIC_STATE_FE_MASK); \
        (state |= (fe << 4))

#define ISUP_CIC_STATE_SET_HG(state, hg) \
        (state &= ISUP_CIC_STATE_HG_MASK); \
        (state |= (hg << 6))

#define ISUP_CIC_STATE_GET_BA(state) \
        (state & (~ISUP_CIC_STATE_BA_MASK))

#define ISUP_CIC_STATE_GET_DC(state) \
        ((state & (~ISUP_CIC_STATE_DC_MASK)) >> 2)

#define ISUP_CIC_STATE_GET_FE(state) \
        ((state & (~ISUP_CIC_STATE_FE_MASK)) >> 4)

#define ISUP_CIC_STATE_GET_HG(state) \
        ((state & (~ISUP_CIC_STATE_HG_MASK)) >> 6)

#define ISUP_CIC_SET_MAINT(state, maint_state) \
        ISUP_CIC_STATE_SET_BA(state, maint_state)

#define ISUP_CIC_SET_CALL(state, call_state) \
        ISUP_CIC_STATE_SET_DC(state, call_state)

#define ISUP_CIC_SET_HDW(state, hdw_state) \
        ISUP_CIC_STATE_SET_FE(state, hdw_state)
    
#define ISUP_CIC_GET_MAINT(state) \
        ISUP_CIC_STATE_GET_BA(state)

#define ISUP_CIC_GET_CALL(state) \
        ISUP_CIC_STATE_GET_DC(state)

#define ISUP_CIC_GET_HDW(state) \
        ISUP_CIC_STATE_GET_FE(state)

#define ISUP_CIC_SET_UNEQUIPPED(state) \
        ISUP_CIC_STATE_SET_DC(state, CKTS_OUT_OF_ORDER_CTK); \
        ISUP_CIC_STATE_SET_BA(state, CKTS_UNEQUIPPED)

#define ISUP_CIC_SET_TRANSIENT(state) \
        ISUP_CIC_STATE_SET_DC(state, CKTS_OUT_OF_ORDER_CTK); \
        ISUP_CIC_STATE_SET_BA(state, CKTS_TRANSIENT)

#define ISUP_CIC_IS_UNEQUIPPED(state) \
        (ISUP_CIC_STATE_GET_DC(state) == CKTS_OUT_OF_ORDER_CTK && \
        ISUP_CIC_STATE_GET_BA(state) == CKTS_UNEQUIPPED) ? \
        1 : 0;

#define ISUP_CIC_IS_TRANSIENT(state) \
        (ISUP_CIC_STATE_GET_DC(state) == CKTS_OUT_OF_ORDER_CTK && \
        ISUP_CIC_STATE_GET_BA(state) == CKTS_TRANSIENT) ? \
        1 : 0;

#if defined(ANSI)
#define SPRC_CKTS_TRANSIENT            0x00
#define SPRC_CKTS_SPARE1               0x01
#define SPRC_CKTS_SPARE2               0x02
#define SPRC_CKTS_UNEQUIPPED           0x03

#define SPRC_CKTS_INBUSY_ACTIVE        0x04
#define SPRC_CKTS_INBUSY_LBLOCKED      0x05
#define SPRC_CKTS_INBUSY_RBLOCKED      0x06
#define SPRC_CKTS_INBUSY_LRBLOCKED     0x07

#define SPRC_CKTS_OUTBUSY_ACTIVE       0x08
#define SPRC_CKTS_OUTBUSY_LBLOCKED     0x09
#define SPRC_CKTS_OUTBUSY_RBLOCKED     0x0A
#define SPRC_CKTS_OUTBUSY_LRBLOCKED    0x0B

#define SPRC_CKTS_IDLE_ACTIVE          0x0C
#define SPRC_CKTS_IDLE_LBLOCKED        0x0D
#define SPRC_CKTS_IDLE_RBLOCKED        0x0E
#define SPRC_CKTS_IDLE_LRBLOCKED       0x0F

#define SPRC_CKTS_INVALID              0xFF

#define ISUP_CIC_STATE_A_MASK          0xFE
#define ISUP_CIC_STATE_B_MASK          0xFD

/* for Local Block Status only */
#define ISUP_CIC_STATE_GET_A(state) \
        (state & (~ISUP_CIC_STATE_A_MASK))

/* for Remote Block Status only */
#define ISUP_CIC_STATE_GET_B(state) \
        (state & (~ISUP_CIC_STATE_B_MASK))

#define ISUP_CIC_IS_BUSY(state) \
        ((ISUP_CIC_STATE_GET_DC(state) == CKTS_IN_CTK_BUSY) || \
        (ISUP_CIC_STATE_GET_DC(state) == CKTS_OUT_CTK_BUSY)) ? \
        1 : 0

#define ISUP_CIC_IS_IDLE(state) \
        ((ISUP_CIC_STATE_GET_DC(state) == CKTS_IDLE_CTK)) ? 1 : 0

#define ISUP_CIC_IS_LOC_BLOCKED(state) \
        ((ISUP_CIC_STATE_GET_A(state) == CKTS_LBLOCKED)) ? 1 : 0

#define ISUP_CIC_IS_REM_BLOCKED(state) \
        ((ISUP_CIC_STATE_GET_B(state) == CKTS_RBLOCKED)) ? 1 : 0

#define ISUP_CIC_REMOVE_LOC_BLOCK(state) \
        (state &= 0xFEU);

#define ISUP_CIC_REMOVE_REM_BLOCK(state) \
        (state &= 0xFDU);

#define ISUP_CIC_SET_LOC_MAINT(state) \
        (state |= ~(ISUP_CIC_STATE_A_MASK) );

#define ISUP_CIC_SET_REM_MAINT(state) \
        (state |= ~(ISUP_CIC_STATE_B_MASK) );

#endif

/*
 * CIC state 
 *      Set CIC state.
 *
 *  Input Parameters:
 *      maint_state - maintenance blocking state
 *      call_state - call state (idle, incoming, outgoing)
 *      hdw_state - hardware blocking state
 *  Output Parameters:
 *      state - byte representation of the state.
 */
#define ISUP_CICStateFromParts_CCITT(state, maint_state,      \
                                     call_state, hdw_state)   \
    do                                                        \
    {                                                         \
        *state = 0x00;                                        \
        if (call_state == CKTS_OUT_OF_ORDER_CTK)              \
        {                                                     \
            ISUP_CIC_STATE_SET_BA(*state, maint_state);       \
            ISUP_CIC_STATE_SET_DC(*state, call_state);        \
        }                                                     \
        else                                                  \
        {                                                     \
            ISUP_CIC_STATE_SET_BA(*state, maint_state);       \
            ISUP_CIC_STATE_SET_DC(*state, call_state);        \
            ISUP_CIC_STATE_SET_FE(*state, hdw_state);         \
        }                                                     \
    }                                                         \
    while (0)

/*
 *      Get CIC state.
 *
 *  Input Parameters:
 *      state - CIC state.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      maint_state - maintenance blocking state
 *      call_state - call state (idle, incoming, outgoing)
 *      hdw_state - hardware blocking state
 */
#define ISUP_CICStateToParts_CCITT(state, maint_state,       \
                                   call_state, hdw_state)    \
    do                                                       \
    {                                                        \
        *maint_state = ISUP_CIC_STATE_GET_BA(state);         \
        *call_state = ISUP_CIC_STATE_GET_DC(state);          \
        *hdw_state = ISUP_CIC_STATE_GET_FE(state);           \
    }                                                        \
    while (0)

/*
 * pending timers
 */
typedef struct
{
    ITS_SHORT      tmr_id;
    ITS_SERIAL     tmr_serial;
} 
ISUP_PNDG_TMR_INFO; 

#define ISUP_MAX_PNDG_TMRS 10

/*
 * message buffers
 */
#define ISUP_MAX_MSG_LEN 256
#define ISUP_MAX_CGB_LEN 64
#define ISUP_MAX_CGU_LEN 64
#define ISUP_MAX_GRS_LEN 64

typedef enum
{
    BLS_IDLE = 0,
    BLS_WAIT_FOR_BLA,
#if defined(CCITT) || defined(PRC) || defined(TTC)
    BLS_LBLOCKED,
#endif
    BLS_WAIT_FOR_UBA
}
ISUP_BLS_STATE;

typedef enum
{
#if defined (ANSI)
    BLR_IDLE = 0
#elif defined (CCITT) || defined(PRC) || defined(TTC)
    BLR_IDLE = 0,
    BLR_WAIT_FOR_BLO_RESP,
    BLR_RBLOCKED,
    BLR_WAIT_FOR_UBL_RESP
#endif
}
ISUP_BLR_STATE;

typedef enum
{
    MGBS_IDLE = 0,
    MGBS_WAIT_FOR_CGBA,
    MGBS_WAIT_FOR_CGUA
} 
ISUP_MGBS_STATE;

typedef enum
{
#if defined(ANSI)
    MGBR_IDLE = 0
#elif defined (CCITT) || defined(PRC) || defined(TTC)
    MGBR_IDLE = 0,
    MGBR_WAIT_FOR_BLO_RESP,
    MGBR_WAIT_FOR_UBL_RESP
#endif
}
ISUP_MGBR_STATE;

typedef enum
{
    CRS_IDLE = 0,
    CRS_WAIT_FOR_RELEASE
}
ISUP_CRS_STATE;

typedef enum
{
#if defined(ANSI)
    CRR_IDLE = 0
#elif defined(CCITT) || defined(PRC) || defined(TTC)
    CRR_IDLE = 0,
    CRR_WAIT_FOR_RESPONSE
#endif
}
ISUP_CRR_STATE;

typedef enum
{
    CGRS_IDLE = 0,
    CGRS_WAIT_FOR_GRA
} 
ISUP_CGRS_STATE;

typedef enum
{
#if defined (ANSI)
    CGRR_IDLE = 0
#elif defined (CCITT) || defined(PRC) || defined(TTC)
    CGRR_IDLE = 0,
    CGRR_WAIT_FOR_GROUP_RESET_COMPLETE
#endif
} 
ISUP_CGRR_STATE;

/*
 * Specifc states particular
 * to CCITT & not in ANSI
 * are added here
 */
#if defined(CCITT) || defined(PRC) || defined(TTC)
typedef enum
{
    HLB_IDLE = 0,
    HLB_LBLOCKED
} 
ISUP_HLB_STATE;

typedef enum
{
    HRB_IDLE = 0,
    HRB_RBLOCKED
} 
ISUP_HRB_STATE;

typedef enum
{
    HGBS_IDLE = 0,
    HGBS_WAIT_FOR_CGBA,
    HGBS_WAIT_FOR_CGUA
} 
ISUP_HGBS_STATE;

typedef enum
{
    HGBR_IDLE = 0,
    HGBR_WAIT_FOR_BLO_RESP,
    HGBR_WAIT_FOR_UBL_RESP
} 
ISUP_HGBR_STATE;
#endif /* CCITT specific */

/*
 * Specifc states particular
 * to ANSI & not in CCITT
 * are added here
 */
#if defined(ANSI)
typedef enum
{
    CVTS_IDLE = 0,
    CVTS_WAIT_FOR_CVR,
    CVTS_WAIT_FOR_CVR_UPT /* cvr for user part availability */
}
ISUP_CVTS_STATE;

typedef enum
{
    CVTR_IDLE = 0,
    CVTR_WAIT_FOR_CVR
}
ISUP_CVTR_STATE;
#endif /* ANSI Specific */


typedef enum
{
    RESET_FROM_CPC = 0,
    RESET_AFTER_T5,
    RESET_FROM_CC
} 
ISUP_RESET_FLAG;

typedef enum
{
    CCO_IDLE = 0,
    CCO_WAIT_COT_REPORT
}
ISUP_CCO_STATE;

typedef enum
{
    CCI_IDLE = 0,
    CCI_WAIT_FOR_COT
}
ISUP_CCI_STATE;

typedef enum
{
    CRO_IDLE = 0,
    CRO_WAIT_TIMER_EXPIRY,
    CRO_WAIT_FOR_OUTGOING_CCR,       /*wait for CCR from app*/
    CRO_WAIT_FOR_COT,
    CRO_WAIT_FOR_RLC
}
ISUP_CRO_STATE;

typedef enum
{
    DCO_IDLE = 0,
    DCO_WAIT_FOR_LPA
}
ISUP_DCO_STATE;

typedef enum
{
    CRI_IDLE = 0,
    CRI_WAIT_FOR_CCR,
    CRI_WAIT_FOR_LPA,
    CRI_WAIT_FOR_REL
}
ISUP_CRI_STATE;

typedef enum
{
     SSI_IDLE = 0,
     SSI_WAIT_FOR_SGM
}
ISUP_SSI_STATE;

typedef struct
{
    ISUP_PCIC               pcic;
    ITS_OCTET               cgb_msg[ISUP_MAX_CGB_LEN];
    ITS_USHORT              cgb_msg_len;
    ITS_OCTET               cgu_msg[ISUP_MAX_CGU_LEN];
    ITS_USHORT              cgu_msg_len;
    ITS_OCTET               grs_msg[ISUP_MAX_GRS_LEN];
    ITS_USHORT              grs_msg_len;
}
ISUP_CIC_MSG_INFO;

#define ISUP_CIC_CGB_MSG(cic_msg) ((cic_msg)->cgb_msg)
#define ISUP_CIC_CGB_LEN(cic_msg) ((cic_msg)->cgb_msg_len)
#define ISUP_CIC_CGU_MSG(cic_msg) ((cic_msg)->cgu_msg)
#define ISUP_CIC_CGU_LEN(cic_msg) ((cic_msg)->cgu_msg_len)
#define ISUP_CIC_GRS_MSG(cic_msg) ((cic_msg)->grs_msg)
#define ISUP_CIC_GRS_LEN(cic_msg) ((cic_msg)->grs_msg_len)

/*
 * hash table info structure
 */
typedef struct
{
    ITS_CTXT                vcic;
    ISUP_PCIC               pcic;
    ITS_OCTET               cic_rule;
    ITS_BOOLEAN             resrv_ind;
    ITS_OCTET               cic_state;
    ITS_ISUP_STATE          fsm_state;
    ITS_ISUP_STATE          pre_susp_state;
    ISUP_PNDG_TMR_INFO      pndg_tmrs[ISUP_MAX_PNDG_TMRS];

    ITS_OCTET               cpc_msg[ISUP_MAX_MSG_LEN];
    ITS_USHORT              cpc_msg_len;

    ISUP_BLS_STATE          bls_state;
    ISUP_BLR_STATE          blr_state;
    ISUP_MGBS_STATE         mgbs_state;
    ISUP_MGBR_STATE         mgbr_state;
#if defined(CCITT) || defined(PRC) || defined(TTC)
    ISUP_HLB_STATE          hlb_state;  
    ISUP_HRB_STATE          hrb_state;
    ISUP_HGBS_STATE         hgbs_state;
    ISUP_HGBR_STATE         hgbr_state;
#endif
    ISUP_CRS_STATE          crs_state;
    ISUP_CRR_STATE          crr_state;
    ISUP_CGRS_STATE         cgrs_state;
    ISUP_CGRR_STATE         cgrr_state;
#if defined(ANSI)
    ISUP_CVTS_STATE         cvts_state;
    ITS_OCTET               cntTCVT;
    ISUP_CVTR_STATE         cvtr_state;
#endif
    ISUP_CCO_STATE          cco_state;
    ISUP_CCI_STATE          cci_state;
    ISUP_CRO_STATE          cro_state;
    ISUP_DCO_STATE          dco_state;
    ISUP_CRI_STATE          cri_state;

    ITS_BOOLEAN             cot_first_ind;
#if defined(CCITT) || defined(PRC) || defined(TTC)
    ISUP_SSI_STATE          ssi_state;
    ITS_OCTET               lastOverlenMsg;
#endif
    ISUP_RESET_FLAG         reset_flag;
    ITS_OCTET               cgrr_h_status;
    ITS_OCTET               cgrr_m_status;
    ITS_OCTET               PAM_allowed[2];
    ITS_BOOLEAN             ovld_indic;
    ITS_OCTET               cntT1;
    ITS_OCTET               cntT12;
    ITS_OCTET               cntT13;
    ITS_OCTET               cntT14;
    ITS_OCTET               cntT15;
    ITS_OCTET               cntT16;
    ITS_OCTET               cntT17;
    ITS_OCTET               cntT18;
    ITS_OCTET               cntT19;
    ITS_OCTET               cntT20;
    ITS_OCTET               cntT21;
    ITS_OCTET               cntT22;
    ITS_OCTET               cntT23;
    ITS_UINT                pegs[PEG_ISUP_CIC_NUM_PEGS];
    PEG_Manager             ISUP_CIC_PEGS;            
}
ISUP_CIC_INFO;

#define ISUP_CIC_VCIC(cic_info) \
        ((cic_info)->vcic)

#define ISUP_CIC_PCIC(cic_info) \
        ((cic_info)->pcic)

#define ISUP_CIC_STATE(cic_info) \
        ((cic_info)->cic_state)

#define ISUP_CIC_FSM_STATE(cic_info) \
        ((cic_info)->fsm_state)

#define ISUP_CIC_PRE_SUSP_STATE(cic_info) \
        ((cic_info)->pre_susp_state)

#define ISUP_CIC_PNDG_TMRS(cic_info) \
        ((cic_info)->pndg_tmrs)

#define ISUP_CIC_CPC_MSG(cic_msg) \
        ((cic_msg)->cpc_msg)

#define ISUP_CIC_CPC_LEN(cic_msg) \
        ((cic_msg)->cpc_msg_len)

#define ISUP_CIC_PAM_ALLOWED(cic_info) \
        ((cic_info)->PAM_allowed)

/*****************************************************************************
 *
 * ISUP Variant "Base Class".
 *
 ****************************************************************************/

#define ISUP_NB_ROWS_TABLE_MSG_SET   32
#define ISUP_NB_MSGS    256 
#define ISUP_NB_STATES   22
#define ISUP_NB_TIMERS   ISUP_MAX_TMRS 


/*
** Convenience #defines for setting the rows in MsgSupported Table
*/
#define TABLE_MSG_SUPPORTED_ROWX_CLEAR  0x00U
#define TABLE_MSG_SUPPORTED_ROWX_SET    0xFFU


/*
** Data section of the ISUP Variant Record.
*/
typedef struct
{
    /* Table representing the set of msgs supported by a variant. */
    ITS_OCTET   ISUP_MsgSupported[ISUP_NB_ROWS_TABLE_MSG_SET];

    /* Table storing details of timers supported by a variant. */
    ISUP_TMR_HNDL_INFO ISUP_TimerData[ISUP_NB_TIMERS];

    /* Table holding a pointer to each msg description (if msg supported). */
    ISUP_MSG_DESC* ISUP_MsgDescription[ISUP_NB_MSGS];

    /* Hash Table storing function pointers for message procs. in each state */
    HASH_Table  ISUP_MsgProcedures;

    /* Hash Table storing function pointers for timeout procs. in each state */
    HASH_Table  ISUP_TimeOutProcedures;

    /* First CIC in ckt. group - 0(Generic ANSI) / 1(Generic ITU/ Bell ANSI) */
    ITS_USHORT  FirstCICInCkgp;

    /* Number of cics supported in 1 ckt. group - 24(ANSI)/32(ITU) */
    ITS_OCTET   CICsInCkgp;

    /* To know if the variant supports the Msg or Param Compatibility info. */
    ITS_OCTET  ISUP_supportMsgCompInfo;
    ITS_OCTET   ISUP_supportParamCompInfo;

    /* To know if the exchange is an ISUP transit network or not: TypeA ex. etc.    */
    ITS_OCTET   ISUP_exchangeType;

    /*Pass on to application in case of unrecognized msg or Parameter  */
    ITS_BOOLEAN pass_on_flag;
}
ISUP_VariantInfo;

#define ISUP_VI_MSGS_SUPP(x) \
    ((x)->ISUP_MsgSupported)

#define ISUP_VI_TIMER_DATA(x) \
    ((x)->ISUP_TimerData)

#define ISUP_VI_MSG_DESC(x) \
    ((x)->ISUP_MsgDescription)

#define ISUP_VI_MSG_PROCS(x) \
    ((x)->ISUP_MsgProcedures)

#define ISUP_VI_TIMEOUT_PROCS(x) \
    ((x)->ISUP_TimeOutProcedures)

#define ISUP_VI_FIRST_CIC(x) \
    ((x)->ISUP_FirstCICInCkgp)

#define ISUP_VI_CICS_PER_GRP(x) \
    ((x)->ISUP_CICsInCkgp)

#define ISUP_VI_SUPP_MSG_COMP(x) \
    ((x)->ISUP_supportMsgCompInfo)

#define ISUP_VI_SUPP_PARAM_COMP(x) \
    ((x)->ISUP_supportParamCompInfo)

#define ISUP_VI_EXCH_TYPE(x) \
    ((x)->ISUP_exchangeType)

#define ISUP_VI_PASS_ON_FLAG(x) \
    ((x)->pass_on_flag)
/*
** These signatures define the ISUP Variant class implementation functions.
*/
typedef void            (*__ISUP_MsgHandlerProc)(ITS_EVENT*, ISUP_CIC_INFO*,
                                         ISUP_OPC_DPC_INFO*, ITS_OCTET);
typedef void    (*__ISUP_TimeoutHandlerProc)(ISUP_TIMER_ENTRY*, ISUP_CIC_INFO*,
                                             ISUP_OPC_DPC_INFO*);

typedef ITS_UINT        (*__ISUP_ComputeMSizeProc)(ITS_Class, ITS_OCTET);
typedef ITS_OCTET       (*__ISUP_HandleUnrecMsgProc)(ITS_Class, ITS_EVENT *);
typedef ITS_OCTET       (*__ISUP_HandleUnrecParamProc)(ITS_Class,ITS_OCTET,
                                                                 ITS_OCTET *);
typedef int             (*__ISUP_InitMsgProcs)(ITS_Class);
typedef int             (*__ISUP_InitTimeoutProcs)(ITS_Class);
typedef int             (*__ISUP_SetMsgProc)(ITS_Class, HASH_Table,
                                             ITS_OCTET, ITS_ISUP_STATE,
                                             __ISUP_MsgHandlerProc);
typedef int             (*__ISUP_SetTimeoutProc)(ITS_Class, HASH_Table,
                                                 ITS_UINT, ITS_ISUP_STATE,
                                                 __ISUP_TimeoutHandlerProc);
typedef __ISUP_MsgHandlerProc    
                        (*__ISUP_GetMsgProc)(ITS_Class, ITS_OCTET,
                                             ITS_ISUP_STATE);
typedef __ISUP_TimeoutHandlerProc 
                        (*__ISUP_GetTimeoutProc)(ITS_Class, ITS_UINT,
                                                 ITS_ISUP_STATE);

/*
** the ISUP Variant Definition
*/
typedef struct
{
    /* members of the ISUP variant: "protected". */
    ISUP_VariantInfo                *info;         

    /****** "public" functions ("protected" variable access): *****/

    /* To decode/encode a msg from ISUP/IEs format to ISUP/IES format. */
    __ISUP_DecodeMsgProc                   DecodeMsg;
    __ISUP_EncodeMsgProc                   EncodeMsg;

    /* To calculate the size of a fixed size IE within a message */
    __ISUP_ComputeMSizeProc                ComputeMsize;

    /* To handle an unrecognized message */
    __ISUP_HandleUnrecMsgProc              HandleUnrecMsg;

    /* To get the function pointer for a message/timeout in a state */
    __ISUP_GetMsgProc                       GetMsgProcedure;
    __ISUP_GetTimeoutProc                   GetTimeoutProcedure;

    /****** "private" functions : Users stay out *****/

    /* Procedures for HashTable init. and set for function Pointers */ 
    __ISUP_InitMsgProcs                     InitMsgProcedures;
    __ISUP_InitTimeoutProcs                 InitTimeoutProcedures;
    __ISUP_SetMsgProc                       SetMsgProcedure;
    __ISUP_SetTimeoutProc                   SetTimeoutProcedure;

    /* To handle an unrecognized message */
    __ISUP_HandleUnrecParamProc              HandleUnrecParam;
}
ISUP_VARIANT_ClassPart;



/*
** the ISUP Variant Class Record.
*/
typedef struct
{
    ITS_CoreClassPart       coreClass;
    ISUP_VARIANT_ClassPart  variantClass;
}
ISUP_VARIANT_ClassRec, *ISUP_VARIANT_Class;


extern ISUP_VARIANT_ClassRec    isupVARIANT_ClassRec;
extern ITS_Class                isupVARIANT_Class;

/*
** Inheritance.
*/

#define ISUP_INFO_INHERIT                  ((ISUP_VariantInfo*)NULL)
#define ISUP_IS_MSG_SUPPORTED_INHERIT      ((__ISUP_IsMsgSupportedProc)NULL)
#define ISUP_IS_MSG_CI_SUPPORTED_INHERIT   ((__ISUP_IsMsgCompInfoSupportedProc)NULL)
#define ISUP_IS_PARAM_PI_SUPPORTED_INHERIT ((__ISUP_IsParamCompInfoSupportedProc)NULL)
#define ISUP_GET_MSG_DESC_INHERIT          ((__ISUP_GetMsgDescriptionProc)NULL)
#define ISUP_GET_CICS_IN_CKGP_INHERIT      ((__ISUP_GetCICsInCkgpProc)NULL)
#define ISUP_DECODE_MSG_INHERIT            ((__ISUP_DecodeMsgProc)NULL)
#define ISUP_ENCODE_MSG_INHERIT            ((__ISUP_EncodeMsgProc)NULL)
#define ISUP_COMPUTE_MSIZE_INHERIT         ((__ISUP_ComputeMSizeProc)NULL)
#define ISUP_HANDLE_UNREC_MSG_INHERIT      ((__ISUP_HandleUnrecMsgProc)NULL)
#define ISUP_HANDLE_UNREC_PARAM_INHERIT      ((__ISUP_HandleUnrecParamProc)NULL)
#define ISUP_INIT_MSG_PROCS_INHERIT        ((__ISUP_InitMsgProcs)NULL)
#define ISUP_GET_MSG_PROC_INHERIT          ((__ISUP_GetMsgProc)NULL)
#define ISUP_SET_MSG_PROC_INHERIT          ((__ISUP_SetMsgProc)NULL)
#define ISUP_INIT_TIMEOUT_PROCS_INHERIT    ((__ISUP_InitTimeoutProcs)NULL)
#define ISUP_GET_TIMEOUT_PROC_INHERIT      ((__ISUP_GetTimeoutProc)NULL)
#define ISUP_SET_TIMEOUT_PROC_INHERIT      ((__ISUP_SetTimeoutProc)NULL)

/*
** ISUP Variant Macros.
*/
#define ISUP_CLASS_INFO(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.info)
#define ISUP_CLASS_HASH_MSG_PROCS(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.info->ISUP_MsgProcedures)
#define ISUP_CLASS_HASH_TIMEOUT_PROCS(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.info->ISUP_TimeOutProcedures)
#define ISUP_DECODE_MSG(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.DecodeMsg)
#define ISUP_ENCODE_MSG(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.EncodeMsg)
#define ISUP_COMPUTE_MSIZE(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.ComputeMsize)    
#define ISUP_HANDLE_UNREC_MSG(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.HandleUnrecMsg)    
#define ISUP_HANDLE_UNREC_PARAM(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.HandleUnrecParam)    
#define ISUP_INIT_MSG_PROCS(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.InitMsgProcedures)    
#define ISUP_INIT_TIMEOUT_PROCS(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.InitTimeoutProcedures)    
#define ISUP_GET_MSG_PROC(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.GetMsgProcedure)    
#define ISUP_GET_TIMEOUT_PROC(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.GetTimeoutProcedure)    
#define ISUP_SET_MSG_PROC(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.SetMsgProcedure)    
#define ISUP_SET_TIMEOUT_PROC(x) \
    (((ISUP_VARIANT_Class)(x))->variantClass.SetTimeoutProcedure)    

/*
 * User Functions: Variant wrappers - these will call corresponding functions
 * for the appropriate variant class
 */
SS7DLLAPI ITS_BOOLEAN       VAR_IsMsgSupported(ITS_Class V_Class, ITS_OCTET msg);
SS7DLLAPI ITS_BOOLEAN       VAR_IsMsgCompInfoSupported(ITS_Class V_Class);
SS7DLLAPI ITS_BOOLEAN       VAR_IsParamCompInfoSupported(ITS_Class V_Class);
SS7DLLAPI ISUP_MSG_DESC*    VAR_GetMsgDescription(ITS_Class V_Class, ITS_OCTET);
SS7DLLAPI ITS_OCTET         VAR_GetNumCICs_Ckgp(ITS_Class V_Class); 
SS7DLLAPI ITS_USHORT        VAR_GetFirstCIC_Ckgp(ITS_Class V_Class); 
SS7DLLAPI void              VAR_GetCkgpFromCIC(ITS_Class V_Class, ITS_USHORT cic,
                                               ITS_USHORT *index, ITS_USHORT *ckgp,
                                               ITS_USHORT *numCics); 
SS7DLLAPI ITS_USHORT        VAR_GetCICFromCkgp(ITS_Class V_Class, ITS_USHORT ckgp,
                                               ITS_OCTET index);

SS7DLLAPI ISUP_TMR_HNDL_INFO*         VAR_GetTimerInfo(ITS_Class V_Class);
SS7DLLAPI __ISUP_MsgHandlerProc       VAR_GetMsgProc(ITS_Class V_Class,
                                                     ITS_OCTET msg,
                                                     ITS_ISUP_STATE state);
SS7DLLAPI __ISUP_TimeoutHandlerProc   VAR_GetTimeoutProc(ITS_Class V_Class,
                                                         ITS_UINT timer,
                                                         ITS_ISUP_STATE state);
SS7DLLAPI __ISUP_DecodeMsgProc        VAR_DecodeMsg(ITS_Class V_Class);
SS7DLLAPI __ISUP_EncodeMsgProc        VAR_EncodeMsg(ITS_Class V_Class);
SS7DLLAPI __ISUP_ComputeMSizeProc     VAR_ComputeMsize(ITS_Class V_Class);
SS7DLLAPI __ISUP_HandleUnrecMsgProc   VAR_HandleUnrecMsg(ITS_Class V_Class);   
SS7DLLAPI __ISUP_HandleUnrecParamProc VAR_HandleUnrecParam(ITS_Class V_Class);   
SS7DLLAPI void                        VAR_PrintRecord(ITS_Class V_Class);

#if defined(__cplusplus)
}
#endif

#endif /* ISUP_VARIANTS_H */
