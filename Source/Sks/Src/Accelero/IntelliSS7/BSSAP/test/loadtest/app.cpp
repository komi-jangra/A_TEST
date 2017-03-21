#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <sys/timeb.h>
#include <string>
#include <map>

#include <its.h>
#include <its++.h>
#include <engine++.h>
#include <its_thread_pool.h>
#include <its_work_item.h>
#include <its_mutex.h>

#include <itu/sccp.h>
#include <sccp++.h>

#include <BSSAP++.h>
#include <BSSAPPrint.h>


ITS_HDR srchdr, remhdr;
#define VALID_CHOICE(x)     ( x >= 1 && x <= 4 || x == 99 )
#define MAX_RK_NUM    5
#define BUILD_DATA    2
#define CONNECT    1
#define SEND_UDT       5
#define TEST_EXIT    99

#define SEND_DT1      1

#define SEND_DT1_AssignReq      11
#define SEND_DT1_AssignCmplt    12
#define SEND_DT1_AssignFail     13

#define SEND_DT1_HORequired     14
#define SEND_DT1_HOCommand      15
#define SEND_DT1_HORequiredRej  16
#define SEND_DT1_HORequest      17
#define SEND_DT1_HORequestAck   18
#define SEND_DT1_HOFailure      19

#define SEND_DT1_ClearCommand   20 
#define SEND_DT1_ClearCmplt     21 
#define SEND_DT1_Alerting       22
#define SEND_DT1_CallConfirm    23
#define SEND_DT1_Connect        24
#define SEND_DT1_ConnectAck     25
#define SEND_DT1_EmergencySetup 26   
#define SEND_DT1_Progress       27
#define SEND_DT1_CCEstablish    28
#define SEND_DT1_Setup          29
#define SEND_DT1_Modify         30
#define SEND_DT1_ModifyComplete 31
#define SEND_DT1_ModifyReject   32
#define SEND_DT1_CallProceeding 33
#define SEND_DT1_Paging         34
#define SEND_DT1_CipherModeCommand 35
#define SEND_DT1_CipherModeComplete   36
#define SEND_DT1_CompleteLayer3Information 37

    





#define SEND_DT2     2
#define DISCONNECT   3
//
// local subsystem for testing
//
#define LOCAL_SSN   2
#define REMOTE_SSN  2
#define LOCAL_PC    2
#define REMOTE_PC   4114
#define ISG_PC      2057

//
// address indicator
//
#define ADDR_IND    (SCCP_CPA_ROUTE_NAT|SCCP_CPA_ROUTE_SSN|\
                     SCCP_CPA_HAS_PC|SCCP_CPA_HAS_SSN)
#define IMPORT
#define EXPORT

//
using namespace std;
using namespace its;
using namespace engine;


extern "C"
{

void BuildAssigmentRequest(ITS_OCTET *databuf, int *datalen);
void BuildAssigmentComplete(ITS_OCTET *databuf, int *datalen);
void BuildAssigmentFailure(ITS_OCTET *databuf, int *datalen);
void BuildHandoverRequest(ITS_OCTET *databuf, int *datalen);
void BuildHandoverRequestAck(ITS_OCTET *databuf, int *datalen);
void BuildHandoverRequired(ITS_OCTET *databuf, int *datalen);
void BuildHandoverRequiredReject(ITS_OCTET *databuf, int *datalen);
void BuildHandoverCommand(ITS_OCTET *databuf, int *datalen);
void BuildHandoverFailure(ITS_OCTET *databuf, int *datalen);
void BuildClearCommand(ITS_OCTET *databuf, int *datalen);
void BuildClearComplete(ITS_OCTET *databuf, int *datalen);
void BuildAlerting(ITS_OCTET *databuf, int *datalen);
void BuildCCConfirm(ITS_OCTET *databuf, int *datalen);
void BuildCallProceeding(ITS_OCTET *databuf, int *datalen);
void BuildConnect(ITS_OCTET *databuf, int *datalen);
void BuildConnectAck(ITS_OCTET *databuf, int *datalen);
void BuildEmergencySetup(ITS_OCTET *databuf, int *datalen);
void BuildModify(ITS_OCTET *databuf, int *datalen);
void BuildModifyComplete(ITS_OCTET *databuf, int *datalen);
void BuildModifyReject(ITS_OCTET *databuf, int *datalen);
void BuildProgress(ITS_OCTET *databuf, int *datalen);
void BuildCCEstablish(ITS_OCTET *databuf, int *datalen);
void BuildSetup(ITS_OCTET *databuf, int *datalen);
void BuildPaging(ITS_OCTET *databuf, int *datalen);
void BuildCompleteLayer3Info(ITS_OCTET *databuf, int *datalen);
void BuildCipherModeComplete(ITS_OCTET *databuf, int *datalen);
void BuildCipherModeCommand(ITS_OCTET *databuf, int *datalen);



void PrintData(SCCP_UserData *ud);


int
TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle, ITS_USHORT instance);
int
TEST_WaitForEvent(ITS_HANDLE handle, ITS_USHORT instance);

int
TEST_BuildAndSendMsg(unsigned char msgType, ITS_OCTET bssapMsgtype,
                     ITS_HANDLE handle, ITS_USHORT instance, ITS_OCTET transparency);
static int 
TEST_PrintCommand();
void
SccpThreadFunction(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle);
void
ReceiveThread(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle);
ITS_USHORT recvInstance;


void RouteAPP()
{
}

EXPORT ITS_ResourceManager *rf = NULL;

void MyPreFunc()
{
  ThreadPoolEntry thr;
  engine::Worker *eng;

  cout << "Inside MyPreFunc " << endl;
  workerPool->GetFirstAvailThread(thr);
  eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
  workerPool->DispatchOnThread(thr, ReceiveThread,
                            (void *)NULL);
  workerPool->GetFirstAvailThread(thr);
  eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
  workerPool->DispatchOnThread(thr, SccpThreadFunction,
                            (void *)NULL);
}

void MyPostFunc()
{
}

