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
 *  ID: $Id: isup_cmn.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $
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
 * LOG: Revision 8.9  2005/03/21 13:49:56  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.11.2.2.6.1.10.1  2004/12/16 03:35:28  randresol
 * LOG: Merge JAPAN variant implementation from TTC branch
 * LOG:
 * LOG: Revision 7.11.2.2.6.1.6.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.11.2.2.6.1  2004/01/05 09:43:43  sjaddu
 * LOG: Merged code from tcs isup branch.
 * LOG: CVg: Committing in .
 * LOG:
 * LOG: Revision 7.11.2.2.2.3  2003/11/14 11:21:16  akumar
 * LOG: Added new ind.
 * LOG:
 * LOG: Revision 7.11.2.2.2.2  2003/10/21 06:34:42  akumar
 * LOG: Added ISUP mgmt indications.
 * LOG:
 * LOG: Revision 7.11.2.2.2.1  2003/10/20 06:30:05  akumar
 * LOG: Added PAUSE/RESUME changes.
 * LOG:
 * LOG: Revision 7.11.2.2  2003/06/13 09:07:50  akumar
 * LOG: SET_RAS_STATUS MACRO modified.
 * LOG:
 * LOG: Revision 7.11.2.1  2003/05/07 09:08:45  ssingh
 * LOG: ANSI/ITU latest changes propped from current to 6.3.
 * LOG:
 * LOG: Revision 8.6  2003/04/25 13:24:47  sjaddu
 * LOG: Cic Rules is changed to ITS_OCTET.
 * LOG:
 * LOG: Revision 8.5  2003/04/16 05:39:45  akumar
 * LOG: Added new MACROS for invalid cic/vcic/ and padbuf/cong.
 * LOG:
 * LOG: Revision 8.4  2003/04/04 04:54:11  ssingh
 * LOG: Conformation Indication, structure, #defined, type removed.
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
 * LOG: Revision 8.1  2003/02/13 17:43:23  yranade
 * LOG: Begin PR6.4
 * LOG:
 * LOG: Revision 7.11  2003/02/05 00:50:23  sjaddu
 * LOG: Cic reserve changes.
 * LOG:
 * LOG: Revision 7.10  2003/01/17 15:16:45  sjaddu
 * LOG: vcic changes ITS_USHORT to ITS_CTXT.
 * LOG:
 * LOG: Revision 7.9  2003/01/16 16:22:55  mmiers
 * LOG: Tandem port, large context changes
 * LOG:
 * LOG: Revision 7.8  2003/01/15 12:22:49  ssingh
 * LOG: Added some indications for ANSI-ISUP in support for UCIC/CQR/CGB.
 * LOG:
 * LOG: Revision 7.7  2002/12/31 08:45:12  ssingh
 * LOG: Added New Macro for Segmentation Procedure
 * LOG:
 * LOG: Revision 7.6  2002/12/27 05:26:39  ssingh
 * LOG: Indication added for GRS(received)-UCIC(found)-GRS(dropped).
 * LOG:
 * LOG: Revision 7.5  2002/11/11 11:31:30  akumar
 * LOG: Modified for Automatic Congestion Control procedures
 * LOG:
 * LOG: Revision 7.4  2002/11/07 13:50:00  ssingh
 * LOG: Added two new App-indications.
 * LOG:
 * LOG: Revision 7.3  2002/10/21 12:26:49  ssingh
 * LOG: Added functions to support CQR (received) for ANSI implementation.
 * LOG:
 * LOG: Revision 7.2  2002/10/11 09:32:42  sjaddu
 * LOG: Added ITS_ISUP_IAM_REATTEMPT_IND for Dual seizure procedures.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:08  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.8  2002/08/01 15:47:44  ssharma
 * LOG: Merge from ISUP_PR7.
 * LOG:
 * LOG: Revision 6.7  2002/07/03 19:55:10  mmiers
 * LOG: China fixes
 * LOG:
 * LOG: Revision 6.6.2.13  2002/07/31 20:30:12  sjaddu
 * LOG: Added CFN alert indication.
 * LOG:
 * LOG: Revision 6.6.2.12  2002/07/30 20:27:48  ssingh
 * LOG: Changes done for ANSI95 related parameters.
 * LOG:
 * LOG: Revision 6.6.2.11  2002/07/30 14:44:58  ssingh
 * LOG: Included ANSI95 related parameters.
 * LOG:
 * LOG: Revision 6.6.2.10  2002/07/29 15:07:35  ssingh
 * LOG: New Indication is added for UCIC case.
 * LOG:
 * LOG: Revision 6.6.2.9  2002/07/25 21:32:11  ssingh
 * LOG: Added new functions to handle Indications and Conformations.
 * LOG:
 * LOG: Revision 6.6.2.8  2002/07/18 22:26:09  ssingh
 * LOG: Added more Indications for App handling.
 * LOG:
 * LOG: Revision 6.6.2.7  2002/07/18 18:42:26  ssingh
 * LOG: Added new Indications for App handling.
 * LOG:
 * LOG: Revision 6.6.2.6  2002/07/18 15:55:16  hbalimid
 * LOG: Added new Indications for App handling.
 * LOG:
 * LOG: Revision 6.6.2.5  2002/07/12 20:11:50  ssingh
 * LOG: Added Blocking Indication values.
 * LOG:
 * LOG: Revision 6.6.2.4  2002/07/12 19:53:11  hbalimid
 * LOG: Hardware blocking specific to CCITT
 * LOG:
 * LOG: Revision 6.6.2.3  2002/07/10 19:27:11  ssharma
 * LOG: Changes for redundancy.
 * LOG:
 * LOG: Revision 6.6.2.2  2002/07/02 20:09:29  hbalimid
 * LOG: ITU93 specific params that are not in ANSI92
 * LOG: are moved to itu/isup.h
 * LOG:
 * LOG: Revision 6.6.2.1  2002/07/01 22:19:18  hbalimid
 * LOG: Updated with ISUP ANSI 92 & 95.
 * LOG:
 * LOG: Revision 6.6  2002/06/28 16:07:49  ssingh
 * LOG: Modified for ANSI ISUP.
 * LOG:
 * LOG: Revision 6.5  2002/06/24 17:07:48  ssingh
 * LOG: Add new state for GRA, add confirmations and indications.
 * LOG:
 * LOG: Revision 6.4  2002/06/10 14:46:27  sjaddu
 * LOG: Added ITU CIC states in cmn.
 * LOG:
 * LOG: Revision 6.3  2002/05/20 15:27:49  sjaddu
 * LOG: Merge from PR6 to current.
 * LOG:
 * LOG: Revision 6.2  2002/04/12 18:42:00  hdivoux
 * LOG: Remove C++ comment.
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:36  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.10.2.3  2002/05/13 22:38:03  hbalimid
 * LOG: Updated with ITU 97 variant
 * LOG:
 * LOG: Revision 5.10.2.2  2002/04/04 21:43:55  ssanyal
 * LOG: Adding new msg ISUP_MSG_FAC for ANSI95: also, ANSI & ITU specific timers are transfered from isup_cmn.h to local file.
 * LOG:
 * LOG: Revision 5.10.2.1  2002/03/07 20:17:37  ssharma
 * LOG: New flags in CIC_INFO, new error codes for ISUP error indications.
 * LOG:
 * LOG: Revision 5.10  2002/02/26 23:54:59  ssharma
 * LOG: Add timer and error indications to stack.
 * LOG:
 * LOG: Revision 5.9  2002/02/13 21:21:25  mmiers
 * LOG: Finish up ISUP integration
 * LOG:
 * LOG: Revision 5.8  2002/02/13 18:27:44  mmiers
 * LOG: Finish off the ISUP integration.
 * LOG:
 * LOG: Revision 5.7  2002/02/12 23:30:08  mmiers
 * LOG: ISUP parser in place
 * LOG:
 * LOG: Revision 5.6  2002/02/08 21:49:43  mmiers
 * LOG: Reorg is complete.
 * LOG:
 * LOG: Revision 5.5  2002/02/06 23:44:57  mmiers
 * LOG: Continued ISUP integration
 * LOG:
 * LOG: Revision 5.4  2002/02/01 20:05:56  ssharma
 * LOG: Start work on IntelliNet ISUP stack.
 * LOG:
 * LOG: Revision 5.3  2001/09/21 23:08:33  mmiers
 * LOG: Protect macro arg.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:35  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 ****************************************************************************/
/*******************************************************************************
 *  Revision History:
 * -----------------------------------------------------------------------------
 * Name      Date        Reference       Description
 * -----------------------------------------------------------------------------
 * kramesh   05-04-2005  BCGI bugs       Param msgType in ISUP_ERROR_ENTRY.
 *                       BugId:389,      New  Error Indications per fsm State.
 *                             494       Indication added for CPG received.
 ******************************************************************************/

#ifndef _ITS_ISUP_CMN_H_
#define _ITS_ISUP_CMN_H_

#ident "$Id: isup_cmn.h,v 1.1.1.1 2007-10-08 11:11:20 bsccs2 Exp $"

#include <its.h>
#include <its_callback.h>

#if defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(PRC)
#include <china/mtp3.h>
#elif defined(TTC)
#include <japan/mtp3.h>
#else
#error Protocol version not defined.
#endif
                                                                               
#define ITS_MAX_ISUP_IES         64
#define MAX_ISUP_DATA_LEN        256 

/*
 * Interface
 */
