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
#include "main.h"
#include <signal.h>
#include <arpa/inet.h>
#include <linux/kernel.h>
#include <string.h>		//strsignal
#include <execinfo.h>		//backtrace,backtrace_symbols
#include <ucontext.h>		//ucontext_t
#include <errno.h>
//#define _GNU_SOURCE
#define _USE_GNU
#include <string.h>		//strsignal
#define BACK_TRACE_DEPTH   100
void reg_sig_hndlr ();
int OldTid = 0;
int OldtokTid = 0;
int OldtokMsgId = 0;
unsigned int LEAVE_EVENT_SEND = 0;
#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_syslog.h>
#endif


#ifdef LOGGER_IMR
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)
#endif

#define MAX_UNLOCKMSG_SIZE 2000
#define MAX_MESSAGE_SIZE 140000
pthread_t TcpClientThread;
pthread_t UDPClientThread;
void Gcsutil_Invoke ();
void PEER_Leave ();
int TcpClient = 0;
int TcpServer = 0;
int UNIX_SMbox = -1;
int CMbox = -1;
int port = 0;
int TCP_PORT = 0;
int UDP_PORT = 0;
char MASTER = 0;
int syncFlag = 1;
int DONT_ALLOW =1; 
int PEER_ALRD_JOIN=0;
int LEAVE_PEER = 0;
int CLIENT_RETRY_FLAG = 0;   /* Used to introduce client connect delay incase of peer leave */
int PEER_NODE_UP = 0;
int tcp_listener;
int udp_listener;
/**SHOULD DIFFERENT FOR BOTH NODE****/
char CLISELF_UDPADDR[25];
char CLIPEER_UDPADDR[25];
char TCPSELF_IP[25];
char TCPPEER_IP[25];
/***********************************/
char *bufUnixRecv = NULL;
char *bufTCPRecv = NULL;
char bufUnlock[MAX_UNLOCKMSG_SIZE];

int sockfd_udp = -1;
int sockfd_udp_client = 0;
struct sockaddr_in servaddr_udp;
struct sockaddr_in cliaddr_udp;
struct State_Struct
{
  unsigned int Table_id;
  unsigned int Master_Flg;
  unsigned int Slave_Flg;
  unsigned int counter;
  unsigned int state;
  unsigned int Len;
  unsigned int Len_1;
  unsigned int Len_2;
  unsigned int Len_3;
  unsigned int Len_4;
  unsigned int Len_5;
  char *buf;
  char *buf_1;
  char *buf_2;
  char *buf_3;
  char *buf_4;
  char *buf_5;
  char Lock_Ack_Flag;
  char Lock_Ack_Flag_1;
  char Lock_Ack_Flag_2;
  char Lock_Ack_Flag_3;
  char Lock_Ack_Flag_4;
  char Lock_Ack_Flag_5;
  char *unlockbuf_1;
  char *unlockbuf_2;
  unsigned int unlockLen_1;
  unsigned int unlockLen_2;
  char un_1_flag;
  char un_2_flag;
  char un_3_flag;
  char un_4_flag;
};
struct token
{
  unsigned int MsgId;
  unsigned int Table_Id;
  unsigned int Master_Flg;
  unsigned int Slave_Flg;
  unsigned int counter;
  unsigned int Tid;
  unsigned int ack;
};
typedef struct token token;
typedef struct State_Struct State_Struct;
State_Struct Table_quee[50];
void SendResponse (token * tok_ptr);
void * UDP_Client (void *args);
void * UDP_Server (void *args);
void  DeallocateGlobalbuffers();
int msleep(unsigned long millisec) ; 
pthread_mutex_t FlagLock;
pthread_t UDPRecvThread = 0;
/****************sandeep chages ***********/
#define FAILURE -1

//pthread_mutex_t *m;
void
Read_ConfFile ()
{
  FILE *file;
  int len, i;
// int  offset =0;
  char buf[128];
  char *tmp = NULL, *dup = NULL;
  char *path;
  char *absPath;
  memset (buf, 0, 128);


  absPath = (char *) malloc (sizeof (char) * 100);
  path = getenv ((const char *) "CONFIG");
  if (path == NULL)
    {
      LOG_PRINT_CRITICAL ("XXXXXXXXXCRASH CONFIG ENV VAR NULLXXXXXXXXX\n");
      abort ();
    }
  LOG_PRINT_DEBUG ("XXXXXXXXXSUCCESSFULLY GET CONFIG ENV VAR[%s]XXXXXXXXX\n",
		   path);
  strcpy (absPath, path);
  strcat (absPath, "isilconf.dat");
  file = fopen (absPath, "r");
  if (file == NULL)
    {
      puts ("cannot open file");
      //GCSUTIL_DEBUG_TRACE(("XXXXXXXXXCRASHXXXXXXXXX\n"));
      LOG_PRINT_CRITICAL ("XXXXXXXXXCRASHXXXXXXXXX\n");
      abort ();

    }

  while (!feof (file))
    {
      fgets (buf, 128, file);
      tmp = strchr (buf, '=');

      if (!tmp)
	continue;
      *tmp = 0;
      tmp++;

      while (*tmp == ' ' || *tmp == '\t')
	tmp++;
      dup = tmp;

      if ((len = strlen (tmp)) == 0)
	{
	  return;
	}

      if (strstr (buf, "UNIX_PORT") != NULL)
	{
	  port = atoi (tmp);
	  GCSUTIL_DEBUG_TRACE (("UNIX_PORT=%d\n", port));
	}
      else if (strstr (buf, "UDP_PORT") != NULL)
	{
	  UDP_PORT = atoi (tmp);
	  GCSUTIL_DEBUG_TRACE (("UDP_PORT=%d\n", UDP_PORT));
	}
      else if (strstr (buf, "UDP_SELFIP") != NULL)
	{
	  strcpy (CLISELF_UDPADDR, tmp);
	  tmp = (char *) getenv ((const char *) "NET_PP_IP");
	  strcpy (CLISELF_UDPADDR, tmp);
	  GCSUTIL_DEBUG_TRACE (("UDP_SELFIP=%s\n", CLISELF_UDPADDR));

	}
      else if (strstr (buf, "UDP_PEERIP") != NULL)
	{
	  strcpy (CLIPEER_UDPADDR, tmp);
	  tmp = (char *) getenv ((const char *) "config_PEER_PP_IP");
	  strcpy (CLIPEER_UDPADDR, tmp);
	  GCSUTIL_DEBUG_TRACE (("UDP_PERRIP=%s\n", CLIPEER_UDPADDR));
	}
      else if (strstr (buf, "TCP_PORT") != NULL)
	{
	  TCP_PORT = atoi (tmp);
	  GCSUTIL_DEBUG_TRACE (("TCP_PORT=%d\n", TCP_PORT));
	}
      else if (strstr (buf, "TCPSELF_IP") != NULL)
	{
	  strcpy (TCPSELF_IP, tmp);
	  tmp = (char *) getenv ((const char *) "NET_PP_IP");
	  strcpy (TCPSELF_IP, tmp);
	  GCSUTIL_DEBUG_TRACE (("TCPSELF_IP=%s\n", TCPSELF_IP));
	}
      else if (strstr (buf, "TCPPEER_IP") != NULL)
	{
	  strcpy (TCPPEER_IP, tmp);
	  tmp = (char *) getenv ((const char *) "config_PEER_PP_IP");
	  strcpy (TCPPEER_IP, tmp);
	  GCSUTIL_DEBUG_TRACE (("TCPPEER_IP=%s\n", TCPPEER_IP));
	}
      else if (strstr (buf, "MASTER") != NULL)
	{
	  MASTER = atoi (tmp);
	  tmp = (char *) getenv ((const char *) "Node");
	  if (strcmp (tmp, "Node1") == 0)
	    {
	      GCSUTIL_DEBUG_TRACE (("Node configured is Node1 and MSATER = 1\n"));
	      MASTER = 1;
	    }
	  else
	    {
	      GCSUTIL_DEBUG_TRACE (("Node configured is Node2 and MASTER = 0\n"));
	      MASTER = 0;
	    }
	}

    }

  fclose (file);

  for (i = 0; i < 50; i++)
    {
      Table_quee[i].buf = NULL;
      Table_quee[i].buf_1 = NULL;
      Table_quee[i].buf_2 = NULL;
      Table_quee[i].buf_3 = NULL;
      Table_quee[i].buf_4 = NULL;
      Table_quee[i].buf_5 = NULL;
      Table_quee[i].Table_id = 0;
      Table_quee[i].Master_Flg = 0;
      Table_quee[i].Slave_Flg = 0;
      Table_quee[i].counter = 0;
      Table_quee[i].state = 0;
      Table_quee[i].Len = 0;
      Table_quee[i].Len_1 = 0;
      Table_quee[i].Len_2 = 0;
      Table_quee[i].Len_3 = 0;
      Table_quee[i].Len_4 = 0;
      Table_quee[i].Len_5 = 0;
      Table_quee[i].Lock_Ack_Flag = 0;
      Table_quee[i].Lock_Ack_Flag_1 = 0;
      Table_quee[i].Lock_Ack_Flag_2 = 0;
      Table_quee[i].Lock_Ack_Flag_3 = 0;
      Table_quee[i].Lock_Ack_Flag_4 = 0;
      Table_quee[i].Lock_Ack_Flag_5 = 0;
      Table_quee[i].unlockbuf_1 = NULL;
      Table_quee[i].unlockbuf_2 = NULL;
      Table_quee[i].unlockLen_1 = 0;
      Table_quee[i].unlockLen_2 = 0;
      Table_quee[i].un_1_flag = 0;
      Table_quee[i].un_2_flag = 0;
      Table_quee[i].un_3_flag = 0;
      Table_quee[i].un_4_flag = 0;


    }
  /*Allocating memory to global buffers*/
  bufUnixRecv = (char*) calloc(1,MAX_MESSAGE_SIZE * sizeof(char));
  if(bufUnixRecv == NULL)
  {
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     abort ();
  }
     LOG_PRINT_CRITICAL ("Allocate memory to bufUnixRecv:0x%x \n",bufUnixRecv);
  
  bufTCPRecv = (char*) calloc(1,MAX_MESSAGE_SIZE * sizeof(char));
  if(bufTCPRecv == NULL)
  {
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     LOG_PRINT_CRITICAL ("BPM unable allocate memory to bufUnixRecv:ABORTING \n");
     abort ();
  }
     LOG_PRINT_CRITICAL ("Allocate memory to bufTCPRecv:0x%x \n",bufTCPRecv);
}

//int main ()
void
Gcsutil_Invoke ()
{
  pthread_t Serverthread;
  pthread_t TcpServerThread;
/*
  pthread_t TcpClientThread;
  pthread_t UDPClientThread;
*/
  pthread_t UDPServerThread;
  int i = 0;
  int ret = 0;
  LOG_PRINT_MAJOR ("XXXXXXXXXSTART Gcsutil_InvokeXXXXXXXXX\n");
  for (i = 0; i < 50; i++)
    {
      Table_quee[i].Master_Flg = 0;
      Table_quee[i].Slave_Flg = 0;
      Table_quee[i].counter = 0;
      Table_quee[i].Table_id = 0;
      Table_quee[i].state = 0;
    }
  /* Catching Signal for ctrl c */
  //(void)signal(SIGINT, termination_handler);


  // Read_ConfFile();
  Read_ConfFile ();
  ret = MUTEX_CreateMutex (&FlagLock);
  if (ret == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("Mutex create Success\n"));
    }
  reg_sig_hndlr ();
 // pthread_create (&Serverthread, NULL, UNIX_Server, NULL);
  pthread_create (&TcpClientThread, NULL, Tcp_Client, NULL);
  pthread_create (&TcpServerThread, NULL, TCP_Server, NULL);
  pthread_create (&UDPClientThread, NULL, UDP_Client, NULL);
  pthread_create (&UDPServerThread, NULL, UDP_Server, NULL);



   sleep(1);
  pthread_create (&Serverthread, NULL, UNIX_Server, NULL);
//  pthread_join (Serverthread, NULL);
  pthread_join (TcpServerThread, NULL);

  LOG_PRINT_MAJOR ("XXXXXXXXXEND Gcsutil_InvokeXXXXXXXXX\n");

//return(0);
}

pthread_t Recvhread = 0;
void *
UNIX_Server (void *args)
{
  int mbox, len;
  struct sockaddr_un unix_addr;
  //struct sockaddr_un peer_addr;

  LOG_PRINT_CRITICAL ("ALERT ::::: UNIX SERVER THREAD INVOKE \n");
  bzero (&unix_addr, sizeof (unix_addr));
  unix_addr.sun_family = AF_LOCAL;
  sprintf (unix_addr.sun_path, "/tmp/%d", port);
  unlink (unix_addr.sun_path);

  mbox = socket (AF_LOCAL, SOCK_STREAM, 0);
  if (mbox < 0)
    {
      LOG_PRINT_CRITICAL ("UNIX_Server: Socket(): failed\n");
      perror ("UNIX_Server:socket() failed ");
      exit (1);
    }
   LOG_PRINT_CRITICAL ("UNIX_Server: SOCKET OPEN for UNIX mbox Fd[%d] \n",mbox);
  if (bind (mbox, (struct sockaddr *) &unix_addr, sizeof (unix_addr)) == -1)
    {
      LOG_PRINT_CRITICAL ("UNIX_Server:bind() failed  \n");
      perror ("UNIX_Server:bind() failed ");
      exit (1);
    }
  SocketOption (mbox);
  if (listen (mbox, 5) < 0)
    {
      perror ("UNIX_Server:listen() failed ");
      LOG_PRINT_CRITICAL ("UNIX_Server:listen() failed \n");
    }
  len = sizeof (struct sockaddr_un);
  while (1)
    {
      if ((UNIX_SMbox = accept (mbox, 0, 0)) == -1)
	{
	  // GCSUTIL_DEBUG_TRACE( ("UNIX_Server:accept() failed\n"));
	  LOG_PRINT_CRITICAL ("UNIX_Server:accept() failed\n");
	}
      else
	{

          LOG_PRINT_CRITICAL ("UNIX_Server: ACCEPT SUCCESS for UNIX mbox Fd[%d] \n",mbox);
	  //GCSUTIL_DEBUG_TRACE( ("UNIX Connection OK\n"));
	  pthread_create (&Recvhread, NULL, UNIX_Recv, NULL);
	}
    }

}

#ifdef ASHU
void *
Client (void *args)
{
  int mbox, ret, len;
  struct sockaddr_un unix_addr;
  struct sockaddr_un peer_addr;
  struct sockaddr_in cliaddr;
  unix_addr.sun_family = AF_UNIX;
  sprintf (unix_addr.sun_path, "/tmp/%d", port);
  mbox = socket (AF_UNIX, SOCK_STREAM, 0);
  if (mbox < 0)
    {
      LOG_PRINT_CRITICAL ("Client:Socket Failed\n");
      perror ("Client:socket() failed ");
      exit (1);
    }

  len = sizeof (struct sockaddr_un);
  while (1)
    {
      if (CMbox == 0)
	{
	  ret = connect (mbox, (struct sockaddr *) &unix_addr, len);
	  GCSUTIL_DEBUG_TRACE (("Connect Connection ConnId=%d\n", ret));
	  GCSUTIL_DEBUG_TRACE (("connect"));
	  CMbox = mbox;
	}
      else
	{
	  LOG_PRINT_CRITICAL ("Connect Connection  Fail ConnId=%d\n", CMbox);
	  perror ("Client:connect() failed ");

	}
       if(CMbox == 0 )
       {
           sleep(1);
       }
       else
       {
            sleep(5);
       }
    }


}
#endif

