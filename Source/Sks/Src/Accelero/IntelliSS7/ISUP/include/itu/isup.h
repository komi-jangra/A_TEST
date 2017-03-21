/****************************************************************************
 *                                                                          *
 *     Copyright 1997 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: isup.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
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
 * LOG: Revision 9.1  2005/03/23 12:52:01  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.6  2005/03/21 13:49:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.7.2.3  2003/12/05 07:07:09  ssingh
 * LOG: Bug #683 fix. Message based pegs propagated to Release 6.3
 * LOG:
 * LOG: Revision 7.7.2.2  2003/07/30 04:33:25  sjaddu
 * LOG: LOP is moved here from 97 dir.
 * LOG:
 * LOG: Revision 7.7.2.1  2003/05/07 09:08:46  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.4  2003/04/04 04:58:01  ssingh
 * LOG: Removed ISUP_ReceiveConformation.
 * LOG:
 * LOG: Revision 8.3  2003/04/03 14:15:29  sjaddu
 * LOG: Added New Hash define for No cics in group.
 * LOG:
 * LOG: Revision 8.2  2003/03/26 10:21:20  ssingh
 * LOG: Changes done in files:
 * LOG: isup_cmn.h      : Indications added for COT reset/release.
 * LOG: isup_sn.h       : UnReserveCIC short name added
 * LOG: ansi/isup.h     : UnReserveCIC declared.
 * LOG: itu/isup.       : UnReserveCIC declared.
 * LOG: isup_variants.h : CIC_INFO is modified for ANSI.
 * LOG:
 * LOG: Revision 8.1  2003/02/13 17:43:24  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.7  2003/02/05 17:04:45  sjaddu
 * LOG: ReserveCic changes of itu.
 * LOG:
 * LOG: Revision 7.6  2003/01/22 09:47:49  akumar
 * LOG: Modified for SGM procedure
 * LOG:
 * LOG: Revision 7.5  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.4  2003/01/13 23:51:25  vnitin
 * LOG: Add Typecasting changes for Tandem Port
 * LOG:
 * LOG: Revision 7.3  2002/11/13 10:07:48  ssingh
 * LOG: corrected the previous wrong commit.
 * LOG:
 * LOG: Revision 7.2  2002/11/11 11:31:30  akumar
 * LOG: Modified for Automatic Congestion Control procedures
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.7  2002/08/16 22:09:03  mmiers
 * LOG: Add the china variant
 * LOG:
 * LOG: Revision 6.6  2002/08/01 15:49:05  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.5.2.3  2002/07/30 14:44:58  ssingh
 * LOG: Included ANSI95 related parameters.
 * LOG:
 * LOG: Revision 6.5.2.2  2002/07/25 21:32:11  ssingh
 * LOG: Added new functions to handle Indications and Conformations.
 * LOG:
 * LOG: Revision 6.5.2.1  2002/07/02 20:12:19  hbalimid
 * LOG: ITU93 specific params moved from isup_cmn.h
 * LOG:
 * LOG: Revision 6.5  2002/06/22 03:09:38  hbalimid
 * LOG: corrected ccss parameter definition.
 * LOG:
 * LOG: Revision 6.4  2002/06/18 20:34:52  hbalimid
 * LOG: Added ITU97 specific parameter definitions.
 * LOG:
 * LOG: Revision 6.3  2002/06/10 14:49:20  sjaddu
 * LOG: Removed CIC states here and added in the cmn file.
 * LOG:
 * LOG: Revision 6.2  2002/05/20 15:29:57  sjaddu
 * LOG: Merge from PR6.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.12.2.3  2002/05/15 16:32:25  hbalimid
 * LOG: modified conf indicator for extension octet
 * LOG: Added more parameters for ITU97
 * LOG:
 * LOG: Revision 5.12.2.2  2002/05/14 18:09:59  hbalimid
 * LOG: added ITU97 specific messages and parameters
 * LOG:
 * LOG: Revision 5.12.2.1  2002/04/04 21:35:46  ssanyal
 * LOG: changes for ANSI 95 implementation: 
 * LOG: transfering common params. to central place (isup_cmn.h).
 * LOG:
 * LOG: Revision 5.12  2002/02/26 23:54:59  ssharma
 * LOG: Add timer and error indications to stack.
 * LOG:
 * LOG: Revision 5.11  2002/02/13 21:21:25  mmiers
 * LOG: Finish up ISUP integration
 * LOG:
 * LOG: Revision 5.10  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 5.9  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.8  2002/02/01 21:17:03  mmiers
 * LOG: Porting.
 * LOG:
 * LOG: Revision 5.7  2002/02/01 21:00:09  mmiers
 * LOG: Use explicit types.
 * LOG:
 * LOG: Revision 5.6  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.5  2001/12/15 01:18:52  mmiers
 * LOG: VFrame is in.
 * LOG:
 * LOG: Revision 5.4  2001/12/13 23:01:05  mmiers
 * LOG: Common vendor framework start.
 * LOG:
 * LOG: Revision 5.3  2001/11/09 20:21:34  mmiers
 * LOG: Don't force the stack to be part of the engine.  Make it a DLL
 * LOG: instead.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.4  2001/06/20 22:01:25  mmiers
 * LOG: Get DSM building as a DLL.  Correct some namespace bugs.
 * LOG:
 * LOG: Revision 4.3  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 * LOG: Revision 4.2  2001/06/20 00:39:53  mmiers
 * LOG: Split the signatures out.  Tomorrow we split out the #defines.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:05  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.6  2001/03/14 22:06:44  mmiers
 * LOG: Finalizing the engine.  Just need to do the thread pools.
 * LOG:
 * LOG: Revision 3.5  2001/01/18 22:31:46  hxing
 * LOG: problem with extern "C"
 * LOG:
 * LOG: Revision 3.4  2000/12/21 22:16:00  mmiers
 * LOG: Add prefix
 * LOG:
 * LOG: Revision 3.3  2000/12/21 22:12:52  mmiers
 * LOG: Add prefix
 * LOG:
 * LOG: Revision 3.2  2000/12/11 22:40:25  hxing
 * LOG: Add ComputeMSize  to the header file
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:24  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.14  2000/07/25 19:29:45  hxing
 * LOG: Add prototypes for Encode/Decode back in.
 * LOG:
 * LOG: Revision 2.13  2000/07/21 19:17:44  hxing
 * LOG: Add functions ISUP_SendCVRRequest and ISUP_ReceiveCVRIndication (ANSI only)
 * LOG: for message CVR
 * LOG:
 * LOG: Revision 2.12  2000/07/14 16:08:01  labuser
 * LOG: cbascon: Removed newnet specific send function for RSC response --RLC
 * LOG: with ISUP_RESET primitive.
 * LOG:
 * LOG: Revision 2.11  2000/06/28 23:40:19  mmiers
 * LOG:
 * LOG:
 * LOG: Move a few things around.
 * LOG:
 * LOG: Revision 2.10  2000/06/28 19:34:43  hxing
 * LOG: Changed field transaction_id from type ITS_UINT to ITS_OCTET[4] for alignment reason
 * LOG:
 * LOG: Revision 2.9  2000/06/16 13:47:50  labuser
 * LOG: Moved definitions outside of #ifdef INCLUDE_CODEC to build ISUP
 * LOG:
 * LOG: Revision 2.8  2000/05/16 22:47:43  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.7  2000/02/03 17:08:06  fhasle
 * LOG:
 * LOG: updated to include variant and CODEC.
 * LOG:
 * LOG: Revision 2.6  2000/01/11 18:29:52  fhasle
 * LOG:
 * LOG: fixed service activation tag.
 * LOG:
 * LOG: Revision 2.5  2000/01/05 19:09:00  labuser
 * LOG: cbascon: officeZ as defined in ANSI spec
 * LOG:
 * LOG: Revision 2.4  1999/12/20 22:07:01  cbascon
 * LOG: "data" is not a member variable in MLPPPrecedence(CCITT).
 * LOG:
 * LOG: Revision 2.3  1999/12/20 21:32:47  cbascon
 * LOG: GenericeReference(CCITT) parameter structure should allow for multiple
 * LOG: reference entries.
 * LOG:
 * LOG: Revision 2.2  1999/12/16 02:40:28  mmiers
 * LOG:
 * LOG: gcc/g++ -Wall is very unforgiving.
 * LOG:
 * LOG: Revision 2.1  1999/12/10 22:30:41  fhasle
 * LOG:
 * LOG: Fixed typos for CQR msg.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:25  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.28  1999/11/22 18:37:23  cbascon
 * LOG: Had wrong tag value for UCIC.
 * LOG:
 * LOG: Revision 1.27  1999/11/19 22:28:07  cbascon
 * LOG: Had wrong tag for Service Activation parameter.
 * LOG:
 * LOG: Revision 1.26  1999/11/14 23:11:39  cbascon
 * LOG: Moved tags for HopCounter, UserTeleserviceInfoPrime,
 * LOG: UserTeleserviceInfo to CCITT tag defines.
 * LOG:
 * LOG: Revision 1.25  1999/11/10 19:57:18  fhasle
 * LOG:
 * LOG: Almost done fully ANSI and ITU compatible.
 * LOG:
 * LOG: Revision 1.24  1999/11/10 18:06:41  mmiers
 * LOG:
 * LOG:
 * LOG: Update after GDI.
 * LOG:
 * LOG: Revision 1.23  1999/11/03 00:11:44  labuser
 * LOG:
 * LOG: fhasle: fix Originating line info.
 * LOG:
 * LOG: Revision 1.22  1999/10/28 17:35:36  fhasle
 * LOG:
 * LOG: Updated Call Progress, and params, (ANSI). Added Exit, and params, (ANSI)
 * LOG:
 * LOG: Revision 1.21  1999/10/27 15:45:22  mmiers
 * LOG:
 * LOG:
 * LOG: Get the headers in here.
 * LOG:
 * LOG: Revision 1.20  1999/10/26 22:44:54  fhasle
 * LOG:
 * LOG: updated file to support ANSI ISUP (generic, not everything yet supported)
 * LOG:
 * LOG: Revision 1.19  1999/10/07 17:52:35  mmiers
 * LOG:
 * LOG:
 * LOG: Add protos (ISUP) fix bug (transports).
 * LOG:
 * LOG: Revision 1.18  1999/10/05 20:35:07  rsonak
 * LOG:
 * LOG: Moved protocol defines here from its.h
 * LOG:
 * LOG: Revision 1.17  1999/05/25 22:00:02  mmiers
 * LOG:
 * LOG:
 * LOG: First pass at ISUP.
 * LOG:
 * LOG: Revision 1.16  1999/05/25 02:10:43  mmiers
 * LOG:
 * LOG:
 * LOG: Get the descriptors in place.  Sort out ANSI vs. CCITT.
 * LOG:
 * LOG: Revision 1.15  1999/05/25 01:43:32  mmiers
 * LOG:
 * LOG:
 * LOG: More work on ISUP.
 * LOG:
 * LOG: Revision 1.14  1999/05/25 01:06:45  mmiers
 * LOG:
 * LOG:
 * LOG: Start cleaning up ISUP.
 * LOG:
 * LOG: Revision 1.13  1999/03/17 18:41:55  mmiers
 * LOG:
 * LOG:
 * LOG: Dual protocol updates.
 * LOG:
 * LOG: Revision 1.12  1999/03/17 15:12:58  mmiers
 * LOG:
 * LOG:
 * LOG: Oops, forgot implementation sigs.
 * LOG:
 * LOG: Revision 1.11  1999/03/17 15:10:05  mmiers
 * LOG:
 * LOG:
 * LOG: More dual protocol work.
 * LOG:
 * LOG: Revision 1.10  1998/11/18 18:39:48  mmiers
 * LOG: Start thinking about ANSI ISUP.
 * LOG:
 * LOG: Revision 1.9  1998/11/11 00:44:44  mmiers
 * LOG: Enhance routing a bit to simplify the logic and increase speed.
 * LOG: Work on defining CPC/CSSN information for SCCP.  Almost done.
 * LOG:
 * LOG: Revision 1.8  1998/09/25 20:35:24  mmiers
 * LOG: Update for MTP3
 * LOG:
 * LOG: Revision 1.7  1998/06/17 19:57:00  mmiers
 * LOG: Retain backwards compatibility.
 * LOG:
 * LOG: Revision 1.6  1998/05/04 22:57:35  mmiers
 * LOG: Much work on naming consistency.  This will force a TCAP change.
 * LOG:
 * LOG: Revision 1.5  1998/02/26 22:26:14  mmiers
 * LOG: Make sure ISUP stays up to date.  Add project and workspace for VC++.
 * LOG:
 * LOG: Revision 1.4  1998/02/25 21:41:43  mmiers
 * LOG: Avoid name clashes with other subsystems having IEs.
 * LOG:
 * LOG: Revision 1.3  1998/02/10 22:32:08  mmiers
 * LOG: Separate out the PART specific stuff from its.h.  Everything is now in
 * LOG: its appropriate place.  The TCAP headers moved from common to TCAP.  The
 * LOG: state machine code has been added to the tree.
 * LOG:
 * LOG: Revision 1.2  1998/01/24 20:57:14  mmiers
 * LOG: Add in California code.  Implementation of ITU ISUP.
 * LOG:
 * LOG: Revision 1.1  1998/01/24 20:47:35  mmiers
 * LOG: add new file.  Merge in advances to API from later California days.  Delete
 * LOG: old api header.
 * LOG:
 *
 ****************************************************************************/

