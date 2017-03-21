#include <scm_localhashdef.h>
#include <scm_errorcode.h>
//#include <scm_oamint_error_code.h>
#include <scm_encaps.h>


void* scm_malloc( size_t  size)
{
 void *p_void;
 p_void = malloc(size);
 if(p_void==NULL)
  {
   SCM_printf(SCM_CRITICAL,"\nMEMORY ALLOCATION FAILED ");
   exit(1);
  }
 return p_void;
}

char* get_entity(int entity)
 {
 char *entity_name;
 strcpy(g_parameter.function_string, "get_entity()");
 switch (entity)
   {
   case ENT_PEER_SCM:
        entity_name = "PEER SCM";
        break;
   case ENT_NWSTK_DBG:
        entity_name = "DBG CONSOLE";
        break;
   case ENT_LAPD:
        entity_name = "LAPD STACK";
        break;
   case ENT_NWSTK:
        entity_name = "N/W STACK";
        break;
   case ENT_OAM:
        entity_name = "OAM";
        break;
   case ENT_SIGTRAN:
        entity_name = "SIGTRAN";
        break;
   case ENT_BSSAP:
        entity_name = "BSSAP";
        break;
   default:
        SCM_printf(SCM_MAJOR,"\nSCM_MISC_FUNC: DEFAULT CASE"); 
        return "entity not found";
   }
  return entity_name;     
 }

U32 check_if_previous_cmd_in_progress(U8 app_id)
 {
  U32 previous_cmd_status =0;
  strcpy(g_parameter.function_string, "check_if_previous_cmd_in_progress()");
  switch(app_id)
     {
        case APP_ID_SIGTRAN: 
        case APP_ID_MAP:
             if(timer_info[TIMER_SIGTRAN].timer_strt_flag == 1)
               {
                previous_cmd_status = 1;  
               }  
             break;
        case APP_ID_NWSTK:
             if(timer_info[TIMER_NWSTK].timer_strt_flag == 1)
               {
                previous_cmd_status = 1;  
               }  
             break;
        case APP_ID_LAPD:
             if(timer_info[TIMER_LAPD].timer_strt_flag == 1)
               {
                previous_cmd_status = 1;  
               }  
             break;
      /*AOIP: CASE ADDED*/
        case APP_ID_BS:
             if(timer_info[TIMER_BSSAP].timer_strt_flag == 1)
               {
                previous_cmd_status = 1;  
               }  
             break;
       /*AOIP: END*/

        default:
             SCM_printf (SCM_INFO, "\nWRONG APP_ID VALUE");
             break;
     }
  return  previous_cmd_status;  

 }

/***************************************************************************/
/*This function message process the message from waiting message 
  queue waiting for scm external entity connectivity recognition or for initial config*/
