/*******************************************************************************
**      FILE NAME:
**          bssap_task.c
**
**      DESCRIPTION:
**              This files defines the Initialization & Configuration of BSSAP Stack.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#include <time.h>
#include <stdlib.h>
#include <sl.h>
#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <bs_stgl.h>
#include <bssap_port.h>
#include <lbs.h>
#include <lbs.x>
#include <bs.h>
#include <bs.x>

#include "bssap.h"
#define LOGGER_IMR
#ifdef LOGGER_IMR
#include "sysxxx_typedef.h"
#include "sysxxx_hashdefs.h"
#include <sysxxx_msgstruct.h>
#include "ipcfrm_syslog.h"
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif
#ifdef LOGGER_ON_SCREEN
#define LOG_PRINT(a,b,args...) printf(b,##args)
#endif

#define SCCP_USER_MSG_MAX_SIZE 1024
#define  NIB_SERVER

#include <pthread.h>
#include <sys/types.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>


#ifdef SCM_CHG
#include "nwstkscm_hashdefs.h"
#include "nwstkscm_msgdef.h"
#define FAILURE -1
#define SUCCESS 0
#define MAX_MESSAGE_SIZE 1024
int bsScmServerFd = 0;
int bsScmtcplistener = 0;
unsigned char bufScmRecv[MAX_MESSAGE_SIZE];
pthread_t ServerFdThread;
void *open_Server_for_SCM (void);
int  RecvDataFromSCM(void);
extern int BS_SERVER_PORT;
void BuildAndSendSCMResponse(NwStkHdr *head_ptr,int errCode);
int ProcessCmdFromScm(unsigned int opCode,unsigned char *msg_buff,unsigned int size);
int Rel_Main_Mutex = 0;

#endif

static int bssap_user_sock[2];
static const int yes = 1;
unsigned char bssap_user_sock_recv(int fd);

extern int source_point_code,rem_pc,bsc_id,nwk_indicator,bsc_ssn_bssap,bs_intf_id,bs_log_user_id;

extern int cl_rem_pc, start_cic,end_cic;

extern return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
                              src_id_t src_id, dst_id_t dst_id,
                              error_t *p_ecode);

unsigned long int user_ip_address;
extern char *host_ip[32];
extern U8bit bssap_state;
extern U8bit bssap_data_state;
unsigned long stack_destinations[5] ;

void bssap_initialization (void *unused);
void ss7_bssap_task (void *unused);
sl_module_t ss7_bssap_mid;

sl_pool_t ss7_pool;

U8bit sccp_register_buf_arr[]={0xa6,0x01,0x02,0x0a,0x00,0x01,0x00,0x07,0x05,0x0};

return_t ss7_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
                              src_id_t src_id, dst_id_t dst_id,
                              error_t *p_ecode);

return_t send_from_bssap_to_sccp (buffer_t *p_buffer, s7_len_t noctets,
                         src_id_t src_id, dst_id_t dst_id,
                         error_t *p_ecode);


void ss7_bssap_timer_handler (QTIMER tid, void *buf, void *context)
{
    bssap_process_mesg (buf);
}

int ss7_bssap_msg_handler (void *buf, void *context)
{
	int arg = qvPriority(buf);
    if (arg == 0)
	bssap_process_mesg (buf);
    else
	sl_buf_free (buf);
    return 0;
}


void bssap_initialization (void *unused)
{
    int                 i = 0, j = 0;
    BsIntfCb *bsIntfCb = SS7_NULL;   
    U32bit cicCount,bsSMemSz;
    U16bit      api_len;
    src_id_t src_id;
    dst_id_t dst_id;
    error_t ecode;
    int ret = 0;

 
/* Configuration Initialization */
   LOG_PRINT(INFO,"###################GENERAL CONFIGURATION ################### \n");
   bsCb.genCfg.nmbMaxCRef = MAX_CALL_REF; 
   bsCb.genCfg.nmbMaxCir =  MAX_CIRCUIT_CIC; 
   bsCb.genCfg.nmbMaxIntf = BS_MAX_NMB_INTF_ID; 
   bsCb.genCfg.timeRes = 10;
   bsSMemSz =  (U32bit) (bsCb.genCfg.nmbMaxIntf * ((bsCb.genCfg.nmbMaxIntf)* sizeof(BsIntfCb)));
   bsSMemSz += (U32bit) (bsCb.genCfg.nmbMaxIntf * ((bsCb.genCfg.nmbMaxCRef)* sizeof(BsLcfRef)));
   bsSMemSz += (U32bit) (bsCb.genCfg.nmbMaxIntf * ((bsCb.genCfg.nmbMaxCir + 1)* sizeof(BsCirCb)));
   LOG_PRINT(INFO,"GENCONFIG: nmbMaxCRef:[%d] \n",bsCb.genCfg.nmbMaxCRef);
   LOG_PRINT(INFO,"GENCONFIG: nmbMaxCir:[%d] \n",bsCb.genCfg.nmbMaxCir);
   LOG_PRINT(INFO,"GENCONFIG: nmbMaxIntf:[%d] \n",bsCb.genCfg.nmbMaxIntf);
   LOG_PRINT(INFO,"#######TOTAL MEMORY REQUIRED :[%ld] \n",bsSMemSz);
   bsCb.intfLst  = (BsIntfCb *) bssap_malloc (bsCb.genCfg.nmbMaxIntf * (sizeof(BsIntfCb *)));			
   if(bsCb.intfLst == SS7_NULL)
   {
      LOG_PRINT(CRITICAL,"bssap_initialization(): Fail to allocate memory to bsCb.intfLst \n");
      return;
   }
   for (i = 0; i < (U16bit) bsCb.genCfg.nmbMaxIntf; i++)
   {
         *(bsCb.intfLst + i) = SS7_NULL;
         bsCb.nmIntf = 0;
   }
         bsCb.init.cfgDone = SS7_TRUE;
   LOG_PRINT(INFO,"GENCONFIG:GENERAL CONFIG done Successfully \n");
   LOG_PRINT(INFO,"######################################################################## \n");
