/*********************************-*-C-*-************************************
 *                                                                          *
 *             Copyright 1997,1998 IntelliNet Technologies, Inc.            *
 *                            All Rights Reserved.                          *
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
 *  ID: $Id: test-itu.c,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:02  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:23  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:54:38  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 1.2  2002/12/19 18:02:22  randresol
 * LOG: Add option for load testing
 * LOG:
 * LOG: Revision 1.1  2002/11/10 00:07:46  randresol
 * LOG: Add ITU test file for TCAP/SCCP/MTP3 stack
 * LOG:
 * LOG: 
 *
 ****************************************************************************/

#include <stdio.h>
#include <iostream.h>
#include <its++.h>
#include <engine.h>
#include <its_dsm_gcs.h>
#include <its_dsm_stub.h>


#include <ss7_mgmt.h>


#if 1
#undef ANSI
#undef CCITT
#define CCITT
#else
#undef CCITT
#undef ANSI
#define ANSI
#endif

#if defined(ANSI)
#include <ansi/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#endif

#include <tcap++.h>
#include <Asn.h>
#include <AsnException.h>

#include <inap_cpp.h>
#include <inap_etsi_cs1_connect_arg.h>





#ident "$Id: test-itu.c,v 1.1.1.1 2007-10-08 11:12:25 bsccs2 Exp $"

#if defined(WIN32)

#if defined(TEST_IMPLEMENTATION)
#define TESTDLLAPI __declspec(dllexport)
#else
#define TESTDLLAPI __declspec(dllimport)
#endif

#else  /* WIN32 */

#define TESTDLLAPI

#endif /* WIN32 */

#if defined(ITS_NAMESPACE)
using namespace std;
using namespace its;
using namespace inap;
using namespace inap_etsi_cs1;
#endif



#define TCAP_RECEIVE_QUEUE_ID    1

ITS_THREAD thr;


static ITS_UINT sndCnt=0, rcvCnt=0;

static ITS_BOOLEAN sendTraffic = ITS_FALSE;

static TaskQueueTransport *tcapEventQueue;
static ITS_TIME startTime = 0 ;

///////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_INT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

#define LOCAL_PC    8
#define LOCAL_SSN   5

#define REMOTE_PC   10 
#define REMOTE_SSN  6


static ITS_UINT  BURST       =      10;
static ITS_UINT  DELAY       =      400;
static ITS_UINT  DURATION    =      0xFFFFFFFF; 


///////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//

vector<byte> BuildOperationConnectArg();




extern "C" TESTDLLAPI void
TcapTestPreFunc()
{

    printf("*** TcapTestPreFunc: TcapTest Initialization ***\n");

    tcapEventQueue = new TaskQueueTransport("Tcap Events",
                                          TCAP_RECEIVE_QUEUE_ID,
                                          ITS_TRANSPORT_TQUEUE);
}


extern "C" void SendBegin()
{
    ITS_USHORT dialogueID = 0;

    TCAP_AllocateDialogueId(ISS7_CCITT_Stack, &dialogueID);


    // Create begin dialogue (dlg) object and populate it.

    TCAP_Begin beginDlg;

    beginDlg.SetDialogueID(dialogueID);

    beginDlg.SetOrigAddr(
                SCCP_ADDR_INDICATOR,
                LOCAL_PC,
                LOCAL_SSN,
                NULL,
                0);

    beginDlg.SetDestAddr(
                SCCP_ADDR_INDICATOR,
                REMOTE_PC,
                REMOTE_SSN,
                NULL,
                0);

    // Create invoke component (cpt) object and populate it.

    TCAP_Invoke invokeCpt;

    invokeCpt.SetInvokeID(1);

    // "OP_connect" is defined in file inap_cpp.h.

    invokeCpt.SetOperation(OP_connect);

    // Class 2 (only errors appear in the INAP Connect operation macro, see
    // INAP recommendation Q.1218).

    invokeCpt.SetClass(2);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses ETSI INAP ASN.1 C++ API.
    //

    vector<byte> encodedConnectArg = BuildOperationConnectArg(); 

    //
    ///////////////////////////////////////////////////////////////////////////

    // The parameter field of the TCAP invoke component contains the ETSI
    // INAP operation argument.

    invokeCpt.SetParameter(encodedConnectArg);


    TCAP_Component::Send(ISS7_CCITT_Stack, &beginDlg, &invokeCpt);

    TCAP_Dialogue::Send(ISS7_CCITT_Stack, &beginDlg);

}

