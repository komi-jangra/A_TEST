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
 *  ID: $Id: testMain.c,v 1.1.1.1 2007-10-08 11:11:22 bsccs2 Exp $
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
 * LOG: Revision 8.2  2005/03/21 13:50:02  cvsadmin
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
 * LOG: Revision 1.1  2000/09/08 14:34:19  labuser
 * LOG: cbascon: now have correct directory structure
 * LOG:
 * LOG: Revision 3.1  2000/08/15 23:59:36  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.8  2000/05/16 15:11:35  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.7  2000/02/08 14:16:55  labuser
 * LOG: OGC Selected is now sent automatically in ANSI.
 * LOG:
 * LOG: Revision 2.6  2000/01/27 14:56:47  labuser
 * LOG: cbascon: Clean up code.
 * LOG:
 * LOG: Revision 2.5  2000/01/16 15:58:52  labuser
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 2.4  2000/01/11 18:11:22  labuser
 * LOG: Almost done with pass thru messages.
 * LOG:
 * LOG: Revision 2.3  1999/12/30 15:54:13  labuser
 * LOG: Clean up...
 * LOG:
 * LOG: Revision 2.2  1999/12/10 22:50:07  cbascon
 * LOG: Tested ANSI ISUP messages ACM, ANM, CPG, IAM, BLO, UBL, UCIC, REL, RLC,
 * LOG: RSC
 * LOG:
 * LOG: Revision 2.1  1999/12/07 00:40:05  cbascon
 * LOG: Encoded and sent the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO
 * LOG:
 * LOG: Received and decoded the messages below successfully:
 * LOG: IAM, ACM, ANM, CPG, REL, RLC, RSC, UBL, BLO, UCIC
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:21:39  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.8  1999/11/24 19:34:28  cbascon
 * LOG: Will now just wait for one ITS_EVENT to be received then user is
 * LOG: prompted to main menu.
 * LOG:
 * LOG: Revision 1.7  1999/11/15 23:22:02  cbascon
 * LOG: Check return value of TestSend*** functions.
 * LOG: Print error text if failed.
 * LOG:
 * LOG: Revision 1.6  1999/11/14 23:18:31  cbascon
 * LOG: *** empty log message ***
 * LOG:
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_app.h>
#include <its_stubs.h>
#include <its_thread.h>
#include <its_semaphore.h>
#include <its_gdi_stubs.h>

#ifdef ANSI
#include <ansi/mtp3.h>
#include <ansi/isup.h>
#endif
#ifdef CCITT
#include <itu/mtp3.h>
#include <itu/isup.h>
#endif

/* EBS headers */
#include <types.h>
#include <isupparams.h>
#include <isupcall.h>
#include <isupcircuit.h>
#include <isupcause.h>
#include <isupuser.h>
#include <isupCallCont.h>

#include "test.h"
#include "sendISUPMsg.h"

int max_no_event_failures = 3;

/* ITS_HANDLE used to send and receive messages */
ITS_HANDLE isup_handle = NULL;


/* ITS_THREAD to receive TCAP transactions and dispatch MTP3 messages */
ITS_THREAD receiveThread;
THREAD_RET_TYPE thread_ReceiveISUPMsgs(void* Userdata);

/* semaphore used to wait for Dispatch thread to complete init process */
ITS_SEMAPHORE semaWaitForReceiveThread;

/* To know if init of dispatch Thread was success or not */
ITS_BOOLEAN dispatch_init_failed;

ITS_BOOLEAN keepGoing; 
ITS_BOOLEAN print_MTP3_MSU;


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

    if (isup_handle)
    {
        ITS_Terminate(isup_handle);
        isup_handle = NULL;
    }
    
    exit(0);
#if defined (WIN32)
    return (1);
#endif
}

/*************************************************************************
 *
 * Purpose: Thread function that will wait for Event from IntelliSS7.
 *
 * Return values: None.
 *
 *************************************************************************/
