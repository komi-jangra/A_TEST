#include <lapd_adaptation_layer.h>
#include <lapdif_handler.h>
#include <lapd_trace.h>
#include <trace.h>

#include <its.h>
#include <its++.h>
#include <its_sctp.h>
#include <sctp_msgs.h>
#include "its_sctp_impl.h"
#include "its_sockets.h"
#include <stdio.h>
#include <errno.h>


#include <tslink3.h>
#include <tsl3tune.h>
#include <l4cel3.h>

extern char PpIpAddress[15];
#define BSC_LAPDIFM_INST 20
#define SOCK_POLL_ERROR      0x10
#define SOCK_POLL_ERROR_OOB  0x20
#define MAX_SCM_CON    5
#define LAPD_ALARM_LEVEL_MAJOR  0x03

#ifdef LAPD_HA
extern "C" int G_CARD_STATE;
extern "C"
{
#ifdef PLATFORM_IMR
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
#endif
}
#endif


void *scmHandler(void  *args);
void *scmReceive(void  *args);
int ScmReadEvent(ITS_SocketInfo *info, ITS_EVENT *evt);

char ScmIpAddress[15];
int LAPDSCMServerPort;
int lapdHaSupport = 1;
ITS_SocketInfo *scmconnections[MAX_SCM_CON];
ITS_SocketInfo *gsock;

extern  ITS_HANDLE CL_Handle_TCAP;
extern "C" int CL_WriteEventTcap(ITS_HANDLE, ITS_EVENT*);
extern "C" ITS_INT Release_Link(int fd, int interface, int sapi, int lapdTei);
#ifdef LAPD_HA
extern "C" void send_card_state_event_to_lapd(int cardState);
#endif
extern "C" ITS_INT modifyLapdTmr(lapdCoreTimerData *lapdCoreTmrData);
extern "C" ITS_INT Get_Stats(LapdPegsShow_t    *lapdPegShow);

extern  int start_comm(ITS_OCTET ts, ITS_OCTET sapi, ITS_OCTET lapdTei, ITS_OCTET appTei, ITS_OCTET teiOffset);
extern "C" int  checkAndUpdateLapdCfgValue(char operation, op_conf_data *cfgPtr);
extern struct conf_data *CONF_DATA[MAXTSVAL];

struct prfm_stats
{
   unsigned int txI;
   unsigned int rxI;
   unsigned int txUI;
   unsigned int rxUI;
   unsigned int txRR_C;
   unsigned int rxRR_C;
   unsigned int txRR_R;
   unsigned int rxRR_R;
   unsigned int txREJ_C;
   unsigned int rxREJ_C;
   unsigned int txREJ_R;
   unsigned int rxREJ_R;
   unsigned int txRNR_C;
   unsigned int rxRNR_C;
   unsigned int txRNR_R;
   unsigned int rxRNR_R;
   unsigned int num_decode_fail;
   unsigned int num_encode_fail;
};


ITS_INT SendToApp(ITS_EVENT *lapdEvent)
{
    int ret;
   
    // Function will write the buffer to App socket
    ret = CL_WriteEventTcap(CL_Handle_TCAP, lapdEvent);  // Check	
    if(ret != ITS_SUCCESS)
    {
        CL_Handle_TCAP = NULL;    // Check 
        ITS_EVENT_TERM(lapdEvent);
    }

    return ITS_SUCCESS;   	
}

