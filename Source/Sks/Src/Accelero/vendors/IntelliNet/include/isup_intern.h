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
 *  ID: $Id: isup_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:47  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/13 09:21:59  cvsadmin
 * LOG: update from MSC
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:35:04  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.3  2005/04/06 10:24:39  ssingh
 * LOG: ISUP Bug Fix propagation. (kramesh)
 * LOG:
 * LOG: Revision 9.2  2005/04/05 10:51:15  smanish
 * LOG: Implementation of changes based on design doc ACC651-SDS-PENH-1.0.02.
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:54:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.26  2005/03/21 13:53:20  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.6  2005/02/25 07:07:19  ssingh
 * LOG: APIs for Destination Specific pegs. (Ramesh KV)
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.5  2005/01/31 10:45:33  snagesh
 * LOG: Moved ISUP management data from ss7_mgmt.h
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.4  2005/01/05 10:47:12  craghavendra
 * LOG: Syslog Enhancement.
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.3  2005/01/04 13:45:43  mmanikandan
 * LOG: Changes for CTF.
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.2  2004/12/16 15:02:01  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.20.2.6.2.1.12.1  2004/12/06 14:04:18  mmanikandan
 * LOG: Windows compilation support.
 * LOG:
 * LOG: Revision 7.20.2.6.2.1  2004/01/05 10:16:58  sjaddu
 * LOG: Merged code from tcs isup.
 * LOG:
 * LOG: Revision 7.20.2.5.2.8  2003/11/24 06:20:01  akumar
 * LOG: Bug fix cycle.
 * LOG:
 * LOG: Revision 7.20.2.5.2.7  2003/11/04 12:30:44  akumar
 * LOG: ret val changed to void for SPRC_Sendmtp3mgmtIndicToApp.
 * LOG:
 * LOG: Revision 7.20.2.5.2.6  2003/11/03 14:46:45  sjaddu
 * LOG: Added SPRC_Sendmtp3mgmtIndicToApp_ function here.
 * LOG:
 * LOG: Revision 7.20.2.5.2.5  2003/10/27 08:53:02  akumar
 * LOG: Introduced msg based PEGs.
 * LOG:
 * LOG: Revision 7.20.2.5.2.4  2003/10/17 07:04:53  akumar
 * LOG: Fixed Req R480-17.
 * LOG:
 * LOG: Revision 7.20.2.5.2.3  2003/10/08 07:46:59  akumar
 * LOG: Added Vcic in DSM related func and few missing defines for GCS-DSM.
 * LOG:
 * LOG: Revision 7.20.2.5.2.2  2003/09/13 06:16:09  akumar
 * LOG: Msg based redundancy works for ANSI.
 * LOG:
 * LOG: Revision 7.20.2.5.2.1  2003/09/05 09:31:24  akumar
 * LOG: Message Based redundancy modifications.
 * LOG:
 * LOG: Revision 7.20.2.5  2003/07/25 04:56:07  akumar
 * LOG: SGM Func signature modified.
 * LOG:
 * LOG: Revision 7.20.2.4  2003/05/07 09:56:15  ssingh
 * LOG: ANSI/ITU latest changes propped from Current to 6.3.
 * LOG:
 * LOG: Revision 8.21  2003/05/02 14:01:10  ssingh
 * LOG: ANSI changes propped to ITU.
 * LOG:
 * LOG: Revision 8.20  2003/04/30 13:21:29  sjaddu
 * LOG: ANSI To ITU changes
 * LOG:
 * LOG: Revision 8.19  2003/04/30 04:53:10  akumar
 * LOG: Misc. modifications.
 * LOG:
 * LOG: Revision 8.18  2003/04/25 13:39:16  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.17  2003/04/25 09:53:25  akumar
 * LOG: ITS_SS7_CONTEXT name changed with ISUP_CONG_CONTEXT for cong.
 * LOG:
 * LOG: Revision 8.16  2003/04/22 07:12:56  akumar
 * LOG: Front port 6.3 to Current Branch (Mainly MML)
 * LOG:
 * LOG: Revision 8.15  2003/04/18 06:52:12  sjaddu
 * LOG: Added functions to Lock and unlock opc_dpc_stat table.
 * LOG:
 * LOG: Revision 8.14  2003/04/16 05:45:47  akumar
 * LOG: Congestion related changes.
 * LOG:
 * LOG: Revision 8.13  2003/04/14 10:35:09  sjaddu
 * LOG: Added New function to check the remote Route.
 * LOG:
 * LOG: Revision 8.12  2003/04/07 21:07:20  mmiers
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 8.11  2003/04/04 12:00:31  ssingh
 * LOG: Functions added to handle CGB/CGU.
 * LOG:
 * LOG: Revision 8.10  2003/04/04 05:03:19  ssingh
 * LOG: SPRC_SendConfToApp_CCITT removed.
 * LOG:
 * LOG: Revision 8.9  2003/04/03 14:39:02  sjaddu
 * LOG: DSM reorgnisation , added new functions.
 * LOG:
 * LOG: Revision 8.8  2003/03/26 11:48:11  ssingh
 * LOG: Changes associated with CIC_MSG_INFO buffer table moved from CIC_INFO
 * LOG: in ANSI. Functions added for getting DPC status and Remote ISUP status.
 * LOG:
 * LOG: Revision 8.7  2003/03/15 12:39:34  ssingh
 * LOG: SendCRAToMTP3 added as part of CRM/CRA support for ANSI.
 * LOG:
 * LOG: Revision 8.6  2003/03/14 09:34:10  ssingh
 * LOG: Changes been proped from PR6.3 to fix Bug# 245.
 * LOG:
 * LOG: Revision 8.5  2003/03/06 19:11:42  mmiers
 * LOG: Convert to new tracing, simply by removing file names from
 * LOG: existing trace subsystems.
 * LOG:
 * LOG: Revision 8.4  2003/03/02 22:11:45  vnitin
 * LOG: Adding Tandemn Trace support and fixes for split.
 * LOG:
 * LOG: Revision 8.3  2003/02/27 10:48:17  akumar
 * LOG: Warning Removal
 * LOG:
 * LOG: Revision 8.2  2003/02/13 21:39:12  mmiers
 * LOG: The great file split.  Files without an its- prefix can
 * LOG: be moved into a netcore library.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:44:21  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.20  2003/01/22 14:55:02  vnitin
 * LOG: Tandem port for Ansi ISUP
 * LOG:
 * LOG: Revision 7.19  2003/01/22 09:30:40  akumar
 * LOG: Modified for COT procedure, moved the __ISUP_CheckRmtCongestion() func
 * LOG: out of ANSI variant directive
 * LOG:
 * LOG: Revision 7.18  2003/01/21 15:34:18  vnitin
 * LOG: Tandem Port for ISUP, mostly type casting
 * LOG:
 * LOG: Revision 7.17  2003/01/17 15:19:46  sjaddu
 * LOG: vcic changes .
 * LOG:
 * LOG: Revision 7.16  2003/01/14 00:36:06  sjaddu
 * LOG: Cic rule changes for this file.
 * LOG:
 * LOG: Revision 7.15  2003/01/10 22:39:10  sjaddu
 * LOG: Added DSM_Que API.
 * LOG:
 * LOG: Revision 7.14  2002/12/31 11:02:08  akumar
 * LOG: Added remaining function signature for Segmentation Purpose
 * LOG:
 * LOG: Revision 7.13  2002/12/31 08:41:33  akumar
 * LOG: Added new signatures for Segmentation procedure implementation, Two
 * LOG: new MACROS have been added also for configuration purpose.
 * LOG:
 * LOG: Revision 7.12  2002/12/31 07:25:53  akumar
 * LOG: Undoing the version 7.11
 * LOG:
 * LOG: Revision 7.10  2002/12/27 05:48:35  ssingh
 * LOG: Function to Support CVT/CQM on UNEQUIPPED CIC is added and bit more.
 * LOG:
 * LOG: Revision 7.9  2002/11/20 13:20:59  akumar
 * LOG: Return Type corrected in __ISUP_ValidateParameters_ANSI() fn
 * LOG:
 * LOG: Revision 7.8  2002/11/20 11:29:44  akumar
 * LOG: Added New Declaration __ISUP_CheckRmtCongestion() for ACC
 * LOG:
 * LOG: Revision 7.7  2002/11/19 12:51:43  sjaddu
 * LOG: Added DelUsableCic function.
 * LOG:
 * LOG: Revision 7.6  2002/11/11 11:20:30  akumar
 * LOG: Code added for Automatic Congestion Control, ANSI ISUP Alarms and modified
 * LOG: the signature of __ISUP_IsExchangeControlling() func to include the new
 * LOG: argument.
 * LOG:
 * LOG: Revision 7.5  2002/11/07 05:15:58  ssingh
 * LOG: Added Source defination to process ISUP event from App for ANSI.
 * LOG:
 * LOG: Revision 7.4  2002/10/30 06:18:59  sjaddu
 * LOG: Added continuity functions.
 * LOG:
 * LOG: Revision 7.3  2002/10/25 13:39:42  ssingh
 * LOG: Function added as a part of BUG 141-to-146.
 * LOG:
 * LOG: Revision 7.2  2002/10/21 12:07:55  ssingh
 * LOG: Added new function to handle <-CQR- in ANSI.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:27  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.22  2002/08/22 20:51:23  omayor
 * LOG: If defined PRC then FAMILY_ITU becomes FAMILY_CHINA. This was needed to
 * LOG: substitute the ITU family with CHINA in the routing subsystem calls.
 * LOG:
 * LOG: Revision 6.21  2002/08/21 15:03:24  sjaddu
 * LOG: Bug fix for InitOpcDpcStat,ANSI redundancy.
 * LOG:
 * LOG: Revision 6.20  2002/08/16 22:07:08  mmiers
 * LOG: Include China variant.
 * LOG:
 * LOG: Revision 6.19  2002/08/02 16:17:19  ssingh
 * LOG: Peg functionalities added.
 * LOG:
 * LOG: Revision 6.18  2002/08/01 15:52:01  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.17  2002/07/08 15:03:21  pmandal
 * LOG: Fix build problem.
 * LOG:
 * LOG: Revision 6.16  2002/07/05 21:32:59  ssharma
 * LOG: Add a function prototype.
 * LOG:
 * LOG: Revision 6.15.2.20  2002/07/31 22:25:44  ssharma
 * LOG: ITU pegs.
 * LOG:
 * LOG: Revision 6.15.2.19  2002/07/31 20:34:58  sjaddu
 * LOG: Added paramters check functiom.
 * LOG:
 * LOG: Revision 6.15.2.18  2002/07/31 16:12:24  ssharma
 * LOG: Performance improvements.
 * LOG:
 * LOG: Revision 6.15.2.17  2002/07/30 13:53:05  sjaddu
 * LOG: Added MTP indications and CFN procedures.
 * LOG:
 * LOG: Revision 6.15.2.16  2002/07/18 18:48:49  ssingh
 * LOG: New function added to handle outgoing group ACKs.
 * LOG:
 * LOG: Revision 6.15.2.15  2002/07/15 21:21:00  hbalimid
 * LOG: New functionalities added.
 * LOG:
 * LOG: Revision 6.15.2.14  2002/07/13 17:41:37  hbalimid
 * LOG: Wait for Incoming ACM procedures completed.
 * LOG:
 * LOG: Revision 6.15.2.13  2002/07/12 22:23:47  hbalimid
 * LOG: Handlers for UCIC.
 * LOG:
 * LOG: Revision 6.15.2.12  2002/07/12 15:22:57  ssingh
 * LOG: Added CQM/CQR related CSC methods.
 * LOG:
 * LOG: Revision 6.15.2.11  2002/07/12 14:05:26  hbalimid
 * LOG: CQM moved to CSC.
 * LOG:
 * LOG: Revision 6.15.2.10  2002/07/10 20:18:12  ssharma
 * LOG: Warning removal.
 * LOG:
 * LOG: Revision 6.15.2.9  2002/07/10 19:31:11  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.15.2.8  2002/07/10 14:12:04  ssingh
 * LOG: Handlers for CSC messages.
 * LOG:
 * LOG: Revision 6.15.2.7  2002/07/08 23:57:51  ssingh
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 6.15.2.6  2002/07/08 23:46:14  hbalimid
 * LOG: Added new function for Blocking CPC to BLS.
 * LOG:
 * LOG: Revision 6.15.2.5  2002/07/07 14:05:16  hbalimid
 * LOG: corrected SPRC_SendRLCToMTP3_ANSI
 * LOG:
 * LOG: Revision 6.15.2.4  2002/07/06 19:55:36  hbalimid
 * LOG: Fixed warnings.
 * LOG:
 * LOG: Revision 6.15.2.3  2002/07/06 06:18:34  hbalimid
 * LOG: Took care of all the warnings.
 * LOG:
 * LOG: Revision 6.15.2.2  2002/07/05 23:17:03  ssingh
 * LOG: New functions for CGB and CGU added.
 * LOG:
 * LOG: Revision 6.15.2.1  2002/07/01 22:24:42  hbalimid
 * LOG: Updated with ISUP ANSI 92 & 95.
 * LOG:
 * LOG: Revision 6.15  2002/06/28 19:07:26  ssharma
 * LOG: Change signature of PrintCic function.
 * LOG:
 * LOG: Revision 6.14  2002/06/24 16:57:08  ssingh
 * LOG: Add function prototypes.
 * LOG:
 * LOG: Revision 6.13  2002/06/18 20:56:16  mmiers
 * LOG: Add debug console hooks in preparation for MML
 * LOG:
 * LOG: Revision 6.12  2002/06/17 22:14:50  sjaddu
 * LOG: Added functions for mtp3 status indication handling.
 * LOG:
 * LOG: Revision 6.11  2002/06/12 19:57:43  sjaddu
 * LOG: Warnings fixed on NT.
 * LOG:
 * LOG: Revision 6.10  2002/06/10 15:52:36  sjaddu
 * LOG: Added short names for isup functions.
 * LOG:
 * LOG: Revision 6.9  2002/06/03 16:18:29  sjaddu
 * LOG: Added Param level confusion.
 * LOG:
 * LOG: Revision 6.8  2002/05/28 16:10:23  sjaddu
 * LOG: Added CFN Procedures.
 * LOG:
 * LOG: Revision 6.7  2002/05/20 22:15:33  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 * LOG: Revision 6.6  2002/05/20 21:46:57  mmiers
 * LOG: Add snames.
 * LOG:
 * LOG: Revision 6.5  2002/05/20 20:54:48  ssharma
 * LOG: Fix NT build after merge from PR6.
 * LOG:
 * LOG: Revision 6.4  2002/05/20 15:43:48  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.3  2002/03/14 21:39:11  mmiers
 * LOG: Convert SCCP for OAM
 * LOG:
 * LOG: Revision 6.2  2002/03/12 23:37:17  mmiers
 * LOG: Standardize alarms.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:38  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 1.10.2.16  2002/05/14 18:15:25  sjaddu
 * LOG: Added MTP3 Indications.
 * LOG:
 * LOG: Revision 1.10.2.15  2002/05/09 18:38:10  labuser
 * LOG: Merge from ISUP_APR_19_2002 branch to PR6.
 * LOG:
 * LOG: Revision 1.10.2.14.2.1  2002/04/29 20:40:36  labuser
 * LOG: Add a function to idle circuit state.
 * LOG:
 * LOG: Revision 1.10.2.14  2002/04/05 19:37:44  ssharma
 * LOG: Add parameter to timeout handling procedures.
 * LOG:
 * LOG: Revision 1.10.2.13  2002/04/03 18:10:55  ssharma
 * LOG: Fix memory leaks.
 * LOG:
 * LOG: Revision 1.10.2.12  2002/04/01 22:01:21  ssharma
 * LOG: Change prototype of ISUP_AllocCic
 * LOG:
 * LOG: Revision 1.10.2.11  2002/04/01 21:08:31  ssharma
 * LOG: Change prototypes to fix memory leaks.
 * LOG:
 * LOG: Revision 1.10.2.10  2002/03/28 20:20:22  ssharma
 * LOG: Add CSC functions.
 * LOG:
 * LOG: Revision 1.10.2.9  2002/03/26 22:07:26  ssharma
 * LOG: More functions added.
 * LOG:
 * LOG: Revision 1.10.2.8  2002/03/22 16:19:18  ssharma
 * LOG: Add function prototypes.
 * LOG:
 * LOG: Revision 1.10.2.7  2002/03/19 18:04:18  ssharma
 * LOG: Change prototype of function.
 * LOG:
 * LOG: Revision 1.10.2.6  2002/03/19 17:21:18  ssharma
 * LOG: Add more function prototypes.
 * LOG:
 * LOG: Revision 1.10.2.5  2002/03/14 22:58:12  ssharma
 * LOG: Add more function prototypes.
 * LOG:
 * LOG: Revision 1.10.2.4  2002/03/14 15:28:40  ssharma
 * LOG: Cleanup, add function signatures.
 * LOG:
 * LOG: Revision 1.10.2.3  2002/03/07 20:09:07  ssharma
 * LOG: Add some timer related and sprc functions.
 * LOG:
 * LOG: Revision 1.10.2.2  2002/03/05 21:26:14  ssharma
 * LOG: Export the ISUP_MTP3Decode function.
 * LOG:
 * LOG: Revision 1.10.2.1  2002/03/05 14:56:50  ssharma
 * LOG: Add new function prototype.
 * LOG:
 * LOG: Revision 1.10  2002/02/27 23:30:14  ssharma
 * LOG: Add function prototype.
 * LOG:
 * LOG: Revision 1.9  2002/02/26 23:50:05  ssharma
 * LOG: Add prototypes.
 * LOG:
 * LOG: Revision 1.8  2002/02/22 22:35:51  ssharma
 * LOG: Change signature of a function.
 * LOG:
 * LOG: Revision 1.7  2002/02/14 17:03:59  mmiers
 * LOG: Signature bugs.
 * LOG:
 * LOG: Revision 1.6  2002/02/13 18:28:32  mmiers
 * LOG: Finish off the ISUP integration.  Still need to add CHINA
 * LOG: variant lib.
 * LOG:
 * LOG: Revision 1.5  2002/02/12 23:29:03  mmiers
 * LOG: ISUP parser in place.
 * LOG:
 * LOG: Revision 1.4  2002/02/08 21:47:43  mmiers
 * LOG: Reorg complete
 * LOG:
 * LOG: Revision 1.3  2002/02/06 23:43:59  mmiers
 * LOG: Continue ISUP integration.
 * LOG:
 * LOG: Revision 1.2  2002/02/01 20:07:30  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:51:27  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:28  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 19:18:38  mmiers
 * LOG: Make the stack participate in HMI
 * LOG:
 * LOG: Revision 4.1  2001/05/04 16:22:05  mmiers
 * LOG: Start PR5.
 * LOG:
 * LOG: Revision 3.6  2001/04/02 21:20:24  mmiers
 * LOG: Align the string names.
 * LOG:
 * LOG: Revision 3.5  2001/03/28 21:11:26  mmiers
 * LOG: Change the names to match config.
 * LOG:
 * LOG: Revision 3.4  2001/03/14 22:07:09  mmiers
 * LOG: Include ISUP in the engine.
 * LOG:
 * LOG: Revision 3.3  2000/08/24 23:07:24  mmiers
 * LOG: Zero copy is in.
 * LOG:
 * LOG: Revision 3.2  2000/08/22 22:33:43  mmiers
 * LOG: Prepare for reentrant SCCP, TCAP, and ISUP warning removal.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:09:32  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.1  2000/02/03 17:12:04  fhasle
 * LOG:
 * LOG: First shoet at ISUP Stack.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:31:31  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/03/17 20:55:07  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol stuff.
 * LOG:
 * LOG: Revision 1.3  1999/03/17 18:39:46  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol commit.  Still have to finish TCAP.
 * LOG:
 * LOG: Revision 1.2  1998/11/10 03:26:35  mmiers
 * LOG: Update/include the string defines.
 * LOG:
 * LOG: Revision 1.1  1998/10/14 23:29:36  mmiers
 * LOG: Set trace levels from INI file.
 * LOG:
 *
 ****************************************************************************/

