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
 * ID: $Id: test.c,v 1.1.1.1 2007-10-08 11:11:29 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:23:59  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:48:55  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:13:34  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:52:42  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.10  2003/11/11 05:59:41  ssingh
 * LOG: TCAP_AllocateLocalDID changed.
 * LOG:
 * LOG: Revision 1.9  2003/10/23 06:43:03  ssingh
 * LOG: Uni and Begin build changed.
 * LOG:
 * LOG: Revision 1.8  2003/10/22 07:12:27  sswami
 * LOG: Changes done to Send more than one components with a Dialogue
 * LOG:
 * LOG: Revision 1.7  2003/10/21 09:20:50  ssingh
 * LOG: After receiving event from STACK, redisplay of menu is removed
 * LOG: to get the the sending thread out from hangin.
 * LOG:
 * LOG: Revision 1.6  2003/10/17 14:33:50  ssingh
 * LOG: Handling of UNI return value used.
 * LOG:
 * LOG: Revision 1.5  2003/10/17 13:48:07  ssingh
 * LOG: Changes done for multiple component handling.
 * LOG:
 * LOG: Revision 1.4  2003/10/17 09:05:01  ssingh
 * LOG: Format changes done.
 * LOG:
 * LOG: Revision 1.3 2003/10/17 02:42:03  sswami
 * LOG: Changes to Handel End and Abort Messages
 * LOG:
 * LOG: Revision 1.2  2003/10/10 04:42:03  sswami
 * LOG: New function to allocate local DID is implemented
 * LOG:
 * LOG: Revision 1.1  2003/10/07 12:26:08  sswami
 * LOG: Test Client
 * LOG:
 ****************************************************************************/
#include <tcap_clientapi.h>
#include <tcap_clientimpl.h>
#include <engine.h>
#include <pthread.h>
#include <signal.h>

/* gloabal variables */
ITS_HANDLE CL_Handle;
static ITS_CTXT nextDID = 1;

/* public variable */
static char* hostIpAddress;
static int serverPort;
char*  style;
extern ITS_HANDLE CL_Handle;

extern ITS_USHORT did;

SS7TRAN_Manager*     ISS7_ANSI_Stack;
#define ISS7_Stack   ISS7_ANSI_Stack

#define SEND_UNI           1
#define SEND_BEGIN         2
#define SEND_END           3
#define SEND_CONTINUE      4
#define SEND_ABORT         5
#define DUMP_RT            6
#define SEND_LOOP          7


#if defined(ANSI)
#define PROTOCOL_VERSION_TAG                  (0xDAU)
#define AC_NAME_TAG                           (0xDCU)
#define USER_INFO_TAG                         (0xFDU)
#define PABT_CAUSE_TAG                        (0xD7U)
#define TCPPN_SEQUENCE_TAG                    (0x30U)
#define TCPPN_SET_TAG                         (0xF2U)
#define U_ABORT_INFO_TAG                      (0xD8U)
//#define TCPPT_TC_INVOKE                       (0xE9U)
#endif

SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_GlobalTitleTranslator = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_SSNRoutingCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* SCCP_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* MTP3_ANSI_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_CCITT_ManagementCallbacks = NULL;
SS7DLLAPI CALLBACK_Manager* ISUP_ANSI_ManagementCallbacks = NULL;

SS7DLLAPI int SCCP_DecodeAddr_ANSI(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                   ITS_UINT* pc, ITS_OCTET *ssn,
                                   ITS_OCTET* gttInfo, ITS_USHORT* gttLen);
SS7DLLAPI int SCCP_EncodeAddr(SCCP_ADDR *addr, ITS_OCTET addrInd,
                                   ITS_UINT pc, ITS_OCTET ssn,
                                   const ITS_OCTET* gttInfo, 
                                   ITS_USHORT gttLen);

#if defined(CCITT)
#define SCCP_GlobalTitleTranslator  SCCP_CCITT_GlobalTitleTranslator
#elif defined(ANSI)
#define SCCP_GlobalTitleTranslator  SCCP_ANSI_GlobalTitleTranslator
#endif

static void TCAP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event);
void InputMenu();
void *PrintMenu();

SS7DLLAPI int
SCCP_EncodeAddr(SCCP_ADDR *addr, ITS_OCTET addrInd,
                ITS_UINT pc, ITS_OCTET ssn,
                const ITS_OCTET* gttInfo, ITS_USHORT gttLen)
{
    int offset = 1;

    if (addr == NULL)
    {
        return (ITS_EMISSMAND);
    }

    addr->data[0] = addrInd;

#if defined(ANSI)

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_ANSI_SET_PC(&addr->data[offset], pc);
        offset += 3;
    }

