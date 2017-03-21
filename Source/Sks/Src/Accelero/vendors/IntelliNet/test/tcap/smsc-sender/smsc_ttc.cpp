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
 *  ID: $Id: smsc_ttc.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:25:03  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:30  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:15:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:55:25  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 1.2  2005/03/23 09:41:23  cvsadmin
 * LOG: PR6.4.2 sources propagated to Current.
 * LOG:
 * LOG: Revision 1.1.2.1  2004/12/17 04:16:26  randresol
 * LOG: Add TCAP test program for TTC
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


#undef TTC
#undef CCITT
#define TTC

#if defined(TTC)
#include <japan/mtp3.h>
#elif defined(CCITT)
#include <itu/mtp3.h>
#elif defined(ANSI)
#include <ansi/mtp3.h>
#endif

#include <tcap++.h>
#include <Asn.h>
#include <AsnException.h>

//#include <inap_cpp.h>
//#include <inap_etsi_cs1_connect_arg.h>
/*#include <mtp3_intern.h>*/

/*#include <as_41e_sms_request_il.h>*/
#include <AsnException.h>



#ident "$Id: smsc_ttc.cpp,v 1.1.1.1 2007-10-08 11:12:26 bsccs2 Exp $"

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
//using namespace inap;
//using namespace inap_etsi_cs1;
#endif



#define TCAP_RECEIVE_QUEUE_ID    1

ITS_THREAD thr;

/**** statistic information ****/
static ITS_UINT openTr = 0, closedTr = 0;
static ITS_UINT averageTransactionTime = 0;
static ITS_UINT minTransactionTime    = 5000;
static ITS_UINT maxTransactionTime    = 0;

static ITS_UINT numberOfTransactionPerStatictic = 100;

static ITS_MUTEX    statsGate;

static ITS_BOOLEAN sendTraffic = ITS_FALSE;
static ITS_USHORT currentDialogueID = 0;

static TaskQueueTransport *tcapEventQueue;
static ITS_TIME startTime = 0 ;

static ITS_BOOLEAN shortTr = ITS_TRUE;

typedef struct
{
    ITS_BOOLEAN beginReceived;
    ITS_BOOLEAN continueReceived; 
    ITS_UINT    timestamp; /* in ms */
}
TrContext;

static TrContext tContext[0xFFFF] = {ITS_FALSE, ITS_FALSE, 0};
void TestCases(DBC_Server *dbc, const char *cmdLine);

///////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

#define SCCP_ADDR_INDICATOR (SCCP_CPA_ROUTE_INT |   \
                             SCCP_CPA_ROUTE_SSN |   \
                             SCCP_CPA_HAS_PC    |   \
                             SCCP_CPA_HAS_SSN)

#define LOCAL_PC    0x1011
#define LOCAL_SSN   11 

#define REMOTE_PC   0x1010
#define REMOTE_SSN  4


static ITS_UINT  BURST       =      1;
static ITS_UINT  DELAY       =      2000;
static ITS_UINT  DURATION    =      0xFFFFFFFF; 

static ITS_BOOLEAN isShuttingDown = ITS_FALSE;

static ITS_BOOLEAN showStat = ITS_TRUE;

static void ShutDownNode();


///////////////////////////////////////////////////////////////////////////////
//
//  Local function declarations.
//

vector<byte> BuildOperationConnectArg();


extern "C" TESTDLLAPI ITS_USHORT  
ApplicationSelector(ITS_HDR *h, ITS_EVENT *ev)
{
   // instruct Accelero to route all inbound message to TCAP instance 

      /*printf("processing dialogue_id %d\n", h->context.dialogue_id);*/
      return (TCAP_RECEIVE_QUEUE_ID);
}


static ITS_UINT 
GetMsTimestamp()
{
    ITS_TIME secs, usecs;
    ITS_UINT ms;

    MUTEX_AcquireMutex(&statsGate); 

    TIMERS_UTime(&secs, &usecs);

    ms = (secs % MILLISEC_PER_SEC) * MILLISEC_PER_SEC + usecs/USEC_PER_MILLISEC;

    MUTEX_ReleaseMutex(&statsGate);

    //printf("msTimestamp: %d\n", ms);
 
    return ms;
    
}