void *
UNIX_Recv (void *args)
{
  int first = 1;
  char data[1000];
  char UDP_buff[50];
  unsigned int len = 0, i = 0, remain = 0;
  int nbytes = 0;

	  LOG_PRINT_CRITICAL ("ALERT ::::: UNIX RECV THREAD INVOKE\n");

  char buff[] =
    { 0xC0, 0xa8, 0x04, 0xC3, 0x4C, 0x6b, 0x26, 0x8A, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
      0x23, 0x64,
    0x2d, 0x31, 0x2d, 0x35, 0x2d, 0x30, 0x23, 0x6e, 0x6f, 0x64, 0x65, 0x31,
      0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00,
    0x00, 0x00
  };

  char buffNode2[] =
  {0xc0, 0xa8,0x0e,0x7f,0x4c,0x72,0x2d,0x05,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,
   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x23,0x64,0x2d,0x32,0x2d,0x35,0x2d,0x30,
   0x23,0x6e,0x6f,0x64,0x65,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00};

  int ret_1 = 0, ret_3 = 0;
  message_header *head_ptr;
  DSM_Message *msg = NULL;
  int tableId = 0, ret = 0, tid = 0;
  token tokmsg;
  //struct sockaddr_in cliaddr;
//  char bufUnixRecv[MAX_MESSAGE_SIZE];
//  char bufUnixTempBuf[MAX_MESSAGE_SIZE];
  while (1)
    {
      if (UNIX_SMbox < 0)
	continue;
      memset (bufUnixRecv, 0, MAX_MESSAGE_SIZE);

      /*This flag is only for Join Message */
      if (first == 1)
	{
	  ret_1 = recv (UNIX_SMbox, bufUnixRecv, 20, 0);
	  GCSUTIL_DEBUG_TRACE( ("recv len [%d] UNIX_SMbox[%d] \n",ret_1,UNIX_SMbox));
	  if (ret_1 > 15)
	    {
	      //GCSUTIL_DEBUG_TRACE (("len have exceed \n"));
              LOG_PRINT_CRITICAL ("UNIX_Recv:len have exceed ");
	      continue;
	    }
	  else
	    {
	      GCSUTIL_DEBUG_TRACE( ("JOIN:RECV len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));
	      if (ret_1 < 0)
		{
		  GCSUTIL_DEBUG_TRACE (("ret_1[%d]", ret_1));
		  perror ("UNIX_Recv:recv() failed ");
		  continue;
		}
	      first = 0;
	      bufUnixRecv[0] = 5;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 < 0)
		{
		  GCSUTIL_DEBUG_TRACE (("UNIX_SMbox:send\n"));
		  GCSUTIL_DEBUG_TRACE (("\n ERROR"));
		  GCSUTIL_DEBUG_TRACE (("ret_1[%d]", ret_1));
		  perror ("UNIX_Recv:send() failed ");
		}
	      GCSUTIL_DEBUG_TRACE( ("JOIN:1. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));
	      len = 5;
	      //memset(bufUnixRecv,'\0',len);
	      strcpy (bufUnixRecv, "NULL");
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, len, 0);
	      if (ret_1 < 0)
		{
		  GCSUTIL_DEBUG_TRACE (("UNIX_SMbox:send failed\n"));
		  GCSUTIL_DEBUG_TRACE (("ret_1[%d]", ret_1));
		  perror ("UNIX_Recv:send() failed ");
		}
	      GCSUTIL_DEBUG_TRACE( ("JOIN:2. SEND len have ret %d\n", ret_1));
	      ret_1 = recv (UNIX_SMbox, bufUnixRecv, 90, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:recv failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:recv() failed ");
		}
	      GCSUTIL_DEBUG_TRACE( ("JOIN:3. RECV len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));
	      bufUnixRecv[0] = 1;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}
			GCSUTIL_DEBUG_TRACE( ("JOIN:4. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));
      bufUnixRecv[0] = 3;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}
						GCSUTIL_DEBUG_TRACE( ("JOIN:5. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));

	      bufUnixRecv[0] = 16;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}
						GCSUTIL_DEBUG_TRACE( ("JOIN:6. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));

	      bufUnixRecv[0] = 0;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}
						GCSUTIL_DEBUG_TRACE( ("JOIN:7. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));

	      bufUnixRecv[0] = 14;
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 1, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}

						GCSUTIL_DEBUG_TRACE( ("JOIN:8. SEND len have ret [%d] UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));

	      memset (bufUnixRecv, 0, MAX_MESSAGE_SIZE);
						if(MASTER == 1)
						{
										strcpy (bufUnixRecv, "#d-1-5-0#node1");
						}
						else
						{
										strcpy (bufUnixRecv, "#d-2-5-0#node2");
						}
	      ret_1 = send (UNIX_SMbox, bufUnixRecv, 14, 0);
	      if (ret_1 <= 0)
		{
		  LOG_PRINT_CRITICAL ("UNIX_SMbox:send failed");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_exit (NULL);
		  perror ("UNIX_Recv:send() failed ");
		}
						GCSUTIL_DEBUG_TRACE( ("JOIN:9. SEND len have ret [%d]  UNIX_SMbox[%d]\n", ret_1,UNIX_SMbox));


	}
	}

      /*Handlind End of join Msg */



      memset (bufUnixRecv, 0, MAX_MESSAGE_SIZE);
     // memset (bufUnixTempBuf, 0, MAX_MESSAGE_SIZE);
      len = 80;
      for (i = 0, remain = len; remain > 0; i += nbytes, remain -= nbytes)
	{
          //LOG_PRINT_CRITICAL (" UNIX_SMbox: Waiting on UNIX RECV for packet HDR from STACKS \n");
	  //nbytes = recv (UNIX_SMbox, &bufUnixTempBuf[i], remain, 0);
	  nbytes = recv (UNIX_SMbox, &bufUnixRecv[i], remain, 0);
	  if (nbytes <= 0)
	    {
	      LOG_PRINT_CRITICAL ("1.UNIX_Recv Broken \n");
	      LOG_PRINT_CRITICAL ("1.UNIX_Recv Broken \n");
	      LOG_PRINT_CRITICAL ("1.UNIX_Recv Broken \n");
              DeallocateGlobalbuffers();
	      abort ();
	      close (UNIX_SMbox);
	      UNIX_SMbox = 0;
	      ResetAllFlags_OnUnixBreak ();
		  pthread_exit (NULL);
	      break;
	    }
	  if (nbytes != len)
	    {
	      GCSUTIL_DEBUG_TRACE (("FROMSTACK:UNIX_Recv:: Try Recv  header bytes len[%d] nbytes[%d]\n", len, nbytes));
	    }
	}
              //LOG_PRINT_CRITICAL (" UNIX_SMbox:  UNIX RECV for packet HDR from STACKS :nbytes[%d]\n",nbytes);
     // memcpy (bufUnixRecv, bufUnixTempBuf, 80);
      head_ptr = (message_header *) bufUnixRecv;
      head_ptr->type = Clear_Endian (head_ptr->type);

      if (head_ptr->type == 0)continue;

      if (head_ptr->data_len > 0)
	{
	  len = head_ptr->data_len;
	  nbytes = 0;
//	  memset (bufUnixTempBuf, 0, MAX_MESSAGE_SIZE);
                    
	  for (i = 80, remain = len; remain > 0; i += nbytes, remain -= nbytes)
	    {
	      //nbytes = recv (UNIX_SMbox, &bufUnixTempBuf[i], remain, 0);
              //LOG_PRINT_CRITICAL (" UNIX_SMbox: Waiting on UNIX RECV for packet DATA from STACKS \n");
	      nbytes = recv (UNIX_SMbox, &bufUnixRecv[i], remain, 0);
	      if (nbytes <= 0)
		{
		  LOG_PRINT_CRITICAL ("2.UNIX_Recv Broken \n");
		  LOG_PRINT_CRITICAL ("2.UNIX_Recv Broken \n");
		  LOG_PRINT_CRITICAL ("2.UNIX_Recv Broken \n");
                  DeallocateGlobalbuffers();
		  abort ();
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  ResetAllFlags_OnUnixBreak ();
		  pthread_exit (NULL);
		  break;
		}
	      if (nbytes != len)
		{
		  LOG_PRINT_CRITICAL("###############################################################\n");
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::MISMATCH len[%d] nbytes[%d]\n", len, nbytes);
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::MISMATCH len[%d] nbytes[%d]\n", len, nbytes);
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::MISMATCH len[%d] nbytes[%d]\n", len, nbytes);
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::MISMATCH len[%d] nbytes[%d]\n", len, nbytes);
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::MISMATCH len[%d] nbytes[%d]\n", len, nbytes);
		  LOG_PRINT_CRITICAL("###############################################################\n");
		}
	    }
            if(head_ptr->data_len > 20000)
            {
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::LEN RECV GREATER THAN 20000: RecvLen[%d]\n",head_ptr->data_len);
            }
             // LOG_PRINT_CRITICAL (" UNIX_SMbox:  UNIX RECV for packet DATA from STACKS :nbytes[%d]\n",nbytes);
	 // memcpy (&bufUnixRecv[80], bufUnixTempBuf, len);
	  msg = (DSM_Message *) & bufUnixRecv[80];
	 // GCSUTIL_DEBUG_TRACE( ("FROMSTACK:UNIX_RECV::  msg len=%d ,Discrimin %x\n", ret_1, msg->discriminator));
	}



    //  GCSUTIL_DEBUG_TRACE(("------------FROMSTACK: UNIX_Recv Start----------\n"));

      MUTEX_AcquireMutex (&FlagLock);

  if (head_ptr->type == 0x00010000)
	{
      /*Handling of Join Membership Message from STACK*/
	  GCSUTIL_DEBUG_TRACE( ("FROMSTACK:UNIX_RECV:: JOIN MEMBERSHIP MSG RECV \n"));
	  head_ptr->type = 0x00001100;
	  head_ptr->type = Set_Endian (head_ptr->type);

	  head_ptr->hint = (0 << 8) & 0x00ffff00;
	  head_ptr->hint = Set_Endian (head_ptr->hint);
	  head_ptr->data_len = 56;
    if(MASTER == 1)
	  {
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0)
		  && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN == 1))
      {
	 	     head_ptr->num_groups = 2;
      }
      else
      {  
		    head_ptr->num_groups = 1;
      } 
		    strcpy (head_ptr->private_group_name, "#d-1-5-0#node1");
		    memcpy (data, head_ptr, sizeof (message_header));
		    len = sizeof (message_header);

      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN== 1))
		  {
			  ret_3 = send (TcpClient, data, len, 0);
			  if (ret_3 <= 0)
			  {
				  LOG_PRINT_CRITICAL("UNIX_Recv: GCS MEMBERSHIP JOIN MSG HDR TcpClientsend() failed \n");
				  //close (TcpClient);
				  //TcpClient = 0;
                                  //PEER_ALRD_JOIN=0;
           MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
           MUTEX_AcquireMutex (&FlagLock);
			  }
       }

		    ret_3 = send (UNIX_SMbox, data, len, 0);
		    if (ret_3 < 0)
		    {
		            LOG_PRINT_CRITICAL("UNIX_Recv: GCS MEMBERSHIP JOIN MSG HDR send to Self failed \n");
			    close (UNIX_SMbox);
			    UNIX_SMbox = 0;
			    pthread_cancel (Recvhread);
			    continue;
		    }
                    if(ret_3 != len)
                    {
		            LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }

		  memset (data, 0, 1000);
      if( head_ptr->num_groups == 2 )
       {
	  	    strcpy (data, "#d-2-5-0#node2");
		      strcpy (&data[32],head_ptr->private_group_name);
		      memcpy (&data[64],buff, 56);/*Plz check the buff in case of node 1*/
		      len = 32 + 32 + 56;
       }
		 else if(head_ptr->num_groups == 1)
       { 
          strcpy (data,head_ptr->private_group_name);
		      memcpy (&data[32],buff, 56);
		      len = 32 + 56;
       }  
		  /*Towards GCS send */
      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN== 1))
		  {
			  ret_3 = send (TcpClient, data, len, 0);
			  if (ret_3 <= 0)
			  {
		            LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv:: MEMBERSHIP JOIN MSG  send to Peer failed on TcpClient[%d] len[%d] errno[%d] \n",TcpClient,ret_3,errno);
				  //close (TcpClient);
				  //TcpClient = 0;
                                  //PEER_ALRD_JOIN=0;
           MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
           MUTEX_AcquireMutex (&FlagLock);
			  }
			  LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv:: MEMBERSHIP JOIN MSG  Send to PEER SUCCESSFULLY:TcpClient[%d] len[%d]\n",TcpClient,len);
		  }
			  PEER_NODE_UP = 1;
		    ret_3 = send (UNIX_SMbox, data, len, 0);
		    if (ret_3 < 0)
		    {
			   perror ("UNIX_Recv:send() failed ");
		            LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv:: MEMBERSHIP JOIN MSG  send to Self failed len[%d] errno[%d]\n",ret_3,errno);
			   close (UNIX_SMbox);
			   UNIX_SMbox = 0;
			   pthread_cancel (Recvhread);
          Recvhread = 0;
			   continue;
		   }
                    if(ret_3 != len)
                    {
		            LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }
		  LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv:: MEMBERSHIP JOIN MSG Send to SELF SUCCESSFULLY :len[%d]\n",len);
	  }
  else
   {
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0)
		  && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN == 1))
      {
	 	     head_ptr->num_groups = 2;
      }
     else
      {
	 	     head_ptr->num_groups = 1;
      }

		  strcpy (head_ptr->private_group_name, "#d-2-5-0#node2");
		  memcpy (data, head_ptr, sizeof (message_header));
		  len = sizeof (message_header);

      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN== 1))
		  {
			  ret_3 = send (TcpClient, data, len, 0);
			  if (ret_3 <= 0)
			  {
		            LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv:: MEMBERSHIP JOIN MSG HDR send to Peer failed \n");
				  //close (TcpClient);
				  //TcpClient = 0;
                                  //PEER_ALRD_JOIN=0;
           MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
           MUTEX_AcquireMutex (&FlagLock);
			  }
		  }

		  ret_3 = send (UNIX_SMbox, data, len, 0);
		  if (ret_3 < 0)
		  {
		          LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv:: MEMBERSHIP JOIN MSG HDR send to Self failed \n");
			  close (UNIX_SMbox);
			  UNIX_SMbox = 0;
			  pthread_cancel (Recvhread);
          Recvhread = 0;
			  continue;
		  }
                    if(ret_3 != len)
                    {
		            LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }


		  memset (data, 0, 1000);
      if( head_ptr->num_groups == 2 )
      {
		    strcpy (data, "#d-1-5-0#node1");
		    strcpy (&data[32],head_ptr->private_group_name);
		    memcpy (&data[64], buffNode2, 56);
		    len = 32 + 32 + 56;
      }
      else if( head_ptr->num_groups == 1)
      {
		   strcpy (data,head_ptr->private_group_name);
		   memcpy (&data[32],  buffNode2, 56);
		   len = 32 + 56;
      }
		  /*Towards GCS send */
      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)&& (PEER_ALRD_JOIN== 1))
		  {
			  ret_3 = send (TcpClient, data, len, 0);
			  if (ret_3 <= 0)
			  {
				  GCSUTIL_DEBUG_TRACE (("UNIX_Recv: MEMBERSHIP JOIN msg Send to PEER failed TcpClient[%d] len[%d] errno[%d]",TcpClient,ret_3,errno));
				  //close (TcpClient);
				  //TcpClient = 0;
                                  //PEER_ALRD_JOIN=0;
           MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
           MUTEX_AcquireMutex (&FlagLock);
			  }
		  LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv:: MEMBERSHIP JOIN MSG Send to PEER SUCCESSFULLY :TcpClient[%d] len[%d]\n",TcpClient,len);
        PEER_NODE_UP = 1;
		  }

		  ret_3 = send (UNIX_SMbox, data, len, 0);
		  if (ret_3 < 0)
		  {
			  LOG_PRINT_CRITICAL ("UNIX_Recv:send() failed ");
			  perror ("UNIX_Recv:send() failed ");
			  close (UNIX_SMbox);
			  UNIX_SMbox = 0;
			  pthread_cancel (Recvhread);
          Recvhread = 0;
			  continue;
		  }
                  if(ret_3 != len)
                  {
		        LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                  }
		  LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv:: MEMBERSHIP JOIN MSG Send to SELF SUCCESSFULLY :len[%d]\n",len);
	  }
	}
      else if((head_ptr->type == 0x00000020) && (msg->discriminator == DSM_MSG_JOIN_INFO))
  {
              LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv:: JOIN INFO RECEIVED FROM STACK\n");
	      head_ptr->type = Set_Endian (head_ptr->type);
	      memcpy (data, head_ptr, sizeof (message_header));
	      memcpy (bufUnixRecv, data, sizeof (message_header));
	      len = sizeof (message_header) + head_ptr->data_len + 32;
	      /*Towards GCS send */
       if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
	      {
		      ret_3 = send (TcpClient, bufUnixRecv, len, 0); 
		      if (ret_3 <= 0)
		      {
			      LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv::JOIN INFO SEND TO PEER failed  on TcpClient[%d] len[%d] errno[%d]\n",TcpClient,ret_3,errno);
			      //close (TcpClient);
			      //TcpClient = 0;
                              //PEER_ALRD_JOIN=0;
           //MUTEX_ReleaseMutex (&FlagLock);
							PEER_NODE_UP = 1;
                              PEER_Leave();

			      LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv::JOIN INFO SEND failed on TCP,But sending to self stack \n");
			      //continue;
		      }
                      else
                      {
							            PEER_NODE_UP = 1;
                          LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv:: JOIN INFO SEND TO PEER SUCCESSFULLY on TcpClient[%d] :len[%d]\n",TcpClient,len);
                      }
         
	      }

	      ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
	      if (ret_3 <= 0)
	      {
		      LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv::JOIN INFO SEND TO SELF failed \n");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      MUTEX_ReleaseMutex (&FlagLock);
		      pthread_cancel (Recvhread);
          Recvhread = 0;
	      }
              if(ret_3 != len)
              {
	           LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
              }
              else
              { 
                 LOG_PRINT_CRITICAL("TOSTACK:UNIX_Recv:: JOIN INFO SEND TO SELF SUCCESSFULLY:len[%d]\n",len);
              }
  }


 else if (head_ptr->type == 0x00000020)
	{
	  switch (msg->discriminator)
	    {
	    case DSM_MSG_ALLOCATE_ROW:
	      tableId = msg->u.allocateRow.tableId;
	      tid = msg->u.allocateRow.tid;
	      // GCSUTIL_DEBUG_TRACE(("DSM_MSG_ALLOCATE_ROW\n"));
	      break;
	    case DSM_MSG_FIND_ROW:
	      //GCSUTIL_DEBUG_TRACE(("DSM_MSG_FIND_ROW\n"));
	      tableId = msg->u.findRow.tableId;
	      tid = msg->u.findRow.tid;
	      break;
	    case DSM_MSG_FREE_ROW:
	      //GCSUTIL_DEBUG_TRACE((" DSM_MSG_FREE_ROW\n"));
	      tableId = msg->u.freeRow.tableId;
	      tid = msg->u.freeRow.tid;
	      break;
	    case DSM_MSG_COMMIT_ROW:
	      //  GCSUTIL_DEBUG_TRACE(("DSM_MSG_COMMIT_ROW\n"));
	      tableId = msg->u.commitRow.tableId;
	      tid = msg->u.commitRow.tid;
	      break;
	    case DSM_MSG_JOIN_INFO:
	      break;
	    case DSM_MSG_SYNC_REQUEST:
	      //GCSUTIL_DEBUG_TRACE(("DSM_MSG_SYNC_REQUEST\n"));
	      break;
	    case DSM_MSG_SYNC_LOCK:
        DONT_ALLOW=0;
	      syncFlag = 2;
	      LOG_PRINT_MAJOR
		("FROMSTACK:UNIX_Recv:: SYNC_LOCK RECV FROM STACK:syncFlag %d DONT_ALLOW %d\n",
		 syncFlag,DONT_ALLOW);
	      break;
	    case DSM_MSG_SYNC_LOCK_RETRY:
	      //GCSUTIL_DEBUG_TRACE(("DSM_MSG_SYNC_LOCK_RETRY\n"));
	      break;
	    case DSM_MSG_SYNC_UNLOCK:
	      syncFlag = 0;
	      LOG_PRINT_MAJOR
		("FROMSTACK:UNIX_Recv::SYNC_UNLOCK RECV FROM STACK:syncFlag %d\n",
		 syncFlag);
	      break;
	    case DSM_MSG_SYNC_MEM:
	      GCSUTIL_DEBUG_TRACE (("FROMSTACK:UNIX_Recv::SYNC_MEM RECV FROM STACK\n"));
	      break;
	    case DSM_MSG_SYNC_INVALID_MASTER:
	      //   //GCSUTIL_DEBUG_TRACE(("DSM_MSG_SYNC_INVALID_MASTER\n"));
	      break;
	    case DSM_MSG_SYNC_MEM_TCP:
	      LOG_PRINT_MAJOR("FROMSTACK:UNIX_Recv::SYNC_MEM_TCP RECV FROM STACK\n");
	      break;
	    case DSM_MSG_LOCK_UNLOCK_ROW:
	      //  //GCSUTIL_DEBUG_TRACE(("DSM_MSG_LOCK_UNLOCK_ROW\n"));
	      break;
	    case DSM_MSG_LOCK_UNLOCK_TABLE:
	      //    GCSUTIL_DEBUG_TRACE(("DSM_MSG_LOCK_UNLOCK_TABLE Toggle Flag[%d]\n",msg->u.lockUnlockTable.lockUnlockToggle));
	      tableId = msg->u.lockUnlockTable.tableId;
	      tid = msg->u.lockUnlockTable.tid;

	      break;
	    case DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK:
	      // //GCSUTIL_DEBUG_TRACE(("DSM_MSG_LOCK_UNLOCK_ROW_NO_LOCK\n"));
	      break;
	    case DSM_MSG_LOCK_UNLOCK_DSM:
	      //  //GCSUTIL_DEBUG_TRACE(("DSM_MSG_LOCK_UNLOCK_DSM\n"));
	      break;
	    case DSM_MSG_MULTICAST_EVENT:
	      // //GCSUTIL_DEBUG_TRACE(("DSM_MSG_MULTICAST_EVENT\n"));
	      break;
	    case DSM_MSG_TO_TCAP_FROM_SCCP:
	      //  //GCSUTIL_DEBUG_TRACE(("DSM_MSG_TO_TCAP_FROM_SCCP\n"));
	      break;
	    case DSM_MSG_TO_TCAP_FROM_APPL:
	      //  //GCSUTIL_DEBUG_TRACE(("DSM_MSG_TO_TCAP_FROM_APPL\n"));
	      break;
	    case DSM_MSG_TCAP_ALLOCATE_DID:
	      //  //GCSUTIL_DEBUG_TRACE(("DSM_MSG_TCAP_ALLOCATE_DID\n"));
	      break;
	    default:
	      //GCSUTIL_DEBUG_TRACE( ("GARBAGE\n"));
	      break;



	    }

/*TEMP PATCH:23april :To discard multiple msg of same tid*/
	  if ((msg->discriminator == DSM_MSG_LOCK_UNLOCK_TABLE) && (syncFlag != 2))

	    {
	      if ((OldTid == tid) && (OldTid != 0))
		{
		  LOG_PRINT_MAJOR
		    ("FROMSTACK:UNIX_Recv::Duplicate Messsage from STACK Tid[%d] \n",
		     tid);
		  MUTEX_ReleaseMutex (&FlagLock);
		  continue;

		}
	      else
		{

		  OldTid = tid;
		}
	    }
	  head_ptr->type = 0x00000020;
	  head_ptr->type = Set_Endian (head_ptr->type);
	  head_ptr->hint = (msg->discriminator << 8) & 0x00ffff00;
	  head_ptr->hint = Set_Endian (head_ptr->hint);
	  head_ptr->num_groups = 1;
	  head_ptr->data_len = head_ptr->data_len;

	  if (MASTER)
	    {
	      strcpy (head_ptr->private_group_name, "#d-1-5-0#node1");
	    }
	  else
	    {
	      strcpy (head_ptr->private_group_name, "#d-2-5-0#node2");
	    }
	  memcpy (data, head_ptr, sizeof (message_header));
	  memcpy (bufUnixRecv, data, sizeof (message_header));

	  len = sizeof (message_header) + head_ptr->data_len + 32;

	  if ((msg->discriminator == DSM_MSG_LOCK_UNLOCK_TABLE)
	      && ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0) && (DONT_ALLOW == 0))
	    {
                      /*LOCK OR UNLOCK RECV FROM STACK in case of PEER GCS present*/
	      if (msg->u.lockUnlockTable.lockUnlockToggle)
		{
		  LOG_PRINT_MAJOR
		    ("FROMSTACK:PEERUP::STATE FLAG::LOCK TbId %d LockTid %d S %d M %d C %d state %d  Msgsize[%d]\n",
		     tableId, tid, Table_quee[tableId].Slave_Flg,
		     Table_quee[tableId].Master_Flg,
		     Table_quee[tableId].counter, Table_quee[tableId].state,head_ptr->data_len);
		}
	      else
		{
		  LOG_PRINT_MAJOR
		    ("FROMSTACK:PEERUP::STATE FLAG::UNLOCK TbId %d LockTid %d S %d M %d C %d state %d Msgsize[%d]\n",
		     tableId, tid, Table_quee[tableId].Slave_Flg,
		     Table_quee[tableId].Master_Flg,
		     Table_quee[tableId].counter, Table_quee[tableId].state,head_ptr->data_len);

		}
	      /*Processing of Double Stub Start */
	      if (msg->u.lockUnlockTable.lockUnlockToggle)
		{
                      /*LOCK RECV FROM STACK in case of PEER GCS present*/
		  Table_quee[tableId].Table_id = tableId;

		  if (((((MASTER == 1)
			 && (Table_quee[tableId].Master_Flg == 1))
			|| ((MASTER == 1)
			    && (Table_quee[tableId].Slave_Flg == 1)))
		       ||
		       (((MASTER == 0)
			 && (Table_quee[tableId].Slave_Flg == 1)))
		       || ((MASTER == 0)
			   && (Table_quee[tableId].Master_Flg == 1)))
		      && (Table_quee[tableId].counter > 0))
		    {
		      Table_quee[tableId].counter++;
		      if (Table_quee[tableId].state == 0)
			{
			  if (Table_quee[tableId].buf == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::I ist LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len = len;
			      Table_quee[tableId].buf = (char *) malloc (len);
			      memcpy (Table_quee[tableId].buf, bufUnixRecv,
				      len);
			    }
			  else if (Table_quee[tableId].buf_1 == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::II nd LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len_1 = len;
			      Table_quee[tableId].buf_1 =
				(char *) malloc (len);
			      memcpy (Table_quee[tableId].buf_1, bufUnixRecv,
				      len);
			    }
			  else if (Table_quee[tableId].buf_2 == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::III rd LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len_2 = len;
			      Table_quee[tableId].buf_2 =
				(char *) malloc (len);
			      memcpy (Table_quee[tableId].buf_2, bufUnixRecv,
				      len);
			    }
			  else if (Table_quee[tableId].buf_3 == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::IV th LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len_3 = len;
			      Table_quee[tableId].buf_3 =
				(char *) malloc (len);
			      memcpy (Table_quee[tableId].buf_3, bufUnixRecv,
				      len);
			    }
			  else if (Table_quee[tableId].buf_4 == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::V th LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len_4 = len;
			      Table_quee[tableId].buf_4 =
				(char *) malloc (len);
			      memcpy (Table_quee[tableId].buf_4, bufUnixRecv,
				      len);
			    }
			  else if (Table_quee[tableId].buf_5 == NULL)
			    {
			      LOG_PRINT_MAJOR
				("FROMSTACK:UNIX_Recv::VI th LOCK STORED TbId %d LockTid %d S %d M %d C %d state %d \n",
				 tableId, tid, Table_quee[tableId].Slave_Flg,
				 Table_quee[tableId].Master_Flg,
				 Table_quee[tableId].counter,
				 Table_quee[tableId].state);
			      Table_quee[tableId].Len_5 = len;
			      Table_quee[tableId].buf_5 =
				(char *) malloc (len);
			      memcpy (Table_quee[tableId].buf_5, bufUnixRecv,
				      len);
			    }
			}
		      else if (Table_quee[tableId].state == 1)
			{
                          /*Already have lock permission , so forwarding the msg to self and peer */
			  if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
			    {
			      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
			      if (ret_3 <= 0)
				{
				  LOG_PRINT_CRITICAL
				    ("TOGCS:UNIX_Recv: TcpClient send failed \n");
				 //close (TcpClient);
				 //TcpClient = 0;
        //   MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
                          /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
				 // continue;
				}
		//	      GCSUTIL_DEBUG_TRACE(("TOGCS:UNIX_Recv:: PeerGCSSend tid %d|len %d\n",tid,len));
			    }
			  ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
			  if (ret_3 <= 0)
			    {
			      LOG_PRINT_CRITICAL
				("TOSTACK:UNIX_Recv: UNIX_SMbox send failed \n");
			      close (UNIX_SMbox);
			      UNIX_SMbox = 0;
			      MUTEX_ReleaseMutex (&FlagLock);
		  pthread_exit (NULL);
			    }
                            if(ret_3 != len)
			    {
			      LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
			    }
		//	  GCSUTIL_DEBUG_TRACE(("TOSTACK:UNIX_Recv:: SelfSend tid %d|len %d\n",tid,len));

			}

		    }
		  else
		    {
		      Table_quee[tableId].counter++;
		      Table_quee[tableId].Len = len;
		      Table_quee[tableId].buf = (char *) malloc (len);
		      memcpy (Table_quee[tableId].buf, bufUnixRecv, len);
		      if (MASTER)
			{
			  Table_quee[tableId].Master_Flg = 1;
			  Table_quee[tableId].Slave_Flg = 0;
			  tokmsg.Master_Flg = 1;
			  tokmsg.Slave_Flg = 0;
			}
		      else
			{
			  Table_quee[tableId].Master_Flg = 0;
			  Table_quee[tableId].Slave_Flg = 1;
			  tokmsg.Master_Flg = 0;
			  tokmsg.Slave_Flg = 1;
			}
      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0) && (DONT_ALLOW == 0))
			{
			  tokmsg.Table_Id = tableId;
			  tokmsg.MsgId = REQUEST;
			  tokmsg.Tid = tid;
			  tokmsg.counter = Table_quee[tableId].counter;
			  tokmsg.ack = 0;
                           /*Sending LOCK REQUEST TO PEER GCS*/
			   LOG_PRINT_MAJOR("TOGCS:UNIX_Recv:: LOCK REQ TbId %d , M %d S %d C %d \n",tableId,tokmsg.Master_Flg,tokmsg.Slave_Flg,tokmsg.counter);

			  memcpy (UDP_buff, &tokmsg, sizeof (tokmsg));
			  ret = send (sockfd_udp_client,UDP_buff, sizeof (tokmsg), 0);
			  if (ret <= 0)
			    {
			      perror ("UNIX_Recv:LOCK REQ token send() failed ");
			      LOG_PRINT_CRITICAL
				("TOGCS:UNIX_Recv:: LOCK REQ token SEND TO PEER  failed");
			      /*if (sockfd_udp != 0)
		              {
	                        close (sockfd_udp);
                                sockfd_udp=0;
		              }
	              close (sockfd_udp_client);
                sockfd_udp_client = 0;*/
           MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
           MUTEX_AcquireMutex (&FlagLock);
				}
			}
		      else	/*TCP and UPD are not there */
			{
			  /*Towards GCS send */
			  if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0) && (DONT_ALLOW == 0))
			    {
			      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
			      if (ret_3 <= 0)
				{
			          LOG_PRINT_CRITICAL
				   ("TOGCS:UNIX_Recv:: TcpClient send failed\n");
				  //close (TcpClient);
				  //TcpClient = 0;
          // MUTEX_ReleaseMutex (&FlagLock);
                                  PEER_Leave();
                                /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
				 // continue;
				}
		//	      GCSUTIL_DEBUG_TRACE (("TOGCS:UNIX_Recv:: PeerGCSSend tid %d|len %d\n", tid, len));
			    }
			  ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
			  if (ret_3 <= 0)
			    {
			      perror ("UNIX_Recv:send() failed ");
			      LOG_PRINT_CRITICAL
				   ("TOSTACK:UNIX_Recv::UNIX_SMbox send failed\n");
			      close (UNIX_SMbox);
			      UNIX_SMbox = 0;
			      MUTEX_ReleaseMutex (&FlagLock);
		  pthread_exit (NULL);
			    }
                            if(ret_3 != len)
			    {
			       LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
			    }
		//	  GCSUTIL_DEBUG_TRACE (("TOSTACK :SelfSend tid %d|len %d\n", tid, len));

			}	/*TCP and UPD are not there */

		    }
		}
	      else		/*processing of Unlock message */
		{
		  /*Checking for lock ack flag , if set then process it as its is otherwise store it till we get the lock ack from peer stub */

		  if (Table_quee[tableId].Lock_Ack_Flag == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :I Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag = 0;

		    }
		  else if (Table_quee[tableId].Lock_Ack_Flag_1 == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :II Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag_1 = 0;
		    }
		  else if (Table_quee[tableId].Lock_Ack_Flag_2 == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :III Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag_2 = 0;
		    }
		  else if (Table_quee[tableId].Lock_Ack_Flag_3 == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :IV Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag_3 = 0;
		    }
		  else if (Table_quee[tableId].Lock_Ack_Flag_4 == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :V Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag_4 = 0;
		    }
		  else if (Table_quee[tableId].Lock_Ack_Flag_5 == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :VI Flag is set \n"));
		      Table_quee[tableId].Lock_Ack_Flag_5 = 0;
		    }
		  else
		    {
		      GCSUTIL_DEBUG_TRACE(("FROMSTACK:UNIX_Recv::NO LOCK ACK FLAG IS SET \n"));
		      if (Table_quee[tableId].unlockbuf_1 == NULL)
			{
			  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::I UNLOCK STORED \n");
			  Table_quee[tableId].unlockLen_1 = len;
			  Table_quee[tableId].unlockbuf_1 =
			    (char *) malloc (len);
			  memcpy (Table_quee[tableId].unlockbuf_1,
				  bufUnixRecv, len);
			  MUTEX_ReleaseMutex (&FlagLock);
			  continue;

			}
		      else if (Table_quee[tableId].unlockbuf_2 == NULL)
			{
			  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv::II UNLOCK STORED \n");
			  Table_quee[tableId].unlockLen_2 = len;
			  Table_quee[tableId].unlockbuf_2 =
			    (char *) malloc (len);
			  memcpy (Table_quee[tableId].unlockbuf_2,
				  bufUnixRecv, len);
			  MUTEX_ReleaseMutex (&FlagLock);
			  continue;

			}
		      else
			{
			  LOG_PRINT_CRITICAL
			    ("FROMSTACK:UNIX_Recv::MORE THAN TWO UNLOCK RECEIVED \n");
                          DeallocateGlobalbuffers();
			  abort ();	/*leaving as for time being, need to be take care in future */
			}

		    }
		  if (Table_quee[tableId].counter == 1)
		    {
		      //GCSUTIL_DEBUG_TRACE(("FROMSTACK :State Have change \n"));
		      Table_quee[tableId].state = 0;
		      /*this is due to storing of Lock until -ve Unlock have came */
		    }

		  if (Table_quee[tableId].un_1_flag == 0)
		    {
		      Table_quee[tableId].un_1_flag = 1;
		    }
		  else
		    {
		      if (Table_quee[tableId].un_2_flag == 0)
			{
			  Table_quee[tableId].un_2_flag = 1;
			}
		      else
			{
			  if (Table_quee[tableId].un_3_flag == 0)
			    {
			      Table_quee[tableId].un_3_flag = 1;
			    }
			  else
			    {
			      if (Table_quee[tableId].un_4_flag == 0)
				{
				  Table_quee[tableId].un_4_flag = 1;
				}
			      else
				{
				  LOG_PRINT_MAJOR
				    ("FROMSTACK:UNIX_Recv::More Than Expected  UNLOCK REC\n");
				}

			    }
			}
		    }

		  /*Towards GCS send */
		  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))&& (syncFlag == 0))
		    {
		      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
		      if (ret_3 <= 0)
			{
			  LOG_PRINT_CRITICAL
			    ("TOGCS:UNIX_Recv::TcpClientsend() failed ");
			  perror ("UNIX_Recv:TcpClientsend() failed ");
			  //close (TcpClient);
			  //TcpClient = 0;
			  //MUTEX_ReleaseMutex (&FlagLock);
                          PEER_Leave();
                                /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
			  //continue;
			}
		 //     GCSUTIL_DEBUG_TRACE(("TOGCS:UNIX_Recv::PeerGCSSendtid %d|len %d\n",tid,len));
		    }
		  ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL ("TOSTACK:UNIX_Recv::send() failed ");
		      perror ("UNIX_Recv:send() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      //MUTEX_ReleaseMutex (&FlagLock);
		  pthread_exit (NULL);
		      //continue;
		    }
                    if(ret_3 != len)
                    {
		        LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }
		  //GCSUTIL_DEBUG_TRACE(("TOSTACK:UNIX_Recv::SelfSend tid %d|len %d\n",tid,len));