#elif defined(CCITT)
    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_ITU_SET_PC(&addr->data[offset], pc);
        offset += 2;
    }

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

#elif defined(PRC)

    if (addrInd & SCCP_CPA_HAS_PC)
    {
        SCCP_PRC_SET_PC(&addr->data[offset], pc);
        offset += 3;
    }

    if (addrInd & SCCP_CPA_HAS_SSN)
    {
        addr->data[offset] = ssn;
        offset++;
    }

#endif

    addr->len = (ITS_USHORT)offset;

    if (gttLen)
    {
        memcpy(&addr->data[offset], gttInfo, gttLen);
        addr->len += gttLen;
    }

    return (ITS_SUCCESS);
}

/* signal handling function */
static void
SignalHandler(int sig)
{
    printf("Terminating TCAP client application\n");
    CL_CloseConnection(CL_Handle);
    exit(0);
}
    
/* Forward declarations */
static void* Receive(void* args);

static void HandleAppEvent(ITS_EVENT *evt);

static int InitClient();
SS7DLLAPI int SCCP_DecodeAddr_ANSI(const SCCP_ADDR *addr, ITS_OCTET* addrInd,
                                   ITS_UINT* pc, ITS_OCTET *ssn,
                                   ITS_OCTET* gttInfo, ITS_USHORT* gttLen)
{
return 0;
}

int main(int argc, const char** argv)
{
    pthread_t thread, threadPrint;
    int ret =0;

    signal(SIGINT, SignalHandler);

    if(argc < 3)
    {
        printf("Usage : ./test <serverIP> <serverport> <Route_Style>\n");
        return(-1);
    }

    printf("\n\t *******************************************\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****  IntelliSS7 TCAP Client Test     *****\n");
    printf("\t *******************************************\n\n\n");

    hostIpAddress = (char*)argv[1];
    serverPort    = atoi(argv[2]);
    style = (char*)argv[3];
    /* Bind the client app with server and register
     * the list of opc,dpc,ni
     */
    ret = InitClient();
    if (ret == ITS_SUCCESS)
    {
        printf("Client Initialization success\n");
    }

    /* Dispatch a new thread to receive event from server */
    pthread_create(&thread, NULL, Receive, NULL);

    pthread_create(&threadPrint, NULL, PrintMenu, NULL);

    /* Set the application name */
    APPL_SetName("Client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");

    ENGINE_Initialize(argc, argv, NULL, 0);
    return(ENGINE_Run(argc, argv));

#if 0
    pthread_t thread;
    int ret =0;

    signal(SIGINT, SignalHandler);

    if(argc < 3)
    {
        printf("Usage : ./test <serverIP> <serverport> \n");
        return(-1);
    }

    printf("\n\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****  IntelliSS7 TCAP Client Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n\n\n");

    hostIpAddress = (char*)argv[1];
    serverPort    = atoi(argv[2]);

    /* Bind the client app with server and register 
     * the list of opc,dpc,ni 
     */
    ret = InitClient();
    if (ret == ITS_SUCCESS)
    {   
        printf("Client Initialization success\n");
    } 

    /* Dispatch a new thread to receive event from server */
    pthread_create(&thread, NULL, Receive, NULL);
    
    PrintMenu();
    /* Set the application name */
    APPL_SetName("Client");

    /* Set the application extension */
    APPL_SetConfigFileExtension("xml");
 
    ENGINE_Initialize(argc, argv, NULL, 0);

    return(ENGINE_Run(argc, argv));
#endif
}

void *
PrintMenu()
{
    int  yes = 1;
    for (;;)
    {
        InputMenu();
        printf("\n Enter 1 to Display Menu or 99 to Exit : ");
        scanf("%d", &yes);
        if (yes == 99)
        exit(0);
    }
}