#ifdef BSSAP_HA
    BsHashInitialize(); 
#endif
#ifdef SCM_CHG
   pthread_create (&ServerFdThread, NULL, open_Server_for_SCM, NULL);
#else
   if(bs_intf_id >= (S16bit) bsCb.genCfg.nmbMaxIntf)
   {
      LOG_PRINT(CRITICAL,"bssap_initialization():Interface Id greater than nmbMaxIntf value[%d]\n",bsCb.genCfg.nmbMaxIntf);
      return;
   }
   bsIntfCb = BSFINDINTF(bs_intf_id);
   if (bsIntfCb != SS7_NULL)
   {
     LOG_PRINT(INFO,"bssap_initialization():Interface Is already Configured");
     return;
   }
  /* Allocate memory for the Interface control block */
    bsIntfCb  = (BsIntfCb *) bssap_malloc (sizeof(BsIntfCb));
    bs_mem_zero((U8bit *)bsIntfCb, sizeof(BsIntfCb));
   
   bsIntfCb->intfId = bs_intf_id;
   bsIntfCb->bscId = bsc_id;
   bsIntfCb->ni = nwk_indicator;
   bsIntfCb->opc = source_point_code;
   bsIntfCb->phyDpc = rem_pc;
   bsIntfCb->swtch = LBS_SW_ITU;       /* user */
   bsIntfCb->t1.enb = SS7_TRUE;
   bsIntfCb->t1.val = 4;
   bsIntfCb->t1.timer_id_key = SS7_FALSE;
   bsIntfCb->t4.enb = SS7_TRUE;
   bsIntfCb->t4.val = 25;
   bsIntfCb->t4.enb = SS7_TRUE;
   bsIntfCb->t4.timer_id_key = SS7_FALSE;
   bsIntfCb->t7.enb = SS7_TRUE;
   bsIntfCb->t7.val = 0;
   bsIntfCb->t7.timer_id_key = SS7_FALSE;
   bsIntfCb->t8.enb = SS7_TRUE;
   bsIntfCb->t8.val = 54;
   bsIntfCb->t8.timer_id_key = SS7_FALSE;
   bsIntfCb->t10.enb = SS7_TRUE;
   //bsIntfCb->t10.val = 5;
   bsIntfCb->t10.val = 20;
   bsIntfCb->t10.timer_id_key = SS7_FALSE;
   bsIntfCb->t11.enb = SS7_TRUE;
   bsIntfCb->t11.val = 10;
   bsIntfCb->t11.timer_id_key = SS7_FALSE;
   bsIntfCb->t13.enb = SS7_TRUE;
   bsIntfCb->t13.val = 5;
   bsIntfCb->t13.timer_id_key = SS7_FALSE;
   bsIntfCb->t17.enb = SS7_TRUE;
   bsIntfCb->t17.val = 5;
   bsIntfCb->t17.timer_id_key = SS7_FALSE;
   bsIntfCb->t18.enb = SS7_TRUE;
   bsIntfCb->t18.val = 5;
   bsIntfCb->t18.timer_id_key = SS7_FALSE;
   bsIntfCb->t19.enb = SS7_TRUE;
   bsIntfCb->t19.val = 10;
   bsIntfCb->t19.timer_id_key = SS7_FALSE;
   bsIntfCb->t20.enb = SS7_TRUE;
   bsIntfCb->t20.val = 10;
   bsIntfCb->t20.timer_id_key = SS7_FALSE;
   bsIntfCb->t25.enb = SS7_TRUE;
   bsIntfCb->t25.val = 10;
   bsIntfCb->t25.timer_id_key = SS7_FALSE;
   bsIntfCb->trbsc.enb = SS7_TRUE;
   bsIntfCb->trbsc.val = 10;
   bsIntfCb->trbsc.timer_id_key = SS7_FALSE;
   bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
   bsIntfCb->rstSndtimerId = BSSAP_INVALID_TMRID;
   bsIntfCb->TrbsctimerId = BSSAP_INVALID_TMRID;
   bsIntfCb->overloadT17 = BSSAP_INVALID_TMRID;
   bsIntfCb->overloadT18 = BSSAP_INVALID_TMRID;
   bsIntfCb->resetRetryCount = 0;
   bsIntfCb->resetIPRetryCount = 0;
  /* Allocate memory for the Interface control block */
    bsIntfCb->lcfRef  = (BsLcfRef *) bssap_malloc ((bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));
    if(bsIntfCb->lcfRef == SS7_NULL)
    {
      LOG_PRINT(CRITICAL,"bssap_initialization(): bssap_malloc failed for lcfRef \n");
      return;
    }
    bs_mem_zero((U8bit *)bsIntfCb->lcfRef, (bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));

  /* Assign control block after switch validation */
   *(bsCb.intfLst + bs_intf_id) = bsIntfCb;
   bsCb.nmIntf++;
      
   LOG_PRINT(INFO,"########################## INTERFACE CONFIGURATION ################### \n");
   LOG_PRINT(INFO,"bscId:%d \n",bsIntfCb->bscId);
   LOG_PRINT(INFO,"intfId:%d \n",bsIntfCb->intfId);
   LOG_PRINT(INFO,"ni:%d \n",bsIntfCb->ni);
   LOG_PRINT(INFO,"OPC:%d \n",bsIntfCb->opc);
   LOG_PRINT(INFO,"DPC:%d \n",bsIntfCb->phyDpc);
   LOG_PRINT(INFO,"variant:%d \n",bsIntfCb->swtch);
   LOG_PRINT(INFO,"Timer:T1[%d]:T4[%d]:T10[%d]:T11[%d]:T13[%d]:T17[%d]:T18[%d]:T25[%d]:Trbsc[%d] \n",bsIntfCb->t1.val,bsIntfCb->t4.val,bsIntfCb->t10.val,bsIntfCb->t11.val,bsIntfCb->t13.val,bsIntfCb->t17.val,bsIntfCb->t18.val,bsIntfCb->t25.val,bsIntfCb->trbsc.val);
   LOG_PRINT(INFO,"Interface Added Successfully");
   LOG_PRINT(INFO,"######################################################################## \n");
