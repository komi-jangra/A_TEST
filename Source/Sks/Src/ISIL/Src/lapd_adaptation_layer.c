
#ifdef LAPD_HA
#include "../Inc/its_mcc_user.h"
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
extern int lapdHaSupport;
#endif


/**
 * Includes
 */
#include <fcntl.h>
#include <tsl3tune.h>
#include <tslink3.h>
#include <ceme.h>
#include <l3_l2.h>
#include <l4cel3.h>
#include <errno.h>
#include <stdio.h>
#include <lapdif_handler.h>
#include <lapd_adaptation_layer.h>
#include <lapd_trace.h>

int GLB_FLAG = 0;

/**
 * Globals
 */
AL3_READ_PROC_DATA_STRUCTURE al3ReadProcDataStructure;

extern ITS_INT AL3_SAPI_ReadProc(ITS_OCTET sapi, ITS_OCTET tei, ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength);
extern ITS_INT AL3_LinkSts_Send(ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength);
void init_lapdCfgData();
extern int  checkAndUpdateLapdCfgValue(char operation, op_conf_data *cfgPtr);
extern void init_scm_interface();
extern void SendAlarmTo_SCM(unsigned short id, ITS_OCTET tei, ITS_OCTET sapi);
extern void SendStatsTo_SCM(ITS_OCTET *databuf, ITS_USHORT datalen, ITS_OCTET appTei);
ITS_INT Release_Link(int fd, int interface, int sapi, int lapdTei);
struct conf_data *CONF_DATA[MAXTSVAL];
//struct ts_teiCfg lapGData.TS_DATA[NUM_APPTEI];
ITS_INT modifyLapdTmr(lapdCoreTimerData *lapdCoreTmrData);
ITS_INT Get_Stats(LapdPegsShow_t    *lapdPegShow);
char lapd_ln_errString[20][100];
ITS_INT modifyLapdTmr(lapdCoreTimerData *lapdCoreTmrData)
{
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;
    op_conf_data cfgdata;
    int interface;
 
     LAPD_TRACE_INFO(("timer modify ts details: ts1 :%d, ts2: %d", 
                       lapdCoreTmrData->lpdTsdetail[0].ts,
                       lapdCoreTmrData->lpdTsdetail[1].ts));
     cfgdata.ts = CONF_DATA[lapdCoreTmrData->lpdTsdetail[0].ts]->ts;
     cfgdata.ifc = CONF_DATA[lapdCoreTmrData->lpdTsdetail[0].ts]->ifc;
     cfgdata.lapdTei = CONF_DATA[lapdCoreTmrData->lpdTsdetail[0].ts]->lapdTei;
     cfgdata.nfd = CONF_DATA[lapdCoreTmrData->lpdTsdetail[0].ts]->nfd;

     if(cfgdata.nfd == 0)
     {
      LAPD_TRACE_INFO(("timer modify command dropped: cause no channel configured yet"));
      return;
     }
     interface = cfgdata.ifc;  

           
          LAPD_TRACE_INFO(("Sending LAPD timer modify cmd:->"));
          memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
          memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));
          l4cel3msg.primcode     = N_MODIRY_LAYER_TIMER_RQ;


          l4cel3msg.lci_chantype = interface << 8 | DCH_PCHAN;
          l4cel3msg.datalen      = sizeof(lapdCoreTimerData);
          l4cel3msg.dataptr = malloc(sizeof(lapdCoreTimerData));
          memcpy(l4cel3msg.dataptr, lapdCoreTmrData, sizeof(lapdCoreTimerData));

          reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
          reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
          reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
          reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
          reqdataxfer.requestor_pid = getpid();

         if(cfgdata.nfd == 0)
         {
          LAPD_TRACE_INFO(("TMR Config dropped: fd value is zero"));
          return;
         }

        write(cfgdata.nfd,   (const void *) &reqdataxfer,
             sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);

        free(l4cel3msg.dataptr);
    return ITS_SUCCESS;
}

#ifdef LAPD_HA
int G_CARD_STATE = 0;
int lapd_cardstate = STANDBY;
void send_card_state_event_to_lapd(int cardState);