void
InteractiveSendUniDlg()
{
    ITS_HDR hdr;
    MTP3_HEADER hdr3;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    int  invokeCount;
    int j;
    int invokeId, i, ret;
    ITS_CTXT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_UINT opc = 0, dpc = 0;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
    addrInd |= SCCP_CPA_ROUTE_NAT;

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);
    hdr3.sio = 0x83;

    pointCode = opc;
    ssn = 2;
    
    SCCP_EncodeAddr(&dlg->u.uni.orig_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    pointCode = dpc;
    SCCP_EncodeAddr(&dlg->u.uni.dest_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    TCAP_AllocateLocalDID(&localDid);
    printf("Allocated Local DID =  %d",localDid);
    /* Set did */

    /* Set did */
    hdr.context.dialogue_id = localDid;
    printf("\n did value = %d\n", hdr.context.dialogue_id);
    hdr.type = ITS_TCAP;

    /*Set ptype*/
    dlg->ptype = TCAP_PT_TC_UNI_ANSI;

    /* Set opc dpc*/
    MTP3_PC_SET_VALUE(dlg->u.uni.opc, opc);
    MTP3_PC_SET_VALUE(dlg->u.uni.dpc, dpc);

    printf("\n======> How many invokes? <======\n");
    scanf("%d",&invokeCount);

    for (j = 1; j <= invokeCount; j++)
    {
        printf("\n========> Enter Invoke Id: <======== \n");
        scanf("%d", &invokeId);
        cpt->ptype = TCPPT_TC_INVOKE;
        /* Set Invoke Id*/
        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = invokeId;

        /* Set Op*/
        cpt->u.invoke.operation.len = 4;
        cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        cpt->u.invoke.operation.data[1] = 2;
        cpt->u.invoke.operation.data[2] = 1;
        cpt->u.invoke.operation.data[3] = 2;
        
        /* Set Param*/
        cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;  
        cpt->u.invoke.param.data[1] = 10;
        for (i = 2; i<10;i++)
        {
            cpt->u.invoke.param.data[i] = i;
        }
        ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt); 
        if (ret == ITS_SUCCESS)
        {
            printf("\n Component Sent successfully:Invoke Id = %d",
                    invokeId);
        }
    }

    ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n UNI Dialogue Sent successfully\n");
    }
    else
    {
        printf("\n Failed to send the UNI Dialogue\n");
    }
}

void
InteractiveSendBeginDlg()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int  invokeCount, ret ;
    int invokeId, i, j, input;
    ITS_CTXT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_UINT opc = 0, dpc = 0;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
    addrInd |= SCCP_CPA_ROUTE_NAT;
    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);

    hdr3.sio = 0x83;
    pointCode = MTP3_PC_GET_VALUE(hdr3.label.opc);
    printf("\n OPC = %d\n", pointCode);
    ssn = 2;

    SCCP_EncodeAddr(&dlg->u.begin.orig_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    pointCode = MTP3_PC_GET_VALUE(hdr3.label.dpc);
    SCCP_EncodeAddr(&dlg->u.begin.dest_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    TCAP_AllocateLocalDID(&localDid);
    printf("Allocated Local DID =  %d",localDid);

    /* Set did */
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;

    /*Set ptype*/
    printf("\nEnter 1 for QWP and 2 for QWOP::\n");
    scanf ("%d",&input);
    if (input == 1)
    {
        dlg->ptype = TCAP_PT_TC_QUERY_W_PERM_ANSI;
    }
    else
    {
       dlg->ptype = TCAP_PT_TC_QUERY_WO_PERM_ANSI;
    }

    /* Set opc dpc*/
    MTP3_PC_SET_VALUE(dlg->u.begin.opc, opc);
    MTP3_PC_SET_VALUE(dlg->u.begin.dpc, dpc);

    printf("\n======> How many invokes? <======\n");
    scanf("%d",&invokeCount);

    for (j = 1; j <= invokeCount; j++)
    {
        printf("\n========> Enter Invoke Id: <======== \n");
        scanf("%d", &invokeId);
        cpt->ptype = TCPPT_TC_INVOKE;
        /* Set Invoke Id*/
        cpt->u.invoke.invoke_id.len = 3;
        cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
        cpt->u.invoke.invoke_id.data[1] = 1;
        cpt->u.invoke.invoke_id.data[2] = invokeId;

        /* Set Op*/
        cpt->u.invoke.operation.len = 4;
        cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
        cpt->u.invoke.operation.data[1] = 2;
        cpt->u.invoke.operation.data[2] = 1;
        cpt->u.invoke.operation.data[3] = 2;

        /* Set Param*/
        cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;
        cpt->u.invoke.param.data[1] = 10;
        for (i = 2; i<10;i++)
        {
            cpt->u.invoke.param.data[i] = i;
        }
        ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);
        if (ret == ITS_SUCCESS)
        {
            printf("\n Component Sent successfully:Invoke Id = %d",
                    invokeId);
        }
    }
    ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg);
    if (ret == ITS_SUCCESS)
    {
        printf("\n Dialogue Sent successfully");
    }
    else
    {
        printf("Failed to send the Dialogue\n");
    }
    return;
}

