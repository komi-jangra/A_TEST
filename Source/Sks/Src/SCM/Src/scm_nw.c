#include "scm_localhashdef.h"
#include <scm_encaps.h>
#include <fcntl.h>
#include <errno.h>

/**************************************************************
*  Name:                                                      *
*  scm_cm_function (void *args) //connection manager function *
*                                                             *
*  Description:                                               *
*  1) This Thread                                             *
*     -Creates & Maintains connection with other modules.     *
*     -Opens the SCM Server                                   *
*  2) Clients connections are made with                       *
*     -BSSAP                                                  *
*     -SIGTRAN                                                *
*     -PEER SCM                                               *
*     -OAM (SCMIF-OIL-CFG INTF)                               *
*  3) Server connections are Accepted from                    *
*     -SIGTRAN                                                *
*     -PEER SCM are Accepted                                  *
*  4) Also Reports the Socket connection Events to main Thread*
*     ie which entity has connected to SCM                    *
*                                                             *
**************************************************************/

void* scm_cm_function (void *args)
{
 S32 temp, ret_fd, ret_val, event_on_severFd, temp1;
 struct timeval timeout;
 fd_set scm_server;
 timeout.tv_sec  = 0;
 //timeout.tv_usec = 200;
 timeout.tv_usec = 10000;
 strcpy(g_parameter.function_string, "scm_cm_function()");
 while(1)
  {
    nano_sleep.tv_sec=0;
    nano_sleep.tv_nsec=500;
    pselect(0,NULL,NULL,NULL,&nano_sleep,NULL); 


 /*here make connection with stack & oam server */
   for(temp = 0; temp<9; temp++ )
    {
     if ((xxx_client_sockfd [ENT_PEER_SCM] == -1)||(xxx_client_sockfd [ENT_NWSTK_DBG] == -1)||
         (xxx_client_sockfd [ENT_NWSTK] == -1)      ||(xxx_client_sockfd [ENT_OAM] == -1)   ||
         (xxx_client_sockfd [ENT_SIGTRAN] == -1) || (xxx_client_sockfd [ENT_LAPD] == -1)   ||
         (xxx_client_sockfd [ENT_BSSAP] == -1))/*AOIP: BSSAP OPEN CLIENT*/
      {
       if(xxx_client_sockfd[temp] == -1)
        {
         if((temp == ENT_PEER_SCM) || (temp == ENT_NWSTK_DBG ) || (temp == ENT_NWSTK)||
             (temp == ENT_OAM)||(temp == ENT_LAPD) || (temp == ENT_SIGTRAN) || 
             (temp == ENT_BSSAP))/*AOIP: CHANGES_BSSAP LINE ADDED*/
          {
          ret_fd = setup_client(xxx_scm_ip[temp], xxx_scm_port[temp]);
           
          if( ret_fd != -1)
           {
             xxx_client_sockfd [temp] = ret_fd;
             FD_SET(xxx_client_sockfd [temp], &client_fd);
             SCM_printf(SCM_INFO,"\nENTITY UP :  %s", get_entity(temp));
       
             if (temp == ENT_NWSTK)
              {
               SCM_printf(SCM_INFO,"\nSending sync message to nwstk");
               ret_val = send_sync_mesg();
               
               if((ret_val == 0))
                {
                 close (xxx_client_sockfd [temp]);
                 if(xxx_client_sockfd [temp] > 0)
                 FD_CLR(xxx_client_sockfd [temp], &client_fd);
                 xxx_client_sockfd [temp] = -1;
                 SCM_printf(SCM_CRITICAL,"\nUnable to send sync message to nwstk");
                 continue;
                }
              }
            /*AOIP_HA*/
             switch(temp)
              {
                 case ENT_SIGTRAN:
                      if(xxx_client_sockfd [ENT_BSSAP] > 0)             /*if BSSAP CONNECTED AND SIGTRAN COMES UP*/
                       {
                         g_parameter.nwstk_cfgComplete = 0;
                         g_parameter.self_stack_up = 1;
                         SCM_printf(SCM_CRITICAL,"[JOIN] SENDING STACK ENT UP TO PEER SCM\n");
                         send_stack_enity_up_to_peerscm(ENT_BSSAP);
                       }
                 break;
                 case ENT_BSSAP:
                      if(xxx_client_sockfd [ENT_SIGTRAN] > 0)
                       {
                         g_parameter.nwstk_cfgComplete = 0;
                         g_parameter.self_stack_up = 1;
                         SCM_printf(SCM_CRITICAL,"[JOIN] SENDING STACK ENT UP TO PEER SCM\n");
                         send_stack_enity_up_to_peerscm(ENT_SIGTRAN);
                       }
                 break;
              }
             /*AOIP_HA end*/
             if(write_in_sock_event_q(temp) == 0)
              {
                SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
              }
             else
              {
               SCM_printf(SCM_INFO,"\nMessage sent to sock event queue");
              }
           }
         }
         }
       else
         continue;   
      }
     else 
       break;
    }
    /* here accept connection on scm server from isup, map/tcap, cap, peer scm */
    if(g_parameter.scm_server > 0)
      {
       for( temp= 0; temp<4; temp++)
        {
         FD_ZERO(&scm_server);
         scm_server = scm_server_fd;
           
         timeout.tv_sec  = 0;
         //timeout.tv_usec = 200;
         timeout.tv_usec = 10000;
         event_on_severFd = select(FD_SETSIZE, &scm_server,   NULL,  NULL, &timeout);
         if(event_on_severFd > 0)
          { 
           event_on_severFd = FD_ISSET(g_parameter.scm_server, &scm_server); 
          }
         if(event_on_severFd <= 0)
          break;
         else
          ret_val = accept_connction_on_server();
          if(ret_val != 0)
           {
            for(temp1 = 0; temp1<=3; temp1++)
             {
              if( xxx_severread_sockfd[temp1] == -1)
               {
                xxx_severread_sockfd[temp1] = ret_val;
                FD_SET(ret_val, &server_fds);
                SCM_printf(SCM_INFO,"\nAccepted new connection on scm server");
                break;
               }
              if(temp1 == 3)
               {  
                SCM_printf(SCM_CRITICAL,"\n CODE ERROR NO VACANT POSITION IN sever_readfd");
                break;
               }
              else continue;
            }
           } 
        }
      }
     else
       { 
        SCM_printf(SCM_CRITICAL,"\n SCM SEVER DOWN");
         for(temp=0;temp<=4;temp++)
            {
               if(xxx_severread_sockfd[temp] > 0)
               {
                close(xxx_severread_sockfd[temp]);
                FD_CLR(xxx_severread_sockfd[temp], &server_fds);
                xxx_severread_sockfd[temp] = -1;
               }
            }
        g_parameter.scm_server = setup_scm_server( xxx_scm_port[ENT_SCM] );
        if (g_parameter.scm_server != 0 )
         {
          FD_SET(g_parameter.scm_server, &scm_server_fd);
          SCM_printf(SCM_INFO,"\n SETUP SCM SERVER");
         }
        else
         {
          SCM_printf(SCM_INFO,"\n ERROR SCM SERVER CAN NOT OPEN");
          exit(0);   
         }
       } 
 }
    /*execution never reach here*/
//  pthread_exit(&dummy);
}