#ifdef __cplusplus
extern "C" {
#endif


ITS_INT AL3_LinkSts_Send(ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength)
{
    ITS_EVENT lapdEvent;
    ITS_USHORT msglen, loop = 0, tempVar;
    ITS_OCTET msgGroupId, msg_buff[100];
    LapdLinkStatusResp *lapdLinkStatusResp;
    lapdLinkStatusResp = (LapdLinkStatusResp*)dataBuffer;
#ifdef LAPD_HA
    if(G_CARD_STATE == CARDSTATE_STANDBY)
    {
     ISIL_DEBUG_TRACE(("Msg dumped card state standby"));
     return 0;
    }
#endif

   msg_buff[0] = LAPD_LINK_STATUS_RESP;
   tempVar = 0;
   for(loop=0;loop<2;loop++)
   {
    tempVar++;
    msg_buff[tempVar] = lapdLinkStatusResp->lapdLinkStsResp[loop].tei;
    tempVar++;
    msg_buff[tempVar] = lapdLinkStatusResp->lapdLinkStsResp[loop].OmlSts;
    tempVar++;
    msg_buff[tempVar] = lapdLinkStatusResp->lapdLinkStsResp[loop].RslSts;
   } 
   tempVar++;


    msglen = tempVar + 10; 
    ITS_EVENT_INIT(&lapdEvent, BSC_LAPDIFM_INST, msglen);
    lapdEvent.len = msglen;
    msgGroupId = LAPD_LINK_MANAGEMENT_MESSAGE;

    lapdEvent.data[0] = 0xc2;   // Fixed
    lapdEvent.data[1] = 0x01;   // Fixed
    lapdEvent.data[2] = 0x03;   // Fixed
    lapdEvent.data[3] = msglen & 0xff;                   // Length
    lapdEvent.data[4] = (msglen & 0xff00) >> 8;            // Length
    lapdEvent.data[5] = msgGroupId;   
    lapdEvent.data[6] = lapdLinkStatusResp->lapdLinkStsResp[1].tei;   
    lapdEvent.data[7] = 62; /* fixed always management sapi */   
    lapdEvent.data[8] = tempVar & 0xff;                   // Length
    lapdEvent.data[9] = (tempVar & 0xff00) >> 8;            // Length

    memcpy(&lapdEvent.data[10], msg_buff, tempVar);

    // Send Data to BSC-Application
    ITS_INT ret  = SendToApp(&lapdEvent);
    if(ret != ITS_SUCCESS)
    {
	LAPD_TRACE_CRITICAL(("\nAL3_LinkSts_Send: Failed to send message on socket"));
    }    
    return ret;
}


ITS_INT 
AL3_SAPI_ReadProc(ITS_OCTET sapi, 
ITS_OCTET tei,
ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength)
{
    ITS_EVENT lapdEvent;
    ITS_USHORT msglen;
    ITS_OCTET msgGroupId;


#ifdef LAPD_HA
    if(G_CARD_STATE == CARDSTATE_STANDBY)
    {
     ISIL_DEBUG_TRACE(("Msg dumped card state standby"));
     return 0;
    }
#endif



    msglen = dataBufferLength + 10; 
    ITS_EVENT_INIT(&lapdEvent, BSC_LAPDIFM_INST, msglen);
    lapdEvent.len = msglen;
        
    if(dataBufferLength == 1)
    {
        msgGroupId = LAPD_LINK_MANAGEMENT_MESSAGE;
    }
    else
    {
       	msgGroupId = LAPD_DATA_MESSAGE;
    }

    lapdEvent.data[0] = 0xc2;   // Fixed
    lapdEvent.data[1] = 0x01;   // Fixed
    lapdEvent.data[2] = 0x03;   // Fixed
    lapdEvent.data[3] = msglen & 0xff;                   // Length
    lapdEvent.data[4] = (msglen & 0xff00) >> 8;            // Length

    lapdEvent.data[5] = msgGroupId;   
    lapdEvent.data[6] = tei;   
    lapdEvent.data[7] = sapi;   
    lapdEvent.data[8] = dataBufferLength & 0xff;                   // Length
    lapdEvent.data[9] = (dataBufferLength & 0xff00) >> 8;            // Length

    memcpy(&lapdEvent.data[10], dataBuffer, dataBufferLength);

    // Send Data to BSC-Application
    ITS_INT ret  = SendToApp(&lapdEvent);
    if(ret != ITS_SUCCESS)
    {
	LAPD_TRACE_CRITICAL(("\nAL3_SAPI_ReadProc: Failed to send message on socket"));
    }    
    return ret;
}
    
void init_scm_interface()
{
    const char *temp =NULL;
    pthread_t scmThreadId; 
    lapdHaSupport = 1;
    gsock = NULL;
    pthread_create(&scmThreadId, NULL, scmReceive, NULL);
    temp = getenv("LAPD_HA_SUPPORT");
    if(temp != NULL)
    {
     if(strcmp(temp, "NO") == 0)
     {
      lapdHaSupport = 0;
     }
    } 
}

void SendAlarmTo_SCM(unsigned short id, ITS_OCTET tei, ITS_OCTET sapi)
{
    ITS_EVENT sendevt;
    int nsend;

    if(gsock == NULL)
    {
        return;
    }

    ITS_EVENT_INIT(&sendevt, BSC_LAPDIFM_INST, 9);
    sendevt.data[0] = LAPD_SCM_IF_ID;
    sendevt.data[1] = 0x07;  // GroupId(1) + MsgType(1) + AlarmId(2) + level(1) + TEI(1) + SAPI(1)
    sendevt.data[2] = LAPD_SCM_ALARM_MSG;
    sendevt.data[3] = LAPD_SCM_ALARM_IND;

//    memcpy(&sendevt.data[4], &id, 2);	         // Alarm Id
    sendevt.data[4] = id & 0xff;	          // Alarm Id
    sendevt.data[5] = (id & 0xff00) >> 8;	  // Alarm Id
    sendevt.data[6] = LAPD_ALARM_LEVEL_MAJOR;    // Alarm Level
    sendevt.data[7] = tei;                       // TEI			
    sendevt.data[8] = sapi;                      // SAPI

    nsend = SOCK_Write(gsock, (char *)sendevt.data, sendevt.len);
    if(nsend > 0)
    {
        LAPD_TRACE_INFO(("\nAlarm nsend = %d", nsend));
    }
    free(sendevt.data);
}

void SendStatsTo_SCM(ITS_OCTET *databuf, ITS_USHORT datalen, ITS_OCTET appTei)
{
    ITS_EVENT sendevt;
    struct prfm_stats *lstats;
    unsigned char apptei; 
    op_conf_data cfgdata;
    int nsend, pegLoop, rcvPegOffset, respLen;
    unsigned short Length; 
    LapdPegCmd *lapdPegCmd;
    LapdPegResponse *lapdPegResponse;
   
    lapdPegCmd = (LapdPegCmd*)databuf;
    respLen = 50 +  sizeof(LapdPegResponse);
    ITS_EVENT_INIT(&sendevt, BSC_LAPDIFM_INST, respLen);
      
    if(gsock == NULL)
    {
        return;
    }
    Length = sizeof(LapdPegR) + ((lapdPegCmd->count - 1) * (sizeof(LapdPeg))) + 3; 
    sendevt.data[0] = LAPD_SCM_IF_ID;
    sendevt.data[1] = 100;
    sendevt.data[2] = LAPD_SCM_PEGS_MSG;
    sendevt.data[3] = Length & 0xff;
    sendevt.data[4] = (Length >> 8) & 0xff;
    lapdPegResponse = (LapdPegResponse*)&sendevt.data[5];
    lapdPegResponse->count = lapdPegCmd->count;
    LAPD_TRACE_INFO(("\n Received peg info count: %d", lapdPegResponse->count));

    rcvPegOffset = sizeof(LapdPegCmd);

   for(pegLoop=0; pegLoop<lapdPegCmd->count; pegLoop++) 
   {
     lstats = (struct prfm_stats *)(databuf + rcvPegOffset); 
     cfgdata.ts = lapdPegCmd->lapdTeiInfo[pegLoop].ts;
     cfgdata.tsflag = 0;
     cfgdata.lapdTei = lapdPegCmd->lapdTeiInfo[pegLoop].lapdTei;
     cfgdata.lapdteiflag = 1;



     if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
     {
       LAPD_TRACE_CRITICAL(("lapd config data get fail !bug! " ));
       continue;
     }
     apptei      = cfgdata.appTei;

    lapdPegResponse->lapdPeg[pegLoop].applTei = apptei;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].sapi = 0;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdInfoSend = lstats->txI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdInfoRecv = lstats->rxI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdUiSend = lstats->txUI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdUiRecv = lstats->rxUI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRrCSend = lstats->txRR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRrCRecv = lstats->rxRR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRrRSend = lstats->txRR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRrRRecv = lstats->rxRR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRejCSend= lstats->txREJ_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRejCRecv = lstats->rxREJ_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRejRSend = lstats->txREJ_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRejRRecv = lstats->rxREJ_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRnrCSend = lstats->txRNR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRnrCRecv = lstats->rxRNR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRnrRSend = lstats->txRNR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdRnrRRecv = lstats->rxRNR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdMsgDecodeFail = lstats->num_decode_fail;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[0].pegLapdMsgEncodeFail = lstats->num_encode_fail;
  
    rcvPegOffset = rcvPegOffset + sizeof(struct prfm_stats);
    lstats = (struct prfm_stats *)(databuf + rcvPegOffset);

    lapdPegResponse->lapdPeg[pegLoop].applTei = apptei;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].sapi = 62;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdInfoSend = lstats->txI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdInfoRecv = lstats->rxI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdUiSend = lstats->txUI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdUiRecv = lstats->rxUI;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRrCSend = lstats->txRR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRrCRecv = lstats->rxRR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRrRSend = lstats->txRR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRrRRecv = lstats->rxRR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRejCSend= lstats->txREJ_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRejCRecv = lstats->rxREJ_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRejRSend = lstats->txREJ_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRejRRecv = lstats->rxREJ_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRnrCSend = lstats->txRNR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRnrCRecv = lstats->rxRNR_C;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRnrRSend = lstats->txRNR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdRnrRRecv = lstats->rxRNR_R;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdMsgDecodeFail = lstats->num_decode_fail;
    lapdPegResponse->lapdPeg[pegLoop].pegInfo[1].pegLapdMsgEncodeFail = lstats->num_encode_fail;
    rcvPegOffset = rcvPegOffset + sizeof(struct prfm_stats);

   }
 


    LAPD_TRACE_INFO(("\nSending peg length: pegdata length %d, buffsize: %d\n", Length, respLen));
    nsend = SOCK_Write(gsock, (char *)sendevt.data, Length + 2);
    if(nsend > 0)
    {
        LAPD_TRACE_INFO(("\nStats nsend = %d", nsend));
    } 
    free(sendevt.data); 
}