/*****************************************************************************
 *  Revision History:
 * ---------------------------------------------------------------------------
 * Name        Date        Reference         Description
 * ---------------------------------------------------------------------------
 * kramesh     04-05-2005  BCGI Problem      Functions added initialization       
 *                         #389/421/423/496  - ISUP_FindCktGrpInfo(..)
 *                                           - ISUP_InsertCktGrpInfo(..)
 *                                           - ISUP_UpdateCktGrpInfo(..) 
 *                                           New Function to Release cic rec
 *                                           - ISUP_ReleasePcic(..)
 *                                           SPRC_SendErrorToApp changed for
 *                                           msgType as passing param.
 ******************************************************************************/
#ifndef ISUP_INTERN_H
#define ISUP_INTERN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <its_emlist.h>
#include <its_transports.h>
#include <its_thread.h>
#include <its_trace.h>
#include <its_hash.h>
#include <its_timers.h>
#include <its_ctf.h>

#include <isup_cmn.h>
#include <isup_variants.h>
#include <its_ss7_trans.h>

#if defined(PRC) || defined(TTC)
#elif defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#ident "$Id: isup_intern.h,v 1.1.1.1 2007-10-08 11:12:12 bsccs2 Exp $"

#include "ss7_pegs.h"
#include "ss7_mgmt.h"
#include "ss7_alarms.h"
#include "ss7_timers.h"
#include "ss7_behaviors.h"

#include <its_dsmqueue.h>

#if defined(PRC)
#define FAMILY_ITU       FAMILY_CHINA
#endif

#if defined(TTC)
#define FAMILY_ITU       FAMILY_JAPAN
#endif
/*
 * Source of the ISUP msg used when handling a msg
 */
#define ISUP_SRC_APP_ITU    1
#define ISUP_SRC_L3_ITU     2
#define ISUP_SRC_L3_ANSI    3
#define ISUP_SRC_APP_ANSI   4
#define ISUP_SRC_APP        5

#if defined (WIN32)
#if defined (TRACE_IMPLEMENTATION)
#define TDATADLLAPI __declspec(dllexport)
#else
#define TDATADLLAPI __declspec(dllimport)
#endif
#else
#define TDATADLLAPI
#endif

/*
 * ISUP trace information
 */
extern TDATADLLAPI TRACE_Data* ISUP_CCITT_TraceData;
extern TDATADLLAPI TRACE_Data* ISUP_ANSI_TraceData;

/*
 * ISUP trace levels
 */
#define ISUP_TRACE_CRITICAL  0
#define ISUP_TRACE_ERROR     1
#define ISUP_TRACE_WARNING   2
#define ISUP_TRACE_DEBUG     3
#define ISUP_TRACE_EVENT     4
#define DO_ROUTE_CONTEXT    -1

#if defined(CCITT) || defined(PRC) ||  defined(TTC)

#define ISUP_CRITICAL(args) \
    TRACE(ISUP_CCITT_TraceData, ISUP_TRACE_CRITICAL, args)

#define ISUP_ERROR(args) \
    TRACE(ISUP_CCITT_TraceData, ISUP_TRACE_ERROR, args)

#define ISUP_WARNING(args) \
    TRACE(ISUP_CCITT_TraceData, ISUP_TRACE_WARNING, args)

#define ISUP_DEBUG(args) \
    TRACE(ISUP_CCITT_TraceData, ISUP_TRACE_DEBUG, args)

#define ISUP_EVENT(args) \
    TRACE(ISUP_CCITT_TraceData, ISUP_TRACE_EVENT, args)

#elif defined(ANSI)

#define ISUP_CRITICAL(args) \
    TRACE(ISUP_ANSI_TraceData, ISUP_TRACE_CRITICAL, args)

#define ISUP_ERROR(args) \
    TRACE(ISUP_ANSI_TraceData, ISUP_TRACE_ERROR, args)

#define ISUP_WARNING(args) \
    TRACE(ISUP_ANSI_TraceData, ISUP_TRACE_WARNING, args)

#define ISUP_DEBUG(args) \
    TRACE(ISUP_ANSI_TraceData, ISUP_TRACE_DEBUG, args)

#define ISUP_EVENT(args) \
    TRACE(ISUP_ANSI_TraceData, ISUP_TRACE_EVENT, args)

#endif

/*
 * ISUP trace strings
 */
#define ISUP_TRACE_CRITICAL_STRING  ITS_TRACE_CRITICAL_STRING
#define ISUP_TRACE_ERROR_STRING     ITS_TRACE_ERROR_STRING
#define ISUP_TRACE_WARNING_STRING   ITS_TRACE_WARNING_STRING
#define ISUP_TRACE_DEBUG_STRING     ITS_TRACE_DEBUG_STRING
#define ISUP_TRACE_EVENT_STRING     ITS_TRACE_EVENT_STRING

#define ISUP_CRITICAL_STRING        ITS_CRITICAL_STRING
#define ISUP_ERROR_STRING           ITS_ERROR_STRING
#define ISUP_WARNING_STRING         ITS_WARNING_STRING
#define ISUP_DEBUG_STRING           ITS_DEBUG_STRING
#define ISUP_EVENT_STRING           ITS_EVENT_STRING

#define ISUP_STDOUT_STRING          ITS_STDOUT_STRING
#define ISUP_SYSLOG_STRING          ITS_SYSLOG_STRING
#define ISUP_FILE_STRING            ITS_FILE_STRING

#define ISUP_VARIANT_STRING         "variant" /* ITU only */

#if defined(CCITT) || defined(PRC) || defined(TTC)

#define ISUP_TRACE_CRITICAL_FILE    ".itu-isup-traceCritical"
#define ISUP_TRACE_ERROR_FILE       ".itu-isup-traceError"
#define ISUP_TRACE_WARNING_FILE     ".itu-isup-traceWarning"
#define ISUP_TRACE_DEBUG_FILE       ".itu-isup-traceDebug"
#define ISUP_TRACE_EVENT_FILE       ".itu-isup-traceEvent"

#elif defined(ANSI)

#define ISUP_TRACE_CRITICAL_FILE    ".ansi-isup-traceCritical"
#define ISUP_TRACE_ERROR_FILE       ".ansi-isup-traceError"
#define ISUP_TRACE_WARNING_FILE     ".ansi-isup-traceWarning"
#define ISUP_TRACE_DEBUG_FILE       ".ansi-isup-traceDebug"
#define ISUP_TRACE_EVENT_FILE       ".ansi-isup-traceEvent"

#endif

#if defined(CCITT) || defined(PRC) || defined(TTC)

/*
 * Circuit Supervision Control (CSC) functions
 */
#define __ISUP_CSC_Received_BLA             __ISUP_CSC_Received_BLA_CCITT
#define __ISUP_CSC_Received_BLO             __ISUP_CSC_Received_BLO_CCITT
#define __ISUP_CSC_Received_CCR             __ISUP_CSC_Received_CCR_CCITT
#define __ISUP_CSC_Received_CGB             __ISUP_CSC_Received_CGB_CCITT
#define __ISUP_CSC_Received_CGBA            __ISUP_CSC_Received_CGBA_CCITT
#define __ISUP_CSC_Received_CGU             __ISUP_CSC_Received_CGU_CCITT
#define __ISUP_CSC_Received_CGUA            __ISUP_CSC_Received_CGUA_CCITT
#define __ISUP_CSC_Received_GRA             __ISUP_CSC_Received_GRA_CCITT
#define __ISUP_CSC_Received_GRS             __ISUP_CSC_Received_GRS_CCITT
#define __ISUP_CSC_Received_LPA             __ISUP_CSC_Received_LPA_CCITT
#define __ISUP_CSC_Received_RSC             __ISUP_CSC_Received_RSC_CCITT
#define __ISUP_CSC_Received_UBA             __ISUP_CSC_Received_UBA_CCITT
#define __ISUP_CSC_Received_UBL             __ISUP_CSC_Received_UBL_CCITT
#define __ISUP_CSC_Received_UCIC            __ISUP_CSC_Received_UCIC_CCITT
#define __ISUP_CSC_Received_CQM             __ISUP_CSC_Received_CQM_CCITT
#define __ISUP_CSC_Received_CQR             __ISUP_CSC_Received_CQR_CCITT
#define __ISUP_CSC_Received_TimeoutT12      __ISUP_CSC_Received_TimeoutT12_CCITT
#define __ISUP_CSC_Received_TimeoutT16      __ISUP_CSC_Received_TimeoutT16_CCITT
#define __ISUP_CSC_Received_TimeoutT17      __ISUP_CSC_Received_TimeoutT17_CCITT
#define __ISUP_CSC_Received_TimeoutT18      __ISUP_CSC_Received_TimeoutT18_CCITT
#define __ISUP_CSC_Received_TimeoutT19      __ISUP_CSC_Received_TimeoutT19_CCITT
#define __ISUP_CSC_Received_TimeoutT20      __ISUP_CSC_Received_TimeoutT20_CCITT
#define __ISUP_CSC_Received_TimeoutT21      __ISUP_CSC_Received_TimeoutT21_CCITT
#define __ISUP_CSC_Received_TimeoutT22      __ISUP_CSC_Received_TimeoutT22_CCITT
#define __ISUP_CSC_Received_TimeoutT23      __ISUP_CSC_Received_TimeoutT23_CCITT     
#define __ISUP_CSC_Received_TimeoutT24      __ISUP_CSC_Received_TimeoutT24_CCITT
#define __ISUP_CSC_Received_TimeoutT25      __ISUP_CSC_Received_TimeoutT25_CCITT
#define __ISUP_CSC_Received_TimeoutT26      __ISUP_CSC_Received_TimeoutT26_CCITT
#define __ISUP_CSC_Received_TimeoutT27      __ISUP_CSC_Received_TimeoutT27_CCITT

/*                                         
 * CSC timers helper functions                                          
 */                                         
#define __ISUP_StartBLOTimers              __ISUP_StartBLOTimers_CCITT
#define __ISUP_StopBLOTimers               __ISUP_StopBLOTimers_CCITT
#define __ISUP_StartBLORepeatTimer         __ISUP_StartBLORepeatTimer_CCITT
#define __ISUP_StartRELTimers              __ISUP_StartRELTimers_CCITT
#define __ISUP_StopRELTimers               __ISUP_StopRELTimers_CCITT
#define __ISUP_StartUBLTimers              __ISUP_StartUBLTimers_CCITT
#define __ISUP_StopUBLTimers               __ISUP_StopUBLTimers_CCITT
#define __ISUP_StartUBLRepeatTimer         __ISUP_StartUBLRepeatTimer_CCITT
#define __ISUP_StartRSCTimers              __ISUP_StartRSCTimers_CCITT
#define __ISUP_StopRSCTimers               __ISUP_StopRSCTimers_CCITT
#define __ISUP_StartRSCRepeatTimer         __ISUP_StartRSCRepeatTimer_CCITT
#define __ISUP_StartCGBTimers              __ISUP_StartCGBTimers_CCITT
#define __ISUP_StopCGBTimers               __ISUP_StopCGBTimers_CCITT
#define __ISUP_StartCGBRepeatTimer         __ISUP_StartCGBRepeatTimer_CCITT
#define __ISUP_StartCGUTimers              __ISUP_StartCGUTimers_CCITT
#define __ISUP_StopCGUTimers               __ISUP_StopCGUTimers_CCITT
#define __ISUP_StartCGURepeatTimer         __ISUP_StartCGURepeatTimer_CCITT
#define __ISUP_StartGRSTimers              __ISUP_StartGRSTimers_CCITT
#define __ISUP_StopGRSTimers               __ISUP_StopGRSTimers_CCITT
#define __ISUP_StartGRSRepeatTimer         __ISUP_StartGRSRepeatTimer_CCITT
/*                                          
 * CSC validation and helper functions                                          
 */                                         
