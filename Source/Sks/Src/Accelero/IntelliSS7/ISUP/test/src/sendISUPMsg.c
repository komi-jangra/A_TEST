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
 *  ID: $Id: sendISUPMsg.c,v 1.1.1.1 2007-10-08 11:11:21 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:49  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:44  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:08  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:05  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:50:01  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:13  mmiers
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
 * LOG: Revision 1.2  2000/09/21 23:20:56  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1  2000/09/08 14:34:18  labuser
 * LOG: cbascon: now have correct directory structure
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:35  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.9  2000/05/16 15:11:34  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.8  2000/02/08 14:16:54  labuser
 * LOG: OGC Selected is now sent automatically in ANSI.
 * LOG:
 * LOG: Revision 2.7  2000/01/27 14:54:37  labuser
 * LOG: cbascon: Initialize IE arrays before use.
 * LOG:          Check if OGC Selected has been sent before sending an ACM,
 * LOG:          ANM, & OGC Selected.
 * LOG:
 * LOG: Revision 2.6  2000/01/11 23:01:05  labuser
 * LOG: Clean up and included correct message name in comments.
 * LOG:
 * LOG: Revision 2.5  2000/01/11 18:11:21  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.4  1999/12/27 21:51:33  cbascon
 * LOG: Clean up code.
 * LOG:
 * LOG: Revision 2.3  1999/12/20 23:29:26  cbascon
 * LOG: Initialize ieCount in ISUP test send functions.
 * LOG:
 * LOG: Revision 2.2  1999/12/10 22:50:06  cbascon
 * LOG: Tested ANSI ISUP messages ACM, ANM, CPG, IAM, BLO, UBL, UCIC, REL,
 * LOG: RLC, RSC
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:04  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:37  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.6  1999/11/24 19:30:09  cbascon
 * LOG: Added send functions for more ISUP messages.
 * LOG:
 * LOG: Revision 1.5  1999/11/14 23:26:19  cbascon
 * LOG: ISUP Messages will now be printed before sending.
 * LOG:
 * LOG: Revision 1.4  1999/11/14 23:18:30  cbascon
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <memory.h>

#include <its.h>
#include <itu/isup.h>
#include <ansi/isup.h>

/* EBS headers */
#include <types.h>
#include <api.h>
#include <isupparams.h>
#include <isupcall.h>
#include <isupcircuit.h>
#include <isupcause.h>
#include <isupuser.h>
#include <isupCallCont.h>
#include <EBSalarm.h>

#include "readISUPMsg.h"
#include "sendISUPMsg.h"
#include "printISUPMsg.h"

int  errno;
static char filename[50] = "";

char*
GetFilename()
{
    return filename;
}