#ifdef __cplusplus
}
#endif


ITS_INT ReadFromApp(ITS_EVENT *evt)
{    
    unsigned char *data;
    ITS_OCTET *pdata;
    ITS_OCTET tei;
    ITS_OCTET sapi;
    ITS_USHORT dataLen;

    data = evt->data;

    tei      = data[6];
    sapi     = data[7];
    dataLen  = data[8] | data[9] << 8;
    pdata = &data[10];

    if(dataLen >= 4)
    {
        LAPD_TRACE_INFO(("\nReadFromApp TEI = 0x%x SAPI = 0x%x Data = 0x%x 0x%x 0x%x 0x%x"
                          , tei, sapi, pdata[0], pdata[1], pdata[2], pdata[3]));
    }
    else
    {
        LAPD_TRACE_INFO(("\nReadFromApp TEI = 0x%x SAPI = 0x%x Data = 0x%x", tei, sapi, pdata[0]));
        if(dataLen == 3)
        {
         LAPD_TRACE_INFO(("\nget_Lapd_Link_Sts_Req: data[0]: %d payload = 0x%x 0x%x 0x%x "
                          , data[0], pdata[0], pdata[1], pdata[2]));
        }	 
    }

    if((data[5] == LAPD_LINK_MANAGEMENT_MESSAGE) && (data[10] == LAPD_LINK_STATUS_REQ))
    {
      LAPD_TRACE_INFO(("\nget_Lapd_Link_Sts_Req: payload = 0x%x 0x%x 0x%x "
                          , pdata[0], pdata[1], pdata[2]));
     get_Lapd_Link_Sts_Req(pdata, dataLen);
    }
    else
    {
     AL3_Send_L2Req(sapi, tei, pdata, dataLen);
    } 

    return ITS_SUCCESS;
}