#define __ISUP_Validate_RangeStatus        __ISUP_Validate_RangeStatus_CCITT
#define __ISUP_GetAffectedCics             __ISUP_GetAffectedCics_CCITT
#define __ISUP_GetGRACics                  __ISUP_GetGRACics_CCITT        
#define __ISUP_GetGRSCics                  __ISUP_GetGRSCics_CCITT
#define __ISUP_ProcessAffectedCic          __ISUP_ProcessAffectedCic_CCITT
#define __ISUP_CompareCGBAWithCGB          __ISUP_CompareCGBAWithCGB_CCITT
#define __ISUP_CompareCGUAWithCGU          __ISUP_CompareCGUAWithCGU_CCITT
#define __ISUP_CompareGRAWithGRS           __ISUP_CompareGRAWithGRS_CCITT
#define __ISUP_BlockingMGBSToBLS           __ISUP_BlockingMGBSToBLS_CCITT
#define __ISUP_MGBSCheckLocallyBlocked     __ISUP_MGBSCheckLocallyBlocked_CCITT
#define __ISUP_MGBSCheckNotLocallyBlocked  __ISUP_MGBSCheckNotLocallyBlocked_CCITT
#define __ISUP_BlockingMGBRToBLR           __ISUP_BlockingMGBRToBLR_CCITT
#define __ISUP_UnblockingMGBSToBLS         __ISUP_UnblockingMGBSToBLS_CCITT
#define __ISUP_UnblockingMGBRToBLR         __ISUP_UnblockingMGBRToBLR_CCITT
#define __ISUP_BlockingBLSToCPC            __ISUP_BlockingBLSToCPC_CCITT
#define __ISUP_BlockingCRRToBLS            __ISUP_BlockingCRRToBLS_CCITT
#define __ISUP_BlockingCPCIToBLS           __ISUP_BlockingCPCIToBLS_CCITT
#define __ISUP_UnblockingCRSToBLS          __ISUP_UnblockingCRSToBLS_CCITT
#define __ISUP_UnblockingCGRSToBLS         __ISUP_UnblockingCGRSToBLS_CCITT
#define __ISUP_BlockingBLRToCPCO           __ISUP_BlockingBLRToCPCO_CCITT  
#define __ISUP_BlockingCGRSToBLR           __ISUP_BlockingCGRSToBLR_CCITT
#define __ISUP_UnblockingCRRToBLR          __ISUP_UnblockingCRRToBLR_CCITT
#define __ISUP_UnblockingCRSToBLR          __ISUP_UnblockingCRSToBLR_CCITT
#define __ISUP_UnblockingCGRRToBLR         __ISUP_UnblockingCGRRToBLR_CCITT
#define __ISUP_UnblockingCPCIToBLR         __ISUP_UnblockingCPCIToBLR_CCITT
#define __ISUP_ResetCGRSToMGBS             __ISUP_ResetCGRSToMGBS_CCITT
#define __ISUP_ResetCGRRToMGBR             __ISUP_ResetCGRRToMGBR_CCITT
#define __ISUP_ResetCGRSToMGBR             __ISUP_ResetCGRSToMGBR_CCITT
#define __ISUP_BlockingHGBSToHLB           __ISUP_BlockingHGBSToHLB_CCITT
#define __ISUP_ReleaseHGBSToCPC            __ISUP_ReleaseHGBSToCPC_CCITT
#define __ISUP_UnblockingCRSToHLB          __ISUP_UnblockingCRSToHLB_CCITT
#define __ISUP_UnblockingCGRSToHLB         __ISUP_UnblockingCGRSToHLB_CCITT
#define __ISUP_UnblockingHGBSToHLB         __ISUP_UnblockingHGBSToHLB_CCITT
#define __ISUP_BlockingHGBRToHRB           __ISUP_BlockingHGBRToHRB_CCITT
#define __ISUP_UnblockingCRSToHRB          __ISUP_UnblockingCRSToHRB_CCITT
#define __ISUP_UnblockingCRRToHRB          __ISUP_UnblockingCRRToHRB_CCITT
#define __ISUP_UnblockingCGRSToHRB         __ISUP_UnblockingCGRSToHRB_CCITT
#define __ISUP_UnblockingCGRRToHRB         __ISUP_UnblockingCGRRToHRB_CCITT
#define __ISUP_UnblockingCPCIToHRB         __ISUP_UnblockingCPCIToHRB_CCITT
#define __ISUP_UnblockingHGBRToHRB         __ISUP_UnblockingHGBRToHRB_CCITT
#define __ISUP_BlockingCRRToHGBS           __ISUP_BlockingCRRToHGBS_CCITT
#define __ISUP_BlockingCGRRToHGBS          __ISUP_BlockingCGRRToHGBS_CCITT
#define __ISUP_BlockingCPCIToHGBS          __ISUP_BlockingCPCIToHGBS_CCITT
#define __ISUP_HGBSCheckLocallyBlocked     __ISUP_HGBSCheckLocallyBlocked_CCITT
#define __ISUP_HGBSCheckNotLocallyBlocked  __ISUP_HGBSCheckNotLocallyBlocked_CCITT
#define __ISUP_ResetCGRSToHGBS             __ISUP_ResetCGRSToHGBS_CCITT
#define __ISUP_ReleaseHGBRToCPC            __ISUP_ReleaseHGBRToCPC_CCITT
#define __ISUP_ResetCGRRToHGBR             __ISUP_ResetCGRRToHGBR_CCITT
#define __ISUP_ResetCGRSToHGBR             __ISUP_ResetCGRSToHGBR_CCITT
#define __ISUP_ResetCRSCommon1             __ISUP_ResetCRSCommon1_CCITT
#define __ISUP_ResetCRSCommon2             __ISUP_ResetCRSCommon2_CCITT
#define __ISUP_ResetCPCToCRS               __ISUP_ResetCPCToCRS_CCITT
#define __ISUP_ResetCRCRToCRS              __ISUP_ResetCRCRToCRS_CCITT
#define __ISUP_ResetAfterT5CPCToCRS        __ISUP_ResetAfterT5CPCToCRS_CCITT
#define __ISUP_ResetAfterT5CRCSToCRS       __ISUP_ResetAfterT5CRCSToCRS_CCITT
#define __ISUP_ResetCRSToCPC               __ISUP_ResetCRSToCPC_CCITT
#define __ISUP_ResetCRRToCPC               __ISUP_ResetCRRToCPC_CCITT
#define __ISUP_ResetCRRToCRCS              __ISUP_ResetCRRToCRCS_CCITT
#define __ISUP_ResetCRRToCRCR              __ISUP_ResetCRRToCRCR_CCITT
#define __ISUP_ResetCompleteCPCToCRR       __ISUP_ResetCompleteCPCToCRR_CCITT
#define __ISUP_ResetCompleteCPCIToCRR      __ISUP_ResetCompleteCPCIToCRR_CCITT
#define __ISUP_ResetCompleteCPCToCGRR      __ISUP_ResetCompleteCPCToCGRR_CCITT
#define __ISUP_ResetCGRSCommon1            __ISUP_ResetCGRSCommon1_CCITT
#define __ISUP_ResetCGRSCommon2            __ISUP_ResetCGRSCommon2_CCITT
#define __ISUP_UnblockingCGRSToBLR         __ISUP_UnblockingCGRSToBLR_CCITT
#define __ISUP_ResetCGRSToCPC              __ISUP_ResetCGRSToCPC_CCITT
#define __ISUP_ResetCGRRCommon1            __ISUP_ResetCGRRCommon1_CCITT
#define __ISUP_ResetCGRRToCRCS             __ISUP_ResetCGRRToCRCS_CCITT
#define __ISUP_ResetCGRRToCRCR             __ISUP_ResetCGRRToCRCR_CCITT
#define __ISUP_ResetCGRRToCPC              __ISUP_ResetCGRRToCPC_CCITT
#define __ISUP_IdleCircuit                 __ISUP_IdleCircuit_CCITT
                    
#else /*ANSI*/                                          
                                            
/*
 * Circuit Supervision Control (CSC) functions
 */
#define __ISUP_CSC_Received_BLA             __ISUP_CSC_Received_BLA_ANSI
#define __ISUP_CSC_Received_BLO             __ISUP_CSC_Received_BLO_ANSI
#define __ISUP_CSC_Received_CCR             __ISUP_CSC_Received_CCR_ANSI
#define __ISUP_CSC_Received_CGB             __ISUP_CSC_Received_CGB_ANSI
#define __ISUP_CSC_Received_CGBA            __ISUP_CSC_Received_CGBA_ANSI
#define __ISUP_CSC_Received_CGU             __ISUP_CSC_Received_CGU_ANSI
#define __ISUP_CSC_Received_CGUA            __ISUP_CSC_Received_CGUA_ANSI
#define __ISUP_CSC_Received_GRA             __ISUP_CSC_Received_GRA_ANSI
#define __ISUP_CSC_Received_GRS             __ISUP_CSC_Received_GRS_ANSI
#define __ISUP_CSC_Received_LPA             __ISUP_CSC_Received_LPA_ANSI
#define __ISUP_CSC_Received_RSC             __ISUP_CSC_Received_RSC_ANSI
#define __ISUP_CSC_Received_UBA             __ISUP_CSC_Received_UBA_ANSI   
#define __ISUP_CSC_Received_UBL             __ISUP_CSC_Received_UBL_ANSI    
#define __ISUP_CSC_Received_UCIC            __ISUP_CSC_Received_UCIC_ANSI
#define __ISUP_CSC_Received_CQM             __ISUP_CSC_Received_CQM_ANSI
#define __ISUP_CSC_Received_CQR             __ISUP_CSC_Received_CQR_ANSI
#define __ISUP_CSC_Received_TimeoutT12      __ISUP_CSC_Received_TimeoutT12_ANSI
#define __ISUP_CSC_Received_TimeoutT16      __ISUP_CSC_Received_TimeoutT16_ANSI
#define __ISUP_CSC_Received_TimeoutT17      __ISUP_CSC_Received_TimeoutT17_ANSI
#define __ISUP_CSC_Received_TimeoutT18      __ISUP_CSC_Received_TimeoutT18_ANSI
#define __ISUP_CSC_Received_TimeoutT19      __ISUP_CSC_Received_TimeoutT19_ANSI
#define __ISUP_CSC_Received_TimeoutT20      __ISUP_CSC_Received_TimeoutT20_ANSI
#define __ISUP_CSC_Received_TimeoutT21      __ISUP_CSC_Received_TimeoutT21_ANSI
#define __ISUP_CSC_Received_TimeoutT22      __ISUP_CSC_Received_TimeoutT22_ANSI
#define __ISUP_CSC_Received_TimeoutT23      __ISUP_CSC_Received_TimeoutT23_ANSI     
#define __ISUP_CSC_Received_TimeoutT24      __ISUP_CSC_Received_TimeoutT24_ANSI     
#define __ISUP_CSC_Received_TimeoutT25      __ISUP_CSC_Received_TimeoutT25_ANSI     
#define __ISUP_CSC_Received_TimeoutT26      __ISUP_CSC_Received_TimeoutT26_ANSI     
#define __ISUP_CSC_Received_TimeoutT27      __ISUP_CSC_Received_TimeoutT27_ANSI     
#define __ISUP_CSC_Received_TimeoutT34      __ISUP_CSC_Received_TimeoutT34_ANSI     
#define __ISUP_CSC_Received_TimeoutTCCR      __ISUP_CSC_Received_TimeoutTCCR_ANSI     
#define __ISUP_CSC_Received_TimeoutTCCRR      __ISUP_CSC_Received_TimeoutTCCRR_ANSI     

/*
 * CSC timers helper functions
 */

#define __ISUP_StartBLOTimers              __ISUP_StartBLOTimers_ANSI
#define __ISUP_StopBLOTimers               __ISUP_StopBLOTimers_ANSI
#define __ISUP_StartBLORepeatTimer         __ISUP_StartBLORepeatTimer_ANSI
#define __ISUP_StartRELTimers              __ISUP_StartRELTimers_ANSI
#define __ISUP_StopRELTimers               __ISUP_StopRELTimers_ANSI
#define __ISUP_StartUBLTimers              __ISUP_StartUBLTimers_ANSI
#define __ISUP_StopUBLTimers               __ISUP_StopUBLTimers_ANSI
#define __ISUP_StartUBLRepeatTimer         __ISUP_StartUBLRepeatTimer_ANSI
#define __ISUP_StartRSCTimers              __ISUP_StartRSCTimers_ANSI
#define __ISUP_StopRSCTimers               __ISUP_StopRSCTimers_ANSI
#define __ISUP_StartRSCRepeatTimer         __ISUP_StartRSCRepeatTimer_ANSI
#define __ISUP_StartCGBTimers              __ISUP_StartCGBTimers_ANSI
#define __ISUP_StopCGBTimers               __ISUP_StopCGBTimers_ANSI
#define __ISUP_StartCGBRepeatTimer         __ISUP_StartCGBRepeatTimer_ANSI
#define __ISUP_StartCGUTimers              __ISUP_StartCGUTimers_ANSI
#define __ISUP_StopCGUTimers               __ISUP_StopCGUTimers_ANSI
#define __ISUP_StartCGURepeatTimer         __ISUP_StartCGURepeatTimer_ANSI
#define __ISUP_StartGRSTimers              __ISUP_StartGRSTimers_ANSI
#define __ISUP_StopGRSTimers               __ISUP_StopGRSTimers_ANSI
#define __ISUP_StartGRSRepeatTimer         __ISUP_StartGRSRepeatTimer_ANSI
#define __ISUP_StartCVTTimers              __ISUP_StartCVTTimers_ANSI
#define __ISUP_StartCVTRepeatTimer         __ISUP_StartCVTRepeatTimer_ANSI
/*                                          
 * CSC validation and helper functions                                          
 */                                         