void
ReceiveThread(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
{
    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    ITS_USHORT instance = worker->GetInstance();
    ITS_USHORT mask = worker->GetMask();

    handle = ITS_Initialize(mask, instance);

    recvInstance = instance;

    for(;;)
    {
        TEST_WaitForEvent(handle, instance);
    }

}

void
SccpThreadFunction(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
{
    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    ITS_USHORT instance = worker->GetInstance();
    int ret;
    ITS_USHORT mask = worker->GetMask();

    handle = ITS_Initialize(mask, instance);


    ret = SCCP_SendUserInService(handle, LOCAL_PC, LOCAL_SSN);
    if (ret != ITS_SUCCESS)
    {
       cout << "Error Sendin UIS" <<  endl;
       return ;
     }
     int cmdInput = 0;
     int i;

     printf(" ENTER NUMBER OF CONNECTIONS TO ESTABLISH ->");
     fflush(stdout);
     cin >> cmdInput;

     for (i = 0; i < cmdInput; i++)
     {
         TEST_ExecuteCommand(1, handle, instance); 
         sleep(1);
     }

     sleep(10000);

}
///////////////////////////////////////////////////////////////////////////////
//
// Display Menu for the ASP
//
//////////////////////////////////////////////////////////////////////////////

static int 
TEST_PrintCommand()
{
    cout << "\n\n\t**** IntelliNet Technologies, Inc. ****\n";
    cout << "\t\tASP Simulator Program\n\n";

    cout <<"Choose one from the following list, \n";
    cout << "\tPlease enter the corresponding number:-\n\n";

    printf("      %d)  Establish Connection  \n", CONNECT);
    /*printf("      %d)  Send UDT  \n", SEND_UDT);*/
    printf("      %d) Quit program.\n", TEST_EXIT);

    printf("\n  -> ");

    return 1;
}


////////////////////////////////////////////////////////////////////////
//
//  o Send connection Request
// 
//  o Send DT1 or RLSD (for Class 2)
//
///////////////////////////////////////////////////////////////////////

int
TEST_BuildAndSendMsg(unsigned char msgType, ITS_OCTET bssapMsgType, 
                     ITS_HANDLE handle, ITS_USHORT instance, ITS_OCTET transparency)
{
    ITS_SCCP_IE sccpIES[7];
    int ret = ITS_SUCCESS, i;
	
    switch (msgType)
    {
    case SCCP_MSG_CR: 
    {
        srchdr.type = ITS_SCCP;
        int ret = SCCP_GetNextLocalRef(&srchdr.context.conref);
        ROUTE_AddApplication(recvInstance, &srchdr);
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        cout<<"Using Local Reference (SLR) ("<<srchdr.context.conref<<") "<<"For Establishing Connection"<<endl;

        SCCP_ConnectionRequest cr;

        SCCP_SourceLocalRef slr(srchdr.context.conref);
        cr.AddIE(&slr);

        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
        cr.AddIE(&pc);

        /* Called Party Address */
        //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(REMOTE_PC);          //octet 3 - any
        called_pa.SetSSN(REMOTE_SSN);               //octet 2 - 0000 0001
        called_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        called_pa.SetInternationalRouting(true);   //octet 1 bit 8
        cr.AddIE(&called_pa);

        /* Calling Party Address */
        //len=3 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(LOCAL_PC);           //octet 3 - any
        calling_pa.SetSSN(LOCAL_SSN);                //octet 2 - 0000 0001
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(true);   //octet 1 bit 8
        cr.AddIE(&calling_pa);
        cr.SetDPC(ISG_PC);

        /* Data */
        SCCP_UserData ud;
        int len = 10;
        ITS_OCTET data[10];
        //fill data
        for(ITS_OCTET i = 0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        cr.AddIE(&ud);

        /* SCC hop Counter  */           //len=3
        SCCP_HopCount hc(10);
        cr.AddIE(&hc);

        ret = SCCP_MessageClass::Send(handle, &srchdr, &cr);
        
        if (ret != ITS_SUCCESS)
        {
            printf("Error Sending SCCP_MSG_CR to Stack !! %d\n", ret);
        }
        else
        {
            cout<<"Successfully sending CR"<<endl;
        }
        break;
    }

    case SCCP_MSG_RLSD:
    { 
        SCCP_Released rm;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(remhdr.context.conref);
        rm.AddIE(&dlr);

        /* Source Local Reference */
        SCCP_SourceLocalRef slr(srchdr.context.conref);
        rm.AddIE(&slr);

        /* Released Cause */
        SCCP_ReleaseCause rc(SCCP_RLC_END_USER_ORG);
        rm.AddIE(&rc);

        // Data
        SCCP_UserData ud;
        int len = 10;                              //len=3-130
        ITS_OCTET data[10];
        // fill data
        for(ITS_OCTET i=0;i<len;i++)
        {
            data[i] = i;
        }
        ud.SetUserData(data, len);
        rm.AddIE(&ud);

        /* Send the message  */
        ret = SCCP_MessageClass::Send(handle, &srchdr, &rm);
        if (ret != ITS_SUCCESS)
        {
            printf("Error Sending SCCP_MSG_RLSD to Stack !! %d\n",
                                                               ret);
        }
        else
        {
             cout<<"Successfully sending RLSD"<<endl;
        }
        break;
    }

    case SCCP_MSG_DT1:
    {
        ITS_UINT pc;
        ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
        ITS_USHORT gttLen = 0;
        SCCP_ADDR cdp;

        /* create a message */
        SCCP_DataForm1 df1;

        /* Destination Local Reference */
        SCCP_DestinationLocalRef dlr(remhdr.context.conref);
        df1.AddIE(&dlr);

        /* segmenting/reassembling */
        SCCP_SegmentReassem sr(1); //more data
        /*  implementation can be changed to:
        SCCP_SegmentReassem sr();
        sr.SetSegmentReassem(0);    //0 means no data */
        df1.AddIE(&sr);

        SCCP_UserData ud;
        ITS_OCTET data[5666];
        int len;
        
        if (transparency == 1)
        {
            switch (bssapMsgType)
            {
            case BSSAP_CC_MSG_ALERTING:
                BuildAlerting(data, &len);
                break;

            case BSSAP_CC_MSG_CALL_CONFIRMED:
                BuildCCConfirm(data, &len);
                break;

            case BSSAP_CC_MSG_CONNECT:
                BuildConnect(data, &len);
                break;

            case BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE:
                BuildConnectAck(data, &len);
                break;

            case BSSAP_CC_MSG_EMERGENCY_SETUP:
                BuildEmergencySetup(data, &len);
                break;

            case BSSAP_CC_MSG_PROGRESS:
                BuildProgress(data, &len);
                break;

            case BSSAP_CC_ESTABLISHMENT:
                BuildCCEstablish(data, &len);
                break;

            case BSSAP_CC_MSG_SETUP:
                BuildSetup(data, &len);
                break;

            case BSSAP_CC_MSG_MODIFY:
                BuildModify(data, &len);
                break;
 
            case BSSAP_CC_MSG_MODIFY_COMPLETE:
                BuildModifyComplete(data, &len);
                break;

            case BSSAP_CC_MSG_MODIFY_REJECT:
                BuildModifyReject(data, &len);
                break;

            case BSSAP_CC_MSG_CALL_PROCEEDING:
                BuildCallProceeding(data, &len);
                break;
            default:
                break;
            }
        }
        else
        {
            switch (bssapMsgType)
            {
            case BSSAP_MSG_ASSIGN_REQUEST:
                BuildAssigmentRequest(data, &len);
                break;

            case BSSAP_MSG_ASSIGN_COMPLETE:
                BuildAssigmentComplete(data, &len);
                break;

            case BSSAP_MSG_ASSIGN_FAILURE:
                BuildAssigmentFailure(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_REQUEST:
                BuildHandoverRequest(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_REQUIRED:
                BuildHandoverRequired(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_REQUEST_ACK:
                BuildHandoverRequestAck(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_COMMAND:
                BuildHandoverCommand(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_FAILURE:
                BuildHandoverFailure(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_REQUIRED_REJECT:
                BuildHandoverRequiredReject(data, &len);
                break;
 
            case BSSAP_MSG_CLEAR_COMMAND:
                BuildClearCommand(data, &len);
                break;

            case BSSAP_MSG_CLEAR_COMPLETE:
                BuildClearComplete(data, &len);
                break;


            case BSSAP_MSG_PAGING:
                BuildPaging(data, &len);
                break;
 
            case BSSAP_MSG_COMPLETE_LAYER3_INFO:
                BuildCompleteLayer3Info(data, &len);
                break;

            case BSSAP_MSG_CIPHER_MODE_CMD:
                BuildCipherModeCommand(data, &len);
                break;

            case BSSAP_MSG_CIPHER_MODE_COMPLETE:
                BuildCipherModeComplete(data, &len);
                break;

            default:
                break;
            }
        }

        if(len > 0)
        {
            for (i = 0; i < len; i++)
            {
                printf("%02x ",data[i]);
                if (!((i+1) % 20))
                {
                    cout << endl;
                }
            }
            if (((i+1) % 20))
            {
                cout << endl;
            }
        }


        ud.SetUserData(data, len);
        df1.AddIE(&ud);

        //PrintData(&ud);

        ret = SCCP_MessageClass::Send(handle, &srchdr, &df1);
        if(ret != ITS_SUCCESS)
        {
            cout<<"Errors in sending DT1 "<<endl;
        }
        else
        {
            cout<<"Successfully sending DT1 "<<endl;
        }

        break;
    }
    case SCCP_MSG_DT2: //This is for CLASS_3 protocol class. 
    { 
        ITS_UINT pc;
        ITS_OCTET ssn = SCCP_SSN_NONE, addrInd = 0, gttInfo[32];
        ITS_USHORT gttLen = 0;
        SCCP_ADDR cdp;

        /* create a message */
        SCCP_DataForm2 df2;

        SCCP_DestinationLocalRef dlr(remhdr.context.conref);
        df2.AddIE(&dlr);

       /* Sequencing/segmenting */
        SCCP_SequenceSegment ss(1,2,1); // tsn=1, rsn=2, haveMore=1
        df2.AddIE(&ss);

        SCCP_UserData ud;
        ITS_OCTET data[150];
        int len = 5;
        /*fill data */
        data[0] = 11;
        data[1] = 12;
        data[2] = 13;
        data[3] = 14;
        data[4] = 15;
        ud.SetUserData(data, len);
        df2.AddIE(&ud);

        /* Send the message  */
        ret = SCCP_MessageClass::Send(handle, &srchdr, &df2);
        if(ret != ITS_SUCCESS)
        {
            cout<<"Error in sending DT2 "<<endl;
        }
        else
        {
            cout<<"Successfully sending DT2 "<<endl;
        }
        break;
    }

    case SCCP_MSG_UDT:
        SCCP_UnitData udt;

        SCCP_ProtocolClass pc(SCCP_PCLASS_1 | SCCP_PCLASS_RET_ON_ERR);
        udt.AddIE(&pc);

        /* Called Party Address */
        //len=3 min
        SCCP_CalledPartyAddr called_pa;
        called_pa.SetPointCode(REMOTE_PC);          //octet 3 - any
        called_pa.SetSSN(REMOTE_SSN);               //octet 2 - 0000 0001
        called_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        called_pa.SetInternationalRouting(false);   //octet 1 bit 8
        udt.AddIE(&called_pa);

        /* Calling Party Address */
        //len=3 min
        SCCP_CallingPartyAddr calling_pa;
        calling_pa.SetPointCode(LOCAL_PC);           //octet 3 - any
        calling_pa.SetSSN(LOCAL_SSN);                //octet 2 - 0000 0001
        calling_pa.SetRouteByPCSSN(true);            //octet 1 bit 7
        calling_pa.SetInternationalRouting(false);   //octet 1 bit 8
        udt.AddIE(&calling_pa);

        /* Data */
        SCCP_UserData ud;
        int len = 38;
        ITS_OCTET data[4500];
        //fill data
        for(int i=0;i<len;i++)
        {
            data[i] = 0x62;
        }
        ud.SetUserData(data, len);
        udt.AddIE(&ud);

        /* SCC hop Counter  */           //len=3
        SCCP_HopCount hc(10);
        udt.AddIE(&hc);
        
        ret = SCCP_MessageClass::Send(handle, &srchdr, &udt);
        
        if (ret != ITS_SUCCESS)
        {
            printf("Error Sending SCCP_MSG_UDT to Stack !! %d\n",
                                                           ret);
        }
        else
        {
            cout<<"Successfully sending DATA"<<endl;
        }

    break;
    defualt:
        printf("error bad MSG \n");
    }

      //char choice;
       // cout << "DO YOU WANT TO WAIT FOR EVENT ->(y/n)";

        // cin >> choice;
      //  if (choice == 'y')
       // {
	//    TEST_WaitForEvent(handle, instance);
      //  }

    return ret;
}


////////////////////////////////////////////////////////////////////////
//
//  Receive loop:
//  
//  o   Receive SCCP messages 
//
//  o   Exit loop.
///////////////////////////////////////////////////////////////////////

int
TEST_WaitForEvent(ITS_HANDLE handle, ITS_USHORT instance)
{

    int ret = ITS_SUCCESS, i;
    ITS_Event event;
    const ITS_OCTET *data;
    SCCP_MessageClass *msg;
    ITS_HDR recvHdr;

    printf("Waiting for Event \n");
    int res = ITS_GetNextEvent(handle, &event.GetEvent());

    if (res != ITS_SUCCESS)
    {
       ITS_Error itsError(res, __FILE__, __LINE__);

       cout << endl << itsError.GetDescription() << endl;
    }

    data = event.GetData();
    cout<<endl<<"-----------------------------------------------------"<<endl;
    cout << "Received Event..." <<endl;

    printf("*---> Dump Event <---*\n");

    for(i=0; i < event.GetLength(); i++)
    {
	printf("%02x ", data[i]);

    }
    printf("\n");
  
   // Process Received Message

    ret = SCCP_MessageClass::Receive(handle, &recvHdr, event, &msg);

    switch (msg->GetMsgType())
    {
        case SCCP_MSG_CR:
        {  
            cout<<"Received Connection Request.... "<<endl;

	    /***** Sending Connection Confirm in response to CR *****/ 
	   srchdr = recvHdr;
           ROUTE_AddApplication(recvInstance, &srchdr);
	   SCCP_SourceLocalRef *tmp = 
           (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
	    remhdr.context.conref = tmp->GetRefNum();

	    SCCP_ConnectionConfirm cc;

	    /* Destination Local Reference */

	    SCCP_DestinationLocalRef dlr(remhdr.context.conref);
	    cc.AddIE(&dlr);

	    /* Source Local Reference */
	    SCCP_SourceLocalRef slr(srchdr.context.conref);
	    cc.AddIE(&slr);

	    /* Protocol Class */
	    SCCP_ProtocolClass pc(SCCP_PCLASS_2);
	    cc.AddIE(&pc);

	    /* Credit */                            //len=3
	    SCCP_Credit credit;
	    credit.SetCredit(20);
	    cc.AddIE(&credit);
        
	    /* Called Party Address*/               //len=4 min
	    SCCP_CalledPartyAddr called_pa;
	    called_pa.SetPointCode(REMOTE_PC);       //octet 3 - any
	    called_pa.SetSSN(REMOTE_SSN);            //octet 2 - 0000 0001
	    called_pa.SetRouteByPCSSN(true);          //octet 1 bit 7
	    called_pa.SetInternationalRouting(false);   //octet 1 bit 8 
	    cc.AddIE(&called_pa);

            // Data                                     //len=3-130
            SCCP_UserData ud;
            int len = 10;
            ITS_OCTET data[10];
            //fill data
            for(ITS_OCTET i=0;i<len;i++)
            {
     	        data[i] = i;
	    }
	    ud.SetUserData(data, len);
	    cc.AddIE(&ud);
        
	    ret = SCCP_MessageClass::Send(handle, &srchdr, &cc);
	    if (ret != ITS_SUCCESS)
	    {
		cout << "Error while sending CC: " << ret << endl;
	    }
            else
            {
               cout<<"Sending Connection Confirm ..."<<endl;
            }
	    break;
        }
       case SCCP_MSG_CC:	//Connection Confirm
       {
	   SCCP_SourceLocalRef *slr = 
		(SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
	   remhdr.context.conref = slr->GetRefNum();

           cout<<"Recieved Connection Confirm Message DLR No:"
                                        << remhdr.context.conref<<endl;
             TEST_ExecuteCommand(BUILD_DATA, handle, instance); 
	   break;
       }
       case SCCP_MSG_AK:	// Data ACK
       {
           printf("Received ACK message for DT2\n");
           break;
       }
       case SCCP_MSG_RLC:	// Release Confirm
       {
           printf("Received RLC Message\n ");
          
           printf("\n   ---Successfully completed release operation---- \n");
          
           printf("\n To continue press (y), else (n) to exit\n\n\n");
           char z;
           cin>>z;
           if(z == 'y')
           {
               break;
           }
           else
           {
               printf("EXITING FROM PROGRAM\n");
               exit(0);
           }
       }
       case SCCP_MSG_DT1:
       { 
           cout <<" Received DT1.... " << endl;
            SCCP_UserData *ud = (SCCP_UserData *)msg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);

           break;
       }
       default:
           break;
    }
    return ret;
}



///////////////////////////////////////////////////////////////////////////
//
// TEST_ExecuteCommand
//
/////////////////////////////////////////////////////////////////////////// 
int
TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle, ITS_USHORT instance)
{
    int ret = ITS_SUCCESS;
    ITS_EVENT evt;
    int msgType = 1;
    ITS_OCTET bssapMsgType = 0xFFU;
    bool submenu = true;
    ITS_OCTET transparency = 0;

    evt.src = ITS_FIRST_USER_SRC;

    switch(cmdInput)
    {
    case CONNECT:
        ret = TEST_BuildAndSendMsg(SCCP_MSG_CR, bssapMsgType, handle, instance, 0);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Occured Sending DATA.\n";
        }
        break;

    case SEND_UDT:
        ret = TEST_BuildAndSendMsg(SCCP_MSG_UDT, bssapMsgType,handle, instance, 0);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Occured Sending DATA.\n";
        }
        break;

    case BUILD_DATA:
	//while (submenu) 
	//{
#if 0
        	cout <<"\n\n\n\nChoose Message to Send: \n";
#ifdef CLASS_3
		cout <<"   "<<SEND_DT2 <<") SEND DT2"<<endl;
#else
                cout <<"   "<< SEND_DT1_AssignReq 
                     << ") Send Assignment Request" << endl; 

                cout <<"   "<<SEND_DT1_AssignCmplt 
                     << ") Send Assignment Complete" << endl; 

                cout <<"   "<<SEND_DT1_AssignFail
                     << ") Send Assignment Failure" << endl; 

                cout <<"   "<<SEND_DT1_HORequired
                     << ") Send Handover Required" << endl; 

                cout <<"   "<<SEND_DT1_HOCommand
                     << ") Send Handover Command" << endl; 

                cout <<"   "<<SEND_DT1_HORequiredRej
                     << ") Send Handover Required Reject" << endl; 

                cout <<"   "<<SEND_DT1_HORequest
                     << ") Send Handover Request" << endl; 

                cout <<"   "<<SEND_DT1_HORequestAck
                     << ") Send Handover Request Ack" << endl; 

                cout <<"   "<<SEND_DT1_HOFailure
                     << ") Send Handover Failure" << endl; 

                cout <<"   "<<SEND_DT1_ClearCommand 
                     << ") Send Clear Command" << endl; 

                cout <<"   "<<SEND_DT1_ClearCmplt
                     << ") Send Clear Complete" << endl; 

                cout <<"   "<< SEND_DT1_Alerting  
                     << ") Send Alerting " << endl; 

                cout <<"   "<<SEND_DT1_CallConfirm 
                     << ") Send Call Confirm " << endl; 

                cout <<"   "<<SEND_DT1_Connect
                     << ") Send Connect" << endl; 

                cout <<"   "<<SEND_DT1_ConnectAck
                     << ") Send Connect Ack" << endl; 

                cout <<"   "<<SEND_DT1_EmergencySetup
                     << ") Send Emergency Setup" << endl; 

                cout <<"   "<<SEND_DT1_Progress
                     << ") Send Progress " << endl; 

                cout <<"   "<<SEND_DT1_CCEstablish
                     << ") Send CC Establish" << endl; 

                cout <<"   "<<SEND_DT1_Setup
                     << ") Send Setup" << endl; 

                cout <<"   "<<SEND_DT1_Modify
                     << ") Send Modify " << endl; 

                cout <<"   "<<SEND_DT1_ModifyComplete 
                     << ") Send Modify Complete" << endl; 

                cout <<"   "<<SEND_DT1_ModifyReject
                     << ") Send Modify Reject" << endl; 

                cout <<"   "<<SEND_DT1_CallProceeding
                     << ") Send Call Proceeding" << endl; 

                cout <<"   "<<SEND_DT1_Paging
                     << ") Send Paging" << endl; 

                cout <<"   "<<SEND_DT1_CipherModeCommand
                     << ") Send Cipher Mode Command" << endl; 

                cout <<"   "<<SEND_DT1_CipherModeComplete
                     << ") Send Cipher Mode Complete" << endl; 

                cout <<"   "<<SEND_DT1_CompleteLayer3Information
                     << ") Send Complete Layer3 Info" << endl; 
#endif
		cout <<"   "<<DISCONNECT <<") Release Connection"<<endl;
#endif

        	// cin >> msgType;
                msgType = SEND_DT1_AssignReq;

   	   switch (msgType)
	   {
	     case SEND_DT1:
		msgType = SCCP_MSG_DT1;
		break;

             case SEND_DT1_AssignReq:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_ASSIGN_REQUEST; 
		break;

             case SEND_DT1_AssignCmplt:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_ASSIGN_COMPLETE; 
		break;

             case SEND_DT1_AssignFail:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_ASSIGN_FAILURE; 
		break;

             case SEND_DT1_HORequired:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_REQUIRED;
		break;

             case SEND_DT1_HOCommand:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_COMMAND;
		break;

             case SEND_DT1_HORequiredRej:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_REQUIRED_REJECT;
		break;

             case SEND_DT1_HORequest:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_REQUEST;
		break;

             case SEND_DT1_HORequestAck:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_REQUEST_ACK;
		break;

             case SEND_DT1_HOFailure:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_FAILURE;
		break;

             case SEND_DT1_ClearCommand: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CLEAR_COMMAND; 
		break;

             case SEND_DT1_ClearCmplt: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CLEAR_COMPLETE; 
		break;

	     case SEND_DT2:
		msgType = SCCP_MSG_DT2;
		break;

             case SEND_DT1_Alerting:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_ALERTING; 
                transparency = 1;
		break;

             case SEND_DT1_CallConfirm:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_CALL_CONFIRMED; 
                transparency = 1;
		break;

             case SEND_DT1_Connect :
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_CONNECT; 
                transparency = 1;
		break;

             case SEND_DT1_ConnectAck:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_CONNECT_ACKNOWLEDGE;
                transparency = 1;
		break;

             case SEND_DT1_EmergencySetup:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_EMERGENCY_SETUP;
                transparency = 1;
		break;

             case SEND_DT1_Progress:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_PROGRESS;
                transparency = 1;
		break;

             case SEND_DT1_CCEstablish:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_ESTABLISHMENT;
                transparency = 1;
		break;

             case SEND_DT1_Setup:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_SETUP;
                transparency = 1;
		break;

             case SEND_DT1_Modify:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_MODIFY;
                transparency = 1;
		break;

             case SEND_DT1_ModifyComplete: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_MODIFY_COMPLETE; 
                transparency = 1;
		break;

             case SEND_DT1_ModifyReject: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_MODIFY_REJECT; 
                transparency = 1;
		break;

             case SEND_DT1_CallProceeding: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_CALL_PROCEEDING; 
                transparency = 1;
		break;


             case SEND_DT1_Paging:
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_PAGING;
		break;

             case SEND_DT1_CipherModeCommand: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CIPHER_MODE_CMD; 
		break;

             case SEND_DT1_CipherModeComplete: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CIPHER_MODE_COMPLETE; 
		break;

             case SEND_DT1_CompleteLayer3Information: 
		msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_COMPLETE_LAYER3_INFO; 
		break;

	     case DISCONNECT:
		msgType = SCCP_MSG_RLSD;
		submenu = false;
		break;

	     default:
		cout << "Invalid Response"<< endl;
	  	break;
       	   }

           ret = TEST_BuildAndSendMsg(msgType, bssapMsgType, handle, instance, transparency);
           if (ret != ITS_SUCCESS)
           {
               cout << "TEST --- > Error Occured Sending Request.\n";
           }
	//}
	break;
    default:
	break;
    }
 return (ITS_SUCCESS);
}

void BuildAssigmentRequest(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
   

    BSSAP_ChanType                  chanType;
    BSSAP_L3HeaderInfo              l3hInfo;
    BSSAP_Prio                      prio;
    BSSAP_CktIDCode                 cktId;
    BSSAP_DLDTXFlag                 dlFlag;
    BSSAP_ClassmarkInfo2            cmInfo2;
    BSSAP_GrpClRef                  gcRef;
    BSSAP_TalkerFlag                tkFlag;
    BSSAP_LsaAccCtrlSuppr           lacs;
    BSSAP_ConfigEvlInd              ceInd;
    BSSAP_ServHandover              servHand;

    // message
    BSSAP_AssignmentRequest assReq;

    // populate Channel Type, add it to the message   
    chanType.SetSpeechDataID(CT_DATA);                           //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);  //0x08
        
    // populate Channel Type, add it to the message      
    chanType.SetSpeechDataID(CT_DATA);                             //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08
    chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
    chanType.SetIFDateRate(0, 0x53);                               //0x53
    // chanType.SetAsymInd(0, 0x02);                                  //0x02

    assReq.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);

    // populate Layer 3 Header Information, add it to the message
    l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    l3hInfo.SetTIVal(TI_VALUE_3);                      //0x03
    l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
    assReq.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

    // populate Priority, add it to the message
    prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
    prio.SetQA(P_QUEUING_ALLOWED);                      //0x01
    prio.SetPCI(P_PREEMPTION_ALLOWED);                  //0x01 
    prio.SetPVI(P_CONN_BE_REQ);                         //0x01

    assReq.AddIE(BSSAP_IEI_PRIORITY, &prio);               

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(ushort);                             //0x228
    cktId.SetTimeslot(octet);                           //0x11

    assReq.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
        
    // populate Downlink DTX Flag, add it to the message
    dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00
    
    assReq.AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);

    // populate Classmark Info Type2, add it to the message
    cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
    cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
    cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
    cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
    cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
    cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
    cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
    cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
    cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
    cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
    cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
    cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
    cmInfo2.SetCM3(CIT2_CM3_OPTIONS_SUPPORTED);         //0x01

    assReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);


    // populate Group Call Reference, add it to the message
    gcRef.SetCallRef(uint);                             //0x4321000
    gcRef.SetClPrio(GCR_CALL_PRIORITY_LEVEL_B);         //0x06
    gcRef.SetAF(GCR_AF_ACK_REQUIRED);                   //0x01
    gcRef.SetSF(GCR_SF_VBS);                            //0x00
    gcRef.SetCiphInfo(GCR_CIPHERING_KEY_9);             //0x09;

    assReq.AddIE(BSSAP_IEI_GROUP_CALL_REFERENCE, &gcRef);


    // populate Talker Flag, add it to the message
    assReq.AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);

    // populate LSA Access Control Suppression, add it to the message
    lacs.SetEmergency(0x01); 

    // assReq.AddIE(BSSAP_IEI_LSA_ACCESS_CTRL_SUPPR, &lacs);

        
    // populate Configuration Evolution Indication, add it to the message
    ceInd.SetSMI(CE_MODIFICATION_ALLOWED_TCH_F_2);        //0x02
    assReq.AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);

    // populate Service Handover, add it to the message
    // servHand.SetServHandoverInfo(SH_HANDPVER_TO_NEITHER_SHOULD_NOT_PERFORM);//0x01

    //assReq.AddIE(BSSAP_IEI_SERVICE_HANDOVER, &servHand);
 
    int len;
    if (BSSAP_Message::Encode(databuf, len, &assReq) != ITS_SUCCESS)
    {
        cout << "Error encoding Assignment Request." << endl;
        return;
    }
     *datalen = len;
}

void BuildAssigmentComplete(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    BSSAP_RRcause                   rrCs;
    BSSAP_CktIDCode                 cktId;
    BSSAP_CellID                    cellId;
    BSSAP_ChsChan                   chsChan;
    BSSAP_ChsEncAlg                 ceAlg;
    BSSAP_CktPool                   cktPl;
    BSSAP_SpchVer                   spchVer;
    BSSAP_LsaId                     lsaid;

    // message
    BSSAP_AssignmentComplete assCmp;

    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

    assCmp.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);


    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(ushort);                             //0x228
    cktId.SetTimeslot(octet);                           //0x04

    assCmp.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate Cell Identifier, add it to the message

    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);

    assCmp.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);


    // populate Chosen Channel, add it to the message
    chsChan.SetChan(CC_CH_SPEECH);                      //0x09
    chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01

    assCmp.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);


    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                 //0x03
    assCmp.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);


    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

    assCmp.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);


    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER3);         //0x21

    assCmp.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);


    // populate LSA Identifier, add it to the message
    /*lsaid.SetLSAIDBit1(0x01);
    lsaid.SetLSAID(0x432111);

    assCmp.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid); */

    int len;
    if (BSSAP_Message::Encode(databuf, len, &assCmp) != ITS_SUCCESS)
    {
        cout << "Error encoding Assignment Complete." << endl;
        return;
    }

    *datalen = len;
}