void send_card_state_event_to_lapd(int cardEvent)
{
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;
    op_conf_data cfgdata;
    int interface;
    int chanloop;
    for(chanloop = 0; chanloop < MAXTSVAL; chanloop++)
    {
     if((CONF_DATA[chanloop] != NULL) && (CONF_DATA[chanloop]->opflag == 1))
      {
       cfgdata.ts = CONF_DATA[chanloop]->ts;
       cfgdata.ifc = CONF_DATA[chanloop]->ifc;
       cfgdata.lapdTei = CONF_DATA[chanloop]->lapdTei;
       cfgdata.nfd = CONF_DATA[chanloop]->nfd;
       break;
      }
    }
    if((cardEvent == CARD_ACTIVE ) || (cardEvent == STANDBY))
     {
      lapd_cardstate = cardEvent;
     }
  
    if(chanloop == MAXTSVAL)
    {
     LAPD_TRACE_INFO(("lapd state event stored: cause no channel configured yet"));
    return;
    }
    interface = cfgdata.ifc;  

           
     switch(cardEvent)
     {
      case CONFIGURED:
          LAPD_TRACE_CRITICAL(("Sending config complete to lapd core"));
          memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
          memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));
          l4cel3msg.primcode     = N_STAT_RQ;
          l4cel3msg.cause[0]     = CTRL_CONFIG_COMPLETE;
          l4cel3msg.cause[1]     = 1;
          if(lapdHaSupport == 0)
          {
           l4cel3msg.cause[1]     = 0; 
          }
          l4cel3msg.lapdTei          = 0;			
          l4cel3msg.lci_chantype = interface << 8 | DCH_PCHAN;
          l4cel3msg.datalen      = 0;
          reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
          reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
          reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
          reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
          reqdataxfer.requestor_pid = getpid();
          ioctl(cfgdata.nfd, LAPD_IOCMSGCTR, reqdataxfer);
          printf(" Ctrl command sent successfully\n");

          LAPD_TRACE_CRITICAL(("Sending card state change event to lapd core"));
          memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
          memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));
          l4cel3msg.primcode        = N_STAT_RQ;
          l4cel3msg.cause[0]        = CTRL_CARD_STATE;
          l4cel3msg.cause[1]        = lapd_cardstate;
          l4cel3msg.lapdTei             = 0;			
          l4cel3msg.lci_chantype    = interface << 8 | DCH_PCHAN;
          l4cel3msg.datalen         = 0;
          reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
          reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
          reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
          reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
          reqdataxfer.requestor_pid = getpid();
          ioctl(cfgdata.nfd, LAPD_IOCMSGCTR, reqdataxfer);
          printf(" Ctrl command sent successfully\n");
          break;  
            
      case CARD_ACTIVE:
      case STANDBY:
      case PEER_ABSENT:
          LAPD_TRACE_CRITICAL(("Sending card state change event to lapd core: event :%d", cardEvent));
          memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
          memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));
          l4cel3msg.primcode        = N_STAT_RQ;
          l4cel3msg.cause[0]        = CTRL_CARD_STATE;
          l4cel3msg.cause[1]        = cardEvent;
          l4cel3msg.lapdTei             = 0;			
          l4cel3msg.lci_chantype    = interface << 8 | DCH_PCHAN;
          l4cel3msg.datalen         = 0;
          reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
          reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
          reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
          reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
          reqdataxfer.requestor_pid = getpid();
          ioctl(cfgdata.nfd, LAPD_IOCMSGCTR, reqdataxfer);
          printf(" Ctrl command sent successfully\n");
          break; 
 
            
            
     } 


      /*  return write( cfg_data[0].nfd, (const void *) &reqdataxfer,
                   sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);*/
}


#endif

void  DUMP_L3_HDR(struct l4_ce_l3_msg *tsl3LinuxWrapper)
{
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->primcode  : %d", tsl3LinuxWrapper->primcode));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->receipt  : %d", tsl3LinuxWrapper->receipt));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->d_attrib  : %d", tsl3LinuxWrapper->d_attrib));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->connid  : %d", tsl3LinuxWrapper->connid));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->datalen  : %d", tsl3LinuxWrapper->datalen));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->cause[0]  : %d", tsl3LinuxWrapper->cause[0]));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->cause[1]  : %d", tsl3LinuxWrapper->cause[1]));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->lapdTei  : %d", tsl3LinuxWrapper->lapdTei));
 LAPD_TRACE_CRITICAL(("DUMP: l4_ce_l3_ms->lci_chantype  : %d", tsl3LinuxWrapper->lci_chantype));
}


void init_Lapd_LinkSts_ErrString()
{
 strcpy(lapd_ln_errString[0],  "Normal link release App disconnected");
 strcpy(lapd_ln_errString[ERROR_TM_RECOV],  "T200 timer re-tries reach max value");
 strcpy(lapd_ln_errString[ERROR_TRX_DISC_RCV],  "Disconnect recvd from TRX/BIC");
 strcpy(lapd_ln_errString[ERROR_INVALID_NR],  "Invalid NR value rcvd");
 strcpy(lapd_ln_errString[ERROR_INCORRECT_FRAME],  "Invalid frame received from TRX/BIC");
 strcpy(lapd_ln_errString[ERROR_DM_RCV],  "DM msg received from TRX/BIC");
 strcpy(lapd_ln_errString[ERROR_FRMR_RCV],  "Framer reject received from TRX/BIC");
 strcpy(lapd_ln_errString[ERROR_RED_HAND],  "Lapd redundancy handling error");
}


void sendToSocket(ITS_OCTET sapi, ITS_OCTET tei,
ITS_OCTET *databuf, ITS_USHORT datalen)
{
    AL3_SAPI_ReadProc(sapi, tei, databuf, datalen);
}