static void
UpdateStats(ITS_USHORT dialogueID)
{
    ITS_UINT trTime;

    if (MUTEX_AcquireMutex(&statsGate) != ITS_SUCCESS)
    {
        printf("GetMsTimeStamp: failed to acquire mutex\n");

        return;
    }


    trTime = GetMsTimestamp() - tContext[dialogueID].timestamp; 

    if(trTime < 0 || trTime > 0x0FFFFFFF)
    {
        MUTEX_ReleaseMutex(&statsGate);

        return;
    }


    if (trTime < minTransactionTime)
    {
        minTransactionTime = trTime; 
    }
    else if (trTime > maxTransactionTime)
    {
        maxTransactionTime = trTime; 
    }

    /* update trTime average */
    if (closedTr <  numberOfTransactionPerStatictic)
    {
        averageTransactionTime = 
           (averageTransactionTime * (closedTr - 1) + trTime)/ closedTr; 
    }
    else
    {
        averageTransactionTime = 
           (averageTransactionTime * (numberOfTransactionPerStatictic - 1) 
                 + trTime)/ numberOfTransactionPerStatictic; 
    }

    MUTEX_ReleaseMutex(&statsGate);

}




extern "C" TESTDLLAPI void
TcapTestPreFunc()
{

    /*printf("*** TcapTestPreFunc: TcapTest Initialization ***\n");*/

    tcapEventQueue = new TaskQueueTransport("Tcap Events",
                                          TCAP_RECEIVE_QUEUE_ID,
                                          ITS_TRANSPORT_TQUEUE);

    /* create mutex */
    if (MUTEX_CreateMutex(&statsGate, 0) != ITS_SUCCESS)
    {
        printf("PreFunc: Couldn't create mutex\n");

        return;
    }

    DBC_AddDoCommand(TestCases);

    /* To automatically start MTP3 stack */
/*
    MGMT_Main_CCITT(MTP3_USER,
                    MGMT_TRIGGER_RESTART,
                    NULL, 0,
                    ITS_SS7_DEFAULT_LINK_SET,
                    ITS_SS7_DEFAULT_LINK_CODE);

*/
    
}

extern "C" TESTDLLAPI void
TcapTestPostFunc()
{
    printf("*** TcapTestPostFunc: TcapTest Termination ***\n");
}



extern "C" void SendBegin()
{
    ITS_USHORT dialogueID = 0;
    ITS_USHORT tStamp = 0;

    tStamp = GetMsTimestamp();

    TCAP_AllocateDialogueId(ISS7_TTC_Stack, &dialogueID);

    
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

    beginDlg.SetOPC(LOCAL_PC);

    // Create invoke component (cpt) object and populate it.

    TCAP_Invoke invokeCpt;

    invokeCpt.SetInvokeID(1);

    invokeCpt.SetTimeOut(30);

    // "OP_connect" is defined in file inap_cpp.h.

    //invokeCpt.SetOperation(true,1 ,1);
    invokeCpt.SetOperation(1);

    // Class 2 (only errors appear in the INAP Connect operation macro, see
    // INAP recommendation Q.1218).

    invokeCpt.SetClass(1);

    ///////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses ETSI INAP ASN.1 C++ API.
    //

    vector<byte> encodedConnectArg /*= BuildOperationConnectArg()*/; 

    invokeCpt.SetParameter(encodedConnectArg);
/*
    ITS_OCTET buf[] = { 0x21, 0x43, 0x65, 0x98, 0x30};
    its::ByteArray array;
    array.assign(buf, buf+5);
    invokeCpt.SetParameter(array);
*/
    //
    ///////////////////////////////////////////////////////////////////////////

    // The parameter field of the TCAP invoke component contains the ETSI
    // INAP operation argument.
#if 0
    as_41e::SMSRequestIL smsreq;
    as_41e::MobileIdentificationNumber min;
    its::ByteArray array;
    min.SetArray(array);
    static int i = 0;

    if (i % 8 == 0) buf[0] = 0x33; // failure scenario.
    i++;

    try
    {
	its::Octets *octs;

	smsreq.SetMobileIdentificationNumber(min);

	cout << smsreq << endl;

	octs = smsreq.Encode();
	
       invokeCpt.SetParameter(octs->GetArray());
    }
    catch(...)
    {
	throw;
    }
#endif

    MUTEX_AcquireMutex(&statsGate); 

    tContext[dialogueID].timestamp = GetMsTimestamp();
/*
    printf("SendBegin Delta = %d ctTs = %d tStamp = %d\n",
            tContext[dialogueID].timestamp - tStamp,
            tContext[dialogueID].timestamp, tStamp);
*/

    MUTEX_ReleaseMutex(&statsGate);

    TCAP_Component::Send(ISS7_TTC_Stack, &beginDlg, &invokeCpt);

    TCAP_Dialogue::Send(ISS7_TTC_Stack, &beginDlg);

}