#if 0
/***********************************************Change for Unlock Pending*****************************************/



		  if ((Table_quee[tableId].counter > 0) && (syncFlag == 0))
		    {
		      Table_quee[tableId].counter--;
		    }
		  //GCSUTIL_DEBUG_TRACE(("UNIX_SMbox:: Table_quee[tableId].counter %d\n",Table_quee[tableId].counter));
		  if (Table_quee[tableId].counter == 0)
		    {
		      tokmsg.MsgId = UNLOCK_REQUEST;
		      tokmsg.Table_Id = tableId;
		      if (Table_quee[tableId].Master_Flg == 1)
			{
			  Table_quee[tableId].Master_Flg = 0;
			  Table_quee[tableId].Slave_Flg = 1;
			  tokmsg.Master_Flg = 0;
			  tokmsg.Slave_Flg = 1;
			}
		      else if (Table_quee[tableId].Slave_Flg == 1)
			{
			  Table_quee[tableId].Master_Flg = 1;
			  Table_quee[tableId].Slave_Flg = 0;
			  tokmsg.Master_Flg = 1;
			  tokmsg.Slave_Flg = 0;
			}
		      else
			{
			  Table_quee[tableId].Master_Flg = 0;
			  Table_quee[tableId].Slave_Flg = 0;
			  tokmsg.Master_Flg = 0;
			  tokmsg.Slave_Flg = 0;
			}

		      Table_quee[tableId].counter++;
		      Table_quee[tableId].state = 0;
		      tokmsg.counter = Table_quee[tableId].counter;
		      bzero (&cliaddr, sizeof (cliaddr));
		      cliaddr.sin_family = AF_INET;
		      cliaddr.sin_addr.s_addr = inet_addr (CLIPEER_UDPADDR);
		      cliaddr.sin_port = htons (UDP_PORT);

		      memcpy (UDP_buff, &tokmsg, sizeof (tokmsg));
		      /*prepare the unlock Request message to peer Stub */
		      ret =
			sendto (sockfd_udp, UDP_buff, sizeof (token), 0,
				(struct sockaddr *) &cliaddr_udp,
				sizeof (cliaddr_udp));
		      if (ret <= 0)
			{
			  //GCSUTIL_DEBUG_TRACE(("sendto:"));
			  //GCSUTIL_DEBUG_TRACE(("ret[%d]",ret));
			  perror ("UNIX_Recv:sendto() failed ");
			}
		      /*send to peer UDP */
	/***********END***********/
		    }



/***********************************************Change for Unlock Pending*****************************************/
#endif
		}
	    }
	  else			/*processing of msg except lock and lock */
	    {
	      /*Processing of Single Stub Start */
	      if (msg->discriminator == DSM_MSG_LOCK_UNLOCK_TABLE)
		{
		  if (msg->u.lockUnlockTable.lockUnlockToggle)
		    {
		      LOG_PRINT_CRITICAL
			("FROMSTACK:STANDALONE::STATE FLAG::LOCK TbId %d LockTid %d S %d M %d C %d state %d Msgsize[%d]\n",
			 tableId, tid, Table_quee[tableId].Slave_Flg,
			 Table_quee[tableId].Master_Flg,
			 Table_quee[tableId].counter,
			 Table_quee[tableId].state,head_ptr->data_len);
		    }
		  else
		    {
		      LOG_PRINT_CRITICAL
			("FROMSTACK:STANDALONE::STATE FLAG::UNLOCK TbId %d LockTid %d S %d M %d C %d state %d Msgsize[%d]\n",
			 tableId, tid, Table_quee[tableId].Slave_Flg,
			 Table_quee[tableId].Master_Flg,
			 Table_quee[tableId].counter,
			 Table_quee[tableId].state,head_ptr->data_len);

		    }
		  if (msg->u.lockUnlockTable.lockUnlockToggle)
		    {
		      if (syncFlag != 2)	/*No need of setting the Flags in case of sync lock as LOCK ACK would update it accordingly through UDP interface */
			{
			  setLockAckFlagON (tableId);
			  Table_quee[tableId].Table_id = tableId;
			  Table_quee[tableId].counter++;
			  Table_quee[tableId].state = 1;
			  //      Table_quee[tableId].buf=NULL;
			  if (MASTER)
			    {
			      Table_quee[tableId].Master_Flg = 1;
			      Table_quee[tableId].Slave_Flg = 0;
			    }
			  else
			    {
			      Table_quee[tableId].Master_Flg = 0;
			      Table_quee[tableId].Slave_Flg = 1;
			    }
			}
		    }
		  else
		    {

		      if (syncFlag == 0 || syncFlag == 1)
			{
			  setLockAckFlagOFF (tableId);
			  if (Table_quee[tableId].counter > 0)
			    {
			      Table_quee[tableId].counter--;
			    }
			  if (Table_quee[tableId].counter == 0)
			    {
			      Table_quee[tableId].state = 0;
			      if (MASTER)
				{
				  Table_quee[tableId].Master_Flg = 0;
				}
			      else
				{
				  Table_quee[tableId].Slave_Flg = 0;

				}
			    }
			}
		    }

		  /*Towards GCS send */
		  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
		    {
		      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
		      if (ret_3 <= 0)
			{
			  LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv::TcpClientsend() failed ");
			  //close (TcpClient);
			  //TcpClient = 0;
			  //MUTEX_ReleaseMutex (&FlagLock);
                          PEER_Leave();
                          /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
			 // continue;
			}
		   //   GCSUTIL_DEBUG_TRACE(("TOGCS:UNIX_Recv::PeerGCSSend tid %d|len %d\n",tid,len));
		    }

		  ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL ("TOSTACK:UNIX_Recv:: send() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      MUTEX_ReleaseMutex (&FlagLock);
		  pthread_exit (NULL);
		      //continue;
		    }
                    if(ret_3 != len)
                    {
		           LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }
	//	  GCSUTIL_DEBUG_TRACE(("FROMSTACK:UNIX_Recv:: SelfSend tid %d|len %d\n",tid,len));
		  // else if(syncFlag == 2)
		  //  {
		  /*Need to store the Lock and Unlock message in case SYNC UNLOCK is not yet received */
		  //    StoreLockUnlock(tableId,bufUnixRecv,len,msg->u.lockUnlockTable.lockUnlockToggle);

		  // }


		}
	      else
		{
		  LOG_PRINT_CRITICAL("FROMSTACK:UNIX_Recv:: RECV MSGDISC [%d] tid [%d] tableId[%d] TcpClient[%d] DONT_ALLOW[%d] Msgsize[%d]\n",msg->discriminator,tid,tableId,TcpClient,DONT_ALLOW,head_ptr->data_len);


      if((msg->discriminator == DSM_MSG_SYNC_LOCK) || (msg->discriminator == DSM_MSG_SYNC_UNLOCK) || (msg->discriminator == DSM_MSG_SYNC_MEM_TCP))
      {
		  /*Towards GCS send */
		  if ((TcpClient > 0)&& (TcpServer > 0) )
		    {
		      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
		      if (ret_3 <= 0)
			{
			  LOG_PRINT_CRITICAL
			    ("TOGCS:UNIX_Recv::TcpClientsend() failed \n");
			  //close (TcpClient);
			  //TcpClient = 0;
			  //MUTEX_ReleaseMutex (&FlagLock);
                          PEER_Leave();
                          /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
			  //continue;
			}
	      LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv::Send MSG[%d] on TCP SOCKET to PEER STUB\n",msg->discriminator);
		    }
       else
        {
	         LOG_PRINT_CRITICAL("DISCARDING  MSG[%d] on TCP SOCKET to PEER STUB\n",msg->discriminator);
        }
     }
    else
     {
		  /*Towards GCS send */
		  if (((TcpClient > 0)&& (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (DONT_ALLOW==0))
		    {
		      ret_3 = send (TcpClient, bufUnixRecv, len, 0);
		      if (ret_3 <= 0)
			{
			  LOG_PRINT_CRITICAL
			    ("TOGCS:UNIX_Recv::TcpClientsend() failed \n");
			  //close (TcpClient);
			  //TcpClient = 0;
			  //MUTEX_ReleaseMutex (&FlagLock);
                          PEER_Leave();
                          /*Removing continue as otherwise the msg will not be send to self stack in case if tcp send fails.*/
			  //continue;
			}
	//      LOG_PRINT_CRITICAL("TOGCS:UNIX_Recv::Send MSG[%d] tid [%d] on TCP SOCKET to PEER STUB\n",msg->discriminator,tid);
		    }
       else
        {
	         LOG_PRINT_CRITICAL("DISCARDING  MSG[%d] tid [%d] on TCP SOCKET to PEER STUB\n",msg->discriminator,tid);

        } 

      }

		  ret_3 = send (UNIX_SMbox, bufUnixRecv, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL ("5.UNIX_Recv:send() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      MUTEX_ReleaseMutex (&FlagLock);
		       pthread_exit (NULL);
		    }
                    if(ret_3 != len)
                    {
		            LOG_PRINT_CRITICAL("UNIX_Recv: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                    }
	//	    GCSUTIL_DEBUG_TRACE(("TOSTACK:UNIX_Recv::SelfSend tid %d|len %d\n",tid,len));
		}
	    }

	}/*elseif for SAFE */
       else
       {
	   LOG_PRINT_CRITICAL("------------------------------------------------------------------------\n");
	   LOG_PRINT_CRITICAL("ERROR:MESSAGE DISCARDED:UNKOWN DATA:head_ptr->type[%x]\n",head_ptr->type);
	   LOG_PRINT_CRITICAL("ERROR:MESSAGE DISCARDED:UNKOWN DATA\n");
	   LOG_PRINT_CRITICAL("ERROR:MESSAGE DISCARDED:UNKOWN DATA\n");
	   LOG_PRINT_CRITICAL("ERROR:MESSAGE DISCARDED:UNKOWN DATA\n");
	   LOG_PRINT_CRITICAL("------------------------------------------------------------------------\n");
       }
      MUTEX_ReleaseMutex (&FlagLock);
    }/*endof while */

	  LOG_PRINT_CRITICAL ("ALERT ::::: UNIX EXITING---------------------\n");

}
void
ResetAllFlags_OnUnixBreak ()
{
  unsigned int tableId = 0;

  MUTEX_AcquireMutex (&FlagLock);
  //GCSUTIL_DEBUG_TRACE( ("ResetAllFlags_OnUnixBreak:MUTEX ACQUIRE SUCCESS\n"));
  for (tableId = 0; tableId < 50; tableId++)
    {
      if (MASTER)
	{
	  if (Table_quee[tableId].Master_Flg == 1)
	    {
	      //GCSUTIL_DEBUG_TRACE( ("ResetAllFlags_OnUnixBreak:: RESET ALL FLAG FOR MASTER TABLE %d COUNTER %d\n",tableId,Table_quee[tableId].counter));
	      Table_quee[tableId].buf = NULL;
	      Table_quee[tableId].buf_1 = NULL;
	      Table_quee[tableId].buf_2 = NULL;
	      Table_quee[tableId].buf_3 = NULL;
	      Table_quee[tableId].buf_4 = NULL;
	      Table_quee[tableId].buf_5 = NULL;
	      Table_quee[tableId].Table_id = 0;
	      Table_quee[tableId].Master_Flg = 0;
	      Table_quee[tableId].Slave_Flg = 0;
	      Table_quee[tableId].counter = 0;
	      Table_quee[tableId].state = 0;
	      Table_quee[tableId].Len = 0;
	      Table_quee[tableId].Len_1 = 0;
	      Table_quee[tableId].Len_2 = 0;
	      Table_quee[tableId].Len_3 = 0;
	      Table_quee[tableId].Len_4 = 0;
	      Table_quee[tableId].Len_5 = 0;
	      Table_quee[tableId].Lock_Ack_Flag = 0;
	      Table_quee[tableId].Lock_Ack_Flag_1 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_2 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_3 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_4 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_5 = 0;
	      Table_quee[tableId].unlockbuf_1 = NULL;
	      Table_quee[tableId].unlockbuf_2 = NULL;
	      Table_quee[tableId].unlockLen_1 = 0;
	      Table_quee[tableId].unlockLen_2 = 0;
	    }

	}
      else
	{
	  if (Table_quee[tableId].Slave_Flg == 1)
	    {
	      //GCSUTIL_DEBUG_TRACE( ("ResetAllFlags_OnUnixBreak:: RESET ALL FLAG FOR SLAVE TABLE %d COUNTER %d\n",tableId,Table_quee[tableId].counter));
	      Table_quee[tableId].buf = NULL;
	      Table_quee[tableId].buf_1 = NULL;
	      Table_quee[tableId].buf_2 = NULL;
	      Table_quee[tableId].buf_3 = NULL;
	      Table_quee[tableId].buf_4 = NULL;
	      Table_quee[tableId].buf_5 = NULL;
	      Table_quee[tableId].Table_id = 0;
	      Table_quee[tableId].Master_Flg = 0;
	      Table_quee[tableId].Slave_Flg = 0;
	      Table_quee[tableId].counter = 0;
	      Table_quee[tableId].state = 0;
	      Table_quee[tableId].Len = 0;
	      Table_quee[tableId].Len_1 = 0;
	      Table_quee[tableId].Len_2 = 0;
	      Table_quee[tableId].Len_3 = 0;
	      Table_quee[tableId].Len_4 = 0;
	      Table_quee[tableId].Len_5 = 0;
	      Table_quee[tableId].Lock_Ack_Flag = 0;
	      Table_quee[tableId].Lock_Ack_Flag_1 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_2 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_3 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_4 = 0;
	      Table_quee[tableId].Lock_Ack_Flag_5 = 0;
	      Table_quee[tableId].unlockbuf_1 = NULL;
	      Table_quee[tableId].unlockbuf_2 = NULL;
	      Table_quee[tableId].unlockLen_1 = 0;
	      Table_quee[tableId].unlockLen_2 = 0;

	    }
	}
    }
  //GCSUTIL_DEBUG_TRACE( ("ResetAllFlags_OnUnixBreak::MUTEX RELEASED SUCCESS\n"));
  MUTEX_ReleaseMutex (&FlagLock);


}


void
StoreLockUnlock (int tableId, char *bufUnixRecv, int len, int LockUnlockFlag)
{
  if (LockUnlockFlag)
    {
      //GCSUTIL_DEBUG_TRACE( ("FROMSTACK :: StoreLockUnlock:: LOCK MESSAGE STORED\n"));
      /*Storing Lock message */
      if (Table_quee[tableId].buf == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::I ist Lock "));
	  Table_quee[tableId].Len = len;
	  Table_quee[tableId].buf = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf, bufUnixRecv, len);
	}
      else if (Table_quee[tableId].buf_1 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::II ist Lock "));
	  Table_quee[tableId].Len_1 = len;
	  Table_quee[tableId].buf_1 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf_1, bufUnixRecv, len);
	}
      else if (Table_quee[tableId].buf_2 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::III nd Lock "));
	  Table_quee[tableId].Len_2 = len;
	  Table_quee[tableId].buf_2 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf_2, bufUnixRecv, len);
	}
      else if (Table_quee[tableId].buf_3 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::IV rd Lock "));
	  Table_quee[tableId].Len_3 = len;
	  Table_quee[tableId].buf_3 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf_3, bufUnixRecv, len);
	}
      else if (Table_quee[tableId].buf_4 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::V th LOck "));
	  Table_quee[tableId].Len_4 = len;
	  Table_quee[tableId].buf_4 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf_4, bufUnixRecv, len);
	}
      else if (Table_quee[tableId].buf_5 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK ::VI th LOck "));
	  Table_quee[tableId].Len_5 = len;
	  Table_quee[tableId].buf_5 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].buf_5, bufUnixRecv, len);
	}
    }
  else
    {
      /*Storing unLock message */
      GCSUTIL_DEBUG_TRACE (("FROMSTACK :: StoreLockUnlock:: UNLOCK MESSAGE STORED\n"));
      LOG_PRINT_MAJOR
	("FROMSTACK :: StoreLockUnlock:: UNLOCK MESSAGE STORED\n");
      if (Table_quee[tableId].unlockbuf_1 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK :I UNLOCK STORED \n"));
	  Table_quee[tableId].unlockLen_1 = len;
	  Table_quee[tableId].unlockbuf_1 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].unlockbuf_1, bufUnixRecv, len);

	}
      else if (Table_quee[tableId].unlockbuf_2 == NULL)
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK :II UNLOCK STORED \n"));
	  Table_quee[tableId].unlockLen_2 = len;
	  Table_quee[tableId].unlockbuf_2 = (char *) malloc (len);
	  memcpy (Table_quee[tableId].unlockbuf_2, bufUnixRecv, len);

	}
      else
	{
	  //GCSUTIL_DEBUG_TRACE(("FROMSTACK :MORE THAN TWO UNLOCK RECEIVED \n"));
	  LOG_PRINT_CRITICAL ("FROMSTACK :MORE THAN TWO UNLOCK RECEIVED \n");
          DeallocateGlobalbuffers();
	  abort ();		/*leaving as for time being, need to be take care in future */
	}

    }

}
pthread_t TcpRecvThread = 0;
//int tcp_listener;
void *
TCP_Server (void *args)
{
  fd_set master;
  fd_set read_fds;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
//  int listener;
  int newfd;
  int yes = 1;
  //int addrlen;
  socklen_t addrlen;
	int ret = 0;


  /* clear the master and temp sets */
  FD_ZERO (&master);
  FD_ZERO (&read_fds);
  /* get the listener */
  LOG_PRINT_CRITICAL ("ALERT ::::: TCP SERVER THREAD INVOKE \n");
  if ((tcp_listener = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("TCP_Server:socket() failed \n");
      LOG_PRINT_CRITICAL ("TCP_Server:socket() failed ");
      LOG_PRINT_CRITICAL ("TCP_Server Thread EXIT \n");
      exit (1);
    }
  //GCSUTIL_DEBUG_TRACE( ("Server-socket() is OK...\n"));
  /*"address already in use" error message */
  if (setsockopt (tcp_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) ==
      -1)
    {
      LOG_PRINT_CRITICAL ("TCP_Server:setsockopt() failed \n");
      perror ("TCP_Server:setsockopt() failed ");
      LOG_PRINT_CRITICAL ("TCP_Server Thread EXIT \n");
      exit (1);
    }
  //GCSUTIL_DEBUG_TRACE( ("Server-setsockopt() is OK...\n"));
  //SocketOption (tcp_listener);
  //SetKeepAliveOption(tcp_listener);
  /* bind */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons (TCP_PORT);
  memset (&(serveraddr.sin_zero), '\0', 8);
  if (bind (tcp_listener, (struct sockaddr *) &serveraddr, sizeof (serveraddr)) ==
      -1)
    {
      perror ("TCP_Server:bind() failed \n");
      LOG_PRINT_CRITICAL ("TCP_Server:bind() failed \n");
      LOG_PRINT_CRITICAL ("TCP_Server Thread EXIT \n");
      exit (1);
    }
  //GCSUTIL_DEBUG_TRACE( ("Server-bind() is OK...\n"));
  SocketOption (tcp_listener);
  SetKeepAliveOption(tcp_listener);
  /* listen */
  if (listen (tcp_listener, 10) == -1)
    {
      perror ("TCP_Server:Server-listen() failed ");
      LOG_PRINT_CRITICAL ("TCP_Server:Server-listen() failed \n ");
      // exit(1);
    }
  //GCSUTIL_DEBUG_TRACE( ("Server-listen() is OK...\n"));
  /* add the listener to the master set */
  GetSocketOption(tcp_listener);
  while (1)
	{
					if(tcp_listener == 0)
					{
									LOG_PRINT_CRITICAL ("TCP_Server thread:Exit\n");
									break;
					}      
          if(LEAVE_PEER == 1)
          {
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###TCP_Server:Sleep for 5 sec########...\n",LEAVE_PEER);
            sleep(5);
            LEAVE_PEER = 0;
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###TCP_Server:After Sleep for 5 sec########...\n",LEAVE_PEER);
          }
					if ((newfd =
																	accept (tcp_listener, (struct sockaddr *) &clientaddr,
																					&addrlen)) == -1)
					{
									perror ("TCP_Server:Server-accept() failed ");
									LOG_PRINT_CRITICAL ("TCP_Server:Server-accept() failed \n");
					}
					else
					{
				LOG_PRINT_CRITICAL ("TCP Server Connection ACCEPTED LEAVE_PEER[%d] \n", LEAVE_PEER);
									if(newfd == 0)
									{
													LOG_PRINT_CRITICAL ("ALERT :::::: ZERO TCP FD %d \n", TcpServer);
													close(newfd);
                          continue;
									}
									TcpServer = newfd;
									LOG_PRINT_CRITICAL ("SocketUP :: TCP SERVER ACCEPT SUCCESS NewFd[%d] \n", TcpServer);
#if 0
									pthread_create (&TcpRecvThread, NULL, TCPRECV_Server, NULL);
#endif
									while(1)
								  {
									   ret = TCPRECV_Server();
									   if(ret < 0)
									   {
                        LOG_PRINT_CRITICAL ("TCP_Server : TCPRECV_Server failed , waiting for accept again \n");
												break;
									   }
									}


					}
         sleep(1);

	}

  return 0;
}

int TCPRECV_Server ()
{
 // unsigned char bufTCPRecv[MAX_MESSAGE_SIZE];
//  unsigned char buffTCPSend[MAX_MESSAGE_SIZE];
  unsigned int tid = 0;
  int nbytes = 0;
  unsigned int len = 0, i = 0, remain = 0;
  int ret_3 = 0;
  message_header head_ptr;
  DSM_Message *msg = NULL;
  int tableId = 0, ret = 0;
  token lockAcktoken;
  char UDP_buff[50];
  struct sockaddr_in cliaddr;
  LOG_PRINT_CRITICAL ("ALERT ::::  TCP RECV FUNCTION INVOKE \n");

  while (1)
    {
      memset (bufTCPRecv, 0, MAX_MESSAGE_SIZE);
  //    memset (buffTCPSend, 0, MAX_MESSAGE_SIZE);
      len = 80;
      for (i = 0, remain = len; remain > 0; i += nbytes, remain -= nbytes)
	{

	  if ((nbytes = recv (TcpServer, &bufTCPRecv[i], remain, 0)) <= 0)
	    {
        DONT_ALLOW=1;
	     /* close (TcpServer);
	      if(TcpClient != 0)
              {
	        close (TcpClient);
	        TcpClient = 0;
	      }
	      TcpServer = 0;*/
	      LOG_PRINT_CRITICAL ("Header:ERRNO[%d] DONT_ALLOW %d \n", errno,DONT_ALLOW);
	      LOG_PRINT_CRITICAL ("Header:recv ERROR nbytes[%d]\n", nbytes);
	      LOG_PRINT_CRITICAL("TCPRECV_Server: recv() failed ");
	      MUTEX_AcquireMutex (&FlagLock);
	      if (syncFlag == 2)
		{
		  MessageRetrieve_ON_SYNC_TCP_break ();
		  syncFlag = 1;
		  LOG_PRINT_CRITICAL
		    ("FROMGCS :TCPRECV_Server setting syncFlag to 1 as TCP break before SYNC  UNLOCK :: syncFlag[%d]\n",syncFlag);
		}
	      else
		{
		  syncFlag = 1;
		  LOG_PRINT_CRITICAL("FROMGCS :TCPRECV_Server setting syncFlag to 1 as TCP break :: syncFlag[%d]\n",syncFlag);
		  MessageRetFromLockque ();
		}
            
	      MUTEX_ReleaseMutex (&FlagLock);
              if(TcpRecvThread != 0)
              {
                TcpRecvThread = 0;
              }
              PEER_Leave();
              //LOG_PRINT_CRITICAL ("TCPRECV_Server:: CANCEL THREAD TcpServerthread \n");
              //pthread_exit(NULL);
		          return FAILURE;
	    }
	}

      memcpy (&head_ptr, bufTCPRecv, 48);
   //   memcpy (buffTCPSend, bufTCPRecv, len);
    //  memset (bufTCPRecv, 0, MAX_MESSAGE_SIZE);
      len = head_ptr.data_len;
					if((Clear_Endian (head_ptr.type)) == 0x00001100)
					{
							len = 32 + 56;
              LOG_PRINT_CRITICAL ("TCPRECV_Server::MEMBERSHIP JOIN MSG RECV FROM PEER:LEAVE_EVENT_SEND[%d] \n",LEAVE_EVENT_SEND);
              LEAVE_EVENT_SEND = 0;
              LOG_PRINT_CRITICAL ("TCPRECV_Server:: LEAVE_EVENT_SEND[%d] is set to zero\n",LEAVE_EVENT_SEND);
					}
      for (i = 80, remain = len; remain > 0; i += nbytes, remain -= nbytes)
	{

	  if ((nbytes = recv (TcpServer, &bufTCPRecv[i], remain, 0)) <= 0)
	    {
        DONT_ALLOW=1;
	      LOG_PRINT_CRITICAL ("TCPRECV_Server:Data:ERRNO[%d] DONT_ALLOW %d\n", errno,DONT_ALLOW);
	      LOG_PRINT_CRITICAL
		("TCPRECV_Server:Data:recv ERROR nbytes[%d]\n", nbytes);
	      perror ("TCPRECV_Server: recv() failed ");

	      MUTEX_AcquireMutex (&FlagLock);
	      if (syncFlag == 2)
		{
		  MessageRetrieve_ON_SYNC_TCP_break ();
		  syncFlag = 1;
		}
	      else
		{
		  syncFlag = 1;
		  LOG_PRINT_CRITICAL("FROMGCS :TCPRECV_Server setting syncFlag to 1 as TCP break :: syncFlag[%d]\n",syncFlag);
		  MessageRetFromLockque ();
		}
	      MUTEX_ReleaseMutex (&FlagLock);
	      /*close (TcpServer);
	      if(TcpClient != 0)
	      {
	        close (TcpClient);
	        TcpClient = 0;
	      }	
	      TcpServer = 0;*/  
              if(TcpRecvThread != 0)
              {
                TcpRecvThread = 0;
              }
              PEER_Leave();
              //LOG_PRINT_CRITICAL ("TCPRECV_Server:: CANCEL THREAD TcpServerthread \n");
              //pthread_exit(NULL);
		          return FAILURE;
	    }
	}
      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0)
                  && (sockfd_udp_client > 0) && (PEER_ALRD_JOIN == 1))
     { 

      MUTEX_AcquireMutex (&FlagLock);
      /*change due to mutex acquire other than this thread and that condition might change the sync flag to 2. */
//			memcpy (&buffTCPSend[80], bufTCPRecv, len);
 //     msg = (DSM_Message *) & buffTCPSend[80];
       msg = (DSM_Message *) & bufTCPRecv[80];
      print_tid (msg);
      if (msg->discriminator == DSM_MSG_SYNC_LOCK)
	{
    DONT_ALLOW=0;
	  syncFlag = 2;
	  LOG_PRINT_MAJOR
	    ("FROMGCS:TCPRECV_Server::SYNC_LOCK RECV AT TCP FROM PEER syncFlag [%d]\n",
	     syncFlag);
	}
      else if (msg->discriminator == DSM_MSG_SYNC_UNLOCK)
	{
	  syncFlag = 0;
	  LOG_PRINT_MAJOR
	    ("FROMGCS:TCPRECV_Server::SYNC_UNLOCK RECV AT TCP FROM PEER :Updating syncFlag %d\n",
	     syncFlag);
	}
        else if (msg->discriminator == DSM_MSG_JOIN_INFO)
	{
	  LOG_PRINT_MAJOR
	    ("FROMGCS:TCPRECV_Server::JOIN_INFO RECV AT TCP FROM PEER :nbytes %d\n",
	     nbytes);
	}
      if (UNIX_SMbox > 0)
	{
	len = len + 80;
//	  ret_3 = send (UNIX_SMbox, buffTCPSend, len, 0);
	  ret_3 = send (UNIX_SMbox, bufTCPRecv, len, 0);
	  if (ret_3 <= 0)
	    {
	      LOG_PRINT_CRITICAL ("TCPRECV_Server:unix send failed \n");
	      LOG_PRINT_CRITICAL
		("TCPRECV_Server: unix send failed :aborting\n");
	      close (UNIX_SMbox);
	      UNIX_SMbox = 0;
	      MUTEX_ReleaseMutex (&FlagLock);
        TcpRecvThread = 0;
        pthread_exit(NULL);
	      GCSUTIL_DEBUG_TRACE (("TCPRECV_Server: unix send failed :aborting\n"));
	      GCSUTIL_DEBUG_TRACE (("TCPRECV_Server: unix send failed :aborting\n"));
	      GCSUTIL_DEBUG_TRACE (("TCPRECV_Server: unix send failed :aborting\n"));
              DeallocateGlobalbuffers();
	      abort ();
	    }
            if(ret_3 != len)
	    {
	        LOG_PRINT_CRITICAL("TCPRECV_Server: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
	    }
//	 LOG_PRINT_CRITICAL("SEND MESSAGE SUCCESSFULLY: Msg type[%d] TO SELF NWSTACK \n",msg->discriminator);
	}
/*Patch:2-june-10:Sending lock msg stored during sync procedure , after sending SYNC UNLOCK to stack first on unix*/
      if (msg->discriminator == DSM_MSG_SYNC_UNLOCK)
	{
	  LOG_PRINT_MAJOR
	    ("FROMGCS:TCPRECV_Server::SYNC_UNLOCK : Check for sending any stored lock msg: syncFlag %d\n",
	     syncFlag);
	  MessageRetFromLockque_Sync ();
	}
      if ((msg->discriminator == DSM_MSG_LOCK_UNLOCK_TABLE)
	  && (msg->u.lockUnlockTable.lockUnlockToggle))
	{
	  tableId = msg->u.lockUnlockTable.tableId;
	  if ((Table_quee[tableId].Slave_Flg == 0)
	      && (Table_quee[tableId].Master_Flg == 0)
	      && (Table_quee[tableId].counter == 0))
	    {
	      Table_quee[tableId].counter++;
	      if (MASTER == 1)
		{
		  Table_quee[tableId].Slave_Flg = 1;
		}
	      else if (MASTER == 0)
		{
		  Table_quee[tableId].Master_Flg = 1;
		}

	      GCSUTIL_DEBUG_TRACE (("TCPRECV_Server::UPDATING COUNTER[%d] FOR FIRST LOCK RECEIVED ON TCP AFTER IDEAL CONDITION", Table_quee[tableId].counter));
	    }

	}
      /*Sending Lock Ack for lock message received from Peer TCP */
      if ((msg->discriminator == DSM_MSG_LOCK_UNLOCK_TABLE))
	{
	  tableId = msg->u.lockUnlockTable.tableId;
	  tid = msg->u.lockUnlockTable.tid;
	  lockAcktoken.Table_Id = tableId;
	  bzero (&cliaddr, sizeof (cliaddr));
	  cliaddr.sin_family = AF_INET;
	  cliaddr.sin_addr.s_addr = inet_addr (CLIPEER_UDPADDR);
	  cliaddr.sin_port = htons (UDP_PORT);
	  memset (UDP_buff, 0, 50);
	  lockAcktoken.Tid = tid;
	  if (msg->u.lockUnlockTable.lockUnlockToggle)
	    {
	      lockAcktoken.MsgId = LOCK_ACK;
	      memcpy (UDP_buff, &lockAcktoken, sizeof (token));
			  ret = send (sockfd_udp_client, UDP_buff, sizeof (token), 0);
	      if (ret <= 0)
		{
		  LOG_PRINT_CRITICAL ("TCPRECV_Server::LOCK ACK token send to GCS failed \n");
		  GCSUTIL_DEBUG_TRACE (("TCPRECV_Server::ret[%d]", ret));

/*		                                                if(sockfd_udp != 0)
								{
								close (sockfd_udp);
								sockfd_udp=0;
								}
								close (sockfd_udp_client);
								sockfd_udp_client = 0;
*/
                  MUTEX_ReleaseMutex (&FlagLock);
                  if(TcpRecvThread != 0)
                  {
                     TcpRecvThread = 0;
                  }
                  PEER_Leave();
                  //LOG_PRINT_CRITICAL ("TCPRECV_Server:: CANCEL THREAD TcpServerthread \n");
                  //pthread_exit(NULL);
          		   return FAILURE;
				}
	 else
		{
	      //     GCSUTIL_DEBUG_TRACE(("TOGCS:TCPRECV_Server:Send LOCK ACK for TableId[%d] \n",tableId));
		}
	    }
	  else
	    {
	      lockAcktoken.MsgId = UNLOCK_ACK;
	      memcpy (UDP_buff, &lockAcktoken, sizeof (token));
			  ret = send (sockfd_udp_client, UDP_buff, sizeof (token), 0);
	      if (ret <= 0)
		{
		  LOG_PRINT_CRITICAL ("TCPRECV_Server::UNLOCK ACK UDP sendto: Fail");
		  GCSUTIL_DEBUG_TRACE (("TCPRECV_Server::ret[%d]", ret));
/*		                                                if(sockfd_udp != 0)
								{
								close (sockfd_udp);
								sockfd_udp=0;
								}
								close (sockfd_udp_client);
								sockfd_udp_client = 0;
*/
                  MUTEX_ReleaseMutex (&FlagLock);
                  if(TcpRecvThread != 0)
                  {
                     TcpRecvThread = 0;
                  }
                  PEER_Leave();
                 // LOG_PRINT_CRITICAL ("TCPRECV_Server:: CANCEL THREAD TcpServerthread \n");
                 // pthread_exit(NULL);
          		    return FAILURE;
				}
	      else
		{
	      //GCSUTIL_DEBUG_TRACE(("TOGCS:TCPRECV_Server:Send UNLOCK ACK for TableId[%d] \n",tableId));
		}
	    }
	}


      MUTEX_ReleaseMutex (&FlagLock);
     }
    }
    return FAILURE;
}