#ifdef BSSAP_HA
    BsHashInitHashList(bs_intf_id);
    ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
    if(ret == RFAILED)
    {
      LOG_PRINT(CRITICAL,"SendInterfaceUpdateToPeer Failed \n");
    }
#endif
   bsIntfCb = bsGetIntfPtr(bsc_id,LBS_SW_ITU);
  if(bsIntfCb == SS7_NULL)
  {
     LOG_PRINT(INFO,"Interface Not found for Bsc-Id %d",bsc_id);
     return;
  }
  if (bsCb.genCfg.nmbMaxCir > 0)
  {
      /* get memory for the cic data list  */
      /* Plus 1 for Implementatio specific in case of cic */
/*      bsIntfCb->cicDataList = (BsCirCb * )bssap_malloc (sizeof(bsCb.genCfg.nmbMaxCir + 1) * sizeof(BsCirCb));*/
        bsIntfCb->cicDataList = (BsCirCb * )bssap_malloc ((Size)((Size)(bsCb.genCfg.nmbMaxCir + 1) * sizeof(BsCirCb)));    
      bs_mem_zero((U8bit *)bsIntfCb->cicDataList, (sizeof(bsCb.genCfg.nmbMaxCir + 1) * sizeof(BsCirCb)));  
      for (i = 0; i <= bsCb.genCfg.nmbMaxCir; i++)
      {
            bsIntfCb->cicDataList[i].cic = 0;
            bsIntfCb->cicDataList[i].flaglistSet = SS7_FALSE;
            bsIntfCb->cicDataList[i].blockReqRetryCount = SS7_FALSE;
            bsIntfCb->cicDataList[i].unBlockReqRetryCount = SS7_FALSE;
            bsIntfCb->cicDataList[i].resetCktRetryCount = SS7_FALSE;
            bsIntfCb->cicDataList[i].cktGrpblockReqRetryCount = SS7_FALSE;
            bsIntfCb->cicDataList[i].cktGrpUnblockReqRetryCount = SS7_FALSE;
            bsIntfCb->cicDataList[i].timerId = BSSAP_INVALID_TMRID;
            bsIntfCb->cicDataList[i].msgtype = SS7_FALSE;
            bsIntfCb->cicDataList[i].intfCb = SS7_NULL;
            bsIntfCb->cicDataList[i].databuf = SS7_NULL;
            bsIntfCb->cicDataList[i].datalen = 0;
      }
    } 
          /*  cmInitTimers(bsIntfCb->cicDataList[i].timers, TMR_DEF_MAX);*/
     bsIntfCb->startCic = start_cic;
     bsIntfCb->endCic = end_cic;
     for(cicCount = start_cic; cicCount <= end_cic; cicCount++)
     {
      if(bsIntfCb->cicDataList[cicCount].cic == cicCount)
      {
      	 if(cicCount == 0)
      	{
	   LOG_PRINT(INFO,"bsCfgCirCb: CIC Invalid CIC : cic %ld",cicCount);
      	}
      	else
     	{
	   LOG_PRINT(INFO,"BS: bsCfgCirCb: CIC Already exist: cic %ld  bscId %d \n",cicCount,bsc_id);
     	}
      }
      else
      {
      LOG_PRINT(INFO,"BS: Configure CIC VAL[%d]\n",cicCount);
      bsIntfCb->cicDataList[cicCount].cic = cicCount;
      bsIntfCb->cicDataList[cicCount].flaglistSet = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].blockReqRetryCount = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].unBlockReqRetryCount = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].resetCktRetryCount = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].cktGrpblockReqRetryCount = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].cktGrpUnblockReqRetryCount = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].timerId = BSSAP_INVALID_TMRID;
      bsIntfCb->cicDataList[cicCount].msgtype = SS7_FALSE;
      bsIntfCb->cicDataList[cicCount].databuf = SS7_NULL;
      bsIntfCb->cicDataList[cicCount].datalen = 0;
      bsIntfCb->cicDataList[cicCount].intfCb = bsIntfCb;
    /*  cmInitTimers(bsIntfCb->cicDataList[cicCount].timers, MAXSIMTIMER);*/
     }
  	LOG_PRINT(INFO,"BS: CIC CFG SUCC CFM_OK\n"); 
   }
   /* Register Mesg from BSSAP to SCCP */
