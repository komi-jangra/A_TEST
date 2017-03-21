#include <stdio.h>
#include <stdlib.h>
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
#include <signal.h>
#include <arpa/inet.h>
#include <linux/kernel.h>
#include <string.h>             //strsignal
#include <execinfo.h>           //backtrace,backtrace_symbols
#include <ucontext.h>           //ucontext_t
#include <errno.h>

#include "bs.h"
#include "bs.x"

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

struct token
{
  unsigned int MsgId;
  unsigned int Table_Id;
  unsigned int Master_Flg;
  unsigned int Slave_Flg;
  unsigned int counter;
  unsigned int ack;
};
typedef struct token token;

pthread_t TcpClientThread;
pthread_t TcpServerThread;
pthread_t TcpSyncPeer;
pthread_t RunBothActMode;
  
pthread_mutex_t FlagLock;
pthread_mutex_t SyncLock;
unsigned char condition_flag = 0;
int syncFlag = 1;
int TcpClient = 0;
int TcpServer = 0;
int tcp_listener;
int tcptoken_listener;
extern char TCPPEER_IP[25];
extern int TCP_PORT;
extern int MASTER;
unsigned char *bufTCPRecv = NULL;
unsigned char  *bufPeerUpd = NULL;
int CLIENT_RETRY_FLAG = 0;   /* Used to introduce client connect delay */
int Bpm_HASTATE = 0; 
int SelfHASTATE = 0; 
unsigned char SYNC_PEER = FALSE;
long long SyncStartMsec = 0;
long long SyncEndMsec = 0;
extern int source_point_code,rem_pc;

/*ProtoTypes */
void *Tcp_ClientFunc (void *args);
void *TCP_ServerFunc (void *args);
void *Tcp_SyncPeerFunc (void *args);
int  TCPRECV_Server(void);
void SendTokenResp (token * tok_ptr);
void Read_EnvVar(void);
void SendSyncLockToken(void);
void SendSyncUnLockToken(void);
void Peer_Leave(void);
int BsHashCreateMutex (pthread_mutex_t * m);
int BsHashAcquireMutex (pthread_mutex_t * m,int mutexType);
int BsHashReleaseMutex (pthread_mutex_t * m,int mutexType);
void BsHashDeleteMutex(pthread_mutex_t  *m);
int InsertEntryTcp(int intfId,unsigned int tableId,unsigned char* key,unsigned int keylen,void *dataptr,int datalen);
int DeleteEntryTcp(int intfId,unsigned int tableId,unsigned char* key,unsigned int keylen);
int UpdateEntryTcp(int intfId,unsigned int tableId,unsigned char* key,unsigned int keylen,void *dataptr);
void FillHashTableTillMaxVal(unsigned int tableId,int intfId);
long long current_timestamp(void);
void SendPeerUpdateForHashTables(CmHashListCp *hashListCp,int intfId,unsigned int tableId,unsigned char *key,unsigned int keylen);
void PackCallDbUpdData(unsigned int tableId,unsigned char *bufptr,unsigned char *dataptr);
BsCallCb* RecvCalldbUpdData(unsigned char opCode,BsUpdCallDb *calldb);
void ProcessIntfAddUpdFrmPeer(BsUpdIntfDb *intfCb);
void ProcessIntfDelUpdFrmPeer(int intfId);
void print_UPDMsg(UPDMsg *updMsgBuf);
/*****************************************CODE START*******************************************************/
void BsHashInvoke(int haState)
{

  SelfHASTATE = haState;
  LOG_PRINT(INFO,"BSSAP_HA: BsHashInvoke :SelfHASTATE[%s]\n",PRINT_CARDSTATE(SelfHASTATE)); 
  return;
}

void Read_EnvVar()
{
  char *path;
  char *tmp = NULL;


  path = getenv ((const char *) "CONFIG");
  if (path == NULL)
  {
     LOG_PRINT(INFO,"BSSAP_HA:XXXXXXXXXCRASH CONFIG ENV VAR NULLXXXXXXXXX\n");
     abort ();
  }
  LOG_PRINT(INFO,"BSSAP_HA:XXXXXXXXXSUCCESSFULLY GET CONFIG ENV VAR[%s]XXXXXXXXX\n",path);

  tmp = (char *) getenv ((const char *) "TCP_PORT");
  TCP_PORT = atoi (tmp);
  LOG_PRINT(INFO,"BSSAP_HA:TCP_PORT=%d\n", TCP_PORT);

  tmp = (char *) getenv ((const char *) "config_PEER_PP_IP");
  strcpy (TCPPEER_IP, tmp);
  LOG_PRINT(INFO,"BSSAP_HA:TCPPEER_IP=%s\n", TCPPEER_IP);
        
  tmp = (char *) getenv ((const char *) "MASTER");
  MASTER = atoi (tmp);
  LOG_PRINT(INFO,"BSSAP_HA:MASTER=%d\n", MASTER);
  
}

void BsHashInitialize(void)
{
 int ret = RFAILED;
 int i;
    
  LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize():Function Enter\n");

  ret = BsHashCreateMutex(&FlagLock);
  if (ret == 1)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize():THREAD_MUTEX CREATE Success\n");
#endif
  }

  ret = BsHashCreateMutex(&SyncLock);
  if (ret == 1)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize():SYNC_MUTEX CREATE Success\n");
#endif
  }
 

/*Allocating memory to global buffers*/
   bufTCPRecv = (unsigned char*) calloc(1,MAX_MESSAGE_SIZE * sizeof(unsigned char));
   if(bufTCPRecv == NULL)
   {
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufTCPRecv:ABORTING \n");
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufTCPRecv:ABORTING \n");
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufTCPRecv:ABORTING \n");
      abort ();
   }
      
/*Allocating memory to global buffers*/
   bufPeerUpd = (unsigned char*) calloc(1,MAX_MESSAGE_SIZE * sizeof(unsigned char));
   if(bufPeerUpd == NULL)
   {
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufPeerUpd:ABORTING \n");
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufPeerUpd:ABORTING \n");
      LOG_PRINT(INFO,"BSSAP_HA:BsHashInitialize() : unable  to allocate memory to bufPeerUpd:ABORTING \n");
      abort ();
   }
  LOG_PRINT(INFO,"BSSAP_HA:TCP_PORT=%d\n", TCP_PORT);
  LOG_PRINT(INFO,"BSSAP_HA:TCPPEER_IP=%s\n", TCPPEER_IP);
  LOG_PRINT(INFO,"BSSAP_HA:MASTER=%d\n", MASTER);
  LOG_PRINT(INFO,"BSSAP_HA:-------------------------------------------------------------\n");
  
  pthread_create (&TcpClientThread, NULL, Tcp_ClientFunc, NULL);
  pthread_create (&TcpServerThread, NULL, TCP_ServerFunc, NULL);
 
  return;
}


