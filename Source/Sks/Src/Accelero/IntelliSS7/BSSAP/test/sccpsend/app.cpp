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


const int maxSize       = 240; 
ITS_HDR srchdr, remhdr;
ITS_UINT dstRefNum;
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
#define SEND_DT1_HODetect 38
#define SEND_DT1_HOComplete 39
#define SEND_DT1_TMSIReallocCmplt 40
#define SEND_DT1_AuthenticationRequest 41
#define SEND_DT1_AuthenticationResponse 42
#define SEND_DT1_IMSIDetachIndication 43
#define SEND_DT1_LocationUpdatingRequest 44
#define SEND_DT1_LocationUpdatingAccept 45
#define SEND_DT1_LocationUpdatingReject 46
#define SEND_DT1_TMSIReallocCommand 47
#define SEND_DT1_UserInformation 48
#define SEND_DT1_Hold 49
#define SEND_DT1_HoldAck 50
#define SEND_DT1_HoldReject 51
#define SEND_DT1_Retrieve 52
#define SEND_DT1_RetrieveAck 53
#define SEND_DT1_RetrieveReject 54
#define SEND_DT1_Disconnect 55
#define SEND_DT1_Release 56
#define SEND_DT1_ReleaseComplete 58
#define SEND_DT1_CongestionControl 59
#define SEND_DT1_Notify 60
#define SEND_DT1_StartDTMF 61
#define SEND_DT1_StartDTMFAck 62
#define SEND_DT1_StartDTMFReject 63
#define SEND_DT1_StopDTMF 64
#define SEND_DT1_StopDTMFAck 65
#define SEND_DT1_Status 66
#define SEND_DT1_StatusEnquiry 67
#define SEND_DT1_AuthenticationReject 68
#define SEND_DT1_IdentityRequest 69
#define SEND_DT1_IdentityResponse 70
#define SEND_DT1_CMServiceAccept 71
#define SEND_DT1_CMServiceReject 72
#define SEND_DT1_CMServiceAbort 73
#define SEND_DT1_CMServiceRequest 74
#define SEND_DT1_CMServiceReRequest 75
#define SEND_DT1_MMInformation 76
#define SEND_DT1_MMStatus 77
#define SEND_DT1_MMNull 78

#define SEND_DT1_Blocking 79
#define SEND_DT1_BlockingAck 80
#define SEND_DT1_Unblocking 81
#define SEND_DT1_UnblockingAck 82
#define SEND_DT1_HOCandidateEnq 83
#define SEND_DT1_HOCandidateRes 84
#define SEND_DT1_ResourceReq 85
#define SEND_DT1_HOSucceeded 86
#define SEND_DT1_ResourceInd 87
#define SEND_DT1_CGBlock 88
#define SEND_DT1_CGBlockAck 89
#define SEND_DT1_CGUBlock 90
#define SEND_DT1_CGUBlockAck 91
#define SEND_DT1_HOPerformed 92
    





#define SEND_DT2     2
#define DISCONNECT   3
//
// local subsystem for testing
//
#define LOCAL_SSN   254
#define REMOTE_SSN  8
#define LOCAL_PC    2
#define REMOTE_PC   4114
#define ISG_PC      4114

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
void BuildHandocerDetect(ITS_OCTET *databuf, int *datalen);
void BuildHandocerComplete(ITS_OCTET *databuf, int *datalen);
void BuildTMSIReallocComplete(ITS_OCTET *databuf, int *datalen);
void BuildAuthenticationRequest(ITS_OCTET *databuf, int *datalen);
void BuildAuthenticationResponse(ITS_OCTET *databuf, int *datalen);
void BuildIMSIDetachIndication(ITS_OCTET *databuf, int *datalen);
void BuildLocationUpdatingRequest(ITS_OCTET *databuf, int *datalen);
void BuildLocationUpdatingAccept(ITS_OCTET *databuf, int *datalen);
void BuildLocationUpdatingReject(ITS_OCTET *databuf, int *datalen);
void BuildTMSIReallocCommand(ITS_OCTET *databuf, int *datalen);
void BuildUserInformation(ITS_OCTET *databuf, int *datalen);
void BuildHold(ITS_OCTET *databuf, int *datalen);
void BuildHoldAck(ITS_OCTET *databuf, int *datalen);
void BuildHoldReject(ITS_OCTET *databuf, int *datalen);
void BuildRetrieve(ITS_OCTET *databuf, int *datalen);
void BuildRetrieveAck(ITS_OCTET *databuf, int *datalen);
void BuildRetrieveReject(ITS_OCTET *databuf, int *datalen);
void BuildDiscoonect(ITS_OCTET *databuf, int *datalen);
void BuildRelease(ITS_OCTET *databuf, int *datalen);
void BuildReleaseComplete(ITS_OCTET *databuf, int *datalen);
void BuildCongestionControl(ITS_OCTET *databuf, int *datalen);
void BuildStartDTMF(ITS_OCTET *databuf, int *datalen);
void BuildNotify(ITS_OCTET *databuf, int *datalen);
void BuildStartDTMFAck(ITS_OCTET *databuf, int *datalen);
void BuildStartDTMFReject(ITS_OCTET *databuf, int *datalen);
void BuildStopDTMF(ITS_OCTET *databuf, int *datalen);
void BuildStatus(ITS_OCTET *databuf, int *datalen);
void BuildStopDTMFAck(ITS_OCTET *databuf, int *datalen);
void BuildStatusEnquiry(ITS_OCTET *databuf, int *datalen);

void BuildAuthenticationReject(ITS_OCTET *databuf, int *datalen);
void BuildIdentityResponse(ITS_OCTET *databuf, int *datalen);
void BuildIdentityRequest(ITS_OCTET *databuf, int *datalen); 
void BuildCMServiceAccept(ITS_OCTET *databuf, int *datalen);
void BuildCMServiceReject(ITS_OCTET *databuf, int *datalen);
void BuildCMServiceAbort(ITS_OCTET *databuf, int *datalen);
void BuildCMServiceRequest(ITS_OCTET *databuf, int *datalen);
void BuildCMServiceReRequest(ITS_OCTET *databuf, int *datalen);
void BuildMMInformation(ITS_OCTET *databuf, int *datalen); 
void BuildMMStatus(ITS_OCTET *databuf, int *datalen);
void BuildMMNull(ITS_OCTET *databuf, int *datalen);

void BuildBlocking(ITS_OCTET *databuf, int *datalen);
void BuildBlockingAck(ITS_OCTET *databuf, int *datalen);
void BuildUnBlock(ITS_OCTET *databuf, int *datalen);
void BuildUnblockAck(ITS_OCTET *databuf, int *datalen);
void BuildHandoverCandidateEnquire(ITS_OCTET *databuf, int *datalen);
void BuildHOCandidateResponse(ITS_OCTET *databuf, int *datalen);
void BuildResourceReq(ITS_OCTET *databuf, int *datalen);
void BuildHOSucceded(ITS_OCTET *databuf, int *datalen);
void BuildResourceInd(ITS_OCTET *databuf, int *datalen);
void BuildCGBlock(ITS_OCTET *databuf, int *datalen);
void BuildCGBlockAck(ITS_OCTET *databuf, int *datalen);
void BuildCGUBlock(ITS_OCTET *databuf, int *datalen);
void BuildCGUBlockAck(ITS_OCTET *databuf, int *datalen);
void BuildHOPerformed(ITS_OCTET *databuf, int *datalen);




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
  workerPool->DispatchOnThread(thr, DISP_Dispatch_USER_CPP,
                            (void *)eng->GetCallbackStruct());
}

void MyPostFunc()
{
}

