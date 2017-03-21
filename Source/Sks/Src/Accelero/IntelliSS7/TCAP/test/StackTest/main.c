#include <stdio.h>
#include <time.h>

#include <its.h>
#include <its_thread.h>
#include <its_tq_trans.h>
#include <its_app.h>
#include <its_trace.h>

#include <itu_tcap_test.h>

//#include <asn_common.h>
#include <its_transports.h>
#include <its_imal_trans.h>

#include <its_ss7_trans.h>


int ISUP_SetVariant_CCITT() { return 0; }
int CCITT_CallTable;
int CCITT_ISUP_Variant() { return 0; }
int ISUP_TlvEventToL3Message_CCITT() { return 0; }
int ISUP_L3MessageToTlvEvent_CCITT() { return 0; }
int ComputeMSize() { return 0; }


/* ITS_HANDLE used to send and receive messages */
ITS_HANDLE tcap_handle;
ITS_HANDLE dispatch_handle;

/* ITS_THREAD to receive TCAP transactions and dispatch MTP3 messages */
ITS_THREAD receiveThread;
THREAD_RET_TYPE thread_ReceiveMsgs(void* Userdata);

ITS_THREAD dispatchThread;
THREAD_RET_TYPE thread_DispatchMsgs(void* Userdata);

/* semaphoe used to wait for Dispatch thread to complete init process */
ITS_SEMAPHORE sema_wait_for_dispatch;
/* To know if init of dispatch Thread was success or not */
ITS_BOOLEAN disptach_init_failed;

/*
 * Destination and Originating addresses used
 * when sending TCAP messages.
 */
SCCP_ADDR cdpa;
SCCP_ADDR cgpa;

/* TCAP Transactions */
TCAP_DLG TC_Begin;
TCAP_DLG TC_Continue;
TCAP_DLG TC_End;
TCAP_DLG TC_U_Abort;
TCAP_DLG TC_Uni;

/* TCAP Component */
TCAP_CPT TC_Invoke;
TCAP_CPT TC_U_Error;
TCAP_CPT TC_Result_L;
TCAP_CPT TC_Result_NL;
TCAP_CPT TC_U_Reject;
TCAP_CPT TC_U_Cancel;
TCAP_CPT TC_U_TimerReset;

/* To know if user wants to provide DID or use new Did */
ITS_BOOLEAN newDidTC_Begin;
ITS_BOOLEAN newDidTC_Continue;
ITS_BOOLEAN newDidTC_End;
ITS_BOOLEAN newDidTC_Continue;
ITS_BOOLEAN newDidTC_U_Abort;
ITS_BOOLEAN newDidTC_Uni;

/* True until the user wants to quit */
ITS_BOOLEAN keepGoing;

ITS_BOOLEAN useITS_stack;
ITS_BOOLEAN print_MTP3_MSU;

extern ITS_OCTET invoke_id;

int initTCAPTest(ITS_BOOLEAN useITS_stack, int instance_nb);
void setTCAPTransaction();
void setTCAPComponent();
int sendTCAPTransaction();


/*************************************************************************
 *
 * Purpose: CTRL C Handler function.
 *
 * Return values: None.
 *
 *************************************************************************/
#if defined (WIN32)
static BOOL WINAPI
#else
static void
#endif
exitHandler(
#if defined (WIN32)
             DWORD ctrlType
#else
             int sig
#endif
            )
{
    THREAD_DeleteThread(&receiveThread);
    THREAD_DeleteThread(&dispatchThread);
    ITS_GlobalStop();
    if (dispatch_handle)
    {
        ITS_Terminate(dispatch_handle);
    }
    ITS_Terminate(tcap_handle);
    ITS_RemFeature(itsINTELLISS7_Class);
    ITS_RemFeature(itsNMS_Class);
    
    exit(0);
#if defined (WIN32)
    return (1);
#endif
}


/*************************************************************************
 *
 * Purpose: Main function.
 *
 * Return values: DNA.
 *
 *************************************************************************/