/***************************************************************************/

 
void process_message_queue()
{
 msgbuf msgbuffer;
 msg_queue_buff *queue_buff;
 strcpy(g_parameter.function_string, "process_message_queue()");
 if( msgrcv( g_parameter.soc_event_q_Id, (msgbuf *)&msgbuffer, sizeof(msgbuf)-4, 0, IPC_NOWAIT) == -1)
  {
   //SCM_printf(SCM_INFO,"\n CONFIG MESSAGE QUEUE IS EMPTY");
   return ;
  }   
 else 
  {
   queue_buff = (msg_queue_buff*)&msgbuffer.mtext[0];
   SCM_printf(SCM_INFO,"\n READING CONFIG MESSAGE QUEUE");
   SCM_DUMP(0, sizeof(msg_queue_buff), (U8*)queue_buff, 15); 
   /* initiallization for stack config if entity comes up is stack entity */
   switch(queue_buff->entity_id) 
       {
        case ENT_LAPD:
         SCM_printf(SCM_INFO,"\n ENT COMES UP LAPD ");
         SCM_printf(SCM_INFO,"\n g_parameter.redundant_status = %d ", g_parameter.redundant_status);
         SCM_printf(SCM_MAJOR,"\n CONFIG BIGINS FOR LAPD ");
         g_parameter.config_flag             = SS7_TRUE;
         g_parameter.entity_cfg              = ENT_LAPD;
 
         multi_cmd[0].roll_back_flag = 0;
         g_parameter.no_config_cmd_sent      = 0;
         g_parameter.config_cmd_resp         = 0;
         g_parameter.no_command_resp_success = 0;
         g_parameter.no_of_config_row_sent = 0;
         g_parameter.lapd_cfgComplete = 0;
         if((timer_info[TIMER_LAPD].timer_strt_flag == 1))
            {
             stop_timer(TIMER_LAPD);
            }
         break;

        case ENT_NWSTK:
         g_parameter.ss7_up_alarm = 1;
         if(g_parameter.lapd_cfgComplete != 1)
         {
          g_parameter.nwstk_cfg_wait = 1;
          start_timer ( TIMER_NWSTK_CONFIG, APP_ID_NWSTK, 0, NULL);
          break;
         }
         SCM_printf(SCM_INFO,"\n ENT COMES UP NWSTK ");
#ifdef NWSTK_REDUNDANCY
         SCM_printf(SCM_INFO,"\n g_parameter.redundant_status = %d ", g_parameter.redundant_status);
         if((g_parameter.redundant_status == SCM_ACTIVE) )
          {
            SCM_printf(SCM_INFO,"\n SCM IS IN ACTIVE STATE CONFIGURE SCM ");
            SCM_printf(SCM_MAJOR,"\n CONFIG BIGINS FOR NWSTK ");
            g_parameter.config_flag             = SS7_TRUE;
            g_parameter.entity_cfg              = ENT_NWSTK;
            if(g_parameter.nwstk_cfgIndFromPeerCard == 1)
              { 
               g_parameter.link_config_flag = 1;   
              }
             else 
              {
               g_parameter.link_config_flag = 0; 
              }
 
          }
         else
          { 
           if((g_parameter.nwstk_cfgIndFromPeerCard == 1)&&(g_parameter.nwstk_cfgComplete == 0))
            { 
              g_parameter.config_flag             = SS7_TRUE;
              g_parameter.entity_cfg              = ENT_NWSTK;
              g_parameter.link_config_flag = 1;
            }      
          }
#else           
         SCM_printf(SCM_MAJOR,"\n CONFIG BIGINS FOR NWSTK ");
         g_parameter.config_flag             = SS7_TRUE;
         g_parameter.entity_cfg              = ENT_NWSTK;
         g_parameter.link_config_flag = 0; 
#endif
         multi_cmd[0].roll_back_flag = 0;
         g_parameter.nwstk_cfgComplete = 0; 
         g_parameter.no_config_cmd_sent      = 0;
         g_parameter.config_cmd_resp         = 0;
         g_parameter.no_command_resp_success = 0;
         g_parameter.no_of_config_row_sent = 0;
         delete_link_hashTbl();
         delete_linkset_hashTbl();
         if((timer_info[TIMER_NWSTK].timer_strt_flag == 1))
            {
             stop_timer(TIMER_NWSTK);
            }
         multi_cmd[0].lock_flag            = 0;   
         break;
        case NWSTK_CONFIG_COMPLETE:
#ifdef NWSTK_REDUNDANCY
             if(g_parameter.nwstk_cfgComplete == 0)
              {
               g_parameter.config_flag                          =  SS7_TRUE;
               g_parameter.entity_cfg                            =  ENT_NWSTK;
               if(xxx_client_sockfd[ENT_PEER_SCM] > 0)
               {
                g_parameter.link_config_flag  =  1;
               }  
               SCM_printf(SCM_MAJOR,"\n  CONFIG  BIGINS  FOR  NWSTK  ");
               multi_cmd[0].roll_back_flag  =  0;
               g_parameter.nwstk_cfgComplete  =  0;
               g_parameter.no_config_cmd_sent            =  0;
               g_parameter.config_cmd_resp                  =  0;
               g_parameter.no_command_resp_success  =  0;
               g_parameter.no_of_config_row_sent  =  0;
               if((timer_info[TIMER_NWSTK].timer_strt_flag  ==  1))
                {
                 stop_timer(TIMER_NWSTK);
                }
                multi_cmd[0].lock_flag                        =  0;
              }
             else
              SCM_printf(SCM_MAJOR,"\n  self card Nwstk is configured");
#endif
              break;
 
        case ENT_SIGTRAN:
         /*MANTIS ID:- 0032492*/
         if(g_parameter.redundant_status == SCM_STANDBY && g_parameter.scm_scm_up == 0)
           {
             SCM_printf(SCM_INFO,"\n ENTITY UP SIGTRAN :- WAIT SCM_SCM_NOT_UP\n");
             g_parameter.stby_sigtran_config_wait = 1;
             g_parameter.entity_up--;
             break;
           }
         /*MANTIS END*/
         SCM_printf(SCM_INFO,"\n ENT COMES UP SIGTRAN");
         SCM_printf(SCM_MAJOR,"\n CONFIG BEGINS FOR SIGTRAN");
         g_parameter.config_flag             = SS7_TRUE; /* Change by Amaresh SS7_TRUE;*//*STOP for OAM TEST*/
         g_parameter.entity_cfg              = ENT_SIGTRAN;
         g_parameter.no_config_cmd_sent      = 0;
         g_parameter.config_cmd_resp         = 0;
         g_parameter.no_command_resp_success = 0;
         g_parameter.no_of_config_row_sent = 0;
         g_parameter.sigtran_cfgComplete = 0;
         if((timer_info[TIMER_SIGTRAN].timer_strt_flag == 1))
            {
             stop_timer(TIMER_SIGTRAN);
            }
         break;
        case ENT_SCM:
        case ENT_PEER_SCM:
         SCM_printf(SCM_INFO,"\n ENT COMES UP PEERSCM ");
         if(g_parameter.self_nwstk_up == 1)
          {
           send_stack_enity_up_to_peerscm(ENT_NWSTK);
          }
         /*here if card is standby and conf of sigtran and bssap done then
           from here send card up ind. to active card*/
          if(g_parameter.self_stack_up == 1)
           { 
              if(g_parameter.nwstk_stsUp_sent == 0)
               {
                 SCM_printf(SCM_MAJOR,"[JOIN] STACKUP IND SEND TO PEER SCM \n");
                 send_stack_enity_up_to_peerscm(ENT_SIGTRAN);
               }
           }
         /*MANTIS ID:- 0032492*/
          g_parameter.scm_scm_up = 1;
          
         if(g_parameter.stby_bssap_config_wait == 1)
           {
               g_parameter.stby_bssap_config_wait = 0;
               if(write_in_sock_event_q(ENT_BSSAP) == 0)
                {
                 SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL - BSSAP");
                }
               else
                 SCM_printf(SCM_CRITICAL,"QUEUE ENTITY - BSSAP");
           }

         if(g_parameter.stby_sigtran_config_wait == 1)
           {
               g_parameter.stby_sigtran_config_wait = 0;
               if(write_in_sock_event_q(ENT_SIGTRAN) == 0)
                {
                 SCM_printf(SCM_CRITICAL,"\nWRITE TO SOCK EVENT QUEUE FAIL - SIGTRAN");
                }
               else
                 SCM_printf(SCM_CRITICAL,"QUEUE ENTITY - SIGTRAN");

           }
         /*MANTIS END*/
         break; 
         /*handling for peer scm will be here */ 
          
        case ENT_OAM:
         SCM_printf(SCM_MAJOR,"\n ENT COMES UP OAM");
         
          if(g_parameter.oam_up !=  0)
           {
             g_parameter.ss7_up_alarm = 1;
             g_parameter.ss7_up_alarm = 0; /*AOIP CHANGE*/
            }
           else
            {
             g_parameter.oam_up = 1;
             g_parameter.ss7_up_alarm = 1;/*AOIP CHANGE*/
            }
         if(((g_parameter.ss7_up_alarm == 1) && (g_parameter.nwstk_cfgComplete == 1)&&
            (g_parameter.lapd_cfgComplete == 1)) ||
            ((g_parameter.ss7_up_alarm == 1) && (g_parameter.bssap_cfgComplete == 1)&&
            (g_parameter.sigtran_cfgComplete == 1))) /*AOIP CHANGE*/
            process_scm_alarm(SS7_UP);
  

         break;  
         /*handling for peer scm will be here */  
        /*AOIP: ENT BSSAP UP*/
        case ENT_BSSAP:
         /*MANTIS ID:- 0032492*/
         if(g_parameter.redundant_status == SCM_STANDBY && g_parameter.scm_scm_up == 0)
           {
             SCM_printf(SCM_INFO,"\n ENTITY UP BSSAP :- WAIT SCM_SCM_NOT_UP\n");
             g_parameter.stby_bssap_config_wait = 1;
             g_parameter.entity_up--;
             break;
           }
         /*MANTIS END*/
        SCM_printf(SCM_INFO,"ENT COMES UP BSSAP\n");
        SCM_printf(SCM_MAJOR,"CONFIG BEGINS FOR BSSAP\n");
         g_parameter.config_flag             = SS7_TRUE; /*STOP FOR OAM TEST*/
         g_parameter.entity_cfg              = ENT_BSSAP;
         g_parameter.no_config_cmd_sent      = 0;
         g_parameter.config_cmd_resp         = 0;
         g_parameter.no_command_resp_success = 0;
         g_parameter.no_of_config_row_sent = 0;
         g_parameter.bssap_cfgComplete = 0;
         if((timer_info[TIMER_BSSAP].timer_strt_flag == 1))
         {
           stop_timer(TIMER_BSSAP);
         }

        break;
        /*AOIP: END*/

       }
   }
return ;
}
 