#ifndef _ITS_ISUP_CCITT_H_
#define _ITS_ISUP_CCITT_H_

#include <its.h>
#include <its_callback.h>

#ident "$Id: isup.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

#if defined(PRC)
#include <china/mtp3.h>
#include <china/tcap.h>
#else
#include <itu/mtp3.h>
#include <itu/tcap.h>
#endif

#include <isup_cmn.h>
#include <isup_sn.h>
#include <itu/isup_macros.h>


#ifdef __cplusplus
extern "C"
{
#endif

#define ISUP_ITU_MAX_CICS_IN_GP   32
                                                       
/*
 ****************************************************************************
 * Message Types Codes 
 *
 * ITU Ref: Q.763 (03/93). page 3.
 * Sec 1.3; Table 4/Q.763.
 *
 * The Message Type code consists of a one octet field and is mandatory
 * for all messages. The message type code uniquely defines the function
 * and the format of each ISDN User Part message.
 * All acronyms (last 3/4 letters) are taken from Table 2/Q.762 (03/93), pg 14.
 * NOTE: All message types are not supported by the board manufacturer.
 ****************************************************************************/ 
#define ISUP_MSG_CON    0x07    /* Connect */
#define ISUP_MSG_IDR    0x36    /* Identification Request */
#define ISUP_MSG_IRS    0x37    /* Identification Response */
#define ISUP_MSG_FAA    0x20    /* Facility Accepted */
#define ISUP_MSG_FAC    0x33    /* Facility */
#define ISUP_MSG_FRJ    0x21    /* Facility Reject */
#define ISUP_MSG_FAR    0x1F    /* Facility Request */
#define ISUP_MSG_NRM    0x32    /* Network Ressource Management */
#define ISUP_MSG_OLM    0x30    /* Overload */
#define ISUP_MSG_SAM    0x02    /* Subsequent Address */
#define ISUP_MSG_SGM    0x38    /* Segmentation */
#define ISUP_MSG_UPA    0x35    /* User Part Available */
#define ISUP_MSG_UPT    0x34    /* User Part Test */
#define ISUP_MSG_USR    0x2D    /* User-to-User Message */


/*
 ****************************************************************************
 * Message Types Codes - Specific to ITU97
 *
 * ITU Ref: Q.763 (09/97). page 10.
 * Sec 1.3; Table 4/Q.763.
 *
 * The Message Type code consists of a one octet field and is mandatory
 * for all messages. The message type code uniquely defines the function
 * and the format of each ISDN User Part message.
 * All acronyms (last 3/4 letters) are taken from Table 1/Q.762 (09/97), pg 3.
 * NOTE: All message types are not supported by the board manufacturer.
 ****************************************************************************/ 
#define ISUP_MSG_LOP    0x40    /* Loop Prevention */

/* ITU Specific Pegs defined here */

#define PEG_ISUP_IDR_SENT_TO_REMOTE    31
#define PEG_ISUP_IRS_SENT_TO_REMOTE    32
#define PEG_ISUP_FAA_SENT_TO_REMOTE    33
#define PEG_ISUP_CON_SENT_TO_REMOTE    34
#define PEG_ISUP_FRJ_SENT_TO_REMOTE    35
#define PEG_ISUP_FAC_SENT_TO_REMOTE    36
#define PEG_ISUP_FAR_SENT_TO_REMOTE    37
#define PEG_ISUP_NRM_SENT_TO_REMOTE    38
#define PEG_ISUP_OLM_SENT_TO_REMOTE    39
#define PEG_ISUP_SAM_SENT_TO_REMOTE    40
#define PEG_ISUP_SGM_SENT_TO_REMOTE    41
#define PEG_ISUP_UPA_SENT_TO_REMOTE    42
#define PEG_ISUP_UPT_SENT_TO_REMOTE    43
#define PEG_ISUP_USR_SENT_TO_REMOTE    44

#define PEG_ISUP_REMOTE_IDR_RCVD       31
#define PEG_ISUP_REMOTE_IRS_RCVD       32
#define PEG_ISUP_REMOTE_FAA_RCVD       33
#define PEG_ISUP_REMOTE_CON_RCVD       34
#define PEG_ISUP_REMOTE_FRJ_RCVD       35
#define PEG_ISUP_REMOTE_FAC_RCVD       36
#define PEG_ISUP_REMOTE_FAR_RCVD       37
#define PEG_ISUP_REMOTE_NRM_RCVD       38
#define PEG_ISUP_REMOTE_OLM_RCVD       39
#define PEG_ISUP_REMOTE_SAM_RCVD       40
#define PEG_ISUP_REMOTE_SGM_RCVD       41
#define PEG_ISUP_REMOTE_UPA_RCVD       42
#define PEG_ISUP_REMOTE_UPT_RCVD       43
#define PEG_ISUP_REMOTE_USR_RCVD       44

/* Itu-97 */
#define PEG_ISUP_REMOTE_LOP_RCVD       45
#define PEG_ISUP_LOP_SENT_TO_REMOTE    45

/*
 ****************************************************************************
 * Parameter Names and Identifiers (ITU specific parameter Names).
 *
 * ITU Ref: Q.763 (03/93) page 8.
 * Sec: 3.1 Table 5/Q.763.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/
#define ISUP_PRM_ACCESS_DELIVERY_INFO           0x2e
#define ISUP_PRM_CALL_DIVERSION_INFO            0x36
#define ISUP_PRM_CALL_HISTORY_INFO              0x2d
#define ISUP_PRM_CONNECTED_NUM                  0x21
#define ISUP_PRM_CLOSED_USR_GRP_INTRLCK_CODE    0x1a
#define ISUP_PRM_ECHO_CTRL_INFO                 0x37
#define ISUP_PRM_FACILITY_INDICATOR             0x18
#define ISUP_PRM_FREEPHONE_INDICATORS           0x41
#define ISUP_PRM_GENERIC_NOTIFICATION           0x2c
#define ISUP_PRM_GENERIC_NUM                    0xC0
#define ISUP_PRM_GENERIC_REF                    0x42
#define ISUP_PRM_LOCATION_NUM                   0x3f
#define ISUP_PRM_MCID_REQ_INDICATOR             0x3b
#define ISUP_PRM_MCID_RESP_INDICATOR            0x3c
#define ISUP_PRM_MLPP_PRECEDENCE                0x3a
#define ISUP_PRM_MSG_COMPAT_INFO                0x38
#define ISUP_PRM_NTWK_SPECIFIC_FACILITIES       0x2f
#define ISUP_PRM_OPT_FWD_CALL_INDICATORS        0x08
#define ISUP_PRM_ORIG_ISC_PC                    0x2b
#define ISUP_PRM_PARAM_COMPAT_INFO              0x39
#define ISUP_PRM_PROP_DELAY_COUNTER             0x31
#define ISUP_PRM_REDIRECTION_NUM                0x0c
#define ISUP_PRM_REDIRECTION_NUM_RESTRICT       0x40
#define ISUP_PRM_REMOTE_OPS                     0x32
#define ISUP_PRM_SIGNALLING_POINT_CODE          0x1e
#define ISUP_PRM_SUBSEQUENT_NUM                 0x05
#define ISUP_PRM_TX_MEDIUM_REQMNT               0x02
#define ISUP_PRM_TX_MEDIUM_REQMNT_PRIME         0x3e
#define ISUP_PRM_TX_MEDIUM_USED                 0x35
#define ISUP_PRM_USER_SERVICE_INFO_PRIME        0x30
#define ISUP_PRM_USER_TELESERVICE_INFO          0x34
#define ISUP_PRM_USER_TO_USER_INDICATORS        0x2a
#define ISUP_PRM_USER_TO_USER_INFO              0x20



/*
 ****************************************************************************
 * Parameter Names and Identifiers (ITU specific parameter Names). - ITU97
 *
 * ITU Ref: Q.763 (09/97) page 15.
 * Sec: 3.1 Table 5/Q.763.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/
#define ISUP_PRM_CIRCUIT_ASSIGNMENT_MAP       0x25
#define ISUP_PRM_CALL_TRANSFER_REFERENCE      0x43
#define ISUP_PRM_LOOP_PREVENTION_INDICATORS   0x44
#define ISUP_PRM_CALL_TRANSFER_NUMBER         0x45
#define ISUP_PRM_CCSS                         0x4b
#define ISUP_PRM_FORWARD_GVNS                 0x4c
#define ISUP_PRM_BACKWARD_GVNS                0x4d
#define ISUP_PRM_NETWORK_MANAGEMENT_CONTROLS  0x5b
#define ISUP_PRM_CORRELATION_ID               0x65
#define ISUP_PRM_SCF_ID                       0x66
#define ISUP_PRM_CALL_DIV_TREAT_INDICATORS    0x6e
#define ISUP_PRM_CALLED_IN_NUMBER             0x6f
#define ISUP_PRM_CALL_OFF_TREAT_INDICATORS    0x70
#define ISUP_PRM_CHARGED_PARTY_IDENTIFICATION 0x71
#define ISUP_PRM_CONF_TREAT_INDICATORS        0x72
#define ISUP_PRM_DISPLAY_INFORMATION          0x73
#define ISUP_PRM_UID_ACTION_INDICATORS        0x74
#define ISUP_PRM_UID_CAPABILITY_INDICATORS    0x75
#define ISUP_PRM_COLLECT_CALL_REQUEST         0x79
#define ISUP_PRM_HOP_COUNTER                  0x3d


/* 
 ****************************************************************************
 * Backward Call Indicators.
 *
 * ITU Ref: sec 3.5. page 10. Figure 7/Q.763.
 ****************************************************************************/ 
/*
 * Bit J: End-to-end Information Indicator 
 */
#define BKWD_NO_ETE_INFO        0x00
#define BKWD_ETE_INFO           0x01 


/*
 ****************************************************************************
 * Called Party Number.
 *
 * ITU Ref: sec 3.9, page 13 (Figure 10/Q.763).
 ****************************************************************************/ 
/*
 * The lower 7 bits of the octet 'addr_ind' represent 
 * Nature of Address Indicator, as defined below
 */
#define CDPN_UNKNOWN_CCITT       0x02

/*
 * The MSB of the octet 'num_plan' represents the Internal Network Number
 * Indicator (INN ind) (CCITT only, Spare for ANSI).
 */
#define CDPN_ROUTING_INN_ALLOWED     0x00
#define CDPN_ROUTING_INN_NOT_ALLOWED 0x01

/*
 * Bits 7->5 of the octet 'num_plan' represent the  Numbering Plan Indicator,
 * Bits 4->1 are reserved (ANSI) or spare (CCITT).
 */                                        
#define CDPN_RESERVED_NATL1          0x05
#define CDPN_RESERVED_NATL2          0x06


/*
 ****************************************************************************
 * Calling Party Number.
 *
 * ITU Ref: sec 3.10, page 14 (Figure 11/Q.763).
 ****************************************************************************/ 
/* 
 * Nature Of Address Indicator
 */
#define CGPN_UNKNOWN                 0x02

/*
 * The 'subfields4' octet comprises 4 parts. 
 * The MSB represents the Calling Party Number Incomplete Indicator (NI)
 */
#define  CGPN_COMPLETE                0x00
#define  CGPN_INCOMPLETE              0x01

/*
 * The 2 bits adjescent to the Numbering Plan Indicator represent
 * the Address Presentation Restricted Indicator.
 */                                    
#define CGPN_ADDR_NOT_AVAILABLE      0x02


/*
 ****************************************************************************
 * Cause Indicator.
 *
 * ITU Ref: sec 3.12, page 17. Figure 13/Q.763.
 * The codes in the subfields of the cause indicators parameter
 * fields are defined in the Q.6XX-Series Recommendations.
 ***************************************************************************/
/*
 * 'Coding Standard' subfield (bit 7 & 6) within subfields4 octet.
 */                          
#define CI_CS_LOCALE    3

/*
 * 'Location' subfield (bit 1 -> 4) within subfields4 octet.
 */                          
#define CI_LOC_BEYOND_INTWK         0x0A

/*
 * cause values, as per Q.850, Table 1
 */
#define CI_CAUSE_SUBSCRIBER_ABSENT                  20
#define CI_CAUSE_NON_SELECTED_USER_CLEARING     26
#define CI_CAUSE_PERMANENT_FRAME_MODE_OOS       39
#define CI_CAUSE_PERMANENT_FRAME_MODE_OK        40
#define CI_CAUSE_QOS_UNAVAIL                        49
#define CI_CAUSE_INCONSISTENT                   62
#define CI_CAUSE_CHANNEL_TYPE_NOT_IMPL          66
#define CI_CAUSE_CHANNEL_DOES_NOT_EXIST         82
#define CI_CAUSE_CALL_SUSPENDED                 83
#define CI_CAUSE_CALL_IDENTITY_IN_USE           84
#define CI_CAUSE_NO_CALL_SUSPENDED              85
#define CI_CAUSE_REQUESTED_ID_CLEARED           86
#define CI_CAUSE_INVALID_TRANSIT_NET            91
#define CI_CAUSE_MANDATORY_IE_MISSING           96
#define CI_CAUSE_MSG_TYPE_BAD_OR_BAD_CALL_STATE 98
#define CI_CAUSE_MSG_NOT_KOSHER_WITH_CALL_STATE 101
#define CI_CAUSE_UNRECOG_PARAMETER_DISCARDED    110


/*
 ****************************************************************************
 * Circuit group supervision message type indicator.
 *
 * ITU Ref: sec 3.13, page 17. Figure 14/Q.763.
 ***************************************************************************/

#define MAINTENANCE_ORIENTED    0x00
#define HARD_FAILURE_ORIENTED   0x01                                           

/*
 ****************************************************************************
 * Forward Call Indicators.
 *
 * ITU Ref: sec 3.23, page 22. Figure 23/Q.763.
 ****************************************************************************/
/*
 * Bit E: End-to-end Information Indicator (CCITT) 
 */
#define FWD_NO_ETE_INFO 0x00
#define FWD_ETE_INFO    0x01


/*
 ****************************************************************************
 * Generic Digits.
 *
 * ITU Ref: sec 3.24, page 24. Figure 24/Q.763.
 ****************************************************************************/ 
/*
 * Type Of Digits
 */
#define GND_BUS_COMM_GRP_ID     0x03
#define GND_EXTENSION           0x1F


/*
 ****************************************************************************
 *  Optional Backward Call Indicators.
 *
 * ITU Ref: sec 3.37, page 37. Figure 38/Q.763.
 ****************************************************************************/ 
/*
 * Bit B: Call Diversion may occur Indicator. 
 */
#define OBKWD_NO_CALL_DIVERSN         0x00
#define OBKWD_CALL_DIVERSN_MAY_OCCUR  0x01

/*
 * Bit C: Simple Segmentation Indicator 
 */
#define OBKWD_NO_ADDIT_INFO         0x00
#define OBKWD_ADDIT_INFO_SEGMENTED  0x01  


/*
 ****************************************************************************
 * Redirection Information.
 *
 * ITU Ref: sec 3.45, page 42. Figure 4/Q.763.
 ****************************************************************************/ 
/*
 * Bits P-M: Redirecting Reason.
 */  
#define RINFO_DEFLECTION_ALERTING     0x04
#define RINFO_DEFLECTION_IMM_RESP     0x05
#define RINFO_MOB_SUBSC_NOT_REACHABLE 0x06


/*
 ****************************************************************************
 * Transit Network Selection.
 *
 * ITU Ref: sec 3.53, page 56. Figure 53/Q.763.
 ****************************************************************************/ 
/*
 * Odd/even indicator 
 */
#define TNS_EVEN_NUM_DIGITS 0x00
#define TNS_ODD_NUM_DIGITS  0x01


/*
 ******************************************************************************
 * User Service Information.
 * Ref: sec 3.57, page 57-58. Figure 55/Q.763.
 * The format of this parameter is the same as the Bearer Capability
 * Information Element from Recommendation Q.931 and not all
 * capabilities coded are supported at this time.
 *****************************************************************************/
/*
 * OCTET 1: Coding Standard (bits 7,6)
 * and Information transfer capability (bits 5->1)
 */              
#define USI_ISO_IEC         0x01
#define USI_NETWORK         0x03
#define USI_DIGITAL_W_TONES 0x11
#define USI_VIDEO           0x18

/*
 * OCTET 3: User information layer 1 protocol (bits 5->1). 
 */
#define USI_CCITT_G711_ALAW     0x03
#define USI_CCITT_G721_ALAW     0x04
#define USI_CCITT_H221_H242     0x05

/*
 * OCTET 3A: synch/asynch (bit 7), negotiation (bit 6)
 * User rate (bits 5-> 1).
 */                           
#define USI_R_7200BITS_V6       0x06
#define USI_R_8KBITS_I460       0x07

/*
 * OCTET 3B V.120: Intermediate rate(bits 7,6). if bits are not specified
 * then they are either included/required/accept (0x1) or not (0x0).
 */                       
#define USI_NEGOTIATION_W_USER_INFO     0x00

/*
 * 0->5, and 32->47: national use. 48->63: user specified 
 */
#define USI_REC_V21     0x11
#define USI_REC_V22     0x12
#define USI_REC_V22_BIS 0x13
#define USI_REC_V23     0x14
#define USI_REC_V26     0x15
#define USI_REC_V26_BIS 0x16
#define USI_REC_V22_TER 0x17
#define USI_REC_V27     0x18
#define USI_REC_V27_BIS 0x19
#define USI_REC_V27_TER 0x1A
#define USI_REC_V29     0x1B
#define USI_REC_V32     0x1C

#define USI_REC_Q931_I451           0x02

/*
 ****************************************************************************
 * Parameter Definitions in the form of structures.(ITU specific parameters).
 *
 * ITU Ref: Q.763 (03/93).
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/

/*
 ****************************************************************************
 * Access Delivery Info.
 *
 * ITU Ref: sec 3.2, page 9. Figure 4/Q.763.
 ****************************************************************************/
typedef struct                                                              
{
    ITS_OCTET info;
}
ISUP_ACCESS_DELIVERY_INFO;

#define ADI_SETUP_GENERATED     0x00
#define ADI_SET_NOT_GENERATED   0x01


/*
 ****************************************************************************
 * Call Diversion Info.
 *
 * ITU Ref: sec 3.6, page 12. Figure 8/Q.763.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET div_info;
}
ISUP_CALL_DIVERSION_INFO;                               

#define CDVI_UNKNOWN    0x00

/*
 * Bits CBA: Notification subscription 
 */
#define CDVI_PRES_NALLOWED              0x01
#define CDVI_PRES_ALLOWED_W_REDIR_NUM   0x02
#define CDVI_PRES_ALLOWED_WO_REDIR_NUM  0x03

/*
  Bits GFED: Redirection reason
 */
#define CDVI_USER_BUSY          0x01
#define CDVI_NO_REPLY           0x02
#define CDVI_UNCONDITIONAL      0x03
#define CDVI_DEFL_ALERTING      0x04
#define CDVI_DEFL_IMM_RESP      0x05
#define CDVI_MOB_SUB_NO_REACH   0x06

                                                      
/*
 ****************************************************************************
 * Call History Info
 *
 * ITU Ref: sec 3.7, page 12. Figure 42/Q.763.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   prop_delay[2];
}
ISUP_CALL_HISTORY_INFO;


/*
 ****************************************************************************
 * Closed User Group Interlock code
 *
 * ITU Ref: sec 3.15, page 19. Figure 16/Q.763.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   digits[2];                                         
    ITS_OCTET   code[2];
}
ISUP_CLOSED_USR_GRP_INTRLCK_CODE;


/*
 ****************************************************************************
 * Connected Number.
 *
 * ITU Ref: sec 3.16, page 20. Figure 17/Q.763.
 *
 * Note: See Calling Party Number.
 *       Bit 8 of subfields4 is spare.
 *************************************************************************/
typedef ISUP_CALLING_PARTY_NUM ISUP_CONNECTED_NUM;        

/*
 ****************************************************************************
 * Echo Control Information.
 *
 * ITU Ref: sec 3.19, page 21. Figure 20/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   info;
}
ISUP_ECHO_CONTROL_INFO;

#define ECHO_NO_INFO    0x00
#define ECHO_SPARE      0x11

/* Bits BA: Outgoing half echo control device reponse indicator */
#define ECHO_OUT_DEVICE_NOT_INCLUDED    0x01
#define ECHO_OUT_DEVICE_INCLUDED        0x02

/* Bits DC: Incoming half echo control device reponse indicator */
#define ECHO_IN_DEVICE_NOT_INCLUDED    0x01
#define ECHO_IN_DEVICE_INCLUDED        0x02                       

/* Bits FE: Outgoing half echo control device request indicator */
#define ECHO_OUT_DEVICE_ACTIVATION_REQUEST      0x01
#define ECHO_OUT_DEVICE_DEACTIVATION_REQUEST    0x02

/* Bits HG: Incoming half echo control device request indicator */
#define ECHO_IN_DEVICE_ACTIVATION_REQUEST   0x01
#define ECHO_IN_DEVICE_DEACTIVATION_REQUEST 0x02


/*
 ****************************************************************************
 * Facility Indicator.
 *
 * ITU Ref: sec 3.22, page 23. Figure 22/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   fac_ind;
}
ISUP_FACILITY_INDICATOR;

/* The 'fac_ind' octet is encoded as one of the following: */
#define FI_SPARE1               0x00
#define FI_SPARE2               0x01
#define FI_USER_TO_USER_SERV    0x02


/*
 ****************************************************************************
 * Generic Number.
 *
 * ITU Ref: sec 3.26, page 26. Figure 26/Q.763.
 *
 * Note: See Calling Party Address.
 *************************************************************************/
typedef struct
{
    ITS_OCTET qualifier;                                          
    ITS_OCTET nature;
    ITS_OCTET subfields4;
    ITS_OCTET dgts[MAX_NB_OCTETS_DIGITS];
}
ISUP_GENERIC_NUMBER;

/* Number qualifier indicator */
#define GEN_NUM_DIALLED_DIGITS              0x00
#define GEN_NUM_ADITNL_CALLED_NUM           0x01
#define GEN_NUM_USER_PROVIDED_FAIL_NTWRK    0x02
#define GEN_NUM_USER_PROVIDED_NOT_SCREENED  0x03
#define GEN_NUM_REDIRECTING_TERM_NUM        0x04
#define GEN_NUM_ADITNL_CONNECTED_NUM        0x05
#define GEN_NUM_ADITNL_CALLING_NUM          0x06
#define GEN_NUM_ADITNL_ORIG_CALLED_NUM      0x07
#define GEN_NUM_ADITNL_REDIRECTING_NUM      0x08
#define GEN_NUM_ADITNL_REDIRECTION_NUM      0x09
/* other values: Spare/Reserved */

                                                            
/*
 ****************************************************************************
 * Generic Reference.
 *
 * ITU Ref: sec 3.27, page 29. Figure 27/Q.763.
 *
 * Note: See Calling Party Address.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   qualifier;
    ITS_OCTET   refCount;
    ITS_OCTET   refs[4];
}
ISUP_GENERIC_REFERENCE_ENTRY;

typedef struct
{
    /* FIXME: determine max no. of entries */
    ISUP_GENERIC_REFERENCE_ENTRY    entries[10];
}
ISUP_GENERIC_REFERENCE;                                               

