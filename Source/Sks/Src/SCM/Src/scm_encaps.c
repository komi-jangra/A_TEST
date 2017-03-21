/********************* File Header ********************************
   File Name    : scm_encaps.c
   Purpose      : SCM encaps file
   Project      : SCM
   Subsystem    : 
   Author       : Anand  Singh
   CSCI id      :
   Version      : 1.0
 **************************************************************/
/********************* Copyright Notice**************************
 VIHAAN NETWORKS PVT. LTD.
 Copyright 2004 - 2007, All rights reserved.
 This file contains unpublished source code owned by Vihaan Networks Limited.
 No part may be reproduced except as authorized by written permission. The
 copyright and the foregoing restriction extend to reproduction in all media.
 The information contained in this file is the proprietary and exclusive
 property of India Mobility Research Pvt. Ltd.  except as otherwise indicated.
 No part of this file, in whole or in part, may be reproduced, stored,
 transmitted, or used for design/implementation purposes without the prior
 written permission of Vihaan Networks Limited.
 This file can not be used purpose other than stated in the separate software
 license agreement.
 This file may contain information of a sensitive nature. This information
 should not be given/transferred to any third party.
 The information contained in this document is subject to change without notice.
 Vihaan Networks Limited  specifically disclaims all warranties,
 express or limited, including, but not limited, to the implied warranties of
 merchantability and fitness for a particular purpose, except as provided for
 in a separate software license agreement.

 Vihaan Network Pvt. Ltd.
 246, Phase IV, Udyog Vihar
 Gurgaon
 Haryana
 INDIA PIN 122015
 Phone: +91-124-4311600
 Fax  : +91-124-4104766
'$Author: AnandSingh $
'$Id: scm_encaps.c 145 2008-07-16 15:24:29Z anandsingh $
************************************************************************/




#include "scm_localhashdef.h"
#include "scm_encaps.h"
#include <stdlib.h>
#include <string.h>
#include <sysxxx_slotid.h>

/*AOIP BT ADDED*/
#include <execinfo.h>

#ifdef PLATFORM_IMR
#include <bpmxxx_platformLib.h>
#include <stdlib.h>
#endif


char   new_str[1000];
fd_set scm_server_fd;
fd_set client_fd;
fd_set server_fds;
fd_set read_fds;
timer_t os_timer_id[10];
link_information *link_node;
LinkHashTable    *linkHashTbl[9];
LinksetHashTable *linksetHashTbl[9]; 
gvar_link        g_linkConfigValue;

char *str;
int sv,iv;
char   new_str[1000];

S8                  *xxx_scm_ip[10];
U32                 xxx_scm_port[10];
S32                 xxx_client_sockfd[9];
S32                 xxx_severread_sockfd[10];
isup_global_data g_isup_parameter;

transaction_id oam_transaction_Id[256];/*this array is to store oam tr_Id + operation code*/

U8 transaction_Id[256];
multiple_cmd_handle multi_cmd[3];
scm_global_parameter g_parameter;

timer_exp_ele timer_info[10]; 

roll_back_flag       g_roll_back_flag;
sigset_t            mask;

/*AOIP: Flag differentiating Conf and Reconf commands*/
U32 Reconf_Flag = 0;
/*AOIP END*/

/*AOIP BT ADDED*/
void bt_sig_hndlr_reg();

#ifndef  PLATFORM_IMR
int  pthread_create(pthread_t*, pthread_attr_t*, void*, void* );
#endif 

/*AOIP_HA
U16 Check_Peer_psp_and_Bss_state(U16 *, U16 *, U16 *);
#define SLOT_3 3
#define SLOT_4 4
AOIP_HA end*/

#ifdef PLATFORM_IMR

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Function    : bpmAisCallbackFunc                                            *
 * Parameters  : None                                                          *
 * Description :                                                               *
 * Author      : Platform                                                      *
 *                                                                             *
 *                                                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void scmBpmAisCallbackFunc(struct sAisParam* param)
{
        //static int count = 1;

       /*MANTIS ID :- 0032193*/
         U8 msg_buff[13];
         U16 Unlocked = 1, Disabled = 0;
         U16 admin_state, opr_status, Asp_id;
       /*MANTIS End*/
        switch(param->messageId)
        {
             case BPM_HEALTHCHECK_MESSAGE:
             bpmRespondToAis (param->invocation,OK);
             SCM_printf(SCM_DEBUG,"SCM : HEALTH CHECK IS OK ");
             fflush(stdout);

             #ifdef  ANAND
             if(count < 6)
             {
                    bpmRespondToAis (param->invocation,OK);
                    SCM_printf(SCM_DEBUG,"SCM : HEALTH CHECK IS OK ");
                    SCM_printf(SCM_DEBUG,"SCM_Health_Platform = %d",
                                        SCM_Health_Platform);
                    if(SCM_Health_Platform == 0)
                    failed_process = failed_process + 1;
                    printf("\nCOUNT:%d\n",count);
             }
             else
             {
                    count = 0;
                    if(failed_process < 3)
                    {
                         bpmRespondToAis (param->invocation,OK);
                         SCM_printf(SCM_INFO,"SCM : HEALTH CHECK IS OK \n");
                         SCM_printf(SCM_INFO,"LOAD : %d\n", failed_process);
                    }
                    else
                    {
                         bpmRespondToAis (param->invocation,NOT_OK);
                         SCM_printf(SCM_CRITICAL,"SCM : HEALTH CHECK FALSE \n");
                    }
             }
             count = count + 1;
             #endif
             break;

             case BPM_SELFCARD_STATE_CHANGE:
                  SCM_printf(SCM_DEBUG,"SelfCard State Change Callback called");
                  if(param->cardState == CARDSTATE_ACTIVE)
                   {
                     g_parameter.redundant_status = SCM_ACTIVE;
                     g_parameter.g_card_state = SCM_ACTIVE;
                     SCM_printf(SCM_MAJOR,"cState=CARDSTATE_ACTIVE");
                     SCM_printf(SCM_DEBUG,"g_parameter.redundant_status = %d", g_parameter.redundant_status);
                    if(g_parameter.scm_process_flag == 0)
                    {
                     scm_signal();
                    }
                    if((g_parameter.nwstk_cfgComplete == 1) && (g_parameter.lapd_cfgComplete == 1))
                    {
                     process_scm_alarm(SS7_UP);
                    }  
                    
                   /*MANTIS Id:- 0032193*/
                    if(g_parameter.Conn_Down_alarm_Resp_Pending == 1)
                     {
                       SCM_printf(SCM_MAJOR,"M3UA_CONN_DOWN Alarm Resp was PENDING\n");
                       g_parameter.Conn_Down_alarm_Resp_Pending = 0;
                       Check_Self_Admin_and_Opr_state(&admin_state, &opr_status, &Asp_id);
                        if((admin_state == Unlocked) && (opr_status == Disabled))
                         {
                           /*Self generated 9011 alarm send to OAM*/
                           msg_buff[0] = 0x63;
                           msg_buff[1] = 0x01;
                           msg_buff[2] = 0x03;
                           msg_buff[3] = 0x0d;
                           msg_buff[4] = 0x00;
                           msg_buff[5] = 0x05;
                           msg_buff[6] = 0x33;
                           msg_buff[7] = 0x23;
                           msg_buff[8] = 0x05;
                           msg_buff[9] = 0x00;
                           msg_buff[10] = (g_parameter.slot_id -2); /*Sigtran Slot id*/
                           msg_buff[11] = Asp_id    & 0x0f;
                           msg_buff[12] = Asp_id>>8 & 0x0f ;
                           process_sigtran_stack_alarm(13, msg_buff, APP_ID_SIGTRAN);
                         }
                       
                     }
                   /*MANTIS End*/  
                   }
                  else if( param->cardState == CARDSTATE_STANDBY)
                   {
                     g_parameter.redundant_status = SCM_STANDBY;
                     g_parameter.g_card_state = SCM_STANDBY;
                     SCM_printf(SCM_MAJOR,"cState=CARDSTATE_STANDBY");
                    if(g_parameter.scm_process_flag == 0)
                     scm_signal();
                   }
                 /* done for nwstk + scm test case */ 
                   if(param->cardState == CARDSTATE_ACTIVE_IN_PROGRESS)
                   {
                     
                     SCM_printf(SCM_DEBUG,"SelfCard State Change AIP");
                     g_parameter.g_card_state = SCM_AIP;
                   }
                 /*  
                  else
                   {
                    bpmRespondToAis (param->invocation,OK);
                    break;
                   }*/ 
                    bpmRespondToAis (param->invocation,OK);
                    break;

             case BPM_PEERCARD_STATE_CHANGE:
                  SCM_printf(SCM_DEBUG,"PeerCard State Change Callback called");
                  if( (param->cardState == CARDSTATE_ABSENT) || (param->cardState == CARDSTATE_FAIL) || (param->cardState == CARDSTATE_RECOVERY))
                   {
                    g_parameter.g_card_state  = SCM_AIP;
                    SCM_printf(SCM_DEBUG,"PeerCard Absent event");
                    SCM_printf(SCM_DEBUG,"Data_Pull_Done Reset\n");
                    g_parameter.data_pull_up = 0;/*MANTIS:- 0032367*/
                     int loop; 
                     /* close peer communicating Fd here */
#if 0
                    for(loop=0;loop<=4;loop++)
                    { 
                     if(xxx_severread_sockfd[loop] != -1)
                      {
                       SCM_printf (SCM_INFO, "\nSCM SERVER CLIENT CONNECTED FD IS MARKED DOWN\n");
                       close(xxx_severread_sockfd[loop]);
                       FD_CLR(xxx_severread_sockfd[loop], &server_fds);
                       locate_entity_down();
                       xxx_severread_sockfd[loop] = -1;
                       break;
                     } 
                    }
                    if(xxx_client_sockfd [ENT_PEER_SCM] != -1)
                    {  
                     close(xxx_client_sockfd [ENT_PEER_SCM]);
                     FD_CLR(xxx_client_sockfd [ENT_PEER_SCM], &client_fd);
                     xxx_client_sockfd [ENT_PEER_SCM] = -1; 
                    } 
#endif /* Amaresh Commented code due to close sockfd */
                   }  
                  bpmRespondToAis (param->invocation,OK);
                  break;

             case BPM_MSG_ACK_CONFIGURE:
                  SCM_printf(SCM_DEBUG,"Message Acknowledgement received from Executive");
                  break;

             case BPM_SHUTDOWN:
                  SCM_printf(SCM_DEBUG,"SIGUSR1 RECEIVED BY SCM");
                  sleep(3); exit (0);
                  break;

             default:
                        break;
        }
}
#endif

