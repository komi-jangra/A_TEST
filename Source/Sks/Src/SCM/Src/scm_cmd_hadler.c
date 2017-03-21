#include "scm_localhashdef.h"
#include "scm_encaps.h"

/*ScmOamTcapPegResponse         *oamTcapPegResponse = NULL;   */
ScmOamMtp3GenPegResponse      *oamMtp3GenPegResponse=NULL; 
ScmOamMtp2PegResponse         *oamMtp2PegResponse=NULL; 
ScmOamMtp3LinkPegResponse     *oamMtp3LinkPegResponse=NULL;
ScmOamMtp3RoutePegResponse    *oamMtp3RoutePegResponse=NULL;
ScmOamSccpGenPegResponse      *oamSccpGenPegResponse=NULL;
ScmOamBssapGenPegResponse     *oamBssapGenPegResponse=NULL;


ScmOamLinkStatusResponse      *oamLinkStatusResponse=NULL;
ScmOamLinkSetStatusResponse   *oamLinkSetStatusResponse=NULL;
ScmOamRouteStatusResponse     *oamRouteStatusResponse=NULL;
ScmOamSsnStatusResponse       *oamSsnStatusResponse=NULL;

NwStkConfigResp               *nwStkConfigResp=NULL;
NwstkScmMtp3GenPegResponse    *nwstkScmMtp3GenPegResponse=NULL;
NwstkScmMtp2PegResponse       *nwstkScmMtp2PegResponse=NULL;
NwstkScmMtp3LinkPegResponse   *nwstkScmMtp3LinkPegResponse=NULL;
NwstkScmMtp3RoutePegResponse  *nwstkScmMtp3RoutePegResponse=NULL;
NwstkScmSccpGenPegResponse    *nwstkScmSccpGenPegResponse=NULL;
NwstkScmBssapGenPegResponse   *nwstkScmBssapGenPegResponse=NULL;

ScmNwstkLinkStatus           *nwstkLinkStatus=NULL;
ScmNwstkLinkSetStatus        *nwstkLinkSetStatus=NULL; 
ScmNwstkRouteStatus          *nwstkRouteStatus=NULL;
ScmNwstkSsnStatus            *nwstkSsnStatus=NULL;


U8 tmr_nxt_cmd_flg = SS7_FALSE;
void process_resp_from_stack ( U8 *msg_buff,  U8* nxt_cmd_flg, int numbytes, int entity );


/**********************************************************************************/
/*this function command from oam & also fetch from db, call the respective command handler 
  function. This function is also return with a value for appropriate handler in main processing
  loop */
/**********************************************************************************/
int process_config_cmd_and_resp(U8 *handle_flag)
{
 U8 nxt_cmd_flg;
 U32 ret_val = 0;
 U16 resp_len;
 resp_len = sizeof(ScmOamResponse);
 strcpy(g_parameter.function_string, "process_config_cmd_and_resp()");
 /* here processing is for configuration */
 if(tmr_nxt_cmd_flg == SS7_FALSE)
 {
  process_event_on_sockfd( &nxt_cmd_flg );
 }
 else
 {
  tmr_nxt_cmd_flg = SS7_FALSE;
  nxt_cmd_flg = SS7_TRUE;
 }
 if ((g_parameter.config_flag == SS7_TRUE))
  {
   if((nxt_cmd_flg == SS7_TRUE) ||(g_parameter.config_cmd_resp == SS7_FALSE))
    {
     if(g_parameter.config_cmd_resp == SS7_FALSE)
      {
       ret_val = fetch_and_send_nxt_cmd_to_stack( g_parameter.entity_cfg );
       if(ret_val == 0)
         {
          check_entity_configured( g_parameter.entity_cfg );
          return HANDLE1;
         }
       else
        { 
         if(g_parameter.config_cmd_resp == SS7_FALSE)
         {
          ret_val = check_entity_configured( g_parameter.entity_cfg );
          if ( ret_val == 1 )
            return HANDLE3;
          else
           return HANDLE1; 
         }
        else
        return HANDLE1;
        }
      }
     else
      {
       /*waiting for resp of previous cmd */
       return HANDLE1;  
      } 
    } 
  } 
 else                                                                                       
  {
   /*configuration processing ends */
   /*processing when stack configured */
   if ((timer_info[TIMER_NWSTK].timer_strt_flag == 0 )  ||
       (timer_info[TIMER_CAP].timer_strt_flag == 0)    ||
       (timer_info[TIMER_SIGTRAN].timer_strt_flag == 0)||
       (timer_info[TIMER_MULTICMD].timer_strt_flag == 0)||
       (timer_info[TIMER_BSSAP].timer_strt_flag == 0))     /*ADDED FOR BSSAP*/ 
    { 
     return HANDLE3; 
    }
   else
    return HANDLE1; 
  }
 return HANDLE1;
}

/**********************************************************************************/
/*this function this fuction read the event on fds and dispatch the buffer to respective 
  handler function */
/**********************************************************************************/
void process_event_on_sockfd ( U8 *nxt_cmd_flg ) 
{
 U8 *msg_buff=NULL, alarm_entity, entity; /*AOIP entity*/
 U16 loop, resp_opcode, resp_len, opcode;
 resp_len = sizeof(ScmOamResponse);
 S32 fd,  event_onFd;
 int ret_val;
 struct timeval tv;
 fd_set read_fd, server_read_fd;
 tv.tv_sec  = 0;
 //tv.tv_usec = 200;
 tv.tv_usec = 10000;
 strcpy(g_parameter.function_string, "process_event_on_sockfd()");


 while(1)
  {
   FD_ZERO(&read_fd);
   read_fd = client_fd;
   event_onFd = select(FD_SETSIZE, &read_fd, SS7_NULL, SS7_NULL, &tv);
   if ( event_onFd <=0 )
    {
     //SCM_printf(SCM_INFO,"EVENT ON CLIENT FD's IS PROCESSED");
     break;
    }
   else
    {
     if ((xxx_client_sockfd[ENT_NWSTK_DBG] > 0 && FD_ISSET(xxx_client_sockfd[ENT_NWSTK_DBG], &read_fd)) > 0 )
      {
       msg_buff = scm_malloc(500 * sizeof(msg_buff));
       ret_val = scm_read_from_socket ( xxx_client_sockfd[ENT_NWSTK_DBG], msg_buff, 
                                        ENT_NWSTK_DBG, NULL);
       if( ret_val != 0)
        {  
         SCM_printf(SCM_MAJOR,"nwstk alarm received no. of byte to read for alarm payload: %d", ret_val);
         process_alarm_nwstk(msg_buff);
        }
       if(msg_buff != NULL)
        { 
         free(msg_buff);
         msg_buff = NULL;
        }
       continue;
      }
     else
     if ((xxx_client_sockfd[ENT_LAPD] > 0 && FD_ISSET(xxx_client_sockfd[ENT_LAPD], &read_fd)) > 0 )
      {
       msg_buff = scm_malloc(1500 * sizeof(msg_buff));
       ret_val = scm_read_from_socket ( xxx_client_sockfd[ENT_LAPD], msg_buff, 
                                        ENT_LAPD, NULL);
       if( ret_val != 0)
        {  
         SCM_printf(SCM_INFO,"Lapd socked bytes received : %d", ret_val);
         SCM_DUMP(0, ret_val, msg_buff, 15);
         process_lapdstk_response(msg_buff, nxt_cmd_flg);
        }
       if(msg_buff != NULL)
        { 
         free(msg_buff);
         msg_buff = NULL;
        }
       continue;
      }
       else
        if ((xxx_client_sockfd[ENT_NWSTK] > 0 && FD_ISSET(xxx_client_sockfd[ENT_NWSTK], &read_fd)) > 0)
         {
          msg_buff = scm_malloc(300 * sizeof(msg_buff));
          ret_val = scm_read_from_socket (xxx_client_sockfd[ENT_NWSTK], msg_buff, 
                                          ENT_NWSTK, NULL);
          if( ret_val > 0)
           {
            SCM_printf(SCM_INFO,"Cmd response from nwstk");
            SCM_DUMP(0, ret_val, msg_buff, 15);
            process_nwstk_resp(msg_buff, nxt_cmd_flg);
           } 
         if(msg_buff != NULL)
          { 
           free(msg_buff);
           msg_buff = NULL;
          }
          continue; 
         }     
        else
          if ((xxx_client_sockfd[ENT_OAM] > 0 && FD_ISSET(xxx_client_sockfd[ENT_OAM], &read_fd))>0)
             {
              if((check_if_previous_cmd_in_progress(APP_ID_NWSTK) != 0) || (check_if_previous_cmd_in_progress(APP_ID_LAPD)||
                  ((check_if_previous_cmd_in_progress(APP_ID_SIGTRAN) != 0) && (g_parameter.noOam_resp_flag == 0)) || 
                  (check_if_previous_cmd_in_progress(APP_ID_BS) != 0))) /*AOIP: LINE ADDED*/
              {
               SCM_printf(SCM_INFO,"Previous stack command in progress, process oam command later");
               break; 
              }
              msg_buff = scm_malloc(200 * sizeof(msg_buff));
              ret_val = scm_read_from_socket (xxx_client_sockfd[ENT_OAM], msg_buff, ENT_OAM, NULL);
              if( ret_val != 0)
               {
                if(g_parameter.config_flag == SS7_TRUE)
                 {
                  SCM_printf(SCM_MAJOR,"OAM MSG DISCARDED BY SCM: 'STACK GETTING CONFIGURED'");
                  opcode = ((ScmHdr *)msg_buff)->opcode;
                  match_resp_opcode(opcode,  &resp_opcode);
                  send_resp_to_oam(  resp_opcode, ((ScmHdr *)msg_buff)->operation, ((ScmHdr *)msg_buff)->trid , 
                                    ((ScmHdr *)msg_buff)->spare, ERROR_STAK_GETTING_CONFIG, 
                                    NULL, resp_len , APP_ID_OAM);
                 }
                else
                 {
                  SCM_printf(SCM_MAJOR,"Cmd buffer received from OAM :");
                  SCM_DUMP(0, ret_val, msg_buff, 15);
                  if(g_parameter.noOam_resp_flag == 1)
                   {
                     /*save command (rare hit scenario)*/
                     SCM_printf(SCM_DEBUG,"SIGTRAN OAM msg Stored as admin cmd alrdy sent to STACK\n");
                     g_parameter.map_tcap_msg = scm_malloc(sizeof(OamScmM3uaLocalAspAdminConfig));
                     memcpy(g_parameter.map_tcap_msg, msg_buff, sizeof(OamScmM3uaLocalAspAdminConfig));
                   }
                  else
                     process_oam_message(msg_buff);
                 }
              }   
                if(msg_buff != NULL)
                 { 
                  free(msg_buff);
                  msg_buff = NULL;
                 }
                continue;
            }
       else /*AOIP: NEW ELSE IF ADDED BSSAP*/
         if ((xxx_client_sockfd[ENT_BSSAP] > 0 && FD_ISSET(xxx_client_sockfd[ENT_BSSAP], &read_fd)) > 0)
            {
             msg_buff = scm_malloc(300 * sizeof(msg_buff));
             memset(msg_buff, 0, 300); /*memset after error_code issue at SCM*/
             ret_val = scm_read_from_socket (xxx_client_sockfd[ENT_BSSAP], msg_buff,
                                          ENT_BSSAP, &entity); /*bug fixed*/
             if( ret_val > 0)
               {
                 SCM_printf(SCM_INFO,"Cmd response from bssap\n");
                 SCM_DUMP(0, ret_val, msg_buff, 15);
                 process_bssap_stack_resp(msg_buff, nxt_cmd_flg);
               }
             if(msg_buff != NULL)
               {
                 free(msg_buff);
                 msg_buff = NULL;
               }
            continue;
            } 
       /*AOIP: END*/
       else/* event on isup, map, tcap, cap client fd's */ 
            {
              
             if ((xxx_client_sockfd[ENT_PEER_SCM] > 0 && FD_ISSET(xxx_client_sockfd[ENT_PEER_SCM], &read_fd))>0)
              {
               SCM_printf(SCM_CRITICAL,"ENTITY MARKED DOWN PEER SCM");
               SCM_printf(SCM_CRITICAL,"RESET GLOBAL FLAGS\n");
               close(xxx_client_sockfd[ENT_PEER_SCM]);
               FD_CLR(xxx_client_sockfd[ENT_PEER_SCM], &read_fd);     
               FD_CLR(xxx_client_sockfd[ENT_PEER_SCM], &client_fd);     
               xxx_client_sockfd[ENT_PEER_SCM] = -1;
               /*AOIP_HA*/
               /*Reset flag on peer DISCONNECT*/
               g_parameter.noOam_resp_flag             = 0; /*if self generated admin to peer was sent*/
               g_parameter.peer_stack_up               = 0; 
               g_parameter.data_pull_up                = 0; 
               g_parameter.nwstk_cfgIndFromPeerCard    = 0;
               g_parameter.nwstk_stsUp_sent            = 0; 
               g_parameter.data_pull_admin_send        = 0;
               /*AOIP_HA end*/
               /*MANTIS ID:-0032492 */
               g_parameter.scm_scm_up = 0;
               g_parameter.stby_bssap_config_wait   = 0;
               g_parameter.stby_sigtran_config_wait = 0;
               /*MANTIS END*/
              }
            else
             if ((xxx_client_sockfd[ENT_SIGTRAN] > 0 && FD_ISSET(xxx_client_sockfd[ENT_SIGTRAN], &read_fd))>0)
              {
               SCM_printf(SCM_CRITICAL,"ENTITY MARKED DOWN SIGTRAN\n"); /*AOIP: PRINT MODIFIED*/
               g_parameter.sigtran_cfgComplete = 0;
               close(xxx_client_sockfd[ENT_SIGTRAN]);
               FD_CLR(xxx_client_sockfd[ENT_SIGTRAN], &read_fd);     
               FD_CLR(xxx_client_sockfd[ENT_SIGTRAN], &client_fd);     
               xxx_client_sockfd[ENT_SIGTRAN] = -1;
              /*AOIP_HA*/
               send_stack_enity_up_to_peerscm(ENT_SIGTRAN);
               g_parameter.self_stack_up = 0;
              /*AOIP_HA end*/
               process_scm_alarm(SS7_DOWN);
              } 
              else
               { 
                SCM_printf(SCM_CRITICAL,"SCM LOGICAL ERROR");
                return ;
               }
            }    
    }
  }
 /*read from scm server connection fds*/
 while(1)
  {
   FD_ZERO(&server_read_fd);
   server_read_fd = server_fds;
   event_onFd = 0;
   event_onFd = select(FD_SETSIZE, &server_read_fd, SS7_NULL, SS7_NULL, &tv);
   if(event_onFd <= 0 )
    {
     //SCM_printf(SCM_INFO," EVENT ON SERVER FD's PROCESSED");
     return ;
    }
   else
    {
     if ((xxx_severread_sockfd[0] > 0) || (xxx_severread_sockfd[1] > 0)||
          (xxx_severread_sockfd[2] > 0) ||(xxx_severread_sockfd[3] > 0) )
      {
       for(loop=0;loop<=10;loop++)
         {
          if((xxx_severread_sockfd[loop] > 0 && FD_ISSET(xxx_severread_sockfd[loop], &server_read_fd))> 0)
            {
             fd = xxx_severread_sockfd[loop];
             break;     
            }  
         }
       msg_buff = scm_malloc(400 * sizeof(U8));
    
       ret_val = scm_read_from_socket (fd, msg_buff, FROM_IMTCS, &entity);
       
       /*AOIP: PRINTS CHANGED*/
       if(ret_val > 0) 
        {
            if(entity == APP_ID_PEER_SCM)
             {
                   SCM_printf(SCM_INFO,"Received from PEER SCM: App_id[%d] Operation[%d] Opcode[%d] Tr_id[%d] len[%d]\n", 
                                 ((ScmHdr*)msg_buff)->appid, ((ScmHdr*)msg_buff)->operation, ((ScmHdr*)msg_buff)->opcode, 
                                 ((ScmHdr*)msg_buff)->trid, ((ScmHdr*)msg_buff)->len);
             }
           else 
            if(entity == FROM_MTI)
              { 
                   SCM_printf(SCM_INFO,"Received from STACK: App_id[%d] version[%d] noe[%d] len_lsb[%d] len_msb[%d] entity[%d]\n", 
                                      msg_buff[0], msg_buff[1], msg_buff[2],msg_buff[3], msg_buff[4], entity);

                 
                   if((msg_buff[0] == SCCP_SM_RESPONSE_API)||(msg_buff[0] == M3UA_SM_RESPONSE_API) ||
                                                             (msg_buff[0] == SCTP_SM_RESPONSE_API))
                      {
                             entity = APP_ID_SIGTRAN;
                      }
                   else
                      {
                             SCM_printf(SCM_INFO,"UNKNOWN APP_ID IN RESP@#@#@#@#\n");    
                      }
                
              }
            else  /*ALARM_IMPL*/
              if(entity == SIGTRAN_ALARM)
               {
                   /*SCM_printf(SCM_INFO,"Received from STACK: App_id[%d] version[%d] noe[%d] len_lsb[%d] len_msb[%d] entity[%d]\n", 
                                      msg_buff[0], msg_buff[1], msg_buff[2],msg_buff[3], msg_buff[4], entity);*/
               }
            else
              {
                   SCM_printf(SCM_INFO,"Reading clients UNknown entity\n"); 
                   if(msg_buff != NULL)
                     {
                         free(msg_buff);
                         msg_buff = NULL;
                     }
                   return 0; /*breaking loop*/
              }
        }
      else
        { 
         if(msg_buff != NULL)
          {
            free(msg_buff);
            msg_buff = NULL;
          }
           continue;
        }       
       /*AOIP: END*/
       
       if( ret_val != 0)
        {
        /* if (entity == FROM_MTI)
          {
           switch(msg_buff[0])
              { 
                case APP_ID_IMTC_ALARM:    
                     entity = ISMAP_TCAP_ALARM;  
                     break;
                case 163:
                case 164:
                     entity = APP_ID_ISUP;
                     break;
                case 242:
                case 234:
                case 233:
                case RESP_SIGTRAN_M3UA_API:
                     entity = APP_ID_MAP;
                     break;
                case 98:
                     break;
             }
           }*/
  
         switch(entity)
           {
            case APP_ID_SIGTRAN:
            case APP_ID_MAP:
            case APP_ID_ISUP:
                 SCM_DUMP(0, ret_val, msg_buff, 15);
                 /*Function below commented & "process_resp_from_sigtran_stack" function
                   is the Alternate function */
                /* process_resp_from_stack ( msg_buff, nxt_cmd_flg, ret_val, entity ); */
                 if( timer_info[TIMER_SIGTRAN].timer_strt_flag == 1)
                  {
                     process_resp_from_sigtran_stack(msg_buff, nxt_cmd_flg, ret_val, entity);  
                  }
                 else
                  {
                     SCM_printf(SCM_INFO,"Timer not running for Command\n");        /*Discard responses when no timer running*/ 
                  }
                 break;
            case SIGTRAN_ALARM:
                 entity = msg_buff [5]; /* MODULE ID = 5 for sigtran */
                 switch (entity)
                  {
                   case 3:
                      alarm_entity = APP_ID_ISUP;
                      break;
                   case 0:
                   case 1:
                      alarm_entity = APP_ID_MAP;
                      break;
                   case 5:
                      alarm_entity = APP_ID_SIGTRAN;
                      break;

                   default:
                      SCM_printf(SCM_INFO,"UNKNOWN ENTITY#@#@#@#@#@\n");
                      break;
                  }
                 process_sigtran_stack_alarm(ret_val, msg_buff, alarm_entity);
                 break; 
            case APP_ID_PEER_SCM:
                 SCM_printf(SCM_INFO,"Buffer length read from socket: %d\n", ret_val); /*AOIP PRINT UPDATE*/
                 SCM_DUMP(0, ret_val, msg_buff, 15);
                 process_peerscm_message(msg_buff);  
                 break;

            default:
                 SCM_printf(SCM_CRITICAL,"DECODING ERROR FOR DATA RECEIVED AT SCM SERVER SOCK");
                 break;
           }
        }
       else
        {
         FD_CLR(fd, &server_read_fd); 
        }   
       if(msg_buff != NULL)
         { 
          free(msg_buff);
          msg_buff = NULL;
         }
       continue;
      }
     else 
     SCM_printf(SCM_CRITICAL,"WRONG EVENT ON FD");
     return ;    
    }
  }
}