void *
Tcp_Client (void *args)
{
  int sockfd = 0;
  int ret = 0;
  int yes = 1;
  struct sockaddr_in their_addr;
  struct timespec req;
  int TcpClientConnectOk = 0;
#if 0
  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Tcp_Client:socket() failed ");
      exit (1);
    }
  else
    {
      //GCSUTIL_DEBUG_TRACE( ("Client-The socket() sockfd is OK...\n"));
    }
  /*"address already in use" error message */
  if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
    {
      //GCSUTIL_DEBUG_TRACE( ("Tcp_Client:-setsockopt() error lol!"));
      perror ("Tcp_Client::setsockopt() failed ");
    }
  //GCSUTIL_DEBUG_TRACE( ("Server-setsockopt() is OK...\n"));
  //SocketOption (sockfd);
  // host byte order
  their_addr.sin_family = AF_INET;
  // short, network byte order
  their_addr.sin_port = htons (TCP_PORT);
  their_addr.sin_addr.s_addr = inet_addr (TCPPEER_IP);
  // zero the rest of the struct
  memset (&(their_addr.sin_zero), '\0', 8);
#endif
  LOG_PRINT_CRITICAL ("ALERT ::::: TCP CLIENT THREAD INVOKE \n");
  while (1)
    {
  //    LOG_PRINT_CRITICAL ("TCP CLIENT PROCEDURE INVOKE ::TcpClient[%d]\n",TcpClient);
      if(TcpClient == 0)
      {
				if(CLIENT_RETRY_FLAG == 1)
				{	
				 LOG_PRINT_CRITICAL ("TCP_Client: Sleeping for 30sec before connecting .......\n");
				 sleep(30);
				 CLIENT_RETRY_FLAG = 0;
				} 
	  if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
	    {
	      LOG_PRINT_CRITICAL ("Tcp_Client:socket() failed \n");
	      perror ("Tcp_Client:socket() failed ");
      LOG_PRINT_CRITICAL ("TCP_Client Thread EXIT \n");
	      exit (1);
	    }
	  else
	    {
	      //GCSUTIL_DEBUG_TRACE( ("Client-The socket() sockfd is OK...\n"));
				LOG_PRINT_CRITICAL ("Tcp_Client:SOCKET OPEN for TCP_CLIENT Fd[%d] \n",sockfd);
	    }
	  /*"address already in use" error message */
	  if (setsockopt
	      (sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
	    {
	      LOG_PRINT_CRITICAL ("Tcp_Client:-setsockopt() error lol! \n");
	      //GCSUTIL_DEBUG_TRACE( ("Tcp_Client:-setsockopt() error lol!"));
	      perror ("Tcp_Client::setsockopt() failed ");
	    }
	  //GCSUTIL_DEBUG_TRACE( ("Server-setsockopt() is OK...\n"));
	    SocketOption (sockfd);
      SetKeepAliveOption(sockfd);
	    TcpClient = sockfd;
	  TcpClientConnectOk = 0;
      }
      /*if ((TcpClientConnectOk == 0) && (LEAVE_PEER == 0)) 29-Jan-2015 */
      if (TcpClientConnectOk == 0)
	{
	  // host byte order
	  their_addr.sin_family = AF_INET;
	  // short, network byte order
	  their_addr.sin_port = htons (TCP_PORT);
	  their_addr.sin_addr.s_addr = inet_addr (TCPPEER_IP);
	  // zero the rest of the struct
	  memset (&(their_addr.sin_zero), '\0', 8);
	      LOG_PRINT_CRITICAL ("Tcp_Client:Trying for connect() Again  \n");
	  if ((ret =
	       connect (sockfd, (struct sockaddr *) &their_addr,
			sizeof (struct sockaddr))) == -1)
	    {
	      LOG_PRINT_CRITICAL ("Tcp_Client:connect() failed  \n");
	      perror ("Tcp_Client:connect() failed ");
	      //LOG_PRINT_CRITICAL ("Tcp_Client:connect() failed : CLOSING FD[%d] \n",sockfd);
	      //close (sockfd);
	    }
	  else
	    { 
	      TcpClientConnectOk = 1;
              GetSocketOption(tcp_listener);
//	      LOG_PRINT_CRITICAL("TCP Client-The connect() is OK...\n");
              LOG_PRINT_CRITICAL ("SocketUP :: TCP CLIENT CONNECT SUCCESS NewFd[%d]\n",TcpClient);
											PEER_ALRD_JOIN=1;
	      LOG_PRINT_CRITICAL("####SETTING PEER_ALRD_JOIN[%d]###########...\n",PEER_ALRD_JOIN);
	    }
	}
      //sleep (5);
      if(TcpClient == 0)
      {
          if(LEAVE_PEER == 1)
          {
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###TCP_Client:Sleep for 5 sec########...\n",LEAVE_PEER);
            sleep(5);
            LEAVE_PEER = 0;
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###TCP_Client:After Sleep for 5 sec########...\n",LEAVE_PEER);
          }
          else
          {
          req.tv_sec=0;
          req.tv_nsec=200000000;
          pselect(FD_SETSIZE,0,0,0,&req,NULL);
          }
      }
      else
      {
           sleep(1);
      }
    }
	      LOG_PRINT_CRITICAL("ALERT ::::: TCP CLIENT EXITING \n");
  return 0;
}

int UDP_Function ()
{
  char bufRecv[100];
  char mesg[100];
  int nbytes = 0;
  unsigned int len = 0 ;
  LOG_PRINT_CRITICAL ("ALERT ::::  UDP RECV FUNCTION INVOKE \n");
  for (;;)
    {
      memset (mesg, 0, sizeof (mesg));

      len = sizeof(token);
							if ((nbytes = recv (sockfd_udp, bufRecv, len, 0)) <= 0)
							{
											LOG_PRINT_CRITICAL ("Header:ERRNO[%d]\n", errno);
											LOG_PRINT_CRITICAL ("Header:recv ERROR nbytes[%d]\n", nbytes);
											LOG_PRINT_CRITICAL ("UDP_Function: recv() failed ");
	                 /*   close (sockfd_udp);
			    if(sockfd_udp_client != 0)
			    {
	                    close (sockfd_udp_client);
                            sockfd_udp_client = 0;
			    }
                      sockfd_udp=0;*/
		                //LOG_PRINT_CRITICAL("FROMGCS :UDP_Function setting syncFlag to 1 as TCP break :: syncFlag[%d]\n",syncFlag);
		               // syncFlag = 1; /* This done in Peer_leave */
                    DONT_ALLOW = 1;
                    if(UDPRecvThread != 0)
                    {
                       UDPRecvThread = 0;
                    } 
                    PEER_Leave();
                    //LOG_PRINT_CRITICAL("UDP_Function : CANCELLED UDP RECV THREAD \n");
                    //pthread_exit(NULL);
	            return FAILURE;
       
                      

							}

							if (nbytes < sizeof (token))
							{
											LOG_PRINT_CRITICAL
															("UDP_Function:recvfrom() shorter bytes received \n");
											LOG_PRINT_CRITICAL
															("UDP_Function:recvfrom() shorter bytes received \n");
							}

       memcpy(mesg,bufRecv,sizeof(token));
      MUTEX_AcquireMutex (&FlagLock);
      if((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
       {
        SendResponse ((token *) mesg);
       }
      else
       {
					LOG_PRINT_CRITICAL
															("UDP_Function:recvfrom() NULL %d \n",sockfd_udp_client);

       } 
      MUTEX_ReleaseMutex (&FlagLock);
    }
	 return FAILURE;
}

void
SendResponse (token * tok_ptr)
{
  token resp_tok;
  token updtCnt;
  char mesg[100];
  //int snt_byt = 0;
  unsigned Table_Id = 0;
  token tokmsg;
  char UDP_buff[50];
  struct sockaddr_in cliaddr;
  int ret = 0;

  if ((OldtokTid == tok_ptr->Tid) && (OldtokTid != 0)
      && (OldtokMsgId == tok_ptr->MsgId) && (OldtokMsgId != 0))
    {
      LOG_PRINT_CRITICAL
	("FROMGCS:SendResponse::ERROR Duplicate Token for MsgTID[%d] TbId[%d] \n",
	 tok_ptr->Tid,tok_ptr->Table_Id);
      return;
    }
  else
    {
      OldtokTid = tok_ptr->Tid;
      OldtokMsgId = tok_ptr->MsgId;
    }

  /* Changed required for Exclusive mutex as this can be used by the unix too */
  if (tok_ptr->Table_Id > 50)
    {
      LOG_PRINT_CRITICAL("FROMGCS:SendResponse::ERROR Invalid Table ID[%d] Recvied\n",tok_ptr->Table_Id);
      return;
    }
  else
    {

      
      switch (tok_ptr->MsgId)
	{
	case REQUEST:
	  {
	    if (MASTER == 1)	//if master do this   
	      {
		if (((Table_quee[tok_ptr->Table_Id].Master_Flg == 1) ||
		     (Table_quee[tok_ptr->Table_Id].Master_Flg == 0))
		    && (Table_quee[tok_ptr->Table_Id].counter >= 0))
		  {
		    // if ((Table_quee[tok_ptr->Table_Id].state == 0) && (Table_quee[tok_ptr->Table_Id].counter != 1))
		    // due to 2 lock is coming at a time and +ve ack coming form both side
		    if (((Table_quee[tok_ptr->Table_Id].state == 0)
			 && (Table_quee[tok_ptr->Table_Id].counter == 0))
			&& (Table_quee[tok_ptr->Table_Id].un_1_flag == 0)
			&& (Table_quee[tok_ptr->Table_Id].un_2_flag == 0)
			&& (Table_quee[tok_ptr->Table_Id].un_3_flag == 0)
			&& (Table_quee[tok_ptr->Table_Id].un_4_flag == 0))
		      {
			/*Send postive Ack   update the M S C Flags Accordingly */
			/*SLAVE_REQ:M|S|C:0|1|1 , MASTER_TABLE:M|S|C :1|0|1, priority to master , hence send NACK to SLAVE */
			resp_tok.MsgId = RESPONSE;
			resp_tok.Table_Id = tok_ptr->Table_Id;
			resp_tok.Tid = tok_ptr->Tid;
			resp_tok.Master_Flg = 0;
			resp_tok.Slave_Flg = 1;
			resp_tok.ack = POSTIVE_ACK;
			resp_tok.counter = tok_ptr->counter;
			memset (mesg, 0, sizeof (mesg));
			memcpy (mesg, &resp_tok, sizeof (token));

			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
			  {
			    LOG_PRINT_CRITICAL ("TOGCS:SendResponse::+ve RESPONSE token send failed \n ");
           perror("send");
                            PEER_Leave();
		            return;
				}
			if (Table_quee[tok_ptr->Table_Id].Slave_Flg == 1
			    && Table_quee[tok_ptr->Table_Id].counter > 0)
			  {
			    LOG_PRINT_MAJOR ("FROMGCSSendResponse::DISCARDING Token as lock permission are already given to SLAVE \n");
			  }
			else
			  {
			    Table_quee[tok_ptr->Table_Id].counter++;
			  }
			Table_quee[tok_ptr->Table_Id].Slave_Flg = 1;
			Table_quee[tok_ptr->Table_Id].Master_Flg = 0;
			LOG_PRINT_MAJOR
			  ("TOGCS:SendResponse:: +ve LOCK RSP token Send TbId %d LockTid %d S %d M %d C %d state %d \n",
			   tok_ptr->Table_Id, tok_ptr->Tid,
			   Table_quee[tok_ptr->Table_Id].Slave_Flg,
			   Table_quee[tok_ptr->Table_Id].Master_Flg,
			   Table_quee[tok_ptr->Table_Id].counter,
			   Table_quee[tok_ptr->Table_Id].state);
		      }
		    else
		      {
			/*Send Negative response  no need to update the flags M S C Flags */
			resp_tok.MsgId = RESPONSE;
			resp_tok.Table_Id = tok_ptr->Table_Id;
			resp_tok.Tid = tok_ptr->Tid;
			resp_tok.Master_Flg = 1;
			resp_tok.Slave_Flg = 0;
			resp_tok.ack = NEGATIVE_ACK;
			resp_tok.counter--;

			memset (mesg, 0, sizeof (mesg));
			memcpy (mesg, &resp_tok, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
			  {
			    LOG_PRINT_CRITICAL ("TOGCS:SendResponse::-ve RESPONSE token send failed \n ");
           perror("send");
                            PEER_Leave();
	                    return;
				}
			LOG_PRINT_MAJOR
			  ("TOGCS:SendResponse:: -ve LOCK RSP token Send TbId %d LockTid %d S %d M %d C %d state %d \n",
			   tok_ptr->Table_Id, tok_ptr->Tid,
			   Table_quee[tok_ptr->Table_Id].Slave_Flg,
			   Table_quee[tok_ptr->Table_Id].Master_Flg,
			   Table_quee[tok_ptr->Table_Id].counter,
			   Table_quee[tok_ptr->Table_Id].state);
		      }
		  }

	      }	//Master if ends here
	    if (MASTER == 0)	//if slave do this 
	      {
		if (((Table_quee[tok_ptr->Table_Id].Slave_Flg == 1) || (Table_quee[tok_ptr->Table_Id].Slave_Flg == 0)) && (Table_quee[tok_ptr->Table_Id].counter >= 0))	/*Query:whether Counter check is neccessary? */
		  {
		    if ((Table_quee[tok_ptr->Table_Id].state == 0)
			&& (Table_quee[tok_ptr->Table_Id].un_1_flag == 0)
			&& (Table_quee[tok_ptr->Table_Id].un_2_flag == 0
			    &&
			    ((Table_quee[tok_ptr->Table_Id].un_3_flag == 0))
			    &&
			    ((Table_quee[tok_ptr->Table_Id].un_4_flag == 0))))
		      {		/*Send postive Ack   update the M S C Flags Accordingly */
			resp_tok.MsgId = RESPONSE;
			resp_tok.Table_Id = tok_ptr->Table_Id;
			resp_tok.Tid = tok_ptr->Tid;
			resp_tok.Master_Flg = 1;
			resp_tok.Slave_Flg = 0;
			resp_tok.ack = POSTIVE_ACK;
			resp_tok.counter = tok_ptr->counter;
			memset (mesg, 0, sizeof (mesg));
			memcpy (mesg, &resp_tok, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
			  {
			    LOG_PRINT_CRITICAL ("TOGCS:SendResponse::+ve RESPONSE token send failed \n ");
           perror("send");
                            PEER_Leave();
		            return;
				}
			/*Need to upadte the MSC FLAGS on This Side too */
			if (Table_quee[tok_ptr->Table_Id].Master_Flg == 1
			    && Table_quee[tok_ptr->Table_Id].counter > 0)
			  {
			    LOG_PRINT_MAJOR ("FROMGCS:SendResponse:: DISCARDING Token as lock permission are already given to MASTER \n");
			  }
			else
			  {
			    Table_quee[tok_ptr->Table_Id].counter++;
			  }
			Table_quee[tok_ptr->Table_Id].Slave_Flg = 0;
			Table_quee[tok_ptr->Table_Id].Master_Flg = 1;
			LOG_PRINT_MAJOR
			  ("TOGCS:SendResponse:: +ve LOCK RSP token Send TbId %d LockTid %d S %d M %d C %d state %d \n",
			   tok_ptr->Table_Id, tok_ptr->Tid,
			   Table_quee[tok_ptr->Table_Id].Slave_Flg,
			   Table_quee[tok_ptr->Table_Id].Master_Flg,
			   Table_quee[tok_ptr->Table_Id].counter,
			   Table_quee[tok_ptr->Table_Id].state);
		      }
		    else
		      {
			/*Send Negative response  no need to update the flags M S C Flags */
			resp_tok.MsgId = RESPONSE;
			resp_tok.Table_Id = tok_ptr->Table_Id;
			resp_tok.Tid = tok_ptr->Tid;
			resp_tok.Master_Flg = 0;
			resp_tok.Slave_Flg = 1;
			resp_tok.ack = NEGATIVE_ACK;
			resp_tok.counter--;	/*Query:Previously copied at slave,but now no handling for this */

			memset (mesg, 0, sizeof (mesg));
			memcpy (mesg, &resp_tok, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
			  {
			    LOG_PRINT_CRITICAL ("TOGCS:SendResponse:: -ve RESPONSE token send failed \n ");
           perror("send");
                            PEER_Leave();
			    return;
				}
			/*Need to upadte the MSC FLAGS on This Side too */
			LOG_PRINT_MAJOR
			  ("TOGCS:SendResponse:: -ve LOCK RSP token Send TbId %d LockTid %d S %d M %d C %d state %d \n",
			   tok_ptr->Table_Id, tok_ptr->Tid,
			   Table_quee[tok_ptr->Table_Id].Slave_Flg,
			   Table_quee[tok_ptr->Table_Id].Master_Flg,
			   Table_quee[tok_ptr->Table_Id].counter,
			   Table_quee[tok_ptr->Table_Id].state);
		      }
		  }
	      }	//Slave if ends here

	  }
	  break;
	case RESPONSE:
	  {
	    if (tok_ptr->ack == POSTIVE_ACK)
	      {
		Table_quee[tok_ptr->Table_Id].Slave_Flg = tok_ptr->Slave_Flg;
		Table_quee[tok_ptr->Table_Id].Master_Flg =
		  tok_ptr->Master_Flg;
		Table_quee[tok_ptr->Table_Id].state = 1;/* setting state = 1 as Response have recieved */
		message_processing (tok_ptr->Table_Id, tok_ptr->MsgId);
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse:: +ve LOCK ACK token Recv TbId %d LockTid %d S %d M %d C %d state %d\n",
		   tok_ptr->Table_Id, tok_ptr->Tid,
		   Table_quee[tok_ptr->Table_Id].Slave_Flg,
		   Table_quee[tok_ptr->Table_Id].Master_Flg,
		   Table_quee[tok_ptr->Table_Id].counter,
		   Table_quee[tok_ptr->Table_Id].state);
	      }
	    if (tok_ptr->ack == NEGATIVE_ACK)
	      {
		if (MASTER)
		  {
		    if (Table_quee[tok_ptr->Table_Id].Slave_Flg == 1
			&& Table_quee[tok_ptr->Table_Id].counter > 0)
		      {
			LOG_PRINT_CRITICAL ("FROMGCS:SendResponse::DISCARDING token as permission flags are alraedy updated for peer lock\n");


		      }
		    else
		      {
			Table_quee[tok_ptr->Table_Id].counter++;	/*when self stub joins then to sync  counter we  need to be update it if lock permission are with peer stub */

		      }
		  }
		else
		  {
		    if (Table_quee[tok_ptr->Table_Id].Master_Flg == 1
			&& Table_quee[tok_ptr->Table_Id].counter > 0)
		      {
			LOG_PRINT_CRITICAL ("FROMGCS:SendResponse::DISCARDING token as permission flags are alraedy updated for peer lock\n");
		      }
		    else
		      {
			Table_quee[tok_ptr->Table_Id].counter++;	/*when self stub joins then to sync  counter we  need to be update it if lock permission are with peer stub */

		      }

		  }
		//    Table_quee[tok_ptr->Table_Id].counter++;/*when self stub joins then to sync  counter we  need to be update it if lock permission are with peer stub*/
		Table_quee[tok_ptr->Table_Id].Master_Flg = tok_ptr->Master_Flg;
		Table_quee[tok_ptr->Table_Id].Slave_Flg = tok_ptr->Slave_Flg;
		/* I hope no need to do anything */
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse::-ve LOCK ACK token Recv TbId %d LockTid %d S %d M %d C %d state %d\n",
		   tok_ptr->Table_Id, tok_ptr->Tid,
		   Table_quee[tok_ptr->Table_Id].Slave_Flg,
		   Table_quee[tok_ptr->Table_Id].Master_Flg,
		   Table_quee[tok_ptr->Table_Id].counter,
		   Table_quee[tok_ptr->Table_Id].state);
	      }
	  }
	  break;

	case UNLOCK_REQUEST:
	  {
	    if (MASTER == 0)
	      {
		if (Table_quee[tok_ptr->Table_Id].Slave_Flg == 0
		    && (Table_quee[tok_ptr->Table_Id].buf != NULL))
		  {

		    resp_tok.MsgId = UNLOCK_RESPONSE;
		    resp_tok.Table_Id = tok_ptr->Table_Id;
		    resp_tok.Tid = tok_ptr->Tid;
		    resp_tok.Master_Flg = 0;
		    resp_tok.Slave_Flg = 1;
		    resp_tok.ack = POSTIVE_ACK;
		    resp_tok.counter = tok_ptr->counter;
		    /*Need to upadte the MSC FLAGS on This Side too */
		    Table_quee[tok_ptr->Table_Id].Slave_Flg = 1;
		    /*Need to decrement counter for master which was increment at time request token received */
		    if (Table_quee[tok_ptr->Table_Id].counter > 1)
		      {
			Table_quee[tok_ptr->Table_Id].counter--;
		      }
		    Table_quee[tok_ptr->Table_Id].Master_Flg = 0;

		    memset (mesg, 0, sizeof (mesg));
		    memcpy (mesg, &resp_tok, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
		      {
			       LOG_PRINT_CRITICAL ("TOGCS:SendResponse:: UNLOCK_RESPONSE token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
		    /*Processing the SLAVE messages from the queue */
		    message_processing (tok_ptr->Table_Id, UNLOCK_RESPONSE);
		    LOG_PRINT_MAJOR
		      ("FROMGCS:SendResponse::+ve UNLOCK_ACK token Send by Slave Tbld %d UNLockTid %d S %d M %d C %d state %d\n",
		       tok_ptr->Table_Id, tok_ptr->Tid,
		       Table_quee[tok_ptr->Table_Id].Slave_Flg,
		       Table_quee[tok_ptr->Table_Id].Master_Flg,
		       Table_quee[tok_ptr->Table_Id].counter,
		       Table_quee[tok_ptr->Table_Id].state);

		  }
		else
		  {
		    resp_tok.MsgId = UNLOCK_RESPONSE;
		    resp_tok.Table_Id = tok_ptr->Table_Id;
		    resp_tok.Tid = tok_ptr->Tid;
		    resp_tok.Master_Flg = 0;
		    resp_tok.Slave_Flg = 0;
		    resp_tok.ack = NEGATIVE_ACK;
		    resp_tok.counter = --tok_ptr->counter;
		    /*Need to upadte the MSC FLAGS on This Side too */
		    if (Table_quee[tok_ptr->Table_Id].Slave_Flg == 1
			&& Table_quee[tok_ptr->Table_Id].counter > 0)
		      {
			/*Change for M flag is one when we are sending the -ve unlock towards Master */
		      }
		    else
		      {
			Table_quee[tok_ptr->Table_Id].Slave_Flg = 0;
			Table_quee[tok_ptr->Table_Id].counter =
			  resp_tok.counter;
			Table_quee[tok_ptr->Table_Id].Master_Flg = 0;
		      }
		    memset (mesg, 0, sizeof (mesg));
		    memcpy (mesg, &resp_tok, sizeof (token));

			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
		      {
			       LOG_PRINT_CRITICAL ("TOGCS:SendResponse:: -ve UNLOCK_RESPONSE token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
		    LOG_PRINT_MAJOR
		      ("FROMGCS :-ve UNLOCK_NACK token Send by Slave Tbld %d UNLockTid %d S %d M %d C %d state %d\n",
		       tok_ptr->Table_Id, tok_ptr->Tid,
		       Table_quee[tok_ptr->Table_Id].Slave_Flg,
		       Table_quee[tok_ptr->Table_Id].Master_Flg,
		       Table_quee[tok_ptr->Table_Id].counter,
		       Table_quee[tok_ptr->Table_Id].state);
		  }
	      }

	    if (MASTER == 1)
	      {
		if (Table_quee[tok_ptr->Table_Id].Master_Flg == 0
		    && (Table_quee[tok_ptr->Table_Id].buf != NULL))
		  {
		    resp_tok.MsgId = UNLOCK_RESPONSE;
		    resp_tok.Table_Id = tok_ptr->Table_Id;
		    resp_tok.Tid = tok_ptr->Tid;
		    resp_tok.Master_Flg = 1;
		    resp_tok.Slave_Flg = 0;
		    resp_tok.ack = POSTIVE_ACK;
		    resp_tok.counter = tok_ptr->counter;
		    /*Need to upadte the MSC FLAGS on This Side too */
		    Table_quee[tok_ptr->Table_Id].Slave_Flg = 0;
		    /*Need to decrement counter for master which was increment at time request token received */
		    if (Table_quee[tok_ptr->Table_Id].counter > 1)
		      {
			Table_quee[tok_ptr->Table_Id].counter--;
		      }
		    Table_quee[tok_ptr->Table_Id].Master_Flg = 1;
		    memset (mesg, 0, sizeof (mesg));
		    memcpy (mesg, &resp_tok, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
		      {
			       LOG_PRINT_CRITICAL ("TOGCS:SendResponse::+ve  UNLOCK_RESPONSE token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
		    /*Processing the MASTER messages from the queue */
		    message_processing (tok_ptr->Table_Id, UNLOCK_RESPONSE);
		    LOG_PRINT_MAJOR
		      ("FROMGCS :+ve UNLOCK_ACK token Send by Master Tbld %d UNLockTid %d S %d M %d C %d state %d\n",
		       tok_ptr->Table_Id, tok_ptr->Tid,
		       Table_quee[tok_ptr->Table_Id].Slave_Flg,
		       Table_quee[tok_ptr->Table_Id].Master_Flg,
		       Table_quee[tok_ptr->Table_Id].counter,
		       Table_quee[tok_ptr->Table_Id].state);
		  }
		else
		  {
		    resp_tok.MsgId = UNLOCK_RESPONSE;
		    resp_tok.Table_Id = tok_ptr->Table_Id;
		    resp_tok.Tid = tok_ptr->Tid;
		    resp_tok.Master_Flg = 0;
		    resp_tok.Slave_Flg = 0;
		    resp_tok.ack = NEGATIVE_ACK;
		    resp_tok.counter = --tok_ptr->counter;
		    /*Need to upadte the MSC FLAGS on This Side too */
		    if (Table_quee[tok_ptr->Table_Id].Master_Flg == 1
			&& Table_quee[tok_ptr->Table_Id].counter > 0)
		      {
			/*Change for M flag is one when we are sending the -ve unlock towards Slave */
		      }
		    else
		      {
			Table_quee[tok_ptr->Table_Id].Slave_Flg = 0;
			Table_quee[tok_ptr->Table_Id].counter =
			  resp_tok.counter;
			Table_quee[tok_ptr->Table_Id].Master_Flg = 0;
		      }

		    memset (mesg, 0, sizeof (mesg));
		    memcpy (mesg, &resp_tok, sizeof (token));

			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
		      {
			       LOG_PRINT_CRITICAL ("TOGCS:SendResponse:: -ve UNLOCK_RESPONSE token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
		    LOG_PRINT_MAJOR
		      ("FROMGCS :-ve UNLOCK_NACK token Send by Master Tbld %d UNLockTid %d S %d M %d C %d state %d\n",
		       tok_ptr->Table_Id, tok_ptr->Tid,
		       Table_quee[tok_ptr->Table_Id].Slave_Flg,
		       Table_quee[tok_ptr->Table_Id].Master_Flg,
		       Table_quee[tok_ptr->Table_Id].counter,
		       Table_quee[tok_ptr->Table_Id].state);
		  }
	      }
	  }
	  break;
	case UNLOCK_RESPONSE:
	  {
	    if (tok_ptr->ack == POSTIVE_ACK)
	      {
		Table_quee[tok_ptr->Table_Id].Slave_Flg = tok_ptr->Slave_Flg;
		Table_quee[tok_ptr->Table_Id].Master_Flg =
		  tok_ptr->Master_Flg;
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse:: +ve UNLOCK_ACK Recv TbId %d UNLockTid %d S %d M %d C %d state %d \n",
		   tok_ptr->Table_Id, tok_ptr->Tid,
		   Table_quee[tok_ptr->Table_Id].Slave_Flg,
		   Table_quee[tok_ptr->Table_Id].Master_Flg,
		   Table_quee[tok_ptr->Table_Id].counter,
		   Table_quee[tok_ptr->Table_Id].state);
	      }
	    if (tok_ptr->ack == NEGATIVE_ACK)
	      {
		Table_quee[tok_ptr->Table_Id].counter--;
		if (MASTER)
		  {
		    Table_quee[tok_ptr->Table_Id].Slave_Flg = 0;
		    Table_quee[tok_ptr->Table_Id].Master_Flg = 1;
		  }
		else
		  {
		    Table_quee[tok_ptr->Table_Id].Slave_Flg = 1;
		    Table_quee[tok_ptr->Table_Id].Master_Flg = 0;

		  }
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse:: -ve UNLOCK_NACK Recv TbId %d UNLockTid %d S %d M %d C %d state %d \n",
		   tok_ptr->Table_Id, tok_ptr->Tid,
		   Table_quee[tok_ptr->Table_Id].Slave_Flg,
		   Table_quee[tok_ptr->Table_Id].Master_Flg,
		   Table_quee[tok_ptr->Table_Id].counter,
		   Table_quee[tok_ptr->Table_Id].state);
		if (Table_quee[tok_ptr->Table_Id].buf)
		  {
		    updtCnt.MsgId = COUNTER_UPDATE;
		    updtCnt.Table_Id = tok_ptr->Table_Id;
		    memset (mesg, 0, sizeof (mesg));
		    memcpy (mesg, &updtCnt, sizeof (token));
			  if((ret = send (sockfd_udp_client, mesg, sizeof (token), 0)) < 0 )
		      {
			       LOG_PRINT_CRITICAL ("SendResponse: COUNTER UPDATE token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
		    LOG_PRINT_MAJOR
		      ("TOGCS:SendResponse:: Sending COUNTER UPDATE TbId %d UNLockTid %d  \n",
		       tok_ptr->Table_Id, tok_ptr->Tid);
		  }
		message_processing (tok_ptr->Table_Id, UNLOCK_RESPONSE);
	      }

	  }
	  break;
	case COUNTER_UPDATE:
	  {
	    if ((((MASTER == 1)
		  && (Table_quee[tok_ptr->Table_Id].Slave_Flg == 1))
		 || ((MASTER == 0)
		     && (Table_quee[tok_ptr->Table_Id].Master_Flg == 1)))
		&& (Table_quee[tok_ptr->Table_Id].counter > 0))
	      {

		/*Note:when counter update is delayed and lock arrives on TCP from peer GCS_STUB then counter is already incremented while receiving it on tcp */
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse:: COUNTER ALREADY UPDATED ON TCP::DISCARDING COUNTER UPDATE TableId[%d]\n",
		   tok_ptr->Table_Id);

	      }
	    else if ((Table_quee[tok_ptr->Table_Id].buf != NULL)
		     && (Table_quee[tok_ptr->Table_Id].state == 0))
	      {
		/*Note:when counter update is delayed and lock arrives & REQUEST is alraedy placed to peer STUB then 
		   on receiving negative lock Ack counter will be update accordingly */
		LOG_PRINT_MAJOR ("FROMGCS:SendResponse:: DISCARDING COUNTER UPDATE TableId[%d]\n",
				 tok_ptr->Table_Id);
	      }
	    else if ((Table_quee[tok_ptr->Table_Id].buf == NULL)
		     && (Table_quee[tok_ptr->Table_Id].state == 0))
	      {
		Table_quee[tok_ptr->Table_Id].counter++;
		if (MASTER == 1)
		  {
		    Table_quee[tok_ptr->Table_Id].Slave_Flg = 1;
		  }
		else if (MASTER == 0)
		  {
		    Table_quee[tok_ptr->Table_Id].Master_Flg = 1;

		  }
		LOG_PRINT_MAJOR
		  ("FROMGCS:SendResponse:: COUNTER_UPDATED TbID %d  S %d M %d C %d state %d\n",
		   tok_ptr->Table_Id, Table_quee[tok_ptr->Table_Id].Slave_Flg,
		   Table_quee[tok_ptr->Table_Id].Master_Flg,
		   Table_quee[tok_ptr->Table_Id].counter,
		   Table_quee[tok_ptr->Table_Id].state);
	      }
	  }
	  break;
	case LOCK_ACK:
	  {
	    LOG_PRINT_MAJOR("FROMGCS:SendResponse:: LOCK ACK Received TableID[%d]\n",tok_ptr->Table_Id);
	    processLockAck (tok_ptr->Table_Id);
	  }
	  break;
	case UNLOCK_ACK:

	    LOG_PRINT_MAJOR("FROMGCS:SendResponse:: UNLOCK ACK Received TableID[%d]\n",tok_ptr->Table_Id);
	  Table_Id = tok_ptr->Table_Id;

	  if (Table_quee[Table_Id].counter > 0)
	    {

	      if (Table_quee[Table_Id].un_1_flag == 1)
		{
		  Table_quee[Table_Id].un_1_flag = 0;
		}
	      else
		{
		  if (Table_quee[Table_Id].un_2_flag == 1)
		    {
		      Table_quee[Table_Id].un_2_flag = 0;
		    }
		  else
		    {
		      if (Table_quee[Table_Id].un_3_flag == 1)
			{
			  Table_quee[Table_Id].un_3_flag = 0;
			}
		      else
			{
			  if (Table_quee[Table_Id].un_4_flag == 1)
			    {
			      Table_quee[Table_Id].un_4_flag = 0;
			    }

			}

		    }
		}
	      /*Towards GCS send */
	      Table_quee[Table_Id].counter--;
	    }
	  if ((Table_quee[Table_Id].counter == 0)
	      || (Table_quee[Table_Id].state == 0))
	    {
	      tokmsg.MsgId = UNLOCK_REQUEST;
	      tokmsg.Table_Id = Table_Id;
	      tokmsg.Tid = tok_ptr->Tid;
	      if (Table_quee[Table_Id].Master_Flg == 1)
		{
		  Table_quee[Table_Id].Master_Flg = 0;
		  Table_quee[Table_Id].Slave_Flg = 1;
		  tokmsg.Master_Flg = 0;
		  tokmsg.Slave_Flg = 1;
		}
	      else if (Table_quee[Table_Id].Slave_Flg == 1)
		{
		  Table_quee[Table_Id].Master_Flg = 1;
		  Table_quee[Table_Id].Slave_Flg = 0;
		  tokmsg.Master_Flg = 1;
		  tokmsg.Slave_Flg = 0;
		}
	      else
		{
		  Table_quee[Table_Id].Master_Flg = 0;
		  Table_quee[Table_Id].Slave_Flg = 0;
		  tokmsg.Master_Flg = 0;
		  tokmsg.Slave_Flg = 0;
		}

	      Table_quee[Table_Id].counter++;
	      Table_quee[Table_Id].state = 0;
	      tokmsg.counter = 1;
	      bzero (&cliaddr, sizeof (cliaddr));
	      cliaddr.sin_family = AF_INET;
	      cliaddr.sin_addr.s_addr = inet_addr (CLIPEER_UDPADDR);
	      cliaddr.sin_port = htons (UDP_PORT);

	      memcpy (UDP_buff, &tokmsg, sizeof (tokmsg));
	      /*prepare the unlock Request message to peer Stub */
			  if((ret = send (sockfd_udp_client,UDP_buff , sizeof (token), 0)) < 0 )
		     {
			       LOG_PRINT_CRITICAL ("TOGCS:SendResponse:: UNLOCK REQUEST token send failed \n");
           perror("send");
                            PEER_Leave();
			    return;
				}
	       LOG_PRINT_MAJOR("TOGCS:SendResponse::SENDING UNLOCK REQUEST PROG TbId %d UNlockTid %d S %d M %d C %d state %d \n",tok_ptr->Table_Id,tok_ptr->Tid,Table_quee[Table_Id].Slave_Flg,Table_quee[Table_Id].Master_Flg,Table_quee[Table_Id].counter,Table_quee[Table_Id].state);
	    }
	  break;

	default:
	  LOG_PRINT_CRITICAL ("FROMGCS:SendResponse:: Invalid Choice reached\n");
	}

    }
}
void
processLockAck (int Table_Id)
{
  setLockAckFlagON (Table_Id);
  /*Stored unlock should not be send from here in case syncFlag == 2 i.e case when no sync unlock has being received */
  if (((Table_quee[Table_Id].unlockbuf_1 != NULL)
       || (Table_quee[Table_Id].unlockbuf_2 != NULL)) && (syncFlag != 2))
    {
      retrieveUnlock (Table_Id);
    }
}
void
setLockAckFlagON (int Table_Id)
{
  if (Table_quee[Table_Id].Lock_Ack_Flag == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting I Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag = 1;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_1 == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting II Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_1 = 1;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_2 == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting III Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_2 = 1;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_3 == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting IV Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_3 = 1;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_4 == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting V Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_4 = 1;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_5 == 0)
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: Setting VI Lock_Ack_Flag ON\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_5 = 1;
    }
  else
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagON:: ALL  Lock_Ack_Flag ON\n"));

    }

}
void
setLockAckFlagOFF (int Table_Id)
{
  if (Table_quee[Table_Id].Lock_Ack_Flag == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting I Lock_Ack_Flag OFF\n"));
      Table_quee[Table_Id].Lock_Ack_Flag = 0;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_1 == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting II Lock_Ack_Flag OFF\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_1 = 0;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_2 == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting III Lock_Ack_Flag OFF\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_2 = 0;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_3 == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting IV Lock_Ack_Flag OFF\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_3 = 0;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_4 == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting V Lock_Ack_Flag OFF\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_4 = 0;
    }
  else if (Table_quee[Table_Id].Lock_Ack_Flag_5 == 1)
    {
      //GCSUTIL_DEBUG_TRACE(("processUnlock:: Setting VI Lock_Ack_Flag\n"));
      Table_quee[Table_Id].Lock_Ack_Flag_5 = 0;
    }
  else
    {
      //GCSUTIL_DEBUG_TRACE(("setLockAckFlagOFF:: ALL Lock_Ack_Flag are already OFF\n"));

    }


}
void
retrieveUnlock (int Table_Id)
{
  unsigned int len = 0;
  int ret_3 = 0;
  //token tokmsg;
  char UDP_buff[50];
  // struct sockaddr_in cliaddr;

  memset (UDP_buff, 0, 50);

  if (Table_quee[Table_Id].unlockbuf_1 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[Table_Id].unlockLen_1;
      memcpy (bufUnlock, Table_quee[Table_Id].unlockbuf_1, len);
      Table_quee[Table_Id].unlockLen_1 = 0;
      free (Table_quee[Table_Id].unlockbuf_1);
      Table_quee[Table_Id].unlockbuf_1 = NULL;

      if (Table_quee[Table_Id].un_1_flag == 0)
	{
	  Table_quee[Table_Id].un_1_flag = 1;
	}
      else
	{
	  if (Table_quee[Table_Id].un_2_flag == 0)
	    {
	      Table_quee[Table_Id].un_2_flag = 1;
	    }
	  else
	    {
	      if (Table_quee[Table_Id].un_3_flag == 0)
		{
		  Table_quee[Table_Id].un_3_flag = 1;
		}
	      else
		{
		  if (Table_quee[Table_Id].un_4_flag == 0)
		    {
		      Table_quee[Table_Id].un_4_flag = 1;
		    }
		  else
		    {
		      LOG_PRINT_CRITICAL
			("FROMSTACK :More Than Two UNLOCK REC\n");
		    }
		}
	    }
	}
      //  GCSUTIL_DEBUG_TRACE(("retrieveUnlock:::un_1_flag %d | un_2_flag %d",un_1_flag,un_2_flag));        
    }
  else if (Table_quee[Table_Id].unlockbuf_2 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[Table_Id].unlockLen_2;
      memcpy (bufUnlock, Table_quee[Table_Id].unlockbuf_2, len);
      Table_quee[Table_Id].unlockLen_2 = 0;
      free (Table_quee[Table_Id].unlockbuf_2);
      Table_quee[Table_Id].unlockbuf_2 = NULL;
      if (Table_quee[Table_Id].un_1_flag == 0)
	{
	  Table_quee[Table_Id].un_1_flag = 1;
	}
      else
	{
	  if (Table_quee[Table_Id].un_2_flag == 0)
	    {
	      Table_quee[Table_Id].un_2_flag = 1;
	    }
	  else
	    {
	      if (Table_quee[Table_Id].un_3_flag == 0)
		{
		  Table_quee[Table_Id].un_3_flag = 1;
		}
	      else
		{
		  if (Table_quee[Table_Id].un_4_flag == 0)
		    {
		      Table_quee[Table_Id].un_4_flag = 1;
		    }
		  else
		    {
		      LOG_PRINT_CRITICAL
			("FROMSTACK :More Than Two UNLOCK REC\n");
		    }
		}
	    }
	}
    }
  setLockAckFlagOFF (Table_Id);

  /*Patch: 2-june-10: Resetting OldTid as the re-multicasted unclock msgfrom Stack  after SYNC UNLOCK  is not discarded at unix recv*/
  if(syncFlag == 2)
  {
      LOG_PRINT_CRITICAL("retrieveUnlock :: Resetting OldTid in case stored unlock msg\n");
      OldTid = 0;
  }
  /*Patch:2-june-10: Not updating state flag when LOCK_ACK token is received during sync procedure when syncflag == 2*/
  //if (Table_quee[Table_Id].counter == 1)
  if ((Table_quee[Table_Id].counter == 1) && (syncFlag != 2))
    {
      //GCSUTIL_DEBUG_TRACE(("retrieveUnlock :State Have change \n"));
      Table_quee[Table_Id].state = 0;
      /*this is due to storing of Lock until -ve Unlock have came */
    }
  /*Towards GCS send */
/*Patch:2-june-10: stored unlock  is not send to peer during sync procedure*/
 // if (TcpClient > 0)
  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
    {
     // GCSUTIL_DEBUG_TRACE (("TOGCS :PeerGCSSend len %d\n", len));
      ret_3 = send (TcpClient, bufUnlock, len, 0);
      if (ret_3 <= 0)
	{
	  LOG_PRINT_CRITICAL ("retrieveUnlock:TcpClientsend() failed \n");
	  //close (TcpClient);
	  //TcpClient = 0;
          //PEER_ALRD_JOIN=0;
          MUTEX_ReleaseMutex (&FlagLock);
          PEER_Leave();
	  return;
	}
    }
 // GCSUTIL_DEBUG_TRACE (("TOSTACK ::SelfSend %d\n", len));
  ret_3 = send (UNIX_SMbox, bufUnlock, len, 0);
  if (ret_3 <= 0)
    {
      LOG_PRINT_CRITICAL ("retrieveUnlock:unix send() failed \n");
      close (UNIX_SMbox);
      UNIX_SMbox = 0;
      pthread_cancel (Recvhread);	/*Need to check whether different thread can cancel each other */
          Recvhread = 0;
      return;
    }
  if(ret_3 != len)
  {
     LOG_PRINT_CRITICAL("retrieveUnlock: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
  }
//  GCSUTIL_DEBUG_TRACE (("retrieveUnlock:::un_1_flag %d|un_2_flag %d|un_3_flag %d|un_4_flag %d", Table_quee[Table_Id].un_1_flag, Table_quee[Table_Id].un_2_flag, Table_quee[Table_Id].un_3_flag, Table_quee[Table_Id].un_4_flag));




/***********************************Change for Unlock Pendinf su*****************************/
#if 0

  if (Table_quee[Table_Id].counter > 0)
    {
      Table_quee[Table_Id].counter--;
    }
  //GCSUTIL_DEBUG_TRACE(("retrieveUnlock:: Table_quee[%d].counter %d\n",Table_Id,Table_quee[Table_Id].counter));
  if (Table_quee[Table_Id].counter == 0)
    {
      tokmsg.MsgId = UNLOCK_REQUEST;
      tokmsg.Table_Id = Table_Id;
      if (Table_quee[Table_Id].Master_Flg == 1)
	{
	  Table_quee[Table_Id].Master_Flg = 0;
	  Table_quee[Table_Id].Slave_Flg = 1;
	  tokmsg.Master_Flg = 0;
	  tokmsg.Slave_Flg = 1;
	}
      else if (Table_quee[Table_Id].Slave_Flg == 1)
	{
	  Table_quee[Table_Id].Master_Flg = 1;
	  Table_quee[Table_Id].Slave_Flg = 0;
	  tokmsg.Master_Flg = 1;
	  tokmsg.Slave_Flg = 0;
	}
      else
	{
	  Table_quee[Table_Id].Master_Flg = 0;
	  Table_quee[Table_Id].Slave_Flg = 0;
	  tokmsg.Master_Flg = 0;
	  tokmsg.Slave_Flg = 0;
	}

      Table_quee[Table_Id].counter++;
      Table_quee[Table_Id].state = 0;
      tokmsg.counter = Table_quee[Table_Id].counter;
      bzero (&cliaddr, sizeof (cliaddr));
      cliaddr.sin_family = AF_INET;
      cliaddr.sin_addr.s_addr = inet_addr (CLIPEER_UDPADDR);
      cliaddr.sin_port = htons (UDP_PORT);

      memcpy (UDP_buff, &tokmsg, sizeof (tokmsg));
      /*prepare the unlock Request message to peer Stub */
      ret =
	sendto (sockfd_udp, UDP_buff, sizeof (token), 0,
		(struct sockaddr *) &cliaddr_udp, sizeof (cliaddr_udp));
      if (ret <= 0)
	{
	  //GCSUTIL_DEBUG_TRACE(("sendto: Fail"));
	  //GCSUTIL_DEBUG_TRACE(("ret[%d]",ret));
	}

    }
#endif
/***********************************Change for Unlock Pendinf su*****************************/

}

int
message_processing (int tableId, int msgtype)
{
  int len;
  char *buf = NULL;
  int ret_3 = 0;
  unsigned int tid = 0;
  DSM_Message *msg = NULL;



  if ((msgtype != RESPONSE))
    {
      if (msgtype != UNLOCK_RESPONSE)
	{
	  LOG_PRINT_CRITICAL ("INVALID RESPONSE RECEIVED \n");
	  return (0);
	}
    }
  len = Table_quee[tableId].Len;
  if ((Table_quee[tableId].buf == NULL))
    {
      GCSUTIL_DEBUG_TRACE (("message_processing ::No message for tableId %d\n", tableId));
      //LOG_PRINT_MAJOR("message_processing ::No message for tableId %d\n",tableId);
      return (0);
    }
  /*Patch:2-june-10 : Sending msg to stack in case of (syncflag!= 2) only . As the stored lock in case of (syncflag == 2) will be send back to stack on receiving SYNC UNLOCK only */
  if ((Table_quee[tableId].buf) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len;
      buf = Table_quee[tableId].buf;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;
      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0)&& (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                  //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		  //         continue;
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		  // continue;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf)
		{
		  free (Table_quee[tableId].buf);
		  Table_quee[tableId].buf = NULL;
		  Table_quee[tableId].Len = 0;
		}

	    }

	}
      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing I:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);
    }

  buf = NULL;
  if ((Table_quee[tableId].buf_1) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len_1;
      buf = Table_quee[tableId].buf_1;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;
      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))&& (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                    //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		  // continue;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_1)
		{
		  free (Table_quee[tableId].buf_1);
		  Table_quee[tableId].buf_1 = NULL;
		  Table_quee[tableId].Len_1 = 0;
		}
	    }

	}

      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing II:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);
    }



  buf = NULL;
  if ((Table_quee[tableId].buf_2) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len_2;
      buf = Table_quee[tableId].buf_2;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;

      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0)&& (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                  //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		  // continue;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_2)
		{
		  free (Table_quee[tableId].buf_2);
		  Table_quee[tableId].buf_2 = NULL;
		  Table_quee[tableId].Len_2 = 0;
		}
	    }

	}
      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing III:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);
    }

  buf = NULL;
  if ((Table_quee[tableId].buf_3) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len_3;
      buf = Table_quee[tableId].buf_3;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;
      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0)&& (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                  //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_3)
		{
		  free (Table_quee[tableId].buf_3);
		  Table_quee[tableId].buf_3 = NULL;
		  Table_quee[tableId].Len_3 = 0;
		}
	    }

	}
      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing IV:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);

    }

  buf = NULL;
  if ((Table_quee[tableId].buf_4) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len_4;
      buf = Table_quee[tableId].buf_4;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;
      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                  //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_4)
		{
		  free (Table_quee[tableId].buf_4);
		  Table_quee[tableId].buf_4 = NULL;
		  Table_quee[tableId].Len_4 = 0;
		}
	    }

	}

      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing V:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);
    }


  buf = NULL;
  if ((Table_quee[tableId].buf_5) && (syncFlag != 2))
    {
      len = Table_quee[tableId].Len_5;
      buf = Table_quee[tableId].buf_5;
      msg = NULL;
      msg = (DSM_Message *) & buf[80];
      tid = msg->u.lockUnlockTable.tid;
      if (((Table_quee[tableId].Master_Flg == 1)
	   || (Table_quee[tableId].Slave_Flg == 1))
	  && (Table_quee[tableId].counter > 0))
	{
	  /*Towards GCS send */
	  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))&& (syncFlag == 0))
	    {
	      ret_3 = send (TcpClient, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:TcpClientsend() failed \n");
		  perror ("message_processing:TcpClientsend() failed ");
		  //close (TcpClient);
		  //TcpClient = 0;
                  //PEER_ALRD_JOIN=0;
                  MUTEX_ReleaseMutex (&FlagLock);
                  PEER_Leave();
		}
	    }
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("message_processing:send_UNIX_SMbox() failed \n");
		  perror ("message_processing:send_UNIX_SMbox() failed ");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		  // continue;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("message_processing: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_5)
		{
		  free (Table_quee[tableId].buf_5);
		  Table_quee[tableId].buf_5 = NULL;
		  Table_quee[tableId].Len_5 = 0;
		}
	    }

	  /*Towards GCS send */
	}
      Table_quee[tableId].state = 1;
      LOG_PRINT_MAJOR
	("message_processing VI:TbId %d LockTid %d S %d M %d C %d state %d\n",
	 tableId, tid, Table_quee[tableId].Slave_Flg,
	 Table_quee[tableId].Master_Flg, Table_quee[tableId].counter,
	 Table_quee[tableId].state);
    }
  return (1);
}


