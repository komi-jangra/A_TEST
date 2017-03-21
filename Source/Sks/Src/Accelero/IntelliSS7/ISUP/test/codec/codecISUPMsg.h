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
 *  ID: $Id: codecISUPMsg.h,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:48  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:07  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:03  cvsadmin
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
 * LOG: Revision 3.1  2000/08/15 23:59:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/11/24 16:13:43  cbascon
 * LOG: Added ISUP C encode/decode test program.
 * LOG: Just ANSI for now. Need to remove obj files and license file.
 * LOG:
 *
 ****************************************************************************/

#ifndef _CODEC_ISUP_H_
#define _CODEC_ISUP_H_

#include <its.h>

#ifdef CCITT
#include <itu/isup.h>
#endif
#ifdef ANSI
#include <ansi/isup.h>
#endif


/* Used to exit test */
#define TEST_EXIT       -1


/* Filename used for building ISUP messages */
#ifdef ANSI
#define FILENAME        "../ansiisupmsgs.txt"
#else
#define FILENAME        "../ccittisupmsgs.txt"
#endif

/* ISUP Encode/Decode Test functions */
void TestACMRequest();
void TestANMRequest();
void TestCFNRequest();
void TestCOTRequest();
void TestCPGRequest();
void TestIAMRequest();
void TestINFRequest();
void TestINRRequest();
void TestPAMRequest();
void TestSAMRequest();
void TestRELRequest();
void TestRLCRequest();
void TestRSCRequest();
void TestUCICRequest();


#ifdef CCITT
void TestCONRequest();
void TestRSCRequest();
#endif

int ISUP_SendEvent(ITS_HANDLE handle, ITS_OCTET type, ITS_HDR *hdr,
                   ITS_ISUP_IE *ies, int ieCount, ISUP_MSG_DESC *desc);

int ISUP_ReceiveEvent(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                      ITS_ISUP_IE *ies, int *ieCount, ISUP_MSG_DESC *desc);

int GetSelection(int min, int max);
void DisplayMainMenu();


#endif /* _CODEC_ISUP_H_ */