void
SccpThreadFunction(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle)
{
    ITS_Worker* worker = static_cast<ITS_Worker*> (thr);
    ITS_USHORT instance = worker->GetInstance();
    int ret;

    ret = SCCP_SendUserInService(handle, LOCAL_PC, LOCAL_SSN);
    if (ret != ITS_SUCCESS)
    {
       cout << "Error Sendin UIS" <<  endl;
       return ;
     }
     int cmdInput = 0;

     for (;;)
     {
         TEST_PrintCommand();

         scanf("%d", &cmdInput);
     
         if (cmdInput == TEST_EXIT)
         {
             printf("Exiting SCCP-M3UA-SCTP TEST Program...\n");
   
             break;
         }

         if (VALID_CHOICE(cmdInput))
         {    
             TEST_ExecuteCommand(cmdInput, handle, instance); 
             TEST_ExecuteCommand(BUILD_DATA, handle, instance); 
         }
         else
         {
             printf("Wrong Choice, Try again \n");
         }
     }

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
        ROUTE_AddApplication(instance, &srchdr);
        ITS_THROW_ASSERT(ret == ITS_SUCCESS);

        cout<<"Using Local Reference (SLR) ("<<srchdr.context.conref<<") "<<"For Establishing Connection"<<endl;

        SCCP_ConnectionRequest cr;

        SCCP_SourceLocalRef slr(srchdr.context.conref);
        cr.AddIE(&slr);

#ifdef CLASS_3
        SCCP_ProtocolClass pc(SCCP_PCLASS_3);
#else 
        SCCP_ProtocolClass pc(SCCP_PCLASS_2);
#endif
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
        for(ITS_OCTET i=0;i<len;i++)
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
        SCCP_DestinationLocalRef dlr(dstRefNum);
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
        SCCP_DestinationLocalRef dlr(dstRefNum);
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

            case BSSAP_CC_MSG_USER_INFORMATION:
                BuildUserInformation(data, &len);
                break;

            case BSSAP_CC_MSG_HOLD:
                BuildHold(data, &len);
                break;

            case BSSAP_CC_MSG_HOLD_ACKNOWLEDGE:
                BuildHoldAck(data, &len);
                break;

            case BSSAP_CC_MSG_HOLD_REJECT:
                BuildHoldReject(data, &len);
                break;

            case BSSAP_CC_MSG_RETRIEVE:
                BuildRetrieve(data, &len);
                break;

            case BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE:
                BuildRetrieveAck(data, &len);
                break;

            case BSSAP_CC_MSG_RETRIEVE_REJECT:
                BuildRetrieveReject(data, &len);
                break;

            case BSSAP_CC_MSG_DISCONNECT:
                BuildDiscoonect(data, &len);
                break;

            case BSSAP_CC_MSG_RELEASE:
                BuildRelease(data, &len);
                break;
 
            case BSSAP_CC_MSG_RELEASE_COMPLETE:
                BuildReleaseComplete(data, &len);
                break;

            case BSSAP_CC_MSG_CONGESTION_CONTROL:
                BuildCongestionControl(data, &len);
                break;

            case BSSAP_CC_MSG_NOTIFY:
                BuildNotify(data, &len);
                break;

            case BSSAP_CC_MSG_START_DTMF:
                BuildStartDTMF(data, &len);
                break;

            case BSSAP_CC_MSG_START_DTMF_ACK:
                BuildStartDTMFAck(data, &len);
                break;

            case BSSAP_CC_MSG_START_DTMF_REJECT:
                BuildStartDTMFReject(data, &len);
                break;

            case BSSAP_CC_MSG_STOP_DTMF :
                BuildStopDTMF(data, &len);
                break;
 
            case BSSAP_CC_MSG_STOP_DTMF_ACK:
                BuildStopDTMFAck(data, &len);
                break;

            case BSSAP_CC_MSG_STATUS:
                BuildStatus(data, &len);
                break;

            case BSSAP_CC_MSG_STATUS_ENQUIRY:
                BuildStatusEnquiry(data, &len);
                break;

            default:
                break;
            }
        }
        else if ( transparency == 2)
        {
            switch (bssapMsgType)
            {
            case BSSAP_MSG_TMSI_REALLOC_COMPLETE:
                BuildTMSIReallocComplete(data, &len);
                break;

            case BSSAP_MSG_AUTHENTICATION_REQUEST:
                BuildAuthenticationRequest(data, &len);
                break;

        case BSSAP_MSG_AUTHENTICATION_RESPONSE:
            BuildAuthenticationResponse(data, &len);
            break;

        case BSSAP_MSG_IMSI_DETACH_INDICATION:
            BuildIMSIDetachIndication(data, &len);
            break;

        case BSSAP_MSG_LOCATION_UPDATING_REQUEST:
                BuildLocationUpdatingRequest(data, &len);
            break;

        case BSSAP_MSG_LOCATION_UPDATING_ACCEPT:
                BuildLocationUpdatingAccept(data, &len);
            break;

        case BSSAP_MSG_LOCATION_UPDATING_REJECT:
                BuildLocationUpdatingReject(data, &len);
            break;

        case BSSAP_MSG_TMSI_REALLOC_COMMAND:
                BuildTMSIReallocCommand(data, &len);
            break;
            


        case BSSAP_MSG_AUTHENTICATION_REJECT:
                BuildAuthenticationReject(data, &len);
            break;                 

        case BSSAP_MSG_IDENTITY_RESPONSE:
                BuildIdentityResponse(data, &len);
            break;        

        case BSSAP_MSG_IDENTITY_REQUEST:
                BuildIdentityRequest(data, &len);
            break;

        case BSSAP_MSG_CM_SERVICE_ACCEPT:
                BuildCMServiceAccept(data, &len);
            break;  
 
         case BSSAP_MSG_CM_SERVICE_REJECT:
                BuildCMServiceReject(data, &len);
            break;    

         case BSSAP_MSG_CM_SERVICE_ABORT:
                BuildCMServiceAbort(data, &len);
            break;    

         case BSSAP_MSG_CM_SERVICE_REQUEST:
                BuildCMServiceRequest(data, &len);
            break;    

         case BSSAP_MSG_CM_REESTABLISHMENT_REQ:
                BuildCMServiceReRequest(data, &len);
            break;    

         case BSSAP_MSG_MM_INFORMATION:
                BuildMMInformation(data, &len);
            break;

         case BSSAP_MSG_MM_STATUS:
                BuildMMStatus(data, &len);
            break; 

         case BSSAP_MSG_MM_NULL:
                BuildMMNull(data, &len);
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
 
            case BSSAP_MSG_BLOCK:
                BuildBlocking(data, &len);
                break;

            case BSSAP_MSG_BLOCK_ACK:
                BuildBlockingAck(data, &len);
                break;

            case BSSAP_MSG_UNBLOCK:
                BuildUnBlock(data, &len);
                break;

            case BSSAP_MSG_UNBLOCK_ACK:
                BuildUnblockAck(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE:
                BuildHandoverCandidateEnquire(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE:
                BuildHOCandidateResponse(data, &len);
                break;

            case BSSAP_MSG_RESOURCE_REQUEST:
                BuildResourceReq(data, &len);
                break;

            case BSSAP_MSG_RESOURCE_INDICATION:
                BuildResourceInd(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_SUCCEEDED:
                BuildHOSucceded(data, &len);
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

            case BSSAP_MSG_CKT_GROUP_BLOCK:
                BuildCGBlock(data, &len);
                break;
 
            case BSSAP_MSG_CKT_GRP_BLK_ACK:
                BuildCGBlockAck(data, &len);
                break;

            case BSSAP_MSG_CKT_GRP_UNBLOCK:
                BuildClearComplete(data, &len);
                break;


            case BSSAP_MSG_CKT_GRP_UNBLKING_ACK:
                BuildPaging(data, &len);
                break;
 
            case BSSAP_MSG_HANDOVER_PERFORMED:
                BuildHOPerformed(data, &len);
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

            case BSSAP_MSG_HANDOVER_DETECT:
                BuildHandocerDetect(data, &len);
                break;

            case BSSAP_MSG_HANDOVER_COMPLETE:
                BuildHandocerComplete(data, &len);
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

        SCCP_DestinationLocalRef dlr(dstRefNum);
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

      char choice;
        cout << "DO YOU WANT TO WAIT FOR EVENT ->(y/n)";

         cin >> choice;
        if (choice == 'y')
        {
        TEST_WaitForEvent(handle, instance);
        }

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
       case SCCP_MSG_CC:    //Connection Confirm
       {
       SCCP_SourceLocalRef *slr = 
        (SCCP_SourceLocalRef *)msg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
       dstRefNum = slr->GetRefNum();

           cout<<"Recieved Connection Confirm Message DLR No:"
                                        << dstRefNum <<endl;
       break;
       }
       case SCCP_MSG_AK:    // Data ACK
       {
           printf("Received ACK message for DT2\n");
           break;
       }
       case SCCP_MSG_RLC:    // Release Confirm
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
    while (submenu) 
    {
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

                cout <<"   "<< SEND_DT1_UserInformation  
                     << ") Send User Information " << endl; 

                cout <<"   "<<SEND_DT1_Hold 
                     << ") Send Hold " << endl; 

                cout <<"   "<<SEND_DT1_HoldAck
                     << ") Send Hold Ack" << endl; 

                cout <<"   "<<SEND_DT1_HoldReject
                     << ") Send Hold Reject" << endl; 

                cout <<"   "<<SEND_DT1_Retrieve
                     << ") Send Retrieve " << endl; 

                cout <<"   "<<SEND_DT1_RetrieveAck
                     << ") Send RetrieveAck " << endl; 

                cout <<"   "<<SEND_DT1_RetrieveReject
                     << ") Send Retrieve Reject" << endl; 

                cout <<"   "<<SEND_DT1_Disconnect
                     << ") Send Disconnect" << endl; 

                cout <<"   "<<SEND_DT1_Release
                     << ") Send Release " << endl; 

                cout <<"   "<<SEND_DT1_ReleaseComplete 
                     << ") Send Release Complete" << endl; 

                cout <<"   "<<SEND_DT1_CongestionControl
                     << ") Send Congestion Control" << endl; 

                cout <<"   "<<SEND_DT1_Notify 
                     << ") Send Notify" << endl; 

                cout <<"   "<<SEND_DT1_StartDTMF
                     << ") Send Start DTMF " << endl; 

                cout <<"   "<<SEND_DT1_StartDTMFAck
                     << ") Send Start DTMF Ack " << endl; 

                cout <<"   "<<SEND_DT1_StartDTMFReject
                     << ") Send Start DTMF Reject" << endl; 

                cout <<"   "<<SEND_DT1_StopDTMF
                     << ") Send Stop DTMF" << endl; 

                cout <<"   "<<SEND_DT1_StopDTMFAck
                     << ") Send Stop DTMF Ack " << endl; 

                cout <<"   "<<SEND_DT1_Status 
                     << ") Send Status " << endl; 

                cout <<"   "<<SEND_DT1_StatusEnquiry
                     << ") Send Status Enquiry" << endl; 


                cout <<"   "<<SEND_DT1_Paging
                     << ") Send Paging" << endl; 

                cout <<"   "<<SEND_DT1_CipherModeCommand
                     << ") Send Cipher Mode Command" << endl; 

                cout <<"   "<<SEND_DT1_CipherModeComplete
                     << ") Send Cipher Mode Complete" << endl; 

                cout <<"   "<<SEND_DT1_CompleteLayer3Information
                     << ") Send Complete Layer3 Info" << endl; 

                cout <<"   "<<SEND_DT1_HODetect
                     << ") Send Handover Detect" << endl; 

                cout <<"   "<<SEND_DT1_HOComplete
                     << ") Send Handover Complete" << endl; 

                cout <<"   "<<SEND_DT1_TMSIReallocCmplt
                     << ") Send TMSI Reallocation Complete" << endl;

                cout <<"   "<<SEND_DT1_AuthenticationRequest
                     << ") Send AuthenticationRequest" << endl;

                cout <<"   "<<SEND_DT1_AuthenticationResponse
                     << ") Send AuthenticationResponse" << endl;

                cout <<"   "<<SEND_DT1_IMSIDetachIndication
                     << ") Send IMSI DetachIndication" << endl;

                cout <<"   "<<SEND_DT1_LocationUpdatingRequest
                     << ") Send LocationUpdatingRequest" << endl;

                
                cout <<"   "<<SEND_DT1_LocationUpdatingAccept
                     << ") Send LocationUpdatingAccept" << endl;

                cout <<"   "<<SEND_DT1_LocationUpdatingReject
                     << ") Send LocationUpdatingReject" << endl;

                    cout <<"   "<<SEND_DT1_TMSIReallocCommand
                     << ") Send TMSIReallocCommand" << endl;
                
                    cout <<"   "<<SEND_DT1_AuthenticationReject
                     << ") Send AuthenticationReject" << endl;


                    cout <<"   "<< SEND_DT1_IdentityRequest 
                     << ") Send IdentiyRequest" << endl;

                    cout <<"   "<<SEND_DT1_IdentityResponse 
                     << ") Send IdentityResponse" << endl;

                    cout <<"   "<<SEND_DT1_CMServiceAccept
                     << ") Send CMServiceAccept" << endl; 

                    cout <<"   "<<SEND_DT1_CMServiceReject
                     << ") Send CmServiceReject" << endl; 

                    cout <<"   "<<SEND_DT1_CMServiceAbort
                     << ") Send CMServiceAbort" << endl; 

                     cout <<"   "<<SEND_DT1_CMServiceRequest
                    << ") Send CMServiceRequest" << endl; 

                    cout <<"   "<<SEND_DT1_CMServiceReRequest
                     << ") Send CMServiceReRequest" << endl; 

                     cout <<"   "<<SEND_DT1_MMInformation
                     << ") Send MMInformation" << endl; 

                      cout <<"   "<<SEND_DT1_MMStatus
                     << ") Send MMStatus" << endl; 

                      cout <<"   "<<SEND_DT1_MMNull
                     << ") Send MMNull" << endl;                 

                    cout <<"   "<< SEND_DT1_Blocking 
                     << ") Send Blocking" << endl;

                    cout <<"   "<< SEND_DT1_BlockingAck 
                     << ") Send Bloacking Ack" << endl;

                    cout <<"   "<< SEND_DT1_Unblocking
                     << ") Send Unblocking" << endl; 

                    cout <<"   "<< SEND_DT1_UnblockingAck
                     << ") Send Unblocking Ack" << endl; 

                    cout <<"   "<<SEND_DT1_HOCandidateEnq
                     << ") Send Handover Candidate Enquiry" << endl; 

                     cout <<"   "<<SEND_DT1_HOCandidateRes
                    << ") Send Handover Candidate Request" << endl; 

                    cout <<"   "<<SEND_DT1_ResourceReq
                     << ") Send Resource Request" << endl; 

                    cout <<"   "<<SEND_DT1_ResourceInd
                     << ") Send Resource Indication" << endl; 

                     cout <<"   "<<SEND_DT1_HOSucceeded
                     << ") Send Handover Succeeded" << endl; 

                     cout <<"   "<<SEND_DT1_CGBlock
                    << ") Send Circuit Block " << endl; 

                    cout <<"   "<<SEND_DT1_CGBlockAck
                     << ") Send Circuit Block Ack" << endl; 

                    cout <<"   "<<SEND_DT1_CGUBlock
                     << ") Send Circuit UnBlock" << endl; 

                     cout <<"   "<<SEND_DT1_CGUBlockAck
                     << ") Send Circuit Unblock Ack" << endl; 

                     cout <<"   "<<SEND_DT1_HOPerformed
                     << ") Send Handover Performed" << endl; 


#endif
        cout <<"   "<<DISCONNECT <<") Release Connection"<<endl;

            cin >> msgType;

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


        case SEND_DT1_Blocking:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_BLOCK; 
        break;

        case SEND_DT1_BlockingAck:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_BLOCK_ACK; 
        break;

        case SEND_DT1_Unblocking :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_UNBLOCK; 
        break;

        case SEND_DT1_UnblockingAck:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_UNBLOCK_ACK;
        break;

        case SEND_DT1_HOCandidateEnq:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_CANDIDATE_ENQUIRE;
        break;

        case SEND_DT1_HOCandidateRes :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_CANDIDATE_RESPONSE;
        break;

        case SEND_DT1_ResourceReq:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_RESOURCE_REQUEST ;
        break;

        case SEND_DT1_ResourceInd:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_RESOURCE_INDICATION;
        break;

         case SEND_DT1_HOSucceeded:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_SUCCEEDED;
        break;

        case SEND_DT1_CGBlock :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CKT_GROUP_BLOCK;
        break;

        case SEND_DT1_CGBlockAck:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CKT_GRP_BLK_ACK;
        break;

        case SEND_DT1_CGUBlock :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CKT_GRP_UNBLOCK;
        break;

         case SEND_DT1_CGUBlockAck:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_CKT_GRP_UNBLKING_ACK;
        break;

         case SEND_DT1_HOPerformed:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_PERFORMED;
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

        case SEND_DT1_UserInformation :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_USER_INFORMATION; 
                transparency = 1;
        break;

        case SEND_DT1_Hold:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_HOLD; 
                transparency = 1;
        break;

             case SEND_DT1_HoldAck :
        msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_HOLD_ACKNOWLEDGE; 
                transparency = 1;
        break;

        case SEND_DT1_HoldReject :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_HOLD_REJECT;
                transparency = 1;
        break;

        case SEND_DT1_Retrieve :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_RETRIEVE;
                transparency = 1;
        break;

        case SEND_DT1_RetrieveAck :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_RETRIEVE_ACKNOWLEDGE;
                transparency = 1;
        break;

        case SEND_DT1_RetrieveReject :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_RETRIEVE_REJECT;
                transparency = 1;
        break;

         case SEND_DT1_Disconnect:
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_DISCONNECT;
                transparency = 1;
        break;

        case SEND_DT1_Release :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_RELEASE;
                transparency = 1;
        break;

        case SEND_DT1_ReleaseComplete: 
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_RELEASE_COMPLETE; 
                transparency = 1;
        break;

        case SEND_DT1_CongestionControl : 
                 msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_CONGESTION_CONTROL; 
                transparency = 1;
        break;

        case SEND_DT1_Notify : 
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_NOTIFY; 
                transparency = 1;
        break;

        case SEND_DT1_StartDTMF :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_START_DTMF;
                transparency = 1;
        break;

        case SEND_DT1_StartDTMFAck :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_START_DTMF_ACK;
                transparency = 1;
        break;

         case SEND_DT1_StartDTMFReject :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_START_DTMF_REJECT;
                transparency = 1;
        break;

        case SEND_DT1_StopDTMF :
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_STOP_DTMF;
                transparency = 1;
        break;

        case SEND_DT1_StopDTMFAck : 
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_STOP_DTMF_ACK; 
                transparency = 1;
        break;

        case SEND_DT1_Status : 
                 msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_STATUS; 
                transparency = 1;
        break;

        case SEND_DT1_StatusEnquiry : 
                msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_CC_MSG_STATUS_ENQUIRY; 
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

             case SEND_DT1_HODetect: 
        msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_DETECT; 
        break;

             case SEND_DT1_HOComplete: 
        msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_HANDOVER_COMPLETE; 
        break;

             case SEND_DT1_TMSIReallocCmplt:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_TMSI_REALLOC_COMPLETE;
                transparency = 2;
        break;
             case SEND_DT1_AuthenticationRequest:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_AUTHENTICATION_REQUEST;
                transparency = 2;
        break;
             case SEND_DT1_AuthenticationResponse:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_AUTHENTICATION_RESPONSE;
                transparency = 2;
        break;

             case SEND_DT1_IMSIDetachIndication:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_IMSI_DETACH_INDICATION;
                transparency = 2;
        break;


             case SEND_DT1_LocationUpdatingRequest:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_LOCATION_UPDATING_REQUEST;
                transparency = 2;
        break;
        

            case SEND_DT1_LocationUpdatingAccept:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_LOCATION_UPDATING_ACCEPT;
                transparency = 2;
        break;

            case SEND_DT1_LocationUpdatingReject:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_LOCATION_UPDATING_REJECT;
                transparency = 2;
        break;

            case SEND_DT1_TMSIReallocCommand:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_TMSI_REALLOC_COMMAND;
                transparency = 2;
        break;

               case SEND_DT1_CMServiceRequest:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_CM_SERVICE_REQUEST;
                transparency = 2;
        break;    

                 case SEND_DT1_CMServiceAbort:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_CM_SERVICE_ABORT;
                transparency = 2;
        break;    

                  case SEND_DT1_CMServiceReject:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_CM_SERVICE_REJECT;
                transparency = 2;
        break;    

                 case SEND_DT1_CMServiceAccept:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_CM_SERVICE_ACCEPT;
                transparency = 2;
        break;  



                 case SEND_DT1_CMServiceReRequest:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_CM_REESTABLISHMENT_REQ;
                transparency = 2;
        break;  

                    

                  case SEND_DT1_IdentityResponse:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_IDENTITY_RESPONSE;
                transparency = 2;
        break;    

                 case  SEND_DT1_IdentityRequest:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_IDENTITY_REQUEST;
                transparency = 2;
        break;    

                  case SEND_DT1_AuthenticationReject:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_AUTHENTICATION_REJECT;
                transparency = 2;
        break;    
 

            case SEND_DT1_MMInformation:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_MM_INFORMATION;
                transparency = 2; 
       break;

            case SEND_DT1_MMStatus:
                 msgType = SCCP_MSG_DT1;
                bssapMsgType = BSSAP_MSG_MM_STATUS; 
                transparency = 2;  
       break;
            case SEND_DT1_MMNull:
                 msgType = SCCP_MSG_DT1;
                 bssapMsgType = BSSAP_MSG_MM_NULL;
                transparency = 2;           

        break;

            
            
        

         case DISCONNECT:
        msgType = SCCP_MSG_RLSD;
        submenu = false;
        break;

         default:
        cout << "Invalid Response"<< endl;
          continue;
              }

           ret = TEST_BuildAndSendMsg(msgType, bssapMsgType, handle, 
                                      instance, transparency);
           if (ret != ITS_SUCCESS)
           {
               cout << "TEST --- > Error Occured Sending Request.\n";
           }
    }
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
    int                     i;  //loop counter
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
    //out.SetCellIDDisc(CI_CID_CGI);  //cgi
    //CI_CGI_SET_MCC_PCS(cid,ushort);
    //CI_CGI_SET_MNC_PCS(cid,octet);
    //CI_CGI_SET_LAC(cid,ushort);
    //CI_CGI_SET_CI(cid,ushort);
    //out.SetCellID(cid);

    //handReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &out);


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
    const int maxSize       = 240;
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        BSSAP_CallConfirmed ccon;

        ccon.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ccon.SetTIVal(TI_VALUE_3);                      //0x03

       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        pr.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        pr.SetTIVal(TI_VALUE_3);                      //0x03

       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Modify modify;
       
        modify.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        modify.SetTIVal(TI_VALUE_3);                      //0x03

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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_ModifyComplete mc;
       
        mc.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        mc.SetTIVal(TI_VALUE_3);                      //0x03

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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_ModifyReject mr;
       
        mr.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        mr.SetTIVal(TI_VALUE_3);                      //0x03

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

    }

}

void BuildUserInformation(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       

        // message
        BSSAP_UserInformation ui;
       
        ui.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ui.SetTIVal(TI_VALUE_3);                      //0x03
        ui.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        ui.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        ui.AddIE(BSSAP_IEI_CC_MORE_DATA, &md);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &ui) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildHold(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Hold ho;
       
        ho.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        ho.SetTIVal(TI_VALUE_3);                      //0x03
        ho.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &ho) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }
        *datalen = len;


    }
}


void BuildHoldAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HoldAck hack;
       
        hack.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        hack.SetTIVal(TI_VALUE_3);                      //0x03
        hack.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &hack) != ITS_SUCCESS)
        {
            cout << "Error encoding hold ack " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildHoldReject(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HoldReject hrej;
       
        hrej.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        hrej.SetTIVal(TI_VALUE_3);                      //0x03
        hrej.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        hrej.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &hrej) != ITS_SUCCESS)
        {
            cout << "Error encoding hold reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildRetrieve(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Retrieve rtrv;
       
        rtrv.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rtrv.SetTIVal(TI_VALUE_3);                      //0x03
        rtrv.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &rtrv) != ITS_SUCCESS)
        {
            cout << "Error encoding modify complete" << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildRetrieveAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_RetrieveAck rack;
       
        rack.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rack.SetTIVal(TI_VALUE_3);                      //0x03
        rack.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &rack) != ITS_SUCCESS)
        {
            cout << "Error encoding hold ack " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildRetrieveReject(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_RetrieveReject rrej;
       
        rrej.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rrej.SetTIVal(TI_VALUE_3);                      //0x03
        rrej.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        rrej.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &rrej) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildDiscoonect(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       

        // message
        BSSAP_Disconnect disc;
       
        disc.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        disc.SetTIVal(TI_VALUE_3);                      //0x03
        disc.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        disc.AddIE(BSSAP_IEI_CC_CAUSE, &cause);


        facility.SetFacilityData(buff, 0);
        disc.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        ITS_OCTET value = 1;
        progress.SetCodingLocationDesc(value, value, value);
        disc.AddIE(BSSAP_IEI_CC_PROGRESS_INDICATOR, &progress);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        disc.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &disc) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildRelease(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Release rel;
       
        rel.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        rel.SetTIVal(TI_VALUE_3);                      //0x03
        rel.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        rel.AddIE(BSSAP_IEI_CC_CAUSE, &cause);


        facility.SetFacilityData(buff, 0);
        rel.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        rel.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &rel) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildReleaseComplete(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_ReleaseComplete relcmp;
       
        relcmp.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        relcmp.SetTIVal(TI_VALUE_3);                      //0x03
        relcmp.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        relcmp.AddIE(BSSAP_IEI_CC_CAUSE, &cause);


        facility.SetFacilityData(buff, 0);
        relcmp.AddIE(BSSAP_IEI_CC_FACILITY, &facility);

        userTouser.SetProtocolDiscriminator(1);
        userTouser.SetUserInfo(buff, 5);
        relcmp.AddIE(BSSAP_IEI_CC_USER_USER, &userTouser);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &relcmp) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildCongestionControl(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_CongestionLevel   cl;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CongestionControl cong;
       
        cong.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        cong.SetTIVal(TI_VALUE_3);                      //0x03
        cong.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        cl.SetCongestionLevel(0);
        cong.AddIE(BSSAP_IEI_CC_CONGESTION_LEVEL_INTERNAL, &cl);

        cause.SetCodingLocationCause(1, 1, 1);
        cong.AddIE(BSSAP_IEI_CC_CAUSE, &cause);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cong) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStartDTMF(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StartDTMF sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        kpf.SetKeyValue(1);
        sdtmf.AddIE(BSSAP_IEI_CC_KEYPAD_FACILITY, &kpf);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildNotify(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_Notify   nfy;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_NotificationIndicator ni;
       
        nfy.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        nfy.SetTIVal(TI_VALUE_3);                      //0x03
        nfy.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        ni.SetNotifyIndicator(1);
        nfy.AddIE(BSSAP_IEI_CC_NOTIFICATION_INDICATOR_INTERNAL, &ni);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &nfy) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStartDTMFAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StartDTMFAck sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        kpf.SetKeyValue(1);
        sdtmf.AddIE(BSSAP_IEI_CC_KEYPAD_FACILITY, &kpf);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStartDTMFReject(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StartDTMFReject sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        sdtmf.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStopDTMF(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StopDTMF sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStopDTMFAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StopDTMFAck sdtmf;
       
        sdtmf.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        sdtmf.SetTIVal(TI_VALUE_3);                      //0x03
        sdtmf.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &sdtmf) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStatus(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_CallingPartyBCDNumber            cg;
        BSSAP_CallingPartySubAddress       cgs;
        BSSAP_CalledPartyBCDNumber            cd;
        BSSAP_CalledPartySubAddress       cds;
        BSSAP_UserToUser    userTouser;
        BSSAP_SSVersion     ss;
        BSSAP_Signal        signal;
        BSSAP_LowLevelCompInfo lc;
        BSSAP_HighLevelCompInfo hc;
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;
        BSSAP_CallState        cs;
        BSSAP_AuxState         as;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Status status;
       
        status.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        status.SetTIVal(TI_VALUE_3);                      //0x03
        status.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01


        cause.SetCodingLocationCause(1, 1, 1);
        status.AddIE(BSSAP_IEI_CC_CAUSE, &cause);

        cs.SetCodingAndState(1, 1);
        status.AddIE(BSSAP_IEI_CC_CALL_STATE_INTERNAL, &cs);

        as.SetAuxState(1);
        status.AddIE(BSSAP_IEI_CC_AUXILLARY_STATES, &as);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &status) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


    }
}

void BuildStatusEnquiry(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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
        BSSAP_MoreData          md;
        BSSAP_KeyPadFacility   kpf;


        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_StatusEnquiry se;
       
        se.SetProtDiscr(PD_CALL_CONTROL_MSGS);        //0x03
        se.SetTIVal(TI_VALUE_3);                      //0x03
        se.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &se) != ITS_SUCCESS)
        {
            cout << "Error encoding retrieve reject " << endl;
            return;
        }
        *datalen = len;


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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
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

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
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