/**********************************************************************************/
/*this is the main thread which takes no argument, it spawns the connection manager 
 and set a loop for various state handlers */
/**********************************************************************************/ 


/*main function*/
int main()
{

 unsigned char  *str1, *str2;
 int ret_val = 0, loop = 0;
 U8 *configPath, *config =NULL;
 char tempread;
 FILE *fp;
 pthread_t scm_cm_thread;
 U16 selfProcessorIdG;
 signal(SIGSEGV, catch_signal); 

 strcpy(g_parameter.function_string, "main()");

 #ifdef LOGGER_IMR
 slfAddr.prcr = 0;
 slfAddr.entity = ENT_SKS_SCM;
 slfAddr.clsId = 0;
 slfAddr.rfu = 0;
 slfAddr.inst = 0;
 g_parameter.slot_id = 3;
 g_parameter.redundant_status =  SCM_ACTIVE;
 if(InitLoggingUtility(slfAddr) == 0)
  {
   SCM_printf(SCM_INFO,"SCM SUCCESFULLY REGISTERED with LOGGER Utility");
  }
 else
  {
   SCM_printf(SCM_INFO,"SCM could't be  REGISTERED with LOGGER Utility");
  }
 #endif
 #ifdef PLATFORM_IMR
 /*  Application will  register with application  */
 bpmGetComponentRegister(scmBpmAisCallbackFunc,(unsigned short)APPID_SCM);
//sleep (10);/* cfg initialization failed due to 10 second sleep */
 /* TEMP : For OAM TEAM */
 g_parameter.slot_id = bpmGetSelfSlotId();
 SCM_printf(SCM_MAJOR," bpm get slot id ret: g_parameter.slot_id %d", g_parameter.slot_id);

 scmSigInit();
 bpmComponentConfigure();
 #endif

 /*AOIP BT ADDED*/
 bt_sig_hndlr_reg();

 SCM_printf(SCM_INFO,"\n");
 SCM_printf(SCM_INFO,"\t\t|||||||||||||||||||||||||||||||||||||||||||||||\n");
 SCM_printf(SCM_INFO,"\t\t|            Vihaan Networks Limited          |\n");
 SCM_printf(SCM_INFO,"\t\t||||||||||||||  S C M Process   |||||||||||||||\n");
 SCM_printf(SCM_INFO,"\t\t|||||||||||||||||||||||||||||||||||||||||||||||\n");

 configPath = malloc(100);
 config = getenv("CONFIG");
 if(config != NULL)
 {
   strcpy(configPath, config);
   strcat(configPath, "clib.cfg");
   SCM_printf(SCM_INFO,"clib init config file path: %s", configPath);
    while((ret_val = clib_init((char *)configPath)) != 0)
    {
           sleep (1);
           SCM_printf(SCM_CRITICAL,"clib_init FAILED : CCM ERR = %d\n", ret_val);
    }
 }
 else
 {
  SCM_printf (SCM_CRITICAL,"\tSCM EXIT: clib config path not set");
  return 0;
 }
 free(configPath);
 configPath=NULL;

 ret_val = scm_init();
 if(ret_val == 0)
  {
   SCM_printf(SCM_CRITICAL,"SCM INITIALIZATION FAILED");
   assert(0); 
  }
 else
 ret_val = 0;
g_parameter.opc_value = 1;
 

#ifndef PLATFORM_IMR
#ifdef TARGET_SETUP
 system("echo `myslot`>slotid");
 if((fp = fopen("./slotid", "r")) == NULL)
 {
  SCM_printf(SCM_MAJOR," myslotid call fail");
 }
 tempread = fgetc(fp);
 if(tempread == '3')
 {
  g_parameter.slot_id = 3;
  SCM_printf(SCM_MAJOR," g_parameter.slot_id %d", g_parameter.slot_id);
 }
 else if(tempread == '4')
 {
  g_parameter.slot_id = 4;
  SCM_printf(SCM_MAJOR," g_parameter.slot_id %d", g_parameter.slot_id);
 }
 fclose(fp);
 system("rm -rf slotid");
#else
 str2 = getenv("config_PRIMARY");

  if(str2!= NULL)
   {
    ret_val = strcmp(str2, "YES");
    if(ret_val == 0)
     {
      g_parameter.slot_id = 3;
      g_parameter.redundant_status =  SCM_ACTIVE;
     }
    else
    {
      g_parameter.slot_id = 4;
      g_parameter.redundant_status =  SCM_STANDBY;
    }
   }
  else
   {
     SCM_printf(SCM_CRITICAL,"SLOT ID ENV VARRIABLE IS NULL");
   }
#endif
#endif



 if((str1 = getenv("SELFPROCESSOR")) == (I_U8  *)0)
  {
   printf("SELFPROCESSOR` not set \n");
   return -1;
  }
 else
  {
   selfProcessorIdG = atoi(str1);
   if(selfProcessorIdG < 1 || selfProcessorIdG >10)
    return -2;
  }
  
  sigemptyset(&mask);

 /* CREATE QUEUES*/
  CREATE_QUEUE(g_parameter.soc_event_q_Id, ((selfProcessorIdG << 16) | 0x109));
  CREATE_QUEUE(g_parameter.timer_event_q_Id, ((selfProcessorIdG << 16) | 0x112));
 /*create a semaphore for bpm callback func to change value of scm state*/

 #ifdef PLATFORM_IMR
  key_t key;
  int nsem = 1, semflg;
  semvalue.val = 0;
  key = ((selfProcessorIdG << 16) | 0x108);
  semflg = IPC_CREAT|0777;
  g_parameter.semID = semget(key, nsem, semflg);
  if(g_parameter.semID == -1)
    {
     SCM_printf(SCM_CRITICAL,"PROBLEM IN CREATING SEMAPHORE");
     EXIT_SCM;
    } 
  else if((semctl(g_parameter.semID, 0, SETVAL, semvalue)) == -1) 
     {
          SCM_printf(SCM_CRITICAL,"PROBLEM IN CREATING SEMAPHORE");
          EXIT_SCM;
     } 
 SCM_printf(SCM_INFO,"SEMAPHORE CREATED: semId %d\n", g_parameter.semID);
#endif

    
  if ( pthread_create ( &scm_cm_thread, NULL, scm_cm_function, NULL) != 0 )
   {
    SCM_printf(SCM_CRITICAL,"PROBLEM IN CREATING SCM CONNECTION MANAGER THREAD");
    EXIT_SCM;
   }
 //scm_cm_function(NULL);
  /* initializing transaction id's*/
  for(loop = 0; loop < 256; loop++)
     {
      transaction_Id[loop] = loop;
     } 
 #ifdef PLATFORM_IMR
  scm_wait();
 #endif  
  
 init_global_config_parm();

  /*main processing start here */
  while(1)
   {
    g_parameter.scm_process_flag = 1;
    handle1:
    process_timer_exp_queue();
 
    handle2:
    ret_val = process_config_cmd_and_resp();       /*This is the main Processing function*/
    /*check for which handle execution proceeds */
    switch(ret_val)
     {
      case HANDLE1:
           goto handle1;
           break;
      case HANDLE2:
           goto handle2;
           break;
      case HANDLE3:
           goto handle3;
           break;
      }
  
    handle3:
    process_message_queue();
    /*check for which handle exection proceed */
   }
  /*execution should never comes here*/
 return 1;
}


