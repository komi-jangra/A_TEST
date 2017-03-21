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
 *  ID: $Id: sltm_sn.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:54  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:51  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:24  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:31  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:31  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1.46.1  2004/12/16 02:28:55  randresol
 * LOG: Add JAPAN variant implementation
 * LOG:
 * LOG: Revision 7.1.42.1  2004/10/25 20:39:56  randresol
 * LOG: Start Implementation for Japan SS7
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:25  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.3  2002/08/16 22:09:37  mmiers
 * LOG: Add the china variant
 * LOG:
 * LOG: Revision 6.2  2002/07/03 15:59:00  mmiers
 * LOG: Changes for china family
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:03  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.2  2001/09/11 22:46:06  mmiers
 * LOG: Version strings.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:51  mmiers
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

#ifndef _ITS_SLTM_SN_H_
#define _ITS_SLTM_SN_H_

#ident "$Id: sltm_sn.h,v 1.1.1.1 2007-10-08 11:11:25 bsccs2 Exp $"

/*
 * commonality
 */
#if defined(CCITT)

#define SLTM_HEADING_CODE_0_MASK    SLTM_HEADING_CODE_0_MASK_CCITT
#define SLTM_HEADING_CODE_1_MASK    SLTM_HEADING_CODE_1_MASK_CCITT

#define SLTM_HC0_SPARE  SLTM_HC0_SPARE_CCITT
#define SLTM_HC0_TST    SLTM_HC0_TST_CCITT

#define SLTM_HC0_GET    SLTM_HC0_GET_CCITT
#define SLTM_HC0_SET    SLTM_HC0_SET_CCITT
#define SLTM_HC1_GET    SLTM_HC1_GET_CCITT
#define SLTM_HC1_SET    SLTM_HC1_SET_CCITT

#define SLTM_HC1_SLTM   SLTM_HC1_SLTM_CCITT
#define SLTM_HC1_SLTA   SLTM_HC1_SLTA_CCITT

#define SLTM_LINK_TEST_GET_SLC      SLTM_LINK_TEST_GET_SLC_CCITT
#define SLTM_LINK_TEST_SET_SLC      SLTM_LINK_TEST_SET_SLC_CCITT
#define SLTM_LINK_TEST_GET_SPARE    SLTM_LINK_TEST_GET_SPARE_CCITT
#define SLTM_LINK_TEST_SET_SPARE    SLTM_LINK_TEST_SET_SPARE_CCITT
#define SLTM_LINK_TEST_GET_LENGTH   SLTM_LINK_TEST_GET_LENGTH_CCITT
#define SLTM_LINK_TEST_SET_LENGTH   SLTM_LINK_TEST_SET_LENGTH_CCITT

#define SLTM_Encode     SLTM_Encode_CCITT
#define SLTM_Decode     SLTM_Decode_CCITT

#elif defined(ANSI) /***************************************************/

#define SLTM_HEADING_CODE_0_MASK    SLTM_HEADING_CODE_0_MASK_ANSI
#define SLTM_HEADING_CODE_1_MASK    SLTM_HEADING_CODE_1_MASK_ANSI

#define SLTM_HC0_SPARE  SLTM_HC0_SPARE_ANSI
#define SLTM_HC0_TST    SLTM_HC0_TST_ANSI

#define SLTM_HC0_GET    SLTM_HC0_GET_ANSI
#define SLTM_HC0_SET    SLTM_HC0_SET_ANSI
#define SLTM_HC1_GET    SLTM_HC1_GET_ANSI
#define SLTM_HC1_SET    SLTM_HC1_SET_ANSI

#define SLTM_HC1_SLTM   SLTM_HC1_SLTM_ANSI
#define SLTM_HC1_SLTA   SLTM_HC1_SLTA_ANSI

