#include <stdio.h>

#include <its.h>
#include <its_app.h>
#include <its_thread.h>
#include <its_transports.h>
#include <its_imal_trans.h>
#include <tcap_test.h>


ITS_OCTET   mtp3_msg_type;
MTP3_HEADER mtp3_header; 

ITS_EVENT mtp3_msg;

ITS_OCTET sccp_msg_type;
ITS_OCTET sccp_protocol_class;
ITS_OCTET sccp_pointer_to_CgPA;
ITS_OCTET sccp_pointer_to_CdPA;
ITS_OCTET sccp_pointer_to_UserData;

SCCP_DATA userData;
int userDataLen;

ITS_HANDLE mtp3_handle;

ITS_THREAD receiveThread;
THREAD_RET_TYPE thread_ReceiveMsgs(void* Userdata);

SCCP_ADDR cdpa;
SCCP_ADDR cgpa;
SCCP_ADDR cgpa_continue;

/* True until the user wants to quit */
ITS_BOOLEAN keepGoing;

int initTCAPMTP3(int instance_nb, ITS_BOOLEAN useSS7);
void send_MTP3message();
void setTCAPTransaction();

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
    ITS_Terminate(mtp3_handle);    
    exit(0);
#if defined (WIN32)
    return (1);
#endif
}