extern "C" TESTDLLAPI void
TrafficGenerator(void *arg)
{
    int i;


    cout <<"**** Entering Traffic Generator..." << endl;

    while(true)
    {
        if (sendTraffic)
        {
            for (i = 0; i < BURST; i++)
            {
                SendBegin();
                sndCnt++;
            }
        }

        TIMERS_USleep(USEC_PER_MILLISEC * DELAY);

        if ((TIMERS_Time() - startTime) > DURATION)
        {
            sendTraffic = ITS_FALSE;
        }


    }

    return ;

}


extern "C" TESTDLLAPI int
TCAP_SS7PostNextEvent(TPOOL_THREAD *thr, ITS_EVENT *ev)
{
    return (ITS_SUCCESS);
}


extern "C" TESTDLLAPI void
TCAP_ShowStats(void *arg)
{

    cout <<"**** TCAP_ShowStats Started..." << endl;
    while (true)
    {
        TIMERS_Sleep(1);

        printf("Total sent   : %d\n"
               "Total Receive: %d\n"
               "Pending      : %d\n\n",
               sndCnt, rcvCnt, sndCnt - rcvCnt);

    }

}




extern "C" TESTDLLAPI void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT *ev = (ITS_EVENT *)callData;
    ITS_OCTET mType;
    ITS_OCTET buf[255];
    ITS_USHORT len;

#if defined(ANSI)
    MTP3_HEADER_ANSI mtp3;

