/*******************************************************************************
**      FILE NAME:
**          bs_main.c
**
**      DESCRIPTION:
**              This is the main file of BSSAP stack handelling soc-mgr,initialization,read conf file **							& main function.
**
**
**      DATE            NAME                          REFERENCE        REASON
**      ----            ----                          ---------        ------
**      21th Feb 2014   Amaresh Prasad Grahacharya
**
**      Copyright 2005, Vihaan Network Ltd.
**
*******************************************************************************/
#include <sl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include <malloc.h>
#include <stdlib.h>
#include "bssap.h"
#include "nw_util.h"
#include <s7_typ.h>
#include <s7_api.h>
#include <s7_def.h>
#include <s7_error.h>
#include <bs_stgl.h>
#include <bs_debug.h>
#include <bssap_port.h>

#ifdef LOGGER_IMR
#include <sysxxx_hashdefs.h>
#include <sysxxx_typedef.h>
#include <sysxxx_msgstruct.h>
#include <sysxxx_proc.h>
#include <sysxxx_prcr.h>
#include <ipcfrm_extern.h>
#include <ipcfrm_syslog.h>
#define LOG_PRINT_DEBUG(_p1...)     LOG_PRINT(DEBUG,##_p1)
#define LOG_PRINT_INFO(_p1...)     LOG_PRINT(INFO,##_p1)
#define LOG_PRINT_MAJOR(_p1...)     LOG_PRINT(MAJOR,##_p1)
#define LOG_PRINT_CRITICAL(_p1...)     LOG_PRINT(CRITICAL,##_p1)

#ifdef LOGGER_ON_SCREEN
#define LOG_PRINT(a,b,args...) printf(b,##args)
#endif

SysAddr slfAddr;
#endif
/*Note :Start added for signal handler */
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#ifndef __USE_GNU
#define __USE_GNU
#endif
#include <signal.h>
#define __USE_GNU
#include <string.h>
#include <execinfo.h>
#include <ucontext.h>
#define BACK_TRACE_DEPTH   100
void reg_sig_hndlr();
void bsc_sighandler(int signum, siginfo_t *sig_info, void *secret);
void printBackTrace(ucontext_t *uc);
/*Note :End added for signal handler */

#ifdef BSSAP_HA
#include "bs_hashFunc.h"
#endif


#ifdef PLATFORM_IMR
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
#endif


#ifndef SIGTRAN_SCCP_IF
#define SIGTRAN_SCCP_IF
#endif

#define MAX_NUM_USERS 4
#define SS7_SUCCESS 1

#define NIB_SERVER

static  int bssap_user_sock[2];
static  int bssap_user_sock_send[2];

#ifdef SIGTRAN_SCCP_IF
static  int sigtran_sccp_if_sock[2];
static  int sigtran_sccp_if_sock_send[2];
char sigtran_sccp_if_serv_addr[32];/* For SCCP */
int sigtran_sccp_if_port;
unsigned long int sccp_ip_address;
#endif

/* static const  int yes = 1; */
unsigned long int user_ip_address;

extern sl_pool_t ss7_pool;

char user_serv_addr[32];/* For User */
int user_port;
int layer_server_port;
int layer_server_port_sccp;

char *host_ip[32];
#ifdef BSSAP_HA
char TCPPEER_IP[25];
int TCP_PORT;
int MASTER;
#endif
#ifdef SCM_CHG
int BS_SERVER_PORT;
#endif
int bsc_ssn_bssap,nwk_indicator;
int ssf_cap_ssn,scf_cap_ssn;

int source_point_code;

int rem_pc,bs_log_user_id,bsc_id,bs_intf_id,start_cic,end_cic;
int read_from_conf = 0;

#ifdef PLATFORM_IMR
I_U8 bpmHealthFlagG;
I_U8 bpmCardState;
#endif


U32bit bssap_trace_table[MAX_TRACE_LEVELS];

extern const QSYSOP *os;
extern const QSHELL *operations;
extern const QWAIT *waitstruct;
extern YLIST sl_event_list;


extern void sl_event_init (void);
void pool_show (void);
int soc_mgr_nw_read
(       int                             sockfd,
        unsigned char   *ptr,
        int                             nbytes)
{
        int     nleft, nread;

        nleft = nbytes;
        while (nleft > 0)
        {
#ifdef WINNT
                nread = recv (sockfd, ptr, nleft, 0);
#else
                nread = read (sockfd, (void *)ptr, nleft);
#endif

                if (nread < 0)
                        return nread;   /* error return < 0 */
                else
                if (nread == 0)
                {
                        return -1;              /* EOF */
                }

                nleft -= nread;
                ptr += nread;
        }
        return (nbytes - nleft);        /* return >= 0 */
}

int soc_mgr_read_api
(       int                    sock_fd,
        unsigned char           *p_buf,
        unsigned int            nbytes)
{
        int                                 sockfd;
        int                                 nread;

        sockfd = sock_fd;

        nread = soc_mgr_nw_read(sockfd, p_buf, nbytes);
        if (nread < 0)
        {
                /* Connection broken */
                close(sockfd);
                return -1;
        }

        return nread;
}