void * Read_From_Module(void *arg)
{
    struct timeval wait;   
    op_conf_data cfgdata;
    fd_set    allfds;
    ITS_INT   i = 0, numset;
    ITS_INT   maxFd = 0;
    ITS_OCTET apptei; 
    //ITS_OCTET sysbuf[SYSBUFSIZ + sizeof(struct l4_ce_l3_msg)];
    ITS_OCTET sysbuf[1000];
    init_Lapd_LinkSts_ErrString();

    while(1)
    {
      wait.tv_sec = 1;
      wait.tv_usec =0;
      select(0,  NULL, NULL, NULL, &wait); 
      if(GLB_FLAG == 1)
            break; 
    } 
   
    while(1)
    {
       maxFd = lapGData.maxFd ; 
       FD_ZERO(&allfds);
       allfds = lapGData.allLapdFd;

      /* if(CONF_DATA[40] != NULL)  
       LAPD_TRACE_INFO(("lapd read variables: fd %d, maxFd: %d", 
                          CONF_DATA[40]->nfd, maxFd));*/
       wait.tv_sec = 10;
       wait.tv_usec =0;
       numset = select(maxFd + 1, &allfds, NULL, NULL, &wait);/* this is done to for select on fds 
                                                                 dynamically as we keep adding fd's */ 

//        if(select(maxFd + 1, &allfds, NULL, NULL, NULL) < 0)
       if(numset <= 0)
       {
           continue;
       }

        //for(i=0; i<NUM_IFC; i++)
       
       for(i=0; i<MAX_TS_VAL; i++)
       {
           int val = 0;

            /* To more optimize lapd user processing here we can add channel offset */
           if((CONF_DATA[i] != NULL) && (CONF_DATA[i]->nfd > 0) )
           {
            cfgdata.nfd = CONF_DATA[i]->nfd;
            cfgdata.ts = CONF_DATA[i]->ts;
           }
           else 
           {
                continue;
           }

            
           //LAPD_TRACE_INFO(("loop for i val: %d, fd: %d",i, cfgdata.nfd));
 
           if(!(FD_ISSET(cfgdata.nfd, &allfds)))
           {continue; }
           
           if((val = read(cfgdata.nfd, sysbuf, SYSBUFSIZ + sizeof(struct l4_ce_l3_msg))) <= 0)
           {
             LAPD_TRACE_CRITICAL(("Read_From_Module: " \
             "Failed to read from module, return val: %d ...", val));
             continue;
           }
          struct l4_ce_l3_msg *l4cel3msg;
          l4cel3msg          = (struct l4_ce_l3_msg*)sysbuf;
#if 0
           LAPD_TRACE_INFO(("Read from lapdTs: %d, fd: %d, retVal: %d, dataLen %d\n", 
                           cfgdata.ts, cfgdata.nfd, val, l4cel3msg->datalen));
           PRINT_HEX_DUMP(DEBUG,sysbuf, val);
#endif	   

          ITS_OCTET sapi     = l4cel3msg->cause[1];
          ITS_OCTET msg_type = l4cel3msg->cause[0];
          ITS_OCTET ifid     = ((l4cel3msg->lci_chantype) >> 8 ) & 0xFF;

          cfgdata.ts = CONF_DATA[i]->ts;
          cfgdata.tsflag = 0;
          cfgdata.lapdTei = l4cel3msg->lapdTei;
          cfgdata.lapdteiflag = 1;



           if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
           {
            LAPD_TRACE_CRITICAL(("lapd config data get fail !bug! " ));
            continue;
           }
           apptei      = cfgdata.appTei;
          
           if(apptei == 0xff)
           {
            LAPD_TRACE_CRITICAL(("\nInvalid appTei found App TEI"));
            continue;
           } 
           LAPD_TRACE_DEBUG(("LAPD params: lapd ts: %d, lapd tei: %d, apptei: %d, sapi: %d, ifc: %d",
                             cfgdata.ts, cfgdata.lapdTei, apptei, sapi, cfgdata.ifc));  

          ITS_OCTET *databuf = (ITS_OCTET*)&sysbuf[sizeof(struct l4_ce_l3_msg)]; //l4cel3msg->dataptr;
          ITS_USHORT datalen  = l4cel3msg->datalen;
   

          switch(msg_type)
          {
           case L2_EST_CF:
           {
               ITS_OCTET nonAbisData[1];
               unsigned short alarmId;
               if(sapi == cfgdata.sapi1)
               {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi1 = sapi; 
                 cfgdata.link_status1 = 1;
                 cfgdata.link_status = 1;
                 cfgdata.lapdteiflag = 0;
                if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
               }
               else if(sapi == cfgdata.sapi2)
               {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi2 = sapi; 
                 cfgdata.link_status2 = 1;
                 cfgdata.link_status = 1;
                 cfgdata.lapdteiflag = 0;
                if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
               } 
               alarmId = 204;
               nonAbisData[0] = LAPD_LINK_UP;
               LAPD_TRACE_MAJOR(("\nLAPD_LINK_UP from: channel=%d, sapi=%d, tei=%d",
                               cfgdata.ts, sapi, apptei));
               sendToSocket(sapi, apptei, nonAbisData, 1);
               SendAlarmTo_SCM(alarmId, apptei, sapi);
               break;
           }
           case L2_EST_IN:
           {
                ITS_OCTET nonAbisData[1];
                unsigned short alarmId;
                if(sapi == cfgdata.sapi1)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi1 = sapi;; 
                 cfgdata.link_status1 = 1;
                 cfgdata.link_status  = 1;
                 cfgdata.lapdteiflag = 0;
                 if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                }
                else if(sapi == cfgdata.sapi2)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi2 = sapi;; 
                 cfgdata.link_status2 = 1;
                 cfgdata.link_status  = 0;
                 cfgdata.lapdteiflag  = 0;
                if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                } 
                alarmId = 204;
                nonAbisData[0] = LAPD_LINK_UP;
                LAPD_TRACE_MAJOR(("\nLAPD_LINK_UP from: channel=%d, sapi=%d, tei=%d", 
                                cfgdata.ts, sapi, apptei));
                sendToSocket(sapi, apptei, nonAbisData, 1);
                SendAlarmTo_SCM(alarmId, apptei, sapi);
                break;
           }
           case L2_REL_IN:
           {
                ITS_OCTET nonAbisData[1];
                unsigned short alarmId;
                if(sapi == cfgdata.sapi1)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi1 = sapi; 
                 cfgdata.link_status1 = 1;
                 cfgdata.link_status  = 0;
                 cfgdata.lapdteiflag = 0;
                 if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                }
                else if(sapi == cfgdata.sapi2)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi2 = sapi; 
                 cfgdata.link_status2 = 1;
                 cfgdata.link_status = 0;
                 cfgdata.lapdteiflag = 0;
                if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                } 
                alarmId = 205;
                nonAbisData[0] = LAPD_LINK_DOWN;
                LAPD_TRACE_MAJOR(("\nLAPD_LINK_DOWN from: channel=%d, sapi=%d, tei=%d 'Cz- %s'",
                                cfgdata.ts, sapi, apptei, lapd_ln_errString[l4cel3msg->d_attrib]));
                sendToSocket(sapi, apptei, nonAbisData, 1);
                SendAlarmTo_SCM(alarmId, apptei, sapi);
                break;
           }
           case L2_REL_CF:
           {
                ITS_OCTET nonAbisData[1];
                unsigned short alarmId;
                if(sapi == cfgdata.sapi1)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi1 = sapi; 
                 cfgdata.link_status1 = 1;
                 cfgdata.link_status  = 0;
                 cfgdata.lapdteiflag = 0;
                 if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                }
                else if(sapi == cfgdata.sapi2)
                {
                 cfgdata.lapdTei = l4cel3msg->lapdTei;
                 cfgdata.sapi2 = sapi; 
                 cfgdata.link_status2 = 1;
                 cfgdata.link_status = 0;
                 cfgdata.lapdteiflag = 0;
                if( checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
                 {
                  LAPD_TRACE_CRITICAL(("lapd config modify fail !bug! " ));
                 }
                } 
                alarmId = 205;
                nonAbisData[0] = LAPD_LINK_DOWN;
                LAPD_TRACE_MAJOR(("\nLAPD_LINK_DOWN from: channel=%d, sapi=%d, tei=%d, 'Cz: %s'",
                                 cfgdata.ts, sapi, apptei, lapd_ln_errString[l4cel3msg->d_attrib]));
                sendToSocket(sapi, apptei, nonAbisData, 1);
                SendAlarmTo_SCM(alarmId, apptei, sapi);
                break;
           }
           case DUMMY_DATA_IN:
           {
                if(datalen >= 5)
                {
                 LAPD_TRACE_INFO(("\nI-FRM SendToApp: channel = 0x%x sapi = 0x%x tei = 0x%x Data = 0x%x 0x%x 0x%x 0x%x 0x%x", cfgdata.ts, sapi, apptei, databuf[0], databuf[1], databuf[2], databuf[3], databuf[4]));
                }
                else
                {   
                 LAPD_TRACE_INFO(("\nI-FRM SendToApp: channel = 0x%x sapi = 0x%x tei = 0x%x Data = 0x%x", cfgdata.ts, sapi, apptei, databuf[0]));
                }
                sendToSocket(sapi, apptei, databuf, datalen);
                    break;
           }
           case DUMMY_U_DATA_IN:
           {
               if(datalen >= 5)
               {
                LAPD_TRACE_INFO(("\nUI-FRM SendToApp: channel = 0x%x sapi = 0x%x tei = 0x%x Data = 0x%x 0x%x 0x%x 0x%x 0x%x", cfgdata.ts, sapi, apptei, databuf[0], databuf[1], databuf[2], databuf[3], databuf[4]));
               }
               else
               {
                LAPD_TRACE_INFO(("\nUI-FRM SendToApp: channel = 0x%x sapi = 0x%x tei = 0x%x Data = 0x%x", cfgdata.ts, sapi, apptei, databuf[0]));
               } 
               sendToSocket(sapi, apptei, databuf, datalen);
               break;
           }
           case N_GET_LAYER_STATS_RQ:
           {
                LAPD_TRACE_INFO(("\nN_GET_LAYER_STATS_RQ: pegdata length %d\n", datalen));
                #ifdef DEBUG_BUF 
                PRINT_HEX_DUMP(DEBUG,databuf,datalen);
                #endif
                SendStatsTo_SCM(databuf, datalen, apptei);
                break;
           }
           case N_GET_LINK_STATUS_RQ:
           {
                LAPD_TRACE_INFO(("\nN_GET_LINK_STATUS_RQ:: protocol data length %d\n", datalen));
                //#ifdef DEBUG_BUF 
                PRINT_HEX_DUMP(DEBUG,databuf,datalen);
               // #endif
               /* righ now link status request is only for 2 trx's in future if 
                  it will be more than 2 then we wil implement loop here */
               cfgdata.tsflag = 0;
               cfgdata.lapdTei = ((LapdLinkStatusResp*)databuf)->lapdLinkStsResp[0].tei;
               cfgdata.lapdteiflag = 1;
               if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
               {
                LAPD_TRACE_CRITICAL(("lapd config data get fail !bug! " ));
                continue;
               }
               ((LapdLinkStatusResp*)databuf)->lapdLinkStsResp[0].tei=cfgdata.appTei;

               cfgdata.tsflag = 0;
               cfgdata.lapdTei = ((LapdLinkStatusResp*)databuf)->lapdLinkStsResp[1].tei;
               cfgdata.lapdteiflag = 1;
               if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
               {
                LAPD_TRACE_CRITICAL(("lapd config data get fail !bug! " ));
                continue;
               } 

               ((LapdLinkStatusResp*)databuf)->lapdLinkStsResp[1].tei=cfgdata.appTei;
                AL3_LinkSts_Send(databuf, datalen);
                
                break;
           }
           default:
           {
              LAPD_TRACE_MAJOR(("\nUNKNOWN MESSAGE from: channel=%d, sapi=%d, tei=%d", cfgdata.ts, sapi, apptei));
              break;
           }
          }
           break;
       } // for
    } // while          
}