void BuildAssigmentFailure(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_Cse                       cs;
    BSSAP_RRcause                   rrCs;
    BSSAP_CktPool                   cktPl;
    BSSAP_CktPoolList               cpList;
    BSSAP_CircuitPool               cpool;

    BSSAP_AssignmentFailure assFail;

    // populate Cause, add it to the message
    cs.SetCause(0x40, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL);
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, 0x11);

    assFail.AddIE(BSSAP_IEI_CAUSE, &cs);

    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

    assFail.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

    assFail.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);

    // populate Circuit Pool List, add it to the message
    CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
    for(int i = 0; i < 2; i++)
    {
        cpList.SetCircuitPoolNo(cpool, i);
    }

    assFail.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);

    int len;
    // build the message
    if (BSSAP_Message::Encode(databuf, len, &assFail) != ITS_SUCCESS)
    {
        cout << "Error encoding Assignment Failure." << endl;
        return;
    }
    *datalen = len;
}

void BuildHandoverRequest(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET                       key[] = {1,3,3,4,5};
    ITS_OCTET                       octet = 0x11U;
    ITS_USHORT                      ushort  = 0x228U;
    BSSAP_CellIDType                cid;
    BSSAP_ChanType                  chanType;
    BSSAP_EncryptionInformation     encInfo;
    BSSAP_CellID                    cellId;
    BSSAP_CellID                    out;
    BSSAP_ClassmarkInfo2            cmInfo2;
    BSSAP_Prio                      prio;
    BSSAP_CktIDCode                 cktId;
    BSSAP_DLDTXFlag                 dlFlag;
    BSSAP_InterBandToBeUsed         ibbu;
    BSSAP_Cse                       cs;
    BSSAP_ClassmarkInfo3            cmInfo3;
    BSSAP_CrtChan                   crtChan;
    BSSAP_SpchVer                   spchVer;
    BSSAP_GrpClRef                  gcRef;
    BSSAP_TalkerFlag                tkFlag;
    BSSAP_ConfigEvlInd              ceInd;
    BSSAP_ChsEncAlg                 ceAlg;
    BSSAP_SrcRNCtoTgtRNCInfoUMTS    umts;
    BSSAP_SrcRNCtoTgtRNCInfoCDMA    cdma;


    BSSAP_HandoverRequest handReq;

    // populate Channel Type, add it to the message
    chanType.SetSpeechDataID(CT_DATA);                           //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);  //0x08

    // populate Channel Type, add it to the message
    chanType.SetSpeechDataID(CT_DATA);                             //0x02
    chanType.SetChanRateType(CT_DATA_FULL_RATE_TCH_CHANNEL_BM);    //0x08

    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 0);      //0x01
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 1);      //0x11
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 2);      //0x21
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER1, 3);      //0x01
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER2, 4);      //0x11
    chanType.SetPermitSpch(1, CT_PSVI_GSM_FULL_RATE_VER3, 5);      //0x21

    chanType.SetDataTransp(1, CT_DATA_MAX_ALLOWED_CHANNEL1, 1);    //0x20
    chanType.SetIFDateRate(0, 0x53);                               //0x53
    //chanType.SetAsymInd(0, 0x02);                                  //0x02

    handReq.AddIE(BSSAP_IEI_CHANNEL_TYPE, &chanType);

    // populate Encryption Information, add it to the message
    encInfo.SetNoEncryption(0);
    encInfo.SetA5_1(1);
    encInfo.SetA5_2(0);
    encInfo.SetA5_3(1);
    encInfo.SetA5_4(0);
    encInfo.SetA5_5(1);
    encInfo.SetA5_6(0);
    encInfo.SetA5_7(1);
    encInfo.SetKey(key, sizeof(key));

    handReq.AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);

    // populate Classmark Information 2, add it to the message
    cmInfo2.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo2.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo2.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo2.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
    cmInfo2.SetFC(CIT2_FC_SUPPORTED);                   //0x01
    cmInfo2.SetVGCS(CIT2_VGCS_CAP_NEEDED);              //0x01
    cmInfo2.SetVBS(CIT2_VBS_CAP_NEEDED);                //0x01
    cmInfo2.SetSMCap(CIT2_SM_CAP_SUPPORTED);            //0x01
    cmInfo2.SetSSSInd(CIT2_SS_SCREEN_IND_4);            //0x03
    cmInfo2.SetPSCap(CIT2_PS_CAP_PRESENT);              //0x01
    cmInfo2.SetA52(CIT2_A5_2_SUPPORTED);                //0x01
    cmInfo2.SetA53(CIT2_A5_3_SUPPORTED);                //0x01
    cmInfo2.SetCMSP(CIT2_CMSP_SUPPORTED);               //0x01
    cmInfo2.SetSoLSA(CIT2_SOLSA_SUPPORTED);             //0x01
    cmInfo2.SetLCSVACap(CIT2_LCS_VA_CAP_SUPPORTED);     //0x01
    cmInfo2.SetCM3(CIT2_CM3_OPTIONS_NOT_SUPPORTED);     //0x01

    handReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);


    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);

    handReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);

    // populate Cell Identifier (out), add it to the message
    out.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,octet);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    out.SetCellID(cid);

    handReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &out);


    // populate Priority, add it to the message
    prio.SetPriority(P_PRI_LEVEL_5);                    //0x05
    prio.SetQA(P_QUEUING_ALLOWED);                      //1
    prio.SetPVI(1);
    prio.SetPCI(P_NO_PREEMPTION );                      //0

    handReq.AddIE(BSSAP_IEI_PRIORITY, &prio);

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(ushort);                             //0x228
    cktId.SetTimeslot(octet);                           //0x04

    handReq.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


    // populate Downlink DTX Flag, add it to the message
    dlFlag.SetDTXFlag(DLDTX_ACTIVATE_ALLOWED);          //0x00

    handReq.AddIE(BSSAP_IEI_DOWNLINK_DTX_FLAG, &dlFlag);


    // populate Interference Band To Be Used, add it to the message
    ibbu.SetBandToBeUsed(octet);                        //0x04

    handReq.AddIE(BSSAP_IEI_INTERFERENCE_BAND_TO_BE_USED, &ibbu);

    // populate Cause, add it to the message
    cs.SetCause(0x40, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL);
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

    handReq.AddIE(BSSAP_IEI_CAUSE, &cs);
    cmInfo3.SetMultiBand(0x05);                      //0x01
    cmInfo3.SetA54(1);                               //0x01
    cmInfo3.SetA55(0);                               //0x01
    cmInfo3.SetA56(0);                               //0x01
    cmInfo3.SetA57(1);                               //0x01
    cmInfo3.SetRadioCap1(0x04);
    cmInfo3.SetRadioCap2(0x08);
    cmInfo3.SetMultiSlotClass(0x07);
    cmInfo3.SetRGSMCap(0x06);
    cmInfo3.SetSMValue(0x09);
    cmInfo3.SetSMSValue(0x02);
    cmInfo3.SetUCS2Treat(1);
    cmInfo3.SetExtMeasCap(0);
    cmInfo3.SetMSConGPS(1);
    cmInfo3.SetMSBasedGPS(0);
    cmInfo3.SetMSAssistedGPS(1);
    cmInfo3.SetMSBasedEOTD(0);
    cmInfo3.SetMSAssistedEOTD(1);

    handReq.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE3, &cmInfo3);


    // populate Current Channel, add it to the message
    crtChan.SetChan(CC_CHANNEL_MODE_SPEECH);               //0x01
    crtChan.SetChanMode(CC_CHANNEL_SDCCH);                 //0x01

    handReq.AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_1, &crtChan);


    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

    handReq.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);


    // populate Talker Flag, add it to the message
    handReq.AddIE(BSSAP_IEI_TALKER_FLAG, &tkFlag);

    // populate Configuration Evolution Indication, add it to the message
    ceInd.SetSMI(CE_NO_MODIFICATION_ALLOWED);           //0x00
    handReq.AddIE(BSSAP_IEI_CONFIGURATION_EVOLUTION_IND, &ceInd);


    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03
    handReq.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