extern "C" void SendContinue()
{

    // Create begin dialogue (dlg) object and populate it.

    TCAP_Continue continueDlg;

    continueDlg.SetDialogueID(currentDialogueID);


    continueDlg.SetOrigAddr(
                SCCP_ADDR_INDICATOR,
                LOCAL_PC,
                LOCAL_SSN,
                NULL,
                0);
/*
    continueDlg.SetDestAddr(
                SCCP_ADDR_INDICATOR,
                REMOTE_PC,
                REMOTE_SSN,
                NULL,
                0);
*/

    // Create invoke component (cpt) object and populate it.


    TCAP_Invoke invokeCpt;

    invokeCpt.SetInvokeID(2);

    invokeCpt.SetTimeOut(5);

    // "OP_connect" is defined in file inap_cpp.h.

     //invokeCpt.SetOperation(true, 1, 1);
     invokeCpt.SetOperation(1);

    // Class 2 (only errors appear in the INAP Connect operation macro, see
    // INAP recommendation Q.1218).

    /*invokeCpt.SetClass(1);*/
    ///////////////////////////////////////////////////////////////////////////
    //
    //  Function call uses ETSI INAP ASN.1 C++ API.
    //

    vector<byte> encodedConnectArg /*= BuildOperationConnectArg()*/;

    //
    ///////////////////////////////////////////////////////////////////////////

    // The parameter field of the TCAP invoke component contains the ETSI
    // INAP operation argument.

    invokeCpt.SetParameter(encodedConnectArg);


    TCAP_Result resultCpt(true);

    resultCpt.SetInvokeID(1);


    TCAP_Component::Send(ISS7_TTC_Stack, &continueDlg, &invokeCpt);

    TCAP_Component::Send(ISS7_TTC_Stack, &continueDlg, &resultCpt);

    TCAP_Dialogue::Send(ISS7_TTC_Stack, &continueDlg);

    /*printf("TC_CONTINUE sent for dialogue: %d\n", currentDialogueID);*/

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
                openTr++;
            }
        }

        TIMERS_USleep(USEC_PER_MILLISEC * DELAY);

        if ((TIMERS_Time() - startTime) > DURATION)
        {
            sendTraffic = ITS_FALSE;
        }


    }

    return;

}


extern "C" TESTDLLAPI int
TCAP_SS7PostNextEvent(TPOOL_THREAD *thr, ITS_EVENT *ev)
{
    int i;
    printf("Got EVENT from MTP2; source: %x\n", ev->src);
    for (i = 0; i < ev->len; i++)
    {
        printf("%02x ", ev->data[i]);

    }
    printf("\n");
    
    return (ITS_SUCCESS);
}


extern "C" TESTDLLAPI void
TCAP_ShowStats(void *arg)
{

    cout <<"**** TCAP_ShowStats Started..." << endl;
    while (true)
    {
        TIMERS_Sleep(1);
        if (showStat)
        {

            if (MUTEX_AcquireMutex(&statsGate) != ITS_SUCCESS)
            {
                printf("GetMsTimeStamp: failed to acquire mutex\n");

                continue;
             }




            printf("Total Transactions         : %d\n"
                   "Total Closed Transsactions : %d\n"
                   "Pending Transactions       : %d\n\n"
                   "Average Transaction time   : %d ms\n"
                   "Minimum Transaction time   : %d ms\n"
                   "Maximum Transaction time   : %d ms\n"
                   "===================================\n\n",
                   openTr, closedTr, openTr - closedTr,
                   averageTransactionTime,
                   minTransactionTime,
                   maxTransactionTime);

            MUTEX_ReleaseMutex(&statsGate);

        }


    }

}