/***************************************************************************/
/*This function catch the signal generated due to segmentation fault in scm
  processing and print the corresponding funtion in which signal generated
  and exit from the main */
/***************************************************************************/

void catch_signal(int sig_num)
{
 SCM_printf(SCM_CRITICAL,"SEGMENTATION FAULT SIGNAL RECEIVED");
 SCM_printf(SCM_CRITICAL,":IN FUNCTION : '%s'", g_parameter.function_string);
 assert(0); 
 fflush(stdout);
}

/***************************************************************************/
/*This function processes the peer scm message recieved from peer 
  card i.e. either cmd response or config cmd update from peer card scm*/
/***************************************************************************/


void process_peerscm_message(U8* msg_buff)
{
 U8 ret;
 U16 resp_opcode, resp_len, opcode, length = 0;
 strcpy(g_parameter.function_string, "process_peerscm_message()");
 resp_len = sizeof(ScmOamResponse);
 
 switch(((ScmHdr*)msg_buff)->appid)
  {
    case APP_ID_PEER_SCM:
         switch(((ScmHdr*)msg_buff)->opcode)
          {
           case NWSTK_CONFIG_COMPLETE:
                 SCM_printf(SCM_INFO,"\nNwstk  configured:  AT  PEER  SCM");
                 g_parameter.peer_nwstk_up = 1;
                 g_parameter.nwstk_cfgIndFromPeerCard  =  1;
#ifdef NWSTK_REDUNDANCY
                 if((g_parameter.nwstk_cfgComplete  ==  0) )
                  {
                     if((g_parameter.nwstk_cfg_wait == 0) && (g_parameter.ss7_up_alarm == 1))
                     { 
                      if((write_in_sock_event_q(NWSTK_CONFIG_COMPLETE) == 0))
                       {
                         SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL");
                        }
                      else
                       {
                        SCM_printf(SCM_INFO,"\nMessage sent to sock event queue");
                       }
                     } 
 
                  }
                 else
                 {
                   SCM_printf(SCM_INFO,"\ng_parameter.link_activated_flag : %d  ", g_parameter.link_activated_flag);
                   if(g_parameter.link_activated_flag == 1)
                    {
                     getAll_linkAdminstate_and_modify_in_peer_nwstack();
                    }
                
                   SCM_printf(SCM_INFO,"\ng_parameter.linkset_activated_flag : %d  ", g_parameter.linkset_activated_flag);
                   /* here we update no of linkset configured  in peer linkset hash table
                      also send linkset activation command if any of configured linkset is activated*/
                   getAll_linksetAdminstate_and_modify_in_peer_nwstack();
                
                 }  
#else 
                   SCM_printf(SCM_INFO,"\ng_parameter.link_activated_flag : %d  ", g_parameter.link_activated_flag);
                   if((g_parameter.link_activated_flag == 1) && (g_parameter.redundant_status == SCM_ACTIVE))
                    {
                     getAll_linkAdminstate_and_modify_in_peer_nwstack();
                    }
                
                   SCM_printf(SCM_INFO,"\ng_parameter.linkset_activated_flag : %d  ", g_parameter.linkset_activated_flag);
                   /* here we update no of linkset configured  in peer linkset hash table
                      also send linkset activation command if any of configured linkset is activated*/
                   //getAll_linksetAdminstate_and_modify_in_peer_nwstack();
#endif
                break;
          
          case SCM_NWSTKUP:
               if(g_parameter.redundant_status != SCM_ACTIVE)
               { 
#ifdef NWSTK_REDUNDANCY
                SCM_printf(SCM_INFO,"\nsleep ");
                nano_sleep.tv_sec = 0;
                nano_sleep.tv_nsec = 1000
                pselect(0,NULL,NULL,NULL,&nano_sleep,NULL);
#else
                 if((((peerNwstkSts*)msg_buff)->status == 1)&&(g_parameter.nwstk_cfgComplete != 1)&&
                   (g_parameter.nwstk_stsUp_sent == 1))
                 {
                   SCM_printf(SCM_INFO,"peer card nwstk up ");
                   g_parameter.peer_nwstk_up = 1;
                   break;
                 }
#endif 
            
               }  
               if(((peerNwstkSts*)msg_buff)->status == 1)
                {
                   g_parameter.peer_nwstk_up = 1;
                  if((g_parameter.nwstk_cfgComplete == 1))
                   {
                    SCM_printf(SCM_INFO,"sending self card nwstack init status configured to peer ");
                    g_parameter.nwstk_stsUp_sent = 1;
                    send_cofigComplete_ind_to_peerScm(ENT_NWSTK);             
                   }
                  else
                    if(g_parameter.self_nwstk_up == 1)
                     {  
                      SCM_printf(SCM_INFO,"sending self card nwstack init status to peer ");
                      g_parameter.nwstk_stsUp_sent = 1;
                      send_stack_enity_up_to_peerscm(ENT_NWSTK);    
                     }
                  
                  break; 
                }
               else if((((peerNwstkSts*)msg_buff)->status == 0 ) ) 
                     {
                      SCM_printf(SCM_CRITICAL," ENTITY DOWN NWSTK AT PEER SCM");
                      g_parameter.nwstk_cfgIndFromPeerCard = 0;
                     }
                 else
                   SCM_printf(SCM_CRITICAL," Unknown message from peer");
                break;


           case SCM_NWSTK_LINK_ADMIN_STATE_MODIFY:
                process_link_adminStateModiy_cmd_from_peerScm(msg_buff);
                break;
           case SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY:
                process_linkset_adminStateModiy_cmd_from_peerScm(msg_buff);
                break;
           case OAM_SCM_SS7_STACK_CONFIG:
                {
                 OamScmSs7StackConfig                  *initconfig;
                 initconfig = (OamScmSs7StackConfig*)msg_buff;
                 if(initconfig->family == SYS_FAMILY_ANSI)
                 {
                  g_parameter.family = ANSI_FAMILY;
                 }
                 else
                 {
                   g_parameter.family = ITU_FAMILY;
                 }
                 g_parameter.opc_value        = initconfig->selfPointCode;
                 g_parameter.alarm_level      = initconfig->alarmLevel;
                 match_resp_opcode(((ScmHdr*)msg_buff)->opcode,  &resp_opcode);
                 send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                 ((ScmHdr *)msg_buff)->spare,
                                 NO_ERROR, NULL, resp_len, APP_ID_OAM );
                }	
                return;
          
            /*AOIP_HA*/
            case MAPTCAP_STACK_UP:
                if(g_parameter.redundant_status != SCM_ACTIVE)
               { 
                 if((((peerNwstkSts*)msg_buff)->status == 1)&&((g_parameter.sigtran_cfgComplete == 0) || (g_parameter.bssap_cfgComplete == 0))&&
                   (g_parameter.nwstk_stsUp_sent == 1))
                 {
                   SCM_printf(SCM_INFO,"[JOIN] PEER STACKUP--STDBY CONF INPROGRESS--STACKUP ALRDY SENT\n");
                   g_parameter.peer_nwstk_up = 1;
                   break;
                 }
            
               }  
               if(((peerNwstkSts*)msg_buff)->status == 1)
                {
                   g_parameter.peer_nwstk_up = 1;
                  if((g_parameter.sigtran_cfgComplete == 1) && (g_parameter.bssap_cfgComplete == 1))
                   {
                    SCM_printf(SCM_INFO,"[JOIN] PEER STACKUP--SELF CONF COMPLETE--SEND CONFIG COMPLETE\n");
                    g_parameter.nwstk_stsUp_sent = 1;
                    send_cofigComplete_ind_to_peerScm(ENT_SIGTRAN);             
                   }
                  else
                    if(g_parameter.self_stack_up == 1) /*MANTIS ID:- 0032492*/
                     {  
                      SCM_printf(SCM_INFO,"[JOIN] PEER STACKUP--SELF CONF INPROGRESS--SEND STACK UP\n");
                     // g_parameter.nwstk_stsUp_sent = 1;
                      send_stack_enity_up_to_peerscm(ENT_SIGTRAN);    
                     }
                  else
                      SCM_printf(SCM_INFO,"[JOIN] PEER STACKUP--SELF STACK NOT UP (no ent conn.)\n");
                  break; 
                }
               else if((((peerNwstkSts*)msg_buff)->status == 0 ) ) 
                     {
                      SCM_printf(SCM_CRITICAL,"[JOIN] AN ENTITY CONNECTED TO PEER SCM IS DOWN \n");
                      g_parameter.nwstk_cfgIndFromPeerCard = 0;
                     }
                 else
                   SCM_printf(SCM_CRITICAL," Unknown message from peer");
            break;

            case MAPTCAP_CONFIG_COMPLETE:
                 if(g_parameter.redundant_status == SCM_ACTIVE)
                  {
                    SCM_printf(SCM_INFO,"[JOIN] ACTIVE RECV--STANDBY STACK CONFIG COMPLETE IND ..\n");
                    g_parameter.peer_nwstk_up = 1;
                    g_parameter.nwstk_cfgIndFromPeerCard  =  1; 
                  }
                 else 
                   if( g_parameter.redundant_status == SCM_STANDBY)
                    {
                        SCM_printf(SCM_INFO,"[JOIN] STANDBY RECV--ACTIVE STACK CONFIG COMPLETE IND ..\n");
                        g_parameter.peer_nwstk_up = 1;
                        g_parameter.nwstk_cfgIndFromPeerCard  =  1; 
                    }
                  else
                           SCM_printf(SCM_INFO,"UNKNOWN STATE@#*@#*@#*\n");
                 break;

             case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG:  /*can cmnt this block too will trigger from below*/
                  
                  SCM_printf (SCM_CRITICAL, "STANDBY RECVD LASP_ADMINSTATE_MODIFY FROM PEER...\n");
                  if( g_parameter.noOam_resp_flag == 0) 
                   {   
                      process_oam_message(msg_buff);   //ADMINSTATE CMD TRIGGER TO STDBY STACK
                   }
                   else                                
                   {
                      length = sizeof(OamScmM3uaLocalAspAdminConfig);
                      SCM_printf (SCM_CRITICAL, "STORE MSG AS CMD ALRDY SENT TO SIGTRAN.....\n");
                      g_parameter.map_tcap_msg = scm_malloc(length);
                      memcpy (g_parameter.map_tcap_msg, msg_buff, length);
                   }
                 break;
           /*AOIP END*/
          default: 
               SCM_printf(SCM_INFO,"config  cmd:  RECEIVED  FROM  PEER  SCM");
               /* peer wont respond for linkset table insersion*/
#ifdef NWSTK_REDUNDANCY 
               if(((ScmHdr*)msg_buff)->opcode == OAM_SCM_LINKSET_CONFIG)
                {
                 ret = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 
                                                ((OamScmLinkSetConfig*)msg_buff)->linkSetId, 0);
               SCM_printf(SCM_INFO,"linkset successfully updated in linksethash table");
               match_resp_opcode(((ScmHdr*)msg_buff)->opcode,  &resp_opcode);
               send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid ,
                                ((ScmHdr *)msg_buff)->spare,
                               NO_ERROR, NULL, resp_len, APP_ID_OAM );
                   
                  
                 return;
                }  