void form_oam_header( U8* msg_buff, U16 opcode, U8 operation, U32  trid, U16 pegrfu,  U16  len)
 {
 ScmHdr scmHdr;
 if((opcode == NWSTK_CONFIG_COMPLETE)||(opcode == SCM_NWSTKUP) ||
    (opcode == ISUP_CONFIG_COMPLETE) ||(opcode == MAPTCAP_CONFIG_COMPLETE)||
    (opcode == OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG)||(opcode == MAPTCAP_STACK_UP))
  {
    scmHdr.appid      =  APP_ID_PEER_SCM;
  }
 else
 {
  scmHdr.appid      =  165;  /*APP_ID_OAM*/
 }
 scmHdr.opcode     =  opcode;
 scmHdr.operation  =  operation;
 scmHdr.trid       =  trid;
 scmHdr.len        =  len;
 scmHdr.spare      =  pegrfu;
 memcpy(msg_buff, &scmHdr, sizeof(ScmHdr));
 return;
 }

void form_scm_header( U8* msg_buff, U16 opcode, U8 operation, U32  trid,  U16  len)
 {
 ScmHdr scmHdr;
 
 scmHdr.appid      =  160;
 scmHdr.opcode     =  opcode;
 scmHdr.operation  =  SCM_ADD;
 scmHdr.trid       =  trid;
 scmHdr.len        =  len;
 memcpy(msg_buff, &scmHdr, sizeof(ScmHdr));
 return;
 }
int form_nwstk_header(U8* msg_buff, U8 app_id, U8 opcode, U8 tr_id, U16 len)
 {
  msg_buff[0] = app_id;
  msg_buff[1] = opcode;
  msg_buff[2] = tr_id;
  EXTRACT_16(3,len,msg_buff);
  return 1;
 }
 
int form_maptcap_header(U8* msg_buff, U8 app_id, U8 noe, U8 ctgry, U8 tr_id, U8 cmd, U16 Length)
{
              #define ASGN(A,C) \
                              msg_buff [A]   = C;

              ASGN (0, app_id);
              ASGN (1, 1);
              ASGN (2, noe);
              ASGN (3, Length & 0xff);
              ASGN (4, (Length >> 8) & 0xff);
              ASGN (5, ctgry);
              ASGN (6, cmd);
              ASGN (7, tr_id);

              #undef ASGN
              return 1;

}