unsigned char user_intf_api_notification_hndlr
     (int         sock_fd,
      unsigned char     *p_hdr_buf)
{
   unsigned char        *p_api_buf;
   unsigned short int   api_len = 0;
   unsigned short int   nread;
   unsigned char        api_id;
   error_t              *p_ecode;

       api_len  |= p_hdr_buf[23];
       api_len  |= p_hdr_buf[22] << 8;
       api_len  |= p_hdr_buf[21] << 16;
       api_len  |= p_hdr_buf[20] << 24;

        
   //LOG_PRINT(INFO,"RECV MSG FROM BSC-APP :Len[%d]\n",api_len);

   p_api_buf  =  (unsigned char *)ss7_mem_get(api_len + SS7_BSSAP_APP_API_HEADER_LEN);
   if(p_api_buf)
   {
        ss7_memcpy(p_api_buf,p_hdr_buf,SS7_BSSAP_APP_API_HEADER_LEN);
   }

   if(p_api_buf)
   {
      nread = soc_mgr_read_api(sock_fd,(p_api_buf+SS7_BSSAP_APP_API_HEADER_LEN),(api_len));
      if(nread != (api_len))
      {
         ss7_mem_free((void *)p_api_buf);
         return NULL;
      }
      ss7_dispatch_buffer (p_api_buf, api_len + SS7_BSSAP_APP_API_HEADER_LEN,0, BSSAP_MODULE_ID,p_ecode);

      /* return ((unsigned char *)p_api_buf);*/
       return SS7_SUCCESS;
    }
   return NULL;
}
unsigned char user_sock_recv_data (int fd)
{
    int len,nread;
    unsigned int count = 0;
    struct sockaddr_in addr;
    int size = sizeof (addr);
    unsigned char buffer[28];
    void *buff = NULL;

     nread = soc_mgr_nw_read (bssap_user_sock[1], (unsigned char *)buffer, SS7_BSSAP_APP_API_HEADER_LEN);
    if (nread < 0)
    {
        return (-1);
        perror("recv");
      /*  abort();*/
    }
    else
    {
        user_intf_api_notification_hndlr(bssap_user_sock[1],buffer);
    }

}
unsigned char user_sock_recv (int fd)
{
    int len,nread;
    unsigned int count = 0;
    struct sockaddr_in addr;
    int size = sizeof (addr);
    unsigned char buffer[28];
    void *buff = NULL;

    int                     nsd;
    struct sockaddr_in  from;
        struct linger           lg;
#ifdef LINUX
    unsigned int fromlen;
#else
    int fromlen;
#endif

	fromlen = sizeof (from);
        if ((nsd = accept (fd, (struct sockaddr *)&from, &fromlen)) < 0)
        {
                /* perror("\nNW UTIL: "); */
                return (-1);
        }

        lg.l_onoff = 1;
        /* l_linger is set to default */
        lg.l_linger = 5;
        if (setsockopt (nsd, SOL_SOCKET, SO_LINGER,
                        (char *)&lg, sizeof (struct linger)) < 0)
        {
                /* perror("\nNW UTIL: "); */
                close (nsd);
                return (-1);
        }
      bssap_user_sock[1] = nsd;
    sl_event_register (bssap_user_sock[1], user_sock_recv_data);
      return nsd;
}

#ifdef SIGTRAN_SCCP_IF
unsigned char sigtran_sccp_if_api_notification_hndlr
     (int         sock_fd,
      unsigned char     *p_hdr_buf)
{
   unsigned char        *p_api_buf;
   unsigned short int   api_len;
   unsigned short int   nread;
   unsigned char        api_id;
   error_t              *p_ecode;
   api_id   =  *p_hdr_buf;
   api_len  = GET_API_LEN(p_hdr_buf);

   p_api_buf  =  (unsigned char *)ss7_mem_get(api_len);
   if(p_api_buf)
   {
        ss7_memcpy(p_api_buf,p_hdr_buf,SS7_API_HEADER_LEN);
   }
   ss7_memcpy(p_api_buf,p_hdr_buf,SS7_API_HEADER_LEN);

   if(p_api_buf)
   {
      nread = soc_mgr_read_api(sock_fd,(p_api_buf+SS7_API_HEADER_LEN),(api_len-SS7_API_HEADER_LEN));
      if(nread != (api_len-SS7_API_HEADER_LEN))
      {
         ss7_mem_free((void *)p_api_buf);
         return NULL;
      }
    /*  ss7_dispatch_buffer (p_api_buf, api_len,0, SCCP_MODULE_ID,p_ecode);*/
      ss7_dispatch_buffer (p_api_buf, api_len,0, BSSAP_MODULE_ID,p_ecode);

       return ((unsigned char *)p_api_buf);
         return SS7_SUCCESS;
    }
   return NULL;
}
unsigned char sigtran_sccp_if_sock_recv_data (int fd)
{
    int len,nread;
    unsigned int count = 0;
    struct sockaddr_in addr;
    int size = sizeof (addr);
    unsigned char buffer[5];
    void *buff = NULL;

     nread = soc_mgr_nw_read (sigtran_sccp_if_sock[1], (char *)buffer, SS7_API_HEADER_LEN);
    if (nread < 0)
    {
        return (-1);
        perror("recv");
      /*  abort();*/
    }
    else
    {
        LOG_PRINT(INFO,"RECV MSG FROM SIGTRAN_SCCP_IF:\n");
        sigtran_sccp_if_api_notification_hndlr(sigtran_sccp_if_sock[1],buffer);
    }

}