/*********************************************************************************/
/* This funtion decodes the response from nwstk and send response to oam if oamstamp
   is true, also send nwstk alarms to o&m*/
/*********************************************************************************/
void process_nwstk_resp(U8* msg_buff, U8* nxt_cmd_flg)
{
 U8 *peg_resp_buff = NULL, cardFlag, *msg_buf=NULL;
 U32 error_code, PEG_FLAG = SS7_FALSE, Length , oam_tr_id;
 S32 ret_val;
 U16  resp_error_code =0, pegrfu;
 U8 opcode, transaction_id, operation;
 U16  resp_opcode, tr_opcode;
 OamScmLinkAdminState   ScmLinkAdminState;
 OamScmLinkSetAdminState ScmLinkSetAdminState;
 Length = sizeof(ScmOamResponse);
 nwStkConfigResp = (NwStkConfigResp*)msg_buff;
 opcode = nwStkConfigResp->nwstkhdr.opcode;
 resp_opcode = 0;
 tr_opcode = timer_info[TIMER_NWSTK].opcode - BASE_OPCODE_SCM; 
 transaction_id = nwStkConfigResp->nwstkhdr.trid;
 error_code = nwStkConfigResp->erro_code;
 strcpy(g_parameter.function_string, "process_nwstk_resp()");
 

 if(transaction_id == transaction_Id[MULTI_CMD]) 
   {
    process_multicmd_resp(msg_buff, nxt_cmd_flg);
    return ;
   }
 
 SCM_printf(SCM_MAJOR,"OPCODE RECV SIGTRAN %d\n", opcode);
 /* handling for init garbase response */
  if(tr_opcode > OPCODEMAX)
  {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
           return ;
  }
 /*end here*/
 switch(opcode)
   {
    case NWSTK_SCM_MTP3_GENCFG_RESP:
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'MTP3_SKS_GEN_CFG_RESP' *****");
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP3_GENCFG])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         break;
         
    case NWSTK_SCM_SCCP_GENCFG_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_GENCFG])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'SCCP_SKS_GEN_CFG_RESP' *****");
         break;
    
     case NWSTK_SCM_BSSAP_GENCFG_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_BSSAP_GENCFG])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"BSSAP - > SCM 'BSSAP_SKS_GEN_CFG_RESP' *****");
         break;


    case NWSTK_SCM_LINK_STATUS_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINK_STATUS_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1)) 
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LN_STATUS_GET_RESP' ");
         peg_resp_buff = (U8*)scm_malloc(100*sizeof(char));
         resp_opcode = SCM_OAM_LINK_STATUS_RESP;
         Length = sizeof(ScmOamLinkStatusResponse);
         nwstkLinkStatus = (ScmNwstkLinkStatus*)msg_buff;
         oamLinkStatusResponse = (ScmOamLinkStatusResponse*)scm_malloc(sizeof(ScmOamLinkStatusResponse));
         oamLinkStatusResponse->linkId = nwstkLinkStatus->linkId;
         oamLinkStatusResponse->linkSetId = nwstkLinkStatus->linkSetId;
         oamLinkStatusResponse->status = nwstkLinkStatus->status;
         memcpy(peg_resp_buff, oamLinkStatusResponse, Length); 
         free(oamLinkStatusResponse); 
         oamLinkStatusResponse =NULL;
         PEG_FLAG = SS7_TRUE;
         break;
         

    case NWSTK_SCM_LINKSET_STATUS_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINKSET_STATUS_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1)) 
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LS_STATUS_GET_RESP' ");
         peg_resp_buff = (U8*)scm_malloc(100*sizeof(char));
         resp_opcode = SCM_OAM_LINKSET_STATUS_RESP;
         Length = sizeof(ScmOamLinkSetStatusResponse);
         nwstkLinkSetStatus = (ScmNwstkLinkSetStatus*)msg_buff;
         oamLinkSetStatusResponse = (ScmOamLinkSetStatusResponse*)scm_malloc(sizeof(ScmOamLinkSetStatusResponse));
         oamLinkSetStatusResponse->linkSetId = nwstkLinkSetStatus->linkSetId;
         oamLinkSetStatusResponse->status = nwstkLinkSetStatus->status;
         memcpy(peg_resp_buff, oamLinkSetStatusResponse, Length); 
         free(oamLinkSetStatusResponse); 
         oamLinkSetStatusResponse = NULL;
         PEG_FLAG = SS7_TRUE;
         break; 
    case NWSTK_SCM_ROUTE_STATUS_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_ROUTE_STATUS_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1)) 
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'ROUTE_STATUS_GET_RESP' ");
         peg_resp_buff = (U8*)scm_malloc(200*sizeof(char));
         resp_opcode = SCM_OAM_ROUTE_STATUS_RESP;
         Length = sizeof(ScmOamRouteStatusResponse);
         nwstkRouteStatus = (ScmNwstkRouteStatus*)msg_buff;
         oamRouteStatusResponse = (ScmOamRouteStatusResponse*)scm_malloc(sizeof(ScmOamRouteStatusResponse));
         oamRouteStatusResponse->destinationPointCode = nwstkRouteStatus->destinationPointCode;
         oamRouteStatusResponse->networkIndicator = nwstkRouteStatus->networkIndicator;
         oamRouteStatusResponse->status = nwstkRouteStatus->status;
         memcpy(peg_resp_buff, oamRouteStatusResponse, Length); 
         free(oamRouteStatusResponse); 
         oamRouteStatusResponse=NULL;
         PEG_FLAG = SS7_TRUE;
         break; 
            
    case NWSTK_SCM_SSN_STATUS_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SSN_STATUS_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1)) 
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'SSN_STATUS_GET_RESP' ");
         peg_resp_buff = (U8*)scm_malloc(200*sizeof(char));
         resp_opcode = SCM_OAM_SSN_STATUS_RESP;
         Length = sizeof(ScmOamSsnStatusResponse);
         nwstkSsnStatus = (ScmNwstkSsnStatus*)msg_buff;
         oamSsnStatusResponse = (ScmOamSsnStatusResponse*)scm_malloc(sizeof(ScmOamSsnStatusResponse));
         oamSsnStatusResponse->destinationPointCode = nwstkSsnStatus->destinationPointCode;
         oamSsnStatusResponse->networkIndicator = nwstkSsnStatus->networkIndicator;
         oamSsnStatusResponse->ssn = nwstkSsnStatus->ssn;
         oamSsnStatusResponse->status = nwstkSsnStatus->status;
         memcpy(peg_resp_buff, oamSsnStatusResponse, Length); 
         free(oamSsnStatusResponse);
         oamSsnStatusResponse=NULL; 
         break; 
            
            
    case NWSTK_SCM_MTP3_TIMER_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP3_TIMER_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1)) 
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
        else
         resp_opcode = SCM_OAM_MTP3_TIMER_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'TIMER_MODIFY_RESP' *****");
         break; 
            
    case NWSTK_SCM_SCCP_TIMER_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_TIMER_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_SCCP_TIMER_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'TIMER_MODIFY_RESP' *****");
         break;
    case NWSTK_SCM_BSSAP_TIMER_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_BSSAP_TIMER_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_BSSAP_TIMER_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"BSSAP - > SCM 'TIMER_MODIFY_RESP' *****");
         break;
 
    case NWSTK_SCM_SCCP_LSSN_ADD_RESP:
    case NWSTK_SCM_SCCP_LSSN_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_LSSN_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'LSSN_CONFIG_RESP' *****");
          break;
   case NWSTK_SCM_SCCP_SET_BEHAV_RESP:
        if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_SET_BEHAV])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
          else
         resp_opcode = NWSTK_SCM_SCCP_SET_BEHAV_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'BEHAVIOR_CONFIG_RESP' *****");
          break;
          

    case NWSTK_SCM_BSSAP_CIC_ADD_RESP:
    case NWSTK_SCM_BSSAP_CIC_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_BSSAP_CIC_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         resp_opcode = SCM_OAM_TRUNK_CIC_CONFIG_RESP;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"BSSAP - > SCM 'A_INTF_CIC_CONFIG_RESP' *****");
         break;


    case NWSTK_SCM_BSSAP_CFG_ADD_RESP:
    case NWSTK_SCM_BSSAP_CFG_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_BSSAP_CFG_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         resp_opcode = SCM_OAM_INTERFACE_CONFIG_RESP;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"BSSAP - > SCM 'BSCID_CONFIG_RESP' *****");
         break;


    case NWSTK_SCM_LINKSET_ADD_RESP:
    case NWSTK_SCM_LINKSET_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINKSET_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_LINKSET_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         if(error_code == 0)
          {
           switch(opcode)
           {
            case NWSTK_SCM_LINKSET_ADD_RESP:
                 checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, g_parameter.linksetId,
                                                           0);
                 break;
            case NWSTK_SCM_LINKSET_DEL_RESP: 
                 checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, g_parameter.linksetId,
                                                           0);
                 break;
                    
           }
          }
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LS_CONFIG_RESP' *****");
         break;


    case NWSTK_SCM_LINKSET_ADMIN_STATE_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_LINKSET_ADMIN_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LS_ADMIN_CONFIG_RESP' *****");
         if(error_code == 0)
          {
            ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_MODIFY, g_parameter.linksetId, g_parameter.linkset_admingSts);
           if(ret_val <= 0)
            {
             SCM_printf(SCM_CRITICAL," LINKSET ADMIN STATE UPDATION IN SCM HASH TABLE IS FAILED");
            }
           if(xxx_client_sockfd[ENT_PEER_SCM] > 0 && (g_parameter.redundant_status == SCM_ACTIVE)
             && (g_parameter.nwstk_cfgIndFromPeerCard  ==  1))
               {
                 msg_buf = malloc(sizeof(OamScmLinkSetAdminState));
                 ScmLinkSetAdminState.linkSetId = g_parameter.linksetId;
                 ScmLinkSetAdminState.adminState = g_parameter.linkset_admingSts;
                 memcpy(msg_buf, &ScmLinkSetAdminState, sizeof(OamScmLinkSetAdminState)); 
                  
                ((ScmHdr*)msg_buf)->opcode =  SCM_NWSTK_LINKSET_ADMIN_STATE_MODIFY;
                ((ScmHdr*)msg_buf)->appid  = APP_ID_PEER_SCM;
                ((ScmHdr*)msg_buf)->len  = sizeof(OamScmLinkSetAdminState);
                ret_val = scm_dispatch_buffer(msg_buf, APP_ID_PEER_SCM, sizeof(OamScmLinkSetAdminState));
                free(msg_buf);
                msg_buf=NULL; 
               }
          }
         break;

    case NWSTK_SCM_LINK_ADD_RESP:
    case NWSTK_SCM_LINK_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINK_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_LINK_CONFIG_RESP;
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LN_CONFIG_RESP' *****");
         if(error_code == 0)
          {
           switch(opcode)
           {
            case NWSTK_SCM_LINK_ADD_RESP:
                 checkAndUpdate_linkValue_in_linkHashTable(SCM_ADD,  g_linkConfigValue.instaceId,
                                                           g_linkConfigValue.link_value,
                                                           g_linkConfigValue.linkSetId,
                                                           &cardFlag, 0);
                 break;
            case NWSTK_SCM_LINK_DEL_RESP:
                   
                  checkAndUpdate_linkValue_in_linkHashTable(SCM_DELETE,  g_linkConfigValue.instaceId,
                                                           g_linkConfigValue.link_value,
                                                           g_linkConfigValue.linkSetId,
                                                           &cardFlag, 0);
                  if(g_parameter.peer_link_del == 1)  
                  {     
                   g_parameter.peer_link_del =0; 
                   g_parameter.peer_nwstk_cmdFlag = 0;
                   stop_timer(TIMER_NWSTK);
                   free(g_parameter.nwstk_msg) ;
                   g_parameter.nwstk_msg = NULL;
                  }
                 break;
                    
           }
          }
         else
          if((g_parameter.peer_link_del == 1) && (g_roll_back_flag.nwstk_roll_back_flag == 0))
           {
             handle_ln_del_resp(error_code);
           }
         break;

    case NWSTK_SCM_LINK_ADMIN_STATE_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_LINK_ADMIN_STATE_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_LINK_ADMIN_CONFIG_RESP;
         stop_timer(TIMER_NWSTK);
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'LN_ADMIN_CONFIG_RESP' *****");
          if(error_code == 0)
          {
            ret_val = checkAndUpdate_linkValue_in_linkHashTable(SCM_MODIFY,  0,
                                                 g_linkConfigValue.link_value,
                                                 g_linkConfigValue.linkSetId,
                                                 &g_linkConfigValue.card_flag, 
                                                 g_linkConfigValue.admin_state);
           if(ret_val == 0)
            {
             SCM_printf(SCM_CRITICAL," LINK ADMIN STATE UPDATION IN SCM HASH TABLE IS FAILED");
            }
           if((xxx_client_sockfd[ENT_PEER_SCM] > 0) && (g_parameter.redundant_status == SCM_ACTIVE) &&
              (g_parameter.nwstk_cfgIndFromPeerCard  ==  1))
               {
                msg_buf = malloc(sizeof(OamScmLinkAdminState));
                //ScmLinkAdminState.linkId    = g_linkConfigValue.link_value; 
                //ScmLinkAdminState.linkSetId = g_linkConfigValue.linkSetId; 
                //ScmLinkAdminState.adminState= g_linkConfigValue.admin_state; 
                memcpy(&ScmLinkAdminState, &g_linkConfigValue.scmLinkAdminState, sizeof(OamScmLinkAdminState));
                memcpy(msg_buf, &ScmLinkAdminState, sizeof(OamScmLinkAdminState));  
                ((ScmHdr*)msg_buf)->opcode =  SCM_NWSTK_LINK_ADMIN_STATE_MODIFY;
                ((ScmHdr*)msg_buf)->appid  = APP_ID_PEER_SCM;
                ((ScmHdr*)msg_buf)->len  = sizeof(OamScmLinkAdminState);
                ret_val = scm_dispatch_buffer(msg_buf, APP_ID_PEER_SCM, sizeof(OamScmLinkAdminState));
                free(msg_buf);
                msg_buf=NULL;   
               }

          }
         break;


    case NWSTK_SCM_SS7ROUTE_ADD_RESP:
    case NWSTK_SCM_SS7ROUTE_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SS7ROUTE_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
          resp_opcode = SCM_OAM_SS7ROUTE_CONFIG_RESP;
          if( timer_info[TIMER_NWSTK].no_of_resp == 2)
          {
           SCM_printf(SCM_INFO,"Route config cmd resp: with ssttest on ");
           if((timer_info[TIMER_NWSTK].resp_error_id != 0) && (error_code == 0))
           {
            error_code = timer_info[TIMER_NWSTK].resp_error_id;  
           }   
          }
          else
          {
           timer_info[TIMER_NWSTK].resp_error_id = error_code;  
          }  
          SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'ROUTE_CONFIG_RESP' *****");
          stop_timer(TIMER_NWSTK);
          break;

    case NWSTK_SCM_SCCP_RSSN_ADD_RESP:
    case NWSTK_SCM__SCCP_RSSN_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_RSSN_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_INFO,"rssn config cmd response from nwstk");
         break;

    case NWSTK_SCM_SCCP_CSSN_ADD_RESP:
    case NWSTK_SCM_SCCP_CSSN_DEL_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_CSSN_ADD])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         if(timer_info[TIMER_NWSTK].no_of_resp == 2)
          {
           SCM_printf(SCM_INFO,"Cssn config cmd response for sstTeston flag");
           timer_info[TIMER_NWSTK].resp_error_id = error_code;
           return ;
          }  
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'CSSN_CONFIG_RESP' *****");
         break;

    case NWSTK_SCM_SS7ROUTE_ADMIN_STATE_MODIFY_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SS7ROUTE_ADMIN_STATE_MODIFY])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         resp_opcode = SCM_OAM_SS7ROUTE_ADMIN_CONFIG_RESP;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'ROUTE_ADMIN_CONFIG_RESP' *****");
         break;


    case NWSTK_SCM_MTP2_PEG_RESP:
    case NWSTK_SCM_MTP2P_PEG_NACK_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP2_PEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         switch(opcode)
          {
           case NWSTK_SCM_MTP2_PEG_RESP:
               SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'SCM_NWSTK_MTP2_PEG_GET Resp' ");
               peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
               resp_opcode = SCM_OAM_MTP2_PEG_RESP;
               Length = sizeof(ScmOamMtp2PegResponse);
               nwstkScmMtp2PegResponse = (NwstkScmMtp2PegResponse*)msg_buff;
               oamMtp2PegResponse = (ScmOamMtp2PegResponse*)scm_malloc(sizeof(ScmOamMtp2PegResponse));
              #define RESP(A,C) \
                    oamMtp2PegResponse->A = nwstkScmMtp2PegResponse->C;\
                    //SCM_printf(SCM_INFO,"oamMtp2PegResponse->A %d", oamMtp2PegResponse->A); 
               RESP(linkId, linkId); 
               RESP(linkSetId, linkSetId); 
               RESP(mtp2PegsLinkFailAbnBSNR, mtp2PegsLinkFailAbnBSNR); 
               RESP(mtp2PegsLinkFailAbnFIBR, mtp2PegsLinkFailAbnFIBR); 
               RESP(mtp2PegsLinkFailT7Exp, mtp2PegsLinkFailT7Exp); 
               RESP(mtp2PegsLinkFailSUERM, mtp2PegsLinkFailSUERM); 
               RESP(mtp2PegsLinkFailCongetion, mtp2PegsLinkFailCongetion); 
               RESP(mtp2PegsLinkAlgnmntFailT2T3, mtp2PegsLinkAlgnmntFailT2T3); 
               RESP(mtp2PegsLinkAlgnmntFailAERM, mtp2PegsLinkAlgnmntFailAERM); 
               RESP(mtp2PegsNumOfNegativeAck, mtp2PegsNumOfNegativeAck); 
               RESP(mtp2PegsNumOfSUsErr, mtp2PegsNumOfSUsErr); 
               RESP(mtp2PegsSIBTx, mtp2PegsSIBTx); 
               RESP(mtp2PegsSIBRx, mtp2PegsSIBRx); 
               RESP(mtp2PegsN1RetransTx, mtp2PegsN1RetransTx); 
               RESP(mtp2PegsN2RetransTx, mtp2PegsN2RetransTx); 
               RESP(mtp2PegsMSURetransTx, mtp2PegsMSURetransTx); 
               RESP(mtp2PegsMSURetransOctTx, mtp2PegsMSURetransOctTx); 
               RESP(mtp2PegsNoOfMSURxFromMtp3, mtp2PegsNoOfMSURxFromMtp3); 
               RESP(mtp2PegsNoOfMSUTxToMtp3, mtp2PegsNoOfMSUTxToMtp3); 
               RESP(mtp2PegsNoOfMSURxFromMCC, mtp2PegsNoOfMSURxFromMCC); 
               RESP(mtp2PegsNoOfMSUTxToMCC, mtp2PegsNoOfMSUTxToMCC); 
               RESP(mtp2PegsNoOfMSUTxToMCC, mtp2PegsNoOfMSUTxToMCC); 
               RESP(mtp2PegsNoOfMSUOctTxToMCC, mtp2PegsNoOfMSUOctTxToMCC); 
               RESP(mtp2PegsNoOfMSUOctTxToMCC, mtp2PegsNoOfMSUOctTxToMCC); 
               RESP(mtp2PegsNoOfMSUOctRxFromMCC, mtp2PegsNoOfMSUOctRxFromMCC); 
               RESP(mtp2PegsRQThresCross, mtp2PegsRQThresCross); 
               RESP(mtp2PegsTQThresCross, mtp2PegsTQThresCross); 
               RESP(mtp2PegsTBThresCross, mtp2PegsTBThresCross); 
               RESP(mtp2PegsRTBThresCross, mtp2PegsRTBThresCross); 

               memcpy(peg_resp_buff, oamMtp2PegResponse, Length); 
               free(oamMtp2PegResponse);
               oamMtp2PegResponse=NULL;  
               #undef RESP
               PEG_FLAG = SS7_TRUE;
               break;
           case NWSTK_SCM_MTP2P_PEG_NACK_RESP:
                SCM_printf(SCM_MAJOR,"Link peg cmd response : cmd failure");
                resp_opcode = SCM_OAM_MTP2_PEG_RESP;
                PEG_FLAG = SS7_FALSE;
                break;
              } 
               break;

    case NWSTK_SCM_MTP3_GENPEG_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP3_GENPEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         timer_info[TIMER_NWSTK].resp_error_id = error_code;
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'MTP3_GEN_PEG_GET_RESP' *****");
         peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
         resp_opcode = SCM_OAM_MTP3_GENPEG_RESP;
         Length = sizeof(ScmOamMtp3GenPegResponse);
         nwstkScmMtp3GenPegResponse = (NwstkScmMtp3GenPegResponse*)msg_buff;
         oamMtp3GenPegResponse = (ScmOamMtp3GenPegResponse*)scm_malloc(sizeof(ScmOamMtp3GenPegResponse));
         #define RESP(A,C) \
                    oamMtp3GenPegResponse->A = nwstkScmMtp3GenPegResponse->C;\
                    //SCM_printf(SCM_INFO,"oamMtp3GenPegResponse->A %d", oamMtp3GenPegResponse->A); 
         RESP(mtp3GenPegsMSGPAUSE, mtp3GenPegsMSGPAUSE); 
         RESP(mtp3GenPegsMSGRESUME, mtp3GenPegsMSGRESUME); 
         RESP(mtp3GenPegsMSGSTATUS, mtp3GenPegsMSGSTATUS); 
         RESP(mtp3GenPegsMSGRECEIVEDINERROR, mtp3GenPegsMSGRECEIVEDINERROR); 
         RESP(mtp3GenPegsCHANGEOVER, mtp3GenPegsCHANGEOVER); 
         RESP(mtp3GenPegsCHANGEBACK, mtp3GenPegsCHANGEBACK); 
         RESP(mtp3GenPegsSLUNAVAILABLE, mtp3GenPegsSLUNAVAILABLE); 
         RESP(mtp3GenPegsLINKINHIBIT, mtp3GenPegsLINKINHIBIT); 
         RESP(mtp3GenPegsLINKUNINHIBIT, mtp3GenPegsLINKUNINHIBIT); 
         RESP(mtp3GenPegsLINKFORCEUNINHIBIT, mtp3GenPegsLINKFORCEUNINHIBIT); 
         RESP(mtp3GenPegsCONGESTION, mtp3GenPegsCONGESTION); 
         RESP(mtp3GenPegsSLSUNAVAILABLE, mtp3GenPegsSLSUNAVAILABLE); 
         RESP(mtp3GenPegsTFCRECEIVED, mtp3GenPegsTFCRECEIVED); 
         RESP(mtp3GenPegsTFARECEIVED, mtp3GenPegsTFARECEIVED); 
         RESP(mtp3GenPegsROUTESETUNAVAILABLE, mtp3GenPegsROUTESETUNAVAILABLE); 
         RESP(mtp3GenPegsADJECENTSPUNACCESIBLE, mtp3GenPegsADJECENTSPUNACCESIBLE); 
         RESP(mtp3GenPegsUSERPARTENABLE, mtp3GenPegsUSERPARTENABLE); 
         RESP(mtp3GenPegsT1EXPIRED, mtp3GenPegsT1EXPIRED); 
         RESP(mtp3GenPegsT2EXPIRED, mtp3GenPegsT2EXPIRED); 
         RESP(mtp3GenPegsT3EXPIRED, mtp3GenPegsT3EXPIRED); 
         RESP(mtp3GenPegsT4EXPIRED, mtp3GenPegsT4EXPIRED); 
         RESP(mtp3GenPegsT5EXPIRED, mtp3GenPegsT5EXPIRED); 
         RESP(mtp3GenPegsT6EXPIRED, mtp3GenPegsT6EXPIRED); 
         RESP(mtp3GenPegsT7EXPIRED, mtp3GenPegsT7EXPIRED); 
         RESP(mtp3GenPegsT8EXPIRED, mtp3GenPegsT8EXPIRED); 
         RESP(mtp3GenPegsT9EXPIRED, mtp3GenPegsT9EXPIRED); 
         RESP(mtp3GenPegsT10EXPIRED, mtp3GenPegsT10EXPIRED); 
         RESP(mtp3GenPegsT11EXPIRED, mtp3GenPegsT11EXPIRED); 
         RESP(mtp3GenPegsT12EXPIRED, mtp3GenPegsT12EXPIRED); 
         RESP(mtp3GenPegsT13EXPIRED, mtp3GenPegsT13EXPIRED); 
         RESP(mtp3GenPegsT14EXPIRED, mtp3GenPegsT14EXPIRED); 
         RESP(mtp3GenPegsT15EXPIRED, mtp3GenPegsT15EXPIRED); 
         RESP(mtp3GenPegsT16EXPIRED, mtp3GenPegsT16EXPIRED); 
         RESP(mtp3GenPegsT17EXPIRED, mtp3GenPegsT17EXPIRED); 
         RESP(mtp3GenPegsT18EXPIRED, mtp3GenPegsT18EXPIRED); 
         RESP(mtp3GenPegsT19EXPIRED, mtp3GenPegsT19EXPIRED); 
         RESP(mtp3GenPegsT20EXPIRED, mtp3GenPegsT20EXPIRED); 
         RESP(mtp3GenPegsT21EXPIRED, mtp3GenPegsT21EXPIRED); 
         RESP(mtp3GenPegsT22EXPIRED, mtp3GenPegsT22EXPIRED); 
         RESP(mtp3GenPegsT23EXPIRED, mtp3GenPegsT23EXPIRED); 
         RESP(mtp3GenPegsT24EXPIRED, mtp3GenPegsT24EXPIRED); 
         RESP(mtp3GenPegsT25EXPIRED, mtp3GenPegsT25EXPIRED); 
         RESP(mtp3GenPegsT26EXPIRED, mtp3GenPegsT26EXPIRED); 
         RESP(mtp3GenPegsT27EXPIRED, mtp3GenPegsT27EXPIRED); 
         RESP(mtp3GenPegsT28EXPIRED, mtp3GenPegsT28EXPIRED); 
         RESP(mtp3GenPegsT29EXPIRED, mtp3GenPegsT29EXPIRED); 
         RESP(mtp3GenPegsT30EXPIRED, mtp3GenPegsT30EXPIRED); 
         RESP(mtp3GenPegsT31EXPIRED, mtp3GenPegsT31EXPIRED); 
         RESP(mtp3GenPegsT32EXPIRED, mtp3GenPegsT32EXPIRED); 
         RESP(mtp3GenPegsT33EXPIRED, mtp3GenPegsT33EXPIRED);
         memcpy(peg_resp_buff, oamMtp3GenPegResponse, Length); 
         free(oamMtp3GenPegResponse);
         oamMtp3GenPegResponse=NULL;  
         #undef RESP
         PEG_FLAG = SS7_TRUE;
         break;

    case NWSTK_SCM_LINK_PEG_RESP:
    case NWSTK_SCM_LINK_PEG_NACK_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP3_LINKPEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         stop_timer(TIMER_NWSTK);
         switch(opcode)
          {
           case NWSTK_SCM_LINK_PEG_NACK_RESP:
                SCM_printf(SCM_MAJOR,"Link peg cmd response : cmd failure");
                resp_opcode = SCM_OAM_LINK_PEG_RESP;
                PEG_FLAG = SS7_FALSE;
                break;
           case NWSTK_SCM_LINK_PEG_RESP:
                SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'MTP3_LINK_PEG_GET_RESP' ");
                peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
                resp_opcode = SCM_OAM_LINK_PEG_RESP;
                Length = sizeof(ScmOamMtp3LinkPegResponse);
                nwstkScmMtp3LinkPegResponse = (NwstkScmMtp3LinkPegResponse*)msg_buff;
                oamMtp3LinkPegResponse = (ScmOamMtp3LinkPegResponse*)scm_malloc(sizeof(ScmOamMtp3LinkPegResponse));
                #define RESP(A,C) \
                    oamMtp3LinkPegResponse->A = nwstkScmMtp3LinkPegResponse->C;
               RESP(mtp3LinkPegslinksetID, mtp3LinkPegslinksetID); 
               RESP(mtp3LinkPegslinkCode, mtp3LinkPegslinkCode); 
               RESP(mtp3LinkPegsLINKCOOTX, mtp3LinkPegsLINKCOOTX); 
               RESP(mtp3LinkPegsLINKCOORX, mtp3LinkPegsLINKCOORX); 
               RESP(mtp3LinkPegsLINKCOATX, mtp3LinkPegsLINKCOATX); 
               RESP(mtp3LinkPegsLINKCOARX, mtp3LinkPegsLINKCOARX); 
               RESP(mtp3LinkPegsLINKECOTX, mtp3LinkPegsLINKECOTX); 
               RESP(mtp3LinkPegsLINKECORX, mtp3LinkPegsLINKECORX); 
               RESP(mtp3LinkPegsLINKECATX, mtp3LinkPegsLINKECATX); 
               RESP(mtp3LinkPegsLINKECARX, mtp3LinkPegsLINKECARX); 
               RESP(mtp3LinkPegsLINKCBDTX, mtp3LinkPegsLINKCBDTX); 
               RESP(mtp3LinkPegsLINKCBDRX, mtp3LinkPegsLINKCBDRX); 
               RESP(mtp3LinkPegsLINKCBATX, mtp3LinkPegsLINKCBATX); 
               RESP(mtp3LinkPegsLINKCBARX, mtp3LinkPegsLINKCBARX);
               RESP(mtp3LinkPegsLINKLINTX, mtp3LinkPegsLINKLINTX);   
               RESP(mtp3LinkPegsLINKLINRX, mtp3LinkPegsLINKLINRX);   
               RESP(mtp3LinkPegsLINKLIATX, mtp3LinkPegsLINKLIATX);   
               RESP(mtp3LinkPegsLINKLIARX, mtp3LinkPegsLINKLIARX);   
               RESP(mtp3LinkPegsLINKLUNTX, mtp3LinkPegsLINKLUNTX);   
               RESP(mtp3LinkPegsLINKLUNRX, mtp3LinkPegsLINKLUNRX);   
               RESP(mtp3LinkPegsLINKLUATX, mtp3LinkPegsLINKLUATX);   
               RESP(mtp3LinkPegsLINKLUARX, mtp3LinkPegsLINKLUARX);   
               RESP(mtp3LinkPegsLINKLIDTX, mtp3LinkPegsLINKLIDTX);   
               RESP(mtp3LinkPegsLINKLIDRX, mtp3LinkPegsLINKLIDRX);   
               RESP(mtp3LinkPegsLINKLFUTX, mtp3LinkPegsLINKLFUTX);   
               RESP(mtp3LinkPegsLINKLFURX, mtp3LinkPegsLINKLFURX);   
               RESP(mtp3LinkPegsLINKLLITX, mtp3LinkPegsLINKLLITX);   
               RESP(mtp3LinkPegsLINKLLIRX, mtp3LinkPegsLINKLLIRX);   
               RESP(mtp3LinkPegsLINKLRITX, mtp3LinkPegsLINKLRITX);   
               RESP(mtp3LinkPegsLINKLR_RX, mtp3LinkPegsLINKLR_RX);   
               RESP(mtp3LinkPegsLINKDLCTX, mtp3LinkPegsLINKDLCTX);   
               RESP(mtp3LinkPegsLINKDLCRX, mtp3LinkPegsLINKDLCRX);   
               RESP(mtp3LinkPegsLINKCSSTX, mtp3LinkPegsLINKCSSTX);   
               RESP(mtp3LinkPegsLINKCSSRX, mtp3LinkPegsLINKCSSRX);   
               RESP(mtp3LinkPegsLINKCNSTX, mtp3LinkPegsLINKCNSTX);   
               RESP(mtp3LinkPegsLINKCNSRX, mtp3LinkPegsLINKCNSRX);   
               RESP(mtp3LinkPegsLINKCNPTX, mtp3LinkPegsLINKCNPTX);   
               RESP(mtp3LinkPegsLINKCNPRX, mtp3LinkPegsLINKCNPRX);   
               RESP(mtp3LinkPegsLINKUPUTX, mtp3LinkPegsLINKUPUTX);   
               RESP(mtp3LinkPegsLINKUPURX, mtp3LinkPegsLINKUPURX);   
               RESP(mtp3LinkPegsLINKSLTMTX, mtp3LinkPegsLINKSLTMTX);   
               RESP(mtp3LinkPegsLINKSLTMRX, mtp3LinkPegsLINKSLTMRX);   
               RESP(mtp3LinkPegsLINKSLTATX, mtp3LinkPegsLINKSLTATX);   
               RESP(mtp3LinkPegsLINKSLTARX, mtp3LinkPegsLINKSLTARX);  
               memcpy(peg_resp_buff, oamMtp3LinkPegResponse, Length);
               free(oamMtp3LinkPegResponse);
               oamMtp3LinkPegResponse=NULL;
               #undef RESP 
               PEG_FLAG = SS7_TRUE;
               break;
           }
         break;

    case NWSTK_SCM_ROUTE_PEG_RESP:
    case NWSTK_SCM_ROUTE_PEG_NACK_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_MTP3_ROUTEPEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_INFO,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         stop_timer(TIMER_NWSTK);
         switch(opcode)
          {
           case NWSTK_SCM_ROUTE_PEG_NACK_RESP:
                SCM_printf(SCM_MAJOR,"Route peg get cmd response: cmd failure");
                resp_opcode = SCM_OAM_ROUTE_PEG_RESP;
                PEG_FLAG = 0;
           case NWSTK_SCM_ROUTE_PEG_RESP:
                SCM_printf(SCM_MAJOR,"MTP3 - > SCM 'ROUTE_PEG_GET_RESP' ");
                resp_opcode = SCM_OAM_ROUTE_PEG_RESP;
                peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
                Length = sizeof(ScmOamMtp3RoutePegResponse);
                oamMtp3RoutePegResponse = (ScmOamMtp3RoutePegResponse*)scm_malloc(sizeof(ScmOamMtp3RoutePegResponse));
                nwstkScmMtp3RoutePegResponse = (NwstkScmMtp3RoutePegResponse*)msg_buff;
                #define RESP(A,C) \
                     oamMtp3RoutePegResponse->A = nwstkScmMtp3RoutePegResponse->C;
         
               RESP(dpc, dpc); 
               RESP(ni, ni); 
               RESP(mtp3RoutePegsDPCTFATX, mtp3RoutePegsDPCTFATX); 
               RESP(mtp3RoutePegsDPCTFARX, mtp3RoutePegsDPCTFARX); 
               RESP(mtp3RoutePegsDPCTFPTX, mtp3RoutePegsDPCTFPTX); 
               RESP(mtp3RoutePegsDPCTFPRX, mtp3RoutePegsDPCTFPRX); 
               RESP(mtp3RoutePegsDPCRSTTX, mtp3RoutePegsDPCRSTTX); 
               RESP(mtp3RoutePegsDPCRSTRX, mtp3RoutePegsDPCRSTRX); 
               RESP(mtp3RoutePegsDPCTFRRX, mtp3RoutePegsDPCTFRRX); 
               RESP(mtp3RoutePegsDPCTFCTX, mtp3RoutePegsDPCTFCTX); 
               RESP(mtp3RoutePegsDPCTFCRX, mtp3RoutePegsDPCTFCRX); 
               RESP(mtp3RoutePegsDPCSIFTX, mtp3RoutePegsDPCSIFTX); 
               memcpy(peg_resp_buff, oamMtp3RoutePegResponse, Length);
               free(oamMtp3RoutePegResponse);
               oamMtp3RoutePegResponse=NULL;
              #undef RESP 

               PEG_FLAG = SS7_TRUE;
               break;
            }
           break;

    case NWSTK_SCM_SCCP_GENPEG_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_SCCP_GENPEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         stop_timer(TIMER_NWSTK);
         SCM_printf(SCM_MAJOR,"SCCP - > SCM 'GEN_PEG_GET_RESP' ");
         peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
         resp_opcode = SCM_OAM_SCCP_GENPEG_RESP;
         Length = sizeof(ScmOamSccpGenPegResponse);
         oamSccpGenPegResponse = (ScmOamSccpGenPegResponse*)scm_malloc(sizeof(ScmOamSccpGenPegResponse));
         nwstkScmSccpGenPegResponse = (NwstkScmSccpGenPegResponse*)msg_buff;
         #define RESP(A,C) \
                    oamSccpGenPegResponse->A = nwstkScmSccpGenPegResponse->C;
         RESP(sccpGenPegsUSERMSGSENT, sccpGenPegsUSERMSGSENT);
         RESP(sccpGenPegsREMOTEMSGRECEIVED, sccpGenPegsREMOTEMSGRECEIVED);
         RESP(sccpGenPegsROUTINGFAILURE, sccpGenPegsROUTINGFAILURE);
         RESP(sccpGenPegsREMOTEGTTREQUEST, sccpGenPegsREMOTEGTTREQUEST);
         RESP(sccpGenPegsREMOTEGTTSUCCESS, sccpGenPegsREMOTEGTTSUCCESS);
         RESP(sccpGenPegsREMOTEGTTFAILURE, sccpGenPegsREMOTEGTTFAILURE);
         RESP(sccpGenPegsREMOTEMSGDECODEERR, sccpGenPegsREMOTEMSGDECODEERR);
         RESP(sccpGenPegsUSERMSGENCODEERR, sccpGenPegsUSERMSGENCODEERR);
         RESP(sccpGenPegsREMOTEREASSEMBLEERR, sccpGenPegsREMOTEREASSEMBLEERR);
         RESP(sccpGenPegsHOPCOUNTERVIOLATIONERR, sccpGenPegsHOPCOUNTERVIOLATIONERR);
         RESP(sccpGenPegsUSERSEGMENTATIONERR, sccpGenPegsUSERSEGMENTATIONERR);
         RESP(sccpGenPegsTIMERTIAREXPIRY, sccpGenPegsTIMERTIAREXPIRY);
         RESP(sccpGenPegsUSERINITIATEDRLS, sccpGenPegsUSERINITIATEDRLS);
         RESP(sccpGenPegsUSERINITITATEDRESET, sccpGenPegsUSERINITITATEDRESET);
         RESP(sccpGenPegsREMOTEUDTRCVD, sccpGenPegsREMOTEUDTRCVD);
         RESP(sccpGenPegsREMOTEXUDTRCVD, sccpGenPegsREMOTEXUDTRCVD);
         RESP(sccpGenPegsREMOTEUDTSRCVD, sccpGenPegsREMOTEUDTSRCVD);
         RESP(sccpGenPegsREMOTEXUDTSRCVD, sccpGenPegsREMOTEXUDTSRCVD);
         RESP(sccpGenPegsREMOTELUDTRCVD, sccpGenPegsREMOTELUDTRCVD);
         RESP(sccpGenPegsREMOTELUDTSRCVD, sccpGenPegsREMOTELUDTSRCVD);
         RESP(sccpGenPegsUSERUDTSENT, sccpGenPegsUSERUDTSENT);
         RESP(sccpGenPegsUSERXUDTSENT, sccpGenPegsUSERXUDTSENT);
         RESP(sccpGenPegsUSERUDTSSENT, sccpGenPegsUSERUDTSSENT);
         RESP(sccpGenPegsUSERXUDTSSENT, sccpGenPegsUSERXUDTSSENT);
         RESP(sccpGenPegsUSERLUDTSENT, sccpGenPegsUSERLUDTSENT);
         RESP(sccpGenPegsUSERLUDTSSENT, sccpGenPegsUSERLUDTSSENT);
         RESP(sccpGenPegsUSERCRSENT, sccpGenPegsUSERCRSENT);
         RESP(sccpGenPegsCREFTOREMOTESENT, sccpGenPegsCREFTOREMOTESENT );
         RESP(sccpGenPegsRSRTOREMOTESENT, sccpGenPegsRSRTOREMOTESENT );
         RESP( sccpGenPegsERRTOREMOTESENT, sccpGenPegsERRTOREMOTESENT);
         RESP(sccpGenPegsREMOTECRRCVD, sccpGenPegsREMOTECRRCVD );
         RESP(sccpGenPegsREMOTECREFRCVD, sccpGenPegsREMOTECREFRCVD);
         RESP(sccpGenPegsREMOTERSRRCVD, sccpGenPegsREMOTERSRRCVD);
         RESP(sccpGenPegsREMOTEERRRCVD, sccpGenPegsREMOTEERRRCVD);
         RESP(sccpGenPegsREMOTEMSGLOCALSSRCVD, sccpGenPegsREMOTEMSGLOCALSSRCVD);
         RESP(sccpGenPegsUSERDT1SENT, sccpGenPegsUSERDT1SENT);
         RESP(sccpGenPegsREMOTEDT1RCVD, sccpGenPegsREMOTEDT1RCVD);
         RESP(sccpGenPegsUSERDT2SENT, sccpGenPegsUSERDT2SENT);
         RESP(sccpGenPegsREMOTEDT2RCVD, sccpGenPegsREMOTEDT2RCVD);
         RESP(sccpGenPegsUSEREDSENT, sccpGenPegsUSEREDSENT);
         RESP(sccpGenPegsREMOTEEDRCVD, sccpGenPegsREMOTEEDRCVD);
         RESP(sccpGenPegsREMOTESSPRCVD, sccpGenPegsREMOTESSPRCVD);
         RESP(sccpGenPegsREMOTESSARCVD, sccpGenPegsREMOTESSARCVD);
         RESP(sccpGenPegsREMOTESSCRCVD, sccpGenPegsREMOTESSCRCVD);
         RESP(sccpGenPegsLOCALSSPROHIBITED, sccpGenPegsLOCALSSPROHIBITED);
         RESP(sccpGenPegsLOCALSSALLOWED, sccpGenPegsLOCALSSALLOWED);
         RESP(sccpGenPegsLOCALSSCONGESTED, sccpGenPegsLOCALSSCONGESTED);
         memcpy(peg_resp_buff, oamSccpGenPegResponse, Length); 
         #undef RESP
         free(oamSccpGenPegResponse);
         oamSccpGenPegResponse=NULL;
         PEG_FLAG = SS7_TRUE;
         break;

    case NWSTK_SCM_BSSAP_GENPEG_RESP:
    case NWSTK_SCM_BSSAP_GENPEG_NACK_RESP:
         if((transaction_id != transaction_Id[SCM_NWSTK_BSSAP_GENPEG_GET])
             && (timer_info[TIMER_NWSTK].timer_strt_flag != 1))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from nwstk: cause:: resp waiting timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
             return ;
           }
        else
         stop_timer(TIMER_NWSTK);
         switch(opcode)
          {
           case NWSTK_SCM_BSSAP_GENPEG_NACK_RESP:
                SCM_printf(SCM_MAJOR,"Bssap general peg get cmd resp: cmd failure");
                PEG_FLAG = SS7_FALSE;
                resp_opcode = SCM_OAM_BSSAP_GENPEG_RESP; 
                break;
           case NWSTK_SCM_BSSAP_GENPEG_RESP:
             peg_resp_buff = (U8*)scm_malloc(500*sizeof(char));
             resp_opcode = SCM_OAM_BSSAP_GENPEG_RESP; 
             SCM_printf(SCM_MAJOR,"BSSAP - > SCM 'GEN_PEG_GET_RESP'");
             Length = sizeof(ScmOamBssapGenPegResponse);
             oamBssapGenPegResponse = (ScmOamBssapGenPegResponse*)scm_malloc(sizeof(ScmOamBssapGenPegResponse));
             nwstkScmBssapGenPegResponse = (NwstkScmBssapGenPegResponse*)msg_buff;
             #define RESP(A,C) \
                              oamBssapGenPegResponse->A = nwstkScmBssapGenPegResponse->C;
             RESP(bscPointCode, bscPointCode);
             RESP(bssapGenPegsCRRECV, bssapGenPegsCRRECV);
             RESP(bssapGenPegsDT1RECV, bssapGenPegsDT1RECV);
             RESP(bssapGenPegsCRSEND, bssapGenPegsCRSEND);
             RESP(bssapGenPegsDT1SEND, bssapGenPegsDT1SEND);
             RESP(bssapGenPegsDTAPSEND, bssapGenPegsDTAPSEND);
             RESP(bssapGenPegsDTAPRECV, bssapGenPegsDTAPRECV);
             RESP(bssapGenPegsmapSEND, bssapGenPegsmapSEND);
             RESP(bssapGenPegsmapRECV, bssapGenPegsmapRECV);
             RESP(bssapGenPegsCONFSEND, bssapGenPegsCONFSEND);
             RESP(bssapGenPegsCONFRECV, bssapGenPegsCONFRECV);
             RESP(bssapGenPegsCMSERVSEND, bssapGenPegsCMSERVSEND);
             RESP(bssapGenPegsPAGRSPSEND, bssapGenPegsPAGRSPSEND);
             memcpy(peg_resp_buff, oamBssapGenPegResponse, Length);
             #undef RESP
             PEG_FLAG = SS7_TRUE;
             break;
        }
      break;

    default:
         SCM_printf(SCM_MAJOR,"WRONG OPCODE VALUE RECIEVED IN NWSTK RESP");


   }
  if((error_code != 0 ) && (PEG_FLAG != SS7_TRUE))
   {
     if((g_parameter.redundant_status == SCM_STANDBY) && (g_parameter.config_flag == SS7_TRUE))
     {
      SCM_printf(SCM_INFO,"CMD successfull: command replicated from active nwstack");
     }
     else
     {
      SCM_printf(SCM_MAJOR,"CMD FAILURE: error code: %d", error_code);
      form_resp_error_code(error_code , &resp_error_code, APP_ID_NWSTK); 
     }
   }
  else 
   SCM_printf(SCM_INFO,"CMD successfull");
 if((g_parameter.config_flag == SS7_TRUE) ||(timer_info[TIMER_NWSTK].db_oam_stamp == DB_STAMP))
  {
   SCM_printf(SCM_DEBUG,"Stk Config Cmd from Db  success");
   *nxt_cmd_flg = SS7_TRUE;
   g_parameter.noOam_resp_flag = 0;
   g_parameter.config_cmd_resp = 0;
   return ;
  }
 else 
  if((g_roll_back_flag.nwstk_roll_back_flag == 0) || (PEG_FLAG == SS7_TRUE))
  {
   if(PEG_FLAG == SS7_TRUE)
   {
     oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
     operation =  oam_transaction_Id[tr_opcode].operation;
     pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
     send_resp_to_oam(resp_opcode, operation, oam_tr_id , pegrfu, NO_ERROR, peg_resp_buff, Length , APP_ID_NWSTK); 
    if(peg_resp_buff != NULL)
    {
     free(peg_resp_buff);
     peg_resp_buff = NULL;
     return ;
    }
   }
  else
   {
     oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
     operation =  oam_transaction_Id[tr_opcode].operation;
     pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
     send_resp_to_oam(resp_opcode, operation,oam_tr_id, pegrfu, resp_error_code, NULL, Length, APP_ID_NWSTK);
   }
  return ; 
 }