int
MUTEX_CreateMutex (pthread_mutex_t * m)
{
  pthread_mutexattr_t attr;

  if (pthread_mutexattr_init (&attr) != 0)
    {
      return (-1);
    }

  if (pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE_NP) != 0)
    {
      return (-1);
    }

  if (pthread_mutex_init (m, &attr) != 0)
    {
      return (-1);
    }
  return (1);
}

int
MUTEX_AcquireMutex (pthread_mutex_t * m)
{
  if (pthread_mutex_lock (m) != 0)
    {
      //GCSUTIL_DEBUG_TRACE(("MUTEX_AcquireMutex:Fail\n"));
      return (-1);
    }

  return (1);
}

int
MUTEX_ReleaseMutex (pthread_mutex_t * m)
{
  if (pthread_mutex_unlock (m) != 0)
    {
      //GCSUTIL_DEBUG_TRACE(("MUTEX_ReleaseMutex:Fail\n"));
      return (-1);
    }

  return (1);
}


				 /*In case of Negative condition*//*TCP Break means peer Kill */
void
MessageRetFromLockque ()
{
  unsigned int tableId = 0, cnt = 0;
  int len, ret_3;
  char *buf = NULL;

  for (tableId = 0; tableId < 50; tableId++)
    {
      if (Table_quee[tableId].buf)
	{
	  len = Table_quee[tableId].Len;
	  buf = Table_quee[tableId].buf;
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque: send_UNIX_SMbox failed ::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf)
		{
		  free (Table_quee[tableId].buf);
		  Table_quee[tableId].buf = NULL;
		  Table_quee[tableId].Len = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:I SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_1)
	{
	  len = Table_quee[tableId].Len_1;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_1;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque: send_UNIX_SMbox failed ::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_1)
		{
		  free (Table_quee[tableId].buf_1);
		  Table_quee[tableId].buf_1 = NULL;
		  Table_quee[tableId].Len_1 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:II SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_2)
	{
	  len = Table_quee[tableId].Len_2;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_2;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque:send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_2)
		{
		  free (Table_quee[tableId].buf_2);
		  Table_quee[tableId].buf_2 = NULL;
		  Table_quee[tableId].Len_2 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:III SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_3)
	{
	  len = Table_quee[tableId].Len_3;
	  buf = NULL;
	  memcpy (buf, Table_quee[tableId].buf_3, len);
	  buf = Table_quee[tableId].buf_3;
	  //GCSUTIL_DEBUG_TRACE(("MessageRetFromLockque:Table_quee[%d].counter %d\n",tableId,Table_quee[tableId].counter));
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_3)
		{
		  free (Table_quee[tableId].buf_3);
		  Table_quee[tableId].buf_3 = NULL;
		  Table_quee[tableId].Len_3 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:IV SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_4)
	{
	  len = Table_quee[tableId].Len_4;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_4;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_4)
		{
		  free (Table_quee[tableId].buf_4);
		  Table_quee[tableId].buf_4 = NULL;
		  Table_quee[tableId].Len_4 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:V SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_5)
	{
	  len = Table_quee[tableId].Len_5;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_5;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetFromLockque: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
        Recvhread = 0;
		  // continue;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetFromLockque: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_5)
		{
		  free (Table_quee[tableId].buf_5);
		  Table_quee[tableId].buf_5 = NULL;
		  Table_quee[tableId].Len_5 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	    LOG_PRINT_CRITICAL("TOSTACK:MessageRetFromLockque:VI SelfSend TbId[%d] len[%d]: S[%d]M[%d]C[%d]State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}

      if (MASTER)
	{
	  /* In case of MASTER STUB */
	  if (Table_quee[tableId].Slave_Flg == 1)
	    {
	      Table_quee[tableId].counter--;
	      Table_quee[tableId].Slave_Flg = 0;
	    }
	  if ((Table_quee[tableId].Master_Flg == 1)
	      && (Table_quee[tableId].counter > 0))
	    {
	      if ((Table_quee[tableId].unlockbuf_1 == NULL)
		  && (Table_quee[tableId].unlockbuf_2 == NULL))
		{
		  /*Case:1 No unlock stored */
		  for (cnt = 1; cnt <= Table_quee[tableId].counter; cnt++)
		    {
		      updateLockAckFlagON (tableId, cnt);	/*Note::updating LockAck Flags on TCP break incase if no LOCK ACK is received for a lock in buffer/given to Peer GCS */
		    }
		}
	      else if ((Table_quee[tableId].unlockbuf_1 != NULL)
		       || (Table_quee[tableId].unlockbuf_2 != NULL))
		{

		  /*Case:2 Either of unlock is stored */
		  if (Table_quee[tableId].unlockbuf_1 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }
		  if (Table_quee[tableId].unlockbuf_2 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }

		}
	    }
	}
      else
	{
	  /* In case of SLAVE STUB */
	  if (Table_quee[tableId].Master_Flg == 1)
	    {
	      Table_quee[tableId].counter--;
	      Table_quee[tableId].Master_Flg = 0;
	    }
	  if ((Table_quee[tableId].Slave_Flg == 1)
	      && (Table_quee[tableId].counter > 0))
	    {
	      if ((Table_quee[tableId].unlockbuf_1 == NULL)
		  && (Table_quee[tableId].unlockbuf_2 == NULL))
		{
		  /*Case:1 No unlock stored */
		  for (cnt = 1; cnt <= Table_quee[tableId].counter; cnt++)
		    {
		      updateLockAckFlagON (tableId, cnt);
		    }
		}
	      else if ((Table_quee[tableId].unlockbuf_1 != NULL)
		       || (Table_quee[tableId].unlockbuf_2 != NULL))
		{

		  /*Case:2 Either of unlock is stored */
		  if (Table_quee[tableId].unlockbuf_1 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }
		  if (Table_quee[tableId].unlockbuf_2 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }

		}

	    }
	}
      if (Table_quee[tableId].un_1_flag == 1)
	{
	  Table_quee[tableId].un_1_flag = 0;
	  Table_quee[tableId].counter--;
	}
      else if (Table_quee[tableId].un_2_flag == 1)
	{
	  Table_quee[tableId].un_2_flag = 0;
	  Table_quee[tableId].counter--;

	}
      else if (Table_quee[tableId].un_3_flag == 1)
	{
	  Table_quee[tableId].un_3_flag = 0;
	  Table_quee[tableId].counter--;

	}
      else if (Table_quee[tableId].un_4_flag == 1)
	{
	  Table_quee[tableId].un_4_flag = 0;
	  Table_quee[tableId].counter--;

	}


    }

}
void
MessageRetrieve_ON_SYNC_TCP_break ()
{
  unsigned int tableId = 0, cnt = 0;
  int len, ret_3;
  char *buf = NULL;

  for (tableId = 0; tableId < 50; tableId++)
    {
      if (Table_quee[tableId].buf)
	{
	  len = Table_quee[tableId].Len;
	  buf = Table_quee[tableId].buf;
	  if (UNIX_SMbox > 0)
	    {
	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox failed ::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf)
		{
		  free (Table_quee[tableId].buf);
		  Table_quee[tableId].buf = NULL;
		  Table_quee[tableId].Len = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::I SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_1)
	{
	  len = Table_quee[tableId].Len_1;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_1;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
              LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox failed ::ERROR\n");
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_1)
		{
		  free (Table_quee[tableId].buf_1);
		  Table_quee[tableId].buf_1 = NULL;
		  Table_quee[tableId].Len_1 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::II SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_2)
	{
	  len = Table_quee[tableId].Len_2;
	  //GCSUTIL_DEBUG_TRACE(("MessageRetFromLockque:MSG LEN %d\n",len));
	  buf = NULL;
	  buf = Table_quee[tableId].buf_2;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break:send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_2)
		{
		  free (Table_quee[tableId].buf_2);
		  Table_quee[tableId].buf_2 = NULL;
		  Table_quee[tableId].Len_2 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::III SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_3)
	{
	  len = Table_quee[tableId].Len_3;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_3;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_3)
		{
		  free (Table_quee[tableId].buf_3);
		  Table_quee[tableId].buf_3 = NULL;
		  Table_quee[tableId].Len_3 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::IV SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_4)
	{
	  len = Table_quee[tableId].Len_4;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_4;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_4)
		{
		  free (Table_quee[tableId].buf_4);
		  Table_quee[tableId].buf_4 = NULL;
		  Table_quee[tableId].Len_4 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::V SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}
      if (Table_quee[tableId].buf_5)
	{
	  len = Table_quee[tableId].Len_5;
	  buf = NULL;
	  buf = Table_quee[tableId].buf_5;
	  if (UNIX_SMbox > 0)
	    {

	      /*Towards Stacks send */
	      ret_3 = send (UNIX_SMbox, buf, len, 0);
	      if (ret_3 <= 0)
		{
		  LOG_PRINT_CRITICAL
		    ("MessageRetrieve_ON_SYNC_TCP_break: send_UNIX_SMbox failed::ERROR\n");
		  close (UNIX_SMbox);
		  UNIX_SMbox = 0;
		  pthread_cancel (Recvhread);
          Recvhread = 0;
		}
                if(ret_3 != len)
                {
                     LOG_PRINT_CRITICAL("MessageRetrieve_ON_SYNC_TCP_break: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                }
	      if (Table_quee[tableId].buf_5)
		{
		  free (Table_quee[tableId].buf_5);
		  Table_quee[tableId].buf_5 = NULL;
		  Table_quee[tableId].Len_5 = 0;
		}
	    }
	  Table_quee[tableId].state = 1;
	  Table_quee[tableId].counter++;	/*Incrementing the counter for lock which was stored before sync lock as this lock will not be received again from stack */
	  if (MASTER)
	    {
	      Table_quee[tableId].Master_Flg = 1;
	    }
	  else
	    {
	      Table_quee[tableId].Slave_Flg = 1;
	    }
	      LOG_PRINT_MAJOR("TOSTACK:MessageRetrieve_ON_SYNC_TCP_break::VI SelfSend TbId[%d] len[%d] S[%d] M[%d] C[%d] State[%d]\n",tableId,len,Table_quee[tableId].Slave_Flg,Table_quee[tableId].Master_Flg,Table_quee[tableId].counter,Table_quee[tableId].state);
	}

      if (MASTER)
	{
	  /* In case of MASTER STUB */
	  if (Table_quee[tableId].Slave_Flg == 1)
	    {
	      Table_quee[tableId].counter--;
	      Table_quee[tableId].Slave_Flg = 0;
	    }
	  if ((Table_quee[tableId].Master_Flg == 1)
	      && (Table_quee[tableId].counter > 0))
	    {
	      if ((Table_quee[tableId].unlockbuf_1 == NULL)
		  && (Table_quee[tableId].unlockbuf_2 == NULL))
		{
		  /*Case:1 No unlock stored */
		  for (cnt = 1; cnt <= Table_quee[tableId].counter; cnt++)
		    {
		      updateLockAckFlagON (tableId, cnt);	/*Note::updating LockAck Flags on TCP break incase if no LOCK ACK is received for a lock in buffer/given to Peer GCS */
		    }
		}
	      else if ((Table_quee[tableId].unlockbuf_1 != NULL)
		       || (Table_quee[tableId].unlockbuf_2 != NULL))
		{

		  /*Case:2 Either of unlock is stored */
		  if (Table_quee[tableId].unlockbuf_1 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }
		  if (Table_quee[tableId].unlockbuf_2 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }

		}
	    }
	}
      else
	{
	  /* In case of SLAVE STUB */
	  if (Table_quee[tableId].Master_Flg == 1)
	    {
	      Table_quee[tableId].counter--;
	      Table_quee[tableId].Master_Flg = 0;
	    }
	  if ((Table_quee[tableId].Slave_Flg == 1)
	      && (Table_quee[tableId].counter > 0))
	    {
	      if ((Table_quee[tableId].unlockbuf_1 == NULL)
		  && (Table_quee[tableId].unlockbuf_2 == NULL))
		{
		  /*Case:1 No unlock stored */
		  for (cnt = 1; cnt <= Table_quee[tableId].counter; cnt++)
		    {
		      updateLockAckFlagON (tableId, cnt);
		    }
		}
	      else if ((Table_quee[tableId].unlockbuf_1 != NULL)
		       || (Table_quee[tableId].unlockbuf_2 != NULL))
		{

		  /*Case:2 Either of unlock is stored */
		  if (Table_quee[tableId].unlockbuf_1 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }
		  if (Table_quee[tableId].unlockbuf_2 != NULL)
		    {
		      setLockAckFlagOFF (tableId);
		      processUnlockOnTCPbreak (tableId);

		    }

		}

	    }
	}

    }




}
void
updateLockAckFlagON (int tableId, int opt)
{
  switch (opt)
    {
    case 1:
      Table_quee[tableId].Lock_Ack_Flag = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] I Flag SET \n",tableId));
      break;
    case 2:
      Table_quee[tableId].Lock_Ack_Flag_1 = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] II Flag SET \n",tableId));
      break;
    case 3:
      Table_quee[tableId].Lock_Ack_Flag_2 = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] III Flag SET \n",tableId));
      break;
    case 4:
      Table_quee[tableId].Lock_Ack_Flag_3 = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] IV Flag SET \n",tableId));
      break;
    case 5:
      Table_quee[tableId].Lock_Ack_Flag_4 = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] V Flag SET \n",tableId));
      break;
    case 6:
      Table_quee[tableId].Lock_Ack_Flag_5 = 1;
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: TableID[%d] VI Flag SET \n",tableId));
      break;
    default:
      //GCSUTIL_DEBUG_TRACE(("updateLockAckFlagON:: INVALID OPTION \n"));
      break;
    }
}
void
processUnlockOnTCPbreak (int tableId)
{
  DSM_Message *msg = NULL;
  int ret_3 = 0, len = 0;
  if (Table_quee[tableId].unlockbuf_1 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[tableId].unlockLen_1;
      memcpy (bufUnlock, Table_quee[tableId].unlockbuf_1, len);
      Table_quee[tableId].unlockLen_1 = 0;
      free (Table_quee[tableId].unlockbuf_1);
      Table_quee[tableId].unlockbuf_1 = NULL;
    }
  else if (Table_quee[tableId].unlockbuf_2 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[tableId].unlockLen_2;
      memcpy (bufUnlock, Table_quee[tableId].unlockbuf_2, len);
      Table_quee[tableId].unlockLen_2 = 0;
      free (Table_quee[tableId].unlockbuf_2);
      Table_quee[tableId].unlockbuf_2 = NULL;
    }


  msg = (DSM_Message *) & bufUnlock;
  print_tid (msg);

  if (Table_quee[tableId].counter > 0)
    {
      Table_quee[tableId].counter--;
    }
  if (Table_quee[tableId].counter == 0)
    {
      Table_quee[tableId].state = 0;
      if (MASTER)
	{
	  Table_quee[tableId].Master_Flg = 0;
	}
      else
	{
	  Table_quee[tableId].Slave_Flg = 0;
	}
    }
  /*Towards GCS send */
  if (((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0)) && (syncFlag == 0))
    {
      ret_3 = send (TcpClient, bufUnlock, len, 0);
      if (ret_3 <= 0)
	{
	  //close (TcpClient);
	 // TcpClient = 0;
      //PEER_ALRD_JOIN=0;
          MUTEX_ReleaseMutex (&FlagLock);
          PEER_Leave();

	}
      GCSUTIL_DEBUG_TRACE (("TOGCS:processUnlockOnTCPbreak::PeerGCSSend %d\n", len));
    }
  ret_3 = send (UNIX_SMbox, bufUnlock, len, 0);
  if (ret_3 <= 0)
    {
      close (UNIX_SMbox);
      UNIX_SMbox = 0;
      pthread_cancel (Recvhread);
          Recvhread = 0;
    }
   if(ret_3 != len)
   {
       LOG_PRINT_CRITICAL("TOSTACK:processUnlockOnTCPbreak: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
   }
  GCSUTIL_DEBUG_TRACE (("TOSTACK:processUnlockOnTCPbreak::SelfSend %d\n", len));


}


/*UNIX BREAK THEN CLEAR THE ALL MESSAGE QUEES AND UPDATE THE FLAGS	*/
void
MessageClearFromLockque ()
{
  unsigned int tableId = 0;
  //int len;
  //char buf[8192];

  for (tableId = 0; tableId < 50; tableId++)
    {
      MUTEX_AcquireMutex (&FlagLock);
      if (MASTER)
	{
	  Table_quee[tableId].Master_Flg = 0;
	}
      else
	{
	  Table_quee[tableId].Slave_Flg = 0;
	}

      if (Table_quee[tableId].counter > 0)
	{
	  Table_quee[tableId].counter = 0;
	}
      if (Table_quee[tableId].buf)
	{
	  free (Table_quee[tableId].buf);
	  Table_quee[tableId].buf = NULL;
	  Table_quee[tableId].Len = 0;

	}
      if (Table_quee[tableId].buf_1)
	{
	  free (Table_quee[tableId].buf_1);
	  Table_quee[tableId].buf_1 = NULL;
	  Table_quee[tableId].Len = 0;

	}
      if (Table_quee[tableId].buf_2)
	{
	  free (Table_quee[tableId].buf_2);
	  Table_quee[tableId].buf_2 = NULL;
	  Table_quee[tableId].Len = 0;

	}
      if (Table_quee[tableId].buf_3)
	{
	  free (Table_quee[tableId].buf_3);
	  Table_quee[tableId].buf_3 = NULL;
	  Table_quee[tableId].Len = 0;

	}
      if (Table_quee[tableId].buf_4)
	{
	  free (Table_quee[tableId].buf_4);
	  Table_quee[tableId].buf_4 = NULL;
	  Table_quee[tableId].Len = 0;

	}
      if (Table_quee[tableId].buf_5)
	{
	  free (Table_quee[tableId].buf_5);
	  Table_quee[tableId].buf_5 = NULL;
	  Table_quee[tableId].Len = 0;

	}
      MUTEX_ReleaseMutex (&FlagLock);
    }
}
void
GetSocketOption (int fd)
{
  unsigned int on;
  socklen_t onlen;
  int ret;

   onlen = sizeof (on);
      ret = getsockopt (fd, SOL_SOCKET, SO_SNDBUF, (void *) &on, &onlen);
      if (ret < 0)
      {
        LOG_PRINT_CRITICAL("getsockopt SNDBUF error %d\n",ret);
      }
        LOG_PRINT_CRITICAL("getsockopt SNDBUF size [%d]  \n",on);
      ret = getsockopt (fd, SOL_SOCKET, SO_RCVBUF, (void *) &on, &onlen);
      if (ret < 0)
      {
        LOG_PRINT_CRITICAL("getsockopt SNDBUF error %d\n",ret);
      }
        LOG_PRINT_CRITICAL("getsockopt:: RCVBUF set size [%d]  \n",on);
}
void
SocketOption (int fd)
{
  unsigned int on;
  //int i;
  socklen_t onlen;
  //int optval;
  int ret ;
  struct linger linger;
  linger.l_onoff = 1;
  linger.l_linger = 0;

  on=1024 *200;
   onlen = sizeof (on);
      ret = setsockopt (fd, SOL_SOCKET, SO_SNDBUF, (void *) &on, onlen);
      if (ret < 0)
      {
        LOG_PRINT_CRITICAL("setsockopt SO_SNDBUF error %d\n",ret);
      }
      ret = setsockopt (fd, SOL_SOCKET, SO_RCVBUF, (void *) &on, onlen);
      if (ret < 0)
      {
        LOG_PRINT_CRITICAL("setsockopt SO_SNDBUF error %d\n",ret);
      }
      if(setsockopt(fd, SOL_SOCKET, SO_LINGER, (I_Void *)&linger,
             sizeof(linger)) < 0)
      {
         LOG_PRINT_CRITICAL("setsockopt: SO_LINGER System call Failed (errno = %d)",errno);
      }
      LOG_PRINT_CRITICAL("setsockopt: SO_LINGER set successfully for Fd[%d]",fd);
#if 0
  for (i = 10; i <= 200; i += 5)
    {
      on = 1024 * i;
      onlen = sizeof (on);

      ret = setsockopt (fd, SOL_SOCKET, SO_SNDBUF, (void *) &on, onlen);
      if (ret < 0)
	break;

      ret = setsockopt (fd, SOL_SOCKET, SO_RCVBUF, (void *) &on, onlen);
      if (ret < 0)
	break;

      ret = getsockopt (fd, SOL_SOCKET, SO_SNDBUF, (void *) &on, &onlen);
      if (on < i * 1024)
	break;
      //      //GCSUTIL_DEBUG_TRACE(("Sess_accept: set sndbuf %d, ret is %d\n", on, ret ));

      onlen = sizeof (on);
      ret = getsockopt (fd, SOL_SOCKET, SO_RCVBUF, (void *) &on, &onlen);
      if (on < i * 1024)
	break;
      //     //GCSUTIL_DEBUG_TRACE(( "Sess_accept: set rcvbuf %d, ret is %d\n", on, ret ));
    }
  //GCSUTIL_DEBUG_TRACE(("SocketOption: set sndbuf/rcvbuf to %d\n", 1024*(i-5) ));
//    LOG_PRINT_CRITICAL("Sucessfuly exit from 200 loop\n");

  /*        KEEP ALIVE TIMEOUT FOR TCP START HERE     */
  {
    onlen = sizeof (optval);
    //LOG_PRINT_CRITICAL("Before getsockopt %d \n", __LINE__);
    if (getsockopt (fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &onlen) < 0)
      {
	     perror ("getsockopt()");
	     close (fd);
      }
  //  LOG_PRINT_CRITICAL("After getsockopt %d \n", __LINE__);
    //printf ("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

    /* Set the option active */
    optval = 1;
    //LOG_PRINT_CRITICAL("Before setsockopt %d \n", __LINE__);
    if (setsockopt (fd, SOL_SOCKET, SO_KEEPALIVE, &optval, onlen) < 0)
      {
	     perror ("setsockopt()");
	     close (fd);
      }
    //LOG_PRINT_CRITICAL("After setsockopt %d \n", __LINE__);
    //printf ("SO_KEEPALIVE set on socket\n");

    //LOG_PRINT_CRITICAL("Before getsockopt %d \n", __LINE__);
    /* Check the status again */
    if (getsockopt (fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &onlen) < 0)
      {
	     perror ("getsockopt()");
	     close (fd);
      }
   // LOG_PRINT_CRITICAL("After getsockopt %d \n", __LINE__);
    //printf ("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
  }
  /*        KEEP ALIVE TIMEOUT FOR TCP END HERE     */

#endif
}
void SetKeepAliveOption(int fd)
{
  socklen_t optlen;
  int optval = 0;
//  LOG_PRINT_CRITICAL("ENTERING SetKeepAliveOption\n");
  //int getval = 0;
#if 0
  /* Check the status for the keepalive option */
  if(getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &getval, &optlen) < 0) {
  perror("getsockopt()");
  close(fd);
  }
#endif
//  LOG_PRINT_CRITICAL("1. SO_KEEPALIVE is %s\n", (getval ? "ON" : "OFF"));

  /* Set the option active */
  optval = 1;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
  perror("setsockopt()");
  LOG_PRINT_CRITICAL ("SetKeepAliveOption:setsockopt() SO_KEEPALIVE failed : CLOSING FD[%d] \n",fd);
  close(fd);
  }
//  LOG_PRINT_CRITICAL("2. SO_KEEPALIVE set on socket\n");

  optval = 2;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPCNT, &optval, optlen) < 0) {
  perror("setsockopt()");
  LOG_PRINT_CRITICAL ("SetKeepAliveOption:setsockopt() TCP_KEEPCNT failed : CLOSING FD[%d] \n",fd);
  close(fd);
  }