printf("\n\n\n\n\n\n\n\n\n\n\n\nMTP3 MANAGEMENT\n\n\n\n\n\n\n"); 
    MTP3_Decode_ANSI(ev, &mType, &mtp3, buf, &len);

    switch (mType)
    {
    case MTP3_MSG_USER_DATA:
        printf("################### GOT USER DATA\n");
        break;

    case MTP3_MSG_PAUSE:
        printf("################### GOT PAUSE: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)buf)->affected));
        sendTraffic = ITS_FALSE;
        break;

    case MTP3_MSG_RESUME:
        printf("################### GOT RESUME: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_ANSI *)buf)->affected));
        sendTraffic = ITS_TRUE;
        break;


    case MTP3_MSG_STATUS:
        printf("################### GOT STATUS: pc %06x cause %d cong %d\n",
               MTP3_PC_GET_VALUE(((MTP3_STATUS_ANSI *)buf)->affected),
               ((MTP3_STATUS_ANSI *)buf)->cause,
               ((MTP3_STATUS_ANSI *)buf)->congLevel);
        break;

    default:
        printf("################### DON'T KNOW WHAT I GOT\n");
        break;
    }
#elif defined(CCITT)
    MTP3_HEADER_CCITT mtp3;

printf("\n\n\n\n\n\n\n\n\n\n\n\nMTP3 MANAGEMENT\n\n\n\n\n\n\n"); 
    MTP3_Decode_CCITT(ev, &mType, &mtp3, buf, &len);

    switch (mType)
    {
    case MTP3_MSG_USER_DATA:
        printf("################### GOT USER DATA\n");
        break;

    case MTP3_MSG_PAUSE:
        printf("################### GOT PAUSE: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)buf)->affected));
        sendTraffic = ITS_FALSE;
        break;

    case MTP3_MSG_RESUME:
        printf("################### GOT RESUME: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_CCITT *)buf)->affected));
        sendTraffic = ITS_TRUE;
        break;

    case MTP3_MSG_STATUS:
        printf("################### GOT STATUS: pc %06x cause %d cong %d\n",
               MTP3_PC_GET_VALUE(((MTP3_STATUS_CCITT *)buf)->affected),
               ((MTP3_STATUS_CCITT *)buf)->cause,
               ((MTP3_STATUS_CCITT *)buf)->congLevel);
        break;

    default:
        printf("################### DON'T KNOW WHAT I GOT\n");
        break;
    }
#endif
}

extern "C" TESTDLLAPI void
TcapEventHandler(void *arg)
{
    ITS_UINT i;
    ITS_Event event ; 
    ITS_USHORT currentDialogueID = 0;
    ITS_INT res = 0;
    ITS_BOOLEAN beginReceived = ITS_FALSE;

    TCAP_Dialogue* recvDlg       = NULL;
    TCAP_Component* recvCpt      = NULL;

    printf("*** TcapEventHandler: Getting TCAP Event ***\n");

    if (tcapEventQueue == 0)
    {
        printf("tcapEventQueue not is Initialized yet...\n");
        TIMERS_Sleep(1);
        return;
    }

    printf("*** TcapEventHandler: Waiting for TCAP Event ***\n");

    while (TRANSPORT_GetNextEvent((TRANSPORT_Control *)tcapEventQueue->GetTC(), &event.GetEvent()) == ITS_SUCCESS)
    {

 

/*
        printf("\n\n***** Application Got Event *************\n");
        for (i = 0; i < event.GetEvent().len; i++)
        {
            printf("%02X ", event.GetData()[i]);
        }
        printf("\n\n");

*/

        if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_DLG)
        {
            if (recvDlg != NULL)
            {
                delete recvDlg;
                recvDlg = NULL;
            }

            res = TCAP_Dialogue::Receive(ISS7_CCITT_Stack, event, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            //cout << endl << "Received TCAP dialogue..." << endl;

            currentDialogueID = recvDlg->GetDialogueID();

            //cout << "Dialogue ID: <" << currentDialogueID << ">." << endl;

            rcvCnt++;

            switch (recvDlg->GetDialogueType())
            {
            case TCAP_PT_TC_BEGIN_CCITT:
            {

                //cout << "Begin dialogue." << endl;

                TCAP_Begin* recvBeginDlg =
                    static_cast<TCAP_Begin*>(recvDlg);

                beginReceived = ITS_TRUE;

                break;
            }
            case TCAP_PT_TC_END_CCITT:
            {
                //cout << "End dialogue." << endl;

                TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);

                break;
            }

            default:
                //cout << " This case is not handle yet..." << endl;
                break; 

            }

        }
        else if (TCAP_MSG_TYPE(&event.GetEvent()) == ITS_TCAP_CPT)
        {
            if (recvCpt != NULL)
            {
                delete recvCpt;
                recvCpt = NULL;
            }

            res = TCAP_Component::Receive(ISS7_CCITT_Stack, event, recvDlg, &recvCpt);
            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            //cout << endl << "Receive TCAP component..." << endl;

            switch (recvCpt->GetComponentType())
            {
            case TCAP_PT_TC_INVOKE_CCITT:
            {
                //cout << "Invoke component." << endl;

                TCAP_Invoke* recvInvokeCpt =
                    static_cast<TCAP_Invoke*> (recvCpt);

                break;

            }
            default:
                //cout << " This case is not handle yet..." << endl;
                break;

            }

        }

        if (beginReceived && recvCpt && recvCpt->GetLast() )
        {
       
            TCAP_End endDlg;

            endDlg.SetDialogueID(currentDialogueID);

            TCAP_Dialogue::Send(ISS7_CCITT_Stack, &endDlg);

            //printf("***** Application Sendind End Dialogue *****\n\n");

            sndCnt++;
          
           beginReceived = ITS_FALSE; 

        }

        ITS_EVENT_TERM(&event.GetEvent());

    }

    return;
}

void
TestCases(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet, linkCode, ret;

    ITS_C_ASSERT(dbc != NULL);

#if defined(ANSI)
    if (DBC_Cmd(dbc, "il", "Inhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("*********** Going to inhibit link 1 now *************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_INHIBIT_LINK,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Returned from the MGMT Inhibit *************\n");
    }
    else if (DBC_Cmd(dbc, "ul", "Uninhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("*********** Going to uninhibit link 1 now *************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_UNINHIBIT_LINK,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Returned from the MGMT UnInhibit *************\n");
    }
    else if (DBC_Cmd(dbc, "dls", "Deactivate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        printf("*********** Deactivating link set ************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                       NULL, 0,
                       (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);
        printf("*********** Link set deactivated *************\n");
    }
    else if (DBC_Cmd(dbc, "als", "Activate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        printf("*********** Deactivating link ************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_ACTIVATE_LINK_SET,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Link deactivated *************\n");
    }
    else if (DBC_Cmd(dbc, "dln", "Deactivate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("****** Going to Deactivate link 1 now ******\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_DEACTIVATE_LINK,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("****** Returned from the MGMT Deactivate Link 1 ******\n");
    }
    else if (DBC_Cmd(dbc, "aln", "Activate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("****** Going to Activate link 1 now ******\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_ACTIVATE_LINK,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("****** Returned from the MGMT Activate Link 1 ******\n");
    }
    else if (DBC_Cmd(dbc, "start", "Start MTP3", "<>", "<>"))
    {
        printf("*********** Starting MTP3 **************\n");
        MGMT_Main_ANSI(MTP3_USER,
                       MGMT_TRIGGER_RESTART,
                       NULL, 0,
                       ITS_SS7_DEFAULT_LINK_SET,
                       ITS_SS7_DEFAULT_LINK_CODE);

        printf("*********** Returned from the MGMT Restart *************\n");
    }
#elif defined(CCITT)
    if (DBC_Cmd(dbc, "il", "Inhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("*********** Going to inhibit link 1 now *************\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_INHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Returned from the MGMT Inhibit *************\n");
    }
    else if (DBC_Cmd(dbc, "ul", "Uninhibit Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("*********** Going to uninhibit link 1 now *************\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_UNINHIBIT_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Returned from the MGMT UnInhibit *************\n");
    }
    else if (DBC_Cmd(dbc, "dls", "Deactivate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        printf("*********** Deactivating link set ************\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, ITS_SS7_DEFAULT_LINK_CODE);
        printf("*********** Link set deactivated *************\n");
    }
    else if (DBC_Cmd(dbc, "als", "Activate Link Set", "<ls>", "<link set>"))
    {
        ret = sscanf(cmdLine, "%s %d", buf, &linkSet);
        if (ret != 2)
        {
            return;
        }

        printf("*********** Activate Link Set ************\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK_SET,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("*********** Link Set Activated *************\n");
    }
    else if (DBC_Cmd(dbc, "dln", "Deactivate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("****** Going to Deactivate link now ******\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_DEACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("****** Returned from the MGMT Deactivate Link ******\n");
    }
    else if (DBC_Cmd(dbc, "aln", "Activate Link", "<ls> <lc>", "<link set> <link code>"))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &linkSet, &linkCode);
        if (ret != 3)
        {
            return;
        }

        printf("****** Going to Activate link now ******\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_ACTIVATE_LINK,
                        NULL, 0,
                        (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("****** Returned from the MGMT Activate Link ******\n");
    }
    else if (DBC_Cmd(dbc, "start", "Start MTP3", "<>", "<>"))
    {
        printf("*********** Starting MTP3 **************\n");
        MGMT_Main_CCITT(MTP3_USER,
                        MGMT_TRIGGER_RESTART,
                        NULL, 0,
                        ITS_SS7_DEFAULT_LINK_SET,
                        ITS_SS7_DEFAULT_LINK_CODE);

        printf("*********** Returned from the MGMT Restart *************\n");
    }
    else if (DBC_Cmd(dbc, "sendB", "Send Begin", "<>", "<>"))
    {
        printf("**** Sending Begin ****");
        SendBegin();
        sndCnt++;
        printf("**** Begin Sent ***");

    }
    else if (DBC_Cmd(dbc, "startt", "start traffic ", "<>", "<>"))
    {
        printf("**** Starting Traffic Begin ****");
        sendTraffic = ITS_TRUE; 
        startTime = TIMERS_Time();

    }
    else if (DBC_Cmd(dbc, "clear", "clear statistics ", "<>", "<>"))
    {
        sndCnt=0, rcvCnt=0;
    }
    else if (DBC_Cmd(dbc, "stopt", "stopping traffic ", "<>", "<>"))
    {
        printf("**** Stopping Traffic Begin ****");
        sendTraffic = ITS_FALSE;

    }
    if (DBC_Cmd(dbc, "load", "load test", "<BURST> <DELAY>", "<BURST> <DELAY>"
))
    {
        ret = sscanf(cmdLine, "%s %d %d", buf, &BURST, &DELAY);
        if (ret != 3)
        {
            return;
        }

    }
    else if (DBC_Cmd(dbc, "dumpLinkSets", "Dump Link Sets", "<>", "<>"))
    {
        char *dump = NULL;

        ROUTE_LockTable();

        LINKSET_DumpLinkSetHashtable(&dump);
 
        ROUTE_UnlockTable();

        if (dump)
        {
            printf(dump);
            free(dump);
        }
    }
#endif
}


int
main(int argc, const char **argv)
{

    APPL_SetName("test");

    DBC_SetDoCommand(TestCases);

    ITS_AddFeature(itsDSM_GcsImplClass);

    ITS_AddFeature(itsDSM_StubImplClass);


    ENGINE_Initialize(argc, argv, NULL, 0);

    return (ENGINE_Run(argc, argv));
}


///////////////////////////////////////////////////////////////////////////////
//
//  Utilities.
//

//
//  Macro to get the size (count of items) of a fixed array.
//
#define FixedArraySize(array)       \
    (sizeof(array) / sizeof(array[0]))

//
//  Macro to convert fixed arrays (of bytes) to vectors.
//
#define FixedByteArrayToVector(array)   \
    (vector<byte>(array, array + FixedArraySize(array)))



////////////////////////////////////////////////////////////////////////////////
//
//  How to Build an INAP Connect operation argument (ConnectArg):
//
//  o   Create ConnectArg object.
//
//  o   Insert data step by step in the created ConnectArg object (i.e. populate
//      various parameters of the Connect operation argument).
//  
//  o   Encode the ConnectArg object to produce a ConnectArg encoded value.
//

vector<byte> 
BuildOperationConnectArg()
{
    //  [1] Create ConnectArg object.

    ConnectArg* connectArg = new ConnectArg();

    ////////////////////////////////////////////////////////////////////////////

    //  Memory management note: all the following parameter objects that are
    //  used to populate the ConnectArg object must be created in the heap (i.e.
    //  using operator new) and not in the stack. They are automatically deleted
    //  when the connectArg object is deleted. Only the ConnectArg object itself
    //  can be created in the stack. 

    ////////////////////////////////////////////////////////////////////////////

    //  [2] Populate mandatory parameter "destinationRoutingAddress".

    //  [2-1] Create DestinationRoutingAddress object.

    DestinationRoutingAddress* 
        destinationRoutingAddress =
            new DestinationRoutingAddress();
    
    //  INAP API Note: a DestinationRoutingAddress object contains a list of 
    //  CalledPartyNumber objects.

    //  [2-1-1] Create CalledPartyNumber object.

    byte fixedArray1[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

    CalledPartyNumber*
        calledPartyNumber =
            new CalledPartyNumber(FixedByteArrayToVector(fixedArray1));

    //  [2-1-2] Add CalledPartyNumber object to DestinationRoutingAddress 
    //  object. 

    destinationRoutingAddress->AddElement(calledPartyNumber);

    //  [2-2] Set DestinationRoutingAddress object in ConnectArg object.

    connectArg->SetDestinationRoutingAddress(destinationRoutingAddress);

    ////////////////////////////////////////////////////////////////////////////

    //  [3] Populate optional parameter "alertingPattern".

    //  [3-1] Create an AlertingPattern object.

    byte fixedArray2[] = { 0x20, 0x21, 0x22 };

    AlertingPattern* 
        alertingPattern =
            new AlertingPattern(FixedByteArrayToVector(fixedArray2));

    //  [3-2] Set AlertingPattern object in ConnectArg object.

    connectArg->SetAlertingPattern(alertingPattern);

    ////////////////////////////////////////////////////////////////////////////

    //  [4] Populate optional parameter "correlationID".

    //  [4-1] Create CorrelationID object.

    byte fixedArray3[] = { 0x30, 0x31, 0x32, 0x33, 0x34 };

    CorrelationID*
        correlationID =
            new CorrelationID(FixedByteArrayToVector(fixedArray3));

    //  [4-2] Set CorrelationID object in ConnectArg object.

    connectArg->SetCorrelationID(correlationID);

    ////////////////////////////////////////////////////////////////////////////

    //  [5] Populate optional parameter "routeList".

    //  [5-1] Create RouteList object.

    RouteList* routeList = new RouteList();

    //  INAP API Note: a RouteList object contains a list of 
    //  RouteList::OCTETSTRING objects.

    //  [5-1-1] Create RouteList::OCTETSTRING object.

    byte fixedArray4[] = { 0x01, 0x02, 0x03 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING1 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray4));

    //  [5-1-2] Create RouteList::OCTETSTRING object.

    byte fixedArray5[] = { 0x11, 0x22, 0x33, 0x44 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING2 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray5));

    //  [5-1-3] Create RouteList::OCTETSTRING object.

    byte fixedArray6[] = { 0x10, 0x20, 0x30, 0x40, 0x50 };

    RouteList::OCTETSTRING*
        routeListOCTETSTRING3 =
            new RouteList::OCTETSTRING(
                FixedByteArrayToVector(fixedArray6));

    //  [5-1-4] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING1);

    //  [5-1-5] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING2);

    //  [5-1-6] Add RouteList::OCTETSTRING object to RouteList object.

    routeList->AddElement(routeListOCTETSTRING3);

    //  [5-2] Set RouteList object in ConnectArg object.

    connectArg->SetRouteList(routeList);

    ////////////////////////////////////////////////////////////////////////////

    //  [6] Populate optional parameter "callingPartyNumber".

    //  [6-1] Create CallingPartyNumber object.

    byte fixedArray7[] = { 0x07, 0x07, 0x08, 0x09, 0x09, 0x08, 0x04 };

    CallingPartyNumber*
        callingPartyNumber =
            new CallingPartyNumber(FixedByteArrayToVector(fixedArray7));

    //  [6-2] Set CallingPartyNumber object in ConnectArg object.

    connectArg->SetCallingPartyNumber(callingPartyNumber);

    ////////////////////////////////////////////////////////////////////////////

    //  [7] Encode ConnectArg object.

    Octets* octets = NULL;

    try
    {
        //  Can throw and AsnEncodeError execption. 

        octets = connectArg->Encode();
    }
    catch (AsnEncodeError& encodeError)
    {
        //cout << endl << encodeError.GetDescription() << endl;

        //  More specific error processing should be added here.

        //  By default re-throw exception.

        throw encodeError;
    }
/*
    cout << endl;
    cout << "Printing ConnectArg ASN.1 encoded value..." << endl;
    cout << *octets;
    cout << endl;
*/

    ////////////////////////////////////////////////////////////////////////////

    //  [8] Retrieve ConnectArg ASN.1 encoded value from octets object.

    vector<byte> encodedConnectArg = octets->GetArray();

    ////////////////////////////////////////////////////////////////////////////

    //  [9] Free all memory allocated on the heap.

    //  [9-1] Delete ConnectArg object (and therefore all the parameter
    //  objects that have been previously set).

    delete connectArg;

    //  [9-2] Delete Octets object created by the call to Encode.

    delete octets;

    ////////////////////////////////////////////////////////////////////////////

    //  [10] Return (by value) ConnectArg ASN.1 encoded value.

    return encodedConnectArg;
}