int accept_connction_on_server()
{
 int fromlen, result;
 U16 sock_id;
 S16  newsock;
 sock_id = g_parameter.scm_server;
 struct sockaddr_in from;
 struct linger        lg; 
 lg.l_onoff = SS7_TRUE;
 lg.l_linger = SS7_TRUE;
 fromlen = sizeof (from); 
 strcpy(g_parameter.function_string, "accept_connction_on_server()");
 if ( (newsock = accept(sock_id, (struct sockaddr *)&from, &fromlen)) <0)
  return SS7_ERROR;
 else
  {
   result = setsockopt(newsock, SOL_SOCKET, SO_LINGER, &lg, sizeof(struct linger));
   if(result <0)         
    {      
     close(sock_id);
     return SS7_ERROR;
    }
   return newsock;
  }
 return 0;
}

 

int write_in_sock_event_q( int  entity )
{
 msgbuf msgbuffer;
 msg_queue_buff *queue_buff=NULL;
 g_parameter.entity_up++;
 SCM_printf(SCM_INFO,"\nNO OF ENTITY COMES UP : [%d]", g_parameter.entity_up);
 queue_buff = (msg_queue_buff*)scm_malloc(sizeof(msg_queue_buff));
 queue_buff->entity_id = entity;
 
 
 strcpy(g_parameter.function_string, "write_in_sock_event_q()");
 if((entity == ENT_NWSTK)||(entity == ENT_SIGTRAN)||(entity == ENT_LAPD) || (entity == NWSTK_CONFIG_COMPLETE) ||
    (entity == ENT_BSSAP))/*Added for BSSAP*/
  {
   queue_buff->config_req = 1;
  } 
 else 
  queue_buff->config_req = 0;

  msgbuffer.mtype = 1;
  msgbuffer.mtext[0]= queue_buff->entity_id;
  msgbuffer.mtext[1]= queue_buff->config_req;
  memcpy(&msgbuffer.mtext[0],queue_buff, sizeof(msg_queue_buff));
  free(queue_buff);
  queue_buff = NULL;
 

  if( msgsnd ( g_parameter.soc_event_q_Id, (msgbuf*)&msgbuffer, sizeof(msgbuf)-4 , 0 ) == -1)
   {
    perror("msgsend");
    return 0;
   }
 return 1;
}





 
int setup_scm_server( U16 port_add )
{
 struct sockaddr_in servadd;
 int sock;
 const int on = 1;
 servadd.sin_family = AF_INET;
 servadd.sin_port = htons( port_add );
 servadd.sin_addr.s_addr = htonl( INADDR_ANY );
 strcpy(g_parameter.function_string, "setup_scm_server()");

 if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
   return 0;
  }
 if ( setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) <0)
  {
   close(sock); return 0;
  }
 if ( bind(sock, (struct sockaddr *) &servadd, sizeof(servadd) ) <0)
  {
   close(sock);
   SCM_printf(SCM_CRITICAL,"PORT NO. %d ALREADY IN USE\n",
              port_add);
   return 0;
  }
 if(listen (sock, 1) > 0)
  {
   close(sock); return 0;
  }
 return sock;
}