#endif

#if 0
   sccp_register_buf_arr[5] = 0x00;
   sccp_register_buf_arr[6] = 0x02;  /* Point Code 256  512 */
#endif   
while(1)
{
 if(Rel_Main_Mutex == 0)
 {
   usleep(100000);
 }
 else
 break;
}
   sccp_register_buf_arr[5] = (U8bit)source_point_code;
   sccp_register_buf_arr[6] = (U8bit)(source_point_code >> 8);  /* Point Code 256  512 */
	 sccp_register_buf_arr[7] = bsc_ssn_bssap;
   sccp_register_buf_arr[8] = bs_log_user_id;
   sccp_register_buf_arr[9] = 0x00;
   
   api_len = 0x0a;  
   src_id = BSSAP_MODULE_ID;
   dst_id = SCCP_MODULE_ID;
/* Send BSSAP Data to SCCP  */
 /*  send_from_bssap_to_sccp(sccp_register_buf_arr,api_len,src_id,dst_id,&ecode);*/
  bssap_state = STACK_INITIALIZED;
  bssap_data_state = STACK_INITIALIZED;
   send_from_bssap_to_sccp(sccp_register_buf_arr,api_len,src_id,dst_id,&ecode);
   LOG_PRINT(INFO,"Register Message Sent from BSSAP to SCCP \n"); 

}

