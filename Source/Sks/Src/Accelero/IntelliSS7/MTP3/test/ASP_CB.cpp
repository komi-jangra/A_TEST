///////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: ASP_CB.cpp,v 1.1.1.1 2007-10-08 11:11:23 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

#include <its++.h>

#include <iostream>

#include <engine++.h>

#include <its_ual.h>
#include <m3ua.h>
#include <its_hash.h>

extern "C" ITS_Class itsINTELLISS7_Class;

#include <itu/tcap.h>
#include <itu/sccp.h>

#include "test_const.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_STD_NAMESPACE)

#define MAX_RK_NUM     5
#define BUILD_DATA     1
#define BUILD_ASPIA    2
#define BUILD_ASPDN    3
#define BUILD_ASPAC    4
#define REGISTER_RK    5
#define DEREG_RK       6 
#define DUMP_AS_TABLE  7
#define DUMP_ASP_TABLE 8
#define DUMP_RT_TABLE  9
#define LOAD_TEST      10
#define TEST_EXIT      99

#define VALID_CHOICE(x)     ( x >= 1 && x <= 9 || x == 99 )

// Need to create border Tansport only once

ITS_BOOLEAN borderInit = ITS_FALSE;
#define SIO 3


////////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//
extern "C"
{
    static int TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle);
    static int TEST_PrintCommand();
    static int TEST_Main(ITS_HANDLE handle);
}

extern ITS_BOOLEAN recv_mode;

////////////////////////////////////////////////////////////////////////////////
//
//  Simple break handler (specific for Unix).
//

static void exitHandler(int sig)
{
    exit(EXIT_SUCCESS);
}

////////////////////////////////////////////////////////////////////////////////
//
//  Synchronization object (semaphore) used to synchronize primary thread and
//  border transport thread.
//

static ITS_Semaphore borderTransportSemaphore(0);

#define RECV_BUFFER_FORMAT "Received: %d \n"
#define SENT_BUFFER_FORMAT "Sent    : %d \n"
char buffer[80];

