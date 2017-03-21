/****************************************************************************
 *                                                                          *
 *     Copyright 2001 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: isup_data.c,v 1.1.1.1 2007-10-08 11:12:14 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.3  2007/09/13 09:19:32  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:07  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/04/06 10:53:03  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/05 11:27:21  sjaddu
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.20  2005/03/21 13:53:41  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.13.2.5.2.1.12.2  2005/02/25 06:30:59  ssingh
 * LOG: ISUP_DEST_PEGS destination specific pegs related changes.
 * LOG:
 * LOG: Revision 7.13.2.5.2.1.12.1  2004/12/17 03:57:43  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.13.2.5.2.1.6.1  2004/10/25 20:34:11  randresol
 * LOG: Start Japan SS7 Implementation
 * LOG:
 * LOG: Revision 7.13.2.5.2.1  2004/01/05 10:04:50  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG:
 * LOG: Revision 7.13.2.4.2.5  2003/11/24 06:32:32  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.13.2.4.2.4  2003/10/27 08:37:44  akumar
 * LOG: Introduced msg based pegs.
 * LOG:
 * LOG: Revision 7.13.2.4.2.3  2003/10/08 07:41:12  akumar
 * LOG: Vcic in DSM.
 * LOG:
 * LOG: Revision 7.13.2.4.2.2  2003/09/11 06:28:42  akumar
 * LOG: Compiler error resolved.
 * LOG:
 * LOG: Revision 7.13.2.4.2.1  2003/09/05 09:38:34  akumar
 * LOG: Message Based redundancy modifications.
 * LOG:
 * LOG: Revision 7.13.2.4  2003/05/07 10:21:54  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3
 * LOG:
 * LOG: Revision 8.15  2003/05/02 14:26:57  ssingh
 * LOG: ANSI to ITU propagation.
 * LOG:
 * LOG: Revision 8.14  2003/04/25 14:04:29  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.13  2003/04/24 06:32:32  ssingh
 * LOG: BUG# 315; Changed ISUP_AllocLocalTable function.
 * LOG:
 * LOG: Revision 8.12  2003/04/22 07:17:36  akumar
 * LOG: Front port PR_6.3 to Current Branch (Mainly MML)
 * LOG:
 * LOG: Revision 8.11  2003/04/18 07:15:54  sjaddu
 * LOG: DSM Initilization issue, Lock STAT Table.
 * LOG:
 * LOG: Revision 8.10  2003/04/16 07:15:32  akumar
 * LOG: Build Error-Fix.
 * LOG:
 * LOG: Revision 8.9  2003/04/16 06:01:39  akumar
 * LOG: Congestion Related Changes.
 * LOG:
 * LOG: Revision 8.8  2003/04/14 10:22:07  sjaddu
 * LOG: Add destination on fly changes and few bug fixes.
 * LOG:
 * LOG: Revision 8.7  2003/04/10 06:46:49  ssingh
 * LOG: Message Proirity (EF bits of SIO) related changes done.
 * LOG:
 * LOG: Revision 8.6  2003/04/07 21:07:20  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.5  2003/04/04 06:40:52  ssingh
 * LOG: Changes in InitCic/UnreserveCIC.
 * LOG:
 * LOG: Revision 8.4  2003/04/03 15:17:51  sjaddu
 * LOG: ISUP DSM Reorganization.
 * LOG:
 * LOG: Revision 8.3  2003/03/26 12:11:20  ssingh
 * LOG: Changed done as per ISUPPending List:
 * LOG: ansi-isup_alarms.c  : New Alarms added for HandleMTP3MgmtMsg.
 * LOG: ansi-isup_context.c : Function calls for DPC and Remote ISUP status.
 * LOG:                     : Indication sent; if msg received is on BAD Cic.
 * LOG:                     : Alarms for PAUSE/RESUME/STATUS.
 * LOG: ansi-isup_ifc.c     : Changes to incorporate CIC_INFO changes.
 * LOG: ansi-sprc.c         : CIC_INFO/CIC_MSG_INFO related changes.
 * LOG:                     : SendConfToApp removed, SendIsupIndToApp added.
 * LOG: isup_data.c         : Modified to include CIC_INFO/CIC_MSG_INFO changes.
 * LOG: its-ansi-isup.c     : CIC_INFO related changes.
 * LOG:
 * LOG: Revision 8.2  2003/02/17 06:40:40  akumar
 * LOG: Modified for new vars
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:23  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.13  2003/02/05 00:49:17  sjaddu
 * LOG: Cic Reserve changes.
 * LOG:
 * LOG: Revision 7.12  2003/01/30 13:06:11  ssingh
 * LOG: Added ANSI-ISUP alarms for ISUP Initialize/Terminate/Abort.
 * LOG: Changed CIC Initialization for ANSI. Now initialized as LBLOCKED.
 * LOG:
 * LOG: Revision 7.11  2003/01/21 15:34:18  vnitin
 * LOG: Tandem Port for ISUP, mostly type casting
 * LOG:
 * LOG: Revision 7.10  2003/01/17 15:29:55  sjaddu
 * LOG: vcic changes.
 * LOG:
 * LOG: Revision 7.9  2003/01/14 00:35:01  sjaddu
 * LOG: Cic rule changes for this file.
 * LOG:
 * LOG: Revision 7.8  2003/01/10 23:26:58  sjaddu
 * LOG: ckgp_list and DSM_Q changes.
 * LOG:
 * LOG: Revision 7.7  2002/12/31 06:20:04  akumar
 * LOG: Modified for Segmentation Procedure, initialization done
 * LOG:
 * LOG: Revision 7.6  2002/12/09 10:34:09  ssingh
 * LOG: Changed UPU handleing in case of Remote ISUP UNEQUIPPED.
 * LOG:
 * LOG: Revision 7.5  2002/11/22 15:04:17  ssingh
 * LOG: Added code in UpdateOpcDpc to drop Memory Leaks.
 * LOG:
 * LOG: Revision 7.4  2002/11/22 10:10:40  sjaddu
 * LOG: Fixed memory leak in CopyOpcDpc().
 * LOG:
 * LOG: Revision 7.3  2002/11/19 12:57:28  sjaddu
 * LOG: Added MML changes.
 * LOG:
 * LOG: Revision 7.2  2002/10/21 12:26:09  ssingh
 * LOG: Addec functions to support <-CQR- for ANSI.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:28  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.11  2002/08/21 15:14:30  sjaddu
 * LOG: ANSI redundancy.
 * LOG:
 * LOG: Revision 6.10  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.9  2002/08/01 15:57:47  ssharma
 * LOG: Merge from ISUP_PR7 branch.
 * LOG:
 * LOG: Revision 6.8  2002/07/03 20:19:18  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 6.7  2002/07/01 21:51:10  mmiers
 * LOG: Vframe changes to support ISUP.  Warning removal
 * LOG:
 * LOG: Revision 6.6.2.9  2002/07/31 22:26:06  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.6.2.8  2002/07/31 16:12:24  ssharma
 * LOG: Performance improvements.
 * LOG:
 * LOG: Revision 6.6.2.7  2002/07/19 19:13:01  ssingh
 * LOG: Modified inital states of BLS and BLR for ANSI.
 * LOG:
 * LOG: Revision 6.6.2.6  2002/07/12 21:50:56  hbalimid
 * LOG: Harware Blocking made specific to CCITT.
 * LOG:
 * LOG: Revision 6.6.2.5  2002/07/10 20:18:46  ssharma
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 6.6.2.4  2002/07/10 19:39:46  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.6.2.3  2002/07/06 18:39:34  hbalimid
 * LOG: CVTR for ANSI in place.
 * LOG:
 * LOG: Revision 6.6.2.2  2002/07/06 06:32:39  hbalimid
 * LOG: Removed unused variables.
 * LOG:
 * LOG: Revision 6.6.2.1  2002/07/05 21:59:31  hbalimid
 * LOG: ANSI CVT states taken care of.
 * LOG:
 * LOG: Revision 6.6  2002/06/28 19:05:57  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 21:46:57  mmiers
 * LOG: Add snames.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 16:18:58  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10.2.12  2002/05/14 18:14:44  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 5.10.2.11  2002/04/03 18:10:55  ssharma
 * LOG: Fix memory leaks.
 * LOG:
 * LOG: Revision 5.10.2.10  2002/04/02 23:53:54  ssharma
 * LOG: Completion of phase 2, coding standards conformance.
 * LOG:
 * LOG: Revision 5.10.2.9  2002/04/01 22:01:01  ssharma
 * LOG: Fix bug in ISUP_AllocCic.
 * LOG:
 * LOG: Revision 5.10.2.8  2002/04/01 21:08:02  ssharma
 * LOG: Fix memory leaks in ISUP_FindXX() functions.
 * LOG:
 * LOG: Revision 5.10.2.7  2002/03/28 20:21:07  ssharma
 * LOG: Add CSC file, Reorganize code to separate CSC code to a file.
 * LOG:
 * LOG: Revision 5.10.2.6  2002/03/22 16:20:06  ssharma
 * LOG: Change assert to ITS_C_ASSERT
 * LOG:
 * LOG: Revision 5.10.2.5  2002/03/19 17:23:30  ssharma
 * LOG: Init of maintenance states.
 * LOG:
 * LOG: Revision 5.10.2.4  2002/03/14 15:31:05  ssharma
 * LOG: Change signature of Validate_RangeStatus, add CSC state machines.
 * LOG:
 * LOG: Revision 5.10.2.3  2002/03/07 20:15:23  ssharma
 * LOG: Add code to initialize BLS/BLR flags, new functions in SPRC.
 * LOG:
 * LOG: Revision 5.10.2.2  2002/03/04 20:25:04  ssharma
 * LOG: Change printf to ISUP_DEBUG.
 * LOG:
 * LOG: Revision 5.10.2.1  2002/03/04 17:37:00  ssharma
 * LOG: Initialize the mtp3 header structure.
 * LOG:
 * LOG: Revision 5.10  2002/02/26 16:41:20  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.9  2002/02/20 21:24:00  mmiers
 * LOG: Don't include engine.h
 * LOG:
 * LOG: Revision 5.8  2002/02/15 23:22:28  ssharma
 * LOG: Integration bug fixes.
 * LOG:
 * LOG: Revision 5.7  2002/02/14 17:09:51  mmiers
 * LOG: Arg order was wrong.
 * LOG:
 * LOG: Revision 5.6  2002/02/14 17:03:59  mmiers
 * LOG: Signature bugs.
 * LOG:
 * LOG: Revision 5.5  2002/02/13 22:45:23  mmiers
 * LOG: Warning removal
 * LOG:
 * LOG: Revision 5.4  2002/02/12 23:29:04  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 5.3  2002/02/08 21:48:16  mmiers
 * LOG: Reorg complete.
 * LOG:
 * LOG: Revision 5.2  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 5.1  2002/02/01 20:07:30  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 1.1.2.3  2002/01/25 22:17:07  yranade
 * LOG: Fix build problems.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/01/25 18:17:34  yranade
 * LOG: Include the right isup.h based on protocol family.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/01/22 23:37:11  ssharma
 * LOG: New files for IntelliNet ISUP stack.
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#if defined(PRC)
#include <china/isup.h>
#elif defined (TTC)
#include <japan/isup.h>
#elif defined (CCITT)
#include <itu/isup.h>
#elif defined (ANSI)
#include <ansi/isup.h>
#endif
#include <its_hash.h>
#include <its_mutex.h>
#include <its_mem_pool.h>
#include <its_assertion.h>
#include <its_dsm.h>
#include <its_dsmqueue.h>

#include "isup_intern.h"

#if defined (CCITT)
#define DSM_TABLE_ISUP_OPC_DPC DSM_TABLE_ITU_ISUP_OPC_DPC
#elif defined (ANSI)
#define DSM_TABLE_ISUP_OPC_DPC DSM_TABLE_ANSI_ISUP_OPC_DPC
#endif

#if defined (CCITT)
#define DSM_TABLE_ISUP_PCIC DSM_TABLE_ITU_ISUP_PCIC
#elif defined (ANSI)
#define DSM_TABLE_ISUP_PCIC DSM_TABLE_ANSI_ISUP_PCIC
#endif

#if defined (CCITT)
#define DSM_TABLE_ISUP_PCIC_CSC_MSG DSM_TABLE_ITU_ISUP_PCIC_CSC_MSG
#elif defined (ANSI)
#define DSM_TABLE_ISUP_PCIC_CSC_MSG DSM_TABLE_ANSI_ISUP_PCIC_CSC_MSG
#endif

#if defined (CCITT)
#define DSM_TABLE_ISUP_CKGP_LIST DSM_TABLE_ITU_ISUP_CKGP_LIST
#elif defined (ANSI)
#define DSM_TABLE_ISUP_CKGP_LIST DSM_TABLE_ANSI_ISUP_CKGP_LIST
#endif

#if defined (CCITT)
#define DSM_TABLE_ISUP_VCIC DSM_TABLE_ITU_ISUP_VCIC
#elif defined (ANSI)
#define DSM_TABLE_ISUP_VCIC DSM_TABLE_ANSI_ISUP_VCIC
#endif

/*
 * global data
 */
static HASH_Table      __ISUP_data = NULL;
static ITS_MUTEX       __ISUP_hashGate;

static HASH_Table      __ISUP_dpctransp = NULL;
static ITS_MUTEX       __ISUP_dpclock;

/*
 * local data
 */
static ITS_BOOLEAN  initialized = ITS_FALSE;
static ITS_BOOLEAN  terminated = ITS_FALSE;

/* This will be used as a key to access Vcic Table */
static ITS_OCTET isup_vcic_key = 5;

char* ISUP_Peg_Desc[] =
{
    "PEG_ISUP_STRT_LCL_UNAV_FAIL",   /*10.1*/
    "PEG_ISUP_STRT_LCL_UNAV_MAINT",  /*10.2*/
    "PEG_ISUP_AVAILABLE",            /*10.3*/
    "PEG_ISUP_TOT_DUR_UNAVAIL",      /*10.4*/
    "PEG_ISUP_STRT_LCL_CONGES",      /*10.5*/
    "PEG_ISUP_STOP_LCL_CONGES",      /*10.6*/
    "PEG_ISUP_DUR_LCL_CONGES",       /*10.7*/
    "PEG_ISUP_TOT_MSGS_SENT",        /*11.1*/
    "PEG_ISUP_TOT_MSGS_RCVD",        /*11.2*/
    "PEG_ISUP_NUM_PEGS"
};

char *ISUP_Dest_Peg_Desc[] =
{
    "PEG_ISUP_DEST_REM_AVAIL",
    "PEG_ISUP_DEST_REM_UNAVAIL",
    "PEG_ISUP_DEST_REM_CONGES",
    "PEG_ISUP_DEST_REM_CONGES_SEIZED",
    "PEG_ISUP_DEST_PAUSE",
    "PEG_ISUP_DEST_RESUME"
};

char *ISUP_CIC_Peg_Desc[] =
{
    "PEG_ISUP_CIC_NO_ACK_RSC_T17",    /*12.1*/
    "PEG_ISUP_CIC_NO_GRA_T23",        /*12.2*/
    "PEG_ISUP_CIC_NO_RLC_T5",         /*12.5*/
    "PEG_ISUP_CIC_REL_ABNORMAL",      /*12.6*/
    "PEG_ISUP_CIC_BLO_CRC_ERR",             /*12.7*/
    "PEG_ISUP_CIC_MISSING_ACK_IN_CGBA",     /*12.8*/
    "PEG_ISUP_CIC_MISSING_ACK_IN_CGUA",     /*12.9*/
    "PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGBA",    /*12.10*/
    "PEG_ISUP_CIC_ABNORMAL_ACK_IN_CGUA",    /*12.11*/
    "PEG_ISUP_CIC_UNEXP_CGBA_ABNORMAL_ACK", /*12.12*/
    "PEG_ISUP_CIC_UNEXP_CGUA_ABNORMAL_ACK", /*12.13*/
    "PEG_ISUP_CIC_UNEXP_BLA_ABNORMAL_ACK",  /*12.14*/
    "PEG_ISUP_CIC_UNEXP_UBA_ABNORMAL_ACK",  /*12.15*/
    "PEG_ISUP_CIC_NO_BLA_T13",        /*12.16*/
    "PEG_ISUP_CIC_NO_UBA_T15",        /*12.17*/
    "PEG_ISUP_CIC_NO_CGBA_T19",       /*12.18*/
    "PEG_ISUP_CIC_NO_CGUA_T21",       /*12.19*/
    "PEG_ISUP_CIC_MSG_FORMAT_ERR",    /*12.20*/
    "PEG_ISUP_CIC_UNEXP_MSG_RCVD",    /*12.21*/
    "PEG_ISUP_CIC_REL_UNRECOG_INFO",  /*12.22*/
    "PEG_ISUP_CIC_UNABLE_RELEASE_CKT",  /*12.23*/
    "PEG_ISUP_CIC_NUM_PEGS"
};

char *ISUP_Msg_Pegs_Sent_Desc[] =
{
    "PEG_ISUP_IAM_SENT_TO_REMOTE",
    "PEG_ISUP_ACM_SENT_TO_REMOTE",
    "PEG_ISUP_ANM_SENT_TO_REMOTE",
    "PEG_ISUP_REL_SENT_TO_REMOTE",
    "PEG_ISUP_RLC_SENT_TO_REMOTE",
    "PEG_ISUP_BLO_SENT_TO_REMOTE",
    "PEG_ISUP_UBL_SENT_TO_REMOTE",
    "PEG_ISUP_BLA_SENT_TO_REMOTE",
    "PEG_ISUP_CPG_SENT_TO_REMOTE",
    "PEG_ISUP_CGB_SENT_TO_REMOTE",
    "PEG_ISUP_CGBA_SENT_TO_REMOTE",
    "PEG_ISUP_CQM_SENT_TO_REMOTE",
    "PEG_ISUP_CQR_SENT_TO_REMOTE",
    "PEG_ISUP_GRS_SENT_TO_REMOTE",
    "PEG_ISUP_GRA_SENT_TO_REMOTE",
    "PEG_ISUP_CGU_SENT_TO_REMOTE",
    "PEG_ISUP_CGUA_SENT_TO_REMOTE",
    "PEG_ISUP_CRG_SENT_TO_REMOTE",
    "PEG_ISUP_CFN_SENT_TO_REMOTE",
    "PEG_ISUP_COT_SENT_TO_REMOTE",
    "PEG_ISUP_CCR_SENT_TO_REMOTE",
    "PEG_ISUP_FOT_SENT_TO_REMOTE",
    "PEG_ISUP_INF_SENT_TO_REMOTE",
    "PEG_ISUP_INR_SENT_TO_REMOTE",
    "PEG_ISUP_LPA_SENT_TO_REMOTE",
    "PEG_ISUP_PAM_SENT_TO_REMOTE",
    "PEG_ISUP_RSC_SENT_TO_REMOTE",
    "PEG_ISUP_RES_SENT_TO_REMOTE",
    "PEG_ISUP_SUS_SENT_TO_REMOTE",
    "PEG_ISUP_UBA_SENT_TO_REMOTE",
    "PEG_ISUP_UCIC_SENT_TO_REMOTE",
#if defined (ANSI)
    "PEG_ISUP_CRM_SENT_TO_REMOTE",
    "PEG_ISUP_CRA_SENT_TO_REMOTE",
    "PEG_ISUP_CVR_SENT_TO_REMOTE",
    "PEG_ISUP_CVT_SENT_TO_REMOTE",
    "PEG_ISUP_EXM_SENT_TO_REMOTE",
    "PEG_ISUP_FAC_SENT_TO_REMOTE",
#endif
#if defined (CCITT) || defined (PRC) ||  defined(TTC)
    "PEG_ISUP_IDR_SENT_TO_REMOTE",
    "PEG_ISUP_IRS_SENT_TO_REMOTE",
    "PEG_ISUP_FAA_SENT_TO_REMOTE",
    "PEG_ISUP_CON_SENT_TO_REMOTE",
    "PEG_ISUP_FRJ_SENT_TO_REMOTE",
    "PEG_ISUP_FAC_SENT_TO_REMOTE",
    "PEG_ISUP_FAR_SENT_TO_REMOTE",
    "PEG_ISUP_NRM_SENT_TO_REMOTE",
    "PEG_ISUP_OLM_SENT_TO_REMOTE",
    "PEG_ISUP_SAM_SENT_TO_REMOTE",
    "PEG_ISUP_SGM_SENT_TO_REMOTE",
    "PEG_ISUP_UPA_SENT_TO_REMOTE",
    "PEG_ISUP_UPT_SENT_TO_REMOTE",
    "PEG_ISUP_USR_SENT_TO_REMOTE",
    "PEG_ISUP_LOP_SENT_TO_REMOTE",
#endif
    "ISUP_MAX_MSG_CODE",
     NULL
};

