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
 *                  
 * CONTRACT: INTERNAL
 *      
 * ID: $Id: mtp2_sn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:01  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:21  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:33  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:44:57  hbalimid
 * LOG: Got here for demo isup
 * LOG:
 * LOG: Revision 5.5  2001/10/05 22:59:15  mmiers
 * LOG: Update from working on NMS MTP2 API
 * LOG:
 * LOG: Revision 5.4  2001/09/11 22:46:05  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.3  2001/09/06 17:24:39  mmiers
 * LOG: Closing in.
 * LOG:
 * LOG: Revision 5.2  2001/09/05 23:06:41  mmiers
 * LOG: Initial cut at an MTP2 interface.  Likely to change.
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
 ****************************************************************************/

#if !defined(_ITS_MTP2_SN_H_)
#define _ITS_MTP2_SN_H_

#ident "$Id: mtp2_sn.h,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $"

/*
 * protocol independent
 */
#if defined(CCITT)

#define MTP2_HEADER             MTP2_HEADER_CCITT

#define MTP2_GET_BSN            MTP2_GET_BSN_CCITT
#define MTP2_SET_BSN            MTP2_SET_BSN_CCITT

#define MTP2_GET_BIB            MTP2_GET_BIB_CCITT
#define MTP2_SET_BIB            MTP2_SET_BIB_CCITT

#define MTP2_GET_FSN            MTP2_GET_FSN_CCITT
#define MTP2_SET_FSN            MTP2_SET_FSN_CCITT

#define MTP2_GET_FIB            MTP2_GET_FIB_CCITT
#define MTP2_SET_FIB            MTP2_SET_FIB_CCITT

#define MTP2_GET_LI             MTP2_GET_LI_CCITT
#define MTP2_SET_LI             MTP2_SET_LI_CCITT

#define MTP2_GET_SIO            MTP2_GET_SIO_CCITT
#define MTP2_SET_SIO            MTP2_SET_SIO_CCITT

#define MTP2_MSG_MSU            MTP2_MSG_MSU_CCITT
#define MTP2_MSG_LSSU           MTP2_MSG_LSSU_CCITT
#define MTP2_MSG_FISU           MTP2_MSG_FISU_CCITT

#define MTP2_MSG_TYPE           MTP2_MSG_TYPE_CCITT

#define MTP2_GET_MSU_LEN        MTP2_GET_MSU_LEN_CCITT
#define MTP2_SET_MSU_LEN        MTP2_SET_MSU_LEN_CCITT

#define MTP2_MAX_MSG_SIZE       MTP2_MAX_MSG_SIZE_CCITT

#define MTP2_SendData           MTP2_SendData_CCITT
#define MTP2_ReceiveData        MTP2_ReceiveData_CCITT
#define MTP2_Encode             MTP2_Encode_CCITT
#define MTP2_Decode             MTP2_Decode_CCITT

#define ITS_MTP2                ITS_MTP2_CCITT
#define ITS_MTP2_SRC            ITS_MTP2_CCITT_SRC

#elif defined(ANSI)

#define MTP2_HEADER             MTP2_HEADER_ANSI

#define MTP2_GET_BSN            MTP2_GET_BSN_ANSI
#define MTP2_SET_BSN            MTP2_SET_BSN_ANSI

#define MTP2_GET_BIB            MTP2_GET_BIB_ANSI
#define MTP2_SET_BIB            MTP2_SET_BIB_ANSI

#define MTP2_GET_FSN            MTP2_GET_FSN_ANSI
#define MTP2_SET_FSN            MTP2_SET_FSN_ANSI

#define MTP2_GET_FIB            MTP2_GET_FIB_ANSI
#define MTP2_SET_FIB            MTP2_SET_FIB_ANSI

#define MTP2_GET_LI             MTP2_GET_LI_ANSI
#define MTP2_SET_LI             MTP2_SET_LI_ANSI

#define MTP2_GET_SIO            MTP2_GET_SIO_ANSI
#define MTP2_SET_SIO            MTP2_SET_SIO_ANSI

#define MTP2_MSG_MSU            MTP2_MSG_MSU_ANSI
#define MTP2_MSG_LSSU           MTP2_MSG_LSSU_ANSI
#define MTP2_MSG_FISU           MTP2_MSG_FISU_ANSI

#define MTP2_MSG_TYPE           MTP2_MSG_TYPE_ANSI

#define MTP2_GET_MSU_LEN        MTP2_GET_MSU_LEN_ANSI
#define MTP2_SET_MSU_LEN        MTP2_SET_MSU_LEN_ANSI

#define MTP2_MAX_MSG_SIZE       MTP2_MAX_MSG_SIZE_ANSI

#define MTP2_SendData           MTP2_SendData_ANSI
#define MTP2_ReceiveData        MTP2_ReceiveData_ANSI
#define MTP2_Encode             MTP2_Encode_ANSI
#define MTP2_Decode             MTP2_Decode_ANSI

#define ITS_MTP2                ITS_MTP2_ANSI
#define ITS_MTP2_SRC            ITS_MTP2_ANSI_SRC

#endif

#endif /* _ITS_MTP2_SN_H_ */

