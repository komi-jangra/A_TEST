#include <iostream>
#include "test_const.h"
#include <engine++.h>
#include <its_thread_pool.h>
#include <its_ual.h>

#include <dbc_server.h>

////////////////////////////////////////////////////////////////////////////////
//
//  Definitions for SCCP addresses.
//

using namespace std;

ITS_OCTET DATA[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x09, 0x00};

/* Write stats to a file/stdout */
//StatsRecord record;

ITS_UINT LOCAL_PC   = 0;
ITS_UINT LOCAL_SSN  = 2;
ITS_UINT REMOTE_PC  = 0;
ITS_UINT REMOTE_SSN = 2;


class OAMServer : public its::DbcServer
{
    public:
        OAMServer() 
          :DbcServer(string("OAMServer"))
        {
        }
        ~OAMServer() {}
        void DoCommand(std::istream &cmdLine)
        {
            return;
        }
};

OAMServer oamServer;

static void
UAL_Notifications(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    //TRANSPORT_Control *tc      = (TRANSPORT_Control *)object;
    UAL_CB_Context    *ctxt = (UAL_CB_Context *)callData;

    switch (UAL_CB_CTXT_TYPE(ctxt))
    {
        case UAL_CB_ASP_CTXT:
            if (UAL_CB_CTXT_ASP_STATE(ctxt) == UAL_ASP_DOWN)
            {
                cout << "**** CRITICAL: ASP is down. Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                cout << endl;
            }
            else if (UAL_CB_CTXT_ASP_STATE(ctxt) == UAL_ASP_ACTIVE)
            {
                cout << "**** DEBUG: ASP is ACTIVE. Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                cout << endl;
            }
            else if (UAL_CB_CTXT_ASP_STATE(ctxt) == UAL_ASP_INACTIVE)
            {
                cout << "**** WARNING: ASP is INACTIVE. ASP id = " << UAL_CB_CTXT_ASP_ID(ctxt) << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                cout << endl;
            }
            else if (UAL_CB_CTXT_ASP_STATE(ctxt) == UAL_ASP_CANT_START)
            {
                cout << "**** CRITICAL: ASP Can't START. Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                cout << endl;
            }

            break;
        case UAL_CB_AS_CTXT:
            switch (UAL_CB_CTXT_AS_STATE(ctxt))
            {
                case UAL_AS_DOWN:
                    cout << "**** CRITICAL: AS is DOWN. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;
                    break;

                case UAL_AS_INACTIVE:
                    cout << "**** CRITICAL: AS is INACTIVE. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;
                    break;

                case UAL_AS_ACTIVE:
                    cout << "**** DEBUG: AS is ACTIVE. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;
                    break;

                case UAL_AS_PENDING:
                    cout << "**** DEBUG: AS is PENDING. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;
                    break;

                case UAL_AS_REG:
                    cout << "**** DEBUG: AS is REG. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;
                    break;

                case UAL_AS_DREG:
                    cout << "**** DEBUG: AS is DREG. Routing key = " << UAL_CB_CTXT_RKEY(ctxt);
                    cout << "Transport id = " << UAL_CB_CTXT_TRANS_ID(ctxt);
                    cout << endl;

                    break;
            }
            break;
        case UAL_CB_RT_FAIL_CTXT:
            cout << "** CRITICAL: ASP ROUTING FAILED: INACTIVE ***" << endl;
            break;
        case UAL_CB__INVALID_CTXT:
        default:
            cout << "**** ERROR: INVALID CB Context." << endl;
            break;
    }
}

static void
UAL_MTP3callbacks(ITS_POINTER object, ITS_POINTER userData, ITS_POINTER callData)
{
    TRANSPORT_Control *tc = (TRANSPORT_Control *)object;
    ITS_EVENT         *evt = (ITS_EVENT *)callData;
    MTP3_PAUSE_RESUME mtpData;
    MTP3_HEADER       hdr;
    ITS_OCTET         type;
    ITS_USHORT        len = 0;

    MTP3_Decode(evt, &type, &hdr, (ITS_OCTET *)&mtpData, &len);
    switch(type)
    {
        case MTP3_MSG_RESUME:

            cout << "**** MTP3 RESUME on Transport id = " << TRANSPORT_INSTANCE(tc)
                 << " PC = " << MTP3_PC_GET_VALUE(mtpData.affected)
                 << endl;

            break;

        case MTP3_MSG_PAUSE:

            cout << "**** MTP3 PAUSE on Transport id = " << TRANSPORT_INSTANCE(tc)
                 << " PC = " << MTP3_PC_GET_VALUE(mtpData.affected)
                 << endl;

            break;

        default:
            break;
   }
}