/* Qualifier */
#define GEN_REF_CCBS_CONTEXT_ID 0x01
/* other values spare/reserved. */


/*
 ****************************************************************************
 * Location Number.
 *
 * ITU Ref: sec 3.31, page 32. Figure 31/Q.763.
 *
 * Note: See Calling Party Number.
 *************************************************************************/
typedef ISUP_CALLING_PARTY_NUM ISUP_LOCATION_NUMBER;


/*
 ****************************************************************************
 * MCID Request Indicators.                                                    
 *
 * ITU Ref: sec 3.31, page 32. Figure 31/Q.763.
 ***************************************************************************/
typedef struct
{
    ITS_OCTET   indics;
}
ISUP_MCID_REQUEST_INDICATORS;

/* Bit A: MCID Request Indicator */
#define MCID_REQ_MCID_NOT_REQUESTED 0x00
#define MCID_REQ_MCID_REQUESTED     0x01

/* Bit B: Holding Indicator */
#define MCID_REQ_HOLDING_NOT_REQUESTED  0x00
#define MCID_REQ_HOLDING_REQUESTED      0x01

/*
 ****************************************************************************
 * MCID Request Indicators.
 *
 * ITU Ref: sec 3.32, page 33. Figure 32/Q.763.                                
 *************************************************************************/
