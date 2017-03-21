#include <stdlib.h>
#include <iostream>
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
#include <its_timers.h>

#include <BSSAP++.h>
#include <BSSAPPrint.h>


ITS_HDR srcHdr, remHdr;
#define VALID_CHOICE(x)     ( x >= 1 && x <= 4 || x == 99 )
#define MAX_RK_NUM    5
#define BUILD_DATA    2
#define CONNECT    1
#define TEST_EXIT    99

#define SEND_DT1      1
#define SEND_DT2     2
#define DISCONNECT   3
//
// local subsystem for testing
//
#define LOCAL_SSN   8
#define REMOTE_SSN  254
#define LOCAL_PC    4114
#define REMOTE_PC   2

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

int BuildAssigmentComplete(ITS_OCTET *databuf, int *datalen);

int
TEST_ExecuteCommand(int cmdInput, ITS_HANDLE handle, ITS_USHORT instance);
void CommandExec(void *handle,int m_type, SCCP_UserData *ud);
void PrintData(SCCP_UserData *ud);
void PrintLongData(SCCP_LongUserData *ud);
static int 
TEST_PrintCommand();
void
SccpThreadFunction(its::ITS_ThreadPoolThread* thr, ITS_HANDLE handle);
static int 
TEST_WaitForEvent(ITS_Worker *worker, ITS_HANDLE handle);

void RouteSS7()
{
}

ITS_USHORT RouteAPP(ITS_HDR *hdr, ITS_EVENT *event)
{
  ThreadPoolEntry thr;
  engine::Worker *eng;

  cout << "Inside MyPreFunc " << endl;
  workerPool->GetFirstAvailThread(thr);
  eng = reinterpret_cast<engine::Worker *>(thr.GetThread());
  workerPool->DispatchOnThread(thr, DISP_Dispatch_USER_CPP,
                            (void *)eng->GetCallbackStruct());
  return eng->GetInstance();

}


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
     // system("clear");
     for (;;)
     {
         cout<<"Waiting for event..."<<endl;
        TEST_WaitForEvent(worker, handle);
     }

}
////////////////////////////////////////////////////////////////////////////
//
// TEST_WaitForEvent
//
///////////////////////////////////////////////////////////////////////////

static int 
TEST_WaitForEvent(ITS_Worker *worker, ITS_HANDLE handle)
{
    ITS_Event event;
    ITS_SCCP_IE ies[32];
    int ret = ITS_SUCCESS, ieCount = 0;
    ITS_BOOLEAN reply = ITS_FALSE;
    ITS_HDR sccpHdr;
    const ITS_OCTET *data;
    ITS_USHORT instance = worker->GetInstance();
 

    int res = worker->GetNextEvent(event);

    if (res != ITS_SUCCESS)
    {
        ITS_Error itsError(res, __FILE__, __LINE__);

        cout << endl << itsError.GetDescription() << endl;

    }
    cout<<"\n\n\n--------------------------------------------------"<<endl;
    cout <<"Received Event..." << endl;
    data = event.GetData();

    printf("*---> Dump Event <---*\n");

    for(int i=0; i < event.GetLength(); i++)
    {
        printf("%02x ", data[i]);

    }
    printf("\n");

    res = ITS_SUCCESS;

    SCCP_MessageClass* sMsg = NULL;

    // Next call will initialize sccpHdr.

    res = SCCP_MessageClass::Receive(handle, &sccpHdr, event, &sMsg);

    if (res != ITS_SUCCESS)
    {
        if (sMsg != NULL)
        {
            delete sMsg;
        }

        ITS_THROW_ERROR(res);
    }

    switch (sMsg->GetMsgType())
    {
        case SCCP_MSG_CR:
        {  
            cout<<"Received Connection Request.... "<<endl;

	    /***** Sending Connection Confirm in response to CR *****/ 
	    srcHdr = sccpHdr;
           ROUTE_AddApplication(instance, &sccpHdr);
	    SCCP_SourceLocalRef *tmp = 
		(SCCP_SourceLocalRef *)sMsg->FindIE(SCCP_PRM_SRC_LOCAL_REF);
	    remHdr.context.conref = tmp->GetRefNum();

	    SCCP_ConnectionConfirm cc;

	    /* Destination Local Reference */

	    SCCP_DestinationLocalRef dlr(remHdr.context.conref);
	    cc.AddIE(&dlr);

	    /* Source Local Reference */
	    SCCP_SourceLocalRef slr(srcHdr.context.conref);
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
	    // cc.AddIE(&called_pa);

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
        
	    ret = SCCP_MessageClass::Send(handle, &srcHdr, &cc);
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
        case SCCP_MSG_DT1:
        {
	    cout <<" Received DT1.... " << endl;
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)sMsg->                                            FindIE(SCCP_PRM_DEST_LOCAL_REF);

            SCCP_SegmentReassem* sr = (SCCP_SegmentReassem *)sMsg->
                                             FindIE(SCCP_PRM_SEGMENT_REASSEM);

            SCCP_UserData *ud = (SCCP_UserData *)sMsg->FindIE(SCCP_PRM_DATA);
            PrintData(ud);

            SCCP_UserData ud1;
            ITS_OCTET data[5666];
            int len;

            BuildAssigmentComplete(data, &len);

            ud1.SetUserData(data, len);

            CommandExec(handle,1, &ud1);
          
            break;
        }
        case SCCP_MSG_DT2: //This is for CLASS_3 protocol class.
        { 
            cout <<" Received DT2..... " << endl;
   
            SCCP_DestinationLocalRef *dlr = (SCCP_DestinationLocalRef *)sMsg->
                                          FindIE(SCCP_PRM_DEST_LOCAL_REF);

            SCCP_SegmentReassem* sr = (SCCP_SegmentReassem *)sMsg->
                                          FindIE(SCCP_PRM_SEGMENT_REASSEM);

            SCCP_UserData *ud = (SCCP_UserData *)sMsg->FindIE(SCCP_PRM_DATA);

            PrintData(ud);

            CommandExec(handle,2, NULL);
     
            break;

        }
        
        case SCCP_MSG_RLSD:
        {
            cout<<"Received RLSD Message\n";

            SCCP_ReleaseComplete rc;

            SCCP_DestinationLocalRef dlr(remHdr.context.conref);
            rc.AddIE(&dlr);

            /* Source Local Reference */
            SCCP_SourceLocalRef slr(srcHdr.context.conref);
            rc.AddIE(&slr);

            ret = SCCP_MessageClass::Send(handle, &srcHdr, &rc);
            if (ret != ITS_SUCCESS)
            {
                cout << "Error while sending CC: " << ret << endl;
            }
            else
            {
               cout<<"Sending RLC Message..."<<endl;
            }

        }
            defualt:
            break;
        
    }
          
    return ret;
}