void BuildBlocking(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    {
        BSSAP_CktIDCode                 cktId;
        BSSAP_Cse                       cs;
        BSSAP_ConRlsReq                 crReq;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Block blk;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        blk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        blk.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Connection Release Requested, add it to the message
        blk.AddIE(BSSAP_IEI_CONNECTION_RELEASE_REQUESTED, &crReq);
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &blk) != ITS_SUCCESS)
        {
            cout << "Error encoding Block." << endl;
            return;
        }
        *datalen = len;
    }
}
    
void BuildBlockingAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {
        BSSAP_CktIDCode                 cktId;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_BlockAcknowledge   blkAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x11

        blkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &blkAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Blocking Acknowledge." << endl;
            return;
        }

        *datalen = len;

    }
}

void BuildUnBlock(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {        
        BSSAP_CktIDCode                 cktId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_Unblock unblk;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        unblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);
    
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &unblk) != ITS_SUCCESS)
        {
            cout << "Error encoding Unblock." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildUnblockAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {
        BSSAP_CktIDCode                 cktId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_UnblockAcknowledge unblkAck;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        unblkAck.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &unblkAck) != ITS_SUCCESS)
        {
            cout << "Error encoding Unblock Acknowledge." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildHandoverCandidateEnquire(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    { 
        BSSAP_NumMSs                    nMs;
        BSSAP_CellIDList                ciList;
        BSSAP_CellID                    cellId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HandoverCandidateEnquire hcEnq;


        // populate Cell Identifier List, add it to the message
        nMs.SetNumHand(octet);                         //0x11

        hcEnq.AddIE(BSSAP_IEI_NUMBER_OF_MS, &nMs);


        // populate Cell Identifier List, add it to the message
        ciList.SetCellIDListDisc(CI_CID_CGI);
        //cgi
        CIL_CGI_SET_MCC_GSM_DCS(cid1,ushort);
        CIL_CGI_SET_MNC_GSM_DCS(cid1,octet);
        CIL_CGI_SET_LAC(cid1,ushort);
        CIL_CGI_SET_CI(cid1,ushort);
//        ciList.AddCellID(cid1);
        for(i = 0; i < 2; i++)
        {
            ciList.SetCellID(cid1, i);
        }

        hcEnq.AddIE(BSSAP_IEI_CELL_IDENTIFIER_LIST, &ciList);



        // populate Cell Identifier, add it to the message
        int disc = -1;

        cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC" << endl;
        cout << "[2] CI" << endl;
        cout << "[3] PLMN_LAC_RNC" << endl;
        cout << "[4] RNC" << endl;
        cout << "[5] LAC_RNC" << endl;
        cout << "[6] SAI" << endl;
        cout << "-->" << endl;
        cin >> disc;


        if (disc == 0)
        {
            cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
            CI_CGI_SET_MCC_PCS(cid,ushort);
            CI_CGI_SET_MNC_PCS(cid,ushort);
            CI_CGI_SET_LAC(cid,ushort);
            CI_CGI_SET_CI(cid,ushort); 
        }
        else if (disc == 1)
        {
            cellId.SetCellIDDisc(CI_CID_LAC);  //lac
            CI_LACCI_SET_LAC(cid,ushort);
            CI_LACCI_SET_CI(cid,ushort);
        }
        else if (disc == 2)
        {
            cellId.SetCellIDDisc(CI_CID_CI);  //ci
            CI_CI_SET_CI(cid,ushort);
        }
        else if (disc == 3)
        {
            cellId.SetCellIDDisc(CI_CID_PLMN_LAC_RNC);  //plmn_lac_rnc
            CI_PLR_SET_MCC(cid,ushort);
            CI_PLR_SET_MNC(cid,octet);
            CI_PLR_SET_LAC(cid,ushort);
            CI_PLR_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 4)
        {
            cellId.SetCellIDDisc(CI_CID_RNC);  // rnc
         
            CI_RNC_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 5)
        {
            cellId.SetCellIDDisc(CI_CID_LAC_RNC);  // lac_rnc
            
            CI_LR_SET_LAC(cid,ushort);
            CI_LR_SET_RNC_ID(cid,ushort); 
        }
        else if (disc == 6)
        {
            cellId.SetCellIDDisc(CI_CID_SAI);  // sai
            CI_SAI_SET_MCC(cid,ushort);
            CI_SAI_SET_MNC(cid,ushort);
            CI_SAI_SET_LAC(cid,ushort);
            CI_SAI_SET_SAC(cid,ushort); 
        }

        cellId.SetCellID(cid);

        hcEnq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &hcEnq) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Candidate Enquire." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildHOCandidateResponse(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    { 
        BSSAP_NumMSs                    nMs;
        BSSAP_CellID                    cellId;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HandoverCandidateResponse hcRsp;

        // populate Cell Identifier List, add it to the message
        nMs.SetNumHand(octet);

        hcRsp.AddIE(BSSAP_IEI_NUMBER_OF_MS, &nMs);


        // populate Cell Identifier, add it to the message

        int disc = -1;

        cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC" << endl;
        cout << "[2] CI" << endl;
        cout << "-->" << endl;
        cin >> disc;


        if (disc == 0)
        {
            cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
            CI_CGI_SET_MCC_PCS(cid,ushort);
            CI_CGI_SET_MNC_PCS(cid,octet);
            CI_CGI_SET_LAC(cid,ushort);
            CI_CGI_SET_CI(cid,ushort); 
        }
        else if (disc == 1)
        {
            cellId.SetCellIDDisc(CI_CID_LAC);  //lac
            CI_LACCI_SET_LAC(cid,ushort);
            CI_LACCI_SET_CI(cid,ushort);
        }
        else if (disc == 2)
        {
            cellId.SetCellIDDisc(CI_CID_CI);  //ci
            CI_CI_SET_CI(cid,ushort);
        }


        cellId.SetCellID(cid);

        hcRsp.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 
 
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &hcRsp) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Candidate Response." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildResourceReq(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {         
        BSSAP_Period                    prd;
        BSSAP_CellID                    cellId;
        BSSAP_ResIndMethod              riMthd;
        BSSAP_ExtResInd                 erInd;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_ResourceRequest resReq;

        // populate Periodicity, add it to the message
        prd.SetPeriod(octet);                          //0x11

        resReq.AddIE(BSSAP_IEI_PERIODICITY, &prd);


        // populate Resource Indication Method, add it to the message
        riMthd.SetResIndMethod(RIM_SUBCLAUSE_3);          //0x03

        resReq.AddIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, &riMthd);
        

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_GSM_DCS(cid,ushort);
        CI_CGI_SET_MNC_GSM_DCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        resReq.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Extended Resource Indicator, add it to the message
        erInd.SetTARR(1);     
        erInd.SetSM(0);

        resReq.AddIE(BSSAP_IEI_EXTENDED_RESOURCE_INDICATOR, &erInd);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &resReq) != ITS_SUCCESS)
        {
            cout << "Error encoding Resource Request." << endl;
            return;
        }
        *datalen = len;
    }
}