typedef struct
{
    ITS_OCTET   indics;
}
ISUP_MCID_RESPONSE_INDICATORS;

/* Bit A: MCID Response Indicator */
#define MCID_RESP_MCID_NOT_INCLUDED 0x00
#define MCID_RESP_MCID_INCLUDED     0x01

/* Bit B: Holding Indicator */
#define MCID_RESP_HOLDING_NOT_PROVIDED  0x00
#define MCID_RESP_HOLDING_PROVIDED      0x01


/*
 ****************************************************************************
 * MLPP Precedence.
 *
 * ITU Ref: sec 3.34, page 34. Figure 35/Q.763.                            
 *************************************************************************/
typedef struct
{
    ITS_OCTET   lfbLevel;
    ITS_OCTET   ni[2];
    ITS_OCTET   domain[3];
}
ISUP_MLPP_PRECEDENCE;

/* lfbLevel, bits 76: LFB. */
#define MLPP_LFB_ALLOWED    0X00
#define MLPP_LFB_PATH_RSVD  0X01
#define MLPP_LFB_NALLOWED   0X02
#define MLPP_LFB_SPARE      0X03

/* lfbLevel, bits 41: Precedence Level. */
#define MLPP_FLASH_OVERRIDE 0X00
#define MLPP_FLASH          0X01
#define MLPP_IMMEDIATE      0X02
#define MLPP_PRIORITY       0X03
#define MLPP_ROUTINE        0X04                                       
/* Other values: Spare. */