void  scm_connection(ITS_SocketInfo *connect)
{
    unsigned char i;

    for(i=0; i<MAX_SCM_CON; i++)
    {
        if(scmconnections[i] == NULL)
        {
            scmconnections[i] = connect;
            gsock = connect;   // Put connected socket id in to global Id
            break;
        }
    }

    if(i == MAX_SCM_CON)
         LAPD_TRACE_CRITICAL(("\n ERROR: No location free for  new ENTRY  of handle"));
}

void *scmReceive(void  *args)
{
    int i;
    ITS_SocketInfo *sock1;
    ITS_SocketInfo *tmpsock;
    pthread_t rthread; 

    LAPD_INT_TRACE_DEBUG(("scmReceive Delay 1234"));
//    sleep(10);
    LAPD_INT_TRACE_DEBUG(("scmReceive Delay 5678"));

    /* connections array initalised with NULL values*/
    for(i=0; i<MAX_SCM_CON; i++)
    {
         scmconnections[i] = NULL;
    }

    if(SOCK_ServerOpen(&sock1, INET_DOMAIN, ScmIpAddress, LAPDSCMServerPort) != ITS_SUCCESS)
    {
        LAPD_TRACE_CRITICAL(("\nSCM_ERROR:FAIL TO OPEN SERVER SOCKET"));
    }
    else
    {
        LAPD_TRACE_INFO(("\nSCM_TRACE:OPEN SERVER SOCKET FOR SCM"));
    }

    pthread_create(&rthread, NULL, scmHandler, NULL);

    while(1)
    {
        if(SOCK_ServerAccept(sock1, &tmpsock) == ITS_SUCCESS)
        {
            scm_connection(tmpsock);
        }
    }

    return 0;
}

