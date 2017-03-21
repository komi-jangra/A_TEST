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
 *     FILE: its.h                                                          *
 *                                                                          *
 ****************************************************************************
 *
 *  ID: $Id: testMain.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
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
 * LOG: Revision 3.1  2000/08/15 23:59:37  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:40  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.1  1999/11/24 16:13:46  cbascon
 * LOG: Added ISUP C encode/decode test program.
 * LOG: Just ANSI for now. Need to remove obj files and license file.
 * LOG:
 *
 ***************************************************************************/

#include <stdio.h>

#include <its.h>
#include <its_app.h>
#include <its_stubs.h>

#ifdef CCITT
#include <itu/mtp3.h>
#include <itu/isup.h>
#elif defined ANSI
#include <ansi/mtp3.h>
#include <ansi/isup.h>
#endif

#include "codecISUPMsg.h"



/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will get 
 *      
 *  Input Parameters:
 *      ie - a pointer to an information element structure to store data read
 *           from the buffer
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      array - pointer to ITS_OCTET array where octets taken from StrToken
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if 
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
main(int argc, char** argv)
{
    int choice = 0;
    int keepGoing = 1;
    int result = 0;
    int cic = 0x00;
    ITS_USHORT instance = 0;
    ITS_HANDLE handle = NULL;
    ITS_HDR hdr;

    /* Initialize header */
    memset((char *)&hdr, 0, sizeof(ITS_HDR));

    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****      IntelliSS7 ISUP API        *****\n");
    printf("\t *****       Encode/Decode Test        *****\n");
    printf("\t *******************************************\n");
    printf("\n");

    APPL_SetName("codec");

    /* Main menu loop */
    while (keepGoing)
    {
        DisplayMainMenu();

        /* ISUP_MSG_CFN has highest tag value of ISUP messages in this test */
        choice = GetSelection( -1, ISUP_MSG_CFN );

        switch ( choice )
        {
        case ISUP_MSG_ACM:
            TestACMRequest();
            break;
        case ISUP_MSG_ANM:
            TestANMRequest();
            break;
        case ISUP_MSG_CFN:
            TestCFNRequest();
            break;
        case ISUP_MSG_COT:
            TestCOTRequest();
            break;
        case ISUP_MSG_CPG:
            TestCPGRequest();
            break;
        case ISUP_MSG_IAM:
            TestIAMRequest();
            break;
        case ISUP_MSG_INF:
            TestINFRequest();
            break;
        case ISUP_MSG_INR:
            TestINRRequest();
            break;
        case ISUP_MSG_PAM:
            TestPAMRequest();
            break;
        case ISUP_MSG_REL:
            TestRELRequest();
            break;
        case ISUP_MSG_RLC:
            TestRLCRequest();
            break;
        case ISUP_MSG_RSC:
            TestRSCRequest();
            break;
        case ISUP_MSG_UCIC:
            TestUCICRequest();
            break;

        case TEST_EXIT:
            keepGoing = 0;
            break;
        default:
            printf("\n Invalid selection.");
        }
    }
    return ITS_SUCCESS;
}