void ReceiveAlarms(ITS_POINTER object, ITS_POINTER userData,
                   ITS_POINTER callData)
{
    ITS_EVENT *evt = (ITS_EVENT *)callData;

    if (evt->len)
    {
        fflush(stdout);
        printf("%s \n", (char *)evt->data);
        fflush(stdout);
    }
}

void
RegisterUAL_Callbacks()
{
    CALLBACK_AddCallback(__UAL_MgntCallBack,
                         UAL_Notifications,
                         NULL);

    CALLBACK_AddCallback(MTP3_ManagementCallbacks,
                         UAL_MTP3callbacks,
                         NULL);

    CALLBACK_AddCallback(ALARM_Callbacks, ReceiveAlarms, NULL);

    return;
}

////////////////////////////////////////////////////////////////////////
//
//   Send a Message UDT
//
int
TEST_BuildAndSendMsg(int numIteration, ITS_HANDLE handle,
                     SCCP_ADDR* remote, SCCP_ADDR* orig)
{
    ITS_SCCP_IE ies[8];             /* To Build IES */
    SCCP_ADDR   origAddr;           /* Origination SCCP addr */
    SCCP_ADDR   destAddr;           /* Destination SCCP Addr */
    ITS_HDR     hdr;                /* ITS Header for routing */
    ITS_UINT    sio = 3, sls = 3;   /* Deafult SIO/SLS */
    ITS_UINT    rpc, pc;            /* var to get info from SCCP address */
    ITS_OCTET   rssn, ssn; 
    ITS_INT     ret = ITS_SUCCESS;
    ITS_INT     ieCount = 0;        /* Number of IEs to send */
    ITS_OCTET   addInd;             /* get address indicator from SCCP Addr */ 
    MTP3_POINT_CODE opc, dpc;       /* For setting routing label */
    char buffer[80];                /* for writing inot a file */

    if(remote != NULL)
    {
        ITS_USHORT len = 0;
        /* We got something from remote, we decode 
         * the addr to send response to what we received.
         */
        ret = SCCP_DecodeAddr(remote, &addInd, &rpc, &rssn, NULL, &len);

        if(ret != ITS_SUCCESS)
        {
            cout << "ERROR: Sccp address decode failed:" << endl;
        }
    }
    else
    {
        cout << endl << "Enter SIO:";   // We need user intervention
        cin  >> sio;                    // when we send unitdata.
        cout << endl << "Enter SLS:";   //
        cin  >> sls;

        rpc  = REMOTE_PC;
        rssn = REMOTE_SSN;
    }

    ret = SCCP_EncodeAddr(&destAddr, SCCP_ADDR_INDICATOR,
                          rpc, rssn, NULL, 0);
    if (ret != ITS_SUCCESS)
    {
        cout << "TEST --- > Error Encoding SCCP Address !!!!!!!! /n";

        return ret;
    }

    if(orig != NULL)
    {
        ITS_USHORT len = 0;

        ret = SCCP_DecodeAddr(orig, &addInd, &pc, &ssn, NULL, &len);

        if(ret != ITS_SUCCESS)
        {
            cout << "ERROR: SCCP Orig decode addr failed:" << endl;
        }
    }
    else
    {
        pc  = LOCAL_PC;
        ssn = LOCAL_SSN;
    }
 
    ret = SCCP_EncodeAddr(&origAddr, SCCP_ADDR_INDICATOR,
                          pc, ssn, NULL, 0);

    if (ret != ITS_SUCCESS)
    {
        cout << "TEST --- > Error Encoding SCCP Address !!!!!!!! /n";

        return ret;
    }

    ies[0].param_id     = SCCP_PRM_ROUTING_LABEL;
    ies[0].param_length = sizeof(MTP3_HEADER);

    opc.data[1] = (pc >> 8) & 0xFF;
    opc.data[0] = (pc & 0xFF);
    dpc.data[1] = (rpc >> 8) & 0xFF;
    dpc.data[0] = (rpc & 0xFF);
 
    MTP3_RL_SET_DPC(ies[0].param_data.routingLabel.label, dpc);
    MTP3_RL_SET_OPC(ies[0].param_data.routingLabel.label, opc);

    MTP3_RL_SET_SLS(ies[0].param_data.routingLabel.label, (sls & 0xFF));
  
    MTP3_RL_GET_OPC(ies[0].param_data.routingLabel.label, opc);
    MTP3_RL_GET_DPC(ies[0].param_data.routingLabel.label, dpc);

    ies[0].param_data.routingLabel.sio =(sio & 0xFF);

    ieCount++;

    ies[1].param_id     = SCCP_PRM_CALLED_PARTY_ADDR;
    ies[1].param_length = sizeof(SCCP_ADDR);
    memcpy(&ies[1].param_data.calledPartyAddr, &destAddr,
           sizeof(SCCP_ADDR));

    ieCount++;

    ies[2].param_id     = SCCP_PRM_CALLING_PARTY_ADDR;
    ies[2].param_length = sizeof(SCCP_ADDR);
    memcpy(&ies[2].param_data.callingPartyAddr, &origAddr,
           sizeof(SCCP_ADDR));

    ieCount++;

    ies[3].param_id     = SCCP_PRM_PROTOCOL_CLASS;
    ies[3].param_length = sizeof (SCCP_PROT_CLASS);
    ies[3].param_data.protocolClass.pclass = 0x82;

    ieCount++;

    ies[4].param_id     = SCCP_PRM_DATA;
    ies[4].param_length = 10;
    memcpy(ies[4].param_data.userData.data, DATA, 10);

    ieCount++;

    memset(buffer, 0, 80 * sizeof(char));

    for (int i=0; i<numIteration; i++)
    {
        int count = 0;
        ret = SCCP_SendUnitData(ISS7_Stack, &hdr, ies, ieCount);
        if (ret != ITS_SUCCESS)
        {
            cout << "TEST --- > Error Sending UDT Message !!!!!!!! /n";

            continue;
        }

        if(numIteration % 2000 == 0)
        {
            count = sprintf(buffer, SENT_BUFFER_FORMAT, numIteration);

           // STATS_WRITE(&record, WRITE_FILE, buffer, count);
        }
    }

    return ret;
}