/*
 ****************************************************************************
 * Message Compatibility information.
 *
 * ITU Ref: sec 3.33, page 33. Figure 33/Q.763,
 *          Figure 34/Q.763 (for instructions)
 *************************************************************************/
typedef struct
{
    ITS_OCTET data[128];
}
ISUP_MSG_COMPATIBILITY_INFO;

/* Bit A: Transit At Intermediate Exchange Indicator. */
#define MSGCI_TRANSIT_INTERP     0x00
#define MSGCI_END_NODE_INTERP    0x01
                                                                       
/* Bit B: B Release Call Indicator. */
#define MSGCI_DO_NOT_RELEASE_CALL  0x00
#define MSGCI_RELEASE_CALL         0x01

/* Bit C:  Send Notification Indicator. */
#define MSGCI_DO_NOT_NOTIFY 0x00
#define MSGCI_NOTIFY        0x01

/* Bit D: Discard Message Indicator. */
#define MSGCI_DO_NOT_DISCARD_MSG  0x00
#define MSGCI_DISCARD_MSG         0x01

/* Bit E: Pass On Not Possible Indicator. */
#define MSGCI_PASSON_RELEASE_CALL   0x00
#define MSGCI_DISCARD_INFO          0x01

/* Bit H : extension indicator */
#define MSGCI_MORE_OCTETS  0x00
#define MSGCI_LAST_OCTET   0x01

#define SET_MC_TRANSIT_IND(x,n,v) \
       ((x)->data[(n)] &= 0xFEU, \
        (x)->data[(n)] |= ((v) & 0x01U))

#define SET_MC_RELEASE_CALL_IND(x,n,v) \
       ((x)->data[(n)] &= 0xFDU, \
        (x)->data[(n)] |= (((v)<<1) & 0x02U))

#define SET_MC_NOTIFY_IND(x,n,v) \
       ((x)->data[(n)] &= 0xFBU, \
        (x)->data[(n)] |= (((v)<<2) & 0x04U))

#define SET_MC_DISCARD_MSG_IND(x,n,v) \
       ((x)->data[(n)] &= 0xF7U, \
        (x)->data[(n)] |= (((v)<<3) & 0x08U))

#define SET_MC_PASS_NOT_POSSIBLE_IND(x,n,v) \
       ((x)->data[(n)] &= 0xEFU, \
        (x)->data[(n)] |= (((x)<<4) & 0x10U))

#define SET_MC_CONTINUE_IND(x,n,v) \
       ((x)->data[(n)] &= 0x7FU, \
        (x)->data[(n)] |= (((v)<<7) & 0x80U))                                


/*
 ****************************************************************************
 * Network specific Facility.
 *
 * ITU Ref: sec 3.36, page 36. Figure 37/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   length_ofNtwrkId;   /* number of bytes present in ntwrk_id */
    ITS_OCTET   ntwrk_type_plan;    /* octet 1a */
    ITS_OCTET   ntwrk_id[12];         /* octet 1b-1m */
    ITS_OCTET   ntwrk_facility[128];
}
ISUP_NETWORK_SPECIFIC_FACILITY;

                                                                               
/*
 ****************************************************************************
 * Optional Forward Call Indicators.
 *
 * ITU Ref: sec 3.38, page 38. Figure 39/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   indics;
}
ISUP_OPT_FWD_CALL_INDICATORS;

/* Bit BA: Closed User Group Call Indicator */
#define OFWD_NON_CUG_CALL                   0x00
#define OFWD_SPARE                          0x01
#define OFWD_CUG_CALL_OUT_ACCESS_ALLOWED    0x02
#define OFWD_CUG_CALL_OUT_ACCESS_NALLOWED   0x03

/* Bit C: Simple Segmentation Indicator */
#define OFWD_NO_ADDITNL_INFO_SENT   0x00                                 
#define OFWD_ADDITNL_INFO_SENT      0x04

/* Bit H: Connected Line Identity Request Indicator */
#define OFWD_NOT_REQUESTED  0x00
#define OFWD_REQUESTED      0x01

/* Other bits: Spare */


/*
 ****************************************************************************
 * Origination ISC PC.
 *
 * ITU Ref: sec 3.40, page 39. Figure 50/Q.763.
 *************************************************************************/
typedef MTP3_POINT_CODE ISUP_ORIG_ISC_POINT_CODE;


/*
 ****************************************************************************
 * Parameter compatibility Information.
 *
 * ITU Ref: sec 3.41, page 39. Figure 41/Q.763, Table 5/Q.763
 *          (for parameter name), Figure 34/Q.763 (for instructions).
 *
 * Notes: See Message Compatibility Information.
 ***************************************************************************/
typedef struct
{
    ITS_OCTET paramName;
    ITS_OCTET instructions[2];
}
ISUP_PARAM_COMPAT_INFO_DATA;

typedef struct
{
    ISUP_PARAM_COMPAT_INFO_DATA param_info[32];
}
ISUP_PARAM_COMPAT_INFO;
                                                                               
/*
 ****************************************************************************
 * Propagation Delay Timer.
 *
 * ITU Ref: sec 3.42, page 40. Figure 42/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   delay[2];
}
ISUP_PROP_DELAY_COUNTER;


/*
 ****************************************************************************
 * Redirection Number.
 *
 * ITU Ref: sec 3.54, page 56. Figure 54/Q.763.
 *
 * Note: See Called Party Number.
 *************************************************************************/
typedef ISUP_CALLED_PARTY_NUM ISUP_REDIRECTION_NUM;


/*
 ****************************************************************************
 * Redirection Number restriction.
 *
 * ITU Ref: sec 3.47, page 43. Figure 45/Q.763.
 ***************************************************************************/
typedef struct
{
    ITS_OCTET   bits;
}
ISUP_REDIRECTION_RESTRICTION;

/* Bits BA: Presentation restricted indicator. Bits H-C: Spare */
#define RNUMR_PRESENTATION_ALLOWED      0x00
#define RNUMR_PRESENTATION_RESTRICTED   0x01                         

/* Bit H of protocol profile: extension indicator */
#define RO_MORE_OCTETS  0x00
#define RO_LAST_OCTET   0x01

/* BitS A->e of protocol profile: protocol profile */
#define RO_ROSE_PROTOCOL        0x11                                  

#define SET_RO_PROTOCOL_ROSE(x,n) \
        ((x)->data[(n)] |= RO_ROSE_PROTOCOL)

#define SET_RO_CONTINUE_IND(x,n,v) \
        ((x)->data[(n)] &= 0x7FU, \
         (x)->data[(n)] |= (((v)<<7) & 0x80U))


/*
 ****************************************************************************
 * Signalling Point Code.
 *
 * ITU Ref: sec 3.50, page 54-55. Figure 50/Q.763.
 ****************************************************************************/
typedef MTP3_POINT_CODE  ISUP_SIGNALLING_POINT_CODE;
                                                                              
/*
 ****************************************************************************
 * Subsequent Number.
 *
 * ITU Ref: sec 3.51, page 55. Figure 51/Q.763.
 *
 * Note: see Called Party Number.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   addr_ind;
    ITS_OCTET   dgts[1];
}
ISUP_SUBSEQUENT_NUM;

/*
 * The 'addr_ind' field has the MSB as the Odd/Even Indicator.
 * The other 7 bits are Spare for this parameter.
 */                                                                            


/*
 ****************************************************************************
 * Transmission Medium Requirement.
 *
 * ITU Ref: sec 3.54, page 56. Figure 54/Q.763.
 *************************************************************************/
typedef struct
{
    ITS_OCTET   tmr;
}
ISUP_TX_MEDIUM_REQUIREMENT;

/* The 'tmr' octet can take the following values. */
#define TMR_SPEECH              0x00
#define TMR_SPARE               0x01
#define TMR_64KBS_UNRESTRICT    0x02                                 
#define TMR_3_1KHZ_AUDIO        0x03
#define TMR_ALT_SPEECH          0x04
#define TMR_ALT_64KBS_UNRESTRICT 0x05
#define TMR_64KBS_PREFERRED     0x06
#define TMR_2T64KBS_UNRESTRICT  0x07
#define TMR_384KBS_UNRESTRICT   0x08
#define TMR_1536KBS_UNRESTRICT  0x09
#define TMR_1920KBS_UNRESTRICT  0x0A