ITS_INT 
get_Lapd_Link_Sts_Req(
ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength)
{
    ITS_OCTET sapi;
    ITS_OCTET tei;
    ITS_INT chan, loop = 0;
    op_conf_data cfgdata;
    struct req_data_xfer reqdataxfer;
    LapdLinkStsGet lapdLinkStsGet;
    //unsigned char data = malloc(264);//)[264];
    struct l4_ce_l3_msg lapdStackMsg;
    struct req_data_xfer tsl3LinuxWrapper;
    for(loop=0;loop < 2; loop++)
    {
     tei = dataBuffer[loop + 1]; 
     chan = lapGData.TS_DATA[tei];
     if(chan == 0xff)
     {
      LAPD_TRACE_CRITICAL(("\n TEI Not configured !"));
      return !ITS_SUCCESS;
     }  
    
     cfgdata.ts = chan;
     cfgdata.appTei = tei;
     cfgdata.lapdTei = 0;
     cfgdata.appteiflag = 1;
     cfgdata.tsflag = 0;
     cfgdata.lapdteiflag = 0;
     if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
     {
      LAPD_TRACE_CRITICAL(("\n appTei not configured  bug!!!"));
      return !ITS_SUCCESS;
     } 
     if(cfgdata.ifc == 0xFF)
     {
      LAPD_TRACE_CRITICAL(("\n Interface Not found ERROR !!"));
      return !ITS_SUCCESS;
     } 
   
    /* i will fil this get struct here n on respon i will parse the resp on above struct n send to app
       also get from hash table wud be done */
    lapdLinkStsGet.lapdTeiInfo[loop].ts = cfgdata.ts;
    lapdLinkStsGet.lapdTeiInfo[loop].lapdTei =cfgdata.lapdTei ;
    lapdLinkStsGet.lapdTeiInfo[loop].lci_chantype = cfgdata.ifc << 8 | DCH_PCHAN;;
    LAPD_TRACE_INFO(("get_Lapd_Link_Sts_Req: apptei[%d]: %d, lapTei: %d, ts: %d", loop, tei, cfgdata.lapdTei, cfgdata.ts));
  }
  //LAPD_TRACE_INFO(("DATA DUMP"));
  //PRINT_HEX_DUMP(DEBUG,data, sizeof(LapdLinkStsGet));

  lapdStackMsg.primcode     = N_GET_LINK_STATUS_RQ;
  lapdStackMsg.cause[0]     = DUMMY_DATA;
  lapdStackMsg.cause[1]     = 0; /* sapi */
  lapdStackMsg.lapdTei      = cfgdata.lapdTei;
  lapdStackMsg.datalen      = sizeof(LapdLinkStsGet);
  lapdStackMsg.dataptr      = malloc(sizeof(LapdLinkStsGet));
  memcpy(lapdStackMsg.dataptr, &lapdLinkStsGet, sizeof(LapdLinkStsGet));

  LAPD_TRACE_INFO(("LAPD Link status get send: ts %d:, lapdTei %d: dataLen: %d",
                       lapdLinkStsGet.lapdTeiInfo[0].ts, lapdLinkStsGet.lapdTeiInfo[0].lapdTei,
                       lapdStackMsg.datalen));
  LAPD_TRACE_INFO(("DATA DUMP"));
  PRINT_HEX_DUMP(DEBUG, lapdStackMsg.dataptr, sizeof(LapdLinkStsGet));


  
  lapdStackMsg.reserved1    = 0L;
  lapdStackMsg.reserved2    = 0L;
  lapdStackMsg.receipt      = NOACK;
  lapdStackMsg.lci_chantype = cfgdata.ifc << 8 | DCH_PCHAN;

  tsl3LinuxWrapper.l4_ce_ptr     = &lapdStackMsg;
  tsl3LinuxWrapper.requestor_pid = getpid();
  tsl3LinuxWrapper.connid        = &lapdStackMsg.connid;
  tsl3LinuxWrapper.tsl3_ipb_ptr  = lapdStackMsg.dataptr;
  tsl3LinuxWrapper.datalen       = lapdStackMsg.datalen;
    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &lapdStackMsg;
    reqdataxfer.connid        = (unsigned short *) &lapdStackMsg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) lapdStackMsg.dataptr;
    reqdataxfer.datalen       = (unsigned short) lapdStackMsg.datalen;
    reqdataxfer.requestor_pid = getpid();

    write(
    cfgdata.nfd,
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + lapdStackMsg.datalen);

    free(lapdStackMsg.dataptr);
    return ITS_SUCCESS;
}


