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
//  ID: $Id: SGP_CB.cpp,v 1.1.1.1 2007-10-08 11:11:24 bsccs2 Exp $ 
//
////////////////////////////////////////////////////////////////////////////////

 
////////////////////////////////////////////////////////////////////////////////
//
//  This is a test program used to simulate a SGP, this is to be used in the 
//  test scenarios written for the M3UA Bakeoff.
//
///////////////////////////////////////////////////////////////////////////////


#include <its++.h>

#if !defined(WIN32)
#include <signal.h>
#endif // defined(WIN32)

#include <iostream>

#include <engine++.h>

#include <its_ual.h>
#include <m3ua.h>
#include <sccp++.h>

#include "test_const.h"

#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
#endif // defined(ITS_STD_NAMESPACE)


#define BUILD_DATA     1
#define BUILD_PAUSE    2
#define BUILD_RESUME   3
#define BUILD_STATUS   4
#define DUMP_RT        5
#define DUMP_AS_TABLE  6
#define DUMP_ASP_TABLE 7
#define LOAD_TEST      8

#define TEST_EXIT    99

#define VALID_CHOICE(x)     ( x >= 1 && x <= 7 || x == 99 )

#define SIO 3

////////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//
extern "C"
{
    /* Prototype declaration */
    static int TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle);
    //static int TEST_WaitForEvent(ITS_HANDLE handle);
    static int TEST_PrintCommand();
    int  TEST_Main(ITS_HANDLE handle);
    void SGP_ReceiveFunction(ITS_HANDLE handle);
}