#endif
                if(g_parameter.config_flag == SS7_TRUE)
                {
                 SCM_printf(SCM_MAJOR,"PEER SCM MSG DISCARDED BY SCM: 'STACK GETTING CONFIGURED'");
                 opcode = ((ScmHdr *)msg_buff)->opcode;
                 match_resp_opcode(opcode,  &resp_opcode);
                 send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid , 
                                   ((ScmHdr *)msg_buff)->spare, ERROR_PREVIOUS_CMD_IN_PROGRESS, 
                                   NULL, resp_len , APP_ID_OAM);
                }
               else
               { 
                set_stackFlag_to_respond_peer_scm(((ScmHdr*)msg_buff)->opcode);
                ret  =  process_oam_message(  msg_buff);
                 
                 /* reset the flags */ 
                  g_parameter.nwstk_standby_respFlag  =  0;
                  g_parameter.multicmd_standby_respFlag  =  0;      
                  g_parameter.lapd_standby_respFlag  =  0;     
                 /* end here */   
               }
         }  
                    break;  
    case APP_ID_OAM: /* here response from peer scm sent command */
         process_response_from_peer_scm(msg_buff);
         break;  
  }
 
  
 return ;
}

/***************************************************************************/
/*This function processes the link admin state modify command received from peer, checks if card state is self then send the command to self card nwstk else update in scm DB for redundancy use*/
/***************************************************************************/