/*
 ***************************************************************************
 * Transmission Medium Requirement Prime.
 *
 * ITU Ref: sec 3.55, page 21. Figure 54/Q.763.
 *
 * Note: See Transmission Medium Requirement.
 *************************************************************************/
typedef ISUP_TX_MEDIUM_REQUIREMENT ISUP_TX_MEDIUM_REQUIREMENT_PRIME;       


/*
 ***************************************************************************
 * Transmission Medium Requirement Used.
 *
 * ITU Ref: sec 3.56, page 21. Figure 54/Q.763.
 *
 * Note: See Transmission Medium Requirement.
 *************************************************************************/
 typedef ISUP_TX_MEDIUM_REQUIREMENT ISUP_TX_MEDIUM_USED;


 /*
 ****************************************************************************
 * User Service Information Prime Information.
 *
 * ITU Ref: sec 3.58, page 58. Figure 55/Q.763.
 *
 * Note: See User Service Information.
 ***************************************************************************/
typedef ISUP_USER_SERVICE_INFO  ISUP_USER_SERVICE_INFO_PRIME;            


/*
 ****************************************************************************
 * User-to-user Indicators.
 *
 * ITU Ref: sec 3.60, page 59. Figure 57/Q.763.
 *************************************************************************/
typedef struct
{
        ITS_OCTET   utu_ind;
}
ISUP_USER_TO_USER_INDICATORS;

/* Bit A: Type */
#define UTU_REQUEST             0x00
#define UTU_RESPONSE            0x01

#define UTU_NO_INFO             0x00
/*
 * If bit 'A' equals UTU_REQUEST (0).
 * Bits C-B: Service 1. Bits E-D: Service 2. Bits G-F: Service 3.         
 * Bit H: Spare.
 */
#define UTU_SPARE_REQ           0x01
#define UTU_REQ_NOT_ESSENT      0x02
#define UTU_REQ_ESSENT          0x03

/*
 * If Bit 'A' equals UTU_RESPONSE (1).
 * Bits C-B: Service 1. Bits E-D: Service 2. Bits G-F: Service 3.
 */
#define UTU_NOT_PROVIDED        0x01
#define UTU_PROVIDED            0x02
#define UTU_SPARE_RESP          0x03

/* Bit H: Network Discard Indicator. */
#define UTU_NTWK_DISCARDED_INFO 0x01

/* The input 'x should be of type (UserTUserInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_UTU_IND_A_BIT(x,y)        /* FIXME */                          

/* The input 'x should be of type (UserTUserInd *) */
/* 'y' should be one of the 4 #defines given above for bits C-B. */
#define SET_UTU_IND_BC_BITS(x,y)        /* FIXME */

/* The input 'x should be of type (UserTUserInd *) */
/* 'y' should be one of the 2 #defines given above for bits E-D. */
#define SET_UTU_IND_DE_BITS(x,y)        /* FIXME */

/* The input 'x should be of type (UserTUserInd *) */
/* 'y' should be one of the 2 #defines given above for bits F-G. */
#define SET_UTU_IND_FG_BITS(x,y)        /* FIXME */

/* The input 'x should be of type (UserTUserInd *) */
/* 'y' should be one of the 2 #defines given above for bit H. */
#define SET_UTU_IND_H_BIT(x,y)        /* FIXME */


/*
 ****************************************************************************
 * User-to-user Information.
 *
 * ITU Ref: sec 3.61, page 60. Figure 58/Q.763.
 *
 * The format of the user-to-user information parameter field is
 * coded identically to the protocol discriminator plus user
 * information field described in 4.5.30/Q.931.
 * Ref: sec 4.5.30/Q.931, page 114.
 *
 * the User-user information element has a network dependent
 * maximum size of 131 octets (including 1 octet for protocol discriminator).
 *************************************************************************/
typedef struct
{
    ITS_OCTET   prot_disc;
    ITS_OCTET   utu_info[130];
}                                                                        
ISUP_USER_TO_USER_INFO;

/* The 'prot_disc' octet can take values as given below: */
#define USR_INFO_USER_SPECIFIC           0x00
#define USR_INFO_OSI_HIGHER_LAYER        0x01
#define USR_INFO_REC_X244                0x02
#define USR_INFO_SYS_MGMT_FUNCT          0x03
#define USR_INFO_IA5_CHARS               0x04
#define USR_INFO_X208_X209_USER_INFO     0x05
#define USR_INFO_V120_RATE_ADAPT         0x07
#define USR_INFO_Q931_I451_USER_NTWK     0x08


/* Begin - ITU97 Specific (09/97) */

/*
 ****************************************************************************
 * Backward Gvns
 *
 * ITU Ref: sec 3.62, page 69. Figure 59/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   backward_gvns[1];
}
ISUP_BACKWARD_GVNS;

/*
 ****************************************************************************
 * CCSS
 *
 * ITU Ref: sec 3.63, page 69. Figure 60/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   ccssInd;
}
ISUP_CCSS;

/*
 ****************************************************************************
 * Call Transfer Number
 *
 * ITU Ref: sec 3.64, page 70. Figure 61/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   nature_addr_ind;
        ITS_OCTET   indicators;
        ITS_OCTET   addr_signals[1];
}
ISUP_CALL_TRANSFER_NUMBER;

/*
 ****************************************************************************
 * Call Transfer Reference
 *
 * ITU Ref: sec 3.65, page 71. Figure 62/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   call_trans_identity;
}
ISUP_CALL_TRANSFER_REFERENCE;

/*
 ****************************************************************************
 * Forward GVNS
 *
 * ITU Ref: sec 3.66, page 72. Figure 63.1,2,3,4/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   opsp_len_ind;
        ITS_OCTET   digits[1];
}OPSP;

typedef struct
{
        ITS_OCTET   gug_len_ind;
        ITS_OCTET   digits[1];
}GUG;

typedef struct
{
        ITS_OCTET   tnrn_indicators;
        ITS_OCTET   digits[1];
}TNRN;

typedef struct
{
        OPSP   opsp;
        GUG    gug;
        TNRN   tnrn;
}
ISUP_FORWARD_GVNS;

/*
 ****************************************************************************
 * Loop Prevention Indicators
 *
 * ITU Ref: sec 3.67, page 74. Figure 64/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   loop_prev_ind;
}
ISUP_LOOP_PREVENTION_INDICATORS;

/*
 ****************************************************************************
 * Network Management Controls
 *
 * ITU Ref: sec 3.68, page 74. Figure 65/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   nw_mgt_ctrls[1];
}
ISUP_NETWORK_MANAGEMENT_CONTROLS;

/*
 ****************************************************************************
 * Circuit Assignment Map
 *
 * ITU Ref: sec 3.69, page 75. Figure 66/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   map_type;
        ITS_OCTET   map_format[4];
}
ISUP_CIRCUIT_ASSIGNMENT_MAP;

/*
 ****************************************************************************
 * Correlation Id
 *
 * ITU Ref: sec 3.70, page 76. Figure 67/Q.763. (09/97)
 * Ref. Q.1218
 *************************************************************************/
typedef struct
{
        ITS_OCTET   corr_Id[1];
}
ISUP_CORRELATION_ID;

/*
 ****************************************************************************
 * SCF Id
 *
 * ITU Ref: sec 3.71, page 76. Figure 68/Q.763. (09/97)
 * Ref. Q.1218
 *************************************************************************/
typedef struct
{
        ITS_OCTET   scf_Id[1];
}
ISUP_SCF_ID;

/*
 ****************************************************************************
 * Call Diversion Treatment Indicators
 *
 * ITU Ref: sec 3.72, page 76. Figure 69/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   call_div_treat_ind[1];
}
ISUP_CALL_DIV_TREAT_INDICATORS;

/*
 ****************************************************************************
 * Called IN Number
 *
 * ITU Ref: sec 3.73, page 77. (09/97)
 * The format of the called IN number parameter corresponds to the
 * original called number parameter (sec: 3.39)
 *************************************************************************/
typedef ISUP_ORIG_CALLED_NUM ISUP_CALLED_IN_NUMBER;

/*
 ****************************************************************************
 * Call offering treatment indicators
 *
 * ITU Ref: sec 3.74, page 77. Figure 70/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   call_off_treat_ind[1];
}
ISUP_CALL_OFF_TREAT_INDICATORS;

/*
 ****************************************************************************
 * Charged Party Identification (national use)
 *
 * ITU Ref: sec 3.75, page 77. (09/97)
 * The format of the charged party identification parameter is network
 * specific. The format is similar to the format of the corresponding
 * INAP parameter in the "FurnishChargingInformation" operation (Q.1218)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   charged_party_iden[1];
}
ISUP_CHARGED_PARTY_IDENTIFICATION;

/*
 ****************************************************************************
 * Conference Treatment Indicators
 *
 * ITU Ref: sec 3.76, page 77. Figure 71/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   conf_treat[1];
}
ISUP_CONF_TREAT_INDICATORS;

/*
 ****************************************************************************
 * Display Information
 *
 * ITU Ref: sec 3.77, page 78. Figure 72/Q.763. (09/97)
 *
 * The format of the display information parameter field
 * is described in Recommendation Q.931
 *************************************************************************/
typedef struct
{
        ITS_OCTET   disp_info[82]; /* to be cross checked with Q.931 */
}
ISUP_DISPLAY_INFORMATION;