void
InteractiveSendEnd()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int numResult = 0, outcome = 0; 
    int invokeId, i, ret;
    int resNL, failure;
    //ITS_CTXT localDid;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT opc = 0, dpc = 0;
    ITS_UINT rejectType, errorcode;
    ITS_UINT rejectCode; 

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
    addrInd |= SCCP_CPA_ROUTE_NAT;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    dlg->ptype = TCPPT_TC_RESP;

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);
    hdr3.sio = 0x83;
  
    /* Set did */
    printf("\n Enter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;
    printf("Sending END on DID == %d", localDid);
    printf("\n OutCome of transaction (1-success, 0-failure) ? \n");
    scanf ("%d",&outcome);
    if (outcome == 1)
    {
        printf("\nHow Many return Results ?\n");
        scanf ("%d" , &numResult);
        for ( i = 0;i < numResult; i ++)
        {
            printf("\n Enter \"0\" for RET_RES_NOT_LAST,"
                   " \"1\" for RET_RES_LAST:");
            scanf("%d" ,&resNL);
            if (resNL == 0)
            {
                cpt->ptype = TCPPT_TC_RESULT_NL;
            }
            else if (resNL == 1)
            {
                cpt->ptype = TCPPT_TC_RESULT_L;
            }
            printf("\n Enter Invoke ID\n");
            scanf("%d" , &invokeId);
            cpt->u.result.invoke_id.len = 3;
            cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.result.invoke_id.data[1] = 1;
            cpt->u.result.invoke_id.data[2] = invokeId;
   
            ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);
             if(ret == ITS_SUCCESS)
             {
                  printf("\n TCAP_Comp RESULT send successful");
             }
             else
             {
                 printf("\n TCAP_Comp RESULT send failed\n");
             }
        }
    }
    else
    {
        printf("\nChoose 0 for ReturnError or 1 for Reject\n");
        scanf("%d", &failure);
        if (failure == 1)
        {
            cpt->ptype = TCPPT_TC_REJECT;
            printf("\n Enter Invoke ID \n");
            scanf("%d" , &invokeId);
            cpt->u.reject.invoke_id.len = 3;
            cpt->u.reject.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.reject.invoke_id.data[1] = 1;
            cpt->u.reject.invoke_id.data[2] = invokeId;
            printf("\n Enter reject Type [128 - 131]:\n"); 
            scanf("%d", &rejectType);
            printf("\n Enter Reject Code \n");
            scanf("%d" , &rejectCode); 
           
            /* Set the Problem Type and Code */
            cpt->u.reject.problem.len = 4;
            cpt->u.reject.problem.data[0] = TCPPROB_IDENT;
            cpt->u.reject.problem.data[1] = 2;
            cpt->u.reject.problem.data[2] = 1;
            cpt->u.reject.problem.data[3] = rejectCode;
            //hasProblem = true;

        }
        else 
        {
            cpt->ptype = TCPPT_TC_ERROR;
            printf("\n Enter Invoke ID \n");
            scanf("%d" , &invokeId);
            cpt->u.error.invoke_id.len = 3;
            cpt->u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.error.invoke_id.data[1] = 1;
            cpt->u.error.invoke_id.data[2] = invokeId;
            printf("\n Enter Error Code \n");
            scanf("%d" , &errorcode); 

            /* Set The Error code */
            cpt->u.error.error.len = 3;
            cpt->u.error.error.data[0] = 1;
            cpt->u.error.error.data[1] = 1;
            cpt->u.error.error.data[2] = errorcode;
            //hasError = true;
        }    
        ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);
        if (ret ==ITS_SUCCESS)
        {
           printf("\nTCAP_Comp RESULT sent successfully\n");
        }
        else
        {
            printf("TCAP_Comp RESULT failed to send.:\n");
        }
    } /* End of Else */

    ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg);
    if ( ret != ITS_SUCCESS) 
    {
        printf("\nFailed to send the END Dialogue \n");
    }  
    else
    {
        printf("\nEND Dialogue sent successfully\n");
    }
} 