int
main(int argc, char** argv)
{
    /* choice selection from user */
    int choiceMenu = 0;
    int result = 0;
    int instance_nb = 0;
    useITS_stack = ITS_FALSE;
    print_MTP3_MSU = ITS_FALSE;

    keepGoing = ITS_TRUE;

    printf("\n");
    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****    IntelliSS7 TCAP API Demo     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n");

    if (argc == 2)
    {
        useITS_stack = ITS_TRUE;
        printf("\n ** Info: Using IntelliNet SCCP,TCAP Stack");
        printf("\n Enter instance number to use (for dispatch Thread) -> ");
    }
    else
    {
        printf("\n ** Info: Using Vendor TCAP Stack");
        printf("\n Enter instance number to use -> ");
    }
    scanf("%d", &instance_nb);
    
    /* Initialize IntelliSS7 and tcap test */
    result = initTCAPTest(useITS_stack, instance_nb);
    if (result != ITS_SUCCESS)
    {
        exit;
    }

    /* Display Menu until user Exits*/
    do
    {
        printf("\n\n");
        printf("------------------------------------------------ \n");
        printf("         TCAP Demo Main Menu                     \n");
        printf("------------------------------------------------ \n");          
        printf(" (1)  Send User In Service                       \n");
        printf(" (2)  Send User Out Of Service                   \n");
        printf(" (3)  Modify Called Party Address                \n");
        printf(" (4)  Modify Calling Party Address               \n");
        printf(" (5)  Set TCAP Transaction                       \n");
        printf(" (6)  Set TCAP Component                         \n");
        printf(" (7)  Send TCAP Transaction                      \n");
        printf(" (8)  End TCAP Transaction                       \n");        
        if (useITS_stack)
        {
            printf(" (9)  Hex Dump of MTP3 MSU (currenty % s)\n",
                (print_MTP3_MSU ? "on" : "off"));        
        }
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - \n");
        printf(" (99) EXIT TCAP Demo\n");
        printf("------------------------------------------------\n");
        printf("Enter choice: ");
        if (scanf("%d", &choiceMenu) != 1)
        {
            /* User did not enter an int */
            fflush(stdin);
            choiceMenu = -1;
        }

        switch (choiceMenu)
        {
        /* Sending User In Service */
        case 1:
            printf("\n ** Info: Going to send User In Service.\n");
            result = sendNStateInd(tcap_handle, cgpa, ITS_TRUE);
            if (result == ITS_SUCCESS)
            {
                printf("\n ** Info: NStateInd successfully sent.");
            }
            else
            {
                printf("\n ** Error: Unable to send NStateInd (%d).", result);
            }
            break;

        /* Sending User Out Of Service */
        case 2:
            printf("\n ** Info: Going to send User Out Of Service.\n");
            result = sendNStateInd(tcap_handle, cgpa, ITS_FALSE);
            if (result == ITS_SUCCESS)
            {
                printf("\n ** Info: NStateInd successfully sent.");
            }
            else
            {
                printf("\n ** Error: Unable to send NStateInd (%d).", result);
            }
            break;
        
        /* Modify CdPA */
        case 3:
            printf("\n ** Info: Going to modify Called Party Address.\n");
            result = setSCCPAddr(&cdpa);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: Failed to set CdPA (%d).", result);
            }
            break;

        /* Modify CdPA */
        case 4:
            printf("\n ** Info: Going to modify Calling Party Address.\n");
            result = setSCCPAddr(&cgpa);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: Failed to set CgPA (%d).", result);
            }
            break;

        /* Set TCAP Transaction */
        case 5:
            printf("\n ** Info: Going to set TCAP transaction.\n");
            setTCAPTransaction();
            break;

        /* Set TCAP Component */
        case 6:
            printf("\n ** Info: Going to set TCAP component.\n");
            setTCAPComponent();
            break;

        /* Send TCAP Transaction */
        case 7:
            printf("\n ** Info: Going to send TCAP transaction.\n");
            sendTCAPTransaction();
            break;

        /* End Transaction */
        case 8:
            printf("\n ** Info: Going to end Transaction.\n");
            result = endTransaction(tcap_handle);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error Failed to end transaction (%d).", result);
            }
            break;

        /* check if a dialogue id is idle */
        case 9:
            print_MTP3_MSU = !print_MTP3_MSU;
            break;

        /* user wants to quit */
        case 99:
            keepGoing = ITS_FALSE;
            break;

        /* Wrong selection */
        default:
            printf("\n ** Warning: Wrong Selection.");
            break;
        }
    }
    while (keepGoing);
    printf("\n ** Info: Quiting ITU TCAP Test Application.");
    exitHandler(0);

    return result;
}