int setup_client(U8* ip_add, U16 port)
{
 int sock;
 in_addr_t ip_adds;
 strcpy(g_parameter.function_string, "setup_client()");
 struct sockaddr_in servadd;
 
 if ((ip_adds = inet_addr(ip_add)) == -1)
  {
   SCM_printf(SCM_CRITICAL,"INVALID IP ADDRESS");
   return SS7_ERROR;
  }
 servadd.sin_family = AF_INET;
 servadd.sin_port = htons( port );
 servadd.sin_addr.s_addr =  ip_adds;
/* SCM_printf(SCM_CRITICAL,"servadd.sin_port %d", servadd.sin_port);
 SCM_printf(SCM_CRITICAL,"servadd.sin_addr.s_addr %d", servadd.sin_addr.s_addr);*/
 

// memset(servadd.sin_zero,'\0',sizeof(servadd.sin_zero)); 
    
 if ( (sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
  {
   return SS7_ERROR;
  }
 /*if ( bind(sock, (struct sockaddr *) &servadd, sizeof(servadd)) <0)
  {
   close(sock);
   SCM_printf(SCM_INFO,"PORT NO. %d ALREADY IN USE\n",
              port);
   return SS7_ERROR;
  }*/
 //if ( connect(sock,  (struct sockaddr *) &servadd, sizeof(struct sockaddr_in)) < 0)
 if( handle_client_connect(sock, &servadd) == 0)
  {
   //perror("connect");
   close (sock);
   return SS7_ERROR;
  }
 return sock;
}

int handle_client_connect(int sock, void* sockAddr)
{
  int arg;
  struct timeval tv;
  socklen_t lon;
  int valopt;
  int err;
  fd_set myset;
/*  SCM_printf(CRITICAL, "sock %d", sock);
 SCM_printf(SCM_CRITICAL,"servadd.sin_port %d", servadd.sin_port);
 SCM_printf(SCM_CRITICAL,"servadd.sin_addr.s_addr %d", servadd.sin_addr.s_addr);*/
  if( (arg = fcntl(sock, F_GETFL, NULL)) < 0)
  {
     SCM_printf(CRITICAL, "connect() Error fcntl(..., F_GETFL).1 (%s)", strerror(errno));
  }
  arg |= O_NONBLOCK;
  if( fcntl(sock, F_SETFL, arg) < 0)
  {
     SCM_printf(CRITICAL, "connect() Error fcntl(..., F_SETFL).2 (%s)", strerror(errno));
  }
  err = connect(sock, (struct sockaddr *)sockAddr, sizeof(struct sockaddr));
  if (err < 0)
  {
   if(errno == EINPROGRESS)
   {
    /* SCM_printf(MAJOR, "connect() EINPROGRESS in connect() - selecting");*/
       do
      {
        tv.tv_sec = 5;
        tv.tv_usec = 100000;
        FD_ZERO(&myset);
        FD_SET(sock, &myset);
        err = select(sock + 1, NULL, &myset, NULL, &tv);
        if (err < 0 && errno != EINTR)
        {
          //SCM_printf(MAJOR, "- Couldn't connect to server, err=%d, errStr=%s", errno, strerror(errno));
          return 0;
        }
         else if (err > 0)
        {
         // Socket selected for write
          lon = sizeof(int);
          if (getsockopt(sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon) < 0)
          {
            //SCM_printf(MAJOR, "connect().2 - Couldn't connect to Server, err=%d, errStr=%s", errno, strerror(errno));
            return 0;
          }
           if (valopt)
          {
            //SCM_printf(MAJOR, "connect().3 - Couldn't connect to Master, err=%d, errStr=%s", valopt, strerror(valopt));
            return 0;
          }
          break;// this means connected successfully
        }
       else
        {
         //SCM_printf(MAJOR, "connect().4 - Timeout in select()");
         return 0;
        }
       }while(1);
     }
    else
    {
      //SCM_printf(MAJOR, "connect() != EINPROGRESS err(%d)errString(%s)",errno, strerror(errno));
      return 0;
    }
  }
  if( (arg = fcntl(sock, F_GETFL, NULL)) < 0)
  {
     SCM_printf(CRITICAL, "connect() Error fcntl(..., F_GETFL).3 (%s)", strerror(errno));
  }

  arg &= (~O_NONBLOCK);

  if( fcntl(sock, F_SETFL, arg) < 0)
  {
    SCM_printf(CRITICAL, "connect() Error fcntl(..., F_GETFL).4 (%s)", strerror(errno));
  }

 return 1;
}

/*read from server fd's where scm connected as cleint to read n write */
int scm_read_from_socket (S32 fd, U8* msg_buff, U8 app_id, U8* entity)
{
 U8 syncdata[20] ;
 S32 nread, ret_val = 0;
 U16 len, loop, resp_opcode, resp_len;
 resp_len = sizeof(ScmOamResponse);
 ScmHdr *scmhdr;
 lapd_header_t *Lapd_Hdr;
 strcpy(g_parameter.function_string, "scm_read_from_socket()");
 switch(app_id)
  {
   case ENT_NWSTK_DBG:
    {
        nread = recv(fd, (char*)syncdata, 1, MSG_PEEK);
       /*else now read syncdata */
       if(nread > 0)
        {    
          nread = read(fd, (char*)syncdata, 7);
          syncdata[7] = '\0';
          SCM_printf(SCM_INFO,"\nSYNC STRING RECEIVED  : %s ", syncdata);
          ret_val = strcmp(syncdata, "ISS7SSI");
          if((read > 0) && (ret_val == 0))
          {   
            nread = read(fd, (char*)msg_buff, 2);
            SCM_printf(SCM_INFO,"\nSRC nread: : %d ", nread);
            nread = read(fd, (char*)&msg_buff[2], 2);
            SCM_printf(SCM_INFO,"\nlen nread: : %d ", nread);
          }
          else 
           {
             nread = 0;
             if(ret_val != 0) 
             SCM_printf(SCM_INFO,"\nWRONG SYNC STRING  RECEIVED FROM DBG CONSOLE");
           } 
            
        }
      /*read 2 byte source ID and lengh 2 byte */
       if(nread > 0) 
         { 
           SCM_DUMP(0, 4, msg_buff, 15);
         }
            
        /*MSB followed by LSB*/
       if(nread >= 0)
         {
            len = *((U16 *) (msg_buff+2));  
            len = ntohs(len);
          SCM_printf(SCM_INFO,"\nlen to read  : %d \n", len );
          /*now read the whole string */
          ret_val  = SS7_read(fd, (char*)&msg_buff[4], len);
         }
       if((nread <= 0)||(ret_val <= 0))
        {
          SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED NWSTK DBG CONSOLE IS DOWN\n");
          close(xxx_client_sockfd [ENT_NWSTK_DBG]);
          FD_CLR(xxx_client_sockfd [ENT_NWSTK_DBG], &client_fd); 
          g_parameter.config_cmd_resp = 0;
          xxx_client_sockfd [ENT_NWSTK_DBG] = -1;
          return 0;
        }
      return len; 
      break;
    }  
      
      
   case ENT_NWSTK:
    { 
       nread = recv(fd, (char*)msg_buff, sizeof(NwStkHdr), MSG_PEEK);
       if(nread > 0)
       {
        len = (U16) ((NwStkHdr *)msg_buff)->len;
        SCM_printf(SCM_INFO,"\nNWSTK READ %d BYTES\n", len);
        nread = SS7_read(fd, msg_buff, len);
       }  
       if(nread <= 0)
         {
          SCM_printf(SCM_CRITICAL,"NWSTK SOCKET READ FAILED\n");
          SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED NWSTK IS MARKED DOWN\n");
          close(xxx_client_sockfd[ENT_NWSTK]); 
          g_parameter.config_cmd_resp = 0;
          FD_CLR(xxx_client_sockfd [ENT_NWSTK], &client_fd);
          xxx_client_sockfd [ENT_NWSTK] = -1;
          g_parameter.nwstk_cfgComplete = 0;
          send_stack_enity_up_to_peerscm(ENT_NWSTK);
          if(g_parameter.peer_nwstk_up == 0)
           {
             g_parameter.nwstk_cfgIndFromPeerCard = 0; 
           }  
          process_scm_alarm(SS7_DOWN);
           return 0;
         }
       /* LSB FOLLOWED BY MSB*/
       return len;
       break;
     }
   case ENT_LAPD:
        {
         nread = recv(fd, (char*)msg_buff, 20, MSG_PEEK);
         if(nread > 0)
          {
           Lapd_Hdr = (lapd_header_t*)msg_buff;
           if(msg_buff[2] == LAPD_SCM_PEGS_MSG)
           {
            len = (msg_buff[3] | (msg_buff[4] << 8));
           }  
           else
           {  
            len = Lapd_Hdr->len;
           }
           len = len+2;
           SCM_printf(SCM_INFO,"\nLAPD STK READ %d BYTES\n", len);
           nread = SS7_read(fd , (msg_buff), len);
          }
         if(nread <= 0)
           {
             SCM_printf(SCM_CRITICAL,"LAPD SOCKET READ FAILED\n");
             SCM_printf(SCM_CRITICAL,"\nENTITY MARKED DOWN LAPD");
             close(xxx_client_sockfd[ENT_LAPD]);
             g_parameter.config_cmd_resp = 0;
             FD_CLR(xxx_client_sockfd[ENT_LAPD], &client_fd);
             xxx_client_sockfd[ENT_LAPD] = -1;
             return 0;
            }
            return len;
         break;
        } 
       
   case ENT_OAM:
   {
        nread = recv(fd, (char*)msg_buff, 12, MSG_PEEK);
        if(nread > 0)
         {  
          scmhdr = (ScmHdr*)msg_buff;
          /* LSB FOLLOWED BY MSB*/
          len = scmhdr->len;
           
          SCM_printf(SCM_INFO,"-----------------------------------------------------------------------------\n");
          SCM_printf(SCM_INFO,"\nNo. of byte to read from Oam: %d", len);
          ret_val = validate_length_of_messag(scmhdr->opcode, scmhdr->len);
          switch(ret_val)
           {
             case 0:
                   SCM_printf(SCM_MAJOR,"\nLength validation failure "); 
                   nread = SS7_read(fd, msg_buff, len);
                   if(nread != 0)
                     {
                      match_resp_opcode(scmhdr->opcode,  &resp_opcode);
                      send_resp_to_oam(  resp_opcode, scmhdr->operation, scmhdr->trid , ((ScmHdr *)msg_buff)->spare,
                                         ERROR_LENGTH_PARAM, NULL, resp_len, APP_ID_OAM);   
                      return 0;
                     } 
                   nread = 0; 
                   break;
             case 1:
                  SCM_printf (SCM_MAJOR, "Length validation success\n");
                  nread = SS7_read(fd, msg_buff, len);
                  break;
             case 2:
                  nread = SS7_read(fd, msg_buff, len);
                  if(nread != 0)
                    { 
                      send_resp_to_oam(  0, scmhdr->operation, scmhdr->trid , ((ScmHdr *)msg_buff)->spare,
                                         ERROR_WRONG_OPCODE, NULL, resp_len , APP_ID_OAM);
                      return 0;
                    }

                  nread = 0;  
                  break;
           }
         } 
        if(nread <= 0)
         {
          SCM_printf (SCM_CRITICAL, "\nENTITY OAM IS MARKED DOWN\n");
          close(xxx_client_sockfd [ENT_OAM]);
          FD_CLR(xxx_client_sockfd [ENT_OAM], &client_fd);
          g_parameter.config_cmd_resp = 0;
          xxx_client_sockfd [ENT_OAM] = -1;
          g_parameter.entity_up--; 
           return 0;
         }
        return len;
        break;
   }
    case FROM_IMTCS:/*to read on scm server */
       {
         nread = recv(fd, (char*)msg_buff, 8, MSG_PEEK);
         if(nread <= 0)
          {
             SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED TO/FROM SCM IS DOWN\n");
             for(loop=0;loop<=4;loop++)
              { 
               if(xxx_severread_sockfd[loop] == fd)
                {
                  SCM_printf (SCM_CRITICAL, "\nSCM SERVER CLIENT CONNECTED FD IS MARKED DOWN\n");
                  close(xxx_severread_sockfd[loop]);
                  FD_CLR(xxx_severread_sockfd[loop], &server_fds);
                  locate_entity_down();
                  g_parameter.config_cmd_resp = 0;
                  xxx_severread_sockfd[loop] = -1;
                  break;
                }
              } 
              /*AOIP: BSSAP SERVER DISC CHANGES*/
             if (xxx_client_sockfd [ENT_BSSAP] == fd)
              {
               SCM_printf(SCM_CRITICAL,"BSSAP CLIENT SOCKET READ FAILED\n");
               SCM_printf (SCM_CRITICAL, "ENTITY CONNECTED BSSAP IS MARKED DOWN\n");
               close(xxx_client_sockfd[ENT_BSSAP]);
               g_parameter.config_cmd_resp = 0;
               FD_CLR(xxx_client_sockfd [ENT_BSSAP], &client_fd);
               xxx_client_sockfd [ENT_BSSAP] = -1;
               g_parameter.bssap_cfgComplete = 0;
               send_stack_enity_up_to_peerscm(ENT_BSSAP);
               g_parameter.self_stack_up =0;
               process_scm_alarm(SS7_DOWN);
              }
              g_parameter.entity_up--; 
             /*AOIP: END*/
             return 0;
          }
         app_id = msg_buff[0];
         switch (app_id)
          {
           case APP_ID_SIGTRAN:
           case APP_ID_MAP:
           case APP_ID_BS:
           case RESP_APP_ID_ISUP:
           case SCCP_SM_RESPONSE_API:  /*AOIP resp case*/
           case M3UA_SM_RESPONSE_API:  /*AOIP resp case*/
           case SCTP_SM_RESPONSE_API:  /*AOIP resp case*/
                *entity = FROM_MTI;
                len = msg_buff [4];
                len = ((len << 8)|(msg_buff [3]));
                nread = SS7_read(fd , msg_buff, len);
                /*AOIP: PRINTS*/
                if(app_id == APP_ID_BS && nread == 1)
                   {
                      SCM_printf(SCM_INFO,"RESP RECV. BSSAP [%d] bytes\n", len);
                   }
                else if(((app_id == SCCP_SM_RESPONSE_API) || (app_id == M3UA_SM_RESPONSE_API) ||(app_id == SCTP_SM_RESPONSE_API))  && nread == 1)
                   {
                      SCM_printf(SCM_INFO,"RESP RECV. SIGTRAN [%d] bytes\n", len);
                   }
                else
                   {
                      SCM_printf(SCM_INFO,"**UNKNOWN READ %d BYTES**\n", len);
                   }
                 /*AOIP: END*/
                if(nread <= 0)
                 {
                  SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED TO/FROM SCM IS DOWN\n");
                  for(loop=0;loop<=4;loop++)
                   { 
                    if(xxx_severread_sockfd[loop] == fd)
                     {
                      SCM_printf (SCM_CRITICAL, "\nSCM SERVER CLIENT CONNECTED FD IS MARKED DOWN\n");
                      close(xxx_severread_sockfd[loop]);
                      FD_CLR(xxx_severread_sockfd[loop], &server_fds);
                      locate_entity_down();
                      g_parameter.config_cmd_resp = 0;
                      xxx_severread_sockfd[loop] = -1;
                      break;
                    } 
                   }
                  /*AOIP: BSSAP SERVER DISC CHANGES*/
                  if (xxx_client_sockfd [ENT_BSSAP] == fd)
                   {    
                       SCM_printf(SCM_CRITICAL,"BSSAP CLIENT SOCKET READ FAILED\n");
                       SCM_printf (SCM_CRITICAL, "ENTITY CONNECTED BSSAP IS MARKED DOWN\n");
                       close(xxx_client_sockfd[ENT_BSSAP]);
                       g_parameter.config_cmd_resp = 0;
                       FD_CLR(xxx_client_sockfd [ENT_BSSAP], &client_fd);
                       xxx_client_sockfd [ENT_BSSAP] = -1;
                       g_parameter.bssap_cfgComplete = 0;
                       send_stack_enity_up_to_peerscm(ENT_BSSAP);
                       g_parameter.self_stack_up = 0;
                       process_scm_alarm(SS7_DOWN);

                   } 
                  g_parameter.entity_up--; 
                  /*AOIP: END*/
                 return 0;
                }
         app_id = msg_buff[0];
         return len;
         break;
           case 99:
                *entity = ISMAP_TCAP_ALARM;
                 len = msg_buff[4];
                 len = ((len << 8)|(msg_buff [3]));
                 SCM_printf(SCM_INFO,"SIGTRAN ALARM READ %d BYTES\n", len);
		 nread = SS7_read(fd, msg_buff, len);
                if(nread <= 0)
                 {
                  SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED ON SCM SERVER DOWN IS DOWN\n");
                  for(loop=0;loop<=4;loop++)
                   { 
                    if(xxx_severread_sockfd[loop] == fd)
                     {
                      SCM_printf (SCM_INFO, "\nSCM SERVER CLIENT CONNECTED FD IS MARKED DOWN\n");
                      close(xxx_severread_sockfd[loop]);
                      FD_CLR(xxx_severread_sockfd[loop], &server_fds);
                      locate_entity_down();
                      g_parameter.config_cmd_resp = 0;
                      xxx_severread_sockfd[loop] = -1;
                      break;
                    } 
                  } 
                 return 0;
                }
                return len;
                break;


           case APP_ID_PEER_SCM:
           case APP_ID_OAM:
             {
                int scmNodeId = 0;
                *entity = APP_ID_PEER_SCM;
                nread = recv(fd, (char*)msg_buff, sizeof(ScmHdr), MSG_PEEK);
                len = ((ScmHdr*)msg_buff)->len;
                scmNodeId = ((ScmHdr*)msg_buff)->spare; 
                SCM_printf(SCM_INFO,"\nPEER READ %d BYTES rem ent[%d]\n", len, *entity);
                nread = SS7_read(fd , msg_buff, len);
                if((nread <= 0) )
                 {
                  SCM_printf (SCM_CRITICAL, "\nENTITY CONNECTED ON SCM SERVER DOWN IS DOWN\n");
                  for(loop=0;loop<=4;loop++)
                   { 
                    if(xxx_severread_sockfd[loop] == fd)
                     {
                      SCM_printf (SCM_INFO, "\nSCM SERVER CLIENT CONNECTED FD IS MARKED DOWN\n");
                      close(xxx_severread_sockfd[loop]);
                      FD_CLR(xxx_severread_sockfd[loop], &server_fds);
                      locate_entity_down();
                      g_parameter.config_cmd_resp = 0;
                      xxx_severread_sockfd[loop] = -1;
                      break;
                    } 
                   } 
                 return 0;
                }
                if(scmNodeId == g_parameter.slot_id)
                { 
                 SCM_printf (SCM_CRITICAL, "\n Peer nodeId: %d, self nodeId: %d", scmNodeId, g_parameter.slot_id);
                 SCM_printf (SCM_CRITICAL, "\n Wrong PEER SCM IP address in scm_conf!!");
                 SCM_printf (SCM_MAJOR, "\n Close socket with peer for further communictaion!!");
                 close(xxx_client_sockfd [ENT_PEER_SCM]);
                 FD_CLR(xxx_client_sockfd [ENT_PEER_SCM], &client_fd);
                 xxx_client_sockfd [ENT_PEER_SCM] = -2; /* marked closed permamently */
                 return 0;
                } 
                return len;
             }
             break;

          default:     
                SCM_printf(SCM_MAJOR,"\nRECEIVED APP_ID UNKNOWN");
                break;
               
         }
         break;
      } 
       default:     
         SCM_printf(SCM_CRITICAL,"\nDECODING ERROR \n");
         break;
  }
return len;
}

int SS7_read(S32 fd, U8* cmd_buff, U16 len)
{
 S32 nread = 0;
 U16 length;
 U32 count=0,  temp = 0;
 length = len;
 strcpy(g_parameter.function_string, "SS7_read()");
 if(len <= 0)
  { 
   SCM_printf(SCM_CRITICAL,"\nRead from socket is failed : cause no. of byte to read is 0\n");
   return 0;
  }
 
 while(len) 
  {
   nread =  recv(fd, (char*)&cmd_buff[temp], len, MSG_PEEK);;
   if((nread <= 0) || (count == 15))
    {
     SCM_printf(SCM_MAJOR,"SOCKET RECEIVED FAILED\n");
     return 0;
    }
   temp = temp + nread; 
   len = len - nread;
  }
 if(temp != length)
   {
    SCM_printf(SCM_MAJOR,"received byte not equal to length to read\n");
    return 0;
   }
 else
  { 
   temp = 0;
   len = length;
   count = 0;
  }

 while(len) 
  {
   nread = read(fd, (char*)&cmd_buff[temp], len);
   if((nread <= 0) || (count == 15))
    {
     SCM_printf(SCM_MAJOR,"SOCKET READ FAILED\n");
     return 0;
    }
   temp = temp + nread; 
   len = len - nread;
  }
 //SCM_printf(SCM_INFO,"\nNo of byte read from socket: %d ", temp);
 return 1;
}

signed int scm_dispatch_buffer(U8* cmd_buff, U8 appId, U16 len)
{
 U16 ret_val;
 strcpy(g_parameter.function_string, "scm_dispatch_buffer()");
 switch(appId)
  {
   case APP_ID_PEER_SCM:
        if(xxx_client_sockfd[ENT_PEER_SCM] <= 0)
        {
         SCM_printf(SCM_CRITICAL,"\n ENTETY PEER SCM IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ((ScmHdr*)cmd_buff)->spare = g_parameter.slot_id; /* anand:- I have used this field to avoid message
                                                            ping pong in case of peer ip & self ip are same 
                                                            on set up and scm_conf */ 
        ret_val = scm_write(ENT_PEER_SCM, xxx_client_sockfd[ENT_PEER_SCM], cmd_buff, len);  
        break; 
   case APP_ID_SIGTRAN:
   case APP_ID_MAP:
        if(xxx_client_sockfd[ENT_SIGTRAN] <= 0)
        {
         g_parameter.config_flag = 0;
         SCM_printf(SCM_CRITICAL,"\n ENTETY MAP/TCAP IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ret_val = scm_write(ENT_SIGTRAN, xxx_client_sockfd[ENT_SIGTRAN], cmd_buff, len);   
        break;

   case APP_ID_NWSTK:
        if(xxx_client_sockfd[ENT_NWSTK] <= 0)
        {
         g_parameter.config_flag = 0;
         SCM_printf(SCM_CRITICAL,"\n ENTETY NWSTK IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ret_val = scm_write(ENT_NWSTK, xxx_client_sockfd[ENT_NWSTK], cmd_buff, len);   
        break;
   case APP_ID_LAPD:
        if(xxx_client_sockfd[ENT_LAPD] <= 0)
        {
         SCM_printf(SCM_CRITICAL,"\n ENTETY LAPD IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ret_val = scm_write(ENT_LAPD, xxx_client_sockfd[ENT_LAPD], cmd_buff, len);  
        break; 
   case APP_ID_OAM:
        if(xxx_client_sockfd[ENT_OAM] <= 0)
        {
         SCM_printf(SCM_CRITICAL,"\n ENTETY OAM IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ret_val = scm_write(ENT_OAM, xxx_client_sockfd[ENT_OAM], cmd_buff, len);  
        break;
/*AOIP: CASE ADDED*/ 
    case APP_ID_BS:
       if(xxx_client_sockfd[ENT_BSSAP] <= 0)
        {
         SCM_printf(SCM_CRITICAL,"\n ENTETY BSSAP IS DOWN BUFFER SEND FAIL\n");
         return 0;
        }
        ret_val = scm_write(ENT_BSSAP, xxx_client_sockfd[ENT_BSSAP], cmd_buff, len);  
        break;
/*AOIP: END*/
    default:
        SCM_printf(SCM_CRITICAL,"\n DECODING ERROR\n");
      
  }
 if(ret_val == 0)
  {
   SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCKET FAIL ENTITY MARKED DOWN" );
  }
 return ret_val;   
}


signed int scm_write( U8 fd_index, U32 fd, U8* msg_buff, U16 len) 
{
   strcpy(g_parameter.function_string, "scm_write()");
   SCM_printf(SCM_INFO,"BUFFER TO WRITE ON SOCKET\n" );
   SCM_DUMP(0, len, msg_buff, 15);
  return send(fd, (U8*)msg_buff, len, 0);
}


signed int send_sync_mesg()
{
  U8 cmd_buff[10], ret_val;
  strcpy(g_parameter.function_string, "send_sync_mesg()");
  form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_REG_MSG, 0, 5 );
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, 5);
  if(ret_val <= 0)
   {
    SCM_printf (SCM_CRITICAL, "\nNW STK SYNCRONISATION CMD FAILURE");
    return ret_val;
   }
  g_parameter.nwstk_cfgComplete = 0;
  g_parameter.self_nwstk_up = 1;
  send_stack_enity_up_to_peerscm(ENT_NWSTK);
  
return 1;
} 

signed int send_stack_enity_up_to_peerscm(U8 entity)
{
  U8 cmd_buff[20], ret_val, Length;
  peerNwstkSts nwstkSts; 
  strcpy(g_parameter.function_string, "send_stack_enity_up_to_peerscm()");

  switch(entity)
  {
    case  ENT_NWSTK:
           if((xxx_client_sockfd[ENT_NWSTK] <= 0))
             {
              nwstkSts.status = 0;
             }
            else
              nwstkSts.status = 1;
              memcpy(cmd_buff, &nwstkSts, sizeof(peerNwstkSts));
              Length = sizeof(peerNwstkSts); 
           
          form_oam_header( cmd_buff, SCM_NWSTKUP, SCM_MODIFY, 0, 0, sizeof(peerNwstkSts));
          break;
/*AOIP_HA*/
    case  ENT_SIGTRAN:
    case  ENT_BSSAP:
           if(((xxx_client_sockfd[ENT_SIGTRAN] <= 0) || (xxx_client_sockfd[ENT_BSSAP] <= 0))) /*ie if either one is down*/
             {
              nwstkSts.status = 0;
             }
            else
              nwstkSts.status = 1;
              memcpy(cmd_buff, &nwstkSts, sizeof(peerNwstkSts));
              Length = sizeof(peerNwstkSts); 
           
          form_oam_header( cmd_buff, MAPTCAP_STACK_UP, SCM_MODIFY, 0, 0, sizeof(peerNwstkSts));
          break;
/*AOIP_HA END*/
    default:
         SCM_printf (SCM_CRITICAL, "\nWrong entity value");
         return 0;
  }
          
  ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_PEER_SCM, Length);
  if(ret_val <= 0)
   {
    SCM_printf (SCM_CRITICAL, "entity up indication send to peer failure");
    return ret_val;
   }
   else g_parameter.nwstk_stsUp_sent = 1; 
  return 1;

} 



void  locate_entity_down()
{
 struct timeval timeout;
 U16 nbytes;
 S32   event_on_fd, ret;
 U8 i;
 U8 p_buf [100];
 fd_set  stk_fdreadset;
 timeout.tv_sec  = 0;
 //timeout.tv_usec = 200 ;
 timeout.tv_usec = 10000;
 FD_ZERO(&stk_fdreadset);
 stk_fdreadset = client_fd;
 strcpy(g_parameter.function_string, "locate_entity_down()");
 event_on_fd = select ( FD_SETSIZE, &stk_fdreadset, NULL, NULL, &timeout );
 if(event_on_fd == 0)
   {
    return ;
  }
 else
  {   
   for(i = 0; i <= 7; i++)
      {
        if((xxx_client_sockfd[i]>0) && (FD_ISSET (xxx_client_sockfd[i], &stk_fdreadset)>0))
           {
             nbytes = recv ( xxx_client_sockfd[i], (char*) p_buf,
                                    5, MSG_PEEK);
             if ( nbytes <= 0 )
              {
               SCM_printf(SCM_CRITICAL," AN ENTITY "
                         "CONNECTED to SCM is DOWN : %s\n", get_entity(i));
               ret = strcmp("ISUP", get_entity(i));
               if(ret == 0)
                { 
                 process_scm_alarm(ISUP_DOWN);
                }
               close(xxx_client_sockfd[i]);
               g_parameter.config_cmd_resp = 0;
               FD_CLR(xxx_client_sockfd[i],&client_fd);
               FD_CLR(xxx_client_sockfd[i],&stk_fdreadset);
               xxx_client_sockfd[i] = -1;
               return;
              }
           }
      }
 
  }
 return;
} 