ITS_INT 
AL3_Send_L2Req(
ITS_OCTET sapi,
ITS_OCTET tei,
ITS_OCTET *dataBuffer, ITS_USHORT dataBufferLength)
{
    op_conf_data cfgdata;
    unsigned char data[264];
    struct l4_ce_l3_msg lapdStackMsg;
    struct req_data_xfer tsl3LinuxWrapper;
#ifdef LAPD_HA
    LAPD_TRACE_DEBUG(("G_CARD_STATE : %d", G_CARD_STATE));
    if( G_CARD_STATE != CARDSTATE_ACTIVE)
    {
     LAPD_TRACE_CRITICAL(("Card state is not active : Application Msg dumped"));
     return !ITS_SUCCESS;
    }
#endif

    ITS_INT chan = lapGData.TS_DATA[tei];
    if(chan == 0xff)
    {
     LAPD_TRACE_CRITICAL(("\n TEI Not configured !"));
     return !ITS_SUCCESS;
    } 
    
   cfgdata.ts = chan;
   cfgdata.appTei = tei;
   cfgdata.lapdTei = 0;
   cfgdata.appteiflag = 1;
   cfgdata.tsflag = 0;
   cfgdata.lapdteiflag = 0;
   if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
   {
     LAPD_TRACE_CRITICAL(("\n appTei not configured  bug!!!"));
     return !ITS_SUCCESS;
   } 
   if(cfgdata.ifc == 0xFF)
   {
    LAPD_TRACE_CRITICAL(("\n Interface Not found ERROR !!"));
    return !ITS_SUCCESS;
   } 

    /**
    * Non abis message
    */
   if(dataBufferLength == 1)
   {
        if(dataBuffer[0] == LAPD_LINK_RELEASE)
        {
            LAPD_TRACE_INFO((
            "AL3_Send_L2TrafficMgmtReq: Send Disconnect message: for TEI: %d", tei));
#ifdef TMCC
            Release_Link(cfgdata.nfd, cfgdata.ifc, sapi, cfgdata.lapdTei);
#endif
            return ITS_SUCCESS;
        }

        if(dataBuffer[0] != LAPD_LINK_ESTABLISH)
        {
            LAPD_TRACE_INFO((
            "AL3_Send_L2Req: Failed to send RSL message: "\
            "Unknown event for TEI: %d", tei));
            return !ITS_SUCCESS;
        }

        LAPD_TRACE_INFO(("\nAL3_Send_L2Req: "\
        "Establishing link for tei: %d, ifc: %d", tei, cfgdata.ifc));

#ifdef TMCC
        if(Establish_Link(cfgdata.nfd, cfgdata.ifc, sapi, cfgdata.lapdTei) < 0)
        {
            LAPD_TRACE_CRITICAL(("\nAL3_Send_L2Req: " \
            "Could not establish link for channel: %d ...", cfgdata.ts));
            LAPD_TRACE_CRITICAL(("\nAL3_Initialize: " \
            "errno: %d ...", errno));
            data[0] = LAPD_LINK_DOWN;
            AL3_SAPI_ReadProc(sapi, tei, data, dataBufferLength);
        }	
#endif
    return ITS_SUCCESS;	
   }

    /**
    * Abis message, proceed normal
    */
  memcpy(data + L2HDRSIZE, dataBuffer, dataBufferLength);
#ifndef LAPD_HA  
  if(cfgdata.sapi1 == sapi)
  { 
    if(!cfgdata.link_status1)
    {
      LAPD_TRACE_CRITICAL((
                  "AL3_Send_L2Req: Failed to send RSL message: "\
                  "link is down for interface: %d", cfgdata.ifc));
      return !ITS_SUCCESS;
    }
  }
  else if(cfgdata.sapi2 == sapi)
  { 
   if(!cfgdata.link_status2)
   {
         LAPD_TRACE_CRITICAL((
           "AL3_Send_L2Req: Failed to send RSL message: "\
           "link is down for interface: %d", cfgdata.ifc));
           return !ITS_SUCCESS;
   }
  }
#endif
	
  lapdStackMsg.primcode     = N_STAT_RQ;
  lapdStackMsg.cause[0]     = DUMMY_DATA;
  lapdStackMsg.cause[1]     = sapi;
  lapdStackMsg.lapdTei      = cfgdata.lapdTei;
  lapdStackMsg.datalen      = dataBufferLength + L2HDRSIZE;
  lapdStackMsg.dataptr      = data;
  lapdStackMsg.reserved1    = 0L;
  lapdStackMsg.reserved2    = 0L;
  lapdStackMsg.receipt      = NOACK;
  lapdStackMsg.lci_chantype = cfgdata.ifc << 8 | DCH_PCHAN;

  tsl3LinuxWrapper.l4_ce_ptr     = &lapdStackMsg;
  tsl3LinuxWrapper.requestor_pid = getpid();
  tsl3LinuxWrapper.connid        = &lapdStackMsg.connid;
  tsl3LinuxWrapper.tsl3_ipb_ptr  = lapdStackMsg.dataptr;
  tsl3LinuxWrapper.datalen       = lapdStackMsg.datalen;
  //DUMP_L3_HDR(&tsl3LinuxWrapper);
  if(-1 == write( cfgdata.nfd,  &tsl3LinuxWrapper, 
        sizeof(struct l4_ce_l3_msg) + lapdStackMsg.datalen))
    {
        LAPD_TRACE_CRITICAL((
        "AL3_Send_L2Req: write: "\
        "Failed to write to module, errno: %d", errno));
        return !ITS_SUCCESS;
    }
    
    return ITS_SUCCESS;
}