void ss7_bssap_init (void)
{
   ss7_bssap_mid = sl_module_register ("BSSAP", bssap_initialization,
				       ss7_bssap_msg_handler,
				       ss7_bssap_timer_handler, 0);

}
return_t send_from_bssap_to_user (buffer_t *p_buffer, s7_len_t noctets,
			 src_id_t src_id, dst_id_t dst_id,
			 error_t *p_ecode)
{
    return ss7_dispatch_buffer (p_buffer, noctets, src_id, dst_id,
				p_ecode); 
}

return_t send_from_bssap_to_sccp (buffer_t *p_buffer, s7_len_t noctets,
			 src_id_t src_id, dst_id_t dst_id,
			 error_t *p_ecode)
{
     return ss7_dispatch_buffer (p_buffer, noctets, src_id, dst_id,
				p_ecode);

/* Added by Amaresh start as on dated 22-01-16 for memory leak */
     if(p_buffer)
    {
        bssap_free (p_buffer);
        LOG_PRINT(INFO,"BSSAP::INIT:Free Memory send from bssap \n");
    }
/* Added by Amaresh stop as on dated 22-01-16 for memory leak */


 
}

return_t sccp_dispatch_buffer (buffer_t *p_buffer, s7_len_t noctets,
			       src_id_t src_id, dst_id_t dst_id,
			       error_t *p_ecode)
{
    return ss7_dispatch_buffer (p_buffer, noctets, src_id, dst_id,
				p_ecode);
}