THREAD_RET_TYPE
thread_ReceiveISUPMsgs(void* Userdata)
{
    int        result = 0;
    int        i = 0;
    int        consecutive_fail_count = 0;
    ITS_HDR    incoming_header;
    ITS_EVENT  event;

    memset((char *)&incoming_header, 0, sizeof(ITS_HDR));
    memset((char *)&event, 0, sizeof(ITS_EVENT));

    /* setting CTRL C Handler functions */
#if defined(WIN32)
    SetConsoleCtrlHandler(exitHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    while (consecutive_fail_count < max_no_event_failures) 
    {
        if (isup_handle == NULL)
        {
            printf("ISUPTEST: isup_handle = NULL, quiting.");
            break;
        }

        result = ITS_GetNextEvent(isup_handle, &event);

        printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__, __TIME__,
               __FILE__, __LINE__); 
        printf("Called GetNextEvent(), result %d\n", result);
#if 0
        printf( "\nevent.src: 0x%02x\n", event.src );
        printf( "event.len: 0x%02x\n", event.len );
        printf( "event.data: " );

        for (i = 0; i < event.len; ++i)
        {
            printf("0x%02x ", event.data[i]);

            if (i % 10 == 0)
            {
                printf("\n");
            }
        }
        printf("\n\n");
#endif

        if (result == ITS_SUCCESS)
        {
            consecutive_fail_count = 0;
            if ( event.src == ITS_ISUP_SRC )
            {
                result = ReceiveISUPMsg(isup_handle, &event, &incoming_header); 
                if (result == ITS_SUCCESS)
                {
                    printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__,
                           __TIME__, __FILE__, __LINE__); 
                    printf("ISUP msg receive success\n");
                }

                DisplayMainMenu();
            }    
        }
        else
        {
            ++consecutive_fail_count;
        }
    }

    SEMA_PostSemaphore(&semaWaitForReceiveThread);
    THREAD_NORMAL_EXIT;
}

/*************************************************************************
 *
 * Purpose: initISUPTest will initialize IntelliSS7 and Newnet stack.
 *
 * Return values: If init is success, it will return ITS_SUCCESS,
 *                else will return en error (check its.h for values).
 *
 *************************************************************************/
int
initISUPTest(int instance_nb)
{
    int        result = ITS_SUCCESS;
    ITS_UINT   initMask;
    ITS_USHORT instanceNumber = 0;

    /* setting CTRL C Handler functions */
#if defined(WIN32)
    SetConsoleCtrlHandler(exitHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    /* setting the name of the application */
    initMask = (ITS_MTP3 | ITS_ISUP | ITS_TRANSPORT_SS7 | 
                ITS_TRANSPORT_SINGLE_USER);

    instanceNumber = (ITS_USHORT)instance_nb;

#if 0
    /* Initialize MTP3 & ISUP */
    result = ITS_GlobalStart(ITS_MTP3 | ITS_ISUP);
    if (result != ITS_SUCCESS)
    {
        printf("ISUPTEST: ITS_GlobalStart failed (%d), quiting. \n", result);
        return (result);
    }
#endif

    /* setting Mask used by IntelliSS7 */
    
    isup_handle = (ITS_HANDLE)ITS_Initialize(initMask, instanceNumber);
    if (isup_handle == NULL)
    {
        printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__, __TIME__,
               __FILE__, __LINE__); 
        printf("ITS_Initialize failed, quiting.\n");
        
        ITS_GlobalStop();

        /* setting result to bad transport */
        result = ITS_EBADTRANSPORT;
        return result;
    }
    
    /* starting the Receiving Thread firs */
    result = THREAD_CreateThread(&receiveThread, 0, thread_ReceiveISUPMsgs,
                                 NULL, ITS_TRUE);
    if (result != ITS_SUCCESS)
    {
        printf("ISUPTEST: Failed to create receive thread (%d), quiting. \n",
               result);

#if 0
        ITS_GlobalStop();
#endif

        if (isup_handle)
        {
            ITS_Terminate(isup_handle);
        }
        return (result);
    }
    else
    {
        printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__, __TIME__,
               __FILE__, __LINE__); 
        printf("Receive thread created. \n");
    }

    return (result);
}

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
    int instance_nb = 0;
    char fname[50] = "";
    ITS_USHORT instance = 0;
    ITS_HDR hdr;

    /* setting CTRL C Handler functions */
#if defined(WIN32)
    SetConsoleCtrlHandler(exitHandler, TRUE);
#else
    signal(SIGINT, exitHandler);