/*************************************************************************
 *
 * Purpose: initTCAPTest will initialize IntelliSS7 and NMS stack.
 *
 * Return values: If init is success, it will return ITS_SUCCESS,
 *                else will return en error (check its.h for values).
 *
 *************************************************************************/
int
initTCAPTest(ITS_BOOLEAN useITS_stack, int instance_nb)
{
    int result = ITS_SUCCESS;
    ITS_UINT initMask;
    ITS_USHORT instanceNumber = 0;

    APPL_SetName("testTCAP");
    
    /* setting the name of the application */
    if (useITS_stack)
    {
        
        initMask = (ITS_TCAP | ITS_SCCP | ITS_TRANSPORT_TQUEUE | 
                    ITS_TRANSPORT_SINGLE_USER);

        instanceNumber = (ITS_USHORT)USE_ITS_INST_NB;

        /* Adding the IntelliSS7 stack feature */
        result = ITS_AddFeature(itsINTELLISS7_Class);

        result = ITS_AddFeature(itsKEEPALIVE_Class);

        result = ITS_AddFeature(itsIMAL_Class);

        if (result != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(result));

            exit (-1);
        }

        /* Adding the NMS Abstraction vendor feature */
        result = ITS_AddFeature(itsNMS_Class);

        if (result != ITS_SUCCESS)
        {
            printf("\nIntelliSS7 Error <%s>.\n", ITS_GetErrorText(result));

            ITS_RemFeature(itsINTELLISS7_Class);

            ITS_RemFeature(itsKEEPALIVE_Class);

            ITS_RemFeature(itsIMAL_Class);

            exit (-1);
        }
    }
    else
    {
        initMask = (ITS_TCAP | ITS_SCCP | ITS_TRANSPORT_SS7 | 
                    ITS_TRANSPORT_SINGLE_USER);

        instanceNumber = (ITS_USHORT)instance_nb;
    }

    /* Initialize TCAP and SCCP */

    result = ITS_GlobalStart(ITS_TCAP | ITS_SCCP);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: ITS_GlobalStart failed (%d), quiting.", result);
        return (result);
    }

    /* setting Mask used by IntelliSS7 */
    
    tcap_handle = (ITS_HANDLE)ITS_Initialize(initMask, instanceNumber);
    if (tcap_handle == NULL)
    {
        printf("\n ** Error: ITS_Initialize failed , quiting.");
        ITS_GlobalStop();
        ITS_RemFeature(itsINTELLISS7_Class);
        ITS_RemFeature(itsNMS_Class);
        /* setting result to bad transport */
        result = ITS_EBADTRANSPORT;
        return result;
    }

    /* starting the Receiving Thread firs */
    result = THREAD_CreateThread(&receiveThread, 0, thread_ReceiveMsgs,
                                 NULL, ITS_TRUE);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to create receive Thread (%d), quiting.",
               result);
        ITS_GlobalStop();
        ITS_Terminate(tcap_handle);
        ITS_RemFeature(itsINTELLISS7_Class);
        ITS_RemFeature(itsNMS_Class);
        return (result);
    }
    else
    {
        printf("\n ** Info: Receive thread created.");
    }

    /*
     * starting the distpatch Thread, wait for its full initialization
     * to be done, and check if initialization was successfull.
     */
    if (useITS_stack)
    {
        SEMA_CreateSemaphore(&sema_wait_for_dispatch, 0);
        result = THREAD_CreateThread(&dispatchThread, 0, thread_DispatchMsgs, 
                                     (void*)instance_nb, ITS_TRUE);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error: Failed to create disptach Thread (%d), quiting.",
                   result);
            SEMA_DeleteSemaphore(&sema_wait_for_dispatch);
            THREAD_DeleteThread(&receiveThread);
            ITS_GlobalStop();
            ITS_Terminate(tcap_handle);
            ITS_RemFeature(itsINTELLISS7_Class);
            ITS_RemFeature(itsNMS_Class);
            return (result);
        }
        else
        {
            printf("\n ** Info: Dispatch thread created.");
        }
        SEMA_WaitSemaphore(&sema_wait_for_dispatch);
        /* we are done using the semaphore */
        SEMA_DeleteSemaphore(&sema_wait_for_dispatch);
        if (disptach_init_failed)
        {
            printf("\n ** Error: Disptach Thread Initializatio failed, quiting.");
            THREAD_DeleteThread(&receiveThread);
            THREAD_DeleteThread(&dispatchThread);
            ITS_GlobalStop();
            ITS_Terminate(tcap_handle);
            ITS_RemFeature(itsINTELLISS7_Class);
            ITS_RemFeature(itsNMS_Class);
            return (result);
        }
    }

    /* set destination and originating addr */
    memset((char *)&cdpa, 0, sizeof(SCCP_ADDR));
    printf("\n Enter Destination Address (GdPA): ");
    result = setSCCPAddr(&cdpa);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to set GdPA (%d), quiting.",
               result);
        THREAD_DeleteThread(&receiveThread);
        THREAD_DeleteThread(&dispatchThread);
        ITS_GlobalStop();
        ITS_Terminate(tcap_handle);
        ITS_Terminate(dispatch_handle);
        ITS_RemFeature(itsINTELLISS7_Class);
        ITS_RemFeature(itsNMS_Class);
        return (result);
    }

    printf("\n Enter Originating Address (GgPA): ");
    memset((char *)&cgpa, 0, sizeof(SCCP_ADDR));
    result = setSCCPAddr(&cgpa);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to set GgPA (%d), quiting.",
               result);
        THREAD_DeleteThread(&receiveThread);
        THREAD_DeleteThread(&dispatchThread);
        ITS_GlobalStop();
        ITS_Terminate(tcap_handle);
        ITS_Terminate(dispatch_handle);
        ITS_RemFeature(itsINTELLISS7_Class);
        ITS_RemFeature(itsNMS_Class);
        return (result);
    }

    /* setting CTRL C Handler functions */