#define SLTM_LINK_TEST_GET_SLC      SLTM_LINK_TEST_GET_SLC_ANSI
#define SLTM_LINK_TEST_SET_SLC      SLTM_LINK_TEST_SET_SLC_ANSI
#define SLTM_LINK_TEST_GET_LENGTH   SLTM_LINK_TEST_GET_LENGTH_ANSI
#define SLTM_LINK_TEST_SET_LENGTH   SLTM_LINK_TEST_SET_LENGTH_ANSI

#define SLTM_Encode     SLTM_Encode_ANSI
#define SLTM_Decode     SLTM_Decode_ANSI

#elif defined(PRC) /***************************************************/

#define SLTM_HEADING_CODE_0_MASK    SLTM_HEADING_CODE_0_MASK_PRC
#define SLTM_HEADING_CODE_1_MASK    SLTM_HEADING_CODE_1_MASK_PRC

#define SLTM_HC0_SPARE  SLTM_HC0_SPARE_PRC
#define SLTM_HC0_TST    SLTM_HC0_TST_PRC

#define SLTM_HC0_GET    SLTM_HC0_GET_PRC
#define SLTM_HC0_SET    SLTM_HC0_SET_PRC
#define SLTM_HC1_GET    SLTM_HC1_GET_PRC
#define SLTM_HC1_SET    SLTM_HC1_SET_PRC

#define SLTM_HC1_SLTM   SLTM_HC1_SLTM_PRC
#define SLTM_HC1_SLTA   SLTM_HC1_SLTA_PRC

#define SLTM_LINK_TEST_GET_SLC      SLTM_LINK_TEST_GET_SLC_PRC
#define SLTM_LINK_TEST_SET_SLC      SLTM_LINK_TEST_SET_SLC_PRC
#define SLTM_LINK_TEST_GET_SPARE    SLTM_LINK_TEST_GET_SPARE_PRC
#define SLTM_LINK_TEST_SET_SPARE    SLTM_LINK_TEST_SET_SPARE_PRC
#define SLTM_LINK_TEST_GET_LENGTH   SLTM_LINK_TEST_GET_LENGTH_PRC
#define SLTM_LINK_TEST_SET_LENGTH   SLTM_LINK_TEST_SET_LENGTH_PRC

#define SLTM_Encode     SLTM_Encode_PRC
#define SLTM_Decode     SLTM_Decode_PRC

#elif defined(TTC) /***************************************************/

#define SLTM_HEADING_CODE_0_MASK    SLTM_HEADING_CODE_0_MASK_TTC
#define SLTM_HEADING_CODE_1_MASK    SLTM_HEADING_CODE_1_MASK_TTC

#define SLTM_HC0_SPARE  SLTM_HC0_SPARE_TTC
#define SLTM_HC0_TST    SLTM_HC0_TST_TTC

#define SLTM_HC0_GET    SLTM_HC0_GET_TTC
#define SLTM_HC0_SET    SLTM_HC0_SET_TTC
#define SLTM_HC1_GET    SLTM_HC1_GET_TTC
#define SLTM_HC1_SET    SLTM_HC1_SET_TTC

#define SLTM_HC1_SLTM   SLTM_HC1_SLTM_TTC
#define SLTM_HC1_SLTA   SLTM_HC1_SLTA_TTC

#define SLTM_LINK_TEST_GET_SLC      SLTM_LINK_TEST_GET_SLC_TTC
#define SLTM_LINK_TEST_SET_SLC      SLTM_LINK_TEST_SET_SLC_TTC
#define SLTM_LINK_TEST_GET_SPARE    SLTM_LINK_TEST_GET_SPARE_TTC
#define SLTM_LINK_TEST_SET_SPARE    SLTM_LINK_TEST_SET_SPARE_TTC
#define SLTM_LINK_TEST_GET_LENGTH   SLTM_LINK_TEST_GET_LENGTH_TTC
#define SLTM_LINK_TEST_SET_LENGTH   SLTM_LINK_TEST_SET_LENGTH_TTC

#define SLTM_Encode     SLTM_Encode_TTC
#define SLTM_Decode     SLTM_Decode_TTC


#else
#error "Protocol family not defined."
#endif

#endif /* _ITS_SLTM_SN_H_ */