int
SetFilename(char* newfilename)
{
    printf("\n");
    printf("ISUPTEST: Filename = %s \n", newfilename);
    strcpy(filename, newfilename);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an 
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
int
TestSendUnknownMsg(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int        result = ITS_SUCCESS;
    ITS_EVENT  event; 
     
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    event.src = ITS_ISUP_SRC;
    event.len = 3;
    event.data[0] = 0xFF;
    event.data[1] = 0;
    event.data[2] = 48;

    result = ITS_PutEvent(handle, &event);

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Address Complete message.
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
int
TestSendACMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          result = ITS_SUCCESS; 
    int          ieCount = 0;
    int          d_ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending ACM Request ------\n");
    
#ifdef ANSI
    if (ogcSelectedSent == ITS_FALSE)
    {
        if (EXT_SelectCIC(handle, hdr, ISUP_MSG_ACM) == ITS_SUCCESS)
        {
            printf("ISUPTEST: OGC Selected sent. CIC %d \n", hdr->context.CIC);
        }
        else
        {
            printf("ISUPTEST: Failed to send OGC Selected. CIC %d \n",
                   hdr->context.CIC);
        }
    }
#endif

    ReadISUPMsg(ISUP_MSG_ACM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);
    result = ISUP_SendACMRequest(handle, hdr, ies, ieCount);

#ifdef ANSI
    printf("ISUPTEST: Setting ogcSelectedSent = true \n");
    ogcSelectedSent = ITS_TRUE;
#endif

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Answer message.
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
int
TestSendANMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          result = ITS_SUCCESS;
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending ANM Request ------\n");

#ifdef ANSI
    if (ogcSelectedSent == ITS_FALSE)
    {
        if (EXT_SelectCIC(handle, hdr, ISUP_MSG_ANM) == ITS_SUCCESS)
        {
            printf("ISUPTEST: OGC Selected sent. CIC %d \n", hdr->context.CIC);
        }
        else
        {
            printf("ISUPTEST: Failed to send OGC Selected. CIC %d \n",
                   hdr->context.CIC);
        }
    }
#endif

    ReadISUPMsg(ISUP_MSG_ANM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);
    result = ISUP_SendANMRequest(handle, hdr, ies, ieCount);

#ifdef ANSI
    /* Resetting to false for next call */
    printf("ISUPTEST: Setting ogcSelectedSent = false \n");
    ogcSelectedSent = ITS_FALSE;
#endif

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Blocking message.
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
int
TestSendBLORequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending BLO Request ------\n");
    printf("No parameters for this message.\n");

    return ISUP_SendBLORequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Continuity Check Request message.
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
int
TestSendCCRRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CCR Request ------\n");
    printf("No parameters for this message.\n");

    return ISUP_SendCCRRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Confusion message.
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
int
TestSendCFNRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CFN Request ------\n");
    ReadISUPMsg(ISUP_MSG_CFN, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCFNRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Group Block message.
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
int
TestSendCGBRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CGB Request ------\n");
    ReadISUPMsg(ISUP_MSG_CGB, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCGBRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Group Unblock message.
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
int
TestSendCGURequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CGU Request ------\n");
    ReadISUPMsg(ISUP_MSG_CGU, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCGURequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Group Unblock message.
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
int
TestSendCGUARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("[ISUPTEST] %s %s: %s: line %d\n", __DATE__, __TIME__, __FILE__,
           __LINE__);
    printf("Sending CGUA Request\n");
    ReadISUPMsg(ISUP_MSG_CGUA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCGUARequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Connect message.
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
#ifdef CCITT
int
TestSendCONRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CON Request ------\n");
    ReadISUPMsg(ISUP_MSG_CON, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCONRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Continuity message.
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
int
TestSendCOTRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending COT Request ------\n");
    ReadISUPMsg(ISUP_MSG_COT, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCOTRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Call Progress message.
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
int
TestSendCPGRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CPG Request ------\n");
    ReadISUPMsg(ISUP_MSG_CPG, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCPGRequest(handle, hdr, ies, ieCount);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Query message.
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
int
TestSendCQMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CQM Request ------\n");
    ReadISUPMsg(ISUP_MSG_CQM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCQMRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Reservation message.
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
#ifdef ANSI
int
TestSendCRMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CRM Request ------\n");
    ReadISUPMsg(ISUP_MSG_CRM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCRMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Validation Response message.
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
#ifdef ANSI
int
TestSendCVRRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CVR Request ------\n");
    ReadISUPMsg(ISUP_MSG_CVR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCVRRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Validation Test message.
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
#ifdef ANSI
int
TestSendCVTRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CVT Request ------\n");
    ReadISUPMsg(ISUP_MSG_CVT, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCVTRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends an ISUP Exit message.
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
#ifdef ANSI
int
TestSendEXMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending EXM Request ------\n");
    ReadISUPMsg(ISUP_MSG_EXM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    if (EXT_SelectCIC(handle, hdr, ISUP_MSG_ACM) == ITS_SUCCESS)
    {
        printf("ISUPTEST: OGC Selected sent. CIC %d \n", hdr->context.CIC);
    }
    else
    {
        printf("ISUPTEST: Failed to send OGC Selected. CIC %d \n",
               hdr->context.CIC);
    }

    return ISUP_SendEXMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendFAARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
 
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending FAA Request ------\n");
    ReadISUPMsg(ISUP_MSG_FAA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendFAARequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendFACRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    TCAP_CPT     cpt;
 
    memset((char *)&ies, 0, sizeof(ies));
    memset((char *)&cpt, 0, sizeof(cpt));

    printf("------ Sending FAC Request ------\n");
    ReadISUPMsg(ISUP_MSG_FAC, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendFACRequest(handle, hdr, ies, ieCount, &cpt);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendFARRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending FAR Request ------\n");
    ReadISUPMsg(ISUP_MSG_FAR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendFARRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendFRJRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending FRJ Request ------\n");
    ReadISUPMsg(ISUP_MSG_FRJ, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendFRJRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends an ISUP Forward Transfer message.
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
int
TestSendFOTRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending FOT Request ------\n");
    ReadISUPMsg(ISUP_MSG_FOT, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendFOTRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends an ISUP Circuit Group Reset Acknowledgement
 *      message.
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
int
TestSendGRARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending GRA Request ------\n");
    ReadISUPMsg(ISUP_MSG_GRA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendGRARequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends an ISUP Circuit Group Reset message.
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
int
TestSendGRSRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending GRS Request ------\n");
    ReadISUPMsg(ISUP_MSG_GRS, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendGRSRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
int
TestSendIAMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending IAM Request ------\n");
    ReadISUPMsg(ISUP_MSG_IAM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendIAMRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendIDRRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending IDR Request ------\n");
    ReadISUPMsg(ISUP_MSG_IDR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendIDRRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Information message.
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
int
TestSendINFRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of information elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending INF Request ------\n");
    ReadISUPMsg(ISUP_MSG_INF, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendINFRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Information Request message.
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
int
TestSendINRRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending INR Request ------\n");
    ReadISUPMsg(ISUP_MSG_INR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    if (EXT_SelectCIC(handle, hdr, ISUP_MSG_ACM) == ITS_SUCCESS)
    {
        printf("ISUPTEST: OGC Selected sent. CIC %d \n", hdr->context.CIC);
    }
    else
    {
        printf("ISUPTEST: Failed to send OGC Selected. CIC %d \n",
               hdr->context.CIC);
    }

    return ISUP_SendINRRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendIRSRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending IRS Request ------\n");
    ReadISUPMsg(ISUP_MSG_IRS, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendIRSRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Resume message.
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
int
TestSendLPARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending LPA Request ------\n");
    ReadISUPMsg(ISUP_MSG_LPA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendLPARequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendNRMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending NRM Request ------\n");
    ReadISUPMsg(ISUP_MSG_NRM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendNRMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendOLMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending OLM Request ------\n");
    ReadISUPMsg(ISUP_MSG_OLM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendOLMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Pass Along message.
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
int
TestSendPAMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending PAM Request ------\n");
    ReadISUPMsg(ISUP_MSG_PAM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendPAMRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Release message.
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
int
TestSendRELRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending REL Request ------\n");
    ReadISUPMsg(ISUP_MSG_REL, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendRELRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Resume message.
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
int
TestSendRESRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending RES Request ------\n");
    ReadISUPMsg(ISUP_MSG_RES, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendRESRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Release Complete message.
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
int
TestSendRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending RLC Request ------\n");
    printf("No parameters for this message.\n");

    return ISUP_SendRLCRequest(handle, hdr, ies, ieCount);
}

int
TestSendResetRLCRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending Reset RLC Request ------\n");
    ReadISUPMsg(ISUP_MSG_RLC, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendResetRLCRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Reset Circuit message.
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
int
TestSendRSCRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending RSC Request ------\n");
    printf("No parameters for this message.\n");

    return ISUP_SendRSCRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Subsequent Address message.
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
#ifdef CCITT
int
TestSendSAMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending SAM Request ------\n");
    ReadISUPMsg(ISUP_MSG_SAM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendSAMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendSGMRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending SGM Request ------\n");
    ReadISUPMsg(ISUP_MSG_SGM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendSGMRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Suspend message.
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
int
TestSendSUSRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending SUS Request ------\n");
    ReadISUPMsg(ISUP_MSG_SUS, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendSUSRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Address Complete message.
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
int
TestSendUBARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    int          d_ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending UBA Request ------\n");
    return ISUP_SendUBARequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Unblocking message.
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
int
TestSendUBLRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    /* only have message tag as parameter */
    printf("------ Sending UBL Request ------\n");
    printf("No parameters for this message.\n");

    return ISUP_SendUBLRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendUPARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending UPA Request ------\n");
    ReadISUPMsg(ISUP_MSG_UPA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendUPARequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendUPTRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending UPT Request ------\n");
    ReadISUPMsg(ISUP_MSG_UPT, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendUPTRequest(handle, hdr, ies, ieCount);
}
#endif

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Initial Address message.
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
#ifdef CCITT
int
TestSendUSRRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];
    
    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending USR Request ------\n");
    ReadISUPMsg(ISUP_MSG_USR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendUSRRequest(handle, hdr, ies, ieCount);
}
#endif

