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
 *  ID: $Id: bssap_common.h,v 1.4 2008/02/13 06:20:18 amaresh.prasad Exp $
 *
 * LOG: $Log: bssap_common.h,v $
 * LOG: Revision 1.4  2008/02/13 06:20:18  amaresh.prasad
 * LOG: Added SCCP Error message
 * LOG:
 * LOG: Revision 1.3  2008/01/18 04:20:19  bsccs2
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.2  2007/11/08 08:07:10  amaresh.prasad
 * LOG: Updated for Handover
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/08 11:11:13  bsccs2
 * LOG: Init Code
 * LOG:
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.2  2007/09/27 06:31:19  amaresh.prasad
 * LOG: Updated SCCP value
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:38  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.4  2007/08/01 11:33:25  amaresh.prasad
 * LOG: Updated for sms data len
 * LOG:
 * LOG: Revision 1.3  2007/07/30 12:04:13  amaresh.prasad
 * LOG: Updated for SMS
 * LOG:
 * LOG: Revision 1.2  2007/07/26 11:43:00  amaresh.prasad
 * LOG: Updated BSSAP DATA len
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.11  2006/02/21 06:15:16  yranade
 * LOG: Fix for issue ID: 3273
 * LOG:
 * LOG: Revision 1.1.2.10  2005/11/24 04:44:35  adutta
 * LOG: Incorporated IMR review changes *.h
 * LOG:
 * LOG: Revision 1.1.2.9  2005/09/29 07:42:21  adutta
 * LOG: Error definitions
 * LOG:
 * LOG: Revision 1.1.2.8  2005/09/27 09:33:33  adutta
 * LOG: BSSMAP procedures implemented
 * LOG:
 * LOG: Revision 1.1.2.7  2005/08/28 19:10:03  adutta
 * LOG: Handover string added
 * LOG:
 * LOG: Revision 1.1.2.6  2005/08/26 20:20:16  adutta
 * LOG: Handling of L3 message
 * LOG:
 * LOG: Revision 1.1.2.5  2005/08/26 06:53:18  adutta
 * LOG: Few more message additions
 * LOG:
 * LOG: Revision 1.1.2.4  2005/08/19 20:09:28  adutta
 * LOG: Interface related changes
 * LOG:
 * LOG: Revision 1.1.2.3  2005/08/19 11:05:49  adutta
 * LOG: Handling disconnect from remote
 * LOG:
 * LOG: Revision 1.1.2.2  2005/08/19 06:39:44  adutta
 * LOG: Design Id mapping
 * LOG:
 * LOG: Revision 1.1.2.1  2005/08/16 10:01:52  adutta
 * LOG: Add in initial implementation of BSSAP interface
 * LOG:
 ****************************************************************************/
                                                                                                                             

#ifndef  _BSSAP_COMMON_H_
#define  _BSSAP_COMMON_H_

#include <its.h>

#ifdef CCITT
#define ISS7_Stack ISS7_CCITT_Stack
#endif

#ifdef ANSI
#define ISS7_Stack ISS7_ANSI_Stack
#endif
//BSSAP App src
#define BSSAP_DTAP_SRC           (ITS_FIRST_USER_SRC)
#define BSSAP_MAP_SRC            (ITS_FIRST_USER_SRC << 1)
#define BSSAP_LAYER3_SRC         (ITS_FIRST_USER_SRC << 2)
#define BSSAP_SCCP_SRC         	 (ITS_FIRST_USER_SRC << 3)
#define ITS_ISUP_CCITT_SRC          (0xFFF8U)
#define ITS_ISUP_SRC        ITS_ISUP_CCITT_SRC

//BSSAP Error Message Types
#define BSSAP_MD_TIMEOUT         (BSSAP_MD_DTAP << 1)
#define BSSAP_MD_NETWORK         ((BSSAP_MD_DTAP << 1) | 0x01U)
#define BSSAP_MD_PROTOCOL        (BSSAP_MD_DTAP << 2)
#define BSSAP_MD_SCCP            (BSSAP_MD_DTAP << 3)