void  process_link_adminStateModiy_cmd_from_peerScm(U8* msg_buff)
{
  U16 Length;
  signed int ret_val;
  U8  cmd_buff[50], cardFlag;
  OamScmLinkAdminState *scmLinkAdminState;
  ScmNwstkLinkAdminStateModify NwstkLinkAdminStateModify;
  scmLinkAdminState = (OamScmLinkAdminState*)msg_buff;
  strcpy(g_parameter.function_string, "process_link_adminStateModiy_cmd_from_peerScm()");
  ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_GET,  0,
                                                 scmLinkAdminState->linkId,
                                                 scmLinkAdminState->linkSetId,
                                                 &cardFlag, 0);
  g_parameter.link_activated_flag = 1; 
  if(cardFlag == SELF )
           { 
             g_parameter.noOam_resp_flag = 1; 
#define FILL_TMR_VAL(A,C) \
        NwstkLinkAdminStateModify.scmNwstkMtp2TimerModify.A = scmLinkAdminState->mtp2TimerConfig.C; 

       FILL_TMR_VAL(mtp2TimerT1,mtp2TimerT1);
       FILL_TMR_VAL(mtp2TimerT2,mtp2TimerT2);
       FILL_TMR_VAL(mtp2TimerT3,mtp2TimerT3);
       FILL_TMR_VAL(mtp2TimerT4,mtp2TimerT4);
       FILL_TMR_VAL(mtp2TimerT5,mtp2TimerT5);
       FILL_TMR_VAL(mtp2TimerT6,mtp2TimerT6);
       FILL_TMR_VAL(mtp2TimerT7,mtp2TimerT7);

       FILL_TMR_VAL(mtp2EmrgncyProvngPriod,mtp2EmrgncyProvngPriod);
       FILL_TMR_VAL(mtp2NormalProvngPriod,mtp2NormalProvngPriod);
       FILL_TMR_VAL(mtp2PCRFlag,mtp2PCRFlag);
       FILL_TMR_VAL(mtp2RcvOnset,mtp2RcvOnset);
       FILL_TMR_VAL(mtp2RcvAbates,mtp2RcvAbates);
       FILL_TMR_VAL(mtp2TxOnset1,mtp2TxOnset1);
       FILL_TMR_VAL(mtp2TxOnset2,mtp2TxOnset2);
       FILL_TMR_VAL(mtp2TxOnset3,mtp2TxOnset3);
       FILL_TMR_VAL(mtp2TxAbetes1,mtp2TxAbetes1);
       FILL_TMR_VAL(mtp2TxAbetes2,mtp2TxAbetes2);
       FILL_TMR_VAL(mtp2TxAbetes3,mtp2TxAbetes3);
       

#define PRINTTMR(A,C) \
       SCM_printf(SCM_MAJOR,A,NwstkLinkAdminStateModify.scmNwstkMtp2TimerModify.C);
       PRINTTMR("mtp2TimerT1: %d", mtp2TimerT1);
       PRINTTMR("mtp2TimerT2: %d", mtp2TimerT2);
       PRINTTMR("mtp2TimerT3: %d", mtp2TimerT3);
       PRINTTMR("mtp2TimerT4: %d", mtp2TimerT4);
       PRINTTMR("mtp2TimerT5: %d", mtp2TimerT5);
       PRINTTMR("mtp2TimerT6: %d", mtp2TimerT6);
       PRINTTMR("mtp2TimerT7: %d", mtp2TimerT7);

       PRINTTMR("mtp2EmrgncyProvngPriod: %d", mtp2EmrgncyProvngPriod);
       PRINTTMR("mtp2NormalProvngPriod: %d", mtp2NormalProvngPriod);
       PRINTTMR("mtp2PCRFlag: %d", mtp2PCRFlag);
       PRINTTMR("mtp2RcvOnset: %d", mtp2RcvOnset);
       PRINTTMR("mtp2RcvAbates: %d", mtp2RcvAbates);
       PRINTTMR("mtp2TxOnset1: %d", mtp2TxOnset1);
       PRINTTMR("mtp2TxOnset2: %d", mtp2TxOnset2);
       PRINTTMR("mtp2TxOnset3: %d", mtp2TxOnset3);
       PRINTTMR("mtp2TxAbetes1: %d", mtp2TxAbetes1);
       PRINTTMR("mtp2TxAbetes2: %d", mtp2TxAbetes2);
       PRINTTMR("mtp2TxAbetes3: %d", mtp2TxAbetes3);
   #undef PRINTTMR
#undef FILL_TMR_VAL





             NwstkLinkAdminStateModify.linkId = scmLinkAdminState->linkId;
             NwstkLinkAdminStateModify.linkSetId = scmLinkAdminState->linkSetId;
             NwstkLinkAdminStateModify.adminState = scmLinkAdminState->adminState;
             SCM_printf(SCM_INFO,"linkId: %d, linkSetId: %d, adminState: %d,",
                  scmLinkAdminState->linkId, scmLinkAdminState->linkSetId,
                  scmLinkAdminState->adminState);
             Length  =  sizeof(ScmNwstkLinkAdminStateModify);
             memcpy(cmd_buff, &NwstkLinkAdminStateModify, Length);
             form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_ADMIN_STATE_MODIFY,
                               transaction_Id[SCM_NWSTK_LINK_ADMIN_STATE_MODIFY], Length);
             ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
            g_linkConfigValue.link_value  = scmLinkAdminState->linkId;
            g_linkConfigValue.linkSetId   = scmLinkAdminState->linkSetId; 
            g_linkConfigValue.card_flag   = cardFlag;
            g_linkConfigValue.admin_state = scmLinkAdminState->adminState;
           } 
           memcpy(&g_linkConfigValue.scmLinkAdminState, scmLinkAdminState, sizeof(OamScmLinkAdminState));

 ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_MODIFY,  0,
                                                     scmLinkAdminState->linkId,
                                                     scmLinkAdminState->linkSetId,
                                                     &cardFlag, scmLinkAdminState->adminState); 
 

}
 
void  process_linkset_adminStateModiy_cmd_from_peerScm(U8* msg_buff)
{
  U16 Length;
  S32 ret_val;
  U8  cmd_buff[50];
  OamScmLinkSetAdminState *scmLinkSetAdminState;
  ScmNwstkLinkSetAdminStateModify NwstkLinkSetAdminStateModify;
  scmLinkSetAdminState = (OamScmLinkSetAdminState*)msg_buff;
  ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD,  scmLinkSetAdminState->linkSetId, 0);
  g_parameter.linksetId         = scmLinkSetAdminState->linkSetId;
  g_parameter.linkset_admingSts = scmLinkSetAdminState->adminState;
  strcpy(g_parameter.function_string, "process_linkset_adminStateModiy_cmd_from_peerScm()");
 
     
    if(scmLinkSetAdminState->adminState == 1)
        {
            g_parameter.noOam_resp_flag = 1; 
            NwstkLinkSetAdminStateModify.linkSetId = scmLinkSetAdminState->linkSetId;
            NwstkLinkSetAdminStateModify.adminState = scmLinkSetAdminState->adminState;
            SCM_printf(SCM_INFO,"linkSetId: %d, adminState: %d,",
                  scmLinkSetAdminState->linkSetId,
                  scmLinkSetAdminState->adminState);
            Length  =  sizeof(ScmNwstkLinkSetAdminStateModify);
            memcpy(cmd_buff, &NwstkLinkSetAdminStateModify, Length);
            form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY,
                              transaction_Id[SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY], Length);
            ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
           if(ret_val <= 0)
            {
              SCM_printf(SCM_CRITICAL,"CMD MAJOR: for linkset admin state modify");
            }
        }
 

}
/***************************************************************************/
/*This function processes config cmd update response received from 
  peer card for config update*/