//  LOG_PRINT_CRITICAL("3. TCP_KEEPCNT set on socket\n");

  optval = 5;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &optval, optlen) < 0) {
  perror("setsockopt()");
  LOG_PRINT_CRITICAL ("SetKeepAliveOption:setsockopt() TCP_KEEPIDLE failed : CLOSING FD[%d] \n",fd);
  close(fd);
  }
// LOG_PRINT_CRITICAL("4. TCP_KEEPIDLE set on socket\n");

  optval = 2;
  optlen = sizeof(optval);
  if(setsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &optval, optlen) < 0) {
  perror("setsockopt()");
  LOG_PRINT_CRITICAL ("SetKeepAliveOption:setsockopt() TCP_KEEPINTVL failed : CLOSING FD[%d] \n",fd);
  close(fd);
  }
//  LOG_PRINT_CRITICAL("5. TCP_KEEPINTVL set on socket\n");

#if 0
  /* Check the status again */
  if(getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &getval, &optlen) < 0) {
  perror("getsockopt()");
  close(fd);
  }
  //LOG_PRINT_CRITICAL("6. SO_KEEPALIVE is %s\n", (getval ? "ON" : "OFF"));

  if(getsockopt(fd, SOL_TCP, TCP_KEEPCNT, &getval, &optlen) < 0) {
  perror("getsockopt()");
  close(fd);
  }
  //LOG_PRINT_CRITICAL("7. TCP_KEEPCNT is %d\n", getval );

  if(getsockopt(fd, SOL_TCP, TCP_KEEPIDLE, &getval, &optlen) < 0) {
  perror("getsockopt()");
  close(fd);
  }
  //LOG_PRINT_CRITICAL("8. TCP_KEEPIDLE is %d\n", getval );
  if(getsockopt(fd, SOL_TCP, TCP_KEEPINTVL, &getval, &optlen) < 0) {
  perror("getsockopt()");
  close(fd);
  }
