#include <stdio.h>

#include <itu_tcap_test.h>

ITS_OCTET invoke_id;


void displaySCCPAddress(SCCP_ADDR* address);
void setGTT(ITS_OCTET* addrIndicator, ITS_OCTET* gttInfo, int* len);
void setInvokeID(CPT_INV_ID* invokeId);
void setOperationCode(CPT_OP* localOpCode);
void setLocalErrorCode(CPT_ERROR_CODE* localErrCode);


/*************************************************************************
 *
 * Purpose: This method will send a SCCP N-State Indication.
 *
 * Return values: ITS_SUCCESS if success, "failure code" otherwise.
 *
 *************************************************************************/
int
sendNStateInd(ITS_HANDLE handle, SCCP_ADDR CgPA, ITS_BOOLEAN allowed)
{
    ITS_OCTET ssn, addrInd = 0;
    ITS_UINT opc = 0;
    int result = ITS_SUCCESS;

    /*
     * Getting the Point Code and SSN from the Calling Party Address.
     * Note: We are not intersted in GTT.
     */
    result = SCCP_DecodeAddr(&CgPA, &addrInd, &opc, &ssn, NULL, NULL);
    if (result != ITS_SUCCESS)
    {
        return result;
    }

    if (allowed)
    {
        result = SCCP_SendUserInService(handle, opc, ssn);
    }
    else
    {
        result = SCCP_SendUserOutOfService(handle, opc, ssn);
    }
    
    return result;
}


/*************************************************************************
 *
 * Purpose: This method will locally end a transaction.
 *
 * Return values: ITS_SUCCESS if success, "failure code" otherwise.
 *
 *************************************************************************/
int
endTransaction(ITS_HANDLE handle)
{
    TCAP_DLG response;
    ITS_HDR header;
    int result = ITS_SUCCESS;
    int userInput = 0;

    memset((char *)&header, 0, sizeof(ITS_HDR));    
    memset((char *)&response, 0, sizeof(TCAP_DLG));

    /* Setting type to  TC_End */ 
     response.ptype = TCPPT_TC_END;

    /* Specifying termination to pre-arranged end. */
    response.u.end.termination = TCPEND_PREARRANGED;

    printf(" Enter Dialogue id to return to idle state (decimal value): " );
    scanf("%d", &userInput);
    header.context.dialogue_id = (ITS_USHORT) userInput;

    result =  TCAP_SendDialogue(handle, &header, &response);
    return result;
}



/*************************************************************************
 *
 * Purpose: This method constructs a SCCP address used in a tcap Message.
 *
 * Return values: ITS_SUCCESS if success, "failure code" otherwise.
 *
 *************************************************************************/
int
setSCCPAddr(SCCP_ADDR *addr)
{
    int result = ITS_SUCCESS;
    int userSelection = 0;
    ITS_OCTET addressIndicator = (0x00U);
    ITS_OCTET gttInfo[50];
    int gttLen = 0;
    int ssn;
    ITS_UINT  pointCode; 

    /* Does addr is national or Intl ? */
    printf("\n [1] SCCP Address use National Standard ?");
    printf("\n [2] SCCP Address use International Standard ?");
    printf("\n Enter your selection -> ");
    scanf("%d", &userSelection);
    if (userSelection == 1)
    {
        addressIndicator |= SCCP_CPA_ROUTE_NAT;
    }
    else if (userSelection == 2)
    {
        addressIndicator |= SCCP_CPA_ROUTE_INT;
    }
    else
    {
        printf("\n Invalid selection, using International Standard.");
        addressIndicator |= SCCP_CPA_ROUTE_INT;
    }
    
    /* Does CdPA is routed based on GTT or SSN/PC ? */
    printf("\n [1] Route Message based on SSN / DPC ?");
    printf("\n [2] Route Message based on GTT ?");
    printf("\n Enter your selection -> ");
    scanf("%d", &userSelection);
    if (userSelection == 1)
    {
        addressIndicator |= SCCP_CPA_ROUTE_SSN;
    }

    /* Does CdPA include a SSN ? */
    printf("\n Does Destination Address have a SSN [y/n]? ");
    if (setOption())
    {
        addressIndicator |= SCCP_CPA_HAS_SSN;
    }
    
    /* Does CdPA include a PC ? */
    printf(" Does Destination Address have a Point Code [y/n]? ");
    if (setOption())
    {
        addressIndicator |= SCCP_CPA_HAS_PC;
    }
    

    /* Request SSN from user */
    if (addressIndicator & SCCP_CPA_HAS_SSN)
    {
        printf(" Enter SSN (decimal value):");
        scanf("%d", &ssn);
    }

    /* Request PC from user */
    if (addressIndicator & SCCP_CPA_HAS_PC)
    {
        printf(" Enter Point Code (decimal value): ");
        scanf("%d", &userSelection);
        pointCode = (ITS_UINT)userSelection;
    }

    
    printf("\n Does Address hold GTT Information [y/n]? ");
    if (setOption())
    {
        setGTT(&addressIndicator, gttInfo, &gttLen);
    }

    /* Calling IntelliSS7 Encoding SCCP address function */
    result = SCCP_EncodeAddr(addr, addressIndicator, pointCode, (ITS_OCTET)ssn,
                             gttInfo, (ITS_USHORT)gttLen);
    return (result);
}


/*************************************************************************
 *
 * Purpose: check if component(s) is (are) present with the Transaction.
 *
 * Return values: ITS_TRUE if component(s) is (are) present, else ITS_FALSE.
 *
 *************************************************************************/
ITS_BOOLEAN
ComponentPresent(TCAP_DLG transaction)
{
    /* by Default, components are not present */
    ITS_BOOLEAN result = ITS_FALSE;

    switch (transaction.ptype)
    {
    /* If Transaction is TC_Uni, component present? */
    case TCPPT_TC_UNI:
        if (transaction.u.uni.cpt_present)
        {
            result = ITS_TRUE;
        }
        break;

    /* If Transaction is TC_Begin, component present? */
    case TCPPT_TC_BEGIN:
        if (transaction.u.begin.cpt_present)
        {
            result = ITS_TRUE;
        }
        break;

    /* If Transaction is TC_End, component present? */
    case TCPPT_TC_END:
        if (transaction.u.end.cpt_present)
        {
            result = ITS_TRUE;
        }
        break;

    /* If Transaction is TC_Begin, component present? */
    case TCPPT_TC_CONTINUE:
        if (transaction.u.cont.cpt_present)
        {
            result = ITS_TRUE;
        }
        break;
    }return result;
}


/*************************************************************************
 *
 * Purpose: will get TCAP components from the stack (after a transaction have
 *          been received, and component(s) is (are) present.
 *
 * Return values: None.
 *
 *************************************************************************/
void
receiveComponent(ITS_HANDLE handle)
{
    int result = 0;
    TCAP_CPT component;
    ITS_EVENT event;
    ITS_HDR header;
    ITS_BOOLEAN errorReceivingCpt;

    memset((char *)&header, 0, sizeof(ITS_HDR));
    memset((char *)&component, 0, sizeof(TCAP_CPT));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    errorReceivingCpt = ITS_FALSE;

    /* Receive component(s) until it is the last one */
    do
    {
        result = ITS_GetNextEvent(handle, &event);
        if (result == ITS_SUCCESS)
        {
            /* Checking the type of event that we did receive */
            if (TCAP_MSG_TYPE(&event) == ITS_TCAP_CPT)
            {
                result = TCAP_ReceiveComponent(handle, &event, &header,
                                               &component);

                displayComponent(header, &component, ITS_TRUE);
            }
            else
            {
                printf("\n ** Warning: The Event is not a %s (type: 0x%02).",
                       "component", TCAP_MSG_TYPE(&event));
                errorReceivingCpt = ITS_TRUE;
            }
        }
        else
        {
            /* GetNextEvent Failed. */
            printf("\n ** Error: ITS_GetNextEvent failed (%d).",
                   result);
            errorReceivingCpt = ITS_TRUE;
        }
    }
    while ((!component.last_component) && (!errorReceivingCpt));
}


/*************************************************************************
 *
 * Purpose: To set a TC_Begin Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTC_Begin(TCAP_DLG* TC_Begin, SCCP_ADDR CdPA, SCCP_ADDR CgPA,
            ITS_BOOLEAN* newDid)
{
    int qos = 0;
    int userInput = 0;

    printf("\n ** Info: Going to set TC_Begin.\n");
    TC_Begin->ptype = TCPPT_TC_BEGIN;

    /* Setting calling and called party address */
    printf("\n Populating calling party address (CgPA).");
    TC_Begin->u.begin.orig_addr.len = CgPA.len;
    memcpy(TC_Begin->u.begin.orig_addr.data, CgPA.data, CgPA.len);

    printf("\n Populating called party address (CdPA).\n");
    TC_Begin->u.begin.dest_addr.len = CdPA.len;
    memcpy(TC_Begin->u.begin.dest_addr.data, CdPA.data, CdPA.len);

    /* Setting quality of service */
    printf("\n Select quality of service:\n");
    printf(" (1) Connectionless, NOT sequenced, NO return on error \n");
    printf(" (2) Connectionless, NOT sequenced,return on error \n");
    printf(" (3) Connectionless, sequenced, NO return on error \n");
    printf(" (4) Connectionless, sequenced, return on error ");
    printf("\n Enter quality of service: ");
    scanf("%d", &qos);
    if ((qos > 4) || (qos < 1))
    {
        printf(" ** Warning: Invalid Selection. Qos set to Return on Error.\n");
        qos = 2;
    }
    set_qos(TC_Begin->u.begin, qos);

    /* Setting App Context Name and User Info. */
    printf("\n Do you want to include application context name [y/n]? ");
    if (setOption())
    {
        printf(" Populating App context name with random information.\n");
        set_proposed_ACName(TC_Begin->u.begin.ac_name);        
    }
    else
    {
        TC_Begin->u.begin.ac_name.len = 0;
    }

    /* User info might be present only if app. context name is */
    printf("\n Do you want to include user information [y/n]? ");
    if (setOption())
    {
        printf(" Populating User Info with random information.\n");
        TC_Begin->u.begin.user_info.len = 12;
        memcpy(TC_Begin->u.begin.user_info.data, user_Info, 12);
    }
    else
    {
        TC_Begin->u.begin.user_info.len = 0;
    }

    printf("\n Which dialogue id do you want to use:\n");
    printf(" (1) Allocate new Dialogue id \n");
    printf(" (2) Ask User to provide dialogue id \n");
    printf(" Enter your selection: ");
    scanf("%d", &userInput);
    if (userInput == 1)
    {
        *newDid = ITS_TRUE;
    }
    else
    {
        *newDid = ITS_FALSE;
    }    
}