ITS_INT LAPDIF_Init()
{
    pthread_t tid = 0;

    LAPD_TRACE_INFO(("\nLAPDIF_Init call ....."));

    init_lapdCfgData();

    init_scm_interface();

    if(pthread_create(&tid, NULL, Read_From_Module, NULL))
    {
        LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
        "Could not create thread for reading ..."));
        return !ITS_SUCCESS;
    }
    LAPD_TRACE_DEBUG(("\nLAPDIF_Init: pthread_create() success ..."));

    return ITS_SUCCESS;
}
#ifdef TMCC

ITS_INT Load_Config_Param(int fd, int tei, int i)
{
    struct cup_parms cupparms;
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;

    memset(&cupparms, 0x00, sizeof(struct cup_parms));
    memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));

    /**
    * This will configure the interface for HDLC
    * This should be != 0
    * Till now I could not see any other configuration
    * parameter that is needed by the stack
    */
    cupparms.swv_model = 13;
    cupparms.sigtei[0] = tei;

    l4cel3msg.primcode  = N_STAT_RQ;
    l4cel3msg.lapdTei   = tei;
    l4cel3msg.cause[0]  = CUP_PARMS_LOAD;
    l4cel3msg.cause[1]  = i;
    l4cel3msg.datalen   = sizeof(struct cup_parms);
    l4cel3msg.dataptr   = (unsigned char*) &cupparms;
    //DUMP_L3_HDR(&l4cel3msg);

    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
    reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
    reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
    reqdataxfer.requestor_pid = getpid();		

    return MCC_Load_Cup_Param(fd, &reqdataxfer);
}

ITS_INT Start_Module(int fd)
{
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;
#ifdef LAPD_HA
    char ipAdds[50];
    char  *config = NULL;
    memset(ipAdds, 0x00,50);
#endif
    memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));
#ifdef LAPD_HA
 
    config = getenv("NET_PP_IP");
    if(config != NULL)
    {
     LAPD_TRACE_INFO(("lapd self pp ip val : %s", config));
     strcpy(ipAdds,config);
    }
    config = getenv("config_PEER_PP_IP");
    if(config != NULL)
    {
     LAPD_TRACE_INFO(("lapd peer pp ip val : %s", config));
     strcpy(&ipAdds[21],config);
    }

#endif    
    l4cel3msg.primcode     = N_START_RQ;
    l4cel3msg.lci_chantype = DCH_PCHAN;
#ifdef LAPD_HA
    l4cel3msg.datalen      = 50;		
    l4cel3msg.dataptr      = ipAdds;