#define __ISUP_Validate_RangeStatus        __ISUP_Validate_RangeStatus_ANSI
#define __ISUP_GetAffectedCics             __ISUP_GetAffectedCics_ANSI
#define __ISUP_GetGRACics                  __ISUP_GetGRACics_ANSI        
#define __ISUP_GetGRSCics                  __ISUP_GetGRSCics_ANSI
#define __ISUP_ProcessAffectedCic          __ISUP_ProcessAffectedCic_ANSI
#define __ISUP_CompareCGBAWithCGB          __ISUP_CompareCGBAWithCGB_ANSI
#define __ISUP_CompareCGUAWithCGU          __ISUP_CompareCGUAWithCGU_ANSI
#define __ISUP_CompareGRAWithGRS           __ISUP_CompareGRAWithGRS_ANSI
#define __ISUP_BlockingMGBSToBLS           __ISUP_BlockingMGBSToBLS_ANSI
#define __ISUP_MGBSCheckLocallyBlocked     __ISUP_MGBSCheckLocallyBlocked_ANSI
#define __ISUP_MGBSCheckNotLocallyBlocked  __ISUP_MGBSCheckNotLocallyBlocked_ANSI
#define __ISUP_BlockingMGBRToBLR           __ISUP_BlockingMGBRToBLR_ANSI
#define __ISUP_UnblockingMGBSToBLS         __ISUP_UnblockingMGBSToBLS_ANSI
#define __ISUP_UnblockingMGBRToBLR         __ISUP_UnblockingMGBRToBLR_ANSI
#define __ISUP_BlockingBLSToCPC            __ISUP_BlockingBLSToCPC_ANSI
#define __ISUP_BlockingCRRToBLS            __ISUP_BlockingCRRToBLS_ANSI
#define __ISUP_BlockingCPCIToBLS           __ISUP_BlockingCPCIToBLS_ANSI
#define __ISUP_UnblockingCRSToBLS          __ISUP_UnblockingCRSToBLS_ANSI
#define __ISUP_UnblockingCGRSToBLS         __ISUP_UnblockingCGRSToBLS_ANSI
#define __ISUP_BlockingBLRToCPC            __ISUP_BlockingBLRToCPC_ANSI  
#define __ISUP_BlockingCGRSToBLR           __ISUP_BlockingCGRSToBLR_ANSI
#define __ISUP_UnblockingCRRToBLR          __ISUP_UnblockingCRRToBLR_ANSI
#define __ISUP_UnblockingCRSToBLR          __ISUP_UnblockingCRSToBLR_ANSI
#define __ISUP_UnblockingCGRRToBLR         __ISUP_UnblockingCGRRToBLR_ANSI
#define __ISUP_UnblockingCPCIToBLR         __ISUP_UnblockingCPCIToBLR_ANSI
#define __ISUP_ResetCGRSToMGBS             __ISUP_ResetCGRSToMGBS_ANSI
#define __ISUP_ResetCGRRToMGBR             __ISUP_ResetCGRRToMGBR_ANSI
#define __ISUP_ResetCGRSToMGBR             __ISUP_ResetCGRSToMGBR_ANSI
#define __ISUP_BlockingHGBSToHLB           __ISUP_BlockingHGBSToHLB_ANSI
#define __ISUP_ReleaseHGBSToCPC            __ISUP_ReleaseHGBSToCPC_ANSI
#define __ISUP_UnblockingCRSToHLB          __ISUP_UnblockingCRSToHLB_ANSI
#define __ISUP_UnblockingCGRSToHLB         __ISUP_UnblockingCGRSToHLB_ANSI
#define __ISUP_UnblockingHGBSToHLB         __ISUP_UnblockingHGBSToHLB_ANSI
#define __ISUP_BlockingHGBRToHRB           __ISUP_BlockingHGBRToHRB_ANSI
#define __ISUP_UnblockingCRSToHRB          __ISUP_UnblockingCRSToHRB_ANSI
#define __ISUP_UnblockingCRRToHRB          __ISUP_UnblockingCRRToHRB_ANSI
#define __ISUP_UnblockingCGRSToHRB         __ISUP_UnblockingCGRSToHRB_ANSI
#define __ISUP_UnblockingCGRRToHRB         __ISUP_UnblockingCGRRToHRB_ANSI
#define __ISUP_UnblockingCPCIToHRB         __ISUP_UnblockingCPCIToHRB_ANSI
#define __ISUP_UnblockingHGBRToHRB         __ISUP_UnblockingHGBRToHRB_ANSI
#define __ISUP_BlockingCRRToHGBS           __ISUP_BlockingCRRToHGBS_ANSI
#define __ISUP_BlockingCGRRToHGBS          __ISUP_BlockingCGRRToHGBS_ANSI
#define __ISUP_BlockingCPCIToHGBS          __ISUP_BlockingCPCIToHGBS_ANSI
#define __ISUP_HGBSCheckLocallyBlocked     __ISUP_HGBSCheckLocallyBlocked_ANSI
#define __ISUP_HGBSCheckNotLocallyBlocked  __ISUP_HGBSCheckNotLocallyBlocked_ANSI
#define __ISUP_ResetCGRSToHGBS             __ISUP_ResetCGRSToHGBS_ANSI
#define __ISUP_ReleaseHGBRToCPC            __ISUP_ReleaseHGBRToCPC_ANSI
#define __ISUP_ResetCGRRToHGBR             __ISUP_ResetCGRRToHGBR_ANSI
#define __ISUP_ResetCGRSToHGBR             __ISUP_ResetCGRSToHGBR_ANSI
#define __ISUP_ResetCRSCommon1             __ISUP_ResetCRSCommon1_ANSI
#define __ISUP_ResetCRSCommon2             __ISUP_ResetCRSCommon2_ANSI
#define __ISUP_ResetCPCToCRS               __ISUP_ResetCPCToCRS_ANSI
#define __ISUP_ResetCRCRToCRS              __ISUP_ResetCRCRToCRS_ANSI
#define __ISUP_ResetAfterT5CPCToCRS        __ISUP_ResetAfterT5CPCToCRS_ANSI
#define __ISUP_ResetAfterT5CRCSToCRS       __ISUP_ResetAfterT5CRCSToCRS_ANSI
#define __ISUP_ResetCRSToCPC               __ISUP_ResetCRSToCPC_ANSI
#define __ISUP_ResetCRRToCPC               __ISUP_ResetCRRToCPC_ANSI
#define __ISUP_ResetCRRToCRCS              __ISUP_ResetCRRToCRCS_ANSI
#define __ISUP_ResetCRRToCRCR              __ISUP_ResetCRRToCRCR_ANSI
#define __ISUP_ResetCompleteCPCToCRR       __ISUP_ResetCompleteCPCToCRR_ANSI
#define __ISUP_ResetCompleteCPCIToCRR      __ISUP_ResetCompleteCPCIToCRR_ANSI
#define __ISUP_ResetCompleteCPCToCGRR      __ISUP_ResetCompleteCPCToCGRR_ANSI
#define __ISUP_ResetCGRSCommon1            __ISUP_ResetCGRSCommon1_ANSI
#define __ISUP_ResetCGRSCommon2            __ISUP_ResetCGRSCommon2_ANSI
#define __ISUP_UnblockingCGRSToBLR         __ISUP_UnblockingCGRSToBLR_ANSI
#define __ISUP_ResetCGRSToCPC              __ISUP_ResetCGRSToCPC_ANSI
#define __ISUP_ResetCGRRCommon1            __ISUP_ResetCGRRCommon1_ANSI
#define __ISUP_ResetCGRRToCRCS             __ISUP_ResetCGRRToCRCS_ANSI
#define __ISUP_ResetCGRRToCRCR             __ISUP_ResetCGRRToCRCR_ANSI
#define __ISUP_ResetCGRRToCPC              __ISUP_ResetCGRRToCPC_ANSI
#define __ISUP_IdleCircuit                 __ISUP_IdleCircuit_ANSI
#define __ISUP_UpdateNearEndCktState       __ISUP_UpdateNearEndCktState_ANSI
#define __ISUP_CheckRemotellyBlocked       __ISUP_CheckRemotellyBlocked_ANSI
                    
#endif


/*
 * ISUP timer strings
 */
#define ISUP_TIMER_T1_STRING    "T1"
#define ISUP_TIMER_T2_STRING    "T2"
#define ISUP_TIMER_T3_STRING    "T3"
#define ISUP_TIMER_T4_STRING    "T4"
#define ISUP_TIMER_T5_STRING    "T5"
#define ISUP_TIMER_T6_STRING    "T6"
#define ISUP_TIMER_T7_STRING    "T7"
#define ISUP_TIMER_T8_STRING    "T8"
#define ISUP_TIMER_T9_STRING    "T9"
#define ISUP_TIMER_T10_STRING   "T10"
#define ISUP_TIMER_T11_STRING   "T11"
#define ISUP_TIMER_T12_STRING   "T12"
#define ISUP_TIMER_T13_STRING   "T13"
#define ISUP_TIMER_T14_STRING   "T14"
#define ISUP_TIMER_T15_STRING   "T15"
#define ISUP_TIMER_T16_STRING   "T16"
#define ISUP_TIMER_T17_STRING   "T17"
#define ISUP_TIMER_T18_STRING   "T18"
#define ISUP_TIMER_T19_STRING   "T19"
#define ISUP_TIMER_T20_STRING   "T20"
#define ISUP_TIMER_T21_STRING   "T21"
#define ISUP_TIMER_T22_STRING   "T22"
#define ISUP_TIMER_T23_STRING   "T23"
#define ISUP_TIMER_T24_STRING   "T24"
#define ISUP_TIMER_T25_STRING   "T25"
#define ISUP_TIMER_T26_STRING   "T26"
#define ISUP_TIMER_T27_STRING   "T27"
#define ISUP_TIMER_T28_STRING   "T28"
#define ISUP_TIMER_T29_STRING   "T29"
#define ISUP_TIMER_T30_STRING   "T30"
#define ISUP_TIMER_T31_STRING   "T31"
#define ISUP_TIMER_T32_STRING   "T32"
#define ISUP_TIMER_T33_STRING   "T33"
#define ISUP_TIMER_T34_STRING   "T34"
#define ISUP_TIMER_T35_STRING   "T35"
#define ISUP_TIMER_T36_STRING   "T36"
#define ISUP_TIMER_T37_STRING   "T37"
#define ISUP_TIMER_T38_STRING   "T38"
#define ISUP_TIMER_T39_STRING   "T39"

/* ISUP additional ANSI timers */
#define ISUP_TIMER_TACCr_STRING  "TACCR"
#define ISUP_TIMER_TCCR_STRING   "TCCR"
#define ISUP_TIMER_TCCRr_STRING  "TCCRr"
#define ISUP_TIMER_TCGB_STRING   "TCGB"
#define ISUP_TIMER_TCRA_STRING   "TCRA"
#define ISUP_TIMER_TCRM_STRING   "TCRM"
#define ISUP_TIMER_TCVT_STRING   "TCVT"
#define ISUP_TIMER_TEXMd_STRING  "TEXMd"
#define ISUP_TIMER_TGRS_STRING   "TGRS"
#define ISUP_TIMER_THGA_STRING   "THGA"
#define ISUP_TIMER_TSCGA_STRING  "TSCGA"
#define ISUP_TIMER_TSCGAd_STRING "TSCGAd"

/*
 * ISUP resdb strings
 */
#define ISUP_CKT_GP_STR         "CircuitGroup"
#define ISUP_CIC_RULE_STR       "cicRule"
#define ISUP_USABLE_CICS_STR    "UsableCics"
#define ISUP_START_CIC_STR      "startCic"
#define ISUP_NUM_CICS_STR       "numberCics"

#define ISUP_XCHANGE_TYPE_STR   "exchangeType"
#define ISUP_SEG_SUPPORT_STR    "segmentationSupported"

#define ISUP_CONG_LEVEL1_STR     "congLevel1"
#define ISUP_CONG_LEVEL2_STR     "congLevel2"
#define ISUP_LOCCONG_TIMER_STR   "localcongTimer"
#define ISUP_AUTORSC_TIMER_STR   "repeatrsctimerVal"

/*
 * RIDs for the hash tables
 */
#define   ISUP_OPC_DPC_RID          1
#define   ISUP_VCIC_RID             2
#define   ISUP_PCIC_RID             3

/*
 * ANSI/ITU toggle
 */
#if defined(ANSI)

#define __ISUP_data     __ISUP_data_ANSI
#define __ISUP_hashGate __ISUP_hashGate_ANSI

#define __ISUP_Init_HashTables  __ISUP_Init_HashTables_ANSI
#define __ISUP_Term_HashTables  __ISUP_Term_HashTables_ANSI
#define ISUP_FindCkgpInfo       ISUP_FindCkgpInfo_ANSI
#define ISUP_CkgpExists         ISUP_CkgpExists_ANSI
#define ISUP_InsertCkgpInfo     ISUP_InsertCkgpInfo_ANSI
#define ISUP_DeleteCkgpInfo     ISUP_DeleteCkgpInfo_ANSI
#define ISUP_UpdateCkgpInfo     ISUP_UpdateCkgpInfo_ANSI
#define ISUP_IsCkgpInfoEmpty    ISUP_IsCkgpInfoEmpty_ANSI
#define ISUP_NumCkgps           ISUP_NumCkgps_ANSI
#define ISUP_DeleteAllCkgps     ISUP_DeleteAllCkgps_ANSI
#define ISUP_CopyCkgp           ISUP_CopyCkgp_ANSI
#define ISUP_InitCkgp           ISUP_InitCkgp_ANSI
#define ISUP_PrintCkgp          ISUP_PrintCkgp_ANSI
#define ISUP_PrintAllCkgps      ISUP_PrintAllCkgps_ANSI
#define ISUP_AddCicInfo         ISUP_AddCicInfo_ANSI
#define ISUP_AddUsableCic       ISUP_AddUsableCic_ANSI
#define ISUP_DelUsableCic       ISUP_DelUsableCic_ANSI
#define ISUP_AddUsableCics      ISUP_AddUsableCics_ANSI
#define ISUP_IsCicUsable        ISUP_IsCicUsable_ANSI
#define ISUP_InitOpcDpc         ISUP_InitOpcDpc_ANSI
#define ISUP_CopyOpcDpc         ISUP_CopyOpcDpc_ANSI
#define ISUP_AllocOpcDpc        ISUP_AllocOpcDpc_ANSI
#define ISUP_FindOpcDpc         ISUP_FindOpcDpc_ANSI
#define ISUP_FindOpcDpcStatic   ISUP_FindOpcDpcStatic_ANSI
#define ISUP_FreeOpcDpc         ISUP_FreeOpcDpc_ANSI
#define ISUP_DeleteOpcDpc       ISUP_DeleteOpcDpc_ANSI
#define ISUP_ReleaseOpcDpc      ISUP_ReleaseOpcDpc_ANSI
#define ISUP_ReleaseOpcDpcStatic     ISUP_ReleaseOpcDpcStatic_ANSI
#define ISUP_UpdateOpcDpc       ISUP_UpdateOpcDpc_ANSI
#define ISUP_PrintOpcDpc        ISUP_PrintOpcDpc_ANSI
#define ISUP_PrintAllOpcDpc     ISUP_PrintAllOpcDpc_ANSI
#define ISUP_PrintTmrHndl       ISUP_PrintTmrHndl_ANSI
#define ISUP_FindPndgTmrInfo    ISUP_FindPndgTmrInfo_ANSI
#define ISUP_PndgTmrExists      ISUP_PndgTmrExists_ANSI
#define ISUP_InsertPndgTmrInfo  ISUP_InsertPndgTmrInfo_ANSI
#define ISUP_DeletePndgTmrInfo  ISUP_DeletePndgTmrInfo_ANSI
#define ISUP_UpdatePndgTmrInfo  ISUP_UpdatePndgTmrInfo_ANSI
#define ISUP_IsPndgTmrInfoEmpty ISUP_IsPndgTmrInfoEmpty_ANSI
#define ISUP_NumPndgTmrs        ISUP_NumPndgTmrs_ANSI
#define ISUP_DeleteAllPndgTmrs  ISUP_DeleteAllPndgTmrs_ANSI
#define ISUP_CopyPndgTmr        ISUP_CopyPndgTmr_ANSI
#define ISUP_GetPndgTmrInfo     ISUP_GetPndgTmrInfo_ANSI
#define ISUP_PrintPndgTmr       ISUP_PrintPndgTmr_ANSI
#define ISUP_PrintAllPndgTmrs   ISUP_PrintAllPndgTmrs_ANSI
#define ISUP_InitCic            ISUP_InitCic_ANSI
#define ISUP_ClearCic           ISUP_ClearCic_ANSI
#define ISUP_CopyCic            ISUP_CopyCic_ANSI
#define ISUP_AllocCics          ISUP_AllocCics_ANSI
#define ISUP_AllocCic           ISUP_AllocCic_ANSI
#define ISUP_FindVcic           ISUP_FindVcic_ANSI
#define ISUP_FindPcic           ISUP_FindPcic_ANSI
#define ISUP_DeleteCic          ISUP_DeleteCic_ANSI
#define ISUP_ReleaseCic         ISUP_ReleaseCic_ANSI
#define ISUP_PrintCic           ISUP_PrintCic_ANSI
#define ISUP_PrintAllCics       ISUP_PrintAllCics_ANSI
#define ISUP_InitOpcDpcStat     ISUP_InitOpcDpcStat_ANSI
#define ISUP_CopyOpcDpcStat     ISUP_CopyOpcDpcStat_ANSI
#define ISUP_AllocOpcDpcStat    ISUP_AllocOpcDpcStat_ANSI
#define ISUP_FindOpcDpcStat     ISUP_FindOpcDpcStat_ANSI
#define ISUP_LockOpcDpcStatTable     ISUP_LockOpcDpcStatTable_ANSI
#define ISUP_UnLockOpcDpcStatTable   ISUP_UnLockOpcDpcStatTable_ANSI
#define ISUP_FreeOpcDpcStat     ISUP_FreeOpcDpcStat_ANSI
#define ISUP_DeleteOpcDpcStat   ISUP_DeleteOpcDpcStat_ANSI
#define ISUP_ReleaseOpcDpcStat  ISUP_ReleaseOpcDpcStat_ANSI
#define ISUP_UpdateOpcDpcStat   ISUP_UpdateOpcDpcStat_ANSI
#define ISUP_PrintOpcDpcStat    ISUP_PrintOpcDpcStat_ANSI
#define ISUP_PrintAllOpcDpcStat ISUP_PrintAllOpcDpcStat_ANSI
#define ISUP_GetPegDesc         ISUP_GetPegDesc_ANSI
#define ISUP_GetDestPegDesc     ISUP_GetDestPegDesc_ANSI
#define ISUP_GetCICPegDesc      ISUP_GetCICPegDesc_ANSI
#define ISUP_AllocCkgpList      ISUP_AllocCkgpList_ANSI
#define ISUP_FindCkgpList       ISUP_FindCkgpList_ANSI
#define ISUP_ReleaseCkgpList    ISUP_ReleaseCkgpList_ANSI
#define ISUP_SyncOpcDpcInfoWithStat  ISUP_SyncOpcDpcInfoWithStat_ANSI
#define ISUP_SyncOpcDpcInfo     ISUP_SyncOpcDpcInfo_ANSI
#define ISUP_AddNewOpcDpcInfoEntry   ISUP_AddNewOpcDpcInfoEntry_ANSI
#define ISUP_FindOpcDpcInfo     ISUP_FindOpcDpcInfo_ANSI
#define ISUP_ReleaseOpcDpcInfo  ISUP_ReleaseOpcDpcInfo_ANSI
#define ISUP_AllocAllLocalTables     ISUP_AllocAllLocalTables_ANSI
#define ISUP_AllocLocalTable    ISUP_AllocLocalTable_ANSI
#define ISUP_InitCkgpList       ISUP_InitCkgpList_ANSI
#define __ISUP_IsInitialized    __ISUP_IsInitialized_ANSI
#define ISUP_IsRouteExists      ISUP_IsRouteExists_ANSI

