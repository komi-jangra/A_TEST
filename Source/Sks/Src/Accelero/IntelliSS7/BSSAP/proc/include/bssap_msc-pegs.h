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
 * ID: $Id: bssap_msc-pegs.h,v 1.1.1.1 2007-10-08 11:11:13 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:40  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:39  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:12:56  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 1.1.2.1  2005/11/30 06:51:41  mkrishna
 * LOG: Added pegs initial implementation
 * LOG:
 ****************************************************************************/

#ifndef  _BSSAP_PEG_H_
#define  _BSSAP_PEG_H_

#include <its_pegs.h>

extern PEG_Manager *BSSAP_Pegs;

#define   PEG_BSSAP_NUM_PEGS     20

// SCCP messages
#define   PEG_BSSAP_CR_RECV      0
#define   PEG_BSSAP_DT1_RECV     1
#define   PEG_BSSAP_CR_SEND      2
#define   PEG_BSSAP_DT1_SEND     3

// DTAP Messages
#define   PEG_BSSAP_DTAP_SEND    4
#define   PEG_BSSAP_DTAP_RECV    5


// MAP Messages
#define   PEG_BSSAP_MAP_SEND     6
#define   PEG_BSSAP_MAP_RECV     7

// Confusion Message
#define   PEG_BSSAP_CONF_SEND    8
#define   PEG_BSSAP_CONF_RECV    9

// CM Service request received
#define   PEG_BSSAP_CMSERV_RECV  10

// Paging response received
#define   PEG_BSSAP_PAGRSP_RECV  11

#define PEG_BSSAP_LAST_COUNT 12

#define PEG_STR(x) ((x==0)?"PEG_BSSAP_CR_RECV":\
                    ((x==1)?"PEG_BSSAP_DT1_RECV":\
                    ((x==2)?"PEG_BSSAP_CR_SEND":\
                    ((x==3)?"PEG_BSSAP_DT1_SEND":\
                    ((x==4)?"PEG_BSSAP_DTAP_SEND":\
                    ((x==5)?"PEG_BSSAP_DTAP_RECV":\
                    ((x==6)?"PEG_BSSAP_MAP_SEND":\
                    ((x==7)?"PEG_BSSAP_MAP_RECV":\
                    ((x==8)?"PEG_BSSAP_CONF_SEND":\
                    ((x==9)?"PEG_BSSAP_CONF_RECV":\
                    ((x==10)?"PEG_BSSAP_CMSERV_RECV":\
                    ((x==11)?"PEG_BSSAP_PAGRSP_RECV":\
                    "UNKNOWN"))))))))))))


#endif