int SCMSOCK_Poll(ITS_SockPollInfo *socks,int nsocks,int usecs)
{
    int i;
    fd_set reads, writes,errors;
    int ret, max;

    if (nsocks == 0 ||
        (usecs == SOCK_POLL_WAIT_FOREVER && nsocks == 0))
    {
        sleep(5);
        return  -1;
       /* return (ITS_EINVALIDARGS);*/
    }

    FD_ZERO(&reads);
    FD_ZERO(&writes);
    FD_ZERO(&errors);

    max = 0;
   for (i = 0; i < nsocks; i++)
    {
        socks[i].wasSet = 0;

        if ((int)socks[i].sinfo->socket > max)
        {
            max = socks[i].sinfo->socket;
        }

        if (socks[i].lookFor & (SOCK_POLL_READ|SOCK_POLL_READ_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &reads);
        }

        if (socks[i].lookFor & (SOCK_POLL_WRITE|SOCK_POLL_WRITE_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &writes);
        }

        if (socks[i].lookFor & (SOCK_POLL_ERROR|SOCK_POLL_ERROR_OOB))
        {
            FD_SET(socks[i].sinfo->socket, &errors);
        }
    }

    if (max > 0)
    {
        max++;
    }
   if (usecs == SOCK_POLL_WAIT_FOREVER)
    {
        ret = select(max, &reads, &writes, NULL, NULL);
    }
    else
    {
        struct timeval tv;

        tv.tv_sec = usecs / USEC_PER_SEC;
        tv.tv_usec = usecs % USEC_PER_SEC;

        ret = select(max, &reads, &writes, NULL, &tv);
    }
/*   ret = select(max, &reads, &writes, &errors, NULL);*/


    if (ret< 0)
    {
        return (ret);
    }
    if (ret == 0)
    {
        return (ret);
    }

   for (i = 0; i < nsocks; i++)
    {
        if (FD_ISSET(socks[i].sinfo->socket, &reads))
        {
            socks[i].wasSet |= SOCK_POLL_READ;
        }
        if (FD_ISSET(socks[i].sinfo->socket, &writes))
        {
            socks[i].wasSet |= SOCK_POLL_WRITE;
        }

        if (FD_ISSET(socks[i].sinfo->socket, &errors))
        {
            socks[i].wasSet |= SOCK_POLL_ERROR;
        }
    }


    return (ret);
}


void *scmHandler(void  *args)
{
    ITS_EVENT evt;
    ITS_INT ret = 0;
    unsigned char count, offset;
    int i;
    ITS_SockPollInfo fds[MAX_SCM_CON];

    while (1)
    {
         int ret;
         offset = 0;

         for(count=0; count<MAX_SCM_CON; count++)
         {
             if(scmconnections[count] != NULL)
             {
                 fds[offset].sinfo = scmconnections[count];
                 fds[offset].lookFor = SOCK_POLL_READ | SOCK_POLL_READ_OOB;
                 offset++;
             }
         }

         ret = SCMSOCK_Poll(fds, offset, 1000);
         if(ret > 0)
         {
             for(count=0; count<offset; count++)
             {
                 if(fds[count].wasSet)
                 {
                     if((fds[count].wasSet & SOCK_POLL_READ) == SOCK_POLL_READ)
                     {
                         if(ScmReadEvent(fds[count].sinfo, &evt) == ITS_SUCCESS)
                         {
                         }
                         else
                         {
                             for(i=0; i<MAX_SCM_CON; i++)
                             {
                                 if(fds[count].sinfo == scmconnections[i])
                                 {
                                     SOCK_Close(scmconnections[i]);
                                     scmconnections[i] = NULL;
				     gsock = NULL;
                                     break;
                                 }
                             }
                         }
                     }
                     if((fds[count].wasSet & SOCK_POLL_ERROR) == SOCK_POLL_ERROR)
                     {
                          for(i =0; i<MAX_SCM_CON;i++)
                          {
                               if(fds[count].sinfo == scmconnections[i])
                               {
                                    SOCK_Close(scmconnections[i]);
                                    scmconnections[i] = NULL;
				    gsock = NULL;
                                    break;
                               }
                          }
                     }
                 }
             }
         }     
    }            /*end of while loop*/
}