//SCCP messages
#define BSSAP_CON_ESTD           (0x04U) /* Amaresh 1 to 4 as on dated 27-09-07*/
#define BSSAP_CON_REL            (0x05U) /* Amaresh 2 to 5 as on dated 27-09-07*/
#define BSSAP_CON_REF            (0x06U) /* Amaresh 3 to 6 as on dated 27-09-07*/
#define BSSAP_CON_ERR            (0x07U) /* Amaresh new entry for err mesage of SCCP ason dated 11-02-08*/


//BSSAP Protocol error codes
#define BSSAP_EENCODE            (0x01U)
#define BSSAP_EDECODE            (0x02U)
#define BSSAP_EINVMESSAGE        (0x03U)
#define BSSAP_ECICNOTFOUND       (0x04U)
#define BSSAP_ENORESETACK        (0x05U)
#define BSSAP_ENOBLKACK          (0x06U)
#define BSSAP_ENOUNBLKACK        (0x07U)
#define BSSAP_ENORESETCKTACK     (0x08U)
#define BSSAP_EUNEQUIPCKT        (0x09U)
#define BSSAP_ENORELEASECMP      (0x0AU)
#define DTAP_EENCODE             (0x0BU)
#define BSSAP_ECKTPROC           (0x0CU)
#define BSSAP_EASSREQFAIL        (0x0DU)
#define BSSAP_ENOCKTGRPBLKACK    (0x0EU)
#define BSSAP_ENOCKTGRPUNBLKACK  (0x0FU)
#define BSSAP_EMSGSENTFAIL       (0x1FU)
#define BSSAP_ENOHANDOVERCMD       (0x20U) /* 06-11-07 Amaresh for T7 timeout */

/* Added by Amaresh as on dated 03-07-08 */
#define BSSAP_ECICCKTUNVL          	(0x2FU)
#define BSSAP_ECICCKTALCTD        	(0x3FU)
#define BSSAP_EPROTOCOLERR        	(0x4FU)
/* Added by Amaresh as on dated 03-07-08 */



/* #define BSSAP_DATA_LEN           (0xC8U) */ /* Commented by Amaresh (0x64U)  */
#define BSSAP_DATA_LEN           (0xFFU)  /* Commented by Ankur (0xC8U)  */
#define DTAP_MSG_P0S             (0x04U)
#define DTAP_PDISCR_POS          (0x03U)
#define L3MSG_TYPE_POS           (0x01U) //Added for Issue 3273



#define DTAP_STR(x) ((x==1)?"BSSAP_CC_MSG_ALERTING":\
                    ((x==2)?"BSSAP_CC_MSG_CALL_PROCEEDING":\
                    ((x==3)?"BSSAP_CC_MSG_PROGRESS":\
                    ((x==4)?"BSSAP_CC_ESTABLISHMENT":\
                    ((x==5)?"BBSSAP_CC_MSG_SETUP":\
                    ((x==6)?"BSSAP_CC_MSG_ESTABLISHMENT_CONFIRMED":\
                    ((x==7)?"BSSAP_CC_MSG_CONNECT":\
                    ((x==8)?"BSSAP_CC_MSG_CALL_CONFIRMED":\
                    ((x==9)?"BSSAP_CC_MSG_START_CC":\
                    ((x==15)?"BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE":\
                    ((x==37)?"BSSAP_CC_MSG_DISCONNECT":\
                    ((x==45)?"BSSAP_CC_MSG_RELEASE":\
                    ((x==42)?"BSSAP_CC_MSG_RELEASE_COMPLETE":\
                    ((x==50)?"BSSAP_CC_MSG_DISC_IND":\
                    ((x==51)?"BSSAP_CC_MSG_REL_IND":\
                    ((x==16)?"BSSAP_MSG_HANDOVER_REQUEST":\
                    ((x==17)?"BSSAP_MSG_HANDOVER_REQUIRED":\
                    ((x==18)?"BSSAP_MSG_HANDOVER_REQUEST_ACK":\
                    ((x==19)?"BSSAP_MSG_HANDOVER_COMMAND":\
                    ((x==20)?"BSSAP_MSG_HANDOVER_COMPLETE":\
                    ((x==27)?"BSSAP_MSG_HANDOVER_DETECT":\
                    ((x==36)?"BSSAP_MSG_CM_SERVICE_REQUEST":\
                    ((x==39)?"BSSAP_MSG_PAGING_RESPONSE":\
                    "UNKNOWN")))))))))))))))))))))))

#endif