char * ISUP_Msg_Pegs_Rcvd_Desc[] =
{
    "PEG_ISUP_REMOTE_IAM_RCVD",
    "PEG_ISUP_REMOTE_ACM_RCVD",
    "PEG_ISUP_REMOTE_ANM_RCVD",
    "PEG_ISUP_REMOTE_REL_RCVD",
    "PEG_ISUP_REMOTE_RLC_RCVD",
    "PEG_ISUP_REMOTE_BLO_RCVD",
    "PEG_ISUP_REMOTE_UBL_RCVD",
    "PEG_ISUP_REMOTE_BLA_RCVD",
    "PEG_ISUP_REMOTE_CPG_RCVD",
    "PEG_ISUP_REMOTE_CGB_RCVD",
    "PEG_ISUP_REMOTE_CGBA_RCVD",
    "PEG_ISUP_REMOTE_CQM_RCVD",
    "PEG_ISUP_REMOTE_CQR_RCVD",
    "PEG_ISUP_REMOTE_GRS_RCVD",
    "PEG_ISUP_REMOTE_GRA_RCVD",
    "PEG_ISUP_REMOTE_CGU_RCVD",
    "PEG_ISUP_REMOTE_CGUA_RCVD",
    "PEG_ISUP_REMOTE_CRG_RCVD",
    "PEG_ISUP_REMOTE_CFN_RCVD",
    "PEG_ISUP_REMOTE_COT_RCVD",
    "PEG_ISUP_REMOTE_CCR_RCVD",
    "PEG_ISUP_REMOTE_FOT_RCVD",
    "PEG_ISUP_REMOTE_INF_RCVD",
    "PEG_ISUP_REMOTE_INR_RCVD",
    "PEG_ISUP_REMOTE_LPA_RCVD",
    "PEG_ISUP_REMOTE_PAM_RCVD",
    "PEG_ISUP_REMOTE_RSC_RCVD",
    "PEG_ISUP_REMOTE_RES_RCVD",
    "PEG_ISUP_REMOTE_SUS_RCVD",
    "PEG_ISUP_REMOTE_UBA_RCVD",
    "PEG_ISUP_REMOTE_UCIC_RCVD",
#if defined (ANSI)
    "PEG_ISUP_REMOTE_CRM_RCVD",
    "PEG_ISUP_REMOTE_CRA_RCVD",
    "PEG_ISUP_REMOTE_CVR_RCVD",
    "PEG_ISUP_REMOTE_CVT_RCVD",
    "PEG_ISUP_REMOTE_EXM_RCVD",
    "PEG_ISUP_REMOTE_FAC_RCVD",
#endif
#if defined(CCITT) || defined (PRC) ||  defined(TTC)
    "PEG_ISUP_REMOTE_IDR_RCVD",
    "PEG_ISUP_REMOTE_IRS_RCVD",
    "PEG_ISUP_REMOTE_FAA_RCVD",
    "PEG_ISUP_REMOTE_CON_RCVD",
    "PEG_ISUP_REMOTE_FRJ_RCVD",
    "PEG_ISUP_REMOTE_FAC_RCVD",
    "PEG_ISUP_REMOTE_FAR_RCVD",
    "PEG_ISUP_REMOTE_NRM_RCVD",
    "PEG_ISUP_REMOTE_OLM_RCVD",
    "PEG_ISUP_REMOTE_SAM_RCVD",
    "PEG_ISUP_REMOTE_SGM_RCVD",
    "PEG_ISUP_REMOTE_UPA_RCVD",
    "PEG_ISUP_REMOTE_UPT_RCVD",
    "PEG_ISUP_REMOTE_USR_RCVD",
    "PEG_ISUP_REMOTE_LOP_RCVD",
#endif
    "ISUP_MAX_MSG_CODE",
    NULL
};

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      We need a decent little hash that's pretty good at eliminating
 *      duplicates.
 *
 *  Input Parameters:
 *      key - key data
 *      klen - key length
 *
 *  Return Value:
 *      hash value
 *
 *  Notes:
 *      if they use a lot of one byte keys they deserve the side effects.
 ****************************************************************************/