int scm_success(ITS_SocketInfo *sock, ITS_OCTET msgGroupId, ITS_OCTET msgType)
{
    ITS_EVENT sendevt;
    int nsend;

    ITS_EVENT_INIT(&sendevt, BSC_LAPDIFM_INST, 5);
    sendevt.data[0] = LAPD_SCM_IF_ID;
    sendevt.data[1] = 0x03;
    sendevt.data[2] = msgGroupId;
    sendevt.data[3] = msgType;
    sendevt.data[4] = LAPD_SCM_SUCCESS;

    nsend = SOCK_Write(sock, (char *)sendevt.data, sendevt.len);
    if(nsend > 0)
    {
    }
    free(sendevt.data); 
}

int scm_fail(ITS_SocketInfo *sock, ITS_OCTET msgGroupId, ITS_OCTET msgType)
{
    ITS_EVENT sendevt;
    int nsend;

    ITS_EVENT_INIT(&sendevt, BSC_LAPDIFM_INST, 5);
    sendevt.data[0] = LAPD_SCM_IF_ID;
    sendevt.data[1] = 0x03;
    if(msgType == LAPD_SCM_PEGS_SHOW)
    {
     msgGroupId = LAPD_SCM_PEGS_NACK;
    }
    sendevt.data[2] = msgGroupId;
    sendevt.data[3] = msgType;
    sendevt.data[4] = LAPD_SCM_ERROR;

    nsend = SOCK_Write(sock, (char *)sendevt.data, sendevt.len);
    if(nsend > 0)
    {
    } 
    free(sendevt.data); 
}



ITS_INT rem_tei_from_db(ITS_OCTET ts, ITS_OCTET laptei, ITS_OCTET apptei)
{
    op_conf_data cfgdata;
    unsigned short alarmId;
    cfgdata.ts = ts;
    cfgdata.tsflag = 1;
    if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
    {
      LAPD_TRACE_CRITICAL(("\nts entry not exist"));
      return -1;
    }
    cfgdata.tsflag = 0;
    cfgdata.lapdTei = laptei;
    cfgdata.appTei = apptei;
    cfgdata.lapdteiflag = 1;
    cfgdata.appteiflag = 1;
    if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 1)
    {
     LAPD_TRACE_DEBUG(("\ntei  exists"));
     if(cfgdata.opflag == 1)
     {
      cfgdata.opflag = 0;
      if((cfgdata.link_status1 == 1) || (cfgdata.link_status2 == 1))
      {
        // Send a LINK DOWN Msg to O&M
        alarmId = 205;
        if(cfgdata.link_status1 == 1)
        {
#ifdef TMCC
         Release_Link(cfgdata.nfd, cfgdata.ifc, cfgdata.sapi1, laptei);
#endif
         SendAlarmTo_SCM(alarmId, cfgdata.appTei, cfgdata.sapi1);
        } 
        if(cfgdata.link_status2 == 1)
        { 
#ifdef TMCC
         Release_Link(cfgdata.nfd, cfgdata.ifc, cfgdata.sapi1, laptei);
#endif
         SendAlarmTo_SCM(alarmId, cfgdata.appTei, cfgdata.sapi2);
        }
        cfgdata.link_status1 = 0;
        cfgdata.link_status2 = 0;
      }
     }
    }
    else
    {
     LAPD_TRACE_MAJOR(("\ntei  not exist"));
     return -1;
    } 
    if( checkAndUpdateLapdCfgValue( LAPD_DEL,   &cfgdata) == 1)
    {
     LAPD_TRACE_DEBUG(("\ntei  delete success"));
     return 0;
    }
    return -1;
}