unsigned char sigtran_sccp_if_sock_recv (int fd)
{
    int len,nread;
    unsigned int count = 0;
    struct sockaddr_in addr;
    int size = sizeof (addr);
    unsigned char buffer[5];
    void *buff = NULL;

    int                     nsd;
    struct sockaddr_in  from;
        struct linger           lg;
#ifdef LINUX
    unsigned int fromlen;
#else
    int fromlen;
#endif

	fromlen = sizeof (from);
        if ((nsd = accept (fd, (struct sockaddr *)&from, &fromlen)) < 0)
        {
                /* perror("\nNW UTIL: "); */
                return (-1);
        }

        lg.l_onoff = 1;
        /* l_linger is set to default */
        lg.l_linger = 5;
        if (setsockopt (nsd, SOL_SOCKET, SO_LINGER,
                        (char *)&lg, sizeof (struct linger)) < 0)
        {
                /* perror("\nNW UTIL: "); */
                close (nsd);
                return (-1);
        }
      sigtran_sccp_if_sock[1] = nsd;
    	sl_event_register (sigtran_sccp_if_sock[1], sigtran_sccp_if_sock_recv_data);
      return nsd;
}

#endif

user_tcp_sock_init (void)
{
    struct sockaddr_in addr;
    int flags;
    unsigned int optval;
    const int  yes = 1;
    int optlen = sizeof(optval);

    if ((bssap_user_sock[0] = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket");
        exit (1);
    }
    memset (&addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
    user_ip_address = inet_addr( host_ip );
    addr.sin_addr.s_addr = user_ip_address;
    addr.sin_port = htons (layer_server_port);

    if( fcntl(bssap_user_sock[0], F_SETFL, O_NONBLOCK) < 0 ) {
    LOG_PRINT(INFO,"[ENCAPS:: ] fcntl fail");
    }
   
  if( setsockopt(bssap_user_sock[0], SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes) ) < 0 ) {
    perror("setsockopt:REUSEADDR");
     exit (1);
  }

  if( bind(bssap_user_sock[0], (struct sockaddr_in *)&addr, sizeof(addr) ) < 0 ) {
    perror("bind");
    exit (1);
  }

  if( listen(bssap_user_sock[0], 5) < 0 ) {
   perror("listen");
    exit (1);
  }

    sl_event_register (bssap_user_sock[0], user_sock_recv);
   /* sl_event_register (sccp_user_sock[1], user_sock_recv_data);*/

}

#ifdef SIGTRAN_SCCP_IF
sigtran_sccp_if_tcp_sock_init (void)
{
    struct sockaddr_in addr;
    int flags;
    unsigned int optval;
    const int  yes = 1;
    int optlen = sizeof(optval);

    if ((sigtran_sccp_if_sock[0] = socket (AF_INET, SOCK_STREAM, 0)) < 0) {
        perror ("socket");
        exit (1);
    }
    memset (&addr, 0, sizeof (addr));
    addr.sin_family = AF_INET;
    user_ip_address = inet_addr( host_ip );
    addr.sin_addr.s_addr = user_ip_address;
    addr.sin_port = htons (layer_server_port_sccp);
#if 0
    if( fcntl(sigtran_sccp_if_sock[0], F_SETFL, O_NONBLOCK) < 0 ) {
    LOG_PRINT(INFO,"[ENCAPS:: ] fcntl fail");
    }
#endif 
  
  if( setsockopt(sigtran_sccp_if_sock[0], SOL_SOCKET, SO_REUSEADDR, (char *)&yes, sizeof(yes) ) < 0 ) {
    perror("setsockopt:REUSEADDR");
     exit (1);
  }

  if( bind(sigtran_sccp_if_sock[0], (struct sockaddr_in *)&addr, sizeof(addr) ) < 0 ) {
    perror("bind");
    exit (1);
  }

  if( listen(sigtran_sccp_if_sock[0], 5) < 0 ) {
   perror("listen");
    exit (1);
  }

    sl_event_register (sigtran_sccp_if_sock[0], sigtran_sccp_if_sock_recv);
   /* sl_event_register (sccp_user_sock[1], user_sock_recv_data);*/

}

#endif

/*****************************************************************************
**
**      FUNCTION :
**              Dump the API.
**
******************************************************************************
**
**      DESCRIPTION :
**              This function dumps all the fields of the api header and
**              dumps in hex all the data bytes
**
******************************************************************************/
void
sccp_api_detail_trace
#ifdef ANSI_PROTO
  (U8bit * p_api)
#else
  (p_api)
  U8bit * p_api;
#endif
{
#define API_DUMP_LINE_SIZE  20
  U16bit i, num_lines, data_buf_len, dump_line_bytes;
  U8bit * p_data_buf;

  /* Check if detail trace for API TRACE is set */
  if ( ! (bssap_trace_table[DETAILED_TRACE] & SCTC_API_TRACE))
    return;
SC_TRC (("SCCP::DBG:api_id = %d, version = %d, num_elem = %d, len = %d\n",
           GET_API_ID(p_api), GET_API_VER(p_api), GET_API_NELEM(p_api),
           GET_API_LEN(p_api)));

  data_buf_len = GET_API_LEN(p_api) - API_HEADER_LEN;

  (data_buf_len % API_DUMP_LINE_SIZE) ?
  (num_lines = (data_buf_len / API_DUMP_LINE_SIZE) + 1) :
  (num_lines = (data_buf_len / API_DUMP_LINE_SIZE));

  for (i=num_lines, p_data_buf = p_api + API_HEADER_LEN;
       i > 0; i--)
  {
    dump_line_bytes = (U16bit)
    ((p_data_buf + API_DUMP_LINE_SIZE) > (p_api + GET_API_LEN(p_api)) ?
     (p_api + GET_API_LEN(p_api) - p_data_buf) : API_DUMP_LINE_SIZE);
    BSSAP_HEX_DUMP (API_TRACE, DETAILED_TRACE,
                  p_data_buf, dump_line_bytes);
    SC_TRC(("\n"));
    p_data_buf += dump_line_bytes;
  }
}





/*****************************************************************************
**
**	FUNCTION NAME
**		soc_mgr_nw_write
**
******************************************************************************
**
**	DESCRIPTION
**		This function will write the specified number of bytes into the socket
**	stream
**
**	INPUTS
**	sockfd:	socket stream descriptor into which the bytes are to be written
**	ptr:	buffer from which the bytes are to be written
**	nbytes:	number of bytes to be written
**
**	RETURNS
**		number of bytes written
**		-1 on failure
**
*****************************************************************************/

int soc_mgr_nw_write 
(	int				sockfd, 
	const unsigned char	*ptr,
	int				nbytes)
{
	int	nleft, nwritten;

	nleft = nbytes;
	while (nleft > 0)
	{
#ifdef VXWORKS
		nwritten = send (sockfd, (char *) ptr, nleft,0);
#else
		nwritten = send (sockfd, (const char *) ptr, nleft,0);
#endif
		if (nwritten < 0)
			return nwritten;	/* error return < 0 */
		
		nleft -= nwritten;
		ptr += nwritten;
	}
	return (nbytes - nleft);
}
/*****************************************************************************
**
**	FUNCTION NAME
**		soc_mgr_send_api_user
**
******************************************************************************
**
**	DESCRIPTION
**		This function will send an api on the specified socket stream
**
**	INPUTS
**	sockfd:	socket stream descriptor from which the bytes are to be sent
**	ptr:	buffer from which the bytes are to be sent
**	nbytes:	number of bytes to be sent
**
**	RETURNS
**		number of bytes sent
**		-1 on failure
**
*****************************************************************************/

int soc_mgr_send_api_user 
(       int                             sockfd,
	const unsigned char		*p_hdr_buf,
	const unsigned char		*p_api_buf,
	unsigned int		api_len)
{
	int			            nsent;


	if(sockfd == SOC_MGR_INVALID_SOC_FD)
	{
	return -1; 
	}
	/* send API header */
	nsent = soc_mgr_nw_write(sockfd, p_hdr_buf, SS7_BSSAP_APP_API_HEADER_LEN);

	/* send the API */
	if (nsent >= 0)
		nsent = soc_mgr_nw_write(sockfd, p_api_buf, api_len);

	if (nsent < 0)
	{
		/* Connection broken */
		close(sockfd);
		/* connection / server will be setup again in other 2 case during
		** next iteration 
		*/
                LOG_PRINT(INFO,"[ENCAPS:: ]->Connection broken down \n");
		bssap_user_sock_send[0] = soc_mgr_setup_client(user_serv_addr,user_port);
		return -1;
	}

	return nsent;
}
/*****************************************************************************
**
**	FUNCTION NAME
**		soc_mgr_send_api
**
******************************************************************************
**
**	DESCRIPTION
**		This function will send an api on the specified socket stream
**
**	INPUTS
**	sockfd:	socket stream descriptor from which the bytes are to be sent
**	ptr:	buffer from which the bytes are to be sent
**	nbytes:	number of bytes to be sent
**
**	RETURNS
**		number of bytes sent
**		-1 on failure
**
*****************************************************************************/

int soc_mgr_send_api 
(       int                             sockfd,
	const unsigned char		*p_hdr_buf,
	const unsigned char		*p_api_buf,
	unsigned int		api_len)
{
	int			            nsent;


	if(sockfd == SOC_MGR_INVALID_SOC_FD)
	{
	return -1; 
	}
	/* send API header */
	nsent = soc_mgr_nw_write(sockfd, p_hdr_buf, 5);

	/* send the API */
	if (nsent >= 0)
		nsent = soc_mgr_nw_write(sockfd, p_api_buf, api_len);

	if (nsent < 0)
	{
		/* Connection broken */
		close(sockfd);
		/* connection / server will be setup again in other 2 case during
		** next iteration 
		*/
		sigtran_sccp_if_sock_send[0] = soc_mgr_setup_client(sigtran_sccp_if_serv_addr,sigtran_sccp_if_port);
		return -1;
	}

	return nsent;
}


/*****************************************************************************
**
**	FUNCTION NAME
**		soc_mgr_setup_client
**
******************************************************************************
**
**	DESCRIPTION
**		This function will set up a socket client
**
**	INPUTS
**		serv_ipstr:		pointer to a char string containing IP address of the
**						server in the form "a.b.c.d" or "server name"
**		serv_tcpport:	port of the server
**		
**
**	RETURNS
**		client fd if succesful
**		-1 otherwise
**
*****************************************************************************/

int soc_mgr_setup_client
(	char 	*serv_ipstr, 
	u_short	serv_tcpport)
{
	int		        sockfd;
	long			serv_ipaddr;
	struct sockaddr_in	saddr;
#ifdef SOLARIS	
	int 		value = 1000; /* 1 sec */
#endif
	if ((serv_ipaddr = inet_addr (serv_ipstr)) == -1)
	{
		  /* perror("\nNW UTIL "); */
		  fprintf (stderr, "NW UTIL:: Invalid IP address \n");
		  return -1;

	}
	saddr.sin_family = AF_INET;

	saddr.sin_port = htons (serv_tcpport);

	saddr.sin_addr.s_addr = serv_ipaddr;

	if ((sockfd = socket (AF_INET, SOCK_STREAM, 0)) < 0)
	{
		/* perror("\nNW UTIL "); */
		return (-1);
	}
#ifdef SOLARIS	
	if ( setsockopt(sockfd, IPPROTO_TCP, TCP_CONN_ABORT_THRESHOLD, 
				(const void*)&value, sizeof(value)) < 0)
	{
		/*SS7P_SYSTEM_TRACE(("SS7P PORT:: Could not set TCP_CONN_ABORT_THRESHOLD " "option \n"));*/
		close (sockfd);
		return (-1);

	}
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) & O_NONBLOCK);
#endif

	if (connect (sockfd, (struct sockaddr *)&saddr, 
		     sizeof (struct sockaddr_in)) < 0)
	{
		/* perror("\nNW UTIL "); */
		close (sockfd);
		return (-1);
	}
