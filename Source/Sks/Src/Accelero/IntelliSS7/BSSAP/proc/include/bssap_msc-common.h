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
 * ID: $Id: bssap_msc-common.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/08/01 11:33:04  amaresh.prasad
 * LOG: Updated for sms data len
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:55  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.7  2006/05/05 05:21:56  adutta
 * LOG: Makeup for large context
 * LOG:
 * LOG: Revision 1.1.2.6  2006/04/25 05:33:13  adutta
 * LOG: Changed as par IMR comments
 * LOG:
 * LOG: Revision 1.1.2.5  2005/11/20 14:25:09  adutta
 * LOG: Added SCCP message code for CREF
 * LOG:
 * LOG: Revision 1.1.2.4  2005/11/18 06:40:41  mkrishna
 * LOG: Added SCCP indications
 * LOG:
 * LOG: Revision 1.1.2.3  2005/11/17 06:16:21  mkrishna
 * LOG: New error code added
 * LOG:
 * LOG: Revision 1.1.2.2  2005/11/08 07:21:33  mkrishna
 * LOG: Added CktGrpBlk/CktGrpUnblk error codes
 * LOG:
 * LOG: Revision 1.1.2.1  2005/10/11 10:06:26  adutta
 * LOG: Add in initial implementation of BSSAP (MSC)
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_COMMON_H_
#define  _BSSAP_COMMON_H_

#include <its.h>


#define ISS7_Stack ISS7_CCITT_Stack

//BSSAP App src
#define BSSAP_DTAP_SRC           (ITS_FIRST_USER_SRC)
#define BSSAP_MAP_SRC            (ITS_FIRST_USER_SRC << 1)
#define BSSAP_HND_SRC            (ITS_FIRST_USER_SRC << 2)

//BSSAP Error Message Types
#define BSSAP_MD_TIMEOUT         (BSSAP_MD_DTAP << 1)
#define BSSAP_MD_NETWORK         ((BSSAP_MD_DTAP << 1) | 0x01U)
#define BSSAP_MD_PROTOCOL        (BSSAP_MD_DTAP << 2)
#define BSSAP_MD_SCCP            (BSSAP_MD_DTAP << 3)

//SCCP messages
#define BSSAP_CON_ESTD           (0x01U)
#define BSSAP_CON_REL            (0x02U)
#define BSSAP_CON_REF            (0x03U)


//BSSAP Protocol error codes
#define BSSAP_EENCODE            (0x01U)
#define BSSAP_EDECODE            (0x02U)
#define BSSAP_EINVMESSAGE        (0x03U)
#define BSSAP_ECICNOTFOUND       (0x04U)
#define BSSAP_ENORESETACK        (0x05U)
#define	BSSAP_ENOBLKACK          (0x06U)
#define BSSAP_ENOUNBLKACK        (0x07U)
#define BSSAP_ENORESETCKTACK     (0x08U)
#define BSSAP_EUNEQUIPCKT        (0x09U)
#define BSSAP_ENORELEASECMP      (0x0AU)
#define DTAP_EENCODE             (0x0BU)
#define BSSAP_ECKTPROC           (0x0CU)
#define BSSAP_EASSREQFAIL        (0x0DU) 
#define BSSAP_ENOCKTGRPBLKACK    (0x0EU)
#define BSSAP_ENOCKTGRPUNBLKACK  (0x0FU)
#define BSSAP_EMSGSENTFAIL       (0x10U)
#define BSSAP_EMSCMASTER         (0x11U)


#define BSSAP_DATA_LEN           (0xC8U)
#define DTAP_MSG_P0S             (0x04U)
#define DTAP_PDISCR_POS          (0x03U)
#define L3MSG_TYPE_POS           (0x01U)




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
                    ((x==50)?"BSSAP_CC_MSG_DISCONNECT_IND":\
                    ((x==51)?"BSSAP_CC_MSG_RELEASE_IND":\
                    ((x==52)?"BSSAP_CC_MSG_TIMEOUT_IND":\
                    ((x==53)?"BSSAP_CC_MSG_RELEASE_COMPLETE_IND":\ 
                    "UNKNOWN")))))))))))))))))))))))))))

#endif
