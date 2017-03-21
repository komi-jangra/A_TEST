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
 *  ID: $Id: sendISUPMsg.h,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
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
 * LOG: Revision 3.1  2000/08/15 23:59:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.6  2000/07/06 18:40:13  labuser
 * LOG: Function declaration for TestSendUBLRequest was missing. Wish I knew
 * LOG: how.
 * LOG:
 * LOG: Revision 2.5  2000/05/16 15:11:35  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.4  2000/02/08 14:16:54  labuser
 * LOG: OGC Selected is now sent automatically in ANSI.
 * LOG:
 * LOG: Revision 2.3  2000/01/27 14:52:18  labuser
 * LOG: Added flag to indicate if OGC Selected has been sent.
 * LOG:
 * LOG: Revision 2.2  2000/01/11 18:11:21  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:04  cbascon
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
 * LOG: Revision 1.4  1999/11/24 19:31:44  cbascon
 * LOG: Added prototypes for send ISUP message functions.
 * LOG:
 * LOG: Revision 1.3  1999/11/14 23:18:31  cbascon
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <its.h>

#ifdef ANSI
#define FILENAME        "ansi_msgs"
#else
#define FILENAME        "ccitt_msgs"
#endif


#define TEST_UNKNOWN_MSG    0


/* OGC Selected is only used in ANSI for Newnet Stack */
#ifdef ANSI

static int ogcSelectedSent = ITS_FALSE;

#endif



char* GetFilename();

int SetFilename(char* newfilename);


int TestSendUnknownMsg(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendACMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendANMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendBLORequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCCRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCFNRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGBARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGURequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCPGRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCQMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFOTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendGRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINFRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendINRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendLPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendPAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRELRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRESRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendResetRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendRSCRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSUSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBLRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUBARequest(ITS_HANDLE handle, ITS_HDR *hdr);


#ifdef ANSI

int TestSendCRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendCVTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendEXMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif



#ifdef CCITT

int TestSendCONRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFAARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFARRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendFRJRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIDRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendIRSRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendNRMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendOLMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSAMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendSGMRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPARequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUPTRequest(ITS_HANDLE handle, ITS_HDR *hdr);

int TestSendUSRRequest(ITS_HANDLE handle, ITS_HDR *hdr);

#endif