#ifdef SOLARIS
	fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFL, 0) & ~O_NONBLOCK);
#endif

	return sockfd;
}

struct poolshow_t  poolshow[] = {
#ifdef M3UA
    POOL_ENTRY(sigtran_m3ua_pool),
#endif
    {0,0}
};

int	gsn_no_reconcile = 0;
int	gsn_daemonize = 1;

sl_pool_t note_pool;

bssap_init()
{
	bssap_user_sock_send[0] = SOC_MGR_INVALID_SOC_FD;
	bssap_user_sock_send[1] = SOC_MGR_INVALID_SOC_FD;
	bssap_user_sock[0] = SOC_MGR_INVALID_SOC_FD;
	bssap_user_sock[1] = SOC_MGR_INVALID_SOC_FD;
#ifdef SIGTRAN_SCCP_IF
sigtran_sccp_if_sock_send[0] = SOC_MGR_INVALID_SOC_FD;
sigtran_sccp_if_sock_send[1] = SOC_MGR_INVALID_SOC_FD;
sigtran_sccp_if_sock[0] = SOC_MGR_INVALID_SOC_FD;
sigtran_sccp_if_sock[1] = SOC_MGR_INVALID_SOC_FD;
#endif
int cnt = 0;
    qvSimpleInit(os);
    sl_event_init();
/* User IP Config for BSC-APP start */
    user_tcp_sock_init();
    /* The loop is for accepting client connection & retry infinite times due to delay in process up start */
#ifndef LOGGER_ON_SCREEN
      for(;;)
      {
            bssap_user_sock_send[0] = soc_mgr_setup_client(user_serv_addr,user_port);
            if (bssap_user_sock_send[0] != SOC_MGR_INVALID_SOC_FD)
            break;
      }
   /* The loop is for accepting client connection & retry infinite times due to delay in process up stop */
    LOG_PRINT(INFO,"[ENCAPS:: ] Established client connection with server %s [port #%d]\n",user_serv_addr, user_port);
#endif

/* User IP Config for BSC-APP stop */

#ifndef LOGGER_ON_SCREEN
#ifdef SIGTRAN_SCCP_IF
    sigtran_sccp_if_tcp_sock_init();
   /* The loop is for accepting client connection & retry infinite times due to delay in process up start */
        for(;;)
 	{
	   sigtran_sccp_if_sock_send[0] = soc_mgr_setup_client(sigtran_sccp_if_serv_addr,sigtran_sccp_if_port);
	   if (sigtran_sccp_if_sock_send[0] != SOC_MGR_INVALID_SOC_FD)
	   break;
        } 	
    LOG_PRINT(INFO,"[ENCAPS:: ] Established client connection with server %s [port #%d]\n",sigtran_sccp_if_serv_addr, sigtran_sccp_if_port);
   /* The loop is for accepting client connection & retry infinite times due to delay in process up stop */
#endif
#endif
   /* The loop is for accepting client connection & retry infinite times due to delay in process up start */
    ss7_bssap_init ();
    ss7_pool = sl_pool_create (BSSAP_BUF_SIZE, BSSAP_NBUF);
    pool_show ();
    qvRun (operations, &sl_event_list,waitstruct, 0);
}