#else
    l4cel3msg.datalen      = 0;		
#endif
    //DUMP_L3_HDR(&l4cel3msg);

    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
    reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
    reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
    reqdataxfer.requestor_pid = getpid();	

    return write(
    fd, 
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);
}

ITS_INT Clear_Stats()
{
    op_conf_data cfgdata;
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;
    int interface;
    int chanloop;
    for(chanloop = 0; chanloop < MAXTSVAL; chanloop++)
    {
     if((CONF_DATA[chanloop] != NULL) && (CONF_DATA[chanloop]->opflag == 1))
      {
       cfgdata.ts = CONF_DATA[chanloop]->ts;
       cfgdata.ifc = CONF_DATA[chanloop]->ifc;
       cfgdata.lapdTei = CONF_DATA[chanloop]->lapdTei;
       cfgdata.nfd = CONF_DATA[chanloop]->nfd;
       break;
      }  
    } 
    if(chanloop == MAXTSVAL)
    {
     LAPD_TRACE_CRITICAL(("Error: PEG Clear request dumped!! cause: lapd not configured"));
     return;
    }  

    interface = cfgdata.ifc;  
    memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));

    l4cel3msg.primcode     = N_RESET_LAYER_STATS_RQ;
    l4cel3msg.lci_chantype = interface << 8 | DCH_PCHAN;
    l4cel3msg.datalen      = 0;

    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
    reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
    reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
    reqdataxfer.requestor_pid = getpid();

    return write(
    cfgdata.nfd,
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);
}

ITS_INT Get_Stats(LapdPegsShow_t    *lapdPegShow)
{
    op_conf_data cfgdata;
    struct l4_ce_l3_msg lapdStackMsg;
    struct req_data_xfer reqdataxfer;
    LapdPegCmd lapdPegCmd;
    int interface, loop;
    ITS_INT chan;

#ifdef LAPD_HA
    LAPD_TRACE_CRITICAL(("G_CARD_STATE : %d", G_CARD_STATE));
    if( G_CARD_STATE != CARDSTATE_ACTIVE)
    {
     LAPD_TRACE_CRITICAL(("Card state is not active : Application Msg dumped"));
     return !ITS_SUCCESS;
    }
#endif
   
    lapdPegCmd.count = lapdPegShow->count;

    for(loop=0; loop < lapdPegShow->count; loop++) 
    {
      chan = lapGData.TS_DATA[lapdPegShow->appTeiInfo[loop]];
      if(chan == 0xff)
      {
       LAPD_TRACE_CRITICAL(("\n TEI Not configured !"));
       return !ITS_SUCCESS;
      }

     cfgdata.ts = chan;
     cfgdata.appTei = lapdPegShow->appTeiInfo[loop];
     cfgdata.lapdTei = 0;
     cfgdata.appteiflag = 1;
     cfgdata.tsflag = 0;
     cfgdata.lapdteiflag = 0;
     if( checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
     {
      LAPD_TRACE_CRITICAL(("\n appTei not configured  !!!"));
      return !ITS_SUCCESS;
     }
     if(cfgdata.ifc == 0xFF)
     {
       LAPD_TRACE_CRITICAL(("\n Interface Not found ERROR !!"));
       return !ITS_SUCCESS;
     }
     lapdPegCmd.lapdTeiInfo[loop].ts      = cfgdata.ts;
     lapdPegCmd.lapdTeiInfo[loop].lapdTei = cfgdata.lapdTei; 
     lapdPegCmd.lapdTeiInfo[loop].lci_chantype = cfgdata.ifc; 
     LAPD_TRACE_INFO(("LAPD Peg get cmd: ts %d:, lapdTei %d: appTei %d , count %d",
                     cfgdata.ts, cfgdata.lapdTei, cfgdata.appTei, lapdPegShow->count));
    }
    interface = cfgdata.ifc;  
    memset(&lapdStackMsg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));

    lapdStackMsg.primcode     = N_GET_LAYER_STATS_RQ;
    lapdStackMsg.lci_chantype = interface << 8 | DCH_PCHAN;
    lapdStackMsg.lapdTei   = cfgdata.lapdTei;
    lapdStackMsg.cause[1]     = lapdPegShow->pegResetFlag;; /* reset flag */
    lapdStackMsg.datalen      = sizeof(LapdPegCmd);
    lapdStackMsg.dataptr = (unsigned char*)malloc(sizeof(LapdPegCmd)); 
    memcpy(lapdStackMsg.dataptr, &lapdPegCmd, sizeof(LapdPegCmd));


    LAPD_TRACE_INFO(("LAPD Peg get send: ts %d:, lapdTei %d: , count %d, dataLen: %d",
                       lapdPegCmd.lapdTeiInfo[0].ts, lapdPegCmd.lapdTeiInfo[0].lapdTei,
                       lapdPegCmd.count, lapdStackMsg.datalen));
    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &lapdStackMsg;
    reqdataxfer.connid        = (unsigned short *) &lapdStackMsg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) lapdStackMsg.dataptr;
    reqdataxfer.datalen       = (unsigned short) lapdStackMsg.datalen;
    reqdataxfer.requestor_pid = getpid();

    write(
    cfgdata.nfd,
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + lapdStackMsg.datalen);

    free(lapdStackMsg.dataptr);
    return ITS_SUCCESS;
}

ITS_INT Establish_Link(int fd, int interface, int sapi, int tei)
{
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;

    memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));

    l4cel3msg.primcode     = N_STAT_RQ;
    l4cel3msg.cause[0]     = L2_EST_REQ;
    l4cel3msg.cause[1]     = sapi;
    l4cel3msg.lci_chantype = interface << 8 | DCH_PCHAN;
    l4cel3msg.datalen      = 0;			
    l4cel3msg.lapdTei      = tei;			
    //DUMP_L3_HDR(&l4cel3msg);

    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
    reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
    reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
    reqdataxfer.requestor_pid = getpid();

    return write(
    fd, 
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);
}