#if 0
    // populate Soruce RNC to Target RNC Transparent Information (UMTS),
    // add it to the message
    umts.SetSrcRNCtoTgtRNCInfoUMTS(key, sizeof(key));

    handReq.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, &umts);

    // populate Soruce RNC to Target RNC Transparent Information (CDMA),
    // add it to the message
    cdma.SetSrcRNCtoTgtRNCInfoCDMA(key, sizeof(key));

    handReq.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, &cdma);
#endif

    int len;
    if (BSSAP_Message::Encode(databuf, len, &handReq) != ITS_SUCCESS)
    {
        cout << "Error encoding Handover Request." << endl;
        return;
    }
    *datalen = len;
}

void BuildHandoverRequestAck(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET                       key[] = {1,3,3,4,5};
    ITS_OCTET                       octet = 0x11U;
    ITS_USHORT                      ushort  = 0x228U;
    BSSAP_L3Info                    l3Info;
    BSSAP_ChsChan                   chsChan;
    BSSAP_ChsEncAlg                 ceAlg;
    BSSAP_CktPool                   cktPl;
    BSSAP_SpchVer                   spchVer;
    BSSAP_CktIDCode                 cktId;
    BSSAP_LsaId                     lsaid;

    BSSAP_HandoverRequestAcknowledge hrAck;

    // populate Layer 3 Information, add it to the message
    l3Info.SetL3Info(key, sizeof(key));

    hrAck.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

    // populate Chosen Channel, add it to the message
    chsChan.SetChan(CC_CH_SPEECH);                      //0x09
    chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01

    hrAck.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);

    // populate Chosen Encryption Algorithm, add it to the message
    ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

    hrAck.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

    hrAck.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);

    // populate Speech Version, add it to the message
    spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

    hrAck.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

    // populate Circuit Identity Code, add it to the message
    cktId.SetPCMID(ushort);                             //0x228
    cktId.SetTimeslot(octet);                           //0x04

    hrAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

    // populate LSA Identifier, add it to the message
    /*lsaid.SetLSAIDBit1(0x01);
    lsaid.SetLSAID(0x432111);

    hrAck.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);*/

    int len;
    if (BSSAP_Message::Encode(databuf, len, &hrAck) != ITS_SUCCESS)
    {
        cout << "Error encoding Handover Request Acknowledge." << endl;
        return;
    }
    *datalen = len;

}