/***************************************************************************/
void process_response_from_peer_scm(U8*msg_buff)
{
 U8 app_id;
 U16 resp_opcode;
 S16 error_code, ret_val = 0;
 /*AOIP ALARM (from peer)*/
 U16 alarm_id= 0, state = 0, no_of_asp = 0, length = 0;
 U16 asp_id[2], asp_state[2], lv = 0, tr_opcode = 0;
 U8 *cmd_buff;
 /*AOIP End*/
 strcpy(g_parameter.function_string, "process_response_from_peer_scm()");

 error_code = ((ScmOamResponse*)msg_buff)->erro_code;
 resp_opcode = ((ScmOamResponse*)msg_buff)->scmhdr.opcode;
 if(resp_opcode == SCM_OAM_ALARM_IND)
 {
  /*AOIP ALARM*/
   alarm_id = ((OamScmAlarmsReport *)msg_buff)->alarmdata.alarmId;
   switch(alarm_id)
     {
 /*      DATA PULL DONE NOT TO BE PROCESSED AT SCM NOW  
        
          case SIGTRAN_DATA_PULL_DONE: //This is case of DATA PULL UP IND from standby to active
          length = sizeof(OamScmM3uaLocalAspAdminConfig);
          OamScmM3uaLocalAspAdminConfig ScmM3uaLAspAdminCfg; 
                 
          SCM_printf(SCM_INFO,"[ALARM - %d] Active Recv Stdby Data PullUp Done Ind....\n", alarm_id);
          g_parameter.data_pull_up =1;
          state = Check_Peer_psp_and_Bss_state(&no_of_asp, asp_id, asp_state); //DECISION MAKING FUNC
          if((state == 1) && (no_of_asp == 1 || no_of_asp == 2))
           {
              SCM_printf(SCM_INFO,"Stanby Asp was UP...\n");
              for(lv=0; lv < no_of_asp; lv++)
                {
                   SCM_printf(SCM_INFO,"SCM -> PEER_SCM || ASP_ADMINCONFIG Asp_id[%d] Adminstate[%d]\n", asp_id[lv], asp_state[lv]);
                   ScmM3uaLAspAdminCfg.localAspId = asp_id[lv];
                   ScmM3uaLAspAdminCfg.adminState = asp_state[lv];  //should be 1
                   
                   cmd_buff = (unsigned char*)scm_malloc(200*sizeof(unsigned char));
                   memcpy(cmd_buff, &ScmM3uaLAspAdminCfg, length);
               
                   form_oam_header( cmd_buff, OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG, SCM_MODIFY, 0, 0,length);
                   tr_opcode = OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG - BASE_OPCODE_SCM_AOIP;
                   //No timer in self generated Msg
                   ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_PEER_SCM, length);
                      
                   if(cmd_buff != NULL)
                    {
                      free(cmd_buff);
                      cmd_buff = NULL;
                    }
  
                   if(ret_val <= 0)
                    {
                       SCM_printf (SCM_CRITICAL, "SCM STACK CONFIG COMPLETE MESSAGE SEND TO PEER SCM FAILED");
                       return 0;
                    }
                   else
                    {
                       g_parameter.data_pull_admin_send =1;   made 0 when resp recvd from peer 
                    }
                }
           }
         else
           {
                SCM_printf(SCM_INFO,"STANDBY ASP was DOWN... Proceed\n");
           }
     break; */
    
     default: /*Bypass rest of the alarms*/ 
      SCM_printf(SCM_INFO,"[ALARM - %s #%d] from Peer\n", get_alarm_string(alarm_id) ,alarm_id);
      
      if(alarm_id == 9000)
       {
        g_parameter.data_pull_up =1;
       }

      ret_val = scm_dispatch_buffer(msg_buff, APP_ID_OAM, 
                                    ((ScmOamResponse*)msg_buff)->scmhdr.len);
      if(ret_val <= 0)
       {
         SCM_printf (SCM_CRITICAL, "Write to oam socket failure");
       }
      break;
     }
  return; 
 }
 app_id = get_app_id_from_resp_opcode(resp_opcode);
#define SET_OPERATION(A)\
        if(A == SCM_ADD) {   A = SCM_DELETE;} else {if(A == SCM_DELETE) A = SCM_ADD;}
 if((resp_opcode == SCM_OAM_LINK_PEG_RESP) || (resp_opcode == SCM_OAM_MTP2_PEG_RESP))
 { 
  error_code = 0;
  stop_timer(TIMER_NWSTK);
 }         
 if(error_code != 0)
  {
   SCM_printf(SCM_CRITICAL,"\nconfig cmd response : CMD FAILURE AT PEER END: error code: %d ", error_code);
  switch(app_id)
   {
     case MULTI_CMD:
          stop_timer(TIMER_MULTICMD);
          SCM_printf (SCM_CRITICAL, "\nSET ALARM LEVEL COMMAND FAILURE AT PEER SCM");
          break;
     case APP_ID_LAPD:
          if(g_parameter.peer_lapd_cmdFlag == 1)
            {
             if(g_parameter.lapd_msg != NULL)
              {
               g_parameter.peer_lapd_cmdFlag = 0;
               g_roll_back_flag.lapd_roll_back_flag = 1;
               SET_OPERATION(((ScmHdr*)g_parameter.lapd_msg)->operation); 
               process_oam_message(g_parameter.lapd_msg);
               free(g_parameter.lapd_msg) ;
               g_parameter.lapd_msg = NULL; 
              }  
            } 
           break; 
     case APP_ID_SIGTRAN:  
     case APP_ID_MAP:
           if(g_parameter.peer_map_tcap_cmdFlag == 1)
            {  
             SCM_printf(SCM_INFO," SIGTRAN CMD command failure at peer card ");
             if(g_parameter.map_tcap_msg != NULL)
              {  
               g_parameter.peer_map_tcap_cmdFlag = 0;
               stop_timer(TIMER_SIGTRAN); 
               g_roll_back_flag.maptcap_roll_back_flag = 1;
               SET_OPERATION(((ScmHdr*)g_parameter.map_tcap_msg)->operation); 
               /*AOIP_HA*/
               /*Rollback IMPL only for add failures--Reconf SCTP allowed*/
               if( (((ScmHdr*)g_parameter.map_tcap_msg)->operation == SCM_DELETE) &&
                   (((ScmHdr*)g_parameter.map_tcap_msg)->opcode != OAM_SCM_SCTP_GEN_CONFIG))/*no rollback for OAM_SCM_SCTP_GEN_CONFIG*/
                {
                   process_oam_message(g_parameter.map_tcap_msg);
                }
               else
                {
                   g_roll_back_flag.maptcap_roll_back_flag = 0;               /*If not processing then make flag 0*/
                }
               /*AOIP_HA end*/
               free(g_parameter.map_tcap_msg) ;
               g_parameter.map_tcap_msg = NULL; 
              }
            }
           break; 
     case APP_ID_NWSTK: 
          if(g_parameter.peer_nwstk_cmdFlag == 1)
            {
             if(g_parameter.nwstk_msg != NULL)
              {
               g_parameter.peer_nwstk_cmdFlag = 0;
               stop_timer(TIMER_NWSTK);
               if((g_parameter.peer_link_del != 1))
               {  
                g_roll_back_flag.nwstk_roll_back_flag = 1;
                SET_OPERATION(((ScmHdr*)g_parameter.nwstk_msg)->operation); 
                if(((ScmHdr*)g_parameter.nwstk_msg)->opcode == OAM_SCM_LINK_CONFIG)
                {
                 self_link_rollback(g_parameter.nwstk_msg);
                }
                else
                {
                 process_oam_message(g_parameter.nwstk_msg);
                }
                g_parameter.peer_link_del =0;
                g_parameter.peer_nwstk_cmdFlag = 0;
               }
               else
               {
                SET_OPERATION(((ScmHdr*)g_parameter.nwstk_msg)->operation); 
                g_roll_back_flag.nwstk_roll_back_flag = 1;
                if(((ScmHdr*)g_parameter.nwstk_msg)->opcode == OAM_SCM_LINK_CONFIG)
                {
                 self_link_rollback(g_parameter.nwstk_msg);
                }
                else
                {
                 process_oam_message(g_parameter.nwstk_msg);
                }
               }  
               free(g_parameter.nwstk_msg) ;
               g_parameter.nwstk_msg = NULL; 
              } 
            }
           else   
            if(g_parameter.peer_multi_cmdFlag == 1)
            {
             if(g_parameter.multicmd_msg != NULL)
              {
               g_parameter.peer_multi_cmdFlag = 0;
               stop_timer(TIMER_MULTICMD);
               g_roll_back_flag.multi_cmd_roll_back_flag = 1;
               SET_OPERATION(((ScmHdr*)g_parameter.multicmd_msg)->operation); 
               process_roll_back(g_parameter.multicmd_msg);
               free(g_parameter.multicmd_msg) ;
               g_parameter.multicmd_msg = NULL; 
              } 
            }
           else   
           break; 
           break; 
      default:
          SCM_printf(SCM_CRITICAL,"wrong resp opcode from peer no parsing present");
          free_peer_update_pointer();          
          return;
    
   }  
  }
 else
  {
   SCM_printf(SCM_CRITICAL,"config cmd response : CMD RESP SUCCESSFUL AT PEER END");
   switch(app_id)
   {
     case APP_ID_SIGTRAN:
     case APP_ID_MAP:
          if(g_parameter.peer_map_tcap_cmdFlag == 1)
            {
             if(g_parameter.map_tcap_msg != NULL)
              {
               g_parameter.peer_map_tcap_cmdFlag = 0;
               stop_timer(TIMER_SIGTRAN);   
               free(g_parameter.map_tcap_msg) ;
               g_parameter.map_tcap_msg = NULL;
              }
            }
         break;

    case APP_ID_NWSTK:
          if((g_parameter.peer_link_del == 1) && (g_parameter.nwstk_msg != NULL))
          {
					 U8 cmd_buff[30], timeslot;
           U16 Length;
           OamScmLinkConfig  *scmLinkConfig;
           ScmNwstkLinkConfig    NwstkLinkConfig; 
           scmLinkConfig  = (OamScmLinkConfig*)g_parameter.nwstk_msg;
           Length            = sizeof(ScmNwstkLinkConfig);
           NwstkLinkConfig.instanceID = 20002;
           NwstkLinkConfig.linkId     = scmLinkConfig->linkId;
           NwstkLinkConfig.linkSetId  = scmLinkConfig->linkSetId;
           SCM_printf(SCM_INFO,"DB QUERY FOR STREAM TIME SLOT for TrkNum=%d,TrkTs=%d", 
                               scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
           GetDstStreamTsConfigDataWithTrunkAndTimeslot( &timeslot, 
                               scmLinkConfig->trunkNum , scmLinkConfig->timeSlot);
           NwstkLinkConfig.timeSlot   = timeslot;
           NwstkLinkConfig.cardNum    = scmLinkConfig->cardNum;
           NwstkLinkConfig.crcFlag    = scmLinkConfig->crcFlag;
           memcpy(cmd_buff, &NwstkLinkConfig, Length);
           SCM_printf(SCM_MAJOR,"SCM -> MTP3 'LINK_DEL:' ln: %d, ls: %d, strmTs: %d, instance: %d",
                         scmLinkConfig->linkId, scmLinkConfig->linkSetId, timeslot,NwstkLinkConfig.instanceID);
            form_nwstk_header(cmd_buff, APP_ID_NWSTK, SCM_NWSTK_LINK_DEL,
                                transaction_Id[SCM_NWSTK_LINK_ADD], Length);
            ret_val = scm_dispatch_buffer(cmd_buff, APP_ID_NWSTK, Length);
            return ;
          }
          else
          { 
           if(g_parameter.peer_nwstk_cmdFlag == 1)
            {
             if(g_parameter.nwstk_msg != NULL)
              {
               g_parameter.peer_nwstk_cmdFlag = 0;
               /* do not stop timer & nullify msg stored if link del in progress */ 
                stop_timer(TIMER_NWSTK);
                free(g_parameter.nwstk_msg) ;
                g_parameter.nwstk_msg = NULL;
              }
             else
             {
              SCM_printf(SCM_MAJOR,"Error : nwstk sync message null");
             } 
            }
           else
           if(g_parameter.peer_multi_cmdFlag == 1)
            {
             if(g_parameter.multicmd_msg != NULL)
              {
               g_parameter.peer_multi_cmdFlag = 0;
               /* do not stop timer & nullify msg stored if link del in progress */ 
                stop_timer(TIMER_MULTICMD);
                free(g_parameter.multicmd_msg);
                g_parameter.multicmd_msg = NULL;
              }
             else
             {
              SCM_printf(SCM_MAJOR,"Error : nwstk sync message null");
             } 
            }
          }
           break;
    default:
          SCM_printf(SCM_CRITICAL,"wrong resp opcode from peer no parsing present");
          free_peer_update_pointer();          
          return;

   }
  }

/*AOIP_HA*/
if((resp_opcode == SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP)) 
{
 if(g_parameter.data_pull_admin_send == 1)/*no timer was running for slf generated adminstate(diff flg req)*/
  {
     SCM_printf (SCM_CRITICAL, "Dropping Lasp Admin State resp from peer\n"); /*AOIP-HA print*/
     g_parameter.data_pull_admin_send =0;
     return;
  }
 else  /*adminstate cmd from oam-- stop timer*/
  {
    stop_timer(TIMER_SIGTRAN);
  }
}
/*AOIP_HA end*/

    SCM_printf (SCM_CRITICAL, "SCM - > OAM ' STACK COMMAND RESPONSE'"); /*AOIP-HA print*/
    ret_val = scm_dispatch_buffer(msg_buff, APP_ID_OAM, 
                                ((ScmOamResponse*)msg_buff)->scmhdr.len);
    if(ret_val <= 0)
     {
      SCM_printf (SCM_CRITICAL, "Write to oam socket failure");
     }
#undef SET_OPERATION
}

void handle_ln_del_resp()
{
  g_parameter.peer_link_del = 0;
  g_roll_back_flag.nwstk_roll_back_flag = 1;
  ((ScmHdr*)g_parameter.nwstk_msg)->operation = SCM_ADD;
  /* write roll back procedure here*/
  process_oam_message(g_parameter.nwstk_msg);
  g_parameter.peer_nwstk_cmdFlag = 0;
  free(g_parameter.nwstk_msg) ;
  g_parameter.nwstk_msg = NULL;
}
/***************************************************************************/
/*This function extracts the appid from response opcode received from
  peer card scm*/
/***************************************************************************/
int get_app_id_from_resp_opcode(U16 resp_opcode)
{
 switch(resp_opcode)
  {
   case SCM_OAM_ALARM_MODIFY_RESP:
        return MULTI_CMD;
#if 0   
   case SCM_OAM_MAP_TIMER_CONFIG_RESP:
   case SCM_OAM_MAP_SEC_CONFIG_RESP:
        return APP_ID_MAP;
#endif

   case SCM_OAM_LINK_CONFIG_RESP      :
   case SCM_OAM_LINKSET_CONFIG_RESP   :
   case SCM_OAM_MTP3_TIMER_CONFIG_RESP:
   case SCM_OAM_SCCP_TIMER_CONFIG_RESP:  
   case SCM_OAM_BSSAP_TIMER_CONFIG_RESP:  
   case SCM_OAM_SS7_STACK_CONFIG_RESP:
   case SCM_OAM_TRUNK_CIC_CONFIG_RESP:
   case SCM_OAM_INTERFACE_CONFIG_RESP:
   case SCM_OAM_SS7ROUTE_CONFIG_RESP:
   case SCM_OAM_SS7ROUTE_ADMIN_CONFIG_RESP:
   case SCM_OAM_SS7ROUTE_TESTON_CONFIG_RESP:
   case SCM_OAM_LINK_PEG_RESP:
   case SCM_OAM_MTP2_PEG_RESP:
        return APP_ID_NWSTK;


   case OAM_SCM_LAPDTS_CONFIG:
   case OAM_SCM_LAPDTEI_CONFIG:
   case OAM_SCM_LAPDSAPI_CONFIG:
          return APP_ID_LAPD;

 /*AOIP_HA*/
   case SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP:
   case SCM_OAM_M3UA_LOCAL_ASP_CONFIG_RESP:
   case SCM_OAM_M3UA_REMOTE_ASP_CONFIG_RESP:
   case SCM_OAM_M3UA_LOCAL_AS_CONFIG_RESP:
   case SCM_OAM_M3UA_REMOTE_AS_CONFIG_RESP:
   case SCM_OAM_M3UA_TIMER_CONFIG_RESP:
           return APP_ID_SIGTRAN;  
        
   case SCM_OAM_SCCP_SP_CONFIG_RESP:         
   case SCM_OAM_SCCP_SS_CONFIG_RESP:        
   case SCM_OAM_SCCP_CSS_CONFIG_RESP:       
   case SCM_OAM_SCCP_CSP_CONFIG_RESP:        
   case SCM_OAM_SCCP_TMR_CONFIG_RESP:
           return APP_ID_SIGTRAN;  

   case SCM_OAM_SCTP_GEN_CONFIG_RESP:
   case SCM_OAM_SCTP_TIMER_CONFIG_RESP:
           return APP_ID_SIGTRAN;  

 /*AOIP_HA END*/
          
    
  }
 SCM_printf (SCM_CRITICAL, "Wrong value recieved from peer scm in resp_opcode ");
 stop_timer(TIMER_SIGTRAN);
 return 1;/* 1 is returned to distinguish 0(i.e. for MULTICMD) 
             it means no parsing at scm for resp opcode*/ 
}

/***************************************************************************/
/*This function set the response waiting flag in case of received from
  peer card scm*/
/***************************************************************************/
void set_stackFlag_to_respond_peer_scm(U16 opcode)
{
 U8 app_id, update;
 app_id = get_entity_appid(opcode, &update, 0);
 if((opcode == OAM_SCM_SS7_STACK_CONFIG) || opcode == OAM_SCM_ALARM_MODIFY)
   {
     g_parameter.multicmd_standby_respFlag = 1;  
     return;
   }
 
 switch(app_id)
 {
  case APP_ID_SIGTRAN:
  case APP_ID_MAP:
       g_parameter.maptcap_standby_respFlag = 1;  
       break;
  case APP_ID_NWSTK:
       g_parameter.nwstk_standby_respFlag = 1;  
       break;
  case APP_ID_LAPD:
       g_parameter.lapd_standby_respFlag = 1;  
       break;
  default:
       SCM_printf(SCM_CRITICAL,"config cmd: WRONG OPCODE VALUE FOR PARSING AT STANDBY SCM");
        
 }
 return; 
}

/*AOIP_HA*/
/*MODIFIED FOR ASP LOCK/UNLOCK*/
U16 Check_Peer_psp_and_Bss_state(U16 *no_asp, U16 *asp_id, U16 *asp_state) /*(asp1, state1, asp2 ,state 2) if both peer asp then admin for both sent*/
{
    U16 Unlocked = 1;
    U16 Locked   = 0;
    U16 lv =0, ret_val =0, index=0;
    U8 row_count=0;
    SigtranM3uaLAspConfigTableApi *M3uaLocAspConfigPtr=NULL;
   /*foR Bss table*/
    void    *DbPtr=NULL;
    I_U32    bss_rows=0;
    I_U16    bss_size=0;
    I_S32 dbSts;
    BssTableApi *BssTblPtr = NULL;
   /*end*/
    SCM_printf(SCM_MAJOR,"Check Peer card ASP_ADMIN_STATE & ASP_ID :: self_slot[%d] \n", g_parameter.slot_id);
    ret_val = GetLocalAspAdminStatePtr(&M3uaLocAspConfigPtr, &row_count);   /*comment */
    if( ret_val == 0 && (row_count==1 || row_count == 2))
     {
         SCM_printf(SCM_INFO,"READ FROM DB IS SUCCESS \n");
         for(lv=0; lv<row_count; lv++)                                     
          {
             switch(g_parameter.slot_id)
               {
                  
                  case SLOT_3:
                       SCM_printf(SCM_INFO,"[Row %d].localAspId -> %d \n", lv, M3uaLocAspConfigPtr[lv].localAspId);
                       SCM_printf(SCM_INFO,"[Row %d].adminState -> %d \n", lv, M3uaLocAspConfigPtr[lv].adminState);
                       SCM_printf(SCM_INFO,"[Row %d].Slot_id    -> %d \n", lv, M3uaLocAspConfigPtr[lv].slotId);
                       if(M3uaLocAspConfigPtr[lv].slotId == (SLOT_4 - 2))     /*ACTUAL 4 but did (-2) for mapping Sigtran slotId*/
                        { 
                           if(M3uaLocAspConfigPtr[lv].adminState == Unlocked)
                            {
                               asp_id[index]    = M3uaLocAspConfigPtr[lv].localAspId;
                               asp_state[index] = Unlocked;
                               index++;
                               (*no_asp)++;
                            }
                        }
                        
                  break; 
                  case SLOT_4:
                       SCM_printf(SCM_INFO,"[Row %d].localAspId -> %d \n", lv, M3uaLocAspConfigPtr[lv].localAspId);
                       SCM_printf(SCM_INFO,"[Row %d].adminState -> %d \n", lv, M3uaLocAspConfigPtr[lv].adminState);
                       SCM_printf(SCM_INFO,"[Row %d].Slot_id    -> %d \n", lv, M3uaLocAspConfigPtr[lv].slotId);
                       if(M3uaLocAspConfigPtr[lv].slotId == (SLOT_3 - 2))
                        {
                           if(M3uaLocAspConfigPtr[lv].adminState == Unlocked)
                            {
                               asp_id[index]    = M3uaLocAspConfigPtr[lv].localAspId;
                               asp_state[index] = Unlocked;
                               index++;
                               (*no_asp)++;
                            }
                        }
                  break; 
               }
          }
     }
    else
     {
 
          SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
          return -1; 
     }
   
    if(M3uaLocAspConfigPtr != NULL)
     {
           free(M3uaLocAspConfigPtr);
           M3uaLocAspConfigPtr = NULL;
     }

    if((*no_asp) == 1 || (*no_asp) ==2)
     {
        SCM_printf(SCM_MAJOR,"Peer Asp's Count %d Check Bss Admin State \n", *no_asp);
        dbSts = getallBssTable((I_PVoid *)&DbPtr, (I_U32 *)&bss_rows, (I_U16 *)&bss_size);
        SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, bss_rows, bss_size);
        if(dbSts == DB_SUCCESS)
         {
            SCM_DUMP(0, (bss_rows*sizeof(BssTableApi)), (unsigned char* )DbPtr, 15);
            BssTblPtr = (BssTableApi*) DbPtr;
            if(BssTblPtr->adminState == Unlocked)
             {
                 SCM_printf(SCM_MAJOR,"BSS IN UNLOCK STATE\n");
                 if(DbPtr != NULL)
                  {
                    free(DbPtr);
                  }
                 return Unlocked; /*bss is unlocked*/
             }
            else
             {
                 SCM_printf(SCM_MAJOR,"BSS IN LOCK STATE\n");
                 if(DbPtr != NULL)
                  {
                    free(DbPtr);
                  }
                 return Locked; /*bss is locked*/
             }
         
         }
        else
         {
            SCM_printf(SCM_CRITICAL,"READ FROM DB IS FAILURE ERROR_CODE: %d\n", ret_val);
            return -1; 
         }
     }
    /*HERE CHECK BSS ADMIN STATE AND ACC SEND 1 FOR BSS UNLOCK & 0 FOR BSS LOCKED*/
     
     return Locked;
}

