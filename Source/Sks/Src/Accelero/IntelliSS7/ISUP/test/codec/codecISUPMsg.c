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
 *  ID: $Id: codecISUPMsg.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
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
 * LOG: Revision 5.1  2001/08/16 20:45:36  mmiers
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

#include <stdio.h>
#include <memory.h>

#include <its.h>
#include <itu/isup.h>
#include <ansi/isup.h>
#include "readISUPMsg.h"
#include "printISUPMsg.h"
#include "codecISUPMsg.h"


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will prompt the user for an integer input 
 *      
 *  Input Parameters:
 *      min - minimum valid input
 *      max - maximum valid input
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None
 *
 *  Return Value:
 *      Integer entered by the user which is between min and max.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
int
GetSelection(int min, int max)
{
	int selection = 0;
    
    fflush(stdin);
    printf("\n -> ");
    scanf("%d", &selection);

    while ((selection < min) || (selection > max))
    {
        fflush(stdin);
        printf("\n Incorrect Selection (range is: %d to %d) -> ", min,
               max);
        scanf("%d", &selection);
    }
    return selection;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function will display the main menu of the ISUP test program.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DisplayMainMenu()
{
    printf("\n");
    printf("\n MAIN MENU");
    printf("\n -----------------------------------------------------");
    printf("\n [%3d] ACM  - Address Complete", ISUP_MSG_ACM);
    printf("\n [%3d] ANM  - Answer", ISUP_MSG_ANM);
    printf("\n [%3d] CFN  - Confusion", ISUP_MSG_CFN);
    printf("\n [%3d] COT  - Continuity", ISUP_MSG_COT);
    printf("\n [%3d] CPG  - Call Progress", ISUP_MSG_CPG);
    printf("\n [%3d] IAM  - Initial Address", ISUP_MSG_IAM);
    printf("\n [%3d] INF  - Information", ISUP_MSG_INF);
    printf("\n [%3d] INR  - Information Request", ISUP_MSG_INR);
    printf("\n [%3d] PAM  - Pass Along", ISUP_MSG_PAM);
    printf("\n [%3d] REL  - Release", ISUP_MSG_REL);
    printf("\n [%3d] RLC  - Release Complete", ISUP_MSG_RLC);
    printf("\n [%3d] RSC  - Release Complete", ISUP_MSG_RSC);
    printf("\n [%3d] UCIC - Unidentified Circuit Identification Code",
           ISUP_MSG_UCIC);
    printf("\n");
    printf("\n [%3d] Exit", TEST_EXIT);
    printf("\n");
}

int
ISUP_SendEvent(ITS_HANDLE handle, ITS_OCTET type, ITS_HDR *hdr,
               ITS_ISUP_IE *ies, int ieCount, ISUP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}

int
ISUP_ReceiveEvent(ITS_HANDLE handle, ITS_EVENT *ev, ITS_HDR *hdr,
                  ITS_ISUP_IE *ies, int *ieCount, ISUP_MSG_DESC *desc)
{
    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP ACM message.
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestACMRequest()
{
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[11], d_ies[11];
    ITS_EVENT *event;
    ITS_HDR *hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *)); 
    hdr = (ITS_HDR*)calloc(1, sizeof(ITS_HDR*));

    hdr->context.CIC = 1;
 
    printf("\n ------ Sending ACM Request ------");
    ReadISUPMsg(ISUP_MSG_ACM, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_ACM, event, hdr,
                         &ISUP_ACM_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
        printf("\n Error: %s", ITS_GetErrorText(result));
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_ACM_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(d_ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
        printf("\n Error: %s", ITS_GetErrorText(result));
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestANMRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[11], d_ies[11];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending ANM Request ------");
    ReadISUPMsg(ISUP_MSG_ANM, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_ANM, event, &hdr,
                         &ISUP_ANM_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_ANM_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestCFNRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[11], d_ies[11];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending CFN Request ------");
    ReadISUPMsg(ISUP_MSG_CFN, FILENAME, &(ies[0]), &ieCount);

    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_CFN, event, &hdr,
                         &ISUP_CFN_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_CFN_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
TestCONRequest()
{
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[11], d_ies[11];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending CON Request ------");
    ReadISUPMsg(ISUP_MSG_CON, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_CON, event, &hdr,
                         &ISUP_CON_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_CON_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestCOTRequest()
{
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[1], d_ies[1];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending COT Request ------");
    ReadISUPMsg(ISUP_MSG_COT, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_COT, event, &hdr,
                         &ISUP_COT_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_COT_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestCPGRequest()
{
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[10], d_ies[10];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending CPG Request ------");
    ReadISUPMsg(ISUP_MSG_CPG, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_CPG, event, &hdr,
                         &ISUP_CPG_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_CPG_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestIAMRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[28], d_ies[28];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending IAM Request ------");
    ReadISUPMsg(ISUP_MSG_IAM, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_IAM, event, &hdr,
                         &ISUP_IAM_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_IAM_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestINFRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[11], d_ies[11];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending INF Request ------");
    ReadISUPMsg(ISUP_MSG_INF, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_INF, event, &hdr,
                         &ISUP_INF_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_INF_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestINRRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[4], d_ies[4];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending INR Request ------");
    ReadISUPMsg(ISUP_MSG_INR, FILENAME, &(ies[0]), &ieCount);
 
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_INR, event, &hdr,
                         &ISUP_INR_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_INR_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestPAMRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[12], d_ies[12];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending PAM Request ------");
    ReadISUPMsg(ISUP_MSG_PAM, FILENAME, &(ies[0]), &ieCount);
  
    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_PAM, event, &hdr,
                         &ISUP_PAM_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_PAM_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestRELRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[6], d_ies[6];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending REL Request ------");
    ReadISUPMsg(ISUP_MSG_REL, FILENAME, &(ies[0]), &ieCount);

    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_REL, event, &hdr,
                         &ISUP_REL_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_REL_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestRLCRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[12], d_ies[12];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));
    
    printf("\n ------ Sending RLC Request ------");
    printf("\n No parameters for this message.");

    printf("\n");
    printf("\n Printing parameters before Encode");
    printf("\n -----------------------------------");
    PrintISUPMsg(ies, ieCount);

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_RLC, event, &hdr,
                         &ISUP_RLC_Desc);
    
    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_RLC_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestRSCRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[12], d_ies[12];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending RSC Request ------");
    printf("\n No parameters for this message.");

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_RSC, event, &hdr,
                         &ISUP_RSC_Desc);

    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_RSC_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
#ifdef CCITT
void
TestSAMRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[12], d_ies[12];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    printf("\n ------ Sending SAM Request ------");
    ReadISUPMsg(ISUP_MSG_SAM, FILENAME, &(ies[0]), &ieCount);
    
    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_SAM, event, &hdr,
                         &ISUP_SAM_Desc);

    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_SAM_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function
 *      
 *  Input Parameters:
 *      handle - the transport associated with this ISUP message
 *      header - a pointer to the context for this ISUP message
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS is returned if ISUP message is sent successfully.
 *      Any other return code indicates an IntelliSS7 error.
 *
 *  Notes:
 *
 *      Each ISUP message has its own ISUP_SendXXXX() function.
 *
 *  See Also:
 ****************************************************************************/
void
TestUCICRequest()
{   
    int result = 0; 
    int ieCount = 0, d_ieCount = 0;
    ITS_ISUP_IE ies[1], d_ies[1];
    ITS_EVENT *event;
    ITS_HDR hdr;

    event = (ITS_EVENT*)calloc(1, sizeof(ITS_EVENT *));

    /* only have message tag as parameter */
    printf("\n ------ Sending UCIC Request ------");
    printf("\n No parameters for this message.");

    printf("\n");
    printf("\n Encoding");
    printf("\n ---------");
    result = ISUP_Encode(ies, ieCount, ISUP_MSG_UCIC, event, &hdr,
                         &ISUP_UCIC_Desc);

    /* Check encode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Encode success.");
    }
    else
    {
        printf("\n Encode failed.");
    }

    printf("\n");
    printf("\n Decoding");
    printf("\n ---------");
    result = ISUP_Decode(d_ies, &d_ieCount, event, &ISUP_UCIC_Desc);

    /* Check decode result */
    if (result == ITS_SUCCESS)
    {
        printf("\n Decode success.");
        printf("\n");
        printf("\n Printing parameters after Decode");
        printf("\n -----------------------------------");
        PrintISUPMsg(ies, ieCount);
    }
    else
    {
        printf("\n Decode failed.");
    }
}