ITS_INT add_tei_in_db(ITS_OCTET ts, ITS_OCTET laptei, ITS_OCTET apptei)
{
    op_conf_data cfgdata;
    int doStart=0, ret;
    cfgdata.ts = ts;
    cfgdata.tsflag = 1;
    int i;

    cfgdata.ts = ts;
    cfgdata.tsflag = 1;
    if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 1)
    {
      LAPD_TRACE_INFO(("\nts  exist: config tei + sapi"));
      cfgdata.tsflag = 0;
      cfgdata.sapi1 = TRAFFIC_MANAGEMENT_SAPI;
      cfgdata.sapi2 = NETWORK_MANAGEMENT_SAPI;
      cfgdata.lapdTei = laptei;
      cfgdata.appTei = apptei;
      cfgdata.lapdteiflag = 1;
      cfgdata.appteiflag = 1;
      cfgdata.nfd = 0;
      cfgdata.ifc = 0xFF;
      cfgdata.link_status1 = 0;
      cfgdata.link_status2 = 0;
      if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 1)
      {
        LAPD_TRACE_CRITICAL(("\ntei already exists"));
        return -1;
      }
 
      if( checkAndUpdateLapdCfgValue( LAPD_ADD,   &cfgdata) == 0)
      {
        LAPD_TRACE_CRITICAL(("\ntei add cmd failed"));
        return -1;
      }
 
    }
    else
    { 
      cfgdata.ts = ts;
      cfgdata.lapdTei = laptei;
      cfgdata.appTei = apptei;
      cfgdata.sapi1 = TRAFFIC_MANAGEMENT_SAPI;
      cfgdata.sapi2 = NETWORK_MANAGEMENT_SAPI;
      cfgdata.tsflag = 1;
      cfgdata.lapdteiflag = 1;
      cfgdata.appteiflag = 1;
      cfgdata.opflag = 0;
      cfgdata.nfd = 0;
      cfgdata.ifc = 0xFF;
      cfgdata.link_status1 = 0;
      cfgdata.link_status2 = 0;
      if( checkAndUpdateLapdCfgValue( LAPD_ADD,   &cfgdata) == 0)
      {
       LAPD_TRACE_CRITICAL(("\nTei add fail !!"));
       return -1;
      }
      LAPD_TRACE_INFO(("\nTei configured for lapd: tei: %d, apptei: %d, Ts: %d & sapi 0, 62", 
                          laptei, apptei, ts));
    }

      // Open & configure the channel and also put the opflag in running mode
     cfgdata.lapdteiflag = 1;
     cfgdata.appteiflag = 1;
     cfgdata.tsflag = 0;

     /* tommarow i will start from here for corseponding changes in lapd driver code */
     if(checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
     {  
      LAPD_TRACE_CRITICAL(("\ntei flag modify cmd failed"));
      return -1;
     }
     return 0;
}