#if defined(WIN32)
    SetConsoleCtrlHandler(exitHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    invoke_id = 0x01;

    return (result);
}


/*************************************************************************
 *
 * Purpose: Will set a TCAP Component.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTCAPComponent()
{
    int compType = 0;
    printf("\n Select Component Type:\n");
    printf(" (%d) TC_Invoke \n", TC_INVOKE);
    printf(" (%d) TC_U_Error \n", TC_ERROR);
    printf(" (%d) TC_ResultL \n", TC_RESULT_L);
    printf(" (%d) TC_ResultNL \n", TC_RESULT_NL);
    printf(" (%d) TC_Reject \n", TC_REJECT);
    printf(" (%d) TC_U_Cancel \n", TC_CANCEL);
    printf(" (%d) TC_U_TimerReset ", TC_TIMER_RESET);
    printf("\n Enter Component Type: ");
    scanf("%d", &compType);

    switch (compType)
    {
    case TC_INVOKE:
        memset(&TC_Invoke, 0, sizeof(TC_Invoke));
        setTC_Invoke(&TC_Invoke);
        break;
    case TC_ERROR:
        memset(&TC_U_Error, 0, sizeof(TC_U_Error));
        setTC_U_Error(&TC_U_Error);
        break;
    case TC_RESULT_L:
        memset(&TC_Result_L, 0, sizeof(TC_Result_L));
        setTC_Result(&TC_Result_L, ITS_TRUE);
        break;
    case TC_RESULT_NL:
        memset(&TC_Result_NL, 0, sizeof(TC_Result_NL));
        setTC_Result(&TC_Result_NL, ITS_FALSE);
        break;
    case TC_REJECT:
        memset(&TC_U_Reject, 0, sizeof(TC_U_Reject));
        setTC_U_Reject(&TC_U_Reject);
        break;
    case TC_CANCEL:
        memset(&TC_U_Cancel, 0, sizeof(TC_U_Cancel));
        setTC_U_Cancel(&TC_U_Cancel);
        break;
    case TC_TIMER_RESET:
        memset(&TC_U_TimerReset, 0, sizeof(TC_U_TimerReset));
        setTC_U_TimerReset(&TC_U_TimerReset);
        break;
    default:
        printf("\n ** Warning: Invalid selection.\n");
        break;
    }
}


/*************************************************************************
 *
 * Purpose: Will set a TCAP Transaction.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTCAPTransaction()
{
    int transType = 0;
    printf("\n Select Transaction Type:\n");
    printf(" (%d) TC_Begin \n", TC_BEGIN);
    printf(" (%d) TC_Continue \n", TC_CONTINUE);
    printf(" (%d) TC_End \n", TC_END);
    printf(" (%d) TC_U_Abort \n", TC_ABORT);
    printf(" (%d) TC_Uni ", TC_UNI);
    printf("\n Enter Transaction Type: ");
    scanf("%d", &transType);

    switch (transType)
    {
    case TC_BEGIN:
        memset(&TC_Begin, 0, sizeof(TC_Begin));
        setTC_Begin(&TC_Begin, cdpa, cgpa, &newDidTC_Begin);
        break;

    case TC_CONTINUE:
        memset(&TC_Continue, 0, sizeof(TC_Continue));
        setTC_Continue(&TC_Continue, cgpa, ITS_TRUE, &newDidTC_Continue);
        break;

    case TC_END:
        memset(&TC_End, 0, sizeof(TC_End));
        setTC_End(&TC_End, &newDidTC_End);
        break;

    case TC_ABORT:
        memset(&TC_U_Abort, 0, sizeof(TC_U_Abort));
        setTC_U_Abort(&TC_U_Abort, &newDidTC_U_Abort);
        break;

    case TC_UNI:
        memset(&TC_Uni, 0, sizeof(TC_Uni));
        setTC_Uni(&TC_Uni, cdpa, cgpa, &newDidTC_Uni);
        break;

    default:
        printf("\n ** Warning: Invalid selection.\n");
        break;
    }
}


/*************************************************************************
 *
 * Purpose: Will send a TCAP Transaction.
 *
 * Return values: None.
 *
 *************************************************************************/