#endif

    /* Initialize header */
    memset((char *)&hdr, 0, sizeof(ITS_HDR));

    SEMA_CreateSemaphore(&semaWaitForReceiveThread, 1);

    printf("\t *******************************************\n");
    printf("\t *****                                 *****\n");
    printf("\t *****  IntelliNet Technologies, Inc.  *****\n");
    printf("\t *****    IntelliSS7 ISUP API Test     *****\n");
    printf("\t *****                                 *****\n");
    printf("\t *******************************************\n");

    if (argc == 2)
    {
        instance_nb = atoi(argv[1]);
    }
    else
    {
        printf("\n");
        printf("Enter instance number: ");
        scanf("%d", &instance_nb);
    }
    
    printf("\n\n");
    printf("ISUPTEST: Setting application name: ");
    if (instance_nb == 1)
    {
        /*
         * Setting the name of the application. The application name is the
         * name of the ini file read by IntelliSS7.
         */
        printf("SEND");
        APPL_SetName("SEND");

        strcpy( fname, FILENAME );
        strcat( fname, ".0" ); 
        SetFilename( fname );
    }
    else
    {
        printf("RECV");
        APPL_SetName("RECV");

        strcpy( fname, FILENAME );
        strcat( fname, ".1" ); 
        SetFilename( fname );
    }
    printf("\n");

    /* Initialize IntelliSS7 and ISUP test */
    result = initISUPTest( instance_nb );
    if (result != ITS_SUCCESS)
    {
        exit(0);
    }


    /* Main menu loop */
    while (keepGoing)
    {
        DisplayMainMenu();

        /* ISUP_MSG_CFN has highest tag value of ISUP messages in this test */
        choice = GetSelection(TEST_QUIT, 255);

        if ((choice > 0 && choice <= 0xff) ||
            (choice == TEST_UNKNOWN_MSG))
        {
            hdr.context.CIC = GetCIC();
        }

        switch ( choice )
        {
        case ISUP_MSG_ACM:
            result = TestSendACMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_ANM:
            result = TestSendANMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_BLO:
            result = TestSendBLORequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CCR:
            result = TestSendCCRRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CFN:
            result = TestSendCFNRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CGB:
            result = TestSendCGBRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CGU:
            result = TestSendCGURequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CGUA:
            result = TestSendCGUARequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_COT:
            result = TestSendCOTRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CPG:
            result = TestSendCPGRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CQM:
            result = TestSendCQMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_FOT:
            result = TestSendFOTRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_GRS:
            result = TestSendGRSRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_IAM:
            result = TestSendIAMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_INF:
            result = TestSendINFRequest( isup_handle, &hdr);
            break;
        case ISUP_MSG_INR:
            result = TestSendINRRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_PAM:
            result = TestSendPAMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_REL:
            result = TestSendRELRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_RES:
            result = TestSendRESRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_RLC:
            result = TestSendRLCRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_RSC:
            result = TestSendRSCRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_SUS:
            result = TestSendSUSRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_UBL:
            result = TestSendUBLRequest( isup_handle, &hdr );
            break;

#ifdef ANSI
        case ISUP_MSG_CRM:
            result = TestSendCRMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CVR:
            result = TestSendCVRRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_CVT:
            result = TestSendCVTRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_EXM:
            result = TestSendEXMRequest( isup_handle, &hdr );
            break;
#endif

#ifdef CCITT
        case ISUP_MSG_CON:
            result = TestSendCONRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_FAA:
            result = TestSendFAARequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_FAR:
            result = TestSendFARRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_FRJ:
            result = TestSendFRJRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_IDR:
            result = TestSendIDRRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_IRS:
            result = TestSendIRSRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_NRM:
            result = TestSendNRMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_OLM:
            result = TestSendOLMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_SAM:
            result = TestSendSAMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_SGM:
            result = TestSendSGMRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_UPA:
            result = TestSendUPARequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_UPT:
            result = TestSendUPTRequest( isup_handle, &hdr );
            break;
        case ISUP_MSG_USR:
            result = TestSendUSRRequest( isup_handle, &hdr );
            break;
#endif 

        case TEST_QUIT:
            keepGoing = 0;
            continue;
            break;
        default:
            printf("ISUPTEST: Invalid selection. \n");
            continue;
        }

        if ( result == ITS_SUCCESS )
        {
            printf("\n");
            printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__, __TIME__,
                   __FILE__, __LINE__); 
            printf("Msg send success.\n");
        }
        else
        {   
            printf("[ISUPTEST]: %s %s: %s: line %d]\n", __DATE__, __TIME__,
                   __FILE__, __LINE__); 
            printf("Fail to send msg. result %d \n", result);
            printf("Error: %s \n", ITS_GetErrorText( result ) );
        }
    }

    if (isup_handle)
    {
#if 0
        ITS_GlobalStop();
#endif
        ITS_Terminate(isup_handle);
        isup_handle = NULL;
    }

    SEMA_WaitSemaphore(&semaWaitForReceiveThread);
    THREAD_DeleteThread(&receiveThread);
    
    exit(0);
}