void BuildHandoverRequired(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET                       octet = 0x11U;
    ITS_USHORT                      ushort  = 0x228U;
    BSSAP_CellIDT                   cid1;
    ITS_OCTET                       key[] = {1,3,3,4,5};
    ITS_OCTET                       key2[] = {3,5,3,4,5,6,7};
    BSSAP_Cse                       cs;
    BSSAP_CellIDList                ciList;
    BSSAP_RspReq                    rspReq;
    BSSAP_CktPoolList               cpList;
    BSSAP_CrtChan                   crtChan;
    BSSAP_SpchVer                   spchVer;
    BSSAP_QueuingInd                qInd;
    BSSAP_OldBSStoNewBSSInfo        bssInfo;
    BSSAP_SrcRNCtoTgtRNCInfoUMTS    umts;
    BSSAP_SrcRNCtoTgtRNCInfoCDMA    cdma;
    // IEs included in Old BSS to New BSS
    BSSAP_ExtraInfo                 exInfo;
    BSSAP_CrtChan2                  crtChan2;
    BSSAP_TargetCellRadioInfo       tcri;
    BSSAP_GPRSSuspendInfo           gsi;
    BSSAP_MultirateConfigInfo       mci;
    BSSAP_DualTransferModeInfo      dtmi;
    BSSAP_UECapInfo                 uci;
    BSSAP_cdma2000CapInfo           cci;
    BSSAP_UTRANIndicationSet        upis;
    BSSAP_UESecurityInfo            usi;

    BSSAP_HandoverRequired handRqd;

    // populate Cause, add it to the message
    cs.SetCause(0x40, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL);
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

    handRqd.AddIE(BSSAP_IEI_CAUSE, &cs);


    // populate Cell Identifier List, add it to the message
    ciList.SetCellIDListDisc(CI_CID_CGI);
    //cgi
    CIL_CGI_SET_MCC_PCS(cid1,ushort);
    CIL_CGI_SET_MNC_PCS(cid1,octet);
    CIL_CGI_SET_LAC(cid1,ushort);
    CIL_CGI_SET_CI(cid1,ushort);
    for(int i = 0; i < 10; i++)
    {
        ciList.SetCellID(cid1, i);
    }

    handRqd.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);

    // populate Old BSS to New BSS Information, add it to the message