/*
 ****************************************************************************
 * UID Action Indicators
 *
 * ITU Ref: sec 3.78, page 78. Figure 73/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   uid_action[1];
}
ISUP_UID_ACTION_INDICATORS;

/*
 ****************************************************************************
 * UID Capability Indicators
 *
 * ITU Ref: sec 3.79, page 79. Figure 74/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   uid_cap_ind[1];
}
ISUP_UID_CAPABILITY_INDICATORS;

/*
 ****************************************************************************
 * Hop Counter
 *
 * ITU Ref: sec 3.80, page 79. Figure 75/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   hop_counter;
}
ISUP_HOP_COUNTER;

/*
 ****************************************************************************
 * Collect Call Request
 *
 * ITU Ref: sec 3.81, page 79. Figure 76/Q.763. (09/97)
 *************************************************************************/
typedef struct
{
        ITS_OCTET   collect_call_req;
}
ISUP_COLLECT_CALL_REQUEST;


/* End - ITU97 Specific (09/97) */

/*************************************************************************
 *
 * externs for messages
 *
 *************************************************************************/
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_ACM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGB_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGBA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGU_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CGUA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_GRA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_GRS_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_ANM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CPG_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CQM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CQR_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CFN_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_COT_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_INF_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_INR_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_IAM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_REL_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RLC_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FOT_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RES_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_SUS_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_BLO_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_BLA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UBL_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UBA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CCR_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_LPA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_RSC_Desc_CCITT;                               
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UCIC_Desc_CCITT;        
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_CON_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FAA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FAC_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FAR_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_FRJ_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_IDR_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_IRS_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_NRM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_OLM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_PAM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_SAM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_SGM_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UPA_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_UPT_Desc_CCITT;
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_USR_Desc_CCITT;
/* This moved from 97 variant dir this is only for 97 */
extern SS7DLLAPI ISUP_MSG_DESC   ISUP_LOP_Desc_CCITT;
          

typedef struct
{
    ITS_OCTET   param_id;
    ITS_OCTET   param_length;
    union
    {
        /*
         * Msg type of the msg included in the PAM:
         * this MUST BE THE FIRST PARAM (no need to populate
         * param_len of param_id).
         * the ieCount parameter in the function ISUP_SendPAMRequest()
         * must represent the number of params for the msg included in
         * the PAM + 1 (for ie  msgTypeInPAM ).
         * ieCount in ISUP_ReceivePAMIndication() will represent the
         * number of params for the msg included in the PAM received + 1
         * for msgTypeInPAM .
         */
        ITS_OCTET                           msgTypeInPAM;
        ISUP_ACCESS_TRANSPORT               accessTransport;
        ISUP_AUTOMATIC_CONGESTION_LEVEL     autoCongestionLevel;
        ISUP_BKWD_CALL_INDICATORS           backwardCallIndicators;            
        ISUP_CALL_REFERENCE                 callRef;
        ISUP_CALLING_PARTY_CATEGORY         callingPartyCategory;
        ISUP_CALLING_PARTY_NUM              callingPartyNum;
        ISUP_CALLED_PARTY_NUM               calledPartyNum;
        ISUP_CAUSE_INDICATOR                causeIndicator;
        ISUP_CIRCUIT_STATE_INDICATORS       circuitStateIndicators;
        ISUP_CONNECTION_REQUEST             connectionRequest;
        ISUP_CONTINUITY_INDICATORS          continuityIndicators;
        ISUP_FORWARD_CALL_INDICATORS        forwardCallIndicators;
        ISUP_EVENT_INFO                     eventInfo;
        ISUP_GENERIC_DIGITS                 genericDigits;
        ISUP_INFORMATION_INDICATORS         informationIndicators;
        ISUP_INFORMATION_REQUEST_INDICATORS informationRequestIndicators;
        ISUP_CONNECTION_INDICATORS          connectionIndicator;
        ISUP_OPT_BKWD_CALL_INDICATORS       optBkwdCallIndicators;
        ISUP_ORIG_CALLED_NUM                origCalledNum;
        ISUP_RANGE_AND_STATUS               rangeAndStatus;
        ISUP_REDIRECTING_NUM                redirectingNum;
        ISUP_REDIRECTION_INFO               redirectionInfo;
        ISUP_SERVICE_ACTIVATION             servactivation;
        ISUP_SUPERVISION_MSG_TYPE           supervisionMsgType;         
        ISUP_SUSPEND_RESUME_INDICATORS      suspendResumeInd;
        ISUP_TRANSIT_NETWORK_SELECTION      transitNetworkSelection;
        ISUP_USER_SERVICE_INFO              userServiceInfo;
        MTP3_HEADER                         routingLabel;
        ISUP_TIMER_ENTRY                    timerData;
        ISUP_ERROR_ENTRY                    errorData;
        ISUP_INDICATION_ENTRY               indData;
        PAD_BUF                             pad;
                 /* CCITT specific parameters */
        ISUP_ACCESS_DELIVERY_INFO           accessDeliveryInfo;
        ISUP_CALL_DIVERSION_INFO            callDiversionInfo;
        ISUP_CALL_HISTORY_INFO              callHistoryInfo;
        ISUP_CLOSED_USR_GRP_INTRLCK_CODE    interlockCode;
        ISUP_CONNECTED_NUM                  connectedNum;
        ISUP_ECHO_CONTROL_INFO              echoControlInfo;
        ISUP_FACILITY_INDICATOR             facilityIndicator;
        ISUP_GENERIC_NOTIFICATION_INDICATOR genericNotificationIndicator;
        ISUP_GENERIC_NUMBER                 genericNumber;
        ISUP_GENERIC_REFERENCE              genericReference;
        ISUP_LOCATION_NUMBER                locationNumber;
        ISUP_MLPP_PRECEDENCE                mlppPrecedence;
        ISUP_MCID_REQUEST_INDICATORS        mcidRequestIndicators;
        ISUP_MCID_RESPONSE_INDICATORS       mcidResponseIndicators;
        ISUP_MSG_COMPATIBILITY_INFO         msgCompatibilityInfo;
        ISUP_NETWORK_SPECIFIC_FACILITY      networkSpecificFacility;    
        ISUP_OPT_FWD_CALL_INDICATORS        optFwdCallIndicators;
        ISUP_ORIG_ISC_POINT_CODE            origIscPointCode;
        ISUP_PARAM_COMPAT_INFO              paramCompatInfo;
        ISUP_PROP_DELAY_COUNTER             propDelayCounter;
        ISUP_REMOTE_OPERATIONS              remoteOperation;
        ISUP_REDIRECTION_NUM                redirectionNum;
        ISUP_REDIRECTION_RESTRICTION        redirectionRestriction;
        ISUP_SIGNALLING_POINT_CODE          signallingPointCode;
        ISUP_SUBSEQUENT_NUM                 subsequentNum;
        ISUP_TX_MEDIUM_REQUIREMENT          txMediumRequirement;
        ISUP_TX_MEDIUM_REQUIREMENT_PRIME    txMediumRequirementPrime;
        ISUP_TX_MEDIUM_USED                 txMediumUsed;
        ISUP_USER_TO_USER_INDICATORS        userToUserIndicators;
        ISUP_USER_TO_USER_INFO              userToUserInfo;
        ISUP_USER_SERVICE_INFO_PRIME        userServiceInfoPrime;

              /* Begin - ITU 97 Specific Parameters */

        ISUP_CIRCUIT_ASSIGNMENT_MAP        circuitAssignmentMap;
        ISUP_CALL_TRANSFER_REFERENCE       callTransferReference;
        ISUP_LOOP_PREVENTION_INDICATORS    loopPreventionIndicators;
        ISUP_CALL_TRANSFER_NUMBER          callTransferNumber;
        ISUP_CCSS                          ccss;
        ISUP_FORWARD_GVNS                  forwardGvns;
        ISUP_BACKWARD_GVNS                 backwardGvns;
        ISUP_NETWORK_MANAGEMENT_CONTROLS   networkManagementControls;
        ISUP_CORRELATION_ID                correlationId;
        ISUP_SCF_ID                        scfId;
        ISUP_CALL_DIV_TREAT_INDICATORS     callDivTreatIndicators;
        ISUP_CALLED_IN_NUMBER              calledInNumber;
        ISUP_CALL_OFF_TREAT_INDICATORS     callOffTreatIndicators;
        ISUP_CHARGED_PARTY_IDENTIFICATION  chargedPartyIdentification;
        ISUP_CONF_TREAT_INDICATORS         confTreatIndicators;
        ISUP_DISPLAY_INFORMATION           displayInformation;
        ISUP_UID_ACTION_INDICATORS         uidActionIndicators;
        ISUP_UID_CAPABILITY_INDICATORS     uidCapabilityIndicators;
        ISUP_HOP_COUNTER                   hopCounter;
        ISUP_COLLECT_CALL_REQUEST          collectCallRequest;

              /* End - ITU 97 Specific Parameters */

              /* end of CCITT specific parameters */
    }
    param_data;
}
ITS_ISUP_IE_CCITT;                                                                  

/*
 * primitives
 */
/* Function prototypes for the user */
SS7DLLAPI int ISUP_ReserveCIC_CCITT(ITS_HANDLE h,
                                     ITS_OCTET sio,
                                     ITS_UINT opc, ITS_UINT dpc,
                                     ITS_USHORT cic,
                                     ITS_OCTET* cic_state,
                                     ITS_CTXT *vcic);

SS7DLLAPI ITS_OCTET ISUP_ComputeMSize_CCITT(ITS_OCTET type);

SS7DLLAPI int ISUP_Encode_CCITT(ITS_ISUP_IE_CCITT *ies, int ieCount,
                                ITS_OCTET msgType, ITS_EVENT *event,
                                ITS_HDR *hdr, ISUP_MSG_DESC* desc);