void
InteractiveSendContinue()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg ;
    TCAP_CPT* cpt;
    MTP3_HEADER hdr3;
    int numResult = 0, invokeCount;
    int ErrorCode;
    int invokeId, i, j;
    int input,ret,resNL;
    //ITS_CTXT localDid;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;
    ITS_UINT pointCode = 0, opc = 0, dpc = 0;
    ITS_OCTET ssn;

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
    addrInd |= SCCP_CPA_ROUTE_NAT;

    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    memset(&hdr3, 0, sizeof(MTP3_HEADER));
    printf("\n Enter the opc value\n");
    scanf("%d", &opc);
    printf("\n Enter the dpc value\n");
    scanf("%d", &dpc);
    MTP3_RL_SET_OPC_VALUE(hdr3.label, opc);
    MTP3_RL_SET_DPC_VALUE(hdr3.label, dpc);

    hdr3.sio = 0x83;

    pointCode = MTP3_PC_GET_VALUE(hdr3.label.opc);
    printf("\n OPC = %d\n", pointCode);
    ssn = 2;

    SCCP_EncodeAddr(&dlg->u.begin.orig_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    pointCode = MTP3_PC_GET_VALUE(hdr3.label.dpc);
    SCCP_EncodeAddr(&dlg->u.begin.dest_addr, addrInd,
                    pointCode, ssn, NULL, 0);

    printf("\n Enter \"1\" for CONV_WO_PERM \"2\" for CONV_W_PERM \n");
    scanf("%d",&input);
    if (input == 1)
    {
        /*Set ptype*/
        dlg->ptype = TCPPT_TC_CONV_WO_PERM;
    }
    else
    {
        dlg->ptype = TCPPT_TC_CONV_W_PERM;
    }

    /* Set did */
    printf("\n Enter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;
    hdr.type = ITS_TCAP;

    printf("\n Enter - \"1\" for Return Result & Invoke Component \n "
             " Enter - \"0\" for Error Component\n");
    scanf("%d",&input);
    if (input == 1)
    {
        printf("\n How many Return Results? \n");
        scanf("%d",&numResult);
        for (i = 0; i < numResult; i++)
        {
            printf("\n Enter \"1\" for RET_RES_NOT_LAST \n"
                     " Enter \"0\" for RET_RES_LAST: \n");
            scanf("%d",&resNL);
            if (resNL == 1)
            {
                cpt->ptype = TCPPT_TC_RESULT_NL;
            }
            else
            {
                cpt->ptype = TCPPT_TC_RESULT_L;
            }

            printf("\n========> Enter Invoke Id: <======== \n");
            scanf("%d", &invokeId);
            cpt->ptype = TCAP_PT_TC_RESULT_L_ANSI;
            /* Set Invoke Id*/
            cpt->u.result.invoke_id.len = 3;
            cpt->u.result.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.result.invoke_id.data[1] = 1;
            cpt->u.result.invoke_id.data[2] = invokeId;
#if defined(CCITT)
            /* Set Op*/
            cpt->u.result.operation.len = 4;
            cpt->u.result.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
            cpt->u.result.operation.data[1] = 2;
            cpt->u.result.operation.data[2] = 1;
#endif
            /* Set Param*/
            cpt->u.result.param.data[0] = TCPPN_SET_TAG;
            cpt->u.result.param.data[1] = 10;
            for (i = 2; i<10;i++)
            {
                cpt->u.invoke.param.data[i] = i;
            }

            ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);
            if (ret ==ITS_SUCCESS)
            {
                printf("TCAP_Comp RESULT send success:\n");
            }
            else
            {
                printf("TCAP_Comp RESULT failed to send.:\n");
            }
        }

        printf("\nHow many Invokes? \n");
        scanf("%d", &invokeCount);
        for (j = 1; j <= invokeCount; j++)
        {
            printf("\n========> Enter Invoke Id: <======== \n");
            scanf("%d", &invokeId);
            cpt->ptype = TCPPT_TC_INVOKE;
            /* Set Invoke Id*/
            cpt->u.invoke.invoke_id.len = 3;
            cpt->u.invoke.invoke_id.data[0] = TCPPN_INVOKE_TAG;
            cpt->u.invoke.invoke_id.data[1] = 1;
            cpt->u.invoke.invoke_id.data[2] = invokeId;

            /* Set Op*/
            cpt->u.invoke.operation.len = 4;
            cpt->u.invoke.operation.data[0] = TCPPN_OCI_NATIONAL_TCAP;
            cpt->u.invoke.operation.data[1] = 2;
            cpt->u.invoke.operation.data[2] = 1;
            cpt->u.invoke.operation.data[3] = 2;

            /* Set Param*/
            cpt->u.invoke.param.data[0] = TCPPN_SET_TAG;
            cpt->u.invoke.param.data[1] = 10;

            for (i = 2; i<10;i++)
            {
                cpt->u.invoke.param.data[i] = i;
            }

            ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);

            if (ret ==ITS_SUCCESS)
            {
                printf("TCAP_Comp INVOKE send success:\n");
            }
            else
            {
                printf("TCAP_Comp INVOKE send failed:\n");
            }
        }
   } /* End of case 1 */

   /*case for ERROR Component */
   else if (input == 0)
   {
       cpt->ptype = TCPPT_TC_ERROR;
       printf( "\nEnter Invoke Id: \n");
       scanf("%d",&invokeId);
       cpt->u.error.invoke_id.len = 3;
       cpt->u.error.invoke_id.data[0] = TCPPN_INVOKE_TAG;
       cpt->u.error.invoke_id.data[1] = 1;
       cpt->u.error.invoke_id.data[2] = invokeId;

       printf("\n Enter Error Code: \n");
       scanf("%d",&ErrorCode);

       cpt->u.error.error.data[0] = TCPPN_ECI_NATIONAL_TCAP;
       cpt->u.error.error.data[1] = 1;
       cpt->u.error.error.data[2] = ErrorCode;
       ret = TCAP_SendComponent_ANSI(ISS7_Stack, &hdr,cpt);
       if (ret ==ITS_SUCCESS)
       {
           printf("TCAP_Comp ERROR send success:\n");
       }
       else
       {
           printf("TCAP_Comp ERROR failed to send.:\n");
       }
   }     /* End of ERROR Component */

   ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg);
   if (ret == ITS_SUCCESS)
   {
       printf("\n Continue Dialogue Sent successfully\n");
   } 
   else
   {
      printf("\n Failed to send the Continue Dialogue\n");
   }
}