ITS_INT Release_Link(int fd, int interface, int sapi, int lapdTei)
{
    struct l4_ce_l3_msg l4cel3msg;
    struct req_data_xfer reqdataxfer;

    memset(&l4cel3msg, 0x00, sizeof(struct l4_ce_l3_msg));
    memset(&reqdataxfer, 0x00, sizeof(struct req_data_xfer));

    l4cel3msg.primcode     = N_STAT_RQ;
    l4cel3msg.cause[0]     = RELEASE_REQ;
    l4cel3msg.cause[1]     = sapi;
    l4cel3msg.lapdTei     = lapdTei;
    l4cel3msg.lci_chantype = interface << 8 | DCH_PCHAN;
    l4cel3msg.datalen      = 0;

    reqdataxfer.l4_ce_ptr     = (struct l4_ce_l3_msg *) &l4cel3msg;
    reqdataxfer.connid        = (unsigned short *) &l4cel3msg.connid;
    reqdataxfer.tsl3_ipb_ptr  = (unsigned char *) l4cel3msg.dataptr;
    reqdataxfer.datalen       = (unsigned short) l4cel3msg.datalen;
    reqdataxfer.requestor_pid = getpid();

    return write(
    fd,
    (const void *) &reqdataxfer,
    sizeof(struct l4_ce_l3_msg) + l4cel3msg.datalen);
}

int start_comm(ITS_OCTET ts1, ITS_OCTET sapi, ITS_OCTET lapdTei, ITS_OCTET appTei)
{
    op_conf_data cfgdata;
    char buf[64], lapdTeiFlg, openFlg;
    int i, done =0;
    //int node = ts1/2;
    int node = ts1;
    cfgdata.tsflag = 1;
    cfgdata.ts = ts1; 
    struct timeval wait;
    if(checkAndUpdateLapdCfgValue( LAPD_GET,   &cfgdata) == 0)
    {
     LAPD_TRACE_CRITICAL(("\nTs entry not found !!"));
     return !ITS_SUCCESS;
    }
    memset(buf, 0, 64);
    sprintf(buf, "%s%d", "/dev/lapd/", node);
    

    LAPD_TRACE_INFO(("\nLAPDIF_Init: cfgdata.opflag: %d ", cfgdata.opflag));
    if(cfgdata.opflag == 0)
    { 
     LAPD_TRACE_INFO(("\nLAPDIF_Init: opening Device File: %s ...", buf));
     if((cfgdata.nfd = open(buf, O_RDWR)) < 0)
     {
      LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                           "Could not open MCC node device: %d ...", node));
      return !ITS_SUCCESS;
     }
     LAPD_TRACE_INFO(("\nLAPDIF_Init: open fd for lapd: %d", cfgdata.nfd)); 
     cfgdata.ifc = 2 * cfgdata.ts;
     LAPD_TRACE_INFO(("\nLAPDIF_Init: cfgdata.ifc: %d", cfgdata.ifc)); 
     FD_SET(cfgdata.nfd, &lapGData.allLapdFd);
     if(MCC_Get_Interface(cfgdata.nfd, &cfgdata.ifc) < 0)
     {
       LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                   "Could not get interface from MCC control device ..."));
        return !ITS_SUCCESS;
     }
     LAPD_TRACE_INFO(("\nLAPDIF_Init: open fd for lapd: %d", cfgdata.nfd)); 
     lapGData.noOfFd++;
     cfgdata.ifcFlag = 1; 
     cfgdata.tsflag = 0;
     if(checkAndUpdateLapdCfgValue( LAPD_MODIFY,   &cfgdata) == 0)
     {
      LAPD_TRACE_CRITICAL(("\ninterface modify failed  !!"));
      return !ITS_SUCCESS;
     }
     LAPD_TRACE_INFO(("\nLAPDIF_Init: MCC_Get_Interface() success .for ifc=%d", cfgdata.ifc));
            
     if(Load_Config_Param(cfgdata.nfd, lapdTei, cfgdata.ifc) < 0)
     {
      LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                         "Could not load cup params in MCC control device ..."));
      return !ITS_SUCCESS;
     }
    /* wait.tv_sec = 0;
     wait.tv_usec =50000;
     select(0,  NULL, NULL, NULL, &wait);

     LAPD_TRACE_INFO(("\nLAPDIF_Init: Load_Config_Param() success for nfd =%d, tei=%d, ifc=%d...",
                          cfgdata.nfd, cfgdata.lapdTei,cfgdata.ifc));*/
     done = 1;  

    } 
            
    if(done == 0)
    {
     if(Load_Config_Param(cfgdata.nfd, lapdTei, cfgdata.ifc) < 0)
     {
       LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
               "Could not load cup params in MCC control device ..."));
       return !ITS_SUCCESS;
     }
/*     wait.tv_sec = 0;
     wait.tv_usec =50000;
     select(0,  NULL, NULL, NULL, &wait);*/
               
    }  
    if(Establish_Link(cfgdata.nfd, cfgdata.ifc, sapi, lapdTei) < 0)
    {
       LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                "Could not establish link for channel: %d ...", cfgdata.ts));
       LAPD_TRACE_CRITICAL(("\nLAPDIF_Init: " \
                "errno: %d ...", errno));
    }
   /* wait.tv_sec = 0;
    wait.tv_usec =50000;
    select(0,  NULL, NULL, NULL, &wait);*/
    LAPD_TRACE_INFO(("\nLAPDIF_Init: Establish_Link() success ..."));

    GLB_FLAG = 1;
    return ITS_SUCCESS;
}
#endif // TMCC




#ifdef MTP2SIM 
#endif // MTP2SIM