#ifdef SCM_CHG
void *open_Server_for_SCM (void)
{
    
  fd_set master;
  fd_set read_fds;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  int newfd;
  int yes = 1;
  socklen_t addrlen;
  int ret = 0;
			  
  /* clear the master and temp sets */
  FD_ZERO (&master);
  FD_ZERO (&read_fds);
  /* get the listener */

   
  LOG_PRINT(INFO,"ALERT ::::: THREAD for open_Server_for_SCM INVOKE \n");
  if ((bsScmtcplistener = socket (AF_INET, SOCK_STREAM, 0)) == -1)
  {
    LOG_PRINT(CRITICAL,"open_Server_for_SCM:socket() failed ");
    LOG_PRINT(CRITICAL,"open_Server_for_SCM Thread EXIT \n");
    exit (1);
  }
    
  /*"address already in use" error message */
  if (setsockopt (bsScmtcplistener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
  {
    LOG_PRINT(CRITICAL,"open_Server_for_SCM:setsockopt() failed \n");
    LOG_PRINT(CRITICAL,"open_Server_for_SCM Thread EXIT \n");
    exit (1);
  }
#if 0    
  /*"address already in use" error message */
  if (setsockopt (bsScmtcplistener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
  {
    LOG_PRINT(CRITICAL,"open_Server_for_SCM:setsockopt() failed \n");
    LOG_PRINT(CRITICAL,"open_Server_for_SCM Thread EXIT \n");
    exit (1);
  }
#endif  
  /* bind */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons (BS_SERVER_PORT);
  memset (&(serveraddr.sin_zero), '\0', 8);
  if (bind (bsScmtcplistener, (struct sockaddr *) &serveraddr, sizeof (serveraddr)) ==
            -1)
  {
    LOG_PRINT(CRITICAL,"open_Server_for_SCM:bind() failed \n");
    LOG_PRINT(CRITICAL,"open_Server_for_SCM Thread EXIT \n");
    exit (1);
  }
    
  SocketOption (bsScmtcplistener);
  SetKeepAliveOption(bsScmtcplistener);
  
  /* listen */
  if (listen (bsScmtcplistener, 10) == -1)
  {
    LOG_PRINT(CRITICAL,"open_Server_for_SCM:Server-listen() failed \n ");
  }
  
  while (1)
  {
    if(bsScmtcplistener == 0)
    {
      LOG_PRINT_CRITICAL ("open_Server_for_SCM thread:Exit\n");
      break;
    }
   /* accept */	
    LOG_PRINT(INFO,"\nopen_Server_for_SCM:Waiting on ServerFd[%d] for accept \n",bsScmtcplistener);
    if ((newfd = accept (bsScmtcplistener, (struct sockaddr *) &clientaddr,&addrlen)) == -1)
    {
      LOG_PRINT(CRITICAL,"open_Server_for_SCM:Server-accept() failed \n");
    }
    else
    {
				                      
      if(newfd == 0)
      {
	LOG_PRINT(CRITICAL,"open_Server_for_SCM:ALERT :::::: ZERO TCP FD %d \n", newfd);
	close(newfd);
	continue;
      }
	
      bsScmServerFd = newfd;

      LOG_PRINT_CRITICAL ("SocketUP :open_Server_for_SCM: SERVER ACCEPT SUCCESS NewFd[%d] for SCM \n", bsScmServerFd);
      while(1)
      {
	ret = RecvDataFromSCM();
	if(ret < 0)
	{
	  LOG_PRINT_CRITICAL ("open_Server_for_SCM : RecvDataFromSCM failed , waiting for accept again \n");
	  break;
	}
	
      }
    }
    sleep(1);
  }
  return 0;
}
int  RecvDataFromSCM(void)
{
  int nbytes = 0;
  unsigned int len = 0, i = 0, remain = 0,hdrlen = 0;
  int ret_3 = 0;
  struct sockaddr_in cliaddr;
  NwStkHdr head_ptr;
  unsigned char opCode = 0;
  int errCode = 0;
  int ret = ROK;
  

  LOG_PRINT(INFO,"ALERT ::::  RecvDataFromSCM()  FUNCTION INVOKE \n");
  
  while (1)
  {
    memset (bufScmRecv, 0, MAX_MESSAGE_SIZE);
    len = 5;
    
    for (i = 0, remain = len; remain > 0; i += nbytes, remain -= nbytes)
    {

      if ((nbytes = recv (bsScmServerFd, &bufScmRecv[i], remain, 0)) <= 0)
      {
	LOG_PRINT(CRITICAL,"RecvDataFromSCM:Recv header fail ERRNO[%d] nbytes[%d] \n", errno,nbytes);
        return FAILURE;
      }
    }
    memset (&head_ptr, 0, sizeof(NwStkHdr));
    head_ptr.appid = bufScmRecv[0];
    head_ptr.opcode = bufScmRecv[1];
    head_ptr.trid = bufScmRecv[2];
    head_ptr.len  |= bufScmRecv[3];
    head_ptr.len  |= bufScmRecv[4] << 8;
#if 0  
    LOG_PRINT(INFO,"-------------------------------------\n");
    LOG_PRINT(INFO," HDR RECV From SCM: \n");
    LOG_PRINT(INFO," head_ptr.appid = %d \n",head_ptr.appid);
    LOG_PRINT(INFO," head_ptr.opcode = %d \n",head_ptr.opcode);
    LOG_PRINT(INFO," head_ptr.trid = %d \n",head_ptr.trid);
    LOG_PRINT(INFO," head_ptr.len = %d  \n",head_ptr.len);
    LOG_PRINT(INFO,"-------------------------------------\n");
#endif
    len = head_ptr.len - 5;
    //LOG_PRINT(INFO," Data len = %d  \n",len);
        
    for (i = 5, remain = len; remain > 0; i += nbytes, remain -= nbytes)
    {
      if ((nbytes = recv (bsScmServerFd, &bufScmRecv[i], remain, 0)) <= 0)
      {
	LOG_PRINT(CRITICAL,"RecvDataFromSCM:Data:ERRNO[%d] \n", errno);
      }
    }
    opCode = (NwStkHdr *)head_ptr.opcode;
      
    LOG_PRINT(INFO,"############################################################# \n");
    errCode = ProcessCmdFromScm(opCode,bufScmRecv,len);
     Rel_Main_Mutex = 1;
    BuildAndSendSCMResponse(&head_ptr,errCode);
    LOG_PRINT(INFO,"############################################################# \n");
  }
  return FAILURE;
}
int ProcessCmdFromScm(unsigned int opCode,unsigned char *msg_buff,unsigned int size)
{
  unsigned char rspOpCode = 0;
  int ret = SS7_FAILURE;
  ScmBsInterfaceConfig cfgIntfPtr;
  switch(opCode)
  {
    case SCM_BSSAP_INTF_ADD:
      LOG_PRINT(INFO,"CMD RECV From SCM: BSSAP INTERFACE ADD \n");
      memset(&cfgIntfPtr,0,sizeof(ScmBsInterfaceConfig));
      memcpy(&cfgIntfPtr,(ScmBsInterfaceConfig *)msg_buff,sizeof(ScmBsInterfaceConfig));
      LOG_PRINT(INFO,"-------------------------------------------------------- \n");
      LOG_PRINT(INFO,"Parameters:\n");
      LOG_PRINT(INFO,"bscId:%d \n",cfgIntfPtr.bscId);
      LOG_PRINT(INFO,"intfType:%d \n",cfgIntfPtr.interfaceType);
      LOG_PRINT(INFO,"ni:%d \n",cfgIntfPtr.ni);
      LOG_PRINT(INFO,"name:%s \n",cfgIntfPtr.name);
      LOG_PRINT(INFO,"OPC:%d \n",cfgIntfPtr.opc);
      LOG_PRINT(INFO,"DPC:%d \n",cfgIntfPtr.dpc);
      LOG_PRINT(INFO,"variant:%d \n",cfgIntfPtr.variant);
      LOG_PRINT(INFO,"Timer:T1[%d]:T4[%d]:T10[%d]:T11[%d]:T13[%d]:T17[%d]:T18[%d]:T25[%d]:Trbsc[%d] \n",cfgIntfPtr.timer_T1,cfgIntfPtr.timer_T4,cfgIntfPtr.timer_T10,cfgIntfPtr.timer_T11,cfgIntfPtr.timer_T13,cfgIntfPtr.timer_T17,cfgIntfPtr.timer_T18,cfgIntfPtr.timer_T25,cfgIntfPtr.timer_Trbsc);
      LOG_PRINT(INFO,"-------------------------------------------------------- \n");
      ret = bsCfgIntfCb(&cfgIntfPtr);
      break;
    
    case SCM_BSSAP_INTF_DEL:
      LOG_PRINT(INFO,"CMD RECV From SCM: BSSAP INTERFACE DELETE \n");
      memset(&cfgIntfPtr,0,sizeof(ScmBsInterfaceConfig));
      memcpy(&cfgIntfPtr,(ScmBsInterfaceConfig *)msg_buff,sizeof(ScmBsInterfaceConfig));
      ret = bsDelIntfCb(&cfgIntfPtr);
      break;
    
    default:
     LOG_PRINT(CRITICAL,"\nProcessCmdFromScm: default case reached \n");
     ret = NWSTK_WRONG_PARAM;
    break;
  }

  return ret;
}
void BuildAndSendSCMResponse(NwStkHdr *head_ptr,int errCode)
{
  int ret = SS7_FAILURE,len = 0;
  unsigned char rspBuf[MAX_MESSAGE_SIZE];
  NwStkConfigResp scmRsp;

  memset(rspBuf,0,MAX_MESSAGE_SIZE);
  
  /*appId*/
  rspBuf[0] = head_ptr->appid;
  
  /*opCode*/
  if(head_ptr->opcode == SCM_BSSAP_INTF_ADD)
  {
    LOG_PRINT(INFO,"BuildAndSendSCMResponse : Sending BSSAP_SCM_INTF_ADD_RESP \n");
    rspBuf[1] = BSSAP_SCM_INTF_ADD_RESP;
  }
  else if(head_ptr->opcode == SCM_BSSAP_INTF_DEL)
  {
    LOG_PRINT(INFO,"BuildAndSendSCMResponse : Sending BSSAP_SCM_INTF_DEL_RESP \n");
    rspBuf[1] = BSSAP_SCM_INTF_DEL_RESP;
  }
 
  /*triId*/
  rspBuf[2] = head_ptr->trid;
  
  /*len*/
  len = 5 + sizeof(I_S16);
  rspBuf[3] = len  & 0x000000FF;
  rspBuf[4] = (len & 0x0000FF00) >> 8;

  /*errCode */
  rspBuf[5] = errCode  & 0x000000FF;
  rspBuf[6] = (errCode & 0x0000FF00) >> 8;

  ret = send(bsScmServerFd,rspBuf,len,0);
  if(ret <= 0)
  {
   LOG_PRINT(CRITICAL,"BuildAndSendSCMResponse: Send rsp failed to SCM:ret[%d] ,bsScmServerFd[%d] \n",ret,bsScmServerFd);
  }
    
  LOG_PRINT(INFO,"BuildAndSendSCMResponse : Send RESPONSE To SCM SUCCESS:nbytes[%d] \n",ret);
  return;
}
#endif
#ifdef BSSAP_HA
void SocketOption (int fd)
{
    
  unsigned int on;
  socklen_t onlen;
  int ret ;
  struct linger linger;
  linger.l_onoff = 1;
  linger.l_linger = 0;

  on=1024 *200;
  onlen = sizeof (on);
  ret = setsockopt (fd, SOL_SOCKET, SO_SNDBUF, (void *) &on, onlen);
  if (ret < 0)
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:setsockopt SO_SNDBUF error %d\n",ret);
  }
		
  ret = setsockopt (fd, SOL_SOCKET, SO_RCVBUF, (void *) &on, onlen);
  if (ret < 0)
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:setsockopt SO_SNDBUF error %d\n",ret);
  }
          
  if(setsockopt(fd, SOL_SOCKET, SO_LINGER, (I_Void *)&linger,
		             sizeof(linger)) < 0)
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:setsockopt: SO_LINGER System call Failed (errno = %d)",errno);
  }
	        
  LOG_PRINT(CRITICAL,"BSSAP_HA:setsockopt: SO_LINGER set successfully for Fd[%d]",fd);
  return;
}

void SetKeepAliveOption(int fd)
{

  socklen_t optlen;
  int optval = 0;
	  
  /* Set the option active */
  optval = 1;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) 
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:SetKeepAliveOption:setsockopt() SO_KEEPALIVE failed : CLOSING FD[%d] \n",fd);
    close(fd);
  }
	        
  optval = 2;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &optval, optlen) < 0) 
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:SetKeepAliveOption:setsockopt() TCP_KEEPCNT failed : CLOSING FD[%d] \n",fd);
    close(fd);
  }
		    
  optval = 5;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &optval, optlen) < 0) 
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:SetKeepAliveOption:setsockopt() TCP_KEEPIDLE failed : CLOSING FD[%d] \n",fd);
    close(fd);
  }
  
  optval = 2;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &optval, optlen) < 0) 
  {
    LOG_PRINT(CRITICAL,"BSSAP_HA:SetKeepAliveOption:setsockopt() TCP_KEEPINTVL failed : CLOSING FD[%d] \n",fd);
    close(fd);
  }
  return;
}
#endif