static ITS_INT
LocalHash(ITS_OCTET *key, ITS_UINT klen)
{
    ITS_INT ret = 131;
    ITS_UINT i;

    for (i = 0; i < klen; i++)
    {
        if (key[i])
        {
            ret *= (key[i] << 3) | 1;
        }
        else
        {
            ret *= ret;
        }
    }

    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function intializes the hash table and hash mutex.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      If the initialization is successful, ITS_SUCCESS is returned.
 *      Any other return value indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
int
__ISUP_Init_HashTables()
{
    int ret;

    if (initialized)
    {
        return (ITS_SUCCESS);
    }

    initialized = ITS_TRUE;

    if ((__ISUP_data = HASH_CreateTable()) == NULL)
    {
        ISUP_CRITICAL(("ISUP_Init_HashTables: hash create failed\n"));

        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ((ret = MUTEX_CreateMutex(&__ISUP_hashGate, 0)) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ISUP_Init_HashTables: mutex create failed\n"));

        HASH_DeleteTable(__ISUP_data);

        initialized = ITS_FALSE;

        return (ret);
    }

    if ((__ISUP_dpctransp = HASH_CreateTable()) == NULL)
    {
        ISUP_CRITICAL(("ISUP_Init_HashTables: hash create failed\n"));

        initialized = ITS_FALSE;

        return (ITS_ENOMEM);
    }

    if ((ret = MUTEX_CreateMutex(&__ISUP_dpclock, 0)) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ISUP_Init_HashTables: mutex create failed\n"));

        HASH_DeleteTable(__ISUP_dpctransp);

        initialized = ITS_FALSE;

        return (ret);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function deletes the hash table and hash mutex.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
void
__ISUP_Term_HashTables()
{
    if (!initialized || terminated)
    {
        return;
    }

    terminated = ITS_TRUE;

    HASH_DeleteTable(__ISUP_data);

    MUTEX_DeleteMutex(&__ISUP_hashGate);

    HASH_DeleteTable(__ISUP_dpctransp);

    MUTEX_DeleteMutex(&__ISUP_dpclock);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds a usable CIC to a group
 *
 *  Input Parameters:
 *      ckgp_info - circuit group info pointer.
 *      cic_index - index in the usable cic bit array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISUP_AddUsableCic(ISUP_OPC_DPC_STAT *opc_dpc_info,
                  ISUP_CKGP_INFO *ckgp_info, ITS_USHORT cic_index,
                  ITS_OCTET cicRule)
{
    int ret = ITS_SUCCESS;
    int byte, bit;
    const char *className = ISUP_VariantToString(opc_dpc_info->isup_var_type);

    /*
     * The usable_cics array is 4 bytes, with bit offsets going from 0
     * to 127 as shown below
     * 
     *      31    30    29  28  .........   3   2   1   0   <-- byte 0
     *      63    62    61  60              35  34  33  32  <-- byte 1
     *      95    94    93  92              67  66  65  64  <-- byte 2
     *      127   126   125  124            99  98  97  96  <-- byte 3
     */

    /*
     * from the offset, find which byte to which bit in that byte to set
     */
    
    if (cic_index > 31)
    {
        return !ITS_SUCCESS;
    }
    
    byte = cic_index / ISUP_CLASS_INFO(ITS_FindFeature(className))->CICsInCkgp;

    bit = cic_index % ISUP_CLASS_INFO(ITS_FindFeature(className))->CICsInCkgp;

    ISUP_SET_BIT(ckgp_info->usable_cics[byte], bit);
    ckgp_info->ckgp_control[cic_index] = cicRule;

    return ret;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function delete a usable CIC from a group
 *
 *  Input Parameters:
 *      ckgp_info - circuit group info pointer.
 *      cic_index - index in the usable cic bit array
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISUP_DelUsableCic(ISUP_OPC_DPC_STAT *opc_dpc_info,
                  ISUP_CKGP_INFO *ckgp_info, ITS_USHORT cic_index)
{
    int ret = ITS_SUCCESS;
    int byte, bit;
    const char *className = ISUP_VariantToString(opc_dpc_info->isup_var_type);

    /*
     * The usable_cics array is 4 bytes, with bit offsets going from 0
     * to 127 as shown below
     * 
     *      31    30    29  28  .........   3   2   1   0   <-- byte 0
     *      63    62    61  60              35  34  33  32  <-- byte 1
     *      95    94    93  92              67  66  65  64  <-- byte 2
     *      127   126   125  124            99  98  97  96  <-- byte 3
     */

    /*
     * from the offset, find which byte to which bit in that byte to set
     */
    
    if (cic_index > 31)
    {
        return !ITS_SUCCESS;
    }
    
    byte = cic_index /ISUP_CLASS_INFO(ITS_FindFeature(className))->CICsInCkgp;

    bit = cic_index % ISUP_CLASS_INFO(ITS_FindFeature(className))->CICsInCkgp;

    ISUP_UNSET_BIT(ckgp_info->usable_cics[byte], bit);

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function adds usable cics to a group
 *
 *  Input Parameters:
 *      ckgp_info - circuit group info pointer.
 *      cic_index - index in the usable cic bit array
 *      number_cics - number of cics to add
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
ISUP_AddUsableCics(ISUP_OPC_DPC_STAT *opc_dpc_info, ISUP_CKGP_INFO *ckgp_info,
                   ITS_USHORT cic_index, ITS_USHORT number_cics,
                   ITS_OCTET cicRule)
{
    ITS_USHORT i = 0;
    int ret = ITS_SUCCESS;

    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    /*
     * in a loop, set each bit to 1
     */
    
    for (i = 0; i < number_cics; i++, cic_index++)
    {
        ret = ISUP_AddUsableCic(opc_dpc_info,ckgp_info, cic_index, cicRule);

        if (ret != ITS_SUCCESS)
        {
            return ret;
        }
    }

    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function checks if Range of Cics are configured or not
 *
 *  Input Parameters:
 *      odInfo - opc dpc info pointer.
 *      cic - cic to be checked
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE or ITS_FALSE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_IsCicsExists(ISUP_OPC_DPC_STAT *odInfo, ITS_USHORT scic,
                      ITS_USHORT count)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;
    int i;
    ITS_USHORT gpid = 0;
    ITS_USHORT cicIndex = 0;
    ITS_USHORT numCics = 0;
    int byte, bit;
    const char * className =0;
    ITS_Class feature;

    className = ISUP_VariantToString(odInfo->isup_var_type);   
    feature = ITS_FindFeature(className);

    ckgp_list = ISUP_FindCkgpList(odInfo->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_FALSE;
    }
    for (i = 0; i < count; ++i)
    {
        VAR_GetCkgpFromCIC(feature, (ITS_USHORT)(scic +i),
                           &cicIndex, &gpid, &numCics);

        if (ckgp_list->ckgp_info[gpid].ckgp_id == ISUP_INV_CKGP_ID)
        {
            i += numCics;
            continue;
        }

        byte = cicIndex / ISUP_CLASS_INFO(feature)->CICsInCkgp;

        bit = cicIndex % ISUP_CLASS_INFO(feature)->CICsInCkgp;

        if (ISUP_GET_BIT(ckgp_list->ckgp_info[gpid].usable_cics[byte], bit))
        {
            ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
            return ITS_TRUE;
        }
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_FALSE;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function checks if Range of Cics are configured or not
 *
 *  Input Parameters:
 *      odInfo - opc dpc info pointer.
 *      cic - cic to be checked
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE or ITS_FALSE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_IsCicsNonExists(ISUP_OPC_DPC_STAT *odInfo, ITS_USHORT scic,
                      ITS_USHORT count)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;
    int i;
    ITS_USHORT gpid = 0;
    ITS_USHORT cicIndex = 0;
    ITS_USHORT numCics = 0;
    int byte, bit;
    const char * className =0;
    ITS_Class feature;

    className = ISUP_VariantToString(odInfo->isup_var_type);   
    feature = ITS_FindFeature(className);

    ckgp_list = ISUP_FindCkgpList(odInfo->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_TRUE;
    }
    for (i = 0; i < count; ++i)
    {
        VAR_GetCkgpFromCIC(feature, (ITS_USHORT)(scic +i),
                           &cicIndex, &gpid, &numCics);

        if (ckgp_list->ckgp_info[gpid].ckgp_id == ISUP_INV_CKGP_ID)
        {
            ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
            return ITS_TRUE;
        }

        if (cicIndex > 31)
        {
            ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
            return ITS_TRUE;
        }
        else
        {
            byte = cicIndex / ISUP_CLASS_INFO(feature)->CICsInCkgp;

            bit = cicIndex % ISUP_CLASS_INFO(feature)->CICsInCkgp;

            if (!ISUP_GET_BIT(ckgp_list->ckgp_info[gpid].usable_cics[byte], bit))
            {
                ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
                return ITS_TRUE;
            }
        }
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_FALSE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function checks if a cic is usable or not
 *
 *  Input Parameters:
 *      odInfo - opc dpc info pointer.
 *      cic - cic to be checked
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE or ITS_FALSE
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_IsCicUsable(ISUP_OPC_DPC_STAT *odInfo, ITS_USHORT cic)
{
    ITS_USHORT gpid = 0;
    ITS_USHORT cicIndex = 0;
    ITS_USHORT numCics = 0;
    ISUP_CKGP_INFO ckgp_info;
    ITS_BOOLEAN gpExists;
    int byte, bit;
    int ret;
    const char * className = ISUP_VariantToString(odInfo->isup_var_type);

    VAR_GetCkgpFromCIC(ITS_FindFeature(className), cic, &cicIndex,
                       &gpid, &numCics);

    /*
     * lookup the gpid in the odInfo group mlist
     */
    gpExists = ISUP_CkgpExists(odInfo, gpid);

    if (!gpExists)
    {
        return ITS_FALSE;
    }
    else
    {
        ret = ISUP_FindCkgpInfo(odInfo, gpid, &ckgp_info);

        if (ret != ITS_SUCCESS)
        {
            return ITS_FALSE;
        }

        if (cicIndex > 31)
        {
            return ITS_FALSE;
        }

        byte = cicIndex / ISUP_CLASS_INFO(
                                    ITS_FindFeature(className))->CICsInCkgp;

        bit = cicIndex % ISUP_CLASS_INFO(
                                    ITS_FindFeature(className))->CICsInCkgp;

        if (ISUP_GET_BIT(ckgp_info.usable_cics[byte], bit))
        {
            return ITS_TRUE;
        }
        else
        {
            return ITS_FALSE;
        }
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a circuit group matching an id in the list 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *      ckgp_id - circuit group id to search
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to circuit group structure for success case.
 *      NULL for failure.
 ****************************************************************************/
int 
ISUP_FindCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info, ITS_USHORT ckgp_id,
                  ISUP_CKGP_INFO* l_ckgp_info)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;

    if (opc_dpc_info == NULL)
    {
        return ITS_FALSE;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_ENOTFOUND;
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        memcpy(l_ckgp_info, &ckgp_list->ckgp_info[ckgp_id],
               sizeof(ISUP_CKGP_INFO));
        return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_ENOTFOUND;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check if a circuit group exists in the list 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *      ckgp_id - circuit group id to search
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if id exists.
 *      ITS_FALSE otherwise.
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_CkgpExists(ISUP_OPC_DPC_STAT *opc_dpc_info, ITS_USHORT ckgp_id)
{
    ISUP_CKGP_LIST *ckgp_list;

    if (opc_dpc_info == NULL)
    {
        return ITS_FALSE;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if ( ckgp_list == NULL)
    {
        return ITS_FALSE;
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
        return ITS_TRUE;
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_FALSE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Decide whether to insert an entry at a particular place in the circuit
 *      group list. (used internally by the List Insert function)
 *
 *  Input Parameters:
 *      prev - prev list entry
 *      next - next list entry
 *      item - list entry to be inserted
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      1 if item should be inserted between prev and next.
 *      0 otherwise.
 ****************************************************************************/
int 
ISUP_CkgpInsFunc(LIST_Entry *prev, LIST_Entry *next, LIST_Entry *item)
{
    ISUP_CKGP_INFO *ckgp_prev;    
    ISUP_CKGP_INFO *ckgp_next;    
    ISUP_CKGP_INFO *ckgp_item;

    if (item == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    ckgp_item = (ISUP_CKGP_INFO *)(item->data);
    
    if ((prev == NULL) && (next == NULL))
    {
        /*
         * the list is empty, so insert it at the beginning
         */
        return !ITS_SUCCESS;
    }

    if ((prev != NULL) && (next == NULL))
    {
        /*
         * this is end of the list so insert here
         */
        return !ITS_SUCCESS;
    }

    if ((prev == NULL) && (next != NULL))
    {
        /*
         * this is first element of the list
         */
        ckgp_next = (ISUP_CKGP_INFO *)(next->data);    

        if (ckgp_item->ckgp_id <= ckgp_next->ckgp_id)
        {
            return !ITS_SUCCESS;
        }
        else
        {
            return ITS_SUCCESS;
        }
    }

    if ((prev != NULL) && (next != NULL))
    {
        /*
         * this is in middle of the list
         */
        ckgp_prev = (ISUP_CKGP_INFO *)(prev->data);    
        ckgp_next = (ISUP_CKGP_INFO *)(next->data);    

        if ((ckgp_item->ckgp_id >= ckgp_prev->ckgp_id) && 
            (ckgp_item->ckgp_id <= ckgp_next->ckgp_id))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /*
     * should not be reached
     */
    return 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert circuit group information in the list 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc info pointer
 *      ckgp_info - circuit group info
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_InsertCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info, ISUP_CKGP_INFO *ckgp_info)
{
    ISUP_CKGP_LIST *ckgp_list;

    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    if (ISUP_CkgpExists(opc_dpc_info, ckgp_info->ckgp_id))
    {
        ISUP_DEBUG(("Insert: ckgp exists - gpid %d\n", ckgp_info->ckgp_id));
        return ITS_ENOMSG;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        ckgp_list = ISUP_AllocCkgpList(opc_dpc_info->opc_dpc_ni);
        if (ckgp_list == NULL)
        {
            return ITS_ENOMEM;
        }
    }
    
    memcpy(&ckgp_list->ckgp_info[ckgp_info->ckgp_id],
           ckgp_info, sizeof(ISUP_CKGP_INFO));

    ++ckgp_list->noCkgps;

    ISUP_DEBUG((" ckgpinsert:- gpid %d.\n", ckgp_info->ckgp_id));
    return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To return if the circuit group id of current item matches the id to
 *      matched. It is used internally by the Remove function.
 *
 *  Input Parameters:
 *      item - current item in list
 *      match - data to be matched
 *      mlen - length of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      1 for a match.
 *      0 otherwise.
 ****************************************************************************/
int
ISUP_CkgpRemFunc(LIST_Entry *item, void *match, int mlen)
{
    ITS_USHORT ckgp_id;
    ISUP_CKGP_INFO *ckgp;
    
    if (item == NULL || match == NULL || mlen != sizeof(ITS_USHORT))
    {
        return !ITS_SUCCESS;
    }
    ckgp = (ISUP_CKGP_INFO *)(item->data);

    ckgp_id = *((ITS_USHORT *)match);

    if (ckgp_id == ckgp->ckgp_id)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete circuit group information for a opc dpc pair 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *      ckgp_id - circuit group id o be deleted
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_DeleteCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info, ITS_USHORT ckgp_id)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;

    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ISUP_INV_CKGP_ID)
    {
        ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
        return ITS_ENOTCONFIG;
    }
    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        ckgp_list->ckgp_info[ckgp_id].ckgp_id = ISUP_INV_CKGP_ID;

        --ckgp_list->noCkgps;
    }
    return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update circuit group information for a group id 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *      ckgp_id - id to be updated
 *      l_ckgp_info - structure with new values
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_UpdateCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info, ITS_USHORT ckgp_id, 
                    ISUP_CKGP_INFO *l_ckgp_info)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;

    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        if ((l_ckgp_info->usable_cics[0] & 0xFFFFFFFF) == 0x00000000)
        {
            l_ckgp_info->ckgp_id = ISUP_INV_CKGP_ID;
        }

        memcpy(&ckgp_list->ckgp_info[ckgp_id], l_ckgp_info,
               sizeof(ISUP_CKGP_INFO));
        return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_ENOMSG;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check if group list is empty 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if list is empty.
 *      ITS_FALSE if list if not empty.
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_IsCkgpInfoEmpty(ISUP_OPC_DPC_STAT *opc_dpc_info)
{

    ISUP_CKGP_LIST *ckgp_list = NULL;
    ITS_BOOLEAN bool;

    if (opc_dpc_info == NULL)
    {
        return ITS_SUCCESS;
    }
    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_FALSE;
    }
    bool =  (ckgp_list->noCkgps == 0 ? ITS_TRUE : ITS_FALSE);
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return bool;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find number of entries in group list 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_NumCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info)
{
    ISUP_CKGP_LIST *ckgp_list;
    int count;

    if (opc_dpc_info != NULL)
        return ITS_ENOTCONFIG;

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_ENOTCONFIG;
    }
    else
    {
        count = (ITS_INT)ckgp_list->noCkgps;
        ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
        return count;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete all circuit groups for an opc dpc pair 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure
 ****************************************************************************/
int
ISUP_DeleteAllCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info)
{
    ISUP_CKGP_LIST *ckgp_list;
    int i;

    if (opc_dpc_info == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return ITS_ENOTCONFIG;
    }

    for (i = 0; i < ISUP_MAX_CKGPS; ++i)
    {
        ckgp_list->ckgp_info[i].ckgp_id = ISUP_INV_CKGP_ID;
    }

    ckgp_list->noCkgps = 0;
    
    return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy Circuit group structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int
ISUP_CopyCkgp(ISUP_CKGP_INFO *dest, ISUP_CKGP_INFO *src)
{
    int i = 0;

    for (i = 0; i < MAX_CICS_PER_CKGP; i++)
    {
        dest->ckgp_control[i] = src->ckgp_control[i];
    }

    dest->ckgp_id = src->ckgp_id;
    memcpy(dest->usable_cics, src->usable_cics, sizeof(ITS_UINT));

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize a circuit group structure 
 *
 *  Input Parameters:
 *      ckgp - pointer to structure
 *      cktGpId - ckt group id
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void 
ISUP_InitCkgp(ISUP_CKGP_INFO *ckgp, ITS_USHORT cktGpId)
{
    int i = 0;
    for (i = 0; i < MAX_CICS_PER_CKGP; i++)
    {
        ckgp->ckgp_control[i] = ISUP_CKGP_CTRL_DEF;
    }
    ckgp->ckgp_id = cktGpId;
    memset(ckgp->usable_cics, 0, sizeof(ITS_UINT));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy Circuit group structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
void
ISUP_PrintCkgp(ISUP_CKGP_INFO *ckgp)
{
    int i = 0;

    for (i = 0; i < MAX_CICS_PER_CKGP; i++) 
    {
        ISUP_DEBUG(("Circuit group control = %d ", ckgp->ckgp_control[i]));
    }
    ISUP_DEBUG(("Circuit group id = %d \n", ckgp->ckgp_id));
    ISUP_DEBUG(("Circuit group usable cics = 0x%0x \n", 
                            ckgp->usable_cics[0]));
    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print all circuit groups for an opc dpc pair 
 *
 *  Input Parameters:
 *      opc_dpc_info - opc dpc structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 ****************************************************************************/
void
ISUP_PrintAllCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info)
{
    ISUP_CKGP_LIST *ckgp_list;
    ITS_INT count;

    if (opc_dpc_info == NULL)
    {
        return;
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        return;
    }

    for (count =0; count < ISUP_MAX_CKGPS; ++count)
    {
        if (ckgp_list->ckgp_info[count].ckgp_id == ISUP_INV_CKGP_ID)
        {
            continue;
        }
        ISUP_PrintCkgp(&ckgp_list->ckgp_info[count]);
    }
    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize Opc Dpc structure with initial default values 
 *
 *  Input Parameters:
 *      od_info - pointer to structure
 *      opcid_dpcid - Octet containing opcid+dpcid.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_InitOpcDpc(ISUP_OPC_DPC_INFO *od_info,
                MTP3_HEADER opc_dpc_ni,
                ISUP_VAR_TYPE variant_type)
{
    ITS_UINT lpc;
    ITS_UINT rpc;
    ITS_OCTET ni;
    ISUP_TMR_HNDL_INFO *tmr_hndl;
    const char *className = ISUP_VariantToString(variant_type);
    int i;

    od_info->opc_dpc_ni     = opc_dpc_ni;
    od_info->isup_var_type  = variant_type;
    od_info->isup_var_class = ITS_FindFeature(className);  
    od_info->syncTime       = TIMERS_Time();

    /* 
     * Setting in_hdr and out_hdr 
     */
    tmr_hndl = VAR_GetTimerInfo(ITS_FindFeature(className));

    for (i = 1; i < ISUP_MAX_TMRS; i++)
    {
        od_info->tmr_hndl_info[i].tmr_hndl_layer =
                                  tmr_hndl[i-1].tmr_hndl_layer;

        od_info->tmr_hndl_info[i].tmr_value = tmr_hndl[i-1].tmr_value;
    }

    /* Message pegs are initialised here:Sent pegs */
    for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
    {
        od_info->pegs_msg_sent[i] = 0;
    }

    od_info->ISUP_PEGS_SENT.name = "ISUP";
    od_info->ISUP_PEGS_SENT.numPegs =
        sizeof(od_info->pegs_msg_sent) / sizeof(ITS_UINT);
    od_info->ISUP_PEGS_SENT.pegs = od_info->pegs_msg_sent;

    /*Message pegs are initialised here:Rcvd Pegs */
    for (i = 0; i < ISUP_MAX_MSG_CODE; i++)
    {
        od_info->pegs_msg_rcvd[i] = 0;
    }

    od_info->ISUP_PEGS_RCVD.name = "ISUP";
    od_info->ISUP_PEGS_RCVD.numPegs =
        sizeof(od_info->pegs_msg_rcvd) / sizeof(ITS_UINT);
    od_info->ISUP_PEGS_RCVD.pegs = od_info->pegs_msg_rcvd;

    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
        od_info->pegs[i] = 0;
    }
    od_info->ISUP_DEST_PEGS.name = "ISUP";
    od_info->ISUP_DEST_PEGS.numPegs = sizeof(od_info->pegs) / sizeof(ITS_UINT);
    od_info->ISUP_DEST_PEGS.pegs = od_info->pegs;

    memset(&od_info->in_hdr, 0, sizeof(MTP3_HEADER));
    memset(&od_info->out_hdr, 0, sizeof(MTP3_HEADER));

    lpc = MTP3_RL_GET_OPC_VALUE(opc_dpc_ni.label);
    rpc = MTP3_RL_GET_DPC_VALUE(opc_dpc_ni.label);
    ni = (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
        (MTP3_NIC_MASK | MTP3_SIO_UP_MASK));

    MTP3_HDR_SET_SIO(od_info->in_hdr, ni);
    
    /* 
     * opc of in_hdr is remote point code
     */
    MTP3_RL_SET_OPC_VALUE(od_info->in_hdr.label, rpc);
    
    /* 
     * dpc of in_hdr is local point code
     */
    MTP3_RL_SET_DPC_VALUE(od_info->in_hdr.label, lpc);    

    MTP3_HDR_SET_SIO(od_info->out_hdr, (ITS_OCTET)(ROUTE_SIO_ISUP | ni));

    /* 
     * opc of out_hdr is local point code
     */
    MTP3_RL_SET_OPC_VALUE(od_info->out_hdr.label, lpc);
    
    /* 
     * dpc of out_hdr is remote point code
     */
    MTP3_RL_SET_DPC_VALUE(od_info->out_hdr.label, rpc);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free Opc Dpc structure
 *
 *  Input Parameters:
 *      od_info - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success
 *      any other value for failure
 ****************************************************************************/
int
ISUP_FreeOpcDpc(ISUP_OPC_DPC_INFO *od_info)
{
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy Opc Dpc structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int
ISUP_CopyOpcDpc(ISUP_OPC_DPC_INFO *dest, ISUP_OPC_DPC_INFO *src)
{
    int i;

    dest->next              = src->next;
    dest->opc_dpc_ni        = src->opc_dpc_ni;
    dest->isup_var_type     = src->isup_var_type;
    dest->isup_var_class    = src->isup_var_class;
    dest->isup_rmt_conglev  = src->isup_rmt_conglev;
    dest->dest_stat         = src->dest_stat;
    dest->remote_isup_stat  = src->remote_isup_stat;
    dest->exchange_type     = src->exchange_type;
    dest->syncTime          = src->syncTime;

#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    dest->segmentation_supported = src->segmentation_supported;
#endif

    dest->repeat_rsc_timerval = src->repeat_rsc_timerval;
    memcpy((void *)&dest->in_hdr, (void *)&src->in_hdr, sizeof(MTP3_HEADER));
    memcpy((void *)&dest->out_hdr, (void *)&src->out_hdr, sizeof(MTP3_HEADER));

    for (i = 1; i < ISUP_MAX_TMRS; ++i)
    {
        dest->tmr_hndl_info[i].tmr_hndl_layer =
                                  src->tmr_hndl_info[i].tmr_hndl_layer;
        dest->tmr_hndl_info[i].tmr_value =src->tmr_hndl_info[i].tmr_value;
    }

    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; ++i)
    {
        dest->pegs[i] = src->ISUP_DEST_PEGS.pegs[i];
    }
    dest->ISUP_DEST_PEGS.name = "ISUP";
    dest->ISUP_DEST_PEGS.numPegs = src->ISUP_DEST_PEGS.numPegs;
    dest->ISUP_DEST_PEGS.pegs = dest->pegs;

    /* Msg pegs: Sent Pegs */

    for (i = 0; i < ISUP_MAX_MSG_CODE; ++i)
    {
        dest->pegs_msg_sent[i] = src->pegs_msg_sent[i];
    }
    dest->ISUP_PEGS_SENT.name = src->ISUP_PEGS_SENT.name;
    dest->ISUP_PEGS_SENT.numPegs= src->ISUP_PEGS_SENT.numPegs;
    dest->ISUP_PEGS_SENT.pegs= dest->pegs_msg_sent;

    /* Msg pegs: Rcvd Pegs */

    for (i = 0; i < ISUP_MAX_MSG_CODE; ++i)
    {
        dest->pegs_msg_rcvd[i] = src->pegs_msg_rcvd[i];
    }
    dest->ISUP_PEGS_RCVD.name = src->ISUP_PEGS_RCVD.name;
    dest->ISUP_PEGS_RCVD.numPegs= src->ISUP_PEGS_RCVD.numPegs;
    dest->ISUP_PEGS_RCVD.pegs= dest->pegs_msg_rcvd;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Add Dpc-Transport pair in table
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      ITS_UINT dpc.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success any other value for failure
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
int ISUP_DpcTransAddEntry(ITS_UINT dpc)
{
    int ret = ITS_SUCCESS;

    ITS_INT *transId = (ITS_INT*)ITS_Malloc(sizeof(ITS_INT));

    *transId = DO_ROUTE_CONTEXT;

    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__ISUP_dpclock) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        ITS_Free(transId);

        return !ITS_SUCCESS;
    }

    if (HASH_AddEntry(__ISUP_dpctransp , 0, dpc,
                 (ITS_POINTER)transId) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("Dpc-TransportId pair insert failed\n"));

        ITS_Free(transId);

        ret = !ITS_SUCCESS;
    }
    else
    {
        ISUP_DEBUG(("Dpc-TransportId pair inserted for dpc:%d\n", dpc));
    }

   MUTEX_ReleaseMutex(&__ISUP_dpclock);

   return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Get the TransportId from the table.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      ITS_UINT dpc.
 *      ITS_INT* transId.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success any other value for failure
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
int ISUP_DpcTransFindEntry(ITS_UINT dpc, ITS_INT* transId)
{
    int ret = ITS_SUCCESS;

    ITS_INT* trId = 0;

    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__ISUP_dpclock) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        return !ITS_SUCCESS;
    }

    if (HASH_FindEntry(__ISUP_dpctransp , 0 , dpc, (ITS_POINTER *) &trId) == ITS_SUCCESS)
    {
        ISUP_DEBUG(("TransportId retrieved\n"));
        *transId = *trId;
    }
    else
    {
        ISUP_WARNING(("Unable to get the TransportId\n"));

        if (ISUP_DpcTransAddEntry(dpc) == ITS_SUCCESS)
        {
            if (HASH_FindEntry(__ISUP_dpctransp , 0 , dpc,
                  (ITS_POINTER*) &trId) == ITS_SUCCESS)
            {
               ISUP_DEBUG(("TransportId retrieved\n"));
               *transId = *trId;
            }
            else
            {
                ret = !ITS_SUCCESS;
            }
            MUTEX_ReleaseMutex(&__ISUP_dpclock);
            return ret;
        }

        ret = !ITS_SUCCESS;
    }
    MUTEX_ReleaseMutex(&__ISUP_dpclock);
    return ret;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update the TransportId in the table.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      ITS_UINT dpc.
 *      ITS_INT transId.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success any other value for failure
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
int ISUP_DpcTransUpdateEntry(ITS_UINT dpc, ITS_INT trpId)
{
    ITS_INT* trId = 0;

    int ret = ITS_SUCCESS;

    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__ISUP_dpclock) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        return !ITS_SUCCESS;
    }

    if (HASH_FindEntry(__ISUP_dpctransp , 0 , dpc, (ITS_POINTER *) &trId) ==
        ITS_SUCCESS)
    {
        ISUP_DEBUG(("TransportId updated\n"));
        *trId = trpId;
    }
    else
    {
        ISUP_CRITICAL(("TransportId update failed\n"));
    }
    MUTEX_ReleaseMutex(&__ISUP_dpclock);
    return ret;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      This function delete the entry from the table.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      ITS_INT context.
 *      ITS_POINTER data.
 *      void *in.
 *      void *out.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned.
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
static int ISUP_DpcIterateEntryProc(ITS_INT context, ITS_POINTER data,
                              void *in, void *out)
{
    HASH_DeleteEntry(__ISUP_dpctransp , 0, context);

    ITS_Free(data);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete all entry from DpcTransport table
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  ----------------------------------------------------------------------------
 *   Name      Date        Reference               Description
 *  ----------------------------------------------------------------------------
 *   Manish    04-01-2005  ACC651-SDS-PENH-1.0.02  Modified for ISUP performance 
 *                     ID::D0010                   enhancement 
 ****************************************************************************/
void ISUP_DpcTransTableIterate()
{
    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__ISUP_dpclock) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        return;
    }

    HASH_VTableIterate(__ISUP_dpctransp , 0, NULL,
                       NULL, ISUP_DpcIterateEntryProc);

    MUTEX_ReleaseMutex(&__ISUP_dpclock);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Retrievess information 
 *      pertaining to an OPC-DPC pair.
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
void ISUP_HashTableIterate(HASH_IterateEntryProc proc,void *in,void *out)
{
    /*
    * acquire mutex
    */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        return;
    }

    HASH_VTableIterate(__ISUP_data, ISUP_OPC_DPC_RID,
                       (void*)in, (void*)out, proc);

    MUTEX_ReleaseMutex(&__ISUP_hashGate);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Sync OpcDpcInfo form DSM
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      opc_dpc_info -  pointer to ISUP_OPC_DPC_INFO.
 *
 *  Output Parameters:
 *
 *  Return Value:
 ****************************************************************************/
static void
ISUP_SyncOpcDpcInfo(ISUP_OPC_DPC_INFO * opc_dpc_info, ITS_BOOLEAN isdsmlocal)
{
    int index, i;
    ISUP_OPC_DPC_STAT *opc_dpc_stat = NULL;

    ISUP_DEBUG(("Entering Function:: ISUP_SyncOpcDpcInfo\n"));
    opc_dpc_stat = ISUP_FindOpcDpcStat(opc_dpc_info->opc_dpc_ni, isdsmlocal);
    if (opc_dpc_stat == NULL)
    {
        return;
    }

    opc_dpc_info->isup_rmt_conglev  =  opc_dpc_stat->isup_rmt_conglev;
    opc_dpc_info->dest_stat         =  opc_dpc_stat->dest_stat;
    opc_dpc_info->remote_isup_stat  =  opc_dpc_stat->remote_isup_stat;
    opc_dpc_info->exchange_type     =  opc_dpc_stat->exchange_type;
    opc_dpc_info->syncTime          =  TIMERS_Time();

    for (index = 0; index < ISUP_MAX_TMRS; ++index)
    {
        opc_dpc_info->tmr_hndl_info[index].tmr_hndl_layer =
                opc_dpc_stat->tmr_hndl_info[index].tmr_hndl_layer;
        opc_dpc_info->tmr_hndl_info[index].tmr_value =
                opc_dpc_stat->tmr_hndl_info[index].tmr_value;
    }

    /* here we are adding u know y */
    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
        opc_dpc_info->pegs[i] = opc_dpc_stat->ISUP_DEST_PEGS.pegs[i];
    }

#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    opc_dpc_info->segmentation_supported = opc_dpc_stat->segmentation_supported;
#endif

    opc_dpc_info->repeat_rsc_timerval = opc_dpc_stat->repeat_rsc_timerval;
    ISUP_ReleaseOpcDpcStat(opc_dpc_stat, isdsmlocal);
    ISUP_DEBUG(("Leaving Function:: ISUP_SyncOpcDpcInfo\n"));
    return;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in the hash table for information 
 *      pertaining to an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key for the table
 *      varType - variant type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      l_od_info - pointer to allocated structure
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
int
ISUP_AllocOpcDpc(MTP3_HEADER opc_dpc_ni, ISUP_VAR_TYPE varType,
                 ISUP_OPC_DPC_INFO *l_od_info)
{
    ISUP_OPC_DPC_INFO *dummy = NULL;
    ISUP_OPC_DPC_INFO *od_info = NULL;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    hash = LocalHash((ITS_OCTET *)&opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
     */
    dummy = NULL;
    if (HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                       hash, (ITS_POINTER *)&dummy) == ITS_SUCCESS)
    {
        ISUP_OPC_DPC_INFO *tmp;

        for (tmp = dummy; tmp != NULL; tmp = tmp->next)
        {
            if (memcmp(&opc_dpc_ni, &tmp->opc_dpc_ni,
                       sizeof(MTP3_HEADER)) == 0)
            {
                /* panic, duplicate  */

                MUTEX_ReleaseMutex(&__ISUP_hashGate);        
        
                return (ITS_EINUSE);
            }
        }
    }

    /*
     * allocate memory
     */
    if ((od_info = (ISUP_OPC_DPC_INFO *)
            calloc(1, sizeof(ISUP_OPC_DPC_INFO))) == NULL)
    {
        ISUP_CRITICAL((": Couldn't calloc.\n"));
        
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOMEM;
    }
    od_info->next = dummy;

    ISUP_InitOpcDpc(od_info, opc_dpc_ni, varType);

    /* 
     * add to hash table 
     */
    if (HASH_AddEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                      hash, (ITS_POINTER)od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);
    
        free(od_info);

        return (ITS_ENOMEM);
    }

    ISUP_CopyOpcDpc(l_od_info, od_info);

    /*
     * success
     */
    MUTEX_ReleaseMutex(&__ISUP_hashGate);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Add new entry in local table in case new destination is added
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to look up in table
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
static int
ISUP_AddNewOpcDpcInfoEntry(MTP3_HEADER opc_dpc_ni, ISUP_OPC_DPC_INFO *odInfo, 
                                                      ITS_BOOLEAN isdsmlocal)
{
    int ret = 0, index;
    ISUP_OPC_DPC_STAT * opc_dpc_stat = NULL;

    opc_dpc_stat = ISUP_FindOpcDpcStat(opc_dpc_ni, isdsmlocal);
    if (opc_dpc_stat == NULL)
    {
        return ITS_ENOTFOUND;
    }

    /* Oh, its new destination add it */
    ret = ISUP_AllocOpcDpc(opc_dpc_ni, opc_dpc_stat->isup_var_type, odInfo);
    if (ret != ITS_SUCCESS)
    {
        ISUP_ReleaseOpcDpcStat(opc_dpc_stat, isdsmlocal);
        return ITS_ENOTFOUND;
    }
    odInfo->isup_var_type     =  opc_dpc_stat->isup_var_type;
    odInfo->isup_rmt_conglev  =  opc_dpc_stat->isup_rmt_conglev;
    odInfo->dest_stat         =  opc_dpc_stat->dest_stat;
    odInfo->remote_isup_stat  =  opc_dpc_stat->remote_isup_stat;
    odInfo->exchange_type     =  opc_dpc_stat->exchange_type;

    ISUP_DEBUG(("ISUP_AddNewOpcDpcInfoEntry: New Destination is Added\n"));

    for (index = 0; index < ISUP_MAX_TMRS; ++index)
    {
        odInfo->tmr_hndl_info[index].tmr_hndl_layer =
                opc_dpc_stat->tmr_hndl_info[index].tmr_hndl_layer;
        odInfo->tmr_hndl_info[index].tmr_value =
                opc_dpc_stat->tmr_hndl_info[index].tmr_value;
    }

#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    odInfo->segmentation_supported = opc_dpc_stat->segmentation_supported;
#endif

    odInfo->repeat_rsc_timerval = opc_dpc_stat->repeat_rsc_timerval;
    ISUP_UpdateOpcDpc(odInfo);
    return ISUP_ReleaseOpcDpcStat(opc_dpc_stat, isdsmlocal);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in the hash table for information pertaining to 
 *      an OPC-DPC pair.This function may call FindOpcDpcStat().
 *      So Do not call this function rite after the FindOpcDpcStat()
 *      berfore calling ReleaseOpcDpcStat().
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to look up in table
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_FindOpcDpc(MTP3_HEADER opc_dpc_ni, ISUP_OPC_DPC_INFO *l_od_info,
                                              ITS_BOOLEAN isdsmlocal)
{
    ISUP_OPC_DPC_INFO *od_info = NULL;
    ISUP_OPC_DPC_INFO *tmp;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);


    hash = LocalHash((ITS_OCTET *)&opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
     */
    if (HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                       hash, (ITS_POINTER *)&od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ISUP_AddNewOpcDpcInfoEntry(opc_dpc_ni, l_od_info, isdsmlocal);
    }

    for (tmp = od_info; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&opc_dpc_ni, &tmp->opc_dpc_ni,
                   sizeof(MTP3_HEADER)) == 0)
        {
            break;
        }
    }

    /* handle not found */
    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        /* Check is it a new destination, if yes alloc and update */
        return  ISUP_AddNewOpcDpcInfoEntry(opc_dpc_ni, l_od_info, isdsmlocal);

    }

    od_info = tmp;
        
    if ((TIMERS_Time() - od_info->syncTime) >= ISUP_SYNC_TIMER_VAL)
    {
        ISUP_SyncOpcDpcInfo(od_info, isdsmlocal);
    }

    /*
     * copy values from src to dest
     */
    if (ISUP_CopyOpcDpc(l_od_info, od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOMEM;
    }

    /*
     * success
     */
    MUTEX_ReleaseMutex(&__ISUP_hashGate);        

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in the hash table for information pertaining to 
 *      an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to look up in table
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITSSS7DLLAPI int
ISUP_FindOpcDpcStatic(MTP3_HEADER opc_dpc_ni, ISUP_OPC_DPC_INFO *l_od_info)
{
    ISUP_OPC_DPC_INFO *od_info = NULL;
    ISUP_OPC_DPC_INFO *tmp;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    hash = LocalHash((ITS_OCTET *)&opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
     */
    if (HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                       hash, (ITS_POINTER *)&od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOTFOUND;
    }

    for (tmp = od_info; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&opc_dpc_ni, &tmp->opc_dpc_ni,
                   sizeof(MTP3_HEADER)) == 0)
        {
            break;
        }
    }

    /* handle not found */
    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOTFOUND;
    }

    od_info = tmp;

    /*
     * copy values from src to dest
     */
    if (ISUP_CopyOpcDpc(l_od_info, od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        free(l_od_info);

        return ITS_ENOMEM;
    }

    /*
     * No need to do find on the OPC-DPC stat table
     */

    /*
     * success
     */
    MUTEX_ReleaseMutex(&__ISUP_hashGate);        

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release row lock held on an entry
 *
 *  Input Parameters:
 *      opc_dpc_info - OPC-DPC pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_ReleaseOpcDpc(ISUP_OPC_DPC_INFO *opc_dpc_info)
{
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release row lock held on an entry
 *
 *  Input Parameters:
 *      opc_dpc_info - OPC-DPC pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_ReleaseOpcDpcStatic(ISUP_OPC_DPC_INFO *opc_dpc_info)
{
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete an entry in the hash table for information pertaining to 
 *      an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to delete
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int
ISUP_DeleteOpcDpc(MTP3_HEADER opc_dpc_ni)
{
    ISUP_OPC_DPC_INFO *od_info;
    int ret = ITS_SUCCESS;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("DeleteOpcDpc: Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    hash = LocalHash((ITS_OCTET *)&opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
     */
    ret = HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                         hash, (ITS_POINTER *)&od_info);

    if (ret == ITS_SUCCESS)
    {
        ISUP_OPC_DPC_INFO **tmp;

        for (tmp = &od_info; *tmp != NULL; )
        {
            if (memcmp(&opc_dpc_ni, &(*tmp)->opc_dpc_ni,
                       sizeof(MTP3_HEADER)) == 0)
            {
                ISUP_OPC_DPC_INFO *tmp2 = *tmp;

                *tmp = (*tmp)->next;

                ISUP_FreeOpcDpc(tmp2);

                free(tmp2);
            }
            else
            {
                tmp = &(*tmp)->next;
            }
        }

        /*
         * delete entry
         */
        if (od_info == NULL)
        {
            ret = HASH_DeleteEntry(__ISUP_data, ISUP_OPC_DPC_RID, hash);
        }
        else
        {
            ret = HASH_AddEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                                hash, (ITS_POINTER)od_info);
        }
    }

    MUTEX_ReleaseMutex(&__ISUP_hashGate);

    return (ret);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Find an OPC DPC, this returns the pointer. 
 *      After this ReleaseOpcDpcInfo() must be called.
 *  Input Parameters:
 *      new_opc_dpc - pointer to updated structure.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
static ISUP_OPC_DPC_INFO *
ISUP_FindOpcDpcInfo(MTP3_HEADER opc_dpc_ni)
{

    ISUP_OPC_DPC_INFO *od_info = NULL;
    ISUP_OPC_DPC_INFO *tmp;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL((": Couldn't acquire mutex.\n"));

        return NULL;
    }


    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    hash = LocalHash((ITS_OCTET *)&opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
     */
    if (HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                       hash, (ITS_POINTER *)&od_info) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return NULL;
    }

    for (tmp = od_info; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&opc_dpc_ni, &tmp->opc_dpc_ni,
                   sizeof(MTP3_HEADER)) == 0)
        {
            break;
        }
    }

    /* handle not found */
    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return NULL;
    }

    return tmp;
}
/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Release Opc Dpc Info
 *
 *  Input Parameters:
 *      odInfo - pointer to updated structure.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 ****************************************************************************/
static int
ISUP_ReleaseOpcDpcInfo(ISUP_OPC_DPC_INFO *odInfo)
{
    odInfo = NULL;
    /*
     * success
     */
    MUTEX_ReleaseMutex(&__ISUP_hashGate);        

    return ITS_SUCCESS;

}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update an OPC DPC INFO for DSM
 *
 *  Input Parameters:
 *      new_opc_dpc - pointer to updated structure.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
ITSSS7DLLAPI int 
ISUP_SyncOpcDpcInfoWithStat(ISUP_OPC_DPC_STAT *opc_dpc_stat)
{
    ISUP_OPC_DPC_INFO *opc_dpc_info = NULL;
    int index, i;

    ISUP_DEBUG(("Calling ISUP_SyncOpcDpcInfoWithStat Func \n"));
    opc_dpc_info = ISUP_FindOpcDpcInfo(opc_dpc_stat->opc_dpc_ni);
    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    opc_dpc_info->isup_rmt_conglev  =  opc_dpc_stat->isup_rmt_conglev;
    opc_dpc_info->dest_stat         =  opc_dpc_stat->dest_stat;
    opc_dpc_info->remote_isup_stat  =  opc_dpc_stat->remote_isup_stat;
    opc_dpc_info->exchange_type     =  opc_dpc_stat->exchange_type;

    for (index = 0; index < ISUP_MAX_TMRS; ++index)
    {
        opc_dpc_info->tmr_hndl_info[index].tmr_hndl_layer =
                opc_dpc_stat->tmr_hndl_info[index].tmr_hndl_layer;
        opc_dpc_info->tmr_hndl_info[index].tmr_value =
                opc_dpc_stat->tmr_hndl_info[index].tmr_value;
    }

    /* here we are adding u know y */
    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
        opc_dpc_info->pegs[i] = opc_dpc_stat->ISUP_DEST_PEGS.pegs[i];
    }

#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    opc_dpc_info->segmentation_supported = opc_dpc_stat->segmentation_supported;
#endif

    opc_dpc_info->repeat_rsc_timerval = opc_dpc_stat->repeat_rsc_timerval;

    return ISUP_ReleaseOpcDpcInfo(opc_dpc_info);

}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update an OPC DPC entry with new values
 *
 *  Input Parameters:
 *      new_opc_dpc - pointer to updated structure.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
int 
ISUP_UpdateOpcDpc(ISUP_OPC_DPC_INFO *new_opc_dpc)
{
    ISUP_OPC_DPC_INFO *old_opc_dpc = NULL;
    ISUP_OPC_DPC_INFO *tmp;
    ITS_INT hash;

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL((": Couldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(new_opc_dpc->opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(new_opc_dpc->opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(new_opc_dpc->opc_dpc_ni.label, 0);

    hash = LocalHash((ITS_OCTET *)&new_opc_dpc->opc_dpc_ni, sizeof(MTP3_HEADER));

    /*
     * find entry
*/
    if (HASH_FindEntry(__ISUP_data, ISUP_OPC_DPC_RID,
                       hash, (ITS_POINTER *)&old_opc_dpc) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOTFOUND;
    }

    /* find entry */
    for (tmp = old_opc_dpc; tmp != NULL; tmp = tmp->next)
    {
        if (memcmp(&new_opc_dpc->opc_dpc_ni, &tmp->opc_dpc_ni,
                   sizeof(MTP3_HEADER)) == 0)
        {
            break;
        }
    }

    /* handle not found */
    if (tmp == NULL)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOTFOUND;
    }

    /*
     * update values in hash table
     */
    if (ISUP_CopyOpcDpc(old_opc_dpc, new_opc_dpc) != ITS_SUCCESS)
    {
        MUTEX_ReleaseMutex(&__ISUP_hashGate);        

        return ITS_ENOMSG;
    }

    /*
     * success
     */
    MUTEX_ReleaseMutex(&__ISUP_hashGate);        

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update an OPC DPC entry with new values
 *
 *  Input Parameters:
 *      key
 *      ent
 *      in
 *      out
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
int
ISUP_PrintOpcDpc(ITS_INT key, ITS_POINTER ent, void *in, void *out)
{
    ISUP_OPC_DPC_INFO *opc_dpc_info = (ISUP_OPC_DPC_INFO *)ent;

    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    while (opc_dpc_info != NULL)
    {
        ISUP_DEBUG(("OPC = %d \n", MTP3_RL_GET_OPC_VALUE(opc_dpc_info->opc_dpc_ni.label)));
        ISUP_DEBUG(("DPC = %d \n", MTP3_RL_GET_DPC_VALUE(opc_dpc_info->opc_dpc_ni.label)));
    
        ISUP_DEBUG(("VARIANT TYPE = %d \n", opc_dpc_info->isup_var_type));
    
        ISUP_DEBUG(("IN_HDR OPC = %d \n", 
                MTP3_RL_GET_OPC_VALUE(opc_dpc_info->in_hdr.label)));

        ISUP_DEBUG(("IN_HDR DPC = %d \n", 
                MTP3_RL_GET_DPC_VALUE(opc_dpc_info->in_hdr.label)));
    
        ISUP_DEBUG(("OUT_HDR OPC = %d \n", 
                MTP3_RL_GET_OPC_VALUE(opc_dpc_info->out_hdr.label)));
    
        ISUP_DEBUG(("OUT_HDR DPC = %d \n", 
                MTP3_RL_GET_DPC_VALUE(opc_dpc_info->out_hdr.label)));

        opc_dpc_info = opc_dpc_info->next;
    }

    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Alloc new OPC DPC tables
 *
 *  Input Parameters:
 *      key
 *      ent
 *      in
 *      out
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
static int
ISUP_AllocLocalTable(ITS_POINTER ent, void *in, void *out)
{
    ISUP_OPC_DPC_STAT *opc_dpc_stat = (ISUP_OPC_DPC_STAT *)ent;
    ISUP_OPC_DPC_INFO config_info;
    int index;
    
    if (opc_dpc_stat == NULL)
    {
        ISUP_ERROR(("ISUP_AllocLocalTable : It should not happen"));
    }

    ISUP_AllocOpcDpc(opc_dpc_stat->opc_dpc_ni, opc_dpc_stat->isup_var_type,
                     &config_info);

    config_info.isup_rmt_conglev  =  opc_dpc_stat->isup_rmt_conglev;
    config_info.dest_stat         =  opc_dpc_stat->dest_stat;
    config_info.remote_isup_stat  =  opc_dpc_stat->remote_isup_stat;
    config_info.exchange_type     =  opc_dpc_stat->exchange_type;

    for (index = 0; index < ISUP_MAX_TMRS; ++index)
    {
        config_info.tmr_hndl_info[index].tmr_hndl_layer =
                opc_dpc_stat->tmr_hndl_info[index].tmr_hndl_layer;
        config_info.tmr_hndl_info[index].tmr_value =
                opc_dpc_stat->tmr_hndl_info[index].tmr_value;
    }

#if defined CCITT
    config_info.segmentation_supported = opc_dpc_stat->segmentation_supported;
#endif

    config_info.repeat_rsc_timerval = opc_dpc_stat->repeat_rsc_timerval;
    ISUP_UpdateOpcDpc(&config_info);
    return ISUP_ReleaseOpcDpc(&config_info);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function will Initialize all Local Opc Dpc InfoTables
 *
 *  Input Parameters:
 *      event: The event holding the timeout.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 ****************************************************************************/
int
ISUP_AllocAllLocalTables()
{
    int ret = 0;

    ret = DSM_TableIterate(DSM_IsupFtGroupId,
                           DSM_TABLE_ISUP_OPC_DPC,
                           NULL,
                           NULL,
                           ISUP_AllocLocalTable);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("SyncTime: Could not iterate, error %d.\n", ret));
        return ret;
    }
    return ret;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information about all opc dpc pairs
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
int
ISUP_PrintAllOpcDpc()
{
    ISUP_DEBUG(("---- PRINT OPC DPC MAP -----\n"));

    /*
     * acquire mutex
     */
    if (MUTEX_AcquireMutex(&__ISUP_hashGate) != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("\nCouldn't acquire mutex.\n"));

        return ITS_EBADMUTEX;
    }

    HASH_VTableIterate(__ISUP_data, ISUP_OPC_DPC_RID,
                       NULL, NULL, ISUP_PrintOpcDpc);

    ISUP_DEBUG(("---- PRINT OPC DPC MAP DONE -----\n"));    
    
    MUTEX_ReleaseMutex(&__ISUP_hashGate);

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Initialize Ckgp list with default values
 *
 *  Input Parameters:
 *      opc_dpc_ni - Octet containing opcid+dpcid.
 *      ckgp_list - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static void
ISUP_InitCkgpList(MTP3_HEADER opc_dpc_ni, ISUP_CKGP_LIST *ckgp_list)
{
    int i;

    memcpy(&ckgp_list->opc_dpc_ni, &opc_dpc_ni, sizeof(MTP3_HEADER));
    for(i = 0; i < ISUP_MAX_CKGPS; ++i)
    {
        ckgp_list->ckgp_info[i].ckgp_id = ISUP_INV_CKGP_ID;
        memset(&ckgp_list->ckgp_info[i].usable_cics[0], 0, sizeof(ITS_UINT));
    }
    ckgp_list->noCkgps = 0;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate Ckgp List
 *
 *  Input Parameters:
 *      opc_dpc_ni - Octet containing opcid+dpcid.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ISUP_CKGP_LIST *
 ****************************************************************************/
ISUP_CKGP_LIST *
ISUP_AllocCkgpList(MTP3_HEADER opc_dpc_ni)
{

    ISUP_CKGP_LIST *list = NULL;
    int error;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    list = (ISUP_CKGP_LIST*) DSM_Find(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_CKGP_LIST,
                                         (ITS_OCTET*)&opc_dpc_ni,
                                         sizeof(opc_dpc_ni), &error);
    if (error == ITS_SUCCESS )
    {
        return list;
    }
    else if (error == ITS_EINUSE)
    {
        return ISUP_FindCkgpList(opc_dpc_ni, ITS_FALSE);

    }
    else if (error == ITS_ENOTFOUND)
    {
    
        list = (ISUP_CKGP_LIST *)DSM_Alloc(DSM_IsupFtGroupId,
                                                 DSM_TABLE_ISUP_CKGP_LIST,
                                                 (ITS_OCTET *)&opc_dpc_ni,
                                                 sizeof(opc_dpc_ni),
                                                 sizeof(ISUP_CKGP_LIST),
                                                 &error);
        if (error != ITS_SUCCESS)
        {
            /* DSM alloc failed */
            switch(error)
            {
            case (ITS_EBADMUTEX):
                ISUP_CRITICAL(("ISUP_CreateCkgpList: Couldn't acquire mutex.\n"));
                break;
            case (ITS_ENOMEM):
                ISUP_CRITICAL(("ISUP_CreateCkgpList: No Memory.\n"));
                break;
            default:
                ISUP_CRITICAL(("ISUP_CreateCkgpList: Error %d.\n"));
                break;
            }
            return (NULL);
        }    
    }

    ISUP_InitCkgpList(opc_dpc_ni, list);
    return list;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find Ckgp List
 *
 *  Input Parameters:
 *      opc_dpc_ni - Octet containing opcid+dpcid.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ISUP_CKGP_LIST *
 ****************************************************************************/
ISUP_CKGP_LIST*
ISUP_FindCkgpList(MTP3_HEADER opc_dpc_ni, ITS_BOOLEAN isdsmlocal)
{
    ISUP_CKGP_LIST *list = NULL;
    int error;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) & 
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);  

    if (isdsmlocal == ITS_TRUE)
    {
        list = (ISUP_CKGP_LIST*) DSM_FindLocal(DSM_IsupFtGroupId,
                                               DSM_TABLE_ISUP_CKGP_LIST,
                                               (ITS_OCTET*)&opc_dpc_ni,
                                               sizeof(opc_dpc_ni), &error);
    }
    else
    {
        list = (ISUP_CKGP_LIST*) DSM_Find(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_CKGP_LIST,
                                             (ITS_OCTET*)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni), &error);
    } 

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);

        /* do a DSM_Find() again */

        if (isdsmlocal == ITS_TRUE)
         {
             list = (ISUP_CKGP_LIST*) DSM_FindLocal(DSM_IsupFtGroupId,
                                                    DSM_TABLE_ISUP_CKGP_LIST,
                                                    (ITS_OCTET*)&opc_dpc_ni,
                                                    sizeof(opc_dpc_ni), &error);
         }
         else
         {
             list = (ISUP_CKGP_LIST*) DSM_Find(DSM_IsupFtGroupId,
                                                  DSM_TABLE_ISUP_CKGP_LIST,
                                                  (ITS_OCTET*)&opc_dpc_ni,
                                                  sizeof(opc_dpc_ni), &error);
         }
    }

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ISUP_ERROR(("ISUP_FindCkgpList: Couldn't acquire mutex.\n"));

            break;
        case (ITS_ENOTFOUND):
            ISUP_WARNING(("ISUP_FindCkgpList: Can't find LIST pcic.\n"));

            break;
        default:
            ISUP_WARNING(("ISUP_FindCkgpList: Can't  Find List %d.\n", error));

            break;
        }

        return (NULL);
    }
    return list;
} 
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit the Ckgp list
 *
 *  Input Parameters:
 *      ckgp_list - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
ISUP_ReleaseCkgpList(ISUP_CKGP_LIST* ckgp_list, ITS_BOOLEAN isdsmlocal)
{
    int error;
    if (ckgp_list == NULL)
    {
        return !ITS_SUCCESS;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(ckgp_list-> opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(ckgp_list-> opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(ckgp_list-> opc_dpc_ni.label, 0);

    /*
     * commit to Ckgp list
     */
    if (isdsmlocal == ITS_TRUE)
    {
        error = DSM_CommitLocal(DSM_IsupFtGroupId,
                                DSM_TABLE_ISUP_CKGP_LIST,
                                (ITS_OCTET *)&(ckgp_list->opc_dpc_ni),
                                sizeof(ckgp_list->opc_dpc_ni), ckgp_list);
    }
    else
    {
        error = DSM_Commit(DSM_IsupFtGroupId,
                           DSM_TABLE_ISUP_CKGP_LIST,
                           (ITS_OCTET *)&(ckgp_list->opc_dpc_ni),
                           sizeof(ckgp_list->opc_dpc_ni), ckgp_list);
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ISUP_ReleaseCkgpList:Commit Failed error %d.\n", error));
        return (error);
    }
    return (ITS_SUCCESS);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize Opc Dpc structure with initial default values 
 *
 *  Input Parameters:
 *      od_stat - pointer to structure
 *      opcid_dpcid - Octet containing opcid+dpcid.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_InitOpcDpcStat(ISUP_OPC_DPC_STAT *od_stat,
                    MTP3_HEADER opc_dpc_ni, 
                    ISUP_VAR_TYPE varType)
{
    int i;
    ISUP_TMR_HNDL_INFO* tmr_hndl;
    const char *className = ISUP_VariantToString(varType);


    od_stat->opc_dpc_ni = opc_dpc_ni;

    od_stat->isup_var_type = varType; 

    tmr_hndl = VAR_GetTimerInfo(ITS_FindFeature(className));

    for (i = 1; i < ISUP_MAX_TMRS; i++)
    {
        od_stat->tmr_hndl_info[i].tmr_hndl_layer =
                                  tmr_hndl[i-1].tmr_hndl_layer;

        od_stat->tmr_hndl_info[i].tmr_value = tmr_hndl[i-1].tmr_value;
    }

    od_stat->isup_rmt_conglev = ISUP_RMT_CONGES_OFF;
    od_stat->dest_stat        = ISUP_DEST_UNREACHABLE;
    od_stat->remote_isup_stat = ISUP_REMOTE_AVAILABLE;
    od_stat->exchange_type    = ISUP_XCHANGE_TYPE_A;
    od_stat->isup_loc_conglev = ISUP_LOC_CONGES_OFF;

#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    od_stat->segmentation_supported = ITS_TRUE;
#endif

    od_stat->repeat_rsc_timerval = 600;

    for (i = 0; i < PEG_ISUP_DEST_NUM_PEGS; i++)
    {
        od_stat->pegs[i] = 0;
    }
    od_stat->ISUP_DEST_PEGS.name = "ISUP";
    od_stat->ISUP_DEST_PEGS.numPegs = sizeof(od_stat->pegs) / sizeof(ITS_UINT);
    od_stat->ISUP_DEST_PEGS.pegs = od_stat->pegs;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free Opc Dpc structure
 *
 *  Input Parameters:
 *      od_stat - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success
 *      any other value for failure
 ****************************************************************************/
int
ISUP_FreeOpcDpcStat(ISUP_OPC_DPC_STAT *od_stat)
{
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy Opc Dpc structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 ****************************************************************************/
int
ISUP_CopyOpcDpcStat(ISUP_OPC_DPC_STAT *dest, ISUP_OPC_DPC_STAT *src)
{
    int index;

    dest->opc_dpc_ni = src->opc_dpc_ni;
    dest->isup_var_type = src->isup_var_type;
    dest->isup_rmt_conglev = src->isup_rmt_conglev;
    dest->dest_stat     = src->dest_stat;
    dest->remote_isup_stat = src->remote_isup_stat;
    dest->exchange_type = src->exchange_type;
    dest->isup_loc_conglev = src->isup_loc_conglev;


#if defined(CCITT) || defined(PRC) ||  defined(TTC)
    dest->segmentation_supported = src->segmentation_supported;
#endif
    
    dest->repeat_rsc_timerval = src->repeat_rsc_timerval;

    for (index = 0; index < ISUP_MAX_TMRS; index++)
    {
        dest->tmr_hndl_info[index].tmr_hndl_layer =
                src->tmr_hndl_info[index].tmr_hndl_layer;
        dest->tmr_hndl_info[index].tmr_value =
                src->tmr_hndl_info[index].tmr_value;
    }
   
    for (index = 0; index < PEG_ISUP_DEST_NUM_PEGS; index++)
    {
        dest->pegs[index] = src->ISUP_DEST_PEGS.pegs[index];
    }
    dest->ISUP_DEST_PEGS.name = "ISUP";
    dest->ISUP_DEST_PEGS.numPegs = src->ISUP_DEST_PEGS.numPegs;
    dest->ISUP_DEST_PEGS.pegs = dest->pegs;

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in the hash table for information 
 *      pertaining to an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key for the table
 *      varType - variant type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      l_od_stat - pointer to allocated structure
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITS_BOOLEAN
__ISUP_IsInitialized(MTP3_HEADER opc_dpc_ni)
{
    ISUP_OPC_DPC_STAT *opc_dpc_stat = NULL;
    int error;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    opc_dpc_stat = (ISUP_OPC_DPC_STAT *)DSM_Find(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_OPC_DPC,
                                         (ITS_OCTET *)&opc_dpc_ni,
                                         sizeof(opc_dpc_ni), &error);
    if (error == ITS_ENOTFOUND)
    {
        return ITS_FALSE;
    }
    else if (error == ITS_SUCCESS)
    {
        /* entry is already present */
        ISUP_CRITICAL(("__ISUP_IsInitialized: OPC-DPC already allocated.\n"));

        ISUP_ReleaseOpcDpcStat(opc_dpc_stat, ITS_FALSE);
        return ITS_TRUE;
    }
    else if (error == ITS_EINUSE)
    {
        /* entry is already present */
        ISUP_CRITICAL(("__ISUP_IsInitialized: OPC-DPC already allocated.\n"));
        return ITS_TRUE;
    }
    return ITS_FALSE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in the hash table for information 
 *      pertaining to an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key for the table
 *      varType - variant type
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      l_od_stat - pointer to allocated structure
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ISUP_OPC_DPC_STAT *
ISUP_AllocOpcDpcStat(MTP3_HEADER opc_dpc_ni,ISUP_VAR_TYPE varType)
{
    ISUP_OPC_DPC_STAT *opc_dpc_stat = NULL;
    ISUP_OPC_DPC_INFO opc_dpc_info;
    int error;
    const char *className = ISUP_VariantToString(varType);

    if (ITS_FindFeature(className) ==  NULL)
    {
        return NULL;
    }

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    opc_dpc_stat = (ISUP_OPC_DPC_STAT *)DSM_Find(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_OPC_DPC,
                                         (ITS_OCTET *)&opc_dpc_ni,
                                         sizeof(opc_dpc_ni), &error);

    if (error == ITS_SUCCESS )
    {
        /* entry is already present */
        ISUP_CRITICAL(("AllocOpcDpcStat: OPC-DPC already allocated.\n"));

        /*Add a Entry for Local copy also*/
        error = ISUP_AllocOpcDpc(opc_dpc_ni, varType, &opc_dpc_info);
        if (error != ITS_SUCCESS)
        {
            error = DSM_UnlockRow(DSM_IsupFtGroupId,
                                  DSM_TABLE_ISUP_OPC_DPC,
                                  (ITS_OCTET *)&opc_dpc_ni,
                                  sizeof(opc_dpc_ni), opc_dpc_stat);
            return NULL;
        }
        return (opc_dpc_stat);
    }
    else if (error == ITS_EINUSE)
    {
        /*Add a Entry for Local copy also*/
        error = ISUP_AllocOpcDpc(opc_dpc_ni, varType, &opc_dpc_info);
        if (error != ITS_SUCCESS)
        {
            return NULL;
        }
        return ISUP_FindOpcDpcStat(opc_dpc_ni, ITS_FALSE);
    }

    if (error == ITS_ENOTFOUND)
    {
        /* Entry not present in table, so allocate new one */

        ISUP_DEBUG(("AllocOpcDpcStat: going to allocate OPC-DPC.\n"));

        /* allocate memory */

        opc_dpc_stat = (ISUP_OPC_DPC_STAT *)DSM_Alloc(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_OPC_DPC,
                                             (ITS_OCTET *)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni),
                                             sizeof(ISUP_OPC_DPC_STAT),
                                             &error);
        if (error != ITS_SUCCESS)
        {
            /* DSM alloc failed */

            switch(error)
            {
            case (ITS_EBADMUTEX):
                ISUP_CRITICAL(("AllocOpcDpcStat: Couldn't acquire mutex.\n"));
                break;
            case (ITS_ENOMEM):
                ISUP_CRITICAL(("AllocOpcDpcStat: No Memory.\n"));
                break;
            default:
                ISUP_CRITICAL(("AllocOpcDpcStat: Error %d.\n"));
                break;
            }

            return (NULL);
        }    
    }
    else
    {
        /* DSM internal error */

        ISUP_CRITICAL(("AllocOpcDpcStat: Error %d.\n", error));
   
        return (NULL);
    }

    ISUP_InitOpcDpcStat(opc_dpc_stat, opc_dpc_ni, varType);

    /*Add a Entry for Local copy also*/
    error = ISUP_AllocOpcDpc(opc_dpc_ni, varType, &opc_dpc_info);
    if (error != ITS_SUCCESS)
    {
        return NULL;
    }
    else
    {
        ISUP_ReleaseOpcDpc(&opc_dpc_info);
    }

    /* return pointer to hash table entry, so no local copy */
    return (opc_dpc_stat);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *       lock OPC_DPC_STAT Table
 *       Do not use this function unless u know what u r doing 
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
int
ISUP_LockOpcDpcStatTable()
{
    return DSM_LockTable(DSM_IsupFtGroupId,
                         DSM_TABLE_ISUP_OPC_DPC);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Un lock OPC_DPC_STAT Table
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
int
ISUP_UnLockOpcDpcStatTable()
{
    return DSM_UnlockTable(DSM_IsupFtGroupId,
                         DSM_TABLE_ISUP_OPC_DPC);

}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in the hash table for information pertaining to 
 *      an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to look up in table
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success, other value for failure
 ****************************************************************************/
ITSSS7DLLAPI ISUP_OPC_DPC_STAT *
ISUP_FindOpcDpcStat(MTP3_HEADER opc_dpc_ni, ITS_BOOLEAN isdsmlocal)
{
    ISUP_OPC_DPC_STAT *opc_dpc_stat = NULL;
    int error = ITS_EINUSE;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    if (isdsmlocal == ITS_TRUE)
    {
        opc_dpc_stat = (ISUP_OPC_DPC_STAT*) DSM_FindLocal(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_OPC_DPC,
                                             (ITS_OCTET*)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni), &error);
    }
    else
    {
        opc_dpc_stat = (ISUP_OPC_DPC_STAT*) DSM_Find(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_OPC_DPC,
                                             (ITS_OCTET*)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni), &error);
    }

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);
       
        /* do a DSM_Find() again */
        if (isdsmlocal == ITS_TRUE)
        {
            opc_dpc_stat = (ISUP_OPC_DPC_STAT*) DSM_FindLocal(DSM_IsupFtGroupId,
                                                 DSM_TABLE_ISUP_OPC_DPC,
                                                 (ITS_OCTET*)&opc_dpc_ni,
                                                 sizeof(opc_dpc_ni), &error);
        } 
        else
        {
            opc_dpc_stat = (ISUP_OPC_DPC_STAT*) DSM_Find(DSM_IsupFtGroupId,
                                                 DSM_TABLE_ISUP_OPC_DPC,
                                                 (ITS_OCTET*)&opc_dpc_ni,
                                                 sizeof(opc_dpc_ni), &error);
        }
    }

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ISUP_ERROR(("FindOpcDpcStat: Couldn't acquire mutex.\n"));

            break;
        case (ITS_ENOTFOUND):
            ISUP_WARNING(("FindOpcDpcStat: Can't find CIC pcic.\n"));

            break;
        default:
            ISUP_WARNING(("FindOpcDpcStat: Can't find CIC pcic error %d.\n", 
                         error));

            break;
        }

        return (NULL);
    }

    /* no need for local copy since actual hash table pointer is returned */

    return opc_dpc_stat;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete an entry in the hash table for information pertaining to 
 *      an OPC-DPC pair.
 *
 *  Input Parameters:
 *      opc_dpc_ni - key to delete
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int
ISUP_DeleteOpcDpcStat(MTP3_HEADER opc_dpc_ni, ITS_BOOLEAN isdsmlocal)
{
    ISUP_OPC_DPC_STAT *opc_dpc_stat;
    int error;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_ni.label, 0);

    if (isdsmlocal == ITS_TRUE)
    {
        opc_dpc_stat = (ISUP_OPC_DPC_STAT *) DSM_FindLocal(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_OPC_DPC,
                                             (ITS_OCTET *)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni),
                                             &error);
    }
    else
    {
        opc_dpc_stat = (ISUP_OPC_DPC_STAT *) DSM_Find(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_OPC_DPC,
                                             (ITS_OCTET *)&opc_dpc_ni,
                                             sizeof(opc_dpc_ni),
                                             &error);
    }
    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);
       
        /* do a DSM_Find() again */
        if (isdsmlocal == ITS_TRUE)
        {
            opc_dpc_stat = (ISUP_OPC_DPC_STAT *) DSM_FindLocal(DSM_IsupFtGroupId,
                                                 DSM_TABLE_ISUP_OPC_DPC,
                                                 (ITS_OCTET *)&opc_dpc_ni,
                                                 sizeof(opc_dpc_ni),
                                                 &error);
        }
        else
        {
            opc_dpc_stat = (ISUP_OPC_DPC_STAT *) DSM_Find(DSM_IsupFtGroupId,
                                                 DSM_TABLE_ISUP_OPC_DPC,
                                                 (ITS_OCTET *)&opc_dpc_ni,
                                                 sizeof(opc_dpc_ni),
                                                 &error);
        }
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("DeleteOpcDpcStat: Couldn't find OPC-DPC error %d.\n", 
                        error));

        return error;
    }

    if ( isdsmlocal == ITS_TRUE)
    {
        error = DSM_FreeLocal(DSM_IsupFtGroupId,
                              DSM_TABLE_ISUP_OPC_DPC,
                              (ITS_OCTET *)&opc_dpc_ni,
                              sizeof(opc_dpc_ni), opc_dpc_stat);
    }
    else
    {
        error = DSM_Free(DSM_IsupFtGroupId,
                         DSM_TABLE_ISUP_OPC_DPC,
                         (ITS_OCTET *)&opc_dpc_ni,
                         sizeof(opc_dpc_ni), opc_dpc_stat);
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("DeleteOpcDpcStat: Couldn't free OPC-DPC error %d.\n", 
                        error));

        return error;
    }
   
    return ITS_SUCCESS;
}



/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release row lock held on an entry
 *
 *  Input Parameters:
 *      opc_dpc_stat - OPC-DPC pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_ReleaseOpcDpcStat(ISUP_OPC_DPC_STAT *opc_dpc_stat, ITS_BOOLEAN isdsmlocal)
{
    int error;

    /* Mask Priority bits out of SIO */
    MTP3_HDR_SET_SIO(opc_dpc_stat->opc_dpc_ni, 
                     (ITS_OCTET)(MTP3_HDR_GET_SIO(opc_dpc_stat->opc_dpc_ni) &
                                 (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)));

    /* Mask SLS bits out of routing lebel */
    MTP3_RL_SET_SLS(opc_dpc_stat->opc_dpc_ni.label, 0);

    /*
     * commit to OPC-DPC hash table
     */
    
    if (isdsmlocal == ITS_TRUE)
    {
        error = DSM_CommitLocal(DSM_IsupFtGroupId,
                          DSM_TABLE_ISUP_OPC_DPC,
                          (ITS_OCTET *)&(opc_dpc_stat->opc_dpc_ni),
                          sizeof(opc_dpc_stat->opc_dpc_ni), opc_dpc_stat);
    }
    else
    {
        error = DSM_Commit(DSM_IsupFtGroupId,
                          DSM_TABLE_ISUP_OPC_DPC,
                          (ITS_OCTET *)&(opc_dpc_stat->opc_dpc_ni),
                          sizeof(opc_dpc_stat->opc_dpc_ni), opc_dpc_stat);
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ReleaseOpcDpcStat: Could not commit error %d.\n", error));

        /* FIXME: May need to call DSM_Free() */

       return (error);
    }


    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update an OPC DPC entry with new values
 *
 *  Input Parameters:
 *      key
 *      ent
 *      in
 *      out
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Congestion level in outgoing REL
 *                           # 488          related changes.
 ****************************************************************************/
int
ISUP_PrintOpcDpcStat(ITS_POINTER entry, void *in, void *out)
{
    char *remote_isup_stat = "UNAVAILABLE";
    char *isup_rmt_conglev = "ISUP REMOTE CONGES OFF";
    char *isup_loc_conglev = "ISUP LOCAL CONGES OFF";

    ISUP_OPC_DPC_STAT *opc_dpc_stat = (ISUP_OPC_DPC_STAT *)entry;

    if (opc_dpc_stat == NULL)
    {
        return !ITS_SUCCESS;
    }

    ISUP_DEBUG(("---- PRINT OPC-DPC STAT -----\n"));

    ISUP_DEBUG(("MTP3_HEADER = SIO:%02x OPC:%08x DPC:%08x \n",
           MTP3_HDR_GET_SIO(opc_dpc_stat->opc_dpc_ni),
           MTP3_RL_GET_OPC_VALUE(opc_dpc_stat->opc_dpc_ni.label),
           MTP3_RL_GET_DPC_VALUE(opc_dpc_stat->opc_dpc_ni.label)));

    ISUP_PrintTmrHndl(opc_dpc_stat);

    switch(opc_dpc_stat->isup_rmt_conglev)
    {
    case ISUP_RMT_CONGES_OFF:
        isup_rmt_conglev =  "ISUP REMOTE CONGES OFF";
        break;
    case ISUP_RMT_CONGES_LEVEL1:
        isup_rmt_conglev = "ISUP REMOTE CONGES LEVEL 1";
        break;
    case ISUP_RMT_CONGES_LEVEL2:
        isup_rmt_conglev = "ISUP REMOTE CONGES LEVEL 2";
        break;
    case ISUP_RMT_CONGES_LEVEL3:
        isup_rmt_conglev = "ISUP REMOTE CONGES LEVEL 3";
        break;
    }

    ISUP_DEBUG(("REMOTE CONGESTION INDICATOR = %s \n",
                isup_rmt_conglev));

    switch(opc_dpc_stat->isup_loc_conglev)
    {
    case ISUP_LOC_CONGES_OFF:
        isup_loc_conglev =  "ISUP LOCAL CONGES OFF";
        break;

    case ISUP_LOC_CONGES_LEVEL1:
        isup_loc_conglev = "ISUP LOCAL CONGES LEVEL 1";
        break;

    case ISUP_LOC_CONGES_LEVEL2:
        isup_loc_conglev = "ISUP LOCAL CONGES LEVEL 2";
        break;

    case ISUP_LOC_CONGES_LEVEL3:
    default:
       break;
    }

    ISUP_DEBUG(("LOCAL CONGESTION INDICATOR = %s \n",
                isup_loc_conglev));

    switch(opc_dpc_stat->remote_isup_stat)
    {
    case ISUP_REMOTE_AVAILABLE:
        remote_isup_stat =  "AVAILABLE";
        break;
    case ISUP_REMOTE_UNAVAILABLE:
        remote_isup_stat = "UNAVAILABLE";
        break;
    case ISUP_REMOTE_UNEQUIPPED:
        remote_isup_stat = "UNEQUIPPED";
        break;
    }

    ISUP_DEBUG(("REMOTE ISUP STATUS = %s \n", remote_isup_stat));

    ISUP_DEBUG(("DESTINATION STATUS = %s \n", 
                 opc_dpc_stat->dest_stat ? "REACHABLE" : "UNREACHABLE"));

    ISUP_DEBUG(("----- PRINT OPC-DPC STAT DONE -----\n"));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information about all opc dpc pairs
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
int
ISUP_PrintAllOpcDpcStat()
{
    int ret;

    ISUP_DEBUG(("----- PRINT OPC-DPC STAT TABLE -----\n"));

    ret = DSM_TableIterate(DSM_IsupFtGroupId,
                           DSM_TABLE_ISUP_OPC_DPC,
                           NULL,
                           NULL,
                           ISUP_PrintOpcDpcStat);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("PrintAllOpcDpcStat: Could not iterate, error %d.\n", ret));

        return ret;
    }

    ISUP_DEBUG(("----- PRINT OPC-DPC STAT TABLE DONE -----\n"));

    return (ITS_SUCCESS);
}

/*
 * VCIC and PCIC Tables are based on the principles of the DSM API since they 
 * will eventually be put in shared memory. Actually they information is only
 * allocated and stored once. The pointer to the information is stored in two
 * tables so as to allow lookup (find) by vcic or pcic.
 *
 * One of the fields in the structure is a row level lock. This lock is
 * acquired when you do an Alloc() or Find(). The user is responsible for
 * calling the Release function to release the row level lock. The lock
 * is released by calling Release() or Delete().
 *
 * Alloc and Find return the actual pointer in hash table so data can be
 * modified directly but all changes or lookup should be done before
 * calling Release.
 */

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize VCIC structure with initial default values 
 *
 *  Input Parameters:
 *      cic_info - pointer to structure
 *      vcic - virtual cic
 *      pcic - physical cic
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_InitCic(ISUP_CIC_INFO *cic_info, ITS_CTXT vcic, ISUP_PCIC pcic,
                                                       ITS_OCTET cicRule)
{
    int i;

    cic_info->vcic     = vcic;
    cic_info->pcic     = pcic;
    cic_info->cic_rule = cicRule;
    cic_info->resrv_ind = ITS_FALSE;
    
#if defined(CCITT)
    ISUP_CICStateFromParts_CCITT(&cic_info->cic_state, CKTS_LRBLOCKED, 
                                 CKTS_IDLE_CTK, CKTS_ACTIVE);
#elif defined(ANSI)
    cic_info->cic_state = CKTS_IDLE_LBLOCKED;
#endif

    cic_info->fsm_state = IDLE;
    cic_info->pre_susp_state = IDLE;

    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        cic_info->pndg_tmrs[i].tmr_id = -1;
        cic_info->pndg_tmrs[i].tmr_serial = TIMER_BAD_SERIAL;
    }

    cic_info->cpc_msg_len = 0;

#if defined(CCITT)
    cic_info->bls_state = BLS_LBLOCKED;
    cic_info->blr_state = BLR_RBLOCKED;
    cic_info->hlb_state = HLB_IDLE;  
    cic_info->hrb_state = HRB_IDLE;
    cic_info->hgbs_state = HGBS_IDLE;
    cic_info->hgbr_state = HGBR_IDLE;
    cic_info->ssi_state =  SSI_IDLE; 
#elif defined(ANSI)
    cic_info->bls_state = BLS_IDLE;
    cic_info->blr_state = BLR_IDLE;
    cic_info->dco_state = DCO_IDLE;
#endif

    cic_info->cro_state = CRO_IDLE;
    cic_info->cco_state = CCO_IDLE;
    cic_info->cci_state = CCI_IDLE;
    cic_info->cri_state = CRI_IDLE;
    cic_info->cot_first_ind = ITS_TRUE;

    cic_info->mgbs_state = MGBS_IDLE;
    cic_info->mgbr_state = MGBR_IDLE;
    cic_info->crs_state = CRS_IDLE;
    cic_info->crr_state = CRR_IDLE;
    cic_info->cgrs_state = CGRS_IDLE;
    cic_info->cgrr_state = CGRR_IDLE;
#if defined(ANSI)
    cic_info->cvts_state = CVTS_IDLE;
    cic_info->cvtr_state = CVTR_IDLE;
#endif
    cic_info->reset_flag = RESET_FROM_CC;

    cic_info->ovld_indic = ITS_FALSE;
    cic_info->cntT1 = 0;
    cic_info->cntT12 = 0;
    cic_info->cntT13 = 0;
    cic_info->cntT14 = 0;
    cic_info->cntT15 = 0;
    cic_info->cntT16 = 0;
    cic_info->cntT17 = 0;
    cic_info->cntT18 = 0;
    cic_info->cntT19 = 0;
    cic_info->cntT20 = 0;
    cic_info->cntT21 = 0;
    cic_info->cntT22 = 0;
#if defined(ANSI)
    cic_info->cntTCVT = 0;
#endif
#if defined(CCITT)
    cic_info->lastOverlenMsg = 0;
#endif

    for (i = 0; i < PEG_ISUP_CIC_NUM_PEGS; i++)
    {
        cic_info->pegs[i] = 0;
    }

    cic_info->ISUP_CIC_PEGS.name = "ISUP"; 
    cic_info->ISUP_CIC_PEGS.numPegs = sizeof(cic_info->pegs)/sizeof(ITS_UINT); 
    cic_info->ISUP_CIC_PEGS.pegs = cic_info->pegs;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Initialize CIC message structure with initial default values 
 *
 *  Input Parameters:
 *      cic_info - pointer to associated cic record
 *      cic_msg - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_InitCicMsgBuf(ISUP_CIC_INFO *cic_info, ISUP_CIC_MSG_INFO *cic_msg)
{
    cic_msg->pcic = cic_info->pcic;
    cic_msg->cgb_msg_len = 0;
    cic_msg->cgu_msg_len = 0;
    cic_msg->grs_msg_len = 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Clear VCIC structure 
 *
 *  Input Parameters:
 *      cic_info - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_ClearCic(ISUP_CIC_INFO *cic_info)
{
#if defined(CCITT)
    ISUP_CIC_SET_CALL(cic_info->cic_state, CKTS_IDLE_CTK);
#elif defined(ANSI)
    cic_info->cic_state = (ITS_OCTET)((cic_info->cic_state & 0xF3) | 0x0C);
#endif

    cic_info->fsm_state = IDLE;
    cic_info->pre_susp_state = IDLE;

    cic_info->resrv_ind = ITS_FALSE;
    cic_info->cpc_msg_len = 0;
    cic_info->ovld_indic = ITS_FALSE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Free Cic structure
 *
 *  Input Parameters:
 *      cic_info - pointer to structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success
 *      any other value for failure
 ****************************************************************************/
int
ISUP_FreeCic(ISUP_CIC_INFO *cic_info)
{
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy Cic structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS.
 ****************************************************************************/
int
ISUP_CopyCic(ISUP_CIC_INFO *dest, ISUP_CIC_INFO *src)
{
    int i;

    dest->vcic = src->vcic;
    dest->pcic = src->pcic;
    
    dest->cic_state = src->cic_state;
    dest->fsm_state = src->fsm_state;
    dest->pre_susp_state = src->pre_susp_state;
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        dest->pndg_tmrs[i] = src->pndg_tmrs[i];
    }
 
    memcpy(dest->cpc_msg, src->cpc_msg, src->cpc_msg_len);
    dest->cpc_msg_len = src->cpc_msg_len;

    dest->bls_state = src->bls_state;
    dest->blr_state = src->blr_state;
    dest->mgbs_state = src->mgbs_state;
    dest->mgbr_state = src->mgbr_state;
#if defined(CCITT)
    dest->hlb_state = src->hlb_state;
    dest->hrb_state = src->hrb_state;
    dest->hgbs_state = src->hgbs_state;
    dest->hgbr_state = src->hgbr_state;
#endif
    dest->crs_state = src->crs_state;
    dest->crr_state = src->crr_state;
    dest->cgrs_state = src->cgrs_state;
    dest->cgrr_state = src->cgrr_state;
#if defined(ANSI)
    dest->cvts_state = src->cvts_state;
    dest->cvtr_state = src->cvtr_state;
#endif
    dest->reset_flag = src->reset_flag;

    dest->ovld_indic = ITS_FALSE;
    dest->cntT1 = src->cntT1;
    dest->cntT12 = src->cntT12;
    dest->cntT13 = src->cntT13;
    dest->cntT14 = src->cntT14;
    dest->cntT15 = src->cntT15;
    dest->cntT16 = src->cntT16;
    dest->cntT17 = src->cntT17;
    dest->cntT18 = src->cntT18;
    dest->cntT19 = src->cntT19;
    dest->cntT20 = src->cntT20;
    dest->cntT21 = src->cntT21;
    dest->cntT22 = src->cntT22;
#if defined(ANSI)
    dest->cntTCVT = src->cntTCVT;
#endif

    memcpy(dest->PAM_allowed, src->PAM_allowed, 2);

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in DSM table for information 
 *      pertaining to a CIC.
 *
 *  Input Parameters:
 *      vcic - virtual CIC.
 *      pcic - physical CIC
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to space allocated 
 *      NULL - any error
 ****************************************************************************/
ISUP_CIC_INFO *
ISUP_AllocCic(ITS_CTXT vcic, ISUP_PCIC pcic, ITS_OCTET cicRule)
{
    ISUP_CIC_INFO *cic_info;

    ISUP_CIC_MSG_INFO *cic_msg_buf;

    int error;

    /* find entry */

    cic_info = (ISUP_CIC_INFO *)DSM_Find(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_PCIC,
                                         (ITS_OCTET *)&pcic,
                                         sizeof(pcic), &error);

    if (error == ITS_SUCCESS)
    {
        /* entry is already present */

        ISUP_CRITICAL(("AllocCic: CIC already allocated. vcic %d pcic %x\n", 
                        vcic, pcic));

        /* commit to release the row lock */

        error = DSM_UnlockRow(DSM_IsupFtGroupId,
                              DSM_TABLE_ISUP_PCIC,
                              (ITS_OCTET *)&pcic,
                              sizeof(pcic), cic_info);

        if (error != ITS_SUCCESS)
        {
            ISUP_ERROR(("AllocCic: Could not unlock row existing CIC vcic %d "
                        "pcic %x.\n", vcic, pcic));
        }

        return (NULL);
    }

    if (error != ITS_ENOTFOUND)
    {
        /* DSM internal error */

        ISUP_CRITICAL(("AllocCic: vcic %d pcic %x Error %d.\n", 
                        vcic, pcic, error));
   
        return (NULL);
    }

    if (error == ITS_ENOTFOUND)
    {
        /* Entry not present in table, so allocate new one */

        ISUP_DEBUG(("AllocCic: going to allocate cic vcic %d pcic %x.\n", 
                     vcic, pcic));

        /* allocate memory */

        cic_info = (ISUP_CIC_INFO *)DSM_Alloc(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_PCIC,
                                             (ITS_OCTET *)&pcic,
                                             sizeof(pcic),
                                             sizeof(ISUP_CIC_INFO),
                                             &error);
        if (error != ITS_SUCCESS)
        {
            /* DSM alloc failed */

            switch(error)
            {
            case (ITS_EBADMUTEX):
                ISUP_CRITICAL(("AllocCic: Couldn't acquire mutex vcic %d "
                               "pcic %x.\n", vcic, pcic));
                break;
            case (ITS_ENOMEM):
                ISUP_CRITICAL(("AllocCic: No Memory vcic %d pcic %x.\n", 
                                vcic, pcic));
                break;
            default:
                ISUP_CRITICAL(("AllocCic: Error %d vcic %d pcic %x.\n", 
                                error, vcic, pcic));
                break;
            }

            return (NULL);
        }    
    }
                   
    /* initialize with default values */
    ISUP_InitCic(cic_info, vcic, pcic, cicRule);

    cic_msg_buf = ISUP_AllocCicMsgBuf(cic_info);
    if (cic_msg_buf == NULL)
    {
        ISUP_CRITICAL(("AllocCic: Error %d vcic %d pcic %x.\n",
                        error, vcic, pcic));
        return NULL;
    }

    /* return pointer to hash table entry, so no local copy */
    return (cic_info);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space for CICs in a range
 *
 *  Input Parameters:
 *      start_vcic - starting virtual CIC.
 *      start_pcic - starting physical CIC.
 *      num_cics - number of CICs in range.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS on success
 *      other value on error
 ****************************************************************************/
int
ISUP_AllocCics(ITS_CTXT start_vcic, ISUP_PCIC start_pcic,
               ITS_USHORT num_cics, ITS_OCTET cicRule)
{
    ITS_USHORT i = 0;
    ITS_CTXT vcic = start_vcic;
    ISUP_PCIC pcic = start_pcic;
    ITS_UINT opc = 0;
    ITS_UINT dpc = 0;
    ITS_OCTET ni = 0;
    ITS_USHORT cic = 0;
    ISUP_CIC_INFO *cic_info;
    
    /* Get opcid, dpcid, start_cic from start_pcic */
    ISUP_PCICToParts(pcic, &opc, &dpc, &ni, &cic);

    /* in a loop, allocate entry for each CIC */
    
    for (i = 0; i < num_cics; i++, vcic++, cic++)
    {
        ISUP_PCICFromParts(&pcic, opc, dpc, ni, cic);
        cic_info = ISUP_AllocCic(vcic, pcic, cicRule);

        if (cic_info == NULL)
        {
            return ITS_ENOMEM;
        }

        ISUP_ReleaseCic(cic_info, ITS_FALSE);
    }

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in the hash table for information pertaining to 
 *      a PCIC.
 *
 *  Input Parameters:
 *      pcic - the pysical CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - no entry in hash table or internal error
 *      other - pointer to hash table entry
 ****************************************************************************/
ISUP_CIC_INFO *
ISUP_FindPcic(ISUP_PCIC pcic, ITS_BOOLEAN isdsmlocal)
{
    ISUP_CIC_INFO *cic_info = NULL;
    int error = ITS_EINUSE;

    if (isdsmlocal == ITS_TRUE)
    {
        cic_info = (ISUP_CIC_INFO*) DSM_FindLocal(DSM_IsupFtGroupId,
                                                DSM_TABLE_ISUP_PCIC,
                                                (ITS_OCTET*)&pcic,
                                                sizeof(pcic), &error);
    }
    else
    {
        cic_info = (ISUP_CIC_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                               DSM_TABLE_ISUP_PCIC,
                                               (ITS_OCTET*)&pcic,
                                               sizeof(pcic), &error);
    }

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);
       
        /* do a DSM_Find() again */
        if (isdsmlocal == ITS_TRUE)
        {
            cic_info = (ISUP_CIC_INFO*) DSM_FindLocal(DSM_IsupFtGroupId,
                                                    DSM_TABLE_ISUP_PCIC,
                                                    (ITS_OCTET*)&pcic,
                                                    sizeof(pcic), &error);
        }
        else
        {
            cic_info = (ISUP_CIC_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                                   DSM_TABLE_ISUP_PCIC,
                                                   (ITS_OCTET*)&pcic,
                                                   sizeof(pcic), &error);
        }
    }

    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ISUP_ERROR(("FindPcic: Couldn't acquire mutex pcic %x.\n", pcic));

            break;
        case (ITS_ENOTFOUND):
            ISUP_WARNING(("FindPcic: Can't find CIC pcic %x.\n", pcic));

            break;
        default:
            ISUP_WARNING(("FindPcic: Can't find CIC pcic %x error %d.\n", 
                           pcic, error));

            break;
        }

        return (NULL);
    }

    /* no need for local copy since actual hash table pointer is returned */

    /* To assign correct address pointer */
    cic_info->ISUP_CIC_PEGS.pegs = cic_info->pegs;
    
    return cic_info;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in the hash table for information pertaining to 
 *      a give PCIC message bufffer.
 *
 *  Input Parameters:
 *      pcic - the pysical CIC.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      NULL - no entry in hash table or internal error
 *      other - pointer to hash table entry
 ****************************************************************************/
ISUP_CIC_MSG_INFO *
ISUP_FindPcicMsgBuf(ISUP_PCIC pcic, ITS_BOOLEAN findFlag, ITS_BOOLEAN isdsmlocal)
{
    ISUP_CIC_MSG_INFO *cic_msg = NULL;
    int error = ITS_EINUSE;

    if (findFlag == ITS_TRUE)
    {
       if (isdsmlocal == ITS_TRUE)
       {
           cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindLocal(DSM_IsupFtGroupId,
                                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                              (ITS_OCTET*)&pcic,
                                              sizeof(pcic), &error);
       }
       else
       {
           cic_msg = (ISUP_CIC_MSG_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                          DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                          (ITS_OCTET*)&pcic,
                                          sizeof(pcic), &error);
       }

    }
    else
    {
       if (isdsmlocal == ITS_TRUE)
       {
           cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindNoLockLocal(DSM_IsupFtGroupId,
                                          DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                          (ITS_OCTET*)&pcic,
                                          sizeof(pcic), &error);
       }
       else
       {
           cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindNoLock(DSM_IsupFtGroupId,
                                          DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                          (ITS_OCTET*)&pcic,
                                          sizeof(pcic), &error);
       }
    }

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */
        TIMERS_USleep(100);
       
        if (findFlag == ITS_TRUE)
        {
           /* do a DSM_Find() again */
           if (isdsmlocal == ITS_TRUE)
           {
               cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindLocal(DSM_IsupFtGroupId,
                                                  DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                                  (ITS_OCTET*)&pcic,
                                                  sizeof(pcic), &error);
           }
           else
           {
               cic_msg = (ISUP_CIC_MSG_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                              (ITS_OCTET*)&pcic,
                                              sizeof(pcic), &error);
           }
        }
        else
        {
           if (isdsmlocal == ITS_TRUE)
           {
               cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindNoLockLocal(DSM_IsupFtGroupId,
                                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                              (ITS_OCTET*)&pcic,
                                              sizeof(pcic), &error);
           }
           else
           {
               cic_msg = (ISUP_CIC_MSG_INFO*) DSM_FindNoLock(DSM_IsupFtGroupId,
                                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                              (ITS_OCTET*)&pcic,
                                              sizeof(pcic), &error);
           }
        }
    }

    if (error != ITS_SUCCESS)
    {
       switch(error)
       {
       case (ITS_EBADMUTEX):
          ISUP_ERROR(("FindPcicMsgBuf: Couldn't acquire mutex pcic %x.\n", 
                      pcic));
          break;
       case (ITS_ENOTFOUND):
          ISUP_WARNING(("FindPcicMsgBuf: Can't find CIC pcic %x.\n", pcic));
          break;
       default:
          ISUP_WARNING(("FindPcicMsgBuf: Can't find CIC pcic %x error %d.\n", 
                         pcic, error));
          break;
       }

       return (NULL);
    }

    /* no need for local copy since actual hash table pointer is returned */

    return cic_msg;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete an entry in the hash tables for information pertaining to 
 *      a CIC.
 *
 *  Input Parameters:
 *      pcic - pysical CIC
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_DeleteCic(ISUP_PCIC pcic)
{
    ISUP_CIC_INFO *cic_info = NULL;
    ISUP_CIC_MSG_INFO *cic_msg = NULL;
    int error;

    cic_info = (ISUP_CIC_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                           DSM_TABLE_ISUP_PCIC,
                                           (ITS_OCTET*)&pcic,
                                           sizeof(pcic), &error);

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);
       
        /* do a DSM_Find() again */

        cic_info = (ISUP_CIC_INFO*) DSM_Find(DSM_IsupFtGroupId,
                                               DSM_TABLE_ISUP_PCIC,
                                               (ITS_OCTET*)&pcic,
                                               sizeof(pcic), &error);
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("DeleteCic: Couldn't find cic pcic %x "
                       "error %d.\n", pcic, error));

        return error;
    }

    error = DSM_Free(DSM_IsupFtGroupId,
                     DSM_TABLE_ISUP_PCIC,
                     (ITS_OCTET *)&pcic,
                     sizeof(pcic), cic_info);

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("DeleteCic: Couldn't free cic pcic %x "
                       "error %d.\n", pcic, error));

        return error;
    }

    cic_msg = ISUP_FindPcicMsgBuf(pcic, ITS_TRUE, ITS_FALSE);
    
    error = DSM_Free(DSM_IsupFtGroupId,
                     DSM_TABLE_ISUP_PCIC_CSC_MSG,
                     (ITS_OCTET *)&pcic,
                     sizeof(pcic), cic_msg); 
   
    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release row lock held on an entry
 *
 *  Input Parameters:
 *      cic_info - cic info pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_ReleaseCic(ISUP_CIC_INFO *cic_info, ITS_BOOLEAN isdsmlocal)
{
    int error;

    /* 
     * commit to PCIC hash table 
     */


    if (isdsmlocal == ITS_TRUE)
    {
        error = DSM_CommitLocal(DSM_IsupFtGroupId,
                               DSM_TABLE_ISUP_PCIC,
                               (ITS_OCTET *)&(cic_info->pcic),
                               sizeof(cic_info->pcic), cic_info);
    }
    else
    {
        error = DSM_Commit(DSM_IsupFtGroupId,
                          DSM_TABLE_ISUP_PCIC,
                          (ITS_OCTET *)&(cic_info->pcic),
                          sizeof(cic_info->pcic), cic_info);
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ReleaseCic: Could not commit error %d vcic %d "
                       "pcic %x.\n", error, cic_info->vcic, cic_info->pcic));
       
        /* FIXME: May need to call DSM_Free() */

       return (error);
    }

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Release row lock held on an entry
 *
 *  Input Parameters:
 *      cic_info - cic info pointer.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      any other value - failure
 ****************************************************************************/
int
ISUP_ReleaseCicMsgBuf(ISUP_CIC_MSG_INFO *cic_msg, ITS_BOOLEAN commitFlag,
                                                  ITS_BOOLEAN isdsmlocal)
{
    int error;

    /* 
     * commit to PCIC_CSC_MSG hash table 
     */
    if (commitFlag == ITS_TRUE)
    {
       if (isdsmlocal == ITS_TRUE)
       {
           error = DSM_CommitLocal(DSM_IsupFtGroupId,
                                   DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                   (ITS_OCTET *)&(cic_msg->pcic),
                                   sizeof(cic_msg->pcic), cic_msg);
       }
       else
       {
           error = DSM_Commit(DSM_IsupFtGroupId,
                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                              (ITS_OCTET *)&(cic_msg->pcic),
                              sizeof(cic_msg->pcic), cic_msg);
       } 

    }
    else
    {
       if (isdsmlocal == ITS_TRUE)
       {
           error = DSM_CommitNoLockLocal(DSM_IsupFtGroupId,
                                   DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                   (ITS_OCTET *)&(cic_msg->pcic),
                                   sizeof(cic_msg->pcic), cic_msg);
       }
       else
       {
           error = DSM_CommitNoLock(DSM_IsupFtGroupId,
                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                              (ITS_OCTET *)&(cic_msg->pcic),
                              sizeof(cic_msg->pcic), cic_msg);
       }
    }

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ReleaseCicMsgBuf: Could not commit error %d "
                       "pcic %x.\n", error, cic_msg->pcic));
        /* FIXME: May need to call DSM_Free() */
       return (error);
    }
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in DSM table for information 
 *      pertaining to message store for the given CIC.
 *
 *  Input Parameters:
 *      cic_info - Cic record
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
ISUP_CIC_MSG_INFO *
ISUP_AllocCicMsgBuf(ISUP_CIC_INFO *cic_info)
{
    int error;
    ISUP_CIC_MSG_INFO *cic_msg;

    /* find entry */

    cic_msg = (ISUP_CIC_MSG_INFO *)DSM_Find(DSM_IsupFtGroupId,
                                   DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                   (ITS_OCTET *)&cic_info->pcic,
                                   sizeof(cic_info->pcic), &error);

    if (error == ITS_SUCCESS)
    {
        /* entry is already present */
        ISUP_CRITICAL(("AllocCicMsgBuf: CIC message buffer already allocated "
                       "for vcic %d pcic %x\n", cic_info->vcic, 
                        cic_info->pcic));

        /* commit to release the row lock */
        error = DSM_UnlockRow(DSM_IsupFtGroupId,
                              DSM_TABLE_ISUP_PCIC_CSC_MSG,
                              (ITS_OCTET *)&cic_info->pcic,
                              sizeof(cic_info->pcic), cic_msg);
        if (error != ITS_SUCCESS)
        {
            ISUP_ERROR(("AllocCicMsgBuf: Could not unlock row for existing"
                        " CIC message Buffer vcic %d pcic %x.\n", 
                        cic_info->vcic, cic_info->pcic));
        }
        return (cic_msg);
    }
    else if (error != ITS_ENOTFOUND)
    {
        /* DSM internal error */
        ISUP_CRITICAL(("AllocCicMsgBuf: cic_info>vcic %d cic_info>pcic %x "
                       "Error %d.\n", cic_info->vcic, cic_info->pcic, error));
        return (NULL);
    }
    else if (error == ITS_ENOTFOUND)
    {
        /* Entry not present in table, so allocate new one */
        ISUP_DEBUG(("AllocCicMsgBuf: Going to allocate cic message buf "
                    "vcic %d pcic %x.\n", cic_info->vcic, cic_info->pcic));

        /* allocate memory */

        cic_msg = (ISUP_CIC_MSG_INFO *)DSM_Alloc(DSM_IsupFtGroupId,
                                        DSM_TABLE_ISUP_PCIC_CSC_MSG,
                                        (ITS_OCTET *)&cic_info->pcic,
                                        sizeof(cic_info->pcic),  
                                        sizeof(ISUP_CIC_MSG_INFO),
                                        &error);

        if (error != ITS_SUCCESS)
        {
            /* DSM Alloc failed */
            switch(error)
            {
            case (ITS_EBADMUTEX):
                ISUP_CRITICAL(("AllocCicMsgBuf: Couldn't acquire mutex vcic %d "
                               "pcic %x.\n", cic_info->vcic, cic_info->pcic));
                break;
            case (ITS_ENOMEM):
                ISUP_CRITICAL(("AllocCicMsgBuf: No Memory vcic %d pcic %x.\n", 
                                cic_info->vcic, cic_info->pcic));
                break;
            default:
                ISUP_CRITICAL(("AllocCicMsgBuf: Error %d vcic %d pcic %x.\n", 
                                error, cic_info->vcic, cic_info->pcic));
                break;
            }
            return (NULL);
        }    
    }
                   
    /* initialize with default values */
    ISUP_InitCicMsgBuf(cic_info, cic_msg);


    /* TRUE: Lock, FALSE: Nolock */
    ISUP_ReleaseCicMsgBuf(cic_msg, ITS_TRUE, ITS_FALSE);

    /* return pointer to hash table entry, so no local copy */
    return (cic_msg);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information on a CIC.
 *
 *  Input Parameters:
 *      key
 *      ent
 *      in
 *      out
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
int
ISUP_PrintCic(ITS_POINTER entry, void *in, void *out)
{
    ISUP_CIC_INFO *cic_info = (ISUP_CIC_INFO *)entry;
    ITS_UINT i;

    ISUP_DEBUG(("---- PRINT CIC -----\n"));

    ISUP_DEBUG(("Virtual CIC = %d \n", cic_info->vcic));

    ISUP_DEBUG(("Physical CIC = SIO:%02x OPC:%08x DPC:%08x CIC:%04x \n",
           MTP3_HDR_GET_SIO(cic_info->pcic.hdr),
           MTP3_RL_GET_OPC_VALUE(cic_info->pcic.hdr.label),
           MTP3_RL_GET_DPC_VALUE(cic_info->pcic.hdr.label),
           cic_info->pcic.cic));

    ISUP_DEBUG(("CIC Rule = %s \n", ISUP_CkgpCtrlToString(cic_info->cic_rule)));

    ISUP_DEBUG(("CIC State = %d \n", cic_info->cic_state));

    ISUP_DEBUG(("FSM State = %d \n", cic_info->fsm_state));

    ISUP_DEBUG(("Pre Suspend State = %d \n", cic_info->pre_susp_state));

    /* TODO: Print MTP3 header */

    ISUP_PrintAllPndgTmrs(cic_info);

    ISUP_DEBUG(("Stored CPC  Message Length = %d \n", cic_info->cpc_msg_len));

    for (i = 0; i < cic_info->cpc_msg_len; i++)
    {
        printf("0x%0x ", cic_info->cpc_msg[i]);
    }
    printf("\n");

    /* TODO: Print Stored CSC message */

    ISUP_DEBUG(("BLS state: %d \n", cic_info->bls_state));
    
    ISUP_DEBUG(("BLR state: %d \n", cic_info->blr_state));

    ISUP_DEBUG(("MGBS state: %d \n", cic_info->mgbs_state));

    ISUP_DEBUG(("MGBR state: %d \n", cic_info->mgbr_state));

#if defined(CCITT)
    ISUP_DEBUG(("HLB state: %d \n", cic_info->hlb_state));

    ISUP_DEBUG(("HRB state: %d \n", cic_info->hrb_state));

    ISUP_DEBUG(("HGBS state: %d \n", cic_info->hgbs_state));

    ISUP_DEBUG(("HGBR state: %d \n", cic_info->hgbr_state));
#endif

#if defined(ANSI)
    ISUP_DEBUG(("CVTS state: %d \n", cic_info->cvts_state));
    ISUP_DEBUG(("CVTR state: %d \n", cic_info->cvtr_state));
    ISUP_DEBUG(("CCO state: %d \n", cic_info->cco_state));
    ISUP_DEBUG(("CCI state: %d \n", cic_info->cci_state));
    ISUP_DEBUG(("CRO state: %d \n", cic_info->cro_state));
    ISUP_DEBUG(("CRI state: %d \n", cic_info->cri_state));
    ISUP_DEBUG(("DCO state: %d \n", cic_info->dco_state));
#endif

    ISUP_DEBUG(("PAM allowed: 0x%0x 0x%0x \n", cic_info->PAM_allowed[0],
                                             cic_info->PAM_allowed[1]));

    ISUP_DEBUG(("----- PRINT CIC DONE -----\n"));

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information on all the CICs.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      ITS_EBADMUTEX - failure
 ****************************************************************************/
int
ISUP_PrintAllCics()
{
    int ret;

    ISUP_DEBUG(("----- PRINT CIC TABLE -----\n"));
    
    ret = DSM_TableIterate(DSM_IsupFtGroupId,
                           DSM_TABLE_ISUP_PCIC,
                           NULL,
                           NULL,
                           ISUP_PrintCic);
    if (ret != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("PrintAllCics: Could not iterate, error %d.\n", ret));

        return ret;
    }

    ISUP_DEBUG(("----- PRINT CIC TABLE DONE -----\n"));

    return (ITS_SUCCESS);
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information about all opc dpc pairs
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success.
 *      any other value - failure
 ****************************************************************************/
void
ISUP_PrintTmrHndl(ISUP_OPC_DPC_STAT *opc_dpc_stat)
{
    ITS_OCTET i;
    ISUP_TMR_HNDL_INFO tmr_info;
    const char *tmr_hndl_str;
    const char *tmr_id_str;
    
    if (opc_dpc_stat == NULL)
    {
        return;
    }

    ISUP_DEBUG(("----- TIMER HANDLING -----\n"));
    
    for (i = 1; i < ITS_ISUP_TIMER_LAST; i++)
    {
        tmr_id_str = ISUP_TimerToString(i);
        if (tmr_id_str == NULL)
        {
            return;
        }

        tmr_info = opc_dpc_stat->tmr_hndl_info[i];
        
        tmr_hndl_str = ISUP_TimerHandlerToString(tmr_info.tmr_hndl_layer);
        if (tmr_hndl_str == NULL)
        {
            return;
        }

        ISUP_DEBUG((" \t %s \t %s \t %d \n", tmr_id_str, tmr_hndl_str, 
                            tmr_info.tmr_value));
    }

    ISUP_DEBUG(("----- TIMER HANDLING DONE -----\n"));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find a pending timer matching an id in the list 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *      timer_id - pending timer id to search
 *      l_pndg_tmr_info - pointer to structure that will be populated
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      pointer to pending timer structure for success case.
 *      NULL for failure.
 ****************************************************************************/
int 
ISUP_FindPndgTmrInfo(ISUP_CIC_INFO *cic_info, ITS_USHORT timer_id,
                     ISUP_PNDG_TMR_INFO* l_pndg_tmr_info)
{
    int i;
    ITS_BOOLEAN found = ITS_FALSE; 

    if (cic_info == NULL || l_pndg_tmr_info == NULL)
    {
        return ITS_ENOTFOUND;
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id == -1)
            continue;
        
        if (cic_info->pndg_tmrs[i].tmr_id == timer_id)
        { 
            found = ITS_TRUE;
            break;
        }
    }

    if (found)
    {
        ISUP_CopyPndgTmr(l_pndg_tmr_info, &cic_info->pndg_tmrs[i]);
        return ITS_SUCCESS;
    }
    else
    {
        return ITS_ENOTFOUND;
    }
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check if a pending timer exists in the list 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *      timer_id - pending timer id to search
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if id exists.
 *      ITS_FALSE otherwise.
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_PndgTmrExists(ISUP_CIC_INFO *cic_info, ITS_USHORT timer_id)
{
    int i;
    ITS_BOOLEAN found = ITS_FALSE; 

    if (cic_info == NULL)
    {
        return ITS_FALSE; 
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id == -1)
            continue;
        
        if (cic_info->pndg_tmrs[i].tmr_id == timer_id)
        { 
            found = ITS_TRUE;
            break;
        }
    }

    return found;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Decide whether to insert an entry at a particular place in the pndg
 *      timers list. (used internally by the List Insert function)
 *
 *  Input Parameters:
 *      prev - prev list entry
 *      next - next list entry
 *      item - list entry to be inserted
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      1 if item should be inserted between prev and next.
 *      0 otherwise.
 ****************************************************************************/
int 
ISUP_PndgTmrInsFunc(LIST_Entry *prev, LIST_Entry *next, LIST_Entry *item)
{
    ISUP_PNDG_TMR_INFO *pndg_tmr_prev;    
    ISUP_PNDG_TMR_INFO *pndg_tmr_next;    
    ISUP_PNDG_TMR_INFO *pndg_tmr_item;

    if (item == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    pndg_tmr_item = (ISUP_PNDG_TMR_INFO *)(item->data);
    
    if ((prev == NULL) && (next == NULL))
    {
        /*
         * the list is empty, so insert it at the beginning
         */
        return 1;
    }

    if ((prev != NULL) && (next == NULL))
    {
        /*
         * this is end of the list so insert here
         */
        return 1;
    }

    if ((prev == NULL) && (next != NULL))
    {
        /*
         * this is first element of the list
         */
        pndg_tmr_next = (ISUP_PNDG_TMR_INFO *)(next->data);    

        if (pndg_tmr_item->tmr_id <= pndg_tmr_next->tmr_id)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if ((prev != NULL) && (next != NULL))
    {
        /*
         * this is in middle of the list
         */
        pndg_tmr_prev = (ISUP_PNDG_TMR_INFO *)(prev->data);    
        pndg_tmr_next = (ISUP_PNDG_TMR_INFO *)(next->data);    

        if ((pndg_tmr_item->tmr_id >= pndg_tmr_prev->tmr_id) && 
            (pndg_tmr_item->tmr_id <= pndg_tmr_next->tmr_id))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    /*
     * should not be reached
     */
    return 0;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Insert pending timer information in the list 
 *
 *  Input Parameters:
 *      cic_info - pointer to cic info
 *      pndg_tmr_info - pointer to pending timer info
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_InsertPndgTmrInfo(ISUP_CIC_INFO *cic_info, ISUP_PNDG_TMR_INFO *pndg_tmr_info)
{
    int i;
    ITS_BOOLEAN vacancy = ITS_FALSE; 

    if (cic_info == NULL || pndg_tmr_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    if (ISUP_PndgTmrExists(cic_info, pndg_tmr_info->tmr_id))
    {
        return ITS_EDUPLENTRY;
    }

    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id == -1)
        {
            vacancy = ITS_TRUE;
            break;
        }
    }

    if (vacancy)
    {
        ISUP_CopyPndgTmr(&cic_info->pndg_tmrs[i], pndg_tmr_info);
        return ITS_SUCCESS;
    }
    else
        return ITS_ENOMSGSPACE;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      To return if the pending timer id of current item matches the id to
 *      matched. It is used internally by the Remove function.
 *
 *  Input Parameters:
 *      item - current item in list
 *      match - data to be matched
 *      mlen - length of data
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      1 for a match.
 *      0 otherwise.
 ****************************************************************************/
int
ISUP_PndgTmrRemFunc(LIST_Entry *item, void *match, int mlen)
{
    ITS_USHORT timer_id;
    ISUP_PNDG_TMR_INFO *pndg_tmr;
    
    if (item == NULL || match == NULL || mlen != sizeof(ITS_USHORT))
    {
        return !ITS_SUCCESS;
    }

    pndg_tmr = (ISUP_PNDG_TMR_INFO *)(item->data);

    timer_id = *((ITS_USHORT *)match);

    if (timer_id == pndg_tmr->tmr_id)
    {
        return !ITS_SUCCESS;
    }
    else
    {
        return ITS_SUCCESS;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete pending timer information for a cic
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *      timer_id - pending timer id o be deleted
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_DeletePndgTmrInfo(ISUP_CIC_INFO *cic_info, ITS_USHORT timer_id)
{
    int i;
    ITS_BOOLEAN found = ITS_FALSE; 

    if (cic_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id == -1)
            continue;
        
        if (cic_info->pndg_tmrs[i].tmr_id == timer_id)
        { 
            found = ITS_TRUE;
            break;
        }
    }

    if (found)
    {
        cic_info->pndg_tmrs[i].tmr_id = -1;
        cic_info->pndg_tmrs[i].tmr_serial = TIMER_BAD_SERIAL;
        return ITS_SUCCESS;
    }
    else
        return ITS_ENOTFOUND;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Update pending timer information for a timer id 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *      timer_id - id to be updated
 *      l_pndg_tmr_info - structure with new values
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_UpdatePndgTmrInfo(ISUP_CIC_INFO *cic_info, ITS_USHORT timer_id, 
                       ISUP_PNDG_TMR_INFO *l_pndg_tmr_info)
{
    int i;
    ITS_BOOLEAN found = ITS_FALSE; 

    if (cic_info == NULL || l_pndg_tmr_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id == -1)
            continue;
        
        if (cic_info->pndg_tmrs[i].tmr_id == timer_id)
        { 
            found = ITS_TRUE;
            break;
        }
    }

    if (found)
    {
        ISUP_CopyPndgTmr(&cic_info->pndg_tmrs[i], l_pndg_tmr_info);
        return ITS_SUCCESS;
    }
    else
    {
        return ITS_ENOTFOUND;
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Check if pndg timer list is empty 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE if list is empty.
 *      ITS_FALSE if list if not empty.
 ****************************************************************************/
ITS_BOOLEAN 
ISUP_IsPndgTmrInfoEmpty(ISUP_CIC_INFO *cic_info)
{
    if (cic_info == NULL)
    {
        return ITS_FALSE;
    }

    return (!ISUP_NumPndgTmrs(cic_info));
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find number of entries in pndg timer list 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int 
ISUP_NumPndgTmrs(ISUP_CIC_INFO *cic_info)
{
    int i;
    int count = 0;

    if (cic_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        if (cic_info->pndg_tmrs[i].tmr_id != -1)
            count++;
    }

    return count;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Delete all pending timers for an cic pair 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure
 ****************************************************************************/
int
ISUP_DeleteAllPndgTmrs(ISUP_CIC_INFO *cic_info)
{
    int i;

    if (cic_info == NULL)
    {
        return !ITS_SUCCESS;
    }
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        cic_info->pndg_tmrs[i].tmr_id = -1;
        cic_info->pndg_tmrs[i].tmr_serial = TIMER_BAD_SERIAL;
    }

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Copy pending timer structure from src to dest 
 *
 *  Input Parameters:
 *      dest - destination structure pointer
 *      src - source structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS for success.
 *      any other value for failure.
 ****************************************************************************/
int
ISUP_CopyPndgTmr(ISUP_PNDG_TMR_INFO *dest, ISUP_PNDG_TMR_INFO *src)
{
    dest->tmr_id = src->tmr_id;
    dest->tmr_serial = src->tmr_serial;

    return ITS_SUCCESS;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print information about a pending timer. 
 *
 *  Input Parameters:
 *      tmr - pointer to pending timer structure
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
void
ISUP_PrintPndgTmr(ISUP_PNDG_TMR_INFO *tmr)
{
    ISUP_DEBUG(("Timer Id = %d, Timer Serial = %d \n", 
           tmr->tmr_id, tmr->tmr_serial));

    return;
}


/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Print all pending timers for a cic. 
 *
 *  Input Parameters:
 *      cic_info - cic structure pointer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None
 ****************************************************************************/
void
ISUP_PrintAllPndgTmrs(ISUP_CIC_INFO *cic_info)
{
    int i;

    if (cic_info == NULL)
    {
        return;
    }

    ISUP_DEBUG(("----- PENDING TIMERS -----\n"));
    
    for (i = 0; i < ISUP_MAX_PNDG_TMRS; i++)
    {
        ISUP_PrintPndgTmr(&cic_info->pndg_tmrs[i]);
    }

    ISUP_DEBUG(("----- PENDING TIMERS DONE -----\n"));

    return;
}

char*
ISUP_GetPegDesc(ITS_UINT peg_index)
{
    if (peg_index < PEG_ISUP_NUM_PEGS)
    {
        return (ISUP_Peg_Desc[peg_index]);
    }
    else
    {
        return "Invalid peg index";
    }
}

char*
ISUP_GetDestPegDesc(ITS_UINT peg_index)
{
    if (peg_index < PEG_ISUP_DEST_NUM_PEGS)
    {
        return (ISUP_Dest_Peg_Desc[peg_index]);
    }
    else
    {
        return "Invalid peg index";
    }
}

char*
ISUP_GetCICPegDesc(ITS_UINT peg_index)
{
    if (peg_index < PEG_ISUP_CIC_NUM_PEGS)
    {
        return (ISUP_CIC_Peg_Desc[peg_index]);
    }
    else
    {
        return "Invalid peg index";
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Finds the circuit Group Info. 
 *
 *  Input Parameters:
 *      opc_dpc_info - ptr to ISUP_OPC_DPC_STAT
 *      ckgp_id - ITS_USHORT variable
 *      l_ckgp_info - ptr to ISUP_CKGP_INFO
 *      exists - ptr to ITS_INT
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Modified function for Finding 
 *                           #421 & #423    Circuit Group to optimise DSM
 *                                          access during STACK initialisation
 ****************************************************************************/

ISUP_CKGP_LIST * ISUP_FindCktGrpInfo (ISUP_OPC_DPC_STAT *opc_dpc_info,
                                      ITS_USHORT ckgp_id,
                                      ISUP_CKGP_INFO* l_ckgp_info,
                                      ITS_INT *exists)
{
    ISUP_CKGP_LIST *ckgp_list = NULL;

    if (opc_dpc_info == NULL)
    {
        *exists = !ITS_SUCCESS;
        return (ckgp_list);
    }

    ckgp_list = ISUP_FindCkgpList(opc_dpc_info->opc_dpc_ni, ITS_FALSE);
    if (ckgp_list == NULL)
    {
        *exists = ITS_ENOTFOUND;
        return (ckgp_list);
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        memcpy(l_ckgp_info, &ckgp_list->ckgp_info[ckgp_id],
               sizeof(ISUP_CKGP_INFO));

        *exists = ITS_SUCCESS;
        return (ckgp_list);
    }

    *exists = ITS_ENOTFOUND;
    return (ckgp_list);
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Updates the circuit Group Info. 
 *
 *  Input Parameters:
 *      opc_dpc_info - ptr to ISUP_OPC_DPC_STAT
 *      ckgp_id - ITS_USHORT variable
 *      l_ckgp_info - ptr to ISUP_CKGP_INFO
 *      ckgp_list - ptr to ISUP_CKGP_LIST
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Modified function for Updating 
 *                           #421 & #423    Circuit Group to optimise DSM
 *                                          access during STACK initialisation
 ****************************************************************************/

int
ISUP_UpdateCktGrpInfo (ISUP_OPC_DPC_STAT *opc_dpc_info,
                       ITS_USHORT ckgp_id,
                       ISUP_CKGP_INFO *l_ckgp_info,
                       ISUP_CKGP_LIST *ckgp_list)
{
    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    if (ckgp_list->ckgp_info[ckgp_id].ckgp_id == ckgp_id)
    {
        if ((l_ckgp_info->usable_cics[0] & 0xFFFFFFFF) == 0x00000000)
        {
            l_ckgp_info->ckgp_id = ISUP_INV_CKGP_ID;
        }

        memcpy(&ckgp_list->ckgp_info[ckgp_id], l_ckgp_info,
               sizeof(ISUP_CKGP_INFO));

        return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    }

    ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
    return ITS_ENOMSG;
}
/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      This function Inserts the circuit Group Info. 
 *
 *  Input Parameters:
 *      opc_dpc_info - ptr to ISUP_OPC_DPC_STAT
 *      ckgp_info - ptr to ISUP_CKGP_INFO
 *      ckgp_list - ptr to ISUP_CKGP_LIST
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   Modified function for Inserting 
 *                           #421 & #423    Circuit Group to optimise DSM  
 *                                          access during STACK initialisation
 ****************************************************************************/

int
ISUP_InsertCktGrpInfo (ISUP_OPC_DPC_STAT *opc_dpc_info,
                       ISUP_CKGP_INFO *ckgp_info,
                       ISUP_CKGP_LIST *ckgp_list)
{
    if (opc_dpc_info == NULL)
    {
        return !ITS_SUCCESS;
    }

    if (ckgp_list == NULL)
    {
        ckgp_list = ISUP_AllocCkgpList(opc_dpc_info->opc_dpc_ni);
        if (ckgp_list == NULL)
        {
            return ITS_ENOMEM;
        }
    }

    memcpy(&ckgp_list->ckgp_info[ckgp_info->ckgp_id],
           ckgp_info, sizeof(ISUP_CKGP_INFO));

    ++ckgp_list->noCkgps;

    ISUP_DEBUG((" ckgpinsert:- gpid %d.\n", ckgp_info->ckgp_id));

    return ISUP_ReleaseCkgpList(ckgp_list, ITS_FALSE);
}





/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Allocate space and add an entry in DSM table for Vcic.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      current_vcic pointer.
 *
 *  Return Value:
 ****************************************************************************/
ITS_CTXT *
ISUP_AllocVcic()
{
    ITS_CTXT *current_vcic = NULL;
    int error;

        /* allocate memory */
    current_vcic = (ITS_CTXT *)DSM_Alloc(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_VCIC,
                                         &isup_vcic_key,
                                         sizeof(ITS_OCTET),
                                         sizeof(ITS_CTXT),
                                         &error);
    if (error != ITS_SUCCESS)
    {
        /* DSM Alloc failed */
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ISUP_CRITICAL(("ISUP_AllocVcic: Couldn't acquire mutex"));
            break;
        case (ITS_ENOMEM):
            ISUP_CRITICAL(("ISUP_AllocVcic: No Memory available\n"));
            break;
        default:
            ISUP_CRITICAL(("ISUP_AllocVcic: Error %d \n", error));
            break;
        }
        return (NULL);
    }
    else
    {
        ISUP_DEBUG(("ISUP_AllocVcic: Allocation Successful\n"));
    }

    /* Initialize the current_vic entry */
    *current_vcic = 1;

    return current_vcic;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Find an entry in DSM table for Vcic value.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      current_vcic pointer.
 *
 *  Return Value:
 ****************************************************************************/
ITS_CTXT *
ISUP_FindVcic()
{
    ITS_CTXT *current_vcic = NULL;
    int error;

    current_vcic = (ITS_CTXT*) DSM_Find(DSM_IsupFtGroupId,
                                         DSM_TABLE_ISUP_VCIC,
                                         &isup_vcic_key,
                                         sizeof(ITS_OCTET), &error);

    while (error == ITS_EINUSE)
    {
        /* sleep for some time */

        TIMERS_USleep(100);

        /* do a DSM_Find() again */

        current_vcic = (ITS_CTXT*) DSM_Find(DSM_IsupFtGroupId,
                                             DSM_TABLE_ISUP_VCIC,
                                             &isup_vcic_key,
                                             sizeof(ITS_OCTET), &error);
    }
    if (error != ITS_SUCCESS)
    {
        switch(error)
        {
        case (ITS_EBADMUTEX):
            ISUP_ERROR(("ISUP_FindVcic: Couldn't acquire mutex.\n"));

            break;
        case (ITS_ENOTFOUND):
            ISUP_WARNING(("ISUP_FindVcic: Can't find ??.\n"));

            break;
        default:
            ISUP_WARNING(("ISUP_FindVcic: Can't  Find the entry %d.\n", error))
;

            break;
        }
        return (NULL);
    }
    return current_vcic;
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit an entry in DSM table for Vcic value.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_SUCCESS/ITS_FAILURE.
 *
 *  Return Value:
 ****************************************************************************/
int
ISUP_ReleaseVcic(ITS_CTXT* current_vcic)
{
    int error;

    if (current_vcic == NULL)
    {
        return !ITS_SUCCESS;
    }

    /*
     * commit it
     */
    error = DSM_Commit(DSM_IsupFtGroupId,
                       DSM_TABLE_ISUP_VCIC,
                       &isup_vcic_key,
                       sizeof(ITS_OCTET), current_vcic);

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ISUP_ReleaseVcic:Commit Failed error %d.\n", error));
        return (error);
    }
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Purpose:
 *      Commit an entry in DSM table for Pcic value.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      ITS_SUCCESS/ITS_FAILURE.
 *
 *  Return Value:
 *
 *  Revision History:
 *  --------------------------------------------------------------------------
 *  Name        Date         Reference      Description
 *  --------------------------------------------------------------------------
 *  Ramesh K V  04-05-2005   BCGI Problem   DSM Alloc problem related changes.
 *                           #496          
 ****************************************************************************/

int
ISUP_ReleasePcic(ISUP_CIC_INFO *cic_info, ISUP_PCIC pcic)
{
    int error;

    /*
     * commit to PCIC hash table
     */
    error = DSM_Commit(DSM_IsupFtGroupId,
                      DSM_TABLE_ISUP_PCIC,
                      (ITS_OCTET *)&pcic,
                      sizeof(pcic), cic_info);

    if (error != ITS_SUCCESS)
    {
        ISUP_CRITICAL(("ReleaseCic: Could not commit error %d vcic %d "
                       "pcic %x.\n", error, cic_info->vcic, cic_info->pcic));

        /* FIXME: May need to call DSM_Free() */

       return (error);
    }

    return (ITS_SUCCESS);
}