U8 get_entity_appid(U16 opcode, U8* peer_update, U8 operation)
 {
  switch(opcode)
    {
     case OAM_SCM_LINK_CONFIG           :
     case OAM_SCM_MTP3_TIMER_CONFIG     :
     case OAM_SCM_SCCP_TIMER_CONFIG     :  
     case OAM_SCM_BSSAP_TIMER_CONFIG    : 
     case OAM_SCM_TRUNK_CIC_CONFIG: 
     case OAM_SCM_INTERFACE_CONFIG: 
#ifdef GCS_OBSOLETE
     case OAM_SCM_MTP3_TIMER_CONFIG: 
     case OAM_SCM_SCCP_TIMER_CONFIG: 
     case OAM_SCM_BSSAP_TIMER_CONFIG: 
     case OAM_SCM_TRUNK_CIC_CONFIG: 
     case OAM_SCM_INTERFACE_CONFIG: 
     case OAM_SCM_LINKSET_CONFIG: 
     case OAM_SCM_LINK_CONFIG: 
     case OAM_SCM_SS7ROUTE_CONFIG: 
     case OAM_SCM_SS7ROUTE_ADMIN_CONFIG: 
     case OAM_SCM_SS7_STACK_CONFIG: 
#endif
          *peer_update = 1;
          return APP_ID_NWSTK;

     case OAM_SCM_LAPDTS_CONFIG         :
     case OAM_SCM_LAPDTEI_CONFIG        :
     case OAM_SCM_LAPDSAPI_CONFIG       :
          *peer_update = 1;
          return APP_ID_LAPD;

     case OAM_SCM_LAPD_PEG_GET:
     case OAM_SCM_LAPDTIMER_CONFIG      :
          *peer_update = 0;
          return APP_ID_LAPD;
 
     case OAM_SCM_LINK_ADMIN_CONFIG     :
/* Added by Amaresh Start as on dated 12-11-16 */
          *peer_update = 1;
          return APP_ID_MAP;  
/* Added by Amaresh Stop as on dated 12-11-16 */
     case OAM_SCM_SS7_STACK_CONFIG      :
     case OAM_SCM_LINKSET_CONFIG: 
     case OAM_SCM_LINKSET_ADMIN_CONFIG  :
     case OAM_SCM_SS7ROUTE_CONFIG       :
     case OAM_SCM_SS7ROUTE_ADMIN_CONFIG :
     case OAM_SCM_MTP3_GENPEG_GET       : 
     case OAM_SCM_LINK_PEG_GET          :
     case OAM_SCM_MTP2_PEG_GET          :
     case OAM_SCM_SS7ROUTE_PEG_GET      :
     case OAM_SCM_SCCP_GENPEG_GET       :
     case OAM_SCM_BSSAP_GENPEG_GET      :  
     case OAM_SCM_MTP3_GEN_CFG          :
     case OAM_SCM_BSSAP_GEN_CFG         :
     case OAM_SCM_SCCP_GEN_CFG          :
     case OAM_SCM_RSSN_CONFIG           :
     case OAM_SCM_LSSN_CONFIG           :
     case OAM_SCM_CSSN_CONFIG           :
     case OAM_SCM_LINKSET_STATUS_GET    :
     case OAM_SCM_LINK_STATUS_GET       :
     case OAM_SCM_ROUTE_STATUS_GET      :
     case OAM_SCM_SSN_STATUS_GET        :    
     case OAM_SCM_SCCP_BEHAVIOR_CONFIG  :   
#ifdef GCS_OBSOLETE
     //case OAM_SCM_SS7_STACK_CONFIG      :
     case OAM_SCM_LINKSET_ADMIN_CONFIG  :
     case OAM_SCM_LINK_ADMIN_CONFIG     :
     case OAM_SCM_MTP3_GENPEG_GET       : 
     case OAM_SCM_LINK_PEG_GET          :
     case OAM_SCM_SS7ROUTE_PEG_GET      :
     case OAM_SCM_SCCP_GENPEG_GET       :
     case OAM_SCM_BSSAP_GENPEG_GET      :  
     case OAM_SCM_MTP3_GEN_CFG          :
     case OAM_SCM_BSSAP_GEN_CFG         :
     case OAM_SCM_SCCP_GEN_CFG          :
     case OAM_SCM_RSSN_CONFIG           :
     case OAM_SCM_LSSN_CONFIG           :
     case OAM_SCM_CSSN_CONFIG           :
     case OAM_SCM_LINKSET_STATUS_GET    :
     case OAM_SCM_LINK_STATUS_GET       :
     case OAM_SCM_ROUTE_STATUS_GET      :
     case OAM_SCM_SSN_STATUS_GET        :    
     case OAM_SCM_SCCP_BEHAVIOR_CONFIG  :   
     case OAM_SCM_MTP2_PEG_GET          :    
#endif 
     
     
          *peer_update = 0;
          return APP_ID_NWSTK;
/* Commented removed by Amaresh Start */                                    
     case OAM_SCM_MAP_SEC_CONFIG        :
     case OAM_SCM_MAP_TIMER_CONFIG      :

          *peer_update = 1;
          return APP_ID_MAP;  

     case OAM_SCM_MAP_INIT_CONFIG       :
     case OAM_SCM_MAP_ALARM_LEVEL_MODIFY:

          *peer_update = 0;
          return APP_ID_MAP;  
         
     case OAM_SCM_TCAP_ALARM_LEVEL_MODIFY :
     case OAM_SCM_TCAP_PEG_GET          :
     case OAM_SCM_TCAP_INIT_CONFIG      :
          *peer_update = 0;
           return APP_ID_TCAP;
/* Commented removed by Amaresh Stop */ 

 /*AOIP: OPCODES START*/
     case OAM_SCM_BS_TIMER_CONFIG:
     case OAM_SCM_BS_INTERFACE_CONFIG:
           *peer_update = 0;   
          return APP_ID_BS;

     case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG: /*command sent to peer without use of flag*/
           *peer_update = 0;  
           return APP_ID_SIGTRAN;

     case OAM_SCM_SCCP_SP_CONFIG:
     case OAM_SCM_SCCP_SS_CONFIG:
     case OAM_SCM_SCCP_CSS_CONFIG:
     case OAM_SCM_SCCP_CSP_CONFIG:
     case OAM_SCM_M3UA_LOCAL_ASP_CONFIG:
     case OAM_SCM_M3UA_REMOTE_ASP_CONFIG:
     case OAM_SCM_M3UA_LOCAL_AS_CONFIG:
     case OAM_SCM_M3UA_REMOTE_AS_CONFIG:
     case OAM_SCM_SCTP_GEN_CONFIG:
     case OAM_SCM_SCCP_TMR_CONFIG:
     case OAM_SCM_M3UA_TIMER_CONFIG:
     case OAM_SCM_SCTP_TIMER_CONFIG:
            *peer_update = 1;  /*SET for cmd to be sent to peer*/
           return APP_ID_SIGTRAN;
 /*AOIP: OPCODES END*/

      default:
          SCM_printf(SCM_MAJOR,"\n OPCODE VALUE UNKNOWN");
          break;
              
         
   }
 return 0;
}


