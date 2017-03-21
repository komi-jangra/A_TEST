/****************************************************************************
 *                                                                          *
 *     Copyright 2002 IntelliNet Technologies, Inc. All Rights Reserved.    *
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
 *  ID: $Id: isupUsage.c,v 1.1.1.1 2007-10-08 11:12:24 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:00  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:29  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:20  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:20  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:30  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:40  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 1.3  2002/06/28 16:39:10  hbalimid
 * LOG: ANSI & ITU Stack Handles
 * LOG:
 * LOG: Revision 1.2  2002/05/20 15:58:50  sjaddu
 * LOG: Merge from PR6, remove unwanted directories.
 * LOG:
 * LOG: Revision 1.1.2.2  2002/05/08 18:41:40  hbalimid
 * LOG: Added more comments
 * LOG:
 * LOG: Revision 1.1.2.1  2002/05/08 18:24:29  hbalimid
 * LOG: Baseline for the isupUsage demo
 * LOG:
 *
 ****************************************************************************/

/*
 * System Includes
 */
#include <stdio.h>

/*
 * IntelliSS7 Includes
 */
#include <engine.h>
#include <its_ss7_trans.h>

/*
 * IntelliNet ISUP Includes
 */
#include <isup_sn.h>
#include <itu/isup.h>

/*
 * Transport Handle For the ISUP send APIs
 */
if defined(CCITT)
#define HANDLE ISS7_CCITT_Stack
#elif defined(ANSI)
#define HANDLE ISS7_ANSI_Stack
#else
#error "Protocol not defined!"
#endif

/*
 * Destination Information
 */
const ITS_USHORT dpc = 0x14;
const ITS_USHORT opc = 0x0F;
const ITS_OCTET  sio = 0x85;


/*
 * Local functions'
 * Forward Declarations
 */

ITS_INT SendUBL(ITS_USHORT cic);
ITS_INT HandleUBL(ITS_EVENT* event);

ITS_INT SendUBA(ITS_USHORT cic);
ITS_INT HandleUBA(ITS_EVENT* event);

ITS_INT SendIAM(ITS_USHORT cic);
ITS_INT HandleIAM(ITS_EVENT* event);

ITS_INT SendACM(ITS_USHORT cic);
ITS_INT HandleACM(ITS_EVENT* event);

ITS_INT SendACM(ITS_USHORT cic);
ITS_INT HandleACM(ITS_EVENT* event);

ITS_INT SendANM(ITS_USHORT cic);
ITS_INT HandleANM(ITS_EVENT* event);

ITS_INT SendREL(ITS_USHORT cic);
ITS_INT HandleREL(ITS_EVENT* event);

ITS_INT SendRLC(ITS_USHORT cic);
ITS_INT HandleRLC(ITS_EVENT* event);

ITS_INT HandleRELAndSendRLC(ITS_EVENT* event);

void DumpITSEvent(ITS_EVENT* ev);
void WorkerThreadDispatchFunction(TPOOL_THREAD* thr, ITS_HANDLE handle);

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Send a UBL message out to network on the given cic
 *
 *  Input Parameters:
 *    circuit number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
SendUBL(ITS_USHORT cic)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    hdr.context.cic = cic;

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (cic & 0x000F) );
    ieIndex++;

    ieCount = ieIndex;

    res  = ISUP_SendUBLRequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending UBL for cic %d \n", cic);
        return (res);
    }

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Handle the incoming UBL message (from isup to app)
 *
 *  Input Parameters:
 *    retrieved event
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
HandleUBL(ITS_EVENT* event)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveUBLIndication(HANDLE, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleUBL:ISUP_ReceiveUBLIndication Failed!\n");
        return (res);
    }

    printf("cic for received UBL = %d\n", hdr.context.cic);
    printf("ieCount for received UBL = %d\n", ieCount);

    return (PrintISUPMsg(ies, ieCount));
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Send a UBA message out to network on the given cic
 *
 *  Input Parameters:
 *    circuit number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
SendUBA(ITS_USHORT cic)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    hdr.context.cic = cic;

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (cic & 0x000F) );
    ieIndex++;

    ieCount = ieIndex;

    res  = ISUP_SendUBARequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending UBA for cic %d \n", cic);
        return (res);
    }

    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Receive the incomig the UBA message (from isup to app)
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
HandleUBA(ITS_EVENT* event)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveUBAIndication(HANDLE, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleUBA:ISUP_ReceiveUBAIndication Failed!\n");
        return (res);
    }

    printf("cic for received UBA = %d\n", hdr.context.cic);
    printf("ieCount for received UBA = %d\n", ieCount);

    return (PrintISUPMsg(ies, ieCount));
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Send an IAM message out to network on the given cic
 *
 *  Input Parameters:
 *    circuit number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
