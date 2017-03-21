/*********************************-*-C-*-************************************
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
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:54  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.4  2006/05/05 05:30:50  adutta
 * LOG: Large context makeup
 * LOG:
 * LOG: Revision 1.1.2.3  2005/12/21 19:51:51  adutta
 * LOG: Message definitions added
 * LOG:
 * LOG: Revision 1.1.2.2  2005/12/20 18:24:44  adutta
 * LOG: Added SCCP clear connection
 * LOG:
 * LOG: Revision 1.1.2.1  2005/12/20 12:10:13  adutta
 * LOG: Initial implementation
 * LOG:
 *
 * ID: $Id: bssapif_common.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $
 ****************************************************************************/
#ident "$Id: bssapif_common.h,v 1.1.1.1 2007-10-08 11:11:12 bsccs2 Exp $"

#ifndef BSSAPIF_COMMON_H
#define BSSAPIF_COMMON_H


#include <iostream>
#include <its++.h>
#include <its_thread_pool.h>
#include <engine++.h>

/* 
 *************************************************************************
 *
 * General format of the BSSAP messages exchanged through socket
 * 
 * <-- 1 byte -->  <---------- (n-1)---------------->
 * Message Header          Message Payload
 * 
 * 1. Format of SCCP request Messages
 * a. CC 
 * b. CREF
 * c. REL
 * Message Header + SCCP Message Discriminator (1byte) + CallReference (4bytes) 
 * 
 * 2. CIC Format
 * Message Header + BSC Id (1byte) + PCM (2bytes) + Start TS (1byte) + End TS (1byte) 
 *
 * 3. Configuration parameters (point codes/ssn)
 * Message Header + BSC Id (1byte) + LPC (4bytes) + RPC (4bytes) + LSSN (1byte) + RSSN (1byte)
 *
 * 4. BSSAP Messages
 * Message Header + BSC Id (1byte) + CallReference (4bytes) + Application ID (2bytes) + \
 *                + BSSAP Message Discriminator (1byte) + BSSAP MessageName (1byte) + BSSAP Message Length (1byte) \
 *                + BSSAP Message encoded data (10...n)
 *
 * 5. Timeout Indication to applicaiton
 * Message Header + Timer Message Discriminator (1byte) + TimerID (1byte)
 *
 * 6. BSSAP protocol error indication to application
 * Message Header + BSC Id (1byte) + CallReference (4bytes) + Application ID (2bytes) + \
 *                + Error Message Discriminator (1byte) + BSSAP Message Name (1byte) + Error Code (1byte) + \
 *                + (optionals) PCM (2bytes) + timeslot (1byte) 
 *
 * 7. SS7 Network status to application
 * Message Header + Message Discriminator (1byte) + SS7 Status Code (1byte)
 *
 * 8. SCCP indications messages to application
 *    a. CC
 *    b. CREF
 * Message Header + Message Discriminator (1byte) + CallReference (4bytes) + Application ID (2bytes) 
 *
 ***********************************************************************/



// Message Headers
#define CP_BSSAP_CIC_TAG          (0x01U) // CIC header
#define CP_BSSAP_CFG_TAG          (0x02U) // Configuration Header
#define CP_BSSAP_SCCP_TAG         (0x03U) // SCCP Message Header
#define CP_BSSAP_MSG_TAG          (0x04U) // BSSAP Message Header
#define CP_BSSAP_TIMEOUT_TAG      (0x05U) // Timeout Header
#define CP_BSSAP_NETWORK_TAG      (0x06U) // SS7 Network Header
#define CP_BSSAP_PROTOCOL_TAG     (0x07U) // BSSAP Protocol error Header
    

// BSSAP Message Discriminator
#define CP_BSSAP_MD_MAP          (0x00U)
#define CP_BSSAP_MD_DTAP         (0x01U)

// Timeout Message Discriminator
#define CP_MD_TIMEOUT            (0x02U)

// Error Message Discriminator
#define CP_BSSAP_MD_PROTOCOL        (0x04U)

// Errro code
#define CP_BSSAP_EENCODE            (0x01U)
#define CP_BSSAP_EDECODE            (0x02U)
#define CP_BSSAP_EINVMESSAGE        (0x03U)
#define CP_BSSAP_ECICNOTFOUND       (0x04U)
#define CP_BSSAP_ENORESETACK        (0x05U)
#define CP_BSSAP_ENOBLKACK          (0x06U)
#define CP_BSSAP_ENOUNBLKACK        (0x07U)
#define CP_BSSAP_ENORESETCKTACK     (0x08U)
#define CP_BSSAP_EUNEQUIPCKT        (0x09U)
#define CP_BSSAP_ENORELEASECMP      (0x0AU)
#define CP_DTAP_EENCODE             (0x0BU)
#define CP_BSSAP_ECKTPROC           (0x0CU)
#define CP_BSSAP_EASSREQFAIL        (0x0DU)
#define CP_BSSAP_ENOCKTGRPBLKACK    (0x0EU)
#define CP_BSSAP_ENOCKTGRPUNBLKACK  (0x0FU)
#define CP_BSSAP_EMSGSENTFAIL       (0x1FU)

// SS7 Network status Message Discriminator
#define CP_BSSAP_MD_NETWORK         (0x03U)

// SS7 status code
#define CP_MTP_RESUME            MTP3_MSG_RESUME
#define CP_MTP_PAUSE             MTP3_MSG_PAUSE
#define CP_MTP_STATUS            MTP3_MSG_STATUS
#define CP_SCCP_ALLOWED          SCCP_SCMG_SS_ALLOWED
#define CP_SCCP_PROHIBIT         SCCP_SCMG_SS_PROHIBIT
#define CP_SCCP_SST              SCCP_SCMG_SS_STATUS_TEST

// SCCP Message Discriminator (to network)
#define CP_SCCP_ACCEPT            (0x01U) // SCCP-CC
#define CP_SCCP_RELEASE           (0x02U) // SCCP-REL
#define CP_SCCP_REJECT            (0x03U) // SCCP-CREF

// SCCP Message Discriminator (from network)
#define CP_BSSAP_CON_ESTD           (0x01U) // SCCP-CC
#define CP_BSSAP_CON_REL            (0x02U) // SCCP-REL
#define CP_BSSAP_CON_REF            (0x03U) // SCCP-CREF



#endif

