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
 *  ID: $Id: mtp3_cmn.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:50  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:46  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:12  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:17  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.14.1  2004/09/21 06:54:43  mmanikandan
 * LOG: Propagating pprint from current.
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:22  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.2  2002/03/12 22:41:42  mmiers
 * LOG: Change the message numbers for better interaction with SCCP
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:01  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:46  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.2  2001/06/21 01:04:48  mmiers
 * LOG: Make sure files end with newline
 * LOG:
 * LOG: Revision 4.1  2001/06/20 17:09:49  mmiers
 * LOG: The great namespace split, part two.  Also a bug fix to support.
 * LOG:
 *
 *****************************************************************************/

#ifndef _ITS_MTP3_CMN_H_
#define _ITS_MTP3_CMN_H_

#ident "$Id: mtp3_cmn.h,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $"

#include <its_pprint.h>

/*
 * SIO data
 */
/* user parts */
#define MTP3_MAX_USER_PARTS     16

#define MTP3_SIO_SNMM           0x00U
#define MTP3_SIO_SLTM_REG       0x01U
#define MTP3_SIO_SLTM_SPEC      0x02U
#define MTP3_SIO_SCCP           0x03U
#define MTP3_SIO_TUP            0x04U
#define MTP3_SIO_ISUP           0x05U
#define MTP3_SIO_DUP_CIRC       0x06U
#define MTP3_SIO_DUP_FAC        0x07U
#define MTP3_SIO_MTP_TEST       0x08U
#define MTP3_SIO_BROAD_ISUP     0x09U
#define MTP3_SIO_SAT_ISUP       0x0AU
#define MTP3_SIO_SPARE3         0x0BU
#define MTP3_SIO_SPARE4         0x0CU
#define MTP3_SIO_ECIS6          0x0DU
#define MTP3_SIO_PRIVATE        0x0EU
#define MTP3_SIO_SPARE5         0x0FU

#define MTP3_SIO_UP_MASK        MTP3_SIO_SPARE5

/* network indicator codes */
#define MTP3_NIC_INTERNATIONAL  0x00U
#define MTP3_NIC_SPARE          0x40U
#define MTP3_NIC_NATIONAL       0x80U
#define MTP3_NIC_RESERVED       0xC0U

#define MTP3_NIC_MASK           MTP3_NIC_RESERVED

/* message priority codes */
#define MTP3_MPC_PRI_0          0x00U
#define MTP3_MPC_PRI_1          0x10U
#define MTP3_MPC_PRI_2          0x20U
#define MTP3_MPC_PRI_3          0x30U

#define MTP3_MPC_MASK           MTP3_MPC_PRI_3

/*
 * Message types
 */
#define MTP3_MSG_USER_DATA      0x21U
#define MTP3_MSG_PAUSE          0x22U
#define MTP3_MSG_RESUME         0x23U
#define MTP3_MSG_STATUS         0x24U

#define MTP3_STATUS_CONGESTED       0x01U
#define MTP3_STATUS_UPU_UNKNOWN     0x02U
#define MTP3_STATUS_UPU_UNEQUIP     0x03U
#define MTP3_STATUS_UPU_INACCESS    0x04U

/*
 * message type
 */
#define MTP3_MSG_TYPE(ev)   ((ev)->data[0])

#endif /* _ITS_MTP3_CMN_H_ */