void
InteractiveSendAbort()
{
    ITS_HDR hdr;
    TCAP_DLG* dlg;
    TCAP_CPT* cpt;
    //ITS_CTXT localDid;
    ITS_UINT abortReason; 
    int ret;
    ITS_UINT localDid;
    ITS_OCTET addrInd = 0;

    addrInd |= SCCP_CPA_HAS_PC_ANSI;
    addrInd |= SCCP_CPA_HAS_SSN_ANSI;
    addrInd |= SCCP_CPA_ROUTE_SSN;
    addrInd |= SCCP_CPA_ROUTE_NAT;
    dlg = (TCAP_DLG*)calloc(1, sizeof(TCAP_DLG));
    cpt = (TCAP_CPT*)calloc(1, sizeof(TCAP_CPT));

    dlg->ptype = TCPPT_TC_ABORT;
    printf("\nEnter DID\n");
    scanf("%d", &localDid);
    hdr.context.dialogue_id = localDid;

    printf("\n Enter the abort Reason \n");
    scanf("%d" ,&abortReason);
    dlg->u.abort.abort_reason = abortReason;
    /* Set the Abort Info */ 
   
    dlg->u.abort.abort_info.len = 3;
    dlg->u.abort.abort_info.data[0] = 0xd8;
    dlg->u.abort.abort_info.data[1] = 0x01;
    dlg->u.abort.abort_info.data[1] = 0x01; 

    /* Send the Dialogue */
    ret = TCAP_SendDialogue_ANSI(ISS7_Stack, &hdr, dlg); 
    if (ret != ITS_SUCCESS)
    {
        printf("\nFailed to send the ABORT Dialogue\n");
    }    
    else
    {
        printf("Successfully sent the ABORT Dialogue \n");
    }
}

void
InputMenu()
{
    ITS_INT val = 0;

    while(val < 1 || val > 5 )
    {
        printf("\n===> 1 - Initiate Transaction - TC_Uni.    <===");
        printf("\n===> 2 - Initiate Transaction - TC_Begin.  <===");
        printf("\n===> 3 - Close Transaction - TC_End.       <===");
        printf("\n===> 4 - Continue Transaction - TC_Continue.<===");
        printf("\n===> 5 - Abort Transaction - TC_Abort.      <===");
        printf("\n===> 99 - Exit                              <===\n");
        
        scanf("%d", &val);

        if ( val == 99)
        {
            exit(0);
        }
    } 

    switch (val)
    {
    case SEND_UNI:
        InteractiveSendUniDlg();
        break;

    case SEND_BEGIN:
        InteractiveSendBeginDlg();
        return;
        break;

    case SEND_END:
        InteractiveSendEnd();
        break;

    case SEND_CONTINUE:
        InteractiveSendContinue();
        break;

    case SEND_ABORT:
        InteractiveSendAbort();
        break;

    default:
        break;
    }
}