void free_peer_update_pointer()
{
 strcpy(g_parameter.function_string, "free_peer_update_pointer()");
 
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
 else
 if(g_parameter.peer_nwstk_cmdFlag == 1)
            {
             if(g_parameter.nwstk_msg != NULL)
              {
               g_parameter.peer_nwstk_cmdFlag = 0;
               stop_timer(TIMER_NWSTK);
               free(g_parameter.nwstk_msg) ;
               g_parameter.nwstk_msg = NULL;
              }
            }
   else
     return;
 
  
 return; 
 
}

int validate_length_of_messag(U16 opcode, U16 len)
{
 U16 length;

 switch(opcode)
 {
   case OAM_SCM_SS7_STACK_CONFIG:
        length = sizeof(OamScmSs7StackConfig);
        break;
   case OAM_SCM_LAPDTS_CONFIG         :
        length = sizeof(OamScmLapdTSConfig); 
        break;
   case OAM_SCM_LAPDTEI_CONFIG        :
        length = sizeof(OamScmLapdTEIConfig); 
        break;
   case OAM_SCM_LAPDSAPI_CONFIG       :
        length = sizeof(OamScmLapdSAPIConfig); 
        break;
   case OAM_SCM_LAPDTIMER_CONFIG      :
        length = len;//sizeof(OamScmLapdTimerConfig); 
        break;
   case OAM_SCM_LAPD_PEG_GET:
        length = len;//sizeof(OamScmLapdPegGet); 
        break;
   case OAM_SCM_ALARM_MODIFY:
        length = sizeof(OamScmAlarmModify); 
        break;
   case OAM_SCM_MTP3_TIMER_CONFIG:
        length = sizeof(OamScmMtp3TimerConfig); 
        break;
   case OAM_SCM_SCCP_TIMER_CONFIG:
        length = sizeof(OamScmSccpTimerConfig);
        break;
   case OAM_SCM_BSSAP_TIMER_CONFIG:
        length = sizeof(OamScmBssapTimerConfig); 
        break;
#if 0
   case OAM_SCM_MAP_TIMER_CONFIG:
        length = sizeof(OamScmMapTimerConfig); 
        break;
   case OAM_SCM_MAP_SEC_CONFIG:
        length = sizeof(OamScmMapSecurityConfig); 
        break;
#endif
   case OAM_SCM_INTERFACE_CONFIG:
        length = sizeof(OamScmInterfaceConfig); 
        break;
   case OAM_SCM_LINKSET_CONFIG:
        length = sizeof(OamScmLinkSetConfig); 
        break;
   case OAM_SCM_LINKSET_ADMIN_CONFIG:
        length = sizeof(OamScmLinkSetAdminState); 
        break;
   case OAM_SCM_LINK_CONFIG:
        length = sizeof(OamScmLinkConfig); 
        break;
   case OAM_SCM_LINK_ADMIN_CONFIG:
        length = sizeof(OamScmLinkAdminState); 
        break;
   case OAM_SCM_SS7ROUTE_CONFIG:
        length = sizeof(OamScmSs7RouteConfig); 
        break;
   case OAM_SCM_SS7ROUTE_ADMIN_CONFIG:
        length = sizeof(OamScmSs7RouteAdminState); 
        break;
   case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
        length = sizeof(OamScmSs7RouteTestOnConfig); 
        break;
   case OAM_SCM_MTP3_GENPEG_GET:
        length = sizeof(OamScmMtp3GenPegGet); 
        break;
   case OAM_SCM_LINK_PEG_GET:
        length = sizeof(OamScmMtp3LinkPegGet); 
        break;
   case OAM_SCM_SS7ROUTE_PEG_GET:
        length = sizeof(OamScmMtp3RoutePegGet); 
        break;
   case OAM_SCM_SCCP_GENPEG_GET:
        length = sizeof(OamScmSccpGenPegGet); 
        break;
   case OAM_SCM_BSSAP_GENPEG_GET:
        length = sizeof(OamScmBssapGenPegGet); 
        break;
   case OAM_SCM_LINKSET_STATUS_GET:
        length = sizeof(OamScmLinkSetStatusGet); 
        break;
   case OAM_SCM_LINK_STATUS_GET:
        length = sizeof(OamScmLinkStatusGet); 
        break;
   case OAM_SCM_ROUTE_STATUS_GET:
        length = sizeof(OamScmRouteStatusGet); 
        break;
   case OAM_SCM_SSN_STATUS_GET:
        length = sizeof(OamScmSsnStatusGet); 
        break;
   case OAM_SCM_MTP2_PEG_GET:
        length = sizeof(OamScmMtp2PegGet); 
        break;

 /*AOIP: OAM MSG LEN VALIDATE*/
   case OAM_SCM_BS_INTERFACE_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_BS_INTERFACE_CONFIG");
        length = sizeof(OamScmBsInterfaceConfig); 
        break;
   case OAM_SCM_BS_TIMER_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_BS_TIMER_CONFIG");
        length = sizeof(OamScmBsTimerConfig); 
        break;
   case OAM_SCM_SCCP_SP_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCCP_SP_CONFIG:");
        length = sizeof(OamScmSccpSpConfig); 
        break;
   case OAM_SCM_SCCP_SS_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCCP_SS_CONFIG:");
        length = sizeof(OamScmSccpSsConfig); 
        break;
   case OAM_SCM_SCCP_CSS_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCCP_CSS_CONFIG:");
        length = sizeof(OamScmSccpCssConfig); 
        break;
   case OAM_SCM_SCCP_CSP_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCCP_CSP_CONFIG:");
        length = sizeof(OamScmSccpCspConfig); 
        break;
   case OAM_SCM_SCCP_TMR_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCCP_TMR_CONFIG:");
        length = sizeof(OamScmSccpTmrConfig); 
        break;
   case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG:");
        length = sizeof(OamScmM3uaLocalAspAdminConfig); 
        break;
   case OAM_SCM_M3UA_LOCAL_ASP_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_LOCAL_ASP_CONFIG:");
        length = sizeof(OamScmM3uaLocalAspConfig); 
        break;
   case OAM_SCM_M3UA_REMOTE_ASP_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_REMOTE_ASP_CONFIG:");
        length = sizeof(OamScmM3uaRemoteAspConfig); 
        break;
   case OAM_SCM_M3UA_LOCAL_AS_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_LOCAL_AS_CONFIG:");
        length = sizeof(OamScmM3uaLocalAsConfig); 
        break;
   case OAM_SCM_M3UA_REMOTE_AS_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_REMOTE_AS_CONFIG:");
        length = sizeof(OamScmM3uaRemoteAsConfig); 
        break;
   case OAM_SCM_M3UA_TIMER_CONFIG:
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_M3UA_TIMER_CONFIG:");
        length =sizeof(OamScmM3uaTimerConfig);      
        break;
   case OAM_SCM_SCTP_GEN_CONFIG:             
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCTP_GEN_CONFIG:");
        length =sizeof(OamScmSctpConfig);      
        break;
   case OAM_SCM_SCTP_TIMER_CONFIG:           
        SCM_printf (SCM_INFO, "FROM OAM: OAM_SCM_SCTP_TIMER_CONFIG:");
        length =sizeof(OamScmSctpTimerConfig);      
        break;

  /*AOIP: LEN VALIDATION END*/

    default:
        SCM_printf (SCM_MAJOR, "\nWRONG OPCODE VALUE RECIEVED\n");
       return 2;  
  }
 if(len == length)
   {
    return 1;
   }
  else
   {
     SCM_printf (SCM_INFO, "Length validation failure");
     SCM_printf (SCM_INFO, "ACTUAL   %d\n", length);
     SCM_printf (SCM_INFO, "RECEIVED %d\n", len);
    return 0;
   }
}