int ScmReadEvent(ITS_SocketInfo *info, ITS_EVENT *evt)
{
    ITS_EVENT *event;
    ITS_EVENT sendevt;
    int nread, dtlen;
    ITS_OCTET msgGroupId;
    ITS_OCTET msgType;
    ITS_OCTET ts, sapi, tei1, tei2;
    unsigned char buffer[5];
    lapdCoreTimerData *lapdCoreTmrData;
    LapdPegsShow_t    *lapdPegShow;
    ITS_OCTET *data,  appTei;
    int nsend; 
    int ret; 

    nread = SOCK_NonBlockingRead(info, (char *)buffer, 3, 5);
    if(nread <= 0)
    {
       return -1;
    }

    dtlen = (buffer[1] | (buffer[2] << 8));
    evt->data = (ITS_OCTET *)ITS_Malloc(dtlen); 
    evt->len = dtlen;

    nread = SOCK_NonBlockingRead(info, (char *)(evt->data), dtlen, 5);
    if(nread == -1)
    {
        LAPD_TRACE_CRITICAL(("\nRead data length not match"));
        ITS_Free(evt->data);
        evt->data = NULL;
        return -1;
    }
    if(nread > 0)
    {
        data = (ITS_OCTET *)evt->data;

        msgGroupId = *data;
        msgType = *(data + 1);

        switch (msgGroupId)
        {
#ifdef LAPD_HA
            case LAPD_CONFIG_COMPLETE:
            { 
                  //if(lapdHaSupport == 1)
                  //{
                   send_card_state_event_to_lapd(CONFIGURED);
                  //} 
                  break;
            }
          
#endif
            case LAPD_SCM_CFG_MSG:
            {
              switch(msgType)
              {
               case LAPD_SCM_CFG_ADD_TEI:

                    ts =  *(data + 2);
                    tei1 = *(data + 3); 
                    tei2 = *(data + 4); 
                    LAPD_TRACE_MAJOR(("\nMsgType == ADD_TEI, ts=%d, lapdTei=%d, appTei=%d", ts, tei1, tei2));
                    ret = add_tei_in_db(ts, tei1, tei2);
                    if(ret == -1)
                    {
                        scm_fail(info, msgGroupId, msgType);
                    }
                    else
                    {
                        scm_success(info, msgGroupId, msgType);
                    }
                   break;
               case LAPD_SCM_CFG_REM_TEI: 
                    ts =  *(data + 2);
                    tei1 = *(data + 3); 
                    tei2 = *(data + 4); 
                    LAPD_TRACE_MAJOR(("\nMsgType == LAPD_SCM_CFG_REM_TEI, ts=%d, lapdTei=%d, appTei=%d", ts, tei1, tei2));
                    ret = rem_tei_from_db(ts, tei1, tei2);
                    if(ret == -1)
                    {
                        scm_fail(info, msgGroupId, msgType);
                    }
                    else
                    {
                        scm_success(info, msgGroupId, msgType);
                    }
                    break;
               default: 
                    LAPD_TRACE_MAJOR(("\nWrong Msg Type in header! command discarded"));
                    break;
              }
              break; 
             }
            case LAPD_SCM_PEGS_MSG:
            {
                if(msgType == LAPD_SCM_PEGS_SHOW)
                {

             #ifdef TMCC
                    lapdPegShow = (LapdPegsShow_t*)malloc(sizeof(LapdPegsShow_t));
                    memcpy(lapdPegShow, (unsigned char*)data, sizeof(LapdPegsShow_t)); 
                    LAPD_TRACE_MAJOR(("LAPD Peg get cmd from SCM: \n"));
                    if(Get_Stats((LapdPegsShow_t*)lapdPegShow) != ITS_SUCCESS)
                    {   
                     scm_fail(info, msgGroupId, msgType);
                    } 
                    free(lapdPegShow);  
             #endif // TMCC 
 
                }
                else if(msgType == LAPD_SCM_PEGS_CLEAR)
                {
                    LAPD_TRACE_INFO(("\nMsgType == LAPD_SCM_PEGS_CLEAR"));

             #ifdef TMCC  
                    //Clear_Stats(resetFlag, appTei); 
             #endif // TMCC
 
                    scm_success(info, msgGroupId, msgType);
                }
                else
                {
                    LAPD_TRACE_MAJOR(("\nWrong Msg Type in header! command discarded"));
                }
                break;
            }
            case LAPD_SCM_TMR_MSG:
            {
                if(msgType == LAPD_SCM_TMR_SET)
                {
                    LAPD_TRACE_MAJOR(("\nLAPD TIMER MODIFY Cmd received from SCM:"));
                    lapdCoreTmrData = (lapdCoreTimerData*)malloc(sizeof(lapdCoreTimerData)); 
                    memcpy(&lapdCoreTmrData->lapdTimerDefault, &((ISILLapdTimerConfig*)data)->lapdTimerDefault, 
                           sizeof(LapdTmrConfig));
                    memcpy(&lapdCoreTmrData->lapdTimerSatellite, &((ISILLapdTimerConfig*)data)->lapdTimerSatellite, 
                           sizeof(LapdTmrConfig));
                    lapdCoreTmrData->noOfLapdTs = ((ISILLapdTimerConfig*)data)->noOfLapdTs;
                    memcpy(lapdCoreTmrData->lpdTsdetail, &((ISILLapdTimerConfig*)data)->lpdTsdetail, 
                           lapdCoreTmrData->noOfLapdTs*sizeof(LapdTsData));
                      
                    ret = modifyLapdTmr(lapdCoreTmrData);
                    if(ret == -1)
                    {
                     scm_fail(info, msgGroupId, msgType);
                    }
                    else
                    { 
                     scm_success(info, msgGroupId, msgType);
                    }
                    free(lapdCoreTmrData);
                }
                else
                {
                   LAPD_TRACE_MAJOR(("\nWrong Msg Type in header! command discarded"));
                   scm_fail(info, msgGroupId, msgType);
                }
                break;
            }
            default:
            {
                LAPD_TRACE_MAJOR(("\nWrong msgGroupId in header! command discarded"));
                scm_fail(info, msgGroupId, msgType);
                break;
            }
        }
    }

    free(evt->data); 
    return ITS_SUCCESS;
}