#if defined(__cplusplus)
extern "C"
{
#endif

/*
 * where to find the ISUP msg type if src == ITS_ISUP
 */
#define ISUP_MSG_TYPE(ev)   ((ev)->data[0])
#define ISUP_MSG_DATA(ev)   ((ev)->data[1 + sizeof(ITS_CTXT)])

/*
 * ISUP MSG descriptor
 */
typedef struct
{
    ITS_BOOLEAN hasEOP;
    ITS_OCTET*  mArgs;
    int         nmArgs;
    ITS_OCTET*  vArgs;
    int         nvArgs;
    ITS_OCTET*  oArgs;
    int         noArgs;
}
ISUP_MSG_DESC;



/*
 * a padding aid
 */
typedef struct
{
        ITS_OCTET   buf[MAX_ISUP_DATA_LEN];
}
PAD_BUF; 
                        
/*
 ****************************************************************************
 * Message Types Codes (common section, followed by ANSI then
 *                      ITU specific parameters).
 *
 * ITU Ref: Q.763 (03/93). page 3.
 * Sec 1.3; Table 4/Q.763.
 *
 * ANSI Ref: T1.113-1992. page T1.113.3-49.
 * Sec 4.1; Table 3 and 3A/T1.113.3.
 *
 * The Message Type code consists of a one octet field and is mandatory
 * for all messages. The message type code uniquely defines the function
 * and the format of each ISDN User Part message.
 * All acronyms (last 3/4 letters) are taken from
 * Table 2/Q.762 (03/93), page 14.
 * NOTE: All message types are not supported by the board manufacturer.
 ****************************************************************************/ 
#define ISUP_MSG_ACM    0x06    /* Address Complete  */
#define ISUP_MSG_ANM    0x09    /* Answer  */
#define ISUP_MSG_BLO    0x13    /* Blocking */
#define ISUP_MSG_BLA    0x15    /* Blocking Acknowledgement */
#define ISUP_MSG_CPG    0x2C    /* Call Progress */
#define ISUP_MSG_CGB    0x18    /* Circuit Group Blocking */
#define ISUP_MSG_CGBA   0x1A    /* Circuit Group Blocking Acknowledgement */
#define ISUP_MSG_CQM    0x2A    /* Circuit [Group - ITU] Query */
#define ISUP_MSG_CQR    0x2B    /* Circuit [Group - ITU] Query Response */
#define ISUP_MSG_GRS    0x17    /* Circuit Group Reset */
#define ISUP_MSG_GRA    0x29    /* Circuit Group Reset Acknowledgement */
#define ISUP_MSG_CGU    0x19    /* Circuit Group Unblocking */
#define ISUP_MSG_CGUA   0x1B    /* Circuit Group Unblocking Acknowledgement */
#define ISUP_MSG_CRG    0x31    /* Charge Information */
#define ISUP_MSG_CFN    0x2F    /* Confusion */
#define ISUP_MSG_COT    0x05    /* Continuity */
#define ISUP_MSG_CCR    0x11    /* Continuity Check Request */
#define ISUP_MSG_FOT    0x08    /* Forward Transfer */
#define ISUP_MSG_INF    0x04    /* Information */
#define ISUP_MSG_INR    0x03    /* Information Request */
#define ISUP_MSG_IAM    0x01    /* Initial Address */                          
#define ISUP_MSG_LPA    0x24    /* LoopBack Ack */
#define ISUP_MSG_PAM    0x28    /* Pass Along */
#define ISUP_MSG_REL    0x0C    /* Release */
#define ISUP_MSG_RLC    0x10    /* Release Complete */
#define ISUP_MSG_RSC    0x12    /* Reset Circuit Message */
#define ISUP_MSG_RES    0x0E    /* Resume */
#define ISUP_MSG_SUS    0x0D    /* Suspend */
#define ISUP_MSG_UBL    0x14    /* Unblocking */
#define ISUP_MSG_UBA    0x16    /* Unblocking Acknowledgement */
#define ISUP_MSG_UCIC   0x2E    /* Unequipped Circuit Identification Code */

/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 * Following message types represent messages constructed by the local
 * stack and have only local significance.
 */
#define ISUP_MSG_TIM    0xFF    /* Timeout indication */
#define ISUP_MSG_ERR    0xFE    /* Error indication  */
#define ISUP_MSG_IND    0xFD    /* CPC Indication   */
#define ISUP_MSG_LCONG  0xFC    /* Local congestion Indication   */
#define ISUP_MSG_STAT   0xFB    /* MTP3 Mgmt Indication   */

/*
 ****************************************************************************
 * Parameter Names and Identifiers (common section, followed by ANSI
 *                                  then ITU specific parameters).
 *
 * ITU Ref: Q.763 (03/93) page 8.
 * Sec: 3.1 Table 5/Q.763.
 *
 * ANSI Ref: T1.113-1992. page T1.113.3-52.
 * Sec 4.1; Table 4 and 4A/T1.113.3.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/
#define ISUP_PRM_ACCESS_TRANSPORT               0x03
#define ISUP_PRM_AUTO_CONGEST_LEVEL             0x27
#define ISUP_PRM_BKWD_CALL_INDICATORS           0x11
#define ISUP_PRM_CALL_REF                       0x01
#define ISUP_PRM_CALLED_PARTY_NUM               0x04
#define ISUP_PRM_CALLING_PARTY_CATEGORY         0x09
#define ISUP_PRM_CALLING_PARTY_NUM              0x0A
#define ISUP_PRM_CAUSE_INDICATORS               0x12
#define ISUP_PRM_CONNECTION_REQ                 0x0d                     
#define ISUP_PRM_CONTINUITY_INDICATORS          0x10
#define ISUP_PRM_CKT_GRP_SUPRVN_MT_IND          0x15
#define ISUP_PRM_CKT_STATE_INDICATOR            0x26
#define ISUP_PRM_EVENT_INFO                     0x24
#define ISUP_PRM_EOP                            0x00
#define ISUP_PRM_FWD_CALL_INDICATORS            0x07
#define ISUP_PRM_GENERIC_DIGITS                 0xc1
#define ISUP_PRM_INFO_INDICATORS                0x0f
#define ISUP_PRM_INFO_REQ_INDICATORS            0x0e
#define ISUP_PRM_NATURE_CONN_INDICATORS         0x06
#define ISUP_PRM_OPT_BKWD_CALL_INDICATORS       0x29
#define ISUP_PRM_ORIG_CALLED_NUM                0x28
#define ISUP_PRM_RANGE_STATUS                   0x16
#define ISUP_PRM_REDIRECTING_NUM                0x0b
#define ISUP_PRM_REDIRECTION_INFO               0x13        
#define ISUP_PRM_SERVICE_ACTIVATION             0x33 
#define ISUP_PRM_SUSP_RESUM_INDICATORS          0x22
#define ISUP_PRM_TRANSIT_NTWK_SELECT            0x23
#define ISUP_PRM_USER_SERVICE_INFO              0x1d

#define ISUP_PRM_PASS_THRU                      0xFE
#define ISUP_PRM_ROUTING_LABEL                  0xFF

/* IntelliSS7 specifics: param id for msgTypeInPAM */
#define ISUP_PRM_MSG_IN_PAM                     0xAA        


/* This Param Id will be used in case, an Invalid Param
 * is encountered during decoding the event received from
 * the MTP3, while calling ReceiveEvent() API. It will
 * denote the Data DUMP followed after invalid param, includes
 * the inv param also
 */
#define ISUP_PRM_PAD_BUF                        0xBB

/* NOTE NOTE NOTE NOTE NOTE NOTE NOTE NOTE
 * Following param types represent params constructed by the local
 * stack and have only local significance.
 */
#define ISUP_PRM_TIMEOUT_DATA                   0xFD    
#define ISUP_PRM_ERROR_DATA                     0xFC    
#define ISUP_PRM_INDICATION_DATA                0xFB

/* To send PAUSE/RESUME/STATUS msg to app */
#define ISUP_PRM_MGMTIND_DATA                   0xCC

/*
 ****************************************************************************
 * Parameter Definitions in the form of structures.(common section,
 *                       followed by ANSI then ITU specific parameters).
 *
 * ITU Ref: Q.763 (03/93).
 *
 * ANSI Ref: T1.113-1992.
 *
 * The parameter names and their codes are given below.
 * NOTE: All parameters are not supported by the board manufacturer.
 ****************************************************************************/ 

/*
 ****************************************************************************
 * Access transport.
 *
 * ITU Ref: sec 3.3, page 9.
 * This information element is coded as described in sec 4.5/Q.931.
 * Multiple Q.931 information elements can be included within this
 * parameter.
 *
 * ANSI Ref: sec 3.1A (Figure 3A/T1.113.3), page T1.113.3-3.
 * This information element is coded as described in sec 4.5/T1.607.
 * Multiple T1.607 information elements can be included within this
 * parameter.
 ****************************************************************************/
typedef struct
{
        ITS_OCTET   acc_transport[128];
}
ISUP_ACCESS_TRANSPORT;                                              

/*
 ****************************************************************************
 * Automatic Congestion Level.
 *
 * ITU Ref: sec 3.4. page 10. Figure 6/Q.763.
 *
 * ANSI Ref: sec 3.2A (Figure 3B/T1.113.3), page T1.113.3-3.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET level;
}
ISUP_AUTOMATIC_CONGESTION_LEVEL;

#define AC_LEVEL_1    0x01
#define AC_LEVEL_2    0x02
/* other values: spare */
                                                                          

/*
 ****************************************************************************
 * Backward Call Indicators.
 *
 * ITU Ref: sec 3.5. page 10. Figure 7/Q.763.
 *
 * ANSI Ref: sec 3.3 (Figure 5/T1.113.3), page T1.113.3-3.
 ****************************************************************************/
typedef struct
{
        ITS_OCTET   bkwd_ci[2];
}
ISUP_BKWD_CALL_INDICATORS;

#define BKWD_NO_INDICATION  0x00
#define BKWD_SPARE          0x03

/*
 * The following codes are used in the backward call indicators
 * parameter field
 * Bits B & A:  Charge Indicator
 * NOTE: The interpretation of the Charge Indicator bits depends             
 * only on the charging exchange.
 */
#define BKWD_NO_CHARGE  0x01
#define BKWD_CHARGE     0x02

/* Bits D & C: Called Party's Status Indicator. */
#define BKWD_SUBSCRIBER_FREE    0x01
#define BKWD_CONNECT_WHEN_FREE  0x02                    

/* Bits F & E: Called Party's Category indicator */
#define BKWD_ORDINARY_SUBSCRIBER    0x01
#define BKWD_PAYPHONE               0x02

/* Bits H & G: End-to-End method indicator. */
#define BKWD_NO_ETE_METHOD      0x00
#define BKWD_PASS_ALONG_METHOD  0x01
#define BKWD_SCCP_METHOD        0x02
#define BKWD_PASS_ALONG_SCCP    0x03

/* Bit I: Interworking Indicator. */
#define BKWD_NO_INTWK_ENCOUNTERED   0x00
#define BKWD_INTWK_ENCOUNTERED      0x01

/* Bit J: End-to-end Information Indicator */

/* Bit K: ISDN User Part Indicator */
#define BKWD_ISUP_NOT_ALL_WAY   0x00                             
#define BKWD_ISUP_ALL_WAY       0x01

/* Bit L: Holding Indicator (national use) */
#define BKWD_HOLDING_NOT_REQ    0x00
#define BKWD_HOLDING_REQ        0x01

/* Bit M: ISDN Access Indicator */
#define BKWD_TERM_NON_ISDN  0x00
#define BKWD_TERM_ISDN      0x01

/* Bit N: Echo Control Device Indicator */
#define BKWD_DEVICE_NOT_INCL    0x00
#define BKWD_DEVICE_INCL        0x01

/* Bits P & O: SCCP Method Indicator */
#define BKWD_CONNLESS_METHOD    0x01
#define BKWD_CONNORIEN_METHOD   0x02
#define BKWD_CONNLESS_CONNORIEN 0x03

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */                  
#define SET_BKWD_CI_BA_BITS(x,y)        ((x)->bkwd_ci[0] &= 0xFCU,   \
                                         (x)->bkwd_ci[0] |= ((y) & 0x3U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_DC_BITS(x,y)         ((x)->bkwd_ci[0] &= 0xF3U,   \
                                         (x)->bkwd_ci[0] |= (((y)<<2) & 0xCU))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_FE_BITS(x,y)         ((x)->bkwd_ci[0] &= 0xCFU,   \
                                         (x)->bkwd_ci[0] |= (((y)<<4) & 0x30U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_HG_BITS(x,y)         ((x)->bkwd_ci[0] &= 0x3FU,   \
                                         (x)->bkwd_ci[0] |= (((y)<<6) & 0xC0U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_I_BIT(x,y)           ((x)->bkwd_ci[1] &= 0xFEU,   \
                                         (x)->bkwd_ci[1] |= ((y) & 0x01U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_J_BIT(x,y)          ((x)->bkwd_ci[1] &= 0xFDU,   \
                                         (x)->bkwd_ci[1] |= (((y)<<1) & 0x02U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_K_BIT(x,y)          ((x)->bkwd_ci[1] &= 0xFBU,   \
                                         (x)->bkwd_ci[1] |= (((y)<<2) & 0x04U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_L_BIT(x,y)          ((x)->bkwd_ci[1] &= 0xF7U,   \
                                         (x)->bkwd_ci[1] |= (((y)<<3) & 0x08U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_M_BIT(x,y)          ((x)->bkwd_ci[1] &= 0xEFU,   \
                                         (x)->bkwd_ci[1] |= (((y)<<4) & 0x10U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_N_BIT(x,y)          ((x)->bkwd_ci[1] &= 0xDFU,   \
                                         (x)->bkwd_ci[1] |= (((y)<<5) & 0x20U))

/* The input 'x should be of type (BackwardCallInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_BKWD_CI_PO_BITS(x,y)        ((x)->bkwd_ci[1] &= 0x3FU,   \
                                         (x)->bkwd_ci[1] |= (((y)<<6) & 0xC0U))


/*
 ****************************************************************************
 * Call Reference.
 *
 * ITU Ref: sec 3.8, page 12 (Figure 9/Q.763).
 *
 * ANSI Ref: sec 3.5 (Figure 7/T1.113.3), page T1.113.3-5.
 ****************************************************************************/
typedef struct                                                                 
{
    ITS_OCTET       call_ident[3];  /* 24 bits */
    MTP3_POINT_CODE point_code;
}
ISUP_CALL_REFERENCE;


/*
 ****************************************************************************
 * Called Party Number.
 *
 * ITU Ref: sec 3.9, page 13 (Figure 10/Q.763).
 *
 * ANSI Ref: sec 3.6 (Figure 8/T1.113.3), page T1.113.3-5.
 ****************************************************************************/
#define MAX_NB_OCTETS_DIGITS    (10)
typedef struct
{
    ITS_OCTET   addr_ind;
    ITS_OCTET   num_plan;
    ITS_OCTET   dgts[MAX_NB_OCTETS_DIGITS];                      
}
ISUP_CALLED_PARTY_NUM;

#define CDPN_SPARE  0x00

/* The MSB of the octet 'addr_ind' is the Odd/Even Indicator. */
#define CDPN_EVEN_DIGITS    0x00
#define CDPN_ODD_DIGITS     0x01

/* The other 7 bits of the octet 'addr_ind' represent the */
/* Nature of Address Indicator, as defined below */
#define CDPN_SUBSCRIBER_NUM     0x01
#define CDPN_NATIONAL_NUM       0x03
#define CDPN_INTL_NUM           0x04                           

/*
 * The MSB of the octet 'num_plan' represents the Internal Network Number
 * Indicator (INN ind) (CCITT only, Spare for ANSI).
 */

/*
 * Bits 7->5 of the octet 'num_plan' represent the  Numbering Plan Indicator,
 * Bits 4->1 are reserved (ANSI) or spare (CCITT).
 */
#define CDPN_ISDN_PLAN               0x01
#define CDPN_CPN_SPARE_02            0x02
#define CDPN_DATA_PLAN               0x03
#define CDPN_TELEX_PLAN              0x04
#define CDPN_SPARE_07                0x07                           

/* The octet 'dgts' is the start of the digit string. */
/* They are BCD encoded digits, 0 - 9 being same in hex. Others are: */
#define CDPN_DGT_SPARE            0x0A
#define CDPN_DGT_CODE_11          0x0B
#define CDPN_DGT_CODE_12          0x0C
#define CDPN_DGT_STAR             0x0D
#define CDPN_DGT_POUND            0x0E
#define CDPN_DGT_ST               0x0F


/*
 ****************************************************************************
 * Calling Party's Category.
 *
 * ITU Ref: sec 3.11, page 16 (Figure 12/Q.763).
 *
 * ANSI Ref: sec 3.8 (Figure 9/T1.113.3), page T1.113.3-7.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   cat;                                                
}
ISUP_CALLING_PARTY_CATEGORY;

/* The 'cat' octet can be one of the following codes */
#define CGP_CAT_UNKNOWN            0x00
#define CGP_CAT_FRENCH             0x01
#define CGP_CAT_ENGLISH            0x02
#define CGP_CAT_GERMAN             0x03
#define CGP_CAT_RUSSIAN            0x04
#define CGP_CAT_SPANISH            0x05
#define CGP_CAT_RESERVED           0x09
#define CGP_CAT_ORDINARY_SUBSC     0x0A
#define CGP_CAT_PRIORITY_SUBSC     0x0B
#define CGP_CAT_DATA_CALL          0x0C
#define CGP_CAT_TEST_CALL          0x0D
#define CGP_CAT_SPARE              0x0E
#define CGP_CAT_PHONE              0x0F

                                                                               
/*
 ****************************************************************************
 * Calling Party Number.
 *
 * ITU Ref: sec 3.10, page 14 (Figure 11/Q.763).
 *
 * ANSI Ref: sec 3.7 (Figure 8A/T1.113.3), page T1.113.3-6.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   addr_ind;
    ITS_OCTET   subfields4;
    ITS_OCTET   dgts[MAX_NB_OCTETS_DIGITS];
}
ISUP_CALLING_PARTY_NUM;

#define CGPN_SPARE  0x00

/* The MSB of the octet 'addr_ind' is the Odd/Even Indicator. */
#define CGPN_EVEN_DIGITS    0x00
#define CGPN_ODD_DIGITS     0x01

/* Nature of Address Indicator */                                              
#define CGPN_SUBSCRIBER_NUM         0x01
#define CGPN_NATL_NUM               0x03
#define CGPN_INTL_NUM               0x04

/* The 'subfields4' octet comprises 4 parts. */
/* The MSB represents the Calling Party Number Incomplete Indicator (NI) */

/*
 * The three bits adjascent to the MSB represent the, Nature of Address
 * Indicator. They are the same as the ones for the Called Party Num.
 */

/*
 * The 2 bits adjescent to the Numbering Plan Indicator represent
 * the Address Presentation Restricted Indicator.
 */
#define CGPN_PRESENTATION_ALLOWED    0x00
#define CGPN_PRESENTATION_RESTRICTED 0x01

/* The 2 LSB's represent the Screening Indicator. */
#define CGPN_USER_PROV_NOT_VER       0x00
#define CGPN_USER_PROV_VER_PASS      0x01
#define CGPN_USER_PROV_VER_FAIL      0x02
#define CGPN_NTWRK_PROV              0x03                           

/* The input 'x should be of type (CallingPartyNum *) */
/* 'y' should be one of the 5 #defines given above for CalledPartyNum. */
#define SET_CPGN_ADDR_IND(x,y)        /* FIXME */


/*
 ****************************************************************************
 * Cause Indicator.
 *
 * ITU Ref: sec 3.12, page 17. Figure 13/Q.763.
 * The codes in the subfields of the cause indicators parameter
 * fields are defined in the Q.6XX-Series Recommendations.
 *
 * ANSI Ref: sec 3.9 (Figure 10 and 10A/T1.113.3), page T1.113.3-8.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   subfields4;
    ITS_OCTET   cause_val;
    ITS_OCTET   diagnostics[1];
}                                                                   
ISUP_CAUSE_INDICATOR;

/*
 * subfields4 octet comprises of:  'Location' subfield (bit 1 -> 4),
 * followed by one spare bit, followed by the
 * 'Coding Standard' subfield (bit 7 & 6) and the 'Ext' bit (bit 8).
 */

/* extension bit */
#define CI_EXTEND       1
#define CI_NO_EXTEND    0

/* Coding Standard */
#define CI_CS_CCITT         0
#define CI_CS_ISOIEC        1
#define CI_CS_NATIONAL      2
#define CI_CS_ANSI          CI_CS_NATIONAL

/* Location */
#define CI_LOC_USER                     0x00
#define CI_LOC_PRIV_SERV_LOCAL          0x01
#define CI_LOC_PUB_SERV_LOCAL           0x02                            
#define CI_LOC_TRANSIT                  0x03
#define CI_LOC_PUB_SERV_REMOTE          0x04
#define CI_LOC_PRIV_SERV_REMOTE         0x05
#define CI_LOC_INTERNATIONAL            0x07
                                               
/* cause values, as per Q.850, Table 1 */
#define CI_CAUSE_UNALLOCATED                    1
#define CI_CAUSE_NO_ROUTE_TO_TRANSIT            2
#define CI_CAUSE_NO_ROUTE_TO_DEST               3
#define CI_CAUSE_SEND_SPECIAL_TONE              4
#define CI_CAUSE_MISDIALLED_TRUNK_PFX           5

#define CI_CAUSE_NORMAL                         16
#define CI_CAUSE_USER_BUSY                      17
#define CI_CAUSE_NO_USER_RESPONDING             18 
#define CI_CAUSE_NO_ANSWER_FROM_USER            19             

#define CI_CAUSE_CALL_REJECTED                  21
#define CI_CAUSE_NUMBER_CHANGED                 22
                                         

#define CI_CAUSE_DEST_OUT_OF_ORDER              27
#define CI_CAUSE_INVALID_NUMBER_FORMAT          28
#define CI_CAUSE_FACILITY_REJECTED              29

#define CI_CAUSE_NORMAL_UNSPECIFIED             31
#define CI_CAUSE_NO_CHANNEL_AVAILABLE           34
#define CI_CAUSE_NETWORK_OUT_OF_ORDER           38

#define CI_CAUSE_TEMPORARY_FAILURE              41
#define CI_CAUSE_SWITCH_CONGESTED               42
#define CI_CAUSE_ACCESS_INFO_DISCARDED          43
#define CI_CAUSE_REQUESTED_CHN_UNAVAIL          44                      

#define CI_CAUSE_RESOURCE_UNAVAIL_UNSPEC        47

#define CI_CAUSE_REQUESTED_FAC_NOT_SUBSCRIBED   50
                                                 

#define CI_CAUSE_INCOMING_CALL_BARRED_IN_CUG    55
#define CI_CAUSE_BEARER_CAP_NOT_AUTH            57
#define CI_CAUSE_BEARER_CAP_NOT_AVAIL           58

#define CI_CAUSE_SERV_OPT_NOT_AVAIL_UNSPEC      63
#define CI_CAUSE_BEARER_CAP_NOT_IMPL            65

#define CI_CAUSE_REQUEST_FAC_NOT_IMPL           69
#define CI_CAUSE_RESTRICTED                     70
#define CI_CAUSE_SERV_OPT_UNIMPL_UNSPEC         79
#define CI_CAUSE_INVALID_CALL_REF               81

#define CI_CAUSE_NOT_MEMBER_OF_CUG              87
#define CI_CAUSE_INCOMPATIBLE_DEST              88
#define CI_CAUSE_NONEXISTENT_CUG                90

#define CI_CAUSE_INVALID_MSG_UNSPEC             95

#define CI_CAUSE_MSG_TYPE_BAD                   97             

#define CI_CAUSE_IE_NONEXISTENT_OR_UNIMPL       99
#define CI_CAUSE_IE_HAS_INVALID_CONTENTS        100

#define CI_CAUSE_RECOVERY_ON_TIMER_EXPIRY       102
#define CI_CAUSE_BAD_PARAMETER_PUNTED           103

#define CI_CAUSE_PROTOCOL_ERROR                 111
#define CI_CAUSE_INTERWORKING                   127


/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_CI_EXT_IND(x,y)             ((x)->subfields4 &= 0x7FU,   \
                                         (x)->subfields4 |= (((y)<<7) & 0x80U))

/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_CI_CODING_STANDARD(x,y)     ((x)->subfields4 &= 0x9FU,   \
                                         (x)->subfields4 |= (((y)<<5) & 0x60U))

/* The input 'x should be of type (CauseInd *) */                           
/* 'y' should be one of the 2 #defines given above. */
#define SET_CI_EXT_IND(x,y)             ((x)->subfields4 &= 0x7FU,   \
                                         (x)->subfields4 |= (((y)<<7) & 0x80U))

/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_CI_CODING_STANDARD(x,y)     ((x)->subfields4 &= 0x9FU,   \
                                         (x)->subfields4 |= (((y)<<5) & 0x60U))

/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 8 #defines given above. */
#define SET_CI_LOCATION(x,y)            ((x)->subfields4 &= 0xF0U,   \
                                         (x)->subfields4 |= ((y) & 0x0FU))

/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 2 #defines given above (CI_EXTEND, CI_NO_EXTEND). */
#define SET_CI_CAUSE_EXT_IND(x,y)       ((x)->cause_val &= 0x7FU,   \
                                         (x)->cause_val |= (((y)<<7) & 0x80U)) 

/* The input 'x should be of type (CauseInd *) */
/* 'y' should be one of the 4 #defines given above. */
#define SET_CI_CAUSE(x,y)               ((x)->cause_val &= 0x80U,   \
                                         (x)->cause_val |= ((y) & 0x7FU))

/*
 *
 * Ref: sec 3.14
 */
/*
 ****************************************************************************
 * Circuit State Indicator.
 *
 * ITU Ref: sec 3.14, page 18. Figure 15/Q.763.
 *
 * ANSI Ref: sec 3.11B (Figure 11B/T1.113.3), page T1.113.3-13.
 ***************************************************************************/
typedef struct
{
    ITS_OCTET   states[32];
}                                                                              
ISUP_CIRCUIT_STATE_INDICATORS;


/* Bits BA for CCITT (if Bits DC=00). Circuit State Indic octet for ANSI. */
#define CKTS_TRANSIENT              0x00
#define CKTS_UNEQUIPPED             0x03
                                                       
/*
 ****************************************************************************
 * Circuit State Indicator.
 *
 * ITU Ref: sec 3.14, page 18. Figure 15/Q.763.
 ***************************************************************************/
/*
 * Bits BA: Maintenance Blocking State. Bits FE: Hardware Blocking State
 */
#define CKTS_ACTIVE     0x00
#define CKTS_LBLOCKED   0x01
#define CKTS_RBLOCKED   0x02
#define CKTS_LRBLOCKED  0x03

/*
 * Bits DC: Call Processing State: not Equal to 00
 */
#define CKTS_OUT_OF_ORDER_CTK     0x00
#define CKTS_IN_CTK_BUSY   0x01
#define CKTS_OUT_CTK_BUSY  0x02
#define CKTS_IDLE_CTK      0x03


/*
 ****************************************************************************
 * ConnectionRequest.
 *
 * ITU Ref: sec 3.17, page 20. Figure 18/Q.763.
 *
 * ANSI Ref: sec 3.15 (Figure 14/T1.113.3), page T1.113.3-14.
 * Protocol Class and Credit:  see Chapter T1.112.3 ANSI T1.112.
 ****************************************************************************/
typedef struct
{
    /* local reference for ANSI */
    ITS_OCTET       call_ident[3];
    MTP3_POINT_CODE point_code;
    ITS_OCTET       protocol_class; /* undefined */
    ITS_OCTET       credit;         /* undefined */
}
ISUP_CONNECTION_REQUEST;                                                    


/*
 ****************************************************************************
 * Continuity Indicators.
 *
 * ITU Ref: sec 3.18, page 21. Figure 19/Q.763.
 *
 * ANSI Ref: sec 3.16 (Figure 15/T1.113.3), page T1.113.3-14.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indicators;
}
ISUP_CONTINUITY_INDICATORS;

/* Bit A: Continuity indicator */
#define CONTINUITY_CHECK_FAILED     0x00
#define CONTINUITY_CHECK_SUCCESS    0x01                          

/* Bit A: Continuity indicator */
#define CONTINUITY_CHECK_FAILED     0x00
#define CONTINUITY_CHECK_SUCCESS    0x01

/*
 *
 * reference 3.13 Q.763
 */
/*
 ****************************************************************************
 * Circuit group supervision message type indicator.
 *
 * ITU Ref: sec 3.13, page 17. Figure 14/Q.763.
 *
 * ANSI Ref: sec 3.11 (Figure 11/T1.113.3), page T1.113.3-12.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET sup_mt;
}
ISUP_SUPERVISION_MSG_TYPE;                                                 
#define RESERVED_NATNL_USE          0x02


/*
 ****************************************************************************
 * Event Information.
 *
 * ITU Ref: sec 3.21, page 22. Figure 21/Q.763.
 *
 * ANSI Ref: sec 3.17A (Figure 15B/T1.113.3), page T1.113.3-14.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   evt_info;
}
ISUP_EVENT_INFO;                                                            

/* The MSB of the octet 'evt_info' represents the */
/* Event Presentation Restricted Indicator. */
#define EI_NO_INDICATION        0x0
#define EI_PRESN_RESTRICTED     0x1

/* The rest of the 7 bits can be coded as one of the following: */
#define EI_SPARE                0x00
#define EI_ALERTING             0x01
#define EI_PROGRESS             0x02
#define EI_INBAND_INFO          0x03
#define EI_CALL_FWD_BUSY        0x04
#define EI_CALL_FWD_NOREPLY     0x05
#define EI_CALL_FWD_UNCOND      0x06                                 

/* The input 'x should be of type (EventInfo *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_EI_PRES_IND(x,y)            ((x)->evt_info &= 0x7FU,   \
                                         (x)->evt_info |= (((y)<<7) & 0x80U))

/* The input 'x should be of type (EventInfo *) */
/* 'y' should be one of the 7 #defines given above. */
#define SET_EI_INFO(x,y)                ((x)->evt_info &= 0x80U,   \
                                         (x)->evt_info |= ((y) & 0x7FU))


/*
 ****************************************************************************
 * Forward Call Indicators.
 *
 * ITU Ref: sec 3.23, page 22. Figure 23/Q.763.
 *
 * ANSI Ref: sec 3.20 (Figure 18/T1.113.3), page T1.113.3-15.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   fwd_ci[2];                                                  
}
ISUP_FORWARD_CALL_INDICATORS;

/* Bit A: National/International Call Indicator. */
#define FWD_NATNL_CALL      0x00
#define FWD_INTNATNL_CALL   0x01


/* Bits C & B: End-to-end method Indicator. */
#define FWD_NO_ETE_METHOD       0x00
#define FWD_PASS_ALONG_METHOD   0x01
#define FWD_SCCP_METHOD         0x02
#define FWD_PASS_ALONG_SCCP     0x03

/* Bit D: Interworking Indicator. */
#define FWD_NO_INTWK_ENCOUNTERED    0x00
#define FWD_INTWK_ENCOUNTERED       0x01

/* Bit E: End-to-end Information Indicator (CCITT) */

/* Bit E: IAM segmentation indicator (ANSI) */             

/* Bit F: ISDN User Part Indicator */
#define FWD_ISUP_NOT_ALL_WAY    0x00
#define FWD_ISUP_ALL_WAY        0x01

/* Bits H & G: ISDN User Part Preference Indicator */
#define FWD_ISUP_PREFERRED      0x00
#define FWD_ISUP_NOT_REQUIRED   0x01
#define FWD_ISUP_REQUIRED       0x02
#define FWD_ISUP_SPARE          0x03

/* Bit I: ISDN Access Indicator */
#define FWD_ORIG_NON_ISDN   0x00
#define FWD_ORIG_ISDN       0x01


/* Bits K & J: SCCP Method Indicator */                                    
#define FWD_NO_INDICATION       0x00
#define FWD_CONNLESS_METHOD     0x01
#define FWD_CONNORIEN_METHOD    0x02
#define CFWD_ONNLESS_CONNORIEN  0x03

/* Bit L: Spare. Bits P - M: reserved for National Use */


/*
 ****************************************************************************
 * Generic Digits.
 *
 * ITU Ref: sec 3.24, page 24. Figure 24/Q.763.
 *
 * ANSI Ref: sec 3.20B (Figure 18B/T1.113.3), page T1.113.3-16.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET type_scheme;
    ITS_OCTET digits[128];
}                                                                    
ISUP_GENERIC_DIGITS;

/* Type of Digits */
#define GND_ACCOUNT_CODE        0x00
#define GND_AUTHORIZATION_CODE  0x01
#define GND_PRIVATE_NETWORK     0x02

#define GND_EXTENSION           0x1F
/*#endif*/
/* other values: spare/reserved */

/* Encoding Scheme */
#define GND_BCD_EVEN    0x00
#define GND_BCD_ODD     0x01
#define GND_IA5         0x02
#define GND_BINARY      0x03
/* other values: spare/reserved */


/*
 ****************************************************************************
 * Information Indicators.
 *
 * ITU Ref: sec 3.28, page 29. Figure 28/Q.763.
 *
 * ANSI Ref: sec 3.22 (Figure 20/T1.113.3), page T1.113.3-17.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indics[2];
}
ISUP_INFORMATION_INDICATORS;

/* Bits ED, I,J,K-O: spare */

/* Bits BA: Calling Party Addr response indicator */
#define INFOI_CGPA_ADDR_NOT_INCLD      0x00
#define INFOI_CGPA_ADDR_NOT_AVAIBL     0x01
#define INFOI_CGPA_SPARE               0x02
#define INFOI_CGPA_ADDR_INCLD          0x03

/* Bit C: Hold provided indicator */                                     
#define INFOI_HOLD_NOT_PROVIDED   0x00
#define INFOI_HOLD_PROVIDED       0x01

/* Bit F: Calling Party's Category indicator */
#define INFOI_CGPA_CAT_NOT_PROVIDED  0x00
#define INFOI_CGPA_CAT_PROVIDED      0x01

/* Bit G: Charge information response indicator */
#define INFOI_CHARGE_INFO_NOT_PROVIDED   0x00
#define INFOI_CHARGE_INFO_PROVIDED       0x01

/* Bit H: Solicited information indicator */
#define INFOI_SOLICITED   0x00
#define INFOI_UNSOLICITED 0x01
                                          

/*
 ****************************************************************************
 * Information Request Indicators.
 *
 * ITU Ref: sec 3.29, page 30. Figure 29/Q.763.
 *
 * ANSI Ref: sec 3.24C (Figure 22C/T1.113.3), page T1.113.3-19.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   indics[2];
}
ISUP_INFORMATION_REQUEST_INDICATORS;

/* Bit A: Calling Party Address indicator */
#define INFO_REQ_CGPA_NOT_REQUESTED 0x00
#define INFO_REQ_CGPA_REQUESTED     0x01

/* Bit B: Holding indicator */
#define INFO_REQ_HOLDING_NOT_REQUESTED  0x00                        
#define INFO_REQ_HOLDING_REQUESTED      0x01

/* Bit D: Calling Party's Category indicator */
#define INFO_REQ_CGPA_CAT_NOT_REQUESTED 0x00
#define INFO_REQ_CGPA_CAT_REQUESTED     0x01

/* Bit E: Charge Information Request indicator */
#define INFO_REQ_CHARGE_INFO_NOT_REQUESTED  0x00
#define INFO_REQ_CHARGE_INFO_REQUESTED      0x01

/* Bit H: Malicious Call Identification Request indicator */
#define INFO_REQ_MAL_CALL_ID_NOT_REQUESTED  0x00
#define INFO_REQ_MAL_CALL_ID_REQUESTED      0x01
                                                                         
/*
 ****************************************************************************
 * Nature Of Connection Indicators.
 *
 * ITU Ref: sec 3.35, page 35. Figure 36/Q.763.
 *
 * ANSI Ref: sec 3.24 (Figure 22/T1.113.3), page T1.113.3-18.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   subfields4;
}
ISUP_CONNECTION_INDICATORS;

#define NCI_SPARE               0x03

/* Bits B & A: Satellite Indicator. */
#define NCI_NO_SATELLITE_CKT    0x00
#define NCI_ONE_SATELLITE_CKT   0x01
#define NCI_TWO_SATELLITE_CKT   0x02                                      

/* Bits D & C: Continuity Check Indicator. */
#define NCI_CHECK_NOT_REQUIRED  0x00
#define NCI_CHECK_CKT_REQUIRED  0x01
#define NCI_CHECKED_PREV_CKT    0x02


/* Bit E: Echo Control Device Indicator. */
#define NCI_DEVICE_NOT_INCL         0x0
#define NCI_DEVICE_INCL             0x1

/* Bits F-H: spares. */


/*
 ****************************************************************************
 *  Optional Backward Call Indicators.
 *
 * ITU Ref: sec 3.37, page 37. Figure 38/Q.763.                        
 *
 * ANSI Ref: sec 3.24C (Figure 22C/T1.113.3), page T1.113.3-19.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   obkwd_ind;
}
ISUP_OPT_BKWD_CALL_INDICATORS;

/* Bit A: In-band Information Indicator */
#define OBKWD_NO_IN_BAND_INDICATION 0x00
#define OBKWD_IN_BAND_INFO_AVAIBL   0x01

/* Bit C: Simple Segmentation Indicator */
#define OBWD_NO_ADDITNL_INFO_SENT   0x00
#define OBWD_ADDITNL_INFO_SENT      0x04

/* The input 'x should be of type (OptBackwardCallInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_OBKWD_IND_A_BIT(x,y)        /* FIXME */

/* The input 'x should be of type (OptBackwardCallInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_OBKWD_IND_B_BIT(x,y)        /* FIXME */

/* The input 'x should be of type (OptBackwardCallInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_OBKWD_IND_C_BIT(x,y)        /* FIXME */

/* The input 'x should be of type (OptBackwardCallInd *) */
/* 'y' should be one of the 2 #defines given above. */
#define SET_OBKWD_IND_D_BIT(x,y)        /* FIXME */                

/*
 ****************************************************************************
 * Original Called number.
 *
 * ITU Ref: sec 3.39, page 38. Figure 40/Q.763.
 *
 * ANSI Ref: sec 3.26 (Figure 23A/T1.113.3), page T1.113.3-19.
 *
 * NOTE: See Calling Party Number.
 *       Bit 8 of subfields4 is spare. Bits 21 of subfields4 are
 *       reserved (ANSI) or spare (ITU).
 ****************************************************************************/
typedef ISUP_CALLING_PARTY_NUM ISUP_ORIG_CALLED_NUM;


/*
 ****************************************************************************
 *  Range and Status.
 *
 * ITU Ref: sec 3.43, page 40. Figure 43/Q.763.
                                                                               
 *
 * ANSI Ref: sec 3.27 (Figure 24/T1.113.3), page T1.113.3-20.
 *
 * Range is a number from 1 to 255 (CCITT) or from 0 to 23/31 (ANSI)
 * indicating how many circuits are affected.  Status is a bitmap containing
 * information for each circuit in the group.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   range;
    ITS_OCTET   status[32];
}
ISUP_RANGE_AND_STATUS;

/* For CCITT */
#define STATUS_NO_INDICATION    0

/* For CGB: a status of 0 is no blocking, a status of 1 is blocking. */
#define STATUS_NO_BLOCKING  0
#define STATUS_BLOCKING     1                                                 

/*
 * For CGBA:
 * a status of 0 is no blocking ACK, a status of 1 is blocking ACK.
 */
#define STATUS_NO_BLOCKING_ACK  0
#define STATUS_BLOCKING_ACK     1

/* For CGU: a status of 0 is no unblocking, a status of 1 is unblocking. */
#define STATUS_NO_UNBLOCKING  0
#define STATUS_UNBLOCKING     1

/*
 * For CGUA:
 * a status of 0 is no unblocking ACK, a status of 1 is unblocking ACK.
 */
#define STATUS_NO_UNBLOCKING_ACK  0
#define STATUS_UNBLOCKING_ACK     1

/* For GRA: a status of 0 is not blocked, a status of 1 is blocked. */
#define STATUS_NOT_BLOCKED  0
#define STATUS_BLOCKED      1                                                  


#define SET_RAS_STATUS(x,b,v)    ((x)->status[(b)/8] &= ~(1 << (1-((b) % 8))), \
                                  (x)->status[(b)/8] |= ((v) << (1-((b) % 8))))


/*
 ****************************************************************************
 * Redirecting Number.
 *
 * ITU Ref: sec 3.44, page 42. Figure 40/Q.763.
 *
 * ANSI Ref: sec 3.27A (Figure 25/T1.113.3), page T1.113.3-21.
 *
 * Note: see Original Called Number.
 ****************************************************************************/
typedef ISUP_ORIG_CALLED_NUM ISUP_REDIRECTING_NUM;

                                                                               
/*
 ****************************************************************************
 * Redirection Information.
 *
 * ITU Ref: sec 3.45, page 42. Figure 4/Q.763.
 *
 * ANSI Ref: sec 3.29 (Figure 25A/T1.113.3), page T1.113.3-21.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   red_info[2];
}
ISUP_REDIRECTION_INFO;

/* Bits C-A: Redirecting Indicator (No procedure specified for US Networks */
#define RINFO_NO_REDIRECT                       0x00
#define RINFO_CALL_REROUT                       0x01
#define RINFO_CALL_REROUT_ALL_INFO_RESTRICT     0x02
#define RINFO_CALL_DIVERSN                      0x03
#define RINFO_CALL_DIVERSN_ALL_INFO_RESTRICT    0x04
#define RINFO_CALL_REROUT_NUM_RESTRICT          0x05
#define RINFO_CALL_DIVERSN_NUM_RESTRICT         0x06
#define RINFO_SPARE                             0x07                           

/* Bit D: spare */

/* Bits H-E: Original Redirection Reasons. */
#define RINFO_UNKNOWN_NOT_AVAIL       0x00
#define RINFO_USER_BUSY               0x01
#define RINFO_NO_REPLY                0x02
#define RINFO_UNCONDITIONAL           0x03

/* Bits K-I: Redirection Counter. */

/* Bit L: Spare. */

/* Bits P-M: Redirecting Reason. */
/* Same as for Original Redirection Reason (Bits H-E) + following for ITU */


                                                                              
/*
 ****************************************************************************
 * Service Activation.
 *
 * ITU Ref: sec 3.49, page 54. Figure 49/Q.763.
 *
 * ANSI Ref: sec 3.29B (Figure 25C/T1.113.3), page T1.113.3-21.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET data[128];

}
ISUP_SERVICE_ACTIVATION;
                                                                       

/*
 ****************************************************************************
 * Suspend/Resume Indicators.
 *
 * ITU Ref: sec 3.52, page 55. Figure 52/Q.763.
 *
 * ANSI Ref: sec 3.31A (Figure 27A/T1.113.3), page T1.113.3-22.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   sus_res;
}
ISUP_SUSPEND_RESUME_INDICATORS;

/* The 'sus_res' octet can take one of the following values. */
#define SUS_RES_ISDN_SUBS_INIT  0x00
#define SUS_RES_NTWK_INIT       0x01
                                                                              

/*
 ****************************************************************************
 * Transit Network Selection.
 *
 * ITU Ref: sec 3.53, page 56. Figure 53/Q.763.
 *
 * ANSI Ref: sec 3.31C (Figure 27C 27D/T1.113.3), page T1.113.3-22.
 ****************************************************************************/
typedef struct
{
    ITS_OCTET   network;
#if defined CCITT
    ITS_OCTET   network_id[127];
#endif
#ifdef ANSI
    ITS_OCTET   digit2and1;
    ITS_OCTET   digit4and3;
    ITS_OCTET   code;
#endif
}
ISUP_TRANSIT_NETWORK_SELECTION;                                             

/*
 ****************************************************************************
 * Remote Operations
 *
 * ITU Ref: sec 3.48, page 44. Figure 46/Q.763.
 * ANSI Ref: T1.113
 *************************************************************************/
typedef struct
{
        ITS_OCTET   protocol_profile;
        ITS_OCTET   components[128];
}
ISUP_REMOTE_OPERATIONS;

#define TNS_UNKNOWN     0x00

/* Type of network id, network id plan */
#define TNS_CCITT_ID    0x01
#define TNS_NATNL_ID    0x02

/* network id plan for CCITT net id, if ntl (check carrier id for ANSI) */
#define TNS_DNIC        0x03
#define TNS_MNIC        0x06
/* other values: reserved */
                                                                           

/*
 * User Service Information.
 * Ref: sec 3.57, page 57-58. Figure 55/Q.763.
 * Defined as "ISUP_USER_SERVICE_INFO" above.
 * The format of this parameter is the same as the Bearer Capability
 * Information Element from Recommendation Q.931 and not all
 * capabilities coded are supported at this time.
 * The codes to be used in the subfields of the User Service
 * Information parameter field are defined in the Bearer Capability
 * Information Element in Recommendation Q.931.
 * NOTE: Octet 'config' is omitted if default values apply to all subfields
 * of octets 'config' and 'symmetry'. Octet 'symmetry' is omitted if default
 * values apply to all its subfields. Octets 'layer1'. 'layer2', 'layer3',
 * or any combination of these octets may be omitted. Octet 'layer1' may be
 * extended as described in Table 4-6/Q.931.
 */

typedef struct
{
    ITS_OCTET   coding;
    ITS_OCTET   trans_mode;
    ITS_OCTET   config;                                                        
    ITS_OCTET   symmetry;
#if defined ANSI
    ITS_OCTET   rate_multiplier;
#endif
    ITS_OCTET   layer1;
    ITS_OCTET   layer1_ext_user_rate;
    ITS_OCTET   layer1_ext_rate_adaption_3b;
    ITS_OCTET   layer1_ext_parity;
    ITS_OCTET   layer1_ext_modem_type;
    ITS_OCTET   layer2;
    ITS_OCTET   layer3;
}
ISUP_USER_SERVICE_INFO;


/*
 * OCTET 1: Coding Standard (bits 7,6)
 * and Information transfer capability (bits 5->1)
 */
#define USI_CCITT_CODING    0x00
#define USI_NATIONAL        0x02                                    

/*
 * OCTET 1: Coding Standard (bits 7,6)
 * and Information transfer capability (bits 5->1)
 */
#define USI_CCITT_CODING    0x00
#define USI_NATIONAL        0x02

#define USI_SPEECH          0x00
#define USI_DIGITAL_N_RES   0x08
#define USI_DIGITAL_W_RES   0x09
#define USI_AUDIO_3_1KHZ    0x10                                      
/*
 * OCTET 2: Transfer mode (bits 7,6)
 * and Information transfer rate (bits 5->1)
 */
#define USI_CIRCUIT_MODE        0x00
#define USI_PACKET_MODE         0x01

#define USI_R_64_KBITPS         0x10
#define USI_R_384_KBITPS        0x13
#define USI_R_1472_KBITPS       0x14
#define USI_R_1536_KBITPS       0x15
#define USI_USI_R_1920_KBITPS   0x17
#define USI_R_MULTI_RATE        0x18

/*
 * OCTET 2A: Structure (bits 7->5)
 * Configuration (bits 4,3), and Establishment (bits 2,1)
 */
#define USI_DEFAULT         0x0
#define USI_INTEGRITY_8KHZ  0x01
#define USI_SERVICE_DATA    0x4
#define USI_UNSTRUCTURED    0x7                                              

#define USI_POINT_TO_POINT  0x00

#define USI_DEMAND          0x00

/*
 * OCTET 2B: Symmetry (bits 7,6)
 * and Information transfer rate (bits 5->1) same as for octet 2.
 */
#define USI_BI_DIRECTIONAL_SYM  0x00

/* OCTET 2.1 (ANSI): 0->1 and 31 -> 127 reserved. */

/* OCTET 3: User information layer 1 protocol (bits 5->1). */
#define USI_CCITT_V110_X30      0x01
#define USI_CCITT_G711_ULAW     0x02
#define USI_NON_CCITT           0x07
#define USI_CCITT_V120          0x08
#define USI_CCITT_X31_HDLC      0x09                                        

/*
 * OCTET 3A: synch/asynch (bit 7), negotiation (bit 6)
 * User rate (bits 5-> 1).
 */
#define USI_SYNCHRONOUS     0x0
#define USI_ASYNCHRONOUS    0x1

#define USI_NEG_NOT_POSSIBLE    0x0
#define USI_NEG_POSSIBLE        0x1

#define USI_R_E_BITS            0x00
#define USI_R_600BITS_V6_X1     0x01
#define USI_R_1200BITS_V6       0x02
#define USI_R_2400BITS_V6_X1    0x03
#define USI_R_3600BITS_V6       0x04
#define USI_R_4800BITS_V6_X1    0x05
#define USI_R_9600BITS_V6_X1    0x08
#define USI_R_14400BITS_V6      0x09
#define USI_R_16KBITS_I460      0x0A
#define USI_R_19200BITS_V6      0x0B                                           
#define USI_R_32KBITS_I460      0x0C
#define USI_R_48KBITS_V6_X1     0x0E
#define USI_R_56KBITS_V6        0x0F
#define USI_R_134BITS_X1        0x15
#define USI_R_100BITS_X1        0x16
#define USI_R_75_1200BITS_V6_X1 0x17
#define USI_R_1200_75BITS_V6_X1 0x18
#define USI_R_50BITS_V6_X1      0x19
#define USI_R_75BITS_V6_X1      0x1A
#define USI_R_110BITS_V6_X1     0x1B
#define USI_R_150BITS_V6_X1     0x1C
#define USI_R_200BITS_V6_X1     0x1D
#define USI_R_300BITS_V6_X1     0x1E
#define USI_R_12KBITS_V6        0x1F                                   

/*
 * OCTET 3B V.110: Intermediate rate(bits 7,6). if bits are not specified
 * then they are either included/required/accept (0x1) or not (0x0).
 */
#define USI_R_NOT_USED  0x00
#define USI_R_8KBITS    0x01
#define USI_R_16KBITS   0x02
#define USI_R_32KBITS   0x03

/*
 * OCTET 3B V.120: Intermediate rate(bits 7,6). if bits are not specified
 * then they are either included/required/accept (0x1) or not (0x0).
 */
#define USI_LLI_256         0x00
#define USI_LLI_NEGOTIATION 0x01

#define USI_BIT_TRANSPARENT_MODE    0x00
#define USI_PROTOCOL_SENSITIVE_MODE 0x01                               

#define USI_DEFAULT_ASSIGNEE    0x00
#define USI_ASSIGNOR_ONLY       0x01
                                                             
#define USI_NEGOTIATION_W_IN_BAND       0x01

/*
 * OCTET 3C: stop bits, number of data bits (without parity bits),
 * parity information
 */
#define USI_NB_STOP_BITS_NOT_USED   0x00
#define USI_NB_STOP_BITS_1          0x01
#define USI_NB_STOP_BITS_1_HALF     0x02
#define USI_NB_STOP_BITS_2          0x03

#define USI_NB_DATA_BITS_NOT_USED   0x00
#define USI_NB_DATA_BITS_5          0x01
#define USI_NB_DATA_BITS_7          0x02
#define USI_NB_DATA_BITS_8          0x03                                       

#define USI_UINFO_PARITY_ODD    0x00
#define USI_UINFO_PARITY_EVEN   0x02
#define USI_UINFO_PARITY_NONE   0x03
#define USI_PARITY_FORCED_0     0x04
#define USI_PARITY_FORCED_1     0x05

/* OCTET 3D: Duplex mode and modem type (network specific for ANSI) */

#define USI_HALF_DUPLEX 0x00
#define USI_FULL_DUPLEX 0x01

/* OCTET 4: User information layer 2 protocol.*/
#define USI_REC_Q921_I441       0x02
#define USI_REC_X25_LINK_LAYER  0x06

/* OCTET 4: User information layer 3 protocol.*/                            
#define USI_REC_X25_PACKET_LAYER    0x6

/*
 * Generic Notification Indicator
 * Ref: sec 3.25
 */
typedef struct
{
    ITS_OCTET indicators[1];
}
ISUP_GENERIC_NOTIFICATION_INDICATOR;


/*
 * array of name/indicator pairs
 */
#define SET_PC_INSTRUCTION_NAME(x,n,v) \
       ((x)->data[(n)<<1] = (v))

#define SET_PC_TRANSIT_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0xFEU, \
        (x)->data[((n)<<1)+1] |= ((v) & 0x01U))                        
#define PC_TRANSIT_INTERP  0x0
#define PC_END_NODE_INTERP 0x1

#define SET_PC_RELEASE_CALL_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0xFDU, \
        (x)->data[((n)<<1)+1] |= (((v)<<1) & 0x02U))
#define PC_DO_NOT_RELEASE  0x0
#define PC_RELEASE         0x1

#define SET_PC_NOTIFY_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0xFBU, \
        (x)->data[((n)<<1)+1] |= (((v)<<2) & 0x04U))
#define PC_DO_NOT_NOTIFY  0x0
#define PC_NOTIFY         0x1

#define SET_PC_DISCARD_MSG_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0xF7U, \
        (x)->data[((n)<<1)+1] |= (((v)<<3) & 0x08U))
#define PC_DO_NOT_DISCARD  0x0
#define PC_DISCARD         0x1                                         

#define SET_PC_DISCARD_PARM_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0xEFU, \
        (x)->data[((n)<<1)+1] |= (((v)<<4) & 0x10U))

#define SET_PC_CONTINUE_IND(x,n,v) \
       ((x)->data[((n)<<1)+1] &= 0x7FU, \
        (x)->data[((n)<<1)+1] |= (((v)<<7) & 0x80U))
#define PC_MORE_ITS_OCTETS  0x0
#define PC_LAST_ITS_OCTET   0x1


/* Populating MTP3 Header */
#define ISUP_SET_MTP3_HEADER(hdr, sio, opc, dpc, sls) \
         MTP3_HDR_SET_SIO(hdr, (ITS_OCTET)sio); \
         MTP3_RL_SET_OPC_VALUE(hdr.label, opc); \
         MTP3_RL_SET_DPC_VALUE(hdr.label, dpc); \
         MTP3_RL_SET_SLS(hdr.label, sls);


#define ISUP_GET_MSG_TYPE(ev) ev->data[0]

#define ISUP_EV_VCIC_INDEX  sizeof(ITS_OCTET)

#define ISUP_EV_CIC_INDEX   (EV_VCIC_INDEX + sizeof(ITS_CTXT))

#define ISUP_GET_VCIC(ev) ITS_GET_CTXT(&ev->data[EV_VCIC_INDEX])

#define ISUP_GET_CIC(ev) \
        (ev->data[EV_CIC_INDEX] & 0x00FF ) | \
        ((ev->data[EV_CIC_INDEX + 1] << 8) & 0xFF00)

/*********************************************************************************
 * From here forward appear definitions specific to the IntelliNet implementation
 * of ISUP.
 *********************************************************************************/

/*
 * ISUP Timer IDs.
 */
#define ITS_ISUP_TIMER_T1    1       /* First RLC timer              */
#define ITS_ISUP_TIMER_T2    2       /* Suspend timer                */
#define ITS_ISUP_TIMER_T3    3       /* Unused                       */
#define ITS_ISUP_TIMER_T4    4       /* Unused                       */
#define ITS_ISUP_TIMER_T5    5       /* Second RLC timer             */
#define ITS_ISUP_TIMER_T6    6       /* RES timer (network)          */
#define ITS_ISUP_TIMER_T7    7       /* ACM timer                    */
#define ITS_ISUP_TIMER_T8    8       /* COT timer                    */
#define ITS_ISUP_TIMER_T9    9       /* ANM timer                    */
#define ITS_ISUP_TIMER_T10   10      /* Unused                       */
#define ITS_ISUP_TIMER_T11   11      /* Unused                       */
#define ITS_ISUP_TIMER_T12   12      /* First BLA timer              */
#define ITS_ISUP_TIMER_T13   13      /* Second BLA timer             */
#define ITS_ISUP_TIMER_T14   14      /* First UBA timer              */
#define ITS_ISUP_TIMER_T15   15      /* Second UBA timer             */
#define ITS_ISUP_TIMER_T16   16      /* First RSC response timer     */
#define ITS_ISUP_TIMER_T17   17      /* Second RSC response timer    */
#define ITS_ISUP_TIMER_T18   18      /* First CGBA timer             */
#define ITS_ISUP_TIMER_T19   19      /* Second CGBA timer            */         
#define ITS_ISUP_TIMER_T20   20      /* First CGUA timer             */
#define ITS_ISUP_TIMER_T21   21      /* Second CGUA timer            */
#define ITS_ISUP_TIMER_T22   22      /* First GRA timer              */
#define ITS_ISUP_TIMER_T23   23      /* Second GRA timer             */
#define ITS_ISUP_TIMER_T24   24      /* Continuity toner timer       */
#define ITS_ISUP_TIMER_T25   25      /* CCR timing timer             */
#define ITS_ISUP_TIMER_T26   26      /* CCR response timer           */
#define ITS_ISUP_TIMER_T27   27      /* CCR receive timer            */
#define ITS_ISUP_TIMER_T28   28      /* CQR timer                    */
#define ITS_ISUP_TIMER_T29   29      /* First congestion             */
#define ITS_ISUP_TIMER_T30   30      /* First congestion indication  */
#define ITS_ISUP_TIMER_T31   31      /* Unused                       */
#define ITS_ISUP_TIMER_T32   32      /* Unused                       */
#define ITS_ISUP_TIMER_T33   33      /* Unused                       */
#define ITS_ISUP_TIMER_T34   34      /* Circuit query timer          */
#define ITS_ISUP_TIMER_T35   35      /*              */
#define ITS_ISUP_TIMER_T36   36      /*              */
#define ITS_ISUP_TIMER_T37   37      /*              */

#define ITS_ISUP_TIMER_LAST     52   /* LAST TIMER ID */

SS7DLLAPI ITS_OCTET     ISUP_StringToTimer(const char *tmr);
SS7DLLAPI const char *  ISUP_TimerToString(ITS_OCTET tmr_id);

/*
 * Variant enumerations.
 */
typedef enum
{
    ISUP_ANSI_MIN,

    ISUP_ANSI_BELL,
    ISUP_ANSI_BELLCORE_96,
    ISUP_ANSI_ERICSSON,
    ISUP_ANSI_GENERIC_88,
    ISUP_ANSI_GENERIC_92,

    ISUP_ANSI_95,    
    ISUP_ANSI_JAMAICA,
    ISUP_ANSI_MCI,
    ISUP_ANSI_PUERTO_RICO,
    
    ISUP_ANSI_MAX,

    ISUP_ITU_MIN,

    ISUP_ITU_GENERIC_88 = 25,
    ISUP_ITU_GENERIC_93,
    ISUP_ITU_97,
    ISUP_ITU_ARGENTINA,
    ISUP_ITU_AUSTRALIA_NIIF_97,
    
    ISUP_ITU_AUSTRALIA_OPTUS_AUG_94,
    ISUP_ITU_BRAZIL,
    ISUP_ITU_BELGIUM,
    ISUP_ITU_BRUNEI,
    ISUP_ITU_CHILE,
    
    ISUP_ITU_CHINA24,
    ISUP_ITU_COLUMBIA,
    ISUP_ITU_CZECH_SLOVAK,
    ISUP_ITU_ERICSSON_BB_CME20R5,
    ISUP_ITU_ERICSSON_PBMS,
    
    ISUP_ITU_ERICSSON_REL3_SWEDEN,
    ISUP_ITU_ERICSSON_WB_CME20R6,
    ISUP_ITU_ETSI_V1_92,
    ISUP_ITU_ETSI_V2_95,
    ISUP_ITU_ETSI_V3_98,
    
    ISUP_ITU_FINLAND,
    ISUP_ITU_FRANCE_SPIROU,
    ISUP_ITU_FRANCE_SSUTR2,
    ISUP_ITU_FRANCE_SSUR,
    ISUP_ITU_FRANCE_TS_ED2,
    
    ISUP_ITU_GERMANY,
    ISUP_ITU_GREECE,
    ISUP_ITU_HONGKONG,
    ISUP_ITU_HUNGARY_NETCOM_CCS_0421,
    ISUP_ITU_INDIA_V1,
    
    ISUP_ITU_INDIA_V2,
    ISUP_ITU_INDONESIA,
    ISUP_ITU_IRELAND,
    ISUP_ITU_ISRAEL_PELEPHONE,
    ISUP_ITU_ITALY_OMNITEL_VMS,
    
    ISUP_ITU_ITALY_SIP_NOKIA,
    ISUP_ITU_JAPAN_CTM,
    ISUP_ITU_JAPAN_NTT,
    ISUP_ITU_JAPAN_TTC2,
    ISUP_ITU_JAPAN_TTC3,
    
    ISUP_ITU_KOREA,
    ISUP_ITU_MALAYSIA,
    ISUP_ITU_MEXICO,
    ISUP_ITU_NETHERLANDS,
    ISUP_ITU_NEWZEALAND,
    
    ISUP_ITU_NORWAY,
    ISUP_ITU_PERU_ARGEN_CHILE,
    ISUP_ITU_PHILIPPINES,
    ISUP_ITU_POLAND,
    ISUP_ITU_PORTUGAL_LUXEM_SEIMENS_EWSD,
    
    ISUP_ITU_Q767,
    ISUP_ITU_RUSSIA,
    ISUP_ITU_SINGAPORE,
    ISUP_ITU_SOUTH_AFRICA_TELKOM_ISSUE4,
    ISUP_ITU_SPAIN_EG_S3_C03,
    
    ISUP_ITU_SWITZERLAND,
    ISUP_ITU_SWEDEN_V1_8211_A335,
    ISUP_ITU_SWEDEN_V2_TELIA,
    ISUP_ITU_TAIWAN,
    ISUP_ITU_THAILAND_AIS_17_ANT,
    
    ISUP_ITU_THAILAND_TOT_93,
    ISUP_ITU_TURKEY,
    ISUP_ITU_UAE,
    ISUP_ITU_VENEZUELA,
    ISUP_ITU_VIETNAM,
 
    ISUP_ITU_MAX,

    ISUP_UNKNOWN
}
ISUP_VAR_TYPE;

/*
 * variant class names.  Use these as the classRec/feature name in the configuration.
 */
#define ISUP_ANSI_BELL_STRING                       "ANSI_BELL"
#define ISUP_ANSI_BELLCORE_96_STRING                "ANSI_BELLCORE_96"
#define ISUP_ANSI_ERICSSON_STRING                   "ANSI_ERICSSON"
#define ISUP_ANSI_GENERIC_88_STRING                 "ANSI_GENERIC_88"
#define ISUP_ANSI_GENERIC_92_STRING                 "ANSI_GENERIC_92"
#define ISUP_ANSI_95_STRING                         "ANSI_ISUP_95"
#define ISUP_ANSI_JAMAICA_STRING                    "ANSI_JAMAICA"
#define ISUP_ANSI_MCI_STRING                        "ANSI_MCI"
#define ISUP_ANSI_PUERTO_RICO_STRING                "ANSI_PUERTO_RICO"
#define ISUP_ITU_GENERIC_88_STRING                  "ITU_GENERIC_88"
#define ISUP_ITU_GENERIC_93_STRING                  "ITU_GENERIC_93"
#define ISUP_ITU_GENERIC_97_STRING                  "ITU_ISUP_97"
#define ISUP_ITU_ARGENTINA_STRING                   "ITU_ARGENTINA"
#define ISUP_ITU_AUSTRALIA_NIIF_97_STRING           "ITU_AUSTRALIA_NIIF_97"
#define ISUP_ITU_AUSTRALIA_OPTUS_AUG_94_STRING      "ITU_AUSTRALIA_OPTUS_AUG_94"
#define ISUP_ITU_BRAZIL_STRING                      "ITU_BRAZIL"
#define ISUP_ITU_BELGIUM_STRING                     "ITU_BELGIUM"
#define ISUP_ITU_BRUNEI_STRING                      "ITU_BRUNEI"
#define ISUP_ITU_CHILE_STRING                       "ITU_CHILE"
#define ISUP_ITU_CHINA24_STRING                     "ITU_CHINA24"
#define ISUP_ITU_COLUMBIA_STRING                    "ITU_COLUMBIA"
#define ISUP_ITU_CZECH_SLOVAK_STRING                "ITU_CZECH_SLOVAK"
#define ISUP_ITU_ERICSSON_BB_CME20R5_STRING         "ITU_ERICSSON_BB_CME20R5"
#define ISUP_ITU_ERICSSON_PBMS_STRING               "ITU_ERICSSON_PBMS"
#define ISUP_ITU_ERICSSON_REL3_SWEDEN_STRING        "ITU_ERICSSON_REL3_SWEDEN"
#define ISUP_ITU_ERICSSON_WB_CME20R6_STRING         "ITU_ERICSSON_WB_CME20R6"
#define ISUP_ITU_ETSI_V1_92_STRING                  "ITU_ETSI_V1_92"
#define ISUP_ITU_ETSI_V2_95_STRING                  "ITU_ETSI_V2_95"
#define ISUP_ITU_ETSI_V3_98_STRING                  "ITU_ETSI_V3_98"
#define ISUP_ITU_FINLAND_STRING                     "ITU_FINLAND"
#define ISUP_ITU_FRANCE_SPIROU_STRING               "ITU_FRANCE_SPIROU"
#define ISUP_ITU_FRANCE_SSUTR2_STRING               "ITU_FRANCE_SSUTR2"
#define ISUP_ITU_FRANCE_SSUR_STRING                 "ITU_SSUR"
#define ISUP_ITU_FRANCE_TS_ED2_STRING               "ITU_FRANCE_TS_ED2"
#define ISUP_ITU_GERMANY_STRING                     "ITU_GERMANY"
#define ISUP_ITU_GREECE_STRING                      "ITU_GREECE"
#define ISUP_ITU_HONGKONG_STRING                    "ITU_HONGKONG"
#define ISUP_ITU_HUNGARY_NETCOM_CCS_0421_STRING     "ITU_HUNGARY_NETCOM_CCS_0421"
#define ISUP_ITU_INDIA_V1_STRING                    "ITU_INDIA_V1"
#define ISUP_ITU_INDIA_V2_STRING                    "ITU_INDIA_V2"
#define ISUP_ITU_INDONESIA_STRING                   "ITU_INDONESIA"
#define ISUP_ITU_IRELAND_STRING                     "ITU_IRELAND"
#define ISUP_ITU_ISRAEL_PELEPHONE_STRING            "ITU_ISRAEL_PELEPHONE"
#define ISUP_ITU_ITALY_OMNITEL_VMS_STRING           "ITU_ITALY_OMNITEL_VMS"
#define ISUP_ITU_ITALY_SIP_NOKIA_STRING             "ITU_ITALY_SIP_NOKIA"
#define ISUP_ITU_JAPAN_CTM_STRING                   "ITU_JAPAN_CTM"
#define ISUP_ITU_JAPAN_NTT_STRING                   "ITU_JAPAN_NIT"
#define ISUP_ITU_JAPAN_TTC2_STRING                  "ITU_JAPAN_TTC2"
#define ISUP_ITU_JAPAN_TTC3_STRING                  "ITU_JAPAN_TTC3"
#define ISUP_ITU_KOREA_STRING                       "ITU_KOREA"
#define ISUP_ITU_MALAYSIA_STRING                    "ITU_MALAYSIA"
#define ISUP_ITU_MEXICO_STRING                      "ITU_MEXICO"
#define ISUP_ITU_NETHERLANDS_STRING                 "ITU_NETHERLANDS"
#define ISUP_ITU_NEWZEALAND_STRING                  "ITU_NEWZEALAND"
#define ISUP_ITU_NORWAY_STRING                      "ITU_NORWAY"
#define ISUP_ITU_PERU_ARGEN_CHILE_STRING            "ITU_PERU_ARGEN_CHILE"
#define ISUP_ITU_PHILIPPINES_STRING                 "ITU_PHILIPPINES"
#define ISUP_ITU_POLAND_STRING                      "ITU_POLAND"
#define ISUP_ITU_PORTUGAL_LUXEM_SEIMENS_EWSD_STRING "ITU_PORTUGAL_LUXEM_SIEMENS_EWSD"
#define ISUP_ITU_Q767_STRING                        "ITU_Q767"
#define ISUP_ITU_RUSSIA_STRING                      "ITU_RUSSIA"
#define ISUP_ITU_SINGAPORE_STRING                   "ITU_SINGAPORE"
#define ISUP_ITU_SOUTH_AFRICA_TELKOM_ISSUE4_STRING  "ITU_SOUTH_AFRICA_TELKOM_ISSUE4"
#define ISUP_ITU_SPAIN_EG_S3_C03_STRING             "ITU_SPAIN_EG_S3_C03"
#define ISUP_ITU_SWITZERLAND_STRING                 "ITU_SWITZERLAND"
#define ISUP_ITU_SWEDEN_V1_8211_A335_STRING         "ITU_SWEDEN_V1_8211_A335"
#define ISUP_ITU_SWEDEN_V2_TELIA_STRING             "ITU_SWEDEN_V2_TELIA"
#define ISUP_ITU_TAIWAN_STRING                      "ITU_TAIWAN"
#define ISUP_ITU_THAILAND_AIS_17_ANT_STRING         "ITU_THAILAND_AIS_17_ANT"
#define ISUP_ITU_THAILAND_TOT_93_STRING             "ITU_THAILAND_TOT_93"
#define ISUP_ITU_TURKEY_STRING                      "ITU_TURKEY"
#define ISUP_ITU_UAE_STRING                         "ITU_UAE"
#define ISUP_ITU_VENEZUELA_STRING                   "ITU_VENEZUELA"
#define ISUP_ITU_VIETNAM_STRING                     "ITU_VIETNAME"

/*
 * variant string functions
 */
SS7DLLAPI const char *  ISUP_VariantToString(ISUP_VAR_TYPE variant);
SS7DLLAPI ISUP_VAR_TYPE ISUP_StringToVariant(const char *variant);

SS7DLLAPI ITS_BOOLEAN ISUP_VariantIsANSI(ISUP_VAR_TYPE variant);
SS7DLLAPI ITS_BOOLEAN ISUP_VariantIsCCITT(ISUP_VAR_TYPE variant);

#define ISUP_VariantStringIsANSI(x) \
    ISUP_VariantIsANSI(ISUP_StringToVariant(x))
#define ISUP_VariantStringIsCCITT(x) \
    ISUP_VariantIsCCITT(ISUP_StringToVariant(x))

/*
 * each timer can be handled by app or stack
 */
typedef enum
{
    ISUP_TMR_HNDL_STACK,
    ISUP_TMR_HNDL_APP,
    ISUP_TMR_HNDL_INVALID
} 
ISUP_TMR_HNDL;

SS7DLLAPI ISUP_TMR_HNDL ISUP_StringToTimerHandler(const char *tmr_hndl);
SS7DLLAPI const char *  ISUP_TimerHandlerToString(ISUP_TMR_HNDL tmr_hndl);

#define ISUP_CKGP_CTRL_NONE     0x0
#define ISUP_CKGP_CTRL_EVEN     0x1
#define ISUP_CKGP_CTRL_ODD      0x2
#define ISUP_CKGP_CTRL_ALL      0x3
#define ISUP_CKGP_CTRL_DEF      0x4
#define ISUP_CKGP_CTRL_INV      0x5

SS7DLLAPI ITS_OCTET    ISUP_StringToCkgpCtrl(const char *ckgp_ctrl);
SS7DLLAPI const char *      ISUP_CkgpCtrlToString(ITS_OCTET ckgp_ctrl);

/*
 * Type of Local Exchange
 */
typedef enum
{
    ISUP_XCHANGE_TYPE_A,
    ISUP_XCHANGE_TYPE_B,

    ISUP_XCHANGE_TYPE_INV
}
ISUP_XCHANGE_TYPE;

SS7DLLAPI ISUP_XCHANGE_TYPE
ISUP_StringToXchangeType(const char *xchange_type);

SS7DLLAPI ITS_BOOLEAN
ISUP_StringToSegSupport(const char *seg_supported);

/*
 * Information about a timer.
 */
typedef struct _timerInfo
{
    ITS_OCTET     timerId;  /* One of the ISUP timer IDs as per specs. */
    ITS_OCTET     sio;      /* SIO for this network */
    ITS_USHORT    cic;
    ITS_UINT      opc;      /* Point Code of this node and */
    ITS_UINT      dpc;      /* point code of remote node for the 'cic' */
}
ISUP_TIMER_ENTRY; 

/*
 * Information about an error in the stack. May need to send more data.
 */
typedef struct _errorInfo
{
    ITS_UINT      errorId;  /* Error IDs defined for IntelliNet's ISUP stack */
    ITS_OCTET     msgType;  /* Message type */
    ITS_OCTET     sio;      /* SIO for this network */
    ITS_USHORT    cic;
    ITS_UINT      opc;      /* Point Code of this node and */
    ITS_UINT      dpc;      /* point code of remote node for the 'cic' */
}
ISUP_ERROR_ENTRY; 

/*
 * Information about an  indication in the stack. May need to send more data.
 */
typedef struct _indicationInfo
{
    ITS_UINT      indId;  /* Error IDs defined for IntelliNet's ISUP stack */
    ITS_OCTET     sio;      /* SIO for this network */
    ITS_USHORT    cic;
    ITS_UINT      opc;      /* Point Code of this node and */
    ITS_UINT      dpc;      /* point code of remote node for the 'cic' */
}
ISUP_INDICATION_ENTRY;

/* Information about Congestion in the stack, Will be used to
 * to send the Congestion Control indication to the application
 */
typedef struct _congestionInfo
{
    ITS_UINT	congId;	    /* Congestion IDs for IntelliNet's ISUP stack */
    ITS_OCTET     sio;      /* SIO for this network */
    ITS_UINT      opc;      /* Point Code of this node and */
    ITS_UINT      dpc;      /* point code of remote node for the 'cic' */
}
ISUP_CONGESTION_ENTRY;

/*
 * Information about MTP3 Status, Pause/Resume indication to be sent
 * to the application
 */

typedef struct _mtp3mgmtInfo
{
    ITS_UINT    statId;
    ITS_OCTET     sio;      /* SIO for this network */
    ITS_UINT      opc;      /* Point Code of this node and */
    ITS_UINT      dpc;      /* point code of remote node for the 'cic' */
}
ISUP_MTP3MGMT_ENTRY;

/*
 * Types of data returned through ManagementCallbacks 
 */
#define ISUP_TIMER_DATA     1
#define ISUP_ERROR_DATA     2

/*
 * Error Identifiers from ISUP stack to application.
 * Generation of any of these errors will most likely lead to the msg and/or
 * the call to stop. 
 */
#define ITS_ISUP_REL_GLARE_ERR                                 1
#define ITS_ISUP_BAD_ADDR_ERR                                  2
#define ITS_ISUP_CIC_BUSY_ERR                                  3
#define ITS_ISUP_CIC_HWBLOCK_ERR                               4
#define ITS_ISUP_CIC_MNBLOCK_ERR                               5
#define ITS_ISUP_BAD_RNG_STATUS_ERR                            6
#define ITS_ISUP_BAD_CIC_ERR                                   7
#define ITS_ISUP_DEST_UNREACHABLE_ERR                          8
#define ITS_ISUP_REMOTE_UNAVAILABLE_ERR                        9
#define ITS_ISUP_UNEXP_APPMSG_IDLE_ERR                         10
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_ACM_ERR                  11
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_ANM_ERR                  12
#define ITS_ISUP_UNEXP_APPMSG_RCVDINC_ANM_ERR                  13
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_RLC_ERR                  14
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_RES_ERR                  15
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_COT_ERR                  16
#define ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_ERR           17

#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_ACM_ERR                  18
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_ANM_ERR                  19
#define ITS_ISUP_UNEXP_APPMSG_SENTOUT_ANM_ERR                  20
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_RES_ERR                  21
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_RLC_ERR                  22

#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_RSC_ERR                  23
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_REL_ERR                  24
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_GRA_ERR                  25

#define ITS_ISUP_UNEXP_APPMSG_WAITINC_CRA_ERR                  26
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_IAM_ERR                  27
#define ITS_ISUP_UNEXP_APPMSG_WAITOUT_IAM_ERR                  28
#define ITS_ISUP_UNEXP_APPMSG_WAITINC_COT_AND_IAM_ERR          29
#define ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_AND_CRA_ERR   30
#define ITS_ISUP_UNEXP_APPMSG_WAITFOR_COTREPORTS_HAVE_CRA_ERR  31
/* INDications to Application */

#define ITS_ISUP_RNS_MNSYS_IND         0x01
#define ITS_ISUP_CIC_REL_IND           0x02
#define ITS_ISUP_CIC_GRS_IND           0x03
#define ITS_ISUP_CIC_RSC_IND           0x04
#define ITS_ISUP_CALL_FAILURE_IND      0x05
#define ITS_ISUP_REL_REATTEMPT_IND     0x06 
#define ITS_ISUP_RSC_REATTEMPT_IND     0x07 
#define ITS_ISUP_START_RESET_IND       0x08 

#define ITS_ISUP_UCIC_MAINT_RQIND      0x09
#define ITS_ISUP_CGB_REATTEMPT_RQIND   0x0A
#define ITS_ISUP_CGB_RBLK_STIND        0x0B
#define ITS_ISUP_CGB_CPCIDLE_STIND     0x0C
#define ITS_ISUP_GRS_CPCIDLE_STIND     0x0D
#define ITS_ISUP_GRS_RUNBLK_STIND      0x0E
#define ITS_ISUP_GRS_REATTEMPT_RQIND   0x0F
#define ITS_ISUP_CGU_RUNBLK_STIND      0x10
#define ITS_ISUP_RSC_RUNBLK_STIND      0x11
#define ITS_ISUP_RSC_CPCIDLE_STIND     0x12
#define ITS_ISUP_RSC_REATTEMPT_RQIND   0x13
#define ITS_ISUP_UCIC_LBLOCK_STIND     0x14
#define ITS_ISUP_CFN_ALERT_IND         0x15
#define ITS_ISUP_IAM_REATTEMPT_IND     0x16 
#define ITS_ISUP_RMT_CONGLEVEL1_IND    0x17 
#define ITS_ISUP_RMT_CONGLEVEL2_IND    0x18 
#define ITS_ISUP_RMT_CONGLEVEL3_IND    0x19 
#define ITS_ISUP_RMT_NOCONG_IND        0x20 
#define ITS_ISUP_LOC_CONGLEVEL1_IND    0x21 
#define ITS_ISUP_LOC_CONGLEVEL2_IND    0x22 
#define ITS_ISUP_LOC_CONGLEVEL3_IND    0x23 
#define ITS_ISUP_LOC_NOCONG_IND        0x24 
#define ITS_ISUP_CQR_RELEASED_STIND    0x25
#define ITS_ISUP_RLC_RELEASE_IND       0x26
#define ITS_ISUP_RLC_RESET_IND         0x27
#define ITS_ISUP_CQR_RUNBLOCKED_STIND  0x28
#define ITS_ISUP_CQR_RBLOCKED_STIND    0x29
#define ITS_ISUP_CQR_LBLOCKED_STIND    0x30
#define ITS_ISUP_UCIC_REATTEMPT_RQIND  0x31
#define ITS_ISUP_UCIC_CPCIDLE_STIND    0x32
#define ITS_ISUP_CGB_RESETRETRY_RQIND  0x33

#define ITS_ISUP_UCIC_GRSDROPPED_IND   0x34
#define ITS_ISUP_SGM_WAIT_IND          0x35

/* CRM-CRA related Indications */
#define ITS_ISUP_REL_CRMRETRY_RQIND      0x36  
#define ITS_ISUP_RSC_CRMRETRY_RQIND      0x37
#define ITS_ISUP_CGB_CRMRETRY_RQIND      0x38
#define ITS_ISUP_GRS_CRMRETRY_RQIND      0x39 
#define ITS_ISUP_UCIC_CRMRETRY_RQIND     0x40
#define ITS_ISUP_FAILURE_CRMRETRY_RQIND  0x41 
#define ITS_ISUP_AUTOREL_CRMRETRY_RQIND  0x42  

#define ITS_ISUP_BAD_CIC_STIND           0x43
#define ITS_ISUP_CIC_COT_RELEASE_RQIND   0x44
#define ITS_ISUP_CIC_COT_RESET_RQIND     0x45
#define ITS_ISUP_CPG_CALLP_IND           0x46

#define ITS_ISUP_UBL_RUNBLOCK_IND        0xF1
#define ITS_ISUP_BLO_RBLOCK_IND          0xF2
#define ITS_ISUP_UBA_IND                 0xF3
#define ITS_ISUP_BLA_IND                 0xF4

#define ITS_ISUP_MTP3_PAUSE_IND          0xF5
#define ITS_ISUP_MTP3_RESUME_IND         0xF6
#define ITS_ISUP_REPEATRSC_FAILURE_IND   0xF7
#define ITS_ISUP_UPU_INACCESS_IND        0xF8
#define ITS_ISUP_UPU_UNEQUIPPED_IND      0xF9


#define ITS_ISUP_INV_CIC                 0xFFFF
#define ITS_ISUP_INV_VCIC                0x00

/*
 * variant records.
 */
#if !defined(DERIVED_CLASS)
extern VSS7DLLAPI ITS_Class               isupITU93_Class;
extern VSS7DLLAPI ITS_Class               isupANSI92_Class;
#else
extern SS7DLLAPI  ITS_Class               isupITU93_Class;
extern SS7DLLAPI  ITS_Class               isupANSI92_Class;
#endif

extern VSS7DLLAPI ITS_Class               isupCHINA_Class;
extern VSS7DLLAPI ITS_Class               isupITU97_Class;

extern VSS7DLLAPI ITS_Class               isupANSI95_Class;

#if defined(__cplusplus)
}
#endif

#endif /* _ITS_ISUP_CMN_H_ */