#if 0
        // Estra Information
        exInfo.SetPREC(0x01);
        exInfo.SetLCS(0x01);

        bssInfo.AddIE(BSSAP_IEI_EXTRA_INFORMATION, &exInfo);

        // Current Channel Type 2
        crtChan2.SetChan(CCT2_CF_1_FULL_RATE);          //0x04
        crtChan2.SetChanMode(CCT2_CM_DATA_6);           //0x08

        bssInfo.AddIE(BSSAP_IEI_CURRENT_CHANNEL_TYPE_2, &crtChan2);

        // Target Cell Radio Information
        tcri.SetRXLEV_NCELL(0x11);
        bssInfo.AddIE(BSSAP_IEI_TARGET_CELL_RADIO_INFO, &tcri);


        // GPRS Suspend Information

        gsi.SetTLLI(key, sizeof(key));

        gsi.SetRAI(key2, sizeof(key2));

        gsi.SetSRN(key, sizeof(key));

        bssInfo.AddIE(BSSAP_IEI_GPRS_SUSPEND_INFO, &gsi);

        // Multirate Configuration Information
        mci.SetStartMode(MCI_CODEC_MODE_4);            // 0x03
        mci.SetICMI(0x01);
        mci.SetMRVersion(MCI_ADAPTIVE_MR_SPCH_VER_1);  // 0x01
        mci.SetARMCodecMode1(0x01);
        mci.SetARMCodecMode2(0x00);
        mci.SetARMCodecMode3(0x01);
        mci.SetARMCodecMode4(0x00);
        mci.SetARMCodecMode5(0x01);
        mci.SetARMCodecMode6(0x00);
        mci.SetARMCodecMode7(0x01);
        mci.SetARMCodecMode8(0x00);
        mci.SetThreshold1(0x06);
        mci.SetThreshold2(0x12);
        mci.SetThreshold3(0x19);
        mci.SetHysteresis1(0x05);
        mci.SetHysteresis2(0x04);
        mci.SetHysteresis3(0x01);

        bssInfo.AddIE(BSSAP_IEI_MULTIRATE_CONFIG_INFO, &mci);
        // Dual Transfer Mode Information
        dtmi.SetDTMInd(0x01);
        dtmi.SetSTOInd(0x00);
        dtmi.SetEGPRSInd(0x01);

        bssInfo.AddIE(BSSAP_IEI_DUAL_TRANSFER_MODE_INFO, &dtmi);

        // UE Capability Information
        uci.SetUECapInfo(key, sizeof(key));

        bssInfo.AddIE(BSSAP_IEI_UE_CAP_INFO, &uci);

        // cdma2000 Capability Information
        cci.SetcdmaCapInfo(key, sizeof(key));

        bssInfo.AddIE(BSSAP_IEI_CDMA_2000_CAP_INFO, &cci);

        // UTRAN Pre-configuration Indication Set
        upis.SetPre_Config_Id_Tag(0x04, 0x05, 0);
        upis.SetPre_Config_Id_Tag(0x06, 0x07, 1);
        upis.SetPre_Config_Id_Tag(0x01, 0x02, 2);

        bssInfo.AddIE(BSSAP_IEI_UTRAN_PRECONFIG_IND_SET_INFO, &upis);

        // UE Security Information
        usi.SetUESecurityInfo(key, sizeof(key));
        bssInfo.AddIE(BSSAP_IEI_UE_SECURITY_INFO, &usi);

    // handRqd.AddIE(BSSAP_IEI_OLD_BSS_TO_NEW_BSS_INFO, &bssInfo);

    // populate Soruce RNC to Target RNC Transparent Information (UMTS),
    // add it to the message
    umts.SetSrcRNCtoTgtRNCInfoUMTS(key, sizeof(key));

    //handRqd.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_UMTS, &umts);

    // populate Soruce RNC to Target RNC Transparent Information (CDMA),
    // add it to the message
    cdma.SetSrcRNCtoTgtRNCInfoCDMA(key, sizeof(key));

    //handRqd.AddIE(BSSAP_IEI_SRC_RNC_TO_TGT_RNC_INFO_CDMA, &cdma);
#endif

    int len;
    if (BSSAP_Message::Encode(databuf, len, &handRqd) != ITS_SUCCESS)
    {
        cout << "Error encoding Handover Required." << endl;
        return;
    }
    *datalen = len;
}

void BuildHandoverCommand(ITS_OCTET *databuf, int *datalen)
{
    ITS_USHORT                      ushort  = 0x228U;
    ITS_OCTET                       key[] = {1,3,3,4,5};
    BSSAP_CellIDType                cid;
    BSSAP_L3Info                    l3Info;
    BSSAP_CellID                    cellId;

    BSSAP_HandoverCommand  handCmd;

    // populate Layer 3 Information, add it to the message
    key[0] = 0x33;
    key[1] = 0x33;
    key[2] = 0x33;
    key[3] = 0x00;
    l3Info.SetL3Info(key, 4);

    handCmd.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

    // populate Cell Identifier, add it to the message
    cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
    CI_CGI_SET_MCC_PCS(cid,ushort);
    CI_CGI_SET_MNC_PCS(cid,0x22);
    CI_CGI_SET_LAC(cid,ushort);
    CI_CGI_SET_CI(cid,ushort);
    cellId.SetCellID(cid);

    handCmd.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &handCmd) != ITS_SUCCESS)
    {
        cout << "Error encoding Handover Command." << endl;
        return;
    }
    *datalen = len;
}