/*************************************************************************
 *
 * Purpose: To set a TC_End Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTC_End(TCAP_DLG* TC_End, ITS_BOOLEAN* newDid)
{
    int userInput = 0;
    int qos = 0;
    int termination = 0;

    printf("\n ** Info: Going to set TC_End.");
    TC_End->ptype = TCPPT_TC_END;

    /* Setting quality of service */
    printf("\n Select quality of service:\n");
    printf(" (1) Connectionless, NOT sequenced, NO return on error \n");
    printf(" (2) Connectionless, NOT sequenced,return on error \n");
    printf(" (3) Connectionless, sequenced, NO return on error \n");
    printf(" (4) Connectionless, sequenced, return on error ");
    printf("\n Enter quality of service: ");
    scanf("%d", &qos);
    if ((qos > 4) || (qos < 1))
    {
        printf(" ** Warning: Invalid Selection. Qos set to Return on Error.\n");
        qos = 2;
    }
    set_qos(TC_End->u.end, qos);

    /* Setting Termination */
    printf("\n Select Termination:\n");
    printf(" (1) Basic end Termination \n");
    printf(" (2) Pre-arranged end \n");
    printf(" (3) Invalid Value ");
    printf("\n Enter termination: ");
    scanf("%d", &termination);
    if ((termination >= 3) || (termination < 1))
    {
        /* Wrong type of termination */
        TC_End->u.end.termination = 0x03;
    }
    else
    {
        (termination == 1) ?
            (TC_End->u.end.termination = TCPEND_BASIC) :
            (TC_End->u.end.termination = TCPEND_PREARRANGED);
    }

    printf("\n Do you want to include application context name [y/n]? ");
    if (setOption())
    {
        printf(" Populating App context name with random information.\n");
        set_proposed_ACName(TC_End->u.end.ac_name);            
    }
    else
    {
        TC_End->u.end.ac_name.len = 0;
    }

    printf("\n Do you want to include user information [y/n]? ");
    if (setOption())
    {
        printf(" Populating User Info with random information.\n");
        TC_End->u.end.user_info.len = 12;
        memcpy(TC_End->u.end.user_info.data, user_Info, 12);
    }
    else
    {
        TC_End->u.end.user_info.len = 0;
    }

    printf("\n Which dialogue id do you want to use:\n");
    printf(" (1) Allocate new Dialogue id \n");
    printf(" (2) Ask User to provide dialogue id \n");
    printf(" Enter your selection: ");
    scanf("%d", &userInput);
    if (userInput == 1)
    {
        *newDid = ITS_TRUE;
    }
    else
    {
        *newDid = ITS_FALSE;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_Continue Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTC_Continue(TCAP_DLG* TC_Continue, SCCP_ADDR CgPA,
               ITS_BOOLEAN confirmTC_Begin, ITS_BOOLEAN* newDid)
{
    int userInput = 0;
    int qos = 0;

    printf("\n ** Info: Going to set TC_Continue.");
    TC_Continue->ptype = TCPPT_TC_CONTINUE;

    /* Setting quality of service */
    printf("\n Select quality of service:\n");
    printf(" (1) Connectionless, NOT sequenced, NO return on error \n");
    printf(" (2) Connectionless, NOT sequenced,return on error \n");
    printf(" (3) Connectionless, sequenced, NO return on error \n");
    printf(" (4) Connectionless, sequenced, return on error ");
    printf("\n Enter quality of service: ");
    scanf("%d", &qos);
    if ((qos > 4) || (qos < 1))
    {
        printf(" ** Warning: Invalid Selection. Qos set to Return on Error.\n");
        qos = 2;
    }
    set_qos(TC_Continue->u.cont, qos);

    printf("\n Do you want to include CgPA (only when confirm new dialogue) [y/n]? ");
    if (setOption())
    {
        /* Setting calling party address */
        printf(" Populating calling party address (CgPA).");
        TC_Continue->u.cont.orig_addr.len = CgPA.len;
        memcpy(TC_Continue->u.cont.orig_addr.data, CgPA.data, CgPA.len);
    }
    else
    {
        TC_Continue->u.cont.orig_addr.len = 0;
    }

    printf("\n Do you want to include application context name [y/n]? ");
    if (setOption())
    {
        printf("\n Which application context name do you want to use:\n");
        printf(" (1) Proposed Application Context Name \n");
        printf(" (2) Alternative Application Context Name \n");
        printf(" Enter your selection: ");
        scanf("%d", &userInput);
        if (userInput == 1)
        {
            printf(" Populating App context name with random information.\n");
            set_proposed_ACName(TC_Continue->u.cont.ac_name);
        }
        else
        {
            printf(" Populating App context name with random information.\n");
            set_alternative_ACName(TC_Continue->u.cont.ac_name);
        }
    }
    else
    {
        TC_Continue->u.cont.ac_name.len = 0;
    }

    printf("\n Do you want to include user information [y/n]? ");
    if (setOption())
    {
        printf(" Populating App context name with random information.\n");
        TC_Continue->u.cont.user_info.len = 12;
        memcpy(TC_Continue->u.cont.user_info.data, user_Info, 12);
        
    }
    else
    {
        TC_Continue->u.cont.user_info.len = 0;
    }

    printf("\n Which dialogue id do you want to use:\n");
    printf(" (1) Allocate new Dialogue id \n");
    printf(" (2) Ask User to provide dialogue id \n");
    printf(" Enter your selection: ");
    scanf("%d", &userInput);
    if (userInput == 1)
    {
        *newDid = ITS_TRUE;
    }
    else
    {
        *newDid = ITS_FALSE;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_U_Abort Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTC_U_Abort(TCAP_DLG* TC_U_Abort, ITS_BOOLEAN* newDid)
{
    int userInput = 0;
    int qos = 0;
    int abortReason = 0;

    printf("\n ** Info: Going to set TC_U_Abort.\n");
    TC_U_Abort->ptype = TCPPT_TC_U_ABORT;

    /* Setting quality of service */
    printf("\n Select quality of service:\n");
    printf(" (1) Connectionless, NOT sequenced, NO return on error \n");
    printf(" (2) Connectionless, NOT sequenced,return on error \n");
    printf(" (3) Connectionless, sequenced, NO return on error \n");
    printf(" (4) Connectionless, sequenced, return on error ");
    printf("\n Enter quality of service: ");
    scanf("%d", &qos);
    if ((qos > 4) || (qos < 1))
    {
        printf(" ** Warning: Invalid Selection. Qos set to Return on Error.\n");
        qos = 2;
    }
    set_qos(TC_U_Abort->u.abort, qos);

    /* Setting abort reason */
    printf("\n Select abort reason:\n");
    printf(" (0) Do no include abort reason \n");
    printf(" (%d) Application context name not supported \n", 
           TCPUABT_AC_NOT_SUP);
    printf(" (%d) User defined \n", TCPUABT_USER_DEFINED);
    printf(" (%d) Invalid type \n", (TCPUABT_USER_DEFINED+1));
    printf("\n Enter abort reason: ");
    scanf("%d", &abortReason);
    TC_U_Abort->u.abort.abort_reason = (ITS_USHORT)abortReason;

    printf("\n Do you want to include application context name [y/n]? ");
    if (setOption())
    {
        printf("\n Which application context name do you want to use:\n");
        printf(" (1) Proposed Application Context Name \n");
        printf(" (2) Alternative Application Context Name \n");
        printf(" Enter your selection: ");
        scanf("%d", &userInput);
        if (userInput == 1)
        {
            printf(" Populating App context name with random information.\n");
            set_proposed_ACName(TC_U_Abort->u.abort.ac_name);
        }
        else
        {
            printf(" Populating App context name with random information.\n");
            set_alternative_ACName(TC_U_Abort->u.abort.ac_name);
        }
    }
    else
    {
        TC_U_Abort->u.abort.ac_name.len = 0;
    }

    printf("\n Do you want to include user information [y/n]? ");
    if (setOption())
    {
        printf(" Populating User Info with random information.\n");
        TC_U_Abort->u.abort.user_info.len = 12;
        memcpy(TC_U_Abort->u.abort.user_info.data, user_Info, 12);
    }
    else
    {
        TC_U_Abort->u.abort.user_info.len = 0;
    }

    printf("\n Which dialogue id do you want to use:\n");
    printf(" (1) Allocate new Dialogue id \n");
    printf(" (2) Ask User to provide dialogue id \n");
    printf(" Enter your selection: ");
    scanf("%d", &userInput);
    if (userInput == 1)
    {
        *newDid = ITS_TRUE;
    }
    else
    {
        *newDid = ITS_FALSE;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_Uni Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTC_Uni(TCAP_DLG* TC_Uni, SCCP_ADDR CdPA, SCCP_ADDR CgPA,
          ITS_BOOLEAN* newDid)
{
    int userInput = 0;
    int qos = 0;
    printf("\n ** Info: Going to set TC_Uni.\n");
    TC_Uni->ptype = TCPPT_TC_UNI;

    /* Setting calling and called party address */
    printf("\n Populating calling party address (CgPA).");
    TC_Uni->u.uni.orig_addr.len = CgPA.len;
    memcpy(TC_Uni->u.uni.orig_addr.data, CgPA.data, CgPA.len);

    printf("\n Populating called party address (CdPA).\n");
    TC_Uni->u.uni.dest_addr.len = CdPA.len;
    memcpy(TC_Uni->u.uni.dest_addr.data, CdPA.data, CdPA.len);

    /* Setting quality of service */
    printf("\n Select quality of service:\n");
    printf(" (1) Connectionless, NOT sequenced, NO return on error \n");
    printf(" (2) Connectionless, NOT sequenced,return on error \n");
    printf(" (3) Connectionless, sequenced, NO return on error \n");
    printf(" (4) Connectionless, sequenced, return on error ");
    printf("\n Enter quality of service: ");
    scanf("%d", &qos);
    if ((qos > 4) || (qos < 1))
    {
        printf(" ** Warning: Invalid Selection. Qos set to Return on Error.\n");
        qos = 2;
    }
    set_qos(TC_Uni->u.uni, qos);

    /* Setting App Context Name and User Info. */
    printf("\n Do you want to include application context name [y/n]? ");
    if (setOption())
    {
        printf(" Populating App context name with random information.\n");
        set_proposed_ACName(TC_Uni->u.uni.ac_name);        
    }
    else
    {
        TC_Uni->u.uni.ac_name.len = 0;
    }

    /* User info might be present only if app. context name is */
    printf("\n Do you want to include user information [y/n]? ");
    if (setOption())
    {
        printf(" Populating User Info with random information.\n");
        setUserInfo(TC_Uni->u.uni.user_info);
    }
    else
    {
        TC_Uni->u.uni.user_info.len = 0;
    }

    printf("\n Which dialogue id do you want to use:\n");
    printf(" (1) Allocate new Dialogue id \n");
    printf(" (2) Ask User to provide dialogue id \n");
    printf(" Enter your selection: ");
    scanf("%d", &userInput);
    if (userInput == 1)
    {
        *newDid = ITS_TRUE;
    }
    else
    {
        *newDid = ITS_FALSE;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_Invoke Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void setTC_Invoke(TCAP_CPT* TC_Comp)
{
    int userInput = 0;
    printf("\n ** Info: Going to set TC_Invoke.\n");
    TC_Comp->ptype = TCPPT_TC_INVOKE;

    /* Setting invoke id */
    setInvokeID(&TC_Comp->u.invoke.invoke_id);

    printf("\n Do you want to include a linked id [y/n]? ");
    if (setOption())
    {
        setInvokeID(&TC_Comp->u.invoke.linked_id);
    }
    else
    {
        TC_Comp->u.invoke.linked_id.len = 0;
    }


    /* Setting the Operation Class */
    printf("\n Select class of operation:\n");
    printf(" (0) Class 0: Invalid Operation Class\n");
    printf(" (1) Class 1: Both success and failure are reported\n");
    printf(" (2) Class 2: Only failure is reported \n");
    printf(" (3) Class 3: Only success is reported\n");
    printf(" (4) Class 4: Neither success, nor failure is reported");
    printf("\n Enter Operation Class -> ");
    scanf("%d", &userInput);
    if ((userInput > 4) || (userInput < 0))
    {
        printf(" ** Warning: Invalid Selection. Using operation class 1.\n");
        userInput = 1;
    }
    TC_Comp->u.invoke.opClass = (ITS_USHORT)userInput;

    /* Setting the timeout */
    printf("\n Enter timeout (in seconds) -> ");
    scanf("%d", &userInput);
    TC_Comp->u.invoke.timeout = (ITS_USHORT)userInput;


    /* Setting local operation code */
    setOperationCode(&TC_Comp->u.invoke.operation);

    /* Setting the parameters */
    printf("\n Do you want to include parameters [y/n]? ");
    if (setOption())
    {
        printf("\n Populating parameter set with ramdom information.\n");
        setParameterSet(TC_Comp->u.invoke.param);
    }
    else
    {
        TC_Comp->u.invoke.param.len = 0;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_U_Error Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void setTC_U_Error(TCAP_CPT* TC_Comp)
{
    printf("\n ** Info: Going to set TC_U_Error.\n");
    TC_Comp->ptype = TCPPT_TC_U_ERROR;

    /* Setting invoke id */
    setInvokeID(&TC_Comp->u.error.invoke_id);

    /* Setting Local Error Code */
    setLocalErrorCode(&TC_Comp->u.error.error);

    /* Setting the parameters */
    printf("\n Do you want to include parameters [y/n]? ");
    if (setOption())
    {
        printf("\n Populating parameter set with ramdom information.\n");
        setParameterSet(TC_Comp->u.error.param);
    }
    else
    {
        TC_Comp->u.error.param.len = 0;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_Result (last or not last) Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void setTC_Result(TCAP_CPT* TC_Comp, ITS_BOOLEAN last)
{
    if (last)
    {
        printf("\n ** Info: Going to set TC_Result_Last.\n");
        TC_Comp->ptype = TCPPT_TC_RESULT_L;
    }
    else
    {
        printf("\n ** Info: Going to set TC_Result_NotLast.\n");
        TC_Comp->ptype = TCPPT_TC_RESULT_NL;
    }

    /* Setting invoke id */
    setInvokeID(&TC_Comp->u.result.invoke_id);

    /* Setting operation code */
    printf("\n Do you want to include Operation Code [y/n]? ");
    if (setOption())
    {
        setOperationCode(&TC_Comp->u.result.operation);
    }
    else
    {
        TC_Comp->u.result.operation.len = 0;
    }

    /* Setting the parameters */
    printf("\n Do you want to include parameters [y/n]? ");
    if (setOption())
    {
        printf("\n Populating parameter set with ramdom information.\n");
        setParameterSet(TC_Comp->u.result.param);
    }
    else
    {
        TC_Comp->u.result.param.len = 0;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_U_Reject Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void setTC_U_Reject(TCAP_CPT* TC_Comp)
{
    int userInput = 0;

    printf("\n ** Info: Going to set TC_U_Reject.\n");
    TC_Comp->ptype = TCPPT_TC_U_REJECT;

    /* setting the Invoke id */
    setInvokeID(&TC_Comp->u.reject.invoke_id);

    printf("\n Do you want to include Problem Code [y/n]? ");
    if (setOption())
    {
        /* Setting the problem type */
        printf("\n Select problem type \n");
        printf(" (%d) General Problem \n", TCPPROB_GENERAL);
        printf(" (%d) Invoke Problem \n", TCPPROB_INVOKE);
        printf(" (%d) Return Result Problem \n", TCPPROB_RETURN_RES);
        printf(" (%d) Return Error Problem ", TCPPROB_RETURN_ERR);
        printf("\n Enter Problem Type -> ");
        scanf("%d", &userInput);
        if ((userInput > TCPPROB_RETURN_ERR) || (userInput < TCPPROB_GENERAL))
        {
            printf(" ** Warning: Invalid Selection. Using General Problem.\n");
            userInput = TCPPROB_GENERAL;
        }
        TC_Comp->u.reject.problem.data[0]= (ITS_OCTET)userInput;

        /* Setting the problem specifier based on the type */
        printf("\n Select problem specifier \n");

        /* based on Problem Type, need to set problem specifier */
        switch (TC_Comp->u.reject.problem.data[0])
        {
        case TCPPROB_GENERAL:
            printf(" (%d) Unrecognized component \n", 
                   TCPPROB_SPEC_GEN_UNREC_COMP);
            printf(" (%d) Mistyped component \n", 
                TCPPROB_SPEC_GEN_MISTYPED_COMP);
            printf(" (%d) Badly structured component", 
                TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP);
            
            printf("\n Enter General Problem -> ");
            scanf("%d", &userInput);
            TC_Comp->u.reject.problem.data[2] =
                (ITS_OCTET)userInput;
            break;

        case TCPPROB_INVOKE:
            printf(" (%d) duplicate invoke ID \n",
                TCPPROB_SPEC_INV_DUPLICATE_INV_ID);
            printf(" (%d) Unrecognized operation \n",
                TCPPROB_SPEC_INV_UNREC_OP_CODE);
            printf(" (%d) Mistyped parameter \n",
                TCPPROB_SPEC_INV_MISTYPED_PARAM);
            printf(" (%d) Resource limitation \n",
                TCPPROB_SPEC_INV_RESOURCE_LIMIT);
            printf(" (%d) Initiating Release \n",
                TCPPROB_SPEC_INV_INITIATE_RELEASE);
            printf(" (%d) Unrecognized linked ID \n",
                TCPPROB_SPEC_INV_UNREC_LINKED_ID);
            printf(" (%d) Linked response unexpected \n",
                TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP);
            printf(" (%d) Unexpected Linked operation",
                TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP);

            printf("\n Enter Invoke Problem -> ");
            scanf("%d", &userInput);
            TC_Comp->u.reject.problem.data[2] =
                (ITS_OCTET)userInput;
            break;

        case TCPPROB_RETURN_RES:
            printf(" (%d) Unrecognized invoke ID \n", 
                TCPPROB_SPEC_RES_UNREC_INVOKE_ID);
            printf(" (%d) Return result unexpected \n",
                TCPPROB_SPEC_RES_UNEXPECTED_RET_RES);
            printf(" (%d) Mistyped parameter",
                TCPPROB_SPEC_RES_MISTYPED_PARAM);

            printf("\n Enter Return Result Problem -> ");
            scanf("%d", &userInput);
            TC_Comp->u.reject.problem.data[2] =
                (ITS_OCTET)userInput;
            break;

        case TCPPROB_RETURN_ERR:
            printf(" (%d) Unrecognized invoke ID \n",
                TCPPROB_SPEC_ERR_UNREC_INVOKE_ID);
            printf(" (%d) Return Error unexpected \n",
                TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR);
            printf(" (%d) Unrecognized error \n", 
                TCPPROB_SPEC_ERR_UNREC_ERROR);
            printf(" (%d) Unexpected error\n",
                TCPPROB_SPEC_ERR_UNEXPECTED_ERROR);
            printf(" (%d) Mistyped parameter", 
                TCPPROB_SPEC_ERR_MISTYPED_PARAM);

            printf("\n Enter Return Error Problem -> ");
            scanf("%d", &userInput);
            TC_Comp->u.reject.problem.data[2] =
                (ITS_OCTET)userInput;
            break;
        }
        /* setting the length */
        TC_Comp->u.reject.problem.len = 3;
        TC_Comp->u.reject.problem.data[1] = 1;
    }
    else
    {
        printf("\n Setting problem code total length to 0 (not present).");
        TC_Comp->u.reject.problem.len = 0;
        TC_Comp->u.reject.problem.data[0] = 0;
        TC_Comp->u.reject.problem.data[1] = 0;
    }
}


/*************************************************************************
 *
 * Purpose: To set a TC_U_Cancel Primitive.
 *
 * Return values: None.
 *
 *************************************************************************/
void setTC_U_Cancel(TCAP_CPT* TC_Comp)
{
    printf("\n ** Info: Going to set TC_U_CANCEL.\n");
    TC_Comp->ptype = TCPPT_TC_U_CANCEL;

    /* Setting invoke id */
    setInvokeID(&TC_Comp->u.cancel.invoke_id);
}

void setTC_U_TimerReset(TCAP_CPT* TC_Comp)
{
    printf("\n ** Info: Going to set TC_U_TimerReset.\n");
    TC_Comp->ptype = TCAP_PT_TC_TIMER_RESET;

    /* Setting invoke id */
    setInvokeID(&TC_Comp->u.timerReset.invoke_id);
}

/*************************************************************************
 *
 * Purpose: will display on the screen a TCAP Transaction.
 *
 * Return values: None.
 *
 *************************************************************************/
void
displayTransaction(ITS_HDR header, TCAP_DLG* transaction,
                   ITS_BOOLEAN indication)
{
    int index = 0;

    switch (transaction->ptype)
    {
    case TCPPT_TC_UNI:
        printf("\n TC_Uni (dialogue id: %d)", header.context.dialogue_id); 

        if (transaction->u.uni.orig_addr.len)
        {
            printf("\n Calling Party Address: ");
            displaySCCPAddress(&transaction->u.uni.orig_addr);
        }
        else
        {
            printf("\n Calling Party Address: Not present");
        }

        if (transaction->u.uni.dest_addr.len)
        {
            printf("\n Called Party Address: ");
            displaySCCPAddress(&transaction->u.uni.dest_addr);        
        }
        else
        {
            printf("\n Called Party Address: Not present");
        }

        /* Quality of service */
        if (transaction->u.uni.qos.indicator)
        {
            /* qos indicator is set */
            printf("\n Quality of service (%d): %s.",
                   transaction->u.uni.qos.indicator,
                   getText_qosInd(transaction->u.uni.qos.indicator));
        }
        else
        {
            printf("\n Quality of service not present.");
        }

        /* Checking if Application Context Name present. */
        printf("\n Application Context Name (length: %d).",
               transaction->u.uni.ac_name.len);
        if (transaction->u.uni.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.uni.ac_name.len; index ++)
            {
                printf("0x%02x ", transaction->u.uni.ac_name.data[index]);
            }            
        }

        /* Checking if User Information present. */
        printf("\n User Information (length: %d).",
               transaction->u.uni.user_info.len);
        if (transaction->u.uni.user_info.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.uni.user_info.len; index ++)
            {
                printf("0x%02x ", transaction->u.uni.user_info.data[index]);
            }
        }

        /* Check if component is present only for indication. */
        if (indication)
        {
            printf("\n Component%s present.",
                ((transaction->u.uni.cpt_present) ? 
                "(s) is(are)" : " not"));
        }
        break;

    case TCPPT_TC_BEGIN:            
        printf("\n TC_Begin (dialogue id: %d)", header.context.dialogue_id); 
        
        if (transaction->u.begin.orig_addr.len)
        {
            printf("\n Calling Party Address: ");
            displaySCCPAddress(&transaction->u.begin.orig_addr);
        }
        else
        {
            printf("\n Calling Party Address: Not present");
        }

        if (transaction->u.begin.dest_addr.len)
        {
            printf("\n Called Party Address: ");
            displaySCCPAddress(&transaction->u.begin.dest_addr);        
        }
        else
        {
            printf("\n Called Party Address: Not present");
        }

        /* Quality of service */
        if (transaction->u.begin.qos.indicator)
        {
            /* qos indicator is set */
            printf("\n Quality of service (%d): %s.",
                   transaction->u.begin.qos.indicator,
                   getText_qosInd(transaction->u.begin.qos.indicator));
        }
        else
        {
            printf("\n Quality of service not present.");
        }

        /* Checking if Application Context Name present. */
        printf("\n Application Context Name (length: %d).",
               transaction->u.begin.ac_name.len);
        if (transaction->u.begin.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.begin.ac_name.len; index ++)
            {
                printf("0x%02x ", transaction->u.begin.ac_name.data[index]);
            }            
        }

        /* Checking if User Information present. */
        printf("\n User Information (length: %d).",
               transaction->u.begin.user_info.len);
        if (transaction->u.begin.user_info.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.begin.user_info.len; index ++)
            {
                printf("0x%02x ", transaction->u.begin.user_info.data[index]);
            }
        }

        /* Check if component is present only for indication. */
        if (indication)
        {
            printf("\n Component%s present.",
                ((transaction->u.begin.cpt_present) ? 
                "(s) is(are)" : " not"));
        }
        break;

    case TCPPT_TC_END:
        printf("\n TC_End (dialogue id: %d)", header.context.dialogue_id);
        /* Quality of Service */
        if (transaction->u.begin.qos.indicator)
        {
            /* qos indicator is set */
            printf("\n Quality of service (%d): %s.",
                   transaction->u.end.qos.indicator,
                   getText_qosInd(transaction->u.end.qos.indicator));
        }
        else
        {
            printf("\n Quality of service not present.");
        }

        /* termination */
        printf("\n Termination is set to %s.",
            ((transaction->u.end.termination) ? "Pre-arranged end" :
             "Basic end"));
        
        /* Checking if Application Context Name present. */
         printf("\n Application Context Name (length: %d).",
               transaction->u.end.ac_name.len);
        if (transaction->u.end.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.end.ac_name.len; index ++)
            {
                printf("0x%02x ", transaction->u.end.ac_name.data[index]);
            }            
        }

        /* Checking if User Information present. */
        printf("\n Application Context Name (length: %d).",
               transaction->u.end.ac_name.len);
        if (transaction->u.end.user_info.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.end.user_info.len; index ++)
            {
                printf("0x%02x ", transaction->u.end.user_info.data[index]);
            }
        }

        /* Check if component is present only for indication. */
        if (indication)
        {
            printf("\n Component%s present.",
                ((transaction->u.end.cpt_present) ? 
                "(s) is(are)" : " not"));
        }
        break;

    case TCPPT_TC_CONTINUE:
        printf("\n TC_Continue (dialogue id: %d)", header.context.dialogue_id);
        /* Quality of service */
        if (transaction->u.cont.qos.indicator)
        {
            /* qos indicator is set */
            printf("\n Quality of service (%d): %s.",
                   transaction->u.cont.qos.indicator,
                   getText_qosInd(transaction->u.cont.qos.indicator));
        }
        else
        {
            printf("\n Quality of service not present.");
        }

        /* Check if CgPA is present only for Request if confirm new dialogue. */
        if ( (!indication) && (transaction->u.cont.orig_addr.len > 0))
        {
            printf("\n Calling Party Address (optional only when confirm): ");
            displaySCCPAddress(&transaction->u.cont.orig_addr);
        }

        /* Checking if Application Context Name present. */
        printf("\n Application Context Name (length: %d).",
               transaction->u.cont.ac_name.len);
        if (transaction->u.cont.ac_name.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.cont.ac_name.len; index ++)
            {
                printf("0x%02x ", transaction->u.cont.ac_name.data[index]);
            }
        }

       /* Checking if User Information present. */
        printf("\n User Information (length: %d).",
               transaction->u.cont.user_info.len);
        if (transaction->u.cont.user_info.len > 0)
        {
            printf("\n Data: ");
            for (index = 0; index < transaction->u.cont.user_info.len; index ++)
            {
                printf("0x%02x ", transaction->u.cont.user_info.data[index]);
            }
        }

        /* Check if component is present only for indication. */
        if (indication)
        {
            printf("\n Component%s present.",
                ((transaction->u.cont.cpt_present) ? 
                "(s) is(are)" : " not"));
        }
        break;

    case TCPPT_TC_P_ABORT:
    case TCPPT_TC_U_ABORT:
        printf("\n Received TC_%s_Abort (dialogue id: %d)." ,
               ((transaction->ptype == TCPPT_TC_U_ABORT) ?
               "U" : "P"), header.context.dialogue_id);
        /* If we receive a TC_P_Abort, printing the Abort reason only. */
        if (transaction->ptype == TCPPT_TC_P_ABORT)
        {
            switch(transaction->u.abort.abort_reason)
            {
            case TCPABT_REASON_UNREC_MSG_TYPE:
                printf("\n Abort reason: Unrecognized Message Type.");
                break;
            case TCPABT_REASON_UNREC_TRANS_ID:
                printf("\n Abort reason: Unrecognized Transaction ID.");
                    break;
            case TCPABT_REASON_BADLY_STRUCT_TRANS_PORT:
                printf("\n Abort reason: Badly Formatted Transaction Portion.");
                break;
            case TCPABT_REASON_INCORRECT_TRANS_PORT:
                printf("\n Abort reason: Incorrect Transaction Portion.");
                break;
            case TCPABT_REASON_RES_UNAVAIL:
                printf("\n Abort reason: Resource Limitation.");
                break;
            default:
                printf("\n Abort reason: 0x%02x.",
                       transaction->u.abort.abort_reason);
                break;
            }
        }
        /* We did receive a TC_U_Abort */
        else
        {
            switch(transaction->u.abort.abort_reason)
            {
            case TCPUABT_AC_NOT_SUP:
                printf("\n Abort reason: Application context not supported.");
                break;
            case TCPUABT_USER_DEFINED:
                printf("\n abort reason: User defined.");
                    break;
            default:
                printf("\n abort reason: 0x%02x.",
                       transaction->u.abort.abort_reason);
                break;
            }

            /* Checking if Application Context Name present. */
            printf("\n Application Context Name (length: %d).",
                       transaction->u.abort.ac_name.len);
            if (transaction->u.abort.ac_name.len > 0)
            {
                printf("\n Data: ");
                for (index = 0; index < transaction->u.abort.ac_name.len;
                     index ++)
                {
                    printf("0x%02x ", transaction->u.abort.ac_name.data[index]);
                }
            }

            /* Checking if User Information present. */
            printf("\n User Information (length: %d).",
                   transaction->u.abort.user_info.len);
            if (transaction->u.abort.user_info.len > 0)
            {
                printf("\n Data: ");
                for (index = 0; index < transaction->u.abort.user_info.len;
                     index ++)
                {
                    printf("0x%02x ", transaction->u.abort.user_info.data[index]);
                }
            }
        }
        break;

    case TCPPT_TC_NOTICE:
        printf("\n TC_Notice (dialogue id: %d)", header.context.dialogue_id); 

        if (transaction->u.notice.report_cause > 0x0B)
        {
            printf("\n Return Cause: 0x%02x",
                transaction->u.notice.report_cause);
        }
        else
        {
            printf("\n Return Cause: %s", 
                   notice_returnCause[transaction->u.notice.report_cause]);
        }
        break;            
    }
}


/*************************************************************************
 *
 * Purpose: will display on the screen a TCAP Component.
 *
 * Return values: None.
 *
 *************************************************************************/
void
displayComponent(ITS_HDR header, TCAP_CPT* component, ITS_BOOLEAN indication)
{
    int index = 0;
    switch (component->ptype)
    {
    /* Printing TC_Invoke Cpt */
    case TCPPT_TC_INVOKE:
        printf("\n TC_Invoke (dialogue id: %d)", 
                   header.context.dialogue_id);

        /* Invoke id */
        printf("\n Invoke Id (total length = %d): ", 
               component->u.invoke.invoke_id.len);
        if (component->u.invoke.invoke_id.len > 0)
        {
            for (index = 0; index < component->u.invoke.invoke_id.len; index ++)
            {
                printf("0x%02x ", component->u.invoke.invoke_id.data[index]);
            }
        }

        /* linked id */
        printf("\n Linked Id (total length = %d): ", 
               component->u.invoke.linked_id.len);
        if (component->u.invoke.linked_id.len > 0)
        {
            for (index = 0; index < component->u.invoke.linked_id.len; index ++)
            {
                printf("0x%02x ", component->u.invoke.linked_id.data[index]);
            }
        }
        
        /* if cpt is a request: print the op class and timeout */
        if (!indication)
        {
            printf("\n Operation class: %d",  component->u.invoke.opClass);
            printf("\n Timeout (in seconds): %d", component->u.invoke.timeout);
        }

        /* Operation Code */
        printf("\n Operation code (Total length = %d): ", 
               component->u.invoke.operation.len);
        if (component->u.invoke.operation.len > 0)
        {
            if (component->u.invoke.operation.data[0] == 
                TCAP_PN_GLOBAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else if (component->u.invoke.operation.data[0] == 
                     TCAP_PN_LOCAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else
            {
                printf("\n Operation Code Tag unknown (0x%02x):",
                       component->u.invoke.operation.data[0]);
            }

            for (index = 0; index < component->u.invoke.operation.len; index ++)
            {
                printf("0x%02x ", component->u.invoke.operation.data[index]);
            }
        }

        /* Parameters */
        printf("\n Parameters (total length: %d):",
                   component->u.invoke.param.len);
        if (component->u.invoke.param.len > 0)
        {            
            printf("\n Data: ");
            for (index = 0; index < component->u.invoke.param.len; index ++)
            {
                printf("0x%02x ", component->u.invoke.param.data[index]);
            }
        }
        
        /* Check if this is the last component only for indication. */
        if (indication)
        {
            printf("\n This is%s the last component.",
                ((component->last_component) ? "" : " not"));
        }
           
        break;

    case TCPPT_TC_RESULT_L:
    case TCPPT_TC_RESULT_NL:
        printf("\n TC_Result_%s (dialogue id: %d)",
               ((component->ptype == TCPPT_TC_RESULT_L) ? "L" : "NL"),
               header.context.dialogue_id);

        /* Invoke id */
        printf("\n Invoke Id (total length = %d): ", 
               component->u.result.invoke_id.len);
        if (component->u.result.invoke_id.len > 0)
        {
            for (index = 0; index < component->u.result.invoke_id.len; index ++)
            {
                printf("0x%02x ", component->u.result.invoke_id.data[index]);
            }
        }
        
        /* Operation Code */
        printf("\n Operation code (Total length = %d): ", 
               component->u.result.operation.len);
        if (component->u.result.operation.len > 0)
        {
            if (component->u.result.operation.data[0] == 
                TCAP_PN_LOCAL_OP_TAG_CCITT)
            {
                printf("\n Local Operation Code: ");
            }
            else if (component->u.result.operation.data[0] == 
                TCAP_PN_GLOBAL_OP_TAG_CCITT)
            {
                printf("\n Global Operation Code: ");
            }
            else
            {
                printf("\n Operation Code Tag unknown (0x%02x):",
                       component->u.result.operation.data[0]);
            }

            for (index = 0; index < component->u.result.operation.len; index ++)
            {
                printf("0x%02x ", component->u.result.operation.data[index]);
            }
        }

        /* Parameters */
        printf("\n Parameters (total length: %d):",
                   component->u.result.param.len);
        if (component->u.result.param.len > 0)
        {            
            printf("\n Data: ");
            for (index = 0; index < component->u.result.param.len; index ++)
            {
                printf("0x%02x ", component->u.result.param.data[index]);
            }
        }

        /* Check if this is the last component only for indication. */
        if (indication)
        {
            printf("\n This is%s the last component.",
                ((component->last_component) ? "" : " not"));
        }
        break;

    case TCPPT_TC_U_ERROR:
        printf("\n TC_U_Error (dialogue id: %d)", 
                   header.context.dialogue_id);

        /* Invoke id */
        printf("\n Invoke Id (total length = %d): ", 
               component->u.error.invoke_id.len);
        if (component->u.error.invoke_id.len > 0)
        {
            for (index = 0; index < component->u.error.invoke_id.len; index ++)
            {
                printf("0x%02x ", component->u.error.invoke_id.data[index]);
            }
        }

        /* Error Code */
        printf("\n Error code (total length = %d): ", 
               component->u.error.error.len);
        if (component->u.error.error.len > 0)
        {
            if (component->u.error.error.data[0] == 
                TCAP_PN_LOCAL_ERR_TAG_CCITT)
            {
                printf("\n Local Error Code: ");
            }
            else if (component->u.error.error.data[0] == 
                TCAP_PN_GLOBAL_ERR_TAG_CCITT)
            {
                printf("\n Global Error Code: ");
            }
            else
            {
                printf("\n Error Code Tag unknown (0x%02x):",
                       component->u.error.error.data[0]);
            }

            for (index = 0; index < component->u.error.error.len; index ++)
            {
                printf("0x%02x ", component->u.error.error.data[index]);
            }
        }
        
        /* Parameters */
        printf("\n Parameters (total length: %d):",
                   component->u.error.param.len);
        if (component->u.error.param.len > 0)
        {            
            printf("\n Data: ");
            for (index = 0; index < component->u.error.param.len; index ++)
            {
                printf("0x%02x ", component->u.error.param.data[index]);
            }
        }
        
        /* Check if this is the last component only for indication. */
        if (indication)
        {
            printf("\n This is%s the last component.",
                ((component->last_component) ? "" : " not"));
        }
        break;
    
    case TCPPT_TC_L_CANCEL:
    case TCPPT_TC_U_CANCEL:
        printf("\n TC_%s_Cancel (dialogue id: %d)",
               ((component->ptype == TCPPT_TC_L_CANCEL) ? "L" : "U"),
               header.context.dialogue_id);

        /* Invoke id */
        printf("\n Invoke Id (total length = %d): ", 
               component->u.cancel.invoke_id.len);
        if (component->u.cancel.invoke_id.len > 0)
        {
            for (index = 0; index < component->u.cancel.invoke_id.len; index ++)
            {
                printf("0x%02x ", component->u.cancel.invoke_id.data[index]);
            }
        }
        break;
    
    case TCPPT_TC_L_REJECT:
    case TCPPT_TC_U_REJECT:
    case TCPPT_TC_R_REJECT:
        printf("\n TC_%s_Reject (dialogue id: %d)",
               ((component->ptype == TCPPT_TC_L_REJECT) ? "L" :
               ((component->ptype == TCPPT_TC_U_REJECT) ? "U" : "R")),
               header.context.dialogue_id);

        /* Invoke id */
        printf("\n Invoke Id (total length = %d): ", 
               component->u.reject.invoke_id.len);
        if (component->u.reject.invoke_id.len > 0)
        {
            for (index = 0; index < component->u.reject.invoke_id.len; index ++)
            {
                printf("0x%02x ", component->u.reject.invoke_id.data[index]);
            }
        }

        /* printing the problem */
        switch (component->u.reject.problem.data[0])
        {
        case TCPPROB_GENERAL:
            switch (component->u.reject.problem.data[2])
            {
            case TCPPROB_SPEC_GEN_UNREC_COMP:
                printf("\n General problem: Unrecognized component");
                break;
            case TCPPROB_SPEC_GEN_MISTYPED_COMP:
                printf("\n General problem: Mistyped component");
                break;
            case TCPPROB_SPEC_GEN_BADLY_STRUCT_COMP:
                printf("\n General problem: Badly structured component");
                break;
            default:
                printf("\n Unknown General problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCPPROB_INVOKE:
            switch (component->u.reject.problem.data[2])
            {
            case TCPPROB_SPEC_INV_DUPLICATE_INV_ID:
                printf("\n Invoke problem: Duplicate invoke ID");
                break;
            case TCPPROB_SPEC_INV_UNREC_OP_CODE:
                printf("\n Invoke problem: Unrecognized operation");
                break;
            case TCPPROB_SPEC_INV_MISTYPED_PARAM:
                printf("\n Invoke problem: Mistyped parameter");
                break;
            case TCPPROB_SPEC_INV_RESOURCE_LIMIT:
                printf("\n Invoke problem: Resource limitation");
                break;
            case TCPPROB_SPEC_INV_INITIATE_RELEASE:
                printf("\n Invokev problem: Initiating release");
                break;
            case TCPPROB_SPEC_INV_UNREC_LINKED_ID:
                printf("\n Invoke problem: Unrecognized linked ID");
                break;
            case TCPPROB_SPEC_INV_UNEXPECTED_LINK_RESP:
                printf("\n Invoke problem: Linked response unexpected");
                break;
            case TCPPROB_SPEC_INV_UNEXPECTED_LINKED_OP:
                printf("\n Invoke problem: Unexpected Linked operation");
                break;
            default:
                printf("\n Unknown Invoke problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCPPROB_RETURN_RES:
            switch (component->u.reject.problem.data[2])
            {
            case TCPPROB_SPEC_RES_UNREC_INVOKE_ID:
                printf("\n Return Result problem: Unrecognized invoke ID");
                break;
            case TCPPROB_SPEC_RES_UNEXPECTED_RET_RES:
                printf("\n Return Result problem: Return result unexpected");
                break;
            case TCPPROB_SPEC_RES_MISTYPED_PARAM:
                printf("\n Return Result problem: Mistyped parameter");
                break;
            default:
                printf("\n Unknown Return Result problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        case TCPPROB_RETURN_ERR:
            switch (component->u.reject.problem.data[2])
            {
            case TCPPROB_SPEC_ERR_UNREC_INVOKE_ID:
                printf("\n Return Error problem: Unrecognized invoke ID");
                break;
            case TCPPROB_SPEC_ERR_UNEXPECTED_RET_ERROR:
                printf("\n Return Error problem: Return Error unexpected");
                break;
            case TCPPROB_SPEC_ERR_UNREC_ERROR:
                printf("\n Return Error problem: Unrecognized error");
                break;
            case TCPPROB_SPEC_ERR_UNEXPECTED_ERROR:
                printf("\n Return Error problem: Unexpected error");
                break;
            case TCPPROB_SPEC_ERR_MISTYPED_PARAM:
                printf("\n Return Error problem: Mistyped parameter");
                break;
            default:
                printf("\n Unknown Return Error problem (0x%02)",
                       component->u.reject.problem.data[2]);
                break;
            }
            break;

        default:
            printf("\n Unknown Problem Tag (0x%02)",
                   component->u.reject.problem.data[0]);
            break;
        }
        /* Check if this is the last component only for indication. */
        if (indication)
        {
            printf("\n This is%s the last component.",
                ((component->last_component) ? "" : " not"));
        }
        break;            
    }
}


/*************************************************************************
 *
 * Purpose: This method constructs a GTT entry in the destination address.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setGTT(ITS_OCTET* addrIndicator, ITS_OCTET* gttInfo, int* len)
{
    int userSelection = 0;

    /* temporary information used to set gtt information */
    ITS_OCTET tmpAddressIndicator = *addrIndicator;
    int gttEncoding = 0;
    ITS_OCTET translationType = 0;
    ITS_OCTET natureAddress = 0;
    ITS_OCTET encoding = 0;
    ITS_OCTET numbering = 0;
    int tmpLen = 0;
    /* Max Number of digits in GTT for ITU is 48. +4 just in case */
    char gttDigits[52] ;

    /* index to browse back and forth in gttInfo array */
    int gttInfoIndex = 0;

    /* number of digits */
    int nbDigits = 0;
    int i;

    /*
     * Setting GGT Encoding.
     * There is more option for ITU than there are for ANSI.
     */
    printf("\n Enter GTT Encoding:");
    printf("\n [1] Perform GTT with Nature of Address only.");
    printf("\n [2] Perform GTT Translation only.");
    printf("\n [3] Perform GTT Translation with Encoding Scheme and Numbering Plan.");
    printf("\n [4] Perform GTT Translation with both Nat of Addr and Scheme + Plan.");
    printf("\n Enter your selection -> ");
    scanf("%d", &gttEncoding);

    switch (gttEncoding)
    {
    case 1:
        /* GTT Translation with Nature of Address */
        tmpAddressIndicator |= SCCP_CPA_GTTI_NATURE;
        break;
    case 2:
        /* GTT Translation Only */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
        break;
    case 3:
        /* GTT Translation with Encoding Scheme and Numbering Plan */
        tmpAddressIndicator |= SCCP_CPA_GTTI_TNE;
        break;
    case 4:
        /* GTT Translation with both Nat of Addr and Scheme + Plan */
        tmpAddressIndicator |= SCCP_CPA_GTTI_ALL;
        break;
    default:
        printf("\n Invalid selection, using GTT Translation Only.");
        tmpAddressIndicator |= SCCP_CPA_GTTI_TRANS;
        break;
    }

    /* Setting Translation Type (not valid for Nature of Addr). */
    if (gttEncoding != 1)
    {
    printf("\n Enter GTT Translation Type (0-255): ");
    scanf("%d", &userSelection);
    translationType = (ITS_OCTET)userSelection;
    gttInfo[gttInfoIndex++] = translationType;
    tmpLen++;
    }

    /*
     * Based on GTT Encoding:
     * ask user for Nature of Address Indicator,
     * and/or Encoding Scheme + Numbering Plan
     */
    switch (tmpAddressIndicator & SCCP_CPA_GTTI_MASK)
    {
#ifdef USE_CCITT_SCCP
    case SCCP_CPA_GTTI_NATURE:
        /* Need to provide Nature of Address */
        printf("\n Enter GTT Nature of Address Indicator (0-127): ");
        scanf("%d", &userSelection);
        natureAddress = (ITS_OCTET)userSelection;
        /*  Need to know number of digits to set or clear MSB
         * for nature of Address Indicator.
         * Will be added to gttInfo array when requesting digits.
         */
        break;
#endif

    case SCCP_CPA_GTTI_TRANS:
        /* Nothing to set for that one */
        break;

    case SCCP_CPA_GTTI_TNE:
        /* Need to provide Encoding Scheme and Numbering Plan */
        printf("\n Enter GTT Encoding Scheme (0-15): " );
        scanf("%d", &userSelection);
        encoding = (ITS_OCTET)userSelection;
        printf(" Enter GTT Numbering Plan (0-15)");
        scanf("%d", &userSelection);
        numbering = (ITS_OCTET)userSelection;
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;
        break;

#ifdef USE_CCITT_SCCP
    case SCCP_CPA_GTTI_ALL:
        /* Need to provide  Scheme + Plan then Nat of Addr*/
        printf("\n Enter GTT Encoding Scheme (0-15): ");
        encoding = (ITS_OCTET)userSelection;
        printf(" Enter GTT Numbering Plan (0-15): ");
        scanf("%d", &userSelection);
        numbering = (ITS_OCTET)userSelection;
        gttInfo[gttInfoIndex++] = (encoding | (numbering << 4));
        tmpLen++;

        printf(" Enter GTT Nature of Address Indicator (0-127): ");
        scanf("%d", &userSelection);
        natureAddress = (ITS_OCTET)userSelection;
        gttInfo[gttInfoIndex++] = natureAddress;
        tmpLen++;
        break;
#endif

    default:
        break;
    }

    /* Ask User for GTT digits. */
    printf(" Address Information (ex: 1800456) -> ");
    scanf("%s", gttDigits);

    nbDigits = strlen(gttDigits);
    
    /*
     * For GTT Encoding Nature of Address Indicator,
     * if Odd number of digits, will set last bit.
     */
    if ((tmpAddressIndicator & SCCP_CPA_GTTI_MASK) == SCCP_CPA_GTTI_NATURE) 
    {
        if ((nbDigits % 2) != 0)
        {
            /* Odd Number of digits: setting MSB */
            gttInfo[gttInfoIndex++] = (natureAddress | 0x80);
            tmpLen++;
        }
        else
        {
            /* Even Number of digits, clearing MSB */
            gttInfo[gttInfoIndex++] = (natureAddress & 0x7F);
            tmpLen++;
        }
    }

    /* Putting digits into GTT Info array */
    for (i = 0; i < nbDigits; i++)
    {
         if (i & 1)
         {
             /* MSB digit*/
             gttInfo[gttInfoIndex++] |= ((gttDigits[i] - 0x30) << 4);            
         }
         else
         {
             /* LSB digit*/
             gttInfo[gttInfoIndex] = (gttDigits[i] - 0x30);
         }
    }

    /* adding the len of digits, if odd number, must add + 1 */
    tmpLen += (nbDigits / 2);
    if (nbDigits & 1)
    {
        tmpLen++;
    }

    /* Updating address Indicator to reflect GTT Encoding */
    *addrIndicator = tmpAddressIndicator;

    /* Updating length of GTT Info */
    *len = tmpLen;
}


/*************************************************************************
 *
 * Purpose: will set the Invoke id (or Linked id) of a TC_Component.
 *
 * Return values: None.
 *
 *************************************************************************/
void setInvokeID(CPT_INV_ID* invokeId)
{
    int userInput = 0;

    /* Setting Invoke Id */
    printf("\n Select type of Invoke Id:\n");
    printf(" (1) Random invoke id \n");
    printf(" (2) Invalid invoke id tag \n");
    printf(" (3) Invoke id not present \n");
    printf(" (4) Invoke id with invalid length \n");
    printf(" (5) User provided invoke id ");
    printf("\n Enter your selection -> ");
    scanf("%d", &userInput);
    if ((userInput > 5) || (userInput < 1))
    {
        printf(" ** Warning: Invalid Selection. Invoke id set to random.\n");
        userInput = 1;
    }

    switch (userInput)
    {
    /* random Invoke id or user provided invoke id, or Invalid Tag */
    case 1:
    case 2:
    case 5:
        /* Total Length */
        invokeId->len = 0x03;
        /* Correct Tag */
        invokeId->data[0] = TCPPN_INVOKE_TAG;
        /* correct lenght */
        invokeId->data[1] = 0x01;
        /* random invoke id */
        if (userInput == 1)
        {
            invokeId->data[2] = invoke_id++;
        }
        else if (userInput == 5)
        {
            printf(" Enter Invoke id -> ");
            scanf("%d", &userInput);
            invokeId->data[2] = (ITS_OCTET)userInput;
        }
        else
        {
            invokeId->data[0] = (TCPPN_INVOKE_TAG + 0x05);
            invokeId->data[2] = invoke_id++;
        }
        break;

    /* invoke id not present */
    case 3:
        /* setting both length to zero */
        invokeId->len = 0x00;
        invokeId->data[1] = 0x00;
        break;

    /* invalid length (more than one byte) */
    case 4:
        /* Total Length */
        invokeId->len = 0x04;
        /* Correct Tag */
        invokeId->data[0] = TCPPN_INVOKE_TAG;
        /* lentgh is 2 bytes instead of 1 */
        invokeId->data[1] = 0x02;
        invokeId->data[2] = 0x34;
        invokeId->data[3] = 0x45;
        break;
    }
}


/*************************************************************************
 *
 * Purpose: will set the Local Operation Code of a TC_Component.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setOperationCode(CPT_OP* localOpCode)
{
    int userInput = 0;

    /* Setting Local Operation Code */
    printf("\n Select type of Operation :\n");
    printf(" (1) User provided Local Operation Code \n");
    printf(" (2) Invalid Local Operation Code tag \n");
    printf(" (3) Local Operation not present \n");
    printf(" (4) Local Operation with invalid length \n");
    printf(" (5) Global Operation Code (Test number: 2.1.7.4.2) ");
    printf("\n Enter your selection -> ");
    scanf("%d", &userInput);
    if ((userInput > 5) || (userInput < 1))
    {
        printf(" ** Warning: Invalid Selection. Local Operation set to user provided.\n");
        userInput = 1;
    }

    switch (userInput)
    {
    /* user provided Operation Code */
    case 1:
        /* Total Length */
        localOpCode->len = 0x03;
        /* Correct Tag */
        localOpCode->data[0] = TCPPN_LOCAL_OP_TAG;
        /* correct length */
        localOpCode->data[1] = 0x01;
        printf(" Enter Local Operation Code -> ");
        scanf("%d", &userInput);
        localOpCode->data[2] = (ITS_OCTET)userInput;
        break;

    /* invalid Operation Tag */
    case 2:
        /* Total Length */
        localOpCode->len = 0x03;
        /* invalid Tag */
        localOpCode->data[0] = (TCPPN_LOCAL_OP_TAG + 0x05);
        /* correct length */
        localOpCode->data[1] = 0x01;
        /* random Operation Code */
        localOpCode->data[2] = 0x43;
        break;

    /* Local Operation not present */
    case 3:
        /* setting both length to zero */
        localOpCode->len = 0x00;
        localOpCode->data[1] = 0x00;
        break;

    /* invalid length (more than one byte) */
    case 4:
        /* Total Length */
        localOpCode->len = 0x04;
        /* Correct Tag */
        localOpCode->data[0] = TCPPN_LOCAL_OP_TAG;
        /* lentgh is 2 bytes instead of 1 */
        localOpCode->data[1] = 0x02;
        localOpCode->data[2] = 0x34;
        localOpCode->data[3] = 0x45;
        break;

    /* Global Op code */
    case 5:
        /* Total Length */
        localOpCode->len = 0x05;
        /* Correct Tag */
        localOpCode->data[0] = TCPPN_GLOBAL_OP_TAG;
        /* lentgh is 3 bytes */
        localOpCode->data[1] = 0x03;
        localOpCode->data[2] = 0x00;
        localOpCode->data[3] = 0x17;
        localOpCode->data[4] = 0x85;
        break;
    }
}


/*************************************************************************
 *
 * Purpose: will set the Local Error Code of a TC_U_Error.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setLocalErrorCode(CPT_ERROR_CODE* localErrCode)
{
    int userInput = 0;

    /* Setting Local Error Code */
    printf("\n Select type of Local Error :\n");
    printf(" (1) User provided Local Error Code \n");
    printf(" (2) Invalid Local Error Code tag \n");
    printf(" (3) Local Error not present \n");
    printf(" (4) Local Error with invalid length ");
    printf("\n Enter your selection -> ");
    scanf("%d", &userInput);
    if ((userInput > 4) || (userInput < 1))
    {
        printf(" ** Warning: Invalid Selection. Local Error set to user provided.\n");
        userInput = 1;
    }

    switch (userInput)
    {
    /* user provided Operation Code */
    case 1:
        /* Total Length */
        localErrCode->len = 0x03;
        /* Correct Tag */
        localErrCode->data[0] = TCAP_PN_LOCAL_ERR_TAG_CCITT;
        /* correct length */
        localErrCode->data[1] = 0x01;
        printf(" Enter Local Error Code -> ");
        scanf("%d", &userInput);
        localErrCode->data[2] = (ITS_OCTET)userInput;
        break;

    /* invalid Error Tag */
    case 2:
        /* Total Length */
        localErrCode->len = 0x03;
        /* invalid Tag */
        localErrCode->data[0] = (TCAP_PN_LOCAL_ERR_TAG_CCITT + 0x05);
        /* correct length */
        localErrCode->data[1] = 0x01;
        /* random Error Code */
        localErrCode->data[2] = 0x43;
        break;

    /* Local Error not present */
    case 3:
        /* setting both length to zero */
        localErrCode->len = 0x00;
        localErrCode->data[1] = 0x00;
        break;

    /* invalid length (more than one byte) */
    case 4:
        /* Total Length */
        localErrCode->len = 0x04;
        /* Correct Tag */
        localErrCode->data[0] = TCAP_PN_LOCAL_ERR_TAG_CCITT;
        /* lentgh is 2 bytes instead of 1 */
        localErrCode->data[1] = 0x02;
        localErrCode->data[2] = 0x34;
        localErrCode->data[3] = 0x45;
        break;
    }
}


/*************************************************************************
 *
 * Purpose: This method constructs the SCCP protocol class.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setProtocolClass(ITS_OCTET* protocolClass)
{
    int pClass = 0;
    int msg_Handling = 0;
    ITS_OCTET tmp_pClass = 0x00;

    printf("\n Select Class:\n");
    printf(" (1) Class 0: Basic connectionless class \n");
    printf(" (2) Class 1: Sequenced connectionless class");
    printf("\n Enter Class: ");
    scanf("%d", &pClass);
    if ((pClass > 2) || (pClass < 1))
    {
        printf(" ** Warning: Invalid Selection. Class set to Basic connectionless.\n");
        pClass = 1;
    }
    if (pClass == 1)
    {
        tmp_pClass = SCCP_PCLASS_0;
    }
    else
    {
        tmp_pClass = SCCP_PCLASS_1;
    }

    printf("\n Select Message Handling:\n");
    printf(" (1) No special options \n");
    printf(" (2) Return message on error \n");
    printf(" (3) Spare ");
    printf("\n Enter Message Handling: ");
    scanf("%d", &msg_Handling);
    if ((msg_Handling > 3) || (msg_Handling < 1))
    {
        printf(" ** Warning: Invalid Selection. Message Handling set to No special options \n");
        msg_Handling = 1;
    }

    if (msg_Handling == 2)
    {
        tmp_pClass |= SCCP_PCLASS_RET_ON_ERR;
    }
    else if (msg_Handling == 3)
    {
        /* random spare value; */
        tmp_pClass |= 0xB0;
    }

    *protocolClass = tmp_pClass;
}


/*************************************************************************
 *
 * Purpose: This method constructs the MTP3 Header.
 *
 * Return values: ITS_SUCCESS if success, "failure code" otherwise.
 *
 *************************************************************************/
int
setMTP3Header(MTP3_HEADER *mtp3_header , SCCP_ADDR cgpa, SCCP_ADDR cdpa)
{
    ITS_OCTET ssn, addrInd = 0;
    ITS_UINT opc = 0;
    ITS_UINT dpc = 0;
    int result = ITS_SUCCESS;

    /* Getting the Point Code  from the Calling and Called Party Addresses. */
    result = SCCP_DecodeAddr(&cgpa, &addrInd, &opc, &ssn, NULL, NULL);
    if (result != ITS_SUCCESS)
    {
        return result;
    }

    result = SCCP_DecodeAddr(&cdpa, &addrInd, &dpc, &ssn, NULL, NULL);
    if (result != ITS_SUCCESS)
    {
        return result;
    }

    /* setting DPC and OPC for MTP3 routing label */
    MTP3_RL_SET_DPC_VALUE(mtp3_header->label, dpc);
    MTP3_RL_SET_OPC_VALUE(mtp3_header->label, opc);

    /* setting SLS */
    MTP3_RL_SET_SLS(mtp3_header->label, 0);
    result = ITS_SUCCESS;

    /* setting SIO to International SCCP */
    mtp3_header->sio = MTP3_SIO_SCCP;


    return result;
}

static ITS_OCTET
getHexFromChar(char inValue)
{
    ITS_OCTET outValue = (ITS_OCTET)inValue;

    if ((outValue >= 0x30) && (outValue <= 0x39))
    {
        return(outValue - 0x30);
    }

    if ((outValue >= 0x41) && (outValue <= 0x46))
    {
        return(outValue - 0x37);
    }

    if ((outValue >= 0x61) && (outValue <= 0x66))
    {
        return(outValue - 0x57);
    }

    return(0);

    return outValue;
}


/*************************************************************************
 *
 * Purpose: This method constructs a TID IE.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setTransactionID(ITS_BOOLEAN originating, ITS_OCTET* data, int *len)
{
    char input_tid[100];
    int index = 0;
    ITS_OCTET tid_tag = 0x00;

    int nbHalfBytes,nbBytes = 0;

    if (originating)
    {
        printf("\n ** Info: Going to set Originating Transaction id.");
        tid_tag = OTID_TAG;
    }
    else
    {
        printf("\n ** Info: Going to set Destination Transaction id.");
        tid_tag = DTID_TAG;
    }

    printf(" Enter (in hex) Transaction ID <0: len of 0, 1: not present> -> ");
    scanf("%s", input_tid);

    nbHalfBytes = strlen(input_tid);

    if (nbHalfBytes == 1)
    {
        ITS_OCTET value = (ITS_OCTET)input_tid[1];
        if ((value - 0x30) == 0)
        {
            /* Length = 0 octet */

            /* TID tag */
            data[nbBytes++] = tid_tag;
            /* TID Len */
            data[nbBytes++] = 0x00;
        }
        else
        {
            /* TID absent */            
        }
    }
    else
    {    
        ITS_OCTET index_tid_ten;

        /* TID tag */
        data[nbBytes++] = tid_tag;
        /* TID Len */
        index_tid_ten = nbBytes;

        data[nbBytes++] = 0x00;

        for (index = 0; index < nbHalfBytes; index++)
        {
            ITS_OCTET highValue = getHexFromChar(input_tid[index++]);
            ITS_OCTET lowValue = getHexFromChar(input_tid[index]);

            data[nbBytes] = (highValue << 4);
            data[nbBytes++] |=  lowValue;
        }

        data[index_tid_ten] = nbBytes - 2;
    }

    *len = nbBytes;
}


/*************************************************************************
 *
 * Purpose: This method constructs the Dialogue portion of a TCAP message.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setDialoguePortion(ITS_OCTET* data, int *len)
{
    printf("\n ** Warning: Not yet implemented.\n");
    *len = 0;
}


/*************************************************************************
 *
 * Purpose: This method constructs the Component portion of a TCAP message.
 *
 * Return values: None.
 *
 *************************************************************************/

void
setComponentPortion(ITS_OCTET* data, int *len)
{
    int index = 0;
    int choice = 0;
    int cptType = 0;
    int inv_id = 0;
    
    /*
     * len of the component and len of the component portion,
     * and sequence tag
     */
    int len_cpt = 0;
    int len_cpt_portion = 0;
    int len_seq_tag = 0;

    ITS_BOOLEAN use_indefinite_form_len_cpt_portion = ITS_FALSE;
    ITS_BOOLEAN use_indefinite_form_len_cpt = ITS_FALSE;
    ITS_BOOLEAN use_sequence_tag = ITS_FALSE;

    /* 
     * index in the array of the len of the component and
     * the len of the component portion, and sequence tag
     */
    int index_cpt_portion_len = 0;
    int index_cpt_len = 0;
    int index_seq_tag = 0;

    /* component portion tag */
    data[index++] = CPT_PORTION_TAG;

    /* Component portion len */
    printf("\n Select encoding of length of component portion tag: ");
    printf("\n (1) Definite short form.");
    printf("\n (2) Definite long form.");
    printf("\n (3) Indefinite form.");    
    printf("\n Enter type of encoding -> ");
    scanf("%d", &choice);
    switch (choice)
    {
    /* definite short form */
    case 1:
        /* does nothing default */
        index_cpt_portion_len = index;
        data[index++] = len_cpt_portion;
        break;

        /* definite long form */
    case 2:
        /*
         * bit 8 must be set for definite long form
         * bit 7 -> 1 number of octets for length 
         */
        data[index++] = 0x81;
        index_cpt_portion_len = index;
        data[index++] = len_cpt_portion;
        break;

    /* indefinite form */
    case 3:
        /* bit 8 must be set for indefinite form */
        data[index++] = 0x80;
        use_indefinite_form_len_cpt_portion = ITS_TRUE;
        break;

    default:
        /* does nothing default */
        printf("\n ** Warning: Invalid selection, using definite short form.");

        index_cpt_portion_len = index;
        data[index++] = len_cpt_portion;
        break;
    }
    /* end choice encoding for component portion len */

    /* component type */
    printf("\n Select component type:\n");
    printf(" (%d) Invoke component \n", CPT_INVOKE_TAG);
    printf(" (%d) Return Result component \n", CPT_R_RESULT_TAG);
    printf(" (%d) Return Error component \n", CPT_R_ERROR_TAG);
    printf(" (%d) Unknown component ", CPT_UNK_TAG);
    printf("\n Enter component Type: ");
    scanf("%d", &cptType);

    if (cptType != CPT_UNK_TAG)
    {
        data[index++] = (ITS_OCTET)(cptType | 0xA0);
    }
    else
    {
        data[index++] = 0xAE;
    }
    /* end component type */

    /* Component len */
    printf("\n Select encoding of length of component:");
    printf("\n (1) Definite short form.");
    printf("\n (2) Definite long form.");
    printf("\n (3) Indefinite form.");    
    printf("\n Enter type of encoding -> ");
    scanf("%d", &choice);
    switch (choice)
    {
    /* definite short form */
    case 1:
        /* does nothing default */
        index_cpt_len = index;
        data[index++] = len_cpt;

        /* updating length of component portion */
        len_cpt_portion += 2; 
        break;

        /* definite long form */
    case 2:
        /*
         * bit 8 must be set for definite long form
         * bit 7 -> 1 number of octets for length 
         */
        data[index++] = 0x81;
        index_cpt_len = index;
        data[index++] = len_cpt;

        /* updating length of component portion */
        len_cpt_portion += 3;
        break;

    /* indefinite form */
    case 3:
        /* bit 8 must be set for indefinite form */
        data[index++] = 0x80;
        use_indefinite_form_len_cpt = ITS_TRUE;

        /* updating length of component portion */
        len_cpt_portion += 2;
        break;

    default:
        /* does nothing default */
        printf("\n ** Warning: Invalid selection, using definite short form.");

        index_cpt_len = index;
        data[index++] = len_cpt;

        /* updating length of component portion */
        len_cpt_portion += 2; 
        break;
    }
    /* end choice encoding for component portion len */

    /* Invoke ID */
    printf("\n Select Invoke ID :");
    printf("\n (1) Valid Invoke ID .");
    printf("\n (2) Length of Invoke ID > 1.");
    printf("\n (3) Length of Invoke ID = 0.");    
    printf("\n (4) Invoke ID is missing.");    
    printf("\n Enter Invoke ID choice -> ");
    scanf("%d", &choice);    
    if (choice != 4)
    {
        data[index++] = TCAP_PN_INVOKE_TAG_CCITT;

        switch (choice)
        {
        /* Valid Invoke Id */        
        case 1:
            data[index++] = 1;
            printf("\n Enter Invoke id (decimal value): ");
            scanf("%d", &inv_id);
            data[index++] = inv_id;

            /* updating length of component portion and component */
            len_cpt_portion += 3; 
            len_cpt += 3;
            break;

        /* Invoke Id Len > 1*/        
        case 2:
            data[index++] = 2;
            data[index++] = 0x81; /* 129 */

            /* updating length of component portion and component */
            len_cpt_portion += 3; 
            len_cpt += 3;
            break;

        /* Invoke Id Len = 0; */        
        case 3:
            data[index++] = 0;

            /* updating length of component portion and component */
            len_cpt_portion += 2; 
            len_cpt += 2; 
            break;

        default:
            printf("\n ** Warning: Invalid selection, using valid invoke id.");
            data[index++] = 1;
            printf("\n Enter Invoke id (decimal value): ");
            scanf("%d", &inv_id);
            data[index++] = inv_id;
            break;
        }
        
    } /* end Invoke Id */    


    if ((cptType == CPT_INVOKE_TAG) || (cptType == CPT_UNK_TAG))
    {
        /* Operation Code */
        printf("\n Do you want to include Operation Code [y/n]? ");
        if (setOption())
        {
            printf("\n Do you want to include Correct Operation Code tag [y/n]? ");
            if (setOption())
            {
                printf("\n Using Random Local Operation Code");
                data[index++] = TCAP_PN_LOCAL_OP_TAG_CCITT;
            }
            else
            {
                data[index++] = 0x22;
            }

            /* len */
            data[index++] = 0x01;
            /* Local Operation Code */
            data[index++] = 0x17;

            /* updating length of component portion and component */
            len_cpt_portion += 3; 
            len_cpt += 3;
        }

        /* no parameters */
    }
    else if (cptType == CPT_R_ERROR_TAG)
    {
        /* Operation Code */
        printf("\n Do you want to include Error Code [y/n]? ");
        if (setOption())
        {
            printf("\n Using Random Local Error Code");
            data[index++] = TCAP_PN_LOCAL_ERR_TAG_CCITT;

            /* len */
            data[index++] = 0x01;
            /* Local Operation Code */
            data[index++] = 0x17;

            /* updating length of component portion and component */
            len_cpt_portion += 3; 
            len_cpt += 3;
        }

        /* no parameters */
        /* no parameters */
    }
    else if (cptType == CPT_R_RESULT_TAG)
    {
        printf("\n Do you want to include Sequence Tag [y/n]? ");
        if (setOption())
        {
            use_sequence_tag = ITS_TRUE;
            data[index++] = SEQUENCE_TAG;
            index_seq_tag = index;
            data[index++] = len_seq_tag;

            /* updating length of component portion and component */
            len_cpt_portion += 2; 
            len_cpt += 2;
        }

        /* Operation Code */
        printf("\n Do you want to include Operation Code [y/n]? ");
        if (setOption())
        {
            printf("\n Using Random Local Operation Code");
            data[index++] = TCAP_PN_LOCAL_OP_TAG_CCITT;

            /* len */
            data[index++] = 0x01;
            /* Local Operation Code */
            data[index++] = 0x17;

            /* updating length of component portion and component and seq tag */
            len_cpt_portion += 3; 
            len_cpt += 3;
            len_seq_tag +=3;
        }

        /* Parameters */
        printf("\n Do you want to include parameters [y/n]? ");
        if (setOption())
        {
            printf("\n Using Random parameters");
            data[index++] = PARAMETER_SET_TAG;
            data[index++] = 0x03;
            data[index++] = 0x0A;
            data[index++] = 0x01;
            data[index++] = 0x81;
            
            /* updating length of component portion and component and seq tag*/
            len_cpt_portion += 5; 
            len_cpt += 5;
            len_seq_tag +=5;
        }

        if (use_sequence_tag)
        {
            data[index_seq_tag] = len_seq_tag;
        }
    }
    
    if (use_indefinite_form_len_cpt)
    {
        printf("\n Do you want to include EOC [y/n]? ");
        if (setOption())
        {
            /* End-of-Octets (tag = 0x00, len = 0x00) */
            data[index++] = 0x00;
            data[index++] = 0x00;

            /* updating length of component portion */
            len_cpt_portion += 2; 
        }
    }
    else
    {
        printf("\n Do you want to use correct length for component [y/n]? ");
        if (setOption())
        {
            data[index_cpt_len] = len_cpt;
        }
        else
        {
            printf("\n Setting length for component to 0 octet ");
            data[index_cpt_len] = 0x00;
        }
    }

    if (use_indefinite_form_len_cpt_portion)
    {
        /* End-of-Octets (tag = 0x00, len = 0x00) */
        data[index++] = 0x00;
        data[index++] = 0x00;
    }
    else
    {
        data[index_cpt_portion_len] = len_cpt_portion;
    }

    *len = index;        
}


/*************************************************************************
 *
 * Purpose: This method sets the P-Abort cause of an Abort TCAP message.
 *
 * Return values: None.
 *
 *************************************************************************/
void
setP_Abort(ITS_OCTET* data, int *len)
{
    int choice = 0;
    int index = 0;

    printf("\n Select type of P-Abort cause:");
    printf("\n (1) Correct P-Abort Cause.");
    printf("\n (2) Invalid P-Abort Cause.");
    printf("\n (3) Invalid length (2 octets) for P-Abort cause.");
    printf("\n Enter type of P-Abort cause -> ");
    scanf("%d", &choice);

    data[index++] = P_ABORT_CAUSE_TAG;
    switch (choice)
    {
    case 1:
        data[index++] = 0x01;
        
        printf("\n Select P-Abort cause:");
        printf("\n (%d) Unrecognized Message Type.",
               TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT);
        printf("\n (%d) Unrecognized Transaction ID.",
               TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT);
        printf("\n (%d) Badly formatted transaction portion.",
               TCAP_ABT_REASON_BADLY_STRUCT_TRANS_PORT_CCITT);
        printf("\n (%d) Incorrect Transaction Portion.",
               TCAP_ABT_REASON_INCORRECT_TRANS_PORT_CCITT);
        printf("\n (%d) Ressource Limitation.",
               TCAP_ABT_REASON_RES_UNAVAIL_CCITT);
        printf("\n Enter P-Abort cause -> ");
        scanf("%d", &choice);
        if ((choice > TCAP_ABT_REASON_RES_UNAVAIL_CCITT) || 
            (choice < TCAP_ABT_REASON_UNREC_MSG_TYPE_CCITT))
        {
            printf(" ** Warning: Invalid Selection. P-Abort cause set to 0x01.\n");
            choice = 1;
        }
        data[index++] = (ITS_OCTET)choice;

        break;

    case 2:
        printf("\n ** Info: Setting P-Abort cause to 0x05.");
        data[index++] = 0x01;
        data[index++] = 0x05;
        break;

    case 3:
        printf("\n ** Info: Setting P-Abort cause over 2 octets.");
        data[index++] = 0x02;
        data[index++] = 0x34;
        data[index++] = 0x67;
        break;

    default:
        printf("\n ** Info: Invalid selection. Setting P-Abort cause to 0x01.");
        data[index++] = 0x01;
        data[index++] = TCAP_ABT_REASON_UNREC_TRANS_ID_CCITT;
        break;
    }
    
    *len = index;
}


/*************************************************************************
 *
 * Purpose: This method asks and sets the user if he wants to include an
 *           invalid IE tag.
 *
 * Return values: None.
 *
 *************************************************************************/
ITS_BOOLEAN
setUnknownElementTag(ITS_OCTET* data, int *len)
{
    int index = 0;
    ITS_BOOLEAN result = ITS_FALSE;

    printf("\n Do you want to include an invalid IE tag [y/n]? ");
    if (setOption())
    {
        printf("\n ** Info: Setting unknown IE Tag (0x%02x).", UNK_IE_TAG);
        data[index++] = UNK_IE_TAG;
        data[index++] = 0x03;
        data[index++] = 0x02;
        data[index++] = 0x01;
        data[index++] = 0x01;
        *len = 5;
        result = ITS_TRUE;
    }
    return result;
}


/*************************************************************************
 *
 * Purpose: will display a SCCP Address.
 *
 * Return values: None.
 *
 *************************************************************************/
void
displaySCCPAddress(SCCP_ADDR* address)
{
    int index = 0;
    ITS_OCTET addressIndicator;
    ITS_UINT pointCode;
    ITS_OCTET ssn;
    ITS_USHORT gttLen;
    ITS_OCTET gttInfo[SCCP_MAX_ADDR_LEN];

    SCCP_DecodeAddr(address, &addressIndicator, 
                    &pointCode, &ssn, gttInfo, &gttLen);
    printf("\n Address Indicator: 0x%02x.", addressIndicator);

    if (addressIndicator & SCCP_CPA_HAS_PC)
    {
        printf("\n Point code: 0x%04x, ", pointCode);
    }
    else
    {
        printf("\n Point code not present,");
    }

    if (addressIndicator & SCCP_CPA_HAS_SSN)
    {
        printf(" SSN: %d.", ssn);
    }
    else
    {
        printf(" SSN not present.");
    }
    if (gttLen > 0)
    {
        printf("\n Global Title Information: ");
        for (index = 0; index < gttLen; index ++)
        {
            printf("0x%02x ", gttInfo[index]);
        }
    }
    else
    {
        printf("\n Global Title Information: not present.");
    }
}


/*************************************************************************
 *
 * Purpose: Ask the user to know if we should set or include an option.
 *
 * Return values: ITS_TRUE if the option must be set or included, ITS_FALSE
 *                otherwise.
 *
 *************************************************************************/
ITS_BOOLEAN
setOption()
{
    char selection;

    fflush(stdin);
    selection = getchar();
    while(selection != 'y' && selection != 'n')
    {
        fflush(stdin);
        printf(" Incorrect Selection (either 'y' or 'n') -> ");
        selection = getchar();
    }

    if (selection == 'y')
    {
        return ITS_TRUE;
    }
    else
    {
        return ITS_FALSE;
    }
}