/*****************************************************************************
**      FUNCTION :
**         BpmCallBackFunc
******************************************************************************
**
**      DESCRIPTION :
**          This function gets card state health check test.
**
**      NOTE :
**
*****************************************************************************/

#ifdef PLATFORM_IMR
void   BpmCallBackFunc(struct sAisParam* param)
{
   LOG_PRINT(DEBUG,"bpmBSSAPCallbackFunc Called");
   switch(param->messageId)
   {
          case BPM_HEALTHCHECK_MESSAGE:
               {
                  LOG_PRINT(DEBUG,"BpmCallBackFunc : BPM_HEALTHCHECK_MESSAGE ");
                  fflush(stdout);
                  bpmRespondToAis (param->invocation,OK);
               }
               break;
					case BPM_SELFCARD_STATE_CHANGE:
              {
                  if(param->cardState == CARDSTATE_ACTIVE)
                  {
                      LOG_PRINT(DEBUG,"BpmCallBackFunc : CARDSTATE_ACTIVE \n");
										  bpmCardState = BSSAP_CARD_STATE_ACTIVE;	
                  }
                  else if(param->cardState == CARDSTATE_STANDBY)
                  {
                      LOG_PRINT(DEBUG,"BpmCallBackFunc : CARDSTATE_STANDBY \n");
										  bpmCardState = BSSAP_CARD_STATE_STANDBY;	
                  }
									bpmRespondToAis (param->invocation,OK);
#ifdef BSSAP_HA
		              BsHashInvoke(param->cardState);
#endif
              }
           break;
           case BPM_PEERCARD_STATE_CHANGE:
             {
                if(param->cardState == CARDSTATE_ABSENT)
                {
                  LOG_PRINT(DEBUG,"BpmCallBackFunc : PEER CARD ABSENT received ");
                }	
            		bpmRespondToAis (param->invocation,OK); 
						}
          break;

        case BPM_MSG_ACK_CONFIGURE:
            {
                  LOG_PRINT(DEBUG,"BpmCallBackFunc : BPM_MSG_ACK_CONFIGURE: ");
                   bpmRespondToAis (param->invocation,OK);
            }
            break;

       case BPM_SHUTDOWN:
            {
                  LOG_PRINT(DEBUG,"BpmCallBackFunc : Received BPM_SHUTDOWN: ");
                  bpmRespondToAis (param->invocation,OK);
            }
            break;
			default:
         LOG_PRINT(INFO,"bpmAisCallbackFunc : Wrong Msg Rcvd. (msgId = %x)",param->messageId);
         break;
   }/*switch*/
}/*BpmCallBackFunc*/
#endif