else 
  g_roll_back_flag.nwstk_roll_back_flag = 0;  
 return ; 
}

void process_lapdstk_response (U8* msg_buff, U8* nxt_cmd_flg)
{
     U8   cmd_buff[1500];
     U32 error_code, Length , oam_tr_id;
     U8  operation, sendOamFlag = 1;
     U16 tr_opcode, resp_opcode, resp_error_code = 0, pegrfu, pegcount;
     LapdPegResponse *lapdPegResponse;

     
     lapdScmCfgResp_t            *lapdResCfg;


     Length = sizeof(ScmOamResponse);
     tr_opcode = timer_info[TIMER_LAPD].opcode - BASE_OPCODE_SCM;
   
     strcpy(g_parameter.function_string, "process_lapdstk_response()");

     if((msg_buff[2] == LAPD_SCM_ALARM_MSG))
      {
       SCM_printf (SCM_MAJOR,"Alarm received from Lapd stack");
       process_Lapd_alarm(msg_buff);
       *nxt_cmd_flg = SS7_FALSE;
       return ; 
      } 
 
     SCM_printf (SCM_INFO,"");
     SCM_printf (SCM_INFO,"# # # # # # # # # # # # # # # #");
     SCM_printf (SCM_INFO,"Command response from Lapd stack");
     SCM_printf (SCM_INFO,"# # # # # # # # # # # # # # # #");
     SCM_printf(SCM_INFO,"");
 /* handling for init garbase response */
  if(tr_opcode > OPCODEMAX)
  {
            SCM_printf(SCM_MAJOR,"Unexpected response from stk: cause:: resp waiting timer flag is zero");
            return;
  }
 /*end here*/
     if(timer_info[TIMER_LAPD].timer_strt_flag != 1)
       {
        SCM_printf(SCM_MAJOR,"Unexpected response from lapd discarded: cause response waiting timer flag is zero");
        *nxt_cmd_flg = SS7_FALSE;
         return ;
       }
     else 
         oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
         operation =  oam_transaction_Id[tr_opcode].operation;
         pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;


        if((g_roll_back_flag.lapd_roll_back_flag == 1)||(g_parameter.config_flag == SS7_TRUE))
        {
         sendOamFlag = 0;     
         g_roll_back_flag.lapd_roll_back_flag = 0; 
         /* added extra check msg_buff[2] != LAPD_SCM_TMR_MSG to avoid misupdation of configflag for lapd tmr cfg*/
         if((g_parameter.config_flag == SS7_TRUE ) && (msg_buff[2] != LAPD_SCM_TMR_MSG))
          {
           *nxt_cmd_flg = SS7_TRUE;
           g_parameter.config_cmd_resp =0;
          }  
        }

    switch ( msg_buff[2] )
    {
      case LAPD_SCM_TMR_MSG:
           lapdResCfg = (lapdScmCfgResp_t*)&msg_buff[2];
           error_code = lapdResCfg->value;
           stop_timer(TIMER_LAPD);
           if(error_code != 0)
           {
            timer_info[TIMER_LAPD].resp_error_id = error_code;
            SCM_printf(SCM_MAJOR,"Lapd timer config command failure");
            resp_error_code =  LAPD_COMMAND_FAILURE;
           }
           else
           { 
            SCM_printf(SCM_MAJOR,"Lapd timer config command successfull");
            if(g_parameter.config_flag == 1) 
             { 
               *nxt_cmd_flg =SS7_TRUE;  
               g_parameter.config_cmd_resp =0;
               return ;
             }
            else
             { 
              match_resp_opcode(timer_info[TIMER_LAPD].opcode, &resp_opcode); 
              nxt_cmd_flg =SS7_FALSE;
              resp_error_code =  NO_ERROR;
             }
           }
           if(sendOamFlag == 1)  
             send_resp_to_oam(resp_opcode, operation, oam_tr_id ,pegrfu, 
                              resp_error_code, NULL, Length, APP_ID_LAPD); 
           return ;
           break;  
        
      case LAPD_SCM_CFG_MSG:
           lapdResCfg = (lapdScmCfgResp_t*)&msg_buff[2];
           error_code = lapdResCfg->value;
           timer_info[TIMER_LAPD].resp_error_id = error_code;
           stop_timer(TIMER_LAPD);
           if(g_parameter.config_flag == 1) 
             { *nxt_cmd_flg =SS7_TRUE;  return ; }
           else
           { 
             match_resp_opcode(timer_info[TIMER_LAPD].opcode, &resp_opcode); 
             nxt_cmd_flg =SS7_FALSE;
             if( error_code == LAPD_SCM_SUCCESS )
              { resp_error_code =  NO_ERROR;
                SCM_printf(SCM_INFO,"Lapd config command successfull");
              }  
             else 
              {  resp_error_code = LAPD_COMMAND_FAILURE;     
                SCM_printf(SCM_MAJOR,"Lapd config command failure");
              }
             if(sendOamFlag == 1)  
             send_resp_to_oam(resp_opcode, operation, oam_tr_id ,pegrfu, 
                              resp_error_code, NULL, Length, APP_ID_LAPD); 
             return ;
          }
           break;  
 
      case LAPD_SCM_PEGS_MSG:
           stop_timer(TIMER_LAPD);
           Length = sizeof(ScmOamLapdPegResponse);
           lapdPegResponse = (LapdPegResponse*)&msg_buff[5];
           ((ScmOamLapdPegResponse*)cmd_buff)->count = lapdPegResponse->count;
           U32 pegLoop, pegOffset= 0;
           pegOffset = sizeof(ScmOamLapdPegResponse);

           for(pegLoop=0; pegLoop < lapdPegResponse->count; pegLoop++)
           {
            if(pegLoop == 0)
            {
             ((ScmOamLapdPegResponse*)cmd_buff)->scmOamLapdPeg[pegLoop].applTei = 
                                                lapdPegResponse->lapdPeg[pegLoop].applTei;
             for(pegcount = 0; pegcount < 2; pegcount++)
             {
              #define FILL_PEG_ELE(A) \
                   ((ScmOamLapdPegResponse*)cmd_buff)->scmOamLapdPeg[pegLoop].pegInfo[pegcount].A = \
                                      lapdPegResponse->lapdPeg[pegLoop].pegInfo[pegcount].A;
               FILL_PEG_ELE(sapi);
               FILL_PEG_ELE(pegLapdInfoSend);
               FILL_PEG_ELE(pegLapdInfoRecv);
               FILL_PEG_ELE(pegLapdUiSend);
               FILL_PEG_ELE(pegLapdUiRecv);
               FILL_PEG_ELE(pegLapdRrCSend);
               FILL_PEG_ELE(pegLapdRrCRecv);
               FILL_PEG_ELE(pegLapdRrRSend);
               FILL_PEG_ELE(pegLapdRrRRecv);
               FILL_PEG_ELE(pegLapdRejCSend);
               FILL_PEG_ELE(pegLapdRejCRecv);
               FILL_PEG_ELE(pegLapdRejRSend);
               FILL_PEG_ELE(pegLapdRejRRecv);
               FILL_PEG_ELE(pegLapdRnrCSend);
               FILL_PEG_ELE(pegLapdRnrCRecv);
               FILL_PEG_ELE(pegLapdRnrRSend);
               FILL_PEG_ELE(pegLapdRnrRRecv);
               FILL_PEG_ELE(pegLapdMsgDecodeFail);
               FILL_PEG_ELE(pegLapdMsgEncodeFail);
               #undef FILL_PEG_ELE  
             }
            }
            else
            {
               (((ScmOamLapdPeg*)&cmd_buff[pegOffset]))->applTei = 
                                                 lapdPegResponse->lapdPeg[pegLoop].applTei;
             for(pegcount = 0; pegcount < 2; pegcount++)
             {
               
              #define FILL_PEG_ELE(A) \
                   (((ScmOamLapdPeg*)&cmd_buff[pegOffset]))->pegInfo[pegcount].A = \
                                      lapdPegResponse->lapdPeg[pegLoop].pegInfo[pegcount].A
               FILL_PEG_ELE(sapi);
               FILL_PEG_ELE(pegLapdInfoSend);
               FILL_PEG_ELE(pegLapdInfoRecv);
               FILL_PEG_ELE(pegLapdUiSend);
               FILL_PEG_ELE(pegLapdUiRecv);
               FILL_PEG_ELE(pegLapdRrCSend);
               FILL_PEG_ELE(pegLapdRrCRecv);
               FILL_PEG_ELE(pegLapdRrRSend);
               FILL_PEG_ELE(pegLapdRrRRecv);
               FILL_PEG_ELE(pegLapdRejCSend);
               FILL_PEG_ELE(pegLapdRejCRecv);
               FILL_PEG_ELE(pegLapdRejRSend);
               FILL_PEG_ELE(pegLapdRejRRecv);
               FILL_PEG_ELE(pegLapdRnrCSend);
               FILL_PEG_ELE(pegLapdRnrCRecv);
               FILL_PEG_ELE(pegLapdRnrRSend);
               FILL_PEG_ELE(pegLapdRnrRRecv);
               FILL_PEG_ELE(pegLapdMsgDecodeFail);
               FILL_PEG_ELE(pegLapdMsgEncodeFail);
               #undef FILL_PEG_ELE  
             }
            }
            if(pegLoop != 0)
            {
             pegOffset = pegOffset + sizeof(ScmOamLapdPeg);   
             Length = Length + sizeof(ScmOamLapdPeg);
            }
           } 
              
 
             SCM_printf(SCM_INFO,"Lapd peg get success");
             match_resp_opcode(timer_info[TIMER_LAPD].opcode, &resp_opcode); 
             send_resp_to_oam(resp_opcode, operation, oam_tr_id ,pegrfu, 
                              resp_error_code, cmd_buff, Length, APP_ID_LAPD);
            break; 
    case LAPD_SCM_PEGS_NACK:
           stop_timer(TIMER_LAPD);
           timer_info[TIMER_LAPD].resp_error_id = error_code;
           SCM_printf(SCM_MAJOR,"Lapd peg get command failure");
           resp_error_code =  LAPD_COMMAND_FAILURE;
           match_resp_opcode(timer_info[TIMER_LAPD].opcode, &resp_opcode);
           send_resp_to_oam(resp_opcode, operation, oam_tr_id ,pegrfu,
                              resp_error_code, NULL, Length, APP_ID_LAPD);
           return ;
           break;

 
             
          default:
               SCM_printf(SCM_MAJOR," ERROR IN HANDLING FOR LAPD RESPONSE  :");
    }
            
}
/*********************************************************************************/
/* This funtion decodes the response from map/tcap/ isup and send response to oam if oamstamp
   is true, also send map/tcap/isup alarms to o&m*/