#endif
  //LOG_PRINT_CRITICAL("9. TCP_KEEPINTVL is %d\n", getval );
  
  /*        KEEP ALIVE TIMEOUT FOR TCP END HERE     */
//  LOG_PRINT_CRITICAL("EXIT SetKeepAliveOption\n");
}

void
termination_handler (int signum)
{
  //GCSUTIL_DEBUG_TRACE(("----CATCHED AGAIN SIGNAL-------\n"));
  //GCSUTIL_DEBUG_TRACE(("----CALLING SHUTDOWN-------\n"));

  shutdown (TcpClient, SHUT_RDWR);	/*Closing TCP receive server Fd */
  //abort();
  (void) signal (SIGINT, SIG_DFL);
  DeallocateGlobalbuffers(); 
  abort ();
}

void
print_tid (DSM_Message * msg)
{
  int tableId = 0, tid = 0;
  int size = 0;
  switch (msg->discriminator)
    {
    case DSM_MSG_ALLOCATE_ROW:
      //      GCSUTIL_DEBUG_TRACE(("DSM_MSG_ALLOCATE_ROW\n"));
      tableId = msg->u.allocateRow.tableId;
      tid = msg->u.allocateRow.tid;
      size = msg->u.allocateRow.size;
  GCSUTIL_DEBUG_TRACE (("MESSAGE ALLOC RECEIVED Disc [%d] Table [%d] Tid [%d] MSGSize[%d]\n",
			msg->discriminator, tableId, tid,size));
      break;
    case DSM_MSG_FIND_ROW:
      //GCSUTIL_DEBUG_TRACE(("DSM_MSG_FIND_ROW\n"));
      tableId = msg->u.findRow.tableId;
      tid = msg->u.findRow.tid;
  GCSUTIL_DEBUG_TRACE (("MESSAGE FIND RECEIVED Disc [%d] Table [%d] Tid [%d] \n",
			msg->discriminator, tableId, tid));
      break;
    case DSM_MSG_FREE_ROW:
      //GCSUTIL_DEBUG_TRACE((" DSM_MSG_FREE_ROW\n"));
      tableId = msg->u.freeRow.tableId;
      tid = msg->u.freeRow.tid;
  GCSUTIL_DEBUG_TRACE (("MESSAGE FREE RECEIVED Disc [%d] Table [%d] Tid [%d] \n",
			msg->discriminator, tableId, tid));
      break;
    case DSM_MSG_COMMIT_ROW:
      //              GCSUTIL_DEBUG_TRACE(("DSM_MSG_COMMIT_ROW\n"));
      tableId = msg->u.commitRow.tableId;
      tid = msg->u.commitRow.tid;
      size = msg->u.commitRow.size;
  GCSUTIL_DEBUG_TRACE (("MESSAGE COMMIT RECEIVED Disc [%d] Table [%d] Tid [%d] MSGSize[%d]\n",
			msg->discriminator, tableId, tid,size));
      break;
    case DSM_MSG_LOCK_UNLOCK_TABLE:
     // GCSUTIL_DEBUG_TRACE (("DSM_MSG_LOCK_UNLOCK_TABLE :Toggle table Id %d Flag[%d]\n", msg->u.lockUnlockTable.tableId, msg->u.lockUnlockTable.lockUnlockToggle));
      tableId = msg->u.lockUnlockTable.tableId;
      tid = msg->u.lockUnlockTable.tid;
  GCSUTIL_DEBUG_TRACE (("MESSAGE LOCKUNLOCK RECEIVED Disc [%d] Table [%d] Tid [%d] \n",
			msg->discriminator, tableId, tid));
      break;

    default:
      break;
    }
}

void Clearing()
{
/***********FD CLEARING***************/

    LOG_PRINT_CRITICAL("RESOURSES CLEARING in clearing Func: \n");
      if(UNIX_SMbox != 0)
      {
        close (UNIX_SMbox);
        UNIX_SMbox = 0;
      }
      if(tcp_listener!=0)
      { 
        LOG_PRINT_CRITICAL ("Clearing :tcp_listener: CLOSING FD[%d] \n",tcp_listener);
        close (tcp_listener);
        tcp_listener = 0;
      }
      if(udp_listener!=0)
      { 
        LOG_PRINT_CRITICAL ("Clearing :udp_listener: CLOSING FD[%d] \n",udp_listener);
        close (udp_listener);
        udp_listener = 0;
      }
      if(TcpClient != 0)
      {
        LOG_PRINT_CRITICAL ("Clearing :TcpClient: CLOSING FD[%d] \n",TcpClient);
        close (TcpClient);
        TcpClient = 0;
        PEER_ALRD_JOIN=0;
      }
      if(TcpServer != 0)
      {
        LOG_PRINT_CRITICAL ("Clearing :TcpServer: CLOSING FD[%d] \n",TcpServer);
        close (TcpServer);
        TcpServer = 0;
        PEER_ALRD_JOIN=0;
      }
      if(sockfd_udp != 0)
      {
        LOG_PRINT_CRITICAL ("Clearing :sockfd_udp: CLOSING FD[%d] \n",sockfd_udp);
        close (sockfd_udp);
        sockfd_udp=0;
      }
      if(sockfd_udp_client != 0)
      {
        LOG_PRINT_CRITICAL ("Clearing :sockfd_udp_client: CLOSING FD[%d] \n",sockfd_udp_client);
        close (sockfd_udp_client);
        sockfd_udp_client = 0;
      }

/**************************************/
/********THREAD CLEARING**************/
      
      if(Recvhread != 0)
      {	  
         pthread_cancel (Recvhread);
          Recvhread = 0;
      }
#if 0			
      if(UDPRecvThread != 0)
      {	  
          pthread_cancel (UDPRecvThread);
          UDPRecvThread = 0;
      }
      if(TcpRecvThread != 0)
      {	  
	       pthread_cancel (TcpRecvThread); 
         TcpRecvThread = 0; 
      }
#endif			
/* Added to clear TCPCLIENT and UDP CLIENT 04-sept-2014*/
      if(TcpClientThread != 0)
      {	  
          pthread_cancel (TcpClientThread);
          TcpClientThread = 0;
      }
      if(UDPClientThread != 0)
      {	  
	       pthread_cancel (UDPClientThread); 
         UDPClientThread = 0; 
      }
/* Added to clear TCPCLIENT and UDP CLIENT 04-sept-2014*/
	  
/**************************************/
    LOG_PRINT_CRITICAL("RESOURSES CLEARING END\n");
}

void
PEER_Leave()
{
    /***********FD CLEARING***************/
    LOG_PRINT_CRITICAL("PEER_Leave:: RESOURSES CLEARING in PEER Leave Func:\n");
    if(LEAVE_PEER == 0)
    {
      CLIENT_RETRY_FLAG = 1;
      LEAVE_PEER = 1;
      DONT_ALLOW = 1;
     
      PEER_ALRD_JOIN = 0;
      if(TcpClient != 0)
      {
        LOG_PRINT_CRITICAL ("PEER_Leave :TcpClient: CLOSING FD[%d] \n",TcpClient);
        close (TcpClient);
        TcpClient = 0;
        PEER_ALRD_JOIN=0;
      }
      if(TcpServer != 0)
      {
        LOG_PRINT_CRITICAL ("PEER_Leave :TcpServer: CLOSING FD[%d] \n",TcpServer);
        close (TcpServer);
        TcpServer = 0;
      PEER_ALRD_JOIN=0;
      }	 
      if(sockfd_udp != 0)
      {
        LOG_PRINT_CRITICAL ("PEER_Leave :sockfd_udp: CLOSING FD[%d] \n",sockfd_udp);
        close (sockfd_udp);
        sockfd_udp=0;
      }
      if(sockfd_udp_client != 0)
      {
        LOG_PRINT_CRITICAL ("PEER_Leave :sockfd_udp_client: CLOSING FD[%d] \n",sockfd_udp_client);
        close (sockfd_udp_client);
        sockfd_udp_client = 0;
      }
        LOG_PRINT_CRITICAL("PEER_Leave:: UNIX_SMbox[%d] \n",UNIX_SMbox);
    if((UNIX_SMbox > 0) && (PEER_NODE_UP == 1))
    {
        LOG_PRINT_CRITICAL("PEER_Leave:: SENDING NETWORK CHANGE ON PEER LEAVE \n");
/*Sending Network change to Self when peer node leave*/
          SendNetworkChangeLeaveMsg();
     PEER_NODE_UP = 0;
    }
 /***********Setting syncflag to 1 & sending any lock stored to stack******************/
/*This is done if tcp connection break is not detected at tcp recv ,
 the any lock if got stored then can retreive and send to stack from here*/
    if(syncFlag == 2)
    {
        LOG_PRINT_CRITICAL("PEER_Leave:: MUTEX_AcquireMutex 1 syncFlag =2\n");
        MUTEX_AcquireMutex (&FlagLock);
        LOG_PRINT_CRITICAL("PEER_Leave:: MUTEX_AcquireMutex 2 syncFlag =2\n");
        MessageRetrieve_ON_SYNC_TCP_break ();
        syncFlag = 1;
        LOG_PRINT_CRITICAL("PEER_Leave:: setting syncFlag to 1 before SYNC  UNLOCK :: syncFlag[%d]\n",syncFlag);
        MUTEX_ReleaseMutex (&FlagLock);
    }
    else if(syncFlag == 0)
    {
       LOG_PRINT_CRITICAL("PEER_Leave:: MUTEX_AcquireMutex 1 syncFlag =0\n");
       MUTEX_AcquireMutex (&FlagLock);
       LOG_PRINT_CRITICAL("PEER_Leave:: MUTEX_AcquireMutex 2 syncFlag =0\n");
       syncFlag = 1;
       LOG_PRINT_CRITICAL("PEER_Leave:: setting syncFlag and check for any lock stored:: syncFlag[%d]\n",syncFlag);
       MessageRetFromLockque ();
       MUTEX_ReleaseMutex (&FlagLock);
    }
    else
      {
       MUTEX_AcquireMutex (&FlagLock);
       MUTEX_ReleaseMutex (&FlagLock);
       LOG_PRINT_CRITICAL("PEER_Leave:: syncFlag Invalid\n");
      }
/**************************************/
#if 0/********THREAD CLEARING**************/
      if(UDPRecvThread != 0)
      {	  
 	      pthread_cancel (UDPRecvThread);
         UDPRecvThread = 0;
        LOG_PRINT_CRITICAL("PEER_Leave:: CANCELLED UDPRecvThread\n"); 
      }
      if(TcpRecvThread != 0)
      {	  
         pthread_cancel (TcpRecvThread);
         TcpRecvThread = 0;
        LOG_PRINT_CRITICAL("PEER_Leave:: CANCELLED TcpRecvThread \n");
      }
#endif			
/**************************************/
			LOG_PRINT_CRITICAL("PEER_Leave:: RESOURCE CLEAR SUCCESS \n");
   }
}