int
sendTCAPTransaction()
{
    TCAP_DLG* transactionToSend;
    TCAP_CPT* componentToSend;
    ITS_HDR header;
    int result = 0;
    int transType = 0;
    int compType = 0;
    int userInput = 0;

    memset((char *)&header, 0, sizeof(ITS_HDR));

    printf("\n Select Transaction Type:\n");
    printf(" (%d) None \n", 0);
    printf(" (%d) TC_Begin \n", TC_BEGIN);
    printf(" (%d) TC_Continue \n", TC_CONTINUE);
    printf(" (%d) TC_End \n", TC_END);
    printf(" (%d) TC_U_Abort \n", TC_ABORT);
    printf(" (%d) TC_Uni ", TC_UNI);
    printf("\n Enter Transaction Type to send: ");
    scanf("%d", &transType);

    switch (transType)
    {
    case 0:
        break;
    case TC_BEGIN:
        transactionToSend = &TC_Begin;
        if (newDidTC_Begin)
        {
            result = TCAP_AllocateDialogueId(&header.context.dialogue_id);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: TCAP_AllocateDialogueId failed (%d)",
                       result);
                return result;
            }
        }
        else
        {
            printf("\n Enter dialogue id -> ");
            scanf("%d", &userInput);
            header.context.dialogue_id = (ITS_USHORT)userInput;
        }
        break;

    case TC_CONTINUE:
        transactionToSend = &TC_Continue;
        if (newDidTC_Continue)
        {
            result = TCAP_AllocateDialogueId(&header.context.dialogue_id);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: TCAP_AllocateDialogueId failed (%d)",
                       result);
                return result;
            }
        }
        else
        {
            printf("\n Enter dialogue id -> ");
            scanf("%d", &userInput);
            header.context.dialogue_id = (ITS_USHORT)userInput;
        }
        break;

    case TC_END:
        transactionToSend = &TC_End;
        if (newDidTC_End)
        {
            result = TCAP_AllocateDialogueId(&header.context.dialogue_id);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: TCAP_AllocateDialogueId failed (%d)",
                       result);
                return result;
            }
        }
        else
        {
            printf("\n Enter dialogue id -> ");
            scanf("%d", &userInput);
            header.context.dialogue_id = (ITS_USHORT)userInput;
        }
        break;

    case TC_ABORT:
        transactionToSend = &TC_U_Abort;

        if (newDidTC_U_Abort)
        {
            result = TCAP_AllocateDialogueId(&header.context.dialogue_id);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: TCAP_AllocateDialogueId failed (%d)",
                       result);
                return result;
            }
        }
        else
        {
            printf("\n Enter dialogue id -> ");
            scanf("%d", &userInput);
            header.context.dialogue_id = (ITS_USHORT)userInput;
        }
        break;

    case TC_UNI:
        transactionToSend = &TC_Uni;
        if (newDidTC_Uni)
        {
            result = TCAP_AllocateDialogueId(&header.context.dialogue_id);
            if (result != ITS_SUCCESS)
            {
                printf("\n ** Error: TCAP_AllocateDialogueId failed (%d)",
                       result);
                return result;
            }
        }
        else
        {
            printf("\n Enter dialogue id -> ");
            scanf("%d", &userInput);
            header.context.dialogue_id = (ITS_USHORT)userInput;
        }
        break;

    default:
        printf("\n ** Warning: Invalid selection.\n");
        return result;
        break;
    }

    printf("\n Select Component Type:\n");
    printf(" (%d) None \n", 0);
    printf(" (%d) TC_Invoke \n", TC_INVOKE);
    printf(" (%d) TC_U_Error \n", TC_ERROR);
    printf(" (%d) TC_ResultL \n", TC_RESULT_L);
    printf(" (%d) TC_ResultNL \n", TC_RESULT_NL);
    printf(" (%d) TC_Reject \n", TC_REJECT);
    printf(" (%d) TC_U_Cancel \n", TC_CANCEL);
    printf(" (%d) TC_U_TimerReset ", TC_TIMER_RESET);
    printf("\n Enter Component Type to send : ");
    scanf("%d", &compType);

    if (!transType)
    {
        printf("\n Enter dialogue id -> ");
        scanf("%d", &userInput);
        header.context.dialogue_id = (ITS_USHORT)userInput;
    }
    
    switch (compType)
    {
    case 0:
        break;
    case TC_INVOKE:
        componentToSend = &TC_Invoke;
        break;
    case TC_ERROR:
        componentToSend = &TC_U_Error;
        break;
    case TC_RESULT_L:
        componentToSend = &TC_Result_L;
        break;
    case TC_RESULT_NL:
        componentToSend = &TC_Result_NL;
        break;
    case TC_REJECT:
        componentToSend = &TC_U_Reject;
        break;
    case TC_CANCEL:
        componentToSend = &TC_U_Cancel;
        break;
    case TC_TIMER_RESET:
        componentToSend = &TC_U_TimerReset;
        break;
    default:
        printf("\n ** Warning: Invalid selection.\n");
        return result;
        break;
    }

    if (compType)
    {
        result = TCAP_SendComponent(tcap_handle, &header, componentToSend);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error : Failed to send TCAP Component (%d).", result);
            return result ;
        }
        else
        {
            printf("\n ** Info : TCAP Component sent.");
            displayComponent(header, componentToSend, ITS_FALSE);
        }
    }

    if (transType)
    {

        result = TCAP_SendDialogue(tcap_handle, &header, transactionToSend);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error : Failed to send TCAP Dialogue (%d).", result);
            return result ;
        }
        else
        {
            printf("\n ** Info : TCAP Dialogue sent.");
            displayTransaction(header, transactionToSend, ITS_FALSE);
        }
    }
    return result;
}