ITS_INT TEST_AddLinkForLocalRoute(ITS_HANDLE handle)
{
    ITS_INT        ret  = 0;
    ITS_USHORT     inst = TRANSPORT_INSTANCE(handle);
    SS7_Link       link;
    SS7_LinkSetPtr linkSet;
    
    memset(&link, 0, sizeof(SS7_Link));
    
    linkSet = LINKSET_FindLinkSet(0); /* Find linkset for localroute */
    
    link.initActive = ITS_TRUE; /* activate when link set activates */
    link.localLink  = ITS_TRUE; /* link is on local node */
    link.linkCode   = inst - 1; /* start from zero */
    link.priority   = 0;
    link.id         = inst;
    link.isUp       = ITS_TRUE;
    link.isAllowed  = ITS_TRUE;
    link.family     = FAMILY_ITU; 
    /* link.linkSet    = linkSet; */
    
    cout << "TEST_AddLinkForLocalRoute():" << endl;
    
    if( (ret = LINK_AddLink(0, &link)) == ITS_SUCCESS)
    {
        SS7_LinkPtr lp = NULL;

        cout << "Added link for local route to Transport Inst 1:" << endl;

        lp = LINK_FindLink(0, link.linkCode);

        if(lp != NULL)
        {
            LINK_AddLinkInfoToTransport((TRANSPORT_Control *)handle, lp);
        }

        LINK_SetLinkState(lp, ITS_TRUE);

        LINKSET_SetLinkSetState(LINKSET_FindLinkSet(0), ITS_TRUE);
    }
    else
    {   
        cout << "ERROR: Failed to add link:" << endl;
    }

    return ret;
}
extern "C"
{
void APP_SetStopper()
{
    SERVICE_SetStopped();

    return;
}

void ENGINE_PreFunc(void)
{
   ITS_INT  numThreads = 2;
   ITS_INT  ret = 0;
   ITS_UINT asp_pc, sgp_pc;

   cout << "Enter ASP Point code:";
   cin  >> asp_pc; cout << endl;
   cout << "Enter SGP Point code:";
   cin  >> sgp_pc;
  
   for(int i = 0; i < numThreads; i++)
   {
       its::ThreadPoolEntry ent;

       if(engine::workerPool->GetFirstAvailThread(ent) == ITS_SUCCESS)
       {
           engine::Worker* work = (engine::Worker *)ent.GetThread();

           if(work != NULL)
           {
               ret =
                 engine::workerPool->DispatchOnThread(ent,
                                        DISP_Dispatch_USER_CPP,
                                        (void*) work->GetCallbackStruct());
           }

           TIMERS_Sleep(1);
       }
   }

   RegisterUAL_Callbacks();
   
   //STATS_CONSTRUCT((STATS_HANDLE)&record, "./record.data");

   return;
}

void ENGINE_PostFunc()
{
    //STATS_DESTRUCT((STATS_HANDLE)&record);

    return;
}

ITS_INT
BorderPostNextEvent(its::ThreadPoolThread* thr, its::Event& evt)
{
   if(evt.GetSource() == ITS_SCCP_SRC)
   {
       evt.SetSource(ITS_MTP3_SRC);

       its::Transport::PutEvent(ITS_SCCP_SRC, evt);

       printf("Sent the message to SCCP\n");
   }

   return ITS_SUCCESS;
}

}