SendIAM(ITS_USHORT cic)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    hdr.context.cic = cic;

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (cic & 0x000F) );
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_NATURE_CONN_INDICATORS;
    ies[ieIndex].param_length = sizeof(ISUP_CONNECTION_INDICATORS);
    ies[ieIndex].param_data.connectionIndicator.subfields4 = 0x00;
    
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_FWD_CALL_INDICATORS;
    ies[ieIndex].param_length = sizeof(ISUP_FORWARD_CALL_INDICATORS);
    ies[ieIndex].param_data.forwardCallIndicators.fwd_ci[0] = 0x20;
    ies[ieIndex].param_data.forwardCallIndicators.fwd_ci[1] = 0x01;
    
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_CALLING_PARTY_CATEGORY;
    ies[ieIndex].param_length = sizeof(ISUP_CALLING_PARTY_CATEGORY);
    ies[ieIndex].param_data.callingPartyCategory.cat = 0x0A;
    
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_TX_MEDIUM_REQMNT;
    ies[ieIndex].param_length = sizeof(ISUP_TX_MEDIUM_REQUIREMENT);
    ies[ieIndex].param_data.txMediumRequirement.tmr = 0x02;
    
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_CALLED_PARTY_NUM;
    ies[ieIndex].param_data.calledPartyNum.addr_ind = 0x01;
    ies[ieIndex].param_data.calledPartyNum.num_plan = 0x10;
    memset( &(ies[ieIndex].param_data.calledPartyNum.dgts), 1, MAX_NB_OCTETS_DIGITS);
    ies[ieIndex].param_length = sizeof(ISUP_CALLED_PARTY_NUM);
    
    ieIndex++;
    ieCount = ieIndex;
    
    printf("Number fo IEs filled in IAM = %d\n", ieCount);
    
    res  = ISUP_SendIAMRequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending IAM for cic %d \n", cic);
        return res;
    }
    
    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Receive the incoming the IAM message (from isup to app)
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
HandleIAM(ITS_EVENT* event)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveIAMIndication(HANDLE, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleIAM:ISUP_ReceiveIAMIndication Failed!\n");
        return (res);
    }

    printf("cic for received IAM = %d\n", hdr.context.cic);
    printf("ieCount for received IAM = %d\n", ieCount);

    return (PrintISUPMsg(ies, ieCount));
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Send an ACM message out to network on the given cic
 *
 *  Input Parameters:
 *    circuit number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
SendACM(ITS_USHORT cic)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;
    hdr.context.cic = cic;

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (cic & 0x000F) );
    ieIndex++;
    
    ies[ieIndex].param_id = ISUP_PRM_BKWD_CALL_INDICATORS;
    ies[ieIndex].param_length = sizeof(ISUP_BKWD_CALL_INDICATORS);
    ies[ieIndex].param_data.backwardCallIndicators.bkwd_ci[0] = 0x15;
    ies[ieIndex].param_data.backwardCallIndicators.bkwd_ci[1] = 0x14;

    ieIndex++;

    ieCount = ieIndex;

    printf("Number fo IEs filled in ACM = %d\n", ieCount);

    res  = ISUP_SendACMRequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending ACM for cic %d \n", cic);
        return res;
    }
    
    return (ITS_SUCCESS);
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *     Receive the incoming the ACM message (from isup to app)
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
HandleACM(ITS_EVENT* event)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveACMIndication(HANDLE, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleACM:ISUP_ReceiveACMIndication Failed!\n");
        return (res);
    }

    printf("cic for received ACM = %d\n", hdr.context.cic);
    printf("ieCount for received ACM = %d\n", ieCount);

    return (PrintISUPMsg(ies, ieCount));
}

/*
 * Dummy functions for ANM and REL
 * Can be implemented on the similar lines
 * as shown above for ACM
 */

ITS_INT
HandleANM(ITS_EVENT* event)
{
    /* .... */

    return (ITS_SUCCESS);
}