void BuildHandoverRequiredReject(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_Cse                       cs;

    BSSAP_HandoverRequiredReject hrRej;

    // populate Cause, add it to the message
    cs.SetCause(0x28, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U

    hrRej.AddIE(BSSAP_IEI_CAUSE, &cs);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &hrRej) != ITS_SUCCESS)
    {
        cout << "Error encoding HandoverRequiredReject." << endl;
        return;
    }
    *datalen = len;
}

void BuildHandoverFailure(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET                       octet = 0x11U;
    BSSAP_CircuitPool               cpool;
    BSSAP_Cse                       cs;
    BSSAP_RRcause                   rrCs;
    BSSAP_CktPool                   cktPl;
    BSSAP_CktPoolList               cpList;

    BSSAP_HandoverFailure handFail;

    // populate Cause, add it to the message
    cs.SetCause(0x40, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL);
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

    handFail.AddIE(BSSAP_IEI_CAUSE, &cs);


    // populate RR Cause, add it to the message
    rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

    handFail.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);


    // populate Circuit Pool, add it to the message
    cktPl.SetCircuitPoolNo(CP_NUMBER_1);                 //0x01

    handFail.AddIE(BSSAP_IEI_CIRCUIT_POOL, &cktPl);
    
    // populate Circuit Pool List, add it to the message
    CP_SET_CIRCUIT_POOL_NUM(cpool,CP_NUMBER_2);          //0x02
    for(int i = 0; i < 2; i++)
    {
        cpList.SetCircuitPoolNo(cpool, i);
    }

    handFail.AddIE(BSSAP_IEI_CIRCUIT_POOL_LIST, &cpList);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &handFail) != ITS_SUCCESS)
    {
        cout << "Error encoding Handover Failure." << endl;
        return;
    }
    *datalen = len;
}

void BuildClearCommand(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET                       octet = 0x11U;
    BSSAP_Cse                       cs;
    BSSAP_L3HeaderInfo              l3hInfo;

    BSSAP_ClearCommand clrCmd;

    // populate Cause, add it to the message
    cs.SetCause(0x40, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL);
    cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

    clrCmd.AddIE(BSSAP_IEI_CAUSE, &cs);

    // populate Layer 3 Header Information, add it to the message
    l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
    l3hInfo.SetTIVal(8);
    l3hInfo.SetTIFlag(9);

    clrCmd.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &clrCmd) != ITS_SUCCESS)
    {
        cout << "Error encoding Clear Command." << endl;
        return;
    }
    *datalen = len;
}

void BuildClearComplete(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_ClearComplete clrCplt;

    int len;
    if (BSSAP_Message::Encode(databuf, len, &clrCplt) != ITS_SUCCESS)
    {
        cout << "Error encoding Clear Complete." << endl;
        return;
    }
    *datalen = len;
}



//Print UserData
void
DumpData(ITS_OCTET* data, int len)
{
    cout << endl;
    cout << "The length of UserData is : " << len <<endl;

    for (int i = 0; i < len; i++)
    {
        if (i && !(i%20))
        {
            cout << endl;
        }
        printf("%02x ", data[i]);
    }
    cout << endl<<endl;
}


void BuildAlerting(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    

    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Alerting alert;

       
        // populate Layer 3 Header Information, add it to the message
        alert.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        alert.SetTIVal(TI_VALUE_3);                      //0x03
        //l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        alert.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

        /*facility.SetFacilityData(buff, 5);
        alert.AddIE(BSSAP_IEI_CC_FACILITY, &facility);*/

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        alert.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        BSSAP_UserToUser    userTouser;
        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        alert.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &alert) != ITS_SUCCESS)
        {
            cout << "Error encoding Alerting " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }
}

void BuildCCConfirm(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CallConfirmed ccon;

       
        // populate Layer 3 Header Information, add it to the message
        l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        l3hInfo.SetTIVal(TI_VALUE_3);                      //0x03
        l3hInfo.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        
        ccon.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        ccon.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        cause.SetCodingLocationCause(1, 1, 1);
        ccon.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        cc.SetDTMF();
        cc.SetPCP();
        ccon.AddIE(BSSAP_IEI_CC_CAPABILITIES, &cc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &ccon) != ITS_SUCCESS)
        {
            cout << "Error encoding Alerting " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }
}

void BuildCallProceeding(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CallProceeding cp;

        cp.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cp.SetTIVal(TI_VALUE_3);                      //0x03
       
        
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        cp.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        facility.SetFacilityData(buff, 5);
        /*cp.AddIE(BSSAP_IEI_CC_FACILITY, &facility);*/

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        cp.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cp) != ITS_SUCCESS)
        {
            cout << "Error encoding Alerting " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }
}

void BuildConnect(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Connect co;

        co.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        co.SetTIVal(TI_VALUE_3);                      //0x03
       

        facility.SetFacilityData(buff, 5);
        //co.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        co.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        cn.SetTypeAndNumPlan( 1, 1);
        cn.SetDigits(buff, 5);
        co.AddIE(BSSAP_IEI_CC_CONNECTED_NUMBER, &cn);

        cs.SetSubAddressType( 1, ITS_TRUE);
        cs.SetSubAddressInfo(buff, 5);
        co.AddIE(BSSAP_IEI_CC_CONNECTED_SUB_ADDRESS, &cs);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        co.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        ss.SetSSVersion(buff, 2);
        co.AddIE(BSSAP_IEI_CC_SS_VERSION_IND, &ss);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &co) != ITS_SUCCESS)
        {
            cout << "Error encoding connect " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);
    }
}


void BuildConnectAck(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ConnectAck cok;

        cok.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cok.SetTIVal(TI_VALUE_3);                      //0x03

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cok) != ITS_SUCCESS)
        {
            cout << "Error encoding connect " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);
    }
}


void BuildEmergencySetup(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_EmergencySetup es;

       
        es.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        es.SetTIVal(TI_VALUE_3);                      //0x03

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        es.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &es) != ITS_SUCCESS)
        {
            cout << "Error encoding Emergency Setup " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }

    
}


void BuildProgress(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_UserToUser                userTouser;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Progress pr;

       
        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        pr.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        pr.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &pr) != ITS_SUCCESS)
        {
            cout << "Error encoding Progress " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }

}


void BuildCCEstablish(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_UserToUser                userTouser;
        BSSAP_SetupContainer            sc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CCEstablishment cce;

       
        ITS_OCTET value = 1;
        sc.SetSetupData(databuf, 5);
        cce.AddIE(BSSAP_IEI_CC_SETUP_CONTAINER_INTERNAL, &sc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &cce) != ITS_SUCCESS)
        {
            cout << "Error encoding CC Establishment " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

    }
}


void BuildSetup(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_RepeatIndicator   ri;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Setup setup;

        ri.SetRepeatType(1);
        setup.AddIE(BSSAP_IEI_CC_REPEAT_INDICATOR, &ri);
       
        setup.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        setup.SetTIVal(TI_VALUE_3);                      //0x03

        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        setup.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);


        bd.SetInfoTransferCapabAndRadioChannelType(2, 2);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        setup.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);


         buff[0] = 1;
         buff[1] = 1;
         buff[2] = 1;
        facility.SetFacilityData(buff, 0);
        // setup.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        setup.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        signal.SetSignal(1);
        setup.AddIE(BSSAP_IEI_CC_SIGNAL, &signal);

        cg.SetTypeAndNumPlan( 1, 1);
        cg.SetDigits(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLING_PARTY_BCD_NUMBER, &cg);

        cgs.SetSubAddressType( 1, ITS_TRUE);
        cgs.SetSubAddressInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLING_PARTY_SUB_ADDRESS, &cgs);

        cd.SetTypeAndNumPlan( 1, 1);
        cd.SetDigits(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLED_PARTY_BCD_NUMBER, &cd);

        cds.SetSubAddressType( 1, ITS_TRUE);
        cds.SetSubAddressInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_CALLED_PARTY_SUB_ADDRESS, &cds);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        lc.SetLowLevelCompInfo(buff, 5);
        setup.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(value, value);
        setup.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &setup) != ITS_SUCCESS)
        {
            cout << "Error encoding connect " << endl;
            return;
        }
        *datalen = len;


        // print the user data
        DumpData(databuf, len);

        // do the decode
    }
}


void BuildModify(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Modify modify;
       
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        modify.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        lc.SetLowLevelCompInfo(buff, 5);
        modify.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        modify.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &modify) != ITS_SUCCESS)
        {
            cout << "Error encoding modify " << endl;
            return;
        }


        *datalen = len;

        // print the user data
        DumpData(databuf, len);

    }
}


