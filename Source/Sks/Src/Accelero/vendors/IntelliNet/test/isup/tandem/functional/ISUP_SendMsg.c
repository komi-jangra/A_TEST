/****************************************************************************
 *                                                                          *
 *     Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 * ID:$Id: ISUP_SendMsg.c,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 * LOG:$Log: not supported by cvs2svn $
 * LOG:Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG:init tree
 * LOG:
 * LOG:Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG:BscCs2
 * LOG:
 * LOG:Revision 1.1.1.1  2007/03/08 15:15:19  cvsadmin
 * LOG:BSC project
 * LOG:
 * LOG:Revision 9.1  2005/03/23 12:55:19  cvsadmin
 * LOG:Begin PR6.5
 * LOG:
 * LOG:Revision 1.1  2003/02/19 15:35:50  vnitin
 * LOG:Add functional tester for Tandem
 * LOG:
 * LOG:Revision 1.2  2003/01/28 14:47:42  ssingh
 * LOG:Initial Checkin for Automated ISUP functional application.
 * LOG:
 ****************************************************************************/

#include <stdio.h>
#include <memory.h>

#include <its.h>
#if defined(CCITT)
#include <itu/isup.h>
#elif defined(ANSI)
#include <ansi/isup.h>
#endif

#include "ISUP_ReadMsg.h"
#include "ISUP_SendMsg.h"
#include "ISUP_PrintMsg.h"
#include "ISUP_ProcessMsg.h"

extern ITS_HANDLE Tandem_handle;

#define ISS7_Stack Tandem_handle


static char filename[50] = FILENAME;

char*
GetFilename()
{
    return filename;
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
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending ACM Request ------\n");

    ReadISUPMsg(ISUP_MSG_ACM, filename, &(ies[0]), &ieCount);

    PrintISUPMsg(ies, ieCount);
    result = ISUP_SendACMRequest(handle, hdr, ies, ieCount);

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_ACM, (ITS_USHORT)hdr->context.cic,
                              &(ies[0]), ieCount);

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

    ReadISUPMsg(ISUP_MSG_ANM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);
    result = ISUP_SendANMRequest(handle, hdr, ies, ieCount);

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_ANM, (ITS_USHORT)hdr->context.cic,
                              &(ies[0]), ieCount);

    return result;
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Blocking Acknowledge message.
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
TestSendBLARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending BLA Request ------\n");
    printf("No parameters for this message.\n");

    ReadISUPMsg(ISUP_MSG_BLA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);


    return ISUP_SendBLARequest(handle, hdr, ies, ieCount);
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

    ReadISUPMsg(ISUP_MSG_BLO, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

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

    ReadISUPMsg(ISUP_MSG_CCR, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);


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
 *      This function send an ISUP Circuit Group Block Ack message.
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
TestSendCGBARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{   
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CGBA Request ------\n");
    ReadISUPMsg(ISUP_MSG_CGBA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCGBARequest(handle, hdr, ies, ieCount);
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

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_COT, (ITS_USHORT)hdr->context.cic,
                              &(ies[0]), ieCount);

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
 *      This function send an Facility message.
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
#if defined(CCITT) || ( defined (ANSI) && defined (ANSI_ISUP_95) )
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

    /* mark Circuits transient */
    ISUP_HandleOutgoingGRSMsg((ITS_USHORT)hdr->context.cic, &(ies[0]), ieCount);

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
    int ret = ITS_SUCCESS;

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending IAM Request ------\n");
    ReadISUPMsg(ISUP_MSG_IAM, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_IAM, (ITS_USHORT)hdr->context.cic, &(ies[0]), ieCount);

    ret = ISUP_SendIAMRequest(handle, hdr, ies, ieCount);

    if(ret != ITS_SUCCESS)
    {
       ISUP_UpdateCicStatus((ITS_USHORT)hdr->context.cic);
    }
    return ret;
}

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

    return ISUP_SendINRRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Loopback Acknowledgement message.
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

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_REL, (ITS_USHORT)hdr->context.cic, &(ies[0]), ieCount);

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

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_RES, (ITS_USHORT)hdr->context.cic, &(ies[0]), ieCount);

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

    ReadISUPMsg(ISUP_MSG_RLC, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendRLCRequest(handle, hdr, ies, ieCount);
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

    ReadISUPMsg(ISUP_MSG_RSC, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    /* Mark Circuit Transient */
    ISUP_HandleOutgoingRSCMsg((ITS_USHORT)hdr->context.cic);

    return ISUP_SendRSCRequest(handle, hdr, ies, ieCount);
}

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

    /* Update FSM/CIC state */
    ISUP_HandleOutgoingCPCMsg(ISUP_MSG_SUS, (ITS_USHORT)hdr->context.cic, &(ies[0]),
                              ieCount);

    return ISUP_SendSUSRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Unblocking Acknowledgement message.
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
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending UBA Request ------\n");

    ReadISUPMsg(ISUP_MSG_UBA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

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

    ReadISUPMsg(ISUP_MSG_UBL, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendUBLRequest(handle, hdr, ies, ieCount);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP UCIC message.
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
TestSendUCICRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending UCIC Request ------\n");

    printf("No parameters for this message.\n");

    ReadISUPMsg(ISUP_MSG_UCIC, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendUCICRequest(handle, hdr, ies, ieCount);

}

/****************************************************************************/
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
 *      This function send an Facility Accepted message.
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
 *      This function send an Facility Request message.
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
 *      This function send an ISUP Facility Reject message.
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
 *      This function send an ISUP Identification Request message.
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
 *      This function send an ISUP Identification Response message.
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
 *      This function send an ISUP Network Resource Management message.
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
 *      This function send an ISUP Initial OverLoad message.
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
 *      This function send an ISUP Segmentation message.
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
 *      This function send an ISUP Userpart Available message.
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
    int          ieCount = 0;
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
 *      This function send an ISUP Userpart Test message.
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
    int          ieCount = 0;
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
 *      This function sends an ISUP User to User Information message.
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

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function sends an Loop Preventition message. (LOP)
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
#if defined (CCITT) && defined (ITU_ISUP_97)
int
TestSendLOPRequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;       /* no. of iinformation elements */
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending LOP Request ------\n");
    ReadISUPMsg(ISUP_MSG_LOP, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendLOPRequest(handle, hdr, ies, ieCount);
}
#endif

/****************************************************************************/

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      This function send an ISUP Circuit Reservation Ack message.
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
TestSendCRARequest(ITS_HANDLE handle, ITS_HDR *hdr)
{
    int          ieCount = 0;
    ITS_ISUP_IE  ies[ITS_MAX_ISUP_IES];

    memset((char *)&ies, 0, sizeof(ies));

    printf("------ Sending CRA Request ------\n");
    ReadISUPMsg(ISUP_MSG_CRA, filename, &(ies[0]), &ieCount);
    PrintISUPMsg(ies, ieCount);

    return ISUP_SendCRARequest(handle, hdr, ies, ieCount);
}
#endif


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

    return ISUP_SendEXMRequest(handle, hdr, ies, ieCount);
}
#endif

/****************************************************************************/