int
main(int argc, char** argv)
{
   
    /* choice selection from user */
    int choiceMenu = 0;
    int result = 0;
    int instance_nb = 0;
    ITS_BOOLEAN useSS7 = ITS_TRUE;

    keepGoing = ITS_TRUE;

    printf("\n");
    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****     IntelliSS7 TCAP (MTP3)      *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n");

    if (argc == 2)
    {
        useSS7 = ITS_FALSE;
        printf("\n ** Info: Using IMAL Transport (Server).");        
    }
    else
    {
        printf("\n ** Info: Using SS7 Transport (Server).");
    }
    
    /* Initialize IntelliSS7 and tcap test */

    printf("\n Enter instance number to use -> ");
    scanf("%d", &instance_nb);

    result = initTCAPMTP3(instance_nb, useSS7);

    if (result != ITS_SUCCESS)
    {
        exit(-1);
    }

    /* Display Menu until user Exits*/
    do
    {
        printf("\n\n");
        printf("------------------------------------------------ \n");
        printf("         TCAP (MTP3) Demo Main Menu              \n");
        printf("------------------------------------------------ \n");          
        printf(" (1)  Send User In Service                       \n");
        printf(" (2)  Send User Out Of Service                   \n");
        printf(" (3)  Modify Called Party Address                \n");
        printf(" (4)  Modify Calling Party Address               \n");
        printf(" (5)  Set TCAP Transaction                       \n");
        printf(" (6)  Send TCAP Transaction (MTP3 msg)           \n");
        printf(" - - - - - - - - - - - - - - - - - - - - - - - - \n");
        printf(" (99) EXIT TCAP Demo\n");
        printf("------------------------------------------------ \n");
        printf("Enter choice: ");
        if (scanf("%d", &choiceMenu) != 1)
        {
            /* User did not enter an int */
            fflush(stdin);
            choiceMenu = -1;
        }

        switch (choiceMenu)
        {
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

        /* Send TCAP Transaction */
        case 6:
            printf("\n ** Info: Going to send TCAP transaction.\n");
            send_MTP3message();
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


int
initTCAPMTP3(int instance_nb, ITS_BOOLEAN useSS7)
{
    int result = ITS_SUCCESS;
    ITS_UINT initMask = 0;

    APPL_SetName("mtp3TestTCAP");

    if (useSS7)
    {
        initMask = (ITS_MTP3 | ITS_TRANSPORT_SS7 | ITS_TRANSPORT_SINGLE_USER);
    }
    else
    {

        result = ITS_AddFeature(itsKEEPALIVE_Class);

        result = ITS_AddFeature(itsIMAL_Class);

        result = ITS_GlobalStart(ITS_MTP3);

        initMask = (ITS_MTP3 | ITS_TRANSPORT_SSOCKET |
                    ITS_TRANSPORT_IMAL_SOCKET | ITS_TRANSPORT_SINGLE_USER);
    }

    mtp3_handle = (ITS_HANDLE)ITS_Initialize(initMask, (ITS_USHORT)instance_nb);

    if (mtp3_handle == NULL)
    {
        printf("\n ** Error: ITS_Initialize failed, quiting.");
        /* setting result to bad transport */
        result = ITS_EBADTRANSPORT;
        return result;
    }
 
    result = THREAD_CreateThread(&receiveThread, 0, thread_ReceiveMsgs, 
                                 NULL, ITS_TRUE); 
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to create receive Thread (%d), quiting.",
               result);
        ITS_Terminate(mtp3_handle);
        return (result);
    }
    else
    {
        printf("\n ** Info: Receive thread created.");
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
        ITS_Terminate(mtp3_handle);
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
        ITS_Terminate(mtp3_handle);
        return (result);
    }

    /* Set MTP3 Header */
    memset((char *)&mtp3_header, 0, sizeof(MTP3_HEADER));
    result = setMTP3Header(&mtp3_header, cgpa, cdpa);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to set MTP3 Header (%d), quiting.",
               result);
        THREAD_DeleteThread(&receiveThread);
        ITS_Terminate(mtp3_handle);
        return (result);
    }

    /* set Protocol Class */
    printf("\n Enter Protocol Class: ");
    setProtocolClass(&sccp_protocol_class);

    /* set pointer to parameters */
    sccp_pointer_to_CdPA = 0x03;
    sccp_pointer_to_CgPA = sccp_pointer_to_CdPA + cdpa.len;
    sccp_pointer_to_UserData = sccp_pointer_to_CgPA + cgpa.len;    

    /* set MTP3 and SCCP message type */
    mtp3_msg_type = MTP3_MSG_USER_DATA;
    sccp_msg_type = SCCP_MSG_UDT;

    memset((char *)&mtp3_msg, 0, sizeof(ITS_EVENT));
    memset((char *)&userData, 0, sizeof(SCCP_DATA));
    userDataLen = 0;

    keepGoing = ITS_TRUE;
    
    return result;
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
    int msgTag = 0;
    int index = 0;
    int IE_Length = 0;
    int trans_id_index = 0;
    int msg_type_len_index = 0;
    int choice = 0;
    ITS_BOOLEAN use_indefinite_form_len = ITS_FALSE;
    ITS_BOOLEAN use_definite_long_form_len = ITS_FALSE;
    
    memset((char *)&userData, 0, sizeof(SCCP_DATA));

    printf("\n Select TCAP message Tag:\n");
    printf(" (%d) Uni Tag \n", UNI_TAG);
    printf(" (%d) Begin Tag \n", BEGIN_TAG);
    printf(" (%d) End Tag \n", END_TAG);
    printf(" (%d) Continue Tag \n", CONTINUE_TAG);
    printf(" (%d) Abort Tag\n", ABORT_TAG);
    printf(" (%d) Unknown Tag ", UNK_TAG);
    printf("\n Enter Transaction Type: ");
    scanf("%d", &msgTag);

    /* setting TCAP msg TAG */
    if (msgTag != UNK_TAG)
    {
        userData.data[index++] = (ITS_OCTET)(msgTag | 0x60);
    }
    else
    {
        userData.data[index++] = TCAP_MSG_UNK_TAG;
    }

    
    printf("\n Select encoding of length of msg type tag ");
    printf("\n (1) Definite short form.");
    printf("\n (2) Definite long form.");
    printf("\n (3) Indefinite form.");    
    printf("\n Enter type of encoding -> ");
    scanf("%d", &choice);
    
    /* setting len of tcap msg */

    switch (choice)
    {
    /* definite short form */
    case 1:
        /* does nothing default */
        msg_type_len_index = index;
        break;

        /* definite long form */
    case 2:
        /*
         * bit 8 must be set for definite long form
         * bit 7 -> 1 number of octets for length (less than 256 for sure) 
         */
        userData.data[index++] = 0x81;
        msg_type_len_index = index;
        use_definite_long_form_len = ITS_TRUE;
        break;

    /* indefinite form */
    case 3:
        use_indefinite_form_len = ITS_TRUE;
        /* bit 8 must be set for indefinite form */
        userData.data[index] = 0x80;
        break;

    default:
        /* does nothing default */
        printf("\n ** Warning: Invalid selection, using definite short form.");
        break;
    }

    switch (msgTag)
    {
    case BEGIN_TAG:
        printf("\n Do you want to include an invalid tag [y/n]? ");
        if (setOption())
        {
            userData.data[++index] = (ITS_OCTET)0x22;
        }

        printf("\n ** Info: Setting transaction portion.");
        setTransactionID(ITS_TRUE, &userData.data[++index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }

        /* Originating TID */
        printf("\n ** Info: Setting dialogue portion.");
        setDialoguePortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        
        if (setUnknownElementTag(&userData.data[index], &IE_Length))
        {
            index += IE_Length;
        }

        printf("\n ** Info: Setting component portion.");
        setComponentPortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    case CONTINUE_TAG:
        printf("\n Do you want to include an invalid tag [y/n]? ");
        if (setOption())
        {
            userData.data[++index] = (ITS_OCTET)0x1F;
        }

        /* Originating TID (duplicated), Destination TID (duplicated) */
        printf("\n ** Info: Setting transaction portion.");
        setTransactionID(ITS_TRUE, &userData.data[++index], &IE_Length);
        trans_id_index = index;
        if (IE_Length > 0)
        {
            index += IE_Length;
            printf("\n Do you want to include a duplicated OTID [y/n]? ");
            if (setOption())
            {
                memcpy(&userData.data[index], &userData.data[trans_id_index],
                       IE_Length);
                index += IE_Length;
            }
        }
        
        setTransactionID(ITS_FALSE, &userData.data[index], &IE_Length);
        trans_id_index = index;
        if (IE_Length > 0)
        {
            index += IE_Length;
            printf("\n Do you want to include a duplicated TID [y/n]? ");
            if (setOption())
            {
                memcpy(&userData.data[index], &userData.data[trans_id_index],
                       IE_Length);
                index += IE_Length;
            }
        }

        if (setUnknownElementTag(&userData.data[index], &IE_Length))
        {
            index += IE_Length;
        }

        printf("\n ** Info: Setting dialogue portion.");
        setDialoguePortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        
        printf("\n ** Info: Setting component portion.");
        setComponentPortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    case END_TAG:
        /* Destination TID */
        printf("\n ** Info: Setting transaction portion.");
        setTransactionID(ITS_FALSE, &userData.data[++index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }

        printf("\n ** Info: Setting dialogue portion.");
        setDialoguePortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        
        printf("\n ** Info: Setting component portion.");
        setComponentPortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    case ABORT_TAG:
        /* Destination TID. Abort Cause */
        printf("\n ** Info: Setting transaction portion.");
        setTransactionID(ITS_FALSE, &userData.data[++index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }

        printf("\n ** Info: Setting P-Abort cause.");
        setP_Abort(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    case UNI_TAG:
        printf("\n ** Info: Setting transaction portion.");
        
        if (setUnknownElementTag(&userData.data[index], &IE_Length))
        {
            index += IE_Length;
        }

        printf("\n ** Info: Setting dialogue portion.");
        setDialoguePortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        
        printf("\n ** Info: Setting component portion.");
        setComponentPortion(&userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    case UNK_TAG:
        /* Originating TID , Destination TID  */
        printf("\n ** Info: Setting transaction portion.");
        setTransactionID(ITS_TRUE, &userData.data[++index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        
        setTransactionID(ITS_FALSE, &userData.data[index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }

        setComponentPortion(&userData.data[++index], &IE_Length);
        if (IE_Length > 0)
        {
            index += IE_Length;
        }
        break;

    default:
        printf("\n ** Warning: Invalid selection.\n");
        break;
    }

    /* setting msg type len */
    if (use_indefinite_form_len)
    {
        /* End-of-Octets (tag = 0x00, len = 0x00) */
        userData.data[index++] = 0x00;
        userData.data[index++] = 0x00;
    }
    else if (use_definite_long_form_len)
    {
        /* (no including msg TCAP and msg Len  (that includes "tag definite form") */
        userData.data[msg_type_len_index] = index - 3;
    }
    else
    {
        /* (no including msg TCAP and msg Len */
        userData.data[msg_type_len_index] = index - 2;
    }

    /* setting userDataLen  */
    userDataLen = index;
}


void
setMTP3Message()
{
    int index = 0;
    memset((char *)&mtp3_msg, 0, sizeof(ITS_EVENT));

    /* MTP3 msg type + SIO + Routing label */
    mtp3_msg.data[index++] = mtp3_msg_type;
    mtp3_msg.data[index++] = mtp3_header.sio;

#ifdef USE_ANSI_MTP3
    memcpy(&mtp3_msg.data[index], mtp3_header.label.dpc.data, 3);
    memcpy(&mtp3_msg.data[index], mtp3_header.label.opc.data, 3);
#else /* ITU */
    memcpy(&mtp3_msg.data[index], mtp3_header.label.data, 4);
#endif
    
    index += 4;

    /* SCCP msg type + protocol class */
    mtp3_msg.data[index++] = sccp_msg_type;
    mtp3_msg.data[index++] = sccp_protocol_class;

    /* pointer to SCCP parameters*/
    mtp3_msg.data[index++] = sccp_pointer_to_CdPA;
    mtp3_msg.data[index++] = sccp_pointer_to_CgPA;
    mtp3_msg.data[index++] = sccp_pointer_to_UserData;

    /* Called Party Address */
    mtp3_msg.data[index++] = (ITS_OCTET)cdpa.len;
    memcpy(&mtp3_msg.data[index], cdpa.data, cdpa.len);
    index += cdpa.len;

    /* Calling Party Address */
    mtp3_msg.data[index++] = (ITS_OCTET)cgpa.len;
    memcpy(&mtp3_msg.data[index], cgpa.data, cgpa.len);
    index += cgpa.len;

    /* User Data holding TCAP trans. */
    mtp3_msg.data[index++] = userDataLen;
    memcpy(&mtp3_msg.data[index], userData.data, userDataLen);
    index += userDataLen;

    /* event src and Length */
    mtp3_msg.src = ITS_SCCP_SRC;
    mtp3_msg.len = index;
}


void
send_MTP3message()
{
    int result = 0;
    int index = 0;

    setMTP3Message();

    result = ITS_PutEvent(mtp3_handle, &mtp3_msg);
    if (result != ITS_SUCCESS)
    {
        printf("\n ** Error: Failed to send MTP3 message (%d).",
               result);
    }
    else
    {
        printf("\n ** Info: MTP3 message sent.");
    }

    printf("\n ** Info: MTP3 MSU Hex Dump\n");
    for (index = 0; index < mtp3_msg.len; index++)
    {
        printf (" 0x%02x", mtp3_msg.data[index]);
    }
    printf("\n\n");
}


THREAD_RET_TYPE
thread_ReceiveMsgs(void* Userdata)
{
    ITS_EVENT event;
    int result = 0;
    int index = 0;

    do 
    {
        memset((char *)&event, 0, sizeof(ITS_EVENT));
        result = ITS_GetNextEvent(mtp3_handle, &event);
        if (result != ITS_SUCCESS)
        {
            printf("\n ** Error: ITS_GetNextEvent (dispatch) failed (%d).",
                   result);
        }
        else
        {
            printf("\n ** Info: MTP3 MSU Hex Dump\n");
            for (index = 0; index < event.len; index++)
            {
                printf (" 0x%02x", event.data[index]);
            }
            printf("\n\n");
        }
    }
    while (keepGoing);

    THREAD_NORMAL_EXIT;
}