/*********************************************************************************/
void process_resp_from_stack ( U8 *msg_buff,  U8* nxt_cmd_flg, int numbytes, int entity )
{
      U16   Length,  resp_error_code = 0;
      int rs = 0;
      unsigned long  error_code;
      U8 cmd_buff [200], resp_entity, sendOamFlag = 1;
      U32  oam_tr_id;
      U8 transaction_id,  operation, timer_id;
      U16  opcode, resp_opcode, tr_opcode, pegrfu;

      Length = sizeof(ScmOamResponse);
      opcode = msg_buff[1];
      transaction_id = msg_buff[7];
      strcpy(g_parameter.function_string, "process_resp_from_stack()");
      if( (msg_buff[0] == 163) &&(msg_buff[5] == 5)&&
          (msg_buff[6] == OAM_ISUP_SS7_SM_UPDATE_WITHRED_DATA ))
         { 
           if((msg_buff[8] != 0))
            {
             SCM_printf (SCM_INFO, " Stanby ISUP updation successful");
            } 
           else 
            {
             SCM_printf (SCM_INFO, " Stanby ISUP updation failed");
            }  
           return;
         }


      if(transaction_id == transaction_Id[MULTI_CMD])
       {
        process_multicmd_resp(msg_buff, nxt_cmd_flg);
        return;
       }
  
      SCM_printf (SCM_INFO,"");
      SCM_printf (SCM_INFO,"# # # # # # # # # # # # # # # #");
      opcode = msg_buff[0];
              #define CASE_DIS(A,B)       \
                      case A:             \
                           SCM_printf(SCM_MAJOR,B); \
                           resp_entity = A;              \
                           break;
         if(msg_buff[8] == 1) 
           {
               switch (msg_buff[0])
               {
               CASE_DIS (RESP_APP_ID_ISUP,"ISUP - > SCM 'CMD RESPONSE SUCCESS' ");
               CASE_DIS (APP_ID_TCAP," TCAP - > SCM 'CMD RESPONSE SUCCESS'");
               CASE_DIS (RESP_APP_ID_MAP,"MAP - > SCM 'CMD RESPONSE SUCCESS'");
               }
          }   
        else
          {
              switch (msg_buff[0])
              {
               CASE_DIS (RESP_APP_ID_ISUP,"ISUP - > SCM 'CMD RESPONSE FAILURE' ");
               CASE_DIS (APP_ID_TCAP," TCAP - > SCM 'CMD RESPONSE FAILURE'");
               CASE_DIS (RESP_APP_ID_MAP,"MAP - > SCM 'CMD RESPONSE FAILURE'");
              }  
          }
       
              #undef CASE_DIS
       
 

      switch(entity)
        {
         case APP_ID_TCAP:
         case APP_ID_MAP:
             timer_id = TIMER_MAPTCAP;
             tr_opcode = timer_info[timer_id].opcode - BASE_OPCODE_SCM;
            /* handling for init garbase response */
            if(tr_opcode > OPCODEMAX)
            {
             SCM_printf(SCM_MAJOR,"Unexpected response from stk: cause:: resp waiting timer flag is zero");
             return;
            }
          /* end here*/
             if(g_roll_back_flag.maptcap_roll_back_flag == 1)
              {
               sendOamFlag = 0;
               g_roll_back_flag.maptcap_roll_back_flag = 0;
              } 
             if((transaction_id != transaction_Id[tr_opcode])
                 && (timer_info[timer_id].timer_strt_flag != 1))
              {
               SCM_printf(SCM_MAJOR,"Unexpected response from map/tcap discarded: cause wainting response timer flag is zero");
               *nxt_cmd_flg = SS7_FALSE;
               return ;
              }
             stop_timer(TIMER_MAPTCAP);
             oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
             operation =  oam_transaction_Id[tr_opcode].operation;
             pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
             break; 
        }
      timer_info[timer_id].resp_error_id = 0;/*to mark resp error so stop the timer*/
      

      SCM_printf (SCM_INFO,"# # # # # # # # # # # # # # # #");
      SCM_printf (SCM_INFO,"");
      if(msg_buff[8] == 0) /* Command Failure */
       {
        g_parameter.config_cmd_resp = 0;  
        SCM_printf(SCM_MAJOR,"command failure ");
        SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||");
        timer_info[timer_id].resp_error_id = 1;   
        stop_timer(timer_id);
        /* Error_ID IS OF 4 BYTES IN CASE OF MAP */
        if (msg_buff[0] != RESP_APP_ID_MAP)
         {
          error_code = ((msg_buff[10] << 8) & 0xff00) | msg_buff[9];
         }
        else
         {
          error_code = ((msg_buff[10] << 8) & 0xff00) | msg_buff[9];
          error_code = error_code | ((msg_buff[11] << 16) &   0xFF0000);
          error_code = error_code | ((msg_buff[12] << 24) & 0xFF000000);

         }
        SCM_printf(SCM_MAJOR,"error code received: %d", error_code);
        timer_info[timer_id].resp_error_id = error_code;
        form_resp_error_code(error_code , &resp_error_code, resp_entity); 
        SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||");
        SCM_printf(SCM_INFO,"");
        if(g_parameter.config_flag == SS7_TRUE)
         {
          *nxt_cmd_flg = SS7_TRUE;
          g_parameter.config_cmd_resp = 0;  
         }
        else
         { 
          match_resp_opcode(timer_info[timer_id].opcode, &resp_opcode); 
          if( sendOamFlag == 1)
          send_resp_to_oam(resp_opcode, operation, oam_tr_id , pegrfu, resp_error_code, 
                           NULL, Length, entity);
         }
        return ;
       }
      else
       /* SUCCESS in command response */
       {
        SCM_printf(SCM_INFO," Command resonse : successful :");
        Length = sizeof(ScmOamResponse);
        /* CHECK FOR GET MESSAGE RESPONSES */
     /* M A P/ T C A P */
     /* COMMAND CATEGORY : 2 */

#if 0 
Amaresh
     if ( ( msg_buff [6] == OAM_TCAP_SS7_SM_GET_STATS_RESP ))
      {
      if(timer_info[timer_id].opcode == OAM_SCM_TCAP_PEG_GET)
       { 
         resp_opcode = SCM_OAM_TCAP_PEG_RESP; 
         Length = sizeof (ScmOamTcapPegResponse);
         oamTcapPegResponse = (ScmOamTcapPegResponse*)scm_malloc(sizeof(ScmOamTcapPegResponse));
         SCM_printf(SCM_INFO,"Tcap peg get command response");
         rs = 9;
         #define SC_RES(T)\
                 SCM_printf(SCM_INFO, T );
                  
         #define GET_RES(P)    \
                 oamTcapPegResponse->P = \
                 EVAL_32(rs, msg_buff); \
                 SCM_printf(SCM_INFO," : %x", oamTcapPegResponse->P);\
                 rs = rs + 4;
          //SC_RES ("tcapStatsPegRecvSerUsrApi");
          GET_RES (tcapStatsPegRecvSerUsrApi);
          //SC_RES ("tcapStatsPegSendSerUsrApi");
          GET_RES (tcapStatsPegSendSerUsrApi);
          //SC_RES ("tcapStatsPegRecvLlayerApi");
          GET_RES (tcapStatsPegRecvLlayerApi);
          //SC_RES ("tcapStatsPegSendLlayerAp");
          GET_RES (tcapStatsPegSendLlayerAp);
          //SC_RES ("tcapStatsPegRecvSmApi");
          GET_RES (tcapStatsPegRecvSmApi);
          //SC_RES ("tcapStatsPegSendSmApi");
          GET_RES (tcapStatsPegSendSmApi);
          //SC_RES ("tcapStatsPegSerUsrErr");
          GET_RES (tcapStatsPegSerUsrErr);
          //SC_RES ("tcapStatsPegSerLlayerErr");
          GET_RES (tcapStatsPegSerLlayerErr);
          //SC_RES ("tcapStatsPegSmErr");
          GET_RES (tcapStatsPegSmErr);
          GET_RES (tcapQ752PegTcMsgSend);
          GET_RES (tcapQ752PegTcMsgRecv);
          GET_RES (tcapQ752PegUnrecogMsgRecv);
          GET_RES (tcapQ752PegRecvIncorrectTp);
          GET_RES (tcapQ752PegRecvBadTp);
          GET_RES (tcapQ752PegRecvUnRecogTrId);
          GET_RES (tcapQ752PegRecvUnRecogComp);
          GET_RES (tcapQ752PegRecvMisTypeComp);
          GET_RES (tcapQ752PegRecvBadComp);
          GET_RES (tcapTrafficPegPktSend);
          GET_RES (tcapTrafficPegPktRecv);
          GET_RES (tcapTrafficPegPktDrop);
          GET_RES (tcapTrafficPegPktInvald);
          GET_RES (tcapTrafficPegDiaLogEst);
          GET_RES (tcapTrafficPegDiaLogFail);
          GET_RES (tcapTrafficPegDiaLogFailAbort);
          GET_RES (tcapErrorPegRecvApiError);
          GET_RES (tcapErrorPegPeerApiError);
          GET_RES (tcapErrorPegCallFail);
          GET_RES (tcapErrorPegResourceFail);
               #undef GET_RES
               memcpy(cmd_buff, oamTcapPegResponse, Length);
               match_resp_opcode(timer_info[timer_id].opcode, &resp_opcode); 
               send_resp_to_oam(resp_opcode, operation, oam_tr_id ,pegrfu, 
                                NO_ERROR, cmd_buff, Length, entity); 
               *nxt_cmd_flg = SS7_FALSE;
               if(oamTcapPegResponse != NULL)
                 { 
                  free(oamTcapPegResponse);
                  oamTcapPegResponse = NULL;
                 }
               return ;                                    


         }
      }
#endif

        if(( msg_buff [6] == OAM_TCAP_SS7_SM_SET_TRACE_LEVEL_RESP  ) ||
           ( msg_buff [6] == OAM_TCAP_SS7_SM_SET_ERR_LEVEL_RESP    ))
         {
          Length = sizeof(ScmOamResponse);
         }
       if(g_parameter.config_flag == SS7_TRUE)
         {
          *nxt_cmd_flg = SS7_TRUE;
           g_parameter.config_cmd_resp =0;
           return ;
         }
       else
        {   
        *nxt_cmd_flg = SS7_FALSE;
        if( sendOamFlag == 1)
         match_resp_opcode(timer_info[timer_id].opcode, &resp_opcode); 
        send_resp_to_oam(resp_opcode, operation, oam_tr_id , pegrfu, 
                         NO_ERROR, NULL, Length, entity); 
         g_parameter.config_cmd_resp = 0;  
        } 
      } /* SUCCESS in command response */
 g_parameter.config_cmd_resp = 0;  
} 