void BuildResourceInd(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {             
        BSSAP_ResIndMethod              riMthd;
        BSSAP_CellID                    cellId;
        BSSAP_ResAvail                  resAvail;
        BSSAP_TotResAcc                 tra;        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_ResourceIndication resInd;

        // populate Resource Indication Method, add it to the message
        riMthd.SetResIndMethod(RIM_SUBCLAUSE_1);          //0x00

        resInd.AddIE(BSSAP_IEI_RESOURCE_INDICATION_METHOD, &riMthd);
        

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        resInd.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 


        // populate Resource Available, add it to the message
        resAvail.SetNumFullHalf(ushort, ushort1, 0); 
        resAvail.SetNumFullHalf(ushort3, ushort4, 1); 
        resAvail.SetNumFullHalf(ushort, ushort1, 2);
        resAvail.SetNumFullHalf(ushort3, ushort4, 3);
        resAvail.SetNumFullHalf(ushort3, ushort4, 4);

        resInd.AddIE(BSSAP_IEI_RESOURCE_AVAILABLE, &resAvail);


        // populate Total Resource Accessible, add it to the message
        tra.SetFullRate(ushort);     
        tra.SetHalfRate(ushort1);

        resInd.AddIE(BSSAP_IEI_TOTAL_RESOURCE_ACCESSIBLE, &tra);

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &resInd) != ITS_SUCCESS)
        {
            cout << "Error encoding Resource Indication." << endl;
            return;
        }

    }
}