void form_resp_error_code(U32 error_code , U16 *resp_error_code, U8 entity)
{
 strcpy(g_parameter.function_string, "form_resp_error_code()");
 switch(entity)
   {
    case APP_ID_NWSTK:
         switch(error_code)
               {
                  case   NWSTK_LNKSET_NOTFOUND:   
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNKSET_NOTFOUND:");
                         *resp_error_code =  LNKSET_NOTFOUND;       
                         break; 
                   case  NWSTK_LNKSET_ALREADY_EXIST:   
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNKSET_ALREADY_EXIST");
                         *resp_error_code = LNKSET_ALREADY_EXIST;       
                         break; 
                  case   NWSTK_LNKSET_ADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNKSET_ADD_FAIL");
                         *resp_error_code = LNKSET_ADD_FAIL;        
                         break; 
                  case   NWSTK_LNKSET_DEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNKSET_DEL_FAIL   ");
                         *resp_error_code = LNKSET_DEL_FAIL;        
                         break; 
                  case   NWSTK_LINK_LNKSET_NOTFOUND:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LINK_LNKSET_NOTFOUND");
                         *resp_error_code =  LINK_LNKSET_NOTFOUND;       
                         break; 
                  case   NWSTK_LNK_NOTFOUND:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNK_NOTFOUND");
                         *resp_error_code =    LNK_NOTFOUND;     
                         break; 
                  case   NW_STK_LNK_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NW_STK_LNK_ALREADY_EXIST");
                         *resp_error_code =    LNK_ALREADY_EXIST;     
                         break; 
                  case   NWSTK_LNK_ADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNK_ADD_FAIL");
                         *resp_error_code =  LNK_ADD_FAIL;       
                         break; 
                  case   NWSTK_LNK_DEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LNK_DEL_FAIL:");
                         *resp_error_code =  LNK_DEL_FAIL;       
                         break; 
                  case   NWSTK_INSTID_INVALID:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_INSTID_INVALID:");
                         *resp_error_code =   UNKNOWN_CAUSE;
                         break; 
                  case   NWSTK_ROUTE_LNKSET_NOTFOUND:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_ROUTE_LNKSET_NOTFOUND:");
                         *resp_error_code = ROUTE_LNKSET_NOTFOUND;        
                         break; 
                  case   NWSTK_ROUTE_ADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_ROUTE_ADD_FAIL:");
                         *resp_error_code = ROUTE_ADD_FAIL;        
                         break; 
                  case   NWSTK_ROUTE_DEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_ROUTE_DEL_FAIL:   ");
                         *resp_error_code =  ROUTE_DEL_FAIL;       
                         break; 
                  case   NWSTK_DUPLICATE_ROUTE:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_DUPLICATE_ROUTE:");
                         *resp_error_code =   DUPLICATE_ROUTE;      
                         break; 
                  case   NWSTK_INVALID_ROUTE:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_INVALID_ROUTE:");
                         *resp_error_code =   INVALID_ROUTE;      
                         break; 
                  case   NWSTK_INVAILD_SSN:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_INVAILD_SSN:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_SSNADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SSNADD_FAIL:");
                         *resp_error_code =   UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SSNDEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SSNDEL_FAIL:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_SSN_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SSN_ALREADY_EXIST:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_INVAILD_BSCID:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_INVAILD_BSCID:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_BSSAPCFGADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_BSSAPCFGADD_FAIL:");
                         *resp_error_code =  UNKNOWN_CAUSE;        
                         break; 
                  case   NWSTK_BSSAPCFGDEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_BSSAPCFGDEL_FAIL:");
                         *resp_error_code =   UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_CFG_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_CFG_ALREADY_EXIST:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_BSSAPCICDEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_BSSAPCICDEL_FAIL:");
                         *resp_error_code =  CICDEL_FAIL;       
                         break; 
                  case   NWSTK_BSSAPCICADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_BSSAPCICADD_FAIL:");
                         *resp_error_code =  CICADD_FAIL;       
                         break; 
                  case   NWSTK_CIC_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_CIC_ALREADY_EXIST:");
                         *resp_error_code =  CIC_ALREADY_EXIST;       
                         break; 
                  case   NWSTK_GTTADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_GTTADD_FAIL:");
                         *resp_error_code =   GTTADD_FAIL;      
                         break; 
                  case   NWSTK_GTTREM_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_GTTREM_FAIL::");
                         *resp_error_code =  GTTREM_FAIL;       
                         break; 
                  case   NWSTK_GTTNOT_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_GTTNOT_EXIST::");
                         *resp_error_code =  GTTNOT_EXIST;       
                         break; 
                  case   NWSTK_GTTALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_GTTALREADY_EXIST:");
                         *resp_error_code =  GTTALREADY_EXIST;       
                         break; 
                  case   NWSTK_ACTLINK_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_ACTLINK_FAIL:");
                         *resp_error_code =  ACT_LINKSET_FAIL;       
                         break; 
                  case   NWSTK_DEACTLINK_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_DEACTLINK_FAIL:");
                         *resp_error_code =  DEACT_LINK_FAIL;        
                         break; 
                  case   NWSTK_LINKSET_ACT_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_LINKSET_ACT_FAIL:");
                         *resp_error_code = ACT_LINKSET_FAIL;        
                         break; 
                  case   NWSTK_DEACTLINKSET_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_DEACTLINKSET_FAIL:");
                         *resp_error_code = DEACT_LINKSET_FAIL;        
                         break; 
                  case   NWSTK_PEGS_NOTFOUND:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_PEGS_NOTFOUND:");
                         *resp_error_code =    PEGS_NOTFOUND;
                         break; 
                  case   NWSTK_WRONG_PARAM:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_WRONG_PARAM:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_BUILDHEAD_FAIL:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_BUILDHEAD_FAIL:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SCM_LINK_STATUS_NACK_RESP:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SCM_LINK_STATUS_NACK_RESP:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SCM_LINKSET_STATUS_NACK_RESP:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SCM_LINKSET_STATUS_NACK_RESP:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SCM_ROUTE_STATUS_NACK_RESP:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SCM_ROUTE_STATUS_NACK_RESP:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SCM_SSN_STATUS_NACK_RESP:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SCM_SSN_STATUS_NACK_RESP:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_SCM_ROUTE_ADMIN_STATE_NACK_RESP:
                          SCM_printf(SCM_MAJOR,"Cmd failure: cause:   NWSTK_SCM_ROUTE_ADMIN_STATE_NACK_RESP:");
                         *resp_error_code = UNKNOWN_CAUSE;      
                         break;
                 default: 
                          SCM_printf(SCM_MAJOR,"\nERROR ID UNKNOWN TO SCM:");
                         *resp_error_code = UNKNOWN_CAUSE;       
                         break; 
                }
                break;
/*AOIP: BSSAP ERROR CAUSE*/
           case APP_ID_BS:
              switch(error_code)
                     {  
                  case   NWSTK_INVAILD_BSCID:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_INVAILD_BSCID:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_BSSAPCFGADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_BSSAPCFGADD_FAIL:");
                         *resp_error_code =  UNKNOWN_CAUSE;        
                         break; 
                  case   NWSTK_BSSAPCFGDEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_BSSAPCFGDEL_FAIL:");
                         *resp_error_code =   UNKNOWN_CAUSE;      
                         break; 
                  case   NWSTK_CFG_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_CFG_ALREADY_EXIST:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                  case   NWSTK_BSSAPCICDEL_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_BSSAPCICDEL_FAIL:");
                         *resp_error_code =  CICDEL_FAIL;       
                         break; 
                  case   NWSTK_BSSAPCICADD_FAIL:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_BSSAPCICADD_FAIL:");
                         *resp_error_code =  CICADD_FAIL;       
                         break; 
                  case   NWSTK_CIC_ALREADY_EXIST:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   BSSAP_CIC_ALREADY_EXIST:");
                         *resp_error_code =  CIC_ALREADY_EXIST;       
                         break; 
                 default:
                         SCM_printf(SCM_MAJOR,"Cmd failure: cause:   UNKNOWN CAUSE BSSAP:");
                         *resp_error_code =  UNKNOWN_CAUSE;       
                         break; 
                            
                        }
                 break;

           case APP_ID_SIGTRAN:
              switch(error_code)
                     { 
                      
                default:
                        SCM_printf(SCM_MAJOR,"Cmd failure: UNKNOWN CAUSE SIGTRAN:");
                        *resp_error_code =  UNKNOWN_CAUSE;       
                        break; 
                     }
                 break;
            /*AOIP: END*/
}   
}
 