ITS_INT
HandleRLC(ITS_EVENT* event)
{
    /* .... */

    return (ITS_SUCCESS);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *    Process the incoming REL and send out RLC
 *
 *  Input Parameters:
 *    
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 *
 ****************************************************************************/
ITS_INT
HandleRELAndSendRLC(ITS_EVENT* event)
{
    ITS_ISUP_IE ies[ITS_MAX_ISUP_IES];
    ITS_INT ieCount = 0;
    ITS_INT ieIndex = 0;
    ITS_HDR hdr;
    ITS_INT res;

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    res = ISUP_ReceiveRELIndication(HANDLE, event, &hdr, ies, &ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleRELAndSendRLC: ISUP_ReceiveRELIndication Failed!\n");
        return (res);
    }

    printf("cic for received REL = %d\n", hdr.context.cic);
    printf("ieCount for received REL = %d\n", ieCount);

    res = PrintISUPMsg(ies, ieCount);
    if( res != ITS_SUCCESS )
    {
        printf("HandleRELAndSendRLC: PrintISUPMsg Failed!\n");
        return (res);
    }

    printf("cic for received REL = %d\n", hdr.context.cic);
    printf("ieCount for received REL = %d\n", ieCount);

    memset( (char*)&ies[0], 0, sizeof(ies) );
    memset( (char*)&hdr, 0, sizeof(ITS_HDR) );

    hdr.type = ITS_ISUP;

    /* cic is extracted from hdr in incomig REL */

    ieIndex = 0;

    ies[ieIndex].param_id = ISUP_PRM_ROUTING_LABEL;
    ies[ieIndex].param_length = sizeof(MTP3_HEADER);

    ISUP_SET_MTP3_HEADER( ies[ieIndex].param_data.routingLabel,
                             sio, opc, dpc, (hdr.context.cic & 0x000F) );
    ieIndex++;

    ieCount = ieIndex;

    printf("Number fo IEs filled in RLC = %d\n", ieCount);

    res  = ISUP_SendRLCRequest(HANDLE, &hdr, ies, ieCount);
    if(res != ITS_SUCCESS)
    {
        printf("Error in sending RLC for cic %d \n", hdr.context.cic);
        return res;
    }
    
    return (ITS_SUCCESS);
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      WorkerThreadDispatchFunction to receive incoming events from ISUP
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
WorkerThreadDispatchFunction(TPOOL_THREAD *thr, ITS_HANDLE handle)
{
    ITS_USHORT workerInstance;
    ITS_EVENT event;
    ITS_INT ret;

    WORKER_Control* worker = (WORKER_Control*)thr;
    workerInstance = worker->worker.instance;

    for(;;)
    {
        memset( &event, 0, sizeof(ITS_EVENT));
        ret = WORKER_GetNextEvent(worker, &event);
        if (ret != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(ret));
        }
        DumpITSEvent(&event);
    
        if ( event.src == ITS_ISUP_SRC )
        {
            printf("Worker Thread: ISUP msg *%s* receive success; Msg is %d\n",
                    ISUP_GetMsgName(event.data[0]), event.data[0] );
        }
    
        switch( event.data[0] )
        {
            case ISUP_MSG_UBL:
                HandleUBL(&event);
                break;
    
            case ISUP_MSG_UBA:
                HandleUBA(&event);
                break;
    
            case ISUP_MSG_IAM:
                HandleIAM(&event);
                break;
    
            case ISUP_MSG_ACM:
                HandleACM(&event);
                break;
    
            case ISUP_MSG_ANM:
                HandleANM(&event);
                break;
    
            case ISUP_MSG_REL:
                HandleRELAndSendRLC(&event);
                break;
    
            case ISUP_MSG_RLC:
                HandleRLC(&event);
                break;
    
            default:
                printf("Invalid Message:\n");
                break;
        }

        ITS_EVENT_TERM(&event);
    }

    return;
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Dumps the given ITS Event
 *
 *  Input Parameters:
 *      event to be dumped
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
DumpITSEvent(ITS_EVENT* ev)
{
    ITS_INT i;

    ITS_C_ASSERT( ev != NULL );

    switch(ev->src)
    {
        case ITS_ISUP_CCITT_SRC:
             printf("Event Source is ITS_ISUP_CCITT_SRC\n");
             break;
        case ITS_ISUP_ANSI_SRC:
             printf("Event Source is ITS_ISUP_ANSI_SRC\n");
             break;
        case ITS_MTP3_CCITT_SRC:
             printf("Event Source is ITS_MTP3_CCITT_SRC\n");
             break;
        case ITS_MTP3_ANSI_SRC:
             printf("Event Source is ITS_MTP3_ANSI_SRC\n");
             break;
        case ITS_TIMER_SRC:
             printf("Event Source is ITS_TIMER_SRC\n");
             break;
        default:
             printf("Event Source is * UNKNOWN * (%d)\n", ev->src);
             break;
    }

    printf("\nEvent came from: %d\n",ev->src);
    printf("The length was:  %d\n", ev->len);

    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);
        if (!((i+1) % 20))
        {
            printf("\n");
        }
    }
    if ((i+1) % 20)
    {
        printf("\n");
    }
}


/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      main program
 *
 *  Input Parameters:
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITS_INT
main(int argc, const char* argv[])
{
    const ITS_USHORT MAXPATH = 256;
    ITS_CHAR path[MAXPATH];

    memset( path, 0, MAXPATH );
    ITS_C_ASSERT( getcwd(path, MAXPATH) != NULL );
    strcat( path, "/" );

    printf("Path = %s\n", path);

    APPL_SetConfigDir(path);
    APPL_SetName("test");
    APPL_SetConfigFileExtension("xml");

    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}
/*****************************************************************************/