/*********************************************************************************/
/* This funtion decodes the response from stk for multcmd transaction id 
   and send response to oam if oamstamp is true.*/
/*********************************************************************************/
void process_multicmd_resp(U8* msg_buff, U8* nxt_cmd_flg)
{
 U8  operation;
 U16 opcode, resp_opcode, tr_opcode, resp_error_code = 0;
 U8 timer_id = TIMER_MULTICMD;
 U32 error_code, Length , oam_tr_id, ret_val;
 Length = sizeof(ScmOamResponse);
 opcode = multi_cmd[0].msg_type;
 tr_opcode = opcode - BASE_OPCODE_SCM;
 /* handling for init garbase response */
  if(tr_opcode > OPCODEMAX)
  {
            SCM_printf(SCM_MAJOR,"Unexpected response from stk: cause:: resp waiting timer flag is zero");
           return;
  }
 /*end here*/
 oam_tr_id = oam_transaction_Id[tr_opcode].transaction_Id;
 operation = oam_transaction_Id[tr_opcode].operation; 
 strcpy(g_parameter.function_string, "process_multicmd_resp()");
 
 switch(opcode)
     {
      case OAM_SCM_SS7_STACK_CONFIG:

          nwStkConfigResp = (NwStkConfigResp*)msg_buff;
          error_code = nwStkConfigResp->erro_code;
                   resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
          if(multi_cmd[0].msg_type == OAM_SCM_SS7_STACK_CONFIG)
           {
            if((timer_info[timer_id].timer_strt_flag ==1))
              {
              multi_cmd[0].no_of_res++;
              SCM_printf(SCM_INFO,"Bsc config command response no. [%d]: ", 
                                    multi_cmd[0].no_of_res );
              }   
           else
             if(((multi_cmd[0].resp_flag) == 0) || (timer_info[timer_id].timer_strt_flag == 0) )
             {
              if((error_code == 0))
               {
                SCM_printf(SCM_INFO,"Roll back command success ");
                *nxt_cmd_flg = SS7_FALSE;
                return ;
               }
              else
                {
                multi_cmd[0].lock_flag = 0;
                SCM_printf(SCM_INFO,"Roll back command failure");
                form_resp_error_code(error_code , &resp_error_code, APP_ID_NWSTK); 
                *nxt_cmd_flg = SS7_FALSE;
                return ;
                }
              }
             else
              {
               multi_cmd[0].lock_flag = 0;
               *nxt_cmd_flg = SS7_FALSE;
               SCM_printf(SCM_MAJOR,"Bsc config command response discarded: cause waiting response timer flag is zero");
               return ; 
              }
 
            if((multi_cmd[0].roll_back_flag == 1) && (multi_cmd[0].no_of_res == 28))
              {
                 form_resp_error_code(error_code , &resp_error_code, APP_ID_NWSTK); 
                 stop_timer(TIMER_MULTICMD);
                 multi_cmd[0].no_of_res = 0; 
                 multi_cmd[0].resp_flag = 0;  
                 multi_cmd[0].lock_flag    = SS7_FALSE;
                 if(g_parameter.config_flag == 1)
                  {
                   *nxt_cmd_flg =SS7_TRUE;
                    g_parameter.config_cmd_resp = 0;
                    free(multi_cmd[0].stored_msg);
                    multi_cmd[0].stored_msg = NULL; 
                    return ;
                  }
                 else
                  {
                   //process_roll_back(multi_cmd[0].stored_msg);  /* obsolete may be used in future */ 
                   nxt_cmd_flg =SS7_FALSE;
                  // send_resp_to_oam(resp_opcode, operation, oam_tr_id , 0,
                    //              timer_info[TIMER_MULTICMD].resp_error_id, NULL, Length, APP_ID_OAM);
                 }
                }
             
               if((multi_cmd[0].no_of_res == 7) || (multi_cmd[0].no_of_res == 14)||
                  (multi_cmd[0].no_of_res == 21) || (multi_cmd[0].no_of_res == 28))
               {
                  switch(multi_cmd[0].no_of_res)
                  {
                    case 7:
                       process_nw_stack_init_config_cmd_set2 (timer_info[TIMER_MULTICMD].opcode, 
                                                              timer_info[TIMER_MULTICMD].operation);
                       break; 
                    case 14:  
                       process_nw_stack_init_config_cmd_set3 (timer_info[TIMER_MULTICMD].opcode, 
                                                              timer_info[TIMER_MULTICMD].operation);
                       break; 
                    case 21:  
                       process_nw_stack_init_config_cmd_set4 (timer_info[TIMER_MULTICMD].opcode, 
                                                              timer_info[TIMER_MULTICMD].operation);
                       break;
                    case 28:
                       stop_timer(TIMER_MULTICMD);
                       break;
                   }
               }
            if(error_code == 0)
              {
               if( multi_cmd[0].no_of_res == 28 )
               {   
                 multi_cmd[0].no_of_res = 0;
                 multi_cmd[0].resp_flag = 0;
                 multi_cmd[0].lock_flag    = 0;
                if(operation == SCM_DELETE)
                 {
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 0, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 253, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 254, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 255, 0);
                 }
                else
                 {
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 0, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 254, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 253, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 255, 0);
                 }
               if(ret_val == 1)
                 {
                   SCM_printf(SCM_INFO,"linkset value 0, 255,253 and 254 is successfully updated in linkset hash table");
                  }
               if(g_parameter.config_flag == 1)
                 {
                  SCM_printf(SCM_MAJOR,"NWSTK -> SCM 'BSC CONFIG' 'CMD RESP SUCCESS' ");
                  free(multi_cmd[0].stored_msg);
                  multi_cmd[0].stored_msg = NULL; 
                  *nxt_cmd_flg =SS7_TRUE;
                  g_parameter.config_cmd_resp = 0;
                  return ;
                 }
                else
                 {
                  *nxt_cmd_flg =SS7_FALSE;
                  SCM_printf(SCM_MAJOR,"NWSTK -> SCM 'INIT CONFIG' 'CMD RESP SUCCESS' ");
                  free(multi_cmd[0].stored_msg);
                  multi_cmd[0].stored_msg = NULL; 
                  send_resp_to_oam(resp_opcode, operation, oam_tr_id , 0,
                                   timer_info[TIMER_MULTICMD].resp_error_id, NULL, Length, APP_ID_NWSTK);
                  return ;
 
                 }   
               }     
               else
               { 
                SCM_printf(SCM_INFO,":cmd successful");
                return ;
               } 
              }
            else
             {
              if((g_parameter.redundant_status == SCM_STANDBY) && (g_parameter.config_flag == SS7_TRUE))
              {
                SCM_printf(SCM_INFO,":cmd successful: replicated from active nwstack");
                if( multi_cmd[0].no_of_res == 28 )
                {   
                 multi_cmd[0].no_of_res = 0;
                 multi_cmd[0].resp_flag = 0;
                 multi_cmd[0].lock_flag    = 0;
                 if(operation == SCM_DELETE)
                 {
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 0, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 253, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 254, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_DELETE, 255, 0);
                 }
                else
                 {
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 0, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 254, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 253, 0);
                   ret_val = checkAndUpdate_linksetValue_in_linksetHashTable(SCM_ADD, 255, 0);
                 }
               if(ret_val == 1)
                 {
                   SCM_printf(SCM_INFO,"linkset value 0, 255,253 and 254 is successfully updated in linkset hash table");
                  }
               SCM_printf(SCM_MAJOR,"NWSTK -> SCM 'BSC CONFIG' 'CMD RESP SUCCESS' ");
               free(multi_cmd[0].stored_msg);
               multi_cmd[0].stored_msg = NULL; 
               *nxt_cmd_flg =SS7_TRUE;
               g_parameter.config_cmd_resp = 0;
               }
              }
              else
              {
               form_resp_error_code(error_code , &resp_error_code, APP_ID_NWSTK); 
               timer_info[TIMER_MULTICMD].resp_error_id = ERROR_MSC_CONFIG_CMD_FAILURE;
               multi_cmd[0].roll_back_flag = 1; 
               g_roll_back_flag.multi_cmd_roll_back_flag = 1;
               SCM_printf(SCM_CRITICAL,"SS7Stack config command failure");
               if((multi_cmd[0].no_of_res == 28) && (g_parameter.config_flag != 1))
                {
                  process_roll_back(multi_cmd[0].stored_msg);   
                  g_roll_back_flag.multi_cmd_roll_back_flag = 0;
                  send_resp_to_oam(resp_opcode, operation, oam_tr_id , 0,
                                   timer_info[TIMER_MULTICMD].resp_error_id, NULL, Length, APP_ID_OAM);
                }
               } 
              return ;  
             }  
           }   
          break;
     case OAM_SCM_ALARM_MODIFY:
          switch (msg_buff[0])
               {
                case APP_ID_ISUP:
                case APP_ID_TCAP: 
                case APP_ID_MAP:
                case 163:
                      if (msg_buff[8] == 0)
                       {
                        /* Error_ID IS OF 4 BYTES IN CASE OF MAP */
                        if (msg_buff[0] != 242)
                          {
                            error_code = ((msg_buff[10] << 8) & 0xff00) | msg_buff[9];
                          }
                         else
                          {
                           error_code = ((msg_buff[10] << 8) & 0xff00) | msg_buff[9];
                           error_code = error_code | ((msg_buff[11] << 16) &   0xFF0000);
                           error_code = error_code | ((msg_buff[12] << 24) & 0xFF000000);

                          }
                        }
                       else
                         error_code = 0; 
  
                case APP_ID_NWSTK:  
                     nwStkConfigResp = (NwStkConfigResp*)msg_buff;
                     error_code = nwStkConfigResp->erro_code;
                    break;
                default:/*from cap*/
                            break;

               }
          if((timer_info[TIMER_MULTICMD].timer_strt_flag ==0))
           {
            SCM_printf(SCM_MAJOR,"Unexpected response from stack discarded: cause waiting response timer is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
           }
          else
           {
            multi_cmd[1].no_of_res++;
            if(error_code == 0)
             { 
              SCM_printf(SCM_INFO,"Alarm level modify cmd :successful "); 
             }
            else 
              {
               SCM_printf(SCM_MAJOR,"Alarm level modify cmd : failure "); 
               timer_info[TIMER_MULTICMD].resp_error_id = ERROR_ALARM_MODIFY_FAILURE; 
              }
              if(multi_cmd[1].no_of_res == 3)
               {
                stop_timer(TIMER_MULTICMD);
                if(g_parameter.config_flag == 1)
                 {
                  *nxt_cmd_flg =SS7_TRUE;
                  g_parameter.config_cmd_resp = 0;
                  return ;
                 }
                else
                 {
                  nxt_cmd_flg =SS7_FALSE;
                  multi_cmd[1].no_of_res = 0;
                  SCM_printf(SCM_MAJOR,"STACK -> SCM 'Alarm level modify' Error code: %d ", 
                             timer_info[TIMER_MULTICMD].resp_error_id); 
                  resp_opcode = SCM_OAM_ALARM_MODIFY_RESP;
                  send_resp_to_oam(resp_opcode, operation, oam_tr_id , 0,
                                   timer_info[TIMER_MULTICMD].resp_error_id, NULL, Length, APP_ID_NWSTK);
                  return ;
                 }
               }
            }
           break; 
          default:  
               SCM_printf(SCM_CRITICAL,"DECODING ERROR "); 
               break;
       
      }
 return ;
}