void  CheckIfPegRespFailed(U16* opcode, U16 error_code)
{
 switch(*opcode)
 {
  case SCM_OAM_MTP3_GENPEG_RESP:
  case SCM_OAM_LINK_PEG_RESP:
  case SCM_OAM_ROUTE_PEG_RESP:
  case SCM_OAM_SCCP_GENPEG_RESP:
  case SCM_OAM_LAPD_PEG_RESP:
  case SCM_OAM_MTP2_PEG_RESP:
       *opcode = SCM_OAM_PEG_NACK_RESP;
       return;
  default:
       return;  
 }  
}
void checkNoOfElementToReport(U32 entity, U32 *alarmElements, U32 *double_par, U32 alarmId)  
{
 switch(entity)
 {
  case MODULE_MTP3: 
   {   
     switch(alarmId)
     {
        case 2800:/*linkset code */    
        case 2801:    
        case 2423:    
        case 2466:    
             *alarmElements = 1;
             *double_par = ALARM_LS;
              break; 
     
        case 2509: /* linkset linkcode */   
        case 2526:    
        case 2403:    
        case 2404:    
        case 2505:    
        case 2506:    
        case 2507:    
        case 2508:    
        case 2510:    
        case 2511:    
        case 2512:    
        case 2513:    
        case 2514:    
        case 2516:    
        case 2528:    
             *alarmElements = 2;
             *double_par = ALARM_LS_LN;
              break; 
 
        case 2411:     
        case 2419:    
        case 2477:     
             /*dpc ni */  
             *alarmElements = 2;
             *double_par = ALARM_DPC_NI;
              break;  

 
        case 2412:/* dpc ni linkset */
        case 2415:    
        case 2416:
             *alarmElements = 3;
             *double_par = ALARM_DPC_NI_LS;
              break;  
    
       case 2900:/* no element only string*/
       case 2405:
       case 2407:
       case 2440:
       case 2487:
             *alarmElements = 0;
             *double_par = ALARM_NO_ELMNT;
             break; 
   
       case 2503:
       case 2489:
       case 2482:
       case 2459:
       case 2451:
       case 2448:
       case 2401:    
       case 2402:    
       case 2501:
            *alarmElements = 1;/* parse dpc */ 
            *double_par = ALARM_DPC;
            break; 
    
       case 2408:
            *alarmElements = 1;/* parse  user part */
             *double_par = ALARM_UP;
           break; 
    
       case 2406:/* msg type */
             *alarmElements = 1;
             *double_par = ALARM_MSGTYPE;
            break; 
   
       case 2504:/* dpc linkset linkcode */
            *alarmElements = 3;
             *double_par = ALARM_DPC_LS_LN;
            break;
     
       default:/* discard the alarm */ 
            *alarmElements = 0;
            *double_par = ALARM_DISCARDED;
            break; 
                 
            
            
     }
    break;
   }
  case MODULE_SCCP:
   {
    if((alarmId >= 443 && alarmId <= 448)||
       (alarmId >= 453 && alarmId <= 456)||
       (alarmId >= 500 && alarmId <= 501)||   
       (alarmId >= 506 && alarmId <= 507)||
       (alarmId == 648))
       { 
        /* here pc ssn */
         *alarmElements = 2;
          *double_par = ALARM_PC_SSN;
       } 
   else
    if((alarmId >= 670 && alarmId <= 686)||
       (alarmId >= 506 && alarmId <= 507))
     {
      /* here protocol class only*/
        *alarmElements = 1;
        *double_par = ALARM_PROTOCOL_CLS; 
     }
    else
     if((alarmId >= 436 && alarmId <= 438)) 
      {
      /* here PC only */ 
        *alarmElements = 1;
        *double_par = ALARM_DPC; 
      }
    else
     if((alarmId >= 634 && alarmId <= 637)||
        (alarmId == 449) )
     {
      /* MSG - TYPE */ 
        *alarmElements = 1;
        *double_par = ALARM_MSGTYPE; 
     } 
    else
     if(alarmId == 643)
      {
       /* PC - SSN - NI */
        *alarmElements = 3;
        *double_par = ALARM_DPC_SSN_NI; 
      
      } 
    else
     if(alarmId == 451)
      {
       /* SSN */
        *alarmElements = 1;
        *double_par = ALARM_SSN; 
      }  
    else
     if((alarmId >= 656 && alarmId <= 661)||
        (alarmId == 644))
     {
      /* NO ELEMENT */
      *alarmElements = 0;
      *double_par = ALARM_NO_ELMNT;
     }
    else 
     {
      *alarmElements = 0;
      *double_par = ALARM_DISCARDED;
     }
    break;
   }
  case MODULE_BSSAP:
   {
    switch(alarmId)
    { 
     case 5101:
     case 5102:
     case 5104:
     case 5130:
     case 5131:
     case 5132:
     case 5133:
     case 5134:
     case 5135:
     case 5136:
     case 5138:
          /* dpc cic */
          *alarmElements = 2;
          *double_par = ALARM_DPC_CIC;
          break;

     case 5117:
         /*dpc ssn */
          *alarmElements = 2;
          *double_par = ALARM_PC_SSN;
          break;

     case 5103:
     case 5115:
     case 5116:
     case 5118:
     case 5119:
     case 5120:
     case 5125:
     case 5127:
     case 5129:
          /* dpc */
          *alarmElements = 1;
          *double_par = ALARM_DPC;
          break;

     case 5105:
          /* No element */
          *alarmElements = 0;
          *double_par = ALARM_NO_ELMNT;
          break;
     
     default:
         /* discard the alarm */
          *alarmElements = 0;
          *double_par = ALARM_DISCARDED;
          break;
            
    
    }
   break;
  }
  case MODULE_MTP2:
         /* discard the alarm */
          *alarmElements = 0;
          *double_par = ALARM_DISCARDED;
          break;
       
}
  return;
} 