void main ()
{
		
    read_from_conf = 1;
#ifdef LOGGER_IMR
/*	slfAddr.prcr = 0;*//* This field is commented due to R3 SysAddr */
	slfAddr.entity = ENT_SKS_BSSAP;
	/*slfAddr.entity = ENT_SKS_TCAP;*/
	slfAddr.clsId = 0;
/*	slfAddr.rfu = 0;*/
	slfAddr.inst = 0;
	if(InitLoggingUtility(slfAddr) == 0)
	{
	LOG_PRINT(INFO,"[ENCAPS:: ]->BSSAP GET REGISTERED  with LOGGER Utility \n ");
	}
	else
	{
	LOG_PRINT(INFO,"[ENCAPS:: ]->BSSAP couldnot REGISTERED  with LOGGER Utility \n ");
	}
#endif
  LOG_PRINT(INFO,"REGISTER WITH SIGNAL HANDLER \n");
  reg_sig_hndlr();

    	if(bssap_read_conf_file() == -1)
        {
		LOG_PRINT(INFO,"[ENCAPS:: ] ->Unable to read sigtran_ph_conf FILE \n ");
            	exit(0);
        }
        else
        {
		LOG_PRINT(INFO,"[ENCAPS:: ] ->Read sigtran_ph_conf FILE Success \n ");
        }

#ifdef PLATFORM_IMR
 /*  Application will  register with application  */
    bpmGetComponentRegister(BpmCallBackFunc, (unsigned short)ENT_SKS_BSSAP);
    bpmComponentConfigure();
    bpmHealthFlagG = OK;
    /*reg_sig_hndlr();*/
#endif

	bssap_init();
 return 0;
}

void pool_show (){
    int i;

    for( i=0; poolshow[i].name; i++ ) {
        if( *(poolshow[i].pool) == 0 ) {
            continue;
        }
        printf("%s => %p\n", poolshow[i].name, *(poolshow[i].pool));
    }
}

/***********************************************************************************
**      FUNCTION :
**         bssap_read_conf_file
************************************************************************************
**
**      DESCRIPTION :
**         read the data from the conf file and fill the above variable accordingly
**
**      NOTE :
**
************************************************************************************/
int
bssap_read_conf_file(void)
{
    char temp[4096];
    char conf_label[50];
    char filename[200];
    unsigned int count;
    char* str;
    char* tmp;

    if(bssap_get_conf_file(filename) == -1)
    {
        return -1;
    }
    /* Getting  HOST_IP_ADDRESS */
    if (!cd_get_param (filename, "HOST_IP_ADDRESS", temp))
    {
        if (sscanf (temp, "%s%s", conf_label,host_ip ) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading HOST_IP_ADDRESS %s\n",host_ip);
	}
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> HOST_IP_ADDRESS parameter not found in CONF file .. Exiting\n");
        return -1;
    }

/* USER */
    /* Getting  USER_IP_ADDRESS */
    if (!cd_get_param (filename, "USER_IP_ADDRESS", temp))
    {
        if (sscanf (temp, "%s%s", conf_label,user_serv_addr ) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading USER_IP_ADDRESS %s\n",user_serv_addr);
	}
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> USER_IP_ADDRESS parameter not found in CONF file .. Exiting\n");
        return -1;
    }

    /* Getting USER_PORT */
    if (!cd_get_param (filename, "USER_PORT", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &user_port) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading USER port %d\n",user_port);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> USER_PORT not found in CONF file\n");
        return -1;
    }
#ifdef BSSAP_HA
    /* Getting TCPPEER_IP_ADDRESS */
    if (!cd_get_param (filename, "TCPPEER_IP_ADDRESS", temp))
    {
        if (sscanf (temp, "%s%s", conf_label,TCPPEER_IP ) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading TCPPEER_IP %s\n",TCPPEER_IP);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> TCPPEER_IP_ADDRESS parameter not found in CONF file .. Exiting\n");
        return -1;
    }
    /* Getting TCP_PORT */
    if (!cd_get_param (filename, "TCP_PORT", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &TCP_PORT) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading TCP port %d\n",TCP_PORT);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> TCP_PORT not found in CONF file\n");
        return -1;
    }
    /* Getting MASTER */
    if (!cd_get_param (filename, "MASTER", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &MASTER) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading MASTER  %d\n",MASTER);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> MASTER not found in CONF file\n");
        return -1;
    }