void *Tcp_ClientFunc (void *args)
{
  int sockfd = 0;
  int ret = 0;
  int yes = 1;
  struct sockaddr_in their_addr;
  struct timespec req;
  int TcpClientConnectOk = 0;
  LOG_PRINT(INFO,"BSSAP_HA:------ TCP CLIENT THREAD INVOKE-------------- \n");
  while (1)
  {
     if(TcpClient == 0)
     {
        if(CLIENT_RETRY_FLAG == 1)
        {
	  LOG_PRINT(INFO,"BSSAP_HA:TCP_Client: Sleeping for 30sec before connecting .......\n");
          sleep(1);
          CLIENT_RETRY_FLAG = 0;
        }

	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	{
	  LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:socket() failed \n");
	  exit (1);
	}
	else
	{
	  LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:SOCKET OPEN for TCP_CLIENT Fd[%d] \n",sockfd);
	}
	  /*"address already in use" error message */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
	{
	  LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:-setsockopt() error lol! \n");
	}
	SocketOption (sockfd);
        SetKeepAliveOption(sockfd);
        TcpClient = sockfd;
        TcpClientConnectOk = 0;
      }
      if (TcpClientConnectOk == 0)
      {
	  their_addr.sin_family = AF_INET;
	  their_addr.sin_port = htons (TCP_PORT);
	  their_addr.sin_addr.s_addr = inet_addr (TCPPEER_IP);
	  memset (&(their_addr.sin_zero), '\0', 8);
	  LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:Trying for connect() Again  \n");
	  if ((ret =  connect (sockfd, (struct sockaddr *) &their_addr,sizeof (struct sockaddr))) == -1)
	  {
	     LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:connect() failed errno[%d] \n",errno);
	     //sleep(1);
	  }
	  else
	  { 
	     TcpClientConnectOk = 1;
             LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:SocketUP :: TCP CLIENT CONNECT SUCCESS NewFd[%d] SelfHASTATE[%d]\n",TcpClient,SelfHASTATE);
	     if(SelfHASTATE == HA_CARDSTATE_ACTIVE)
	     {
               pthread_create (&TcpSyncPeer, NULL, Tcp_SyncPeerFunc, NULL);
	     }
	     else
	     {
	       /*Note sleep added so that master send lock request first after syncing */
	       /* if we want slave should send lock first then remove this sleep */
                sleep(1);
	     }
	  }
      }
      if(TcpClient == 0)
      {
        /* sleeping for 200 milliseconds */      
	req.tv_sec=0;
	req.tv_nsec=200000000;
	pselect(FD_SETSIZE,0,0,0,&req,NULL);
      }
      else
      {
	sleep(1);
      }
    }
    LOG_PRINT(INFO,"BSSAP_HA:Tcp_ClientFunc:ALERT ::::: TCP CLIENT EXITING \n");
  return 0;
}
void *Tcp_SyncPeerFunc (void *args)
{
  BsIntfCb *bsIntfCb = NULL;
  int j,i,ret = RFAILED;
  U32 callref =0,callId = 0;
  BsCallCb *call = SS7_NULL;

  LOG_PRINT(INFO,"BSSAP_HA:--------- Tcp_SyncPeerFunc THREAD INVOKE---------------\n");
 while(1)
 {
   LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: TcpClient[%d] TcpServer[%d]..... \n",TcpClient,TcpServer);
   if ((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
   {
     LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: SelfHASTATE[%s] SYNC_PEER[%d]..... \n",PRINT_CARDSTATE(SelfHASTATE),SYNC_PEER);
     if((SelfHASTATE == HA_CARDSTATE_ACTIVE) && (SYNC_PEER ==  FALSE))
     {
       LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: BOTH FD Connected:TcpClient[%d] : TcpServer[%d]  \n",TcpClient,TcpServer);
       LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: Sending PEER Update From ACTIVE Node for Syncing \n");
       
       LOG_PRINT(INFO,"##############################################################\n");
       LOG_PRINT(INFO,"BSSAP_HA:SENDING SYNC LOCK:\n");
       LOG_PRINT(INFO,"##############################################################\n");
       SendSyncLockToken();
      
       for (j = 1;j < bsCb.genCfg.nmbMaxIntf; j++)
       { 
	 bsIntfCb = BSFINDINTF(j);
         if(bsIntfCb)
         {
	   ret = SendInterfaceAddUpdateToPeer(bsIntfCb);
	   if(ret == ROK)
	   {
	     for(i = 1;i<= bsCb.genCfg.nmbMaxCRef;i++)
	     {
	       callref = i;
	       SendPeerUpdateForHashTables(bsIntfCb->callRefList,j,BSHASH_TABLE_CALLREF_CTXT,(unsigned char *)&callref,sizeof(U32));
	       call = bsFindCall(bsIntfCb,callref);
	       if(call != SS7_NULL)
	       {	
		 callId = call->callId;
	         if(callId)
		 {  
                   //LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: Sending CALLID hashlist Update for Callref[%d] CallId[%d]: \n",callref,callId);
		   SendPeerUpdateForHashTables(bsIntfCb->callIdList,j,BSHASH_TABLE_CALLID_CTXT,(unsigned char *)&callId,sizeof(U32));
		 }
	       }
	     }
	   }
         }
       }
      
       SYNC_PEER = TRUE;
       LOG_PRINT(INFO,"##############################################################\n");
       LOG_PRINT(INFO,"BSSAP_HA:SENDING SYNC UNLOCK:\n");
       LOG_PRINT(INFO,"##############################################################\n");
       SendSyncUnLockToken();
    }
   }
   if(SYNC_PEER == TRUE)
   {
     LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: SYNC_PEER is Now TRUE,hence exiting Tcp_SyncPeerFunc() \n");
     pthread_exit (NULL);
   }
     LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc: Thread still working:...SYNC_PEER[%d]..... \n",SYNC_PEER);
   sleep(1);
 }
  
 LOG_PRINT(INFO,"BSSAP_HA:Tcp_SyncPeerFunc:EXITING  After SYNCING PEER.... \n");
 return 0;
}
void *TCP_ServerFunc (void *args)
{
  fd_set master;
  fd_set read_fds;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
  int newfd;
  int yes = 1;
  socklen_t addrlen;
  int ret = 0;

  LOG_PRINT(INFO,"BSSAP_HA:--------- TCP SERVER THREAD INVOKE---------------\n");

  /* clear the master and temp sets */
  FD_ZERO (&master);
  FD_ZERO (&read_fds);

  /* get the listener */
  if ((tcp_listener = socket (AF_INET, SOCK_STREAM, 0)) == -1)
  {
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:socket() failed ");
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc Thread EXIT \n");
     exit (1);
  }
  /*"address already in use" error message */
  if (setsockopt (tcp_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) ==
      -1)
  {
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:setsockopt() failed \n");
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc Thread EXIT \n");
     exit (1);
  }
  /* bind */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons (TCP_PORT);
  memset (&(serveraddr.sin_zero), '\0', 8);
  if (bind (tcp_listener, (struct sockaddr *) &serveraddr, sizeof (serveraddr)) ==
      -1)
  {
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:bind() failed \n");
     LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc Thread EXIT \n");
     exit (1);
  }
  SocketOption (tcp_listener);
  SetKeepAliveOption(tcp_listener);
  /* listen */
  if (listen (tcp_listener, 10) == -1)
  {
      LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:Server-listen() failed \n ");
  }
  /* add the listener to the master set */
  while (1)
  {
     if(tcp_listener == 0)
     {
       LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc thread:Exit\n");
       break;
     }      
              
      LOG_PRINT(INFO,"\nBSSAP_HA:TCP_ServerFunc : WAITING for TCP SERVER ACCEPT again \n");
      if ((newfd = accept (tcp_listener, (struct sockaddr *) &clientaddr,&addrlen)) == -1)
      {
	LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:Server-accept() failed \n");
      }
      else
      {
	if(newfd == 0)
	{
	  LOG_PRINT(INFO,"BSSAP_HA:ALERT :::::: ZERO TCP FD %d \n", TcpServer);
	  close(newfd);
          continue;
	}
	TcpServer = newfd;
	LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:SocketUP :: TCP SERVER ACCEPT SUCCESS NewFd[%d] \n", TcpServer);
	while(1)
        {
	   ret = TCPRECV_Server();
	   if(ret < 0)
	   {
              LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc : TCPRECV_Server failed  \n");
              break;
	    }
	}


        }
        sleep(1);
  }

  LOG_PRINT(INFO,"BSSAP_HA:TCP_ServerFunc:ALERT ::::: TCP SERVER EXITING \n");
  return 0;
}

int TCPRECV_Server (void)
{
  char mesg[100];
  token *tokenptr = NULL;
  unsigned int tokenlen = 0 ;
  int nbytes = 0 , count = 0,ret = 0, intfId = 0;
  unsigned int len = 0,totalLen = 0, i = 0, remain = 0 , tableId = 0;
  unsigned char opCode = 0;
  unsigned char* key = 0;
  unsigned int keylen = 0 ,datalen = 0;
  U8 msgType = 0;
  UPDMsg *intfUpdPtr = NULL;

  LOG_PRINT(INFO,"BSSAP_HA:--------------TCP RECV FUNCTION INVOKE--------------- \n");

  while (1)
  {
     LOG_PRINT(INFO,"BSSAP_HA:--------- TCP:GOING TO RECV PACKET from PEER ------------- \n");
      memset (bufTCPRecv, 0, MAX_MESSAGE_SIZE);
      len = 7;
      for (i = 0, remain = len; remain > 0; i += nbytes, remain -= nbytes)
      {

	  if ((nbytes = recv (TcpServer, &bufTCPRecv[i], remain, 0)) <= 0)
	    {
	      LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: header recv() failed  nbytes[%d]\n", nbytes);
	      CLIENT_RETRY_FLAG = 1;
	      Peer_Leave();
              return FAILURE;
	    }
	}
       LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: header recv success nbytes[%d]\n", nbytes);
       if((bufTCPRecv[0] == SYNC_LOCK) || (bufTCPRecv[0] == SYNC_UNLOCK)) 
       {
	   
	 LOG_PRINT(INFO,"BSSAP_HA:\n***********************TOKEN START***************************************** \n");
	 if((bufTCPRecv[0] == SYNC_LOCK) || (bufTCPRecv[0] == SYNC_UNLOCK))
	 {
	   LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: TOKEN MSG RECV [%s]  \n",PRINT_TOKEN(bufTCPRecv[0]));
	   if(bufTCPRecv[0] == SYNC_LOCK)
	   {
	     BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
	     syncFlag = 2;
	     LOG_PRINT(INFO,"BSSAP_HA:Setting syncFlag = [%d] on recv of SYNC_LOCK \n",syncFlag);
             SyncStartMsec = current_timestamp();
	     LOG_PRINT(INFO,"BSSAP_HA:TCP:SyncStartMsec[%lld] \n",SyncStartMsec);
	   }
	   if(bufTCPRecv[0] == SYNC_UNLOCK)
	   {
	     syncFlag = 0;
	     LOG_PRINT(INFO,"BSSAP_HA:Setting syncFlag = [%d] on recv of SYNC_UNLOCK \n",syncFlag);
             SyncEndMsec = current_timestamp();
	     LOG_PRINT(INFO,"BSSAP_HA:TCP:SyncEndMsec[%lld] \n",SyncEndMsec);
	     LOG_PRINT(INFO,"BSSAP_HA:TCP: TOTAL SYNC TIME in msec[%lld] \n",(SyncEndMsec - SyncStartMsec));
	     BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
	   }
	 }
	 LOG_PRINT(INFO,"BSSAP_HA:\n***************************************************************************** \n");
       }
       else
       {
	 LOG_PRINT(INFO,"BSSAP_HA:###################TCP DATA BUFFER START ####################### \n");
	  /* len of data*/
	 len = 0;
	 len  |= bufTCPRecv[3];
	 len  |= bufTCPRecv[4] << 8;
	 len  |= bufTCPRecv[5] << 16;
	 len  |= bufTCPRecv[6] << 24;

//	 LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: len[%d] of DATA to RECV\n",len);
	 for (i = 7, remain = len; remain > 0; i += nbytes, remain -= nbytes)
	 {
	   if ((nbytes = recv (TcpServer, &bufTCPRecv[i], remain, 0)) <= 0)
	   {
	     LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: Data recv() failed  nbytes[%d]\n", nbytes);
	     CLIENT_RETRY_FLAG = 1;
	     Peer_Leave();
	     return FAILURE;
	   }
	 }
	 count = 0;
#ifdef DEBUG_ALL
	 LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: DATA RECV success LEN[%d]\n", nbytes);
#endif
	 if (nbytes > 0)
	 {
	   totalLen = 7 + len;
	   //print_buf((unsigned char *)bufTCPRecv,totalLen);
	 }
	 if ((TcpClient > 0) && (TcpServer > 0) && (nbytes > 0))
	 { 
	   opCode = bufTCPRecv[0];	
	   intfId = bufTCPRecv[1];
	   tableId = bufTCPRecv[2];
	   if(tableId == BSHASH_TABLE_INTF)
	   {
	     switch(opCode)
	     {
	       case INSERT:
		 intfUpdPtr = malloc(sizeof(UPDMsg));
		 if(intfUpdPtr)
		 {
		   intfUpdPtr->msgType = bufTCPRecv[7];
		   memcpy(&intfUpdPtr->u.intfdb,&bufTCPRecv[8],sizeof(BsUpdIntfDb));
                   //print_UPDMsg(intfUpdPtr); 
		   ProcessIntfAddUpdFrmPeer(&intfUpdPtr->u.intfdb);
	           LOG_PRINT(CRITICAL,"BSSAP_HA:TMP:Freeing memory for intfUpdPtr[%p]  \n",intfUpdPtr);
		   free(intfUpdPtr);
		   intfUpdPtr = NULL;
		 }
		 break;
	       case DELETE:
		 ProcessIntfDelUpdFrmPeer(intfId);
		 break;
	       default:
		 break;
	     }
	   }
	   else
	   {
	     count = 7;
	     while(count < totalLen)
	     {
	       keylen = 0;
	       datalen = 0;
	       keylen  |= bufTCPRecv[count++];
	       keylen  |= bufTCPRecv[count++] << 8;
	       keylen  |= bufTCPRecv[count++] << 16;
	       keylen  |= bufTCPRecv[count++] << 24;
	     
	       key = calloc(1,keylen);
	     
	       memcpy(key,&bufTCPRecv[count],keylen);
	       count = count + keylen;
	       datalen  |= bufTCPRecv[count++];
	       datalen  |= bufTCPRecv[count++] << 8;
	       datalen  |= bufTCPRecv[count++] << 16;
	       datalen  |= bufTCPRecv[count++] << 24;
	       LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: opCode[%s] for intfId[%d] tableId[%d] key[%d] keylen[%d] datalen[%d] \n",PRINT_OPCODE(opCode),intfId,tableId,*(int*)key,keylen,datalen);
	       switch(opCode)
	       {
		 case INSERT:
		   ret = InsertEntryTcp(intfId,tableId,key,keylen,&bufTCPRecv[count],datalen);
		   if(ret != ROK)
		   {
		     LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: InsertEntryTcp failed for intfId[%d] tableId[%d] \n",intfId,tableId);
		   }
		   break;
		 case DELETE:
		   ret = DeleteEntryTcp(intfId,tableId,key,keylen);
		   if(ret != ROK)
		   {
		     LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: DeleteEntryTcp failed for intfId[%d] tableId[%d] \n",intfId,tableId);
		   }
		   break;
		 case UPDATE:
		   ret = UpdateEntryTcp(intfId,tableId,key,keylen,&bufTCPRecv[count]);
		   if(ret != ROK)
		   {
		     LOG_PRINT(INFO,"BSSAP_HA:TCPRECV_Server: UpdateEntryTcp failed for intfId[%d] tableId[%d] \n",intfId,tableId);
		   }
		   break;
		 default:
		   break;
	       }
	       len = len - (datalen + keylen);
	       count = count + datalen;
	     }
	   }
	 }
	 LOG_PRINT(INFO,"BSSAP_HA:###################TCP DATA BUFFER END ####################### \n");
       }
  }
  return FAILURE;
}

void SendSyncLockToken()
{

  char syncbuf[6];
  int ret = 0;

     
  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  memset(&syncbuf,0,5);

  syncbuf[0] = SYNC_LOCK;
  syncbuf[1] = 0x00; 
  syncbuf[2] = 0x00;
  syncbuf[3] = 0x00;
  syncbuf[4] = 0x00;
  syncbuf[5] = 0x00;
  syncbuf[6] = 0x00;


  ret = send (TcpClient,syncbuf,7,0);

  if (ret <= 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:SendSyncLockToken: PEER UP: SYNC LOCK token SEND TO PEER  failed ret[%d]",ret);
  }
  else
  {
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:TOKEN:SendSyncLockToken:SYNC LOCK  token Send TO PEER Success \n");
    syncFlag = 2;
    SyncStartMsec = current_timestamp();
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:TOKEN:SendSyncLockToken:SyncStartMsec[%lld] \n",SyncStartMsec);
  }
       
  return;
}
void SendSyncUnLockToken()
{

  char syncUnlockbuff[6];
  int ret = 0;

  memset(&syncUnlockbuff,0,6);
  
  syncUnlockbuff[0] = SYNC_UNLOCK;
  syncUnlockbuff[1] = 0x00;
  syncUnlockbuff[2] = 0x00;
  syncUnlockbuff[3] = 0x00;
  syncUnlockbuff[4] = 0x00;
  syncUnlockbuff[5] = 0x00;
  syncUnlockbuff[6] = 0x00;

  ret = send (TcpClient,syncUnlockbuff,7, 0);
  if (ret <= 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:SendSyncUnLockToken: PEER UP: SYNC UNLOCK token SEND TO PEER  failed ret[%d]",ret);
  }
  else
  {
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:TOKEN:SendSyncUnLockToken:SYNC UNLOCK  token Send TO PEER Success \n");
    syncFlag = 0;
    SyncEndMsec = current_timestamp();
    LOG_PRINT(INFO,"BSSAP_HA:TO_PEER:TOKEN:SendSyncLockToken:SyncEndMsec[%lld] \n",SyncEndMsec);
    LOG_PRINT(INFO,"BSSAP_HA:SendSyncLockToken: TOTAL SYNC TIME in msec[%lld] \n",(SyncEndMsec - SyncStartMsec));
  }
       
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  return;
}
int SendInterfaceDelUpdateToPeer(int intfId)
{
  int totallen = 0,tolaldatalen = 0;
  int ret = RFAILED;
  
  if((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
  {
    tolaldatalen = 0;
  
    bufPeerUpd[0] = DELETE;
    bufPeerUpd[1] = intfId;
    bufPeerUpd[2] = BSHASH_TABLE_INTF;
    bufPeerUpd[3] = tolaldatalen & 0x000000FF;
  
    bufPeerUpd[4] = (tolaldatalen & 0x0000FF00) >> 8;
    bufPeerUpd[5] = (tolaldatalen & 0x00FF0000) >> 16;
    bufPeerUpd[6] = (tolaldatalen & 0xFF000000) >> 24;
    totallen = 7 + tolaldatalen;
    
    ret = send (TcpClient, bufPeerUpd, totallen, 0);
    if (ret <= 0)
    {
      LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceDelUpdateToPeer: Buffer Send to Peer failed ret[%d]\n",ret);
      return RFAILED;
    }
    LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceDelUpdateToPeer: SEND DATA SUCCESS : byteSend[%d] len[%d]\n",ret,totallen);

  }
  else
  {
    LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceDelUpdateToPeer: Peer Absent, therefore No update for Interface \n");
  }
  return ROK;
  
}
int SendInterfaceAddUpdateToPeer(BsIntfCb *bsIntfCb)
{
  UPDMsg intfUpdMsg;
  int totallen = 0,tolaldatalen = 0;
  int ret = RFAILED;

  if((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
  {
    if(bsIntfCb == NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceAddUpdateToPeer: Interfcace ptr bsIntfCb is NULL \n");
      return RFAILED;
    }
  
    memset(&intfUpdMsg,0,sizeof(UPDMsg));
    memset(bufPeerUpd,0,MAX_MESSAGE_SIZE);

    intfUpdMsg.msgType = BSSMAP_INTFDB_UPDATE;
    intfUpdMsg.u.intfdb.intfId = bsIntfCb->intfId;
    intfUpdMsg.u.intfdb.bscId = bsIntfCb->bscId;
    intfUpdMsg.u.intfdb.ni = bsIntfCb->ni;
    intfUpdMsg.u.intfdb.opc = bsIntfCb->opc;
    intfUpdMsg.u.intfdb.phyDpc = bsIntfCb->phyDpc;
    intfUpdMsg.u.intfdb.swtch = bsIntfCb->swtch;

    intfUpdMsg.u.intfdb.t1.enb = bsIntfCb->t1.enb;
    intfUpdMsg.u.intfdb.t1.val = bsIntfCb->t1.val;
    intfUpdMsg.u.intfdb.t1.timer_id_key = bsIntfCb->t1.timer_id_key;

  
    intfUpdMsg.u.intfdb.t4.enb = bsIntfCb->t4.enb;
    intfUpdMsg.u.intfdb.t4.val = bsIntfCb->t4.val;
    intfUpdMsg.u.intfdb.t4.timer_id_key = bsIntfCb->t4.timer_id_key;

  
    intfUpdMsg.u.intfdb.t10.enb = bsIntfCb->t10.enb;
    intfUpdMsg.u.intfdb.t10.val = bsIntfCb->t10.val;
    intfUpdMsg.u.intfdb.t10.timer_id_key = bsIntfCb->t10.timer_id_key;

  
    intfUpdMsg.u.intfdb.t11.enb = bsIntfCb->t11.enb;
    intfUpdMsg.u.intfdb.t11.val = bsIntfCb->t11.val;
    intfUpdMsg.u.intfdb.t11.timer_id_key = bsIntfCb->t11.timer_id_key;

  
    intfUpdMsg.u.intfdb.t13.enb = bsIntfCb->t13.enb;
    intfUpdMsg.u.intfdb.t13.val = bsIntfCb->t13.val;
    intfUpdMsg.u.intfdb.t13.timer_id_key = bsIntfCb->t13.timer_id_key;

  
    intfUpdMsg.u.intfdb.t17.enb = bsIntfCb->t17.enb;
    intfUpdMsg.u.intfdb.t17.val = bsIntfCb->t17.val;
    intfUpdMsg.u.intfdb.t17.timer_id_key = bsIntfCb->t17.timer_id_key;

  
    intfUpdMsg.u.intfdb.t18.enb = bsIntfCb->t18.enb;
    intfUpdMsg.u.intfdb.t18.val = bsIntfCb->t18.val;
    intfUpdMsg.u.intfdb.t18.timer_id_key = bsIntfCb->t18.timer_id_key;

  
    intfUpdMsg.u.intfdb.t25.enb = bsIntfCb->t25.enb;
    intfUpdMsg.u.intfdb.t25.val = bsIntfCb->t25.val;
    intfUpdMsg.u.intfdb.t25.timer_id_key = bsIntfCb->t25.timer_id_key;

  
    intfUpdMsg.u.intfdb.trbsc.enb = bsIntfCb->trbsc.enb;
    intfUpdMsg.u.intfdb.trbsc.val = bsIntfCb->trbsc.val;
    intfUpdMsg.u.intfdb.trbsc.timer_id_key = bsIntfCb->trbsc.timer_id_key;
  
    intfUpdMsg.u.intfdb.resetRetryCount = bsIntfCb->resetRetryCount;
    intfUpdMsg.u.intfdb.resetIPRetryCount = bsIntfCb->resetIPRetryCount;
    //intfUpdMsg.u.intfdb.rstRcvtimerId = bsIntfCb->rstRcvtimerId;
   // intfUpdMsg.u.intfdb.rstSndtimerId = bsIntfCb->rstSndtimerId;
    intfUpdMsg.u.intfdb.PcSsnStatusInd = bsIntfCb->PcSsnStatusInd;
    intfUpdMsg.u.intfdb.overloadT17 = bsIntfCb->overloadT17;
    intfUpdMsg.u.intfdb.overloadT18 = bsIntfCb->overloadT18;
    intfUpdMsg.u.intfdb.Fistoverld = bsIntfCb->Fistoverld;
   // intfUpdMsg.u.intfdb.TrbsctimerId = bsIntfCb->TrbsctimerId;

  
    if(bsIntfCb->databuf)
    {
      memcpy(&intfUpdMsg.u.intfdb.Data,bsIntfCb->databuf,bsIntfCb->datalen);
      intfUpdMsg.u.intfdb.len = bsIntfCb->datalen;
    }
    
    //print_UPDMsg(&intfUpdMsg); 

    tolaldatalen = 1 + sizeof(BsUpdIntfDb); /* 1 added for msgType of UPDMsg */
  
    bufPeerUpd[0] = INSERT;
    bufPeerUpd[1] = bsIntfCb->intfId;
    bufPeerUpd[2] = BSHASH_TABLE_INTF;
    bufPeerUpd[3] = tolaldatalen & 0x000000FF;
  
    bufPeerUpd[4] = (tolaldatalen & 0x0000FF00) >> 8;
    bufPeerUpd[5] = (tolaldatalen & 0x00FF0000) >> 16;
    bufPeerUpd[6] = (tolaldatalen & 0xFF000000) >> 24;
      
    totallen = 7 + tolaldatalen;
    bufPeerUpd[7] = intfUpdMsg.msgType;
    memcpy(&bufPeerUpd[8],&intfUpdMsg.u.intfdb,sizeof(BsUpdIntfDb));    
  
    ret = send (TcpClient, bufPeerUpd, totallen, 0);
    if (ret <= 0)
    {
      LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceAddUpdateToPeer: Buffer Send to Peer failed ret[%d]\n",ret);
      return RFAILED;
    }
    LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceAddUpdateToPeer: SEND DATA SUCCESS : byteSend[%d] len[%d]\n",ret,totallen);
    //print_buf(bufPeerUpd,totallen);
  }
  else
  {
   LOG_PRINT(INFO,"BSSAP_HA:SendInterfaceAddUpdateToPeer: Peer Absent, therefore No update for Interface \n");
  }
  return ROK;
}
void SendPeerUpdateForHashTables(CmHashListCp *hashListCp,
                                 int intfId,
                                 unsigned int tableId,
				 unsigned char *key,
				 unsigned int keylen)
{
  int ret = 0;
  HashEntry *entry = NULL;
  U16 *prevEnt = NULL , *getEntry = NULL;
  int count = 0;
  int totallen = 0,tolaldatalen = 0,datalen = 0;
  CallIdCb *callIdVal = NULL;
  
  //LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: Start PEER UPDATE for interface with intfId[%d] tableId[%d] key[%d] keylen[%d]\n",intfId,tableId,*(int*)key,keylen);
  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);
  memset(bufPeerUpd,0,MAX_MESSAGE_SIZE);
  tolaldatalen = 0;
  totallen = 0;
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: hashListCp  for intfId[%d] tableId[%d] is NULL \n",intfId,tableId);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return;
  }
  bufPeerUpd[0] = INSERT;
  bufPeerUpd[1] = intfId;
  bufPeerUpd[2] = tableId;
  count = 7;
  getEntry = NULL;
  
  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if(ret != ROK)
  {
      //LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: cmHashListFind failed for intfId[%d] tableId[%d] key[%d] keylen[%d]\n",intfId,tableId,*(int*)key,keylen);
     BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
     return;
  }
    
  entry = (HashEntry *)getEntry; 
  if((entry != NULL) && (entry->key != NULL))
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables:  FOUND ENTRY IN HASHLIST for intfId[%d] tableId[%d]  key[%d]: datalen[%d] entry[%p] entry->key[%p] \n",intfId,tableId,*(int*)entry->key,entry->datalen,entry,entry->key);
#endif
    bufPeerUpd[count++] = entry->keylen & 0x000000FF;
    bufPeerUpd[count++] = (entry->keylen & 0x0000FF00) >> 8;
    bufPeerUpd[count++] = (entry->keylen & 0x00FF0000) >> 16;
    bufPeerUpd[count++] = (entry->keylen & 0xFF000000) >> 24;
    memcpy(&bufPeerUpd[count],entry->key,entry->keylen);
    count = count + entry->keylen;
    datalen = 0;
    if(entry->data)
    {
      if(tableId == BSHASH_TABLE_CALLREF_CTXT)
      {
	datalen = sizeof(UPDMsg);
	bufPeerUpd[count++] = datalen & 0x000000FF;
	bufPeerUpd[count++] = (datalen & 0x0000FF00) >> 8;
	bufPeerUpd[count++] = (datalen & 0x00FF0000) >> 16;
	bufPeerUpd[count++] = (datalen & 0xFF000000) >> 24;
        PackCallDbUpdData(tableId,&bufPeerUpd[count],entry->data);
      }
      else if(tableId == BSHASH_TABLE_CALLID_CTXT)
      {
	datalen = sizeof(U32);
	bufPeerUpd[count++] = datalen & 0x000000FF;
	bufPeerUpd[count++] = (datalen & 0x0000FF00) >> 8;
	bufPeerUpd[count++] = (datalen & 0x00FF0000) >> 16;
	bufPeerUpd[count++] = (datalen & 0xFF000000) >> 24;
	callIdVal = (CallIdCb *)entry->data;
	if(callIdVal)
	{
	  LOG_PRINT(INFO,"PACKING : CallID[%d] CallrefId[%d] \n",callIdVal->callId,callIdVal->callRefId);
	  memcpy(&bufPeerUpd[count],(U32 *)&callIdVal->callRefId,datalen);
	}
      }
    }
    count = count + datalen;
  }
       
    tolaldatalen  = count - 7; /* length of key + data pairs*/
    if(tolaldatalen > 0)
    {
      bufPeerUpd[3] = tolaldatalen & 0x000000FF;
      bufPeerUpd[4] = (tolaldatalen & 0x0000FF00) >> 8;
      bufPeerUpd[5] = (tolaldatalen & 0x00FF0000) >> 16;
      bufPeerUpd[6] = (tolaldatalen & 0xFF000000) >> 24;
      totallen = 7 + tolaldatalen;
      
      ret = send (TcpClient, bufPeerUpd, totallen, 0);
      if (ret <= 0)
      {
        LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: Buffer Send to Peer failed ret[%d]\n",ret);
        BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
        return;
      }
      LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: SEND DATA SUCCESS :tableId[%d] byteSend[%d] len[%d]\n",tableId,ret,totallen);
      //print_buf(bufPeerUpd,totallen);
     }
     else
     {
       LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: NO ENTRY IN HASHLIST for intfId[%d] tableId[%d] \n",intfId,tableId);
     }
     BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
     //LOG_PRINT(INFO,"BSSAP_HA:SendPeerUpdateForHashTables: -----EXITING----- \n");
     return;
}

int HashListTbInsert(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen,
		     void *dataptr,
		     int datalen)
{
  int ret = 0,count = 0;
  BsIntfCb *bsIntfCb = NULL;
  HashEntry *entry = NULL;
  HashEntry *getEntry = NULL;
  unsigned int totallen = 0,len = 0;
  unsigned char bufToSend[MAX_MESSAGE_SIZE];
  U32 callId = 0, callRefId = 0;
  CallIdCb *callIdPtr = NULL;

     
  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: hashListCp is NULL \n");
    return (RFAILED);
  }
  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);
 
  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if(getEntry)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: Entry already exists for tableId[%d] key[%d],Therefore No Insertion \n",tableId,*key);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  entry = (HashEntry*)calloc(1,sizeof(HashEntry));
  if(entry == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: could not allocate memory to entry ptr\n");
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  entry->key = calloc(1,keylen);
  if(entry->key == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: could not allocate memory to entry key ptr\n");
    free(entry);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  memcpy(entry->key,key,keylen);
  entry->keylen = keylen;
  entry->tableId = tableId;
  entry->intfId = intfId;
  entry->data = dataptr;
  entry->datalen = datalen;
  ret = cmHashListInsert(hashListCp,(U16 *)entry,(U8 *)key,keylen);
  if(ret != ROK)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: cmHashListInsert Failed for tableId[%d] \n",tableId);
    free(entry->key);
    free(entry);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert:ENTRY INSERT SUCCESS for tableId[%d] key[%d] keylen[%d]  entry[%p] entry->key[%p]\n",tableId,*(int*)key,keylen,entry,entry->key);
  //print_buf((unsigned char *)dataptr,datalen);
  
  if((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
  {
    memset(bufToSend,0,MAX_MESSAGE_SIZE);
   
    bufToSend[0] = INSERT; /*opCode = INSERT*/
    bufToSend[1] = intfId;/*intfId*/
    bufToSend[2] = tableId;/*TableId*/
    if(tableId == BSHASH_TABLE_CALLREF_CTXT)
    {
      len = 4 + keylen + 4 + sizeof(UPDMsg); /* adding 4 for  keylen bytes &  datalen bytes*/
    }
    else if (tableId == BSHASH_TABLE_CALLID_CTXT)
    {
      /*adding 4 for keylen,callrefIdlen bytes*/
      len = 4 + keylen + 4 + sizeof(callRefId); 
    }
    bufToSend[3] = len & 0x000000FF;
    bufToSend[4] = (len & 0x0000FF00) >> 8;
    bufToSend[5] = (len & 0x00FF0000) >> 16;
    bufToSend[6] = (len & 0xFF000000) >> 24;
    bufToSend[7] = keylen & 0x000000FF;
    bufToSend[8] = (keylen & 0x0000FF00) >> 8;
    bufToSend[9] = (keylen & 0x00FF0000) >> 16;
    bufToSend[10] = (keylen & 0xFF000000) >> 24;
    memcpy(&bufToSend[11],key,keylen);
    count = 11 + keylen;
    if(dataptr)
    {
      if(tableId == BSHASH_TABLE_CALLREF_CTXT)
      {
	datalen = sizeof(UPDMsg);
	bufToSend[count++] = datalen & 0x000000FF;
	bufToSend[count++] = (datalen & 0x0000FF00) >> 8;
	bufToSend[count++] = (datalen & 0x00FF0000) >> 16;
	bufToSend[count++] = (datalen & 0xFF000000) >> 24;
        PackCallDbUpdData(tableId,&bufToSend[count],dataptr);
      }
      else if(tableId == BSHASH_TABLE_CALLID_CTXT)
      {
	callIdPtr = (CallIdCb *)dataptr;
	if(callIdPtr)
	{
	  /*Packing CallRefId for this callId */
	  datalen = sizeof(callRefId);
	  bufToSend[count++] = datalen & 0x000000FF;
	  bufToSend[count++] = (datalen & 0x0000FF00) >> 8;
	  bufToSend[count++] = (datalen & 0x00FF0000) >> 16;
	  bufToSend[count++] = (datalen & 0xFF000000) >> 24;
	  
	  callRefId = callIdPtr->callRefId;
	  bufToSend[count++] = callRefId & 0x000000FF;
	  bufToSend[count++] = (callRefId & 0x0000FF00) >> 8;
	  bufToSend[count++] = (callRefId & 0x00FF0000) >> 16;
	  bufToSend[count++] = (callRefId & 0xFF000000) >> 24;
	}
	LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: PACKING  callId[%d] callRefId[%d] \n",*(U32*)key,callRefId);
      }
    }

    totallen = 7 + len;
    ret = send (TcpClient, bufToSend, totallen, 0);
    if (ret <= 0)
    {
      LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: Buffer Send to Peer failed ret[%d]\n",ret);
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (ROK);
    }

    LOG_PRINT(INFO,"BSSAP_HA:HashListTbInsert: SEND DATA SUCCESS : byteSend[%d] len[%d]\n",ret,totallen);
  
    //print_buf(bufToSend,totallen);
  }
  
  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    
  return (ROK);
}
int HashListTbDelete(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen)
{
  int ret = 0,count = 0;
  unsigned int totallen = 0,len = 0,datalen = 0;
  HashEntry *getEntry = NULL;
  unsigned char bufToSend[MAX_MESSAGE_SIZE];
  BsIntfCb *bsIntfCb = NULL;

  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: hashListCp is NULL \n");
    return (RFAILED);
  }

  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);

  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if((ret != ROK) || (getEntry == NULL))
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: cmHashListFind Failed for tableId[%d] key[%d] keylen[%d] entry[%p] \n",tableId,*(int*)key,keylen,getEntry);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: cmHashListFind Success for tableId[%d] key[%d] keylen[%d] entry[%p] entry->key[%p]\n",tableId,*(int*)key,keylen,getEntry,getEntry->key);

  ret = cmHashListDelete(hashListCp,(U16 *)getEntry);
  if(ret != ROK)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: cmHashListDelete failed for tableId[%d] key[%d] keylen[%d]\n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete:ENTRY DELETE SUCCESS for tableId[%d] & key[%d] keylen[%d] entry[%p] entry->key[%p]\n",tableId,*(int*)key,keylen,getEntry,getEntry->key);
  
  if((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
  {
    memset(bufToSend,0,MAX_MESSAGE_SIZE);
    datalen = 0;
   
    bufToSend[0] = DELETE; /*opCode = INSERT*/
    bufToSend[1] = intfId;/*intfId*/
    bufToSend[2] = tableId;/*TableId*/
    len = 4 + keylen + 4 + datalen; /* adding 1 for byte storing len value  of data .i.e bufToSend[7]*/
    bufToSend[3] = len & 0x000000FF;
    bufToSend[4] = (len & 0x0000FF00) >> 8;
    bufToSend[5] = (len & 0x00FF0000) >> 16;
    bufToSend[6] = (len & 0xFF000000) >> 24;
    bufToSend[7] = keylen & 0x000000FF;
    bufToSend[8] = (keylen & 0x0000FF00) >> 8;
    bufToSend[9] = (keylen & 0x00FF0000) >> 16;
    bufToSend[10] = (keylen & 0xFF000000) >> 24;
    memcpy(&bufToSend[11],key,keylen);
    count = 11 + keylen;
    bufToSend[count++] = datalen & 0x000000FF;
    bufToSend[count++] = (datalen & 0x0000FF00) >> 8;
    bufToSend[count++] = (datalen & 0x00FF0000) >> 16;
    bufToSend[count++] = (datalen & 0xFF000000) >> 24;

    totallen = 7 + len;
    ret = send (TcpClient, bufToSend, totallen, 0);
    if (ret <= 0)
    {
      LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: Buffer Send to Peer failed ret[%d]\n",ret);
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (ROK);
    }
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: SEND DATA SUCCESS : byteSend[%d] len[%d]\n",ret,totallen);
    
    //print_buf((unsigned char *)bufToSend,totallen);
  }
  if(getEntry)
  {
    //LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: --getEntry[%p] \n",getEntry);
    if(getEntry->key)
    {
     // LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete:--Freeing getEntry->key[%p]",getEntry->key);
      free(getEntry->key);
      getEntry->key = NULL;
    }
    //LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: -- data ptr[%p]\n",getEntry->data);
    getEntry->data = NULL;
    //LOG_PRINT(INFO,"BSSAP_HA:HashListTbDelete: --Freeing entry ptr[%p]\n",getEntry);
    free(getEntry);
    getEntry = NULL;
  }
  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
  
  return (ROK);
}

int HashListTbUpdate(CmHashListCp *hashListCp,
                     int intfId,
		     unsigned int tableId,
		     unsigned char* key,
		     unsigned int keylen,
		     void *dataptr)
{
  int ret = 0,count = 0;
  unsigned int datalen = 0,len = 0;
  unsigned int totallen = 0;
  unsigned char bufToSend[MAX_MESSAGE_SIZE];
  HashEntry *getEntry = NULL;
  BsIntfCb  *bsIntfCb = NULL;
  U32 callId = 0;
  int callIdlen = 0;
  
  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);

  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbUpdate: hashListCp is NULL \n");
    return (RFAILED);
  }

  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);

  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if(ret != ROK)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbUpdate: Entry does not exists for tableId[%d] key[%d] keylen[%d],Therefore No Updation \n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  LOG_PRINT(INFO,"BSSAP_HA:HashListTbUpdate:ENTRY FOUND SUCCESS for tableId[%d] & key[%d] keylen[%d] getEntry[%p]\n",tableId,*(int*)key,keylen,getEntry);
  getEntry->data = dataptr;
   
  datalen = getEntry->datalen; 
  //print_buf((unsigned char *)getEntry->data,datalen);
  if((TcpClient > 0) && (TcpServer > 0) && (SelfHASTATE == HA_CARDSTATE_ACTIVE))
  {
    memset(bufToSend,0,MAX_MESSAGE_SIZE);
    
   
    bufToSend[0] = UPDATE; /*opCode = INSERT*/
    bufToSend[1] = intfId;/*TableId*/
    bufToSend[2] = tableId;/*TableId*/
    if(tableId == BSHASH_TABLE_CALLREF_CTXT)
    {
      len = 4 + keylen + 4 + sizeof(UPDMsg); /* adding 4 for  keylen bytes &  datalen bytes*/
    }
    else if (tableId == BSHASH_TABLE_CALLID_CTXT)
    {
      len = 4 + keylen; /* adding 4 for  keylen bytes &  datalen bytes*/
    }
    bufToSend[3] = len & 0x000000FF;
    bufToSend[4] = (len & 0x0000FF00) >> 8;
    bufToSend[5] = (len & 0x00FF0000) >> 16;
    bufToSend[6] = (len & 0xFF000000) >> 24;
    bufToSend[7] = keylen & 0x000000FF;
    bufToSend[8] = (keylen & 0x0000FF00) >> 8;
    bufToSend[9] = (keylen & 0x00FF0000) >> 16;
    bufToSend[10] = (keylen & 0xFF000000) >> 24;
    memcpy(&bufToSend[11],key,keylen);
    count = 11 + keylen;
    if(dataptr)
    {
      if(tableId == BSHASH_TABLE_CALLREF_CTXT)
      {
	datalen = sizeof(UPDMsg);
	bufToSend[count++] = datalen & 0x000000FF;
	bufToSend[count++] = (datalen & 0x0000FF00) >> 8;
	bufToSend[count++] = (datalen & 0x00FF0000) >> 16;
	bufToSend[count++] = (datalen & 0xFF000000) >> 24;
	PackCallDbUpdData(tableId,&bufToSend[count],dataptr);
      }
      else if(tableId == BSHASH_TABLE_CALLID_CTXT)
      {
      }
    }
    totallen = 7 + len;
    ret = send (TcpClient, bufToSend, totallen, 0);
    if (ret <= 0)
    {
      LOG_PRINT(INFO,"BSSAP_HA:HashListTbUpdate: Buffer Send to Peer failed ret[%d]\n",ret);
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (ROK);
    }

    LOG_PRINT(INFO,"BSSAP_HA:HashListTbUpdate: SEND DATA SUCCESS : byteSend[%d] len[%d]\n",ret,totallen);
  
  //  print_buf(bufToSend,totallen);
  }
  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
  return (ROK);
}

int HashListTbSearch(CmHashListCp *hashListCp,
                     unsigned int tableId,
                     unsigned char* key,
		     int keylen,
		     HashEntry **entry)
{
  int ret = 0;
  HashEntry *getEntry = NULL;
  
  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashListTbSearch: hashListCp is NULL \n");
    return (RFAILED);
  }

  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);
   
  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if((ret != ROK) || (getEntry == NULL))
  {
   // LOG_PRINT(INFO,"BSSAP_HA:HashListTbSearch: cmHashListFind failed for tableId[%d] key[%d] keylen[%d] ret[%d]\n",tableId,*(int*)key,keylen,ret);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (ROKDNA);
  }
  LOG_PRINT(INFO,"BSSAP_HA:HashListTbSearch: ENTRY FIND SUCCESS for intfId[%d] tableId[%d] key[%d] keylen[%d] entry[%p] entry->key[%p]\n",getEntry->intfId,getEntry->tableId,*(int*)getEntry->key,keylen,getEntry,getEntry->key);
  
  *entry = (HashEntry *)getEntry;

  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
  
  return (ROK);
}
int HashTableListIterate(CmHashListCp *hashListCp,
                         int intfId,
			 unsigned int tableId,
			 void* in,
			 void* out,
			 BS_HASH_IterateEntryProc iterateEntryFn)
{
  U16 *prevEnt = NULL , *getEntry = NULL;
  HashEntry *entry = NULL;
  int ret = 0;
  
  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:HashTableListIterate: hashListCp is NULL \n");
    return (RFAILED);
  }
  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);
  prevEnt = NULL;
  getEntry = NULL;
  do
  {
     ret = cmHashListGetNext(hashListCp,prevEnt,&getEntry);
     if(ret != ROK)
     {
       LOG_PRINT(INFO,"BSSAP_HA:HashTableListIterate: cmHashListGetNext  for tableId[%d] is NULL \n",tableId);
       break;
     }
     if(getEntry)
     {
       entry = (HashEntry *)getEntry;
       if(entry->data)
       {
	 LOG_PRINT(INFO,"BSSAP_HA:HashTableListIterate: Entry found   for tableId[%d],Calling ITERATE Func \n",tableId);
         
	 ret = iterateEntryFn((char *)entry->data, in, out);
	 if (ret != ITS_SUCCESS)
	 {
           LOG_PRINT(INFO,"BSSAP_HA:HashTableListIterate: iterateEntryFn failed  for tableId[%d] \n",tableId);
           BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
	   return ret;
	 }

       }
     }        
      
     prevEnt = getEntry;
     getEntry = NULL;
     
  }while(prevEnt);
 
  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
  return ITS_SUCCESS;
}
void print_UPDMsg(UPDMsg *updMsgBuf)
{
  if(updMsgBuf == NULL)
  {
      LOG_PRINT(INFO,"BSSAP_HA:print_UPDMsg : Input buf ptr is NULL\n");
      return; 
  }
  if(updMsgBuf->msgType == BSSMAP_INTFDB_UPDATE)
  {
    LOG_PRINT(INFO,"BSSAP_HA:######################print_UPDMsg : ################################# \n");
    LOG_PRINT(INFO,"BSSAP_HA:msgType = BSSMAP_INTFDB_UPDATE \n");
    LOG_PRINT(INFO,"BSSAP_HA:intfId = [%d] \n",updMsgBuf->u.intfdb.intfId);
    LOG_PRINT(INFO,"BSSAP_HA:bscId = [%d] \n",updMsgBuf->u.intfdb.bscId);
    LOG_PRINT(INFO,"BSSAP_HA:ni = [%d] \n",updMsgBuf->u.intfdb.ni);
    LOG_PRINT(INFO,"BSSAP_HA:opc = [%d] \n",updMsgBuf->u.intfdb.opc);
    LOG_PRINT(INFO,"BSSAP_HA:phyDpc = [%d] \n",updMsgBuf->u.intfdb.phyDpc);
    LOG_PRINT(INFO,"BSSAP_HA:swtch = [%d] \n",updMsgBuf->u.intfdb.swtch);
    LOG_PRINT(INFO,"BSSAP_HA:resetRetryCount = [%d] \n",updMsgBuf->u.intfdb.resetRetryCount);
    LOG_PRINT(INFO,"BSSAP_HA:resetIPRetryCount = [%d] \n",updMsgBuf->u.intfdb.resetIPRetryCount);
    LOG_PRINT(INFO,"BSSAP_HA:rstRcvtimerId = [%d] \n",updMsgBuf->u.intfdb.rstRcvtimerId);
    LOG_PRINT(INFO,"BSSAP_HA:rstSndtimerId = [%d] \n",updMsgBuf->u.intfdb.rstSndtimerId);
    LOG_PRINT(INFO,"BSSAP_HA:PcSsnStatusInd = [%d] \n",updMsgBuf->u.intfdb.PcSsnStatusInd);
    LOG_PRINT(INFO,"BSSAP_HA:overloadT17 = [%d] \n",updMsgBuf->u.intfdb.overloadT17);
    LOG_PRINT(INFO,"BSSAP_HA:overloadT18 = [%d] \n",updMsgBuf->u.intfdb.overloadT18);
    LOG_PRINT(INFO,"BSSAP_HA:Fistoverld = [%d] \n",updMsgBuf->u.intfdb.Fistoverld);
    LOG_PRINT(INFO,"BSSAP_HA:TrbsctimerId = [%d] \n",updMsgBuf->u.intfdb.TrbsctimerId);
    LOG_PRINT(INFO,"Timer:T1[%d]:T4[%d]:T10[%d]:T11[%d]:T13[%d]:T17[%d]:T18[%d]:T25[%d]:Trbsc[%d] \n",updMsgBuf->u.intfdb.t1.val,updMsgBuf->u.intfdb.t4.val,updMsgBuf->u.intfdb.t10.val,updMsgBuf->u.intfdb.t11.val,updMsgBuf->u.intfdb.t13.val,updMsgBuf->u.intfdb.t17.val,updMsgBuf->u.intfdb.t18.val,updMsgBuf->u.intfdb.t25.val,updMsgBuf->u.intfdb.trbsc.val);
    LOG_PRINT(INFO,"BSSAP_HA:len = [%d] \n",updMsgBuf->u.intfdb.len);
    if(updMsgBuf->u.intfdb.len)
    {
      print_buf(updMsgBuf->u.intfdb.Data,updMsgBuf->u.intfdb.len);      
    }
    LOG_PRINT(INFO,"BSSAP_HA:######################print_UPDMsg : ################################# \n");
  }
  else if(updMsgBuf->msgType == BSSMAP_CALLDB_UPDATE)
  {

  }
  else
  {
      LOG_PRINT(INFO,"BSSAP_HA:print_UPDMsg : Invalid Msg Type\n");
      return; 
  }

}
void print_buf(unsigned char *bufprt,int buflen)
{
  unsigned int count;
  unsigned char buff[MAX_MESSAGE_SIZE];
  unsigned char TempBuffer[10];
   
  if (buflen != 0)
  {
      LOG_PRINT(INFO,"BSSAP_HA:###################################################\n");
      LOG_PRINT(INFO,"BSSAP_HA:PRINT buflen[%d] \n",buflen);
      
      memset(buff,0,MAX_MESSAGE_SIZE);
      for (count = 0; count < buflen; count++)
      {

	sprintf((char *)TempBuffer, "0x%02x ",bufprt[count]);
	strcat((char*)buff,(const char *)TempBuffer);
	if (!(count % 15)&& (count!=0))
	{
	  strcat((char *)buff,"\n");
	}
      }			                    
      LOG_PRINT(INFO,"BSSAP_HA:BUFFER:-\n\n%s\n\n",buff);
      LOG_PRINT(INFO,"BSSAP_HA:\n###################################################\n");
   
  }

}
void Peer_Leave()
{
       
  if(TcpClient != 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:Peer_Leave:Clearing :TcpClient: CLOSING FD[%d] \n",TcpClient);
    close (TcpClient);
    TcpClient = 0;
  }
  
  if(TcpServer != 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:Peer_Leave:Clearing :TcpServer: CLOSING FD[%d] \n",TcpServer);
    close (TcpServer);
    TcpServer = 0;
  }
  syncFlag = 1;
#ifdef PLATFORM_IMR
  /*Note: commented as HaState will only be update when recv event from bpm */ 
  /*SelfHASTATE = HA_CARDSTATE_ACTIVE;*/
#else
  SelfHASTATE = HA_CARDSTATE_ACTIVE;
  LOG_PRINT(INFO,"BSSAP_HA:Peer_Leave:-----SWITCHOVER----Setting  SelfHASTATE = HA_CARDSTATE_ACTIVE---------\n");
#endif
  SYNC_PEER = FALSE;
}
int BsHashCreateMutex(pthread_mutex_t * m)
{
   pthread_mutexattr_t attr;

   if (pthread_mutexattr_init (&attr) != 0)
   {
     LOG_PRINT(INFO,"BsHashCreateMutex: pthread_mutexattr_init  failed \n");
      return (-1);
   }

   if (pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE_NP) != 0)
   {
     LOG_PRINT(INFO,"BsHashCreateMutex: pthread_mutexattr_settype  failed \n");
     return (-1);
   }

   if (pthread_mutex_init (m, &attr) != 0)
   {
     LOG_PRINT(INFO,"BsHashCreateMutex: pthread_mutex_init  failed \n");
      return (-1);
   }
 return (1);
}
int BsHashAcquireMutex (pthread_mutex_t * m,int mutexType)
{
  if (pthread_mutex_lock (m) != 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:BsHashAcquireMutex:Fail\n");
    return (-1);
  }
  /*print mutex type acquired*/
  if(mutexType == SYNC_MUTEX)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashAcquireMutex: SYNC_MUTEX Acquired \n");
#endif
  }
  else if(mutexType == THREAD_MUTEX)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashAcquireMutex: THREAD_MUTEX Acquired \n");