/*********************************************************************************/
/* This funtion dispatch the buffer to o&m*/
/*********************************************************************************/
void send_resp_to_oam(U16 opcode, U8 operation, U32 oam_tr_id , U16 pegrfu, U16 error_cd, U8* msg_buff, U16 Length, U8 app_id)
{
 U8 *oam_buff;
 S32  ret_val;
 oam_buff = (U8*)scm_malloc(1500 * sizeof(U8) );
 U16 error_code, hdr_offset;
 hdr_offset = sizeof(ScmHdr);
 error_code = error_cd;
 strcpy(g_parameter.function_string, "send_resp_to_oam()");
/* SCM_printf(SCM_DEBUG,"In Func: send_resp_to_oam\n");*/
 if(g_parameter.noOam_resp_flag == 1)  
  {
    g_parameter.noOam_resp_flag = 0;
    if(g_parameter.map_tcap_msg != NULL)                   
    {
     SCM_printf(SCM_DEBUG,"Retrive stored cmd ON CARD\n");
     process_maptcap_stack_cmd(g_parameter.map_tcap_msg);
     free(g_parameter.map_tcap_msg);
     g_parameter.map_tcap_msg = NULL;
    }
    free(oam_buff);
    oam_buff = NULL;
    
   return;
  }
 if(error_code == NO_ERROR)
   {
    SCM_printf(SCM_INFO,"Stk cmd response successful\n");
    if( (xxx_client_sockfd[ENT_PEER_SCM] > 0 ))
     {
      if( (g_parameter.peer_nwstk_cmdFlag == 1) || (g_parameter.peer_lapd_cmdFlag == 1) || (g_parameter.peer_multi_cmdFlag == 1)||
          (g_parameter.peer_map_tcap_cmdFlag == 1))/*AOIP-HA*/
      {
       SCM_printf(SCM_INFO,"Updating peer scm stack configuration ");
       ret_val = send_config_update_to_peer_scm(); 
      if( ret_val <= 0)
       {
        SCM_printf(SCM_INFO,"COMMAND SEND TO PEER SCM FAILURE");
        error_code = ERROR_PEERSCM_WRITE_FAILED; 
       }
      else
       {    
        free(oam_buff);
        oam_buff=NULL;  
        return;
       }
      } 
    } 
   }
 else
   {
    SCM_printf(SCM_MAJOR,"Stk cmd response failure");
    CheckIfPegRespFailed(&opcode, error_code);  
    switch(app_id)
      {
       case APP_ID_NWSTK:
          if(g_parameter.peer_nwstk_cmdFlag == 1)
            {
             if(g_parameter.nwstk_msg != NULL)
              {
               g_parameter.peer_nwstk_cmdFlag = 0;
               free(g_parameter.nwstk_msg) ;
               g_parameter.nwstk_msg = NULL;
              }
            }
           else if(g_parameter.peer_multi_cmdFlag == 1)
           {
            g_parameter.peer_multi_cmdFlag = 0;
            free(g_parameter.multicmd_msg) ;
            g_parameter.multicmd_msg = NULL;
           }    
       break;
     /*AOIP-HA*/
       case APP_ID_SIGTRAN:
       case APP_ID_MAP:
            if(g_parameter.peer_map_tcap_cmdFlag == 1)
             {
               g_parameter.peer_map_tcap_cmdFlag = 0;
               if(g_parameter.map_tcap_msg != NULL)
                {
                   free(g_parameter.map_tcap_msg) ;
                   g_parameter.map_tcap_msg = NULL;
                }
             }
       break;
     /*AOIP-END*/
       default:
       break;

      } 
   }

 if(msg_buff != NULL)
  {
   memcpy(oam_buff, msg_buff, (Length )); 
  }
 else
 {
   Length = sizeof(ScmOamResponse);
   ((ScmOamResponse*)(oam_buff))->erro_code = (S16)error_code;
   //EXTRACT_16( hdr_offset, error_code,  oam_buff);
 }
 form_oam_header( oam_buff, opcode, operation, oam_tr_id, pegrfu,  Length);  
 if((g_parameter.redundant_status == SCM_STANDBY))
  {
   if( (xxx_client_sockfd[ENT_PEER_SCM] > 0 ))
    {
      SCM_printf (SCM_MAJOR, "SCM - > PEER SCM 'STACK COMMAND UPDATE'");
      ret_val = scm_dispatch_buffer(oam_buff, APP_ID_PEER_SCM, Length); 
      /*AOIP_HA*/
  /*    if(g_parameter.noOam_resp_flag == 1) 
       {
           g_parameter.noOam_resp_flag = 0;
           
           if(g_parameter.map_tcap_msg != NULL)                   
            {
               SCM_printf(SCM_DEBUG,"Retrive stored cmd STDBY CARD\n");
               process_oam_message(g_parameter.map_tcap_msg);
               free(g_parameter.map_tcap_msg);
               g_parameter.map_tcap_msg = NULL;
            }
       }*/
      /*AOIP_HA end*/
    }
  else
    {
     SCM_printf (SCM_CRITICAL, "CAN NOT SEND MSG: CAUSE - PEER SCM IS DOWN");
    }       
  }
 else   /*AOIP ACTIVE CARD*/
  { 
   SCM_printf (SCM_MAJOR, "SCM - > OAM 'STACK COMMAND RESPONSE'\n");
   ret_val = scm_dispatch_buffer(oam_buff, APP_ID_OAM, Length); 
   SCM_printf(SCM_INFO,"-----------------------------------------------------------------------------\n");
/*    if(g_parameter.noOam_resp_flag == 1) 
       {
           g_parameter.noOam_resp_flag = 0;
           
           if(g_parameter.map_tcap_msg != NULL)                   
            {
               SCM_printf(SCM_DEBUG,"Retrive stored cmd ACTV CARD\n");
               process_oam_message(g_parameter.map_tcap_msg);
               free(g_parameter.map_tcap_msg);
               g_parameter.map_tcap_msg = NULL;
            }
       }*/
  }
 if(ret_val <= 0)
  {
   SCM_printf (SCM_CRITICAL, "Write to oam socket failure");
  }
 
 if(oam_buff !=  NULL)
   { 
    free(oam_buff);
    oam_buff = NULL;
   } 
 return ;
}
/*********************************************************************************/
/* This funtion sends oam config updates to peer card scm stack    */             
/*********************************************************************************/