I_S32  GetLocalAspAdminStatePtr (SigtranM3uaLAspConfigTableApi  **M3uaConfigPtrToPtr, U8 *row_count)
{
   I_S16 rowSize = 0;
   I_S16 i = 0;
   I_S32 rowCount = 0;
   I_S32 dbSts;
   void       *DbPtr=NULL;
   SigtranM3uaLAspConfigTableApi *M3uaTblPtr=NULL;
   SigtranM3uaLAspConfigTableApi *M3uaConfigPtr=NULL;
   strcpy(g_parameter.function_string, "M3uaLocAspTableApi()");

   dbSts = getallSigtranM3uaLAspConfigTable( (I_PVoid *)&DbPtr, (I_U32 *)&rowCount, (I_U16*)&rowSize);
   *row_count = rowCount;
   SCM_printf (SCM_DEBUG, "dbSts: %d, rowsize: %d, rowCount %d\n", dbSts, rowSize, rowCount);
   if(dbSts == DB_SUCCESS)
   {
     /* SCM_DUMP(0,(rowCount *sizeof(SigtranM3uaLAspConfigTableApi)), (unsigned char* )DbPtr, 15);dump not req */
      M3uaConfigPtr = calloc (rowCount,sizeof(SigtranM3uaLAspConfigTableApi));
      *M3uaConfigPtrToPtr = M3uaConfigPtr;
      while (rowCount)
      {
         M3uaTblPtr  = (SigtranM3uaLAspConfigTableApi*)(DbPtr + i*rowSize);
         M3uaConfigPtr[i].localAspId        = (U16)M3uaTblPtr->localAspId;
         M3uaConfigPtr[i].localPort         = (U16)M3uaTblPtr->localPort;
         M3uaConfigPtr[i].slotId            = (U16)M3uaTblPtr->slotId;
         M3uaConfigPtr[i].assocType         = (U16)M3uaTblPtr->assocType;
         M3uaConfigPtr[i].maxInStream       = (U16)M3uaTblPtr->maxInStream;
         M3uaConfigPtr[i].maxOutStream      = (U16)M3uaTblPtr->maxOutStream;
         M3uaConfigPtr[i].operationalStatus = (U16)M3uaTblPtr->operationalStatus;
         M3uaConfigPtr[i].adminState = (U16)M3uaTblPtr->adminState;   /*need to make this extra function due to this variable*/
         memcpy(M3uaConfigPtr[i].localIp , M3uaTblPtr->localIp, 25);
         memcpy(M3uaConfigPtr[i].name    , M3uaTblPtr->name   , 25);
         rowCount--;
         i++;

      }
         free(DbPtr);

   }
   else
  {
      return dbSts;
   }
return 0;
}