void BuildHOSucceded(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HandoverSucceeded handSuc;

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &handSuc) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Succeeded." << endl;
            return;
        }

        *datalen = len;

    }
}

void BuildHandocerDetect(ITS_OCTET *databuf, int *datalen)
{
        // encode/decode buffer
        int maxSize       = 240;

        // message
        BSSAP_HandoverDetect handDet;

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &handDet) != ITS_SUCCESS)
        {
            cout << "Error encoding HandoverDetect." << endl;
            return;
        }
        *datalen = len;

        // print the user data
}

void BuildHandocerComplete(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;

    {        
        BSSAP_RRcause                   rrCs;
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_HandoverComplete handCmp;

        // populate RR Cause, add it to the message
        rrCs.SetRRCause(RRC_PREEMPTIVE_RELEASE);             //0x05

        handCmp.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &handCmp) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Complete." << endl;
            return;
        }
        *datalen = len;

    }
}


void BuildCGBlock(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {
        BSSAP_Cse                      cs;
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList; 
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupBlock cgBlk;


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        cgBlk.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code List, add it to the message
        cicList.SetRange(20); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgBlk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cgBlk) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Block." << endl;
            return;
        }
        *datalen = len;
    }
}

void BuildCGBlockAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {  
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList; 

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupBlockAcknowledge cgba;


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x11

        cgba.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);

        // populate Circuit Identity Code, add it to the message

        cicList.SetRange(255); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgba.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cgba) != ITS_SUCCESS)
        {
            cout << "Error encoding Parameter CircuitGroupBlockAck." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildCGUBlock(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {  
        BSSAP_Cse                      cs;
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList; 
        

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupUnblock cgUnblk;


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_TRAFFIC_LOAD, C_INVALID_CELL);    //0x28U,0x27U
//        cs.SetNationalCause(C_CLASS_INTERWORKING, octet);

        cgUnblk.AddIE(BSSAP_IEI_CAUSE, &cs); 


        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgUnblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code, add it to the message

        cicList.SetRange(2); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgUnblk.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cgUnblk) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Unblock." << endl;
            return;
        }
        *datalen = len;
    }

}


void BuildCGUBlockAck(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    { 
        BSSAP_CktIDCode                cktId;
        BSSAP_CktIDCodeList            cicList;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_CircuitGroupUnblockAck cgua;

        // populate Circuit Identity Code, add it to the message
        cktId.SetPCMID(ushort);                             //0x228
        cktId.SetTimeslot(octet);                           //0x04

        cgua.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE, &cktId);


        // populate Circuit Identity Code List, add it to the message
        cicList.SetRange(2); 

        int range = cicList.GetRange() + 1;

        for (int i = 0; i < range; i++)
        {
            if (i & 1)
            {
                cicList.SetStatusBit(0, i); 
            }
            else
            {
                cicList.SetStatusBit(1, i); 
            }
        }

//        cicList.SetStatus(status, sizeof(status));    // 9 data

        cgua.AddIE(BSSAP_IEI_CIRCUIT_IDENTITY_CODE_LIST, &cicList);
        
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cgua) != ITS_SUCCESS)
        {
            cout << "Error encoding Circuit Group Unblock Ack." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildHOPerformed(ITS_OCTET *databuf, int *datalen)
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
    char                   digits[] = "7260686";
    char                   dgts1[]  = "186213217260686";
    char                   dgts2[]  = "1186213217260686";
    char                   cdigit[] = "0729abc*#4395";
    char                   dtmfchars[] = "#729*4395";
    const int maxSize       = 240;
    int                     i;  //loop counter
    BSSAP_CellIDType        cid;  
    BSSAP_CellIDT           cid1;
    bool                    isExt = 1;
    BSSAP_CircuitPool       cpool;
    BSSAP_ResSitnElmnt      rse;
    {                  
        BSSAP_Cse                       cs;
        BSSAP_CellID                    cellId;
        BSSAP_ChsChan                   chsChan; 
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_SpchVer                   spchVer;
        BSSAP_LsaId                     lsaid;

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_HandoverPerformed handPfm;


        // populate Cause, add it to the message
        cs.SetCause(isExt, C_CIPHER_ALGORITHM_UNSUPPORTED, C_INVALID_CELL); //0x40U,0x27U
        cs.SetNationalCause(C_CLASS_SERVICE_UNAVAILABLE, octet);

        handPfm.AddIE(BSSAP_IEI_CAUSE, &cs); 

        // populate Cell Identifier, add it to the message
        cellId.SetCellIDDisc(CI_CID_CGI);  //cgi
        CI_CGI_SET_MCC_PCS(cid,ushort);
        CI_CGI_SET_MNC_PCS(cid,octet);
        CI_CGI_SET_LAC(cid,ushort);
        CI_CGI_SET_CI(cid,ushort);        
        cellId.SetCellID(cid);

        handPfm.AddIE(BSSAP_IEI_CELL_IDENTIFIER, &cellId); 

              
        // populate Chosen Channel, add it to the message
        chsChan.SetChan(CC_CH_SPEECH);                      //0x09
        chsChan.SetChanMode(CC_CM_SDCCH);                   //0x01 
        
        handPfm.AddIE(BSSAP_IEI_CHOSEN_CHANNEL, &chsChan);


        // populate Chosen Encryption Algorithm, add it to the message
        ceAlg.SetAlgorithmID(CEA_GSM_A_5_2);                //0x03

        handPfm.AddIE(BSSAP_IEI_CHOSEN_ENCRYPTION_ALGORITHM, &ceAlg);

  
        // populate Speech Version, add it to the message
        spchVer.SetSpchVerID(SV_GSM_FULL_RATE_VER1);         //0x01

        handPfm.AddIE(BSSAP_IEI_SPEECH_VERSION, &spchVer);

        // populate LSA Identifier, add it to the message
        lsaid.SetLSAIDBit1(0x01); 
        lsaid.SetLSAID(0x432111); 

        handPfm.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);
 
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &handPfm) != ITS_SUCCESS)
        {
            cout << "Error encoding Handover Performed." << endl;
            return;
        }
        *datalen = len;

    }
}

void BuildTMSIReallocComplete(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_TMSIReallocComplete reallocCplt;

        reallocCplt.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        
        reallocCplt.SetTIVal(TI_VALUE_3);                      //0x03 

    int len;
    if (BSSAP_Message::Encode(databuf, len, &reallocCplt) != ITS_SUCCESS)
    {
        cout << "Error encoding TMSIReallocComplete." << endl;
        return;
    }
    *datalen = len;
}

void BuildAuthenticationRequest(ITS_OCTET *databuf, int *datalen)
{
    
    ITS_OCTET type=0x01U;
    ITS_OCTET pararand[16]={88,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    BSSAP_AuthenticationRequest AuthReqst;
    BSSAP_CypheringKeySequence cks;
    BSSAP_ParameterRand pr;

    cks.SetCypheringKeySequence(type);

    pr.SetParameterRand(pararand);

        AuthReqst.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        AuthReqst.SetTIVal(TI_VALUE_3);                      //0x03   

    AuthReqst.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cks);
    AuthReqst.AddIE(BSSAP_IEI_PARAMETER_RAND, &pr);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &AuthReqst) != ITS_SUCCESS)
    {
        cout << "Error encoding AuthenticationRequest." << endl;
        return;
    }
    *datalen = len;
}