#endif
#ifdef SCM_CHG
    /* Getting BS_SERVER_PORT */
    if (!cd_get_param (filename, "BS_SERVER_PORT", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &BS_SERVER_PORT) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading BS_SERVER_PORT %d\n",BS_SERVER_PORT);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> BS_SERVER_PORT not found in CONF file\n");
        return -1;
    }
#endif
#ifdef SIGTRAN_SCCP_IF
/* SIGTRAN_SCCP_IF */
    /* Getting  SCCP_IF_IP_ADDRESS */
    if (!cd_get_param (filename, "SCCP_IF_IP_ADDRESS", temp))
    {
        if (sscanf (temp, "%s%s", conf_label,sigtran_sccp_if_serv_addr ) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> SCCP_IF_IP_ADDRESS parameter not found in CONF file .. Exiting\n");
        return -1;
    }

    /* Getting SCCP_IF_PORT */
    if (!cd_get_param (filename, "SCCP_IF_PORT", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &sigtran_sccp_if_port) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading SCCP_IF port %d\n",sigtran_sccp_if_port);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> SCCP_IF_PORT not found in CONF file\n");
        return -1;
    }

 /* Getting SELF_SERVER_PORT_SCCP */
    if (!cd_get_param (filename, "SELF_SERVER_PORT_SCCP", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &layer_server_port_sccp) < 0)
            return -1;
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading SELF_SERVER_PORT_SCCP   %d\n",layer_server_port_sccp);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> SELF_SERVER_PORT_SCCP not found in CONF file\n");
        return -1;
    }

#endif
 /* Getting SELF_SERVER_PORT_USER */
    if (!cd_get_param (filename, "SELF_SERVER_PORT_USER", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &layer_server_port) < 0)
            return -1;
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading SELF_SERVER_PORT_USER   %d\n",layer_server_port);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> SELF_SERVER_PORT_USER not found in CONF file\n");
        return -1;
    }

    /* Getting SSN_BSSAP */
    if (!cd_get_param (filename, "SSN_BSSAP", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &bsc_ssn_bssap) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading SSN_BSSAP  %d\n",bsc_ssn_bssap);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]-> SSN_BSSAP not found in CONF file\n");
        return -1;
    }
    
    /* Getting BS_LOG_USER_ID */
    if (!cd_get_param (filename, "BS_LOG_USER_ID", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &bs_log_user_id) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->BS_LOG_USER_ID not found in CONF file\n");
        return -1;
    }
/*BS_INTF_ID */
    /* Getting BS_INTF_ID */
    if (!cd_get_param (filename, "BS_INTF_ID", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &bs_intf_id) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->BS_INTF_ID not found in CONF file\n");
        return -1;
    }

    /* Getting START_CIC */
    if (!cd_get_param (filename, "START_CIC", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &start_cic) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->START_CIC not found in CONF file\n");
        return -1;
    }

    /* Getting END_CIC */
    if (!cd_get_param (filename, "END_CIC", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &end_cic) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->END_CIC not found in CONF file\n");
        return -1;
    }
    /* Getting NWK_INDICATOR */
    if (!cd_get_param (filename, "NWK_INDICATOR", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &nwk_indicator) < 0)
        {
            return -1;
        }
        else
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]-> Reading NWK_INDICATOR %d\n",nwk_indicator);
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->NWK_INDICATOR not found in CONF file\n");
        return -1;
    }
    
   /* Getting BSC_ID */
    if (!cd_get_param (filename, "BSC_ID", temp))
    {
        if (sscanf (temp, "%s%d", conf_label, &bsc_id) < 0)
        {
            return -1;
        }
    }
    else
    {
        LOG_PRINT(INFO,"[ENCAPS:: ]->BSC_ID not found in CONF file\n");
        return -1;
    }
 
}
/*****************************************************************************
**      FUNCTION :
**         bssap_get_conf_file
******************************************************************************
**
**      DESCRIPTION :
**          This is for Read Config file from Env for BSSAP
**
**      NOTE :
**
*****************************************************************************/
int
bssap_get_conf_file
(char *filename)
{
  int ret_result = 0;
  char *my_path;
  my_path = getenv("CONFIG");
    if (my_path == (char *)0)
    {
      LOG_PRINT(INFO,"[ENCAPS:: ] Environment variable not set \n");
      ret_result = -1;
    }
    else
    {
      sprintf (filename, "%s/%s", my_path, BSSAP_CONF_FILENAME);
    }
}

/*****************************************************************************
**      FUNCTION :
**         cd_get_param
******************************************************************************
**
**      DESCRIPTION :
**          This function gets parameters from conf file
**
**      NOTE :
**
*****************************************************************************/
int cd_get_param
(char *filename,
 char *key_string,
 char *return_string)
{
  FILE *fptr;
    int ret_result = -1;
    char  key_string_buf[MAX_KEY_SIZE];

    if ((fptr = fopen(filename, "r")) == (FILE *)0)
    {
         LOG_PRINT(INFO,"[ENCAPS:: ] cd_get_param :  Cannot open file %s for reading ", filename);
      return(-1);
    }
 while (fgets(return_string, MAX_BUFF_SIZE, fptr) != NULL)
    {
      if (sscanf(return_string, "%s", key_string_buf) <= 0)
        continue;

      if (!strcmp(key_string_buf, "#"))
      {
#ifndef WINNT
          fflush(fptr);
#endif
        continue;
      }

      if (strlen(key_string_buf) == 0)
          continue;

      if (!strcmp(key_string, key_string_buf))
      {
          ret_result = 0;
          break;
      }
    }

    fclose(fptr);
    return(ret_result);
}