/*AOIP_HA end*/

/*AOIP BT ADDED*/
void fault_trap()
{
  printf("GOT THE FAULT TRAP\n");
  void *array[64];
  size_t size;
  char **strings;
  size_t i;


  size = backtrace (array, 64);
  strings = backtrace_symbols (array, size);
  SCM_printf(SCM_CRITICAL,"Obtained %zd stack frames.\n", size);


  for (i = 0; i < size; i++)
  {
     SCM_printf(SCM_CRITICAL,"%s \n", strings[i]);
  }
  free (strings);

exit(0);

}

void bt_sig_hndlr_reg ()
{
  struct sigaction sa;

  SCM_printf(CRITICAL," reg_sig_hndlr :: Entering for Capture SIGNAL\n");
  sa.sa_sigaction = fault_trap;
  sigemptyset (&sa.sa_mask);
  sa.sa_flags = SA_RESTART | SA_SIGINFO;

  sigaction (SIGKILL, &sa, NULL);
  sigaction (SIGSEGV, &sa, NULL);
  sigaction (SIGFPE, &sa, NULL);
  sigaction (SIGABRT, &sa, NULL);

  return;
}

/* FILE ENDS */

/********************************* Change History ***************************
'$Rev: 145 $
 initial version

 
 *************************************************************************/