extern "C"
{
void ASP_ReceiveFunc(ITS_HANDLE handle)
{
    ITS_INT    ret, i;
    char       sendBuff[80];
    static int recv_count = 0;
    ITS_EVENT  event;

    memset(sendBuff, 0, sizeof(char) * 80);

    ITS_EVENT_INIT(&event, 0, 0);

    if( (ret = ITS_GetNextEvent(handle, &event)) != ITS_SUCCESS)
    {
        ITS_Error itsError(ret, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;
    }
    else
    {
        for(i = 0; i < event.len; i++)
        {
            if(i != 0 && i% 16 == 0)
            {
                cout << endl;
            }
            printf("0x%02x ",  event.data[i]);
        }

        cout << endl;
    }

    if(recv_count % 2000 == 0)
    {
        ITS_INT wr = 0;

        wr = sprintf(sendBuff, SENT_BUFFER_FORMAT, recv_count);

        //STATS_WRITE(&record, WRITE_FILE, sendBuff, wr);
    }

    recv_count++;
    return;
}

void ASP_PostInitFunc(ThreadPoolThread* thr, ITS_HANDLE handle)
{
    ITS_UINT   pc;
    ITS_EVENT  event;
    int        ret = ITS_SUCCESS, i = 0; 
    ITS_OCTET  ni = 0x00;
    static int count = 0;
    Worker     *work = (Worker *) thr;

    ret = SCCP_SendUserInService(ISS7_Stack, ni, LOCAL_PC, LOCAL_SSN);

    if (ret != ITS_SUCCESS)
    {
        cout << "TEST --- > Failed to SEND UIS !!!! \n";
    }

    if(TRANSPORT_INSTANCE(handle) == 1)
    {
        TEST_AddLinkForLocalRoute(handle);
    }

    while (!work->GetExit())
    {
        if(TRANSPORT_INSTANCE(handle) == 1)
        {
            ASP_ReceiveFunc(handle);
        }
        else
        {
            TEST_Main(handle); /* To send traffic */
            count++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
//
//  Entry point.
//

int TEST_Main(ITS_HANDLE handle)
{
    int bt = 0;

    try
    {
        int cmdInput = 0;

        TEST_PrintCommand();

        scanf("%d", &cmdInput);
        printf("\nYou input %d.\n", cmdInput);
       
        if (VALID_CHOICE(cmdInput))
        {
            TEST_ExecuteCommand(cmdInput, handle); 
        }
        else
        {
            cout << "Wrong Choice, Try again" << endl;
        }
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////
//
// Display Menu for the ASP
//
//

static int 
TEST_PrintCommand()
{
    cout << "\n\n\t**** IntelliNet Technologies, Inc. ****\n";
    cout << "\t\tASP Simulator Program\n\n";

    cout << "Please choose one from the following list, \n";
    cout << "\ttype in the corresponding number:-\n\n";

    printf("    %d) Send DATA Message \n", BUILD_DATA);
    printf("    %d) Send ASPIA Message. \n", BUILD_ASPIA);
    printf("    %d) Send ASPDN Message. \n", BUILD_ASPDN);
    printf("    %d) Build ASPAC Message.\n", BUILD_ASPAC);
    printf("    %d) Register RK.\n", REGISTER_RK);
    printf("    %d) Deregister RK.\n", DEREG_RK);
    printf("    %d) Dump AS Table. \n", DUMP_AS_TABLE);
    printf("    %d) Dump ASP Table. \n", DUMP_ASP_TABLE);
    printf("    %d) Dump RT Table. \n", DUMP_RT_TABLE);
    printf("\n    %d) Quit program.\n", TEST_EXIT);

    printf("\n  -> ");

    return 1;
}

int
TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle)
{
    int ret = ITS_SUCCESS;
    ITS_UAL_IE m3uaIES[32];
    ITS_EVENT evt;
    char* dumpStr = NULL;

    ITS_EVENT_INIT(&evt, ITS_FIRST_USER_SRC, 256);

    evt.src = ITS_FIRST_USER_SRC;

    switch(cmdInput)
    {
    case DEREG_RK:
    {
        ITS_UINT rCtxt = 0;

        cout << "TEST ---> Enter RCtxt \n";
        cin  >> rCtxt;

        ret = UAL_DeregisterApplicationServer(&rCtxt, 1, 1);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ---> ERROR Degistering RK \n";
        }

        break;
    }
    case REGISTER_RK:
    {
        UAL_AS_DEF newAS;
        ITS_UINT localRkId = 0;
        ITS_UINT sio = 0x00;

        cout << "TEST ---> Enter DPC \n";
        //cin >> newAS.dpc;
 
        cout << "TEST ---> Enter SIO\n";
        cin >> sio; 

        if (sio != 0)
        {
            newAS.si.siList[0] = (ITS_OCTET)sio & 0xFF;

            newAS.numSI = 1;
        }

        cout << "TEST ---> Enter Traffic Mode\n";
        cout << "M3UA_OVERRIDE_MODE        0x01 \n";
        cout << "M3UA_LOADSHARE_MODE       0x02 \n";
        cin  >> newAS.tm;

        ret = UAL_RegisterApplicationServer(&newAS, 1, 1, &localRkId);        
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ---> ERROR Registering New RK \n";
        }

        cout << "\n *** Local RK Id Allocated ---> " << localRkId << endl;

        break;
    }
    case BUILD_DATA:
    {
        int iterration = 0;

        cout << endl << "Enter OPC: ";
        cin  >> LOCAL_PC;
        cout << endl << "Enter DPC:";
        cin  >> REMOTE_PC;
        cout << endl << "Number of Msg to Send: \n";
        cin  >> iterration;

        ret = TEST_BuildAndSendMsg(iterration, handle, NULL, NULL);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Occured Sending DATA.\n";
        }
        
        break;
    }
    case BUILD_ASPIA:
    {
        ITS_UINT ctx[MAX_RK_NUM], thm = 0;
        int numRCtx = 0;

        cout << "---- Enter Number of RCtx you want to deregister :\n";
        cin >> numRCtx;
       
        if (numRCtx <= MAX_RK_NUM)
        {
            for (int j=0; j<numRCtx; j++)
            {
                cout << "---- Enter RCtx :\n";
                cin >> ctx[j];
            }
        } 
        
        cout << "---- Enter THM:\n";
        cout << "M3UA_OVERRIDE_MODE        0x01 \n";
        cout << "M3UA_LOADSHARE_MODE       0x02 \n";

        cin >> thm;

        m3uaIES[0].param_id = UAL_PRM_MSG_HDR;
        m3uaIES[0].param_length =  sizeof(UAL_MSG_HDR);
        m3uaIES[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPTM;

        m3uaIES[0].param_data.msgHeader.msgType = UAL_MSG_ASPIA;
        m3uaIES[0].param_data.msgHeader.version = UAL_PROT_VER1;

        m3uaIES[1].param_id = UAL_PRM_TRAFFIC_MODE;
        m3uaIES[1].param_length = sizeof(UAL_TRAFFIC_MODE);
        m3uaIES[1].param_data.trafMode.tm = thm;

        m3uaIES[2].param_id = UAL_PRM_ROUT_CTX;

        ret = UAL_EncodeRoutingContext(m3uaIES[2].param_data.rCtxt.rCtxt, 
                                       (&m3uaIES[2].param_length),
                                       ctx, numRCtx);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ---- > Error Encoding Routing Ctx.\n";
        }

        ret = UAL_EncodeMsg(m3uaIES, 3, &evt, &UAL_ASPIA_Desc);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ERROR: Could not encode ASPIA message.\n";
        }

        for (int j=0; j<evt.len; j++)
        {
            printf("%02x ", evt.data[j]);
        }
        printf("\n");

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ERROR: PutEvent Failed. Could not send ASPIA.\n";
        }
 
        break;
    }
    case BUILD_ASPDN:
    {
        m3uaIES[0].param_id = UAL_PRM_MSG_HDR;
        m3uaIES[0].param_length =  sizeof(UAL_MSG_HDR);
        m3uaIES[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPSM;
        m3uaIES[0].param_data.msgHeader.msgType = UAL_MSG_ASPDN;
        m3uaIES[0].param_data.msgHeader.version = M3UA_PROT_VER1;

        ret = UAL_EncodeMsg(m3uaIES, 1, &evt, &UAL_ASPDN_Desc);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Could not encode ASPDN message.\n";
        }

        PRINT_EVENT(&evt);

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST ERROR: PutEvent Failed. Could not send ASPDN.\n";
        }

        break;
    }
    case BUILD_ASPAC:
    {
        ITS_UINT ctx = 0, thm = 0;

        cout << "---- Enter RCtx you want to Register:\n";
        cin >> ctx;

        cout << "---- Enter THM:\n";
        cin >> thm;

        m3uaIES[0].param_id = UAL_PRM_MSG_HDR;
        m3uaIES[0].param_length =  sizeof(UAL_MSG_HDR);
        m3uaIES[0].param_data.msgHeader.msgClass = UAL_CLASS_ASPTM;
        m3uaIES[0].param_data.msgHeader.msgType = UAL_MSG_ASPAC;
        m3uaIES[0].param_data.msgHeader.version = UAL_PROT_VER1;

        m3uaIES[1].param_id = UAL_PRM_TRAFFIC_MODE;
        m3uaIES[1].param_length = sizeof(UAL_TRAFFIC_MODE);
        m3uaIES[1].param_data.trafMode.tm = thm;

        m3uaIES[2].param_id = UAL_PRM_ROUT_CTX;

        ret = UAL_EncodeRoutingContext(m3uaIES[2].param_data.rCtxt.rCtxt,
                                        &m3uaIES[2].param_length,
                                        &ctx, 1);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Encoding Routing Ctx.\n";
        }

        ret = UAL_EncodeMsg(m3uaIES, 3, &evt, &UAL_ASPAC_Desc);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Could not encode ASPAC message.\n";
        }

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error PutEvent Failed. Could not send ASPAC.\n";
        }

        break;
    }
    case DUMP_RT_TABLE:
    {
        char* routeString = NULL;

        /* ROUTE_DumpIdToSS7Hashtable(&routeString); */

        if(routeString)
        {
            free(routeString);
        }

        printf("%s", routeString);

        break;
    }
    case DUMP_AS_TABLE:

         UAL_DumpASTable(&dumpStr);
         if(dumpStr != NULL)
         {
             printf("%s", dumpStr);
             free(dumpStr);
         }

       break;

    case DUMP_ASP_TABLE:

         UAL_DumpASPTable(&dumpStr);
         if(dumpStr != NULL)
         {
             printf("%s", dumpStr);
             free(dumpStr);
         }

       break;

    case TEST_EXIT:

       cout << "Exiting the program:" << endl;

       APP_SetStopper();
       break;

    default:

        break;
    }

    return ret;
}
}