/*************************************************************************
 *
 * Purpose: Thread function that will wait for Event from IntelliSS7.
 *
 * Return values: None.
 *
 *************************************************************************/
THREAD_RET_TYPE
thread_ReceiveMsgs(void* Userdata)
{
    int result = 0;
    TCAP_CPT incoming_component;
    TCAP_DLG incoming_dialogue;
    ITS_HDR incoming_header;
    ITS_EVENT event;

    memset((char *)&incoming_header, 0, sizeof(ITS_HDR));
    memset((char *)&incoming_dialogue, 0, sizeof(TCAP_DLG));
    memset((char *)&incoming_component, 0, sizeof(TCAP_CPT));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    for (; ; )
    {
        result = ITS_GetNextEvent(tcap_handle, &event);
        if (result == ITS_SUCCESS)
        {
            printf("\n **Info: Response Thread received TCAP events.");
            /* Checking the type of event that we did receive */
            if (TCAP_MSG_TYPE(&event) == ITS_TCAP_DLG)
            {
                /* received TCAP Dialogue. */
                result = TCAP_ReceiveDialogue(tcap_handle, &event,
                                              &incoming_header,
                                              &incoming_dialogue);
                if (result != ITS_SUCCESS)
                {
                    printf("\n ** Error: TCAP_ReceiveDialogue (%d).",
                           result);
                    continue;
                }
                else
                {
                    printf("\n ** Info: TCAP Transaction Received.");
                    displayTransaction(incoming_header, &incoming_dialogue,
                                       ITS_TRUE);
                }
                
                /* Did we receive a TC_Notice. TC_P(U)_Abort */
                if ((incoming_dialogue.ptype == TCPPT_TC_NOTICE) || 
                    (incoming_dialogue.ptype == TCPPT_TC_P_ABORT) ||
                    (incoming_dialogue.ptype == TCPPT_TC_U_ABORT))
                {
                    /* no need to check for component present. */
                    continue;
                }
                else
                {
                    if (ComponentPresent(incoming_dialogue))
                    {                        
                        receiveComponent(tcap_handle);     
                    }
                }
            }
            else if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
            {
                /*
                 * If a TCAP component is received 1st,
                 * it can be a Local Cancel or maybe Reject.
                 */
                result = TCAP_ReceiveComponent(tcap_handle, &event,
                                               &incoming_header,
                                               &incoming_component);
                if (result != ITS_SUCCESS)
                {
                    printf("\n ** Error: TCAP_ReceiveComponent (%d).",
                           result);
                    continue;
                }
                else
                {
                    printf("\n ** Info: TCAP Component Received.");
                    displayComponent(incoming_header, &incoming_component,
                                     ITS_TRUE);
                }
            }
            else
            {
                printf("\n ** Warning: The Event is not a %s or a %s (type: 0x%02).",
                           "dialogue", "component", TCAP_MSG_TYPE(&event));
            }
        }
        else
        {
            /* GetNextEvent Failed. */
            printf("\n ** Error: ITS_GetNextEvent failed (%d).",
                           result);
        }
    }
    THREAD_NORMAL_EXIT;
}