void BuildAuthenticationResponse(ITS_OCTET *databuf, int *datalen)
{
    

    ITS_OCTET parasres[4]={88,77,66,44};
    
    BSSAP_AuthenticationResponse AuthResp;
    BSSAP_ParameterSres psr;
    psr.SetParameterSres(parasres);


        AuthResp.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        AuthResp.SetTIVal(TI_VALUE_3);                      //0x03  

    AuthResp.AddIE(BSSAP_IEI_PARAMETER_SRES, &psr);


    int len;
    if (BSSAP_Message::Encode(databuf, len, &AuthResp) != ITS_SUCCESS)
    {
        cout << "Error encoding AuthenticationResponse." << endl;
        return;
    }
    *datalen = len;
}


void BuildIMSIDetachIndication(ITS_OCTET *databuf, int *datalen)
{
    
    BSSAP_ClassmarkInfo1            cmInfo1;

    // populate Classmark Info Type1, add it to the message
    cmInfo1.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo1.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo1.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo1.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
 

    
    BSSAP_MobileID                    mid;
    char setdig[]="123";
    int leng=3;
    ITS_OCTET setdig2[]={1,2,3};
    int nDigits=3;


    mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
    mid.SetIdenCDig(setdig, leng);    
    //mid.SetIdenBDig(setdig2,nDigits);


    BSSAP_IMSIDetachIndication IMSIDI;

        IMSIDI.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x05
        IMSIDI.SetTIVal(TI_VALUE_3);                      //0x03      

    IMSIDI.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, &cmInfo1);
    IMSIDI.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &IMSIDI) != ITS_SUCCESS)
    {
        cout << "Error encoding IMSI Detach Indication." << endl;
        return;
    }
    *datalen = len;
}

void BuildLocationUpdatingRequest(ITS_OCTET *databuf, int *datalen)
{
    
    BSSAP_LocationUpdatingType         lutype;
    BSSAP_CypheringKeySequence            cks;
    BSSAP_LocationAreaID                lai;
    BSSAP_ClassmarkInfo1            cmInfo1;
    BSSAP_MobileID                        mid;

    ITS_OCTET MCC[]={0x11,0x12};
    ITS_OCTET MNC[]={0x21,0x22};
    ITS_OCTET LAC[]={0x31,0x32};
    ITS_OCTET LAI[]={0x11, 0x22, 0x33, 0x44, 0x55};

    lutype.SetLocationUpdatingType(0x01U);
    cks.SetCypheringKeySequence(0x00U);
    lai.SetLocationAreaID(LAI);
    //lai.SetLocationAreaIDMNC(MNC);
    //lai.SetLocationAreaIDLAC(LAC);



    // populate Classmark Info Type1, add it to the message
    cmInfo1.SetRFPowerCap(CIT2_RF_POWER_CAP_CLASS2);    //0x01
    cmInfo1.SetA51(CIT2_A5_1_IS_AVAILABLE);             //0x00
    cmInfo1.SetESIND(CIT2_ES_IND_IS_IMPLEMENTED);       //0x00
    cmInfo1.SetRevLevel(CIT2_REV_LEVEL_PHASE_2);        //0x01
 

    
    
        char setdig[]="1234567";
        int leng=7;
        ITS_OCTET setdig2[]={3,2,1};
        int nDigits=6;



        mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
        mid.SetIdenCDig(setdig, leng);
    




    //mid.SetIdenBDig(setdig2,nDigits);


    BSSAP_LocationUpdatingRequest LUR;

        LUR.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        LUR.SetTIVal(TI_VALUE_3);                      //0x03      

    LUR.AddIE(BSSAP_IEI_LOCATION_UPDATING_TYPE, &lutype);
    LUR.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cks);
    LUR.AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &lai);
    LUR.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE1, &cmInfo1);
    LUR.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &LUR) != ITS_SUCCESS)
    {
        cout << "Error encoding LocationUpdatingRequest." << endl;
        return;
    }
    *datalen = len;
}

void BuildLocationUpdatingAccept(ITS_OCTET *databuf, int *datalen)
{

        
    
        BSSAP_LocationAreaID            lai;    
    BSSAP_MobileID                        mid;
    BSSAP_FollowOnProceed                fop;
    BSSAP_CTSPermission                    ctsp;


        ITS_OCTET MCC[]={0x11,0x12};
        ITS_OCTET MNC[]={0x21,0x22};
        ITS_OCTET LAC[]={0x31,0x32};

        ITS_OCTET LAI[]={0x11, 0x22, 0x33, 0x44, 0x55};

        lai.SetLocationAreaIDMCC(MCC);

    
    char setdig[]="1234567";
    int leng=7;
    ITS_OCTET setdig2[]={3,2,1};
    int nDigits=6;



    mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
    mid.SetIdenCDig(setdig, leng);    
    //mid.SetIdenBDig(setdig2,nDigits);


    BSSAP_LocationUpdatingAccept LUA;

        LUA.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        LUA.SetTIVal(TI_VALUE_3);                      //0x03      

        LUA.AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &lai);
    LUA.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);
    LUA.AddIE(BSSAP_IEI_FOLLOW_ON_PROCEED, &fop);
    LUA.AddIE(BSSAP_IEI_CTS_PERMISSION, &ctsp);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &LUA) != ITS_SUCCESS)
    {
        cout << "Error encoding LocationUpdatingAccept." << endl;
        return;
    }
    *datalen = len;
}

void BuildLocationUpdatingReject(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_RRcause                       cs;

    BSSAP_LocationUpdatingReject luRej;

        luRej.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        luRej.SetTIVal(TI_VALUE_3);                      //0x03  

    // populate Cause, add it to the message
    cs.SetRRCause(0x02U);    

    luRej.AddIE(BSSAP_IEI_RR_CAUSE, &cs);

    int len;
    if (BSSAP_Message::Encode(databuf, len, &luRej) != ITS_SUCCESS)
    {
        cout << "Error encoding LocationUpdatingReject." << endl;
        return;
    }
    *datalen = len;
}

void BuildTMSIReallocCommand(ITS_OCTET *databuf, int *datalen)
{
    BSSAP_TMSIReallocCommand reallocCmd;

        reallocCmd.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);        //0x03
        reallocCmd.SetTIVal(TI_VALUE_3);                      //0x03  

    BSSAP_LocationAreaID                lai;
    

ITS_OCTET LAI[]={0x11, 0x22, 0x33, 0x44, 0x55};

    lai.SetLocationAreaID(LAI);                     
    BSSAP_MobileID                        mid;

    char setdig[]="123";
    int leng=3;
    ITS_OCTET setdig2[]={3,2,1};
    int nDigits=3;



    mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
    mid.SetIdenCDig(setdig, leng);    
//    mid.SetIdenBDig(setdig2,nDigits);



    reallocCmd.AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &lai);
    reallocCmd.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);



    int len;
    if (BSSAP_Message::Encode(databuf, len, &reallocCmd) != ITS_SUCCESS)
    {
        cout << "Error encoding TMSIReallocCommand." << endl;
        return;
    }
    *datalen = len;
}


void BuildAuthenticationReject(ITS_OCTET *databuf, int *datalen)
{
 // message
        BSSAP_AuthenticationReject arej;

        arej.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        arej.SetTIVal(TI_VALUE_3);                      //0x03    

    int len;
    if (BSSAP_Message::Encode(databuf, len, &arej) != ITS_SUCCESS)
    {
        cout << "Error encoding AuthenticationReject." << endl;
        return;
    }
    *datalen = len;
}
void BuildIdentityRequest(ITS_OCTET *databuf, int *datalen)
{
 BSSAP_IdentityType                idtype;   // Mandatory

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_IdentityRequest idreq;

        idreq.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        idreq.SetTIVal(TI_VALUE_3);                      //0x03
        
        idtype.SetIdentityType(0x02);

        idreq.AddIE(BSSAP_IEI_IDENTITY_TYPE, &idtype);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &idreq) != ITS_SUCCESS)
        {
            cout << "Error encoding Identity Request." << endl;
            return;
        }                      
        *datalen = len;

}
void BuildIdentityResponse(ITS_OCTET *databuf, int *datalen)
{

 BSSAP_MobileID                mid;   // Mandatory

        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_IdentityResponse idres;

        idres.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        idres.SetTIVal(TI_VALUE_3);                      //0x03

        // populate MOBILE IDENTITY, add it to the message 
        char setdig[]="123";
        int leng=3;
        ITS_OCTET setdig2[]={1,2,3};
        int nDigits=3;


        mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
        mid.SetIdenCDig(setdig, leng);
        mid.SetTypeIdentity(0x02);

        idres.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);


        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &idres) != ITS_SUCCESS)
        {
            cout << "Error encoding Identity Request." << endl;
            return;
        }                      
        *datalen = len;
}
void BuildCMServiceAccept(ITS_OCTET *databuf, int *datalen)
{
          // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CMServiceAccept cmsa;

        cmsa.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsa.SetTIVal(TI_VALUE_3);                      //0x03
        cmsa.SetTIFlag(TI_FLAG_TO_SIDE);                //0x01
        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsa) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Accept ." << endl;
            return;
        }        
        *datalen = len;
}
void BuildCMServiceReject(ITS_OCTET *databuf, int *datalen)
{
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CMServiceReject cmsr;

        cmsr.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsr.SetTIVal(TI_VALUE_3);                      //0x03

         BSSAP_RRcause                   rrCs;

        // populate Cause, add it to the message
        rrCs.SetRRCause(0x02);

        cmsr.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

        int len;
        // build the message                    
        if (BSSAP_Message::Encode(databuf, len, &cmsr) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Reject ." << endl;
            return;
        }
        *datalen = len;
                           
} 