///////////////////////////////////////////////////////////////////////////
//
// CommandExec
//
//////////////////////////////////////////////////////////////////////////

void CommandExec(void *handle,int m_type, SCCP_UserData *ud)
{
    int n;
    if(m_type ==2)
    {
       //This ACK Message is for DT2.
       cout<<"If you want send the DATA ACK  press (1)"<<endl;

       cin>>n;

       if(n == 1)
       {
           cout<<"Sending Data acknowlegement"<<endl;

           /* build a message */
           SCCP_Acknowledge ack;

           /* Destination Local Reference */
           SCCP_DestinationLocalRef dlr(remHdr.context.conref);
           ack.AddIE(&dlr);

           SCCP_ReceiveSequenceNum rsn(1,0); //rsn=1, haveMore=0
           ack.AddIE(&rsn);

           SCCP_Credit credit(1);
           ack.AddIE(&credit);

           SCCP_MessageClass::Send(handle, &srcHdr, &ack);
        }
        else
        {
            cout<<"Waiting Message "<<endl;
        }
    }
    else
    {
        //cout<<"If you want send the DT1 back press (1)"<<endl;
        //cin>>n;
        n =1;
        cout<<"\nSending DT1 back to ASP....\n\n\n"<<endl;
        if(n == 1)
        { 
            /* create a message */
            SCCP_DataForm1 df1;

            /* Destination Local Reference */
            SCCP_DestinationLocalRef dlr(remHdr.context.conref);
            df1.AddIE(&dlr);

            /* segmenting/reassembling */
            SCCP_SegmentReassem sr(1); //more data
            /*  implementation can be changed to:
            SCCP_SegmentReassem sr();
            sr.SetSegmentReassem(1);    //0 means no data */
            df1.AddIE(&sr);

            df1.AddIE(ud);

            SCCP_MessageClass::Send(handle, &srcHdr, &df1);
        }   
        else
        {
            cout<<"Waiting Message "<<endl;
        }
    }
} 


////////////////////////////////////////////////////////////////////////
//
// PrintData
//
////////////////////////////////////////////////////////////////////////
void PrintData(SCCP_UserData *ud)
{
    if (ud != NULL)
    {
        ITS_OCTET data[1000];
        int len,i;

        cout << "UserData:" << endl;

        ud->GetUserData(data, len);
        PrintBSSAPMessage(data, len);
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

            /*BSSAP_Message* dec;
            if (BSSAP_Message::Decode(data, len, &dec) != ITS_SUCCESS)
            {
                cout << "Error decoding Assignment Request." << endl;
                return;
            }

            PrintBSSMAPMsgAssignReq(dec);*/

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

void PrintLongData(SCCP_LongUserData *ud)
{
    if (ud != NULL)
    {
        ITS_OCTET data[5000];
        int len,i;

        cout << "UserData:" << endl;

        ud->GetLongUserData(data, len);
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

int BuildAssigmentComplete(ITS_OCTET *databuf, int *datalen)
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
        BSSAP_RRcause                   rrCs;
        BSSAP_CktIDCode                 cktId;
        BSSAP_CellID                    cellId;
        BSSAP_ChsChan                   chsChan;    
        BSSAP_ChsEncAlg                 ceAlg;
        BSSAP_CktPool                   cktPl;
        BSSAP_SpchVer                   spchVer;
        BSSAP_LsaId                     lsaid;
        
        // encode/decode buffer
        ITS_OCTET buff[maxSize];

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
        lsaid.SetLSAIDBit1(0x01); 
        lsaid.SetLSAID(0x432111); 

        assCmp.AddIE(BSSAP_IEI_LSA_IDENTIFIER, &lsaid);
        

        int len;
        // build the message
        if (BSSAP_Message::Encode(buff, len, &assCmp) != ITS_SUCCESS)
        {
            cout << "Error encoding Assignment Complete." << endl;
            return -1;
        }
     
        memcpy(databuf, buff, len);
        *datalen = len;

#if 0
        // print the user data
        DumpData(buff, len);

        // do the decode
        BSSAP_Message* dec;
        if (BSSAP_Message::Decode(buff, len, &dec) != ITS_SUCCESS)
        {
            cout << "Error decoding Assignment Complete." << endl;
            return;
        }

        // PrintBSSMAPMsgAssignComplete(dec); 
#endif
    }
}
}