extern "C"
{
ITS_INT
SGP_PostInitFunc(ThreadPoolThread* thr, ITS_HANDLE handle)
{
    Worker* work = (Worker *) thr;
    ITS_OCTET ni = 0x00;

    if (handle == NULL)
    {
        ITS_Error itsError(ITS_ENOTRANSPORT, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;
    }

    if(TRANSPORT_INSTANCE(handle) == 1)
    {
    }

    if(SCCP_SendUserInService(ISS7_Stack, ni, LOCAL_PC, LOCAL_SSN) !=
                              ITS_SUCCESS)
    {
        cout << "ERROR: Failed to send UserInService:" << endl; 
        /*
         * Should I terminate the application ????????? 
         */
    }

    while (!work->GetExit())
    {
        if(TRANSPORT_INSTANCE(handle) != 1)
        {
            TEST_Main(handle);  /* We leave instance 1 for default 
                                 * app routing.
                                 */
        }
        else
        {
            SGP_ReceiveFunction(handle);
        }
    }
}

void SGP_ReceiveFunction(ITS_HANDLE handle)
{
    ITS_INT     ret = ITS_SUCCESS;
    ITS_INT     ieCount = 0;
    ITS_HDR     hdr;
    ITS_EVENT   event;
    ITS_SCCP_IE ies[8];

    memset(ies, 0, sizeof(ITS_SCCP_IE) * 8);

    if (handle == NULL)
    {
        // Fatal error.
        throw ITS_Error(ITS_ENOTRANSPORT, __FILE__, __LINE__);
    }

    if (ret != ITS_SUCCESS)
    {
        cout << "TEST --- > Failed to SEND UIS !!!! \n";
    }

    ITS_EVENT_INIT(&event, 0, 0);

    ret = ITS_GetNextEvent(handle, &event);

    if (ret != ITS_SUCCESS)
    {
        ITS_Error itsError(ret, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;
    }

    cout << endl << "Received Event..." << endl;

    cout << "Source: <" << event.src << ">." << endl;

    for (int i = 0; i < event.len; i++)
    {
        if(i != 0 && i % 16 == 0) 
        {
           cout << endl;
        }
        printf("0x%02x ", event.data[i]);
    }
    cout << endl;

    if(SCCP_ReceiveUnitData(handle, &event, &hdr, ies, &ieCount) ==
                            ITS_SUCCESS)
    {
        ITS_INT    i, cdp_id, cgp_id;
        ITS_USHORT gttLen = 0; 
        ITS_OCTET  gttInfo[15];

        cdp_id = cgp_id = -1;

        for(i = 0; i < ieCount; i++)
        {
            if(ies[i].param_id == SCCP_PRM_CALLING_PARTY_ADDR)
            {
                cgp_id = i;
            }
            else if(ies[i].param_id == SCCP_PRM_CALLED_PARTY_ADDR)
            {
               cdp_id = i;
            }
            else
            {
                printf("Param ID = %0x \n", ies[i].param_id);
                printf("param length = %d:\n", ies[i].param_length);
            }

            if(cgp_id != -1 && cdp_id != -1)
            {
                /* Flip the address for sending response to the unitdata */
                TEST_BuildAndSendMsg(1/*send one*/, handle, 
                                      &ies[cgp_id].param_data.callingPartyAddr,
                                      &ies[cdp_id].param_data.calledPartyAddr);

                break; /*we don't need to continue the loop*/
            }
        } 
    }
    else
    {
        cout << "ERROR: Failed to receive Unit data:" << endl;
    }

    return;
}

int TEST_Main(ITS_HANDLE handle)
{
    cout << endl << "Begin SGP Simulator ..." << endl;

    try
    {
        cout << "\n Enter SG Point Code: \n";
        cin  >> LOCAL_PC;

        int cmdInput = 0, ret = ITS_SUCCESS;

        TEST_PrintCommand();

        scanf("%d", &cmdInput);
        printf("\nYou input %d.\n", cmdInput);
        
        if (cmdInput == TEST_EXIT)
        {
            printf("Exiting Test Program...\n");

            APP_SetStopper();
        }

        if (VALID_CHOICE(cmdInput))
        {    
            ret = TEST_ExecuteCommand(cmdInput, handle); 
        }
        else
        {
            cout << "Wrong Choice, Try again:" << endl;
        }
    }
    catch (ITS_GenericException& exp)
    {
        cout << endl << exp.GetDescription() << endl;

        exit(EXIT_FAILURE);
    }

    cout << endl << "Press Enter to quit...";

    char c = '\0';
    cin.get(c);

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
    printf("    %d) Send PAUSE Message. \n", BUILD_PAUSE);
    printf("    %d) Send RESUME Message. \n", BUILD_RESUME);
    printf("    %d) Send STATUS Message.\n", BUILD_STATUS);
    printf("    %d) Dump ISS7 Routing Table.\n", DUMP_RT);
    printf("    %d) Dump AS Table.\n", DUMP_AS_TABLE);
    printf("    %d) Dump ASP Table.\n", DUMP_ASP_TABLE);
    printf("\n    %d) Quit program.\n", TEST_EXIT);

    printf("\n  -> ");

    return 1;
}

int
TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle)
{
    int ret = ITS_SUCCESS;
    MTP3_HEADER hdr;
    ITS_EVENT evt;
    ITS_USHORT src = 0x00;

#if defined (CCITT)
    src = ITS_MTP3_CCITT_SRC;
#elif defined (ANSI)
    src = ITS_MTP3_ANSI_SRC;
#endif

    evt.src =src;

    memset(&hdr, 0, sizeof(MTP3_HEADER));

    switch(cmdInput)
    {
    case BUILD_DATA:
    {
        int iterration = 0;

        cout << "TEST ---> Enter DPC:";
        cin  >> REMOTE_PC;

        cout << "TEST ---> Enter SSN:";
        cin  >> REMOTE_SSN;

        cout << endl << "Number of Msg to Send:";
        cin  >> iterration;
        cout << endl;

        ret = TEST_BuildAndSendMsg(iterration, handle, NULL, NULL);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Occured Sending DATA.\n";
        }
 
        break;
    }
    case BUILD_PAUSE:
    {
        MTP3_PAUSE_RESUME pause;

        MTP3_PC_SET_VALUE(pause.affected, LOCAL_PC);

        ret = MTP3_Encode(&evt, MTP3_MSG_PAUSE, &hdr, (ITS_OCTET*)&pause,
                          sizeof(MTP3_PAUSE_RESUME));
        if (ret != ITS_SUCCESS)
        {
             cout << "TEST ERROR: Could not Encode PAUSE indication message.\n"; 
        } 

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST_ERROR: Transport PutEvent Failed.\n";
        }
    
        break;
    }
    case BUILD_RESUME:
    {
        MTP3_PAUSE_RESUME resume;

        MTP3_PC_SET_VALUE(resume.affected, LOCAL_PC);

        ret = MTP3_Encode(&evt, MTP3_MSG_RESUME, &hdr, (ITS_OCTET*)&resume, 
                          sizeof(MTP3_PAUSE_RESUME));
        if (ret != ITS_SUCCESS) 
        {
             cout << "TEST ERROR: Could not Encode RESUME indication message.\n"; 
        }

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {       
            cout << "TEST_ERROR: Transport PutEvent Failed.\n";
        }
   
        break;
    }
    case BUILD_STATUS:
    {
        MTP3_STATUS status;

        MTP3_PC_SET_VALUE(status.affected, LOCAL_PC);
        status.cause = MTP3_STATUS_CONGESTED;
        status.congLevel = 0x03U;

        ret = MTP3_Encode(&evt, MTP3_MSG_STATUS, &hdr, (ITS_OCTET*)&status, 
                          sizeof(MTP3_STATUS));
        if (ret != ITS_SUCCESS) 
        {
             cout << "TEST ERROR: Could not Encode STATUS indication message.\n"; 
        }

        ret = TRANSPORT_PutEvent(UAL_MANAGER_INSTANCE, &evt);
        if (ret != ITS_SUCCESS)
        {       
            cout << "TEST_ERROR: Transport PutEvent Failed.\n";
        }
   
        break;
    }
    case DUMP_RT:
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
    {
        char* dumpStr = NULL;

        UAL_DumpASTable(&dumpStr);

        if(dumpStr != NULL)
        {
           printf("%s", dumpStr);

           free(dumpStr);
           dumpStr = NULL;
        }
        break;
    }
    case DUMP_ASP_TABLE:
    {
        char* dumpStr = NULL;

        UAL_DumpASPTable(&dumpStr);

        if(dumpStr != NULL)
        {
            printf("\n%s", dumpStr);
            free(dumpStr);
            dumpStr = NULL;
        }
        break;
    }
    default:

        cout << "TEST ERROR: Invalid command.\n";

        break;
    }

    return ret;

}

}