#define ISUP_AllocCicMsgBuf     ISUP_AllocCicMsgBuf_ANSI
#define ISUP_InitCICMsgBuf      ISUP_InitCICMsgBuf_ANSI
#define ISUP_ReleaseCicMsgBuf   ISUP_ReleaseCicMsgBuf_ANSI
#define ISUP_FindPcicMsgBuf     ISUP_FindPcicMsgBuf_ANSI

#define ISUP_UpdateCktGrpInfo   ISUP_UpdateCktGrpInfo_ANSI
#define ISUP_InsertCktGrpInfo   ISUP_InsertCktGrpInfo_ANSI
#define ISUP_FindCktGrpInfo     ISUP_FindCktGrpInfo_ANSI

#elif defined(CCITT) || defined(PRC) || defined(TTC)

#define __ISUP_data     __ISUP_data_CCITT
#define __ISUP_hashGate __ISUP_hashGate_CCITT

#define __ISUP_Init_HashTables  __ISUP_Init_HashTables_CCITT
#define __ISUP_Term_HashTables  __ISUP_Term_HashTables_CCITT
#define ISUP_FindCkgpInfo       ISUP_FindCkgpInfo_CCITT
#define ISUP_CkgpExists         ISUP_CkgpExists_CCITT
#define ISUP_InsertCkgpInfo     ISUP_InsertCkgpInfo_CCITT
#define ISUP_DeleteCkgpInfo     ISUP_DeleteCkgpInfo_CCITT
#define ISUP_UpdateCkgpInfo     ISUP_UpdateCkgpInfo_CCITT
#define ISUP_IsCkgpInfoEmpty    ISUP_IsCkgpInfoEmpty_CCITT
#define ISUP_NumCkgps           ISUP_NumCkgps_CCITT
#define ISUP_DeleteAllCkgps     ISUP_DeleteAllCkgps_CCITT
#define ISUP_CopyCkgp           ISUP_CopyCkgp_CCITT
#define ISUP_InitCkgp           ISUP_InitCkgp_CCITT
#define ISUP_PrintCkgp          ISUP_PrintCkgp_CCITT
#define ISUP_PrintAllCkgps      ISUP_PrintAllCkgps_CCITT
#define ISUP_AddCicInfo         ISUP_AddCicInfo_CCITT
#define ISUP_AddUsableCic       ISUP_AddUsableCic_CCITT
#define ISUP_DelUsableCic       ISUP_DelUsableCic_CCITT
#define ISUP_AddUsableCics      ISUP_AddUsableCics_CCITT
#define ISUP_IsCicUsable        ISUP_IsCicUsable_CCITT
#define ISUP_InitOpcDpc         ISUP_InitOpcDpc_CCITT
#define ISUP_CopyOpcDpc         ISUP_CopyOpcDpc_CCITT
#define ISUP_AllocOpcDpc        ISUP_AllocOpcDpc_CCITT
#define ISUP_FindOpcDpc         ISUP_FindOpcDpc_CCITT
#define ISUP_FindOpcDpcStatic   ISUP_FindOpcDpcStatic_CCITT
#define ISUP_FreeOpcDpc         ISUP_FreeOpcDpc_CCITT
#define ISUP_DeleteOpcDpc       ISUP_DeleteOpcDpc_CCITT
#define ISUP_ReleaseOpcDpc      ISUP_ReleaseOpcDpc_CCITT
#define ISUP_ReleaseOpcDpcStatic     ISUP_ReleaseOpcDpcStatic_CCITT
#define ISUP_UpdateOpcDpc       ISUP_UpdateOpcDpc_CCITT
#define ISUP_PrintOpcDpc        ISUP_PrintOpcDpc_CCITT
#define ISUP_PrintAllOpcDpc     ISUP_PrintAllOpcDpc_CCITT
#define ISUP_PrintTmrHndl       ISUP_PrintTmrHndl_CCITT
#define ISUP_FindPndgTmrInfo    ISUP_FindPndgTmrInfo_CCITT
#define ISUP_PndgTmrExists      ISUP_PndgTmrExists_CCITT
#define ISUP_InsertPndgTmrInfo  ISUP_InsertPndgTmrInfo_CCITT
#define ISUP_DeletePndgTmrInfo  ISUP_DeletePndgTmrInfo_CCITT
#define ISUP_UpdatePndgTmrInfo  ISUP_UpdatePndgTmrInfo_CCITT
#define ISUP_IsPndgTmrInfoEmpty ISUP_IsPndgTmrInfoEmpty_CCITT
#define ISUP_NumPndgTmrs        ISUP_NumPndgTmrs_CCITT
#define ISUP_DeleteAllPndgTmrs  ISUP_DeleteAllPndgTmrs_CCITT
#define ISUP_CopyPndgTmr        ISUP_CopyPndgTmr_CCITT
#define ISUP_GetPndgTmrInfo     ISUP_GetPndgTmrInfo_CCITT
#define ISUP_PrintPndgTmr       ISUP_PrintPndgTmr_CCITT
#define ISUP_PrintAllPndgTmrs   ISUP_PrintAllPndgTmrs_CCITT
#define ISUP_InitCic            ISUP_InitCic_CCITT
#define ISUP_ClearCic           ISUP_ClearCic_CCITT
#define ISUP_CopyCic            ISUP_CopyCic_CCITT
#define ISUP_AllocCics          ISUP_AllocCics_CCITT
#define ISUP_AllocCic           ISUP_AllocCic_CCITT
#define ISUP_FindVcic           ISUP_FindVcic_CCITT
#define ISUP_FindPcic           ISUP_FindPcic_CCITT
#define ISUP_DeleteCic          ISUP_DeleteCic_CCITT
#define ISUP_ReleaseCic         ISUP_ReleaseCic_CCITT
#define ISUP_PrintCic           ISUP_PrintCic_CCITT
#define ISUP_PrintAllCics       ISUP_PrintAllCics_CCITT
#define ISUP_InitOpcDpcStat     ISUP_InitOpcDpcStat_CCITT
#define ISUP_CopyOpcDpcStat     ISUP_CopyOpcDpcStat_CCITT
#define ISUP_AllocOpcDpcStat    ISUP_AllocOpcDpcStat_CCITT
#define ISUP_FindOpcDpcStat     ISUP_FindOpcDpcStat_CCITT
#define ISUP_LockOpcDpcStatTable     ISUP_LockOpcDpcStatTable_CCITT
#define ISUP_UnLockOpcDpcStatTable   ISUP_UnLockOpcDpcStatTable_CCITT
#define ISUP_FreeOpcDpcStat     ISUP_FreeOpcDpcStat_CCITT
#define ISUP_DeleteOpcDpcStat   ISUP_DeleteOpcDpcStat_CCITT
#define ISUP_ReleaseOpcDpcStat  ISUP_ReleaseOpcDpcStat_CCITT
#define ISUP_UpdateOpcDpcStat   ISUP_UpdateOpcDpcStat_CCITT
#define ISUP_PrintOpcDpcStat    ISUP_PrintOpcDpcStat_CCITT
#define ISUP_PrintAllOpcDpcStat ISUP_PrintAllOpcDpcStat_CCITT
#define ISUP_GetPegDesc         ISUP_GetPegDesc_CCITT
#define ISUP_GetDestPegDesc     ISUP_GetDestPegDesc_CCITT
#define ISUP_GetCICPegDesc      ISUP_GetCICPegDesc_CCITT
#define ISUP_AllocCkgpList      ISUP_AllocCkgpList_CCITT
#define ISUP_FindCkgpList       ISUP_FindCkgpList_CCITT
#define ISUP_ReleaseCkgpList    ISUP_ReleaseCkgpList_CCITT
#define ISUP_SyncOpcDpcInfoWithStat  ISUP_SyncOpcDpcInfoWithStat_CCITT
#define ISUP_SyncOpcDpcInfo     ISUP_SyncOpcDpcInfo_CCITT
#define ISUP_AddNewOpcDpcInfoEntry   ISUP_AddNewOpcDpcInfoEntry_CCITT
#define ISUP_FindOpcDpcInfo     ISUP_FindOpcDpcInfo_CCITT
#define ISUP_ReleaseOpcDpcInfo  ISUP_ReleaseOpcDpcInfo_CCITT
#define ISUP_AllocAllLocalTables     ISUP_AllocAllLocalTables_CCITT
#define ISUP_AllocLocalTable    ISUP_AllocLocalTable_CCITT
#define ISUP_InitCkgpList       ISUP_InitCkgpList_CCITT
#define __ISUP_IsInitialized    __ISUP_IsInitialized_CCITT
#define ISUP_IsRouteExists      ISUP_IsRouteExists_CCITT

#define ISUP_AllocCicMsgBuf     ISUP_AllocCicMsgBuf_CCITT
#define ISUP_InitCICMsgBuf      ISUP_InitCICMsgBuf_CCITT
#define ISUP_ReleaseCicMsgBuf   ISUP_ReleaseCicMsgBuf_CCITT
#define ISUP_FindPcicMsgBuf     ISUP_FindPcicMsgBuf_CCITT

#endif

/*
 * Global functions
 */
int     __ISUP_Init_HashTables_CCITT();
void    __ISUP_Term_HashTables_CCITT();

int     __ISUP_Init_HashTables_ANSI();
void    __ISUP_Term_HashTables_ANSI();

/*
 * Circuit group functions
 */
int             ISUP_FindCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info,
                                 ITS_USHORT ckgp_id,
                                 ISUP_CKGP_INFO* l_ckgp_info);
ITS_BOOLEAN     ISUP_CkgpExists(ISUP_OPC_DPC_STAT *opc_dpc_info,
                                ITS_USHORT ckgp_id);
int             ISUP_InsertCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info,
                                    ISUP_CKGP_INFO *ckgp_info);
int             ISUP_DeleteCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info,
                                    ITS_USHORT ckgp_id);
int             ISUP_UpdateCkgpInfo(ISUP_OPC_DPC_STAT *opc_dpc_info,
                                    ITS_USHORT ckgp_id,
                                    ISUP_CKGP_INFO *l_ckgp_info);

/* Modified above Circuit group functions
 * to minimise DSM access
 */
/********************************************************/
ISUP_CKGP_LIST * ISUP_FindCktGrpInfo (
                        ISUP_OPC_DPC_STAT *opc_dpc_info,
                        ITS_USHORT ckgp_id,
                        ISUP_CKGP_INFO* l_ckgp_info,
                        ITS_INT *exists);
int              ISUP_InsertCktGrpInfo (
                        ISUP_OPC_DPC_STAT *opc_dpc_info,
                        ISUP_CKGP_INFO *ckgp_info,
                        ISUP_CKGP_LIST *ckgp_list);
int              ISUP_UpdateCktGrpInfo (
                        ISUP_OPC_DPC_STAT *opc_dpc_info,
                        ITS_USHORT ckgp_id,
                        ISUP_CKGP_INFO *l_ckgp_info,
                        ISUP_CKGP_LIST *ckgp_list);
/********************************************************/

ITS_BOOLEAN     ISUP_IsCkgpInfoEmpty(ISUP_OPC_DPC_STAT *opc_dpc_info);
int             ISUP_NumCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info);
int             ISUP_DeleteAllCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info);
int             ISUP_CopyCkgp(ISUP_CKGP_INFO *dest,
                              ISUP_CKGP_INFO *src);
void            ISUP_InitCkgp(ISUP_CKGP_INFO *ckgp,
                              ITS_USHORT cktGpId);
void            ISUP_PrintCkgp(ISUP_CKGP_INFO *ckgp);
void            ISUP_PrintAllCkgps(ISUP_OPC_DPC_STAT *opc_dpc_info);

/*
 * CIC functions
 */
int         ISUP_AddCicInfo(ISUP_OPC_DPC_STAT *opc_dpc_info);
int         ISUP_AddUsableCic(ISUP_OPC_DPC_STAT *opc_dpc_info,
                              ISUP_CKGP_INFO *ckgp_info, 
                              ITS_USHORT cic_index, ITS_OCTET cicRule);
int         ISUP_DelUsableCic(ISUP_OPC_DPC_STAT *opc_dpc_info,
                              ISUP_CKGP_INFO *ckgp_info, 
                              ITS_USHORT cic_index);
int         ISUP_AddUsableCics(ISUP_OPC_DPC_STAT *opc_dpc_info,
                               ISUP_CKGP_INFO *ckgp_info, 
                               ITS_USHORT cic_index,
                               ITS_USHORT number_cics,
                               ITS_OCTET cicRule);
ITS_BOOLEAN ISUP_IsCicUsable(ISUP_OPC_DPC_STAT *odInfo, ITS_USHORT cic);
ITS_BOOLEAN ISUP_IsCicsNonExists(ISUP_OPC_DPC_STAT *odInfo,
                                ITS_USHORT scic,
                                ITS_USHORT count);
ITS_BOOLEAN ISUP_IsCicsExists(ISUP_OPC_DPC_STAT *odInfo, ITS_USHORT scic,
                              ITS_USHORT count);


/*
 * OPC/DPC configuration info functions 
 */
ITSSS7DLLAPI void        ISUP_InitOpcDpc(ISUP_OPC_DPC_INFO *od_info,
                                         MTP3_HEADER opcid_dpcid,
                                         ISUP_VAR_TYPE variant_type);