SS7DLLAPI int ISUP_Decode_CCITT(ITS_ISUP_IE_CCITT *ies, int *ieCount,
                                ITS_EVENT *ev, ISUP_MSG_DESC* desc);

SS7DLLAPI extern CALLBACK_Manager*    ISUP_CCITT_ManagementCallbacks;
                                                                        
/* Function to get the string equivalent for a TimerId (both ITU & ANSI) */
SS7DLLAPI char* ISUP_GetTimerText_CCITT(ITS_UINT timerid);

/* Function to get string equivalent for ISUP msg; abbreviated & full form */
SS7DLLAPI char* ISUP_GetMsgAbbr_CCITT(ITS_UINT msgType);
SS7DLLAPI char* ISUP_GetMsgName_CCITT(ITS_UINT msgType);

/* for variant management */
typedef int             (*__ISUP_DecodeMsgProc_CCITT)(ITS_Class, ITS_EVENT,
                                                      ITS_OCTET, ITS_OCTET,
                                                      ITS_ISUP_IE_CCITT*,
                                                      int*, ITS_HDR*);
typedef int             (*__ISUP_EncodeMsgProc_CCITT)(ITS_Class,
                                                      ITS_ISUP_IE_CCITT*,
                                                      int,
                                                      ITS_OCTET, ITS_OCTET,
                                                      ITS_HDR*, ITS_EVENT*);

/*******************************************************************
 *                       ISUP interface
 *******************************************************************/

/*** ACM ***/
SS7DLLAPI int ISUP_SendACMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveACMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** ANM ***/
SS7DLLAPI int ISUP_SendANMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveANMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CPG ***/
SS7DLLAPI int ISUP_SendCPGRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,  
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCPGIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CQM ***/
SS7DLLAPI int ISUP_SendCQMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCQMIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CQR ***/
SS7DLLAPI int ISUP_SendCQRRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCQRIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount); 

/*** CFN ***/
SS7DLLAPI int ISUP_SendCFNRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCFNIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** COT ***/
SS7DLLAPI int ISUP_SendCOTRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCOTIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** INF ***/
SS7DLLAPI int ISUP_SendINFRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);        
SS7DLLAPI int ISUP_ReceiveINFIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** INR ***/
SS7DLLAPI int ISUP_SendINRRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveINRIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** IAM ***/
SS7DLLAPI int ISUP_SendIAMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveIAMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** REL ***/
SS7DLLAPI int ISUP_SendRELRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRELIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** RLC ***/
SS7DLLAPI int ISUP_SendRLCRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRLCIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** FOT ***/
SS7DLLAPI int ISUP_SendFOTRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveFOTIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** SUS ***/
SS7DLLAPI int ISUP_SendSUSRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveSUSIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** RES ***/
SS7DLLAPI int ISUP_SendRESRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRESIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** BLO ***/                                                               
SS7DLLAPI int ISUP_SendBLORequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveBLOIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** BLA ***/
SS7DLLAPI int ISUP_SendBLARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveBLAIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** UBL ***/
SS7DLLAPI int ISUP_SendUBLRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUBLIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,              
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** UBA ***/
SS7DLLAPI int ISUP_SendUBARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUBAIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CCR ***/
SS7DLLAPI int ISUP_SendCCRRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCCRIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** LPA ***/
SS7DLLAPI int ISUP_SendLPARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveLPAIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** RSC ***/
SS7DLLAPI int ISUP_SendRSCRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveRSCIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** UCIC ***/
SS7DLLAPI int ISUP_SendUCICRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUCICIndication_CCITT(ITS_HANDLE handle,
                                               ITS_EVENT *event,
                                               ITS_HDR *hdr,            
                                               ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CGB ***/
SS7DLLAPI int ISUP_SendCGBRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGBIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CGBA ***/
SS7DLLAPI int ISUP_SendCGBARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGBAIndication_CCITT(ITS_HANDLE handle,
                                               ITS_EVENT *event,
                                               ITS_HDR *hdr,
                                               ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CGU ***/
SS7DLLAPI int ISUP_SendCGURequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGUIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CGUA ***/
SS7DLLAPI int ISUP_SendCGUARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveCGUAIndication_CCITT(ITS_HANDLE handle,
                                               ITS_EVENT *event,
                                               ITS_HDR *hdr,
                                               ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** GRS ***/
SS7DLLAPI int ISUP_SendGRSRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveGRSIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** GRA ***/
SS7DLLAPI int ISUP_SendGRARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveGRAIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** PAM ***/
SS7DLLAPI int ISUP_SendPAMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceivePAMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** CON ***/
SS7DLLAPI int ISUP_SendCONRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount); 
SS7DLLAPI int ISUP_ReceiveCONIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** FAA ***/
SS7DLLAPI int ISUP_SendFAARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveFAAIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** FAC ***/
SS7DLLAPI int ISUP_SendFACRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount,
                                        TCAP_CPT *cpt);

SS7DLLAPI int ISUP_ReceiveFACIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,              
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount,
                                              TCAP_CPT *cpt);

/*** FAR ***/
SS7DLLAPI int ISUP_SendFARRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveFARIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** FRJ ***/
SS7DLLAPI int ISUP_SendFRJRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveFRJIndication_CCITT(ITS_HANDLE handle, 
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);
                                                                              
/*** IDR ***/
SS7DLLAPI int ISUP_SendIDRRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveIDRIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** IRS ***/
SS7DLLAPI int ISUP_SendIRSRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveIRSIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** NRM ***/
SS7DLLAPI int ISUP_SendNRMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                         ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveNRMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,                
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** OLM ***/
SS7DLLAPI int ISUP_SendOLMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveOLMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** SAM ***/
SS7DLLAPI int ISUP_SendSAMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveSAMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** SGM ***/
SS7DLLAPI int ISUP_SendSGMRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr, 
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveSGMIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** UPT ***/
SS7DLLAPI int ISUP_SendUPTRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUPTIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** UPA ***/
SS7DLLAPI int ISUP_SendUPARequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUPAIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount); 
/*** USR ***/
SS7DLLAPI int ISUP_SendUSRRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveUSRIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** Timeout Indication ***/
SS7DLLAPI int ISUP_ReceiveTimeoutIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/*** Error Indication ***/
SS7DLLAPI int ISUP_ReceiveErrorIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);
/*** Indication ***/
SS7DLLAPI int ISUP_ReceiveIndication_CCITT(ITS_HANDLE handle,
                                           ITS_EVENT *event,
                                           ITS_HDR *hdr,
                                           ITS_ISUP_IE_CCITT *ies, int *ieCount);

/* Begin - ITU 97 Specific Message Types */
/*** Loop Prevention ***/
SS7DLLAPI int ISUP_SendLOPRequest_CCITT(ITS_HANDLE handle, ITS_HDR *hdr,
                                        ITS_ISUP_IE_CCITT *ies, int ieCount);
SS7DLLAPI int ISUP_ReceiveLOPIndication_CCITT(ITS_HANDLE handle,
                                              ITS_EVENT *event,
                                              ITS_HDR *hdr,
                                              ITS_ISUP_IE_CCITT *ies, int *ieCount);

/* End - ITU 97 Specific Message Types */

/******************************** ISUP PRIVATE ******************************/
/******************************* USERS STAY OUT *****************************/
/*
 * Users shouldn't call these
 */

SS7DLLAPI int ISUP_EncodeMTP3_CCITT(ITS_ISUP_IE_CCITT *ies, int ieCount,
                                    ITS_OCTET msgType, ITS_EVENT *event,
                                    ITS_HDR *hdr, ISUP_MSG_DESC* desc);
SS7DLLAPI int ISUP_DecodeMTP3_CCITT(ITS_ISUP_IE_CCITT *ies, int *ieCount,
                                    ITS_EVENT *ev, ISUP_MSG_DESC* desc);

SS7DLLAPI int ISUP_SendEvent_CCITT(ITS_HANDLE handle, ITS_OCTET type,      
                                   ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                                   int ieCount, ISUP_MSG_DESC *desc);
SS7DLLAPI int ISUP_ReceiveEvent_CCITT(ITS_HANDLE handle, ITS_EVENT *ev,
                                      ITS_HDR *hdr, ITS_ISUP_IE_CCITT *ies,
                                      int *ieCount, ISUP_MSG_DESC *desc);
SS7DLLAPI int ISUP_MessageSanityCheck_CCITT(ITS_OCTET type, ITS_ISUP_IE_CCITT *ies,
                                            int ieCount, ISUP_MSG_DESC *desc);

SS7DLLAPI int ISUP_UnReserveCIC_CCITT(ITS_HANDLE h, ITS_OCTET sio, ITS_UINT opc, 
                                      ITS_UINT dpc, ITS_USHORT cic);

SS7DLLAPI ISUP_MSG_DESC *ISUP_GetDescriptor_CCITT(ITS_OCTET msgType);

/*
 * This is only for CCITT.  The default variant is White Book.
 * This is not valid for any stack other than the IntelliNet stack.
 */
#define CCITT_ISUP_WHITE_BOOK          1
#define CCITT_ISUP_BLUE_BOOK           2
#define CCITT_ISUP_C_ISUP              3                                   
 

/* ITU specific Timer definitions */
#define ITS_ISUP_TIMER_T38    38
#define ITS_ISUP_TIMER_T39    39

#if defined(INCLUDE_CODEC)
                                                                               
/*
 * this needs to be a well known global to control which ISUP
 * variant is in use.
 */
SS7DLLAPI extern int  CCITT_ISUP_Variant;

#endif /* INCLUDE_CODEC */

#ifdef __cplusplus
}
#endif

#endif /* _ITS_ISUP_CCITT_H_ */            