#endif
  }
  return (1);
}
int BsHashReleaseMutex (pthread_mutex_t * m,int mutexType)
{
  if (pthread_mutex_unlock (m) != 0)
  {
    LOG_PRINT(INFO,"BSSAP_HA:BsHashReleaseMutex:Fail\n");
    return (-1);
  }
  /*print mutex type released*/
  if(mutexType == SYNC_MUTEX)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashReleaseMutex: SYNC_MUTEX Released \n");
#endif
  }
  else if (mutexType == THREAD_MUTEX)
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:BsHashReleaseMutex: THREAD_MUTEX Released \n");
#endif
  }
  return (1);
}
void BsHashDeleteMutex(pthread_mutex_t  *m)
{
      pthread_mutex_destroy(m);
}

int InsertEntryTcp(int intfId,
                   unsigned int tableId,
		   unsigned char* key,
		   unsigned int keylen,
		   void *dataptr,
		   int datalen)
{
  int ret = 0;
  CmHashListCp *hashListCp = NULL;
  HashEntry *entry = NULL;
  HashEntry *getEntry = NULL;
  BsIntfCb *bsIntfCb = NULL; 
  BsCallCb *call = NULL;
  UPDMsg *callUpdPtr = NULL;
  unsigned char opCode = 0;
  CallIdCb *callIdVal = NULL;

  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);

  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);

  bsIntfCb = BSFINDINTF(intfId);
  if(bsIntfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: bsIntfCb ptr is NULL for IntfId[%d] \n",intfId);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  if(tableId == BSHASH_TABLE_CALLID_CTXT)
  {
    hashListCp = bsIntfCb->callIdList;
  }
  if(tableId == BSHASH_TABLE_CALLREF_CTXT)
  {
    hashListCp = bsIntfCb->callRefList;
  }
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: hashListCp is NULL \n");
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }

  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if(getEntry)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: Entry already exists for tableId[%d] key[%d] keylen[%d],Therefore No Insertion \n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
    
  entry = (HashEntry *)calloc(1,sizeof(HashEntry));
  if(entry == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: could not allocate memory to entry ptr\n");
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  entry->key = calloc(1,keylen);
  if(entry->key == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: could not allocate memory to entry key ptr\n");
    free(entry);
    entry = NULL;
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  memcpy(entry->key,key,keylen);
  entry->keylen = keylen;
  entry->intfId = intfId;
  entry->tableId = tableId;

  if(tableId == BSHASH_TABLE_CALLREF_CTXT)
  {
    callUpdPtr = (UPDMsg *)dataptr;
    opCode = INSERT;
    call = RecvCalldbUpdData(opCode,&callUpdPtr->u.Calldb);
    if(call == NULL)
    {
       LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp:could not decode recv Calldb data \n");
       free(entry->key);
       entry->key = NULL;
       free(entry);
       entry = NULL;
       BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
       return (RFAILED);
    }
    entry->data = call;
    entry->datalen = sizeof(BsCallCb);
  }
  else if(tableId == BSHASH_TABLE_CALLID_CTXT)
  {
    callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
    if(callIdVal == NULL)
    {
       LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp:could not allocate memory to callIdVal ptr \n");
       free(entry->key);
       entry->key = NULL;
       free(entry);
       entry = NULL;
       BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
       return (RFAILED);
    }
    /*Unpacking CallId*/
    memcpy(&callIdVal->callId,(U32*)key,sizeof(U32));
    /*Unpacking Callref*/
    memcpy(&callIdVal->callRefId,(U32*)dataptr,datalen);
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp:UNPACKING callId[%d] callRefId[%d] \n",callIdVal->callId,callIdVal->callRefId);
    entry->data = callIdVal;
    entry->datalen = sizeof(CallIdCb);
  }

  ret = cmHashListInsert(hashListCp,(U16 *)entry,(U8 *)key,keylen);
  if(ret != ROK)
  {
    LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp: cmHashListInsert Failed for tableId[%d] & key[%d] keylen[%d]\n",tableId,*(int*)key,keylen);
    free(entry->data);
    free(entry);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  if(tableId == BSHASH_TABLE_CALLID_CTXT)
  {
    call = bsFindCall(bsIntfCb,callIdVal->callRefId);
    if(call)
    {
      LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp:Setting callId[%d] for callRefId[%d] in CallDb[%p] \n",callIdVal->callId,callIdVal->callRefId,call);
      call->callId = callIdVal->callId;
    }
  }
  LOG_PRINT(INFO,"BSSAP_HA:InsertEntryTcp:ENTRY INSERT SUCCESS for tableId[%d] & key[%d] keylen[%d] entry[%p] \n",tableId,*(int*)key,keylen,entry);
  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
  return (ROK);
}
int DeleteEntryTcp(int intfId,
                   unsigned int tableId,
		   unsigned char* key,
		   unsigned int keylen)
{
  int ret = 0;
  CmHashListCp *hashListCp = NULL;
  HashEntry *getEntry = NULL;
  BsIntfCb *bsIntfCb = NULL; 
  BsCallCb *call = NULL;
  CallIdCb *callIdVal = NULL;

  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);

  bsIntfCb = BSFINDINTF(intfId);
  if(bsIntfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp: bsIntfCb ptr is NULL for IntfId[%d] \n",intfId);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  if(tableId == BSHASH_TABLE_CALLREF_CTXT)
  {
    call = bsFindCall(bsIntfCb,*(int*)key);
    if(call)
    {
      /* Stopping any running timer for this call */
      bsStopConTmr(call,TMR_ALL);
      if(call->callId)
      {
	LOG_PRINT(INFO,"DeleteEntryTcp:CALLID[%d] present , hence first Deleteing it \n",call->callId);
	ret = HashListTbDelete(call->intfCb->callIdList,
	                       call->intfCb->intfId,
			       BSHASH_TABLE_CALLID_CTXT,
			       &call->callId,
			       sizeof(U32bit));
	if(ret == ROK)
	{
	  LOG_PRINT(INFO,"DeleteEntryTcp:HashListTbDelete SUCCESS for CALLID[%d] callref[%d]:intfId[%d] \n",call->callId,*(int*)key,intfId);
	  call->callId = 0;
	}
	else
	{
	  LOG_PRINT(CRITICAL,"DeleteEntryTcp: HashListTbDelete Failed for CALLID[%d] callref[%d] intfId[%d] \n",call->callId,*(int*)key,intfId);
          BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
	  return (RFAILED);
	}
      }
      /*Deallocating Call pointer */
      ret = bsDeallocateConRef(call);
      if(ret == SS7_FAILURE)
      {
        LOG_PRINT(CRITICAL,"DeleteEntryTcp:HashListTbDelete Failed for callref[%d]:intfId[%d] \n",*(int*)key,intfId);
	BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
	return (RFAILED);
      }
    }
    LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp:ENTRY DELETE SUCCESS for tableId[%d] & key[%d] keylen[%d]\n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (ROK);
  }
  else if (tableId == BSHASH_TABLE_CALLID_CTXT)
  {
    hashListCp = bsIntfCb->callIdList;
    if(hashListCp == NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp: hashListCp is NULL \n");
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (RFAILED);
    }
    ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
    if((ret != ROK) || (getEntry == NULL))
    {
      LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp: Entry does not exists for tableId[%d] key[%d] keylen[%d],Therefore No Deletion \n",tableId,*(int*)key,keylen);
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (RFAILED);
    }
  
    LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp:ENTRY FOUND SUCCESS for tableId[%d] & key[%d] keylen[%d] getEntry[%p]\n",tableId,*(int*)key,keylen,getEntry);

    callIdVal = (CallIdCb *)getEntry->data;
    if(callIdVal)
    {
       call = bsFindCall(bsIntfCb,callIdVal->callRefId);
       if(call)
       {
         LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp:Resetting callId for callRef[%d] in CallDb[%p] \n",callIdVal->callRefId,call); 
         call->callId = 0;
       }
    }
    ret = cmHashListDelete(hashListCp,(U16 *)getEntry);
    if(ret != ROK)
    {
      LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp: cmHashListDelete failed for tableId[%d] key[%d] keylen[%d] \n",tableId,*(int*)key,keylen);
      BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
      return (RFAILED);
    }
      LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp: AFTER getEntry[%p] \n",getEntry);
    if(getEntry)
    {
      if(getEntry->key)
      {
	free(getEntry->key);
	getEntry->key = NULL;
      }
      getEntry->data = NULL;
      free(getEntry);
    } 
    LOG_PRINT(INFO,"BSSAP_HA:DeleteEntryTcp:ENTRY DELETE SUCCESS for tableId[%d] & key[%d] keylen[%d]\n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (ROK);
  }
}
int UpdateEntryTcp(int intfId,
                   unsigned int tableId,
		   unsigned char* key,
		   unsigned int keylen,
		   void *dataptr)
{
  int ret = 0;
  CmHashListCp *hashListCp = NULL;
  HashEntry *getEntry = NULL;
  BsIntfCb *bsIntfCb = NULL; 
  unsigned char opCode = 0;
  BsCallCb *call = NULL;
  UPDMsg *callUpdPtr = NULL;


  BsHashAcquireMutex (&SyncLock,SYNC_MUTEX);
  
  BsHashReleaseMutex (&SyncLock,SYNC_MUTEX);
 
  BsHashAcquireMutex (&FlagLock,THREAD_MUTEX);

  bsIntfCb = BSFINDINTF(intfId);
  if(bsIntfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:UpdateEntryTcp: bsIntfCb ptr is NULL for IntfId[%d] \n",intfId);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  if(tableId == BSHASH_TABLE_CALLID_CTXT)
  {
    hashListCp = bsIntfCb->callIdList;
  }
  if(tableId == BSHASH_TABLE_CALLREF_CTXT)
  {
    hashListCp = bsIntfCb->callRefList;
  }
  if(hashListCp == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:UpdateEntryTcp: hashListCp is NULL \n");
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }

  ret = cmHashListFind(hashListCp,(U8 *)key,keylen,0,(U16 **)&getEntry);
  if(ret != ROK)
  {
    LOG_PRINT(INFO,"BSSAP_HA:UpdateEntryTcp: Entry does not exists for tableId[%d] key[%d] keylen[%d],Therefore No Updation \n",tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
  if(getEntry)
  {
    if(getEntry->data)
    {
      if(tableId == BSHASH_TABLE_CALLREF_CTXT)
      {
	callUpdPtr = (UPDMsg *)dataptr;
	opCode = UPDATE;
	call = RecvCalldbUpdData(opCode,&callUpdPtr->u.Calldb);
	if(call == NULL)
	{
	  LOG_PRINT(INFO,"BSSAP_HA:UpdateEntryTcp: RecvCalldbUpdData Fail for intfId[%d] tableId[%d] & key[%d] keylen[%d]\n",intfId,tableId,*(int*)key,keylen);
	  BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
	  return (RFAILED);
	}
	getEntry->data = call;
	getEntry->datalen = sizeof(BsCallCb);
      }
      else if(tableId == BSHASH_TABLE_CALLID_CTXT)
      {
      }
    }
    LOG_PRINT(INFO,"BSSAP_HA:UpdateEntryTcp:ENTRY UPDATE SUCCESS for intfId[%d] tableId[%d] & key[%d] keylen[%d]\n",intfId,tableId,*(int*)key,keylen);
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (ROK);
  }
  else
  {
    BsHashReleaseMutex (&FlagLock,THREAD_MUTEX);
    return (RFAILED);
  }
}
void BsHashInitHashList(int intfId)
{
 int ret = RFAILED;
 BsIntfCb *bsIntfCb = NULL;
 
 bsIntfCb = BSFINDINTF(intfId);
 if(bsIntfCb)
 {
    intfId = bsIntfCb->intfId;
    if((bsIntfCb->callIdList = (CmHashListCp*)calloc(1,sizeof(CmHashListCp))) == NULL)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashInitHashList : memory allocation failed for interface callIdList intfId[%d] \n",intfId);
       return;
    }
    if((bsIntfCb->callRefList = (CmHashListCp*)calloc(1,sizeof(CmHashListCp))) == NULL)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashInitHashList: memory allocation failed for interface callRefList intfId[%d] \n",intfId);
       return;
    }
    ret = cmHashListInit(bsIntfCb->callRefList,256, 0, 0,CM_HASH_KEYTYPE_U32MOD);
    if (ret != ROK)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashInitHashList :cmHashListInit failed for interface callRefList intfId[%d]\n",intfId);
       free(bsIntfCb->callRefList);
       bsIntfCb->callRefList = NULL;
       return;
    }
    ret = cmHashListInit(bsIntfCb->callIdList,256, 0, 0,CM_HASH_KEYTYPE_U32MOD);
    if (ret != ROK)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashInitHashList :cmHashListInit failed for interface callIdList intfId[%d] \n",intfId);
       free(bsIntfCb->callIdList);
       bsIntfCb->callIdList = NULL;
       return;
    }
       
    LOG_PRINT(INFO,"BSSAP_HA:BsHashInitHashList :Successfully Initialed Hashlist for  intfId[%d] \n",intfId);
 }
 return; 
}
void BsHashDeInitHashList(int intfId)
{
 
 int ret = RFAILED;
 BsIntfCb *bsIntfCb = NULL;
   
 bsIntfCb = BSFINDINTF(intfId);

 if(bsIntfCb)
 {
    ret = cmHashListDeinit(bsIntfCb->callRefList);
    if (ret != ROK)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashDeInitialize :cmHashListDeinit for interface callRefList intfId[%d]  \n",intfId);
       return;
    }
    LOG_PRINT(INFO,"BSSAP_HA:BsHashDeInitialize :cmHashListDeinit SUCCESS for interface callRefList intfId[%d] \n",intfId);
    if(bsIntfCb->callRefList)
    {
      free(bsIntfCb->callRefList);
      bsIntfCb->callRefList = NULL;
    }
    ret = cmHashListDeinit(bsIntfCb->callIdList);
    if (ret != ROK)
    {
       LOG_PRINT(INFO,"BSSAP_HA:BsHashDeInitialize :cmHashListDeinit for interface callIdList intfId[%d] \n",intfId);
       return;
    }
    LOG_PRINT(INFO,"BSSAP_HA:BsHashDeInitialize :cmHashListDeinit SUCCESS for interface callIdList intfId[%d] \n",intfId);
    if(bsIntfCb->callIdList)
    {
      free(bsIntfCb->callIdList);
      bsIntfCb->callIdList = NULL;
    }
 }
 return; 
}
void FillHashTableTillMaxVal(unsigned int tableId,int intfId)
{

  int j ,ret = RFAILED;
  BsIntfCb *bsIntfCb = NULL;
  BsCallCb *call = NULL;
  CallIdCb *callIdVal = NULL;

  if(MASTER == 1)
  {
    //LOG_PRINT(INFO,"BSSAP_HA: FillHashTableTillMaxVal :MASTER, hence fill data in CALLREF Hashlist \n");
      bsIntfCb = BSFINDINTF(intfId);
      if(bsIntfCb)
      {
	LOG_PRINT(INFO,"BSSAP_HA: FillHashTableTillMaxVal : Found INTERFACE with intfId[%d] bsIntfCb[%p]\n",intfId,bsIntfCb);
	for(j = 1; j <= bsCb.genCfg.nmbMaxCRef;j++)
	{
	  if(tableId == BSHASH_TABLE_CALLREF_CTXT)
	  {
	    call = bsCreate_InsertConRef(bsIntfCb);
	    if(call)
	    {
	      callIdVal = (CallIdCb *)calloc(1,sizeof(CallIdCb));
	      if(callIdVal == NULL)
	      {
		LOG_PRINT(INFO,"BSSAP_HA: FillHashTableTillMaxVal :could not allocate memory to callIdVal ptr \n");
		break;
	      }
	      callIdVal->callId = j;
	      callIdVal->callRefId = call->suInstId;
	      ret = HashListTbInsert(bsIntfCb->callIdList,bsIntfCb->intfId,BSHASH_TABLE_CALLID_CTXT,(unsigned char*)&callIdVal->callId,sizeof(U32),callIdVal,sizeof(CallIdCb));
	      if(ret != ROK)
	      {
		LOG_PRINT(INFO,"BSSAP_HA: FillHashTableTillMaxVal :could not Insert CallId Val [%d] \n",j);
		free(callIdVal);
		callIdVal = NULL;
		break;
	      }
	      /*Updateing call Id value in Call pointer */
	      call->callId = callIdVal->callId; 
	    }/*end of if(call) */
	  }
	}/*end of for loop */
      }
  }
  else
  {
    LOG_PRINT(INFO,"BSSAP_HA: FillHashTableTillMaxVal :SLAVE, hence do not fill data in CALLREF Hashlist \n");
  }
 return; 
}
long long current_timestamp(void) 
{
      
  struct timeval te;
 
  gettimeofday(&te, NULL); // get current time

  long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds

  LOG_PRINT(INFO,"BSSAP_HA:current_timestamp(): milliseconds: %lld\n", milliseconds);

  return milliseconds;
}
void PackCallDbUpdData(unsigned int tableId,
                       unsigned char *bufptr,
		       unsigned char *dataptr)
{
  UPDMsg call_updmsg;
  BsCallCb *calldb = NULL;
    
  memset(&call_updmsg,'\0',sizeof(UPDMsg));
  calldb = (BsCallCb *)dataptr;
  if(calldb)
  {
    call_updmsg.msgType=BSSMAP_CALLDB_UPDATE;
    if(calldb->intfCb)
    {
      call_updmsg.u.Calldb.intfId=calldb->intfCb->intfId;
    }
    else
    {
      LOG_PRINT(INFO,"BSSAP_HA:PackCallDbUpdData: calldb->intfCb is NULL for CallRef[%d] \n",calldb->suInstId);
    }

    call_updmsg.u.Calldb.suInstId=calldb->suInstId;
    call_updmsg.u.Calldb.spInstId=calldb->spInstId;
    call_updmsg.u.Calldb.cic=calldb->cic;
    call_updmsg.u.Calldb.timerId=calldb->timerId;
    call_updmsg.u.Calldb.callId=calldb->callId;
    call_updmsg.u.Calldb.appId=calldb->appId;
    call_updmsg.u.Calldb.callType=calldb->callType;
    call_updmsg.u.Calldb.handoverFlagSet=calldb->handoverFlagSet;
    call_updmsg.u.Calldb.hofaicause=calldb->hofaicause;
    call_updmsg.u.Calldb.channelAlloc=calldb->channelAlloc;
    call_updmsg.u.Calldb.msgType = calldb->msgType;
    memcpy(bufptr,&call_updmsg,sizeof(UPDMsg));
    LOG_PRINT(INFO,"BSSAP_HA:PackCallDbUpdData: PACKING CallRef[%d] AppId[%d] \n",calldb->suInstId,calldb->appId);
  }
  return;
}
BsCallCb* RecvCalldbUpdData(unsigned char opCode,BsUpdCallDb *calldb)
{
    
  BsCallCb   *call = NULL;
  U32  callRef;
  U32  callid;
  BsIntfCb  * bsIntfCb = NULL;
  U32  intfId = 0;
  BsLcfRef *Call =NULL;      /* source local reference */

  S16 ret;
		       
  if(calldb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : input calldb pointer is NULL \n");
    return NULL;
  }
		         
  intfId=calldb->intfId;
#ifdef DEBUG_ALL
  LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : RECV Call Update for IntfId[%d] \n",intfId);
#endif 
  bsIntfCb = BSFINDINTF(intfId);
  if(bsIntfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : bsIntfCb pointer is NULL \n");
    return NULL;
  }
 
  callRef=calldb->suInstId;
#ifdef DEBUG_ALL
  LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : RECV Call Update for Callref[%d] \n",callRef);
#endif 

  callid=callRef & 0x0000ffff;
  if(opCode == UPDATE)
  {
    call = bsFindCall(bsIntfCb ,callRef);
    if (call == NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : CALL Not found for Callref[%d] \n",callRef);
      return NULL;
    }
    call->suInstId=calldb->suInstId;
    call->spInstId=calldb->spInstId;
    call->cic=calldb->cic;
    call->timerId=calldb->timerId;
    call->callId=calldb->callId;
    call->appId=calldb->appId;
    call->msgType = calldb->msgType;
    call->callType = calldb->callType;
    call->handoverFlagSet=calldb->handoverFlagSet;
    call->hofaicause=calldb->hofaicause;
    call->channelAlloc=calldb->channelAlloc;
    LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : UPDATED OLD CALL:CallrefId[%d] AppId[%d] \n",callRef,call->appId);
  }
  else
  {
#ifdef DEBUG_ALL
    LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : ADDING NEW CALL:CallRefId[%d] AppId[%d]\n",calldb->suInstId,calldb->appId);
#endif
    callid--; /*index should be one less*/

    Call = *(bsIntfCb->lcfRef + callid );
    if(Call != NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : Already Occupied lcfRef Id[%d]\n",callid);
      return NULL;
    }
    Call = (unsigned char *)bssap_malloc((sizeof(BsLcfRef)));
    if(Call == SS7_NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : could not allocate memory to Call of size BsLcfRef\n");
      return NULL;
    }
    call = (unsigned char *)bssap_malloc((sizeof(BsCallCb)));
    if(call == SS7_NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : could not allocate memory to Call of size BsLcfRef\n");
      return NULL;
    }
  
    call->intfCb = bsIntfCb;
    *(bsIntfCb->lcfRef + callid) = Call;
    bsIntfCb->nmbLr++;
    bsIntfCb->nextLr++;
    Call->callCb = call;
    call->suInstId= calldb->suInstId;
    /*if(call->intfCb->nextLr == bsCb.genCfg.nmbMaxCRef)
    {
      call->intfCb->nextLr=0;
    }*/
    Call->allocateFfg= TRUE;
    call->suInstId=calldb->suInstId;
    call->spInstId=calldb->spInstId;
    call->cic=calldb->cic;
    call->timerId=calldb->timerId;
    call->callId=calldb->callId;
    call->appId=calldb->appId;
    call->msgType = calldb->msgType;
    call->callType = calldb->callType;
    call->handoverFlagSet=calldb->handoverFlagSet;
    call->hofaicause=calldb->hofaicause;
    call->channelAlloc=calldb->channelAlloc;
    /*cmInitTimers(call->timers, MAXSIMTIMER);*/
    LOG_PRINT(INFO,"BSSAP_HA:RecvCalldbUpdData : New Call Refernce Allocated [%d] : AppId[%d] nmbLr[%d]: nextLr[%d] \n",call->suInstId,call->appId,bsIntfCb->nmbLr,bsIntfCb->nextLr);
  }
  return (call);
}
void ProcessIntfDelUpdFrmPeer(int intfId)
{
  BsIntfCb *bsIntfCb = NULL;
  int i;
  BsCallCb *call= NULL;
  int ret = RFAILED;

  bsIntfCb = BSFINDINTF(intfId);
  if(bsIntfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfDelUpdFrmPeer : No Interface present for Deletion with intfId[%d]\n",intfId);
    return;
  }
  else
  {
      /*stop Interface timer*/
      bsStopIntfTmr(bsIntfCb,TMR_ALL);
    
      ret = cmHashListDeinit(bsIntfCb->callRefList);
      if(ret == RFAILED)
      {
	LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfDelUpdFrmPeer:cmHashListDeinit Failed for callRefList of intfId[%d] \n",intfId);
      }
      bsIntfCb->callRefList = NULL;
      
      ret = cmHashListDeinit(bsIntfCb->callIdList);
      if(ret == RFAILED)
      {
	LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfDelUpdFrmPeer:cmHashListDeinit Failed for  callIdList of intfId[%d] \n",intfId);
      }
      bsIntfCb->callIdList = NULL;
    
      if(bsIntfCb->databuf)
      {
	free(bsIntfCb->databuf);
	bsIntfCb->databuf = NULL;
      }
      bssap_free(bsIntfCb);
      bsIntfCb = NULL;
      bsCb.nmIntf--;
      *(bsCb.intfLst + intfId) = NULL;
	
      LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfDelUpdFrmPeer: INTERFACE with  intfId[%d] DELETE SUCCESS \n",intfId);
  }
  return;
}
void ProcessIntfAddUpdFrmPeer(BsUpdIntfDb *intfCb)
{
  U32 intfId = 0;
  BsIntfCb *bsIntfCb = NULL;

    LOG_PRINT(CRITICAL,"BSSAP_HA:TMP: ProcessIntfAddUpdFrmPeer :  Entering ...intfCb[%p] \n",intfCb);
  if(intfCb == NULL)
  {
    LOG_PRINT(INFO,"BSSAP_HA: ProcessIntfAddUpdFrmPeer : intfCb is NULL \n");
    return;
  }
  intfId = intfCb->intfId;
    
  LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: RECV update for Interface with intfId[%d] \n",intfId);
  
  bsIntfCb = BSFINDINTF(intfId);
  LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: bsIntfCb[%p] intfId[%d] \n",bsIntfCb,intfId);
  if(bsIntfCb)
  {
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: Interface with intfId[%d] bsIntfCb[%p] found , hence only updating it \n",intfId,bsIntfCb);
    bsIntfCb->resetRetryCount = intfCb->resetRetryCount; 
    bsIntfCb->resetIPRetryCount = intfCb->resetIPRetryCount;
/*Note:Commenting this , as no need to store & sync timer Id on standby card as timers are not replicated on standby card*/
    //bsIntfCb->rstRcvtimerId = intfCb->rstRcvtimerId;
    //bsIntfCb->rstSndtimerId = intfCb->rstSndtimerId;
    bsIntfCb->PcSsnStatusInd = intfCb->PcSsnStatusInd;
    bsIntfCb->overloadT17 = intfCb->overloadT17;
    bsIntfCb->overloadT18 = intfCb->overloadT18;
    bsIntfCb->Fistoverld = intfCb->Fistoverld;
    //bsIntfCb->TrbsctimerId = intfCb->TrbsctimerId;
    if(intfCb->len)
    {
      if(bsIntfCb->databuf)
      {
        LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: old databuf present , so free it \n");
        bssap_free(bsIntfCb->databuf);
	bsIntfCb->databuf = NULL;
      }
      bsIntfCb->databuf = (U8bit *)bssap_malloc(intfCb->len);
      if(bsIntfCb->databuf)
      {
        LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: updated New databuf for len[%d] \n",intfCb->len);
	ss7_memcpy((U8bit*)bsIntfCb->databuf,(U8bit*)intfCb->Data,intfCb->len);
	bsIntfCb->datalen = intfCb->len;
      }    
    }
    bsIntfCb->t1.enb = intfCb->t1.enb;
    bsIntfCb->t1.val = intfCb->t1.val;
    bsIntfCb->t1.timer_id_key = intfCb->t1.timer_id_key;
  
    bsIntfCb->t4.enb = intfCb->t4.enb;
    bsIntfCb->t4.val = intfCb->t4.val;
    bsIntfCb->t4.timer_id_key = intfCb->t4.timer_id_key;
    
    bsIntfCb->t10.enb = intfCb->t10.enb;
    bsIntfCb->t10.val = intfCb->t10.val;
    bsIntfCb->t10.timer_id_key = intfCb->t10.timer_id_key;
    
    bsIntfCb->t11.enb = intfCb->t11.enb;
    bsIntfCb->t11.val = intfCb->t11.val;
    bsIntfCb->t11.timer_id_key = intfCb->t11.timer_id_key;
    
    bsIntfCb->t13.enb = intfCb->t13.enb;
    bsIntfCb->t13.val = intfCb->t13.val;
    bsIntfCb->t13.timer_id_key = intfCb->t13.timer_id_key;
   
    bsIntfCb->t17.enb = intfCb->t17.enb;
    bsIntfCb->t17.val = intfCb->t17.val;
    bsIntfCb->t17.timer_id_key = intfCb->t17.timer_id_key;
    
    bsIntfCb->t18.enb = intfCb->t18.enb;
    bsIntfCb->t18.val = intfCb->t18.val;
    bsIntfCb->t18.timer_id_key = intfCb->t18.timer_id_key;
    
    bsIntfCb->t25.enb = intfCb->t25.enb;
    bsIntfCb->t25.val = intfCb->t25.val;
    bsIntfCb->t25.timer_id_key = intfCb->t25.timer_id_key;
      
    bsIntfCb->trbsc.enb = intfCb->trbsc.enb;
    bsIntfCb->trbsc.val = intfCb->trbsc.val;
    bsIntfCb->trbsc.timer_id_key = intfCb->trbsc.timer_id_key;
    
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: Interface with intfId[%d] updated successfully \n",intfId);
  }
  else
  {
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer: NO Interface with intfId[%d] found,Therefore Adding New Interface \n",intfId);
    /* Allocate memory for the Interface control block */
    bsIntfCb  = (BsIntfCb *) bssap_malloc (sizeof(BsIntfCb));
    if(bsIntfCb == SS7_NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer:could not allocate memory to bsIntfCb ptr");
      return;
    }
    LOG_PRINT(INFO,"BSSAP_HA: ProcessIntfAddUpdFrmPeer : New Interface ptr bsIntfCb[%p] \n",bsIntfCb);
    bs_mem_zero((U8bit *)bsIntfCb, sizeof(BsIntfCb));
    bsIntfCb->intfId = intfId;
    bsIntfCb->bscId = intfCb->bscId;
    bsIntfCb->ni = intfCb->ni;
    bsIntfCb->opc = intfCb->opc;
    bsIntfCb->phyDpc = intfCb->phyDpc;
    /* Updating global variable for src & destination PointCode */
    source_point_code = intfCb->opc;
    rem_pc            = intfCb->phyDpc;
    bsIntfCb->swtch = intfCb->swtch;       /* user */
      
    bsIntfCb->t1.enb = intfCb->t1.enb;
    bsIntfCb->t1.val = intfCb->t1.val;
    bsIntfCb->t1.timer_id_key = intfCb->t1.timer_id_key;
  
    bsIntfCb->t4.enb = intfCb->t4.enb;
    bsIntfCb->t4.val = intfCb->t4.val;
    bsIntfCb->t4.timer_id_key = intfCb->t4.timer_id_key;
      
    bsIntfCb->t10.enb = intfCb->t10.enb;
    bsIntfCb->t10.val = intfCb->t10.val;
    bsIntfCb->t10.timer_id_key = intfCb->t10.timer_id_key;
    
    bsIntfCb->t11.enb = intfCb->t11.enb;
    bsIntfCb->t11.val = intfCb->t11.val;
    bsIntfCb->t11.timer_id_key = intfCb->t11.timer_id_key;
    
    bsIntfCb->t13.enb = intfCb->t13.enb;
    bsIntfCb->t13.val = intfCb->t13.val;
    bsIntfCb->t13.timer_id_key = intfCb->t13.timer_id_key;
   
    bsIntfCb->t17.enb = intfCb->t17.enb;
    bsIntfCb->t17.val = intfCb->t17.val;
    bsIntfCb->t17.timer_id_key = intfCb->t17.timer_id_key;
    
    bsIntfCb->t18.enb = intfCb->t18.enb;
    bsIntfCb->t18.val = intfCb->t18.val;
    bsIntfCb->t18.timer_id_key = intfCb->t18.timer_id_key;
    
    bsIntfCb->t25.enb = intfCb->t25.enb;
    bsIntfCb->t25.val = intfCb->t25.val;
    bsIntfCb->t25.timer_id_key = intfCb->t25.timer_id_key;
      
    bsIntfCb->trbsc.enb = intfCb->trbsc.enb;
    bsIntfCb->trbsc.val = intfCb->trbsc.val;
    bsIntfCb->trbsc.timer_id_key = intfCb->trbsc.timer_id_key;
    
    bsIntfCb->rstRcvtimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->rstSndtimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->TrbsctimerId = BSSAP_INVALID_TMRID;
    bsIntfCb->overloadT17 = BSSAP_INVALID_TMRID;
    bsIntfCb->overloadT18 = BSSAP_INVALID_TMRID;
    bsIntfCb->resetRetryCount = 0;
    bsIntfCb->resetIPRetryCount = 0;
    bsIntfCb->PcSsnStatusInd = intfCb->PcSsnStatusInd;
    /* Allocate memory for the Interface control block */
    bsIntfCb->lcfRef  = (BsLcfRef **) bssap_malloc ((bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));
    if(bsIntfCb->lcfRef == SS7_NULL)
    {
      LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer:could not allocate memory to bsIntfCb->lcfRef ptr \n");
      bssap_free(bsIntfCb);
      bsIntfCb = NULL;
      return;
    }
    bs_mem_zero((U8bit *)bsIntfCb->lcfRef, (bsCb.genCfg.nmbMaxCRef * (sizeof(BsLcfRef *))));
    bsIntfCb->databuf = SS7_NULL;
    *(bsCb.intfLst + intfId) = bsIntfCb;
    bsCb.nmIntf++;
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer : New Interface ptr bsIntfCb[%p] added to bsCb.intfLst\n",bsIntfCb);
#ifdef BSSAP_HA
    BsHashInitHashList(intfId);
#endif
    LOG_PRINT(INFO,"BSSAP_HA:ProcessIntfAddUpdFrmPeer:Interface with intfId[%d] Added Successfully \n",intfId);
  }
  return;
}