void
print_ppc_context (ucontext_t * uc)
{
  unsigned int i = 0;
#if 0
  for (i = 0; i < 32; i++)
    {
      LOG_PRINT_CRITICAL("R%d [0x%x] [%u]",i,uc->uc_mcontext.regs->gpr[i],uc->uc_mcontext.regs->gpr[i]);
    }
  LOG_PRINT_CRITICAL("NIP       [0x%x] [%u]",uc->uc_mcontext.regs->nip,uc->uc_mcontext.regs->nip);
  LOG_PRINT_CRITICAL("MSR       [0x%x] [%u]",uc->uc_mcontext.regs->msr,uc->uc_mcontext.regs->msr);
  LOG_PRINT_CRITICAL("ORIG_GPR3 [0x%x] [%u]",uc->uc_mcontext.regs->orig_gpr3,uc->uc_mcontext.regs->orig_gpr3);
  LOG_PRINT_CRITICAL("CTR       [0x%x] [%u]",uc->uc_mcontext.regs->ctr,uc->uc_mcontext.regs->ctr);
  LOG_PRINT_CRITICAL("LINK      [0x%x] [%u]",uc->uc_mcontext.regs->link,uc->uc_mcontext.regs->link);
  LOG_PRINT_CRITICAL("XER       [0x%x] [%u]",uc->uc_mcontext.regs->xer,uc->uc_mcontext.regs->xer);
  LOG_PRINT_CRITICAL("CCR       [0x%x] [%u]",uc->uc_mcontext.regs->ccr,uc->uc_mcontext.regs->ccr);
  LOG_PRINT_CRITICAL("MQ        [0x%x] [%u]",uc->uc_mcontext.regs->mq,uc->uc_mcontext.regs->mq);
#endif
}


void
printBackTrace (ucontext_t * uc)
{
  void *BackTrace[BACK_TRACE_DEPTH];
  char **messages = (char **) NULL;
  int i, BackTraceSize = 0;

  BackTraceSize = backtrace (BackTrace, BACK_TRACE_DEPTH);

  /* overwrite sigaction with caller's address */
#if 0
  if (uc)
    {
      BackTrace[2] = (void *) uc->uc_mcontext.regs->nip;
      BackTrace[3] = (void *) uc->uc_mcontext.regs->link;
    }
#endif

  messages = backtrace_symbols (BackTrace, BackTraceSize);
  /* skip first stack frame (points here) */

  LOG_PRINT_CRITICAL("[bt] Execution path:");

  for (i = 2; i < BackTraceSize; ++i)
    {
      LOG_PRINT_CRITICAL("[bt]#[%u]->%s",i-2,messages[i]);
    }
}
void
bsc_sighandler (int signum, siginfo_t * sig_info, void *secret)
{
  ucontext_t *uc = (ucontext_t *) secret;

  LOG_PRINT_CRITICAL("Got Signal [%d] [%s]",signum,strsignal(signum));

  if (signum == SIGSEGV)
    {
      LOG_PRINT_CRITICAL("SIGSEGV Faulty Address is [%p]",sig_info->si_addr);
    }

  print_ppc_context (uc);
  printBackTrace (uc);
  printf("\n");
 //LOG_PRINT_CRITICAL("\n");

  Clearing();
/*
  signal (signum, SIG_DFL);

  kill (getpid (), signum);
  kill (0, 9);
*/
  LOG_PRINT(CRITICAL," System kill Api Fail so exiting by itself\n");
  LOG_PRINT(CRITICAL," System kill Api Fail so exiting by itself\n");
  LOG_PRINT(CRITICAL," System kill Api Fail so exiting by itself\n");
  exit(0);
  return;
}


void
reg_sig_hndlr ()
{
  /* Install our signal handler */
  struct sigaction sa;

 LOG_PRINT_CRITICAL(" reg_sig_hndlr :: Entering for Capture SIGNAL\n");
  sa.sa_sigaction = bsc_sighandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction (SIGKILL, &sa, NULL);
  sigaction (SIGSEGV, &sa, NULL);
  sigaction (SIGFPE, &sa, NULL);
  sigaction (SIGABRT, &sa, NULL);
#if 0
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGSTOP, &sa, NULL);
  sigaction(SIGCONT, &sa, NULL);
  sigaction(SIGHUP, &sa, NULL);
  sigaction(SIGILL, &sa, NULL);
  sigaction(SIGQUIT, &sa, NULL);
#endif

  /* ... add any other signal here */

  return;
}

/***************************************************************************************************/
void
MessageRetFromLockque_Sync ()
{
  unsigned int tableId = 0;
  int len;
  char *buf = NULL;
  int ret_3 = 0;
  unsigned int tid = 0;
  DSM_Message *msg = NULL;


  for (tableId = 0; tableId < 50; tableId++)
    {
      if (Table_quee[tableId].buf)
	{
	  len = Table_quee[tableId].Len;
	  buf = Table_quee[tableId].buf;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
/* Patch: 2-june-10: Sending only own stored lock msg when permission with own GCS-UTIL[ in case of +ve Lock rsp or -ve unlock rsp from peer GCS-UTIL only*/
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0)&& (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync I: TCPClient send failed ret_3[%d]",
			 ret_3);
		      //close (TcpClient);
		     // TcpClient = 0;
                     //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync I: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		      // continue;
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync I: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf)
		    {
		      free (Table_quee[tableId].buf);
		      Table_quee[tableId].buf = NULL;
		      Table_quee[tableId].Len = 0;
		    }

		}

	     Table_quee[tableId].state = 1;
	    }
	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync I :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);
	}
      buf = NULL;
      if (Table_quee[tableId].buf_1)
	{
	  len = Table_quee[tableId].Len_1;
	  buf = Table_quee[tableId].buf_1;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync II: TCPClient send failed ret_3[%d]",
			 ret_3);
		      perror ("message_processing:TcpClientsend() failed ");
		      //close (TcpClient);
		      //TcpClient = 0;
                      //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		      //         continue;
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync II: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		      // continue;
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync II: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf_1)
		    {
		      free (Table_quee[tableId].buf_1);
		      Table_quee[tableId].buf_1 = NULL;
		      Table_quee[tableId].Len_1 = 0;
		    }
		}
	        Table_quee[tableId].state = 1;

	    }

	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync II :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);
	}
      buf = NULL;
      if (Table_quee[tableId].buf_2)
	{
	  len = Table_quee[tableId].Len_2;
	  buf = Table_quee[tableId].buf_2;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync III: TCPClient send failed ret_3[%d]",
			 ret_3);
		      perror ("message_processing:TcpClientsend() failed ");
		      //close (TcpClient);
		      //TcpClient = 0;
                      //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		      //         continue;
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync III: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		      // continue;
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync III: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf_2)
		    {
		      free (Table_quee[tableId].buf_2);
		      Table_quee[tableId].buf_2 = NULL;
		      Table_quee[tableId].Len_2 = 0;
		    }
		}
	       Table_quee[tableId].state = 1;

	    }
	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync III :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);

	}
      buf = NULL;
      if (Table_quee[tableId].buf_3)
	{
	  len = Table_quee[tableId].Len_3;
	  buf = Table_quee[tableId].buf_3;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync IV: TCPClient send failed ret_3[%d]",
			 ret_3);
		      perror ("message_processing:TcpClientsend() failed ");
		      //close (TcpClient);
		      //TcpClient = 0;
                      //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync IV: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		      // continue;
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync IV: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf_3)
		    {
		      free (Table_quee[tableId].buf_3);
		      Table_quee[tableId].buf_3 = NULL;
		      Table_quee[tableId].Len_3 = 0;
		    }
		}
	      Table_quee[tableId].state = 1;

	    }
	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync IV :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);

	}
      buf = NULL;
      if (Table_quee[tableId].buf_4)
	{
	  len = Table_quee[tableId].Len_4;
	  buf = Table_quee[tableId].buf_4;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync V: TCPClient send failed ret_3[%d]",
			 ret_3);
		      perror ("message_processing:TcpClientsend() failed ");
		      //close (TcpClient);
		      //TcpClient = 0;
                      //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync V: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync V: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf_4)
		    {
		      free (Table_quee[tableId].buf_4);
		      Table_quee[tableId].buf_4 = NULL;
		      Table_quee[tableId].Len_4 = 0;
		    }
		}
	      Table_quee[tableId].state = 1;

	    }

	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync V :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);
	}
      buf = NULL;
      if (Table_quee[tableId].buf_5)
	{
	  len = Table_quee[tableId].Len_5;
	  buf = Table_quee[tableId].buf_5;
	  msg = NULL;
	  msg = (DSM_Message *) & buf[80];
	  tid = msg->u.lockUnlockTable.tid;
	  //if( ((Table_quee[tableId].Master_Flg==1) || (Table_quee[tableId].Slave_Flg==1)) && (Table_quee[tableId].counter >0))
	  if ((((MASTER == 1) && (Table_quee[tableId].Master_Flg == 1))
	       || ((MASTER == 0) && (Table_quee[tableId].Slave_Flg == 1)))
	      && (Table_quee[tableId].counter > 0))
	    {
	      /*Towards GCS send */
	      if ((TcpClient > 0) && (TcpServer > 0) && (sockfd_udp > 0) && (sockfd_udp_client > 0))
		{
		  ret_3 = send (TcpClient, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync VI: TCPClient send failed ret_3[%d]",
			 ret_3);
		      perror ("message_processing:TcpClientsend() failed ");
		      //close (TcpClient);
		      //TcpClient = 0;
                      //PEER_ALRD_JOIN=0;
                      PEER_Leave();
		    }
		}
	      if (UNIX_SMbox > 0)
		{
		  /*Towards Stacks send */
		  ret_3 = send (UNIX_SMbox, buf, len, 0);
		  if (ret_3 <= 0)
		    {
		      LOG_PRINT_CRITICAL
			("MessageRetFromLockque_Sync VI: UNIX_SMbox send failed ret_3[%d]",
			 ret_3);
		      perror
			("MessageRetFromLockque_Sync:send_UNIX_SMbox() failed ");
		      close (UNIX_SMbox);
		      UNIX_SMbox = 0;
		      pthread_cancel (Recvhread);
		    }
                    if(ret_3 != len)
                     {
                           LOG_PRINT_CRITICAL("MessageRetFromLockque_Sync VI: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
                     }
		  if (Table_quee[tableId].buf_5)
		    {
		      free (Table_quee[tableId].buf_5);
		      Table_quee[tableId].buf_5 = NULL;
		      Table_quee[tableId].Len_5 = 0;
		    }
		}
	      Table_quee[tableId].state = 1;

	    }
	  LOG_PRINT_CRITICAL
	    ("MessageRetFromLockque_Sync VI :Lock Tid %d TbId %d M %d |S %d |C %d |state %d\n",
	     tid, tableId, Table_quee[tableId].Master_Flg,
	     Table_quee[tableId].Slave_Flg, Table_quee[tableId].counter,
	     Table_quee[tableId].state);
	}
      /*Retreiving unlock incase if stored */
      if ((Table_quee[tableId].unlockbuf_1 != NULL))
	{
	  RetriveUnlock_ONSyncUnlock (tableId);
	}
      if ((Table_quee[tableId].unlockbuf_2 != NULL))
	{
	  RetriveUnlock_ONSyncUnlock (tableId);
	}
    }

}



/***********************Retrive Unlock on Sync Unlock From Peer*********************/
void
RetriveUnlock_ONSyncUnlock (int Table_Id)
{
  unsigned int len = 0;
  int ret_3 = 0;


  if (Table_quee[Table_Id].unlockbuf_1 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[Table_Id].unlockLen_1;
      memcpy (bufUnlock, Table_quee[Table_Id].unlockbuf_1, len);
      Table_quee[Table_Id].unlockLen_1 = 0;
      free (Table_quee[Table_Id].unlockbuf_1);
      Table_quee[Table_Id].unlockbuf_1 = NULL;
      if (Table_quee[Table_Id].un_1_flag == 0)
	{
	  Table_quee[Table_Id].un_1_flag = 1;
	}
      else
	{
	  if (Table_quee[Table_Id].un_2_flag == 0)
	    {
	      Table_quee[Table_Id].un_2_flag = 1;
	    }
	  else
	    {
	      if (Table_quee[Table_Id].un_3_flag == 0)
		{
		  Table_quee[Table_Id].un_3_flag = 1;
		}
	      else
		{
		  if (Table_quee[Table_Id].un_4_flag == 0)
		    {
		      Table_quee[Table_Id].un_4_flag = 1;
		    }
		  else
		    {
		      GCSUTIL_DEBUG_TRACE (("FROMSTACK :More Than Two UNLOCK REC\n"));
		    }
		}
	    }
	}
    }
  else if (Table_quee[Table_Id].unlockbuf_2 != NULL)
    {
      memset (bufUnlock, 0, MAX_UNLOCKMSG_SIZE);
      len = Table_quee[Table_Id].unlockLen_2;
      memcpy (bufUnlock, Table_quee[Table_Id].unlockbuf_2, len);
      Table_quee[Table_Id].unlockLen_2 = 0;
      free (Table_quee[Table_Id].unlockbuf_2);
      Table_quee[Table_Id].unlockbuf_2 = NULL;
      if (Table_quee[Table_Id].un_1_flag == 0)
	{
	  Table_quee[Table_Id].un_1_flag = 1;
	}
      else
	{
	  if (Table_quee[Table_Id].un_2_flag == 0)
	    {
	      Table_quee[Table_Id].un_2_flag = 1;
	    }
	  else
	    {
	      if (Table_quee[Table_Id].un_3_flag == 0)
		{
		  Table_quee[Table_Id].un_3_flag = 1;
		}
	      else
		{
		  if (Table_quee[Table_Id].un_4_flag == 0)
		    {
		      Table_quee[Table_Id].un_4_flag = 1;
		    }
		  else
		    {
		      GCSUTIL_DEBUG_TRACE (("FROMSTACK :More Than Two UNLOCK REC\n"));
		    }
		}
	    }
	}
    }

  ret_3 = send (UNIX_SMbox, bufUnlock, len, 0);
  if (ret_3 <= 0)
    {
      GCSUTIL_DEBUG_TRACE (("RetriveUnlock_ONSyncUnlock:send() failed \n"));
      close (UNIX_SMbox);
      UNIX_SMbox = 0;
      pthread_cancel (Recvhread);	/*Need to check whether different thread can cancel each other */
      return;
    }
    if(ret_3 != len)
    {
	    LOG_PRINT_CRITICAL("RetriveUnlock_ONSyncUnlock: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret_3);
    }
      LOG_PRINT_CRITICAL("RetriveUnlock_ONSyncUnlock:Selfsend TbId[%d] len[%d]\n",Table_Id,len);


}

//int udp_listener;
void *
UDP_Server (void *args)
{
  fd_set master;
  fd_set read_fds;
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr;
 // int listener;
  int newfd;
  int yes = 1;
	int ret = 0;
  //int addrlen;
  socklen_t addrlen;


  /* clear the master and temp sets */
  FD_ZERO (&master);
  FD_ZERO (&read_fds);
  /* get the listener */
      LOG_PRINT_CRITICAL ("ALERT ::::: UDP SERVER  THREAD INVOKE \n");
  if ((udp_listener = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("UDP Server :socket() failed \n");
      LOG_PRINT_CRITICAL ("UDP_Server:socket() failed ");
      exit (1);
    }
  /*"address already in use" error message */
  if (setsockopt (udp_listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) ==
      -1)
    {
      LOG_PRINT_CRITICAL ("UDP_Server:setsockopt() failed \n");
      perror ("UDP_Server:setsockopt() failed ");
      exit (1);
    }
 // SocketOption (udp_listener);
 // SetKeepAliveOption(udp_listener);
  /* bind */
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = htons (UDP_PORT);
  memset (&(serveraddr.sin_zero), '\0', 8);
  if (bind (udp_listener, (struct sockaddr *) &serveraddr, sizeof (serveraddr)) ==
      -1)
    {
      perror ("UDP_Server:bind() failed \n");
      LOG_PRINT_CRITICAL ("UDP_Server:bind() failed \n");
      exit (1);
    }
  SocketOption(udp_listener);
  SetKeepAliveOption(udp_listener);
  /* listen */
  if (listen (udp_listener, 10) == -1)
    {
      perror ("UDP_Server:Server-listen() failed ");
      LOG_PRINT_CRITICAL ("UDP_Server:Server-listen() failed \n ");
      // exit(1);
    }
  /* add the listener to the master set */
  GetSocketOption(udp_listener);
  while (1)
	{
					if(udp_listener == 0)
					{
									LOG_PRINT_CRITICAL ("UDP_Server thread:Exit\n");
									break;
					}      
          if(LEAVE_PEER == 1)
          {
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###UDP_Server:Sleep for 5 sec########...\n",LEAVE_PEER);
            sleep(5);
            LEAVE_PEER = 0;
	      LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]###UDP_Server:After Sleep for 5 sec########...\n",LEAVE_PEER);
          }
					if ((newfd = accept (udp_listener, (struct sockaddr *) &clientaddr,&addrlen)) == -1)
					{
									perror ("UDP_Server:Server-accept() failed ");
									LOG_PRINT_CRITICAL ("UDP_Server:Server-accept() failed \n");
					}
					else
					{
				LOG_PRINT_CRITICAL ("UDP Server connection ACCEPTED LEAVE_PEER[%d] \n", LEAVE_PEER);
                 if(newfd == 0 )
                  {
									   LOG_PRINT_CRITICAL ("UDP_Server:ZERO FD \n");
                     close(newfd);
                     continue;
                  }
									LOG_PRINT_CRITICAL ("UDP_Server:Server-accept() SUCCESS  \n");

									sockfd_udp = newfd;
									LOG_PRINT_CRITICAL ("SocketUP :: UDP Server ACCEPT SUCCESS NewFd[%d]\n", sockfd_udp);
#if 0
									pthread_create (&UDPRecvThread, NULL, UDP_Function, NULL);
#endif
								 while(1)
								 {
								    ret = UDP_Function();
								    if(ret < 0)
								    {
									     LOG_PRINT_CRITICAL ("UDP_Server: UDP_Function failed, waiting for accept again  \n");
											 break;
								    }
                 }
					}
           sleep(1);

	}


  return 0;
}

void *
UDP_Client (void *args)
{
  int sockfd = 0;
  int ret = 0;
  int yes = 1;
  struct sockaddr_in their_addr;
  struct timespec req;
  int UDPClientConnectOk = 0;
 LOG_PRINT_CRITICAL ("ALERT ::::: UDP CLIENT THREAD INVOKE \n");
  while (1)
    {
     // LOG_PRINT_CRITICAL ("ALERT ::::: UDP CLIENT THREAD PROCEDURE \n");
      if (sockfd_udp_client == 0)
			{
				if(CLIENT_RETRY_FLAG == 1)
				{	
				 LOG_PRINT_CRITICAL ("UDP_Client: Sleeping for 30sec before connecting .......\n");
				 sleep(30);
				 CLIENT_RETRY_FLAG = 0;
				} 
							if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
							{
											LOG_PRINT_CRITICAL ("UDP_Client:socket() failed \n");
											perror ("UDP_Client:socket() failed ");
											exit (1);
							}
							LOG_PRINT_CRITICAL ("UDP_Client:SOCKET OPEN for UDP_CLIENT Fd[%d] \n",sockfd);
							/*"address already in use" error message */
							if (setsockopt
															(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1)
							{
											LOG_PRINT_CRITICAL ("UDP_Client:-setsockopt() error lol! \n");
											perror ("UDP_Client::setsockopt() failed ");
							}
							SocketOption (sockfd);
               SetKeepAliveOption(sockfd);
							sockfd_udp_client = sockfd;
							UDPClientConnectOk = 0;
			 }
			 /*if((UDPClientConnectOk == 0) && (LEAVE_PEER == 0)) 29-Jan-2015 */
			 if(UDPClientConnectOk == 0)
			 {
							// host byte order
							their_addr.sin_family = AF_INET;
							// short, network byte order
							their_addr.sin_port = htons (UDP_PORT);
							their_addr.sin_addr.s_addr = inet_addr (CLIPEER_UDPADDR);
							// zero the rest of the struct
							memset (&(their_addr.sin_zero), '\0', 8);
							if ((ret =	connect (sockfd, (struct sockaddr *) &their_addr,
																	sizeof (struct sockaddr))) == -1)
							{
											LOG_PRINT_CRITICAL ("UDP_Client:connect() failed  \n");
											perror ("UDP_Client:connect() failed ");
                      //LOG_PRINT_CRITICAL ("UDP_Client :connect() failed: CLOSING FD[%d] \n",sockfd);
											//close (sockfd);
							}
							else
							{
								UDPClientConnectOk = 1;
                                                                                        GetSocketOption(sockfd);
											LOG_PRINT_CRITICAL ("SocketUP :: UDP CLIENT  CONNECT SUCCESS NewFd[%d]\n",sockfd_udp_client);
							}
			}
        if(sockfd_udp_client == 0)
        {
          if(LEAVE_PEER == 1)
          {
              LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]#####UDP_Client##########Sleep for 5 sec########...\n",LEAVE_PEER);
            sleep(5);
            LEAVE_PEER = 0;
              LOG_PRINT_CRITICAL("####LEAVE_PEER[%d]##UDP_Client##########After Sleep for 5 sec########...\n",LEAVE_PEER);
          }
          else
          {
          req.tv_sec=0;
          req.tv_nsec=200000000;
          pselect(FD_SETSIZE,0,0,0,&req,NULL);
          }
        }
        else
        {
          sleep(1);

        } 
    }
	      LOG_PRINT_CRITICAL("UDP Client EXITING >>>>>>>>>>>>>>>>>>>>>>...\n");
  return 0;

}
void SendNetworkChangeLeaveMsg()
{
	char  head_buf[100];
	char data[1000];
	char SendBuff[1000];
	message_header  *head_ptr;
	char            *group_ptr;
	int num_groups = 1;
	int len = 0,ret = 0,hdrlen=0;
	char BuffN2leave[] = {0xc0,0xa8,0x0e,0x7f,0x4c,0x76,0x0b,0x33,0x00,0x00,0x00,0x01,
                              0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
                              0x23,0x64,0x2d,0x31,0x2d,0x35,0x2d,0x30,0x23,0x6e,0x6f,0x64,0x65,0x31,
                              0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	char BuffN1leave[] = {0xc0,0xa8,0x0e,0x8f,0x4c,0x76,0x07,0x80,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x01,
                              0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
                              0x23,0x64,0x2d,0x32,0x2d,0x35,0x2d,0x30,0x23,0x6e,0x6f,0x64,0x65,0x32,
                              0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
        memset(head_buf,0,100);
	head_ptr = (message_header *)head_buf;
	group_ptr = &head_buf[ sizeof(message_header) ];
	head_ptr->type = 0x00001800;
	head_ptr->type = Set_Endian( head_ptr->type );
	head_ptr->num_groups = num_groups;
	head_ptr->data_len = 56; 
	head_ptr->hint = (0 << 8) & 0x00ffff00;
	head_ptr->hint = Set_Endian( head_ptr->hint );


	if(MASTER == 1)
	{
		strcpy (head_ptr->private_group_name, "#d-1-5-0#node1");
	}
	else
	{
		strcpy (head_ptr->private_group_name, "#d-2-5-0#node2");
	}
	strcpy(group_ptr,head_ptr->private_group_name);
	hdrlen = sizeof (message_header) + 32;
#if 0
	ret = send (UNIX_SMbox, head_buf, len, 0);
	if (ret < 0)
	{
		GCSUTIL_DEBUG_TRACE (("UNIX_Recv:send() failed "));
		close (UNIX_SMbox);
		UNIX_SMbox = 0;
		pthread_cancel (Recvhread);
	}
        if(ret != len)
        {
	    LOG_PRINT_CRITICAL("SendNetworkChangeLeaveMsg: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret);
        }
	LOG_PRINT_CRITICAL("HEADER for NETWORK CHANGE SEND SUCCESSFULLY to STACK ret %d ",ret);
#endif
        memset(SendBuff, 0, 1000);
	memcpy(SendBuff,head_buf,hdrlen);
	len = 56;
	if(MASTER == 1)
	{ 
		/*when Node2 leave , Node 1 send BuffN2leave to its own stack*/
		memcpy(data,BuffN2leave,56);
	}
	else
	{
		/*when Node1 leave , Node 2 send BuffN1leave to its own stack*/
		memcpy(data,BuffN1leave,56);

	}
	memcpy(&SendBuff[hdrlen],data,len);
	len = hdrlen + 56;
	ret = send (UNIX_SMbox,SendBuff, len, 0);
	if (ret < 0)
	{
		GCSUTIL_DEBUG_TRACE (("UNIX_Recv:send() failed "));
		close (UNIX_SMbox);
		UNIX_SMbox = 0;
		pthread_cancel (Recvhread);
	}
        if(ret != len)
        {
	    LOG_PRINT_CRITICAL("SendNetworkChangeLeaveMsg: ERROR In UNIX SEND:LESS BYTES SEND[%d]\n",ret);
        }
	LOG_PRINT_CRITICAL("NETWORK CHANGE MSG SEND SUCCESSFULLY to STACK ret %d ",ret);


}

void  DeallocateGlobalbuffers()
{
    LOG_PRINT_CRITICAL ("Free Globalbuffers \n");
    free(bufUnixRecv);
    bufUnixRecv = NULL;
    free(bufTCPRecv);
    bufTCPRecv = NULL;
}
