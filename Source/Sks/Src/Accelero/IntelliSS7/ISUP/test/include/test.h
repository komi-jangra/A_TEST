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
 *  ID: $Id: test.h,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:08  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:04  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:12  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:13:37  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:45:37  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:06  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.1  2000/09/08 14:35:59  labuser
 * LOG: cbascon: add header files in include directory
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.4  2000/05/16 15:11:35  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.3  2000/01/11 18:11:22  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.2  1999/12/27 19:01:49  cbascon
 * LOG: Added functions for reading and printing parameters for ACM, ANM, CPG,
 * LOG: REL, RLC, CFN, CON, SAM, UCIC, RSC for CCITT only.
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:05  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:38  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.5  1999/11/14 23:18:31  cbascon
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#if defined CCITT
#include <itu/mtp3.h>
#include <itu/sccp.h>
#include <itu/tcap.h>
#elif defined ANSI
#include <ansi/mtp3.h>
#include <ansi/sccp.h>
#include <ansi/tcap.h>
#endif


#define TEST_CFN           -2
#define TEST_WAIT           0
#define TEST_QUIT          -1

#define USE_ITS_INST_NB     1
#define MTP3_INST_NB        2


void DisplayMainMenu();

ITS_USHORT GetCIC();

int GetSelection(int min, int max);

int ReceiveISUPMsg(ITS_HANDLE handle, ITS_EVENT *event, ITS_HDR *hdr);

int WaitForEvent(ITS_HANDLE handle, ITS_HDR *recvHeader);