ITSSS7DLLAPI int         ISUP_CopyOpcDpc(ISUP_OPC_DPC_INFO *dest,
                                         ISUP_OPC_DPC_INFO *src);
ITSSS7DLLAPI int         ISUP_AllocOpcDpc(MTP3_HEADER opc_dpc_ni, 
                                          ISUP_VAR_TYPE varType,
                                          ISUP_OPC_DPC_INFO *info);
ITSSS7DLLAPI int         ISUP_FindOpcDpc(MTP3_HEADER opc_dpc_ni, 
                                         ISUP_OPC_DPC_INFO *l_od_info,
                                         ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int         ISUP_FindOpcDpcStatic(MTP3_HEADER opc_dpc_ni, 
                                         ISUP_OPC_DPC_INFO *l_od_info);

ITSSS7DLLAPI int         ISUP_FreeOpcDpc(ISUP_OPC_DPC_INFO *l_od_info);
ITSSS7DLLAPI int         ISUP_DeleteOpcDpc(MTP3_HEADER opcid_dpcid);
ITSSS7DLLAPI int         ISUP_ReleaseOpcDpc(ISUP_OPC_DPC_INFO *opc_dpc_info);
ITSSS7DLLAPI int         ISUP_ReleaseOpcDpcStatic(ISUP_OPC_DPC_INFO *opc_dpc_info);
ITSSS7DLLAPI int         ISUP_UpdateOpcDpc(ISUP_OPC_DPC_INFO *opc_dpc);
ITSSS7DLLAPI int         ISUP_SyncOpcDpcInfoWithStat(ISUP_OPC_DPC_STAT *od_stat);
ITSSS7DLLAPI int         ISUP_PrintOpcDpc(ITS_INT key, ITS_POINTER ent,
                                          void *in, void *out);
ITSSS7DLLAPI int         ISUP_PrintAllOpcDpc();
ITSSS7DLLAPI void        ISUP_PrintTmrHndl(ISUP_OPC_DPC_STAT *opc_dpc_stat);


ITSSS7DLLAPI void        ISUP_InitOpcDpcStat(ISUP_OPC_DPC_STAT *od_stat,
                                         MTP3_HEADER opcid_dpcid, 
                                         ISUP_VAR_TYPE varType);
ITSSS7DLLAPI int         ISUP_CopyOpcDpcStat(ISUP_OPC_DPC_STAT *dest,
                                         ISUP_OPC_DPC_STAT *src);
ITSSS7DLLAPI ISUP_OPC_DPC_STAT*   ISUP_AllocOpcDpcStat(MTP3_HEADER opc_dpc_ni,
                                                    ISUP_VAR_TYPE variant_type);
ITSSS7DLLAPI ISUP_OPC_DPC_STAT*   ISUP_FindOpcDpcStat(MTP3_HEADER opc_dpc_ni,
                                                      ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int                  ISUP_LockOpcDpcStatTable();
ITSSS7DLLAPI int                  ISUP_UnLockOpcDpcStatTable();

ITSSS7DLLAPI int         ISUP_UpdateOpcDpcStat(ISUP_OPC_DPC_STAT *od_stat); 
ITSSS7DLLAPI int         ISUP_FreeOpcDpcStat(ISUP_OPC_DPC_STAT *l_od_stat);
ITSSS7DLLAPI int         ISUP_DeleteOpcDpcStat(MTP3_HEADER opcid_dpcid,
                                               ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int         ISUP_ReleaseOpcDpcStat(ISUP_OPC_DPC_STAT *opc_dpc_stat,
                                                ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int         ISUP_PrintOpcDpcStat(ITS_POINTER ent, 
                                              void *in, void *out);
ITSSS7DLLAPI int         ISUP_PrintAllOpcDpcStat();

ITSSS7DLLAPI void        ISUP_HashTableIterate(HASH_IterateEntryProc proc,
                                               void *in,void *out);
/*
 * Dpc-transport table functions
 */

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
int ISUP_DpcTransAddEntry(ITS_UINT dpc);

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
int ISUP_DpcTransFindEntry(ITS_UINT dpc, ITS_INT* transId);

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
int ISUP_DpcTransUpdateEntry(ITS_UINT dpc, ITS_INT transId);

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
ITSSS7DLLAPI void  ISUP_DpcTransTableIterate();


ITSSS7DLLAPI ITS_BOOLEAN __ISUP_IsInitialized(MTP3_HEADER hdr);
ITSSS7DLLAPI int         ISUP_AllocAllLocalTables();

ITSSS7DLLAPI ITS_BOOLEAN ISUP_IsRouteExists(ITS_UINT dpc, ITS_OCTET sio);

/*
 * The vcic is generated by the stack. It starts with 1 and rolls over
 * after 65535.
 */
ITS_CTXT ISUP_NextVcic_CCITT();

/*
 * Pending timer functions
 */
ITSSS7DLLAPI int ISUP_FindPndgTmrInfo(ISUP_CIC_INFO *cic_info, 
                                      ITS_USHORT timer_id,
                                      ISUP_PNDG_TMR_INFO* l_pndg_tmr_info);
ITSSS7DLLAPI ITS_BOOLEAN   ISUP_PndgTmrExists(ISUP_CIC_INFO *cic_info,
                                              ITS_USHORT timer_id);
ITSSS7DLLAPI int     ISUP_InsertPndgTmrInfo(ISUP_CIC_INFO *cic_info,
                                            ISUP_PNDG_TMR_INFO *pndg_tmr_info);
ITSSS7DLLAPI int     ISUP_DeletePndgTmrInfo(ISUP_CIC_INFO *cic_info,
                                            ITS_USHORT timer_id);
ITSSS7DLLAPI int     ISUP_UpdatePndgTmrInfo(ISUP_CIC_INFO *cic_info,
                                            ITS_USHORT timer_id, 
                                            ISUP_PNDG_TMR_INFO *pndg_tmr_info);
ITSSS7DLLAPI ITS_BOOLEAN   ISUP_IsPndgTmrInfoEmpty(ISUP_CIC_INFO *cic_info);
ITSSS7DLLAPI int     ISUP_NumPndgTmrs(ISUP_CIC_INFO *cic_info);
ITSSS7DLLAPI int     ISUP_DeleteAllPndgTmrs(ISUP_CIC_INFO *cic_info);
ITSSS7DLLAPI int     ISUP_CopyPndgTmr(ISUP_PNDG_TMR_INFO *dest,
                                      ISUP_PNDG_TMR_INFO *src);
ITSSS7DLLAPI ISUP_PNDG_TMR_INFO* ISUP_GetPndgTmrInfo(ISUP_CIC_INFO *cic_info, 
                                                     ITS_USHORT index);
ITSSS7DLLAPI void    ISUP_PrintPndgTmr(ISUP_PNDG_TMR_INFO *tmr);
ITSSS7DLLAPI void    ISUP_PrintAllPndgTmrs(ISUP_CIC_INFO *cic_info);

char* ISUP_GetPegDesc(ITS_UINT peg_index);
char* ISUP_GetDestPegDesc(ITS_UINT peg_index);
char* ISUP_GetCICPegDesc(ITS_UINT peg_index);




/*
 * CIC functions
 */
ITSSS7DLLAPI void       ISUP_InitCic(ISUP_CIC_INFO *cic_info,
                                     ITS_CTXT vcic,
                                     ISUP_PCIC pcic,
                                     ITS_OCTET cicRule);
ITSSS7DLLAPI void       ISUP_ClearCic(ISUP_CIC_INFO *cic_info);
ITSSS7DLLAPI int        ISUP_CopyCic(ISUP_CIC_INFO *dest,
                                     ISUP_CIC_INFO *src);
ITSSS7DLLAPI int        ISUP_AllocCics(ITS_CTXT start_vcic,
                                       ISUP_PCIC start_pcic,
                                       ITS_USHORT num_cics,
                                       ITS_OCTET cicRule);
ITSSS7DLLAPI ISUP_CIC_INFO*  ISUP_AllocCic(ITS_CTXT vcic, 
                                           ISUP_PCIC pcic,
                                           ITS_OCTET cicRule);
ITSSS7DLLAPI ITS_CTXT*  ISUP_AllocVcic();
ITSSS7DLLAPI ITS_CTXT*  ISUP_FindVcic();
ITSSS7DLLAPI int  ISUP_ReleaseVcic(ITS_CTXT* current_vcic);
ITSSS7DLLAPI ISUP_CIC_INFO*  ISUP_FindPcic(ISUP_PCIC pcic, ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int        ISUP_DeleteCic(ISUP_PCIC pcic);
ITSSS7DLLAPI int        ISUP_ReleaseCic(ISUP_CIC_INFO *cic_info,
                                                ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI int        ISUP_PrintCic(ITS_POINTER ent, void *in, void *out);
ITSSS7DLLAPI int        ISUP_PrintAllCics();

ITSSS7DLLAPI ISUP_CIC_MSG_INFO*  ISUP_FindPcicMsgBuf(ISUP_PCIC pcic, 
                                      ITS_BOOLEAN findFlag, ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI ISUP_CIC_MSG_INFO*  ISUP_AllocCicMsgBuf(ISUP_CIC_INFO *cic_info);
ITSSS7DLLAPI int   ISUP_ReleaseCicMsgBuf(ISUP_CIC_MSG_INFO *cic_msg, 
                                      ITS_BOOLEAN commitFlag, ITS_BOOLEAN isdsmlocal);
ITSSS7DLLAPI void  ISUP_InitCicMsgBuf(ISUP_CIC_INFO *cic_info,
                                      ISUP_CIC_MSG_INFO *cic_msg);

ITSSS7DLLAPI int   ISUP_ReleasePcic(ISUP_CIC_INFO *cic_info, ISUP_PCIC pcic);

/* DPC state and Remote ISUP status related functions */
ITSSS7DLLAPI void ISUP_SetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info, 
                                   ISUP_REMOTE_ISUP_STATUS state);
ITSSS7DLLAPI void ISUP_GetRemoteIsupState(ISUP_OPC_DPC_INFO *config_info,
                                   ISUP_REMOTE_ISUP_STATUS *state);
ITSSS7DLLAPI void ISUP_SetDpcState(ISUP_OPC_DPC_INFO *config_info, 
                                   ISUP_DEST_STATUS state);
ITSSS7DLLAPI void ISUP_GetDpcState(ISUP_OPC_DPC_INFO *config_info,
                                   ISUP_DEST_STATUS *state);

/*
 * Circuit Supervision Control (CSC) functions
 */
ITSSS7DLLAPI void __ISUP_CSC_Received_BLA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_BLO(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CGB(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CGBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CGU(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CGUA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_GRA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_GRS(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_RSC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_UBA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_UBL(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CQM(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CQR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_UCIC(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                              ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_CCR(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);
ITSSS7DLLAPI void __ISUP_CSC_Received_LPA(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);


ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT12(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT13(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT14(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT15(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT16(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT17(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT18(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT19(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT20(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT21(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT22(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT23(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT24(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT25(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT26(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT27(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT34(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutTCCR(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutTCCRR(ISUP_TIMER_ENTRY* t_entry, 
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);

/*
 * CSC timers helper functions
 */
ITSSS7DLLAPI int __ISUP_StartBLOTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopBLOTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartBLORepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartRELTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopRELTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartUBLTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopUBLTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartUBLRepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartRSCTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopRSCTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartRSCRepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCGBTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopCGBTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCGBRepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCGUTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopCGUTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCGURepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartGRSTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StopGRSTimers(ISUP_CIC_INFO *cic_rec, 
                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartGRSRepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCVTTimers(ISUP_CIC_INFO *cic_rec, 
                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI int __ISUP_StartCVTRepeatTimer(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_StartCRS(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void __ISUP_CSC_BlockingBLS(ISUP_CIC_INFO *cic_rec,
                            ISUP_OPC_DPC_INFO *config_info);

/*
 * CSC validation and helper functions
 */
typedef ITS_BOOLEAN (*ISUP_PROC_FUNC)(ISUP_CIC_INFO *, ISUP_OPC_DPC_INFO *);

ITSSS7DLLAPI int __ISUP_Validate_RangeStatus(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                                ISUP_OPC_DPC_INFO *config_info, 
                                ITS_ISUP_IE *rs_ie,
                                ITS_OCTET *sup_msg_type,
                                ITS_USHORT *cic);
ITSSS7DLLAPI int __ISUP_GetAffectedCics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                           ITS_USHORT *affected_cics, 
                           ITS_USHORT *num_affected_cics);
ITSSS7DLLAPI int __ISUP_GetGRACics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                      ITS_USHORT *set_cics, 
                      ITS_USHORT *num_set_cics,
                      ITS_USHORT *unset_cics,
                      ITS_USHORT *num_unset_cics);
ITSSS7DLLAPI int __ISUP_GetGRSCics(ITS_USHORT cic, ITS_ISUP_IE *rs_ie, 
                      ITS_USHORT *affected_cics, 
                      ITS_USHORT *num_afefcted_cics);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ProcessAffectedCics(ITS_USHORT *affected_cics, 
                                       ITS_USHORT num_affected_cics,
                                       ISUP_PROC_FUNC func,
                                       ISUP_CIC_INFO *cic_rec,
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CompareCGBAWithCGB(ITS_EVENT *cgba_ev,
                                      ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CompareCGUAWithCGU(ITS_EVENT *cgua_ev,
                                      ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CompareGRAWithGRS(ITS_EVENT *gra_ev,
                                     ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CompareCGUWithGRS(ISUP_CIC_INFO *cic_rec,
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CompareCGBWithGRS(ISUP_CIC_INFO *cic_rec,
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingMGBRToCPCO(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_MGBSCheckLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_MGBSCheckNotLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                              ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingMGBSToBLS(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingMGBRToBLR(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingBLSToCPC(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCRRToBLS(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCPCIToBLS(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRSToBLS(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRSToBLS(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingBLRToCPCO(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRRToBLR(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRSToBLR(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRRToBLR(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCPCIToBLR(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSToMGBS(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRToMGBR(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSToMGBR(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingHGBSToHLB(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ReleaseHGBSToCPC(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRSToHLB(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRSToHLB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingHGBSToHLB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingHGBRToHRB(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRSToHRB(ISUP_CIC_INFO *cic_rec,
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCRRToHRB(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRSToHRB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRRToHRB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCPCIToHRB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingHGBRToHRB(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCRRToHGBS(ISUP_CIC_INFO *cic_rec, 
                                     ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCGRRToHGBS(ITS_USHORT *affected_cics,
                                      ITS_USHORT num_affected_cics,
                                      ISUP_CIC_INFO *cic_rec,
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingCPCIToHGBS(ISUP_CIC_INFO *cic_rec, 
                                      ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_HGBSCheckLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_HGBSCheckNotLocallyBlocked(ISUP_CIC_INFO *cic_rec, 
                                              ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSToHGBS(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ReleaseHGBRToCPC(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRToHGBR(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSToHGBR(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRSCommon1(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRSCommon2(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCPCToCRS(ISUP_CIC_INFO *cic_rec, 
                                 ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRCRToCRS(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetAfterT5CPCToCRS(ISUP_CIC_INFO *cic_rec, 
                                        ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetAfterT5CRCSToCRS(ISUP_CIC_INFO *cic_rec, 
                                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRSToCPC(ISUP_CIC_INFO *cic_rec, 
                                 ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRRToCPC(ISUP_CIC_INFO *cic_rec, 
                                 ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRRToCRCS(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCRRToCRCR(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCToCRR(ISUP_CIC_INFO *cic_rec, 
                                         ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCIToCRR(ISUP_CIC_INFO *cic_rec, 
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCOToCRR(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCIToCGRR(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCToCGRR(ITS_EVENT *msg,
                                          ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSCommon1(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSCommon2(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingCGRSToBLR(ISUP_CIC_INFO *cic_rec, 
                                       ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRSToCPC(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRCommon1(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRToCRCS(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRToCRCR(ISUP_CIC_INFO *cic_rec, 
                                   ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRToCPC(ISUP_CIC_INFO *cic_rec, 
                                  ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_IdleCircuit(ISUP_CIC_INFO *cic_rec, 
                               ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCompleteCPCToCGRR(ITS_EVENT *msg,
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_Change_RangeStatus(ITS_EVENT *msg, 
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ISUP_RANGE_AND_STATUS rs_ie, 
                                    ITS_OCTET msgType);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetCGRRCommon0(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_HandleUnexpectedCGBA(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_OCTET sup_msg_type,
                                    ITS_ISUP_IE rs_ie,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_HandleUnexpectedCGUA(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_OCTET sup_msg_type,
                                    ITS_ISUP_IE rs_ie,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetMGBSToCPC(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ResetMGBRToCPC(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_GetGRARangeNStatus(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT  *affected_cics,
                                    ITS_USHORT  num_affected_cics,
                                    ISUP_RANGE_AND_STATUS *rs);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_GetCGBARangeNStatus(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT  *affected_cics,
                                    ITS_USHORT  num_affected_cics,
                                    ISUP_RANGE_AND_STATUS *rs);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_GetCGUARangeNStatus(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT  *affected_cics,
                                    ITS_USHORT  num_affected_cics,
                                    ISUP_RANGE_AND_STATUS *rs);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UpdateNearEndCktState(ITS_EVENT *msg,
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_CheckRemotellyBlocked(ISUP_CIC_INFO *cic_rec, 
                                    ISUP_OPC_DPC_INFO *config_info);

#if defined (ANSI)
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingMGBRCommon1(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics,
                                    ITS_OCTET sup_msg_type,
                                    ITS_ISUP_IE rs_ie);

ITSSS7DLLAPI ITS_BOOLEAN __ISUP_BlockingMGBSCommon1(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics,
                                    ITS_OCTET sup_msg_type,
                                    ITS_ISUP_IE rs_ie);

ITSSS7DLLAPI ITS_BOOLEAN __ISUP_UnblockingMGBRCommon1(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics,
                                    ITS_ISUP_IE rs_ie);

ITSSS7DLLAPI ITS_BOOLEAN __ISUP_IdleRemoteBlockCircut(ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);

#endif
/* UCIC specific function */
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_IsRangeCICUnequipped( ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_USHORT *affected_cics,
                                    ITS_USHORT num_affected_cics);

/*
 * these functions will be moved to ansi later
 */
ITSSS7DLLAPI ITS_BOOLEAN 
__ISUP_BlockingBLRToCPC(ISUP_CIC_INFO *cic_rec, 
                        ISUP_OPC_DPC_INFO *config_info);



#if defined(CCITT) || defined(PRC) || defined(TTC)

/*
 * initialization and termination
 */
int ISUP_Init_CCITT(RESFILE_Manager *res, const char *section);
void ISUP_Term_CCITT(void);

/*
 * Message encode, decode and validation
 */
ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_ValidateMsgParsing_CCITT(ITS_OCTET msgType, ISUP_MSG_DESC* mDesc, 
                                ITS_OCTET* params, ITS_USHORT len);

ITSSS7DLLAPI ITS_OCTET 
__ISUP_ValidateParamCompatability_CCITT(ITS_Class isup_variant,
                                        ITS_EVENT *event, ITS_OCTET mType );

ITSSS7DLLAPI int ISUP_MTP3Decode_CCITT(ITS_OCTET *data, 
                                       ITS_USHORT len, 
                                       ITS_OCTET mType, 
                                       ITS_ISUP_IE *ies, 
                                       int *ieCount, 
                                       ITS_Class isup_variant);
ITSSS7DLLAPI int ISUP_MTP3Encode_CCITT(ITS_OCTET *data, 
                          ITS_USHORT *len, 
                          ITS_OCTET type,
                          ITS_ISUP_IE *ies, 
                          int ieCount, 
                          ITS_Class isup_variant);
/* 
 * ISUP Message and Timeout handling functions 
 */
ITSSS7DLLAPI int __ISUP_HandleTimeout_CCITT(ITS_EVENT *event);

ITSSS7DLLAPI int __ISUP_HandleMsg_CCITT(ITS_EVENT* event, ITS_OCTET source);


/*
 * Functions for SEGmentation Procedure
 */
ITSSS7DLLAPI void
__ISUP_SegmentOverlenMsg_ITU93(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                                ITS_OCTET type, ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void
__ISUP_HandleOverlenMsg_CCITT(__ISUP_MsgHandlerProc msgProc,
                        ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void
__ISUP_StoreOverlenMsg_CCITT(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                             ISUP_OPC_DPC_INFO *config_info, ITS_OCTET msgType);
ITSSS7DLLAPI void
__ISUP_AssembleOverlenMsg_CCITT(__ISUP_MsgHandlerProc msgProc, ITS_EVENT *ev,
                      ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO *config_info,
                                                              ITS_OCTET src);
ITSSS7DLLAPI void
__ISUP_FillLabel_CCITT(ITS_EVENT *event, ISUP_CIC_INFO *cic_rec,
                                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
__ISUP_SendOverlenMsg_ITU93(ITS_OCTET type, ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info,
                                    ITS_ISUP_IE *ies, int ieCount);

ITSSS7DLLAPI ITS_BOOLEAN
__ISUP_SplitOverlenMsg_ITU93(ITS_ISUP_IE *ies, int ieCount,
                                   ITS_ISUP_IE *savedMsgParam,
                                      int *savedMsgParamCount,
                                 ITS_ISUP_IE *segmentMsgParam,
                                    int *segmentMsgParamCount, int *sgm_length);

/* Continuity Timer Timeout Function - Only for ITU */
ITSSS7DLLAPI void __ISUP_CSC_Received_TimeoutT36(ISUP_TIMER_ENTRY* t_entry,
                                    ISUP_CIC_INFO *cic_rec,
                                    ISUP_OPC_DPC_INFO *config_info);

/* 
 * SPRC functions
 */
ITSSS7DLLAPI int SPRC_SendIsupToMTP3_CCITT(ITS_EVENT* event, ITS_CTXT cic);
ITSSS7DLLAPI void SPRC_SendIsupToApp_CCITT(ITS_CTXT vcic,
                                           ITS_EVENT* event);
ITSSS7DLLAPI void SPRC_SendTimeoutIndicToApp_CCITT(ITS_CTXT vcic,
                                        ISUP_TIMER_ENTRY* tdata);
ITSSS7DLLAPI void SPRC_SendErrorToApp_CCITT(ITS_OCTET msgType,
                                             ITS_UINT errId,
                                             ISUP_CIC_INFO *cic_rec);
ITSSS7DLLAPI void SPRC_SendIndToApp_CCITT(ITS_UINT indId, 
                                        ISUP_CIC_INFO *cic_rec);
ITSSS7DLLAPI void SPRC_SendIsupIndToApp_CCITT(ITS_UINT indId,
                                        ITS_EVENT* event,
                                        ITS_OCTET src);

ITSSS7DLLAPI void SPRC_SendRELToMTP3_CCITT(ITS_OCTET rel_code,
                                           ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendRELToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                             ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUCICToMTP3_CCITT(ITS_USHORT cic,
                                            ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendBLOToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUBLToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendHWBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendHWGBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                            ISUP_OPC_DPC_INFO *config_info,
                                            ISUP_RANGE_AND_STATUS rs_ie);
ITSSS7DLLAPI void SPRC_SendBLAToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUBAToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendCGBToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                             ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendCGUToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                             ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendGRSToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                             ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendRSCToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendRLCToMTP3_CCITT(ITS_OCTET rel_code,
                                           ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUPTToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCFNToMTP3_CCITT(ITS_OCTET cause_ind,
                                           ITS_OCTET msgType,
                                           ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCQRToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info,
                                           ITS_ISUP_IE* rs_ie);

ITSSS7DLLAPI void SPRC_SendCOTToMTP3_CCITT(ITS_OCTET ind,
                                           ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);
 
ITSSS7DLLAPI void SPRC_SendCCRToMTP3_CCITT(ISUP_CIC_INFO *cic_rec,
                                           ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void SPRC_SendLocCongIndicToApp_CCITT(ITS_CTXT vcic, 
                                           ISUP_CONGESTION_ENTRY *congdata);

ITSSS7DLLAPI void
SPRC_Sendmtp3mgmtIndicToApp_CCITT(ITS_CTXT vcic,
                                 ISUP_MTP3MGMT_ENTRY *mgmtdata);


/* 
 * Timer abstraction functions 
 */
ITSSS7DLLAPI void __ISUP_StopTimer_CCITT(ISUP_CIC_INFO *cic_rec,
                                         ITS_OCTET timerId);
ITSSS7DLLAPI int  __ISUP_StartTimer_CCITT(ISUP_CIC_INFO *cic_rec,
                                          ITS_OCTET timerId,
                                          int timerValue);
#endif /* defined(CCITT) */



#if defined(ANSI)

/*
 * initialization and termination
 */
int ISUP_Init_ANSI(RESFILE_Manager *res, const char *section);
void ISUP_Term_ANSI(void);

/*
 * Message encode, decode and validation
 */
ITSSS7DLLAPI ITS_BOOLEAN __ISUP_ValidateMsgParsing_ANSI(ITS_OCTET msgType, 
                                            ISUP_MSG_DESC* mDesc, 
                                            ITS_OCTET* params, 
                                            ITS_USHORT len);
int 
__ISUP_ValidateParameters_ANSI(ITS_Class isup_variant,ITS_EVENT *event,
                                                              ITS_OCTET mType );
ITSSS7DLLAPI int ISUP_MTP3Decode_ANSI(ITS_OCTET *data, 
                                       ITS_USHORT len, 
                                       ITS_OCTET mType, 
                                       ITS_ISUP_IE *ies, 
                                       int *ieCount, 
                                       ITS_Class isup_variant);
ITSSS7DLLAPI int ISUP_MTP3Encode_ANSI(ITS_OCTET *data, 
                          ITS_USHORT *len, 
                          ITS_OCTET type,
                          ITS_ISUP_IE *ies, 
                          int ieCount, 
                          ITS_Class isup_variant);


/* 
 * ISUP Message and Timeout handling functions 
 */
ITSSS7DLLAPI int __ISUP_HandleTimeout_ANSI(ITS_EVENT *event);

ITSSS7DLLAPI int __ISUP_HandleMsg_ANSI(ITS_EVENT* event, ITS_OCTET source);

ITSSS7DLLAPI ITS_OCTET
__ISUP_ValidateParamCompatability_ANSI(ITS_Class V_Class,ITS_EVENT *event,
                                       ITS_OCTET mType);

/* 
 * SPRC functions
 */
ITSSS7DLLAPI int SPRC_SendIsupToMTP3_ANSI(ITS_EVENT* event, ITS_CTXT vcic);
ITSSS7DLLAPI void SPRC_SendIsupToApp_ANSI(ITS_CTXT vcic,
                                          ITS_EVENT* event);
ITSSS7DLLAPI void SPRC_SendTimeoutIndicToApp_ANSI(ITS_CTXT vcic,
                                          ISUP_TIMER_ENTRY* tdata);
ITSSS7DLLAPI void SPRC_SendErrorToApp_ANSI(ITS_OCTET msgType,
                                            ITS_UINT errId,
                                            ISUP_CIC_INFO *cic_rec);
ITSSS7DLLAPI void SPRC_SendRELToMTP3_ANSI(ITS_OCTET rel_code,
                                          ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUCICToMTP3_ANSI(ITS_USHORT cic,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendBLOToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUBLToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendHWBToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendBLAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendUBAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendCGBToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendCGUToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_ResendGRSToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendRSCToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendRLCToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCGUToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ISUP_RANGE_AND_STATUS rs_ie,
                                          ITS_OCTET sup_msg_type);
ITSSS7DLLAPI void SPRC_SendCGBToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ISUP_RANGE_AND_STATUS rs_ie,
                                          ITS_OCTET sup_msg_type);
ITSSS7DLLAPI void SPRC_SendIsupIndToApp_ANSI(ITS_UINT indId, 
                                          ITS_EVENT* event,
                                          ITS_OCTET src);
ITSSS7DLLAPI void SPRC_SendIndToApp_ANSI(ITS_UINT indId, 
                                          ISUP_CIC_INFO *cic_rec);
ITSSS7DLLAPI void SPRC_ResendRELToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCVTToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCQRToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ITS_ISUP_IE* rs_ie,
                                          ITS_USHORT cic);
ITSSS7DLLAPI void SPRC_SendGRAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ISUP_RANGE_AND_STATUS rs_ie);
ITSSS7DLLAPI void SPRC_SendCGBAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ISUP_RANGE_AND_STATUS rs_ie,
                                          ITS_OCTET sup_msg_type);
ITSSS7DLLAPI void SPRC_SendCGUAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info,
                                          ISUP_RANGE_AND_STATUS rs_ie,
                                          ITS_OCTET sup_msg_type);
ITSSS7DLLAPI void SPRC_SendCFNToMTP3_ANSI(ITS_OCTET cause_ind,
                                          ITS_OCTET msgType,
                                          ITS_USHORT cic,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCVRToMTP3_ANSI(ITS_USHORT cic,
                                          ISUP_OPC_DPC_INFO *config_info);
ITSSS7DLLAPI void SPRC_SendCRAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                                          ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI ITS_OCTET
SPRC_QueryCircuitStatus(const ISUP_CIC_INFO *cic_rec);

ITSSS7DLLAPI void
SPRC_SendCOTToMTP3_ANSI(ITS_OCTET ind, ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
SPRC_SendCCRToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
SPRC_SendLPAToMTP3_ANSI(ISUP_CIC_INFO *cic_rec,
                         ISUP_OPC_DPC_INFO *config_info);

ITSSS7DLLAPI void
SPRC_SendLocCongIndicToApp_ANSI(ITS_CTXT vcic, ISUP_CONGESTION_ENTRY *congdata);

ITSSS7DLLAPI void
SPRC_Sendmtp3mgmtIndicToApp_ANSI(ITS_CTXT vcic,
                                 ISUP_MTP3MGMT_ENTRY *mgmtdata);

/*
 * Timer abstraction functions
 */
ITSSS7DLLAPI void __ISUP_StopTimer_ANSI(ISUP_CIC_INFO *cic_rec,
                                        ITS_OCTET timerId);
ITSSS7DLLAPI int  __ISUP_StartTimer_ANSI(ISUP_CIC_INFO *cic_rec,
                                         ITS_OCTET timerId,
                                         ITS_UINT timerValue);


/*
 * MTP3 status handling functions 
 */
ITSSS7DLLAPI int
__ISUP_HandleMTP3MgmtMsg_ANSI(ITS_EVENT * evt);

#endif /* defined(ANSI) */

/*
 * ISUP Remote Congestion (ACC) Detection and transmission function
 */
ITSSS7DLLAPI void
__ISUP_CheckRmtCongestion(ITS_EVENT* event, ISUP_MSG_DESC *msg_desc,
                         ISUP_CIC_INFO *cic_rec, ISUP_OPC_DPC_INFO config_info);

/* 
 * ISUP stack internal return and error codes 
 */
#define ITS_ISUP_TIMER_DONE             -10000

/* 
 * Functions returning Message handlers and Timeout handlers
 * depending on message type and call state
 * NOTE: These should go into the variant specific headers.
 */
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgHandler_ITU93(ITS_OCTET msgType, 
                                                 ITS_ISUP_STATE state); 
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutHandler_ITU93(ITS_UINT timerID,
                                                         ITS_ISUP_STATE state);
/*
 * Message handling functions for all the call states
 */
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAcm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingAnm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_RcvdIncomingAnm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRlc_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitIncomingRes_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAcm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingAnm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_SentOutgoingAnm_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRlc_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRes_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRel_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingRsc_ITU93(ITS_OCTET msgType);
ITSSS7DLLAPI __ISUP_MsgHandlerProc __ISUP_GetMsgProc_WaitOutgoingGra_ITU93(ITS_OCTET msgType);
/*
 * Timeout handling functions for all the call states
 */
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_Idle_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingAcm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_RcvdIncomingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingRlc_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitIncomingRes_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingAcm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_SentOutgoingAnm_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRlc_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRes_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRel_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingRsc_ITU93(ITS_UINT timerId);
ITSSS7DLLAPI __ISUP_TimeoutHandlerProc __ISUP_GetTimeoutProc_WaitOutgoingGra_ITU93(ITS_UINT timerId);
/*
 * MTP3 status handling functions 
 */
ITSSS7DLLAPI int
__ISUP_HandleMTP3MgmtMsg_CCITT(ITS_EVENT * evt);

/* UPA message shall be handled in any state */
ITSSS7DLLAPI void
__ISUP_Received_UPA_ITU93(ITS_EVENT *msg, ISUP_CIC_INFO *cic_rec,
                    ISUP_OPC_DPC_INFO *config_info, ITS_OCTET src);

/* Timer T4 Handing function,this is nothing to do with CIC state */
ITSSS7DLLAPI void
__ISUP_Received_TimeoutT4_ITU93(ISUP_TIMER_ENTRY* t_entry,ISUP_CIC_INFO *cic_rec,
                           ISUP_OPC_DPC_INFO *config_info);


ITSSS7DLLAPI ISUP_CKGP_LIST *ISUP_AllocCkgpList(MTP3_HEADER opc_dpc_ni);

ITSSS7DLLAPI ISUP_CKGP_LIST *ISUP_FindCkgpList(MTP3_HEADER opc_dpc_ni,
                                              ITS_BOOLEAN isdsmlocal);

ITSSS7DLLAPI int ISUP_ReleaseCkgpList(ISUP_CKGP_LIST* ckgp_list,
                                              ITS_BOOLEAN isdsmlocal);

/*
 * For DSM Needs
 */

#define TIMERS_StartSharedTimer   TIMERS_StartTimer
#define TIMERS_StartSharedUTimer  TIMERS_StartUTimer
#define TIMERS_CancelSharedTimer TIMERS_CancelTimer


/*
 * Confusion Handling 
 */
#define ISUP_SEND_CFN_MSG 0x01
#define ISUP_DISCARD_MSG  0x02
#define ISUP_RELEASE_CALL 0x03
#define ISUP_PASS_ON_MSG  0x04
#define ISUP_DISCARD_PARAM  0x05

/*
 * For SEGmentation Purpose
 */
#define ISUP_SEGMENT_MSG  0x06

extern char *ISUP_Dest_Peg_Desc[];
extern char *ISUP_CIC_Peg_Desc[];
extern char *ISUP_Peg_Desc[];
extern char *ISUP_Msg_Pegs_Sent_Desc[];
extern char *ISUP_Msg_Pegs_Rcvd_Desc[];

/* Flags and values for Automatic Congestion Control */

extern ITS_BOOLEAN ANSI_ISUP_conglevel1Found;
extern ITS_BOOLEAN ANSI_ISUP_conglevel2Found;
extern ITS_UINT ANSI_ISUP_conglevel1;
extern ITS_UINT ANSI_ISUP_conglevel2;
extern ITS_UINT ANSI_ISUP_localcongtimer;

extern ITS_BOOLEAN CCITT_ISUP_conglevel1Found;
extern ITS_BOOLEAN CCITT_ISUP_conglevel2Found;
extern ITS_UINT CCITT_ISUP_conglevel1;
extern ITS_UINT CCITT_ISUP_conglevel2;
extern ITS_UINT CCITT_ISUP_localcongtimer;

#define AUTO_CONGESTION_OFF	0x00
#define AUTO_CONGESTION_LEVEL1	0x01
#define AUTO_CONGESTION_LEVEL2	0x02
#define AUTO_CONGESTION_LEVEL3	0x03


/*
 * The 2nd shot value of the local congestion
 * timer, a value which will be used
 * when local congestion is seen
 */
#define LOCAL_CONG_TIMER2      4

/* Local Congestion Control Timer Symbol */
#define ITS_ISUP_TIMER_T99     99

/* Repeat RSC Timer Symbol */
#define ITS_ISUP_TIMER_T98     98

/*
 * definition for ACC parser extension
 */

typedef struct
{
    ITS_UINT       congLevel1;
    ITS_UINT       congLevel2;
    ITS_UINT       congLevel3;
    ITS_UINT       localcongTimer;
    ITS_UINT       repeatrsctimerVal;
}
ISUP_CONG_CONTEXT;

/*
 * a helper for the parser extension for ACC
 */

typedef struct __XML_ParseData
{
    struct __XML_ParseData  *next;
    ISUP_CONG_CONTEXT        ctxt;
    char                    *sectionName;
}
XML_ParseData;


/*****************************************************************************
 *
 * The ISUP General Configuration.
 *
 *****************************************************************************/

typedef struct
{
    MGMT_AlarmLevel   alarmLevel;
    ITS_BOOLEAN         traceOn;     /* on(1), off(0) */
    ITS_CHAR       traceType[ITS_PATH_MAX];
    ITS_CHAR       traceOutput[ITS_PATH_MAX];

}
ISUPGeneralCfg;

/*The CIC information*/

/*defs for the control type of the circuit group: */
#define    ISUP_CFG_CKGP_CTRL_NONE  0x0
#define    ISUP_CFG_CKGP_CTRL_EVEN  0x1
#define    ISUP_CFG_CKGP_CTRL_ODD   0x2
#define    ISUP_CFG_CKGP_CTRL_ALL   0x3
#define    ISUP_CFG_CKGP_CTRL_DEF   0x4
#define    ISUP_CFG_CKGP_CTRL_INV   0x5

#if defined(ANSI)
#define ISUP_MAX_CFG_CICS_PER_CKGP 24
#else
#define ISUP_MAX_CFG_CICS_PER_CKGP 32
#endif

/*
 * General Configuration related functions
 */
ITSSS7DLLAPI ISUPGeneralCfg* ISUP_GetGeneralCfg_ANSI();
ITSSS7DLLAPI ISUPGeneralCfg* ISUP_GetGeneralCfg_CCITT();

ITSSS7DLLAPI int ISUP_SetGeneralCfg_ANSI(ISUPGeneralCfg *data);
ITSSS7DLLAPI int ISUP_SetGeneralCfg_CCITT(ISUPGeneralCfg *data);


/* Add ISUP Variant Type*/
ITSSS7DLLAPI int ISUP_AddVariantFeature_ANSI(const char *varType);

ITSSS7DLLAPI int ISUP_AddVariantFeature_CCITT(const char *varType);

/* Get configuration and status information of the destination for the
 * given OPC DPC
 */
ITSSS7DLLAPI int ISUP_GetDestCfgInfo_ANSI(ISUP_CFG_KEY cfg,
                                          ISUP_CFG_DEST_INFO* info);
ITSSS7DLLAPI int ISUP_GetDestCfgInfo_CCITT(ISUP_CFG_KEY cfg,
                                           ISUP_CFG_DEST_INFO* info);

ITSSS7DLLAPI int ISUP_AddDestCfgInfo_ANSI(ISUP_CFG_KEY cfg,
                                          char *variantType, char *xchangeType);

ITSSS7DLLAPI int ISUP_AddDestCfgInfo_CCITT(ISUP_CFG_KEY cfg,
                                          char *variantType, char *xchangeType);

/*Get configuration and status information of all the destinations*/

ITSSS7DLLAPI int ISUP_GetAllDestCfgInfo_ANSI(ISUP_CFG_DEST_INFO **info,
                                             int* noEnt);

ITSSS7DLLAPI int ISUP_GetAllDestCfgInfo_CCITT(ISUP_CFG_DEST_INFO **info,
                                              int* noEnt);

/*
 * Get timer setting for a given OPC-DPC pair and the timer ID
 */

ITSSS7DLLAPI int ISUP_GetTimerCfgInfo_ANSI (ISUP_CFG_KEY cfg, int tId,
                                            ISUP_CFG_TMR_INFO* info);
ITSSS7DLLAPI int ISUP_GetTimerCfgInfo_CCITT (ISUP_CFG_KEY cfg, int tId,
                                             ISUP_CFG_TMR_INFO* info);

/*
 * Get all the Timer configuration for the given destination
 */
ITSSS7DLLAPI int ISUP_GetAllTimerCfgInfo_ANSI(ISUP_CFG_KEY cfg,
                                              ISUP_CFG_TMR_INFO* tEnt);
ITSSS7DLLAPI int ISUP_GetAllTimerCfgInfo_CCITT(ISUP_CFG_KEY cfg,
                                            ISUP_CFG_TMR_INFO* info);

/*
 * Set the timer value for a given timer
 */
ITSSS7DLLAPI int ISUP_SetTimerCfgInfo_ANSI(ISUP_CFG_KEY cfg, int tId,
                                           int tVal,
                                           ISUP_CFG_TMR_HNDL handlBy);
ITSSS7DLLAPI int ISUP_SetTimerCfgInfo_CCITT(ISUP_CFG_KEY cfg, int tId,
                                            int tVal,
                                            ISUP_CFG_TMR_HNDL handlBy);

/*
 * Add the CICs to the current configuration for the given destination
 */

/*Get all circuit codes configured for the given destination*/
ITSSS7DLLAPI int ISUP_GetAllCicsCfg_ANSI(ISUP_CFG_KEY cfg,
                                         ISUP_CFG_CKGP_INFO** ckgps,
                                         int* noCkgps);

/*Add the CICs to the current configuration for the given destination*/

ITSSS7DLLAPI int ISUP_AddCicsCfg_ANSI (ISUP_CFG_KEY key,
                                       ITS_USHORT scic,
                                       ITS_USHORT count,
                                       ITS_OCTET cicRule);
ITSSS7DLLAPI int ISUP_AddCicsCfg_CCITT (ISUP_CFG_KEY key,
                                        ITS_USHORT scic,
                                        ITS_USHORT count,
                                        ITS_OCTET cicRule);

/*
 * Delete the CICs from the current configuration for the given destination
 */
ITSSS7DLLAPI int ISUP_DelCicsCfg_ANSI (ISUP_CFG_KEY key,
                                       ITS_USHORT cic,
                                       ITS_USHORT count);
ITSSS7DLLAPI int ISUP_DelCicsCfg_CCITT (ISUP_CFG_KEY key,
                                        ITS_USHORT cic,
                                        ITS_USHORT count);

/*
 * Get the CIC status for a given CIC
 */
ITSSS7DLLAPI int ISUP_GetCicStateInfo_ANSI (ISUP_CFG_KEY key,
                                            ITS_USHORT cic,
                                            ITS_OCTET* cicState);

ITSSS7DLLAPI int ISUP_SetCicStateInfo_ANSI(ISUP_CFG_KEY key,
                                            ITS_USHORT cic,
                                            ITS_OCTET state);
ITSSS7DLLAPI int ISUP_GetCicStateInfo_CCITT (ISUP_CFG_KEY key,
                                             ITS_USHORT cic,
                                             ITS_OCTET* cicState);
ITSSS7DLLAPI int ISUP_SetCicStateInfo_CCITT(ISUP_CFG_KEY key,
                                            ITS_USHORT cic,
                                            ITS_OCTET state);

/*
 * Get all circuit codes configured for the given destination
 */
ITSSS7DLLAPI int ISUP_GetAllCicsCfg_ANSI(ISUP_CFG_KEY cfg,
                                         ISUP_CFG_CKGP_INFO** ckgps,
                                         int* noCkgps);

ITSSS7DLLAPI int ISUP_GetCicPegs_ANSI(ISUP_CFG_KEY cfg, ITS_USHORT cic,
                                      ISUP_CFG_PEGS *cicPeg);

ITSSS7DLLAPI int ISUP_ClearCicPegs_ANSI(ISUP_CFG_KEY cfg, ITS_USHORT cic,
                                        ITS_INT pegType);

ITSSS7DLLAPI int ISUP_ClearAllCicPegs_ANSI(ISUP_CFG_KEY cfg, ITS_USHORT cic);

ITSSS7DLLAPI int ISUP_GetGeneralPegs_ANSI(ISUP_CFG_PEGS *genPegs, int noEnt);

ITSSS7DLLAPI int ISUP_ClearGenPeg_ANSI(ITS_UINT pegType);

ITSSS7DLLAPI int ISUP_ClearAllGenPeg_ANSI();

ITSSS7DLLAPI int ISUP_GetAllCicsCfg_CCITT(ISUP_CFG_KEY cfg,
                                          ISUP_CFG_CKGP_INFO** ckgps,
                                          int* noCkgps);

ITSSS7DLLAPI int ISUP_GetCicPegs_CCITT(ISUP_CFG_KEY cfg, ITS_USHORT cic,
                                              ISUP_CFG_PEGS *cicPeg);

/* function for msg-based pegs */
ITSSS7DLLAPI int ISUP_ClearAllMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg);
ITSSS7DLLAPI int ISUP_ClearAllMsgSentPegs_ANSI(ISUP_CFG_KEY cfg);

ITSSS7DLLAPI int ISUP_ClearMsgRcvdPeg_ANSI(ISUP_CFG_KEY cfg, 
                                         ITS_OCTET pegId);
ITSSS7DLLAPI int ISUP_ClearMsgSentPeg_ANSI(ISUP_CFG_KEY cfg, 
                                         ITS_OCTET pegId);
ITSSS7DLLAPI int ISUP_GetMsgSentPegs_ANSI(ISUP_CFG_KEY cfg, 
                                         ISUP_CFG_PEGS *SentPegs,
                                         int *noEnt);
ITSSS7DLLAPI int ISUP_GetMsgRcvdPegs_ANSI(ISUP_CFG_KEY cfg, 
                                         ISUP_CFG_PEGS *RcvdPegs,
                                         int *noEnt);

ITSSS7DLLAPI int ISUP_ClearAllMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg);
ITSSS7DLLAPI int ISUP_ClearAllMsgSentPegs_CCITT(ISUP_CFG_KEY cfg);
ITSSS7DLLAPI int ISUP_ClearMsgRcvdPeg_CCITT(ISUP_CFG_KEY cfg,
                                         ITS_OCTET pegId);
ITSSS7DLLAPI int ISUP_ClearMsgSentPeg_CCITT(ISUP_CFG_KEY cfg,
                                         ITS_OCTET pegId);
ITSSS7DLLAPI int ISUP_GetMsgRcvdPegs_CCITT(ISUP_CFG_KEY cfg,
                                         ISUP_CFG_PEGS *SentPegs,
                                         int *noEnt);
ITSSS7DLLAPI int ISUP_GetMsgSentPegs_CCITT(ISUP_CFG_KEY cfg,
                                         ISUP_CFG_PEGS *RcvdPegs,
                                         int *noEnt);


/* Get the Destination specific pegs Desc */

ITSSS7DLLAPI int ISUP_GetDestPegs_CCITT(ISUP_CFG_KEY cfg, 
                                      ISUP_CFG_PEGS *destPegs );


/* Get the Destination specific pegs Desc */

ITSSS7DLLAPI int ISUP_GetDestPegs_ANSI(ISUP_CFG_KEY cfg, 
                                      ISUP_CFG_PEGS *destPegs );


/*
 * Set and Get the Congestion Levels Threshold in ISUP protocol
 */
ITSSS7DLLAPI int ISUP_SetCong_CCITT(ITS_UINT congLev, ITS_UINT congVal);
ITSSS7DLLAPI int ISUP_SetCong_ANSI(ITS_UINT congLev, ITS_UINT congVal);


#ifdef __cplusplus
}
#endif

#endif /* ISUP_INTERN_H */