int send_config_update_to_peer_scm()
{
 U8 len;
 S32 ret;
 strcpy(g_parameter.function_string, "send_config_update_to_peer_scm()");
 
#define SET_OPERATION(A)\
        if(A == SCM_ADD)    A = SCM_DELETE;\
        if(A == SCM_DELETE) A = SCM_ADD;
   if((g_parameter.peer_nwstk_cmdFlag == 1)  && (timer_info[TIMER_NWSTK].resp_from_peer_cardFlag == 1))
  {
   if(g_parameter.nwstk_msg != NULL)
    {
     len = ((ScmHdr*)g_parameter.nwstk_msg)->len;
     ((ScmHdr*)g_parameter.nwstk_msg)->appid = APP_ID_PEER_SCM;
     ret = scm_dispatch_buffer(g_parameter.nwstk_msg, APP_ID_PEER_SCM, len);
     //((ScmHdr*)g_parameter.nwstk_msg)->opcode = APP_ID_PEER_SCM;
     timer_info[TIMER_NWSTK].resp_from_peer_cardFlag = 0;
     if(ret <= 0)
      {
       SET_OPERATION(((ScmHdr*)g_parameter.nwstk_msg)->operation); 
       g_roll_back_flag.nwstk_roll_back_flag = 1;
       process_oam_message(g_parameter.nwstk_msg);
       g_parameter.peer_nwstk_cmdFlag = 0;
       free(g_parameter.nwstk_msg);
       g_parameter.nwstk_msg = NULL;
       return 0;
      }
     else
      {
        return 1;
      }
     }
   return 0;
  }
  if((g_parameter.peer_lapd_cmdFlag == 1)  && (timer_info[TIMER_LAPD].resp_from_peer_cardFlag == 1))
  {
   if(g_parameter.lapd_msg != NULL)
    {
     len = ((ScmHdr*)g_parameter.lapd_msg)->len;
     ((ScmHdr*)g_parameter.lapd_msg)->appid = APP_ID_PEER_SCM;
     ret = scm_dispatch_buffer(g_parameter.lapd_msg, APP_ID_PEER_SCM, len);
     //((ScmHdr*)g_parameter.lapd_msg)->opcode = APP_ID_PEER_SCM;
     timer_info[TIMER_LAPD].resp_from_peer_cardFlag = 0;
     if(ret <= 0) 
      { 
       SET_OPERATION(((ScmHdr*)g_parameter.lapd_msg)->operation); 
       g_roll_back_flag.lapd_roll_back_flag = 1;
       process_oam_message(g_parameter.lapd_msg);
       g_parameter.peer_lapd_cmdFlag = 0;
       free(g_parameter.lapd_msg);
       g_parameter.lapd_msg = NULL;
       return 0;
      } 
     else 
      { 
        return 1;
      } 
     } 
   return 0; 
  } 
  if((g_parameter.peer_multi_cmdFlag == 1)  && (timer_info[TIMER_MULTICMD].resp_from_peer_cardFlag == 1))
  {
   if(g_parameter.multicmd_msg != NULL)
    {
     len = ((ScmHdr*)g_parameter.multicmd_msg)->len;
     ((ScmHdr*)g_parameter.multicmd_msg)->appid = APP_ID_PEER_SCM;
     ret = scm_dispatch_buffer(g_parameter.multicmd_msg, APP_ID_PEER_SCM, len);
     timer_info[TIMER_MULTICMD].resp_from_peer_cardFlag = 0;
     if(ret <= 0)/* this will rare possible */ 
     { 
      SET_OPERATION(((ScmHdr*)g_parameter.multicmd_msg)->operation); 
      g_roll_back_flag.multi_cmd_roll_back_flag = 1;
      process_oam_message(g_parameter.multicmd_msg);
      g_roll_back_flag.multi_cmd_roll_back_flag = 0;
      g_parameter.peer_multi_cmdFlag = 0;
      free(g_parameter.multicmd_msg);
      g_parameter.multicmd_msg = NULL;
      return 0;
     } 
     else 
      { 
        return 1;
      } 
     } 
   return 0; 
  }

/*AOIP_HA*/
 if((g_parameter.peer_map_tcap_cmdFlag == 1)  && (timer_info[TIMER_SIGTRAN].resp_from_peer_cardFlag == 1))
  {
   if(g_parameter.map_tcap_msg != NULL)
    {
     len = ((ScmHdr*)g_parameter.map_tcap_msg)->len;
     ((ScmHdr*)g_parameter.map_tcap_msg)->appid = APP_ID_PEER_SCM;
     ret = scm_dispatch_buffer(g_parameter.map_tcap_msg, APP_ID_PEER_SCM, len);
     timer_info[TIMER_SIGTRAN].resp_from_peer_cardFlag = 0;
     if(ret <= 0)
      {
       /*SET_OPERATION(((ScmHdr*)g_parameter.nwstk_msg)->operation);
       g_roll_back_flag.maptcap_roll_back_flag = 1;
       process_oam_message(g_parameter.nwstk_msg);*/
       g_parameter.peer_map_tcap_cmdFlag = 0;
       free(g_parameter.map_tcap_msg);
       g_parameter.map_tcap_msg = NULL;
       return 0;
      }
     else
      {
        return 1;
      }
     }
   return 0;
  }

/*AOIP END*/ 

#undef SET_OPERATION 
return 1;
}