extern "C" TESTDLLAPI void
MTP3Mgmt(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    ITS_EVENT *ev = (ITS_EVENT *)callData;
    ITS_OCTET mType;
    ITS_OCTET buf[255];
    ITS_USHORT len;

#if defined(TTC)
    MTP3_HEADER_TTC mtp3;

printf("\n\n\n\n\n\n\n\n\n\n\n\nMTP3 MANAGEMENT\n\n\n\n\n\n\n"); 
    MTP3_Decode_TTC(ev, &mType, &mtp3, buf, &len);

    switch (mType)
    {
    case MTP3_MSG_USER_DATA:
        printf("################### GOT USER DATA\n");
        break;

    case MTP3_MSG_PAUSE:
        printf("################### GOT PAUSE: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_TTC *)buf)->affected));
        sendTraffic = ITS_FALSE;
        break;

    case MTP3_MSG_RESUME:
        printf("################### GOT RESUME: pc %06x\n",
               MTP3_PC_GET_VALUE(((MTP3_PAUSE_RESUME_TTC *)buf)->affected));
        sendTraffic = ITS_TRUE;
        break;


    case MTP3_MSG_STATUS:
        printf("################### GOT STATUS: pc %06x cause %d cong %d\n",
               MTP3_PC_GET_VALUE(((MTP3_STATUS_TTC *)buf)->affected),
               ((MTP3_STATUS_TTC *)buf)->cause,
               ((MTP3_STATUS_TTC *)buf)->congLevel);
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
    ITS_INT res = 0;

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

            res = TCAP_Dialogue::Receive(ISS7_TTC_Stack, event, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            cout << endl << "Received TCAP dialogue..." << endl;

            currentDialogueID = recvDlg->GetDialogueID();

            cout << "Dialogue ID: <" << currentDialogueID << ">." << endl;

            switch (recvDlg->GetDialogueType())
            {
            case TCPPT_TC_BEGIN:
            {

                cout << "Begin dialogue." << endl;

                TCAP_Begin* recvBeginDlg =
                    static_cast<TCAP_Begin*>(recvDlg);

                tContext[currentDialogueID].beginReceived = ITS_TRUE;
                tContext[currentDialogueID].continueReceived = ITS_FALSE;

                openTr++;
 
                MUTEX_AcquireMutex(&statsGate); 

                tContext[currentDialogueID].timestamp = GetMsTimestamp();

                MUTEX_ReleaseMutex(&statsGate);

                break;
            }
            case TCPPT_TC_END:
            {
                cout << "End dialogue received" << endl;

                TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);
                closedTr++;
                tContext[currentDialogueID].beginReceived = ITS_FALSE;
                tContext[currentDialogueID].continueReceived = ITS_FALSE;
                 
                UpdateStats(currentDialogueID);

                break;
            }
            case TCPPT_TC_CONTINUE:
            {
                cout << "Receive Continue dialogue..." << endl;
                TCAP_Continue *recvContDlg =
                     static_cast<TCAP_Continue*>(recvDlg);

                 tContext[currentDialogueID].continueReceived = ITS_TRUE;
                break;
            } 
         

            default:
                cout << "This Dialogue is not handle yet... type: "
                     << recvDlg->GetDialogueType()  <<endl;
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

            res = TCAP_Component::Receive(ISS7_TTC_Stack, event, recvDlg, &recvCpt);
            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            //cout << endl << "Receive TCAP component..." << endl;

            switch (recvCpt->GetComponentType())
            {
            case TCPPT_TC_INVOKE:
            {
                //cout << "Invoke component: Id = " 
                //     << (int) recvCpt->GetInvokeID() << endl;

           printf("Got Invoke component: Id = %d\n", recvCpt->GetInvokeID());

                TCAP_Invoke* recvInvokeCpt =
                    static_cast<TCAP_Invoke*> (recvCpt);

                break;

            }
            case TCPPT_TC_RESULT_NL:
            {
                //cout << "Got Return Result Last component: Id = " 
                //     << (int) recvCpt->GetInvokeID() << endl;

           printf("Got RR-NL component: Id = %d\n", recvCpt->GetInvokeID());

                TCAP_Result* recvResultCpt =
                    static_cast<TCAP_Result*> (recvCpt);

                break;

            }
            case TCPPT_TC_RESULT_L:
            {
                //cout << "Got Return Result Last component: Id = " 
                //     << (int) recvCpt->GetInvokeID() << endl;

           printf("Got RR-L component: Id = %d\n", recvCpt->GetInvokeID());

                TCAP_Result* recvResultCpt =
                    static_cast<TCAP_Result*> (recvCpt);

                break;

            }
            case TCPPT_TC_L_CANCEL:
            {
                TCAP_Cancel *recvCancelCpt =
                    static_cast<TCAP_Cancel*> (recvCpt);

                currentDialogueID = recvCancelCpt->GetDialogueID();

                cout << "Got CANCEL component: did: " << currentDialogueID
                     << "InvkId: "<< (int) recvCpt->GetInvokeID() << endl;

                // Send Prearranged END to release the local dialogue Id
                TCAP_End endDlg;
                endDlg.SetDialogueID(currentDialogueID);
                endDlg.SetPreArrangedEnd(true);

                TCAP_Dialogue::Send(ISS7_TTC_Stack, &endDlg);

                break;
            }


            default:
                cout << "This Component is not handle yet... type: "
                     << recvCpt->GetComponentType()  << endl;
                break;
            }

        }

        if (tContext[currentDialogueID].beginReceived && recvCpt && recvCpt->GetLast() )
        {
            if (shortTr) /* short transaction: BEGIN-END */
            {
     
                TCAP_End endDlg;

                endDlg.SetDialogueID(currentDialogueID);

                TCAP_Result resultCpt(true);

                resultCpt.SetInvokeID(1);

                TCAP_Component::Send(ISS7_TTC_Stack, &endDlg, &resultCpt);

                TCAP_Dialogue::Send(ISS7_TTC_Stack, &endDlg);

                closedTr++;

                UpdateStats(currentDialogueID);

            }
            else /* Long Transaction BEGIN-CONTINUE-END */
            {
               //cout << " receive BEGIN... Sending Continue..." << endl;
               SendContinue();      
            }

            tContext[currentDialogueID].beginReceived = ITS_FALSE; 
            tContext[currentDialogueID].continueReceived = ITS_FALSE;

        }

        else if (tContext[currentDialogueID].continueReceived && recvCpt && recvCpt->GetLast() )
        {

            TCAP_End endDlg;

            endDlg.SetDialogueID(currentDialogueID);

            TCAP_Result resultCpt(true);

            resultCpt.SetInvokeID(2);

            TCAP_Component::Send(ISS7_TTC_Stack, &endDlg, &resultCpt);

            TCAP_Dialogue::Send(ISS7_TTC_Stack, &endDlg);

            //printf("***** Got CONTINUE: Application Sendind End Dialogue *****\n\n");

             closedTr++;

             UpdateStats(currentDialogueID);
         
             tContext[currentDialogueID].beginReceived = ITS_FALSE; 
             tContext[currentDialogueID].continueReceived = ITS_FALSE;

         }


        ITS_EVENT_TERM(&event.GetEvent());

    }

    return;
}

#if 0
extern "C" TESTDLLAPI void
TcapEventHandlerNode2(void *arg)
{
    ITS_UINT i;
    ITS_Event event ; 
    ITS_INT res = 0;
    ITS_BOOLEAN beginReceived = ITS_FALSE;
    ITS_BOOLEAN continue1Received = ITS_FALSE;
    ITS_BOOLEAN continue2Received = ITS_FALSE;

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

        if (DSM_GetNodeId() == 1) 
        {
            ITS_EVENT_TERM(&event.GetEvent());
            continue;
        }

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

            res = TCAP_Dialogue::Receive(ISS7_ANSI_Stack, event, &recvDlg);

            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            //cout << endl << "Received TCAP dialogue..." << endl;

            currentDialogueID = recvDlg->GetDialogueID();

            //cout << "Dialogue ID: <" << currentDialogueID << ">." << endl;


            switch (recvDlg->GetDialogueType())
            {
            case TCAP_PT_TC_BEGIN_ANSI:
            {

                //cout << "Begin dialogue." << endl;

                TCAP_Begin* recvBeginDlg =
                    static_cast<TCAP_Begin*>(recvDlg);

                beginReceived = ITS_TRUE;
                openTr++;

                break;
            }
            case TCAP_PT_TC_END_ANSI:
            {
                cout << "End dialogue received." << endl;

                TCAP_End* recvEndDlg = static_cast<TCAP_End*>(recvDlg);
                closedTr++;

                break;
            }
            case TCAP_PT_TC_CONTINUE_ANSI:
            {
                cout << "Receive Continue dialogue..." << endl;
                TCAP_Continue *recvContDlg =
                     static_cast<TCAP_Continue*>(recvDlg);

                 continue1Received = ITS_TRUE;
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

            res = TCAP_Component::Receive(ISS7_ANSI_Stack, event, recvDlg, &recvCpt);
            if (res != ITS_SUCCESS)
            {
                throw ITS_Error(res, __FILE__, __LINE__); // Fatal error.
            }

            //cout << endl << "Receive TCAP component..." << endl;

            switch (recvCpt->GetComponentType())
            {
            case TCAP_PT_TC_INVOKE_ANSI:
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
     
#if 0  
            TCAP_End endDlg;

            endDlg.SetDialogueID(currentDialogueID);

            TCAP_Dialogue::Send(ISS7_ANSI_Stack, &endDlg);

            //printf("***** Application Sendind End Dialogue *****\n\n");

#endif
           //cout << " receive BEGIN... Sending Continue..." << endl;
           SendContinue();      
           beginReceived = ITS_FALSE; 

        }

        ITS_EVENT_TERM(&event.GetEvent());

    }

    return;
}

#endif

void
TestCases(DBC_Server *dbc, const char *cmdLine)
{    
    char buf[ITS_PATH_MAX];
    int linkSet, linkCode, ret;

    ITS_C_ASSERT(dbc != NULL);

#if defined(TTC)
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

        printf("*********** Deactivating link ************\n");
        MGMT_Main_CCITT(MTP3_USER,
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
        MGMT_Main_CCITT(MTP3_USER,
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
        MGMT_Main_CCITT(MTP3_USER,
                       MGMT_TRIGGER_ACTIVATE_LINK,
                       NULL, 0,
                       (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);
        printf("****** Returned from the MGMT Activate Link 1 ******\n");
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
#endif
    else if (DBC_Cmd(dbc, "sendB", "Send Begin", "<>", "<>"))
    {
        printf("**** Sending Begin ****");
        SendBegin();
        openTr++;
        printf("**** Begin Sent ***");

    }
    else if (DBC_Cmd(dbc, "startt", "start traffic ", "<>", "<>"))
    {
        printf("**** Starting Traffic Begin ****");
        sendTraffic = ITS_TRUE; 
        startTime = TIMERS_Time();

    }
    else if (DBC_Cmd(dbc, "showstat", "start traffic ", "<>", "<>"))
    {
        printf("**** show statistics ****");
        showStat = ITS_TRUE; 

    }
    else if (DBC_Cmd(dbc, "stopstat", "stop traffic ", "<>", "<>"))
    {
        printf("**** show statistics ****");
        showStat = ITS_FALSE; 

    }
    else if (DBC_Cmd(dbc, "clear", "clear statistics ", "<>", "<>"))
    {
        openTr=0, closedTr=0;
        averageTransactionTime = 0;
        minTransactionTime    = 5000;
        maxTransactionTime    = 0;



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
    if (DBC_Cmd(dbc, "range", "Set Number of Transactions per stats", 
                     "<#num>", "<num>"
))
    {
        ret = sscanf(cmdLine, "%s %d ", buf, &numberOfTransactionPerStatictic);
        if (ret != 2)
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
#if 0
    else if (DBC_Cmd(dbc, "status_link", "get Link Status", "<ls>", "<lc>"))
    {
        char *dump = NULL;

        ret = sscanf(cmdLine, "%s %s %d %d", buf, &linkSet, &linkCode);
        
        ROUTE_LockTable();

        LINK_DumpLinkInfo(&dump, (ITS_OCTET)linkSet, (ITS_OCTET)linkCode);

        ROUTE_UnlockTable();

        if (dump)
        {
            DBC_AppendText(dbc, dump);
        }

    }
#endif
    else if (DBC_Cmd(dbc, "addRoute", "add a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT pointCode;
        ITS_UINT sio;
        ITS_UINT linkSet;

        memset(&rinfo, 0, sizeof(rinfo));

        /* addRoute dirrection style paremeters */
  
        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]", buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Adding a Route *************\n");
        DBC_AppendText(dbc, buf);

        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n" 
               "         linkSet:    %d \n"
               "         style:      %s \n" 
               "         parameters: %s \n", 
               direction, family, linkSet, style, parameters);
   
        DBC_AppendText(dbc, buf);

        /*** process direction ***/

        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else
        {
            printf("Error: direction must be remoteRoute or localRoute\n");
            return;
        }

       /*** process family ***/

       if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU; 
       }
       else if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI; 
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA; 
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN; 
       }
       else
       {
           printf("Error invalid family...\n");
       }
   

       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI; 
           
            sscanf(parameters,"%d %d", &pointCode, &sio);
            rinfo.basic.dpc = pointCode;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
        }
        else
        {
            printf("Error: Invalid routing style\n");
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0; 
        rinfo.priority = 0; 
        rinfo.sls  = 0; 
        rinfo.rkey = 0; 
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

        if (ROUTE_AddRouteContextInfo(&rinfo) != ITS_SUCCESS)
        {
            printf("Error: Route cannot be added\n");
        }

    }
    else if (DBC_Cmd(dbc, "delRoute", "delete a Route", "", ""))
    {
        char direction[20];
        char style[20];
        char family[10];
        char parameters[50];
        ROUTE_MatchInfo rinfo;
        ITS_UINT pointCode;
        ITS_UINT sio;
        ITS_UINT linkSet;

        /* addRoute dirrection style paremeters */
  
        ret = sscanf(cmdLine, "%s %s %s %d %s %[^\n]", buf, direction, family, &linkSet, style, parameters);

        sprintf(buf, "*********** Deleting a Route *************\n");
        DBC_AppendText(dbc, buf);

        sprintf(buf, "         direction:  %s \n"
               "         family:     %s \n" 
               "         linkSet:    %d \n"
               "         style:      %s \n" 
               "         parameters: %s \n", 
               direction, family, linkSet, style, parameters);
   
        DBC_AppendText(dbc, buf);

        /*** process direction ***/

        if (strcmp(direction, ROUTE_TYPE_LOCAL_STRING) == 0)
        {
            rinfo.basic.type = LOCAL_ROUTE;
        }
        else if (strcmp(direction, ROUTE_TYPE_REMOTE_STRING) == 0)
        {
            rinfo.basic.type = REMOTE_ROUTE;
        }
        else
        {
            printf("Error: direction must be remoteRoute or localRoute\n");
            return;
        }

       /*** process family ***/

       if (strcmp(family, FAMILY_CCITT_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ITU; 
       }
       else if (strcmp(family, FAMILY_ANSI_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_ANSI; 
       }
       else if (strcmp(family, FAMILY_CHINA_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_CHINA; 
       }
       else if (strcmp(family, FAMILY_JAPAN_STRING) == 0)
       {
           rinfo.basic.family = FAMILY_JAPAN; 
       }
       else
       {
           printf("Error invalid family...\n");
       }
   

       /*** process route style ****/

        if (strcmp(style, ROUTE_STYLE_DPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_NI; 
           
            sscanf(parameters,"%d %d", &pointCode, &sio);
            rinfo.basic.dpc = pointCode;
            rinfo.basic.criteria.sio = (ITS_OCTET)sio & ROUTE_NI_MASK;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_NI_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_NI; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO; 
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_SSN_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_SSN_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_SSN_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_SIO_CIC_RANGE;
        }
        else if (strcmp(style, ROUTE_STYLE_DPC_OPC_SIO_CIC_RANGE_STRING) == 0)
        {
            rinfo.basic.style = ROUTE_DPC_OPC_SIO_CIC_RANGE;
        }
        else
        {
            printf("Error: Invalid routing style\n");
        }

        rinfo.linkSet = (ITS_OCTET) linkSet;
        rinfo.linkCode = 0; 
        rinfo.priority = 0; 
        rinfo.sls  = 0; 
        rinfo.rkey = 0; 
        rinfo.basic.mask = ITS_SS7_DEFAULT_ROUTE_MASK;

        if (ROUTE_DeleteRouteContextInfo(&rinfo) != ITS_SUCCESS)
        {
            printf("Error: Route cannot be added\n");
        }
    }
#if 0
    else if (DBC_Cmd(dbc, "DebugTrace", "Debug Trace", "<on, off>", "<>"))
    {    
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_DEBUG_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_DEBUG_STRING, ITS_FALSE);
        }
    }        
    else if (DBC_Cmd(dbc, "WarningTrace", "Warning Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_WARNING_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_WARNING_STRING, ITS_FALSE);
        }
    }       
    else if (DBC_Cmd(dbc, "ErrorTrace", "Error Trace", "<on, off>", "<>"))
    {
        char onOff[10];

        ret = sscanf(cmdLine, "%s %s ",buf, onOff);

        if (strstr(onOff, "on") != NULL)
        {

            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_TRUE);


            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_TRUE);

        }
        else
        {
            TRACE_SetOutputOnOffByName(MTP3_CCITT_TraceData,
                                       MTP3_ERROR_STRING,
                                       MTP3_STDOUT_STRING, ITS_FALSE);

            TRACE_SetLevelOnOffByName(MTP3_CCITT_TraceData,
                                      MTP3_ERROR_STRING, ITS_FALSE);
        }
    }      
#endif
    else if (DBC_Cmd(dbc, "shutdown", "shutdown this node", "<>", "<>"))
    {
        ShutDownNode();
        TIMERS_Sleep(5);

        isShuttingDown = ITS_TRUE;

        ENGINE_Terminate();

#if 0
        TRANSPORT_Manager *tm;
        TRANSPORT_Control *tr;
        ITS_UINT mask;
        char dump[100];

        tm = TRANSPORT_GetManager();

        if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
        {
             return;
        }

        for ( tr = tm->listHead;
              tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
        {
            mask = TRANSPORT_MASK(tr);
            printf("Transport %d found\n", TRANSPORT_INSTANCE(tr));
        
            if ((mask & ITS_MTP2_ANSI) == ITS_MTP2_ANSI)
            {
                SS7_LinkPtr lp;

                printf("Transport %d has MTP2 MASK\n", TRANSPORT_INSTANCE(tr));

                for (lp = TRANSPORT_SS7_INFO(tr).linkInfo; 
                     lp != NULL; lp = lp->next)               
                {
                   printf("Deactivating ls:%d lc:%d\n", 
                           lp->linkSet->linkSet, lp->linkCode);
                   DBC_AppendText(dbc, dump); 
                   MGMT_Main_ANSI(MTP3_USER,
                                   MGMT_TRIGGER_DEACTIVATE_LINK,
                                   NULL, 0,
                                   lp->linkSet->linkSet, lp->linkCode);
                }

            }
        }

        RWLOCK_UnlockShared(&tm->transportGate);

        TIMERS_Sleep(8);
 
        isShuttingDown = ITS_TRUE;

        ENGINE_Terminate();
#endif

    }

}

void static
ShutDownNode()
{
    TRANSPORT_Manager *tm;
    TRANSPORT_Control *tr;
    ITS_UINT mask;
    char dump[100];

    tm = TRANSPORT_GetManager();

    if (RWLOCK_LockShared(&tm->transportGate) != ITS_SUCCESS)
    {
         return;
    }

    for ( tr = tm->listHead;
          tr != NULL; tr = TRANSPORT_HMI_NEXT(tr))
    {
        mask = TRANSPORT_MASK(tr);
        printf("Transport %d found\n", TRANSPORT_INSTANCE(tr));

        if ((mask & ITS_MTP2_TTC) == ITS_MTP2_TTC)
        {
            SS7_LinkPtr lp;

            printf("Transport %d has MTP2 MASK\n", TRANSPORT_INSTANCE(tr));

            for (lp = TRANSPORT_SS7_INFO(tr).linkInfo;
                 lp != NULL; lp = lp->next)
            {
               printf("Deactivating ls:%d lc:%d\n",
                       lp->linkSet->linkSet, lp->linkCode);
/*               DBC_AppendText(dbc, dump);*/
               MGMT_Main_CCITT(MTP3_USER,
                               MGMT_TRIGGER_DEACTIVATE_LINK,
                               NULL, 0,
                               lp->linkSet->linkSet, lp->linkCode);
            }

        }
    }

    RWLOCK_UnlockShared(&tm->transportGate);


}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *
 *  Input Parameters:
 *      object      - see DSM API.
 *      userData    - see DSM API.
 *      callData    - see DSM API.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
extern "C" TESTDLLAPI void
ApplicationMembershipChangeCb(
    ITS_POINTER object,
    ITS_POINTER userData,
    ITS_POINTER callData)
{
    DSM_MembershipChangeCbData*
        membershipChangeCbData =
            (DSM_MembershipChangeCbData*)callData;


    ITS_USHORT concernedNodeId = membershipChangeCbData->memberNodeId;


    /* Two nodes system only. */
    /*if (membershipChangeCbData->memberNodeId != DSM_GetNodeId())*/
    {
        if (membershipChangeCbData->
                membershipChangeType ==
                    DSM_FT_GROUP_MEMBER_LEAVE)
        {
            printf("DSM_FT_GROUP_MEMBER_LEAVE: Setting peerActive to "
                   "ITS_FALSE\n");

            ROUTE_SetApplicationSelector(ApplicationSelector);

        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_JOIN)
        {

            printf("DSM_FT_GROUP_MEMBER_JOIN: Setting peerActive "
                   "to ITS_TRUE\n");

            if (DSM_GetNodeId() == 1)
            {
                ROUTE_SetApplicationSelector(ApplicationSelector); 
            }
            else
            {
 
                ROUTE_SetApplicationSelector(ApplicationSelector); 
            }


        }
        else if (membershipChangeCbData->
                     membershipChangeType ==
                        DSM_FT_GROUP_MEMBER_ALIVE)
        {

            printf("DSM_FT_GROUP_MEMBER_ALIVE: Setting peerActive "
                   "to ITS_TRUE");


        }

        else
        {
            /* Ignore. */
        }
    }
}

#if 0
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

#endif