/* Method binds the app with server on specified ipaddress and port
 * and also registers the list of OPC,DPC,Ni supported by app
 */
int InitClient()
{
    int flag = ITS_SUCCESS;
    int ret =0;
    CL_REG_INFO rInfo;
    ITS_UINT opcIn, dpcIn, ssnIn;
    //ITS_OCTET ssnIn;

    do 
    {
        /* Method binds client app with server on specified 
         *  ipaddress and port 
         */
        CL_Handle = CL_Initialize(hostIpAddress, serverPort); 
        if (CL_Handle == NULL)
        {
            printf("Client Connect to Server failed\n");
            sleep(5);
            flag = (!ITS_SUCCESS);
        }
        else
        {
            flag = ITS_SUCCESS;
            fflush(stdout);
        }

    } while(flag != ITS_SUCCESS);

    /* Compose routing info for list of routing keys*/
    memset(&rInfo, 0, sizeof(CL_REG_INFO));

    rInfo.route_style = GetRouteStyle(style);
    printf("ROUTE_STYLE is %s \n",style);

    MTP3_HDR_SET_SIO(rInfo,0x83);
    switch (rInfo.route_style)
    {
    case DPC:
        //fflush(stdout);
        printf("Enter the DPC\n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf( "DPC = %d\n", dpcIn);
        break;

    case SSN:
        //fflush(stdout);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf( "SSN = %d\n", ssnIn);
        break;

    case OPC_DPC:
       // fflush(stdout);
        printf("Enter OPC \n");
        scanf("%d",&opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("Enter DPC \n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d DPC = %d\n ", opcIn,dpcIn);
        break;

    case DPC_SIO:
        //fflush(stdout);
        printf("Enter DPC \n");
        scanf("%d",&dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d SIO = %d \n", opcIn,rInfo.sio);
        break;

    case DPC_SSN:
        //fflush(stdout);
        printf("Enter DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d SSN = %d\n ", opcIn,ssnIn);
        break;

    case OPC_DPC_SIO:
        //fflush(stdout);
        printf("\n Enter the OPC \n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("\n Enter the DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("OPC = %d DPC = %d SIO = %d\n",opcIn ,dpcIn,rInfo.sio);
        break;

    case OPC_DPC_SSN:
        //fflush(stdout);
        printf("\n Enter the OPC \n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("\n Enter the DPC \n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d DPC= %d SIO= %d SSN = %d",
               opcIn, dpcIn,rInfo.sio,ssnIn);
       break;

    case OPC_DPC_SIO_SSN:
        //flush(stdout);
        printf("Enter the OPC\n");
        scanf("%d", &opcIn);
        MTP3_RL_SET_OPC_VALUE(rInfo, opcIn);
        printf("Enter the DPC\n");
        scanf("%d", &dpcIn);
        MTP3_RL_SET_DPC_VALUE(rInfo, dpcIn);
        printf("Enter the SSN\n");
        scanf("%d", &ssnIn);
        rInfo.ssn = (ITS_OCTET)ssnIn;
        printf("OPC = %d DPC = %d SIO = %d SSN = %d \n",
                opcIn,dpcIn,rInfo.sio,rInfo.ssn);
        break;

    default:
        printf("\n Invalid Option\n");
        break;
    }

    /* Register with the server */
    ret = CL_Register(CL_Handle, &rInfo, 1);

    if (ret  == ITS_SUCCESS)
    {
        printf("\nCL_Register: Successfully Regitered the client \n");
    }

    return ret;
}

/* 
 * This Function runs as a separate thread to 
 * receive event from the Server and waits for 
 * establishing connection with server
 */
void* Receive(void* args)
{
    ITS_EVENT evt;
    ITS_INT ret=0;
    signal(SIGINT, SignalHandler);

    while(1)
    {
        /* Receive event from the server */
        ret = CL_GetNextEvent(CL_Handle, &evt);
        if(ret != ITS_SUCCESS)
        {
            printf("Lost connection with server !!\n");
            /* Try to bind to server again and get new CL_Handlele*/
            ret = InitClient();
            if (ret == ITS_SUCCESS) 
            {
                printf("Client Re Initialization success\n");
            }
        }

        HandleAppEvent(&evt);

        /* Free the Event we no longer require it */
        ITS_EVENT_TERM(&evt);
        fflush(stdout);
    }
}

/* 
 * This function will Handle the application events
 * It decodes the events and prints the contents
 */
void HandleAppEvent(ITS_EVENT *evt)
{
    CL_TCAP_REG_ENTRY  regInfo;

    int ret =0;

    switch (evt->data[0])
    {
    case CL_TCAP_ALLOC_DID_RESP:
        did = 0;
        did |= evt->data[1];
        did |= evt->data[2] & (did << 8);
        printf("\n Got ALLOC DID %d\n", did);
        break;

    case CL_TCAP_REGISTER_RESP:
        printf("HandleAppEvent: Received Register Response\n");

        ret = TCAP_ReceiveRegisterIndication(CL_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC %d SIO %d SSN = %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.reg_info),
                MTP3_RL_GET_DPC_VALUE(regInfo.reg_info),
                (ITS_OCTET)(MTP3_HDR_GET_SIO(regInfo.reg_info) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),regInfo.reg_info.ssn);
        break;
    case CL_TCAP_DEREGISTER_RESP:
        printf("HandleAppEvent: Received DeRegister Response\n");

        ret = TCAP_ReceiveDeRegisterIndication(CL_Handle, evt, &regInfo);
        printf("Ret = %d\n", regInfo.ret);
        printf("OPC = %d  DPC = %d SIO = %d SSN = %d\n",
                MTP3_RL_GET_OPC_VALUE(regInfo.reg_info),
                MTP3_RL_GET_DPC_VALUE(regInfo.reg_info),
                (ITS_OCTET)
                (MTP3_HDR_GET_SIO(regInfo.reg_info) &
                (MTP3_SIO_UP_MASK | MTP3_NIC_MASK)),
                regInfo.reg_info.ssn);
        break;

    default:
        printf("\n\nHandleAppEvent :: Received TCAP Event From Server\n");
        TCAP_ReceiveMsg(CL_Handle, evt);
        break;
    }
}

/*************************************************************************
* Purpose : This function  handles messages received from Server.
*
* Inputs :   Handle and received event
*
* Return Value :
*
**************************************************************************/
static void
TCAP_ReceiveMsg(ITS_HANDLE handle, ITS_EVENT *event)
{
    switch ( event->data[0] )
    {
    case ITS_TCAP_DLG:
        printf("\n TCAP_ReceiveMsg:: Dialogue\n");
        break;

    case ITS_TCAP_CPT:
        printf("\n TCAP_ReceiveMsg:: Component\n");
        break;

    default:
        printf("\n TCAP_ReceiveMsg:: Neither Dialogue nor Cpt\n");
        break;
    }
    return;
}

/*************************************************************************
* Purpose : This function returns the routing style 
* used for the registration and for routing messages.
*
* Input : style as string 
* [This is a command line argument for the time being]
*
* Return Value :route_style
*
**************************************************************************/
int
GetRouteStyle(char* style)
{
    CL_REG_INFO rInfo;
    if(strcmp(style,ROUTE_DPC_STRING) == 0)
    rInfo.route_style = DPC;
    else if(strcmp(style,ROUTE_SSN_STRING) == 0)
    rInfo.route_style = SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_STRING) == 0)
    rInfo.route_style = OPC_DPC;
    else if(strcmp(style,ROUTE_DPC_SIO_STRING) == 0)
    rInfo.route_style = DPC_SIO;
    else if(strcmp(style,ROUTE_DPC_SSN_STRING) == 0)
    rInfo.route_style = DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_STRING) == 0)
    rInfo.route_style = OPC_DPC_SIO;
    else if(strcmp(style,ROUTE_OPC_DPC_SSN_STRING) == 0)
    rInfo.route_style = OPC_DPC_SSN;
    else if(strcmp(style,ROUTE_OPC_DPC_SIO_SSN_STRING) == 0)
    rInfo.route_style = OPC_DPC_SIO_SSN;
    return rInfo.route_style;
}

/*************************************************************************
*Purpose : This function allocates the local DID
*
* Input : Handle
* OutPut: LocalDID
*
* Return Value :
*
**************************************************************************/
int
TCAP_AllocateLocalDID(ITS_CTXT *did)
{
    if (nextDID >= MAX_NUM_LID)
    {
        nextDID = 1;
    }

    *did = nextDID;

    nextDID++;

    return (ITS_SUCCESS);
}