/***************************************************************************
**
**           FUNCTION : get_buffer_length
**
**
**
****************************************************************************
**
**           DESCRIPTION : return the length of the buffer
**
**           NOTE :
**
*************************************************************************/
int
get_buffer_length(const void *buf)
{
  unsigned char lsb, msb;
  int length;

  lsb =  *((const unsigned char *)buf+3);
  msb =  *((const unsigned char *)buf+4);

  length = (lsb | (msb <<8)) ;

  return (length);
}

/*****************************************************************************
 **
 **  FUNCTION NAME
 **      bssap_send_to_user
 **
 ******************************************************************************
 **
 **  DESCRIPTION
 **      This function send if any message comes from BSSAP to APP.
 **
 **  INPUTS
 ** 
 **  RETURNS
 **      NONE
 **
 *****************************************************************************/
void bssap_send_to_user
( const void *        buffer,s7_len_t noctets
)
{
    unsigned int len;
    unsigned int length;
    
    if (buffer == NULL)
    return;	
    len =  noctets;

    if (bssap_user_sock_send[0] != SOC_MGR_INVALID_SOC_FD)
    {
        if ((unsigned)soc_mgr_send_api_user(bssap_user_sock_send[0],(const unsigned char *)buffer,((const unsigned char *)buffer+SS7_BSSAP_APP_API_HEADER_LEN),(len-SS7_BSSAP_APP_API_HEADER_LEN)) != (len-SS7_BSSAP_APP_API_HEADER_LEN))
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]->Message to an invalid destination\n");
        }
    }
}

#ifdef SIGTRAN_SCCP_IF
/*****************************************************************************

 **
 **  FUNCTION NAME
 **      bssap_send_to_sccp
 **
 ******************************************************************************
 **
 **  DESCRIPTION
 **      This function send if any message comes from BSSAP module to SCCP.
 **
 **  INPUTS
 ** 
 **  RETURNS
 **      NONE
 **
 *****************************************************************************/
void bssap_send_to_sccp
( const void *        buffer
)
{
    unsigned int len;
    unsigned int length;
    
    if (buffer == NULL)
    return;	
    len = (unsigned)get_buffer_length(buffer);

    if (sigtran_sccp_if_sock_send[0] != SOC_MGR_INVALID_SOC_FD)
    {
        if ((unsigned)soc_mgr_send_api(sigtran_sccp_if_sock_send[0],(const unsigned char *)buffer,((const unsigned char *)buffer+SS7_API_HEADER_LEN),(len-SS7_API_HEADER_LEN)) != (len-SS7_API_HEADER_LEN))
        {
            LOG_PRINT(INFO,"[ENCAPS:: ]->Message to an invalid destination\n");
        }
    }
}
#endif


void printBackTrace(ucontext_t *uc)
{

  void *BackTrace[BACK_TRACE_DEPTH];
  char **messages = (char **)NULL;
  int i, BackTraceSize = 0;

  BackTraceSize = backtrace(BackTrace, BACK_TRACE_DEPTH);

  messages = backtrace_symbols(BackTrace, BackTraceSize);

  /* skip first stack frame (points here) */
  backtrace_symbols_fd(BackTrace,BackTraceSize, 2);

  LOG_PRINT(CRITICAL,"\n[bt] Execution path:");
  for (i=2; i < BackTraceSize; ++i) {
    LOG_PRINT(CRITICAL,"\n[bt]#[%u]->%s",i-2,messages[i]);
  }
}

void bsc_sighandler(int signum, siginfo_t *sig_info, void *secret)
{
    ucontext_t *uc = (ucontext_t *)secret;

    LOG_PRINT(CRITICAL,"\nGot Signal [%d] [%s]",signum,strsignal(signum));
	  
    if (signum == SIGSEGV) {
      printf("\nSIGSEGV Faulty Address is [%p]",sig_info->si_addr);
    }

    printBackTrace(uc);
    LOG_PRINT(CRITICAL,"\n");
   
    signal(signum,SIG_DFL);
    kill(getpid(),signum);
    
    return ;
}

void reg_sig_hndlr()
{
    
  /* Install our signal handler */
  struct sigaction sa;
  sigset_t set;

  
  sigfillset(&set);

  sigdelset(&set, SIGSEGV);
  sigdelset(&set, SIGFPE);
  sigdelset(&set, SIGABRT);
  sigdelset(&set, SIGKILL);
  sigdelset(&set, SIGINT);
  sigdelset(&set, SIGTERM);

  pthread_sigmask(SIG_SETMASK, &set, NULL);
  sa.sa_sigaction = bsc_sighandler;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;

  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGFPE , &sa, NULL);
  sigaction(SIGABRT , &sa, NULL);
  sigaction(SIGKILL , &sa, NULL);
  sigaction(SIGTERM , &sa, NULL);
  /* ... add any other signal here */

  return ;
}