void BuildModifyComplete(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ModifyComplete mc;
       
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        mc.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);

        lc.SetLowLevelCompInfo(buff, 5);
        mc.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        mc.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &mc) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }

        *datalen = len;

        // print the user data
        DumpData(databuf, len);

        // do the decode
    }
}


void BuildModifyReject(ITS_OCTET *databuf, int *datalen)
{
    //variables
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_ChanType                  chanType;
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_Prio                      prio;
        BSSAP_CktIDCode                 cktId;
        BSSAP_DLDTXFlag                 dlFlag;
        BSSAP_ClassmarkInfo2            cmInfo2;
        BSSAP_GrpClRef                  gcRef;
        BSSAP_TalkerFlag                tkFlag;
        BSSAP_LsaAccCtrlSuppr           lacs;
        BSSAP_ConfigEvlInd              ceInd;
        BSSAP_ServHandover              servHand;
        BSSAP_Facility                  facility;
        BSSAP_ProgressIndicator         progress;
        BSSAP_BearerData                bd;
        BSSAP_CCCause                   cause;
        BSSAP_CCCapabilities            cc;
        BSSAP_ConnectedNumber            cn;
        BSSAP_ConnectedSubAddress       cs;
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_ModifyReject mr;
       
        bd.SetInfoTransferCapabAndRadioChannelType(1, 1);
        bd.SetCodingGsm();
        bd.SetTransferModeCkt();
        mr.AddIE(BSSAP_IEI_CC_BEARER_CAPABILITY, &bd);


        cause.SetCodingLocationCause(1, 1, 1);
        mr.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        lc.SetLowLevelCompInfo(buff, 5);
        mr.AddIE(BSSAP_IEI_CC_LOW_LAYER_COMPATIBILITY, &lc);

        hc.SetCodingPrsInterpretAndCharacterstics(1, 1);
        mr.AddIE(BSSAP_IEI_CC_HIGH_LAYER_COMPATIBILITY, &hc);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &mr) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }

        *datalen = len;

        // print the user data
        DumpData(databuf, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding modify complete" << endl;
            return;
        }     

        PrintBSSMAPMsgModifyReject(dec);
    }

}

void BuildPaging(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {     
        BSSAP_IMSI                      imsi;
        BSSAP_CellIDList                ciList;
        BSSAP_TMSI                      tmsi;
        BSSAP_ChanNeeded                chanNd;
        BSSAP_eMMLPrio                  emmlp;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_Paging pag;

        
        // populate IMSI, add it to the message
//        imsi.SetDigits(digits, strlen(digits));              //7260686
        imsi.SetDigitsB(mindig, 7);

        pag.AddIE(BSSAP_IEI_IMSI, &imsi);

        // populate Cell Identifier List, add it to the message
        ciList.SetCellIDListDisc(CI_CID_CGI);
        //cgi
        CIL_CGI_SET_MCC_PCS(cid1,ushort);
        CIL_CGI_SET_MNC_PCS(cid1,octet);
        CIL_CGI_SET_LAC(cid1,ushort);
        CIL_CGI_SET_CI(cid1,ushort);
//        ciList.AddCellID(cid1);
        for(i = 0; i < 10; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        pag.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);


        // populate TMSI, add it to the message
        tmsi.SetTMSI(uint);                                    //0x4321000

        pag.AddIE(BSSAP_IEI_TMSI, &tmsi);


        // populate Channel Needed, add it to the message
        chanNd.SetChan(CN_CHANNEL_TCH_F);                      //0x02

        pag.AddIE(BSSAP_IEI_CHANNEL_NEEDED, &chanNd);


        // populate eMMLPriority, add it to the message
        emmlp.SetClPrio(octet);

        pag.AddIE(BSSAP_IEI_eMLPP_PRIORITY, &emmlp);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &pag) != ITS_SUCCESS)
        {
            cout << "Error encoding Paging." << endl;
            return;
        }
        *datalen = len;

    }
}


void BuildCompleteLayer3Info(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    
    {
        BSSAP_CellID                    cellId;
        BSSAP_L3Info                    l3Info;
        BSSAP_LsaIdList                 lidList;

        BSSAP_LSAIdentifier lid = {0};

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CompleteLayer3Information cl3i;

        
        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        cl3i.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Layer 3 Information, add it to the message
        l3Info.SetL3Info(key, sizeof(key));                      
        
        cl3i.AddIE(BSSAP_IEI_LAYER3_INFORMATION, &l3Info);

        // populate LSA Identifier List, add it to the message
        lidList.SetEscapePLMN(0x01); 
        
        LSAID_SET_LSA_ID_BIT_1(lid,0x01);
        LSAID_SET_LSA_ID(lid,0x432110);

        lidList.SetLSAID(lid, 0);
        lidList.SetLSAID(lid, 1);
        
        // cl3i.AddIE(BSSAP_IEI_LSA_IDENTIFIER_LIST, &lidList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cl3i) != ITS_SUCCESS)
        {
            cout << "Error encoding Complete Layer3 Information." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildCipherModeCommand(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    {
        BSSAP_EncryptionInformation     encInfo;  
        BSSAP_L3HeaderInfo              l3hInfo;
        BSSAP_CipherRspMode             crMd;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CipherModeCommand cmCmd;

        
        // populate Encryption Information, add it to the message
        encInfo.SetNoEncryption(0); 
        encInfo.SetA5_1(1);
        encInfo.SetA5_2(0);
        encInfo.SetA5_3(1);
        encInfo.SetA5_4(0);
        encInfo.SetA5_5(1);
        encInfo.SetA5_6(0);
        encInfo.SetA5_7(1);
        encInfo.SetKey(key, sizeof(key));                     

        cmCmd.AddIE(BSSAP_IEI_ENCRYPTION_INFORMATION, &encInfo);


        // populate Layer 3 Header Information, add it to the message
        l3hInfo.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        l3hInfo.SetTIVal(7);
        l3hInfo.SetTIFlag(1);
        
        cmCmd.AddIE(BSSAP_IEI_LAYER3_HEADER_INFORMATION, &l3hInfo);
        

        // populate Cipher Response Mode, add it to the message
        crMd.SetCipherRspMode(CRM_IMEISV_INLCUDED);        //0x01
        
        cmCmd.AddIE(BSSAP_IEI_CIPHER_RESPONSE_MODE, &crMd);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmCmd) != ITS_SUCCESS)
        {
            cout << "Error encoding CipherModeCommand." << endl;
            return;
        }

       *datalen = len;
        // do the decode
    }
}
    
void BuildCipherModeComplete(ITS_OCTET *databuf, int *datalen)
{
    ITS_OCTET               octet = 0x11U;
    ITS_OCTET               zero = 0x00U;
    ITS_OCTET               one = 0x01U;
    ITS_OCTET               status[] = {1,0,0,1,1,0,0,1,1};
    ITS_OCTET               prio[1] = {1};
    ITS_OCTET               key[] = {1,3,3,4,5};
    ITS_OCTET               key1[20] = {2,7,3,4,5,6,7,8,9};
    ITS_OCTET               key2[] = {3,5,3,4,5,6,7};
    ITS_OCTET               mindig[] = {0x69,0x64,0x63,0x60};
    ITS_USHORT              ushort  = 0x228U;
    ITS_USHORT              ushort1 = 0x229U;
    ITS_USHORT              ushort3 = 0x218U;
    ITS_USHORT              ushort4 = 0x219U;
    ITS_UINT                uint = 0x4321000;
    ITS_CHAR                itschar = 'x';
    char*                   digits = "7260686";
    char*                   dgts1  = "186213217260686";
    char*                   dgts2  = "1186213217260686";
    char*                   cdigit = "0729abc*#4395";
    char*                   dtmfchars = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    {
        BSSAP_L3MsgCnt                  l3mc;
        BSSAP_ChsEncAlg                 ceAlg;
     
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CipherModeComplete cmCplt;

        // populate Layer 3 Messge Contents, add it to the message
        l3mc.SetL3MsgCnt(key, sizeof(key));       

        cmCplt.AddIE(BSSAP_IEI_LAYER3_MESSAGE_CONTENT, &l3mc);

        
        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

        cmCplt.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmCplt) != ITS_SUCCESS)
        {
            cout << "Error encoding CipherModeComplete." << endl;
            return;
        }
        *datalen = len;

    }
}

void PrintData(SCCP_UserData *ud)
{
    if (ud != NULL)
    {
        ITS_OCTET data[1000];
        int len,i;

        cout << "UserData:" << endl;

        ud->GetUserData(data, len);
        if(len > 0)
        {
            for (i = 0; i < len; i++)
            {
                printf("%02x ",data[i]);
                if (!((i+1) % 20))
                {
                    cout << endl;
                }
            }
            if (((i+1) % 20))
            {
                cout << endl;
            }
            // PrintBSSAPMessage(data, len);
        }
        else
        {
            cout << "Length = 0" << endl;
        }
    }
    else
    {
        cout << "No UserData" << endl;
    }
}

}