void BuildCMServiceAbort(ITS_OCTET *databuf, int *datalen)
{
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CMServiceAbort cmsa;

        cmsa.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsa.SetTIVal(TI_VALUE_3);                      //0x03

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsa) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Abort ." << endl;
            return;
        }                         
        *datalen = len;
}

void BuildCMServiceRequest(ITS_OCTET *databuf, int *datalen)
{
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CMServiceRequest cmsr;



        cmsr.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsr.SetTIVal(TI_VALUE_3);                      //0x03


        BSSAP_CMServiceType cmt;
        cmt.SetCMServiceType(0x02);
        BSSAP_CypheringKeySequence cks;
        cks.SetCypheringKeySequence(0x01);
        BSSAP_ClassmarkInfo2 cmInfo2;      

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
        
        BSSAP_MobileID     mid;
        char setdig[]="123";
        int leng=3;
        mid.SetOddEvenInd(MI_ODD_DIGITS);
        mid.SetTypeIdentity(MI_IMSI);
        mid.SetIdenCDig(setdig, leng);
        mid.SetTypeIdentity(0x02);


        cmsr.AddIE(BSSAP_IEI_CM_SERVICE_TYPE, &cmt);
        cmsr.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cks);
        cmsr.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);
        cmsr.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsr) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Service Request ." << endl;
            return;
        }                
        *datalen = len;

}

void BuildCMServiceReRequest(ITS_OCTET *databuf, int *datalen)
{
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

        buff[0] = 1;
        buff[1] = 2;
        buff[2] = 3;
        buff[3] = 4;
        buff[4] = 5;
        buff[5] = 6;
       
        // message
        BSSAP_CMReestablishmentReq cmsr;



        cmsr.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsr.SetTIVal(TI_VALUE_3);                      //0x03


        BSSAP_CypheringKeySequence cks;
        cks.SetCypheringKeySequence(0x01);
        BSSAP_ClassmarkInfo2 cmInfo2;    
        
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

        BSSAP_MobileID     mid;
        char* setdig="123";
        int leng=3;
        mid.SetOddEvenInd(MI_ODD_DIGITS);         
        mid.SetTypeIdentity(MI_IMSI);
        mid.SetIdenCDig(setdig, leng);
        mid.SetTypeIdentity(0x02);

        BSSAP_LocationAreaID                lai;
        ITS_OCTET LAI[]={0x11, 0x22, 0x33, 0x44, 0x55};
        lai.SetLocationAreaID(LAI);

        cmsr.AddIE(BSSAP_IEI_CYPHERING_KEY_SEQUENCE, &cks);
        cmsr.AddIE(BSSAP_IEI_CLASSMARK_INFORMATION_TYPE2, &cmInfo2);
        cmsr.AddIE(BSSAP_IEI_MOBILE_IDENTITY, &mid);
        cmsr.AddIE(BSSAP_IEI_LOCATION_AREA_IDENTIFIER, &lai);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsr) != ITS_SUCCESS)
        {
            cout << "Error encoding CM Reestablishment Request ." << endl;
            return;
        }                  
        *datalen = len;
 
}
void BuildMMInformation(ITS_OCTET *databuf, int *datalen)
{

 // encode/decode buffer
        ITS_OCTET buff[maxSize];
ITS_OCTET               octet = 0x11U;  
ITS_USHORT              ushort  = 0x228U;  

        // message
        BSSAP_MMInformation mmi;

        mmi.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        mmi.SetTIVal(TI_VALUE_3);                      //0x03

        int len;
        BSSAP_NetElementID        netId1;  // Mandatory
        BSSAP_NetElementID        netId2;  // Mandatory

        BSSAP_NetID  netid = {0};


        // populate Network Element Identity, add it to the message
        int disc = -1;               

 cout << "Select Discriminator." <<endl;
        cout << "[0] CGI" << endl;
        cout << "[1] LAC_CI" << endl;
        cout << "[2] LAI" << endl;
        cout << "[3] LAC" << endl;
        cout << "-->" << endl;
        cin >> disc;


        if (disc == 0)
        {
            netId1.SetIDDisc(NEI_ID_CGI);  //cgi
            NEI_CGI_SET_MCC(netid,ushort);
            NEI_CGI_SET_MNC(netid,octet);
            NEI_CGI_SET_LAC(netid,ushort);
            NEI_CGI_SET_CI(netid,ushort);
        }                                    
 else if (disc == 1)
        {
            netId1.SetIDDisc(NEI_ID_LAC_CI);             //0x01

            // LAC+CI
            NEI_LACCI_SET_LAC(netid,ushort);
            NEI_LACCI_SET_CI(netid,ushort);
        }
        else if (disc == 2)
        {
            netId1.SetIDDisc(NEI_ID_LAI);             //0x04

            // LAI -- MCC + MNC + LAC
            NEI_LAI_SET_MCC(netid,ushort);
            NEI_LAI_SET_MNC(netid,octet);
            NEI_LAI_SET_LAC(netid,ushort);
        }                         
 else if (disc == 3)
        {
            netId1.SetIDDisc(NEI_ID_LAC);             //0x05

            // LAC
            NEI_LAC_SET_LAC(netid,ushort);
        }

        netId1.SetNetElementID(netid);
        mmi.AddIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, &netId1);


        netId2.SetIDDisc(NEI_ID_LAI);             //0x04

        // LAI -- MCC + MNC + LAC
        NEI_LAI_SET_MCC(netid,ushort);
        NEI_LAI_SET_MNC(netid,octet);
        NEI_LAI_SET_LAC(netid,ushort);

        netId2.SetNetElementID(netid);       

 mmi.AddIE(BSSAP_IEI_NETWORK_ELEMENT_IDENTITY, &netId2);

        BSSAP_TimeZone tz;
        tz.SetTimeZone(0x02);
        //mmi.AddIE(BSSAP_IEI_TIME_ZONE, &tz);

        BSSAP_TimeZoneTime tzt;
        tzt.SetTimeZoneYear(0x02);
        tzt.SetTimeZoneMonth(0x02);
        tzt.SetTimeZoneDay(0x02);
        tzt.SetTimeZoneHour(0x02);
        tzt.SetTimeZoneMinute(0x02);
        tzt.SetTimeZoneSecond(0x02);
        tzt.SetTimeZoneZone(0x02);


        //mmi.AddIE(BSSAP_IEI_TIME_ZONE_TIME, &tzt);
                                                     
     BSSAP_LsaId                     lsaid;
         lsaid.SetLSAIDBit1(0x01);
        lsaid.SetLSAID(0x432111);

        mmi.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);


        // build the message
        if (BSSAP_Message::Encode(databuf, len, &mmi) != ITS_SUCCESS)
        {
            cout << "Error encoding  MM Information ." << endl;
            return;
        }                                   
        *datalen = len;
}

void BuildMMStatus(ITS_OCTET *databuf, int *datalen)
{
   // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_MMStatus cmsr;

        cmsr.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsr.SetTIVal(TI_VALUE_3);                      //0x03
        cmsr.SetTIFlag(TI_FLAG_TO_SIDE);
         BSSAP_RRcause                   rrCs;  

  // populate Cause, add it to the message
        rrCs.SetRRCause(0x02);

        cmsr.AddIE(BSSAP_IEI_RR_CAUSE, &rrCs);

        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsr) != ITS_SUCCESS)
        {
            cout << "Error encoding MM Status ." << endl;
            return;
        }                                      
        *datalen = len;

}

void BuildMMNull(ITS_OCTET *databuf, int *datalen)
{

   // encode/decode buffer
        ITS_OCTET buff[maxSize];

        // message
        BSSAP_MMNull cmsr;

        cmsr.SetProtDiscr(PD_MOBILITY_MGMT_MSGS_NON_GPRS);  //0x05
        cmsr.SetTIVal(TI_VALUE_3);                      //0x03




        int len;
        // build the message
        if (BSSAP_Message::Encode(databuf, len, &cmsr) != ITS_SUCCESS)
        {
            cout << "Error encoding MM Null ." << endl;
            return;
        }                                      
        *datalen = len;
 
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
            PrintBSSAPMessage(data, len);
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