void process_bssap_stack_resp(U8* msg_buff, U8* nxt_cmd_flg)
{
 U32  oam_tr_id, Length;
 U8   opcode, transaction_id, operation;
 U16  resp_opcode, tr_opcode, pegrfu;
 U16  resp_error_code =0;

 I_S16 error_code = 0;
 nwStkConfigResp = (NwStkConfigResp*)msg_buff;

/* SCM_printf(SCM_MAJOR,"DEBUG:: erro_code [%d] nwStkConfigResp->erro_code[%d] sizeof(NwStkConfigResp)[%d]\n", error_code, nwStkConfigResp->erro_code, sizeof(NwStkConfigResp));*/
 
 Length = sizeof(ScmOamResponse);
 transaction_id = nwStkConfigResp->nwstkhdr.trid;
 error_code     = nwStkConfigResp->erro_code;
 opcode         = nwStkConfigResp->nwstkhdr.opcode;
/*tr_opcode      = timer_info[TIMER_ISUP].opcode - BASE_OPCODE_SCM;*/
 tr_opcode      = timer_info[TIMER_BSSAP].opcode - BASE_OPCODE_SCM_AOIP;

 switch(opcode)
   {
      case BSSAP_SCM_INTF_ADD_RESP:
      case BSSAP_SCM_INTF_DEL_RESP:
           if((transaction_id != transaction_Id[SCM_BSSAP_INTF_ADD])
                && (timer_info[TIMER_BSSAP].timer_strt_flag != 1))
              {
               SCM_printf(SCM_MAJOR,"Unexpected response from bssap: cause:: resp waiting timer flag is zero");
               *nxt_cmd_flg = SS7_FALSE; 
               return ;
              }
           else
           timer_info[TIMER_BSSAP].resp_error_id = error_code;
           if(Reconf_Flag == SS7_TRUE)
            {
              resp_opcode = SCM_OAM_BS_TIMER_CONFIG_RESP;
              stop_timer(TIMER_BSSAP);
              Reconf_Flag = SS7_FALSE;
              SCM_printf(SCM_MAJOR,"SCM  <- BSSAP 'RECONFIG_BSSAP_INTERFACE_RESP' ****\n");
            }
           else
            {
              resp_opcode = SCM_OAM_BS_INTERFACE_CONFIG_RESP;
              stop_timer(TIMER_BSSAP);
              SCM_printf(SCM_MAJOR,"SCM  <- BSSAP 'BSSAP_INTERFACE_CONFIG_RESP' ****\n");
            }
           break;
 
      default:
           SCM_printf(SCM_MAJOR,"UNEXPECTED RESP FROM BSSAP #@#@#@#\n");
           return 0;
           break;
   
     }

   if((error_code != 0 ))
   {
      SCM_printf(SCM_MAJOR,"BSSAP CMD FAILURE: error code: %d", error_code);
      form_resp_error_code(error_code , &resp_error_code, APP_ID_BS); 
   }
  else 
   SCM_printf(SCM_INFO,"BSSAP CMD successful\n");


  if((g_parameter.config_flag == SS7_TRUE) ||(timer_info[TIMER_BSSAP].db_oam_stamp == DB_STAMP))
   {
     SCM_printf(SCM_DEBUG,"Bssap Config Cmd from Db  success");
     *nxt_cmd_flg = SS7_TRUE;
/*     g_parameter.noOam_resp_flag = 0; used for adminstate may be  cmd sent & also conf. in progress */
     g_parameter.config_cmd_resp = 0;
    }
    else
   {
     SCM_printf(SCM_DEBUG,"Bssap Config Cmd from OAM  success\n");
     oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
     operation =  oam_transaction_Id[tr_opcode].operation;
     pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
     send_resp_to_oam(resp_opcode, operation, oam_tr_id, pegrfu, resp_error_code, NULL, Length, APP_ID_BS);
   }

}

/*AOIP: SIGTRAN RESPONSE FUNC*/
process_resp_from_sigtran_stack(U8 *msg_buff, U8 *nxt_cmd_flg, U32 numbytes, U32 entity)
{
      U16   Length,  resp_error_code = 0;
      unsigned long  error_code;
      U8 cmd_buff [200], resp_entity, sendOamFlag = 1;
      U32  oam_tr_id;
      U8 transaction_id,  operation, timer_id;
      U16  opcode, resp_opcode, tr_opcode, pegrfu;

      strcpy(g_parameter.function_string, "process_resp_from_stack()");
     
      Length         = sizeof(ScmOamResponse);
      opcode         = msg_buff[6];
      transaction_id = msg_buff[7];
      resp_entity    = APP_ID_SIGTRAN;    
    
        
      timer_id = TIMER_SIGTRAN;
     /* tr_opcode = timer_info[timer_id].opcode - BASE_OPCODE_SCM;*/
      tr_opcode = timer_info[timer_id].opcode - BASE_OPCODE_SCM_AOIP;       
        
      if((transaction_id != transaction_Id[tr_opcode])
               && (timer_info[timer_id].timer_strt_flag != 1))
          {
            SCM_printf(SCM_MAJOR,"Unexpected response from map/tcap discarded: cause wainting response timer flag is zero");
            *nxt_cmd_flg = SS7_FALSE;
            return ;
          }

      timer_info[timer_id].resp_error_id = 0; /*marked 1 in case of error so make 0 here*/
   
      if(msg_buff[8] == 0) /* Command Failure */
       {
           g_parameter.config_cmd_resp = 0;  
           SCM_printf(SCM_MAJOR,"command failure ");
           SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||");
           SCM_printf(SCM_INFO,"");
           timer_info[timer_id].resp_error_id = 1;   
           stop_timer(TIMER_SIGTRAN); /*AOIP-HA*/
           /* Error_ID IS OF 2 BYTES IN CASE OF SIGTRAN */
           
           error_code = ((msg_buff[10] << 8) & 0xff00) | msg_buff[9];

           SCM_printf(SCM_MAJOR,"error code received: %d", error_code);
           timer_info[timer_id].resp_error_id = error_code;
           form_resp_error_code(error_code , &resp_error_code, resp_entity); 
           SCM_printf(SCM_INFO,"|||||||||||||||||||||||||||||||||||||||||");
           SCM_printf(SCM_INFO,"");
           if(g_parameter.config_flag == SS7_TRUE || (timer_info[TIMER_SIGTRAN].db_oam_stamp == DB_STAMP))
            {
              *nxt_cmd_flg = SS7_TRUE;
              g_parameter.config_cmd_resp = 0;  
            }
           else
            { 
              oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
              operation =  oam_transaction_Id[tr_opcode].operation;
              pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
              match_resp_opcode(timer_info[timer_id].opcode, &resp_opcode); 
              if(g_roll_back_flag.maptcap_roll_back_flag == 1)  /*AOIP-HA error PEER FAILED*/ 
               {
                  SCM_printf(SCM_INFO,"Sigtran Cmd ROLLBACK got FAILED.....\n"); 
                  g_roll_back_flag.maptcap_roll_back_flag = 0;   /*ROLL_BACK FAILS*/ 
                  return;
               }
              send_resp_to_oam(resp_opcode, operation, oam_tr_id , pegrfu, resp_error_code, 
                              NULL, Length, entity);
            }
           return ;
       }
      else/* SUCCESS in command response */
       {
          
           SCM_printf(SCM_INFO,"SIGTRAN CMD FROM %s SUCCESS noOamResp[%d]\n", 
           ((timer_info[TIMER_SIGTRAN].db_oam_stamp == DB_STAMP) ? "DB" : "OAM"), g_parameter.noOam_resp_flag);
           
           stop_timer(TIMER_SIGTRAN);/*AOIP-HA*/

           Length = sizeof(ScmOamResponse);

           if(g_parameter.config_flag == SS7_TRUE || (timer_info[TIMER_SIGTRAN].db_oam_stamp == DB_STAMP))
            {
              *nxt_cmd_flg = SS7_TRUE;
              g_parameter.config_cmd_resp =0;
              return ;
            }
           else
            {   
              oam_tr_id =  oam_transaction_Id[tr_opcode].transaction_Id;
              operation =  oam_transaction_Id[tr_opcode].operation;
              pegrfu =  oam_transaction_Id[tr_opcode].pegrfu;
              match_resp_opcode(timer_info[timer_id].opcode, &resp_opcode);
                                                       
              if(g_roll_back_flag.maptcap_roll_back_flag == 1)  /*AOIP-HA error PEER FAILED*/ 
               {
                  SCM_printf(SCM_INFO,"Sigtran Cmd ROLLBACK Success\n"); 
                  g_roll_back_flag.maptcap_roll_back_flag = 0;   /*ROLL_BACK SUCCESS*/ 
               }
              else 
               {
                  send_resp_to_oam(resp_opcode, operation, oam_tr_id , pegrfu, NO_ERROR, 
                              NULL, Length, entity); 
               }
              g_parameter.config_cmd_resp = 0;  
             } 
       } /* SUCCESS in command response */


}
/*AOIP: END*/

/*********************************************************************************/
/* This funtion extracts the response code from cmdcode to respond oam    */             
/*********************************************************************************/
void match_resp_opcode(U16 opcode, U16 *resp_opcode)
{
 //SCM_printf (SCM_INFO, "OPCODE VALUE TO EXTRACT RESP OPCODE : %d ", opcode);
 strcpy(g_parameter.function_string, "match_resp_opcode()");
 switch(opcode)
  {
   case OAM_SCM_SS7_STACK_CONFIG:
        *resp_opcode = SCM_OAM_SS7_STACK_CONFIG_RESP;
        break;

   case OAM_SCM_ALARM_MODIFY:
        *resp_opcode = SCM_OAM_ALARM_MODIFY_RESP;
        break;
   case OAM_SCM_MTP3_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_MTP3_TIMER_CONFIG_RESP;
        break;
   case OAM_SCM_SCCP_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_TIMER_CONFIG_RESP;
        break;
   case OAM_SCM_BSSAP_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_BSSAP_TIMER_CONFIG_RESP;
        break;
#if 0 
Amaresh   
case OAM_SCM_MAP_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_MAP_TIMER_CONFIG_RESP;
        break;
#endif
   case OAM_SCM_INTERFACE_CONFIG:
        *resp_opcode = SCM_OAM_INTERFACE_CONFIG_RESP;
        break;
   case OAM_SCM_LINKSET_CONFIG:
        *resp_opcode = SCM_OAM_LINKSET_CONFIG_RESP;
        break;
   case OAM_SCM_LINKSET_ADMIN_CONFIG:
        *resp_opcode = SCM_OAM_LINKSET_ADMIN_CONFIG_RESP;
        break;
   case OAM_SCM_LINK_CONFIG:
        *resp_opcode = SCM_OAM_LINK_CONFIG_RESP;
        break;
   case OAM_SCM_LINK_ADMIN_CONFIG:
        *resp_opcode = SCM_OAM_LINK_ADMIN_CONFIG_RESP;
        break;
   case OAM_SCM_SS7ROUTE_CONFIG:
        *resp_opcode = SCM_OAM_SS7ROUTE_CONFIG_RESP;
        break;
   case OAM_SCM_SS7ROUTE_ADMIN_CONFIG:
        *resp_opcode = SCM_OAM_SS7ROUTE_ADMIN_CONFIG_RESP;
        break;
   case OAM_SCM_SS7ROUTE_TESTON_CONFIG:
        *resp_opcode = SCM_OAM_SS7ROUTE_TESTON_CONFIG_RESP;
        break;
   case OAM_SCM_SCCP_BEHAVIOR_CONFIG:
        SCM_printf (SCM_INFO, "\n SCCP BEHAVIOUR CONFIG");
        *resp_opcode = 0;
        break;
   case OAM_SCM_MTP3_GENPEG_GET:
        *resp_opcode = SCM_OAM_MTP3_GENPEG_RESP;
        break;
   case OAM_SCM_LINK_PEG_GET:
        *resp_opcode = SCM_OAM_LINK_PEG_RESP;
        break;
   case OAM_SCM_SS7ROUTE_PEG_GET:
        *resp_opcode = SCM_OAM_ROUTE_PEG_RESP;
        break;
   case OAM_SCM_SCCP_GENPEG_GET:
        *resp_opcode = SCM_OAM_SCCP_GENPEG_RESP;
        break;
   case OAM_SCM_BSSAP_GENPEG_GET:
        *resp_opcode = SCM_OAM_BSSAP_GENPEG_RESP;
        break;
#if 0 
Amaresh
   case OAM_SCM_TCAP_PEG_GET:
        *resp_opcode = SCM_OAM_TCAP_PEG_RESP;
        break;
#endif
   case OAM_SCM_LINKSET_STATUS_GET:
        *resp_opcode = SCM_OAM_LINKSET_STATUS_RESP;
        break;
   case OAM_SCM_LINK_STATUS_GET:
        *resp_opcode = SCM_OAM_LINK_STATUS_RESP;
        break;
   case OAM_SCM_ROUTE_STATUS_GET:
        *resp_opcode = SCM_OAM_ROUTE_STATUS_RESP;
        break;
   case OAM_SCM_SSN_STATUS_GET:
        *resp_opcode = SCM_OAM_SSN_STATUS_RESP;
        break;
  case OAM_SCM_LAPDTS_CONFIG:
        *resp_opcode = SCM_OAM_LAPDTS_CONFIG_RESP;
        break;
  case OAM_SCM_LAPDTEI_CONFIG: 
        *resp_opcode = SCM_OAM_LAPDTEI_CONFIG_RESP;
        break;
  case OAM_SCM_LAPDSAPI_CONFIG: 
        *resp_opcode = SCM_OAM_LAPDSAPI_CONFIG_RESP;
        break;
  case OAM_SCM_LAPDTIMER_CONFIG: 
        *resp_opcode = SCM_OAM_LAPDTIMER_CONFIG_RESP;
        break;
  case OAM_SCM_LAPD_PEG_GET: 
        *resp_opcode = SCM_OAM_LAPD_PEG_RESP;
        break;
  case OAM_SCM_MTP2_PEG_GET: 
        *resp_opcode = SCM_OAM_MTP2_PEG_RESP;
        break;
 /*AOIP CASES*/
  case OAM_SCM_BS_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_BS_TIMER_CONFIG_RESP;
        break; 
  case OAM_SCM_BS_INTERFACE_CONFIG:
        *resp_opcode = SCM_OAM_BS_INTERFACE_CONFIG_RESP;
        break; 
  case OAM_SCM_SCCP_SP_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_SP_CONFIG_RESP;
        break; 
  case OAM_SCM_SCCP_SS_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_SS_CONFIG_RESP;
        break; 
  case OAM_SCM_SCCP_CSS_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_CSS_CONFIG_RESP;
        break; 
  case OAM_SCM_SCCP_CSP_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_CSP_CONFIG_RESP;
        break; 
  case OAM_SCM_SCCP_TMR_CONFIG:
        *resp_opcode = SCM_OAM_SCCP_TMR_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_LOCAL_ASP_ADMIN_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_LOCAL_ASP_ADMIN_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_LOCAL_ASP_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_LOCAL_ASP_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_REMOTE_ASP_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_REMOTE_ASP_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_LOCAL_AS_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_LOCAL_AS_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_REMOTE_AS_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_REMOTE_AS_CONFIG_RESP;
        break; 
  case OAM_SCM_M3UA_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_M3UA_TIMER_CONFIG_RESP;
        break; 
  case OAM_SCM_SCTP_GEN_CONFIG:
        *resp_opcode = SCM_OAM_SCTP_GEN_CONFIG_RESP;
        break; 
  case OAM_SCM_SCTP_TIMER_CONFIG:
        *resp_opcode = SCM_OAM_SCTP_TIMER_CONFIG_RESP;
        break; 
 /*AOIP END*/
  default:
        SCM_printf (SCM_MAJOR, "WRONG OPCODE VALUE FOR RESP OPCODE MATCH");
        *resp_opcode = 0;
        break;
  }
}
