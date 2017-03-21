/****************************************************************************
 *                                                                          *
 * Copyright 1997-1999 IntelliNet Technologies, Inc. All Rights Reserved.   *
 *             Manufactured in the United States of America.                *
 *       1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.       *
 *                                                                          *
 *   This product and related documentation is protected by copyright and   *
 *   distributed under licenses restricting its use, copying, distribution  *
 *   and decompilation.  No part of this product or related documentation   *
 *   may be reproduced in any form by any means without prior written       *
 *   authorization of IntelliNet Technologies and its licensors, if any.    *
 *                                                                          *
 *   RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      *
 *   government is subject to restrictions as set forth in subparagraph     *
 *   (c)(1)(ii) of the Rights in Technical Data and Computer Software       *
 *   clause at DFARS 252.227-7013 and FAR 52.227-19.                        *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 * CONTRACT: INTERNAL                                                       *
 *                                                                          *
 ****************************************************************************
 *
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:31  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:13  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.1.1.1  2007/03/08 15:14:23  cvsadmin
 * LOG: BSC project
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:46  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.4  2005/03/21 13:52:17  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.2.10.1  2004/09/29 09:56:14  asingh
 * LOG: Changes for linux ES 30 operating system; compilation issue.
 * LOG:
 * LOG: Revision 7.2  2003/01/28 23:17:10  mmiers
 * LOG: Make sure the class records are correctly exported.
 * LOG: Flesh out ring buffer class (not done yet).
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:10:05  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:28  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:14  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:17  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 1.6  2001/03/09 18:33:25  mmiers
 * LOG: Convert to DLL modifier.
 * LOG:
 * LOG: Revision 1.5  2001/03/05 23:35:08  lbana
 * LOG: gotback socket fixes fixed by Mitch
 * LOG:
 * LOG: Revision 1.3  2001/02/20 19:00:57  mmiers
 * LOG: Assert removal
 * LOG:
 * LOG: Revision 1.2  2001/02/12 21:42:33  lbana
 * LOG: ident macro is defined
 * LOG:
 * LOG: Revision 1.1  2001/02/12 21:11:35  lbana
 * LOG: vxworks platform specific for sockets
 * LOG:
 *
 ***************************************************************************/
#include <netinet/in.h>

#include <its.h>
#include <its_assertion.h>

#if !defined(vxworks)
#include <error.h>
#else
#include <errno.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

#include <vxWorks.h>
/*Include net files. */
#include <netinet/tcp.h>

#include <its_sockets.h>

/* 
 * [get set]hostbyname and vis-versa is not defined in netdb.h 
 * need to include hostLib.h and resolvLib.h also here.
 *
 */
#include <netdb.h>
#include <resolvLib.h>
#include <hostLib.h>
#include <inetLib.h>
#include <selectLib.h>

#include <arpa/inet.h>

#include <ioLib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
/* no unix domain or pipe addr struct */

#include <its_timers.h>

#ident "$Id: its_sockets.c,v 1.1.1.1 2007-10-08 11:11:59 bsccs2 Exp $"

#ifndef SOMAXCONN
#define SOMAXCONN 25
#endif

/*
 * What is VxWorks
 */


/*local definition, maximum amount of times to retry hostname resolution */
#define MAX_RESOLVE_ATTEMPTS 12

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_CreateAddr
 *
 *  Purpose:
 *      Create the address structure appropriate for an INET addr
 *
 *  Input Parameters:
 *      host - the hostname or IP address (second form is dotted quad).
 *      port - the port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      sin - the INET address
 *      NULL - an error occurred
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_CreateAddr(ITS_SOCK_DOMAIN domain,
                const char* host_or_path, int port,
                void **data, int *size)
{
    /* VxWorks doesn't support UNIX domain */
    if(domain != INET_DOMAIN)
    {
       *data = NULL;
       *size = 0;
       
       return ITS_EINVALIDARGS;
    }

    {
       struct sockaddr_in *sin;           /* ptr to INET domain addr data */ 
       u_long 		  addr;
       ITS_BOOLEAN        status = ITS_TRUE; /* find the DNS query success/failure */

#if defined(USE_DNS)
       int    i;                          /* loop iterator */
       struct hostent *hostinfo = NULL;   /* host resolution structure */
       int    attempts = 0;
       int    done = ITS_FALSE;

       /*
        * Try for up to one minute to resolve hostname 
        * Close socket on failure because if we can't   
        * resolve then we don't have a use for it        
        */
       while (!done) 
       {
           if(isalapha(host_or_path[0]) > 0 ) /* if it is char ret val > 0 */
           {
              if( (addr = hostGetByName(host_or_path) == ERROR)
              {
                   status = ITS_FALSE;
                   perror("DNSerror\n");
              }
           }
           else
           {
              if( (addr = inet_addr(host_or_path)) == ERROR)
              {
                  status = ITS_FALSE;
                  if( (addr = hostGetByName(host_or_path)) != ERROR)
                  {
                      status = ITS_TRUE;
                  }
              }
              else
              {
                  char hostName[64];
                  int  temp;

                  temp = hostGetByAddr(addr, hostName);

                  if (temp == ERROR)
                  {
                      status = ITS_FALSE;
                      if( (addr = hostGetByName(host_or_path)) != ERROR)
                      {
                          status = ITS_TRUE;
                      }
                  }
              }
           }

           /* if DNS query fails */           
           if(status == ITS_FALSE)
           {
             /*
              * If the error is TRY_AGAIN do so unless we have tried to 
              * often already, in which case just timeout 
              */
              switch (h_errno) 
              {    
               case TRY_AGAIN:
                  if (++attempt > MAX_RESOLVE_ATTEMPTS) 
                  {
                      return (ITS_EBADHOST);
                  } 
                  else
                  {
                      done = ITS_FALSE;

                      TIMERS_Sleep(5);
                  } 
                  break; 

                  /* Any other error we just give up */ 
               default:
                  return (ITS_EINVALIDARGS);
              }
           }
       }

#else /* if No DNS */       

    addr = inet_addr(host_or_path);

    if ((int)addr == -1)
    {
        return (ITS_EBADHOST);
    }

#endif /* USE_DNS */

       /* allocate memory for sin */
       if( (sin = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in))) == NULL)
       {
           return ITS_ENOMEM;
       }

       sin->sin_family = AF_INET;
       sin->sin_port  = htons(port);
              
       sin->sin_addr.s_addr = addr;

       sin->sin_len = (ITS_OCTET) sizeof(struct sockaddr_in);

       *data = sin;
       *size = sin->sin_len;
    }