/*************************************************************************
 *
 * Purpose: Thread function that will wait for Event from IntelliSS7.
 *
 * Return values: None.
 *
 *************************************************************************/
THREAD_RET_TYPE
thread_DispatchMsgs(void* Userdata)
{
    ITS_EVENT event;
    int result = 0;
    int index = 0;
    int transportType = 0;
    ITS_USHORT instanceNumber = (int)Userdata;
    ITS_UINT initMask = 0;

    printf("\n\n Select transport type for dispatch thread:\n");
    printf(" (1) SS7 transport\n");
    printf(" (2) IMAL transport (Server) \n");
    printf(" (3) IMAL transport (Client) \n");
    printf(" Enter transport type for dispatch thread -> ");
    scanf("%d", &transportType);
    switch (transportType)
    {
    case 1:
        initMask = (ITS_MTP3 | ITS_TRANSPORT_SS7 | ITS_TRANSPORT_SINGLE_USER);
        break;

    case 2:
        initMask = (ITS_TCAP | ITS_TRANSPORT_SSOCKET |
                    ITS_TRANSPORT_IMAL_SOCKET | ITS_TRANSPORT_SINGLE_USER);
        break;

    case 3:
        initMask = (ITS_TCAP | ITS_TRANSPORT_CSOCKET |
                    ITS_TRANSPORT_IMAL_SOCKET | ITS_TRANSPORT_SINGLE_USER);
        break;

    default:
        printf("\n ** warning: Invalid selection: Using SS7 transport.");
        initMask = (ITS_MTP3 | ITS_TRANSPORT_SS7 | ITS_TRANSPORT_SINGLE_USER);
        break;
    }
        
    dispatch_handle = (ITS_HANDLE)ITS_Initialize(initMask, instanceNumber);
    if (!dispatch_handle)
    {
        disptach_init_failed = ITS_TRUE;
        SEMA_PostSemaphore(&sema_wait_for_dispatch);
        THREAD_NORMAL_EXIT;
    }

    SEMA_PostSemaphore(&sema_wait_for_dispatch);

    do 
    {
        memset((char *)&event, 0, sizeof(ITS_EVENT));
        result = ITS_GetNextEvent(dispatch_handle, &event);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error: ITS_GetNextEvent (dispatch) failed (%d).",
                   result);
        }
        else
        {
            event.src = ITS_MTP3_SRC;

            if (print_MTP3_MSU)
            {
                printf("\n ** Info: MTP3 MSU Hex Dump\n");
                for (index = 0; index < event.len; index++)
                {
                    printf (" 0x%02x", event.data[index]);
                }
                printf("\n\n");
            }
            TRANSPORT_PutEvent(ITS_SCCP_SRC, &event);
        }
    }while (keepGoing);

    THREAD_NORMAL_EXIT;
}