return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
 *
 *  Purpose:
 *      This will create a client socket and resolve the target server's 
 *      hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN                        INET_DOMAIN
 *      char *                             hostname of steam pathname of server
 *      int                                port number of server socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ClientOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
   if(domain != INET_DOMAIN)
   {
      return ITS_EINVALIDARGS;
   }
   
   {
      int            dummy = 1;         /* for setsockoption() */
      ITS_SocketInfo *ret = NULL;
      struct linger  linger;
   
      /*make sure the address is good */
      ITS_C_ASSERT(sockInfo != NULL);

      /*Set up our address info accounting */
      if( (ret = calloc(1, sizeof(ITS_SocketInfo))) == NULL)
      {
         return (ITS_ENOMEM);
      }
  
      /* get the address */
      if(SOCK_CreateAddr(domain, host_or_path, port, 
                         &ret->addr, &ret->asize) != ITS_SUCCESS)
      {
          free(ret);
          return ITS_EBADHOST;  
      }
      
      if( (ret->socket = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
      {
         free(ret->addr);           /* mem is allocated in SOCK_CreateAddr */  
         free(ret);
         perror("Ctcp_socket");        /* for min debug info */

         return ITS_ENOSOCKET;
      }
 
      linger.l_onoff = 1;
      linger.l_linger = 0;
    
      /* To make sure all UN ACK data in Tx channel are ACKed. */
      setsockopt(ret->socket, SOL_SOCKET, SO_LINGER, 
                  (char *)&linger, sizeof(struct linger));               
      
      ret->type = SPROT_TYPE_TCP_CLIENT;
      ret->af   = AF_INET;

      *sockInfo = ret;  

      /* to avoid bind() fail because of zombie ions */
      setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR, 
                 (void *)&dummy, sizeof(int));
   }  
   
   return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientOpen.
 *
 *  Purpose:
 *     Create a server socket and resolve hostname (why a hostname?  don't 
 *     ask me I didn't write this I am just cleaning it up.  I suspect the 
 *     client was written first and modified into this... ) 
 *
 *  Input Parameters:
 *      SOCK_DOMAIN         INET_DOMAIN or UNIX_DOMAIN 
 *      host_or_path        hostname (of what, self??) 
 *      port                port number (of what, self??) 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured 
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ServerOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                const char *host_or_path, int port) 
{
   if(domain != INET_DOMAIN)
   {
      return ITS_EINVALIDARGS;
   }

   {
      int 		dummy = 1;                     /* for setsocketopt() */
      ITS_SocketInfo	*ret;
      struct linger     linger;

      /* make sure the address is good */
      ITS_C_ASSERT(sockInfo != NULL);
      
      if( (ret = calloc(1, sizeof(ITS_SocketInfo))) == NULL)
      {
          return ITS_ENOMEM;
      }

      /* get the address */
      if(SOCK_CreateAddr(domain, host_or_path, port, 
                         &ret->addr, &ret->asize) != ITS_SUCCESS)
      {
          free(ret);
          return ITS_EBADHOST;
      }
      
      if( (ret->socket = socket(AF_INET, SOCK_STREAM, 0)) == ERROR)
      {
          free(ret->addr);        /* mem is allocated in SOCK_CreateAddr */  
          free(ret);
          perror("Stcp_socket");     /* for min debug info */
   
          return ITS_ENOSOCKET;
      }

      ret->type = SPROT_TYPE_TCP_SERVER;
      ret->af   = AF_INET;
 
      linger.l_onoff = 1;
      linger.l_linger = 0;
   
      /* To make sure all UN ACK data in Tx channel are ACKed. */ 
      setsockopt(ret->socket, SOL_SOCKET, SO_LINGER, 
                   (char *)&linger, sizeof(struct linger));
   
      *sockInfo = ret; 

      setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR, 
                 (void *)&dummy, sizeof(int));

      /* bind to the port specified */
      if(bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize)
           == ERROR)
      {
          free(ret->addr);
          close(ret->socket);
          free(ret);
          perror("Stcp_bind");

          return ITS_EBINDFAIL;
      }

      /* Set up a listen queue */
      if(listen(ret->socket, SOMAXCONN) == ERROR)
      {
          free(ret->addr);
          close(ret->socket); 
          free(ret);
          perror("Stcp_listen");
 
          return ITS_ELISTENFAIL;
      }    
   }            
   
   return ITS_SUCCESS;     
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_EndPointOpen.
 *
 *  Purpose:
 *     Create an end socket and resolve hostname
 *
 *  Input Parameters:
 *      host_or_path        local hostname
 *      port                local port number
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - an error occured 
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_EndPointOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
                  const char *host_or_path, int port) 
{
    if(domain != INET_DOMAIN)
    {
        return ITS_EINVALIDARGS;
    }
    
    {
        int            dummy = 1;
        ITS_SocketInfo *ret;
        
        /* make sure the address is good */
        ITS_C_ASSERT(sockInfo != NULL);

        if( (ret = calloc(1, sizeof(ITS_SocketInfo))) == NULL)
        {
            return ITS_ENOMEM;
        }

        /* get the address */
        if(SOCK_CreateAddr(domain, host_or_path, port, 
                           &ret->addr, &ret->asize) != ITS_SUCCESS)
        {
            free(ret);
            return ITS_EBADHOST;         
        }
 
        if(socket(ret->socket, SOCK_DGRAM, 0) == ERROR)
        { 
            free(ret->addr);
            free(ret);
            perror("udp_socket");
   
            return ITS_EBADSOCKET; 
        }

        ret->type = SPROT_TYPE_UDP;               
        ret->af   = AF_INET;
 
        *sockInfo = ret;

        /* To avoid bind() fail because of zombie connections */
        setsockopt(ret->socket, SOL_SOCKET, SO_REUSEADDR, (void *)&dummy, sizeof(int));

        if(bind(ret->socket, (struct sockaddr *)ret->addr, ret->asize) == ERROR)
        {
            free(ret->addr);
            close(ret->socket);
            free(ret); 
            perror("upd_bind");

            return ITS_EBINDFAIL;
        }
    }
    
    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_RawOpen.
 *
 *  Purpose:
 *      This will create a raw socket and resolve the target server's 
 *      hostname.
 *
 *  Input Parameters:
 *      SOCK_DOMAIN                        INET_DOMAIN or UNIX_DOMAIN
 *      char *                             hostname of steam pathname of server
 *      int                                port number of server socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS - success
 *      Anything else - Something bad happened
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_RawOpen(ITS_SocketInfo **sockInfo, ITS_SOCK_DOMAIN domain,
             const char *host_or_path, int port, int pf,
             ITS_BOOLEAN autoHeaders) 
{
    if(domain != INET_DOMAIN)
    {
       return ITS_EINVALIDARGS;
    }
    
    {
       int dummy = 1;
       ITS_SocketInfo *ret;
       
       /* make sure the address is good */
       ITS_C_ASSERT(sockInfo != NULL);
 
       if( (ret = calloc(1, sizeof(ITS_SocketInfo))) == NULL)
       {
           return ITS_ENOMEM;
       }

       if(SOCK_CreateAddr(domain, host_or_path, port,
                        &ret->addr, &ret->asize) != ITS_SUCCESS)
       {
           free(ret);
           return (ITS_EBADHOST);
       }
     
       if( (ret->socket = socket(AF_INET, SOCK_RAW, 0)) == ERROR)
       {
           free(ret->addr);
           free(ret);
           perror("Rsocket");

           return ITS_EBADSOCKET;
       }

       ret->type = SPROT_TYPE_RAW;
       ret->af   = AF_INET;
 
       *sockInfo = ret;

       if(autoHeaders)
       { 
           setsockopt(ret->socket, IPPROTO_IP, IP_HDRINCL,(void *)&dummy, sizeof(int));
       }
    }

    return ITS_SUCCESS;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Pending.
 *
 *  Purpose:
 *      Use this to see how many bytes can be gotten from a subsequent read() 
 *      call.  Note that this will return a number meaning that _at least_ so 
 *      many bytes can be read, because more data may be received in between 
 *      the time this call is made and the actual read() system call is made
 *
 *  Input Parameters:
 *      int     sock                File descriptor to check
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      <0              An error occured
 *      (Other)         Number of bytes available (may be 0)
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_Pending(ITS_SocketInfo *info)
{
    int bytes_pending = 0;       /* ioctl() will fill in with #bytes ready */  
    int rc;                      /* return code */  

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /* If error display and return -1 else return bytes pending */ 
    if (ioctl(info->socket, FIONREAD, &bytes_pending) < 0) 
    {
        rc= ITS_EINVALIDARGS; 
    } 
    else
    {    
        rc = bytes_pending; 
    }

    return rc;
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ReadyToRead.  
 *
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      int    sock              File descriptor to check 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_TRUE - data pending
 *      ITS_FALSE - no data or error.
 *
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_ReadyToRead(ITS_SocketInfo* info) 
{
    fd_set fds;

    if (!info)
    {
        return (ITS_FALSE);
    }

    FD_ZERO(&fds);
#if !defined(vxworks)
    FD_SET(&fds, info->socket);
#else
    FD_SET(info->socket, &fds);
#endif

    if (select(info->socket + 1, &fds, NULL, NULL, NULL) > 0)
    {
        return (ITS_TRUE);
    }
    else
    {
        return (ITS_FALSE);
    }
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ClientConnect.
 *
 *  Purpose:
 *      Connect a socket, if it is a tcp socket disable that pesky nagle 
 *      algorithm
 *
 *  Input Parameters:
 *      int sock        file descriptor to connect() with
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS      if everything is OK
 *      Anything else    if it's all gone horribly wrong
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ClientConnect(ITS_SocketInfo* info)
{
    int ret;
    struct protoent     *ent;                /* For use in disabling nagle */ 
    int flag = 1;                            /* For use in disabling nagle */

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    /*
     * Attempt connection 
     */
    if( (ret = connect(info->socket, (struct sockaddr *)info->addr, 
                                       info->asize)) < 0)
    {
        return (ITS_ECONNECTFAIL);
    } 

    /*
     * Disable TCP NAGLE algorighm. (don't delay short messages waiting for 
     * window ack)
     */
    if (info->af == AF_INET) 
    {    
        setsockopt(info->socket, IPPROTO_TCP,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    /*
     * fini 
     */
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_ServerAccept.
 *
 *  Purpose:
 *      Accept a connection and disable the NAGLE algorithm (queue short 
 *      messages waiting for window ack) support on connection 
 *
 *  Input Parameters:
 *      int sock                file descriptor to accept on 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_SUCCESS           file descriptor of connection 
 *      Anything else         something is wrong     
 *
 ****************************************************************************/
ITSDLLAPI int
SOCK_ServerAccept(ITS_SocketInfo* info, ITS_SocketInfo **newInfo)
{
    int    flag = 1;          /* for setsockopt() call */
    struct protoent    *ent;  /* protocol entry */ 
    ITS_SocketInfo* tmp;

    if (!info)
    {
        return (ITS_ECONNECTFAIL);
    }

    ITS_C_ASSERT(newInfo != NULL);

    *newInfo = NULL;

    /* allocate info struct */
    if ((tmp = (ITS_SocketInfo *)calloc(1, sizeof(ITS_SocketInfo))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    /* Allocate storage for addr structure */ 
    if ((tmp->addr = (struct sockaddr_in *)calloc(1, sizeof(struct sockaddr_in)))
        == NULL)
    {    
        return (ITS_ENOMEM);
    }

    /* Accept a connection */ 
    tmp->asize = sizeof(struct sockaddr_in);
    tmp->socket = accept(info->socket, (struct sockaddr *)tmp->addr, &tmp->asize);

    /*
     * If the return code is 0 or greater it is a file descriptor 
     * (technically this is an err, but you will never see a file 
     * descriptor of zero so I'm leaving the code as is        
     */
    if (tmp->socket <= 0) 
    {
        /* We could not accept so we do not need this memory anymore */
        free(tmp->addr);
        free(tmp);

        return (ITS_EBADSOCKET);
    }

    /* Update our socket data info */ 
    tmp->af = ((struct sockaddr_in *)tmp->addr)->sin_family;

    /* Get rid of nagle support */ 
    /* if (tmp->af == AF_INET && (ent = getprotobyname("tcp")) != NULL)  */
    if (tmp->af == AF_INET)  
    {    
        setsockopt(tmp->socket, IPPROTO_TCP,
                   TCP_NODELAY, (char *)&flag, sizeof(flag));
    }

    *newInfo = tmp;

    /* fini */ 
    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Read.
 *
 *  Purpose:
 *      Read whatever data is on the socket, keep doing it until we get all 
 *      data or a closed peer
 *
 *  Input Parameters:
 *      int sock                       file descriptor of this socket
 *      char *buf                      pointer to where you want to stick data
 *      int nbytes                     the number of bytes you expect to read
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  0                    peer has closed connection or there was an error 
 *                       and thus far no data has been read 
 *
 *  >0                   This much data has been read.  There may or 
 *                       may not have been an error. 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Read(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int     nleft;                    /* Amount of data left to read */      
    int     nread;                    /* Amount of data we have read */ 
    int     done = ITS_FALSE;         /* Loop terminator for EOF      */  

    /* Set up how much we want to read */ 
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While not error or EOF and there is more data expected... */ 
    while ((nleft > 0) && (!done)) 
    {
        /* Read something */ 
        nread = read(info->socket, buf, nleft); 

        /*
         * If there was an error return # of bytes read thus far  
         * (how odd..)                                            
         */
        if (nread < 0)        
        {    
            return nread;
        }

        /* If there is an EOF set while to exit */ 
        else if (nread == 0)    
        {    
            done = ITS_TRUE; 
        }

        /* We read some data */ 
        else 
        {    
            nleft -= nread;
            buf += nread;
        }
    }

    /* Return the amount of data we read */ 
    return (nbytes - nleft);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Read.
 *
 *  Purpose:
 *      Read whatever data is on the socket, keep doing it until we get all 
 *      data or a closed peer
 *
 *  Input Parameters:
 *      int sock                       file descriptor of this socket
 *      char *buf                      pointer to where you want to stick data
 *      int nbytes                     the number of bytes you expect to read
 *      void *from                     who the message came from
 *      int *len                       length of the orig addr
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *  0                    peer has closed connection or there was an error 
 *                       and thus far no data has been read 
 *
 *  >0                   This much data has been read.  There may or 
 *                       may not have been an error. 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Recv(ITS_SocketInfo* info, char *buf, int nbytes, void* from, int* len) 
{
    if (!info)
    {
        return (0);
    }

    /* Read something */ 
    return recvfrom(info->socket, buf, nbytes, 0, from, len); 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingRead.
 *
 *  Purpose:
 *      This is a nonblocking read that will timeout if it does not receive the
 *      specified amount of data in the time indicated.   
 *
 *  Input Parameters:
 *      int fd                   file descriptor of socket to read from 
 *      char *dataptr            pointer to buffer to write to 
 *      int datasize             amount of bytes to attempt reading 
 *      int maxtime              time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes read
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingRead(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t     start_time, now_time;    /* Used to check for timeout */  
    int        ioctl_val = 1;           /* value for ioctl() call */
    int        br = 0;                  /* bytes read in single read() */ 
    int        rc = 0;                  /* function return code */ 
    int        done = ITS_FALSE;            /* while() terminator */ 
    int        totalread = 0;           /* bytes read in total */ 

 
    /* Note the time we started */ 
    time(&start_time); 

    if (!info)
    {
        return (0);
    }

    /* Set this socket to nonblocking */ 
    ioctl_val = 1;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    }  

    /* While we are not done, try to read */ 
    while(!done) 
    {
        /* Read some data */ 
        switch ((br = read(info->socket, buf + totalread, size - totalread)))
        {
            /* An error has occured */ 
            case -1: 
            switch(errno) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case EAGAIN: 
            case EINPROGRESS:  
                break; 

            /* Recover from interrupt errors */ 
            case EINTR: 
            case EDEADLK: 
            case EBUSY:
                break; 
 
            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

            /* EOF (peer has closed connection) */ 
            case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

            /* We have read some amount of data */ 
            default:
            totalread += br;   
            if (totalread >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalread;
 
        /*
         * Check to see if we have timed out if we are not already done 
         */
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
            }
        }
    } 

   /* Set this socket back to blocking */
   ioctl_val = 0; 
   if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
   {
       /* what to do? */
   }

    /* fini */
    return rc; 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Write.
 *
 *  Purpose:
 *      Write a fixed amount of data (or as much as you can) out over a socket 
 *
 *  Input Parameters:
 *      int sock             file descriptor of socket 
 *      char *buf            pointer to data to write out 
 *      int nbytes           size of data to write 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                   Some sort of error occured and no data send 
 *      other               Amount of data that was sent (which could be less
 *                          than requested) 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Write(ITS_SocketInfo* info, char *buf, int nbytes) 
{
    int    nleft;
    int    nwritten;

    /* Set up how much we need to write */ 
    nleft = nbytes;

    if (!info)
    {
        return (0);
    }

    /* While still bytes to write do so */ 
    while (nleft > 0)
    {
        /* Write some data */ 
        nwritten = write(info->socket, buf, nleft); 

        /* If any of these errors return # actually written */ 
        if (nwritten <= 0 && 
            (errno != EINTR &&   errno != EBUSY &&
             errno != EDEADLK && errno != EWOULDBLOCK &&
             errno != EINPROGRESS))    /* error, or zero length write */
        {
            return nwritten;
        }

        /* else adjust counters and keep going */
        else
        {
            /*
             * If the return code was -1 (error) set to zero so we 
             * do not end up losing data!!!                        
             */
            if (nwritten == -1)
            {    
                nwritten = 0;
            }

            /*
             * Note that the buf pointer is incremented as opposed to 
             * doing a write to buf+nwritten (which might have been a  
             * bit more clear).
             */
            nleft -= nwritten;
            buf += nwritten;
        }
    }

    /* Return how much we actually wrote */ 
    return (nbytes - nleft);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Write.
 *
 *  Purpose:
 *      Write a fixed amount of data (or as much as you can) out over a socket 
 *
 *  Input Parameters:
 *      int sock             file descriptor of socket 
 *      char *buf            pointer to data to write out 
 *      int nbytes           size of data to write 
 *      void *to             address to send to
 *      int len              length of addr to send to
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                   Some sort of error occured and no data send 
 *      other               Amount of data that was sent (which could be less
 *                          than requested) 
 ****************************************************************************/
ITSDLLAPI int
SOCK_Send(ITS_SocketInfo* info, char *buf, int nbytes, void* to, int len) 
{
    /* Write some data */ 
    return sendto(info->socket, buf, nbytes, 0, to, len); 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NonBlockingWrite.
 *
 *  Purpose:
 *      This is a nonblocking write that will timeout if it does not receive the
 *      specified amount of data in the time indicated. 
 *
 *  Input Parameters:
 *      int fd                  file descriptor of socket to write from 
 *      char *dataptr           pointer to buffer to write to 
 *      int datasize            amount of bytes to attempt writeing 
 *      int maxtime             time in seconds to wait for data 
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      0                          EOF or TIMEOUT or ERROR has occured  
 *      default                    The amount of bytes actually written
 ****************************************************************************/
ITSDLLAPI int
SOCK_NonBlockingWrite(ITS_SocketInfo* info, char *buf, int size, int maxtime) 
{ 
    time_t    start_time, now_time;        /* Used to check for timeout */  
    int       ioctl_val = 1;              /* value for ioctl() call */
    int       br = 0;                    /* bytes write in single write() */ 
    int       rc = 0;                    /* function return code */ 
    int       done = ITS_FALSE;              /* while() terminator */ 
    int       totalwrite = 0;           /* bytes write in total */ 
    int       write_attempt_size = 0;     /* Amount of bytes to attempt */ 
                                           /* to write on a single write()*/ 
 
    /* Note the time we started */ 
    time(&start_time); 

    if (!info)
    {
        return (0);
    }

    /* Set this socket to nonblocking */ 
    ioctl_val = 1;
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0) 
    {
        return (0);
    } 

    /* While we are not done, try to write */ 
    while(!done) 
    {
        /* Optimize write for ethernet */ 
        write_attempt_size = size - totalwrite; 
        if (write_attempt_size > 1400) 
        {
            write_attempt_size = 1400; 
        } 
    
        /* Read some data */ 
        switch((br = write(info->socket, buf + totalwrite, write_attempt_size)))
        {
        /* An error has occured */ 
        case -1: 
            switch(errno) 
            {
            /* Resource temporarily unavailable (no data yet) */ 
            case EAGAIN: 
            case EINPROGRESS:  
                break; 

            /*
             * Recover from intterupted system calls and that lot 
             * In these cases return with whatever data we wrote   
             */
            case EINTR: 
            case EBUSY: 
            case EDEADLK: 
                break; 

            /* Any other error */ 
            default: 
                done = ITS_TRUE;
                rc = 0;  
                break; 
            } 
            break; 

            /* EOF (peer has closed connection) */ 
            case 0:
            done = ITS_TRUE;
            rc=0;  
            break;

            /* We have write some amount of data */ 
            default:
            totalwrite+=br;   
            if (totalwrite >= size) 
            {    
                done = ITS_TRUE;
            } 
            break; 
        }
        
        /* Set the return code (may be reset in timeout below) */ 
        rc = totalwrite;
 
        /* Check to see if we have timed out if we are not already done */ 
        if (!done) 
        {    
            time(&now_time); 
            if (now_time > start_time + maxtime) 
            {    
                done = ITS_TRUE;
                rc = 0; 
            }
        }
    } 

    /* Set this socket back to blocking */
    ioctl_val = 0; 
    if (ioctl(info->socket, FIONBIO, &ioctl_val) < 0)
    {
        /* what to do here */
    }

    /* fini */
    return rc; 
} 

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_Close.
 *
 *  Purpose:
 *      Close the socket, delete any stream files that may be littering 
 *      the file system and remove the socket data from the tracking structure
 *
 *  Input Parameters:
 *      int sock                                socket handle
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      void
 ****************************************************************************/
ITSDLLAPI void
SOCK_Close(ITS_SocketInfo* info)
{
    struct sockaddr_in *aun;

    if (!info)
    {
        return;
    }

    if (info->socket >= 0)
    {
        /* Close the socket handle */ 
        close(info->socket);

        /* Remove from our dataspace */ 
        free(info->addr);
    }

    free(info);
 
    return; 
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_DebugDump.  
 *
 *  Purpose:
 *      Dump out all the accounting info we have been maintaining on a 
 *      given socket
 *
 *  Input Parameters:
 *      int sock                        file descriptor of socket
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
ITSDLLAPI void
SOCK_DebugDump(ITS_SocketInfo* info) 
{
#if 0
    struct hostent *hostinfo;
    struct in_addr in;

    TRACE_DEBUG(("sock_debug_dump: SOCKET DEBUG INFO:\n"));
    TRACE_DEBUG(("sock_debug_dump: fd: %d  address family: %s\n",
                 info->socket,
                 info->af == AF_INET ? "AF_INET" : "AF_UNIX"));

    /* If this is a socket... */ 
    if (info->af == AF_INET) 
    {
        /*
         * Print address and hostname if available 
         * Print out the port in any case          
         */
        in = ((struct sockaddr_in *)info->addr)->sin_addr;
        if ((hostinfo = gethostbyaddr((char *)&in, sizeof(struct in_addr),
                                      AF_INET)) != NULL)
        {    
            TRACE_DEBUG(( "address: %-16.16s  hostname: %s\n",
                    inet_ntoa(in), hostinfo->h_name));
        } 
        else
        {    
            TRACE_DEBUG (("address: %-16.16s  hostname: unresolved\n",
                    inet_ntoa(in)));
        }

        TRACE_DEBUG (("port: %d\n",
             ntohs(((struct sockaddr_in *)info->addr)->sin_port)));
    }

    /* This is not a socket, it must be a stream */ 
    else 
    {    
        TRACE_DEBUG(("path: %s\n",
                    ((struct sockaddr_un *)info->addr)->sun_path));
    }

    /* fini */ 
    return; 
#endif
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetPeerName
 *
 *  Purpose:
 *      Determine the address information for a connected peer.
 *
 *  Input Parameters:
 *      in - pointer to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      out - pointer to ITS_SocketInfo
 *
 *  Return Value:
 *      ITS_SUCCESS - address of connected peer is in "out".
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetPeerName(ITS_SocketInfo* in, ITS_SocketInfo* out)
{
    out->socket = in->socket;
    out->type = in->type;

    if ((out->addr = calloc(1, sizeof(struct sockaddr))) == NULL)
    {
        return (ITS_ENOMEM);
    }

    out->asize = sizeof(struct sockaddr);

    if (getpeername(in->socket, out->addr, &out->asize) != 0)
    {
        free(out->addr);

        return (ITS_EBADSOCKET);
    }

    out->af = in->af;

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_AddrsAreEqual
 *
 *  Purpose:
 *      Determine if the address information for two connections
 *
 *  Input Parameters:
 *      a1, a2 - pointers to ITS_SocketInfo
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      ITS_FALSE - addrs are not equal
 *      ITS_TRUE - addrs are equal
 *
 *  Notes:
 *      The actual file descriptors for the sockets are not included
 *      in the equality check.
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_BOOLEAN
SOCK_AddrsAreEqual(ITS_SocketInfo* a1, ITS_SocketInfo* a2)
{
    if (a1->type != a2->type ||
        a1->af != a2->af ||
        a1->asize != a2->asize ||
        memcmp(a1->addr, a2->addr, a1->asize) != 0)
    {
        return ITS_FALSE;
    }

    return (ITS_TRUE);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from network order to host order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_NToHL(ITS_ULONG ulong)
{
    return ntohl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from network order to host order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_NToHS(ITS_USHORT ushort)
{
    return ntohs(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned long from host order to network order
 *
 *  Input Parameters:
 *      ulong - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_ULONG
SOCK_HToNL(ITS_ULONG ulong)
{
    return htonl(ulong);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_NToHL
 *
 *  Purpose:
 *      Convert an unsigned short from host order to network order
 *
 *  Input Parameters:
 *      ushort - the value to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      The converted value
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI ITS_USHORT
SOCK_HToNS(ITS_USHORT ushort)
{
    return htons(ushort);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_Poll(ITS_SockPollInfo *socks, int nsocks, int usecs)
{
    int i;
    fd_set reads, writes;
    int ret, max;

    if (nsocks < 0 ||
        (usecs == SOCK_POLL_WAIT_FOREVER && nsocks == 0))
    {
        return (ITS_EINVALIDARGS);
    }

    FD_ZERO(&reads);
    FD_ZERO(&writes);

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

    if (ret < 0)
    {
        return (ITS_EBADSOCKET);
    }

    if (ret == 0)
    {
        return (ITS_SUCCESS);
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
    }


    return (ret);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetLocalAddrs()
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetLocalAddrs(SOCK_AddrStore **addrs, SOCK_AddrStore **masks,
                   SOCK_AddrStore **bcasts)
{
    struct ifconf cf;
    struct ifreq *ifrequest;
    u_int intf_flags;
    int numints, i, numAddrs, tsock, numnets;
    struct sockaddr_in *tmp;

    *addrs = *masks = NULL;

    cf.ifc_buf = malloc(8192);
    cf.ifc_len = 8192;
    if (cf.ifc_buf == NULL)
    {
        return (-1);
    }

    if ((tsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        free(cf.ifc_buf);

        return (-1);
    }

    if (ioctl(tsock, SIOCGIFCONF, (char *)&cf) == -1)
    {
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }

    numints = cf.ifc_len / sizeof(struct ifreq);

    numAddrs = numints + 1;
    ifrequest = cf.ifc_req;

    if ((*addrs = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }
    
    if ((*masks = (SOCK_AddrStore *)calloc(numAddrs,
                                           sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*addrs);
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }
    
    if ((*bcasts = (SOCK_AddrStore *)calloc(numAddrs,
                                            sizeof(SOCK_AddrStore))) == NULL)
    {
        free(*addrs);
        close(tsock);
        free(cf.ifc_buf);

        return (-1);
    }

    numnets = 0;

    for (i = 0; i < numints; i++, ifrequest++)
    {
        /* look at each network */
        if (ioctl(tsock, SIOCGIFFLAGS, (char *)ifrequest) == -1)
        {
            /* cant get the flags? */
            continue;
        }

        intf_flags = ifrequest->ifr_flags;

#ifdef SKIP_LOOPBACK
        if (ifrequest->ifr_flags & IFF_LOOPBACK)
        {
            continue;
        }
#endif

        if (ioctl(tsock, SIOCGIFADDR, (char *)ifrequest) == -1)
        {
            /* now get the address */
            continue;
        }

        if (ifrequest->ifr_addr.sa_family != AF_INET)
        {
            /* It is not a IP address skip it */
            continue;
        }

        if (((struct sockaddr_in *)(&ifrequest->ifr_addr))->sin_addr.s_addr == 0)
        {
            /* no address is set */
            continue;
        }

        /* Test to see if duplicate */
        /* some O/S's will give it to you twice */
        if (numnets)
        {
            int dup, j;
            dup = 0;

            for (j = 0; j < numnets; j++)
            {
                if (((struct sockaddr_in *)(&ifrequest->ifr_addr))->sin_addr.s_addr == 
                    ((struct sockaddr_in *)&addrs[j])->sin_addr.s_addr)
                {
                    dup = 1;

                    break;
                }
            }

            if (dup)
            {
                continue;
            }
        }

        tmp = (struct sockaddr_in *)&((*addrs)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));
        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        /* now get the netmask */
        if (ioctl(tsock, SIOCGIFNETMASK, (char *)ifrequest) == -1)
        {
            numnets++;

            continue;
        }

        tmp = (struct sockaddr_in *)&((*masks)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));

        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        if (ioctl(tsock, SIOCGIFBRDADDR, (char *)ifrequest) == -1)
        {
            numnets++;

            continue;
        }

        tmp = (struct sockaddr_in *)&((*bcasts)[numnets]);

        memcpy(tmp, &ifrequest->ifr_addr, sizeof(struct sockaddr_in));

        tmp->sin_port = 0;
        memset(tmp->sin_zero, 0, sizeof(tmp->sin_zero));
        tmp->sin_family = AF_INET;

        numnets++;
    }

    if (!numnets)
    {
        if (*addrs)
        {
            free(*addrs);
            *addrs = NULL;
        }

        if (*masks)
        {
            free(*masks);
            *masks = NULL;
        }

        if (*bcasts)
        {
            free(*bcasts);
            *bcasts = NULL;
        }
    }

    close(tsock);

    return (numnets);
}

/*.implementation:extern
 ****************************************************************************
 *  Name:
 *      SOCK_GetIPv4AddrAndPort() extracts the IP addr and port from
 *      an opaque type.
 *
 *  Purpose:
 *
 *  Input Parameters:
 *      addrStruct - the address to convert
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *      port - the port
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_GetIPv4AddrAndPort(SOCK_AddrStore *addrStruct,
                        SOCK_IPv4Addr *addr,
                        ITS_USHORT *port)
{
    struct sockaddr_in *who = (struct sockaddr_in *)addrStruct;

    if (who->sin_family != AF_INET)
    {
        return (ITS_EINVALIDARGS);
    }

    *addr = SOCK_NToHL(who->sin_addr.s_addr);
    *port = SOCK_NToHS(who->sin_port);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from a name in dotted quad to an address.
 *
 *  Input Parameters:
 *      name - the name to convert.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      addr - the IP address
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4NameToAddr(const char *name, SOCK_IPv4Addr *addr)
{
    char *tmp, *tmp2;
    ITS_ULONG conv;

    /* first */
    if ((tmp = strchr(name, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv = atoi(name) << 24;

    /* second */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 16;

    /* third */
    tmp2 = tmp;
    if ((tmp = strchr(tmp, '.')) == NULL)
    {
        return (ITS_EINVALIDARGS);
    }

    *tmp = 0;
    tmp++;
    conv |= atoi(tmp2) << 8;

    /* last */
    conv |= atoi(tmp);

    *addr = SOCK_HToNL(conv);

    return (ITS_SUCCESS);
}

/*.implementation:extern
 ****************************************************************************
 *
 *  Purpose:
 *      Convert from an address to the dotted quad notation
 *
 *  Input Parameters:
 *      addr - the IP address
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      name - the string value of the name
 *
 *  Return Value:
 *      number of local addresses.  -1 on failure.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
ITSDLLAPI int
SOCK_IPv4AddrToName(char *name, SOCK_IPv4Addr addr)
{
    char buf[12];

    sprintf(buf, "%u.", addr >> 24);
    strcpy(name, buf);

    sprintf(buf, "%u.", (addr >> 16) & 0xFFU);
    strcat(name, buf);

    sprintf(buf, "%u.", (addr >> 8) & 0xFFU);
    strcat(name, buf);

    sprintf(buf, "%u", addr & 0xFFU);
    strcat(name, buf);

    return (ITS_SUCCESS);
}

/*
 * the class record
 */
ITSDLLAPI ITS_ClassRec itsSOCKET_ClassRec =
{
    /* core part */
    {
        &itsCORE_ClassRec,              /* CORE is superclass */
        0,                              /* sizeof(instance) */
        ITS_FALSE,                      /* not initted */
        0,                              /* initial ref count */
        SOCKET_CLASS_NAME,              /* class name */
        ITS_CLASS_NO_INIT,              /* class init */
        ITS_CLASS_NO_DEST,              /* class destroy */
        ITS_CLASS_PART_NO_INIT,         /* class part init */
        ITS_CLASS_PART_NO_DEST,         /* class part destroy */
        ITS_INST_NO_CONST,              /* instance create */
        ITS_INST_NO_DEST,               /* instance delete */
        ITS_INST_CLONE_INHERIT,         /* inherit clone */
        ITS_INST_PRINT_INHERIT,         /* inherit print */
        ITS_INST_SERIAL_INHERIT,        /* inherit serial */
        ITS_INST_EQUALS_INHERIT,        /* inherit equals */
        NULL                            /* no extension of interest */
    }
};

ITSDLLAPI ITS_Class itsSOCKET_Class = (ITS_Class)&itsSOCKET_ClassRec;
